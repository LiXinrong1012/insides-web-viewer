/*
 * Copyright (c) by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.824 2011-01-25 01:14:00 heppe Exp $
 */


#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "phedron.h"
#include "phdraw.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hc_proto.h"
#include "patterns.h"
#include "hpserror.h"
#include "lod.h"
#include "adt.h"


#define _hoops_HSCIS(_hoops_IHCR,phon) _hoops_GHIA(\
	if ((BIT ((_hoops_IHCR)->heuristics, _hoops_GPSA) && \
		 !BIT ((phon)->polyhedron_flags, PHF_IMPLICIT_NORMALS_REVERSED)) || \
		(BIT ((_hoops_IHCR)->heuristics, _hoops_SASA) && \
		 BIT ((phon)->polyhedron_flags, PHF_IMPLICIT_NORMALS_REVERSED))) { \
		_hoops_ISCIS ((Polyhedron alter *)(phon)); \
	} \
)



_hoops_SGRGH::~_hoops_SGRGH () {
#if 0
	if (_hoops_CSCIS.tristrips != null)
		_hoops_SSCIS();
	if (_hoops_CSCIS._hoops_CHGPR != null)
		_hoops_GGSIS();
	if (_hoops_CSCIS._hoops_SHGPR != null)
		_hoops_RGSIS();
	if (_hoops_CSCIS._hoops_GIGPR != null)
		_hoops_AGSIS();
#endif

	_hoops_HPRH (_hoops_IPRI);
}

#if 0
void _hoops_SGRGH::_hoops_PGSIS () alter {
	Polyhedron alter *		_hoops_HPGPR = (Polyhedron alter *)_hoops_IPRI;

	_hoops_CSCIS.tristrips = _hoops_IPRI->tristrips;
	_hoops_CSCIS._hoops_ACRHR = _hoops_IPRI->_hoops_ACRHR;
	_hoops_HPGPR->tristrips = null;
	_hoops_HPGPR->_hoops_ACRHR = 0;
}
void _hoops_SGRGH::_hoops_HGSIS () alter {
	Polyhedron alter *		_hoops_HPGPR = (Polyhedron alter *)_hoops_IPRI;

	_hoops_CSCIS._hoops_SHGPR = _hoops_IPRI->_hoops_SHGPR;
	_hoops_CSCIS._hoops_RSHPR = _hoops_IPRI->_hoops_RSHPR;
	_hoops_HPGPR->_hoops_SHGPR = null;
	_hoops_HPGPR->_hoops_RSHPR = 0;
}
void _hoops_SGRGH::_hoops_IGSIS () alter {
	Polyhedron alter *		_hoops_HPGPR = (Polyhedron alter *)_hoops_IPRI;

	_hoops_CSCIS._hoops_CHGPR = _hoops_IPRI->_hoops_CHGPR;
	_hoops_HPGPR->_hoops_CHGPR = null;
}
void _hoops_SGRGH::_hoops_CGSIS () alter {
	Polyhedron alter *		_hoops_HPGPR = (Polyhedron alter *)_hoops_IPRI;

	_hoops_CSCIS._hoops_GIGPR = _hoops_IPRI->_hoops_GIGPR;
	_hoops_CSCIS._hoops_AGRHR = _hoops_IPRI->_hoops_AGRHR;
	_hoops_HPGPR->_hoops_GIGPR = null;
	_hoops_HPGPR->_hoops_AGRHR = 0;
}

void _hoops_SGRGH::_hoops_SSCIS () alter {
	Polyhedron alter *		_hoops_HPGPR = (Polyhedron alter *)_hoops_IPRI;

	HI_Free_Tristrip_List (_hoops_HPGPR->tristrips);
	_hoops_HPGPR->tristrips = _hoops_CSCIS.tristrips;
	_hoops_HPGPR->_hoops_ACRHR = _hoops_CSCIS._hoops_ACRHR;
	_hoops_CSCIS.tristrips = null;
}
void _hoops_SGRGH::_hoops_RGSIS() alter {
	Polyhedron alter *		_hoops_HPGPR = (Polyhedron alter *)_hoops_IPRI;

	HI_Free_Polyedge_List (_hoops_HPGPR->_hoops_SHGPR);
	_hoops_HPGPR->_hoops_SHGPR = _hoops_CSCIS._hoops_SHGPR;
	_hoops_HPGPR->_hoops_RSHPR = _hoops_CSCIS._hoops_RSHPR;
	_hoops_CSCIS._hoops_SHGPR = null;
}
void _hoops_SGRGH::_hoops_GGSIS() alter {
	Polyhedron alter *		_hoops_HPGPR = (Polyhedron alter *)_hoops_IPRI;

	HI_Free_Polyedge_List (_hoops_HPGPR->_hoops_CHGPR);
	_hoops_HPGPR->_hoops_CHGPR = _hoops_CSCIS._hoops_CHGPR;
	_hoops_CSCIS._hoops_CHGPR = null;
}
void _hoops_SGRGH::_hoops_AGSIS () alter {
	Polyhedron alter *		_hoops_HPGPR = (Polyhedron alter *)_hoops_IPRI;

	HI_Free_Polymarker_List (_hoops_HPGPR->_hoops_GIGPR);
	_hoops_HPGPR->_hoops_GIGPR = _hoops_CSCIS._hoops_GIGPR;
	_hoops_HPGPR->_hoops_AGRHR = _hoops_CSCIS._hoops_AGRHR;
	_hoops_CSCIS._hoops_GIGPR = null;
}
#endif



GLOBAL_FUNCTION void HD_Report_Null_Color_Map (
	char const *				_hoops_IPRI,
	_hoops_RHAH const *			_hoops_CSIR) {
	char						buf[MAX_ERRMSG];

	if (!strcmp(_hoops_IPRI, "shell") || !strcmp(_hoops_IPRI, "mesh"))
		HE_ERROR2 (HEC_TRISTRIP, HES_REQUIRES_COLOR_MAP,
							  "Shell or mesh requires a color map,",
				   Sprintf_P (buf,
							  "but the current map (from '%p') is of length zero.",
							  _hoops_CSIR->owner));
	else
		HE_ERROR2 (HEC_TRISTRIP, HES_REQUIRES_COLOR_MAP,
				   "Tristrip, polyedge, or polymarker requires a color map,",
				   Sprintf_P (buf,
							  "but the current map (from '%p') is of length zero.",
							  _hoops_CSIR->owner));
}




local void _hoops_ISCIS (
	Polyhedron alter *			_hoops_IPRI) {
	Vector alter *				normal;
	Vector const *				end;

	if (!ANYBIT (_hoops_IPRI->polyhedron_flags, 
		PHF_VERTEX_NORMALS_VALID |
		PHF_FACE_NORMALS_VALID |
		_hoops_GAAHR))
		return;

	if (BIT (_hoops_IPRI->polyhedron_flags, PHF_VERTEX_NORMALS_VALID)) {
		if (_hoops_IPRI->local_vertex_attributes.explicit_normal_count != 
			_hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR) {
			normal = _hoops_IPRI->local_vertex_attributes.normals;
			if (normal != null) {
				Local_Vertex_Flags const *	flags;

				flags = _hoops_IPRI->local_vertex_attributes._hoops_CHHPR();
				end = normal + _hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR;
				while (normal < end) {
					if (!BIT (*flags, LVA_EXPLICIT_NORMAL)) {
						normal->x = -normal->x;
						normal->y = -normal->y;
						normal->z = -normal->z;
					}
					normal++;
					if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR))
						flags++;
				}
			}
		}
	}

	if (BIT (_hoops_IPRI->polyhedron_flags, PHF_FACE_NORMALS_VALID)) {
		if (_hoops_IPRI->local_face_attributes.explicit_normal_count != 
			_hoops_IPRI->face_count) {
			_hoops_ARPA alter *plane;
			_hoops_ARPA alter *_hoops_HRHRA;

			plane = _hoops_IPRI->local_face_attributes.normals;
			if (plane != null) {
				_hoops_GIIPR const *	flags;

				flags = _hoops_IPRI->local_face_attributes._hoops_CHHPR();
				_hoops_HRHRA = plane + _hoops_IPRI->face_count;
				while (plane < _hoops_HRHRA) {
					if (!BIT (*flags, LFA_EXPLICIT_NORMAL)) {
						plane->a = -plane->a;
						plane->b = -plane->b;
						plane->c = -plane->c;
						plane->d = -plane->d;
					}
					plane++;
					if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR))
						flags++;
				}
			}
		}
	}

	if (BIT (_hoops_IPRI->polyhedron_flags, _hoops_GAAHR)) {
		if (_hoops_IPRI->_hoops_IHHPR.explicit_normal_count != 
			_hoops_IPRI->_hoops_SPHA) {
			normal = _hoops_IPRI->_hoops_IHHPR.normals;
			if (normal != null) {
				_hoops_GHHPR const *	flags;

				flags = _hoops_IPRI->_hoops_IHHPR.flags;
				end = normal + _hoops_IPRI->_hoops_SPHA;
				while (normal < end) {
					if (!BIT (*flags, _hoops_CRAHR)) {
						normal->x = -normal->x;
						normal->y = -normal->y;
						normal->z = -normal->z;
					}
					normal++;
					flags++;
				}
			}
		}
	}

	/* _hoops_HRCI _hoops_AIRI _hoops_CPCI */
	{
		Tristrip *			ts;

		if ((ts = _hoops_IPRI->tristrips) != null) do {
			_hoops_GACR *		dl;

			if (ts->_hoops_ICHA || ts->_hoops_PRHH) {
				while ((dl = ts->_hoops_GAHA) != null) {
					ts->_hoops_GAHA = dl->next;
					_hoops_HPRH(dl);
				}
			}
		} while ((ts = ts->next) != null);
	}
	{
		Polyedge *			pe;

		if ((pe = _hoops_IPRI->_hoops_SHGPR) != null) do {
			_hoops_GACR *		dl;

			if (pe->_hoops_ICHA || pe->_hoops_RSHA) {
				while ((dl = pe->_hoops_GAHA) != null) {
					pe->_hoops_GAHA = dl->next;
					_hoops_HPRH(dl);
				}
			}
		} while ((pe = pe->next) != null);

		if ((pe = _hoops_IPRI->_hoops_CHGPR) != null) do {
			_hoops_GACR *		dl;

			if (pe->_hoops_ICHA || pe->_hoops_RSHA) {
				while ((dl = pe->_hoops_GAHA) != null) {
					pe->_hoops_GAHA = dl->next;
					_hoops_HPRH(dl);
				}
			}
		} while ((pe = pe->next) != null);
	}
	{
		Polymarker *			pm;

		if ((pm = _hoops_IPRI->_hoops_GIGPR) != null) do {
			_hoops_GACR *		dl;

			if (pm->_hoops_ICHA) {
				while ((dl = pm->_hoops_GAHA) != null) {
					pm->_hoops_GAHA = dl->next;
					_hoops_HPRH(dl);
				}
			}
		} while ((pm = pm->next) != null);
	}

	/* _hoops_SGSIS _hoops_PIHHR _hoops_IS _hoops_GIARC _hoops_RH _hoops_GRSIS _hoops_IGRH */
	_hoops_IPRI->polyhedron_flags ^= PHF_IMPLICIT_NORMALS_REVERSED;
}


local _hoops_RRCC * _hoops_RRSIS (
	Net_Rendition const & 			nr,
	Polyhedron const *				_hoops_IPRI) {
	Local_Vertex_Attributes alter *	_hoops_SPRI = (Local_Vertex_Attributes alter *)&_hoops_IPRI->local_vertex_attributes;
	_hoops_RRCC *			_hoops_SRAIS;
	_hoops_RRCC *			_hoops_HAPAR;

	ZALLOC (_hoops_HAPAR, _hoops_RRCC);
	_hoops_ICAI(_hoops_HAPAR);

	_hoops_SRAIS = _hoops_HAPAR;

#ifndef DISABLE_TEXTURING
	if (BIT (nr->_hoops_IRR->_hoops_CSA,
			 (_hoops_GSRC & ~_hoops_AHGI)) &&
		(nr->_hoops_IHA->_hoops_CHA->_hoops_ARIR || 
		 nr->_hoops_IHA->_hoops_GIA->_hoops_ARIR)) {

		_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
		_hoops_HIR *		current = null;
		_hoops_RCR const *				texture = null;
		Param_Source				_hoops_PSR;
		int							_hoops_ARSIS = 0;
		bool 						_hoops_PRSIS = true;
		bool 						_hoops_HRSIS = false;
		bool 						_hoops_IRSIS = false;

		_hoops_HAPAR->_hoops_SASCC = true;
		if ((current = _hoops_SIGA->_hoops_CHA->_hoops_SCA) != null)
			texture = current->texture;

		if (!texture)
			texture = _hoops_SIGA->_hoops_CHA->texture[_hoops_HIA];
		if (!texture)
			texture = _hoops_SIGA->_hoops_CHA->texture[_hoops_IIA];
		if (!texture)
			texture = _hoops_SIGA->_hoops_CHA->texture[_hoops_ACA];
		if (!texture)
			texture = _hoops_SIGA->_hoops_CHA->texture[_hoops_HCA];
		if (!texture)
			texture = _hoops_SIGA->_hoops_CHA->texture[_hoops_PCA];

		if (!current)
			current = _hoops_SIGA->_hoops_GIA->_hoops_SCA;

		while (current || texture) {
			if (current) {
				texture = current->texture;
			}
			else {
				/* _hoops_AGIR _hoops_IH _hoops_CGPR _hoops_SR _hoops_SRPS _hoops_SPR _hoops_IIGR _hoops_RH _hoops_RSHAR->_hoops_PAAIS->_hoops_HH[_hoops_ASIGA] _hoops_GH _hoops_ARRS */
			}

			/* _hoops_HIAP _hoops_AGCR _hoops_HSH */
			_hoops_PRSIS = true;
			_hoops_HRSIS = false;
			_hoops_IRSIS = false;


			_hoops_HAPAR->_hoops_SCAI = _hoops_GSRSP;
			_hoops_HAPAR->_hoops_SASCC = true;
			_hoops_PSR = texture->_hoops_PSR;

			if (_hoops_PSR == HK_PS_UV &&
				_hoops_SPRI->_hoops_RSAPA == 0)
				_hoops_PSR = HK_PS_NATURAL_UV;

#ifndef DISABLE_EXTENDED_TEXTURE
			switch (_hoops_PSR) {
				case HK_PS_REFLECTION_VECTOR:
				case HK_PS_UV: {
					_hoops_PRSIS = true;

					if (_hoops_SPRI->_hoops_RSAPA) {
						if (!_hoops_SPRI->params || _hoops_SPRI->param_width != 2)
							HI_Initialize_Vertex_Attributes((Polyhedron alter*)_hoops_IPRI, _hoops_ASAPA, 2);
					}

					_hoops_HAPAR->_hoops_GSHA = _hoops_SPRI->param_width;
					_hoops_HAPAR->_hoops_SCAI |= _hoops_ASRSP | _hoops_HSRSP;
				} break;

				case HK_PS_WORLD: {
					if (!_hoops_SPRI->_hoops_PPHIR || _hoops_SPRI->_hoops_HPHIR != 3)
						HI_Initialize_Vertex_Attributes ((Polyhedron alter*)_hoops_IPRI, _hoops_CCCCC, 3);

					if (!ALLBITS (_hoops_SPRI->_hoops_SSCCC,_hoops_ASRSP|_hoops_SSRSP)) { 
						/* _hoops_PSCPR _hoops_IS _hoops_GSSC _hoops_PAPA*/
						_hoops_SPRI->_hoops_SSCCC = _hoops_SSRSP | _hoops_PSRSP;
					}

					_hoops_PRSIS = false;
					_hoops_HRSIS = true;

					_hoops_HAPAR->_hoops_GSHA = _hoops_SPRI->_hoops_HPHIR;
					_hoops_HAPAR->_hoops_SCAI |= _hoops_SPRI->_hoops_SSCCC | _hoops_ISRSP;
				}	break;
								
				case HK_PS_OBJECT: {
					_hoops_HAPAR->_hoops_CCHA = (_hoops_RSSH *)_hoops_IPRI->points;
					_hoops_HAPAR->_hoops_GSHA = 3;
					_hoops_HAPAR->_hoops_SCAI |= _hoops_ASRSP | _hoops_PGASP; 

					_hoops_PRSIS = false;
					_hoops_HRSIS = false;
				}	break;

				case HK_PS_SURFACE_NORMAL: {
					if (!_hoops_SPRI->_hoops_PPHIR || _hoops_SPRI->_hoops_HPHIR != 3)
						HI_Initialize_Vertex_Attributes ((Polyhedron alter*)_hoops_IPRI, _hoops_CCCCC, 3);

					if (!BIT(_hoops_SPRI->_hoops_SSCCC,_hoops_ASRSP) ||	 
						!BIT(_hoops_SPRI->_hoops_SSCCC,_hoops_GGASP)) { 
						/* _hoops_IPPRH _hoops_CCGR _hoops_ASGA _hoops_CHR _hoops_IAIAR */
						_hoops_SPRI->_hoops_SSCCC = _hoops_GGASP | _hoops_PSRSP;
					}

					_hoops_PRSIS = false;
					_hoops_HRSIS = true;

					_hoops_HAPAR->_hoops_CCHA = _hoops_SPRI->_hoops_PPHIR;
				}	break;

				case HK_PS_SPHERE: {
					if (!_hoops_SPRI->_hoops_PPHIR || (_hoops_SPRI->_hoops_HPHIR != 3))
						HI_Initialize_Vertex_Attributes ((Polyhedron alter*)_hoops_IPRI, _hoops_CCCCC, 3);

					if (!ALLBITS (_hoops_SPRI->_hoops_SSCCC,_hoops_ASRSP|_hoops_RGASP)) {
						Bounding const &	_hoops_RCHS = _hoops_IPRI->bounding;
						_hoops_RSSH *			params = _hoops_SPRI->_hoops_PPHIR;
						Point *				points = _hoops_IPRI->points;
						int					point_count = _hoops_IPRI->point_count;
						float				scale = 1.0f/180.0f;

						for (int i=0; i<point_count; i++) {

							int		offset = i*3;

							Vector	direction = points[i] - _hoops_RCHS->sphere.center;
							direction._hoops_AAIAR();

							if (Abs(direction.x) < 0.0001f && Abs(direction.z) < 0.0001f) 
								params[offset+0] = 0.0f;
							else
								params[offset+0] = scale * HI_ATan2(direction.x, direction.z);

							params[offset+1] =	scale * HI_ACos(direction.y);
							params[offset+2] =	0.0f;
						}

						_hoops_SPRI->_hoops_SSCCC = _hoops_ASRSP | _hoops_RGASP | _hoops_HPPAR; //_hoops_RGR _hoops_HRGR _hoops_IRS _hoops_HSRAP _hoops_CRSIS
					}

					_hoops_PRSIS = false;
					_hoops_HRSIS = true;
				}	break;

				case HK_PS_CYLINDER: {
					if (!_hoops_SPRI->_hoops_PPHIR || _hoops_SPRI->_hoops_HPHIR != 3)
						HI_Initialize_Vertex_Attributes ((Polyhedron alter*)_hoops_IPRI, _hoops_CCCCC, 3);

					if (!ALLBITS (_hoops_SPRI->_hoops_SSCCC, _hoops_ASRSP|_hoops_AGASP)) { 
						Bounding const &	_hoops_RCHS = _hoops_IPRI->bounding;
						_hoops_RSSH *			params = _hoops_SPRI->_hoops_PPHIR;
						Point *				points = _hoops_IPRI->points;
						int					point_count = _hoops_IPRI->point_count;
						
						float				scale = 1.0f/180.0f;
						float				_hoops_CGRPA = _hoops_IAAA(_hoops_RCHS->cuboid.min.y, _hoops_RCHS->sphere.center.y-_hoops_RCHS->sphere.radius);
						float				_hoops_SGRPA = _hoops_IAAA(_hoops_RCHS->cuboid.max.y, _hoops_RCHS->sphere.center.y+_hoops_RCHS->sphere.radius);
						float				_hoops_SRSIS = _hoops_SGRPA - _hoops_CGRPA;

						for (int i=0; i<point_count; i++) {
							int		offset = i*3;

							Vector	direction = points[i] - _hoops_RCHS->sphere.center;
							direction._hoops_AAIAR();

							if (Abs(direction.x) < 0.0001f && Abs(direction.z) < 0.0001f) 
								params[offset+0] = 0.0f;
							else
								params[offset+0] = scale * HI_ATan2(direction.x, direction.z);

							params[offset+1] =	(points[i].y - _hoops_CGRPA) / _hoops_SRSIS;
							params[offset+2] =	0.0f;
						}

						_hoops_SPRI->_hoops_SSCCC = _hoops_ASRSP | _hoops_AGASP | _hoops_HPPAR;
					}
					_hoops_PRSIS = false;
					_hoops_HRSIS = true;
				}	break;

				case HK_PS_NATURAL_UV: {
					if (!_hoops_SPRI->_hoops_IPHIR) {
						float			u,v;
						int				i,j;
						_hoops_RSSH *		_hoops_APHCP;

						ALLOC_ARRAY (_hoops_SPRI->_hoops_IPHIR,
									 2*(_hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR), _hoops_RSSH);

						_hoops_APHCP = _hoops_SPRI->_hoops_IPHIR;
						if (_hoops_IPRI->type == _hoops_GSIP) {
							_hoops_AIHPR const *		_hoops_PIHPR = (_hoops_AIHPR const *)_hoops_IPRI;

							for (j = 0; j < _hoops_PIHPR->rows; j++) {
								v = (float)j / (_hoops_PIHPR->rows - 1);

								for (i = 0; i < _hoops_PIHPR->columns; i++) {
									u = (float)i / (_hoops_PIHPR->columns - 1);

									*_hoops_APHCP++ = u;
									*_hoops_APHCP++ = v;
								}
							}
						}
						else { 
							Bounding const &		_hoops_RCHS = _hoops_IPRI->bounding;
							float					_hoops_PSPHH;

							/* _hoops_CAHA _hoops_RH _hoops_GASIS _hoops_GIRA _hoops_IGIAR _hoops_HII _hoops_SPR _hoops_RPIA _hoops_IS _hoops_RH _hoops_RII _hoops_IGIAR
								_hoops_RH _hoops_IPPA _hoops_IIAAR _hoops_RH _hoops_CPIS _hoops_PGCR _hoops_HAARR _hoops_IIGR _hoops_RH _hoops_IPIS */
							Vector _hoops_RPIS = _hoops_RCHS->cuboid.max - _hoops_RCHS->cuboid.min;

							if (_hoops_RPIS.x > _hoops_RPIS.y) {
								_hoops_PSPHH = _hoops_RPIS.x;
								if (_hoops_RPIS.y > _hoops_RPIS.z)
									_hoops_PSPHH += _hoops_RPIS.y;
								else
									_hoops_PSPHH += _hoops_RPIS.z;
							}
							else {
								_hoops_PSPHH = _hoops_RPIS.y;
								if (_hoops_RPIS.x > _hoops_RPIS.z)
									_hoops_PSPHH += _hoops_RPIS.x;
								else
									_hoops_PSPHH += _hoops_RPIS.z;
							}

							for (i = 0; i < _hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR; i++) {
								Vector _hoops_ARGCR = _hoops_IPRI->points[i] - _hoops_RCHS->cuboid.min;
								u = (_hoops_ARGCR.x + _hoops_ARGCR.z) / _hoops_PSPHH;
								v = (_hoops_ARGCR.x + _hoops_ARGCR.y) / _hoops_PSPHH;
								*_hoops_APHCP++ = u;
								*_hoops_APHCP++ = v;
							}
						}
					}

					_hoops_PRSIS = false;
					_hoops_HRSIS = false;
					_hoops_IRSIS = true;
				}	break;

				case HK_PS_UNSPECIFIED: {
					_hoops_HAPAR->_hoops_CCHA = _hoops_SPRI->params;
					_hoops_HAPAR->_hoops_GSHA = _hoops_SPRI->param_width;
					_hoops_HAPAR->_hoops_SCAI |= _hoops_ASRSP | _hoops_HSRSP;

				}	break;

				default: break;
			}
#endif
		

			if (_hoops_PRSIS) {
				_hoops_HAPAR->_hoops_CCHA = _hoops_SPRI->params;
				_hoops_HAPAR->_hoops_GSHA = _hoops_SPRI->param_width;
				_hoops_HAPAR->_hoops_SCAI |= _hoops_ASRSP | _hoops_HSRSP;
			}
			else if (_hoops_HRSIS) {
				_hoops_HAPAR->_hoops_CCHA = _hoops_SPRI->_hoops_PPHIR;
				_hoops_HAPAR->_hoops_GSHA = _hoops_SPRI->_hoops_HPHIR;
				_hoops_HAPAR->_hoops_SCAI = _hoops_SPRI->_hoops_SSCCC | _hoops_ISRSP;
			}
			else if (_hoops_IRSIS) {
				_hoops_HAPAR->_hoops_SCAI |= _hoops_HGASP;
				_hoops_HAPAR->_hoops_CCHA = _hoops_SPRI->_hoops_IPHIR;
				_hoops_HAPAR->_hoops_GSHA = 2;
			} 
			else {
				_hoops_HAPAR->_hoops_SCAI |= _hoops_CSRSP;
			}

			if (current) {
				texture = null;
				current = current->next;
				if (current) {
					ZALLOC (_hoops_HAPAR->next, _hoops_RRCC);
					_hoops_ICAI (_hoops_HAPAR->next);
					_hoops_HAPAR = _hoops_HAPAR->next;
				}
			}
			else {
				texture = null;
				break;
			}

			_hoops_ARSIS++;
		}
	}
#ifdef _hoops_GCGGC
	else {
		// _hoops_RASIS - _hoops_AIAP _hoops_GRAR _hoops_AASIS
		// _hoops_SGGGR _hoops_RGR _hoops_IPSP _hoops_CIHA _hoops_IS _hoops_GII _hoops_GRAA-_hoops_AHHR _hoops_PIRA _hoops_GRS _hoops_HHSA _hoops_IRISR _hoops_IS _hoops_SHR
		// _hoops_HSPAA _hoops_RH _hoops_HH _hoops_PCRR _hoops_ARHI, _hoops_PRGI _hoops_RPP _hoops_IIH _hoops_HRGR _hoops_PSP _hoops_RIHRR _hoops_HH.
		if (HD_Show_User_Index(nr, 'EFTC') != 0) {
			if (_hoops_SPRI->params) {
				_hoops_HAPAR->_hoops_CCHA = _hoops_SPRI->params;
				_hoops_HAPAR->_hoops_GSHA = _hoops_SPRI->param_width;
				_hoops_HAPAR->_hoops_SCAI |= _hoops_ASRSP | _hoops_HSRSP;
			}
			_hoops_HAPAR->_hoops_SPGRC = true;
		}
	}
#endif
#endif

	return _hoops_SRAIS;
}



local Net_Rendition _hoops_PASIS (
	Polyhedron const *				_hoops_IPRI,
	Net_Rendition const & 			_hoops_SGIIH,
	Net_Rendition const & 			_hoops_IAIIH,
	_hoops_PSGHR const *	_hoops_HPHCR) {
	Net_Rendition					nr = _hoops_SGIIH;
	_hoops_ICP const &		_hoops_HASIS = _hoops_IAIIH->_hoops_GSP;
	_hoops_HHAGP					_hoops_RAIIP = _hoops_SGIIH->_hoops_IRR->locks._hoops_IPPGR;
	_hoops_ICP alter &		_hoops_RRGH = nr.Modify()->_hoops_GSP.Modify();
	_hoops_ICP alter &		_hoops_CCP = nr.Modify()->_hoops_SCP.Modify();

	_hoops_RRGH->_hoops_CHA = _hoops_CCP->_hoops_CHA;

	if (!BIT (_hoops_HPHCR->flags, _hoops_SIICA) ||
		BIT (_hoops_RAIIP, 1L << HK_MARKER_SYMBOL)) {
		_hoops_RRGH->glyph = _hoops_CCP->glyph = _hoops_HASIS->glyph;
	}
	else {
		_hoops_RPHIR	*		sl;
		_hoops_GASC				glyph;

		sl = HI_LVA_Symbol_Lookup(_hoops_IPRI, _hoops_HPHCR->glyph_symbol);
		for (int i=0; i<nr->glyph_rendition->count; ++i) {
			if (nr->glyph_rendition->keys[i] == sl->key &&
				_hoops_RAHSR(sl->name, nr->glyph_rendition->glyphs[i]->name)) {
				glyph = nr->glyph_rendition->glyphs[i];
				break;
			}
		}
		if (!glyph) {
			HE_WARNING (HEC_MARKER, HES_NOT_AVAILABLE,
						Sprintf_N (null, "Requested marker '%n' not found", &sl->name));
			_hoops_RRGH->glyph = _hoops_CCP->glyph = _hoops_HASIS->glyph;
		}
		else {
			_hoops_RRGH->glyph = _hoops_CCP->glyph = glyph;
		}
	}

	if (!BIT (_hoops_HPHCR->flags, _hoops_GCICA) ||
		BIT (_hoops_RAIIP, 1L << HK_MARKER_SIZE)) {
		_hoops_RRGH->_hoops_RGRS = _hoops_CCP->_hoops_RGRS = _hoops_HASIS->_hoops_RGRS;
		_hoops_RRGH->ysize = _hoops_CCP->ysize = _hoops_HASIS->ysize;
	}
	else {
		Display_Context const *	dc = nr->_hoops_SRA;
		float					size;

		size = _hoops_HPHCR->size * _hoops_RRRIP * dc->current._hoops_PRPSR.y;
		_hoops_RRGH->_hoops_RGRS = _hoops_CCP->_hoops_RGRS = size * dc->current._hoops_AGRS;
		_hoops_RRGH->ysize = _hoops_CCP->ysize = size;
	}

	_hoops_RRGH->_hoops_CSRS = _hoops_CCP->_hoops_CSRS;

	return nr;
}



local void _hoops_IASIS (
	Net_Rendition const & 		nr,
	Line_Rendition alter &		_hoops_HC,
	_hoops_HHA alter &	matr,
	_hoops_IAHPR const *	_hoops_HPHCR) {
	Display_Context const *		dc = nr->_hoops_SRA;

	_hoops_HC->color = _hoops_CAHSR::_hoops_SAHSR;

#ifndef DISABLE_COLOR_MAPS
	if (BIT (_hoops_HPHCR->flags, _hoops_RPGI)) {
		if (_hoops_HPHCR->findex == (int) _hoops_HPHCR->findex) {
			_hoops_CAHHP const &		_hoops_SAHHP = nr->_hoops_ASIR->_hoops_PSIR;
			int								index = ((int) _hoops_HPHCR->findex) % ((int) _hoops_SAHHP->length);

			if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR)
				_hoops_HC->color._hoops_PGGCR = _hoops_SAHHP->_hoops_RHHHP + index;
			else
				_hoops_HC->color = _hoops_SAHHP->_hoops_AHHHP[index];

			matr->_hoops_CSHR = _hoops_SAHHP->_hoops_CSIR->_hoops_HAA[index]._hoops_CSHR;

//			_hoops_ASRC;
		}
		else {					/* _hoops_PSHII _hoops_CIHA _hoops_GPRI - _hoops_AA _hoops_RPIHR _hoops_PSHA */
			_hoops_RHAH const *	_hoops_CSIR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR;
			bool				_hoops_SIAIS;

			if (BIT (_hoops_HPHCR->flags, _hoops_IPACP))
				_hoops_SIAIS =
					ALLBITS (nr->_hoops_IRR->_hoops_CSA,
							 ((_hoops_HIRC |
							   _hoops_PHGI) & ~_hoops_AHGI));
			else
				_hoops_SIAIS =
					ALLBITS (nr->_hoops_IRR->_hoops_CSA,
							 ((_hoops_SSRC |
							   _hoops_CSRC) & ~_hoops_AHGI));

			if (_hoops_CSIR->length == 0) {
				HD_Report_Null_Color_Map ("polyedge", _hoops_CSIR);
				matr->_hoops_CSHR = _hoops_GPSR::_hoops_RPSR;
			}
			else {
				_hoops_AHAH 		_hoops_SHAIS;
				_hoops_ICRCP (_hoops_CSIR, _hoops_HPHCR->findex, matr->_hoops_CSHR, _hoops_SIAIS, _hoops_SHAIS);
			}
		}
	}
	else
#endif
	{					/* _hoops_CARRI _hoops_CASIS */
		matr->_hoops_CSHR = _hoops_HPHCR->color;
	}

	_hoops_AHAH const &				_hoops_PHAH = nr->_hoops_ARA->_hoops_IHRH;

	if (BIT (_hoops_PHAH.options, _hoops_CHRH)) 
		matr->_hoops_CSHR = HD_Apply_Color_Effects (matr->_hoops_CSHR, _hoops_PHAH);

	if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
		RGBAS32			_hoops_SASIS = _hoops_HC->_hoops_CHA->_hoops_CSHR;
		_hoops_GARSR		colors[4 + 1];
		int				_hoops_AHHIR[3 + 1];

		(void) HD_Find_Dither_Pattern (nr, &_hoops_SASIS, colors, _hoops_AHHIR);

		/* _hoops_SR _hoops_PAH _hoops_RGAR _hoops_IPHAI _hoops_SPR _hoops_HAIR, _hoops_GPSIS */
		_hoops_HC->color._hoops_PGGCR = colors[0];
	}
	else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR) {
		float tmp;

		tmp = (float)dc->_hoops_PGCC._hoops_PCHSR - 0.01f;

		_hoops_HC->color._hoops_HRIR.r =
			0xFF & (int) (_hoops_HC->_hoops_CHA->_hoops_CSHR.red * tmp);
		_hoops_HC->color._hoops_HRIR.g =
			0xFF & (int) (_hoops_HC->_hoops_CHA->_hoops_CSHR.green * tmp);
		_hoops_HC->color._hoops_HRIR.b =
			0xFF & (int) (_hoops_HC->_hoops_CHA->_hoops_CSHR.blue * tmp);
		_hoops_HC->color._hoops_HRIR.a = _hoops_GPGCR;
	}
	else {						/* _hoops_AIHHP */
		_hoops_HC->color._hoops_PIHHP = (Integer32)
			(_hoops_HC->_hoops_CHA->_hoops_CSHR._hoops_CPIR() *
			 ((float)dc->_hoops_PGCC._hoops_PCHSR - 0.01f));
	}
}


GLOBAL_FUNCTION Net_Rendition HD_New_Local_Edge_Rendition (
	Polyhedron	 alter *			_hoops_IPRI,
	Net_Rendition const & 			_hoops_SGIIH,
	Net_Rendition const & 			_hoops_IAIIH,
	_hoops_IAHPR const *		_hoops_HPHCR) {
	Net_Rendition					nr = _hoops_SGIIH;
	Line_Rendition const &			_hoops_RPSIS = _hoops_IAIIH->_hoops_RHP;
	_hoops_HHAGP					_hoops_RAIIP = _hoops_SGIIH->_hoops_IRR->locks._hoops_IPPGR;
	_hoops_IAHPR				_hoops_APSIS = *_hoops_HPHCR;
	_hoops_IAHPR const *		_hoops_PPSIS = _hoops_HPHCR;
	_hoops_PSIHP				_hoops_HSIHP;
	Line_Rendition alter &			_hoops_GHP = nr.Modify()->_hoops_RHP.Modify();
	_hoops_HHA alter &		mat = _hoops_GHP->_hoops_CHA.Modify();


	bool	_hoops_HPSIS = BIT (_hoops_RAIIP, 1L << HK_EDGE_WEIGHT);

	if (BIT (_hoops_HPHCR->flags, _hoops_IPACP)) {
		_hoops_GRA const &	_hoops_RRA = _hoops_IAIIH->_hoops_ARA;

		_hoops_PPSIS = &_hoops_APSIS;

		if (_hoops_RRA->_hoops_ACP._hoops_ACAIR != null) {
			int						index = _hoops_HPHCR->_hoops_CPACP % _hoops_RRA->_hoops_ACP._hoops_RCAIR;
			_hoops_HCRPR const &			pattern = _hoops_RRA->_hoops_ACP._hoops_ACAIR[index];

			if (pattern.length == 0) {
				_hoops_HPSIS = true;	// _hoops_HHSA _hoops_CAPGP
			}
			else {
				_hoops_ISAIR		_hoops_CSAIR;

				ZERO_STRUCT (&_hoops_CSAIR, _hoops_ISAIR);
				_hoops_CSAIR.type = HK_EDGE_PATTERN;

				HI_Canonize_Line_Pattern (pattern.text, &_hoops_CSAIR.line_style, &_hoops_CSAIR.value);
				_hoops_HCARA(_hoops_CSAIR.line_style, _hoops_CSAIR._hoops_SCCAP);

				HD_Downwind_Rendition (nr, &_hoops_CSAIR, T_EDGES, false);

				_hoops_APSIS.flags |= _hoops_GPGI;
				_hoops_RGAIR(_hoops_CSAIR.line_style);
			}
		}
		else {
			_hoops_HPSIS = true;	// _hoops_HHSA _hoops_CAPGP
		}
	}

	if (!BIT (_hoops_PPSIS->flags, _hoops_GPGI) || _hoops_HPSIS) {
		_hoops_GHP->line_style = _hoops_RPSIS->line_style;
	}
	else if (!BIT (_hoops_HPHCR->flags, _hoops_IPACP)) {
		_hoops_HHHIR *		_hoops_IHHIR;
		Line_Style			line_style;

		_hoops_IHHIR = HI_LEA_Pattern_Lookup(_hoops_IPRI, _hoops_HPHCR->pattern);
		for (int i=0; i<nr->_hoops_GCSHP->count; i++) {
			if (nr->_hoops_GCSHP->keys[i] == _hoops_IHHIR->key &&
				_hoops_RAHSR(_hoops_IHHIR->name, nr->_hoops_GCSHP->_hoops_HPAIR[i]->name)) {
				line_style = nr->_hoops_GCSHP->_hoops_HPAIR[i];
				break;
			}
		}
		if (!line_style) {
			HE_WARNING (HEC_MARKER, HES_NOT_AVAILABLE,
				Sprintf_N (null, "Requested line pattern '%n' not found", &_hoops_IHHIR->name));
			_hoops_GHP->line_style = _hoops_RPSIS->line_style;
		}
		else {
			_hoops_GHP->line_style = line_style;
		}
	}

	_hoops_GHP->style = LCAP_ROUND|LJOIN_ROUND;



	bool	_hoops_IPSIS = BIT (_hoops_RAIIP, 1L << HK_EDGE_WEIGHT);

	if (BIT (_hoops_HPHCR->flags, _hoops_IPACP)) {
		_hoops_GRA const &	_hoops_RRA = _hoops_IAIIH->_hoops_ARA;

		_hoops_PPSIS = &_hoops_APSIS;

		if (_hoops_RRA->_hoops_ACP.weights != null) {
			int						index = _hoops_HPHCR->_hoops_CPACP % _hoops_RRA->_hoops_ACP.weight_count;
			_hoops_HCAIR const &	weight = _hoops_RRA->_hoops_ACP.weights[index];

			if (weight._hoops_HHP == -1) {
				_hoops_IPSIS = true;	// _hoops_HHSA _hoops_CAPGP
			}
			else {
				_hoops_RHCAP			_hoops_PSGIP;

				ZERO_STRUCT (&_hoops_PSGIP, _hoops_RHCAP);
				_hoops_PSGIP.type = HK_EDGE_WEIGHT;
				_hoops_PSGIP.data.value = weight.value;
				_hoops_PSGIP.data._hoops_HHP = weight._hoops_HHP;

				HD_Downwind_Rendition (nr, &_hoops_PSGIP, T_EDGES, false);

				_hoops_APSIS.flags |= _hoops_SCICA;
			}
		}
		else {
			_hoops_IPSIS = true;	// _hoops_HHSA _hoops_CAPGP
		}
	}

	if (!BIT (_hoops_PPSIS->flags, _hoops_SCICA) || _hoops_IPSIS)
		_hoops_GHP->weight = _hoops_RPSIS->weight;
	else if (!BIT (_hoops_HPHCR->flags, _hoops_IPACP))
		_hoops_GHP->weight = (int)_hoops_HPHCR->weight * nr->_hoops_SRA->_hoops_PGCC._hoops_IHHSR;



	bool	_hoops_SPGI = BIT (_hoops_SGIIH->_hoops_IRR->locks.color, Color_EDGE) &&
							 BIT (_hoops_SGIIH->_hoops_IRR->locks._hoops_HAA[_hoops_SAA], M_DIFFUSE);

	if (BIT (_hoops_HPHCR->flags, _hoops_IPACP)) {
		_hoops_GRA const &	_hoops_RRA = _hoops_IAIIH->_hoops_ARA;

		_hoops_PPSIS = &_hoops_APSIS;

		if (_hoops_RRA->_hoops_ACP.colors != null) {
			int						index = _hoops_HPHCR->_hoops_CPACP % _hoops_RRA->_hoops_ACP._hoops_GCAIR;
			RGB const &				color = _hoops_RRA->_hoops_ACP.colors[index];

			if (color.red == -1.0f) {
				_hoops_SPGI = true;	// _hoops_HHSA _hoops_CAPGP
			}
			else if (color.red == -2.0) {
				_hoops_APSIS.flags &= ~_hoops_CCICA;
				_hoops_APSIS.flags |= _hoops_RPGI;
			}
			else {
				_hoops_APSIS.flags &= ~_hoops_CCICA;
				_hoops_APSIS.flags |= _hoops_SSRRA;
				_hoops_APSIS.color = color;
			}
		}
		else {
			_hoops_APSIS.flags &= ~_hoops_CCICA;
			_hoops_APSIS.flags |= _hoops_RPGI;
		}
	}

	if (!ANYBIT (_hoops_PPSIS->flags, _hoops_CCICA) || _hoops_SPGI) {
		_hoops_GHP->color = _hoops_RPSIS->color;
		_hoops_GHP->_hoops_CHA = _hoops_RPSIS->_hoops_CHA;
	}
	else {
		_hoops_IASIS (nr, _hoops_GHP, mat, _hoops_PPSIS);
	}

	_hoops_GHP->_hoops_IHA = null;
	_hoops_GHP->_hoops_SSHHP = null;
	_hoops_GHP->contrast_rendition = null;



	/* _hoops_GAAP _hoops_HS _hoops_IS _hoops_HPSI _hoops_CCA _hoops_PGSI */
	_hoops_HSIHP = nr->_hoops_RSGC;
	if (_hoops_HSIHP->action.draw_dc_polyline != _hoops_HSIHP->action.draw_dc_edge) {
		_hoops_HSIHP = nr.Modify()->_hoops_RSGC.Modify();

		_hoops_HSIHP->action.draw_dc_polyline = _hoops_HSIHP->action.draw_dc_edge;
	}

	nr->_hoops_AHP = _hoops_GHP;

	return nr;
}



local bool _hoops_CPSIS (
	Net_Rendition alter & 		nr,
	_hoops_CIGA alter &		_hoops_SIGA,
	_hoops_HHA alter &	matr,
	One_Face_Attributes const *	_hoops_HPHCR) {
	Display_Context const *		dc = nr->_hoops_SRA;

	_hoops_SIGA->color = _hoops_CAHSR::_hoops_SAHSR;

#ifndef DISABLE_COLOR_MAPS
	if (BIT (_hoops_HPHCR->flags, LFA_EXPLICIT_COLOR_BY_FINDEX)) {
		if (_hoops_HPHCR->findex == (int) _hoops_HPHCR->findex) {
			Display_Context alter *		_hoops_AAHCP = (Display_Context alter *)nr->_hoops_SRA;
			_hoops_CAHHP const &	_hoops_SAHHP = nr->_hoops_ASIR->_hoops_PSIR;
			_hoops_SSGI						color;
			_hoops_PCSGA				list;
			bool						_hoops_SPSIS = dc->options._hoops_RAHHP;
			bool						_hoops_GHSIS = false;

			ZERO_STRUCT (&list, _hoops_PCSGA);
			list.type = _hoops_SHGRA;
			list._hoops_GHA = Color_FACE;
			list.value = (float)((int)_hoops_HPHCR->findex % (int)_hoops_SAHHP->length);

			ZERO_STRUCT (&color, _hoops_SSGI);
			color.type = HK_COLOR;
			color._hoops_GHA = color._hoops_CCCIR = Color_FACE;
			color.colors = &list;

			_hoops_AAHCP->options._hoops_RAHHP = false;
			HD_Downwind_Color (nr, &color, T_FACES, &nr->_hoops_IRR->locks);
			_hoops_AAHCP->options._hoops_RAHHP = _hoops_SPSIS;

			if (BIT (_hoops_SAHHP->_hoops_CSIR->_hoops_HAA[(int)list.value]._hoops_PRGRA, M_TRANSMISSION) &&
				!BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_IAA], M_TRANSMISSION))
				_hoops_GHSIS = true;

			return _hoops_GHSIS;
		}
		else {					/* _hoops_PSHII _hoops_CIHA _hoops_GPRI - _hoops_AA _hoops_RPIHR _hoops_PSHA */
			_hoops_RHAH const *_hoops_CSIR;
			bool _hoops_SIAIS;

			_hoops_SIAIS =
				ALLBITS (nr->_hoops_IRR->_hoops_CSA,
						 ((_hoops_HIRC |
						   _hoops_PHGI) & ~_hoops_AHGI));

			_hoops_CSIR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR;

			if (_hoops_CSIR->length == 0) {
				HD_Report_Null_Color_Map ("shell", _hoops_CSIR);
				matr->_hoops_CSHR.red =
					matr->_hoops_CSHR.green = 
						matr->_hoops_CSHR.blue = 0.0f;
			}
			else {
				_hoops_AHAH 		_hoops_SHAIS;
				_hoops_ICRCP (_hoops_CSIR, _hoops_HPHCR->findex, matr->_hoops_CSHR, _hoops_SIAIS, _hoops_SHAIS);
			}
		}
	}
	else
#endif
	{					/* _hoops_CARRI _hoops_CASIS */
		matr->_hoops_CSHR = _hoops_HPHCR->color;
	}

	_hoops_AHAH const &				_hoops_PHAH = nr->_hoops_ARA->_hoops_IHRH;

	if (BIT (_hoops_PHAH.options, _hoops_CHRH)) 
		matr->_hoops_CSHR = HD_Apply_Color_Effects (matr->_hoops_CSHR, _hoops_PHAH);

	if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
		RGBAS32			_hoops_SASIS = _hoops_SIGA->_hoops_CHA->_hoops_CSHR;
		_hoops_GARSR		colors[4 + 1];
		int				_hoops_AHHIR[3 + 1];
		int				_hoops_GCAIR;

		_hoops_GCAIR = HD_Find_Dither_Pattern (nr, &_hoops_SASIS, colors, _hoops_AHHIR);

		if (_hoops_SIGA->pattern != FP_SOLID || _hoops_GCAIR == 1) {
			/* _hoops_SR _hoops_PAH _hoops_RGAR _hoops_HHSHH _hoops_SPR _hoops_HAIR, _hoops_GPSIS */
			_hoops_SIGA->color._hoops_PGGCR = colors[0];
		}
		else {
			/* _hoops_SR _hoops_PAH _hoops_AA _hoops_PGCR _hoops_IIGR _hoops_RH _hoops_PSHA */
			/* _hoops_SAHR _hoops_RHSIS _hoops_RH 3_hoops_IAPPA _hoops_PPR 4_hoops_CRISR _hoops_PSHA _hoops_HRGR _hoops_IRS _hoops_RSCA _hoops_ISPC */
			_hoops_SIGA->color._hoops_PGGCR = colors[0];
			_hoops_SIGA->contrast_color._hoops_PGGCR = colors[1];
			_hoops_SIGA->pattern = _hoops_AHHIR[0];
		}
	}
	else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR) {
		float			tmp;

		tmp = (float)dc->_hoops_PGCC._hoops_PCHSR - 0.01f;

		_hoops_SIGA->color._hoops_HRIR.r =
			0xFF & (int) (_hoops_SIGA->_hoops_CHA->_hoops_CSHR.red * tmp);
		_hoops_SIGA->color._hoops_HRIR.g =
			0xFF & (int) (_hoops_SIGA->_hoops_CHA->_hoops_CSHR.green * tmp);
		_hoops_SIGA->color._hoops_HRIR.b =
			0xFF & (int) (_hoops_SIGA->_hoops_CHA->_hoops_CSHR.blue * tmp);
		_hoops_SIGA->color._hoops_HRIR.a = _hoops_GPGCR;
	}
	else {						/* _hoops_AIHHP */
		_hoops_SIGA->color._hoops_PIHHP = (Integer32)
			(_hoops_SIGA->_hoops_CHA->_hoops_CSHR._hoops_CPIR() *
			 ((float)dc->_hoops_PGCC._hoops_PCHSR - 0.01f));
	}
	_hoops_SIGA->_hoops_RGIR = _hoops_SIGA->color;

	return false;
}



local void _hoops_AHSIS (
	Net_Rendition alter & 		nr,
	One_Face_Attributes const *	_hoops_HPHCR) {
	_hoops_HHAGP				_hoops_RAIIP = nr->_hoops_IRR->locks._hoops_IPPGR;
	bool						_hoops_SPGI;

	_hoops_SPGI = BIT (nr->_hoops_IRR->locks.color, Color_FRONT) &&
					 BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_IAA], M_DIFFUSE);

	_hoops_CIGA alter &		_hoops_SIGA = nr.Modify()->_hoops_IHA.Modify();
	_hoops_HHA alter &	mat = _hoops_SIGA->_hoops_CHA.Modify();
	_hoops_SIGA->_hoops_GIA = mat;

	if (BIT (_hoops_HPHCR->flags, _hoops_HAGI) &&
		!BIT (_hoops_RAIIP, 1L << HK_FACE_PATTERN))
		_hoops_SIGA->pattern = _hoops_HPHCR->pattern;

	if (ANYBIT (_hoops_HPHCR->flags, _hoops_IACHR) && !_hoops_SPGI) {
		if (_hoops_CPSIS (nr, _hoops_SIGA, mat, _hoops_HPHCR) &&
			nr->_hoops_CPP->_hoops_PRH.style == _hoops_GCPI) {
			HD_Setup_Screen_Door (nr);
		}
	}
}

local void _hoops_PHSIS (
	Net_Rendition const &			nr,
	Polyedge alter *				pe,
	Local_Vertex_Attributes const * _hoops_SPRI) {
	RGB								_hoops_HHSIS;
	RGB alter *						_hoops_IHSIS;
	Local_Vertex_Flags const *		flags;
	int								_hoops_PHHA = pe->_hoops_PHHA;
	int const *						lengths = pe->lengths;
	int const *						vi = pe->_hoops_AIHA;
	int								length;
	int								vertex;

	/* _hoops_SSS _hoops_RH _hoops_SCGR _hoops_ISHA _hoops_HAIR */
#ifndef DISABLE_COLOR_MAPS
	if (BIT (pe->_hoops_PPGI.flags, _hoops_RPGI)) {
		_hoops_RHAH const *		_hoops_CSIR;
		bool					_hoops_SIAIS;
		_hoops_GRGH const &	_hoops_RRGH = nr->_hoops_IRR;

		_hoops_SIAIS = ALLBITS (_hoops_RRGH->_hoops_CSA,
									 ((_hoops_SSRC |
									   _hoops_CSRC) & ~_hoops_AHGI));

		_hoops_CSIR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR;

		if (_hoops_CSIR->length == 0) {
			HD_Report_Null_Color_Map ("polyedge", _hoops_CSIR);
			_hoops_HHSIS = _hoops_GPSR::_hoops_RPSR;
		}
		else {
			_hoops_AHAH 		_hoops_SHAIS;
			_hoops_ICRCP (_hoops_CSIR,
						   pe->_hoops_PPGI.findex,
						   _hoops_HHSIS, _hoops_SIAIS, _hoops_SHAIS);
		}
	}
	else						/* _hoops_CHSIS */
#endif
		_hoops_HHSIS = pe->_hoops_PPGI.color;

	_hoops_AHAH const &				_hoops_PHAH = nr->_hoops_ARA->_hoops_IHRH;

	if (BIT (_hoops_PHAH.options, _hoops_CHRH)) 
		_hoops_HHSIS = HD_Apply_Color_Effects (_hoops_HHSIS, _hoops_PHAH);

	flags = _hoops_SPRI->flags;
	_hoops_IHSIS = pe->_hoops_PCHA;

	while (_hoops_PHHA-- > 0) {
		length = *lengths++;

		while (length-- > 0) {
			vertex = *vi++;

			if (!ANYBIT (flags[vertex], _hoops_PPPRA))
				_hoops_IHSIS[vertex] = _hoops_HHSIS;
		}
	}
}

local void _hoops_SHSIS (
	Net_Rendition const &			nr,
	Tristrip  *						ts,
	Local_Vertex_Attributes const *	_hoops_SPRI) {
	RGB								_hoops_RSISR;
	RGB alter *						_hoops_IHSIS;
	Local_Vertex_Flags const *		flags;
	int								_hoops_PHHA = ts->_hoops_PHHA;
	int const *						lengths = ts->lengths;
	int const *						vi = ts->_hoops_AIHA;
	int								length;
	int								vertex;

	/* _hoops_SSS _hoops_RH _hoops_SCGR _hoops_HSP _hoops_HAIR */
#ifndef DISABLE_COLOR_MAPS
	if (BIT (ts->face_attributes.flags, LFA_EXPLICIT_COLOR_BY_FINDEX)) {
		_hoops_RHAH const *		_hoops_CSIR;
		bool					_hoops_SIAIS;
		_hoops_GRGH const &	_hoops_RRGH = nr->_hoops_IRR;

		_hoops_SIAIS = ALLBITS (_hoops_RRGH->_hoops_CSA,
									 ((_hoops_HIRC |
									   _hoops_PHGI) & ~_hoops_AHGI));

		_hoops_CSIR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR;

		if (_hoops_CSIR->length == 0) {
			HD_Report_Null_Color_Map ("tristrip", _hoops_CSIR);
			_hoops_RSISR = _hoops_GPSR::_hoops_RPSR;
		}
		else {
			_hoops_AHAH 		_hoops_SHAIS;
			_hoops_ICRCP (_hoops_CSIR,
						   ts->face_attributes.findex,
						   _hoops_RSISR, _hoops_SIAIS, _hoops_SHAIS);
		}
	}
	else						/* _hoops_GISIS */
#endif
		_hoops_RSISR = ts->face_attributes.color;

	_hoops_AHAH const &				_hoops_PHAH = nr->_hoops_ARA->_hoops_IHRH;

	if (BIT (_hoops_PHAH.options, _hoops_CHRH)) 
		_hoops_RSISR = HD_Apply_Color_Effects (_hoops_RSISR, _hoops_PHAH);

	flags = _hoops_SPRI->flags;
	_hoops_IHSIS = ts->_hoops_PCHA;

	while (_hoops_PHHA-- > 0) {
		length = *lengths++;
		if (length < 0)			/* _hoops_HAHCP */
			length = -length;

		while (length-- > 0) {
			vertex = *vi++;

			if (flags) {
				if (!ANYBIT (flags[vertex], _hoops_HPPRA))
					_hoops_IHSIS[vertex] = _hoops_RSISR;
			}
			else {
				if (!ANYBIT (_hoops_SPRI->_hoops_SGRHR, _hoops_HPPRA))
					_hoops_IHSIS[vertex] = _hoops_RSISR;
			}

		}
	}
}

local RGB * _hoops_PHACP (
	Net_Rendition const & 			nr,
	Tristrip *						ts,
	Local_Vertex_Attributes const *	_hoops_SPRI) {
	Display_Context *				dc = (Display_Context *)nr->_hoops_SRA;
	Local_Vertex_Flags  *		flags;
	_hoops_ACGHR const *		_hoops_HHACP;
	RGB const *						_hoops_HCPGS;
	RGB alter *						vcolors;
	int								remaining;
	_hoops_RHAH const *				_hoops_CSIR;
	RGB								_hoops_RSISR = _hoops_GPSR::_hoops_RPSR;
	bool							_hoops_SIAIS;

	_hoops_SIAIS = ALLBITS (nr->_hoops_IRR->_hoops_CSA,
								 ((_hoops_HIRC |
								   _hoops_PHGI) & ~_hoops_AHGI));

	/*_hoops_IIRRA = &_hoops_CPHAR->_hoops_SPSSI;*/

	flags = ((Local_Vertex_Attributes*) _hoops_SPRI)->_hoops_CHHPR();
	_hoops_HHACP = _hoops_SPRI->_hoops_IGHIR;
	_hoops_HCPGS = _hoops_SPRI->fcolors;
	remaining = ts->point_count;

	if ((vcolors = dc->_hoops_SSPGH) == null || dc->_hoops_GGHGH < remaining) {
		if (vcolors != null)
			FREE_ARRAY (vcolors, dc->_hoops_GGHGH, RGB);
		POOL_ALLOC_ARRAY (vcolors, remaining, RGB, dc->memory_pool);
		dc->_hoops_SSPGH = vcolors;
		dc->_hoops_GGHGH = remaining;
	}
	ts->_hoops_PCHA = vcolors;


	if (_hoops_SPRI->_hoops_SIRHR +
		_hoops_SPRI->_hoops_RCRHR < ts->point_count)
		_hoops_RSISR = nr->_hoops_IHA->_hoops_CHA->_hoops_CSHR;

	_hoops_CSIR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR;

	_hoops_AHAH const &				_hoops_PHAH = nr->_hoops_ARA->_hoops_IHRH;
	_hoops_AHAH 					_hoops_SHAIS;

	do {
#ifndef DISABLE_COLOR_MAPS
		if (BIT (*flags, _hoops_HARHR)) {
			if (_hoops_CSIR->length == 0) {
				HD_Report_Null_Color_Map ("tristrip", _hoops_CSIR);
				*vcolors = _hoops_GPSR::_hoops_RPSR;
			}
			else {
				_hoops_ICRCP (_hoops_CSIR, *_hoops_HHACP, *vcolors, _hoops_SIAIS, _hoops_SHAIS);
			}
		}
		else
#endif
		if (BIT (*flags, _hoops_AARHR))
			*vcolors = *_hoops_HCPGS;
		else
			*vcolors = _hoops_RSISR;

		if (BIT (_hoops_PHAH.options, _hoops_CHRH)) 
			*vcolors = HD_Apply_Color_Effects (*vcolors, _hoops_PHAH);


		if ((ts->_hoops_GSCP->type == _hoops_SCIP || ts->_hoops_GSCP->type == _hoops_GSIP) &&
			BIT(((Polyhedron*)ts->_hoops_GSCP)->polyhedron_flags, _hoops_CGRHR))
			++flags;
		++_hoops_HHACP;
		++_hoops_HCPGS;
		++vcolors;
	} _hoops_RGGA (--remaining == 0);

	if (ANYBIT (ts->face_attributes.flags, _hoops_IACHR)) {
		/*-- _hoops_RISIS _hoops_AISIS _hoops_PISIS _hoops_HISIS _hoops_IHASR --*/
		_hoops_SHSIS (nr, ts, _hoops_SPRI);
		/*_hoops_CRHH->_hoops_IISIS = _hoops_HSAGA->_hoops_CISIS;*/
	}

	return ts->_hoops_PCHA;
}


local RGB * _hoops_SISIS (
	Net_Rendition const & 			nr,
	Tristrip *						ts,
	Local_Face_Attributes const *	_hoops_CPRI) {
	Display_Context *				dc = (Display_Context *)nr->_hoops_SRA;
	_hoops_GIIPR const *		flags;
	_hoops_ACGHR const *		_hoops_HHACP;
	RGB const *						_hoops_HCPGS;
	RGB alter *						fcolors;
	int								remaining;
	_hoops_RHAH const *				_hoops_CSIR;
	RGB								_hoops_RSISR = _hoops_GPSR::_hoops_RPSR;
	bool							_hoops_SIAIS;

	_hoops_SIAIS = ALLBITS (nr->_hoops_IRR->_hoops_CSA,
								 ((_hoops_HIRC |
								   _hoops_PHGI) & ~_hoops_AHGI));

	/*_hoops_IIRRA = &_hoops_CPHAR->_hoops_SPSSI;*/

	flags = _hoops_CPRI->_hoops_CHHPR();
	_hoops_HHACP = _hoops_CPRI->findices;
	_hoops_HCPGS = _hoops_CPRI->colors;
	remaining = ts->face_count;

	if ((fcolors = dc->_hoops_RGHGH) == null || dc->_hoops_AGHGH < remaining) {
		if (fcolors != null)
			FREE_ARRAY (fcolors, dc->_hoops_AGHGH, RGB);
		POOL_ALLOC_ARRAY (fcolors, remaining, RGB, dc->memory_pool);
		dc->_hoops_RGHGH = fcolors;
		dc->_hoops_AGHGH = remaining;
	}
	ts->_hoops_PAGI = fcolors;
	ts->_hoops_SRHA |= DL_TEMPORARY_DATA;

	if (_hoops_CPRI->_hoops_PSRRA +
		_hoops_CPRI->_hoops_HSRRA < ts->point_count)
		_hoops_RSISR = nr->_hoops_IHA->_hoops_CHA->_hoops_CSHR;

	_hoops_CSIR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR;

	_hoops_AHAH const &				_hoops_PHAH = nr->_hoops_ARA->_hoops_IHRH;
	_hoops_AHAH 					_hoops_SHAIS;

	do {
#ifndef DISABLE_COLOR_MAPS
		if (BIT (*flags, LFA_EXPLICIT_COLOR_BY_FINDEX)) {
			if (_hoops_CSIR->length == 0) {
				HD_Report_Null_Color_Map ("tristrip", _hoops_CSIR);
				*fcolors = _hoops_GPSR::_hoops_RPSR;
			}
			else {
				_hoops_ICRCP (_hoops_CSIR, *_hoops_HHACP, *fcolors, _hoops_SIAIS, _hoops_SHAIS);
			}
		}
		else
#endif
		if (BIT (*flags, LFA_EXPLICIT_COLOR_BY_VALUE))
			*fcolors = *_hoops_HCPGS;
		else
			*fcolors = _hoops_RSISR;

		if (BIT (_hoops_PHAH.options, _hoops_CHRH)) 
			*fcolors = HD_Apply_Color_Effects (*fcolors, _hoops_PHAH);


		if ((ts->_hoops_GSCP->type == _hoops_SCIP || ts->_hoops_GSCP->type == _hoops_GSIP) &&
			BIT(((Polyhedron*)ts->_hoops_GSCP)->polyhedron_flags, _hoops_APRHR))
			++flags;
		++_hoops_HHACP;
		++_hoops_HCPGS;
		++fcolors;
	} _hoops_RGGA (--remaining == 0);

	//_hoops_RPP (_hoops_AGGC (_hoops_GARI->_hoops_GCSIS._hoops_SGI, _hoops_RCSIS)) {
	//	/*-- _hoops_RISIS _hoops_AISIS _hoops_PISIS _hoops_HISIS _hoops_IHASR --*/
	//	_hoops_ACSIS (_hoops_SCII, _hoops_GARI, _hoops_IIRRA);
	//	/*_hoops_CRHH->_hoops_IISIS = _hoops_HSAGA->_hoops_CISIS;*/
	//}

	return ts->_hoops_PAGI;
}



local RGB * _hoops_PCSIS (
	Net_Rendition const & 			nr,
	Polyedge alter *				polyedge,
	Local_Vertex_Attributes const *	_hoops_SPRI) {
	Display_Context *				dc = (Display_Context *)nr->_hoops_SRA;
	Local_Vertex_Flags  *		flags;
	_hoops_ACGHR const *		_hoops_HHACP;
	RGB const *						_hoops_HCPGS;
	RGB alter *						vcolors;
	int								remaining;
	_hoops_RHAH const *				_hoops_CSIR;
	RGB								_hoops_HHSIS = _hoops_GPSR::_hoops_RPSR;
	bool							_hoops_SIAIS;

	_hoops_SIAIS = ALLBITS (nr->_hoops_IRR->_hoops_CSA,
								 ((_hoops_SSRC |
								   _hoops_CSRC) & ~_hoops_AHGI));


	flags = ((Local_Vertex_Attributes*)_hoops_SPRI)->_hoops_CHHPR();
	_hoops_HCPGS = _hoops_SPRI->ecolors;
	_hoops_HHACP = _hoops_SPRI->_hoops_HGHIR;
	remaining = polyedge->point_count;

	if ((vcolors = dc->_hoops_SSPGH) == null || dc->_hoops_GGHGH < remaining) {
		if (vcolors != null)
			FREE_ARRAY (vcolors, dc->_hoops_GGHGH, RGB);
		POOL_ALLOC_ARRAY (vcolors, remaining, RGB, dc->memory_pool);
		dc->_hoops_SSPGH = vcolors;
		dc->_hoops_GGHGH = remaining;
	}
	polyedge->_hoops_PCHA = vcolors;


	if (_hoops_SPRI->_hoops_CCHPR +
		_hoops_SPRI->_hoops_SCHPR < polyedge->point_count)
		_hoops_HHSIS = nr->_hoops_RHP->_hoops_CHA->_hoops_CSHR;

	_hoops_CSIR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR;

	_hoops_AHAH const &				_hoops_PHAH = nr->_hoops_ARA->_hoops_IHRH;
	_hoops_AHAH 					_hoops_SHAIS;

	do {
#ifndef DISABLE_COLOR_MAPS
		if (BIT (*flags, _hoops_RPHPR)) {
			if (_hoops_CSIR->length == 0) {
				HD_Report_Null_Color_Map ("polyedge", _hoops_CSIR);
				*vcolors = _hoops_GPSR::_hoops_RPSR;
			}
			else {
				_hoops_ICRCP (_hoops_CSIR, *_hoops_HHACP, *vcolors, _hoops_SIAIS, _hoops_SHAIS);
			}
		}
		else
#endif
		if (BIT (*flags, _hoops_PPHPR))
			*vcolors = *_hoops_HCPGS;
		else					/* _hoops_HPP _hoops_SHIR */
			*vcolors = _hoops_HHSIS;

		if (BIT (_hoops_PHAH.options, _hoops_CHRH)) 
			*vcolors = HD_Apply_Color_Effects (*vcolors, _hoops_PHAH);

		if ((polyedge->_hoops_GSCP->type == _hoops_SCIP || polyedge->_hoops_GSCP->type == _hoops_GSIP) &&
				BIT(((Polyhedron*)polyedge->_hoops_GSCP)->polyhedron_flags, _hoops_CGRHR))
			++flags;
		++_hoops_HCPGS;
		++_hoops_HHACP;
		++vcolors;
	} _hoops_RGGA (--remaining == 0);

	if (ANYBIT (polyedge->_hoops_PPGI.flags, _hoops_CCICA)) {
		_hoops_PHSIS(nr, polyedge, _hoops_SPRI);
	}

	return polyedge->_hoops_PCHA;
}


GLOBAL_FUNCTION int alter * HD_Generate_DC_Screen_Facings (
	Net_Rendition const & 		nr,
	int							count,
	_hoops_ARPA const *				planes,
	bool						_hoops_CRCPH) {
	Display_Context *			dc = (Display_Context *)nr->_hoops_SRA;

	/* _hoops_SIPHA _hoops_GSSIA _hoops_SRHR _hoops_RPP _hoops_RRI _hoops_SIGR */
	if (count > dc->_hoops_ICACP) {
		if (dc->_hoops_CGHAR != null)
			FREE_ARRAY_ALIGNED (dc->_hoops_CGHAR, dc->_hoops_ICACP, int, 16);
		POOL_ALLOC_ARRAY_ALIGNED_CACHED (dc->_hoops_CGHAR, count, int, 16, dc->memory_pool);
		dc->_hoops_ICACP = count;
	}

	HD_Compute_Screen_Plane_Facings (nr, count, planes, _hoops_CRCPH,
									 dc->_hoops_CGHAR);

	return dc->_hoops_CGHAR;
}


//_hoops_CRRHP _hoops_HISI _hoops_SIRGR _hoops_CHR _hoops_HCIAA _hoops_HHRI
local void _hoops_HCSIS (Tristrip alter *tristrip)
{
	if (BIT (tristrip->_hoops_RAHH, _hoops_AIPI)) {
		tristrip->_hoops_RAHH &= ~_hoops_AIPI;
		if (tristrip->points) {
			FREE_ARRAY_ALIGNED (tristrip->points, tristrip->point_count, Point, 16);
			tristrip->points = null;
		}
	}
#ifndef DISABLE_GEOMETRY_ATTRIBUTES
#  ifndef _hoops_GCGHR
	if (BIT (tristrip->_hoops_RAHH, _hoops_PIPI)) {
		tristrip->_hoops_RAHH &= ~_hoops_PIPI;
		if (tristrip->_hoops_PCHA) {
			FREE_ARRAY (tristrip->_hoops_PCHA, tristrip->point_count, RGB);
			tristrip->_hoops_PCHA = null;
		}
	}
	if (BIT (tristrip->_hoops_RAHH, _hoops_RCGHR)) {
		tristrip->_hoops_RAHH &= ~_hoops_RCGHR;
		if (tristrip->_hoops_HCHA) {
			FREE_ARRAY (tristrip->_hoops_HCHA, tristrip->point_count, _hoops_ACGHR);
			tristrip->_hoops_HCHA = null;
		}
	}
	if (BIT (tristrip->_hoops_RAHH, _hoops_SHRI)) {
		tristrip->_hoops_RAHH &= ~_hoops_SHRI;
		if (tristrip->_hoops_PAGI) {
			FREE_ARRAY (tristrip->_hoops_PAGI, tristrip->face_count, RGB);
			tristrip->_hoops_PAGI = null;
		}
	}
#  endif
#  ifndef _hoops_HCGHR
	if (BIT (tristrip->_hoops_RAHH, _hoops_ICGHR)) {
		tristrip->_hoops_RAHH &= ~_hoops_ICGHR;
		if (tristrip->_hoops_ICHA) {
			FREE_ARRAY (tristrip->_hoops_ICHA, tristrip->point_count, Vector);
			tristrip->_hoops_ICHA = null;
		}
	}
	if (BIT (tristrip->_hoops_RAHH, _hoops_RCPI)) {
		tristrip->_hoops_RAHH &= ~_hoops_RCPI;
		if (tristrip->_hoops_PRHH) {
			FREE_ARRAY_ALIGNED (tristrip->_hoops_PRHH, tristrip->face_count, _hoops_ARPA, 16);
			tristrip->_hoops_PRHH = null;
		}
	}
#  endif
#endif
}

local void _hoops_ICSIS (Polyedge alter *polyedge)
{
	if (BIT (polyedge->_hoops_RAHH, _hoops_AIPI)) {
		polyedge->_hoops_RAHH &= ~_hoops_AIPI;
		if (polyedge->points) {
			FREE_ARRAY_ALIGNED (polyedge->points, polyedge->point_count, Point, 16);
			polyedge->points = null;
		}
	}
#ifndef DISABLE_GEOMETRY_ATTRIBUTES
#  ifndef _hoops_GCGHR
	if (BIT (polyedge->_hoops_RAHH, _hoops_PIPI)) {
		polyedge->_hoops_RAHH &= ~_hoops_PIPI;
		if (polyedge->_hoops_PCHA) {
			FREE_ARRAY (polyedge->_hoops_PCHA, polyedge->point_count, RGB);
			polyedge->_hoops_PCHA = null;
		}
	}
	if (BIT (polyedge->_hoops_RAHH, _hoops_RCGHR)) {
		polyedge->_hoops_RAHH &= ~_hoops_RCGHR;
		if (polyedge->_hoops_HCHA) {
			FREE_ARRAY (polyedge->_hoops_HCHA, polyedge->point_count, _hoops_ACGHR);
			polyedge->_hoops_HCHA = null;
		}
	}
	if (BIT (polyedge->_hoops_RAHH, _hoops_PCGHR)) {
		polyedge->_hoops_RAHH &= ~_hoops_PCGHR;
		if (polyedge->_hoops_ASHA) {
			FREE_ARRAY (polyedge->_hoops_ASHA, polyedge->_hoops_SPHA, RGB);
			polyedge->_hoops_ASHA = null;
		}
	}
#  endif
#  ifndef _hoops_HCGHR
	if (BIT (polyedge->_hoops_RAHH, _hoops_ICGHR)) {
		polyedge->_hoops_RAHH &= ~_hoops_ICGHR;
		if (polyedge->_hoops_ICHA) {
			FREE_ARRAY (polyedge->_hoops_ICHA, polyedge->point_count, Vector);
			polyedge->_hoops_ICHA = null;
		}
	}
	if (BIT (polyedge->_hoops_RAHH, _hoops_GHII)) {
		polyedge->_hoops_RAHH &= ~_hoops_GHII;
		if (polyedge->_hoops_RSHA) {
			FREE_ARRAY (polyedge->_hoops_RSHA, polyedge->_hoops_SPHA, Vector);
			polyedge->_hoops_RSHA = null;
		}
	}
#  endif
#endif
}



local bool _hoops_CCSIS (
	Net_Rendition const &nr,
	One_Face_Attributes *_hoops_HPHCR,
	bool alter *_hoops_SCSIS,
	RGB alter *_hoops_GSSIS) 
{
	/* _hoops_RH _hoops_GRH _hoops_PRCA _hoops_GGR _hoops_RGR _hoops_RIS _hoops_PCIC _hoops_SGP _hoops_IRS _hoops_CCAH _hoops_IRGH _hoops_IPP,
	 * _hoops_HIH _hoops_RGAR _hoops_RPP _hoops_RH _hoops_IRGH _hoops_HHHA _hoops_SIGRA _hoops_ACAR _hoops_IS _hoops_IRS _hoops_IHGP _hoops_APIR _hoops_SGS _hoops_HRGR 
	 * _hoops_SASPR _hoops_IS _hoops_PCPA _hoops_RH _hoops_APIR _hoops_IPP _hoops_AIAH _hoops_ICGI */
	int index = (int)_hoops_HPHCR->findex;

	*_hoops_SCSIS = false;
	_hoops_CAHHP const &	_hoops_SAHHP = nr->_hoops_ASIR->_hoops_PSIR;
	if (_hoops_SAHHP->length) {
		index =				index % _hoops_SAHHP->length;
		Named_Material *	_hoops_GASPA = &_hoops_SAHHP->_hoops_CSIR->_hoops_HAA[index];

		if (!ANYBIT (_hoops_GASPA->_hoops_PRGRA, ~(
						M_DIFFUSE|
						_hoops_RHGRA|
						M_TRANSMISSION|
						_hoops_IIARA))) {
			if (ANYBIT (_hoops_GASPA->_hoops_PRGRA, M_TRANSMISSION|_hoops_IIARA)) {
				if (_hoops_HPHCR->findex != index ||
				    _hoops_GASPA->texture[_hoops_PCA] != null ||
					_hoops_GASPA->_hoops_IRIR != nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR)
					return true;
			}
			if (ANYBIT (_hoops_GASPA->_hoops_PRGRA, M_DIFFUSE|_hoops_RHGRA)) {
				if (_hoops_GASPA->_hoops_SCA != null) {
					return true;
				}
				if (_hoops_HPHCR->findex == index) {
					if (_hoops_GASPA->_hoops_CSHR != nr->_hoops_IHA->_hoops_CHA->_hoops_CSHR) {
						*_hoops_SCSIS = true;
						*_hoops_GSSIS = _hoops_GASPA->_hoops_CSHR;
						return true;
					}
				}
				else {
					bool _hoops_SIAIS =
								ALLBITS (nr->_hoops_IRR->_hoops_CSA,
										 ((_hoops_HIRC |
										   _hoops_PHGI) & ~_hoops_AHGI));
					_hoops_AHAH 		_hoops_SHAIS;
					_hoops_ICRCP (_hoops_SAHHP->_hoops_CSIR, _hoops_HPHCR->findex, *_hoops_GSSIS, _hoops_SIAIS, _hoops_SHAIS);
					if (*_hoops_GSSIS != nr->_hoops_IHA->_hoops_CHA->_hoops_CSHR) {
						*_hoops_SCSIS = true;
						return true;
					}
				}
			}
			return false;
		}
		else
			return true;
	}
	else 
		return true;
	
}


#if 0
local void _hoops_RSSIS (
	Net_Rendition const &			nr,
	Tristrip const *				tristrip,
	Polyhedron const *				_hoops_IPRI) {
	Local_Vertex_Attributes const *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;
	Local_Face_Attributes const *	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;

	if (_hoops_SPRI->normals != null) {
		Net_Rendition	_hoops_ASSIS = nr.Copy();
		Line_Rendition	_hoops_PSSIS = _hoops_ASSIS->_hoops_AHP.Modify();

		_hoops_PSSIS->color = RGBAS32 (255, 0, 0);

		Line			line;

		line.type = _hoops_PIIP;

		for (int i=0; i < _hoops_IPRI->point_count; ++i) {
			line.points[0] = _hoops_IPRI->points[i];
			line.points[1] = line.points[0] + _hoops_SPRI->normals[i];

			_hoops_CCAIP (_hoops_ASSIS, (Polyline *)&line);
		}
	}
	if (_hoops_CPRI->normals != null) {
		Net_Rendition	_hoops_ASSIS = nr.Copy();
		Line_Rendition	_hoops_PSSIS = _hoops_ASSIS->_hoops_AHP.Modify();

		_hoops_PSSIS->color = RGBAS32 (255, 255, 0);

		Line			line;

		line.type = _hoops_PIIP;

		int const *	_hoops_ACCI = tristrip->lengths;
		int const *	vi = tristrip->_hoops_AIHA;
		int const *	fi = tristrip->face_indices;
		int		_hoops_HSPI, _hoops_ISPI, _hoops_CSPI;
		int		f = -1;

		for (int s = 0; s < tristrip->_hoops_PHHA; ++s) {
			int	l = *_hoops_ACCI++;
			_hoops_HSPI = *vi++;
			_hoops_ISPI = *vi++;
			l -= 2;
			if (fi)
				fi += 2;
			while (l-- > 0) {
				_hoops_CSPI = *vi++;
				if (fi)
					f = *fi++;
				else
					++f;

				line.points[0] = (_hoops_IPRI->points[_hoops_HSPI] +
								  (_hoops_IPRI->points[_hoops_ISPI] - _hoops_HPCH::_hoops_IPCH) +
								  (_hoops_IPRI->points[_hoops_CSPI] - _hoops_HPCH::_hoops_IPCH)) / 3.0f;
				line.points[1] = line.points[0] + 0.5f * _hoops_CPRI->normals[f];

				_hoops_CCAIP (_hoops_ASSIS, (Polyline *)&line);

				_hoops_HSPI = _hoops_ISPI;
				_hoops_ISPI = _hoops_CSPI;
			}
		}

	}
}
#endif


local INLINE Tristrip alter * _hoops_HSSIS (Tristrip const *tristrip)
{
	Tristrip *	_hoops_AHPIS;

	ASSERT (!BIT (tristrip->_hoops_SRHA, _hoops_GAHH));
	ZALLOC (_hoops_AHPIS, Tristrip);
	*_hoops_AHPIS = *tristrip;
	_hoops_ICAI (_hoops_AHPIS);
	_hoops_AHPIS->_hoops_RAHH = _hoops_CGCGP;

	if (_hoops_AHPIS->_hoops_GSSH != null)
		_hoops_CAHS (_hoops_AHPIS->_hoops_GSSH);

	_hoops_AHPIS->_hoops_SCGHR = tristrip;
	_hoops_CAHS (tristrip);

	_hoops_AHPIS->_hoops_GAHA = null;
	_hoops_AHPIS->_hoops_SRHA |= DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS|_hoops_GAHH;
	_hoops_AHPIS->_hoops_SRHA &= ~DL_HAS_TRANSPARENCY;

	return _hoops_AHPIS;
}


typedef VHash<int, int> _hoops_ISSIS;

local INLINE Tristrip alter * _hoops_CSSIS (
	_hoops_AIGPR *	_hoops_RIGC,
	Tristrip const *		ts) 
{	
	int i, vi;
	int _hoops_PCAP, src;
	int _hoops_SSSIS;

	_hoops_ISSIS *	_hoops_GCAH = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_ISSIS)(_hoops_RIGC->memory_pool);

	Tristrip *_hoops_GGGCS;
	ZALLOC (_hoops_GGGCS, Tristrip);
	_hoops_ICAI (_hoops_GGGCS);
	_hoops_GGGCS->_hoops_GSCP = ts->_hoops_GSCP;
	_hoops_GGGCS->bounding = ts->bounding;
	_hoops_GGGCS->total = ts->total;
	_hoops_GGGCS->face_count = ts->total - 2*ts->_hoops_PHHA;
	_hoops_GGGCS->face_attributes = ts->face_attributes;
	_hoops_GGGCS->_hoops_PHHA = ts->_hoops_PHHA;
	_hoops_GGGCS->_hoops_SRHA = ts->_hoops_SRHA;
	_hoops_GGGCS->_hoops_CARI = ts->_hoops_CARI;
	_hoops_GGGCS->_hoops_GSAI = ts->_hoops_GSAI;
	if (ts->lengths) {
		ALLOC_ARRAY (_hoops_GGGCS->lengths, _hoops_GGGCS->_hoops_PHHA, int);
		_hoops_AIGA (ts->lengths, _hoops_GGGCS->_hoops_PHHA, int, _hoops_GGGCS->lengths);
		_hoops_GGGCS->_hoops_RAHH |= _hoops_AAHH;
	}
	if (ts->_hoops_PAGI) {
		ALLOC_ARRAY (_hoops_GGGCS->_hoops_PAGI, _hoops_GGGCS->face_count, RGB);
		_hoops_GGGCS->_hoops_RAHH |= _hoops_SHRI;
	}
	if (ts->_hoops_PRHH) {
		ALLOC_ARRAY_ALIGNED (_hoops_GGGCS->_hoops_PRHH, _hoops_GGGCS->face_count, _hoops_ARPA, 16);
		_hoops_GGGCS->_hoops_RAHH |= _hoops_RCPI;
	}
	ASSERT (ts->_hoops_PCHA == null);
	ASSERT (ts->_hoops_HCHA == null);
	ASSERT (ts->_hoops_GSSH == null || ts->_hoops_GSSH->_hoops_GSHA == 0);
	_hoops_GGGCS->_hoops_GSSH = ts->_hoops_GSSH;
	_hoops_CAHS (ts->_hoops_GSSH);
	ASSERT (ts->_hoops_CCCP == null);

	if (ts->_hoops_AIHA) {
		ALLOC_ARRAY (_hoops_GGGCS->_hoops_AIHA, ts->total, int);
		_hoops_SSSIS = 0;
		vi = -1;
		for (i = 0 ; i < ts->total ; i++) {
			if (ts->_hoops_AIHA)
				vi = ts->_hoops_AIHA[i];
			else
				vi++;
			if (_hoops_GCAH->LookupItem (vi) != VHASH_STATUS_SUCCESS) {
				_hoops_GCAH->InsertItem (vi, _hoops_SSSIS);
				_hoops_SSSIS++;
			}
		}
		_hoops_GGGCS->point_count = _hoops_SSSIS;
		ALLOC_ARRAY_ALIGNED (_hoops_GGGCS->points, _hoops_GGGCS->point_count, Point, 16);
	}
	else {
		_hoops_GGGCS->point_count = ts->point_count;
		ALLOC_ARRAY (_hoops_GGGCS->_hoops_AIHA, ts->total, int);
		ALLOC_ARRAY_ALIGNED (_hoops_GGGCS->points, _hoops_GGGCS->point_count, Point, 16);
		_hoops_AIGA (ts->points, _hoops_GGGCS->point_count, Point, _hoops_GGGCS->points);
	}
	_hoops_GGGCS->_hoops_RAHH |= _hoops_AIPI;

	_hoops_PCAP = 0;
	src = -1;
	for (i = 0 ; i < ts->total ; i++) {
		if (ts->face_indices)
			src = ts->face_indices[i];
		else
			src++;
		if (ts->_hoops_AIHA) {
			_hoops_GCAH->LookupItem (ts->_hoops_AIHA[i], &_hoops_GGGCS->_hoops_AIHA[i]);
			_hoops_GGGCS->points[_hoops_GGGCS->_hoops_AIHA[i]] = ts->points[ts->_hoops_AIHA[i]];
		}
		if (ts->_hoops_PAGI)
			_hoops_GGGCS->_hoops_PAGI[_hoops_PCAP] = ts->_hoops_PAGI[src];
		if (ts->_hoops_PRHH)
			_hoops_GGGCS->_hoops_PRHH[_hoops_PCAP] = ts->_hoops_PRHH[src];
	}

	delete _hoops_GCAH;

	return _hoops_GGGCS;
}


local _hoops_SGRGH alter * _hoops_RGGCS (
	Net_Rendition const & 			inr,
	_hoops_SGRGH alter *			node,
	Color_Object					_hoops_GSSCC,
	Polyhedron const *				_hoops_IPRI) {
	_hoops_SSAGR(_hoops_IPRI);
	Display_Context alter *			dc = (Display_Context alter *)inr->_hoops_SRA;
	_hoops_SSAGR(dc);
	_hoops_GRGH const &			_hoops_RRGH = inr->_hoops_IRR;
	_hoops_CIGA const &			_hoops_SIGA = inr->_hoops_IHA;
	_hoops_HHCR const &		_hoops_IHCR = inr->transform_rendition;
	Tristrip *						tristrip;
	Tristrip alter *				_hoops_AGGCS = null;
	Vector const *					_hoops_ICHA;
	_hoops_ARPA const *					_hoops_PRHH;
	_hoops_RRCC *			_hoops_HAPAR;
	
	_hoops_SARHR			_hoops_PIHIH;
	
	int								_hoops_PGGCS;
	unsigned int					_hoops_SRHA;
	unsigned int					_hoops_CARI;
	unsigned int					_hoops_GSAI;
	bool							_hoops_PAACP;
	bool							_hoops_HGGCS;
	bool							_hoops_SCSCC = false;

	Local_Vertex_Attributes const *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;
	Local_Face_Attributes const *	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;
	_hoops_SSAGR(_hoops_SPRI);
	_hoops_SSAGR(_hoops_CPRI);

	Activity						_hoops_IGGCS = 
										dc->_hoops_CPGPR | _hoops_IPRI->_hoops_CPGPR | 
										dc->_hoops_RIIAP & _hoops_IPRI->_hoops_SPGPR;

	bool							_hoops_CGGCS = false;
	bool							_hoops_SGGCS = false;

	_hoops_ACHR						_hoops_CIPSH = inr->_hoops_RGP & T_FACES;

	if (BIT (_hoops_RRGH->locks._hoops_RGP, T_FACES)) {
		if (_hoops_CIPSH) {
			if (_hoops_IPRI->face_count > 0) {
				_hoops_SGGCS = true;
				_hoops_CGGCS = true;
			}
		}
	}
	else {
		if (_hoops_CIPSH) {
			if (_hoops_IPRI->face_count > _hoops_CPRI->_hoops_SIIPR)
				_hoops_SGGCS = true;
		}
		else {
			if (_hoops_CPRI->_hoops_CPIAA > 0)
				_hoops_SGGCS = true;
		}
	}

	_hoops_PGGCS = 0;
	if (BIT (inr->current, _hoops_PGCGA))
		_hoops_PGGCS |= Tristrip_Cut_Edges;
	if (BIT (_hoops_IPRI->polyhedron_flags, _hoops_CCRHR))
		_hoops_PGGCS |= Tristrip_Resort;

	if (!_hoops_SGGCS && 
		!ANYBIT (_hoops_PGGCS, Tristrip_Specials))
		return null;

	/* _hoops_PGSA _hoops_HHH _hoops_RSSI */

	_hoops_PIHIH = _hoops_PPRHR | _hoops_IACHR | _hoops_HAGI;

	if (_hoops_IPRI->type == _hoops_SCIP && ((Shell const *)_hoops_IPRI)->face_list_length > 0)
		_hoops_PIHIH |= _hoops_RGIHR;


	if (!_hoops_CGGCS) {
		if (_hoops_CIPSH)
			_hoops_PIHIH |= _hoops_HSIPR;
		else
			_hoops_PIHIH |= _hoops_HRAPA;
	}

	_hoops_HAPAR = _hoops_RRSIS (inr, _hoops_IPRI);

	_hoops_SRHA = 0;
	_hoops_CARI = 0;
	_hoops_GSAI = 0;

	/* _hoops_RH _hoops_HGRH _hoops_RPHR _hoops_ARI _hoops_HRGR _hoops_IGPHR _hoops_PGGA _hoops_GRPHR _hoops_SGH _hoops_PAII
	 * _hoops_CRHH-_hoops_GRGCS _hoops_IS _hoops_GACC _hoops_RIPHR _hoops_PAII _hoops_GPHA _hoops_ASGA.
	 */
	if (!BIT (_hoops_IPRI->polyhedron_flags, PHF_VERTEX_NORMALS_VALID) &&
		(BIT (_hoops_IHCR->flags, _hoops_GRHH) &&
		 BIT (inr->_hoops_RGP, T_LIGHTS_FOR_FACES) &&
		 _hoops_SIGA->_hoops_AGP != null &&
		 ANYBIT (_hoops_RRGH->_hoops_CSA, _hoops_SSA|_hoops_GGP|_hoops_IIRAP) ||
		 // _hoops_RHI _hoops_SIA
		 _hoops_SIGA->_hoops_CHA->texture[_hoops_RIA] != null ||
		 // _hoops_RRP _hoops_CIGGR _hoops_GSSR _hoops_IH _hoops_RHPS
		 _hoops_HAPAR->_hoops_CCHA != null && 
		 ALLBITS (_hoops_HAPAR->_hoops_SCAI, _hoops_GGASP|_hoops_PSRSP))) {

		// _hoops_HSGIR _hoops_CCA _hoops_GPHA _hoops_ASGA
		_hoops_RCCA(_hoops_RHRGH) += HI_Assemble_3D_Tristrips ((Polyhedron alter *) _hoops_IPRI,
															 _hoops_PIHIH, true);
		_hoops_HSCIS (_hoops_IHCR, _hoops_IPRI);
	}
	else if (!ALLBITS (_hoops_IPRI->_hoops_ACRHR, _hoops_PIHIH)) {
		/* _hoops_HSGIR _hoops_SIHH _hoops_GPHA _hoops_ASGA */
		_hoops_RCCA(_hoops_RHRGH) += HI_Assemble_3D_Tristrips ((Polyhedron alter *) _hoops_IPRI,
															 _hoops_PIHIH, false);
		_hoops_HSCIS (_hoops_IHCR,(Polyhedron alter *)_hoops_IPRI);
	}
	else if (ANYBIT (_hoops_IPRI->_hoops_CPGPR, _hoops_AHSGA|_hoops_CASIR)) {
		/* _hoops_CCGI _hoops_RPGAH _hoops_IHRI, _hoops_HIH _hoops_CPHP _hoops_HGAS.	_hoops_GAAP _hoops_CPHP _hoops_PII
		   _hoops_GPHA _hoops_PSHA, _hoops_PGAP _hoops_PSP _hoops_RPIP _hoops_HRCI _hoops_IIRGR (_hoops_CR _hoops_SR _hoops_PAH
		   _hoops_PSP _hoops_RPIP _hoops_SHH _hoops_RCRR _hoops_IIGR _hoops_SSRHR _hoops_CAPR _hoops_HII _hoops_RH _hoops_SCRPA)
		*/
		Polyhedron alter *	_hoops_HPGPR = (Polyhedron alter *)_hoops_IPRI;

		if (BIT (_hoops_HPGPR->polyhedron_flags, _hoops_CCRHR))
			HI_Resort_Tristrips (_hoops_HPGPR, -1);

		HI_Reset_Strip_Flags (_hoops_HPGPR);
		_hoops_HPGPR->_hoops_CPGPR &= ~_hoops_AHSGA;
	}
	else if (BIT (_hoops_IPRI->polyhedron_flags, _hoops_CCRHR))
		HI_Resort_Tristrips ((Polyhedron alter *)_hoops_IPRI, -1);

	((Polyhedron alter *)_hoops_IPRI)->polyhedron_flags &= ~_hoops_CCRHR;


	if (BIT (_hoops_IPRI->polyhedron_flags, PHF_VERTEX_NORMALS_VALID) &&
		 // _hoops_RRP _hoops_CIGGR _hoops_GSSR _hoops_IH _hoops_RHPS
		 _hoops_HAPAR->_hoops_CCHA != null && 
		 ALLBITS (_hoops_HAPAR->_hoops_SCAI, _hoops_GGASP|_hoops_PSRSP)) {

#ifndef DISABLE_EXTENDED_TEXTURE
		if (ALLBITS (_hoops_HAPAR->_hoops_SCAI, _hoops_GGASP|_hoops_PSRSP)) {
			_hoops_RSSH *			params = _hoops_SPRI->_hoops_PPHIR;
			Vector const *		normals = _hoops_SPRI->normals;
			int					point_count = _hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR;

			/* _hoops_GHAP _hoops_RHCA _hoops_RGR _hoops_HHS _hoops_SHH _hoops_IGI _hoops_SSPP */
			/* _hoops_RPP _hoops_RH _hoops_ASGA _hoops_IIP _hoops_HGCR _hoops_AHAPI */
			/* _hoops_IH _hoops_HA _hoops_SR _hoops_IRHH _hoops_IRS _hoops_IPS */
			_hoops_AIGA (normals, point_count, Vector, params);
			_hoops_AIGA (normals, point_count, Vector, _hoops_HAPAR->_hoops_CCHA);	// _hoops_SSRS?
		
			(_hoops_SSIC alter &)_hoops_SPRI->_hoops_SSCCC |= _hoops_ASRSP;
			(_hoops_SSIC alter &)_hoops_SPRI->_hoops_SSCCC &= ~_hoops_PSRSP;
			_hoops_HAPAR->_hoops_SCAI |= _hoops_ASRSP;
			_hoops_HAPAR->_hoops_SCAI &= ~_hoops_PSRSP;
		}
#endif
	}


	if ((tristrip = _hoops_IPRI->tristrips) == null) {
		if (_hoops_ISAI(_hoops_HAPAR) == 0)
			HI_Free_Texture_Parameters (_hoops_HAPAR);

		return node;
	}


	if (BIT (_hoops_PGGCS, Tristrip_Cut_Edges)) {
		 do {
			_hoops_SARHR	_hoops_RCGPS = tristrip->face_attributes.flags & _hoops_PIHIH;

			_hoops_AGGCS = tristrip->next;

			if (!ANYBIT (_hoops_RCGPS, _hoops_HSIPR|_hoops_RGIHR)) {
				/* _hoops_PSHR _hoops_HGSR _hoops_GAR _hoops_GSSR _hoops_ASCA, _hoops_HIH _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_HIISR _hoops_GII _hoops_CCA _hoops_AIRC */
				tristrip->points = _hoops_IPRI->points;
				tristrip->point_count = _hoops_IPRI->point_count;
				tristrip->face_count = _hoops_IPRI->face_count;

				if (tristrip->_hoops_HSAI > 1) {
					tristrip = _hoops_HSSIS (tristrip);
				}
				else
					_hoops_CAHS (tristrip);

				tristrip->_hoops_ICHA = null;
				tristrip->_hoops_PCHA = null;
				tristrip->_hoops_HCHA = null;
				//_hoops_CRHH->_hoops_GHARC = 0;
				tristrip->_hoops_PAGI = null;
				tristrip->_hoops_PRHH = null;
				//_hoops_CRHH->_hoops_APSCC = _hoops_IRAP;
				tristrip->_hoops_RPRCP = false;
				tristrip->_hoops_GPPPI = false;

				
				_hoops_RCCA(tristrips) += tristrip->_hoops_PHHA;

				_hoops_RACIP (inr, tristrip);

				_hoops_ISAI (tristrip);
				if (tristrip->_hoops_HSAI == 0)
					HI_Free_Tristrip (tristrip);
			}
		} while ((tristrip = _hoops_AGGCS) != null /* && !_hoops_RRGCS(_hoops_ARGCS) */);

		if (_hoops_ISAI(_hoops_HAPAR) == 0)
			HI_Free_Texture_Parameters (_hoops_HAPAR);

		return node;
	}



	bool				_hoops_PRGCS;
	bool				_hoops_ARPSH;
	bool				_hoops_HRGCS;
	bool				_hoops_IRGCS;
	bool				_hoops_SPGI;
	bool				_hoops_CRRS = false;

	_hoops_PRGCS = !ANYBIT (_hoops_RRGH->_hoops_CSA, _hoops_IIRAP|_hoops_GGP|_hoops_SSA);
	_hoops_ARPSH = (ANYBIT (_hoops_GSSCC, Color_FRONT|Color_BACK) ||
					_hoops_SPRI->_hoops_RCRHR != 0 ||
					_hoops_SPRI->_hoops_SIRHR != 0 ||
					_hoops_CPRI->_hoops_HSRRA);

	_hoops_SPGI = BIT (_hoops_RRGH->locks.color, Color_FRONT) &&
					 BIT (_hoops_RRGH->locks._hoops_HAA[_hoops_IAA], M_DIFFUSE);
	_hoops_HRGCS = (BIT (_hoops_RRGH->_hoops_CSA,
								(_hoops_HIRC & ~_hoops_AHGI)) &&
						  !_hoops_SPGI);
	_hoops_IRGCS = (BIT (_hoops_RRGH->_hoops_CSA,
								(_hoops_PHGI & ~_hoops_AHGI)) &&
								!_hoops_SPGI);

	_hoops_PAACP = _hoops_HRGCS && _hoops_ARPSH;
	_hoops_HGGCS = _hoops_IRGCS &&  _hoops_SPRI->_hoops_SIRHR;


	/*		_hoops_CRGCS _hoops_GAIGC _hoops_HGAPR _hoops_SRIGC:

	 *		_hoops_RPP _hoops_PSP _hoops_RCA
	 *			_hoops_PSP _hoops_ASGA _hoops_SIGR
	 *		_hoops_SHS _hoops_RPP _hoops_PSP _hoops_RCA _hoops_SRGCS
	 *			_hoops_HSP _hoops_ASGA _hoops_SIGR
	 *		_hoops_SHS
	 *			_hoops_GPHA _hoops_ASGA
	 *
	 *		_hoops_IH _hoops_GRR _hoops_SIGC _hoops_CGGR
	 *			_hoops_RPP _hoops_HAIR _hoops_SRGCS && _hoops_HHH _hoops_GPHA _hoops_PSHA
	 *				_hoops_CCIH _hoops_GH _hoops_HSP _hoops_HSGP (_hoops_HIH _hoops_HAR _hoops_HAIR)
	 *				_hoops_RPP _hoops_CGGR _hoops_HRGR _hoops_AGIRH _hoops_HAIR-_hoops_HPP-_hoops_PIRA
	 *					_hoops_PGSA _hoops_SSPP _hoops_CCA _hoops_RH _hoops_AARPR _hoops_GPHA _hoops_PSHA
	 *				_hoops_SHS
	 *					_hoops_SIHA _hoops_HRSAR _hoops_GPHA _hoops_PSHA (_hoops_IH _hoops_SHSC _hoops_CPHAR)
	 *					_hoops_RPP _hoops_IRGH _hoops_HSP _hoops_HAIR _hoops_ASSP'_hoops_RA _hoops_CHASA _hoops_GII
	 *						_hoops_PGSA _hoops_CCA _hoops_HRSAR _hoops_GPHA _hoops_PSHA
	 *					_hoops_SHS
	 *						_hoops_GRAS _hoops_GCHRR _hoops_IRGH _hoops_PSHA
	 *						_hoops_PGSA _hoops_CCA _hoops_IRGH _hoops_GPHA _hoops_PSHA
	 *			_hoops_SHS
	 *				_hoops_CCIH _hoops_GH _hoops_HSP _hoops_HSGP _hoops_GCPAR _hoops_HAIR _hoops_IH _hoops_SHSC _hoops_CGGR
	 *				_hoops_PGSA _hoops_SIHH _hoops_GPHA _hoops_PSHA
	 */

	if (!BIT (_hoops_IHCR->flags, _hoops_GRHH) ||
		!BIT (inr->_hoops_RGP, T_LIGHTS_FOR_FACES) ||
		_hoops_SIGA->_hoops_AGP == null) {
		/*-- _hoops_GRAPR _hoops_CRIRC --*/
		_hoops_PRHH = null;

		if (_hoops_SIGA->_hoops_CHA->texture[_hoops_RIA] != null) 
			_hoops_ICHA = _hoops_SPRI->normals;
		else 
			_hoops_ICHA = null;
	}
	else if (_hoops_PRGCS) {
		/*--- _hoops_CRPIS _hoops_CRIRC ---*/

		if (!ALLBITS (_hoops_IPRI->polyhedron_flags,
					  PHF_FACE_NORMALS_VALID|_hoops_ASAHR)) {
			HI_Assemble_Face_Normals ((Polyhedron alter *) _hoops_IPRI);
			_hoops_HSCIS(_hoops_IHCR,(Polyhedron alter *)_hoops_IPRI);
		}
		_hoops_PRHH = _hoops_CPRI->normals;

		if (_hoops_SIGA->_hoops_CHA->texture[_hoops_RIA] != null) 
			_hoops_ICHA = _hoops_SPRI->normals;
		else
			_hoops_ICHA = null;
	}
	else {
		/*--- _hoops_SRPIS _hoops_CRIRC ---*/

		if (!BIT (_hoops_IPRI->polyhedron_flags, PHF_VERTEX_NORMALS_VALID))
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Vertex normals undone");

		_hoops_ICHA = _hoops_SPRI->normals;
		_hoops_PRHH = null;
	}

	

	if (_hoops_RRGH->_hoops_GAHA &&	/* _hoops_AIRI _hoops_CPCI _hoops_AAPR _hoops_HGRC */
			 /* _hoops_PSP _hoops_ASGC _hoops_PAR _hoops_GRH _hoops_ASCA _hoops_CAPRR */
			 inr->_hoops_RSGC->action.draw_3d_tristrip == nullroutine &&
			 dc->_hoops_IPCI->draw_3d_tristrip != HD_Std_3D_Tristrip) {
		_hoops_CRRS = true;
	}

	if (!_hoops_CRRS && 
		BIT (_hoops_IHCR->flags, _hoops_IGSP) &&
		_hoops_IPRI->face_count != 0 &&
		!BIT (inr->current, _hoops_AHIHP) &&
		!BIT(dc->flags, _hoops_GPHHP)) {
		if (!BIT (_hoops_IPRI->polyhedron_flags, _hoops_PGAHR)) {
			HE_WARNING (HEC_TRISTRIP, HES_NON_UNIFORM_HANDEDNESS, "Backface culling performed on polyhedron with non-uniform handedness");
		}

		if (BIT (HOOPS_WORLD->_hoops_CIIPA, _hoops_SIIPA) && /* _hoops_SCICP _hoops_PAR _hoops_PHPA */
			!BIT (HOOPS_WORLD->_hoops_HGGHR, _hoops_IICPP) &&
			!BIT(dc->flags, _hoops_GIHCP)) {
			if (!ALLBITS (_hoops_IPRI->polyhedron_flags, PHF_FACE_NORMALS_VALID|_hoops_ASAHR)) {
				HI_Assemble_Face_Normals ((Polyhedron alter *) _hoops_IPRI);
				_hoops_HSCIS(_hoops_IHCR, (Polyhedron alter *)_hoops_IPRI);
			}

			if (_hoops_IPRI->face_count > dc->_hoops_ICACP)
				_hoops_SCSCC = true;
			HD_Generate_DC_Screen_Facings (inr, _hoops_IPRI->face_count, _hoops_CPRI->normals, true);
		}
	}

	_hoops_SIGA._hoops_SSAGR();

	if (_hoops_CRRS) {
		bool				_hoops_SSAIS;
		bool				_hoops_GAGCS;

		_hoops_SSAIS = BIT(_hoops_RRGH->_hoops_PPH, _hoops_HAI);
		_hoops_GAGCS = (_hoops_SIGA->pattern != FP_SOLID) ||
							_hoops_CPRI->_hoops_SRAPA;

		if (_hoops_PRGCS)
			_hoops_SRHA |= DL_FLAT_LIGHTING;
		if (_hoops_GAGCS)
			_hoops_SRHA |= DL_PATTERN;
		if (_hoops_HRGCS)
			_hoops_SRHA |= DL_COLOR_INTERPOLATION;
		if (_hoops_IRGCS)
			_hoops_SRHA |= DL_INDEX_INTERPOLATION;
		if (_hoops_SPRI->_hoops_SIRHR)
			_hoops_SRHA |= DL_COLORS_BY_FINDEX;
		if (BIT (_hoops_IHCR->flags, _hoops_GRHH) && 
			BIT (inr->_hoops_RGP, T_LIGHTS_FOR_FACES)) 
			_hoops_SRHA |= DL_LIGHTING;
		if (_hoops_HAPAR->_hoops_SASCC)
			_hoops_SRHA |= DL_TEXTURING;
		if (BIT (_hoops_HAPAR->_hoops_SCAI, _hoops_HGASP))
			_hoops_SRHA |= DL_NATURAL_PARAMETERS;
		if (_hoops_ARPSH) {
			_hoops_SRHA |= DL_VCOLORED_TRISTRIP;
			if (_hoops_SSAIS)
				_hoops_SRHA |= DL_LOCAL_GRAYSCALE;
			if (_hoops_SPGI) 
				_hoops_SRHA |= _hoops_IIRC;
		}
		if (BIT (inr->_hoops_PSGI, T_FACES) &&
			inr->_hoops_CPP->_hoops_PRH.style != _hoops_GCPI) {
			_hoops_SRHA |= DL_HAS_TRANSPARENCY;
		}
		_hoops_GSAI = _hoops_RRGH->_hoops_CSA & Rendo_TRISTRIP_MASK;
	}

	_hoops_SSAGR(tristrip);

	One_Face_Attributes				_hoops_RAGCS;

	_hoops_AAPHR (_hoops_RAGCS);
	/* _hoops_ARP _hoops_GII _hoops_SR _hoops_PAH _hoops_CGIC _hoops_CPIIS */
	_hoops_RAGCS.pattern = _hoops_SIGA->pattern;
	_hoops_RAGCS.flags |= _hoops_CARHR;
	
	do {
		_hoops_SSAGR(tristrip);
		_hoops_SSAGR(_hoops_IPRI);

		_hoops_SARHR	_hoops_RCGPS;
		Net_Rendition		 	nr = inr;
		_hoops_IGCGP	_hoops_HCSHS = 0;


		_hoops_AGGCS = tristrip->next;

		if (tristrip->_hoops_HSAI > 1 && !BIT(tristrip->_hoops_CARI, _hoops_SARI)) {
			tristrip = _hoops_HSSIS (tristrip);
			tristrip->_hoops_SRHA |= _hoops_SRHA;			
		}
		else {
			if (ANYBIT (tristrip->_hoops_RAHH, _hoops_RRCGP & ~_hoops_AAHH))
				_hoops_HCSIS (tristrip);
			_hoops_CAHS (tristrip);
			tristrip->_hoops_SRHA = _hoops_SRHA;			
		}

		tristrip->points = _hoops_IPRI->points;
		tristrip->_hoops_PRHH = (_hoops_ARPA alter *)_hoops_PRHH;
		tristrip->_hoops_ICHA = (Vector alter *)_hoops_ICHA;
		if (tristrip->_hoops_GSSH != null && _hoops_ISAI (tristrip->_hoops_GSSH) == 0)
			HI_Free_Texture_Parameters (tristrip->_hoops_GSSH);
		tristrip->_hoops_GSSH = _hoops_HAPAR;
		_hoops_CAHS(_hoops_HAPAR);
		tristrip->point_count = _hoops_IPRI->point_count;
		tristrip->face_count = _hoops_IPRI->face_count;
		tristrip->_hoops_RPRCP = _hoops_PAACP;
		tristrip->_hoops_GPPPI = false;
		tristrip->_hoops_GSCP = (Polyhedron*)_hoops_IPRI;
		tristrip->bounding = _hoops_IPRI->bounding;
		tristrip->_hoops_PAGI = null;
		tristrip->_hoops_PCHA = null;
		tristrip->_hoops_HCHA = null;
		tristrip->_hoops_GSAI = _hoops_GSAI;

		if (tristrip->_hoops_GSSH->_hoops_CCHA && !BIT(dc->flags, _hoops_GPHHP))
			_hoops_CARI |= _hoops_HPCGP;
		tristrip->_hoops_CARI = _hoops_CARI;		

		//_hoops_CRHH->_hoops_APSCC = _hoops_CSPH->_hoops_APSCC;

		_hoops_RCGPS = tristrip->face_attributes.flags & _hoops_PIHIH;

		if (ANYBIT (_hoops_IGGCS | tristrip->_hoops_CPGPR | dc->_hoops_RIIAP & tristrip->_hoops_SPGPR,
					_hoops_ICHPA | _hoops_CPPGP) &&
			!BIT (_hoops_RCGPS, _hoops_RGIHR) &&
			(BIT (_hoops_RCGPS, _hoops_IAGI) ||
			 (_hoops_CIPSH && !BIT (_hoops_RCGPS, _hoops_HSIPR)))) {


			if (BIT (_hoops_RCGPS, _hoops_HAGI) &&
					_hoops_RAGCS.pattern != tristrip->face_attributes.pattern ||
				!BIT (_hoops_RCGPS, _hoops_HAGI) &&
					_hoops_RAGCS.pattern != inr->_hoops_IHA->pattern) {
				_hoops_AHSIS (nr, &tristrip->face_attributes);
				_hoops_RAGCS = tristrip->face_attributes;
			}

#ifndef _hoops_SGRCP
			if (_hoops_HGGCS &&
				BIT (tristrip->face_attributes.flags, _hoops_IARHR) &&
				!ANYBIT (tristrip->face_attributes.flags, _hoops_PARHR | _hoops_CARHR)) {
				if (nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR->length == 0) {
					HD_Report_Null_Color_Map ("tristrip", nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR);
				}
				else if (ANYBIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_FACES)) {
					_hoops_GPRH(tristrips) += tristrip->_hoops_PHHA;

					tristrip->_hoops_HCHA = _hoops_SPRI->_hoops_IGHIR;
					_hoops_GAIGH (nr, tristrip);
				}
			}
			else
#endif
			if (_hoops_PAACP &&
				ANYBIT (tristrip->face_attributes.flags, _hoops_PGSII)) {
				/*-- _hoops_IHASR-_hoops_AAGCS --*/
				if (!BIT(nr->_hoops_ARA->_hoops_IHRH.options, _hoops_CHRH) &&
					!ANYBIT (tristrip->face_attributes.flags, _hoops_CARHR | _hoops_IARHR)) {
					/*-- _hoops_HCSRH _hoops_RISIS _hoops_IHASR-_hoops_CARRI-_hoops_CASIS --*/
					tristrip->_hoops_PCHA = _hoops_SPRI->fcolors;
				}
				else {
					/*-- _hoops_AAGCS, _hoops_HGRIR _hoops_PAGCS _hoops_RISIS --*/
					if (!BIT (tristrip->_hoops_SRHA, _hoops_GAHH)) {
						if (nr->_hoops_IRR->_hoops_GAHA == Display_List_SEGMENT) {
							_hoops_ISAI (tristrip);
							tristrip = _hoops_HSSIS (tristrip);
						}
						else {
							_hoops_HCSHS |= _hoops_PIPI;
						}
					}
					_hoops_PHACP (nr, tristrip, _hoops_SPRI);
					//_hoops_RPP _hoops_RGR _hoops_ACSRA _hoops_SAGGR _hoops_RHHR, _hoops_RH _hoops_GGAS _hoops_HPGR _hoops_RH _hoops_PRPC _hoops_IIGR _hoops_RH _hoops_HAPR _hoops_GRS _hoops_RRP _hoops_HHH _hoops_IPHR.
					ASSERT (!BIT (tristrip->_hoops_RAHH, _hoops_PIPI));  
					tristrip->_hoops_SRHA |= DL_TEMPORARY_DATA;
				}

				if (nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR > 0 ||
					nr->_hoops_IHA->_hoops_CHA->_hoops_ARIR) {
					_hoops_GPRH(tristrips) += tristrip->_hoops_PHHA;
					_hoops_HPHCP (nr, tristrip);
				}
				else
					dc->_hoops_GSGC |= _hoops_GCGI;
			}
			else {
				/*-- _hoops_CRPIS-_hoops_HAGCS --*/
				Display_Context alter *		ldc = (Display_Context alter *)dc;
				bool						_hoops_ARRGH = false;
				bool						_hoops_IAGCS= false;
				bool						_hoops_ARIR;
				int							_hoops_CAGCS;

				_hoops_CAGCS = (_hoops_HAGI);

				_hoops_ARIR = nr->_hoops_IHA->_hoops_CHA->_hoops_ARIR || 
								nr->_hoops_IHA->_hoops_GIA->_hoops_ARIR;

				if (_hoops_ARIR ||
					nr->_hoops_IHA->_hoops_GIA != nr->_hoops_IHA->_hoops_CHA) {
					_hoops_CAGCS |= (LFA_EXPLICIT_COLOR_BY_VALUE|LFA_EXPLICIT_COLOR_BY_FINDEX);
				}
				else if (BIT (tristrip->face_attributes.flags, LFA_EXPLICIT_COLOR_BY_FINDEX)) {	

					if (BIT(dc->flags, _hoops_HSAGR)) {
						bool		_hoops_SCSIS = false;
						RGB			_hoops_SAGCS;

						if (_hoops_CCSIS (nr, &tristrip->face_attributes, &_hoops_SCSIS, &_hoops_SAGCS)) {
							if (_hoops_SCSIS) {
								if (tristrip->total * 100 < tristrip->face_count) {
									Tristrip *_hoops_GPGCS = _hoops_CSSIS (dc->_hoops_RIGC, tristrip);
									_hoops_ISAI (tristrip);
									tristrip = _hoops_GPGCS;
							}

								if (!BIT (tristrip->_hoops_RAHH, _hoops_SHRI) ||
									tristrip->_hoops_PAGI == null) {
									ALLOC_ARRAY_CACHED (tristrip->_hoops_PAGI, tristrip->face_count, RGB);
									tristrip->_hoops_RAHH |= _hoops_SHRI;
								}
								for (int i = 0; i < tristrip->face_count; i++)
									tristrip->_hoops_PAGI[i] = _hoops_SAGCS;
								tristrip->_hoops_SRHA |= _hoops_CAGI;
							}
							else
								_hoops_IAGCS = true;
						}
					}	
					else
						_hoops_CAGCS |= LFA_EXPLICIT_COLOR_BY_FINDEX;
				}
				else if (BIT (_hoops_RAGCS.flags, LFA_EXPLICIT_COLOR_BY_FINDEX)) {
					_hoops_IAGCS = true;
				}

				if (BIT (HOOPS_WORLD->_hoops_IRARR, _hoops_AACHR))
					_hoops_IAGCS = true;

				if (_hoops_IAGCS ||
					!_hoops_SAGI (_hoops_RAGCS, tristrip->face_attributes, _hoops_CAGCS)) {
					_hoops_RRCC *	_hoops_RPGCS;

					_hoops_AHSIS (nr, &tristrip->face_attributes);
					_hoops_RAGCS = tristrip->face_attributes;

					/* _hoops_GHCA _hoops_RRP _hoops_IS _hoops_CCIH _hoops_HH _hoops_GRPAR */
					_hoops_RPGCS = _hoops_RRSIS (nr, _hoops_IPRI);

					/* _hoops_RH _hoops_HGRH _hoops_RPHR _hoops_ARI _hoops_HRGR _hoops_IGPHR _hoops_PGGA _hoops_GRPHR _hoops_SGH _hoops_PAII
					 * _hoops_CRHH-_hoops_GRGCS _hoops_IS _hoops_GACC _hoops_RIPHR _hoops_PAII _hoops_GPHA _hoops_ASGA.
					 */
					if (_hoops_SPRI->normals == null &&
						/* _hoops_RRP _hoops_CIGGR _hoops_GSSR _hoops_IH _hoops_RHPS */ 
						_hoops_RPGCS->_hoops_CCHA != null && 
						ALLBITS (_hoops_RPGCS->_hoops_SCAI, _hoops_GGASP|_hoops_PSRSP)) {
						/* _hoops_HSGIR _hoops_CCA _hoops_GPHA _hoops_ASGA */
						_hoops_GPRH(_hoops_RHRGH) += HI_Assemble_3D_Tristrips ((Polyhedron alter *) _hoops_IPRI,
																		  _hoops_PIHIH, true);

						_hoops_HSCIS (_hoops_IHCR, _hoops_IPRI);
					}

#ifndef DISABLE_EXTENDED_TEXTURE
					if (ALLBITS (_hoops_RPGCS->_hoops_SCAI, _hoops_GGASP|_hoops_PSRSP)) {
						_hoops_RSSH *		params = _hoops_SPRI->_hoops_PPHIR;
						Vector const *	normals = _hoops_SPRI->normals;
						int				point_count = _hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR;

						/* _hoops_GHAP _hoops_RHCA _hoops_RGR _hoops_HHS _hoops_SHH _hoops_IGI _hoops_SSPP */
						/* _hoops_RPP _hoops_RH _hoops_ASGA _hoops_IIP _hoops_HGCR _hoops_AHAPI */
						/* _hoops_IH _hoops_HA _hoops_SR _hoops_IRHH _hoops_IRS _hoops_IPS */
						_hoops_AIGA (normals, point_count*3, float, params);
						_hoops_AIGA (normals, point_count*3, float, _hoops_RPGCS->_hoops_CCHA);
													
						(_hoops_SSIC alter &)_hoops_SPRI->_hoops_SSCCC |= _hoops_ASRSP;
						(_hoops_SSIC alter &)_hoops_SPRI->_hoops_SSCCC &= ~_hoops_PSRSP;
						_hoops_RPGCS->_hoops_SCAI |= _hoops_ASRSP;
						_hoops_RPGCS->_hoops_SCAI &= ~_hoops_PSRSP;
					}
#endif

					_hoops_ISAI(tristrip->_hoops_GSSH);
					tristrip->_hoops_GSSH = _hoops_RPGCS;


					if (BIT (nr->_hoops_RCSHR, _hoops_AHIHP) &&
						!BIT (nr->current, _hoops_AHIHP)) {
						HD_Prepare_Geometry_Transparency (nr, "tristrip transparency");

						_hoops_ARRGH = true;
					}
				}
				else if (!BIT (_hoops_RRGH->locks.color, Color_FACE) ||
						 !BIT (_hoops_RRGH->locks._hoops_HAA[_hoops_IAA], M_DIFFUSE)) {
					if (BIT (tristrip->face_attributes.flags, LFA_EXPLICIT_COLOR_BY_VALUE)) {
						if (!BIT(nr->_hoops_ARA->_hoops_IHRH.options, _hoops_CHRH)) {
							tristrip->_hoops_PAGI = _hoops_CPRI->colors;
						}
						else {
							if (nr->_hoops_IRR->_hoops_GAHA == Display_List_SEGMENT) {
								_hoops_ISAI (tristrip);
								tristrip = _hoops_HSSIS (tristrip);
							}
							else {
								_hoops_HCSHS |= _hoops_SHRI;
							}
							_hoops_SISIS (nr, tristrip, _hoops_CPRI);
							//_hoops_RPP _hoops_RGR _hoops_ACSRA _hoops_SAGGR _hoops_RHHR, _hoops_RH _hoops_GGAS _hoops_HPGR _hoops_RH _hoops_PRPC _hoops_IIGR _hoops_RH _hoops_HAPR _hoops_GRS _hoops_RRP _hoops_HHH _hoops_IPHR.
							ASSERT (!BIT (tristrip->_hoops_RAHH, _hoops_SHRI));  
							tristrip->_hoops_SRHA |= DL_TEMPORARY_DATA;
						}
					}
				}

				if (nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR > 0 ||
					nr->_hoops_IHA->_hoops_CHA->_hoops_ARIR) {
					_hoops_RCCA(tristrips) += tristrip->_hoops_PHHA;
					_hoops_HPHCP (nr, tristrip);
#if 0
					_hoops_APGCS (nr, tristrip, _hoops_IPRI);
#endif
				}
				else
					dc->_hoops_GSGC |= _hoops_GCGI;

				if (_hoops_ARRGH)
					_hoops_HGSGA (ldc, "tristrip transparency");
			}
		}

		_hoops_SSAGR(_hoops_AGGCS);

		if (_hoops_ISAI (tristrip) == 0) {
			HI_Free_Tristrip (tristrip);
		}
		else {
			if (BIT (_hoops_HCSHS, _hoops_PIPI)) {
				if (!BIT (tristrip->_hoops_RAHH, _hoops_PIPI))
					tristrip->_hoops_PCHA = null;
			}
			if (BIT (_hoops_HCSHS, _hoops_SHRI)) {
				if (!BIT (tristrip->_hoops_RAHH, _hoops_SHRI))
					tristrip->_hoops_PAGI = null;
			}
			_hoops_HCSHS = 0;
		}
	} while ((tristrip = _hoops_AGGCS) != null);

	if (_hoops_ISAI (_hoops_HAPAR) == 0)
		HI_Free_Texture_Parameters (_hoops_HAPAR);

	if (_hoops_SCSCC) {
		Display_Context alter *		_hoops_AAHCP = (Display_Context alter *)dc;

		FREE_ARRAY_ALIGNED(_hoops_AAHCP->_hoops_CGHAR, _hoops_AAHCP->_hoops_ICACP, int, 16);
		_hoops_AAHCP->_hoops_ICACP = 0;
		_hoops_AAHCP->_hoops_CGHAR = null;
	}

	return node;
}



local bool _hoops_CAGPS (
	Net_Rendition const &			nr,
	Polyhedron const *				_hoops_IPRI) {
	_hoops_GRA const &		_hoops_RRA = nr->_hoops_ARA;

	if (_hoops_RRA->_hoops_CICP.scale != _hoops_IPRI->_hoops_GIHIR.scale ||
		_hoops_RRA->_hoops_CICP.translate != _hoops_IPRI->_hoops_GIHIR.translate)
		return true;

	if (_hoops_RRA->_hoops_ACP._hoops_RSCRP != _hoops_IPRI->_hoops_GIHIR._hoops_RSCRP ||
		_hoops_RRA->_hoops_ACP._hoops_CIAIR != _hoops_IPRI->_hoops_GIHIR._hoops_CIAIR)
		return true;

	if (!EQUAL_MEMORY (_hoops_RRA->_hoops_ACP._hoops_SIAIR, _hoops_RRA->_hoops_ACP._hoops_CIAIR * sizeof(float),
						_hoops_IPRI->_hoops_GIHIR._hoops_SIAIR))
		return true;

	return false;
}

GLOBAL_FUNCTION void HD_Assemble_Isolines (
	Net_Rendition const & 			nr,
	Polyhedron const *				_hoops_IPRI,
	_hoops_SARHR			_hoops_PIHIH) {
	Display_Context alter *			dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_CIGA const &			_hoops_SIGA = nr->_hoops_IHA;
	_hoops_GRGH const &			_hoops_RRGH = nr->_hoops_IRR;
	_hoops_GRA const &		_hoops_RRA = nr->_hoops_ARA;
	_hoops_HHCR const &		_hoops_IHCR = nr->transform_rendition;
	Local_Vertex_Attributes const *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;
	Local_Face_Attributes const *	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;
	Tristrip *						tristrip;
	Tristrip alter *				_hoops_AGGCS = null;
	Vector const *					_hoops_ICHA = null;
	_hoops_ARPA const *					_hoops_PRHH = null;

	// _hoops_APRI _hoops_GII _hoops_RHGS _hoops_ACGC
	HI_Free_Polyedge_List (_hoops_IPRI->_hoops_CHGPR);
	((Polyhedron alter *)_hoops_IPRI)->_hoops_CHGPR = null;
	((Polyhedron alter *)_hoops_IPRI)->_hoops_AHSCC = 0;

	// _hoops_ASGGR _hoops_HGAGA / _hoops_RGAP

	if (BIT (_hoops_IHCR->flags, _hoops_GRHH) && BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES) &&
		_hoops_SIGA->_hoops_AGP != null &&
		ANYBIT (_hoops_RRGH->_hoops_CSA, _hoops_SSA|_hoops_GGP|_hoops_IIRAP) &&
		!BIT (_hoops_IPRI->polyhedron_flags, PHF_VERTEX_NORMALS_VALID)) {
		/* _hoops_HSGIR _hoops_CCA _hoops_GPHA _hoops_ASGA */
		_hoops_RCCA(_hoops_RHRGH) += HI_Assemble_3D_Tristrips ((Polyhedron alter *) _hoops_IPRI,
															 _hoops_PIHIH, true);
		_hoops_HSCIS (_hoops_IHCR, _hoops_IPRI);
	}
	else if (!ALLBITS (_hoops_IPRI->_hoops_ACRHR, _hoops_PIHIH)) {
		/* _hoops_HSGIR _hoops_SIHH _hoops_GPHA _hoops_ASGA */
		_hoops_RCCA(_hoops_RHRGH) += HI_Assemble_3D_Tristrips ((Polyhedron alter *) _hoops_IPRI,
															 _hoops_PIHIH, false);
		_hoops_HSCIS (_hoops_IHCR,(Polyhedron alter *)_hoops_IPRI);
	}
	else if (ANYBIT (_hoops_IPRI->_hoops_CPGPR, _hoops_AHSGA|_hoops_CASIR)) {
		/* _hoops_CCGI _hoops_RPGAH _hoops_IHRI, _hoops_HIH _hoops_CPHP _hoops_HGAS.	_hoops_GAAP _hoops_CPHP _hoops_PII
		   _hoops_GPHA _hoops_PSHA, _hoops_PGAP _hoops_PSP _hoops_RPIP _hoops_HRCI _hoops_IIRGR (_hoops_CR _hoops_SR _hoops_PAH
		   _hoops_PSP _hoops_RPIP _hoops_SHH _hoops_RCRR _hoops_IIGR _hoops_SSRHR _hoops_CAPR _hoops_HII _hoops_RH _hoops_SCRPA)
		*/
		Polyhedron alter *	_hoops_HPGPR = (Polyhedron alter *)_hoops_IPRI;

		if (BIT (_hoops_HPGPR->polyhedron_flags, _hoops_CCRHR))
			HI_Resort_Tristrips (_hoops_HPGPR, -1);

		HI_Reset_Strip_Flags (_hoops_HPGPR);
		_hoops_HPGPR->_hoops_CPGPR &= ~_hoops_AHSGA;
	}
	else if (BIT (_hoops_IPRI->polyhedron_flags, _hoops_CCRHR))
		HI_Resort_Tristrips ((Polyhedron alter *)_hoops_IPRI, -1);

	((Polyhedron alter *)_hoops_IPRI)->polyhedron_flags &= ~_hoops_CCRHR;


	if ((tristrip = _hoops_IPRI->tristrips) == null)
		return;


	bool		_hoops_PRGCS = !ANYBIT (_hoops_RRGH->_hoops_CSA,
										 _hoops_IIRAP|_hoops_GGP|_hoops_SSA);

	if (!BIT (_hoops_IHCR->flags, _hoops_GRHH) || !BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES) ||
		_hoops_SIGA->_hoops_AGP == null) {
		/*-- _hoops_GRAPR _hoops_CRIRC --*/
		_hoops_PRHH = null;
		_hoops_ICHA = null;
	}
	else if (_hoops_PRGCS) {
		/*--- _hoops_CRPIS _hoops_CRIRC ---*/
		if (!ALLBITS (_hoops_IPRI->polyhedron_flags,
					  PHF_FACE_NORMALS_VALID|_hoops_ASAHR)) {
			HI_Assemble_Face_Normals ((Polyhedron alter *) _hoops_IPRI);
			_hoops_HSCIS(_hoops_IHCR, (Polyhedron alter *)_hoops_IPRI);
		}
		_hoops_PRHH = _hoops_CPRI->normals;
		_hoops_ICHA = null;
	}
	else {
		_hoops_PRHH = null;
		if (!BIT (_hoops_IPRI->polyhedron_flags, PHF_VERTEX_NORMALS_VALID))
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Vertex normals undone");
		_hoops_ICHA = _hoops_SPRI->normals;
	}


	do {
		_hoops_AGGCS = tristrip->next;

		if (tristrip->_hoops_HSAI > 1) {
			tristrip = _hoops_HSSIS (tristrip);
		}
		else {
			if (ANYBIT (tristrip->_hoops_RAHH, _hoops_RRCGP & ~_hoops_AAHH))
				_hoops_HCSIS (tristrip);
			_hoops_CAHS (tristrip);
			tristrip->_hoops_SRHA = 0;
			tristrip->_hoops_CARI = 0;
		}


		tristrip->points = _hoops_IPRI->points;
		tristrip->_hoops_PRHH = (_hoops_ARPA alter *)_hoops_PRHH;
		tristrip->_hoops_ICHA = (Vector alter *)_hoops_ICHA;
		tristrip->point_count = _hoops_IPRI->point_count;
		tristrip->face_count = _hoops_IPRI->face_count;
		tristrip->_hoops_RPRCP = true;
		tristrip->_hoops_GPPPI = false;
		tristrip->_hoops_GSCP = (Polyhedron *)_hoops_IPRI;
		tristrip->bounding = _hoops_IPRI->bounding;
		tristrip->_hoops_PAGI = null;
		tristrip->_hoops_PCHA = null;
		tristrip->_hoops_HCHA = null;
		tristrip->_hoops_GSAI = 0;


		if (BIT (tristrip->face_attributes.flags, _hoops_IARHR) &&
			!ANYBIT (tristrip->face_attributes.flags, _hoops_PARHR | _hoops_CARHR)) {
			if (nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR->length == 0) {
				HD_Report_Null_Color_Map ("tristrip", nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR);
			}
			else {
				tristrip->_hoops_HCHA = _hoops_SPRI->_hoops_IGHIR;
				HD_Isoline_From_Tristrip (nr, tristrip);
			}
		}

		_hoops_ISAI (tristrip);
		if (tristrip->_hoops_HSAI == 0)
			HI_Free_Tristrip (tristrip);
	} while ((tristrip = _hoops_AGGCS) != null);


	// _hoops_HPIRA _hoops_IPCGP _hoops_RGAP
	Polyhedron alter *			_hoops_HPGPR = (Polyhedron alter *)_hoops_IPRI;
	float						tolerance = _hoops_HPGPR->bounding->sphere.radius * 0.001f;

	_hoops_HPGPR->_hoops_AHSCC =
		HD_Process_Isolines (dc, _hoops_IPRI, _hoops_IPRI->bounding, (Polyedge **)&_hoops_IPRI->_hoops_CHGPR, tolerance);

	_hoops_HPGPR->polyhedron_flags |= _hoops_SCRRA;

	if (_hoops_HPGPR->_hoops_GIHIR._hoops_CIAIR > 0)
		FREE_ARRAY (_hoops_HPGPR->_hoops_GIHIR._hoops_SIAIR, _hoops_HPGPR->_hoops_GIHIR._hoops_CIAIR, float);
	_hoops_HPGPR->_hoops_GIHIR.scale = _hoops_RRA->_hoops_CICP.scale;
	_hoops_HPGPR->_hoops_GIHIR.translate = _hoops_RRA->_hoops_CICP.translate;
	_hoops_HPGPR->_hoops_GIHIR._hoops_RSCRP = _hoops_RRA->_hoops_ACP._hoops_RSCRP;
	_hoops_HPGPR->_hoops_GIHIR._hoops_CIAIR = _hoops_RRA->_hoops_ACP._hoops_CIAIR;
	_hoops_APRGA (_hoops_RRA->_hoops_ACP._hoops_SIAIR, _hoops_HPGPR->_hoops_GIHIR._hoops_CIAIR, float, _hoops_HPGPR->_hoops_GIHIR._hoops_SIAIR);
}

local void _hoops_PPGCS (
	Net_Rendition const &nr,
	_hoops_IAHPR *_hoops_HPHCR,
	bool alter *_hoops_SCSIS,
	RGB alter *_hoops_GSSIS) 
{
	int index = (int)_hoops_HPHCR->findex;

	*_hoops_SCSIS = false;
	_hoops_CAHHP const &	_hoops_SAHHP = nr->_hoops_ASIR->_hoops_PSIR;
	if (_hoops_SAHHP->length) {
		index = index % _hoops_SAHHP->length;
		Named_Material *_hoops_GASPA = &_hoops_SAHHP->_hoops_CSIR->_hoops_HAA[index];
		if (!ANYBIT (_hoops_GASPA->_hoops_PRGRA, ~(M_DIFFUSE|_hoops_RHGRA))) {
			if (_hoops_HPHCR->findex == index) {
				*_hoops_SCSIS = true;
				*_hoops_GSSIS = _hoops_GASPA->_hoops_CSHR;
			}
			else {
				bool _hoops_SIAIS = false;

				_hoops_SIAIS = ALLBITS (nr->_hoops_IRR->_hoops_CSA,
					((_hoops_HIRC | _hoops_PHGI) & ~_hoops_AHGI));

				_hoops_AHAH _hoops_SHAIS;
				_hoops_ICRCP (_hoops_SAHHP->_hoops_CSIR, _hoops_HPHCR->findex, *_hoops_GSSIS, _hoops_SIAIS, _hoops_SHAIS);
				*_hoops_SCSIS = true;
			}
		}
	}
}

local INLINE Polyedge alter *_hoops_HPGCS (Polyedge const *polyedge)
{
	Polyedge *	_hoops_AHPIS;

	ZALLOC (_hoops_AHPIS, Polyedge);
	*_hoops_AHPIS = *polyedge;
	_hoops_ICAI (_hoops_AHPIS);
	_hoops_AHPIS->_hoops_RAHH = _hoops_CGCGP;

	_hoops_AHPIS->_hoops_SCGHR = polyedge;
	_hoops_CAHS (polyedge);

	_hoops_AHPIS->_hoops_GAHA = null;
	_hoops_AHPIS->_hoops_SRHA |= DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS|_hoops_GAHH;
	_hoops_AHPIS->_hoops_SRHA &= ~DL_HAS_TRANSPARENCY;

	return _hoops_AHPIS;
}


local _hoops_SGRGH alter * _hoops_IPGCS (
	Net_Rendition const & 			inr,
	_hoops_SGRGH alter *			node,
	Color_Object					_hoops_GSSCC,
	Polyhedron const *				_hoops_IPRI) {
	Display_Context alter *			dc = (Display_Context alter *)inr->_hoops_SRA;
	_hoops_GRGH const &			_hoops_RRGH = inr->_hoops_IRR;
	Line_Rendition const &			_hoops_GHP = inr->_hoops_RHP;
	Local_Vertex_Attributes const *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;
	Local_Face_Attributes const *	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;
	Polyedge *						_hoops_ACP;
	Polyedge alter *				_hoops_RHPIS = null;
	Activity						_hoops_IGGCS;
	_hoops_GHHPR				_hoops_CPGCS;
	_hoops_ACHR						_hoops_CIPSH;
	unsigned int					_hoops_SRHA = 0;
	unsigned int					_hoops_CARI = 0;
	unsigned int					_hoops_GSAI = 0;

	if (1 /* _hoops_GIIS == _hoops_IRAP || _hoops_GIIS->_hoops_IPCGP == _hoops_IRAP */) {
		bool							_hoops_SGGCS;
		bool							_hoops_CGGCS = false;

		// _hoops_PAGA: _hoops_SPGCS _hoops_GPP _hoops_AHAR
		_hoops_CIPSH = _hoops_RRGH->_hoops_AARIP & T_FACES;

		_hoops_SGGCS = false;
		if (BIT (_hoops_RRGH->locks._hoops_RGP, T_FACES)) {
			if (_hoops_CIPSH) {
				if (_hoops_IPRI->face_count > 0) {
					_hoops_SGGCS = true;
					_hoops_CGGCS = true;
				}
			}
		}
		else {
			if (_hoops_CIPSH) {
				if (_hoops_IPRI->face_count > _hoops_CPRI->_hoops_SIIPR)
					_hoops_SGGCS = true;
			}
			else {
				if (_hoops_CPRI->_hoops_CPIAA > 0)
					_hoops_SGGCS = true;
			}
		}

		if (!_hoops_SGGCS)
			return null;

		_hoops_CPGCS = _hoops_SHHPR |
								_hoops_RPGI |
								_hoops_SSRRA |
								_hoops_SCICA | _hoops_GPGI;


		/* _hoops_RGR _hoops_RPGP _hoops_PAHH _hoops_IRHS _hoops_IS _hoops_PCR _hoops_ACSRR _hoops_SASI _hoops_CPRC _hoops_HRP -- 2 _hoops_SGHC _hoops_CCA _hoops_HAGH
			_hoops_PAIA, _hoops_SGGGH, _hoops_PAR _hoops_HISI _hoops_SIAS _hoops_GHGCS _hoops_GPP _hoops_RH _hoops_PSHR _hoops_RRCPR
		 */
		if (BIT (dc->_hoops_CPGPR, _hoops_PIPGP) || !BIT (_hoops_IPRI->polyhedron_flags, _hoops_SCRRA) ||
			_hoops_CAGPS (inr, _hoops_IPRI)) {
			_hoops_SARHR			_hoops_PIHIH;

			// _hoops_ASGGR _hoops_HGAGA / _hoops_RGAP
			_hoops_PIHIH = _hoops_PPRHR | _hoops_IACHR;
			if (!_hoops_CGGCS) {
				if (_hoops_CIPSH)
					_hoops_PIHIH |= _hoops_HSIPR;
				else
					_hoops_PIHIH |= _hoops_HRAPA;
			}

			HD_Assemble_Isolines (inr, _hoops_IPRI, _hoops_PIHIH);

			if (_hoops_IPRI->_hoops_CHGPR == null)
				return node;
		}



		bool				_hoops_ARPSH;
		bool				_hoops_SPGI;
		bool				_hoops_CRRS = false;
		bool				_hoops_RHGCS;

		UNREFERENCED (_hoops_GSSCC); //_hoops_RHAP _hoops_RGR _hoops_RCPS _hoops_CRGR _hoops_HPSI _hoops_ARI??
		_hoops_ARPSH = (_hoops_SPRI->_hoops_RCRHR != 0 ||
						_hoops_SPRI->_hoops_SIRHR != 0 ||
						_hoops_CPRI->_hoops_HSRRA);
		_hoops_SPGI = BIT (_hoops_RRGH->locks.color, Color_FRONT) &&
						 BIT (_hoops_RRGH->locks._hoops_HAA[_hoops_IAA], M_DIFFUSE);


		_hoops_RHGCS = !BIT(_hoops_GHP->line_style->flags, LSF_SOLID);// || _hoops_AHGCS->_hoops_PHGCS;

		/* _hoops_CGP _hoops_IIH _hoops_CSAP _hoops_IRS _hoops_CAPGR _hoops_ARP _hoops_PAR _hoops_RPP _hoops_RH _hoops_RHPP _hoops_AASA _hoops_CSAP _hoops_RASA _hoops_CCA _hoops_HHGCS,
		 * _hoops_SR _hoops_CGH _hoops_IGGRA _hoops_GAR _hoops_PHRI _hoops_AIRI _hoops_CPCI _hoops_AAPR _hoops_GRGR */
		_hoops_CRRS =
			_hoops_RRGH->_hoops_GAHA &&
			inr->_hoops_RSGC->action.draw_3d_isoline == nullroutine &&
			dc->_hoops_IPCI->draw_3d_polyedge != HD_Std_3D_Polyedge;

		/* _hoops_SCH _hoops_HRGR _hoops_SAPIA _hoops_SGS _hoops_RGR _hoops_RIS _hoops_RCPS _hoops_RAS _hoops_RH _hoops_CSHS _hoops_HGSR _hoops_ARRS, _hoops_HIS _hoops_SGS 
		 * _hoops_IPHR _hoops_HRGR _hoops_CPHR _hoops_PRGI _hoops_RPP _hoops_SR _hoops_RSGR _hoops_GH _hoops_HHPHR _hoops_IS _hoops_IHGCS (_hoops_CAS _hoops_SR _hoops_SIAS) _hoops_HGGC
		 * _hoops_RRP _hoops_IS _hoops_GRAS _hoops_PPR _hoops_PGSA (_hoops_RAR-_hoops_AAR) _hoops_ASSIA _hoops_SPPR. */

		if (_hoops_CRRS) {
			bool						_hoops_SSAIS;

			_hoops_SSAIS = BIT(_hoops_RRGH->_hoops_PPH, _hoops_HAI);

			_hoops_CARI |= _hoops_RCRI;

			if (_hoops_RHGCS)
				_hoops_SRHA |= DL_PATTERN;

			if (_hoops_ARPSH) {
				_hoops_SRHA |= DL_VCOLORED_TRISTRIP;
				if (_hoops_SSAIS)
					_hoops_SRHA |= DL_LOCAL_GRAYSCALE;
				if (_hoops_SPGI) 
					_hoops_SRHA |= _hoops_IIRC;
			}
			if (BIT (inr->_hoops_PSGI, T_EDGES) &&
				inr->_hoops_CPP->_hoops_PRH.style != _hoops_GCPI)
				_hoops_SRHA |= DL_HAS_TRANSPARENCY;
		}
	}
#if 0
	else {
		node->_hoops_GGSIS();
		_hoops_ACP = node->_hoops_ACP;
		node->_hoops_ACP = null;

		_hoops_CPGCS = node->_hoops_CPGCS;
		_hoops_CIPSH = node->_hoops_CIPSH;
		_hoops_SRHA = node->_hoops_SRHA;
		_hoops_CARI = node->_hoops_CARI;
		_hoops_GSAI = node->_hoops_GSAI;
	}
#endif

	if ((_hoops_ACP = _hoops_IPRI->_hoops_CHGPR) == null)
		return node;


	_hoops_IGGCS = dc->_hoops_CPGPR | _hoops_IPRI->_hoops_CPGPR | dc->_hoops_RIIAP & _hoops_IPRI->_hoops_SPGPR;

	do {
		Net_Rendition		 		nr = inr;

		_hoops_RHPIS = _hoops_ACP->next;


		if (_hoops_ACP->_hoops_HSAI > 1 && !BIT(_hoops_ACP->_hoops_CARI, _hoops_SARI) ||
			!nr->_hoops_ARA->_hoops_ACP._hoops_PCP &&
				(_hoops_ACP->_hoops_ICHA != null || _hoops_ACP->_hoops_RSHA != null)) {
			_hoops_ACP = _hoops_HPGCS (_hoops_ACP);
			if (!nr->_hoops_ARA->_hoops_ACP._hoops_PCP) {
				_hoops_ACP->_hoops_ICHA = null;
				_hoops_ACP->_hoops_RSHA = null;
			}
		}
		else {
			_hoops_CAHS (_hoops_ACP);
		}


		_hoops_ACP->_hoops_GSCP = (Polyhedron *)_hoops_IPRI;
		_hoops_ACP->bounding = _hoops_IPRI->bounding;
		_hoops_ACP->_hoops_GSAI = _hoops_GSAI;
		_hoops_ACP->_hoops_SRHA |= _hoops_SRHA;
		_hoops_ACP->_hoops_CARI |= _hoops_CARI;

		if (BIT(dc->flags, _hoops_HSAGR)) {
			_hoops_GRA const &_hoops_RRA = nr->_hoops_ARA;
			bool _hoops_SCSIS = false;
			RGB _hoops_SAGCS;
			int i;

			if (_hoops_RRA->_hoops_ACP._hoops_GCAIR == 0 &&
				_hoops_RRA->_hoops_ACP.weight_count == 0 && 
				_hoops_RRA->_hoops_ACP._hoops_RCAIR == 0) {
				_hoops_PPGCS (nr, &_hoops_ACP->_hoops_PPGI, &_hoops_SCSIS, &_hoops_SAGCS);
				if (_hoops_SCSIS) {
					if (!BIT (_hoops_ACP->_hoops_RAHH, _hoops_PCGHR) ||
						_hoops_ACP->_hoops_ASHA == null) {
						ALLOC_ARRAY (_hoops_ACP->_hoops_ASHA, _hoops_ACP->_hoops_SPHA, RGB);
						_hoops_ACP->_hoops_RAHH |= _hoops_PCGHR;
					}
					for (i = 0; i < _hoops_ACP->_hoops_SPHA; i++)
						_hoops_ACP->_hoops_ASHA[i] = _hoops_SAGCS;
					_hoops_ACP->_hoops_SRHA |= _hoops_CAGI;
				}
			}
			if (!_hoops_SCSIS)
				nr = HD_New_Local_Edge_Rendition ((Polyhedron *)_hoops_IPRI, nr, inr, &_hoops_ACP->_hoops_PPGI);

			if (nr->_hoops_RHP->_hoops_CHA->_hoops_IRIR > 0 ||
				nr->_hoops_RHP->_hoops_CHA->_hoops_ARIR) {
				_hoops_AAIGH (nr, _hoops_ACP);
			}
			else
				dc->_hoops_GSGC |= _hoops_RSRI;
		}
		else {
			if (ANYBIT (_hoops_IGGCS | _hoops_ACP->_hoops_CPGPR | dc->_hoops_RIIAP & _hoops_ACP->_hoops_SPGPR,
						_hoops_ICHPA | _hoops_CPPGP)) {
				nr = HD_New_Local_Edge_Rendition ((Polyhedron *)_hoops_IPRI, nr, inr, &_hoops_ACP->_hoops_PPGI);

				if (nr->_hoops_ARA->_hoops_ACP._hoops_PCP) {
					if (!BIT (nr->_hoops_RGP, T_LIGHTS_FOR_EDGES))
						nr->_hoops_RGP |= T_LIGHTS_FOR_EDGES;
				}
				else {
					if (BIT (nr->_hoops_RGP, T_LIGHTS_FOR_EDGES))
						nr->_hoops_RGP &= ~T_LIGHTS_FOR_EDGES;
				}


				if (nr->_hoops_RHP->_hoops_CHA->_hoops_IRIR > 0 ||
					nr->_hoops_RHP->_hoops_CHA->_hoops_ARIR) {
					_hoops_AAIGH (nr, _hoops_ACP);
				}
				else
					dc->_hoops_GSGC |= _hoops_RSRI;
			}
		}

		if (_hoops_ISAI (_hoops_ACP) == 0)
			HI_Free_Polyedge (_hoops_ACP);

#if 0
		if (_hoops_GGPGR(nr)) {
			if (node == null) {
				node = new (dc->memory_pool) _hoops_SGRGH (_hoops_IPRI);

				node->_hoops_CPGCS = _hoops_CPGCS;
				node->_hoops_CIPSH = _hoops_CIPSH;
				node->_hoops_SRHA = _hoops_SRHA;
				node->_hoops_CARI = _hoops_CARI;
				node->_hoops_GSAI = _hoops_GSAI;
			}
			node->_hoops_ACP = _hoops_RHPIS;
			node->_hoops_IGSIS();

			return node;
		}
#endif
	} while ((_hoops_ACP = _hoops_RHPIS) != null);


	return node;
}

/* _hoops_HHH _hoops_SGI _hoops_IH _hoops_AIRI _hoops_HIGR _hoops_PGAAP */
#define _hoops_ICAIS 0x8  /* _hoops_IRHS _hoops_IS _hoops_SHH _hoops_GIAH _hoops_HII _hoops_CCAIS */

local _hoops_SGRGH alter * _hoops_CHGCS (
	Net_Rendition const & 			inr,
	_hoops_SGRGH alter *			node,
	Color_Object					_hoops_GSSCC,
	Polyhedron const *				_hoops_IPRI) {
	Display_Context alter *			dc = (Display_Context alter *)inr->_hoops_SRA;
	_hoops_GRGH const &			_hoops_RRGH = inr->_hoops_IRR;
	_hoops_HHCR const &		_hoops_IHCR = inr->transform_rendition;
	Line_Rendition const &			_hoops_GHP = inr->_hoops_RHP;
	Local_Vertex_Attributes const *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;
	_hoops_RPGHR const *	lea = &_hoops_IPRI->_hoops_IHHPR;
	Polyedge *						polyedge;
	Polyedge alter *				_hoops_SHGCS = null;
	Vector const *					_hoops_ICHA;
	Vector const *					_hoops_RSHA;
	_hoops_RRCC				_hoops_HAPAR;
	Activity						_hoops_IGGCS;
	_hoops_GHHPR				_hoops_CPGCS;
	_hoops_ACHR						_hoops_CIPSH;
	int								_hoops_PGGCS = 0;
	unsigned int					_hoops_SRHA;
	unsigned int					_hoops_GSAI;
	bool							_hoops_PAACP;
	bool							_hoops_HGGCS;
	bool							_hoops_GIGCS = false;

	if (dc->_hoops_SHCI() == _hoops_GICI ||
		dc->_hoops_SHCI() == _hoops_RICI)
		return node;

	if (1 /* _hoops_GIIS == _hoops_IRAP || _hoops_GIIS->_hoops_ACRI == _hoops_IRAP */) {
		_hoops_ACHR					_hoops_PPGPS = _hoops_RRGH->locks._hoops_RGP;
		bool						_hoops_CGGCS = false;
		bool						_hoops_SGGCS;
		int							weight;

		if (_hoops_IPRI->type == _hoops_GSIP)
			_hoops_CIPSH = inr->_hoops_RGP & T_ANY_MESH_EDGE;
		else
			_hoops_CIPSH = inr->_hoops_RGP & T_ANY_SHELL_EDGE;

		if (BIT (_hoops_CIPSH, _hoops_GCSI) &&
			!ANYBIT (_hoops_IHCR->heuristics, _hoops_RSA)) {
			_hoops_CIPSH &= ~_hoops_GCSI;
			_hoops_CIPSH |= _hoops_CRHGP;
		}

		_hoops_SGGCS = false;
		if (ANYBIT (_hoops_PPGPS, T_ANY_EDGE)) {
			/* (_hoops_ASHS _hoops_GHCA _hoops_HAR _hoops_SHH _hoops_HSSPR _hoops_GAPR; _hoops_SGH _hoops_ACHAA _hoops_IS _hoops_HCGGS _hoops_SPPR) */
			if (_hoops_CIPSH) {
				if (_hoops_IPRI->face_count > 0) {
					_hoops_SGGCS = true;
					_hoops_CGGCS = true;
				}
			}
		}
		else {
			if (_hoops_IPRI->_hoops_SPHA < 0) {	/* _hoops_CCSHR? */
				if (_hoops_IPRI->face_count > 0 && _hoops_CIPSH) /* _hoops_PSCR _hoops_HPGR _hoops_CHGC _hoops_HPPR _hoops_SCH */
					_hoops_SGGCS = true;
			}
			else if (_hoops_CIPSH) {
				if (_hoops_IPRI->_hoops_SPHA > _hoops_IPRI->_hoops_IHHPR._hoops_SIIPR)
					_hoops_SGGCS = true;
			}
			else {
				if (_hoops_IPRI->_hoops_IHHPR._hoops_CPIAA > 0) {
					if (BIT(dc->flags, _hoops_RCHCP) ||
						dc->_hoops_SHCI() == _hoops_GAIIP ||
						dc->_hoops_SHCI() == _hoops_CRIIP &&
						BIT (inr->_hoops_ASIR->_hoops_GCCI.options, _hoops_RCCI))
						_hoops_SGGCS = true;
				}
			}
		}

		if (!_hoops_SGGCS)
			return node;

		_hoops_SSAGR (_hoops_IPRI->_hoops_SHGPR);
		_hoops_GHP._hoops_SSAGR();

		/* _hoops_PGSA _hoops_HHH _hoops_SPPR */

		_hoops_CPGCS = _hoops_SHHPR |
								_hoops_RPGI |
								_hoops_SSRRA |
								_hoops_SCICA | _hoops_GPGI;

		if (BIT (_hoops_CIPSH, T_GENERIC_EDGES)) {
			/* _hoops_IPCP _hoops_RGAR _hoops_AHAP _hoops_GCAS _hoops_IS _hoops_ISPR _hoops_HRGR _hoops_HHHA _hoops_PIGPS. */
			if (!_hoops_CGGCS)
				_hoops_CPGCS |= _hoops_AHIAA;
		}
		else {
			/* _hoops_ACHSP _hoops_HS _hoops_IS _hoops_ISPR _hoops_SRAPH _hoops_IIGR _hoops_CGSI */
			if (!_hoops_CGGCS)
				_hoops_CPGCS |= _hoops_APGI | _hoops_AHIAA;
			if (BIT (_hoops_CIPSH, T_PERIMETER_EDGES))
				_hoops_CPGCS |= _hoops_AACPR;
			if (BIT (_hoops_CIPSH, _hoops_CRHGP))
				_hoops_CPGCS |= _hoops_CCCPR;
			if (BIT (_hoops_CIPSH, T_MESH_QUAD_EDGES))
				_hoops_CPGCS |= _hoops_AGSPR;
			if (BIT (_hoops_CIPSH, T_HARD_EDGES))
				_hoops_CPGCS |= _hoops_CIIPR;
		}

#ifndef DISABLE_TEXTURING
		if (BIT (_hoops_RRGH->_hoops_CSA, (_hoops_RGAC & ~_hoops_AHGI)) &&
			_hoops_GHP->_hoops_CHA->_hoops_ARIR) {
			_hoops_HAPAR._hoops_CCHA = _hoops_SPRI->params;
			_hoops_HAPAR._hoops_GSHA = _hoops_SPRI->param_width;
		}
		else
#endif
		{
			_hoops_HAPAR._hoops_CCHA = null;
			_hoops_HAPAR._hoops_GSHA = 0;
		}
		_hoops_HAPAR._hoops_SCAI = 0;


		_hoops_SRHA = 0;
		_hoops_GSAI = 0;


		lea = &_hoops_IPRI->_hoops_IHHPR;

		if ((weight = _hoops_GHP->weight) < 0)
			weight = (int)(HD_Compute_Generic_Size (inr, _hoops_GHP->_hoops_PHP, _hoops_GHP->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
		if (weight == 0)
			weight = 1;

		if (BIT(dc->flags, _hoops_GPHHP)) {
			if (_hoops_IPRI->tristrips != null) {
				Polyedge alter *	polyedge;

				ZALLOC (polyedge, Polyedge);
				_hoops_ICAI (polyedge);

				polyedge->points = _hoops_IPRI->points;
				polyedge->point_count = _hoops_IPRI->point_count;
				polyedge->_hoops_SPHA = _hoops_IPRI->_hoops_SPHA;
				polyedge->bounding = _hoops_IPRI->bounding;
				polyedge->_hoops_GSCP = (Polyhedron*)_hoops_IPRI;
				polyedge->_hoops_SRHA = DL_POLYEDGE_FROM_TRISTRIP | DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS | _hoops_GAHH;

				if (dc->_hoops_IPCI->draw_3d_polyedge_from_tristrip != nullroutine)
					_hoops_IGCGH (inr, polyedge, _hoops_IPRI->tristrips);
				else
					HD_Std_3D_Polyedge_From_Tristrip (inr, polyedge, _hoops_IPRI->tristrips);

				HI_Free_Polyedge_List (polyedge);
			}

			return node;
		}

		if (BIT (HOOPS_WORLD->_hoops_HGGHR, _hoops_IGGHR) &&
			dc->_hoops_IPCI->draw_3d_polyedge_from_tristrip != nullroutine &&
			_hoops_IPRI->tristrips != null &&
			weight == 1 && !ANYBIT (_hoops_GHP->line_style->flags, LSF_COMPLEX_ANYBITS) &&
			ANYBIT (_hoops_CIPSH, T_GENERIC_EDGES|_hoops_CRHGP|_hoops_GCSI) &&
			((_hoops_CGGCS || lea->_hoops_SIIPR == 0) ||
			 (!_hoops_CGGCS && lea->_hoops_CPIAA == _hoops_IPRI->point_count)) &&
			 lea->_hoops_HSRRA == 0 &&
			 lea->_hoops_PSRRA == 0 &&
			 lea->_hoops_SRAPA == 0 &&
			 lea->_hoops_CCHHC == 0 &&
			 _hoops_HAPAR._hoops_CCHA == null) {
			/* _hoops_RARIR _hoops_GGAGA _hoops_ACRI */
			Polyedge alter *	polyedge;

			polyedge = _hoops_IPRI->_hoops_SHGPR;

			if (polyedge != null && !BIT (polyedge->_hoops_SRHA, DL_POLYEDGE_FROM_TRISTRIP)) {
				HI_Free_Polyedge_List (_hoops_IPRI->_hoops_SHGPR);
				polyedge = ((Polyhedron alter *)_hoops_IPRI)->_hoops_SHGPR = null;
			}

			if (polyedge == null) {
				ZALLOC (polyedge, Polyedge);
				_hoops_ICAI(polyedge);
				((Polyhedron alter *)_hoops_IPRI)->_hoops_SHGPR = polyedge;
			}

			_hoops_SRHA |= DL_POLYEDGE_FROM_TRISTRIP;
		}
		else if (!ALLBITS (_hoops_IPRI->_hoops_RSHPR, _hoops_CPGCS) ||
			BIT (_hoops_CPGCS, _hoops_CIIPR) &&
			inr->_hoops_ARA->_hoops_GCIPR != _hoops_IPRI->_hoops_GCIPR) {
			Polyhedron alter *	_hoops_HPGPR = (Polyhedron alter *)_hoops_IPRI;

			_hoops_RCCA(_hoops_RHRGH) += HI_Assemble_3D_Polyedges (_hoops_HPGPR,
									  _hoops_CPGCS,
									  inr->_hoops_ARA->_hoops_GCIPR);
			_hoops_HSCIS(_hoops_IHCR, _hoops_HPGPR);
		}
		else if (BIT (_hoops_IPRI->_hoops_CPGPR, _hoops_AHSGA)) {
			/* _hoops_AHHA _hoops_RPGAH _hoops_IHRI, _hoops_HIH _hoops_CPHP _hoops_HGAS.	_hoops_GAAP _hoops_CPHP _hoops_PII
			   _hoops_GPHA _hoops_PSHA, _hoops_PGAP _hoops_PSP _hoops_RPIP _hoops_HRCI _hoops_IIRGR (_hoops_CR _hoops_SR _hoops_PAH
			   _hoops_PSP _hoops_RPIP _hoops_SHH _hoops_RCRR _hoops_IIGR _hoops_SSRHR _hoops_CAPR _hoops_HII _hoops_RH _hoops_SCRPA)
			*/
			Polyhedron alter *	_hoops_HPGPR = (Polyhedron alter *)_hoops_IPRI;

			HI_Reset_Strip_Flags (_hoops_HPGPR);
			_hoops_HPGPR->_hoops_CPGPR &= ~_hoops_AHSGA;
		}

		if (_hoops_IPRI->_hoops_SHGPR &&
			_hoops_IPRI->_hoops_SHGPR->_hoops_PPGI.flags == 0) {
			Polyhedron alter *	_hoops_HPGPR = (Polyhedron alter *)_hoops_IPRI;
			HI_Reset_Strip_Flags (_hoops_HPGPR); 
		}


		if ((polyedge = (Polyedge alter *)_hoops_IPRI->_hoops_SHGPR) == null)
			return node;


		bool						_hoops_PRGCS;
		bool						_hoops_ARPSH;
		bool						_hoops_SPGI;
		bool						_hoops_RHGCS;
		bool						_hoops_CRRS;

		_hoops_PRGCS = !ANYBIT (_hoops_RRGH->_hoops_CSA, _hoops_HIRAP|_hoops_RCP|_hoops_GCP);
		_hoops_ARPSH = (BIT (_hoops_GSSCC, Color_EDGE) ||
						_hoops_SPRI->_hoops_SCHPR != 0 ||
						_hoops_SPRI->_hoops_CCHPR != 0);
		_hoops_SPGI = BIT (_hoops_RRGH->locks.color, Color_EDGE) &&
						 BIT (_hoops_RRGH->locks._hoops_HAA[_hoops_SAA], M_DIFFUSE);
		_hoops_RHGCS = !BIT(_hoops_GHP->line_style->flags,LSF_SOLID) || lea->_hoops_SRAPA;

		_hoops_PAACP = (BIT (_hoops_RRGH->_hoops_CSA,
									(_hoops_SSRC & ~_hoops_AHGI)) &&
							   _hoops_ARPSH && !_hoops_SPGI);
		_hoops_HGGCS = (BIT (_hoops_RRGH->_hoops_CSA,
									(_hoops_CSRC & ~_hoops_AHGI)) &&
							   _hoops_SPRI->_hoops_CCHPR != 0 && !_hoops_SPGI);

		if (!BIT (_hoops_IHCR->flags, _hoops_GRHH) ||
			!BIT (inr->_hoops_RGP, T_LIGHTS_FOR_EDGES) ||
			_hoops_GHP->_hoops_AGP == null) {
			/*-- _hoops_GRAPR _hoops_CRIRC --*/

			_hoops_RSHA = null;
			_hoops_ICHA = null;
		}
		else if (!ANYBIT (_hoops_RRGH->_hoops_CSA,
						  _hoops_GCP | _hoops_HIRAP)) {
			/*-- _hoops_CRPIS _hoops_CRIRC --*/

			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_GAAHR)) {
				HI_Assemble_Edge_Normals ((Polyhedron alter *) _hoops_IPRI);
				_hoops_HSCIS(_hoops_IHCR,(Polyhedron alter *)_hoops_IPRI);
			}
			_hoops_RSHA = lea->normals;
			_hoops_ICHA = null;
		}
		else {
			/*-- _hoops_SRPIS _hoops_CRIRC --*/

			if (!BIT(_hoops_IPRI->polyhedron_flags,PHF_VERTEX_NORMALS_VALID)) {
				_hoops_RCCA(_hoops_RHRGH) += HI_Assemble_3D_Tristrips ((Polyhedron alter *) _hoops_IPRI, false, true);
				_hoops_HSCIS(_hoops_IHCR,(Polyhedron alter *)_hoops_IPRI);
			}
			_hoops_ICHA = _hoops_SPRI->normals;
			_hoops_RSHA = null;
		}

		/* _hoops_CGP _hoops_IIH _hoops_CSAP _hoops_IRS _hoops_CAPGR _hoops_ARP _hoops_PAR _hoops_RPP _hoops_RH _hoops_RHPP _hoops_AASA _hoops_CSAP _hoops_RASA _hoops_CCA _hoops_HHGCS,
		 * _hoops_SR _hoops_CGH _hoops_IGGRA _hoops_GAR _hoops_PHRI _hoops_AIRI _hoops_CPCI _hoops_AAPR _hoops_GRGR */
		_hoops_CRRS =
			_hoops_RRGH->_hoops_GAHA &&
			inr->_hoops_RSGC->action.draw_3d_polyedge == nullroutine &&
			dc->_hoops_IPCI->draw_3d_polyedge != HD_Std_3D_Polyedge;

		/* _hoops_SCH _hoops_HRGR _hoops_SAPIA _hoops_SGS _hoops_RGR _hoops_RIS _hoops_RCPS _hoops_RAS _hoops_RH _hoops_CSHS _hoops_HGSR _hoops_ARRS, _hoops_HIS _hoops_SGS 
		 * _hoops_IPHR _hoops_HRGR _hoops_CPHR _hoops_PRGI _hoops_RPP _hoops_SR _hoops_RSGR _hoops_GH _hoops_HHPHR _hoops_IS _hoops_IHGCS (_hoops_CAS _hoops_SR _hoops_SIAS) _hoops_HGGC
		 * _hoops_RRP _hoops_IS _hoops_GRAS _hoops_PPR _hoops_PGSA (_hoops_RAR-_hoops_AAR) _hoops_ASSIA _hoops_SPPR. */

		if (_hoops_CRRS) {
			bool						_hoops_SSAIS;

			_hoops_SSAIS = BIT(_hoops_RRGH->_hoops_PPH, _hoops_HAI);

			if (_hoops_PRGCS)
				_hoops_SRHA |= DL_FLAT_LIGHTING;
			if (_hoops_RHGCS)
				_hoops_SRHA |= DL_PATTERN;
			if (_hoops_PAACP)
				_hoops_SRHA |= DL_COLOR_INTERPOLATION;
			if (_hoops_HGGCS)
				_hoops_SRHA |= DL_INDEX_INTERPOLATION;
			if (_hoops_SPRI->_hoops_CCHPR)
				_hoops_SRHA |= DL_COLORS_BY_FINDEX;
			if (_hoops_ARPSH) {
				_hoops_SRHA |= DL_VCOLORED_TRISTRIP;
				if (_hoops_SSAIS)
					_hoops_SRHA |= DL_LOCAL_GRAYSCALE;
				if (_hoops_SPGI) 
					_hoops_SRHA |= _hoops_IIRC;
			}
			if (BIT (inr->_hoops_PSGI, T_EDGES) &&
				inr->_hoops_CPP->_hoops_PRH.style != _hoops_GCPI)
				_hoops_SRHA |= DL_HAS_TRANSPARENCY;
			if (_hoops_GHP->_hoops_CHA->_hoops_ARIR && 
				BIT (_hoops_RRGH->_hoops_CSA, (_hoops_RGAC & ~_hoops_AHGI)))
				_hoops_SRHA |= DL_TEXTURING;

			_hoops_GSAI = (_hoops_RRGH->_hoops_CSA & _hoops_RHII);
			if (BIT (_hoops_IHCR->flags, _hoops_GRHH) && 
				BIT (inr->_hoops_RGP, T_LIGHTS_FOR_EDGES))
				_hoops_GSAI |= _hoops_ICAIS;
		}
	}
#if 0
	else {
		node->_hoops_RGSIS();
		polyedge = node->polyedge;
		node->polyedge = null;

		_hoops_ICHA = node->_hoops_ICHA;
		_hoops_RSHA = node->_hoops_RSHA;
		_hoops_HAPAR = node->_hoops_HAPAR;
		_hoops_CPGCS = node->_hoops_CPGCS;
		_hoops_CIPSH = node->_hoops_CIPSH;
		_hoops_PGGCS = node->_hoops_PGGCS;
		_hoops_SRHA = node->_hoops_SRHA;
		_hoops_GSAI = node->_hoops_GSAI;
		_hoops_PAACP = node->_hoops_PAACP;
		_hoops_HGGCS = node->_hoops_HGGCS;
	}
#endif

	_hoops_IAHPR			_hoops_RIGCS;
	int							_hoops_CAGCS;


	_hoops_SHSPR (_hoops_RIGCS);
	/* _hoops_ARP _hoops_GII _hoops_SR _hoops_PAH _hoops_CGIC _hoops_CPIIS */
	_hoops_RIGCS.pattern = 0;
	_hoops_RIGCS.line_style = _hoops_GHP->line_style;
	_hoops_RIGCS.weight = (float)_hoops_GHP->weight;
	_hoops_RIGCS.flags |= _hoops_IPHPR;

	_hoops_CAGCS = (_hoops_GPGI | _hoops_SCICA | _hoops_CCICA);

	_hoops_IGGCS = dc->_hoops_CPGPR | _hoops_IPRI->_hoops_CPGPR | dc->_hoops_RIIAP & _hoops_IPRI->_hoops_SPGPR;


	if (!BIT (_hoops_PGGCS, Polyedge_View_Dependent_Pass)) {
		do {
			_hoops_GHHPR			_hoops_RCGPS;
			Net_Rendition		 		nr = inr;
			_hoops_IGCGP		_hoops_HCSHS = 0;

			_hoops_SHGCS = polyedge->next;

			if (polyedge->_hoops_HSAI > 1 && !BIT(polyedge->_hoops_CARI, _hoops_SARI)) {
				polyedge = _hoops_HPGCS (polyedge);
				polyedge->_hoops_SRHA |= _hoops_SRHA;
			}
			else {
				if (ANYBIT (polyedge->_hoops_RAHH, _hoops_RRCGP & ~_hoops_AAHH))
					_hoops_ICSIS (polyedge);
				_hoops_CAHS (polyedge);
				polyedge->_hoops_SRHA = _hoops_SRHA;
			}
			polyedge->points = _hoops_IPRI->points;
			polyedge->_hoops_RSHA = (Vector alter *) _hoops_RSHA;
			polyedge->_hoops_ICHA = (Vector alter *) _hoops_ICHA;
			polyedge->_hoops_CCHA = (_hoops_RSSH alter *) _hoops_HAPAR._hoops_CCHA;
			polyedge->_hoops_GSHA = _hoops_HAPAR._hoops_GSHA;
			polyedge->_hoops_SCAI = _hoops_HAPAR._hoops_SCAI;
			polyedge->point_count = _hoops_IPRI->point_count;
			polyedge->_hoops_SPHA = _hoops_IPRI->_hoops_SPHA;
			polyedge->_hoops_RPRCP = _hoops_PAACP;
			polyedge->_hoops_GPPPI = false;
			polyedge->_hoops_GSCP = (Polyhedron*)_hoops_IPRI;
			polyedge->bounding = _hoops_IPRI->bounding;

			polyedge->_hoops_GSAI = _hoops_GSAI;

			_hoops_RCGPS = polyedge->_hoops_PPGI.flags & _hoops_CPGCS;

			if (ANYBIT (_hoops_IGGCS | polyedge->_hoops_CPGPR | dc->_hoops_RIIAP & polyedge->_hoops_SPGPR,
						_hoops_ICHPA | _hoops_CPPGP) &&
				(BIT (_hoops_RCGPS, _hoops_APGI) ||
				 (_hoops_CIPSH && !BIT (_hoops_RCGPS, _hoops_AHIAA)))) {

				polyedge->_hoops_ASHA = null;
				polyedge->_hoops_PCHA = null;
				polyedge->_hoops_HCHA = null;

				if (!_hoops_HPGI (_hoops_RIGCS, polyedge->_hoops_PPGI, _hoops_CAGCS)) {
					nr = HD_New_Local_Edge_Rendition ((Polyhedron *)_hoops_IPRI, nr, inr, &polyedge->_hoops_PPGI);

					_hoops_AAIPR (polyedge->_hoops_PPGI, _hoops_RIGCS);
				}

				if (BIT (_hoops_SRHA, DL_POLYEDGE_FROM_TRISTRIP)) {
					_hoops_IGCGH (nr, polyedge, _hoops_IPRI->tristrips);
				}
				else

				if (BIT (_hoops_CIPSH, T_GENERIC_EDGES) ||
					ANYBIT (_hoops_RCGPS,
							_hoops_APGI | _hoops_AACPR | _hoops_CCCPR |
							_hoops_AGSPR | _hoops_CIIPR)) {

#ifndef _hoops_SGRCP
					if (_hoops_HGGCS &&
						BIT (polyedge->_hoops_PPGI.flags,
							 _hoops_APHPR)
						&& !ANYBIT (polyedge->_hoops_PPGI.flags,
									_hoops_HPHPR | _hoops_IPHPR)) {
						if (nr->_hoops_ASIR->_hoops_PSIR->
							_hoops_CSIR->length == 0) {
							HD_Report_Null_Color_Map ("polyedge", nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR);
						}
						else {
							polyedge->_hoops_HCHA = _hoops_SPRI->_hoops_HGHIR;
							_hoops_PAIGH (nr, polyedge);
						}
					}
					else
#endif
					if (_hoops_PAACP &&
						 ANYBIT (polyedge->_hoops_PPGI.flags,
								 _hoops_APHPR | _hoops_HPHPR)) {
						/*-- _hoops_IHASR-_hoops_AAGCS --*/
						if (!BIT(nr->_hoops_ARA->_hoops_IHRH.options, _hoops_CHRH) &&
							!ANYBIT (polyedge->_hoops_PPGI.flags,
									 _hoops_IPHPR | _hoops_APHPR)) {
							/*-- _hoops_HCSRH _hoops_RISIS _hoops_IHASR-_hoops_CARRI-_hoops_CASIS --*/
							polyedge->_hoops_PCHA = &_hoops_SPRI->ecolors[0];
							_hoops_RAIGH (nr, polyedge);
						}
						else {
							/*-- _hoops_AAGCS, _hoops_HGRIR _hoops_PAGCS _hoops_RISIS --*/
							/* _hoops_RGR _hoops_GRS _hoops_SAHR _hoops_AASA _hoops_GRRAR, _hoops_PGAP _hoops_GRS _hoops_HA _hoops_IRAA _hoops_IRS _hoops_ACRI, _hoops_PPR _hoops_CISA _hoops_GGR _hoops_RH _hoops_GPHA _hoops_PSHA (_hoops_ISGRA _hoops_AIGCS)
							   _hoops_HHIGR _hoops_GRS _hoops_GACC _hoops_AA _hoops_RH _hoops_ISPR _hoops_CAPP, _hoops_IH _hoops_PIGCS _hoops_PPR _hoops_IAPR-_hoops_GGI _hoops_RH _hoops_ACRI->_hoops_IISIS _hoops_CCA _hoops_IRS _hoops_IRGH
							   _hoops_HHHA _hoops_HAIR.  _hoops_ACRI->_hoops_IISIS _hoops_GRS _hoops_SHH _hoops_RH _hoops_CRPR _hoops_ARRHP _hoops_RH _hoops_PSHA */
							if (!BIT (polyedge->_hoops_SRHA,_hoops_GAHH)) {
								if (nr->_hoops_IRR->_hoops_GAHA == Display_List_SEGMENT) {
									_hoops_ISAI (polyedge);
									polyedge = _hoops_HPGCS (polyedge);
								}
								else {
									_hoops_HCSHS |= _hoops_PIPI;
								}
							}
							if (!_hoops_GIGCS)
								_hoops_PCSIS (nr, polyedge, _hoops_SPRI);
							else
								polyedge->_hoops_PCHA = dc->_hoops_SSPGH;
							_hoops_GIGCS = true;
							polyedge->_hoops_SRHA |= DL_TEMPORARY_DATA;

							_hoops_RAIGH (nr, polyedge);
						}
					}
					else {
						/*-- _hoops_CRPIS-_hoops_HAGCS --*/
						if (!_hoops_HPGI (_hoops_RIGCS, polyedge->_hoops_PPGI, ~0)) {
							if (!_hoops_HPGI (_hoops_RIGCS, polyedge->_hoops_PPGI, _hoops_CAGCS)) {
								nr = HD_New_Local_Edge_Rendition ((Polyhedron *)_hoops_IPRI, nr, inr, &polyedge->_hoops_PPGI);
							}
							_hoops_AAIPR (polyedge->_hoops_PPGI, _hoops_RIGCS);
						}
						if (nr->_hoops_RHP->_hoops_CHA->_hoops_IRIR > 0 ||
							nr->_hoops_RHP->_hoops_CHA->_hoops_ARIR) {
							_hoops_RAIGH (nr, polyedge);
						}
						else
							dc->_hoops_GSGC |= _hoops_ASRI;
					}
				}
			}

			if (_hoops_ISAI (polyedge) == 0) {
				HI_Free_Polyedge (polyedge);
			}
			else {
				if (BIT (_hoops_HCSHS, _hoops_PIPI)) {
					if (!BIT (polyedge->_hoops_RAHH, _hoops_PIPI))
						polyedge->_hoops_PCHA = null;
				}
				_hoops_HCSHS = 0;
			}

#if 0
			if (_hoops_GGPGR(nr)) {
				if (node == null) {
					node = new (dc->memory_pool) _hoops_SGRGH (_hoops_IPRI);

					node->_hoops_ICHA = _hoops_ICHA;
					node->_hoops_RSHA = _hoops_RSHA;
					node->_hoops_HAPAR = _hoops_HAPAR;
					node->_hoops_CPGCS = _hoops_CPGCS;
					node->_hoops_CIPSH = _hoops_CIPSH;
					node->_hoops_PGGCS = _hoops_PGGCS;
					node->_hoops_SRHA = _hoops_SRHA;
					node->_hoops_GSAI = _hoops_GSAI;
					node->_hoops_PAACP = _hoops_PAACP;
					node->_hoops_HGGCS = _hoops_HGGCS;
				}
				node->polyedge = _hoops_SHGCS;
				node->_hoops_HGSIS();

				return node;
			}
#endif
		} while ((polyedge = _hoops_SHGCS) != null);

		if (ANYBIT (_hoops_CIPSH, T_INTERIOR_SILHOUETTE_EDGES|_hoops_GCSI) &&
			!BIT (_hoops_CIPSH, T_GENERIC_EDGES)) {
			// _hoops_ASGGR _hoops_IH _hoops_GIAP _hoops_HAPR
			polyedge = _hoops_IPRI->_hoops_SHGPR;
			_hoops_PGGCS |= Polyedge_View_Dependent_Pass;
		}
	}

	/* _hoops_HA _hoops_SGS _hoops_SR _hoops_HS _hoops_APCRR _hoops_CPS _hoops_SGS _hoops_HIAAI _hoops_CRGR _hoops_IRS _hoops_AIRI _hoops_HIGR, _hoops_SR _hoops_HGGC _hoops_RRP
	 * _hoops_IS _hoops_PGSA _hoops_GII _hoops_RAR-_hoops_AAR _hoops_CPAP (_hoops_IAS._hoops_ISHI. _hoops_ASSIA _hoops_SPPR) */

	/* _hoops_APHS/_hoops_SGGC _hoops_CSCS _hoops_HAPR _hoops_IS _hoops_IGHAR _hoops_ASSIA _hoops_ARAR, _hoops_PSP _hoops_AIRI _hoops_CPCI */
	if (polyedge != null) do {
		_hoops_GHHPR			_hoops_RCGPS;
		Net_Rendition		 		nr = inr;

		_hoops_SHGCS = polyedge->next;

		if (polyedge->_hoops_HSAI > 1) {
			polyedge = _hoops_HPGCS (polyedge);
		}
		else {
			if (ANYBIT (polyedge->_hoops_RAHH, _hoops_RRCGP & ~_hoops_AAHH))
				_hoops_ICSIS (polyedge);
			_hoops_CAHS (polyedge);
			polyedge->_hoops_SRHA = _hoops_SRHA;
		}


		polyedge->_hoops_GSCP = (Polyhedron *)_hoops_IPRI;
		polyedge->bounding = _hoops_IPRI->bounding;

		_hoops_RCGPS = polyedge->_hoops_PPGI.flags & _hoops_CPGCS;

		if (BIT (_hoops_RCGPS, _hoops_APGI) ||
			(_hoops_CIPSH &&
			!BIT (_hoops_RCGPS, _hoops_AHIAA))) {
				if (!ANYBIT (_hoops_RCGPS,
					_hoops_APGI | _hoops_AACPR | _hoops_CCCPR |
					_hoops_AGSPR | _hoops_CIIPR)) {

					/* _hoops_RAR-_hoops_AAR _hoops_ISHA _hoops_CSSC */
					if (!BIT(dc->flags, _hoops_CHSI)) {
						polyedge->_hoops_ASHA = null;
						polyedge->_hoops_PCHA = null;
						polyedge->_hoops_HCHA = null;

						if (!_hoops_HPGI (_hoops_RIGCS, polyedge->_hoops_PPGI, _hoops_CAGCS)) {
							nr = HD_New_Local_Edge_Rendition ((Polyhedron *)_hoops_IPRI, nr, inr, &polyedge->_hoops_PPGI);
							_hoops_AAIPR (polyedge->_hoops_PPGI, _hoops_RIGCS);
						}

						if (BIT (_hoops_CIPSH, _hoops_GCSI))
							_hoops_HIIGH (nr, polyedge);
						else if (BIT (_hoops_CIPSH, T_INTERIOR_SILHOUETTE_EDGES))
							_hoops_PIIGH (nr, polyedge);
					}
				}
		}

		if (_hoops_ISAI (polyedge) == 0)
			HI_Free_Polyedge (polyedge);

#if 0
		if (_hoops_GGPGR(nr)) {
			if (node == null) {
				node = new (dc->memory_pool) _hoops_SGRGH (_hoops_IPRI);

				node->_hoops_ICHA = _hoops_ICHA;
				node->_hoops_RSHA = _hoops_RSHA;
				node->_hoops_HAPAR = _hoops_HAPAR;
				node->_hoops_CPGCS = _hoops_CPGCS;
				node->_hoops_CIPSH = _hoops_CIPSH;
				node->_hoops_PGGCS = _hoops_PGGCS;
				node->_hoops_SRHA = _hoops_SRHA;
				node->_hoops_GSAI = _hoops_GSAI;
				node->_hoops_PAACP = _hoops_PAACP;
				node->_hoops_HGGCS = _hoops_HGGCS;
			}
			node->polyedge = _hoops_SHGCS;
			node->_hoops_HGSIS();

			return node;
		}
#endif
	} while ((polyedge = _hoops_SHGCS) != null);

	return node;
}


/* _hoops_HHH _hoops_SGI _hoops_IH _hoops_AIRI _hoops_HIGR _hoops_PGAAP */
#define _hoops_HIGCS 0x1	 /* _hoops_IRHS _hoops_IS _hoops_SHH _hoops_GIAH _hoops_HII _hoops_CCAIS */

local _hoops_SGRGH alter * _hoops_IIGCS (
	Net_Rendition const & 			inr,
	_hoops_SGRGH alter *			node,
	Color_Object					_hoops_GSSCC, 
	Polyhedron const *				_hoops_IPRI) {
	Display_Context const *			dc = inr->_hoops_SRA;
	_hoops_GRGH const &			_hoops_RRGH = inr->_hoops_IRR;
	_hoops_HHCR const &		_hoops_IHCR = inr->transform_rendition;
	Local_Vertex_Attributes const *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;
	Polymarker *					_hoops_RGRHR;
	Polymarker alter *				_hoops_CIGCS = null;
	Vector const *					_hoops_ICHA;
	_hoops_RRCC				_hoops_HAPAR;
	Activity						_hoops_IGGCS;
	Local_Vertex_Flags				_hoops_SIGCS;
	_hoops_ACHR						_hoops_CIPSH;
	int								_hoops_PGGCS;
	unsigned int					_hoops_SRHA;
	unsigned int					_hoops_GSAI;
	bool							_hoops_PAACP;

	if (dc->_hoops_SHCI() == _hoops_GICI ||
		dc->_hoops_SHCI() == _hoops_RICI)
		return node;

	if (1 /* _hoops_GIIS == _hoops_IRAP || _hoops_GIIS->_hoops_PAAI == _hoops_IRAP */) {
		_hoops_ACHR					_hoops_PPGPS = _hoops_RRGH->locks._hoops_RGP;
		bool						_hoops_CGGCS = false;
		bool						_hoops_SGGCS;

		_hoops_CIPSH = inr->_hoops_RGP & T_VERTICES;

		_hoops_SGGCS = false;

		if (ANYBIT (_hoops_PPGPS, T_VERTICES)) {
			if (_hoops_CIPSH) {
				if (_hoops_IPRI->point_count > 0) {
					_hoops_SGGCS = true;
					_hoops_CGGCS = true;
				}
			}
		}
		else {
			if (_hoops_CIPSH) {
				if (_hoops_IPRI->point_count >
					_hoops_IPRI->local_vertex_attributes.
					_hoops_SIIPR) _hoops_SGGCS = true;
			}
			else {
				if (_hoops_IPRI->local_vertex_attributes.
					_hoops_CPIAA > 0) {
					if (BIT(dc->flags, _hoops_RCHCP) ||
						dc->_hoops_SHCI() == _hoops_GAIIP ||
						dc->_hoops_SHCI() == _hoops_CRIIP &&
						BIT (inr->_hoops_ASIR->_hoops_GCCI.options,
							 _hoops_RCCI))
						_hoops_SGGCS = true;
				}
			}
		}

		if (!_hoops_SGGCS)
			return node;

		_hoops_SIGCS = _hoops_APPRA | _hoops_SIICA;

		if (!_hoops_CGGCS) {
			if (BIT (_hoops_CIPSH, T_VERTICES))
				_hoops_SIGCS |= _hoops_HHIAA;
			else
				_hoops_SIGCS |= _hoops_PHIAA | _hoops_HHIAA;
		}

#ifndef DISABLE_TEXTURING
		if (BIT (_hoops_RRGH->_hoops_CSA, (_hoops_CHRAP & ~_hoops_AHGI)) &&
				inr->_hoops_SCP->_hoops_CHA->_hoops_ARIR) {
			_hoops_HAPAR._hoops_CCHA = _hoops_SPRI->params;
			_hoops_HAPAR._hoops_GSHA = _hoops_SPRI->param_width;
		}
		else
#endif
		{
			_hoops_HAPAR._hoops_CCHA = null;
			_hoops_HAPAR._hoops_GSHA = 0;
		}
		_hoops_HAPAR._hoops_SCAI = 0;


		_hoops_SRHA = 0;
		_hoops_GSAI = 0;

		if (!ALLBITS (_hoops_IPRI->_hoops_AGRHR, _hoops_SIGCS)) {
			_hoops_RCCA(_hoops_RHRGH) += HI_Assemble_3D_Polymarkers ((Polyhedron alter *) _hoops_IPRI,
																	_hoops_SIGCS);
			_hoops_HSCIS (_hoops_IHCR,(Polyhedron alter *)_hoops_IPRI);
		}
		else if (BIT (_hoops_IPRI->_hoops_CPGPR, _hoops_AHSGA)) {
			/* _hoops_PSSI _hoops_RPGAH _hoops_IHRI, _hoops_HIH _hoops_CPHP _hoops_HGAS.  _hoops_GAAP _hoops_CPHP _hoops_PII
			   _hoops_GPHA _hoops_PSHA, _hoops_PGAP _hoops_PSP _hoops_RPIP _hoops_HRCI _hoops_IIRGR (_hoops_CR _hoops_SR _hoops_PAH
			   _hoops_PSP _hoops_RPIP _hoops_SHH _hoops_RCRR _hoops_IIGR _hoops_SSRHR _hoops_CAPR _hoops_HII _hoops_RH _hoops_SCRPA)
			*/
			Polyhedron alter *	_hoops_HPGPR = (Polyhedron alter *)_hoops_IPRI;

			HI_Reset_Strip_Flags (_hoops_HPGPR);
			_hoops_HPGPR->_hoops_CPGPR &= ~_hoops_AHSGA;
		}


		if ((_hoops_RGRHR = (Polymarker *)_hoops_IPRI->_hoops_GIGPR) == null)
			return node;


		bool 					_hoops_SPGI;
		bool					_hoops_CRRS;

		_hoops_SPGI = BIT (_hoops_RRGH->locks.color, Color_VERTEX) &&
						 BIT (_hoops_RRGH->locks._hoops_HAA[_hoops_PPA], M_DIFFUSE);

		_hoops_PAACP = (BIT (_hoops_RRGH->_hoops_CSA,
									(_hoops_RHRAP & ~_hoops_AHGI)));

		_hoops_PGGCS = 0;
		if (_hoops_SPGI)
			_hoops_PGGCS |= Polymarker_Diffuse_Locked;

		if (!BIT (_hoops_IHCR->flags, _hoops_GRHH) ||
			!BIT (inr->_hoops_RGP, T_LIGHTS_FOR_MARKERS) ||
			inr->_hoops_SCP->_hoops_AGP == null)
			_hoops_ICHA = null;
		else {
			if (!BIT (_hoops_IPRI->polyhedron_flags, PHF_VERTEX_NORMALS_VALID)) {
				_hoops_RCCA(_hoops_RHRGH) += HI_Assemble_3D_Tristrips ((Polyhedron alter *) _hoops_IPRI,
										  false, true);
				_hoops_HSCIS(_hoops_IHCR,(Polyhedron alter *)_hoops_IPRI);
			}
			_hoops_ICHA = _hoops_SPRI->normals;
		}


		/* _hoops_CGP _hoops_IIH _hoops_CSAP _hoops_IRS _hoops_CAPGR _hoops_ARP _hoops_PAR _hoops_RPP _hoops_RH _hoops_RHPP _hoops_AASA _hoops_CSAP _hoops_RASA _hoops_CCA _hoops_HHGCS,
		   * _hoops_SR _hoops_CGH _hoops_IGGRA _hoops_GAR _hoops_PHRI _hoops_AIRI _hoops_CPCI _hoops_AAPR _hoops_GRGR */
		_hoops_CRRS =
			_hoops_RRGH->_hoops_GAHA &&
			inr->_hoops_RSGC->action.draw_3d_polymarker == nullroutine &&
			(dc->_hoops_IPCI->draw_3d_polymarker != HD_Std_3D_Polymarker ||
			BIT(inr->_hoops_CPP->_hoops_PRH._hoops_SRI, _hoops_HSSS));

		if (_hoops_CRRS) {
			bool 					_hoops_ARPSH;
			bool 					_hoops_SSAIS;

			_hoops_ARPSH = (BIT (_hoops_GSSCC, Color_VERTEX) ||
							_hoops_SPRI->_hoops_ICRRA != 0 ||
							_hoops_SPRI->_hoops_PCRRA != 0 ||
							_hoops_SPRI->_hoops_HIRRA != 0);
			_hoops_SSAIS = BIT(_hoops_RRGH->_hoops_PPH, _hoops_HAI);

			if (_hoops_SPRI->_hoops_PCRRA)
				_hoops_SRHA |= DL_COLORS_BY_FINDEX;
			if (_hoops_ARPSH) {
				_hoops_SRHA |= DL_VCOLORED_TRISTRIP;
				if (_hoops_SSAIS)
					_hoops_SRHA |= DL_LOCAL_GRAYSCALE;
				if (_hoops_SPGI) 
					_hoops_SRHA |= _hoops_IIRC;
			}
			_hoops_GSAI = (_hoops_RRGH->_hoops_CSA & _hoops_HGAAP);
			if (BIT (_hoops_IHCR->flags, _hoops_GRHH) && 
				BIT (inr->_hoops_RGP, T_LIGHTS_FOR_MARKERS))
				_hoops_GSAI |= _hoops_HIGCS;
			if (BIT (inr->_hoops_PSGI, T_VERTICES) &&
				inr->_hoops_CPP->_hoops_PRH.style != _hoops_GCPI) {
				_hoops_SRHA |= DL_HAS_TRANSPARENCY;
			}
		}
	}
#if 0
	else {
		node->_hoops_AGSIS();
		_hoops_RGRHR = node->_hoops_RGRHR;
		node->_hoops_RGRHR = null;

		_hoops_ICHA = node->_hoops_ICHA;
		_hoops_HAPAR = node->_hoops_HAPAR;
		_hoops_SIGCS = node->_hoops_SIGCS;
		_hoops_CIPSH = node->_hoops_CIPSH;
		_hoops_PGGCS = node->_hoops_PGGCS;
		_hoops_SRHA = node->_hoops_SRHA;
		_hoops_GSAI = node->_hoops_GSAI;
		_hoops_PAACP = node->_hoops_PAACP;
		_hoops_HGGCS = node->_hoops_HGGCS;
	}
#endif


	_hoops_PSGHR	_hoops_GCGCS;


	_hoops_GRRHR (_hoops_GCGCS);
	/* _hoops_ARP _hoops_GII _hoops_SR _hoops_PAH _hoops_CGIC _hoops_CPIIS */
	_hoops_GCGCS.size = (float)inr->_hoops_GSP->ysize;
	_hoops_GCGCS.glyph = inr->_hoops_GSP->glyph;
	_hoops_GCGCS.glyph_symbol = 0;

	_hoops_IGGCS = dc->_hoops_CPGPR | _hoops_IPRI->_hoops_CPGPR | dc->_hoops_RIIAP & _hoops_IPRI->_hoops_SPGPR;


	do {
		Local_Vertex_Flags			_hoops_RCGPS;
		Net_Rendition		 		nr = inr;
		bool						_hoops_HGGCS = BIT(_hoops_RGRHR->_hoops_SACI.flags, _hoops_SIRRA);

		_hoops_CIGCS = _hoops_RGRHR->next;

		if (_hoops_HGGCS)
			_hoops_SRHA |= DL_INDEX_INTERPOLATION;
		else
			_hoops_SRHA &= ~DL_INDEX_INTERPOLATION;

		if (_hoops_RGRHR->_hoops_HSAI > 1 && !BIT(_hoops_RGRHR->_hoops_CARI, _hoops_SARI)) {
			Polymarker *	_hoops_AHPIS;

			ZALLOC (_hoops_AHPIS, Polymarker);
			*_hoops_AHPIS = *_hoops_RGRHR;
			_hoops_ICAI(_hoops_AHPIS);
			_hoops_AHPIS->_hoops_RAHH = _hoops_CGCGP;
			//_hoops_AHSCP->_hoops_RCGCS = _hoops_PAAI;
			//_hoops_ACGCS (_hoops_PAAI);
			_hoops_AHPIS->_hoops_GAHA = null;
			_hoops_AHPIS->_hoops_SRHA = _hoops_SRHA | DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS | _hoops_GAHH;
			_hoops_RGRHR = _hoops_AHPIS;
		}
		else {
			if (BIT (_hoops_RGRHR->_hoops_RAHH, _hoops_AIPI)) {
				_hoops_RGRHR->_hoops_RAHH &= ~_hoops_AIPI;
				if (_hoops_RGRHR->points) {
					FREE_ARRAY_ALIGNED (_hoops_RGRHR->points, _hoops_RGRHR->point_count, Point, 16);
					_hoops_RGRHR->points = null;
				}
			}
#ifndef DISABLE_GEOMETRY_ATTRIBUTES
#  ifndef _hoops_GCGHR
			if (BIT (_hoops_RGRHR->_hoops_RAHH, _hoops_PIPI)) {
				_hoops_RGRHR->_hoops_RAHH &= ~_hoops_PIPI;
				if (_hoops_RGRHR->_hoops_PCHA) {
					FREE_ARRAY (_hoops_RGRHR->_hoops_PCHA, _hoops_RGRHR->point_count, RGB);
					_hoops_RGRHR->_hoops_PCHA = null;
				}
			}
			if (BIT (_hoops_RGRHR->_hoops_RAHH, _hoops_RCGHR)) {
				_hoops_RGRHR->_hoops_RAHH &= ~_hoops_RCGHR;
				if (_hoops_RGRHR->_hoops_HCHA) {
					FREE_ARRAY (_hoops_RGRHR->_hoops_HCHA, _hoops_RGRHR->point_count, _hoops_ACGHR);
					_hoops_RGRHR->_hoops_HCHA = null;
				}
			}
			if (BIT (_hoops_RGRHR->_hoops_RAHH, _hoops_HRRHR)) {
				_hoops_RGRHR->_hoops_RAHH &= ~_hoops_HRRHR;
				if (_hoops_RGRHR->_hoops_RGIA) {
					FREE_ARRAY (_hoops_RGRHR->_hoops_RGIA, _hoops_RGRHR->point_count, RGBAS32);
					_hoops_RGRHR->_hoops_RGIA = null;
				}
			}
#  endif
#  ifndef _hoops_HCGHR
			if (BIT (_hoops_RGRHR->_hoops_RAHH, _hoops_ICGHR)) {
				_hoops_RGRHR->_hoops_RAHH &= ~_hoops_ICGHR;
				if (_hoops_RGRHR->_hoops_ICHA) {
					FREE_ARRAY (_hoops_RGRHR->_hoops_ICHA, _hoops_RGRHR->point_count, Vector);
					_hoops_RGRHR->_hoops_ICHA = null;
				}
			}
#  endif
#  ifndef DISABLE_TEXTURING
			if (BIT (_hoops_RGRHR->_hoops_RAHH, _hoops_CCGHR)) {
				_hoops_RGRHR->_hoops_RAHH &= ~_hoops_CCGHR;
				if (_hoops_RGRHR->_hoops_CCHA) {
					FREE_ARRAY (_hoops_RGRHR->_hoops_CCHA, _hoops_RGRHR->point_count * _hoops_RGRHR->_hoops_GSHA, _hoops_RSSH);
					_hoops_RGRHR->_hoops_CCHA = null;
				}
			}
#  endif
#endif
			_hoops_CAHS (_hoops_RGRHR);
			_hoops_RGRHR->_hoops_SRHA = _hoops_SRHA;
		}




		_hoops_RGRHR->points = _hoops_IPRI->points;
		_hoops_RGRHR->_hoops_ICHA = (Vector alter *) _hoops_ICHA;
		_hoops_RGRHR->_hoops_CCHA = (_hoops_RSSH alter *) _hoops_HAPAR._hoops_CCHA;
		_hoops_RGRHR->_hoops_GSHA = _hoops_HAPAR._hoops_GSHA;
		_hoops_RGRHR->point_count = _hoops_IPRI->point_count;
		_hoops_RGRHR->_hoops_GPPPI = false;

		_hoops_RGRHR->_hoops_GSAI = _hoops_GSAI;
		_hoops_RGRHR->_hoops_SRHA = _hoops_SRHA;

		_hoops_RCGPS = _hoops_RGRHR->_hoops_SACI.flags & _hoops_SIGCS;

		if (ANYBIT (_hoops_IGGCS | _hoops_RGRHR->_hoops_CPGPR | dc->_hoops_RIIAP & _hoops_RGRHR->_hoops_SPGPR,
					_hoops_ICHPA | _hoops_CPPGP) &&
			(BIT (_hoops_RCGPS, _hoops_PHIAA) ||
			 _hoops_CIPSH && !BIT (_hoops_RCGPS, _hoops_HHIAA))) {

			_hoops_RGRHR->_hoops_PCHA = null;
			_hoops_RGRHR->_hoops_RGIA = null;
			_hoops_RGRHR->_hoops_HCHA = null;

			if (BIT (_hoops_RCGPS, _hoops_GCICA) &&
					_hoops_GCGCS.size != _hoops_RGRHR->_hoops_SACI.size ||
				!BIT (_hoops_RCGPS, _hoops_GCICA) &&
					_hoops_GCGCS.size != inr->_hoops_GSP->ysize ||
				BIT (_hoops_RCGPS, _hoops_SIICA) &&
					_hoops_GCGCS.glyph_symbol != _hoops_RGRHR->_hoops_SACI.glyph_symbol ||
				!BIT (_hoops_RCGPS, _hoops_SIICA) &&
					_hoops_GCGCS.glyph != inr->_hoops_GSP->glyph) {
				nr = _hoops_PASIS (_hoops_IPRI, nr, inr, &_hoops_RGRHR->_hoops_SACI);
				COPY_ONE_VERTEX_ATTRIBUTES (_hoops_RGRHR->_hoops_SACI, _hoops_GCGCS);
			}

			if (BIT (_hoops_RCGPS, _hoops_PHIAA) ||
				(_hoops_CIPSH && !BIT (_hoops_RCGPS, _hoops_HHIAA))) {

#ifndef DISABLE_COLOR_MAPS
				if (_hoops_HGGCS &&
					nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR->length == 0) {
					HD_Report_Null_Color_Map ("polymarker", nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR);
					_hoops_HGGCS = false;
				}
#endif
				if (!_hoops_HSGHR (_hoops_GCGCS, _hoops_RGRHR->_hoops_SACI)) {
					nr = _hoops_PASIS (_hoops_IPRI, nr, inr, &_hoops_RGRHR->_hoops_SACI);
					COPY_ONE_VERTEX_ATTRIBUTES (_hoops_RGRHR-> _hoops_SACI, _hoops_GCGCS);
				}

				if (!BIT (_hoops_PGGCS, Polymarker_Diffuse_Locked)) {
					if (_hoops_HGGCS) {
						_hoops_RGRHR->_hoops_HCHA = _hoops_SPRI->_hoops_HAHIR;
					}
					else if (_hoops_PAACP) {
						if (BIT(_hoops_RGRHR->_hoops_SACI.flags, _hoops_HCRRA))
							_hoops_RGRHR->_hoops_PCHA = _hoops_SPRI->_hoops_PAHIR;
						else if (BIT(_hoops_RGRHR->_hoops_SACI.flags, _hoops_CCRRA))
							_hoops_RGRHR->_hoops_RGIA = _hoops_SPRI->_hoops_IAHIR;
					}
				}

				if (nr->transform_rendition->_hoops_IGAAP != 0) {
					_hoops_HHCR alter &		_hoops_IHCR = nr.Modify()->transform_rendition.Modify();

					_hoops_IHCR->_hoops_SHIH += _hoops_IHCR->_hoops_IGAAP;
					_hoops_IHCR->_hoops_IGAAP = 0;
				}

				_hoops_HAIGH (nr, _hoops_RGRHR);
			}
		}

		if (_hoops_ISAI (_hoops_RGRHR) == 0)
			HI_Free_Polymarker (_hoops_RGRHR);

#if 0
		if (_hoops_GGPGR(nr)) {
			if (node == null) {
				node = new (dc->memory_pool) _hoops_SGRGH (_hoops_IPRI);

				node->_hoops_ICHA = _hoops_ICHA;
				node->_hoops_HAPAR = _hoops_HAPAR;
				node->_hoops_SIGCS = _hoops_SIGCS;
				node->_hoops_CIPSH = _hoops_CIPSH;
				node->_hoops_PGGCS = _hoops_PGGCS;
				node->_hoops_SRHA = _hoops_SRHA;
				node->_hoops_GSAI = _hoops_GSAI;
				node->_hoops_PAACP = _hoops_PAACP;
				node->_hoops_HGGCS = _hoops_HGGCS;
			}
			node->_hoops_RGRHR = _hoops_CIGCS;
			node->_hoops_CGSIS();

			return node;
		}
#endif
	} while ((_hoops_RGRHR = _hoops_CIGCS) != null);

	return node;
}



#ifndef DISABLE_LOD_GENERATION
/* _hoops_SISRP
 * _hoops_PGAA
 * _hoops_RGSHI _hoops_RH _hoops_SISRP _hoops_CSHHR _hoops_IIGR _hoops_PCPA _hoops_CHH _hoops_SHH 
 * _hoops_RH _hoops_SPS _hoops_PAPA _hoops_IAIAR
 */
local float _hoops_PCGCS (
	Net_Rendition const &			nr,
	Polyhedron const *				_hoops_HCGCS) {
	_hoops_GRA const &		_hoops_RRA = nr->_hoops_ARA;
	float							_hoops_SRCP, geom, _hoops_PRPHA;
	/* _hoops_IRHS _hoops_RIGRP */
	int								_hoops_CPGCP = (int)(_hoops_RRA->_hoops_PRSI._hoops_PRPHA[0] * _hoops_HCGCS->point_count);

	Bounding bounding = _hoops_HCGCS->bounding._hoops_SCIS (&nr->transform_rendition->_hoops_IPH->data.elements[0][0]);

	/* _hoops_PCPA _hoops_IS _hoops_CSGA _hoops_HRGR _hoops_IIHA _hoops_GPP _hoops_CISAR _hoops_HCPC. _hoops_RSCHI */
	switch (_hoops_RRA->_hoops_PRSI._hoops_SRHHR) {
		case _hoops_APSRP:
		case _hoops_HPSRP:
		case _hoops_IPSRP:
		case _hoops_PPSRP: {
			_hoops_SRCP = _hoops_RRA->_hoops_PRSI.bounding._hoops_PGCIR();
			geom = bounding._hoops_PGCIR();
			_hoops_PRPHA = geom / _hoops_SRCP;
		}break;

		case _hoops_CASRP:
		case _hoops_SASRP:
		case _hoops_GPSRP:
		case _hoops_RPSRP: {
			_hoops_SRCP = _hoops_RRA->_hoops_PRSI.bounding->sphere.radius;
			geom = bounding->sphere.radius;
			_hoops_PRPHA = geom / _hoops_SRCP;
		}break;

		case _hoops_CPSRP:
		default:
			HE_ERROR (HEC_LOD, HES_NOT_AVAILABLE,
				  "The specified calculation usefulness heuristic has not been implemented.");
			return 0;
	}

	/* _hoops_PCPA _hoops_IS _hoops_ASRC _hoops_HRGR _hoops_IIHA _hoops_GPP _hoops_AHHSR _hoops_PPR/_hoops_PAR _hoops_IGH _hoops_SCPH 
	 * _hoops_RPR _hoops_AAR */
	switch (_hoops_RRA->_hoops_PRSI._hoops_SRHHR) {
		case _hoops_CASRP:
		case _hoops_APSRP:
			return _hoops_PRPHA / _hoops_CPGCP;
		case _hoops_GPSRP:
		case _hoops_HPSRP:
			return geom / _hoops_CPGCP;
		case _hoops_RPSRP:
		case _hoops_IPSRP: 
			return geom;
		case _hoops_SASRP:
		case _hoops_PPSRP: 
			return _hoops_PRPHA;

		case _hoops_CPSRP:
		default:
			return 0;
	}
}


/* _hoops_PRCCA _hoops_RGAP _hoops_HRGR _hoops_IRS _hoops_AHPH-_hoops_IS-_hoops_SPR _hoops_CAIH _hoops_IH _hoops_GIHA.	_hoops_GRAS _hoops_IRS _hoops_IHGP
 * _hoops_AASHR _hoops_IIGR _hoops_RH _hoops_HCGP _hoops_GIHA' _hoops_ICGCS, _hoops_PPR _hoops_SGH _hoops_SGS _hoops_GAR _hoops_RH _hoops_SPIGA'_hoops_GRI _hoops_CCGCS */
local void _hoops_SCGCS (
		Polyhedron const *phon,
		Polyhedron alter *_hoops_ICAPI,
		int const *_hoops_PHAS) {
	int i, _hoops_GSGCS, _hoops_RSGCS;
	Local_Vertex_Attributes const *_hoops_ASGCS;
	Local_Vertex_Attributes alter *_hoops_PSGCS;
	int *_hoops_ICI;

	_hoops_ASGCS = &phon->local_vertex_attributes;
	if ((BIT(phon->polyhedron_flags, _hoops_CGRHR) && _hoops_ASGCS->flags == null)|| 
		(!BIT(phon->polyhedron_flags, _hoops_CGRHR) && _hoops_ASGCS->_hoops_SGRHR == 0))
		return;	 /* _hoops_IIH _hoops_CHR _hoops_PSP _hoops_AIRC _hoops_IS _hoops_IPS */
	if (_hoops_PHAS == null)
		return;	 /* _hoops_SR _hoops_GA'_hoops_RA _hoops_ACPA _hoops_RSH _hoops_IS _hoops_IPS _hoops_SCH */

	_hoops_PSGCS = &_hoops_ICAPI->local_vertex_attributes;
	_hoops_GSGCS = phon->point_count;
	_hoops_RSGCS = _hoops_ICAPI->point_count;
	ALLOC_ARRAY (_hoops_PSGCS->flags, _hoops_RSGCS, Local_Vertex_Flags);
	_hoops_ICAPI->polyhedron_flags |= _hoops_CGRHR;
	ALLOC_ARRAY (_hoops_ICI, _hoops_RSGCS, int);
	for (i = 0; i < _hoops_RSGCS; i++)
		_hoops_PSGCS->flags[i] = 0;

	/* _hoops_HSGCS _hoops_CARRI _hoops_CASIS */
	if (_hoops_ASGCS->_hoops_ICRRA == _hoops_GSGCS) {
		ALLOC_ARRAY (_hoops_PSGCS->_hoops_PAHIR, _hoops_RSGCS, RGB);
		for (i = 0; i < _hoops_RSGCS; i++) {
			_hoops_PSGCS->_hoops_PAHIR[i].red	 = 0;
			_hoops_PSGCS->_hoops_PAHIR[i].green = 0;
			_hoops_PSGCS->_hoops_PAHIR[i].blue	 = 0;
			_hoops_ICI[i] = 0;
		}
		for (i = 0; i < _hoops_GSGCS; i++) {
			_hoops_PSGCS->_hoops_PAHIR[_hoops_PHAS[i]].red   += _hoops_ASGCS->_hoops_PAHIR[i].red;
			_hoops_PSGCS->_hoops_PAHIR[_hoops_PHAS[i]].green += _hoops_ASGCS->_hoops_PAHIR[i].green;
			_hoops_PSGCS->_hoops_PAHIR[_hoops_PHAS[i]].blue  += _hoops_ASGCS->_hoops_PAHIR[i].blue;
			_hoops_ICI[_hoops_PHAS[i]]++;
		}
		for (i = 0; i < _hoops_RSGCS; i++) {
			_hoops_PSGCS->flags[i] |= _hoops_HCRRA;
			if (_hoops_ICI[i] > 1) {
				_hoops_PSGCS->_hoops_PAHIR[i].red	 /= _hoops_ICI[i];
				_hoops_PSGCS->_hoops_PAHIR[i].green /= _hoops_ICI[i];
				_hoops_PSGCS->_hoops_PAHIR[i].blue	 /= _hoops_ICI[i];
			}
		}
		_hoops_PSGCS->_hoops_ICRRA = _hoops_RSGCS;
	}
	if (_hoops_ASGCS->_hoops_SCHPR == _hoops_GSGCS) {
		ALLOC_ARRAY (_hoops_PSGCS->ecolors, _hoops_RSGCS, RGB);
		for (i = 0; i < _hoops_RSGCS; i++) {
			_hoops_PSGCS->ecolors[i].red	 = 0;
			_hoops_PSGCS->ecolors[i].green = 0;
			_hoops_PSGCS->ecolors[i].blue	 = 0;
			_hoops_ICI[i] = 0;
		}
		for (i = 0; i < _hoops_GSGCS; i++) {
			_hoops_PSGCS->ecolors[_hoops_PHAS[i]].red   += _hoops_ASGCS->ecolors[i].red;
			_hoops_PSGCS->ecolors[_hoops_PHAS[i]].green += _hoops_ASGCS->ecolors[i].green;
			_hoops_PSGCS->ecolors[_hoops_PHAS[i]].blue  += _hoops_ASGCS->ecolors[i].blue;
			_hoops_ICI[_hoops_PHAS[i]]++;
		}
		for (i = 0; i < _hoops_RSGCS; i++) {
			_hoops_PSGCS->flags[i] |= _hoops_PPHPR;
			if (_hoops_ICI[i] > 1) {
				_hoops_PSGCS->ecolors[i].red	 /= _hoops_ICI[i];
				_hoops_PSGCS->ecolors[i].green /= _hoops_ICI[i];
				_hoops_PSGCS->ecolors[i].blue	 /= _hoops_ICI[i];
			}
		}
		_hoops_PSGCS->_hoops_SCHPR = _hoops_RSGCS;
	}
	if (_hoops_ASGCS->_hoops_RCRHR == _hoops_GSGCS) {
		ALLOC_ARRAY (_hoops_PSGCS->fcolors, _hoops_RSGCS, RGB);
		for (i = 0; i < _hoops_RSGCS; i++) {
			_hoops_PSGCS->fcolors[i].red	 = 0;
			_hoops_PSGCS->fcolors[i].green = 0;
			_hoops_PSGCS->fcolors[i].blue	 = 0;
			_hoops_ICI[i] = 0;
		}
		for (i = 0; i < _hoops_GSGCS; i++) {
			_hoops_PSGCS->fcolors[_hoops_PHAS[i]].red   += _hoops_ASGCS->fcolors[i].red;
			_hoops_PSGCS->fcolors[_hoops_PHAS[i]].green += _hoops_ASGCS->fcolors[i].green;
			_hoops_PSGCS->fcolors[_hoops_PHAS[i]].blue  += _hoops_ASGCS->fcolors[i].blue;
			_hoops_ICI[_hoops_PHAS[i]]++;
		}
		for (i = 0; i < _hoops_RSGCS; i++) {
			_hoops_PSGCS->flags[i] |= _hoops_AARHR;
			if (_hoops_ICI[i] > 1) {
				_hoops_PSGCS->fcolors[i].red	 /= _hoops_ICI[i];
				_hoops_PSGCS->fcolors[i].green /= _hoops_ICI[i];
				_hoops_PSGCS->fcolors[i].blue	 /= _hoops_ICI[i];
			}
		}
		_hoops_PSGCS->_hoops_RCRHR = _hoops_RSGCS;
	}

	/* _hoops_HSGCS _hoops_CARRI _hoops_ISGCS */
	if (_hoops_ASGCS->_hoops_PCRRA == _hoops_GSGCS) {
		ALLOC_ARRAY (_hoops_PSGCS->_hoops_HAHIR, _hoops_RSGCS, _hoops_ACGHR);
		for (i = 0; i < _hoops_RSGCS; i++) {
			_hoops_PSGCS->_hoops_HAHIR[i] = 0;
			_hoops_ICI[i] = 0;
		}
		for (i = 0; i < _hoops_GSGCS; i++) {
			_hoops_PSGCS->_hoops_HAHIR[_hoops_PHAS[i]] += _hoops_ASGCS->_hoops_HAHIR[i];
			_hoops_ICI[_hoops_PHAS[i]]++;
		}
		for (i = 0; i < _hoops_RSGCS; i++) {
			_hoops_PSGCS->flags[i] |= _hoops_SIRRA;
			if (_hoops_ICI[i] > 1) {
				_hoops_PSGCS->_hoops_HAHIR[i] /= _hoops_ICI[i];
			}
		}
		_hoops_PSGCS->_hoops_PCRRA = _hoops_RSGCS;
	}
	if (_hoops_ASGCS->_hoops_CCHPR == _hoops_GSGCS) {
		ALLOC_ARRAY (_hoops_PSGCS->_hoops_HGHIR, _hoops_RSGCS, _hoops_ACGHR);
		for (i = 0; i < _hoops_RSGCS; i++) {
			_hoops_PSGCS->_hoops_HGHIR[i] = 0;
			_hoops_ICI[i] = 0;
		}
		for (i = 0; i < _hoops_GSGCS; i++) {
			_hoops_PSGCS->_hoops_HGHIR[_hoops_PHAS[i]] += _hoops_ASGCS->_hoops_HGHIR[i];
			_hoops_ICI[_hoops_PHAS[i]]++;
		}
		for (i = 0; i < _hoops_RSGCS; i++) {
			_hoops_PSGCS->flags[i] |= _hoops_RPHPR;
			if (_hoops_ICI[i] > 1) {
				_hoops_PSGCS->_hoops_HGHIR[i] /= _hoops_ICI[i];
			}
		}
		_hoops_PSGCS->_hoops_CCHPR = _hoops_RSGCS;
	}
	if (_hoops_ASGCS->_hoops_SIRHR == _hoops_GSGCS) {
		ALLOC_ARRAY (_hoops_PSGCS->_hoops_IGHIR, _hoops_RSGCS, _hoops_ACGHR);
		for (i = 0; i < _hoops_RSGCS; i++) {
			_hoops_PSGCS->_hoops_IGHIR[i] = 0;
			_hoops_ICI[i] = 0;
		}
		for (i = 0; i < _hoops_GSGCS; i++) {
			_hoops_PSGCS->_hoops_IGHIR[_hoops_PHAS[i]] += _hoops_ASGCS->_hoops_IGHIR[i];
			_hoops_ICI[_hoops_PHAS[i]]++;
		}
		for (i = 0; i < _hoops_RSGCS; i++) {
			_hoops_PSGCS->flags[i] |= _hoops_HARHR;
			if (_hoops_ICI[i] > 1) {
				_hoops_PSGCS->_hoops_IGHIR[i] /= _hoops_ICI[i];
			}
		}
		_hoops_PSGCS->_hoops_SIRHR = _hoops_RSGCS;
	}

	/* _hoops_CSGCS */
	if (_hoops_ASGCS->_hoops_SCHHC == _hoops_GSGCS) {
		ALLOC_ARRAY (_hoops_PSGCS->_hoops_CAHIR, _hoops_RSGCS, float);
		for (i = 0; i < _hoops_RSGCS; i++) {
			_hoops_PSGCS->_hoops_CAHIR[i] = 0;
			_hoops_ICI[i] = 0;
		}
		for (i = 0; i < _hoops_GSGCS; i++) {
			_hoops_PSGCS->_hoops_CAHIR[_hoops_PHAS[i]] += _hoops_ASGCS->_hoops_CAHIR[i];
			_hoops_ICI[_hoops_PHAS[i]]++;
		}
		for (i = 0; i < _hoops_RSGCS; i++) {
			_hoops_PSGCS->flags[i] |= _hoops_GCICA;
			if (_hoops_ICI[i] > 1) {
				_hoops_PSGCS->_hoops_CAHIR[i] /= _hoops_ICI[i];
			}
		}
		_hoops_PSGCS->_hoops_SCHHC = _hoops_RSGCS;
	}

/* _hoops_IPCP _hoops_HSPR _hoops_RIS _hoops_HRGR _hoops_GRGR _hoops_PGGA _hoops_ISCP _hoops_SSGCS _hoops_HRGR _hoops_SGS _hoops_SCH _hoops_HRGR _hoops_AAH 
 * _hoops_IS _hoops_HRHPA _hoops_HRII _hoops_HSAR _hoops_ACIAR. */
#if 0 
	/* _hoops_GGRCS */
	if (_hoops_ASGCS->explicit_normal_count == _hoops_GSGCS) {
		ALLOC_ARRAY (_hoops_PSGCS->normals, _hoops_RSGCS, Vector);
		for (i = 0; i < _hoops_RSGCS; i++) {
			_hoops_PSGCS->normals[i].x = 0;
			_hoops_PSGCS->normals[i].y = 0;
			_hoops_PSGCS->normals[i].z = 0;
			_hoops_ICI[i] = 0;
		}
		for (i = 0; i < _hoops_GSGCS; i++) {
			_hoops_PSGCS->normals[_hoops_PHAS[i]].x += _hoops_ASGCS->normals[i].x;
			_hoops_PSGCS->normals[_hoops_PHAS[i]].y += _hoops_ASGCS->normals[i].y;
			_hoops_PSGCS->normals[_hoops_PHAS[i]].z += _hoops_ASGCS->normals[i].z;
			_hoops_ICI[_hoops_PHAS[i]]++;
		}
		for (i = 0; i < _hoops_RSGCS; i++) {
			_hoops_PSGCS->flags[i] |= LVA_EXPLICIT_NORMAL;
			if (_hoops_ICI[i] > 1) {
				_hoops_PSGCS->normals[i].x /= _hoops_ICI[i];
				_hoops_PSGCS->normals[i].y /= _hoops_ICI[i];
				_hoops_PSGCS->normals[i].z /= _hoops_ICI[i];
			}
		}
		_hoops_PSGCS->explicit_normal_count = _hoops_RSGCS;
	}
#endif

	/* _hoops_RGRCS */
	if (_hoops_ASGCS->_hoops_SCHHC == _hoops_GSGCS) {
		ALLOC_ARRAY (_hoops_PSGCS->_hoops_SAHIR, _hoops_RSGCS, unsigned char);
		for (i = 0; i < _hoops_GSGCS; i++) {
			_hoops_PSGCS->_hoops_CAHIR[_hoops_PHAS[i]] = _hoops_ASGCS->_hoops_CAHIR[i];
		}
		for (i = 0; i < _hoops_RSGCS; i++) {
			_hoops_PSGCS->flags[i] |= _hoops_SIICA;
		}
		_hoops_PSGCS->_hoops_SCHHC = _hoops_RSGCS;
	}

	/* _hoops_AGRCS */
	if (_hoops_ASGCS->_hoops_RSAPA == _hoops_GSGCS) {
		/*_hoops_ASIGA _hoops_PIHA _hoops_AA _hoops_RGR _hoops_GIH _hoops_HIH _hoops_PCPA _hoops_HRGR _hoops_SCH???*/
		int				j;
		Integer32		param_width = _hoops_ASGCS->param_width;

		ALLOC_ARRAY (_hoops_PSGCS->params, _hoops_RSGCS*param_width, _hoops_RSSH);
		for (i = 0; i < _hoops_RSGCS; i++) {
			_hoops_CRAGI(&_hoops_PSGCS->params[i*param_width], param_width);
			_hoops_ICI[i] = 0;
		}
		for (i = 0; i < _hoops_GSGCS; i++) {
			for (j=0;j<param_width;j++) {
				_hoops_PSGCS->params[(_hoops_PHAS[i]*param_width)+j] += _hoops_ASGCS->params[(i*param_width)+j];
			}
			_hoops_ICI[_hoops_PHAS[i]]++;
		}
		for (i = 0; i < _hoops_RSGCS; i++) {
			_hoops_PSGCS->flags[i] |= _hoops_ASAPA;
			if (_hoops_ICI[i] > 1) {
				for (j=0;j<param_width;j++) {
					_hoops_PSGCS->params[(i*param_width)+j] /= _hoops_ICI[i];
				}
			}
		}
		_hoops_PSGCS->_hoops_RSAPA = _hoops_RSGCS;
		_hoops_PSGCS->param_width = param_width;
	}

	FREE_ARRAY (_hoops_ICI, _hoops_RSGCS, int);
}


/* _hoops_PGRCS
 * _hoops_AICP _hoops_RH _hoops_IIPR _hoops_HII _hoops_RH _hoops_SPIGA _hoops_RPHRA (_hoops_GGR _hoops_SRRPR), _hoops_PPR _hoops_PICII _hoops_SCH _hoops_IS _hoops_IPGC.
 * _hoops_PS _hoops_HS _hoops_IS _hoops_SHH _hoops_RHRIR, _hoops_PHRI.  _hoops_SPCA _hoops_SIAS _hoops_SHH _hoops_IPSP-_hoops_PAPR _hoops_SCHS _hoops_AIAH _hoops_IIH.
 * _hoops_IPCP _hoops_HGRCS _hoops_HRGR _hoops_HAR _hoops_RCAPI _hoops_HPISR _hoops_ARI. 
 */
local void _hoops_IGRCS (
	Polyhedron alter *	phon,
	int *				_hoops_CGRCS,
	_hoops_HAPHA *		root,
	int					_hoops_HISRP) {
	_hoops_HAPHA *		node;
	Polyhedron *		_hoops_ICAPI;
	Shell *				_hoops_SPHPR;
	int					level;
	int					*_hoops_GAHI, *_hoops_ICGCR;

	if (phon->_hoops_HGAIR == null) {
		ZALLOC (phon->_hoops_HGAIR, _hoops_PGAIR);
		phon->_hoops_HGAIR->type = _hoops_AGAIR;
		phon->_hoops_HGAIR->owner = (_hoops_HPAH *)phon;
		phon->_hoops_HGAIR->backlink = (_hoops_HPAH **) &(phon->_hoops_HGAIR);
		phon->_hoops_HGAIR->_hoops_HIHI = 1;
	}
	else {
		for (level = 0; level < _hoops_IGAIR; level++) {
			if (phon->_hoops_HGAIR->data[level] != null) {
				HI_Au_Revoir ((_hoops_HPAH *)(phon->_hoops_HGAIR->data[level]));
				phon->_hoops_HGAIR->data[level] = null;
			}
		}
	}

	node = root;
	/* _hoops_GCPC = _hoops_IPGC; */
	for (level = 0; level < _hoops_IGAIR; level++) {
		if (node == null)
			break;
		/* _hoops_HSPR _hoops_III _hoops_CIAH _hoops_IGIPR _hoops_PRHI _hoops_GCIHC _hoops_HS _hoops_HIPH _hoops_RGAR */
		if (node->_hoops_IAPHA._hoops_RHGIR < _hoops_HISRP * 4)
			break;

		ZALLOC (_hoops_SPHPR, Shell);
		_hoops_ICAPI = (Polyhedron *) _hoops_SPHPR;

		_hoops_ICAPI->type = _hoops_SCIP;
		_hoops_ICAPI->point_count = -1;		/* _hoops_HAR _hoops_AISP _hoops_GAPR */
		_hoops_ICAPI->_hoops_SPHA = -1;		/* _hoops_HAR _hoops_AISP _hoops_GAPR */
		_hoops_ICAPI->face_count = -1;		/* _hoops_HAR _hoops_AISP _hoops_GAPR */
		_hoops_ICAPI->_hoops_IPPGR = null;
		_hoops_ICAPI->_hoops_HIHI = 1;
		_hoops_ICAPI->key = _hoops_AIRIR (_hoops_ICAPI);

		_hoops_ICAPI->bounding = phon->bounding;

		_hoops_ICAPI->points = (Point *) (node->_hoops_IAPHA.points);
		node->_hoops_IAPHA.points = null;
		_hoops_ICAPI->point_count = node->_hoops_IAPHA.pcount;

		_hoops_SPHPR->face_list = node->_hoops_IAPHA.faces;
		node->_hoops_IAPHA.faces = null;
		_hoops_SPHPR->face_list_length = node->_hoops_IAPHA._hoops_RHGIR;

		if (_hoops_CGRCS == null) {
			_hoops_SCGCS (phon, _hoops_ICAPI, node->_hoops_PHAS);
		}
		else {
			int *_hoops_SGRCS;
			int i;

			ALLOC_ARRAY (_hoops_SGRCS, phon->point_count, int);
			for (i = 0; i < phon->point_count; i++)
				_hoops_SGRCS[i] = node->_hoops_PHAS[_hoops_CGRCS[i]];
			_hoops_SCGCS (phon, _hoops_ICAPI, _hoops_SGRCS);
			FREE_ARRAY (_hoops_SGRCS, phon->point_count, int);
		}

		/* _hoops_CSGA _hoops_RH _hoops_PHI _hoops_IIGR _hoops_RSSI (_hoops_PAH _hoops_HPCAR _hoops_PSP _hoops_HHHR _hoops_RSSI _hoops_ARI) */
		_hoops_ICAPI->face_count = 0;
		_hoops_GAHI = _hoops_SPHPR->face_list;
		_hoops_ICGCR = _hoops_GAHI + _hoops_SPHPR->face_list_length;
		while  (_hoops_GAHI < _hoops_ICGCR) {
			if (*_hoops_GAHI > 0) 
				_hoops_GAHI += *_hoops_GAHI + 1;
			else
				_hoops_GAHI += -(*_hoops_GAHI) + 1;
			_hoops_ICAPI->face_count++;
		}
		phon->_hoops_HGAIR->data[level] = (Geometry *) _hoops_ICAPI;

		HI_Assemble_3D_Tristrips (_hoops_ICAPI, (_hoops_SARHR)~0, true);

		/* _hoops_GCPC = _hoops_GRRCS; */
		node = node->next;
	}
	while (level < _hoops_IGAIR) {
		if (phon->_hoops_HGAIR->data[level] != null) {
			HI_Au_Revoir ((_hoops_HPAH *)(phon->_hoops_HGAIR->data[level]));
			phon->_hoops_HGAIR->data[level] = null;
		}
		level++;
	}
} 


local void _hoops_RRRCS (
	_hoops_AIGPR *	_hoops_RIGC,
	Polyhedron alter *	_hoops_ARRCS,
	int 				_hoops_PRRCS,
	int 				_hoops_AASIH,
	float				_hoops_PRPHA,
	bool				_hoops_HRPHA,
	int 				_hoops_HISRP,
	int 				_hoops_RHPHA) {
	Shell const *		_hoops_HRRCS = (Shell const *)_hoops_ARRCS;
	_hoops_HAPHA		*node, *root, *_hoops_IRRCS;
	Polyhedron *		phon;
	_hoops_SAPHA			_hoops_GPPHA;
	int *				_hoops_CGRCS = null;

	_hoops_GPPHA._hoops_PPPHA = _hoops_SGRHA;
	_hoops_GPPHA._hoops_HPPHA = _hoops_SGRHA;
	_hoops_GPPHA._hoops_IPPHA = (float)_hoops_SGRHA;
	_hoops_GPPHA._hoops_CPPHA = (float)_hoops_SGRHA;
	_hoops_GPPHA._hoops_SPPHA = (float)_hoops_SGRHA;
	_hoops_GPPHA._hoops_GHPHA = _hoops_SGRHA;

	/* _hoops_CHASA _hoops_RH _hoops_RCRAH _hoops_HSSHH */
	_hoops_GPPHA._hoops_PRPHA = _hoops_PRPHA;
	_hoops_GPPHA._hoops_RHPHA = _hoops_RHPHA;

	if (_hoops_ARRCS->face_count < _hoops_HISRP) {
		/* _hoops_IRHH _hoops_RCRR _hoops_SR _hoops_GA'_hoops_RA _hoops_RCRPA _hoops_SHRRR _hoops_SPS _hoops_GHIR */
		_hoops_IGRCS (_hoops_ARRCS, null, null, _hoops_HISRP);
		return;
	}

	if (_hoops_HRPHA && (_hoops_ARRCS->type == _hoops_SCIP)) {
		int *_hoops_GAHI, *_hoops_ICGCR;
		Shell * tmp;

		if (_hoops_HRRCS->face_list == null) {
			if (_hoops_ARRCS->tristrips == null)
				return;
			HI_Face_List_From_Tristrips (_hoops_RIGC, (Shell *) _hoops_HRRCS);
		}

		ZALLOC(tmp, Shell);
		phon = (Polyhedron*) tmp;

		phon->type = _hoops_SCIP;

		phon->point_count = _hoops_ARRCS->point_count;
		ALLOC_ARRAY_ALIGNED(phon->points, phon->point_count, Point, 16);
		ALLOC_ARRAY(_hoops_CGRCS, phon->point_count, int);

		tmp->face_list_length = _hoops_HRRCS->face_list_length;
		ALLOC_ARRAY(tmp->face_list, tmp->face_list_length, int);

		phon->bounding = _hoops_ARRCS->bounding;

		/* _hoops_IGIPR _hoops_SGS _hoops_PIASR _hoops_AAHP (_hoops_AHPHA _hoops_PPR _hoops_ASGA) _hoops_IH _hoops_GHRHA _hoops_HRGR 0 */
		HI_Compute_Optimized_Shell(_hoops_RIGC,
			_hoops_ARRCS->point_count, _hoops_ARRCS->points, null,
			_hoops_HRRCS->face_list_length, _hoops_HRRCS->face_list,
			"",
			&phon->point_count, phon->points,
			&tmp->face_list_length, tmp->face_list,
			_hoops_CGRCS, null
		);

		/* _hoops_HRHPA _hoops_RH _hoops_HSP _hoops_RPR */
		phon->face_count = 0;
		_hoops_ICGCR = tmp->face_list + tmp->face_list_length;
		_hoops_GAHI = tmp->face_list;
		while (_hoops_GAHI < _hoops_ICGCR) {
			phon->face_count++;
			if (*_hoops_GAHI > 0)
				_hoops_GAHI += *_hoops_GAHI + 1;
			else
				/* _hoops_IHPHA _hoops_IIGR (_hoops_RCCPR _hoops_CHPHA _hoops_GGR) _hoops_PGHC _hoops_HSP */
				_hoops_GAHI += -(*_hoops_GAHI) + 1;
		}
		phon->tristrips = null;
		phon->_hoops_ACRHR = 0;
		if (tmp->face_list_length != 0) {
			int			_hoops_APPHA = HOOPS_WORLD->_hoops_HGGHR;

			HOOPS_WORLD->_hoops_HGGHR &= ~_hoops_SRRIR;
			HI_Assemble_3D_Tristrips (phon, (_hoops_SARHR)~0, false);
			HOOPS_WORLD->_hoops_HGGHR = _hoops_APPHA;
		}
	}
	else {
		phon = _hoops_ARRCS;
		/* _hoops_IGIPR _hoops_SGS _hoops_IPGC->_hoops_CCGI _hoops_CHR _hoops_APIP _hoops_RPP _hoops_HAR _hoops_IRAP */
		if (phon->tristrips == null &&
			phon->face_count != 0) {
			HI_Assemble_3D_Tristrips (phon, (_hoops_SARHR)~0, false);
		}
	}

	if (phon->tristrips == null ||
		phon->face_count < _hoops_HISRP) {
		/* _hoops_IRHH _hoops_RCRR _hoops_SR _hoops_GA'_hoops_RA _hoops_RCRPA _hoops_SHRRR _hoops_SPS _hoops_GHIR */
		_hoops_IGRCS (_hoops_ARRCS, null, null, 0);
		goto _hoops_HPAGR;
	}

	root = HI_LOD_Chain_Execute_Tristrips (
			phon->point_count, 
			(float *)phon->points,
			phon->tristrips,
			&_hoops_GPPHA, _hoops_AASIH - _hoops_PRRCS);
	_hoops_IGRCS (_hoops_ARRCS, _hoops_CGRCS, root, _hoops_HISRP);
	if (_hoops_CGRCS != null)
		FREE_ARRAY(_hoops_CGRCS, phon->point_count, int);

	/* _hoops_SP _hoops_GH _hoops_RH _hoops_HGRCS. _hoops_HRHII _hoops_SGS _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_AASH _hoops_HRGR _hoops_IRAP-_hoops_CCGAI */
	node = root;
	while (node != null) {
		if (node->_hoops_IAPHA.points != null)
			FREE_ARRAY_ALIGNED (node->_hoops_IAPHA.points, 3 * node->_hoops_IAPHA.pcount, float, 16);
		if (node->_hoops_IAPHA.faces != null)
			FREE_ARRAY (node->_hoops_IAPHA.faces, node->_hoops_IAPHA._hoops_RHGIR, int);
		if (node->_hoops_PHAS != null)
			FREE_ARRAY (node->_hoops_PHAS, node->_hoops_CAPHA, int);
		_hoops_IRRCS = node;
		node = node->next;
		FREE (_hoops_IRRCS, _hoops_HAPHA);
	}

	/* _hoops_IPCP _hoops_CPHAR _hoops_SSCP _hoops_RPII _hoops_SRSS. _hoops_PS _hoops_RRP _hoops_IS _hoops_HPGGR _hoops_SCH. */
	_hoops_ARRCS->_hoops_CPGPR |= _hoops_AHSGA;

	_hoops_HPAGR:
	/* _hoops_RCAPI _hoops_PGGC _hoops_RH _hoops_AH _hoops_RRCPR (_hoops_RPP _hoops_HAHH) */
	if (phon != _hoops_ARRCS) {
		/* _hoops_IH _hoops_RH _hoops_GCGC _hoops_IIGR _hoops_PPGS _hoops_HCPCA, _hoops_PHIH _hoops_CCPAR _hoops_IS _hoops_PSPP _hoops_SPCC */
		phon->point_count = _hoops_ARRCS->point_count;
		if (_hoops_ARRCS->type == _hoops_SCIP) {
			((Shell *)phon)->face_list_length = _hoops_HRRCS->face_list_length;
		}
		HI_Au_Revoir ((_hoops_HPAH *) phon);
	}
}


local void _hoops_CRRCS (
	Polyhedron alter *	phon,
	int 				_hoops_PRRCS,
	int 				_hoops_AASIH,
	float				_hoops_PRPHA,
	bool				_hoops_HRPHA,
	int					_hoops_HISRP) {
	_hoops_HAPHA		*node, *root, *_hoops_IRRCS;
	int					i, _hoops_SRRCS;

	UNREFERENCED(_hoops_HRPHA);

	if (phon->tristrips == null &&
		phon->face_count != 0) {
		HI_Assemble_3D_Tristrips (phon, (_hoops_SARHR)~0, false);
	}

	if (phon->tristrips == null ||
		phon->face_count < _hoops_HISRP) {
		/* _hoops_IRHH _hoops_RCRR _hoops_SR _hoops_GA'_hoops_RA _hoops_RCRPA _hoops_SHRRR _hoops_SPS _hoops_GHIR */
		_hoops_IGRCS (phon, null, null, _hoops_HISRP);
		return;
	}

	/* _hoops_IRS _hoops_GARAS _hoops_HRGI-_hoops_AGIR _hoops_GARCS _hoops_IIHA _hoops_GPP _hoops_RARCS _hoops_ISSGR */
	_hoops_SRRCS = 2 * phon->point_count; 
	i = 0;
	while (_hoops_SRRCS > _hoops_HISRP && i != _hoops_AASIH) {
		_hoops_SRRCS = (int)(_hoops_PRPHA * _hoops_SRRCS);
		i++;
	}
	_hoops_AASIH = i;

	/*
	_hoops_RPP (_hoops_IPGC->_hoops_GPRR == _hoops_HGCPR) {
		_hoops_SRRPR = _hoops_AARCS (
				_hoops_IPGC->_hoops_RSHS, 
				(_hoops_AIIC *)_hoops_IPGC->_hoops_RSSA,
				_hoops_IPGC->_hoops_RRCPR._hoops_PARCS,
				_hoops_IPGC->_hoops_RRCPR._hoops_SCAPA,
				_hoops_IISPH->_hoops_PRCCA._hoops_AHHSR[0],
				_hoops_HARCS - _hoops_IARCS);
	}
	_hoops_SHS
	*/
	{
		root = HI_Compute_LOD_Tristrips_Fast (
				phon->point_count, 
				(float *)phon->points,
				phon->tristrips,
				_hoops_PRPHA,
				_hoops_AASIH - _hoops_PRRCS);
	}
	_hoops_IGRCS (phon, null, root, _hoops_HISRP);

	/* _hoops_SP _hoops_GH _hoops_RH _hoops_HGRCS. _hoops_HRHII _hoops_SGS _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_AASH _hoops_HRGR _hoops_IRAP-_hoops_CCGAI */
	node = root;
	while (node != null) {
		if (node->_hoops_IAPHA.points != null)
			FREE_ARRAY_ALIGNED (node->_hoops_IAPHA.points, 3 * node->_hoops_IAPHA.pcount, float, 16);
		if (node->_hoops_IAPHA.faces != null)
			FREE_ARRAY (node->_hoops_IAPHA.faces, node->_hoops_IAPHA._hoops_RHGIR, int);
		if (node->_hoops_PHAS != null)
			FREE_ARRAY (node->_hoops_PHAS, node->_hoops_CAPHA, int);
		_hoops_IRRCS = node;
		node = node->next;
		FREE (_hoops_IRRCS, _hoops_HAPHA);
	}
	/* _hoops_IPCP _hoops_CPHAR _hoops_SSCP _hoops_RPII _hoops_SRSS. _hoops_PS _hoops_RRP _hoops_IS _hoops_HPGGR _hoops_SCH. */
	phon->_hoops_CPGPR |= _hoops_AHSGA;
}


local void _hoops_CARCS (
	_hoops_AIGPR *	_hoops_RIGC,
	Polyhedron alter *		phon,
	int						_hoops_GAIIH,
	int						_hoops_SISAR,
	float					_hoops_PRPHA) 
{
	int						level;
	int						count = phon->point_count;
	int *					mapping;

	if (count == 0)
		return;

	if (phon->_hoops_HGAIR == null) {
		ZALLOC (phon->_hoops_HGAIR, _hoops_PGAIR);
		phon->_hoops_HGAIR->type = _hoops_AGAIR;
		phon->_hoops_HGAIR->owner = (_hoops_HPAH *)phon;
		phon->_hoops_HGAIR->backlink = (_hoops_HPAH **) &(phon->_hoops_HGAIR);
		phon->_hoops_HGAIR->_hoops_HIHI = 1;
	}
	else {
		for (level = 0; level < _hoops_IGAIR; level++) {
			if (phon->_hoops_HGAIR->data[level] != null) {
				HI_Au_Revoir ((_hoops_HPAH *)(phon->_hoops_HGAIR->data[level]));
				phon->_hoops_HGAIR->data[level] = null;
			}
		}
	}

	ALLOC_ARRAY (mapping, phon->point_count, int);

	for (level = 0; level < _hoops_GAIIH; level++)
		count = int (_hoops_PRPHA * count);

	for (; level < _hoops_SISAR; level++) {
		count = int (_hoops_PRPHA * count);

		if (count > 0) {
			Shell *		_hoops_SPHPR;

			ZALLOC (_hoops_SPHPR, Shell);

			_hoops_SPHPR->type = _hoops_SCIP;
			_hoops_SPHPR->_hoops_HIHI = 1;
			_hoops_SPHPR->key = _hoops_AIRIR (_hoops_SPHPR);
			_hoops_SPHPR->bounding = phon->bounding;
			_hoops_SPHPR->point_count = -1;		/* _hoops_HAR _hoops_AISP _hoops_GAPR */
			_hoops_SPHPR->_hoops_SPHA = -1;		/* _hoops_HAR _hoops_AISP _hoops_GAPR */
			_hoops_SPHPR->face_count = -1;		/* _hoops_HAR _hoops_AISP _hoops_GAPR */

			ALLOC_ARRAY_ALIGNED (_hoops_SPHPR->points, count, Point, 16);
			_hoops_SPHPR->point_count = count;

			HI_Median_Cut (_hoops_RIGC, phon->point_count, phon->points, null,count, _hoops_SPHPR->points, null,mapping);

			_hoops_SCGCS (phon, (Polyhedron *)_hoops_SPHPR, mapping);

			phon->_hoops_HGAIR->data[level] = (Geometry *)_hoops_SPHPR;
		}
	}

	FREE_ARRAY (mapping, phon->point_count, int);
}

GLOBAL_FUNCTION void HI_Compute_Polyhedron_LOD (
	_hoops_AIGPR *	_hoops_RIGC,
	Polyhedron *		phon, 
	int 				_hoops_GAIIH,
	int 				_hoops_AASIH,
	_hoops_RRPHA			_hoops_ARPHA,
	float				_hoops_PRPHA,
	bool				_hoops_HRPHA,
	int 				_hoops_HISRP,
	int 				_hoops_RHPHA) {

	if (((Shell *)phon)->face_list_length == 0 && phon->tristrips == null)
		_hoops_CARCS (_hoops_RIGC, phon, _hoops_GAIIH, _hoops_AASIH, _hoops_PRPHA);
	else if (_hoops_ARPHA == _hoops_SHSRP)
		_hoops_CRRCS (phon, _hoops_GAIIH, _hoops_AASIH, _hoops_PRPHA, 
							_hoops_HRPHA, _hoops_HISRP);
	else
		_hoops_RRRCS (_hoops_RIGC, phon, _hoops_GAIIH, _hoops_AASIH, _hoops_PRPHA,
							_hoops_HRPHA, _hoops_HISRP, _hoops_RHPHA);
}


GLOBAL_FUNCTION void HD_Compute_Polyhedron_LOD (
	Net_Rendition const &		nr,
	Polyhedron *				phon, 
	int							_hoops_GAIIH) {
	_hoops_GRA const &	_hoops_RRA = nr->_hoops_ARA;
	Polyhedron *				_hoops_HCGCS;
	int							level;

	if (phon->point_count == 0) return;
	if (((Shell *)phon)->face_list_length == 0 && phon->tristrips == null)
		_hoops_CARCS (nr->_hoops_SRA->_hoops_RIGC, phon, _hoops_GAIIH, _hoops_RRA->_hoops_PRSI._hoops_IRSH, _hoops_RRA->_hoops_PRSI._hoops_PRPHA[0]);
	else if (_hoops_RRA->_hoops_PRSI._hoops_ARPHA == _hoops_SHSRP)
		_hoops_CRRCS (phon, _hoops_GAIIH, _hoops_RRA->_hoops_PRSI._hoops_IRSH, _hoops_RRA->_hoops_PRSI._hoops_PRPHA[0],
							BIT(_hoops_RRA->_hoops_PRSI.options, _hoops_RGSRP),
							_hoops_RRA->_hoops_PRSI._hoops_HISRP);
	else
		_hoops_RRRCS (nr->_hoops_SRA->_hoops_RIGC, phon, _hoops_GAIIH, _hoops_RRA->_hoops_PRSI._hoops_IRSH, _hoops_RRA->_hoops_PRSI._hoops_PRPHA[0],
							BIT(_hoops_RRA->_hoops_PRSI.options, _hoops_RGSRP),
							_hoops_RRA->_hoops_PRSI._hoops_HISRP, _hoops_RRA->_hoops_PRSI._hoops_RHPHA);

	/* _hoops_PCHIA _hoops_RH _hoops_HARH _hoops_SGS _hoops_AAPR _hoops_HAR _hoops_PSIGA _hoops_RAPR */
	for (level = 0; level < _hoops_IGAIR; level++) {
		_hoops_HCGCS = (Polyhedron *) phon->_hoops_HGAIR->data[level];
		if (_hoops_HCGCS == null)
			continue;
		if (ANYBIT(_hoops_RRA->_hoops_PRSI.options, _hoops_HRSRP) &&
			 BIT(_hoops_RRA->_hoops_PRSI.options, _hoops_GRSRP) &&
			 (_hoops_PCGCS (nr, _hoops_HCGCS) < _hoops_RRA->_hoops_PRSI._hoops_GHRGR[level])) {
			/* _hoops_RH _hoops_SCGR _hoops_GIIS _hoops_GPGH'_hoops_RA _hoops_PSIGA _hoops_RAPR */
			HI_Au_Revoir ((_hoops_HPAH *) _hoops_HCGCS);
			phon->_hoops_HGAIR->data[level] = null;
			continue;
		}
	}
}

local void _hoops_SARCS (
	Net_Rendition const &	nr,
	Polyhedron const *		_hoops_IPRI) {

	static int faces[6][4] = {
		{ 0, 2, 3, 1 }, /* -_hoops_SISR */
		{ 6, 4, 5, 7 }, /*	_hoops_SISR */
		{ 4, 0, 1, 5 }, /* -_hoops_HAPC */
		{ 2, 6, 7, 3 }, /*	_hoops_HAPC */
		{ 2, 0, 4, 6 }, /* -_hoops_SSH */
		{ 1, 3, 7, 5 }	/*	_hoops_SSH */
	};
	/* _hoops_PISSH _hoops_GHC _hoops_IH _hoops_RH _hoops_RSSI _hoops_IIGR _hoops_RH _hoops_IASC _hoops_RGCRA.  
	   "_hoops_GHGP" _hoops_GRS _hoops_SHH _hoops_PIISR _hoops_GGR _hoops_GPP _hoops_IRS _hoops_RIR-_hoops_IASC _hoops_AHCRR _hoops_HARGR, _hoops_RAS _hoops_RH _hoops_IPS. */
	static _hoops_ARPA planes[6] = {
		_hoops_ARPA (-1,  0,  0, 0),
		_hoops_ARPA ( 1,  0,  0, 0),
		_hoops_ARPA ( 0, -1,  0, 0),
		_hoops_ARPA ( 0,  1,  0, 0),
		_hoops_ARPA ( 0,  0, -1, 0),
		_hoops_ARPA ( 0,  0,  1, 0)
	};

	_hoops_SASC const &	cuboid = _hoops_IPRI->bounding->cuboid;
	Point	pts[8];
	cuboid._hoops_GPSC(&pts[0]);

	float	d[6];
	
	d[0] =	cuboid.min.x;
	d[1] = -cuboid.max.x;
	d[2] =	cuboid.min.y;
	d[3] = -cuboid.max.y;
	d[4] =	cuboid.min.z;
	d[5] = -cuboid.max.z;


	Point *		_hoops_PAGR;
	ALLOC_ARRAY (_hoops_PAGR, 4, Point);

	Polygon *	polygon;
	ZALLOC (polygon, Polygon);	
	polygon->_hoops_HIHI = 1;
	polygon->type = _hoops_RCIP;
	polygon->_hoops_CPGPR = _hoops_PHSSR;
	polygon->_hoops_SPGPR = false;
	polygon->_hoops_IPPGR = null;
	polygon->count = 4;
	polygon->allocated = 4;
	polygon->points = _hoops_PAGR;

	if (BIT(nr->transform_rendition->heuristics, _hoops_GPSA)) {
		for (int i = 0; i < 6; i++) {
			polygon->_hoops_RRHH = _hoops_ARHH;
			_hoops_PAGR[3] = pts[faces[i][0]];
			_hoops_PAGR[2] = pts[faces[i][1]];
			_hoops_PAGR[1] = pts[faces[i][2]];
			_hoops_PAGR[0] = pts[faces[i][3]];
			polygon->plane = planes[i];
			polygon->plane.d = d[i];
			_hoops_RCAIP (nr, polygon);
		}
	}
	else {
		for (int i = 0; i < 6; i++) {
			polygon->_hoops_RRHH = _hoops_ARHH;
			_hoops_PAGR[0] = pts[faces[i][0]];
			_hoops_PAGR[1] = pts[faces[i][1]];
			_hoops_PAGR[2] = pts[faces[i][2]];
			_hoops_PAGR[3] = pts[faces[i][3]];
			polygon->plane = planes[i];
			polygon->plane.d = d[i];
			_hoops_RCAIP (nr, polygon);
		}
	}
	_hoops_HPRH (polygon);
}


/* _hoops_CCRHS _hoops_RH _hoops_IASC _hoops_CISAR _hoops_CRGR _hoops_SHPR _hoops_GC, _hoops_PPR _hoops_HGCR _hoops_RH _hoops_GARRA 2D _hoops_ARRGR.
 * _hoops_CGP _hoops_SR _hoops_CHR _hoops_GGR _hoops_AIHP _hoops_PPR _hoops_ARIP _hoops_IIGR _hoops_RH _hoops_IASC _hoops_HRGR _hoops_GHIPR _hoops_RH _hoops_RHC, _hoops_HGRRA, _hoops_IIH _hoops_HRGR
 * _hoops_HAR _hoops_GSGS _hoops_PSIGA _hoops_HPHS _hoops_SGS _hoops_RGR _hoops_API _hoops_PAH _hoops_GSRS, _hoops_HIS _hoops_SCH _hoops_GAGPR _hoops_HRS _hoops_RCPP. */
local bool _hoops_GPRCS (
	Bounding const &			bounding,
	_hoops_HHCR const &	_hoops_IHCR,
	_hoops_SASC alter &		cuboid) {
	
	_hoops_RPRA const *			matrix = _hoops_IHCR->matrix->data.elements;

	Point						pt[8], _hoops_RPRCS[8];

	bounding->cuboid._hoops_GPSC(&_hoops_RPRCS[0]);

	/* _hoops_HIHP _hoops_RH _hoops_IASC _hoops_IPIS'_hoops_GRI _hoops_GRPC */
	if (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH) {
		for (int i = 0; i < 8; i++) {
			pt[i].x = _hoops_HPRA (matrix, _hoops_RPRCS[i]);
			pt[i].y = _hoops_IPRA (matrix, _hoops_RPRCS[i]);
			/* _hoops_HSGR _hoops_SGPSH[_hoops_HAS]._hoops_SSH = _hoops_APRCS (_hoops_RSGA, _hoops_PPRCS[_hoops_HAS]); _hoops_GA'_hoops_RA _hoops_RRP _hoops_RH _hoops_SSH _hoops_ISRR */
			pt[i].z = 0.0f;
			float w = _hoops_PHCP (matrix, _hoops_RPRCS[i]);
			if (w <= 0)
				return false;
			pt[i].x /= w;
			pt[i].y /= w;
		}
	}
	else {
		for (int i = 0; i < 8; i++) {
			pt[i].x = _hoops_HPRA (matrix, _hoops_RPRCS[i]);
			pt[i].y = _hoops_IPRA (matrix, _hoops_RPRCS[i]);
			pt[i].z = 0.0f;
		}
	}

	cuboid = _hoops_SASC(8, pt);

	return true;
}


/* _hoops_HPRCS _hoops_HII _hoops_IPRCS _hoops_GGR _hoops_CPRCS... */
// _hoops_SPRCS _hoops_HASC _hoops_CCA _hoops_SGCR _hoops_RRGR?
// _hoops_PASC _hoops_AA _hoops_GIH?
local float _hoops_GHRCS (
	Net_Rendition const &		nr,
	Bounding const &			bounding) {

	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;

	_hoops_RPRA alter			_hoops_RHRCS[4];

	HI_Matmul_43_by_43 (
		&_hoops_IHCR->_hoops_IPH->data.elements[0][0],
		&_hoops_IHCR->_hoops_SPH->_hoops_PRPA.elements[0][0],
		(float alter *) _hoops_RHRCS);

	_hoops_CAIS const &	sphere = bounding->sphere;

	float	z = _hoops_CPRA (_hoops_RHRCS, sphere.center);

	float	_hoops_AHRCS = sphere.radius * 
				_hoops_SGIHR(_hoops_RHRCS[2][0]*_hoops_RHRCS[2][0] + _hoops_RHRCS[2][1]*_hoops_RHRCS[2][1] + _hoops_RHRCS[2][2]*_hoops_RHRCS[2][2]);

	float	_hoops_RPSC = z - _hoops_AHRCS + _hoops_IHCR->_hoops_SPH->_hoops_SRIR;

	return _hoops_RPSC;
}


local Geometry * _hoops_PHRCS (
	_hoops_PGAIR const *	node,
	int					start) {
	int					i;

	if (node == null)
		return null;
	for (i = start; i < _hoops_IGAIR; i++) {
		if (node->data[i] != null) {
			return node->data[i];
		}
	}
	return null;
}

local Geometry * _hoops_HHRCS (
	Net_Rendition const &		nr,
	Polyhedron const *			phon,
	int 						_hoops_IHRCS,
	int 						_hoops_CHRCS) {

	switch (_hoops_IHRCS) {
		case _hoops_CHSRP:
			if (phon->_hoops_HGAIR == null) {
				if (_hoops_CHRCS == 1)
					_hoops_SARCS(nr, phon);
			}
			else if (_hoops_CHRCS == 1 ||
					 phon->_hoops_HGAIR->data[_hoops_CHRCS-2] != null)
				_hoops_SARCS(nr, phon);
			return null;

	    case _hoops_SPSRP:
			return null;

	    case _hoops_RHSRP:
	    case _hoops_AHSRP:
			if (phon->_hoops_HGAIR) {
				while (_hoops_CHRCS >= 0) {
					if (phon->_hoops_HGAIR->data[_hoops_CHRCS])
						return phon->_hoops_HGAIR->data[_hoops_CHRCS];
					--_hoops_CHRCS;
				}
			}
			return (Geometry *)phon;

	    default:
			return (Geometry *)phon;
	}
}


/* _hoops_SSS _hoops_RH _hoops_RPHR _hoops_SPIGA _hoops_SCCI. 
 * _hoops_HRS _hoops_IHPR _hoops_RPP _hoops_RH _hoops_RRCPR _hoops_CGH _hoops_SHH _hoops_CHCC */
local Polyhedron* _hoops_SHRCS (
	Net_Rendition const &		nr,
	Polyhedron *				phon) {

	Polyhedron const *			_hoops_CPCR = null;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	int 						_hoops_IISRP;
	int 						i;
	int 						_hoops_RCSRP = nr->_hoops_ARA->_hoops_PRSI._hoops_RCSRP;
	Geometry *					thing;

	if (phon == null || phon->bounding._hoops_HICAR())
		return null;

	if (BIT(dc->flags, _hoops_HSAGR) || 
		!BIT(nr->_hoops_ARA->_hoops_PRSI.options, _hoops_HRSI)) {

		if (phon->points != null)
			return phon;		/* _hoops_APIP _hoops_AIRA _hoops_RAAA */

		if (_hoops_RCSRP == _hoops_SPSRP)
			return null;

		/* _hoops_GIPHR _hoops_IH _hoops_RH _hoops_SRS _hoops_GRAA-_hoops_IRAP _hoops_AHAP _hoops_SGS _hoops_SR _hoops_PAH _hoops_PGSA */
		if (phon->_hoops_HGAIR == null)
			return null;

		for (i = 0; i < _hoops_IGAIR; i++) {
			if (phon->_hoops_HGAIR->data[i] != null) {
				break;
			}
		}

		if (i == _hoops_IGAIR)
			return null;		/* _hoops_GSGI _hoops_ISAP */

		thing = phon->_hoops_HGAIR->data[i];
		if (thing->next == null &&
			(thing->type == _hoops_SCIP || thing->type == _hoops_GSIP)) {
			_hoops_CPCR = (Polyhedron *) phon->_hoops_HGAIR->data[i];
			goto _hoops_HPAGR;		/* _hoops_GSGI _hoops_IRS _hoops_CPHAR */
		}
		else {
			Geometry const *		_hoops_GIRCS = dc->_hoops_RAI;
			_hoops_AAGSP *		_hoops_PAGSP = dc->_hoops_SPA;

			dc->_hoops_SPA = dc->_hoops_ISAGR;
			HD_Standard_Render (nr, thing, _hoops_RAPI, false); 
			dc->_hoops_SPA = _hoops_PAGSP;
			dc->_hoops_RAI = _hoops_GIRCS;
			return null;		/* _hoops_GSGI _hoops_CPHP _hoops_SHS */
		}
	}	

	/* _hoops_CSGA _hoops_RPP _hoops_SR _hoops_RRP _hoops_IS */
	if (BIT (nr->_hoops_ARA->_hoops_PRSI.options, _hoops_SGSRP) &&
		phon->_hoops_HGAIR == null)
		HD_Compute_Polyhedron_LOD (nr, phon, 0);

	if (phon->_hoops_HGAIR == null) {
		if (_hoops_RCSRP == _hoops_RHSRP)
			return phon;
		
		if (_hoops_RCSRP == _hoops_AHSRP &&
			phon->face_count < nr->_hoops_ARA->_hoops_PRSI._hoops_HISRP)
			return phon;
	}

	_hoops_IISRP = nr->_hoops_ARA->_hoops_PRSI._hoops_IISRP;
	if (_hoops_IISRP < 0 || !BIT(nr->_hoops_ARA->_hoops_PRSI.options, _hoops_HASRP)) {
		/* 
		 * _hoops_PHIRC _hoops_HRGR _hoops_GRGR 
		 */
		float const *		target = nr->_hoops_ARA->_hoops_PRSI._hoops_AISRP;
		float				w, h, area = 0, _hoops_RIRCS = 0;
		Polyhedron const *	_hoops_IIRHA = null;

		if (BIT(nr->_hoops_ARA->_hoops_PRSI.options, _hoops_AASRP)) {
			float _hoops_CGSIR = _hoops_GHRCS (nr, phon->bounding);

			_hoops_CPCR = phon;
			if (_hoops_CGSIR >target[0]) {
				for (i = 1; i < _hoops_IGAIR; i++) {
					if (_hoops_CGSIR < target[i]) {
						break;
					}
				}
				if (phon->_hoops_HGAIR == null) {
					switch (_hoops_RCSRP) {
						case _hoops_SPSRP:
							return 0;
						case _hoops_CHSRP:
							if (i>1)
								return null;
							_hoops_HHHI; /* _hoops_HSSC _hoops_RHIR _hoops_IS _hoops_AIRCS _hoops_AGIR */
						case _hoops_GHSRP:
							_hoops_SARCS (nr, phon);
							return null;
						/* _hoops_SHIR: _hoops_AA _hoops_ISAP */
					}
				} 
				else {
					if (phon->_hoops_HGAIR->data[i-1] != null)
						_hoops_CPCR = (Polyhedron *) phon->_hoops_HGAIR->data[i-1];
					else switch (_hoops_RCSRP) {
						case _hoops_SPSRP:
							return null;
						case _hoops_CHSRP:
							if (i>1 && phon->_hoops_HGAIR->data[i-2]==null)
								return null;
							_hoops_HHHI; /* _hoops_HSSC _hoops_RHIR _hoops_IS _hoops_AIRCS _hoops_AGIR */
						case _hoops_GHSRP:
							_hoops_SARCS (nr, phon);
							return null;
						default: {
							while (--i>1) {
								if (phon->_hoops_HGAIR->data[i-1] != null) {
									_hoops_CPCR = (Polyhedron *) phon->_hoops_HGAIR->data[i-1];
									break;
								}
							}
						}
					}
				}
			}
		}
		else {		// _hoops_SPIGA _hoops_SIGSP _hoops_HPP _hoops_HHH _hoops_HPPSR _hoops_RII _hoops_HSAR _hoops_GIRA
			/* _hoops_HIHP _hoops_IASC _hoops_CISAR _hoops_CRGR _hoops_CSPH, _hoops_PPR _hoops_CSGA _hoops_CSPH _hoops_CCAC */
			_hoops_SASC	cuboid;
			if	(_hoops_GPRCS (phon->bounding, nr->transform_rendition, cuboid)) {
				w = cuboid.max.x - cuboid.min.x;
				h = cuboid.max.y - cuboid.min.y;
			}
			else {
				w = (float)nr->_hoops_SRA->current._hoops_PRPSR.x;
				h = (float)nr->_hoops_SRA->current._hoops_PRPSR.y;
			}
			area = w * h;
			if (BIT(nr->_hoops_ARA->_hoops_PRSI.options, _hoops_RASRP))
				_hoops_RIRCS = 100.0f * area / 
					((nr->_hoops_SAIR->_hoops_PHRA.right - nr->_hoops_SAIR->_hoops_PHRA.left) * 
					 (nr->_hoops_SAIR->_hoops_PHRA.top - nr->_hoops_SAIR->_hoops_PHRA.bottom));
			else if (!BIT(nr->_hoops_ARA->_hoops_PRSI.options, _hoops_SRSRP))
				area /= (nr->_hoops_SRA->current._hoops_HAP.x *
						 nr->_hoops_SRA->current._hoops_HAP.y);

			if (BIT(nr->_hoops_ARA->_hoops_PRSI.options, _hoops_RASRP)) {
				for (i = 0; i < _hoops_IGAIR; i++)
					if (_hoops_RIRCS > target[i])
						break;
				if (i == 0) {
					_hoops_CPCR = phon;
					if (phon->point_count == 0) {
						/* _hoops_RPP _hoops_RH _hoops_AIRA _hoops_HRGR _hoops_SAHR _hoops_IRS _hoops_GGAGA, _hoops_SSS _hoops_RH _hoops_SRS _hoops_GRAA-_hoops_IRAP _hoops_PIRA _hoops_PPR _hoops_SGH _hoops_SCH */
						if ((thing = _hoops_PHRCS (phon->_hoops_HGAIR, 0)) != null)
							_hoops_CPCR = (Polyhedron *)thing;
					}
				} 
				else if ((thing = _hoops_PHRCS (phon->_hoops_HGAIR, i-1)) != null) {
					/* _hoops_CPHP _hoops_HRGR _hoops_HHPA _hoops_HPGR _hoops_PAR _hoops_ARRS _hoops_RH _hoops_GSISC _hoops_PAPA */
					_hoops_CPCR = (Polyhedron *)thing;
				}
				else if ((thing = _hoops_HHRCS (nr, phon, _hoops_RCSRP, i-1)) != null) {
					/* _hoops_GSGI _hoops_CPHP _hoops_IS _hoops_HSSC _hoops_ISSC _hoops_IS (_hoops_PAR _hoops_RPP _hoops_PAGPR _hoops_AIAH _hoops_ACIRC _hoops_SCH) */
					_hoops_CPCR = (Polyhedron *)thing;
				}
			}
			else {
				/* _hoops_HHH _hoops_PISRP _hoops_RII _hoops_HSAR _hoops_PIRCS */
				if (phon->point_count &&
					phon->face_count/area < target[0]) {
					_hoops_CPCR = phon;
				}
				else {
					/* _hoops_GGR _hoops_RH _hoops_HSPR _hoops_HAPR, "_hoops_AHCAH" _hoops_HRGR _hoops_RH _hoops_PHSRP _hoops_RRCPR _hoops_GSGI _hoops_HIS _hoops_SGIP */
					_hoops_IIRHA = phon;
					for (i = 0; i < _hoops_IGAIR; i++) {
						if (phon->_hoops_HGAIR &&
							phon->_hoops_HGAIR->data[i] != null) {
							thing = phon->_hoops_HGAIR->data[i];
							if (thing->type != _hoops_SCIP && thing->type != _hoops_GSIP) {
								HE_ERROR (HEC_LOD, HES_INVALID_TYPE, 
									"non-polyhedron lods supported only with clamping, area percentage thresholds, or distance thresholds");
								return 0;
							}
							if (((Polyhedron *) thing)->face_count != 0)
								_hoops_IIRHA = (Polyhedron *) thing;
						}
						if ((_hoops_IIRHA->face_count / area) < target[i]) {
							_hoops_CPCR = (Polyhedron *)_hoops_IIRHA;
							break;
						}
						if (ANYBIT (_hoops_RCSRP, 
									_hoops_RHSRP |
									_hoops_AHSRP | 
									_hoops_IHSRP))
							_hoops_CPCR = (Polyhedron*)_hoops_IIRHA;
					}
				}
			}
		}
		if (!_hoops_CPCR)
			return 0;
		if (_hoops_CPCR->type != _hoops_SCIP && _hoops_CPCR->type != _hoops_GSIP) {
			Geometry const *	_hoops_GIRCS = dc->_hoops_RAI;
			_hoops_AAGSP *	_hoops_PAGSP = dc->_hoops_SPA;

			dc->_hoops_SPA = dc->_hoops_ISAGR;
			HD_Standard_Render (nr, (Geometry const *)_hoops_CPCR, _hoops_RAPI, false); 
			dc->_hoops_SPA = _hoops_PAGSP;
			dc->_hoops_RAI = _hoops_GIRCS;
			return null;
		}
	}
	else {
		/*
		 * _hoops_PHIRC _hoops_AGIR 
		 */
		_hoops_CPCR = phon; /* _hoops_SHIR */
		thing = null; /* _hoops_IRAP _hoops_CCGR _hoops_SR _hoops_SSS _hoops_IRS _hoops_PGSA _hoops_AHCAH */
		if (_hoops_IISRP > _hoops_IGAIR)
			_hoops_IISRP = _hoops_IGAIR;
		if (_hoops_IISRP == 0) {
			goto _hoops_HPAGR;
		}
		_hoops_IISRP -= 1; /* _hoops_PRCCA 0 _hoops_HRGR _hoops_AIRA _hoops_RRCPR.	 _hoops_CPS _hoops_GGR _hoops_ARCCA _hoops_HRGR _hoops_PRCCA _hoops_PAPA >= 1 */
		if (phon->_hoops_HGAIR != null &&
			phon->_hoops_HGAIR->data[_hoops_IISRP] != null) {
			/* _hoops_PIHGR: _hoops_RH _hoops_CGCH _hoops_PRCCA _hoops_SR _hoops_AAPR _hoops_HCHAR _hoops_IH _hoops_CSAP _hoops_HHPA.  */
			thing = phon->_hoops_HGAIR->data[_hoops_IISRP];
			if (thing->next == null &&
				(thing->type == _hoops_SCIP || thing->type == _hoops_GSIP)) {
				_hoops_CPCR = (Polyhedron *) thing;
				goto _hoops_HPAGR;
			}
			else {
				Geometry const *		_hoops_GIRCS = dc->_hoops_RAI;
				_hoops_AAGSP *		_hoops_PAGSP = dc->_hoops_SPA;

				dc->_hoops_SPA = dc->_hoops_ISAGR;
				HD_Standard_Render (nr, thing, _hoops_RAPI, false); 
				dc->_hoops_SPA = _hoops_PAGSP;
				dc->_hoops_RAI = _hoops_GIRCS;
				return null;
			}
		}
		/* _hoops_GACC _hoops_PIHGR: _hoops_SRS _hoops_AHSGH _hoops_HAR _hoops_HHPA, _hoops_PPR _hoops_PSP _hoops_IIPGA */
		if (_hoops_RCSRP == _hoops_SPSRP)
			return null;

		/* 
		 * _hoops_HA _hoops_RH _hoops_ACIPR _hoops_CIPH.	_hoops_CAHA _hoops_GGSR _hoops_PGAP _hoops_IIPGA _hoops_IS _hoops_SGH 
		 */
		if (phon->_hoops_HGAIR != null) {
			/* _hoops_GIPHR _hoops_IH _hoops_IRS _hoops_APIP _hoops_SPIGA _hoops_HPGR _hoops_IRS _hoops_PHPA (_hoops_HAHP) _hoops_PAPA */
			for (i = _hoops_IISRP; i < _hoops_IGAIR; i++) {
				if (phon->_hoops_HGAIR->data[i] != null) {
					thing = phon->_hoops_HGAIR->data[i];
					break;
				}
			}
			if (thing == null) {
				if (_hoops_RCSRP == _hoops_CHSRP) {
					if (_hoops_IISRP == 0 ||
						phon->_hoops_HGAIR->data[_hoops_IISRP-1] != null) {
						_hoops_SARCS (nr, phon);
					}
					return null;
				}
				else for (i = _hoops_IISRP; i >= 0; i--) {
					/* _hoops_GIPHR _hoops_IH _hoops_IRS _hoops_APIP _hoops_SPIGA _hoops_HPGR _hoops_IRS _hoops_GSSC (_hoops_HIRCS) _hoops_PAPA */
					if (phon->_hoops_HGAIR->data[i] != null) {
						thing = phon->_hoops_HGAIR->data[i];
						break;
					}
				}
			}
		}
		else if (_hoops_RCSRP == _hoops_CHSRP) {
			if (_hoops_IISRP == 0)
				_hoops_SARCS (nr, phon);
			return null;
		}
		
		if (ANYBIT (_hoops_RCSRP, _hoops_AHSRP | _hoops_IHSRP)) {
			int			_hoops_IIRCS;
			float		_hoops_PRPHA;
			int			_hoops_HISRP;

			if (thing == null)
				thing = (Geometry *)_hoops_CPCR;
			if (thing->type != _hoops_SCIP &&
				thing->type != _hoops_GSIP) {
				/* _hoops_SIGS _hoops_CGIC _hoops_IRS _hoops_CSHHR _hoops_PIRA _hoops_IH "_hoops_IHPH" _hoops_IH _hoops_GRAA-_hoops_SCHS.
				 * _hoops_PSPC, _hoops_SR _hoops_APGP _hoops_HPCAR _hoops_GRAA-_hoops_SCHS _hoops_CHR _hoops_SHR _hoops_IHPH */
				return 0;
			}
			_hoops_PRPHA = nr->_hoops_ARA->_hoops_PRSI._hoops_PRPHA[0]; /* _hoops_ASIGA _hoops_IRHS _hoops_RIGRP _hoops_IH _hoops_CIRCS */
			_hoops_HISRP = nr->_hoops_ARA->_hoops_PRSI._hoops_HISRP;

			_hoops_IIRCS = (_hoops_HISRP > (_hoops_PRPHA * _hoops_CPCR->point_count));
			if (_hoops_IIRCS) {
				goto _hoops_HPAGR;
			}
			else if (_hoops_RCSRP == _hoops_AHSRP) {
				return null;
			}
			else {
				_hoops_SARCS (nr, phon);
				return null;
			}
		} 
		else if (_hoops_RCSRP == _hoops_RHSRP) {
			if (thing == null)
				thing = (Geometry *)_hoops_CPCR;
			if (thing == (Geometry *)phon ||
				thing->next == null &&
					(thing->type == _hoops_SCIP || thing->type == _hoops_GSIP)) {
				_hoops_CPCR = (Polyhedron *) thing;
				goto _hoops_HPAGR;
			}
			else {
				Geometry const *		_hoops_GIRCS = dc->_hoops_RAI;
				_hoops_AAGSP *	_hoops_PAGSP = dc->_hoops_SPA;

				dc->_hoops_SPA = dc->_hoops_ISAGR;
				HD_Standard_Render (nr, thing, _hoops_RAPI, false); 
				dc->_hoops_SPA = _hoops_PAGSP;
				dc->_hoops_RAI = _hoops_GIRCS;
				return null;
			}
		}
		else if (_hoops_RCSRP == _hoops_GHSRP) {
			_hoops_SARCS (nr, phon);
			return null;
		}
	}

_hoops_HPAGR:
	return (Polyhedron*)_hoops_CPCR;
}
#endif

 
GLOBAL_FUNCTION void HD_Std_3D_Polyhedron (
	Net_Rendition const & 		inr,
	Polyhedron const *			_hoops_IPRI) 
{
	Net_Rendition		 		nr = inr;
	Display_Context alter *		dc = (Display_Context alter *) nr->_hoops_SRA;
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	_hoops_SGRGH alter *		node = null;
	int							stage = 0;
	float						_hoops_IARGH = 0.0f;
	unsigned Integer32			action_mask = nr->_hoops_SRA->_hoops_IPCI->mask;
	bool						_hoops_ARRGH = false;
	Color_Object				_hoops_GSSCC = 0;
	_hoops_CRCP const *				_hoops_SRCP = null;
	_hoops_HICS				path;

	ASSERT(_hoops_IPRI->owner == null || _hoops_IPRI->owner->_hoops_RHAGR._hoops_ASAGP(dc->_hoops_RIGC->thread_id));

	_hoops_SSAGR(&_hoops_IPRI->local_vertex_attributes._hoops_ICRRA);

	if (dc->_hoops_AHSI != null) {
		node = dc->_hoops_AHSI->_hoops_AARGH;
		_hoops_IARGH = dc->_hoops_AHSI->_hoops_IARGH;
		_hoops_SRCP = dc->_hoops_AHSI->segment;
		path = dc->_hoops_AHSI->path;
	}

	if (node == null) {
		Bounding const & _hoops_RCHS = _hoops_IPRI->bounding;
		_hoops_RCHS._hoops_SSAGR();

		if (!ANYBIT (action_mask, _hoops_PCSI) &&
			!BIT (nr->_hoops_RGP, T_INTERIOR_SILHOUETTE_EDGES) &&
			!ALLBITS (_hoops_RRGH->_hoops_CSA, _hoops_HCSI))
			return;

		if (!BIT (dc->flags, _hoops_HSAGR) &&
			!BIT (nr->current, _hoops_CRSI) &&
			!BIT (nr->current, _hoops_PGCGA) &
			!BIT (_hoops_IHCR->flags, _hoops_CHHS) &&
			ANYBIT (_hoops_IHCR->_hoops_APH, Heur_Culling_EXTENT|_hoops_RIHS|Heur_Culling_VIEW_FRUSTUM)) {

			Test	_hoops_ASIS = Test_DISJOINT;
			float	_hoops_CIHS = 0.0f;
			int		_hoops_SIHS = 0;

			if (!_hoops_RCHS._hoops_HICAR()) {
				_hoops_ICP const &	_hoops_CCP = nr->_hoops_GSP;
				float						_hoops_SRIHS = 0.0f;
			
				if (!BIT (nr->current, _hoops_CRSI) &&
					ANYBIT (_hoops_IHCR->_hoops_APH, Heur_Culling_EXTENT|_hoops_RIHS) &&
					BIT (_hoops_RRGH->_hoops_SHHS, _hoops_PIIRP)) {

					if (BIT (_hoops_IHCR->_hoops_APH, _hoops_RIHS))
						_hoops_SIHS = _hoops_RRGH->_hoops_GCHS;
					if (BIT (_hoops_IHCR->_hoops_APH, Heur_Culling_EXTENT))
						_hoops_SIHS = _hoops_IAAA(_hoops_RRGH->_hoops_GRGC, _hoops_SIHS);
				}

				if (BIT (nr->_hoops_RGP, T_VERTICES) ||
					_hoops_IPRI->local_vertex_attributes._hoops_CPIAA > 0) {

					if (BIT (_hoops_CCP->glyph->flags, _hoops_GSIAP))
						_hoops_SRIHS = 1.0f;
					else if (_hoops_CCP->ysize < 0)
						_hoops_SRIHS = 0.5f * HD_Compute_Generic_Size (nr, _hoops_CCP->_hoops_PHP, _hoops_CCP->_hoops_HHP, 1.0f, false, 0, true);
					else 
						_hoops_SRIHS = _hoops_CCP->ysize;

					if (_hoops_IPRI->point_count == 1 && _hoops_SIHS < _hoops_SRIHS)
						_hoops_SIHS = 0;
				}

				float	_hoops_RRIIH = _hoops_IAAA(nr->_hoops_SAIR->_hoops_SCIH.left - nr->_hoops_SAIR->_hoops_HHCAR.left, _hoops_SRIHS);

				HD_Transform_And_Test_Simple_Sphere (nr, 1, &_hoops_RCHS->sphere, null, _hoops_RRIIH,
													 _hoops_SIHS, &_hoops_ASIS, null, &_hoops_CIHS);
			}

			switch (_hoops_ASIS) {
				case Test_DISJOINT: {
					_hoops_GPRH(_hoops_PIRGH)++;
					return;
				} _hoops_HHHI;

				case _hoops_GAAGI: {
					if (BIT (_hoops_IHCR->_hoops_APH, Heur_Culling_VIEW_FRUSTUM) &&
						!ANYBIT (_hoops_IHCR->flags, _hoops_AIHS|_hoops_PSASP))
						nr.Modify()->transform_rendition.Modify()->flags |= _hoops_AIHS;
				} break;

				case _hoops_AAAGI:
				case _hoops_PAAGI: {

					if (ANYBIT (_hoops_IHCR->_hoops_APH, Heur_Culling_EXTENT|_hoops_RIHS) &&
						BIT (_hoops_RRGH->_hoops_SHHS, _hoops_PIIRP)) {

						if (_hoops_RRGH->_hoops_PCHS == Heur_MAX_EXTENT_MODE_DEFER &&
							(!BIT (_hoops_IHCR->_hoops_APH, _hoops_RIHS) ||
							  _hoops_CIHS > _hoops_RRGH->_hoops_GCHS)) {

							// _hoops_PAH'_hoops_RA _hoops_PSCPR _hoops_CCSHP _hoops_APGR _hoops_CAPRR, _hoops_HAR _hoops_GHGC _hoops_SIRCS _hoops_HIASR
							if (!BIT(dc->flags, _hoops_RASS) ||
								(BIT (nr->current, _hoops_CSGGR) &&
								 ANYBIT (_hoops_RRGH->_hoops_SRI, _hoops_GRAAP|_hoops_HSSS|_hoops_PRAAP|_hoops_SICI)))
									break;		

							Net_Rendition					_hoops_CRAI = nr.Copy();
							_hoops_HHCR alter &		_hoops_GGCC = _hoops_CRAI->transform_rendition.Modify();
							_hoops_CGRA alter &		_hoops_GCRCS = _hoops_CRAI->_hoops_SAIR.Modify();
							
							if (_hoops_ASIS == _hoops_AAAGI &&
								BIT (_hoops_IHCR->_hoops_APH, Heur_Culling_VIEW_FRUSTUM) &&
								!BIT (_hoops_IHCR->flags, _hoops_PSASP))
								_hoops_GGCC->flags |= _hoops_AIHS;

							_hoops_GGCC->flags |= _hoops_CAHPP|_hoops_APGSP|_hoops_CHHS;
							_hoops_GCRCS->_hoops_ASIHP |= _hoops_ACARP;

							int _hoops_HCHS = (int) (_hoops_CIHS * (float)_hoops_ICHS / (float)_hoops_SIHS);

							HD_Defer_Tree_Batch (_hoops_CRAI, _hoops_SRCP, path, _hoops_HCHS, _hoops_IPRI);
						}
						else
							_hoops_GPRH(_hoops_CCHS)++;
						return;
					}
				}	break;

				default:break;
			}

			nr.Modify()->transform_rendition.Modify()->flags |= _hoops_CHHS;
		}
	}
	else {
		stage = node->stage;
		_hoops_ARRGH = node->_hoops_ARRGH;
		_hoops_GSSCC = node->_hoops_GSSCC;
	}

	switch (stage) {
		case Polyhedron_Progress_Setup: {
			if (_hoops_IPRI->_hoops_IPPGR) {
				_hoops_HPPIR const * _hoops_IPPIR = (_hoops_HPPIR const *)_hoops_IPRI->_hoops_IPPGR;
				if (_hoops_IPRI->_hoops_IPPGR->next || _hoops_IPRI->_hoops_IPPGR->type != HK_USER_OPTIONS ||
					_hoops_IPPIR->_hoops_IGGSA != null ||
					(_hoops_IPPIR->_hoops_AGGSA && _hoops_IPPIR->_hoops_AGGSA->Count() != 0)) {

					// _hoops_RH _hoops_HAGIR _hoops_ARI _hoops_HRGR _hoops_RPP _hoops_SPR _hoops_CPHAR _hoops_SSCP _hoops_PCCP _hoops_HCSP
					// _hoops_PSCR _hoops_IRS _hoops_ARGHR _hoops_GRS _hoops_HIS _hoops_SCH _hoops_HRGR _hoops_GIH _hoops_IS _hoops_HGCR _hoops_CAPR _hoops_RPHGA
					// _hoops_ARR _hoops_HPGR _hoops_RH _hoops_CAGH _hoops_PAPA _hoops_PPR _hoops_PSCR _hoops_RCRCS _hoops_GPP _hoops_RH _hoops_IRGH _hoops_SPR
					// _hoops_HRII _hoops_HSAR _hoops_HASC _hoops_RH _hoops_SHSC _hoops_HIGR _hoops_RIR _hoops_IGCI
					_hoops_CIGIP const &	_hoops_SIGIP = nr->_hoops_GCGIP;
					if (_hoops_SIGIP->_hoops_IGGSA && _hoops_SIGIP->_hoops_IGGSA->Count()>1)
						HD_Merge_User_Indices(_hoops_SIGIP);

					HD_Downwind_Rendition (nr, _hoops_IPRI->_hoops_IPPGR, T_FACES|T_EDGES|T_VERTICES, true);

					Attribute const *_hoops_HPHCR = _hoops_IPRI->_hoops_IPPGR;
					while (_hoops_HPHCR && _hoops_HPHCR->type <= HK_COLOR) {
						if (_hoops_HPHCR->type == HK_COLOR) {
							_hoops_SSGI const *color = (_hoops_SSGI const *)_hoops_HPHCR;
							_hoops_GSSCC = color->_hoops_GHA;
							break;				
						}
						_hoops_HPHCR = _hoops_HPHCR->next;
					} 

					if (BIT (nr->_hoops_RCSHR, _hoops_AHIHP) &&
						!BIT (nr->current, _hoops_AHIHP)) {
						if (!BIT(dc->flags, _hoops_RGSGA)) {
							HD_Prepare_Geometry_Transparency (nr, "polyhedron transparency");
							_hoops_ARRGH = true;
						}
					}
				}
			}
			if (_hoops_IPRI->local_vertex_attributes._hoops_HIRRA != 0 &&
				(BIT (nr->_hoops_RGP, T_VERTICES) ||
				 _hoops_IPRI->local_vertex_attributes._hoops_CPIAA > 0) &&
				!BIT (nr->current, _hoops_AHIHP) &&
				!BIT(dc->flags, _hoops_RGSGA)) {
				nr.Modify()->_hoops_RCSHR |= _hoops_AHIHP;
				HD_Prepare_Geometry_Transparency (nr, "polyhedron transparency");
				_hoops_ARRGH = true;
			}

#ifndef DISABLE_LOD_GENERATION
			if ((!BIT(dc->flags, _hoops_HSAGR) && 
					BIT(nr->_hoops_ARA->_hoops_PRSI.options, _hoops_HRSI)) ||
				(_hoops_IPRI->points == null && 
					nr->_hoops_ARA->_hoops_PRSI._hoops_RCSRP != _hoops_SPSRP)) {

				Polyhedron *	_hoops_ACRCS = null;

				if ((_hoops_ACRCS = _hoops_SHRCS (nr, (Polyhedron alter *)_hoops_IPRI)) == null) {
					stage = Polyhedron_Progress_Cleanup;
					break;
				}

				if (_hoops_ACRCS)
					_hoops_IPRI = _hoops_ACRCS;
			}
#endif

			if (_hoops_IPRI->type == _hoops_SCIP && !((Shell *)_hoops_IPRI)->_hoops_GSAPA) {
				HI_Repair_Shell_Edges (dc->_hoops_RIGC, (Shell alter *)_hoops_IPRI);
			}

			_hoops_HSCIS (_hoops_IHCR, (Polyhedron alter *)_hoops_IPRI);

			_hoops_GPRH(_hoops_AIRGH)++;
			++stage;
		}	_hoops_HHHI;



		case Polyhedron_Progress_Tristrips: {
			if (BIT (action_mask, _hoops_PGRI))
				node = _hoops_RGGCS (nr, node, _hoops_GSSCC, _hoops_IPRI);

			//_hoops_RPP (_hoops_GIIS != _hoops_IRAP && _hoops_GIIS->_hoops_CRHH != _hoops_IRAP)
			//	_hoops_IHSA;
			//_hoops_SHS
				++stage;

			if (_hoops_GGPGR(nr)) {
				if (node == null)
					node = POOL_NEW(dc->memory_pool, _hoops_SGRGH)(_hoops_IPRI);

				goto _hoops_PCRCS;
			}
			//_hoops_RPP (_hoops_CASRH(_hoops_CSPH))
			//	_hoops_HHIIA _hoops_SSIAA;
		}	_hoops_HHHI;

		case _hoops_HCSCC: {
			if (BIT (action_mask, _hoops_RSRI) &&
				BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_EDGES))
				node = _hoops_IPGCS (nr, node, _hoops_GSSCC, _hoops_IPRI);

			//_hoops_RPP (_hoops_GIIS != _hoops_IRAP && _hoops_GIIS->_hoops_IPCGP != _hoops_IRAP)
			//	_hoops_IHSA;
			//_hoops_SHS
				++stage;

			//_hoops_RPP (_hoops_CASRH(_hoops_CSPH))
			//	_hoops_HHIIA _hoops_SSIAA;
		}	_hoops_HHHI;

		case Polyhedron_Progress_Polyedges: {
			if (BIT (action_mask, _hoops_IGAI) ||
				BIT (nr->_hoops_RGP, T_INTERIOR_SILHOUETTE_EDGES))
				node = _hoops_CHGCS (nr, node, _hoops_GSSCC, _hoops_IPRI);

			//_hoops_RPP (_hoops_GIIS != _hoops_IRAP && _hoops_GIIS->_hoops_ACRI != _hoops_IRAP)
			//	_hoops_IHSA;
			//_hoops_SHS
				++stage;

			//_hoops_RPP (_hoops_CASRH(_hoops_CSPH))
			//	_hoops_HHIIA _hoops_SSIAA;
		}	_hoops_HHHI;

		case Polyhedron_Progress_Polymarkers: {
			if (BIT (action_mask, _hoops_RGPI))
				node = _hoops_IIGCS (nr, node, _hoops_GSSCC, _hoops_IPRI);

			//_hoops_RPP (_hoops_GIIS != _hoops_IRAP && _hoops_GIIS->_hoops_PAAI != _hoops_IRAP)
			//	_hoops_IHSA;
			//_hoops_SHS
				++stage;

		}	break;

		NODEFAULT;
	}


	if (stage == Polyhedron_Progress_Cleanup) {
		if (_hoops_ARRGH)
			_hoops_HGSGA (dc, "polyhedron transparency");

		if (dc->_hoops_CGHAR != null) {
			FREE_ARRAY_ALIGNED (dc->_hoops_CGHAR, dc->_hoops_ICACP, int, 16);
			dc->_hoops_CGHAR = null;
			dc->_hoops_ICACP = 0;
		}

		if (dc->_hoops_SSPGH != null) {
			FREE_ARRAY (dc->_hoops_SSPGH, dc->_hoops_GGHGH, RGB);
			dc->_hoops_SSPGH = null;
			dc->_hoops_GGHGH = 0;
		}
		if (dc->_hoops_RGHGH != null) {
			FREE_ARRAY (dc->_hoops_RGHGH, dc->_hoops_AGHGH, RGB);
			dc->_hoops_RGHGH = null;
			dc->_hoops_AGHGH = 0;
		}

		if (dc->_hoops_AHSI != null)
			dc->_hoops_AHSI->_hoops_AARGH = null;
		delete node;
		node = null;
	}
	else if (dc->_hoops_AHSI == null) {
		delete node;
		node = null;
	}

_hoops_PCRCS:
	if (node != null) {
		if (dc->_hoops_AHSI != null) {
			dc->_hoops_AHSI->_hoops_AARGH = node;
			node->_hoops_ARRGH = _hoops_ARRGH;
			node->_hoops_GSSCC = _hoops_GSSCC;
			node->stage = stage;
		}
		else
			// _hoops_RPP _hoops_GHHIP _hoops_HRGR _hoops_IRAP, _hoops_SCH _hoops_PAHH _hoops_AGSR _hoops_SGS _hoops_SR _hoops_CHR 
			// _hoops_PRCA _hoops_HHH _hoops_GHIS _hoops_IIGR _hoops_HHCI _hoops_IHCI
			delete node;
	}
}


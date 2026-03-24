/*
 * Copyright (c) 2001 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.212 2010-10-06 19:15:52 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "driver.h"
#include "phdraw.h"
#include "patterns.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hd_proto.h"
#include "hpserror.h"


#ifndef _hoops_PSPIR

#define _hoops_CACIR (1e-5f)

#ifndef _hoops_IAGHA
#  define _hoops_IAGHA 3.141592653589f
#endif


local Net_Rendition _hoops_HHPRC (
	Net_Rendition const & 		_hoops_SGIIH) {
	Net_Rendition				nr = _hoops_SGIIH;
	_hoops_CIGA alter &		_hoops_SIGA = nr.Modify()->_hoops_IHA.Modify();
	_hoops_HHA alter &	mat = _hoops_SIGA->_hoops_CHA.Modify();

	_hoops_SIGA->_hoops_GIA = mat;

	{
		_hoops_SIHHP alter *		up;
		unsigned short					value;
		unsigned short const *			_hoops_HAPAR;
		unsigned char alter *			_hoops_SCGCR;
		int								i;

		if ((up = (_hoops_SIHHP alter *)_hoops_SIGA->_hoops_PGPH) != null) {
			if (_hoops_ISAI (up) == 0) {
				if (up->pattern != null)
					FREE_ARRAY (up->pattern, up->width * up->height,
								unsigned char);

				FREE (up, _hoops_SIHHP);
			}
		}

		ALLOC (up, _hoops_SIHHP);
		_hoops_ICAI (up);
		up->_hoops_CPA = nr->_hoops_SRA->_hoops_GCHHP();
		up->width = up->height = 8;
		up->_hoops_RCHHP = true;
		up->_hoops_ACHHP = UPAT_NO_CONTRAST;
		ALLOC_ARRAY (_hoops_SCGCR, 64, unsigned char);
		up->pattern = _hoops_SCGCR;

		value = (unsigned short)(mat->_hoops_IRIR * 0x0000FFFF);
		_hoops_HAPAR = &HOOPS_READ_ONLY._hoops_CHGCR[0][0];
		for (i=0; i<64; i++) {
			*_hoops_SCGCR++ = (value < *_hoops_HAPAR++) ? 1 : 0;	/* 1 _hoops_HRGR _hoops_ASPA _hoops_IS _hoops_HSGR */
		}
		up->stipple = 64 - (int)(mat->_hoops_IRIR * 64);

		_hoops_SIGA->_hoops_PGPH = up;
		_hoops_SIGA->pattern = FP_USER_DEFINED;

		mat->_hoops_IRIR = 1.0f;
		mat->color[_hoops_PCA].red =
		 mat->color[_hoops_PCA].green =
		  mat->color[_hoops_PCA].blue = 0.0f;

		if (nr->_hoops_SRA->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR) {
			_hoops_SIGA->color._hoops_HRIR.a = _hoops_GPGCR;
			_hoops_SIGA->_hoops_RGIR._hoops_HRIR.a = _hoops_GPGCR;
		}
		else {
			/* _hoops_PA _hoops_SR *_hoops_PAH* _hoops_AA? */
		}
	}

	return nr;
}


local void _hoops_SGAIS (
	PolyCylinder const *		polycylinder, 
	float alter *				_hoops_GRAIS) {
	Vector						_hoops_ARGCR;
	int							i;

	for (i = 0; i < polycylinder->point_count-1; i++) {
		_hoops_ARGCR.x = polycylinder->points[i].x - polycylinder->points[i+1].x;
		_hoops_ARGCR.y = polycylinder->points[i].y - polycylinder->points[i+1].y;
		_hoops_ARGCR.z = polycylinder->points[i].z - polycylinder->points[i+1].z;
		_hoops_GRAIS[i] = HI_Sqrt (_hoops_ARGCR.x*_hoops_ARGCR.x + _hoops_ARGCR.y*_hoops_ARGCR.y + _hoops_ARGCR.z*_hoops_ARGCR.z);
	}
	_hoops_GRAIS[i] = 0;
}


/* _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_CPIC _hoops_IS _hoops_AIRI _hoops_HHH _hoops_GHIS _hoops_IIGR _hoops_SPPR _hoops_PGAP _hoops_ARAS _hoops_IGIAR _hoops_RH
 * _hoops_SPCC _hoops_APIC, _hoops_PGSA _hoops_SPR _hoops_GRGA _hoops_PGAP _hoops_SPASR _hoops_RH _hoops_HSP _hoops_APIR _hoops_PPR
 * _hoops_RCA _hoops_IGIAR _hoops_RH _hoops_SPCC _hoops_HIS _hoops_SGS _hoops_SR _hoops_HS _hoops_CPHP _hoops_GHCSA _hoops_SIGC
 * _hoops_GGR _hoops_AGIR _hoops_RH _hoops_HPHR _hoops_RIRPA _hoops_HRGR _hoops_SHRII _hoops_GGIC
 */
local void _hoops_RRAIS (
	Net_Rendition const &		nr,
	PolyCylinder const *		polycylinder,
	int							_hoops_HGII,
	Tristrip const *			tristrip) {
	int							*vi, *ei;
	int							_hoops_HCRGR, _hoops_PGRPS;
	int							_hoops_ICRHH;
	Net_Rendition				_hoops_RHICP = nr;
	Polyedge alter *			polyedge;

	ZALLOC (polyedge, Polyedge);
	_hoops_ICAI(polyedge);

	polyedge->lengths_allocated = 1;
	polyedge->_hoops_IPII = polycylinder->point_count;
	polyedge->_hoops_CPII = polycylinder->point_count;
	ALLOC_ARRAY (polyedge->lengths, polyedge->lengths_allocated, int);
	ALLOC_ARRAY (polyedge->_hoops_AIHA, polyedge->_hoops_IPII, int);
	ALLOC_ARRAY (polyedge->_hoops_SPII, polyedge->_hoops_CPII, int);
	polyedge->_hoops_RAHH |= _hoops_AAHH;
	
	vi = polyedge->_hoops_AIHA;
	ei = polyedge->_hoops_SPII;

	_hoops_HCRGR = polycylinder->point_count * _hoops_HGII;
	_hoops_PGRPS = _hoops_HCRGR - _hoops_HGII;	/* _hoops_RHAP _hoops_HAR _hoops_GCIS _hoops_RIRR */

	polyedge->point_count = _hoops_HCRGR;
	polyedge->points = tristrip->points;
	polyedge->_hoops_SPHA = polycylinder->point_count - 1;
	polyedge->_hoops_ICHA = tristrip->_hoops_ICHA;
	polyedge->_hoops_PCHA = tristrip->_hoops_PCHA;
	polyedge->_hoops_HCHA = tristrip->_hoops_HCHA;
	polyedge->total = polycylinder->point_count;
	polyedge->_hoops_PHHA = 1;
	polyedge->lengths[0] = polycylinder->point_count;
	polyedge->bounding = polycylinder->bounding;

	for (_hoops_ICRHH=0; _hoops_ICRHH<polycylinder->point_count; _hoops_ICRHH++) {
		*vi++ = _hoops_ICRHH*_hoops_HGII;
		*ei++ = _hoops_ICRHH*_hoops_HGII + _hoops_HCRGR;
	}
	polyedge->_hoops_SRHA |= _hoops_GAHH | DL_TEMPORARY_DATA | _hoops_SRHH;

	Line_Rendition alter &		_hoops_ARAIS = _hoops_RHICP.Modify()->_hoops_RHP.Modify();

	_hoops_ARAIS->color = nr->_hoops_IHA->color;

	HD_Replace_Line_Style(_hoops_ARAIS, nr->_hoops_GCSHP->_hoops_IHRIP);

	_hoops_ARAIS->weight = 1;

	_hoops_ARAIS->_hoops_CHA = nr->_hoops_IHA->_hoops_CHA;

	if ((_hoops_ARAIS->_hoops_AGP = nr->_hoops_IHA->_hoops_AGP) != null)
		if (!BIT (_hoops_RHICP->_hoops_RGP, T_LIGHTS_FOR_EDGES))
			_hoops_RHICP->_hoops_RGP |= T_LIGHTS_FOR_EDGES;

	if (ALLBITS (nr->_hoops_IRR->_hoops_CSA,
				 _hoops_HIRC & ~_hoops_AHGI))
		polyedge->_hoops_RPRCP = true;

	if (polyedge->_hoops_HCHA != null)
		HD_Draw_Indexicated_3D_Polyedge (nr, polyedge);
	else
		_hoops_RAIGH (_hoops_RHICP, polyedge);

	if (_hoops_ISAI (polyedge) == 0)
		HI_Free_Polyedge (polyedge);
}

local int _hoops_PRAIS (int _hoops_PSR) 
{
	switch (_hoops_PSR) {
		case HK_PS_WORLD:
			return (_hoops_ASRSP | _hoops_SSRSP | _hoops_PSRSP | _hoops_ISRSP);
						
		case HK_PS_OBJECT:
			return (_hoops_ASRSP | _hoops_PGASP | _hoops_ISRSP); 

		case HK_PS_SURFACE_NORMAL:
			return (_hoops_ASRSP | _hoops_GGASP | _hoops_ISRSP);

		case HK_PS_U:
		case HK_PS_UV: 
		case HK_PS_UVW:
		case HK_PS_NATURAL_UV:
		case HK_PS_CYLINDER:
			return (_hoops_ASRSP | _hoops_AGASP);
	}
	return 0;
}

 
local void _hoops_HRAIS (		
	Net_Rendition const &		nr,
	PolyCylinder const *		polycylinder,
	int							_hoops_HGII,
	Tristrip alter *			tristrip,
	bool						_hoops_IRAIS) {
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	_hoops_RCR const *				texture = null;
	_hoops_RSSH *					_hoops_CRAIS = null;
	_hoops_RRCC *		_hoops_HAPAR, *_hoops_SRAIS;
	_hoops_HIR *		current = null;
	int 						_hoops_GAAIS = 0;
	int 						_hoops_HHCAP = 0;
	int 						_hoops_IHRSR = nr->_hoops_RGP & T_ANY_SHELL_EDGE;
	bool						_hoops_HHAHR;
	int							_hoops_RAAIS;
	int							_hoops_AAAIS;

	ZALLOC (_hoops_HAPAR, _hoops_RRCC);
	_hoops_ICAI(_hoops_HAPAR);

	_hoops_SRAIS = _hoops_HAPAR;

	_hoops_HAPAR->_hoops_SASCC = true;
	if ((current = _hoops_SIGA->_hoops_CHA->_hoops_SCA) != null)
		texture = current->texture;

	if (!texture)
		texture = _hoops_SIGA->_hoops_CHA->texture[_hoops_HIA];
	if (!texture)
		texture = _hoops_SIGA->_hoops_CHA->texture[_hoops_IIA];

	if (!current)
		current = _hoops_SIGA->_hoops_GIA->_hoops_SCA;

	_hoops_HHAHR = BIT (nr->_hoops_ARA->geometry_options, _hoops_RHGAP);
	if (!_hoops_HHAHR) {
		_hoops_RAAIS = _hoops_IHHIA;
		_hoops_AAAIS = _hoops_SHHIA;
	}
	else {
		_hoops_RAAIS = _hoops_SHHIA;
		_hoops_AAAIS = _hoops_IHHIA;
	}
	
	while (current || texture) {
		if (current) {
			texture = current->texture;
		}
		else {
			/* _hoops_AGIR _hoops_IH _hoops_CGPR _hoops_SR _hoops_SRPS _hoops_SPR _hoops_IIGR _hoops_RH _hoops_RSHAR->_hoops_PAAIS->_hoops_HH[_hoops_ASIGA] _hoops_GH _hoops_ARRS */
		}

		_hoops_HAPAR->_hoops_SASCC = true;
	
#ifndef DISABLE_EXTENDED_TEXTURE
		switch (texture->_hoops_PSR) {
			case HK_PS_OBJECT: {
				_hoops_HAPAR->_hoops_CCHA = (_hoops_RSSH*) tristrip->points;
				_hoops_HAPAR->_hoops_GSHA = 3;
				_hoops_HAPAR->_hoops_SCAI = _hoops_PRAIS (texture->_hoops_PSR);
			}	break;
			case HK_PS_SURFACE_NORMAL: {
				if (tristrip->_hoops_ICHA) {
					_hoops_HAPAR->_hoops_CCHA = (_hoops_RSSH*) tristrip->_hoops_ICHA;
					_hoops_HAPAR->_hoops_GSHA = 3;
					_hoops_HAPAR->_hoops_SCAI = _hoops_PRAIS (texture->_hoops_PSR);
				}
				else {
					_hoops_HAPAR->_hoops_SCAI = _hoops_GSRSP;
					_hoops_HAPAR->_hoops_CCHA = null;
				}
			}	break;
			case HK_PS_WORLD: {
				_hoops_HAPAR->_hoops_GSHA = 3;
				_hoops_HAPAR->_hoops_SCAI = _hoops_PRAIS (texture->_hoops_PSR);
			}	break;

			case HK_PS_U: /* _hoops_HAR _hoops_SSRR, _hoops_HIS _hoops_ARCR _hoops_IS _hoops_RGSSA */
			case HK_PS_UV: /* _hoops_HAR _hoops_SSRR, _hoops_HIS _hoops_ARCR _hoops_IS _hoops_RGSSA */
			case HK_PS_UVW: /* _hoops_HAR _hoops_SSRR, _hoops_HIS _hoops_ARCR _hoops_IS _hoops_RGSSA */
			case HK_PS_NATURAL_UV:
			case HK_PS_CYLINDER: {
				_hoops_RSSH *ptr, *next;
				_hoops_RSSH u, v, _hoops_IRIAR, _hoops_HAAIS, _hoops_CPHA;
				float _hoops_IAAIS[128];
				float *_hoops_GRAIS = _hoops_IAAIS;

				_hoops_HAPAR->_hoops_GSHA = 2;
				_hoops_HAPAR->_hoops_SCAI = _hoops_PRAIS (texture->_hoops_PSR);
				_hoops_HHCAP = polycylinder->point_count; /* _hoops_ASSS _hoops_RSIAR _hoops_IS _hoops_HHGP _hoops_IRS _hoops_CAAIS */
				_hoops_GAAIS = (tristrip->point_count + _hoops_HHCAP)*2;
				ALLOC_ARRAY (_hoops_CRAIS, _hoops_GAAIS, _hoops_RSSH);
				_hoops_HAPAR->_hoops_CCHA = _hoops_CRAIS;
				_hoops_IRIAR = 1.0f / (_hoops_HGII);
				v = 0;
				if (polycylinder->point_count > 128)
					ALLOC_ARRAY (_hoops_GRAIS, polycylinder->point_count, float);
				_hoops_SGAIS (polycylinder, _hoops_GRAIS);
				if (texture->_hoops_PSR == HK_PS_CYLINDER || 
					polycylinder->_hoops_PCCSA == 0) {
					_hoops_CPHA = 0;
					for (int i = 0 ; i < polycylinder->point_count ; i++)
						_hoops_CPHA += _hoops_GRAIS[i];
					_hoops_HAAIS = _hoops_CPHA;
				}
				else {
					_hoops_HAAIS = 2*_hoops_IAGHA*polycylinder->_hoops_PCCSA;
				}
				ptr = _hoops_HAPAR->_hoops_CCHA;
				for (int i = 0 ; i < polycylinder->point_count ; i++) {
					next = ptr + 2*_hoops_HGII;
					u = _hoops_IRIAR;
					while (ptr < next-2) {
						*ptr++ = u;
						u += _hoops_IRIAR;
						*ptr++ = v;
					}
					*ptr++ = 0.99999f;
					*ptr++ = v;
					v += _hoops_GRAIS[i]/_hoops_HAAIS;
				}
				if (ANYBIT (polycylinder->flags, _hoops_PPSSA) &&
					!BIT (polycylinder->flags, _hoops_GASSA)) {
					float const *_hoops_GAIAA = HI_Get_Sin72_Lookup();
					float const *_hoops_SAAIS, *_hoops_GPAIS;
					int _hoops_HGCGP = 72/_hoops_HGII;

					if (polycylinder->flags & _hoops_RAAIS) {
						_hoops_SAAIS = _hoops_GAIAA;
						_hoops_GPAIS = _hoops_SAAIS + 18;	/* _hoops_HHSPA(_hoops_SISR) = _hoops_IHSPA(_hoops_SISR-90) */
						next = ptr + 2*_hoops_HGII;
						while (ptr < next) {
							*ptr++ = (*_hoops_SAAIS + 1)/(2*_hoops_IAGHA);
							*ptr++ = (*_hoops_GPAIS + 1)/(2*_hoops_IAGHA);
							_hoops_SAAIS += _hoops_HGCGP;
							_hoops_GPAIS += _hoops_HGCGP;
						}
					}
					if (polycylinder->flags & _hoops_AAAIS) {
						_hoops_SAAIS = _hoops_GAIAA;
						_hoops_GPAIS = _hoops_SAAIS + 18;	/* _hoops_HHSPA(_hoops_SISR) = _hoops_IHSPA(_hoops_SISR-90) */
						next = ptr + 2*_hoops_HGII;
						while (ptr < next) {
							*ptr++ = (*_hoops_SAAIS + 1)/(2*_hoops_IAGHA);
							*ptr++ = (*_hoops_GPAIS + 1)/(2*_hoops_IAGHA);
							_hoops_SAAIS += _hoops_HGCGP;
							_hoops_GPAIS += _hoops_HGCGP;
						}
					}
				}
				if (_hoops_GRAIS != _hoops_IAAIS)
					FREE_ARRAY (_hoops_GRAIS, polycylinder->point_count, float);

				//_hoops_RPP (1) {
					/* _hoops_RPAIS _hoops_IRS _hoops_CAAIS _hoops_IGIAR _hoops_SPR _hoops_ISHA _hoops_IIGR _hoops_RH _hoops_RSRRA _hoops_IS _hoops_CCIH _hoops_GH _hoops_RH _hoops_HH
					 * _hoops_PCRR.  _hoops_PS _hoops_CHH _hoops_IAII _hoops_ARGAR _hoops_RH _hoops_RHPH _hoops_HAGA _hoops_ARHI _hoops_RH _hoops_HH
					 * _hoops_IH _hoops_HHH _hoops_HIPH. */
					int j, _hoops_APAIS, vi, _hoops_PPAIS;
					bool _hoops_HPAIS = !BIT (nr->transform_rendition->heuristics,
											_hoops_GPSA);

					_hoops_PPAIS = tristrip->point_count;
					j = _hoops_APAIS = 0;
					vi = _hoops_HGII-1;
					for (int i = 0; i < polycylinder->point_count-1; i++) {
						_hoops_APAIS = j+tristrip->lengths[i];
						_hoops_RSAI (&tristrip->points[vi], Point, &tristrip->points[_hoops_PPAIS]);
						if (tristrip->_hoops_ICHA)
							_hoops_RSAI (&tristrip->_hoops_ICHA[vi], Point, &tristrip->_hoops_ICHA[_hoops_PPAIS]);
						_hoops_HAPAR->_hoops_CCHA[ 2*_hoops_PPAIS] = 0;
						_hoops_HAPAR->_hoops_CCHA[1+2*_hoops_PPAIS] = _hoops_HAPAR->_hoops_CCHA[1+2*vi];
						if (_hoops_HPAIS) {
							tristrip->_hoops_AIHA[j] = _hoops_PPAIS;
							tristrip->_hoops_AIHA[j+1] = _hoops_PPAIS+1;
						}
						else {
							tristrip->_hoops_AIHA[j] = _hoops_PPAIS+1;
							tristrip->_hoops_AIHA[j+1] = _hoops_PPAIS;
						}
						_hoops_PPAIS++;
						vi += _hoops_HGII;
						j = _hoops_APAIS;
					}
					_hoops_RSAI (&tristrip->points[vi], Point, &tristrip->points[_hoops_PPAIS]);
					if (tristrip->_hoops_ICHA)
						_hoops_RSAI (&tristrip->_hoops_ICHA[vi], Point, &tristrip->_hoops_ICHA[_hoops_PPAIS]);
					_hoops_HAPAR->_hoops_CCHA[ 2*_hoops_PPAIS] = 0;
					_hoops_HAPAR->_hoops_CCHA[1+2*_hoops_PPAIS] = _hoops_HAPAR->_hoops_CCHA[1+2*vi];
					tristrip->point_count += _hoops_HHCAP;
				//}
				//_hoops_SHS
				//	_hoops_CRHH->_hoops_HGCI |= _hoops_IPAIS;
			} break;

			case HK_PS_REFLECTION_VECTOR: /* _hoops_GIR _hoops_HPP _hoops_GSSC _hoops_PAPA */
			case _hoops_HSR: /* _hoops_GIR _hoops_HPP _hoops_GSSC _hoops_PAPA */
			case HK_PS_LOCAL_PIXELS: /* _hoops_HAR _hoops_GAPR _hoops_HGPS */
			case HK_PS_OUTER_PIXELS: /* _hoops_HAR _hoops_GAPR _hoops_HGPS */
			case HK_PS_LOCAL_WINDOW: /* _hoops_HAR _hoops_GAPR _hoops_HGPS */
			case HK_PS_OUTER_WINDOW: /* _hoops_HAR _hoops_GAPR _hoops_HGPS */
			case HK_PS_SPHERE: /* _hoops_HAR _hoops_GAPR _hoops_HGPS */
			case HK_PS_UNSPECIFIED: 
			default: 
				_hoops_HAPAR->_hoops_SCAI = _hoops_GSRSP;
				_hoops_HAPAR->_hoops_CCHA = null;
				break;
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

#endif
	}

	if (tristrip->_hoops_GSSH != null && _hoops_ISAI (tristrip->_hoops_GSSH) == 0)
		HI_Free_Texture_Parameters (tristrip->_hoops_GSSH);

	tristrip->_hoops_GSSH = _hoops_SRAIS;
		
	_hoops_HPHCP (nr, tristrip);
	if (!_hoops_IRAIS &&
		!ANYBIT (_hoops_IHRSR, T_GENERIC_EDGES|T_INTERIOR_SILHOUETTE_EDGES) &&
		nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR == 1.0f && 
		nr->_hoops_IRR->_hoops_GAHA != Display_List_SEGMENT) {
		Net_Rendition		_hoops_CRAI = nr;

		_hoops_CRAI.Modify()->transform_rendition.Modify()->_hoops_GSCH[0] += 0.001f;

		_hoops_RRAIS (_hoops_CRAI, polycylinder, _hoops_HGII, tristrip);
	}

	if (_hoops_CRAIS)
		FREE_ARRAY (_hoops_CRAIS, _hoops_GAAIS, _hoops_RSSH);
}


local void _hoops_CPAIS (
	Net_Rendition const &		inr,
	PolyCylinder const	*		polycylinder,
	bool						_hoops_IHRSR,
	bool						_hoops_SPAIS,
	bool						_hoops_GHAIS) {
	Net_Rendition				nr = inr;
	Display_Context alter *		dc = (Display_Context alter *) nr->_hoops_SRA;
	Polyedge *					polyedge;
	RGB							_hoops_RHAIS[512];
	float						_hoops_AGRPS[512];
	RGB *						_hoops_PCHA = _hoops_RHAIS;
	float *						_hoops_HCHA = _hoops_AGRPS;
	int *						_hoops_AIHA;
	int *						_hoops_SPII;
	int							ii, _hoops_ICRHH;
	_hoops_AGHIR const *_hoops_PGHIR = polycylinder->_hoops_RGHIR;
	_hoops_GRGH const		&_hoops_RRGH = nr->_hoops_IRR;

	ZALLOC(polyedge, Polyedge); 
	_hoops_ICAI(polyedge);
	polyedge->points = polycylinder->points;
	polyedge->point_count = polycylinder->point_count;
	polyedge->_hoops_SPHA = polycylinder->point_count - 1;
	polyedge->_hoops_PHHA = 1;

	polyedge->lengths_allocated = 1;
	polyedge->_hoops_IPII = polycylinder->point_count;
	polyedge->_hoops_CPII = polycylinder->point_count;
	ALLOC_ARRAY(polyedge->lengths, polyedge->lengths_allocated, int);
	ALLOC_ARRAY(polyedge->_hoops_AIHA, polyedge->_hoops_IPII, int);
	ALLOC_ARRAY(polyedge->_hoops_SPII, polyedge->_hoops_CPII, int);
	polyedge->_hoops_RAHH |= _hoops_AAHH;

	_hoops_AIHA = polyedge->_hoops_AIHA;
	_hoops_SPII = polyedge->_hoops_SPII;

	if (polycylinder->point_count > _hoops_GGAPR(_hoops_RHAIS)) {
		ALLOC_ARRAY (_hoops_PCHA, polycylinder->point_count, RGB);
		ALLOC_ARRAY (_hoops_HCHA, polycylinder->point_count, float);
	}

	polyedge->total = polyedge->lengths[0] = polycylinder->point_count;
	for (ii=0; ii<polycylinder->point_count; ii++) {
		_hoops_AIHA[ii] = ii;
		_hoops_SPII[ii] = ii-1;
	}
	_hoops_SPII[0] = 0;		/* _hoops_PAHA'_hoops_RA _hoops_RPSHR */

	if (_hoops_PGHIR != null) {
		if (_hoops_PGHIR->_hoops_SCHPR == 0 &&
			_hoops_PGHIR->_hoops_CCHPR == 0)
			_hoops_GHAIS = false;
		if (_hoops_PGHIR->_hoops_RCRHR == 0 &&
			_hoops_PGHIR->_hoops_SIRHR == 0)
			_hoops_SPAIS = false;

		if ((_hoops_IHRSR && _hoops_GHAIS) ||
			(!_hoops_IHRSR && _hoops_SPAIS)) {
			_hoops_RHAH const *		_hoops_CSIR;
			RGB						_hoops_AHAIS;
			bool					_hoops_PHAIS;
			bool					_hoops_HHAIS;
			bool					_hoops_IHAIS;
			bool					_hoops_CHAIS;
			bool					_hoops_HHAHR;
			int						_hoops_IGRPS = 0, _hoops_CGRPS = 1;

			_hoops_PHAIS = ALLBITS (_hoops_RRGH->_hoops_CSA,
										  _hoops_SSRC & ~_hoops_AHGI);
			_hoops_HHAIS = ALLBITS (_hoops_RRGH->_hoops_CSA,
										  _hoops_HIRC & ~_hoops_AHGI);
			_hoops_IHAIS = ALLBITS (_hoops_RRGH->_hoops_CSA,
												_hoops_CSRC & ~_hoops_AHGI) &&
										 _hoops_PGHIR->_hoops_CCHPR == polycylinder->point_count;
			_hoops_CHAIS = ALLBITS (_hoops_RRGH->_hoops_CSA,
												_hoops_PHGI & ~_hoops_AHGI) &&
										 _hoops_PGHIR->_hoops_SIRHR == polycylinder->point_count;

			_hoops_CSIR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR;

			if (_hoops_IHRSR)
				_hoops_AHAIS = nr->_hoops_RHP->_hoops_CHA->_hoops_CSHR;
			else
				_hoops_AHAIS = nr->_hoops_IHA->_hoops_CHA->_hoops_CSHR;

			_hoops_HHAHR = BIT (nr->_hoops_ARA->geometry_options, _hoops_RHGAP);
			if (BIT (nr->_hoops_ARA->geometry_options, _hoops_AHGAP)) {
				_hoops_IGRPS = polycylinder->point_count - 1;
				_hoops_CGRPS = -1;
			}

			_hoops_AHAH			_hoops_PHAH = nr->_hoops_ARA->_hoops_IHRH;
			_hoops_AHAH 		_hoops_SHAIS;

			for (_hoops_ICRHH=0; _hoops_ICRHH<polycylinder->point_count; _hoops_ICRHH++) {
				RGB						color;
				_hoops_CGHIR		flags;

				flags = _hoops_PGHIR->flags[_hoops_IGRPS];

				if (_hoops_IHRSR) {
					if (BIT (flags, _hoops_SHRRA))
						color = _hoops_PGHIR->ecolors[_hoops_IGRPS];
#ifndef DISABLE_COLOR_MAPS
					else if (BIT (flags, _hoops_IHRRA)) {
						if (_hoops_CSIR->length == 0) {
#if 0
							HD_Report_Null_Color_Map ("polycylinder", _hoops_CSIR);
#endif
							color = _hoops_GPSR::_hoops_RPSR;
						}
						else
							_hoops_ICRCP (_hoops_CSIR, _hoops_PGHIR->_hoops_HGHIR[_hoops_IGRPS],
										   color, _hoops_PHAIS, _hoops_SHAIS);

						_hoops_HCHA[_hoops_ICRHH] = _hoops_PGHIR->_hoops_HGHIR[_hoops_IGRPS];
					}
#endif
					else
						color = _hoops_AHAIS;
				}
				else {
					if (BIT (flags, _hoops_GIRRA))
						color = _hoops_PGHIR->fcolors[_hoops_IGRPS];
#ifndef DISABLE_COLOR_MAPS
					else if (BIT (flags, _hoops_CHRRA)) {
						if (_hoops_CSIR->length == 0) {
#if 0
							HD_Report_Null_Color_Map ("polycylinder", _hoops_CSIR);
#endif
							color = _hoops_GPSR::_hoops_RPSR;
						}
						else
							_hoops_ICRCP (_hoops_CSIR, _hoops_PGHIR->_hoops_IGHIR[_hoops_IGRPS],
										   color, _hoops_HHAIS, _hoops_SHAIS);

						_hoops_HCHA[_hoops_ICRHH] = _hoops_PGHIR->_hoops_IGHIR[_hoops_IGRPS];
					}
#endif
					else
						color = _hoops_AHAIS;
				}

				if (BIT (_hoops_PHAH.options, _hoops_CHRH))
					color = HD_Apply_Color_Effects (color, _hoops_PHAH);

				_hoops_PCHA[_hoops_ICRHH] = color;

				_hoops_IGRPS += _hoops_CGRPS;
			}

			if (_hoops_IHRSR && _hoops_IHAIS) {
				polyedge->_hoops_HCHA = _hoops_HCHA;

				if (_hoops_PHAIS)
					polyedge->_hoops_RPRCP = true;
			}
			else if (_hoops_CHAIS) {
				polyedge->_hoops_HCHA = _hoops_HCHA;

				if (_hoops_HHAIS)
					polyedge->_hoops_RPRCP = true;

				if (_hoops_HHAIS &&
					!BIT (_hoops_RRGH->_hoops_CSA, _hoops_SSRC & ~_hoops_AHGI) ||
					_hoops_CHAIS &&
					!BIT (_hoops_RRGH->_hoops_CSA, _hoops_CSRC & ~_hoops_AHGI)) {

					if (_hoops_HHAIS)
						nr.Modify()->_hoops_IRR.Modify()->_hoops_CSA |=
											 _hoops_SSRC & ~_hoops_AHGI;
					if (_hoops_CHAIS)
						nr.Modify()->_hoops_IRR.Modify()->_hoops_CSA |=
											 _hoops_CSRC & ~_hoops_AHGI;
				}
			}
			else if (_hoops_PHAIS)
				polyedge->_hoops_PCHA = _hoops_PCHA;
			else
				polyedge->_hoops_ASHA = _hoops_PCHA;
		}
	}

	polyedge->_hoops_SRHA |= DL_TEMPORARY_DATA | DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS;
	polyedge->_hoops_CARI |= _hoops_GCRI;
	if (_hoops_PGHIR) {
		//_hoops_PRIA _hoops_IGH _hoops_IIH _hoops_AAPR _hoops_PSHA _hoops_SGS _hoops_GGHP _hoops_AGSI _hoops_PGGA _hoops_IIGR _hoops_HAIR _hoops_SGHS
		if (_hoops_IHRSR) {
			if (BIT (_hoops_RRGH->locks.color, Color_EDGE))
				polyedge->_hoops_SRHA |= _hoops_IIRC;
		}
		else if (BIT (_hoops_RRGH->locks.color, Color_FRONT))
			polyedge->_hoops_SRHA |= _hoops_IIRC;
	}
	Action_Mask _hoops_HPCI = nr->_hoops_SRA->_hoops_IPCI->mask;
	if (_hoops_ICCSP (nr, _hoops_PGRI))
		dc->_hoops_IPCI->mask |= (_hoops_ASRI|_hoops_GHCI);

	if (polyedge->_hoops_HCHA != null)
		HD_Draw_Indexicated_3D_Polyedge (nr, polyedge);
	else
		_hoops_RAIGH (nr, polyedge);

	dc->_hoops_IPCI->mask = _hoops_HPCI;

	if (polycylinder->point_count > _hoops_GGAPR(_hoops_RHAIS)) {
		FREE_ARRAY (_hoops_PCHA, polycylinder->point_count, RGB);
		FREE_ARRAY (_hoops_HCHA, polycylinder->point_count, float);
	}

	if (_hoops_ISAI(polyedge) == 0)
		HI_Free_Polyedge(polyedge);
} /* _hoops_RSGR _hoops_API _hoops_PGSA _hoops_RSRRA _hoops_IRSS _hoops_RGAR */


/* _hoops_GIAIS _hoops_AAPC _hoops_IS _hoops_RH _hoops_HISGR _hoops_PRGI _hoops_RIAIS _hoops_IIGR 72 */
local int _hoops_AIAIS (int _hoops_HGII)
{
	if (_hoops_HGII <= 3) 
		return 3;
	else if (_hoops_HGII <= 4) 
		return 4;
	else if (_hoops_HGII <= 6) 
		return 6;
	else if (_hoops_HGII <= 8) 
		return 8;
	else if (_hoops_HGII <= 9) 
		return 9;
	else if (_hoops_HGII <= 12) 
		return 12;
	else if (_hoops_HGII <= 18) 
		return 18;
	else if (_hoops_HGII <= 24) 
		return 24;
	else if (_hoops_HGII <= 36) 
		return 36;
	else 
		return 72;
}


/* _hoops_IHGP _hoops_PSCHR _hoops_HPAHR _hoops_IIGR _hoops_AAGA _hoops_ISPAA _hoops_IIGR _hoops_HSP _hoops_GHC */
#define _hoops_PIAIS(_hoops_ICIPR,_hoops_CCIPR) (_hoops_ICIPR.a*_hoops_CCIPR.a + _hoops_ICIPR.b*_hoops_CCIPR.b + _hoops_ICIPR.c*_hoops_CCIPR.c)

local void _hoops_HIAIS (
		Net_Rendition const &		nr,
		PolyCylinder const *		polycylinder,
		_hoops_ACHR					_hoops_IHRSR,
		bool 						_hoops_IIAIS,
		bool 						_hoops_CIAIS,
		bool 						_hoops_GHAIS,
		int  						_hoops_HGII,
		Point *						points,
		RGB *						_hoops_PCHA,
		float *						_hoops_HCHA,
		_hoops_ARPA *						_hoops_PRHH,
		int *						_hoops_AGHAR,
		Polyedge alter *			polyedge) 
{
	int 						*vi, *ei;
	int 						_hoops_HCRGR, _hoops_PGRPS;
	int 						ii, _hoops_ICRHH, index;
	_hoops_AGHIR const *_hoops_PGHIR = polycylinder->_hoops_RGHIR;
	bool						_hoops_HHAHR;
	int							_hoops_RAAIS = _hoops_IHHIA;
	int							_hoops_AAAIS = _hoops_SHHIA;
	bool						_hoops_PHAIS = false;
	bool						_hoops_IHAIS = false;
	RGB							*_hoops_ASHA = null;

	_hoops_HHAHR = BIT (nr->_hoops_ARA->geometry_options, _hoops_RHGAP);

	_hoops_HCRGR = polycylinder->point_count * _hoops_HGII;
	_hoops_PGRPS = _hoops_HCRGR - _hoops_HGII;	/* _hoops_RHAP _hoops_HAR _hoops_GCIS _hoops_RIRR */

	polyedge->points = points;
	polyedge->point_count = _hoops_HCRGR;
	polyedge->_hoops_SPHA = 2 * _hoops_PGRPS + _hoops_HGII;
	polyedge->_hoops_PCHA = null;
	polyedge->_hoops_HCHA = null;
	polyedge->_hoops_ASHA = null;
	polyedge->_hoops_CCHA = null;
	polyedge->_hoops_GSHA = 0;

	polyedge->_hoops_RPRCP = false;
	polyedge->_hoops_GPPPI = false;

	polyedge->_hoops_PHHA = 0;
	polyedge->total = 0;

	polyedge->bounding = polycylinder->bounding;
	
	polyedge->lengths_allocated=3*_hoops_HCRGR/2;
	polyedge->_hoops_IPII = 3*_hoops_HCRGR;
	polyedge->_hoops_CPII = 3*_hoops_HCRGR;
	ALLOC_ARRAY_CACHED (polyedge->lengths, polyedge->lengths_allocated, int);
	ALLOC_ARRAY_CACHED (polyedge->_hoops_AIHA, polyedge->_hoops_IPII, int);
	ALLOC_ARRAY_CACHED (polyedge->_hoops_SPII, polyedge->_hoops_CPII, int);
	polyedge->_hoops_RAHH |= _hoops_AAHH;

	vi = polyedge->_hoops_AIHA;
	ei = polyedge->_hoops_SPII;

	if (_hoops_GHAIS && _hoops_PGHIR != null &&
		(_hoops_PGHIR->_hoops_SCHPR > 0 ||
		 _hoops_PGHIR->_hoops_CCHPR > 0)) {
		_hoops_RHAH const *		_hoops_CSIR;
		RGB						_hoops_AHAIS;
		_hoops_GRGH const &	_hoops_RRGH = nr->_hoops_IRR;
		bool					_hoops_SIAIS;
		int						_hoops_IGRPS = 0, _hoops_CGRPS = 1;

		_hoops_PHAIS = ALLBITS (nr->_hoops_IRR->_hoops_CSA,
									  _hoops_SSRC & ~_hoops_AHGI);
		_hoops_IHAIS = BIT (nr->_hoops_IRR->_hoops_CSA,
										_hoops_CSRC & ~_hoops_AHGI) &&
								   _hoops_PGHIR->_hoops_CCHPR == polycylinder->point_count;
		_hoops_SIAIS = ALLBITS (_hoops_RRGH->_hoops_CSA,
									 (_hoops_SSRC |
									  _hoops_CSRC) & ~_hoops_AHGI);
		if (!_hoops_PHAIS && !_hoops_IHAIS) {
			ALLOC_ARRAY (_hoops_ASHA, polyedge->_hoops_SPHA, RGB);
			polyedge->_hoops_ASHA = _hoops_ASHA;
		}

		_hoops_CSIR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR;


		_hoops_AHAIS = nr->_hoops_RHP->_hoops_CHA->_hoops_CSHR;

		if (BIT (nr->_hoops_ARA->geometry_options, _hoops_AHGAP)) {
			_hoops_IGRPS = polycylinder->point_count - 1;
			_hoops_CGRPS = -1;
		}

		_hoops_AHAH const &			_hoops_PHAH = nr->_hoops_ARA->_hoops_IHRH;
		_hoops_AHAH 				_hoops_SHAIS;

		index = 0;
		for (_hoops_ICRHH=0; _hoops_ICRHH<polycylinder->point_count; _hoops_ICRHH++) {
			RGB						color;
			_hoops_CGHIR		flags;

			flags = _hoops_PGHIR->flags[_hoops_IGRPS];

			if (BIT (flags, _hoops_SHRRA))
				color = _hoops_PGHIR->ecolors[_hoops_IGRPS];
#ifndef DISABLE_COLOR_MAPS
			else if (BIT (flags, _hoops_IHRRA)) {
				if (_hoops_CSIR->length == 0) {
#if 0
					HD_Report_Null_Color_Map ("polycylinder", _hoops_CSIR);
#endif
					color = _hoops_GPSR::_hoops_RPSR;
				}
				else
					_hoops_ICRCP (_hoops_CSIR, _hoops_PGHIR->_hoops_HGHIR[_hoops_IGRPS],
								   color, _hoops_SIAIS, _hoops_SHAIS);
			}
#endif
			else 
				color = _hoops_AHAIS;

			if (BIT (_hoops_PHAH.options, _hoops_CHRH))
				color = HD_Apply_Color_Effects (color, _hoops_PHAH);

			for (ii=0; ii<_hoops_HGII; ++ii) {
				_hoops_PCHA[index].red   = color.red;
				_hoops_PCHA[index].green = color.green;
				_hoops_PCHA[index].blue  = color.blue;
				if (BIT (flags, _hoops_IHRRA))
					_hoops_HCHA[index] = _hoops_PGHIR->_hoops_HGHIR[_hoops_IGRPS];
				index++;
			}

			_hoops_IGRPS += _hoops_CGRPS;
		}

		if (_hoops_IHAIS) {
			polyedge->_hoops_HCHA = _hoops_HCHA;

			if (_hoops_PHAIS)
				polyedge->_hoops_RPRCP = true;
		}
		else
			polyedge->_hoops_PCHA = _hoops_PCHA;
	}

	if (BIT (_hoops_IHRSR, T_GENERIC_EDGES)) {
		int		_hoops_GIGRI = polycylinder->point_count;

		if (BIT (polycylinder->flags, _hoops_GASSA))
			--_hoops_GIGRI;	/* _hoops_CGHI _hoops_CHH _hoops_SAHR _hoops_APHS _hoops_RH _hoops_SRS */

		/* _hoops_RGHS */
		for (_hoops_ICRHH=0; _hoops_ICRHH<_hoops_GIGRI; _hoops_ICRHH++) {
			int				shift = _hoops_ICRHH*_hoops_HGII;

			polyedge->lengths[polyedge->_hoops_PHHA] = _hoops_HGII+1;
			polyedge->total += polyedge->lengths[polyedge->_hoops_PHHA];
			polyedge->_hoops_PHHA++;
			*vi++ = shift + _hoops_HGII-1;
			*ei++ = 0;
			for (ii=0; ii<_hoops_HGII; ii++) {
				*vi = shift + ii;
				*ei = shift + ii;
				if (polyedge->_hoops_ASHA)
					_hoops_RSAI (&polyedge->_hoops_PCHA[*vi], RGB, &polyedge->_hoops_ASHA[*ei]);
				++vi;
				++ei;
			}
		}

		/* _hoops_CSHC _hoops_APGR */
		for (ii=0; ii<_hoops_HGII; ii++) {
			polyedge->lengths[polyedge->_hoops_PHHA] = polycylinder->point_count;
			polyedge->total += polyedge->lengths[polyedge->_hoops_PHHA];
			polyedge->_hoops_PHHA++;
			*vi++ = ii;
			*ei++ = 0;
			for (_hoops_ICRHH=1; _hoops_ICRHH<polycylinder->point_count; _hoops_ICRHH++) {
				*vi = ii + _hoops_ICRHH*_hoops_HGII;
				*ei = ii + (_hoops_ICRHH-1)*_hoops_HGII + _hoops_HCRGR;
				if (polyedge->_hoops_ASHA)
					_hoops_RSAI (&polyedge->_hoops_PCHA[vi[-1]], RGB, &polyedge->_hoops_ASHA[*ei]);
				vi++;
				ei++;
			}	 
		}
	}
	else {
		float						_hoops_GCAIS = 0.7071f;
		int							_hoops_RCAIS, _hoops_ACAIS;

		if (_hoops_IIAIS) {
			_hoops_RPRA const			*_hoops_CRIPA;

			_hoops_CRIPA = nr->transform_rendition->matrix->_hoops_PPRA()->data.elements;

			for (ii=0; ii<_hoops_PGRPS+2; ii++) {
				/* _hoops_HIHP _hoops_PPR _hoops_RPGP _hoops_RH _hoops_IPPA '_hoops_GSGGR' */
				if (_hoops_CRIPA[2][0] * _hoops_PRHH[ii].a +
					_hoops_CRIPA[2][1] * _hoops_PRHH[ii].b +
					_hoops_CRIPA[2][2] * _hoops_PRHH[ii].c +
					_hoops_CRIPA[2][3] * _hoops_PRHH[ii].d < 0.0f) {
					_hoops_AGHAR[ii] = _hoops_AARCA;
				}
				else {
					_hoops_AGHAR[ii] = _hoops_HARCA;
				}
			}
		}

		if (!_hoops_HHAHR) {
			_hoops_RCAIS = 0;
			_hoops_ACAIS = polycylinder->_hoops_ISPIR - 1;
			_hoops_RAAIS = _hoops_IHHIA;
			_hoops_AAAIS = _hoops_SHHIA;
		}
		else {
			_hoops_RCAIS = polycylinder->_hoops_ISPIR - 1;
			_hoops_ACAIS = 0;
			_hoops_RAAIS = _hoops_SHHIA;
			_hoops_AAAIS = _hoops_IHHIA;
		}

		if (polycylinder->radii[_hoops_RCAIS] > 0.0f) {
			if (!BIT (polycylinder->flags, _hoops_GASSA) &&
				(BIT (polycylinder->flags, _hoops_RAAIS) &&
				  ANYBIT (_hoops_IHRSR, T_HARD_EDGES|_hoops_CRHGP) ||
				 !BIT (polycylinder->flags, _hoops_RAAIS) &&
				  ANYBIT (_hoops_IHRSR, T_PERIMETER_EDGES|_hoops_CRHGP))) {
				/* _hoops_HAPR _hoops_AARI _hoops_HSPP */
				polyedge->lengths[polyedge->_hoops_PHHA] = _hoops_HGII + 1;
				polyedge->total += polyedge->lengths[polyedge->_hoops_PHHA];
				polyedge->_hoops_PHHA++;
				*vi++ = _hoops_HGII-1;
				*ei++ = 0;
				for (ii=0; ii<_hoops_HGII; ii++) {
					*vi++ = ii;
					*ei++ = ii;
				}
			}
			else if (_hoops_IIAIS || _hoops_CIAIS) {
				if (BIT (polycylinder->flags, _hoops_GASSA)) {
					/* _hoops_ARIP(_hoops_GRI) _hoops_IIGR _hoops_HAPR */
					for (ii=0; ii<_hoops_HGII; ii++) {
						int		other = ii+_hoops_PGRPS-_hoops_HGII;

						if (_hoops_IIAIS &&
							 _hoops_AGHAR[ii] != _hoops_AGHAR[other] ||
							_hoops_CIAIS &&
							_hoops_PIAIS (_hoops_PRHH[ii], _hoops_PRHH[other]) <=
							   _hoops_GCAIS) {
							polyedge->lengths[polyedge->_hoops_PHHA] = 2;
							polyedge->total += polyedge->lengths[polyedge->_hoops_PHHA];
							polyedge->_hoops_PHHA++;
							*vi++ = ii;
							*ei++ = 0;
							*vi++ = (ii+1)%_hoops_HGII;
							*ei++ = ii;
						}
					}
				}
				else if (BIT (polycylinder->flags, _hoops_RAAIS)) {
					/* _hoops_ARIP _hoops_IIGR _hoops_RH _hoops_HAPR */
					/* _hoops_RGAR _hoops_ASSIA _hoops_HCGC, _hoops_ACIPR & _hoops_CAHC _hoops_GIR _hoops_ARRS */
					for (ii=0; ii<_hoops_HGII; ii++) {
						if (_hoops_AGHAR[ii] != _hoops_AGHAR[_hoops_PGRPS]) {
							polyedge->lengths[polyedge->_hoops_PHHA] = 2;
							polyedge->total += polyedge->lengths[polyedge->_hoops_PHHA];
							polyedge->_hoops_PHHA++;
							*vi++ = ii;
							*ei++ = 0;
							*vi++ = (ii+1)%_hoops_HGII;
							*ei++ = ii;
						}
					}
				}
			}
		}

		if (polycylinder->radii[_hoops_ACAIS] > 0.0f) {
			if (!BIT (polycylinder->flags, _hoops_GASSA) &&
				(BIT (polycylinder->flags, _hoops_AAAIS) &&
				  ANYBIT (_hoops_IHRSR, T_HARD_EDGES|_hoops_CRHGP) ||
				 !BIT (polycylinder->flags, _hoops_AAAIS) &&
				  ANYBIT (_hoops_IHRSR, T_PERIMETER_EDGES|_hoops_CRHGP))) {
				/* _hoops_HAPR _hoops_AARI _hoops_RSGR */
				int				shift = _hoops_PGRPS;

				polyedge->lengths[polyedge->_hoops_PHHA] = _hoops_HGII + 1;
				polyedge->total += polyedge->lengths[polyedge->_hoops_PHHA];
				polyedge->_hoops_PHHA++;
				*vi++ = _hoops_HGII-1 + shift;
				*ei++ = 0;
				for (ii=0; ii<_hoops_HGII; ii++) {
					*vi++ = ii + shift;
					*ei++ = ii + shift;
				}
			}
			else if (_hoops_IIAIS) {
				if (BIT (polycylinder->flags, _hoops_GASSA)) {
					/* _hoops_ISAP _hoops_ARI, _hoops_PSHR _hoops_GAR _hoops_SRS _hoops_AGIR _hoops_ARRS */
				}
				else if (BIT (polycylinder->flags, _hoops_AAAIS)) {
					/* _hoops_ARIP _hoops_IIGR _hoops_RH _hoops_HAPR */
					for (ii=0; ii<_hoops_HGII; ii++) {
						if (_hoops_AGHAR[ii+_hoops_PGRPS-_hoops_HGII] != _hoops_AGHAR[_hoops_PGRPS+1]) {
							polyedge->lengths[polyedge->_hoops_PHHA] = 2;
							polyedge->total += polyedge->lengths[polyedge->_hoops_PHHA];
							polyedge->_hoops_PHHA++;
							*vi++ = ii+_hoops_PGRPS;
							*ei++ = 0;
							*vi++ = (ii+1)%_hoops_HGII+_hoops_PGRPS;
							*ei++ = ii+_hoops_PGRPS;
						}
					}
				}
			}
		}


		if (_hoops_IIAIS || _hoops_CIAIS) {
			int		_hoops_GIGRI = polycylinder->point_count-1;

			/* _hoops_RGHS (_hoops_AHSAR _hoops_SRS & _hoops_CGHI _hoops_PGAP _hoops_CHR _hoops_GIR _hoops_ARRS) */
			for (_hoops_ICRHH=1; _hoops_ICRHH<_hoops_GIGRI; _hoops_ICRHH++) {
				int				shift = _hoops_ICRHH*_hoops_HGII;

				for (ii=0; ii<_hoops_HGII; ii++) {
					int		current = ii+shift;
					int		other = ii+shift-_hoops_HGII;

					if (_hoops_IIAIS &&
						 _hoops_AGHAR[current] != _hoops_AGHAR[other] ||
						_hoops_CIAIS &&
						_hoops_PIAIS (_hoops_PRHH[current], _hoops_PRHH[other]) <= _hoops_GCAIS) {
						polyedge->lengths[polyedge->_hoops_PHHA] = 2;
						polyedge->total += polyedge->lengths[polyedge->_hoops_PHHA];
						polyedge->_hoops_PHHA++;
						*vi++ = shift + ii;
						*ei++ = 0;
						*vi++ = shift + (ii+1)%_hoops_HGII;
						*ei++ = shift + ii;
					}
				}
			}
		}

		if (_hoops_IIAIS) {
			/* _hoops_CSHC _hoops_APGR (_hoops_IIP _hoops_GHSAR _hoops_GAR _hoops_ACIPR _hoops_SPPR) */
			for (ii=0; ii<_hoops_HGII; ii++) {
				for (_hoops_ICRHH=0; _hoops_ICRHH<polycylinder->point_count-1; _hoops_ICRHH++) {
					int				shift = _hoops_ICRHH*_hoops_HGII;

					if (_hoops_AGHAR[shift+ii] != _hoops_AGHAR[shift+(ii+_hoops_HGII-1)%_hoops_HGII]) {
						polyedge->lengths[polyedge->_hoops_PHHA] = 2;
						polyedge->total += polyedge->lengths[polyedge->_hoops_PHHA];
						polyedge->_hoops_PHHA++;
						*vi++ = ii + _hoops_ICRHH*_hoops_HGII;
						*ei++ = 0;
						*vi++ = ii + (_hoops_ICRHH+1)*_hoops_HGII;
						*ei++ = ii + _hoops_ICRHH*_hoops_HGII + _hoops_HCRGR;
					}
				}
			}
		}
	}

	if (!BIT (_hoops_IHRSR, T_GENERIC_EDGES))
		polyedge->_hoops_SRHA |= _hoops_SRHH;

	if (polyedge->_hoops_ASHA)
		polyedge->_hoops_PCHA = null;

	if (polyedge->_hoops_PHHA > 0 && polyedge->total > 0)
		if (polyedge->_hoops_HCHA != null)
			HD_Draw_Indexicated_3D_Polyedge (nr, polyedge);
		else
			_hoops_RAIGH (nr, polyedge);

	if (_hoops_ASHA) {
		ASSERT (_hoops_ASHA != polyedge->_hoops_ASHA ||
				!BIT (polyedge->_hoops_RAHH, _hoops_PCGHR));
		FREE_ARRAY (_hoops_ASHA, polyedge->_hoops_SPHA, RGB);
	}

} /* _hoops_RSGR _hoops_API "_hoops_PGSA _hoops_RSRRA _hoops_SPPR" */


/* _hoops_RAGA _hoops_RH _hoops_HARS _hoops_IIGR _hoops_IRS _hoops_HIGR _hoops_IIGR _hoops_IRCGP _hoops_HCCGR, _hoops_SSS _hoops_RH _hoops_SPR _hoops_SGS
 * _hoops_SPASR _hoops_RH _hoops_SCGR _hoops_RHPP (_hoops_RPP _hoops_GII).   _hoops_CGP _hoops_PIRC _hoops_PAH _hoops_SHH _hoops_GSGI, _hoops_ASRC _hoops_IRAP.
 */
local _hoops_GACR const * _hoops_AACR (
	Net_Rendition const &		nr,
	_hoops_GACR const *		dl) {

	if (nr->_hoops_IRR->_hoops_GAHA && dl) do { 
		if (dl->_hoops_GHRI == nr->_hoops_SRA->_hoops_GHRI)
			return dl;
	} while ((dl = dl->next) != null);

	return null;
}

#endif




/* _hoops_CHII _hoops_HII _hoops_ICGC */
#define _hoops_PCAIS (_hoops_SSA|_hoops_IIRAP|_hoops_GSRC|_hoops_HIRC|_hoops_PHGI)
#define _hoops_HCAIS (_hoops_GCP|_hoops_HIRAP|_hoops_RGAC|_hoops_SSRC|_hoops_CSRC)
#define _hoops_ICAIS 0x8  /* _hoops_IRHS _hoops_IS _hoops_SHH _hoops_GIAH _hoops_HII _hoops_CCAIS */


GLOBAL_FUNCTION void HD_Std_3D_PolyCylinder (
	Net_Rendition const &		inr,
	PolyCylinder const *		polycylinder) {
#ifndef _hoops_PSPIR
	Net_Rendition				nr = inr;
	Display_Context alter *		dc = (Display_Context alter *) nr->_hoops_SRA;
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	_hoops_HHA const &	matr = nr->_hoops_IHA->_hoops_CHA;
	_hoops_AGHIR const *_hoops_PGHIR;
	Point						_hoops_HRIGA[512];
	Vector						_hoops_SCAIS[73];
	Vector						_hoops_GSAIS[512];
	RGB							_hoops_RHAIS[512];
	float						_hoops_AGRPS[512];
	_hoops_ARPA						_hoops_RSAIS[512];
	int							_hoops_ASAIS[512];
	Point *						points = _hoops_HRIGA;
	Vector *					_hoops_ICHA = _hoops_GSAIS;
	RGB *						_hoops_PCHA = _hoops_RHAIS;
	float *						_hoops_HCHA = _hoops_AGRPS;
	_hoops_ARPA *						_hoops_PRHH = _hoops_RSAIS;
	RGB *						_hoops_PAGI = null;
	int *						_hoops_AGHAR = _hoops_ASAIS;
	int							_hoops_HGII, _hoops_PSAIS;
	int							ii, _hoops_ICRHH;
	float						delta;
	Tristrip *					tristrip;
	Polyedge *					polyedge;
	int							*vi, *fi;
	int							offset1, offset2;
	_hoops_ACHR					_hoops_IHRSR;
	int							_hoops_IISRP;
	int							_hoops_HCRGR;
	int							_hoops_HSAIS;
	int							_hoops_PGRPS;
	int							index;
	float						_hoops_RAHCR;
	int							_hoops_HGCGP;
	float const					*_hoops_GAIAA, *_hoops_SAAIS, *_hoops_GPAIS;
	float						len, _hoops_ISAIS;
	bool						_hoops_HPAIS;
	bool						_hoops_IIAIS;
	bool						_hoops_CIAIS;
	bool						_hoops_CSAIS;
	bool						_hoops_SPAIS;
	bool						_hoops_GHAIS;
	bool						_hoops_SSAIS;
	bool						_hoops_GGPIS = true;
	bool						_hoops_RGPIS = false;
	bool						_hoops_AGPIS, _hoops_PGPIS;
	bool						_hoops_CHAIS, _hoops_HGPIS;
	bool						_hoops_IGPIS = false;
	bool						_hoops_CGPIS, _hoops_SGPIS;
	bool						_hoops_IHAIS, _hoops_GRPIS;
	bool						_hoops_IRAIS = false;
	int							_hoops_HHCAP;
	_hoops_GACR const			*_hoops_RRPIS = null;
	_hoops_GACR const			*_hoops_ARPIS = null;
	int							_hoops_RGP;
	bool						_hoops_HHAHR;
	int							_hoops_HGRPS = 0;
	int							_hoops_RAAIS;
	int							_hoops_AAAIS;
	unsigned Integer32			action_mask;
	_hoops_SPAGR						_hoops_RIIAA (polycylinder->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);

	if (polycylinder->point_count < 2) 
		return;
	_hoops_RGP = nr->_hoops_RGP;

	/* _hoops_HSPP _hoops_CCA _hoops_RH _hoops_PGSI _hoops_PAPR _hoops_GGR _hoops_CSPH, _hoops_ACPAR _hoops_IS _hoops_RGAR _hoops_RH _hoops_PGSI 
	 * _hoops_SGS _hoops_PAH _hoops_GCAS _hoops_SHH _hoops_HRCRA _hoops_HPP _hoops_HAHAR, _hoops_ACPAR _hoops_GASAR _hoops_IIHA _hoops_GPP
	 * _hoops_HPRC, _hoops_PSCR _hoops_HCHGA _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_RAAP _hoops_CCA _hoops_ISAP */
	action_mask = dc->_hoops_IPCI->mask;
	action_mask &= (_hoops_PGRI|_hoops_IGAI|_hoops_RSRI);
	if (!BIT(_hoops_RGP, T_FACES))
		action_mask &= ~_hoops_PGRI;
	if (!BIT(_hoops_RGP, T_ANY_SHELL_EDGE))
		action_mask &= ~_hoops_IGAI;
	if (!BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_EDGES))
		action_mask &= ~_hoops_RSRI;
	if (!action_mask)
		return;

	if (!BIT(dc->flags, _hoops_HSAGR) && 
		!BIT (nr->transform_rendition->flags, _hoops_AIHS) &&
		BIT (nr->transform_rendition->_hoops_APH, Heur_Culling_VIEW_FRUSTUM)) {

		if (HD_Transform_And_Test_Bounding (nr, &polycylinder->bounding,
											&nr->_hoops_SAIR->_hoops_HHCAR,
											&nr->transform_rendition->_hoops_AGAA,
											nr->_hoops_IRR->_hoops_GRGC) == Test_DISJOINT)
			return;
	}

	ZALLOC (tristrip, Tristrip);
	_hoops_ICAI (tristrip);
	ZALLOC (tristrip->_hoops_GSSH, _hoops_RRCC);
	_hoops_ICAI(tristrip->_hoops_GSSH);
	tristrip->_hoops_GSCP = (Geometry*)polycylinder;
	tristrip->bounding = polycylinder->bounding;

	ZALLOC (polyedge, Polyedge);
	_hoops_ICAI (polyedge);
	polyedge->_hoops_GSCP = (Geometry*)polycylinder;
	polyedge->bounding = polycylinder->bounding;

	_hoops_PGHIR = polycylinder->_hoops_RGHIR;
	_hoops_IHRSR = nr->_hoops_RGP & T_ANY_SHELL_EDGE;
	_hoops_IIAIS = BIT (_hoops_IHRSR, T_INTERIOR_SILHOUETTE_EDGES) &&
					   !BIT (_hoops_IHRSR, T_GENERIC_EDGES);
	_hoops_CIAIS = BIT (_hoops_IHRSR, T_HARD_EDGES) &&
				 !BIT (_hoops_IHRSR, T_GENERIC_EDGES);
	_hoops_HPAIS = !BIT (nr->transform_rendition->heuristics, _hoops_GPSA);
	_hoops_PGPIS = BIT (_hoops_RRGH->_hoops_CSA,
											  _hoops_HIRC & ~_hoops_AHGI);
	_hoops_HGPIS = BIT (_hoops_RRGH->_hoops_CSA,
											  _hoops_PHGI & ~_hoops_AHGI);
	_hoops_SGPIS = BIT (_hoops_RRGH->_hoops_CSA,
											  _hoops_SSRC & ~_hoops_AHGI);
	_hoops_GRPIS = BIT (_hoops_RRGH->_hoops_CSA,
											  _hoops_CSRC & ~_hoops_AHGI);

	/* _hoops_CGP _hoops_RH _hoops_RHPP _hoops_PAH _hoops_PRPIS _hoops_GCPA, _hoops_SR _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_PGSA _hoops_GHCPR _hoops_SPPR - _hoops_RH _hoops_RHPP
	   _hoops_GRS _hoops_PRPIS _hoops_RH _hoops_RGSSA _hoops_IS _hoops_GRHP _hoops_SCH _hoops_HII _hoops_HRPIS. _hoops_PGPR _hoops_SGH _hoops_RGR _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_SAHR 
	   _hoops_ASCA _hoops_RSSI _hoops_IAII _hoops_RH _hoops_RSSI _hoops_PAH _hoops_IRCH _hoops_ISGR _hoops_RH _hoops_SPPR. */
	if (BIT(dc->_hoops_PGCC.flags, _hoops_GHPGH) &&
		BIT (_hoops_RGP, T_FACES) && !BIT (_hoops_RGP, T_EDGES))
		_hoops_IRAIS = true;

	if (_hoops_PGHIR) {
		_hoops_SPAIS = !BIT (_hoops_RRGH->locks.color, Color_FRONT);
		_hoops_GHAIS = BIT (_hoops_RRGH->_hoops_CSA,
								(_hoops_SSRC |
								  _hoops_CSRC) & ~_hoops_AHGI) &&
						  !BIT (_hoops_RRGH->locks.color, Color_EDGE);

		_hoops_AGPIS = _hoops_PGPIS && _hoops_SPAIS;
		_hoops_CHAIS = _hoops_HGPIS &&
								   _hoops_PGHIR->_hoops_SIRHR == polycylinder->point_count &&
								   _hoops_SPAIS;
		_hoops_CGPIS = _hoops_SGPIS && _hoops_GHAIS;
		_hoops_IHAIS = _hoops_GRPIS &&
								   _hoops_PGHIR->_hoops_CCHPR  == polycylinder->point_count;

		if (!_hoops_CHAIS && !_hoops_AGPIS)
			_hoops_SPAIS = false;
		if (!_hoops_IHAIS && !_hoops_CGPIS)
			_hoops_GHAIS = false;

		_hoops_SSAIS = BIT (_hoops_RRGH->_hoops_PPH, _hoops_HAI);
	}
	else {
		_hoops_SPAIS = 
		_hoops_GHAIS = 
		_hoops_AGPIS = 
		_hoops_CHAIS = 
		_hoops_CGPIS = 
		_hoops_IHAIS = 
		_hoops_SSAIS = false;
	}

	_hoops_IISRP = nr->_hoops_ARA->_hoops_PRSI._hoops_IISRP;
	if (!BIT(nr->_hoops_ARA->_hoops_PRSI.options,_hoops_HRSI) || _hoops_IISRP < 0)
		_hoops_IISRP = 0;
	_hoops_HGII = _hoops_PSAIS = nr->_hoops_ARA->_hoops_GAICA.cylinder[_hoops_IISRP];
	if (_hoops_HGII < 0)				/* _hoops_IRPIS _hoops_SGGR */
		goto _hoops_HPAGR;

	/* _hoops_SAHR _hoops_PGSA _hoops_IRSS? */
	if (_hoops_HGII < 2 ||
		polycylinder->_hoops_ISPIR == 1 && polycylinder->radii[0] == 0.0f) {
		_hoops_CPAIS (nr, polycylinder, 
									 _hoops_IHRSR != 0, _hoops_SPAIS, _hoops_GHAIS);
		goto _hoops_HPAGR;
	}

	if (_hoops_RGP & T_FACES) {
		if (!BIT (nr->transform_rendition->flags, _hoops_GRHH) ||
			!BIT (_hoops_RGP, T_LIGHTS_FOR_FACES) ||
			nr->_hoops_IHA->_hoops_AGP == null) {
			/*-- _hoops_GRAPR _hoops_CRIRC --*/
		}
		else if (!ANYBIT (_hoops_RRGH->_hoops_CSA,
						  _hoops_IIRAP | _hoops_GGP| _hoops_SSA)) {
			/*--- _hoops_CRPIS _hoops_CRIRC ---*/
			tristrip->_hoops_PRHH = _hoops_PRHH;
			_hoops_RGPIS = true;
		}
		else {
			/*--- _hoops_SRPIS _hoops_CRIRC ---*/
			tristrip->_hoops_ICHA = _hoops_ICHA;
		}
		if (!tristrip->_hoops_ICHA) {
			/* _hoops_PRGI _hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_RRP _hoops_RH _hoops_GPHA _hoops_ASGA _hoops_IH _hoops_RCA, _hoops_SR _hoops_GHCA _hoops_RRP _hoops_CAPR _hoops_IH _hoops_RHI _hoops_SIA */
			if (BIT (_hoops_RRGH->_hoops_CSA, _hoops_GSRC)) {
				_hoops_HHA const &matr = nr->_hoops_IHA->_hoops_CHA;
				if (matr->texture[_hoops_RIA])
					tristrip->_hoops_ICHA = _hoops_ICHA; 
				if (matr->_hoops_SCA && 
					matr->_hoops_SCA->texture->_hoops_PSR == HK_PS_SURFACE_NORMAL)
					tristrip->_hoops_ICHA = _hoops_ICHA; 
			}
		}
	}
	if (_hoops_IHRSR) {
		if (!BIT (nr->transform_rendition->flags, _hoops_GRHH) ||
			!BIT (_hoops_RGP, T_LIGHTS_FOR_EDGES) ||
			nr->_hoops_RHP->_hoops_AGP == null) {
			/*-- _hoops_GRAPR _hoops_CRIRC --*/
		}
		else if (!ANYBIT (_hoops_RRGH->_hoops_CSA,
						  _hoops_HIRAP | _hoops_RCP| _hoops_GCP)) {
			polyedge->_hoops_ICHA = _hoops_ICHA;
			/*--- _hoops_CRPIS _hoops_CRIRC _hoops_IH _hoops_SPPR _hoops_HAR _hoops_GAPR _hoops_AGPC _hoops_HGPS ---*/
			/* _hoops_ACRI._hoops_GAPIS = _hoops_GAPIS; */
			_hoops_IGPIS = true; 
		}
		else {
			/*--- _hoops_SRPIS _hoops_CRIRC ---*/
			polyedge->_hoops_ICHA = _hoops_ICHA;
		}
	}

	_hoops_HHAHR = BIT (nr->_hoops_ARA->geometry_options, _hoops_RHGAP);

	if (_hoops_RGPIS)
		tristrip->_hoops_SRHA |= DL_FLAT_LIGHTING;
	if (_hoops_PGPIS)
		tristrip->_hoops_SRHA |= (DL_COLOR_INTERPOLATION|DL_FORCE_SMOOTH_SHADE_MODEL);
	if (_hoops_HGPIS)
		tristrip->_hoops_SRHA |= DL_INDEX_INTERPOLATION;
	if (BIT (nr->transform_rendition->flags, _hoops_GRHH) && 
		BIT (_hoops_RGP, T_LIGHTS_FOR_FACES)) 
		tristrip->_hoops_SRHA |= DL_LIGHTING;
	if (_hoops_SPAIS && _hoops_SSAIS)
		tristrip->_hoops_SRHA |= DL_LOCAL_GRAYSCALE;
	if (_hoops_IRAIS)
		tristrip->_hoops_CARI |= _hoops_RAHAR;
	if (_hoops_HHAHR)
		tristrip->_hoops_CARI |= _hoops_HCRC;
	if (_hoops_HPAIS)
		tristrip->_hoops_CARI |= _hoops_PCRC;
	if (BIT (nr->_hoops_ARA->geometry_options, _hoops_AHGAP))
		tristrip->_hoops_CARI |= _hoops_ICRC;
	if (BIT (nr->_hoops_PSGI, T_FACES))
		tristrip->_hoops_SRHA |= DL_HAS_TRANSPARENCY;
	if (_hoops_PGHIR) {
		if (ANYBIT (_hoops_RRGH->locks.color, Color_FRONT|Color_BACK))
			tristrip->_hoops_SRHA |= _hoops_IIRC;
		tristrip->_hoops_SRHA |= DL_VCOLORED_TRISTRIP;
	}

	if (matr->_hoops_SCA)
		tristrip->_hoops_GSSH->_hoops_SCAI = _hoops_PRAIS (matr->_hoops_SCA->texture->_hoops_PSR);

	tristrip->_hoops_GSAI = _hoops_RRGH->_hoops_CSA & _hoops_PCAIS;
	if (!_hoops_PGHIR)
		tristrip->_hoops_GSAI &= ~(_hoops_AHRAP|_hoops_HHRAP);

	if (_hoops_IGPIS)
		polyedge->_hoops_SRHA |= DL_FLAT_LIGHTING;
	if (_hoops_CGPIS)
		polyedge->_hoops_SRHA |= DL_COLOR_INTERPOLATION;
	if (_hoops_IHAIS)
		polyedge->_hoops_SRHA |= DL_INDEX_INTERPOLATION;
	if (_hoops_GHAIS && _hoops_SSAIS)
		polyedge->_hoops_SRHA |= DL_LOCAL_GRAYSCALE;
	if (_hoops_HHAHR)
		polyedge->_hoops_CARI |= _hoops_HCRC;
	if (BIT (nr->_hoops_ARA->geometry_options, _hoops_AHGAP))
		polyedge->_hoops_CARI |= _hoops_ICRC;
	if (BIT (nr->_hoops_PSGI, T_EDGES))
		polyedge->_hoops_SRHA |= DL_HAS_TRANSPARENCY;
	if (_hoops_PGHIR &&
		BIT (_hoops_RRGH->locks.color, Color_EDGE))
		polyedge->_hoops_SRHA |= _hoops_IIRC;

	polyedge->_hoops_GSAI = (_hoops_RRGH->_hoops_CSA & _hoops_HCAIS);
	if (!_hoops_PGHIR)
		polyedge->_hoops_GSAI &= ~(_hoops_AHRAP|_hoops_HHRAP);

	if (BIT (nr->transform_rendition->flags, _hoops_GRHH) && 
		BIT (nr->_hoops_RGP, T_LIGHTS_FOR_EDGES))
		polyedge->_hoops_GSAI |= _hoops_ICAIS;

	if (ANYBIT(dc->flags, _hoops_HSAGR|_hoops_IIGC)) {

		PolyCylinder alter *_hoops_SRCIP = (PolyCylinder alter *) polycylinder;
		// _hoops_CGPR _hoops_IGGC _hoops_HCGI'_hoops_GRI, _hoops_SCAC _hoops_GGSR _hoops_CPAP-_hoops_PAPA _hoops_AIRI _hoops_CPCI, _hoops_RPP _hoops_GII
		if (_hoops_SRCIP->_hoops_SGHIR) {
			HI_Au_Revoir ((_hoops_HPAH *)_hoops_SRCIP->_hoops_SGHIR);
			_hoops_SRCIP->_hoops_SGHIR = null;
		}
		if (_hoops_SRCIP->_hoops_GRHIR) {
			HI_Au_Revoir ((_hoops_HPAH *)_hoops_SRCIP->_hoops_GRHIR);
			_hoops_SRCIP->_hoops_GRHIR = null;
		}
	}

	if (polycylinder->type != _hoops_ASIP &&
		(polycylinder->_hoops_SGHIR || polycylinder->_hoops_GRHIR)) {

		if (BIT(_hoops_RGP, T_FACES) && 
			(_hoops_RRPIS = _hoops_AACR (nr, polycylinder->_hoops_SGHIR)) != null &&
			dc->_hoops_IPCI->draw_3d_tristrip != HD_Std_3D_Tristrip &&
			_hoops_RRPIS->list) {
			if (!BIT(_hoops_RRPIS->_hoops_AGRI, DL_INSUFFICIENT_VRAM)) {
				tristrip->_hoops_PHHA = 1;
				tristrip->total = 1000;
				tristrip->_hoops_SRHA |= DL_DO_NOT_RECOMPILE;
				if (_hoops_HPAIS)
					tristrip->_hoops_CARI |= _hoops_PCRC;
				tristrip->_hoops_GAHA = polycylinder->_hoops_SGHIR;
				if (_hoops_HGII == polycylinder->_hoops_SHSGP) {
					if (_hoops_SPAIS && _hoops_PGHIR != null &&
						(_hoops_PGHIR->_hoops_RCRHR > 0 ||
						 _hoops_PGHIR->_hoops_SIRHR > 0))
						 if (_hoops_CHAIS)
							tristrip->_hoops_HCHA = _hoops_HCHA;
						 else
							tristrip->_hoops_PCHA = _hoops_PCHA;
					if (_hoops_CHAIS) {
						tristrip->_hoops_SRHA |= _hoops_GGIA;
						_hoops_GAIGH (nr, tristrip);
					}
					else
						_hoops_HPHCP (nr, tristrip);
					tristrip->_hoops_PCHA = null;
					tristrip->_hoops_HCHA = null;
					/* _hoops_RPP _hoops_RH _hoops_GARI _hoops_AIRI _hoops_HIGR _hoops_RSAS'_hoops_RA _hoops_HGGPR, _hoops_SR _hoops_PAH _hoops_SRCH _hoops_ASCA 
					 * _hoops_RH _hoops_GSSR _hoops_PPRRR (_hoops_IHPPA _hoops_HPRC &= ~_hoops_AAHRC)*/
					if (_hoops_RRPIS->list != null)
						_hoops_RGP &= ~T_FACES;
				}
				else {
					/* _hoops_RAAA _hoops_SSCP _hoops_HGAS _hoops_CR _hoops_SR _hoops_CPIAR */
					if (_hoops_RRPIS->list)
						HD_Queue_Destroy_List (_hoops_RRPIS->list, true);
				}
				/* _hoops_SHS _hoops_RH _hoops_RHPP _hoops_RAPIS _hoops_IS _hoops_PGSA _hoops_RH _hoops_HIGR _hoops_PPR _hoops_HGGPR _hoops_SCH (_hoops_PSHRR _hoops_PGGA _hoops_HHH
				 * _hoops_ARGPR _hoops_HPAC _hoops_HGAS _hoops_CR _hoops_RH _hoops_GHIR _hoops_SCH _hoops_CSAP _hoops_SPIP).  
				 * _hoops_PS _hoops_RRP _hoops_IS _hoops_PSASA _hoops_RH _hoops_CPAP _hoops_PPR _hoops_HPPR _hoops_GICS. */
				tristrip->_hoops_PHHA = tristrip->total = 0;
				tristrip->_hoops_SRHA &= ~DL_DO_NOT_RECOMPILE;
				tristrip->_hoops_GAHA = null;
			}
		}
		if (BIT(_hoops_RGP, T_GENERIC_EDGES) && 
			(_hoops_ARPIS = _hoops_AACR (nr, polycylinder->_hoops_GRHIR)) != null &&
			dc->_hoops_IPCI->draw_3d_polyedge != HD_Std_3D_Polyedge &&
			_hoops_ARPIS->list) {
			if (!BIT(_hoops_ARPIS->_hoops_AGRI, DL_INSUFFICIENT_VRAM)) {
				polyedge->_hoops_PHHA = 1;
				polyedge->total = 1000;
				polyedge->_hoops_SRHA |= DL_DO_NOT_RECOMPILE;
				polyedge->_hoops_GAHA = polycylinder->_hoops_GRHIR;
				if (_hoops_HGII == polycylinder->_hoops_SHSGP) {
					if (_hoops_GHAIS && _hoops_PGHIR != null &&
						(_hoops_PGHIR->_hoops_RCRHR > 0 ||
						 _hoops_PGHIR->_hoops_SIRHR > 0))
						 if (_hoops_IHAIS)
							polyedge->_hoops_HCHA = _hoops_HCHA;
						 else
							polyedge->_hoops_PCHA = _hoops_PCHA;
					_hoops_RAIGH (nr, polyedge);
					polyedge->_hoops_PCHA = null;
					polyedge->_hoops_HCHA = null;
					if (_hoops_ARPIS->list != null)
						_hoops_RGP &= ~T_ANY_EDGE;
				}
				else {
					/* _hoops_RAAA _hoops_SSCP _hoops_HGAS _hoops_CR _hoops_SR _hoops_CPIAR */
					HD_Queue_Destroy_List (_hoops_ARPIS->list, true);
				}
				polyedge->_hoops_PHHA = polyedge->total = 0;
				polyedge->_hoops_SRHA &= ~DL_DO_NOT_RECOMPILE;
				polyedge->_hoops_GAHA = null;
			}
		}
		if (!ANYBIT (_hoops_RGP, T_FACES|T_ANY_EDGE))
			goto _hoops_HPAGR;  /* _hoops_AIRI _hoops_CPCI _hoops_AICS.  _hoops_HCR _hoops_CPHR! */
	}

	if (72 % _hoops_HGII)
		_hoops_HGII = _hoops_AIAIS(_hoops_HGII);
	_hoops_HGCGP = 72/_hoops_HGII;

	delta = 360.0f / _hoops_HGII;

	_hoops_HCRGR = polycylinder->point_count * _hoops_HGII;
	_hoops_PGRPS = _hoops_HCRGR - _hoops_HGII;	/* _hoops_RHAP _hoops_HAR _hoops_GCIS _hoops_RIRR _hoops_GAPR */
	/* '_hoops_IHH' _hoops_IHIGR _hoops_IRS _hoops_CAAIS _hoops_IS _hoops_SHH _hoops_PICSI _hoops_IGIAR _hoops_SPR _hoops_PPAP _hoops_IS _hoops_CCIH _hoops_GH _hoops_HH _hoops_CPHH, _hoops_PPR 
	 * _hoops_SSRS _hoops_RSSA _hoops_IS _hoops_SHH _hoops_PICSI _hoops_HPGR _hoops_RH _hoops_PCAS (_hoops_CR _hoops_SSIA _hoops_GRS _hoops_HS _hoops_HAGH _hoops_ASGA) */
	_hoops_HHCAP = polycylinder->point_count + 2*_hoops_HGII; 

	/* _hoops_IRHH _hoops_RCRR _hoops_SGS _hoops_RPP _hoops_PA _hoops_CGPRA _hoops_IS _hoops_PCGPA _hoops_AGCR _hoops_HCCGR, _hoops_SSIA _hoops_IRHH 
	 * _hoops_IRS _hoops_ACAHP _hoops_IPS.  _hoops_RCHPR _hoops_SIAS _hoops_SHH _hoops_PHPC _hoops_CRGR _hoops_AAPIS _hoops_RRGC _hoops_GC */
	tristrip->_hoops_SRHA |= _hoops_GAHH | DL_TEMPORARY_DATA;
	polyedge->_hoops_SRHA |= _hoops_GAHH | DL_TEMPORARY_DATA;

	tristrip->point_count = _hoops_HSAIS = _hoops_HCRGR;
	tristrip->face_count = _hoops_PGRPS;
	if (!BIT (polycylinder->flags, _hoops_GASSA)) {
		if (BIT(polycylinder->flags, _hoops_IHHIA))
			tristrip->face_count++;
		if (BIT(polycylinder->flags, _hoops_SHHIA))
			tristrip->face_count++;
	}

	if (_hoops_HCRGR+_hoops_HHCAP > _hoops_GGAPR(_hoops_HRIGA)) {
		ALLOC_ARRAY_CACHED (points, _hoops_HCRGR+_hoops_HHCAP, Point);
		ALLOC_ARRAY_CACHED (_hoops_ICHA, _hoops_HCRGR+_hoops_HHCAP, Vector);
		ALLOC_ARRAY_CACHED (_hoops_PCHA, _hoops_HCRGR+_hoops_HHCAP, RGB);
		ALLOC_ARRAY_CACHED (_hoops_HCHA, _hoops_HCRGR+_hoops_HHCAP, float);
		ALLOC_ARRAY_CACHED (_hoops_PRHH, _hoops_PGRPS + 2, _hoops_ARPA);
		ALLOC_ARRAY_CACHED (_hoops_AGHAR, _hoops_PGRPS + 2, int);
		if (tristrip->_hoops_ICHA)
			tristrip->_hoops_ICHA = _hoops_ICHA;
		if (tristrip->_hoops_PRHH)
			tristrip->_hoops_PRHH = _hoops_PRHH;
		if (polyedge->_hoops_ICHA)
			polyedge->_hoops_ICHA = _hoops_ICHA;
	}

	_hoops_CSAIS = tristrip->_hoops_PRHH || _hoops_IIAIS || _hoops_CIAIS;

	/* _hoops_SRPA _hoops_HSCHR _hoops_IIHA _hoops_GPP _hoops_RSSP */
	if (_hoops_HPAIS) {
		offset1 = 0;
		offset2 = _hoops_HGII;
	}
	else {
		offset1 = _hoops_HGII;
		offset2 = 0;
	}

	if (!_hoops_HHAHR) {
		_hoops_HGRPS = 0;
		_hoops_RAAIS = _hoops_IHHIA;
		_hoops_AAAIS = _hoops_SHHIA;
	}
	else {
		_hoops_HGRPS = polycylinder->_hoops_ISPIR-1;
		_hoops_RAAIS = _hoops_SHHIA;
		_hoops_AAAIS = _hoops_IHHIA;
	}

	_hoops_GAIAA = HI_Get_Sin72_Lookup();
	for (_hoops_ICRHH=0; _hoops_ICRHH<polycylinder->point_count; _hoops_ICRHH++) {
		Vector			_hoops_GGHI;
		Vector			_hoops_RGHI;
		Point			*p, *_hoops_HRHRA;
		Vector *		_hoops_HCPCP;
		Point const *	center;
		float			radius = polycylinder->radii[_hoops_HGRPS];

		_hoops_RAHCR = polycylinder->_hoops_GGHIR[_hoops_ICRHH];
		if (_hoops_RAHCR < 0)
			_hoops_RAHCR += 360;
		
		_hoops_SAAIS = _hoops_GAIAA + (int)(72.0f * _hoops_RAHCR / 360.0f);
		_hoops_GPAIS = _hoops_SAAIS + 18;								/* _hoops_HHSPA(_hoops_SISR) = _hoops_IHSPA(_hoops_SISR-90) */
		center = &polycylinder->points[_hoops_ICRHH];
		_hoops_GGHI.x = polycylinder->_hoops_CSPIR[_hoops_ICRHH].axis[0].x * radius;
		_hoops_GGHI.y = polycylinder->_hoops_CSPIR[_hoops_ICRHH].axis[0].y * radius;
		_hoops_GGHI.z = polycylinder->_hoops_CSPIR[_hoops_ICRHH].axis[0].z * radius;
		_hoops_RGHI.x = polycylinder->_hoops_CSPIR[_hoops_ICRHH].axis[1].x * radius;
		_hoops_RGHI.y = polycylinder->_hoops_CSPIR[_hoops_ICRHH].axis[1].y * radius;
		_hoops_RGHI.z = polycylinder->_hoops_CSPIR[_hoops_ICRHH].axis[1].z * radius;
		p = &points[_hoops_ICRHH*_hoops_HGII];
		_hoops_HRHRA = p + _hoops_HGII;

		if (radius == 0.0f) {
			ii = 0;
			if (_hoops_HGII >= 4) {
				p[0] = *center;
				p[1] = *center;
				_hoops_AIGA(&p[0], 2, Point, &p[2]);
				for (ii = 4; ii < _hoops_HGII; ii += 4) {
					_hoops_AIGA(&p[0], 4, Point, &p[ii]);
				}
			}
			while (ii < _hoops_HGII) {
				p[ii] = *center;
				ii++;
			}	 
		}
		else {
			_hoops_HCPCP = &_hoops_ICHA[_hoops_ICRHH*_hoops_HGII];
			while (p < _hoops_HRHRA) {
				_hoops_HCPCP->x = _hoops_GPAIS[0]*_hoops_GGHI.x + _hoops_SAAIS[0]*_hoops_RGHI.x;
				_hoops_HCPCP->y = _hoops_GPAIS[0]*_hoops_GGHI.y + _hoops_SAAIS[0]*_hoops_RGHI.y;
				_hoops_HCPCP->z = _hoops_GPAIS[0]*_hoops_GGHI.z + _hoops_SAAIS[0]*_hoops_RGHI.z;
				p->x = _hoops_HCPCP->x + center->x;
				p->y = _hoops_HCPCP->y + center->y;
				p->z = _hoops_HCPCP->z + center->z;
				_hoops_GPAIS += _hoops_HGCGP;
				_hoops_SAAIS += _hoops_HGCGP;
				p++;
				_hoops_HCPCP++;
			}
		}

		if (!_hoops_HHAHR) {
			if (++_hoops_HGRPS == polycylinder->_hoops_ISPIR)
				_hoops_HGRPS = 0;
		}
		else {
			if (_hoops_HGRPS-- == 0)
				_hoops_HGRPS = polycylinder->_hoops_ISPIR - 1;
		}
	}

	if (tristrip->_hoops_ICHA || polyedge->_hoops_ICHA) {
		/* _hoops_GASA: _hoops_RH _hoops_HSPR _hoops_RIS _hoops_GHSAI _hoops_ISCP _hoops_PAPIS _hoops_HAPIS
		 * _hoops_CGPR _hoops_SCH _hoops_IAPIS _hoops_IRS _hoops_HHACR _hoops_PSAA.  _hoops_HHIGR _hoops_HRGR _hoops_CAPIS _hoops_HAHH _hoops_IH _hoops_HICAA _hoops_ARAR _hoops_HGPP _hoops_GAR _hoops_GGR
		 * _hoops_ARRPA _hoops_RPGP #1949 _hoops_CAS _hoops_HAHAR _hoops_CHR _hoops_IGI _hoops_IS _hoops_ARPR _hoops_IRS _hoops_SAPIS _hoops_HSGP.  _hoops_GHAP _hoops_HS _hoops_HAR _hoops_GAPR,
		 * _hoops_HGRRA _hoops_GSGI _hoops_IRS "_hoops_SHISR" _hoops_IPI _hoops_AGIR _hoops_CAS _hoops_SCH _hoops_HRGR _hoops_HAHH, _hoops_HIS _hoops_SCH _hoops_GHCA _hoops_SHH _hoops_GHGC _hoops_GPPIS _hoops_RGR _hoops_SPHR. */
		if (polycylinder->_hoops_ISPIR > 1) {
			float _hoops_RPPIS;

			/* _hoops_SAHR _hoops_IAHP, _hoops_HIS _hoops_ASSP'_hoops_RA _hoops_RPSHR _hoops_RPP _hoops_RH _hoops_SACGP _hoops_CHR _hoops_AAGIR */
			for (_hoops_ICRHH = 0; _hoops_ICRHH < polycylinder->_hoops_ISPIR - 1; _hoops_ICRHH++) {
				_hoops_RPPIS = polycylinder->radii[_hoops_ICRHH] - polycylinder->radii[_hoops_ICRHH+1];
				if (_hoops_RPPIS < -_hoops_CACIR || _hoops_RPPIS > _hoops_CACIR) {
					_hoops_GGPIS = false;
					_hoops_CSAIS = true;
					break;
				}
			}
		}
		if (_hoops_GGPIS) {
			Vector			*_hoops_HCPCP, *_hoops_APPIS;

			/* _hoops_RGR _hoops_SSCP _hoops_IS _hoops_ARAS _hoops_ICSI, _hoops_HIS _hoops_GA'_hoops_RA _hoops_SGH _hoops_PPPIS _hoops_RIR _hoops_GSSR... */
			_hoops_HCPCP = _hoops_ICHA;
			_hoops_APPIS = _hoops_ICHA + _hoops_HCRGR;
			while (_hoops_HCPCP < _hoops_APPIS) {
				len = (float)sqrt(_hoops_HCPCP->x*_hoops_HCPCP->x + _hoops_HCPCP->y*_hoops_HCPCP->y + _hoops_HCPCP->z*_hoops_HCPCP->z);
				if (len > 1e-20) {
					_hoops_ISAIS = 1.0f/len;
					_hoops_HCPCP->x *= _hoops_ISAIS;
					_hoops_HCPCP->y *= _hoops_ISAIS;
					_hoops_HCPCP->z *= _hoops_ISAIS;
				}
				_hoops_HCPCP++;		
			}
		}
	}

	if (_hoops_CSAIS) {
		_hoops_ARPA *		_hoops_CAGRA;

		/* _hoops_HPPIS _hoops_SAGGR _hoops_IRHP _hoops_PSPAR _hoops_CPIC _hoops_AARI, _hoops_PGAP _hoops_CHR _hoops_PSCR _hoops_IGISH
		 * _hoops_CCA _hoops_RH _hoops_PGGHR _hoops_CPIC _hoops_IGIAR _hoops_IS _hoops_HGCR _hoops_HPHR _hoops_ASGA.	_hoops_PAGA _hoops_SGS _hoops_RPP _hoops_RH
		 * _hoops_PSAA _hoops_HRGR 0, _hoops_RH _hoops_PSPAR _hoops_AARI _hoops_CHH _hoops_SHH _hoops_ARHAR, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IS
		 * _hoops_SGH _hoops_IRS _hoops_HAGH _hoops_CCHRA -- _hoops_RH _hoops_CSHC _hoops_PSPAR _hoops_CGH _hoops_SRSGR _hoops_IRS _hoops_PRII
		 * _hoops_GGSR _hoops_HII _hoops_RH _hoops_PPSR, _hoops_HIS _hoops_SR _hoops_PAH _hoops_SHHP _hoops_CAPR (_hoops_RPP _hoops_RH _hoops_SPS _hoops_PSAA _hoops_HRGR _hoops_GACC
		 * 0 _hoops_RGR _hoops_HRGR _hoops_ARHAR, _hoops_HIH _hoops_HIS _hoops_CHR _hoops_RH _hoops_RSSI _hoops_PSCR...) */

		if (!_hoops_HHAHR)
			_hoops_HGRPS = 0;
		else
			_hoops_HGRPS = polycylinder->_hoops_ISPIR - 1;

		index = 0;
		for (_hoops_ICRHH=0; _hoops_ICRHH<polycylinder->point_count-1; _hoops_ICRHH++) {
			for (ii=0; ii<_hoops_HGII; ii++) {
				_hoops_SCAIS[ii].x = points[ii + index + _hoops_HGII].x - points[ii + index].x;
				_hoops_SCAIS[ii].y = points[ii + index + _hoops_HGII].y - points[ii + index].y;
				_hoops_SCAIS[ii].z = points[ii + index + _hoops_HGII].z - points[ii + index].z;
			}
			_hoops_SCAIS[ii].x = _hoops_SCAIS[0].x;
			_hoops_SCAIS[ii].y = _hoops_SCAIS[0].y;
			_hoops_SCAIS[ii].z = _hoops_SCAIS[0].z;

			if (polycylinder->radii[_hoops_HGRPS] == 0.0f) {
				for (ii=0; ii<_hoops_HGII; ii++) {
					HI_Cross_Product (&_hoops_SCAIS[ii+1],
									  &_hoops_SCAIS[ii],
									  (Vector *)&_hoops_PRHH[index]);
					/* _hoops_RGR _hoops_SSCP _hoops_IS _hoops_ARAS _hoops_ICSI, _hoops_HIS _hoops_GA'_hoops_RA _hoops_SGH _hoops_PPPIS */
					_hoops_CAGRA = &_hoops_PRHH[index];
					len = (float)sqrt(_hoops_CAGRA->a*_hoops_CAGRA->a + _hoops_CAGRA->b*_hoops_CAGRA->b + _hoops_CAGRA->c*_hoops_CAGRA->c);
					if (len > 1e-20) {
						_hoops_ISAIS = 1.0f/len;
						_hoops_CAGRA->a *= _hoops_ISAIS;
						_hoops_CAGRA->b *= _hoops_ISAIS;
						_hoops_CAGRA->c *= _hoops_ISAIS;
					}
					_hoops_PRHH[index].d = -(_hoops_PRHH[index].a * points[index].x +
											  _hoops_PRHH[index].b * points[index].y +
											  _hoops_PRHH[index].c * points[index].z);
					index++;
				}				
			}
			else {
				int		next;
				int		_hoops_IPPIS;

				_hoops_IPPIS = _hoops_HGII-1;
				for (ii=0; ii<_hoops_HGII; ii++) {
					next = index+1;
					if (ii == _hoops_IPPIS)
						next -= _hoops_HGII;
					_hoops_PRHH[index].a = points[next].x - points[index].x;
					_hoops_PRHH[index].b = points[next].y - points[index].y;
					_hoops_PRHH[index].c = points[next].z - points[index].z;

					HI_Cross_Product ((Vector *)&_hoops_PRHH[index],
									  &_hoops_SCAIS[ii],
									  (Vector *)&_hoops_PRHH[index]);
					/* _hoops_RGR _hoops_SSCP _hoops_IS _hoops_ARAS _hoops_ICSI, _hoops_HIS _hoops_GA'_hoops_RA _hoops_SGH _hoops_PPPIS */
					_hoops_CAGRA = &_hoops_PRHH[index];
					len = (float)sqrt(_hoops_CAGRA->a*_hoops_CAGRA->a + _hoops_CAGRA->b*_hoops_CAGRA->b + _hoops_CAGRA->c*_hoops_CAGRA->c);
					if (len > 1e-20) {
						_hoops_ISAIS = 1.0f/len;
						_hoops_CAGRA->a *= _hoops_ISAIS;
						_hoops_CAGRA->b *= _hoops_ISAIS;
						_hoops_CAGRA->c *= _hoops_ISAIS;
					}
					_hoops_PRHH[index].d = -(_hoops_PRHH[index].a * points[index].x +
											  _hoops_PRHH[index].b * points[index].y +
											  _hoops_PRHH[index].c * points[index].z);
					index++;
				}
			}

			if (!_hoops_HHAHR) {
				if (++_hoops_HGRPS == polycylinder->_hoops_ISPIR)
					_hoops_HGRPS = 0;
			}
			else {
				if (_hoops_HGRPS-- == 0)
					_hoops_HGRPS = polycylinder->_hoops_ISPIR - 1;
			}
		}
		if (!_hoops_GGPIS && 
			 (tristrip->_hoops_ICHA || polyedge->_hoops_ICHA)) {

			if (polycylinder->point_count == 2) {
				float _hoops_CPPIS = _hoops_SGIHR(
					_hoops_PRHH[0].a * _hoops_PRHH[0].a  +  
					_hoops_PRHH[0].b * _hoops_PRHH[0].b  +  
					_hoops_PRHH[0].c * _hoops_PRHH[0].c);
				if (_hoops_CPPIS != 0.0f)
					_hoops_CPPIS = 1.0f / _hoops_CPPIS;
				for (ii=0; ii<_hoops_HGII; ii++) {
					_hoops_ICHA[ii].x = _hoops_PRHH[ii].a * _hoops_CPPIS;
					_hoops_ICHA[ii].y = _hoops_PRHH[ii].b * _hoops_CPPIS;
					_hoops_ICHA[ii].z = _hoops_PRHH[ii].c * _hoops_CPPIS;
				}
				_hoops_AIGA(&_hoops_ICHA[0], _hoops_HGII, Vector, &_hoops_ICHA[_hoops_HGII]);
			}
			else {
				/* _hoops_GRAS _hoops_GPHA _hoops_ASGA _hoops_HPP _hoops_SPRHS _hoops_IRPR _hoops_HSP _hoops_ASGA */
				index = 0;
				for (_hoops_ICRHH=0; _hoops_ICRHH<polycylinder->point_count; _hoops_ICRHH++) {
					for (ii=0; ii<_hoops_HGII; ii++) {
						_hoops_ICHA[index].x = 0.0f;
						_hoops_ICHA[index].y = 0.0f;
						_hoops_ICHA[index].z = 0.0f;

						index++;
					}
				}
				index = 0;
				for (_hoops_ICRHH=0; _hoops_ICRHH<polycylinder->point_count-1; _hoops_ICRHH++) {
					for (ii=0; ii<_hoops_HGII; ii++) {
						int				prev = _hoops_ICRHH*_hoops_HGII + (ii+_hoops_HGII-1)%_hoops_HGII;

						_hoops_ICHA[index].x += _hoops_PRHH[index].a;
						_hoops_ICHA[index].y += _hoops_PRHH[index].b;
						_hoops_ICHA[index].z += _hoops_PRHH[index].c;

						_hoops_ICHA[index].x += _hoops_PRHH[prev].a;
						_hoops_ICHA[index].y += _hoops_PRHH[prev].b;
						_hoops_ICHA[index].z += _hoops_PRHH[prev].c;

						_hoops_ICHA[index+_hoops_HGII].x += _hoops_PRHH[index].a;
						_hoops_ICHA[index+_hoops_HGII].y += _hoops_PRHH[index].b;
						_hoops_ICHA[index+_hoops_HGII].z += _hoops_PRHH[index].c;

						_hoops_ICHA[index+_hoops_HGII].x += _hoops_PRHH[prev].a;
						_hoops_ICHA[index+_hoops_HGII].y += _hoops_PRHH[prev].b;
						_hoops_ICHA[index+_hoops_HGII].z += _hoops_PRHH[prev].c;

						index++;
					}
				}
				if (BIT (polycylinder->flags, _hoops_GASSA)) {
					for (ii=0; ii<_hoops_HGII; ii++) {
						int				_hoops_PHHCA = _hoops_PGRPS + ii;

						_hoops_ICHA[ii].x += _hoops_ICHA[_hoops_PHHCA].x;
						_hoops_ICHA[ii].y += _hoops_ICHA[_hoops_PHHCA].y;
						_hoops_ICHA[ii].z += _hoops_ICHA[_hoops_PHHCA].z;

						_hoops_ICHA[_hoops_PHHCA].x = _hoops_ICHA[ii].x;
						_hoops_ICHA[_hoops_PHHCA].y = _hoops_ICHA[ii].y;
						_hoops_ICHA[_hoops_PHHCA].z = _hoops_ICHA[ii].z;
					}
				}
				HI_Normalize_Vectors(polycylinder->point_count * _hoops_HGII, _hoops_ICHA);
			}
		}
	}

	if (_hoops_CSAIS ||
		(polycylinder->flags & _hoops_PPSSA) &&
		!BIT (polycylinder->flags, _hoops_GASSA)) {
		Point const *		center;

		center = &polycylinder->points[0];
		ii = _hoops_PGRPS;
		_hoops_PRHH[ii].a = polycylinder->_hoops_ACCSA[0].x;
		_hoops_PRHH[ii].b = polycylinder->_hoops_ACCSA[0].y;
		_hoops_PRHH[ii].c = polycylinder->_hoops_ACCSA[0].z;
		_hoops_PRHH[ii].d = -(_hoops_PRHH[ii].a * center->x +
							   _hoops_PRHH[ii].b * center->y +
							   _hoops_PRHH[ii].c * center->z);

		center = &polycylinder->points[polycylinder->point_count-1];
		ii = _hoops_PGRPS+1;
		_hoops_PRHH[ii].a = polycylinder->_hoops_ACCSA[1].x;
		_hoops_PRHH[ii].b = polycylinder->_hoops_ACCSA[1].y;
		_hoops_PRHH[ii].c = polycylinder->_hoops_ACCSA[1].z;
		_hoops_PRHH[ii].d = -(_hoops_PRHH[ii].a * center->x +
							   _hoops_PRHH[ii].b * center->y +
							   _hoops_PRHH[ii].c * center->z);
	}


	if (_hoops_RGP & T_FACES) {
		if (nr->_hoops_CPP->_hoops_PRH.style == _hoops_GCPI &&
			nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR < 1.0f)
			nr = _hoops_HHPRC (nr);

		tristrip->lengths_allocated=3*_hoops_HCRGR/2;
		tristrip->_hoops_IPII = 3*_hoops_HCRGR;
		tristrip->_hoops_SGAHR = 3*_hoops_HCRGR+_hoops_HHCAP;

		ALLOC_ARRAY_CACHED (tristrip->lengths, tristrip->lengths_allocated, int);
		ALLOC_ARRAY_CACHED (tristrip->_hoops_AIHA, tristrip->_hoops_IPII, int);
		ALLOC_ARRAY_CACHED (tristrip->face_indices, tristrip->_hoops_SGAHR, int);
		tristrip->_hoops_RAHH |= _hoops_AAHH;

		tristrip->points = points;
		vi = tristrip->_hoops_AIHA;
		fi = tristrip->face_indices;

		if (_hoops_SPAIS && _hoops_PGHIR != null &&
			(_hoops_PGHIR->_hoops_RCRHR > 0 ||
			 _hoops_PGHIR->_hoops_SIRHR > 0)) {
			_hoops_RHAH const *		_hoops_CSIR;
			RGB						_hoops_AHAIS;
			bool					_hoops_SIAIS;
			int						_hoops_IGRPS = 0, _hoops_CGRPS = 1;

			_hoops_SIAIS = ALLBITS (_hoops_RRGH->_hoops_CSA,
										 (_hoops_HIRC |
										  _hoops_PHGI) & ~_hoops_AHGI);

			_hoops_CSIR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR;

			_hoops_AHAIS = nr->_hoops_IHA->_hoops_CHA->_hoops_CSHR;

			if (BIT (nr->_hoops_ARA->geometry_options, _hoops_AHGAP)) {
				_hoops_IGRPS = polycylinder->point_count - 1;
				_hoops_CGRPS = -1;
			}

			_hoops_AHAH			_hoops_PHAH = nr->_hoops_ARA->_hoops_IHRH;
			_hoops_AHAH 		_hoops_SHAIS;

			index = 0;
			for (_hoops_ICRHH=0; _hoops_ICRHH<polycylinder->point_count; _hoops_ICRHH++) {
				RGB						color;
				_hoops_CGHIR		flags;

				flags = _hoops_PGHIR->flags[_hoops_IGRPS];

				if (BIT (flags, _hoops_GIRRA))
					color = _hoops_PGHIR->fcolors[_hoops_IGRPS];
#ifndef DISABLE_COLOR_MAPS
				else if (BIT (flags, _hoops_CHRRA)) {
					if (_hoops_CSIR->length == 0) {
#if 0
						HD_Report_Null_Color_Map ("polycylinder", _hoops_CSIR);
#endif
						color = _hoops_GPSR::_hoops_RPSR;
					}
					else
						_hoops_ICRCP (_hoops_CSIR, _hoops_PGHIR->_hoops_IGHIR[_hoops_IGRPS],
									   color, _hoops_SIAIS, _hoops_SHAIS);
				}
#endif
				else
					color = _hoops_AHAIS;

				if (BIT (_hoops_PHAH.options, _hoops_CHRH))
					color = HD_Apply_Color_Effects (color, _hoops_PHAH);

				for (ii=0; ii<_hoops_HGII; ++ii) {
					_hoops_PCHA[index].red   = color.red;
					_hoops_PCHA[index].green = color.green;
					_hoops_PCHA[index].blue  = color.blue;
					if (BIT (flags, _hoops_CHRRA))
						_hoops_HCHA[index] = _hoops_PGHIR->_hoops_IGHIR[_hoops_IGRPS];
					index++;
				}

				_hoops_IGRPS += _hoops_CGRPS;
			}

			if (_hoops_CHAIS) {
				tristrip->_hoops_HCHA = _hoops_HCHA;

				if (_hoops_AGPIS && BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_FACES))
					tristrip->_hoops_RPRCP = true;
			}
			else
				tristrip->_hoops_PCHA = _hoops_PCHA;

#if 0
			if (!_hoops_CHAIS && !_hoops_AGPIS) {
				ALLOC_ARRAY (_hoops_PAGI, tristrip->face_count, RGB);
				tristrip->_hoops_PAGI = _hoops_PAGI;
			}
#endif
		}

		for (_hoops_ICRHH=0; _hoops_ICRHH<polycylinder->point_count-1; _hoops_ICRHH++) {
			int				shift = _hoops_ICRHH * _hoops_HGII;

			/* _hoops_CGGR _hoops_CSGPS _hoops_AARI */
			tristrip->lengths[tristrip->_hoops_PHHA] = 2*_hoops_HGII+2;
			tristrip->total += tristrip->lengths[tristrip->_hoops_PHHA];
			tristrip->_hoops_PHHA++;

			/* _hoops_HSPP "_hoops_ARPP" _hoops_RH _hoops_GSSR _hoops_ICPPR */
			*vi = shift + _hoops_HGII-1 + offset1;
			*fi = shift + 0;
			if (tristrip->_hoops_PAGI)
				_hoops_RSAI (&tristrip->_hoops_PCHA[*vi], RGB, &tristrip->_hoops_PAGI[*fi]);
			++vi;
			++fi;
			*vi = shift + _hoops_HGII-1 + offset2;
			*fi = shift + 0;
			if (tristrip->_hoops_PAGI)
				_hoops_RSAI (&tristrip->_hoops_PCHA[*vi], RGB, &tristrip->_hoops_PAGI[*fi]);
			++vi;
			++fi;
			for (ii=0; ii<_hoops_HGII; ii++) {
				*vi = shift + ii+offset1;
				*fi = shift + ii;
				if (tristrip->_hoops_PAGI)
					_hoops_RSAI (&tristrip->_hoops_PCHA[*vi], RGB, &tristrip->_hoops_PAGI[*fi]);
				++vi;
				++fi; 
				*vi = shift + ii+offset2;
				*fi = shift + ii;
				if (tristrip->_hoops_PAGI)
					_hoops_RSAI (&tristrip->_hoops_PCHA[*vi], RGB, &tristrip->_hoops_PAGI[*fi]);
				++vi;
				++fi;
			}
		}

		if (ANYBIT (polycylinder->flags, _hoops_PPSSA) &&
			!BIT (polycylinder->flags, _hoops_GASSA)) {
			int				_hoops_SPPIS;
			_hoops_ARPA *			_hoops_CAGRA;
			Vector *		_hoops_HCPCP;
			RGB *			_hoops_GICAA;
			float *			_hoops_PPCP;

			if (_hoops_HPAIS)
				_hoops_SPPIS = 0;
			else
				_hoops_SPPIS = 1;

			vi = tristrip->_hoops_AIHA + tristrip->total;
			fi = tristrip->face_indices + tristrip->total;
			_hoops_HCPCP = (tristrip->_hoops_ICHA ? tristrip->_hoops_ICHA + tristrip->point_count : null);
			_hoops_GICAA = (tristrip->_hoops_PCHA ? tristrip->_hoops_PCHA + tristrip->point_count : null);
			_hoops_CAGRA = (tristrip->_hoops_PRHH ? tristrip->_hoops_PRHH + _hoops_PGRPS : null);
			_hoops_PPCP = (tristrip->_hoops_HCHA ? tristrip->_hoops_HCHA + tristrip->point_count : null);

			if (BIT (polycylinder->flags, _hoops_RAAIS)) {
				tristrip->lengths[tristrip->_hoops_PHHA] = _hoops_HGII;
				tristrip->total += tristrip->lengths[tristrip->_hoops_PHHA];
				tristrip->_hoops_PHHA++;
				for (ii=0; ii<_hoops_HGII; ii++) {
					if ((ii & 1) == _hoops_SPPIS)
						*vi = tristrip->point_count + _hoops_HGII-1 - ii/2;
					else
						*vi = tristrip->point_count + ii/2;
					*fi = _hoops_PGRPS;
					if (tristrip->_hoops_PAGI)
						_hoops_RSAI (&tristrip->_hoops_PCHA[*vi], RGB, &tristrip->_hoops_PAGI[*fi]);
					vi++;
					fi++;
					if (_hoops_HCPCP)
						*_hoops_HCPCP++ = polycylinder->_hoops_ACCSA[0];
					if (_hoops_GICAA)
						*_hoops_GICAA++ = _hoops_PCHA[0];
					if (_hoops_PPCP)
						*_hoops_PPCP++ = _hoops_HCHA[0];
				}
				if (_hoops_CAGRA)
					*_hoops_CAGRA++ = _hoops_ARPA (polycylinder->_hoops_ACCSA[0], polycylinder->points[0]);
				_hoops_AIGA (&tristrip->points[0], _hoops_HGII, Point, &tristrip->points[tristrip->point_count]);
				tristrip->point_count += _hoops_HGII;
			}	

			if (BIT (polycylinder->flags, _hoops_AAAIS)) {
				int		shift = _hoops_HCRGR - _hoops_HGII;
				int		_hoops_GHPIS = polycylinder->point_count*_hoops_HGII - 1;
				tristrip->lengths[tristrip->_hoops_PHHA] = _hoops_HGII;
				tristrip->total += tristrip->lengths[tristrip->_hoops_PHHA];
				tristrip->_hoops_PHHA++;
				for (ii=0; ii<_hoops_HGII; ii++) {
					if ((ii & 1) == _hoops_SPPIS)
						*vi = tristrip->point_count + ii/2;
					else
						*vi = tristrip->point_count + _hoops_HGII-1 - ii/2;
					if (BIT (polycylinder->flags, _hoops_RAAIS))
						*fi = _hoops_PGRPS + 1;
					else
						*fi = _hoops_PGRPS;
					if (tristrip->_hoops_PAGI)
						_hoops_RSAI (&tristrip->_hoops_PCHA[*vi], RGB, &tristrip->_hoops_PAGI[*fi]);
					vi++;
					fi++;
					if (_hoops_HCPCP)
						*_hoops_HCPCP++ = polycylinder->_hoops_ACCSA[1];
					if (_hoops_GICAA)
						*_hoops_GICAA++ = _hoops_PCHA[_hoops_GHPIS];
					if (_hoops_PPCP)
						*_hoops_PPCP++ = _hoops_HCHA[_hoops_GHPIS];
				}
				if (_hoops_CAGRA)
					*_hoops_CAGRA++ = _hoops_ARPA (polycylinder->_hoops_ACCSA[1], polycylinder->points[polycylinder->point_count-1]);
				_hoops_AIGA (&tristrip->points[shift], _hoops_HGII, Point, &tristrip->points[tristrip->point_count]);
				tristrip->point_count += _hoops_HGII;
			}	
			if (tristrip->_hoops_PAGI)
				tristrip->_hoops_PCHA = null;
		}

		if (BIT (_hoops_RRGH->_hoops_CSA,
				 _hoops_GSRC & ~_hoops_AHGI) &&
			nr->_hoops_IHA->_hoops_CHA->_hoops_ARIR) {
			_hoops_HRAIS (nr, polycylinder, _hoops_HGII, tristrip, _hoops_IRAIS);
		}
		else {
			if (!_hoops_IRAIS &&
				!ANYBIT (_hoops_IHRSR, T_GENERIC_EDGES|T_INTERIOR_SILHOUETTE_EDGES) &&
				nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR == 1.0f &&
				BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_FACES) && 
				nr->_hoops_IRR->_hoops_GAHA != Display_List_SEGMENT) {
				_hoops_RRAIS (nr, polycylinder, _hoops_HGII, tristrip);
			}

			if (polycylinder->_hoops_SGHIR) {
				tristrip->_hoops_GAHA = polycylinder->_hoops_SGHIR;
				_hoops_PRRH (polycylinder->_hoops_SGHIR);
			}
			if (_hoops_CHAIS) {
				tristrip->_hoops_SRHA |= _hoops_GGIA;
				if (BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_FACES))
					_hoops_GAIGH (nr, tristrip);

				if (BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_EDGES)) {
					Polyedge *			_hoops_CHGPR = null;

					HD_Isoline_From_Tristrip (nr, tristrip);
					HD_Process_Isolines (dc, polycylinder, polycylinder->bounding, &_hoops_CHGPR, 0.001f);

					if (_hoops_CHGPR != null) {
						Polyedge *		_hoops_ACP = _hoops_CHGPR;
						Polyedge *		_hoops_RHPIS;

						do {
							_hoops_RHPIS = _hoops_ACP->next;

							if (_hoops_ACP->_hoops_HSAI > 1 && !BIT(_hoops_ACP->_hoops_CARI, _hoops_SARI) ||
								!nr->_hoops_ARA->_hoops_ACP._hoops_PCP &&
									(_hoops_ACP->_hoops_ICHA != null || _hoops_ACP->_hoops_RSHA != null)) {
								Polyedge *		_hoops_AHPIS;

								ALLOC (_hoops_AHPIS, Polyedge);
								_hoops_RSAI (_hoops_ACP, Polyedge, _hoops_AHPIS);
								_hoops_AHPIS->bounding.retain();
								_hoops_AHPIS->_hoops_RAHH = _hoops_CGCGP;
								_hoops_AHPIS->_hoops_GAHA = 0;
								_hoops_AHPIS->_hoops_SCGHR = _hoops_ACP;
								_hoops_CAHS (_hoops_ACP);
								_hoops_AHPIS->_hoops_SRHA |= DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS|_hoops_GAHH|DL_TEMPORARY_DATA;
								_hoops_AHPIS->_hoops_HSAI = 1;
								if (!nr->_hoops_ARA->_hoops_ACP._hoops_PCP) {
									_hoops_AHPIS->_hoops_ICHA = null;
									_hoops_AHPIS->_hoops_RSHA = null;
								}
								_hoops_ACP = _hoops_AHPIS;
							}
							else {
								_hoops_CAHS (_hoops_ACP);
							}

							_hoops_ACP->_hoops_GSCP = (Polyhedron *)polycylinder;
							_hoops_ACP->bounding = polycylinder->bounding;	
							_hoops_ACP->_hoops_GSAI = 0;

							nr = HD_New_Local_Edge_Rendition ((Polyhedron *)null, nr, inr, &_hoops_ACP->_hoops_PPGI);

							if (nr->_hoops_RHP->_hoops_CHA->_hoops_IRIR > 0 ||
								nr->_hoops_RHP->_hoops_CHA->_hoops_ARIR) {
								_hoops_AAIGH (nr, _hoops_ACP);
							}
							else
								dc->_hoops_GSGC |= (_hoops_ASRI|_hoops_RSRI);

							_hoops_ISAI (_hoops_ACP);
							if (_hoops_ACP->_hoops_HSAI == 0)
								HI_Free_Polyedge (_hoops_ACP);
						} while ((_hoops_ACP = _hoops_RHPIS) != null);

						HI_Free_Polyedge_List (_hoops_CHGPR);
					}
				}
			}
			else {
				tristrip->_hoops_SRHA &= ~_hoops_GGIA;
				_hoops_HPHCP (nr, tristrip);
			}
			if (_hoops_PAGI) {
				//_hoops_RPP _hoops_AICRR _hoops_HRGR _hoops_HGGC _hoops_ARRHP _hoops_CIAA _hoops_RH _hoops_CRHH, _hoops_RH _hoops_PIH _hoops_GGR _hoops_PHPIS
				//_hoops_CGH _hoops_HS _hoops_RPII _hoops_RIRRR _hoops_SGGR _hoops_HPP _hoops_HHPIS _hoops_HPP _hoops_RGR _hoops_PPSR
				ASSERT (tristrip->_hoops_HSAI == 1 || _hoops_PAGI != tristrip->_hoops_PAGI);
				FREE_ARRAY (_hoops_PAGI, tristrip->face_count, RGB);
			}
		}
	}
	if (_hoops_IHRSR) {
		if (polycylinder->_hoops_GRHIR) {
			polyedge->_hoops_GAHA = polycylinder->_hoops_GRHIR;
			_hoops_PRRH (polycylinder->_hoops_GRHIR);
		}
		_hoops_HIAIS(
			nr, polycylinder, 
			_hoops_IHRSR, _hoops_IIAIS, _hoops_CIAIS, _hoops_GHAIS, 
			_hoops_HGII, points, _hoops_PCHA, _hoops_HCHA, _hoops_PRHH, _hoops_AGHAR, polyedge);
	}

	if (_hoops_HCRGR+_hoops_HHCAP > _hoops_GGAPR(_hoops_HRIGA)) {
		FREE_ARRAY (points, _hoops_HCRGR+_hoops_HHCAP, Point);
		FREE_ARRAY (_hoops_ICHA, _hoops_HCRGR+_hoops_HHCAP, Vector);
		FREE_ARRAY (_hoops_PCHA, _hoops_HCRGR+_hoops_HHCAP, RGB);
		FREE_ARRAY (_hoops_HCHA, _hoops_HCRGR+_hoops_HHCAP, float);
		FREE_ARRAY (_hoops_PRHH, _hoops_PGRPS + 2, _hoops_ARPA);
		FREE_ARRAY (_hoops_AGHAR, _hoops_PGRPS + 2, int);
	}

	/* _hoops_RPP _hoops_GII _hoops_AIRI _hoops_HIGR _hoops_GGHP _hoops_SPIP, _hoops_SRAI _hoops_CAPR */
	{
		PolyCylinder alter *		_hoops_SRCIP = (PolyCylinder alter *)polycylinder;
		_hoops_GACR alter *		dl;

		if (tristrip->_hoops_GAHA) {
			dl = tristrip->_hoops_GAHA;
			if (dl != _hoops_SRCIP->_hoops_SGHIR) {
				dl->next = _hoops_SRCIP->_hoops_SGHIR;
				dl->backlink = &_hoops_SRCIP->_hoops_SGHIR;
				_hoops_SRCIP->_hoops_SGHIR = dl;
			}
			else {
				ASSERT (dl->_hoops_HIHI > 1);
				_hoops_HPRH (dl);
			}
			tristrip->_hoops_GAHA = null;
		}
		if (polyedge->_hoops_GAHA) {
			dl = polyedge->_hoops_GAHA;
			if (dl != _hoops_SRCIP->_hoops_GRHIR) {
				dl->next = _hoops_SRCIP->_hoops_GRHIR;
				dl->backlink = &_hoops_SRCIP->_hoops_GRHIR;
				_hoops_SRCIP->_hoops_GRHIR = polyedge->_hoops_GAHA;
			}
			else {
				ASSERT (dl->_hoops_HIHI > 1);
				_hoops_HPRH (dl);
			}
			polyedge->_hoops_GAHA = null;
		}
		_hoops_SRCIP->_hoops_SHSGP = _hoops_PSAIS;
	}

  _hoops_HPAGR:
	if (tristrip) {
		if (polycylinder->owner && polycylinder->owner->type == _hoops_ASIP)
			tristrip->_hoops_GSCP = (Geometry *)polycylinder->owner;
		if (_hoops_ISAI (tristrip) == 0)
			HI_Free_Tristrip (tristrip);
	}

	if (polyedge) {
		if (polycylinder->owner && polycylinder->owner->type == _hoops_ASIP)
			polyedge->_hoops_GSCP = (Geometry *)polycylinder->owner; 
		if (_hoops_ISAI (polyedge) == 0)
			HI_Free_Polyedge (polyedge);
	}

	if (dc->_hoops_CGHAR) {
		FREE_ARRAY_ALIGNED(dc->_hoops_CGHAR, dc->_hoops_ICACP, int, 16);
		dc->_hoops_ICACP = 0;
		dc->_hoops_CGHAR = null;
	}
#endif
}



GLOBAL_FUNCTION void HD_Std_3D_Cylinder (
	Net_Rendition const &		inr,
	Cylinder const *			cylinder) {
	Net_Rendition				nr = inr;
	PolyCylinder *				_hoops_HSPIR;

	/* _hoops_SAHR _hoops_ARAS _hoops_IRS _hoops_IHGP _hoops_ISPR _hoops_IH _hoops_HA.  _hoops_IHPIS 3D _hoops_CHPIS _hoops_GRS 
	   _hoops_IHSH _hoops_HPGR _hoops_RH _hoops_PGSI _hoops_GGR _hoops_RRI _hoops_AHSIR */
	if (!ANYBIT (nr->_hoops_SRA->_hoops_IPCI->mask, 
				 _hoops_PGRI | _hoops_IGAI))
		return;

	if (nr->_hoops_IRR->_hoops_GAHA == Display_List_GEOMETRY)
		nr.Modify()->_hoops_IRR.Modify()->_hoops_GAHA = Display_List_NONE;

	_hoops_HSPIR = HI_Cylinder_To_PolyCylinder (cylinder);
	HD_Std_3D_PolyCylinder (nr, _hoops_HSPIR);
	_hoops_HPRH (_hoops_HSPIR);
}


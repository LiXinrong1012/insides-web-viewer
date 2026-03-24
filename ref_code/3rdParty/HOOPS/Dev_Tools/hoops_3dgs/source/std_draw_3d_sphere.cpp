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
 * $Id: obf_tmp.txt 1.78 2010-10-06 19:15:52 jason Exp $
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

#ifndef _hoops_IAGHA
#  define _hoops_IAGHA 3.141592653589f
#endif




local Net_Rendition _hoops_HHPRC (
	Net_Rendition const & 		inr) {
	Net_Rendition				nr = inr;
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


/* _hoops_HGCR _hoops_RH _hoops_HISGR _hoops_PRGI _hoops_RIAIS _hoops_IIGR 72 */
local int _hoops_AIAIS (int input) {
	if (input <= 0) 
		return 0;
	else if (input <= 2) 
		return 2;
	else if (input <= 3) 
		return 3;
	else if (input <= 4) 
		return 4;
	else if (input <= 6) 
		return 6;
	else if (input <= 8) 
		return 8;
	else if (input <= 9) 
		return 9;
	else if (input <= 12) 
		return 12;
	else if (input <= 18) 
		return 18;
	else if (input <= 24) 
		return 24;
	else if (input <= 36) 
		return 36;
	else 
		return 72;
}


#define _hoops_PCAIS (_hoops_SSA|_hoops_IIRAP|_hoops_GGP|_hoops_GSRC)
#define _hoops_HCAIS (_hoops_GCP|_hoops_HIRAP|_hoops_RCP|_hoops_RGAC)
#define _hoops_ICAIS 0x8  /* _hoops_IRHS _hoops_IS _hoops_SHH _hoops_GIAH _hoops_HII _hoops_CCAIS */


#define _hoops_GIAHA 1024
GLOBAL_FUNCTION void HD_Std_3D_Sphere (
	Net_Rendition const &		inr,
	Sphere const *				sphere) {
	Net_Rendition				nr = inr;
	Display_Context const *		dc = nr->_hoops_SRA;
	int							i, j, _hoops_SSPAR=0, _hoops_SHPC, _hoops_HCGS, a, b;
	float 						_hoops_GSGPS;
	float 						_hoops_GPIAA, _hoops_RPIAA;
	float 						_hoops_HAIAA, _hoops_IAIAA;
	int 						_hoops_GIIRC, _hoops_RIIRC, _hoops_HAPAR;
	int 						point_count;
	Point						_hoops_PIAI[_hoops_GIAHA], *points, *p;
	Vector						_hoops_GRPCS[_hoops_GIAHA], *_hoops_ICHA, *_hoops_HCPCP;
	_hoops_ARPA						_hoops_RRPCS[_hoops_GIAHA], *_hoops_PRHH, *_hoops_CAGRA;
	int							_hoops_GGGCA[_hoops_GIAHA], *_hoops_AGHAR;
	int							*l, *vi, *fi;
	Tristrip *					tristrip = null;
	Polyedge *					polyedge = null;
	_hoops_ACHR					_hoops_IHRSR;
	bool						_hoops_IIAIS;
	bool						_hoops_ARPCS;
	_hoops_GRA const &	_hoops_RRA = nr->_hoops_ARA;
	float const 				*_hoops_GAIAA, *_hoops_CAIAA, *_hoops_AAIAA;
	float const 				*_hoops_RAIAA, *_hoops_SAIAA, *_hoops_PAIAA;
	int							_hoops_PRPCS, _hoops_HRPCS;

	if (!BIT(dc->flags, _hoops_HSAGR) &&
		!BIT (nr->transform_rendition->flags, _hoops_AIHS) &&
		BIT (nr->transform_rendition->_hoops_APH, Heur_Culling_VIEW_FRUSTUM)) {

		Test _hoops_ASIS = Test_DISJOINT;

		float	_hoops_RRIIH = _hoops_IAAA(nr->_hoops_SAIR->_hoops_SCIH.left - nr->_hoops_SAIR->_hoops_HHCAR.left, 0.0f);

		HD_Transform_And_Test_Simple_Sphere (nr, 1, &sphere->data, null, _hoops_RRIIH, 0.0f, &_hoops_ASIS, null, null);

		if (_hoops_ASIS == Test_DISJOINT)
			return;
	}

	Bounding _hoops_RCHS = Bounding::Create(sphere->data);

	if (nr->_hoops_IRR->_hoops_GAHA == Display_List_GEOMETRY)
		nr.Modify()->_hoops_IRR.Modify()->_hoops_GAHA = Display_List_NONE;

	if (sphere->data.radius == 0.0f) {
		_hoops_GIIRC = 0;
	}
	else if (_hoops_RRA->_hoops_PRSI.options & _hoops_HRSI) {
		if (_hoops_RRA->_hoops_PRSI._hoops_IISRP >= 0)
			_hoops_GIIRC = _hoops_RRA->_hoops_GAICA.sphere[_hoops_RRA->_hoops_PRSI._hoops_IISRP];
		else
			/* _hoops_AHPPR _hoops_GHSHA _hoops_IIGR _hoops_PRCCA _hoops_HARH _hoops_IPIH _hoops_AHIRC _hoops_GAR _hoops_PRCCA == _hoops_PSAP 
			 * _hoops_IH _hoops_CRCIA.	 _hoops_RHRPA _hoops_CHGC, _hoops_SGS _hoops_HRGR, _hoops_CCGR _hoops_SR _hoops_RCPS _hoops_GH _hoops_CCA _hoops_IRS 
			 * _hoops_IRGIR _hoops_RIIRA.  (_hoops_CISRP < 0) _hoops_AGSR _hoops_PHIRC _hoops_GRGR. */
			_hoops_GIIRC = _hoops_RRA->_hoops_GAICA.sphere[0];	 
	}
	else {
		_hoops_GIIRC = _hoops_RRA->_hoops_GAICA.sphere[0];
	}
	_hoops_RIIRC = _hoops_GIIRC/2;
	_hoops_GIIRC = _hoops_AIAIS(_hoops_GIIRC);
	_hoops_RIIRC = _hoops_AIAIS(_hoops_RIIRC);
	if (_hoops_RIIRC > 36)
		_hoops_RIIRC = 36;
	_hoops_HAPAR = _hoops_GIIRC * (_hoops_RIIRC+1);

	points = _hoops_PIAI;
	_hoops_ICHA = _hoops_GRPCS;
	_hoops_PRHH = _hoops_RRPCS;
	_hoops_AGHAR = _hoops_GGGCA;
	
	if (_hoops_GIIRC <= 0) {
		if (_hoops_GIIRC < 0)
			return;
		/* _hoops_HSPR _hoops_RRGR _hoops_RCAGR _hoops_HII _hoops_RGSSA */
		POOL_ZALLOC (polyedge, Polyedge, dc->memory_pool); 
		_hoops_ICAI(polyedge);

		polyedge->points = points;
		points[0] = points[1] = sphere->data.center;
		polyedge->point_count = 2;
		polyedge->total = 2;
		polyedge->_hoops_SPHA = 1;

		polyedge->_hoops_PHHA = 1;

		polyedge->bounding = _hoops_RCHS;
	
		polyedge->lengths_allocated = 1;
		polyedge->_hoops_IPII = 2;
		polyedge->_hoops_CPII = 2;
		POOL_ALLOC_ARRAY_CACHED(polyedge->lengths, polyedge->lengths_allocated, int, dc->memory_pool);
		POOL_ALLOC_ARRAY_CACHED(polyedge->_hoops_AIHA, polyedge->_hoops_IPII, int, dc->memory_pool);
		POOL_ALLOC_ARRAY_CACHED(polyedge->_hoops_SPII, polyedge->_hoops_CPII, int, dc->memory_pool);
		polyedge->_hoops_RAHH |= _hoops_AAHH;

		polyedge->_hoops_SRHA = _hoops_GAHH|DL_TEMPORARY_DATA;

		polyedge->lengths[0] = 2;
		polyedge->_hoops_AIHA[0] = 0;
		polyedge->_hoops_SPII[0] = 0;
		polyedge->_hoops_AIHA[1] = 1;
		polyedge->_hoops_SPII[1] = 0;

		_hoops_RAIGH (nr, polyedge);

		goto _hoops_RCCSR;
	}

	if (_hoops_HAPAR > _hoops_GIAHA) {
		POOL_ALLOC_ARRAY_CACHED(points, _hoops_HAPAR, Point, dc->memory_pool);
		POOL_ALLOC_ARRAY_CACHED(_hoops_ICHA, _hoops_HAPAR, Vector, dc->memory_pool);
		POOL_ALLOC_ARRAY_CACHED(_hoops_PRHH, _hoops_HAPAR, _hoops_ARPA, dc->memory_pool);
		POOL_ALLOC_ARRAY_CACHED(_hoops_AGHAR, _hoops_HAPAR, int, dc->memory_pool);
	}

	POOL_ZALLOC (tristrip, Tristrip, dc->memory_pool);
	_hoops_ICAI (tristrip);

	POOL_ZALLOC (tristrip->_hoops_GSSH, _hoops_RRCC, dc->memory_pool);
	_hoops_ICAI (tristrip->_hoops_GSSH);

	tristrip->lengths_allocated=_hoops_HAPAR;
	tristrip->_hoops_IPII=4*_hoops_HAPAR;
	tristrip->_hoops_SGAHR=4*_hoops_HAPAR;

	tristrip->_hoops_GSCP = (Geometry*)sphere;
	tristrip->bounding = _hoops_RCHS;

	POOL_ALLOC_ARRAY_CACHED(tristrip->lengths, tristrip->lengths_allocated, int, dc->memory_pool);
	POOL_ALLOC_ARRAY_CACHED(tristrip->_hoops_AIHA, tristrip->_hoops_IPII, int, dc->memory_pool);
	POOL_ALLOC_ARRAY_CACHED(tristrip->face_indices, tristrip->_hoops_SGAHR, int, dc->memory_pool);
	tristrip->_hoops_RAHH |= _hoops_AAHH;

	_hoops_GAIAA = HI_Get_Sin72_Lookup();
	_hoops_RAIAA = HI_Get_Cos72_Lookup();

	_hoops_PRPCS = 72/_hoops_GIIRC;
	_hoops_HRPCS = 72/(_hoops_RIIRC*2);
	p = points;
	_hoops_HCPCP = _hoops_ICHA;
	if (sphere->_hoops_CSPIR) {
		_hoops_AAIAA = _hoops_GAIAA;
		_hoops_PAIAA = _hoops_RAIAA;
		for (j = 0; j < (_hoops_RIIRC+1); j++) {
			_hoops_HAIAA = *_hoops_AAIAA;
			_hoops_IAIAA = *_hoops_PAIAA;
			_hoops_CAIAA = _hoops_GAIAA;
			_hoops_SAIAA = _hoops_RAIAA;
			for (i = 0; i < _hoops_GIIRC; i++) {
				_hoops_GPIAA = *_hoops_CAIAA;
				_hoops_RPIAA = *_hoops_SAIAA;
				_hoops_GSGPS = _hoops_HAIAA * _hoops_RPIAA;
				_hoops_HCPCP->x = _hoops_GSGPS * sphere->_hoops_CSPIR[0].x;
				_hoops_HCPCP->y = _hoops_GSGPS * sphere->_hoops_CSPIR[0].y;
				_hoops_HCPCP->z = _hoops_GSGPS * sphere->_hoops_CSPIR[0].z;
				_hoops_GSGPS = _hoops_IAIAA;
				_hoops_HCPCP->x += _hoops_GSGPS * sphere->_hoops_CSPIR[1].x;
				_hoops_HCPCP->y += _hoops_GSGPS * sphere->_hoops_CSPIR[1].y;
				_hoops_HCPCP->z += _hoops_GSGPS * sphere->_hoops_CSPIR[1].z;
				_hoops_GSGPS = _hoops_HAIAA * _hoops_GPIAA;
				_hoops_HCPCP->x += _hoops_GSGPS * sphere->_hoops_CSPIR[2].x;
				_hoops_HCPCP->y += _hoops_GSGPS * sphere->_hoops_CSPIR[2].y;
				_hoops_HCPCP->z += _hoops_GSGPS * sphere->_hoops_CSPIR[2].z;
				p->x = sphere->data.center.x + _hoops_HCPCP->x;
				p->y = sphere->data.center.y + _hoops_HCPCP->y;
				p->z = sphere->data.center.z + _hoops_HCPCP->z;
				_hoops_HCPCP++;
				p++;
				_hoops_CAIAA += _hoops_PRPCS;
				_hoops_SAIAA += _hoops_PRPCS;
			}
			_hoops_AAIAA += _hoops_HRPCS;
			_hoops_PAIAA += _hoops_HRPCS;
		}

		if (sphere->data.radius != 1.0f) {
			HI_Normalize_Vectors ((_hoops_RIIRC+1) * _hoops_GIIRC, _hoops_ICHA);
		}
	}
	else {
		_hoops_AAIAA = _hoops_GAIAA;
		_hoops_PAIAA = _hoops_RAIAA;
		for (j = 0; j < (_hoops_RIIRC+1); j++) {
			_hoops_HAIAA = *_hoops_AAIAA;
			_hoops_IAIAA = *_hoops_PAIAA;
			_hoops_CAIAA = _hoops_GAIAA;
			_hoops_SAIAA = _hoops_RAIAA;
			for (i = 0; i < _hoops_GIIRC; i++) {
				_hoops_GPIAA = *_hoops_CAIAA;
				_hoops_RPIAA = *_hoops_SAIAA;
				_hoops_HCPCP->x = _hoops_HAIAA * _hoops_RPIAA;
				_hoops_HCPCP->y = _hoops_IAIAA;
				_hoops_HCPCP->z = _hoops_HAIAA * _hoops_GPIAA;
				p->x = sphere->data.center.x + (_hoops_HCPCP->x * sphere->data.radius);
				p->y = sphere->data.center.y + (_hoops_HCPCP->y * sphere->data.radius);
				p->z = sphere->data.center.z + (_hoops_HCPCP->z * sphere->data.radius);
				_hoops_HCPCP++;
				p++;
				_hoops_CAIAA += _hoops_PRPCS;
				_hoops_SAIAA += _hoops_PRPCS;
			}
			_hoops_AAIAA += _hoops_HRPCS;
			_hoops_PAIAA += _hoops_HRPCS;
		}
	}
	point_count = p - points; 

	_hoops_IHRSR = nr->_hoops_RGP & _hoops_SRHGP;
	_hoops_IIAIS = BIT (_hoops_IHRSR, T_INTERIOR_SILHOUETTE_EDGES) &&
					   !BIT (_hoops_IHRSR, T_GENERIC_EDGES);

	if (nr->_hoops_RGP & T_FACES) {
		_hoops_ARPCS = false;

		if (!BIT (nr->transform_rendition->flags, _hoops_GRHH) ||
			!BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES) ||
			nr->_hoops_IHA->_hoops_AGP == null) {
			/*-- _hoops_GRAPR _hoops_CRIRC --*/
		}
		else if (!ANYBIT (nr->_hoops_IRR->_hoops_CSA,
						  _hoops_IIRAP | _hoops_GGP | _hoops_SSA)) {
			/*--- _hoops_CRPIS _hoops_CRIRC ---*/
			tristrip->_hoops_PRHH = _hoops_PRHH;
		}
		else {
			/*--- _hoops_SRPIS _hoops_CRIRC ---*/
			_hoops_ARPCS = true;
		}

		/* _hoops_RAGCC _hoops_SIA _hoops_GCA _hoops_GPHA _hoops_ASGA _hoops_IS _hoops_CAHP _hoops_RH _hoops_IRPCS */
		if ( nr->_hoops_IHA->_hoops_CHA->texture[_hoops_RIA] != null )
			_hoops_ARPCS = true;

		if ( _hoops_ARPCS ) 
			tristrip->_hoops_ICHA = _hoops_ICHA;

	}

	if (nr->_hoops_RGP & T_FACES || _hoops_IIAIS) {
		if (tristrip->_hoops_PRHH || _hoops_IIAIS) {
			_hoops_CAGRA = _hoops_PRHH;
			_hoops_HCGS = 0;
			_hoops_SSPAR = 0;
			if (sphere->_hoops_CSPIR) {
				/* _hoops_HSP _hoops_ASGA _hoops_IH _hoops_CRCIA _hoops_PRCS _hoops_HHAA _hoops_PPRRR _hoops_GGR _hoops_GAPA _hoops_RH _hoops_GPHA _hoops_ASGA */
				_hoops_AAIAA = _hoops_GAIAA + _hoops_HRPCS/2;
				_hoops_PAIAA = _hoops_RAIAA + _hoops_HRPCS/2;
				for (j = 0; j < _hoops_RIIRC; j++) {
					_hoops_HAIAA = *_hoops_AAIAA;
					_hoops_IAIAA = *_hoops_PAIAA;
					/* _hoops_HSP _hoops_ASGA _hoops_IH _hoops_CRCIA _hoops_PRCS _hoops_HHAA _hoops_PPRRR _hoops_GGR _hoops_GAPA _hoops_RH _hoops_GPHA _hoops_ASGA */
					_hoops_CAIAA = _hoops_GAIAA + _hoops_PRPCS/2;
					_hoops_SAIAA = _hoops_RAIAA + _hoops_PRPCS/2;
					for (i = 0; i < _hoops_GIIRC; i++) {
						_hoops_GPIAA = *_hoops_CAIAA;
						_hoops_RPIAA = *_hoops_SAIAA;
						_hoops_GSGPS = _hoops_HAIAA * _hoops_RPIAA;
						_hoops_CAGRA->a = _hoops_GSGPS * sphere->_hoops_CSPIR[0].x;
						_hoops_CAGRA->b = _hoops_GSGPS * sphere->_hoops_CSPIR[0].y;
						_hoops_CAGRA->c = _hoops_GSGPS * sphere->_hoops_CSPIR[0].z;
						_hoops_GSGPS = _hoops_IAIAA;
						_hoops_CAGRA->a += _hoops_GSGPS * sphere->_hoops_CSPIR[1].x;
						_hoops_CAGRA->b += _hoops_GSGPS * sphere->_hoops_CSPIR[1].y;
						_hoops_CAGRA->c += _hoops_GSGPS * sphere->_hoops_CSPIR[1].z;
						_hoops_GSGPS = _hoops_HAIAA * _hoops_GPIAA;
						_hoops_CAGRA->a += _hoops_GSGPS * sphere->_hoops_CSPIR[2].x;
						_hoops_CAGRA->b += _hoops_GSGPS * sphere->_hoops_CSPIR[2].y;
						_hoops_CAGRA->c += _hoops_GSGPS * sphere->_hoops_CSPIR[2].z;
						_hoops_CAGRA->d = -(_hoops_CAGRA->a * points[_hoops_HCGS].x +
								  _hoops_CAGRA->b * points[_hoops_HCGS].y +
								  _hoops_CAGRA->c * points[_hoops_HCGS].z);
						_hoops_CAGRA++;
						_hoops_HCGS++;
						_hoops_CAIAA += _hoops_PRPCS;
						_hoops_SAIAA += _hoops_PRPCS;
					}
					_hoops_AAIAA += _hoops_HRPCS;
					_hoops_PAIAA += _hoops_HRPCS;
				}
			}
			else {
				_hoops_AAIAA = _hoops_GAIAA + _hoops_HRPCS/2;
				_hoops_PAIAA = _hoops_RAIAA + _hoops_HRPCS/2;
				for (j = 0; j < _hoops_RIIRC; j++) {
					_hoops_HAIAA = *_hoops_AAIAA;
					_hoops_IAIAA = *_hoops_PAIAA;
					_hoops_CAIAA = _hoops_GAIAA + _hoops_PRPCS/2;
					_hoops_SAIAA = _hoops_RAIAA + _hoops_PRPCS/2;
					for (i = 0; i < _hoops_GIIRC; i++) {
						_hoops_GPIAA = *_hoops_CAIAA;
						_hoops_RPIAA = *_hoops_SAIAA;
						_hoops_CAGRA->a = _hoops_HAIAA * _hoops_RPIAA;
						_hoops_CAGRA->b = _hoops_IAIAA;
						_hoops_CAGRA->c = _hoops_HAIAA * _hoops_GPIAA;
						_hoops_CAGRA->d = -(_hoops_CAGRA->a * points[_hoops_HCGS].x +
								  _hoops_CAGRA->b * points[_hoops_HCGS].y +
								  _hoops_CAGRA->c * points[_hoops_HCGS].z);
						_hoops_CAGRA++;
						_hoops_HCGS++;
						_hoops_CAIAA += _hoops_PRPCS;
						_hoops_SAIAA += _hoops_PRPCS;
					}
					_hoops_AAIAA += _hoops_HRPCS;
					_hoops_PAIAA += _hoops_HRPCS;
				}
			}
		}
		l = tristrip->lengths;
		vi = tristrip->_hoops_AIHA;
		if (BIT (nr->transform_rendition->heuristics, _hoops_GPSA)) {
			a = 0;
			b = 1;
		}
		else {
			a = 1;
			b = 0;
		}

		if (tristrip->face_indices) {
			fi = tristrip->face_indices;
			for (j = 0; j < _hoops_RIIRC; j++) {
				*l++ = 2*_hoops_GIIRC + 2;
				*vi++ = (j+b)*_hoops_GIIRC;
				*vi++ = (j+a)*_hoops_GIIRC;
				*fi++ = _hoops_SSPAR;
				*fi++ = _hoops_SSPAR; /* _hoops_PSP _hoops_GPISR: 1_hoops_ICPC 4 _hoops_GIHA _hoops_IIGR _hoops_RH _hoops_CRHH _hoops_CHR _hoops_HCR _hoops_ARIP _hoops_IIGR _hoops_SRS _hoops_HSP */
				for (i = 1; i < _hoops_GIIRC; i++) {
					*vi++ = (j+b)*_hoops_GIIRC + i;
					*vi++ = (j+a)*_hoops_GIIRC + i;
					*fi++ = _hoops_SSPAR;
					*fi++ = _hoops_SSPAR++;
				}
				*vi++ = (j+b)*_hoops_GIIRC;
				*vi++ = (j+a)*_hoops_GIIRC;
				*fi++ = _hoops_SSPAR;
				*fi++ = _hoops_SSPAR++;
			}
		}
		else {
			for (j = 0; j < _hoops_RIIRC; j++) {
				*l++ = 2*_hoops_GIIRC + 2;
				*vi++ = (j+b)*_hoops_GIIRC;
				*vi++ = (j+a)*_hoops_GIIRC;
				for (i = 1; i < _hoops_GIIRC; i++) {
					*vi++ = (j+b)*_hoops_GIIRC + i;
					*vi++ = (j+a)*_hoops_GIIRC + i;
				}
				*vi++ = (j+b)*_hoops_GIIRC;
				*vi++ = (j+a)*_hoops_GIIRC;
			}
		}
		tristrip->face_count = _hoops_GIIRC*_hoops_RIIRC;
		if (tristrip->face_indices == null)
			tristrip->face_count *= 2;
		tristrip->total = vi - tristrip->_hoops_AIHA;
		tristrip->_hoops_PHHA = l - tristrip->lengths;
	}

	if (nr->_hoops_RGP & T_FACES) {
		if (nr->_hoops_CPP->_hoops_PRH.style == _hoops_GCPI &&
			nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR < 1.0f)
			nr = _hoops_HHPRC (nr);

		tristrip->point_count = point_count;
		tristrip->points = points;
		tristrip->_hoops_SRHA =_hoops_GAHH|DL_TEMPORARY_DATA;
		if (BIT (nr->_hoops_PSGI, T_FACES))
			tristrip->_hoops_SRHA |= DL_HAS_TRANSPARENCY;
		tristrip->_hoops_GSAI = nr->_hoops_IRR->_hoops_CSA & _hoops_PCAIS;
		_hoops_HPHCP (nr, tristrip);
	}

	if (_hoops_IHRSR) {
		POOL_ZALLOC(polyedge, Polyedge, dc->memory_pool); 
		_hoops_ICAI(polyedge);

		polyedge->lengths_allocated=_hoops_HAPAR;
		polyedge->_hoops_IPII=4*_hoops_HAPAR;
		polyedge->_hoops_CPII=4*_hoops_HAPAR;

		polyedge->_hoops_GSCP = (Geometry*)sphere;

		POOL_ALLOC_ARRAY_CACHED(polyedge->lengths, polyedge->lengths_allocated, int, dc->memory_pool);
		POOL_ALLOC_ARRAY_CACHED(polyedge->_hoops_AIHA, polyedge->_hoops_IPII, int, dc->memory_pool);
		POOL_ALLOC_ARRAY_CACHED(polyedge->_hoops_SPII, polyedge->_hoops_CPII, int, dc->memory_pool);
		polyedge->_hoops_RAHH |= _hoops_AAHH;

		polyedge->_hoops_SRHA = _hoops_GAHH|DL_TEMPORARY_DATA;
		if (BIT (nr->_hoops_PSGI, T_EDGES))
			polyedge->_hoops_SRHA |= DL_HAS_TRANSPARENCY;
		polyedge->_hoops_GSAI = nr->_hoops_IRR->_hoops_CSA & _hoops_HCAIS;
		polyedge->points = points;
		polyedge->point_count = point_count;

		polyedge->bounding = _hoops_RCHS;

		if (!BIT (nr->transform_rendition->flags, _hoops_GRHH) ||
			!BIT (nr->_hoops_RGP, T_LIGHTS_FOR_EDGES) ||
			nr->_hoops_RHP->_hoops_AGP == null) {
			/*-- _hoops_GRAPR _hoops_CRIRC --*/
		}
		else if (!ANYBIT (nr->_hoops_IRR->_hoops_CSA,
						  _hoops_HIRAP | _hoops_RCP | _hoops_GCP)) {
			/*--- _hoops_CRPIS _hoops_CRIRC ---*/
			/* _hoops_ACRI._hoops_GAPIS = _hoops_GAPIS; */
		}
		else {
			/*--- _hoops_SRPIS _hoops_CRIRC ---*/
			polyedge->_hoops_ICHA = _hoops_ICHA;
		}

		/* _hoops_RAGCC _hoops_SIA _hoops_GCA _hoops_GPHA _hoops_ASGA _hoops_IS _hoops_CAHP _hoops_RH _hoops_IRPCS */
		if ( nr->_hoops_IHA->_hoops_CHA->texture[_hoops_RIA] )
			polyedge->_hoops_ICHA = _hoops_ICHA;

		if (_hoops_IIAIS) {
			_hoops_RPRA const *		_hoops_CRIPA;
			int						_hoops_PIGIC, _hoops_GPCPA, left, right;

			_hoops_CRIPA = nr->transform_rendition->matrix->_hoops_PPRA()->data.elements;

			for (i = 0; i < tristrip->face_count; i++) {
				/* _hoops_HIHP _hoops_PPR _hoops_RPGP _hoops_RH _hoops_IPPA */
				if (_hoops_CRIPA[2][0] * _hoops_PRHH[i].a +
					_hoops_CRIPA[2][1] * _hoops_PRHH[i].b +
					_hoops_CRIPA[2][2] * _hoops_PRHH[i].c +
					_hoops_CRIPA[2][3] * _hoops_PRHH[i].d < 0.0f) {
					_hoops_AGHAR[i] = _hoops_AARCA;
				}
				else {
					_hoops_AGHAR[i] = _hoops_HARCA;
				}
			}
			l = polyedge->lengths;
			vi = polyedge->_hoops_AIHA;
			fi = polyedge->_hoops_SPII;
			_hoops_SHPC = 0;
			/* _hoops_CRPCS */
			for (j = 1; j < _hoops_RIIRC; j++) {
				for (i = 0; i < _hoops_GIIRC; i++) {
					_hoops_PIGIC = j*_hoops_GIIRC + i;
					_hoops_GPCPA = (j-1)*_hoops_GIIRC + i;
					if (_hoops_AGHAR[_hoops_PIGIC] != _hoops_AGHAR[_hoops_GPCPA]) {
						*l++ = 2;
						*vi++ = j*_hoops_GIIRC + i;
						*vi++ = j*_hoops_GIIRC + (i+1)%_hoops_GIIRC;
						*fi++ = _hoops_SHPC;
						*fi++ = _hoops_SHPC++;
					}
				}
			}
			/* _hoops_SRPCS */
			for (i = 0; i < _hoops_GIIRC; i++) {
				for (j = 0; j < _hoops_RIIRC; j++) {
					left = j*_hoops_GIIRC + i;
					right = j*_hoops_GIIRC + (i+1)%_hoops_GIIRC;
					if (_hoops_AGHAR[left] != _hoops_AGHAR[right]) {
						*l++ = 2;
						*vi++ = j*_hoops_GIIRC + (i+1)%_hoops_GIIRC;
						*vi++ = (j+1)*_hoops_GIIRC + (i+1)%_hoops_GIIRC;
						*fi++ = _hoops_SHPC;
						*fi++ = _hoops_SHPC++;
					}
				}
			}
			polyedge->total = vi - polyedge->_hoops_AIHA;
			polyedge->_hoops_PHHA = l - polyedge->lengths;
			polyedge->_hoops_SPHA = polyedge->_hoops_PHHA;
		}
		else {
			l = polyedge->lengths;
			vi = polyedge->_hoops_AIHA;
			fi = polyedge->_hoops_SPII;
			_hoops_SHPC = 0;
			/* _hoops_CRPCS */
			for (j = 1; j < _hoops_RIIRC; j++) {
				*l++ = _hoops_GIIRC+1;
				*fi++ = _hoops_SHPC;
				for (i = 0; i < _hoops_GIIRC; i++) {
					*vi++ = j*_hoops_GIIRC + i;
					*fi++ = _hoops_SHPC++;
				}
				*vi++ = j*_hoops_GIIRC;
			}
			/* _hoops_SRPCS */
			for (i = 0; i < _hoops_GIIRC; i++) {
				*l++ = _hoops_RIIRC+1;
				*fi++ = _hoops_SHPC;
				for (j = 0; j < _hoops_RIIRC+1; j++) {
					*fi++ = _hoops_SHPC++;
					*vi++ = j*_hoops_GIIRC + i;
				}
			}
			polyedge->total = vi - polyedge->_hoops_AIHA;
			polyedge->_hoops_PHHA = l - polyedge->lengths;
			polyedge->_hoops_SPHA = _hoops_SHPC;
		}

		_hoops_RAIGH (nr, polyedge);
	}

	if (_hoops_HAPAR > _hoops_GIAHA) {
		FREE_ARRAY(points, _hoops_HAPAR, Point);
		FREE_ARRAY(_hoops_ICHA, _hoops_HAPAR, Vector);
		FREE_ARRAY(_hoops_PRHH, _hoops_HAPAR, _hoops_ARPA);
		FREE_ARRAY(_hoops_AGHAR, _hoops_HAPAR, int);
	}

_hoops_RCCSR:
	if (tristrip && _hoops_ISAI (tristrip) == 0)
		HI_Free_Tristrip (tristrip);

	if (polyedge && _hoops_ISAI (polyedge) == 0)
		HI_Free_Polyedge (polyedge);
}

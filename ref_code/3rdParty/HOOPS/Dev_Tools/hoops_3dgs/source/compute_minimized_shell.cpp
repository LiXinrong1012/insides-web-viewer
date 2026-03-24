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
 * $Id: obf_tmp.txt 1.170 2010-12-06 22:05:41 jason Exp $
 */

#include "hoops.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "database.h"
#include "hpserror.h"
#include "phedron.h"
#include "adt.h"
#include "lod.h"



struct _hoops_GSSPA {
	int		indices[2];
	float	_hoops_RPIS[6][2];
	float	weight[6];
	int		_hoops_PPIS;
};


typedef VHeap<_hoops_GSSPA *,float, true, false> _hoops_RSSPA;



GLOBAL_FUNCTION void HI_Median_Cut (
	_hoops_AIGPR *	_hoops_RIGC,
	int						in_count,
	Point const *			in_points,
	RGB const *				_hoops_ASSPA,
	int						_hoops_PSSPA,
	Point alter *			out_points,
	RGB alter *				_hoops_HSSPA,
	int alter *				mapping) 
{

	int						_hoops_HAHC = in_count;
	int						dimensions = 3;
	float *					data;
	float *					_hoops_ISSPA;
	int *					indices;
	_hoops_GSSPA *			_hoops_CSSPA;
	int						i;
	int						_hoops_PPIS;
	int						_hoops_SSSPA;

	_hoops_RSSPA *	_hoops_GGGHA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_RSSPA)(_hoops_RIGC->memory_pool);

	if (_hoops_ASSPA != null)
		dimensions = 6;

	/* _hoops_ARP _hoops_GH _hoops_SRS _hoops_AHCRR _hoops_HII _hoops_CIIA _hoops_PIH */
	ALLOC (_hoops_CSSPA, _hoops_GSSPA);
	ZERO_STRUCT (_hoops_CSSPA, _hoops_GSSPA);
	_hoops_CSSPA->indices[0] = 0;
	_hoops_CSSPA->indices[1] = in_count - 1;
	for (i=0; i<6; i++) {
		_hoops_CSSPA->_hoops_RPIS[i][0] =  MAX_FLOAT;
		_hoops_CSSPA->_hoops_RPIS[i][1] = -MAX_FLOAT;
		_hoops_CSSPA->weight[i] = 1.0f;
	}

	ALLOC_ARRAY (indices, in_count, int);
	for (i=0; i<in_count; i++)
		indices[i] = i;

	ALLOC_ARRAY (data, dimensions*in_count, float);
	_hoops_ISSPA = data;

	while (in_count-- > 0) {
		_hoops_ISSPA[0] = in_points->x;
		_hoops_ISSPA[1] = in_points->y;
		_hoops_ISSPA[2] = in_points->z;
		++in_points;
		if (_hoops_ASSPA != null) {
			_hoops_ISSPA[3] = _hoops_ASSPA->red;
			_hoops_ISSPA[4] = _hoops_ASSPA->green;
			_hoops_ISSPA[5] = _hoops_ASSPA->blue;
			++_hoops_ASSPA;
		}

		for (i=0; i<dimensions; i++) {
			if (_hoops_ISSPA[i] < _hoops_CSSPA->_hoops_RPIS[i][0])
				_hoops_CSSPA->_hoops_RPIS[i][0] = _hoops_ISSPA[i];
			if (_hoops_ISSPA[i] > _hoops_CSSPA->_hoops_RPIS[i][1])
				_hoops_CSSPA->_hoops_RPIS[i][1] = _hoops_ISSPA[i];
		}

		_hoops_ISSPA += dimensions;
	}

	_hoops_PPIS = 0;
	for (i=1; i<3; i++) {
		if (_hoops_CSSPA->_hoops_RPIS[i][1] - _hoops_CSSPA->_hoops_RPIS[i][0] >
			_hoops_CSSPA->_hoops_RPIS[_hoops_PPIS][1] - _hoops_CSSPA->_hoops_RPIS[_hoops_PPIS][0])
			_hoops_PPIS = i;
	}
	_hoops_CSSPA->_hoops_PPIS = _hoops_PPIS;

	if (_hoops_ASSPA != null) {
		_hoops_CSSPA->weight[3] =
			_hoops_CSSPA->weight[4] =
				_hoops_CSSPA->weight[5] = 0.5f * (_hoops_CSSPA->_hoops_RPIS[_hoops_PPIS][1] -
												   _hoops_CSSPA->_hoops_RPIS[_hoops_PPIS][0]);
	}

	_hoops_SSSPA = 1;

	_hoops_GGGHA->Push(_hoops_CSSPA, 
			_hoops_CSSPA->_hoops_RPIS[_hoops_CSSPA->_hoops_PPIS][1] -
			_hoops_CSSPA->_hoops_RPIS[_hoops_CSSPA->_hoops_PPIS][0]);

	while (_hoops_SSSPA < _hoops_PSSPA) {
		_hoops_GSSPA *			_hoops_RGGHA;
		float					_hoops_SPGIR;
		int						j;

		/* _hoops_AGGHA _hoops_PGGHA _hoops_PSAP _hoops_SCIA _hoops_IIGR _hoops_SIHPA */
		_hoops_GGGHA->Pop(&_hoops_CSSPA);

		ALLOC (_hoops_RGGHA, _hoops_GSSPA);
		*_hoops_RGGHA = *_hoops_CSSPA;

		i = _hoops_CSSPA->indices[0];
		j = _hoops_CSSPA->indices[1];
		_hoops_PPIS = _hoops_CSSPA->_hoops_PPIS;
		_hoops_SPGIR = 0.5f * (_hoops_CSSPA->_hoops_RPIS[_hoops_PPIS][0] + _hoops_CSSPA->_hoops_RPIS[_hoops_CSSPA->_hoops_PPIS][1]);

		while (i < j) {
			while (i < j && data[i*dimensions+_hoops_PPIS] < _hoops_SPGIR) i++;
			while (i < j && data[j*dimensions+_hoops_PPIS] > _hoops_SPGIR) j--;
			if (i < j) {
				float			tmp[6];
				int				_hoops_HGGHA;

				_hoops_AIGA (&data[dimensions*i], dimensions, float, tmp);
				_hoops_AIGA (&data[dimensions*j], dimensions, float, &data[dimensions*i]);
				_hoops_AIGA (tmp, dimensions, float, &data[dimensions*j]);

				_hoops_HGGHA = indices[i];
				indices[i] = indices[j];
				indices[j] = _hoops_HGGHA;

				i++;
				j--;
			}
		}
		if (i == j) {
			if (i - _hoops_CSSPA->indices[0] > _hoops_CSSPA->indices[1] - j) {
				while (i > 0 &&
						data[i*dimensions+_hoops_PPIS] == data[j*dimensions+_hoops_PPIS])
					i--;
				j = i+1;
			}
			else {
				while (j < _hoops_CSSPA->indices[1] &&
						data[i*dimensions+_hoops_PPIS] == data[j*dimensions+_hoops_PPIS])
					j++;
				i = j-1;
			}
		}
		_hoops_CSSPA->indices[0] = j;	/* _hoops_PHPA _hoops_IGGHA */
		_hoops_RGGHA->indices[1] = i;		/* _hoops_GSSC _hoops_IGGHA */

		while (_hoops_CSSPA != null) {
			_hoops_ISSPA = &data[dimensions * _hoops_CSSPA->indices[0]];

			for (i=0; i<dimensions; i++)
				_hoops_CSSPA->_hoops_RPIS[i][0] = _hoops_CSSPA->_hoops_RPIS[i][1] = _hoops_ISSPA[i];

			for (j=_hoops_CSSPA->indices[0]; j<=_hoops_CSSPA->indices[1]; j++) {
				for (i=0; i<dimensions; i++) {
					if (_hoops_ISSPA[i] < _hoops_CSSPA->_hoops_RPIS[i][0])
						_hoops_CSSPA->_hoops_RPIS[i][0] = _hoops_ISSPA[i];
					else if (_hoops_ISSPA[i] > _hoops_CSSPA->_hoops_RPIS[i][1])
						_hoops_CSSPA->_hoops_RPIS[i][1] = _hoops_ISSPA[i];
				}

				_hoops_ISSPA += dimensions;
			}

			_hoops_PPIS = 0;
			for (i=1; i<dimensions; i++) {
				if ((_hoops_CSSPA->_hoops_RPIS[i][1] - _hoops_CSSPA->_hoops_RPIS[i][0]) * _hoops_CSSPA->weight[i] >
					(_hoops_CSSPA->_hoops_RPIS[_hoops_PPIS][1] - _hoops_CSSPA->_hoops_RPIS[_hoops_PPIS][0]) * _hoops_CSSPA->weight[_hoops_PPIS])
					_hoops_PPIS = i;
			}
			_hoops_CSSPA->_hoops_PPIS = _hoops_PPIS;

			/* _hoops_AISI _hoops_GRR _hoops_PGGHA _hoops_GPP _hoops_SIHPA */
			_hoops_GGGHA->Push(_hoops_CSSPA, 
				_hoops_CSSPA->_hoops_RPIS[_hoops_CSSPA->_hoops_PPIS][1] -
				_hoops_CSSPA->_hoops_RPIS[_hoops_CSSPA->_hoops_PPIS][0]);

			_hoops_CSSPA = _hoops_RGGHA;
			_hoops_RGGHA = null;
		}

		++_hoops_SSSPA;
	}

	/* _hoops_SICR _hoops_HACH _hoops_RGCRA _hoops_CRGR _hoops_CGGHA _hoops_IIPR _hoops_PIH */
	i = 0;	/* _hoops_SGGHA _hoops_CIHA _hoops_IIGR _hoops_CCAH _hoops_IIPR _hoops_PPSR */
	while (_hoops_GGGHA->Pop(&_hoops_CSSPA)) {
		/* _hoops_SAHR _hoops_GRP _hoops_AASHR _hoops_ARI, _hoops_HHS _hoops_AA _hoops_IRS _hoops_ISCRA _hoops_AASHR _hoops_PAR _hoops_GRGHA _hoops_IIGR _hoops_RH _hoops_RSSA _hoops_GGR _hoops_RH _hoops_AHCRR */
		if (out_points != null) {
			out_points->x = 0.5f * (_hoops_CSSPA->_hoops_RPIS[0][0] + _hoops_CSSPA->_hoops_RPIS[0][1]);
			out_points->y = 0.5f * (_hoops_CSSPA->_hoops_RPIS[1][0] + _hoops_CSSPA->_hoops_RPIS[1][1]);
			out_points->z = 0.5f * (_hoops_CSSPA->_hoops_RPIS[2][0] + _hoops_CSSPA->_hoops_RPIS[2][1]);
			++out_points;
		}

		if (_hoops_HSSPA != null) {
			_hoops_HSSPA->red   = 0.5f * (_hoops_CSSPA->_hoops_RPIS[4][0] + _hoops_CSSPA->_hoops_RPIS[4][1]);
			_hoops_HSSPA->green = 0.5f * (_hoops_CSSPA->_hoops_RPIS[5][0] + _hoops_CSSPA->_hoops_RPIS[5][1]);
			_hoops_HSSPA->blue  = 0.5f * (_hoops_CSSPA->_hoops_RPIS[6][0] + _hoops_CSSPA->_hoops_RPIS[6][1]);
			++_hoops_HSSPA;
		}

		if (mapping != null) {
			int			j;

			for (j=_hoops_CSSPA->indices[0]; j<=_hoops_CSSPA->indices[1]; j++)
				mapping[indices[j]] = i;
		}

		FREE (_hoops_CSSPA, _hoops_GSSPA);
		i++;
	}

	FREE_ARRAY (data, dimensions*_hoops_HAHC, float);
	FREE_ARRAY (indices, _hoops_HAHC, int);
	delete _hoops_GGGHA;
}







#ifndef DISABLE_COMPUTE
/* 
 * _hoops_AAP _hoops_IH _hoops_RRGHA _hoops_RH _hoops_AAHP
 */

#define _hoops_ARGHA(a,b,c,_hoops_PRGHA) ((a)^((b)<<((_hoops_PRGHA)/2))^((c)<<(_hoops_PRGHA)))
#define _hoops_HRGHA(a,b) ((a)^(((b)>>16)|((b)<<16)))

/* _hoops_CARA _hoops_CSCHR _hoops_PSPA, _hoops_PAR _hoops_IRGHA _hoops_CSCHR _hoops_PSPA */
#define _hoops_CRGHA	0x1				
#define _hoops_SRGHA	0x2		

local const _hoops_IGRCR _hoops_GAGHA[] = {
	{_hoops_CRGHA, _hoops_GRRCR ("oru"),						_hoops_RRRCR, 0, false},
	{_hoops_CRGHA, _hoops_GRRCR (""),							_hoops_RRRCR, 0, false},
	{_hoops_SRGHA, _hoops_GRRCR ("%"),							_hoops_RRRCR, 0, false},
	{_hoops_SRGHA, _hoops_GRRCR ("% fru"),						_hoops_RRRCR, 0, false},
	{_hoops_SRGHA, _hoops_GRRCR ("% feature relative units"),	_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_RAGHA = {
	_hoops_GGAPR (_hoops_GAGHA),
	_hoops_GAGHA,
};


/* 
 * _hoops_AAP _hoops_IH _hoops_RRGHA _hoops_RH _hoops_GSSR _hoops_AAHP 
 */

/* _hoops_ASIPR _hoops_PAR _hoops_AAGHA */
#define _hoops_PAGHA	0x1
#define _hoops_HAGHA	0x2

#if !defined(_hoops_IAGHA)
#	 define _hoops_IAGHA		(3.14159265358979323846264338327950288)
#endif
/* 360 _hoops_RIPI _hoops_HPP 2_hoops_CAGHA */
#define _hoops_SAGHA					(180.0 / _hoops_IAGHA)	

local const _hoops_IGRCR _hoops_GPGHA[] = {
	{_hoops_PAGHA, _hoops_GRRCR ("deg"),				_hoops_RRRCR, 0, false},
	{_hoops_PAGHA, _hoops_GRRCR ("degrees"),			_hoops_RRRCR, 0, false},
	{_hoops_PAGHA, _hoops_GRRCR (""),					_hoops_RRRCR, 0, false},
	{_hoops_HAGHA, _hoops_GRRCR ("rad"),				_hoops_RRRCR, 0, false},
	{_hoops_HAGHA, _hoops_GRRCR ("radians"),			_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_RPGHA = {
	_hoops_GGAPR (_hoops_GPGHA),
	_hoops_GPGHA,
};


local const _hoops_IGRCR _hoops_APGHA[] = {
	{_hoops_PPGHA, _hoops_GRRCR ("%"),			_hoops_RRRCR, 0, false},
	{_hoops_HPGHA,	 _hoops_GRRCR (""),				_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_IPGHA = {
	_hoops_GGAPR (_hoops_APGHA),
	_hoops_APGHA,
};


#define _hoops_CPGHA 0x1
#define _hoops_SPGHA 0x2
local const _hoops_IGRCR _hoops_GHGHA[] = {
	{_hoops_CPGHA, _hoops_GRRCR ("nicest"), _hoops_RRRCR, 0, false},
	{_hoops_SPGHA, _hoops_GRRCR ("fastest"), _hoops_RRRCR, 0, false},
	{_hoops_CPGHA, _hoops_GRRCR ("nice"), _hoops_RRRCR, 0, false},
	{_hoops_SPGHA, _hoops_GRRCR ("fast"), _hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_RHGHA = {
	_hoops_GGAPR (_hoops_GHGHA),
	_hoops_GHGHA,
};


/* 
 * _hoops_AHGHA _hoops_AAP _hoops_HIGR _hoops_IH _hoops_PHGHA 
 */

#define _hoops_HHGHA		0x0001
#define _hoops_IHGHA				0x0002
#define _hoops_CHGHA			0x0004
#define _hoops_SHGHA		0x0008
#define _hoops_GIGHA		0x0010
#define _hoops_RIGHA					0x0020
#define _hoops_AIGHA			0x0040
#define _hoops_PIGHA					0x0080
#define _hoops_HIGHA					0x0100

local const _hoops_IGRCR _hoops_IIGHA[] = {
	{_hoops_HHGHA, _hoops_GRRCR ("normal tolerance"), _hoops_CIGHA, 1, true, &_hoops_RPGHA},
	{_hoops_IHGHA, _hoops_GRRCR ("tolerance"), _hoops_CIGHA, 1, true, &_hoops_RAGHA},
	{_hoops_CHGHA, _hoops_GRRCR ("collapsible"), _hoops_PRRCR, 1, true},
	{_hoops_SHGHA, _hoops_GRRCR ("collapsible info"), _hoops_SIGHA, 1, true},
	{_hoops_GIGHA, _hoops_GRRCR ("orphan elimination"), _hoops_RRRCR, 0, true},
	{_hoops_RIGHA, _hoops_GRRCR ("lod"), _hoops_CIGHA, -1, true, &_hoops_IPGHA},
	{_hoops_RIGHA, _hoops_GRRCR ("level of detail"), _hoops_CIGHA, -1, true, &_hoops_IPGHA},
	{_hoops_AIGHA, _hoops_GRRCR("lod algorithm"), _hoops_GHAGA, -999, false, &_hoops_RHGHA },
	{_hoops_AIGHA, _hoops_GRRCR("level of detail algorithm"), _hoops_GHAGA, -999, false, &_hoops_RHGHA },
	{_hoops_PIGHA, _hoops_GRRCR ("skin"), _hoops_RRRCR, 0, false},
	{_hoops_HIGHA, _hoops_GRRCR ("faces fix"), _hoops_RRRCR, 0, false},
	{_hoops_HIGHA, _hoops_GRRCR ("face fix"), _hoops_RRRCR, 0, false},
	{_hoops_HIGHA, _hoops_GRRCR ("fix faces"), _hoops_RRRCR, 0, false},
	{_hoops_HIGHA, _hoops_GRRCR ("fix handedness"), _hoops_RRRCR, 0, false},
};


/*
 * _hoops_HGI _hoops_CPPC _hoops_PCCP _hoops_CIHA _hoops_SGS _hoops_HRGR _hoops_HPAP _hoops_IS _hoops_PHGA "_hoops_GCGHA"
 * _hoops_HHIGR _hoops_PIHA _hoops_SHH -1 _hoops_PGGA 
 *    _hoops_IRS) _hoops_SCH _hoops_PIHA _hoops_SHH _hoops_CRGP _hoops_HSAR _hoops_GII _hoops_SSRR _hoops_PSHS _hoops_GPHA
 *    _hoops_RCSR) _hoops_GII _hoops_RII _hoops_HHHR _hoops_PIRA _hoops_GRS _hoops_IHSA _hoops_RH _hoops_RCGHA _hoops_AASA
 */
#define _hoops_ACGHA (-1)


struct configs {
	float				tolerance;
	long				_hoops_PCGHA;
	float				_hoops_HCGHA;
	long				_hoops_ICGHA;
	_hoops_HCHIR	*collapsible;		 /* _hoops_CCGHA _hoops_IRGHA */
	void				*_hoops_SCGHA;
	void				*_hoops_GSGHA;
	bool			_hoops_RSGHA;
	bool			_hoops_PRSI;
	int					_hoops_ASGHA;
	float				_hoops_PSGHA;
	float				_hoops_HSGHA;
	bool			_hoops_ISGHA;
	bool			_hoops_HICPA;
};


typedef struct vertex {
	struct vertex		*_hoops_CSGHA;
	float				_hoops_SSGHA;
	Integer32				_hoops_GGRHA; /* _hoops_RGRHA _hoops_PGGA _hoops_SCH'_hoops_GRI _hoops_CGI _hoops_IS _hoops_RHGC _hoops_AGRHA */
	int					_hoops_PGRHA;
	int					_hoops_HIHI;
} _hoops_HGRHA;


#define _hoops_IGRHA(a, b, c)	((a) + (b) + (c))
#define _hoops_CGRHA (1e-12f)


local bool _hoops_CHGAA (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			option_string,
	struct configs *		_hoops_SHGAA) 
{
	Option_Value *			option_list = null;
	Option_Value *			option;

	/* _hoops_ARP _hoops_SHIR _hoops_HSH _hoops_IH _hoops_HCR _hoops_IIGR _hoops_RH _hoops_GIGAA */
	_hoops_SHGAA->tolerance = 0.0f;
	_hoops_SHGAA->_hoops_PCGHA = _hoops_CRGHA;
	_hoops_SHGAA->_hoops_HCGHA = 0.0f;
	_hoops_SHGAA->_hoops_ICGHA = _hoops_PAGHA;
	_hoops_SHGAA->collapsible = null;
	_hoops_SHGAA->_hoops_SCGHA = null;
	_hoops_SHGAA->_hoops_GSGHA = null;
	_hoops_SHGAA->_hoops_RSGHA = true;
	_hoops_SHGAA->_hoops_PRSI = 0;
	_hoops_SHGAA->_hoops_ASGHA = _hoops_SPGHA;
	_hoops_SHGAA->_hoops_PSGHA = _hoops_SGRHA;
	_hoops_SHGAA->_hoops_HSGHA = _hoops_SGRHA;
	_hoops_SHGAA->_hoops_ISGHA = false;
	_hoops_SHGAA->_hoops_HICPA = false;

	if (option_string == null) return false;

	_hoops_HIACR (_hoops_GRRHA, _hoops_IIGHA);

	if (!HI_Parse_Options (_hoops_RIGC, option_string, _hoops_CIACR (_hoops_GRRHA),
						   &option_list, _hoops_SIACR))
		return false;


	if ((option = option_list) != null) do {
		switch (option->type->id) {
		  case _hoops_IHGHA: {
			  if (option->_hoops_GCACR) {
				  _hoops_SHGAA->tolerance = 0.0f;
				  _hoops_SHGAA->_hoops_PCGHA = _hoops_CRGHA;
			  }
			  else if (option->value._hoops_RRRHA[0].value < 0.0f) {
				  HE_ERROR (HEC_COMPUTE, HES_INVALID_TOLERENCE,
						  "Tolerance value must be non-negative");
				  HI_Free_Option_List (_hoops_RIGC, option_list);
				  return false;
			  }
			  else {
				  _hoops_SHGAA->tolerance = option->value._hoops_RRRHA[0].value;
				  _hoops_SHGAA->_hoops_PCGHA = option->value._hoops_RRRHA[0]._hoops_HHP;
			  }
		  }	  break;

		  case _hoops_HHGHA: {
			  if (option->_hoops_GCACR) {
				  _hoops_SHGAA->_hoops_HCGHA = 0.0f;
				  _hoops_SHGAA->_hoops_ICGHA = _hoops_PAGHA;
			  }
			  else if (option->value._hoops_RRRHA[0].value < 0.0f) {
				  HE_ERROR (HEC_COMPUTE, HES_INVALID_TOLERENCE,
						  "Normal tolerance value must be non-negative");
				  HI_Free_Option_List (_hoops_RIGC, option_list);
				  return false;
			  }
			  else {
				  _hoops_SHGAA->_hoops_HCGHA = option->value._hoops_RRRHA[0].value;
				  _hoops_SHGAA->_hoops_ICGHA = option->value._hoops_RRRHA[0]._hoops_HHP;
			  }
		  }	  break;

		  case _hoops_CHGHA: {
			  _hoops_HCRPR					*name = &option->value._name[0];
			  _hoops_HCHIR		*_hoops_IGPCR;

			  if (option->_hoops_GCACR)
				  _hoops_SHGAA->collapsible = null;
#ifndef DISABLE_CALLBACKS
			  else if ((_hoops_IGPCR = *HI_Look_Up_Callback_Name (_hoops_RIGC, name->text,
															name->length)) != null)
				  _hoops_SHGAA->collapsible = _hoops_IGPCR;
			  else {
				  HE_ERROR (HEC_COMPUTE, HES_CALLBACK,
						  Sprintf_N (null, "Collapsible '%n' is not a defined callback",
									   name));
				  HI_Free_Option_List (_hoops_RIGC, option_list);
				  return false;
			  }
#else
			  else
				  _hoops_SHGAA->collapsible = null;
#endif
		  }	  break;

		  /* 
		   *  _hoops_ARRHA _hoops_IIAC _hoops_GPP 7/28/98 _hoops_PAHH _hoops_PRRHA _hoops_RGR _hoops_HRRHA _hoops_CAPGR _hoops_RRGR.  _hoops_HGI _hoops_IRGHA
		   * _hoops_HRGR _hoops_CCGHA, _hoops_IRRHA, _hoops_PPR _hoops_PRGS.	_hoops_IPCP _hoops_CRRHA _hoops_CHR _hoops_RAAP _hoops_IS _hoops_SHSP
		   * _hoops_IGS _hoops_RH _hoops_SRRHA _hoops_IIGR _hoops_GARHA _hoops_SCH _hoops_ISSC.
		   */
		  case _hoops_SHGHA: {
			  if (option->_hoops_GCACR)
				  _hoops_SHGAA->_hoops_SCGHA = null;
			  else
				  _hoops_SHGAA->_hoops_SCGHA = (void *)(POINTER_SIZED_INT)option->value._hoops_RARHA[0];
		  }	  break;

		  case _hoops_GIGHA: {
			  _hoops_SHGAA->_hoops_RSGHA = !option->_hoops_GCACR;
		  }	  break;

		  case _hoops_RIGHA: {
			  if (option->_hoops_GCACR) {
				  _hoops_SHGAA->_hoops_PRSI = 0;
			  }
			  else if (option->value._hoops_RRRHA[0].value < 0.0f) {
				  HE_ERROR (HEC_COMPUTE, HES_INVALID_NUMBER,
						  "LOD target percentage value must be non-negative");
				  HI_Free_Option_List (_hoops_RIGC, option_list);
				  return false;
			  }
			  else {
				  _hoops_SHGAA->_hoops_PRSI = 1;
				  _hoops_SHGAA->_hoops_PSGHA = option->value._hoops_RRRHA[0].value * 0.01f;
			  }
		  }	  break;

		  case _hoops_AIGHA: {
			  _hoops_SHGAA->_hoops_ASGHA = option->value.option_list->type->id;
		  }	  break;

		  case _hoops_PIGHA: {
			  _hoops_SHGAA->_hoops_ISGHA = !option->_hoops_GCACR;
		  }	  break;

		  case _hoops_HIGHA: {
			  _hoops_SHGAA->_hoops_HICPA = !option->_hoops_GCACR;
		  }	  break;

		}
	} _hoops_RGGA ((option = option->next) == null);

	HI_Free_Option_List (_hoops_RIGC, option_list);
	return true;
}
#endif


/*
 * _hoops_RGR _hoops_API _hoops_HRGR _hoops_HA _hoops_AARHA.  _hoops_HHIGR _hoops_HRGR _hoops_ARSAR _hoops_IH _hoops_SPCHR _hoops_AAACR _hoops_RGAR
 */
HC_INTERFACE void HC_CDECL HC_Compute_Minimized_Shell (
	int					in_point_count,
	Point const *		in_points,
	int					in_face_list_length,
	int const *			in_face_list,
	char const *		option_string,
	int *				out_point_count,
	Point *				out_points,
	int *				out_face_list_length,
	int *				out_face_list,
	int *				vertex_mapping,
	int *				face_mapping) {

	HC_Compute_Optimized_Shell (
			in_point_count, in_points, null, 
			in_face_list_length, in_face_list,
			option_string, 
			out_point_count, out_points,
			out_face_list_length, out_face_list,
			vertex_mapping, face_mapping
	);
}

#ifndef DISABLE_COMPUTE

local void compute_optimized_shell (
	int						in_point_count,
	Point const				*in_points,
	Vector const			*_hoops_ISHRA,	   /* _hoops_HHS _hoops_SHH _hoops_IRAP _hoops_RPP _hoops_HAR _hoops_GPIHR */
	int						in_face_list_length,
	int const				*in_face_list,
	int						(HC_CDECL * collapsible) (
												void *pts,
												void *_hoops_PARHA,
												Integer32 a,
												Integer32 b,
												double _hoops_HARHA,
												double _hoops_IARHA),
	const struct configs	*config,
	int						*out_point_count,
	Point					*out_points,
	int						*out_face_list_length,
	int						*out_face_list,
	int						*_hoops_CARHA, /* _hoops_HHS _hoops_SHH _hoops_IRAP _hoops_RPP _hoops_HAR _hoops_GPIHR */
	int						*face_mapping)    /* _hoops_HHS _hoops_SHH _hoops_IRAP _hoops_RPP _hoops_HAR _hoops_GPIHR */
{ 
	_hoops_HGRHA			*vertices;
	int						*vertex_mapping;
	float					_hoops_SARHA;
	float					_hoops_GPRHA = config->tolerance;
	double					_hoops_HARHA; /* _hoops_GHGPR _hoops_PGGA _hoops_RPRHA _hoops_CGI */
	double					_hoops_IARHA;
	float					*_hoops_APRHA;
	int						*indices;

	UNREFERENCED (_hoops_ISHRA);

	/*
	 * _hoops_SIPR _hoops_IRS _hoops_GPHA _hoops_SIA _hoops_CRPR _hoops_RPP _hoops_RH _hoops_IPSP _hoops_SARS'_hoops_RA _hoops_RCRP _hoops_IHHH _hoops_SPR
	 * _hoops_PPR _hoops_SCAC _hoops_SCH _hoops_GGSR
	 */
	if (_hoops_CARHA != null)
		vertex_mapping = _hoops_CARHA;
	else
		ALLOC_ARRAY (vertex_mapping, in_point_count, int);
	SET_MEMORY (vertex_mapping, in_point_count*sizeof(int), _hoops_ACGHA);

	ALLOC_ARRAY_CACHED (_hoops_APRHA, in_point_count, float);
	ALLOC_ARRAY_CACHED (indices, in_point_count, int);
	{
		const Point *pp = in_points;
		const Point *pe = pp + in_point_count;
		int index = 0;

		do {
			indices[index]		= index;
			_hoops_APRHA[index]  = _hoops_IGRHA (pp->x, pp->y, pp->z);
			++index;
		} _hoops_RGGA (++pp == pe);
	}
	HI_Sort_Array (in_point_count, _hoops_APRHA, (void **)indices, sizeof(int), true);

	/*
	 * _hoops_IIPP _hoops_PPR _hoops_HSPC _hoops_IRS _hoops_HRPR _hoops_IH
	 * _hoops_GRR _hoops_PSHS _hoops_GPHA.	_hoops_HGI _hoops_GRS _hoops_SHH _hoops_IGI _hoops_GGR
	 * _hoops_RH _hoops_RIIRA _hoops_CAPP.
	 */
	ALLOC_ARRAY_CACHED (vertices, in_point_count, _hoops_HGRHA);
	{
		_hoops_HGRHA	*_hoops_PAPH = vertices;
		const Point *pp = in_points;
		const Point *pe = pp + in_point_count;
		int				index = 0;

		do {
			vertices[index]._hoops_GGRHA	= indices[index];
			vertex_mapping[indices[index]] = index;
			_hoops_PAPH = &vertices[indices[index]];
			_hoops_PAPH->_hoops_PGRHA		= _hoops_ACGHA;
			_hoops_PAPH->_hoops_CSGHA		= null;
			_hoops_PAPH->_hoops_SSGHA = _hoops_APRHA[indices[index]];
			_hoops_PAPH->_hoops_HIHI			= 0;
			++index;
		} _hoops_RGGA (++pp == pe);
	}
	FREE_ARRAY (_hoops_APRHA, in_point_count, float);
	FREE_ARRAY (indices, in_point_count, int);

	/*
	 * _hoops_SSCR _hoops_RH _hoops_IGPI _hoops_IIGR _hoops_RH _hoops_RSSA _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_GPIHR
	 */
	if (config->_hoops_RSGHA && in_face_list_length > 0) {
		const int *_hoops_PPRHA = in_face_list;
		const int *_hoops_HPRHA = _hoops_PPRHA + in_face_list_length;
		const int *_hoops_CRRHR;
		int _hoops_HCGS;

		do {
			if (*_hoops_PPRHA < 0)
				_hoops_CRRHR = _hoops_PPRHA - *_hoops_PPRHA + 1;
			else
				_hoops_CRRHR = _hoops_PPRHA + *_hoops_PPRHA + 1;

			_hoops_RGGA (++_hoops_PPRHA == _hoops_CRRHR) {
				_hoops_HCGS = vertex_mapping[*_hoops_PPRHA];
				vertices[_hoops_HCGS]._hoops_HIHI++;
			}
		} _hoops_RGGA (_hoops_PPRHA == _hoops_HPRHA);
	}
	SET_MEMORY (vertex_mapping, in_point_count*sizeof(int), _hoops_ACGHA);

	/*
	 * _hoops_HGH _hoops_RH _hoops_IPRHA _hoops_SAIPR, "_hoops_CPRHA" _hoops_IH _hoops_RSSA
	 * _hoops_IS _hoops_SHH _hoops_GHSAR _hoops_HRRHA, _hoops_PPR _hoops_RH _hoops_SPRHA _hoops_AAHP _hoops_IH
	 * _hoops_HGPP _hoops_IRS _hoops_GHRHA _hoops_IS _hoops_GPHCR.
	 */
	if (config->_hoops_PCGHA == _hoops_SRGHA && in_face_list_length > 0) {
		int const		*_hoops_PPRHA = in_face_list;
		int const		*_hoops_HPRHA = _hoops_PPRHA + in_face_list_length;
		int const		*_hoops_CRRHR;
		int				_hoops_RHRHA;
		int				index;
		float			dx, _hoops_CRRAR, _hoops_AAAC, len;
		float			_hoops_AHRHA = MAX_FLOAT;

		/*
		 * _hoops_ACGR _hoops_RH _hoops_GIRA _hoops_GAPA _hoops_RH _hoops_PHRHA _hoops_PGCR
		 * _hoops_GIHA _hoops_GPP _hoops_GII _hoops_SPR _hoops_HSP _hoops_GGR _hoops_RH _hoops_RRCPR.  _hoops_HGI _hoops_GRS
		 * _hoops_PPIP _hoops_RH _hoops_HHRHA _hoops_IH _hoops_SGH _hoops_GGR _hoops_IHRHA _hoops_PCCP _hoops_CHRHA _hoops_PPR
		 * _hoops_GPSGA.
		 */
		do {
			if (*_hoops_PPRHA < 0)
				_hoops_CRRHR = _hoops_PPRHA - *_hoops_PPRHA + 1;
			else
				_hoops_CRRHR = _hoops_PPRHA + *_hoops_PPRHA + 1;

			_hoops_RHRHA = _hoops_CRRHR[-1];

			_hoops_RGGA (++_hoops_PPRHA == _hoops_CRRHR) {
				index = *_hoops_PPRHA;

				dx = in_points[index].x - in_points[_hoops_RHRHA].x;
				_hoops_CRRAR = in_points[index].y - in_points[_hoops_RHRHA].y;
				_hoops_AAAC = in_points[index].z - in_points[_hoops_RHRHA].z;
				len = dx*dx + _hoops_CRRAR*_hoops_CRRAR + _hoops_AAAC*_hoops_AAAC;
				if (len < _hoops_AHRHA && len != 0.0f) _hoops_AHRHA = len;

				_hoops_RHRHA = index;
			}
		} _hoops_RGGA (_hoops_PPRHA == _hoops_HPRHA);

		_hoops_HARHA = _hoops_AHRHA * _hoops_GPRHA / 100.0f;
		{
			float	_hoops_IASGA = _hoops_SGIHR ((float)_hoops_HARHA);
			_hoops_SARHA = _hoops_IGRHA (_hoops_IASGA, _hoops_IASGA, _hoops_IASGA);
		}
	}
	else {
		_hoops_SARHA = _hoops_IGRHA (_hoops_GPRHA, _hoops_GPRHA, _hoops_GPRHA);
		_hoops_HARHA = _hoops_GPRHA * _hoops_GPRHA;
	}

	  /* 
	   * _hoops_SGPR _hoops_RH _hoops_SHRHA _hoops_IIGR _hoops_GIRHA (_hoops_IHRPR^2 = _hoops_RAIGR^2 + _hoops_IHAC^2 - 2ABc_hoops_RIRHA(_hoops_CCSA)) 
	   * _hoops_IS _hoops_CSGA _hoops_RH _hoops_AIRHA.
	   * _hoops_HAPI _hoops_SR _hoops_CHR _hoops_HAGC _hoops_RH _hoops_GHPH _hoops_SGS _hoops_RH _hoops_ASGA _hoops_CHR _hoops_SCGA, _hoops_HIS _hoops_RAIGR = _hoops_IHAC = 1.0
	   * _hoops_CPGP _hoops_SR _hoops_CHR _hoops_GPIHR _hoops_GGR _hoops_PPS, _hoops_HAR _hoops_PIRHA, _hoops_HIRHA _hoops_GIRA _hoops_GAPA
	   * _hoops_PSPAR _hoops_HRGR _hoops_CHIS.
	   */
	if (config->_hoops_ICGHA == _hoops_PAGHA)
		_hoops_IARHA = 2.0 - 2.0 * COS ((float)config->_hoops_HCGHA);
	else
		_hoops_IARHA = 2.0 - 2.0 * COS ((float)config->_hoops_HCGHA * (float)_hoops_SAGHA);


	/*
	 * _hoops_ACGR _hoops_HSGS _hoops_RSSA
	 */
	{
		_hoops_HGRHA			*_hoops_IIRHA;
		_hoops_HGRHA			*_hoops_CSAGR;
		_hoops_HGRHA			*_hoops_PAPH = vertices;
		_hoops_HGRHA			*_hoops_CIRHA = _hoops_PAPH + in_point_count;
		int				_hoops_SIRHA = 0;

		do {
			if (config->_hoops_RSGHA && _hoops_PAPH->_hoops_HIHI == 0) {
				_hoops_PAPH->_hoops_PGRHA = _hoops_ACGHA;
			}
			else if (_hoops_PAPH->_hoops_PGRHA != _hoops_ACGHA) {
				/* _hoops_SR'_hoops_RISP _hoops_AIAH _hoops_GCRHA _hoops_RGR _hoops_PPSR */
			}
			else {
				/*
				 * _hoops_HGI _hoops_PPSR _hoops_HRGR _hoops_HSGS, _hoops_HIS _hoops_SGIP
				 */
				_hoops_PAPH->_hoops_PGRHA =
					vertex_mapping[_hoops_PAPH->_hoops_GGRHA] =
						_hoops_SIRHA++;

				_hoops_CSAGR = _hoops_PAPH;

				/*
				 * _hoops_ACGR _hoops_APIHR _hoops_GASAR _hoops_ISHP _hoops_RH _hoops_HIGR, _hoops_GIAA _hoops_RH '_hoops_CPRHA.
				 */
				_hoops_IIRHA = _hoops_PAPH + 1;
				while (_hoops_IIRHA != _hoops_CIRHA &&
					   _hoops_IIRHA->_hoops_SSGHA -
						 _hoops_CSAGR->_hoops_SSGHA <= _hoops_SARHA) {
					if ((*collapsible) (config->_hoops_SCGHA,
										config->_hoops_GSGHA,
										_hoops_CSAGR->_hoops_GGRHA,
										_hoops_IIRHA->_hoops_GGRHA,
										_hoops_HARHA,
										_hoops_IARHA)) {
						_hoops_HGRHA *_hoops_CSGHA;

						/*
						 * _hoops_RCRHA _hoops_RCRR _hoops_SR'_hoops_ASAR _hoops_IRS _hoops_SAIHR _hoops_IIGR _hoops_HCR _hoops_APIHR
						 */
						if ((_hoops_CSGHA = _hoops_CSAGR->_hoops_CSGHA) != null) do {
							if (!(*collapsible) (config->_hoops_SCGHA,
												 config->_hoops_GSGHA,
												 _hoops_IIRHA->_hoops_GGRHA,
												 _hoops_CSGHA->_hoops_GGRHA,
												 _hoops_HARHA,
												 _hoops_IARHA))
								break;
						} _hoops_RGGA ((_hoops_CSGHA = _hoops_CSGHA->_hoops_CSGHA) == null);

						if (_hoops_CSGHA == null) {
							_hoops_IIRHA->_hoops_PGRHA =
								vertex_mapping[_hoops_IIRHA->_hoops_GGRHA] =
									_hoops_CSAGR->_hoops_PGRHA;

							_hoops_IIRHA->_hoops_CSGHA = _hoops_CSAGR;
							_hoops_CSAGR = _hoops_IIRHA;
						}
					}

					++_hoops_IIRHA;
				}
			}
		} _hoops_RGGA (++_hoops_PAPH == _hoops_CIRHA);
	}


	/*
	 * _hoops_ACRHA _hoops_RH _hoops_RSSA
	 * _hoops_PS _hoops_ACPA _hoops_SGS _hoops_RH _hoops_HACH _hoops_PSPI _hoops_IIGR _hoops_RH _hoops_GSHHR _hoops_GIHA _hoops_GRS _hoops_SHH
	 * _hoops_PCRHA, _hoops_HIH _hoops_HAR _hoops_HCRHA, _hoops_GRAA-_hoops_HSRAR.	_hoops_HPGHR _hoops_RGR _hoops_GHAP _hoops_PHGA _hoops_SGS
	 *	   _hoops_GPHA[_hoops_ICRHA + 1]._hoops_CCRHA - _hoops_GPHA[_hoops_ICRHA]._hoops_CCRHA = [0, 1]
	 * _hoops_PS _hoops_PHGA _hoops_IS _hoops_PRIA _hoops_RH _hoops_SCRHA, _hoops_PGAP _hoops_IRHC _hoops_IRS _hoops_CCAH, _hoops_HSGS, _hoops_GRAA-_hoops_GSRHA _hoops_GPHA.
	 * _hoops_HGI _hoops_HRGR _hoops_CPHR _hoops_HPP _hoops_RSRHA _hoops_PCCP _hoops_ASRHA _hoops_GGR _hoops_HIHHR _hoops_IIGR _hoops_RH _hoops_CCRHA _hoops_CGPR
	 * _hoops_PSRHA _hoops_HSRHA _hoops_RH _hoops_GIHA _hoops_CRPR.
	 */
	if (out_points != null) {
		int				index;
		Point		*pp = out_points;
		_hoops_HGRHA			*_hoops_PAPH;
		_hoops_HGRHA			*_hoops_CIRHA;

		index = _hoops_ACGHA;
		_hoops_PAPH = vertices;
		_hoops_CIRHA = _hoops_PAPH + in_point_count;

		do if (index < _hoops_PAPH->_hoops_PGRHA) {
			index = _hoops_PAPH->_hoops_PGRHA;
			pp->x = in_points[_hoops_PAPH->_hoops_GGRHA].x;
			pp->y = in_points[_hoops_PAPH->_hoops_GGRHA].y;
			pp->z = in_points[_hoops_PAPH->_hoops_GGRHA].z;
			++pp;
		} _hoops_RGGA (++_hoops_PAPH == _hoops_CIRHA);
		*out_point_count = pp - out_points;
	}
	else if (out_point_count != null) {
		int				pcount;
		int				index;
		_hoops_HGRHA *_hoops_PAPH;
		_hoops_HGRHA *_hoops_CIRHA;

		index = _hoops_ACGHA;
		_hoops_PAPH = vertices;
		_hoops_CIRHA = _hoops_PAPH + in_point_count;
		pcount = 0;

		do if (index < _hoops_PAPH->_hoops_PGRHA) {
			index = _hoops_PAPH->_hoops_PGRHA;
			pcount++;
		} _hoops_RGGA (++_hoops_PAPH == _hoops_CIRHA);
		*out_point_count = pcount;
	}



	/*
	 * _hoops_ACRHA _hoops_RH _hoops_HSP _hoops_HIGR, _hoops_ISRHA _hoops_SSRS _hoops_GIHA
	 * _hoops_PPR _hoops_CSRHA _hoops_SGGR _hoops_ARHAR _hoops_RSSI
	 */
	if ((in_face_list_length > 0) && (out_face_list != null)) {
		int const		*_hoops_PPRHA;
		int const		*_hoops_HPRHA;
		int				*_hoops_SSRHA;
		int				_hoops_GGAHA = 0;
		bool			_hoops_RGAHA = false;

		_hoops_PPRHA = in_face_list;
		_hoops_HPRHA = _hoops_PPRHA + in_face_list_length;
		_hoops_SSRHA = out_face_list;

		do {
			int const		*_hoops_CRRHR;
			int				_hoops_RHRHA;
			int				*_hoops_AGAHA;
			int				_hoops_PGAHA;
			int				_hoops_HGAHA;

			if (*_hoops_PPRHA < 0) {
				_hoops_HGAHA = 1;
				_hoops_CRRHR = _hoops_PPRHA - *_hoops_PPRHA + 1;
			}
			else {
				_hoops_HGAHA = 0;
				_hoops_CRRHR = _hoops_PPRHA + *_hoops_PPRHA + 1;
			}

			_hoops_RHRHA = vertex_mapping[_hoops_CRRHR[-1]];
			_hoops_AGAHA = _hoops_SSRHA++;

			_hoops_RGGA (++_hoops_PPRHA == _hoops_CRRHR) {
				int		index = vertex_mapping[*_hoops_PPRHA];
				if (index < 0 && !_hoops_RGAHA) {
					HE_ERROR (HEC_COMPUTE, HES_INVALID_INDEX,
						"internal error in Compute_Optimized_Shell: negative index in vertex mapping.");
					_hoops_RGAHA = true;
				}
				if (index != _hoops_RHRHA)
					*_hoops_SSRHA++ = _hoops_RHRHA = index;
			}

			_hoops_PGAHA = _hoops_SSRHA - _hoops_AGAHA - 1;
			if (_hoops_PGAHA < 3) {
				if (face_mapping != null) *face_mapping++ = _hoops_ACGHA;
				_hoops_SSRHA -= _hoops_PGAHA + 1;
			}
			else {
				if (_hoops_HGAHA)
					*_hoops_AGAHA = -_hoops_PGAHA;
				else
					*_hoops_AGAHA = _hoops_PGAHA;
				if (face_mapping != null) *face_mapping++ = _hoops_GGAHA++;
			}
		} _hoops_RGGA (_hoops_PPRHA == _hoops_HPRHA);

		if (out_face_list_length != null)
			*out_face_list_length = _hoops_SSRHA - out_face_list;
	}
	else
		if (out_face_list_length != null)
			*out_face_list_length = 0;

	/*
	 * _hoops_SP _hoops_GH
	 */
	if (vertex_mapping != _hoops_CARHA)
		FREE_ARRAY (vertex_mapping, in_point_count, int);
	FREE_ARRAY (vertices, in_point_count, _hoops_HGRHA);
}


local int _hoops_IGAHA (
	void			*_hoops_CGAHA,
	void			*_hoops_SGAHA,
	Integer32	a,
	Integer32	b,
	double			_hoops_HARHA,
	double			_hoops_IARHA) {
	Point		*pts = (Point *)_hoops_CGAHA;
	Vector		*_hoops_PARHA = (Vector *)_hoops_SGAHA;
	float			delta;
	float			dist; /* _hoops_GRAHA _hoops_RRAHA _hoops_GIRA */

	delta = pts[a].x - pts[b].x;
	dist =	delta*delta;
	delta = pts[a].y - pts[b].y;
	dist += delta*delta;
	delta = pts[a].z - pts[b].z;
	if ((dist +	 delta*delta) > _hoops_HARHA) 
		return false;

	if (_hoops_PARHA != null) {
		delta = _hoops_PARHA[a].x - _hoops_PARHA[b].x;
		dist =	delta*delta;
		delta = _hoops_PARHA[a].y - _hoops_PARHA[b].y;
		dist += delta*delta;
		delta = _hoops_PARHA[a].z - _hoops_PARHA[b].z;
		if ((dist +	 delta*delta) > _hoops_IARHA) 
			return false;
	}

	return true;
}


local int _hoops_ARAHA (int _hoops_HAGR) {
	int i;

	for (i = 0; i < 32; i++) {
	   if (0x1<<i >= _hoops_HAGR)
		   break;
	}
	return i+1;
}


/* _hoops_PRAHA _hoops_PPR _hoops_HRAHA _hoops_CHR _hoops_RH _hoops_PSPI _hoops_GIAA _hoops_RH _hoops_HSP _hoops_SGS _hoops_CGRPR _hoops_RH _hoops_ISPP _hoops_GPHA _hoops_CRSRR.
 * _hoops_RIH -1 _hoops_RPP _hoops_HAR _hoops_HSSPR */
local bool _hoops_IRAHA (
	const int *_hoops_AIPPA, int i1, 
	const int *_hoops_PIPPA, int i2, 
	bool _hoops_HHAHR)
{
	int i, min, length;

	/* _hoops_HSP _hoops_IHHA _hoops_HS _hoops_IS _hoops_PSSP */
	if (*_hoops_AIPPA != *_hoops_PIPPA)
		return false;

	if (*_hoops_AIPPA > 0)
		length = *_hoops_AIPPA + 1;
	else
		length = -(*_hoops_AIPPA) + 1;
	
	/* _hoops_SSS _hoops_RH _hoops_CIHA _hoops_IIGR _hoops_RH _hoops_ISPP _hoops_GPHA _hoops_GGR _hoops_CRAHA (_hoops_RPP _hoops_HAR _hoops_AIAH _hoops_RAGA) */
	if (i1 < 0) {
		min = _hoops_AIPPA[1];
		i1 = 1;
		for (i = 2; i < length; i++) {
			if (_hoops_AIPPA[i] < min) {
				min = _hoops_AIPPA[i];
				i1 = i;
			}
		}
	}
	/* _hoops_SSS _hoops_RH _hoops_CIHA _hoops_IIGR _hoops_RH _hoops_ISPP _hoops_GPHA _hoops_GGR _hoops_SRAHA (_hoops_RPP _hoops_HAR _hoops_AIAH _hoops_RAGA) */
	if (i2 < 0) {
		min = _hoops_PIPPA[1];
		i2 = 1;
		for (i = 2; i < length; i++) {
			if (_hoops_PIPPA[i] < min) {
				min = _hoops_PIPPA[i];
				i2 = i;
			}
		}
	}
	if (_hoops_HHAHR) {
		for (i = 1; i < length; i++) {
			if (_hoops_AIPPA[i1] != _hoops_PIPPA[i2])
				return false;
			i1 = (i1 == length-1 ? 1 : i1+1);
			i2 = (i2 == 1 ? length-1 : i2-1);
		}
	}
	else {
		for (i = 1; i < length; i++) {
			if (_hoops_AIPPA[i1] != _hoops_PIPPA[i2])
				return false;
			i1 = (i1 == length-1 ? 1 : i1+1);
			i2 = (i2 == length-1 ? 1 : i2+1);
		}
	}
	return true;
}

typedef VHash<POINTER_SIZED_INT, const int *> _hoops_GAAHA;
typedef VHash<const int *, POINTER_SIZED_INT> _hoops_RAAHA;

local void _hoops_ISGHA (
	_hoops_AIGPR *	_hoops_RIGC,
	struct configs *		_hoops_SHGAA,
	int						point_count, 
	Point const *			points,
	int						face_list_length, 
	int const *				face_list,
	int *					_hoops_AAAHA, 
	Point *					new_points,
	int *					_hoops_PAAHA, 
	int *					new_face_list,
	int *					_hoops_HAAHA, 
	int *					face_map)
{
	int a, b, c, i, min, _hoops_IAAHA, length;
	const int *ptr, *end, *_hoops_IIRHA = null;
	int *_hoops_CAAHA;
	_hoops_GAAHA *find;
	_hoops_RAAHA *_hoops_RRSI;
	POINTER_SIZED_INT _hoops_HGGI, _hoops_SAAHA;
	int status;
	const int *item;
	int count = 0, _hoops_GPAHA = 0;
	int _hoops_RPAHA, _hoops_APAHA, _hoops_PPAHA;
	bool _hoops_HPAHA;

	find = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_GAAHA)(_hoops_RIGC->memory_pool, face_list_length);
	_hoops_RRSI = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_RAAHA)(_hoops_RIGC->memory_pool, face_list_length);
	_hoops_PPAHA = 32 - _hoops_ARAHA (point_count);

	/* _hoops_SSS _hoops_RH _hoops_ARP _hoops_IIGR _hoops_RSSI _hoops_SGS _hoops_HS _hoops_PIS _hoops_RRGP */
	ptr = face_list;
	end = face_list + face_list_length;
	while (ptr < end) {
		_hoops_HPAHA = false;
		if (*ptr > 0)
			length = *ptr + 1;
		else
			length = -(*ptr) + 1;

		/* _hoops_SSS _hoops_RH _hoops_ISPP _hoops_GPHA _hoops_CIHA _hoops_GGR _hoops_RH _hoops_SCGR _hoops_HSP _hoops_IS _hoops_SGH _hoops_GAR _hoops_IRS _hoops_APHR _hoops_PPSR */
		min = ptr[1];
		_hoops_IAAHA = 1;
		for (i = 2; i < length; i++) {
			if (ptr[i] < min) {
				min = ptr[i];
				_hoops_IAAHA = i;
			}
		}
		a = _hoops_IAAHA;

		/* _hoops_CAHP _hoops_SIC _hoops_IH _hoops_IRS _hoops_IPAHA _hoops_CCA _hoops_HSP _hoops_PSPI _hoops_HSHPR _hoops_IS _hoops_SCGR _hoops_HSP */
		b = (a == length-1 ? 1 : a+1);
		c = (b == length-1 ? 1 : b+1);
		_hoops_HGGI = _hoops_ARGHA (ptr[a], ptr[b], ptr[c], _hoops_PPAHA);
		/* _hoops_CAHP _hoops_SIC _hoops_IH _hoops_IRS _hoops_IPAHA _hoops_CCA _hoops_HSP _hoops_PSPI _hoops_AAGIR _hoops_CSCHR _hoops_IS _hoops_SCGR _hoops_HSP */
		b = (a == 1 ? length-1 : a-1);
		c = (b == 1 ? length-1 : b-1);
		_hoops_SAAHA = _hoops_ARGHA (ptr[a], ptr[b], ptr[c], _hoops_PPAHA);
		for (i=0; !_hoops_HPAHA; i++) {
			status = find->LookupNthItem(_hoops_HGGI, i, &item);
			if (status == VHASH_STATUS_SUCCESS) {
				_hoops_IIRHA = item;
				if (_hoops_IRAHA (_hoops_IIRHA, -1, ptr, a, true)) {
					_hoops_HPAHA = true;
				}
			}
			else
				break;
		}
		for (i=0; !_hoops_HPAHA; i++) {
			status = find->LookupNthItem(_hoops_SAAHA, i, &item);
			if (status == VHASH_STATUS_SUCCESS) {
				_hoops_IIRHA = item;
				if (_hoops_IRAHA (_hoops_IIRHA, -1, ptr, a, false)) {
					_hoops_HPAHA = true;
				}
			}		
			else
				break;
		}
		if (!_hoops_HPAHA) {
			/* _hoops_GCPR _hoops_RH _hoops_SCGR _hoops_HSP _hoops_CCA _hoops_RH _hoops_GASR _hoops_HIS _hoops_SACS _hoops_ARIPR _hoops_GRS _hoops_SHH _hoops_SHSS _hoops_IS _hoops_SSS _hoops_SCH */
			find->InsertItem(_hoops_SAAHA, ptr);
		}
		else {
			_hoops_RRSI->InsertItem(ptr);
			_hoops_RRSI->InsertItem(_hoops_IIRHA);
			_hoops_GPAHA++;
		}
		ptr += length;
		count++;
	}	
	delete find;
	find = null; 

	/* _hoops_CISA _hoops_RH _hoops_CCAH _hoops_HSP _hoops_HIGR, _hoops_PSCR _hoops_RH _hoops_CCAH _hoops_PPSR _hoops_CRPR, _hoops_PPR _hoops_CISA _hoops_GGR _hoops_RH _hoops_IHHA _hoops_IIGR _hoops_GRR */
	if (new_face_list != null) {
		ptr = face_list;
		_hoops_CAAHA = new_face_list;
		_hoops_RPAHA = _hoops_APAHA = 0;
		while (ptr < end) {
			if (*ptr > 0)
				length = *ptr + 1;
			else
				length = -(*ptr) + 1;
			/* _hoops_RPP _hoops_RH _hoops_CRS _hoops_HICP _hoops_GGR _hoops_RH "_hoops_ASSI" _hoops_SCAH, _hoops_ASSI _hoops_SCH */
			if (_hoops_RRSI->LookupItem(ptr) != VHASH_STATUS_SUCCESS) {
				_hoops_AIGA (ptr, length, int, _hoops_CAAHA);
				_hoops_CAAHA += length;
				if (face_map != null)
					face_map[_hoops_APAHA] = _hoops_RPAHA;
				_hoops_RPAHA++;
			}
			else if (face_map != null)
				face_map[_hoops_APAHA] = -1;
			ptr += length;
			_hoops_APAHA++;
		}		
		if (_hoops_PAAHA != null)
			*_hoops_PAAHA = _hoops_CAAHA - new_face_list;

		if (_hoops_AAAHA != null)
			*_hoops_AAAHA = point_count; /* _hoops_GHCA _hoops_SHH _hoops_CPAHA _hoops_SPHR */

		if (new_points != null &&
			_hoops_SHGAA->_hoops_RSGHA) {
			int *_hoops_SPAHA;
			int _hoops_GHAHA = 0;  /* _hoops_RH _hoops_SPS _hoops_PPRAR _hoops_PPSR _hoops_CRSRR */

			if (_hoops_HAAHA == null)
				ALLOC_ARRAY (_hoops_SPAHA, point_count, int);
			else
				_hoops_SPAHA = _hoops_HAAHA;
			SET_MEMORY(_hoops_SPAHA, point_count * sizeof (int), -1);
			end = _hoops_CAAHA;
			_hoops_CAAHA = new_face_list;
			while (_hoops_CAAHA < end) {
				if (*_hoops_CAAHA > 0)
					length = *_hoops_CAAHA + 1;
				else
					length = -(*_hoops_CAAHA) + 1;
				for (i = 1; i < length; i++) {
					if (_hoops_SPAHA[_hoops_CAAHA[i]] >= 0) {
						/* _hoops_SR'_hoops_RISP _hoops_GCRHA _hoops_RGR _hoops_PPSR _hoops_CIHA _hoops_ARPP */
						_hoops_CAAHA[i] = _hoops_SPAHA[_hoops_CAAHA[i]];
					}
					else { 
						/* _hoops_RGR _hoops_PPSR _hoops_CIHA _hoops_HRGR _hoops_CCAH.	 _hoops_IPASR _hoops_SCH _hoops_RH _hoops_SPS _hoops_PPSR _hoops_CRSRR */
						_hoops_SPAHA[_hoops_CAAHA[i]] = _hoops_GHAHA;
						new_points[_hoops_GHAHA] = points[_hoops_CAAHA[i]];
						_hoops_CAAHA[i] = _hoops_GHAHA;
						_hoops_GHAHA++;
					}
				}
				_hoops_CAAHA += length;
			}	
			if (_hoops_AAAHA != 0)
				*_hoops_AAAHA = _hoops_GHAHA;
			if (_hoops_SPAHA != _hoops_HAAHA)
				FREE_ARRAY (_hoops_SPAHA, point_count, int);
		}
		else if (new_points != null) {
			_hoops_AIGA (points, point_count, Point, new_points);
		}
	}
	delete _hoops_RRSI;
	_hoops_RRSI = null;

} 

/* _hoops_RHAHA _hoops_SGS _hoops_RH _hoops_HSP _hoops_ICGI _hoops_PCCP _hoops_ISHA _hoops_HII _hoops_IRS _hoops_IS _hoops_RCSR */
local bool _hoops_AHAHA (int a, int b, int const *face)
{
	int i, length;
	if (*face > 0)
		length = *face;
	else
		length = -(*face);
	if (face[length] == a && face[1] == b)
		return true;
	for (i = 2; i <= length; i++) {
		if (face[i-1] == a && face[i] == b)
			return true;
	}
	return false;
}


#define _hoops_PHAHA	0
#define _hoops_HHAHA		1
#define _hoops_IHAHA	2
#define _hoops_CHAHA		3

#define _hoops_SHAHA(x) (0x1^x)	/* _hoops_PIHHR */

#define _hoops_GIAHA 256

local bool _hoops_RIAHA(
	_hoops_AIGPR *		_hoops_RIGC,
	POINTER_SIZED_INT			start,
	int const **				_hoops_AIAHA,
	_hoops_HICRA *	_hoops_PIAHA,
	char *						_hoops_HHAHR,
	int alter *					_hoops_HIAHA,
	int alter *					_hoops_IIAHA)
{
	bool status=true;
	vhash_status_t _hoops_CIAHA;
	int i, j, k, length, a, b, count;
	int const *_hoops_SIAHA;

	_hoops_IICRA *	_hoops_GCAHA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_IICRA)(_hoops_RIGC->memory_pool);

	POINTER_SIZED_INT _hoops_HGGI, _hoops_RCAHA;
	POINTER_SIZED_INT _hoops_GASI, _hoops_ACAHA, _hoops_CPCR;
	POINTER_SIZED_INT _hoops_PCAHA[_hoops_GIAHA];
	bool _hoops_HCAHA;
		
	_hoops_GCAHA->AddLast(start);

	_hoops_HHAHR[start] = _hoops_PHAHA;
	/* _hoops_IH _hoops_GRR _hoops_HSP _hoops_ICAHA _hoops_HII _hoops_RH _hoops_HSPP _hoops_PPSR _hoops_SGS _hoops_CSAP _hoops_CGI _hoops_GGR */
	while (_hoops_GCAHA->Count() > 0) {
		_hoops_CPCR = _hoops_GCAHA->RemoveFirst();
		_hoops_SIAHA = _hoops_AIAHA[_hoops_CPCR];
		if (*_hoops_SIAHA > 0)
			length = *_hoops_SIAHA;
		else
			length = -(*_hoops_SIAHA);
		/* _hoops_IH _hoops_GRR _hoops_ISHA _hoops_GGR _hoops_RH _hoops_SCGR _hoops_HSP */
		for (i = 1; i <= length; i++) {
			if (i == 1) {
				a = _hoops_SIAHA[length];
				b = _hoops_SIAHA[i];
			}
			else {
				a = _hoops_SIAHA[i-1];
				b = _hoops_SIAHA[i];
			}
			_hoops_RCAHA = _hoops_HRGHA (a, b);
			_hoops_HGGI = _hoops_HRGHA (b, a);
			count = 0;
			/* _hoops_IHSH _hoops_IH _hoops_PRRP _hoops_GRSHR _hoops_SPPR (_hoops_CSCHR _hoops_IS _hoops_RH _hoops_CISI _hoops_HSP) */
			for (;;) {
				_hoops_CIAHA = _hoops_PIAHA->RemoveItem(_hoops_HGGI, &_hoops_GASI);
				if (_hoops_CIAHA == VHASH_STATUS_FAILED)
					break;
				if (count == _hoops_GIAHA) {
					status = false;
					goto done;
				}
				_hoops_PCAHA[count++] = _hoops_GASI;
			}
			/* _hoops_IHSH _hoops_IH _hoops_CCAHA _hoops_GRSHR _hoops_SPPR (_hoops_CSCHR _hoops_IS _hoops_RH _hoops_CISI _hoops_HSP) */
			for (;;) {
				_hoops_CIAHA = _hoops_PIAHA->RemoveItem(_hoops_RCAHA, &_hoops_GASI);
				if (_hoops_CIAHA == VHASH_STATUS_FAILED)
					break;
				if (_hoops_GASI == _hoops_CPCR)
					continue;
				if (count == _hoops_GIAHA) {
					status = false;
					goto done;
				}
				_hoops_PCAHA[count++] = ~_hoops_GASI;
			}
			/* _hoops_SCAHA _hoops_GGSR _hoops_RH _hoops_RSSI _hoops_SGS _hoops_GSAHA'_hoops_RA _hoops_IGRC _hoops_APIHR (_hoops_HIH _hoops_RIAGR _hoops_RH _hoops_PSHR _hoops_SCAH _hoops_SIC */
			for (j = count-1; j >= 0; j--) {
				if (_hoops_PCAHA[j] >= 0) {
					_hoops_GASI = _hoops_PCAHA[j];
					_hoops_HCAHA = _hoops_AHAHA (b, a, _hoops_AIAHA[_hoops_GASI]);
				}
				else {
					_hoops_GASI = ~_hoops_PCAHA[j];
					_hoops_HCAHA = _hoops_AHAHA (a, b, _hoops_AIAHA[_hoops_GASI]);
				}
				if (!_hoops_HCAHA) {
					/* _hoops_RSRHR _hoops_SCH _hoops_ISSC _hoops_CRGR _hoops_RH _hoops_ICGAR */
					if (_hoops_PCAHA[j] < 0)
						_hoops_PIAHA->InsertItem(_hoops_RCAHA, _hoops_GASI);
					else
						_hoops_PIAHA->InsertItem(_hoops_HGGI, _hoops_GASI);
					if (j < count - 1)
						_hoops_PCAHA[j] = _hoops_PCAHA[count-1];
					count--;
				}
			}
			/* _hoops_IHSH _hoops_IH _hoops_SSRS _hoops_RSSI _hoops_RSAHA _hoops_RH _hoops_ASAHA */
			for (j = count-1; j >= 1; j--) {
				if (_hoops_PCAHA[j] >= 0)
					_hoops_GASI = _hoops_PCAHA[j];
				else
					_hoops_GASI = ~_hoops_PCAHA[j];
				if (_hoops_HHAHR[_hoops_GASI] == _hoops_CHAHA)
					continue;
				for (k = j-1; k >= 0; k--) {
					if (_hoops_PCAHA[k] >= 0)
						_hoops_ACAHA = _hoops_PCAHA[k];
					else
						_hoops_ACAHA = ~_hoops_PCAHA[k];
					if (_hoops_HHAHR[_hoops_ACAHA] == _hoops_CHAHA)
						continue;
					/* _hoops_RPP _hoops_HRASR _hoops_IIGR _hoops_PSAHA[_hoops_PPHR] _hoops_HRGR _hoops_HAR _hoops_PSHR _hoops_GAR _hoops_HRASR _hoops_IIGR _hoops_PSAHA[_hoops_ARGI], 
						_hoops_SSIA _hoops_CHR _hoops_AAGIR _hoops_CSCHR _hoops_IS _hoops_GRR _hoops_RII */
					if (_hoops_IRAHA (_hoops_AIAHA[_hoops_GASI], -1, _hoops_AIAHA[_hoops_ACAHA], -1, 
							((_hoops_PCAHA[j] >= 0) != (_hoops_PCAHA[k] >= 0)))
					) {
						(*_hoops_IIAHA)++;
						count--;
						/* _hoops_SSRS _hoops_HSP _hoops_AASAR.	 _hoops_CSHA _hoops_IISA _hoops_SRS _hoops_GGR _hoops_HSP _hoops_HIGR _hoops_AGGRA */
						if (_hoops_AIAHA[_hoops_GASI] > _hoops_AIAHA[_hoops_ACAHA]) {
							_hoops_HHAHR[_hoops_GASI] = _hoops_CHAHA;
							_hoops_PCAHA[j] = _hoops_PCAHA[count];
							break; /* _hoops_SPS _hoops_PPHR */
						}
						else {
							_hoops_HHAHR[_hoops_ACAHA] = _hoops_CHAHA;
							_hoops_PCAHA[k] = _hoops_PCAHA[count];
							continue; /* _hoops_SPS _hoops_ARGI */
						}
					}
				}
			}
			for (j = count-1; j >= 0; j--) {
				if (_hoops_PCAHA[j] >= 0)
					_hoops_GASI = _hoops_PCAHA[j];
				else
					_hoops_GASI = ~_hoops_PCAHA[j];
				if (_hoops_HHAHR[_hoops_GASI] == _hoops_CHAHA)
					continue;
				if (_hoops_IRAHA (_hoops_AIAHA[_hoops_GASI], -1, _hoops_SIAHA, -1, (_hoops_PCAHA[j] >= 0))) {
					(*_hoops_IIAHA)++;
					count--;
					_hoops_HHAHR[_hoops_GASI] = _hoops_CHAHA;
					_hoops_PCAHA[j] = _hoops_PCAHA[count];
				}
			}
			/* _hoops_RGAR _hoops_SHGR _hoops_ARHI _hoops_SPPR _hoops_SGS _hoops_CHR _hoops_PSHS _hoops_GPCPR _hoops_RRPC 
			   (_hoops_ISAP _hoops_IGS _hoops_PAR _hoops_HSAHA) _hoops_HIH _hoops_HAR _hoops_RPP _hoops_SR'_hoops_RISP _hoops_ISAHA _hoops_RH _hoops_GIGR _hoops_GAR _hoops_IRS _hoops_ARHAR */
			if (count == 1 && _hoops_HHAHR[_hoops_GASI] != _hoops_CHAHA) {
				if (_hoops_PCAHA[0] >= 0)
					_hoops_GASI = _hoops_PCAHA[0];
				else
					_hoops_GASI = ~_hoops_PCAHA[0];
				if (_hoops_HHAHR[_hoops_GASI] == _hoops_IHAHA) {
					_hoops_GCAHA->AddLast(_hoops_GASI);
					if (_hoops_PCAHA[0] >= 0)
						_hoops_HHAHR[_hoops_GASI] = _hoops_HHAHR[_hoops_CPCR];
					else
						_hoops_HHAHR[_hoops_GASI] = _hoops_SHAHA(_hoops_HHAHR[_hoops_CPCR]);
					if (_hoops_HHAHR[_hoops_GASI])
						(*_hoops_HIAHA)++;
				}
			}
		}
	}
  done:

	delete _hoops_GCAHA;

	return status;
}


local void _hoops_CSAHA (int alter *_hoops_SIAHA) 
{
	int *first, *_hoops_SSAC;
	int length, temp;

	if (*_hoops_SIAHA > 0)
		length = *_hoops_SIAHA;
	else
		length = -(*_hoops_SIAHA);
	first = _hoops_SIAHA + 1;
	_hoops_SSAC = _hoops_SIAHA + length;
	while (first < _hoops_SSAC) {
		temp = *first;
		*first = *_hoops_SSAC;
		*_hoops_SSAC = temp;
		first++;
		_hoops_SSAC--;
	}
}


local void _hoops_SSAHA (int const *in, int alter *_hoops_PAGR) 
{
	int length, i;

	if (*in > 0)
		length = *in;
	else
		length = -(*in);
	_hoops_PAGR[0] = in[0];
	for (i = 0; i < length; i++)
		_hoops_PAGR[1+i] = in[length-i];
}


local void _hoops_HICPA (
	_hoops_AIGPR *	_hoops_RIGC,
	struct configs *		_hoops_SHGAA,
	int						point_count, 
	Point const *			points,
	int						face_list_length, 
	int const *				face_list,
	int *					_hoops_AAAHA, 
	Point *					new_points,
	int *					_hoops_PAAHA, 
	int *					new_face_list,
	int *					_hoops_HAAHA, 
	int *					face_map)
{
	POINTER_SIZED_INT id;
	int i, length;
	int face_count;

	char *_hoops_HHAHR;			/* _hoops_IH _hoops_GRR _hoops_HSP _hoops_CRSRR, _hoops_SPR _hoops_IIGR _hoops_HRSP _hoops_AAIP: _hoops_GGPHA, _hoops_RGPHA, _hoops_PAR _hoops_AGPHA */
	int const **_hoops_AIAHA;	/* _hoops_IH _hoops_GRR _hoops_HSP _hoops_CRSRR, _hoops_RH _hoops_CRS _hoops_IS _hoops_RH _hoops_ACAGR _hoops_GIAA _hoops_RH _hoops_HSP _hoops_HIGR _hoops_HPGR _hoops_PGAP _hoops_SCH _hoops_RRGPR*/
	int _hoops_HIAHA = 0, _hoops_IIAHA = 0; 
	POINTER_SIZED_INT _hoops_HGGI;
	int const *ptr, *end;
	char _hoops_PGPHA;
	int alter *_hoops_CAAHA;

	/* _hoops_IH _hoops_GRR _hoops_ISHA, _hoops_RH _hoops_CRSRR _hoops_IIGR _hoops_RH _hoops_HSP _hoops_IS _hoops_PGAP _hoops_SCH _hoops_HGPHA */
	_hoops_HICRA *	_hoops_PIAHA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_HICRA)(_hoops_RIGC->memory_pool, face_list_length*3);

	ptr = face_list;
	end = face_list + face_list_length;
	id = 0;
	/* _hoops_RIPHR _hoops_GH _hoops_RH _hoops_IGPHA _hoops_SCAH */
	while (ptr < end) {
		if (*ptr > 0)
			length = *ptr;
		else
			length = -(*ptr);
		for (i = 1; i <= length; i++) {
			if (i == 1)
				_hoops_HGGI = _hoops_HRGHA (ptr[length], ptr[i]);
			else
				_hoops_HGGI = _hoops_HRGHA (ptr[i-1], ptr[i]);
			_hoops_PIAHA->InsertItem(_hoops_HGGI, id);
		}
		id++;
		ptr += length + 1;
	}
	face_count = id;

	/* _hoops_RIPHR _hoops_GH _hoops_RH _hoops_CGPHA _hoops_IHSH _hoops_GH _hoops_GASR */
	ALLOC_ARRAY (_hoops_AIAHA, face_count, const int *);
	ptr = face_list;
	for (id = 0; id < face_count; id++) {
		if (*ptr > 0)
			length = *ptr;
		else
			length = -(*ptr);
		_hoops_AIAHA[id] = ptr;
		ptr += length + 1;
	}

	_hoops_HIAHA = 0;
	_hoops_IIAHA = 0;
	ALLOC_ARRAY (_hoops_HHAHR, face_count, char);
	SET_MEMORY (_hoops_HHAHR, face_count * sizeof(char), _hoops_IHAHA);
	for (id = 0; id < face_count; id++) {
		if (_hoops_HHAHR[id] == _hoops_IHAHA)
			_hoops_RIAHA (_hoops_RIGC, id, _hoops_AIAHA, _hoops_PIAHA, _hoops_HHAHR, &_hoops_HIAHA, &_hoops_IIAHA);
	}
	if (_hoops_HIAHA > face_count/2) /* _hoops_SGPHA _hoops_AGGRA */
		_hoops_PGPHA = _hoops_PHAHA;
	else
		_hoops_PGPHA = _hoops_HHAHA;

	if (face_list == new_face_list) {
		/* _hoops_RPP _hoops_SR _hoops_HS _hoops_RPII _hoops_SSGRR _hoops_IS _hoops_GRPHA _hoops_RH _hoops_HSP _hoops_HIGR */
		_hoops_CAAHA = new_face_list;
		for (id = 0; id < face_count; id++) {
			if (*_hoops_CAAHA > 0)
				length = *_hoops_CAAHA;
			else
				length = -(*_hoops_CAAHA);
			if (_hoops_HHAHR[id] == _hoops_PGPHA)
				_hoops_CSAHA (_hoops_CAAHA);
			_hoops_CAAHA += length + 1;
		}
	}
	else {
		/* _hoops_RPP _hoops_SR _hoops_HS _hoops_RPII _hoops_SSGRR _hoops_IS _hoops_IPS _hoops_RH _hoops_CCAH _hoops_HSP _hoops_HIGR _hoops_CRGR _hoops_IRS _hoops_CASI _hoops_CRPR */
		ptr = face_list;
		_hoops_CAAHA = new_face_list;
		for (id = 0; id < face_count; id++) {
			if (*ptr > 0)
				length = *ptr;
			else
				length = -(*ptr);
			if (_hoops_HHAHR[id] == _hoops_PGPHA)
				_hoops_SSAHA (ptr, _hoops_CAAHA);
			else
				memcpy (_hoops_CAAHA, ptr, (length+1) * sizeof(int));
			ptr += length + 1;
			_hoops_CAAHA += length + 1;
		}
	}
	if (_hoops_IIAHA != 0) {
		ptr = new_face_list;
		_hoops_CAAHA = new_face_list;
		for (id = 0; id < face_count; id++) {
			if (*ptr > 0)
				length = *ptr;
			else
				length = -(*ptr);
			if (ptr != _hoops_CAAHA)
				memcpy (_hoops_CAAHA, ptr, (length+1) * sizeof(int));
			ptr += length + 1;
			if (_hoops_HHAHR[id] != _hoops_CHAHA)
				_hoops_CAAHA += length + 1;
		}
		if (_hoops_PAAHA != null)
			*_hoops_PAAHA = (_hoops_CAAHA - new_face_list);
	}
	else if (_hoops_PAAHA != null)
		*_hoops_PAAHA = face_list_length;

	delete _hoops_PIAHA;
	FREE_ARRAY (_hoops_AIAHA, face_count, int *);

	if (_hoops_AAAHA != null)
		*_hoops_AAAHA = point_count;

	if (_hoops_HAAHA != null) {
		for (i = 0; i < point_count; i++) {
			_hoops_HAAHA[i] = i;
		}
	}
	if (face_map != null) {
		id=0;
		for (i = 0; i < face_count; i++) {
			if (_hoops_HHAHR[i] != _hoops_CHAHA)
				face_map[i] = id++;
			else
				face_map[i] = _hoops_ACGHA;
		}
	}
	if (new_points && new_points != points) 
		_hoops_AIGA (points, point_count, Point, new_points);

	FREE_ARRAY (_hoops_HHAHR, face_count, char);

	UNREFERENCED (_hoops_SHGAA);

} /* _hoops_RSGR _hoops_API _hoops_CCIH */

#endif


GLOBAL_FUNCTION void HI_Compute_LOD(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_RRPHA _hoops_ARPHA,
	float _hoops_PRPHA,
	bool _hoops_HRPHA,
	int pcount, const float *points,
	int _hoops_IRPHA, const int *_hoops_ASPH,
	int *_hoops_CRPHA, float *_hoops_SRPHA, 
	int *_hoops_GAPHA, int *_hoops_RAPHA,
	int *_hoops_AAPHA, int *_hoops_PAPHA) 
{
#ifndef DISABLE_LOD_GENERATION
	_hoops_HAPHA *node;

	UNREFERENCED(_hoops_PAPHA);

	if (_hoops_IRPHA == 0) {
		*_hoops_CRPHA = int (pcount * _hoops_PRPHA);
		HI_Median_Cut (_hoops_RIGC, pcount, (Point const *)points, null, *_hoops_CRPHA, (Point *)_hoops_SRPHA, null, _hoops_AAPHA);
	}
	else if (_hoops_ARPHA == _hoops_SPGHA) {
		node = HI_Compute_LOD_Fast (pcount, points, _hoops_IRPHA, _hoops_ASPH, _hoops_PRPHA, 1);

		*_hoops_CRPHA = node->_hoops_IAPHA.pcount;
		*_hoops_GAPHA = node->_hoops_IAPHA._hoops_RHGIR;
		_hoops_AIGA (node->_hoops_IAPHA.points, node->_hoops_IAPHA.pcount, Point, _hoops_SRPHA);
		if (_hoops_RAPHA != null)
			_hoops_AIGA (node->_hoops_IAPHA.faces, node->_hoops_IAPHA._hoops_RHGIR, int, _hoops_RAPHA);
		if (node->_hoops_IAPHA.points != null)
			FREE_ARRAY_ALIGNED (node->_hoops_IAPHA.points, 3 * node->_hoops_IAPHA.pcount, float, 16);
		if (node->_hoops_IAPHA.faces != null)
			FREE_ARRAY (node->_hoops_IAPHA.faces, node->_hoops_IAPHA._hoops_RHGIR, int);
		if (_hoops_AAPHA != null)
			_hoops_AIGA (node->_hoops_PHAS, node->_hoops_CAPHA, int, _hoops_AAPHA);
		if (node->_hoops_PHAS != null)
			FREE_ARRAY (node->_hoops_PHAS, node->_hoops_CAPHA, int);
		FREE (node, _hoops_HAPHA);
	} 
	else {
		_hoops_SAPHA _hoops_GPPHA;
		int *_hoops_GAHI, *_hoops_ICGCR;
		Polyhedron *phon;
		int *_hoops_RPPHA = null;
		int _hoops_APPHA = HOOPS_WORLD->_hoops_HGGHR;

		_hoops_GPPHA._hoops_PPPHA = _hoops_SGRHA;
		_hoops_GPPHA._hoops_HPPHA = _hoops_SGRHA;
		_hoops_GPPHA._hoops_IPPHA	 = (float)_hoops_SGRHA;
		_hoops_GPPHA._hoops_CPPHA= (float)_hoops_SGRHA;
		_hoops_GPPHA._hoops_SPPHA	 = (float)_hoops_SGRHA;
		_hoops_GPPHA._hoops_GHPHA	 = _hoops_SGRHA;
		_hoops_GPPHA._hoops_RHPHA		 = _hoops_SGRHA;
		_hoops_GPPHA._hoops_PRPHA = _hoops_PRPHA;

		Shell *		_hoops_SPHPR;
		ZALLOC(_hoops_SPHPR, Shell);

		phon = (Polyhedron *)_hoops_SPHPR;
		phon->type = _hoops_SCIP;

		phon->point_count = pcount;
		ALLOC_ARRAY_ALIGNED (phon->points, phon->point_count, Point, 16);
		_hoops_SPHPR->face_list_length = _hoops_IRPHA;
		ALLOC_ARRAY (_hoops_SPHPR->face_list, _hoops_SPHPR->face_list_length, int);

		/* _hoops_IGIPR _hoops_SGS _hoops_PIASR _hoops_AAHP (_hoops_AHPHA _hoops_PPR _hoops_ASGA) _hoops_IH _hoops_GHRHA _hoops_HRGR 0 */
		if (_hoops_HRPHA) {
			ALLOC_ARRAY (_hoops_RPPHA, pcount, int);
			HI_Compute_Optimized_Shell(_hoops_RIGC,
				pcount, (const Point *)points, null,
				_hoops_IRPHA, _hoops_ASPH,
				"",
				&phon->point_count, phon->points,
				&_hoops_SPHPR->face_list_length, _hoops_SPHPR->face_list,
				_hoops_RPPHA, null
			);
		}
		else {
			phon->point_count = pcount;
			_hoops_AIGA (points, pcount, Point, phon->points);
			_hoops_SPHPR->face_list_length = _hoops_IRPHA;
			_hoops_AIGA (_hoops_ASPH, _hoops_IRPHA, int, _hoops_SPHPR->face_list);
		}
		/* _hoops_PHPHA _hoops_PIH _hoops_HHPHA _hoops_GAR _hoops_AIPH */
		_hoops_SPHPR->_hoops_GRCPR = null;
		_hoops_SPHPR->_hoops_HHHPR = null;
		_hoops_SPHPR->_hoops_SGCPR = null;
		/* _hoops_HRHPA _hoops_RH _hoops_HSP _hoops_RPR */
		phon->face_count = 0;
		_hoops_ICGCR = _hoops_SPHPR->face_list + _hoops_SPHPR->face_list_length;
		for (_hoops_GAHI = _hoops_SPHPR->face_list; _hoops_GAHI < _hoops_ICGCR;) {
			if (*_hoops_GAHI > 0) {
				_hoops_GAHI += *_hoops_GAHI + 1;
				phon->face_count++;
			}
			else
				/* _hoops_IHPHA _hoops_IIGR (_hoops_RCCPR _hoops_CHPHA _hoops_GGR) _hoops_PGHC _hoops_HSP */
				_hoops_GAHI += -(*_hoops_GAHI) + 1;
		}
		phon->tristrips = null;
		phon->_hoops_ACRHR = 0;
		HOOPS_WORLD->_hoops_HGGHR &= ~_hoops_SRRIR;
		HI_Assemble_3D_Tristrips  (phon, (_hoops_SARHR)~0, false);	/* _hoops_RARIR _hoops_HCR, _hoops_PSP _hoops_ASGA */
		HOOPS_WORLD->_hoops_HGGHR = _hoops_APPHA;

		node = HI_LOD_Chain_Execute_Tristrips (phon->point_count, 
											   (float *)phon->points,
												phon->tristrips,
												&_hoops_GPPHA, 1);
		*_hoops_CRPHA = node->_hoops_IAPHA.pcount;
		*_hoops_GAPHA = node->_hoops_IAPHA._hoops_RHGIR;
		_hoops_AIGA (node->_hoops_IAPHA.points, node->_hoops_IAPHA.pcount, Point, _hoops_SRPHA);
		if (_hoops_RAPHA != null)
			_hoops_AIGA (node->_hoops_IAPHA.faces, node->_hoops_IAPHA._hoops_RHGIR, int, _hoops_RAPHA);
		if (_hoops_AAPHA != null) {
			if (_hoops_RPPHA != null) {
				for (int i = 0; i < pcount; i++) {
					if (_hoops_RPPHA[i] >= 0)
						_hoops_AAPHA[i] = node->_hoops_PHAS[_hoops_RPPHA[i]];
					else
						_hoops_AAPHA[i] = _hoops_RPPHA[i];
				}
			}
			else
				_hoops_AIGA (node->_hoops_PHAS, node->_hoops_CAPHA, int, _hoops_AAPHA);
		}
		if (node->_hoops_IAPHA.points != null)
			FREE_ARRAY_ALIGNED (node->_hoops_IAPHA.points, 3 * node->_hoops_IAPHA.pcount, float, 16);
		if (node->_hoops_IAPHA.faces != null)
			FREE_ARRAY (node->_hoops_IAPHA.faces, node->_hoops_IAPHA._hoops_RHGIR, int);
		if (node->_hoops_PHAS != null)
			FREE_ARRAY (node->_hoops_PHAS, node->_hoops_CAPHA, int);
		if (_hoops_RPPHA != null)
			FREE_ARRAY (_hoops_RPPHA, pcount, int);
		FREE (node, _hoops_HAPHA);
		phon->point_count = pcount;
		_hoops_SPHPR->face_list_length = _hoops_IRPHA;
		HI_Au_Revoir ((_hoops_HPAH *) phon);
	}
#endif /* _hoops_SHPHA*/
} 


GLOBAL_FUNCTION void HI_Compute_Optimized_Shell (
	_hoops_AIGPR *	_hoops_RIGC,
	int				in_point_count,
	Point const	*	in_points,
	Vector const *	_hoops_ISHRA,
	int				in_face_list_length,
	int const *		in_face_list,

	char const *	option_string,

	int *			out_point_count,
	Point *			out_points,
	int *			out_face_list_length,
	int	*			out_face_list,

	int	*			vertex_mapping,
	int	*			face_mapping) 
{
	struct configs	config;
	int				_hoops_GIPHA;

	/* _hoops_CACH _hoops_AHAC _hoops_GGR _hoops_RH _hoops_IRGH _hoops_API, _hoops_RIPHA, 
	 * _hoops_IH _hoops_PCCP _hoops_AIPHA _hoops_IIGR _hoops_RH _hoops_AIRHA _hoops_RHPC _hoops_CAPP */

	int	(HC_CDECL * collapsible)(
			void *pts,
			void *_hoops_PARHA,
			Integer32 a,
			Integer32 b,
			double _hoops_HARHA,
			double _hoops_IARHA);

	if (in_point_count == 0 && in_face_list_length == 0) {
		*out_point_count = 0;
		*out_face_list_length = 0;
		return;
	}

	if (!_hoops_CHGAA (_hoops_RIGC, option_string, &config))
		return;

	if (in_point_count < 0) {
		HE_ERROR (HEC_COMPUTE, HES_INVALID_COUNT, "Negative number of points given to Compute_Optimized_Shell");
		return;
	}

	if (in_face_list_length < 0) {
		HE_ERROR (HEC_COMPUTE, HES_INVALID_COUNT, "Negative number of faces given to Compute_Optimized_Shell");
		return;
	}

	if (in_face_list_length == 0 &&
		config._hoops_PCGHA == _hoops_SRGHA) {
		HE_ERROR (HEC_COMPUTE, HES_INVALID_OPTION, "Can't use \"feature relative units\" with no faces defined");
		return;
	}

	if (in_face_list_length == 0 &&
		config._hoops_RSGHA) {
		HE_ERROR (HEC_COMPUTE, HES_INVALID_OPTION, "Can't use \"orphan elimination\" with no faces defined");
		return;
	}


	/* _hoops_RPGP _hoops_IH _hoops_IRS _hoops_IPSP-_hoops_PAPR _hoops_HRRHA _hoops_CAPGR _hoops_RPGP (_hoops_CCGHA _hoops_IRGHA)*/
	config._hoops_SCGHA = (void *)in_points;
	config._hoops_GSGHA = (void *)_hoops_ISHRA;
	if (config.collapsible == null)
		collapsible = _hoops_IGAHA;
	else
		collapsible = (int (HC_CDECL *) (void *pts,
									  void *_hoops_PARHA,
									  Integer32 a,
									  Integer32 b,
									  double _hoops_HARHA,
									  double _hoops_IARHA))
							config.collapsible->address;

	_hoops_GIPHA = 0;
	if (config._hoops_PRSI)
		_hoops_GIPHA++;
	if (config._hoops_ISGHA)
		_hoops_GIPHA++;
	if (config._hoops_HICPA)
		_hoops_GIPHA++;
	if (_hoops_GIPHA > 1) {
		HE_ERROR (HEC_COMPUTE, HES_INVALID_OPTION,
				 "\"skin\", \"lod\" and \"fix handedness\" options to HC_Compute_Optimized_Shell are mutually exclusive.  "
				 "Please choose one or the other.");
		return;
	}

	if (config._hoops_PRSI) {
		HI_Compute_LOD (_hoops_RIGC,
			config._hoops_ASGHA,
			config._hoops_PSGHA, 
			true,
			in_point_count, (const float *) in_points,
			in_face_list_length, in_face_list,
			out_point_count, (float *) out_points,
			out_face_list_length, out_face_list,
			vertex_mapping, face_mapping
		);
	}
	else
	if (config._hoops_ISGHA) {
		_hoops_ISGHA (_hoops_RIGC,
			&config,
			in_point_count, in_points,
			in_face_list_length, in_face_list,
			out_point_count, out_points,
			out_face_list_length, out_face_list,
			vertex_mapping, face_mapping
		);

	}
	else if (config._hoops_HICPA) {
		_hoops_HICPA (_hoops_RIGC,
			&config,
			in_point_count, in_points,
			in_face_list_length, in_face_list,
			out_point_count, out_points,
			out_face_list_length, out_face_list,
			vertex_mapping, face_mapping
		);

	}
	else {
		compute_optimized_shell (
			in_point_count, in_points, _hoops_ISHRA,
			in_face_list_length, in_face_list,
			collapsible,
			&config,
			out_point_count, out_points,
			out_face_list_length, out_face_list,
			vertex_mapping, face_mapping
		);
	}

} 


HC_INTERFACE void HC_CDECL HC_Compute_Optimized_Shell (
	int				in_point_count,
	Point const	*	in_points,
	Vector const *	_hoops_ISHRA,
	int				in_face_list_length,
	int const *		in_face_list,

	char const *	option_string,

	int *			out_point_count,
	Point *			out_points,
	int *			out_face_list_length,
	int	*			out_face_list,

	int	*			vertex_mapping,
	int	*			face_mapping) 
{
	_hoops_PAPPR context("Compute_Optimized_Shell");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Optimized_Shell () */\n");
	);

	HI_Compute_Optimized_Shell (context,
		in_point_count,
		in_points,
		_hoops_ISHRA,
		in_face_list_length,
		in_face_list,
		option_string,
		out_point_count,
		out_points,
		out_face_list_length,
		out_face_list,
		vertex_mapping,
		face_mapping);

#endif
} 


struct _hoops_PIPHA{
	int *		_hoops_HCGPA;
	int			_hoops_HIPHA;
	int			_hoops_ICGH;
};

local void _hoops_IIPHA (
	void *						info,
	Integer32				_hoops_HAPH,
	Integer32				_hoops_ISPI,
	Integer32				_hoops_CSPI,
	Integer32				_hoops_SSPI) {
	struct _hoops_PIPHA *			data = (struct _hoops_PIPHA *)info;

	UNREFERENCED (_hoops_HAPH);

	/* _hoops_RPP _hoops_CRPR _hoops_PRCH _hoops_GRS _hoops_SHH _hoops_CIPHA, _hoops_SIPHA */
	if (data->_hoops_HIPHA + 4 >= data->_hoops_ICGH) {
		/* _hoops_GRHP _hoops_IHGC _hoops_IIGR _hoops_RHGS _hoops_PIH, _hoops_CCPP _hoops_CCAH _hoops_PPGS, _hoops_IPS _hoops_PPGS _hoops_IAPR, _hoops_CIH _hoops_RHGS _hoops_PIH */
		int *temp = data->_hoops_HCGPA;
		ALLOC_ARRAY (data->_hoops_HCGPA, 2 * data->_hoops_ICGH, int);
		_hoops_AIGA (temp, data->_hoops_ICGH, int, data->_hoops_HCGPA);
		FREE_ARRAY (temp, data->_hoops_ICGH, int);
		data->_hoops_ICGH *= 2;
	}

	data->_hoops_HCGPA[data->_hoops_HIPHA] = 3;
	data->_hoops_HCGPA[data->_hoops_HIPHA+1] = _hoops_ISPI;
	data->_hoops_HCGPA[data->_hoops_HIPHA+2] = _hoops_CSPI;
	data->_hoops_HCGPA[data->_hoops_HIPHA+3] = _hoops_SSPI;

	data->_hoops_HIPHA += 4;
}


HC_INTERFACE void HC_CDECL HC_Compute_Triangulation (
	Point const			*in_points,
	int						in_face_list_length,
	int const				*in_face_list,
	int						*_hoops_GCPHA,
	int						*_hoops_RCPHA) {
	int const				*global_end = in_face_list + in_face_list_length;
	struct _hoops_PIPHA			data;

	/* _hoops_RASR _hoops_PIH _hoops_HRPR */
	data._hoops_HIPHA = 0;
	data._hoops_ICGH = 1024;
	ALLOC_ARRAY (data._hoops_HCGPA, data._hoops_ICGH, int);

	do {
		int const *				_hoops_CRRHR = in_face_list + 1 + *in_face_list;

		/* _hoops_HSGR _hoops_ISGR _hoops_ARAH-_hoops_RSSI */
		while (_hoops_CRRHR != global_end && *_hoops_CRRHR < 0)
			_hoops_CRRHR += 1 - *_hoops_CRRHR;

		HI_Triangulate_Face (in_points, null,
							 in_face_list, _hoops_CRRHR,
							 _hoops_IIPHA, (void *)&data);

		in_face_list = _hoops_CRRHR;
	} while (in_face_list != global_end);

	if (_hoops_GCPHA != null)
		*_hoops_GCPHA = data._hoops_HIPHA;

	if (_hoops_RCPHA != null)
		_hoops_AIGA (data._hoops_HCGPA, data._hoops_HIPHA, int, _hoops_RCPHA);

	FREE_ARRAY (data._hoops_HCGPA, data._hoops_ICGH, int);
}

HC_INTERFACE void HC_CDECL HC_Compute_Triangulation_Size (
	Point const			*in_points,
	int						in_face_list_length,
	int const				*in_face_list,
	int						*_hoops_GCPHA) {

	HC_Compute_Triangulation (in_points, in_face_list_length, in_face_list, _hoops_GCPHA, null);
}

inline local void _hoops_ACPHA(int _hoops_PCPHA, int * _hoops_HCPHA, int * face_indices)
{
	int _hoops_PHHHR=0, index=0, _hoops_HHHHR;
	
	if(!_hoops_PCPHA)
		return;

	while(index < _hoops_PCPHA)
	{
		face_indices[_hoops_PHHHR++] = index;
		_hoops_HHHHR = _hoops_HCPHA[index];
		if(_hoops_HHHHR < 0) _hoops_HHHHR = -_hoops_HHHHR;
		index+=_hoops_HHHHR+1;
	}

}

HC_INTERFACE Key HC_CDECL HC_Compute_Subshell ( 
	Key			_hoops_ICPHA,
	int			keep_fcount, 
	const int *	keep_faces,
	int			keep_pcount, 
	const int *	keep_pts1, 
	const int *	keep_pts2,
	int *		face_map, 
	int *		pts_map)
{
	_hoops_PAPPR context("Compute_Subshell");

	if (keep_fcount == 0 && keep_pcount ==0) {
		HE_WARNING (HEC_TRISTRIP, HES_INVALID_NUMBER, "Cannot create empty subshell.");
		return -1;
	}

	CODE_GENERATION (
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		if(keep_fcount)	{
			int	count1 = keep_fcount;
			HI_Dump_Code (Sprintf_D (null, "int* faces = (int*) malloc(sizeof(int)*%d);\n", count1));
			_hoops_RGGA (count1-- == 0) {
				HI_Dump_Code (Sprintf_DD (null, "faces[%d] = %d;\n", count1, keep_faces[count1]));
			}
		}
		if(keep_pcount)	{
			int		count2 = keep_pcount;
			HI_Dump_Code (Sprintf_D (null, "int* points = (int*) malloc(sizeof(int)*%d);\n", count2));
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (Sprintf_DD (null, "points[%d] = %d;\n", count2, keep_pts1[count2]));
			}
		}
		if(keep_pts2)	{
			int		count2 = keep_pcount;
			HI_Dump_Code (Sprintf_D (null, "int* points2 = (int*) malloc(sizeof(int)*%d);\n", count2));
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (Sprintf_DD (null, "points2[%d] = %d;\n", count2, keep_pts2[count2]));
			}
		}

		HI_Dump_Code (Sprintf_LD (null, "HC_Compute_Subshell (LOOKUP (%D), ", _hoops_ICPHA));
		if(keep_fcount)
			HI_Dump_Code (Sprintf_D (null, "%d, faces, ", keep_fcount));
		else 
			HI_Dump_Code ("0, 0, ");
		if(keep_pcount)
			HI_Dump_Code (Sprintf_D (null, "%d, points, ", keep_pcount));
		else 
			HI_Dump_Code ("0, 0, ");
		if(keep_pts2)
			HI_Dump_Code ("points2, ");
		else 
			HI_Dump_Code ("0, ");
		
		//_hoops_PS _hoops_GA'_hoops_RA _hoops_RGHH _hoops_GGI-_hoops_ISSC _hoops_HSH
		HI_Dump_Code ("0, 0);\n");
		if(keep_fcount)
			HI_Dump_Code ("free (faces);\n");
		if(keep_pcount)
			HI_Dump_Code ("free (points);\n");
		if(keep_pts2)
			HI_Dump_Code ("free (points2);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	// _hoops_GIIC-_hoops_CRGP _hoops_HPHS _hoops_HII _hoops_HCGP _hoops_CPAP
	int _hoops_CCPHA;
	int _hoops_SCPHA;

	// _hoops_GSPHA _hoops_IH _hoops_CCAH _hoops_CPAP
	int		_hoops_RSPHA = 0;
	int		* _hoops_ASPHA;	
	int		_hoops_PSPHA = 0;
	int		new_pcount = 0;
	Point		* _hoops_HSPHA;		
	Key		_hoops_PGRAA = -1;
	Vector * _hoops_IRPA;
	int 	_hoops_ISPHA;
	int		i, j;

	// _hoops_GACS
	int *	_hoops_CSPHA;
	int *	_hoops_SSPHA;


	_hoops_RPPPR();

	Polyhedron * source = (Polyhedron *)_hoops_RCSSR(context, _hoops_ICPHA);

	if (source == null || 
		(source->type != _hoops_SCIP && source->type != _hoops_GSIP) ||
		BIT (source->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_KEY, "Key does not refer to a valid shell or mesh");
		goto Release;
	}

	if(source->type == _hoops_SCIP) {
		Shell * _hoops_GGHHA = (Shell *)source;
		_hoops_CCPHA = _hoops_GGHHA->face_count;
		_hoops_SCPHA = _hoops_GGHHA->face_list_length;
		_hoops_ISPHA = _hoops_GGHHA->face_list_length + (keep_pts2 ? 3*keep_pcount : 0);
	}
	else /* _hoops_RPP(_hoops_HCGP->_hoops_GPRR == _hoops_GSHPR) */ {
		_hoops_CCPHA = 2 * (((_hoops_AIHPR *)source)->rows - 1) * (((_hoops_AIHPR *)source)->columns - 1);
		_hoops_SCPHA = 4 * source->point_count;
		_hoops_ISPHA = _hoops_SCPHA;
	}

	ALLOC_ARRAY_ALIGNED(_hoops_HSPHA, source->point_count, Point, 16);
	if(_hoops_ISPHA)
		ALLOC_ARRAY(_hoops_ASPHA, _hoops_ISPHA, int);
	else
		_hoops_ASPHA = null;
	if(source->type == _hoops_GSIP ||
		(source->type == _hoops_SCIP && ((Shell *)source)->face_count) )
		ALLOC_ARRAY(_hoops_CSPHA, _hoops_CCPHA, int);
	else
		_hoops_CSPHA = null;
	ALLOC_ARRAY(_hoops_SSPHA, source->point_count, int);

	// _hoops_HSPC _hoops_ACAR
	if(_hoops_CCPHA)
		for(i=0; i<_hoops_CCPHA; ++i)
			_hoops_CSPHA[i]=-1;

	for(i=0; i<source->point_count; ++i)
		_hoops_SSPHA[i]=-1;

	// _hoops_GSCA _hoops_RSSA
	if(keep_pcount>0 && keep_pts1) {
		for(i=0; i<keep_pcount; ++i) {
			if(keep_pts1[i]==-1)
				break;

			if(_hoops_SSPHA[keep_pts1[i]]==-1) {
				_hoops_HSPHA[new_pcount]=source->points[keep_pts1[i]];
				_hoops_SSPHA[keep_pts1[i]]=new_pcount++;
			}
			
			//_hoops_RGHH _hoops_SPPR
			if(keep_pts2 && keep_pts2[i]>=0) {
				if(_hoops_SSPHA[keep_pts2[i]]==-1) {
					_hoops_HSPHA[new_pcount]=source->points[keep_pts2[i]];
					_hoops_SSPHA[keep_pts2[i]]=new_pcount++;
				}

				//_hoops_GGCR _hoops_IRS _hoops_ARHAR _hoops_HSP-_hoops_HIGR _hoops_RARP
				if(_hoops_RSPHA+3 >= _hoops_ISPHA) {
					int * _hoops_RGHHA = 0;
					ALLOC_ARRAY(_hoops_RGHHA, _hoops_ISPHA*2, int);
					memcpy(_hoops_RGHHA, _hoops_ASPHA, _hoops_ISPHA*sizeof(int));
					FREE_ARRAY(_hoops_ASPHA, _hoops_ISPHA, int);
					_hoops_ASPHA = _hoops_RGHHA;
					_hoops_ISPHA*=2;
				}

				_hoops_ASPHA[_hoops_RSPHA++]=2;
				_hoops_ASPHA[_hoops_RSPHA++]=_hoops_SSPHA[keep_pts1[i]];
				_hoops_ASPHA[_hoops_RSPHA++]=_hoops_SSPHA[keep_pts2[i]];
				++_hoops_PSPHA;
			}
		}
	} //_hoops_CPHR _hoops_CCA _hoops_RSSA

	// _hoops_GSCA _hoops_RSSI
	if(keep_fcount>0 && keep_faces && _hoops_ISPHA>0 && _hoops_SCPHA)
	{
		if(source->type == _hoops_SCIP) {
			Shell * _hoops_GGHHA = (Shell *)source;
			int * face_indices;
			ALLOC_ARRAY_CACHED(face_indices, _hoops_GGHHA->face_list_length, int);
			_hoops_ACPHA(_hoops_SCPHA, _hoops_GGHHA->face_list, face_indices);

			for(i=0; i<keep_fcount; ++i) {
				if(keep_faces[i]==-1)
					break;
				if(_hoops_RSPHA>=_hoops_ISPHA) {
					int * _hoops_RGHHA = 0;
					ALLOC_ARRAY(_hoops_RGHHA, _hoops_ISPHA*2, int);
					memcpy(_hoops_RGHHA, _hoops_ASPHA, _hoops_ISPHA*sizeof(int));
					FREE_ARRAY(_hoops_ASPHA, _hoops_ISPHA, int);
					_hoops_ASPHA = _hoops_RGHHA;
					_hoops_ISPHA*=2;
				}

				int _hoops_SSPAR = face_indices[keep_faces[i]];
				int _hoops_HHHHR=_hoops_GGHHA->face_list[_hoops_SSPAR];
				if(_hoops_HHHHR < 0) _hoops_HHHHR = -_hoops_HHHHR;
				_hoops_ASPHA[_hoops_RSPHA++]=_hoops_HHHHR;
				if(_hoops_GGHHA->face_count)
					_hoops_CSPHA[keep_faces[i]]=_hoops_PSPHA++;

				for(j=1; j<=_hoops_HHHHR; ++j) {
					int _hoops_AGHHA = _hoops_GGHHA->face_list[_hoops_SSPAR+j];

					if(_hoops_SSPHA[_hoops_AGHHA]==-1) {
						_hoops_HSPHA[new_pcount]=_hoops_GGHHA->points[_hoops_AGHHA];
						_hoops_SSPHA[_hoops_AGHHA]=new_pcount++;
					}

					if(_hoops_RSPHA >= _hoops_ISPHA){
						int * _hoops_RGHHA = 0;
						ALLOC_ARRAY(_hoops_RGHHA, _hoops_ISPHA*2, int);
						memcpy(_hoops_RGHHA, _hoops_ASPHA, _hoops_ISPHA*sizeof(int));
						FREE_ARRAY(_hoops_ASPHA, _hoops_ISPHA, int);
						_hoops_ASPHA = _hoops_RGHHA;
						_hoops_ISPHA*=2;
					}
					_hoops_ASPHA[_hoops_RSPHA++]=_hoops_SSPHA[_hoops_AGHHA];
				}
			}
			FREE_ARRAY(face_indices, _hoops_GGHHA->face_list_length, int);
		}
		else /* _hoops_RPP(_hoops_HCGP->_hoops_GPRR == _hoops_GSHPR) */ {
			int _hoops_GAPPA, _hoops_RAPPA, _hoops_CAPPA;
			int _hoops_PGHHA, _hoops_HGHHA, _hoops_IGHHA;
			int _hoops_SIGA, _hoops_CRAPA;
			int _hoops_CGHHA;
			
			_hoops_PGHHA = ((_hoops_AIHPR *)source)->rows;
			_hoops_HGHHA = ((_hoops_AIHPR *)source)->columns;
			_hoops_IGHHA = 2 * _hoops_HGHHA - 2;

			for(i=0; i<keep_fcount; ++i) {
				_hoops_CGHHA = keep_faces[i];

				if(_hoops_CGHHA == -1)
					break;
				if(_hoops_RSPHA + 4 >= _hoops_ISPHA) {
					int * _hoops_RGHHA = 0;
					ALLOC_ARRAY(_hoops_RGHHA, _hoops_ISPHA*2, int);
					memcpy(_hoops_RGHHA, _hoops_ASPHA, _hoops_ISPHA*sizeof(int));
					FREE_ARRAY(_hoops_ASPHA, _hoops_ISPHA, int);
					_hoops_ASPHA = _hoops_RGHHA;
					_hoops_ISPHA*=2;
				}

				_hoops_ASPHA[_hoops_RSPHA++] = 3;
				_hoops_CSPHA[_hoops_CGHHA] = _hoops_PSPHA++;				

				if(_hoops_CGHHA % 2 == 0) {
					_hoops_SIGA = _hoops_CGHHA / _hoops_IGHHA;
					_hoops_CRAPA = _hoops_CGHHA % _hoops_IGHHA / 2;

					_hoops_GAPPA = _hoops_CGHHA / 2 + _hoops_SIGA;
					_hoops_RAPPA = _hoops_GAPPA + 1;
					_hoops_CAPPA = _hoops_HGHHA * (_hoops_SIGA+1) + _hoops_CRAPA;
				}
				else {
					_hoops_SIGA = _hoops_CGHHA / _hoops_IGHHA;
					_hoops_CRAPA = (_hoops_CGHHA-1) % _hoops_IGHHA / 2;

					_hoops_GAPPA = (_hoops_CGHHA+1) / 2 + _hoops_SIGA;
					_hoops_RAPPA = _hoops_HGHHA * (_hoops_SIGA+1) + _hoops_CRAPA + 1;
					_hoops_CAPPA = _hoops_RAPPA - 1;
				}

				if(_hoops_SSPHA[_hoops_GAPPA] == -1) {
					_hoops_HSPHA[new_pcount] = source->points[_hoops_GAPPA];
					_hoops_SSPHA[_hoops_GAPPA] = new_pcount++;
				}
				if(_hoops_SSPHA[_hoops_RAPPA] == -1) {
					_hoops_HSPHA[new_pcount] = source->points[_hoops_RAPPA];
					_hoops_SSPHA[_hoops_RAPPA] = new_pcount++;
				}
				if(_hoops_SSPHA[_hoops_CAPPA] == -1) {
					_hoops_HSPHA[new_pcount] = source->points[_hoops_CAPPA];
					_hoops_SSPHA[_hoops_CAPPA] = new_pcount++;
				}

				_hoops_ASPHA[_hoops_RSPHA++] = _hoops_SSPHA[_hoops_GAPPA];
				_hoops_ASPHA[_hoops_RSPHA++] = _hoops_SSPHA[_hoops_RAPPA];
				_hoops_ASPHA[_hoops_RSPHA++] = _hoops_SSPHA[_hoops_CAPPA];
			}
		}
	} //_hoops_CPHR _hoops_CCA _hoops_RSSI

	if(face_map && _hoops_CCPHA)
		memcpy(face_map, _hoops_CSPHA, _hoops_CCPHA);

	if(pts_map)
		memcpy(pts_map, _hoops_SSPHA, source->point_count*sizeof(int));

	// _hoops_CARR _hoops_CPAP _hoops_PPR _hoops_ASRC _hoops_SIC
	PUSHNAME(context);
	_hoops_PGRAA = HC_Insert_Shell(new_pcount, _hoops_HSPHA, _hoops_RSPHA, _hoops_ASPHA);
	POPNAME(context);

	if (source->local_vertex_attributes.explicit_normal_count > 0 && 
		!BIT (source->polyhedron_flags, PHF_VERTEX_NORMALS_VALID)) 
		HI_Assemble_3D_Tristrips(source, 0, true);	
	
	if(source->local_vertex_attributes.normals != null){
		ALLOC_ARRAY(_hoops_IRPA, new_pcount, Vector);

		for(i=0; i<source->point_count; ++i){
			if(_hoops_SSPHA[i] != -1)
				_hoops_IRPA[_hoops_SSPHA[i]] = source->local_vertex_attributes.normals[i];
		}
		
		PUSHNAME(context);
		HC_MSet_Vertex_Normals(_hoops_PGRAA, 0, new_pcount, _hoops_IRPA);
		POPNAME(context);

		FREE_ARRAY(_hoops_IRPA, new_pcount, Vector);
	}

	FREE_ARRAY_ALIGNED(_hoops_HSPHA, source->point_count, Point, 16);
	if(_hoops_ISPHA)
		FREE_ARRAY(_hoops_ASPHA, _hoops_ISPHA, int);
	if(_hoops_CCPHA)
		FREE_ARRAY(_hoops_CSPHA, _hoops_CCPHA, int);
	FREE_ARRAY(_hoops_SSPHA, source->point_count, int);

Release:
	_hoops_IRRPR();
	
	return _hoops_PGRAA;
}

















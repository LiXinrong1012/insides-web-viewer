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
 * $Id: obf_tmp.txt 1.125 2010-09-22 02:29:38 trask Exp $
 */

#include "hoops.h"
#include "database.h"	/* _hoops_IH _hoops_HRHSA... */
#include "driver.h"		/* _hoops_IH _hoops_IPP->_hoops_SGSS _hoops_PPR _hoops_IRHSA */
#include "hidden.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

#ifndef _hoops_CRHSA


local _hoops_SRHSA alter * _hoops_GAHSA(
	Display_Context const *		dc,
	_hoops_SRHSA alter *		_hoops_RAHSA,
	bool						_hoops_AAHSA) {
	_hoops_SRHSA alter *		_hoops_PAHSA;

	POOL_ZALLOC (_hoops_PAHSA, _hoops_SRHSA, dc->memory_pool);
	_hoops_ICAI(_hoops_PAHSA);
	_hoops_PAHSA->type = _hoops_RAHSA->type;
	_hoops_PAHSA->_hoops_APHGA = _hoops_RAHSA->_hoops_APHGA;


	_hoops_PAHSA->xmin = _hoops_RAHSA->xmin;
	_hoops_PAHSA->xmax = _hoops_RAHSA->xmax;
	_hoops_PAHSA->ymin = _hoops_RAHSA->ymin;
	_hoops_PAHSA->ymax = _hoops_RAHSA->ymax;
	_hoops_PAHSA->_hoops_RICR = _hoops_RAHSA->_hoops_RICR;
	_hoops_PAHSA->_hoops_AICR = _hoops_RAHSA->_hoops_AICR;

	_hoops_PAHSA->plane = _hoops_RAHSA->plane;

	/*
	 * _hoops_IPS _hoops_RH _hoops_PPSR _hoops_HIGR
	 */

	if (_hoops_AAHSA) {
		_hoops_PAHSA->count = _hoops_RAHSA->count;
		_hoops_HAHSA(_hoops_RAHSA->points, _hoops_RAHSA->count, DC_Point, _hoops_PAHSA->points, dc->memory_pool);
	}

	switch (_hoops_PAHSA->type) {
	  case _hoops_IAHSA: {
		  _hoops_CAHSA alter	*_hoops_SAHSA;

		  if ((_hoops_SAHSA = (_hoops_CAHSA alter *)_hoops_RAHSA->_hoops_GPHSA) == null) {
			  _hoops_PAHSA->_hoops_GPHSA = null;
		  }
		  else {
			  _hoops_CAHSA alter	*_hoops_RPHSA;

			  POOL_ALLOC (_hoops_RPHSA, _hoops_CAHSA, dc->memory_pool);
			  _hoops_PAHSA->_hoops_GPHSA = (_hoops_APHSA alter *)_hoops_RPHSA;
			  _hoops_RPHSA->_hoops_RAGR = _hoops_SAHSA->_hoops_RAGR;
			  if (BIT (_hoops_SAHSA->_hoops_RAGR, _hoops_PPHSA)) {
				  POOL_ALLOC_ARRAY (_hoops_RPHSA->_hoops_HPHSA, 1, RGBAS32, dc->memory_pool);
				  _hoops_RPHSA->_hoops_HPHSA[0] = _hoops_SAHSA->_hoops_HPHSA[0];
			  }
			  else _hoops_RPHSA->_hoops_HPHSA = null;
			  _hoops_RPHSA->rgba_colors = null;
			  _hoops_RPHSA->planes = null;
			  _hoops_RPHSA->params = null;
			  _hoops_RPHSA->param_width = 0;
			  _hoops_RPHSA->param_flags = 0;
		  }
	  }	  break;

	  case _hoops_IPHSA: {
		  _hoops_CAHSA alter	*_hoops_SAHSA;

		  if ((_hoops_SAHSA = (_hoops_CAHSA alter *)_hoops_RAHSA->_hoops_GPHSA) == null) {
			  _hoops_PAHSA->_hoops_GPHSA = null;
		  }
		  else {
			  _hoops_CAHSA alter	*_hoops_RPHSA;

			  POOL_ALLOC (_hoops_RPHSA, _hoops_CAHSA, dc->memory_pool);
			  _hoops_PAHSA->_hoops_GPHSA = (_hoops_APHSA alter *)_hoops_RPHSA;
			  _hoops_RPHSA->_hoops_RAGR = _hoops_SAHSA->_hoops_RAGR;
			  _hoops_RPHSA->param_flags = 0;

			  if (BIT (_hoops_SAHSA->_hoops_RAGR, _hoops_PPHSA)) {
				  POOL_ALLOC_ARRAY (_hoops_RPHSA->_hoops_HPHSA, 1, RGBAS32, dc->memory_pool);
				  _hoops_RPHSA->_hoops_HPHSA[0] = _hoops_SAHSA->_hoops_HPHSA[0];
				  _hoops_RPHSA->rgba_colors = null;
			  }
			  else if (BIT (_hoops_SAHSA->_hoops_RAGR, _hoops_CPHSA)) {
				  POOL_ALLOC_ARRAY (_hoops_RPHSA->_hoops_HPHSA, 3, RGBAS32, dc->memory_pool);
				  _hoops_RPHSA->_hoops_HPHSA[0] = _hoops_SAHSA->_hoops_HPHSA[0];
				  _hoops_RPHSA->_hoops_HPHSA[1] = _hoops_SAHSA->_hoops_HPHSA[1];
				  _hoops_RPHSA->_hoops_HPHSA[2] = _hoops_SAHSA->_hoops_HPHSA[2];
				  _hoops_RPHSA->rgba_colors = null;
			  }
			  else if (BIT (_hoops_SAHSA->_hoops_RAGR, _hoops_SPHSA)) {
				  POOL_ALLOC_ARRAY (_hoops_RPHSA->rgba_colors, 3, RGBA, dc->memory_pool);
				  _hoops_RPHSA->rgba_colors[0] = _hoops_SAHSA->rgba_colors[0];
				  _hoops_RPHSA->rgba_colors[1] = _hoops_SAHSA->rgba_colors[1];
				  _hoops_RPHSA->rgba_colors[2] = _hoops_SAHSA->rgba_colors[2];
				  _hoops_RPHSA->_hoops_HPHSA = null;
			  }
			  else {
				  _hoops_RPHSA->_hoops_HPHSA = null;
				  _hoops_RPHSA->rgba_colors = null;
			  }

			  if (BIT (_hoops_SAHSA->_hoops_RAGR, _hoops_GHHSA)) {
				  POOL_ALLOC_ARRAY (_hoops_RPHSA->planes, 3, _hoops_ARPA, dc->memory_pool);
				  _hoops_RPHSA->planes[0] = _hoops_SAHSA->planes[0];
				  _hoops_RPHSA->planes[1] = _hoops_SAHSA->planes[1];
				  _hoops_RPHSA->planes[2] = _hoops_SAHSA->planes[2];
			  }
			  else _hoops_RPHSA->planes = null;

			  if (BIT (_hoops_SAHSA->_hoops_RAGR, _hoops_RHHSA)) {

				  _hoops_RPHSA->param_width = _hoops_SAHSA->param_width;
				  _hoops_RPHSA->param_flags = _hoops_SAHSA->param_flags;
				  POOL_ALLOC_ARRAY (_hoops_RPHSA->params, _hoops_SAHSA->param_width*3, _hoops_RSSH, dc->memory_pool);
				  COPY_PARAMETER (&_hoops_SAHSA->params[_hoops_SAHSA->param_width*0],
						  &_hoops_RPHSA->params[_hoops_SAHSA->param_width*0], _hoops_SAHSA->param_width);
				  COPY_PARAMETER (&_hoops_SAHSA->params[_hoops_SAHSA->param_width*1],
						  &_hoops_RPHSA->params[_hoops_SAHSA->param_width*1], _hoops_SAHSA->param_width);
				  COPY_PARAMETER (&_hoops_SAHSA->params[_hoops_SAHSA->param_width*2],
						  &_hoops_RPHSA->params[_hoops_SAHSA->param_width*2], _hoops_SAHSA->param_width);
			  }
			  else {
				  _hoops_RPHSA->params = null;
				  _hoops_RPHSA->param_width = 0;
				  _hoops_RPHSA->param_flags = 0;
			  }
		  }
	  }	  break;

	  case _hoops_AHHSA: {
		  _hoops_CAHSA alter	*_hoops_SAHSA;

		  if ((_hoops_SAHSA = (_hoops_CAHSA alter *)_hoops_RAHSA->_hoops_GPHSA) == null) {
			  _hoops_PAHSA->_hoops_GPHSA = null;
		  }
		  else {
			  _hoops_CAHSA alter	*_hoops_RPHSA;

			  POOL_ALLOC (_hoops_RPHSA, _hoops_CAHSA, dc->memory_pool);
			  _hoops_PAHSA->_hoops_GPHSA = (_hoops_APHSA alter *)_hoops_RPHSA;
			  _hoops_RPHSA->_hoops_RAGR = _hoops_SAHSA->_hoops_RAGR;
			  _hoops_RPHSA->param_flags = _hoops_SAHSA->param_flags;

			  if (BIT (_hoops_SAHSA->_hoops_RAGR, _hoops_PPHSA)) {
				  POOL_ALLOC_ARRAY (_hoops_RPHSA->_hoops_HPHSA, 1, RGBAS32, dc->memory_pool);
				  _hoops_RPHSA->_hoops_HPHSA[0] = _hoops_SAHSA->_hoops_HPHSA[0];
				  _hoops_RPHSA->rgba_colors = null;
			  }
			  else if (BIT (_hoops_SAHSA->_hoops_RAGR, _hoops_CPHSA)) {
				  POOL_ALLOC_ARRAY (_hoops_RPHSA->_hoops_HPHSA, 2, RGBAS32, dc->memory_pool);
				  _hoops_RPHSA->_hoops_HPHSA[0] = _hoops_SAHSA->_hoops_HPHSA[0];
				  _hoops_RPHSA->_hoops_HPHSA[1] = _hoops_SAHSA->_hoops_HPHSA[1];
				  _hoops_RPHSA->rgba_colors = null;
			  }
			  else if (BIT (_hoops_SAHSA->_hoops_RAGR, _hoops_SPHSA)) {
				  POOL_ALLOC_ARRAY (_hoops_RPHSA->rgba_colors, 2, RGBA, dc->memory_pool);
				  _hoops_RPHSA->rgba_colors[0] = _hoops_SAHSA->rgba_colors[0];
				  _hoops_RPHSA->rgba_colors[1] = _hoops_SAHSA->rgba_colors[1];
				  _hoops_RPHSA->_hoops_HPHSA = null;
			  }

			  else {
				  _hoops_RPHSA->_hoops_HPHSA = null;
				  _hoops_RPHSA->rgba_colors = null;
			  }

			  if (BIT (_hoops_SAHSA->_hoops_RAGR, _hoops_GHHSA)) {
				  POOL_ALLOC_ARRAY (_hoops_RPHSA->planes, 2, _hoops_ARPA, dc->memory_pool);
				  _hoops_RPHSA->planes[0] = _hoops_SAHSA->planes[0];
				  _hoops_RPHSA->planes[1] = _hoops_SAHSA->planes[1];
			  }
			  else _hoops_RPHSA->planes = null;

			  if (BIT (_hoops_SAHSA->_hoops_RAGR, _hoops_RHHSA)) {
				  _hoops_RPHSA->param_width = _hoops_SAHSA->param_width;
				  POOL_ALLOC_ARRAY (_hoops_RPHSA->params, _hoops_SAHSA->param_width*2, _hoops_RSSH, dc->memory_pool);
				  COPY_PARAMETER (&_hoops_SAHSA->params[_hoops_SAHSA->param_width*0],
						  &_hoops_RPHSA->params[_hoops_SAHSA->param_width*0], _hoops_SAHSA->param_width);
				  COPY_PARAMETER (&_hoops_SAHSA->params[_hoops_SAHSA->param_width*1],
						  &_hoops_RPHSA->params[_hoops_SAHSA->param_width*1], _hoops_SAHSA->param_width);
			  }
			  else {
				  _hoops_RPHSA->params = null;
				  _hoops_RPHSA->param_width = 0;
			  }
		  }
	  }	  break;

	  case _hoops_PHHSA: {
		  _hoops_HHHSA alter	*_hoops_IHHSA;

		  _hoops_IHHSA = &_hoops_RAHSA->_hoops_GPHSA->_hoops_CHHSA;

		  _hoops_PAHSA->_hoops_GPHSA = _hoops_RAHSA->_hoops_GPHSA;
		  ++_hoops_IHHSA->_hoops_HIHI;
	  }	  break;

	  case _hoops_SHHSA: {
		  _hoops_GIHSA alter		*_hoops_RIHSA;

		  _hoops_RIHSA = &_hoops_RAHSA->_hoops_GPHSA->_hoops_AIHSA;

		  _hoops_PAHSA->_hoops_GPHSA = _hoops_RAHSA->_hoops_GPHSA;
		  ++_hoops_RIHSA->_hoops_HIHI;
	  }	  break;

	  case _hoops_PIHSA: {
		  _hoops_HIHSA alter	*_hoops_IIHSA;
		  _hoops_HIHSA alter	*_hoops_CIHSA;

		  _hoops_CIHSA = (_hoops_HIHSA alter *)_hoops_RAHSA->_hoops_GPHSA;
		  POOL_ALLOC (_hoops_IIHSA, _hoops_HIHSA, dc->memory_pool);
		  _hoops_PAHSA->_hoops_GPHSA = (_hoops_APHSA alter *)_hoops_IIHSA;
		  HI_Copy_KName (&_hoops_CIHSA->_hoops_SIHSA, &_hoops_IIHSA->_hoops_SIHSA);
		  _hoops_IIHSA->_hoops_RACSR = _hoops_CIHSA->_hoops_RACSR;
		  _hoops_IIHSA->_hoops_GCHSA = _hoops_CIHSA->_hoops_GCHSA;

		  if ((_hoops_IIHSA->text = _hoops_CIHSA->text) != null)
			  _hoops_PRRH (_hoops_IIHSA->text);
	  }	  break;

	  case _hoops_RCHSA:
	  case _hoops_ACHSA:
	  case _hoops_PCHSA: {
		  if (_hoops_RAHSA->_hoops_GPHSA != null)
			  _hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								 "Unexpected data in hidden item");
		  _hoops_PAHSA->_hoops_GPHSA = null;
	  }	  break;
	  case _hoops_HCHSA:{
		    _hoops_ICHSA* _hoops_SSRPR;
			POOL_ZALLOC (_hoops_SSRPR, _hoops_ICHSA, dc->memory_pool);
			_hoops_PAHSA->_hoops_GPHSA = (_hoops_APHSA*)_hoops_SSRPR;
			_hoops_HAHSA( ((_hoops_ICHSA*)(_hoops_RAHSA->_hoops_GPHSA))->_hoops_CCHSA,
				_hoops_RAHSA->count, bool, _hoops_SSRPR->_hoops_CCHSA, dc->memory_pool);
	  } break;

	  default: {
		  _hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Cannot copy hidden item");
	  }	  break;
	}

	return _hoops_PAHSA;

}



typedef struct {
	DC_Point					point;
	RGBAS32					_hoops_PIHR;
	RGBA						_hoops_IIRGA;
	_hoops_ARPA					plane;
	_hoops_RSSH				*params;
	int							param_width;
	bool					_hoops_CCHSA;
	_hoops_SCHSA			_hoops_RAGR;
} _hoops_GSHSA;

local void _hoops_RSHSA (
	_hoops_CASS alter			*hidden) {
	_hoops_SRHSA alter	*_hoops_ASHSA = hidden->_hoops_ASHSA;
	DC_Point alter		*pt = _hoops_ASHSA->points;
	int						count = _hoops_ASHSA->count;

	_hoops_ASHSA->xmin = _hoops_ASHSA->xmax = pt->x;
	_hoops_ASHSA->ymin = _hoops_ASHSA->ymax = pt->y;
	_hoops_ASHSA->_hoops_RICR = _hoops_ASHSA->_hoops_AICR = pt->z;

	while (--count > 0) {
		++pt;
		if (_hoops_ASHSA->xmin > pt->x) _hoops_ASHSA->xmin = pt->x;
		if (_hoops_ASHSA->xmax < pt->x) _hoops_ASHSA->xmax = pt->x;
		if (_hoops_ASHSA->ymin > pt->y) _hoops_ASHSA->ymin = pt->y;
		if (_hoops_ASHSA->ymax < pt->y) _hoops_ASHSA->ymax = pt->y;
		if (_hoops_ASHSA->_hoops_RICR > pt->z) _hoops_ASHSA->_hoops_RICR = pt->z;
		if (_hoops_ASHSA->_hoops_AICR < pt->z) _hoops_ASHSA->_hoops_AICR = pt->z;
	}
}

#define _hoops_PSHSA(_hoops_HSHSA, _hoops_ISHSA, _hoops_CSHSA) { \
	(_hoops_HSHSA)->point.x = (_hoops_ISHSA)->x; \
	(_hoops_HSHSA)->point.y = (_hoops_ISHSA)->y; \
	(_hoops_HSHSA)->point.z = (_hoops_ISHSA)->z; \
	(_hoops_HSHSA)->_hoops_CCHSA = (_hoops_CSHSA); \
}

#define _hoops_SSHSA(_hoops_HCHPR) do { \
		if ((_hoops_HCHPR).params) FREE_ARRAY((_hoops_HCHPR).params, (_hoops_HCHPR).param_width, _hoops_RSSH); \
	}while (0)


#if 1
#define _hoops_GGISA
#endif

#if 0
#define _hoops_RGISA
#define _hoops_AGISA
#endif

/*
 * _hoops_PGISA _hoops_RH _hoops_SGGPR, _hoops_PPR _hoops_GAR _hoops_AHPH _hoops_AIRC _hoops_GAR _hoops_CHR _hoops_GPRI
 */
local void _hoops_HGISA (
	Display_Context const *		dc,
	_hoops_CASS alter *				hidden,
	_hoops_GSHSA alter *		expansion,
	int							index) {

	_hoops_CAHSA alter	*	info;

	/* _hoops_HSPC _hoops_AGCR _hoops_IS _hoops_CRHR _hoops_HHGS */
	expansion->_hoops_PIHR = _hoops_CAHSR::_hoops_SAHSR;
	expansion->_hoops_IIRGA = _hoops_IGISA::_hoops_SAHSR;
	expansion->plane = _hoops_CGISA::_hoops_CRGA;
	expansion->params = null;
	expansion->param_width = 0;

	if ((info = (_hoops_CAHSA alter *)hidden->_hoops_ASHSA->_hoops_GPHSA) == null) {
		expansion->_hoops_RAGR = false;
	}
	else {
		expansion->_hoops_RAGR = info->_hoops_RAGR;

		if (BIT (info->_hoops_RAGR, _hoops_SPHSA))
			expansion->_hoops_IIRGA = info->rgba_colors[index];

		if (BIT (info->_hoops_RAGR, _hoops_CPHSA))
			expansion->_hoops_PIHR = info->_hoops_HPHSA[index];

		if (BIT (info->_hoops_RAGR, _hoops_GHHSA))
			expansion->plane = info->planes[index];

		if (BIT (info->_hoops_RAGR, _hoops_RHHSA)) {
			expansion->param_width = info->param_width;
			POOL_ALLOC_ARRAY(expansion->params, expansion->param_width, _hoops_RSSH, dc->memory_pool);
			COPY_PARAMETER(&info->params[index*expansion->param_width],
					expansion->params, expansion->param_width);
		}
	}
}

#define _hoops_SGISA(pl,_hoops_GRISA) ((pl)->a * (_hoops_GRISA)->x  +		\
					  (pl)->b * (_hoops_GRISA)->y  +		\
					  (pl)->c * (_hoops_GRISA)->z  +		\
					  (pl)->d)

local float _hoops_RRISA (
	_hoops_ARPA const			*plane,
	DC_Point const		*_hoops_GGIAR,
	DC_Point const		*p1,
	DC_Point alter		*_hoops_RHGI) {
	float					dx = p1->x - _hoops_GGIAR->x,
										_hoops_CRRAR = p1->y - _hoops_GGIAR->y,
										_hoops_AAAC = p1->z - _hoops_GGIAR->z,
										_hoops_SSHGA, t;

	/*
	 * _hoops_ARISA _hoops_RH _hoops_ASGH _hoops_PRISA _hoops_GHSSR _hoops_IH _hoops_RH _hoops_SGSSR _hoops_IIGR _hoops_IRS _hoops_III
	 * _hoops_PPR _hoops_IRS _hoops_IPPA.
	 */

	if (dx < 0.0f || dx ==0.0f && _hoops_CRRAR < 0.0f) {
		dx=-dx;
		_hoops_CRRAR=-_hoops_CRRAR;
		_hoops_AAAC=-_hoops_AAAC;

		_hoops_SSHGA = plane->a*dx + plane->b*_hoops_CRRAR + plane->c*_hoops_AAAC;
		if (_hoops_SSHGA == 0.0f) t = 0.5f; /* _hoops_CGH _hoops_IIP _hoops_IHPS */
		else {
			t = -(plane->a*p1->x +
				  plane->b*p1->y +
				  plane->c*p1->z + plane->d) / _hoops_SSHGA;
			if (t < 0.0f) t = 0.0f;				/* _hoops_CGH _hoops_IIP _hoops_IHPS */
			else if (t > 1.0f) t = 1.0f; /* _hoops_CGH _hoops_IIP _hoops_IHPS */
		}

		_hoops_PCCAR {
			float			_hoops_HRISA;
			float			_hoops_IRISA;

			_hoops_RHGI->x = p1->x + dx * t;
			_hoops_RHGI->y = p1->y + _hoops_CRRAR * t;
			_hoops_RHGI->z = p1->z + _hoops_AAAC * t;

			_hoops_HRISA = _hoops_SGISA (plane, p1);
			_hoops_IRISA   = _hoops_SGISA (plane, _hoops_RHGI);

			if (_hoops_HRISA * _hoops_IRISA >= 0.0f) break;

			t *= 0.999f;
		}

		t = 1.0f - t;
	}
	else {

		_hoops_SSHGA = plane->a*dx + plane->b*_hoops_CRRAR + plane->c*_hoops_AAAC;
		if (_hoops_SSHGA == 0.0f) t = 0.5f; /* _hoops_CGH _hoops_IIP _hoops_IHPS */
		else {
			t = -(plane->a*_hoops_GGIAR->x +
				  plane->b*_hoops_GGIAR->y +
				  plane->c*_hoops_GGIAR->z + plane->d) / _hoops_SSHGA;
			if (t < 0.0f) t = 0.0f;				/* _hoops_CGH _hoops_IIP _hoops_IHPS */
			else if (t > 1.0f) t = 1.0f; /* _hoops_CGH _hoops_IIP _hoops_IHPS */
		}

		_hoops_PCCAR {
			float			_hoops_HRISA;
			float			_hoops_IRISA;

			_hoops_RHGI->x = _hoops_GGIAR->x + dx * t;
			_hoops_RHGI->y = _hoops_GGIAR->y + _hoops_CRRAR * t;
			_hoops_RHGI->z = _hoops_GGIAR->z + _hoops_AAAC * t;

			_hoops_HRISA = _hoops_SGISA (plane, _hoops_GGIAR);
			_hoops_IRISA   = _hoops_SGISA (plane, _hoops_RHGI);

			if (_hoops_HRISA * _hoops_IRISA >= 0.0f) break;

			t *= 0.999f;
		}
	}

	return	t;
}

local void _hoops_CRISA (
	Net_Rendition const &		nr,
	_hoops_ARPA alter *				plane,
	_hoops_GSHSA alter *		_hoops_GGIAR,
	_hoops_GSHSA alter *		p1,
	_hoops_GSHSA alter *		_hoops_RHGI,
	bool						edge,
	float						t) {

	UNREFERENCED(plane);

	Display_Context const *		dc = nr->_hoops_SRA;

	/*
	 * _hoops_ACIAR _hoops_CPS _hoops_SHS _hoops_HPGR _hoops_SGS _hoops_SGSSR _hoops_PPSR
	 */

	_hoops_RHGI->_hoops_RAGR = _hoops_GGIAR->_hoops_RAGR;

	_hoops_RHGI->_hoops_PIHR = _hoops_CAHSR::_hoops_SAHSR; /* _hoops_AHHR _hoops_GGSR _hoops_RH _hoops_PPRAR _hoops_SIH */
	if (BIT (_hoops_RHGI->_hoops_RAGR, _hoops_CPHSA)) {
#ifndef _hoops_SRISA
		float					_hoops_GAISA, _hoops_RAISA;

		_hoops_GAISA = (float)_hoops_IRGCR (_hoops_GGIAR->_hoops_PIHR.r);
		_hoops_RAISA = (float)_hoops_IRGCR (p1->_hoops_PIHR.r);
		_hoops_RHGI->_hoops_PIHR.r = (unsigned char)(_hoops_GAISA + (_hoops_RAISA - _hoops_GAISA)*t);
		_hoops_GAISA = (float)_hoops_IRGCR (_hoops_GGIAR->_hoops_PIHR.g);
		_hoops_RAISA = (float)_hoops_IRGCR (p1->_hoops_PIHR.g);
		_hoops_RHGI->_hoops_PIHR.g = (unsigned char)(_hoops_GAISA + (_hoops_RAISA - _hoops_GAISA)*t);
		_hoops_GAISA = (float)_hoops_IRGCR (_hoops_GGIAR->_hoops_PIHR.b);
		_hoops_RAISA = (float)_hoops_IRGCR (p1->_hoops_PIHR.b);
		_hoops_RHGI->_hoops_PIHR.b = (unsigned char)(_hoops_GAISA + (_hoops_RAISA - _hoops_GAISA)*t);
		_hoops_GAISA = (float)_hoops_IRGCR (_hoops_GGIAR->_hoops_PIHR.a);
		_hoops_RAISA = (float)_hoops_IRGCR (p1->_hoops_PIHR.a);
		_hoops_RHGI->_hoops_PIHR.a = (unsigned char)(_hoops_GAISA + (_hoops_RAISA - _hoops_GAISA)*t);
#else
		/*_hoops_HISRA _hoops_PSHA*/
		static unsigned char r,g,b;

		r=g=b = _hoops_AAISA() % 256;

		_hoops_RHGI->_hoops_PIHR.r = r;
		_hoops_RHGI->_hoops_PIHR.g = g;
		_hoops_RHGI->_hoops_PIHR.b = b;
		_hoops_RHGI->_hoops_PIHR.a = 255;
#endif
	}

	if (BIT (_hoops_RHGI->_hoops_RAGR, _hoops_SPHSA))
		_hoops_ACRGA (_hoops_GGIAR->_hoops_IIRGA, p1->_hoops_IIRGA, t, _hoops_RHGI->_hoops_IIRGA);
	else
		_hoops_RHGI->_hoops_IIRGA = _hoops_IGISA::_hoops_SAHSR;

	if (BIT (_hoops_RHGI->_hoops_RAGR, _hoops_GHHSA))
		_hoops_RGRGA (_hoops_GGIAR->plane, p1->plane, t, _hoops_RHGI->plane);
	else
		_hoops_RHGI->plane = _hoops_CGISA::_hoops_CRGA;

	if (BIT (_hoops_RHGI->_hoops_RAGR, _hoops_RHHSA)) {
		float					_hoops_PAISA, _hoops_IICPA;

		if (BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_CSGGA)) {
			Point							_hoops_SSGGA;
			_hoops_HHCR const &		_hoops_IHCR = nr->transform_rendition;
			_hoops_SGCC const &		mat = _hoops_IHCR->_hoops_CGCC;
			_hoops_RPRA const *				_hoops_APRA;
			float							_hoops_APCP;

			if (!BIT (_hoops_IHCR->flags, _hoops_IGCC))
				HD_Validate_World_To_Screen (nr);

			_hoops_APRA = mat->_hoops_PPRA()->data.elements;

			_hoops_APCP = 1.0f / _hoops_PHCP (_hoops_APRA, _hoops_GGIAR->point);
			_hoops_SSGGA.x = _hoops_HPRA (_hoops_APRA, _hoops_GGIAR->point) * _hoops_APCP;
			_hoops_SSGGA.y = _hoops_IPRA (_hoops_APRA, _hoops_GGIAR->point) * _hoops_APCP;
			_hoops_SSGGA.z = _hoops_CPRA (_hoops_APRA, _hoops_GGIAR->point) * _hoops_APCP;
			_hoops_PAISA		= _hoops_PHCP (mat->data.elements, _hoops_SSGGA);

			_hoops_APCP = 1.0f / _hoops_PHCP (_hoops_APRA, p1->point);
			_hoops_SSGGA.x = _hoops_HPRA (_hoops_APRA, p1->point) * _hoops_APCP;
			_hoops_SSGGA.y = _hoops_IPRA (_hoops_APRA, p1->point) * _hoops_APCP;
			_hoops_SSGGA.z = _hoops_CPRA (_hoops_APRA, p1->point) * _hoops_APCP;
			_hoops_IICPA		= _hoops_PHCP (mat->data.elements, _hoops_SSGGA);
		}
		else
			_hoops_PAISA = _hoops_IICPA = 1.0f;

		_hoops_RHGI->param_width=_hoops_GGIAR->param_width;
		POOL_ALLOC_ARRAY(_hoops_RHGI->params, _hoops_RHGI->param_width, _hoops_RSSH, dc->memory_pool);

		_hoops_GGRGA (nr, _hoops_GGIAR->params, p1->params,
				t, _hoops_RHGI->params, _hoops_IICPA / _hoops_PAISA, _hoops_RHGI->param_width);

	}
	else {
		_hoops_RHGI->params = null;
		_hoops_RHGI->param_width = 0;
	}

	_hoops_RHGI->_hoops_CCHSA = edge;

}



local void _hoops_HAISA (
	Display_Context const *		dc,
	_hoops_CASS alter *				_hoops_IAISA,
	bool						_hoops_CAISA,
	_hoops_GSHSA alter *		_hoops_GGIAR,
	_hoops_GSHSA alter *		p1,
	_hoops_GSHSA alter *		p2) {
	_hoops_CASS alter *				_hoops_SAISA;
	_hoops_CAHSA alter *	_hoops_RPHSA;
	_hoops_CAHSA alter	*	_hoops_SAHSA;
	_hoops_SRHSA alter *		_hoops_PAHSA;
	_hoops_SRHSA alter *		_hoops_RAHSA = _hoops_IAISA->_hoops_ASHSA;

	if (!_hoops_CAISA) {
		POOL_ZALLOC (_hoops_SAISA, _hoops_CASS, dc->memory_pool);
		POOL_ZALLOC (_hoops_PAHSA, _hoops_SRHSA, dc->memory_pool);
		_hoops_ICAI(_hoops_PAHSA);
		_hoops_SAISA->_hoops_ASHSA = _hoops_PAHSA;
		_hoops_SAISA->next = _hoops_IAISA->next;
		_hoops_IAISA->next->prev = _hoops_SAISA;
		_hoops_IAISA->next = _hoops_SAISA;
		_hoops_SAISA->prev = _hoops_IAISA;

		_hoops_PAHSA->plane = _hoops_RAHSA->plane;
		_hoops_PAHSA->type = _hoops_RAHSA->type;
		_hoops_PAHSA->_hoops_APHGA = _hoops_RAHSA->_hoops_APHGA;

		POOL_ALLOC_ARRAY (_hoops_PAHSA->points, 3, DC_Point, dc->memory_pool);
		_hoops_PAHSA->count = 3;

		if ((_hoops_SAHSA = (_hoops_CAHSA alter *)_hoops_RAHSA->_hoops_GPHSA) != null) {
			POOL_ALLOC (_hoops_RPHSA, _hoops_CAHSA, dc->memory_pool);
			_hoops_PAHSA->_hoops_GPHSA = (_hoops_APHSA alter *)_hoops_RPHSA;
			_hoops_RPHSA->_hoops_RAGR = _hoops_SAHSA->_hoops_RAGR;
			_hoops_RPHSA->param_flags = 0;

			if (BIT (_hoops_SAHSA->_hoops_RAGR, _hoops_PPHSA)) {
				POOL_ALLOC_ARRAY (_hoops_RPHSA->_hoops_HPHSA, 1, RGBAS32, dc->memory_pool);
				_hoops_RPHSA->_hoops_HPHSA[0] = _hoops_SAHSA->_hoops_HPHSA[0];
				_hoops_RPHSA->rgba_colors = null;
			}
			else if (BIT (_hoops_SAHSA->_hoops_RAGR, _hoops_CPHSA)) {
				POOL_ALLOC_ARRAY (_hoops_RPHSA->_hoops_HPHSA, 3, RGBAS32, dc->memory_pool);
				_hoops_RPHSA->_hoops_HPHSA[0] = _hoops_GGIAR->_hoops_PIHR;
				_hoops_RPHSA->_hoops_HPHSA[1] = p1->_hoops_PIHR;
				_hoops_RPHSA->_hoops_HPHSA[2] = p2->_hoops_PIHR;
				_hoops_RPHSA->rgba_colors = null;
			}
			else if (BIT (_hoops_SAHSA->_hoops_RAGR, _hoops_SPHSA)) {
				POOL_ALLOC_ARRAY (_hoops_RPHSA->rgba_colors, 3, RGBA, dc->memory_pool);
				_hoops_RPHSA->rgba_colors[0] = _hoops_GGIAR->_hoops_IIRGA;
				_hoops_RPHSA->rgba_colors[1] = p1->_hoops_IIRGA;
				_hoops_RPHSA->rgba_colors[2] = p2->_hoops_IIRGA;
				_hoops_RPHSA->_hoops_HPHSA = null;
			}
			else {
				_hoops_RPHSA->rgba_colors = null;
				_hoops_RPHSA->_hoops_HPHSA = null;
			}

			if (BIT (_hoops_SAHSA->_hoops_RAGR, _hoops_GHHSA)) {
				POOL_ALLOC_ARRAY (_hoops_RPHSA->planes, 3, _hoops_ARPA, dc->memory_pool);
				_hoops_RPHSA->planes[0] = _hoops_GGIAR->plane;
				_hoops_RPHSA->planes[1] = p1->plane;
				_hoops_RPHSA->planes[2] = p2->plane;
			}
			else
				_hoops_RPHSA->planes = null;

			if (BIT (_hoops_SAHSA->_hoops_RAGR, _hoops_RHHSA)) {
				_hoops_RPHSA->param_width = _hoops_GGIAR->param_width;
				POOL_ALLOC_ARRAY (_hoops_RPHSA->params, _hoops_RPHSA->param_width*3, _hoops_RSSH, dc->memory_pool);
				COPY_PARAMETER (_hoops_GGIAR->params, &_hoops_RPHSA->params[_hoops_RPHSA->param_width*0], _hoops_RPHSA->param_width);
				COPY_PARAMETER (p1->params, &_hoops_RPHSA->params[_hoops_RPHSA->param_width*1], _hoops_RPHSA->param_width);
				COPY_PARAMETER (p2->params, &_hoops_RPHSA->params[_hoops_RPHSA->param_width*2], _hoops_RPHSA->param_width);
			}
			else {
				_hoops_RPHSA->param_width = 0;
				_hoops_RPHSA->params = null;
			}
		}
		else
			_hoops_PAHSA->_hoops_GPHSA = null;
	}
	else {

		_hoops_SAISA = _hoops_IAISA;
		if (_hoops_IAISA->_hoops_ASHSA->_hoops_HSAI == 1)
			_hoops_PAHSA = _hoops_IAISA->_hoops_ASHSA;
		else{
			_hoops_PAHSA = _hoops_GAHSA(dc, _hoops_SAISA->_hoops_ASHSA, true);
			_hoops_ISAI(_hoops_SAISA->_hoops_ASHSA);
			_hoops_SAISA->_hoops_ASHSA = _hoops_PAHSA;
		}

		/*
		_hoops_GPISA = _hoops_RPISA;
		_hoops_APISA = _hoops_GPISA->_hoops_PPISA;
		*/


		if (_hoops_IAISA->_hoops_HPISA != null) {
			--_hoops_IAISA->_hoops_HPISA->values;
			_hoops_IAISA->_hoops_HPISA = null;
		}
		if (_hoops_IAISA->values != 0)
			HD_Remove_Hidden_Followers (_hoops_IAISA, _hoops_SAISA->next);

		if ((_hoops_RPHSA = (_hoops_CAHSA alter *)_hoops_PAHSA->_hoops_GPHSA) != null) {
			if (BIT (_hoops_RPHSA->_hoops_RAGR, _hoops_CPHSA)) {
				_hoops_RPHSA->_hoops_HPHSA[0] = _hoops_GGIAR->_hoops_PIHR;
				_hoops_RPHSA->_hoops_HPHSA[1] = p1->_hoops_PIHR;
				_hoops_RPHSA->_hoops_HPHSA[2] = p2->_hoops_PIHR;
			}
			if (BIT (_hoops_RPHSA->_hoops_RAGR, _hoops_SPHSA)) {
				_hoops_RPHSA->rgba_colors[0] = _hoops_GGIAR->_hoops_IIRGA;
				_hoops_RPHSA->rgba_colors[1] = p1->_hoops_IIRGA;
				_hoops_RPHSA->rgba_colors[2] = p2->_hoops_IIRGA;
			}
			if (BIT (_hoops_RPHSA->_hoops_RAGR, _hoops_GHHSA)) {
				_hoops_RPHSA->planes[0] = _hoops_GGIAR->plane;
				_hoops_RPHSA->planes[1] = p1->plane;
				_hoops_RPHSA->planes[2] = p2->plane;
			}
			if (BIT (_hoops_RPHSA->_hoops_RAGR, _hoops_RHHSA)) {

				if (_hoops_GGIAR->param_width != _hoops_RPHSA->param_width) {
					if (_hoops_RPHSA->params)
						FREE_ARRAY (_hoops_RPHSA->params, _hoops_RPHSA->param_width*3, _hoops_RSSH);
					_hoops_RPHSA->param_width = _hoops_GGIAR->param_width;
					POOL_ALLOC_ARRAY (_hoops_RPHSA->params, _hoops_RPHSA->param_width*3, _hoops_RSSH, dc->memory_pool);
				}
				COPY_PARAMETER (_hoops_GGIAR->params, &_hoops_RPHSA->params[_hoops_RPHSA->param_width*0], _hoops_RPHSA->param_width);
				COPY_PARAMETER (p1->params, &_hoops_RPHSA->params[_hoops_RPHSA->param_width*1], _hoops_RPHSA->param_width);
				COPY_PARAMETER (p2->params, &_hoops_RPHSA->params[_hoops_RPHSA->param_width*2], _hoops_RPHSA->param_width);

			}
			else {
				if (_hoops_RPHSA->params)
					FREE_ARRAY (_hoops_RPHSA->params, _hoops_RPHSA->param_width*3, _hoops_RSSH);
				_hoops_RPHSA->param_width=0;
				_hoops_RPHSA->params=null;
			}
		}
	}

	_hoops_PAHSA->points[0] = _hoops_GGIAR->point;
	_hoops_PAHSA->points[1] = p1->point;
	_hoops_PAHSA->points[2] = p2->point;

	_hoops_RSHSA (_hoops_SAISA);
}



local void _hoops_IPISA (
	Display_Context const *		dc,
	_hoops_CASS alter *				_hoops_IAISA,
	bool						_hoops_CAISA,
	_hoops_GSHSA alter *		_hoops_GGIAR,
	_hoops_GSHSA alter *		p1,
	bool						_hoops_CPISA,
	float						_hoops_SPISA) {
	_hoops_CASS alter *				_hoops_SAISA;
	_hoops_CAHSA alter	*	_hoops_RPHSA;
	_hoops_CAHSA alter	*	_hoops_SAHSA;
	_hoops_SRHSA alter *		_hoops_RAHSA = _hoops_IAISA->_hoops_ASHSA;
	_hoops_SRHSA alter *		_hoops_PAHSA;

	/* _hoops_HGI _hoops_CSAP _hoops_RH _hoops_GHISA _hoops_IIGR _hoops_RH _hoops_AACC */
	if (!_hoops_CAISA) {
		POOL_ZALLOC (_hoops_SAISA, _hoops_CASS, dc->memory_pool);
		POOL_ZALLOC (_hoops_PAHSA, _hoops_SRHSA, dc->memory_pool);
		_hoops_ICAI(_hoops_PAHSA);
		_hoops_SAISA->_hoops_ASHSA = _hoops_PAHSA;
		_hoops_SAISA->next = _hoops_IAISA->next;
		_hoops_IAISA->next->prev = _hoops_SAISA;
		_hoops_IAISA->next = _hoops_SAISA;
		_hoops_SAISA->prev = _hoops_IAISA;


		_hoops_PAHSA->plane = _hoops_RAHSA->plane;
		_hoops_PAHSA->type = _hoops_RAHSA->type;

		if (_hoops_IAISA->_hoops_ASHSA->_hoops_APHGA != null &&
			ANYBIT(_hoops_IAISA->_hoops_ASHSA->_hoops_APHGA->_hoops_AHP->line_style->flags, _hoops_RHISA)) {
			_hoops_PAHSA->_hoops_APHGA = _hoops_RAHSA->_hoops_APHGA;
			Line_Rendition alter &	_hoops_AHISA = _hoops_PAHSA->_hoops_APHGA.Modify()->_hoops_AHP.Modify();

			if (!BIT(_hoops_IAISA->flags, HF_CHOPPED_ANY)) {
				if (BIT(_hoops_IAISA->flags, HF_CHOPPED_NEAR_START)) {
					_hoops_SAISA->flags |= HF_CHOPPED_START;
					_hoops_AHISA->flags |= _hoops_PHISA;
				}
				else if (BIT(_hoops_IAISA->flags, HF_CHOPPED_NEAR_END)) {
					_hoops_SAISA->flags |= HF_CHOPPED_END;
					_hoops_AHISA->flags |= _hoops_HHISA;
				}
			}
			else if (BIT(_hoops_IAISA->flags, HF_CHOPPED_START)) {
				if (BIT(_hoops_IAISA->flags, HF_CHOPPED_NEAR_START)) {
					_hoops_SAISA->flags |= HF_CHOPPED_START;
					_hoops_AHISA->flags |= _hoops_PHISA;
				}
				else if (BIT(_hoops_IAISA->flags, HF_CHOPPED_NEAR_END)) {
					_hoops_SAISA->flags |= HF_CHOPPED_MIDDLE;
					_hoops_AHISA->flags |= _hoops_HHISA|_hoops_PHISA;
				}
			}
			else if (BIT(_hoops_IAISA->flags, HF_CHOPPED_MIDDLE)) {
				_hoops_AHISA->flags |= _hoops_HHISA|_hoops_PHISA;
			}
			else if (BIT(_hoops_IAISA->flags, HF_CHOPPED_END)) {
				if (BIT(_hoops_IAISA->flags, HF_CHOPPED_NEAR_START)) {
					_hoops_SAISA->flags |= HF_CHOPPED_MIDDLE;
					_hoops_AHISA->flags |= _hoops_HHISA|_hoops_PHISA;
				}
				else if (BIT(_hoops_IAISA->flags, HF_CHOPPED_NEAR_END)) {
					_hoops_SAISA->flags |= HF_CHOPPED_END;
					_hoops_AHISA->flags |= _hoops_HHISA;
				}
			}
		}
		else {
			_hoops_PAHSA->_hoops_APHGA = _hoops_RAHSA->_hoops_APHGA;
		}

		POOL_ALLOC_ARRAY (_hoops_PAHSA->points, 2, DC_Point, dc->memory_pool);
		_hoops_PAHSA->count = 2;

		if ((_hoops_SAHSA = (_hoops_CAHSA alter *)_hoops_RAHSA->_hoops_GPHSA) != null) {
			POOL_ALLOC (_hoops_RPHSA, _hoops_CAHSA, dc->memory_pool);
			_hoops_PAHSA->_hoops_GPHSA = (_hoops_APHSA alter *)_hoops_RPHSA;
			_hoops_RPHSA->_hoops_RAGR = _hoops_SAHSA->_hoops_RAGR;
			_hoops_RPHSA->param_flags = _hoops_SAHSA->param_flags;

			if (BIT (_hoops_SAHSA->_hoops_RAGR, _hoops_PPHSA)) {
				POOL_ALLOC_ARRAY (_hoops_RPHSA->_hoops_HPHSA, 1, RGBAS32, dc->memory_pool);
				_hoops_RPHSA->_hoops_HPHSA[0] = _hoops_SAHSA->_hoops_HPHSA[0];
				_hoops_RPHSA->rgba_colors = null;
			}
			else if (BIT (_hoops_SAHSA->_hoops_RAGR, _hoops_CPHSA)) {
				POOL_ALLOC_ARRAY (_hoops_RPHSA->_hoops_HPHSA, 2, RGBAS32, dc->memory_pool);
#ifndef _hoops_RGISA
				_hoops_RPHSA->_hoops_HPHSA[0] = _hoops_GGIAR->_hoops_PIHR;
				_hoops_RPHSA->_hoops_HPHSA[1] = p1->_hoops_PIHR;
#else
				{
					/*_hoops_HISRA _hoops_PSHA*/
					unsigned char r,g,b;

					r=g=b = 0;

					_hoops_RPHSA->_hoops_HPHSA[0].r = r;
					_hoops_RPHSA->_hoops_HPHSA[0].g = g;
					_hoops_RPHSA->_hoops_HPHSA[0].b = b;
					_hoops_RPHSA->_hoops_HPHSA[0].a = 255;

					_hoops_RPHSA->_hoops_HPHSA[1].r = r;
					_hoops_RPHSA->_hoops_HPHSA[1].g = g;
					_hoops_RPHSA->_hoops_HPHSA[1].b = b;
					_hoops_RPHSA->_hoops_HPHSA[1].a = 255;
				}
#endif
				_hoops_RPHSA->rgba_colors = null;
			}
			else if (BIT (_hoops_SAHSA->_hoops_RAGR, _hoops_SPHSA)) {
				POOL_ALLOC_ARRAY (_hoops_RPHSA->rgba_colors, 2, RGBA, dc->memory_pool);
				_hoops_RPHSA->rgba_colors[0] = _hoops_GGIAR->_hoops_IIRGA;
				_hoops_RPHSA->rgba_colors[1] = p1->_hoops_IIRGA;
				_hoops_RPHSA->_hoops_HPHSA = null;
			}
			else {
				_hoops_RPHSA->rgba_colors = null;
				_hoops_RPHSA->_hoops_HPHSA = null;
			}

			if (BIT (_hoops_SAHSA->_hoops_RAGR, _hoops_GHHSA)) {
				POOL_ALLOC_ARRAY (_hoops_RPHSA->planes, 2, _hoops_ARPA, dc->memory_pool);
				_hoops_RPHSA->planes[0] = _hoops_GGIAR->plane;
				_hoops_RPHSA->planes[1] = p1->plane;
			}
			else
				_hoops_RPHSA->planes = null;

			if (BIT (_hoops_SAHSA->_hoops_RAGR, _hoops_RHHSA)) {
				_hoops_RPHSA->param_width = _hoops_SAHSA->param_width;
				POOL_ALLOC_ARRAY (_hoops_RPHSA->params, _hoops_RPHSA->param_width*2, _hoops_RSSH, dc->memory_pool);
				COPY_PARAMETER (_hoops_GGIAR->params, &_hoops_RPHSA->params[_hoops_RPHSA->param_width*0], _hoops_RPHSA->param_width);
				COPY_PARAMETER (p1->params, &_hoops_RPHSA->params[_hoops_RPHSA->param_width*1], _hoops_RPHSA->param_width);
			}
			else {
				_hoops_RPHSA->param_width = 0;
				_hoops_RPHSA->params = null;
			}
		}
		else
			_hoops_PAHSA->_hoops_GPHSA = null;
	}
	else {
		/* _hoops_HGI _hoops_HRGR _hoops_RH _hoops_SGIP _hoops_PPAP _hoops_IIGR _hoops_RH _hoops_AACC */

		/*
	 	_hoops_GPISA = _hoops_RPISA;
                _hoops_APISA = _hoops_GPISA->_hoops_PPISA;
		*/

		_hoops_SAISA = _hoops_IAISA;
		if (_hoops_IAISA->_hoops_ASHSA->_hoops_HSAI == 1)
			_hoops_PAHSA = _hoops_IAISA->_hoops_ASHSA;
		else{
			_hoops_PAHSA = _hoops_GAHSA(dc, _hoops_SAISA->_hoops_ASHSA, true);
			_hoops_ISAI(_hoops_SAISA->_hoops_ASHSA);
			_hoops_SAISA->_hoops_ASHSA = _hoops_PAHSA;
		}

		if (ANYBIT(_hoops_SAISA->_hoops_ASHSA->_hoops_APHGA->_hoops_AHP->line_style->flags, _hoops_RHISA)) {
			Line_Rendition alter &	_hoops_AHISA = _hoops_PAHSA->_hoops_APHGA.Modify()->_hoops_AHP.Modify();

			if (!BIT(_hoops_SAISA->flags, HF_CHOPPED_ANY)) {
				if (BIT(_hoops_SAISA->flags, HF_CHOPPED_NEAR_START)) {
					_hoops_SAISA->flags |= HF_CHOPPED_END;
					_hoops_AHISA->flags |= _hoops_HHISA;
				}
				else if (BIT(_hoops_SAISA->flags, HF_CHOPPED_NEAR_END)) {
					_hoops_SAISA->flags |= HF_CHOPPED_START;
					_hoops_AHISA->flags |= _hoops_PHISA;
				}
			}
			else if (BIT(_hoops_SAISA->flags, HF_CHOPPED_START)) {
				if (BIT(_hoops_SAISA->flags, HF_CHOPPED_NEAR_START)) {
					_hoops_SAISA->flags |= HF_CHOPPED_MIDDLE;
					_hoops_AHISA->flags |= _hoops_HHISA|_hoops_PHISA;
				}
				else if (BIT(_hoops_SAISA->flags, HF_CHOPPED_NEAR_END)) {
					_hoops_SAISA->flags |= HF_CHOPPED_START;
					_hoops_AHISA->flags |= _hoops_PHISA;
				}
			}
			else if (BIT(_hoops_SAISA->flags, HF_CHOPPED_MIDDLE)) {
				_hoops_AHISA->flags |= _hoops_HHISA|_hoops_PHISA;
			}
			else if (BIT(_hoops_SAISA->flags, HF_CHOPPED_END)) {
				if (BIT(_hoops_SAISA->flags, HF_CHOPPED_NEAR_START)) {
					_hoops_SAISA->flags |= HF_CHOPPED_END;
					_hoops_AHISA->flags |= _hoops_HHISA;
				}
				else if (BIT(_hoops_SAISA->flags, HF_CHOPPED_NEAR_END)) {
					_hoops_SAISA->flags |= HF_CHOPPED_MIDDLE;
					_hoops_AHISA->flags |= _hoops_HHISA|_hoops_PHISA;
				}
			}
		}

		if (_hoops_IAISA->_hoops_HPISA != null) {
			--_hoops_IAISA->_hoops_HPISA->values;
			_hoops_IAISA->_hoops_HPISA = null;
		}
		if (_hoops_IAISA->values != 0)
			HD_Remove_Hidden_Followers (_hoops_IAISA, _hoops_SAISA->next);

		if ((_hoops_RPHSA = (_hoops_CAHSA alter *)_hoops_PAHSA->_hoops_GPHSA) != null) {
			if (BIT (_hoops_RPHSA->_hoops_RAGR, _hoops_CPHSA)) {
				_hoops_RPHSA->_hoops_HPHSA[0] = _hoops_GGIAR->_hoops_PIHR;
				_hoops_RPHSA->_hoops_HPHSA[1] = p1->_hoops_PIHR;
			}
			if (BIT (_hoops_RPHSA->_hoops_RAGR, _hoops_SPHSA)) {
				_hoops_RPHSA->rgba_colors[0] = _hoops_GGIAR->_hoops_IIRGA;
				_hoops_RPHSA->rgba_colors[1] = p1->_hoops_IIRGA;
			}
			if (BIT (_hoops_RPHSA->_hoops_RAGR, _hoops_GHHSA)) {
				_hoops_RPHSA->planes[0] = _hoops_GGIAR->plane;
				_hoops_RPHSA->planes[1] = p1->plane;
			}
			if (BIT (_hoops_RPHSA->_hoops_RAGR, _hoops_RHHSA)) {
				_hoops_RPHSA->param_width = _hoops_GGIAR->param_width;
				COPY_PARAMETER (_hoops_GGIAR->params, &_hoops_RPHSA->params[_hoops_RPHSA->param_width*0],_hoops_RPHSA->param_width);
				COPY_PARAMETER (p1->params, &_hoops_RPHSA->params[_hoops_RPHSA->param_width*1],_hoops_RPHSA->param_width);
			}
			else {
				_hoops_RPHSA->param_width = 0;
				_hoops_RPHSA->params = null;
			}
		}
	}

	_hoops_PAHSA->points[0] = _hoops_GGIAR->point;
	_hoops_PAHSA->points[1] = p1->point;

	if (_hoops_CPISA)
		_hoops_PAHSA->points[0].z = _hoops_PAHSA->points[1].z = _hoops_SPISA;

	_hoops_RSHSA (_hoops_SAISA);
}
#endif

#define _hoops_IHISA -1
#define _hoops_CHISA 0
#define _hoops_SHISA 1

GLOBAL_FUNCTION int HD_Cut_Hidden_By_Plane (
	Display_Context const *		dc,
	_hoops_CASS alter *				_hoops_GIISA,
	_hoops_ARPA alter *				plane,
	bool						_hoops_RIISA) {

	_hoops_SRHSA alter	*_hoops_ASHSA = _hoops_GIISA->_hoops_ASHSA;
	UNREFERENCED(_hoops_RIISA);

#ifndef _hoops_CRHSA

	if (plane->d == 0.0f && plane->c == 0.0f &&
		plane->b == 0.0f && plane->a == 0.0f) return _hoops_CHISA;

	/*
	 * _hoops_IRAA _hoops_HCR _hoops_RH _hoops_ISPAA _hoops_IIGR "_hoops_AIISA" _hoops_GPP _hoops_RH _hoops_APAP _hoops_PPAP _hoops_IIGR "_hoops_IPPA", _hoops_PPR
	 * _hoops_IRHH _hoops_IRS _hoops_CCAH _hoops_PIISA _hoops_GGSR _hoops_IIGR _hoops_CAPR.
	 */

	if (_hoops_ASHSA->type == _hoops_IPHSA) { /* _hoops_SARGA _hoops_IRS _hoops_SCPH */
		/*
		 * _hoops_SPR _hoops_PPSR _hoops_CGH _hoops_SHH _hoops_GPP _hoops_SPR _hoops_PPAP _hoops_IIGR _hoops_RH _hoops_IPPA, _hoops_PPR _hoops_PGCR
		 * _hoops_GPP _hoops_RH _hoops_RII _hoops_PPAP. _hoops_IPCP _hoops_SCPH _hoops_GRS _hoops_SHH _hoops_PRGS _hoops_CRGR _hoops_HRSP _hoops_IIPR
		 * _hoops_HIPH.
		 */

		int						_hoops_HIISA,
												_hoops_IIISA,
												_hoops_CIISA;
		float					_hoops_CGSIR[3];
		int						min,
												max;
		_hoops_GSHSA			_hoops_SIISA,
												_hoops_GCISA,
												_hoops_RCISA,
												_hoops_ACISA,
												_hoops_PCISA,
												_hoops_HCISA,
												_hoops_ICISA;
		bool				_hoops_CCISA,
												_hoops_SCISA;

		DC_Point alter		*_hoops_GHAS;
		float					_hoops_GSISA, _hoops_RSISA, _hoops_ASISA, _hoops_PSISA;

		/*
		 * _hoops_CAHA _hoops_GGSR _hoops_PGAP _hoops_CHR _hoops_RH _hoops_PGCR _hoops_RSSA _hoops_GPP _hoops_SPR _hoops_PPAP
		 * _hoops_PPR _hoops_PGAP _hoops_RH _hoops_SPR _hoops_GPP _hoops_RH _hoops_RII _hoops_PPAP.
		 */
		_hoops_GHAS = &_hoops_ASHSA->points[0];
		_hoops_CGSIR[0] = _hoops_GHAS->x * plane->a +
					  _hoops_GHAS->y * plane->b +
					  _hoops_GHAS->z * plane->c + plane->d;
		_hoops_GHAS = &_hoops_ASHSA->points[1];
		_hoops_CGSIR[1] = _hoops_GHAS->x * plane->a +
					  _hoops_GHAS->y * plane->b +
					  _hoops_GHAS->z * plane->c + plane->d;
		_hoops_GHAS = &_hoops_ASHSA->points[2];
		_hoops_CGSIR[2] = _hoops_GHAS->x * plane->a +
					  _hoops_GHAS->y * plane->b +
					  _hoops_GHAS->z * plane->c + plane->d;

		min = max = 0;	/* "0" _hoops_AGSR "_hoops_CIHA _hoops_AHHR" */
		if (_hoops_CGSIR[1] < _hoops_CGSIR[0]) min = 1;
		else if (_hoops_CGSIR[1] > _hoops_CGSIR[0]) max = 1;
		if (_hoops_CGSIR[2] < _hoops_CGSIR[min]) min = 2;
		else if (_hoops_CGSIR[2] > _hoops_CGSIR[max]) max = 2;

		/* _hoops_CACH _hoops_RPP _hoops_SR _hoops_CPSA _hoops_AA _hoops_ARCRA _hoops_RGR _hoops_IPPA */
		if (_hoops_CGSIR[max] < (float)(_hoops_HSISA/10))
			return _hoops_CHISA;
		if (_hoops_CGSIR[min] > (float)(-_hoops_HSISA/10))
			return _hoops_CHISA;

		/* _hoops_PPIP '_hoops_ISISA' _hoops_GAR _hoops_RH _hoops_PPSR _hoops_PGAP _hoops_HRGR _hoops_HAR _hoops_HICAA */
		_hoops_CIISA = 0;
		if (min == 0 || max == 0) _hoops_CIISA = 1;
		if (min == _hoops_CIISA || max == _hoops_CIISA)
			_hoops_CIISA = 2;

		/* _hoops_PPR _hoops_CSISA _hoops_PPR _hoops_RH _hoops_RII _hoops_SSISA _hoops_CHR _hoops_RH _hoops_RII _hoops_PGCR _hoops_RSSA */
		if (_hoops_CGSIR[_hoops_CIISA] < 0.0f) {
			_hoops_IIISA = min;
			_hoops_HIISA = max;
		}
		else {
			_hoops_IIISA = max;
			_hoops_HIISA = min;
		}

		_hoops_PSHSA(&_hoops_GCISA, &_hoops_ASHSA->points[_hoops_IIISA], false);
		_hoops_PSHSA(&_hoops_RCISA, &_hoops_ASHSA->points[_hoops_CIISA], false);
		_hoops_PSHSA(&_hoops_SIISA, &_hoops_ASHSA->points[_hoops_HIISA], false);

		_hoops_GSISA = _hoops_RRISA (plane, &_hoops_SIISA.point,
				&_hoops_GCISA.point, &_hoops_ACISA.point);

		_hoops_RSISA = _hoops_RRISA (plane, &_hoops_GCISA.point,
				&_hoops_SIISA.point, &_hoops_HCISA.point);

		_hoops_ASISA = _hoops_RRISA (plane, &_hoops_SIISA.point,
				&_hoops_RCISA.point, &_hoops_PCISA.point);

		_hoops_PSISA = _hoops_RRISA (plane, &_hoops_RCISA.point,
				&_hoops_SIISA.point, &_hoops_ICISA.point);

#define _hoops_GGCSA 1.0f

#ifndef _hoops_GGISA
		if (_hoops_RIISA) {

			Vector _hoops_HSPI,_hoops_ISPI,_hoops_CSPI;

			if ((int)_hoops_GCISA.point.y == (int)_hoops_HCISA.point.y &&
				(int)_hoops_GCISA.point.y == (int)_hoops_RCISA.point.y) {

				return _hoops_IHISA;
			}

			if ((int)_hoops_RCISA.point.y == (int)_hoops_HCISA.point.y &&
				(int)_hoops_RCISA.point.y == (int)_hoops_ICISA.point.y) {

				return _hoops_IHISA;
			}

			if ((int)_hoops_ACISA.point.y == (int)_hoops_PCISA.point.y &&
				(int)_hoops_ACISA.point.y == (int)_hoops_SIISA.point.y) {

				return _hoops_IHISA;
			}

			if ((int)_hoops_GCISA.point.x == (int)_hoops_HCISA.point.x &&
				(int)_hoops_GCISA.point.x == (int)_hoops_RCISA.point.x) {

				return _hoops_IHISA;
			}

			if ((int)_hoops_RCISA.point.x == (int)_hoops_HCISA.point.x &&
				(int)_hoops_RCISA.point.x == (int)_hoops_ICISA.point.x) {

				return _hoops_IHISA;
			}

			if ((int)_hoops_ACISA.point.x == (int)_hoops_PCISA.point.x &&
				(int)_hoops_ACISA.point.x == (int)_hoops_SIISA.point.x) {

				return _hoops_IHISA;
			}


			_hoops_HSPI.x = _hoops_GCISA.point.x - _hoops_HCISA.point.x;
			_hoops_HSPI.y = _hoops_GCISA.point.y - _hoops_HCISA.point.y;

			_hoops_ISPI.x = _hoops_HCISA.point.x - _hoops_RCISA.point.x;
			_hoops_ISPI.y = _hoops_HCISA.point.y - _hoops_RCISA.point.y;

			_hoops_CSPI.x = _hoops_RCISA.point.x - _hoops_GCISA.point.x;
			_hoops_CSPI.y = _hoops_RCISA.point.y - _hoops_GCISA.point.y;

			_hoops_HSPI.x = Abs(_hoops_HSPI.x);
			_hoops_HSPI.y = Abs(_hoops_HSPI.y);
			_hoops_ISPI.x = Abs(_hoops_ISPI.x);
			_hoops_ISPI.y = Abs(_hoops_ISPI.y);
			_hoops_CSPI.x = Abs(_hoops_CSPI.x);
			_hoops_CSPI.y = Abs(_hoops_CSPI.y);

			if ((_hoops_HSPI.x < _hoops_GGCSA && _hoops_HSPI.y < _hoops_GGCSA) ||
				(_hoops_ISPI.x < _hoops_GGCSA && _hoops_ISPI.y < _hoops_GGCSA) ||
				(_hoops_CSPI.x < _hoops_GGCSA && _hoops_CSPI.y < _hoops_GGCSA)) {

				return _hoops_IHISA;
			}

			_hoops_HSPI.x = _hoops_RCISA.point.x - _hoops_HCISA.point.x;
			_hoops_HSPI.y = _hoops_RCISA.point.y - _hoops_HCISA.point.y;

			_hoops_ISPI.x = _hoops_HCISA.point.x - _hoops_ICISA.point.x;
			_hoops_ISPI.y = _hoops_HCISA.point.y - _hoops_ICISA.point.y;

			_hoops_CSPI.x = _hoops_ICISA.point.x - _hoops_RCISA.point.x;
			_hoops_CSPI.y = _hoops_ICISA.point.y - _hoops_RCISA.point.y;

			_hoops_HSPI.x = Abs(_hoops_HSPI.x);
			_hoops_HSPI.y = Abs(_hoops_HSPI.y);
			_hoops_ISPI.x = Abs(_hoops_ISPI.x);
			_hoops_ISPI.y = Abs(_hoops_ISPI.y);
			_hoops_CSPI.x = Abs(_hoops_CSPI.x);
			_hoops_CSPI.y = Abs(_hoops_CSPI.y);

			if ((_hoops_HSPI.x < _hoops_GGCSA && _hoops_HSPI.y < _hoops_GGCSA) ||
				(_hoops_ISPI.x < _hoops_GGCSA && _hoops_ISPI.y < _hoops_GGCSA) ||
				(_hoops_CSPI.x < _hoops_GGCSA && _hoops_CSPI.y < _hoops_GGCSA)) {

				return _hoops_IHISA;
			}

			_hoops_HSPI.x = _hoops_ACISA.point.x - _hoops_PCISA.point.x;
			_hoops_HSPI.y = _hoops_ACISA.point.y - _hoops_PCISA.point.y;

			_hoops_ISPI.x = _hoops_PCISA.point.x - _hoops_SIISA.point.x;
			_hoops_ISPI.y = _hoops_PCISA.point.y - _hoops_SIISA.point.y;

			_hoops_CSPI.x = _hoops_SIISA.point.x - _hoops_ACISA.point.x;
			_hoops_CSPI.y = _hoops_SIISA.point.y - _hoops_ACISA.point.y;

			_hoops_HSPI.x = Abs(_hoops_HSPI.x);
			_hoops_HSPI.y = Abs(_hoops_HSPI.y);
			_hoops_ISPI.x = Abs(_hoops_ISPI.x);
			_hoops_ISPI.y = Abs(_hoops_ISPI.y);
			_hoops_CSPI.x = Abs(_hoops_CSPI.x);
			_hoops_CSPI.y = Abs(_hoops_CSPI.y);

			if ((_hoops_HSPI.x < _hoops_GGCSA && _hoops_HSPI.y < _hoops_GGCSA) ||
				(_hoops_ISPI.x < _hoops_GGCSA && _hoops_ISPI.y < _hoops_GGCSA) ||
				(_hoops_CSPI.x < _hoops_GGCSA && _hoops_CSPI.y < _hoops_GGCSA)) {

				return _hoops_IHISA;
			}
		}
#endif

		if (_hoops_IIISA == (_hoops_HIISA+1)%3) {
			_hoops_CCISA = _hoops_GCISA._hoops_CCHSA;
			_hoops_SCISA = _hoops_SIISA._hoops_CCHSA;
		}
		else {
			_hoops_CCISA = _hoops_SIISA._hoops_CCHSA;
			_hoops_SCISA = _hoops_RCISA._hoops_CCHSA;
		}

		_hoops_HGISA (dc, _hoops_GIISA, &_hoops_GCISA, _hoops_IIISA);
		_hoops_HGISA (dc, _hoops_GIISA, &_hoops_RCISA, _hoops_CIISA);
		_hoops_HGISA (dc, _hoops_GIISA, &_hoops_SIISA, _hoops_HIISA);

		_hoops_CRISA (_hoops_ASHSA->_hoops_APHGA, plane,
							&_hoops_SIISA, &_hoops_GCISA,
							&_hoops_ACISA, _hoops_CCISA, _hoops_GSISA);

		_hoops_CRISA (_hoops_ASHSA->_hoops_APHGA, plane,
							&_hoops_GCISA, &_hoops_SIISA,
							&_hoops_HCISA, _hoops_CCISA, _hoops_RSISA);

		_hoops_CRISA (_hoops_ASHSA->_hoops_APHGA, plane,
							&_hoops_SIISA, &_hoops_RCISA,
							&_hoops_PCISA, _hoops_SCISA, _hoops_ASISA);

		_hoops_CRISA (_hoops_ASHSA->_hoops_APHGA, plane,
							&_hoops_RCISA, &_hoops_SIISA,
							&_hoops_ICISA, _hoops_SCISA, _hoops_PSISA);


		/*
		 * _hoops_IPCP _hoops_CIS _hoops_GSSS '_hoops_AIISA' _hoops_IS _hoops_RSGR _hoops_GH _hoops_PHPC _hoops_HPGR _hoops_IRS _hoops_HSSP
		 * _hoops_GGR *_hoops_ISSC* _hoops_IIGR _hoops_RH _hoops_IPPA _hoops_PPR _hoops_AIISA->_hoops_SPS _hoops_IS _hoops_PPSR _hoops_HPGR _hoops_IRS _hoops_HSSP
		 * _hoops_GGR *_hoops_RIPS* _hoops_IIGR _hoops_RH _hoops_IPPA. _hoops_HHIGR _hoops_ASSP'_hoops_RA _hoops_ACPA _hoops_AHCA _hoops_ISCP _hoops_HRSSR
		 * _hoops_HSSP.
		 * _hoops_HIPR, _hoops_SR _hoops_HS _hoops_IS _hoops_SHH _hoops_RHRIR _hoops_IS _hoops_PPSI _hoops_IRAP _hoops_SPPR _hoops_IGIAR _hoops_RH _hoops_RGCSA.
		 */

		if (_hoops_CGSIR[_hoops_HIISA] > 0.0f) {
			/* _hoops_CSISA _hoops_HRGR _hoops_SGIP _hoops_SGGR - _hoops_PPIP _hoops_SCH _hoops_IS _hoops_SHH _hoops_HPGR _hoops_RH _hoops_RIPS _hoops_IIGR _hoops_RH _hoops_HIGR */
			bool		_hoops_AGCSA, _hoops_PGCSA;

			_hoops_AGCSA = _hoops_RCISA._hoops_CCHSA;
			_hoops_RCISA._hoops_CCHSA = false;
			_hoops_HAISA (dc, _hoops_GIISA, false, &_hoops_GCISA, &_hoops_HCISA, &_hoops_RCISA);
			_hoops_RCISA._hoops_CCHSA = _hoops_AGCSA;

#ifdef _hoops_AGISA
			{
			float					_hoops_SPISA;
			_hoops_SPISA = _hoops_GIISA->_hoops_APHGA->transform_rendition->_hoops_PCHH -
				(_hoops_GIISA->_hoops_APHGA->transform_rendition->_hoops_CHIH+
					_hoops_GIISA->_hoops_APHGA->transform_rendition->_hoops_SHIH);

			_hoops_GIISA->type = _hoops_AHHSA;
			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_GCISA, &_hoops_RCISA, true, _hoops_SPISA);
			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_RCISA, &_hoops_SIISA, true, _hoops_SPISA);
			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_SIISA, &_hoops_GCISA, true, _hoops_SPISA);

			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_GCISA, &_hoops_HCISA, true, _hoops_SPISA);
			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_HCISA, &_hoops_RCISA, true, _hoops_SPISA);
			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_RCISA, &_hoops_GCISA, true, _hoops_SPISA);

			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_RCISA, &_hoops_HCISA, true, _hoops_SPISA);
			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_HCISA, &_hoops_ICISA, true, _hoops_SPISA);
			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_ICISA, &_hoops_RCISA, true, _hoops_SPISA);

			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_ACISA, &_hoops_PCISA, true, _hoops_SPISA);
			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_HCISA, &_hoops_ICISA, true, _hoops_SPISA);
			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_SIISA, &_hoops_ACISA, true, _hoops_SPISA);
			_hoops_GIISA->type = _hoops_IPHSA;
			}
#endif

			_hoops_AGCSA = _hoops_HCISA._hoops_CCHSA;
			_hoops_PGCSA = _hoops_ICISA._hoops_CCHSA;
			_hoops_HCISA._hoops_CCHSA = false;
			_hoops_ICISA._hoops_CCHSA = false;
			_hoops_HAISA (dc, _hoops_GIISA, false, &_hoops_RCISA, &_hoops_HCISA, &_hoops_ICISA);
			_hoops_HCISA._hoops_CCHSA = _hoops_AGCSA;
			_hoops_ICISA._hoops_CCHSA = _hoops_PGCSA;

			_hoops_AGCSA = _hoops_ACISA._hoops_CCHSA;
			_hoops_PGCSA = _hoops_PCISA._hoops_CCHSA;
			_hoops_ACISA._hoops_CCHSA = false;
			_hoops_PCISA._hoops_CCHSA = false;
			_hoops_HAISA (dc, _hoops_GIISA, true, &_hoops_ACISA, &_hoops_PCISA, &_hoops_SIISA);
			_hoops_ACISA._hoops_CCHSA = _hoops_AGCSA;
			_hoops_PCISA._hoops_CCHSA = _hoops_PGCSA;
		}
		else {
			/* _hoops_CSISA _hoops_HRGR _hoops_GGGR - _hoops_PPIP _hoops_SCH _hoops_IS _hoops_SHH *_hoops_GIAP* _hoops_GPP _hoops_RH _hoops_HIGR */
			bool		_hoops_AGCSA, _hoops_PGCSA;

			_hoops_AGCSA = _hoops_RCISA._hoops_CCHSA;
			_hoops_RCISA._hoops_CCHSA = false;
			_hoops_HAISA (dc, _hoops_GIISA, false, &_hoops_GCISA, &_hoops_HCISA, &_hoops_RCISA);
			_hoops_RCISA._hoops_CCHSA = _hoops_AGCSA;

#ifdef _hoops_AGISA
			{
			float					_hoops_SPISA;
			_hoops_SPISA = _hoops_GIISA->_hoops_APHGA->transform_rendition->_hoops_PCHH -
				(_hoops_GIISA->_hoops_APHGA->transform_rendition->_hoops_CHIH+
					_hoops_GIISA->_hoops_APHGA->transform_rendition->_hoops_SHIH);

			_hoops_GIISA->type = _hoops_AHHSA;
			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_GCISA, &_hoops_RCISA, true, _hoops_SPISA);
			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_RCISA, &_hoops_SIISA, true, _hoops_SPISA);
			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_SIISA, &_hoops_GCISA, true, _hoops_SPISA);

			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_GCISA, &_hoops_HCISA, true, _hoops_SPISA);
			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_HCISA, &_hoops_RCISA, true, _hoops_SPISA);
			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_RCISA, &_hoops_GCISA, true, _hoops_SPISA);

			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_RCISA, &_hoops_HCISA, true, _hoops_SPISA);
			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_HCISA, &_hoops_ICISA, true, _hoops_SPISA);
			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_ICISA, &_hoops_RCISA, true, _hoops_SPISA);

			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_ACISA, &_hoops_PCISA, true, _hoops_SPISA);
			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_HCISA, &_hoops_ICISA, true, _hoops_SPISA);
			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_SIISA, &_hoops_ACISA, true, _hoops_SPISA);
			_hoops_GIISA->type = _hoops_IPHSA;
			}
#endif

			_hoops_AGCSA = _hoops_PCISA._hoops_CCHSA;
			_hoops_PCISA._hoops_CCHSA = false;
			_hoops_HAISA (dc, _hoops_GIISA, false, &_hoops_ACISA, &_hoops_PCISA, &_hoops_SIISA);
			_hoops_PCISA._hoops_CCHSA = _hoops_AGCSA;

			_hoops_AGCSA = _hoops_HCISA._hoops_CCHSA;
			_hoops_PGCSA = _hoops_ICISA._hoops_CCHSA;
			_hoops_HCISA._hoops_CCHSA = false;
			_hoops_ICISA._hoops_CCHSA = false;
			_hoops_HAISA (dc, _hoops_GIISA, true, &_hoops_RCISA, &_hoops_HCISA, &_hoops_ICISA);
			_hoops_HCISA._hoops_CCHSA = _hoops_AGCSA;
			_hoops_ICISA._hoops_CCHSA = _hoops_PGCSA;
		}

		_hoops_SSHSA(_hoops_SIISA);
		_hoops_SSHSA(_hoops_GCISA);
		_hoops_SSHSA(_hoops_RCISA);
		_hoops_SSHSA(_hoops_ACISA);
		_hoops_SSHSA(_hoops_PCISA);
		_hoops_SSHSA(_hoops_HCISA);
		_hoops_SSHSA(_hoops_ICISA);

		return _hoops_SHISA;
	}
	else if (_hoops_ASHSA->type == _hoops_AHHSA) {
		/*
		 * _hoops_SPR _hoops_PPSR _hoops_CGH _hoops_SHH _hoops_GPP _hoops_SPR _hoops_PPAP _hoops_IIGR _hoops_RH _hoops_IPPA, _hoops_PPR _hoops_SPR
		 * _hoops_GPP _hoops_RH _hoops_RII _hoops_PPAP. _hoops_IPCP _hoops_III _hoops_GRS _hoops_SHH _hoops_PRGS _hoops_CRGR _hoops_PGCR _hoops_IIPR
		 * _hoops_APGR.
		 */

		float					_hoops_CGSIR[2];
		int						min,
												max;
		_hoops_GSHSA			_hoops_HGCSA,
												_hoops_IGCSA,
												_hoops_CGCSA,
												_hoops_SGCSA;
		DC_Point alter		*_hoops_GHAS;
		float					_hoops_GRCSA, _hoops_RRCSA;

		/*
		 * _hoops_CAHA _hoops_GGSR _hoops_PGAP _hoops_PPSR _hoops_HRGR _hoops_GPP _hoops_GRR _hoops_PPAP _hoops_IIGR _hoops_RH _hoops_IPPA
		 */
		_hoops_GHAS = &_hoops_ASHSA->points[0];
		_hoops_CGSIR[0] = _hoops_GHAS->x * plane->a +
					  _hoops_GHAS->y * plane->b +
					  _hoops_GHAS->z * plane->c + plane->d;
		_hoops_GHAS = &_hoops_ASHSA->points[1];
		_hoops_CGSIR[1] = _hoops_GHAS->x * plane->a +
					  _hoops_GHAS->y * plane->b +
					  _hoops_GHAS->z * plane->c + plane->d;

		min = max = 0;	/* "0" _hoops_AGSR "_hoops_CIHA _hoops_AHHR" */
		if (_hoops_CGSIR[1] < _hoops_CGSIR[0])
			min = 1;
		else if (_hoops_CGSIR[1] > _hoops_CGSIR[0])
			max = 1;

		/* _hoops_CACH _hoops_RPP _hoops_SR _hoops_CPSA _hoops_AA _hoops_ARCRA _hoops_RGR _hoops_IPPA */
		if (_hoops_CGSIR[max] <	 _hoops_HSISA/10.0f ||
			_hoops_CGSIR[min] > -_hoops_HSISA/10.0f)
			return _hoops_CHISA;

		_hoops_PSHSA(&_hoops_HGCSA, &_hoops_ASHSA->points[min], false);
		_hoops_PSHSA(&_hoops_IGCSA, &_hoops_ASHSA->points[max], false);

		_hoops_HGISA (dc, _hoops_GIISA, &_hoops_HGCSA, min);
		_hoops_HGISA (dc, _hoops_GIISA, &_hoops_IGCSA, max);

		_hoops_GRCSA = _hoops_RRISA (plane, &_hoops_HGCSA.point, &_hoops_IGCSA.point, &_hoops_CGCSA.point);
		_hoops_RRCSA = _hoops_RRISA (plane, &_hoops_IGCSA.point, &_hoops_HGCSA.point, &_hoops_SGCSA.point);

		_hoops_CRISA (_hoops_ASHSA->_hoops_APHGA, plane, &_hoops_HGCSA, &_hoops_IGCSA,
							&_hoops_CGCSA, false, _hoops_GRCSA);

		_hoops_CRISA (_hoops_ASHSA->_hoops_APHGA, plane, &_hoops_IGCSA, &_hoops_HGCSA,
							&_hoops_SGCSA, false, _hoops_RRCSA);

		/*
		 * _hoops_IPCP _hoops_CIS _hoops_GSSS '_hoops_AIISA' _hoops_IS _hoops_RSGR _hoops_GH _hoops_PHPC _hoops_HPGR _hoops_IRS _hoops_III
		 * _hoops_GGR *_hoops_ISSC* _hoops_IIGR _hoops_RH _hoops_IPPA _hoops_PPR _hoops_AIISA->_hoops_SPS _hoops_IS _hoops_PPSR _hoops_HPGR _hoops_IRS _hoops_III
		 * _hoops_GGR *_hoops_RIPS* _hoops_IIGR _hoops_RH _hoops_IPPA.
		 */

		/* _hoops_ARP _hoops_IRS _hoops_RIP _hoops_SGS _hoops_ARCSA _hoops_IHHH _hoops_IGH _hoops_RH _hoops_HSPP _hoops_IIGR _hoops_RH _hoops_III _hoops_CSAP _hoops_GPP _hoops_RH _hoops_GHISA
		 * _hoops_PAR _hoops_PRCSA _hoops_IIGR _hoops_RH _hoops_AACC. _hoops_CPGP _hoops_SR'_hoops_RISP _hoops_SAHR _hoops_CPHR _hoops_IRS _hoops_CCAH _hoops_AACC, _hoops_SCAC _hoops_GGSR _hoops_HISI
		 * _hoops_PGHC _hoops_PIRA _hoops_IIH _hoops_GHCA _hoops_HS _hoops_RPII, _hoops_PPR _hoops_ASAR-_hoops_ARP _hoops_SCH _hoops_IIHA _hoops_GPP _hoops_RH _hoops_PGCAA _hoops_AACC.*/
		_hoops_GIISA->flags &= ~(HF_CHOPPED_NEAR_START|HF_CHOPPED_NEAR_END);
		if (min == 0) {
			_hoops_GIISA->flags |= HF_CHOPPED_NEAR_START;
			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_HGCSA, &_hoops_CGCSA, false, 0.0f);
			_hoops_IPISA (dc, _hoops_GIISA, true, &_hoops_SGCSA, &_hoops_IGCSA, false, 0.0f);
		}
		else{
			_hoops_GIISA->flags |= HF_CHOPPED_NEAR_END;
			_hoops_IPISA (dc, _hoops_GIISA, false, &_hoops_CGCSA, &_hoops_HGCSA, false, 0.0f);
			_hoops_IPISA (dc, _hoops_GIISA, true, &_hoops_IGCSA, &_hoops_SGCSA, false, 0.0f);
		}



		_hoops_SSHSA(_hoops_HGCSA);
		_hoops_SSHSA(_hoops_IGCSA);
		_hoops_SSHSA(_hoops_CGCSA);
		_hoops_SSHSA(_hoops_SGCSA);

		return _hoops_SHISA;
	}
	else if (_hoops_HRCSA (_hoops_ASHSA->type)) { /* _hoops_SARGA _hoops_SCIRA */
		int						_hoops_IRCSA = _hoops_ASHSA->count;
		DC_Point				_hoops_CRCSA[128], _hoops_SRCSA[128];
		DC_Point alter		*_hoops_GACSA = _hoops_CRCSA, *_hoops_RACSA = _hoops_SRCSA;
		DC_Point alter		*list[2];
		DC_Point const		*_hoops_GHAS = _hoops_ASHSA->points;
		DC_Point const		*_hoops_HSPS;
		int						_hoops_AACSA=0, _hoops_PACSA, _hoops_HACSA;
		bool				_hoops_IACSA[128], _hoops_CACSA[128];
		bool alter		*_hoops_SACSA = _hoops_IACSA, *_hoops_GPCSA = _hoops_CACSA;
		bool alter		*_hoops_RPCSA[2];
		bool const		*_hoops_APCSA = null;
		bool const		*_hoops_PPCSA = null;
		float					_hoops_HPCSA,
												_hoops_IPCSA,
												_hoops_CPCSA;
		int						count = _hoops_IRCSA;

		if (_hoops_IRCSA*2 > _hoops_GGAPR(_hoops_CRCSA)) {
			POOL_ALLOC_ARRAY (_hoops_GACSA, _hoops_IRCSA*2, DC_Point, dc->memory_pool);
			POOL_ALLOC_ARRAY (_hoops_RACSA, _hoops_IRCSA*2, DC_Point, dc->memory_pool);
			POOL_ALLOC_ARRAY (_hoops_SACSA, _hoops_IRCSA*2, bool, dc->memory_pool);
			POOL_ALLOC_ARRAY (_hoops_GPCSA, _hoops_IRCSA*2, bool, dc->memory_pool);
		}
		list[0] = _hoops_GACSA;
		list[1] = _hoops_RACSA;
		_hoops_RPCSA[0] = _hoops_SACSA;
		_hoops_RPCSA[1] = _hoops_GPCSA;
		if (_hoops_ASHSA->type == _hoops_IAHSA) {
			_hoops_RPCSA[0] = _hoops_RPCSA[1] = null; /* _hoops_SR _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_PGGC _hoops_RH _hoops_SGI */
		}
		else if (_hoops_ASHSA->type == _hoops_HCHSA) {
			_hoops_ICHSA *	_hoops_SSRPR = (_hoops_ICHSA *)_hoops_ASHSA->_hoops_GPHSA;

			_hoops_PPCSA = _hoops_APCSA = _hoops_SSRPR->_hoops_CCHSA;	/* _hoops_SR _hoops_HS _hoops_PGHC _hoops_ACPP */
		}

		/* _hoops_AAHP _hoops_PIHA _hoops_PSSP _hoops_PAR _hoops_SHH _hoops_CRGP _hoops_HSAR _hoops_GGR _hoops_PGII-_hoops_GPGP-_hoops_SPCSA! */

		_hoops_CPCSA = -plane->d + (float)(_hoops_HSISA / 10);
		_hoops_IPCSA = -plane->d - (float)(_hoops_HSISA / 10);

		/*
		 * _hoops_IS _hoops_HSPP, _hoops_HAPR _hoops_AARI _hoops_HCHAR _hoops_IH _hoops_IRS _hoops_PPSR _hoops_SGS'_hoops_GRI _hoops_GHCSA
		 * _hoops_GPP _hoops_RH _hoops_APAP _hoops_PPAP _hoops_PAR _hoops_GHCSA _hoops_GPP _hoops_RH _hoops_SGIP _hoops_PPAP, _hoops_PPR
		 * _hoops_SGH _hoops_SGS _hoops_IS _hoops_IPASR _hoops_AIISA->_hoops_RHCSA _hoops_IS _hoops_APAP _hoops_PAR _hoops_SGIP.
		 */

		while (count-- > 0) {
			_hoops_HPCSA = _hoops_GHAS->x * plane->a +
				  _hoops_GHAS->y * plane->b +
				  _hoops_GHAS->z * plane->c;

			if (_hoops_HPCSA < _hoops_IPCSA) {
				_hoops_AACSA = 0;
				break;
			}
			else if (_hoops_HPCSA > _hoops_CPCSA) {
				_hoops_AACSA = 1;
				break;
			}
			if (--count == 0) {
				if (_hoops_GACSA != _hoops_CRCSA) {
					FREE_ARRAY (_hoops_GACSA, _hoops_IRCSA*2, DC_Point);
					FREE_ARRAY (_hoops_RACSA, _hoops_IRCSA*2, DC_Point);
					FREE_ARRAY (_hoops_SACSA, _hoops_IRCSA*2, bool);
					FREE_ARRAY (_hoops_GPCSA, _hoops_IRCSA*2, bool);
				}
				return _hoops_CHISA;
			}
			++_hoops_GHAS;
			if (_hoops_APCSA)
				++_hoops_APCSA;
		}

		{
			int			_hoops_AHCSA = _hoops_GHAS - _hoops_ASHSA->points + 1;

			_hoops_AIGA (_hoops_ASHSA->points, _hoops_AHCSA, DC_Point, list[_hoops_AACSA]);
			list[_hoops_AACSA] += _hoops_AHCSA;
		}

		_hoops_HACSA = _hoops_PACSA = _hoops_AACSA;
		while (count-- > 0) {
			_hoops_HSPS = _hoops_GHAS++;
			if (_hoops_APCSA)
				++_hoops_APCSA;

			_hoops_HPCSA = _hoops_GHAS->x * plane->a +
				  _hoops_GHAS->y * plane->b +
				  _hoops_GHAS->z * plane->c;

			/* _hoops_SCH'_hoops_GRI _hoops_PGI _hoops_GHCSA "_hoops_APAP", _hoops_GHCSA "_hoops_SGIP", _hoops_PAR
			 * _hoops_SR _hoops_PAH'_hoops_RA _hoops_CRGS & _hoops_SGH _hoops_RH _hoops_PGHC _hoops_PIRA.
			 */

			_hoops_PACSA = _hoops_AACSA;
			if (_hoops_HPCSA < _hoops_IPCSA)
				_hoops_AACSA = 0;
			else if (_hoops_HPCSA > _hoops_CPCSA)
				_hoops_AACSA = 1;

			if (_hoops_AACSA != _hoops_PACSA) { /* _hoops_RPP _hoops_IIH _hoops_CSAP _hoops_IRS _hoops_PHCSA */
				/* _hoops_PPSI _hoops_PCCP _hoops_RSGR _hoops_GPP _hoops_RH _hoops_PGHC _hoops_AASH */
				_hoops_RRISA (plane,
								   _hoops_HSPS,
								   _hoops_GHAS,
								   list[_hoops_PACSA]);
				++list[_hoops_PACSA];

				if (_hoops_RPCSA[_hoops_PACSA] != null) {
					if (_hoops_APCSA != null)
						*_hoops_RPCSA[_hoops_PACSA] = *_hoops_APCSA;
					else
						*_hoops_RPCSA[_hoops_PACSA] = true;
					++_hoops_RPCSA[_hoops_PACSA];
				}

				/* _hoops_PPSI _hoops_IRS _hoops_HSPP _hoops_GPP _hoops_RH _hoops_CCAH _hoops_AASH */
				_hoops_RRISA (plane,
								   _hoops_GHAS,
								   _hoops_HSPS,
								   list[_hoops_AACSA]);
				++list[_hoops_AACSA];

				if (_hoops_RPCSA[_hoops_AACSA] != null) {
					*_hoops_RPCSA[_hoops_AACSA] = false;
					++_hoops_RPCSA[_hoops_AACSA];
				}
			}

			_hoops_RSAI (_hoops_GHAS, DC_Point, list[_hoops_AACSA]);
			++list[_hoops_AACSA];
		}

		_hoops_HSPS = _hoops_GHAS;
		_hoops_GHAS = _hoops_ASHSA->points;
		_hoops_APCSA = _hoops_PPCSA;
		if (_hoops_AACSA != _hoops_HACSA) {
			/* _hoops_PPSI _hoops_PCCP _hoops_RSGR _hoops_GPP _hoops_RH _hoops_PGHC _hoops_AASH */
			_hoops_RRISA (plane,
							   _hoops_HSPS,
							   _hoops_GHAS,
							   list[_hoops_AACSA]);
			++list[_hoops_AACSA];

			if (_hoops_RPCSA[_hoops_AACSA] != null) {
				if (_hoops_APCSA != null)
					*_hoops_RPCSA[_hoops_AACSA] = *_hoops_APCSA;
				else
					*_hoops_RPCSA[_hoops_AACSA] = true;
				++_hoops_RPCSA[_hoops_AACSA];
			}

			_hoops_AACSA = _hoops_HACSA;

			/* _hoops_PPSI _hoops_IRS _hoops_HSPP _hoops_GPP _hoops_RH _hoops_CCAH _hoops_AASH */
			_hoops_RRISA (plane,
							   _hoops_GHAS,
							   _hoops_HSPS,
							   list[_hoops_AACSA]);
			++list[_hoops_AACSA];

			if (_hoops_RPCSA[_hoops_AACSA] != null) {
				*_hoops_RPCSA[_hoops_AACSA] = false;
				++_hoops_RPCSA[_hoops_AACSA];
			}
		}


		if (list[0] == _hoops_GACSA || list[1] == _hoops_RACSA) {	/* _hoops_PSP _hoops_HPHR _hoops_AACC _hoops_IIAC */
			if (_hoops_GACSA != _hoops_CRCSA) {
				FREE_ARRAY (_hoops_GACSA, _hoops_IRCSA*2, DC_Point);
				FREE_ARRAY (_hoops_RACSA, _hoops_IRCSA*2, DC_Point);
				FREE_ARRAY (_hoops_SACSA, _hoops_IRCSA*2, bool);
				FREE_ARRAY (_hoops_GPCSA, _hoops_IRCSA*2, bool);
			}
			return _hoops_CHISA;
		}
		else {
			_hoops_CASS alter			*_hoops_HHCSA;
			_hoops_SRHSA alter	*_hoops_PAHSA;

			POOL_ZALLOC (_hoops_HHCSA, _hoops_CASS, dc->memory_pool);
			POOL_ZALLOC (_hoops_PAHSA, _hoops_SRHSA, dc->memory_pool);
			_hoops_ICAI(_hoops_PAHSA);
			_hoops_HHCSA->_hoops_ASHSA = _hoops_PAHSA;
			_hoops_PAHSA->type = _hoops_ASHSA->type;

			_hoops_PAHSA->_hoops_APHGA = _hoops_ASHSA->_hoops_APHGA;
			_hoops_PAHSA->plane = _hoops_ASHSA->plane;


			_hoops_HHCSA->next = _hoops_GIISA->next;
			_hoops_GIISA->next->prev = _hoops_HHCSA;
			_hoops_GIISA->next = _hoops_HHCSA;
			_hoops_HHCSA->prev = _hoops_GIISA;

			_hoops_HHCSA->_hoops_HPISA = null;
			_hoops_HHCSA->values = 0;

			if (_hoops_GIISA->_hoops_HPISA != null) {
				--_hoops_GIISA->_hoops_HPISA->values;
				_hoops_GIISA->_hoops_HPISA = null;
			}
			if (_hoops_GIISA->values != 0)
				HD_Remove_Hidden_Followers (_hoops_GIISA, _hoops_HHCSA->next);

			_hoops_PAHSA->count = list[0] - _hoops_GACSA;
			_hoops_HAHSA(_hoops_GACSA, _hoops_PAHSA->count, DC_Point, _hoops_PAHSA->points, dc->memory_pool);

			if (_hoops_ASHSA->_hoops_HSAI > 1) {
				_hoops_GIISA->_hoops_ASHSA = _hoops_GAHSA(dc, _hoops_ASHSA, false);
				HD_Free_Hidden_Payload(dc, _hoops_ASHSA);
				_hoops_ASHSA = _hoops_GIISA->_hoops_ASHSA;
			}
			else{
				_hoops_SRHSA* _hoops_IHCSA = _hoops_ASHSA;

				_hoops_GIISA->_hoops_ASHSA = _hoops_ASHSA = _hoops_GAHSA(dc, _hoops_ASHSA, false);

				if (_hoops_IHCSA->_hoops_CHCSA || _hoops_IHCSA->next)
					_hoops_ASHSA->next = _hoops_IHCSA;
				else
					HD_Free_Hidden_Payload(dc, _hoops_IHCSA);
			}
			_hoops_ASHSA->count = list[1] - _hoops_RACSA;
			_hoops_HAHSA(_hoops_RACSA, _hoops_ASHSA->count, DC_Point, _hoops_ASHSA->points, dc->memory_pool);


			switch (_hoops_ASHSA->type) {
				case _hoops_HCHSA: {
					_hoops_ICHSA *	_hoops_SSRPR = (_hoops_ICHSA *)_hoops_ASHSA->_hoops_GPHSA;

					FREE_ARRAY (_hoops_SSRPR->_hoops_CCHSA, _hoops_IRCSA, bool);
					FREE (_hoops_SSRPR, _hoops_ICHSA);
				}	_hoops_HHHI;

				case _hoops_ACHSA: {
					_hoops_ICHSA *	_hoops_SSRPR;

					_hoops_PAHSA->type = _hoops_ASHSA->type = _hoops_HCHSA;

					POOL_ALLOC (_hoops_SSRPR, _hoops_ICHSA, dc->memory_pool);
					_hoops_PAHSA->_hoops_GPHSA = (_hoops_APHSA *)_hoops_SSRPR;
					_hoops_HAHSA(_hoops_RPCSA[0], _hoops_PAHSA->count, bool, _hoops_SSRPR->_hoops_CCHSA, dc->memory_pool);

					POOL_ALLOC (_hoops_SSRPR, _hoops_ICHSA, dc->memory_pool);
					_hoops_ASHSA->_hoops_GPHSA = (_hoops_APHSA *)_hoops_SSRPR;
					_hoops_HAHSA(_hoops_RPCSA[1], _hoops_ASHSA->count, bool, _hoops_SSRPR->_hoops_CCHSA, dc->memory_pool);
				}	break;

				case _hoops_IAHSA: {
					_hoops_CAHSA alter	*_hoops_SAHSA;
					_hoops_CAHSA alter	*_hoops_RPHSA;

					if ((_hoops_SAHSA = (_hoops_CAHSA alter *)_hoops_ASHSA->_hoops_GPHSA) != null) {
						POOL_ALLOC (_hoops_RPHSA, _hoops_CAHSA, dc->memory_pool);
						_hoops_PAHSA->_hoops_GPHSA = (_hoops_APHSA alter *)_hoops_RPHSA;
						_hoops_RPHSA->_hoops_RAGR = _hoops_SAHSA->_hoops_RAGR;
						_hoops_RPHSA->param_flags = 0;

						if (BIT (_hoops_SAHSA->_hoops_RAGR, _hoops_PPHSA)) {
							POOL_ALLOC_ARRAY (_hoops_RPHSA->_hoops_HPHSA, 1, RGBAS32, dc->memory_pool);
							_hoops_RPHSA->_hoops_HPHSA[0] = _hoops_SAHSA->_hoops_HPHSA[0];
						}
						else
							_hoops_RPHSA->_hoops_HPHSA = null;
						_hoops_RPHSA->rgba_colors = null;
						_hoops_RPHSA->planes = null;
						_hoops_RPHSA->params = null;
						_hoops_RPHSA->param_width = 0;
					}
					else
						_hoops_PAHSA->_hoops_GPHSA = null;
				}	break;

				default: {
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected hidden cut type");
					_hoops_PAHSA->_hoops_GPHSA = null;
				}	break;
			}

			_hoops_RSHSA (_hoops_GIISA);
			_hoops_RSHSA (_hoops_HHCSA);

			if (_hoops_GACSA != _hoops_CRCSA) {
				FREE_ARRAY (_hoops_GACSA, _hoops_IRCSA*2, DC_Point);
				FREE_ARRAY (_hoops_RACSA, _hoops_IRCSA*2, DC_Point);
				FREE_ARRAY (_hoops_SACSA, _hoops_IRCSA*2, bool);
				FREE_ARRAY (_hoops_GPCSA, _hoops_IRCSA*2, bool);
			}
			return _hoops_SHISA;
		}
	}

#endif
	return _hoops_CHISA;  /* _hoops_PAH'_hoops_RA _hoops_SARGA _hoops_IRS _hoops_HISI-_hoops_SCH-_hoops_HRGR */
}

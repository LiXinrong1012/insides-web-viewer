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
 * $Id: obf_tmp.txt 1.156 2011-01-14 22:23:34 reuben Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "patterns.h"
#include "phedron.h"
#include "hd_proto.h"
#include "hi_proto.h"

local void _hoops_HAISS (
	Net_Rendition const &		nr,
	Int_Rectangle const *		extent) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
	Display_Context const *		dc = nr->_hoops_SRA;
	Net_Rendition				_hoops_CRAI = nr;
	int							left = extent->left-1,
								right = extent->right+1,
								bottom = extent->bottom-1,
								top = extent->top+1;
	int							overflow;
	DC_Point					_hoops_RIRSH[4];
	RGBAS32						colors[4];
	RGBAS32						start, end;

	overflow = 3 * dc->_hoops_PGCC._hoops_IHHSR;

	if (left < _hoops_IHCR->_hoops_AGAA.left - overflow)
		left = _hoops_IHCR->_hoops_AGAA.left - overflow;
	if (right > _hoops_IHCR->_hoops_AGAA.right + overflow)
		right = _hoops_IHCR->_hoops_AGAA.right + overflow;
	if (bottom < _hoops_IHCR->_hoops_AGAA.bottom - overflow)
		bottom = _hoops_IHCR->_hoops_AGAA.bottom - overflow;
	if (top > _hoops_IHCR->_hoops_AGAA.top + overflow)
		top = _hoops_IHCR->_hoops_AGAA.top + overflow;

	/* _hoops_AHHCP _hoops_HSP _hoops_CCA _hoops_RSPH _hoops_SPR _hoops_IH _hoops_RPPS */
	_hoops_CIGA alter &			_hoops_CPIHP = _hoops_CRAI.Modify()->_hoops_IHA.Modify();
	_hoops_HHCR alter &		_hoops_GGCC = _hoops_CRAI->transform_rendition.Modify();

	_hoops_CPIHP->pattern = FP_SOLID;
	HD_Free_User_Face_Pattern (_hoops_CPIHP->_hoops_PGPH);
	_hoops_CPIHP->_hoops_PGPH = null;
	_hoops_CPIHP->color = _hoops_SGRA->_hoops_GPIR;
	_hoops_CPIHP->contrast_color = _hoops_SGRA->contrast_color;

	_hoops_GGCC->_hoops_CHIH = 0;
	_hoops_GGCC->_hoops_SHIH = 0;
	_hoops_GGCC->_hoops_RHPHP = _hoops_AHPHP;
	_hoops_GGCC->flags |= _hoops_ISH;

	/* _hoops_IAISS (_hoops_CAISS, _hoops_RAAP, _hoops_RPHR, _hoops_PRPC, _hoops_SCIA); */
	_hoops_RIRSH[0].x = (float)left;
	_hoops_RIRSH[0].y = (float)bottom;
	_hoops_RIRSH[0].z = _hoops_IHCR->_hoops_GSCH[1] * _hoops_IHCR->_hoops_PCHH - 1.0f;
	_hoops_RIRSH[1].x = (float)right;
	_hoops_RIRSH[1].y = (float)bottom;
	_hoops_RIRSH[1].z = _hoops_IHCR->_hoops_GSCH[1] * _hoops_IHCR->_hoops_PCHH - 1.0f;
	_hoops_RIRSH[2].x = (float)left;
	_hoops_RIRSH[2].y = (float)top;
	_hoops_RIRSH[2].z = _hoops_IHCR->_hoops_GSCH[1] * _hoops_IHCR->_hoops_PCHH - 1.0f;
	_hoops_RIRSH[3].x = (float)right;
	_hoops_RIRSH[3].y = (float)top;
	_hoops_RIRSH[3].z = _hoops_IHCR->_hoops_GSCH[1] * _hoops_IHCR->_hoops_PCHH - 1.0f;

	if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR) {
		start = _hoops_SGRA->_hoops_GPIR;
		end = _hoops_SGRA->contrast_color;
	}
	else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
		RGB const *		_hoops_SPRAR = nr->_hoops_SRA->_hoops_CHHIP;

		start = _hoops_SPRAR[_hoops_SGRA->_hoops_GPIR._hoops_PGGCR];
		end = _hoops_SPRAR[_hoops_SGRA->contrast_color._hoops_PGGCR];
	}
	else /* _hoops_AIHHP */ {
		start.r = 
		 start.g = 
		  start.b = (int)(255.99f *
						(_hoops_SGRA->_hoops_GPIR._hoops_PIHHP /
						 (float)(dc->_hoops_PGCC._hoops_PCHSR-1)));
		end.r = 
		 end.g = 
		  end.b = (int)(255.99f *
						(_hoops_SGRA->contrast_color._hoops_PIHHP /
						 (float)(dc->_hoops_PGCC._hoops_PCHSR-1)));

		start.a =
		 end.a = _hoops_GPGCR;
	}

	switch (_hoops_SGRA->_hoops_CGAIP) {
		case FP_WINDOW_GRADIENT_N: {
			colors[0] = start;
			colors[1] = start;
			colors[2] = end;
			colors[3] = end;
		}	break;
		case FP_WINDOW_GRADIENT_S: {
			colors[0] = end;
			colors[1] = end;
			colors[2] = start;
			colors[3] = start;
		}	break;
		case FP_WINDOW_GRADIENT_E: {
			colors[0] = start;
			colors[1] = end;
			colors[2] = start;
			colors[3] = end;
		}	break;
		case FP_WINDOW_GRADIENT_W: {
			colors[0] = end;
			colors[1] = start;
			colors[2] = end;
			colors[3] = start;
		}	break;

		case FP_WINDOW_GRADIENT_NE:
		case FP_WINDOW_GRADIENT_NW:
		case FP_WINDOW_GRADIENT_SE:
		case FP_WINDOW_GRADIENT_SW: {
			float			_hoops_PAHCR = (float)(extent->right - extent->left);
			float			_hoops_HAHCR  = (float)(extent->top - extent->bottom);
			float			total = _hoops_PAHCR + _hoops_HAHCR;
			RGBAS32		_hoops_RHGI[2];
			float			delta;
			
			delta = _hoops_PAHCR / total;
			_hoops_PCRGA (start, end, delta, _hoops_RHGI[0]);
			delta = _hoops_HAHCR / total;
			_hoops_PCRGA (start, end, delta, _hoops_RHGI[1]);

			switch (_hoops_SGRA->_hoops_CGAIP) {
				case FP_WINDOW_GRADIENT_NE: {
					colors[0] = start;
					colors[1] = _hoops_RHGI[0];
					colors[2] = _hoops_RHGI[1];
					colors[3] = end;
				}	break;

				case FP_WINDOW_GRADIENT_NW: {
					colors[0] = _hoops_RHGI[0];
					colors[1] = start;
					colors[2] = end;
					colors[3] = _hoops_RHGI[1];
				}	break;

				case FP_WINDOW_GRADIENT_SE: {
					colors[0] = _hoops_RHGI[1];
					colors[1] = end;
					colors[2] = start;
					colors[3] = _hoops_RHGI[0];
				}	break;

				case FP_WINDOW_GRADIENT_SW: {
					colors[0] = end;
					colors[1] = _hoops_RHGI[1];
					colors[2] = _hoops_RHGI[0];
					colors[3] = start;
				}	break;
			}
		}	break;
	}

	/* _hoops_CCPH _hoops_HAIR _hoops_ACPP _hoops_IS _hoops_HSPH _hoops_CCAC */
	if (left > extent->left && left < extent->right) {
		float			width = (float)(extent->right - extent->left);
		float			delta = (float)(left - extent->left) / width;

		if (right > extent->left && right < extent->right) {
			/* _hoops_CCPH _hoops_GIPR.  _hoops_RRP _hoops_IS _hoops_ASAC _hoops_GIGR _hoops_RAAP _hoops_PSHA _hoops_ARPP
			 * _hoops_GGAR _hoops_CR _hoops_HHACR _hoops_SCH _hoops_CHH _hoops_SAISS _hoops_GH _hoops_RH _hoops_SHRRR
			 * _hoops_IIGR _hoops_RH _hoops_RPHR _hoops_HAIR
			 */
			float		_hoops_GPISS = (float)(right - extent->left) / width;
			RGBAS32		_hoops_RPISS;

			_hoops_RPISS = colors[0];
			_hoops_PCRGA (_hoops_RPISS, colors[1], delta, colors[0]);
			_hoops_PCRGA (_hoops_RPISS, colors[1], _hoops_GPISS, colors[1]);
			_hoops_RPISS = colors[2];
			_hoops_PCRGA (_hoops_RPISS, colors[3], delta, colors[2]);
			_hoops_PCRGA (_hoops_RPISS, colors[3], _hoops_GPISS, colors[3]);
		}
		else {
			/* _hoops_RAAP _hoops_RGAR */
			_hoops_PCRGA (colors[0], colors[1], delta, colors[0]);
			_hoops_PCRGA (colors[2], colors[3], delta, colors[2]);
		}
	}
	else if (right > extent->left && right < extent->right) {
		float			width = (float)(extent->right - extent->left);
		float			delta = (float)(right - extent->left) / width;

		/* _hoops_RPHR _hoops_RGAR */
		_hoops_PCRGA (colors[0], colors[1], delta, colors[1]);
		_hoops_PCRGA (colors[2], colors[3], delta, colors[3]);
	}
	if (bottom > extent->bottom && bottom < extent->top) {
		float			height = (float)(extent->top - extent->bottom);
		float			delta = (float)(bottom - extent->bottom) / height;

		if (top > extent->bottom && top < extent->top) {
			/* _hoops_CCPH _hoops_GIPR.  _hoops_RRP _hoops_IS _hoops_ASAC _hoops_GIGR _hoops_PRPC _hoops_PSHA _hoops_ARPP
			 * _hoops_GGAR _hoops_CR _hoops_HHACR _hoops_SCH _hoops_CHH _hoops_SAISS _hoops_GH _hoops_RH _hoops_SHRRR
			 * _hoops_IIGR _hoops_RH _hoops_SCIA _hoops_HAIR
			 */
			float		_hoops_APISS = (float)(top - extent->bottom) / height;
			RGBAS32		_hoops_PPISS;

			_hoops_PPISS = colors[0];
			_hoops_PCRGA (_hoops_PPISS, colors[2], delta, colors[0]);
			_hoops_PCRGA (_hoops_PPISS, colors[2], _hoops_APISS, colors[2]);
			_hoops_PPISS = colors[1];
			_hoops_PCRGA (_hoops_PPISS, colors[3], delta, colors[1]);
			_hoops_PCRGA (_hoops_PPISS, colors[3], _hoops_APISS, colors[3]);
		}
		else {
			/* _hoops_PRPC _hoops_RGAR */
			_hoops_PCRGA (colors[0], colors[2], delta, colors[0]);
			_hoops_PCRGA (colors[1], colors[3], delta, colors[1]);
		}
	}
	else if (top > extent->bottom && top < extent->top) {
		float			height = (float)(extent->top - extent->bottom);
		float			delta = (float)(top - extent->bottom) / height;

		/* _hoops_SCIA _hoops_RGAR */
		_hoops_PCRGA (colors[0], colors[2], delta, colors[2]);
		_hoops_PCRGA (colors[1], colors[3], delta, colors[3]);
	}

	_hoops_CCRGA (_hoops_CRAI, 4, _hoops_RIRSH, colors);
}


local bool _hoops_CAHSI(_hoops_AIGH const * img, int width, int height, int _hoops_SAHSI, _hoops_AIGH const & _hoops_GPHSI)
{
	while(height--){
		if(
			img[ (width * height) + _hoops_SAHSI ].r != _hoops_GPHSI.r ||
			img[ (width * height) + _hoops_SAHSI ].g != _hoops_GPHSI.g ||
			img[ (width * height) + _hoops_SAHSI ].b != _hoops_GPHSI.b
		){
			return false;
		}
	}
	return true;
}

local void _hoops_RPHSI(
	Net_Rendition const & nr,
	Int_Rectangle const * _hoops_GAHIP,
	_hoops_RCR	const * _hoops_IICSR)
{
	_hoops_SAHAP _hoops_HGIIR = *((_hoops_SAHAP)_hoops_IICSR->_hoops_HGIIR->address);
	void * _hoops_HRARP = _hoops_IICSR->_hoops_HRARP;
	RGBAS32 * _hoops_APHSI = 0;
	_hoops_AIGH * rasters = 0;
	_hoops_AIGH * row = 0;
	int width = 0;
	int height = 0;
	int const _hoops_PPHSI = _hoops_GAHIP->left;
	int const _hoops_HPHSI = _hoops_GAHIP->right - _hoops_PPHSI +2;
	int const _hoops_HPISS = _hoops_GAHIP->top;
	int const _hoops_CPHSI = _hoops_GAHIP->top - _hoops_GAHIP->bottom +2;
	
	_hoops_HGIIR (
		_hoops_HPHSI, 
		_hoops_CPHSI,
		0, 
		&width, 
		&height,
		0,
		0,
		0,
		_hoops_HRARP);

	int const _hoops_SPHSI = 148;
	POOL_ALLOC_ARRAY_CACHED(_hoops_APHSI, _hoops_SPHSI * width, RGBAS32, nr->_hoops_SRA->memory_pool);
	POOL_ALLOC_ARRAY_CACHED(rasters, _hoops_SPHSI * width, _hoops_AIGH, nr->_hoops_SRA->memory_pool);

	int _hoops_RPHAP = 0;
	while (_hoops_RPHAP < height) {
		int _hoops_RHHSI = _hoops_SPHSI;
		if(_hoops_RHHSI > height - _hoops_RPHAP){
			_hoops_RHHSI = height - _hoops_RPHAP;
		}

		int _hoops_AHHSI = 0;
		int _hoops_PHHSI = width < _hoops_HPHSI ? width -1 : _hoops_HPHSI -1;
		for(int i = 0; i < _hoops_RHHSI; ++i){
			_hoops_HGIIR (
				_hoops_HPHSI,
				_hoops_CPHSI,
				_hoops_RPHAP +i,
				&width,
				&height,
				0,
				(char**)&row,
				0,
				_hoops_HRARP);

			if(row)
				COPY_MEMORY(row, (_hoops_PHHSI +1) * sizeof(_hoops_AIGH), rasters + i * width);
			else
				ZERO_ARRAY(rasters + i * width, _hoops_PHHSI+1, _hoops_AIGH);
		}

		/* _hoops_IHHSI _hoops_SGGR _hoops_RH _hoops_PGS _hoops_ASPA _hoops_HII _hoops_RH _hoops_RAAP... */
		while (_hoops_AHHSI < (_hoops_PHHSI+1) && _hoops_CAHSI(rasters, width, _hoops_RHHSI, _hoops_AHHSI, _hoops_AIGH(255, 255, 255))){
			++_hoops_AHHSI;
		}
		/* _hoops_CGP _hoops_IIH'_hoops_GRI _hoops_PA _hoops_RAAP _hoops_RAS _hoops_CHHSI _hoops_SGGR _hoops_RH _hoops_RAAP _hoops_ICRP _hoops_PGS _hoops_ASPA... */
		if (_hoops_AHHSI < (_hoops_PHHSI+1)) {

			/* _hoops_IHHSI _hoops_SGGR _hoops_RH _hoops_PGS _hoops_ASPA _hoops_HII _hoops_RH _hoops_RPHR... */
			while (_hoops_PHHSI >= _hoops_AHHSI && _hoops_CAHSI(rasters, width, _hoops_RHHSI, _hoops_PHHSI, _hoops_AIGH(255, 255, 255))){
				--_hoops_PHHSI;
			}
			int const _hoops_SHHSI = _hoops_PHHSI - _hoops_AHHSI +1;

			if(_hoops_SHHSI > 0){

				float _hoops_AGRSH = _hoops_PPHSI + _hoops_AHHSI;
				float x1 = _hoops_AGRSH + _hoops_SHHSI -1;
				float _hoops_PGRSH = _hoops_HPISS - _hoops_RPHAP - _hoops_RHHSI +1;
				float _hoops_AGSIR = _hoops_PGRSH + _hoops_RHHSI -1;

				DC_Point start(_hoops_AGRSH, _hoops_AGSIR, 0);
				DC_Point end(x1, _hoops_PGRSH, 0);
				
				for(int r = 0; r < _hoops_RHHSI; ++r){
					for(int c = 0; c < _hoops_SHHSI; ++c){
						int const _hoops_AHPCP = r * _hoops_SHHSI + c;
						int const _hoops_GIHSI = r * width + c;
						_hoops_APHSI[_hoops_AHPCP].r = rasters[_hoops_GIHSI + _hoops_AHHSI].r;
						_hoops_APHSI[_hoops_AHPCP].g = rasters[_hoops_GIHSI + _hoops_AHHSI].g;
						_hoops_APHSI[_hoops_AHPCP].b = rasters[_hoops_GIHSI + _hoops_AHHSI].b;
						_hoops_APHSI[_hoops_AHPCP].a = rasters[_hoops_GIHSI + _hoops_AHHSI].a;
					}
				}
				_hoops_ARCGH(nr, &start, &end, 0, _hoops_APHSI);
			}
		}
		_hoops_RPHAP += _hoops_RHHSI;
	}
	FREE_ARRAY(_hoops_APHSI, _hoops_SPHSI * width, RGBAS32);
	FREE_ARRAY(rasters, _hoops_SPHSI * width, _hoops_AIGH);
}

GLOBAL_FUNCTION void HD_Standard_Draw_Window (
	Net_Rendition const &		inr,
	Int_Rectangle const *		extent) 
{
	Net_Rendition				nr = inr;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	Image const *				image = null;
	_hoops_RCR *					_hoops_IICSR = null;
	int							pattern = _hoops_SGRA->_hoops_CGAIP;
	int							overflow;

	if (_hoops_GGPGR(nr))
		return; /* _hoops_HRGHP */

	overflow = 3 * dc->_hoops_PGCC._hoops_IHHSR;
	dc->_hoops_RAI = null;

#ifndef DISABLE_TEXTURING
	if (_hoops_SGRA->_hoops_SICSR != null) {
		_hoops_CPAIR		_hoops_CICSR;

		if (nr->_hoops_GCCSR->count > 0) {
			_hoops_CICSR.textures = nr->_hoops_GCCSR->textures;
			_hoops_CICSR.keys = nr->_hoops_GCCSR->keys;
			_hoops_CICSR.count = nr->_hoops_GCCSR->count;
		}
		else {
			_hoops_CICSR.textures = 0;
			_hoops_CICSR.keys = 0;
			_hoops_CICSR.count = 0;
		}

		if (BIT(_hoops_SGRA->_hoops_SICSR->flags, TF_UNEVALUATED)) {
			if ((_hoops_IICSR = HI_Activate_Texture((_hoops_RCR alter *)_hoops_SGRA->_hoops_SICSR, &_hoops_CICSR, false)) != null) {		
				_hoops_IICSR->_hoops_SCR |= _hoops_RCRH;
				image = _hoops_IICSR->image;
			}
			else
				image = null;
		}
		else
			image = _hoops_SGRA->_hoops_SICSR->image;
	}
#endif

	if (_hoops_IICSR == null ||
		image != null &&
		(image->format == Image_RGBA32 ||
		 image->format == _hoops_HRSRH)) {
		if (pattern >= FP_WINDOW_FIRST_GRADIENT &&
			pattern <= FP_WINDOW_LAST_GRADIENT &&
			_hoops_SGRA->_hoops_GPIR == _hoops_SGRA->contrast_color)
			pattern = FP_SOLID;

		if (pattern >= FP_WINDOW_FIRST_GRADIENT &&
			 pattern <= FP_WINDOW_LAST_GRADIENT)
			_hoops_HAISS (nr, &_hoops_SGRA->_hoops_GAHIP);
		else {
			Net_Rendition				_hoops_CRAI = nr.Copy();
			int							left = extent->left,
										right = extent->right,
										bottom = extent->bottom,
										top = extent->top;

			if (left < _hoops_IHCR->_hoops_AGAA.left - overflow)
				left = _hoops_IHCR->_hoops_AGAA.left - overflow;
			if (right > _hoops_IHCR->_hoops_AGAA.right + overflow)
				right = _hoops_IHCR->_hoops_AGAA.right + overflow;
			if (bottom < _hoops_IHCR->_hoops_AGAA.bottom - overflow)
				bottom = _hoops_IHCR->_hoops_AGAA.bottom - overflow;
			if (top > _hoops_IHCR->_hoops_AGAA.top + overflow)
				top = _hoops_IHCR->_hoops_AGAA.top + overflow;

			/* _hoops_AHHCP _hoops_HSP _hoops_CCA _hoops_RSPH _hoops_SPR _hoops_IH _hoops_RPPS */
			_hoops_HHCR alter &		_hoops_GGCC = _hoops_CRAI->transform_rendition.Modify();
			_hoops_GGCC->_hoops_CHIH = 0;
			_hoops_GGCC->_hoops_SHIH = 0;

			_hoops_CIGA alter &			_hoops_CPIHP = _hoops_CRAI->_hoops_IHA.Modify();
			_hoops_CPIHP->pattern = pattern;
			HD_Free_User_Face_Pattern (_hoops_CPIHP->_hoops_PGPH);
			if ((_hoops_CPIHP->_hoops_PGPH = _hoops_SGRA->_hoops_PGPH) != null)
				_hoops_CAHS (_hoops_CPIHP->_hoops_PGPH);
			_hoops_CPIHP->color = _hoops_SGRA->_hoops_GPIR;
			_hoops_CPIHP->contrast_color = _hoops_SGRA->contrast_color;

			_hoops_HHA alter &		_hoops_APIHP = _hoops_CPIHP->_hoops_CHA.Modify();
			_hoops_APIHP->_hoops_ARIR = false;

			if (pattern != FP_WINDOW_TRANSPARENT &&
				pattern != FP_WINDOW_TRANS_NO_ZCLEAR) {
				if (_hoops_SGRA->_hoops_PGPH != null)
					HD_Std_DC_Rectangle (_hoops_CRAI, left, right, bottom, top);
				else
					_hoops_HSIGH (_hoops_CRAI, left, right, bottom, top);
			}
		}
	}

#ifndef DISABLE_TEXTURING
	if (_hoops_SGRA->_hoops_SICSR && _hoops_IICSR && _hoops_IICSR->_hoops_HGIIR) {
		_hoops_RPHSI(nr, &_hoops_SGRA->_hoops_GAHIP, _hoops_IICSR);
	}
	else if (_hoops_SGRA->_hoops_SICSR && image) {
		Int_Rectangle const *		_hoops_GASP = &_hoops_SGRA->_hoops_GAHIP;
		DC_Point					box[4];
		_hoops_RSSH					params[8];
		_hoops_ARPA						planes[4];
		float						_hoops_IPISS = (float)(_hoops_GASP->right - _hoops_GASP->left);
		float						_hoops_CPISS = (float)(_hoops_GASP->top - _hoops_GASP->bottom);
		Net_Rendition				_hoops_CRAI = nr.Copy();
		_hoops_HHCR			_hoops_GGCC;
		int							i, j;

		/* _hoops_AHHCP _hoops_HSP _hoops_CCA _hoops_SPR _hoops_IIAAR _hoops_RPPS'_hoops_GRI _hoops_IPSP _hoops_HSGP */

		_hoops_GGCC = _hoops_CRAI->transform_rendition.Modify();
		_hoops_GGCC->_hoops_CHIH = 0;
		_hoops_GGCC->_hoops_SHIH = 0;
		HD_Set_Z_Buffering_Transform (_hoops_CRAI, true, false, 0.0f);

		if (!BIT(_hoops_IICSR->flags, _hoops_AIA) &&
			BIT(_hoops_CRAI->_hoops_IRR->_hoops_PPH, _hoops_CSGGA)) {
			_hoops_CRAI->_hoops_IRR.Modify()->_hoops_PPH &= ~_hoops_CSGGA;
		}
		else if (BIT(_hoops_IICSR->flags, _hoops_AIA) &&
			!BIT(_hoops_CRAI->_hoops_IRR->_hoops_PPH, _hoops_CSGGA)) {
			_hoops_CRAI->_hoops_IRR.Modify()->_hoops_PPH |= _hoops_CSGGA;
		}

		_hoops_CIGA alter &		_hoops_CPIHP = _hoops_CRAI->_hoops_IHA.Modify();
		_hoops_HHA alter &	_hoops_GGHHP = _hoops_CPIHP->_hoops_CHA.Modify();
		_hoops_CPIHP->_hoops_GIA = _hoops_GGHHP;

		_hoops_CPIHP->_hoops_AGP = null;

		if (_hoops_SGRA->_hoops_PGPH != null) {
			_hoops_CPIHP->pattern = pattern;
			HD_Free_User_Face_Pattern (_hoops_CPIHP->_hoops_PGPH);
			_hoops_CPIHP->_hoops_PGPH = _hoops_SGRA->_hoops_PGPH;
			_hoops_CAHS (_hoops_CPIHP->_hoops_PGPH);
		}


		for (i=0; i<_hoops_GAGRA; i++) {
			if (_hoops_GGHHP->texture[i] != null) {
				_hoops_HPRH(_hoops_GGHHP->texture[i]);
				_hoops_GGHHP->texture[i] = null;
			}
		}

		if (BIT(_hoops_IICSR->flags, _hoops_AIA)) {
			Point	_hoops_SPISS[6][4] = {
				{Point ( 1, -1, -1), Point ( 1,  1, -1), Point (-1, -1, -1), Point (-1,  1, -1)}, 
				{Point (-1, -1,  1), Point (-1,  1,  1), Point ( 1, -1,  1), Point ( 1,  1,  1)},
				{Point (-1, -1, -1), Point (-1,  1, -1), Point (-1, -1,  1), Point (-1,  1,  1)},
				{Point ( 1, -1,  1), Point ( 1,  1,  1), Point ( 1, -1, -1), Point ( 1,  1, -1)},
				{Point (-1, -1, -1), Point (-1, -1,  1), Point ( 1, -1, -1), Point ( 1, -1,  1)},
				{Point (-1,  1,  1), Point (-1,  1, -1), Point ( 1,  1,  1), Point ( 1,  1, -1)}
			};

			int const _hoops_GHISS[4] = {0,1,2,3};
#if 0
			int const _hoops_RHISS[4] = {0,0,0,0};
#endif
			_hoops_RSSH const		_hoops_AHISS[4*2] = {
									0.0f, 0.0f,  0.0f, 1.0f,  1.0f, 0.0f,  1.0f, 1.0f 
								};

			_hoops_HHRA *	_hoops_SPH;
			ZALLOC(_hoops_SPH, _hoops_HHRA);
			if (_hoops_IICSR->_hoops_RRIIR != null)
				HI_Default_Camera (_hoops_SPH, _hoops_IICSR->_hoops_RRIIR); 
			else
				HI_Default_Camera (_hoops_SPH, _hoops_GGCC->_hoops_SPH); 

			_hoops_SPH->projection = _hoops_GHH;
			_hoops_SPH->target.x -= _hoops_SPH->position.x;
			_hoops_SPH->target.y -= _hoops_SPH->position.y;
			_hoops_SPH->target.z -= _hoops_SPH->position.z;
			_hoops_SPH->position.x = 0.0f;
			_hoops_SPH->position.y = 0.0f;
			_hoops_SPH->position.z = 0.0f;

			// _hoops_CCA *_hoops_HACRH* _hoops_HICAA _hoops_HARH _hoops_IIGR _hoops_GRCPC, _hoops_RH _hoops_SARA _hoops_PAH _hoops_AHGS _hoops_IS _hoops_PGPCR _hoops_RH _hoops_IASC _hoops_IPIS
			// _hoops_CACH 11609_hoops_PHISS
#define _hoops_HHISS 1000.0f
			if (_hoops_SPH->_hoops_ISPA > _hoops_HHISS || _hoops_SPH->_hoops_SSPA > _hoops_HHISS) {
				float _hoops_RGRA;

				if (_hoops_SPH->_hoops_ISPA > _hoops_SPH->_hoops_SSPA)
					_hoops_RGRA = _hoops_SPH->_hoops_ISPA / _hoops_HHISS;
				else
					_hoops_RGRA = _hoops_SPH->_hoops_SSPA / _hoops_HHISS;
				for (i = 0 ; i < 6 ; i++) {
					for (j = 0 ; j < 4 ; j++) {
						_hoops_SPISS[i][j].x *= _hoops_RGRA;
						_hoops_SPISS[i][j].y *= _hoops_RGRA;
						_hoops_SPISS[i][j].z *= _hoops_RGRA;
					}
				}
			}

			HD_Downwind_Camera(_hoops_CRAI, _hoops_SPH);

			for (i=0; i<6; i++) {
				Tristrip *			tristrip;

				HI_Free_Diffuse_Channel_List (_hoops_GGHHP->_hoops_SCA);
				_hoops_GGHHP->_hoops_SCA = HI_New_Diffuse_Channel (_hoops_IICSR->_hoops_PRAH[i]);
				_hoops_GGHHP->_hoops_ARIR = true;

				ZALLOC (tristrip, Tristrip);
				_hoops_ICAI (tristrip);
				ZALLOC (tristrip->_hoops_GSSH, _hoops_RRCC);
				_hoops_ICAI (tristrip->_hoops_GSSH);
				tristrip->total = 4;
				tristrip->point_count = 4;
				tristrip->face_count = 1;
				tristrip->points = _hoops_SPISS[i];
		
				if (BIT (_hoops_IHCR->flags, _hoops_PGCH))
					tristrip->_hoops_GSSH->_hoops_CCHA = (_hoops_RSSH *)_hoops_AHISS;
				else
					tristrip->_hoops_GSSH->_hoops_CCHA = (_hoops_RSSH *)_hoops_AHISS;

				
				tristrip->_hoops_GSSH->_hoops_GSHA = 2;
				tristrip->_hoops_GSSH->_hoops_SCAI = _hoops_ASRSP|_hoops_RSRSP;

				tristrip->_hoops_PHHA = 1;
				tristrip->lengths_allocated = 1;
				ALLOC_ARRAY (tristrip->lengths, tristrip->lengths_allocated, int);
				tristrip->lengths[0] = 4;
				tristrip->_hoops_IPII = tristrip->_hoops_SGAHR = 4;
				ALLOC_ARRAY (tristrip->_hoops_AIHA, tristrip->_hoops_IPII, int);
				tristrip->_hoops_RAHH |= _hoops_AAHH;
				_hoops_AIGA (_hoops_GHISS, 4, int, tristrip->_hoops_AIHA);
#if 0
				ALLOC_ARRAY (tristrip->face_indices, tristrip->_hoops_SGAHR, int);				
				_hoops_AIGA (_hoops_RHISS, 4, int, tristrip->face_indices);
#endif
				tristrip->_hoops_SRHA |= DL_SHADOW_TRISTRIP | _hoops_GAHH | DL_TEMPORARY_DATA;
				tristrip->_hoops_SRHA |= _hoops_SRHH | DL_DO_NOT_DEFER | DL_3D_TRANSPARENCY;

				_hoops_RACIP (_hoops_CRAI, tristrip);

				if (_hoops_ISAI (tristrip) == 0)
					HI_Free_Tristrip (tristrip);
			}
		}
		else {
			_hoops_HPRH (_hoops_GGCC->_hoops_SPH);
			ZALLOC(_hoops_GGCC->_hoops_SPH, _hoops_HHRA);
			HI_Default_Camera(_hoops_PGRCA(_hoops_GGCC->_hoops_SPH));
			_hoops_PRRH (_hoops_GGCC->_hoops_SPH);
			_hoops_PGRCA(_hoops_GGCC->_hoops_SPH)->projection = _hoops_CPPCR;

			HI_Free_Diffuse_Channel_List (_hoops_GGHHP->_hoops_SCA);
			_hoops_GGHHP->_hoops_SCA = HI_New_Diffuse_Channel (_hoops_IICSR);
			_hoops_GGHHP->_hoops_ARIR = true;

			box[0].x = box[2].x = extent->left - 1;
			box[1].x = box[3].x = extent->right + 3;
			box[0].y = box[1].y = extent->bottom - 1;
			box[2].y = box[3].y = extent->top + 3;
			box[0].z = box[1].z = box[2].z = box[3].z = _hoops_IHCR->_hoops_GSCH[1] * _hoops_IHCR->_hoops_PCHH - 1.0f;

			params[0] = params[4] = (float)(extent->left  - 1 - _hoops_GASP->left) / _hoops_IPISS;
			params[2] = params[6] = (float)(extent->right + 1 - _hoops_GASP->left) / _hoops_IPISS;
			params[1] = params[3] = (float)(extent->bottom - 1 - _hoops_GASP->bottom) / _hoops_CPISS;
			params[5] = params[7] = (float)(extent->top	   + 1 - _hoops_GASP->bottom) / _hoops_CPISS;

			planes[0] = planes[1] = planes[2] = planes[3] = _hoops_ARPA (0.0f, 0.0f, 1.0f, 0.0f);

			_hoops_SSIC param_flags = _hoops_IGASP;
			_hoops_HCRGA (_hoops_CRAI, 4, box, null, planes, &params[0], 2, param_flags);
		}
	}

	if (_hoops_IICSR)
		_hoops_HPRH (_hoops_IICSR);
#endif
}

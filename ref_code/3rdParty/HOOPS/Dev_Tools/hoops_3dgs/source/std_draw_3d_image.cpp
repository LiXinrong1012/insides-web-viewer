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
 * $Id: obf_tmp.txt 1.121 2010-10-08 18:07:16 heppe Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "patterns.h"
#include "phedron.h"



GLOBAL_FUNCTION bool HD_Calc_Image_Position_And_Size (
	Net_Rendition const &		nr,
	Image const *				image,
	int *						width, 
	int *						height,
	float *						_hoops_SPHIH,
	float *						_hoops_GHHIH,
	float *						_hoops_RHHIH) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_RPRA const *			elements = _hoops_IHCR->matrix->data.elements;
	float						_hoops_IACC, _hoops_CACC, _hoops_SACC, _hoops_HGCPC;
	int							w, h;

	if (image->_hoops_PIRRP._hoops_HHP != _hoops_SHGRP || 
		image->_hoops_HIRRP._hoops_HHP != _hoops_SHGRP) {
		if (image->_hoops_PIRRP._hoops_HHP == image->_hoops_HIRRP._hoops_HHP) {
			/*_hoops_HRSPA _hoops_HSIH _hoops_AHHSR */
			w = (int)(HD_Compute_Generic_Size(nr, image->_hoops_PIRRP.value, image->_hoops_PIRRP._hoops_HHP, (float)image->width, false, 0, true)+0.5f);
			h = (int)((float)w*((float)image->height/(float)image->width));
		}
		else {
			if (image->_hoops_PIRRP._hoops_HHP != _hoops_SHGRP)
				w = (int)(HD_Compute_Generic_Size(nr, image->_hoops_PIRRP.value, image->_hoops_PIRRP._hoops_HHP, (float)image->width, false, 0, true)+0.5f);
			else
				w = image->width;
			
			if (image->_hoops_HIRRP._hoops_HHP != _hoops_SHGRP) 
				h = (int)(HD_Compute_Generic_Size(nr, image->_hoops_HIRRP.value, image->_hoops_HIRRP._hoops_HHP, (float)image->width, false, 0, true)+0.5f);
			else
				h = image->height;
		}
	}
	else {
		w = image->width;
		h = image->height;
	}
		

	if (BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_GARAP)) {
		w = (int)(w * nr->_hoops_ARA->image.width_scale);
		h = (int)(h * nr->_hoops_ARA->image._hoops_IISHP);
	}

	switch (_hoops_IHCR->_hoops_HGSC) {
		case _hoops_SIPHP: {
			_hoops_IACC = image->_hoops_CSAI.x;
			_hoops_CACC = image->_hoops_CSAI.y;
			_hoops_SACC = 0.0f;
		}	break;

		case _hoops_CIPHP: {
			_hoops_IACC = _hoops_PRPPI (elements, image->_hoops_CSAI);
			_hoops_CACC = _hoops_HRPPI (elements, image->_hoops_CSAI);
			_hoops_SACC = 0.0f;
		}	break;

		case _hoops_PCPHP: {
			_hoops_IACC = _hoops_HPRA (elements, image->_hoops_CSAI);
			_hoops_CACC = _hoops_IPRA (elements, image->_hoops_CSAI);
			_hoops_SACC = 0.0f;
		}	break;

		case _hoops_RCPHP: {
			_hoops_HGCPC = _hoops_PHCP (elements, image->_hoops_CSAI);
			if (_hoops_HGCPC <= _hoops_IHCR->_hoops_CHCR)
				return false;

			_hoops_IACC = _hoops_HPRA (elements, image->_hoops_CSAI) / _hoops_HGCPC;
			_hoops_CACC = _hoops_IPRA (elements, image->_hoops_CSAI) / _hoops_HGCPC;
			_hoops_SACC = 0.0f;
		}	break;

		case _hoops_ACPHP: {
			_hoops_IACC = _hoops_HPRA (elements, image->_hoops_CSAI);
			_hoops_CACC = _hoops_IPRA (elements, image->_hoops_CSAI);
			_hoops_SACC = _hoops_CPRA (elements, image->_hoops_CSAI);
		}	break;

		case _hoops_GCPHP: {
			_hoops_HGCPC = _hoops_PHCP (elements, image->_hoops_CSAI);
			if (_hoops_HGCPC <= _hoops_IHCR->_hoops_CHCR)
				return false;

			_hoops_IACC = _hoops_HPRA (elements, image->_hoops_CSAI) / _hoops_HGCPC;
			_hoops_CACC = _hoops_IPRA (elements, image->_hoops_CSAI) / _hoops_HGCPC;
			_hoops_SACC = _hoops_CPRA (elements, image->_hoops_CSAI) / _hoops_HGCPC;
		}	break;

		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "unexpected transform type");
			_hoops_IACC = _hoops_CACC = _hoops_SACC = 0.0f;
		}
	}


	*width = w;
	*height = h;
	*_hoops_SPHIH = _hoops_IACC;
	*_hoops_GHHIH = _hoops_CACC;
	*_hoops_RHHIH = _hoops_SACC;

	return true;
}


local void _hoops_RGIIS (
	Net_Rendition const &		in_nr,
	_hoops_RCR alter *				txr,
	bool						_hoops_GSCC,
	int							width, 
	int							height,
	float						_hoops_IACC,
	float						_hoops_CACC,
	float						_hoops_SACC) {
	Net_Rendition				nr = in_nr;
	DC_Point alter				points[4];			
	int							i;
	_hoops_RSSH params[] = { 
		0.0f, 0.0f,  
		0.0f, 1.0f,  
		1.0f, 0.0f, 
		1.0f, 1.0f, 
	};
	_hoops_ARPA planes[] = { 
		_hoops_ARPA (0.0f, 0.0f, -1.0f, 0.0f), 
		_hoops_ARPA (0.0f, 0.0f, -1.0f, 0.0f), 
		_hoops_ARPA (0.0f, 0.0f, -1.0f, 0.0f), 
		_hoops_ARPA (0.0f, 0.0f, -1.0f, 0.0f)
	};

	;
	_hoops_CIGA alter &		_hoops_SIGA = nr.Modify()->_hoops_IHA.Modify();
	_hoops_HHA alter &	mat = _hoops_SIGA->_hoops_CHA.Modify();

	_hoops_SIGA->_hoops_AGP = null;

	nr->_hoops_RGP &= ~T_LIGHTS_FOR_FACES;
	
	for (i=0;i<_hoops_GAGRA;i++) {
		if (mat->texture[i] != null) {
			_hoops_HPRH(mat->texture[i]);
			mat->texture[i] = null;
		}
	}
	HI_Free_Diffuse_Channel_List (mat->_hoops_SCA);
	mat->_hoops_SCA = HI_New_Diffuse_Channel (txr);
	mat->_hoops_ARIR = true;

	if (_hoops_GSCC) {
		mat->_hoops_SCA->flags |= _hoops_PRA|_hoops_PPIR;
		mat->_hoops_CSHR.red = in_nr->_hoops_ARA->image._hoops_RSCC.red;
		mat->_hoops_CSHR.green = in_nr->_hoops_ARA->image._hoops_RSCC.green;
		mat->_hoops_CSHR.blue = in_nr->_hoops_ARA->image._hoops_RSCC.blue;
	}

	_hoops_GRA const &	_hoops_RRA = nr->_hoops_ARA;
	if (_hoops_RRA->image._hoops_HRA.red != 1.0 ||
		_hoops_RRA->image._hoops_HRA.green != 1.0 ||
		_hoops_RRA->image._hoops_HRA.blue != 1.0) {

		_hoops_GRA alter &	_hoops_GCIHP = nr->_hoops_ARA.Modify();
		_hoops_GCIHP->image._hoops_HRA.red = 1.0; 
		_hoops_GCIHP->image._hoops_HRA.green = 1.0;
		_hoops_GCIHP->image._hoops_HRA.blue = 1.0;
	}

	if (_hoops_SACC == 0.0f && !BIT(nr->transform_rendition->flags, _hoops_PASP))
		_hoops_SACC = nr->transform_rendition->_hoops_PCHH*0.5f;

	points[0].x = ((int)(_hoops_IACC - width  * 0.5f))+ 0.5f;
	points[0].y = ((int)(_hoops_CACC - height * 0.5f))+ 0.5f;
	points[0].z = _hoops_SACC;

	points[1].x = points[0].x ;
	points[1].y = points[0].y + height;
	points[1].z = _hoops_SACC;

	points[2].x = points[0].x + width;
	points[2].y = points[0].y;
	points[2].z = _hoops_SACC;

	points[3].x = points[0].x + width;
	points[3].y = points[0].y + height;
	points[3].z = _hoops_SACC;

	_hoops_SSIC flags = _hoops_RSRSP|_hoops_ASRSP|_hoops_HSRSP|_hoops_IGASP;
	if (BIT(txr->image->flags, _hoops_SHCC)) {
		nr.Modify()->_hoops_CPP.Modify()->_hoops_PRH._hoops_HRH = true;

		if (BIT(nr->transform_rendition->flags, _hoops_PASP))
			HD_Hide_DC_Textured_Polytris(nr, 4, points, 0, planes, params, 2, flags);
		else
			_hoops_HCRGA(nr, 4, points, 0, planes, params, 2, flags);
	}
	else
		_hoops_HCRGA(nr, 4, points, 0, planes, params, 2, flags);
}


GLOBAL_FUNCTION void HD_Std_3D_Image (
	Net_Rendition const &		nr,
	Image const *				_hoops_AGIIS) {
	_hoops_ISHHP const &	_hoops_CSHHP = nr->_hoops_ASIR;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	int							hoffset, voffset,
								_hoops_PARSP, vcount;
	int							_hoops_CHCGR, _hoops_SHCGR;
	float						_hoops_IACC, _hoops_CACC, _hoops_SACC;
	int							width, height;
	DC_Point					start, end;
	Image alter *				image;
	bool						_hoops_GSCC = false;
	Image alter *				_hoops_HCSHS = null;

	if ((_hoops_AGIIS->format == Image_MAPPED_8 || _hoops_AGIIS->format == Image_MAPPED_16) &&
		_hoops_AGIIS->_hoops_RGARP >= _hoops_CSHHP->_hoops_PSIR->length) {
		HE_WARNING (HEC_IMAGE, HES_OUT_OF_RANGE_COLOR_MAP, Sprintf_DD (null,
			"Mapped image max of %d may exceed color map max of %d - not drawn",
			(int)_hoops_AGIIS->_hoops_RGARP, (int)_hoops_CSHHP->_hoops_PSIR->length - 1));
		return;
	}

	if (!HD_Calc_Image_Position_And_Size (nr, _hoops_AGIIS, &width, &height, &_hoops_IACC, &_hoops_CACC, &_hoops_SACC)) 
		return;

	/* _hoops_PGSA _hoops_RGR _hoops_GAR _hoops_IRS _hoops_HH? */	
	_hoops_GSCC = (nr->_hoops_ARA->image._hoops_RSCC.red != 1.0f ||
			  nr->_hoops_ARA->image._hoops_RSCC.green != 1.0f ||
			  nr->_hoops_ARA->image._hoops_RSCC.blue != 1.0f);

	if (BIT(_hoops_AGIIS->flags, _hoops_SHCC) || width != _hoops_AGIIS->width || height != _hoops_AGIIS->height || _hoops_GSCC || 
		ANYBIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HAI | _hoops_HPH) ||
		BIT(nr->_hoops_ARA->_hoops_IHRH.options, _hoops_CHRH) ||
		nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR != 1.0f ) {

		_hoops_RCR alter *		txr = HI_Clone_Texture(0);
	
		txr->image = (Image alter*)_hoops_AGIIS;
		txr->_hoops_SCR |= _hoops_RCRH;
		if (width < _hoops_AGIIS->width>>1 || height < _hoops_AGIIS->height>>1)
			txr->_hoops_RARH = _hoops_AARH;
		txr->_hoops_CGA = _hoops_ASCC;
		if (width == _hoops_AGIIS->width && height == _hoops_AGIIS->height)
			txr->_hoops_PSCC = _hoops_HSCC;
		_hoops_PRRH(txr->image);

		_hoops_RGIIS (nr, txr, _hoops_GSCC, width, height, _hoops_IACC, _hoops_CACC, _hoops_SACC);

		_hoops_HPRH(txr);
		return;
	}
	else {
		/* _hoops_SGH _hoops_GIGR _hoops_CSCR */
		image = (Image alter *)_hoops_AGIIS;
	}

	/*** _hoops_ICAH _hoops_IS _hoops_ACPA _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_PGIIS _hoops_IGSIP _hoops_HPGR _hoops_RGR _hoops_PPSR! ***/

	_hoops_CHCGR = (int)(_hoops_IACC + 0.5f - image->width  * 0.5f);
	_hoops_SHCGR = (int)(_hoops_CACC + 0.5f + image->height * 0.5f);

	start.x = (float)_hoops_CHCGR;
	start.y = (float)_hoops_SHCGR;

	if (_hoops_CHCGR <= _hoops_IHCR->_hoops_AGAA.right - image->width + 1) {
		_hoops_PARSP = image->width;
	}
	else {
		if (_hoops_CHCGR >= _hoops_IHCR->_hoops_AGAA.right + 1) return;
		_hoops_PARSP = (int)(_hoops_IHCR->_hoops_AGAA.right + 1 - start.x);
	}

	if (_hoops_CHCGR >= _hoops_IHCR->_hoops_AGAA.left) hoffset = 0;
	else {
		if (_hoops_PARSP <= _hoops_IHCR->_hoops_AGAA.left - _hoops_CHCGR) return;
		hoffset = (int)(_hoops_IHCR->_hoops_AGAA.left - start.x);
		_hoops_PARSP -= hoffset;
		start.x = (float)_hoops_IHCR->_hoops_AGAA.left;
	}

	if (_hoops_PARSP <= 0) return;	/* _hoops_ISAP _hoops_IS _hoops_PGSA! */


	if (_hoops_SHCGR >= _hoops_IHCR->_hoops_AGAA.bottom + image->height - 1) {
		vcount = image->height;
	}
	else {
		if (_hoops_SHCGR <= _hoops_IHCR->_hoops_AGAA.bottom + 1) return;
		if ((vcount = (int)(start.y - _hoops_IHCR->_hoops_AGAA.bottom + 1)) <= 0) return;
	}

	if (_hoops_SHCGR <= _hoops_IHCR->_hoops_AGAA.top) voffset = 0;
	else {
		if (vcount <= _hoops_SHCGR - _hoops_IHCR->_hoops_AGAA.top) return;
		voffset = (int)(start.y - _hoops_IHCR->_hoops_AGAA.top);
		if ((vcount -= voffset) <= 0) return;
		start.y = (float)_hoops_IHCR->_hoops_AGAA.top;
	}

	if (vcount <= 0) return;	/* _hoops_ISAP _hoops_IS _hoops_PGSA! */


	if (_hoops_PGSC (_hoops_IHCR->_hoops_HGSC))
		start.z = _hoops_IGSC (_hoops_SACC, _hoops_IHCR);
	else
		start.z = 0.0f;

	/* ("_hoops_AHRH" _hoops_HRGR _hoops_HII _hoops_RH _hoops_AAPA _hoops_RAAP) */

	end.x = start.x + (_hoops_PARSP - 1);
	end.y = start.y - (vcount - 1);
	end.z = start.z;

	if (image->format == _hoops_GGRH) {
		_hoops_HCSHS = HI_PNG_Decompress (image);
		image = _hoops_HCSHS;
		if (image == null)
			return;
	}
	else if (image->format == _hoops_RGRH) {
		_hoops_HCSHS = HI_JPEG_Decompress (image);
		image = _hoops_HCSHS;
		if (image == null)
			return;
	}
	else if (image->format == _hoops_AGRH) {
		_hoops_HCSHS = HI_TARGA_Decompress (image);
		image = _hoops_HCSHS;
		if (image == null)
			return;
	}
	else if (image->format == _hoops_IRRH ||
		image->format == _hoops_CRRH ||
		image->format == _hoops_SRRH) {
		HE_ERROR (HEC_SYSTEM, HES_INVALID_TYPE,
				"Software rendering of dxt images is not supported.");
		return;
	}

	if (_hoops_IHCR->_hoops_HCHH != null)
		HD_Draw_Clipped_DC_Image (nr, &start, &end,
								  hoffset, image->format, image->row_bytes,
								  image->rasters + voffset,
								  FP_SOLID, null, image);
	else if (BIT (_hoops_IHCR->flags, _hoops_CSP))
		HD_Draw_Trimmed_DC_Image (nr, &start, &end,
								  hoffset, image->format, image->row_bytes,
								  image->rasters + voffset,
								  FP_SOLID, null, image);
	else
		_hoops_SSGCP (nr, &start, &end,
						   hoffset, image->format, image->row_bytes,
						   image->rasters + voffset,
						   FP_SOLID, null, image);

	if (_hoops_HCSHS != null)
		HI_Au_Revoir ((_hoops_HPAH *)_hoops_HCSHS);

}




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
 * $Id: obf_tmp.txt 1.71 2010-10-06 19:16:21 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


local void _hoops_GAPCS(_hoops_RAARP alter *stencil, bool antialias)
{
	_hoops_RCR alter *	txr = HI_Clone_Texture(0);
	Image alter *	image;
	int nw, nh;
	int i, j, _hoops_CAAIP;

	txr->flags |= _hoops_IAPS;
	HOOPS_WORLD->_hoops_ACPIR++;

	if (!antialias) {
		txr->flags |= _hoops_RARRP|_hoops_AARRP;
		txr->_hoops_PSCC = _hoops_HSCC;
		txr->_hoops_RARH = _hoops_HSCC;
	}
	else{
		txr->flags |= _hoops_AARRP;
		/*_hoops_CAGRC->_hoops_RAPCS = _hoops_AAPCS;*/
		txr->_hoops_RARH = _hoops_PARH;
	}

	txr->_hoops_CGA = _hoops_ASCC;

	nw = _hoops_HSHGI(_hoops_IAAA(stencil->width+2, 4));
	nh = _hoops_HSHGI(_hoops_IAAA(stencil->height+2, 4));

	nw = nh = _hoops_IAAA(nw, nh);

	HI_Create_Image (&txr->image,
					 null,
					 nw, nh,
					 Image_RGBA32, 0,
					 _hoops_RRPGI, null);

	image=txr->image;
	
	image->flags |= _hoops_SHCC;

	for (i = 0; i < image->height; i++) {
		_hoops_AIGH alter *_hoops_GPRIS = (_hoops_AIGH alter *)image->rasters[i];
		for (j = 0; j < image->width; j++) {
			_hoops_GPRIS[j].a = 0;
			_hoops_GPRIS[j].r = 255;
			_hoops_GPRIS[j].g = 255;
			_hoops_GPRIS[j].b = 255;
		}
	}

	_hoops_CAAIP = image->height - stencil->height;

	if (stencil->_hoops_PPARP == 1) {
		for (i = 0; i < stencil->height; i++) {
			unsigned char const *row = stencil->bitmap + i * stencil->_hoops_APARP;
			for (j = 0; j < stencil->width; j++) {
				if ((row[j >> 3] & (0x0080 >> (j & 0x0007)))) {
					_hoops_AIGH alter *_hoops_GPRIS = (_hoops_AIGH *) image->rasters[i+_hoops_CAAIP-1];
					_hoops_GPRIS[j].a = 255;
				}
			}
		}
	}
	else {
		for (i = 0; i < stencil->height; i++) {
			unsigned char const *row = stencil->bitmap + i * stencil->_hoops_APARP;
			for (j = 0; j < stencil->width; j++) {
				if (row[j]) {
					_hoops_AIGH alter *_hoops_GPRIS = (_hoops_AIGH *) image->rasters[i+_hoops_CAAIP-1];
					_hoops_GPRIS[j].a = row[j];
				}
			}
		}
	}

#if 0
	/* _hoops_HISRA _hoops_AHCRR */
	for (j = 0; j < stencil->width; j++) {
		_hoops_AIGH alter *_hoops_GPRIS = (_hoops_AIGH *) image->rasters[0+_hoops_CAAIP-1];
		_hoops_GPRIS[j].a = 255;
	}
	for (j = 0; j < stencil->width; j++) {
		_hoops_AIGH alter *_hoops_GPRIS = (_hoops_AIGH *) image->rasters[stencil->height-1+_hoops_CAAIP-1];
		_hoops_GPRIS[j].a = 255;
	}
	for (i = 0; i < stencil->height; i++) {
		_hoops_AIGH alter *_hoops_GPRIS = (_hoops_AIGH *) image->rasters[i+_hoops_CAAIP-1];
		_hoops_GPRIS[0].a = 255;
	}
	for (i = 0; i < stencil->height; i++) {
		_hoops_AIGH alter *_hoops_GPRIS = (_hoops_AIGH *) image->rasters[i+_hoops_CAAIP-1];
		_hoops_GPRIS[stencil->width-1].a = 255;
	}
#endif
	
	stencil->txr = txr;
}

GLOBAL_FUNCTION void HD_Std_3D_Stenciled_Quad (
	Net_Rendition const &		in_nr,
	Point const *				in_points,
	_hoops_RAARP const *		stencil) {
	Net_Rendition				nr = in_nr.Copy();
	Display_Context const *		dc = nr->_hoops_SRA;
	DC_Point alter				points[4];		
	_hoops_RSSH					params[8];
	float						_hoops_ACCRR,_hoops_ISPI,_hoops_PCCRR,_hoops_CSPI,_hoops_PAPCS,_hoops_HAPCS;
	int							i;

	_hoops_HHCR alter &			_hoops_IHCR = nr->transform_rendition.Modify(1<<24);
	_hoops_GCIR alter &		_hoops_RCIR = nr->_hoops_CPP.Modify();
	_hoops_CIGA alter &				_hoops_SIGA = nr->_hoops_IHA.Modify();
	_hoops_HHA					mat = nr->_hoops_SISI->_hoops_CHA.Copy();

	_hoops_SIGA->color = nr->_hoops_SISI->color;
	_hoops_SIGA->_hoops_CHA = mat;

	_hoops_SIGA->_hoops_AGP = null;
	nr->_hoops_RGP &= ~T_LIGHTS_FOR_FACES;

	if (!ANYBIT(nr->current, _hoops_GSSHP|_hoops_RSSHP) &&
		BIT(dc->flags, _hoops_AASHP)) {
		_hoops_RCIR->_hoops_PRH._hoops_HRH = false;
		_hoops_RCIR->_hoops_PRH.style = Transparency_STYLE_BLENDING;
	}
	else {
		_hoops_RCIR->_hoops_PRH._hoops_HRH = true;
		_hoops_RCIR->_hoops_PRH.style = Transparency_STYLE_BLENDING;
	}

	nr->_hoops_PSGI |= T_FACES;

	HI_Free_Diffuse_Channel_List (mat->_hoops_SCA);
	mat->_hoops_SCA = null;
	for (i=0; i<_hoops_GAGRA; i++) {
		if (mat->texture[i] != null) {
			_hoops_HPRH(mat->texture[i]);
			mat->texture[i] = null;
		}
	}

	_hoops_IHCR->flags |= _hoops_ISH;
	_hoops_IHCR->_hoops_CHIH = 0.0f;

	if (!stencil->txr)
		_hoops_GAPCS((_hoops_RAARP alter *)stencil, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_CRAAP));

	mat->_hoops_SCA = HI_New_Diffuse_Channel (stencil->txr);
	mat->_hoops_ARIR = true;

	mat->_hoops_SCA->flags |= _hoops_PRA|_hoops_PPIR;

	/* _hoops_RHCHH _hoops_IH _hoops_CSCR _hoops_HCPC _hoops_APSP _hoops_IGIR _hoops_PPR _hoops_AHC */
	_hoops_PCCRR = (float)stencil->width/(float)stencil->txr->image->width;
	_hoops_CSPI = (float)stencil->height/(float)stencil->txr->image->height;

	_hoops_ACCRR = 1.0f/(float)stencil->txr->image->width;
	_hoops_ISPI = 1.0f/(float)stencil->txr->image->height;

	_hoops_PCCRR += _hoops_ACCRR;
	_hoops_CSPI += _hoops_ISPI;

	/* _hoops_CIAAI _hoops_IS _hoops_GGCR _hoops_IHH _hoops_HGPC _hoops_AIR _hoops_IH _hoops_GGAR _hoops_IAPCS */
	_hoops_PAPCS = (float)(stencil->width+2)/(float)stencil->width; 
	_hoops_HAPCS = (float)(stencil->height+2)/(float)stencil->height;

	_hoops_PAPCS *= _hoops_ACCRR;
	_hoops_HAPCS *= _hoops_ISPI;

	_hoops_ACCRR -= _hoops_PAPCS;
	_hoops_ISPI -= _hoops_HAPCS;
	_hoops_PCCRR += _hoops_PAPCS;
	_hoops_CSPI += _hoops_HAPCS;

	params[0] = _hoops_ACCRR;
	params[1] = _hoops_ISPI;

	params[2] = _hoops_ACCRR;
	params[3] = _hoops_CSPI;

	params[4] = _hoops_PCCRR;
	params[5] = _hoops_ISPI;

	params[6] = _hoops_PCCRR;
	params[7] = _hoops_CSPI;

	HI_Compute_Transformed_Points (4, in_points, &nr->transform_rendition->matrix->data.elements[0][0],
									(Point alter *)points);

	if (nr->_hoops_IRR->_hoops_SRI == _hoops_PRAAP){
		_hoops_APARR _hoops_RRCI;
		_hoops_RRCI = _hoops_HGCGA(dc, "hidden text", nr);
		_hoops_RRCI->_hoops_HPCGA = HD_Std_DC_Image;
		HD_Span_DC_Textured_Polytris(nr, 4, points, 0, 0, params, 2, _hoops_RSRSP|_hoops_ASRSP|_hoops_HSRSP);
		_hoops_HGSGA(dc, "hidden text");
	}
	else if (dc->_hoops_HCAGH || !BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_CRAAP)) {

		if (_hoops_RCIR->_hoops_PRH._hoops_HRH && BIT(nr->current, _hoops_RSSHP))
			_hoops_RCIR->_hoops_PRH._hoops_HRH = false;

		_hoops_IHCR->flags &= ~_hoops_ISH;
		_hoops_IHCR->flags |= _hoops_CASP;
		_hoops_HCRGA (nr, 4, points, 0, 0, params, 2, _hoops_RSRSP|_hoops_ASRSP|_hoops_HSRSP);
	}
	else
		HD_Hide_DC_Textured_Polytris (nr, 4, points, 0, 0, params, 2, _hoops_RSRSP|_hoops_ASRSP|_hoops_HSRSP);

#if 0
	_hoops_SCGGA(nr, 4, (DC_Point*)points);
#endif
}

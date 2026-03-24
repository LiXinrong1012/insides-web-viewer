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
 * $Id: obf_tmp.txt 1.154 2010-10-08 18:07:15 heppe Exp $
 */

#include "windows_wrapper.h"	// _hoops_CGRI <_hoops_SPHGR._hoops_GGHR>, _hoops_PIHA _hoops_RCPS _hoops_SRS :(


#include "hoops.h"
#include "hd_proto.h"

#ifndef IMAGE_DRIVER

/*
 * _hoops_GRRPI _hoops_PPICR
 */
extern "C"  bool HC_CDECL HD_Image_Driver (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED(request_info);
	return HD_No_Driver (_hoops_RIGC, _hoops_GHRI, request, "image");
}

#else

#include "database.h"
#include "driver.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "patterns.h"
#include "searchh.h"
#include "hversion.h"

#if defined( WINDOWS_SYSTEM ) && !defined( NUTCRACKER )
#	include "msw.h"
#endif

#undef CONST

struct _hoops_RRRPI {
	Image *		image;
	Image *		_hoops_ARRPI;
	Image *		_hoops_PRRPI; 
	bool		_hoops_RIPGR;
	
#if defined( WINDOWS_SYSTEM ) && !defined( NUTCRACKER )
    HDC				hDC;				/* _hoops_HRRPI _hoops_HRCSR _hoops_PRCA */
    _hoops_SGRRR *	_hoops_GRRRR;    /* _hoops_IRRPI _hoops_HRCSR _hoops_HIGR */
#endif
};


/***********************************************************************
 ***********************************************************************
					 _hoops_HRHI _hoops_CRRPI
 ***********************************************************************
 ***********************************************************************/

/*
 * _hoops_SRAC
 */
local void init_picture (
	Net_Rendition const &		nr) {
	UNREFERENCED (nr);
}


/*
 * _hoops_SRAC
 */
local void finish_picture (
	Net_Rendition const &		nr,
	bool						swap_buffers) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_RRRPI *				state = (_hoops_RRRPI alter *)dc->data;
	Image alter *				image = state->image;


	UNREFERENCED (swap_buffers);

	HI_Clear_Image_Cache(image);

	if (BIT(dc->flags, _hoops_SAISR))
		HI_Set_Delayed_Activity (image->owner, _hoops_IHSSR,
								 image, _hoops_HHSSR);
}


/***********************************************************************
 ***********************************************************************
					_hoops_IPSRH _hoops_SRRPI _hoops_CGHA
 ***********************************************************************
 ***********************************************************************/

/*
 * _hoops_SRAC
 */
local void _hoops_GARPI (
	Net_Rendition const	&		nr,
	DC_Point const		*start,
	DC_Point const		*end,
	int						row_bytes,
	RGBAS32 const		*_hoops_GAAC) {
	RGBAS32 const		*_hoops_SCGCR;
	_hoops_AIGH alter			*pp;
	_hoops_AIGH alter			*pe;
	Image alter			*image = ((_hoops_RRRPI alter *)nr->_hoops_SRA->data)->image;
	int						x, y;
	int						width = (int)end->x - (int)start->x + 1;
	Int_Rectangle const & _hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

	if (row_bytes == 0)
		row_bytes = width * sizeof (RGBAS32);

	y = (int)start->y;

	_hoops_RGGA (y < (int)end->y || y < _hoops_GPHH.bottom) {
		if (y <= _hoops_GPHH.top) {
			_hoops_SCGCR = _hoops_GAAC;
			pp = (_hoops_AIGH alter *)image->_hoops_RCPIR[y] + (int)start->x;
			pe = pp + width;
			x = (int)start->x;

			_hoops_RGGA (x >= _hoops_GPHH.left) {
				++pp;
				++_hoops_SCGCR;
				++x;
			}

			_hoops_RGGA (pp >= pe || x > _hoops_GPHH.right) {
				pp->r = _hoops_SCGCR->r;
				pp->g = _hoops_SCGCR->g;
				pp->b = _hoops_SCGCR->b;
				pp->a = _hoops_GPGCR;

				++pp;
				++_hoops_SCGCR;
				++x;
			}
		}
		_hoops_GAAC = (RGBAS32 const *)((unsigned char const *)_hoops_GAAC + row_bytes);
		--y;
	}
}




/*
 * _hoops_SRAC
 */
local void _hoops_RARPI (
	Net_Rendition const & nr,
	DC_Point const		*start,
	DC_Point const		*end,
	int						row_bytes,
	RGBAS32 const			*_hoops_GAAC) {
	RGBAS32 const			*_hoops_SCGCR;
	_hoops_SHGH alter		*pp;
	_hoops_SHGH alter		*pe;
	Image alter			*image =
		((_hoops_RRRPI alter *)nr->_hoops_SRA->data)->image;
	int						x, y;
	int						width =
		(int)end->x - (int)start->x + 1;
	Int_Rectangle const &	_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

	if (row_bytes == 0)
		row_bytes = width * sizeof (RGBAS32);

	y = (int)start->y;

	_hoops_RGGA (y < (int)end->y || y < _hoops_GPHH.bottom) {
		if (y <= _hoops_GPHH.top) {
			_hoops_SCGCR = _hoops_GAAC;
			pp = (_hoops_SHGH alter *)image->_hoops_RCPIR[y] +
					 (int)start->x;
			pe = pp + width;
			x = (int)start->x;

			_hoops_RGGA (x >= _hoops_GPHH.left) {
				++pp;
				++_hoops_SCGCR;
				++x;
			}

			_hoops_RGGA (pp >= pe || x > _hoops_GPHH.right) {
				pp->r = _hoops_SCGCR->r;
				pp->g = _hoops_SCGCR->g;
				pp->b = _hoops_SCGCR->b;

				++pp;
				++_hoops_SCGCR;
				++x;
			}
		}
		_hoops_GAAC = (RGBAS32 const *)((unsigned char const *)_hoops_GAAC + row_bytes);
		--y;
	}
}



/*
 * _hoops_SRAC
 */
local void _hoops_AARPI (
	Net_Rendition const & nr,
	DC_Point const		*start,
	DC_Point const		*end,
	int						row_bytes,
	RGBAS32 const			*_hoops_GAAC) {
	RGBAS32 const			*_hoops_SCGCR;
	RGBAS32 alter			*pp;
	RGBAS32 alter			*pe;
	Image alter			*image =
		((_hoops_RRRPI alter *)nr->_hoops_SRA->data)->image;
	int						x, y;
	int						width =
		(int)end->x - (int)start->x + 1;
	Int_Rectangle const & _hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

	if (row_bytes == 0)
		row_bytes = width * sizeof (RGBAS32);

	y = (int)start->y;

	_hoops_RGGA (y < (int)end->y || y < _hoops_GPHH.bottom) {
		if (y <= _hoops_GPHH.top) {
			_hoops_SCGCR = _hoops_GAAC;
			pp = (RGBAS32 alter *)image->_hoops_RCPIR[y] + (int)start->x;
			pe = pp + width;
			x = (int)start->x;

			_hoops_RGGA (x >= _hoops_GPHH.left) {
				++pp;
				++_hoops_SCGCR;
				++x;
			}

			_hoops_RGGA (pp >= pe || x > _hoops_GPHH.right) {
				*pp = *_hoops_SCGCR;

				++pp;
				++_hoops_SCGCR;
				++x;
			}
		}
		_hoops_GAAC = (RGBAS32 const *)((unsigned char const *)_hoops_GAAC + row_bytes);
		--y;
	}
}


/*
 * _hoops_SRAC
 */
local void _hoops_CCCSR (
	Net_Rendition const & nr,
	DC_Point const		*start,
	DC_Point const		*end,
	int						row_bytes,
	unsigned char const		*_hoops_GAAC) {
	unsigned char const		*_hoops_SCGCR;
	unsigned char alter		*pp;
	unsigned char alter		*pe;
	Image alter			*image =
		((_hoops_RRRPI alter *)nr->_hoops_SRA->data)->image;
	int						x, y;
	int						width =
		(int)end->x - (int)start->x + 1;
	Int_Rectangle const & _hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

	if (row_bytes == 0)
		row_bytes = width * sizeof (unsigned char);

	y = (int)start->y;

	_hoops_RGGA (y < (int)end->y || y < _hoops_GPHH.bottom) {
		if (y <= _hoops_GPHH.top) {
			_hoops_SCGCR = _hoops_GAAC;
			pp = (unsigned char alter *)image->_hoops_RCPIR[y] +
					 (int)start->x;
			pe = pp + width;
			x = (int)start->x;

			_hoops_RGGA (x >= _hoops_GPHH.left) {
				++pp;
				++_hoops_SCGCR;
				++x;
			}

			_hoops_RGGA (pp >= pe || x > _hoops_GPHH.right) {
				*pp = *_hoops_SCGCR;

				++pp;
				++_hoops_SCGCR;
				++x;
			}
		}
		_hoops_GAAC = (unsigned char const *)_hoops_GAAC + row_bytes;
		--y;
	}
}


/*****************************************************************************
 *****************************************************************************
							 _hoops_CSSGR _hoops_IPHH _hoops_PARPI
 *****************************************************************************
 *****************************************************************************/

/*
 * _hoops_SRAC
 */
local void _hoops_HARPI (
	Display_Context const	*dc,
	unsigned int				r,
	unsigned int				g,
	unsigned int				b,
	int							index) {
	Image alter				*_hoops_ARRPI =
		((_hoops_RRRPI alter *)dc->data)->_hoops_ARRPI;
	_hoops_SHGH alter			*entry;

	entry = (_hoops_SHGH alter *)_hoops_ARRPI->rasters[0] + index;

	entry->r = r;
	entry->g = g;
	entry->b = b;
}


/*
 * _hoops_SRAC
 */
local void _hoops_IARPI (
	Display_Context const	*dc,
	unsigned int				r,
	unsigned int				g,
	unsigned int				b,
	int							index) {
	Image alter				*_hoops_ARRPI =
		((_hoops_RRRPI alter *)dc->data)->_hoops_ARRPI;
	RGBAS32 alter				*entry;

	entry = (RGBAS32 alter *)_hoops_ARRPI->rasters[0] + index;

	entry->r = r;
	entry->g = g;
	entry->b = b;
	entry->a = 0;
}


/***********************************************************************
 ***********************************************************************
						_hoops_HGGSP _hoops_PARPI
 ***********************************************************************
 ***********************************************************************/

/*
 * _hoops_HGHGR
 */

local bool _hoops_CARPI (
	Display_Context alter	*dc,
	Image alter				**image,
	Image alter				**_hoops_ARRPI) {

	*image = (Image alter *)_hoops_RCSSR (dc->_hoops_RIGC, dc->options._hoops_GCHSR);
	if (*image == null) {
		HE_ERROR2 (HEC_IMAGE_DRIVER, HES_INVALID_KEY,
				   "An invalid key was passed to the image driver. You must pass",
				   "a non-null image key through the \"use window ID\" driver option.");
		return false;
	}

	if ((*image)->format == _hoops_HHGH) {
		dc->_hoops_ACPGR->draw_dc_rgb32_rasters = _hoops_RARPI;
	}
	else if ((*image)->format == Image_RGBA32) {
		dc->_hoops_ACPGR->draw_dc_rgb32_rasters = _hoops_GARPI;
	}
	else if ((*image)->format == _hoops_CSGSP) {
		dc->_hoops_ACPGR->draw_dc_rgb32_rasters = _hoops_AARPI;
	}
	else if ((*image)->format == Image_MAPPED_8) {
		*_hoops_ARRPI =
			(Image alter *)_hoops_RCSSR (dc->_hoops_RIGC, dc->options._hoops_ISPRP);
		if (*_hoops_ARRPI == null) {
			HE_ERROR3 (HEC_IMAGE_DRIVER, HES_INVALID_KEY,
					   "An invalid key was passed to the image driver. With a \"mapped8\"",
					   "primary image, you must also pass a non-null \"color map\" image",
					   "key through the \"use window ID2\" driver option.");
			return false;
		}
		if (((*_hoops_ARRPI)->format != _hoops_HHGH &&
			 (*_hoops_ARRPI)->format != _hoops_CSGSP) ||
			(*_hoops_ARRPI)->height != 1 ||
			(*_hoops_ARRPI)->width < 2 ||
			(*_hoops_ARRPI)->width >= 256) {
			HE_ERROR2 (HEC_IMAGE_DRIVER, HES_RGB_TYPE_IMAGE_REQUIRED,
					   "The image driver requires a 1 high by 2..255 wide \"rgb\"",
					   "image as the \"color map\" parameter.");
			return false;
		}

		dc->_hoops_ACPGR->_hoops_CCCSR = _hoops_CCCSR;

		if ((*_hoops_ARRPI)->format == _hoops_HHGH)
			dc->_hoops_ACPGR->_hoops_SCCSR = _hoops_HARPI;
		else
			dc->_hoops_ACPGR->_hoops_SCCSR = _hoops_IARPI;
	}
	else if ((*image)->format == _hoops_AHGH) {
		dc->_hoops_ACPGR->_hoops_CCCSR = _hoops_CCCSR;
	}
	else {
		/* _hoops_SARPI, _hoops_GPRPI, _hoops_RPRPI, _hoops_APRPI, _hoops_PPRPI _hoops_PAR _hoops_HPRPI _hoops_GACC _hoops_CCCHA _hoops_ARI -- _hoops_CSCR _hoops_RHPP _hoops_PAH'_hoops_RA _hoops_IIPR _hoops_IS _hoops_SGRH _hoops_AGHS */
		HE_ERROR (HEC_IMAGE_DRIVER, HES_RGB_TYPE_IMAGE_REQUIRED,
				  "The image driver requires an \"rgb\" or \"mapped8\" type image.");
		return false;
	}

	HI_Validate_Inverted_Rasters (*image);

	return true;
}

/*
 * _hoops_SRAC
 */
local POINTER_SIZED_INT get_outer_window (
	Display_Context const	*dc) {
	_hoops_RRRPI				*state = (_hoops_RRRPI alter *)dc->data;
	Image alter				*image = null;
	Image alter				*_hoops_ARRPI = null;

	if (!_hoops_CARPI ((Display_Context alter *)dc, &image, &_hoops_ARRPI))
		return false;

	if (image != state->image || _hoops_ARRPI != state->_hoops_ARRPI) {
		_hoops_HPRH (state->image);
		if (state->_hoops_ARRPI != null)
			_hoops_HPRH (state->_hoops_ARRPI);

		state->image = image;
		_hoops_PRRH (image);
		if ((state->_hoops_ARRPI) != null)
			_hoops_PRRH (_hoops_ARRPI);

		HD_Get_Physical_Info ((Display_Context alter *)dc);
	}

	return (POINTER_SIZED_INT)image->key;
}


/*
 * _hoops_SRAC
 */
local void free_outer_window (
	Display_Context const	  *dc) {

	UNREFERENCED (dc);
}

/***********************************************************************
 ***********************************************************************
						_hoops_HHCI _hoops_IHCI
 ***********************************************************************
 ***********************************************************************/

local void
draw_overlay_list (Net_Rendition const & nr) 
{
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_RRRPI *state = (_hoops_RRRPI alter *)dc->data;

	HD_Alternate_Hidden_Root (dc, _hoops_IHPGR);
	if (!dc->_hoops_CHPGR && 
		!dc->_hoops_HASS[dc->_hoops_IASS] &&
		!dc->_hoops_GPSS[dc->_hoops_IASS] &&
		!dc->_hoops_RPSS[dc->_hoops_IASS])
		goto _hoops_HPAGR;

	/* _hoops_GASA _hoops_IPRPI: _hoops_IAIR _hoops_RH _hoops_RCGRA _hoops_IIGR _hoops_CPRPI (_hoops_SPRPI, 1.0f);*/
	HD_Standard_Draw_Overlay_List (nr);
	dc->flags |= _hoops_ICPGR;
	state->_hoops_RIPGR = true;

  _hoops_HPAGR:
	HD_Alternate_Hidden_Root (dc, _hoops_IHPGR);
}

local void
_hoops_SCPGR (Net_Rendition const &  nr) 
{
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_RRRPI *state = (_hoops_RRRPI alter *)dc->data;

	if (!state->_hoops_RIPGR)
		return;
	/* _hoops_GASA _hoops_IPRPI: _hoops_IAIR _hoops_RH _hoops_RCGRA _hoops_IIGR _hoops_CPRPI(_hoops_GHRPI, 1.0);*/
	state->_hoops_RIPGR = false;
}


/***********************************************************************
 ***********************************************************************
						_hoops_IPSRH _hoops_RRSCP
 ***********************************************************************
 ***********************************************************************/

/*
 * _hoops_SRAC
 */
local bool start_device (
	Display_Context alter	*dc) {
	Image alter				*image;
	Image alter				*_hoops_ARRPI = null;
	_hoops_RRRPI				*state;

	if (!_hoops_CARPI (dc, &image, &_hoops_ARRPI))
		return false;

	ALLOC (state, _hoops_RRRPI);
	ZERO_STRUCT(state, _hoops_RRRPI);

	dc->data = (void alter *)state;
	state->image = image;
	_hoops_PRRH (image);
	state->_hoops_ARRPI = _hoops_ARRPI;
	if (_hoops_ARRPI)
		_hoops_PRRH (_hoops_ARRPI);

	HD_Get_Bit_Patterns_8 (dc, false);

	return true;
}


/*
 * _hoops_SRAC
 */
local void get_physical_info (
	Display_Context alter	*dc) {
	_hoops_RRRPI				*state = (_hoops_RRRPI alter *)dc->data;
	Image alter				*image = state->image;
	Image alter				*_hoops_ARRPI = state->_hoops_ARRPI;

	if (_hoops_ARRPI == null) {
		dc->_hoops_PGCC._hoops_PIHSR = _hoops_HIHSR;
		dc->_hoops_PGCC._hoops_PCHSR = 256;
		dc->_hoops_PGCC._hoops_AAPSR = 1L << 24;
	}
	else {
		dc->_hoops_PGCC._hoops_PIHSR = _hoops_SIHSR;
		dc->_hoops_PGCC._hoops_PCHSR = 256;
		dc->_hoops_PGCC._hoops_AAPSR = _hoops_ARRPI->width;
	}

	dc->_hoops_PGCC._hoops_ARISR.x = 0;
	dc->_hoops_PGCC._hoops_ARISR.y = 0;

	dc->_hoops_PGCC._hoops_PRPSR.x = image->width;
	dc->_hoops_PGCC._hoops_PRPSR.y = image->height;

	if (dc->options._hoops_SPHSR.x != -1) {	/* _hoops_IPSP _hoops_CARSR _hoops_IGIR */
		dc->_hoops_PGCC.size.x = dc->options._hoops_SPHSR.x;
		dc->_hoops_PGCC.size.y = dc->options._hoops_SPHSR.y;
	}
	else {
		/* _hoops_SHIR _hoops_RHRPI _hoops_IIGR 72 _hoops_CGSGI */
		dc->_hoops_PGCC.size.x = dc->_hoops_PGCC._hoops_PRPSR.x * (2.54f / 72.0f);
		dc->_hoops_PGCC.size.y = dc->_hoops_PGCC._hoops_PRPSR.y * (2.54f / 72.0f);
	}

	dc->_hoops_PGCC._hoops_CHHSR = _hoops_SHHSR;
	dc->_hoops_PGCC.flags |= _hoops_CAPGH;
	dc->_hoops_PGCC.flags &= ~_hoops_RSHSR;
	dc->_hoops_PGCC.flags &= ~_hoops_PSHSR;
	dc->_hoops_PGCC.flags &= ~_hoops_HSHSR;
	dc->_hoops_PGCC._hoops_PIPGH = true;

	dc->_hoops_PGCC._hoops_IIPGH[0] = QMoves_Accumulation;
	/* _hoops_GASA _hoops_IPRPI: _hoops_CSPH->_hoops_SGI |= _hoops_AHRPI; */

	dc->_hoops_PGCC.driver_type = "Image";
	dc->_hoops_PGCC._hoops_SCHSR = "$Revision: 1.154 $";
	dc->_hoops_PGCC._hoops_ICHSR = "HOOPS image";

}


/*
 * _hoops_SRAC
 */
local void stop_device (
	Display_Context alter	*dc) {
	_hoops_RRRPI				*state = (_hoops_RRRPI alter *)dc->data;
	Image alter				*image = state->image;
	Image alter				*_hoops_ARRPI = state->_hoops_ARRPI;

	_hoops_HPRH (image);

	if (_hoops_ARRPI != null)
		_hoops_HPRH (_hoops_ARRPI);

#if defined( WINDOWS_SYSTEM ) && !defined( NUTCRACKER )
	if (state->hDC)
		ReleaseDC (GetDesktopWindow (), state->hDC);


	/*_hoops_RGR _hoops_CRRHP _hoops_RH _hoops_IRGH _hoops_HRCSR _hoops_HIGR*/
	{
		_hoops_SGRRR * _hoops_HSSRH = state->_hoops_GRRRR;
		_hoops_SGRRR * _hoops_ISSRH;

		while (_hoops_HSSRH) {

			_hoops_ISSRH = _hoops_HSSRH->next;

			FREE_ARRAY (_hoops_HSSRH->name, _hoops_SSGR(_hoops_HSSRH->name) + 1, char);

			if (_hoops_HSSRH->specific)
				FREE_ARRAY (_hoops_HSSRH->specific, _hoops_SSGR(_hoops_HSSRH->specific) + 1, char);

			FREE (_hoops_HSSRH, _hoops_SGRRR);

			_hoops_HSSRH = _hoops_ISSRH;
		}

		state->_hoops_GRRRR = 0;
	}
#endif


	FREE (state, _hoops_RRRPI);
	dc->data = null;
}

/*
 * _hoops_SRAC
 * */
local bool
snapshot(
	Net_Rendition const &  nr,
	int width,
	int height,
	unsigned char * data) {

	_hoops_RRRPI	*state = (_hoops_RRRPI alter *)nr->_hoops_SRA->data;
	Image alter *image = state->image;
	Int_Rectangle const * area = &nr->_hoops_SAIR->_hoops_SCIH;
	int w,h;
	int x,y;


	w = area->right - area->left + 1;
	h = area->top - area->bottom + 1;

	if (w*h > width*height) return false;

	if (image->format == Image_RGBA32) {

		for (y=0; y<image->height; y++) {

			_hoops_AIGH * _hoops_GAAC = (_hoops_AIGH *) image->rasters[y];

			for (x=0; x<image->width; x++) {

				*data++ = _hoops_GAAC[x].r;
				*data++ = _hoops_GAAC[x].g;
				*data++ = _hoops_GAAC[x].b;
			}
		}
	}
	else
	if (image->format == _hoops_HRSRH) {

		for (y=0; y<image->height; y++) {

			_hoops_IRSRH * _hoops_GAAC = (_hoops_IRSRH *) image->rasters[y];

			for (x=0; x<image->width; x++) {

				*data++ = _hoops_GAAC[x].r;
				*data++ = _hoops_GAAC[x].g;
				*data++ = _hoops_GAAC[x].b;
			}
		}
	}
	else
	if (image->format == Image_RGBA32) {
	  
		for (y=0; y<image->height; y++) {

			RGBAS32 * _hoops_GAAC = (RGBAS32 *) image->rasters[y];

			for (x=0; x<image->width; x++) {

				*data++ = _hoops_GAAC[x].r;
				*data++ = _hoops_GAAC[x].g;
				*data++ = _hoops_GAAC[x].b;
			}
		}

	}
	else {
		/* _hoops_CSCR->_hoops_RPCC == _hoops_SGRPI */

		for (y=0; y<image->height; y++) {

			_hoops_SHGH * _hoops_GAAC = (_hoops_SHGH *) image->rasters[y];

			for (x=0; x<image->width; x++) {

				*data++ = _hoops_GAAC[x].r;
				*data++ = _hoops_GAAC[x].g;
				*data++ = _hoops_GAAC[x].b;
			}
		}

	}

	return true;
}


#if defined( WINDOWS_SYSTEM ) && !defined( NUTCRACKER )
/*****************************************************************************
 *****************************************************************************
								_hoops_PPSRH
 *****************************************************************************
 *****************************************************************************/

/*
 * _hoops_SRAC
 */
local bool measure_char(
	Net_Rendition const & nr,
	Font_Instance const *instance,
	Karacter _hoops_IPCSR,
	float alter *_hoops_GGGS,
	bool alter *_hoops_CPCSR,
	void ** _hoops_HPSRH) {

	return HI_W32_measure_char_stenciled(nr, instance, _hoops_IPCSR, _hoops_GGGS, _hoops_CPCSR, _hoops_HPSRH);
}

local _hoops_RAARP * _hoops_RGSSP (
	Net_Rendition const & nr,
	Font_Instance const	*instance,
	unsigned short			_hoops_IPCSR,
	int						bitmap_height,
	int						bolding_level,
	float					xrslant,
	float					xrrotation,
	float					xrwidth_scale,
	bool				antialias) {

	UNREFERENCED(nr);

	return HI_W32_make_font_stencil (instance, _hoops_IPCSR, 
									bitmap_height, bolding_level,
									xrslant,xrrotation,xrwidth_scale,
									antialias); 
}

/*
 * _hoops_SRAC
 */
local void
unload_font (
	Display_Context const * dc, 
	Font_Instance alter	*instance) {

	HI_W32_unload_font_stenciled(dc, instance);
}


/*
 * _hoops_SRAC
 */
local void * 
load_font(
	Display_Context const * dc,
	char const * name,
	Font_Instance alter * instance) {

	_hoops_RRRPI alter *data = (_hoops_RRRPI alter *)dc->data;
	_hoops_RRPRH alter *_hoops_IRSRA = _hoops_ARPRH ();

	if (!data->hDC)
		data->hDC = GetDC (GetDesktopWindow ());

	return HI_W32_load_font_stenciled(dc, name, instance, data->hDC, &data->_hoops_GRRRR, &_hoops_IRSRA->font_list);	 
}


/*
 * _hoops_SRAC
 */
local bool _hoops_CSCSP(
	Net_Rendition const &	nr,
	_hoops_IGPIR const			*_hoops_RRCSP,
	_hoops_IGPIR alter			*_hoops_ARCSP) {
	
	return HI_W32_name_font(nr, _hoops_RRCSP, _hoops_ARCSP);
}


/*
 * _hoops_SRAC
 */
local void find_all_fonts (
	Display_Context alter *dc) {

	_hoops_RRRPI alter *data = (_hoops_RRRPI alter *)dc->data;
	_hoops_RRPRH alter *_hoops_IRSRA = _hoops_ARPRH ();

	if (!data->hDC)
		data->hDC = GetDC (GetDesktopWindow ());

	HI_W32_find_all_fonts (dc, &data->_hoops_GRRRR, &_hoops_IRSRA->font_list);
}


/*
 *	** _hoops_SRAC **
 */
local bool _hoops_AACSR (
	Display_Context alter	*dc,
	char const					 *_hoops_PACSR) {

	_hoops_RRRPI alter *data = (_hoops_RRRPI alter *)dc->data;
	_hoops_RRPRH alter *_hoops_IRSRA = _hoops_ARPRH ();

	return HI_W32_find_one_font (dc, _hoops_PACSR, data->hDC, &data->_hoops_GRRRR, &_hoops_IRSRA->font_list);
}

/*
 * _hoops_SRAC
 */
local void _hoops_CACSR (
	Display_Context alter *dc) {

	_hoops_RRRPI alter *data = (_hoops_RRRPI alter *)dc->data;
	_hoops_RRPRH alter *_hoops_IRSRA = _hoops_ARPRH ();

	if (!data->hDC)
		data->hDC = GetDC (GetDesktopWindow ());

	HI_W32_find_basic_fonts (dc, data->hDC, &data->_hoops_GRRRR, &_hoops_IRSRA->font_list);
}

#endif

/***********************************************************************
 ***********************************************************************
							_hoops_PHRPI _hoops_HHRPI
 ***********************************************************************
 ***********************************************************************/

local void _hoops_RSCSR (
	_hoops_APARR alter &		_hoops_RRCI) {

	_hoops_RRCI->start_device			= start_device;
	_hoops_RRCI->stop_device				= stop_device;

	_hoops_RRCI->get_physical_info		= get_physical_info;

	_hoops_RRCI->get_outer_window		= get_outer_window;
	_hoops_RRCI->free_outer_window		= free_outer_window;

	_hoops_RRCI->init_picture			= init_picture;
	_hoops_RRCI->finish_picture			= finish_picture;

	_hoops_RRCI->draw_dc_rectangle		= HD_Span_DC_Rectangle;

	_hoops_RRCI->snapshot				= snapshot;
	_hoops_RRCI->draw_overlay_list		= draw_overlay_list;
	_hoops_RRCI->_hoops_SCPGR		= _hoops_SCPGR;

#if defined( WINDOWS_SYSTEM ) && !defined( NUTCRACKER )
	/*_hoops_HRRPI _hoops_HRCSR _hoops_PRCA */
	_hoops_RRCI->measure_char = measure_char;
	/*_hoops_HPGR->_hoops_IHRPI = _hoops_IHRPI;*/
	_hoops_RRCI->_hoops_AACSR = _hoops_AACSR;
	_hoops_RRCI->_hoops_CACSR = _hoops_CACSR;
	_hoops_RRCI->find_all_fonts = find_all_fonts;
	_hoops_RRCI->load_font = load_font;
	_hoops_RRCI->unload_font = unload_font;
	_hoops_RRCI->_hoops_CSCSP = _hoops_CSCSP;
	_hoops_RRCI->_hoops_RGSSP = _hoops_RGSSP;
#endif

}


/*
 * _hoops_IAAAH _hoops_PPICR
 */
extern "C" bool HC_CDECL HD_Image_Driver (
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED (request_info);
	return HD_Connect_Standard_Driver (_hoops_RIGC, _hoops_GHRI, request, _hoops_RSCSR);
}
#endif /* _hoops_CHRPI */

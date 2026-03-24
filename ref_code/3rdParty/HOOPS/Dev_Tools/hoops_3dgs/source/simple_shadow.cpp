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
 * $Id: obf_tmp.txt 1.257 2010-11-30 21:47:28 jason Exp $
 */


#include "hoops.h"

#ifndef DISABLE_SIMPLE_SHADOW

#include "database.h"
#include "driver.h"
#include "please.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "patterns.h"
#include "tandt.h"

#include <math.h>

#define _hoops_RARHS	1024
#define _hoops_AARHS		0	// _hoops_GRAA-_hoops_AHHR _hoops_IS _hoops_CACH _hoops_RH _hoops_RCAR _hoops_ISHA, 64 _hoops_IIAH _hoops_PRAR
#define _hoops_PARHS		0	// _hoops_GRAA-_hoops_AHHR _hoops_IS _hoops_CACH _hoops_SHSC _hoops_RCAR _hoops_CCAC, _hoops_GAAP 32
#define _hoops_HARHS	8

#define _hoops_RAAHR 1e-7



local bool _hoops_IARHS (
	Net_Rendition const & 		nr,
	Image *						image) {
	int		_hoops_CHRRC = nr->_hoops_CPP->_hoops_GHSS._hoops_IGGGR;
	int		_hoops_CARHS[_hoops_RARHS],_hoops_SARHS[_hoops_RARHS],
						_hoops_GPRHS[_hoops_RARHS],_hoops_RPRHS[_hoops_RARHS];
	int		_hoops_APRHS, _hoops_PPRHS, _hoops_HPRHS, _hoops_IPRHS;
	int		_hoops_RAISA, _hoops_RASSA;
	int		i,j;
	bool		_hoops_CPRHS = false;

	/* _hoops_HIHP _hoops_APRP & _hoops_PGS _hoops_CSCR _hoops_IS _hoops_PGS-_hoops_RRH _hoops_CSCR */
	for (i=0; i<image->height; ++i) {
		RGBAS32 alter			*_hoops_CSHPP;

		_hoops_CSHPP = (RGBAS32 alter *)image->rasters[i];

		for (j=0; j<image->width; ++j) {
			unsigned char			value;

			/* ._hoops_ISHI _hoops_HRGR _hoops_CGGHA _hoops_PIRA _hoops_HPIAA _hoops_HIAH.
			 * _hoops_CIIA _hoops_CGH _hoops_HCAGR _hoops_SHH _hoops_APRP _hoops_PAR _hoops_PGS
			 * _hoops_HIH _hoops_IH _hoops_HA _hoops_HAR _hoops_GHGC _hoops_SPRHS _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_CPHP _hoops_SHS
			 */
			value = _hoops_CSHPP->g;
			*_hoops_CSHPP = _hoops_CAHSR::_hoops_IAHHP;
			_hoops_CSHPP->a = value;
			if (value != 0)
				_hoops_CPRHS = true;
			++_hoops_CSHPP;
		}
	}

	if (!_hoops_CPRHS)
		return false;

	/* _hoops_HA _hoops_HAIP _hoops_AIIR _hoops_HSH _hoops_GAR _hoops_SIGR */
	while (_hoops_CHRRC-- > 0) {
		ZERO_ARRAY (_hoops_CARHS, image->width, int);
		ZERO_ARRAY (_hoops_SARHS, image->width, int);
		ZERO_ARRAY (_hoops_GPRHS, image->width, int);
		ZERO_ARRAY (_hoops_RPRHS, image->width, int);

		for (i=2; i<image->height; ++i) {
			RGBAS32 alter			*_hoops_CSHPP;
			RGBAS32 alter			*_hoops_AHSCA;

			_hoops_CSHPP = (RGBAS32 alter *)image->rasters[i];
			_hoops_APRHS = _hoops_PPRHS = _hoops_HPRHS = _hoops_IPRHS = 0;

			for (j=2; j<image->width; ++j) {
				_hoops_RAISA = _hoops_CSHPP[j].a;

				_hoops_RASSA = _hoops_APRHS + _hoops_RAISA;
				_hoops_APRHS = _hoops_RAISA;
				_hoops_RAISA = _hoops_PPRHS + _hoops_RASSA;
				_hoops_PPRHS = _hoops_RASSA;
				_hoops_RASSA = _hoops_HPRHS + _hoops_RAISA;
				_hoops_HPRHS = _hoops_RAISA;
				_hoops_RAISA = _hoops_IPRHS + _hoops_RASSA;
				_hoops_IPRHS = _hoops_RASSA;

				_hoops_RASSA = _hoops_CARHS[j] + _hoops_RAISA;
				_hoops_CARHS[j] = _hoops_RAISA;
				_hoops_RAISA = _hoops_SARHS[j] + _hoops_RASSA;
				_hoops_SARHS[j] = _hoops_RASSA;
				_hoops_RASSA = _hoops_GPRHS[j] + _hoops_RAISA;
				_hoops_GPRHS[j] = _hoops_RAISA;

				_hoops_AHSCA = (RGBAS32 alter *)image->rasters[i-2] + j-2;
				_hoops_AHSCA->a = (unsigned char)((128 + _hoops_RPRHS[j] + _hoops_RASSA) >> 8);

				_hoops_RPRHS[j] = _hoops_RASSA;
			}
		}
	}


	/* _hoops_ARP _hoops_RH _hoops_ASPA _hoops_PGAP _hoops_SPGA'_hoops_RA _hoops_RHIAA _hoops_HPP _hoops_RH _hoops_HAIP */
	for (i=0; i<2; ++i)
		SET_MEMORY ((void *)image->rasters[i], image->width * sizeof(RGBAS32), _hoops_AARHS);
	for (i=image->height-2; i<image->height; ++i)
		SET_MEMORY ((void *)image->rasters[i], image->width * sizeof(RGBAS32), _hoops_AARHS);
	for (i=0; i<image->height; ++i) {
		SET_MEMORY ((void *)image->rasters[i], 2 * sizeof(RGBAS32), _hoops_AARHS);
		SET_MEMORY ((void *)((RGBAS32 alter *)image->rasters[i] + image->width - 2),
					2 * sizeof(RGBAS32), _hoops_AARHS);
	}


#if _hoops_PARHS
	/* _hoops_RSAIP _hoops_IS _hoops_SHRPA _hoops_RCAR _hoops_CCAC */
	for (i=0; i<image->height; ++i) {
		RGBAS32 alter			*_hoops_CSHPP;

		_hoops_CSHPP = (RGBAS32 alter *)image->rasters[i];
		for (j=0; j<image->width; ++j) {
			if (_hoops_CSHPP[j].a < _hoops_PARHS)
				_hoops_CSHPP[j].a = _hoops_PARHS;
		}
	}
#endif

	return true;
}

/*****************************************************************************/
/* _hoops_IRGH _hoops_IPS _hoops_IIGR _hoops_GHRHS _hoops_CCA _hoops_GRH _hoops_PRCA */

#define _hoops_PCGCR(a) _hoops_IRGCR(a)

local void _hoops_RHRHS (
	Net_Rendition const & nr,
	DC_Point const		*start,
	DC_Point const		*end,
	int						row_bytes,
	RGBAS32 const		*_hoops_GAAC) {
	Display_Context const	*dc = nr->_hoops_SRA;
	RGBAS32 const			*_hoops_SCGCR;
	RGBAS32 alter			*pp;
	RGBAS32 alter			*pe;
	Image alter			*image = (Image alter *)dc->data;
	int						x, y;
	int						width = (int)end->x - (int)start->x + 1;
	Int_Rectangle const &	_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

	if (row_bytes == 0)
		row_bytes = width * sizeof (RGBAS32);

	y = (int)start->y;

	_hoops_RGGA (y < (int)end->y || y < _hoops_GPHH.bottom) {
		if (y <= _hoops_GPHH.top) {
			_hoops_SCGCR = _hoops_GAAC;
			pp = (RGBAS32 alter *)image->_hoops_RCPIR[y] + (int)start->x;
			pe = pp + width;
			x = (int)start->x;

			if (x < _hoops_GPHH.left) {
				int		delta = _hoops_GPHH.left - x;

				pp += delta;
				_hoops_SCGCR += delta;
				x += delta;
			}

			_hoops_RGGA (pp >= pe || x > _hoops_GPHH.right) {
				if (_hoops_SCGCR->a == _hoops_GPGCR)
					*pp = *_hoops_SCGCR;
				else if (_hoops_SCGCR->a != 0) {
					int		_hoops_IRIR, _hoops_PRH;

					_hoops_IRIR		 = _hoops_PCGCR (_hoops_SCGCR->a);
					_hoops_PRH = 255 - _hoops_IRIR;

					pp->r = (_hoops_PCGCR (_hoops_SCGCR->r) * _hoops_IRIR +
							 _hoops_PCGCR (pp->r) * _hoops_PRH) / 255;
					pp->g = (_hoops_PCGCR (_hoops_SCGCR->g) * _hoops_IRIR +
							 _hoops_PCGCR (pp->g) * _hoops_PRH) / 255;
					pp->b = (_hoops_PCGCR (_hoops_SCGCR->b) * _hoops_IRIR +
							 _hoops_PCGCR (pp->b) * _hoops_PRH) / 255;
					pp->a = _hoops_GPGCR;
				}

				++pp;
				++_hoops_SCGCR;
				++x;
			}
		}
		_hoops_GAAC = (RGBAS32 const *)((unsigned char const *)_hoops_GAAC + row_bytes);
		--y;
	}
}


local POINTER_SIZED_INT _hoops_AHRHS (
	Display_Context const	*dc) {
	Image alter				*image = (Image alter *)dc->data;

	return (POINTER_SIZED_INT)image->key;
}

local bool _hoops_PHRHS (
	Display_Context alter	*dc) {

	HD_Get_Bit_Patterns_8 (dc, false);

	return true;
}

local void _hoops_HHRHS (
	Display_Context alter	*dc) {

	dc->_hoops_PGCC._hoops_PIHSR = _hoops_HIHSR;
	dc->_hoops_PGCC._hoops_PCHSR = 256;
	dc->_hoops_PGCC._hoops_AAPSR = 1L << 24;

	dc->_hoops_PGCC._hoops_ARISR.x = 0;
	dc->_hoops_PGCC._hoops_ARISR.y = 0;

	/* _hoops_SPCS _hoops_HSH _hoops_AGHPA _hoops_SR _hoops_ACPA _hoops_GIH */
	dc->_hoops_PGCC._hoops_PRPSR.x = _hoops_RARHS;
	dc->_hoops_PGCC._hoops_PRPSR.y = _hoops_RARHS;
	dc->_hoops_PGCC.size.x = 10.0f * 2.54f;
	dc->_hoops_PGCC.size.y = 10.0f * 2.54f;

	dc->_hoops_PGCC._hoops_CHHSR = _hoops_SHHSR;
	dc->_hoops_PGCC.flags |= _hoops_CAPGH;
	dc->_hoops_PGCC.flags &= ~(_hoops_RSHSR | _hoops_PSHSR | _hoops_HSHSR);
	dc->_hoops_PGCC._hoops_PIPGH = true;

	dc->_hoops_PGCC.driver_type = "HOOPS Internal Shadow Image";
	dc->_hoops_PGCC._hoops_SCHSR = "$Revision: 1.257 $";
	dc->_hoops_PGCC._hoops_ICHSR = "HOOPS Internal shadow image";
}

local void _hoops_IHRHS (
	Display_Context alter	*dc) {
	Image alter				*image = (Image alter *)dc->data;

	dc->options._hoops_HPHRP = false;

	dc->options._hoops_CASSP = false;
	dc->options._hoops_SASSP = false;
	dc->options._hoops_GPSSP = false;

	dc->_hoops_PGCC._hoops_PRPSR.x = image->width;
	dc->_hoops_PGCC._hoops_PRPSR.y = image->height;

	dc->current.extent.left = 0.0f;
	dc->current.extent.right = (float)image->width - 0.01f;
	dc->current.extent.bottom = 0.0f;
	dc->current.extent.top = (float)image->height - 0.01f;
}

local void _hoops_CHRHS (
	Display_Context alter	*dc) {

	dc->options._hoops_IRARR = dc->_hoops_GHSS._hoops_PAHGH;

	dc->options._hoops_CASSP = false;
	dc->options._hoops_SASSP = false;
	dc->options._hoops_GPSSP = false;

	(*dc->_hoops_GHSS.get_current_info) (dc);
}

local void _hoops_SHRHS (
	Display_Context alter	*dc) {

	UNREFERENCED(dc);
}

local void _hoops_GIRHS (
	_hoops_APARR alter &		_hoops_RRCI) {

	_hoops_RRCI->id = "shadow renderer";

	_hoops_RRCI->start_device			= _hoops_PHRHS;
	_hoops_RRCI->get_physical_info		= _hoops_HHRHS;
	_hoops_RRCI->get_current_info		= _hoops_IHRHS;
	_hoops_RRCI->get_outer_window		= _hoops_AHRHS;
	_hoops_RRCI->stop_device				= _hoops_SHRHS;

	_hoops_RRCI->draw_dc_rectangle		= HD_Span_DC_Rectangle;

	_hoops_RRCI->draw_dc_rgb32_rasters	= _hoops_RHRHS;
}

local bool _hoops_RIRHS (
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED (request_info);
	return HD_Connect_Standard_Driver (_hoops_RIGC, _hoops_GHRI, request, _hoops_GIRHS);
}





#define _hoops_ARRAH			0x01000000


local bool _hoops_AIRHS (
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
#if defined(WINDOWS_SYSTEM) && !defined(EXCEED_BUILD)
	Driver_Action	action = HD_Win32_OpenGL_Driver;
#else
	Driver_Action	action = HD_OpenGL_Driver;
#endif

	if (HOOPS_WORLD->_hoops_IARPR != nullroutine) {
		Driver_Action	test = nullroutine;

		test = (*HOOPS_WORLD->_hoops_IARPR) ("opengl");
		if (test != nullroutine)
			action = test;
	}

	return (*action) (_hoops_RIGC, _hoops_GHRI, request, request_info);
}

local bool _hoops_PIRHS (
	Display_Context alter		*dc) {
	_hoops_CPSS				*_hoops_SPSS = dc->_hoops_GHSS.current;

	dc->options._hoops_GCHSR = _hoops_AIRIR (_hoops_SPSS->master_rendition->_hoops_SRA->_hoops_GHSS.image);

	dc->options._hoops_RGHRP = _hoops_GGHRP;

	if (dc->options._hoops_PPHRP == _hoops_APHRP ||
		dc->options._hoops_PPHRP == _hoops_CAHRP ||
		dc->options._hoops_PPHRP == _hoops_GPHRP) {
		dc->options._hoops_IRARR |= _hoops_ARRAH;
	}

	dc->options._hoops_HCPRP.left = -1.0f;
	dc->options._hoops_HCPRP.right = 1.0f;
	dc->options._hoops_HCPRP.bottom = -1.0f;
	dc->options._hoops_HCPRP.top = 1.0f;

	dc->_hoops_GHSS._hoops_PAHGH = dc->options._hoops_IRARR;

	return (*dc->_hoops_GHSS.start_device) (dc);
}


#define _hoops_HIRHS		(_hoops_CRSI)
#define _hoops_IIRHS		(_hoops_CSGGR | _hoops_GSSHP | \
								 _hoops_RSSHP | \
								 _hoops_SARIP | _hoops_AIPIP | \
								 _hoops_HSGGR | _hoops_ISGGR | _hoops_SRGIP)



local void _hoops_CIRHS (
	Net_Rendition alter &			nr) {
	_hoops_ISHHP alter &		_hoops_CSHHP = nr->_hoops_ASIR;
	_hoops_GCIR alter &	_hoops_RCIR = nr->_hoops_CPP;
	_hoops_GRGH alter &			_hoops_RRGH = nr->_hoops_IRR;
	_hoops_CGRA alter &		_hoops_SGRA = nr->_hoops_SAIR;
	_hoops_HHCR alter &		_hoops_IHCR = nr->transform_rendition;
	_hoops_PSIHP				_hoops_HSIHP = nr->_hoops_RSGC;
	float							_hoops_SIRHS = _hoops_SGRA->extent.left - _hoops_SGRA->_hoops_HHCAR.left;
	int								_hoops_HGII = _hoops_RCIR->_hoops_HRR._hoops_HAP;

	nr->_hoops_RCSHR &= ~(_hoops_IIRHS|_hoops_CRSI);
	nr->current &= ~(_hoops_IIRHS|_hoops_CRSI);

	_hoops_CSHHP->window._hoops_ASIHP = _hoops_GIARP;

	nr->flags &= ~_hoops_AHSHP;

	nr->_hoops_RGP &= (T_FACES|T_WINDOWS|T_CUTTING_PLANES|T_CUT_GEOMETRY);

	_hoops_RRGH->_hoops_AARIP &= (T_FACES|T_WINDOWS|T_CUTTING_PLANES|T_CUT_GEOMETRY);
	_hoops_RRGH->_hoops_GHIHP &= T_FACES;
	_hoops_RRGH->locks.color = Color_EVERYTHING | Color_CUT_FACE|Color_CUT_EDGE;
	_hoops_RRGH->locks._hoops_HAA[_hoops_IAA] = _hoops_RRGH->locks._hoops_HAA[_hoops_RSHHP] = ~M_TRANSMISSION;
	_hoops_RRGH->locks._hoops_RGP = T_ANY_DRAWABLE_GEOMETRY & ~T_FACES;

	/* _hoops_CHASA _hoops_GII _hoops_GAPGH & _hoops_RPPS _hoops_HRP _hoops_GH _hoops_IS _hoops_RGR _hoops_PPSR */
	_hoops_SGRA->_hoops_CIIH.left	= _hoops_SGRA->_hoops_PHRA.left	= _hoops_SGRA->_hoops_SCIH.left	= 0;
	_hoops_SGRA->_hoops_CIIH.bottom	= _hoops_SGRA->_hoops_PHRA.bottom = _hoops_SGRA->_hoops_SCIH.bottom = 0;
	_hoops_SGRA->_hoops_CIIH.right	= _hoops_SGRA->_hoops_PHRA.right  = _hoops_SGRA->_hoops_SCIH.right  = _hoops_HGII - 1;
	_hoops_SGRA->_hoops_CIIH.top	= _hoops_SGRA->_hoops_PHRA.top	= _hoops_SGRA->_hoops_SCIH.top	= _hoops_HGII - 1;
	_hoops_SGRA->extent.left	 = _hoops_SGRA->extent.bottom = 0.0f;
	_hoops_SGRA->extent.right = _hoops_SGRA->extent.top	 = (float)(_hoops_HGII-1) + 0.99f;
	_hoops_SGRA->_hoops_HHCAR.left	 = _hoops_SGRA->extent.left	 - _hoops_SIRHS;
	_hoops_SGRA->_hoops_HHCAR.right	 = _hoops_SGRA->extent.right	 + _hoops_SIRHS;
	_hoops_SGRA->_hoops_HHCAR.bottom = _hoops_SGRA->extent.bottom - _hoops_SIRHS;
	_hoops_SGRA->_hoops_HHCAR.top	 = _hoops_SGRA->extent.top	 + _hoops_SIRHS;
	_hoops_SGRA->_hoops_CSIH = 1.0f;
	_hoops_SGRA->_hoops_ASIHP = _hoops_GIARP;

	_hoops_IHCR->_hoops_AGAA.left = _hoops_SGRA->_hoops_PHRA.left;
	_hoops_IHCR->_hoops_AGAA.bottom = _hoops_SGRA->_hoops_PHRA.bottom;
	_hoops_IHCR->_hoops_AGAA.right = _hoops_SGRA->_hoops_PHRA.right;
	_hoops_IHCR->_hoops_AGAA.top = _hoops_SGRA->_hoops_PHRA.top;
	_hoops_IHCR->_hoops_APH &= ~(Heur_Culling_EXTENT|_hoops_RIHS);
	_hoops_IHCR->_hoops_CHIH = 0.0f;
	_hoops_IHCR->_hoops_IGAAP = 0.0f;
	_hoops_IHCR->_hoops_SHIH = 0.0f;
	if (!_hoops_RCIR->_hoops_HRR._hoops_SAR)
		_hoops_IHCR->flags |= _hoops_AIHS;

	_hoops_HSIHP->action.finish_picture = nullroutine;
	_hoops_HSIHP->action.draw_window = nullroutine;
}


/* _hoops_RRPGP _hoops_IASC _hoops_CHRA _hoops_IH _hoops_RH _hoops_SARA _hoops_GAR _hoops_ARPGP _hoops_RSSA */
local void _hoops_GCRHS(Net_Rendition const & nr, float const _hoops_RCRHS, float const far, Point *points) {
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	_hoops_CGRA const & _hoops_SGRA = nr->_hoops_SAIR;
	_hoops_HHRA const & _hoops_SPH = *_hoops_IHCR->_hoops_SPH;

	/* _hoops_PHAA _hoops_CGIC _hoops_RH _hoops_HSIH _hoops_AHHSR, _hoops_HIS _hoops_SR _hoops_CACH _hoops_RH _hoops_RSIR _hoops_CHRA _hoops_PGAP _hoops_GRS _hoops_SHH _hoops_CHCC, _hoops_HAR _hoops_SAHR _hoops_RH
	   _hoops_CHIA _hoops_ARIP. */
	float _hoops_ISIH = _hoops_SGRA->_hoops_CSIH * (_hoops_IHCR->_hoops_HCIH.top - _hoops_IHCR->_hoops_HCIH.bottom) /
									   (_hoops_IHCR->_hoops_HCIH.right - _hoops_IHCR->_hoops_HCIH.left);

	/* _hoops_SGAA _hoops_IS _hoops_PSP _hoops_SAAA */
	float _hoops_PIIH = BIT (_hoops_IHCR->flags, _hoops_PGCH) ? -1.0f : +1.0f;
	float _hoops_HIIH = 1;

	/* _hoops_ACRHS _hoops_IS _hoops_RPPS */
	if (_hoops_SPH.projection != _hoops_SSIH) {
		if (_hoops_ISIH <= _hoops_IHCR->_hoops_SPH->_hoops_CSIH)
			_hoops_PIIH *= _hoops_IHCR->_hoops_SPH->_hoops_CSIH / _hoops_ISIH;
		else
			_hoops_HIIH *= _hoops_ISIH / _hoops_IHCR->_hoops_SPH->_hoops_CSIH;
	}

	/* _hoops_AGGA _hoops_IIPR _hoops_CHRA _hoops_RSSA */
	if (_hoops_SPH.projection == _hoops_GHH) {
		/* _hoops_RGHA _hoops_AGIR */
		Vector const k = _hoops_SPH._hoops_IIPCR;
		Vector const i = _hoops_SPH._hoops_CRSS * 0.5f * _hoops_SPH._hoops_ARSS * _hoops_PIIH;
		Vector const j = _hoops_SPH.up_vector * 0.5f * _hoops_SPH._hoops_PRSS * _hoops_HIIH;
		Point const p = _hoops_SPH.position;

		/* _hoops_PCRHS _hoops_IPPA */
		points[0] = p + _hoops_RCRHS * (k - i - j);
		points[1] = p + _hoops_RCRHS * (k + i - j);
		points[2] = p + _hoops_RCRHS * (k - i + j);
		points[3] = p + _hoops_RCRHS * (k + i + j);

		/* _hoops_RSAP _hoops_IPPA */
		points[4] = p + far * (k - i - j);
		points[5] = p + far * (k + i - j);
		points[6] = p + far * (k - i + j);
		points[7] = p + far * (k + i + j);
	}
	else {
		/* _hoops_RSPA _hoops_AGIR */
		Vector const _hoops_HCRHS = _hoops_SPH._hoops_IIPCR * _hoops_RCRHS;
		Vector const _hoops_ICRHS = _hoops_SPH._hoops_IIPCR * far;
		Vector const i = _hoops_SPH._hoops_CRSS * (0.5f * _hoops_SPH._hoops_ISPA) * _hoops_PIIH;
		Vector const j = _hoops_SPH.up_vector * (0.5f * _hoops_SPH._hoops_SSPA) * _hoops_HIIH;
		Point const p = _hoops_SPH.position;

		/* _hoops_PCRHS _hoops_IPPA */
		points[0] = p + _hoops_HCRHS - i - j;
		points[1] = p + _hoops_HCRHS + i - j;
		points[2] = p + _hoops_HCRHS - i + j;
		points[3] = p + _hoops_HCRHS + i + j;

		/* _hoops_RSAP _hoops_IPPA */
		points[4] = p + _hoops_ICRHS - i - j;
		points[5] = p + _hoops_ICRHS + i - j;
		points[6] = p + _hoops_ICRHS - i + j;
		points[7] = p + _hoops_ICRHS + i + j;
	}
}

/* _hoops_CCRHS _hoops_PRCH _hoops_CIAA _hoops_PCCP _hoops_CSCR _hoops_IPPA */
local void _hoops_SCRHS(Point const & p, Vector const & i, Vector const& j, Vector const & k, Point const *points, size_t count, _hoops_SASC alter & cuboid)
{
	/* _hoops_GCIH _hoops_CCA _hoops_RHPA _hoops_ASCR */
	cuboid.min = Point(MAX_FLOAT, MAX_FLOAT, MAX_FLOAT);
	cuboid.max = Point(-MAX_FLOAT, -MAX_FLOAT, -MAX_FLOAT);

	/* _hoops_HSRR _hoops_GRR _hoops_PPSR */
	while (count--) {
		/* _hoops_CCRHS _hoops_GSRHS. */
		float _hoops_SSRP = i._hoops_SSRP(*points - p);
		cuboid.min.x = _hoops_AHIA(cuboid.min.x, _hoops_SSRP);
		cuboid.max.x = _hoops_IAAA(cuboid.max.x, _hoops_SSRP);

		_hoops_SSRP = j._hoops_SSRP(*points - p);
		cuboid.min.y = _hoops_AHIA(cuboid.min.y, _hoops_SSRP);
		cuboid.max.y = _hoops_IAAA(cuboid.max.y, _hoops_SSRP);

		_hoops_SSRP = k._hoops_SSRP(*points - p);
		cuboid.min.z = _hoops_AHIA(cuboid.min.z, _hoops_SSRP);
		cuboid.max.z = _hoops_IAAA(cuboid.max.z, _hoops_SSRP);

		/* _hoops_CPR _hoops_PPSR */
		++points;
	}
}


/* _hoops_IIHA _hoops_GASAS _hoops_GPP _hoops_IRS _hoops_PRGGR _hoops_IIGR _hoops_RSRHS */
local bool _hoops_ASRHS (
	Net_Rendition const &		_hoops_PSRHS,
	Net_Rendition &				_hoops_HSRHS,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_AS const *		light,
	bool						_hoops_SAR) {
	Display_Context const *		dc = _hoops_HSRHS->_hoops_SRA;
	_hoops_GSAR *				_hoops_SPSS = dc->_hoops_HRR.current;

	_hoops_SASC				cuboid;
	_hoops_HHRA const &				_hoops_ISRHS = *_hoops_PSRHS->transform_rendition->_hoops_SPH;

	if (!_hoops_PSRHS || !_hoops_HSRHS)
		return false;

	/* _hoops_HCR _hoops_HAHH _hoops_IGPC _hoops_IIGR _hoops_RH _hoops_SCII _hoops_CGH _hoops_HS _hoops_AIAH _hoops_RPII _hoops_SHIS,
	 * _hoops_HIH _hoops_SR _hoops_RRP _hoops_IS _hoops_IRHH _hoops_RCRR _hoops_RGR _hoops_API _hoops_GPGH'_hoops_RA _hoops_SGP _hoops_PA _hoops_CCAH */
	ASSERT (!_hoops_HSRHS->shared());

	/* _hoops_GISA _hoops_CCAH _hoops_SARA _hoops_IH _hoops_RH _hoops_RCAR _hoops_SCII */
	/* _hoops_SGSS 0 _hoops_GRS _hoops_SHH _hoops_GRSS _hoops_HPP _hoops_RRSS */
	_hoops_HHRA *	_hoops_SPH; 
	ZALLOC(_hoops_SPH, _hoops_HHRA);
	HI_Default_Camera(_hoops_SPH);

	/*
	 * _hoops_HGH _hoops_RRR _hoops_HARGR
	 */

#define _hoops_CSRHS
#ifdef _hoops_CSRHS
	/* _hoops_CGP _hoops_SR _hoops_PAH _hoops_RHSHP _hoops_ARAA _hoops_HRHAR _hoops_GHC _hoops_CCA _hoops_RH _hoops_HIRA'_hoops_GRI _hoops_SARA, _hoops_SR _hoops_HGCR _hoops_CRGP _hoops_IASC
	   _hoops_SSRHS _hoops_CGPR _hoops_GGAHS. */
	Vector const & _hoops_RGAHS = _hoops_ISRHS.up_vector;
	Vector const & _hoops_AGAHS = _hoops_ISRHS._hoops_CRSS;
#else
	/* _hoops_PGAHS-_hoops_CSCHR */
	Vector const & _hoops_RGAHS = _hoops_IRGA::_hoops_RCPCR;
	Vector const & _hoops_AGAHS = _hoops_IRGA::_hoops_IGHH;
#endif

	float const _hoops_HGAHS = 0.99f;

	if (Abs(light->direction._hoops_SSRP(_hoops_RGAHS)) < _hoops_HGAHS) {
		_hoops_SPH->up_vector = _hoops_RGAHS;
	}
	else {
		/* _hoops_RRR _hoops_HRGR _hoops_PHPC _hoops_RGCPR _hoops_GH _hoops_PAR _hoops_ISHP _hoops_CSCHR _hoops_IS _hoops_GSISC _hoops_HAGA */
		_hoops_SPH->up_vector = _hoops_AGAHS;
		ASSERT(Abs(light->direction._hoops_SSRP(_hoops_AGAHS)) < _hoops_HGAHS);
	}

	/* _hoops_ACGR _hoops_RRR'_hoops_GRI _hoops_HAGA. _hoops_HHHSI _hoops_RSSR _hoops_SS _hoops_CR _hoops_SSIA _hoops_AHGS _hoops_IS _hoops_SGH _hoops_RGR _hoops_GAR _hoops_RH _hoops_IGAHS _hoops_AAGA. */
	_hoops_SPH->_hoops_IIPCR = light->direction;
	if (light->_hoops_PRR == _hoops_H)
		_hoops_SPH->_hoops_IIPCR = -_hoops_SPH->_hoops_IIPCR;

	/* _hoops_PARGR _hoops_HARGR - _hoops_CGAHS _hoops_GH _hoops_AAGA _hoops_IPSH _hoops_RHC _hoops_AAGA _hoops_RCRP _hoops_RPHR _hoops_AAGA */
	_hoops_SPH->_hoops_CRSS = _hoops_SPH->up_vector._hoops_SAIAR(_hoops_SPH->_hoops_IIPCR);
	_hoops_SPH->_hoops_CRSS._hoops_AAIAR();

	/* _hoops_RCIAH _hoops_AAGA _hoops_PPR _hoops_RHC _hoops_AAGA _hoops_RCRP _hoops_GGSP _hoops_GH _hoops_AAGA */
	_hoops_SPH->up_vector = _hoops_SPH->_hoops_IIPCR._hoops_SAIAR(_hoops_SPH->_hoops_CRSS);
	_hoops_SPH->up_vector._hoops_AAIAR();

	/* _hoops_PHIR _hoops_GGR _hoops_RII _hoops_PPCAR _hoops_HRPRA */
	_hoops_SPH->_hoops_CIPCR = 0.0f;
	_hoops_SPH->_hoops_SIPCR = &_hoops_SPH->_hoops_CIPCR;
	_hoops_SPH->_hoops_RRHH = _hoops_RSPCR;
	_hoops_SPH->_hoops_IHCH = 0.0f;
	_hoops_SPH->_hoops_HHCH = 0.0f;

	/*
	 * _hoops_HGH _hoops_GSSP _hoops_PRCH _hoops_IH _hoops_HIRA.
	 */

	/* _hoops_ISGHR _hoops_GGR _hoops_RH _hoops_RSRHS _hoops_RRGR, _hoops_SR _hoops_GA'_hoops_RA _hoops_SHRGS _hoops_RCAR _hoops_RSSA */
	if (!_hoops_SRCP->bounding._hoops_HICAR()) {
		/* _hoops_CGP _hoops_SR _hoops_AIAH _hoops_HS _hoops_IRS _hoops_IPIS, _hoops_SGH _hoops_SGS _hoops_SSPP. */
		cuboid = _hoops_SRCP->bounding->cuboid;
	}
	else {
		Bounding	bounding;
		Bounding	_hoops_HSRIR;
		/* _hoops_HHPC _hoops_GRAS _hoops_IASC - _hoops_PGAIP _hoops_IS _hoops_SHH _hoops_GSGS _hoops_CRGP _hoops_RIRA */
		HI_Figure_Segment_Bounding(_hoops_SRCP, bounding, _hoops_HSRIR);
		if (bounding._hoops_HICAR())
			return false;		/*_hoops_PSP _hoops_PSIGA _hoops_CPAP*/
		cuboid = bounding->cuboid;
	}

	/* _hoops_RRPGP _hoops_CAGH _hoops_IASC _hoops_RSSA _hoops_PPR _hoops_HIHP _hoops_CRGR _hoops_GSSP _hoops_GC */
	Point points[8];
	cuboid._hoops_GPSC(&points[0]);

	_hoops_HHCR const &_hoops_IHCR = _hoops_HSRHS->transform_rendition;
	for (int i = 0; i != 8; ++i) {
		Point p = points[i];
		points[i].x = _hoops_HPRA (_hoops_IHCR->_hoops_IPH->data.elements, p);
 		points[i].y = _hoops_IPRA (_hoops_IHCR->_hoops_IPH->data.elements, p);
 		points[i].z = _hoops_CPRA (_hoops_IHCR->_hoops_IPH->data.elements, p);
	}

	/* _hoops_HSRR _hoops_RSSR _hoops_SS, _hoops_CGRS _hoops_GPGH'_hoops_RA _hoops_PRAR _hoops_PAPR, _hoops_SAHR _hoops_SGH _hoops_CGRS. */
	Point origin = _hoops_HPCH::_hoops_IPCH;
	if (light->_hoops_PRR != _hoops_H)
		/* _hoops_HSRR _hoops_GISR _hoops_SS, _hoops_PRRGR _hoops_CSCHR _hoops_IS _hoops_RRR. */
		origin = light->position;

	/* _hoops_CCRHS _hoops_GSSP _hoops_PRCH _hoops_CRGR _hoops_RRR _hoops_HARGR */
	_hoops_SASC	_hoops_SGAHS;

	_hoops_SCRHS(origin, _hoops_SPH->_hoops_CRSS, _hoops_SPH->up_vector, _hoops_SPH->_hoops_IIPCR, points, 8, _hoops_SGAHS);

	/* _hoops_SIIR _hoops_CSCS _hoops_SARA _hoops_CISAR _hoops_IASC _hoops_CPS. */
	Vector const _hoops_GRAHS = _hoops_SGAHS.max - _hoops_SGAHS.min;

	Point const _hoops_RRAHS = _hoops_AICIR(_hoops_SGAHS.max, _hoops_SGAHS.min);

	/* _hoops_RAP _hoops_RRR-_hoops_SASI _hoops_SARA _hoops_HRPRA */
	if (light->_hoops_PRR == _hoops_H) {
		/* _hoops_RSPA _hoops_SARA */
		_hoops_SPH->projection = _hoops_SSIH;

		/* _hoops_ARAHS _hoops_RH _hoops_SAAP _hoops_HPGR _hoops_RH _hoops_SPRSH _hoops_CGAA */
		_hoops_SPH->target = _hoops_HPCH::_hoops_IPCH + _hoops_RRAHS.x * _hoops_SPH->_hoops_CRSS +
											   _hoops_RRAHS.y * _hoops_SPH->up_vector +
											   _hoops_RRAHS.z * _hoops_SPH->_hoops_IIPCR;


		/* _hoops_HRSS _hoops_ISSC _hoops_RGR _hoops_SGIP _hoops_HII _hoops_APAP _hoops_PPAP _hoops_IIGR _hoops_SPRSH _hoops_CISAR */
		_hoops_SPH->_hoops_SRIR = 0.707f * _hoops_GRAHS.z;
		_hoops_SPH->_hoops_ISPA = _hoops_GRAHS.x;
		_hoops_SPH->_hoops_SSPA = _hoops_GRAHS.y;
	}
	else {
		/* _hoops_RGHA _hoops_SARA */
		ASSERT(light->_hoops_PRR == _hoops_I);
		_hoops_SPH->projection = _hoops_GHH;

		/* _hoops_SGCH _hoops_HPGR _hoops_RH _hoops_SGIP _hoops_PPAP _hoops_IIGR _hoops_RH _hoops_GSSP _hoops_IPSH _hoops_IRS _hoops_RSCA _hoops_IGRH. */
		float const _hoops_PRAHS = 1.1f;
		_hoops_SPH->_hoops_SRIR =_hoops_SGAHS.max.z * _hoops_PRAHS;
		_hoops_SPH->target = light->position + _hoops_SPH->_hoops_SRIR * _hoops_SPH->_hoops_IIPCR;

		/* _hoops_SSSA _hoops_RAR _hoops_IPPA _hoops_HAARR */
		float const _hoops_HRAHS = tan(_hoops_PCSR(light->_hoops_HCSR));
		_hoops_SPH->_hoops_ISPA = _hoops_SPH->_hoops_SSPA = 2.0f * _hoops_HRAHS * _hoops_SPH->_hoops_SRIR;

		/* _hoops_IRAHS _hoops_RRI _hoops_CCCI _hoops_ARSHA _hoops_RPP _hoops_SR _hoops_PAH */
		if (_hoops_SGAHS.min.z > 0)
			/* _hoops_CRAHS _hoops_CPAP _hoops_SRAHS */
			_hoops_SPH->_hoops_CIPCR = _hoops_SGAHS.min.z / (_hoops_PRAHS * _hoops_SPH->_hoops_SRIR);
		else
			/* _hoops_RAP _hoops_GHRP _hoops_SHIR */
			_hoops_SPH->_hoops_CIPCR = 0.05f;
	}

	/* _hoops_RAP _hoops_PPCAR _hoops_SARA _hoops_HRPRA */
	_hoops_SPH->position = _hoops_SPH->target - _hoops_SPH->_hoops_IIPCR * _hoops_SPH->_hoops_SRIR;
	_hoops_SPH->_hoops_CSIH = 1.0f;
	_hoops_SPH->_hoops_ARSS = _hoops_SPH->_hoops_ISPA / _hoops_SPH->_hoops_SRIR;
	_hoops_SPH->_hoops_PRSS = _hoops_SPH->_hoops_SSPA / _hoops_SPH->_hoops_SRIR;

	/* _hoops_RAGGR */
	HD_Downwind_Camera (_hoops_HSRHS, (Attribute *)_hoops_SPH);
	_hoops_HSRHS->transform_rendition.Renew();

	/* _hoops_CGP _hoops_RAR _hoops_PGSS _hoops_HRGR _hoops_GGR _hoops_SGH, _hoops_PPR _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_RSSR _hoops_RRR... */
	if (_hoops_SAR &&
		light->_hoops_PRR == _hoops_H) {

		/* _hoops_PARAR _hoops_GSSP _hoops_PRCH _hoops_CRGR _hoops_RH _hoops_AGPC-_hoops_PAPR _hoops_SARA _hoops_GC */
		Vector const c(_hoops_RRAHS.x, _hoops_RRAHS.y, 0);
		_hoops_SGAHS.min -= c;
		_hoops_SGAHS.max -= c;
		float const width_scale = 2.0f / _hoops_SPH->_hoops_ISPA;
		float const _hoops_IISHP = 2.0f / _hoops_SPH->_hoops_SSPA;
		float const _hoops_IIRA = 1.0f / (2.0f * _hoops_SPH->_hoops_SRIR);
		_hoops_SGAHS.min.x *= width_scale;
		_hoops_SGAHS.max.x *= width_scale;
		_hoops_SGAHS.min.y *= _hoops_IISHP;
		_hoops_SGAHS.max.y *= _hoops_IISHP;
		_hoops_SGAHS.min.z *= _hoops_IIRA;
		_hoops_SGAHS.max.z *= _hoops_IIRA;

		/* _hoops_HIPR _hoops_PRRGR _hoops_GSSP _hoops_PRCH _hoops_CRGR _hoops_SARA _hoops_HARGR _hoops_IS _hoops_HGCR _hoops_SSH-_hoops_PHGSP _hoops_IIGR _hoops_HIRA. */
		_hoops_SASC _hoops_GAAHS;
		_hoops_SCRHS(_hoops_ISRHS.position, _hoops_ISRHS._hoops_CRSS,
								 _hoops_ISRHS.up_vector, _hoops_ISRHS._hoops_IIPCR, points, 8, _hoops_GAAHS);

		/* _hoops_GPGP _hoops_AIHP _hoops_CCH, _hoops_HSPH _hoops_IS _hoops_CGSI _hoops_GGR _hoops_RIPS _hoops_IIGR _hoops_RH _hoops_RHC */
		float _hoops_RAAHS = _hoops_GAAHS.min.z;
		float _hoops_AAAHS = _hoops_GAAHS.max.z;
		if (_hoops_ISRHS.projection == _hoops_GHH)
			_hoops_RAAHS = _hoops_IAAA(_hoops_GAAHS.min.z, 0.0f);
		else {
			/* _hoops_AHH: _hoops_HCCS _hoops_RRGR - _hoops_SGH _hoops_RIHRR _hoops_HSCH _hoops_AHCR _hoops_HSH _hoops_HII _hoops_RHPP. */
			if (false && _hoops_SPSS->_hoops_SCCS < _hoops_SPSS->_hoops_GSCS) {
				float _hoops_CHCR = _hoops_IAAA(1.0e-3f, _hoops_PSRHS->transform_rendition->_hoops_CHCR);
				float f = _hoops_ISRHS._hoops_SRIR / _hoops_CHCR;
				float n = -_hoops_ISRHS._hoops_SRIR / _hoops_CHCR;
				float _hoops_RICR = n + _hoops_SPSS->_hoops_SCCS * (f - n) + _hoops_ISRHS._hoops_SRIR;
				float _hoops_AICR = n + _hoops_SPSS->_hoops_GSCS * (f - n) + _hoops_ISRHS._hoops_SRIR;
				_hoops_RAAHS = _hoops_IAAA(_hoops_RAAHS, _hoops_RICR);
				_hoops_AAAHS = _hoops_AHIA(_hoops_AAAHS, _hoops_AICR);
			}
		}

		/*
		 * _hoops_AGGA _hoops_IPHR _hoops_GGSR _hoops_RRI _hoops_IAAIC _hoops_IHAIA _hoops_PHGSP _hoops_IH _hoops_RCAR _hoops_PAAHS. _hoops_PS _hoops_IPHR _hoops_GGSR _hoops_HCR _hoops_RH
		 * _hoops_SSRR _hoops_GGGRR (_hoops_CR _hoops_SCH'_hoops_GRI _hoops_RGSRS _hoops_SPSIA _hoops_IS _hoops_GCAC _hoops_IRS _hoops_APR) _hoops_HIS _hoops_RH
		 * _hoops_RHPP _hoops_PAH _hoops_HAIHR _hoops_SPR _hoops_SIHH _hoops_PRHPA _hoops_PGCR-_hoops_PPRRR _hoops_RCHSP.
		 */

		/* _hoops_AGHP _hoops_SGGGH _hoops_PPAHP _hoops_IH _hoops_RH _hoops_PAAHS _hoops_IGIAR _hoops_RH _hoops_RAR _hoops_CHRA. _hoops_IPCP
		   _hoops_AIRP _hoops_CHR _hoops_HPGR _hoops_GRR _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_ARAA, _hoops_HIS _hoops_SR _hoops_HS (_hoops_SCAR+1) _hoops_IS _hoops_IPHR _hoops_GGSR.
		   _hoops_RCPA _hoops_SHAA _hoops_RH _hoops_RSIR _hoops_RAR, _hoops_RH _hoops_SRS _hoops_PPR _hoops_CGHI _hoops_CGH _hoops_SHR _hoops_SHH 0 _hoops_PPR 1. */
		int const count = _hoops_GSAR::_hoops_RSAR;
		float spacing[count+1];
		float const _hoops_HAAHS = 1.0f / count;
		if (_hoops_ISRHS.projection == _hoops_GHH) {
			/* _hoops_IAAHS _hoops_SGGGH */
			float const _hoops_CAAHS = 1.0f / (pow(2.0f, count) - 1.0f);
			float x = 0;
			for (int i = 0; i <= count; ++i) {
				spacing[i] = x;
				x += pow(2.0f, i) * _hoops_CAAHS;
			}
		}
		else {
			/* _hoops_SAAHS _hoops_SGGGH */
			for (int i = 0; i <= count; ++i)
				spacing[i] = i * _hoops_HAAHS;
		}

		/* _hoops_AGHP _hoops_SCAR _hoops_GAR _hoops_IASC _hoops_SRS, _hoops_PSCR _hoops_SICR _hoops_IS _hoops_GPAHS _hoops_AIRP _hoops_RAS _hoops_HPHRA */
		_hoops_SASC _hoops_RPAHS[count];
		for (int i = 0; i < count; ++i) {
			/* _hoops_HGH _hoops_RH _hoops_ARAA _hoops_IIGR _hoops_RH _hoops_CHRA _hoops_SR'_hoops_ASAR _hoops_GCAC */
			const float _hoops_AAAC = _hoops_AAAHS - _hoops_RAAHS;
			const float _hoops_HGRSH = _hoops_IAAA(_hoops_RAAHS, _hoops_RAAHS + spacing[i] * _hoops_AAAC - 0.01f * _hoops_AAAC);
			const float _hoops_HGSIR = _hoops_AHIA(_hoops_RAAHS + _hoops_AAAC, _hoops_RAAHS + spacing[i+1] * _hoops_AAAC + 0.01f * _hoops_AAAC);

			/* _hoops_CGIP _hoops_GGSR _hoops_CAS _hoops_SCH _hoops_SSPAA _hoops_GGR _hoops_RRR _hoops_GC */
			_hoops_GCRHS(_hoops_PSRHS, _hoops_HGRSH, _hoops_HGSIR, points);

			_hoops_SASC _hoops_APAHS;
			_hoops_SCRHS(_hoops_SPH->position, _hoops_SPH->_hoops_CRSS, _hoops_SPH->up_vector, _hoops_SPH->_hoops_IIPCR, points, 8, _hoops_APAHS);

			/* _hoops_AHGA */
			_hoops_APAHS.min.x *= width_scale;
			_hoops_APAHS.max.x *= width_scale;
			_hoops_APAHS.min.y *= _hoops_IISHP;
			_hoops_APAHS.max.y *= _hoops_IISHP;
			_hoops_APAHS.min.z *= _hoops_IIRA;
			_hoops_APAHS.max.z *= _hoops_IIRA;

			/* _hoops_PPAHS _hoops_RH _hoops_PGCR _hoops_PRCH _hoops_IS _hoops_HGCR _hoops_RH _hoops_ARAA _hoops_PRCH */
			_hoops_RPAHS[i] = _hoops_PGPGP(_hoops_APAHS, _hoops_SGAHS);

			/* _hoops_RSCS _hoops_AGSRH _hoops_AGAH _hoops_RHC-_hoops_GC _hoops_PHGSP _hoops_IH _hoops_RGR _hoops_ARAA */
			_hoops_RPAHS[i].min.z = _hoops_HGRSH - _hoops_ISRHS._hoops_SRIR;
			_hoops_RPAHS[i].max.z = _hoops_HGSIR - _hoops_ISRHS._hoops_SRIR;
		}

#define _hoops_HPAHS
#ifdef _hoops_HPAHS

		/**
		 * _hoops_IPAHS _hoops_HPHRA _hoops_SCAR _hoops_PGAP _hoops_RSSAI _hoops_PGARH, _hoops_IS _hoops_RASHR _hoops_HSRAP.
		 */

		/* _hoops_CPAHS _hoops_GAR _hoops_CCAC _hoops_SIPIR. _hoops_CGP _hoops_RH _hoops_SRS _hoops_ARAA _hoops_SPAHS _hoops_RRI _hoops_HSAR _hoops_AAHP * _hoops_CCAC
		   _hoops_IIGR _hoops_RH _hoops_GIAP, _hoops_HASC _hoops_CAPR _hoops_PPR _hoops_HHSP _hoops_RH _hoops_SRS _hoops_ARAA. */
		const float _hoops_GHAHS = 0.75f;

		/* _hoops_RHAHS _hoops_SCAR _hoops_CHR _hoops_HPGR _hoops_RH _hoops_RSGR, _hoops_HIS _hoops_IPHR _hoops_HPIPR _hoops_GGR _hoops_RRGP. */
		for (int i = _hoops_GSAR::_hoops_RSAR - 2; i >= 0; --i) {
			/* _hoops_ACGR _hoops_SCAR */
			_hoops_SASC& _hoops_SCAAR = _hoops_RPAHS[i+1];
			_hoops_SASC& _hoops_HCPIH = _hoops_RPAHS[i];

			/* _hoops_SSSA _hoops_CCAC _hoops_IIGR _hoops_PCIRA _hoops_ARAA. */
			Vector _hoops_AHAHS = _hoops_SCAAR.max - _hoops_SCAAR.min;
			float const _hoops_PHAHS = _hoops_AHAHS.x * _hoops_AHAHS.y;

			/* _hoops_PPAHS _hoops_GIPR _hoops_SCAR */
			_hoops_SASC _hoops_RSPSA = _hoops_PGPGP(_hoops_HCPIH, _hoops_SCAAR);

			/* _hoops_CGIP _hoops_GGSR _hoops_CCAC _hoops_IIGR _hoops_SGSSR */
			Vector _hoops_HHAHS = _hoops_RSPSA.max - _hoops_RSPSA.min;
			float const _hoops_IHAHS = _hoops_HHAHS.x * _hoops_HHAHS.y;

			if (_hoops_IHAHS > _hoops_PHAHS * _hoops_GHAHS) {
				/* _hoops_CHAHS _hoops_RHCHR _hoops_HIPRA _hoops_IIGR _hoops_PCIRA + _hoops_RPSI */
				_hoops_HCPIH._hoops_AACIR(_hoops_SCAAR);

				/* _hoops_SHAHS _hoops_SAGGR _hoops_GSRHA */
				_hoops_SCAAR.min = _hoops_HPCH::_hoops_IPCH;
				_hoops_SCAAR.max = _hoops_HPCH::_hoops_IPCH;
			}
		}

#endif // _hoops_GIAHS

		/* _hoops_CAAA _hoops_IASC _hoops_IS _hoops_SCAR */
		int _hoops_GGCHP = 0;
		for (int i = 0; i < _hoops_GSAR::_hoops_RSAR; ++i) {
			_hoops_SASC const &_hoops_RIAHS = _hoops_RPAHS[i];

			/* _hoops_PHIR _hoops_RGR _hoops_GGR */
			_hoops_GSAR::_hoops_APCR& _hoops_PPCR = _hoops_SPSS->_hoops_HPCR[i];

			/* _hoops_CGP _hoops_RH _hoops_IASC _hoops_SSCP _hoops_GSRHA, _hoops_RH _hoops_ARAA _hoops_HRGR _hoops_IPCR */
			if ((_hoops_RIAHS.min.x == _hoops_RIAHS.max.x) || (_hoops_RIAHS.min.y == _hoops_RIAHS.max.y)) {
				_hoops_PPCR._hoops_CPCR = false;

				_hoops_PPCR.size = _hoops_IRGA::_hoops_CRGA;
				_hoops_PPCR._hoops_CPAA = _hoops_HPCH::_hoops_IPCH;
				_hoops_PPCR._hoops_RICR = _hoops_PPCR._hoops_AICR = 0.0f;
			}
			else {
				_hoops_PPCR._hoops_CPCR = true;
				++_hoops_GGCHP;

				/* _hoops_GRSH _hoops_AHSC, _hoops_PPR _hoops_CAS, _hoops_HRGR _hoops_RH _hoops_SPRSH _hoops_IASC _hoops_CISAR _hoops_GGR _hoops_RHC _hoops_GC? */
				_hoops_PPCR.size = _hoops_RIAHS.max - _hoops_RIAHS.min;
				_hoops_PPCR._hoops_CPAA = _hoops_AICIR(_hoops_RIAHS.min, _hoops_RIAHS.max);

				/* _hoops_IGPP _hoops_SSH _hoops_PHGSP */
				_hoops_PPCR._hoops_RICR = _hoops_RIAHS.min.z;
				_hoops_PPCR._hoops_AICR = _hoops_RIAHS.max.z;
			}
		}

		/* _hoops_ACIGC, _hoops_RGR _hoops_CSAP _hoops_RAGPR _hoops_GPP (_hoops_AIAHS > 1) _hoops_HIH _hoops_SR _hoops_RRP
		 * _hoops_IS _hoops_IRHH _hoops_RCRR _hoops_SGS _hoops_SR _hoops_SCRHR _hoops_RH _hoops_RCAR _hoops_CGPR _hoops_RH _hoops_SARA _hoops_IHCI */
		_hoops_SPSS->_hoops_SAR = true;
	}
	else
		_hoops_SPSS->_hoops_SAR = false;


	return true;
}


enum _hoops_PIAHS {
	_hoops_HIAHS,
	_hoops_IIAHS,
	_hoops_CIAHS
};

struct _hoops_SIAHS : public _hoops_HIGGH {
	private:
		int		stage;

	public:
		_hoops_SIAHS (int s = _hoops_HIAHS) : stage (s) {}
		bool _hoops_PPCRR (Net_Rendition alter & nr, _hoops_CRCP const * _hoops_SRCP, _hoops_HICS const & path);
};

bool _hoops_SIAHS::_hoops_PPCRR (
	Net_Rendition alter &		nr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path) alter {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	UNREFERENCED (path);

	/* _hoops_GIGHR: _hoops_ARI _hoops_SR *_hoops_HHGC* _hoops_IS _hoops_GRPHA _hoops_SSPP _hoops_GPP _hoops_RH _hoops_PPHHH _hoops_IPP */
	switch (stage) {
		case _hoops_HIAHS: {
			_hoops_CPSS *				_hoops_SPSS = dc->_hoops_GHSS.current;
			Net_Rendition		 		_hoops_PGCPH = _hoops_SPSS->master_rendition;
			Vector const *				light = &_hoops_PGCPH->_hoops_CPP->_hoops_GHSS.light;
			_hoops_ARPA const *				plane = &_hoops_PGCPH->_hoops_CPP->_hoops_GHSS.plane;
			_hoops_HHRA *					_hoops_SPH;

			_hoops_HHCR alter &		_hoops_IHCR = nr->transform_rendition;
			_hoops_ISHHP alter &		_hoops_CSHHP = nr->_hoops_ASIR;
			_hoops_GRGH alter &			_hoops_RRGH = nr->_hoops_IRR;
			_hoops_GCIR alter &	_hoops_RCIR = nr->_hoops_CPP;
			_hoops_CGRA alter &		_hoops_SGRA = nr->_hoops_SAIR;
			_hoops_PSIHP				_hoops_HSIHP = nr->_hoops_RSGC;

			/* _hoops_RRP _hoops_RSSP _hoops_HRPP _hoops_ARPP _hoops_SARA, _hoops_SHS _hoops_SR'_hoops_GHGP _hoops_RRP _hoops_IHH _hoops_GGCH _hoops_RAS */
			/* _hoops_SHH _hoops_RHRIR, _hoops_SCII & _hoops_IAAI _hoops_GHCA _hoops_PPSR _hoops_IS _hoops_RH _hoops_PSHR _hoops_CPSP */
			_hoops_IHCR->flags = (_hoops_IHCR->flags & ~_hoops_PGCH) | (_hoops_PGCPH->transform_rendition->flags & _hoops_PGCH);

			// _hoops_CHASA _hoops_HSGC _hoops_RSIH _hoops_GGR _hoops_AGIR _hoops_SR _hoops_IS _hoops_IRS _hoops_HHCI _hoops_ASRC
			_hoops_HSIHP->action.finish_picture = nullroutine;
			_hoops_HSIHP->action.draw_window = nullroutine;

			_hoops_SPSS->_hoops_CHRP = _hoops_SPSS->_hoops_SHRP = 1.0f;

			int pixels = _hoops_RARHS;
			int border = 2 * _hoops_PGCPH->_hoops_CPP->_hoops_GHSS._hoops_IGGGR;
			int _hoops_GCAHS = pixels - 2 * border;

			if (_hoops_GCAHS < _hoops_HARHS)
				_hoops_GCAHS = _hoops_HARHS;

			float scale = (float)_hoops_RARHS / (float)_hoops_GCAHS;
			float _hoops_HAP = _hoops_PGCPH->_hoops_SAIR->shadow_resolution;
			float _hoops_RCAHS = _hoops_GCAHS/2 * _hoops_HAP;

			float	size, _hoops_ACAHS, _hoops_PCAHS;
			int		_hoops_HCAHS, _hoops_ICAHS;

			Point	center;
			Vector	_hoops_HAHCR;

			float _hoops_SSRP = plane->a * light->x + plane->b * light->y + plane->c * light->z;

			if (_hoops_SSRP > 0.99f &&
				(light->x > 0.99f || light->y > 0.99f || light->z > 0.99f ||
				 light->x < -0.99f || light->y < -0.99f || light->z < -0.99f)) {

				Bounding		bounding = Bounding::Create();

				HI_Accumulate_Segment_Bounding (dc->_hoops_RIGC, _hoops_SRCP, bounding,
												&nr->transform_rendition->_hoops_IPH->data,
												T_FACES, _hoops_AACAA|_hoops_CRIAA|_hoops_RACAA);

				if (bounding._hoops_HICAR()) {
					_hoops_SPSS->valid = true;
					_hoops_SPSS->_hoops_APGGR = false;
					return false;
				}

				ZALLOC(_hoops_SPH, _hoops_HHRA);
				HI_Default_Camera(_hoops_SPH);
				/* _hoops_SGSS 0 _hoops_GRS _hoops_SHH _hoops_GRSS _hoops_HPP _hoops_RRSS */

				_hoops_SPH->target = _hoops_AICIR(bounding->cuboid.min, bounding->cuboid.max);

				float _hoops_RGRS = 0.5f * (bounding->cuboid.max.x - bounding->cuboid.min.x);
				float ysize = 0.5f * (bounding->cuboid.max.y - bounding->cuboid.min.y);
				float _hoops_CCAHS = 0.5f * (bounding->cuboid.max.z - bounding->cuboid.min.z);

				if (light->x > 0.99f || light->x < -0.99f) {
					_hoops_SPH->up_vector.x = 0.0f;
					_hoops_SPH->up_vector.y = 1.0f;
					_hoops_SPH->up_vector.z = 0.0f;

					_hoops_ACAHS = _hoops_CCAHS;
					_hoops_PCAHS = ysize;
				}
				else if (light->y > 0.99f || light->y < -0.99f) {
					_hoops_SPH->up_vector.x = 0.0f;
					_hoops_SPH->up_vector.y = 0.0f;
					_hoops_SPH->up_vector.z = 1.0f;

					_hoops_ACAHS = _hoops_RGRS;
					_hoops_PCAHS = _hoops_CCAHS;
				}
				else {
					_hoops_SPH->up_vector.x = 1.0f;
					_hoops_SPH->up_vector.y = 0.0f;
					_hoops_SPH->up_vector.z = 0.0f;

					_hoops_ACAHS = ysize;
					_hoops_PCAHS = _hoops_RGRS;
				}


				_hoops_SPH->_hoops_CRSS = light->_hoops_SAIAR(_hoops_SPH->up_vector);

				_hoops_HAHCR.x = _hoops_SPH->up_vector.x;
				_hoops_HAHCR.y = _hoops_SPH->up_vector.y;
				_hoops_HAHCR.z = _hoops_SPH->up_vector.z;

				bounding = Bounding::Create();
				HI_Accumulate_Segment_Bounding (dc->_hoops_RIGC, _hoops_SRCP, bounding,
												&_hoops_PGCPH->transform_rendition->_hoops_IPH->data,
												T_FACES, _hoops_AACAA|_hoops_CRIAA|_hoops_RACAA);

				center = _hoops_AICIR(bounding->cuboid.min, bounding->cuboid.max);
			}
			else {
				if (_hoops_SSRP < 0.01f) {
					/* _hoops_RRR _hoops_AIIA _hoops_GGAIA _hoops_IS _hoops_IPPA */
					return false;
				}

				Bounding			bounding = Bounding::Create();

				HI_Accumulate_Segment_Bounding (dc->_hoops_RIGC, _hoops_SRCP, bounding,
												&nr->transform_rendition->_hoops_IPH->data,
												T_FACES, _hoops_AACAA|_hoops_CRIAA|_hoops_RACAA);

				if (bounding._hoops_HICAR()) {
					_hoops_SPSS->valid = true;
					_hoops_SPSS->_hoops_APGGR = false;
					return false;
				}


				ZALLOC(_hoops_SPH, _hoops_HHRA);
				HI_Default_Camera(_hoops_SPH);
				/* _hoops_SGSS 0 _hoops_GRS _hoops_SHH _hoops_GRSS _hoops_HPP _hoops_RRSS */

				_hoops_SPH->target = bounding->sphere.center;

				_hoops_ACAHS = _hoops_PCAHS = bounding->sphere.radius;

				if (_hoops_SSRP > 0.99f) {
					/* _hoops_PSP _hoops_SCAHS _hoops_HSCHR, _hoops_SSS _hoops_GII _hoops_AAGA _hoops_GSAHS _hoops_IS _hoops_RRR */

					/*	_hoops_AHGC _hoops_RRP _hoops_HAR _hoops_SHH _hoops_AARGR, _hoops_SAHR _hoops_HAR _hoops_GGAIA */
					_hoops_SPH->_hoops_CRSS = light->_hoops_SAIAR(Vector(0.0f, 0.0f, 1.0f));

					if (_hoops_SPH->_hoops_CRSS.x == 0.0f &&
						  _hoops_SPH->_hoops_CRSS.y == 0.0f &&
							_hoops_SPH->_hoops_CRSS.z == 0.0f) {

						/* _hoops_AHCI _hoops_AHGC -- _hoops_RRR _hoops_PIHA _hoops_SHH _hoops_IGIAR _hoops_AHCR _hoops_IRSS, _hoops_GHCR _hoops_HRGR _hoops_IHRI _hoops_PSCR */
						_hoops_SPH->_hoops_CRSS = light->_hoops_SAIAR(Vector(0.0f, 1.0f, 0.0f));
					}
				}
				else {
					/* _hoops_GRHC _hoops_SARA _hoops_SPCR _hoops_IS _hoops_SHH _hoops_RH _hoops_RSAHS _hoops_IRSS */
					_hoops_SPH->_hoops_CRSS = light->_hoops_SAIAR(*((Vector const *)plane));
				}

				_hoops_SPH->_hoops_CRSS._hoops_AAIAR();

				_hoops_SPH->up_vector = _hoops_SPH->_hoops_CRSS._hoops_SAIAR(*light);
				_hoops_SPH->up_vector._hoops_AAIAR(); /* _hoops_SAHR _hoops_IS _hoops_SHH _hoops_RCRR */

				/* _hoops_RRP _hoops_IRS _hoops_AAGA _hoops_GGR _hoops_RH _hoops_IPPA _hoops_GSAHS _hoops_IS _hoops_RH _hoops_SARA _hoops_IRGGA */
				_hoops_HAHCR = _hoops_SPH->_hoops_CRSS._hoops_SAIAR(*((Vector const *)plane));
				_hoops_HAHCR._hoops_AAIAR();

				/* _hoops_PPR _hoops_CPPSR _hoops_IS _hoops_IGIR _hoops_IPSH _hoops_CIAAI _hoops_SAPGP _hoops_IS _hoops_GII _hoops_HSAIP */
				float _hoops_ASAHS = 1.0f / _hoops_SSRP;

				_hoops_HAHCR *= _hoops_ASAHS;

				bounding = Bounding::Create();

				HI_Accumulate_Segment_Bounding (dc->_hoops_RIGC, _hoops_SRCP, bounding,
												&_hoops_PGCPH->transform_rendition->_hoops_IPH->data,
												T_FACES, _hoops_AACAA|_hoops_CRIAA|_hoops_RACAA);
				center =  bounding->sphere.center;
			}

			/* _hoops_SGSSR _hoops_IIGR _hoops_RRR _hoops_RHIR _hoops_IASC _hoops_RHCH _hoops_CCA _hoops_IPPA */
			float t = -(plane->a * _hoops_SPH->target.x +
						plane->b * _hoops_SPH->target.y +
						plane->c * _hoops_SPH->target.z +
						plane->d) / _hoops_SSRP;

			center.x += t * light->x;
			center.y += t * light->y;
			center.z += t * light->z;

			if (_hoops_ACAHS >= _hoops_PCAHS) {
				if (_hoops_ACAHS > _hoops_RCAHS || _hoops_HAP == 0.0f) {
					_hoops_PCAHS += _hoops_ACAHS * (scale - 1.0f);
					_hoops_ACAHS *= scale;
					_hoops_HCAHS = pixels;
					_hoops_ICAHS = int (_hoops_PCAHS / _hoops_HAP);
					size = _hoops_ACAHS;
				}
				else {
					_hoops_HCAHS = (int)(_hoops_ACAHS / _hoops_HAP + 0.99f) + border;
					_hoops_ICAHS = (int)(_hoops_PCAHS / _hoops_HAP + 0.99f) + border;
					_hoops_ACAHS = _hoops_HCAHS * _hoops_HAP;
					_hoops_PCAHS = _hoops_ICAHS * _hoops_HAP;
					pixels /= 2;
					while (pixels >= 2*_hoops_HCAHS)
						pixels /= 2;
					size = pixels * _hoops_HAP;
					pixels *= 2;
				}
			}
			else {
				if (_hoops_PCAHS > _hoops_RCAHS || _hoops_HAP == 0.0f) {
					_hoops_ACAHS += _hoops_PCAHS * (scale - 1.0f);
					_hoops_PCAHS *= scale;
					_hoops_HCAHS = int (_hoops_ACAHS / _hoops_HAP);
					_hoops_ICAHS = pixels;
					size = _hoops_PCAHS;
				}
				else {
					_hoops_HCAHS = (int)(_hoops_ACAHS / _hoops_HAP + 0.99f) + border;
					_hoops_ICAHS = (int)(_hoops_PCAHS / _hoops_HAP + 0.99f) + border;
					_hoops_ACAHS = _hoops_HCAHS * _hoops_HAP;
					_hoops_PCAHS = _hoops_ICAHS * _hoops_HAP;
					pixels /= 2;
					while (pixels >= 2*_hoops_ICAHS)
						pixels /= 2;
					size = pixels * _hoops_HAP;
					pixels *= 2;
				}
			}

			_hoops_SPSS->points[0].x = center.x - _hoops_ACAHS * _hoops_SPH->_hoops_CRSS.x - _hoops_PCAHS * _hoops_HAHCR.x;
			_hoops_SPSS->points[0].y = center.y - _hoops_ACAHS * _hoops_SPH->_hoops_CRSS.y - _hoops_PCAHS * _hoops_HAHCR.y;
			_hoops_SPSS->points[0].z = center.z - _hoops_ACAHS * _hoops_SPH->_hoops_CRSS.z - _hoops_PCAHS * _hoops_HAHCR.z;
			_hoops_SPSS->points[1].x = center.x + _hoops_ACAHS * _hoops_SPH->_hoops_CRSS.x - _hoops_PCAHS * _hoops_HAHCR.x;
			_hoops_SPSS->points[1].y = center.y + _hoops_ACAHS * _hoops_SPH->_hoops_CRSS.y - _hoops_PCAHS * _hoops_HAHCR.y;
			_hoops_SPSS->points[1].z = center.z + _hoops_ACAHS * _hoops_SPH->_hoops_CRSS.z - _hoops_PCAHS * _hoops_HAHCR.z;
			_hoops_SPSS->points[2].x = center.x - _hoops_ACAHS * _hoops_SPH->_hoops_CRSS.x + _hoops_PCAHS * _hoops_HAHCR.x;
			_hoops_SPSS->points[2].y = center.y - _hoops_ACAHS * _hoops_SPH->_hoops_CRSS.y + _hoops_PCAHS * _hoops_HAHCR.y;
			_hoops_SPSS->points[2].z = center.z - _hoops_ACAHS * _hoops_SPH->_hoops_CRSS.z + _hoops_PCAHS * _hoops_HAHCR.z;
			_hoops_SPSS->points[3].x = center.x + _hoops_ACAHS * _hoops_SPH->_hoops_CRSS.x + _hoops_PCAHS * _hoops_HAHCR.x;
			_hoops_SPSS->points[3].y = center.y + _hoops_ACAHS * _hoops_SPH->_hoops_CRSS.y + _hoops_PCAHS * _hoops_HAHCR.y;
			_hoops_SPSS->points[3].z = center.z + _hoops_ACAHS * _hoops_SPH->_hoops_CRSS.z + _hoops_PCAHS * _hoops_HAHCR.z;
			_hoops_SPSS->points[4].x = center.x;
			_hoops_SPSS->points[4].y = center.y; /* _hoops_GRHP _hoops_RHCH _hoops_PIRA _hoops_AARI _hoops_IH _hoops_PIHGR _hoops_HCHIA */
			_hoops_SPSS->points[4].z = center.z;

			if (_hoops_SPSS->image != null) {
				if (_hoops_SPSS->image->width != pixels) {
					_hoops_HPRH (_hoops_SPSS->image);
					_hoops_SPSS->image = null;
				}
				else {
					/* _hoops_SCAC _hoops_GGSR _hoops_PIAH _hoops_CIPH */
					if (_hoops_SPSS->image->next) {
						_hoops_HPRH (_hoops_SPSS->image->next);
						_hoops_SPSS->image->next = null;
					}

					_hoops_SPSS->image->_hoops_CPGPR = _hoops_AHSGA;
				}
			}
			if (_hoops_SPSS->image == null) {
				HI_Create_Image (&_hoops_SPSS->image,
								 null,
								 pixels, pixels,
								 _hoops_CSGSP, 0,
								 _hoops_HISCP, null);
				_hoops_SPSS->image->flags |= _hoops_SHCC;
				HOOPS_WORLD->_hoops_ACPIR++;
				HI_Validate_Inverted_Rasters (_hoops_SPSS->image);
			}

			if (size) {
				_hoops_SPSS->_hoops_CHRP = _hoops_ACAHS / size;
				_hoops_SPSS->_hoops_SHRP = _hoops_PCAHS / size;
			}

			float							_hoops_SIRHS;

			nr->_hoops_RCSHR &= ~_hoops_CRSI;
			nr->current &= ~_hoops_CRSI;

			_hoops_CSHHP->window._hoops_ASIHP = _hoops_GIARP;
			_hoops_SGRA->_hoops_ASIHP = _hoops_GIARP;
			_hoops_IHCR->heuristics &= ~_hoops_IRI;
			if (dc->_hoops_IPCI->_hoops_IPSS == nullroutine)
				_hoops_RRGH->_hoops_SRI = _hoops_RRAAP;

			nr->flags &= ~_hoops_SPSHP;
			nr->flags |= _hoops_GHSHP;

			_hoops_RCIR->_hoops_PRH.style = Transparency_STYLE_BLENDING;

			_hoops_RCIR->_hoops_GHSS._hoops_RPHHP = _hoops_PGCPH->_hoops_CPP->_hoops_GHSS._hoops_RPHHP;

			nr->_hoops_RGP = _hoops_PGCPH->_hoops_RGP &
								(T_FACES|T_WINDOWS|T_CUTTING_PLANES|T_CUT_GEOMETRY) |
							 T_WINDOWS;
			_hoops_RRGH->_hoops_AARIP = _hoops_PGCPH->_hoops_IRR->_hoops_AARIP &
								(T_FACES|T_WINDOWS|T_CUTTING_PLANES|T_CUT_GEOMETRY) |
							 T_WINDOWS;
			_hoops_RRGH->_hoops_GHIHP =
					_hoops_PGCPH->_hoops_IRR->_hoops_GHIHP & T_FACES;

			_hoops_RRGH->_hoops_CSA = _hoops_IHGPR;

			if (!dc->_hoops_ACPGR->_hoops_IPSS)
				_hoops_RRGH->_hoops_GAHA = Display_List_NONE;

			if (_hoops_SGRA->_hoops_SICSR != null) {
				_hoops_HPRH (_hoops_SGRA->_hoops_SICSR);
				_hoops_SGRA->_hoops_SICSR = null;
			}
			_hoops_SGRA->_hoops_GPIR._hoops_HRIR.r =
			 _hoops_SGRA->_hoops_GPIR._hoops_HRIR.g =
			  _hoops_SGRA->_hoops_GPIR._hoops_HRIR.b = 0;
			_hoops_SGRA->_hoops_CGAIP = FP_SOLID;

			/* _hoops_CHASA _hoops_GII _hoops_GAPGH & _hoops_RPPS _hoops_HRP _hoops_GH _hoops_IS _hoops_RGR _hoops_PPSR */
			_hoops_SIRHS = _hoops_SGRA->extent.left - _hoops_SGRA->_hoops_HHCAR.left;

			_hoops_SGRA->_hoops_CIIH.left	= _hoops_SGRA->_hoops_PHRA.left	= _hoops_SGRA->_hoops_SCIH.left	= 0;
			_hoops_SGRA->_hoops_CIIH.bottom	= _hoops_SGRA->_hoops_PHRA.bottom	= _hoops_SGRA->_hoops_SCIH.bottom	= 0;
			_hoops_SGRA->_hoops_CIIH.right	= _hoops_SGRA->_hoops_PHRA.right	= _hoops_SGRA->_hoops_SCIH.right	= _hoops_RARHS - 1;
			_hoops_SGRA->_hoops_CIIH.top	= _hoops_SGRA->_hoops_PHRA.top	= _hoops_SGRA->_hoops_SCIH.top	= _hoops_RARHS - 1;
			_hoops_SGRA->extent.left	 = _hoops_SGRA->extent.bottom = 0.0f;
			_hoops_SGRA->extent.right = _hoops_SGRA->extent.top	 = (float)(_hoops_RARHS-1) + 0.99f;
			_hoops_SGRA->_hoops_HHCAR.left	 = _hoops_SGRA->extent.left	 - _hoops_SIRHS;
			_hoops_SGRA->_hoops_HHCAR.right	 = _hoops_SGRA->extent.right	 + _hoops_SIRHS;
			_hoops_SGRA->_hoops_HHCAR.bottom = _hoops_SGRA->extent.bottom - _hoops_SIRHS;
			_hoops_SGRA->_hoops_HHCAR.top	 = _hoops_SGRA->extent.top	 + _hoops_SIRHS;
			_hoops_SGRA->_hoops_CSIH = 1.0f;

			_hoops_IHCR->_hoops_IPH = _hoops_PGCPH->transform_rendition->_hoops_IPH;

			/* _hoops_AHH: _hoops_PPSHR _hoops_SRIPR _hoops_GAPA _hoops_RSRHS _hoops_PPR _hoops_PSAHS, _hoops_PAHH _hoops_GGR _hoops_RH _hoops_SGSI
			   _hoops_HPPP, _hoops_PGAP _hoops_IGISR _hoops_GGR _hoops_RH _hoops_GGSP _hoops_ACIPR _hoops_HSPH _hoops_GGR _hoops_RH _hoops_HIHP _hoops_IPP. _hoops_GPGP _hoops_RH _hoops_AHHH _hoops_RHPP, _hoops_RGR _hoops_GPGH'_hoops_RA
			   _hoops_RH _hoops_AGIR _hoops_PPR _hoops_SCH _hoops_HRGR _hoops_RAAP _hoops_AIPH. _hoops_RCPA _hoops_GGSP _hoops_SGS, _hoops_CISA _hoops_GGR _hoops_RH _hoops_ACIPR _hoops_HSPH _hoops_IH _hoops_RH _hoops_RCAR _hoops_HH _hoops_HA.

			   _hoops_PS _hoops_GA'_hoops_RA _hoops_AA _hoops_RGR _hoops_HCCPR _hoops_RH _hoops_RCAR _hoops_ACPH _hoops_HRGR _hoops_IISGS _hoops_HPP _hoops_RH _hoops_RHPP, _hoops_GAR _hoops_IRS _hoops_HSAHS _hoops_PPRRR _hoops_IIGR _hoops_ISAHS _hoops_AHHH.

			   _hoops_RAIGR _hoops_AGSRH _hoops_CCIH _hoops_HRGR _hoops_HGGC _hoops_RGHP _hoops_ARI. */
			if (dc->_hoops_ACPGR->_hoops_IPSS) {
				_hoops_IHCR->_hoops_AGAA.left = _hoops_SGRA->_hoops_PHRA.left;
				_hoops_IHCR->_hoops_AGAA.bottom = _hoops_SGRA->_hoops_PHRA.bottom;
				_hoops_IHCR->_hoops_AGAA.right = _hoops_SGRA->_hoops_PHRA.right;
				_hoops_IHCR->_hoops_AGAA.top = _hoops_SGRA->_hoops_PHRA.top;
			}

			_hoops_IHCR->_hoops_APH &= ~(Heur_Culling_EXTENT|_hoops_RIHS);

			_hoops_SPH->position.x = _hoops_SPH->target.x + size * light->x;
			_hoops_SPH->position.y = _hoops_SPH->target.y + size * light->y;
			_hoops_SPH->position.z = _hoops_SPH->target.z + size * light->z;

			_hoops_SPH->_hoops_RRHH = _hoops_RSPCR;
			_hoops_SPH->projection = _hoops_CPPCR;
			_hoops_SPH->_hoops_IIPCR.x = -light->x;
			_hoops_SPH->_hoops_IIPCR.y = -light->y;
			_hoops_SPH->_hoops_IIPCR.z = -light->z;
			_hoops_SPH->_hoops_SRIR = size;
			_hoops_SPH->_hoops_ISPA = _hoops_SPH->_hoops_SSPA = 2.0f * size * (_hoops_RARHS / pixels);
			_hoops_SPH->_hoops_ARSS = _hoops_SPH->_hoops_PRSS = 2.0f;
			_hoops_SPH->_hoops_CSIH = 1.0f;
			_hoops_SPH->_hoops_IHCH = _hoops_SPH->_hoops_HHCH = 0.0f;
			_hoops_SPH->_hoops_CIPCR = 0.0f;
			_hoops_SPH->_hoops_SIPCR = &_hoops_SPH->_hoops_CIPCR;

			HD_Downwind_Camera (nr, (Attribute *)_hoops_SPH);

			// _hoops_CICA _hoops_IS _hoops_RPGS _hoops_PHSPR _hoops_IH _hoops_GASAR _hoops_SGHC
			if (_hoops_PGCPH->transform_rendition->_hoops_RGH != null)
				stage = _hoops_IIAHS;
			else
				stage = _hoops_CIAHS;

			dc->flags |= _hoops_GPHHP;

			_hoops_SPSS->_hoops_CHSS = true;
		}	break;


		case _hoops_IIAHS: {
			_hoops_CPSS *					_hoops_SPSS = dc->_hoops_GHSS.current;
			Net_Rendition		 			_hoops_PGCPH = _hoops_SPSS->master_rendition;
			_hoops_HHCR alter &		_hoops_IHCR = nr->transform_rendition;

			if (_hoops_IHCR != _hoops_PGCPH->transform_rendition)
				_hoops_IHCR->_hoops_RGH = _hoops_PGCPH->transform_rendition->_hoops_RGH;

			if (_hoops_IHCR->_hoops_RGH != null) {
				_hoops_IHCR->flags |= _hoops_CSP;
				nr->_hoops_RCSHR |= _hoops_GPRIP;
			}


			stage = _hoops_CIAHS;
		}	_hoops_HHHI;


		case _hoops_CIAHS: {
			_hoops_CIGA alter &			_hoops_SIGA = nr->_hoops_IHA;
			_hoops_GRGH alter &			_hoops_RRGH = nr->_hoops_IRR;
			_hoops_HHCR alter &		_hoops_IHCR = nr->transform_rendition;
			Attribute const *				_hoops_HPHCR;

			if (!ANYBIT(dc->flags, _hoops_GIHCP|_hoops_IGSS)) {
				if (_hoops_SRCP != nr->_hoops_SRA->_hoops_AAHSR &&
					(BIT (nr->_hoops_RCSHR, _hoops_CRHPP) ||
					 BIT (_hoops_SRCP->_hoops_PHSI, _hoops_HCHGP)))
					return false;
			}
			if (_hoops_IHCR->_hoops_HCIH.left != -1 ||
				_hoops_IHCR->_hoops_HCIH.right != 1 ||
				_hoops_IHCR->_hoops_HCIH.bottom != -1 ||
				_hoops_IHCR->_hoops_HCIH.top != 1)
				return false;
			if ((_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR) != null) do {
				if (_hoops_HPHCR->type == HK_RENDERING_OPTIONS) {
					_hoops_RHAIR const *_hoops_AHAIR = (_hoops_RHAIR const *)_hoops_HPHCR;

					if (BIT (_hoops_AHAIR->_hoops_SCIAA & _hoops_AHAIR->_hoops_RSIAA, _hoops_AGICA) &&
						_hoops_AHAIR->_hoops_PGICA != _hoops_GCAAP)
					{
						bool global_locked = BIT (_hoops_RRGH->locks._hoops_IPPGR, _hoops_GGCAA(HK_RENDERING_OPTIONS));
						bool _hoops_ACIPH = (
							BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_GSIAA) &&
							BIT (_hoops_AHAIR->locks->normal.mask._hoops_IPPGR, _hoops_GGCAA(HK_RENDERING_OPTIONS)));
						if (!global_locked || _hoops_ACIPH)
							return false;
					}
				}
				else if (_hoops_HPHCR->type > HK_RENDERING_OPTIONS)
					break;
			} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);

			if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA))
				return false;
			if (ANYBIT (nr->_hoops_RCSHR, _hoops_HIRHS))
				return false;

			if (BIT(dc->flags, _hoops_GPHHP)) {
				if (BIT(nr->flags, _hoops_SPSHP) ||
					!BIT(nr->flags, _hoops_GHSHP))
					return false;

				nr->_hoops_RGP &= ~T_ANY_EDGE;
				if (!BIT (_hoops_RRGH->_hoops_CRR, _hoops_SHHGP))
					nr->_hoops_RGP &= ~T_FACES;
				else {
					nr->_hoops_RGP |= (_hoops_RRGH->_hoops_AARIP & T_FACES);
#if 0
					// _hoops_HGI _hoops_HRGR _hoops_RH _hoops_CCIH _hoops_IH _hoops_GGIC _hoops_APSAR _hoops_HAR _hoops_RAHIR _hoops_RGCH
					if (BIT (nr->_hoops_RGP, T_FACES))
						nr->_hoops_RGP |= _hoops_CRHGP;
#endif
				}
			}


			if (BIT(dc->flags, _hoops_GIHCP)) {		// _hoops_RCAR _hoops_ACAR
				Display_Context alter *_hoops_HAPRH;
				_hoops_HAPRH = (Display_Context alter *)dc;

				_hoops_HAPRH->flags &= ~_hoops_IGSS; // _hoops_PSP _hoops_RPIP _hoops_HPGR _hoops_RH _hoops_SCIA _hoops_PAPA

#ifdef SHADOW_MAPS_WITH_TRANSMISSION
				if (!BIT (_hoops_RRGH->_hoops_CRR, _hoops_SHHGP))
#else
				if (_hoops_SIGA->_hoops_CHA->_hoops_IRIR != 1.0f ||
					!BIT (_hoops_RRGH->_hoops_CRR, _hoops_SHHGP))
#endif
					nr->_hoops_RGP &= ~T_FACES;
				else
					nr->_hoops_RGP |= (_hoops_RRGH->_hoops_AARIP & T_FACES);
			}
			else {									// _hoops_IHGP _hoops_RGCH
				if (!dc->_hoops_ACPGR->_hoops_IPSS)
					_hoops_RRGH->_hoops_GAHA = Display_List_NONE;
			}


			_hoops_IHCR->_hoops_HCHH = null;

			_hoops_IHCR->_hoops_APH &= ~(Heur_Culling_EXTENT|_hoops_RIHS);
		}
	}


	// _hoops_SHR
	_hoops_GRGH alter &			_hoops_RRGH = nr->_hoops_IRR;
	_hoops_CIGA alter &			_hoops_SIGA = nr->_hoops_IHA;
	Line_Rendition alter &			_hoops_GHP = nr->_hoops_RHP;
	_hoops_CIGA alter &			_hoops_SPIHP = nr->_hoops_HAIHP;

	nr->_hoops_RCSHR &= ~_hoops_IIRHS;
	nr->current &= ~_hoops_IIRHS;

	_hoops_RRGH->locks.color = Color_EVERYTHING | Color_CUT_FACE | Color_CUT_EDGE;
#ifdef SHADOW_MAPS_WITH_TRANSMISSION
	_hoops_RRGH->locks._hoops_HAA[_hoops_IAA] = _hoops_RRGH->locks._hoops_HAA[_hoops_RSHHP] = ~0;
#else
	_hoops_RRGH->locks._hoops_HAA[_hoops_IAA] = _hoops_RRGH->locks._hoops_HAA[_hoops_RSHHP] = ~M_TRANSMISSION;
#endif
	_hoops_RRGH->locks._hoops_RGP = T_ANY_DRAWABLE_GEOMETRY & ~(T_FACES|T_ANY_SHADOW);

	if (nr->_hoops_CPP->_hoops_GHSS._hoops_RPHHP) {
		_hoops_SIGA->_hoops_CHA->_hoops_IRIR = 1.0f;
		_hoops_SIGA->_hoops_GIA->_hoops_IRIR = 1.0f;
	}
	else {	// _hoops_PHIH (_hoops_RRI _hoops_PAR _hoops_CRGP)
		_hoops_SIGA->_hoops_CHA->_hoops_IRIR = 1.0f - _hoops_SIGA->_hoops_CHA->color[_hoops_PCA]._hoops_CPIR();
		_hoops_SIGA->_hoops_GIA->_hoops_IRIR = 1.0f - _hoops_SIGA->_hoops_GIA->color[_hoops_PCA]._hoops_CPIR();
	}

	_hoops_SIGA->color._hoops_HRIR.r =
	 _hoops_SIGA->color._hoops_HRIR.g =
	  _hoops_SIGA->color._hoops_HRIR.b = 255;
	_hoops_SIGA->color._hoops_HRIR.a = (unsigned char)(_hoops_SIGA->_hoops_CHA->_hoops_IRIR * 255.99f);

	_hoops_SIGA->_hoops_SCHHP =
	 _hoops_SIGA->_hoops_RGIR = _hoops_SIGA->color;
	_hoops_SIGA->_hoops_AGP = null;
	_hoops_SIGA->pattern = FP_SOLID;

	if (_hoops_SIGA->_hoops_CHA->_hoops_ARIR) {
		_hoops_HHA alter &		mat = _hoops_SIGA->_hoops_CHA;

		HI_Free_Diffuse_Channel_List (mat->_hoops_SCA);
		mat->_hoops_SCA = null;

		for (int i=0; i<_hoops_GAGRA; i++) {
			if (mat->texture[i] != null && i != _hoops_PCA) {
				_hoops_HPRH (mat->texture[i]);
				mat->texture[i] = null;
			}
		}

		mat->_hoops_ARIR = (mat->texture[_hoops_PCA] != null);
	}

	_hoops_GHP->color = _hoops_SIGA->color;
	_hoops_GHP->color._hoops_HRIR.a /= 16;
	_hoops_GHP->_hoops_SCHHP = _hoops_GHP->color;
	_hoops_GHP->_hoops_AGP = null;
	if (_hoops_GHP->line_style != nr->_hoops_GCSHP->_hoops_IHRIP)
		HD_Replace_Line_Style(_hoops_GHP, nr->_hoops_GCSHP->_hoops_IHRIP);
	_hoops_GHP->weight = 1;
	_hoops_GHP->flags = 0;
	_hoops_GHP->style = LCAP_BUTT|LJOIN_MITER;
	nr->_hoops_CPP->_hoops_PRH._hoops_HRH = true;

	_hoops_SPIHP->color._hoops_HRIR.r =
	 _hoops_SPIHP->color._hoops_HRIR.g =
	  _hoops_SPIHP->color._hoops_HRIR.b = 255;
	_hoops_SPIHP->_hoops_SCHHP =
	 _hoops_SPIHP->_hoops_RGIR = _hoops_SPIHP->color;
	_hoops_SPIHP->_hoops_AGP = null;


	return true;
}



GLOBAL_FUNCTION void HD_Reposition_Shadow (
	Net_Rendition const & 		nr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path) {
	_hoops_CPSS *				_hoops_SPSS;

	{
		_hoops_SPAGR					_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, nr->_hoops_SRA->_hoops_RIGC->thread_id);
		_hoops_AHAGR *			_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, path);
		_hoops_SPSS = _hoops_CSC->_hoops_CSCGP();
	}

	_hoops_SPSS->_hoops_RIHSP = true;

	Vector const *	light = &nr->_hoops_CPP->_hoops_GHSS.light;
	_hoops_ARPA const *	plane = &nr->_hoops_CPP->_hoops_GHSS.plane;

	float	_hoops_SSRP = plane->a * light->x + plane->b * light->y + plane->c * light->z;
	Point	center;

	if (_hoops_SSRP > 0.99f &&
		(light->x > 0.99f || light->y > 0.99f || light->z > 0.99f ||
		 light->x < -0.99f || light->y < -0.99f || light->z < -0.99f)) {

		Bounding			bounding = Bounding::Create();

		HI_Accumulate_Segment_Bounding (nr->_hoops_SRA->_hoops_RIGC, _hoops_SRCP, bounding,
										&nr->transform_rendition->_hoops_IPH->data,
										T_FACES, _hoops_AACAA|_hoops_CRIAA|_hoops_RACAA);

		if (bounding._hoops_HICAR())
			return;		/* _hoops_PSP _hoops_PSIGA _hoops_CPAP */

		center = _hoops_AICIR(bounding->cuboid.min, bounding->cuboid.max);
	}
	else {
		if (_hoops_SSRP < 0.01f) {
			/* _hoops_RRR _hoops_AIIA _hoops_GGAIA _hoops_IS _hoops_IPPA */
			return;
		}

		Bounding			bounding = Bounding::Create();

		HI_Accumulate_Segment_Bounding (nr->_hoops_SRA->_hoops_RIGC, _hoops_SRCP, bounding,
										&nr->transform_rendition->_hoops_IPH->data,
										T_FACES, true);

		if (bounding._hoops_HICAR())
			return;		/* _hoops_PSP _hoops_PSIGA _hoops_CPAP */

		center = bounding->sphere.center;
	}

	/* _hoops_SGSSR _hoops_IIGR _hoops_RRR _hoops_RHIR _hoops_IASC _hoops_RHCH _hoops_CCA _hoops_IPPA */
	float t = -(plane->a * center.x +
				plane->b * center.y +
				plane->c * center.z +
				plane->d) / _hoops_SSRP;

	center.x += t * light->x;
	center.y += t * light->y;
	center.z += t * light->z;

	/* _hoops_AGRP _hoops_IS _hoops_IRS _hoops_ISGSP _hoops_AAGA _hoops_HII _hoops_PGHC _hoops_RHCH */
	center.x -= _hoops_SPSS->points[4].x;
	center.y -= _hoops_SPSS->points[4].y;
	center.z -= _hoops_SPSS->points[4].z;

	for (int i=0; i<5; i++) {
		_hoops_SPSS->points[i].x += center.x;
		_hoops_SPSS->points[i].y += center.y;
		_hoops_SPSS->points[i].z += center.z;
	}
}


GLOBAL_FUNCTION void HD_Compute_Shadow_Resolution (
	Net_Rendition const & 		nr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path) {
	int							pixels = nr->_hoops_CPP->_hoops_GHSS._hoops_HAP;
	_hoops_CPSS *				_hoops_SPSS;

	{
		_hoops_SPAGR					_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, nr->_hoops_SRA->_hoops_RIGC->thread_id);
		_hoops_AHAGR *			_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, path);
		_hoops_SPSS = _hoops_CSC->_hoops_CSCGP();
	}

	if (_hoops_SPSS->image != null && _hoops_SPSS->image->width != pixels) {
		_hoops_HPRH (_hoops_SPSS->image);
		_hoops_SPSS->image = null;
	}

	Vector const *	light = &nr->_hoops_CPP->_hoops_GHSS.light;
	_hoops_ARPA const *	plane = &nr->_hoops_CPP->_hoops_GHSS.plane;

	float	_hoops_SSRP = plane->a * light->x + plane->b * light->y + plane->c * light->z;
	float	size;

	if (_hoops_SSRP > 0.99f &&
		(light->x > 0.99f || light->y > 0.99f || light->z > 0.99f ||
		 light->x < -0.99f || light->y < -0.99f || light->z < -0.99f)) {

		Bounding			bounding = Bounding::Create();

		HI_Accumulate_Segment_Bounding (nr->_hoops_SRA->_hoops_RIGC, _hoops_SRCP, bounding,
										&nr->transform_rendition->_hoops_IPH->data,
										T_FACES, _hoops_CRIAA|_hoops_RACAA);

		if (bounding._hoops_HICAR())
			return;		/* _hoops_PSP _hoops_PSIGA _hoops_CPAP */

		Vector _hoops_RPIS = bounding->cuboid.max - bounding->cuboid.min;

		if (light->x > 0.99f || light->x < -0.99f) {
			size = _hoops_IAAA(_hoops_RPIS.z, _hoops_RPIS.y);
		}
		else if (light->y > 0.99f || light->y < -0.99f) {
			size = _hoops_IAAA(_hoops_RPIS.x, _hoops_RPIS.z);
		}
		else {
			size = _hoops_IAAA(_hoops_RPIS.y, _hoops_RPIS.x);
		}
	}
	else {
		Bounding			bounding = Bounding::Create();

		HI_Accumulate_Segment_Bounding (nr->_hoops_SRA->_hoops_RIGC, _hoops_SRCP, bounding,
										&nr->transform_rendition->_hoops_IPH->data,
										T_FACES, _hoops_CRIAA|_hoops_RACAA);

		if (bounding._hoops_HICAR())
			return;		/* _hoops_PSP _hoops_PSIGA _hoops_CPAP */

		size = 2.0f * bounding->sphere.radius;
	}

	int	border = 2 * nr->_hoops_CPP->_hoops_GHSS._hoops_IGGGR;

	pixels -= 2 * border;
	if (pixels < _hoops_HARHS)
		pixels = _hoops_HARHS;

	_hoops_SPSS->_hoops_AIHSP = size / (float)pixels;
}


GLOBAL_FUNCTION void HD_Shadow_Map_Update (
	Net_Rendition const &		inr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path) {
	Net_Rendition				nr = inr;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_SPAGR						_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
	_hoops_AHAGR *				_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, path);
	_hoops_GSAR alter			*_hoops_HRR, *victim, *_hoops_CSAHS;
	_hoops_PC const &		_hoops_HC = nr->_hoops_IHA->_hoops_AGP;
	_hoops_AS alter *		light;
	_hoops_GSISP			_hoops_SSAHS = dc->_hoops_IPCI->_hoops_SCCSP;
	_hoops_GSPGR						_hoops_RSPGR, _hoops_ASPGR;
	bool						_hoops_SAR;

	_hoops_RSPGR = HI_What_Time();

	dc->flags |= _hoops_GIHCP;

	if ((_hoops_HRR = _hoops_CSC->_hoops_GGSGP()) != null) do {
		_hoops_HRR->used = false;
		_hoops_HRR = (_hoops_GSAR alter *)_hoops_HRR->next;
	} while (_hoops_HRR != null);

	_hoops_SAR = nr->_hoops_CPP->_hoops_HRR._hoops_SAR;
	if (_hoops_SAR &&
		(light = (_hoops_AS alter *) _hoops_HC->_hoops_CGR) != null) {
		int _hoops_PGR = 0;
		while (light) {
			if ((light->_hoops_PRR == _hoops_H || light->_hoops_PRR == _hoops_I) &&
				BIT (light->_hoops_CRR, _hoops_GIHGP))
				_hoops_PGR++;
			light = light->next;
		}
		if (_hoops_PGR > dc->_hoops_PGCC._hoops_HCPGH)
			_hoops_SAR = false;
	}

	_hoops_CSAHS = null;
	_hoops_HRR = _hoops_CSC->_hoops_GGSGP();
	if ((light = (_hoops_AS alter *) _hoops_HC->_hoops_CGR) != null) do {
		if ((light->_hoops_PRR == _hoops_H || light->_hoops_PRR == _hoops_I) &&
			BIT (light->_hoops_CRR, _hoops_GIHGP)) {
			bool _hoops_GGPHS = false;

			if (!_hoops_HRR) {
				ZALLOC (_hoops_HRR, _hoops_GSAR);
				_hoops_HRR->_hoops_PCASP = light->_hoops_PCASP;

				if (!_hoops_CSC->_hoops_GGSGP())
					_hoops_CSC->_hoops_SSCGP (_hoops_HRR);
				else
					_hoops_CSAHS->next = _hoops_HRR;
				_hoops_HRR->next = null;
			}

			/* _hoops_IPS _hoops_CRS _hoops_CIAA _hoops_RRR _hoops_HAGAR */
			light->_hoops_HRR = (_hoops_GSAR const *)_hoops_HRR;

			//_hoops_GA'_hoops_RA _hoops_CRCR _hoops_RCAR _hoops_ACAR _hoops_HII _hoops_SS _hoops_SGS _hoops_HS _hoops_RPII _hoops_GGGGA _hoops_RRI
			//_hoops_PGSRS _hoops_HSAR _hoops_CGPR _hoops_RH _hoops_RCAR _hoops_ARCR _hoops_CSAP _hoops_IIAC
			if (_hoops_HRR->time_stamp < light->time_stamp)
				_hoops_HRR->valid = false;

			_hoops_GGPHS = (_hoops_HRR->_hoops_SAR || light->_hoops_ICASP);

			if (BIT (dc->_hoops_CPGPR, _hoops_IISSR) ||
				!_hoops_HRR->valid || _hoops_GGPHS) {

				if (dc->_hoops_RIGC->_hoops_HCPGR == 0 ||
					(!_hoops_GGPHS && _hoops_HRR->time_stamp == 0)) {

					dc->_hoops_HRR.current = _hoops_HRR;
					if (nr == inr) {
						nr.Modify();
						nr->transform_rendition.Modify();
						nr->_hoops_CPP.Modify();
						nr->_hoops_IRR.Modify();
						nr->_hoops_SAIR.Modify();
						nr->_hoops_RSGC.Modify();
						nr->_hoops_ASIR.Modify();
						nr->_hoops_IHA.Modify();
						nr->_hoops_RHP.Modify();
						_hoops_CIRHS (nr);
					}

					if (_hoops_ASRHS (inr, nr, _hoops_SRCP, light, _hoops_SAR)) {
						_hoops_HRR->master_rendition = nr;
						_hoops_HRR->master_rendition.Modify();

						_hoops_HRR->_hoops_CHSS = true;
						dc->flags |= _hoops_IGSS;

						/* _hoops_AHH: 1/2 _hoops_SGGS _hoops_RGPHS _hoops_HII _hoops_ASAC/_hoops_PHIH _hoops_HPP _hoops_IHGP _hoops_RGCH. _hoops_AGPHS _hoops_PGGS _hoops_PAGIR. */
						Tree_Node *_hoops_PGPHS = dc->_hoops_AHSI;
						dc->_hoops_AHSI = null;

						dc->Add_Filter (POOL_NEW(dc->memory_pool, _hoops_SIAHS)(_hoops_CIAHS));
						int _hoops_HGPHS = dc->_hoops_RIGC->_hoops_HCPGR;
						dc->_hoops_RIGC->_hoops_HCPGR = 0;

						(*dc->_hoops_ACPGR->_hoops_PICS) (nr, _hoops_SRCP, path);

						dc->_hoops_RIGC->_hoops_HCPGR = _hoops_HGPHS;
						dc->Remove_Filter ();
						_hoops_HRR->valid = _hoops_HRR->_hoops_CHSS;
						_hoops_HRR->used = true;
						_hoops_HRR->time_stamp =  HOOPS_WORLD->_hoops_GPPI;

						/* _hoops_AHH: 2/2 _hoops_SGGS _hoops_RGPHS _hoops_HII _hoops_ASAC/_hoops_PHIH _hoops_HPP _hoops_IHGP _hoops_RGCH. _hoops_AGPHS _hoops_PGGS _hoops_PAGIR. */
						dc->_hoops_AHSI = _hoops_PGPHS;
					}
				}
				else {
					_hoops_HRR->valid = false;
				}
			}
			_hoops_CSAHS = _hoops_HRR;
			_hoops_HRR = (_hoops_GSAR alter *) _hoops_HRR->next;
		}
	} while ((light = light->next) != null);


	/* _hoops_RPP _hoops_IGPHS _hoops_CIH */
	if ((_hoops_HRR = _hoops_CSC->_hoops_GGSGP()) != null) do {
		if (!_hoops_HRR->used)
			victim = _hoops_HRR;
		_hoops_HRR = (_hoops_GSAR alter *)_hoops_HRR->next;
		/* _hoops_SRSA _hoops_CIH _hoops_CGPHS */
	} while (_hoops_HRR != null);

	dc->_hoops_IPCI->_hoops_SCCSP = _hoops_SSAHS;

	dc->flags &= ~_hoops_GIHCP;

	_hoops_ASPGR = HI_What_Time();
	_hoops_GPRH(_hoops_GHRGH) += (_hoops_ASPGR - _hoops_RSPGR) / _hoops_HSPGR;
}


GLOBAL_FUNCTION void HD_Shadow_Update (
	Net_Rendition const &		inr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path) 
{
	Net_Rendition				nr = inr;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	Display_Context alter *		_hoops_SGPHS = null;
	Activity					_hoops_GRPHS = _hoops_GSCCA;
	_hoops_HCSIR alter	*	_hoops_RRPHS;
	bool						_hoops_ARPHS = true;
	_hoops_GGAGR alter *				_hoops_GHRI = null;
	_hoops_GSPGR						_hoops_RSPGR, _hoops_ASPGR;

	_hoops_RSPGR = HI_What_Time();

	_hoops_CPSS *				_hoops_SPSS;
	{
		_hoops_SPAGR						_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
		_hoops_AHAGR *				_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, path);
		_hoops_SPSS = _hoops_CSC->_hoops_CSCGP();
	}

	if (dc->_hoops_IPCI->_hoops_IPSS &&
		!BIT(nr->current, _hoops_RSSHP)) {

		int							_hoops_HGRS = 0;


		/* _hoops_PGRS _hoops_PGSI _hoops_ISSC _hoops_IS _hoops_RHPP _hoops_HIS _hoops_SCH _hoops_PAH _hoops_CACH _hoops_HCR _hoops_RCAR _hoops_ASCA.
		   _hoops_RAH _hoops_RGR *_hoops_ARPP* _hoops_CICHR _hoops_GGSR _hoops_RH _hoops_PRPHS _hoops_ACPH. */
		while (!_hoops_AGGR(dc->_hoops_IPCI->id, "driver")) {
			_hoops_HGRS++;
			_hoops_IGRS (dc);
		}

		dc->flags |= _hoops_GPHHP;

		nr.Modify();
		nr->transform_rendition.Modify();
		nr->_hoops_CPP.Modify();
		nr->_hoops_IRR.Modify();
		nr->_hoops_SAIR.Modify();
		nr->_hoops_RSGC.Modify();
		nr->_hoops_IHA.Modify();
		nr->_hoops_RHP.Modify();
		nr->_hoops_HAIHP.Modify();
		_hoops_SPSS->master_rendition = nr;
		dc->_hoops_GHSS.current = _hoops_SPSS;


		Tree_Node *			_hoops_PGPHS = dc->_hoops_AHSI;

		dc->_hoops_AHSI = null;

		_hoops_SPSS->valid = false;
		_hoops_SPSS->_hoops_CHSS = true;

		dc->Add_Filter (POOL_NEW(dc->memory_pool, _hoops_SIAHS)());
		(dc->_hoops_IPCI->_hoops_IPSS) (nr, _hoops_SRCP, path);
		dc->Remove_Filter ();

		_hoops_SPSS->valid = _hoops_SPSS->_hoops_CHSS;

		dc->_hoops_AHSI = _hoops_PGPHS;


		_hoops_SPSS->master_rendition = null;

		nr = inr;

		dc->flags &= ~_hoops_GPHHP;

		/* _hoops_IPRP _hoops_PGSI *_hoops_RAS* _hoops_CSICP _hoops_ISSC _hoops_RH _hoops_RCPGR _hoops_PRPHS */
		while (_hoops_HGRS-- > 0)
			_hoops_SGRS (dc);

		goto _hoops_PRSPR;
	}


#ifndef DISABLE_RASTERIZER
	if (dc->options._hoops_PPHRP == _hoops_CAHRP ||
		dc->options._hoops_PPHRP == _hoops_GPHRP) {
		_hoops_ARPHS = false;
	}
#endif

	if ((_hoops_GHRI = nr->_hoops_SRA->_hoops_GHSS._hoops_GHRI) == null) {
		bool _hoops_CGGHS;
		Image *image;

		ZALLOC (_hoops_GHRI, _hoops_GGAGR);
		((Display_Context alter *)nr->_hoops_SRA)->_hoops_GHSS._hoops_GHRI = _hoops_GHRI;

		_hoops_GHRI->type = HK_DRIVER;
		_hoops_GHRI->owner = _hoops_PGRCA(_hoops_SRCP);
		_hoops_GHRI->backlink = &_hoops_GHRI->next;
		_hoops_GHRI->_hoops_HIHI = 1;


		HI_Create_Image (&image,
						 null,
						 1024, 1024,
						 _hoops_CSGSP, 0,
						 _hoops_HISCP, null);
		image->flags |= _hoops_SHCC;
		HOOPS_WORLD->_hoops_ACPIR++;
		dc->_hoops_GHSS.image = image;
		HI_Validate_Inverted_Rasters (dc->_hoops_GHSS.image);

		_hoops_CGGHS = false;
		while (!_hoops_CGGHS) {
			if (_hoops_ARPHS)
				_hoops_GHRI->connected_action = _hoops_AIRHS;
			else
				_hoops_GHRI->connected_action = _hoops_RIRHS;

			_hoops_GHRI->action = _hoops_GHRI->connected_action;

			HI_Init_Driver (dc->_hoops_RIGC, _hoops_GHRI, true);

			/* _hoops_ASIGA "_hoops_SRSIR" _hoops_RGR _hoops_GRH _hoops_RHPP */
			//_hoops_PCSHA->_hoops_RRRPR->_hoops_AIHGP |= _hoops_HACSC;

			*_hoops_GHRI->_hoops_RAIAP = _hoops_GHRI->_hoops_CISHA;
			_hoops_GHRI->_hoops_RAIAP = &_hoops_GHRI->_hoops_CISHA;

			if ((_hoops_SGPHS = (Display_Context alter *)_hoops_GHRI->_hoops_PPRPR) == null)
				_hoops_SGPHS = (Display_Context alter *)_hoops_GHRI->_hoops_HAIAP;

			if (_hoops_ARPHS) {
				_hoops_SGPHS->_hoops_GHSS.start_device = _hoops_SGPHS->_hoops_ACPGR->start_device;
				_hoops_SGPHS->_hoops_ACPGR->start_device = _hoops_PIRHS;
				_hoops_SGPHS->_hoops_GHSS.get_current_info = _hoops_SGPHS->_hoops_ACPGR->get_current_info;
				_hoops_SGPHS->_hoops_ACPGR->get_current_info	 = _hoops_CHRHS;
			}
			_hoops_SPSS->master_rendition = nr;
			_hoops_SGPHS->_hoops_GHSS.current = _hoops_SPSS;
			if (HD_Standard_Driver (dc->_hoops_RIGC, _hoops_GHRI, _hoops_AAGSC, null)) {
				HD_Get_Physical_Info (_hoops_SGPHS);
				_hoops_SGPHS->current._hoops_HAP.x = _hoops_SGPHS->_hoops_PGCC._hoops_PRPSR.x / _hoops_SGPHS->_hoops_PGCC.size.x;
				_hoops_SGPHS->current._hoops_HAP.y = _hoops_SGPHS->_hoops_PGCC._hoops_PRPSR.y / _hoops_SGPHS->_hoops_PGCC.size.y;
				_hoops_SGPHS->current._hoops_AGRS = _hoops_SGPHS->current._hoops_HAP.x / _hoops_SGPHS->current._hoops_HAP.y;

				_hoops_GHRI->_hoops_CGPIR |= _hoops_GCSHA;
				_hoops_CGGHS = true;
			}
			else if (_hoops_ARPHS) {
#ifdef DISABLE_RASTERIZER
				HE_ERROR (HEC_SYSTEM, HES_NOT_AVAILABLE, "shadow requested but unavailable due to compile options.");
				_hoops_GHRI->_hoops_CGPIR |= _hoops_SGPIR;
				ASSERT(_hoops_GHRI->_hoops_PPRPR == null);
				return;
#endif
				_hoops_ARPHS = false;
			}
		}
	}
	else {
		_hoops_GHRI->owner = _hoops_PGRCA(_hoops_SRCP);
		if (BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_SGPIR))
			goto _hoops_PRSPR;

		_hoops_SGPHS = (Display_Context alter *)_hoops_GHRI->_hoops_PPRPR;
		_hoops_SPSS->master_rendition = nr;
		_hoops_SGPHS->_hoops_GHSS.current = _hoops_SPSS;
	}

	if (!_hoops_ARPHS) {
		_hoops_SGPHS->data = dc->_hoops_GHSS.image;
	}

	_hoops_SGPHS->_hoops_PGCC.size.x = 16;
	_hoops_SGPHS->_hoops_PGCC.size.y = 16;

	/* _hoops_SSPC _hoops_GII _hoops_HHGS _hoops_CCA _hoops_GRAHA _hoops_GAPGH, _hoops_SR _hoops_CHASA _hoops_SPHR */
	_hoops_SGPHS->_hoops_PGCC.flags |= _hoops_HSHSR;

	/* _hoops_CAHP _hoops_RH _hoops_RCAR */
	_hoops_SGPHS->_hoops_AAHSR = _hoops_SRCP;

	{
		_hoops_SPAGR						_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
		_hoops_AHAGR *				_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, path);
		_hoops_RRPHS = _hoops_CSC->_hoops_PSSIR();
		_hoops_CSC->_hoops_HSCGP (null);
	}

	_hoops_SGPHS->flags |= _hoops_GPHHP;
	_hoops_SPSS->valid = false;
	_hoops_SPSS->_hoops_CHSS = true;

	_hoops_SGPHS->Add_Filter (POOL_NEW(dc->memory_pool, _hoops_SIAHS)());
	_hoops_GHRI->_hoops_CGPIR |= _hoops_CSRPH;
	HD_Standard_Driver (dc->_hoops_RIGC, _hoops_GHRI, _hoops_HAGSC, &_hoops_GRPHS);
	_hoops_GHRI->_hoops_CGPIR &= ~_hoops_CSRPH;
	_hoops_SGPHS->Remove_Filter ();
	
	{
		_hoops_SPAGR						_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
		_hoops_AHAGR *				_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, path);
		if (_hoops_CSC->_hoops_PSSIR() != null)
			HD_Free_Frame_Buffer_Info (_hoops_SGPHS->_hoops_SHCIP, _hoops_CSC->_hoops_PSSIR());
		_hoops_CSC->_hoops_HSCGP (_hoops_RRPHS);
	}

	_hoops_SGPHS->_hoops_SHCIP = null;

	if (_hoops_SPSS->valid) {
		/* _hoops_HASPH _hoops_IPARS _hoops_RHPA */
	}
	else {
		_hoops_SPSS->valid = _hoops_SPSS->_hoops_CHSS;

		if (_hoops_SPSS->valid && _hoops_SPSS->image != null) {
			/* _hoops_IPS _hoops_IRPR _hoops_GPSPR _hoops_IIGR _hoops_IAAI _hoops_CSCR _hoops_IS _hoops_RCAR _hoops_CSCR */
			int				i, width, offset;
			RGBAS32 **	source;
			RGBAS32 **	_hoops_PCAP;

			width = _hoops_SPSS->image->width;
			offset = (_hoops_RARHS - _hoops_SPSS->image->height) / 2;
			source = (RGBAS32 **)&dc->_hoops_GHSS.image->rasters[offset];
			_hoops_PCAP = (RGBAS32 **)&_hoops_SPSS->image->rasters[0];

			for (i=0; i<_hoops_SPSS->image->height; i++) {
				_hoops_AIGA (&(*source)[offset], width, RGBAS32, &(*_hoops_PCAP)[0]);
				++source;
				++_hoops_PCAP;
			}

			/* _hoops_PPR _hoops_ASGGR _hoops_SCH _hoops_GAR _hoops_IRS _hoops_HH */
			_hoops_SPSS->_hoops_APGGR = _hoops_IARHS (nr, _hoops_SPSS->image);

			if (_hoops_SPSS->texture == null) {
				_hoops_SPSS->texture = HI_Define_Shadow_Texture (dc->_hoops_RIGC, _hoops_SPSS->image);
			}
			else {
				if (_hoops_SPSS->texture->image != _hoops_SPSS->image) {
					_hoops_HPRH (_hoops_SPSS->texture->image);
					_hoops_SPSS->texture->image = _hoops_SPSS->image;
					_hoops_PRRH (_hoops_SPSS->image);
				}

				if (_hoops_SPSS->texture->_hoops_RHGH != null) {
					_hoops_HPRH (_hoops_SPSS->texture->_hoops_RHGH);
					_hoops_SPSS->texture->_hoops_RHGH = null;
				}
			}
		}
		else
			_hoops_SPSS->_hoops_APGGR = false;

		_hoops_SPSS->_hoops_RIHSP = true;
	}

	(*nr->_hoops_SRA->_hoops_ACPGR->init_picture) (nr);

_hoops_PRSPR:
	_hoops_ASPGR = HI_What_Time();
	_hoops_GPRH(_hoops_GHRGH) += (_hoops_ASPGR - _hoops_RSPGR) / _hoops_HSPGR;

	if (_hoops_GHRI !=  null)
		_hoops_PGRCA(_hoops_GHRI)->owner = null;
}

#endif

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
 * $Id: obf_tmp.txt 1.282 2010-08-03 23:51:11 jason Exp $
 */


#include "hoops.h"
#include "hd_proto.h"

#ifndef PRINTF_DRIVER

/*
 * _hoops_APICR _hoops_PPICR
 */
extern "C" bool HC_CDECL HD_Printf_Driver (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED (request_info);
	return HD_No_Driver (_hoops_RIGC, _hoops_GHRI, request, "printf");
}

#else

/* _hoops_HISRA _hoops_AAP _hoops_PIHA _hoops_PSSP _hoops_HASSC _hoops_GGR _hoops_SCIA _hoops_ARIP _hoops_IIGR _hoops_GRPAI */
#define _hoops_IASSC				1L
#define _hoops_CASSC			(_hoops_IASSC<<0)	 /* 1 */
#define _hoops_SASSC			(_hoops_IASSC<<1)	 /* 2 */
#define _hoops_GPSSC				(_hoops_IASSC<<2)	 /* 4 */
#define _hoops_RPSSC				(_hoops_IASSC<<3)	 /* 8 */
#define _hoops_APSSC					(_hoops_IASSC<<4)	 /* 16 */
#define _hoops_PPSSC				(_hoops_IASSC<<5)	 /* 32 */
#define _hoops_HPSSC			(_hoops_IASSC<<6)	 /* 64 */
#define _hoops_IPSSC			(_hoops_IASSC<<7)	 /* 128 */
#define _hoops_CPSSC			(_hoops_IASSC<<8)	 /* 256 */
#define _hoops_SPSSC			(_hoops_IASSC<<9)	 /* 512 */
#define _hoops_GHSSC				(_hoops_IASSC<<10) /* 1024 */
#define _hoops_RHSSC				(_hoops_IASSC<<11) /* 2048 */
#define _hoops_AHSSC				(_hoops_IASSC<<12) /* 4096 */

#include "database.h"
#include "phedron.h"
#include "driver.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "patterns.h"
#include "phdraw.h"
#include "searchh.h"
#include "hversion.h"
#include <stdio.h>

#define _hoops_IACSR(x) (float)(1.0f/(x))
#define _hoops_PHSSC				13


/*
 * _hoops_ICHHR _hoops_IHGC _hoops_IIGR _hoops_RSH _hoops_AHPH _hoops_IACH _hoops_RH _hoops_IPP _hoops_PPPIA
 * _hoops_HIS _hoops_SR _hoops_PAH _hoops_GRAS _hoops_PAGC
 */
struct _hoops_HHSSC {
	_hoops_GARRR			_hoops_SSAC;
	long				_hoops_GRHPR,
						_hoops_CCCIR;
	Driver_Color		color;
	long				_hoops_IHSSC,
						_hoops_CCASR;
	Driver_Color		contrast_color;
	long				_hoops_CHSSC,
						_hoops_SHSSC;
	Line_Style			line_style;
	int					pattern;
	long				_hoops_GISSC,
						_hoops_RISSC;
	int					weight;
	long				_hoops_AISSC,
						_hoops_PISSC;
	int					style;
	long				_hoops_HISSC,
						_hoops_IISSC;
	void				*font;
	long				_hoops_CISSC,
						_hoops_SISSC;
};

/*
 * _hoops_ICHHR _hoops_IHGC _hoops_IIGR _hoops_HCPH _hoops_IS _hoops_RH _hoops_CPAP _hoops_PCPH
 * _hoops_HIS _hoops_SR _hoops_PAH _hoops_GRAS _hoops_PAGC
 */
struct _hoops_GCSSC {
	long		_hoops_RCSSC;
	long		points;
};

/*
 * _hoops_ICHHR _hoops_IHGC _hoops_IIGR _hoops_HCPH _hoops_IS _hoops_RH _hoops_CIIA _hoops_PCPH
 * _hoops_HIS _hoops_SR _hoops_PAH _hoops_GRAS _hoops_PAGC
 */
typedef long	_hoops_ACSSC;

/*
 * _hoops_ICHHR _hoops_IHGC _hoops_IIGR _hoops_HCHSR _hoops_SRHR _hoops_SHCS / _hoops_CRRHP
 */
struct _hoops_PCSSC {
	int					size;
	unsigned char		*data;
};

/*
 * _hoops_PIH _hoops_SGS _hoops_RHGSR _hoops_AGRR _hoops_RHPP _hoops_HCPH
 */
struct _hoops_HCSSC {
	/* _hoops_RGHR _hoops_IIPR */
	FILE alter *		fp;
	bool				_hoops_ICSSC;
	char				buf[132];

	/* _hoops_AGAH _hoops_IPP _hoops_PRCA */
	bool				_hoops_CCSSC;
	_hoops_HHSSC	transform,
						face,
						line,
						text;
	_hoops_GARRR			_hoops_SCSSC,
						_hoops_GSSSC,
						_hoops_RSSSC;

	/* _hoops_AGAH _hoops_ASCA  (_hoops_RRIPR _hoops_IS _hoops_PSSP _hoops_RHPP._hoops_GGHR) */
	_hoops_GCSSC	draw_3d_ellipse,
						draw_3d_elliptical_arc,
						draw_3d_marker,
						draw_3d_polyline,
						draw_3d_polygon,
						draw_dc_ellipse,
						_hoops_CCISR,
						_hoops_SCISR,
						draw_dc_polyline,
						draw_dc_face,
						draw_dc_colorized_face,
						draw_dc_rectangle,
						draw_dc_polydot,
						draw_dc_text,
						draw_overlay_list,
						_hoops_SCPGR,
						draw_3d_polyedge,
						draw_3d_tristrip,
						_hoops_ASSSC,
						draw_3d_polymarker,
						draw_dc_polytriangle,
						draw_dc_colorized_polytriangle,
						draw_dc_gouraud_polytriangle,
						_hoops_PSSSC,
						_hoops_HSSSC,
						_hoops_IGSSP,
						_hoops_CGSSP,
						_hoops_SGSSP;

	/* _hoops_CIIA _hoops_ISSSC */
	_hoops_ACSSC		_hoops_HSCSP,
						_hoops_ISCSP;
};

/*
 * _hoops_PHSRI _hoops_IS _hoops_GHPHR _hoops_IRS _hoops_PIAP _hoops_CRS _hoops_HII _hoops_IRS _hoops_CSPH _hoops_PAR _hoops_SCII
 */
#define _hoops_CSSSC(dc)		((_hoops_HCSSC alter *)(dc)->data)
#define _hoops_SSSSC(nr)		((_hoops_HCSSC alter *)(nr)->_hoops_SRA->data)


/*
 * _hoops_PGAA
 */
local void _hoops_GGGGS (
	_hoops_HHSSC alter *r) {

	/* _hoops_PHIGR _hoops_AHHR _hoops_IIGR _hoops_CRAPH _hoops_IH _hoops_GII _hoops_GPRR _hoops_IIGR _hoops_IPP */
	r->_hoops_SSAC = (_hoops_GARRR)0;
	r->_hoops_GRHPR = 0L;
	r->_hoops_CCCIR = 0L;
	r->color = _hoops_IAASP;
	r->_hoops_IHSSC = 0L;
	r->_hoops_CCASR = 0L;
	r->contrast_color = _hoops_IAASP;
	r->_hoops_CHSSC = 0L;
	r->_hoops_SHSSC = 0L;
	r->line_style = null;
	r->pattern = -1;
	r->_hoops_GISSC = 0L;
	r->_hoops_RISSC = 0L;
	r->weight = -1;
	r->_hoops_AISSC = 0L;
	r->_hoops_PISSC = 0L;
	r->style = -1;
	r->_hoops_HISSC = 0L;
	r->_hoops_IISSC = 0L;
	r->font = null;
	r->_hoops_CISSC = 0L;
	r->_hoops_SISSC = 0L;
}


/*
 * _hoops_PGAA
 */
local void _hoops_RGGGS (
	_hoops_GCSSC alter	*g) {

	/* _hoops_PHIGR _hoops_AHHR _hoops_IIGR _hoops_CRAPH _hoops_IH _hoops_GII _hoops_GPRR _hoops_IIGR _hoops_CPAP */
	g->_hoops_RCSSC = 0L;
	g->points = 0L;
}


/*
 * _hoops_PGAA
 */
local void _hoops_AGGGS (
	_hoops_ACSSC alter *i) {

	/* _hoops_PHIGR _hoops_AHHR _hoops_IIGR _hoops_CRAPH _hoops_IH _hoops_GII _hoops_GPRR _hoops_IIGR _hoops_CIIA */
	*i = (_hoops_ACSSC)0;
}


/*
 * _hoops_SRAC
 */
local bool start_device (
	Display_Context alter		*dc) {
	_hoops_HCSSC alter				*state;
	int								i;

	ZALLOC (state, _hoops_HCSSC);
	dc->data = (void alter *) state;

	/* _hoops_RGHR _hoops_IIPR */
#	ifdef WIN32_SYSTEM
		if (_hoops_AGGR(dc->_hoops_PCRSR, "null") ||
			_hoops_GPPSA(dc->_hoops_PCRSR, 5, "null+")) {
			state->fp = null;
			state->_hoops_ICSSC = false;
		}
		else {
			if ((state->fp = fopen (dc->_hoops_PCRSR, "w")) == null) {
				HE_ERROR (HEC_PRINTF_DRIVER, HES_FILE_OPEN,
						  Sprintf_S (null,
									 "Can't open Printf driver output '%s'",
									 dc->_hoops_PCRSR));
				FREE (state, _hoops_HCSSC);
				dc->data = null;
				return false;
			}
			state->_hoops_ICSSC = false;
			fprintf (state->fp, "start_device: %s\n", dc->_hoops_PCRSR);
		}
#	else
		if (dc->_hoops_PCRSR == '\0' ||
			_hoops_AGGR (dc->_hoops_PCRSR, "stdout")) {
			state->fp = stdout;
			state->_hoops_ICSSC = true;
			fprintf (state->fp, "start_device: stdout\n");
		}
		else if (_hoops_AGGR (dc->_hoops_PCRSR, "null")) {
			state->fp = null;
			state->_hoops_ICSSC = false;
		}
		else {
			if ((state->fp = fopen (dc->_hoops_PCRSR, "w")) == null) {
				HE_ERROR (HEC_PRINTF_DRIVER, HES_FILE_OPEN,
						  Sprintf_S (null,
									 "Can't open Printf driver output '%s'",
									 dc->_hoops_PCRSR));
				FREE (state, _hoops_HCSSC);
				dc->data = null;
				return false;
			}
			state->_hoops_ICSSC = false;
			fprintf (state->fp, "start_device: %s\n", dc->_hoops_PCRSR);
		}
#	endif /* _hoops_HIHPH */
	for (i = 0; i < 132; i++)
		state->buf[i] = '\0';

	/* _hoops_AGAH _hoops_IPP _hoops_PRCA */
	state->_hoops_CCSSC = false;
	_hoops_GGGGS (&state->transform);
	_hoops_GGGGS (&state->face);
	_hoops_GGGGS (&state->line);
	_hoops_GGGGS (&state->text);
	state->_hoops_SCSSC = (_hoops_GARRR)0;
	state->_hoops_GSSSC = (_hoops_GARRR)0;
	state->_hoops_RSSSC = (_hoops_GARRR)0;

	/* _hoops_AGAH _hoops_ASCA */
	_hoops_RGGGS (&state->draw_3d_ellipse);
	_hoops_RGGGS (&state->draw_3d_elliptical_arc);
	_hoops_RGGGS (&state->draw_3d_marker);
	_hoops_RGGGS (&state->draw_3d_polyline);
	_hoops_RGGGS (&state->draw_3d_polygon);
	_hoops_RGGGS (&state->draw_dc_ellipse);
	_hoops_RGGGS (&state->_hoops_CCISR);
	_hoops_RGGGS (&state->_hoops_SCISR);
	_hoops_RGGGS (&state->draw_dc_polyline);
	_hoops_RGGGS (&state->draw_dc_face);
	_hoops_RGGGS (&state->draw_dc_colorized_face);
	_hoops_RGGGS (&state->draw_dc_rectangle);
	_hoops_RGGGS (&state->draw_dc_polydot);
	_hoops_RGGGS (&state->draw_dc_text);
	_hoops_RGGGS (&state->draw_overlay_list);
	_hoops_RGGGS (&state->_hoops_SCPGR);
	_hoops_RGGGS (&state->draw_3d_polyedge);
	_hoops_RGGGS (&state->draw_3d_tristrip);
	_hoops_RGGGS (&state->_hoops_ASSSC);
	_hoops_RGGGS (&state->draw_3d_polymarker);
	_hoops_RGGGS (&state->draw_dc_polytriangle);
	_hoops_RGGGS (&state->draw_dc_colorized_polytriangle);
	_hoops_RGGGS (&state->draw_dc_gouraud_polytriangle);
	_hoops_RGGGS (&state->_hoops_PSSSC);
	_hoops_RGGGS (&state->_hoops_HSSSC);
	_hoops_RGGGS (&state->_hoops_IGSSP);
	_hoops_RGGGS (&state->_hoops_CGSSP);
	_hoops_RGGGS (&state->_hoops_SGSSP);

	/* _hoops_CIIA _hoops_ISSSC */
	_hoops_AGGGS (&state->_hoops_HSCSP);
	_hoops_AGGGS (&state->_hoops_ISCSP);

	HD_Get_Bit_Patterns_8 (dc, false);
	return true;
}


/*
 * _hoops_PGAA
 */
local void _hoops_PGGGS (
	_hoops_HCSSC alter		*state,
	_hoops_HHSSC const *r,
	char const				*_hoops_GAASR) {

	/* _hoops_PHIGR _hoops_AIRII _hoops_IIGR _hoops_CIPI _hoops_IH _hoops_GII _hoops_GPRR _hoops_IIGR _hoops_IPP */
	if (r->_hoops_CCCIR > 0L) {
		long					total;

		fprintf (state->fp,
				 "\t%s: %ld new, %ld same (%ld percent reused)\n",
				 _hoops_GAASR,
				 r->_hoops_CCCIR,
				 r->_hoops_GRHPR,
				 (100L * r->_hoops_GRHPR) / (r->_hoops_CCCIR + r->_hoops_GRHPR));
		if (r->_hoops_IHSSC > 0L) {
			total = r->_hoops_GRHPR + r->_hoops_IHSSC;
			fprintf (state->fp,
					 "\t\t%s: %ld new, %ld same (%ld percent reused)\n",
					 "color",
					 r->_hoops_CCASR,
					 total,
					 (100L * total) / (r->_hoops_CCASR + total));
		}
		if (r->_hoops_CHSSC > 0L) {
			total = r->_hoops_GRHPR + r->_hoops_CHSSC;
			fprintf (state->fp,
					 "\t\t%s: %ld new, %ld same (%ld percent reused)\n",
					 "contrast color",
					 r->_hoops_SHSSC,
					 total,
					 (100L * total) / (r->_hoops_SHSSC + total));
		}
		if (r->_hoops_GISSC > 0L) {
			total = r->_hoops_GRHPR + r->_hoops_GISSC;
			fprintf (state->fp,
					 "\t\t%s: %ld new, %ld same (%ld percent reused)\n",
					 "pattern",
					 r->_hoops_RISSC,
					 total,
					 (100L * total) / (r->_hoops_RISSC + total));
		}
		if (r->_hoops_AISSC > 0L) {
			total = r->_hoops_GRHPR + r->_hoops_AISSC;
			fprintf (state->fp,
					 "\t\t%s: %ld new, %ld same (%ld percent reused)\n",
					 "weight",
					 r->_hoops_PISSC,
					 total,
					 (100L * total) / (r->_hoops_PISSC + total));
		}
		if (r->_hoops_HISSC > 0L) {
			total = r->_hoops_GRHPR + r->_hoops_HISSC;
			fprintf (state->fp,
					 "\t\t%s: %ld new, %ld same (%ld percent reused)\n",
					 "style",
					 r->_hoops_IISSC,
					 total,
					 (100L * total) / (r->_hoops_IISSC + total));
		}
		if (r->_hoops_CISSC > 0L) {
			total = r->_hoops_GRHPR + r->_hoops_CISSC;
			fprintf (state->fp,
					 "\t\t%s: %ld new, %ld same (%ld percent reused)\n",
					 "font",
					 r->_hoops_SISSC,
					 total,
					 (100L * total) / (r->_hoops_SISSC + total));
		}
	}
}


/*
 * _hoops_PGAA
 */
local void _hoops_HGGGS (
	_hoops_HCSSC alter		*state,
	_hoops_GCSSC const	*g,
	char const				*_hoops_GAASR,
	char const				*data_type) {

	/* _hoops_PHIGR _hoops_AIRII _hoops_IIGR _hoops_CIPI _hoops_IH _hoops_GII _hoops_GPRR _hoops_IIGR _hoops_CPAP */
	if (g->_hoops_RCSSC > 0L)
		fprintf (state->fp, "\t%s: %ld call%s averaging %4.1f %s per call\n",
				 _hoops_GAASR,
				 g->_hoops_RCSSC,
				 (g->_hoops_RCSSC > 1L ? "s" : ""),
				 (float)g->points / (float)g->_hoops_RCSSC,
				 data_type);
}


/*
 * _hoops_PGAA
 */
local void _hoops_IGGGS (
	_hoops_HCSSC alter		*state,
	_hoops_ACSSC const		*i,
	char const				*_hoops_GAASR) {

	/* _hoops_PHIGR _hoops_AIRII _hoops_IIGR _hoops_CIPI _hoops_IH _hoops_GII _hoops_GPRR _hoops_IIGR _hoops_CIIA */
	if (*i > (_hoops_ACSSC)0)
		fprintf (state->fp, "\t%s: %ld calls\n", _hoops_GAASR, *i);
}


/*
 * _hoops_PGAA
 */
local void _hoops_CGGGS (
	_hoops_HCSSC alter				*state,
	Display_Context const		*dc) {

	if (BIT (dc->options._hoops_IRARR, _hoops_RPSSC)) {
		if (state->draw_3d_ellipse._hoops_RCSSC == 0L)
			fprintf (state->fp, "\tdraw_3d_ellipse was not called\n");

		if (state->draw_3d_elliptical_arc._hoops_RCSSC == 0L)
			fprintf (state->fp, "\tdraw_3d_elliptical_arc was not called\n");

		if (state->draw_3d_marker._hoops_RCSSC == 0L)
			fprintf (state->fp, "\tdraw_3d_marker was not called\n");

		if (state->draw_3d_polyline._hoops_RCSSC == 0L)
			fprintf (state->fp, "\tdraw_3d_polyline was not called\n");

		if (state->draw_3d_polygon._hoops_RCSSC == 0L)
			fprintf (state->fp, "\tdraw_3d_polygon was not called\n");
	}

	if (state->draw_dc_ellipse._hoops_RCSSC == 0L)
		fprintf (state->fp, "\tdraw_dc_ellipse was not called\n");

	if (state->_hoops_CCISR._hoops_RCSSC == 0L)
		fprintf (state->fp, "\tdraw_dc_elliptical_arc was not called\n");

	if (state->_hoops_SCISR._hoops_RCSSC == 0L)
		fprintf (state->fp, "\tdraw_dc_outline_ellipse was not called\n");

	if (state->draw_dc_polyline._hoops_RCSSC == 0L)
		fprintf (state->fp, "\tdraw_dc_polyline was not called\n");

	if (state->draw_dc_face._hoops_RCSSC == 0L)
		fprintf (state->fp, "\tdraw_dc_face was not called\n");

	if (state->draw_dc_colorized_face._hoops_RCSSC == 0L)
		fprintf (state->fp, "\tdraw_dc_colorized_face was not called\n");

	if (state->draw_dc_rectangle._hoops_RCSSC == 0L)
		fprintf (state->fp, "\tdraw_dc_rectangle was not called\n");

	if (state->draw_dc_polydot._hoops_RCSSC == 0L)
		fprintf (state->fp, "\tdraw_dc_polydot was not called\n");

	if (state->draw_dc_text._hoops_RCSSC == 0L)
		fprintf (state->fp, "\tdraw_dc_text was not called\n");

	if (state->draw_overlay_list._hoops_RCSSC == 0L)
		fprintf (state->fp, "\tdraw_overlay_list was not called\n");

	if (state->_hoops_SCPGR._hoops_RCSSC == 0L)
		fprintf (state->fp, "\tundraw_overlay_list was not called\n");

	if (BIT (dc->options._hoops_IRARR, _hoops_RPSSC)) {
		if (state->draw_3d_polyedge._hoops_RCSSC == 0L)
			fprintf (state->fp, "\tdraw_3d_polyedge was not called\n");

		if (state->draw_3d_tristrip._hoops_RCSSC == 0L)
			fprintf (state->fp, "\tdraw_3d_tristrip was not called\n");

		if (state->draw_3d_polymarker._hoops_RCSSC == 0L)
			fprintf (state->fp, "\tdraw_3d_polymarker was not called\n");
	}

	if (state->draw_dc_polytriangle._hoops_RCSSC == 0L)
		fprintf (state->fp, "\tdraw_dc_polytriangle was not called\n");

	if (state->draw_dc_colorized_polytriangle._hoops_RCSSC == 0L)
		fprintf (state->fp, "\tdraw_dc_colorized_polytriangle was not called\n");

	if (BIT (dc->options._hoops_IRARR, _hoops_SASSC))
		if (state->draw_dc_gouraud_polytriangle._hoops_RCSSC == 0L)
			fprintf (state->fp, "\tdraw_dc_gouraud_polytriangle was not called\n");

	switch (dc->_hoops_PGCC._hoops_PIHSR) {
		case _hoops_SIHSR: {
			if (dc->_hoops_PGCC._hoops_AAPSR <= 256) {
				if (state->_hoops_PSSSC._hoops_RCSSC == 0L)
					fprintf (state->fp,
							 "\tdraw_dc_mapped8_rasters was not called\n");
			}
			else {
				if (state->_hoops_PSSSC._hoops_RCSSC == 0L)
					fprintf (state->fp,
							 "\tdraw_dc_mapped16_rasters was not called\n");
			}
		}	break;

		case _hoops_HIHSR: {
			if (state->_hoops_PSSSC._hoops_RCSSC == 0L)
				fprintf (state->fp, "\tdraw_dc_rgb32_rasters was not called\n");
		}	break;

		case _hoops_RIIHP: {
			if (state->_hoops_PSSSC._hoops_RCSSC == 0L)
				fprintf (state->fp, "\tdraw_dc_bit_rasters was not called\n");
		}	break;
	}

	if (!BIT (dc->options._hoops_IRARR, _hoops_RPSSC)) {
		if (state->_hoops_IGSSP._hoops_RCSSC == 0L)
			fprintf (state->fp, "\tcreate_frame_buffer was not called\n");

		if (state->_hoops_CGSSP._hoops_RCSSC == 0L)
			fprintf (state->fp, "\tdisplay_frame_buffer was not called\n");

		if (state->_hoops_SGSSP._hoops_RCSSC == 0L)
			fprintf (state->fp, "\tdestroy_frame_buffer was not called\n");
	}

	if (BIT (dc->options._hoops_IRARR, _hoops_PPSSC)) {
		if (state->_hoops_HSCSP == (_hoops_ACSSC)0)
			fprintf (state->fp, "\trequest_location was not called\n");

		if (state->_hoops_ISCSP == (_hoops_ACSSC)0)
			fprintf (state->fp, "\trequest_keyboard was not called\n");
	}
}


/*
 * _hoops_SRAC
 */
local void stop_device (
	Display_Context alter		*dc) {
	_hoops_HCSSC alter				*state = _hoops_CSSSC (dc);

	if (state->fp != null)
		fprintf (state->fp, "\nstop_device\n");

	if (state->fp != null &&
		!BIT (dc->options._hoops_IRARR, _hoops_CPSSC)) {

		fprintf (state->fp, "\t*** rendition handling ***\n");
		_hoops_PGGGS (state, &state->transform, "transform");
		_hoops_PGGGS (state, &state->face, "face");
		_hoops_PGGGS (state, &state->line, "line");
		_hoops_PGGGS (state, &state->text, "text");

		fprintf (state->fp, "\n\t*** geometry processing ***\n");
		_hoops_HGGGS (state, &state->draw_3d_ellipse,
							   "draw_3d_ellipse", "ellipse");
		_hoops_HGGGS (state, &state->draw_3d_elliptical_arc,
							   "draw_3d_elliptical_arc", "elliptical arc");
		_hoops_HGGGS (state, &state->draw_3d_marker,
							   "draw_3d_marker", "marker");
		_hoops_HGGGS (state, &state->draw_3d_polyline,
							   "draw_3d_polyline", "points");
		_hoops_HGGGS (state, &state->draw_3d_polygon,
							   "draw_3d_polygon", "points");
		_hoops_HGGGS (state, &state->draw_dc_ellipse,
							   "draw_dc_ellipse", "ellipse");
		_hoops_HGGGS (state, &state->_hoops_CCISR,
							   "draw_dc_elliptical_arc", "elliptical arc");
		_hoops_HGGGS (state, &state->_hoops_SCISR,
							   "draw_dc_outline_ellipse", "ellipse");
		_hoops_HGGGS (state, &state->draw_dc_polyline,
							   "draw_dc_polyline", "points");
		_hoops_HGGGS (state, &state->draw_dc_face,
							   "draw_dc_face", "points");
		_hoops_HGGGS (state, &state->draw_dc_colorized_face,
							   "draw_dc_colorized_face", "points");
		_hoops_HGGGS (state, &state->draw_dc_rectangle,
							   "draw_dc_rectangle", "rectangle");
		_hoops_HGGGS (state, &state->draw_dc_polydot,
							   "draw_dc_polydot", "pixel");
		_hoops_HGGGS (state, &state->draw_dc_text,
							   "draw_dc_text", "characters");
		_hoops_HGGGS (state, &state->draw_overlay_list,
							   "draw_overlay_list", "list");
		_hoops_HGGGS (state, &state->_hoops_SCPGR,
							   "undraw_overlay_list", "list");
		_hoops_HGGGS (state, &state->draw_3d_polyedge,
							   "draw_3d_polyedge", "points");
		_hoops_HGGGS (state, &state->draw_3d_tristrip,
							   "draw_3d_tristrip", "vertices");
		_hoops_HGGGS (state, &state->_hoops_ASSSC,
							   "\ttristrip substrips", "vertices");
		_hoops_HGGGS (state, &state->draw_3d_polymarker,
							   "draw_3d_polymarker", "markers");
		_hoops_HGGGS (state, &state->draw_dc_polytriangle,
							   "draw_dc_triangle", "triangle");
		_hoops_HGGGS (state, &state->draw_dc_colorized_polytriangle,
							   "draw_dc_colorized_triangle", "triangle");
		_hoops_HGGGS (state, &state->draw_dc_gouraud_polytriangle,
							   "draw_dc_gouraud_triangle", "triangle");
		switch (dc->_hoops_PGCC._hoops_PIHSR) {
			case _hoops_SIHSR: {
				if (dc->_hoops_PGCC._hoops_AAPSR <= 256)
					_hoops_HGGGS (state, &state->_hoops_PSSSC,
										   "draw_dc_mapped8_rasters", "pixels");
				else
					_hoops_HGGGS (state, &state->_hoops_PSSSC,
										   "draw_dc_mapped16_rasters", "pixels");
			}	break;

			case _hoops_HIHSR: {
				_hoops_HGGGS (state, &state->_hoops_PSSSC,
									   "draw_dc_rgb32_rasters", "pixels");
			}	break;

			case _hoops_RIIHP: {
				_hoops_HGGGS (state, &state->_hoops_PSSSC,
									   "draw_dc_bit_rasters", "pixels");
			}	break;
		}
		_hoops_HGGGS (state, &state->_hoops_HSSSC,
								   "\traster rows", "rows");
		_hoops_HGGGS (state, &state->_hoops_IGSSP,
							   "create_frame_buffer", "creation");
		_hoops_HGGGS (state, &state->_hoops_CGSSP,
							   "display_frame_buffer", "pixels");
		_hoops_HGGGS (state, &state->_hoops_SGSSP,
							   "destroy_frame_buffer", "destruction");


		if (BIT (dc->options._hoops_IRARR, _hoops_PPSSC)) {
			fprintf (state->fp, "\n\t*** input handling ***\n");
			_hoops_IGGGS (state, &state->_hoops_HSCSP, "mouse");
			_hoops_IGGGS (state, &state->_hoops_ISCSP, "keyboard");
		}

		if (!BIT (dc->options._hoops_IRARR, _hoops_SPSSC)) {
			fprintf (state->fp, "\n\t*** test program coverage ***\n");
			_hoops_CGGGS (state, dc);
		}

		if (!state->_hoops_ICSSC)
			fclose (state->fp);
	}

	FREE (state, _hoops_HCSSC);
	dc->data = null;
}


/*
 * _hoops_SRAC
 */
local void init_update (
	Display_Context const		*dc) {
	_hoops_HCSSC alter				*state = _hoops_CSSSC (dc);

	if (state->fp != null)
		fprintf (state->fp, "\ninit_update\n");
}


/*
 * _hoops_SRAC
 */
local void finish_update (
	Display_Context const		*dc) {
	_hoops_HCSSC alter				*state = _hoops_CSSSC (dc);

	if (state->fp != null)
		fprintf (state->fp, "\nfinish_update\n");
}


/*
 * _hoops_SRAC
 */
local void init_picture (
	Net_Rendition const & nr) {
		Display_Context const		*dc = nr->_hoops_SRA;
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (!BIT(dc->flags, _hoops_SAISR)) return;

	if (state->fp != null) {

		fprintf (state->fp, "\ninit_picture\n");

		if (BIT (dc->options._hoops_IRARR, _hoops_AHSSC)) {
			if (dc->options._hoops_ARPSR)
				fprintf (state->fp, "\tlandscape orientation\n");
			else
				fprintf (state->fp, "\tno landscape orientation\n");

			fprintf (state->fp, "\tcurrent size = %.2f by %.2f cm\n",
					 dc->current.size.x,
					 dc->current.size.y);

			fprintf (state->fp, "\tcurrent number of pixels = %d by %d\n",
					 dc->current._hoops_PRPSR.x,
					 dc->current._hoops_PRPSR.y);
		}
	}

	/*
	 * _hoops_CRGH _hoops_SGGGS _hoops_III _hoops_GPP _hoops_SRS _hoops_AASA _hoops_RAS _hoops_IHPI _hoops_RPISR
	 */
	state->_hoops_CCSSC = false;
}


/*
 * _hoops_SRAC
 */
local void finish_picture (
	Net_Rendition const & nr,
	bool				swap_buffers) {
	Display_Context const		*dc = nr->_hoops_SRA;
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	UNREFERENCED (swap_buffers);

	if (!BIT(dc->flags, _hoops_SAISR)) return;

	if (state->fp != null) {
		fprintf (state->fp, "\nfinish_picture\n");
		fflush (state->fp);
	}
}


/*
 * _hoops_SRAC
 */
local POINTER_SIZED_INT get_outer_window (
	Display_Context const		*dc) {
	_hoops_HCSSC alter				*state = _hoops_CSSSC (dc);

	if (state->fp != null) {
		fprintf (state->fp, "\nget_outer_window\n");
		fprintf (state->fp, "\tleft	  = %d\n", dc->_hoops_RHPGA.left);
		fprintf (state->fp, "\tright  = %d\n", dc->_hoops_RHPGA.right);
		fprintf (state->fp, "\tbottom = %d\n", dc->_hoops_RHPGA.bottom);
		fprintf (state->fp, "\ttop	  = %d\n", dc->_hoops_RHPGA.top);
	}

	return (POINTER_SIZED_INT)state->fp;
}


/*
 * _hoops_SRAC
 */
local void free_outer_window (
	Display_Context const		*dc) {
	_hoops_HCSSC alter				*state = _hoops_CSSSC (dc);

	if (state->fp != null)
		fprintf (state->fp, "\nfree_outer_window\n");
}


/*
 * _hoops_SRAC
 */
local void _hoops_RSCSP (
	Display_Context const		*dc) {
	_hoops_HCSSC alter				*state = _hoops_CSSSC (dc);

	if (state->fp != null) {
		fprintf (state->fp, "\nresize_outer_window\n");
		fprintf (state->fp, "\tleft	  = %d\n", dc->_hoops_RHPGA.left);
		fprintf (state->fp, "\tright  = %d\n", dc->_hoops_RHPGA.right);
		fprintf (state->fp, "\tbottom = %d\n", dc->_hoops_RHPGA.bottom);
		fprintf (state->fp, "\ttop	  = %d\n", dc->_hoops_RHPGA.top);
	}
}


/*
 * _hoops_PGAA
 */
local char const *_hoops_RSHPP (
	char alter						*_hoops_ASAPR,
	Driver_Color const			*color,
	Display_Context const		*dc) {

	switch (dc->_hoops_PGCC._hoops_PIHSR) {
		case _hoops_SIHSR: {
			Sprintf_D (_hoops_ASAPR, "index %d", color->_hoops_PGGCR);
		}	break;

		case _hoops_HIHSR: {
			char	buffer[64];

			Sprintf_DD (buffer, "(r=%d, g=%d,",
						color->_hoops_HRIR.r,
						color->_hoops_HRIR.g);
			Sprintf_SD (_hoops_ASAPR, "%s b=%d)", buffer, color->_hoops_HRIR.b);
		}	break;

		case _hoops_RIIHP: {
			Sprintf_D (_hoops_ASAPR, "gray level %d", (int)color->_hoops_PIHHP);
		}	break;

		default: {
			Sprintf_D (_hoops_ASAPR, "** Unknown color system (%d)",
					   dc->_hoops_PGCC._hoops_PIHSR);
		}	break;
	}
	return _hoops_ASAPR;
}


/*
 * _hoops_PGAA
 */
local char const *_hoops_ACASR (
	char alter		*_hoops_ASAPR,
	RGBAS32 const	*color) {
	char			buffer[64];

	Sprintf_DD (buffer, "(r=%d, g=%d,", color->r, color->g);
	Sprintf_SD (_hoops_ASAPR, "%s b=%d)", buffer, color->b);
	return _hoops_ASAPR;
}


/*
 * _hoops_PGAA
 */
local void _hoops_GRGGS (
	_hoops_HCSSC const		*state,
	_hoops_HRPA const		*matrix) {
	int						row;

	fprintf (state->fp, "\t\t\tContents: (");
	if (BIT (matrix->_hoops_RAGR, _hoops_GRICR))
		fprintf (state->fp, "Rotation ");
	if (BIT (matrix->_hoops_RAGR, _hoops_CHCP))
		fprintf (state->fp, "Scale ");
	if (BIT (matrix->_hoops_RAGR, _hoops_PRICR))
		fprintf (state->fp, "Translation ");
	if (BIT (matrix->_hoops_RAGR, _hoops_HRICR))
		fprintf (state->fp, "Perspective ");
	if (BIT (matrix->_hoops_RAGR, _hoops_RRICR))
		fprintf (state->fp, "3D ");
	fprintf (state->fp, ")\n");

	fprintf (state->fp,
			 "\t\t\tSymmetric scale = %f\n", matrix->_hoops_CPH);

	fprintf (state->fp, "\t\t\tElements:\n");
	for (row = 0; row < 4; ++row)
		fprintf (state->fp, "\t\t\t[%10.4f %10.4f %10.4f %10.4f]\n",
				 matrix->elements[row][0],
				 matrix->elements[row][1],
				 matrix->elements[row][2],
				 matrix->elements[row][3]);

	if (matrix->_hoops_APRA != null) {
		fprintf (state->fp, "\t\t\tAdjoint is valid:\n");
		for (row = 0; row < 4; ++row)
			fprintf (state->fp, "\t\t\t[%10.4f %10.4f %10.4f %10.4f]\n",
					 matrix->_hoops_APRA->data.elements[row][0],
					 matrix->_hoops_APRA->data.elements[row][1],
					 matrix->_hoops_APRA->data.elements[row][2],
					 matrix->_hoops_APRA->data.elements[row][3]);
	}
}


/*
 * _hoops_PGAA
 */
#define _hoops_RRGGS true
#define _hoops_ARGGS false
local void _hoops_PRGGS (
	Net_Rendition const &		nr,
	bool						_hoops_HRGGS) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_HCSSC alter *		state = _hoops_CSSSC (dc);

	/* _hoops_RGHH _hoops_HHH _hoops_IRGGS */
	state->transform._hoops_SSAC =
		(_hoops_HRGGS ? ~_hoops_IHCR->_hoops_CPA : _hoops_IHCR->_hoops_CPA);
	state->transform._hoops_CCCIR++;

	/* _hoops_IPIHR _hoops_RH _hoops_ACSP _hoops_RPP _hoops_IPSP _hoops_APSI _hoops_PIRC _hoops_IIGR _hoops_SCH */
	if (state->fp == null)
		return;

	fprintf (state->fp, "\tnew %s transform rendition: %d\n",
			 _hoops_HRGGS ? "3D" : "DC", _hoops_IHCR->_hoops_CPA);

	if (BIT (dc->options._hoops_IRARR, _hoops_CASSC)) {
		fprintf (state->fp, "\t\t(transformation) matrix:\n");
		_hoops_GRGGS (state, &_hoops_IHCR->matrix->data);

		fprintf (state->fp, "\t\ttransform type = %d\n", _hoops_IHCR->_hoops_HGSC);
	}

	if (_hoops_HRGGS) {
		fprintf (state->fp, "\t\tflags:\n");
		if (BIT (_hoops_IHCR->flags, _hoops_PRIR))
			fprintf (state->fp, "\t\t\twith hardware lighting\n");
		if (BIT (_hoops_IHCR->flags, _hoops_GRHH))
			fprintf (state->fp, "\t\t\twith lighting\n");
		if (BIT (_hoops_IHCR->flags, _hoops_GSIHP))
			fprintf (state->fp, "\t\t\twith 3D modelling\n");
		if (BIT (_hoops_IHCR->flags, _hoops_PGCH))
			fprintf (state->fp, "\t\t\twith right handed world\n");

		if (BIT (_hoops_IHCR->flags, _hoops_PRAIP))
			fprintf (state->fp, "\t\t\twith matrix includes screen\n");
		if (BIT (_hoops_IHCR->flags, _hoops_IGCC))
			fprintf (state->fp, "\t\t\twith world to screen matrix valid\n");
		if (BIT (_hoops_IHCR->flags, _hoops_AIPHP))
			fprintf (state->fp, "\t\t\twith matrix includes modelling\n");
		if (BIT (_hoops_IHCR->flags, _hoops_IGSP))
			fprintf (state->fp, "\t\t\twith request to cull\n");

		if (BIT (_hoops_IHCR->flags, _hoops_RCRIP))
			fprintf (state->fp, "\t\t\twith hardware cutting planes\n");
		if (BIT (_hoops_IHCR->flags, _hoops_CSP))
			fprintf (state->fp, "\t\t\twith cutting planes\n");
		if (BIT (_hoops_IHCR->flags, _hoops_HHGGA))
			fprintf (state->fp, "\t\t\twith DC cutting planes set\n");

		if (BIT (_hoops_IHCR->flags, _hoops_GSASP))
			fprintf (state->fp, "\t\t\twith sort hidden by Y min\n");
		if (BIT (_hoops_IHCR->flags, TR_SORT_HIDDEN_BY_PRIORITY))
			fprintf (state->fp, "\t\t\twith sort hidden by priority\n");
		if (BIT (_hoops_IHCR->flags, _hoops_RSASP))
			fprintf (state->fp, "\t\t\twith sort hidden mask\n");

		if (BIT (_hoops_IHCR->flags, _hoops_CGHIP))
			fprintf (state->fp, "\t\t\twith clip is nonnull\n");
		if (BIT (_hoops_IHCR->flags, _hoops_ASPIP))
			fprintf (state->fp, "\t\t\twith clip is full\n");

		if (BIT (_hoops_IHCR->flags, _hoops_AIHS))
			fprintf (state->fp, "\t\t\twith clipping not needed\n");
	}

	if (BIT(_hoops_IHCR->flags, _hoops_PASP))
		fprintf (state->fp,
				 "\t\tZ buffering is active (max = %.4f, face displacement = %.4f)\n",
				 _hoops_IHCR->_hoops_PCHH,
				 _hoops_IHCR->_hoops_CHIH);

	if (_hoops_HRGGS) {
		fprintf (state->fp, "\t\tcamera position = (%.4f, %.4f, %.4f)\n",
				 _hoops_IHCR->_hoops_SPH->position.x,
				 _hoops_IHCR->_hoops_SPH->position.y,
				 _hoops_IHCR->_hoops_SPH->position.z);
		fprintf (state->fp, "\t\tcamera target = (%.4f, %.4f, %.4f)\n",
				 _hoops_IHCR->_hoops_SPH->target.x,
				 _hoops_IHCR->_hoops_SPH->target.y,
				 _hoops_IHCR->_hoops_SPH->target.z);
		fprintf (state->fp, "\t\tcamera up vector = (%.4f, %.4f, %.4f)\n",
				 _hoops_IHCR->_hoops_SPH->up_vector.x,
				 _hoops_IHCR->_hoops_SPH->up_vector.y,
				 _hoops_IHCR->_hoops_SPH->up_vector.z);

		fprintf (state->fp, "\t\tcamera positioning matrix:\n");
		_hoops_GRGGS (state, &_hoops_IHCR->_hoops_SPH->_hoops_PRPA);

		fprintf (state->fp, "\t\tcamera projection matrix:\n");
		_hoops_GRGGS (state, &_hoops_IHCR->_hoops_SPH->_hoops_AIIH);

		fprintf (state->fp, "\t\tcamera complete matrix:\n");
		_hoops_GRGGS (state, &_hoops_IHCR->_hoops_SPH->_hoops_GRCC);
	}

	if (BIT (dc->options._hoops_IRARR, _hoops_CASSC)) {
		fprintf (state->fp, "\t\tsoft clip = (%.4f, %.4f, %.4f, %.4f)\n",
				 nr->_hoops_SAIR->_hoops_HHCAR.left,
				 nr->_hoops_SAIR->_hoops_HHCAR.right,
				 nr->_hoops_SAIR->_hoops_HHCAR.bottom,
				 nr->_hoops_SAIR->_hoops_HHCAR.top);
	}

	fprintf (state->fp, "\t\thard clip = (%d, %d, %d, %d)\n",
			 _hoops_IHCR->_hoops_AGAA.left,
			 _hoops_IHCR->_hoops_AGAA.right,
			 _hoops_IHCR->_hoops_AGAA.bottom,
			 _hoops_IHCR->_hoops_AGAA.top);

	if (BIT (dc->options._hoops_IRARR, _hoops_CASSC)) {
		fprintf (state->fp,
				 "\t\tunframed hard clip = (%d, %d, %d, %d)\n",
				 _hoops_IHCR->_hoops_RGPSP.left,
				 _hoops_IHCR->_hoops_RGPSP.right,
				 _hoops_IHCR->_hoops_RGPSP.bottom,
				 _hoops_IHCR->_hoops_RGPSP.top);
	}

	if (BIT (dc->options._hoops_IRARR, _hoops_CASSC)) {
		fprintf (state->fp, "\t\theuristics:\n");
		if (BIT (_hoops_IHCR->heuristics, _hoops_PICAR))
			fprintf (state->fp, "\t\t\thas clipping\n");
		if (BIT (_hoops_IHCR->heuristics, _hoops_IGIRP))
			fprintf (state->fp, "\t\t\thas transformations\n");
		if (BIT (_hoops_IHCR->heuristics, _hoops_CGIRP))
			fprintf (state->fp, "\t\t\thas intersecting polygons\n");
		if (BIT (_hoops_IHCR->heuristics, _hoops_SGIRP))
			fprintf (state->fp, "\t\t\thas backplane cull\n");
		if (BIT (_hoops_IHCR->heuristics, _hoops_CGCS))
			fprintf (state->fp, "\t\t\thas concave polygons\n");
		if (BIT (_hoops_IHCR->heuristics, _hoops_GRIRP))
			fprintf (state->fp, "\t\t\thas polygon crossings\n");
		if (BIT (_hoops_IHCR->heuristics, _hoops_SASA))
			fprintf (state->fp, "\t\t\thas right handed polygons only\n");
		if (BIT (_hoops_IHCR->heuristics, _hoops_GPSA))
			fprintf (state->fp, "\t\t\thas left handed polygons only\n");
		if (BIT (_hoops_IHCR->heuristics, _hoops_RRIRP))
			fprintf (state->fp, "\t\t\thas incremental updates\n");
		if (BIT (_hoops_IHCR->heuristics, _hoops_IRI))
			fprintf (state->fp, "\t\t\thas hidden surfaces\n");
		if (BIT (_hoops_IHCR->heuristics, _hoops_HRIRP)) {
			_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;

			fprintf (state->fp,
					 "\t\t\thas overlay (quick moves) on top of %s\n",
					 _hoops_RSHPP (state->buf, &_hoops_SGRA->_hoops_GPIR, dc));
		}
		if (BIT (_hoops_IHCR->heuristics, _hoops_PRIRP))
			fprintf (state->fp, "\t\t\thas partial erase\n");
		if (BIT (_hoops_IHCR->heuristics, _hoops_SICIA))
			fprintf (state->fp, "\t\t\thas related selection limit\n");
	}
	else
		/* _hoops_HHGC _hoops_IS _hoops_ACPA _hoops_AHCA _hoops_HHCI _hoops_IHCI _hoops_HCR _hoops_RH _hoops_GHIR */
		if (BIT (_hoops_IHCR->heuristics, _hoops_HRIRP)) {
			_hoops_CGRA const &		_hoops_SGRA = nr->_hoops_SAIR;

			fprintf (state->fp, "\t\theuristics:\n");
			fprintf (state->fp,
					 "\t\t\thas overlay (quick moves) on top of %s\n",
					 _hoops_RSHPP (state->buf, &_hoops_SGRA->_hoops_GPIR, dc));
		}

	if (_hoops_HRGGS) {
		fprintf (state->fp, "\t\tnet modelling matrix:\n");
		_hoops_GRGGS (state, &_hoops_IHCR->_hoops_IPH->data);

		if (BIT (_hoops_IHCR->flags, _hoops_IGCC)) {
			fprintf (state->fp, "\t\tworld to screen matrix:\n");
			_hoops_GRGGS (state, &_hoops_IHCR->_hoops_CGCC->data);
		}
	}

	/* _hoops_AHCR _hoops_AHPA _hoops_PPR _hoops_HSP _hoops_ISP _hoops_AIAH _hoops_CPHR _hoops_CCA _hoops_AHCR _hoops_RHGPR */

	if (BIT (dc->options._hoops_IRARR, _hoops_CASSC) && _hoops_HRGGS)
		if (_hoops_IHCR->_hoops_RGH != null)
			fprintf (state->fp, "\t\tcutting plane count = %d\n",
					 _hoops_IHCR->_hoops_RGH->_hoops_PGH);
}


/*
 * _hoops_PGAA
 */
local void _hoops_CRGGS (
	_hoops_HHSSC alter *r) {

	/* _hoops_PHIGR _hoops_GPISR _hoops_IIGR _hoops_CRAPH _hoops_IH _hoops_GII _hoops_GPRR _hoops_IIGR _hoops_IPP */
	r->_hoops_GRHPR++;
}


/*
 * _hoops_PGAA
 */
local void _hoops_SRGGS (
	_hoops_HCSSC alter			*state,
	Display_Context const		*dc,
	_hoops_HHA const &	_hoops_ISHIR) {

	fprintf (state->fp, "\t\tnew material rendition: %d\n",
			 _hoops_ISHIR->_hoops_CPA);

	if (BIT (dc->options._hoops_IRARR, _hoops_CASSC)) {
		if (_hoops_ISHIR->_hoops_SCA)
			fprintf (state->fp, "\t\t\tdiffuse textures address = %p\n",
					 (void*)_hoops_ISHIR->_hoops_SCA->texture);
		else
			fprintf (state->fp, "\t\t\tno diffuse texture\n");

		fprintf (state->fp, "\t\t\tspecular texture address = %p\n",
				 (void*)_hoops_ISHIR->texture[_hoops_HIA]);

		fprintf (state->fp, "\t\t\tmirror texture address = %p\n",
				 (void*)_hoops_ISHIR->texture[_hoops_ACA]);

		fprintf (state->fp, "\t\t\ttransmission texture address = %p\n",
				 (void*)_hoops_ISHIR->texture[_hoops_PCA]);

		fprintf (state->fp, "\t\t\tbump texture address = %p\n",
				 (void*)_hoops_ISHIR->texture[_hoops_IIA]);

		fprintf (state->fp, "\t\t\tenvironment texture address = %p\n",
				 (void*)_hoops_ISHIR->texture[_hoops_RIA]);
	}

	fprintf (state->fp, "\t\t\tdiffuse = (r=%.4f, g=%.4f, b=%.4f)\n",
			 _hoops_ISHIR->_hoops_CSHR.red,
			 _hoops_ISHIR->_hoops_CSHR.green,
			 _hoops_ISHIR->_hoops_CSHR.blue);

	fprintf (state->fp, "\t\t\tspecular = (r=%.4f, g=%.4f, b=%.4f)\n",
			 _hoops_ISHIR->color[_hoops_HIA].red,
			 _hoops_ISHIR->color[_hoops_HIA].green,
			 _hoops_ISHIR->color[_hoops_HIA].blue);

	fprintf (state->fp, "\t\t\tmirror = (r=%.4f, g=%.4f, b=%.4f)\n",
			 _hoops_ISHIR->color[_hoops_ACA].red,
			 _hoops_ISHIR->color[_hoops_ACA].green,
			 _hoops_ISHIR->color[_hoops_ACA].blue);

	fprintf (state->fp, "\t\t\ttransmission = (r=%.4f, g=%.4f, b=%.4f)\n",
			 _hoops_ISHIR->color[_hoops_PCA].red,
			 _hoops_ISHIR->color[_hoops_PCA].green,
			 _hoops_ISHIR->color[_hoops_PCA].blue);

	fprintf (state->fp, "\t\t\topacity = %.4f\n", _hoops_ISHIR->_hoops_IRIR);

	fprintf (state->fp, "\t\t\tgloss = %.4f\n", _hoops_ISHIR->gloss);

	fprintf (state->fp, "\t\t\tindex of refraction = %.4f\n",
			 _hoops_ISHIR->_hoops_PAGRA);
}


/*
 * _hoops_PGAA
 */
local void _hoops_GAGGS (
	_hoops_HCSSC alter				*state,
	Display_Context const		*dc,
	_hoops_SIHHP const		*_hoops_PGPH) {

	fprintf (state->fp, "\t\tnew user face pattern: %d\n",
			 _hoops_PGPH->_hoops_CPA);

	if (BIT (dc->options._hoops_IRARR, _hoops_CASSC))
		fprintf (state->fp, "\t\t\tpattern address = %p\n",
				 _hoops_PGPH->pattern);

	fprintf (state->fp, "\t\t\theight = %d\n", _hoops_PGPH->height);

	fprintf (state->fp, "\t\t\twidth = %d\n", _hoops_PGPH->width);

	fprintf (state->fp, "\t\t\ttop_to_bottom = %d\n",
			 _hoops_PGPH->_hoops_RCHHP);

	fprintf (state->fp, "\t\t\tsee_through = %d\n", _hoops_PGPH->_hoops_ACHHP);

	if (BIT (dc->options._hoops_IRARR, _hoops_CASSC))
		fprintf (state->fp, "\t\t\tutility = %d\n", _hoops_PGPH->_hoops_HSAI);
}


/*
 * _hoops_PGAA
 */
local void _hoops_RAGGS (
	_hoops_HCSSC alter *		state,
	Display_Context const *		dc,
	_hoops_PC const &		light) {
	_hoops_AS const *		current;
	int							i;
	UNREFERENCED(dc);

	fprintf (state->fp, "\t\tlight rendition: %d\n", light->_hoops_CPA);

	current = light->_hoops_CGR;
	for (i = 0; i < light->count; i++) {
		fprintf (state->fp, "\t\t\ttype = %d\n", current->_hoops_PRR);
		fprintf (state->fp, "\t\t\t\tcolor = (r=%.4f, g=%.4f, b=%.4f)\n",
				 current->color.red,
				 current->color.green,
				 current->color.blue);
		fprintf (state->fp, "\t\t\t\tposition = (%.4f, %.4f, %.4f)\n",
				 current->position.x,
				 current->position.y,
				 current->position.z);
		fprintf (state->fp, "\t\t\t\ttarget = (%.4f, %.4f, %.4f)\n",
				 current->target.x,
				 current->target.y,
				 current->target.z);
		fprintf (state->fp, "\t\t\t\tdirection = (%.4f, %.4f, %.4f)\n",
				 current->direction.x,
				 current->direction.y,
				 current->direction.z);
		current = current->next;
	}

	fprintf (state->fp, "\t\t\tscale = %.4f\n", light->scale);

	fprintf (state->fp, "\t\t\tcount = %d\n", light->count);

	fprintf (state->fp, "\t\t\tcompute light requires XYZ = %s\n",
			 light->_hoops_ISPHP ? "true" : "false");
}

/*
 * _hoops_PGAA
 */
local void _hoops_AAGGS (
	_hoops_HCSSC alter *		state,
	Display_Context const *		dc,
	_hoops_HHA const &	_hoops_HSIHP,
	_hoops_PC				_hoops_PAGGS) {
	UNREFERENCED(dc);

	if (_hoops_HSIHP == null) {
		if (state->_hoops_SCSSC != (_hoops_GARRR)0) {
			fprintf (state->fp, "\t\tmaterial rendition *canceled*\n");
			state->_hoops_SCSSC = (_hoops_GARRR)0;
		}
	}
	else if (state->_hoops_SCSSC != _hoops_HSIHP->_hoops_CPA) {
		_hoops_SRGGS (state, dc, _hoops_HSIHP);
		state->_hoops_SCSSC = _hoops_HSIHP->_hoops_CPA;
	}

	if (_hoops_PAGGS == null) {
		if (state->_hoops_RSSSC != (_hoops_GARRR)0) {
			fprintf (state->fp, "\t\tlight rendition *canceled*\n");
			state->_hoops_RSSSC = (_hoops_GARRR)0;
		}
	}
	else if (state->_hoops_RSSSC != _hoops_PAGGS->_hoops_CPA) {
		_hoops_RAGGS (state, dc, _hoops_PAGGS);
		state->_hoops_RSSSC = _hoops_PAGGS->_hoops_CPA;
	}
}


/*
 * _hoops_PGAA
 */
local char const *_hoops_HAGGS (
	int				pattern) {
	char const		*_hoops_ASAPR;

	switch (pattern) {
		case FP_SOLID:
			_hoops_ASAPR = "SOLID";
			break;
		case FP_CHECKERBOARD:
			_hoops_ASAPR = "CHECKERBOARD";
			break;
		case FP_CROSSHATCH:
			_hoops_ASAPR = "CROSSHATCH";
			break;
		case FP_DIAMONDS:
			_hoops_ASAPR = "DIAMONDS";
			break;
		case FP_HORIZONTAL_BARS:
			_hoops_ASAPR = "HORIZONTAL BARS";
			break;
		case FP_SLANT_LEFT:
			_hoops_ASAPR = "SLANT LEFT";
			break;
		case FP_SLANT_RIGHT:
			_hoops_ASAPR = "SLANT RIGHT";
			break;
		case FP_SQUARE_DOTS:
			_hoops_ASAPR = "SQUARE DOTS";
			break;
		case FP_USER_DEFINED:
			_hoops_ASAPR = "USER DEFINED";
			break;
		case FP_VERTICAL_BARS:
			_hoops_ASAPR = "VERTICAL BARS";
			break;
		case FP_WINDOW_CHECKERBOARD:
			_hoops_ASAPR = "WINDOW CHECKERBOARD";
			break;
		case FP_WINDOW_CROSSHATCH:
			_hoops_ASAPR = "WINDOW CROSSHATCH";
			break;
		case FP_WINDOW_DIAMONDS:
			_hoops_ASAPR = "WINDOW DIAMONDS";
			break;
		case FP_WINDOW_HORIZONTAL_BARS:
			_hoops_ASAPR = "WINDOW HORIZONTAL BARS";
			break;
		case FP_WINDOW_SLANT_LEFT:
			_hoops_ASAPR = "WINDOW SLANT LEFT";
			break;
		case FP_WINDOW_SLANT_RIGHT:
			_hoops_ASAPR = "WINDOW SLANT RIGHT";
			break;
		case FP_WINDOW_SQUARE_DOTS:
			_hoops_ASAPR = "WINDOW SQUARE DOTS";
			break;
		case FP_WINDOW_VERTICAL_BARS:
			_hoops_ASAPR = "WINDOW VERTICAL BARS";
			break;
		default:
			_hoops_ASAPR = "** Unrecognized **";
			break;
	}
	return _hoops_ASAPR;
}



/*
 * _hoops_PGAA
 */
local void _hoops_IAGGS (
	Net_Rendition const &		nr) {
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HCSSC alter *		state = _hoops_CSSSC (dc);

	/* _hoops_RGHH _hoops_HHH _hoops_IRGGS */
	state->face._hoops_SSAC = _hoops_SIGA->_hoops_CPA;
	state->face._hoops_CCCIR++;
	if (_hoops_SIGA->color == state->face.color)
		state->face._hoops_IHSSC++;
	else {
		state->face._hoops_CCASR++;
		state->face.color = _hoops_SIGA->color;
	}
	if (_hoops_SIGA->contrast_color == state->face.contrast_color)
		state->face._hoops_CHSSC++;
	else {
		state->face._hoops_SHSSC++;
		state->face.contrast_color = _hoops_SIGA->contrast_color;
	}
	if (_hoops_SIGA->pattern == state->face.pattern)
		state->face._hoops_GISSC++;
	else {
		state->face._hoops_RISSC++;
		state->face.pattern = _hoops_SIGA->pattern;
	}

	/* _hoops_IPIHR _hoops_RH _hoops_ACSP _hoops_RPP _hoops_IPSP _hoops_APSI _hoops_PIRC _hoops_IIGR _hoops_SCH */
	if (state->fp != null) {
		fprintf (state->fp, "\tnew face rendition: %d\n", _hoops_SIGA->_hoops_CPA);

		fprintf (state->fp, "\t\tcolor = %s\n",
				 _hoops_RSHPP (state->buf,
							 &_hoops_SIGA->color,
							 nr->_hoops_SRA));

		if (_hoops_SIGA->pattern != FP_SOLID)
			fprintf (state->fp, "\t\tcontrast color = %s\n",
					 _hoops_RSHPP (state->buf,
								 &_hoops_SIGA->contrast_color,
								 nr->_hoops_SRA));

		/* _hoops_SSPC _hoops_CAGGS */

		/* _hoops_SSPC _hoops_PSHAR */

		if (BIT (dc->options._hoops_IRARR, _hoops_RPSSC))
			_hoops_AAGGS (state, dc,
									  _hoops_SIGA->_hoops_CHA,
									  _hoops_SIGA->_hoops_AGP);

		fprintf (state->fp, "\t\tpattern = %s\n",
				 _hoops_HAGGS (_hoops_SIGA->pattern));

		if (_hoops_SIGA->pattern == FP_USER_DEFINED) {
			_hoops_SIHHP const		*up = _hoops_SIGA->_hoops_PGPH;

			if (state->_hoops_GSSSC != up->_hoops_CPA) {
				_hoops_GAGGS (state, dc, up);
				state->_hoops_GSSSC = up->_hoops_CPA;
			}
		}
	}
}


/*
 * _hoops_PGAA
 */
local void _hoops_AIHSC (
	Net_Rendition const & nr,
	Line_Rendition const &	_hoops_HC) {
	Display_Context const		*dc = nr->_hoops_SRA;
	_hoops_HCSSC alter				*state = _hoops_CSSSC (dc);

	/* _hoops_RGHH _hoops_HHH _hoops_IRGGS */
	state->line._hoops_SSAC = _hoops_HC->_hoops_CPA;
	state->line._hoops_CCCIR++;
	if (_hoops_HC->color == state->line.color)
		state->line._hoops_IHSSC++;
	else {
		state->line._hoops_CCASR++;
		state->line.color = _hoops_HC->color;
	}
	if (_hoops_HC->line_style == state->line.line_style)
		state->line._hoops_GISSC++;
	else {
		state->line._hoops_RISSC++;
		state->line.line_style = _hoops_HC->line_style;
	}
	if (_hoops_HC->weight == state->line.weight)
		state->line._hoops_AISSC++;
	else {
		state->line._hoops_PISSC++;
		state->line.weight = _hoops_HC->weight;
	}
	if (_hoops_HC->style == state->line.style)
		state->line._hoops_HISSC++;
	else {
		state->line._hoops_IISSC++;
		state->line.style = _hoops_HC->style;
	}

	/* _hoops_IPIHR _hoops_RH _hoops_ACSP _hoops_RPP _hoops_IPSP _hoops_APSI _hoops_PIRC _hoops_IIGR _hoops_SCH */
	if (state->fp != null) {
		char const		*pattern;
		int				temp;

		fprintf (state->fp, "\tnew line rendition: %d\n", _hoops_HC->_hoops_CPA);

		fprintf (state->fp, "\t\tcolor = %s\n",
				 _hoops_RSHPP (state->buf,
							 &_hoops_HC->color,
							 nr->_hoops_SRA));

		if (BIT (dc->options._hoops_IRARR, _hoops_RPSSC))
			_hoops_AAGGS (state, dc,
									  _hoops_HC->_hoops_CHA,
									  _hoops_HC->_hoops_AGP);

		if (_hoops_HC->line_style->name.text)
			fprintf (state->fp, "\t\tpattern = %s\n", _hoops_HC->line_style->name.text);
		else
			fprintf (state->fp, "\t\tpattern = ** Unrecognized **\n");

		fprintf (state->fp, "\t\tstyle = %d\n", _hoops_HC->style);
		temp = _hoops_HC->style & LJOIN_MASK;
		switch (temp) {
			case LJOIN_ROUND: {
				pattern = "ROUND";
			}	break;
			case LJOIN_BEVEL: {
				pattern = "BEVEL";
			}	break;
			case LJOIN_MITER: {
				pattern = "MITER";
			}	break;
			default: {
				pattern = "** Unrecognized **";
			}
		}
		fprintf (state->fp, "\t\t\tjoin = %s\n", pattern);
		temp = _hoops_HC->style & LCAP_MASK;
		switch (temp) {
			case LCAP_BUTT: {
				pattern = "BUTT";
			}	break;
			case LCAP_ROUND: {
				pattern = "ROUND";
			}	break;
			case LCAP_SQUARE: {
				pattern = "SQUARE";
			}	break;
			default: {
				pattern = "** Unrecognized **";
			}
		}
		fprintf (state->fp, "\t\t\tcap = %s\n", pattern);

		fprintf (state->fp, "\t\tweight = %d\n", (int)_hoops_HC->weight);

		/* _hoops_SSPC _hoops_GGCS _hoops_CRS */
	}
}


/*
 * _hoops_PGAA
 */
local void _hoops_SAGGS (
	FILE alter *				fp,
	int							count,
	DC_Point const *			points,
	Net_Rendition const &		nr,
	char const *				_hoops_RHSRR) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	int							i;
	bool						_hoops_GPGGS,
								_hoops_RPGGS;

	/* _hoops_RGSPR _hoops_III */
	if (count == 0) {
		fprintf (fp, "\t(no %s!)\n", _hoops_RHSRR);
		return;
	}
	else if (count == 1)
		fprintf (fp, "\t%s %s = ",
				 (BIT(_hoops_IHCR->flags, _hoops_PASP) ? "Z-buffered" : "non-Z-buffered"),
				 _hoops_RHSRR);
	else
		fprintf (fp, "\t%d %s %s:\n\t\t",
				 count,
				 (BIT(_hoops_IHCR->flags, _hoops_PASP) ? "Z-buffered" : "non-Z-buffered"),
				 _hoops_RHSRR);

	/* _hoops_RIHRR _hoops_RSSA (2 _hoops_RIR _hoops_III) */
	_hoops_GPGGS = _hoops_RPGGS = false;
	for (i = 0; i < count - 1; i++) {
		fprintf (fp, "(%.4f, %.4f, %.4f) - ",
				 points[i].x, points[i].y, points[i].z);
		if (points[i].z != 0.0f) {
			_hoops_GPGGS = true;
			if (points[i].z > _hoops_IHCR->_hoops_PCHH)
				_hoops_RPGGS = true;
		}
		if (i % 2 == 1) {
			fprintf (fp, "\n\t\t");
		}
	}
	fprintf (fp,
			 "(%.4f, %.4f, %.4f)\n",
			 points[i].x, points[i].y, points[i].z);

	/* _hoops_GRH _hoops_IPAC */
	if (BIT(_hoops_IHCR->flags, _hoops_PASP)) {
		if (_hoops_RPGGS)
			fprintf (fp,
					 "\t\t(Z value exceeds transform rendition Z buffer max)\n");
	}
	else {
		if (_hoops_GPGGS)
			fprintf (fp,
					 "\t\t(Nonzero Z value although HOOPS is not Z buffering)\n");
	}
}


/*
 * _hoops_PGAA
 */
local void _hoops_APGGS (
	_hoops_GCSSC alter	*g,
	long					count) {

	/* _hoops_PHIGR _hoops_GPISR _hoops_IIGR _hoops_CRAPH _hoops_IH _hoops_GII _hoops_GPRR _hoops_IIGR _hoops_IPP */
	g->_hoops_RCSSC++;
	g->points += count;
}


/*
 * _hoops_SRAC
 */
local void _hoops_IGSSP (
	Net_Rendition const & nr,
	int						width,
	int						height,
	Image_Format			format,
	Image alter * alter  *image,
	void alter * alter	   *_hoops_PISCP) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (format == Image_MAPPED_8 ||
		format == Image_MAPPED_16 ||
		format == _hoops_HHGH ||
		format == Image_RGBA32 ||
		format == _hoops_HRSRH ||
		format == _hoops_CSGSP) {
		_hoops_PCSSC alter		*_hoops_PPGGS;
		int						row_bytes;

		if (state->fp != null) {
			fprintf (state->fp, "\ncreate_frame_buffer\n");

			_hoops_APGGS (&state->_hoops_IGSSP, 1L);
		}

		/* _hoops_CCPP _hoops_RAPR _hoops_IH _hoops_RH _hoops_IRRPA, _hoops_HAS._hoops_IAS. _hoops_RGPP, 4 _hoops_GCSRR */
		row_bytes = width * sizeof (RGBAS32);
		ALLOC (_hoops_PPGGS, _hoops_PCSSC);
		_hoops_PPGGS->size = height * row_bytes;
		ALLOC_ARRAY (_hoops_PPGGS->data, _hoops_PPGGS->size, unsigned char);
		SET_MEMORY (_hoops_PPGGS->data, _hoops_PPGGS->size, 0xFF);

		/* _hoops_GSRS _hoops_AGAH _hoops_CCA _hoops_RH _hoops_CRS _hoops_IS _hoops_RH _hoops_SRHR */
		HI_Create_Image (image,
						 null,
						 width, height,
						 format, row_bytes,
						 _hoops_IGPGI,
						 _hoops_PPGGS->data);

		HI_Validate_Inverted_Rasters (*image);
		*_hoops_PISCP = _hoops_PPGGS;
	}
	else
		HD_Std_Create_Frame_Buffer (nr, width, height, format, image,
									_hoops_PISCP);
}


/*
 * _hoops_SRAC
 */
local void _hoops_SGSSP (
	Net_Rendition const & nr,
	Image alter			*image,
	void alter				*_hoops_PISCP) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (_hoops_PISCP == null)
		/* _hoops_SCH _hoops_RSAS'_hoops_RA _hoops_CARS */
		HD_Std_Destroy_Frame_Buffer (nr, image, _hoops_PISCP);
	else {
		_hoops_PCSSC alter		*_hoops_PPGGS;

		if (state->fp != null) {
			fprintf (state->fp, "\ndestroy_frame_buffer\n");

			_hoops_APGGS (&state->_hoops_SGSSP, 1L);
		}

		_hoops_PPGGS = (_hoops_PCSSC *)_hoops_PISCP;
		FREE_ARRAY (_hoops_PPGGS->data, _hoops_PPGGS->size, unsigned char);
		FREE (_hoops_PPGGS, _hoops_PCSSC);
		_hoops_HPRH (image);
	}
}


/*
 * _hoops_SRAC
 */
local void _hoops_CGSSP (
	Net_Rendition const & nr,
	DC_Point const	   *start,
	DC_Point const	   *end,
	Image const			*image,
	int						hoffset,
	int						voffset,
	void const				*_hoops_PISCP) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	UNREFERENCED(_hoops_PISCP);

	if (state->fp != null) {
		int								width,
												height,
												row_bytes;
		Display_Context const *dc = nr->_hoops_SRA;

		width  = (int)end->x - (int)start->x + 1;
		height = (int)start->y - (int)end->y + 1;

		fprintf (state->fp,
				 "\ndisplay_frame_buffer (%d rows, %d pixels per row)\n",
				 height, width);

		if (nr->transform_rendition->_hoops_CPA != state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_ARGGS);
		else
			_hoops_CRGGS (&state->transform);

		_hoops_SAGGS (state->fp, 1, start, nr, "start");
		_hoops_SAGGS (state->fp, 1, end, nr, "end");
		_hoops_APGGS (&state->_hoops_CGSSP, (long)width * (long)height);

		row_bytes = image->row_bytes;

		switch (dc->_hoops_PGCC._hoops_PIHSR) {
			case _hoops_SIHSR: {
				if (dc->_hoops_PGCC._hoops_AAPSR <= 256) {
					/* _hoops_SCGH 8 */
					unsigned char const		*rasters =
							(unsigned char const *)image->rasters[voffset];

					rasters = rasters+hoffset;

					fprintf (state->fp, "\tcolor indexes:\n");
					_hoops_RGGA (height-- == 0) {
						unsigned char const		*_hoops_SCGCR;
						unsigned char const	   *_hoops_HSGCR;

						fprintf (state->fp, "\t\t");

						_hoops_SCGCR = rasters;
						_hoops_HSGCR = rasters + width;
						_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR)
							fprintf (state->fp, "%3d ", *_hoops_SCGCR++);
						rasters += row_bytes;

						fprintf (state->fp, "\n");
					}
				}
				else {
					/* _hoops_HHCC 16 */
					unsigned short const	*rasters =
							(unsigned short const *)image->rasters[voffset];

					rasters = rasters+hoffset;

					fprintf (state->fp, "\tcolor indexes:\n");
					_hoops_RGGA (height-- == 0) {
						unsigned short const	*_hoops_SCGCR;
						unsigned short const	   *_hoops_HSGCR;

						fprintf (state->fp, "\t\t");

						_hoops_SCGCR = rasters;
						_hoops_HSGCR = rasters + width;
						_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR)
							fprintf (state->fp, "%3d ", *_hoops_SCGCR++);

						fprintf (state->fp, "\n");
					 }
				}
			}	break;

			case _hoops_HIHSR: {
				RGBAS32 const			*rasters =
							(RGBAS32 const *)image->rasters[voffset];

				rasters = rasters+hoffset;

				fprintf (state->fp, "\tRGBA values:\n");
				_hoops_RGGA (height-- == 0) {
					RGBAS32 const	*_hoops_SCGCR;
					RGBAS32 const	*_hoops_HSGCR;

					_hoops_SCGCR = rasters;
					_hoops_HSGCR = rasters + width;
					_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR) {
						fprintf (state->fp, "\t\t(%3d,%3d,%3d,%3d)\n",
								 _hoops_SCGCR->r, _hoops_SCGCR->g, _hoops_SCGCR->b, _hoops_SCGCR->a);
						++_hoops_SCGCR;
					}
					rasters = (RGBAS32 const *)((unsigned char const *)rasters +
												 row_bytes);
				}
			}	break;

		   case _hoops_RIIHP: {
				unsigned char const		*rasters =
							(unsigned char const *)image->rasters[voffset];
				int						_hoops_HCRPI;
				int						_hoops_HPGGS;

				rasters = rasters+hoffset;

				_hoops_HCRPI = width / 8;
				_hoops_HPGGS = width % 8;

				fprintf (state->fp, "\tbits:\n");
				_hoops_RGGA (height-- == 0) {
					unsigned char			byte;
					unsigned char const	   *_hoops_SCGCR;
					unsigned char const	   *_hoops_HSGCR;

					fprintf (state->fp, "\t\t");

					_hoops_SCGCR = rasters;
					_hoops_HSGCR = rasters+_hoops_HCRPI;
					_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR) {
						byte = *_hoops_SCGCR++;
						fprintf (state->fp, BIT (byte, 0x01) ? "1" : "_");
						fprintf (state->fp, BIT (byte, 0x02) ? "1" : "_");
						fprintf (state->fp, BIT (byte, 0x04) ? "1" : "_");
						fprintf (state->fp, BIT (byte, 0x08) ? "1" : "_");
						fprintf (state->fp, BIT (byte, 0x10) ? "1" : "_");
						fprintf (state->fp, BIT (byte, 0x20) ? "1" : "_");
						fprintf (state->fp, BIT (byte, 0x40) ? "1" : "_");
						fprintf (state->fp, BIT (byte, 0x80) ? "1" : "_");
					}

					if (_hoops_HPGGS) {
						byte = *_hoops_SCGCR;

						switch (_hoops_HPGGS) {
							case 7: {
								fprintf (state->fp,
										 BIT (byte, 0x01) ? "1" : "_");
								byte >>= 1;
							}	_hoops_HHHI;

							case 6: {
								fprintf (state->fp,
										 BIT (byte, 0x01) ? "1" : "_");
								byte >>= 1;
							}	_hoops_HHHI;

							case 5: {
								fprintf (state->fp,
										 BIT (byte, 0x01) ? "1" : "_");
								byte >>= 1;
							}	_hoops_HHHI;

							case 4: {
								fprintf (state->fp,
										 BIT (byte, 0x01) ? "1" : "_");
								byte >>= 1;
							}	_hoops_HHHI;

							case 3: {
								fprintf (state->fp,
										 BIT (byte, 0x01) ? "1" : "_");
								fprintf (state->fp,
										 BIT (byte, 0x01) ? "1" : "_");
								byte >>= 1;
							}	_hoops_HHHI;

							case 2: {
								fprintf (state->fp,
										 BIT (byte, 0x01) ? "1" : "_");
								byte >>= 1;
							}	_hoops_HHHI;

							case 1: {
								fprintf (state->fp,
										 BIT (byte, 0x01) ? "1" : "_");
							}	break;

							case 0: {
							}	break;
						}
					}

					rasters += row_bytes;

					fprintf (state->fp, "\n");
				}
			}
		}
	}
}


/*
 * _hoops_SRAC
 */
local void draw_3d_ellipse (
	Net_Rendition const & nr,
	Ellipse const		*ellipse) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		fprintf (state->fp, "\ndraw_3d_ellipse\n");

		if (nr->transform_rendition->_hoops_CPA !=
			~state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_RRGGS);
		else
			_hoops_CRGGS (&state->transform);

		if (nr->_hoops_IHA->_hoops_CPA != state->face._hoops_SSAC)
			_hoops_IAGGS (nr);
		else
			_hoops_CRGGS (&state->face);

		_hoops_SAGGS (state->fp,
					 1,
					 (DC_Point const *)&ellipse->center,
					 nr,
					 "center");
		_hoops_SAGGS (state->fp,
					 1,
					 (DC_Point const *)&ellipse->major,
					 nr,
					 "major");
		_hoops_SAGGS (state->fp,
					 1,
					 (DC_Point const *)&ellipse->minor,
					 nr,
					 "minor");
		_hoops_APGGS (&state->draw_3d_ellipse, 1L);
	}
}


/*
 * _hoops_SRAC
 */
local void draw_3d_elliptical_arc (
	Net_Rendition const & nr,
	Elliptical_Arc const *_hoops_ICCHH) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		fprintf (state->fp, "\ndraw_3d_elliptical_arc\n");

		if (nr->transform_rendition->_hoops_CPA !=
			~state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_RRGGS);
		else
			_hoops_CRGGS (&state->transform);

		if (nr->_hoops_AHP->_hoops_CPA != state->line._hoops_SSAC)
			_hoops_AIHSC (nr, nr->_hoops_AHP);
		else
			_hoops_CRGGS (&state->line);

		_hoops_SAGGS (state->fp,
					 1,
					 (DC_Point const *)&_hoops_ICCHH->center,
					 nr,
					 "center");
		_hoops_SAGGS (state->fp,
					 1,
					 (DC_Point const *)&_hoops_ICCHH->major,
					 nr,
					 "major");
		_hoops_SAGGS (state->fp,
					 1,
					 (DC_Point const *)&_hoops_ICCHH->minor,
					 nr,
					 "minor");
		fprintf (state->fp, "\t\tstart = %f\n", _hoops_ICCHH->arc_start);
		fprintf (state->fp, "\t\tend = %f\n", _hoops_ICCHH->_hoops_PHHI);
		_hoops_APGGS (&state->draw_3d_elliptical_arc, 1L);
	}
}


/*
 * _hoops_SRAC
 */
local void draw_3d_marker (
	Net_Rendition const & nr,
	Marker const			*marker) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		fprintf (state->fp, "\ndraw_3d_marker\n");

		if (nr->transform_rendition->_hoops_CPA !=
			~state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_RRGGS);
		else
			_hoops_CRGGS (&state->transform);

		/*_hoops_ASIGA
		_hoops_RPP (_hoops_SCII->_hoops_IPGGS->_hoops_HSHR != _hoops_PIAP->_hoops_III._hoops_CGHI)
			_hoops_CPGGS (_hoops_SCII, _hoops_SCII->_hoops_IPGGS);
		_hoops_SHS
			_hoops_SPGGS (&_hoops_PIAP->_hoops_III);
			*/

		_hoops_SAGGS (state->fp,
					 1,
					 (DC_Point const *)&marker->_hoops_CSAI,
					 nr,
					 "where");
		_hoops_APGGS (&state->draw_3d_marker, 1L);
	}
}


/*
 * _hoops_SRAC
 */
local void draw_3d_polyline (
	Net_Rendition const & nr,
	Polyline const		*polyline) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		fprintf (state->fp, "\ndraw_3d_polyline\n");

		if (nr->transform_rendition->_hoops_CPA !=
			~state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_RRGGS);
		else
			_hoops_CRGGS (&state->transform);

		if (nr->_hoops_AHP->_hoops_CPA != state->line._hoops_SSAC)
			_hoops_AIHSC (nr, nr->_hoops_AHP);
		else
			_hoops_CRGGS (&state->line);

		if (polyline->type == _hoops_PIIP) {
			Line const *	line = (Line const *)polyline;

			_hoops_SAGGS (state->fp,
						 2,
						 (DC_Point const *)line->points,
						 nr,
						 "points");
			_hoops_APGGS (&state->draw_3d_polyline, (long)2);
		}
		else {
			_hoops_SAGGS (state->fp,
						 Abs(polyline->count),
						 (DC_Point const *)polyline->points,
						 nr,
						 "points");
			_hoops_APGGS (&state->draw_3d_polyline, (long)Abs(polyline->count));
		}
	}
}


/*
 * _hoops_SRAC
 */
local void draw_3d_polygon (
	Net_Rendition const & nr,
	Polygon const		*polygon) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		fprintf (state->fp, "\ndraw_3d_polygon\n");

		if (nr->transform_rendition->_hoops_CPA !=
			~state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_RRGGS);
		else
			_hoops_CRGGS (&state->transform);

		if (nr->_hoops_IHA->_hoops_CPA != state->face._hoops_SSAC)
			_hoops_IAGGS (nr);
		else
			_hoops_CRGGS (&state->face);

		_hoops_SAGGS (state->fp,
					 polygon->count,
					 (DC_Point const *)polygon->points,
					 nr,
					 "points");
		_hoops_APGGS (&state->draw_3d_polygon, (long)polygon->count);
	}
}


/*
 * _hoops_SRAC
 */
local void draw_dc_ellipse (
	Net_Rendition const & nr,
	DC_Point const		*center,
	DC_Point const		*radius) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		fprintf (state->fp, "\ndraw_dc_ellipse\n");

		if (nr->transform_rendition->_hoops_CPA !=
			state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_ARGGS);
		else
			_hoops_CRGGS (&state->transform);

		if (nr->_hoops_IHA->_hoops_CPA != state->face._hoops_SSAC)
			_hoops_IAGGS (nr);
		else
			_hoops_CRGGS (&state->face);

		_hoops_SAGGS (state->fp, 1, center, nr, "center");
		_hoops_SAGGS (state->fp, 1, radius, nr, "radius");
		_hoops_APGGS (&state->draw_dc_ellipse, 1L);
	}
}


/*
 * _hoops_SRAC
 */
local void _hoops_CCISR (
	Net_Rendition const & nr,
	DC_Point const		*where,
	DC_Point const		*radius,
	float					start,
	float					end) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		fprintf (state->fp, "\ndraw_dc_elliptical_arc\n");

		if (nr->transform_rendition->_hoops_CPA !=
			~state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_ARGGS);
		else
			_hoops_CRGGS (&state->transform);

		if (nr->_hoops_AHP->_hoops_CPA != state->line._hoops_SSAC)
			_hoops_AIHSC (nr, nr->_hoops_AHP);
		else
			_hoops_CRGGS (&state->line);

		_hoops_SAGGS (state->fp,
					 1,
					 where,
					 nr,
					 "center");
		_hoops_SAGGS (state->fp,
					 1,
					 radius,
					 nr,
					 "radius");
		fprintf (state->fp, "\t\tstart = %f\n", start);
		fprintf (state->fp, "\t\tend = %f\n", end);
		_hoops_APGGS (&state->_hoops_CCISR, 1L);
	}
}


/*
 * _hoops_SRAC
 */
local void _hoops_SCISR (
	Net_Rendition const & nr,
	DC_Point const		*center,
	DC_Point const		*radius) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		fprintf (state->fp, "\ndraw_dc_outline_ellipse\n");

		if (nr->transform_rendition->_hoops_CPA !=
			state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_ARGGS);
		else
			_hoops_CRGGS (&state->transform);

		if (nr->_hoops_AHP->_hoops_CPA != state->line._hoops_SSAC)
			_hoops_AIHSC (nr, nr->_hoops_AHP);
		else
			_hoops_CRGGS (&state->line);

		_hoops_SAGGS (state->fp, 1, center, nr, "center");
		_hoops_SAGGS (state->fp, 1, radius, nr, "radius");
		_hoops_APGGS (&state->_hoops_SCISR, 1L);
	}
}


/*
 * _hoops_SRAC
 */
local void draw_dc_polyline (
	Net_Rendition const & nr,
	int						count,
	DC_Point const		*points) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		fprintf (state->fp, "\ndraw_dc_polyline\n");

		if (nr->transform_rendition->_hoops_CPA !=
			state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_ARGGS);
		else
			_hoops_CRGGS (&state->transform);

		if (nr->_hoops_AHP->_hoops_CPA != state->line._hoops_SSAC)
			_hoops_AIHSC (nr, nr->_hoops_AHP);
		else
			_hoops_CRGGS (&state->line);

		_hoops_SAGGS (state->fp, count, points, nr, "points");
		_hoops_APGGS (&state->draw_dc_polyline, (long)count);
	}
}


/*
 * _hoops_SRAC
 */
local void draw_dc_face (
	Net_Rendition const & nr,
	int						count,
	DC_Point const		*points) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		fprintf (state->fp, "\ndraw_dc_face\n");

		if (nr->transform_rendition->_hoops_CPA !=
			state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_ARGGS);
		else
			_hoops_CRGGS (&state->transform);

		if (nr->_hoops_IHA->_hoops_CPA != state->face._hoops_SSAC)
			_hoops_IAGGS (nr);
		else
			_hoops_CRGGS (&state->face);

		_hoops_SAGGS (state->fp, count, points, nr, "points");
		_hoops_APGGS (&state->draw_dc_face, (long)count);
	}
}


/*
 * _hoops_PGAA
 */
local void _hoops_GHGGS (
	Net_Rendition const &		nr,
	RGBAS32 const *				color) {
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HCSSC alter *		state = _hoops_CSSSC (dc);

	/* _hoops_RGHH _hoops_HHH _hoops_IRGGS */
	state->face._hoops_CCCIR++;
	if (_hoops_SIGA->color == state->face.color)
		state->face._hoops_IHSSC++;
	else {
		state->face._hoops_CCASR++;
	}
	if (_hoops_SIGA->contrast_color == state->face.contrast_color)
		state->face._hoops_CHSSC++;
	else {
		state->face._hoops_SHSSC++;
		state->face.contrast_color = _hoops_SIGA->contrast_color;
	}
	if (_hoops_SIGA->pattern == state->face.pattern)
		state->face._hoops_GISSC++;
	else {
		state->face._hoops_RISSC++;
		state->face.pattern = _hoops_SIGA->pattern;
	}

	/* _hoops_IPIHR _hoops_RH _hoops_ACSP _hoops_RPP _hoops_IPSP _hoops_APSI _hoops_PIRC _hoops_IIGR _hoops_SCH */
	if (state->fp != null) {
		fprintf (state->fp, "\tnew colorized face rendition: %d\n",
				 _hoops_SIGA->_hoops_CPA);

		switch (dc->_hoops_PGCC._hoops_PIHSR) {
			case _hoops_SIHSR:
			case _hoops_RIIHP: {
				int				i;
				_hoops_GARSR	colors[5];
				int				count,
												_hoops_AHHIR[4];

				fprintf (state->fp, "\t\ttarget color = %s\n",
						 _hoops_ACASR (state->buf, color));

				count = HD_Find_Dither_Pattern (nr, color, colors, _hoops_AHHIR);

				fprintf (state->fp, "\t\t\tcolor count = %d\n", count);
				fprintf (state->fp, "\t\t\tcolor[0] = %d, pattern = %d (SOLID)\n",
						 (int)colors[0], FP_SOLID);
				for (i = 1; i < count; i++)
					fprintf (state->fp, "\t\t\tcolor[%d] = %d, pattern[%d] = %d\n",
							 i, (int)colors[i], i - 1, _hoops_AHHIR[i - 1]);
				state->face.color._hoops_PGGCR = colors[count -1];
				state->face._hoops_SSAC = (_hoops_GARRR)0;
			}	break;

			case _hoops_HIHSR: {
				fprintf (state->fp, "\t\tcolorized color = %s\n",
						 _hoops_ACASR (state->buf,
									color));
				state->face.color = *color;
				state->face._hoops_SSAC = _hoops_SIGA->_hoops_CPA;
			}	break;
		}

		if (_hoops_SIGA->pattern != FP_SOLID)
			fprintf (state->fp, "\t\tcontrast color = %s\n",
					 _hoops_RSHPP (state->buf,
								 &_hoops_SIGA->contrast_color,
								 nr->_hoops_SRA));

		/* _hoops_SSPC _hoops_CAGGS */

		/* _hoops_SSPC _hoops_PSHAR */

		if (BIT (dc->options._hoops_IRARR, _hoops_RPSSC))
			_hoops_AAGGS (state, dc,
									  _hoops_SIGA->_hoops_CHA,
									  _hoops_SIGA->_hoops_AGP);

		fprintf (state->fp, "\t\tpattern = %s\n",
				 _hoops_HAGGS (_hoops_SIGA->pattern));

		if (_hoops_SIGA->pattern == FP_USER_DEFINED) {
			_hoops_SIHHP const		*up = _hoops_SIGA->_hoops_PGPH;

			if (state->_hoops_GSSSC != up->_hoops_CPA) {
				_hoops_GAGGS (state, dc, up);
				state->_hoops_GSSSC = up->_hoops_CPA;
			}
		}
	}
}


/*
 * _hoops_SRAC
 */
local void draw_dc_colorized_face (
	Net_Rendition const & nr,
	int						count,
	DC_Point const		*points,
	RGBAS32 const			*color) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		fprintf (state->fp, "\ndraw_dc_colorized_face\n");

		if (nr->transform_rendition->_hoops_CPA !=
			state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_ARGGS);
		else
			_hoops_CRGGS (&state->transform);

		if (nr->_hoops_IHA->_hoops_CPA != state->face._hoops_SSAC)
			_hoops_GHGGS (nr, color);
		else
			_hoops_CRGGS (&state->face);

		_hoops_SAGGS (state->fp, count, points, nr, "points");
		_hoops_APGGS (&state->draw_dc_colorized_face, (long)count);
	}
}


/*
 * _hoops_SRAC
 */
local void draw_dc_rectangle (
	Net_Rendition const & nr,
	int						left,
	int						right,
	int						bottom,
	int						top) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		fprintf (state->fp, "\ndraw_dc_rectangle\n");

		if (nr->transform_rendition->_hoops_CPA !=
			state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_ARGGS);
		else
			_hoops_CRGGS (&state->transform);

		if (nr->_hoops_IHA->_hoops_CPA != state->face._hoops_SSAC)
			_hoops_IAGGS (nr);
		else
			_hoops_CRGGS (&state->face);

		fprintf (state->fp, "\trectangle\n");
		fprintf (state->fp, "\t\tleft	= %d\n", left);
		fprintf (state->fp, "\t\tright	= %d\n", right);
		fprintf (state->fp, "\t\tbottom = %d\n", bottom);
		fprintf (state->fp, "\t\ttop	= %d\n", top);
		_hoops_APGGS (&state->draw_dc_rectangle, 1L);
	}
}


/*
 * _hoops_SRAC
 */
local void draw_dc_polydot (
	Net_Rendition const & nr,
	int						count,
	DC_Point const		*points) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		fprintf (state->fp, "\ndraw_dc_dot\n");

		if (nr->transform_rendition->_hoops_CPA !=
			state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_ARGGS);
		else
			_hoops_CRGGS (&state->transform);

		if (nr->_hoops_AHP->_hoops_CPA != state->line._hoops_SSAC)
			_hoops_AIHSC (nr, nr->_hoops_AHP);
		else
			_hoops_CRGGS (&state->line);

		_hoops_SAGGS (state->fp, count, points, nr, "where");
		_hoops_APGGS (&state->draw_dc_polydot, 1L);
	}
}


/*
 * _hoops_PGAA
 */
local void _hoops_RHGGS (
	Net_Rendition const & nr) {
	_hoops_IGCSR const &	_hoops_HRCIR = nr->_hoops_SISI;
	Display_Context const		*dc = nr->_hoops_SRA;
	_hoops_HCSSC alter				*state = _hoops_CSSSC (dc);

	/* _hoops_RGHH _hoops_HHH _hoops_IRGGS */
	state->text._hoops_SSAC = _hoops_HRCIR->_hoops_CPA;
	state->text._hoops_CCCIR++;
	if (_hoops_HRCIR->color == state->text.color)
		state->text._hoops_IHSSC++;
	else {
		state->text._hoops_CCASR++;
		state->text.color = _hoops_HRCIR->color;
	}
	if ((void const *)_hoops_HRCIR->font == state->text.font)
		state->text._hoops_CISSC++;
	else {
		state->text._hoops_SISSC++;
		state->text.font = (void alter *)_hoops_HRCIR->font;
	}

	/* _hoops_IPIHR _hoops_RH _hoops_ACSP _hoops_RPP _hoops_IPSP _hoops_APSI _hoops_PIRC _hoops_IIGR _hoops_SCH */
	if (state->fp == null)
		return;

	fprintf (state->fp, "\tnew text rendition: %d\n", _hoops_HRCIR->_hoops_CPA);

	if (BIT (dc->options._hoops_IRARR, _hoops_RPSSC))
		_hoops_AAGGS (state, dc, _hoops_HRCIR->_hoops_CHA, null);

	fprintf (state->fp, "\t\tcolor = %s\n", _hoops_RSHPP (state->buf,
														&_hoops_HRCIR->color,
														nr->_hoops_SRA));

	if (BIT (dc->options._hoops_IRARR, _hoops_CASSC)) {
		fprintf (state->fp, "\t\talignment = %d\n", _hoops_HRCIR->_hoops_PRRIP);

		fprintf (state->fp, "\t\tspacing = %.4f\n", _hoops_HRCIR->spacing);

		fprintf (state->fp, "\t\tpath = (%.4f, %.4f, %.4f)\n",
				 _hoops_HRCIR->path.x, _hoops_HRCIR->path.y, _hoops_HRCIR->path.z);

		fprintf (state->fp, "\t\tfont = 0x%p\n", (void*)_hoops_HRCIR->font);

		fprintf (state->fp, "\t\tnames_ref = 0x%p\n", (void*)_hoops_HRCIR->_hoops_HSRIP);

		fprintf (state->fp, "\t\tdbsize = %.4f\n", _hoops_HRCIR->_hoops_PHP);

		fprintf (state->fp, "\t\tsize tolerance = %.4f\n", _hoops_HRCIR->_hoops_ACPAP);

		fprintf (state->fp, "\t\textra space = %.4f\n", _hoops_HRCIR->_hoops_PCPAP);

		switch (_hoops_HRCIR->transform) {
			case FT_NOT_VALID: {
				fprintf (state->fp, "\t\ttranform = FT_NOT_VALID\n");
			}	break;

			case FT_FULL: {
				fprintf (state->fp, "\t\ttransform = FT_FULL\n");
			}	break;

			case FT_NONE: {
				fprintf (state->fp, "\t\ttransform = FT_NONE\n");
			}	break;

			case FT_POSITION_ONLY: {
				fprintf (state->fp, "\t\ttransform = FT_POSITION_ONLY\n");
			}	break;

			case FT_POSITION_ADJUSTED: {
				fprintf (state->fp, "\t\ttransform = FT_POSITION_ADJUSTED\n");
			}	break;
		}

		/* _hoops_SSPC _hoops_AHGGS */

		/* _hoops_SSPC _hoops_PHGGS */

		/* _hoops_SSPC _hoops_HHGGS */

		/* _hoops_SSPC _hoops_IHGGS */

		fprintf (state->fp, "\t\trotation = %.4f\n", _hoops_HRCIR->rotation);

		fprintf (state->fp, "\t\twidth scale = %.4f\n", _hoops_HRCIR->width_scale);

		fprintf (state->fp, "\t\tslant = %.4f\n", _hoops_HRCIR->_hoops_IPGRP);

		fprintf (state->fp, "\t\teven spacing = %s\n",
				 _hoops_HRCIR->_hoops_HCRIP ? "true" : "false");
	}
}


/*
 * _hoops_SRAC
 */
local void draw_dc_text (
	Net_Rendition const & nr,
	DC_Point const		*where,
	int						count,
	Karacter const		*kstring) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		int				i;

		fprintf (state->fp, "\ndraw_dc_text\n");

		if (nr->transform_rendition->_hoops_CPA !=
			state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_ARGGS);
		else
			_hoops_CRGGS (&state->transform);

		if (nr->_hoops_SISI->_hoops_CPA != state->text._hoops_SSAC)
			_hoops_RHGGS (nr);
		else
			_hoops_CRGGS (&state->text);

		_hoops_SAGGS (state->fp, 1, where, nr, "where");
		_hoops_APGGS (&state->draw_dc_text, (long)count);
		fprintf (state->fp, "\ttext = ");
		/*_hoops_SIGP _hoops_CCIH _hoops_IH _hoops_CHGGS*/
		for (i = 0; i < count; i++)
			fprintf (state->fp, "%x ", kstring[i]);
		fprintf (state->fp, "\n");
	}
}


/*
 * _hoops_PGAA
 */
local void _hoops_SHGGS (
	FILE alter		*fp,
	long			count,
	long			offset,
	Point const	*point,
	char const		*_hoops_RHSRR) {

	fprintf (fp, "\t\t%s(%ld) = %ld (%.4f, %.4f, %.4f)\n",
			 _hoops_RHSRR, count, offset, point->x, point->y, point->z);
}


/*
 * _hoops_PGAA
 */
local void _hoops_GIGGS (
	FILE alter		*fp,
	long			count,
	long			offset,
	RGB const	*color,
	char const		*_hoops_RHSRR) {

	fprintf (fp, "\t\t%s(%ld) = %ld (%.4f, %.4f, %.4f)\n",
			 _hoops_RHSRR, count, offset, color->red, color->green, color->blue);
}


/*
 * _hoops_PGAA
 */
local void _hoops_RIGGS (
	FILE alter		*fp,
	long			count,
	long			offset,
	Vector const *normal,
	char const		*_hoops_RHSRR) {

	fprintf (fp, "\t\t%s(%ld) = %ld (%.4f, %.4f, %.4f)\n",
			 _hoops_RHSRR, count, offset, normal->x, normal->y, normal->z);
}



/*
 * _hoops_PGAA
 */
local void _hoops_AIGGS (
	FILE alter						*fp,
	long							count,
	long							offset,
	_hoops_RSSH const				*param,
	Integer32					param_width,
	char const						*_hoops_RHSRR) {
	int		i;

	fprintf (fp, "\t\t%s(%ld) = %ld (",_hoops_RHSRR, count, offset);

	for (i=0;i<param_width-1;i++) {
		fprintf (fp, "%.4f, ", param[i]);
	}

	fprintf (fp, "%.4f)\n", param[param_width-1]);
}


/*
 * _hoops_SRAC
 */
local void draw_3d_polyedge (
	Net_Rendition const & nr,
	Polyedge const		*polyedge) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		int						_hoops_PHHA = polyedge->_hoops_PHHA;
		int const *				lengths = polyedge->lengths;
		int const *				vi = polyedge->_hoops_AIHA;
		int const *				ei = polyedge->_hoops_SPII;
		long					point_count;
		long					_hoops_SPHA;
		long					_hoops_PIGGS;

		fprintf (state->fp, "\ndraw_3d_polyedge\n");
		if (polyedge->_hoops_ASHA != null)
			fprintf (state->fp, "\twith edge colors\n");
		if (polyedge->_hoops_RSHA != null)
			fprintf (state->fp, "\twith edge normals\n");
		if (polyedge->_hoops_PCHA != null)
			fprintf (state->fp, "\twith vertex colors\n");
		if (polyedge->_hoops_ICHA != null)
			fprintf (state->fp, "\twith vertex normals\n");
		if (polyedge->_hoops_CCHA != null)
			fprintf (state->fp, "\twith vertex parameters\n");

		if (nr->transform_rendition->_hoops_CPA != ~state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_RRGGS);
		else
			_hoops_CRGGS (&state->transform);

		if (nr->_hoops_RHP->_hoops_CPA != state->line._hoops_SSAC)
			_hoops_AIHSC (nr, nr->_hoops_RHP);
		else
			_hoops_CRGGS (&state->line);

		_hoops_PIGGS = 0L;
		while (_hoops_PHHA-- > 0) {
			int				length;
			int				offset;

			fprintf (state->fp, "\tsub-line:\n");
			point_count = 0L;
			_hoops_SPHA = 0L;

			/* _hoops_SRS _hoops_PPSR */
			offset = *vi++;
			_hoops_SHGGS (state->fp,
						point_count,
						offset,
						&polyedge->points[offset],
						"point");
			if (polyedge->_hoops_PCHA != null)
				_hoops_GIGGS (state->fp,
							point_count,
							offset,
							&polyedge->_hoops_PCHA[offset],
							"vertex color");
			if (polyedge->_hoops_ICHA != null)
				_hoops_RIGGS (state->fp,
							 point_count,
							 offset,
							 &polyedge->_hoops_ICHA[offset],
							 "vertex normal");
			if (polyedge->_hoops_CCHA != null)
				_hoops_AIGGS (state->fp,
								point_count,
								offset,
								&polyedge->_hoops_CCHA[offset*polyedge->_hoops_GSHA],
								polyedge->_hoops_GSHA,
								"vertex parameter");
			point_count++;

			length = *lengths++ - 1;
			ei++;
			while (length-- > 0) {
				offset = *vi++;
				_hoops_SHGGS (state->fp,
							point_count,
							offset,
							&polyedge->points[offset],
							"point");
				if (polyedge->_hoops_PCHA != null)
					_hoops_GIGGS (state->fp,
								point_count,
								offset,
								&polyedge->_hoops_PCHA[offset],
								"vertex color");
				if (polyedge->_hoops_ICHA != null)
					_hoops_RIGGS (state->fp,
								 point_count,
								 offset,
								 &polyedge->_hoops_ICHA[offset],
								 "vertex normal");
				if (polyedge->_hoops_CCHA != null)
					_hoops_AIGGS (state->fp,
									point_count,
									offset,
									&polyedge->_hoops_CCHA[offset*polyedge->_hoops_GSHA],
									polyedge->_hoops_GSHA,
									"vertex parameter");
				point_count++;

				/* _hoops_ISHA */
				offset = *ei++;
				if (polyedge->_hoops_ASHA != null)
					_hoops_GIGGS (state->fp,
								_hoops_SPHA,
								offset,
								&polyedge->_hoops_ASHA[offset],
								"edge color");
				if (polyedge->_hoops_RSHA != null)
					_hoops_RIGGS (state->fp,
								 _hoops_SPHA,
								 offset,
								 &polyedge->_hoops_RSHA[offset],
								 "edge normal");
				_hoops_SPHA++;
			}

			_hoops_PIGGS += point_count;
		}
		_hoops_APGGS (&state->draw_3d_polyedge, _hoops_PIGGS);
	}
}


/*
 * _hoops_SRAC
 */
local void draw_3d_tristrip (
	Net_Rendition const & nr,
	Tristrip const		*tristrip) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		int						_hoops_PHHA = tristrip->_hoops_PHHA;
		int const *				lengths = tristrip->lengths;
		int const *				vi = tristrip->_hoops_AIHA;
		int const *				fi = tristrip->face_indices;
		long					point_count;
		long					face_count;
		long					_hoops_PIGGS;
		long					_hoops_SSPAR = -1;

		fprintf (state->fp, "\ndraw_3d_tristrip\n");
		if (tristrip->_hoops_PAGI != null)
			fprintf (state->fp, "\twith face colors\n");
		if (tristrip->_hoops_PRHH != null)
			fprintf (state->fp, "\twith face normals\n");
		if (tristrip->_hoops_PCHA != null)
			fprintf (state->fp, "\twith vertex colors\n");
		if (tristrip->_hoops_ICHA != null)
			fprintf (state->fp, "\twith vertex normals\n");
		if (tristrip->_hoops_GSSH->_hoops_CCHA != null)
			fprintf (state->fp, "\twith vertex parameters\n");

		if (nr->transform_rendition->_hoops_CPA !=
			~state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_RRGGS);
		else
			_hoops_CRGGS (&state->transform);

		if (nr->_hoops_IHA->_hoops_CPA != state->face._hoops_SSAC)
			_hoops_IAGGS (nr);
		else
			_hoops_CRGGS (&state->face);

		_hoops_PIGGS = 0L;
		while (_hoops_PHHA-- > 0) {
			int				length;
			int				offset;

			fprintf (state->fp, "\tsub-strip:\n");
			point_count = 0L;
			face_count = 0L;

			/* _hoops_SRS _hoops_PPSR */
			offset = *vi++;
			_hoops_SHGGS (state->fp,
						point_count,
						offset,
						&tristrip->points[offset],
						"point");
			if (tristrip->_hoops_PCHA != null)
				_hoops_GIGGS (state->fp,
							point_count,
							offset,
							&tristrip->_hoops_PCHA[offset],
							"vertex color");
			if (tristrip->_hoops_ICHA != null)
				_hoops_RIGGS (state->fp,
							 point_count,
							 offset,
							 &tristrip->_hoops_ICHA[offset],
							 "vertex normal");
			if (tristrip->_hoops_GSSH->_hoops_CCHA != null)
				_hoops_AIGGS (state->fp,
								point_count,
								offset,
								&tristrip->_hoops_GSSH->_hoops_CCHA[offset*tristrip->_hoops_GSSH->_hoops_GSHA],
								tristrip->_hoops_GSSH->_hoops_GSHA,
								"vertex parameter");
			point_count++;

			/* _hoops_GIAP _hoops_PPSR */
			offset = *vi++;
			_hoops_SHGGS (state->fp,
						point_count,
						offset,
						&tristrip->points[offset],
						"point");
			if (tristrip->_hoops_PCHA != null)
				_hoops_GIGGS (state->fp,
							point_count,
							offset,
							&tristrip->_hoops_PCHA[offset],
							"vertex color");
			if (tristrip->_hoops_ICHA != null)
				_hoops_RIGGS (state->fp,
							 point_count,
							 offset,
							 &tristrip->_hoops_ICHA[offset],
							 "vertex normal");
			if (tristrip->_hoops_GSSH->_hoops_CCHA != null)
				_hoops_AIGGS (state->fp,
								point_count,
								offset,
								&tristrip->_hoops_GSSH->_hoops_CCHA[offset*tristrip->_hoops_GSSH->_hoops_GSHA],
								tristrip->_hoops_GSSH->_hoops_GSHA,
								"vertex parameter");
			point_count++;


			length = *lengths++ - 2;
			if (fi) fi += 2;
			while (length-- > 0) {
				offset = *vi++;
				_hoops_SHGGS (state->fp,
							point_count,
							offset,
							&tristrip->points[offset],
							"point");
				if (tristrip->_hoops_PCHA != null)
					_hoops_GIGGS (state->fp,
								point_count,
								offset,
								&tristrip->_hoops_PCHA[offset],
								"vertex color");
				if (tristrip->_hoops_ICHA != null)
					_hoops_RIGGS (state->fp,
								 point_count,
								 offset,
								 &tristrip->_hoops_ICHA[offset],
								 "vertex normal");
				if (tristrip->_hoops_GSSH->_hoops_CCHA != null)
					_hoops_AIGGS (state->fp,
									point_count,
									offset,
									&tristrip->_hoops_GSSH->_hoops_CCHA[offset*tristrip->_hoops_GSSH->_hoops_GSHA],
									tristrip->_hoops_GSSH->_hoops_GSHA,
									"vertex parameter");
				point_count++;

				if (fi)
					_hoops_SSPAR = *fi++;
				else
					_hoops_SSPAR++;
				if (tristrip->_hoops_PAGI != null)
					_hoops_GIGGS (state->fp,
								face_count,
								offset,
								&tristrip->_hoops_PAGI[_hoops_SSPAR],
								"face color");
				if (tristrip->_hoops_PRHH != null)
					_hoops_RIGGS (state->fp,
								 face_count,
								 offset,
								 (Vector *)&tristrip->_hoops_PRHH[_hoops_SSPAR],
								 "face normal");
				face_count++;
			}

			_hoops_APGGS (&state->_hoops_ASSSC, point_count);
			_hoops_PIGGS += point_count;
		}

		_hoops_APGGS (&state->draw_3d_tristrip, _hoops_PIGGS);
	}
}


/*
 * _hoops_SRAC
 */
local void draw_3d_polymarker (
	Net_Rendition const & nr,
	Polymarker const		*_hoops_RGRHR) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		int						length = _hoops_RGRHR->length;
		int const *				vi = _hoops_RGRHR->_hoops_AIHA;
		int						offset;
		long					point_count;

		fprintf (state->fp, "\ndraw_3d_polymarker\n");
		if (_hoops_RGRHR->_hoops_PCHA != null)
			fprintf (state->fp, "\twith vertex colors\n");
		if (_hoops_RGRHR->_hoops_ICHA != null)
			fprintf (state->fp, "\twith vertex normals\n");
		if (_hoops_RGRHR->_hoops_CCHA != null)
			fprintf (state->fp, "\twith vertex parameters\n");

		if (nr->transform_rendition->_hoops_CPA !=
			~state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_RRGGS);
		else
			_hoops_CRGGS (&state->transform);

		/*_hoops_ASIGA
		_hoops_RPP (_hoops_SCII->_hoops_HIGGS->_hoops_HSHR != _hoops_PIAP->_hoops_III._hoops_CGHI) {
			_hoops_CPGGS (_hoops_SCII, _hoops_SCII->_hoops_HIGGS);
		}
		_hoops_SHS
			_hoops_SPGGS (&_hoops_PIAP->_hoops_III);
			*/

		point_count = 0L;
		while (length-- > 0) {
			offset = *vi++;

			_hoops_SHGGS (state->fp,
						1,
						offset,
						&_hoops_RGRHR->points[offset],
						"point");
			if (_hoops_RGRHR->_hoops_PCHA != null)
				_hoops_GIGGS (state->fp,
							1,
							offset,
							&_hoops_RGRHR->_hoops_PCHA[offset],
							"vertex color");
			if (_hoops_RGRHR->_hoops_ICHA != null)
				_hoops_RIGGS (state->fp,
							 1,
							 offset,
							 &_hoops_RGRHR->_hoops_ICHA[offset],
							 "vertex normal");
			if (_hoops_RGRHR->_hoops_CCHA != null)
				_hoops_AIGGS (state->fp,
								1,
								offset,
								&_hoops_RGRHR->_hoops_CCHA[offset*_hoops_RGRHR->_hoops_GSHA],
								_hoops_RGRHR->_hoops_GSHA,
								"vertex parameter");
			point_count++;
		}
		_hoops_APGGS (&state->draw_3d_polymarker, point_count);
	}
}


/*
 * _hoops_SRAC
 */
local void draw_dc_polytriangle (
	Net_Rendition const & nr,
	int						count,
	DC_Point const		*points) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		fprintf (state->fp, "\ndraw_dc_polytriangle\n");

		if (nr->transform_rendition->_hoops_CPA !=
			state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_ARGGS);
		else
			_hoops_CRGGS (&state->transform);

		if (nr->_hoops_IHA->_hoops_CPA != state->face._hoops_SSAC)
			_hoops_IAGGS (nr);
		else
			_hoops_CRGGS (&state->face);

		_hoops_SAGGS (state->fp, count, points, nr, "points");
		_hoops_APGGS (&state->draw_dc_polytriangle, 1L);
	}
}


/*
 * _hoops_SRAC
 */
local void draw_dc_colorized_polytriangle (
	Net_Rendition const & nr,
	int						count,
	DC_Point const		*points,
	RGBAS32 const			*colors,
	bool				single) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		fprintf (state->fp, "\ndraw_dc_colorized_polytriangle\n");

		if (nr->transform_rendition->_hoops_CPA !=
			state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_ARGGS);
		else
			_hoops_CRGGS (&state->transform);

		if (nr->_hoops_IHA->_hoops_CPA != state->face._hoops_SSAC)
			_hoops_IAGGS (nr);
		else
			_hoops_CRGGS (&state->face);

		fprintf (state->fp, "\tRGB's:\n");
		if (single)
			count = 1;
		else {
			int		_hoops_RRC;
			_hoops_ICHC (count, _hoops_RRC, 3);
		}
		while (count-- > 0) {
			fprintf (state->fp, "\t\t%ld %ld %ld\n",
					 (long)colors->r, (long)colors->g, (long)colors->b);
			colors++;
		}

		_hoops_SAGGS (state->fp, count, points, nr, "points");
		_hoops_APGGS (&state->draw_dc_colorized_polytriangle, 1L);
	}
}


/*
 * _hoops_SRAC
 */
local void draw_dc_gouraud_polytriangle (
	Net_Rendition const & nr,
	int						count,
	DC_Point const		*points,
	RGBAS32 const			*colors) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		fprintf (state->fp, "\ndraw_dc_gouraud_polytriangle\n");

		if (nr->transform_rendition->_hoops_CPA !=
			state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_ARGGS);
		else
			_hoops_CRGGS (&state->transform);

		if (nr->_hoops_IHA->_hoops_CPA != state->face._hoops_SSAC)
			_hoops_IAGGS (nr);
		else
			_hoops_CRGGS (&state->face);
		state->face._hoops_SSAC = (_hoops_GARRR)0;

		_hoops_SAGGS (state->fp, count, points, nr, "points");

		fprintf (state->fp, "\tRGB's:\n");
		if (count < 0) count = -count;
		while (count-- > 0) {
			fprintf (state->fp, "\t\t%ld %ld %ld\n",
					 (long)colors->r, (long)colors->g, (long)colors->b);
			colors++;
		}

		_hoops_APGGS (&state->draw_dc_gouraud_polytriangle, 1L);
	}
}


/*
 * _hoops_SRAC
 */
local void _hoops_CCCGA (
	Net_Rendition const & nr,
	DC_Point const		*start,
	DC_Point const		*end,
	int						row_bytes,
	unsigned char const		*rasters) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		int						width, height;
		int						_hoops_HCRPI;
		int						_hoops_HPGGS;

		width  = (int)end->x - (int)start->x + 1;
		height = (int)start->y - (int)end->y + 1;

		fprintf (state->fp, "\ndraw_dc_bit_rasters (%d rows)\n", height);

		if (nr->transform_rendition->_hoops_CPA != state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_ARGGS);
		else
			_hoops_CRGGS (&state->transform);

		_hoops_SAGGS (state->fp, 1, start, nr, "start");
		_hoops_SAGGS (state->fp, 1, end, nr, "end");
		_hoops_APGGS (&state->_hoops_PSSSC, (long)width * (long)height);
		_hoops_APGGS (&state->_hoops_HSSSC, (long)height);

		if (row_bytes == 0)
			row_bytes = (width * sizeof (unsigned char) + 7) / 8;
		_hoops_HCRPI = width / 8;
		_hoops_HPGGS = width % 8;

		fprintf (state->fp, "\tbits:\n");
		_hoops_RGGA (height-- == 0) {
			unsigned char			byte;
			unsigned char const		*_hoops_SCGCR;
			unsigned char const		*_hoops_HSGCR;

			fprintf (state->fp, "\t\t");

			_hoops_SCGCR = rasters;
			_hoops_HSGCR = rasters+_hoops_HCRPI;
			_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR) {
				byte = *_hoops_SCGCR++;
				fprintf (state->fp, BIT (byte, 0x01) ? "1" : "_");
				fprintf (state->fp, BIT (byte, 0x02) ? "1" : "_");
				fprintf (state->fp, BIT (byte, 0x04) ? "1" : "_");
				fprintf (state->fp, BIT (byte, 0x08) ? "1" : "_");
				fprintf (state->fp, BIT (byte, 0x10) ? "1" : "_");
				fprintf (state->fp, BIT (byte, 0x20) ? "1" : "_");
				fprintf (state->fp, BIT (byte, 0x40) ? "1" : "_");
				fprintf (state->fp, BIT (byte, 0x80) ? "1" : "_");
			}

			if (_hoops_HPGGS) {
				byte = *_hoops_SCGCR;

				switch (_hoops_HPGGS) {
					case 7: {
						fprintf (state->fp,
								 BIT (byte, 0x01) ? "1" : "_");
						byte >>= 1;
					}	_hoops_HHHI;

					case 6: {
						fprintf (state->fp,
								 BIT (byte, 0x01) ? "1" : "_");
						byte >>= 1;
					}	_hoops_HHHI;

					case 5: {
						fprintf (state->fp,
								 BIT (byte, 0x01) ? "1" : "_");
						byte >>= 1;
					}	_hoops_HHHI;

					case 4: {
						fprintf (state->fp,
								 BIT (byte, 0x01) ? "1" : "_");
						byte >>= 1;
					}	_hoops_HHHI;

					case 3: {
						fprintf (state->fp,
								 BIT (byte, 0x01) ? "1" : "_");
						byte >>= 1;
					}	_hoops_HHHI;

					case 2: {
						fprintf (state->fp,
								 BIT (byte, 0x01) ? "1" : "_");
						byte >>= 1;
					}	_hoops_HHHI;

					case 1: {
						fprintf (state->fp,
								 BIT (byte, 0x01) ? "1" : "_");
					}	break;

					case 0: {
					}	break;
				}
			}

			rasters += row_bytes;

			fprintf (state->fp, "\n");
		}
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
	unsigned char const		*rasters) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		int						width, height;

		width  = (int)end->x - (int)start->x + 1;
		height = (int)start->y - (int)end->y + 1;

		fprintf (state->fp, "\ndraw_dc_mapped8_rasters (%d rows)\n", height);

		if (nr->transform_rendition->_hoops_CPA != state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_ARGGS);
		else
			_hoops_CRGGS (&state->transform);

		_hoops_SAGGS (state->fp, 1, start, nr, "start");
		_hoops_SAGGS (state->fp, 1, end, nr, "end");
		_hoops_APGGS (&state->_hoops_PSSSC, (long)width * (long)height);
		_hoops_APGGS (&state->_hoops_HSSSC, (long)height);

		if (row_bytes == 0)
			row_bytes = width * sizeof (unsigned char);

		fprintf (state->fp, "\tcolor indexes:\n");
		_hoops_RGGA (height-- == 0) {
			unsigned char const		*_hoops_SCGCR;
			unsigned char const		*_hoops_HSGCR;

			fprintf (state->fp, "\t\t");

			_hoops_SCGCR = rasters;
			_hoops_HSGCR = rasters + width;
			_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR)
				fprintf (state->fp, "%3d ", *_hoops_SCGCR++);
			rasters += row_bytes;

			fprintf (state->fp, "\n");
		}
	}
}


/*
 * _hoops_SRAC
 */
local void _hoops_PSCGA (
	Net_Rendition const & nr,
	DC_Point const		*start,
	DC_Point const		*end,
	int						row_bytes,
	unsigned short const	*rasters) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		int						width, height;

		width  = (int)end->x - (int)start->x + 1;
		height = (int)start->y - (int)end->y + 1;

		fprintf (state->fp, "\ndraw_dc_mapped16_rasters (%d rows)\n", height);

		if (nr->transform_rendition->_hoops_CPA != state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_ARGGS);
		else
			_hoops_CRGGS (&state->transform);

		_hoops_SAGGS (state->fp, 1, start, nr, "start");
		_hoops_SAGGS (state->fp, 1, end, nr, "end");
		_hoops_APGGS (&state->_hoops_PSSSC, (long)width * (long)height);
		_hoops_APGGS (&state->_hoops_HSSSC, (long)height);

		if (row_bytes == 0)
			row_bytes = width * sizeof (unsigned short);

		fprintf (state->fp, "\tcolor indexes:\n");
		_hoops_RGGA (height-- == 0) {
			unsigned short const	*_hoops_SCGCR;
			unsigned short const	*_hoops_HSGCR;

			fprintf (state->fp, "\t\t");

			_hoops_SCGCR = rasters;
			_hoops_HSGCR = rasters + width;
			_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR)
				fprintf (state->fp, "%3d ", *_hoops_SCGCR++);
			rasters = (unsigned short const *) ((unsigned char const *)rasters +
												row_bytes);

			fprintf (state->fp, "\n");
		}
	}
}


/*
 * _hoops_SRAC
 */
local void draw_dc_rgb32_rasters (
	Net_Rendition const & nr,
	DC_Point const		*start,
	DC_Point const		*end,
	int						row_bytes,
	RGBAS32 const			*rasters) {
	_hoops_HCSSC alter		*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		int						width, height;

		width  = (int)end->x - (int)start->x + 1;
		height = (int)start->y - (int)end->y + 1;

		fprintf (state->fp, "\ndraw_dc_rgb32_rasters (%d rows)\n", height);

		if (nr->transform_rendition->_hoops_CPA != state->transform._hoops_SSAC)
			_hoops_PRGGS (nr, _hoops_ARGGS);
		else
			_hoops_CRGGS (&state->transform);

		_hoops_SAGGS (state->fp, 1, start, nr, "start");
		_hoops_SAGGS (state->fp, 1, end, nr, "end");
		_hoops_APGGS (&state->_hoops_PSSSC, (long)width * (long)height);
		_hoops_APGGS (&state->_hoops_HSSSC, (long)height);

		if (row_bytes == 0)
			row_bytes = width * sizeof (RGBAS32);

		fprintf (state->fp, "\tRGBA values:\n");
		_hoops_RGGA (height-- == 0) {
			RGBAS32 const	*_hoops_SCGCR;
			RGBAS32 const	*_hoops_HSGCR;

			_hoops_SCGCR = rasters;
			_hoops_HSGCR = rasters + width;
			_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR) {
				fprintf (state->fp, "\t\t(%3d,%3d,%3d,%3d)\n",
						 _hoops_SCGCR->r, _hoops_SCGCR->g, _hoops_SCGCR->b, _hoops_SCGCR->a);
				++_hoops_SCGCR;
			}
			rasters = (RGBAS32 const *)((unsigned char const *)rasters +
										 row_bytes);
		}
	}
}


/*
 * _hoops_SRAC
 */
local void draw_overlay_list (
	Net_Rendition const & nr) {
	_hoops_HCSSC alter				*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		fprintf (state->fp, "\ndraw_overlay_list\n");
		_hoops_APGGS (&state->draw_overlay_list, 1L);
	}

	/* _hoops_HHSPR _hoops_GPP _hoops_HGIIP _hoops_CR _hoops_CCH _hoops_HRIRR _hoops_HAIR _hoops_AGRP */
	state->transform._hoops_SSAC = (_hoops_GARRR)0;
	state->face._hoops_SSAC = (_hoops_GARRR)0;
	state->line._hoops_SSAC = (_hoops_GARRR)0;
	state->text._hoops_SSAC = (_hoops_GARRR)0;

	HD_Standard_Draw_Overlay_List (nr);

	/* _hoops_HHSPR _hoops_GPP _hoops_HGIIP _hoops_CR _hoops_CCH _hoops_HRIRR _hoops_HAIR _hoops_AGRP */
	state->transform._hoops_SSAC = (_hoops_GARRR)0;
	state->face._hoops_SSAC = (_hoops_GARRR)0;
	state->line._hoops_SSAC = (_hoops_GARRR)0;
	state->text._hoops_SSAC = (_hoops_GARRR)0;
}


/*
 * _hoops_SRAC
 */
local void _hoops_SCPGR (
	Net_Rendition const & nr) {
	_hoops_HCSSC alter				*state = _hoops_SSSSC (nr);

	if (state->fp != null) {
		fprintf (state->fp, "\nundraw_overlay_list\n");
		_hoops_APGGS (&state->_hoops_SCPGR, 1L);
	}

	/* _hoops_HHSPR _hoops_GPP _hoops_HGIIP _hoops_CR _hoops_CCH _hoops_HRIRR _hoops_HAIR _hoops_AGRP */
	state->transform._hoops_SSAC = (_hoops_GARRR)0;
	state->face._hoops_SSAC = (_hoops_GARRR)0;
	state->line._hoops_SSAC = (_hoops_GARRR)0;
	state->text._hoops_SSAC = (_hoops_GARRR)0;

	HD_Standard_UnDraw_Overlay_List (nr);

	/* _hoops_HHSPR _hoops_GPP _hoops_HGIIP _hoops_CR _hoops_CCH _hoops_HRIRR _hoops_HAIR _hoops_AGRP */
	state->transform._hoops_SSAC = (_hoops_GARRR)0;
	state->face._hoops_SSAC = (_hoops_GARRR)0;
	state->line._hoops_SSAC = (_hoops_GARRR)0;
	state->text._hoops_SSAC = (_hoops_GARRR)0;
}


/*
 * _hoops_PGAA
 */
local void _hoops_IIGGS (
	_hoops_ACSSC alter		*i) {

	/* _hoops_PHIGR _hoops_GPISR _hoops_IIGR _hoops_CRAPH _hoops_IH _hoops_GII _hoops_GPRR _hoops_IIGR _hoops_CIIA */
	*i += (_hoops_ACSSC)1;
}


/*
 * _hoops_SRAC
 */
local bool _hoops_HSCSP (
	Display_Context const		*dc,
	int alter						*button,
	int alter						*x,
	int alter						*y) {
	_hoops_HCSSC alter				*state = _hoops_CSSSC (dc);

	_hoops_IIGGS (&state->_hoops_HSCSP);

	if (state->fp != null &&
		!BIT (dc->options._hoops_IRARR, _hoops_HPSSC))
		fprintf (state->fp, "\nrequest_location: %ld\n",
				 state->_hoops_HSCSP);

	*button = ((state->_hoops_HSCSP % 10) > 7) ? 1 : 0;
	if (BIT (dc->options._hoops_IRARR, _hoops_APSSC)) {
		*x = *y = (int)state->_hoops_HSCSP * 100 % 600;
	}
	else {
		*x = *y = (int)state->_hoops_HSCSP * 100 % 800;
	}

	if (state->fp != null &&
		!BIT (dc->options._hoops_IRARR, _hoops_HPSSC)) {
		fprintf (state->fp, "\tmouse coordinates returned = %d %d\n", *x, *y);
		fprintf (state->fp, "\tmouse button returned = %d\n", *button);
	}

	return true;
}


/*
 * _hoops_SRAC
 */
local bool _hoops_ISCSP (
	Display_Context const		*dc,
	int alter						*button,
	int alter						*status) {
	_hoops_HCSSC alter				*state = _hoops_CSSSC (dc);

	_hoops_IIGGS (&state->_hoops_ISCSP);

	if (state->fp != null &&
		!BIT (dc->options._hoops_IRARR, _hoops_HPSSC))
		fprintf (state->fp, "\nrequest_keyboard: %ld\n",
				 state->_hoops_ISCSP);

	if ((state->_hoops_ISCSP % 4) == 0) {
		if (state->_hoops_ISCSP < 80)
			*button = 'A';
		else if (state->_hoops_ISCSP < 96)
			*button = 'q';
		else
			*button = _hoops_PHSSC;
		*status = 0;

		HI_Queue_Keyboard_Event ((_hoops_GGAGR alter *)dc->_hoops_GHRI,
								 *button, *status);

		if (state->fp != null &&
			!BIT (dc->options._hoops_IRARR, _hoops_HPSSC))
			fprintf (state->fp, "\tkeystroke queued = '%c' %d\n",
					 *button, *status);
	}
	else {
		*button = 0;
		*status = 0;
	}

	return false;
}


/*
 * _hoops_SRAC
 */
local void _hoops_SCCSR (
	Display_Context const		*dc,
	unsigned int					r,
	unsigned int					g,
	unsigned int					b,
	int								index) {
	_hoops_HCSSC alter				*state = _hoops_CSSSC (dc);

	if (state->fp != null &&
		!BIT (dc->options._hoops_IRARR, _hoops_IPSSC)) {
		if (!state->_hoops_CCSSC) {
			fprintf (state->fp, "\nset_device_color_map\n");
			state->_hoops_CCSSC = true;
		}

		fprintf (state->fp, "\tentry %3d set to %3d %3d %3d\n",
				 index, r, g, b);
	}
}


/*
 * _hoops_SRAC
 */
local void find_all_fonts (
	Display_Context alter		*dc) {
	_hoops_HCSSC alter				*state = _hoops_CSSSC (dc);

	if (state->fp != null)
		fprintf (state->fp, "\nfind_all_fonts\n");

	HD_Record_Font (dc, "Times-Roman", "", 0.0f, _hoops_IACSR(0.6759));
	HD_Record_Font (dc, "Times-Italic", "", 0.0f, _hoops_IACSR(0.6720));
	HD_Record_Font (dc, "Times-Bold", "", 0.0f, _hoops_IACSR(0.6809));
	HD_Record_Font (dc, "Times-BoldItalic", "", 0.0f, _hoops_IACSR(0.6759));
	HD_Record_Font (dc, "Helvetica", "", 0.0f, _hoops_IACSR(0.7290));
	HD_Record_Font (dc, "Helvetica-Oblique","", 0.0f, _hoops_IACSR(0.7290));
	HD_Record_Font (dc, "Helvetica-Bold", "", 0.0f, _hoops_IACSR(0.7290));
	HD_Record_Font (dc, "Helvetica-BoldOblique","", 0.0f, _hoops_IACSR(0.7290));
	HD_Record_Font (dc, "Courier", "", 0.0f, _hoops_IACSR(0.7290));
	HD_Record_Font (dc, "Courier-Oblique", "", 0.0f, _hoops_IACSR(0.7290));
	HD_Record_Font (dc, "Courier-Bold", "", 0.0f, _hoops_IACSR(0.7290));
	HD_Record_Font (dc, "Courier-BoldOblique", "", 0.0f, _hoops_IACSR(0.7290));

	HD_Mark_Font_As_Generic (dc, "Times-Roman", GFN_ROMAN);
	HD_Mark_Font_As_Generic (dc, "Helvetica", GFN_SANS_SERIF);
	HD_Mark_Font_As_Generic (dc, "Courier", GFN_TYPEWRITER);

	HD_Mark_Font_As_Transformable (dc, "Times-Roman", _hoops_HAGGH);
	HD_Mark_Font_As_Transformable (dc, "Times-Italic", _hoops_HAGGH);
	HD_Mark_Font_As_Transformable (dc, "Times-Bold", _hoops_HAGGH);
	HD_Mark_Font_As_Transformable (dc, "Times-BoldItalic", _hoops_HAGGH);
	HD_Mark_Font_As_Transformable (dc, "Helvetica", _hoops_HAGGH);
	HD_Mark_Font_As_Transformable (dc, "Helvetica-Oblique", _hoops_HAGGH);
	HD_Mark_Font_As_Transformable (dc, "Helvetica-Bold", _hoops_HAGGH);
	HD_Mark_Font_As_Transformable (dc, "Helvetica-BoldOblique", _hoops_HAGGH);
	HD_Mark_Font_As_Transformable (dc, "Courier", _hoops_HAGGH);
	HD_Mark_Font_As_Transformable (dc, "Courier-Oblique", _hoops_HAGGH);
	HD_Mark_Font_As_Transformable (dc, "Courier-Bold", _hoops_HAGGH);
	HD_Mark_Font_As_Transformable (dc, "Courier-BoldOblique", _hoops_HAGGH);
	HD_Mark_Font_As_Transformable (dc, "Symbol", _hoops_HAGGH);
}



/*
 * _hoops_SRAC
 */
local bool measure_char(
	Net_Rendition const & nr,
	Font_Instance const * instance,
	Karacter _hoops_IPCSR,
	float alter *_hoops_GGGS,
	bool alter *_hoops_CPCSR,
	void ** _hoops_SPCSR) {

	UNREFERENCED(nr);
	UNREFERENCED(_hoops_IPCSR);

	*_hoops_CPCSR = false;

	if (instance->_hoops_ISISR < 2)
		*_hoops_GGGS = 1.0f;
	else
		*_hoops_GGGS = 0.7f * (float)instance->_hoops_ISISR;

	*_hoops_SPCSR=(void*)1;

	return true;
}

/*
 * _hoops_SRAC
 */
local void * load_font (
	Display_Context const		*dc,
	char const						*name,
	Font_Instance alter *		instance) {
	_hoops_HCSSC alter				*state = _hoops_CSSSC (dc);

	if (state->fp != null) {
		fprintf (state->fp, "\nload_font\n");

		fprintf (state->fp, "\tname = %s\n", name);

		fprintf (state->fp, "\tA height = %f\n", instance->_hoops_ISISR);

		fprintf (state->fp, "\tV space = %f\n", instance->_hoops_IGGGH);
	}

	return (void*)1;
}


/*
 * _hoops_SRAC
 */
local void unload_font (
	Display_Context const	*dc,
	Font_Instance alter		*instance) {
	_hoops_HCSSC alter		*state = _hoops_CSSSC (dc);

	UNREFERENCED (instance);

	if (state->fp != null)
		fprintf (state->fp, "\nunload_font\n");
}


/*
 * _hoops_SRAC
 */
local void _hoops_CAAGR (
	Net_Rendition const & nr,
	int								left,
	int								right,
	int								bottom,
	int								top) {
	Display_Context const		*dc = nr->_hoops_SRA;
	_hoops_HCSSC alter				*state = _hoops_CSSSC (dc);

	if (state->fp != null) {
		fprintf (state->fp, "\nclear_z_buffer\n");
		fprintf (state->fp, "\tleft	  = %d\n", left);
		fprintf (state->fp, "\tright  = %d\n", right);
		fprintf (state->fp, "\tbottom = %d\n", bottom);
		fprintf (state->fp, "\ttop	  = %d\n", top);
	}
}


/*
 * _hoops_SRAC
 */
local void get_physical_info (
	Display_Context alter		*dc) {
	_hoops_HCSSC alter				*state = _hoops_CSSSC (dc);

	if (state->fp != null) {
		fprintf (state->fp, "\nget_physical_info: debug = %d\n",
				 dc->options._hoops_IRARR);
		fprintf (state->fp,"\tdebug driver options include:\n");
		fprintf (state->fp,"\t\t   1 = show full rendition information\n");
		fprintf (state->fp,"\t\t   2 = has separate Gouraud triangle drawing\n");
		fprintf (state->fp,"\t\t   4 = has 24 bit color\n");
		fprintf (state->fp,"\t\t   8 = has 3D Z drawing capabilities\n");
		fprintf (state->fp,"\t\t  16 = uses VGA pixels (640 by 480)\n");
		fprintf (state->fp,"\t\t  32 = has input calls (mouse & keyboard)\n");
		fprintf (state->fp,"\t\t  64 = no input calls (mouse & keyboard)\n");
		fprintf (state->fp,"\t\t 128 = hides color map calls\n");
		fprintf (state->fp,"\t\t 256 = hides statistics\n");
		fprintf (state->fp,"\t\t 512 = hides test coverage analysis\n");
		fprintf (state->fp,"\t\t1024 = has gray scale\n");
		fprintf (state->fp,"\t\t2048 = has 16 bit color\n");
		fprintf (state->fp,"\t\t4096 = can do landscape\n");
		fprintf (state->fp,"\t\trecommended settings to simulate:\n");
		fprintf (state->fp,"\t\t\t2D   driver: debug =	0\n");
		fprintf (state->fp,"\t\t\t2.5D driver: debug =	2\n");
		fprintf (state->fp,"\t\t\t3D   driver: debug = 12\n");
	}

	/* _hoops_HHH _hoops_AGAH _hoops_RHPP _hoops_CHR _hoops_CHPGH, _hoops_HHH _hoops_CHR _hoops_IIHSR */
	if (BIT (dc->options._hoops_IRARR, _hoops_GPSSC)) {
		dc->_hoops_PGCC._hoops_PIHSR = _hoops_HIHSR;
		dc->_hoops_PGCC._hoops_AAPSR = 1<<24;
		dc->_hoops_PGCC._hoops_PCHSR = 256;

		dc->_hoops_ACPGR->draw_dc_rgb32_rasters = draw_dc_rgb32_rasters;
		if (state->fp != null)
			fprintf (state->fp, "\tcolor system = 24 bit direct color\n");
	}
	else if (BIT (dc->options._hoops_IRARR, _hoops_GHSSC)) {
		dc->_hoops_PGCC._hoops_PIHSR = _hoops_RIIHP;
		dc->_hoops_PGCC._hoops_AAPSR = 2;
		dc->_hoops_PGCC._hoops_PCHSR = 2;

		dc->_hoops_ACPGR->_hoops_SCCSR = _hoops_SCCSR;
		dc->_hoops_ACPGR->_hoops_CCCGA = _hoops_CCCGA;
		if (state->fp != null)
			fprintf (state->fp, "\tcolor system = 2 gray scale color\n");
	}
	else if (BIT (dc->options._hoops_IRARR, _hoops_RHSSC)) {
		dc->_hoops_PGCC._hoops_PIHSR = _hoops_SIHSR;
		dc->_hoops_PGCC._hoops_AAPSR = 512;
		dc->_hoops_PGCC._hoops_PCHSR = 256;

		dc->_hoops_ACPGR->_hoops_SCCSR = _hoops_SCCSR;
		dc->_hoops_ACPGR->_hoops_PSCGA = _hoops_PSCGA;
		if (state->fp != null)
			fprintf (state->fp, "\tcolor system = 512 mapped color\n");
	}
	else {
		dc->_hoops_PGCC._hoops_PIHSR = _hoops_SIHSR;
		dc->_hoops_PGCC._hoops_AAPSR = 256;
		dc->_hoops_PGCC._hoops_PCHSR = 256;

		dc->_hoops_ACPGR->_hoops_SCCSR = _hoops_SCCSR;
		dc->_hoops_ACPGR->_hoops_CCCSR = _hoops_CCCSR;
		if (state->fp != null)
			fprintf (state->fp, "\tcolor system = 256 mapped color\n");
	}

	/* _hoops_HHH _hoops_SPSIR _hoops_HS _hoops_AHCR _hoops_PSCA, _hoops_IHAGH _hoops_ARIPR _hoops_AA _hoops_HAR */
	if (BIT (dc->options._hoops_IRARR, _hoops_RPSSC)) {
		dc->_hoops_PGCC._hoops_HASHP = 24;
		if (dc->_hoops_PGCC._hoops_HASHP > 0)
			dc->flags &= ~_hoops_AASHP;
		else
			dc->flags |= _hoops_AASHP;
		dc->flags |= _hoops_RAAGH;
		dc->_hoops_PGCC._hoops_HGCC = 24;
		dc->_hoops_PGCC._hoops_ACPGH = 24;
		if (state->fp != null)
			fprintf (state->fp, "\tZ buffer depth = %d\n",
					 dc->_hoops_PGCC._hoops_HASHP);
	}

	/* _hoops_HHH _hoops_SPSIR _hoops_PAH _hoops_RGHH _hoops_PPIC _hoops_HIPH _hoops_SSPP */
	if (BIT (dc->options._hoops_IRARR, _hoops_SASSC)) {
		dc->_hoops_ACPGR->draw_dc_gouraud_polytriangle = draw_dc_gouraud_polytriangle;
		if (state->fp != null)
			fprintf (state->fp, "\thas Gouraud polytriangle routine\n");
	}

	dc->_hoops_PGCC._hoops_ARISR.x = 0;
	dc->_hoops_PGCC._hoops_ARISR.y = 0;

	/* _hoops_SGH 1280 _hoops_HPP 1024 _hoops_HCCPR _hoops_SAACI 640 _hoops_HPP 480 _hoops_HRGR _hoops_HGRC */
	if (BIT (dc->options._hoops_IRARR, _hoops_APSSC)) {
		dc->_hoops_PGCC._hoops_PRPSR.x = 640;
		dc->_hoops_PGCC._hoops_PRPSR.y = 480;
		if (state->fp != null)
			fprintf (state->fp, "\tpixels = 640 by 480\n");
		dc->_hoops_PGCC.size.x = 25.4f *
							  (float)dc->_hoops_PGCC._hoops_PRPSR.x /
							  (float)dc->_hoops_PGCC._hoops_PRPSR.y;
		dc->_hoops_PGCC.size.y = 25.4f;
	}
	else if (dc->options._hoops_SPHSR.x != -1) {
		float width = 8.5f;
		float height = 11.0f;
		float _hoops_HGII = 150;

		if (dc->options._hoops_SPHSR.x != -1) {
			width = dc->options._hoops_SPHSR.x / 2.54f;
			height = dc->options._hoops_SPHSR.y / 2.54f;
		}

		dc->_hoops_PGCC._hoops_PRPSR.x = (int) (_hoops_HGII * width);
		dc->_hoops_PGCC._hoops_PRPSR.y = (int) (_hoops_HGII * height);
		dc->_hoops_PGCC.size.x = width * 2.54;
		dc->_hoops_PGCC.size.y = height * 2.54;
	}
	else {
		dc->_hoops_PGCC._hoops_PRPSR.x = 1280;
		dc->_hoops_PGCC._hoops_PRPSR.y = 1024;
		if (state->fp != null)
			fprintf (state->fp, "\tpixels = 1280 by 1024\n");
		dc->_hoops_PGCC.size.x = 25.4f *
							  (float)dc->_hoops_PGCC._hoops_PRPSR.x /
							  (float)dc->_hoops_PGCC._hoops_PRPSR.y;
		dc->_hoops_PGCC.size.y = 25.4f;
	}


	if (state->fp != null)
		fprintf (state->fp, "\tphysical size = %.2f by %.2f cm\n",
				 dc->_hoops_PGCC.size.x,
				 dc->_hoops_PGCC.size.y);

	dc->_hoops_PGCC.driver_type = "Printf";
	dc->_hoops_PGCC._hoops_SCHSR = "$Revision: 1.282 $";
	dc->_hoops_PGCC.flags &= ~_hoops_HSHSR;
	if (BIT (dc->options._hoops_IRARR, _hoops_PPSSC)) {
		dc->_hoops_PGCC.flags |= _hoops_RSHSR;
		dc->_hoops_PGCC.flags |= _hoops_PSHSR;
		dc->_hoops_ACPGR->_hoops_HSCSP = _hoops_HSCSP;
		dc->_hoops_ACPGR->_hoops_ISCSP = _hoops_ISCSP;
		if (state->fp != null)
			fprintf (state->fp, "\thas mouse and keyboard\n");
	}
	else {
		dc->_hoops_PGCC.flags &= ~_hoops_RSHSR;
		dc->_hoops_PGCC.flags &= ~_hoops_PSHSR;
		if (state->fp != null)
			fprintf (state->fp, "\tno mouse nor keyboard\n");
	}

	dc->_hoops_PGCC._hoops_ICHSR = "debugging printout";
	if (BIT (dc->options._hoops_IRARR, _hoops_AHSSC)) {
		dc->_hoops_PGCC.flags |= _hoops_ISHSR;
		if (state->fp != null)
				fprintf (state->fp, "\tcan handle landscape orientation\n");
	}
	else {
		dc->_hoops_PGCC.flags &= ~_hoops_ISHSR;
		if (state->fp != null)
				fprintf (state->fp, "\tcannot handle landscape orientation\n");
	}

}


/*
 * _hoops_SRAC
 */
local void get_current_info (
	Display_Context alter		*dc) {
	_hoops_HCSSC alter				*state = _hoops_CSSSC (dc);

	if (state->fp != null)
		fprintf (state->fp, "\nget_current_info\n");

	/*
	 * _hoops_CRGH _hoops_SGGGS _hoops_III _hoops_GPP _hoops_SRS _hoops_AASA _hoops_RAS _hoops_CCAH _hoops_SIHC
	 */
	state->_hoops_CCSSC = false;

	/*
	 * _hoops_ARR 3D (_hoops_AHCR _hoops_SRHR) _hoops_HRGR _hoops_HGRC, _hoops_RH _hoops_RHPP _hoops_SSCP _hoops_AAPI,
	 * _hoops_PGRC, _hoops_PPR _hoops_CCGI
	 */
	if (BIT (dc->options._hoops_IRARR, _hoops_RPSSC)) {
		dc->_hoops_ACPGR->draw_3d_ellipse = draw_3d_ellipse;
		dc->_hoops_ACPGR->draw_3d_elliptical_arc = draw_3d_elliptical_arc;
		dc->_hoops_ACPGR->draw_3d_marker = draw_3d_marker;
		dc->_hoops_ACPGR->draw_3d_polyline = draw_3d_polyline;
		dc->_hoops_ACPGR->draw_3d_polygon = draw_3d_polygon;
		dc->_hoops_ACPGR->draw_3d_polyedge = draw_3d_polyedge;
		dc->_hoops_ACPGR->draw_3d_tristrip = draw_3d_tristrip;
		dc->_hoops_ACPGR->draw_3d_polymarker = draw_3d_polymarker;

		dc->_hoops_ACPGR->_hoops_IGSSP = HD_Std_Create_Frame_Buffer;
		dc->_hoops_ACPGR->_hoops_CGSSP = HD_Std_Display_Frame_Buffer;
		dc->_hoops_ACPGR->_hoops_SGSSP = HD_Std_Destroy_Frame_Buffer;
	}
	else {
		dc->_hoops_ACPGR->draw_3d_ellipse = HD_Std_3D_Ellipse;
		dc->_hoops_ACPGR->draw_3d_elliptical_arc = HD_Std_3D_Elliptical_Arc;
		dc->_hoops_ACPGR->draw_3d_marker = HD_Std_3D_Marker;
		dc->_hoops_ACPGR->draw_3d_polyline = HD_Std_3D_Polyline;
		dc->_hoops_ACPGR->draw_3d_polygon = HD_Std_3D_Polygon;
		dc->_hoops_ACPGR->draw_3d_polyedge = HD_Std_3D_Polyedge;
		dc->_hoops_ACPGR->draw_3d_tristrip = HD_Std_3D_Tristrip;
		dc->_hoops_ACPGR->draw_3d_polymarker = HD_Std_3D_Polymarker;

		dc->_hoops_ACPGR->_hoops_IGSSP = _hoops_IGSSP;
		dc->_hoops_ACPGR->_hoops_CGSSP = _hoops_CGSSP;
		dc->_hoops_ACPGR->_hoops_SGSSP = _hoops_SGSSP;
	}
	if (dc->options._hoops_SPHSR.x != -1) {
		float width = 8.5f;
		float height = 11.0f;
		float _hoops_HGII = dc->options._hoops_GHHSR;

		if (dc->options._hoops_SPHSR.x != -1) {
			width = dc->options._hoops_SPHSR.x / 2.54f;
			height = dc->options._hoops_SPHSR.y / 2.54f;
		}

		dc->_hoops_PGCC._hoops_PRPSR.x = (int) (_hoops_HGII * width);
		dc->_hoops_PGCC._hoops_PRPSR.y = (int) (_hoops_HGII * height);
		dc->_hoops_PGCC.size.x = width * 2.54;
		dc->_hoops_PGCC.size.y = height * 2.54;
		dc->options._hoops_HPHRP = false;
		dc->current.extent.left = 0;
		dc->current.extent.right = dc->_hoops_PGCC._hoops_PRPSR.x -1;
		dc->current.extent.bottom = 0;
		dc->current.extent.top = dc->_hoops_PGCC._hoops_PRPSR.y -1;
	}
}


/*
 * _hoops_SRAC (_hoops_ARSAR _hoops_AIH _hoops_ACSCC)
 */
local void _hoops_RSCSR (
	_hoops_APARR alter &		_hoops_RRCI) {

	/* _hoops_SISS */
	_hoops_RRCI->start_device			= start_device;
	_hoops_RRCI->stop_device				= stop_device;
	_hoops_RRCI->get_physical_info		= get_physical_info;
	_hoops_RRCI->get_current_info		= get_current_info;
	_hoops_RRCI->init_picture			= init_picture;
	_hoops_RRCI->finish_picture			= finish_picture;
	_hoops_RRCI->init_update				= init_update;
	_hoops_RRCI->finish_update			= finish_update;

	/* _hoops_RPPS */
	_hoops_RRCI->get_outer_window		= get_outer_window;
	_hoops_RRCI->free_outer_window		= free_outer_window;
	_hoops_RRCI->_hoops_RSCSP		= _hoops_RSCSP;

	/* 2D _hoops_ASCA */
	_hoops_RRCI->draw_dc_ellipse			   = draw_dc_ellipse;
	_hoops_RRCI->_hoops_CCISR	   = _hoops_CCISR;
	_hoops_RRCI->_hoops_SCISR	   = _hoops_SCISR;
	_hoops_RRCI->draw_dc_polyline		   = draw_dc_polyline;
	_hoops_RRCI->draw_dc_face			   = draw_dc_face;
	_hoops_RRCI->draw_dc_colorized_face	   = draw_dc_colorized_face;
	_hoops_RRCI->draw_dc_polytriangle	   = draw_dc_polytriangle;
	_hoops_RRCI->draw_dc_colorized_polytriangle = draw_dc_colorized_polytriangle;
	_hoops_RRCI->draw_dc_rectangle		   = draw_dc_rectangle;
	_hoops_RRCI->draw_dc_polydot			   = draw_dc_polydot;

	/* _hoops_HCGR */
	_hoops_RRCI->draw_dc_text			= draw_dc_text;
	_hoops_RRCI->find_all_fonts			= find_all_fonts;
	_hoops_RRCI->load_font				= load_font;
	_hoops_RRCI->unload_font				= unload_font;
	_hoops_RRCI->measure_char			= measure_char;

	/* _hoops_PIHHR _hoops_ASCA */
	_hoops_RRCI->draw_overlay_list		= draw_overlay_list;
	_hoops_RRCI->_hoops_SCPGR		= _hoops_SCPGR;

	/* 3D _hoops_ASCA */
	_hoops_RRCI->_hoops_CAAGR			= _hoops_CAAGR;
}


/*
 * _hoops_IAAAH _hoops_PPICR
 */
extern "C" bool HC_CDECL HD_Printf_Driver (
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED (request_info);
	return HD_Connect_Standard_Driver (_hoops_RIGC, _hoops_GHRI, request, _hoops_RSCSR);
}

/*
 * _hoops_ASCSR _hoops_RARP _hoops_PPSR (_hoops_IGI _hoops_GPP _hoops_PSCSR)
 */
_hoops_HSCSR (_hoops_RSCSR)

#endif /* _hoops_CIGGS */




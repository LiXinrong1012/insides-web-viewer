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
 * $Id: obf_tmp.txt 1.212 2010-11-30 21:47:28 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hc_proto.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "please.h"
#include "hversion.h"


#ifdef NUTCRACKER
#include <stdio.h>
#include <stdlib.h>
#ifndef FALSE
#define FALSE 0
#endif
extern "C" _hoops_ICIHS();
#endif

#ifdef OSX_SYSTEM
extern "C" bool HC_CDECL HD_Cocoa_OpenGL_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter * _hoops_GHRI, int request, void * request_info);
#endif

extern "C" bool HC_CDECL HD_MGL_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter * _hoops_GHRI, int request, void * request_info);

GLOBAL_FUNCTION bool HD_No_Driver (
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_GGAGR const *			_hoops_GHRI,
	int						request,
	char const *			_hoops_HSS) 
{
	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (_hoops_GHRI);

	if (request == _hoops_GAGRH)
		return false;

#ifdef WIN32_SYSTEM
	if (request == _hoops_AAGSC) {
		char	_hoops_CCIHS[MAX_ERRMSG];
		char	_hoops_SCIHS[MAX_ERRMSG];

		Sprintf_S (_hoops_CCIHS, "The '%s' driver was requested but is not available in this Hoops",_hoops_HSS);
		Sprintf_SD (_hoops_SCIHS, "Is '%s%d.hdi' in a directory specified in your PATH?", _hoops_HSS, HOOPS_VERSION);
		HE_ERROR2 (HEC_DRIVER, HES_NOT_AVAILABLE, _hoops_CCIHS, _hoops_SCIHS);
	}
#else
	if (request == _hoops_AAGSC)
		HE_ERROR (HEC_DRIVER, HES_NOT_AVAILABLE,
			Sprintf_S (null,"The '%s' driver was requested but is not available in this Hoops",_hoops_HSS));
#endif /* _hoops_HIHPH */

	return false;
}



local Attribute *_hoops_GSIHS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR)
{
	_hoops_GGAGR const *	_hoops_RSIHS = (_hoops_GGAGR const *)_hoops_CPACR;
	_hoops_GGAGR alter *	_hoops_ASIHS = (_hoops_GGAGR alter *)_hoops_SPACR;

	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (_hoops_RSIHS);

	_hoops_ASIHS->connected_action = _hoops_ASIHS->action;
	_hoops_ASIHS->type = HK_DRIVER;
	_hoops_ASIHS->owner = (_hoops_CRCP*)item;

	HI_Init_Driver (_hoops_RIGC, _hoops_ASIHS, false);

	return _hoops_ASIHS;
}


GLOBAL_FUNCTION void HI_Init_Driver (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR *					_hoops_GHRI,
	bool					_hoops_CHCIH) 
{
	/* _hoops_CCGR _hoops_GIPCR _hoops_IAII */
	_hoops_GHRI->_hoops_CGPIR = _hoops_IRGSC|_hoops_ISRPH;

	if (_hoops_CHCIH)
		_hoops_GHRI->_hoops_CGPIR |= _hoops_SISHA;

	/* _hoops_GGCR _hoops_IS _hoops_GHARR _hoops_PCSHA _hoops_HIGR - */
	/* _hoops_PPSI _hoops_SCH _hoops_RRCGC _hoops_RCSPR _hoops_HIGGR - _hoops_HIS _hoops_PSIHS _hoops_GRS _hoops_IPHR _hoops_RPHR */

	_hoops_GGAGR **	_hoops_ASRGR = &HOOPS_WORLD->_hoops_CISHA;
	_hoops_RGGA (*_hoops_ASRGR == null) _hoops_ASRGR = &(*_hoops_ASRGR)->_hoops_CISHA;
	*_hoops_ASRGR = _hoops_GHRI;
	_hoops_GHRI->_hoops_CISHA = null;
	_hoops_GHRI->_hoops_RAIAP = _hoops_ASRGR;

	/* _hoops_GSRS _hoops_SPCS _hoops_RPPS _hoops_IS _hoops_CRCC _hoops_AIIAP _hoops_HSIHS _hoops_CGPR _hoops_IIH _hoops_GPGH'_hoops_RA
	 * _hoops_IRS _hoops_HPHR _hoops_RPPS _hoops_HPGR _hoops_AACAR.
	 */
	_hoops_GHRI->_hoops_CSGPR.type = HK_WINDOW;
	_hoops_GHRI->_hoops_CSGPR._hoops_RCHS.left = -1.0f;
	_hoops_GHRI->_hoops_CSGPR._hoops_RCHS.right = 1.0f;
	_hoops_GHRI->_hoops_CSGPR._hoops_RCHS.bottom = -1.0f;
	_hoops_GHRI->_hoops_CSGPR._hoops_RCHS.top = 1.0f;

	_hoops_HISAA (_hoops_RIGC, _hoops_GHRI, _hoops_RAGRH, null);
}

GLOBAL_FUNCTION _hoops_GGAGR * HI_Create_Actor(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP, 
	Driver_Action			action)
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_GGAGR * _hoops_GHRI;
	ZALLOC (_hoops_GHRI, _hoops_GGAGR);
	_hoops_GHRI->action = action;
	if (!HI_Set_Attribute(_hoops_RIGC, (_hoops_HPAH*)_hoops_SRCP, HK_DRIVER, _hoops_GSIHS, _hoops_GHRI)) {
		FREE (_hoops_GHRI, _hoops_GGAGR);
		_hoops_GHRI = null;
	}
	return _hoops_GHRI;
}


struct _hoops_ISIHS {
	Driver_Action		_hoops_CSIHS;
};


GLOBAL_FUNCTION void HI_Attach_Automatic_Driver (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP alter *			_hoops_SRCP) 
{

	Attribute const *	_hoops_ASGPR = _hoops_SRCP->owner->_hoops_IPPGR;
	while (_hoops_ASGPR->type != HK_DRIVER)
		_hoops_ASGPR = _hoops_ASGPR->next;

	_hoops_GGAGR alter *	driver = (_hoops_GGAGR alter *)_hoops_ASGPR;

	_hoops_ISIHS alter *	_hoops_PAAIR = (_hoops_ISIHS alter *)driver->_hoops_PPRPR;

	HI_Create_Actor(_hoops_RIGC, _hoops_SRCP, _hoops_PAAIR->_hoops_CSIHS);
}




local bool _hoops_SSIHS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (request_info);

	switch (request) {
		case _hoops_RAGRH: {
			struct _hoops_ISIHS alter   *_hoops_PAAIR;

			ZALLOC (_hoops_PAAIR, struct _hoops_ISIHS);

			_hoops_GHRI->_hoops_PPRPR = (void alter *)_hoops_PAAIR;
		}	break;

		case _hoops_IAGSC: {
			struct _hoops_ISIHS alter   *_hoops_PAAIR;

			_hoops_PAAIR = (struct _hoops_ISIHS alter *)_hoops_GHRI->_hoops_PPRPR;

			FREE (_hoops_PAAIR, struct _hoops_ISIHS);

			_hoops_GHRI->_hoops_PPRPR = null;
			_hoops_GHRI->_hoops_CGPIR |= _hoops_SGPIR;
		}	break;

		case _hoops_AAGSC: {
		}	break;

		default: {
			return false;
		}		/* _hoops_IHSA; */
	}

	return true;
}


local void _hoops_GGCHS (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			name,
	Driver_Action			address)
{

	PUSHNAME(_hoops_RIGC);

	bool _hoops_RGCHS = address(_hoops_RIGC, 0, _hoops_GAGRH, 0);

	if (!_hoops_RGCHS &&
		HOOPS_WORLD->_hoops_IARPR != nullroutine) {

		Driver_Action	test = nullroutine;

		test = (*HOOPS_WORLD->_hoops_IARPR) (name);

		if (test != nullroutine) {
			_hoops_RGCHS = test(_hoops_RIGC, 0, _hoops_GAGRH,0);
			if (_hoops_RGCHS)
				address = test;
		}
	}

	if (_hoops_RGCHS) {
		if (HC_Open_Segment (name) != _hoops_SHSSR) { 

			_hoops_CRCP *	_hoops_SRCP = _hoops_RIGC->open_list->info.segment._hoops_IGRPR;

			HI_Create_Actor(_hoops_RIGC, _hoops_SRCP, _hoops_SSIHS);

			/* _hoops_SSS _hoops_SGS _hoops_RHPP _hoops_HRPR & _hoops_AGCHS _hoops_RH _hoops_GRGPR _hoops_GGR */
			/*** _hoops_RCASA ***/

			Attribute const *	_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR;
			while (_hoops_ASGPR->type != HK_DRIVER)
				_hoops_ASGPR = _hoops_ASGPR->next;

			_hoops_GGAGR alter *	driver = (_hoops_GGAGR alter *)_hoops_ASGPR;
			driver->_hoops_CGPIR = _hoops_GCSHA|_hoops_ARGSC;

			_hoops_ISIHS alter *	_hoops_PAAIR = (_hoops_ISIHS alter *)driver->_hoops_PPRPR;
			_hoops_PAAIR->_hoops_CSIHS = address;

			_hoops_PGRCA(_hoops_SRCP)->_hoops_PHSI |= _hoops_CGPSA;

			HC_Close_Segment ();
		}
	}
	POPNAME(_hoops_RIGC);
}


local bool _hoops_PGCHS (
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (request_info);

	if (request == _hoops_GAGRH)
		return true;

	if (request == _hoops_AAGSC)
		_hoops_ARGIP (HEC_START_DRIVERS, HES_DRIVER_ATTRIBUTE_MISSING,
					 Sprintf_P (null, "Segment '%p' should have a \"Driver\" attribute but doesn't.", _hoops_GHRI->owner),
					 "(On Update_Display, it was found within a generic 'drivers' segment.)",
					 "Are you sure your HOOPS_PICTURE value is correct?");

	return false;
}


/* "_hoops_IRAP" _hoops_CAGH _hoops_RHPP - _hoops_PGICR _hoops_HHHH _hoops_RHPP _hoops_RPGP */

GLOBAL_FUNCTION bool HD_Null_Driver (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (_hoops_GHRI);
	UNREFERENCED (request);
	UNREFERENCED (request_info);

	if (request == _hoops_GAGRH)
		return true;

	return false;
}


GLOBAL_FUNCTION void HD_Start_Drivers (
	_hoops_AIGPR *	_hoops_RIGC)
{

#ifdef NUTCRACKER
	char *_hoops_HGCHS;
#endif

	PUSHNAME(_hoops_RIGC);
	HC_Open_Segment ("?driver");
	POPNAME(_hoops_RIGC);

		PUSHNAME(_hoops_RIGC);
		HC_Open_Segment ("null"); 
			HI_Create_Actor(_hoops_RIGC, _hoops_RIGC->open_list->info.segment._hoops_IGRPR, HD_Null_Driver);
		HC_Close_Segment ();
		POPNAME(_hoops_RIGC);

		_hoops_GGCHS (_hoops_RIGC, "cgm",				HD_CGM3_Driver);
		_hoops_GGCHS (_hoops_RIGC, "cgm3",				HD_CGM3_Driver);
		_hoops_GGCHS (_hoops_RIGC, "hpgl",				HD_HPGL_Driver);
		_hoops_GGCHS (_hoops_RIGC, "hpgl2",			HD_HPGL2_Driver);
		_hoops_GGCHS (_hoops_RIGC, "image",			HD_Image_Driver);
		_hoops_GGCHS (_hoops_RIGC, "msw",				HD_MSW_Driver);
#if	!defined(WIN32_SYSTEM) || defined(EXCEED_BUILD)
		_hoops_GGCHS (_hoops_RIGC, "opengl",			HD_OpenGL_Driver);
#else
		_hoops_GGCHS (_hoops_RIGC, "opengl",			HD_Win32_OpenGL_Driver);
#endif
#if	!defined(WIN32_SYSTEM) || defined(EXCEED_BUILD)
		_hoops_GGCHS (_hoops_RIGC, "opengl2",			HD_OpenGL2_Driver);
#else
		_hoops_GGCHS (_hoops_RIGC, "opengl2",			HD_Win32_OpenGL2_Driver);
#endif
		_hoops_GGCHS (_hoops_RIGC, "postscript",		HD_PostScript_Driver);
		_hoops_GGCHS (_hoops_RIGC, "pdf",				HD_PDF_Driver);
		_hoops_GGCHS (_hoops_RIGC, "qt",				HD_QT_Driver);
		_hoops_GGCHS (_hoops_RIGC, "printf",			HD_Printf_Driver);
		_hoops_GGCHS (_hoops_RIGC, "quartz",			HD_Quartz_Driver);
#ifdef NUTCRACKER
		_hoops_GGCHS (_hoops_RIGC, "opengl",			HD_OpenGL_Driver);
		_hoops_HGCHS = getenv("CV_PLATFORM");
		if (_hoops_ICIHS() == FALSE)
			_hoops_GGCHS (_hoops_RIGC, "x11",			HD_X11_Driver);
		else if ((strcmp(_hoops_HGCHS,"OGL") == 0) || (strcmp(_hoops_HGCHS,"ogl") == 0))
			_hoops_GGCHS (_hoops_RIGC, "x11",			HD_OpenGL_Driver);
		else
			_hoops_GGCHS (_hoops_RIGC, "x11",			HD_X11_Driver);
#else
		_hoops_GGCHS (_hoops_RIGC, "x11",				HD_X11_Driver);
#endif
		_hoops_GGCHS (_hoops_RIGC, "direct3d",			HD_DX9_Driver);
		_hoops_GGCHS (_hoops_RIGC, "dx9",				HD_DX9_Driver);

#ifdef LINUX_SYSTEM
		_hoops_GGCHS (_hoops_RIGC, "mgl",				HD_MGL_Driver);
#endif
		_hoops_GGCHS (_hoops_RIGC, "whip2d",			HD_Whip2D_Driver);

#ifdef OSX_SYSTEM
		_hoops_GGCHS (_hoops_RIGC, "cocoa_opengl",		HD_Cocoa_OpenGL_Driver);
#endif

		// _hoops_AA _hoops_RGR _hoops_CGHI _hoops_HIS ?_hoops_SCHGR _hoops_HRIHS _hoops_ASSP'_hoops_RA _hoops_RGRIR _hoops_HPGP _hoops_RH _hoops_PGHC _hoops_CHR _hoops_IHGS _hoops_SAHGA
		_hoops_GGCHS (_hoops_RIGC, ".", _hoops_PGCHS);

	PUSHNAME(_hoops_RIGC);
	HC_Close_Segment ();

	/* _hoops_RAP _hoops_AAP _hoops_GPP _hoops_SPSIR. */
	HC_Begin_Segment_Search("/driver");

		char const * _hoops_IGCHS[] = {
			"cgm",
			"cgm3",
			"hpgl",
			"hpgl2",
			"pdf",
			"postscript",
			"whip2d",
		};

		char segname[100] = {""};

		while (HC_Find_Segment(segname)) {
			for (int i = 0; i < _hoops_GGAPR(_hoops_IGCHS); ++i) {
				if (strcmp(segname, _hoops_IGCHS[i]) == 0) {
					HC_Open_Segment(segname);
					HC_Set_Heuristics ("no incremental updates");
					HC_Set_Driver_Options ("no update interrupts, subscreen=(-1,1,-1,1), no control area");
					HC_Close_Segment();
				}
				else if (strcmp(segname, "image") == 0) {
					HC_Open_Segment(segname);
					HC_Set_Driver_Options ("no update interrupts, subscreen=(-1,1,-1,1), no control area");
					HC_Close_Segment();
				}
				else if (strcmp(segname, "msw") == 0) {
					/* _hoops_GRH _hoops_PSCSR _hoops_HCSP _hoops_GAR _hoops_SHIR */
					HC_Open_Segment(segname);
					HC_Set_Driver_Options ("landscape orientation=environment");
					HC_Close_Segment();
				}
			}
		}

	HC_End_Segment_Search();

	POPNAME(_hoops_RIGC);
}


local void _hoops_CGCHS (
	_hoops_CRCP const *		_hoops_SRCP) {
	Subsegment *		_hoops_GIPIA;
	Net_Rendition		nr;

	// _hoops_IRHRC _hoops_HCR _hoops_RIAH ?
	if (_hoops_SRCP->_hoops_CSC != null && (nr = _hoops_SRCP->_hoops_CSC->_hoops_APHGA) != null) {
		if (_hoops_SRCP->_hoops_CSC->_hoops_PSSIR() != null) {
			HD_Free_Frame_Buffer_Info (nr, _hoops_SRCP->_hoops_CSC->_hoops_PSSIR());
		}
	}

	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
		if (_hoops_GIPIA->type != _hoops_AGRPR)
			_hoops_CGCHS ((_hoops_CRCP const *)_hoops_GIPIA);
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);
}

local bool _hoops_SGCHS () {return false;}

GLOBAL_FUNCTION void HD_Kill_Driver (
	Display_Context const *		dc) {
	Display_Context alter *		_hoops_GRCHS;
	_hoops_GGAGR alter *				_hoops_GHRI;

	_hoops_GRCHS = (Display_Context alter *)dc;
	_hoops_GHRI = (_hoops_GGAGR alter *)dc->_hoops_GHRI;

	HI_Queue_Actor_Shutdown(dc->_hoops_GHRI, false);
	// _hoops_RGR _hoops_HRGR _hoops_PIGS _hoops_RGAR _hoops_HII _hoops_ASSA _hoops_IRS _hoops_RHPP _hoops_ISSSH _hoops_ASSS _hoops_RH _hoops_SHISR _hoops_AIHPC _hoops_IS _hoops_IHPS _hoops_IS _hoops_SRCH _hoops_GGGAH
	//_hoops_PCSHA->_hoops_RRCHS |= _hoops_ARCHS; 
	_hoops_GHRI->owner->_hoops_PHSI &= ~_hoops_HIHGP;

	_hoops_GRCHS->flags |= _hoops_IRAGH;

	_hoops_CGCHS (dc->_hoops_AAHSR);

	/*
	 * _hoops_PCICP _hoops_GGSR _hoops_ICRP _hoops_RHPP _hoops_PGSI _hoops_IS _hoops_PRCHS _hoops_HRCHS
	 * "_hoops_PGSA _hoops_RPP _hoops_HAR _hoops_ISAHA" _hoops_HCGC.	 _hoops_PAGA _hoops_SGS _hoops_SR _hoops_HHSP _hoops_AHPH
	 * _hoops_SICAR _hoops_PGAP _hoops_CGH _hoops_IIP _hoops_SHH _hoops_PIGS _hoops_GICS _hoops_APIC, _hoops_HGPP
	 * _hoops_GAR _hoops_APISR, _hoops_HIH _hoops_RGR _hoops_CGH _hoops_HAR _hoops_GIPPR _hoops_PA.
	 * _hoops_IRCHS _hoops_HHH _hoops_IIGR _hoops_RH _hoops_ISPP _hoops_PAPA _hoops_SICAR _hoops_GHCA _hoops_AHGS _hoops_PII
	 * _hoops_CRCHS, _hoops_HIH _hoops_SR _hoops_PAH'_hoops_RA _hoops_SHH _hoops_RCRR _hoops_CGPR _hoops_RGR _hoops_SIAS _hoops_HGCR _hoops_CPHR.
	 *
	 * _hoops_ICIA _hoops_AGCR _hoops_IS _hoops_ASSS "_hoops_HPHR" _hoops_AIHPC
	 *			_hoops_SRCHS
	 *			_hoops_GACHS
	 */

	_hoops_GRCHS->_hoops_ACPGR->start_device			= (_hoops_PSISP)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->get_physical_info		= (_hoops_ISISP)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->get_current_info		= (_hoops_CSISP)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->update					= (Update_Action)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->_hoops_SCCSP				= (_hoops_GSISP)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->_hoops_CHCI					= (_hoops_RSISP)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->_hoops_GSCSP					= (_hoops_ASISP)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->init_update			= (_hoops_SSISP)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->finish_update			= (_hoops_GGCSP)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->init_picture			= (_hoops_GCISP)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->finish_picture			= (_hoops_ACISP)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->get_outer_window		= (_hoops_RGCSP)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->_hoops_RSCSP	= (Resize_Outer_Window_Action)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->_hoops_ASCSP	= (_hoops_PGCSP)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->draw_3d_ellipse		= (_hoops_RCIGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_3d_elliptical_arc = (_hoops_PCIGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_3d_grid			= (_hoops_SCIGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_3d_marker			= (_hoops_SGCGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_3d_polyhedron		= (_hoops_SHIGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_3d_polyline		= (_hoops_GRCGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_3d_polygon		= (_hoops_ICIGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_3d_image			= (_hoops_ARCGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_3d_text			= (_hoops_PRCGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->_hoops_HRCGA			= (_hoops_IRCGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_3d_nurbs_curve	= (_hoops_RRCGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_3d_nurbs_surface	= (_hoops_RIIGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_3d_polycylinder	= (_hoops_IIIGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_3d_cylinder		= (_hoops_PIIGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_3d_sphere			= (_hoops_SIIGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->_hoops_SHCHP		= (_hoops_GIISP)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->draw_window			= (_hoops_HHISP)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_window_frame		= (_hoops_IHISP)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->draw_dc_ellipse		= (_hoops_HACGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->_hoops_CCISR = (_hoops_CACGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->_hoops_SCISR= (_hoops_IACGA)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->draw_dc_face			= (_hoops_SACGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_dc_colorized_face = (_hoops_GPCGA)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->_hoops_RPCGA		= (_hoops_APCGA)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->draw_dc_rectangle		= (_hoops_PPCGA)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->_hoops_HPCGA			= (_hoops_IPCGA)_hoops_SGCHS;


	_hoops_GRCHS->_hoops_ACPGR->draw_dc_text			= (_hoops_CPCGA)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->draw_3d_polyedge		= (_hoops_GACGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_3d_tristrip		= (_hoops_PACGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_3d_polymarker		= (_hoops_AACGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_3d_polyedge_from_tristrip = (_hoops_RACGA)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->_hoops_PPAS	= (_hoops_GACGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->_hoops_ARCI	= (_hoops_PACGA)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->draw_dc_polytriangle			= (_hoops_RHCGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_dc_colorized_polytriangle = (_hoops_AHCGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_dc_gouraud_polytriangle	= (_hoops_PHCGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_dc_phong_polytriangle				= (_hoops_HHCGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_dc_textured_polytriangle	= (_hoops_IHCGA)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->draw_dc_polyline				= (_hoops_CHCGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_dc_colorized_polyline		= (_hoops_SHCGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_dc_gouraud_polyline		= (_hoops_GICGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_dc_phong_polyline			= (_hoops_RICGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_dc_textured_polyline		= (_hoops_AICGA)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->draw_dc_polymarker				= (_hoops_PICGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_dc_colorized_polymarker	= (_hoops_HICGA)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->draw_dc_polydot				= (_hoops_IICGA)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->_hoops_CICGA			= (_hoops_SICGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->_hoops_GCCGA= (_hoops_RCCGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->_hoops_ACCGA	= (_hoops_PCCGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->_hoops_HCCGA = (_hoops_ICCGA)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->_hoops_CCCGA	= (_hoops_SCCGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->_hoops_GSCGA	= (_hoops_RSCGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->_hoops_CCCSR= (_hoops_ASCGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->_hoops_PSCGA	= (_hoops_HSCGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->draw_dc_rgb32_rasters	= (_hoops_ISCGA)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->_hoops_CSCGA		= (_hoops_SSCGA)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->_hoops_AGCSR		= (_hoops_GGSGA)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->draw_overlay_list		= (Draw_Overlay_List_Action)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->_hoops_SCPGR	= (Undraw_Overlay_List_Action)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->_hoops_HSCSP		= (_hoops_GACSP)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->_hoops_ISCSP		= (_hoops_RACSP)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->_hoops_SCCSR	= (_hoops_AACSP)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->find_all_fonts			= (_hoops_HACSP)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->load_font				= (_hoops_IACSP)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->unload_font			= (_hoops_CACSP)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->measure_char			= (_hoops_IGCSP)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->_hoops_CAAGR			= (_hoops_SACSP)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->_hoops_AGSSP		= (_hoops_GPCSP)_hoops_SGCHS;

	_hoops_GRCHS->_hoops_ACPGR->_hoops_PGSSP		= (_hoops_APCSP)_hoops_SGCHS;
	_hoops_GRCHS->_hoops_ACPGR->_hoops_HGSSP		= (_hoops_PPCSP)_hoops_SGCHS;
}

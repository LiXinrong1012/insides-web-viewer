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
 * $Id: obf_tmp.txt 1.1094.2.1 2011-01-27 05:21:47 jason Exp $
 */


#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "driver.h"
#include "please.h"
#include "tandt.h"
#include "phdraw.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "hidden.h"
#include "hl.h"
#include "patterns.h"
#include "adt.h"
#include "hc_proto.h"


#define _hoops_CGASS	0


// "_hoops_SHIR" _hoops_GGAS _hoops_IH _hoops_SGASS _hoops_SGS _hoops_AISI _hoops_PGSI
struct _hoops_GRASS : public _hoops_HIHCP {
	public:
		_hoops_GRASS (const char * _hoops_RRASS) : id(_hoops_RRASS) {}

		bool _hoops_SIHCP (Net_Rendition alter & nr, bool _hoops_PPHPP) alter {
			if (!_hoops_PPHPP) {
				_hoops_HGSGA (nr->_hoops_SRA, id);
			}
			return true;
		}

		const char * id;
};



local void _hoops_ARASS (
	Net_Rendition alter &	nr) {
	/* _hoops_AGSGR _hoops_GPP _hoops_AHCR _hoops_AHGGR */

	if (!_hoops_PGSC (nr->transform_rendition->_hoops_HGSC)) {
		_hoops_HHCR alter &		_hoops_IHCR = nr.Modify()->transform_rendition.Modify();

		switch (_hoops_IHCR->_hoops_HGSC) {
			case _hoops_CIPHP:
			case _hoops_PCPHP:		_hoops_IHCR->_hoops_HGSC = _hoops_ACPHP;	 break;

			case _hoops_RCPHP:		_hoops_IHCR->_hoops_HGSC = _hoops_GCPHP; break;

			case _hoops_SIPHP:		break;

			default: {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								   "Unexpected non-hidden transform type");
			}	break;
		}
	}
}


GLOBAL_FUNCTION void HD_Handle_FBI_Pending_Window (
	Net_Rendition const & 		nr) {
	_hoops_HCSIR alter *	_hoops_ICSIR = null;

	if (nr->_hoops_SAIR->_hoops_ASSIR != null)
		_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	if (_hoops_ICSIR != null) {
		if (_hoops_ICSIR->_hoops_AIIIP[0] == null ||
			nr->_hoops_SRA->_hoops_APHHP != null) {	/* _hoops_ICCGR _hoops_ARAR */
			HD_Setup_Frame_Buffer (nr);

			if (_hoops_ICSIR->_hoops_RSSCP != null) {
				_hoops_RGGSP (_hoops_ICSIR->_hoops_RSSCP);
				_hoops_ICSIR->_hoops_PCGSP = false;

				/* _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_SCH, _hoops_PAR _hoops_HPGR _hoops_CHGC _hoops_ISCP _hoops_RRGSP _hoops_GGR _hoops_SCH */
				_hoops_ICSIR->_hoops_RSSCP = null;

				_hoops_ICSIR->_hoops_GHIAA = true;
				_hoops_ICSIR->_hoops_PSPIP = false;
			}

			if (_hoops_ICSIR->_hoops_HRSCP && _hoops_ICSIR->depth_buffer != null) {
				HD_Clear_Software_Z_Buffer (nr);
				if (nr->_hoops_SAIR->_hoops_CGAIP == FP_WINDOW_TRANSPARENT &&
				   _hoops_ICSIR->_hoops_HIAI->format == _hoops_CSGSP) {
					/* _hoops_CAAP _hoops_RH _hoops_CSCR */
					Net_Rendition		_hoops_CRAI = nr;

					_hoops_CRAI.Modify()->_hoops_SAIR.Modify()->_hoops_CGAIP = FP_SOLID;
					HD_Standard_Draw_Window(_hoops_CRAI,&nr->_hoops_SAIR->_hoops_SCIH);
				}

				_hoops_ICSIR->_hoops_GHIAA = true;
			}
		}
	}
}


typedef void (*_hoops_PRASS) (Net_Rendition const & nr);


struct _hoops_HRASS : public _hoops_HIHCP {
	_hoops_SHCRP		_hoops_ARPHA;
	_hoops_PRASS			what;
	_hoops_AHAGR *		_hoops_CSC;

	_hoops_HRASS (_hoops_SHCRP _hoops_IRASS, _hoops_PRASS _hoops_CRASS, _hoops_AHAGR * sc)
		: _hoops_ARPHA (_hoops_IRASS), what (_hoops_CRASS), _hoops_CSC (sc) {}

	bool _hoops_SIHCP (Net_Rendition alter & nr, bool _hoops_PPHPP) alter {
		Display_Context const *		dc = nr->_hoops_SRA;

		if (_hoops_PPHPP)
			return true;

		// _hoops_GHCA _hoops_HAR _hoops_HS _hoops_SHR _hoops_CPHR _hoops_IRS _hoops_SRASS (_hoops_GA'_hoops_RA _hoops_RPP _hoops_GRP _hoops_PIAH _hoops_GAASS _hoops_PIH), _hoops_HIS _hoops_CACH _hoops_RPP _hoops_SR _hoops_RRP _hoops_IRS _hoops_RAASS
		if (BIT (dc->_hoops_IPCI->mode, _hoops_CSGGR))
			_hoops_HGSGA (dc, "hidden");

#ifndef _hoops_IRRHP
		if (_hoops_ARPHA == _hoops_PRAAP) {
			(*what)(nr);

			if (dc->_hoops_SHSHP != null) {
				_hoops_CSC->_hoops_CGSGP (dc->_hoops_SHSHP);
				_hoops_PGRCA(dc)->_hoops_SHSHP = null;
			}
		}
		else
#endif
		if (dc->_hoops_HASS[dc->_hoops_IASS] != null)
			(*what)(nr);

		return true;
	}
};


local void _hoops_AAASS (
	Net_Rendition alter &		nr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path,
	bool						_hoops_PAASS) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	_hoops_SHCRP				_hoops_SRI;
	_hoops_SCASP					_hoops_HAASS;
	_hoops_PRASS					_hoops_IAASS;
	bool						_hoops_CAASS = true;


	if (BIT (nr->_hoops_RCSHR, _hoops_GAHPP)) {
		/* _hoops_IPIHR _hoops_AHCA _hoops_CCSHP! */
		nr.Modify()->_hoops_RCSHR &= ~_hoops_IRGIP;
		return;
	}

	if (!ANYBIT (dc->_hoops_CPGPR, _hoops_HPPGP|_hoops_RIPGP)) {
		/* _hoops_ISAP'_hoops_GRI _hoops_IGRC _hoops_CPIC _hoops_IS _hoops_SHH _hoops_CHCC, _hoops_HIS _hoops_SAHR _hoops_SPIC _hoops_GPP _hoops_ISHP */
		nr.Modify()->current |= _hoops_CSGGR;
		return;
	}

#if 0	/* _hoops_AGIRA _hoops_RGR _hoops_RPP _hoops_IRS _hoops_GRAA-_hoops_PISI _hoops_IHSP _hoops_PGSA _hoops_HRGR _hoops_SIGR */
	if (!_hoops_PAASS &&
		nr->_hoops_IRR->_hoops_PRH._hoops_SRI == _hoops_CGAAP) {
		/* _hoops_GA'_hoops_RA _hoops_CPSA _hoops_HHGC _hoops_IS _hoops_PSCPR _hoops_CIPH */
		nr.Modify()->current |= _hoops_CSGGR;
		return;
	}
#endif

	if (_hoops_PAASS)
		dc->_hoops_CPGPR |= _hoops_RCGSA & ~_hoops_AASCA;
	/* (_hoops_RPP _hoops_SR _hoops_RIIPS _hoops_ISHP _hoops_CRGR _hoops_IRS _hoops_GRAA-_hoops_CCSHP _hoops_ISPH, _hoops_HCR _hoops_RH _hoops_CPAP
	 *	_hoops_IIH _hoops_GRS _hoops_SHH _hoops_SIGSA _hoops_HAH. _hoops_IPGRH _hoops_PRAR.)
	 */

	if (_hoops_PAASS)
		_hoops_SRI = nr->_hoops_IRR->_hoops_SRI;
	else
		_hoops_SRI = nr->_hoops_CPP->_hoops_PRH._hoops_SRI;

	/* _hoops_GRH _hoops_PRCA _hoops_IIGR _hoops_HSCH _hoops_RSSI _hoops_GGR _hoops_IRS "_hoops_CCSHP _hoops_III" _hoops_HIRA */
	if (BIT (_hoops_SRI, _hoops_PRAAP) &&
		!ANYBIT (_hoops_SRI, _hoops_GRAAP|_hoops_HSSS) &&
		!BIT (nr->current, _hoops_CRSI)) {
		Net_Rendition				_hoops_SAASS = nr.Copy();
		_hoops_GRGH				_hoops_GPASS =	_hoops_SAASS->_hoops_IRR.Modify();
		_hoops_ISHHP			_hoops_RPASS =	_hoops_SAASS->_hoops_ASIR.Modify();
		_hoops_CGRA			_hoops_APASS =	_hoops_SAASS->_hoops_SAIR.Modify();
		Activity					_hoops_IPHIP = dc->_hoops_CPGPR;

		if ((BIT (nr->_hoops_RCSHR, _hoops_AHIHP) ||	 /* _hoops_IRS _hoops_RRSS */
			 _hoops_SRCP->_hoops_IGCCA > 0 || _hoops_SRCP->_hoops_SHGSA() > 0)) {	/* _hoops_PIPIP _hoops_GH */

			/* _hoops_SR _hoops_RRP _hoops_HHH _hoops_CGGAR _hoops_IIGR _hoops_SSH _hoops_SRHR.  _hoops_SGH _hoops_HIPIP _hoops_RPP _hoops_HGRC, _hoops_IAII
			 * _hoops_SGH _hoops_GSIA _hoops_RPP _hoops_HHPA, _hoops_HIPIP _hoops_RPP _hoops_PSP _hoops_PPASS _hoops_HIH _hoops_RGCH (_hoops_CCIAH), _hoops_SHS _hoops_HPASS _hoops_SSCHA/_hoops_IPASS
			 */
			if (_hoops_RPASS->_hoops_GCCI._hoops_SRI == _hoops_RRAAP) {
				_hoops_GPASS->_hoops_SRI |= _hoops_RRAAP;
				_hoops_SAASS->_hoops_RCSHR |= _hoops_RSSHP;
			}
			else if (BIT(dc->flags, _hoops_IIPIP) &&
					 !BIT(dc->flags, _hoops_AASHP)) {
				_hoops_GPASS->_hoops_SRI |= _hoops_SGAAP;
				_hoops_SAASS->_hoops_RCSHR |= _hoops_GSSHP;
			}
			else if (_hoops_SRCP->_hoops_SHGSA() > 0) {
				_hoops_GPASS->_hoops_SRI |= _hoops_RRAAP;
				_hoops_SAASS->_hoops_RCSHR |= _hoops_RSSHP;


				HD_Init_Frame_Buffer_Info (_hoops_SAASS, _hoops_SRCP, path);
				HD_Setup_Frame_Buffer(_hoops_SAASS);
				_hoops_HCSIR alter *	_hoops_ICSIR;
				_hoops_ICSIR = _hoops_SAASS->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

				_hoops_ICSIR->_hoops_RSSCP = _hoops_SAASS;
			}
			else {
				_hoops_GPASS->_hoops_SRI |= _hoops_GRAAP;

				_hoops_SAASS->_hoops_RCSHR &= ~_hoops_AHIHP;
				_hoops_SAASS->_hoops_CPP.Modify()->_hoops_PRH.style = _hoops_GCPI;
			}
		}
		else if (BIT(dc->flags, _hoops_AASHP))
			_hoops_GPASS->_hoops_SRI |= _hoops_GRAAP;
		else {
			_hoops_GPASS->_hoops_SRI |= _hoops_RPASS->_hoops_GCCI._hoops_SRI;
			if (_hoops_RPASS->_hoops_GCCI._hoops_SRI == _hoops_SGAAP)
				_hoops_SAASS->_hoops_RCSHR |= _hoops_GSSHP;
			else if (_hoops_RPASS->_hoops_GCCI._hoops_SRI == _hoops_RRAAP)
				_hoops_SAASS->_hoops_RCSHR |= _hoops_RSSHP;
		}

		dc->_hoops_RASIP(_hoops_GICI);
		HD_Fixup_Attributes (_hoops_SAASS, null, _hoops_IPIHP);
		dc->flags &= ~_hoops_RASS;

		_hoops_CASS const *			_hoops_CPASS = dc->_hoops_HASS[dc->_hoops_IASS];
		_hoops_CHAGH  *		_hoops_SCRPS = dc->_hoops_SRSIP[dc->_hoops_IASS];

		dc->_hoops_HASS[dc->_hoops_IASS] = null;
		dc->_hoops_SRSIP[dc->_hoops_IASS] = null;

		_hoops_AASS (_hoops_SAASS, _hoops_SRCP, path);

		if (_hoops_SRCP->_hoops_SHGSA() > 0) {
			dc->_hoops_RASIP(_hoops_IIAGH);
			_hoops_SAASS->current = nr->current;
			_hoops_GPASS = _hoops_SAASS->_hoops_IRR.Modify();
			_hoops_SAASS->_hoops_RGP = _hoops_GPASS->_hoops_AARIP;
			_hoops_SAASS->flags &= ~_hoops_IPIHP;
			HD_Fixup_Attributes (_hoops_SAASS, null, _hoops_IPIHP);
			dc->flags &= ~_hoops_RASS;

			_hoops_AASS (_hoops_SAASS, _hoops_SRCP, path);
		}

		if (dc->_hoops_HASS[dc->_hoops_IASS] != null ||
			dc->_hoops_SRSIP[dc->_hoops_IASS] != null) {
			HD_See_Whats_Hidden (nr);
		}
		if (dc->_hoops_GPSS[dc->_hoops_IASS] != null) {
			_hoops_PGCIP *			item = null;

			// _hoops_SRAI _hoops_RH _hoops_ARHP _hoops_HIGR
			while ((item = dc->_hoops_RPSS[dc->_hoops_IASS]) != null) {
				dc->_hoops_RPSS[dc->_hoops_IASS] = item->next;
				item->next = dc->_hoops_GPSS[dc->_hoops_IASS];
				dc->_hoops_GPSS[dc->_hoops_IASS] = item;
			}

			_hoops_SSGGR (dc);
		}

		dc->_hoops_HASS[dc->_hoops_IASS] = _hoops_CPASS;
		dc->_hoops_SRSIP[dc->_hoops_IASS] = _hoops_SCRPS;


		dc->_hoops_RASIP(_hoops_AASIP);
		dc->_hoops_CPGPR = _hoops_IPHIP;
		dc->flags |= _hoops_RASS;
	}


	/* _hoops_AA _hoops_ICCGR _hoops_CCSHP _hoops_ISSGR! */

	/* _hoops_SRS _hoops_HPPP _hoops_GII "_hoops_PIAP" _hoops_SHPH */

	_hoops_ARASS (nr);

	nr.Modify();

	nr->current |= _hoops_CSGGR | _hoops_HPGSP;
	nr->_hoops_RCSHR |= _hoops_HPGSP;

	nr->_hoops_RCSHR &= ~(_hoops_HSGGR|_hoops_ISGGR);
	if (!ANYBIT(nr->current, _hoops_GSSHP|_hoops_RSSHP) &&
		ANYBIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP|_hoops_CRAAP) &&
		BIT(dc->flags, _hoops_AASHP))
		nr->_hoops_IRR.Modify()->_hoops_CHP &= ~(_hoops_SHP|_hoops_CRAAP);

#ifndef _hoops_IRRHP
	if (BIT (_hoops_SRI, _hoops_PRAAP) &&
		!ANYBIT (_hoops_SRI, _hoops_GRAAP|_hoops_HSSS)) {
		_hoops_CGRA const &		_hoops_SGRA = nr->_hoops_SAIR;
		_hoops_SPAGR							_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
		_hoops_AHAGR *					_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, path, false);

		_hoops_HAASS = _hoops_GSASP;
		_hoops_IAASS = HD_HL_See_Whats_Hidden;

		/* _hoops_CACH _hoops_RPP _hoops_IRS _hoops_PIAH _hoops_GAASS _hoops_SR _hoops_PAH _hoops_SGH */
		if (_hoops_CSC != null) {
			if (_hoops_CSC->_hoops_GRSGP() != null) {
				_hoops_SGSGP *		_hoops_SPASS = _hoops_CSC->_hoops_GRSGP();

				if (BIT (dc->_hoops_CPGPR, _hoops_RPSIR) ||
					_hoops_SPASS->extent.left   != _hoops_SGRA->_hoops_PHRA.left ||
					_hoops_SPASS->extent.right  != _hoops_SGRA->_hoops_PHRA.right ||
					_hoops_SPASS->extent.bottom != _hoops_SGRA->_hoops_PHRA.bottom ||
					_hoops_SPASS->extent.top	   != _hoops_SGRA->_hoops_PHRA.top)
					HD_Free_HL_Data (_hoops_SPASS);
				else {
					dc->_hoops_SHSHP = _hoops_SPASS;
					_hoops_CAASS = false;
				}
				_hoops_CSC->_hoops_CGSGP (null);
			}
		}

		if (nr->_hoops_SRA->_hoops_SHSHP == null) {
			_hoops_SGSGP *		_hoops_SPASS;

			HD_Initialize_HL_Data (dc);

			_hoops_SPASS = dc->_hoops_SHSHP;
			_hoops_SPASS->extent.left   = _hoops_SGRA->_hoops_PHRA.left;
			_hoops_SPASS->extent.right  = _hoops_SGRA->_hoops_PHRA.right;
			_hoops_SPASS->extent.bottom = _hoops_SGRA->_hoops_PHRA.bottom;
			_hoops_SPASS->extent.top	   = _hoops_SGRA->_hoops_PHRA.top;
		}
	}
	else
#endif
	{
#ifndef _hoops_IRSSH
		if (_hoops_SRI == _hoops_GAI)
			_hoops_HAASS = TR_SORT_HIDDEN_BY_PRIORITY;
		else
#endif
			_hoops_HAASS = 0;

		_hoops_IAASS = HD_See_Whats_Hidden;
	}

	if (_hoops_CAASS) {
		_hoops_APARR		_hoops_RRCI;

		if ((nr->transform_rendition->flags & _hoops_RSASP) != _hoops_HAASS) {
			_hoops_HHCR alter &		_hoops_IHCR = nr.Modify()->transform_rendition.Modify();
			_hoops_IHCR->flags &= ~_hoops_RSASP;
			_hoops_IHCR->flags |= _hoops_HAASS;
		}

		/********************************************************************
		 *																		*
		 *		_hoops_GHASS _hoops_RHASS:													*
		 *																		*
		 *			1) _hoops_AHASS _hoops_GISP-3D _hoops_PPR -_hoops_AHHGH _hoops_ACPH _hoops_SAGGR _hoops_SHIS _hoops_IS "_hoops_HHRCP".	*
		 *			   _hoops_GSASR: 3d _hoops_CCGI _hoops_RAAP _hoops_GAR _hoops_HRGR _hoops_HIS _hoops_SPSIR _hoops_PRPS		*
		 *			   _hoops_IGH _hoops_PAR _hoops_HAR _hoops_IS _hoops_CAH								 	*
		 *																		*
		 *			2) _hoops_AHASS _hoops_GISP-_hoops_SHCA _hoops_ACPH _hoops_SAGGR _hoops_SHIS _hoops_IS "_hoops_PHASS-_hoops_SHCA". _hoops_IPCP		*
		 *			   _hoops_PHASS-_hoops_SHCA-_hoops_ASIGA _hoops_SICAR _hoops_CHR _hoops_PSCR _hoops_HGSAR _hoops_IH _hoops_GHGA		*
		 *			   _hoops_CPHP _hoops_HHASS.									*
		 *																		*
		 *			3) _hoops_HGI _hoops_PCPH _hoops_SSCP _hoops_IS _hoops_SHH _hoops_GPGGR _hoops_PAPRH "_hoops_GISP" _hoops_PGSI	*
		 *			   _hoops_CHR _hoops_RRAI _hoops_PAR _hoops_RHSI.									*
		 *																		*
		 ********************************************************************/

		_hoops_RRCI = _hoops_HGCGA (dc, "hidden", nr);

		if (!ANYBIT (_hoops_RRCI->mode, _hoops_CRSI|_hoops_SRSI))
			_hoops_RRCI->_hoops_CHCI						= HD_Standard_Render;

		_hoops_RRCI->draw_3d_cylinder			= HD_Std_3D_Cylinder;
		_hoops_RRCI->draw_3d_ellipse				= HD_Std_3D_Ellipse;
		_hoops_RRCI->draw_3d_elliptical_arc		= HD_Std_3D_Elliptical_Arc;
		_hoops_RRCI->draw_3d_grid				= HD_Std_3D_Grid;
		_hoops_RRCI->draw_3d_image				= HD_Std_3D_Image;
		_hoops_RRCI->draw_3d_marker				= HD_Std_3D_Marker;
		_hoops_RRCI->_hoops_RIICP			= HD_Std_3D_Multimarker;
		_hoops_RRCI->draw_3d_nurbs_curve			= HD_Std_3D_NURBS_Curve;
		_hoops_RRCI->draw_3d_nurbs_surface		= HD_Std_3D_NURBS_Surface;
		_hoops_RRCI->draw_3d_polycylinder		= HD_Std_3D_PolyCylinder;
		_hoops_RRCI->draw_3d_sphere				= HD_Std_3D_Sphere;
		_hoops_RRCI->draw_3d_polyline			= HD_Std_3D_Polyline;
		_hoops_RRCI->draw_3d_polygon				= HD_Std_3D_Polygon;
		_hoops_RRCI->_hoops_SHCHP				= HD_Std_3D_Contour;
		_hoops_RRCI->draw_3d_text				= HD_Std_3D_Text;
		_hoops_RRCI->draw_3d_polyhedron			= HD_Std_3D_Polyhedron;

		_hoops_RRCI->_hoops_ARCI		= HD_Draw_Indexicated_3D_Tristrip;
		_hoops_RRCI->_hoops_PPAS		= HD_Draw_Indexicated_3D_Polyedge;

		/* _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_ARI _hoops_HIH _hoops_ARP _hoops_IS _hoops_GSIA, _hoops_SR _hoops_GHCA _hoops_PAR _hoops_GHCA _hoops_HAR _hoops_HS _hoops_IHSP,
			_hoops_HIS _hoops_IIS _hoops_RH _hoops_RHPP _hoops_PRPS */
		if (ANYBIT (nr->_hoops_IRR->_hoops_SRI, ~(_hoops_SGAAP|_hoops_SICI)))
			_hoops_RRCI->draw_3d_tristrip		= HD_Std_3D_Tristrip;

		_hoops_RRCI->draw_3d_polyedge			= HD_Std_3D_Polyedge;

		if (ANYBIT (nr->_hoops_IRR->_hoops_SRI, ~_hoops_SGAAP) ||
			(BIT(nr->_hoops_CPP->_hoops_PRH._hoops_SRI, _hoops_HSSS) &&
			!nr->_hoops_CPP->_hoops_PRH._hoops_RGGIP))
			_hoops_RRCI->draw_3d_polymarker			= HD_Std_3D_Polymarker;
		_hoops_RRCI->draw_3d_polyedge_from_tristrip = nullroutine;

		_hoops_RRCI->_hoops_CRCGA		= HD_Std_3D_Stenciled_Quad;

		_hoops_RRCI->_hoops_CSCGA				= HD_Standard_Draw_Inter_Text;
		_hoops_RRCI->draw_dc_ellipse				= HD_Std_DC_Ellipse;
		_hoops_RRCI->_hoops_SCISR		= HD_Std_DC_Outline_Ellipse;

		_hoops_RRCI->_hoops_SPCGA		= HD_Std_DC_Stenciled_Quad;

		/*
		 * _hoops_HGI _hoops_PCGR _hoops_HIRGR _hoops_HHGS _hoops_PGGA _hoops_RH _hoops_HPRGR _hoops_PCPH
		 * _hoops_GPISP _hoops_IRS _hoops_RSPH _hoops_HSP _hoops_SGS _hoops_IISA _hoops_HII _hoops_PSP "_hoops_IHASS", _hoops_CRSHA
		 * _hoops_RIHGH _hoops_IRS _hoops_ARPC _hoops_GGR _hoops_RH _hoops_CHASS _hoops_RRGR.	 _hoops_GHAP _hoops_PAH'_hoops_RA _hoops_CACH _hoops_RCSC _hoops_SCH _hoops_CHH
		 * _hoops_SHH _hoops_HAHH _hoops_APIC - _hoops_SHASS
		 *
		 *		_hoops_HPGR->_hoops_CIAC	= _hoops_GIASS;
		 */

#ifndef _hoops_IRRHP
		if (BIT (_hoops_SRI, _hoops_PRAAP) &&
			!ANYBIT (_hoops_SRI, _hoops_GRAAP|_hoops_HSSS)) {
			_hoops_RRCI->draw_3d_image					= HD_HL_3D_Image;
			_hoops_RRCI->draw_dc_colorized_face			= HD_Std_DC_Colorized_Face;
			_hoops_RRCI->draw_dc_face					= HD_Std_DC_Face;
			_hoops_RRCI->_hoops_RPCGA					= HD_Std_DC_Polygon;
			_hoops_RRCI->_hoops_HPCGA					= HD_HL_DC_Image;
			_hoops_RRCI->draw_dc_polytriangle			= HD_HL_DC_Polytriangle;
			_hoops_RRCI->draw_dc_colorized_polytriangle	= HD_HL_DC_Colorized_Polytris;
			_hoops_RRCI->draw_dc_gouraud_polytriangle	= HD_HL_DC_Gouraud_Polytris;
			_hoops_RRCI->draw_dc_phong_polytriangle		= HD_HL_DC_Phong_Polytris;
			_hoops_RRCI->draw_dc_textured_polytriangle	= HD_HL_DC_Textured_Polytris;
			_hoops_RRCI->draw_dc_polyline				= HD_HL_DC_Polyline;
			_hoops_RRCI->draw_dc_colorized_polyline		= HD_HL_DC_Colorized_Polyline;
			_hoops_RRCI->draw_dc_gouraud_polyline		= HD_HL_DC_Gouraud_Polyline;
			_hoops_RRCI->draw_dc_phong_polyline			= HD_HL_DC_Phong_Polyline;
			_hoops_RRCI->draw_dc_textured_polyline		= HD_HL_DC_Textured_Polyline;
			_hoops_RRCI->draw_dc_polymarker				= HD_HL_DC_Polymarker;
			_hoops_RRCI->_hoops_AGCSR					= HD_HL_Plain_Text;
			_hoops_RRCI->draw_dc_polydot					= HD_HL_DC_Polydot;
			_hoops_RRCI->draw_dc_colorized_polydot		= HD_HL_DC_Colorized_Polydot;
			_hoops_RRCI->draw_dc_rgb32_rasters			= HD_HL_DC_Text_Rasters;

			_hoops_RRCI->draw_3d_polyhedron				= HD_HL_3D_Polyhedron;

			/*
			 * _hoops_IPCP _hoops_HSPR _hoops_SICAR _hoops_CGH *_hoops_IIP* _hoops_HGCR _hoops_PIGS.
			 * _hoops_IPCP _hoops_SICAR _hoops_ARRS _hoops_CGH _hoops_HS _hoops_RIASS _hoops_GGSR _hoops_HCR _hoops_PIPHC.
			 */
			_hoops_RRCI->draw_dc_text					= HD_HL_DC_Text;
		}
		else
#endif
		{
			_hoops_RRCI->draw_dc_colorized_face			= HD_Hide_DC_Colorized_Face;
			_hoops_RRCI->draw_dc_face					= HD_Hide_DC_Face;
			_hoops_RRCI->_hoops_RPCGA					= HD_Hide_DC_Polygon;
			_hoops_RRCI->_hoops_HPCGA					= HD_Hide_DC_Image;
			_hoops_RRCI->draw_dc_polymarker				= HD_Std_DC_Polymarker; /*_hoops_IRHH _hoops_SCSRA _hoops_IH _hoops_HCAS*/
			_hoops_RRCI->draw_dc_polytriangle			= HD_Hide_DC_Polytriangle;
			_hoops_RRCI->draw_dc_colorized_polytriangle	= HD_Hide_DC_Colorized_Polytris;
			_hoops_RRCI->draw_dc_gouraud_polytriangle	= HD_Hide_DC_Gouraud_Polytris;
			_hoops_RRCI->draw_dc_phong_polytriangle		= HD_Hide_DC_Phong_Polytris;
			_hoops_RRCI->draw_dc_textured_polytriangle	= HD_Hide_DC_Textured_Polytris;
			_hoops_RRCI->draw_dc_polydot					= HD_Hide_DC_Polydot;
			_hoops_RRCI->draw_dc_colorized_polydot		= HD_Hide_DC_Colorized_Polydot;
			_hoops_RRCI->draw_dc_polyline				= HD_Hide_DC_Polyline;
			_hoops_RRCI->draw_dc_colorized_polyline		= HD_Hide_DC_Colorized_Polyline;
			_hoops_RRCI->draw_dc_gouraud_polyline		= HD_Hide_DC_Gouraud_Polyline;
			_hoops_RRCI->draw_dc_phong_polyline			= HD_Hide_DC_Phong_Polyline;
			_hoops_RRCI->draw_dc_textured_polyline		= HD_Hide_DC_Textured_Polyline;
			_hoops_RRCI->_hoops_AGCSR					= HD_Hide_Plain_Text;
			_hoops_RRCI->_hoops_SPCGA			= HD_Hide_DC_Stenciled_Quad;

#ifndef _hoops_IRSSH
			if (BIT (nr->transform_rendition->flags, TR_SORT_HIDDEN_BY_PRIORITY)) {
				_hoops_RRCI->_hoops_PGSSP				= HD_Start_Priority_Inclusion;
				_hoops_RRCI->_hoops_HGSSP			= HD_Finish_Priority_Inclusion;
			}
#endif

			/*
			 * _hoops_IPCP _hoops_HSPR _hoops_SICAR _hoops_CGH *_hoops_IIP* _hoops_HGCR _hoops_PIGS.
			 * _hoops_IPCP _hoops_SICAR _hoops_ARRS _hoops_CGH _hoops_HS _hoops_RIASS _hoops_GGSR _hoops_HCR _hoops_PIPHC.
			 */
			_hoops_RRCI->draw_dc_text			 = HD_Hide_DC_Text;
		}
	}
	else {
		dc->_hoops_AHSI->stage = _hoops_ACHCP;
		HD_Search_Null_Clip_Tree (nr, _hoops_SRCP, path, dc->_hoops_CPGPR, false);
	}

	/* _hoops_PIP _hoops_SGS _hoops_CSPH _hoops_SICAR _hoops_CHR _hoops_PSHCI _hoops_SRS, _hoops_HIS _hoops_RGR _hoops_PAH _hoops_HA _hoops_CPSA _hoops_PGSA */

	if (_hoops_PAASS) {
		_hoops_SPAGR				_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
		_hoops_AHAGR *		_hoops_CSC = null;

#ifndef _hoops_IRRHP
		if (_hoops_SRI == _hoops_PRAAP)
			_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, path);
#endif

		dc->_hoops_AHSI->_hoops_GSHCP (POOL_NEW(dc->memory_pool, _hoops_HRASS)(_hoops_SRI, _hoops_IAASS, _hoops_CSC));
	}
	else if (_hoops_CAASS)	// _hoops_SSAS _hoops_IRS _hoops_SRASS
		dc->_hoops_AHSI->_hoops_GSHCP (POOL_NEW(dc->memory_pool, _hoops_GRASS)("hidden"));
}


GLOBAL_FUNCTION void HD_Defer_Antialiased_3D_Polygon (
	Net_Rendition const &		nr,
	Polygon const *				polygon) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	_hoops_PGCIP *				_hoops_AIASS;

	if (!BIT (nr->_hoops_PSGI, T_EDGES) &&
		!ANYBIT (nr->current, _hoops_CRSI|_hoops_SRSI) ||
		!BIT (nr->_hoops_SRA->flags, _hoops_RASS)) {
		if (!ANYBIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE) ||
			!BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP)) {
			_hoops_IGRS (dc);
			_hoops_SGPGR (nr, polygon);
			_hoops_SGRS (dc);
			return;
		}

		if (BIT (nr->_hoops_RGP, T_FACES)) {
			Net_Rendition				_hoops_CRAI = nr;
			int							count = 0;

			if (ANYBIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE)) {
				_hoops_CRAI.Modify()->_hoops_RGP &= ~T_ANY_POLYGON_EDGE;
			}
			while (BIT (dc->_hoops_IPCI->mode, _hoops_HSGGR)) {
				_hoops_IGRS (dc);
				++count;
			}
			_hoops_SGPGR (_hoops_CRAI, polygon);
			while (count-- > 0)
				_hoops_SGRS (dc);
		}
	}

	if (BIT (nr->_hoops_RGP, T_FACES) &&
		BIT (nr->current, _hoops_AHIHP) &&
		BIT (nr->_hoops_PSGI, T_FACES) &&
		nr->_hoops_CPP->_hoops_PRH._hoops_SRI == _hoops_PIII) {
		HD_Defer_Peeled_Trans_3D_Polygon (nr, polygon);
		return;
	}

	POOL_ZALLOC (_hoops_AIASS, _hoops_PGCIP, dc->memory_pool);
	_hoops_AIASS->next = dc->_hoops_RPSS[dc->_hoops_IASS];
	dc->_hoops_RPSS[dc->_hoops_IASS] = _hoops_AIASS;
	_hoops_AIASS->type = polygon->type;
	_hoops_AIASS->item = polygon;	_hoops_PRRH (polygon);
	_hoops_AIASS->segment = dc->_hoops_RRCIP;
	_hoops_AIASS->path = dc->path;
	if (!BIT (nr->_hoops_RGP, T_FACES)) {
		_hoops_AIASS->nr = nr;
	}
	else {
		_hoops_AIASS->nr = nr;
		if (ANYBIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE))
			_hoops_AIASS->nr.Modify()->_hoops_RGP = T_ANY_POLYGON_EDGE;
	}
	if (dc->_hoops_RAI != dc->_hoops_HHAGH) {
		if (nr->_hoops_IRR->_hoops_GAHA == Display_List_SEGMENT)
			dc->_hoops_GSGC |= HD_Geometry_To_Action_Mask (dc->_hoops_RAI);
		dc->_hoops_GSGC |= _hoops_ACIP;
		dc->_hoops_HHAGH = dc->_hoops_RAI;
	}
	dc->_hoops_GSGC |= _hoops_ACIP;
}


GLOBAL_FUNCTION void HD_Defer_Antialiased_3D_Polyline (
	Net_Rendition const &		nr,
	Polyline const *			polyline) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	_hoops_PGCIP *				_hoops_AIASS;

	if (!BIT (nr->_hoops_PSGI, T_LINES) &&
		!BIT (nr->_hoops_IRR->_hoops_CHP, _hoops_SHP) &&
		!ANYBIT (nr->current, _hoops_CRSI|_hoops_SRSI) ||
		!BIT (nr->_hoops_SRA->flags, _hoops_RASS)) {
		_hoops_IGRS (dc);
		_hoops_CPAGR (nr, polyline);
		_hoops_SGRS (dc);
		return;
	}

	// _hoops_CCPH _hoops_PIASS _hoops_HCCGR
	if (polyline->type == _hoops_IIIP && polyline->allocated > Abs(polyline->count)) {
		Point *	points;
		ALLOC_ARRAY (points, Abs(polyline->count), Point);
		_hoops_AIGA(polyline->points, Abs(polyline->count), Point, points);
		FREE_ARRAY(polyline->points, polyline->allocated, Point);
		_hoops_PGRCA(polyline)->allocated = Abs(polyline->count);
		_hoops_PGRCA(polyline)->points = points;
	}

	POOL_ZALLOC (_hoops_AIASS, _hoops_PGCIP, dc->memory_pool);
	_hoops_AIASS->next = dc->_hoops_RPSS[dc->_hoops_IASS];
	dc->_hoops_RPSS[dc->_hoops_IASS] = _hoops_AIASS;
	_hoops_AIASS->type = polyline->type;
	_hoops_AIASS->item = polyline;	_hoops_PRRH (polyline);
	_hoops_AIASS->segment = dc->_hoops_RRCIP;
	_hoops_AIASS->path = dc->path;
	_hoops_AIASS->nr = nr;
	if (dc->_hoops_RAI != dc->_hoops_HHAGH) {
		if (nr->_hoops_IRR->_hoops_GAHA == Display_List_SEGMENT)
			dc->_hoops_GSGC |= HD_Geometry_To_Action_Mask (dc->_hoops_RAI);
		dc->_hoops_GSGC |= _hoops_CIIP;
		dc->_hoops_HHAGH = dc->_hoops_RAI;
	}
	dc->_hoops_GSGC |= _hoops_CIIP;
}


GLOBAL_FUNCTION void HD_Defer_Antialiased_3D_Polyedge (
	Net_Rendition const &		nr,
	Polyedge const *			pe) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	_hoops_PGCIP *				_hoops_AIASS;

	if (!BIT (pe->_hoops_SRHA, DL_DO_NOT_DEFER) &&
		!BIT (nr->_hoops_PSGI, T_EDGES) &&
		!BIT (nr->_hoops_IRR->_hoops_CHP, _hoops_SHP) &&
		!ANYBIT (nr->current, _hoops_CRSI|_hoops_SRSI) ||
		!BIT (nr->_hoops_SRA->flags, _hoops_RASS)) {
		_hoops_IGRS (dc);
		_hoops_IACIP (nr, pe);
		_hoops_SGRS (dc);
		return;
	}

	POOL_ZALLOC (_hoops_AIASS, _hoops_PGCIP, dc->memory_pool);
	_hoops_AIASS->next = dc->_hoops_RPSS[dc->_hoops_IASS];
	dc->_hoops_RPSS[dc->_hoops_IASS] = _hoops_AIASS;
	_hoops_AIASS->type = _hoops_HACIP;
	HD_Isolate_Polyedge_Data (dc, pe);
	_hoops_AIASS->item = pe;		_hoops_CAHS (pe);
	_hoops_AIASS->segment = dc->_hoops_RRCIP;
	_hoops_AIASS->path = dc->path;
	_hoops_AIASS->nr = nr;
	if (dc->_hoops_RAI != dc->_hoops_HHAGH) {
		if (nr->_hoops_IRR->_hoops_GAHA == Display_List_SEGMENT)
			dc->_hoops_GSGC |= HD_Geometry_To_Action_Mask (dc->_hoops_RAI);
		dc->_hoops_GSGC |= _hoops_IGAI;
		dc->_hoops_HHAGH = dc->_hoops_RAI;
	}
	dc->_hoops_GSGC |= (_hoops_ASRI|_hoops_GHCI);
	if (BIT (pe->_hoops_CARI, _hoops_RCRI))
		dc->_hoops_GSGC |= _hoops_RSRI;
}


GLOBAL_FUNCTION void HD_Defer_Peeled_Trans_3D_Polygon (
	Net_Rendition const &		nr,
	Polygon const *				polygon) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	_hoops_PGCIP *				_hoops_AIASS;

	if (!BIT (nr->_hoops_PSGI, T_FACES) &&
		!ANYBIT (nr->current, _hoops_CRSI|_hoops_SRSI)) {
		int                            _hoops_HIASS = 0;

		do {
			_hoops_IGRS (dc);
			++_hoops_HIASS;
		} while (BIT(dc->_hoops_IPCI->mode, _hoops_AHIHP));

		_hoops_SGPGR (nr, polygon);
		while (_hoops_HIASS-- > 0)
			_hoops_SGRS (dc);
		return;
	}

	POOL_ZALLOC (_hoops_AIASS, _hoops_PGCIP, dc->memory_pool);
	_hoops_AIASS->next = dc->_hoops_GPSS[dc->_hoops_IASS];
	dc->_hoops_GPSS[dc->_hoops_IASS] = _hoops_AIASS;

	if (dc->_hoops_SPA->modelling_matrix != null) {
		_hoops_AIASS->_hoops_IRCIP = dc->_hoops_SPA->modelling_matrix;
		_hoops_PRRH (_hoops_AIASS->_hoops_IRCIP);
	}
	if (dc->_hoops_SPA->color != null) {
		_hoops_AIASS->_hoops_GPCP = dc->_hoops_SPA->color;
		_hoops_PRRH (_hoops_AIASS->_hoops_GPCP);
	}

	_hoops_AIASS->type = polygon->type;
	_hoops_AIASS->item = polygon;	_hoops_PRRH (polygon);
	_hoops_AIASS->segment = dc->_hoops_RRCIP;
	_hoops_AIASS->path = dc->path;
	_hoops_AIASS->nr = nr;
	if (dc->_hoops_RAI) {
		_hoops_AIASS->g = dc->_hoops_RAI;
		_hoops_PRRH (dc->_hoops_RAI);
	}
}

GLOBAL_FUNCTION void HD_Defer_Peeled_Trans_3D_Ellipse (
	Net_Rendition const &		nr,
	Ellipse const *				ellipse) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	_hoops_PGCIP *				_hoops_AIASS;

	if (!BIT(nr->_hoops_PSGI, T_FACES) &&
		!ANYBIT (nr->current, _hoops_CRSI|_hoops_SRSI)) {
		int                            _hoops_HIASS = 0;

		do {
			_hoops_IGRS (dc);
			++_hoops_HIASS;
		} while (BIT(dc->_hoops_IPCI->mode, _hoops_AHIHP));

		_hoops_PCAIP (nr, ellipse);
		while (_hoops_HIASS-- > 0)
			_hoops_SGRS (dc);
		return;
	}

	POOL_ZALLOC (_hoops_AIASS, _hoops_PGCIP, dc->memory_pool);
	_hoops_AIASS->next = dc->_hoops_GPSS[dc->_hoops_IASS];
	dc->_hoops_GPSS[dc->_hoops_IASS] = _hoops_AIASS;

	if (dc->_hoops_SPA->modelling_matrix != null) {
		_hoops_AIASS->_hoops_IRCIP = dc->_hoops_SPA->modelling_matrix;
		_hoops_PRRH (_hoops_AIASS->_hoops_IRCIP);
	}
	if (dc->_hoops_SPA->color != null) {
		_hoops_AIASS->_hoops_GPCP = dc->_hoops_SPA->color;
		_hoops_PRRH (_hoops_AIASS->_hoops_GPCP);
	}

	_hoops_AIASS->type = ellipse->type;
	_hoops_AIASS->item = ellipse;	_hoops_PRRH (ellipse);
	_hoops_AIASS->segment = dc->_hoops_RRCIP;
	_hoops_AIASS->path = dc->path;
	_hoops_AIASS->nr = nr;
	if (dc->_hoops_RAI) {
		_hoops_AIASS->g = dc->_hoops_RAI;
		_hoops_PRRH (dc->_hoops_RAI);
	}
}


GLOBAL_FUNCTION void HD_Defer_Peeled_Trans_3D_Tristrip (
	Net_Rendition const &		nr,
	Tristrip const *			ts) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_PGCIP *				_hoops_AIASS;

	if (BIT (ts->_hoops_SRHA, DL_DO_NOT_DEFER) ||
		!BIT (nr->_hoops_PSGI, T_FACES) && !ANYBIT (nr->current, _hoops_CRSI|_hoops_SRSI)) {
		int                            _hoops_HIASS = 0;

		do {
			_hoops_IGRS (dc);
			++_hoops_HIASS;
		} while (BIT(dc->_hoops_IPCI->mode, _hoops_AHIHP));

		_hoops_RACIP (nr, ts);
		while (_hoops_HIASS-- > 0)
			_hoops_SGRS (dc);
		return;
	}

	POOL_ZALLOC (_hoops_AIASS, _hoops_PGCIP, dc->memory_pool);
	_hoops_AIASS->next = dc->_hoops_GPSS[dc->_hoops_IASS];
	_hoops_PGRCA(dc)->_hoops_GPSS[dc->_hoops_IASS] = _hoops_AIASS;

	if (dc->_hoops_SPA->modelling_matrix != null) {
		_hoops_AIASS->_hoops_IRCIP = dc->_hoops_SPA->modelling_matrix;
		_hoops_PRRH (_hoops_AIASS->_hoops_IRCIP);
	}
	if (dc->_hoops_SPA->color != null) {
		_hoops_AIASS->_hoops_GPCP = dc->_hoops_SPA->color;
		_hoops_PRRH (_hoops_AIASS->_hoops_GPCP);
	}

	_hoops_AIASS->type = _hoops_CRCIP;
	if (BIT(ts->_hoops_SRHA, DL_TEMPORARY_DATA))
		HD_Isolate_Tristrip_Data (dc, ts);
	_hoops_AIASS->item = ts;		_hoops_CAHS (ts);

	_hoops_AIASS->segment = dc->_hoops_RRCIP;
	_hoops_AIASS->path = dc->path;
	_hoops_AIASS->nr = nr;
	if (dc->_hoops_RAI) {
		_hoops_AIASS->g = dc->_hoops_RAI;
		_hoops_PRRH (dc->_hoops_RAI);
	}
}


GLOBAL_FUNCTION void HD_Defer_Peeled_Trans_3D_Polyline (
	Net_Rendition const &		nr,
	Polyline const *			polyline) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	_hoops_PGCIP *				_hoops_AIASS;

	if (!BIT (nr->_hoops_PSGI, T_LINES) &&
		!BIT (nr->_hoops_IRR->_hoops_CHP, _hoops_SHP) &&
		!ANYBIT (nr->current, _hoops_CRSI|_hoops_SRSI)) {
		int                            _hoops_HIASS = 0;

		do {
			_hoops_IGRS (dc);
			++_hoops_HIASS;
		} while (BIT(dc->_hoops_IPCI->mode, _hoops_AHIHP));

		_hoops_CPAGR (nr, polyline);
		while (_hoops_HIASS-- > 0)
			_hoops_SGRS (dc);
		return;
	}

	POOL_ZALLOC (_hoops_AIASS, _hoops_PGCIP, dc->memory_pool);
	_hoops_AIASS->next = dc->_hoops_GPSS[dc->_hoops_IASS];
	dc->_hoops_GPSS[dc->_hoops_IASS] = _hoops_AIASS;

	if (dc->_hoops_SPA->modelling_matrix != null) {
		_hoops_AIASS->_hoops_IRCIP = dc->_hoops_SPA->modelling_matrix;
		_hoops_PRRH (_hoops_AIASS->_hoops_IRCIP);
	}
	if (dc->_hoops_SPA->color != null) {
		_hoops_AIASS->_hoops_GPCP = dc->_hoops_SPA->color;
		_hoops_PRRH (_hoops_AIASS->_hoops_GPCP);
	}

	_hoops_AIASS->type = polyline->type;
	_hoops_AIASS->item = polyline;	_hoops_PRRH (polyline);
	_hoops_AIASS->segment = dc->_hoops_RRCIP;
	_hoops_AIASS->path = dc->path;
	_hoops_AIASS->nr = nr;
	if (dc->_hoops_RAI) {
		_hoops_AIASS->g = dc->_hoops_RAI;
		_hoops_PRRH (dc->_hoops_RAI);
	}
}


GLOBAL_FUNCTION void HD_Defer_Peeled_Trans_3D_Polymarker (
	Net_Rendition const &		nr,
	Polymarker const *			pm) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	_hoops_PGCIP *				_hoops_AIASS;

	if (!BIT (nr->_hoops_PSGI, T_VERTICES) &&
		!ANYBIT (nr->current, _hoops_CRSI|_hoops_SRSI) &&
		(pm->_hoops_RGIA == null)) {
		int                            _hoops_HIASS = 0;

		do {
			_hoops_IGRS (dc);
			++_hoops_HIASS;
		} while (BIT(dc->_hoops_IPCI->mode, _hoops_AHIHP));

		_hoops_SACIP (nr, pm);
		while (_hoops_HIASS-- > 0)
			_hoops_SGRS (dc);
		return;
	}

	POOL_ZALLOC (_hoops_AIASS, _hoops_PGCIP, dc->memory_pool);
	_hoops_AIASS->next = dc->_hoops_GPSS[dc->_hoops_IASS];
	dc->_hoops_GPSS[dc->_hoops_IASS] = _hoops_AIASS;

	if (dc->_hoops_SPA->modelling_matrix != null) {
		_hoops_AIASS->_hoops_IRCIP = dc->_hoops_SPA->modelling_matrix;
		_hoops_PRRH (_hoops_AIASS->_hoops_IRCIP);
	}
	if (dc->_hoops_SPA->color != null) {
		_hoops_AIASS->_hoops_GPCP = dc->_hoops_SPA->color;
		_hoops_PRRH (_hoops_AIASS->_hoops_GPCP);
	}

	_hoops_AIASS->type = _hoops_CACIP;
	HD_Isolate_Polymarker_Data(dc, pm);
	_hoops_AIASS->item = pm;	_hoops_CAHS (pm);
	_hoops_AIASS->segment = dc->_hoops_RRCIP;
	_hoops_AIASS->path = dc->path;
	_hoops_AIASS->nr = nr;
	if (dc->_hoops_RAI) {
		_hoops_AIASS->g = dc->_hoops_RAI;
		_hoops_PRRH (dc->_hoops_RAI);
	}
}


GLOBAL_FUNCTION void HD_Defer_Peeled_Trans_3D_Marker (
	Net_Rendition const &		inr,
	Marker const *				marker) {
	Polymarker alter			*pm;
	Net_Rendition				nr = inr;

	/* _hoops_IRHH _hoops_RH _hoops_SCII _hoops_IRAA _hoops_RGCI _hoops_GPHA _hoops_AIRC _hoops_HII _hoops_GPIA _hoops_AIRC */
	nr.Modify()->_hoops_SCP = nr->_hoops_GSP;
	ZALLOC (pm, Polymarker);
	_hoops_ICAI (pm);
	pm->points = _hoops_PGRCA(&marker->_hoops_CSAI);
	pm->point_count = pm->length = 1;
	pm->_hoops_SRHA = DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS;
	HD_Defer_Peeled_Trans_3D_Polymarker (nr, pm);
	if (_hoops_ISAI (pm) == 0) {
		ASSERT (pm->_hoops_GAHA == null);
		HI_Free_Polymarker_List (pm);
	}
}



GLOBAL_FUNCTION void HD_Defer_Peeled_Trans_3D_Text (
	Net_Rendition const &		nr,
	_hoops_HACC const *				text) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	_hoops_PGCIP *				_hoops_AIASS;

	if (!BIT (nr->_hoops_PSGI, T_TEXT) &&
		!BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_CRAAP) &&
		!ANYBIT (nr->current, _hoops_CRSI|_hoops_SRSI)) {
		int                            _hoops_HIASS = 0;

		do {
			_hoops_IGRS (dc);
			++_hoops_HIASS;
		} while (BIT(dc->_hoops_IPCI->mode, _hoops_AHIHP));

		_hoops_PAPGR (nr, text);
		while (_hoops_HIASS-- > 0)
			_hoops_SGRS (dc);
		return;
	}

	POOL_ZALLOC (_hoops_AIASS, _hoops_PGCIP, dc->memory_pool);
	_hoops_AIASS->next = dc->_hoops_GPSS[dc->_hoops_IASS];
	dc->_hoops_GPSS[dc->_hoops_IASS] = _hoops_AIASS;

	if (dc->_hoops_SPA->modelling_matrix != null) {
		_hoops_AIASS->_hoops_IRCIP = dc->_hoops_SPA->modelling_matrix;
		_hoops_PRRH (_hoops_AIASS->_hoops_IRCIP);
	}
	if (dc->_hoops_SPA->color != null) {
		_hoops_AIASS->_hoops_GPCP = dc->_hoops_SPA->color;
		_hoops_PRRH (_hoops_AIASS->_hoops_GPCP);
	}

	_hoops_AIASS->type = text->type;
	_hoops_AIASS->item = text;	_hoops_PRRH (text);
	_hoops_AIASS->segment = dc->_hoops_RRCIP;
	_hoops_AIASS->path = dc->path;
	_hoops_AIASS->nr = nr;
	if (dc->_hoops_RAI) {
		_hoops_AIASS->g = dc->_hoops_RAI;
		_hoops_PRRH (dc->_hoops_RAI);
	}
}


GLOBAL_FUNCTION void HD_Defer_Peeled_Trans_3D_Polyedge (
	Net_Rendition const &		nr,
	Polyedge const *			pe) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	_hoops_PGCIP *				_hoops_AIASS;

	if (BIT (pe->_hoops_SRHA, DL_DO_NOT_DEFER) ||
		!BIT (nr->_hoops_PSGI, T_EDGES) &&
		!BIT (nr->_hoops_IRR->_hoops_CHP, _hoops_SHP) &&
		!ANYBIT (nr->current, _hoops_CRSI|_hoops_SRSI)) {
		int                            _hoops_HIASS = 0;

		do {
			_hoops_IGRS (dc);
			++_hoops_HIASS;
		} while (BIT(dc->_hoops_IPCI->mode, _hoops_AHIHP));

		_hoops_IACIP (nr, pe);
		while (_hoops_HIASS-- > 0)
			_hoops_SGRS (dc);
		return;
	}

	POOL_ZALLOC (_hoops_AIASS, _hoops_PGCIP, dc->memory_pool);
	_hoops_AIASS->next = dc->_hoops_GPSS[dc->_hoops_IASS];
	dc->_hoops_GPSS[dc->_hoops_IASS] = _hoops_AIASS;

	if (dc->_hoops_SPA->modelling_matrix != null) {
		_hoops_AIASS->_hoops_IRCIP = dc->_hoops_SPA->modelling_matrix;
		_hoops_PRRH (_hoops_AIASS->_hoops_IRCIP);
	}
	if (dc->_hoops_SPA->color != null) {
		_hoops_AIASS->_hoops_GPCP = dc->_hoops_SPA->color;
		_hoops_PRRH (_hoops_AIASS->_hoops_GPCP);
	}

	_hoops_AIASS->type = _hoops_HACIP;
	HD_Isolate_Polyedge_Data (dc, pe);
	_hoops_AIASS->item = pe;		_hoops_CAHS (pe);
	_hoops_AIASS->segment = dc->_hoops_RRCIP;
	_hoops_AIASS->path = dc->path;
	_hoops_AIASS->nr = nr;
	if (dc->_hoops_RAI) {
		_hoops_AIASS->g = dc->_hoops_RAI;
		_hoops_PRRH (dc->_hoops_RAI);
	}
}


local void _hoops_IIASS (
	Net_Rendition alter &		nr) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);

	nr.Modify();

	if (!ANYBIT (dc->_hoops_CPGPR, _hoops_HPPGP|_hoops_RIPGP)) {
		/* _hoops_ISAP'_hoops_GRI _hoops_IGRC _hoops_CPIC _hoops_IS _hoops_SHH _hoops_CHCC, _hoops_HIS _hoops_SAHR _hoops_SPIC _hoops_GPP _hoops_ISHP */
		nr->current |= _hoops_HSGGR;
		return;
	}
	else if (BIT (nr->current, _hoops_CRSI)) {
		/* _hoops_SR _hoops_GGHP _hoops_ICCGR _hoops_CCSHP _hoops_RGAR! */
		nr->_hoops_RCSHR &= ~_hoops_HSGGR;
		return;
	}

	nr->current |= _hoops_HSGGR;

	if (BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP)) {
		_hoops_APARR			_hoops_RRCI;

		_hoops_RRCI = _hoops_HGCGA (dc, "antialias line deferral", nr);

		_hoops_RRCI->_hoops_CHCI = HD_Standard_Render;

		_hoops_RRCI->draw_3d_polygon			= HD_Defer_Antialiased_3D_Polygon;
		_hoops_RRCI->draw_3d_polyline		= HD_Defer_Antialiased_3D_Polyline;
		_hoops_RRCI->draw_3d_polyedge		= HD_Defer_Antialiased_3D_Polyedge;
		_hoops_RRCI->draw_3d_polyedge_from_tristrip = nullroutine;

		_hoops_RRCI->draw_dc_polyline				= HD_Hide_DC_Polyline;
		_hoops_RRCI->draw_dc_colorized_polyline		= HD_Hide_DC_Colorized_Polyline;
		_hoops_RRCI->draw_dc_gouraud_polyline		= HD_Hide_DC_Gouraud_Polyline;
		_hoops_RRCI->draw_dc_phong_polyline			= HD_Hide_DC_Phong_Polyline;
		_hoops_RRCI->draw_dc_textured_polyline		= HD_Hide_DC_Textured_Polyline;

		dc->_hoops_AHSI->_hoops_GSHCP (POOL_NEW(dc->memory_pool, _hoops_GRASS)("antialias line deferral"));
	}
}


local void _hoops_CIASS (
	Net_Rendition alter &		nr) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);

	nr.Modify();

	if (!ANYBIT (dc->_hoops_CPGPR, _hoops_HPPGP|_hoops_RIPGP)) {
		/* _hoops_ISAP'_hoops_GRI _hoops_IGRC _hoops_CPIC _hoops_IS _hoops_SHH _hoops_CHCC, _hoops_HIS _hoops_SAHR _hoops_SPIC _hoops_GPP _hoops_ISHP */
		nr->current |= _hoops_ISGGR;
		return;
	}
	else if (BIT (nr->current, _hoops_CRSI)) {
		/* _hoops_SR _hoops_GGHP _hoops_ICCGR _hoops_CCSHP _hoops_RGAR! */
		nr->_hoops_RCSHR &= ~_hoops_ISGGR;
		return;
	}

	nr->current |= _hoops_ISGGR;

	if (BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_CRAAP)) {
		_hoops_APARR			_hoops_RRCI;

		_hoops_RRCI = _hoops_HGCGA (dc, "antialias text deferral", nr);

		_hoops_RRCI->_hoops_SPCGA = HD_Hide_DC_Stenciled_Quad;
		_hoops_RRCI->draw_dc_textured_polytriangle = HD_Hide_DC_Textured_Polytris;

		dc->_hoops_AHSI->_hoops_GSHCP (POOL_NEW(dc->memory_pool, _hoops_GRASS)("antialias text deferral"));
	}
}

local void _hoops_SIASS (
	Net_Rendition alter &		nr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);

	nr.Modify();

	if (BIT(dc->flags, _hoops_GPHHP)) {
		nr->current |= _hoops_AHIHP;
		nr->_hoops_CPP.Modify()->_hoops_PRH._hoops_HRH = true;
		return;
	}

	if (!ANYBIT (dc->_hoops_CPGPR, _hoops_HPPGP|_hoops_RIPGP)) {
		/* _hoops_ISAP'_hoops_GRI _hoops_IGRC _hoops_CPIC _hoops_IS _hoops_SHH _hoops_CHCC, _hoops_HIS _hoops_SAHR _hoops_SPIC _hoops_GPP _hoops_ISHP */
		nr->current |= _hoops_AHIHP;
		return;
	}
	else if (BIT (nr->current, _hoops_AIPIP) ||
			 BIT (nr->_hoops_RCSHR, _hoops_AIPIP)) {
		/* _hoops_IIS _hoops_RCPGP/_hoops_HGGS-_hoops_IHIRC _hoops_HIISR _hoops_CCA _hoops_SCH */
		nr->current |= _hoops_AHIHP;
		return;
	}
	else if (BIT (nr->current, _hoops_CRSI) &&
			 !BIT (nr->current, _hoops_SRSI) &&
			 (dc->_hoops_SHPGR == QMoves_XOR ||
			  !BIT(dc->flags, _hoops_IIPIP))) {
		nr->_hoops_RCSHR &= ~_hoops_AHIHP;
		nr->_hoops_CPP.Modify()->_hoops_PRH.style = _hoops_GCPI;
		if (nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR < 1.0f) {
			nr->_hoops_IHA.Modify()->_hoops_CHA.Modify();
			HD_Setup_Screen_Door (nr);
		}
		return;
	}
	else if (nr->_hoops_IRR->_hoops_SRI == _hoops_PRAAP ||
		nr->_hoops_CPP->_hoops_PRH.style == _hoops_AIII ||
		BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSRAP)) {
		nr->_hoops_RCSHR &= ~_hoops_AHIHP;
		return;
	}

	nr->_hoops_CPP.Modify()->_hoops_PRH._hoops_HRH = true;

	nr->current |= _hoops_AHIHP;

	if (!BIT(dc->flags, _hoops_AASHP) &&
			nr->_hoops_CPP->_hoops_PRH._hoops_SRI == _hoops_PIII) {
		_hoops_APARR			_hoops_RRCI;
		_hoops_PRGIP			_hoops_PGCHP;

		_hoops_RRCI = _hoops_HGCGA (dc, "depth peeling deferral", nr);

		_hoops_PGCHP = _hoops_RRCHP | ((nr->_hoops_RCSHR&~nr->current)&_hoops_HPGSP);

		/* _hoops_HSPP _hoops_CCA _hoops_APRAR _hoops_HPRGR _hoops_CRAA [_hoops_IH _hoops_CPAP _hoops_CCA _hoops_RSSI] */
		HD_Vanillify_Actions (_hoops_PGCHP, _hoops_RRCI);

		nr->current |= _hoops_PGCHP;
		nr->_hoops_RCSHR |= _hoops_PGCHP;

		/* _hoops_AGRP _hoops_ARIPR _hoops_SR _hoops_PAH _hoops_PSCPR _hoops_GAR _hoops_PSPA (_hoops_CGSI _hoops_PII _hoops_SCHS _hoops_HGCR _hoops_PRGS _hoops_ISHP _hoops_IS _hoops_CCGI _hoops_AHI) */
		_hoops_RRCI->draw_3d_ellipse			= HD_Defer_Peeled_Trans_3D_Ellipse;
		_hoops_RRCI->draw_3d_polygon			= HD_Defer_Peeled_Trans_3D_Polygon;
		_hoops_RRCI->draw_3d_tristrip		= HD_Defer_Peeled_Trans_3D_Tristrip;
		_hoops_RRCI->_hoops_ARCI	= HD_Defer_Peeled_Trans_3D_Tristrip;
		_hoops_RRCI->draw_3d_polyedge		= HD_Defer_Peeled_Trans_3D_Polyedge;
		_hoops_RRCI->draw_3d_polyline		= HD_Defer_Peeled_Trans_3D_Polyline;
		_hoops_RRCI->draw_3d_text			= HD_Defer_Peeled_Trans_3D_Text;
		_hoops_RRCI->draw_3d_polymarker		= HD_Defer_Peeled_Trans_3D_Polymarker;
		_hoops_RRCI->draw_3d_marker			= HD_Defer_Peeled_Trans_3D_Marker;

		dc->_hoops_AHAGH = nr->_hoops_CPP->_hoops_PRH._hoops_RPAAP;
		dc->_hoops_PHAGH = nr->_hoops_CPP->_hoops_PRH._hoops_APAAP;

		nr->flags |= _hoops_PSPSP;

		dc->_hoops_AHSI->_hoops_GSHCP (POOL_NEW(dc->memory_pool, _hoops_GRASS)("depth peeling deferral"));
	}
	else if (ANYBIT (nr->current, _hoops_CSGGR|_hoops_CRSI)) {
		/*
		 * _hoops_RAH _hoops_ICCGR _hoops_CCSHP _hoops_ISSGR!
		 * _hoops_PS _hoops_GA'_hoops_RA _hoops_HSRPR _hoops_RH _hoops_HHIS _hoops_CGPR _hoops_CPHR (_hoops_GCASS _hoops_RH _hoops_RCPP _hoops_RHPC) _hoops_PGGA
		 * _hoops_SR _hoops_HHGC _hoops_IS _hoops_PSCPR _hoops_HCR _hoops_RGR _hoops_CPAP _hoops_CCGR _hoops_HCR _hoops_RH _hoops_CIGC _hoops_AGSAR
		 * _hoops_IRHH _hoops_PAII _hoops_PPRRR _hoops_CRGR _hoops_RH _hoops_HCHSR _hoops_SRHR.
		 * _hoops_RCASS _hoops_GRS _hoops_ACASS _hoops_RH _hoops_ACPH _hoops_GASR _hoops_IH _hoops_IHHH, _hoops_IS _hoops_PCASS
		 * _hoops_RH _hoops_HCASS _hoops_SICAR.
		 */

		HD_Handle_FBI_Pending_Window (nr);
		_hoops_AAASS (nr, _hoops_SRCP, path, false);
	}
	else {
		_hoops_APARR			_hoops_RRCI;

		/*
		 * _hoops_PS _hoops_PCASS _hoops_RH _hoops_HCASS _hoops_SICAR _hoops_SAHR _hoops_GGR _hoops_AGIR _hoops_SR _hoops_SPGA'_hoops_RA
		 * _hoops_SGGHA _hoops_GPP _hoops_GSIA _hoops_SGS _hoops_SSCP 3D _hoops_IHAHP.	_hoops_GPGP _hoops_SGS _hoops_PGRRR,
		 * _hoops_RH _hoops_CPAP _hoops_GRS _hoops_SHH _hoops_ICASS _hoops_HPP _hoops_ICCGR.
		 */

		_hoops_RRCI = _hoops_HGCGA (dc, "transparency", nr);

		_hoops_RRCI->_hoops_GCCGA		 = HD_Rasterize_DC_Spans_C24_U;
		_hoops_RRCI->_hoops_ACCGA		 = HD_Rasterize_DC_Spans_C24_G;
		_hoops_RRCI->_hoops_HCCGA		 = HD_Rasterize_DC_Spans_C24_R;

		dc->_hoops_AHSI->_hoops_GSHCP (POOL_NEW(dc->memory_pool, _hoops_GRASS)("transparency"));
	}
}


GLOBAL_FUNCTION void HD_Vanillify_Actions  (
	_hoops_PRGIP			_hoops_RCSHR,
	_hoops_APARR alter &	_hoops_ACPGR) {

	if (BIT (_hoops_RCSHR, _hoops_CGCHP)) {
		_hoops_ACPGR->draw_3d_elliptical_arc = HD_Std_3D_Elliptical_Arc;
		_hoops_ACPGR->draw_3d_nurbs_curve	= HD_Std_3D_NURBS_Curve;
		_hoops_ACPGR->draw_3d_polyline		= HD_Std_3D_Polyline;
		_hoops_ACPGR->draw_3d_infinite_line  = HD_Std_3D_Infinite_Line;
		_hoops_ACPGR->_hoops_PPAS	= HD_Draw_Indexicated_3D_Polyedge;
		_hoops_ACPGR->draw_3d_polyedge		= HD_Std_3D_Polyedge;
		_hoops_ACPGR->draw_3d_polyedge_from_tristrip = nullroutine;
	}

	if (ANYBIT (_hoops_RCSHR, _hoops_RRCHP|_hoops_CGCHP)) {
		_hoops_ACPGR->draw_3d_ellipse		= HD_Std_3D_Ellipse;
		_hoops_ACPGR->draw_3d_polygon		= HD_Std_3D_Polygon;
		_hoops_ACPGR->_hoops_SHCHP		= HD_Std_3D_Contour;
		_hoops_ACPGR->_hoops_ARCI	= HD_Draw_Indexicated_3D_Tristrip;
		_hoops_ACPGR->draw_3d_tristrip		= HD_Std_3D_Tristrip;
		_hoops_ACPGR->draw_3d_cylinder		= HD_Std_3D_Cylinder;
		_hoops_ACPGR->draw_3d_polycylinder	= HD_Std_3D_PolyCylinder;
		_hoops_ACPGR->draw_3d_sphere			= HD_Std_3D_Sphere;

		_hoops_ACPGR->_hoops_RPCGA		= HD_Std_DC_Polygon;
	}

	if (BIT (_hoops_RCSHR, _hoops_HGCHP)) {
		_hoops_ACPGR->draw_3d_marker			= HD_Std_3D_Marker;
		_hoops_ACPGR->_hoops_RIICP	= HD_Std_3D_Multimarker;
		_hoops_ACPGR->draw_3d_polymarker		= HD_Std_3D_Polymarker;
	}

	_hoops_ACPGR->draw_3d_grid				= HD_Std_3D_Grid;
	_hoops_ACPGR->draw_3d_polyhedron			= HD_Std_3D_Polyhedron;
	_hoops_ACPGR->draw_3d_nurbs_surface		= HD_Std_3D_NURBS_Surface;

	if (!ANYBIT (_hoops_ACPGR->mode, _hoops_CRSI|_hoops_SRSI))
		_hoops_ACPGR->_hoops_CHCI					= HD_Standard_Render;
}


local void _hoops_CCASS (
	Net_Rendition alter &		nr) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);

	nr.Modify();

	nr->current |= (nr->_hoops_RCSHR & _hoops_HPGSP);
	nr->current &= ~_hoops_CRSI;		/* _hoops_RCRP _hoops_IAGIP _hoops_IRS _hoops_CGGC _hoops_GICS */

	_hoops_HGCGA (dc, "vanilla", nr);
	HD_Vanillify_Actions (nr->_hoops_RCSHR, dc->_hoops_IPCI);
	dc->_hoops_AHSI->_hoops_GSHCP (POOL_NEW(dc->memory_pool, _hoops_GRASS)("vanilla"));
}



local void _hoops_SCASS (
	Net_Rendition alter &			nr) {
	Display_Context alter *			dc = _hoops_PGRCA(nr->_hoops_SRA);
	nr.Modify();
	_hoops_HHCR alter &		_hoops_IHCR = nr->transform_rendition.Modify();

	nr->current |= _hoops_GPRIP;
	_hoops_IHCR->flags |= _hoops_HHGGA;
	HD_Set_Z_Buffering_Transform (nr, true, false, 0.0f);

	if (_hoops_IHCR->_hoops_RGH->_hoops_PGH <=
			dc->_hoops_PGCC._hoops_ACPGH) {
		_hoops_IHCR->flags |= _hoops_CSP|_hoops_RCRIP;
	}
	else {
		_hoops_IHCR->flags |= _hoops_CSP;

		/* _hoops_IRHH _hoops_RCRR _hoops_SR'_hoops_ASAR _hoops_ARP _hoops_GH _hoops_IH _hoops_ICCGR 3d, _hoops_PSCR _hoops_PHHR _hoops_IAISR */
		nr->_hoops_RCSHR |= _hoops_HPGSP | _hoops_RRCHP |
						_hoops_CGCHP | _hoops_HGCHP;
		_hoops_CCASS (nr);
	}
}



local void _hoops_GSASS (
	Net_Rendition alter &		nr) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	nr.Modify();

	nr->current |= _hoops_SARIP;

	if ((nr->_hoops_IHA->_hoops_AGP == null ||
		 nr->_hoops_IHA->_hoops_AGP->count <= dc->_hoops_PGCC._hoops_HGCC) &&
		(nr->_hoops_RHP->_hoops_AGP == null ||
		 nr->_hoops_RHP->_hoops_AGP->count <= dc->_hoops_PGCC._hoops_HGCC) &&
		(nr->_hoops_SCP->_hoops_AGP == null ||
		 nr->_hoops_SCP->_hoops_AGP->count <= dc->_hoops_PGCC._hoops_HGCC)) {
		nr->transform_rendition.Modify()->flags |= _hoops_GRHH|_hoops_PRIR;

		HD_Set_Z_Buffering_Transform (nr, true, false, 0.0f);
	}
	else {
		_hoops_APARR	_hoops_RRCI;

		nr->transform_rendition.Modify()->flags |= _hoops_GRHH;

		HD_Set_Z_Buffering_Transform (nr, true, false, 0.0f);

		/* _hoops_IRHH _hoops_RCRR _hoops_SR'_hoops_ASAR _hoops_ARP _hoops_GH _hoops_IH _hoops_ICCGR 3d, _hoops_PSCR _hoops_PHHR _hoops_IAISR */

		/* _hoops_GIGHR: _hoops_GHAP _hoops_GA'_hoops_RA _hoops_HHSA _hoops_RH _hoops_PPGRR _hoops_IS _hoops_AGRP _hoops_PGGA _hoops_SGS _hoops_CHH
		 *		 _hoops_CRCH _hoops_ICSI 3D _hoops_RSASS _hoops_IH *_hoops_CPS* _hoops_PGGA
		 *		 _hoops_IIGR _hoops_RH _hoops_CSCAS _hoops_RGI _hoops_IIGR _hoops_HAH _hoops_AHPH _hoops_SS. _hoops_PHGP _hoops_PARAS _hoops_CIPIP
		 *		 _hoops_SIGPS _hoops_HHRCP-_hoops_PCSS _hoops_RRP _hoops_IS _hoops_SHH _hoops_IPAC
		 *		 _hoops_ASASS _hoops_GAR _hoops_PRAR _hoops_GAR _hoops_PSASS.
		 */

		_hoops_RRCI = _hoops_HGCGA (dc, "lighting", nr);

		/*_hoops_GA'_hoops_RA _hoops_AA _hoops_RGR _hoops_RH _hoops_HSPR:	 _hoops_HPGR->_hoops_SRGS = _hoops_HSASS;*/
		_hoops_RRCI->draw_3d_cylinder		= HD_Std_3D_Cylinder;
		_hoops_RRCI->draw_3d_polycylinder	= HD_Std_3D_PolyCylinder;
		_hoops_RRCI->draw_3d_sphere			= HD_Std_3D_Sphere;
		_hoops_RRCI->draw_3d_ellipse			= HD_Std_3D_Ellipse;
		_hoops_RRCI->draw_3d_grid			= HD_Std_3D_Grid;
		_hoops_RRCI->draw_3d_polygon			= HD_Std_3D_Polygon;
		_hoops_RRCI->_hoops_SHCHP			= HD_Std_3D_Contour;
		_hoops_RRCI->draw_3d_nurbs_surface	= HD_Std_3D_NURBS_Surface;
		_hoops_RRCI->_hoops_ARCI	= HD_Draw_Indexicated_3D_Tristrip;
		_hoops_RRCI->_hoops_PPAS	= HD_Draw_Indexicated_3D_Polyedge;
		_hoops_RRCI->draw_3d_tristrip		= HD_Std_3D_Tristrip;
		_hoops_RRCI->draw_3d_polyedge		= HD_Std_3D_Polyedge;
		_hoops_RRCI->draw_3d_polymarker		= HD_Std_3D_Polymarker;
		_hoops_RRCI->draw_3d_polyedge_from_tristrip = nullroutine;
		_hoops_RRCI->draw_3d_polyhedron		= HD_Std_3D_Polyhedron;

		dc->_hoops_AHSI->_hoops_GSHCP (POOL_NEW(dc->memory_pool, _hoops_GRASS)("lighting"));
	}
}



local void _hoops_ISASS (
	Net_Rendition const & 		nr,
	Image const *				image) {
	float						_hoops_IACC, _hoops_CACC, _hoops_SACC;
	int							width, height;
	DC_Point					box[5];

	if (BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_RHCRP) &&
		!BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_HPCRP)) {
		if (!HD_Calc_Image_Position_And_Size (nr, image, &width, &height, &_hoops_IACC, &_hoops_CACC, &_hoops_SACC))
			return;

		box[0].x = box[3].x = _hoops_IACC - width  * 0.5f;
		box[1].x = box[2].x = _hoops_IACC + width  * 0.5f;
		box[0].y = box[1].y = _hoops_CACC - height * 0.5f;
		box[3].y = box[2].y = _hoops_CACC + height * 0.5f;
		box[0].z = box[1].z = box[2].z = box[3].z = _hoops_SACC;
		box[4].x = box[0].x;
		box[4].y = box[0].y;
		box[4].z = box[0].z;

		_hoops_SCGGA (nr, 5, box);
	}
}

struct _hoops_CSASS : public _hoops_HIHCP {
	int					pass;

	_hoops_CSASS (int p) : pass (p) {}

	bool _hoops_SIHCP (Net_Rendition alter & nr, bool _hoops_PPHPP) alter {

		if (_hoops_PPHPP)
			return true;

		Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
		nr.Modify();

		nr->_hoops_RCSHR &= ~(_hoops_HSGGR|_hoops_ISGGR);
		if (!ANYBIT(nr->current, _hoops_GSSHP|_hoops_RSSHP) &&
			ANYBIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP|_hoops_CRAAP) &&
			BIT(dc->flags, _hoops_AASHP))
			nr->_hoops_IRR.Modify()->_hoops_CHP &= ~(_hoops_SHP|_hoops_CRAAP);

		dc->_hoops_RASIP(pass);
		switch (pass) {
			case _hoops_HRIIP: {
				/* _hoops_RPPS & _hoops_SSH-_hoops_SRHR _hoops_SCAC _hoops_RGAR (_hoops_CPHR _hoops_ARPP _hoops_SR _hoops_HHSP _hoops_CSCR _hoops_GGI) */
			}	break;

			case _hoops_GICI: {
				/* _hoops_RSSI, _hoops_GSSR _hoops_AIRC */
				_hoops_CGRA alter &	_hoops_GCRCS = nr->_hoops_SAIR.Modify();

				/* _hoops_SSASS->_hoops_SPGCS &= _hoops_AAHRC|_hoops_GGPSS; */
				_hoops_GCRCS->_hoops_ASIHP &= ~_hoops_GCARP;
				_hoops_GCRCS->_hoops_ASIHP |= _hoops_ACARP;

				HD_Fixup_Attributes (nr, null, _hoops_IPIHP);
				dc->flags &= ~_hoops_RASS;

				(*dc->_hoops_ACPGR->init_picture) (nr);
			}	break;

			case _hoops_RICI: {
				/* _hoops_RSSI, _hoops_CSCR _hoops_GGI _hoops_GRGR */
				_hoops_GRGH alter &		_hoops_APIHP = nr->_hoops_IRR.Modify();
				_hoops_CGRA alter &	_hoops_GCRCS = nr->_hoops_SAIR.Modify();

				/* _hoops_SSASS->_hoops_SPGCS &= _hoops_AAHRC|_hoops_GGPSS|_hoops_ASHHP; */
				_hoops_APIHP->_hoops_GIRC = true;
				_hoops_GCRCS->_hoops_ASIHP &= ~_hoops_GCARP;
				_hoops_GCRCS->_hoops_ASIHP |= _hoops_ACARP;

				HD_Fixup_Attributes (nr, null, _hoops_IPIHP);
				dc->flags &= ~_hoops_RASS;

				(*dc->_hoops_ACPGR->init_picture) (nr);
			}	break;

			case _hoops_CRIIP: {
				/* _hoops_GRAA-_hoops_RSSI, _hoops_HCH _hoops_AAGIR, _hoops_CCSHP _hoops_AIRC */
				/*	   _hoops_HSGR _hoops_RPP _hoops_SR _hoops_PAH _hoops_ACPA _hoops_IIH _hoops_CHR _hoops_PIRC		*/

				_hoops_CGRA alter &	_hoops_GCRCS = nr->_hoops_SAIR.Modify();
				_hoops_HHCR alter &	_hoops_GGCC = nr->transform_rendition.Modify();

				_hoops_GCRCS->_hoops_ASIHP &= ~_hoops_GCARP;
				_hoops_GCRCS->_hoops_ASIHP |= _hoops_ACARP;
				_hoops_GGCC->flags |= _hoops_PIHIP;
				_hoops_GGCC->flags |= _hoops_ISH;

				HD_Fixup_Attributes (nr, null, _hoops_ASPSP);
				dc->_hoops_IPCI->draw_3d_image = _hoops_ISASS;
				dc->flags &= ~_hoops_RASS;

				(*dc->_hoops_ACPGR->init_picture) (nr);
			}	break;

			case _hoops_GAIIP: {
				/* _hoops_GRAA-_hoops_RSSI, _hoops_GSSR _hoops_AIRC */
				_hoops_CGRA alter &	_hoops_GCRCS = nr->_hoops_SAIR.Modify();

				_hoops_GCRCS->_hoops_ASIHP &= ~_hoops_GCARP;
				_hoops_GCRCS->_hoops_ASIHP |= _hoops_ACARP;

				HD_Fixup_Attributes (nr, null, _hoops_IPIHP);
				dc->_hoops_IPCI->draw_3d_image = _hoops_ISASS;
				dc->flags &= ~_hoops_RASS;

				(*dc->_hoops_ACPGR->init_picture) (nr);
			}	break;
		}

		return true;
	}
};

struct _hoops_RGPSS : public _hoops_HIHCP {
	bool _hoops_SIHCP (Net_Rendition alter & nr, bool _hoops_PPHPP) alter {
		Display_Context alter *			dc = _hoops_PGRCA(nr->_hoops_SRA);
		_hoops_HHCR const &		_hoops_IHCR = nr->transform_rendition;

		if (!_hoops_PPHPP) {
			_hoops_HGSGA (dc, "zhlr");

			if (dc->_hoops_HASS[dc->_hoops_IASS] != null)
				HD_See_Whats_Hidden (nr);
			if (dc->_hoops_GPSS[dc->_hoops_IASS] != null)
				_hoops_SSGGR (dc);

			(*dc->_hoops_ACPGR->_hoops_CAAGR) (nr,
											_hoops_IHCR->_hoops_AGAA.left, _hoops_IHCR->_hoops_AGAA.right,
											_hoops_IHCR->_hoops_AGAA.bottom, _hoops_IHCR->_hoops_AGAA.top);
		}

		return true;
	}
};

local void _hoops_AGPSS (
	Net_Rendition alter &		nr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	nr.Modify();

	nr->flags &= ~_hoops_ASPSP;

	if (BIT (nr->_hoops_RCSHR, _hoops_GAHPP)) {
		/* _hoops_IPIHR _hoops_AHCA _hoops_CCSHP! */
		nr->_hoops_RCSHR &= ~_hoops_IRGIP;
		return;
	}
	else if (BIT (nr->current, _hoops_CRSI) ||
			 BIT(dc->flags, _hoops_AASHP)) {
		/* _hoops_SR _hoops_GGHP _hoops_ICCGR _hoops_CCSHP _hoops_RGAR! */
		nr->_hoops_RCSHR &= ~_hoops_HSSHP;
		/* _hoops_RCAPR._hoops_PSGSP (_hoops_PPR _hoops_GAAP _hoops_SHPP-_hoops_SSH) _hoops_HRGR _hoops_HGGC _hoops_GPP */
		return;
	}


	nr->current |= _hoops_HSSHP;
	_hoops_HGCGA (dc, "zhlr", nr);	// _hoops_PSP _hoops_IRGH _hoops_SHPH, _hoops_HIH _hoops_CGHI _hoops_HHHH _hoops_RRP _hoops_IS _hoops_GCGRA _hoops_CSCR _hoops_ACPH

	// _hoops_SCGR _hoops_AHHRA _hoops_GIIS _hoops_SAGGR _hoops_RH _hoops_CGHI _hoops_RIH, _hoops_HIASR _hoops_RRAI _hoops_GGR _hoops_PIIA _hoops_AGR
	dc->_hoops_AHSI->_hoops_GARSP (POOL_NEW(dc->memory_pool, _hoops_CSASS)(_hoops_GAIIP));
	dc->_hoops_AHSI->_hoops_GSHCP (POOL_NEW(dc->memory_pool, _hoops_GRASS)("zhlr"));

	dc->Push_Tree (nr, _hoops_SRCP, path);
	dc->_hoops_AHSI->_hoops_GARSP (POOL_NEW(dc->memory_pool, _hoops_CSASS)(_hoops_CRIIP));
	dc->_hoops_AHSI->_hoops_GSHCP (POOL_NEW(dc->memory_pool, _hoops_GRASS)("zhlr"));

	dc->Push_Tree (nr, _hoops_SRCP, path);
	dc->_hoops_AHSI->_hoops_GARSP (POOL_NEW(dc->memory_pool, _hoops_CSASS)(_hoops_RICI));
	dc->_hoops_AHSI->_hoops_GSHCP (POOL_NEW(dc->memory_pool, _hoops_GRASS)("zhlr"));

	dc->Push_Tree (nr, _hoops_SRCP, path);
	dc->_hoops_AHSI->_hoops_GARSP (POOL_NEW(dc->memory_pool, _hoops_CSASS)(_hoops_GICI));
	dc->_hoops_AHSI->_hoops_GSHCP (POOL_NEW(dc->memory_pool, _hoops_RGPSS)());

	dc->Push_Tree (nr, _hoops_SRCP, path);	// _hoops_RPPS _hoops_GIR _hoops_SIPP, _hoops_HIH _hoops_SR _hoops_HGGC _hoops_RRP _hoops_RH _hoops_RCAR _hoops_HPGR _hoops_RGR _hoops_GHIR
	dc->_hoops_AHSI->_hoops_GARSP (POOL_NEW(dc->memory_pool, _hoops_CSASS)(_hoops_HRIIP));
	dc->_hoops_AHSI->_hoops_GSHCP (POOL_NEW(dc->memory_pool, _hoops_GRASS)("zhlr"));
}

local void _hoops_PGPSS (
	Net_Rendition alter &		nr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	nr.Modify();
	UNREFERENCED(path);

	if (BIT (nr->_hoops_RCSHR, _hoops_GAHPP)) {
		/* _hoops_IPIHR _hoops_AHCA _hoops_CCSHP! */
		nr->_hoops_RCSHR &= ~_hoops_IRGIP;
	}
#if 0
	else if (!ANYBIT (dc->_hoops_CPGPR, _hoops_HPPGP|_hoops_IHPGP) &&
			 !BIT (nr->_hoops_RCSHR, _hoops_CRSI)) {
		/* _hoops_ISAP'_hoops_GRI _hoops_IGRC _hoops_CPIC _hoops_IS _hoops_SHH _hoops_CHCC, _hoops_HIS _hoops_SAHR _hoops_SPIC _hoops_GPP _hoops_ISHP */
		nr->current |= _hoops_CSGGR|_hoops_GSSHP;
		nr->_hoops_RCSHR &= ~(_hoops_RSSHP|_hoops_CISHP);
	}
#endif
	else if (BIT (nr->current, _hoops_CRSI) ||
			 BIT(dc->flags, _hoops_AASHP)) {
		/* _hoops_SR _hoops_GGHP _hoops_ICCGR _hoops_CCSHP _hoops_RGAR! */
		nr->_hoops_RCSHR &= ~_hoops_GSSHP;
#ifdef DISABLE_SORTING_HSR
		nr->_hoops_RCSHR &= ~_hoops_CSGGR;
#endif
		/* _hoops_RCAPR._hoops_PSGSP (_hoops_PPR _hoops_GAAP _hoops_SHPP-_hoops_SSH) _hoops_HRGR _hoops_HGGC _hoops_GPP */
	}
	else {
		/* _hoops_SGH _hoops_GSIA _hoops_AHCR _hoops_SRHR _hoops_IS _hoops_AA _hoops_RH _hoops_IPHR */

		_hoops_HHCR const &		_hoops_IHCR = nr->transform_rendition.Modify();

		HD_Set_Z_Buffering_Transform (nr, true, true, dc->_hoops_PGCC._hoops_PASHP);

		if (nr->_hoops_ASIR->window.pattern != FP_WINDOW_TRANS_NO_ZCLEAR &&
			!BIT (nr->_hoops_SAIR->_hoops_ASIHP, _hoops_ACARP) &&
			(BIT (nr->_hoops_SAIR->_hoops_ASIHP, _hoops_GCARP) ||
			 !BIT(dc->flags, _hoops_RAAGH) ||
			 BIT (dc->_hoops_CPGPR, _hoops_ICHPA) ||

			/* (_hoops_RPP _hoops_SCH _hoops_ASSP'_hoops_RA _hoops_HS _hoops_IRS _hoops_RPPS, _hoops_PSCR _hoops_SR *_hoops_SIAS* _hoops_SHH _hoops_GHGA
			 *	_hoops_ISSC-_hoops_IS-_hoops_RIPS _hoops_GRAA-_hoops_CCSHP _hoops_CPCP, _hoops_PPR _hoops_RH _hoops_AHCR _hoops_SRHR
			 *	_hoops_CHH _hoops_HS _hoops_IS _hoops_SHH _hoops_RPSGA.)
			 */

			/*** _hoops_ASAI _hoops_HGPSS _hoops_RPAAR _hoops_HGAPR! (_hoops_PCPA _hoops_RPP _hoops_CGGRA _hoops_ACIPR & _hoops_SHPP _hoops_CCSHP?) ***/

			 (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|_hoops_GISIR) &&
			  BIT (_hoops_SRCP->_hoops_RRHH, _hoops_PASIR)))) {
			_hoops_HCSIR const		*_hoops_ICSIR = null;

			if (nr->_hoops_SAIR->_hoops_ASSIR != null)
				_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

			if (dc->_hoops_RPSS[dc->_hoops_IASS] != null) {
				if (!(_hoops_GGPGR(nr)))
					HD_Draw_Deferred_3D_Geometry (dc->_hoops_RPSS[dc->_hoops_IASS], true);
				HD_Free_Deferred_3D_Geometry (dc->_hoops_RPSS[dc->_hoops_IASS]);
				dc->_hoops_RPSS[dc->_hoops_IASS] = null;
			}

			(*dc->_hoops_ACPGR->_hoops_CAAGR) (nr,
											_hoops_IHCR->_hoops_AGAA.left, _hoops_IHCR->_hoops_AGAA.right,
											_hoops_IHCR->_hoops_AGAA.bottom, _hoops_IHCR->_hoops_AGAA.top);

			if (_hoops_ICSIR != null)		/* ?_hoops_PRGIR _hoops_HIIC */
				_hoops_PGRCA(_hoops_ICSIR)->_hoops_HRSCP = true;

			dc->_hoops_CPGPR |= _hoops_GGARA & ~_hoops_AASCA;
		}

		nr->current |= _hoops_CSGGR|_hoops_GSSHP;
		nr->_hoops_RCSHR &= ~(_hoops_RSSHP|_hoops_CISHP);
	}
}


local void _hoops_IGPSS (
	Net_Rendition alter &		nr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	nr.Modify();

	if (_hoops_SRCP == null ||
		!BIT (nr->_hoops_RCSHR, _hoops_GSSHP) ||
		!BIT(dc->flags, _hoops_RCHCP)) {
		nr->_hoops_RCSHR &= ~_hoops_SRGIP;
		return;
	}

	nr->current |= _hoops_SRGIP;

	_hoops_SPAGR						_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
	_hoops_AHAGR *				_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, path);

	if (_hoops_CSC->_hoops_IGSGP() != null &&
		BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_PISSR)) {
		HD_Delete_Octree (dc->_hoops_RIGC, nr, _hoops_CSC->_hoops_IGSGP());
		_hoops_CSC->_hoops_AGSGP (null);
	}
	if (_hoops_CSC->_hoops_IGSGP() == null) {
		_hoops_PGSGP *		_hoops_AHGGC = HD_Generate_Octree (nr, _hoops_SRCP, path);

		_hoops_CSC->_hoops_AGSGP (_hoops_AHGGC);
		if (_hoops_CSC->_hoops_APHGA == null)
			_hoops_CSC->_hoops_APHGA = nr;
		if (nr->transform_rendition->_hoops_RHPHP != _hoops_HHPHP)
			HD_Send_Queries (nr, _hoops_AHGGC);	/* _hoops_AA _hoops_RGR _hoops_SPR _hoops_HA _hoops_IH _hoops_HGAI _hoops_SGH */
	}

	if (nr->transform_rendition->_hoops_RHPHP != _hoops_HHPHP)
		HD_Process_Queries (nr, _hoops_CSC->_hoops_IGSGP());

	/* _hoops_CCAH _hoops_IIPRH _hoops_IS _hoops_HPPP _hoops_SPHR (_hoops_APAP _hoops_RSGR _hoops_IIGR _hoops_CGPSS) */
	if (nr->transform_rendition->_hoops_RHPHP != _hoops_HHPHP) {
		_hoops_PGISP *		_hoops_HIGGC;

		ZALLOC (_hoops_HIGGC, _hoops_PGISP);
		_hoops_HIGGC->nr = nr;
		_hoops_HIGGC->_hoops_HGISP = _hoops_CSC->_hoops_IGSGP();
		_hoops_HIGGC->next = dc->_hoops_PPSIP;
		dc->_hoops_PPSIP = _hoops_HIGGC;
	}
}


/*
 * _hoops_GIGHR: _hoops_SGPSS _hoops_HRGR _hoops_IGI _hoops_IS _hoops_PSCPR _hoops_PRRGS _hoops_IIGR _hoops_PCCP _hoops_GGSR-_hoops_IIGR-_hoops_AGR
 * _hoops_AIIAP _hoops_CCGR _hoops_SR _hoops_ACPA _hoops_SR _hoops_RRP _hoops_SCH.	 _hoops_SGPR _hoops_IIGR _hoops_GRPSS (_hoops_HII
 * _hoops_RRPSS) _hoops_HRGR _hoops_HAR _hoops_PRCCS (_hoops_CGH _hoops_SGH _hoops_CPGGR _hoops_SGI _hoops_RIIA),
 * _hoops_HIH _hoops_SR _hoops_PAH _hoops_HGCR _hoops_SGGR _hoops_CCA _hoops_SCH _hoops_CR _hoops_RH _hoops_CHAPA _hoops_ARPSS'_hoops_RA _hoops_RPII _hoops_HPSPR _hoops_GAPR
 * _hoops_HPP _hoops_PRPHS.
 */


local void _hoops_PRPSS (
	Net_Rendition const &	nr,
	_hoops_CRCP const *			_hoops_SRCP,
	Activity				which) {
	_hoops_CRCP					_hoops_IIAPH;

	/* _hoops_HPGGR _hoops_HCR _hoops_GGSR-_hoops_IIGR-_hoops_AGR _hoops_CPAP _hoops_HHASA'_hoops_GRI _hoops_GIAA "_hoops_PHHIP" */

	if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GGPSA)) {
		if (_hoops_SRCP->_hoops_RGRPR == null) {
			/* _hoops_HIIC _hoops_HRGR _hoops_RPPR _hoops_PRGIR */
			_hoops_PGRCA(_hoops_SRCP)->_hoops_PHSI &= ~_hoops_GGPSA;
			return;
		}

		ZERO_STRUCT(&_hoops_IIAPH, _hoops_CRCP);
		_hoops_IIAPH.type = _hoops_IRCP;
		_hoops_IIAPH.next = _hoops_SRCP->_hoops_RGRPR;

		HI_Redraw_Downstream (nr->_hoops_SRA->_hoops_RIGC, (_hoops_SIHIR alter *)&_hoops_IIAPH, which, &_hoops_SGPGP::_hoops_GRPGP);
	}
}


local void _hoops_HRPSS (
	Net_Rendition const &		inr,
	Geometry const *			test,
	Action_Mask					mask) {
	Net_Rendition				nr = inr;
	bool						_hoops_IRPSS = false;
	_hoops_CRCP const *				_hoops_SRCP = test->owner;
	_hoops_HCSIR const	*	_hoops_ICSIR = null;
	int							_hoops_CRPSS = nr->_hoops_IRR->_hoops_GAHA;
	Display_Context const *		dc = nr->_hoops_SRA;

	/* _hoops_HHGC _hoops_IS _hoops_AIIAP _hoops_HCR _hoops_APSAR _hoops_IIGR _hoops_CPAP _hoops_SGS _hoops_CHR _hoops_RSRGR _hoops_PPSPR
	 * _hoops_IH _hoops_IGSIP.
	 */

	if (nr->_hoops_SAIR->_hoops_ASSIR != null)
		_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	if (_hoops_ICSIR != null)
		_hoops_PGRCA(_hoops_ICSIR)->_hoops_GHIAA = true;

	nr->_hoops_IRR->_hoops_GAHA = Display_List_NONE;

	if (ANYBIT (test->_hoops_CPGPR | (test->_hoops_SPGPR & dc->_hoops_RIIAP),
				_hoops_ICHPA|_hoops_HPPGP) &&
		BIT (test->_hoops_RRHH, _hoops_PASIR)) {
		/* _hoops_SR'_hoops_GHGP _hoops_RRP _hoops_IS _hoops_AIIAP _hoops_CPS _hoops_RAS _hoops_RGR _hoops_SPR _hoops_APIC */
		_hoops_RPHPP (nr, test, mask, false);
		_hoops_IRPSS = true;
	}
	else do {
		if (ANYBIT (test->_hoops_CPGPR | (test->_hoops_SPGPR & dc->_hoops_RIIAP),
					_hoops_ICHPA|_hoops_HPPGP)) {
			_hoops_RPHPP (nr, test, mask, true);
			_hoops_IRPSS = true;
		}
	} while ((test = test->next) != null && !BIT (test->_hoops_RRHH, _hoops_PASIR));

	nr->_hoops_IRR->_hoops_GAHA = _hoops_CRPSS;

	if (_hoops_IRPSS) {
		_hoops_PRPSS (nr, _hoops_SRCP, _hoops_IHSSR|_hoops_PHPGP);

	    if (_hoops_ICSIR != null && !ANYBIT(nr->current, _hoops_CRSI | _hoops_SRSI))
		    _hoops_PGRCA(_hoops_ICSIR)->_hoops_PSPIP = false;
    }
}




local void _hoops_SRPSS (
	Net_Rendition alter &		nr) {
	Display_Context const *		dc = nr->_hoops_SRA;
	nr.Modify();
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;

	/* _hoops_PGSA _hoops_IRS 2d _hoops_HHIS */
	nr->current |= _hoops_GAHPP;
	if (BIT (nr->_hoops_RCSHR, _hoops_RSSHP) &&
		BIT (dc->_hoops_CPGPR, _hoops_IHPGP)) {
		_hoops_PGRCA(dc)->_hoops_CPGPR &= ~_hoops_IHPGP;
		_hoops_PGRCA(dc)->_hoops_CPGPR |= _hoops_RCGSA & ~_hoops_AASCA;
	}
	_hoops_PRGIP	_hoops_HRGIP = nr->_hoops_RCSHR & nr->current & _hoops_RSSHP;

	nr->_hoops_RCSHR &= ~_hoops_IRGIP;
	nr->_hoops_RCSHR |= _hoops_HRGIP;

	if (_hoops_IHCR->_hoops_HGSC != _hoops_SIPHP)
		nr->transform_rendition.Modify()->_hoops_HGSC = _hoops_CIPHP;

	if (BIT(_hoops_IHCR->flags, _hoops_PASP)) {
		nr->transform_rendition.Modify();
		HD_Set_Z_Buffering_Transform (nr, false, false, 0.0f);
	}
}




struct _hoops_GAPSS : public _hoops_HIHCP {
	bool _hoops_SIHCP (Net_Rendition alter & nr, bool _hoops_PPHPP) alter {
		if (!_hoops_PPHPP)
			_hoops_HGSGA (nr->_hoops_SRA, "ordered render");
		HD_Defer_Ordered (nr, _hoops_PPHPP);
		return true;
	}
};

local void _hoops_RAPSS (
	Net_Rendition alter &		nr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path) {
	UNREFERENCED (_hoops_SRCP);
	UNREFERENCED (path);

	/* _hoops_PSCPR _hoops_IGCGA _hoops_RIIA _hoops_IIGR _hoops_GCAC _hoops_CAPR _hoops_HA */
	nr.Modify()->current |= _hoops_CSPPP;

	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);

	_hoops_HGCGA (dc, "ordered render", nr);
	dc->_hoops_IPCI->_hoops_CHCI = HD_Ordered_Render;

	_hoops_HPHPP * _hoops_IAHPP;
	POOL_ZALLOC (_hoops_IAHPP, _hoops_HPHPP, dc->memory_pool);

	_hoops_IAHPP->_hoops_SAHPP = MAX_FLOAT;
	_hoops_IAHPP->_hoops_GPHPP = -MAX_FLOAT;
	_hoops_IAHPP->_hoops_GGCRP = nr->_hoops_CPP->_hoops_GGCRP;
	_hoops_IAHPP->_hoops_RGCRP = nr->_hoops_CPP->_hoops_RGCRP;
	_hoops_IAHPP->_hoops_AGCRP = nr->_hoops_CPP->_hoops_AGCRP;

	_hoops_IAHPP->next = dc->_hoops_IAHPP;
	dc->_hoops_IAHPP = _hoops_IAHPP;

	dc->_hoops_AHSI->_hoops_GSHCP (POOL_NEW(dc->memory_pool, _hoops_GAPSS)());
}



/*****************************************************************************/

/* _hoops_PIH _hoops_IH _hoops_IHGP _hoops_RCAR _hoops_CRHH */
local int const _hoops_AAPSS[4] = {0,1,2,3};
local int const _hoops_PAPSS[4] = {0,0,0,0};
local _hoops_RSSH const _hoops_HAPSS[4*3] = {
				0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f
		};
local _hoops_RSSH const _hoops_IAPSS[4*3] = {
				1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f
		};


local void _hoops_CAPSS (
	Net_Rendition alter &		nr) {

	nr.Modify()->_hoops_ARA.Modify()->_hoops_PRSI.options &= ~_hoops_HRSI;
}

// _hoops_SPRCS _hoops_HASC _hoops_CCA _hoops_SGCR _hoops_RRGR
local float _hoops_SAPSS  (Net_Rendition const & nr, Bounding const & bounding) {

	_hoops_HHCR const &		_hoops_IHCR = nr->transform_rendition;
	/* _hoops_CCRHS _hoops_RH _hoops_IASC _hoops_CISAR _hoops_CRGR _hoops_SHPR _hoops_GC, _hoops_PPR _hoops_HGCR _hoops_RH _hoops_GARRA 2D _hoops_ARRGR */
	_hoops_RPRA const *matrix = (_hoops_RPRA const *) _hoops_IHCR->matrix->data.elements;

	Point	_hoops_GPPSS[8];

	bounding->cuboid._hoops_GPSC(&_hoops_GPPSS[0]);

	Point min, max;
	min.x = min.y = MAX_FLOAT;
	max.x = max.y = -MAX_FLOAT;

	bool	_hoops_RAHIS = false;

	for (int i = 0; i < 8; i++) {
		float w = _hoops_PHCP (matrix, _hoops_GPPSS[i]);
		if (w >= _hoops_IHCR->_hoops_CHCR) {
			float x = _hoops_HPRA (matrix, _hoops_GPPSS[i]) / w;
			float y = _hoops_IPRA (matrix, _hoops_GPPSS[i]) / w;
			if (x < min.x)
				min.x = x;
			if (y < min.y)
				min.y = y;
			if (x > max.x)
				max.x = x;
			if (y > max.y)
				max.y = y;
		}
		else
			_hoops_RAHIS = true;
	}

	if (max.x < min.x)	// _hoops_HCR _hoops_GHIPR _hoops_RH _hoops_RHC?
		return 0.0f;
	if (_hoops_RAHIS)
		return 1.0f;	// ?

	float	area = (max.x - min.x) * (max.y - min.y);
	float	_hoops_PRPHA = area / (nr->_hoops_SRA->current._hoops_PRPSR.x * nr->_hoops_SRA->current._hoops_PRPSR.y);

	return _hoops_PRPHA;
}

struct _hoops_RPPSS : public _hoops_HIGGH {
	private:
		_hoops_CRCP const *		top;
	public:
		_hoops_RPPSS (_hoops_CRCP const * start) : top (start) {}
		bool _hoops_PPCRR (Net_Rendition alter & nr, _hoops_CRCP const * _hoops_SRCP, _hoops_HICS const & path);
};

bool _hoops_RPPSS::_hoops_PPCRR (
	Net_Rendition alter &		nr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path) alter {
	UNREFERENCED(path);

	if (BIT (nr->_hoops_RCSHR, _hoops_CRHPP) && _hoops_SRCP != top)
		return false;

	if (BIT(_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR))
		return false;

	if (!BIT (_hoops_SRCP->_hoops_RCGC, T_TEXT))
		return false;

	nr->_hoops_RCSHR &= _hoops_GAHPP;
	nr->current = nr->_hoops_RCSHR;

	/* _hoops_ASIGA _hoops_SHHH _hoops_RGR _hoops_SHH _hoops_CPHR _hoops_IRS _hoops_GIH _hoops_PPRRR? */
	nr->_hoops_RSGC->action.draw_segment = nullroutine;
	nr->_hoops_RSGC->action.draw_segment_tree = nullroutine;
	nr->_hoops_RSGC->action.draw_text = nullroutine;
	nr->_hoops_RSGC->action.draw_dc_polyline = nullroutine;

	return true;
}


local bool _hoops_SGCHS () {return false;}


local void _hoops_GPPHP (
	Display_Context const *		dc,
	_hoops_HRPA const *			matrix,
	_hoops_HHRA const *				_hoops_SPH,
	_hoops_PC alter &		_hoops_RPPHP,
	_hoops_AS const *		_hoops_APPHP) {
	_hoops_AS alter *		light;

	_hoops_RPPHP->_hoops_CGR = null;
	do {
		POOL_ALLOC (light, _hoops_AS, dc->memory_pool);
		_hoops_RSAI (_hoops_APPHP, _hoops_AS, light);

		HI_Compute_Transformed_Vectors (1, &_hoops_APPHP->direction, &matrix->elements[0][0],
										&light->direction);
		if (light->count != 0) {
			ALLOC_ARRAY (light->points, light->count, Point);
			HI_Compute_Transformed_Points (light->count, _hoops_APPHP->points, &matrix->elements[0][0],
											_hoops_PGRCA(light->points));
		}

		light->next = _hoops_RPPHP->_hoops_CGR;
		_hoops_RPPHP->_hoops_CGR = light;

		light->_hoops_ARSR.x = light->direction.x - _hoops_SPH->_hoops_IIPCR.x;
		light->_hoops_ARSR.y = light->direction.y - _hoops_SPH->_hoops_IIPCR.y;
		light->_hoops_ARSR.z = light->direction.z - _hoops_SPH->_hoops_IIPCR.z;
		HI_Normalize (&light->_hoops_ARSR);
	} while ((_hoops_APPHP = _hoops_APPHP->next) != null);
}

local void _hoops_APPSS (
	Net_Rendition alter &		nr,
	_hoops_HRPA const *			matrix) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_PC				_hoops_ASPHP;
	_hoops_PC				_hoops_PSPHP;
	_hoops_PC				_hoops_HSPHP;

	if ((_hoops_ASPHP = nr->_hoops_IHA->_hoops_AGP) != null) {
		_hoops_PC				_hoops_RPPHP = _hoops_PC::Create(nr->_hoops_SRA);

		_hoops_CIGA alter &		_hoops_SIGA = nr.Modify()->_hoops_IHA.Modify();

		_hoops_SIGA->_hoops_AGP = _hoops_RPPHP;

		_hoops_RPPHP->scale = _hoops_ASPHP->scale;
		_hoops_RPPHP->count = _hoops_ASPHP->count;
		_hoops_RPPHP->_hoops_ISPHP =
					 _hoops_ASPHP->_hoops_ISPHP;

		_hoops_GPPHP (dc, matrix, _hoops_IHCR->_hoops_SPH, _hoops_RPPHP, _hoops_ASPHP->_hoops_CGR);
	}

	if ((_hoops_PSPHP = nr->_hoops_RHP->_hoops_AGP) != null) {
		Line_Rendition alter &		_hoops_GHP = nr.Modify()->_hoops_RHP.Modify();

		if (_hoops_PSPHP == _hoops_ASPHP)		// _hoops_CCAH _hoops_ISHA _hoops_SS _hoops_PAH _hoops_SHH _hoops_PSHR _hoops_GAR _hoops_CCAH _hoops_HSP _hoops_SS
			_hoops_GHP->_hoops_AGP = nr->_hoops_IHA->_hoops_AGP;
		else {
			_hoops_PC				_hoops_RPPHP = _hoops_PC::Create(nr->_hoops_SRA);

			_hoops_GHP->_hoops_AGP = _hoops_RPPHP;

			_hoops_RPPHP->scale = _hoops_PSPHP->scale;
			_hoops_RPPHP->count = _hoops_PSPHP->count;
			_hoops_RPPHP->_hoops_ISPHP =
						 _hoops_PSPHP->_hoops_ISPHP;

			_hoops_GPPHP (dc, matrix, _hoops_IHCR->_hoops_SPH, _hoops_RPPHP, _hoops_PSPHP->_hoops_CGR);
		}
	}

	if ((_hoops_HSPHP = nr->_hoops_SCP->_hoops_AGP) != null) {
		_hoops_ICP alter 		_hoops_CCP = nr.Modify()->_hoops_SCP.Modify();

		if (_hoops_HSPHP == _hoops_ASPHP)		// _hoops_CCAH _hoops_GPIA _hoops_SS _hoops_PAH _hoops_SHH _hoops_PSHR _hoops_GAR _hoops_CCAH _hoops_HSP _hoops_SS
			_hoops_CCP->_hoops_AGP = nr->_hoops_IHA->_hoops_AGP;
		else if (_hoops_HSPHP == _hoops_PSPHP)	// _hoops_CCAH _hoops_GPIA _hoops_SS _hoops_PAH _hoops_SHH _hoops_PSHR _hoops_GAR _hoops_CCAH _hoops_ISHA _hoops_SS
			_hoops_CCP->_hoops_AGP = nr->_hoops_RHP->_hoops_AGP;
		else {
			_hoops_PC				_hoops_RPPHP = _hoops_PC::Create(nr->_hoops_SRA);

			_hoops_CCP->_hoops_AGP = _hoops_RPPHP;

			_hoops_RPPHP->scale = _hoops_HSPHP->scale;
			_hoops_RPPHP->count = _hoops_HSPHP->count;
			_hoops_RPPHP->_hoops_ISPHP =
						 _hoops_HSPHP->_hoops_ISPHP;

			_hoops_GPPHP (dc, matrix, _hoops_IHCR->_hoops_SPH, _hoops_RPPHP, _hoops_HSPHP->_hoops_CGR);
		}
	}
}

local void _hoops_PPPSS (
	_hoops_ARPA alter *			plane,
	_hoops_HRPA const *		matrix) {
	_hoops_RPRA const *		_hoops_CRIPA = matrix->_hoops_APRA->data.elements;
	_hoops_ARPA					input;

	/* "_hoops_IRSIR _hoops_HIHP _hoops_GAR _hoops_GPRRH . _hoops_HAICR" - _hoops_RPRRH & _hoops_APRRH */
	/* _hoops_RH _hoops_IAPGR-_hoops_GGSR _hoops_AIRP _hoops_CHR _hoops_HSSPR _hoops_IS _hoops_SHH _hoops_AHHR _hoops_GGR _hoops_IRS _hoops_IRISR 4x3 */
	_hoops_RSAI (plane, _hoops_ARPA, &input);

	plane->a =	_hoops_CRIPA[0][0] * input.a +
				_hoops_CRIPA[0][1] * input.b +
				_hoops_CRIPA[0][2] * input.c /* +
				_hoops_PPRRH[0][3] * _hoops_CIIA._hoops_GHGP */;

	plane->b =	_hoops_CRIPA[1][0] * input.a +
				_hoops_CRIPA[1][1] * input.b +
				_hoops_CRIPA[1][2] * input.c /* +
				_hoops_PPRRH[1][3] * _hoops_CIIA._hoops_GHGP */;

	plane->c =	_hoops_CRIPA[2][0] * input.a +
				_hoops_CRIPA[2][1] * input.b +
				_hoops_CRIPA[2][2] * input.c /* +
				_hoops_PPRRH[2][3] * _hoops_CIIA._hoops_GHGP */;

	plane->d =	_hoops_CRIPA[3][0] * input.a +
				_hoops_CRIPA[3][1] * input.b +
				_hoops_CRIPA[3][2] * input.c +
				_hoops_CRIPA[3][3] * input.d;

	(void)HI_Normalize_Plane (plane);
}

local void _hoops_HPPSS (
	Net_Rendition alter &			nr,
	_hoops_HRPA const *				matrix) {
	_hoops_SSP			_hoops_IPPSS = nr->transform_rendition->_hoops_RGH;

	if (_hoops_IPPSS == null)
		return;

	if (matrix->_hoops_APRA == null)
		HI_Validate_Matrix_Adjoint (matrix);

	_hoops_HHCR alter &		_hoops_IHCR = nr.Modify()->transform_rendition.Modify();
	_hoops_IHCR->_hoops_RGH = _hoops_SSP::Create(nr->_hoops_SRA);
	_hoops_SSP alter &	_hoops_GGH = _hoops_IHCR->_hoops_RGH;

	_hoops_GGH->_hoops_ISIGA = HD_Copy_Cutting_Plane_Sets (_hoops_IPPSS->_hoops_ISIGA);
	_hoops_GGH->_hoops_PGH = _hoops_IPPSS->_hoops_PGH;
	_hoops_GGH->_hoops_CRH = _hoops_IPPSS->_hoops_CRH;
	_hoops_GGH->_hoops_AHASP = _hoops_IPPSS->_hoops_AHASP;

	_hoops_IAPA const *		_hoops_HRCAR;
	if ((_hoops_HRCAR = _hoops_GGH->_hoops_ISIGA) != null) do {
		_hoops_GPPA alter *	_hoops_IRCAR;

		if ((_hoops_IRCAR = _hoops_PGRCA(_hoops_HRCAR->_hoops_APPA)) != null) do {
			_hoops_PPPSS (&_hoops_IRCAR->_hoops_SHPA, matrix);
		} while ((_hoops_IRCAR = _hoops_IRCAR->next) != null);
	} while ((_hoops_HRCAR = _hoops_HRCAR->next) != null);

	HD_Validate_Cutting_Plane_Sets (_hoops_GGH);

	if (BIT (_hoops_IHCR->flags, _hoops_PRAIP)) {
		HD_Set_DC_Cutting_Planes (nr);
		_hoops_IHCR->flags |= _hoops_HHGGA;
	}
}

GLOBAL_FUNCTION bool HI_Compute_Camera_Min_Max (
	_hoops_HRPA const *		_hoops_HSGA,
	_hoops_HHRA const *			_hoops_ISPCR,
	_hoops_CRCP const *			_hoops_SRCP,
	Bounding const &		_hoops_PHSIH,
	float alter *			minz_out,
	float alter *			_hoops_HHSIH) {

	_hoops_RPRA alter		_hoops_RHRCS[4];

	HI_Matmul_43_by_43 (&_hoops_HSGA->elements[0][0], &_hoops_ISPCR->_hoops_PRPA.elements[0][0],
						(float alter *) _hoops_RHRCS);

	Bounding	bounding;
	if (_hoops_PHSIH != null)
		bounding = _hoops_PHSIH;
	else
		bounding = _hoops_SRCP->bounding;

#if 1
	_hoops_CAIS const & sphere = bounding->sphere;
	float z = _hoops_CPRA (_hoops_RHRCS, sphere.center);
	float _hoops_AHRCS = sphere.radius *
					_hoops_SGIHR(_hoops_RHRCS[2][0]*_hoops_RHRCS[2][0] +
						 _hoops_RHRCS[2][1]*_hoops_RHRCS[2][1] +
						 _hoops_RHRCS[2][2]*_hoops_RHRCS[2][2]);

	float _hoops_RPSC = z - _hoops_AHRCS;
	float _hoops_CGSAA = z + _hoops_AHRCS;
#else

	float	_hoops_RPSC = 1e12f, _hoops_CGSAA = -1e12f;

	_hoops_SASC const &	cuboid = bounding->cuboid;

	Point 	in[8];
	cuboid._hoops_GPSC(&in[0]);

	for (int i = 0; i < 8; i++) {
		float z = _hoops_CPRA (_hoops_RHRCS, in[i]);
		if (z < _hoops_RPSC)
			_hoops_RPSC = z;
		if (z > _hoops_CGSAA)
			_hoops_CGSAA = z;
	}
#endif

	if ((_hoops_CGSAA - _hoops_RPSC) < _hoops_ISPCR->_hoops_SRIR/100.0f)
		return false;

	if (_hoops_ISPCR->projection == _hoops_GHH) {
		_hoops_RPSC += _hoops_ISPCR->_hoops_SRIR;
		_hoops_CGSAA += _hoops_ISPCR->_hoops_SRIR;
	}

	*minz_out = _hoops_RPSC;
	*_hoops_HHSIH = _hoops_CGSAA;

	return true;
}


local _hoops_GSPGR _hoops_CPPSS (
	Net_Rendition const &		nr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path) {
	_hoops_GSPGR						_hoops_RSPGR, _hoops_ASPGR;

	_hoops_RSPGR = HI_What_Time();

	if (BIT (_hoops_SRCP->_hoops_RCGC, T_TEXT)) {
		Net_Rendition				_hoops_CRAI = nr.Copy();
		Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
		_hoops_APARR		 		_hoops_RRCI;
		int							_hoops_SPPSS = dc->_hoops_SHCI();
		Activity					_hoops_IPHIP = dc->_hoops_CPGPR;
		bool						_hoops_GHPSS = BIT(dc->flags, _hoops_CHSI);

		_hoops_APSRR(dc, "regenerate_text_bounds","", 0);

		dc->_hoops_RASIP(_hoops_HIAGH);
		dc->flags &= ~_hoops_CHSI;

		_hoops_CRAI->_hoops_RGPGR &= _hoops_AGPGR(_hoops_AGCP) | _hoops_AGPGR(_hoops_AHIP);

		_hoops_CRAI->_hoops_RSGC.Modify();	// _hoops_RGRR _hoops_GRS _hoops_GRPHA _hoops_PGSI

		_hoops_CRAI->transform_rendition.Modify()->_hoops_APH = _hoops_CPIRP;

		_hoops_RRCI = _hoops_HGCGA (dc, "text bounding", _hoops_CRAI);

		_hoops_RRCI->draw_3d_polyline		= (_hoops_GRCGA)_hoops_SGCHS;
		_hoops_RRCI->draw_dc_polyline		= (_hoops_CHCGA)_hoops_SGCHS;
		_hoops_RRCI->_hoops_RPCGA			= (_hoops_APCGA)_hoops_SGCHS;
		_hoops_RRCI->draw_dc_face			= (_hoops_SACGA)_hoops_SGCHS;

		_hoops_RRCI->_hoops_CSCGA			= (_hoops_SSCGA)_hoops_SGCHS;
		_hoops_RRCI->_hoops_AGCSR			= (_hoops_GGSGA)_hoops_SGCHS;

		_hoops_RRCI->_hoops_CHCI					= HD_Standard_Render;

		dc->Add_Filter (POOL_NEW(dc->memory_pool, _hoops_RPPSS)(_hoops_SRCP));
		dc->_hoops_CPGPR |= _hoops_RSCCA;

		_hoops_AGSGA	_hoops_PGSGA (dc);
		_hoops_AASS (_hoops_CRAI, _hoops_SRCP, path);

		dc->_hoops_CPGPR = _hoops_IPHIP;
		dc->Remove_Filter ();

		_hoops_HGSGA (dc, "text bounding");

		dc->_hoops_RASIP(_hoops_SPPSS);

		if (_hoops_GHPSS)
			dc->flags |= _hoops_CHSI;
		else
			dc->flags &= ~_hoops_CHSI;
	}

	_hoops_ASPGR = HI_What_Time();
	return (_hoops_ASPGR - _hoops_RSPGR + 0.001) / _hoops_HSPGR;
}

/* _hoops_RGR _hoops_API _hoops_CGPAA _hoops_RH _hoops_ARSHA _hoops_GAR _hoops_SGIP _hoops_GAR _hoops_SCH _hoops_PAH _hoops_RIISH _hoops_PHHR _hoops_IS _hoops_HGCR _hoops_RH _hoops_ICRP _hoops_GGSR
 * _hoops_IIGR _hoops_RH _hoops_HHPA _hoops_SSH-_hoops_SRHR _hoops_RAAA.  _hoops_HHIGR _hoops_HRGR _hoops_ICIC _hoops_IS _hoops_GRPHA _hoops_RH _hoops_CPSP _hoops_ARI _hoops_PGGA
 * _hoops_SR _hoops_RGAR _hoops_AASA _hoops_RGR _hoops_API _hoops_RPHR _hoops_RAS _hoops_RHPSS _hoops_IRS _hoops_CCAH _hoops_SARA. */
GLOBAL_FUNCTION void HD_Adjust_WLimit (
	Net_Rendition alter &		nr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path) {
	_hoops_HHRA const *				_hoops_SPH;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	float						_hoops_RPSC = 1e12f, _hoops_CGSAA = -1e12f;
	float						_hoops_CHCR;

	if (BIT(_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR))
		return;

	{
		_hoops_SPAGR					_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, nr->_hoops_SRA->_hoops_RIGC->thread_id);
		_hoops_AHAGR alter *	_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, path);
		_hoops_HRPA *	_hoops_HSGA;

		if ((_hoops_HSGA = _hoops_CSC->_hoops_ARSGP()) != null) {
			_hoops_HSGA->_hoops_APRA.release();
			FREE (_hoops_HSGA, _hoops_HRPA);
		}

		ZALLOC (_hoops_HSGA, _hoops_HRPA);
		HI_Copy_Matrix (&_hoops_IHCR->_hoops_IPH->data, _hoops_HSGA);
		_hoops_CSC->_hoops_RRSGP (_hoops_HSGA);
	}

	_hoops_SPH = _hoops_IHCR->_hoops_SPH;
	if (BIT (nr->current, _hoops_GAHPP))
		return;

	if (!BIT(_hoops_SRCP->_hoops_CPGPR, _hoops_HIPGP) &&
		BIT (nr->_hoops_SRA->_hoops_CPGPR, _hoops_RSCCA)) {
		_hoops_CPPSS (nr, _hoops_SRCP, path);
		_hoops_PGRCA(_hoops_SRCP)->_hoops_CPGPR |= _hoops_HIPGP;
	}

	if (_hoops_SRCP->bounding._hoops_HICAR() || BIT(_hoops_SRCP->bounding->flags, Bounding_TRANSFORM_DEPENDENT))
		return;

	if (!HI_Compute_Camera_Min_Max (&_hoops_IHCR->_hoops_IPH->data, _hoops_IHCR->_hoops_SPH,
										_hoops_SRCP, null, &_hoops_RPSC, &_hoops_CGSAA))
		return;

	if (_hoops_SPH->projection != _hoops_GHH) {
		if (Abs(_hoops_CGSAA) > Abs(_hoops_RPSC))
			_hoops_CHCR = _hoops_IHCR->_hoops_SPH->_hoops_SRIR/Abs(_hoops_CGSAA);
		else
			_hoops_CHCR = _hoops_IHCR->_hoops_SPH->_hoops_SRIR/Abs(_hoops_RPSC);
	}
	else if (_hoops_RPSC > 0)
		_hoops_CHCR = _hoops_RPSC / _hoops_IHCR->_hoops_SPH->_hoops_SRIR;
	else
		return;

	_hoops_CHCR -= 0.01f;

	if (_hoops_CHCR < _hoops_IHCR->_hoops_CHCR)
		return;

	/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GRP _hoops_CPPSR _hoops_ISP, _hoops_AA _hoops_HAR _hoops_ACPC _hoops_ARSHA */
	if (!BIT(nr->transform_rendition->flags, _hoops_GPSHP) && _hoops_CHCR > 0.95f)
		_hoops_CHCR = 0.95f;

	if (_hoops_CHCR != _hoops_IHCR->_hoops_CHCR) {
		_hoops_HHCR alter &		_hoops_AHPSS = nr->transform_rendition;

		_hoops_AHPSS->_hoops_CHCR = _hoops_CHCR;
		_hoops_AHPSS->_hoops_RIPHP = _hoops_CHCR<0.001f?1.0f:1000.0f * _hoops_CHCR;

		_hoops_AHPSS->_hoops_CHIH = HD_Compute_Displacement_Scale(nr, _hoops_AHPSS->_hoops_RASHP);
		_hoops_AHPSS->_hoops_IGAAP = HD_Compute_Displacement_Scale(nr, _hoops_AHPSS->_hoops_CASHP);
		_hoops_AHPSS->_hoops_SHIH = HD_Compute_Displacement_Scale(nr, _hoops_AHPSS->_hoops_SASHP);


		if (!BIT (nr->transform_rendition->flags, _hoops_AIPHP)) {
			/* _hoops_PSP _hoops_SIRRS; _hoops_SAHR _hoops_RH _hoops_SARA _hoops_PPR _hoops_SHPR */
			HD_Redo_Screen (nr, &_hoops_PGRCA(_hoops_IHCR->_hoops_SPH)->_hoops_GRCC);
		}
		else {
			_hoops_HRPA					_hoops_PIPHP;

			HI_Multiply_Matrices (&_hoops_IHCR->_hoops_IPH->data,
								  &_hoops_IHCR->_hoops_SPH->_hoops_GRCC,
								  &_hoops_PIPHP);

			HD_Redo_Screen (nr, &_hoops_PIPHP);
		}
		if (BIT (_hoops_IHCR->flags, _hoops_HHGGA))
			HD_Set_DC_Cutting_Planes (nr);


		_hoops_SPAGR				_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, nr->_hoops_SRA->_hoops_RIGC->thread_id);
		_hoops_AHAGR *		_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, path, false);

		if (_hoops_CSC == null || _hoops_CSC->_hoops_APHGA == null ||
			_hoops_CSC->_hoops_APHGA->transform_rendition->_hoops_CHCR != _hoops_CHCR)
			_hoops_PGRCA (nr->_hoops_SRA)->_hoops_CPGPR |= _hoops_GGARA;
	}
}

// _hoops_PASC _hoops_HASC _hoops_RRGR
local void _hoops_PHPSS (
	Net_Rendition const &		nr,
	_hoops_CRCP const *				_hoops_SRCP) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	_hoops_RPRA const *			matrix = _hoops_IHCR->matrix->data.elements;
	_hoops_SASC const &		cuboid = _hoops_SRCP->bounding->cuboid;

	Point	_hoops_GPPSS[8];
	cuboid._hoops_GPSC(&_hoops_GPPSS[0]);

	Point min, max;
	min.x = min.y = MAX_FLOAT;
	max.x = max.y = -MAX_FLOAT;

	bool	_hoops_RAHIS = false;

	for (int i = 0; i < 8; i++) {
		float w = _hoops_PHCP (matrix, _hoops_GPPSS[i]);
		if (w >= _hoops_IHCR->_hoops_CHCR) {
			float x = _hoops_HPRA (matrix, _hoops_GPPSS[i]) / w;
			float y = _hoops_IPRA (matrix, _hoops_GPPSS[i]) / w;
			if (x < min.x)
				min.x = x;
			if (y < min.y)
				min.y = y;
			if (x > max.x)
				max.x = x;
			if (y > max.y)
				max.y = y;
		}
		else
			_hoops_RAHIS = true;
	}

	if (max.x < min.x)	// _hoops_HCR _hoops_GHIPR _hoops_RH _hoops_RHC?
		return;

	//_hoops_RPP (_hoops_GHIPR)		// _hoops_SAHR _hoops_PHHR _hoops_CCA _hoops_HISI _hoops_SR _hoops_SSAS _hoops_HGCR...?

	if (nr->_hoops_IRR->_hoops_PCHS == _hoops_SHIRP) {
		/* _hoops_HIHP _hoops_RH _hoops_GSSP _hoops_PPSR _hoops_IS _hoops_RH _hoops_CSPH _hoops_PPSR _hoops_AIH _hoops_RH _hoops_GSSP _hoops_IS _hoops_SHPR _hoops_RSGA. */
		Point	center = _hoops_AICIR(cuboid.min, cuboid.max);
		float	w = _hoops_PHCP (matrix, center);

		if (w >= nr->transform_rendition->_hoops_CHCR) {
			DC_Point	_hoops_GIISR;

			_hoops_GIISR.x = _hoops_HPRA (matrix, center) / w;
			_hoops_GIISR.y = _hoops_IPRA (matrix, center) / w;
			_hoops_GIISR.z = _hoops_CPRA (matrix, center) / w;

			if (_hoops_GIISR.x < _hoops_IHCR->_hoops_AGAA.right &&
				_hoops_GIISR.x > _hoops_IHCR->_hoops_AGAA.left &&
				_hoops_GIISR.y < _hoops_IHCR->_hoops_AGAA.top &&
				_hoops_GIISR.y > _hoops_IHCR->_hoops_AGAA.bottom) {

				DC_Polydot_Batch* _hoops_IGIC = dc->_hoops_GASIP;

				if (!_hoops_IGIC)
					POOL_ZALLOC(dc->_hoops_GASIP, DC_Polydot_Batch, dc->memory_pool);
				_hoops_IGIC = dc->_hoops_GASIP;

				if (_hoops_IGIC->allocated == 0) {
					_hoops_IGIC->allocated = 64;
					POOL_ALLOC_ARRAY_CACHED (_hoops_IGIC->pts, _hoops_IGIC->allocated, DC_Point, dc->memory_pool);
					POOL_ALLOC_ARRAY_CACHED (_hoops_IGIC->colors, _hoops_IGIC->allocated, RGBAS32, dc->memory_pool);
				}
				else if (_hoops_IGIC->used == _hoops_IGIC->allocated) {
					DC_Point *_hoops_HHPSS, *_hoops_AIRSC;
					RGBAS32 *_hoops_IHPSS, *_hoops_PGICP;

					_hoops_AIRSC = _hoops_IGIC->pts;
					POOL_ALLOC_ARRAY_CACHED (_hoops_HHPSS, 2*_hoops_IGIC->allocated, DC_Point, dc->memory_pool);
					_hoops_IGIC->pts = _hoops_HHPSS;
					_hoops_AIGA (_hoops_AIRSC, _hoops_IGIC->allocated, DC_Point, _hoops_IGIC->pts);
					FREE_ARRAY (_hoops_AIRSC, _hoops_IGIC->allocated, DC_Point);

					_hoops_PGICP = _hoops_IGIC->colors;
					POOL_ALLOC_ARRAY_CACHED (_hoops_IHPSS, 2*_hoops_IGIC->allocated, RGBAS32, dc->memory_pool);
					_hoops_IGIC->colors = _hoops_IHPSS;
					_hoops_AIGA (_hoops_PGICP, _hoops_IGIC->allocated, RGBAS32, _hoops_IGIC->colors);
					FREE_ARRAY (_hoops_PGICP, _hoops_IGIC->allocated, RGBAS32);

					_hoops_IGIC->allocated = 2*_hoops_IGIC->allocated;
				}

				_hoops_ACHR			_hoops_PRIGP = _hoops_SRCP->_hoops_RCGC & nr->_hoops_RGP & _hoops_IRHGP;
				Driver_Color		source = nr->_hoops_IHA->color;

				if (BIT (_hoops_PRIGP, T_FACES))
					source = nr->_hoops_IHA->color;
				else if (BIT (_hoops_PRIGP, T_EDGES))
					source = nr->_hoops_RHP->color;
				else if (BIT (_hoops_PRIGP, T_LINES))
					source = nr->_hoops_AHP->color;
				else if (BIT (_hoops_PRIGP, T_TEXT))
					source = nr->_hoops_SISI->color;
				else if (BIT (_hoops_PRIGP, T_MARKERS))
					source = nr->_hoops_GSP->color;

				_hoops_AAASP(dc, source, dc->_hoops_PGCC._hoops_PIHSR, _hoops_IGIC->colors[_hoops_IGIC->used]);
				_hoops_IGIC->pts[_hoops_IGIC->used] = _hoops_GIISR;
				_hoops_IGIC->used++;
			}
		}
	}
	else if (nr->_hoops_IRR->_hoops_PCHS == _hoops_GIIRP) {
		/* _hoops_PGSA _hoops_IRS 3d _hoops_IASC */
		Tristrip *		tristrip;
		Point *			_hoops_CHPSS;
		int 			_hoops_IAIGA[] = {0, 1, 2, 3,
											10, 11, 6, 7,
											14, 15, 4, 5,
											18, 22, 8, 12,
											16, 20, 9, 13,
											17, 21, 19, 23 };
		int 			_hoops_IHGGC[] = { 4, 4, 4, 4,  4, 4 };
		Vector *		normals;

		POOL_ZALLOC (tristrip, Tristrip, dc->memory_pool);
		_hoops_ICAI (tristrip);

		POOL_ALLOC_ARRAY_ALIGNED_CACHED (_hoops_CHPSS, 24, Point, 16, dc->memory_pool);

		_hoops_AIGA(_hoops_GPPSS, 8, Point, _hoops_CHPSS);
		_hoops_AIGA(_hoops_GPPSS, 8, Point, &_hoops_CHPSS[8]);
		_hoops_AIGA(_hoops_GPPSS, 8, Point, &_hoops_CHPSS[16]);

		tristrip->_hoops_SRHA = _hoops_SRHH;

		tristrip->points = _hoops_CHPSS;
		tristrip->point_count = 24;
		tristrip->_hoops_RAHH |= _hoops_AIPI;

		POOL_ALLOC_ARRAY_CACHED (normals, 24, Vector, dc->memory_pool);

		normals[0].x = -1.0f; normals[0].y = 0.0f; normals[0].z = 0.0f;
		normals[1].x = -1.0f; normals[1].y = 0.0f; normals[1].z = 0.0f;
		normals[2].x = -1.0f; normals[2].y = 0.0f; normals[2].z = 0.0f;
		normals[3].x = -1.0f; normals[3].y = 0.0f; normals[3].z = 0.0f;
		normals[10].x = 0.0f; normals[10].y = 1.0f; normals[10].z = 0.0f;
		normals[11].x = 0.0f; normals[11].y = 1.0f; normals[11].z = 0.0f;
		normals[6].x = 0.0f; normals[6].y = 1.0f; normals[6].z = 0.0f;
		normals[7].x = 0.0f; normals[7].y = 1.0f; normals[7].z = 0.0f;
		normals[14].x = 1.0f; normals[14].y = 0.0f; normals[14].z = 0.0f;
		normals[15].x = 1.0f; normals[15].y = 0.0f; normals[15].z = 0.0f;
		normals[4].x = 1.0f; normals[4].y = 0.0f; normals[4].z = 0.0f;
		normals[5].x = 1.0f; normals[5].y = 0.0f; normals[5].z = 0.0f;
		normals[18].x = 0.0f; normals[18].y = 0.0f; normals[18].z = -1.0f;
		normals[22].x = 0.0f; normals[22].y = 0.0f; normals[22].z = -1.0f;
		normals[8].x = 0.0f; normals[8].y = 0.0f; normals[8].z = -1.0f;
		normals[12].x = 0.0f; normals[12].y = 0.0f; normals[12].z = -1.0f;
		normals[16].x = 0.0f; normals[16].y = -1.0f; normals[16].z = 0.0f;
		normals[20].x = 0.0f; normals[20].y = -1.0f; normals[20].z = 0.0f;
		normals[9].x = 0.0f; normals[9].y = -1.0f; normals[9].z = 0.0f;
		normals[13].x = 0.0f; normals[13].y = -1.0f; normals[13].z = 0.0f;
		normals[17].x = 0.0f; normals[17].y = 0.0f; normals[17].z = 1.0f;
		normals[21].x = 0.0f; normals[21].y = 0.0f; normals[21].z = 1.0f;
		normals[19].x = 0.0f; normals[19].y = 0.0f; normals[19].z = 1.0f;
		normals[23].x = 0.0f; normals[23].y = 0.0f; normals[23].z = 1.0f;

		tristrip->_hoops_ICHA = normals;
		tristrip->_hoops_RAHH |= _hoops_ICGHR;

		tristrip->_hoops_PHHA = 6;
		POOL_ALLOC_ARRAY(tristrip->lengths, 6, int, dc->memory_pool);
		_hoops_AIGA(_hoops_IHGGC, 6, int, tristrip->lengths);
		tristrip->lengths_allocated = 6;

		POOL_ALLOC_ARRAY(tristrip->_hoops_AIHA, 24, int, dc->memory_pool);
		_hoops_AIGA(_hoops_IAIGA, 24, int, tristrip->_hoops_AIHA);
		tristrip->_hoops_IPII = 24;
		tristrip->_hoops_RAHH |= _hoops_AAHH;

		tristrip->total = 24;

		if (ANYBIT(nr->current, _hoops_CISHP|_hoops_RSSHP))
			HD_Handle_FBI_Pending_Window (nr);

		_hoops_HPHCP (nr, tristrip);

		if (_hoops_ISAI(tristrip) == 0)
			HI_Free_Tristrip (tristrip);
	}
}


GLOBAL_FUNCTION Action_Mask HD_Type_To_Action_Mask (int type)
{
	switch (type) {
		case _hoops_CHIP:			return _hoops_SHIP;
		case _hoops_GIIP:
		case _hoops_RIIP:			return _hoops_AIIP;
		case _hoops_PIIP:
		case _hoops_HIIP:
		case _hoops_IIIP:				return _hoops_CIIP;
		case _hoops_SIIP:			return _hoops_GCIP;
		case _hoops_RCIP:				return _hoops_ACIP;
		case _hoops_PCIP:					return _hoops_HCIP;
		case _hoops_PIRS:			return _hoops_HCIP;
		case _hoops_ICIP:					return _hoops_CCIP;
		case _hoops_SCIP:
		case _hoops_GSIP:					return _hoops_RSIP;
		case _hoops_ASIP:				return _hoops_PSIP;
		case _hoops_HSIP:					return _hoops_ISIP;
		case _hoops_CSIP:			return _hoops_SSIP;
		case _hoops_GGCP:					return _hoops_RGCP;
		case HK_STRING_CURSOR:
		case _hoops_AGCP:					return _hoops_PGCP;
		case _hoops_HGCP:					return _hoops_IGCP;
		case _hoops_CGCP:
		case _hoops_SGCP:
		case _hoops_GRCP:
		case _hoops_RRCP:			return _hoops_ARCP;
		case _hoops_PRCP:			return _hoops_HRCP;
		case _hoops_HGPGR:			return 0;
		case _hoops_HCIIR:			return _hoops_RAPI;  //_hoops_SR _hoops_HS _hoops_PSP _hoops_GRIGI _hoops_HPGR _hoops_RGR _hoops_PPSR _hoops_PCPA _hoops_RH _hoops_AIRI _hoops_HIGR _hoops_SIAS _hoops_SCIR
		case _hoops_CRCIP:		return _hoops_PGRI;
		case _hoops_HACIP:		return _hoops_IGAI;
		case _hoops_CACIP:	return _hoops_RGPI;
		default:
			HE_ERROR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					"unrecognized type in HD_Type_To_Action_Mask");
			return _hoops_RAPI;
	}
}


GLOBAL_FUNCTION Action_Mask HD_Geometry_To_Action_Mask (
	Geometry const *				g) {

	if (g == null)
		return 0;

#	define _hoops_SHPSS(x)		(int)((x)+_hoops_AHRIR)

	if (g->type == _hoops_AHIP) {
		_hoops_PHIP const *	_hoops_RRA = (_hoops_PHIP const *)g;
		Action_Mask					mask = 0;
		Geometry const *			geo;
		Type						_hoops_GIPSS = -1;

		if (_hoops_RRA->_hoops_RGPGR != ~0) {
			int 					_hoops_RGPGR = _hoops_RRA->_hoops_RGPGR;
			int 					index = 0;

			while (_hoops_RGPGR != 0) {
				if (BIT((1<<index), _hoops_RGPGR)) {
					mask |= HD_Type_To_Action_Mask (_hoops_SHPSS(index));
					_hoops_RGPGR &= ~(1<<index);
				}
				index++;
			}
		}
		else {
			if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP) {
				_hoops_CRCP const *		_hoops_SRCP = (_hoops_CRCP const *)_hoops_RRA->_hoops_IHIP[0];

				if ((geo = _hoops_SRCP->geometry) != null) {
					while (1) {
						if (BIT(_hoops_RRA->_hoops_RGPGR, _hoops_AGPGR(geo->type)) && geo->type != _hoops_GIPSS) {
							if (geo->type != _hoops_AHIP)
								_hoops_GIPSS = geo->type;
							mask |= HD_Geometry_To_Action_Mask (geo);
							geo = geo->next;
						}
						else
							_hoops_PGPGR (geo, geo->type);

						if (!geo)
							break;
					}
				}
			}
			else {
				for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++) {
					geo = (Geometry const *)_hoops_RRA->_hoops_IHIP[i];

					if (BIT(_hoops_RRA->_hoops_RGPGR, _hoops_AGPGR(geo->type)) && geo->type != _hoops_GIPSS) {
						if (geo->type != _hoops_AHIP)
							_hoops_GIPSS = geo->type;
						mask |= HD_Geometry_To_Action_Mask (geo);
					}
				}
			}
		}

		return mask;
	}
	else
		return HD_Type_To_Action_Mask (g->type);
}

local void _hoops_RIPSS (
	Net_Rendition const &		nr,
	_hoops_AHAGR *				_hoops_CSC,
	_hoops_PGCIP alter *			list) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	_hoops_APARR alter &		_hoops_RRCI = dc->_hoops_IPCI;
	Action_Mask					_hoops_HPCI = _hoops_RRCI->mask;
	_hoops_PGCIP alter *			ptr;
	_hoops_GACR alter			*_hoops_AIPSS = null, *_hoops_CHGI;
	bool						_hoops_RACR;
	Action_Mask					_hoops_PIPSS = 0;
	bool						_hoops_HIPSS = false;
	Action_Mask					action_mask = 0, _hoops_IIPSS = 0;

	_hoops_GPAGR			_hoops_RPAGR = _hoops_CSC->_hoops_PHAGR();
	if (_hoops_RPAGR == null) {
		_hoops_RPAGR = _hoops_GPAGR::Create(dc->memory_pool);
		_hoops_CSC->_hoops_HHAGR (_hoops_RPAGR);
	}

	/* _hoops_RPP _hoops_SR _hoops_HRCI _hoops_PAR _hoops_PA _hoops_GGGAH _hoops_ISSC _hoops_CRGR _hoops_RH _hoops_HGSI _hoops_PISI _hoops_HIGR,
	 * _hoops_SR _hoops_RRP _hoops_IS _hoops_HPGGR _hoops_RH _hoops_HGSI _hoops_AIRI _hoops_HIGR _hoops_GAR _hoops_PRAR */
	_hoops_RACR = HI_Get_Display_List (dc->_hoops_GHRI, &_hoops_RPAGR->_hoops_GAHA, &_hoops_CHGI);
	ASSERT (!_hoops_RACR);
	if (BIT (nr->flags, _hoops_PSPSP)) {
		/* _hoops_CIPSS _hoops_HCGI-_hoops_SHSS _hoops_CPAP. _hoops_CPS _hoops_SHS _hoops_IAGA _hoops_ISSC _hoops_GPP _hoops_RH
		 * _hoops_HGSI _hoops_HCH _hoops_ICH _hoops_HIGR.  _hoops_GCIAR _hoops_HSGRA _hoops_GRGA _hoops_GAR _hoops_IRS
		 * _hoops_AGIR _hoops_ARI _hoops_HRGR _hoops_ARII _hoops_HCGI-_hoops_SHSS, _hoops_PHRI _hoops_GRRC _hoops_PPR _hoops_RRRC
		 * _hoops_HSSC _hoops_RHIR _hoops_RPP _hoops_RAR-_hoops_AAR */
		if ((ptr = list) != null) {
			_hoops_PGCIP **		_hoops_ASRGR = &list;

			do {
				switch (ptr->type) {
					case _hoops_PIIP:
					case _hoops_HIIP:
					case _hoops_IIIP:
						_hoops_HIPSS = true;
						_hoops_HHHI;
					case _hoops_CRCIP:
					case _hoops_HACIP:
					case _hoops_RCIP:
					//_hoops_AGIR _hoops_SIPSS:
					//_hoops_AGIR _hoops_HPIHC:
					case _hoops_HCIIR: {
						_hoops_ASRGR = &ptr->next;
					} break;
					case _hoops_CHIP:
					case _hoops_GIIP:
					case _hoops_RIIP: {
						if (!nr->_hoops_ARA->_hoops_APPI._hoops_SAR) {
							_hoops_ASRGR = &ptr->next;
							_hoops_HIPSS = true;
							break;
						}
					} _hoops_HHHI;
					default : {
						_hoops_CHGI->action_mask |= HD_Type_To_Action_Mask (ptr->type);
						*_hoops_ASRGR = ptr->next;
						ptr->next = dc->_hoops_GPSS[dc->_hoops_IASS];
						dc->_hoops_GPSS[dc->_hoops_IASS] = ptr;
					} break;
				}
			} while ((ptr = *_hoops_ASRGR) != null);

			if (_hoops_HIPSS) {
				_hoops_PGCIP *head;
				head = null;
				while ((ptr = list) != null) {
					list = ptr->next;
					ptr->next = head;
					head = ptr;
				}
				list = head;
			}
		}
		dc->flags |= _hoops_IIGC;
		dc->_hoops_SHAGH = 0;
		dc->_hoops_GSGC = 0;
		dc->_hoops_SCGC = 0;
		_hoops_GPCGH (nr, &_hoops_RPAGR->_hoops_HHICA, &action_mask, true);
		_hoops_RACR = HI_Get_Display_List (dc->_hoops_GHRI, &_hoops_RPAGR->_hoops_HHICA, &_hoops_AIPSS);
		ASSERT (!_hoops_RACR);
		_hoops_AIPSS->_hoops_GASI = _hoops_CHGI;
		_hoops_CHGI->_hoops_GASI = _hoops_AIPSS;
		if (list) {
			if (action_mask) {
				int _hoops_GCPSS = 0;
				while (dc->_hoops_IPCI != dc->_hoops_ACPGR) {
					_hoops_IGRS (dc);
					_hoops_GCPSS++;
				}
				/* _hoops_SGH _hoops_RH _hoops_RCPSS _hoops_GGSR _hoops_IIGR _hoops_CPSP _hoops_SAHR _hoops_IS _hoops_SRCH _hoops_HAGC _hoops_CCAH _hoops_HGIIP.  _hoops_ISAP
				   _hoops_CGH _hoops_IGRC _hoops_HGCR _hoops_CHCC _hoops_ARI, _hoops_SAHR _hoops_HPISR */
				_hoops_IIPSS = _hoops_RRCI->mask;
				action_mask |= ~_hoops_RSCI;
				_hoops_RRCI->mask = action_mask;
				HD_Draw_Deferred_3D_Geometry (list, BIT(nr->transform_rendition->flags, _hoops_ISH));
				_hoops_RRCI->mask = _hoops_IIPSS;
				while (_hoops_GCPSS--)
					_hoops_SGRS (dc);
			}
		}
		_hoops_PPCGH (nr, &_hoops_RPAGR->_hoops_HHICA, true);
		dc->flags &= ~_hoops_IIGC;
		_hoops_CHGI->action_mask |= _hoops_AIPSS->action_mask;
	}
	else if ((ptr = list) != null) {
		/* !_hoops_IGGC _hoops_AGSR _hoops_SGS _hoops_SR _hoops_GGHP _hoops_ARI _hoops_HPP _hoops_ACPSS, _hoops_IAS._hoops_ISHI. _hoops_HPP _hoops_IHSP _hoops_ARP _hoops_GPP _hoops_CPAP */
		do {
			switch (ptr->type) {
				case _hoops_HCIIR: {
					_hoops_PIPSS |= ((_hoops_GACR *)ptr->item)->action_mask;
				} break;
				default : {
					_hoops_PIPSS |= HD_Type_To_Action_Mask (ptr->type);
				} break;
			}
		} while ((ptr = ptr->next) != null);
	}

	if (_hoops_AIPSS) {
		_hoops_PIPSS = _hoops_AIPSS->action_mask;
		_hoops_PIPSS &= ~_hoops_SHSI;
		if (!BIT (nr->_hoops_RGP, T_FACES))
			_hoops_PIPSS &= ~_hoops_PGRI;
		if (!ANYBIT (nr->_hoops_RGP, _hoops_PSRI))
			_hoops_PIPSS &= ~_hoops_IGAI;
		if (!BIT (nr->_hoops_RGP, T_LINES))
			_hoops_PIPSS &= ~_hoops_IRPI;
	}

	if (!BIT (nr->flags, _hoops_PSPSP) || _hoops_PIPSS) {
		/* _hoops_PCPSS _hoops_IIGR _hoops_RSH _hoops_IS _hoops_HGCR _hoops_ARI:
			1) _hoops_RRH _hoops_GHCPR _hoops_SAHP
			2) _hoops_RRH _hoops_RSSI _hoops_CCA _hoops_ACHGC _hoops_HH _hoops_GRPAR _hoops_GPP _hoops_IRS _hoops_RPIHR _hoops_API _hoops_RHPP
			3) _hoops_IHSP _hoops_CHIA _hoops_HPGR _hoops_CPAP _hoops_PAPA
			4) _hoops_RSSP == _hoops_PIRC _hoops_GPP _hoops_RRH _hoops_CPAP _hoops_GPP _hoops_RPIHR _hoops_API _hoops_RHPP
			5) _hoops_RRH _hoops_RAR-_hoops_AAR _hoops_RRRC _hoops_PAR _hoops_GRRC
		*/
		if ((ptr = list) != null) {
			_hoops_PGCIP **		_hoops_ASRGR = &list;
			do {
				if (ptr->type == _hoops_HCIIR) {
					_hoops_PIPSS |= ((_hoops_GACR *)ptr->item)->action_mask;
					_hoops_ASRGR = &ptr->next;
				}
				else if (ANYBIT (_hoops_PIPSS, HD_Type_To_Action_Mask (ptr->type))) {
					*_hoops_ASRGR = ptr->next;
					ptr->next = dc->_hoops_GPSS[dc->_hoops_IASS];
					dc->_hoops_GPSS[dc->_hoops_IASS] = ptr;
				}
				else {
					_hoops_ASRGR = &ptr->next;
				}
			} while ((ptr = *_hoops_ASRGR) != null);
		}
		if (!BIT(dc->flags, _hoops_GPHHP)) {
			_hoops_CHGI->action_mask |= _hoops_PIPSS;
			if (!_hoops_AIPSS) {
				dc->flags |= _hoops_IIGC;
				dc->_hoops_SHAGH = 0;
				dc->_hoops_GSGC = 0;
				dc->_hoops_SCGC = 0;
				_hoops_GPCGH (nr, &_hoops_RPAGR->_hoops_HHICA, &action_mask, true);
				_hoops_RACR = HI_Get_Display_List (dc->_hoops_GHRI, &_hoops_RPAGR->_hoops_HHICA, &_hoops_AIPSS);
				ASSERT (!_hoops_RACR);
				_hoops_AIPSS->_hoops_GASI = _hoops_CHGI;
				_hoops_CHGI->_hoops_GASI = _hoops_AIPSS;
				_hoops_PPCGH (nr, &_hoops_RPAGR->_hoops_HHICA, true);
				dc->flags &= ~_hoops_IIGC;
				_hoops_CHGI->action_mask |= _hoops_AIPSS->action_mask;
				_hoops_AIPSS->action_mask |= _hoops_PIPSS;
				_hoops_AIPSS = null;
			}
		}
	}

	if (_hoops_AIPSS) {
		_hoops_PGCIP alter *_hoops_AIASS;
		POOL_ZALLOC (_hoops_AIASS, _hoops_PGCIP, dc->memory_pool);
		_hoops_AIASS->next = dc->_hoops_GPSS[dc->_hoops_IASS];
		dc->_hoops_GPSS[dc->_hoops_IASS] = _hoops_AIASS;
		_hoops_AIASS->type = _hoops_HCIIR;
		_hoops_AIASS->item = _hoops_AIPSS;
		_hoops_PRRH (_hoops_AIPSS);
		_hoops_AIASS->segment = dc->_hoops_RRCIP;
		_hoops_AIASS->path = dc->path;
		_hoops_AIASS->nr = nr;
		/* '_hoops_SPCGP' _hoops_HA _hoops_ICGI _hoops_CPS _hoops_SGS _hoops_CSAP _hoops_GGR '_hoops_HIGR' */
		if (list)
			HD_Free_Deferred_3D_Geometry (list);
	}
	_hoops_RRCI->mask = _hoops_HPCI;
	UNREFERENCED (_hoops_RACR); /* _hoops_GRHP _hoops_RH _hoops_HICA _hoops_RSPPP */
}



enum _hoops_HCPSS {
	_hoops_ICPSS,
	_hoops_CCPSS
};

struct _hoops_SCPSS : public _hoops_HIGGH {
	private:
		int		stage;

	public:
		_hoops_SCPSS (int s = _hoops_ICPSS) : stage (s) {}
		bool _hoops_PPCRR (Net_Rendition alter & nr, _hoops_CRCP const * _hoops_SRCP, _hoops_HICS const & path);
};

bool _hoops_SCPSS::_hoops_PPCRR (
	Net_Rendition alter &		nr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path) alter {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	UNREFERENCED(path);

	switch (stage) {
		case _hoops_ICPSS: {
			stage = _hoops_CCPSS;
		}	break;

		case _hoops_CCPSS: {
			if (_hoops_SRCP != dc->_hoops_AAHSR &&
				(BIT (nr->_hoops_RCSHR, _hoops_CRHPP) ||
				 BIT (_hoops_SRCP->_hoops_PHSI, _hoops_HCHGP)))
				return false;
		}
	}
	return true;
}


local void  _hoops_GSPSS (
	Net_Rendition const &		nr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	_hoops_ARPA const *				plane;

	if (ANYBIT (nr->transform_rendition->_hoops_APH, Heur_Culling_EXTENT|_hoops_RIHS) &&
		nr->_hoops_IRR->_hoops_PCHS != _hoops_CHIRP)
		return;

	if (!BIT (nr->transform_rendition->flags, _hoops_IGCC))
		HD_Validate_World_To_Screen (nr);
	_hoops_RPRA const *			_hoops_APRA = nr->transform_rendition->_hoops_CGCC->_hoops_PPRA()->data.elements;

	plane = &nr->_hoops_CPP->_hoops_RHGGR.plane;

	if (_hoops_APRA[2][0] * plane->a +
		_hoops_APRA[2][1] * plane->b +
		_hoops_APRA[2][2] * plane->c +
		_hoops_APRA[2][3] * plane->d < 0.0f) {
		Net_Rendition					_hoops_ASSIS = nr.Copy();
		_hoops_ISGI				_hoops_RSPSS;
		_hoops_HHCR				_hoops_ASPSS;
		_hoops_CGRA				_hoops_PSPSS;
		_hoops_GCIR 		_hoops_HSPSS;
		_hoops_CIGA					_hoops_ISPSS;
		_hoops_HHA				mat;
		_hoops_HRPA						temp;
		_hoops_RPRA alter *				m = _hoops_RSPSS.matrix.elements;
		float							_hoops_IRIR;
		unsigned char					alpha;
		/*_hoops_SPRS		_hoops_AIIC								_hoops_CSPSS;*/

		HI_Ident_Matrix (&_hoops_RSPSS.matrix);
		m[0][0] = 1.0f - 2.0f * plane->a * plane->a;
		m[1][1] = 1.0f - 2.0f * plane->b * plane->b;
		m[2][2] = 1.0f - 2.0f * plane->c * plane->c;
		m[0][1] = m[1][0] = -2.0f * plane->a * plane->b;
		m[0][2] = m[2][0] = -2.0f * plane->a * plane->c;
		m[1][2] = m[2][1] = -2.0f * plane->b * plane->c;

		m[3][0] = -2.0f * plane->a * plane->d;
		m[3][1] = -2.0f * plane->b * plane->d;
		m[3][2] = -2.0f * plane->c * plane->d;

		_hoops_RSPSS.matrix._hoops_RAGR = _hoops_GRICR | _hoops_CHCP;
		if (plane->d != 0.0f)
			_hoops_RSPSS.matrix._hoops_RAGR |= _hoops_PRICR;
		if (plane->c != 0.0f)
			_hoops_RSPSS.matrix._hoops_RAGR |= _hoops_RRICR;


		HD_Downwind_Modelling_Matrix (_hoops_ASSIS, (Attribute const *)&_hoops_RSPSS);	/* _hoops_CGPAA _hoops_CPSP */
		_hoops_ASPSS = _hoops_ASSIS->transform_rendition;

		HD_Undo_Screen (_hoops_ASSIS, &temp);
		_hoops_ASPSS->_hoops_GSCH[0] = _hoops_ASPSS->_hoops_GSCH[0] + 0.95f*(_hoops_ASPSS->_hoops_GSCH[1]-_hoops_ASPSS->_hoops_GSCH[0]);
		HD_Redo_Screen (_hoops_ASSIS, &temp);

		/* _hoops_GII _hoops_SS _hoops_RRP _hoops_IS _hoops_SHH _hoops_AHAPI _hoops_HAH */
		_hoops_APPSS (_hoops_ASSIS, &_hoops_RSPSS.matrix);
		/* _hoops_PSHR _hoops_IH _hoops_HPPA _hoops_GHC */
		_hoops_HPPSS (_hoops_ASSIS, &_hoops_RSPSS.matrix);

		HD_Fixup_Attributes (_hoops_ASSIS, null, _hoops_HARIP);


		/* _hoops_SGAA _hoops_IS _hoops_CSCS _hoops_PPRGR */
		_hoops_IRIR = nr->_hoops_CPP->_hoops_RHGGR._hoops_IRIR;
		if (nr->_hoops_CPP->_hoops_RHGGR._hoops_IHSHP) {
			Vector				test;

			if (!BIT (nr->transform_rendition->flags, _hoops_HCPHP))
				HD_Validate_Object_To_Proj (nr);

			_hoops_RPRA const * _hoops_CRIPA = nr->transform_rendition->object_to_projection_matrix->_hoops_PPRA()->data.elements;
			/* _hoops_SAHR _hoops_RH _hoops_AAGA _hoops_PRGGR _hoops_IIGR _hoops_IRS _hoops_IPPA _hoops_HIHP */
			test.x = plane->a*_hoops_CRIPA[0][0] + plane->b*_hoops_CRIPA[0][1] + plane->c*_hoops_CRIPA[0][2] + plane->d*_hoops_CRIPA[0][3];
			test.y = plane->a*_hoops_CRIPA[1][0] + plane->b*_hoops_CRIPA[1][1] + plane->c*_hoops_CRIPA[1][2] + plane->d*_hoops_CRIPA[1][3];
			test.z = plane->a*_hoops_CRIPA[2][0] + plane->b*_hoops_CRIPA[2][1] + plane->c*_hoops_CRIPA[2][2] + plane->d*_hoops_CRIPA[2][3];
			HI_Normalize (&test);

			/* _hoops_SSPSS _hoops_IS _hoops_IPPA _hoops_CCPA _hoops_PPRGR */
			_hoops_IRIR *= _hoops_SGIHR(Abs(test.z));
		}

		dc->flags |= _hoops_CHSHP;

		dc->Add_Filter (POOL_NEW(dc->memory_pool, _hoops_SCPSS)());
		/* _hoops_ASHGR _hoops_IS _hoops_RHPP _hoops_RPP _hoops_SSRR */
		if (dc->_hoops_IPCI->_hoops_GHGGR &&
			!BIT(nr->current, _hoops_RSSHP)) {
			/* _hoops_SCHGR _hoops_IRHS _hoops_IS _hoops_ACPA _hoops_RSH _hoops_AHSC _hoops_RH _hoops_AGSAR _hoops_CHR*/

			if (!_hoops_SRCP->bounding._hoops_HICAR())
				(dc->_hoops_IPCI->_hoops_GHGGR) (_hoops_ASSIS, _hoops_SRCP, path, _hoops_IRIR, _hoops_SRCP->bounding->sphere.radius);
		}
		else {
			int				count = 0;

			HD_Alternate_Hidden_Root (dc, _hoops_PSGGR);

			/* _hoops_GISP _hoops_RH _hoops_CHIR */
			_hoops_AASS (_hoops_ASSIS, _hoops_SRCP, path);

			/* _hoops_HPPP _hoops_GII _hoops_PISI (_hoops_IAS._hoops_ISHI. _hoops_RRH) _hoops_CPAP _hoops_CRGR _hoops_RH _hoops_CHIR */
			while (ANYBIT (dc->_hoops_IPCI->mode, _hoops_HSGGR|_hoops_ISGGR) ||
				   BIT (dc->_hoops_IPCI->mode, _hoops_CSGGR) &&
				   !ANYBIT (dc->_hoops_IPCI->mode, _hoops_RSSHP|_hoops_CISHP)) {
				_hoops_IGRS (dc);
				++count;
			}

			if (dc->_hoops_HASS[dc->_hoops_IASS] != null)
				HD_See_Whats_Hidden (nr);
			if (dc->_hoops_GPSS[dc->_hoops_IASS] != null)
				_hoops_SSGGR (dc);
			if (dc->_hoops_RPSS[dc->_hoops_IASS] != null) {
				HD_Draw_Deferred_3D_Geometry (dc->_hoops_RPSS[dc->_hoops_IASS], true);
				HD_Free_Deferred_3D_Geometry (dc->_hoops_RPSS[dc->_hoops_IASS]);
				dc->_hoops_RPSS[dc->_hoops_IASS] = null;
			}

			while (count-- > 0)
				_hoops_SGRS (dc);

			/* _hoops_PHIH _hoops_GGRGR-_hoops_APRS _hoops_PISI _hoops_CPAP _hoops_CRGR _hoops_RGCI _hoops_RHGS _hoops_GISR */
			HD_Alternate_Hidden_Root (dc, _hoops_PSGGR);
		}

		/* _hoops_PGPR _hoops_SRGS _hoops_RH _hoops_IPPA _hoops_ACAS _hoops_RPP _hoops_RH _hoops_RHPP _hoops_GPGH'_hoops_RA _hoops_PRCA _hoops_CGSI */
		if (!dc->_hoops_IPCI->_hoops_GHGGR) {
			alpha = (unsigned char)(_hoops_GPGCR * (1.0f - _hoops_IRIR));

			_hoops_ASSIS = nr.Copy();
			_hoops_ASPSS = _hoops_ASSIS->transform_rendition.Modify();
			_hoops_ISPSS = _hoops_ASSIS->_hoops_IHA.Modify();
			_hoops_PSPSS = _hoops_ASSIS->_hoops_SAIR.Modify();
			_hoops_HSPSS = _hoops_ASSIS->_hoops_CPP.Modify();
			HD_Undo_Screen (_hoops_ASSIS, &temp);
			_hoops_ASPSS->_hoops_GSCH[1] = _hoops_ASPSS->_hoops_GSCH[0] + 0.95f*(_hoops_ASPSS->_hoops_GSCH[1]-_hoops_ASPSS->_hoops_GSCH[0]);
			HD_Redo_Screen (_hoops_ASSIS, &temp);
			_hoops_ASPSS->flags |= _hoops_ISH;
			_hoops_PSPSS->_hoops_GPIR._hoops_HRIR.a = alpha;
			_hoops_PSPSS->contrast_color._hoops_HRIR.a = alpha;

#ifdef _hoops_GCGGC
			// _hoops_HPSP _hoops_IS _hoops_ASSS _hoops_IHHH _hoops_IS _hoops_CHASA _hoops_PCCP _hoops_IHH _hoops_SRGS _hoops_IIGR _hoops_RH _hoops_IGHP.
			// _hoops_IPCP '_hoops_RPP' _hoops_AACCC _hoops_HRGR _hoops_IS _hoops_ASSS _hoops_IHHH _hoops_IS _hoops_HSGR _hoops_RH _hoops_SPS '_hoops_RPP' _hoops_AACCC _hoops_CGPR _hoops_SIGR.
			if (_hoops_PSPSS->_hoops_GPIR._hoops_HRIR.r == 0x00 &&
				_hoops_PSPSS->_hoops_GPIR._hoops_HRIR.g == 0x00 &&
				_hoops_PSPSS->_hoops_GPIR._hoops_HRIR.b == 0x01)
				_hoops_PSPSS->_hoops_CGAIP = FP_WINDOW_TRANSPARENT;
			else
#endif

			if (_hoops_PSPSS->_hoops_CGAIP == FP_SOLID) {
				/* _hoops_HHSA _hoops_GRH _hoops_PRCA _hoops_GGR _hoops_GGHSS _hoops_CRAA */
				_hoops_PSPSS->_hoops_CGAIP = FP_WINDOW_GRADIENT_S;
				_hoops_PSPSS->contrast_color = _hoops_PSPSS->_hoops_GPIR;
			}
			_hoops_PSPSS->contrast_color._hoops_HRIR.a ^= 0x01;	/* _hoops_IRHH _hoops_SCH _hoops_RPPR _hoops_HAGH */
			mat = _hoops_ISPSS->_hoops_CHA;
			mat->_hoops_IRIR = 1.0f - _hoops_IRIR;
			_hoops_ASSIS->_hoops_RCSHR |= _hoops_AHIHP;
			_hoops_ASSIS->current |= _hoops_AHIHP;
			_hoops_HSPSS->_hoops_PRH._hoops_HRH = true;
			_hoops_HSPSS->_hoops_PRH.style = Transparency_STYLE_BLENDING;

			/* _hoops_HGIHR _hoops_HIPIP _hoops_PPSCP _hoops_RRGR _hoops_RPP _hoops_SIGR */
				_hoops_APARR alter &		_hoops_RRCI = dc->_hoops_IPCI;

				if (_hoops_RRCI->draw_dc_gouraud_polytriangle == HD_Buffer_DC_Polytris_C24_Z16_G)
					_hoops_RRCI->draw_dc_gouraud_polytriangle = HD_Span_DC_Gouraud_Polytris;
				if (_hoops_RRCI->draw_dc_rgb32_rasters == HD_Buffer_DC_Raster_C24_Z16)
					_hoops_RRCI->draw_dc_rgb32_rasters = HD_Buffer_DC_Raster_C32_Z16;

			HD_Draw_Window(_hoops_ASSIS, &_hoops_PSPSS->_hoops_PHRA);
		}
		dc->Remove_Filter ();
	}

	dc->flags &= ~_hoops_CHSHP;
}


local void _hoops_RGHSS (
	Net_Rendition const &			nr,
	_hoops_GACR *					dl,
	_hoops_CRCP const *					_hoops_SRCP,
	_hoops_HICS const &			path) {
	Display_Context alter *			dc = _hoops_PGRCA(nr->_hoops_SRA);
	Net_Rendition					_hoops_CRAI = nr.Copy();
	_hoops_GRGH alter &			_hoops_APIHP = _hoops_CRAI->_hoops_IRR.Modify();
	_hoops_CGRA alter &		_hoops_GCRCS = _hoops_CRAI->_hoops_SAIR.Modify();
	_hoops_HHCR alter &		_hoops_GGCC = _hoops_CRAI->transform_rendition.Modify();

	_hoops_GGCC->flags |= _hoops_CHHS;
	_hoops_APIHP->_hoops_GRGC = -_hoops_APIHP->_hoops_GRGC;
	_hoops_GCRCS->_hoops_ASIHP |= _hoops_ACARP;
	HD_Defer_Tree_Batch (_hoops_CRAI, _hoops_SRCP, path, dc->_hoops_SSGC, (Geometry *)dl);
	dc->_hoops_SSGC = -1;
}



_hoops_GGCGP::_hoops_GGCGP (Memory_Pool *p)
: _hoops_RGCGP(p), _hoops_PGCGP (null), key (0), count (0) {}

_hoops_GGCGP::~_hoops_GGCGP () {
	if (count > 0)
		FREE_ARRAY (_hoops_PGCGP, count, _hoops_PGRPR const *);
}

void _hoops_HICS::_hoops_IACHA (_hoops_PGRPR const * _hoops_HGCGP, Display_Context const * dc) {
	CP			old = *this;

	*this = (const HOOPS::_hoops_HICS &) Create (dc->memory_pool);
	if (old == null) {
		CP::_hoops_RPPGP->count = 1;
		POOL_ZALLOC_ARRAY (CP::_hoops_RPPGP->_hoops_PGCGP, 1, _hoops_PGRPR const *, dc->memory_pool);
	}
	else {
		CP::_hoops_RPPGP->count = old->count + 1;
		CP::_hoops_RPPGP->key = old->key;
		POOL_ZALLOC_ARRAY (CP::_hoops_RPPGP->_hoops_PGCGP, CP::_hoops_RPPGP->count, _hoops_PGRPR const *, dc->memory_pool);
		_hoops_AIGA (old->_hoops_PGCGP, old->count, _hoops_PGRPR const *, &CP::_hoops_RPPGP->_hoops_PGCGP[1]);
	}
	CP::_hoops_RPPGP->_hoops_PGCGP[0] = _hoops_HGCGP;
	CP::_hoops_RPPGP->key ^= (POINTER_SIZED_INT)_hoops_HGCGP;
	CP::_hoops_RPPGP->key++;
}


Tree_Node::~Tree_Node () {
	Display_Context alter *	dc = _hoops_PGRCA(nr->_hoops_SRA);
	_hoops_HIHCP *			list;
	_hoops_HIHCP *			victim;

	//_hoops_RH _hoops_HSPR _hoops_RIS _hoops_HIRGR _hoops_IRS _hoops_SCCHH _hoops_GGR 8657_hoops_AGHSS
	if (BIT (flags, _hoops_HSGGH)) {
		_hoops_SPAGR				_hoops_GHAGR (segment->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
		_hoops_AHAGR *		_hoops_CSC = HI_Find_Segment_Cache (segment, path);

		if (ALLBITS(dc->flags, _hoops_GIRIP|_hoops_HSAGR) &&
			_hoops_CSC != null && _hoops_CSC->_hoops_PHAGR() != null) {
			// _hoops_RPP _hoops_HAR _hoops_SR _hoops_CHR _hoops_PHARA _hoops_GH
			_hoops_GPAGR	_hoops_RPAGR = _hoops_CSC->_hoops_PHAGR();
			_hoops_PPCGH (nr, &_hoops_RPAGR->_hoops_GAHA, false);
			HD_Free_Deferred_3D_Geometry (_hoops_GARGH);
			dc->flags &= ~_hoops_HSAGR;
			_hoops_APSRR(dc, "aborting seg_dl","", 0);
		}
	}

	if (dc->_hoops_SSGC >= 0 &&
		_hoops_CSC != null) {
		_hoops_GPAGR 	 _hoops_RPAGR = _hoops_CSC->_hoops_PHAGR();

		if (_hoops_RPAGR != null && _hoops_RPAGR->_hoops_GAHA != null) {
			_hoops_GACR *dl;
			HI_Get_Display_List (dc->_hoops_GHRI, &_hoops_RPAGR->_hoops_GAHA, &dl);
			ASSERT (nr->_hoops_IRR->_hoops_PCHS == Heur_MAX_EXTENT_MODE_DEFER);
			_hoops_RGHSS (nr, dl, segment, path);
		}
	}

	if (_hoops_PARGH != null) {
		_hoops_RAHGA	*		_hoops_PGHSS = dc->_hoops_CRIGA;

		dc->_hoops_CRIGA = _hoops_PARGH;
		HD_Process_Cut_Geometry (nr, null, _hoops_HICS(), false, true);
		dc->_hoops_CRIGA = _hoops_PGHSS;
	}

	list = _hoops_HARGH;
	while ((victim = list) != null) {
		list = victim->prev;
		delete victim;
	}
	list = _hoops_HPAGR;
	while ((victim = list) != null) {
		list = victim->prev;
		victim->_hoops_SIHCP(nr, true);
		delete victim;
	}

	delete _hoops_AARGH;
}

local bool _hoops_HGHSS (
	_hoops_CRCP const *			_hoops_SRCP)
{
	Subsegment const *		_hoops_GIPIA;

	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
		if (_hoops_GIPIA->type == _hoops_AGRPR || !BIT(((_hoops_CRCP *)_hoops_GIPIA)->_hoops_PHSI, _hoops_GIPSA))
			return true;
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);

	return false;
}


local bool _hoops_IGHSS (
	Net_Rendition alter &		nr,
	bool alter &				_hoops_CGHSS) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	Tree_Node *					node = dc->_hoops_AHSI;
	_hoops_CRCP const *				_hoops_SRCP = node->segment;

	/* _hoops_CIPSR _hoops_ARI _hoops_ICIC _hoops_CR '_hoops_AIHGP' _hoops_GPRI _hoops_RPP '_hoops_HSPP' _hoops_HRGR _hoops_PCCP _hoops_HISCI */
	if (ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_PCHGP|_hoops_ACHGP)) {	// "_hoops_GAAP" _hoops_CPHP _hoops_IS _hoops_RGHH
		_hoops_SPAGR					_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
		_hoops_AHAGR *			_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, node->path);

		if (_hoops_CSC != null) {
			_hoops_PIHGP			_hoops_CPGGC = _hoops_CSC->_hoops_SRSGP();		// _hoops_HPHR _hoops_RPAIA _hoops_CGH _hoops_SHH _hoops_ARI

			if (BIT (_hoops_CPGGC, _hoops_PCHGP))
				return false;

			if (BIT (_hoops_CPGGC, _hoops_ACHGP)) {
				bool				_hoops_SGHSS = true;	// _hoops_CCGR _hoops_CIIHP _hoops_IAII

				if (BIT (_hoops_CPGGC, _hoops_PCHGP)) {
					if (BIT (_hoops_SRCP->_hoops_RCGC, _hoops_PSPCR))
						_hoops_SGHSS = false;
					else if (_hoops_SRCP->bounding != null) {
						if (BIT (_hoops_SRCP->bounding->flags, _hoops_AAPGP))
							_hoops_SGHSS = false;
						else {
							bool _hoops_SSRPS =
								ANYBIT (_hoops_SRCP->bounding->flags, _hoops_IGCIR|Bounding_TRANSFORM_DEPENDENT) ||
								  BIT (_hoops_SRCP->bounding->flags, _hoops_HGCIR) &&
								  (nr->_hoops_SISI->transform != FT_FULL ||
								   BIT (dc->_hoops_CPGPR, _hoops_RSCCA)) ||
								  ANYBIT (nr->_hoops_AHP->line_style->flags,
								   _hoops_PRCAP|LSF_OFFSET|LSF_WEIGHT|_hoops_RHISA|LSF_GLYPHS);

							if (_hoops_SSRPS)
								_hoops_SGHSS = false;
						}
					}
				}

				if (_hoops_SGHSS) {
					_hoops_RCCA(_hoops_RIRGH)++;
					node->stage = _hoops_CCGGH;
					return true;
				}
			}
		}

		return false;
	}

	_hoops_CGHSS = false;		/* _hoops_RSIPR _hoops_RHGCP _hoops_GHCRH _hoops_GRHSS */

	return false;
}


local bool _hoops_RRHSS (
	Net_Rendition alter &		nr) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	Tree_Node *					node = dc->_hoops_AHSI;
	_hoops_CRCP const *				_hoops_SRCP = node->segment;
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;

	// _hoops_ASIGA _hoops_ISPR _hoops_SRGR _hoops_PAR _hoops_HPRC?
	bool _hoops_SSRPS =
				ANYBIT (_hoops_SRCP->bounding->flags, _hoops_IGCIR|Bounding_TRANSFORM_DEPENDENT) ||
				  BIT (_hoops_SRCP->bounding->flags, _hoops_HGCIR) && nr->_hoops_SISI->transform != FT_FULL ||
				  ANYBIT (nr->_hoops_AHP->line_style->flags,
				   _hoops_PRCAP|LSF_OFFSET|LSF_WEIGHT|_hoops_RHISA|LSF_GLYPHS);

	/* _hoops_SR'_hoops_ASAR _hoops_HPIAA _hoops_SGS _hoops_IRS _hoops_IAPRR _hoops_AAGA _hoops_HRGR _hoops_HAR _hoops_HIHP _hoops_AAR _hoops_HPGR _hoops_RH _hoops_HRGS */
	if (BIT (_hoops_IHCR->_hoops_APH, _hoops_GHIRP)) {
		Vector const *	_hoops_ARHSS = &_hoops_IHCR->_hoops_SPH->_hoops_IIPCR;
		Vector const *	_hoops_PRHSS = &_hoops_RRGH->vector;
		float			_hoops_IIIRP = _hoops_RRGH->_hoops_IIIRP;
		float			_hoops_GCCRA;

		_hoops_GCCRA = (float)_hoops_ISSSR(_hoops_ARHSS->x*_hoops_PRHSS->x + _hoops_ARHSS->y*_hoops_PRHSS->y + _hoops_ARHSS->z*_hoops_PRHSS->z);

		if (_hoops_GCCRA < _hoops_IIIRP) {
			_hoops_RCCA(_hoops_GIRGH)++;
			node->stage = _hoops_CCGGH;
			return true;
		}
	}

	if (!_hoops_SSRPS &&
		ANYBIT (_hoops_IHCR->_hoops_APH, Heur_Culling_EXTENT|_hoops_RIHS|Heur_Culling_VIEW_FRUSTUM)) {
		int		_hoops_SIHS = 0;

		if (!BIT (nr->current, _hoops_CRSI) &&
			ANYBIT (_hoops_IHCR->_hoops_APH, Heur_Culling_EXTENT|_hoops_RIHS) &&
			BIT (_hoops_RRGH->_hoops_SHHS, _hoops_AIIRP)) {
			if (BIT (_hoops_IHCR->_hoops_APH, _hoops_RIHS))
				_hoops_SIHS = _hoops_RRGH->_hoops_GCHS;
			if (BIT (_hoops_IHCR->_hoops_APH, Heur_Culling_EXTENT))
				_hoops_SIHS = _hoops_IAAA(_hoops_RRGH->_hoops_GRGC, _hoops_SIHS);
		}

		if (BIT(node->flags, _hoops_IGRGH) &&
			HOOPS_WORLD->_hoops_HCPGI != 1.0f)
			_hoops_SIHS *= HOOPS_WORLD->_hoops_HCPGI;

		Test	_hoops_ASIS = Test_DISJOINT;

		if (_hoops_RRGH->_hoops_PCHS != Heur_MAX_EXTENT_MODE_DEFER) {
			_hoops_ASIS = HD_Transform_And_Test_Bounding (nr, &_hoops_SRCP->bounding,
															&nr->_hoops_SAIR->_hoops_HHCAR,
															&nr->_hoops_SAIR->_hoops_SCIH,
															_hoops_SIHS,
															&node->_hoops_CIHS);
		}
		else {
			float	_hoops_SRIHS = nr->_hoops_SAIR->_hoops_SCIH.left - nr->_hoops_SAIR->_hoops_HHCAR.left;

			HD_Transform_And_Test_Simple_Sphere (nr, 1, &_hoops_SRCP->bounding->sphere, null, _hoops_SRIHS,
												 _hoops_SIHS, &_hoops_ASIS, null, &node->_hoops_CIHS);
		}

		if (BIT (_hoops_IHCR->_hoops_APH, Heur_Culling_VIEW_FRUSTUM)) {
			switch (_hoops_ASIS) {
				case Test_DISJOINT: {
					if (BIT(_hoops_SRCP->_hoops_RCGC, _hoops_GPHGP) &&
						HOOPS_WORLD->_hoops_HCPGI != 1.0f)
						dc->_hoops_ISPGH->AddFirst(_hoops_PGRCA(_hoops_SRCP));

					_hoops_RCCA(_hoops_SHRGH)++;
					node->stage = _hoops_CCGGH;
					return true;
				}	_hoops_HHHI;

				case _hoops_AAAGI:
				case _hoops_GAAGI: {
					// _hoops_PSSSR _hoops_IH _hoops_CIPH _hoops_GCSS _hoops_GRP _hoops_IRS _hoops_RSRA _hoops_PPSR _hoops_HIH _hoops_CHCC _hoops_APPR
					// _hoops_HAR _hoops_CPSA _hoops_SGS _hoops_RISA (_hoops_CRRPA) _hoops_PAR _hoops_GHCA _hoops_SSHSH _hoops_SIPP (_hoops_CHRA)
					if (BIT (_hoops_SRCP->_hoops_RCGC, _hoops_SAHGP) &&
						(BIT (_hoops_SRCP->_hoops_RCGC, _hoops_APHGP) ||
						 ANYBIT (_hoops_SRCP->_hoops_RCGC&nr->_hoops_RGP, T_MARKERS|T_VERTICES)))
						break;

					if (!ANYBIT (_hoops_IHCR->flags, _hoops_AIHS|_hoops_PSASP))
						nr.Modify()->transform_rendition.Modify()->flags |= _hoops_AIHS;
				}	  break;

				case _hoops_RAAGI:
				case _hoops_PAAGI:
					break;
			}
		}

		/* _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_RHGCP _hoops_HPP _hoops_SASGI _hoops_HRHSS _hoops_IAPRR... */
		if (BIT (_hoops_ASIS, Test_EXTENT) &&

			ANYBIT (_hoops_IHCR->_hoops_APH, Heur_Culling_EXTENT|_hoops_RIHS) &&

			(BIT (_hoops_SRCP->_hoops_RCGC, _hoops_GPHGP) ||
			 !(BIT (_hoops_SRCP->_hoops_RCGC, _hoops_APHGP) ||
				BIT (_hoops_SRCP->_hoops_RCGC & nr->_hoops_RGP, T_MARKERS))) &&

			!BIT(_hoops_SRCP->_hoops_RCGC, _hoops_AHASA) &&

			!ANYBIT(dc->flags, _hoops_GPHHP|
								_hoops_GIHCP|_hoops_CSHSR|_hoops_IRSI) &&

			!BIT (nr->current, _hoops_CRSI) &&

			(!BIT (nr->current, _hoops_CSGGR) ||
			 !ANYBIT (_hoops_RRGH->_hoops_SRI, _hoops_GRAAP|_hoops_HSSS|_hoops_PRAAP|_hoops_SICI)) &&

			BIT (_hoops_RRGH->_hoops_SHHS, _hoops_AIIRP)) {

			if (_hoops_RRGH->_hoops_PCHS == Heur_MAX_EXTENT_MODE_DEFER) {
				if (!BIT(node->flags, _hoops_IGRGH) &&
					(!BIT (_hoops_IHCR->_hoops_APH, _hoops_RIHS) ||
					 node->_hoops_CIHS > _hoops_RRGH->_hoops_GCHS)) {

					// _hoops_PAH'_hoops_RA _hoops_CPSA _hoops_PSCPR, _hoops_HIS _hoops_HPPP _hoops_HCAGR
					if (!BIT(dc->flags, _hoops_RASS))
						return false;

					Net_Rendition					_hoops_CRAI = nr.Copy();
					_hoops_HHCR alter &		_hoops_GGCC = _hoops_CRAI->transform_rendition.Modify();
					_hoops_CGRA alter &		_hoops_GCRCS = _hoops_CRAI->_hoops_SAIR.Modify();
					_hoops_GRGH alter &			_hoops_APIHP = _hoops_CRAI->_hoops_IRR.Modify();

					_hoops_GGCC->flags |= _hoops_CAHPP;
					_hoops_GCRCS->_hoops_ASIHP |= _hoops_ACARP;

					_hoops_APIHP->_hoops_GRGC = (int)((float)_hoops_APIHP->_hoops_GRGC * 0.25f);

					int _hoops_HCHS = int ((float)node->_hoops_CIHS /
						(float)nr->_hoops_IRR->_hoops_GRGC * (float)_hoops_ICHS);

					HD_Defer_Tree_Batch (_hoops_CRAI, _hoops_SRCP, node->path, _hoops_HCHS);
				}
				else {
					if (BIT(_hoops_SRCP->_hoops_RCGC, _hoops_GPHGP) &&
						HOOPS_WORLD->_hoops_HCPGI != 1.0f)
						dc->_hoops_CSPGH->AddFirst(_hoops_PGRCA(_hoops_SRCP));

					_hoops_RCCA(_hoops_CHRGH)++;
				}
			}
			else {
				if (_hoops_RRGH->_hoops_PCHS != _hoops_CHIRP)
					_hoops_PHPSS (nr, _hoops_SRCP);

				if (BIT(_hoops_SRCP->_hoops_RCGC, _hoops_GPHGP) &&
					HOOPS_WORLD->_hoops_HCPGI != 1.0f)
					dc->_hoops_CSPGH->AddFirst(_hoops_PGRCA(_hoops_SRCP));

				_hoops_RCCA(_hoops_CHRGH)++;
			}

			node->stage = _hoops_CCGGH;
			return true;
		}
		/* _hoops_IRHSS:	*/
	}

	return false;
}

local void _hoops_CRHSS (
	Net_Rendition const &		nr)
{
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	Tree_Node *					node = dc->_hoops_AHSI;
	_hoops_CRCP const *				_hoops_SRCP = node->segment;

	if (BIT(_hoops_SRCP->_hoops_PHSI, _hoops_GIPSA) &&
		!BIT(_hoops_SRCP->_hoops_PHSI, _hoops_HSHGP)) {

#ifdef HOOPS_DEBUG_BUILD
		_hoops_SPAGR				_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
		_hoops_AHAGR *		_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP);
		_hoops_RHPSA *		_hoops_HSPIR;
		_hoops_HSPIR = _hoops_CSC->_hoops_AHPSA();
		ASSERT(_hoops_HSPIR == null || _hoops_HSPIR->_hoops_IHPSA == null);
#endif

		if (HOOPS_WORLD->_hoops_SHPSA - HOOPS_WORLD->_hoops_CIPSA < HOOPS_WORLD->_hoops_ICPGI) {
			ASSERT(_hoops_SRCP->geometry == null);

			_hoops_CRCP *	_hoops_IHPSA = HI_Create_Proxy(dc->_hoops_RIGC, _hoops_SRCP);

			ASSERT(_hoops_IHPSA != null);

			// _hoops_CAPGR
			_hoops_PSHGH(nr, _hoops_IHPSA->key);

			dc->flags |= _hoops_CAAGH;

			_hoops_PGRCA(_hoops_SRCP)->_hoops_PHSI |= _hoops_HSHGP;
		}
		else {
			HOOPS_WORLD->_hoops_RAAPH = true;
			dc->_hoops_RCAGH = true;
		}
	}
}


local void _hoops_SRHSS (
	Net_Rendition const &		nr) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	Tree_Node *					node = dc->_hoops_AHSI;
	_hoops_CRCP const *				_hoops_SRCP = node->segment;

	node->_hoops_RARGH = node->geometry;
	node->flags |= _hoops_PSGGH;

	if (ANYBIT(nr->current, _hoops_CISHP|_hoops_RSSHP))
		HD_Handle_FBI_Pending_Window (node->_hoops_SSGS);

	if (BIT (dc->_hoops_CPGPR, _hoops_ICHPA)) {
		_hoops_SPAGR						_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
		_hoops_AHAGR *				_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, node->path, false);
		_hoops_APARR alter &		_hoops_RRCI = dc->_hoops_IPCI;
		_hoops_GACR alter *		dl = null;
		bool						_hoops_RACR;
		_hoops_HCSIR const	*	_hoops_ICSIR = null;

		if (nr->_hoops_SAIR->_hoops_ASSIR != null)
			_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

		if (_hoops_ICSIR != null) {
			_hoops_PGRCA(_hoops_ICSIR)->_hoops_GHIAA = true;
			if (!ANYBIT(nr->current, _hoops_CRSI | _hoops_SRSI))
				_hoops_PGRCA(_hoops_ICSIR)->_hoops_PSPIP = false;
		}

		if (!ANYBIT (nr->current, _hoops_CRSI|_hoops_SRSI))
		   dc->flags |= _hoops_SHIIP;

		if (_hoops_RRCI->_hoops_GGSI != null && _hoops_RRCI->_hoops_AIGC != null) {
			if (nr->_hoops_IRR->_hoops_GAHA == Display_List_SEGMENT &&
				nr->_hoops_IRR->_hoops_GRGC >= 0 &&
				!BIT(dc->flags, _hoops_IRSI) &&
				!BIT (nr->current, _hoops_PGCGA) &&
				!BIT (nr->_hoops_ARA->_hoops_PRSI.options, _hoops_HRSI)) {

				/* _hoops_RPP _hoops_PIGGP _hoops_IISI */
				if (ANYBIT (nr->_hoops_IRR->_hoops_SRI, _hoops_SGAAP|_hoops_SICI) ||
					 (BIT (nr->_hoops_IRR->_hoops_SRI, _hoops_GAI) && BIT (dc->_hoops_PGCC.flags, _hoops_ISSHP))) {
					_hoops_SCASP _hoops_GAHSS =  nr->transform_rendition->flags;

					/* _hoops_RPP _hoops_HAH _hoops_AHPH _hoops_SS _hoops_GGR _hoops_HIRA _hoops_IS _hoops_RGHH _hoops_GGR _hoops_GSIA, _hoops_GA'_hoops_RA _hoops_AA _hoops_HCGI */
					if (!BIT (_hoops_GAHSS, _hoops_GRHH) || BIT(_hoops_GAHSS, _hoops_PRIR))
						node->flags |= _hoops_HSGGH;
				}
			}
			if (BIT(dc->flags, _hoops_GAAGH))
				node->flags |= _hoops_ISGGH;
		}

		if (ANYBIT (node->flags, _hoops_HSGGH|_hoops_ISGGH)) {
			_hoops_GPAGR		_hoops_RPAGR;

			//_hoops_ASSI _hoops_RPGAR _hoops_IS _hoops_HSSRR _hoops_GAPA _hoops_SPGIA
			//_hoops_RPP _hoops_RGR _hoops_HRGR _hoops_SAHR _hoops_HGAI _hoops_CCH _hoops_HGAGA
			if (BIT (node->flags, _hoops_HSGGH)) {
				if (_hoops_CSC != null) {
					_hoops_RPAGR = _hoops_CSC->_hoops_PHAGR();

					if (_hoops_RPAGR != null) {
						Action_Mask		_hoops_SGRC = 0, _hoops_RAHSS = 0;

						if (_hoops_RPAGR->_hoops_GAHA) {
							if (BIT (_hoops_RPAGR->_hoops_GAHA->_hoops_AGRI, DL_TEXTURING))
								_hoops_SGRC = _hoops_RAPI;
							else
								_hoops_RPCGH (nr, &_hoops_RPAGR->_hoops_GAHA, &_hoops_SGRC, null);
						}
						if (_hoops_RPAGR->_hoops_HHICA)
							_hoops_RPCGH (nr, &_hoops_RPAGR->_hoops_HHICA, &_hoops_RAHSS, null);

						if (ANYBIT (_hoops_SGRC|_hoops_RAHSS, _hoops_RSCI)) {
							 _hoops_CSC->_hoops_HHAGR(null);
							 _hoops_RPAGR = null;
						}
					}
				}

				if (_hoops_RPAGR == null) {
					bool _hoops_ARIR = nr->_hoops_IHA->_hoops_CHA->_hoops_ARIR ||
										nr->_hoops_IHA->_hoops_GIA->_hoops_ARIR;
					bool _hoops_AAHSS = BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_EDGES);

					if (!_hoops_ARIR && !_hoops_AAHSS) {
						_hoops_AHAGR *		_hoops_PAHSS = _hoops_SRCP->_hoops_CSC;

						while (_hoops_PAHSS != null) {
							if (_hoops_PAHSS != _hoops_CSC) {
								_hoops_GPAGR		_hoops_HAHSS = _hoops_PAHSS->_hoops_PHAGR();

								if (_hoops_HAHSS != null) {
									Action_Mask		_hoops_SGRC = 0, _hoops_RAHSS = 0;

									if (_hoops_HAHSS->_hoops_GAHA) {
										if (BIT (_hoops_HAHSS->_hoops_GAHA->_hoops_AGRI, DL_TEXTURING))
											_hoops_SGRC = _hoops_RAPI;
										else
											_hoops_RPCGH (nr, &_hoops_HAHSS->_hoops_GAHA, &_hoops_SGRC, null);
									}
									if (_hoops_HAHSS->_hoops_HHICA)
										_hoops_RPCGH (nr, &_hoops_HAHSS->_hoops_HHICA, &_hoops_RAHSS, null);

									if (!ANYBIT (_hoops_SGRC|_hoops_RAHSS, _hoops_RSCI)) {
										_hoops_RPAGR = _hoops_HAHSS;
										if (_hoops_CSC == null)
											_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, node->path);
										_hoops_CSC->_hoops_HHAGR (_hoops_RPAGR);
										break;
									}
								}
							}
							_hoops_PAHSS = _hoops_PAHSS->next;
						}
					}
				}
			}

			if (_hoops_CSC == null)
				_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, node->path);

			if (_hoops_RPAGR == null) {
				if ((_hoops_RPAGR = _hoops_CSC->_hoops_PHAGR()) == null) {
					_hoops_RPAGR = _hoops_GPAGR::Create(dc->memory_pool);
					_hoops_CSC->_hoops_HHAGR (_hoops_RPAGR);
				}
			}

			node->_hoops_CSC = _hoops_CSC;


			dc->_hoops_SHAGH = 0;
			dc->_hoops_GSGC = 0;
			dc->_hoops_SCGC = 0;
			dc->_hoops_GIAGH = null;
			dc->_hoops_HHAGH = null;
			if (BIT (node->flags, _hoops_HSGGH)) {
				node->_hoops_GARGH = dc->_hoops_GPSS[dc->_hoops_IASS];
				dc->_hoops_GPSS[dc->_hoops_IASS] = null;
				if (_hoops_RPAGR->_hoops_HHICA) {
					Action_Mask _hoops_IAHSS = 0;
					Action_Mask _hoops_CAHSS = 0;

					_hoops_RPCGH (nr, &_hoops_RPAGR->_hoops_HHICA, &_hoops_IAHSS, &_hoops_CAHSS);
					if (_hoops_IAHSS) {
						_hoops_RACR = HI_Get_Display_List (dc->_hoops_GHRI, &_hoops_RPAGR->_hoops_GAHA, &dl);
						ASSERT (!_hoops_RACR);
						dl->action_mask |= _hoops_IAHSS;
						dl->action_mask |= _hoops_CAHSS;
					}
				}
			}
			dc->_hoops_SSGC = -1;
			if (!_hoops_GPCGH (nr, &_hoops_RPAGR->_hoops_GAHA, &_hoops_RRCI->mask, BIT(dc->flags, _hoops_CHSI)))
				node->flags &= ~_hoops_HSGGH;

			if (BIT (node->flags, _hoops_HSGGH))
				dc->flags |= _hoops_HSAGR;

			if (dc->_hoops_SSGC >= 0) {
				ASSERT (nr->_hoops_IRR->_hoops_PCHS == Heur_MAX_EXTENT_MODE_DEFER);
				if (ANYBIT(dc->flags, _hoops_GIHCP|_hoops_GPHHP) ||
					BIT (nr->_hoops_IRR->_hoops_SRI, _hoops_SICI))
					dc->_hoops_SSGC = -1;
				else {
					if (!dl)
						HI_Get_Display_List (dc->_hoops_GHRI, &_hoops_RPAGR->_hoops_GAHA, &dl);
					_hoops_RGHSS (nr, dl, _hoops_SRCP, node->path);
				}
			}
		}
	}
}

local void _hoops_SAHSS (
	Net_Rendition const &		nr) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	Tree_Node *					node = dc->_hoops_AHSI;
	_hoops_CRCP const *				_hoops_SRCP = node->segment;
	_hoops_SPAGR						_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
	_hoops_AHAGR *				_hoops_CSC = node->_hoops_CSC;
	_hoops_PGCIP alter *			_hoops_GPHSS;
	_hoops_GACR alter *		dl = null;
	_hoops_GPAGR			_hoops_RPAGR = _hoops_CSC->_hoops_PHAGR();

	if (BIT (node->flags, _hoops_HSGGH)) {
		if (dc->_hoops_SHAGH != 0 || dc->_hoops_GSGC != 0) {
			bool					_hoops_RACR;
			_hoops_RACR = HI_Get_Display_List (dc->_hoops_GHRI, &_hoops_RPAGR->_hoops_GAHA, &dl);
			ASSERT (!_hoops_RACR);
			/* _hoops_GRHP _hoops_RH _hoops_HICA _hoops_RSPPP _hoops_GGR _hoops_AGIR _hoops_RH _hoops_ARRS _hoops_AGHR _hoops_GSHAC _hoops_IS _hoops_ISAP*/
			UNREFERENCED (_hoops_RACR);

			/* _hoops_PCHIA _hoops_RH _hoops_AIRI _hoops_HIGR.  _hoops_HAIA _hoops_PHPA _hoops_AGR _hoops_CHCA _hoops_GGHP _hoops_RHHS _hoops_CIAA _hoops_RH
			   (_hoops_RAR-_hoops_AAR _hoops_SHCAH) _hoops_SGSI _hoops_CPCI */
			if (ANYBIT (dc->_hoops_SHAGH, _hoops_SHSI)) {
				HI_Clean_Display_List (&_hoops_RPAGR->_hoops_GAHA, true, false);
			}
			else {
				dl->action_mask |= dc->_hoops_SHAGH;
				dl->action_mask |= dc->_hoops_GSGC;
			}
		}
	}

	_hoops_PPCGH (nr, &_hoops_RPAGR->_hoops_GAHA, BIT(dc->flags, _hoops_CHSI));
	if (dc->_hoops_SHCI() == _hoops_RICI && _hoops_RPAGR->_hoops_HHICA != null)
		_hoops_GPCIP (nr, _hoops_RPAGR->_hoops_HHICA);

	if (BIT (node->flags, _hoops_HSGGH))
		dc->flags &= ~_hoops_HSAGR;

	if (dc->_hoops_SSGC >= 0) {
		if (!dl)
			HI_Get_Display_List (dc->_hoops_GHRI, &_hoops_RPAGR->_hoops_GAHA, &dl);
		ASSERT (nr->_hoops_IRR->_hoops_PCHS == Heur_MAX_EXTENT_MODE_DEFER);
		_hoops_RGHSS (nr, dl, _hoops_SRCP, node->path);
	}
	if (BIT (node->flags, _hoops_HSGGH)) {
		_hoops_GPHSS = dc->_hoops_GPSS[dc->_hoops_IASS];
		dc->_hoops_GPSS[dc->_hoops_IASS] = node->_hoops_GARGH;
		node->_hoops_GARGH = null;

		if (_hoops_GPHSS || _hoops_RPAGR->_hoops_HHICA)
			_hoops_RIPSS (nr, _hoops_CSC, _hoops_GPHSS);
	}
}


local void _hoops_RPHSS (
	Net_Rendition const &		in_nr) {
	Net_Rendition				nr = in_nr.Copy();
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	Tree_Node *					node = dc->_hoops_AHSI;
	_hoops_CRCP const *				_hoops_SRCP = node->segment;
	_hoops_PHSGA *			_hoops_APHSS;
	_hoops_HHCR			_hoops_IHCR;
	_hoops_GRGH				_hoops_RRGH;
	_hoops_GCIR		_hoops_RCIR;
	_hoops_PSIHP			_hoops_HSIHP;

	{
		_hoops_SPAGR					_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
		_hoops_AHAGR *			_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, node->path);

		if ((_hoops_APHSS = _hoops_CSC->_hoops_GHSGA()) == null) {
			ZALLOC (_hoops_APHSS, _hoops_PHSGA);
			_hoops_CSC->_hoops_RGSGP (_hoops_APHSS);
		}
	}

	if (!_hoops_APHSS->valid && BIT(node->_hoops_CPGPR, _hoops_ISCCA)) {
		dc->_hoops_RHIGA = _hoops_SRCP;

		_hoops_IHCR = nr.Modify()->transform_rendition.Modify();
		_hoops_IHCR->flags &= ~_hoops_IGSP;
		_hoops_RRGH = nr->_hoops_IRR.Modify();
		_hoops_RRGH->_hoops_GAHA = Display_List_NONE;

		HD_Generate_Cut_Geometry (nr, _hoops_SRCP, node->geometry);

		if (BIT (node->flags, _hoops_CSGGH))
			HD_Process_Cut_Geometry (nr, _hoops_SRCP, node->path, true, true);
		else if (nr->_hoops_CPP->_hoops_PRIGA.level == _hoops_SSSRP)
			HD_Process_Cut_Geometry (nr, _hoops_SRCP, node->path, true, false);

		_hoops_APHSS->valid = true;
	}

	if (_hoops_APHSS->_hoops_RHSGA != null && !BIT (nr->current, _hoops_RPCIP)) {
		_hoops_CIGA				_hoops_SPIHP;
		_hoops_RRSGA const *		_hoops_PRIGA = _hoops_APHSS->_hoops_RHSGA;

		_hoops_HGCGA (dc, "draw cut geometry", nr);

		if (in_nr->_hoops_RSGC->action._hoops_HSCHP != nullroutine) {
			dc->_hoops_IPCI->draw_3d_polyline = HD_Std_3D_Polyline;
			dc->_hoops_IPCI->_hoops_CHCI = HD_Standard_Render;
		}

		do if (_hoops_PRIGA->geometry != null) {
			nr = in_nr.Copy();

			_hoops_HSIHP = nr->_hoops_RSGC.Modify();
			_hoops_HSIHP->action.draw_dc_polyline = _hoops_HSIHP->action._hoops_HSCHP;

			_hoops_IHCR = nr->transform_rendition.Modify();
			_hoops_IHCR->flags &= ~_hoops_IGSP;
			_hoops_IHCR->heuristics &= ~(_hoops_GPSA |
								_hoops_SASA);

			/* _hoops_RGAR _hoops_AIRI _hoops_RH _hoops_CIPH _hoops_SR _hoops_PICP _hoops_AHCA */
			_hoops_RRGH = nr->_hoops_IRR.Modify();
			_hoops_RRGH->_hoops_AARIP &= ~(T_FACES | T_ANY_EDGE | T_LINES | T_MARKERS|T_VERTICES);

			/* _hoops_PPHSS: _hoops_PISH _hoops_RGR _hoops_HPP _hoops_AACC _hoops_CPAP _hoops_HPRC _hoops_GCSS _hoops_CCA _hoops_RH _hoops_IPPA? */
			_hoops_RRGH->_hoops_AARIP |= _hoops_RRGH->_hoops_GHIHP;

			nr->_hoops_RGP = _hoops_RRGH->_hoops_AARIP;
			nr->flags &= ~_hoops_IPIHP;
			HD_Fixup_Attributes (nr, null, _hoops_IPIHP);

			_hoops_RRGH->_hoops_GAHA = Display_List_NONE;
			_hoops_RCIR = nr->_hoops_CPP.Modify();

			{
				_hoops_SSP alter &		_hoops_GGH = _hoops_IHCR->_hoops_RGH.Modify();

				/* _hoops_SRSIR _hoops_ARP _hoops_PGAP _hoops_AGCCA _hoops_IS _hoops_RH _hoops_PIASR _hoops_IPPA */
				_hoops_IAPA alter *		_hoops_HRCAR;
				{
					_hoops_IAPA alter **			_hoops_HPHSS;

					_hoops_HPHSS = (_hoops_IAPA alter **)&_hoops_GGH->_hoops_ISIGA;
					if ((_hoops_HRCAR = *_hoops_HPHSS) != null) do {
						_hoops_GPPA const *	_hoops_IRCAR;

						if ((_hoops_IRCAR = _hoops_HRCAR->_hoops_APPA) != null) do {
							if (_hoops_IRCAR->id == _hoops_PRIGA->_hoops_AAHGA)
								break;
						} while ((_hoops_IRCAR = _hoops_IRCAR->next) != null);

						if (_hoops_IRCAR != null) {
							*_hoops_HPHSS = _hoops_HRCAR->next;
							_hoops_HRCAR->next = null;
							break;
						}
					} while ((_hoops_HRCAR = *(_hoops_HPHSS = &_hoops_HRCAR->next)) != null);
				}

				if (_hoops_HRCAR != null) {
					if (_hoops_HRCAR->_hoops_IPASP != 1) {
						_hoops_GPPA const *	_hoops_IRCAR;

						_hoops_IRCAR = _hoops_HRCAR->_hoops_APPA;
						do if (_hoops_IRCAR->id != _hoops_PRIGA->_hoops_AAHGA) {
							_hoops_IAPA alter		*_hoops_GCCRS;
							_hoops_GPPA alter	*_hoops_ACCRS;

							ZALLOC (_hoops_GCCRS, _hoops_IAPA);
							_hoops_GCCRS->next = (_hoops_IAPA alter *)_hoops_GGH->_hoops_ISIGA;
							_hoops_GGH->_hoops_ISIGA = _hoops_GCCRS;

							ALLOC (_hoops_ACCRS, _hoops_GPPA);
							_hoops_RSAI (_hoops_IRCAR, _hoops_GPPA, _hoops_ACCRS);
							_hoops_PPASP (_hoops_ACCRS);
							_hoops_ACCRS->next = null;
							_hoops_GCCRS->_hoops_APPA = _hoops_ACCRS;
							++_hoops_GCCRS->_hoops_IPASP;
						} while ((_hoops_IRCAR = _hoops_IRCAR->next) != null);
					}

					HD_Free_Cutting_Plane_Sets (_hoops_HRCAR);
				}

				if (_hoops_GGH->_hoops_ISIGA == null) {
					_hoops_IHCR->_hoops_RGH = null;
					_hoops_IHCR->flags &= ~(_hoops_CSP|_hoops_RCRIP|
									_hoops_HHGGA);

					nr->current &= ~_hoops_GPRIP;
					nr->_hoops_RCSHR &= ~_hoops_GPRIP;
				}
				else {
					HD_Validate_Cutting_Plane_Sets (_hoops_GGH);

					if (BIT (_hoops_IHCR->flags, _hoops_PRAIP)) {
						HD_Set_DC_Cutting_Planes (nr);
						_hoops_IHCR->flags |= _hoops_HHGGA;
					}
				}
			}

			/* _hoops_IRHH _hoops_RCRR _hoops_SR _hoops_PGSA _hoops_GRP _hoops_IRPR _hoops_AIRC */
			if (_hoops_RCIR->_hoops_PRIGA._hoops_SRIGA == _hoops_RGGAP) {
				nr->_hoops_AHP = nr->_hoops_CAIHP;

				_hoops_SPIHP = nr->_hoops_HAIHP;
				_hoops_SPIHP->_hoops_AGP = nr->_hoops_IHA->_hoops_AGP;
				nr->_hoops_IHA = nr->_hoops_HAIHP;
			}
			else if (_hoops_RCIR->_hoops_PRIGA._hoops_SRIGA != _hoops_AGGAP) {
				_hoops_HHA			_hoops_RGHHP;

				_hoops_CIGA alter &		_hoops_IPHSS = nr.Modify()->_hoops_IHA.Modify();
				Line_Rendition alter &		_hoops_ARAIS = nr->_hoops_AHP.Modify();

				_hoops_IPHSS->color = _hoops_APHSS->_hoops_RSISR;
				_hoops_ARAIS->color = _hoops_APHSS->_hoops_IHSGA;

				_hoops_IPHSS->pattern = FP_SOLID;

				HD_Replace_Line_Style(_hoops_ARAIS, nr->_hoops_GCSHP->_hoops_IHRIP);

				_hoops_RGHHP = _hoops_IPHSS->_hoops_CHA;
				_hoops_IPHSS->_hoops_GIA = _hoops_RGHHP;

				if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR) {
					RGBAS32		tmp = _hoops_IPHSS->color;
					_hoops_RGHHP->_hoops_CSHR = tmp;
				}
				else {
					_hoops_RHAH const *	_hoops_CSIR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR;
					_hoops_AHAH 			_hoops_SHAIS;

					if (_hoops_CSIR->length > 0)
						_hoops_ICRCP (_hoops_CSIR, (float)_hoops_IPHSS->color._hoops_PGGCR,
									   _hoops_RGHHP->_hoops_CSHR, false, _hoops_SHAIS);
				}
			}
			else {
				/* _hoops_SCGR _hoops_HSP _hoops_HAIR _hoops_HRGR _hoops_IHRI, _hoops_SGH _hoops_SCGR _hoops_ISHA _hoops_HAIR _hoops_IS _hoops_PGSA _hoops_AACC '_hoops_APGR' */
				Line_Rendition alter &		_hoops_ARAIS = nr.Modify()->_hoops_AHP.Modify();

				_hoops_ARAIS->color = nr->_hoops_RHP->color;

				HD_Replace_Line_Style(_hoops_ARAIS, nr->_hoops_GCSHP->_hoops_IHRIP);

				if (nr->_hoops_IHA->pattern != FP_SOLID)
					nr->_hoops_IHA.Modify()->pattern = FP_SOLID;
			}

			/* _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_ICSI _hoops_CCSHP _hoops_III, _hoops_HPRC _hoops_GHCA _hoops_RRP _hoops_IS _hoops_AGRP */
			if (_hoops_RRGH->_hoops_SRI == _hoops_SICI)
				HD_Fixup_Attributes (nr, null, _hoops_IPIHP);

			nr->_hoops_PSGI &= ~(T_FACES|T_LINES);
			if (_hoops_RIRGR(nr->_hoops_IHA->_hoops_CHA))
				nr->_hoops_PSGI |= T_FACES;
			if (_hoops_RIRGR(nr->_hoops_AHP->_hoops_CHA))
				nr->_hoops_PSGI |= T_LINES;

			_hoops_RPHPP (nr, _hoops_PRIGA->geometry, _hoops_RAPI, false);
		} while ((_hoops_PRIGA = _hoops_PRIGA->next) != null);

		_hoops_HGSGA (dc, "draw cut geometry");
	}
}


local void _hoops_CPHSS (
	Net_Rendition const &		in_nr) {
	Net_Rendition				nr = in_nr.Copy();
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	Tree_Node *					node = dc->_hoops_AHSI;
	_hoops_CRCP const *				_hoops_SRCP = node->segment;
	_hoops_ARPA const *				plane;

	if (!BIT (nr->transform_rendition->flags, _hoops_IGCC))
		HD_Validate_World_To_Screen (nr);

	_hoops_RPRA const *			_hoops_APRA = nr->transform_rendition->_hoops_CGCC->_hoops_PPRA()->data.elements;

	plane = &nr->_hoops_CPP->_hoops_GHSS.plane;

	if (_hoops_APRA[2][0] * plane->a +
		_hoops_APRA[2][1] * plane->b +
		_hoops_APRA[2][2] * plane->c +
		_hoops_APRA[2][3] * plane->d < 0.0f) {
		_hoops_CIGA				_hoops_SIGA;
		_hoops_HHCR			_hoops_IHCR;
		_hoops_GRGH				_hoops_RRGH;
		_hoops_HHA			mat;
		_hoops_CPSS *				_hoops_SPSS;

		{
			_hoops_SPAGR					_hoops_GHAGR (node->segment->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
			_hoops_AHAGR *			_hoops_CSC = HI_Find_Segment_Cache (node->segment, node->path);

			if ((_hoops_SPSS = _hoops_CSC->_hoops_CSCGP()) == null) {
				ZALLOC (_hoops_SPSS, _hoops_CPSS);
				_hoops_CSC->_hoops_ISCGP (_hoops_SPSS);
			}
		}

		if (!_hoops_SPSS->valid)
			HD_Shadow_Update (nr, _hoops_SRCP, node->path);
		else if (BIT (dc->_hoops_CPGPR, _hoops_PSCCA) || !_hoops_SPSS->_hoops_RIHSP)
			HD_Reposition_Shadow (nr, _hoops_SRCP, node->path);

		if (_hoops_SPSS->valid && _hoops_SPSS->_hoops_APGGR) {
			float							_hoops_PSIC[12];
			int								i;
			Tristrip *						tristrip;

			_hoops_SIGA = nr->_hoops_IHA.Modify();
			_hoops_IHCR = nr->transform_rendition.Modify();
			_hoops_RRGH = nr->_hoops_IRR.Modify();
			nr->_hoops_CPP.Modify();

			_hoops_SIGA->_hoops_AGP = null;
			mat = _hoops_SIGA->_hoops_CHA;
			_hoops_SIGA->_hoops_GIA = mat;

			_hoops_IHCR->_hoops_RGH = null;
			_hoops_IHCR->flags &= ~(_hoops_IGSP | _hoops_AIHS |
							_hoops_CSP|_hoops_RCRIP |
							_hoops_GRHH|_hoops_PRIR);

			if (_hoops_IHCR->_hoops_IPH->data._hoops_RAGR != _hoops_SGICR)
				_hoops_IHCR->_hoops_IPH = _hoops_SGCC::Create (dc);

			_hoops_IHCR->_hoops_CHIH = 0;
			_hoops_IHCR->_hoops_SHIH = 0;
			_hoops_IHCR->_hoops_GSCH[0] = _hoops_IHCR->_hoops_GSCH[0] + 0.9f*(_hoops_IHCR->_hoops_GSCH[1]-_hoops_IHCR->_hoops_GSCH[0]);
			_hoops_IHCR->flags |= _hoops_ISH;
			HD_Redo_Screen (nr, &_hoops_PGRCA(_hoops_IHCR->_hoops_SPH)->_hoops_GRCC);

			nr->_hoops_RCSHR |= _hoops_AHIHP;
			nr->current |= _hoops_AHIHP;

			nr->_hoops_PSGI |= T_FACES;

			nr->_hoops_CPP->_hoops_PRH._hoops_HRH = true;
			nr->_hoops_CPP->_hoops_PRH.style = Transparency_STYLE_BLENDING;

			nr->_hoops_RGP = T_FACES;
			_hoops_RRGH->_hoops_GAHA = Display_List_NONE;

			_hoops_SIGA->color = _hoops_SIGA->_hoops_RGIR =
					nr->_hoops_CPP->_hoops_GHSS.color;
			_hoops_SPSS->texture->_hoops_HPIR._hoops_IPIR = nr->_hoops_CPP->_hoops_GHSS.color;
			mat->_hoops_IRIR = nr->_hoops_CPP->_hoops_GHSS._hoops_IRIR;

			for (i=0; i<_hoops_GAGRA; i++) {
				if (mat->texture[i] != null) {
					_hoops_HPRH(mat->texture[i]);
					mat->texture[i] = null;
				}
			}
			HI_Free_Diffuse_Channel_List (mat->_hoops_SCA);
			mat->_hoops_SCA = HI_New_Diffuse_Channel (_hoops_SPSS->texture);
			mat->_hoops_SCA->flags |= _hoops_PRA;
			mat->_hoops_ARIR = true;

			/* _hoops_PSSSR _hoops_IH _hoops_PISC _hoops_AGIR _hoops_CAS _hoops_CPS _hoops_SHS _hoops_GGR _hoops_HIRA _hoops_CSAP _hoops_CHCC _hoops_GRAA-_hoops_SPHSS */
			HD_Handle_FBI_Pending_Window (nr);

			ZALLOC (tristrip, Tristrip);
			_hoops_ICAI (tristrip);
			ZALLOC (tristrip->_hoops_GSSH, _hoops_RRCC);
			_hoops_ICAI (tristrip->_hoops_GSSH);
			tristrip->total = 4;
			tristrip->point_count = 4;
			tristrip->face_count = 1;
			tristrip->points = _hoops_SPSS->points;

			if (BIT (_hoops_IHCR->flags, _hoops_PGCH))
				tristrip->_hoops_GSSH->_hoops_CCHA = (_hoops_RSSH *)_hoops_IAPSS;
			else
				tristrip->_hoops_GSSH->_hoops_CCHA = (_hoops_RSSH *)_hoops_HAPSS;
			tristrip->_hoops_GSSH->_hoops_GSHA  = 3;
			tristrip->_hoops_GSSH->_hoops_SCAI = _hoops_ASRSP|_hoops_RSRSP;

			if (_hoops_SPSS->_hoops_CHRP != 1.0f || _hoops_SPSS->_hoops_SHRP != 1.0f) {
				_hoops_AIGA (tristrip->_hoops_GSSH->_hoops_CCHA, 12, float, _hoops_PSIC);
				tristrip->_hoops_GSSH->_hoops_CCHA = _hoops_PSIC;

				_hoops_PSIC[ 0] = (_hoops_PSIC[ 0] - 0.5f) * _hoops_SPSS->_hoops_CHRP + 0.5f;
				_hoops_PSIC[ 3] = (_hoops_PSIC[ 3] - 0.5f) * _hoops_SPSS->_hoops_CHRP + 0.5f;
				_hoops_PSIC[ 6] = (_hoops_PSIC[ 6] - 0.5f) * _hoops_SPSS->_hoops_CHRP + 0.5f;
				_hoops_PSIC[ 9] = (_hoops_PSIC[ 9] - 0.5f) * _hoops_SPSS->_hoops_CHRP + 0.5f;
				_hoops_PSIC[ 1] = (_hoops_PSIC[ 1] - 0.5f) * _hoops_SPSS->_hoops_SHRP + 0.5f;
				_hoops_PSIC[ 4] = (_hoops_PSIC[ 4] - 0.5f) * _hoops_SPSS->_hoops_SHRP + 0.5f;
				_hoops_PSIC[ 7] = (_hoops_PSIC[ 7] - 0.5f) * _hoops_SPSS->_hoops_SHRP + 0.5f;
				_hoops_PSIC[10] = (_hoops_PSIC[10] - 0.5f) * _hoops_SPSS->_hoops_SHRP + 0.5f;
			}

			tristrip->_hoops_PHHA = 1;
			tristrip->lengths_allocated = 1;
			ALLOC_ARRAY (tristrip->lengths, tristrip->lengths_allocated, int);
			tristrip->lengths[0] = 4;
			tristrip->_hoops_IPII = tristrip->_hoops_SGAHR = 4;
			ALLOC_ARRAY (tristrip->_hoops_AIHA, tristrip->_hoops_IPII, int);
			ALLOC_ARRAY (tristrip->face_indices, tristrip->_hoops_SGAHR, int);
			tristrip->_hoops_RAHH |= _hoops_AAHH;
			_hoops_AIGA (_hoops_AAPSS, 4, int, tristrip->_hoops_AIHA);
			_hoops_AIGA (_hoops_PAPSS, 4, int, tristrip->face_indices);

			tristrip->_hoops_SRHA |= DL_SHADOW_TRISTRIP | _hoops_GAHH | DL_TEMPORARY_DATA;
			tristrip->_hoops_SRHA |= _hoops_SRHH | DL_DO_NOT_DEFER | DL_3D_TRANSPARENCY;

			dc->_hoops_RAI = null;
			_hoops_RACIP (nr, tristrip);

			if (_hoops_ISAI (tristrip) == 0)
				HI_Free_Tristrip (tristrip);

			/* _hoops_RGR _hoops_PPPPR'_hoops_RA _hoops_SHH _hoops_GHHSS _hoops_HPP _hoops_GSSR _hoops_RHHSS _hoops_CRAA */
			_hoops_SPSS->image->_hoops_CPGPR = 0;
		}
	}
}

local void _hoops_AHHSS (
	Net_Rendition const &		nr) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);

	if (dc->_hoops_RPSS[dc->_hoops_IASS] != null) {
		int		_hoops_HGRS = 0;
		while (ANYBIT(dc->_hoops_IPCI->mode, _hoops_AHIHP|_hoops_HSGGR|_hoops_ISGGR)) {
			_hoops_HGRS++;
			_hoops_IGRS (dc);
		}
		HD_Draw_Deferred_3D_Geometry (dc->_hoops_RPSS[dc->_hoops_IASS], true);
		HD_Free_Deferred_3D_Geometry (dc->_hoops_RPSS[dc->_hoops_IASS]);
		while (_hoops_HGRS-- > 0)
			_hoops_SGRS (dc);
		dc->_hoops_RPSS[dc->_hoops_IASS] = null;
	}

	if (dc->_hoops_HASS[dc->_hoops_IASS] != null) {
		int		_hoops_HGRS = 0;
		while (ANYBIT(dc->_hoops_IPCI->mode, _hoops_AHIHP|_hoops_HSGGR|_hoops_ISGGR|_hoops_CSGGR)) {
			_hoops_HGRS++;
			_hoops_IGRS (dc);
		}
		HD_See_Whats_Hidden (nr);
		while (_hoops_HGRS-- > 0)
			_hoops_SGRS (dc);
		dc->_hoops_HASS[dc->_hoops_IASS] = null;
		dc->_hoops_SASS[dc->_hoops_IASS] = 0;
	}
}

local bool _hoops_PHHSS (
	Net_Rendition alter &		nr) {
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	Tree_Node *					node = dc->_hoops_AHSI;
	_hoops_CRCP const *				_hoops_SRCP = node->segment;
	_hoops_HICS const &		path = node->path;
	/* _hoops_PAGA: _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_ICPAA _hoops_ARI _hoops_HII _hoops_IRS _hoops_RIRP _hoops_PAGIR, _hoops_RGR "_hoops_AISI" _hoops_RHAP _hoops_ISAP */
	nr.Modify();
	_hoops_PRGIP				_hoops_HGGRS = nr->_hoops_RCSHR & ~nr->current;
	_hoops_PRGIP				_hoops_IGGRS = nr->current & ~nr->_hoops_RCSHR;

	/* _hoops_HHHSS:

		_hoops_CCSHP _hoops_PIHA _hoops_SHH _hoops_RAS _hoops_APHSR _hoops_HIS _hoops_SGS _hoops_SCH _hoops_PAH _hoops_HIRAI _hoops_APHSR
		_hoops_PPR _hoops_SRCH _hoops_AHCR _hoops_RHGPR

		_hoops_IHHSS & _hoops_SPHGR _hoops_ACASA _hoops_RH _hoops_CCSHP _hoops_AARAR-_hoops_GGR-_hoops_GCRPA,
		_hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_IS _hoops_SHH _hoops_CPPPR _hoops_RHRIR _hoops_AHCA _hoops_RAHIR _hoops_CGSI _hoops_GGSR _hoops_IS
		_hoops_CHHSS _hoops_IS _hoops_HGCR _hoops_GGSR _hoops_IIGR _hoops_GII _hoops_IIGR _hoops_AGAP _hoops_AAIP. _hoops_HSHCR *_hoops_SS*
		_hoops_PAH _hoops_PHHR _hoops_PSAP _hoops_PPR _hoops_GPP *_hoops_GIAA* _hoops_IRS _hoops_CCSHP-_hoops_GGR-_hoops_GCRPA.

		_hoops_ARGH _hoops_SHHSS _hoops_SRS, _hoops_CR _hoops_SCH _hoops_HHSH _hoops_SHR _hoops_ACPP
		_hoops_GGR _hoops_CPS _hoops_IHGS _hoops_PISI _hoops_PPR _hoops_GIHSS _hoops_GIICP.

		_hoops_ARGH 2D _hoops_ARPP _hoops_CCSHP, _hoops_HIS _hoops_SCH _hoops_PAH _hoops_HHSA _hoops_PSAP _hoops_CCSHP _hoops_RRI
		_hoops_SSHCR.
	 */

	if (BIT (_hoops_HGGRS, _hoops_CRHPP)) {
		/* _hoops_PGSA _hoops_IRS _hoops_AISIR _hoops_HHIS */
		if (BIT (nr->_hoops_RGP, T_WINDOWS) &&
			(ANYBIT (dc->_hoops_CPGPR, _hoops_APPGP|
								   _hoops_ICHPA|
								   _hoops_PPPGP) ||
			 BIT (_hoops_SRCP->_hoops_CPGPR | dc->_hoops_RIIAP & _hoops_SRCP->_hoops_SPGPR,
				  _hoops_IPPGP))) {
			/* _hoops_HPCIP _hoops_APPP _hoops_PICP _hoops_IIGR _hoops_HCR _hoops_SPHGR */
			_hoops_CGRA alter &	_hoops_SGRA = nr->_hoops_SAIR;

			/* _hoops_RIHSS _hoops_RSAIP _hoops_IH _hoops_HGHIP _hoops_RRGI _hoops_ICSI-_hoops_CCSI */
			if (0 && BIT (_hoops_SGRA->_hoops_ASIHP, _hoops_ACARP) &&
				nr->_hoops_IRR->_hoops_GIRC) {
				/* _hoops_RRRIR _hoops_RCRR _hoops_RGR _hoops_PIHA _hoops_SHH _hoops_IRS _hoops_CCAH _hoops_RPPS */
				_hoops_SGRA->_hoops_ASIHP &= ~_hoops_ACARP;
			}

			if (_hoops_SGRA->_hoops_PHRA.right > _hoops_SGRA->_hoops_PHRA.left &&
				_hoops_SGRA->_hoops_PHRA.top > _hoops_SGRA->_hoops_PHRA.bottom &&
				BIT(dc->flags, _hoops_RASS) &&
				(BIT(dc->flags, _hoops_RCHCP) || dc->_hoops_SHCI() == _hoops_HRIIP)) {
				HD_Defer_Tree (nr, _hoops_SRCP, path);
			}
		}
	}
	else if (BIT (_hoops_HGGRS, _hoops_GAHPP)) {
		_hoops_SRPSS (nr);
		node->_hoops_CPGPR = dc->_hoops_CPGPR;
		return true;
	}
	else if (BIT (_hoops_HGGRS, _hoops_RRSIP)) {
		/* "_hoops_GGSR _hoops_IIGR _hoops_AGR" _hoops_CSAP _hoops_SAHR _hoops_IRS _hoops_RIP _hoops_HII _hoops_ISHP _hoops_CAPP _hoops_IS _hoops_HHSA
		 * _hoops_IRS *_hoops_SSRR* _hoops_GGSR _hoops_IIGR _hoops_AGR _hoops_SGSI.
		 */
		nr->_hoops_RCSHR &= ~_hoops_RRSIP;

		/* _hoops_RGR _hoops_HRGR _hoops_IRS '_hoops_CPAP' _hoops_HHIS, _hoops_HAR _hoops_IRS '_hoops_AISIR' _hoops_HHIS (_hoops_CACH
		 * _hoops_AIHSS)
		 */

		/* _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_CSICP _hoops_RGR _hoops_RPHR _hoops_GPP _hoops_RH _hoops_RIPS _hoops_IIGR _hoops_RH _hoops_HIGR,
		 * _hoops_SCH'_hoops_GRI _hoops_GPRS _hoops_SAHR _hoops_IS _hoops_PHHR _hoops_IAISR _hoops_PPR _hoops_AA _hoops_SCH. _hoops_HHPC, _hoops_PSCPR _hoops_SCH
		 * _hoops_IS _hoops_HGCR _hoops_RH _hoops_PIHSS _hoops_CPCP _hoops_RPHR.
		 */
		if (BIT(dc->flags, _hoops_RASS)) {
			_hoops_RGHPP alter *	_hoops_SGCCA;

			if (BIT (nr->_hoops_RCSHR, _hoops_GAHPP))
				_hoops_SGCCA = &dc->_hoops_HRHPP[_hoops_RAHPP];
			else
				_hoops_SGCCA = &dc->_hoops_HRHPP[_hoops_IRHPP];

			/* (_hoops_RH _hoops_HIIC _hoops_HRGR _hoops_ICIC) */
			if (ANYBIT (nr->current, _hoops_CSGGR|_hoops_CRSI) ||
				_hoops_SGCCA->_hoops_ASRGR == (_hoops_HSPPP alter * alter *)&_hoops_SGCCA->list)
				return true;
			else
				HD_Defer_Tree (nr, _hoops_SRCP, path);
		}
		else
			return true;
	}

	/* _hoops_ASSS _hoops_GRAA-_hoops_CCSHP -> _hoops_ACIPR _hoops_PAR _hoops_SHPP _hoops_CCSHP
	 * _hoops_HIH _hoops_PSCPR _hoops_CPS _hoops_SHS.
	 */
	else if (ANYBIT (_hoops_HGGRS, _hoops_RSSHP | _hoops_CISHP)) {
		if (!BIT (nr->current, _hoops_CSGGR)) {
			HD_Prepare_Soft_Z_Buffered_Tree (nr, _hoops_SRCP, path);
			return true;
		}
		else if (BIT(dc->flags, _hoops_RASS)) {
			HD_Defer_Tree (nr, _hoops_SRCP, path);
		}
	}
	else if (BIT (_hoops_HGGRS, _hoops_GSSHP)) {
		if (!BIT (nr->current, _hoops_CSGGR)) {
			_hoops_PGPSS (nr, _hoops_SRCP, path);
			return true;
		}
		else if (BIT(dc->flags, _hoops_RASS)) {
			HD_Defer_Tree (nr, _hoops_SRCP, path);
		}
	}
	/* _hoops_IIPGR _hoops_PIHA _hoops_RCPS _hoops_ARPP _hoops_IHSP */
	// _hoops_HIH _hoops_RAS _hoops_AHCR-_hoops_RHGPR _hoops_IH _hoops_IAGIP
	else if (BIT (_hoops_HGGRS, _hoops_CRSI)) {
		if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_RIGSA)) {
			/* _hoops_HIHSS-_hoops_ICIC _hoops_CIPSR */
			_hoops_PGRCA(_hoops_SRCP)->_hoops_PHSI &= ~_hoops_RIGSA;
			_hoops_PGRCA(_hoops_SRCP)->_hoops_PHSI |= _hoops_GIGSA;
		}
		HD_Prepare_Overlay_Tree (nr, _hoops_SRCP);
		return true;
	}

	/* _hoops_GIGHR: _hoops_SR _hoops_HHGC _hoops_GII _hoops_RPPS _hoops_IS _hoops_SHH _hoops_CHCC _hoops_ARPP _hoops_ICRP _hoops_CCSHP
	 * _hoops_AARAR, _hoops_HIH _hoops_RAS _hoops_RH _hoops_ICCGR _hoops_SSH _hoops_SRHR (_hoops_RPP _hoops_GII)
	 */
	else if (BIT (_hoops_HGGRS, _hoops_PRHIP)) {
		_hoops_HCSIR const	*	_hoops_ICSIR = null;

		nr->_hoops_RCSHR &= ~_hoops_PRHIP;

		/* _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_IPSP _hoops_RPPS _hoops_CAPGR, _hoops_ARP _hoops_GH _hoops_RH _hoops_HCHSR _hoops_SRHR
		 * _hoops_HA _hoops_CR _hoops_SR _hoops_HS _hoops_PSP _hoops_RII _hoops_PPRRR _hoops_IS _hoops_IRHH _hoops_RCRR _hoops_SCH _hoops_HRGR _hoops_HRPP
		 * _hoops_IS _hoops_HGRAI _hoops_HISI _hoops_RH _hoops_IPSP _hoops_RRRS
		 */
		if (nr->_hoops_SAIR->_hoops_ASSIR != null)
			_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
		if (_hoops_ICSIR != null) {
#ifndef DISABLE_CALLBACKS
			/* _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_IPSP _hoops_RPPS _hoops_CAPGR, _hoops_ARP _hoops_GH _hoops_RH _hoops_HCHSR _hoops_SRHR
			 * _hoops_HA _hoops_CR _hoops_SR _hoops_HS _hoops_PSP _hoops_RII _hoops_PPRRR _hoops_IS _hoops_IRHH _hoops_RCRR _hoops_SCH _hoops_HRGR _hoops_HRPP
			 * _hoops_IS _hoops_HGRAI _hoops_HISI _hoops_RH _hoops_IPSP _hoops_RRRS.	_hoops_IRHH _hoops_RCRR _hoops_ARP _hoops_GH
			 * _hoops_CGGHR _hoops_IH _hoops_CCSI _hoops_HAH
			 */
			if ((_hoops_ICSIR->_hoops_AIIIP[0] == null ||
				 dc->_hoops_APHHP != null) &&	/* _hoops_ICCGR _hoops_ARAR _hoops_RGAR */
				(nr->_hoops_RSGC->action.draw_window != nullroutine ||
				 nr->_hoops_IRR->_hoops_SRI == _hoops_PRAAP)) {
				HD_Setup_Frame_Buffer (nr);
				_hoops_PGRCA(_hoops_ICSIR)->_hoops_GHIAA = true;
			}

			/* _hoops_GACC, _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_IIHSS, _hoops_HHSA _hoops_RPPS _hoops_HA _hoops_IS _hoops_SRCH _hoops_SGSI
			 * _hoops_IIGR _hoops_GII _hoops_GRAA-_hoops_HPRGR _hoops_RPPS _hoops_ASCA (_hoops_HIPH _hoops_IH _hoops_GGHSS)
			 */
			_hoops_PGRCA(_hoops_ICSIR)->_hoops_GRGSP = (nr->_hoops_IRR->_hoops_SRI == _hoops_PRAAP);
#endif
		}

		dc->flags |= _hoops_SHIIP;

		Net_Rendition		_hoops_CIHSS = nr;

		if (BIT(_hoops_CIHSS->transform_rendition->flags, _hoops_PASP)) {
			_hoops_HHCR alter &		_hoops_GGCC = _hoops_CIHSS.Modify()->transform_rendition.Modify();

			_hoops_GGCC->flags &= ~_hoops_PASP;
			_hoops_GGCC->flags |= _hoops_ISH;
		}

		_hoops_RGGSP (_hoops_CIHSS);

		/* _hoops_PPR _hoops_IRHH _hoops_RCRR _hoops_SCH _hoops_AHIRC _hoops_PII "_hoops_RPPS" (_hoops_IGHP _hoops_AHCR) */
		if (_hoops_ICSIR != null) {
			_hoops_PGRCA(_hoops_ICSIR)->_hoops_PSPIP = false;

			if ((_hoops_ICSIR->_hoops_AIIIP[0] == null ||
				 dc->_hoops_APHHP != null) &&	/* _hoops_ICCGR _hoops_ARAR _hoops_RGAR */
				_hoops_ICSIR->depth_buffer != null &&
				(nr->_hoops_RSGC->action.draw_window != nullroutine ||
				 BIT (nr->_hoops_IRR->_hoops_SRI, _hoops_PRAAP)))
				HD_Clear_Software_Z_Buffer (nr);
		}

		return true;
	}
	else if (ANYBIT (_hoops_HGGRS, _hoops_HSSHP)) {
		_hoops_AGPSS (nr, _hoops_SRCP, path);
		return true;
	}
	else if (BIT (_hoops_HGGRS, _hoops_SRGIP)) {
		_hoops_IGPSS (nr, _hoops_SRCP, path);
		return true;
	}

	/* _hoops_GSIA _hoops_IHSP _hoops_GCA _hoops_SHPP _hoops_CCSHP _hoops_AARAR _hoops_GCPAR _hoops_SSH-_hoops_SRHR */
	else if (BIT (_hoops_HGGRS, _hoops_AHIHP)) {
		_hoops_SIASS (nr, _hoops_SRCP, path);
		return true;
	}
	else if (BIT (_hoops_IGGRS, _hoops_AHIHP)) {
		if (BIT(dc->flags, _hoops_RASS) &&
			!BIT (nr->flags, _hoops_PSPSP)) {
			Net_Rendition		_hoops_PPHIS = nr;

			if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH)
				_hoops_PPHIS->_hoops_CPP.Modify()->_hoops_PRH._hoops_HRH = false;

			_hoops_PPHIS->_hoops_SAIR.Modify()->_hoops_ASIHP |= _hoops_ACARP;

			HD_Defer_Tree (_hoops_PPHIS, _hoops_SRCP, path);
		}
		else {
			/* _hoops_SAHR _hoops_HPPR _hoops_CPHP... */
			nr->current &= ~_hoops_AHIHP;
			return true;
		}
	}
	else if (BIT (_hoops_HGGRS, _hoops_CSGGR)) {
		if (!ANYBIT (nr->current, _hoops_IRGIP)) {
			_hoops_AAASS (nr, _hoops_SRCP, path, true);
			return true;
		}
		else if (BIT(dc->flags, _hoops_RASS)) {
			HD_Defer_Tree (nr, _hoops_SRCP, path);
		}
	}
	else if (BIT (_hoops_IGGRS, _hoops_CSGGR)) {
		nr->current &= ~_hoops_CSGGR;

		if (_hoops_PGSC (nr->transform_rendition->_hoops_HGSC)) {
			_hoops_HHCR alter &		_hoops_IHCR = nr->transform_rendition.Modify();

			HD_Set_Z_Buffering_Transform (nr, false, false, 0.0f);

			if (_hoops_IHCR->_hoops_HGSC == _hoops_ACPHP)
				_hoops_IHCR->_hoops_HGSC = _hoops_PCPHP;
			else
				_hoops_IHCR->_hoops_HGSC = _hoops_RCPHP;
		}

		return true;
	}
	else if (ANYBIT (_hoops_IGGRS, _hoops_GSSHP|_hoops_RSSHP)) {
		/* _hoops_PAH'_hoops_RA _hoops_HIISR _hoops_CCA _hoops_SCH _hoops_HA - _hoops_SIHSS (_hoops_PCPA _hoops_HIASR?) */
		if (BIT(dc->flags, _hoops_RASS)) {
			if (ANYBIT (nr->current, _hoops_RSSHP | _hoops_CISHP))
				dc->_hoops_CPGPR |= _hoops_AHPGP;

			HD_Defer_Tree (nr, _hoops_SRCP, path);
		}
		else {
			// _hoops_RPP _hoops_SR _hoops_PAH'_hoops_RA _hoops_PSCPR, _hoops_SAHR _hoops_IIS _hoops_SCH _hoops_RHIR _hoops_PPR _hoops_GRHHR...
			nr->current &= ~(_hoops_GSSHP|_hoops_RSSHP);
			nr->current |= nr->_hoops_RCSHR&(_hoops_GSSHP|_hoops_RSSHP);
			return true;
		}
	}
	else if (BIT (_hoops_HGGRS, _hoops_CSPPP)) {
		_hoops_RAPSS (nr, _hoops_SRCP, node->path);
		return true;
	}

	/* _hoops_GIGHR: _hoops_IPCP "_hoops_GCHSS _hoops_RCA/_hoops_HPPA-_hoops_GHC _hoops_CPIC _hoops_PSAP" _hoops_ARAR
	 *		 _hoops_CHH _hoops_HAR _hoops_SHH _hoops_HAHH _hoops_RPP _hoops_SR _hoops_AAPR _hoops_IS _hoops_SGHHR _hoops_IS
	 *		 _hoops_PGSA-_hoops_PISI-_hoops_CPHRA _hoops_HPGR _hoops_SHSIP _hoops_RCHSS _hoops_IIGR _hoops_RH _hoops_PGSA-_hoops_HHIS
	 *		 _hoops_RRGC. _hoops_RAHP _hoops_SCH _hoops_HRGR, _hoops_RPP _hoops_IIH _hoops_CSAP _hoops_PSP _hoops_CPIC-_hoops_PSAP _hoops_GRH
	 *		 _hoops_AGIR, _hoops_RH _hoops_RRGR _hoops_CHH _hoops_CCASA _hoops_HCR _hoops_RH _hoops_PPRRR _hoops_ISGR _hoops_RH _hoops_ACHSS
	 *		 _hoops_PGSA-_hoops_HHIS _hoops_ARPP _hoops_PCHSS _hoops_CCA _hoops_RH _hoops_PISI _hoops_RCA/
	 *		 _hoops_HPPA-_hoops_IPPA "_hoops_PSAP" _hoops_PGHAA. _hoops_HGI _hoops_CHH _hoops_CCASA _hoops_ISGR _hoops_RH
	 *		 _hoops_PSAAS'_hoops_GRI _hoops_PPR _hoops_RCPGP _hoops_IASAH, _hoops_PGAP _hoops_CHH _hoops_SHH _hoops_IRS _hoops_AHSHS
	 *		 _hoops_HCHSS.
	 *
	 *		 _hoops_PAAS _hoops_RH _hoops_PGSA-_hoops_PISI _hoops_AGRP _hoops_HRGR _hoops_IIAC _hoops_HCR _hoops_RH "_hoops_CPIC
	 *		 _hoops_PSAP" _hoops_ARAR _hoops_GGR _hoops_ARI _hoops_CGH _hoops_SHH _hoops_ISCGC _hoops_AHCA _hoops_PPR _hoops_PAHH
	 *		 _hoops_CPHR _hoops_SGGR _hoops_CCA.
	 */

	/* _hoops_GCHSS _hoops_RCA _hoops_PGI _hoops_CPIC _hoops_GPP _hoops_PAR _hoops_PSAP, _hoops_PSP _hoops_RPSHR _hoops_PCPA
	 * _hoops_SHS _hoops_HRGR _hoops_CPIC _hoops_GPP.
	 */
	else if (BIT (_hoops_HGGRS, _hoops_SARIP)) {
		_hoops_GSASS (nr);
		return true;
	}
	else if (BIT (_hoops_IGGRS, _hoops_SARIP)) {
		/* _hoops_PGSA _hoops_IRS _hoops_GRAA-_hoops_GCAAC _hoops_HHIS */
		/* (_hoops_PHHR _hoops_HII _hoops_GCAAC _hoops_CCH _hoops_IS _hoops_GRAA-_hoops_GCAAC) */
		nr->current &= ~_hoops_SARIP;
		nr->transform_rendition.Modify()->flags &= ~(_hoops_GRHH|_hoops_PRIR);
		return true;
		/* (_hoops_IIS _hoops_PGRS _hoops_CCIH _hoops_GH _hoops_RH _hoops_ICHSS _hoops_CCPAR) */
	}

	/* _hoops_GCHSS _hoops_HPPA _hoops_GHC _hoops_PGI _hoops_CPIC _hoops_GPP _hoops_PAR _hoops_PSAP, _hoops_PSP _hoops_RPSHR _hoops_PCPA
	 * _hoops_SHS _hoops_HRGR _hoops_CPIC _hoops_GPP.
	 */
	else if (BIT (_hoops_HGGRS, _hoops_GPRIP)) {
		_hoops_SCASS (nr);
		return true;
	}
	else if (BIT (_hoops_IGGRS, _hoops_GPRIP)) {
		/* _hoops_PGSA _hoops_IRS _hoops_GRAA-_hoops_HPPA-_hoops_CCHSS _hoops_HHIS */
		/* (_hoops_PHHR _hoops_HII _hoops_HPPA-_hoops_CCHSS _hoops_CCH _hoops_IS _hoops_GRAA-_hoops_HPPA-_hoops_CCHSS) */

		/* _hoops_PAGA: _hoops_SR _hoops_GIASI _hoops_PAH'_hoops_RA _hoops_SCHSS _hoops_SRGGR _hoops_RH _hoops_GIGR
		 *		 _hoops_GSIA-3D _hoops_ACPH _hoops_SICAR. _hoops_HGI _hoops_HRGR _hoops_GSHSS. _hoops_AIHH
		 *		 _hoops_AHSC _hoops_PIP _hoops_ARRS _hoops_AHCA _hoops_GHGA _hoops_GGHAS _hoops_PGSA-_hoops_PISI _hoops_CGSI.
		 */
		nr->current &= ~_hoops_GPRIP;
		nr->transform_rendition.Modify()->flags &= ~(_hoops_CSP|_hoops_RCRIP);

		return true;
	}
	else if (BIT (_hoops_HGGRS, _hoops_HSGGR)) {
		_hoops_IIASS (nr);
		return true;
	}
	else if (BIT (_hoops_HGGRS, _hoops_ISGGR)) {
		_hoops_CIASS (nr);
		return true;
	}
	else if (BIT (_hoops_IGGRS, _hoops_HSGGR)) {
		/* _hoops_SR _hoops_PAH _hoops_SSPC _hoops_RH _hoops_IAGC _hoops_IS _hoops_AGSGR _hoops_PSAP */
		nr->_hoops_RCSHR |= _hoops_HSGGR;
		return true;
	}
	else if (BIT (_hoops_IGGRS, _hoops_ISGGR)) {
		/* _hoops_SR _hoops_PAH _hoops_SSPC _hoops_RH _hoops_IAGC _hoops_IS _hoops_AGSGR _hoops_PSAP */
		nr->_hoops_RCSHR |= _hoops_ISGGR;
		return true;
	}

	/* _hoops_PPSI _hoops_RGR _hoops_GCISR _hoops_CGHI, _hoops_HIS _hoops_GAR _hoops_HAR _hoops_IS _hoops_HHSA _hoops_RSHSS _hoops_HII _hoops_GII
	 * _hoops_APRS _hoops_PIAP. _hoops_HSHCR _hoops_ACPH-_hoops_GASR _hoops_ASHSS _hoops_PIHA _hoops_PSHSS
	 * _hoops_GPP _hoops_ISCPR _hoops_RH '_hoops_GCRAC' _hoops_PIAP!
	 */
	else if (ANYBIT (_hoops_HGGRS, _hoops_HPGSP)) {
		_hoops_CCASS (nr);
		return true;
	}
	else {
		/* _hoops_PAH'_hoops_RA _hoops_HIISR _hoops_CCA _hoops_SCH _hoops_HA - _hoops_SIHSS (_hoops_PCPA _hoops_HIASR?) */
		if (BIT(dc->flags, _hoops_RASS)) {
			if (ANYBIT (nr->current, _hoops_RSSHP | _hoops_CISHP))
				dc->_hoops_CPGPR |= _hoops_AHPGP;

			HD_Defer_Tree (nr, _hoops_SRCP, path);
		}
		else {
			// _hoops_RPP _hoops_SR _hoops_PAH'_hoops_RA _hoops_PSCPR, _hoops_SAHR _hoops_IIS _hoops_SCH _hoops_RHIR _hoops_PPR _hoops_GRHHR...
			nr->current = nr->_hoops_RCSHR;
			return true;
		}
	}

	// _hoops_HSHSS _hoops_PSP _hoops_GCRPA
	return false;
}


GLOBAL_FUNCTION void HD_Standard_Draw_Tree (
	Net_Rendition const &		inr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		_hoops_APPIP) {
	Display_Context alter *		dc = _hoops_PGRCA(inr->_hoops_SRA);
	_hoops_SSAGR(dc);
	_hoops_HICS				path = _hoops_APPIP;
	Tree_Node *					node = dc->_hoops_AHSI;
	Tree_Node *					_hoops_PGPHS = null;
	_hoops_APARR				_hoops_CHAPH = dc->_hoops_IPCI;
	long						_hoops_ISHSS = 0;

	_hoops_SSAGR(node);

	if (_hoops_SRCP != null) {					// _hoops_HHHA _hoops_PAGIR, _hoops_ARP _hoops_IIRAA _hoops_SCGR _hoops_PHSPR
		_hoops_PGPHS = dc->_hoops_AHSI;
		dc->_hoops_AHSI = null;
		node = dc->Push_Tree (inr, _hoops_SRCP, path);	// _hoops_PPR _hoops_ASGGR _hoops_IRS _hoops_CCAH _hoops_GIIS _hoops_IH _hoops_SAHR _hoops_RGR _hoops_HHIS
		_hoops_SSAGR(node);
	}

	_hoops_AGSGA	_hoops_PGSGA (dc);

	do {
		Net_Rendition alter &	nr = node->nr;
		nr._hoops_SSAGR();

		dc->_hoops_RRCIP = _hoops_SRCP = node->segment;
		_hoops_SSAGR(_hoops_SRCP);
		dc->path = path = node->path;
		dc->_hoops_CPGPR = node->_hoops_CPGPR;
		dc->_hoops_PCGPR = node->_hoops_PCGPR;
		dc->_hoops_IPCI = node->_hoops_ACPGR;

		if (!BIT(_hoops_SRCP->_hoops_RCGC, _hoops_AHASA) &&
			!BIT(nr->current, _hoops_CRSI))
			_hoops_PGSGA.restore();

		Bounding const & bounding = _hoops_SRCP->bounding;
		bounding._hoops_SSAGR();

		switch (node->stage) {
			case _hoops_IIGGH: {
				if (BIT(nr->flags, _hoops_AHGIP)) {
					_hoops_ISHHP const &	_hoops_CSHHP = nr->_hoops_ASIR;
					_hoops_PCACA *		action;
					_hoops_PCACA **		_hoops_ASRGR = &_hoops_PGRCA(_hoops_CSHHP->conditions._hoops_ACPGR);

					while ((action = *_hoops_ASRGR) != null) {
						if (HI_Condition_Passed (_hoops_CSHHP->conditions.count, _hoops_CSHHP->conditions._hoops_RCHA, &action->condition)) {
							switch (action->type) {
								case _hoops_CRPCA: {
									node->stage = _hoops_ACHCP;
								} break;

								default:ASSERT(0); break;
							}
						}

						if (!BIT(action->flags, _hoops_PRPCA)) {
							*_hoops_ASRGR = action->next;
							action->next = null;
							HI_Free_Conditional_Actions(action);
						}
						else
							_hoops_ASRGR = &action->next;
					}

					nr->flags &= ~_hoops_AHGIP;

					if (_hoops_GGPGR(nr))
						goto _hoops_CSHSS;		/* _hoops_HRGHP! */

					if (node->stage != _hoops_IIGGH)
						goto _hoops_SPPGR;
				}

				++node->stage;
			}	_hoops_HHHI;

			case _hoops_CIGGH: {
				_hoops_HIGGH *		filter = dc->_hoops_ARAGH;

				if (filter != null) do {
					if (!filter->_hoops_PPCRR (nr, _hoops_SRCP, path)) {
						node->stage = _hoops_RSGGH;
						goto _hoops_SPPGR;
					}
				} while ((filter = filter->prev) != null);
				++node->stage;
			}	_hoops_HHHI;

			case _hoops_SIGGH: {
				_hoops_HIHCP *		ps;

				while ((ps = node->_hoops_HARGH) != null) {
					if (!ps->_hoops_SIHCP (nr))
						goto _hoops_SPPGR;

					node->_hoops_HARGH = ps->prev;
					delete ps;
				}
				++node->stage;
			}	_hoops_HHHI;

			case _hoops_GCGGH: {
				_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
				_hoops_IHCR._hoops_SSAGR();

				if (!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_ASPCR) &&
					!BIT (nr->_hoops_RCSHR, _hoops_GAHPP) &&
					_hoops_SRCP->_hoops_IGCCA == 0 &&
					!dc->_hoops_APHHP &&
					!BIT(dc->flags, _hoops_GAAGH) &&
					!ANYBIT (nr->current,
							 _hoops_CSGGR|_hoops_AHIHP|_hoops_GPRIP|_hoops_HSGGR|_hoops_ISGGR) &&
					!ANYBIT (nr->_hoops_RCSHR,
							 _hoops_AHIHP|_hoops_GPRIP|_hoops_HSGGR|_hoops_ISGGR) &&
					!BIT (_hoops_IHCR->flags,
						  _hoops_GSIHP) &&
#ifndef _hoops_IRSSH
					nr->_hoops_IRR->_hoops_SRI != _hoops_GAI &&
#endif
					Abs (_hoops_IHCR->_hoops_SPH->_hoops_IIPCR.z) > 0.999f &&
					(_hoops_IHCR->_hoops_SPH->projection != _hoops_GHH ||
					 _hoops_IHCR->_hoops_SPH->target.z == 0.0f)  &&
					 !BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_CRAAP)) {
					/*
					 * _hoops_GPGP _hoops_RH _hoops_PGRRR _hoops_SGS _hoops_RH _hoops_RGR _hoops_HRGR _hoops_RH _hoops_RGAR _hoops_RPSI _hoops_IIGR _hoops_RH _hoops_PCIRA (_hoops_RIRP _hoops_PAGIR)
					 * _hoops_PPR _hoops_SR _hoops_CHR _hoops_SIGSP _hoops_IS 2D _hoops_CCA _hoops_PSP _hoops_RII _hoops_AIRC _hoops_HHACR,
					 * _hoops_HHIGR'_hoops_GRI _hoops_SSRR _hoops_SGS _hoops_RH _hoops_PCIRA'_hoops_GRI _hoops_SCII _hoops_GRS _hoops_PSP _hoops_RPIP _hoops_SHH _hoops_PSHS _hoops_ARI.
					 * _hoops_SSHSS, _hoops_RGR _hoops_SCIPA _hoops_ISPR.
					 */

					nr.Modify();
					nr->_hoops_RCSHR |= _hoops_GAHPP;
				}

				if (nr->current != nr->_hoops_RCSHR) {
					if (_hoops_PHHSS(nr))
						continue;

					// _hoops_PIHA _hoops_HS _hoops_CPHR _hoops_IRS _hoops_GGISS (_hoops_HAR _hoops_IRS _hoops_SAS _hoops_GAR _hoops_ICRP _hoops_ARAR) _hoops_HIS _hoops_GGAS _hoops_PPR _hoops_HPPR _hoops_GICS
					_hoops_HIHCP *		_hoops_PPRGH;

					while ((_hoops_PPRGH = node->_hoops_HPAGR) != null) {
						if (!_hoops_PPRGH->_hoops_SIHCP (nr))
							goto _hoops_SPPGR;

						node->_hoops_HPAGR = _hoops_PPRGH->prev;
						delete _hoops_PPRGH;
					}

					dc->Pop_Tree ();
					continue;
				}

				_hoops_ISHSS++;

				++node->stage;
			}	_hoops_HHHI;

			case _hoops_RCGGH: {
				ASSERT(_hoops_SRCP);
				_hoops_SSAGR(_hoops_SRCP);
				bounding._hoops_SSAGR();

#ifndef DISABLE_CALLBACKS
				if (BIT(dc->flags, _hoops_HHICP)) {
					dc->flags &= ~_hoops_HHICP;
				}
				else if (!BIT(dc->flags, _hoops_IRSI)) {
					_hoops_PSIHP const &	_hoops_HSIHP = nr->_hoops_RSGC;

					if (_hoops_HSIHP->action.draw_segment_tree != nullroutine || _hoops_HSIHP->action.draw_segment != nullroutine) {
						Segment_Info alter *		si;

						HD_Handle_FBI_Pending_Window (nr);

						ZALLOC (si, Segment_Info);
						si->segment = _hoops_SRCP;
						si->path = node->path;
						si->next = _hoops_PGRCA(dc->_hoops_CHICP);
						dc->_hoops_CHICP = si;
						dc->flags |= _hoops_HHICP;

						_hoops_SGIGH (nr, si);

						if (dc->_hoops_CHICP != si) {
							do {
								Segment_Info const	*victim;
								if ((victim = dc->_hoops_CHICP) == null) {
									HE_ERROR (HEC_SEGMENT, HES_RENDITION_FREED, "Too many Renditions freed during a segment callback.");
									return;
								}
								dc->_hoops_CHICP = victim->next;
								victim->path.release();
								FREE (victim, Segment_Info);
							} _hoops_RGGA (dc->_hoops_CHICP == si);
							HE_ERROR (HEC_SEGMENT, HES_RENDITION_NOT_FREED, "New Renditions during a segment callback were not freed.");
						}

						dc->_hoops_CHICP = si->next;
						si->path.release();
						FREE (si, Segment_Info);
						dc->flags &= ~_hoops_HHICP;

						node->stage = _hoops_ACHCP;	// _hoops_GII _hoops_CIPGR _hoops_CHH _hoops_HS _hoops_RPII _hoops_CPHR _hoops_GGR _hoops_RH _hoops_PGHGR _hoops_CPSRR
						continue;
					}
				}
#endif

				if (BIT(_hoops_SRCP->_hoops_PHSI, _hoops_GIPSA)) {
					node->flags |= _hoops_IGRGH;

					if (dc->_hoops_AHSI->next == null ||
						!BIT(dc->_hoops_AHSI->next->flags, _hoops_IGRGH))
						node->flags |= _hoops_HGRGH;
				}


				bool	_hoops_RGISS = BIT (dc->_hoops_CPGPR, _hoops_ISCCA) &&
										BIT(nr->flags, _hoops_IPSHP);

				bool	_hoops_CGHSS = true;

				if (BIT (nr->current, _hoops_SRGIP) && //_hoops_CSPH->_hoops_SCHSP != _hoops_IRAP &&			/* _hoops_SCHSP _hoops_PHSPR _hoops_CISI */
					BIT (nr->transform_rendition->_hoops_APH, _hoops_SPIRP)) {	/* _hoops_PPR _hoops_SR _hoops_CHR _hoops_GPIHR _hoops_GGR _hoops_SCH */

					if (_hoops_IGHSS(nr, _hoops_CGHSS))
						continue;
				}

				if (!ANYBIT(dc->flags, _hoops_GPHHP | _hoops_GIHCP |
										_hoops_CRAGH | _hoops_CHSHP |
										_hoops_CSHSR | _hoops_IRSI) &&
					BIT(dc->flags, _hoops_RASS) &&
					BIT(nr->flags, _hoops_RRGIP) &&
					(!BIT(nr->flags, _hoops_SISHP)||
					 !ANYBIT(nr->current, _hoops_CISHP | _hoops_RSSHP)) &&
					!BIT(nr->current, _hoops_CRSI) &&
					!BIT(_hoops_SRCP->_hoops_RCGC, _hoops_AHASA)) {

					Net_Rendition					_hoops_CRAI = nr.Copy();
					_hoops_GRGH alter &			_hoops_APIHP = _hoops_CRAI->_hoops_IRR.Modify();
					_hoops_CGRA alter &		_hoops_GCRCS = _hoops_CRAI->_hoops_SAIR.Modify();

					int	_hoops_RRCRP = _hoops_APIHP->_hoops_RRCRP;

					if (_hoops_APIHP->_hoops_ARCRP > 0.0)
						_hoops_RRCRP = (int)((float)_hoops_RRCRP * _hoops_APIHP->_hoops_ARCRP);

					_hoops_CRAI->flags &= ~_hoops_RRGIP;
					_hoops_APIHP->_hoops_RRCRP = 0;
					_hoops_GCRCS->_hoops_ASIHP |= _hoops_ACARP;

					HD_Defer_Tree_Batch (_hoops_CRAI, _hoops_SRCP, node->path, 0, null, _hoops_RRCRP);

					node->stage = _hoops_CCGGH;
					continue;
				}


				{
					_hoops_HHCR const &		_hoops_IHCR = nr->transform_rendition;
					_hoops_IHCR._hoops_SSAGR();

					if (!_hoops_RGISS &&
						!BIT(_hoops_IHCR->flags, _hoops_CAHPP) &&
						!ANYBIT (_hoops_SRCP->_hoops_RCGC, _hoops_PSPCR | T_WINDOWS | _hoops_AHASA) &&
						(_hoops_CGHSS || ANYBIT (_hoops_IHCR->_hoops_APH, Heur_Culling_EXTENT|_hoops_GHIRP|_hoops_RIHS)) &&
						(ANYBIT (_hoops_IHCR->_hoops_APH, Heur_Culling_EXTENT|_hoops_GHIRP|_hoops_RIHS) ||
						 BIT (_hoops_IHCR->_hoops_APH, Heur_Culling_VIEW_FRUSTUM) && !BIT (_hoops_IHCR->flags, _hoops_AIHS)) &&
						 !bounding._hoops_HICAR() && bounding != node->_hoops_IRRGH) {

						if (BIT (bounding->flags, _hoops_AAPGP))
							HI_Refresh_Segment_Bounding (_hoops_PGRCA(_hoops_SRCP));

						if (BIT (dc->_hoops_CPGPR, _hoops_RSCCA)) {
							_hoops_CPPSS(nr, _hoops_SRCP, path);
							_hoops_PGRCA(_hoops_SRCP)->_hoops_CPGPR |= _hoops_HIPGP;
						}

						if (!bounding._hoops_HICAR() &&
							_hoops_RRHSS(nr))
							continue;
					}
					else {
						if (BIT(_hoops_IHCR->flags, _hoops_CAHPP) &&
							!ANYBIT(_hoops_IHCR->flags, _hoops_CHHS|_hoops_APGSP)) {
							nr.Modify()->transform_rendition.Modify()->flags &= ~_hoops_CAHPP;
						}
					}
				}

				if (ALLBITS (nr->transform_rendition->_hoops_SSPPP, _hoops_GRGIP)) {
					HD_Ordered_Segment (nr, _hoops_SRCP);
					node->stage = _hoops_CCGGH;
					continue;
				}

				node->geometry = _hoops_SRCP->geometry;
				node->_hoops_SSGPR = _hoops_SRCP->_hoops_RGRPR;

				if (dc->_hoops_HRHPP[_hoops_SRHPP].list != null) {
					_hoops_HSPPP const *	_hoops_ISPPP = dc->_hoops_HRHPP[_hoops_SRHPP].list;

					if (_hoops_ISPPP->_hoops_CPCR != null && _hoops_ISPPP->_hoops_CPCR->geometry != null) {
						// _hoops_CRARH _hoops_GGR _hoops_CPAP, _hoops_ARP _hoops_GH _hoops_SSPP
						node->_hoops_SSGS = nr;
						node->_hoops_RARGH = node->geometry = _hoops_ISPPP->_hoops_CPCR->geometry;
						node->single = true;
						node->_hoops_SSGPR = null;
						node->flags |= _hoops_PSGGH;
						node->_hoops_RGHGR = dc->_hoops_IPCI->mask;
					}
				}


				// _hoops_ASAC _hoops_IPP
				if (!ANYBIT(dc->flags, _hoops_GPHHP|_hoops_GIHCP|_hoops_CHSHP|_hoops_IRSI)) {
					_hoops_SPAGR						_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
#if _hoops_CGASS
					// _hoops_SHR _hoops_IRCC _hoops_IS _hoops_GRHP _hoops_AARI _hoops_IRS _hoops_PSIGA _hoops_IPP
					_hoops_AHAGR *				_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, node->path);

					_hoops_CSC->_hoops_APHGA = nr;
#else				// _hoops_RHGS _hoops_RRGR _hoops_RGAR _hoops_GCSS _hoops_RPP _hoops_HRGR _hoops_PPRIP _hoops_PII _hoops_SR _hoops_SIGR _hoops_SCH _hoops_IH _hoops_CIPH _hoops_PII _hoops_IASI _hoops_AHPIP
					_hoops_AHAGR *				_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, node->path, false);
					_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;

					/* _hoops_GAAP _hoops_PCCP _hoops_RHGS _hoops_IPP _hoops_IS _hoops_RSRHR _hoops_SGGR */
					if (_hoops_CSC != null)
						_hoops_CSC->_hoops_APHGA = null;

					/* _hoops_GAAP _hoops_ASAC _hoops_RH _hoops_SCGR _hoops_HGIIP */
					if (BIT (_hoops_IHCR->heuristics, _hoops_PRIRP) ||
						ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GISIR|_hoops_HCHGP|_hoops_SHSIR) ||
						_hoops_CSC && (_hoops_CSC->_hoops_PSSIR() != null || _hoops_CSC->_hoops_IGSGP() != null)) {
						/* _hoops_SR _hoops_CGH _hoops_CRCC _hoops_CIAA _hoops_RGR _hoops_SPR! */
						if (_hoops_CSC == null)
							_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, node->path);
						_hoops_CSC->_hoops_APHGA = nr;
					}
#endif
				}



				if (BIT (nr->transform_rendition->heuristics, _hoops_GPIRP) &&
					!BIT(_hoops_SRCP->_hoops_RRHH, _hoops_HIRIR) &&
					(ANYBIT(_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, nr->_hoops_RGP) || BIT(_hoops_SRCP->_hoops_RCGC, _hoops_APHGP)) &&
					!ANYBIT(dc->flags, _hoops_GPHHP|_hoops_RGSGA) &&
					(BIT(dc->flags, _hoops_RCHCP) || dc->_hoops_SHCI() == _hoops_GICI) &&
					(_hoops_SRCP->_hoops_RGRPR != null ||
					 _hoops_SRCP->geometry != null && nr->_hoops_IRR->_hoops_IRCRP == _hoops_HRCRP) &&
					(_hoops_SRCP->_hoops_RGRPR == null || _hoops_HGHSS(_hoops_SRCP)) &&
					nr->_hoops_RSGC->action.draw_segment_tree == nullroutine &&
					nr->_hoops_RSGC->action.draw_segment == nullroutine) {
					_hoops_SPAGR				_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
					_hoops_AHAGR *		_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP);
					_hoops_CRCP const *		_hoops_AGISS;

					if (BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_SSCCA)) {
						HI_Clean_Static_Tree(nr->_hoops_SRA->_hoops_RIGC, _hoops_SRCP);
						_hoops_PGRCA(_hoops_SRCP)->_hoops_CPGPR &= ~_hoops_SSCCA;
						nr.Modify()->flags |= _hoops_HSPSP;

						if (nr->_hoops_IRR->_hoops_GAHA == Display_List_SEGMENT)
							nr->_hoops_IRR.Modify()->_hoops_GAHA = Display_List_NONE;
					}
					else if (!BIT (nr->flags, _hoops_HSPSP)) {
						_hoops_PGRPR *		st = _hoops_CSC->_hoops_CHICA();

						if (st != null &&
							BIT(nr->flags, _hoops_HRSHP) &&
							!BIT(st->_hoops_RRHH, _hoops_PSIGP)) {
							//_hoops_AGHR(0); //_hoops_RHAP _hoops_RGR _hoops_SGIPR _hoops_IHPS
							HI_Clean_Static_Tree(nr->_hoops_SRA->_hoops_RIGC, _hoops_SRCP);
							st = null;
						}

						if (st == null) {
							_hoops_RCCA(_hoops_SPRGH) += HI_Make_Static_Tree (nr, _hoops_SRCP);
							st = _hoops_CSC->_hoops_CHICA();
							_hoops_RCCA(_hoops_SPRGH) += _hoops_CPPSS (nr, _hoops_PGRCA(st->_hoops_IGRPR), path);

							node->_hoops_CPGPR |= _hoops_ISCCA;

							HI_Invalidate_Segment_Display_Lists (dc->_hoops_RIGC, _hoops_SRCP, -2, null, 0);
							/*_hoops_PGISS ("_hoops_SPIP\_hoops_ACHP");*/
						}

						_hoops_AGISS = st->_hoops_IGRPR;

						node->path._hoops_IACHA (st, dc);

						node->geometry = _hoops_AGISS->geometry;
						node->_hoops_SSGPR = _hoops_AGISS->_hoops_RGRPR;

						if (nr->_hoops_IRR->_hoops_IRCRP == _hoops_HRCRP &&
							nr->_hoops_IRR->_hoops_PCHS == Heur_MAX_EXTENT_MODE_DEFER &&
							nr->_hoops_IRR->_hoops_GAHA != Display_List_NONE) {

							if (nr->_hoops_IRR->_hoops_SHHS != _hoops_AIIRP)
								nr.Modify()->_hoops_IRR.Modify()->_hoops_SHHS = _hoops_AIIRP;
						}
					}
				}


				/* _hoops_RCAR & _hoops_AACC _hoops_CPAP _hoops_IRSPR _hoops_RHAP _hoops_HAR _hoops_GARIR _hoops_GPP _hoops_RH _hoops_RIHRR _hoops_CPAP, _hoops_HIS _hoops_SR _hoops_PAH _hoops_HIISR _hoops_CCA _hoops_SCH _hoops_SRS */
				/* _hoops_PCSA _hoops_RPP _hoops_SR _hoops_CHR _hoops_AGIA _hoops_IS _hoops_AA "_hoops_CAGH _hoops_HHIS" _hoops_ARI,
				 * _hoops_PPR _hoops_RPP _hoops_HIS, _hoops_RIP _hoops_CHAPA _hoops_IS _hoops_HSGR _hoops_PHSPR.
				 * _hoops_CRICR _hoops_IH _hoops_RSPH _hoops_RCAR
				 */

				if (!BIT(dc->flags, _hoops_IRSI) &&
					BIT(nr->flags, _hoops_CPSHP))
					node->flags |= _hoops_CSGGH;

				if (ANYBIT(dc->flags, _hoops_RCHCP|_hoops_SAAGH) &&
					!BIT(dc->flags, _hoops_CHSHP) &&
					BIT(nr->flags, _hoops_SPSHP) &&
					!BIT(nr->current, _hoops_CRSI))
					node->flags |= _hoops_RGRGH;

				if (ALLBITS(dc->flags, _hoops_SRAGH|_hoops_RCHCP) &&
					BIT(nr->flags, _hoops_AHSHP) &&
					!BIT(nr->current, _hoops_RSSHP) &&
					nr->_hoops_IHA->_hoops_AGP != null)
					node->flags |= _hoops_SSGGH;

				if ((BIT(dc->flags, _hoops_RCHCP) || dc->_hoops_SHCI() == _hoops_GICI) &&
					BIT(nr->flags, _hoops_HHSHP))
					node->flags |= _hoops_GGRGH;


				if (ANYBIT (node->flags, _hoops_CSGGH|_hoops_RGRGH|_hoops_GGRGH)) {
					_hoops_GCIR	 alter &		_hoops_RCIR = nr.Modify()->_hoops_CPP.Modify();

#ifndef DISABLE_CUT_GEOMETRY
					if (BIT (node->flags, _hoops_CSGGH)) {
						node->_hoops_PARGH = dc->_hoops_CRIGA;
						dc->_hoops_CRIGA = null;

						_hoops_RCIR->_hoops_PRIGA.level = _hoops_CSSRP;
						nr->flags = _hoops_IPSHP | (nr->flags & ~_hoops_CPSHP);
					}
#endif
#ifndef DISABLE_SIMPLE_SHADOW
					/* _hoops_ACHSS (_hoops_PAR _hoops_SRS) _hoops_RCAR _hoops_GGR _hoops_IRS _hoops_RPPS _hoops_ARH _hoops_RH _hoops_GSISC _hoops_SAAA */
					if (BIT (node->flags, _hoops_RGRGH)) {
						_hoops_SPAGR				_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
						_hoops_AHAGR *		_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, node->path);
						_hoops_CPSS *		_hoops_SPSS = _hoops_CSC->_hoops_CSCGP();

						if (_hoops_SPSS == null) {
							ZALLOC (_hoops_SPSS, _hoops_CPSS);
							_hoops_CSC->_hoops_ISCGP (_hoops_SPSS);
						}

						if (BIT(nr->flags, _hoops_GHSHP) &&
							!BIT (nr->current, _hoops_RPCIP) &&
							BIT (dc->_hoops_CPGPR, _hoops_ICHPA) &&
							ANYBIT (nr->_hoops_IRR->_hoops_SRI, ~_hoops_PRAAP) &&
							BIT (_hoops_SRCP->_hoops_RCGC, T_FACES) &&
							(BIT (nr->_hoops_RGP, T_FACES) ||
							 BIT (_hoops_SRCP->_hoops_RCGC, _hoops_APHGP) ||
							 dc->_hoops_SHCI() == _hoops_GAIIP))
							node->flags |= _hoops_AGRGH;

						if (!BIT (node->flags, _hoops_AGRGH)) {
							/* _hoops_HGGC _hoops_RRP _hoops_IS _hoops_HRCI _hoops_GII _hoops_APRS _hoops_RCAR */
							if (BIT (dc->_hoops_CPGPR, _hoops_HISSR))
								_hoops_SPSS->valid = false;
							else if (BIT (dc->_hoops_CPGPR, _hoops_PSCCA))
								_hoops_SPSS->_hoops_RIHSP = false;
						}
						else if (ANYBIT(dc->flags, _hoops_RCHCP|_hoops_SAAGH) &&
								 nr->_hoops_SAIR->shadow_resolution == 0.0f) {

							if (BIT (dc->_hoops_CPGPR, _hoops_HISSR))
								_hoops_SPSS->valid = false;
							else if (BIT (dc->_hoops_CPGPR, _hoops_PSCCA))
								_hoops_SPSS->_hoops_RIHSP = false;

							if (!_hoops_SPSS->valid ||
								BIT (dc->_hoops_CPGPR, _hoops_PSCCA) &&
								BIT (nr->transform_rendition->flags, _hoops_CSP))
								HD_Compute_Shadow_Resolution (nr, _hoops_SRCP, node->path);

							nr->_hoops_SAIR->shadow_resolution = _hoops_SPSS->_hoops_AIHSP;
						}
					}
#endif
					nr->flags &= ~_hoops_SPSHP;
					nr->flags &= ~_hoops_HHSHP;
				}




				if (!BIT(dc->flags, _hoops_IRSI) && _hoops_SRCP->_hoops_CSC != null) {
					_hoops_SPAGR				_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
					_hoops_AHAGR *		_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, node->path);

					if (_hoops_CSC != null) {
#ifndef DISABLE_CUT_GEOMETRY
						if (!ANYBIT(dc->flags, _hoops_GPHHP|_hoops_GIHCP|_hoops_CHSHP)) {
							if (BIT (dc->_hoops_CPGPR, _hoops_ISCCA)) {
								_hoops_PHSGA *	_hoops_APHSS;

								if ((_hoops_APHSS = _hoops_CSC->_hoops_GHSGA()) != null) {
									_hoops_RRSGA *		_hoops_PRIGA;

									while ((_hoops_PRIGA = _hoops_APHSS->_hoops_RHSGA) != null) {
										Geometry *		victim;

										while ((victim = _hoops_PRIGA->geometry) != null) {
											_hoops_PRIGA->geometry = victim->next;
											_hoops_CIGPR (dc->_hoops_RIGC,victim);
											_hoops_HPRH (victim);
										}

										_hoops_APHSS->_hoops_RHSGA = _hoops_PRIGA->next;
										FREE (_hoops_PRIGA, _hoops_RRSGA);
									}

									_hoops_APHSS->valid = false;
								}
							}
						}
#endif
#ifndef DISABLE_SIMPLE_SHADOW
						if (BIT (dc->_hoops_CPGPR, _hoops_HISSR) ||
							BIT (dc->_hoops_CPGPR, _hoops_PSCCA) &&
								BIT (nr->transform_rendition->flags, _hoops_CSP) ||
							BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_HSCCA)) {

							_hoops_CPSS *		_hoops_SPSS;

							if (ANYBIT(dc->flags, _hoops_RCHCP|_hoops_SAAGH) &&
								(_hoops_SPSS = _hoops_CSC->_hoops_CSCGP()) != null) {
								_hoops_SPSS->valid = false;
							}
						}
#endif
					}
				}

				node->_hoops_SSGS = nr;
				if (!BIT(dc->flags, _hoops_IRSI) && _hoops_SRCP->_hoops_SSRIR() != null) {
					_hoops_GRA const &		_hoops_RRA = nr->_hoops_ARA;
					int								_hoops_RCSRP = _hoops_RRA->_hoops_PRSI._hoops_RCSRP;
					int								i, _hoops_IISRP;
					float							_hoops_HGISS;

					_hoops_IISRP = _hoops_RRA->_hoops_PRSI._hoops_IISRP;
					if (_hoops_IISRP < 0 || !BIT(_hoops_RRA->_hoops_PRSI.options, _hoops_HASRP)) {
						if (_hoops_SRCP->bounding != null &&
							!_hoops_SRCP->bounding._hoops_HICAR() &&
							BIT (_hoops_RRA->_hoops_PRSI.options, _hoops_RASRP)) {
							_hoops_HGISS = _hoops_SAPSS(nr, _hoops_SRCP->bounding);
							for (i = 0; i < _hoops_IGAIR; i++) {
								if (_hoops_HGISS > _hoops_RRA->_hoops_PRSI._hoops_AISRP[i]) {
									_hoops_IISRP = i;
									break;
								}
							}
						}
					}
					if (_hoops_IISRP > 0) {
						_hoops_PGAIR *		_hoops_HGAIR = _hoops_SRCP->_hoops_SSRIR();

						node->geometry = _hoops_HGAIR->data[_hoops_IISRP - 1];
						if (_hoops_RCSRP == _hoops_SPSRP || node->geometry != null) {
							node->_hoops_SSGPR = null;
							_hoops_CAPSS (node->_hoops_SSGS);
						}
						else if (node->geometry == null) {
							/* _hoops_GIPHR _hoops_IH _hoops_IRS _hoops_IIPGA */
							i = _hoops_IISRP - 1;
							while (i >= 0 && node->geometry == null) {
								node->geometry = _hoops_HGAIR->data[i];
								i--;
							}
							if (node->geometry != null) {
								node->_hoops_SSGPR = null;
								_hoops_CAPSS (node->_hoops_SSGS);
							}
							else {
								/* _hoops_PHHR _hoops_ISSC _hoops_IS _hoops_PCPA _hoops_SR _hoops_AAPR _hoops_GHGA _hoops_ARPP */
								node->geometry = _hoops_SRCP->geometry;
							}
						}
					}
					/* _hoops_SHS _hoops_AA _hoops_ISAP _hoops_PPR _hoops_HSSC _hoops_ISHP _hoops_IS _hoops_GSSR _hoops_ASCA */
				}


				if (BIT (nr->transform_rendition->_hoops_SSPPP, _hoops_SSASP))
					node->_hoops_SSGPR = null;

				/*** _hoops_CAHP _hoops_GII _hoops_RCAR _hoops_ARCR, _hoops_PGAP _hoops_IRHS _hoops_IS _hoops_IHPS _hoops_ARPP _hoops_RH _hoops_GSSR _hoops_ASCA ***/
				if (BIT (node->flags, _hoops_SSGGH) &&
					!ANYBIT (nr->current, _hoops_SRSI|_hoops_CRSI) &&
					_hoops_SRCP->bounding != null) {
					HI_Find_Segment_Cache (_hoops_SRCP, node->path);

					if (BIT (_hoops_SRCP->bounding->flags, _hoops_AAPGP))
						HI_Refresh_Segment_Bounding (_hoops_PGRCA(_hoops_SRCP));

					if (!BIT (dc->flags, _hoops_CHSI))
						HD_Shadow_Map_Update (nr, _hoops_SRCP, node->path);

					nr.Modify()->flags &= ~_hoops_AHSHP;
				}

 				// _hoops_CCGR _hoops_HCR _hoops_GPAC _hoops_AA _hoops_RGR _hoops_GAR _hoops_IRS _hoops_IGHP _hoops_APHSR, _hoops_AA _hoops_SCH _hoops_ARPP _hoops_RH _hoops_GSSR _hoops_SRGS _hoops_HIS _hoops_SGS _hoops_RH
				// _hoops_HIHSS-_hoops_RRH _hoops_RPPS _hoops_GRS _hoops_HAR _hoops_HAHA _hoops_RH _hoops_HPHR _hoops_CPAP
				if (BIT (node->flags, _hoops_GGRGH) &&
					!ANYBIT(dc->flags, _hoops_GPHHP|_hoops_CHSHP|_hoops_IRSI) &&
					BIT (dc->_hoops_CPGPR, _hoops_ICHPA) &&
					!ANYBIT (nr->current, _hoops_SRSI|_hoops_CRSI)) {
					if (ANYBIT(nr->current, _hoops_CISHP|_hoops_RSSHP))
						HD_Handle_FBI_Pending_Window (node->_hoops_SSGS);

					_hoops_GSPSS (nr, _hoops_SRCP, path);
				}

				++node->stage;
			}	_hoops_HHHI;

			case _hoops_ACGGH: {
				if (!BIT (dc->_hoops_IASS, _hoops_HHIIP) &&
					!ANYBIT(dc->flags, _hoops_RPSRR|_hoops_CHSI) &&
					(//_hoops_CSPH->_hoops_IGISS ||
						(dc->_hoops_CGAP == 0 &&
						 dc->_hoops_CPAGH &&
						 dc->_hoops_CPAGH == _hoops_SRCP &&
						 dc->_hoops_RIGC->_hoops_HCPGR != 0 &&
						 ((node->path == null && dc->_hoops_IPAGH == 0) ||
						  (node->path != null && dc->_hoops_IPAGH == node->path->key)))
					 )
					) {

					_hoops_GSPGR _hoops_APARH = dc->_hoops_RIGC->_hoops_ACHGH-*HOOPS_WORLD->time_stamp;
					_hoops_GSPGR _hoops_SGII = _hoops_IAAA(dc->_hoops_RIGC->_hoops_RHPGI * 0.5, 15.0);

					if (dc->_hoops_PPAGH || _hoops_APARH < _hoops_SGII) {
						dc->_hoops_HPAGH = dc->_hoops_CPAGH;
						HD_Interrupt_Update (dc, false, false);

						_hoops_APSRR(dc, "update_interupted_by_stop_segment","", 0);
						goto _hoops_CSHSS;
					}
					else {
						dc->flags |= _hoops_RPSRR;
						dc->_hoops_APAGH = true;
						dc->_hoops_PPAGH = true;
					}
				}

				node->_hoops_RGHGR = dc->_hoops_IPCI->mask;

				if (BIT(node->flags, _hoops_IGRGH))
					_hoops_CRHSS(nr);

				if (node->geometry != null &&
					BIT (dc->_hoops_IPCI->mask, _hoops_IRGC) &&
					!BIT (nr->current, _hoops_RPCIP) &&
					(ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, node->_hoops_SSGS->_hoops_RGP) ||
					 BIT (_hoops_SRCP->_hoops_RCGC, T_EDGES) && ANYBIT (node->_hoops_SSGS->_hoops_RGP, T_ANY_EDGE) ||
					 BIT (_hoops_SRCP->_hoops_RCGC, _hoops_APHGP)) &&
					 (!BIT(dc->flags, _hoops_SAAGH) ||
					  BIT(dc->flags, _hoops_GPHHP) ||
					  BIT (nr->current, _hoops_CRSI))) {
					_hoops_SRHSS(nr);
				}

				node->_hoops_SRRGH = dc->_hoops_IPCI->mask;

				++node->stage;
			}	_hoops_HHHI;

			case _hoops_PCGGH: {
				if (!BIT(dc->flags, _hoops_IRSI)) {
					_hoops_PSIHP const &	_hoops_HSIHP = nr->_hoops_RSGC;
					if (_hoops_HSIHP->action._hoops_ARSHP != nullroutine) {
						_hoops_RRIGH(nr);
						if (node->stage == _hoops_ACHCP)
							continue;
						// _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_SPR _hoops_SIPPI
						_hoops_PSIHP	_hoops_PHGRI = nr.Modify()->_hoops_RSGC.Modify();
						_hoops_PHGRI->action._hoops_ARSHP = nullroutine;
						_hoops_HSIHP->_hoops_AIACR[_hoops_HPACR] = 0;
					}
				}

				/* _hoops_PGSA _hoops_HHH _hoops_CPAP! (_hoops_CGISS) */
				dc->_hoops_IPCI->mask = node->_hoops_SRRGH;

				if (BIT (node->flags, _hoops_PSGGH)) {
					if (BIT (dc->_hoops_CPGPR, _hoops_ICHPA)) {
						_hoops_APARR alter &	_hoops_RRCI = dc->_hoops_IPCI;

						if (ANYBIT (_hoops_RRCI->mask, _hoops_SICHP)) {
							if (node->_hoops_RARGH->type == _hoops_HCIIR) {
								if (!BIT(dc->flags, _hoops_HSAGR)) {
									_hoops_GACR *dl = (_hoops_GACR *)node->_hoops_RARGH;
									_hoops_GPCIP (node->_hoops_SSGS, dl);
									if (dc->_hoops_SSGC >= 0) {
										ASSERT (nr->_hoops_IRR->_hoops_PCHS == Heur_MAX_EXTENT_MODE_DEFER);
										_hoops_RGHSS (nr, dl, _hoops_SRCP, path);
									}
								}
								node->_hoops_RARGH = null;
							}
							else
								node->_hoops_RARGH = _hoops_RPHPP (node->_hoops_SSGS, node->_hoops_RARGH, _hoops_RRCI->mask, node->single);

							if (node->_hoops_RARGH != null)		// _hoops_AGRRR
								goto _hoops_CSHSS;
						}
					}
					else if (BIT (_hoops_SRCP->_hoops_CPGPR | (_hoops_SRCP->_hoops_SPGPR & dc->_hoops_RIIAP), _hoops_HPPGP)) {
						if (!ANYBIT (nr->current, _hoops_CRSI|_hoops_SRSI))
						   dc->flags |= _hoops_SHIIP;
						_hoops_HRPSS (node->_hoops_SSGS, node->geometry, dc->_hoops_IPCI->mask);
					}

					dc->_hoops_IPCI->mask = node->_hoops_RGHGR;
				}
				++node->stage;
			}	_hoops_HHHI;

			case _hoops_HCGGH: {
				if (BIT (node->flags, _hoops_PSGGH) &&
					BIT (dc->_hoops_CPGPR, _hoops_ICHPA) &&
					ANYBIT (node->flags, _hoops_HSGGH|_hoops_ISGGH)) {

					_hoops_SAHSS(nr);
				}

				if (dc->_hoops_APAGH) {
					dc->flags &= ~_hoops_RPSRR;
					dc->_hoops_APAGH = false;
				}

				// _hoops_CGPR _hoops_SR _hoops_HPIRA _hoops_ASCA _hoops_IRS _hoops_PHHIP _hoops_SCH _hoops_RHCHR _hoops_RH _hoops_SPS _hoops_SSRR _hoops_RRS _hoops_PPSR
				dc->_hoops_GHAGH = _hoops_SRCP;
				if (node->path)
					dc->_hoops_SPAGH = node->path->key;
				else
					dc->_hoops_SPAGH = 0;

				nr._hoops_SSAGR();

				++node->stage;
			}	_hoops_HHHI;

			case _hoops_ICGGH: {
				if (node->_hoops_SSGPR && BIT (dc->_hoops_IPCI->mask, _hoops_HRGC)) {
					_hoops_SSAGR (node->_hoops_SSGPR);

					long				priority = 0L;
					bool				_hoops_SGISS = false;
					_hoops_ACHR			_hoops_CCGPS = nr->_hoops_RGP;

					if (BIT (nr->_hoops_RGP, T_CUT_GEOMETRY)) {
						if (BIT (nr->transform_rendition->flags, _hoops_CSP))
							_hoops_SGISS = true;
						else
							_hoops_CCGPS &= ~T_CUT_GEOMETRY;
					}

					/* _hoops_IHSH _hoops_HPGR _hoops_RH _hoops_CHAPA */
					if (!BIT(dc->flags, _hoops_IRSI) &&
						!BIT (nr->current, _hoops_CSGGR) &&
						BIT(_hoops_SRCP->_hoops_PHSI, _hoops_CCHGP)) {
						node->flags |= _hoops_CGRGH;

						node->_hoops_CARGH = dc->_hoops_RPSS[dc->_hoops_IASS];
						node->_hoops_SARGH = dc->_hoops_HASS[dc->_hoops_IASS];
						node->_hoops_GPRGH = dc->_hoops_SASS[dc->_hoops_IASS];
						dc->_hoops_RPSS[dc->_hoops_IASS] = 0;
						dc->_hoops_HASS[dc->_hoops_IASS] = 0;
						dc->_hoops_SASS[dc->_hoops_IASS] = 0;

						dc->flags |= _hoops_CRAGH;
					}

					do {
						bool	_hoops_GRISS = false;

						_hoops_SSAGR (node->_hoops_SSGPR);
						_hoops_SSAGR (&dc->flags);

						_hoops_HICS		_hoops_HHPIP = node->path;
						Activity			_hoops_APHIP = 0;
						Subsegment const *	_hoops_GIPIA = node->_hoops_SSGPR;

						if (_hoops_GIPIA->type == _hoops_AGRPR) {
							_hoops_PGRPR const *	include = (_hoops_PGRPR const *)_hoops_GIPIA;

							_hoops_SRCP = include->_hoops_IGRPR;
							_hoops_HHPIP._hoops_IACHA (include, dc);

							if (include->condition.count == 0 ||
								HI_Condition_Passed (nr->_hoops_ASIR->conditions.count,
													 nr->_hoops_ASIR->conditions._hoops_RCHA,
													 &include->condition)) {
								_hoops_GRISS = true;

								_hoops_APHIP = include->_hoops_CPGPR |
													 dc->_hoops_RIIAP & include->_hoops_SPGPR &
														 ~(_hoops_ISCCA|_hoops_PISSR);
							}
							else {
#if _hoops_CGASS
								{
									_hoops_SPAGR				_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
									_hoops_AHAGR *		_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, _hoops_HHPIP, false);

									if (_hoops_CSC != null) {
										_hoops_CSC->_hoops_PCGPR |= dc->_hoops_PCGPR;		// _hoops_PCSA _hoops_IH _hoops_SPHR _hoops_CGPR _hoops_SR _hoops_AA _hoops_HGCR _hoops_CHCC
										if (BIT (dc->_hoops_PCGPR, _hoops_HSPGP))
											_hoops_CSC->_hoops_APHGA = null;	// _hoops_CIH _hoops_PCPA _hoops_SR _hoops_PAH _hoops_HA
									}
								}
#endif
								continue; // _hoops_SPS _hoops_HHASA
							}
						}
						else
							_hoops_SRCP = (_hoops_CRCP const *)_hoops_GIPIA;
						_hoops_SSAGR(_hoops_SRCP);

						if (!BIT(dc->flags, _hoops_IRSI) &&
							BIT(node->flags, _hoops_CGRGH) && _hoops_SRCP->priority != priority) {
							_hoops_AHHSS (nr);
							priority = _hoops_SRCP->priority;
						}

						_hoops_APHIP |= _hoops_SRCP->_hoops_CPGPR |
										  dc->_hoops_RIIAP & _hoops_SRCP->_hoops_SPGPR &
											  ~(_hoops_ISCCA|_hoops_PISSR);

						/* _hoops_HRGR _hoops_IIH _hoops_IRS _hoops_SCPC _hoops_IS _hoops_PHHR _hoops_CRGR _hoops_SCH? (_hoops_RHCA _hoops_HRGHR _hoops_HA!) */
						if (!(BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR) &&
							  (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GCHGP) ||
							   (!BIT (_hoops_CCGPS, T_WINDOWS) &&
								!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_HPHGP)))) &&
							/* _hoops_SCH _hoops_ASSP'_hoops_RA _hoops_AHGS _hoops_IS _hoops_SHH _hoops_PCCP _hoops_PSIPR _hoops_RPPS */

							BIT (_hoops_APHIP, _hoops_CHPGP) ||
							/* _hoops_SAHR _hoops_HS _hoops_IS _hoops_IHSH _hoops_PAR ...*/

							(((ANYBIT (dc->_hoops_CPGPR, _hoops_ICHPA|_hoops_CHPGP) ||
							   BIT (_hoops_APHIP, _hoops_IPPGP)) &&
							  (ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, _hoops_CCGPS) ||
							   (BIT (_hoops_SRCP->_hoops_RCGC, T_FACES) && BIT (_hoops_CCGPS, T_CUT_GEOMETRY) &&
								nr->_hoops_IRR->_hoops_GHIHP != 0 &&
								(BIT (nr->current, _hoops_GPRIP) || _hoops_SRCP->_hoops_PAGSA() > 0)) ||
							   BIT (_hoops_SRCP->_hoops_RCGC, T_EDGES) && ANYBIT (_hoops_CCGPS, T_ANY_EDGE) ||
							   BIT (_hoops_SRCP->_hoops_RCGC, _hoops_APHGP) &&
							   (ANYBIT (_hoops_SRCP->_hoops_RCGC, _hoops_AHHGP|_hoops_RHHGP) ||
							    !ALLBITS (nr->_hoops_IRR->locks._hoops_RGP, _hoops_SRCP->_hoops_RCGC & _hoops_IRHGP) ||
								BIT (_hoops_SRCP->_hoops_RCGC, T_EDGES) && !ALLBITS (nr->_hoops_IRR->locks._hoops_RGP, T_ANY_EDGE) ||
							    dc->_hoops_SHCI() > _hoops_RICI &&
									BIT (_hoops_SRCP->_hoops_RCGC, T_FACES) &&
									BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_EDGES)))) ||
							 /* _hoops_GGHP _hoops_SIGC _hoops_CPAP _hoops_IS _hoops_PGSA (_hoops_GAAP) _hoops_PAR */

							 ((ANYBIT (dc->_hoops_CPGPR, _hoops_APPGP|_hoops_PPPGP) ||
							   BIT (_hoops_APHIP, _hoops_IPPGP)) &&
							  (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR) ||
							   BIT (_hoops_SRCP->_hoops_RCGC, T_WINDOWS)) &&
							  (BIT (_hoops_CCGPS, T_WINDOWS) ||
							   BIT (_hoops_SRCP->_hoops_RCGC, _hoops_HPHGP)))
							 /* _hoops_PAR _hoops_GGHP _hoops_PCCP _hoops_RHPA _hoops_RPPS _hoops_IS _hoops_PGSA (_hoops_GAAP) */
							)) {

							Net_Rendition		_hoops_PPHIP = nr;

							if (_hoops_GGPGR(nr))
								goto _hoops_CSHSS;		/* _hoops_HRGHP! */

							_hoops_SSAGR (_hoops_SRCP->_hoops_IPPGR);
							_hoops_SSAGR (_hoops_SRCP->_hoops_CSC);

							//_hoops_PHHIP->_hoops_IASC._hoops_RRISS();

							Activity			_hoops_IPHIP = dc->_hoops_CPGPR;
							dc->_hoops_CPGPR |= _hoops_APHIP & ~_hoops_CHPGP;

							if (_hoops_SRCP->_hoops_IPPGR != null) {
								_hoops_HHRA const *		_hoops_HPHIP = _hoops_PPHIP->transform_rendition->_hoops_SPH;
#if _hoops_CGASS
								Net_Rendition		_hoops_ARISS;
								{
									_hoops_SPAGR				_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
									_hoops_AHAGR *		_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, _hoops_HHPIP, false);

									if (_hoops_CSC != null) {
										_hoops_ARISS = _hoops_CSC->_hoops_APHGA;
										dc->_hoops_PCGPR |= _hoops_CSC->_hoops_PCGPR;
									}
								}

								dc->_hoops_PCGPR |= _hoops_SRCP->_hoops_PCGPR;
								if (_hoops_ARISS == null ||
									BIT (dc->_hoops_PCGPR, _hoops_HSPGP) ||
									dc->_hoops_APHHP != null ||
									BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR))
									HD_Downwind_Rendition (_hoops_PPHIP, _hoops_SRCP->_hoops_IPPGR,
															_hoops_CAHGP, // _hoops_PHHIP->_hoops_SGHGP,
															true);
								else
									HD_Patch_Rendition (_hoops_PPHIP, _hoops_ARISS, _hoops_SRCP, dc->_hoops_PCGPR);
#else
								HD_Downwind_Rendition (_hoops_PPHIP, _hoops_SRCP->_hoops_IPPGR, _hoops_SRCP->_hoops_RCGC, true);
#endif

								if (BIT (_hoops_PPHIP->_hoops_RCSHR, _hoops_CRHPP)) {
									if (!_hoops_SRCP->bounding._hoops_HICAR() &&
										BIT (_hoops_SRCP->bounding->flags, _hoops_AAPGP)) {

										HI_Refresh_Segment_Bounding (_hoops_PGRCA(_hoops_SRCP));
										if (BIT (dc->_hoops_CPGPR, _hoops_RSCCA))
											_hoops_CPPSS(_hoops_PPHIP, _hoops_SRCP, _hoops_HHPIP);
										_hoops_PGRCA(_hoops_SRCP)->_hoops_CPGPR |= _hoops_HIPGP;
									}
								}
								else if (!BIT(dc->flags, _hoops_IRSI) &&
										 (_hoops_PPHIP->transform_rendition->_hoops_SPH != _hoops_HPHIP ||
										  BIT(_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) &&
										 (*_hoops_PPHIP->transform_rendition->_hoops_SPH->_hoops_SIPCR < 0.0f ||
										  *_hoops_PPHIP->transform_rendition->_hoops_SPH->_hoops_SIPCR == 0.0f &&
										  _hoops_GIPHP < 0.0f)) {
									HD_Adjust_WLimit (_hoops_PPHIP, _hoops_SRCP, node->path);
								}
							}

							if (BIT(nr->current, _hoops_CSPPP) &&
								!BIT (_hoops_PPHIP->transform_rendition->heuristics, _hoops_SAIRP))
								_hoops_PPHIP.Modify()->transform_rendition.Modify()->_hoops_SSPPP = _hoops_GRGIP;

							// _hoops_PRISS _hoops_HRGR _hoops_HAR _hoops_HRISS _hoops_CRPGI _hoops_IPIH
							if (BIT(_hoops_PPHIP->_hoops_RGP, T_CUTTING_PLANES) &&
								/* _hoops_PHHIP->_hoops_CPAP != _hoops_IRAP && */
								_hoops_SRCP->_hoops_GACP != null &&
								(_hoops_SRCP->_hoops_GACP->_hoops_AACP (_hoops_IIAGR(_hoops_HGPGR)) != null /*||
								 _hoops_PHHIP->_hoops_IRISS->_hoops_HGCR (_hoops_CRISS) != _hoops_IRAP*/) &&
								BIT(_hoops_PPHIP->_hoops_IRR->_hoops_PPH, _hoops_AARAP) /*&&
								_hoops_PHHIP->_hoops_SRISS() > 0*/)
								HD_Find_Local_Cutting_Planes (_hoops_PPHIP, _hoops_SRCP);

							if (BIT(dc->flags, _hoops_RASS) &&
								BIT (node->_hoops_SSGPR->_hoops_RRHH, _hoops_PASIR))
								  _hoops_PPHIP->_hoops_RCSHR |= _hoops_RRSIP;

							if (BIT(dc->flags, _hoops_CHSHP) &&
								!BIT(nr->flags, _hoops_PHSHP)) {}
#ifndef _hoops_IRSSH
							else if (_hoops_GRISS && dc->_hoops_IPCI->_hoops_PGSSP != nullroutine) {
								(*dc->_hoops_IPCI->_hoops_PGSSP) (_hoops_PPHIP, priority);
								_hoops_AASS (_hoops_PPHIP, _hoops_SRCP, _hoops_HHPIP); /* _hoops_GHHA! */
								(*dc->_hoops_IPCI->_hoops_HGSSP) (_hoops_PPHIP);
							}
#endif
							else if (BIT(node->flags, _hoops_CGRGH) ||
									 ANYBIT(dc->flags, _hoops_IRSI|_hoops_GIHCP)) {
								_hoops_AASS (_hoops_PPHIP, _hoops_SRCP, _hoops_HHPIP); /* _hoops_GHHA! */
							}
							else if (BIT(node->flags, _hoops_IGRGH)) {
								dc->Push_Tree (_hoops_PPHIP, _hoops_SRCP, _hoops_HHPIP, true);
								dc->_hoops_AHSI->_hoops_IRRGH = node->segment->bounding;
								if (BIT(_hoops_SRCP->_hoops_PHSI, _hoops_GIPSA))
									dc->_hoops_PRAGH->flags |= _hoops_IGRGH;
							}
							else if (node->_hoops_SSGPR->next == null &&
									 node->_hoops_HPAGR == null &&
									 dc->_hoops_IPCI->_hoops_SCCSP == HD_Standard_Draw_Tree &&
									 !_hoops_SGISS &&
									 !ANYBIT (node->flags, _hoops_RGRGH|_hoops_GGRGH)) {
								// _hoops_AA "_hoops_RIRP _hoops_PAGIR" -- _hoops_AIIA _hoops_ARRC & _hoops_PASSC _hoops_HPGP _hoops_GAISS _hoops_PGSI
								node->nr = _hoops_PPHIP;
								node->_hoops_IRRGH = node->segment->bounding;
								node->segment = _hoops_SRCP;
								node->path = _hoops_HHPIP;
								node->_hoops_CPGPR = dc->_hoops_CPGPR;
								node->_hoops_PCGPR = dc->_hoops_PCGPR;
								node->stage = 0;
								node->flags = 0;
								node->_hoops_SSGS = null;
								node->geometry = null;
								node->_hoops_SSGPR = null;

								goto _hoops_SPPGR;
							}
							else {
								node->_hoops_SSGPR = node->_hoops_SSGPR->next;	// _hoops_GCHGA _hoops_GPP _hoops_SCGR

								dc->Push_Tree (_hoops_PPHIP, _hoops_SRCP, _hoops_HHPIP);
								dc->_hoops_AHSI->_hoops_IRRGH = node->segment->bounding;

								goto _hoops_SPPGR;
							}

							dc->_hoops_CPGPR = _hoops_IPHIP;
						}
						else {
#if _hoops_CGASS
							{
								_hoops_SPAGR				_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
								_hoops_AHAGR *		_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, _hoops_HHPIP, false);

								if (_hoops_CSC != null) {
									_hoops_CSC->_hoops_PCGPR |= dc->_hoops_PCGPR;		// _hoops_PCSA _hoops_IH _hoops_SPHR _hoops_CGPR _hoops_SR _hoops_AA _hoops_HGCR _hoops_CHCC
									if (BIT (dc->_hoops_PCGPR, _hoops_HSPGP))
										_hoops_CSC->_hoops_APHGA = null;	// _hoops_CIH _hoops_PCPA _hoops_SR _hoops_PAH _hoops_HA
								}
							}
#endif
							if (BIT(_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA) &&
			  					ANYBIT(nr->current, _hoops_RSSHP|_hoops_CISHP)) {
								_hoops_HCSIR alter  *_hoops_ICSIR;

								_hoops_ICSIR = HD_Init_Frame_Buffer_Info (nr, _hoops_SRCP, node->path);
								_hoops_ICSIR->_hoops_GHIAA = true;
							}
						}
					} while ((node->_hoops_SSGPR = node->_hoops_SSGPR->next) != null);

					if (BIT(node->flags, _hoops_CGRGH) && !ANYBIT (dc->_hoops_IASS, _hoops_HHIIP|_hoops_IHPGR)) {
						_hoops_AHHSS (nr);

						dc->_hoops_RPSS[dc->_hoops_IASS] = node->_hoops_CARGH;
						dc->_hoops_HASS[dc->_hoops_IASS] = node->_hoops_SARGH;
						dc->_hoops_SASS[dc->_hoops_IASS] = node->_hoops_GPRGH;

						if (node->_hoops_RPRGH)
							dc->flags |= _hoops_CRAGH;
						else
							dc->flags &= ~_hoops_CRAGH;
					}
				}

				if (BIT(node->flags, _hoops_HGRGH)) {
					if (dc->_hoops_CPHGH())
						goto _hoops_SPPGR;
				}

				/* _hoops_HGCR _hoops_ISSC _hoops_GIGR _hoops_CAGH */
				_hoops_SRCP = node->segment;

				++node->stage;
			}	_hoops_HHHI;

			case _hoops_CCGGH: {
				while (dc->_hoops_GPSIP.list != null) {
					if (_hoops_GGPGR(nr))
						goto _hoops_CSHSS;

					_hoops_HSPPP alter *	list = dc->_hoops_GPSIP.list;
					dc->_hoops_GPSIP.list = 0;
					dc->_hoops_GPSIP._hoops_ASRGR = &dc->_hoops_GPSIP.list;

					while (list) {
						_hoops_HSPPP alter *	_hoops_PASIP = list;
						list = _hoops_PASIP->next;

						Net_Rendition		_hoops_RAISS = _hoops_PASIP->_hoops_APHGA;
						_hoops_RAISS.Modify()->current = nr->current;

						HD_Standard_Draw_Tree(_hoops_RAISS, _hoops_PASIP->segment, _hoops_PASIP->path);

						_hoops_PASIP->_hoops_APHGA.release();
						FREE (_hoops_PASIP, _hoops_HSPPP);
					}
				}

				node->path = node->_hoops_CRRGH;

				++node->stage;
			}	_hoops_HHHI;

			case _hoops_SCGGH: {
#ifndef DISABLE_CUT_GEOMETRY
				if (BIT (nr->transform_rendition->flags, _hoops_CSP) &&
					!BIT(dc->flags, _hoops_IRSI) &&
					dc->_hoops_SHCI() != _hoops_HRIIP &&
					(node->geometry != null || BIT (node->flags, _hoops_CSGGH)) &&
					BIT (nr->_hoops_RGP, T_CUT_GEOMETRY) &&
					nr->_hoops_IRR->_hoops_GHIHP != 0) {

					if (_hoops_GGPGR(nr))
						goto _hoops_CSHSS;

					_hoops_RPHSS(nr);
				}

				if (BIT (node->flags, _hoops_CSGGH)) {
					dc->_hoops_CRIGA = node->_hoops_PARGH;
					node->_hoops_PARGH = null;
				}
#endif
				++node->stage;
			}	_hoops_HHHI;

			case _hoops_GSGGH: {
#if 0			// _hoops_IPIH _hoops_CPHR _hoops_IARRA _hoops_IS _hoops_SRCH _hoops_RH _hoops_HIHSS-_hoops_RRH _hoops_RPPS _hoops_AAISS _hoops_HPHR _hoops_CPAP
				if (_hoops_PAISS &&
					!ANYBIT(dc->flags, _hoops_GPHHP|_hoops_CHSHP|_hoops_IRSI) &&
					!ANYBIT (nr->current, _hoops_SRSI|_hoops_CRSI)) {
					_hoops_GSPSS (nr, start);
				}
#endif

#ifndef DISABLE_SIMPLE_SHADOW
				if (BIT (node->flags, _hoops_AGRGH) && !BIT(dc->flags, _hoops_CHSHP)) {
					if (_hoops_GGPGR(nr))
						goto _hoops_CSHSS;

					_hoops_CPHSS (nr);
				}
#endif
				++node->stage;
			}	_hoops_HHHI;

			case _hoops_ACHCP: {
				_hoops_HIHCP *		_hoops_PPRGH;

				while ((_hoops_PPRGH = node->_hoops_HPAGR) != null) {
					if (!_hoops_PPRGH->_hoops_SIHCP (nr))
						goto _hoops_SPPGR;

					node->_hoops_HPAGR = _hoops_PPRGH->prev;
					delete _hoops_PPRGH;
				}
				++node->stage;
			}	_hoops_HHHI;

			case _hoops_RSGGH: {
				// _hoops_CPHR!
				dc->Pop_Tree ();
			}	break;

			NODEFAULT;
		}

	  _hoops_SPPGR:;
	} while ((node = dc->_hoops_AHSI) != null);

	dc->_hoops_AHSI = _hoops_PGPHS;
	dc->_hoops_IPCI = _hoops_CHAPH;

	_hoops_RCCA(_hoops_SISAA) += _hoops_ISHSS;
	return;


_hoops_CSHSS:

	node->_hoops_ACPGR = dc->_hoops_IPCI;
	dc->_hoops_IPCI = _hoops_CHAPH;

	_hoops_RCCA(_hoops_SISAA) += _hoops_ISHSS;
}


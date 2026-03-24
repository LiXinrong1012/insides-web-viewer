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
 * $Id: obf_tmp.txt 1.253 2010-10-09 05:46:33 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hd_proto.h"
#include "hi_proto.h"


local void _hoops_PRAPS () {
#define _hoops_HRAPS	100,	0,	  0
#define _hoops_IRAPS		100, -100,	  0
#define _hoops_CRAPS	100,  100,	  0
#define _hoops_SRAPS	100,	0, -100
#define _hoops_GAAPS		100,	0,	100


#define _hoops_HCIPR				1, 0, 0
#define _hoops_RAAPS			2, -100, 0, 100, 0
#define _hoops_AAAPS			2, 0, -100, 0, 100
#define _hoops_PAAPS			2, -71, -71, 71, 71
#define _hoops_HAAPS		2, 71, -71, -71, 71
#define _hoops_AASCR			_hoops_SSIAP, -100, -100, 100, 100
#define _hoops_IAAPS	_hoops_SSIAP, -40, -40, 40, 40
#define _hoops_CAAPS				5, -71, -71, -71, 71, 71, 71, 71, -71, -71, -71
#define _hoops_SAAPS			5, 0, 100, 100, 0, 0, -100, -100, 0, 0, 100

#define _hoops_GPAPS		4, 0, 100, -87, -50, 87, -50, 0, 100
#define _hoops_RPAPS	4, 0, -100, -87, 50, 87, 50, 0, -100
#define _hoops_APAPS	4, -50, 87, 100, 0, -50, -87, -50, 87
#define _hoops_PPAPS	4, 50, 87, -100, 0, 50, -87, 50, 87

#define _hoops_HPAPS			_hoops_PAAPS, _hoops_HAAPS
#define _hoops_IPAPS			_hoops_RAAPS, _hoops_AAAPS
#define _hoops_CPAPS			_hoops_RAAPS, 2, 50, -87, -50, 87, 2, -50, -87, 50, 87

#define _hoops_SPAPS		3, -87, 50, 0, 0, 87, 50, 2, 0, 0, 0, -100
#define _hoops_GHAPS		4, -71, 71, 71, 71, -71, -71, 71, -71

#define _hoops_RHAPS			2, -35, 94, -35, -94, 2, 35, 94, 35, -94, 2, 94, -35, -94, -35, 2, 94, 35, -94, 35
#define _hoops_AHAPS		13, 95, 30, 95, -30, 30, -30, 30, -95, -30, -95, -30, -30, -95, -30, -95, 30, -30, 30, -30, 95, 30, 95, 30, 30, 95, 30
#define _hoops_PHAPS		13, 45, 89, 89, 45, 42, 0, 89, -45, 45, -89, 0, -42, -45, -89, -89, -45, -42, 0, -89, 45, -45, 89, 0, 42, 45, 89

	const char _hoops_HHAPS[] = {_hoops_HRAPS, _hoops_AASCR, _hoops_PSIAP};
	const char _hoops_IHAPS[] = {_hoops_HRAPS, _hoops_AASCR, _hoops_HCIPR, _hoops_PSIAP};
	const char _hoops_CHAPS[] = {_hoops_HRAPS, _hoops_AASCR, _hoops_IPAPS, _hoops_PSIAP};
	const char _hoops_SHAPS[] = {_hoops_HRAPS, _hoops_AASCR, _hoops_HPAPS, _hoops_PSIAP};
	const char _hoops_GIAPS[] = {_hoops_HRAPS, _hoops_AASCR, _hoops_IAAPS, _hoops_PSIAP};
	const char _hoops_RIAPS[] = {_hoops_HRAPS, _hoops_HSIAP, _hoops_AASCR, _hoops_CSIAP, _hoops_PSIAP};

	const char _hoops_AIAPS[] = {_hoops_HRAPS, _hoops_HCIPR, _hoops_PSIAP};
	const char _hoops_PIAPS[] = {_hoops_HRAPS, _hoops_IPAPS, _hoops_PSIAP};
	const char _hoops_HIAPS[] = {_hoops_HRAPS, _hoops_HPAPS, _hoops_PSIAP};
	const char _hoops_IIAPS[] = {_hoops_HRAPS, _hoops_CPAPS, _hoops_PSIAP};

	const char _hoops_CIAPS[] = {_hoops_HRAPS, _hoops_CAAPS, _hoops_PSIAP};
	const char _hoops_SIAPS[] = {_hoops_HRAPS, _hoops_CAAPS, _hoops_HCIPR, _hoops_PSIAP};
	const char _hoops_GCAPS[] = {_hoops_HRAPS, _hoops_CAAPS, _hoops_HPAPS, _hoops_PSIAP};
	const char _hoops_RCAPS[] = {_hoops_HRAPS, _hoops_HSIAP, _hoops_CAAPS, _hoops_CSIAP, _hoops_PSIAP};

	const char _hoops_ACAPS[] = {_hoops_HRAPS, _hoops_SAAPS, _hoops_PSIAP};
	const char _hoops_PCAPS[] = {_hoops_HRAPS, _hoops_SAAPS, _hoops_HCIPR, _hoops_PSIAP};
	const char _hoops_HCAPS[] = {_hoops_HRAPS, _hoops_SAAPS, _hoops_IPAPS, _hoops_PSIAP};
	const char _hoops_ICAPS[] = {_hoops_HRAPS, _hoops_HSIAP, _hoops_SAAPS, _hoops_CSIAP, _hoops_PSIAP};

	const char _hoops_CCAPS[] = {_hoops_HRAPS, _hoops_GPAPS, _hoops_PSIAP};
	const char _hoops_SCAPS[] = {_hoops_HRAPS, _hoops_GPAPS, _hoops_HCIPR, _hoops_PSIAP};
	const char _hoops_GSAPS[] = {_hoops_HRAPS, _hoops_HSIAP, _hoops_GPAPS, _hoops_CSIAP, _hoops_PSIAP};
	const char _hoops_RSAPS[] = {_hoops_HRAPS, _hoops_RPAPS, _hoops_PSIAP};
	const char _hoops_ASAPS[] = {_hoops_HRAPS, _hoops_RPAPS, _hoops_HCIPR, _hoops_PSIAP};
	const char _hoops_PSAPS[] = {_hoops_HRAPS, _hoops_HSIAP, _hoops_RPAPS, _hoops_CSIAP, _hoops_PSIAP};
	const char _hoops_HSAPS[] = {_hoops_HRAPS, _hoops_APAPS, _hoops_PSIAP};
	const char _hoops_ISAPS[] = {_hoops_HRAPS, _hoops_APAPS, _hoops_HCIPR, _hoops_PSIAP};
	const char _hoops_CSAPS[] = {_hoops_HRAPS, _hoops_HSIAP, _hoops_APAPS, _hoops_CSIAP, _hoops_PSIAP};
	const char _hoops_SSAPS[] = {_hoops_HRAPS, _hoops_PPAPS, _hoops_PSIAP};
	const char _hoops_GGPPS[] = {_hoops_HRAPS, _hoops_PPAPS, _hoops_HCIPR, _hoops_PSIAP};
	const char _hoops_RGPPS[] = {_hoops_HRAPS, _hoops_HSIAP, _hoops_PPAPS, _hoops_CSIAP, _hoops_PSIAP};

	const char _hoops_AGPPS[] = {_hoops_GAAPS, _hoops_GPAPS, _hoops_PSIAP};
	const char _hoops_PGPPS[] = {_hoops_GAAPS, _hoops_HSIAP, _hoops_GPAPS, _hoops_CSIAP, _hoops_PSIAP};
	const char _hoops_HGPPS[] = {_hoops_SRAPS, _hoops_RPAPS, _hoops_PSIAP};
	const char _hoops_IGPPS[] = {_hoops_SRAPS, _hoops_HSIAP, _hoops_RPAPS, _hoops_CSIAP, _hoops_PSIAP};
	const char _hoops_CGPPS[] = {_hoops_CRAPS, _hoops_APAPS, _hoops_PSIAP};
	const char _hoops_SGPPS[] = {_hoops_CRAPS, _hoops_HSIAP, _hoops_APAPS, _hoops_CSIAP, _hoops_PSIAP};
	const char _hoops_GRPPS[] = {_hoops_IRAPS, _hoops_PPAPS, _hoops_PSIAP};
	const char _hoops_RRPPS[] = {_hoops_IRAPS, _hoops_HSIAP, _hoops_PPAPS, _hoops_CSIAP, _hoops_PSIAP};

	const char _hoops_ARPPS[] = {_hoops_HRAPS, _hoops_SPAPS, _hoops_PSIAP};
	const char _hoops_PRPPS[] = {_hoops_HRAPS, _hoops_GHAPS, _hoops_PSIAP};
	const char _hoops_HRPPS[] = {_hoops_HRAPS, _hoops_AASCR, _hoops_SPAPS, _hoops_PSIAP};
	const char _hoops_IRPPS[] = {_hoops_HRAPS, _hoops_AASCR, _hoops_GHAPS, _hoops_PSIAP};
	const char _hoops_CRPPS[] = {_hoops_HRAPS, _hoops_AAAPS, _hoops_PSIAP};
	const char _hoops_SRPPS[] = {_hoops_HRAPS, _hoops_RAAPS, _hoops_PSIAP};
	const char _hoops_GAPPS[] = {_hoops_HRAPS, _hoops_HAAPS, _hoops_PSIAP};
	const char _hoops_RAPPS[] = {_hoops_HRAPS, _hoops_PAAPS, _hoops_PSIAP};
	const char _hoops_AAPPS[] = {_hoops_HRAPS, _hoops_AHAPS, _hoops_PSIAP};
	const char _hoops_PAPPS[] = {_hoops_HRAPS, _hoops_HSIAP, _hoops_AHAPS, _hoops_CSIAP, _hoops_PSIAP};
	const char _hoops_HAPPS[] = {_hoops_HRAPS, _hoops_PHAPS, _hoops_PSIAP};
	const char _hoops_IAPPS[] = {_hoops_HRAPS, _hoops_HSIAP, _hoops_PHAPS, _hoops_CSIAP, _hoops_PSIAP};
	const char _hoops_CAPPS[] = {_hoops_HRAPS, _hoops_RHAPS, _hoops_PSIAP};

#define _hoops_SAPPS(name,definition)	HC_Define_Glyph (name, _hoops_GGAPR(definition), definition)

	_hoops_SAPPS ("()",		_hoops_HHAPS);
	_hoops_SAPPS ("(.)",	_hoops_IHAPS);
	_hoops_SAPPS ("(+)",	_hoops_CHAPS);
	_hoops_SAPPS ("(x)",	_hoops_SHAPS);
	_hoops_SAPPS ("(())",	_hoops_GIAPS);
	_hoops_SAPPS ("(*)",	_hoops_RIAPS);

	_hoops_SAPPS ("o",		_hoops_HHAPS);
	_hoops_SAPPS ("0",		_hoops_HHAPS);
	_hoops_SAPPS ("@",		_hoops_RIAPS);
	_hoops_SAPPS ("(o)",	_hoops_GIAPS);
	_hoops_SAPPS ("(0)",	_hoops_GIAPS);

	_hoops_SAPPS (".",		_hoops_AIAPS);
	_hoops_SAPPS ("+",		_hoops_PIAPS);
	_hoops_SAPPS ("x",		_hoops_HIAPS);
	_hoops_SAPPS ("*",		_hoops_IIAPS);

	_hoops_SAPPS ("[]",		_hoops_CIAPS);
	_hoops_SAPPS ("[.]",	_hoops_SIAPS);
	_hoops_SAPPS ("[x]",	_hoops_GCAPS);
	_hoops_SAPPS ("[*]",	_hoops_RCAPS);
	_hoops_SAPPS ("<>",		_hoops_ACAPS);
	_hoops_SAPPS ("<.>",	_hoops_PCAPS);
	_hoops_SAPPS ("<+>",	_hoops_HCAPS);
	_hoops_SAPPS ("<*>",	_hoops_ICAPS);

	_hoops_SAPPS ("/\\",	_hoops_CCAPS);
	_hoops_SAPPS ("/.\\",	_hoops_SCAPS);
	_hoops_SAPPS ("/*\\",	_hoops_GSAPS);
	_hoops_SAPPS ("^/\\",	_hoops_AGPPS);
	_hoops_SAPPS ("^/*\\",	_hoops_PGPPS);
	_hoops_SAPPS ("\\/",	_hoops_RSAPS);
	_hoops_SAPPS ("\\./",	_hoops_ASAPS);
	_hoops_SAPPS ("\\*/",	_hoops_PSAPS);
	_hoops_SAPPS ("v\\/",	_hoops_HGPPS);
	_hoops_SAPPS ("v\\*/",	_hoops_IGPPS);
	_hoops_SAPPS ("<|",		_hoops_SSAPS);
	_hoops_SAPPS ("<.|",	_hoops_GGPPS);
	_hoops_SAPPS ("<*|",	_hoops_RGPPS);
	_hoops_SAPPS ("<<|",	_hoops_GRPPS);
	_hoops_SAPPS ("<<*|",	_hoops_RRPPS);
	_hoops_SAPPS ("|>",		_hoops_HSAPS);
	_hoops_SAPPS ("|.>",	_hoops_ISAPS);
	_hoops_SAPPS ("|*>",	_hoops_CSAPS);
	_hoops_SAPPS (">|>",	_hoops_CGPPS);
	_hoops_SAPPS (">|*>",	_hoops_SGPPS);

	_hoops_SAPPS ("y",		_hoops_ARPPS);
	_hoops_SAPPS ("z",		_hoops_PRPPS);
	_hoops_SAPPS ("(y)",	_hoops_HRPPS);
	_hoops_SAPPS ("(z)",	_hoops_IRPPS);
	_hoops_SAPPS ("|",		_hoops_CRPPS);
	_hoops_SAPPS ("-",		_hoops_SRPPS);
	_hoops_SAPPS ("/",		_hoops_RAPPS);
	_hoops_SAPPS ("\\",		_hoops_GAPPS);
	_hoops_SAPPS ("++",		_hoops_AAPPS);
	_hoops_SAPPS ("+*+",	_hoops_PAPPS);
	_hoops_SAPPS ("xx",		_hoops_HAPPS);
	_hoops_SAPPS ("x*x",	_hoops_IAPPS);
	_hoops_SAPPS ("#",		_hoops_CAPPS);
}

local void _hoops_GPPPS () {
	const char *_hoops_RPPPS = "dash";
	const char *_hoops_APPPS = "18 dash, 5 blank, 4 dash, 5 blank";
	const char *_hoops_PPPPS = "10 dash, 6 blank";
	const char *_hoops_HPPPS = "5 dash, 3 blank";
	const char *_hoops_IPPPS = "15 dash, 4 blank, 3 dash, 3 blank, 3 dash, 4 blank";
	const char *_hoops_CPPPS = "15 dash, 2 blank, 3 dash, 2 blank, 3 dash, 2 blank, 3 dash, 2 blank";
	const char *_hoops_SPPPS = "26 dash, 6 blank";
	const char *_hoops_GHPPS = "100 dash, 10 blank, 20 dash, 10 blank";
	const char *_hoops_RHPPS = "86 dash, 8 blank, 15 dash, 8 blank, 15 dash, 8 blank";
	const char *_hoops_AHPPS = "1 dash, 3 blank";

	/* 0-9 _hoops_CHR _hoops_IRRIR _hoops_IH _hoops_CCSHP _hoops_III */

	/*_hoops_PHPPS*/
	HC_Define_Line_Style("0", _hoops_RPPPS);
	HC_Define_Line_Style("-", _hoops_RPPPS);
	HC_Define_Line_Style("solid", _hoops_RPPPS);

	/*_hoops_HHPPS*/
	HC_Define_Line_Style("1", _hoops_APPPS);
	HC_Define_Line_Style("-.", _hoops_APPPS);

	/*_hoops_IHPPS*/
	HC_Define_Line_Style("2", _hoops_PPPPS);
	HC_Define_Line_Style("- -", _hoops_PPPPS);
	HC_Define_Line_Style("dashed", _hoops_PPPPS);

	/*_hoops_CHPPS*/
	HC_Define_Line_Style("3", _hoops_HPPPS);
	HC_Define_Line_Style(".", _hoops_HPPPS);
	HC_Define_Line_Style("dotted", _hoops_HPPPS);

	/*_hoops_SHPPS*/
	HC_Define_Line_Style("4", _hoops_IPPPS);
	HC_Define_Line_Style("-..", _hoops_IPPPS);

	/*_hoops_GIPPS*/
	HC_Define_Line_Style("5", _hoops_CPPPS);
	HC_Define_Line_Style("-...", _hoops_CPPPS);

	/*_hoops_RIPPS*/
	HC_Define_Line_Style("6", _hoops_SPPPS);
	HC_Define_Line_Style("-- --", _hoops_SPPPS);
	HC_Define_Line_Style("long dash", _hoops_SPPPS);

	/*_hoops_AIPPS*/
	HC_Define_Line_Style("7", _hoops_GHPPS);
	HC_Define_Line_Style("center", _hoops_GHPPS);

	/*_hoops_PIPPS*/
	HC_Define_Line_Style("8", _hoops_RHPPS);
	HC_Define_Line_Style("phantom", _hoops_RHPPS);

	/*_hoops_HIPPS*/
	HC_Define_Line_Style("9", _hoops_AHPPS);
	HC_Define_Line_Style("...fine", _hoops_AHPPS);
	HC_Define_Line_Style("finedot", _hoops_AHPPS);
}



HC_INTERFACE void HC_CDECL HC_Set_Default_Line_Styles()
{
	_hoops_PAPPR context("Set_Default_Line_Styles");

	CODE_GENERATION (
		HI_Dump_Code ("HC_Set_Default_Line_Styles();\n");
	);

	_hoops_RPPPR();

	if (context->open_list != null && context->open_list->_hoops_GCRIR == _hoops_RCRIR ||
		HI_Find_Our_Open (context)) {

		_hoops_GPPPS ();
	}

	_hoops_IRRPR();
}

HC_INTERFACE void HC_CDECL HC_Set_Default_Line_Styles_By_K(Key target_segment)
{
	_hoops_PAPPR context("Set_Default_Line_Styles_By_Key");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Set_Default_Line_Styles_By_Key (LOOKUP (%D));\n", target_segment));
	);

	_hoops_RPPPR();
	_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)_hoops_RCSSR (context, target_segment);
	if (_hoops_SRCP == null || _hoops_SRCP->type != _hoops_IRCP || BIT(_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SYSTEM, HES_INVALID_KEY, "Provided key does not refer to a valid segment");
		_hoops_IRRPR();
		return;
	}

	HI_Open_Segment (context, _hoops_SRCP);
	_hoops_GPPPS ();
	HI_Close_Segment (context);

	_hoops_IRRPR();
}

HC_INTERFACE void HC_CDECL HC_Set_Default_Glyphs()
{
	_hoops_PAPPR context("Set_Default_Glyphs");

	CODE_GENERATION (
		HI_Dump_Code ("HC_Set_Default_Glyphs();\n");
	);

	_hoops_RPPPR();

	if (context->open_list != null && context->open_list->_hoops_GCRIR == _hoops_RCRIR ||
		HI_Find_Our_Open (context)) {

		_hoops_PRAPS ();
	}

	_hoops_IRRPR();
}

HC_INTERFACE void HC_CDECL HC_Set_Default_Glyphs_By_Key(Key target_segment)
{
	_hoops_PAPPR context("Set_Default_Glyphs_By_Key");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Set_Default_Glyphs_By_Key (LOOKUP (%D));\n", target_segment));
	);

	_hoops_RPPPR();
	_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)_hoops_RCSSR (context, target_segment);
	if (_hoops_SRCP == null || _hoops_SRCP->type != _hoops_IRCP || BIT(_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SYSTEM, HES_INVALID_KEY, "Provided key does not refer to a valid segment");
		_hoops_IRRPR();
		return;
	}

	HI_Open_Segment (context, _hoops_SRCP);
	_hoops_PRAPS ();
	HI_Close_Segment (context);

	_hoops_IRRPR();
}


GLOBAL_FUNCTION void HI_Set_Default_Attributes (
	_hoops_AIGPR *		_hoops_RIGC) 
{
	Attribute *					_hoops_ASGPR;
	float						matrix[16];

	PUSHNAME(_hoops_RIGC);

	_hoops_AASAH(_hoops_RIGC, "Set Default Attributes (internal)");

	// _hoops_PHAA, _hoops_CASI _hoops_GGSR _hoops_GII _hoops_RHGS _hoops_AIRC _hoops_GGR _hoops_AGIR _hoops_SR _hoops_CHR _hoops_GRP _hoops_RGR _hoops_GAR _hoops_IRS _hoops_SHPP-_hoops_HIAP
	if ((_hoops_ASGPR = HOOPS_WORLD->root->_hoops_IPPGR) != null) do {
		//_hoops_IIPPS (_hoops_HHAPA, _hoops_IRAP, _hoops_IGRI->_hoops_RRRPR, _hoops_GPRR, _hoops_IGRI, _hoops_IRAP);
		HI_Generic_Delete (_hoops_RIGC, (_hoops_HPAH *)_hoops_ASGPR);
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

	HI_Open_Segment (_hoops_RIGC, HOOPS_WORLD->root);

	PUSHNAME(_hoops_RIGC);		/* (_hoops_ICRP _hoops_IIGR _hoops_RH _hoops_HSPR _hoops_AA _hoops_IRS _hoops_IISPP) */

	HI_Compute_Identity_Matrix (matrix);

	/* _hoops_GRR _hoops_PPR _hoops_RCSAR _hoops_SSRR _hoops_CHCA _hoops_IGRI _hoops_PIHA _hoops_RPGAH
	 * _hoops_GGR _hoops_RGR _hoops_HIGR (_hoops_GSSR _hoops_SAHR _hoops_ARR).
	 */

#ifndef DISABLE_CALLBACKS
	HC_Set_Callback ("draw dc face=null, draw dc edge=null, draw dc colorized face=null");
	HC_Set_Callback ("draw dc marker=null, draw dc colorized marker=null");
	HC_Set_Callback ("draw dc polymarker=null, draw dc colorized polymarker=null");
	HC_Set_Callback ("draw dc line=null, draw dc colorized line=null");
	HC_Set_Callback ("draw dc gouraud line=null, draw dc reshaded line=null");
	HC_Set_Callback ("draw dc polyline=null, draw dc colorized polyline=null, draw dc gouraud polyline=null");
	HC_Set_Callback ("draw dc phong polyline=null, draw dc textured polyline=null");
	HC_Set_Callback ("draw dc triangle=null, draw dc colorized triangle=null");
	HC_Set_Callback ("draw dc gouraud triangle=null, draw dc reshaded triangle=null");
	HC_Set_Callback ("draw dc polytriangle=null, draw dc colorized polytriangle=null, draw dc gouraud polytriangle=null");
	HC_Set_Callback ("draw dc phong polytriangle=null, draw dc textured polytriangle=null");
	HC_Set_Callback ("draw dc text stroke=null, draw dc text area=null");
	HC_Set_Callback ("draw dc cut line=null");

	HC_Set_Callback ("draw text=null");
	HC_Set_Callback ("draw window=null, draw window frame=null");

	HC_Set_Callback ("hlr marker=null, hlr polyline=null");
	HC_Set_Callback ("hlr hidden marker=null, hlr hidden polyline=null");


	HC_Set_Callback ("draw 3d marker=null, draw 3d polyline=null, draw 3d polygon=null");
	HC_Set_Callback ("draw 3d infinite line=null, draw 3d image=null, draw 3d grid=null");
	HC_Set_Callback ("draw 3d ellipse=null, draw 3d elliptical arc=null");
	HC_Set_Callback ("draw 3d sphere=null, draw 3d cylinder=null, draw 3d polycylinder=null");
	HC_Set_Callback ("draw 3d nurbs curve=null, draw 3d nurbs surface=null");
	HC_Set_Callback ("draw 3d polyhedron=null, draw 3d isoline=null");
	HC_Set_Callback ("draw 3d tristrip=null, draw 3d polyedge=null, draw 3d polymarker=null");
	HC_Set_Callback ("draw 3d text=null, draw 3d text stroke=null, draw 3d text area=null");
	HC_Set_Callback ("draw 3d contour=null, draw 3d geometry=null");

	HC_Set_Callback ("draw segment=null, draw segment tree=null");


	HC_Set_Callback ("select 3d marker=null, select 3d polyline=null");
	HC_Set_Callback ("select 3d polygon=null, select 3d text=null");
	HC_Set_Callback ("select 3d geometry=null");

	HC_Set_Callback ("select text=null");
	HC_Set_Callback ("select window=null");

	HC_Set_Callback ("select segment=null, select segment tree=null");


	HC_Set_Callback ("segment activity change=null");
	HC_Set_Callback ("driver startup=null, driver shutdown=null");
	HC_Set_Callback ("finish picture=null");
	HC_Set_Callback ("create region=null, save region=null, restore region=null, destroy region=null");
	HC_Set_Callback ("process segment=null");
#endif

	HC_Set_Camera_By_Volume ("perspective", -1.0, 1.0, -1.0, 1.0);

	HC_Set_Polygonal_Clip_Region (0, null, "");

#ifndef DISABLE_COLOR_NAMES
	HC_Set_Color ("geometry = window contrast = black, ambient = dark gray, windows = face contrast = lighting = white");
	HC_Set_Color ("edge contrast = line contrast = marker contrast = vertex contrast = text contrast = white");
	HC_Set_Color ("everything = (specular=mirror=white,transmission=emission=black,gloss=5,index=1)");

	HC_Set_Color ("cut edges = light gray, cut faces = dark gray");
	HC_Set_Color ("cut geometry = (specular=mirror=white,transmission=emission=black,gloss=5,index=1)");
	HC_Set_Color ("simple reflection = black");
#else
	HC_Set_Color ("geometry = window contrast = (R=0 G=0 B=0), ambient = (R=0.3 G=0.3 B=0.3), windows = face contrast = lighting = (R=1 G=1 B=1)");
	HC_Set_Color ("edge contrast = line contrast = marker contrast = vertex contrast = text contrast =  (R=1 G=1 B=1)");
	HC_Set_Color ("everything=(specular=mirror=(R=1 G=1 B=1),transmission=emission=(R=0 G=0 B=0),gloss=5,index=1)");

	HC_Set_Color ("cut edges = (R=0.675 G=0.675 B=0.675), cut faces = (R=0.325 G=0.325 B=0.325)");
	HC_Set_Color ("cut geometry = (specular=mirror=R=1 G=1 B=1,transmission=emission=R=0 G=0 B=0,gloss=5,index=1)");
#endif

#ifndef DISABLE_COLOR_MAPS
	HC_Set_Color_Map ("");
#endif
	HC_Set_Conditions ("");

	HI_Create_Actor(_hoops_RIGC, _hoops_RIGC->open_list->info.segment._hoops_IGRPR, HD_Null_Driver);

	HC_Set_Driver_Options ("no display statistics, no backing store, border, color consolidation = 1.5625%");
	HC_Set_Driver_Options ("control area, no debug, no disable input, no double-buffering");
	HC_Set_Driver_Options ("no first color, no fixed colors, no force black-and-white");
	HC_Set_Driver_Options ("no gamma correction, landscape orientation, no light scaling");
	HC_Set_Driver_Options ("no locater transform, no number of colors");
	HC_Set_Driver_Options ("no output format, pen speed = 1.0, no physical size");
	HC_Set_Driver_Options ("no selection proximity, no special events");
	HC_Set_Driver_Options ("no subscreen, subscreen creating, subscreen moving, subscreen resizing");
	HC_Set_Driver_Options ("no subscreen stretching, title, update interrupts");
	HC_Set_Driver_Options ("no use colormap ID, no use window ID, no use window ID2");
	HC_Set_Driver_Options ("no write mask, hardcopy resolution = 75, text preference = default");
	HC_Set_Driver_Options ("stencil,no stereo,no anti-alias,no isolated");
	HC_Set_Driver_Options ("shadow preference=software");
	HC_Set_Driver_Options ("no absolute line weight");
	HC_Set_Driver_Options ("ambient occlusion = (off, strength = 1.0, quality = fast)");
	HC_Set_Driver_Options ("fast silhouette edges = (off, tolerance = 1.0, no heavy exterior)");
	HC_Set_Driver_Options ("bloom = (off, strength = 1.0, blur = 5, shape = radial)");
	HC_Set_Driver_Options ("depth of field = (off, strength = 1.0, near = -1e6, far = 1e6)");
	HC_Set_Driver_Options ("spotlight interpolation=vertex");
	HC_Set_Driver_Options ("no exit update, exit update data=0x00000000");

	HC_Set_Edge_Pattern ("---");
	HC_Set_Edge_Weight (1.0);
	HC_Set_Face_Pattern ("SOLID");
	HC_Set_Handedness ("left");

	HC_Set_Heuristics ("clipping, transformations, no intersecting polygons, backplane cull, no concave polygons, no polygon crossings");
	HC_Set_Heuristics ("no polygon handedness, hidden surfaces, no memory purge, incremental updates, no quick move, no partial erase");
	HC_Set_Heuristics ("selection sorting, related selection limit = 5, internal selection limit = 0, no visual selection, no detail selection, selection level=entity");
	HC_Set_Heuristics ("culling=(view frustum,sub-pixel,no obscuration), no ordered drawing, ordered weights=(everything=0)");
	HC_Set_Heuristics ("no static model, model type=default");
	HC_Set_Heuristics ("no force defer batch, culling=maximum extent level=default");
	/* _hoops_CIPPS ("_hoops_GHIAR _hoops_IASC"); <-- _hoops_GRH _hoops_RIR-_hoops_CAGH _hoops_RGSR, _hoops_PSP _hoops_RRP _hoops_IS '_hoops_ARP' _hoops_IRS _hoops_SHIR */

	HC_Set_Line_Pattern ("---");
	HC_Set_Line_Weight (1.0);
	HC_Set_Marker_Size (1.0);
	HC_Set_Marker_Symbol ("O");

	_hoops_PRAPS ();
	_hoops_GPPPS ();

	HC_Set_Modelling_Matrix (matrix);

	HC_Set_Rendering_Options ("lighting interpolation, color interpolation, color index interpolation, texture interpolation");
	HC_Set_Rendering_Options ("perspective correction, no local viewer, no atmospheric attenuation");
	HC_Set_Rendering_Options ("no attribute lock, no debug, technology=standard, quantization=dither");
	HC_Set_Rendering_Options ("hsr algorithm=hardware z buffer, face displacement=8, vertex displacement=0, general displacement=0, no scaled displacement");
	HC_Set_Rendering_Options ("software frame buffer options=(no size limit, retention, color depth=match device)");
	HC_Set_Rendering_Options ("hidden line removal options=(visibility=on, pattern=4, dim factor=0.5, face displacement=0.5, no silhouette cleanup, transparency cutoff=0.8)");
	HC_Set_Rendering_Options (" hidden line removal options=(no weight, no color, no image outline, rendered face sorting algorithm=hardware z buffer)");
	HC_Set_Rendering_Options ("no lod, lodo=(clamp=-1, threshold=30tpcm2, ratio=0.5, levels=2, min triangle count=25, no conserve memory, mode=geometry)");
	HC_Set_Rendering_Options (" lodo=(algorithm=fast)");
	HC_Set_Rendering_Options (" lodo=(no bounding, usefulness heuristic = volume ratio, no calculation usefulness cutoff)");
	HC_Set_Rendering_Options (" lodo=(collapse duplicate vertices, fallback = coarsest none)");
	HC_Set_Rendering_Options ("gooch options = (color range = (0,1), diffuse weight = 0.5, no color map segment)");
	HC_Set_Rendering_Options ("no display lists,nurbs curve=(no view dependent, budget=512, no continued budget)");
	HC_Set_Rendering_Options ("nurbs curve=(no max deviation, max angle = 10, max length = 0)");
	HC_Set_Rendering_Options ("nurbs surface=(max trim curve deviation=0.005, trim curve budget=500)");
	HC_Set_Rendering_Options ("nurbs surface=(max facet deviation=10, max facet angle=20)");
	HC_Set_Rendering_Options ("nurbs surface=(max facet width=1.42, budget=10000)"); /* _hoops_RIHPA _hoops_SHIR _hoops_PIHA _hoops_PSSP _hoops_SIPPS._hoops_GSGGR */
	HC_Set_Rendering_Options ("no stereo, stereo separation=3.0, no anti-alias");
	HC_Set_Rendering_Options ("tessellation=(sphere=(24,12,6,0,-1), cylinder=(24,12,6,0,-1)), geometry options=(dihedral=135, no invert polycylinders)");
	HC_Set_Rendering_Options ("vertex decimation = 1");

	HC_Set_Rendering_Options ("transparency=(no depth writing, zsort options=nicest, style=blending, hsr algorithm=z-sort only, hardware, depth peeling options=(layers=4, minimum area=0))");
	HC_Set_Rendering_Options ("cut geometry options=(level=entity, tolerance=10%, match color=off)");
	HC_Set_Rendering_Options ("simple shadow=(off, plane=(0,1,0,1), light=(0,1,0), color='r=0 g=0 b=0', opacity=1, resolution=256, blurring=1, no ignore transparency)");
	HC_Set_Rendering_Options ("shadow map=(off, jitter, view dependent, resolution=1024, samples=4)");
	HC_Set_Rendering_Options ("simple reflection=(off, plane=(0,1,0,1), opacity=0.5, fading, no attenuation, no blur, visibility=(off, faces, lights))");
	HC_Set_Rendering_Options ("depth range=(0,1), screen range=(-1,1,-1,1)");
	HC_Set_Rendering_Options ("no ambient up vector");
	HC_Set_Rendering_Options ("frame buffer effects=on");
	HC_Set_Rendering_Options ("image scale=(1.0,1.0)");
	/* _hoops_GCPPS ("_hoops_PSP _hoops_PISH _hoops_AHGGR"); <-- _hoops_GRH _hoops_RIR-_hoops_CAGH _hoops_RGSR, _hoops_PSP _hoops_RRP _hoops_IS '_hoops_ARP' _hoops_IRS _hoops_SHIR */
	HC_Set_Rendering_Options ("join cutoff angle=170");
	HC_Set_Rendering_Options ("contour options=(visibility, no value adjustment)");
	HC_Set_Rendering_Options ("isoline options=(no visibility, position=default, no colors, no patterns, no weights, no lighting)");
	HC_Set_Rendering_Options ("diffuse color tint=(off, range=(0,1), color=white, effect=modulate grayscale)");
	HC_Set_Rendering_Options ("no local viewer, no local cutting planes");

#ifndef DISABLE_AIR_OPTIONS
	HC_Set_Rendering_Options ("radiosity options=(convergence goal=50%,interim display,no special events)");
	HC_Set_Rendering_Options ("radiosity options=(no internal subdivision,accuracy=2,no boundary continuity)");
	HC_Set_Rendering_Options ("radiosity options=(no energy preservation, no interference detection)");
	HC_Set_Rendering_Options ("radiosity options=(autoscale, brightness=1.0, contrast=1.0)");
	HC_Set_Rendering_Options ("ray-trace options=(no special events,scan-line method,no anti-aliasing,bounce limit=5)");
	HC_Set_Rendering_Options ("ray-trace options=(required contribution=10%,display style=interlaced raster,no blocking)");
#endif


	HC_Set_Selectability ("everything=off, windows=v");
	HC_Set_Streaming_Mode ("off");


	HC_Set_Text_Alignment ("**[");
	HC_Set_Text_Font ("name=sans serif, no transforms, size = 0.03sru, size tolerance = 50%, line spacing=1.25");
	HC_Set_Text_Font ("no rotation, no width scale, no extra space, no slant, no greeking limit, greeking mode=lines");
	HC_Set_Text_Font ("no outline, no underline, no strikethrough, no overline, no even spacing, no fill edges");
	HC_Set_Text_Font ("renderer=(default, no cutoff), preference=(driver, no cutoff)");
	HC_Set_Text_Path (1.0, 0.0, 0.0);
	HC_Set_Text_Spacing (1.0);


#ifndef DISABLE_TEXTURING
	HC_Set_Texture_Matrix (matrix);
#endif

	HC_Set_User_Options ("");
	unsigned short	_hoops_RCPPS = 0;
	HC_Set_Unicode_Options (&_hoops_RCPPS);
	HC_Set_User_Value ((long)0);

	HC_Set_Visibility ("on, no cut geometry");

	HC_Set_Window (-1.0, 1.0, -1.0, 1.0);
	HC_Set_Window_Frame ("on");
	HC_Set_Window_Pattern ("SOLID");


	HC_Close_Segment ();
	POPNAME(_hoops_RIGC);
	POPNAME(_hoops_RIGC);
}

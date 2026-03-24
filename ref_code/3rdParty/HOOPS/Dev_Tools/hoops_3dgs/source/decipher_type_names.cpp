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
 * $Id: obf_tmp.txt 1.142 2010-10-22 23:49:54 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "searchh.h"
#include "hi_proto.h"
#include "hpserror.h"


local const struct {
	_hoops_SRHSR			name;
	int					type;
}		_hoops_SPAPP[] = {

	{_hoops_GRRCR ("e"),						_hoops_GHAPP},
	{_hoops_GRRCR ("a"),						_hoops_RHAPP},
	{_hoops_GRRCR ("g"),						_hoops_AHAPP},
	{_hoops_GRRCR ("s"),						_hoops_PHAPP},

	{_hoops_GRRCR ("everything"),				_hoops_GHAPP},
	{_hoops_GRRCR ("anything"),					_hoops_GHAPP},
	{_hoops_GRRCR ("geometry"),					_hoops_AHAPP},
	{_hoops_GRRCR ("attribute"),				_hoops_RHAPP},
	{_hoops_GRRCR ("subsegment"),				_hoops_PHAPP},
	{_hoops_GRRCR ("ordered"),					_hoops_HHAPP},
	{_hoops_GRRCR ("inked line"),				_hoops_IHAPP},

	{_hoops_GRRCR ("self"),						_hoops_CHAPP},
	{_hoops_GRRCR ("interesting"),				_hoops_SHAPP},
	{_hoops_GRRCR ("first match"),				_hoops_GIAPP},


	{_hoops_GRRCR ("distant light"),			_hoops_RIAPP},
	{_hoops_GRRCR ("local light"),				_hoops_AIAPP},
	{_hoops_GRRCR ("spot light"),				_hoops_PIAPP},
	{_hoops_GRRCR ("area light"),				_hoops_HIAPP},

	{_hoops_GRRCR ("includer"),					_hoops_IIAPP},
	{_hoops_GRRCR ("styler"),					_hoops_CIAPP},
	{_hoops_GRRCR ("referrer"),					_hoops_SIAPP},

	{_hoops_GRRCR ("style"),					HK_STYLE},
	{_hoops_GRRCR ("style segment"),			HK_STYLE},
	{_hoops_GRRCR ("segment style"),			HK_STYLE},
	{_hoops_GRRCR ("color"),					HK_COLOR},
	{_hoops_GRRCR ("callback"),					HK_CALLBACK},
	{_hoops_GRRCR ("camera"),					HK_CAMERA},
	{_hoops_GRRCR ("clip region"),				HK_CLIP_REGION},
	{_hoops_GRRCR ("handedness"),				HK_HANDEDNESS},
	{_hoops_GRRCR ("selectability"),			HK_SELECTABILITY},
	{_hoops_GRRCR ("visibility"),				HK_VISIBILITY},
	{_hoops_GRRCR ("window"),					HK_WINDOW},
	{_hoops_GRRCR ("window frame"),				HK_WINDOW_FRAME},
	{_hoops_GRRCR ("color map"),				HK_COLOR_MAP},
	{_hoops_GRRCR ("driver"),					HK_DRIVER},
	{_hoops_GRRCR ("driver options"),			HK_DRIVER_OPTIONS},
	{_hoops_GRRCR ("edge pattern"),				HK_EDGE_PATTERN},
	{_hoops_GRRCR ("edge weight"),				HK_EDGE_WEIGHT},
	{_hoops_GRRCR ("face pattern"),				HK_FACE_PATTERN},
	{_hoops_GRRCR ("heuristics"),				HK_HEURISTICS},
	{_hoops_GRRCR ("line pattern"),				HK_LINE_PATTERN},
	{_hoops_GRRCR ("line weight"),				HK_LINE_WEIGHT},
	{_hoops_GRRCR ("marker size"),				HK_MARKER_SIZE},
	{_hoops_GRRCR ("marker symbol"),			HK_MARKER_SYMBOL},
	{_hoops_GRRCR ("modelling matrix"),			HK_MODELLING_MATRIX},
	{_hoops_GRRCR ("rendering options"),		HK_RENDERING_OPTIONS},
	{_hoops_GRRCR ("text alignment"),			HK_TEXT_ALIGNMENT},
	{_hoops_GRRCR ("text font"),				HK_TEXT_FONT},
	{_hoops_GRRCR ("text path"),				HK_TEXT_PATH},
	{_hoops_GRRCR ("text spacing"),				HK_TEXT_SPACING},
	{_hoops_GRRCR ("texture matrix"),			HK_TEXTURE_MATRIX},
	{_hoops_GRRCR ("user value"),				HK_USER_VALUE},
	{_hoops_GRRCR ("window pattern"),			HK_WINDOW_PATTERN},
	{_hoops_GRRCR ("texture definition"),		_hoops_IPAIR},
	{_hoops_GRRCR ("local texture"),			_hoops_IPAIR},
	{_hoops_GRRCR ("glyph definition"),			_hoops_RAAIR},
	{_hoops_GRRCR ("line pattern definition"),	_hoops_RPAIR},
	{_hoops_GRRCR ("line style definition"),	_hoops_RPAIR},
	{_hoops_GRRCR ("named style definition"),	_hoops_HAAIR},
	{_hoops_GRRCR ("condition"),				_hoops_CPPIR},
	{_hoops_GRRCR ("streaming mode"),			_hoops_GRAIR},
	{_hoops_GRRCR ("circle"),					_hoops_SGCP},
	{_hoops_GRRCR ("circular arc"),				_hoops_RIIP},
	{_hoops_GRRCR ("circular chord"),			_hoops_GRCP},
	{_hoops_GRRCR ("circular wedge"),			_hoops_RRCP},
	{_hoops_GRRCR ("cutting plane"),			_hoops_HGPGR},
	{_hoops_GRRCR ("cutting section"),			_hoops_HGPGR},
	{_hoops_GRRCR ("light"),					_hoops_ICIP},
	{_hoops_GRRCR ("ellipse"),					_hoops_CGCP},
	{_hoops_GRRCR ("elliptical arc"),			_hoops_GIIP},
	{_hoops_GRRCR ("grid"),						_hoops_GGCP},
	{_hoops_GRRCR ("line"),						_hoops_PIIP},
	{_hoops_GRRCR ("marker"),					_hoops_PCIP},
	{_hoops_GRRCR ("mesh"),						_hoops_GSIP},
	{_hoops_GRRCR ("image"),					_hoops_HGCP},
	{_hoops_GRRCR ("pixel array"),				_hoops_HGCP},
	{_hoops_GRRCR ("polyline"),					_hoops_IIIP},
	{_hoops_GRRCR ("polygon"),					_hoops_RCIP},
	{_hoops_GRRCR ("shell"),					_hoops_SCIP},
	{_hoops_GRRCR ("string cursor"),			HK_STRING_CURSOR},
	{_hoops_GRRCR ("text"),						_hoops_AGCP},
	{_hoops_GRRCR ("nurbs curve"),				_hoops_CHIP},
	{_hoops_GRRCR ("nurbs surface"),			_hoops_PRCP},
	{_hoops_GRRCR ("cylinder"),					_hoops_ASIP},
	{_hoops_GRRCR ("polycylinder"),				_hoops_CSIP},
	{_hoops_GRRCR ("sphere"),					_hoops_HSIP},
	{_hoops_GRRCR ("reference"),				_hoops_AHIP},
	{_hoops_GRRCR ("reference geometry"),		_hoops_AHIP},
	{_hoops_GRRCR ("geometry reference"),		_hoops_AHIP},
	{_hoops_GRRCR ("include"),					_hoops_AGRPR},
	{_hoops_GRRCR ("include segment"),			_hoops_AGRPR},
	{_hoops_GRRCR ("segment include"),			_hoops_AGRPR},
	{_hoops_GRRCR ("segment"),					_hoops_IRCP},
	{_hoops_GRRCR ("infinite line"),			_hoops_SIIP},
	{_hoops_GRRCR ("infinite ray"),				_hoops_GCAPP},

	{_hoops_GRRCR ("normal"),					_hoops_RCICA},
	{_hoops_GRRCR ("parameter"),				_hoops_PCICA},
	{_hoops_GRRCR ("face attribute"),			_hoops_RCAPP},
	{_hoops_GRRCR ("face color"),				_hoops_ACAPP},
	{_hoops_GRRCR ("face normal"),				_hoops_PCAPP},
	{_hoops_GRRCR ("face pattern"),				_hoops_HCAPP},
	{_hoops_GRRCR ("face visibility"),			_hoops_ICAPP},
	{_hoops_GRRCR ("edge attribute"),			_hoops_CCAPP},
	{_hoops_GRRCR ("edge color"),				_hoops_SCAPP},
	{_hoops_GRRCR ("edge normal"),				_hoops_GSAPP},
	{_hoops_GRRCR ("edge pattern"),				_hoops_RSAPP},
	{_hoops_GRRCR ("edge weight"),				_hoops_ASAPP},
	{_hoops_GRRCR ("edge visibility"),			_hoops_PSAPP},
	{_hoops_GRRCR ("vertex attribute"),			_hoops_HSAPP},
	{_hoops_GRRCR ("vertex color"),				_hoops_ISAPP},
	{_hoops_GRRCR ("vertex face color"),		_hoops_CSAPP},
	{_hoops_GRRCR ("vertex edge color"),		_hoops_SSAPP},
	{_hoops_GRRCR ("vertex marker color"),		_hoops_GGPPP},
	{_hoops_GRRCR ("vertex marker rgba"),		_hoops_RGPPP},
	{_hoops_GRRCR ("vertex normal"),			_hoops_AGPPP},
	{_hoops_GRRCR ("vertex parameter"),			_hoops_PGPPP},
	{_hoops_GRRCR ("vertex symbol"),			_hoops_HGPPP},
	{_hoops_GRRCR ("vertex size"),				_hoops_IGPPP},
	{_hoops_GRRCR ("vertex visibility"),		_hoops_CGPPP},

	{_hoops_GRRCR ("face color"),				_hoops_CSAPP},
	{_hoops_GRRCR ("edge color"),				_hoops_SSAPP},
	{_hoops_GRRCR ("marker color"),				_hoops_GGPPP},

	{_hoops_GRRCR ("attributes"),				_hoops_RHAPP},
	{_hoops_GRRCR ("subsegments"),				_hoops_PHAPP},
	{_hoops_GRRCR ("inked lines"),				_hoops_IHAPP},

	{_hoops_GRRCR ("distant lights"),			_hoops_RIAPP},
	{_hoops_GRRCR ("local lights"),				_hoops_AIAPP},
	{_hoops_GRRCR ("spot lights"),				_hoops_PIAPP},
	{_hoops_GRRCR ("area lights"),				_hoops_HIAPP},

	{_hoops_GRRCR ("includers"),				_hoops_IIAPP},
	{_hoops_GRRCR ("stylers"),					_hoops_CIAPP},
	{_hoops_GRRCR ("referrers"),				_hoops_SIAPP},

	{_hoops_GRRCR ("styles"),					HK_STYLE},
	{_hoops_GRRCR ("style segments"),			HK_STYLE},
	{_hoops_GRRCR ("segment styles"),			HK_STYLE},
	{_hoops_GRRCR ("colors"),					HK_COLOR},
	{_hoops_GRRCR ("callbacks"),				HK_CALLBACK},
	{_hoops_GRRCR ("cameras"),					HK_CAMERA},
	{_hoops_GRRCR ("clip regions"),				HK_CLIP_REGION},
	{_hoops_GRRCR ("windows"),					HK_WINDOW},
	{_hoops_GRRCR ("window frames"),			HK_WINDOW_FRAME},
	{_hoops_GRRCR ("color maps"),				HK_COLOR_MAP},
	{_hoops_GRRCR ("drivers"),					HK_DRIVER},
	{_hoops_GRRCR ("edge patterns"),			HK_EDGE_PATTERN},
	{_hoops_GRRCR ("edge weights"),				HK_EDGE_WEIGHT},
	{_hoops_GRRCR ("face patterns"),			HK_FACE_PATTERN},
	{_hoops_GRRCR ("line patterns"),			HK_LINE_PATTERN},
	{_hoops_GRRCR ("line weights"),				HK_LINE_WEIGHT},
	{_hoops_GRRCR ("marker sizes"),				HK_MARKER_SIZE},
	{_hoops_GRRCR ("marker symbols"),			HK_MARKER_SYMBOL},
	{_hoops_GRRCR ("modelling matrices"),		HK_MODELLING_MATRIX},
	{_hoops_GRRCR ("text alignments"),			HK_TEXT_ALIGNMENT},
	{_hoops_GRRCR ("text fonts"),				HK_TEXT_FONT},
	{_hoops_GRRCR ("text paths"),				HK_TEXT_PATH},
	{_hoops_GRRCR ("text spacings"),			HK_TEXT_SPACING},
	{_hoops_GRRCR ("texture matrices"),			HK_TEXTURE_MATRIX},
	{_hoops_GRRCR ("local textures"),			_hoops_IPAIR},
	{_hoops_GRRCR ("texture definitions"),		_hoops_IPAIR},
	{_hoops_GRRCR ("user values"),				HK_USER_VALUE},
	{_hoops_GRRCR ("window patterns"),			HK_WINDOW_PATTERN},
	{_hoops_GRRCR ("texture definitions"),		_hoops_IPAIR},
	{_hoops_GRRCR ("local textures"),			_hoops_IPAIR},
	{_hoops_GRRCR ("glyph definitions"),		_hoops_RAAIR},
	{_hoops_GRRCR ("line pattern definitions"), _hoops_RPAIR},
	{_hoops_GRRCR ("line style definitions"),	_hoops_RPAIR},
	{_hoops_GRRCR ("named style definitions"),	_hoops_HAAIR},
	{_hoops_GRRCR ("conditions"),				_hoops_CPPIR},
	{_hoops_GRRCR ("circles"),					_hoops_SGCP},
	{_hoops_GRRCR ("circular arcs"),			_hoops_RIIP},
	{_hoops_GRRCR ("circular chords"),			_hoops_GRCP},
	{_hoops_GRRCR ("circular wedges"),			_hoops_RRCP},
	{_hoops_GRRCR ("cutting planes"),			_hoops_HGPGR},
	{_hoops_GRRCR ("cutting sections"),			_hoops_HGPGR},
	{_hoops_GRRCR ("lights"),					_hoops_ICIP},
	{_hoops_GRRCR ("ellipses"),					_hoops_CGCP},
	{_hoops_GRRCR ("elliptical arcs"),			_hoops_GIIP},
	{_hoops_GRRCR ("grids"),					_hoops_GGCP},
	{_hoops_GRRCR ("lines"),					_hoops_PIIP},
	{_hoops_GRRCR ("markers"),					_hoops_PCIP},
	{_hoops_GRRCR ("meshes"),					_hoops_GSIP},
	{_hoops_GRRCR ("images"),					_hoops_HGCP},
	{_hoops_GRRCR ("pixel arrays"),				_hoops_HGCP},
	{_hoops_GRRCR ("polylines"),				_hoops_IIIP},
	{_hoops_GRRCR ("polygons"),					_hoops_RCIP},
	{_hoops_GRRCR ("shells"),					_hoops_SCIP},
	{_hoops_GRRCR ("string cursors"),			HK_STRING_CURSOR},
	{_hoops_GRRCR ("nurbs curves"),				_hoops_CHIP},
	{_hoops_GRRCR ("nurbs surfaces"),			_hoops_PRCP},
	{_hoops_GRRCR ("cylinders"),				_hoops_ASIP},
	{_hoops_GRRCR ("polycylinders"),			_hoops_CSIP},
	{_hoops_GRRCR ("spheres"),					_hoops_HSIP},
	{_hoops_GRRCR ("references"),				_hoops_AHIP},
	{_hoops_GRRCR ("reference geometries"),		_hoops_AHIP},
	{_hoops_GRRCR ("geometry references"),		_hoops_AHIP},
	{_hoops_GRRCR ("includes"),					_hoops_AGRPR},
	{_hoops_GRRCR ("include segments"),			_hoops_AGRPR},
	{_hoops_GRRCR ("segment includes"),			_hoops_AGRPR},
	{_hoops_GRRCR ("segments"),					_hoops_IRCP},
	{_hoops_GRRCR ("infinite lines"),			_hoops_SIIP},
	{_hoops_GRRCR ("infinite rays"),			_hoops_GCAPP},

	{_hoops_GRRCR ("normals"),					_hoops_RCICA},
	{_hoops_GRRCR ("parameters"),				_hoops_PCICA},
	{_hoops_GRRCR ("face attributes"),			_hoops_RCAPP},
	{_hoops_GRRCR ("face colors"),				_hoops_ACAPP},
	{_hoops_GRRCR ("face normals"),				_hoops_PCAPP},
	{_hoops_GRRCR ("face patterns"),			_hoops_HCAPP},
	{_hoops_GRRCR ("face visibilities"),		_hoops_ICAPP},
	{_hoops_GRRCR ("edge attributes"),			_hoops_CCAPP},
	{_hoops_GRRCR ("edge colors"),				_hoops_SCAPP},
	{_hoops_GRRCR ("edge normals"),				_hoops_GSAPP},
	{_hoops_GRRCR ("edge patterns"),			_hoops_RSAPP},
	{_hoops_GRRCR ("edge weights"),				_hoops_ASAPP},
	{_hoops_GRRCR ("edge visibilities"),		_hoops_PSAPP},
	{_hoops_GRRCR ("vertex attributes"),		_hoops_HSAPP},
	{_hoops_GRRCR ("vertex colors"),			_hoops_ISAPP},
	{_hoops_GRRCR ("vertex face colors"),		_hoops_CSAPP},
	{_hoops_GRRCR ("vertex edge colors"),		_hoops_SSAPP},
	{_hoops_GRRCR ("vertex marker colors"),		_hoops_GGPPP},
	{_hoops_GRRCR ("vertex marker rgbas"),		_hoops_RGPPP},
	{_hoops_GRRCR ("vertex normals"),			_hoops_AGPPP},
	{_hoops_GRRCR ("vertex parameters"),		_hoops_PGPPP},
	{_hoops_GRRCR ("vertex symbols"),			_hoops_HGPPP},
	{_hoops_GRRCR ("vertex sizes"),				_hoops_IGPPP},
	{_hoops_GRRCR ("vertex visibilities"),		_hoops_CGPPP},

	{_hoops_GRRCR ("face colors"),				_hoops_CSAPP},
	{_hoops_GRRCR ("edge colors"),				_hoops_SSAPP},
	{_hoops_GRRCR ("marker colors"),			_hoops_GGPPP},

	{_hoops_GRRCR ("user options"),				HK_USER_OPTIONS},
	{_hoops_GRRCR ("user indices"),				HK_USER_OPTIONS},
	{_hoops_GRRCR ("user option"),				HK_USER_OPTIONS},
	{_hoops_GRRCR ("user index"),				HK_USER_OPTIONS},
	{_hoops_GRRCR ("user data"),				HK_USER_OPTIONS},

	{_hoops_GRRCR ("variable line weight"),		HK_LINE_WEIGHT},
	{_hoops_GRRCR ("variable edge weight"),		_hoops_ASAPP},
	{_hoops_GRRCR ("variable marker size"),		HK_MARKER_SIZE},
	{_hoops_GRRCR ("variable line weights"),	HK_LINE_WEIGHT},
	{_hoops_GRRCR ("variable edge weights"),	_hoops_ASAPP},
	{_hoops_GRRCR ("variable marker sizes"),	HK_MARKER_SIZE},
	
	{_hoops_GRRCR ("level of detail"),			_hoops_AGAIR},
	{_hoops_GRRCR ("levels of detail"),			_hoops_AGAIR},
	{_hoops_GRRCR ("lod"),						_hoops_AGAIR},
	{_hoops_GRRCR ("lods"),						_hoops_AGAIR},
	{_hoops_GRRCR ("hardware resource"),		_hoops_HCIIR},
	{_hoops_GRRCR ("hardware resources"),		_hoops_HCIIR},

	{_hoops_GRRCR ("static model"),				_hoops_SGPPP},
	{_hoops_GRRCR ("static"),					_hoops_SGPPP},

	{_hoops_GRRCR ("transparency present"),		_hoops_GRPPP},

	{_hoops_GRRCR ("geometry options"),			_hoops_RRPPP},

	{_hoops_GRRCR ("bounding"),					_hoops_ARPPP},
	{_hoops_GRRCR ("bounding volume"),			_hoops_ARPPP},

	{_hoops_GRRCR ("shader"),					_hoops_PRPPP},
	{_hoops_GRRCR ("shaders"),					_hoops_PRPPP},

	{_hoops_GRRCR ("conditional action"),		_hoops_HRPPP},
	{_hoops_GRRCR ("conditional actions"),		_hoops_HRPPP},

	{_hoops_GRRCR ("named style"),				_hoops_IRPPP},
	{_hoops_GRRCR ("named styles"),				_hoops_IRPPP},
};

local void _hoops_CRPPP (
	_hoops_AIGPR *	_hoops_RIGC) 
{
	_hoops_GCIIR *		_hoops_SPHHR = _hoops_CIACR (_hoops_SRPPP);
	int						_hoops_IPSAA = _hoops_GGAPR (_hoops_SPAPP);

	while (_hoops_IPSAA != _hoops_RIII (_hoops_IPSAA))
		_hoops_IPSAA &= ~_hoops_RIII (_hoops_IPSAA);

	ZALLOC_ARRAY (_hoops_SPHHR->table, _hoops_IPSAA, _hoops_PIIIR *);
	_hoops_SPHHR->size = _hoops_IPSAA;

	HI_Decipher_Color_Type (_hoops_RIGC, "", 0);		/* _hoops_GRS _hoops_HHSA _hoops_RGAP _hoops_IIGR _hoops_GAPPP _hoops_RPP _hoops_HAR _hoops_AIAH _hoops_CPHR */

	int	count = _hoops_GGAPR (_hoops_SPAPP);

	while (count-- > 0) {
		_hoops_GCIIR *	_hoops_CIIIR = null;

		/* _hoops_GRH _hoops_PRCA _hoops_IS _hoops_GGGRA _hoops_GGR _hoops_PPPCR _hoops_PIRRR */
		switch (_hoops_SPAPP[count].type) {
			case HK_CALLBACK:				_hoops_CIIIR = _hoops_CIACR (_hoops_IIACR);	break;
			case HK_COLOR:					_hoops_CIIIR = _hoops_CIACR (_hoops_RAPPP);				break;
			case _hoops_CPPIR:				_hoops_CIIIR = _hoops_CIACR (_hoops_GGPCA);		break;
			case HK_DRIVER_OPTIONS:			_hoops_CIIIR = _hoops_CIACR (_hoops_AAPPP);	break;
			case HK_HEURISTICS:				_hoops_CIIIR = _hoops_CIACR (_hoops_PAPPP);		break;
			case HK_RENDERING_OPTIONS:		_hoops_CIIIR = _hoops_CIACR (_hoops_HAPPP); break;
			case HK_SELECTABILITY:			_hoops_CIIIR = _hoops_CIACR (_hoops_IAPPP);		break;
			case HK_TEXT_FONT:				_hoops_CIIIR = _hoops_CIACR (_hoops_CAPPP);			break;
			case HK_USER_OPTIONS:			_hoops_CIIIR = _hoops_CIACR (_hoops_SAPPP);		break;
			case HK_VISIBILITY:				_hoops_CIIIR = _hoops_CIACR (_hoops_CPSAA);		break;

			case _hoops_HRPPP:	_hoops_CIIIR = _hoops_CIACR (_hoops_SRPCA);	break;
		}

		if (_hoops_CIIIR != null) {
			_hoops_PIIIR *		_hoops_SPSAA;

			_hoops_SPSAA = HI_Define_Nice_Option (_hoops_SPHHR,
												(long)_hoops_SPAPP[count].type,
												(_hoops_HCRPR const *)&_hoops_SPAPP[count].name,
											   _hoops_GHAGA, -999, true, _hoops_CIIIR);
			_hoops_SPSAA->_hoops_RRHH |= _hoops_SIIIR;
		}
		else
			HI_Define_Nice_Option (_hoops_SPHHR,
								   (long)_hoops_SPAPP[count].type,
								   (_hoops_HCRPR const *)&_hoops_SPAPP[count].name,
								   _hoops_RRRCR, 0, true, null);
	}
}


const Karacter	_hoops_GPPPP[]	= {'u','s','e','r',' ','o','p','t','i','o','n', 0};
const Karacter	_hoops_RPPPP[]	= {'u','s','e','r',' ','o','p','t','i','o','n','s', 0};

local void _hoops_APPPP (void) {
	_hoops_GCIIR *		_hoops_SPHHR = _hoops_CIACR (_hoops_PPPPP);
	int						_hoops_IPSAA = 1;

	ZALLOC_ARRAY (_hoops_SPHHR->table, _hoops_IPSAA, _hoops_PIIIR *);
	_hoops_SPHHR->size = _hoops_IPSAA;

	KName				_hoops_HPPPP;
	_hoops_RPSAP *		_hoops_SPSAA;

	_hoops_HPPPP._hoops_IPPPP = (Karacter *)_hoops_GPPPP;
	_hoops_HPPPP.length = _hoops_GGAPR(_hoops_GPPPP) - 1;
	_hoops_SPSAA = HI_Define_Nice_KOption (_hoops_SPHHR, (long)HK_USER_OPTIONS, &_hoops_HPPPP,
										 _hoops_GHAGA, -999, true, _hoops_CIACR (_hoops_CPPPP));
	_hoops_SPSAA->_hoops_RRHH |= _hoops_SIIIR;

	_hoops_HPPPP._hoops_IPPPP = (Karacter *)_hoops_RPPPP;
	_hoops_HPPPP.length = _hoops_GGAPR(_hoops_RPPPP) - 1;
	_hoops_SPSAA = HI_Define_Nice_KOption (_hoops_SPHHR, (long)HK_USER_OPTIONS, &_hoops_HPPPP,
										 _hoops_GHAGA, -999, true, _hoops_CIACR (_hoops_CPPPP));
	_hoops_SPSAA->_hoops_RRHH |= _hoops_SIIIR;
}


GLOBAL_FUNCTION void HI_Clean_FCD (
	_hoops_RRHCA *	_hoops_ARHCA) {

	if (_hoops_ARHCA->_hoops_GAHCA.user_options.count > 0)
		FREE_ARRAY (_hoops_ARHCA->_hoops_GAHCA.user_options._hoops_GPICA, _hoops_ARHCA->_hoops_GAHCA.user_options.count, int);
	if (_hoops_ARHCA->_hoops_GAHCA.conditions.count > 0)
		FREE_ARRAY (_hoops_ARHCA->_hoops_GAHCA.conditions._hoops_GPICA, _hoops_ARHCA->_hoops_GAHCA.conditions.count, int);
	if (_hoops_ARHCA->_hoops_GAHCA._hoops_PPICA.count > 0)
		FREE_ARRAY (_hoops_ARHCA->_hoops_GAHCA._hoops_PPICA._hoops_GPICA, _hoops_ARHCA->_hoops_GAHCA._hoops_PPICA.count, int);
	if (_hoops_ARHCA->_hoops_GAHCA.callbacks.count > 0)
		FREE_ARRAY (_hoops_ARHCA->_hoops_GAHCA.callbacks._hoops_GPICA, _hoops_ARHCA->_hoops_GAHCA.callbacks.count, int);
}


GLOBAL_FUNCTION bool HI_Decipher_Type_Names (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			types,
	_hoops_RRHCA *	_hoops_ARHCA) 
{
	_hoops_CAAI (HOOPS_WORLD->_hoops_HPSAP);
	if (_hoops_CIACR (_hoops_SRPPP)->table == null)
		_hoops_CRPPP (_hoops_RIGC);
	_hoops_APAI (HOOPS_WORLD->_hoops_HPSAP);

	ZERO_STRUCT (_hoops_ARHCA, _hoops_RRHCA);
	_hoops_ARHCA->_hoops_AHHCA = true;
	for(int i=0; i<_hoops_IIGRA; ++i)
		_hoops_ARHCA->_hoops_GAHCA.color._hoops_GSHCA[i] = -1;

	Option_Value *	options = null;
	Option_Value *	_hoops_SPPPP = null;

	if (!HI_Parse_Options (_hoops_RIGC, types, _hoops_CIACR (_hoops_SRPPP), &options, _hoops_CGPCR))
		return	false;

	if ((_hoops_SPPPP = options) != null) do {
		int	id = _hoops_SPPPP->type->id;

		if (id == _hoops_GHAPP && !_hoops_SPPPP->_hoops_GCACR) {
			_hoops_ARHCA->_hoops_AHHCA = _hoops_ARHCA->_hoops_GHPPP = true;
			_hoops_ARHCA->_hoops_CPICA = _hoops_ARHCA->_hoops_SPICA = _hoops_ARHCA->_hoops_SHHCA = true;
			_hoops_ARHCA->_hoops_GAHCA._hoops_RAHCA = _hoops_RHPPP;
			_hoops_ARHCA->_hoops_GAHCA._hoops_APHCA = _hoops_AHPPP;
			_hoops_ARHCA->_hoops_GAHCA._hoops_IPHCA = _hoops_PHPPP;
		}
		else {
			if (_hoops_ARHCA->_hoops_AHHCA) {
				SET_MEMORY (&_hoops_ARHCA->_hoops_CHHCA[0],
					(1 + _hoops_HHPPP - 0) *	 sizeof(bool),
					_hoops_ARHCA->_hoops_GHPPP);

				_hoops_ARHCA->_hoops_CHHCA[HK_DRIVER] = false;

				_hoops_ARHCA->_hoops_CGR._hoops_PHHCA = _hoops_ARHCA->_hoops_GHPPP;
				_hoops_ARHCA->_hoops_CGR.point = _hoops_ARHCA->_hoops_GHPPP;
				_hoops_ARHCA->_hoops_CGR._hoops_HHHCA = _hoops_ARHCA->_hoops_GHPPP;
				_hoops_ARHCA->_hoops_CGR.area = _hoops_ARHCA->_hoops_GHPPP;
				_hoops_ARHCA->_hoops_SHHCA = _hoops_ARHCA->_hoops_GHPPP;
				if (_hoops_ARHCA->_hoops_GHPPP) {
					_hoops_ARHCA->_hoops_GAHCA._hoops_RAHCA = _hoops_RHPPP;
					_hoops_ARHCA->_hoops_GAHCA._hoops_APHCA = _hoops_AHPPP;
					_hoops_ARHCA->_hoops_GAHCA._hoops_IPHCA = _hoops_PHPPP;
				}
				else {
					_hoops_ARHCA->_hoops_GAHCA._hoops_RAHCA = 0;
					_hoops_ARHCA->_hoops_GAHCA._hoops_APHCA = 0;
					_hoops_ARHCA->_hoops_GAHCA._hoops_IPHCA = 0;
				}
				_hoops_ARHCA->_hoops_AHHCA = false;
			}

			if (id == _hoops_IHAPP) {
				if (_hoops_SPPPP->_hoops_GCACR)
					_hoops_ARHCA->_hoops_PIHCA = _hoops_AIHCA;
				else {
					_hoops_ARHCA->_hoops_PIHCA = _hoops_RIHCA;
					id = _hoops_IIIP;
				}
			}
			else if (id == _hoops_HHAPP) {
				if (_hoops_SPPPP->_hoops_GCACR)
					_hoops_ARHCA->_hoops_RAIHR = _hoops_AIHCA;
				else {
					_hoops_ARHCA->_hoops_RAIHR = _hoops_RIHCA;

					/* _hoops_CACH _hoops_RPP _hoops_IIH'_hoops_GRI _hoops_PA _hoops_AIAH _hoops_IHPPP _hoops_GPP... */
					if (_hoops_ARHCA->_hoops_CHHCA[(int)_hoops_IRCP]) {}
					else if (_hoops_ARHCA->_hoops_CHHCA[(int)_hoops_AGRPR]) {}
					else {
						int offset = _hoops_PHRIR;
						do if (_hoops_ARHCA->_hoops_CHHCA[offset]) break;
						_hoops_RGGA (--offset < _hoops_AHRIR);

						if (offset >= _hoops_AHRIR) {}
						else {
							/* _hoops_RPP _hoops_HAR, _hoops_RCRP _hoops_CAPR _hoops_CPHP _hoops_GHAR */
							_hoops_ARHCA->_hoops_CHHCA[(int)_hoops_IRCP] = true;
							_hoops_ARHCA->_hoops_CHHCA[(int)_hoops_AGRPR] = true;
							id = _hoops_AHAPP;
						}
					}
				}
			}

			if (id < _hoops_RHAGP) {
				if (_hoops_SPPPP->_hoops_GCACR) {
					_hoops_ARHCA->_hoops_CHHCA[id] = false;
					if (id == _hoops_ICIP) {
						_hoops_ARHCA->_hoops_CGR._hoops_PHHCA = false;
						_hoops_ARHCA->_hoops_CGR.point = false;
						_hoops_ARHCA->_hoops_CGR._hoops_HHHCA = false;
						_hoops_ARHCA->_hoops_CGR.area = false;
					}
					else if (id == _hoops_IPAIR)
						_hoops_ARHCA->_hoops_GAHCA._hoops_RAHCA &= ~_hoops_HPICA;
					else if (id == _hoops_CPPIR)
						_hoops_ARHCA->_hoops_GAHCA._hoops_APHCA &= ~_hoops_PPHCA;
					else if (id == HK_STYLE)
						_hoops_ARHCA->_hoops_GAHCA._hoops_IPHCA &= ~_hoops_CPHCA;
				}
				else {
					if ((_hoops_RAAGP <= id && id <= _hoops_CRCCA) ||
						id == HK_STYLE) {
						Option_Value const *	option = _hoops_SPPPP->value.option_list;

						_hoops_ARHCA->_hoops_CPICA = true;

						if (option == null) {
							if (id == _hoops_IPAIR)
								_hoops_ARHCA->_hoops_GAHCA._hoops_RAHCA |= _hoops_HPICA;
							else if (id == _hoops_CPPIR)
								_hoops_ARHCA->_hoops_GAHCA._hoops_APHCA |= _hoops_PPHCA;
							else if (id == HK_STYLE)
								_hoops_ARHCA->_hoops_GAHCA._hoops_IPHCA |= _hoops_CPHCA;
							else
								_hoops_ARHCA->_hoops_CHHCA[id] = true;
						}
						else {
							switch (id) {
								case HK_RENDERING_OPTIONS: {
									do {
										_hoops_GHGI					_hoops_CHPPP = option->type->id;
										Option_Value const *		_hoops_AHSAA = option->value.option_list;

										if ((_hoops_CHPPP & _hoops_AHGI) == _hoops_PSGAP) {
											_hoops_CHPPP &= ~_hoops_AHGI;

											if (option->_hoops_GCACR)
												_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_HSHCA &= ~_hoops_CHPPP;
											else
												_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_HSHCA |= _hoops_CHPPP;
										}
										else if (_hoops_AHSAA == null) {
											if ((_hoops_CHPPP & _hoops_AHGI) == _hoops_RSGAP) {
												if (option->_hoops_GCACR) {
													_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_ASHCA &= ~_hoops_CHPPP;
													/* _hoops_SCAC _hoops_PIS _hoops_CHHGP(_hoops_GRI) */
													switch (_hoops_CHPPP) {
														case _hoops_GSIAA:
															ZERO_STRUCT (&_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA.locks, _hoops_PIGRA);
															break;
														case _hoops_CSHCA:
															_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_SSHCA = 0;
															break;
														case _hoops_GGICA:
															_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_RGICA = 0;
															break;
														case _hoops_IGICA:
															_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_CGICA = 0;
															break;
														case _hoops_SGICA:
															_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_GRICA = 0;
															break;
														case _hoops_IRICA:
															_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_APPI = 0;
															break;
														case _hoops_CRICA:
															_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_PSRIR = 0;
															break;
														case _hoops_SRICA:
															_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_GAICA = 0;
															break;
														case _hoops_ARICA:
															_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_PRIGA = 0;
															break;
														case _hoops_RRICA:
															_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_GHSS = 0;
															break;
														case _hoops_AGICA:
															_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_PGICA = 0;
															break;
													}
												}
												else
													_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_ASHCA |= _hoops_CHPPP;
											}
											else {
												_hoops_CHPPP &= ~_hoops_AHGI;

												if (option->_hoops_GCACR)
													_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA.simple &= ~_hoops_CHPPP;
												else
													_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA.simple |= _hoops_CHPPP;
											}
										}
										else switch (_hoops_CHPPP) {
											case _hoops_GSIAA: {
												do {
													_hoops_HHAGP			flags = _hoops_AHSAA->type->id;

													if (_hoops_AHSAA->_hoops_GCACR)
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA.locks._hoops_IPPGR &= ~flags;
													else
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA.locks._hoops_IPPGR |= flags;
													/* _hoops_SIGP: _hoops_SHPPP */
												} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
											}	break;
											case _hoops_CSHCA: {
												do {
													short						flags = _hoops_AHSAA->type->id;

													if (_hoops_AHSAA->_hoops_GCACR)
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_SSHCA &= ~flags;
													else
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_SSHCA |= flags;
												} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
											}	break;
											case _hoops_GGICA: {
												do {
													_hoops_PPAAP				flags = _hoops_AHSAA->type->id;

													if (_hoops_AHSAA->_hoops_GCACR)
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_RGICA &= ~flags;
													else
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_RGICA |= flags;
												} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
											}	break;
											case _hoops_IGICA: {
												do {
													_hoops_GPCRP		flags = _hoops_AHSAA->type->id;

													if (_hoops_AHSAA->_hoops_GCACR)
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_CGICA &= ~flags;
													else
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_CGICA |= flags;
												} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
											}	break;
											case _hoops_SGICA: {
												do {
													_hoops_RRPHA				flags = _hoops_AHSAA->type->id;

													if (_hoops_AHSAA->_hoops_GCACR)
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_GRICA &= ~flags;
													else
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_GRICA |= flags;
												} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
											}	break;
											case _hoops_HRICA: {
												do {
													int						flags = _hoops_AHSAA->type->id;

													if (_hoops_AHSAA->_hoops_GCACR)
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA.geometry &= ~flags;
													else
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA.geometry |= flags;
												} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
											}	break;
											case _hoops_AGRAP: {
												do {
													_hoops_GICRP	flags = _hoops_AHSAA->type->id;

													if (_hoops_AHSAA->_hoops_GCACR)
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_IIAIR &= ~flags;
													else
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_IIAIR |= flags;
												} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
											}	break;
											case _hoops_IRICA: {
												do {
													_hoops_IHGAP		flags = _hoops_AHSAA->type->id;

													if (_hoops_AHSAA->_hoops_GCACR)
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_APPI &= ~flags;
													else
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_APPI |= flags;
												} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
											}	break;
											case _hoops_CRICA: {
												do {
													_hoops_HIGAP		flags = _hoops_AHSAA->type->id;

													if (_hoops_AHSAA->_hoops_GCACR)
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_PSRIR &= ~flags;
													else
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_PSRIR |= flags;
												} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
											}	break;
											case _hoops_SRICA: {
												do {
													_hoops_CCGAP		flags = _hoops_AHSAA->type->id;

													if (_hoops_AHSAA->_hoops_GCACR)
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_GAICA &= ~flags;
													else
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_GAICA |= flags;
												} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
											}	break;
											case _hoops_ARICA: {
												do {
													_hoops_ASSRP		flags = _hoops_AHSAA->type->id;

													if (_hoops_AHSAA->_hoops_GCACR)
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_PRIGA &= ~flags;
													else
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_PRIGA |= flags;
												} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
											}	break;
											case _hoops_RRICA: {
												do {
													_hoops_HGGAP		flags = _hoops_AHSAA->type->id;

													if (_hoops_AHSAA->_hoops_GCACR)
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_GHSS &= ~flags;
													else
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_GHSS |= flags;
												} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
											}	break;
											case _hoops_AGICA: {
												do {
													int							flags = _hoops_AHSAA->type->id;

													if (_hoops_AHSAA->_hoops_GCACR)
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_PGICA &= ~flags;
													else
														_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_PGICA |= flags;
												} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
											}	break;
										}
									} while ((option = option->next) != null);
								}	break;
								case HK_COLOR: {
									do {
										Color_Object				color_type = option->type->id;
										Option_Value const *		_hoops_AHSAA = option->value.option_list;
										int							i;

										if (_hoops_AHSAA == null) {
											if (option->_hoops_GCACR) {

												_hoops_ARHCA->_hoops_GAHCA.color.mask &= ~color_type;
												/* _hoops_SCAC _hoops_SASI _hoops_PAIP _hoops_RSHCR _hoops_IS _hoops_RH _hoops_CRSRR */
												for (i=0; i<_hoops_IIGRA; i++) {
													if (color_type == 1<<i)
														_hoops_ARHCA->_hoops_GAHCA.color._hoops_HAA[i] = 0;
												}
											}
											else
												_hoops_ARHCA->_hoops_GAHCA.color.mask |= option->type->id;
										}
										else do {
											_hoops_ARGRA			channel = _hoops_AHSAA->type->id;

											for (i=0; i<_hoops_IIGRA; i++) {
												if (BIT (color_type, 1<<i)) {
													if (_hoops_AHSAA->_hoops_GCACR)
														_hoops_ARHCA->_hoops_GAHCA.color._hoops_HAA[i] &= ~channel;
													else {
														_hoops_ARHCA->_hoops_GAHCA.color._hoops_HAA[i] |= channel;
														if(_hoops_AHSAA->_hoops_AIPCR > 0)
															_hoops_ARHCA->_hoops_GAHCA.color._hoops_GSHCA[i] = _hoops_AHSAA->value._hoops_RIARA[0];
													}
												}
											}
										} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
									} while ((option = option->next) != null);
								}	break;
								case HK_SELECTABILITY: {
									do {
										if (option->_hoops_GCACR)
											_hoops_ARHCA->_hoops_GAHCA._hoops_AAICA &= ~option->type->id;
										else
											_hoops_ARHCA->_hoops_GAHCA._hoops_AAICA |= option->type->id;
									} while ((option = option->next) != null);
								}	break;
								case HK_VISIBILITY: {
									do {
										if (option->_hoops_GCACR)
											_hoops_ARHCA->_hoops_GAHCA._hoops_RGP &= ~option->type->id;
										else
											_hoops_ARHCA->_hoops_GAHCA._hoops_RGP |= option->type->id;
									} while ((option = option->next) != null);
								}	break;
								case HK_DRIVER_OPTIONS: {
									do {
										_hoops_PCARP			_hoops_RPICA = option->type->id;
										if (BIT (_hoops_RPICA, _hoops_HAPRP)) {
											_hoops_RPICA &= ~_hoops_HAPRP;

											if (option->_hoops_GCACR)
												_hoops_ARHCA->_hoops_GAHCA._hoops_PAICA.flags &= ~_hoops_RPICA;
											else
												_hoops_ARHCA->_hoops_GAHCA._hoops_PAICA.flags |= _hoops_RPICA;
										}
										else {
											if (option->_hoops_GCACR)
												_hoops_ARHCA->_hoops_GAHCA._hoops_PAICA.values &= ~_hoops_RPICA;
											else
												_hoops_ARHCA->_hoops_GAHCA._hoops_PAICA.values |= _hoops_RPICA;
										}
									} while ((option = option->next) != null);
								}	break;
								case HK_HEURISTICS: {
									do {
										if (option->_hoops_GCACR)
											_hoops_ARHCA->_hoops_GAHCA.heuristics.mask &= ~option->type->id;
										else if (option->value.option_list == null)
											_hoops_ARHCA->_hoops_GAHCA.heuristics.mask |= option->type->id;
										else if (option->type->id == _hoops_RAIRP) {
											Option_Value *	_hoops_AHSAA = option->value.option_list;

											do {
												if (_hoops_AHSAA->_hoops_GCACR)
													_hoops_ARHCA->_hoops_GAHCA.heuristics._hoops_APH &= ~_hoops_AHSAA->type->id;
												else
													_hoops_ARHCA->_hoops_GAHCA.heuristics._hoops_APH |= _hoops_AHSAA->type->id;
											} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
										}
										else {
											Option_Value *	_hoops_AHSAA = option->value.option_list;

											do {
												if (_hoops_AHSAA->_hoops_GCACR)
													_hoops_ARHCA->_hoops_GAHCA.heuristics.mask &= ~_hoops_AHSAA->type->id;
												else
													_hoops_ARHCA->_hoops_GAHCA.heuristics.mask |= _hoops_AHSAA->type->id;
											} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
										}
									} while ((option = option->next) != null);
								}	break;
								case HK_TEXT_FONT: {
									do {
										if (option->_hoops_GCACR)
											_hoops_ARHCA->_hoops_GAHCA._hoops_CAICA &= ~option->type->id;
										else
											_hoops_ARHCA->_hoops_GAHCA._hoops_CAICA |= option->type->id;
									} while ((option = option->next) != null);
								}	break;
								case HK_USER_OPTIONS: {
									Option_Value const * _hoops_GIPPP = option;
									int						count = 0;

									do {
										++_hoops_ARHCA->_hoops_GAHCA.user_options.count;
									} while ((option = option->next) != null);

									ALLOC_ARRAY (_hoops_ARHCA->_hoops_GAHCA.user_options._hoops_GPICA,
												 _hoops_ARHCA->_hoops_GAHCA.user_options.count, int);

									option = _hoops_GIPPP;
									do {
										_hoops_ARHCA->_hoops_GAHCA.user_options._hoops_GPICA[count++] = option->type->id;
									} while ((option = option->next) != null);
								}	break;
								case _hoops_CPPIR: {
									Option_Value const * _hoops_GIPPP = option;
									int						count = 0;

									do {
										++_hoops_ARHCA->_hoops_GAHCA.conditions.count;
									} while ((option = option->next) != null);

									ALLOC_ARRAY (_hoops_ARHCA->_hoops_GAHCA.conditions._hoops_GPICA,
												 _hoops_ARHCA->_hoops_GAHCA.conditions.count, int);

									option = _hoops_GIPPP;
									do {
										_hoops_ARHCA->_hoops_GAHCA.conditions._hoops_GPICA[count++] = option->type->id;
									} while ((option = option->next) != null);
								}	break;
								case HK_CALLBACK: {
									Option_Value const * _hoops_GIPPP = option;
									int						count = 0;

									do {
										++_hoops_ARHCA->_hoops_GAHCA.callbacks.count;
									} while ((option = option->next) != null);

									ALLOC_ARRAY (_hoops_ARHCA->_hoops_GAHCA.callbacks._hoops_GPICA,
												 _hoops_ARHCA->_hoops_GAHCA.callbacks.count, int);

									option = _hoops_GIPPP;
									do {
										_hoops_ARHCA->_hoops_GAHCA.callbacks._hoops_GPICA[count++] = option->type->id;
									} while ((option = option->next) != null);
								}	break;
							}
						}
					}
					else if (_hoops_AHRIR <= id && id <= _hoops_PHRIR) {
						_hoops_ARHCA->_hoops_SPICA = true;
						_hoops_ARHCA->_hoops_CHHCA[id] = true;

						if (id == _hoops_ICIP) {
							_hoops_ARHCA->_hoops_CGR._hoops_PHHCA = true;
							_hoops_ARHCA->_hoops_CGR.point = true;
							_hoops_ARHCA->_hoops_CGR._hoops_HHHCA = true;
							_hoops_ARHCA->_hoops_CGR.area = true;
						}
					}
					else
						_hoops_ARHCA->_hoops_CHHCA[id] = true;
				}
			}
			else switch (id) {
				case _hoops_CHAPP: {
					_hoops_ARHCA->_hoops_IPICA = !_hoops_SPPPP->_hoops_GCACR;
				}	break;
				case _hoops_IIAPP: {
					_hoops_ARHCA->_hoops_GHICA = !_hoops_SPPPP->_hoops_GCACR;
				}	break;
				case _hoops_CIAPP: {
					_hoops_ARHCA->_hoops_RHICA = !_hoops_SPPPP->_hoops_GCACR;
				}	break;
				case _hoops_SIAPP: {
					_hoops_ARHCA->_hoops_PHICA = !_hoops_SPPPP->_hoops_GCACR;
				}	break;
				case _hoops_SGPPP: {
					_hoops_ARHCA->_hoops_IHICA = !_hoops_SPPPP->_hoops_GCACR;
				}	break;
				case _hoops_GRPPP: {
					_hoops_ARHCA->_hoops_HGCCA = !_hoops_SPPPP->_hoops_GCACR;
				}	break;

				case _hoops_SHAPP: {
					_hoops_ARHCA->_hoops_SSICA = !_hoops_SPPPP->_hoops_GCACR;
				}	break;
				case _hoops_GIAPP: {
					_hoops_ARHCA->_hoops_RCHCA = !_hoops_SPPPP->_hoops_GCACR;
				}	break;

				case _hoops_RIAPP: {
					_hoops_ARHCA->_hoops_CGR._hoops_PHHCA = !_hoops_SPPPP->_hoops_GCACR;
					if (_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_CHHCA[(int)_hoops_ICIP] = false;
					else
						_hoops_ARHCA->_hoops_SPICA = true;
				}	break;
				case _hoops_AIAPP: {
					_hoops_ARHCA->_hoops_CGR.point = !_hoops_SPPPP->_hoops_GCACR;
					if (_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_CHHCA[(int)_hoops_ICIP] = false;
					else
						_hoops_ARHCA->_hoops_SPICA = true;
				}	break;
				case _hoops_PIAPP: {
					_hoops_ARHCA->_hoops_CGR._hoops_HHHCA = !_hoops_SPPPP->_hoops_GCACR;
					if (_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_CHHCA[(int)_hoops_ICIP] = false;
					else
						_hoops_ARHCA->_hoops_SPICA = true;
				}	break;
				case _hoops_HIAPP: {
					_hoops_ARHCA->_hoops_CGR.area = !_hoops_SPPPP->_hoops_GCACR;
					if (_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_CHHCA[(int)_hoops_ICIP] = false;
					else
						_hoops_ARHCA->_hoops_SPICA = true;
				}	break;
				case _hoops_GCAPP: {
					_hoops_ARHCA->_hoops_SHHCA = !_hoops_SPPPP->_hoops_GCACR;
					if (_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_CHHCA[(int)_hoops_SIIP] = false;
					else
						_hoops_ARHCA->_hoops_SPICA = true;
				}	break;
				case _hoops_RRPPP: {
					_hoops_ARHCA->geometry_options = !_hoops_SPPPP->_hoops_GCACR;
				}	break;
				case _hoops_ARPPP: {
					_hoops_ARHCA->bounding = !_hoops_SPPPP->_hoops_GCACR;
				}	break;
				case _hoops_PRPPP: {
					if (_hoops_SPPPP->_hoops_GCACR) {
						_hoops_ARHCA->_hoops_GAHCA._hoops_RAHCA &= ~_hoops_GPHCA;
					}
					else {
						_hoops_ARHCA->_hoops_GAHCA._hoops_RAHCA |= _hoops_GPHCA;
						_hoops_ARHCA->_hoops_CPICA = true;
					}
				}	break;

				case _hoops_HRPPP: {
					Option_Value const *	option = _hoops_SPPPP->value.option_list;

					if (_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_GAHCA._hoops_APHCA &= ~_hoops_HPHCA;
					else if (option == null) {
						_hoops_ARHCA->_hoops_GAHCA._hoops_APHCA |= _hoops_HPHCA;
						_hoops_ARHCA->_hoops_CPICA = true;
					}
					else {
						int					count = 0;

						do {
							++_hoops_ARHCA->_hoops_GAHCA._hoops_PPICA.count;
						} while ((option = option->next) != null);

						ALLOC_ARRAY (_hoops_ARHCA->_hoops_GAHCA._hoops_PPICA._hoops_GPICA,
									 _hoops_ARHCA->_hoops_GAHCA._hoops_PPICA.count, int);

						option = _hoops_SPPPP->value.option_list;
						do {
							_hoops_ARHCA->_hoops_GAHCA._hoops_PPICA._hoops_GPICA[count++] = option->type->id;
						} while ((option = option->next) != null);
						_hoops_ARHCA->_hoops_CPICA = true;
					}
				}	break;

				case _hoops_IRPPP: {
					if (_hoops_SPPPP->_hoops_GCACR) {
						_hoops_ARHCA->_hoops_GAHCA._hoops_IPHCA &= ~_hoops_SPHCA;
					}
					else {
						_hoops_ARHCA->_hoops_GAHCA._hoops_IPHCA |= _hoops_SPHCA;
						_hoops_ARHCA->_hoops_CPICA = true;
					}
				}	break;

				case _hoops_RCAPP: {
					_hoops_ARHCA->_hoops_RIPPP =
						_hoops_ARHCA->_hoops_RGHIR._hoops_PAGI =
						_hoops_ARHCA->_hoops_RGHIR._hoops_PRHH =
						_hoops_ARHCA->_hoops_RGHIR.face_patterns =
						_hoops_ARHCA->_hoops_RGHIR._hoops_AIPPP = !_hoops_SPPPP->_hoops_GCACR;
				}	break;
				case _hoops_CCAPP: {
					_hoops_ARHCA->_hoops_PIPPP =
						_hoops_ARHCA->_hoops_RGHIR._hoops_ASHA =
						_hoops_ARHCA->_hoops_RGHIR._hoops_RSHA =
						_hoops_ARHCA->_hoops_RGHIR._hoops_HIPPP =
						_hoops_ARHCA->_hoops_RGHIR._hoops_IIPPP =
						_hoops_ARHCA->_hoops_RGHIR._hoops_CIPPP = !_hoops_SPPPP->_hoops_GCACR;
				}	break;
				case _hoops_HSAPP: {
					_hoops_ARHCA->any_vertex_attributes =
						_hoops_ARHCA->_hoops_SIPPP =
						_hoops_ARHCA->_hoops_RGHIR._hoops_GCPPP =
						_hoops_ARHCA->_hoops_RGHIR._hoops_RCPPP =
						_hoops_ARHCA->_hoops_RGHIR._hoops_ACPPP =
						_hoops_ARHCA->_hoops_RGHIR._hoops_PCPPP =
						_hoops_ARHCA->_hoops_RGHIR._hoops_ICHA =
						_hoops_ARHCA->_hoops_RGHIR._hoops_ACICA =
						_hoops_ARHCA->_hoops_RGHIR._hoops_HCPPP =
						_hoops_ARHCA->_hoops_RGHIR._hoops_ICPPP =
						_hoops_ARHCA->_hoops_RGHIR._hoops_CCPPP = !_hoops_SPPPP->_hoops_GCACR;
				}	break;

				case _hoops_ACAPP: {
					_hoops_ARHCA->_hoops_RGHIR._hoops_PAGI = !_hoops_SPPPP->_hoops_GCACR;
					if (!_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_SCPPP =
						_hoops_ARHCA->_hoops_RIPPP = true;
				}	break;
				case _hoops_PCAPP: {
					_hoops_ARHCA->_hoops_RGHIR._hoops_PRHH = !_hoops_SPPPP->_hoops_GCACR;
					if (!_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_SCPPP =
						_hoops_ARHCA->_hoops_RIPPP = true;
				}	break;
				case _hoops_HCAPP: {
					_hoops_ARHCA->_hoops_RGHIR.face_patterns = !_hoops_SPPPP->_hoops_GCACR;
					if (!_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_SCPPP =
						_hoops_ARHCA->_hoops_RIPPP = true;
				}	break;
				case _hoops_ICAPP: {
					_hoops_ARHCA->_hoops_RGHIR._hoops_AIPPP = !_hoops_SPPPP->_hoops_GCACR;
					if (!_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_SCPPP =
						_hoops_ARHCA->_hoops_RIPPP = true;
				}	break;
				case _hoops_SCAPP: {
					_hoops_ARHCA->_hoops_RGHIR._hoops_ASHA = !_hoops_SPPPP->_hoops_GCACR;
					if (!_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_SCPPP =
						_hoops_ARHCA->_hoops_PIPPP = true;
				}	break;
				case _hoops_GSAPP: {
					_hoops_ARHCA->_hoops_RGHIR._hoops_RSHA = !_hoops_SPPPP->_hoops_GCACR;
					if (!_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_SCPPP =
						_hoops_ARHCA->_hoops_PIPPP = true;
				}	break;
				case _hoops_RSAPP: {
					_hoops_ARHCA->_hoops_RGHIR._hoops_HIPPP = !_hoops_SPPPP->_hoops_GCACR;
					if (!_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_SCPPP =
						_hoops_ARHCA->_hoops_PIPPP = true;
				}	break;
				case _hoops_ASAPP: {
					_hoops_ARHCA->_hoops_RGHIR._hoops_IIPPP = !_hoops_SPPPP->_hoops_GCACR;
					if (!_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_SCPPP =
						_hoops_ARHCA->_hoops_PIPPP = true;
				}	break;
				case _hoops_PSAPP: {
					_hoops_ARHCA->_hoops_RGHIR._hoops_CIPPP = !_hoops_SPPPP->_hoops_GCACR;
					if (!_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_SCPPP =
						_hoops_ARHCA->_hoops_PIPPP = true;
				}	break;
				case _hoops_ISAPP: {
					_hoops_ARHCA->_hoops_SIPPP =
						_hoops_ARHCA->_hoops_RGHIR._hoops_GCPPP =
						_hoops_ARHCA->_hoops_RGHIR._hoops_RCPPP =
						_hoops_ARHCA->_hoops_RGHIR._hoops_ACPPP =
						_hoops_ARHCA->_hoops_RGHIR._hoops_PCPPP = !_hoops_SPPPP->_hoops_GCACR;
					if (!_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_SCPPP =
						_hoops_ARHCA->any_vertex_attributes = true;
				}	break;
				case _hoops_CSAPP: {
					_hoops_ARHCA->_hoops_RGHIR._hoops_GCPPP = !_hoops_SPPPP->_hoops_GCACR;
					if (!_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_SCPPP =
						_hoops_ARHCA->any_vertex_attributes =
						_hoops_ARHCA->_hoops_SIPPP = true;
				}	break;
				case _hoops_SSAPP: {
					_hoops_ARHCA->_hoops_RGHIR._hoops_RCPPP = !_hoops_SPPPP->_hoops_GCACR;
					if (!_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_SCPPP =
						_hoops_ARHCA->any_vertex_attributes =
						_hoops_ARHCA->_hoops_SIPPP = true;
				}	break;
				case _hoops_GGPPP: {
					_hoops_ARHCA->_hoops_RGHIR._hoops_ACPPP = !_hoops_SPPPP->_hoops_GCACR;
					if (!_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_SCPPP =
						_hoops_ARHCA->any_vertex_attributes =
						_hoops_ARHCA->_hoops_SIPPP = true;
				}	break;
				case _hoops_RGPPP: {
					_hoops_ARHCA->_hoops_RGHIR._hoops_PCPPP = !_hoops_SPPPP->_hoops_GCACR;
					if (!_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_SCPPP =
						_hoops_ARHCA->any_vertex_attributes =
						_hoops_ARHCA->_hoops_SIPPP = true;
				}	break;
				case _hoops_AGPPP: {
					_hoops_ARHCA->_hoops_RGHIR._hoops_ICHA = !_hoops_SPPPP->_hoops_GCACR;
					if (!_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_SCPPP =
						_hoops_ARHCA->any_vertex_attributes = true;
				}	break;
				case _hoops_PGPPP: {
					_hoops_ARHCA->_hoops_RGHIR._hoops_ACICA = !_hoops_SPPPP->_hoops_GCACR;
					if (!_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_SCPPP =
						_hoops_ARHCA->any_vertex_attributes = true;
				}	break;
				case _hoops_HGPPP: {
					_hoops_ARHCA->_hoops_RGHIR._hoops_HCPPP = !_hoops_SPPPP->_hoops_GCACR;
					if (!_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_SCPPP =
						_hoops_ARHCA->any_vertex_attributes = true;
				}	break;
				case _hoops_IGPPP: {
					_hoops_ARHCA->_hoops_RGHIR._hoops_ICPPP = !_hoops_SPPPP->_hoops_GCACR;
					if (!_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_SCPPP =
						_hoops_ARHCA->any_vertex_attributes = true;
				}	break;
				case _hoops_CGPPP: {
					_hoops_ARHCA->_hoops_RGHIR._hoops_CCPPP = !_hoops_SPPPP->_hoops_GCACR;
					if (!_hoops_SPPPP->_hoops_GCACR)
						_hoops_ARHCA->_hoops_SCPPP =
						_hoops_ARHCA->any_vertex_attributes = true;
				}	break;
				case _hoops_RCICA: {
					_hoops_ARHCA->_hoops_RGHIR._hoops_ICHA = !_hoops_SPPPP->_hoops_GCACR;
					_hoops_ARHCA->_hoops_RGHIR._hoops_PRHH = !_hoops_SPPPP->_hoops_GCACR;
				}	break;
				case _hoops_PCICA: {
					_hoops_ARHCA->_hoops_RGHIR._hoops_ACICA = !_hoops_SPPPP->_hoops_GCACR;
				}	break;

				default: {
					int first, _hoops_SSAC;

					switch (id) {
						case _hoops_GHAPP: {
							_hoops_SSAC = _hoops_HHPPP;
							first = 0;
							_hoops_ARHCA->_hoops_CPICA = !_hoops_SPPPP->_hoops_GCACR;
							_hoops_ARHCA->_hoops_SPICA = !_hoops_SPPPP->_hoops_GCACR;
						}	break;

						case _hoops_AHAPP: {
							_hoops_SSAC = _hoops_PHRIR;
							first = _hoops_AHRIR;
							_hoops_ARHCA->_hoops_SPICA = _hoops_ARHCA->_hoops_SHHCA = !_hoops_SPPPP->_hoops_GCACR;
						}	break;

						case _hoops_RHAPP: {
							_hoops_ARHCA->_hoops_CHHCA[(int)_hoops_GRAIR] = !_hoops_SPPPP->_hoops_GCACR;
							_hoops_SSAC = _hoops_CRCCA;
							first = _hoops_RAAGP;
							_hoops_ARHCA->_hoops_CPICA = !_hoops_SPPPP->_hoops_GCACR;
							_hoops_ARHCA->geometry_options = !_hoops_SPPPP->_hoops_GCACR;
						}	break;

						case _hoops_PHAPP: {
							_hoops_SSAC = _hoops_IHRIR;
							first = _hoops_IISIR;
						}	break;


						default: {
							_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unrecognized contents search flag");
							_hoops_SSAC = 0;
							first = 1;
						}	break;
					}

					if (first <= _hoops_ICIP && _hoops_ICIP <= _hoops_SSAC) {
						_hoops_ARHCA->_hoops_CGR._hoops_PHHCA =
							_hoops_ARHCA->_hoops_CGR.point =
							_hoops_ARHCA->_hoops_CGR._hoops_HHHCA =
							_hoops_ARHCA->_hoops_CGR.area = !_hoops_SPPPP->_hoops_GCACR;
					}

					SET_MEMORY (&_hoops_ARHCA->_hoops_CHHCA[first], (_hoops_SSAC - first + 1) * sizeof(bool), !_hoops_SPPPP->_hoops_GCACR);

					if (first <= _hoops_IPAIR && _hoops_SSAC >= _hoops_IPAIR) {
						if (_hoops_SPPPP->_hoops_GCACR)
							_hoops_ARHCA->_hoops_GAHCA._hoops_RAHCA &= ~_hoops_RHPPP;
						else
							_hoops_ARHCA->_hoops_GAHCA._hoops_RAHCA |= _hoops_RHPPP;
					}
					if (first <= _hoops_CPPIR && _hoops_SSAC >= _hoops_CPPIR) {
						if (_hoops_SPPPP->_hoops_GCACR)
							_hoops_ARHCA->_hoops_GAHCA._hoops_APHCA &= ~_hoops_AHPPP;
						else
							_hoops_ARHCA->_hoops_GAHCA._hoops_APHCA |= _hoops_AHPPP;
					}
					if (first <= HK_STYLE && _hoops_SSAC >= HK_STYLE) {
						if (_hoops_SPPPP->_hoops_GCACR)
							_hoops_ARHCA->_hoops_GAHCA._hoops_IPHCA &= ~_hoops_PHPPP;
						else
							_hoops_ARHCA->_hoops_GAHCA._hoops_IPHCA |= _hoops_PHPPP;
					}
				}	break;
			}
		}
	} while ((_hoops_SPPPP = _hoops_SPPPP->next) != null);

	HI_Free_Option_List (_hoops_RIGC, options);

	return	true;
}

GLOBAL_FUNCTION bool HI_Decipher_Unicode_Type_Names (
	_hoops_AIGPR *		_hoops_RIGC,
	Karacter const *			types,
	_hoops_RRHCA *		_hoops_ARHCA) 
{


	_hoops_CAAI (HOOPS_WORLD->_hoops_HPSAP);
	if (_hoops_CIACR (_hoops_PPPPP)->table == null)
		_hoops_APPPP ();
	_hoops_APAI (HOOPS_WORLD->_hoops_HPSAP);

	ZERO_STRUCT (_hoops_ARHCA, _hoops_RRHCA);

	Option_Value *	options = null;
	Option_Value *	_hoops_SPPPP = null;

	if (!HI_Parse_KOptions (_hoops_RIGC, types, _hoops_CIACR (_hoops_PPPPP), &options, _hoops_CGPCR))
		return	false;

	if ((_hoops_SPPPP = options) != null) do {
		int						id = _hoops_SPPPP->type->id;
		Option_Value const *	option = _hoops_SPPPP->value.option_list;

		_hoops_ARHCA->_hoops_CPICA = true;

		if (option == null)
			_hoops_ARHCA->_hoops_CHHCA[id] = true;
		else {
			Option_Value const *	_hoops_GIPPP = option;
			int						count = 0;

			do {
				++_hoops_ARHCA->_hoops_GAHCA.user_options.count;
			} while ((option = option->next) != null);

			ALLOC_ARRAY (_hoops_ARHCA->_hoops_GAHCA.user_options._hoops_GPICA,
				_hoops_ARHCA->_hoops_GAHCA.user_options.count, int);

			option = _hoops_GIPPP;
			do {
				_hoops_ARHCA->_hoops_GAHCA.user_options._hoops_GPICA[count++] = option->type->id;
			} while ((option = option->next) != null);
		}
	} while ((_hoops_SPPPP = _hoops_SPPPP->next) != null);

	HI_Free_Option_List (_hoops_RIGC, options);

	return	true;
}


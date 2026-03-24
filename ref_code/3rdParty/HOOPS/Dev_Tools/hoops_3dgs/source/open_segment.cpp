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
 * $Id: obf_tmp.txt 1.70 2010-11-18 00:59:02 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "searchh.h"
#include "hi_proto.h"
#include "hc_proto.h"
#include "hpserror.h"



#define m(x)		_hoops_GGCAA(x)

#define	_hoops_RGIHC		m(HK_USER_OPTIONS) | m(HK_USER_VALUE)
#define	_hoops_AGIHC		_hoops_RGIHC |		m(HK_COLOR)

#if 0
#define	_hoops_PGIHC	_hoops_AGIHC |	m(HK_RENDERING_OPTIONS) | m(HK_HEURISTICS) |	\
	m(HK_VISIBILITY) | m(HK_SELECTABILITY) |		\
	m(HK_MODELLING_MATRIX) | m(HK_TEXTURE_MATRIX) |	\
	m(HK_CALLBACK) | m(HK_CLIP_REGION)
#endif

#define	_hoops_HGIHC		m(HK_EDGE_PATTERN) | m(HK_EDGE_WEIGHT)
#define	_hoops_IGIHC		m(HK_FACE_PATTERN)
#define	_hoops_CGIHC		m(HK_LINE_PATTERN) | m(HK_LINE_WEIGHT)
#define	_hoops_SGIHC		m(HK_MARKER_SYMBOL) | m(HK_MARKER_SIZE)
#define	_hoops_GRIHC		m(HK_TEXT_ALIGNMENT) | m(HK_TEXT_FONT) | m(HK_TEXT_PATH) | m(HK_TEXT_SPACING) | m(HK_MODELLING_MATRIX)
#define _hoops_RRIHC  _hoops_AGIHC | _hoops_GRIHC | m(HK_MODELLING_MATRIX) | _hoops_SGIHC | _hoops_CGIHC | m(HK_VISIBILITY)

local Integer32 const _hoops_ARIHC[] = {
	/* _hoops_PRIHC		*/	_hoops_RGIHC,
	/* _hoops_HRIHC				*/	_hoops_AGIHC,
	/* _hoops_HGCPR				*/	_hoops_AGIHC, /* _hoops_IRIHC | _hoops_CRIHC | _hoops_SRIHC | _hoops_GAIHC, */
	/* _hoops_GSHPR				*/	_hoops_AGIHC, /* _hoops_IRIHC | _hoops_CRIHC | _hoops_SRIHC | _hoops_GAIHC, */
	/* _hoops_RAIHC				*/	_hoops_RGIHC,	/* _hoops_IRIHC | _hoops_CRIHC | _hoops_SRIHC | _hoops_GAIHC, */
	/* _hoops_AAIHC		*/	_hoops_RGIHC,	/* _hoops_IRIHC | _hoops_CRIHC | _hoops_SRIHC, */
	/* _hoops_PAIHC			*/	_hoops_RGIHC,	/* _hoops_IRIHC | _hoops_CRIHC | _hoops_SRIHC, */
	/* _hoops_HAIHC		*/	_hoops_RGIHC,	/* _hoops_IRIHC | _hoops_CRIHC | _hoops_SRIHC, */
	/* _hoops_IAIHC			*/	_hoops_RGIHC,	/* _hoops_IRIHC | _hoops_CRIHC | _hoops_SRIHC, */
	/* _hoops_SAGIA			*/	_hoops_RGIHC,	/* _hoops_IRIHC | _hoops_CRIHC | _hoops_SRIHC, */
	/* _hoops_GPGIA			*/	_hoops_RGIHC,	/* _hoops_IRIHC | _hoops_CRIHC | _hoops_SRIHC, */
	/* _hoops_APGIA	*/	_hoops_RGIHC,	/* _hoops_IRIHC | _hoops_CRIHC | _hoops_SRIHC, */
	/* _hoops_PPGIA	*/	_hoops_RGIHC,	/* _hoops_IRIHC | _hoops_CRIHC | _hoops_SRIHC, */
	/* _hoops_RPGIA			*/	_hoops_RGIHC,	/* _hoops_IRIHC | _hoops_CRIHC | _hoops_SRIHC, */
	/* _hoops_HGIRC				*/	_hoops_RGIHC,	/* _hoops_IRIHC | _hoops_CAIHC, */
	/* _hoops_IGIRC			*/	0,		/* _hoops_SGCRP, _hoops_SSSCP _hoops_RAP _hoops_GPP _hoops_SCH */
	/* _hoops_CGIRC			*/	_hoops_RGIHC,	/* _hoops_IRIHC | _hoops_CAIHC, */
	/* _hoops_SAIHC		*/	_hoops_RGIHC,	/* _hoops_IRIHC | _hoops_CAIHC, */
	/* _hoops_GPIHC		*/	_hoops_RGIHC,	/* _hoops_IRIHC | _hoops_CAIHC, */
	/* _hoops_RPIHC	*/	_hoops_RGIHC,	/* _hoops_IRIHC | _hoops_CAIHC, */
	/* _hoops_APIHC		*/	_hoops_RGIHC,	/* _hoops_IRIHC | _hoops_CAIHC, */
	/* _hoops_PPIHC				*/	_hoops_RGIHC,	/* _hoops_IRIHC, */
	/* _hoops_HPIHC			*/	_hoops_RGIHC,	/* _hoops_IRIHC | _hoops_GAIHC, */
	/* _hoops_IPIHC		*/	0,		/* _hoops_SGCRP, _hoops_SSSCP _hoops_RAP _hoops_GPP _hoops_SCH */
	/* _hoops_CPIHC				*/	_hoops_AGIHC | _hoops_GRIHC,	/* _hoops_SPIHC | _hoops_GHIHC, */
	/* _hoops_RHIHC		*/	_hoops_RGIHC,	/* _hoops_SPIHC | _hoops_GHIHC, */
	/* _hoops_AHIHC*/	_hoops_RRIHC, /* _hoops_CGH _hoops_RGR _hoops_SHH _hoops_SPIHC _hoops_PAR _hoops_RRI? */
	/* _hoops_IPPPH	*/	0,		/* _hoops_SGCRP, _hoops_SSSCP _hoops_RAP _hoops_GPP _hoops_SCH */
};


local int const	_hoops_PHIHC[] = {
	0,
	_hoops_AGPGR(_hoops_SCIP)|_hoops_AGPGR(_hoops_GSIP)|_hoops_AGPGR(_hoops_CSIP),
	_hoops_AGPGR(_hoops_SCIP)|_hoops_AGPGR(_hoops_GSIP),
	_hoops_AGPGR(_hoops_SCIP)|_hoops_AGPGR(_hoops_GSIP)|_hoops_AGPGR(_hoops_CSIP)|_hoops_AGPGR(_hoops_AHIP),
	_hoops_AGPGR(_hoops_SGCP)|_hoops_AGPGR(_hoops_RIIP)|_hoops_AGPGR(_hoops_GRCP)|_hoops_AGPGR(_hoops_RRCP),
	_hoops_AGPGR(_hoops_SGCP)|_hoops_AGPGR(_hoops_RIIP)|_hoops_AGPGR(_hoops_GRCP)|_hoops_AGPGR(_hoops_RRCP)|
	_hoops_AGPGR(_hoops_CGCP)|_hoops_AGPGR(_hoops_GIIP)|_hoops_AGPGR(_hoops_CHIP)|_hoops_AGPGR(_hoops_CHIP),
	_hoops_AGPGR(_hoops_AGCP),
	_hoops_AGPGR(_hoops_CSIP),
	_hoops_AGPGR(_hoops_SGCP),
	_hoops_AGPGR(_hoops_SCIP),
	_hoops_AGPGR(_hoops_GSIP),
	_hoops_AGPGR(_hoops_RIIP),
	_hoops_AGPGR(_hoops_RRCP),
	_hoops_AGPGR(_hoops_HGPGR),
	_hoops_AGPGR(_hoops_ICIP),
	_hoops_AGPGR(_hoops_ICIP),
	_hoops_AGPGR(_hoops_CGCP),
	_hoops_AGPGR(_hoops_GIIP),
	_hoops_AGPGR(_hoops_SIIP),
	_hoops_AGPGR(_hoops_PIIP)|_hoops_AGPGR(_hoops_HIIP),
	_hoops_AGPGR(_hoops_PCIP)|_hoops_AGPGR(_hoops_PIRS),
	_hoops_AGPGR(_hoops_CHIP),
	_hoops_AGPGR(_hoops_PRCP),
	_hoops_AGPGR(_hoops_RCIP),
	_hoops_AGPGR(_hoops_HSIP),
	_hoops_AGPGR(_hoops_IIIP)
};


GLOBAL_FUNCTION bool HI_Check_Geometry_Attribute_Type(
	_hoops_AIGPR *	_hoops_RIGC,
	Geometry const *		geo,
	Type					type)
{
	if (_hoops_GGAPR(_hoops_ARIHC) != _hoops_PHRIR-_hoops_AHRIR+1) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "geometry->attribute table invalid");
	}

	if (!BIT (_hoops_ARIHC[(int)(geo->type - _hoops_AHRIR)], _hoops_GGCAA(type))) {
		char	_hoops_HHIHC[64], _hoops_IHIHC[64];
		HI_Show_Type_Name (type, _hoops_HHIHC, _hoops_GGAPR(_hoops_HHIHC));
		HI_Show_Type_Name (geo->type, _hoops_IHIHC, _hoops_GGAPR(_hoops_IHIHC));
		HE_ERROR (HEC_ATTRIBUTE, HES_CANNOT_SET_ATTRIBUTE,
			_hoops_IAIGI (_hoops_RIGC, null, "Can not set a '%s' on an open '%s'", _hoops_HHIHC, _hoops_IHIHC));
		return false;
	}

	return true;
}

GLOBAL_FUNCTION bool HI_Check_Geo_Mask_Type(
	_hoops_AIGPR *	_hoops_RIGC,
	Geometry const *		geo,
	int						_hoops_CHIHC)
{
	if (!BIT (_hoops_AGPGR(geo->type), _hoops_CHIHC)) {
		char	_hoops_IHIHC[64];
		HI_Show_Type_Name (geo->type, _hoops_IHIHC, _hoops_GGAPR(_hoops_IHIHC));
		HE_ERROR (HEC_INVALID_KEY, HES_INVALID_KEY,
			_hoops_GIRHH(_hoops_RIGC, null, "Can't perform action on '%s'", _hoops_IHIHC));
		return false;
	}

	return true;
}

GLOBAL_FUNCTION _hoops_IPRRA HI_Anything_To_Open_Type(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH const *		item,
	_hoops_CRCP **				_hoops_SRCP,
	Geometry **				geo,
	_hoops_SIRIR **			_hoops_ASSIH)
{
	UNREFERENCED(_hoops_RIGC);

	_hoops_IPRRA	_hoops_GCRIR = _hoops_RRGPP;

	if (item->type == _hoops_IRCP) {
		_hoops_GCRIR = _hoops_RCRIR;
		if (_hoops_SRCP != null)
			*_hoops_SRCP = (_hoops_CRCP *)item;
	}
	else if (item->type >= _hoops_AHRIR && item->type <= _hoops_PHRIR) {
		_hoops_GCRIR = _hoops_HCRIR;
		if (geo != null)
			*geo = (Geometry *)item;
	}
	else if (item->type == _hoops_CIRIR) {
		_hoops_SIRIR *	_hoops_ASIIR = (_hoops_SIRIR *)item;
		_hoops_GCRIR = _hoops_ASIIR->_hoops_GCRIR;

		if (_hoops_ASSIH != null)
			*_hoops_ASSIH = _hoops_ASIIR;

		if (_hoops_GCRIR == _hoops_RCRIR && _hoops_SRCP != null)
			*_hoops_SRCP = _hoops_ASIIR->info.segment._hoops_IGRPR;
		else if (_hoops_GCRIR == _hoops_HCRIR && geo != null)
			*geo = _hoops_ASIIR->info.geometry._hoops_IGRPR;
	}

	return _hoops_GCRIR;
}


GLOBAL_FUNCTION  _hoops_HPAH * HI_Find_Target_And_Lock (
	_hoops_AIGPR *	_hoops_RIGC,
	Key						key,
	_hoops_IPRRA				_hoops_HPPS)
{
	bool _hoops_SHIHC = false;

_hoops_GIIHC:
	if (!BIT(_hoops_HPPS, _hoops_SRGPP)) {

		if (_hoops_SHIHC)
			_hoops_RPPPR();
		else
			_hoops_CSPPR();
	}
	else {

		if (_hoops_SHIHC)
			_hoops_ICIIR(_hoops_RIGC);
		else
			_hoops_RSIIR(_hoops_RIGC);
	}

	_hoops_HPAH * item = (_hoops_HPAH *)_hoops_RCSSR (_hoops_RIGC, key);

	if (item == null) {
		HE_ERROR (HEC_INVALID_KEY, HES_INVALID_OPEN, "Can't perform action on key.");
		if (!BIT(_hoops_HPPS, _hoops_SRGPP))
			_hoops_IRRPR();
		return null;
	}

	if (BIT (item->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_INVALID_KEY, HES_INVALID_OPEN, "Can't perform action on deleted key.");
		if (!BIT(_hoops_HPPS, _hoops_SRGPP))
			_hoops_IRRPR();
		return null;
	}

	if (item->type == _hoops_IRCP &&
		BIT(_hoops_HPPS, _hoops_RCRIR)) {

		_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)item;

		if (!_hoops_SHIHC) {

			if (BIT(_hoops_HPPS, _hoops_HRGPP))
				; // _hoops_HCR _hoops_HRPP _hoops_CRCC _hoops_IRIGR
			else if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_AGPSA)) {
				if (!BIT(_hoops_HPPS, _hoops_SRGPP))
					_hoops_IRRPR();
				_hoops_SHIHC = true;
				goto _hoops_GIIHC;
			}
			else
				_hoops_RIGC->flags |= _hoops_PGPSA;
		}

		return (_hoops_HPAH *)_hoops_SRCP;
	}

	if (item->type >= _hoops_AHRIR && item->type <= _hoops_PHRIR &&
		BIT(_hoops_HPPS, _hoops_HCRIR)) {

		Geometry *	geo = (Geometry *)item;

		if (!_hoops_SHIHC) {
			if (BIT(_hoops_HPPS, _hoops_ARGPP)) {
				Type	_hoops_HHIHC = _hoops_RAGPP(_hoops_HPPS);

				if (!HI_Check_Geometry_Attribute_Type(_hoops_RIGC, geo, _hoops_HHIHC))
					goto FAILED;
			}
			else if (BIT(_hoops_HPPS, _hoops_PRGPP)) {
				int		_hoops_CHIHC = _hoops_HAGPP(_hoops_HPPS, _hoops_PHIHC);

				if (!HI_Check_Geo_Mask_Type(_hoops_RIGC, geo, _hoops_CHIHC))
					goto FAILED;
			}

			if (BIT(_hoops_HPPS, _hoops_HRGPP))
				; // _hoops_HCR _hoops_HRPP _hoops_CRCC _hoops_IRIGR
			else if (geo->owner != null) {
				_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)geo->owner;

				if (_hoops_SRCP->type == _hoops_IRCP) {
					if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_AGPSA)) {
						if (!BIT(_hoops_HPPS, _hoops_SRGPP))
							_hoops_IRRPR();
						_hoops_SHIHC = true;
						goto _hoops_GIIHC;
					}
					else
						_hoops_RIGC->flags |= _hoops_PGPSA;
				}
			}
			else {
				// _hoops_SPIGA _hoops_RIIHC
				if (!BIT(_hoops_HPPS, _hoops_SRGPP))
					_hoops_IRRPR();
				_hoops_SHIHC = true;
				goto _hoops_GIIHC;
			}
		}

		return (_hoops_HPAH *)geo;
	}

	ASSERT(0);

FAILED:
	if (!BIT(_hoops_HPPS, _hoops_SRGPP))
		_hoops_IRRPR();
	return null;
}



GLOBAL_FUNCTION  _hoops_HPAH * HI_Find_Target_And_Lock (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_IPRRA				_hoops_HPPS)
{

	if (_hoops_RIGC->open_list == null &&
		!HI_Find_Our_Open (_hoops_RIGC)) {
		return null;
	}

	_hoops_SIRIR const *	item = _hoops_RIGC->open_list;

	if (BIT(item->_hoops_GCRIR & _hoops_HPPS, _hoops_RCRIR)) {
		_hoops_CRCP *	_hoops_SRCP;

		if (BIT(_hoops_HPPS, _hoops_ARGPP))
			_hoops_SRCP = item->info.segment._hoops_PCRIR;
		else
			_hoops_SRCP = item->info.segment._hoops_IGRPR;

		if (BIT (_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR)) {
			HE_ERROR (HEC_INVALID_KEY, HES_INVALID_OPEN, "Can't perform action on deleted key.");
			return null;
		}

		if (BIT(_hoops_HPPS, _hoops_GSIIR) &&
			BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR)) {
			HI_Not_When_Streamed (_hoops_SRCP, "perform action.");
			return null;
		}

		if (!BIT(_hoops_HPPS, _hoops_SRGPP)) {

			if (BIT(_hoops_HPPS, _hoops_HRGPP))
				_hoops_CSPPR();
			else if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_AGPSA))
				_hoops_RPPPR();
			else {
				_hoops_RIGC->flags |= _hoops_PGPSA;
				_hoops_CSPPR();
			}
		}
		else {

			if (BIT(_hoops_HPPS, _hoops_HRGPP))
				_hoops_RSIIR(_hoops_RIGC);
			else if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_AGPSA))
				_hoops_ICIIR(_hoops_RIGC);
			else {
				_hoops_RIGC->flags |= _hoops_PGPSA;
				_hoops_RSIIR(_hoops_RIGC);
			}
		}

		return (_hoops_HPAH *)_hoops_SRCP;
	}
	else if (BIT(item->_hoops_GCRIR & _hoops_HPPS, _hoops_HCRIR)) {
		Geometry *	geo = item->info.geometry._hoops_IGRPR;

		if (BIT (geo->_hoops_RRHH, _hoops_HGAGR)) {
			HE_ERROR (HEC_INVALID_KEY, HES_INVALID_OPEN, "Can't perform action on deleted key.");
			return null;
		}

		if (BIT(_hoops_HPPS, _hoops_ARGPP)) {
			Type	_hoops_HHIHC = _hoops_RAGPP(_hoops_HPPS);

			if (!HI_Check_Geometry_Attribute_Type(_hoops_RIGC, geo, _hoops_HHIHC))
				return null;
		}
		else if (BIT(_hoops_HPPS, _hoops_PRGPP)) {
			int		_hoops_CHIHC = _hoops_HAGPP(_hoops_HPPS, _hoops_PHIHC);

			if (!HI_Check_Geo_Mask_Type(_hoops_RIGC, geo, _hoops_CHIHC))
				return null;
		}

		if (!BIT(_hoops_HPPS, _hoops_SRGPP)) {

			if (BIT(_hoops_HPPS, _hoops_HRGPP))
				_hoops_CSPPR();
			else if (geo->owner != null) {
				_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)geo->owner;

				if (_hoops_SRCP->type != _hoops_IRCP || !BIT (_hoops_SRCP->_hoops_PHSI, _hoops_AGPSA))
					_hoops_RPPPR();
				else {
					_hoops_RIGC->flags |= _hoops_PGPSA;
					_hoops_CSPPR();
				}
			}
			else
				_hoops_RPPPR();

		}
		else {

			if (BIT(_hoops_HPPS, _hoops_HRGPP))
				_hoops_RSIIR(_hoops_RIGC);
			else if (geo->owner != null) {
				_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)geo->owner;

				if (_hoops_SRCP->type != _hoops_IRCP || !BIT (_hoops_SRCP->_hoops_PHSI, _hoops_AGPSA))
					_hoops_ICIIR(_hoops_RIGC);
				else {
					_hoops_RIGC->flags |= _hoops_PGPSA;
					_hoops_RSIIR(_hoops_RIGC);
				}
			}
			else
				_hoops_ICIIR(_hoops_RIGC);

		}

		// _hoops_IHRI _hoops_ASRC _hoops_IGS _hoops_IGCI
		return (_hoops_HPAH *)geo;
	}
	else if (item->_hoops_GCRIR & _hoops_HPPS) {
		/*_hoops_IHRI*/;
	}
	else {
		char const *	_hoops_AIIHC = "???";

		switch (item->_hoops_GCRIR) {
			case _hoops_RCRIR:		_hoops_AIIHC = "Segment";	break;
			case _hoops_HCRIR:		_hoops_AIIHC = "Geometry";	break;
			case _hoops_CCRIR:			_hoops_AIIHC = "Edge";		break;
			case _hoops_SCRIR:		_hoops_AIIHC = "Vertex";		break;
			case _hoops_ICRIR:			_hoops_AIIHC = "Face";		break;
			case _hoops_RSRIR:			_hoops_AIIHC = "LOD";		break;
			case _hoops_ASRIR:			_hoops_AIIHC = "Trim";		break;
			case _hoops_GSRIR:		_hoops_AIIHC = "Region";		break;
			default: ASSERT(0); break;
		}

		HE_ERROR (HEC_INVALID_KEY, HES_INVALID_OPEN,
			Sprintf_S (null,"Can't perform action after an 'Open_%s'", _hoops_AIIHC));

		return null;
	}

	if (!BIT(_hoops_HPPS, _hoops_SRGPP)) {

		if (BIT(_hoops_HPPS, _hoops_HRGPP))
			_hoops_CSPPR();
		else 
			_hoops_RPPPR();

	}
	else {

		if (BIT(_hoops_HPPS, _hoops_HRGPP))
			_hoops_RSIIR(_hoops_RIGC);
		else 
			_hoops_ICIIR(_hoops_RIGC);

	}
		 
	return (_hoops_HPAH *)item;
}




GLOBAL_FUNCTION bool HI_Find_Our_Open (
	_hoops_AIGPR *_hoops_RIGC)
{
	local const char _hoops_PIIHC[] = "an 'Open_Segment' is needed.";

	/* _hoops_HGI _hoops_PCPH _hoops_RGIHH _hoops_IRS _hoops_SHIR _hoops_CAGH _hoops_PPR _hoops_IAGA _hoops_CRGR "_hoops_SPRS _hoops_PIGHH"
	 * _hoops_CCH, _hoops_RPP _hoops_IRPR.
	 *
	 * _hoops_HHPC _hoops_SCH _hoops_AHRPA _hoops_RH _hoops_HPRGR _hoops_HSIII.
	 */

	if (_hoops_RIGC->open_list == null) {
		if (HOOPS_WORLD->_hoops_APPSA)
			HE_ERROR (HEC_SEGMENT, HES_NO_OPEN_SEGMENT, "No open segment");
		else {
			/* _hoops_PHHR _hoops_CRGR '_hoops_SPRS-_hoops_PIGHH' _hoops_CCH */

			PUSHNAME(_hoops_RIGC);
			HC_Open_Segment ("?picture");
			POPNAME(_hoops_RIGC);

			if (_hoops_RIGC->open_list->info.segment._hoops_PCRIR == null) {
				/* _hoops_IGS _hoops_SRSH?	 _hoops_PIHA _hoops_SHH _hoops_IRS _hoops_AHCI _hoops_PHPPR */
				return false;
			}

			PUSHNAME(_hoops_RIGC);
			HC_Set_Streaming_Mode ("On");
			POPNAME(_hoops_RIGC);

			_hoops_RIGC->open_list->_hoops_RRHH |= _hoops_APAPP;

			return true;
		}
	}
	else switch (_hoops_RIGC->open_list->_hoops_GCRIR) {
		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected Open type");
		}	break;

		case _hoops_HCRIR: {
			HE_ERROR2 (HEC_GEOMETRY, HES_MOST_RECENT_OPEN, "The most recent 'open' was an 'Open_Geometry' -", _hoops_PIIHC);
		}	break;

		case _hoops_CCRIR: {
			HE_ERROR2 (HEC_EDGE, HES_MOST_RECENT_OPEN, "The most recent 'open' was an 'Open_Edge' -",_hoops_PIIHC);
		}	break;

		case _hoops_SCRIR: {
			HE_ERROR2 (HEC_VERTEX, HES_MOST_RECENT_OPEN, "The most recent 'open' was an 'Open_Vertex' -", _hoops_PIIHC);
		}	break;

		case _hoops_ICRIR: {
			HE_ERROR2 (HEC_FACE, HES_MOST_RECENT_OPEN, "The most recent 'open' was an 'Open_Face' -", _hoops_PIIHC);
		}	break;

		case _hoops_GSRIR: {
			HE_ERROR2 (HEC_FACE, HES_MOST_RECENT_OPEN, "The most recent 'open' was an 'Open_Region' -", _hoops_PIIHC);
		}	break;

		case _hoops_RCRIR: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Open segment already exists");
		}	break;
	}

	return false;
}



GLOBAL_FUNCTION void HI_Open_Segment (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP)
{
	_hoops_RSIIR(_hoops_RIGC);

	_hoops_SIRIR *	_hoops_RGGGC;

	ZALLOC (_hoops_RGGGC, _hoops_SIRIR);
	_hoops_RGGGC->type = _hoops_CIRIR;
	_hoops_RGGGC->_hoops_HIHI = 1;
	_hoops_RGGGC->owner = HOOPS_WORLD;
	_hoops_RGGGC->_hoops_GCRIR = _hoops_RCRIR;
	_hoops_RGGGC->info.segment._hoops_PCRIR = _hoops_SRCP;

	_hoops_PRRH (_hoops_SRCP);

	if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR)) {
		Attribute			*_hoops_HPHCR;

		if ((_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR) != null) do {
			if (_hoops_HPHCR->type == _hoops_GRAIR)
				break;
		} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);
		if (_hoops_HPHCR == null) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Streaming attribute missing");
			return;
		}
		_hoops_SRCP = ((_hoops_RRAIR *)_hoops_HPHCR)->_hoops_PHSCA;
	}
	_hoops_RGGGC->info.segment._hoops_IGRPR = _hoops_SRCP;
	_hoops_PRRH (_hoops_SRCP);

	_hoops_IPAPP(_hoops_RIGC, _hoops_RGGGC);
}


GLOBAL_FUNCTION void HI_Close_Segment (
	_hoops_AIGPR *	_hoops_RIGC)
{
	_hoops_SIRIR *	_hoops_AHSCA = _hoops_RIGC->open_list;

	if (_hoops_AHSCA == null || _hoops_AHSCA->_hoops_GCRIR != _hoops_RCRIR) {
		HI_Close_Complaint (_hoops_RIGC, _hoops_RCRIR);
		return;
	}

	/* _hoops_IPCA */
	_hoops_CIGPR (_hoops_RIGC, _hoops_AHSCA);
	_hoops_HPRH (_hoops_AHSCA);

	/* _hoops_SGS _hoops_CSAP _hoops_CAHPH */

	/* _hoops_IRS _hoops_PGHC _hoops_SSHHC _hoops_III _hoops_SIAS _hoops_HS _hoops_RIPPR, _hoops_HIS _hoops_SAHR _hoops_PCHIA _hoops_SCH */
	_hoops_AHSCA = _hoops_RIGC->open_list;
	if (_hoops_AHSCA == null)
;//_hoops_HIIHC(_hoops_HHAPA);	// _hoops_PAHH _hoops_IIIHC, _hoops_RSH _hoops_AAGAI _hoops_RHAP *_hoops_CPS* _hoops_HGCR _hoops_CAHC?
	else if (_hoops_AHSCA->_hoops_GCRIR == _hoops_RCRIR && _hoops_AHSCA->info.segment._hoops_ACRIR != null) {
		_hoops_HPRH (_hoops_AHSCA->info.segment._hoops_ACRIR);
		_hoops_AHSCA->info.segment._hoops_ACRIR = null;
	}
}



local char const * _hoops_HIRPH (
	int				_hoops_GCRIR)
{

	switch (_hoops_GCRIR) {
		case _hoops_RCRIR:		return "a 'segment'";
		case _hoops_HCRIR:		return "a 'geometry'";
		case _hoops_SCRIR:		return "a 'vertex'";
		case _hoops_CCRIR:			return "an 'edge'";
		case _hoops_ICRIR:			return "a 'face'";
		case _hoops_RSRIR:			return "a 'lod'";
		case _hoops_GSRIR:		return "a 'region'";

		default:   _hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected open type"); return "a '?'";
	}
}


GLOBAL_FUNCTION void HI_Close_Complaint (
	_hoops_AIGPR *	_hoops_RIGC,
	int						_hoops_SRCIH) {

	if (_hoops_RIGC->open_list == null ||
		BIT (_hoops_RIGC->open_list->_hoops_RRHH, _hoops_APAPP)) {
		HE_ERROR (HEC_SEGMENT, HES_NO_OPEN_SEGMENT, Sprintf_S (null, "Nothing open - can't Close %s", _hoops_HIRPH (_hoops_SRCIH)));
	}
	else {
		char			buf[MAX_ERRMSG];

		HE_ERROR2 (HEC_SEGMENT, HES_CANNOT_CLOSE_SEGMENT,
				Sprintf_S (null, "Can't close %s -", _hoops_HIRPH (_hoops_SRCIH)),
				   Sprintf_S (buf, "The most recent open item is %s", _hoops_HIRPH (_hoops_RIGC->open_list->_hoops_GCRIR)));
	}
}



HC_INTERFACE void HC_CDECL HC_Close_Segment (void)
{
	_hoops_PAPPR context("Close_Segment");

	CODE_GENERATION (
		HOOPS_WORLD->_hoops_ISPPR -= 2;
		HI_Dump_Code ("HC_Close_Segment ();\n");
	);

	HI_Close_Segment(context);
}


HC_INTERFACE Key HC_CDECL HC_Open_Segment (
	char const *	name)
{
	_hoops_PAPPR context("Open_Segment");

	CODE_GENERATION (
		char	_hoops_RICIA[256];
		if (name[0] == '\0') {
			Sprintf_D(_hoops_RICIA, "unnamed %d", HOOPS_WORLD->_hoops_CGHGA);
			name = _hoops_RICIA;
		}
	);

	_hoops_CSPPR();

	_hoops_CRCP *	_hoops_SRCP = HI_Create_Segment (context, null, name, true);

	if (_hoops_SRCP != null)
		HI_Open_Segment (context, _hoops_SRCP);

	_hoops_IRRPR();

	if (_hoops_SRCP == null)
		return _hoops_SHSSR;

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "DEFINE (HC_Open_Segment (%S), ", name));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_SRCP->key));
		HOOPS_WORLD->_hoops_ISPPR += 2;
	);

	return _hoops_SRCP->key;
}


HC_INTERFACE void HC_CDECL HC_Open_Segment_By_Key (
	Key			key)
{
	_hoops_PAPPR context("Open_Segment_By_Key");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Open_Segment_By_Key (LOOKUP (%D));\n", key));
		HOOPS_WORLD->_hoops_ISPPR += 2;
	);

	_hoops_CSPPR();
	_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)_hoops_RCSSR (context, key);

	if (_hoops_SRCP == null || (_hoops_SRCP->type != _hoops_IRCP && _hoops_SRCP->type != _hoops_PIRIR) || BIT(_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SEGMENT, HES_INVALID_KEY, "Provided key does not refer to a valid Segment");
	}
	else {
		if (_hoops_SRCP->type == _hoops_PIRIR)
			_hoops_SRCP = (_hoops_CRCP *)((_hoops_PGRPR *)_hoops_SRCP)->_hoops_IGRPR;

		HI_Open_Segment (context, _hoops_SRCP);
	}
	_hoops_IRRPR();
}



HC_INTERFACE Key HC_CDECL HC_Open_Segment_Key_By_Key (
	Key				parent_segment,
	char const *	child_segment_name)
{
	_hoops_PAPPR context("Open_Segment_Key_By_Key");

	CODE_GENERATION (
		char	_hoops_RICIA[256];
		if (child_segment_name[0] == '\0') {
			Sprintf_D(_hoops_RICIA, "unnamed %d", HOOPS_WORLD->_hoops_CGHGA);
			child_segment_name = _hoops_RICIA;
		}
	);

	_hoops_CSPPR();
	_hoops_CRCP *	_hoops_HAPSA = (_hoops_CRCP *)_hoops_RCSSR (context, parent_segment);

	if (_hoops_HAPSA == null || (_hoops_HAPSA->type != _hoops_IRCP &&
		_hoops_HAPSA->type != _hoops_PIRIR) || BIT(_hoops_HAPSA->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SEGMENT, HES_INVALID_KEY, "Provided key does not refer to a valid Segment");
		_hoops_IRRPR();
		return _hoops_SHSSR;
	}

	if (_hoops_HAPSA->type == _hoops_PIRIR)
		_hoops_HAPSA = (_hoops_CRCP *)((_hoops_PGRPR *)_hoops_HAPSA)->_hoops_IGRPR;

	_hoops_CRCP *	_hoops_CIIHC = HI_Create_Segment (context, _hoops_HAPSA, child_segment_name, true);

	if (_hoops_CIIHC == null)
		return _hoops_SHSSR;

	HI_Open_Segment (context, _hoops_CIIHC);

	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Open_Segment_Key_By_Key (LOOKUP (%D), ", parent_segment));
		HI_Dump_Code (Sprintf_S (null, "%S), ", child_segment_name));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CIIHC->key));
		HOOPS_WORLD->_hoops_ISPPR += 2;
	);

	return _hoops_CIIHC->key;
}




HC_INTERFACE void HC_CDECL HC_Begin_Open_Segment_Search (void)
{
	_hoops_PAPPR context("Begin_Open_Segment_Search");


#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Begin_Open_Segment_Search () */\n");
		++HOOPS_WORLD->_hoops_ISPPR;

	);

	/* _hoops_SR _hoops_HSGR _hoops_IAPR _hoops_IGS _hoops_CGSI _hoops_PGAP _hoops_SPGA'_hoops_RA _hoops_SGHC */

	_hoops_SSPPR *	_hoops_GGHPR;
	ZALLOC (_hoops_GGHPR, _hoops_SSPPR);
	_hoops_GGHPR->prev = context->_hoops_PHPGI;
	context->_hoops_PHPGI = _hoops_GGHPR;

	_hoops_CSPPR();

	_hoops_SIRIR *		_hoops_ASIIR = context->open_list;
	_hoops_AGHPR **	_hoops_ASRGR = &_hoops_GGHPR->list;
	while (_hoops_ASIIR != null) {
		if (_hoops_ASIIR->_hoops_GCRIR == _hoops_RCRIR) {
			++_hoops_GGHPR->count;
			_hoops_CRCP *		_hoops_SRCP = _hoops_ASIIR->info.segment._hoops_PCRIR;
			_hoops_AGHPR *	node;
			ZALLOC (node, _hoops_AGHPR);
			node->item = (_hoops_HPAH *)_hoops_SRCP;
			_hoops_PRRH (_hoops_SRCP);
			*_hoops_ASRGR = node;
			_hoops_ASRGR = &node->next;
		}
		_hoops_ASIIR = _hoops_ASIIR->next;
	}

	_hoops_IRRPR();
#endif
}

HC_INTERFACE bool HC_CDECL HC_Find_Open_Segment (
	char *		pathname)
{
	_hoops_PAPPR context("Find_Open_Segment");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Find_Open_Segment () */\n");
	);

	if (context->_hoops_PHPGI == null) {
		HE_ERROR (HEC_SEGMENT, HES_INACTIVE_SEARCH, "No open segment search is active");
		return false;
	}

	_hoops_AGHPR	*	list;
	_hoops_RGGA ((list = context->_hoops_PHPGI->list) == null) {
		_hoops_HPAH		*item = list->item;

		context->_hoops_PHPGI->list = list->next;
		FREE (list, _hoops_AGHPR);
		if (BIT (item->_hoops_RRHH, _hoops_HGAGR))
			_hoops_HPRH (item);
		else {
			_hoops_HPRH (item);
			HI_Return_Sprintf1 (pathname, -1, "%p", (void *)item);
			return true;
		}
	}
#endif
	return false;
}


HC_INTERFACE void HC_CDECL HC_Show_Open_Segment_Count (
	int *	count)
{
	_hoops_PAPPR context("Show_Open_Segment_Count");

	*count = 0;

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Open_Segment_Count () */\n");
	);

	if (context->_hoops_PHPGI == null)
		HE_ERROR (HEC_SEGMENT, HES_INACTIVE_SEARCH, "No open segment search is active");
	else
		*count = context->_hoops_PHPGI->count;
#endif
}


HC_INTERFACE void HC_CDECL HC_End_Open_Segment_Search (void)
{
	_hoops_PAPPR context("End_Open_Segment_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("/* HC_End_Open_Segment_Search () */\n");
	);

	_hoops_SSPPR *	_hoops_GGHPR = context->_hoops_PHPGI;
	if (_hoops_GGHPR == null) {
		HE_ERROR (HEC_SEGMENT, HES_END_WITHOUT_BEGIN_SEARCH, "End without matching Begin");
		return;
	}

	HI_Free_Search_List (context, _hoops_GGHPR->list);

	context->_hoops_PHPGI = _hoops_GGHPR->prev;
	FREE (_hoops_GGHPR, _hoops_SSPPR);
#endif
}



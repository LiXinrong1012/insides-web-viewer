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
 * $Id: obf_tmp.txt 1.136 2011-01-18 22:42:13 covey Exp $
 */

#include "hoops.h"
#include "patterns.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "tandt.h"

#define _hoops_PGHHA(x) (int)((x) + 0.5f)

#define _hoops_HAAIP(p,_hoops_IAAIP,_hoops_CAAIP,_hoops_PRAA,_hoops_HRAA,x,y,_hoops_RAC) do { \
		int _hoops_HAGR; \
		_hoops_HAGR = _hoops_SAAIP (*p); ++p; \
		if (_hoops_RAC) \
			x = (-_hoops_HAGR - _hoops_IAAIP) * _hoops_PRAA; \
		else \
			x = (_hoops_HAGR - _hoops_IAAIP) * _hoops_PRAA; \
		_hoops_HAGR = _hoops_SAAIP (*p); ++p; \
		y = (_hoops_HAGR - _hoops_CAAIP) * _hoops_HRAA; \
	} while (0)

#define _hoops_GPAIP(_hoops_RICGR,_hoops_AICGR,_hoops_IPGRP,_hoops_GGHCR,_hoops_AGHCR,_hoops_RPAIP,_hoops_APAIP) do { \
		float tx, ty; \
		tx = _hoops_RICGR + _hoops_IPGRP * _hoops_AICGR; ty = _hoops_AICGR; \
		_hoops_RPAIP = tx * _hoops_AGHCR - ty * _hoops_GGHCR; \
		_hoops_APAIP = tx * _hoops_GGHCR   + ty * _hoops_AGHCR; \
	} while (0)

#define _hoops_PPAIP(_hoops_RICGR,_hoops_AICGR,_hoops_HPAIP,_hoops_IPAIP,_hoops_IPGRP,_hoops_GGHCR,_hoops_AGHCR,_hoops_RPAIP,_hoops_APAIP) do { \
		_hoops_GPAIP (_hoops_RICGR, _hoops_AICGR, _hoops_IPGRP, _hoops_GGHCR,_hoops_AGHCR, _hoops_RPAIP, _hoops_APAIP); \
		(_hoops_RPAIP>0)?(_hoops_RPAIP=(float)_hoops_PGHHA(_hoops_RPAIP)):(_hoops_RPAIP=(float)((int)(_hoops_RPAIP-0.499f))); \
		(_hoops_APAIP>0)?(_hoops_APAIP=(float)_hoops_PGHHA(_hoops_APAIP)):(_hoops_APAIP=(float)((int)(_hoops_APAIP-0.499f))); \
		_hoops_RPAIP += _hoops_HPAIP; _hoops_APAIP += _hoops_IPAIP; \
	} while (0)

#define _hoops_CPAIP(p,_hoops_HPAIP,_hoops_IPAIP,_hoops_SPAIP,_hoops_IAAIP,_hoops_CAAIP,_hoops_PRAA,_hoops_HRAA,_hoops_IPGRP,_hoops_GGHCR,_hoops_AGHCR,x,y,z,_hoops_RAC) do { \
		float _hoops_GHAIP, _hoops_RHAIP; \
		_hoops_HAAIP (p, _hoops_IAAIP, _hoops_CAAIP, _hoops_PRAA, _hoops_HRAA, _hoops_GHAIP, _hoops_RHAIP, _hoops_RAC); \
		_hoops_PPAIP (_hoops_GHAIP, _hoops_RHAIP, _hoops_HPAIP, _hoops_IPAIP, _hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR, x, y); \
		z = _hoops_SPAIP; \
	} while (0)


struct _hoops_CRCCS {
	_hoops_CRCCS *	next;
	Net_Rendition		nr;

	struct {
		int count;
		int _hoops_SAGCA;
		DC_Point *points;
		DC_Point *_hoops_ASPS;
	} _hoops_SSRP;
 
	struct {
		int count;
		int _hoops_SAGCA;
		DC_Point *points;
		DC_Point *_hoops_ASPS;
		bool *_hoops_AGSSH;
	} ellipse;

	struct {
		int count;
		int _hoops_SAGCA;
		DC_Point *points;
		DC_Point *_hoops_ASPS;		
		int _hoops_SRCCS;
		int *lengths;
		int _hoops_GACCS;
		bool *_hoops_AGSSH;
	} polyline;
};


local INLINE _hoops_CRCCS * _hoops_RACCS(Net_Rendition const & in_nr)
{
	_hoops_CRCCS * _hoops_AACCS;
	ZALLOC(_hoops_AACCS, _hoops_CRCCS);
	_hoops_AACCS->nr = in_nr;
	return _hoops_AACCS;
}


local INLINE void _hoops_PACCS(
	_hoops_CRCCS *		_hoops_AACCS, 
	DC_Point *				pt, 
	bool					_hoops_RAIHR, 
	bool					_hoops_HACCS, 
	Int_Rectangle const *	_hoops_HHHIH)
{
	if (!_hoops_HACCS && _hoops_HHHIH) {
		if (pt->x < _hoops_HHHIH->left) {
			_hoops_HACCS=true;
		} else
		if (pt->x > _hoops_HHHIH->right) {
			_hoops_HACCS=true;
		} else
		if (pt->y < _hoops_HHHIH->bottom) {
			_hoops_HACCS=true;
		} else
		if (pt->y > _hoops_HHHIH->top) {
			_hoops_HACCS=true;
		}
	} 
	if (_hoops_RAIHR) {
		if (_hoops_HACCS && BIT (_hoops_AACCS->nr->transform_rendition->flags, _hoops_AIHS))
			_hoops_AACCS->nr.Modify()->transform_rendition.Modify()->flags &= ~_hoops_AIHS;
		_hoops_AIGGA (_hoops_AACCS->nr, 1, pt);
	} else {
		if (_hoops_AACCS->_hoops_SSRP.count+1 >= _hoops_AACCS->_hoops_SSRP._hoops_SAGCA) {
			DC_Point *_hoops_IACCS;
			int _hoops_CGCGR = _hoops_AACCS->_hoops_SSRP._hoops_SAGCA * 2 + 1;
			ALLOC_ARRAY_CACHED(_hoops_IACCS, _hoops_CGCGR, DC_Point);
			if (_hoops_AACCS->_hoops_SSRP.count) _hoops_AIGA(_hoops_AACCS->_hoops_SSRP.points, _hoops_AACCS->_hoops_SSRP.count, DC_Point, _hoops_IACCS);
			if (_hoops_AACCS->_hoops_SSRP._hoops_SAGCA) FREE_ARRAY(_hoops_AACCS->_hoops_SSRP.points, _hoops_AACCS->_hoops_SSRP._hoops_SAGCA, DC_Point);
			_hoops_AACCS->_hoops_SSRP._hoops_SAGCA = _hoops_CGCGR;
			_hoops_AACCS->_hoops_SSRP.points = _hoops_IACCS;
			_hoops_AACCS->_hoops_SSRP._hoops_ASPS=&_hoops_AACCS->_hoops_SSRP.points[_hoops_AACCS->_hoops_SSRP.count];
		}
		_hoops_AACCS->_hoops_SSRP._hoops_ASPS[0] = *pt;
		_hoops_AACCS->_hoops_SSRP._hoops_ASPS++;
		_hoops_AACCS->_hoops_SSRP.count++;
	} 
}

local INLINE void _hoops_CACCS(
	_hoops_CRCCS *		_hoops_AACCS, 
	DC_Point *				center, 
	DC_Point *				radii, 
	bool					_hoops_HIHCC, 
	bool					_hoops_RAIHR, 
	bool					_hoops_HACCS, 
	Int_Rectangle const *	_hoops_HHHIH) 
{
	if (!_hoops_HACCS && _hoops_HHHIH) {
		if (center->x - radii->x < _hoops_HHHIH->left) {
			_hoops_HACCS=true;
		} else
		if (center->x + radii->x > _hoops_HHHIH->right) {
			_hoops_HACCS=true;
		} else
		if (center->y - radii->y < _hoops_HHHIH->bottom) {
			_hoops_HACCS=true;
		} else
		if (center->y + radii->y > _hoops_HHHIH->top) {
			_hoops_HACCS=true;
		}
	}
	if (_hoops_RAIHR) {
		if (_hoops_HIHCC)
			_hoops_AAPIP (_hoops_AACCS->nr, center, radii);
		_hoops_PAPIP (_hoops_AACCS->nr, center, radii);
	} else {
		if ((_hoops_AACCS->ellipse.count+1)*2 >= _hoops_AACCS->ellipse._hoops_SAGCA) {
			DC_Point *_hoops_IACCS;
			bool *_hoops_SACCS;
			int _hoops_CGCGR = _hoops_AACCS->ellipse._hoops_SAGCA * 2 + 2;
			ALLOC_ARRAY_CACHED(_hoops_IACCS, _hoops_CGCGR, DC_Point);
			ALLOC_ARRAY_CACHED(_hoops_SACCS, _hoops_CGCGR>>1, bool);
			if (_hoops_AACCS->ellipse.count) {
				_hoops_AIGA(_hoops_AACCS->ellipse.points, _hoops_AACCS->ellipse.count*2, DC_Point, _hoops_IACCS);
				_hoops_AIGA(_hoops_AACCS->ellipse._hoops_AGSSH, _hoops_AACCS->ellipse.count, bool, _hoops_SACCS);
			}
			if (_hoops_AACCS->ellipse._hoops_SAGCA) {
				FREE_ARRAY(_hoops_AACCS->ellipse.points, _hoops_AACCS->ellipse._hoops_SAGCA, DC_Point);
				FREE_ARRAY(_hoops_AACCS->ellipse._hoops_AGSSH, _hoops_AACCS->ellipse._hoops_SAGCA>>1, bool);
			}
			_hoops_AACCS->ellipse._hoops_SAGCA = _hoops_CGCGR;
			_hoops_AACCS->ellipse.points = _hoops_IACCS;
			_hoops_AACCS->ellipse._hoops_AGSSH = _hoops_SACCS;
			_hoops_AACCS->ellipse._hoops_ASPS=&_hoops_AACCS->ellipse.points[_hoops_AACCS->ellipse.count*2];
		}
		_hoops_AACCS->ellipse._hoops_ASPS[0] = *center;
		_hoops_AACCS->ellipse._hoops_ASPS[1] = *radii;
		_hoops_AACCS->ellipse._hoops_ASPS+=2;
		_hoops_AACCS->ellipse._hoops_AGSSH[_hoops_AACCS->ellipse.count]=(_hoops_HIHCC);
		_hoops_AACCS->ellipse.count++;
	}
}

local INLINE void _hoops_GPCCS(
	_hoops_CRCCS *		_hoops_AACCS, 
	int						_hoops_PRPIP, 
	DC_Point *				_hoops_GSGGA, 
	bool					_hoops_HIHCC, 
	bool					_hoops_RAIHR, 
	bool					_hoops_HACCS, 
	Int_Rectangle const *	_hoops_HHHIH) 
{
	if (!_hoops_HACCS && _hoops_HHHIH) {

		for (int _hoops_CAASP=0;_hoops_CAASP<_hoops_PRPIP;_hoops_CAASP++) {
			if (_hoops_GSGGA[_hoops_CAASP].x < _hoops_HHHIH->left) {
				_hoops_HACCS=true;
				break;
			}
			if (_hoops_GSGGA[_hoops_CAASP].x > _hoops_HHHIH->right) {
				_hoops_HACCS=true;
				break;
			}
			if (_hoops_GSGGA[_hoops_CAASP].y < _hoops_HHHIH->bottom) {
				_hoops_HACCS=true;
				break;
			}
			if (_hoops_GSGGA[_hoops_CAASP].y > _hoops_HHHIH->top) {
				_hoops_HACCS=true;
				break;
			}
		}
	}
	if (_hoops_RAIHR) {
		if (_hoops_HACCS && BIT (_hoops_AACCS->nr->transform_rendition->flags, _hoops_AIHS))
			_hoops_AACCS->nr.Modify()->transform_rendition.Modify()->flags &= ~_hoops_AIHS;
		if (_hoops_HIHCC)
			_hoops_RSGCP (_hoops_AACCS->nr, _hoops_PRPIP-1, _hoops_GSGGA);
		_hoops_SCGGA (_hoops_AACCS->nr, _hoops_PRPIP, _hoops_GSGGA);
	} else {
		if (_hoops_AACCS->polyline._hoops_GACCS+(_hoops_PRPIP) >= _hoops_AACCS->polyline._hoops_SAGCA) {
			DC_Point *_hoops_IACCS;
			int _hoops_CGCGR = _hoops_AACCS->polyline._hoops_SAGCA * 2 + (_hoops_PRPIP);
			ALLOC_ARRAY_CACHED(_hoops_IACCS, _hoops_CGCGR, DC_Point);
			if (_hoops_AACCS->polyline._hoops_GACCS) _hoops_AIGA(_hoops_AACCS->polyline.points,
				_hoops_AACCS->polyline._hoops_GACCS, DC_Point, _hoops_IACCS);
			if (_hoops_AACCS->polyline._hoops_SAGCA) FREE_ARRAY(_hoops_AACCS->polyline.points,
				_hoops_AACCS->polyline._hoops_SAGCA, DC_Point);
			_hoops_AACCS->polyline._hoops_SAGCA = _hoops_CGCGR;
			_hoops_AACCS->polyline.points = _hoops_IACCS;
			_hoops_AACCS->polyline._hoops_ASPS=&_hoops_AACCS->polyline.points[_hoops_AACCS->polyline._hoops_GACCS];
		}
		if (_hoops_AACCS->polyline.count+1 >= _hoops_AACCS->polyline._hoops_SRCCS) {
			int *_hoops_RPCCS;
			bool *_hoops_SACCS;
			int _hoops_CGCGR = _hoops_AACCS->polyline._hoops_SRCCS * 2 + 1;
			ALLOC_ARRAY_CACHED(_hoops_RPCCS, _hoops_CGCGR, int);
			ALLOC_ARRAY_CACHED(_hoops_SACCS, _hoops_CGCGR, bool);
			if ((_hoops_AACCS)->polyline.count) {
				_hoops_AIGA(_hoops_AACCS->polyline.lengths, _hoops_AACCS->polyline.count, int, _hoops_RPCCS);
				_hoops_AIGA(_hoops_AACCS->polyline._hoops_AGSSH, _hoops_AACCS->polyline.count, bool, _hoops_SACCS);
			}
			if (_hoops_AACCS->polyline._hoops_SRCCS) {
				FREE_ARRAY(_hoops_AACCS->polyline.lengths, _hoops_AACCS->polyline._hoops_SRCCS, int);
				FREE_ARRAY(_hoops_AACCS->polyline._hoops_AGSSH, _hoops_AACCS->polyline._hoops_SRCCS, bool);
			}
			_hoops_AACCS->polyline._hoops_SRCCS = _hoops_CGCGR;
			_hoops_AACCS->polyline.lengths = _hoops_RPCCS;
			_hoops_AACCS->polyline._hoops_AGSSH = _hoops_SACCS;
		}
		_hoops_AIGA(_hoops_GSGGA, _hoops_PRPIP, DC_Point, _hoops_AACCS->polyline._hoops_ASPS);
		_hoops_AACCS->polyline._hoops_ASPS+=_hoops_PRPIP;
		_hoops_AACCS->polyline._hoops_GACCS+=_hoops_PRPIP;
		_hoops_AACCS->polyline.lengths[_hoops_AACCS->polyline.count]=_hoops_PRPIP;
		_hoops_AACCS->polyline._hoops_AGSSH[_hoops_AACCS->polyline.count]=_hoops_HIHCC;
		_hoops_AACCS->polyline.count++;
	}
} 

GLOBAL_FUNCTION void HD_Tint_Driver_Color (
	Net_Rendition const &		nr,
	Driver_Color alter *		_hoops_CPHHP) {
	_hoops_AHAH const &				_hoops_PHAH = nr->_hoops_ARA->_hoops_IHRH;
	int							_hoops_PIHSR = nr->_hoops_SRA->_hoops_PGCC._hoops_PIHSR;

	if (_hoops_PIHSR == _hoops_HIHSR) {
		RGBAS32		_hoops_HPHSA = *_hoops_CPHHP;
		RGB			rgb = _hoops_HPHSA;

		rgb = HD_Apply_Color_Effects (rgb, _hoops_PHAH);

		_hoops_HPHSA = RGBAS32 (rgb, _hoops_HPHSA.a);
		*_hoops_CPHHP = _hoops_HPHSA;
	}
	else if (_hoops_PIHSR == _hoops_SIHSR) {
		/* _hoops_ASIGA */
	}
	else {/* _hoops_AIHHP */
		/* _hoops_ISAP _hoops_SIGR */
		/* _hoops_ASIGA _hoops_AA _hoops_RRP _hoops_CPHP _hoops_RPP _hoops_HAR _hoops_HIAH, _hoops_HPGR _hoops_CHGC _hoops_IH _hoops_SSRR _hoops_PIRA _hoops_CIAAI */
	}
}


GLOBAL_FUNCTION void HD_Draw_Glyphs (
	Net_Rendition const &		in_nr,
	_hoops_GASC const *				glyphs,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors,
	bool						_hoops_AIPSP,
	float const *				rotations,
	float const *				size_fixups) {
	_hoops_ICP const &	_hoops_CCP = in_nr->_hoops_GSP;
	Display_Context const *		dc = in_nr->_hoops_SRA;
	_hoops_GASC		 				glyph;
	char						*p, *end;
	int							_hoops_SIAIP;
	int							_hoops_IAAIP, _hoops_CAAIP;
	int							_hoops_HPAIP, _hoops_IPAIP;
	float						_hoops_SPAIP;
	DC_Point					_hoops_ARPIP[1024];
	DC_Point alter *			pt = _hoops_ARPIP;
	float						_hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR;
	bool						_hoops_CIAIP;
	float						_hoops_PRAA, _hoops_HRAA;
	bool						_hoops_RAIHR;
	bool						_hoops_RAC = BIT(_hoops_CCP->flags, _hoops_IGPSP);
	bool						_hoops_HACCS=false;
	Int_Rectangle const *		_hoops_HHHIH = null;
	_hoops_CRCCS *			_hoops_AACCS = null;
	_hoops_CRCCS *			_hoops_APCCS = null;
	_hoops_CRCCS *			_hoops_PPCCS = null;
	_hoops_CRCCS *			_hoops_HPCCS = null;
	_hoops_CRCCS *			_hoops_IPCCS = null;
	_hoops_CRCCS *			_hoops_CPCCS = null;
	int i;

	/* _hoops_CIHH _hoops_HRGR _hoops_SIGR */
	if (ANYBIT (in_nr->current,
		_hoops_RSSHP|_hoops_CISHP))
		_hoops_HHHIH = &in_nr->transform_rendition->_hoops_AGAA;

	_hoops_PPCCS = _hoops_RACCS(in_nr);

_hoops_SPCCS:

	_hoops_APCCS = _hoops_HPCCS = _hoops_PPCCS;

	_hoops_CIAIP = false;

	if (glyphs) 
		glyph = glyphs[0];
	else
		glyph = _hoops_CCP->glyph;

	if (colors) {
		Driver_Color _hoops_CPHHP;

		/* _hoops_IGAAI */
		_hoops_CPHHP = in_nr->_hoops_AHP->color; 

		if (dc->options._hoops_RAHHP) {
			_hoops_CPHHP = dc->_hoops_SPHHP;
		}
		else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR ||
			(ANYBIT (in_nr->current, _hoops_RSSHP|_hoops_CISHP) &&
			 in_nr->_hoops_ASIR->buffer._hoops_GHAAP == _hoops_PHAAP)) {
			RGB		color = colors[0];
			float	_hoops_PHHHP = (float)dc->_hoops_PGCC._hoops_PCHSR - 0.01f;
			_hoops_CPHHP._hoops_HRIR.r = dc->_hoops_PGCC._hoops_HHHHP[(int)(color.red   * _hoops_PHHHP)];
			_hoops_CPHHP._hoops_HRIR.g = dc->_hoops_PGCC._hoops_HHHHP[(int)(color.green * _hoops_PHHHP)];
			_hoops_CPHHP._hoops_HRIR.b = dc->_hoops_PGCC._hoops_HHHHP[(int)(color.blue  * _hoops_PHHHP)];
			_hoops_CPHHP._hoops_HRIR.a = colors[0].a;
		}
		else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
			_hoops_GARSR		_hoops_IASGR[4+1];
			int				_hoops_AHHIR[3+1];

			/* _hoops_SGH "_hoops_AAH" _hoops_HAIR */
			HD_Find_Dither_Pattern (in_nr, colors, _hoops_IASGR, _hoops_AHHIR);
			_hoops_CPHHP._hoops_PGGCR = _hoops_IASGR[0];
		}
		else /* _hoops_AIHHP */ {
			RGB				color = *colors;

			_hoops_CPHHP = _hoops_CAHSR::_hoops_SAHSR;
			_hoops_CPHHP._hoops_PIHHP = (_hoops_HIHHP)(color._hoops_CPIR() * 
											 ((float)dc->_hoops_PGCC._hoops_PCHSR - 0.001f));
		}

		/* _hoops_SSS _hoops_PIS _hoops_HAIR */
		_hoops_AACCS = _hoops_CPCCS;
		while (_hoops_AACCS) {
			if (_hoops_AACCS->nr->_hoops_AHP->color == _hoops_CPHHP)
				break;
			_hoops_AACCS = _hoops_AACCS->next;
		}

		if (!_hoops_AACCS) {
			Net_Rendition			_hoops_GHCCS = in_nr;
			_hoops_CIGA alter &	_hoops_CPIHP = _hoops_GHCCS.Modify()->_hoops_IHA.Modify();
			Line_Rendition alter &	_hoops_ASGIP = _hoops_GHCCS->_hoops_AHP.Modify();

			/* _hoops_RHCCS _hoops_PSHA */
			_hoops_CPIHP->_hoops_RGIR = _hoops_CPIHP->color = _hoops_CPIHP->contrast_color =
				_hoops_ASGIP->color = _hoops_ASGIP->contrast_color = _hoops_CPHHP;
			_hoops_ASGIP->_hoops_SSHHP = null;
			_hoops_ASGIP->_hoops_IHA = null;

			if (_hoops_CPHHP._hoops_HRIR.a != _hoops_GPGCR) {
				_hoops_CPIHP->_hoops_CHA.Modify()->_hoops_IRIR = (float)_hoops_IRGCR(_hoops_CPHHP._hoops_HRIR.a)*(1.00001f/255.0f);
				_hoops_ASGIP->_hoops_CHA = _hoops_CPIHP->_hoops_CHA;
			}

			_hoops_AACCS = _hoops_RACCS(_hoops_GHCCS);

			/* _hoops_AGGAR _hoops_GH _hoops_AHCCS _hoops_AGR _hoops_IIGR _hoops_SGH */
			if (_hoops_CPCCS) {
				_hoops_APCCS = _hoops_CPCCS;
				while (_hoops_APCCS->next)
					_hoops_APCCS = _hoops_APCCS->next;
				_hoops_APCCS->next=_hoops_AACCS;
			}
			else
				_hoops_CPCCS = _hoops_AACCS;
		}
	
		/* _hoops_RGR _hoops_HRGR _hoops_RH _hoops_SCGR _hoops_GACC */
		_hoops_APCCS = _hoops_HPCCS = _hoops_AACCS;			
	}

	if (BIT(glyph->flags, _hoops_PAGS) && !_hoops_IPCCS) {
		Net_Rendition			_hoops_PIRCP = in_nr;
		_hoops_CIGA alter &	_hoops_CPIHP = _hoops_PIRCP.Modify()->_hoops_IHA.Modify();
		Line_Rendition alter &	_hoops_ASGIP = _hoops_PIRCP->_hoops_AHP.Modify();
		
		_hoops_CPIHP->_hoops_RGIR = _hoops_CPIHP->color = _hoops_CPIHP->contrast_color =
			_hoops_ASGIP->color = _hoops_ASGIP->contrast_color =
				in_nr->_hoops_GSP->contrast_color; 
		_hoops_ASGIP->_hoops_SSHHP = null;
		_hoops_ASGIP->_hoops_IHA = null;

		/* _hoops_RRP _hoops_CGARA _hoops_IHAH */
		_hoops_IPCCS = _hoops_RACCS(_hoops_PIRCP);
	}

	if (BIT(glyph->flags, _hoops_RSIAP)) {
		_hoops_RAIHR = true;
		if (_hoops_HHHIH)
			_hoops_HACCS=true;
	}
	else
		_hoops_RAIHR = false;

	_hoops_HPAIP = _hoops_PGHHA(points->x);
	_hoops_IPAIP = _hoops_PGHHA(points->y);
	_hoops_SPAIP = points->z;

	/* _hoops_ISPR _hoops_GIPR _hoops_CR _hoops_SAACI _hoops_SSCP _hoops_PHCCS _hoops_ASPA */
	if ((!size_fixups && _hoops_CCP->_hoops_RGRS < 0.1f && _hoops_CCP->ysize < 0.1f) ||
		 (size_fixups && *size_fixups*_hoops_CCP->_hoops_RGRS < 0.1f && *size_fixups*_hoops_CCP->ysize < 0.1f)) {
		/* _hoops_CPSA, _hoops_CPSA _hoops_IRS _hoops_RSRA _hoops_AIR */
		pt[0].x = (float)_hoops_HPAIP;
		pt[0].y = (float)_hoops_IPAIP;
		pt[0].z = _hoops_SPAIP;
		_hoops_PACCS(_hoops_APCCS, &pt[0], _hoops_RAIHR, _hoops_HACCS, _hoops_HHHIH);
		goto _hoops_PRSPR;
	}

	_hoops_PRAA = _hoops_HRAA = 1.0f/(float)GLYPH_RADIUS(glyph);	 
	_hoops_PRAA *= _hoops_CCP->_hoops_RGRS;
	_hoops_HRAA *= _hoops_CCP->ysize;
	if (size_fixups) {
		_hoops_PRAA *= *size_fixups;
		_hoops_HRAA *= *size_fixups;
	}

	p = GLYPH_OPS(glyph);
	end = glyph->data + glyph->length;

	_hoops_IPGRP = 0.0f;

	if (rotations && *rotations != 0.0f)
		_hoops_RICH(*rotations, _hoops_GGHCR, _hoops_AGHCR);
	else
		_hoops_GGHCR = 0.0f, _hoops_AGHCR = 1.0f;

	_hoops_IAAIP = GLYPH_HOTSPOT_X(glyph);
	_hoops_CAAIP = GLYPH_HOTSPOT_Y(glyph);

	while (p < end) {
		switch ((_hoops_SIAIP = _hoops_SAAIP (*p))) {
			case _hoops_PSIAP: {
				goto _hoops_PRSPR;
			} break;

			case _hoops_HSIAP: {
				++p;
				_hoops_CIAIP = true;
			} break;

			case _hoops_CSIAP: {
				_hoops_CIAIP = false;
			} _hoops_HHHI;
			case _hoops_ISIAP: {
				int _hoops_PRPIP = pt - _hoops_ARPIP;
				++p;
				if (_hoops_PRPIP > 2) {
					pt->x = _hoops_ARPIP[0].x;
					pt->y = _hoops_ARPIP[0].y;
					pt->z = _hoops_ARPIP[0].z;
					_hoops_GPCCS(_hoops_APCCS, _hoops_PRPIP+1, _hoops_ARPIP, true, _hoops_RAIHR, _hoops_HACCS, _hoops_HHHIH);
				}
				else if (_hoops_PRPIP == 1)
					_hoops_PACCS(_hoops_APCCS, _hoops_ARPIP, _hoops_RAIHR, _hoops_HACCS, _hoops_HHHIH);
				pt = _hoops_ARPIP;
			} break;

			case _hoops_SSIAP: {
				DC_Point 	_hoops_GAPPA, _hoops_RAPPA;
				DC_Point 	center, radii;
				++p;

				_hoops_HAAIP (p, _hoops_IAAIP, _hoops_CAAIP, _hoops_PRAA, _hoops_HRAA, _hoops_GAPPA.x, _hoops_GAPPA.y, _hoops_RAC);
				_hoops_HAAIP (p, _hoops_IAAIP, _hoops_CAAIP, _hoops_PRAA, _hoops_HRAA, _hoops_RAPPA.x, _hoops_RAPPA.y, _hoops_RAC);

				center.x = (_hoops_GAPPA.x + _hoops_RAPPA.x) / 2.0f;
				center.y = (_hoops_GAPPA.y + _hoops_RAPPA.y) / 2.0f;
				center.z = (float)_hoops_SPAIP;

				radii.x = Abs (_hoops_GAPPA.x - _hoops_RAPPA.x) / 2.0f + 0.5f;
				radii.y = Abs (_hoops_GAPPA.y - _hoops_RAPPA.y) / 2.0f + 0.5f;
				radii.z = 0.0f;

				if (_hoops_IPGRP != 0.0f || 
					(radii.x != radii.y) && 
						(_hoops_GGHCR != 0.0f || _hoops_AGHCR != 1.0f)) {
					DC_Point				_hoops_IRPIP[4*100+1];
					DC_Point alter *		_hoops_CRPIP = _hoops_IRPIP;
					float					_hoops_HCAIP, _hoops_ICAIP;
					int						ii;
					Vector					_hoops_IHHI, _hoops_CHHI;
					int						_hoops_GSICS;
					int						_hoops_GACGR;
					float					delta;

					_hoops_PPAIP (center.x, center.y, _hoops_HPAIP, _hoops_IPAIP, _hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR, center.x, center.y);
					_hoops_GPAIP (radii.x, 0.0f, _hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR, _hoops_IHHI.x, _hoops_IHHI.y);
					_hoops_GPAIP (0.0f, radii.y, _hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR, _hoops_CHHI.x, _hoops_CHHI.y);

					_hoops_GSICS = (int)(0.5f + _hoops_SGIHR (_hoops_IAAA (radii.x, radii.y)));

					if (_hoops_GSICS == 0) {
						_hoops_PACCS(_hoops_APCCS, &center, _hoops_RAIHR, _hoops_HACCS, _hoops_HHHIH);
						break;
					}

					if (_hoops_GSICS > 100)
						_hoops_GSICS = 100;

					_hoops_GACGR = 4 * _hoops_GSICS;

					delta = 90.0f / (float)_hoops_GSICS;

					center.x = (float)(int)center.x;
					center.y = (float)(int)center.y;

					for (ii=0; ii<=_hoops_GACGR; ++ii) {
						_hoops_RICH ((float)(ii*delta), _hoops_HCAIP, _hoops_ICAIP);
						_hoops_CRPIP->x = center.x + (int)(_hoops_ICAIP * _hoops_IHHI.x + _hoops_HCAIP * _hoops_CHHI.x);
						_hoops_CRPIP->y = center.y + (int)(_hoops_ICAIP * _hoops_IHHI.y + _hoops_HCAIP * _hoops_CHHI.y);
						_hoops_CRPIP->z = center.z;
						++_hoops_CRPIP;
					}

					if (_hoops_CIAIP) {
						_hoops_GPCCS(_hoops_APCCS, _hoops_GACGR+1, _hoops_IRPIP, true, _hoops_RAIHR, _hoops_HACCS, _hoops_HHHIH);
					}
					else
						_hoops_GPCCS(_hoops_APCCS, _hoops_GACGR+1, _hoops_IRPIP, false, _hoops_RAIHR, _hoops_HACCS, _hoops_HHHIH);

				}
				else {
					DC_Point	_hoops_GAPIP, _hoops_RAPIP;

					_hoops_GAPIP.x = _hoops_HPAIP + center.x;
					_hoops_GAPIP.y = _hoops_IPAIP + center.y;
					_hoops_GAPIP.z = center.z;

					_hoops_RAPIP.x = radii.x;
					_hoops_RAPIP.y = radii.y;
					_hoops_RAPIP.z = radii.z;

					if (_hoops_CIAIP)
						_hoops_CACCS(_hoops_APCCS, &_hoops_GAPIP, &_hoops_RAPIP, true, _hoops_RAIHR, _hoops_HACCS, _hoops_HHHIH);
					else
						_hoops_CACCS(_hoops_APCCS, &_hoops_GAPIP, &_hoops_RAPIP, false, _hoops_RAIHR, _hoops_HACCS, _hoops_HHHIH);
				}
			} break;

			case _hoops_GGCAP: {
				Point		_hoops_GAPPA, _hoops_RAPPA, _hoops_CAPPA;
				Point		center, _hoops_GGHI, _hoops_RGHI;
				float		_hoops_RAHCR, _hoops_HCAIP, _hoops_ICAIP;
				int			ii;

				++p;

				_hoops_HAAIP (p, _hoops_IAAIP, _hoops_CAAIP, _hoops_PRAA, _hoops_HRAA, _hoops_GAPPA.x, _hoops_GAPPA.y, _hoops_RAC);
				_hoops_HAAIP (p, _hoops_IAAIP, _hoops_CAAIP, _hoops_PRAA, _hoops_HRAA, _hoops_RAPPA.x, _hoops_RAPPA.y, _hoops_RAC);
				_hoops_HAAIP (p, _hoops_IAAIP, _hoops_CAAIP, _hoops_PRAA, _hoops_HRAA, _hoops_CAPPA.x, _hoops_CAPPA.y, _hoops_RAC);

				_hoops_GAPPA.z = _hoops_RAPPA.z = _hoops_CAPPA.z = (float)_hoops_SPAIP;

				if (HI_Analyze_Arc (&_hoops_GAPPA, &_hoops_RAPPA, &_hoops_CAPPA, &center, &_hoops_GGHI, &_hoops_RGHI, &_hoops_RAHCR)) {
					/* _hoops_HIHP _hoops_PHPHA _hoops_SIHC */
					_hoops_PPAIP (center.x, center.y, _hoops_HPAIP, _hoops_IPAIP, _hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR, center.x, center.y);
					_hoops_GPAIP (_hoops_GGHI.x, _hoops_GGHI.y, _hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR, _hoops_GGHI.x, _hoops_GGHI.y);
					_hoops_GPAIP (_hoops_RGHI.x, _hoops_RGHI.y, _hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR, _hoops_RGHI.x, _hoops_RGHI.y);

					for (ii=0; ii<_hoops_RAHCR; ii+=5) {
						_hoops_RICH ((float)ii, _hoops_HCAIP, _hoops_ICAIP);
						pt->x = center.x + _hoops_ICAIP * _hoops_GGHI.x + _hoops_HCAIP * _hoops_RGHI.x;
						pt->y = center.y + _hoops_ICAIP * _hoops_GGHI.y + _hoops_HCAIP * _hoops_RGHI.y;
						pt->z = center.z;
						++pt;
					}

					_hoops_RICH (_hoops_RAHCR, _hoops_HCAIP, _hoops_ICAIP);
					pt->x = center.x + _hoops_ICAIP * _hoops_GGHI.x + _hoops_HCAIP * _hoops_RGHI.x;
					pt->y = center.y + _hoops_ICAIP * _hoops_GGHI.y + _hoops_HCAIP * _hoops_RGHI.y;
					pt->z = center.z;
					++pt;

				}
				else {		/* _hoops_GGR _hoops_IRS _hoops_III -- _hoops_SAHR _hoops_SGH _hoops_CAPR */
					_hoops_PPAIP (_hoops_GAPPA.x, _hoops_GAPPA.y, _hoops_HPAIP, _hoops_IPAIP, _hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR, pt->x, pt->y);
					pt->z = (float)_hoops_SPAIP;	
					++pt;
					_hoops_PPAIP (_hoops_RAPPA.x, _hoops_RAPPA.y, _hoops_HPAIP, _hoops_IPAIP, _hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR, pt->x, pt->y);
					pt->z = (float)_hoops_SPAIP;	
					++pt;
					_hoops_PPAIP (_hoops_CAPPA.x, _hoops_CAPPA.y, _hoops_HPAIP, _hoops_IPAIP, _hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR, pt->x, pt->y);
					pt->z = (float)_hoops_SPAIP;	
					++pt;
				}

				if (!_hoops_CIAIP) {
					int		_hoops_PRPIP = pt - _hoops_ARPIP;
					_hoops_GPCCS(_hoops_APCCS, _hoops_PRPIP, _hoops_ARPIP, false, _hoops_RAIHR, _hoops_HACCS, _hoops_HHHIH);
					pt = _hoops_ARPIP;
				}
			} break;

			case _hoops_RGCAP: 
			case _hoops_AGCAP: {
				Point		_hoops_GAPPA, _hoops_RAPPA;
				float		_hoops_PGSAA, _hoops_IGSAA, max;
				Vector		v;

				++p;
				_hoops_PGSAA = in_nr->_hoops_SAIR->extent.top - in_nr->_hoops_SAIR->extent.bottom;
				_hoops_IGSAA = in_nr->_hoops_SAIR->extent.right - in_nr->_hoops_SAIR->extent.left;

				max = _hoops_IAAA(_hoops_PGSAA,_hoops_IGSAA);

				_hoops_CPAIP(p,
					0, 0, 0,
					_hoops_IAAIP, _hoops_CAAIP,
					_hoops_PRAA, _hoops_HRAA, 
					_hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR,
					_hoops_GAPPA.x, _hoops_GAPPA.y, _hoops_GAPPA.z, _hoops_RAC);

				_hoops_CPAIP(p,
					0, 0, 0,
					_hoops_IAAIP, _hoops_CAAIP,
					_hoops_PRAA, _hoops_HRAA, 
					_hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR,
					_hoops_RAPPA.x, _hoops_RAPPA.y, _hoops_RAPPA.z, _hoops_RAC);

				v.x = _hoops_RAPPA.x-_hoops_GAPPA.x;
				v.y = _hoops_RAPPA.y-_hoops_GAPPA.y;
				v.z = _hoops_RAPPA.z-_hoops_GAPPA.z;

				if (_hoops_SIAIP == _hoops_RGCAP) {
					_hoops_ARPIP[0].x = _hoops_HPAIP + _hoops_GAPPA.x - v.x*max; 
					_hoops_ARPIP[0].y = _hoops_IPAIP + _hoops_GAPPA.y - v.y*max;
					_hoops_ARPIP[0].z = _hoops_SPAIP + _hoops_GAPPA.z - v.z*max;
				}
				else {
					_hoops_ARPIP[0].x = _hoops_HPAIP + _hoops_GAPPA.x;
					_hoops_ARPIP[0].y = _hoops_IPAIP + _hoops_GAPPA.y;
					_hoops_ARPIP[0].z = _hoops_SPAIP + _hoops_GAPPA.z;
				}

				_hoops_ARPIP[1].x = _hoops_HPAIP + _hoops_GAPPA.x + v.x*max;
				_hoops_ARPIP[1].y = _hoops_IPAIP + _hoops_GAPPA.y + v.y*max; 
				_hoops_ARPIP[1].z = _hoops_SPAIP + _hoops_GAPPA.z + v.z*max;

				_hoops_GPCCS(_hoops_APCCS, 2, _hoops_ARPIP, false, _hoops_RAIHR, _hoops_HACCS, _hoops_HHHIH);

				pt = _hoops_ARPIP;
			} break;

			case _hoops_PGCAP: {
				++p;
				_hoops_APCCS = _hoops_IPCCS;
			} break;
			case _hoops_HGCAP: {
				++p;
				_hoops_APCCS = _hoops_HPCCS;
			} break;

			case _hoops_IGCAP: 
			case _hoops_CGCAP: {
				Driver_Color	_hoops_CPHHP;
				++p;

				// _hoops_CRICR _hoops_IS _hoops_III _hoops_IAHA _hoops_HAIR _hoops_RRGR

				/* _hoops_IGAAI */
				_hoops_CPHHP = in_nr->_hoops_AHP->color; 

				if (_hoops_SIAIP == _hoops_IGCAP) {
					RGBAS32		_hoops_HHCCS;
					RGB			color;

					_hoops_HHCCS.r = (unsigned char)*p++;
					_hoops_HHCCS.g = (unsigned char)*p++;
					_hoops_HHCCS.b = (unsigned char)*p++;

					color = _hoops_HHCCS;

					if (dc->options._hoops_RAHHP) {
						_hoops_CPHHP = dc->_hoops_SPHHP;
					}
					else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR ||
						(ANYBIT (in_nr->current, 
							_hoops_RSSHP|_hoops_CISHP) &&
								in_nr->_hoops_ASIR->buffer._hoops_GHAAP == _hoops_PHAAP)) {

						float _hoops_PHHHP;
						_hoops_PHHHP = (float)dc->_hoops_PGCC._hoops_PCHSR - 0.01f;
						_hoops_CPHHP._hoops_HRIR.r = dc->_hoops_PGCC._hoops_HHHHP[(int)(color.red   * _hoops_PHHHP)];
						_hoops_CPHHP._hoops_HRIR.g = dc->_hoops_PGCC._hoops_HHHHP[(int)(color.green * _hoops_PHHHP)];
						_hoops_CPHHP._hoops_HRIR.b = dc->_hoops_PGCC._hoops_HHHHP[(int)(color.blue  * _hoops_PHHHP)];
						_hoops_CPHHP._hoops_HRIR.a = _hoops_GPGCR;
					}
					else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
						int			index;
						_hoops_CPHHP = _hoops_CAHSR::_hoops_SAHSR; 
						index = (int)(color.red * ((float)dc->_hoops_AGPGH.r - 0.001f));
						index *= dc->_hoops_AGPGH.g;
						index += (int)(color.green * ((float)dc->_hoops_AGPGH.g - 0.001f));
						index *= dc->_hoops_AGPGH.b;
						index += (int)(color.blue * ((float)dc->_hoops_AGPGH.b - 0.001f));
						_hoops_CPHHP._hoops_PGGCR = index + dc->_hoops_RHGCR;
					}
					else /* _hoops_AIHHP */ {
						_hoops_CPHHP = _hoops_CAHSR::_hoops_SAHSR;
						_hoops_CPHHP._hoops_PIHHP = (_hoops_HIHHP)(color._hoops_CPIR() * 
														 ((float)dc->_hoops_PGCC._hoops_PCHSR - 0.001f));
					}
				}
				else {
					/* _hoops_IHCCS */
#ifndef DISABLE_COLOR_MAPS
					_hoops_CAHHP const &		_hoops_SAHHP = in_nr->_hoops_ASIR->_hoops_PSIR;
					int								index = (int)*p++;

					if (index >= (int)_hoops_SAHHP->length) {
						char			buf[MAX_ERRMSG];
						Sprintf_DD (buf, "The current color map has only %d entries; offset %d was requested.", 
							(int)_hoops_SAHHP->length, index);
						_hoops_PHPGR (HEC_COLOR, HES_OUT_OF_RANGE_COLOR_INDEX,
							Sprintf_N (null, "A color-by-index in glyph %n is out of range -", &glyph->name), buf);
					}
					else {
						if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
							_hoops_CPHHP = _hoops_CAHSR::_hoops_SAHSR;	/* _hoops_CASI _hoops_SCH _hoops_GGSR */
							_hoops_CPHHP._hoops_PGGCR = _hoops_SAHHP->_hoops_RHHHP + index;
						}
						else {
							_hoops_CPHHP = _hoops_SAHHP->_hoops_AHHHP[index];
						}
					}
#endif
				}
				if (BIT(in_nr->_hoops_ARA->_hoops_IHRH.options, _hoops_CHRH))
					HD_Tint_Driver_Color (in_nr, &_hoops_CPHHP);

				/* _hoops_SSS _hoops_PIS _hoops_HAIR */
				_hoops_AACCS = _hoops_CPCCS;
				while (_hoops_AACCS) {
					if (_hoops_AACCS->nr->_hoops_AHP->color == _hoops_CPHHP)
						break;
					_hoops_AACCS = _hoops_AACCS->next;
				}

				if (!_hoops_AACCS) {
					Net_Rendition			_hoops_GHCCS = in_nr;
					_hoops_CIGA alter &	_hoops_CPIHP = _hoops_GHCCS.Modify()->_hoops_IHA.Modify();
					Line_Rendition alter &	_hoops_ASGIP = _hoops_GHCCS->_hoops_AHP.Modify();
					
					/* _hoops_RHCCS _hoops_PSHA */
					_hoops_CPIHP->color = _hoops_CPIHP->_hoops_RGIR = _hoops_CPIHP->contrast_color =
						_hoops_ASGIP->color = _hoops_ASGIP->contrast_color =
							_hoops_CPHHP;
					_hoops_ASGIP->_hoops_SSHHP = null;
					_hoops_ASGIP->_hoops_IHA = null;

					_hoops_AACCS = _hoops_RACCS(_hoops_GHCCS);

					/* _hoops_AGGAR _hoops_GH _hoops_AHCCS _hoops_AGR _hoops_IIGR _hoops_SGH */
					if (_hoops_CPCCS) {
						_hoops_APCCS = _hoops_CPCCS;
						while (_hoops_APCCS->next)
							_hoops_APCCS = _hoops_APCCS->next;
						_hoops_APCCS->next = _hoops_AACCS;
					}
					else
						_hoops_CPCCS = _hoops_AACCS;
				}
				
				_hoops_APCCS = _hoops_AACCS;
			} break;

			case _hoops_SGCAP: {
				++p;
				/* _hoops_HCR _hoops_HRPP _hoops_GGR _hoops_RH _hoops_SGI */
			}	break;		
			
			case _hoops_ASIAP:	{
				++p;
				_hoops_CPAIP(p,
					_hoops_HPAIP, _hoops_IPAIP, _hoops_SPAIP,
					_hoops_IAAIP, _hoops_CAAIP,
					_hoops_PRAA, _hoops_HRAA, 
					_hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR,
					pt->x, pt->y, pt->z, _hoops_RAC);

				if (_hoops_CIAIP)
					++pt;	/* _hoops_SAHR _hoops_HPIH _hoops_PPSR _hoops_GGR _hoops_RH _hoops_HHGPA */
				else {
					/* _hoops_PGSA _hoops_IRS _hoops_SIGC _hoops_PSCHR _hoops_HA */
					if (_hoops_PRAA < 1.0f && _hoops_HRAA < 1.0f) {
						/* _hoops_RISA _hoops_RAPR _hoops_IS _hoops_SGH _hoops_IRS _hoops_RSRA _hoops_AIR _hoops_PSCHR */
						_hoops_PACCS(_hoops_APCCS, _hoops_ARPIP, _hoops_RAIHR, _hoops_HACCS, _hoops_HHHIH);
					}
					else {
						++pt;
						pt->x = _hoops_PRAA;	 
						pt->y = _hoops_HRAA;	 
						pt->z = _hoops_SPAIP;

						/* _hoops_PSHR _hoops_GAR _hoops_IRS _hoops_CPPPR _hoops_RISA _hoops_PIISR _hoops_PRHC */
						_hoops_CACCS(_hoops_APCCS, &_hoops_ARPIP[0], &_hoops_ARPIP[1], true, _hoops_RAIHR, _hoops_HACCS, _hoops_HHHIH);
						pt = _hoops_ARPIP;
					}
				}
			} break;

			default: {
				++p;
				do {
					_hoops_CPAIP (p,
					_hoops_HPAIP, _hoops_IPAIP, (float)_hoops_SPAIP,
					_hoops_IAAIP, _hoops_CAAIP,
					_hoops_PRAA, _hoops_HRAA, 
					_hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR,
					pt->x, pt->y, pt->z, _hoops_RAC);
					++pt;
				} _hoops_RGGA (--_hoops_SIAIP == 0);

				if (!_hoops_CIAIP) {
					int		_hoops_PRPIP = pt - _hoops_ARPIP;
					_hoops_GPCCS(_hoops_APCCS, _hoops_PRPIP, _hoops_ARPIP, false, _hoops_RAIHR, _hoops_HACCS, _hoops_HHHIH);
					pt = _hoops_ARPIP;
				}
			} break;
		}
	}

_hoops_PRSPR:
	if (_hoops_CIAIP && pt != _hoops_ARPIP) {
		int _hoops_PRPIP = pt - _hoops_ARPIP;

		if (_hoops_PRPIP > 2) {
			pt->x = _hoops_ARPIP[0].x;
			pt->y = _hoops_ARPIP[0].y;
			pt->z = _hoops_ARPIP[0].z;
			_hoops_GPCCS(_hoops_APCCS, _hoops_PRPIP+1, _hoops_ARPIP, true, _hoops_RAIHR, _hoops_HACCS, _hoops_HHHIH);
		}
		else if (_hoops_PRPIP == 1)
			_hoops_PACCS(_hoops_APCCS, _hoops_ARPIP, _hoops_RAIHR, _hoops_HACCS, _hoops_HHHIH);
	} 

	if (count>1) {
		points++;
		if (rotations)
			rotations++;
		if (size_fixups)
			size_fixups++;
		if (glyphs)
			glyphs++;
		if (colors && !_hoops_AIPSP)
			colors++;
		count--;
		goto _hoops_SPCCS;
	}
  

	/* _hoops_AGGAR _hoops_GH _hoops_PPR _hoops_RIAH */
	_hoops_PPCCS->next = _hoops_IPCCS;
	if (_hoops_CPCCS) {
		if (_hoops_PPCCS->next)
			_hoops_PPCCS->next->next = _hoops_CPCCS;
		else
			_hoops_PPCCS->next = _hoops_CPCCS;
	}

	/* _hoops_GGCH _hoops_HGIIP */
	if (_hoops_HACCS) {

		_hoops_APCCS = _hoops_PPCCS;
		while ((_hoops_AACCS = _hoops_APCCS) != null) {
			if (BIT (_hoops_AACCS->nr->transform_rendition->flags, _hoops_AIHS))
				_hoops_AACCS->nr.Modify()->transform_rendition.Modify()->flags &= ~_hoops_AIHS;

			_hoops_APCCS = _hoops_APCCS->next;
		}
	}

	/* _hoops_PGSA _hoops_GII _hoops_PAGAI */
	_hoops_APCCS = _hoops_PPCCS;
	while ((_hoops_AACCS = _hoops_APCCS) != null) {
		if (_hoops_AACCS->_hoops_SSRP.count)
			_hoops_AIGGA (_hoops_AACCS->nr, _hoops_AACCS->_hoops_SSRP.count, _hoops_AACCS->_hoops_SSRP.points);
		/* _hoops_GGAS _hoops_GAR _hoops_SR _hoops_PHHR */
		if (_hoops_AACCS->_hoops_SSRP._hoops_SAGCA)
			FREE_ARRAY(_hoops_AACCS->_hoops_SSRP.points, _hoops_AACCS->_hoops_SSRP._hoops_SAGCA, DC_Point);
		_hoops_APCCS = _hoops_APCCS->next;
	}

	/* _hoops_PGSA _hoops_GII _hoops_HCPI */
	_hoops_APCCS = _hoops_PPCCS;
	while ((_hoops_AACCS = _hoops_APCCS) != null) {
		if (_hoops_AACCS->ellipse.count) {
			DC_Point const *	pts = _hoops_AACCS->ellipse.points;
			bool const *		_hoops_AGSSH = _hoops_AACCS->ellipse._hoops_AGSSH;
			bool				opaque = (_hoops_AACCS->nr->_hoops_AHP->_hoops_CHA->_hoops_IRIR > 0.9f);

			for (i=0; i<_hoops_AACCS->ellipse.count; i++) {
				if (_hoops_AGSSH[0])
					_hoops_AAPIP (_hoops_AACCS->nr, &pts[0], &pts[1]);
				if (!_hoops_AGSSH[0] || opaque)
					_hoops_PAPIP (_hoops_AACCS->nr, &pts[0], &pts[1]);
				pts += 2;
				_hoops_AGSSH++;
			}
		}
		/* _hoops_GGAS _hoops_GAR _hoops_SR _hoops_PHHR */
		if (_hoops_AACCS->ellipse._hoops_SAGCA) {
			FREE_ARRAY(_hoops_AACCS->ellipse.points, _hoops_AACCS->ellipse._hoops_SAGCA, DC_Point);
			FREE_ARRAY(_hoops_AACCS->ellipse._hoops_AGSSH, _hoops_AACCS->ellipse._hoops_SAGCA>>1, bool);
		}
		_hoops_APCCS = _hoops_APCCS->next;
	}

	/* _hoops_PGSA _hoops_GII _hoops_PGRC */
	_hoops_APCCS = _hoops_PPCCS;
	while ((_hoops_AACCS = _hoops_APCCS) != null) {
		if (_hoops_AACCS->polyline.count) {
			DC_Point const *	pts = _hoops_AACCS->polyline.points;
			int const *			length = _hoops_AACCS->polyline.lengths;
			bool const *		_hoops_AGSSH = _hoops_AACCS->polyline._hoops_AGSSH;
			bool				opaque = (_hoops_AACCS->nr->_hoops_AHP->_hoops_CHA->_hoops_IRIR > 0.9f);

			for (i=0; i<_hoops_AACCS->polyline.count; i++) {
				if (_hoops_AGSSH[0])
					_hoops_RSGCP (_hoops_AACCS->nr, length[0]-1, &pts[0]);
				if (!_hoops_AGSSH[0] || opaque)
					_hoops_SCGGA (_hoops_AACCS->nr, length[0], &pts[0]);
				pts += length[0];
				length++;
				_hoops_AGSSH++;
			}
		}
		/* _hoops_GGAS _hoops_GAR _hoops_SR _hoops_PHHR */
		if (_hoops_AACCS->polyline._hoops_SAGCA) 
			FREE_ARRAY(_hoops_AACCS->polyline.points, _hoops_AACCS->polyline._hoops_SAGCA, DC_Point);
		if (_hoops_AACCS->polyline._hoops_SRCCS) {
			FREE_ARRAY(_hoops_AACCS->polyline.lengths, _hoops_AACCS->polyline._hoops_SRCCS, int);
			FREE_ARRAY(_hoops_AACCS->polyline._hoops_AGSSH, _hoops_AACCS->polyline._hoops_SRCCS, bool);
		}

		_hoops_APCCS = _hoops_APCCS->next;
	}
  
	/* _hoops_CASI _hoops_GH _hoops_HHRPA _hoops_CHCCS _hoops_PPR _hoops_SCII */
	_hoops_APCCS = _hoops_PPCCS;
	while ((_hoops_AACCS = _hoops_APCCS) != null) {
		_hoops_AACCS->nr.release();

		_hoops_APCCS = _hoops_APCCS->next;

		FREE(_hoops_AACCS, _hoops_CRCCS);
	}

}


GLOBAL_FUNCTION void HD_Std_DC_Polymarker (
	Net_Rendition const &		inr,
	int							count,
	DC_Point const *			points,
	float const *				rotations,
	float const *				size_fixups) {
	Net_Rendition				nr = inr.Copy();
	_hoops_ICP const &	_hoops_CCP = nr->_hoops_GSP;
	Line_Rendition				_hoops_HC;
   
	if (_hoops_CCP->_hoops_SSHHP == null) {
		((_hoops_ICP alter &)_hoops_CCP)->_hoops_SSHHP = nr->_hoops_AHP;
		Line_Rendition alter &	_hoops_ASGIP = ((_hoops_ICP alter &)_hoops_CCP)->_hoops_SSHHP.Modify();

		HD_Replace_Line_Style(_hoops_ASGIP, nr->_hoops_GCSHP->_hoops_IHRIP);

		float weight = 1.0f;

		if (BIT(_hoops_CCP->flags, _hoops_SGPSP)) {

			weight = _hoops_CCP->_hoops_GRPSP.value;

			// _hoops_IPIH _hoops_RGAR _hoops_ICPAA _hoops_GGR _hoops_HII _hoops_III _hoops_PCIAA _hoops_GGRGR-_hoops_CIICS
			ASSERT(_hoops_CCP->_hoops_GRPSP._hoops_HHP == GSU_PIXELS);
		}
	
		_hoops_ASGIP->weight = weight * nr->_hoops_SRA->_hoops_PGCC._hoops_IHHSR;

		_hoops_ASGIP->color = _hoops_CCP->color;
		_hoops_ASGIP->contrast_color = _hoops_CCP->contrast_color;

		_hoops_ASGIP->_hoops_SSHHP = _hoops_ASGIP->contrast_rendition = null;
		_hoops_ASGIP->_hoops_IHA = null;

		_hoops_ASGIP->_hoops_CHA = _hoops_CCP->_hoops_CHA;
	}
	_hoops_HC = nr->_hoops_AHP = _hoops_CCP->_hoops_SSHHP;

	if (_hoops_HC->_hoops_IHA == null) {
		_hoops_HC->_hoops_IHA = nr->_hoops_IHA;
		_hoops_CIGA alter &		_hoops_SIGA = _hoops_HC->_hoops_IHA.Modify();

		_hoops_SIGA->_hoops_RGIR = _hoops_SIGA->color = _hoops_HC->color;
		_hoops_SIGA->contrast_color = _hoops_HC->contrast_color;
		_hoops_SIGA->pattern = FP_SOLID;

		_hoops_SIGA->_hoops_CHA = _hoops_HC->_hoops_CHA;
	} 
	nr->_hoops_IHA = _hoops_HC->_hoops_IHA;

	if (nr->transform_rendition->_hoops_CHIH != 0 ||
		!BIT (nr->transform_rendition->heuristics, _hoops_CGCS)) {
		_hoops_HHCR alter &		_hoops_GGCC = nr->transform_rendition.Modify(1000000);

		_hoops_GGCC->_hoops_CHIH = 0;
		_hoops_GGCC->heuristics |= _hoops_CGCS;
	}

	if (BIT (nr->transform_rendition->flags, _hoops_AIHS) &&
		(size_fixups != null || _hoops_CCP->_hoops_RGRS > 0.5f || _hoops_CCP->ysize > 0.5f))
		nr->transform_rendition.Modify()->flags &= ~_hoops_AIHS;

	HD_Draw_Glyphs (nr, 0, count, points, 0, false, rotations, size_fixups);
}


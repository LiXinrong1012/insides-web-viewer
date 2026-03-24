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
 * $Id: obf_tmp.txt 1.211 2010-10-29 00:49:05 jason Exp $
 */


#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "phdraw.h"
#include "patterns.h"
#include "tandt.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hc_proto.h"
#include "hpserror.h"

#define _hoops_HRIIS(_hoops_IRIIS, _hoops_PAGR)	\
	do {								\
		(_hoops_PAGR).x = (_hoops_IRIIS).x;			\
		(_hoops_PAGR).y = (_hoops_IRIIS).y;			\
		(_hoops_PAGR).z = (_hoops_IRIIS).z;			\
	} while (0)


#ifndef DISABLE_DRAW_3D

#define _hoops_CSACP(nr, mat, _hoops_SSACP, point, color, plane, _hoops_ASACP, _hoops_GGPCP) do {			\
		if (_hoops_SSACP && ANYBIT (nr->transform_rendition->_hoops_IPH->data._hoops_RAGR,	\
								  _hoops_CICH))									\
			_hoops_GSACP (nr, mat, point, color, plane, _hoops_ASACP, _hoops_GGPCP);			\
		else																					\
			_hoops_ISACP (nr,															\
								 nr->_hoops_RHP->_hoops_AGP,							\
								 mat, point, color, plane, _hoops_ASACP, null, 0, 0, _hoops_GGPCP, null);\
	} while (0)

local void _hoops_GSACP (
	Net_Rendition const &		nr,
	_hoops_HHA const &	_hoops_ISHIR,
	Point const *				_hoops_RSACP,
	RGB const *					color,
	_hoops_ARPA const *				plane,
	Vector const *				_hoops_ASACP,
	RGBA alter *				total) {
	Point						_hoops_HSACP;
	_hoops_RPRA const *			elements = nr->transform_rendition->_hoops_IPH->data.elements;

	_hoops_HSACP.x = _hoops_HPRA (elements, *_hoops_RSACP);
	_hoops_HSACP.y = _hoops_IPRA (elements, *_hoops_RSACP);
	_hoops_HSACP.z = _hoops_CPRA (elements, *_hoops_RSACP);
	_hoops_ISACP (nr, nr->_hoops_RHP->_hoops_AGP, _hoops_ISHIR,
						 &_hoops_HSACP, color, plane, _hoops_ASACP, null, 0, 0, total, null);
}

#endif



#define _hoops_CRIIS		256
#define _hoops_AGACP		(2*_hoops_CRIIS)
#define _hoops_PGACP		_hoops_AGACP


GLOBAL_FUNCTION void HD_Std_3D_Polyedge (
	Net_Rendition const & 		inr,
	Polyedge const *			pe) {
#ifndef DISABLE_DRAW_3D
	Net_Rendition				nr = inr;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	int							_hoops_PHHA = pe->_hoops_PHHA;
	int const *					lengths = pe->lengths;
	int const *					_hoops_AIHA = pe->_hoops_AIHA;
	int const *					_hoops_SPII = pe->_hoops_SPII;
	RGB const *					_hoops_PCHA = pe->_hoops_PCHA;
	RGB const *					_hoops_ASHA = pe->_hoops_ASHA;
	Vector const *				_hoops_ICHA = pe->_hoops_ICHA;
	Vector const *				_hoops_RSHA = pe->_hoops_RSHA;
	_hoops_RSSH const *			_hoops_CCHA = pe->_hoops_CCHA;
	int							param_width = pe->_hoops_GSHA;
	int							edge = -1;
	int							_hoops_HSPI, _hoops_ISPI;
	RGB const					*_hoops_SRIIS = null, *_hoops_GAIIS = null;
	_hoops_ARPA const					*_hoops_RAIIS = null, *_hoops_AIAIA = null;
	int							point_count = pe->point_count;
	int							_hoops_SPHA = pe->_hoops_SPHA;
	_hoops_PC const &		_hoops_CGR = nr->_hoops_RHP->_hoops_AGP;
	unsigned char				_hoops_IRIR;
	bool						_hoops_HIGSI = false, _hoops_AAIIS = false;
	bool						_hoops_HAACP = false, _hoops_IAACP = false, _hoops_CRIR = false;
	bool						_hoops_CAACP = false;
	DC_Point alter *			points = null;
	RGBAS32 alter *				colors = null;
	_hoops_ARPA alter *				planes = null;
	_hoops_RSSH alter *			params = null;
	RGBA alter *				_hoops_HPHSA = null;
	RGBAS32 *					_hoops_GHGCP = null;
	int							_hoops_AGH = 0;
	DC_Point *					_hoops_GHPCP = null;
	float *						ws = null;
	_hoops_GRCAR *					_hoops_ARCAR = null;
	_hoops_ARPA  *					_hoops_PAIIS = null;
	_hoops_ARPA  *					_hoops_HAIIS = null;
	DC_Point 					_hoops_HRIGA[_hoops_PGACP];
	RGBAS32 					_hoops_HIAI[_hoops_PGACP];
	_hoops_ARPA 						_hoops_IHRGA[_hoops_PGACP];
	_hoops_RSSH 					_hoops_SHRGA[_hoops_PGACP*3*8];
	RGBA 						_hoops_IGACP[_hoops_PGACP];
	int							_hoops_CRCAR;
	_hoops_AHAH const &				_hoops_PHAH = nr->_hoops_ARA->_hoops_IHRH;

	if (BIT(nr->_hoops_RHP->line_style->flags, _hoops_CRCAP) &&
		nr->_hoops_RSGC->action.draw_dc_polyline == nullroutine)
		return;

	dc->_hoops_GSGC |= _hoops_ASRI;
	if (BIT (pe->_hoops_CARI, _hoops_RCRI))
		dc->_hoops_GSGC |= _hoops_RSRI;

	if (BIT(dc->flags, _hoops_CHSI))
		return;

	if (_hoops_CGR == null) {
		_hoops_ICHA = null;
		_hoops_RSHA = null;
	}

	/*
	 * _hoops_GIGHR: _hoops_RPP _hoops_IAIIS _hoops_HRGR _hoops_CAIIS '_hoops_AH' _hoops_RSSA, _hoops_PSCR
	 *		 _hoops_RH _hoops_IHH _hoops_RSSA _hoops_PPR _hoops_SAIIS _hoops_CHR _hoops_IS _hoops_SHH _hoops_GSGI _hoops_SPGCC
	 *		 _hoops_GGR '_hoops_HSAGA'.
	 *
	 *		 _hoops_HGI _hoops_HRGR _hoops_SCIPA _hoops_PPR _hoops_APIGP _hoops_RH _hoops_GPIIS _hoops_IIGR _hoops_RGR _hoops_RRGR, _hoops_HIH
	 *		 _hoops_GIASI _hoops_SR'_hoops_ASAR _hoops_GGR _hoops_IRS _hoops_RPIIS.
	 */

	if (!lengths) {
		lengths = &point_count;
		_hoops_SPHA = point_count - 1;
	}

	if (point_count == 0 || _hoops_SPHA == 0) {
		int				index;
		/* _hoops_PS _hoops_GHCA _hoops_HS _hoops_PCCP _hoops_AIPH _hoops_RSHS _hoops_PPR/_hoops_PAR _hoops_ASHS, _hoops_SPIC _hoops_HIGR _hoops_IS _hoops_CGIC _hoops_RH
		** _hoops_CIAS _hoops_PSHS _hoops_HSH _hoops_IH _hoops_AGCR. */

		while (_hoops_PHHA-- > 0) {
			int			length = *lengths++;

			if (length < 0)
				length = -length;

			if (_hoops_AIHA) {
				while (length-- > 0) {
					if ((index = *_hoops_AIHA++) > point_count)
						point_count = index;
					if (_hoops_SPII) {
						if ((index = *_hoops_SPII++) > _hoops_SPHA)
							_hoops_SPHA = index;
					}
				}
			}
			else {
				point_count = pe->total;
				_hoops_SPHA = pe->total - pe->_hoops_PHHA;
			}
		}
		_hoops_PHHA = pe->_hoops_PHHA;
		lengths = pe->lengths;
		_hoops_AIHA = pe->_hoops_AIHA;
		_hoops_SPII = pe->_hoops_SPII;

		if (_hoops_SPHA == 0 && !_hoops_SPII)
			_hoops_SPHA = pe->total - pe->_hoops_PHHA;

		/* _hoops_AGRP _hoops_CCAH _hoops_HSH _hoops_HII "_hoops_CIAS _hoops_CIHA" _hoops_IS "_hoops_PHI _hoops_IIGR _hoops_PSPI" */
		if (pe->point_count == 0)
			((Polyedge alter *)pe)->point_count = ++point_count;
		if (pe->_hoops_SPHA == 0)
			((Polyedge alter *)pe)->_hoops_SPHA = ++_hoops_SPHA;
	}


	ALLOC_ARRAY_ALIGNED_CACHED (_hoops_GHPCP, pe->point_count, DC_Point, 16);
	ALLOC_ARRAY_ALIGNED_CACHED (ws, pe->point_count, float, 16);
	ALLOC_ARRAY_CACHED (_hoops_ARCAR, pe->point_count, _hoops_GRCAR);
	_hoops_CRCAR = HD_Acquire_Clip_Points (nr, pe->bounding, pe->point_count, pe->points, _hoops_GHPCP, ws, _hoops_ARCAR);

	if (_hoops_CRCAR == 0)
		goto _hoops_HPAGR;


	if ((!ALLBITS(nr->_hoops_RHP->flags, _hoops_AGRIP) &&
		ANYBIT(nr->_hoops_RHP->line_style->flags, _hoops_RHISA)) ||
		(nr->_hoops_RHP->weight != 1 &&
		 !BIT(nr->_hoops_RHP->style, LCAP_ROUND))) {

		Line_Rendition alter &	_hoops_ASGIP = nr.Modify()->_hoops_RHP.Modify();
		
		_hoops_ASGIP->flags |= _hoops_AGRIP;
		_hoops_ASGIP->style |= LCAP_ROUND;
	}

	if (nr->_hoops_AHP != nr->_hoops_RHP ||
		nr->_hoops_AHP->weight < 0 ||
		nr->_hoops_RSGC->action.draw_dc_polyline != nr->_hoops_RSGC->action.draw_dc_edge) {
		_hoops_PSIHP const &		_hoops_HSIHP = nr.Modify()->_hoops_RSGC;

		/* _hoops_AHHCP _hoops_III _hoops_CCA _hoops_ISHA */
		nr->_hoops_AHP = nr->_hoops_RHP;
		if (nr->_hoops_AHP->weight < 0) {
			Line_Rendition alter &		_hoops_ASGIP = nr.Modify()->_hoops_AHP.Modify();

			_hoops_ASGIP->weight = (int)(HD_Compute_Generic_Size (nr, _hoops_ASGIP->_hoops_PHP, _hoops_ASGIP->_hoops_HHP, 1.0f, false, 0, true) + 0.5f);
		}

		if (_hoops_HSIHP->action.draw_dc_polyline != _hoops_HSIHP->action.draw_dc_edge)
			nr.Modify()->_hoops_RSGC.Modify()->action.draw_dc_polyline = _hoops_HSIHP->action.draw_dc_edge;
	}

	
	_hoops_IRIR = (unsigned char)(255.99f * nr->_hoops_RHP->_hoops_CHA->_hoops_IRIR);

	if (dc->_hoops_APHHP == null) {
		_hoops_CRIR = BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HPH);

		_hoops_HAACP = BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_GCP);
		_hoops_IAACP = BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_RGAC) && 
				   nr->_hoops_RHP->_hoops_CHA->_hoops_ARIR;

		if (_hoops_ICHA != null || _hoops_HAACP || (_hoops_CCHA || _hoops_IAACP) && !_hoops_RSHA) {
			ALLOC_ARRAY_ALIGNED_CACHED(_hoops_PAIIS, pe->point_count, _hoops_ARPA, 16);

		if (pe->_hoops_ICHA == null)
			ZERO_ARRAY (_hoops_PAIIS, pe->point_count, _hoops_ARPA);
		else 
			HD_Compute_World_Vertex_Planes (nr, pe->point_count,
											pe->points, pe->_hoops_ICHA, 
											_hoops_PAIIS);

		}
		else if (_hoops_RSHA != null) {
			ALLOC_ARRAY_ALIGNED_CACHED(_hoops_HAIIS, pe->_hoops_SPHA, _hoops_ARPA, 16);
			HD_Compute_World_Edge_Planes (nr, pe, _hoops_HAIIS);
		}

		if (_hoops_ICHA != null || _hoops_RSHA != null) {
			_hoops_CAACP = _hoops_CGR->_hoops_ISPHP ||
								BIT (nr->_hoops_IRR->_hoops_PPH, Rendo_LOCAL_VIEWER) ||
								BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HPH);
		}
	}

	_hoops_SRIIS = _hoops_GAIIS = null;
	_hoops_RAIIS = _hoops_AIAIA = null;

	_hoops_HIGSI = (_hoops_CCHA == null) && (_hoops_ICHA == null) &&
				(_hoops_PCHA == null) && !_hoops_CRIR;
	_hoops_AAIIS = (_hoops_ICHA && _hoops_ASHA) || (_hoops_PCHA && _hoops_RSHA);

#define _hoops_APIIS(_hoops_PPIIS, _hoops_HPIIS) do if (BIT(_hoops_PPIIS.options, _hoops_CHRH)) {	\
			RGBAS32 alter &	_hoops_HAPCR = _hoops_HPIIS;											\
			RGB				tmp = _hoops_HAPCR;											\
			tmp = HD_Apply_Color_Effects (tmp, _hoops_PPIIS);							\
			_hoops_HAPCR = RGBAS32 (tmp, _hoops_HAPCR.a);											\
		} while (0)

#define _hoops_IPIIS(_hoops_PPIIS, _hoops_HPIIS) do if (BIT(_hoops_PPIIS.options, _hoops_CHRH)) {		\
			RGBA alter &	_hoops_HAPCR = _hoops_HPIIS;											\
			RGB				tmp = _hoops_HAPCR;											\
			tmp = HD_Apply_Color_Effects (tmp, _hoops_PPIIS);							\
			_hoops_HAPCR = RGBA (tmp, _hoops_HAPCR.alpha);											\
		} while (0)

	points = _hoops_HRIGA;
	colors = _hoops_HIAI;
	planes = _hoops_IHRGA;
	params = _hoops_SHRGA;
	_hoops_HPHSA = _hoops_IGACP;

	if (!pe->_hoops_CCHA && !_hoops_HAACP &&
		(_hoops_ICHA || _hoops_RSHA || _hoops_CRIR)) {

		_hoops_AGH = _hoops_IAAA (point_count, _hoops_SPHA);
		ZALLOC_ARRAY_CACHED (_hoops_GHGCP, _hoops_AGH, RGBAS32);
	}

	_hoops_ISPI = _hoops_HSPI = -1;
	while (_hoops_PHHA-- > 0) {
		int								length = *lengths++;

		if (length < 0)
			length = -length;

		if (_hoops_AIHA) {
			_hoops_HSPI = *_hoops_AIHA++;
			_hoops_ISPI = 0; /* _hoops_GRHP _hoops_RH _hoops_HICA _hoops_RSPPP */
		}
		else {
			_hoops_HSPI++;
			_hoops_ISPI++;
		}

		if (_hoops_SPII != null)
			_hoops_SPII++;
		length--;
		while (length-- > 0) {
			if (_hoops_AIHA)
				_hoops_ISPI = *_hoops_AIHA++;
			else
				_hoops_ISPI++;
			if (_hoops_SPII != null)
				edge = *_hoops_SPII++;
			else
				edge++;

			/* _hoops_HPPP _hoops_RGR _hoops_III _hoops_CAGH */
			if (!ANYBIT (_hoops_ARCAR[_hoops_HSPI] & _hoops_ARCAR[_hoops_ISPI], ~_hoops_RPCAR)) {
				/* _hoops_HAR _hoops_CPIIS _hoops_SACH _hoops_SGGR _hoops_GGR _hoops_SPR _hoops_HAGA */
				_hoops_HRIIS (_hoops_GHPCP[_hoops_HSPI], points[0]);
				_hoops_HRIIS (_hoops_GHPCP[_hoops_ISPI], points[1]);
				points += 2;

				if (pe->_hoops_CCHA || _hoops_HAACP) {
					float		_hoops_SPIIS = nr->_hoops_RHP->_hoops_CHA->_hoops_IRIR;

#ifndef DISABLE_TEXTURING
					if (_hoops_CCHA) {
						int			i;

						for (i=0; i<param_width; i++) *params++ = _hoops_CCHA[_hoops_HSPI*param_width+i];
						for (i=0; i<param_width; i++) *params++ = _hoops_CCHA[_hoops_ISPI*param_width+i];
					}
#endif
					if (_hoops_PAIIS) {
						planes[0] = _hoops_PAIIS[_hoops_HSPI];
						planes[1] = _hoops_PAIIS[_hoops_ISPI];
						planes += 2;
					}
					else if (_hoops_HAIIS) {
						planes[0] = _hoops_HAIIS[edge];
						planes[1] = _hoops_HAIIS[edge];
						planes += 2;
					}

					if (_hoops_PCHA) {
						_hoops_HPHSA[0] = RGBA (_hoops_PCHA[_hoops_HSPI], _hoops_SPIIS);
						_hoops_IPIIS (_hoops_PHAH, _hoops_HPHSA[0]);
						_hoops_HPHSA[1] = RGBA (_hoops_PCHA[_hoops_ISPI], _hoops_SPIIS);
						_hoops_IPIIS (_hoops_PHAH, _hoops_HPHSA[1]);
						_hoops_HPHSA += 2;
					}
					else if (_hoops_ASHA) {
						_hoops_HPHSA[0] = RGBA (_hoops_ASHA[edge], _hoops_SPIIS);
						_hoops_IPIIS (_hoops_PHAH, _hoops_HPHSA[0]);
						_hoops_HPHSA[1] = _hoops_HPHSA[0];
						_hoops_HPHSA += 2;
					}
					else {
						RGBAS32		tmp = nr->_hoops_RHP->color;
						_hoops_HPHSA[0] = tmp;
						_hoops_IPIIS (_hoops_PHAH, _hoops_HPHSA[0]);
						_hoops_HPHSA[1] = _hoops_HPHSA[0];
						_hoops_HPHSA += 2;
					}
				}
				else if (_hoops_ICHA || _hoops_HAIIS || _hoops_CRIR) {
					_hoops_HHA const &		_hoops_ISHIR = nr->_hoops_RHP->_hoops_CHA;
					RGBA							tmp;

					if (_hoops_PCHA) {
						_hoops_SRIIS = &_hoops_PCHA[_hoops_HSPI];
						_hoops_GAIIS = &_hoops_PCHA[_hoops_ISPI];
					}
					else if (_hoops_ASHA)
						_hoops_SRIIS = _hoops_GAIIS = &_hoops_ASHA[edge];

					if (_hoops_ICHA) {
						_hoops_RAIIS = &_hoops_PAIIS[_hoops_HSPI];
						_hoops_AIAIA = &_hoops_PAIIS[_hoops_ISPI];
					}
					else if (_hoops_HAIIS)
						_hoops_RAIIS = _hoops_AIAIA = &_hoops_HAIIS[edge];

					if (!_hoops_HIGSI) {
						if (_hoops_GHGCP[_hoops_HSPI] == _hoops_CAHSR::_hoops_SAHSR || _hoops_AAIIS) {
							_hoops_CSACP (nr, _hoops_ISHIR, _hoops_CAACP, &pe->points[_hoops_HSPI], _hoops_SRIIS, _hoops_RAIIS, null, &tmp);
							_hoops_GHGCP[_hoops_HSPI] = RGBAS32 (tmp, _hoops_IRIR);
							_hoops_APIIS (_hoops_PHAH, _hoops_GHGCP[_hoops_HSPI]);
							_hoops_SIPCP (dc, _hoops_GHGCP[_hoops_HSPI]);
						}
						*colors++ = _hoops_GHGCP[_hoops_HSPI];

						if (_hoops_GHGCP[_hoops_ISPI] == _hoops_CAHSR::_hoops_SAHSR || _hoops_AAIIS) {
							_hoops_CSACP (nr, _hoops_ISHIR, _hoops_CAACP, &pe->points[_hoops_ISPI], _hoops_GAIIS, _hoops_AIAIA, null, &tmp);
							_hoops_GHGCP[_hoops_ISPI] = RGBAS32 (tmp, _hoops_IRIR);
							_hoops_APIIS (_hoops_PHAH, _hoops_GHGCP[_hoops_ISPI]);
							_hoops_SIPCP (dc, _hoops_GHGCP[_hoops_ISPI]);
						}
						*colors++ = _hoops_GHGCP[_hoops_ISPI];
					}
					else {
						if (_hoops_GHGCP[edge] == _hoops_CAHSR::_hoops_SAHSR) {
							_hoops_CSACP (nr, _hoops_ISHIR, _hoops_CAACP, &pe->points[_hoops_ISPI], _hoops_GAIIS, _hoops_AIAIA, null, &tmp);
							_hoops_GHGCP[edge] = RGBAS32 (tmp, _hoops_IRIR);
							_hoops_APIIS (_hoops_PHAH, _hoops_GHGCP[edge]);
							_hoops_SIPCP (dc, _hoops_GHGCP[edge]);
						}
						*colors++ = _hoops_GHGCP[edge];
					}
				}
				else {
					if (_hoops_PCHA) {
						*colors = RGBAS32 (_hoops_PCHA[_hoops_HSPI], _hoops_IRIR);
						_hoops_APIIS (_hoops_PHAH, *colors);
						_hoops_SIPCP (dc, *colors);
						colors++;

						*colors = RGBAS32 (_hoops_PCHA[_hoops_ISPI], _hoops_IRIR);
						_hoops_APIIS (_hoops_PHAH, *colors);
						_hoops_SIPCP (dc, *colors);
						colors++;
					}
					else if (_hoops_ASHA) {
						RGBAS32			result = RGBAS32 (_hoops_ASHA[edge], _hoops_IRIR);
						_hoops_APIIS (_hoops_PHAH, result);
						_hoops_SIPCP (dc, result);
						*colors++ = result;

						if (!_hoops_HIGSI)
							*colors++ = result;
					}
				}

				/* _hoops_GII _hoops_GHIPR-_hoops_RH-_hoops_RHC (_hoops_ARSHA) _hoops_CIHH _hoops_IRHS _hoops_IS _hoops_SHH _hoops_GIR _hoops_ARI */
				if (BIT (_hoops_ARCAR[_hoops_HSPI] | _hoops_ARCAR[_hoops_ISPI], _hoops_IPCAR)) {
					_hoops_HHCR const &		_hoops_IHCR = nr->transform_rendition;
					int								a, b;
					float							_hoops_PRSAS, _hoops_HRSAS;
					float							trim;
					float							_hoops_PASAS = 1.0f / _hoops_IHCR->_hoops_CHCR;
					float							_hoops_SRSAS = _hoops_IHCR->_hoops_GSCH[0] * dc->_hoops_PGCC._hoops_PASHP;

					/* _hoops_HAIHR _hoops_RSSA _hoops_HIS _hoops_SGS _hoops_PPSR _hoops_RAIGR _hoops_HRGR _hoops_GGR _hoops_RIPS _hoops_IIGR _hoops_RH _hoops_RHC
					 * _hoops_PPR _hoops_PPSR _hoops_IHAC _hoops_HRGR _hoops_GHIPR.
					 */
					if (ws[_hoops_HSPI] >= _hoops_IHCR->_hoops_CHCR) {
						a = 0;	_hoops_PRSAS = ws[_hoops_HSPI];
						b = 1;	_hoops_HRSAS = ws[_hoops_ISPI];
					}
					else {
						a = 1;	_hoops_PRSAS = ws[_hoops_ISPI];
						b = 0;	_hoops_HRSAS = ws[_hoops_HSPI];
					}

					a -= 2; b -= 2;		/* _hoops_AGCR _hoops_CGRPR _hoops_RH _hoops_PSAI _hoops_GSSRH _hoops_RH _hoops_CICRR */

					trim = (_hoops_IHCR->_hoops_CHCR - _hoops_PRSAS) / (_hoops_HRSAS - _hoops_PRSAS);

					points[b].x = (_hoops_PRSAS*points[a].x + (points[b].x - _hoops_PRSAS*points[a].x) * trim) * _hoops_PASAS;
					points[b].y = (_hoops_PRSAS*points[a].y + (points[b].y - _hoops_PRSAS*points[a].y) * trim) * _hoops_PASAS;
					points[b].z = _hoops_SRSAS;

					if (colors != _hoops_HIAI) {
						if (!_hoops_HIGSI)
							_hoops_PCRGA (colors[a], colors[b], trim, colors[b]);
					}
					else if (_hoops_HPHSA != _hoops_IGACP)
						_hoops_ACRGA (_hoops_HPHSA[a], _hoops_HPHSA[b], trim, _hoops_HPHSA[b]);
					if (planes != _hoops_IHRGA)
						_hoops_RGRGA (planes[a], planes[b], trim, planes[b]);
#ifndef DISABLE_TEXTURING
					if (params != _hoops_SHRGA)
						_hoops_GGRGA (nr, &params[param_width*a], &params[param_width*b], trim,
											   &params[param_width*b], _hoops_IHCR->_hoops_CHCR/_hoops_PRSAS, param_width);
#endif
				}
			}


			if (points != _hoops_HRIGA &&
				((points-_hoops_HRIGA) >= _hoops_AGACP || _hoops_PHHA == 0 && length == 0)) {
				int			count = -(points-_hoops_HRIGA);

#ifndef DISABLE_TEXTURING
				if (_hoops_CCHA)
					_hoops_RGIGH (nr, count, _hoops_HRIGA,
												   (_hoops_HPHSA != _hoops_IGACP) ? _hoops_IGACP : null,
												   (planes != _hoops_IHRGA) ? _hoops_IHRGA : null,
												   _hoops_SHRGA, param_width, pe->_hoops_SCAI);
				else
#endif
#ifndef DISABLE_PHONG
				if (_hoops_HAACP)
					_hoops_GGIGH (nr, count, _hoops_HRIGA,
												(_hoops_HPHSA != _hoops_IGACP) ? _hoops_IGACP: null,
												_hoops_IHRGA);
				else
#endif
				if (colors != _hoops_HIAI) {
					if (!_hoops_HIGSI)
						_hoops_SSHGH (nr, count, _hoops_HRIGA, _hoops_HIAI);
					else
						_hoops_CSHGH (nr, count, _hoops_HRIGA, _hoops_HIAI, false);
				}
				else
					_hoops_SRPIP (nr, count, _hoops_HRIGA);

				points = _hoops_HRIGA;
				colors = _hoops_HIAI;
				planes = _hoops_IHRGA;
				params = _hoops_SHRGA;
				_hoops_HPHSA = _hoops_IGACP;
			}

			_hoops_HSPI = _hoops_ISPI;
		}

		/* _hoops_GAPA _hoops_CRPHR _hoops_CGH _hoops_SHH _hoops_IRS _hoops_RIRA _hoops_GHIR _hoops_IS _hoops_ISPR _hoops_SSHGR */
		if (_hoops_GGPGR(nr)) 
			break; /* _hoops_HRGHP */
	}

	if (_hoops_GHGCP != null)
		FREE_ARRAY (_hoops_GHGCP, _hoops_AGH, RGBAS32);

#endif

_hoops_HPAGR:
	if (_hoops_HAIIS != null)
		FREE_ARRAY_ALIGNED (_hoops_HAIIS, pe->_hoops_SPHA, _hoops_ARPA, 16);
	if (_hoops_GHPCP != null)
		FREE_ARRAY_ALIGNED (_hoops_GHPCP, pe->point_count, DC_Point, 16);
	if (ws != null)
		FREE_ARRAY_ALIGNED (ws, pe->point_count, float, 16);
	if (_hoops_PAIIS != null)
		FREE_ARRAY_ALIGNED(_hoops_PAIIS, pe->point_count, _hoops_ARPA, 16);
	FREE_ARRAY (_hoops_ARCAR, pe->point_count, _hoops_GRCAR);
}


GLOBAL_FUNCTION void HD_Std_3D_Polyedge_From_Tristrip (
	Net_Rendition const & 		nr,
	Polyedge const *			pe,
	Tristrip const *			ts) {
	UNREFERENCED (pe);

	// _hoops_PAGA: _hoops_PS _hoops_CHR _hoops_SAHR _hoops_IRCC _hoops_IS _hoops_HGCR _hoops_HHH _hoops_SPPR _hoops_IIGR _hoops_RH _hoops_CCGI _hoops_CHCC _hoops_IS _hoops_SHH _hoops_RCRR _hoops_SGS _hoops_GHIIS
	// _hoops_HS _hoops_HHH _hoops_SCCI _hoops_GGR _hoops_RGCH -- _hoops_SR *_hoops_GA'_hoops_RA* _hoops_RRP _hoops_RCSAR _hoops_SCPH _hoops_ISHA _hoops_GGHAA _hoops_IH _hoops_SGS.
	// _hoops_CGP _hoops_HCR _hoops_RH _hoops_SPPR _hoops_RRP _hoops_IS _hoops_SHH _hoops_CHCC, _hoops_RGR _hoops_API _hoops_GRS _hoops_RRP _hoops_IS _hoops_AGRP
	do {
		Polyedge alter *	polyedge;

		ZALLOC (polyedge, Polyedge);
		_hoops_ICAI (polyedge);

		polyedge->points = ts->points;
		polyedge->point_count = ts->point_count;
		polyedge->_hoops_SPHA = ts->face_count;
		polyedge->bounding = ts->bounding;
		polyedge->_hoops_GSCP = ts->_hoops_GSCP;
		polyedge->_hoops_SRHA = DL_POLYEDGE_FROM_TRISTRIP | DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS | _hoops_GAHH;

		polyedge->_hoops_PHHA = ts->_hoops_PHHA;
		polyedge->lengths = ts->lengths;
		polyedge->total = ts->total;
		polyedge->_hoops_AIHA = ts->_hoops_AIHA;
		polyedge->_hoops_SPII = ts->face_indices;

		_hoops_IACIP (nr, polyedge);

		HI_Free_Polyedge_List (polyedge);
	} while ((ts = ts->next) != null);
}






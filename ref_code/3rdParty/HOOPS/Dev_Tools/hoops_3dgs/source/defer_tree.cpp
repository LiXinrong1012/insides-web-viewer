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
 * $Id: obf_tmp.txt 1.109 2010-12-06 22:05:41 jason Exp $
 */


#include "hoops.h"
#include "database.h"	/* (_hoops_IRHH _hoops_GSPPP _hoops_SHH _hoops_RSPPP _hoops_AHCA _hoops_ASPPP _hoops_PRCHR) */
#include "driver.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "adt.h"
 

local void _hoops_PSPPP(Display_Context alter * dc, _hoops_HSPPP alter *	_hoops_ISPPP, int _hoops_IGIC)
{
	if (BIT(_hoops_ISPPP->_hoops_APHGA->current, _hoops_CSPPP)) {

		_hoops_ISPPP->_hoops_APHGA.Modify();

		_hoops_ISPPP->_hoops_APHGA->current &= ~_hoops_CSPPP;
		_hoops_ISPPP->_hoops_APHGA->_hoops_RCSHR &= ~_hoops_CSPPP;

		_hoops_ISPPP->_hoops_APHGA->transform_rendition.Modify();
		_hoops_ISPPP->_hoops_APHGA->transform_rendition->_hoops_SSPPP = _hoops_GGHPP;
	}

	_hoops_RGHPP alter * _hoops_SGCCA = null;

	if (dc->_hoops_AGHPP == null){
		dc->_hoops_AGHPP = POOL_NEW(dc->memory_pool, _hoops_PGHPP)(dc->memory_pool);
		dc->_hoops_HGHPP = POOL_NEW(dc->memory_pool, _hoops_IGHPP)(dc->memory_pool);
	} 
	else 
		dc->_hoops_HGHPP->LookupItem(_hoops_IGIC, &_hoops_SGCCA);

	if (_hoops_SGCCA == null) {

		POOL_ZALLOC (_hoops_SGCCA, _hoops_RGHPP, dc->memory_pool);

		_hoops_SGCCA->_hoops_ASRGR = &_hoops_SGCCA->list;

		dc->_hoops_AGHPP->Push(_hoops_SGCCA, _hoops_IGIC);
		dc->_hoops_HGHPP->InsertItem(_hoops_IGIC, _hoops_SGCCA);
	}

	_hoops_ISPPP->next = *_hoops_SGCCA->_hoops_ASRGR;
	*_hoops_SGCCA->_hoops_ASRGR = _hoops_ISPPP;
	_hoops_SGCCA->_hoops_ASRGR = &_hoops_ISPPP->next;
}

void HC_CDECL HD_Defer_Tree_Batch (
	Net_Rendition const & 		inr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path,
	int							_hoops_GPIGR,
	Geometry const *			geometry,
	int							_hoops_RRCRP) {
	Net_Rendition				nr = inr;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_HSPPP alter *	_hoops_ISPPP;


	POOL_ZALLOC (_hoops_ISPPP, _hoops_HSPPP, dc->memory_pool);
	_hoops_ISPPP->segment = _hoops_SRCP;
	_hoops_ISPPP->path = path;
	_hoops_ISPPP->geometry = geometry;
	_hoops_ISPPP->_hoops_CPGPR = dc->_hoops_CPGPR;

	// ???
	nr.Modify()->current &= _hoops_CGHPP;
	_hoops_ISPPP->_hoops_APHGA = nr;

	if (_hoops_RRCRP == -1) {

		if (geometry == null)
			_hoops_GPRH(_hoops_SGHPP)++;
		else
		if (geometry->type == _hoops_HCIIR)
			_hoops_GPRH(_hoops_GRHPP)++;
		else 
		if (geometry->type == _hoops_AHIP)
			_hoops_GPRH(_hoops_RRHPP)++;
		else
			_hoops_GPRH(_hoops_ARHPP)++;

		if (_hoops_GPIGR >= _hoops_ICHS)
			_hoops_GPIGR = _hoops_ICHS - 1;
		else if (_hoops_GPIGR < 0)
			_hoops_GPIGR = 0;

		// _hoops_AAGIR
		_hoops_GPIGR = _hoops_ICHS - 1  -  _hoops_GPIGR;

		_hoops_PSPPP(dc, _hoops_ISPPP, _hoops_GPIGR*100);
	}
	else {

		_hoops_GPRH(_hoops_PRHPP)++;

		_hoops_PSPPP(dc, _hoops_ISPPP, _hoops_RRCRP);
	}

}



GLOBAL_FUNCTION void HD_Defer_Tree (
	Net_Rendition const & 		inr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path,
	Geometry const *			geometry) {
	Net_Rendition				nr = inr;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_HSPPP alter *	_hoops_ISPPP;
	_hoops_RGHPP alter *	_hoops_SGCCA;

	POOL_ZALLOC (_hoops_ISPPP, _hoops_HSPPP, dc->memory_pool);
	_hoops_ISPPP->segment = _hoops_SRCP;
	_hoops_ISPPP->path = path;
	_hoops_ISPPP->geometry = geometry;
	_hoops_ISPPP->_hoops_CPGPR = dc->_hoops_CPGPR;

	nr.Modify()->current &= _hoops_CGHPP;
	_hoops_ISPPP->_hoops_APHGA = nr;

	/* _hoops_GGCR _hoops_IS _hoops_IRPR _hoops_HIGR; _hoops_PH _hoops_RSGR _hoops_CRS */
	if (geometry != null)
		_hoops_SGCCA = &dc->_hoops_HRHPP[_hoops_IRHPP];
	else if (ANYBIT (nr->_hoops_RCSHR, _hoops_CRHPP|_hoops_CRSI))
		_hoops_SGCCA = &dc->_hoops_HRHPP[_hoops_SRHPP];
	else if (BIT (nr->_hoops_RCSHR, _hoops_GAHPP) || 
			!BIT (nr->_hoops_RCSHR, _hoops_CSGGR))
		_hoops_SGCCA = &dc->_hoops_HRHPP[_hoops_RAHPP];
	else
		_hoops_SGCCA = &dc->_hoops_HRHPP[_hoops_IRHPP];
	
	_hoops_ISPPP->next = *_hoops_SGCCA->_hoops_ASRGR;
	*_hoops_SGCCA->_hoops_ASRGR = _hoops_ISPPP;
	_hoops_SGCCA->_hoops_ASRGR = &_hoops_ISPPP->next;
}

/****************************************************************************************************/



local float _hoops_AAHPP(Net_Rendition const & nr, _hoops_CRCP const * _hoops_SRCP, Bounding const & _hoops_RCHS) 
{
	_hoops_HHCR	const &		_hoops_IHCR = nr->transform_rendition;

	float const *					weights = nr->_hoops_CPP->_hoops_SSIRP;
	float							value = 0.0f;

	if (!_hoops_RCHS._hoops_HICAR()) {
		_hoops_HHRA const *				_hoops_SPH = _hoops_IHCR->_hoops_SPH;

		Bounding	_hoops_PAHPP;

		if (weights[_hoops_RSIRP] != 0.0f ||
			weights[_hoops_ASIRP] != 0.0f ||
			weights[_hoops_SCIRP] != 0.0f) {
	
			_hoops_PAHPP = _hoops_RCHS._hoops_SCIS (&_hoops_IHCR->_hoops_IPH->data.elements[0][0]);
			_hoops_PAHPP = _hoops_PAHPP._hoops_SCIS (&_hoops_IHCR->_hoops_SPH->_hoops_PRPA.elements[0][0]);
		}

		if (weights[_hoops_SCIRP] != 0.0f)
			value += weights[_hoops_SCIRP] * _hoops_PAHPP->sphere.radius;

		if (weights[_hoops_GSIRP] != 0.0f) {
	
			ASSERT(0);

			Point						in[8];

			_hoops_RCHS->cuboid._hoops_GPSC(&in[0]);

			int count = 8;

			DC_Point					_hoops_PAGR[8];
			float						ws[8];
			_hoops_GRCAR					_hoops_ARCAR[8];

			(*HOOPS_WORLD->_hoops_PHCAR[_hoops_IHCR->_hoops_HGSC])
				(_hoops_IHCR, count, in, &_hoops_IHCR->matrix->data.elements[0][0], &nr->_hoops_SAIR->_hoops_HHCAR, _hoops_PAGR, ws, _hoops_ARCAR);

			int							_hoops_HAHPP = 0;

			_hoops_PACIR			rect;


			for (int i=0; i<8; i++) {

				if (!BIT (_hoops_ARCAR[i], _hoops_IPCAR)) {

					if (rect.left > _hoops_PAGR[i].x)
						rect.left = _hoops_PAGR[i].x;
					else if (rect.right < _hoops_PAGR[i].x)
						rect.right = _hoops_PAGR[i].x;

					if (rect.bottom > _hoops_PAGR[i].y)
						rect.bottom = _hoops_PAGR[i].y;
					else if (rect.top < _hoops_PAGR[i].y)
						rect.top = _hoops_PAGR[i].y;
				}

				_hoops_HAHPP |= (int)_hoops_ARCAR[i];
			}

			_hoops_PACIR const &	extent = nr->_hoops_SAIR->extent;

			rect._hoops_PGPGP(extent);

			float _hoops_RCGCR = (float)((rect.right - rect.left + 1) * (rect.top-rect.bottom + 1)) /
				(float)((extent.right - extent.left + 1) * (extent.top - extent.bottom + 1));

			if (BIT (_hoops_HAHPP, _hoops_IPCAR))
				_hoops_RCGCR += 0.5f * (1.0f - _hoops_RCGCR);

			value += weights[_hoops_GSIRP] * _hoops_RCGCR;
		}

		if (weights[_hoops_RSIRP] != 0.0f) {
			float _hoops_CGSIR = _hoops_PAHPP->sphere.center.z - _hoops_PAHPP->sphere.radius;
			value += weights[_hoops_RSIRP] * -_hoops_CGSIR / _hoops_SPH->_hoops_SRIR;
		}

		if (weights[_hoops_ASIRP] != 0.0f) {

			Point const &	center = _hoops_PAHPP->sphere.center;
			float _hoops_CGSIR = _hoops_SGIHR (center.x * center.x + center.y * center.y);

			if (_hoops_SPH->projection == _hoops_GHH) {
				_hoops_CGSIR = _hoops_AGGGA (_hoops_CGSIR, center.z+_hoops_SPH->_hoops_SRIR);
				_hoops_CGSIR = _hoops_CGSIR / _hoops_AGGGA (_hoops_AHIA (_hoops_SPH->_hoops_ISPA, _hoops_SPH->_hoops_SSPA), _hoops_SPH->_hoops_SRIR);
			}
			else {
				_hoops_CGSIR = _hoops_CGSIR / _hoops_AHIA (_hoops_SPH->_hoops_ISPA, _hoops_SPH->_hoops_SSPA);
			}

			value += weights[_hoops_ASIRP] * (1.0f - _hoops_CGSIR);
		}

		if (weights[_hoops_PSIRP] != 0.0f) {
			value += weights[_hoops_PSIRP] * _hoops_RCHS->_hoops_CGCIR;
		}
	}

	if (weights[_hoops_HSIRP] != 0.0f)
		value += weights[_hoops_HSIRP] * (float)_hoops_SRCP->priority;

	return value;
}


/* _hoops_PCGR _hoops_IH "_hoops_SRGS" _hoops_SGS (_hoops_RPP _hoops_IGI _hoops_GPP _hoops_IRS _hoops_CAGH'_hoops_GRI _hoops_CPAP) _hoops_IIHP _hoops_SGS _hoops_CPAP _hoops_CRGR _hoops_IRS _hoops_SIHPA */

GLOBAL_FUNCTION void HD_Ordered_Segment (
	Net_Rendition const & 			inr,
	_hoops_CRCP const *					_hoops_SRCP) {
	Display_Context alter *			dc = (Display_Context alter *)inr->_hoops_SRA;
	Net_Rendition					nr = inr.Copy();
	_hoops_HHCR				_hoops_IHCR = nr->transform_rendition.Modify();

	ASSERT(dc->_hoops_IAHPP != null);

	_hoops_IHCR->flags |= _hoops_CAHPP;

	_hoops_HSPPP alter *		_hoops_ISPPP;
	
	POOL_ZALLOC (_hoops_ISPPP, _hoops_HSPPP, dc->memory_pool);

	_hoops_ISPPP->segment = _hoops_SRCP;
	if (dc->_hoops_AHSI != null)
		_hoops_ISPPP->path = dc->_hoops_AHSI->path;
	_hoops_ISPPP->_hoops_APHGA = nr;
	_hoops_ISPPP->_hoops_CPGPR = dc->_hoops_CPGPR;

	_hoops_ISPPP->value = _hoops_AAHPP(nr, _hoops_SRCP, _hoops_SRCP->bounding); 

	if (_hoops_ISPPP->value < dc->_hoops_IAHPP->_hoops_SAHPP)
		dc->_hoops_IAHPP->_hoops_SAHPP = _hoops_ISPPP->value;

	if (_hoops_ISPPP->value > dc->_hoops_IAHPP->_hoops_GPHPP)
		dc->_hoops_IAHPP->_hoops_GPHPP = _hoops_ISPPP->value;

	_hoops_ISPPP->next = dc->_hoops_IAHPP->list;
	dc->_hoops_IAHPP->list = _hoops_ISPPP;
}

GLOBAL_FUNCTION Geometry const * HD_Ordered_Render (
	Net_Rendition const & 			inr,
	Geometry const *				geometry,
	Action_Mask						mask,
	bool							single) {
	Display_Context alter *			dc = (Display_Context alter *)inr->_hoops_SRA;
	_hoops_CRCP const *					_hoops_SRCP = geometry->owner;

	ASSERT(dc->_hoops_IAHPP != null);

	if (_hoops_SRCP == null) {
		/* _hoops_HAR _hoops_IRS _hoops_CAGH _hoops_PAPA _hoops_SRGS, _hoops_HIS _hoops_SAHR _hoops_SGH _hoops_RH _hoops_GSSR _hoops_PGSA _hoops_CRAA */
		_hoops_IGRS (dc);
		_hoops_RPHPP (inr, geometry, mask, single);
		_hoops_SGRS (dc);
		return null;
	}

	Net_Rendition			nr = inr.Copy();
	_hoops_HHCR		_hoops_IHCR = nr->transform_rendition.Modify();
	_hoops_IHCR->_hoops_SSPPP = _hoops_APHPP;

	if (BIT (nr->transform_rendition->heuristics, _hoops_SAIRP))
		nr->current &= _hoops_CGHPP;
	else {
		nr->current &= ~_hoops_CSPPP;
		nr->_hoops_RCSHR &= ~_hoops_CSPPP;
	}

	_hoops_HSPPP alter *		_hoops_ISPPP;
	POOL_ZALLOC (_hoops_ISPPP, _hoops_HSPPP, dc->memory_pool);

	_hoops_ISPPP->segment = _hoops_SRCP;
	if (dc->_hoops_AHSI != null)
		_hoops_ISPPP->path = dc->_hoops_AHSI->path;
	_hoops_ISPPP->_hoops_APHGA = nr;
	_hoops_ISPPP->_hoops_CPGPR = dc->_hoops_CPGPR;

	_hoops_ISPPP->value = _hoops_AAHPP(nr, _hoops_SRCP, _hoops_SRCP->_hoops_HSRIR); 

	if (_hoops_ISPPP->value < dc->_hoops_IAHPP->_hoops_SAHPP)
		dc->_hoops_IAHPP->_hoops_SAHPP = _hoops_ISPPP->value;

	if (_hoops_ISPPP->value > dc->_hoops_IAHPP->_hoops_GPHPP)
		dc->_hoops_IAHPP->_hoops_GPHPP = _hoops_ISPPP->value;

	_hoops_ISPPP->next = dc->_hoops_IAHPP->list;
	dc->_hoops_IAHPP->list = _hoops_ISPPP;

	return null;
}

/* _hoops_CCASA _hoops_RH _hoops_SIHPA _hoops_CRGR _hoops_GSSR _hoops_PISI _hoops_CPHRA */

GLOBAL_FUNCTION void HD_Defer_Ordered (
	Net_Rendition const & 			nr,
	bool							_hoops_PPHPP) {

	Display_Context alter *			dc = (Display_Context alter *)nr->_hoops_SRA;

	_hoops_HPHPP * _hoops_IAHPP = dc->_hoops_IAHPP;

	ASSERT(_hoops_IAHPP != null);

	dc->_hoops_IAHPP = _hoops_IAHPP->next;

	if (_hoops_IAHPP->list != null) {

		if (_hoops_PPHPP) {

			while (_hoops_IAHPP->list) {

				_hoops_HSPPP alter *	_hoops_ISPPP = _hoops_IAHPP->list;
				_hoops_IAHPP->list = _hoops_ISPPP->next;

				_hoops_ISPPP->_hoops_APHGA.release();
				_hoops_ISPPP->path.release();
				FREE(_hoops_ISPPP, _hoops_HSPPP);
			}
		}
		else {

			float _hoops_RPIS = _hoops_IAHPP->_hoops_GPHPP - _hoops_IAHPP->_hoops_SAHPP;

			int _hoops_IPHPP = _hoops_IAHPP->_hoops_AGCRP - _hoops_IAHPP->_hoops_RGCRP;

			float scale = (float)_hoops_IPHPP;
			
			if (_hoops_RPIS > 0.0)
				scale /= _hoops_RPIS;

			while (_hoops_IAHPP->list) {

				_hoops_HSPPP alter *	_hoops_ISPPP = _hoops_IAHPP->list;
				_hoops_IAHPP->list = _hoops_ISPPP->next;

				_hoops_RCCA(_hoops_PRHPP)++;

				int _hoops_CPHPP = _hoops_IAHPP->_hoops_AGCRP -
					(int)((_hoops_ISPPP->value - _hoops_IAHPP->_hoops_SAHPP) * scale);

				_hoops_PSPPP(dc, _hoops_ISPPP, _hoops_CPHPP);
			}
			
		}	
	}

	FREE (_hoops_IAHPP, _hoops_HPHPP);
}


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
 * * $Id: obf_tmp.txt 1.434 2011-01-26 22:32:58 jason Exp $
 */


#include "hoops.h"

#include "database.h"
#include "driver.h"
#include "phedron.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "patterns.h"
#include "tandt.h"
#include "adt.h"


/***********************************************************************
 ***********************************************************************
						_hoops_GRSCP _hoops_RRSCP
 ***********************************************************************
 ***********************************************************************/


#ifndef _hoops_GCSIR
local void _hoops_CAAGR (
	Net_Rendition const & nr,
	int								left,
	int								right,
	int								bottom,
	int								top) {
	_hoops_HCSIR alter		*_hoops_ICSIR = null;

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RGAAP))
		return;
#endif

	if (left > right || bottom > top)
		return;

	if (nr->_hoops_SAIR->_hoops_ASSIR != null)
		_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	/*
	 * _hoops_CAAP _hoops_RH _hoops_SSH _hoops_SRHR
	 * _hoops_PS'_hoops_ASAR _hoops_CPIC _hoops_IS _hoops_PAIHR _hoops_ARSCP, _hoops_CR _hoops_SR _hoops_ACPA _hoops_RH
	 * _hoops_CIAS _hoops_AHCR _hoops_PIRA _hoops_HRGR 0xFFFF _hoops_GCSS _hoops_GAR _hoops_PCCP _hoops_APPC _hoops_ICHRR, _hoops_PGAP
	 * _hoops_HRGR _hoops_RH _hoops_PSHR _hoops_GAR 0xFF _hoops_GCSS _hoops_GGR _hoops_PGCR _hoops_GCSRR.	 _hoops_PHGP _hoops_SR'_hoops_GCPP _hoops_AASA
	 * _hoops_GGSR _hoops_IS _hoops_IRS _hoops_ICSI _hoops_CISA _hoops_API.
	 */
	if (_hoops_ICSIR != null && _hoops_ICSIR->depth_buffer != null) {
		/* _hoops_IHH _hoops_ISPR _hoops_IS _hoops_IRHH _hoops_RCRR _hoops_CCAC _hoops_HRGR _hoops_GIAA _hoops_RH _hoops_SRHR */
		if ((left - _hoops_ICSIR->offset.x) + (right - left + 1) >
												_hoops_ICSIR->depth_buffer->width ||
			(bottom - _hoops_ICSIR->offset.y) + (top - bottom + 1) >
												_hoops_ICSIR->depth_buffer->height)
			return;

		if (_hoops_ICSIR->depth_buffer->rasters != null) {
			_hoops_RAAH alter * const			*_hoops_SCGCR;
			_hoops_RAAH alter * const			*_hoops_HSGCR;
			int								_hoops_ASGCR;
			int								_hoops_PRSCP;

			_hoops_ASGCR = sizeof (_hoops_RAAH) * (right - left + 1);
			_hoops_PRSCP = left - _hoops_ICSIR->offset.x;

			_hoops_SCGCR = (_hoops_RAAH alter * const *)
				&_hoops_ICSIR->depth_buffer->_hoops_RCPIR[bottom - _hoops_ICSIR->offset.y];
			_hoops_HSGCR = (_hoops_RAAH alter * const *)
				&_hoops_ICSIR->depth_buffer->_hoops_RCPIR[top - _hoops_ICSIR->offset.y];

			do SET_MEMORY (&_hoops_SCGCR[0][_hoops_PRSCP], _hoops_ASGCR, 0x7F);
			_hoops_RGGA (_hoops_SCGCR++ == _hoops_HSGCR);
		}
		_hoops_ICSIR->_hoops_HRSCP = false;
	}
}
#endif


GLOBAL_FUNCTION void HD_Clear_Software_Z_Buffer (
	Net_Rendition const & nr) {

#ifndef _hoops_GCSIR

	Int_Rectangle const	&	_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

	_hoops_CAAGR (nr, _hoops_GPHH.left, _hoops_GPHH.right, _hoops_GPHH.bottom, _hoops_GPHH.top);
#endif
}



#ifndef _hoops_GCSIR
local void _hoops_IRSCP (
	Net_Rendition const & nr,
	_hoops_RAAH						z,
	int								left,
	int								right,
	int								bottom,
	int								top) {
	_hoops_RAAH const * const			*_hoops_CRSCP;
	_hoops_RAAH const * const			*_hoops_SRSCP;
	DC_Point						start, end;
	_hoops_HCSIR const		*_hoops_ICSIR;

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	/* _hoops_SHPR _hoops_GC */

	bottom -= _hoops_ICSIR->offset.y;
	top	   -= _hoops_ICSIR->offset.y;
	left   -= _hoops_ICSIR->offset.x;
	right  -= _hoops_ICSIR->offset.x;

	/* _hoops_CSCR _hoops_GC */

	if (bottom < 0)
		bottom = 0;
	if (top > _hoops_ICSIR->_hoops_HIAI->height - 1)
		top = _hoops_ICSIR->_hoops_HIAI->height - 1;
	if (left < 0)
		left = 0;
	if (right > _hoops_ICSIR->_hoops_HIAI->width - 1)
		right = _hoops_ICSIR->_hoops_HIAI->width - 1;
	if (left > right || bottom > top)
		return;

	end.y = start.y = (float)(bottom + _hoops_ICSIR->offset.y); /* _hoops_SHPR _hoops_GC */
	end.z = start.z = 0.0f;

	_hoops_CRSCP = (_hoops_RAAH const * const *)&_hoops_ICSIR->depth_buffer->_hoops_RCPIR[bottom];
	_hoops_SRSCP = (_hoops_RAAH const * const *)&_hoops_ICSIR->depth_buffer->_hoops_RCPIR[top + 1];
	do {
		_hoops_RAAH const			*_hoops_GASCP = *_hoops_CRSCP;
		_hoops_RAAH const			*_hoops_RASCP = &_hoops_GASCP[left];
		_hoops_RAAH const			*_hoops_AASCP = &_hoops_GASCP[right + 1];
		int						hoffset;
		Int_Rectangle const &	_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

		_hoops_RGGA (_hoops_RASCP == _hoops_AASCP) {
			_hoops_RGGA (_hoops_RASCP == _hoops_AASCP || *_hoops_RASCP < z) ++_hoops_RASCP;
			if (_hoops_RASCP == _hoops_AASCP)
				break;
			hoffset = (_hoops_RASCP - _hoops_GASCP);
			start.x = (float)(hoffset + _hoops_ICSIR->offset.x); /* _hoops_SHPR _hoops_GC */

			_hoops_RGGA (_hoops_RASCP == _hoops_AASCP || *_hoops_RASCP >= z) ++_hoops_RASCP;
			end.x = (float)((_hoops_RASCP - _hoops_GASCP) - 1 + _hoops_ICSIR->offset.x); /* _hoops_SHPR _hoops_GC */

			if (start.x < (float)_hoops_GPHH.left)
				start.x = (float)_hoops_GPHH.left;

			if (end.x > (float)_hoops_GPHH.right)
				end.x = (float)_hoops_GPHH.right;

			if (start.y <= (float)_hoops_GPHH.top && end.y >= (float)_hoops_GPHH.bottom &&
				start.x <= end.x)
				if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_ASRAP))
					_hoops_PASCP (nr, &start, &end,
										  _hoops_ICSIR->depth_buffer,
										  hoffset, _hoops_ICSIR->_hoops_HIAI->height - 1 - bottom,
										  _hoops_ICSIR->_hoops_HASCP);
				else
					_hoops_PASCP (nr, &start, &end,
										  _hoops_ICSIR->_hoops_HIAI,
										  hoffset, _hoops_ICSIR->_hoops_HIAI->height - 1 - bottom,
										  _hoops_ICSIR->_hoops_IASCP);
		}

		end.y = ++start.y;
		++bottom;
	} _hoops_RGGA (++_hoops_CRSCP == _hoops_SRSCP ||
			 _hoops_GGPGR(nr));
}
#endif



local void _hoops_CASCP (
	Net_Rendition const &		nr) {
	_hoops_HCSIR alter *	_hoops_ICSIR;
	int							width, height;
	DC_Point					start, end;
	Net_Rendition				_hoops_RHICP = nr;
	_hoops_HHCR			_hoops_AHICP;

	if (nr->_hoops_SAIR->_hoops_ASSIR == null ||
		(_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR()) == null ||
		_hoops_ICSIR->_hoops_HIAI == null)
		return;

	if (BIT (_hoops_ICSIR->input._hoops_SASCP.update, _hoops_GPSCP)) {
		_hoops_ICSIR->_hoops_GHIAA = true;
		return;
	}

	_hoops_AHICP = _hoops_RHICP.Modify()->transform_rendition.Modify();
	HD_Set_Z_Buffering_Transform (_hoops_RHICP, false, false, _hoops_AHICP->_hoops_PCHH);
	_hoops_AHICP->flags &= ~_hoops_CSP;

	width  = _hoops_ICSIR->_hoops_HIAI->width;
	height = _hoops_ICSIR->_hoops_HIAI->height;

	if (width != 0 && height != 0) {
		int								hoffset, voffset;

		if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_ISRAP))
			return;

		if (_hoops_RHICP->_hoops_ASIR->_hoops_PSIR->_hoops_RHHHP != 0)
			_hoops_RHICP->_hoops_ASIR.Modify()->_hoops_PSIR.Modify()->_hoops_RHHHP = 0;

		_hoops_RHICP->current &= ~_hoops_RSSHP; /* _hoops_HIIPA */

		{
			Int_Rectangle const &	_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

			start.x = (float)_hoops_ICSIR->offset.x;
			end.x	= (float)(_hoops_ICSIR->offset.x + width	 - 1);
			start.y = (float)(_hoops_ICSIR->offset.y + height - 1);
			end.y	= (float)_hoops_ICSIR->offset.y;

			if (start.x < (float)_hoops_GPHH.left) {
				hoffset = _hoops_GPHH.left - (int)start.x;
				start.x = (float)_hoops_GPHH.left;
			}
			else
				hoffset = 0;

			if (start.y > (float)_hoops_GPHH.top) {
				voffset = (int)start.y - _hoops_GPHH.top;
				start.y = (float)_hoops_GPHH.top;
			}
			else
				voffset = 0;

			if (end.x > (float)_hoops_GPHH.right)
				end.x = (float)_hoops_GPHH.right;
			if (end.y < (float)_hoops_GPHH.bottom)
				end.y = (float)_hoops_GPHH.bottom;
		}

		if (_hoops_ICSIR->depth_buffer == null ||
			(_hoops_RHICP->_hoops_ASIR->window.pattern != FP_WINDOW_TRANSPARENT &&
				_hoops_RHICP->_hoops_ASIR->window.pattern != FP_WINDOW_TRANS_NO_ZCLEAR) &&
			_hoops_ICSIR->_hoops_RPSCP) {
			start.z = end.z = 0.0f;

			if (BIT (nr->_hoops_IRR->_hoops_GSSIR,
					 _hoops_ASRAP) &&
				_hoops_ICSIR->depth_buffer != null)
				_hoops_PASCP (_hoops_RHICP,
										  &start, &end,
										  _hoops_ICSIR->depth_buffer,
										  hoffset, voffset,
										  _hoops_ICSIR->_hoops_HASCP);
			else
				_hoops_PASCP (_hoops_RHICP,
										  &start, &end,
										  _hoops_ICSIR->_hoops_HIAI,
										  hoffset, voffset,
										  _hoops_ICSIR->_hoops_IASCP);
		}
#ifndef _hoops_GCSIR
		else {
			/*
			 * _hoops_APSCP _hoops_SCH _hoops_GGSR _hoops_PPSCP-_hoops_HPP-_hoops_PPSCP, _hoops_PACGR _hoops_CCA _hoops_IGHP
			 */
			_hoops_IRSCP (_hoops_RHICP, _hoops_GGGCR,
								   (int)start.x, (int)end.x, (int)end.y,(int)start.y);
		}
#endif

		_hoops_RHICP->current |= _hoops_RSSHP;
	}
}




/***********************************************************************
 ***********************************************************************
						   _hoops_HPSCP _hoops_IPSCP
 ***********************************************************************
 ***********************************************************************/

Begin_HOOPS_Namespace
	struct _hoops_CPSCP {
		_hoops_CPSCP alter *		next;
		Net_Rendition				nr;
		DC_Point					where;
		int							count;
		Karacter alter *			kstring;
		float						_hoops_RACSR;
		float						_hoops_GCHSA;
	};
End_HOOPS_Namespace;


local void _hoops_SPSCP (
	_hoops_HCSIR alter	*_hoops_ICSIR) {
	_hoops_CPSCP alter			*victim;

	_hoops_RGGA ((victim = _hoops_ICSIR->_hoops_GHSCP) == null) {
		victim->nr->release();
		FREE_ARRAY (victim->kstring, victim->count, Karacter);

		_hoops_ICSIR->_hoops_GHSCP = victim->next;

		FREE (victim, _hoops_CPSCP);
	}
}


local void _hoops_RHSCP (
	Net_Rendition const &		inr) {
	_hoops_HCSIR alter *	_hoops_ICSIR;
	_hoops_CPSCP alter *		text;

	if (inr->_hoops_SAIR->_hoops_ASSIR == null ||
		(_hoops_ICSIR = inr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR()) == null ||
		_hoops_ICSIR->_hoops_HIAI == null)
		return;

	/* (_hoops_RH _hoops_HIIC _hoops_HRGR _hoops_ICIC) */
	if ((text = _hoops_ICSIR->_hoops_GHSCP) != null) {
		if (!BIT(inr->_hoops_SRA->flags, _hoops_AASHP))
			(*inr->_hoops_SRA->_hoops_ACPGR->_hoops_CAAGR)(inr,
				inr->transform_rendition->_hoops_AGAA.left,
				inr->transform_rendition->_hoops_AGAA.right,
				inr->transform_rendition->_hoops_AGAA.bottom,
				inr->transform_rendition->_hoops_AGAA.top);

		do {
			Net_Rendition		nr = text->nr;
			// _hoops_IPCP "_hoops_SCII" _hoops_IIGR _hoops_RH _hoops_HCGR _hoops_HRGR _hoops_AIAH _hoops_AHSCP, _hoops_SRIPA _hoops_IIGR _hoops_PHSCP.

			((Font_Instance *)text->nr->_hoops_SISI->font)->_hoops_RACSR = text->_hoops_RACSR;
			((Font_Instance *)text->nr->_hoops_SISI->font)->_hoops_GCHSA = text->_hoops_GCHSA;

#ifndef _hoops_GCSIR
			/* _hoops_SAP _hoops_PSAP _hoops_AHCR _hoops_RHGPR. _hoops_HHSCP. */
			nr.Modify()->transform_rendition.Modify();
			HD_Set_Z_Buffering_Transform (nr, false, false, nr->transform_rendition->_hoops_PCHH);

			if (_hoops_ICSIR->depth_buffer != null &&
				BIT (nr->current, _hoops_RSSHP)) {
				Karacter const		*_hoops_IHSCP = text->kstring;
				int						count = text->count;
				float			_hoops_CRRAR;
				float			_hoops_CHSCP;
				DC_Point		where;

				_hoops_CRRAR = (float)nr->_hoops_SISI->font->_hoops_ISISR;
				_hoops_CHSCP = _hoops_CRRAR / 2.0f;

				where.x = text->where.x;
				where.y = text->where.y;
				where.z = text->where.z;

				while (count > 0) {
					float			dx;

					HD_Measure_Characters (nr, 1, _hoops_IHSCP, nr->_hoops_SISI->font->encoding, &dx);

					_hoops_RAICP (nr, &where, 1, _hoops_IHSCP);
					_hoops_IRSCP (inr, (_hoops_RAAH)where.z,
										   (int)where.x,
										   (int)(where.x + dx),
										   (int)(where.y - _hoops_CHSCP),
										   (int)(where.y + _hoops_CRRAR));
					where.x += dx;

					count--;
					_hoops_IHSCP++;
				}
			}
			else
#endif
				_hoops_RAICP (nr, &text->where, text->count, text->kstring);
		} _hoops_RGGA ((text = (_hoops_CPSCP alter *)text->next) == null);
	}
}


/*
 * _hoops_GSAH _hoops_RIIA _hoops_IIGR _hoops_SHSCP
 */
local void _hoops_GISCP (
	Net_Rendition const &		nr,
	DC_Point const *			where,
	int							count,
	Karacter const *			kstring) {
	_hoops_CPSCP alter *		text;
	_hoops_HCSIR alter	*	_hoops_ICSIR;

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	ZALLOC (text, _hoops_CPSCP);

	text->nr = nr;

	text->where.x = where->x;
	text->where.y = where->y;
	text->where.z = where->z + nr->transform_rendition->_hoops_SHIH *
					_hoops_ISSIR(nr->transform_rendition);
	text->count = count;

	ALLOC_ARRAY (text->kstring, count, Karacter);
	_hoops_AIGA(kstring, count, Karacter, text->kstring);

	text->_hoops_RACSR = text->nr->_hoops_SISI->font->_hoops_RACSR;
	text->_hoops_GCHSA = text->nr->_hoops_SISI->font->_hoops_GCHSA;

	/*
	 * _hoops_CARR _hoops_CRGR _hoops_PISI _hoops_HCGR _hoops_HIGR _hoops_HIS _hoops_SGS
	 *	   _hoops_HCGR->_hoops_CAS._hoops_SSH > _hoops_HCGR->_hoops_SPS->_hoops_CAS._hoops_SSH
	 * _hoops_SGPR _hoops_RISCP _hoops_AGGPR _hoops_GHIS.
	 */
	if (_hoops_ICSIR->_hoops_GHSCP == null ||
		where->z > _hoops_ICSIR->_hoops_GHSCP->where.z) {
		text->next = _hoops_ICSIR->_hoops_GHSCP; /* (_hoops_ICIC _hoops_HIIC) */
		_hoops_ICSIR->_hoops_GHSCP = text;
	}
	else {
		_hoops_CPSCP alter		*_hoops_HAPAR;

		_hoops_HAPAR = _hoops_ICSIR->_hoops_GHSCP; /* (_hoops_ICIC _hoops_HIIC) */
		_hoops_RGGA (_hoops_HAPAR->next == null || where->z >= _hoops_HAPAR->next->where.z)
			_hoops_HAPAR = _hoops_HAPAR->next;
		text->next = _hoops_HAPAR->next;
		_hoops_HAPAR->next = text;
	}
}



/***********************************************************************
 ***********************************************************************
						 _hoops_CGSRA/_hoops_AISCP
 ***********************************************************************
 ***********************************************************************/


GLOBAL_FUNCTION void HD_Std_Create_Frame_Buffer (
	Net_Rendition const &		nr,
	int							width,
	int							height,
	Image_Format				format,
	Image alter * alter	*		image,
	void alter * alter *		_hoops_PISCP) {
	UNREFERENCED (nr);

	HI_Create_Image (image,
					 null,
					 width, height,
					 format, 0,
					 _hoops_HISCP, null);
	HI_Validate_Inverted_Rasters (*image);
	*_hoops_PISCP = null;
}


GLOBAL_FUNCTION void HD_Std_Destroy_Frame_Buffer (
	Net_Rendition const &		nr,
	Image alter *				image,
	void alter *				_hoops_PISCP) {
	UNREFERENCED (nr);

	_hoops_HPRH (image);
	if (_hoops_PISCP != null) {
		_hoops_IISCP (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							"Driver specific frame buffer data was non-null",
							"even though the driver didn't create the buffer");
	}
}

GLOBAL_FUNCTION void HD_Std_Display_Frame_Buffer (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	Image const *				image,
	int							hoffset,
	int							voffset,
	void const *				_hoops_PISCP) {
	UNREFERENCED (_hoops_PISCP);

	_hoops_SSGCP (nr, start, end, hoffset,
					   image->format, image->row_bytes,
					   &image->rasters[voffset],
					   FP_SOLID, null, image);
}



GLOBAL_FUNCTION _hoops_HCSIR alter * HD_Init_Frame_Buffer_Info (
	Net_Rendition const &		inr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path) {
	Net_Rendition				nr = inr;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_SPAGR						_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
	_hoops_AHAGR *				_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, path, false);
	_hoops_HCSIR alter	*	_hoops_ICSIR = null;

	if (nr->_hoops_SAIR->_hoops_ASSIR == null)
		nr->_hoops_SAIR->_hoops_ASSIR = _hoops_CSC;
	else
		_hoops_CSC = nr->_hoops_SAIR->_hoops_ASSIR;

	if (_hoops_CSC != null)
		_hoops_ICSIR = _hoops_CSC->_hoops_PSSIR();

	if (_hoops_ICSIR == null) {
		POOL_ZALLOC (_hoops_ICSIR, _hoops_HCSIR, dc->memory_pool);

		if ((_hoops_ICSIR->next = dc->_hoops_CISCP) != null)
			_hoops_ICSIR->next->backlink = &_hoops_ICSIR->next;

		dc->_hoops_CISCP = _hoops_ICSIR;
		_hoops_ICSIR->backlink = &dc->_hoops_CISCP;

		if (_hoops_CSC == null) {
			_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, path);
			nr->_hoops_SAIR->_hoops_ASSIR = _hoops_CSC;
		}
		_hoops_CSC->_hoops_HSCGP (_hoops_ICSIR);
		if (_hoops_CSC->_hoops_APHGA == null)
			_hoops_CSC->_hoops_APHGA = nr;
		_hoops_ICSIR->_hoops_SISCP = _hoops_CSC;

		_hoops_ICSIR->_hoops_GCSCP = _hoops_CAHPA;

		_hoops_ICSIR->_hoops_PCIIP.left = _hoops_ICSIR->_hoops_PCIIP.bottom = _hoops_IICIA;
		_hoops_ICSIR->_hoops_PCIIP.right = _hoops_ICSIR->_hoops_PCIIP.top = -_hoops_IICIA;
		_hoops_ICSIR->_hoops_HCIIP.left = _hoops_ICSIR->_hoops_HCIIP.bottom = _hoops_IICIA;
		_hoops_ICSIR->_hoops_HCIIP.right = _hoops_ICSIR->_hoops_HCIIP.top = -_hoops_IICIA;

		_hoops_ICSIR->input._hoops_RCSCP = _hoops_ACSCP;
	}

	_hoops_ICSIR->_hoops_GHIAA = false;
	return _hoops_ICSIR;
}



GLOBAL_FUNCTION void HD_Free_Frame_Buffer_Info (
	Net_Rendition const &		nr,
	_hoops_HCSIR const *	_hoops_ICSIR) {

	if (_hoops_ICSIR != null) {
		if (_hoops_ICSIR->_hoops_HIAI != null)
			_hoops_PCSCP (nr, _hoops_ICSIR->_hoops_HIAI,
									  _hoops_ICSIR->_hoops_IASCP);
		if (_hoops_ICSIR->depth_buffer != null)
			_hoops_PCSCP (nr, _hoops_ICSIR->depth_buffer,
									  _hoops_ICSIR->_hoops_HASCP);
		if (_hoops_ICSIR->_hoops_HCSCP != null)
			_hoops_PCSCP (nr, _hoops_ICSIR->_hoops_HCSCP,
									  _hoops_ICSIR->_hoops_ICSCP);

		if (_hoops_ICSIR->_hoops_AIIIP[0] != null) {
			Display_Context const		*dc = nr->_hoops_SRA;

			(*dc->_hoops_ACPGR->_hoops_ISPGR) (nr, _hoops_ICSIR->_hoops_AIIIP[0], _hoops_ICSIR->_hoops_GCIIP[0]);

			if (_hoops_ICSIR->_hoops_AIIIP[1] != null)
				(*dc->_hoops_ACPGR->_hoops_ISPGR) (nr, _hoops_ICSIR->_hoops_AIIIP[1], _hoops_ICSIR->_hoops_GCIIP[1]);
		}

		if (_hoops_ICSIR->_hoops_RIIIP != null)
			_hoops_PCSCP (nr, _hoops_ICSIR->_hoops_RIIIP,
									  _hoops_ICSIR->_hoops_CCSCP);
		if (_hoops_ICSIR->_hoops_SCSCP != null)
			_hoops_PCSCP (nr, _hoops_ICSIR->_hoops_SCSCP,
									  _hoops_ICSIR->_hoops_GSSCP);

		_hoops_ICSIR->_hoops_SAIR.release();

		if (_hoops_ICSIR->_hoops_GHSCP != null)
			_hoops_SPSCP ((_hoops_HCSIR alter *)_hoops_ICSIR);

		_hoops_ICSIR->_hoops_RSSCP.release();

		_hoops_ICSIR->_hoops_SISCP->_hoops_HSCGP (null);

		if ((*_hoops_ICSIR->backlink = _hoops_ICSIR->next) != null)
			_hoops_ICSIR->next->backlink = _hoops_ICSIR->backlink;

		FREE (_hoops_ICSIR, _hoops_HCSIR);
	}
}



GLOBAL_FUNCTION bool HD_Setup_Frame_Buffer (
	Net_Rendition const &		nr) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
	Display_Context const *		dc = nr->_hoops_SRA;

	int							_hoops_ASCIP;
	int							_hoops_PSCIP;
	bool						_hoops_ASSCP = false;

	_hoops_HCSIR alter * _hoops_ICSIR = _hoops_SGRA->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ASCIP = _hoops_SGRA->_hoops_SCIH.right - _hoops_SGRA->_hoops_SCIH.left  + 1  +  2 * dc->_hoops_ARAIP;

	if (!BIT(nr->flags, _hoops_SISHP))
		_hoops_PSCIP = _hoops_SGRA->_hoops_SCIH.top - _hoops_SGRA->_hoops_SCIH.bottom + 1  +  2 * dc->_hoops_ARAIP;
	else {
		_hoops_PSCIP = _hoops_IHCR->_hoops_AGAA.top - _hoops_IHCR->_hoops_AGAA.bottom + 1  +  2 * dc->_hoops_ARAIP;
		// _hoops_ASSS _hoops_IRS _hoops_CSCIP _hoops_IS _hoops_RCPS _hoops_RHIR _hoops_GRP _hoops_RH _hoops_SCGR _hoops_SRHR _hoops_RPP _hoops_SCH _hoops_SRIPR _hoops_IS _hoops_SHH _hoops_SSCIP
		if (_hoops_ICSIR->_hoops_HIAI != null &&  _hoops_PSCIP < _hoops_ICSIR->_hoops_HIAI->height)
			_hoops_PSCIP = _hoops_ICSIR->_hoops_HIAI->height;
	}

	if (_hoops_ICSIR->_hoops_HIAI == null ||
		_hoops_ICSIR->_hoops_HIAI->format != _hoops_ICSIR->_hoops_GCSCP ||
		_hoops_ICSIR->_hoops_HIAI->width  != _hoops_ASCIP	||
		_hoops_ICSIR->_hoops_HIAI->height != _hoops_PSCIP ||

		_hoops_ICSIR->depth_buffer == null &&
		BIT (nr->_hoops_RCSHR, _hoops_RSSHP) ||
		_hoops_ICSIR->depth_buffer != null &&
		(_hoops_ICSIR->depth_buffer->width  != _hoops_ASCIP ||
		 _hoops_ICSIR->depth_buffer->height != _hoops_PSCIP) ||

		_hoops_ICSIR->_hoops_HCSCP == null &&
		_hoops_ICSIR->_hoops_PSSCP != _hoops_CAHPA ||
		_hoops_ICSIR->_hoops_HCSCP != null &&
		(_hoops_ICSIR->_hoops_HCSCP->width	 != _hoops_ASCIP ||
		 _hoops_ICSIR->_hoops_HCSCP->height != _hoops_PSCIP)) {
		/*
		 * _hoops_HSSCP _hoops_IGIR _hoops_HGAS
		 */
		Display_Context *		_hoops_AAHCP = (Display_Context alter *)nr->_hoops_SRA;

		_hoops_AAHCP->_hoops_CPGPR |= _hoops_RCGSA & ~_hoops_AASCA;

		if (_hoops_ICSIR->_hoops_HIAI != null) {
			_hoops_PCSCP (nr, _hoops_ICSIR->_hoops_HIAI,
									  _hoops_ICSIR->_hoops_IASCP);
			_hoops_ICSIR->_hoops_HIAI = null;
			_hoops_ICSIR->_hoops_IASCP = null;

			_hoops_ASSCP = true;
		}
		if (_hoops_ICSIR->_hoops_RIIIP != null) {
			_hoops_PCSCP (nr, _hoops_ICSIR->_hoops_RIIIP,
									  _hoops_ICSIR->_hoops_CCSCP);
			_hoops_ICSIR->_hoops_RIIIP = null;
			_hoops_ICSIR->_hoops_CCSCP = null;
		}

		if (_hoops_ICSIR->_hoops_GCSCP != _hoops_CAHPA) {
			if (!_hoops_ICSIR->_hoops_ISSCP) {
				_hoops_CSSCP (nr, _hoops_ASCIP, _hoops_PSCIP,
								 _hoops_ICSIR->_hoops_GCSCP,
								 &_hoops_ICSIR->_hoops_HIAI,
								 &_hoops_ICSIR->_hoops_IASCP);
			}
			else {
				HD_Std_Create_Frame_Buffer (nr, _hoops_ASCIP, _hoops_PSCIP,
								_hoops_ICSIR->_hoops_GCSCP,
								&_hoops_ICSIR->_hoops_HIAI,
								&_hoops_ICSIR->_hoops_IASCP);

				_hoops_ICSIR->_hoops_HIAI->flags |= _hoops_SHCC;
				HOOPS_WORLD->_hoops_ACPIR++;
			}
		}

		/*
		 * _hoops_HSSCP _hoops_PSCA _hoops_SSSCP _hoops_GGGSP _hoops_PAII _hoops_SRGR _hoops_CRGR _hoops_PCCP _hoops_APRS
		 * _hoops_RPPS, _hoops_HIS _hoops_RPP _hoops_IRS _hoops_RPPS _hoops_GPGH'_hoops_RA _hoops_CPIC _hoops_IS _hoops_SHH _hoops_CHCC *_hoops_CRGR* _hoops_RGR
		 * _hoops_HCHSR _hoops_SRHR, _hoops_HHSA _hoops_SPR.
		 */
		if (!BIT (nr->current, _hoops_RSSHP) &&
			BIT (nr->current, _hoops_CISHP) &&
			_hoops_ICSIR->_hoops_RSSCP == null &&
			!BIT (nr->_hoops_RCSHR, _hoops_PRHIP)) {
			_hoops_RGGSP (nr);
		}

#ifndef _hoops_GCSIR
		if (_hoops_ICSIR->depth_buffer != null) {
			_hoops_PCSCP (nr, _hoops_ICSIR->depth_buffer,
									  _hoops_ICSIR->_hoops_HASCP);
			_hoops_ICSIR->depth_buffer = null;
			_hoops_ICSIR->_hoops_HASCP = null;
		}
#endif
		if (_hoops_ICSIR->_hoops_SCSCP != null) {
			_hoops_PCSCP (nr, _hoops_ICSIR->_hoops_SCSCP,
									  _hoops_ICSIR->_hoops_GSSCP);
			_hoops_ICSIR->_hoops_SCSCP = null;
			_hoops_ICSIR->_hoops_GSSCP = null;
		}

#ifndef _hoops_GCSIR
		if (BIT (nr->_hoops_RCSHR, _hoops_RSSHP)) {
			_hoops_CSSCP (nr, _hoops_ASCIP, _hoops_PSCIP,
									 _hoops_AGGSP,
									 &_hoops_ICSIR->depth_buffer,
									 &_hoops_ICSIR->_hoops_HASCP);
			_hoops_ICSIR->_hoops_HRSCP = true;
		}
#endif

		if (_hoops_ICSIR->_hoops_HCSCP != null) {
			_hoops_PCSCP (nr, _hoops_ICSIR->_hoops_HCSCP,
									  _hoops_ICSIR->_hoops_ICSCP);
			_hoops_ICSIR->_hoops_HCSCP = null;
			_hoops_ICSIR->_hoops_ICSCP = null;
		}

		if (_hoops_ICSIR->_hoops_PSSCP != _hoops_CAHPA)
			_hoops_CSSCP (nr, _hoops_ASCIP, _hoops_PSCIP,
									 _hoops_PGGSP,
									 &_hoops_ICSIR->_hoops_HCSCP,
									 &_hoops_ICSIR->_hoops_ICSCP);

		_hoops_ICSIR->_hoops_PSPIP = false;
	}

	return _hoops_ASSCP;
}



/***********************************************************************
 ***********************************************************************
						   _hoops_HGGSP _hoops_IPSCP
 ***********************************************************************
 ***********************************************************************/

/*
 * _hoops_PS _hoops_SGH _hoops_RH _hoops_HAISR _hoops_IIGR _hoops_CCGRA _hoops_RH _hoops_IGGSP _hoops_ACPH
 * _hoops_CCA _hoops_RGR _hoops_PCPH, _hoops_PGAP _hoops_ARH _hoops_GH _hoops_ISCP _hoops_PSCA _hoops_PIIHR
 * _hoops_IS _hoops_RCPH _hoops_RH "_hoops_HPHR" _hoops_IGGSP.  _hoops_GPGP _hoops_RGR _hoops_PPRRR, _hoops_SR _hoops_PAH
 * _hoops_SHH _hoops_RCRR _hoops_SGS _hoops_SR _hoops_CCPP _hoops_PSCA _hoops_RGAR _hoops_RPP _hoops_SR _hoops_HS
 * _hoops_CPHP _hoops_IS _hoops_PGSA.
 */
local void _hoops_CGGSP (
	Net_Rendition const &		nr,
	Int_Rectangle const *		extent) {
	_hoops_HCSIR alter	*	_hoops_ICSIR;
	Int_Rectangle				_hoops_SGGSP;

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	if (_hoops_ICSIR->_hoops_RSSCP == null && !_hoops_ICSIR->_hoops_GRGSP) {	// _hoops_PRIA _hoops_IH _hoops_SPHR
		_hoops_ICSIR->_hoops_RSSCP = nr;
	}
	else {														// _hoops_PGSA _hoops_HA
		if (_hoops_ICSIR->_hoops_HIAI == null)
			HD_Setup_Frame_Buffer (nr);

		if (_hoops_ICSIR->_hoops_HRSCP && _hoops_ICSIR->depth_buffer != null)
			HD_Clear_Software_Z_Buffer (nr);

		if (extent->left - _hoops_ICSIR->offset.x < 0 ||
			extent->right - _hoops_ICSIR->offset.x >= _hoops_ICSIR->_hoops_HIAI->width ||
			extent->bottom - _hoops_ICSIR->offset.y < 0 ||
			extent->top - _hoops_ICSIR->offset.y >= _hoops_ICSIR->_hoops_HIAI->height) {

			_hoops_RSAI (extent, Int_Rectangle, &_hoops_SGGSP);

			if (extent->left - _hoops_ICSIR->offset.x < 0)
				_hoops_SGGSP.left = _hoops_ICSIR->offset.x;
			if (extent->right - _hoops_ICSIR->offset.x >= _hoops_ICSIR->_hoops_HIAI->width)
				_hoops_SGGSP.right = _hoops_ICSIR->_hoops_HIAI->width-1 + _hoops_ICSIR->offset.x;
			if (extent->bottom - _hoops_ICSIR->offset.y < 0)
				_hoops_SGGSP.bottom = _hoops_ICSIR->offset.y;
			if (extent->top - _hoops_ICSIR->offset.y >= _hoops_ICSIR->_hoops_HIAI->height)
				_hoops_SGGSP.top = _hoops_ICSIR->_hoops_HIAI->height-1 + _hoops_ICSIR->offset.y;

			extent = &_hoops_SGGSP;
		}

		// _hoops_IIS'_hoops_GRI _hoops_AA _hoops_SCH
		HD_Standard_Draw_Window (nr, extent);

		// _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_SCH, _hoops_PAR _hoops_HPGR _hoops_CHGC _hoops_ISCP _hoops_RRGSP _hoops_GGR _hoops_SCH
		_hoops_ICSIR->_hoops_RSSCP = null;

		// _hoops_SR'_hoops_ASAR _hoops_HPGR _hoops_RH _hoops_RPPS _hoops_PAPA, _hoops_HIS _hoops_SR _hoops_PAH _hoops_ARGSP _hoops_APRS _hoops_HCISR
		_hoops_ICSIR->_hoops_RPSCP = true;

		// _hoops_RCPGR _hoops_PGHH _hoops_CHR _hoops_HA _hoops_AIPH
		_hoops_ICSIR->_hoops_PSPIP = false;
	}
}





local void _hoops_PRGSP (
	_hoops_HCSIR const *	_hoops_ICSIR,
	Image const *				from,
	Image alter *				to,
	Int_Rectangle const *		rect) {

	if (rect == null) {
		int				height = from->height;
		int				row_bytes = from->row_bytes;

		if (from->_hoops_PHGH != null && to->_hoops_PHGH != null) {
			COPY_MEMORY (from->_hoops_PHGH, height*row_bytes, (void *)to->_hoops_PHGH);
		}
		else {
			void const * const *	src = from->rasters;
			void alter * const *	_hoops_HRGSP = (void **)to->rasters;

			do {
				COPY_MEMORY (*src++, row_bytes, *_hoops_HRGSP++);
			} while (--height > 0);
		}
	}
	else {
		int				height = rect->top - rect->bottom + 1;
		int				width = rect->right - rect->left + 1;
		int				_hoops_SHGGR = width * from->_hoops_GCPIR;

		void const * const *	src = from->_hoops_RCPIR;
		void alter * const *	_hoops_HRGSP = (void **)to->_hoops_RCPIR;
		int						_hoops_IRGSP = (rect->left - _hoops_ICSIR->offset.x) *
														from->_hoops_GCPIR;
		int						_hoops_CRGSP = rect->bottom - _hoops_ICSIR->offset.y;
		src += _hoops_CRGSP;
		_hoops_HRGSP += _hoops_CRGSP;
		do {
			COPY_MEMORY ((char *)*src++ + _hoops_IRGSP, _hoops_SHGGR,
							  (char *)*_hoops_HRGSP++ + _hoops_IRGSP);
		} while (--height > 0);
	}
}

local bool _hoops_SRGSP (_hoops_ACHR _hoops_RGP, Type type)
{
	switch (type) {
		case _hoops_CHIP:
		case _hoops_PIIP:
		case _hoops_HIIP:
		case _hoops_IIIP:
		case _hoops_RIIP:
		case _hoops_GIIP:
			return BIT (_hoops_RGP, T_LINES);

		case _hoops_CGCP:
		case _hoops_SGCP:
		case _hoops_RCIP:
		case _hoops_GRCP:
		case _hoops_RRCP:
			return ANYBIT (_hoops_RGP, T_ANY_POLYGON_EDGE | T_FACES);

		case _hoops_PCIP:
		case _hoops_PIRS:
			return BIT (_hoops_RGP, T_MARKERS);

		case _hoops_ICIP:
			return BIT (_hoops_RGP, T_ANY_LIGHTS);

		case _hoops_HGPGR:
			return false;

		case _hoops_ASIP:
		case _hoops_SCIP:
		case _hoops_GSIP:
		case _hoops_PRCP:
			return ANYBIT (_hoops_RGP, T_FACES | T_ANY_SHELL_EDGE | T_VERTICES);

		case _hoops_GGCP:
			return ANYBIT (_hoops_RGP, T_FACES | T_ANY_GRID_EDGE | T_VERTICES);

		case _hoops_AGCP:
			return BIT (_hoops_RGP, T_TEXT);

		case _hoops_HGCP:
			return BIT (_hoops_RGP, T_IMAGES);

		default:
			return true;
	}
}


GLOBAL_FUNCTION void HD_Draw_Sprites (
   	Display_Context alter *		dc,
	_hoops_HCSIR alter *	_hoops_ICSIR,
	bool						_hoops_GAGSP,
	bool						_hoops_RAGSP) {
	_hoops_HSIIP alter *		si = dc->_hoops_IHIIP[0];
	Int_Rectangle 				_hoops_GPHH;

	_hoops_RSAI(&si->nr->_hoops_SAIR->_hoops_SCIH, Int_Rectangle, &_hoops_GPHH);

	/* _hoops_ASAC _hoops_PGHC _hoops_CAGGR _hoops_ISPH & _hoops_HSPP _hoops_IRS _hoops_CASI _hoops_SPR */
	_hoops_ICSIR->_hoops_HCIIP.left = _hoops_ICSIR->_hoops_PCIIP.left;
	_hoops_ICSIR->_hoops_HCIIP.right = _hoops_ICSIR->_hoops_PCIIP.right;
	_hoops_ICSIR->_hoops_HCIIP.bottom = _hoops_ICSIR->_hoops_PCIIP.bottom;
	_hoops_ICSIR->_hoops_HCIIP.top = _hoops_ICSIR->_hoops_PCIIP.top;
	_hoops_ICSIR->_hoops_PCIIP.left = _hoops_ICSIR->_hoops_PCIIP.bottom = _hoops_IICIA;
	_hoops_ICSIR->_hoops_PCIIP.right = _hoops_ICSIR->_hoops_PCIIP.top = -_hoops_IICIA;

	dc->_hoops_CPGPR |= _hoops_ICHPA;	/* _hoops_IPSC _hoops_PIHA _hoops_SHR _hoops_SHH _hoops_CHCC */

	_hoops_AAGSP *	_hoops_PAGSP = dc->_hoops_SPA;
	dc->_hoops_SPA = dc->_hoops_ISAGR;

	_hoops_HAGSP (dc);

	do {
		Geometry const *			geometry = si->geometry;
		Net_Rendition				nr = si->nr;
		_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
		_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;

		if (_hoops_RAGSP && _hoops_IHCR->_hoops_RHPHP != _hoops_PHPHP) {
			_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

			_hoops_GGCC->_hoops_RHPHP = _hoops_PHPHP;	/* _hoops_SGH _hoops_RAAP _hoops_SRHR */
			_hoops_GGCC->_hoops_ACSRP = 0.0f;		/* _hoops_HIH _hoops_GA'_hoops_RA _hoops_SHI _hoops_HIRA */

			_hoops_GGCC->_hoops_AGAA.left	  = _hoops_SGRA->_hoops_PHRA.left;
			_hoops_GGCC->_hoops_AGAA.right  = _hoops_SGRA->_hoops_PHRA.right;
			_hoops_GGCC->_hoops_AGAA.bottom = _hoops_SGRA->_hoops_PHRA.bottom;
			_hoops_GGCC->_hoops_AGAA.top	  = _hoops_SGRA->_hoops_PHRA.top;
		}
		else if (_hoops_IHCR->_hoops_AGAA.left	  != _hoops_SGRA->_hoops_PHRA.left ||
				 _hoops_IHCR->_hoops_AGAA.right  != _hoops_SGRA->_hoops_PHRA.right ||
				 _hoops_IHCR->_hoops_AGAA.bottom != _hoops_SGRA->_hoops_PHRA.bottom ||
				 _hoops_IHCR->_hoops_AGAA.top	  != _hoops_SGRA->_hoops_PHRA.top) {
			_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

			_hoops_GGCC->_hoops_AGAA.left	  = _hoops_SGRA->_hoops_PHRA.left;
			_hoops_GGCC->_hoops_AGAA.right  = _hoops_SGRA->_hoops_PHRA.right;
			_hoops_GGCC->_hoops_AGAA.bottom = _hoops_SGRA->_hoops_PHRA.bottom;
			_hoops_GGCC->_hoops_AGAA.top	  = _hoops_SGRA->_hoops_PHRA.top;
		}

		if (1) {
			_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();
			//_hoops_IAGSP->_hoops_CAGSP = 0;
			//_hoops_IAGSP->_hoops_SAGSP = _hoops_GPGSP(_hoops_SCII, _hoops_CPSP->_hoops_RPGSP - 32);
			_hoops_GGCC->flags |= _hoops_CHHS|_hoops_CAHPP|_hoops_APGSP;
		}

		_hoops_APSRR(dc, "Sprite render geometry","", (int)(POINTER_SIZED_INT)geometry);

		_hoops_CRCP const *			_hoops_GRCIP = dc->_hoops_RRCIP;
		_hoops_HICS			_hoops_ARCIP = dc->path;
		dc->_hoops_RRCIP = si->segment;
		dc->path = si->path;

		if (si->_hoops_ISIIP != null) {
			_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

			/* _hoops_RCAR _hoops_CCGI _hoops_GACC _hoops_RGHH _hoops_PPGSP _hoops_HPPA _hoops_CPAP _hoops_GGR _hoops_HHH _hoops_ARAR */
			if (BIT (si->_hoops_ISIIP->_hoops_SRHA, DL_SHADOW_TRISTRIP))
				_hoops_GGCC->flags |= _hoops_ISH;

			_hoops_RACIP (nr, si->_hoops_ISIIP);
		}
		else if (ANYBIT (nr->_hoops_RCSHR, _hoops_HPGSP)) {
			_hoops_HGCGA (dc, "szb spriting", nr);
			HD_Vanillify_Actions(nr->_hoops_RCSHR, dc->_hoops_IPCI);
			HD_Standard_Render (nr, geometry, _hoops_RAPI, si->single);
			_hoops_HGSGA (dc, "szb spriting");
		}
		else
			(*dc->_hoops_IPCI->_hoops_CHCI) (nr, geometry, _hoops_RAPI, si->single);

		dc->_hoops_RRCIP = _hoops_GRCIP;
		dc->path = _hoops_ARCIP;
		nr = si->nr;

		if (_hoops_GAGSP) {
			_hoops_HHCR const &	_hoops_IPGSP = si->nr->transform_rendition;
			_hoops_RPRA const *			matrix = (_hoops_RPRA const *)_hoops_IPGSP->matrix->data.elements;
			Bounding					bounding;
			Point						point;
			Point						screen;
			int							i;

			/* _hoops_HGI _hoops_CPGSP _hoops_RAGC _hoops_PCCP _hoops_CARA _hoops_GC _hoops_IASC _hoops_AHCRR _hoops_PGAP
			 * _hoops_GRS _hoops_SHH _hoops_CHIAR _hoops_IS _hoops_SHPR _hoops_GC.	 _hoops_HAIA _hoops_IGCGA _hoops_CGH
			 * _hoops_RIIA _hoops_GRAS _hoops_SHPR _hoops_GC _hoops_HIAHR _hoops_PGAP _hoops_PAH _hoops_SHH _hoops_RPHGA _hoops_SSPP
			 * _hoops_RH _hoops_SPGSP.
			 */

			if (si->_hoops_ISIIP != null) {
				for (i=0; i<4; i++) {
					float	w, _hoops_APCP;

					w = _hoops_PHCP (matrix, si->_hoops_ISIIP->points[i]);

					if (w < nr->transform_rendition->_hoops_CHCR) {
						_hoops_GAGSP = false;
						break;
					}
					_hoops_APCP = 1.0f / w;
					screen.x = _hoops_HPRA (matrix, si->_hoops_ISIIP->points[i]) * _hoops_APCP;
					screen.y = _hoops_IPRA (matrix, si->_hoops_ISIIP->points[i]) * _hoops_APCP;

					if (screen.x <= _hoops_ICSIR->_hoops_PCIIP.left)
						_hoops_ICSIR->_hoops_PCIIP.left = (int)screen.x-1;
					if (screen.x >= _hoops_ICSIR->_hoops_PCIIP.right)
						_hoops_ICSIR->_hoops_PCIIP.right = (int)screen.x+1;
					if (screen.y <= _hoops_ICSIR->_hoops_PCIIP.bottom)
						_hoops_ICSIR->_hoops_PCIIP.bottom = (int)screen.y-1;
					if (screen.y >= _hoops_ICSIR->_hoops_PCIIP.top)
						_hoops_ICSIR->_hoops_PCIIP.top = (int)screen.y+1;
				}
			}
			else do if (!BIT (geometry->_hoops_RRHH, _hoops_HGAGR)) {
				if (geometry->type == _hoops_HGCP) {
					Image const *	image = (Image const *)geometry;
					int				_hoops_GHGSP = (image->width + 1) / 2;
					int				_hoops_RHGSP = (image->height + 1) / 2;
					float			_hoops_APCP;

					_hoops_APCP = 1.0f / _hoops_PHCP (matrix, image->_hoops_CSAI);
					screen.x = _hoops_HPRA (matrix, image->_hoops_CSAI) * _hoops_APCP;
					screen.y = _hoops_IPRA (matrix, image->_hoops_CSAI) * _hoops_APCP;

					if (screen.x-_hoops_GHGSP <= _hoops_ICSIR->_hoops_PCIIP.left)
						_hoops_ICSIR->_hoops_PCIIP.left = (int)screen.x-_hoops_GHGSP-1;
					if (screen.x+_hoops_GHGSP >= _hoops_ICSIR->_hoops_PCIIP.right)
						_hoops_ICSIR->_hoops_PCIIP.right = (int)screen.x+_hoops_GHGSP+1;
					if (screen.y-_hoops_RHGSP <= _hoops_ICSIR->_hoops_PCIIP.bottom)
						_hoops_ICSIR->_hoops_PCIIP.bottom = (int)screen.y-_hoops_RHGSP-1;
					if (screen.y+_hoops_RHGSP >= _hoops_ICSIR->_hoops_PCIIP.top)
						_hoops_ICSIR->_hoops_PCIIP.top = (int)screen.y+_hoops_RHGSP+1;
				}
#if 0
				else if (geometry->type == _hoops_AGCP) {
					/* _hoops_PAH _hoops_SR _hoops_SHH _hoops_AHGSP _hoops_ARI (_hoops_HGCR _hoops_HCGR _hoops_PHGSP)? */
				}
#endif
				else if (_hoops_SRGSP (nr->_hoops_RGP, geometry->type)) {
					Bounding				_hoops_HSIGA;

					if (HI_Figure_Geometry_Bounding (geometry, _hoops_HSIGA)) {
						if (!_hoops_HSIGA._hoops_HICAR()) {
							/* _hoops_HHGSP _hoops_HRGR _hoops_HCGR, _hoops_RRRH, _hoops_PGGS _hoops_IPSIA */
							if (ANYBIT (_hoops_HSIGA->flags, _hoops_HGCIR|_hoops_IGCIR|Bounding_TRANSFORM_DEPENDENT)) {
								_hoops_GAGSP = false;
								break;
							}
							else
								bounding.Merge (_hoops_HSIGA);
						}
					}
					else {
						_hoops_GAGSP = false;
						break;
					}
				}
				if (si->single)
					break;
			} while ((geometry = geometry->next) != null);

			if (_hoops_GAGSP && bounding != null) { /* _hoops_HGGC _hoops_RIRA? */

				int						_hoops_HHCAP = 0;

				/* _hoops_IRCH _hoops_HGSGR _hoops_IRS _hoops_RSCA _hoops_IH _hoops_SHPR-_hoops_GC _hoops_AIRC
				 * _hoops_HGPP _hoops_GAR _hoops_III _hoops_SGCR & _hoops_GPIA _hoops_IGIR
				 */

				_hoops_HHCAP = si->nr->_hoops_AHP->weight / 2;
				if (_hoops_HHCAP < si->nr->_hoops_RHP->weight / 2)
					_hoops_HHCAP = (int)si->nr->_hoops_RHP->weight / 2;
				if (_hoops_HHCAP < si->nr->_hoops_GSP->_hoops_RGRS)
					_hoops_HHCAP = (int)si->nr->_hoops_GSP->_hoops_RGRS;
				if (_hoops_HHCAP < si->nr->_hoops_GSP->ysize)
					_hoops_HHCAP = (int)si->nr->_hoops_GSP->ysize;
				_hoops_HHCAP += 2;

				/* _hoops_HA _hoops_SGS _hoops_SR _hoops_HS _hoops_IASC, _hoops_SICR _hoops_IS _hoops_CAGGR _hoops_ISPH */

				for (i=0; _hoops_GAGSP && i<8; ++i) {
					float	w;

					point.x = (i&1) ? bounding->cuboid.min.x : bounding->cuboid.max.x;
					point.y = (i&2) ? bounding->cuboid.min.y : bounding->cuboid.max.y;
					point.z = (i&4) ? bounding->cuboid.min.z : bounding->cuboid.max.z;

					screen.x = _hoops_HPRA (matrix, point);
					screen.y = _hoops_IPRA (matrix, point);
					if (_hoops_IHGSP (_hoops_IPGSP->_hoops_HGSC)) {
						if ((w = _hoops_PHCP (matrix, point)) > _hoops_IPGSP->_hoops_CHCR) {
							screen.x /= w;
							screen.y /= w;
						}
						else
							_hoops_GAGSP = false;
					}

					if (screen.x-_hoops_HHCAP <= _hoops_ICSIR->_hoops_PCIIP.left)
						_hoops_ICSIR->_hoops_PCIIP.left = (int)screen.x-_hoops_HHCAP;
					if (screen.x+_hoops_HHCAP >= _hoops_ICSIR->_hoops_PCIIP.right)
						_hoops_ICSIR->_hoops_PCIIP.right = (int)screen.x+_hoops_HHCAP;
					if (screen.y-_hoops_HHCAP <= _hoops_ICSIR->_hoops_PCIIP.bottom)
						_hoops_ICSIR->_hoops_PCIIP.bottom = (int)screen.y-_hoops_HHCAP;
					if (screen.y+_hoops_HHCAP >= _hoops_ICSIR->_hoops_PCIIP.top)
						_hoops_ICSIR->_hoops_PCIIP.top = (int)screen.y+_hoops_HHCAP;
				}
			}
		}
	} while ((si = si->next) != null);

	_hoops_CHGSP (dc);

	dc->_hoops_SPA = _hoops_PAGSP;

	if (_hoops_GAGSP) {
		/* _hoops_SHGSP _hoops_ACPP */
		_hoops_ICSIR->_hoops_PCIIP._hoops_PGPGP(_hoops_GPHH);
	}
	else {
		/* _hoops_SAHR _hoops_ARP _hoops_IS _hoops_IHIR */
		_hoops_ICSIR->_hoops_PCIIP = _hoops_GPHH;
	}
}

/***********************************************************************
 ***********************************************************************
							   _hoops_AHGHA _hoops_RIAHP
 ***********************************************************************
 ***********************************************************************/

struct _hoops_GIGSP : public _hoops_HIHCP {
	_hoops_HCSIR *		_hoops_ICSIR;
	Int_XY					offset;
	bool					_hoops_RIGSP;

	_hoops_GIGSP (_hoops_HCSIR * f, int x, int y, bool zc)
		: _hoops_ICSIR (f), _hoops_RIGSP (zc) {
		offset.x = x;	offset.y = y;
	}

	bool _hoops_SIHCP (Net_Rendition alter & nr, bool _hoops_PPHPP) alter {
		UNREFERENCED (nr);
		if (!_hoops_PPHPP) {
			_hoops_ICSIR->offset = offset;
			_hoops_ICSIR->_hoops_HRSCP = _hoops_RIGSP;
			/* _hoops_IRHH _hoops_RCRR _hoops_IS _hoops_IGRC _hoops_CISA _hoops_GGR _hoops_RH _hoops_RPPS */
			if (_hoops_ICSIR->_hoops_RSSCP)
				_hoops_RGGSP(_hoops_ICSIR->_hoops_RSSCP);
		}
		return true;
	}
};

struct _hoops_AIGSP : public _hoops_HIHCP {
	_hoops_HCSIR *		_hoops_ICSIR;
	bool					_hoops_PIGSP;

	_hoops_AIGSP (_hoops_HCSIR * f, bool b) : _hoops_ICSIR (f), _hoops_PIGSP (b) {}

	bool _hoops_SIHCP (Net_Rendition alter & nr, bool _hoops_PPHPP) alter;
};
bool _hoops_AIGSP::_hoops_SIHCP (Net_Rendition alter & nr, bool _hoops_PPHPP) alter {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_HSPPP *		_hoops_HIGSP = null;

	if (_hoops_PPHPP)
		return true;

	if (dc->_hoops_HRHPP[_hoops_IRHPP].list == null) {
		dc->_hoops_HRHPP[_hoops_IRHPP].list = dc->_hoops_HRHPP[_hoops_RAHPP].list;
		if (dc->_hoops_HRHPP[_hoops_RAHPP]._hoops_ASRGR == &dc->_hoops_HRHPP[_hoops_RAHPP].list)
			dc->_hoops_HRHPP[_hoops_IRHPP]._hoops_ASRGR = &dc->_hoops_HRHPP[_hoops_IRHPP].list;
		else
			dc->_hoops_HRHPP[_hoops_IRHPP]._hoops_ASRGR = dc->_hoops_HRHPP[_hoops_RAHPP]._hoops_ASRGR;

		dc->_hoops_HRHPP[_hoops_RAHPP].list = null;
		dc->_hoops_HRHPP[_hoops_RAHPP]._hoops_ASRGR = &dc->_hoops_HRHPP[_hoops_RAHPP].list;
	}

	while (dc->_hoops_HRHPP[_hoops_IRHPP].list == null &&
		dc->_hoops_AGHPP != null &&
		dc->_hoops_AGHPP->Count() > 0) {

			_hoops_RGHPP alter *	_hoops_SGCCA;
			int							_hoops_IGIC;

			dc->_hoops_AGHPP->Pop(&_hoops_SGCCA, &_hoops_IGIC);
			dc->_hoops_HGHPP->RemoveItem(_hoops_IGIC);

			if (_hoops_SGCCA->list != null) {
				*dc->_hoops_HRHPP[_hoops_IRHPP]._hoops_ASRGR = _hoops_SGCCA->list;

				if (_hoops_SGCCA->_hoops_ASRGR == &_hoops_SGCCA->list)
					dc->_hoops_HRHPP[_hoops_IRHPP]._hoops_ASRGR = &dc->_hoops_HRHPP[_hoops_IRHPP].list;
				else
					dc->_hoops_HRHPP[_hoops_IRHPP]._hoops_ASRGR = _hoops_SGCCA->_hoops_ASRGR;
			}

			FREE (_hoops_SGCCA, _hoops_RGHPP);
	}

	// _hoops_PIIA _hoops_HIGR _hoops_HCIAA -- _hoops_SRS _hoops_GPP _hoops_GIGR _hoops_HRGR _hoops_CGHI _hoops_SR _hoops_HHGC _hoops_IS _hoops_AISI
	if (dc->_hoops_HRHPP[_hoops_IRHPP].list != null) {
		_hoops_HSPPP *		_hoops_IIGSP = dc->_hoops_HRHPP[_hoops_IRHPP].list;

		dc->_hoops_HRHPP[_hoops_IRHPP].list = null;
		dc->_hoops_HRHPP[_hoops_IRHPP]._hoops_ASRGR = &dc->_hoops_HRHPP[_hoops_IRHPP].list;

		while (_hoops_IIGSP != null) {
			_hoops_HSPPP alter *	_hoops_PASIP = _hoops_IIGSP;

			_hoops_IIGSP = _hoops_PASIP->next;

			if (ANYBIT (_hoops_PASIP->_hoops_APHGA->_hoops_RCSHR, _hoops_RSSHP|_hoops_CISHP)) {
				_hoops_PASIP->next = _hoops_HIGSP;
				_hoops_HIGSP = _hoops_PASIP;
			}
			else {	// _hoops_HAR _hoops_SPR _hoops_SR _hoops_HHGC, _hoops_RSRHR _hoops_SCH _hoops_ISSC
				*dc->_hoops_HRHPP[_hoops_IRHPP]._hoops_ASRGR = _hoops_PASIP;
				_hoops_PASIP->next = null;
				dc->_hoops_HRHPP[_hoops_IRHPP]._hoops_ASRGR = &_hoops_PASIP->next;
			}
		}
	}

	if (_hoops_HIGSP != null) {
		while (_hoops_HIGSP != null) {
			_hoops_HSPPP alter *	_hoops_PASIP = _hoops_HIGSP;

			_hoops_HIGSP = _hoops_PASIP->next;

			/* _hoops_IRHH _hoops_PIP _hoops_SGS _hoops_SR _hoops_CHR _hoops_HGGC _hoops_ARP _hoops_GH _hoops_IH _hoops_CIGSP, _hoops_PPR _hoops_PA _hoops_SHS, _hoops_HII _hoops_ARRS */
			Net_Rendition				_hoops_SSGS = _hoops_PASIP->_hoops_APHGA;

			_hoops_SSGS.Modify();

			_hoops_SSGS->_hoops_RCSHR |= nr->current;
			_hoops_SSGS->current = nr->current;
			HD_Reset_Tree_State (_hoops_SSGS);

			/* _hoops_PSP _hoops_SIGSP _hoops_HII _hoops_SHPP _hoops_SSH _hoops_IS _hoops_ACIPR _hoops_SSH */
			if (ANYBIT(_hoops_SSGS->current, _hoops_CISHP|_hoops_RSSHP))
				_hoops_SSGS->_hoops_RCSHR &= ~_hoops_GSSHP;

			dc->_hoops_CPGPR = _hoops_PASIP->_hoops_CPGPR;
			dc->Push_Tree (_hoops_SSGS, _hoops_PASIP->segment, _hoops_PASIP->path);

			_hoops_PASIP->_hoops_APHGA.release();
			_hoops_PASIP->path.release();
			FREE (_hoops_PASIP, _hoops_HSPPP);
		}

		return false;	// _hoops_GA'_hoops_RA _hoops_APRI, _hoops_RCRPA _hoops_RAS _hoops_AGAP _hoops_SCSHR _hoops_GCGSP
	}

	// _hoops_HASIR _hoops_GII _hoops_ACPH _hoops_PIRRR _hoops_SGS _hoops_GGHP _hoops_RAAP _hoops_GPP _hoops_SCIA _hoops_IIGR _hoops_HIPIP
	while (dc->_hoops_IPCI->prev != null &&
			ANYBIT (dc->_hoops_IPCI->prev->mode, _hoops_CISHP|_hoops_RSSHP))
		_hoops_HGSGA (dc, null);

	/*
	 * _hoops_GRH _hoops_AGIR -- _hoops_AA _hoops_SR _hoops_HS _hoops_CIPH _hoops_RAAP _hoops_HII _hoops_ICCGR _hoops_CCSHP _hoops_AARAR _hoops_SGS
	 * _hoops_CSAP _hoops_HAR _hoops_CHHHP _hoops_HPGR _hoops_SGS _hoops_GHIR?	_hoops_RPP _hoops_HIS, _hoops_SR _hoops_PIHA _hoops_HS _hoops_IHSP, _hoops_PPR
	 * _hoops_CGH _hoops_AIRI _hoops_SCH _hoops_CGPR _hoops_SR _hoops_CHR _hoops_CPHR _hoops_CCA _hoops_RGR _hoops_RPPS
	 */
	if (dc->_hoops_HASS[dc->_hoops_IASS] != null || dc->_hoops_GASIP != null) {
		HD_Handle_FBI_Pending_Window (nr);

		/* _hoops_GIGGA _hoops_SSAI*/
		if (dc->_hoops_GASIP) {
			_hoops_RIGGA(nr, dc->_hoops_GASIP->used,
				dc->_hoops_GASIP->pts, dc->_hoops_GASIP->colors, 0);

			FREE_ARRAY(dc->_hoops_GASIP->pts, dc->_hoops_GASIP->allocated, DC_Point);
			FREE_ARRAY(dc->_hoops_GASIP->colors, dc->_hoops_GASIP->allocated, RGBAS32);
			FREE(dc->_hoops_GASIP, DC_Polydot_Batch);
			dc->_hoops_GASIP = 0;
		}

		if (dc->_hoops_HASS[dc->_hoops_IASS] != null)
			HD_See_Whats_Hidden (nr);
	}

	if (dc->_hoops_RPSS[dc->_hoops_IASS] != null) {
		HD_Draw_Deferred_3D_Geometry (dc->_hoops_RPSS[dc->_hoops_IASS], true);
		HD_Free_Deferred_3D_Geometry (dc->_hoops_RPSS[dc->_hoops_IASS]);
		dc->_hoops_RPSS[dc->_hoops_IASS] = null;
	}

	/*
	 * _hoops_CHSR _hoops_HPIH _hoops_GRH _hoops_AGIR -- _hoops_AA _hoops_SR _hoops_HS _hoops_GII _hoops_IPSC?
	 */
#ifndef _hoops_GCSIR
	if (_hoops_PIGSP) {
		// _hoops_IAGIP _hoops_HPGP _hoops_RCGSP?  _hoops_ACGSP, _hoops_PSP...
		if (dc->_hoops_IHIIP[0] != null) {
			HD_Draw_Sprites (dc, _hoops_ICSIR, false, false);
			_hoops_ICSIR->_hoops_SCIIP = true;
			_hoops_APSRR(dc, "SZB 1 drawn_spriting = true","", (int)(POINTER_SIZED_INT)_hoops_ICSIR);
		}
	}
	else if (dc->_hoops_APHHP == null) {
		HD_Alternate_Hidden_Root (dc, _hoops_HHIIP);

		if (dc->_hoops_IHIIP[0] != null ||
			dc->_hoops_HASS[dc->_hoops_IASS] != null) {
			if (_hoops_ICSIR->_hoops_RSSCP != null) {
				if (_hoops_ICSIR->_hoops_PCGSP || _hoops_ICSIR->_hoops_HIAI == null)
					HD_Draw_Window (_hoops_ICSIR->_hoops_RSSCP,
									 &_hoops_ICSIR->_hoops_RSSCP->_hoops_SAIR->_hoops_PHRA);
				_hoops_ICSIR->_hoops_PCGSP = false;

				/* _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_SCH, _hoops_PAR _hoops_HPGR _hoops_CHGC _hoops_ISCP _hoops_RRGSP _hoops_GGR _hoops_SCH */
				_hoops_ICSIR->_hoops_RSSCP = null;
			}

			if (_hoops_ICSIR->_hoops_PSPIP && !BIT (dc->_hoops_CPGPR, _hoops_GIPGP)) {
				/* _hoops_IPS _hoops_HII _hoops_RCPGR */
				Int_Rectangle const *		_hoops_RCIIP;

				if (dc->options._hoops_SRRRR &&
					dc->_hoops_PGCC._hoops_CHHSR == _hoops_RCPGA) {
					/* _hoops_HASC _hoops_CCAH _hoops_CRGR _hoops_RHGS _hoops_PPR _hoops_SGH _hoops_SGS _hoops_SPR (_hoops_CR _hoops_SR _hoops_PPPPR'_hoops_RA _hoops_SGH _hoops_SCH _hoops_GICS) */
					if (_hoops_ICSIR->_hoops_PCIIP.left < _hoops_ICSIR->_hoops_HCIIP.left)
						_hoops_ICSIR->_hoops_HCIIP.left = _hoops_ICSIR->_hoops_PCIIP.left;
					if (_hoops_ICSIR->_hoops_PCIIP.right > _hoops_ICSIR->_hoops_HCIIP.right)
						_hoops_ICSIR->_hoops_HCIIP.right = _hoops_ICSIR->_hoops_PCIIP.right;
					if (_hoops_ICSIR->_hoops_PCIIP.bottom < _hoops_ICSIR->_hoops_HCIIP.bottom)
						_hoops_ICSIR->_hoops_HCIIP.bottom = _hoops_ICSIR->_hoops_PCIIP.bottom;
					if (_hoops_ICSIR->_hoops_PCIIP.top > _hoops_ICSIR->_hoops_HCIIP.top)
						_hoops_ICSIR->_hoops_HCIIP.top = _hoops_ICSIR->_hoops_PCIIP.top;

					_hoops_RCIIP = &_hoops_ICSIR->_hoops_HCIIP;
				}
				else
					_hoops_RCIIP = &_hoops_ICSIR->_hoops_PCIIP;

				if (_hoops_RCIIP->left <= _hoops_RCIIP->right &&
					_hoops_RCIIP->bottom <= _hoops_RCIIP->top) {
					_hoops_PRGSP (_hoops_ICSIR, _hoops_ICSIR->_hoops_RIIIP, _hoops_ICSIR->_hoops_HIAI, _hoops_RCIIP);
					if (_hoops_ICSIR->_hoops_SCSCP != null)
						_hoops_PRGSP (_hoops_ICSIR, _hoops_ICSIR->_hoops_SCSCP, _hoops_ICSIR->depth_buffer, _hoops_RCIIP);
				}
			}
			else {
				int 		width  = _hoops_ICSIR->_hoops_HIAI->width;
				int 		height = _hoops_ICSIR->_hoops_HIAI->height;

				if (_hoops_ICSIR->_hoops_RIIIP == null)
					_hoops_CSSCP (nr, width, height,
											 _hoops_ICSIR->_hoops_GCSCP,
											 &_hoops_ICSIR->_hoops_RIIIP,
											 &_hoops_ICSIR->_hoops_CCSCP);
				_hoops_PRGSP (_hoops_ICSIR, _hoops_ICSIR->_hoops_HIAI, _hoops_ICSIR->_hoops_RIIIP, null);

				if (BIT (nr->current, _hoops_RSSHP)) {
					if (_hoops_ICSIR->_hoops_SCSCP == null)
						_hoops_CSSCP (nr, width, height,
												 _hoops_AGGSP,
												 &_hoops_ICSIR->_hoops_SCSCP,
												 &_hoops_ICSIR->_hoops_GSSCP);
					_hoops_PRGSP (_hoops_ICSIR, _hoops_ICSIR->depth_buffer, _hoops_ICSIR->_hoops_SCSCP, null);
				}
				_hoops_ICSIR->_hoops_PSPIP = true;
			}

			if (dc->_hoops_IHIIP[0]) {
				HD_Draw_Sprites (dc, _hoops_ICSIR, true, false);
				_hoops_ICSIR->_hoops_SCIIP = true;
				_hoops_APSRR(dc, "SZB 2 drawn_spriting = true","", (int)(POINTER_SIZED_INT)_hoops_ICSIR);
			}

			dc->flags &= ~_hoops_CHIIP;

			if (dc->_hoops_HASS[dc->_hoops_IASS]) {
				_hoops_ICSIR->_hoops_PCIIP.left   = nr->_hoops_SAIR->_hoops_PHRA.left;
				_hoops_ICSIR->_hoops_PCIIP.right  = nr->_hoops_SAIR->_hoops_PHRA.right;
				_hoops_ICSIR->_hoops_PCIIP.bottom = nr->_hoops_SAIR->_hoops_PHRA.bottom;
				_hoops_ICSIR->_hoops_PCIIP.top    = nr->_hoops_SAIR->_hoops_PHRA.top;

				// _hoops_ASIGA _hoops_RGR _hoops_GGRIP _hoops_APSH _hoops_PISC
				nr->current |= _hoops_AHIHP;
				nr->_hoops_RCSHR |= _hoops_AHIHP;

				HD_See_Whats_Hidden (nr);

				if (dc->_hoops_AGGIP) {
					HD_Alternate_Hidden_Root (dc, _hoops_GGCIP);
					HD_See_Whats_Hidden (nr);
				}

				nr->current &= ~_hoops_AHIHP;
				nr->_hoops_RCSHR &= ~_hoops_AHIHP;
			}
		}
		else if (BIT (dc->_hoops_CPGPR, _hoops_IHPGP) &&
				 _hoops_ICSIR->_hoops_PSPIP) {
			/* _hoops_IRS _hoops_SGHIP _hoops_SGS _hoops_HCGSP'_hoops_SAAAR _hoops_GHGA _hoops_RRI _hoops_IAGIP -- _hoops_IPS _hoops_HII _hoops_RCPGR */
			_hoops_PRGSP (_hoops_ICSIR, _hoops_ICSIR->_hoops_RIIIP, _hoops_ICSIR->_hoops_HIAI, null);
			if (_hoops_ICSIR->_hoops_SCSCP != null)
				_hoops_PRGSP (_hoops_ICSIR, _hoops_ICSIR->_hoops_SCSCP, _hoops_ICSIR->depth_buffer, null);

			dc->flags &= ~_hoops_CHIIP;
		}
		else {
			/* _hoops_CGH _hoops_ICGSP _hoops_GPP _hoops_HCPCA _hoops_RH _hoops_PPGS */
			if (_hoops_ICSIR->_hoops_PSPIP)
				_hoops_ICSIR->_hoops_PSPIP = false;
			else {
				if (_hoops_ICSIR->_hoops_RIIIP != null) {
					_hoops_PCSCP (nr, _hoops_ICSIR->_hoops_RIIIP,
											  _hoops_ICSIR->_hoops_CCSCP);
					_hoops_ICSIR->_hoops_RIIIP = null;
					_hoops_ICSIR->_hoops_CCSCP = null;
				}
				if (_hoops_ICSIR->_hoops_SCSCP != null) {
					_hoops_PCSCP (nr, _hoops_ICSIR->_hoops_SCSCP,
											  _hoops_ICSIR->_hoops_GSSCP);
					_hoops_ICSIR->_hoops_SCSCP = null;
					_hoops_ICSIR->_hoops_GSSCP = null;
				}
			}
		}

		HD_Alternate_Hidden_Root (dc, _hoops_HHIIP);
	}
#endif

	if (dc->_hoops_APHHP == null) {
		/* _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_GHGA _hoops_IRS _hoops_GHSHA _hoops_HPRC _hoops_ISPR.  _hoops_PHIH
		 * _hoops_RH _hoops_PGSI _hoops_RH _hoops_RHPP _hoops_SIAS _hoops_RRP _hoops_IS _hoops_CCGSP _hoops_RH _hoops_SCGSP _hoops_ACPP */
		_hoops_HGSGA (dc, "szb");

		if (_hoops_ICSIR->_hoops_RSSCP != null) {
			if (_hoops_ICSIR->_hoops_PCGSP || _hoops_ICSIR->_hoops_HIAI == null) {
				if (nr->_hoops_SRA->_hoops_GHRI->action == HD_Image_Driver &&
					_hoops_ICSIR->_hoops_HIAI == null)
						HD_Setup_Frame_Buffer (nr);

				HD_Draw_Window (_hoops_ICSIR->_hoops_RSSCP,
								 &_hoops_ICSIR->_hoops_RSSCP->_hoops_SAIR->_hoops_PHRA);
			}
			_hoops_ICSIR->_hoops_PCGSP = false;

			/* _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_SCH, _hoops_PAR _hoops_HPGR _hoops_CHGC _hoops_ISCP _hoops_RRGSP _hoops_GGR _hoops_SCH */
			_hoops_ICSIR->_hoops_RSSCP = null;
		}
		else if (_hoops_ICSIR->_hoops_GHIAA) {
			_hoops_CASCP (nr);
			_hoops_RHSCP (nr);

			if (_hoops_PIGSP)
				_hoops_SPSCP (_hoops_ICSIR);
		}
	}

	return true;
}


GLOBAL_FUNCTION void HD_Prepare_Soft_Z_Buffered_Tree (
	Net_Rendition alter &		nr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path) {
#ifdef DISABLE_RASTERIZER
	return;
#else
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
	_hoops_HCSIR alter *	_hoops_ICSIR;
	_hoops_APARR				_hoops_RRCI;
	//_hoops_CICC						_hoops_GSGSP;
	_hoops_HHCR			_hoops_IHCR;
	bool						_hoops_RSGSP;
	bool						_hoops_ASGSP;

	nr.Modify();

	if (BIT (nr->_hoops_RCSHR, _hoops_CRSI) && dc->_hoops_SHPGR == QMoves_XOR) {
		/* _hoops_IPIHR _hoops_AHCA _hoops_SHPP _hoops_SSH _hoops_SRHR */
		nr->_hoops_RCSHR &= ~(_hoops_RSSHP|_hoops_CISHP);
		return;
	}


	if (dc->options._hoops_RAHHP)
		_hoops_PHPGR (HEC_DRIVER, HES_FORCEBW_WITH_SOFTWARE_Z_BUFFER,
					 "Using force black and white with the software frame or Z buffer",
					 "is not recommended since the output is image based");


#ifndef _hoops_GCSIR
	_hoops_RSGSP = BIT (nr->_hoops_RCSHR, _hoops_RSSHP);
#else
	_hoops_RSGSP = false;
#endif

#ifndef _hoops_GCSIR
	if (_hoops_RSGSP && BIT (nr->_hoops_RCSHR, _hoops_GAHPP)) {
		/* _hoops_IPIHR _hoops_AHCA _hoops_CCSHP! */
		nr->_hoops_RCSHR &= ~(_hoops_CSGGR|_hoops_RSSHP);
		return;
	}
	else
#endif
#if 0	/* _hoops_RGR _hoops_CHCRA _hoops_SSCP _hoops_HHGS _hoops_CCA _hoops_IAGIP _hoops_SGHC _hoops_CAPP */
	if (!ANYBIT (dc->_hoops_CPGPR, _hoops_HPPGP|_hoops_IHPGP)) {
		/* _hoops_ISAP'_hoops_GRI _hoops_IGRC _hoops_CPIC _hoops_IS _hoops_SHH _hoops_CHCC, _hoops_HIS _hoops_SAHR _hoops_SPIC _hoops_GPP _hoops_ISHP */
		nr->current |= (_hoops_CSGGR|
						_hoops_RSSHP|
						_hoops_CISHP) & nr->_hoops_RCSHR;
		nr->_hoops_RCSHR &= ~_hoops_GSSHP;
		return;
	}
	else
#endif
	if (BIT (nr->current, _hoops_CRSI)) {
		/* _hoops_SR _hoops_GGHP _hoops_ICCGR _hoops_CCSHP _hoops_RGAR! */
		nr->_hoops_RCSHR &= ~(_hoops_RSSHP|_hoops_CISHP);
		/* (_hoops_RCAPR._hoops_PSGSP _hoops_HRGR _hoops_HGGC _hoops_GPP) */
		return;
	}


	if (_hoops_SRCP != null) {
		_hoops_ICSIR = HD_Init_Frame_Buffer_Info (nr, _hoops_SRCP, dc->_hoops_AHSI->path);
		_hoops_ICSIR->_hoops_HSGSP = HOOPS_WORLD->_hoops_GPPI;

		/* _hoops_ARP _hoops_IS _hoops_AHC + _hoops_ISGSP */
		_hoops_ICSIR->offset.x = _hoops_SGRA->_hoops_SCIH.left - dc->_hoops_ARAIP;
		_hoops_ICSIR->offset.y = _hoops_SGRA->_hoops_SCIH.bottom - dc->_hoops_ARAIP;

		_hoops_ICSIR->_hoops_PCGSP = BIT (nr->_hoops_RCSHR, _hoops_PRHIP);
		if (_hoops_ICSIR->_hoops_HIAI == null &&
			ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|_hoops_GISIR)) {
			_hoops_ICSIR->_hoops_HRSCP = true;
			if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GISIR) ||
				!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_RCHGP)) {
				nr->_hoops_RCSHR |= _hoops_PRHIP;
				_hoops_ICSIR->_hoops_RSSCP = null;
				dc->_hoops_CPGPR |= _hoops_RCGSA & ~_hoops_AASCA;
			}
		}
		else if (BIT (_hoops_SGRA->_hoops_ASIHP, _hoops_RCARP) &&
				 BIT (_hoops_SRCP->_hoops_PHSI, _hoops_RCHGP) &&
				 _hoops_ICSIR->depth_buffer != null) {
			HD_Clear_Software_Z_Buffer (nr);
		}

		if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR &&
			dc->_hoops_PGCC._hoops_AAPSR <= 256 &&
			nr->_hoops_ASIR->buffer._hoops_GHAAP == _hoops_RHAAP &&
			(_hoops_SRCP->_hoops_IGCCA == 0 && _hoops_SRCP->_hoops_SHGSA() == 0 ||
			 nr->_hoops_CPP->_hoops_PRH.style == _hoops_AIII) &&
			!BIT (nr->current|nr->_hoops_RCSHR, _hoops_AHIHP) &&
			!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_RCHGP)) {
			_hoops_ICSIR->_hoops_GCSCP = Image_MAPPED_8;
			_hoops_ICSIR->_hoops_ISSCP = false;
		}
		else if ((_hoops_SRCP->_hoops_IGCCA == 0 && _hoops_SRCP->_hoops_SHGSA() == 0 ||
				  nr->_hoops_CPP->_hoops_PRH.style == _hoops_AIII) &&
				 dc->_hoops_PGCC._hoops_PIHSR != _hoops_SIHSR &&
				!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_RCHGP)) {
			_hoops_ICSIR->_hoops_GCSCP = _hoops_CSGSP;
			_hoops_ICSIR->_hoops_ISSCP = false;
		}
		else {
			_hoops_ICSIR->_hoops_GCSCP = _hoops_CSGSP;
			_hoops_ICSIR->_hoops_ISSCP = true;
		}

		_hoops_ICSIR->_hoops_RPSCP = ANYBIT (_hoops_SRCP->_hoops_PHSI,
										   _hoops_SHSIR|_hoops_GISIR) ||
								   !_hoops_RSGSP;
	}
	else
		_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ASGSP = nr->_hoops_CPP->_hoops_PRH.style != _hoops_AIII &&
						 (BIT (nr->current|nr->_hoops_RCSHR, _hoops_AHIHP) ||
						  _hoops_SRCP != null && (_hoops_SRCP->_hoops_IGCCA > 0 || _hoops_SRCP->_hoops_SHGSA() > 0));

#ifndef _hoops_GCSIR
	if (_hoops_RSGSP) {
		_hoops_IHCR = nr->transform_rendition.Modify();
		HD_Set_Z_Buffering_Transform (nr, true,
									  true, (float)_hoops_HSCHA);
		_hoops_IHCR->flags &= ~(_hoops_PRIR|_hoops_RCRIP);

		if (_hoops_SRCP != null && (dc->_hoops_HRHPP[_hoops_SRHPP].list == null || dc->_hoops_HRHPP[_hoops_SRHPP].list->_hoops_CPCR == null)) {
			if (BIT (dc->_hoops_CPGPR, _hoops_ICHPA) ||

				/* (_hoops_RPP _hoops_SCH _hoops_ASSP'_hoops_RA _hoops_HS _hoops_IRS _hoops_RPPS, _hoops_PSCR _hoops_SR *_hoops_SIAS* _hoops_SHH _hoops_GHGA
				 *	_hoops_ISSC-_hoops_IS-_hoops_RIPS _hoops_GRAA-_hoops_CCSHP _hoops_CPCP, _hoops_PPR _hoops_RH _hoops_AHCR _hoops_SRHR
				 *	_hoops_CHH _hoops_HS _hoops_IS _hoops_SHH _hoops_RPSGA.)
				 */

				!BIT (dc->_hoops_CPGPR, _hoops_IHPGP) &&
				!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|_hoops_GISIR) &&
				BIT (_hoops_SRCP->_hoops_RRHH, _hoops_PASIR)) {

				_hoops_ICSIR->_hoops_HRSCP = true;
				dc->_hoops_CPGPR |= _hoops_GGARA & ~_hoops_AASCA;
			}
		}

		nr->current |= _hoops_CSGGR;
	}
#endif
	nr->current &= ~_hoops_GSSHP;
	nr->_hoops_RCSHR &= ~_hoops_GSSHP;

	nr->current |= nr->_hoops_RCSHR & (_hoops_CISHP|_hoops_RSSHP);

	nr->current |= _hoops_HPGSP;
	nr->_hoops_RCSHR |= _hoops_HPGSP;

	_hoops_RRCI = _hoops_HGCGA (dc, "szb", nr);

	// _hoops_HSPP _hoops_CCA _hoops_HPRGR _hoops_ICCGR _hoops_GPAC
	_hoops_RRCI->_hoops_CHCI					= HD_Standard_Render;
	_hoops_RRCI->_hoops_GGSI		= nullroutine;
	_hoops_RRCI->_hoops_AICI		= nullroutine;
	_hoops_RRCI->_hoops_AIGC		= nullroutine;
	_hoops_RRCI->_hoops_PPCI	= nullroutine;
	_hoops_RRCI->_hoops_CSPGR			= nullroutine;
	_hoops_RRCI->_hoops_AGHGR			= nullroutine;

	_hoops_RRCI->draw_3d_sphere			= HD_Std_3D_Sphere;
	_hoops_RRCI->draw_3d_polycylinder	= HD_Std_3D_PolyCylinder;
	_hoops_RRCI->draw_3d_cylinder		= HD_Std_3D_Cylinder;
	_hoops_RRCI->draw_3d_nurbs_curve		= HD_Std_3D_NURBS_Curve;
	_hoops_RRCI->draw_3d_nurbs_surface	= HD_Std_3D_NURBS_Surface;
	_hoops_RRCI->draw_3d_ellipse			= HD_Std_3D_Ellipse;
	_hoops_RRCI->draw_3d_elliptical_arc	= HD_Std_3D_Elliptical_Arc;
	_hoops_RRCI->draw_3d_marker			= HD_Std_3D_Marker;
	_hoops_RRCI->_hoops_RIICP		= HD_Std_3D_Multimarker;
	_hoops_RRCI->draw_3d_polyedge		= HD_Std_3D_Polyedge;
	_hoops_RRCI->draw_3d_polyedge_from_tristrip = nullroutine;
	_hoops_RRCI->draw_3d_polymarker		= HD_Std_3D_Polymarker;
	_hoops_RRCI->draw_3d_polyline		= HD_Std_3D_Polyline;
	_hoops_RRCI->draw_3d_polygon			= HD_Std_3D_Polygon;
	_hoops_RRCI->_hoops_SHCHP			= HD_Std_3D_Contour;
	_hoops_RRCI->draw_3d_polyhedron		= HD_Std_3D_Polyhedron;
	_hoops_RRCI->draw_3d_image			= HD_Std_3D_Image;
	_hoops_RRCI->draw_3d_text			= HD_Std_3D_Text;
	_hoops_RRCI->draw_3d_tristrip		= HD_Std_3D_Tristrip;
	_hoops_RRCI->_hoops_CRCGA	= HD_Std_3D_Stenciled_Quad;
	_hoops_RRCI->_hoops_ARCI	= HD_Draw_Indexicated_3D_Tristrip;
	_hoops_RRCI->_hoops_PPAS	= HD_Draw_Indexicated_3D_Polyedge;

	_hoops_RRCI->_hoops_CSCGA			= HD_Standard_Draw_Inter_Text;

	_hoops_RRCI->_hoops_RPCGA			= HD_Std_DC_Polygon;
	_hoops_RRCI->draw_dc_face			= HD_Std_DC_Face;
	_hoops_RRCI->draw_dc_ellipse			= HD_Std_DC_Ellipse;
	_hoops_RRCI->_hoops_CCISR	= HD_Std_DC_Elliptical_Arc;
	_hoops_RRCI->_hoops_SCISR = HD_Std_DC_Outline_Ellipse;
	_hoops_RRCI->draw_dc_polymarker		= HD_Std_DC_Polymarker;
	_hoops_RRCI->_hoops_SPCGA	= HD_Std_DC_Stenciled_Quad;

	_hoops_RRCI->draw_dc_colorized_face	= HD_Std_DC_Colorized_Face;
	_hoops_RRCI->draw_dc_colorized_polydot = HD_Std_DC_Colorized_Polydot;

	_hoops_RRCI->draw_dc_textured_polytriangle		= HD_Span_DC_Textured_Polytris;
	_hoops_RRCI->draw_dc_phong_polytriangle			= HD_Span_DC_Phong_Polytris;
	_hoops_RRCI->draw_dc_textured_polyline			= HD_Span_DC_Textured_Polyline;
	_hoops_RRCI->draw_dc_phong_polyline				= HD_Span_DC_Phong_Polyline;


	_hoops_RRCI->_hoops_GCCGA			= HD_Rasterize_DC_Spans_C24_U;
	_hoops_RRCI->_hoops_ACCGA			= HD_Rasterize_DC_Spans_C24_G;
	_hoops_RRCI->_hoops_HCCGA			= HD_Rasterize_DC_Spans_C24_R;
	if (_hoops_ICSIR->_hoops_GCSCP == Image_MAPPED_8)
		_hoops_RRCI->_hoops_CICGA				= HD_Rasterize_DC_Spans_C08_U;
	else
		_hoops_RRCI->_hoops_CICGA				= HD_Rasterize_DC_Spans_C24_U;


	// _hoops_PHIC _hoops_IGH _hoops_IS _hoops_SSGSP _hoops_PICA _hoops_IH _hoops_GASAR _hoops_PHSPR,
	// _hoops_PAR, _hoops_RRI _hoops_GGRSP, _hoops_GRSCP _hoops_SSPP _hoops_CRGR _hoops_RH _hoops_HCHSR/_hoops_SSH _hoops_SRHR.
	_hoops_RRCI->draw_dc_text			= _hoops_GISCP;
	_hoops_RRCI->draw_window				= _hoops_CGGSP;

	if (_hoops_ASGSP ||
		dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR &&
		_hoops_ICSIR->_hoops_GCSCP != Image_MAPPED_8) {
		_hoops_RRCI->draw_dc_polytriangle			= HD_Span_DC_Polytriangle;
		_hoops_RRCI->draw_dc_colorized_polytriangle	= HD_Span_DC_Colorized_Polytris;
		_hoops_RRCI->draw_dc_gouraud_polytriangle	= HD_Span_DC_Gouraud_Polytris;

		_hoops_RRCI->draw_dc_polyline				= HD_Span_DC_Polyline;
		_hoops_RRCI->draw_dc_colorized_polyline		= HD_Span_DC_Colorized_Polyline;
		_hoops_RRCI->draw_dc_gouraud_polyline		= HD_Span_DC_Gouraud_Polyline;

		_hoops_RRCI->draw_dc_polydot					= HD_Std_DC_Polydot;
	}
#ifndef _hoops_GCSIR
	else if (_hoops_RSGSP) {
		if (_hoops_ICSIR->_hoops_GCSCP == Image_MAPPED_8) {
			_hoops_RRCI->draw_dc_polytriangle				= HD_Buffer_DC_Polytris_C08_Z16_U;
			_hoops_RRCI->draw_dc_colorized_polytriangle		= HD_Buffer_DC_Polytris_C08_Z16_C;
			_hoops_RRCI->draw_dc_gouraud_polytriangle		= HD_Buffer_DC_Polytris_C08_Z16_G;

			_hoops_RRCI->draw_dc_polyline					= HD_Buffer_DC_Polyline_C08_Z16_U;
			_hoops_RRCI->draw_dc_colorized_polyline			= HD_Buffer_DC_Polyline_C08_Z16_C;
			_hoops_RRCI->draw_dc_gouraud_polyline			= HD_Buffer_DC_Polyline_C08_Z16_G;

			_hoops_RRCI->draw_dc_polydot						= HD_Buffer_DC_Polydot_C08_Z16;
		}
		else {
			_hoops_RRCI->draw_dc_polytriangle				= HD_Buffer_DC_Polytris_C24_Z16_U;
			_hoops_RRCI->draw_dc_colorized_polytriangle		= HD_Buffer_DC_Polytris_C24_Z16_C;
			_hoops_RRCI->draw_dc_gouraud_polytriangle		= HD_Buffer_DC_Polytris_C24_Z16_G;

			_hoops_RRCI->draw_dc_polyline					= HD_Buffer_DC_Polyline_C24_Z16_U;
			_hoops_RRCI->draw_dc_colorized_polyline			= HD_Buffer_DC_Polyline_C24_Z16_C;
			_hoops_RRCI->draw_dc_gouraud_polyline			= HD_Buffer_DC_Polyline_C24_Z16_G;

			_hoops_RRCI->draw_dc_polydot						= HD_Buffer_DC_Polydot_C24_Z16;

#ifdef _hoops_RGRSP
			_hoops_RRCI->draw_dc_polytriangle				= HD_SZB_DC_Polytris;
			_hoops_RRCI->draw_dc_colorized_polytriangle		= HD_SZB_DC_Colorized_Triangle;
			_hoops_RRCI->draw_dc_gouraud_polytriangle		= HD_SZB_DC_Gouraud_Triangle;

			_hoops_RRCI->draw_dc_polyline					= HD_SZB_DC_Polyline;
			_hoops_RRCI->draw_dc_colorized_polyline			= HD_SZB_DC_Colorized_Line;
			_hoops_RRCI->draw_dc_gouraud_polyline			= HD_SZB_DC_Gouraud_Line;
#endif
		}
	}
#endif
	else {
		if (_hoops_ICSIR->_hoops_GCSCP == Image_MAPPED_8) {
			_hoops_RRCI->draw_dc_polytriangle				= HD_Buffer_DC_Polytris_C08_Z00_U;
			_hoops_RRCI->draw_dc_colorized_polytriangle		= HD_Buffer_DC_Polytris_C08_Z00_C;
			_hoops_RRCI->draw_dc_gouraud_polytriangle		= HD_Buffer_DC_Polytris_C08_Z00_G;

			_hoops_RRCI->draw_dc_polyline					= HD_Buffer_DC_Polyline_C08_Z00_U;
			_hoops_RRCI->draw_dc_colorized_polyline			= HD_Buffer_DC_Polyline_C08_Z00_C;
			_hoops_RRCI->draw_dc_gouraud_polyline			= HD_Buffer_DC_Polyline_C08_Z00_G;

			_hoops_RRCI->draw_dc_polydot						= HD_Buffer_DC_Polydot_C08_Z00;
		}
		else {
			_hoops_RRCI->draw_dc_polytriangle				= HD_Buffer_DC_Polytris_C24_Z00_U;
			_hoops_RRCI->draw_dc_colorized_polytriangle		= HD_Buffer_DC_Polytris_C24_Z00_C;
			_hoops_RRCI->draw_dc_gouraud_polytriangle		= HD_Buffer_DC_Polytris_C24_Z00_G;

			_hoops_RRCI->draw_dc_polyline					= HD_Buffer_DC_Polyline_C24_Z00_U;
			_hoops_RRCI->draw_dc_colorized_polyline			= HD_Buffer_DC_Polyline_C24_Z00_C;
			_hoops_RRCI->draw_dc_gouraud_polyline			= HD_Buffer_DC_Polyline_C24_Z00_G;

			_hoops_RRCI->draw_dc_polydot						= HD_Buffer_DC_Polydot_C24_Z00;
		}
	}

#ifndef _hoops_GCSIR
	if (_hoops_RSGSP) {
		if (1 || _hoops_ASGSP)
			_hoops_RRCI->draw_dc_rgb32_rasters		= HD_Buffer_DC_Raster_C32_Z16;
		else
			_hoops_RRCI->draw_dc_rgb32_rasters		= HD_Buffer_DC_Raster_C24_Z16;
		_hoops_RRCI->_hoops_CCCSR			= HD_Buffer_DC_Raster_C08_Z16;

		_hoops_RRCI->_hoops_CAAGR					= _hoops_CAAGR;
	}
	else
#endif
	{
		if (1 || _hoops_ASGSP)
			_hoops_RRCI->draw_dc_rgb32_rasters		= HD_Buffer_DC_Raster_C32_Z00;
		else
			_hoops_RRCI->draw_dc_rgb32_rasters		= HD_Buffer_DC_Raster_C24_Z00;
		_hoops_RRCI->_hoops_CCCSR			= HD_Buffer_DC_Raster_C08_Z00;
	}

	if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR &&
		_hoops_ICSIR->_hoops_GCSCP != Image_MAPPED_8)
		_hoops_RRCI->draw_dc_rectangle				= HD_Span_DC_Rectangle;
	else if (_hoops_ICSIR->_hoops_GCSCP == Image_MAPPED_8)
		_hoops_RRCI->draw_dc_rectangle				= HD_Buffer_DC_Rectangle_C08;
	else
		_hoops_RRCI->draw_dc_rectangle				= HD_Buffer_DC_Rectangle_C24;

	if (_hoops_ICSIR->_hoops_GCSCP == Image_MAPPED_8)
		_hoops_RRCI->_hoops_HPCGA					= HD_Image_To_Mapped8_Rasters;
	else
		_hoops_RRCI->_hoops_HPCGA					= HD_Image_To_RGB32_Rasters;


	// _hoops_GRH _hoops_AGRSP
	if (dc->_hoops_APHHP != null) {
		_hoops_RRCI->draw_dc_polytriangle			= HD_SZB_DC_Polytriangle;
		_hoops_RRCI->draw_dc_colorized_polytriangle	= HD_SZB_DC_Colorized_Polytris;
		_hoops_RRCI->draw_dc_gouraud_polytriangle	= HD_SZB_DC_Gouraud_Polytris;
		_hoops_RRCI->draw_dc_phong_polytriangle		= HD_SZB_DC_Phong_Polytris;
		_hoops_RRCI->draw_dc_textured_polytriangle	= HD_SZB_DC_Textured_Polytris;
		_hoops_RRCI->draw_dc_polyline				= HD_SZB_DC_Polyline;
	}



	bool				_hoops_PIGSP = false;
	int					_hoops_PGRSP = _hoops_SGRA->_hoops_SCIH.top - _hoops_SGRA->_hoops_SCIH.bottom + 1;
	bool				_hoops_HGRSP = _hoops_ICSIR->_hoops_HRSCP;

	if (BIT(nr->flags, _hoops_SISHP)) {
		_hoops_PGRSP = nr->_hoops_ASIR->buffer._hoops_SPAAP;

		if (_hoops_PGRSP < 0) {
			/* _hoops_IGRSP _hoops_CSAP _hoops_GGR "_hoops_GCSRR", _hoops_HAR "_hoops_AHRH" - _hoops_SICR _hoops_IS _hoops_AHRH */
			int				_hoops_CGRSP;

			if (_hoops_ICSIR->_hoops_GCSCP == _hoops_CSGSP)
				_hoops_CGRSP = sizeof (RGBAS32);
			else
				_hoops_CGRSP = sizeof (unsigned char);

			if (_hoops_RSGSP)
				_hoops_CGRSP += sizeof (_hoops_RAAH); /* _hoops_RH _hoops_SSH _hoops_SRHR */

			_hoops_PGRSP /= -(_hoops_SGRA->_hoops_SCIH.right - _hoops_SGRA->_hoops_SCIH.left) * _hoops_CGRSP;
			if (_hoops_PGRSP == 0)
				_hoops_PGRSP = 1;
		}

		if (_hoops_PGRSP  <  _hoops_SGRA->_hoops_SCIH.top - _hoops_SGRA->_hoops_SCIH.bottom + 1)
			_hoops_PIGSP = true;
	}


	if (_hoops_PIGSP) {
		/* _hoops_SGRSP, _hoops_PAH'_hoops_RA _hoops_PGICR _hoops_SGHIP */
		if (BIT (dc->_hoops_CPGPR, _hoops_IHPGP)) {
			dc->_hoops_CPGPR &= ~_hoops_IHPGP;
			dc->_hoops_CPGPR |= _hoops_GGARA & ~_hoops_AASCA;
			if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GISIR) ||
				BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR) &&
				!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_RCHGP))
				nr->_hoops_RCSHR |= _hoops_PRHIP;
			/* _hoops_HHSA _hoops_HCH _hoops_SRHR _hoops_SCAC, _hoops_PRGI _hoops_IH _hoops_SGHIP */
			_hoops_HGRSP |= (BIT (nr->current, _hoops_RSSHP));
		}
		_hoops_SPSCP (_hoops_ICSIR);
	}
	else {
		if (BIT (dc->_hoops_CPGPR, _hoops_ICHPA)) {
			if (BIT (dc->_hoops_CPGPR, _hoops_IHPGP)) {
				dc->_hoops_CPGPR &= ~_hoops_IHPGP;
				dc->_hoops_CPGPR |= _hoops_GGARA & ~_hoops_AASCA;
			}
			_hoops_SPSCP (_hoops_ICSIR);
		}
		else if (!ANYBIT (dc->_hoops_CPGPR, _hoops_HPPGP|_hoops_IHPGP)) {
			_hoops_SPSCP (_hoops_ICSIR);
		}

		if (dc->_hoops_APHHP == null &&
			_hoops_ICSIR->_hoops_PSPIP &&
			BIT (dc->_hoops_CPGPR, _hoops_GIPGP) &&
			!BIT (nr->_hoops_SAIR->_hoops_ASIHP, _hoops_GCARP)) {
			/* _hoops_IPS _hoops_HII _hoops_RCPGR */
			Int_Rectangle const *		_hoops_RCIIP;

			if (dc->options._hoops_SRRRR &&
				dc->_hoops_PGCC._hoops_CHHSR == _hoops_RCPGA) {
				/* _hoops_HASC _hoops_CCAH _hoops_CRGR _hoops_RHGS _hoops_PPR _hoops_SGH _hoops_SGS _hoops_SPR (_hoops_CR _hoops_SR _hoops_PPPPR'_hoops_RA _hoops_SGH _hoops_SCH _hoops_GICS) */
				if (_hoops_ICSIR->_hoops_PCIIP.left < _hoops_ICSIR->_hoops_HCIIP.left)
					_hoops_ICSIR->_hoops_HCIIP.left = _hoops_ICSIR->_hoops_PCIIP.left;
				if (_hoops_ICSIR->_hoops_PCIIP.right > _hoops_ICSIR->_hoops_HCIIP.right)
					_hoops_ICSIR->_hoops_HCIIP.right = _hoops_ICSIR->_hoops_PCIIP.right;
				if (_hoops_ICSIR->_hoops_PCIIP.bottom < _hoops_ICSIR->_hoops_HCIIP.bottom)
					_hoops_ICSIR->_hoops_HCIIP.bottom = _hoops_ICSIR->_hoops_PCIIP.bottom;
				if (_hoops_ICSIR->_hoops_PCIIP.top > _hoops_ICSIR->_hoops_HCIIP.top)
					_hoops_ICSIR->_hoops_HCIIP.top = _hoops_ICSIR->_hoops_PCIIP.top;

				_hoops_RCIIP = &_hoops_ICSIR->_hoops_HCIIP;
			}
			else
				_hoops_RCIIP = &_hoops_ICSIR->_hoops_PCIIP;

			if (_hoops_RCIIP->left <= _hoops_RCIIP->right &&
				_hoops_RCIIP->bottom <= _hoops_RCIIP->top) {
				_hoops_PRGSP (_hoops_ICSIR, _hoops_ICSIR->_hoops_RIIIP, _hoops_ICSIR->_hoops_HIAI, _hoops_RCIIP);
				if (_hoops_ICSIR->_hoops_SCSCP != null)
					_hoops_PRGSP (_hoops_ICSIR, _hoops_ICSIR->_hoops_SCSCP, _hoops_ICSIR->depth_buffer, _hoops_RCIIP);
			}
		}
	}

	//_hoops_CSPH->_hoops_CPGGR |= _hoops_GRRSP;

	dc->_hoops_AHSI->_hoops_CPGPR = dc->_hoops_CPGPR;

	Int_Rectangle			area = _hoops_SGRA->_hoops_PHRA;

	if (area.left < _hoops_SGRA->_hoops_SCIH.left)
		area.left = _hoops_SGRA->_hoops_SCIH.left;
	if (area.right > _hoops_SGRA->_hoops_SCIH.right)
		area.right = _hoops_SGRA->_hoops_SCIH.right;
	if (area.bottom < _hoops_SGRA->_hoops_SCIH.bottom)
		area.bottom = _hoops_SGRA->_hoops_SCIH.bottom;
	if (area.top > _hoops_SGRA->_hoops_SCIH.top)
		area.top = _hoops_SGRA->_hoops_SCIH.top;


	int						_hoops_RRRSP = area.bottom;
	int						_hoops_ARRSP = area.top;
	int						top = _hoops_ARRSP;
	int						_hoops_PRRSP;

	_hoops_PRRSP = (_hoops_ARRSP - _hoops_RRRSP + 1  +  _hoops_PGRSP - 1) / _hoops_PGRSP;
	top -= (_hoops_PRRSP - 1) * _hoops_PGRSP;

	Tree_Node const *		_hoops_HRRSP =  dc->_hoops_AHSI;
	do {
		int								bottom = _hoops_IAAA (top - _hoops_PGRSP + 1, _hoops_RRRSP);
		Net_Rendition					_hoops_RHICP = _hoops_HRRSP->nr.Copy();
		_hoops_HHCR alter &		_hoops_AHICP = _hoops_RHICP->transform_rendition.Modify();

		// _hoops_IRRSP _hoops_RH _hoops_CIHH

		if (_hoops_AHICP->_hoops_AGAA.bottom	< bottom)
			_hoops_AHICP->_hoops_AGAA.bottom	= bottom;
		if (_hoops_AHICP->_hoops_AGAA.top	> top)
			_hoops_AHICP->_hoops_AGAA.top	= top;

		if (_hoops_AHICP->_hoops_AGAA.bottom <= _hoops_AHICP->_hoops_AGAA.top) {
			_hoops_CGRA alter &		_hoops_CRRSP = _hoops_RHICP->_hoops_SAIR.Modify();

			if (bottom != _hoops_RRRSP)		// _hoops_CGHI _hoops_CGGR _hoops_IS _hoops_PGSA _hoops_SAHR _hoops_SRRSP _hoops_RH _hoops_SCGR _hoops_GIIS
				dc->Push_Tree (_hoops_RHICP, _hoops_SRCP, path);

			_hoops_CRRSP->_hoops_ASSIR = nr->_hoops_SAIR->_hoops_ASSIR;

			dc->_hoops_AHSI->_hoops_GARSP (POOL_NEW(dc->memory_pool, _hoops_GIGSP)(_hoops_ICSIR,
															  area.left - dc->_hoops_ARAIP,
															  bottom - dc->_hoops_ARAIP,
															  _hoops_HGRSP));

			dc->_hoops_AHSI->_hoops_GSHCP (POOL_NEW(dc->memory_pool, _hoops_AIGSP)(_hoops_ICSIR, _hoops_PIGSP));
		}

		top += _hoops_PGRSP;
	} while (top <= _hoops_ARRSP);

#endif
}

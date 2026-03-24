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
 * $Id: obf_tmp.txt 1.47 2009-11-07 01:16:33 covey Exp $
 */
#include "hoops.h"
#include "driver.h"
#include "hd_proto.h"

/*
 * _hoops_RARSP _hoops_HPPA _hoops_GHC _hoops_IS _hoops_PCCP _hoops_CSCR. _hoops_HGI _hoops_HRGR _hoops_IRS _hoops_RHAA-_hoops_HPPP _hoops_GPP
 * _hoops_GISP-3D-_hoops_AARSP.
 */

GLOBAL_FUNCTION void HD_Draw_Trimmed_DC_Image (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	int							hoffset,
	Image_Format				format,
	int							row_bytes,
	void const * const *		rasters,
	int							pattern,
	Driver_Color const *		contrast_color,
	Image const *				db_image) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	int							vcount = (int)(start->y - end->y + 1);
	int							_hoops_PARSP = (int)(end->x - start->x + 1);

	/* _hoops_HARSP _hoops_SAHR _hoops_ARPP _hoops_PGSA-_hoops_CSPH-_hoops_CSCR _hoops_IS _hoops_HSPH _hoops_ACSRR
	 * _hoops_RH _hoops_SCGR _hoops_HPPA _hoops_GHC.
	 */

	if (HD_Box_Within_Cutting_Planes (_hoops_IHCR, start->x, start->y, start->z, _hoops_PARSP, vcount)) {
		_hoops_SSGCP (nr, start, end,
						   hoffset, format, row_bytes,
						   rasters,
						   pattern, contrast_color, db_image);
	}
	else if (HD_Box_Outside_Cutting_Planes (_hoops_IHCR, start->x, start->y, start->z, _hoops_PARSP, vcount)) {
		/* _hoops_RPAPR */
	}
	else {
		_hoops_SSP const &	_hoops_GGH = _hoops_IHCR->_hoops_RGH;
		_hoops_IAPA const *		_hoops_IARSP = null;
		DC_Point						_hoops_CARSP;
		DC_Point						_hoops_IPIPP;

		if (db_image != null && BIT (db_image->flags, _hoops_SHCC)) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_IARSP = _hoops_GGH->_hoops_IRH;
		}
		else
			_hoops_IARSP = _hoops_GGH->_hoops_PHCA;

		/* _hoops_HAIA _hoops_IIGR _hoops_RH _hoops_GRPC _hoops_CHR _hoops_GGR, _hoops_HHH _hoops_CHR _hoops_GGSR */

		/* _hoops_CICR _hoops_PGSA _hoops_SCH _hoops_PPSCP-_hoops_HPP-_hoops_PPSCP */

		/* _hoops_HSRR _hoops_GRR _hoops_PPSCP, _hoops_RPGP _hoops_IS _hoops_CACH _hoops_RSH _hoops_GSGS _hoops_HRGR _hoops_GGR */

		_hoops_CARSP.y = start->y;
		_hoops_CARSP.z = start->z;

		do {
			_hoops_IAPA const *_hoops_HRCAR = _hoops_IARSP;
			int						_hoops_SARSP,
												_hoops_GPRSP;

			/* _hoops_IH _hoops_GRR _hoops_HPPA _hoops_ARP, _hoops_CCPH _hoops_RH _hoops_PPSCP _hoops_ACSRR _hoops_GRR _hoops_IPPA */
			do {
				_hoops_GPPA const *_hoops_IRCAR = _hoops_HRCAR->_hoops_APPA;

				_hoops_GPRSP = (int)start->x;
				_hoops_SARSP = (int)end->x;

				_hoops_PCCAR {
					float			_hoops_RPRSP;

					if (_hoops_IRCAR->_hoops_SPPA.a > 0.0f) {
						_hoops_RPRSP = -(_hoops_IRCAR->_hoops_SPPA.b*_hoops_CARSP.y +
									   _hoops_IRCAR->_hoops_SPPA.c*_hoops_CARSP.z +
									   _hoops_IRCAR->_hoops_SPPA.d) / _hoops_IRCAR->_hoops_SPPA.a;

						if (start->x <= _hoops_RPRSP) {
							/* _hoops_RAAP _hoops_RSGR _hoops_HRGR _hoops_GIAA _hoops_RGR _hoops_AACC - _hoops_CCPH _hoops_HII _hoops_RPHR */
							if ((float)_hoops_SARSP > _hoops_RPRSP) _hoops_SARSP = (int)_hoops_RPRSP;
						}
						else break; /* _hoops_HCR _hoops_PPRGA */
					}
					else if (_hoops_IRCAR->_hoops_SPPA.a < 0.0f) {
						_hoops_RPRSP = -(_hoops_IRCAR->_hoops_SPPA.b*_hoops_CARSP.y +
									   _hoops_IRCAR->_hoops_SPPA.c*_hoops_CARSP.z +
									   _hoops_IRCAR->_hoops_SPPA.d) / _hoops_IRCAR->_hoops_SPPA.a;

						if (end->x >= _hoops_RPRSP) {
							/* _hoops_RPHR _hoops_RSGR _hoops_HRGR _hoops_GIAA - _hoops_CCPH _hoops_HII _hoops_RAAP */
							if ((float)_hoops_GPRSP < _hoops_RPRSP) _hoops_GPRSP = (int)_hoops_RPRSP;
						}
						else break; /* _hoops_HCR _hoops_PPRGA */
					}
					else {
						/* _hoops_GGAIA _hoops_IS _hoops_SPCR */

						if (_hoops_IRCAR->_hoops_SPPA.a * start->x +
							_hoops_IRCAR->_hoops_SPPA.b * _hoops_CARSP.y +
							_hoops_IRCAR->_hoops_SPPA.c * _hoops_CARSP.z +
							_hoops_IRCAR->_hoops_SPPA.d > 0.0f) break; /* _hoops_HCR _hoops_PPRGA */
					}

					if ((_hoops_IRCAR = _hoops_IRCAR->next) == null) {
						if (_hoops_GPRSP <= _hoops_SARSP) {
							float	_hoops_APRSP;

							/* _hoops_PPRSP: _hoops_RSGR->_hoops_SISR != _hoops_HSPP->_hoops_SISR, _hoops_HPP _hoops_GGSGR _hoops_IIGR _hoops_PCGC _hoops_ARRS */
							_hoops_APRSP = (end->z - start->z) / (float)(end->x - start->x);

							_hoops_CARSP.x = (float)_hoops_GPRSP;
							_hoops_CARSP.z = start->z + (_hoops_CARSP.x - start->x) * _hoops_APRSP;
							_hoops_IPIPP.x = (float)_hoops_SARSP;
							_hoops_IPIPP.y = _hoops_CARSP.y;
							_hoops_IPIPP.z = start->z + (_hoops_IPIPP.x - start->x) * _hoops_APRSP;
							_hoops_SSGCP (nr, &_hoops_CARSP, &_hoops_IPIPP,
											   hoffset + ((int)_hoops_CARSP.x - (int)start->x),
											   format, row_bytes,
											   rasters,
											   pattern, contrast_color, db_image);
						}
						break;
					}
				}
			} while ((_hoops_HRCAR = _hoops_HRCAR->next) != null);

			--_hoops_CARSP.y;
			++rasters;
		} while (--vcount != 0);
	}
}



GLOBAL_FUNCTION void HD_Draw_Clipped_DC_Image (
	Net_Rendition const &			nr,
	DC_Point const *				start,
	DC_Point const *				end,
	int								hoffset,
	Image_Format					format,
	int								row_bytes,
	void const * const *			rasters,
	int								pattern,
	Driver_Color const *			contrast_color,
	Image const *					db_image) {
	_hoops_HHCR const &		_hoops_IHCR = nr->transform_rendition;
	int								vcount = (int)(start->y - end->y + 1);
	Net_Rendition					_hoops_RHICP = nr.Copy();
	_hoops_HHCR				_hoops_AHICP = _hoops_RHICP->transform_rendition.Modify();
	void const * const *			_hoops_HPRSP = rasters;
	DC_Point						_hoops_CARSP = *start;
	DC_Point						_hoops_IPIPP;
	_hoops_ASHH const *		_hoops_CRAIR;
	_hoops_GPPA const *	_hoops_GRCPR;
	int								i = 0;
	
	// _hoops_HARSP _hoops_SAHR _hoops_ARPP _hoops_PGSA-_hoops_CSPH-_hoops_CSCR _hoops_IS _hoops_HSPH _hoops_ACSRR _hoops_RH _hoops_SCGR _hoops_HSPH _hoops_ISPH.

	if (_hoops_AHICP->_hoops_HCHH->_hoops_AHGGA == null)
		HD_Validate_Clipping_Rendition (_hoops_AHICP, _hoops_AHICP->_hoops_HCHH);

	if (_hoops_AHICP->_hoops_HCHH->_hoops_AHGGA->count == 0)	// _hoops_ISAP _hoops_PAH _hoops_SHH _hoops_CHCC
		return;

	_hoops_CRAIR = _hoops_AHICP->_hoops_HCHH->_hoops_AHGGA;
	_hoops_AHICP->_hoops_HCHH = null;
  

	do {
		_hoops_GRCPR = _hoops_CRAIR->_hoops_GRCPR;

		/* _hoops_HSRR _hoops_GRR _hoops_PPSCP, _hoops_RPGP _hoops_IS _hoops_CACH _hoops_RSH _hoops_GSGS _hoops_HRGR _hoops_GGR */
		do {
			int						_hoops_GPRSP = (int)start->x,
									_hoops_SARSP = (int)end->x;

			/* _hoops_IH _hoops_GRR _hoops_PPSCP, _hoops_RPGP _hoops_GRR _hoops_IPPA */

			for (i=0; i<_hoops_CRAIR->count; i++) {
				float			_hoops_RPRSP;

				if (_hoops_GRCPR[i]._hoops_SPPA.a > 0.0f) {
					_hoops_RPRSP = -(_hoops_GRCPR[i]._hoops_SPPA.b*_hoops_CARSP.y +
								   _hoops_GRCPR[i]._hoops_SPPA.d) / _hoops_GRCPR[i]._hoops_SPPA.a;

					if (start->x <= _hoops_RPRSP) {
						/* _hoops_RAAP _hoops_RSGR _hoops_HRGR _hoops_GIAA _hoops_RGR _hoops_AACC - _hoops_CCPH _hoops_HII _hoops_RPHR */
						if ((float)_hoops_SARSP > _hoops_RPRSP) _hoops_SARSP = (int)_hoops_RPRSP;
					}
					else {
						_hoops_SARSP = _hoops_GPRSP - 1;
						break; /* _hoops_HCR _hoops_PPRGA */
					}
				}
				else if (_hoops_GRCPR[i]._hoops_SPPA.a < 0.0f) {
					_hoops_RPRSP = -(_hoops_GRCPR[i]._hoops_SPPA.b*_hoops_CARSP.y +
								   _hoops_GRCPR[i]._hoops_SPPA.d) / _hoops_GRCPR[i]._hoops_SPPA.a;

					if (end->x >= _hoops_RPRSP) {
						/* _hoops_RPHR _hoops_RSGR _hoops_HRGR _hoops_GIAA - _hoops_CCPH _hoops_HII _hoops_RAAP */
						if ((float)_hoops_GPRSP < _hoops_RPRSP) _hoops_GPRSP = (int)_hoops_RPRSP;
					}
					else {
						_hoops_SARSP = _hoops_GPRSP - 1;
						break; /* _hoops_HCR _hoops_PPRGA */
					}
				}
				else {
					/* _hoops_GGAIA _hoops_IS _hoops_SPCR */

					if (_hoops_GRCPR[i]._hoops_SPPA.a * start->x +
						_hoops_GRCPR[i]._hoops_SPPA.b * _hoops_CARSP.y +
						_hoops_GRCPR[i]._hoops_SPPA.d > 0.0f) {
						_hoops_SARSP = _hoops_GPRSP - 1;
						break; /* _hoops_HCR _hoops_PPRGA */
					}
				}
			}

			if (_hoops_GPRSP <= _hoops_SARSP) {
				float	_hoops_APRSP;

				/* _hoops_PPRSP: _hoops_RSGR->_hoops_SISR != _hoops_HSPP->_hoops_SISR, _hoops_HPP _hoops_GGSGR _hoops_IIGR _hoops_PCGC _hoops_ARRS */
				_hoops_APRSP = (end->z - start->z) / (float)(end->x - start->x);

				_hoops_CARSP.x = (float)_hoops_GPRSP;
				_hoops_CARSP.z = start->z + (_hoops_CARSP.x - start->x) * _hoops_APRSP;
				_hoops_IPIPP.x = (float)_hoops_SARSP;
				_hoops_IPIPP.y = _hoops_CARSP.y;
				_hoops_IPIPP.z = start->z + (_hoops_IPIPP.x - start->x) * _hoops_APRSP;

				if (BIT (_hoops_IHCR->flags, _hoops_CSP))
					HD_Draw_Trimmed_DC_Image (_hoops_RHICP, &_hoops_CARSP, &_hoops_IPIPP,
									   hoffset + ((int)_hoops_CARSP.x - (int)start->x),
									   format, row_bytes,
									   rasters,
									   pattern, contrast_color, db_image);
				else
					_hoops_SSGCP (_hoops_RHICP, &_hoops_CARSP, &_hoops_IPIPP,
									   hoffset + ((int)_hoops_CARSP.x - (int)start->x),
									   format, row_bytes,
									   rasters,
									   pattern, contrast_color, db_image);
			}

			--_hoops_CARSP.y;
			++rasters;
		} _hoops_RGGA (--vcount == 0);

		rasters = _hoops_HPRSP;
		_hoops_CARSP = *start;
	} while ((_hoops_CRAIR = _hoops_CRAIR->next) != null);
}

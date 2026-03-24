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
 * $Id: obf_tmp.txt 1.58 2010-09-22 02:29:38 trask Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "span.h"


#define _hoops_PCGCR(a) _hoops_IRGCR(a)


GLOBAL_FUNCTION void HD_Buffer_DC_Raster_C08_Z00 (
	Net_Rendition const & nr,
	DC_Point const				*_hoops_HCGCR,
	DC_Point const				*_hoops_ICGCR,
	int								row_bytes,
	unsigned char const				*_hoops_GAAC) {
#ifndef _hoops_RGGCR
	unsigned char alter * const		*_hoops_ACSIR;
	unsigned char const * const		*_hoops_CCGCR;
	unsigned char alter				*_hoops_RPPA;
	int								dx;
	int								hoffset;
	_hoops_HCSIR const		*_hoops_ICSIR;
	_hoops_RCSIR					pts[2];

	LOAD_ARGUMENT (_hoops_HCGCR);
	TRUNCATE_POINT (_hoops_HCGCR, 0, pts, 0, x);
	TRUNCATE_POINT (_hoops_HCGCR, 0, pts, 1, y);

	LOAD_ARGUMENT (_hoops_ICGCR);
	TRUNCATE_POINT (_hoops_ICGCR, 0, pts, 1, x);
	TRUNCATE_POINT (_hoops_ICGCR, 0, pts, 0, y);

	dx = pts[1].x - pts[0].x + 1;

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
	_hoops_ACSIR = &((unsigned char alter * const *)
					 _hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[pts[0].y - _hoops_ICSIR->offset.y];
	_hoops_CCGCR = &((unsigned char const * const *)
					 _hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[pts[1].y - _hoops_ICSIR->offset.y + 1];
	hoffset = pts[0].x - _hoops_ICSIR->offset.x;
	_hoops_GAAC =  _hoops_GAAC + row_bytes * (pts[1].y - pts[0].y + 1);

	_hoops_PCCAR {
		_hoops_GAAC = _hoops_GAAC - row_bytes;
		_hoops_RPPA = &_hoops_ACSIR[0][hoffset];

		switch (dx) {
		  default: COPY_MEMORY (_hoops_GAAC, dx, _hoops_RPPA); break;
		  case 16: _hoops_RPPA[15] = _hoops_GAAC[15]; _hoops_HHHI;
		  case 15: _hoops_RPPA[14] = _hoops_GAAC[14]; _hoops_HHHI;
		  case 14: _hoops_RPPA[13] = _hoops_GAAC[13]; _hoops_HHHI;
		  case 13: _hoops_RPPA[12] = _hoops_GAAC[12]; _hoops_HHHI;
		  case 12: _hoops_RPPA[11] = _hoops_GAAC[11]; _hoops_HHHI;
		  case 11: _hoops_RPPA[10] = _hoops_GAAC[10]; _hoops_HHHI;
		  case 10: _hoops_RPPA[9]  = _hoops_GAAC[9];	_hoops_HHHI;
		  case	9: _hoops_RPPA[8]  = _hoops_GAAC[8];	_hoops_HHHI;
		  case	8: _hoops_RPPA[7]  = _hoops_GAAC[7];	_hoops_HHHI;
		  case	7: _hoops_RPPA[6]  = _hoops_GAAC[6];	_hoops_HHHI;
		  case	6: _hoops_RPPA[5]  = _hoops_GAAC[5];	_hoops_HHHI;
		  case	5: _hoops_RPPA[4]  = _hoops_GAAC[4];	_hoops_HHHI;
		  case	4: _hoops_RPPA[3]  = _hoops_GAAC[3];	_hoops_HHHI;
		  case	3: _hoops_RPPA[2]  = _hoops_GAAC[2];	_hoops_HHHI;
		  case	2: _hoops_RPPA[1]  = _hoops_GAAC[1];	_hoops_HHHI;
		  case	1: _hoops_RPPA[0]  = _hoops_GAAC[0];	break;
		  case	0: break;
		}

		_hoops_ACSIR = &_hoops_ACSIR[1];
		if ((void *)_hoops_ACSIR == (void *)_hoops_CCGCR) break;
	}
#endif
}



GLOBAL_FUNCTION void HD_Buffer_DC_Raster_C08_Z16 (
	Net_Rendition const & nr,
	DC_Point const				*_hoops_HCGCR,
	DC_Point const				*_hoops_ICGCR,
	int							row_bytes,
	unsigned char const			*_hoops_GAAC) {
#ifndef _hoops_GCSIR
	unsigned char alter * const	*_hoops_ACSIR;
	unsigned char const * const	*_hoops_CCGCR;
	_hoops_RAAH alter * const			*_hoops_PCSIR;
	unsigned char const			*_hoops_SCGCR;
	unsigned char alter			*_hoops_RPPA;
	unsigned char alter			*_hoops_GSGCR;
	_hoops_RAAH alter					*_hoops_HSSIR;
	_hoops_RSGCR		bz;
	int							dx;
	int							hoffset;
	bool						_hoops_CCSIR = !BIT(nr->transform_rendition->flags, _hoops_ISH);
	int							offset = (int)(nr->transform_rendition->_hoops_SHIH * 
		_hoops_ISSIR(nr->transform_rendition));
	_hoops_HCSIR const	*_hoops_ICSIR;
	_hoops_RCSIR				pts[2];

	LOAD_ARGUMENT (_hoops_HCGCR);
	TRUNCATE_POINT (_hoops_HCGCR, 0, pts, 0, x);
	TRUNCATE_POINT (_hoops_HCGCR, 0, pts, 1, y);
	TRUNCATE_POINT (_hoops_HCGCR, 0, pts, 0, z);

	LOAD_ARGUMENT (_hoops_ICGCR);
	TRUNCATE_POINT (_hoops_ICGCR, 0, pts, 1, x);
	TRUNCATE_POINT (_hoops_ICGCR, 0, pts, 0, y);
	TRUNCATE_POINT (_hoops_ICGCR, 0, pts, 1, z);

	pts[0].z += offset;
	pts[1].z += offset;

	dx = pts[1].x - pts[0].x + 1;
	_hoops_IAGCR (bz, pts[0].z, pts[1].z, dx);

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
	_hoops_PCSIR = &((_hoops_RAAH alter * const *)
					 _hoops_ICSIR->depth_buffer->_hoops_RCPIR)[pts[0].y - _hoops_ICSIR->offset.y];
	_hoops_ACSIR = &((unsigned char alter * const *)
					 _hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[pts[0].y - _hoops_ICSIR->offset.y];
	_hoops_CCGCR = &((unsigned char const * const *)
					 _hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[pts[1].y - _hoops_ICSIR->offset.y + 1];
	hoffset = pts[0].x - _hoops_ICSIR->offset.x;
	_hoops_GAAC = _hoops_GAAC + row_bytes * (pts[1].y - pts[0].y + 1);


	_hoops_PCCAR {
		_hoops_GAAC = _hoops_GAAC - row_bytes;
		_hoops_SCGCR = _hoops_GAAC;
		_hoops_HSSIR = &_hoops_PCSIR[0][hoffset];
		_hoops_RPPA = &_hoops_ACSIR[0][hoffset];
		_hoops_GSGCR = &_hoops_RPPA[dx];

		_hoops_PCCAR {
			if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
				if (_hoops_CCSIR)
					_hoops_HSSIR[0] = bz._hoops_HAGR._hoops_SAGCR;
				else if (_hoops_HSSIR[0] == _hoops_GGGCR)
					_hoops_HSSIR[0]--;

				_hoops_RPPA[0] = _hoops_SCGCR[0];
			}

			_hoops_RPPA = &_hoops_RPPA[1];
			if (_hoops_RPPA == _hoops_GSGCR) break;

			_hoops_HSSIR = &_hoops_HSSIR[1];
			_hoops_SCGCR = &_hoops_SCGCR[1];
			_hoops_APGCR (bz);
		}

		_hoops_ACSIR = &_hoops_ACSIR[1];
		if ((void *)_hoops_ACSIR == (void *)_hoops_CCGCR) break;
	}
#endif
}



GLOBAL_FUNCTION void HD_Buffer_DC_Raster_C24_Z00 (
	Net_Rendition const & nr,
	DC_Point const				*_hoops_HCGCR,
	DC_Point const				*_hoops_ICGCR,
	int							row_bytes,
	RGBAS32 const				*_hoops_GAAC) {
#ifndef _hoops_RGGCR
	RGBAS32 alter * const		*_hoops_ACSIR;
	RGBAS32 const * const		*_hoops_CCGCR;
	RGBAS32 alter				*_hoops_RPPA;
	int							dx;
	int							hoffset;
	_hoops_HCSIR const		*_hoops_ICSIR;
	_hoops_RCSIR					pts[2];

	LOAD_ARGUMENT (_hoops_HCGCR);
	TRUNCATE_POINT (_hoops_HCGCR, 0, pts, 0, x);
	TRUNCATE_POINT (_hoops_HCGCR, 0, pts, 1, y);

	LOAD_ARGUMENT (_hoops_ICGCR);
	TRUNCATE_POINT (_hoops_ICGCR, 0, pts, 1, x);
	TRUNCATE_POINT (_hoops_ICGCR, 0, pts, 0, y);

	dx = pts[1].x - pts[0].x + 1;

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
	_hoops_ACSIR = &((RGBAS32 alter * const *)
					 _hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[pts[0].y - _hoops_ICSIR->offset.y];
	_hoops_CCGCR = &((RGBAS32 const * const *)
					 _hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[pts[1].y - _hoops_ICSIR->offset.y + 1];
	hoffset = pts[0].x - _hoops_ICSIR->offset.x;

	_hoops_GAAC =  (RGBAS32 alter *) ((char alter *) _hoops_GAAC + row_bytes * (pts[1].y - pts[0].y + 1));


	_hoops_PCCAR {
		_hoops_GAAC = (RGBAS32 alter *)((char alter *)_hoops_GAAC - row_bytes);

		_hoops_RPPA = &_hoops_ACSIR[0][hoffset];

		switch (dx) {
		  default: COPY_MEMORY (_hoops_GAAC, dx * sizeof (RGBAS32), _hoops_RPPA); break;
		  case 16: _hoops_RPPA[15] = _hoops_GAAC[15]; _hoops_HHHI;
		  case 15: _hoops_RPPA[14] = _hoops_GAAC[14]; _hoops_HHHI;
		  case 14: _hoops_RPPA[13] = _hoops_GAAC[13]; _hoops_HHHI;
		  case 13: _hoops_RPPA[12] = _hoops_GAAC[12]; _hoops_HHHI;
		  case 12: _hoops_RPPA[11] = _hoops_GAAC[11]; _hoops_HHHI;
		  case 11: _hoops_RPPA[10] = _hoops_GAAC[10]; _hoops_HHHI;
		  case 10: _hoops_RPPA[9]  = _hoops_GAAC[9];	_hoops_HHHI;
		  case	9: _hoops_RPPA[8]  = _hoops_GAAC[8];	_hoops_HHHI;
		  case	8: _hoops_RPPA[7]  = _hoops_GAAC[7];	_hoops_HHHI;
		  case	7: _hoops_RPPA[6]  = _hoops_GAAC[6];	_hoops_HHHI;
		  case	6: _hoops_RPPA[5]  = _hoops_GAAC[5];	_hoops_HHHI;
		  case	5: _hoops_RPPA[4]  = _hoops_GAAC[4];	_hoops_HHHI;
		  case	4: _hoops_RPPA[3]  = _hoops_GAAC[3];	_hoops_HHHI;
		  case	3: _hoops_RPPA[2]  = _hoops_GAAC[2];	_hoops_HHHI;
		  case	2: _hoops_RPPA[1]  = _hoops_GAAC[1];	_hoops_HHHI;
		  case	1: _hoops_RPPA[0]  = _hoops_GAAC[0];	break;
		  case	0: break;
		}

		_hoops_ACSIR = &_hoops_ACSIR[1];
		if ((void *)_hoops_ACSIR == (void *)_hoops_CCGCR) break;
	}
#endif
}



GLOBAL_FUNCTION void HD_Buffer_DC_Raster_C24_Z16 (
	Net_Rendition const & nr,
	DC_Point const				*_hoops_HCGCR,
	DC_Point const				*_hoops_ICGCR,
	int							row_bytes,
	RGBAS32 const				*_hoops_GAAC) {
#ifndef _hoops_GCSIR
	RGBAS32 alter * const		*_hoops_ACSIR;
	RGBAS32 const * const		*_hoops_CCGCR;
	_hoops_RAAH alter * const			*_hoops_PCSIR;
	RGBAS32 const				*_hoops_SCGCR;
	RGBAS32 alter				*_hoops_RPPA;
	RGBAS32 const				*_hoops_GSGCR;
	_hoops_RAAH alter					*_hoops_HSSIR;
	_hoops_RSGCR		bz;
	int							dx;
	int							hoffset;
	bool						_hoops_CCSIR = !BIT(nr->transform_rendition->flags, _hoops_ISH);
	int							offset = (int)(nr->transform_rendition->_hoops_SHIH * 
		_hoops_ISSIR(nr->transform_rendition));
	_hoops_HCSIR const	*_hoops_ICSIR;
	_hoops_RCSIR				pts[2];

	LOAD_ARGUMENT (_hoops_HCGCR);
	TRUNCATE_POINT (_hoops_HCGCR, 0, pts, 0, x);
	TRUNCATE_POINT (_hoops_HCGCR, 0, pts, 1, y);
	TRUNCATE_POINT (_hoops_HCGCR, 0, pts, 0, z);

	LOAD_ARGUMENT (_hoops_ICGCR);
	TRUNCATE_POINT (_hoops_ICGCR, 0, pts, 1, x);
	TRUNCATE_POINT (_hoops_ICGCR, 0, pts, 0, y);
	TRUNCATE_POINT (_hoops_ICGCR, 0, pts, 1, z);

	pts[0].z += offset;
	pts[1].z += offset;

	dx = pts[1].x - pts[0].x + 1;
	_hoops_IAGCR (bz, pts[0].z, pts[1].z, dx);

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
	_hoops_PCSIR = &((_hoops_RAAH alter * const *)
					 _hoops_ICSIR->depth_buffer->_hoops_RCPIR)[pts[0].y - _hoops_ICSIR->offset.y];
	_hoops_ACSIR = &((RGBAS32 alter * const *)
					 _hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[pts[0].y - _hoops_ICSIR->offset.y];
	_hoops_CCGCR = &((RGBAS32 const * const *)
					 _hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[pts[1].y - _hoops_ICSIR->offset.y + 1];
	hoffset = pts[0].x - _hoops_ICSIR->offset.x;
	_hoops_GAAC =  (RGBAS32 alter *) ((char alter *) _hoops_GAAC + row_bytes * (pts[1].y - pts[0].y + 1));


	_hoops_PCCAR {
		_hoops_GAAC = (RGBAS32 alter *)((char alter *)_hoops_GAAC - row_bytes);
		_hoops_SCGCR = _hoops_GAAC;
		_hoops_HSSIR = &_hoops_PCSIR[0][hoffset];
		_hoops_RPPA = &_hoops_ACSIR[0][hoffset];
		_hoops_GSGCR = &_hoops_RPPA[dx];

		_hoops_PCCAR {
			if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
				if (_hoops_CCSIR)
					_hoops_HSSIR[0] = bz._hoops_HAGR._hoops_SAGCR;
				else if (_hoops_HSSIR[0] == _hoops_GGGCR)
					_hoops_HSSIR[0]--;

				*_hoops_RPPA = *_hoops_SCGCR;
			}

			_hoops_RPPA = &_hoops_RPPA[1];
			if (_hoops_RPPA == _hoops_GSGCR) break;

			_hoops_HSSIR = &_hoops_HSSIR[1];
			_hoops_SCGCR = &_hoops_SCGCR[1];
			_hoops_APGCR (bz);
		}

		_hoops_ACSIR = &_hoops_ACSIR[1];
		if ((void *)_hoops_ACSIR == (void *)_hoops_CCGCR) break;
	}
#endif
}



GLOBAL_FUNCTION void HD_Buffer_DC_Raster_C32_Z00 (
	Net_Rendition const & nr,
	DC_Point const				*_hoops_HCGCR,
	DC_Point const				*_hoops_ICGCR,
	int							row_bytes,
	RGBAS32 const				*_hoops_GAAC) {
#ifndef _hoops_RGGCR
	RGBAS32 alter * const		*_hoops_ACSIR;
	RGBAS32 const * const		*_hoops_CCGCR;
	RGBAS32 const				*_hoops_SCGCR;
	RGBAS32 alter				*_hoops_RPPA;
	RGBAS32 const				*_hoops_GSGCR;
	int							dx;
	int							hoffset;
	_hoops_HCSIR const		*_hoops_ICSIR;
	_hoops_RCSIR					pts[2];

	LOAD_ARGUMENT (_hoops_HCGCR);
	TRUNCATE_POINT (_hoops_HCGCR, 0, pts, 0, x);
	TRUNCATE_POINT (_hoops_HCGCR, 0, pts, 1, y);

	LOAD_ARGUMENT (_hoops_ICGCR);
	TRUNCATE_POINT (_hoops_ICGCR, 0, pts, 1, x);
	TRUNCATE_POINT (_hoops_ICGCR, 0, pts, 0, y);

	dx = pts[1].x - pts[0].x + 1;

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
	_hoops_ACSIR = &((RGBAS32 alter * const *)
					 _hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[pts[0].y - _hoops_ICSIR->offset.y];
	_hoops_CCGCR = &((RGBAS32 const * const *)
					 _hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[pts[1].y - _hoops_ICSIR->offset.y + 1];
	hoffset = pts[0].x - _hoops_ICSIR->offset.x;
	_hoops_GAAC =  (RGBAS32 alter *) ((char alter *) _hoops_GAAC + row_bytes * (pts[1].y - pts[0].y + 1));


	_hoops_PCCAR {
		_hoops_GAAC = (RGBAS32 alter *)((char alter *)_hoops_GAAC - row_bytes);
		_hoops_SCGCR = _hoops_GAAC;
		_hoops_RPPA = &_hoops_ACSIR[0][hoffset];
		_hoops_GSGCR = &_hoops_RPPA[dx];

		_hoops_PCCAR {
			if (_hoops_SCGCR->a == _hoops_GPGCR)
				*_hoops_RPPA = *_hoops_SCGCR;
			else {
				int		_hoops_IRIR, _hoops_PRH;

				_hoops_IRIR		 = _hoops_PCGCR (_hoops_SCGCR->a);
				_hoops_PRH = 255 - _hoops_SCGCR->a;

				_hoops_RPPA->r = (_hoops_PCGCR (_hoops_SCGCR->r) * _hoops_IRIR +
						 _hoops_PCGCR (_hoops_RPPA->r) * _hoops_PRH) / 255;
				_hoops_RPPA->g = (_hoops_PCGCR (_hoops_SCGCR->g) * _hoops_IRIR +
						 _hoops_PCGCR (_hoops_RPPA->g) * _hoops_PRH) / 255;
				_hoops_RPPA->b = (_hoops_PCGCR (_hoops_SCGCR->b) * _hoops_IRIR +
						 _hoops_PCGCR (_hoops_RPPA->b) * _hoops_PRH) / 255;
				_hoops_RPPA->a = _hoops_GPGCR;
			}

			_hoops_RPPA = &_hoops_RPPA[1];
			if (_hoops_RPPA == _hoops_GSGCR) break;

			_hoops_SCGCR = &_hoops_SCGCR[1];
		}

		_hoops_ACSIR = &_hoops_ACSIR[1];
		if ((void *)_hoops_ACSIR == (void *)_hoops_CCGCR) break;
	}
#endif
}



GLOBAL_FUNCTION void HD_Buffer_DC_Raster_C32_Z16 (
	Net_Rendition const & nr,
	DC_Point const				*_hoops_HCGCR,
	DC_Point const				*_hoops_ICGCR,
	int							row_bytes,
	RGBAS32 const				*_hoops_GAAC) {
#ifndef _hoops_GCSIR
	RGBAS32 alter * const		*_hoops_ACSIR;
	RGBAS32 const * const		*_hoops_CCGCR;
	_hoops_RAAH alter * const			*_hoops_PCSIR;
	RGBAS32 const				*_hoops_SCGCR;
	RGBAS32 alter				*_hoops_RPPA;
	RGBAS32 const				*_hoops_GSGCR;
	_hoops_RAAH alter					*_hoops_HSSIR;
	_hoops_RSGCR		bz;
	int							dx;
	int							hoffset;
	bool						_hoops_CCSIR = !BIT(nr->transform_rendition->flags, _hoops_ISH);
	_hoops_HCSIR const		*_hoops_ICSIR;
	_hoops_RCSIR					pts[2];
	int							offset = (int)(nr->transform_rendition->_hoops_SHIH * 
		_hoops_ISSIR(nr->transform_rendition));

	LOAD_ARGUMENT (_hoops_HCGCR);
	TRUNCATE_POINT (_hoops_HCGCR, 0, pts, 0, x);
	TRUNCATE_POINT (_hoops_HCGCR, 0, pts, 1, y);
	TRUNCATE_POINT (_hoops_HCGCR, 0, pts, 0, z);

	LOAD_ARGUMENT (_hoops_ICGCR);
	TRUNCATE_POINT (_hoops_ICGCR, 0, pts, 1, x);
	TRUNCATE_POINT (_hoops_ICGCR, 0, pts, 0, y);
	TRUNCATE_POINT (_hoops_ICGCR, 0, pts, 1, z);

	pts[0].z += offset;
	pts[1].z += offset;

	dx = pts[1].x - pts[0].x + 1;
	_hoops_IAGCR (bz, pts[0].z, pts[1].z, dx);

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
	_hoops_PCSIR = &((_hoops_RAAH alter * const *)
					 _hoops_ICSIR->depth_buffer->_hoops_RCPIR)[pts[0].y - _hoops_ICSIR->offset.y];
	_hoops_ACSIR = &((RGBAS32 alter * const *)
					 _hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[pts[0].y - _hoops_ICSIR->offset.y];
	_hoops_CCGCR = &((RGBAS32 const * const *)
					 _hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[pts[1].y - _hoops_ICSIR->offset.y + 1];
	hoffset = pts[0].x - _hoops_ICSIR->offset.x;
	_hoops_GAAC =  (RGBAS32 alter *) ((char alter *) _hoops_GAAC + row_bytes * (pts[1].y - pts[0].y + 1));

	_hoops_PCCAR {
		_hoops_GAAC = (RGBAS32 alter *)((char alter *)_hoops_GAAC - row_bytes);
		_hoops_SCGCR = _hoops_GAAC;
		_hoops_HSSIR = &_hoops_PCSIR[0][hoffset];
		_hoops_RPPA = &_hoops_ACSIR[0][hoffset];
		_hoops_GSGCR = &_hoops_RPPA[dx];

		_hoops_PCCAR {
			if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
				if (_hoops_CCSIR)
					_hoops_HSSIR[0] = bz._hoops_HAGR._hoops_SAGCR;
				else if (_hoops_HSSIR[0] == _hoops_GGGCR)
					_hoops_HSSIR[0]--;

				if (_hoops_SCGCR->a == _hoops_GPGCR) {
					*_hoops_RPPA = *_hoops_SCGCR;
				}
				else if (_hoops_SCGCR->a != 0) {
					int		_hoops_IRIR, _hoops_PRH;

					_hoops_IRIR		 = _hoops_PCGCR (_hoops_SCGCR->a);
					_hoops_PRH = 255 - _hoops_SCGCR->a;

					_hoops_RPPA->r = (_hoops_PCGCR (_hoops_SCGCR->r) * _hoops_IRIR +
							 _hoops_PCGCR (_hoops_RPPA->r) * _hoops_PRH) / 255;
					_hoops_RPPA->g = (_hoops_PCGCR (_hoops_SCGCR->g) * _hoops_IRIR +
							 _hoops_PCGCR (_hoops_RPPA->g) * _hoops_PRH) / 255;
					_hoops_RPPA->b = (_hoops_PCGCR (_hoops_SCGCR->b) * _hoops_IRIR +
							 _hoops_PCGCR (_hoops_RPPA->b) * _hoops_PRH) / 255;
					_hoops_RPPA->a = _hoops_GPGCR;
				}
			}

			_hoops_RPPA = &_hoops_RPPA[1];
			if (_hoops_RPPA == _hoops_GSGCR) break;

			_hoops_HSSIR = &_hoops_HSSIR[1];
			_hoops_SCGCR = &_hoops_SCGCR[1];
			_hoops_APGCR (bz);
		}

		_hoops_ACSIR = &_hoops_ACSIR[1];
		if ((void *)_hoops_ACSIR == (void *)_hoops_CCGCR) break;
	}
#endif
}

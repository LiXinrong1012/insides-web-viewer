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
 * $Id: obf_tmp.txt 1.115 2010-10-28 03:14:26 reuben Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "patterns.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "span.h"


local void _hoops_SHRPI (
	Net_Rendition const &		nr,
	DC_Point const *			_hoops_HCGCR,
	DC_Point const *			_hoops_ICGCR,
	RGBAS32 const *				_hoops_GIRPI,
	int							pattern,
	Driver_Color const *		contrast_color) {
	Display_Context const *		dc = nr->_hoops_SRA;
	int							row;
	int							col;
	RGBAS32 alter *				_hoops_SCGCR;
	RGBAS32 alter *				_hoops_HSGCR;
	RGBAS32						color;
	RGBAS32 alter *				_hoops_GAAC;

	/* _hoops_GIAPR: ?? _hoops_ICPSA _hoops_CPPPR _hoops_HGPSA! */
	_hoops_GAAC = (RGBAS32 alter *)_hoops_GIRPI;

	_hoops_AAASP (dc, (*contrast_color), dc->_hoops_PGCC._hoops_PIHSR, color);
	color.a = _hoops_GPGCR;

	if (pattern != FP_USER_DEFINED) {
		int						_hoops_RIRPI;
		int const				*_hoops_AIRPI;

		row = (int)_hoops_HCGCR->y & (dc->_hoops_ASPGH-1);
		if (dc->_hoops_CCAGH)
			row = dc->_hoops_ASPGH - 1 - row;
		col = (int)_hoops_HCGCR->x & (dc->_hoops_ASPGH-1);

		if (dc->_hoops_ASPGH == 4) {
			_hoops_RIRPI = ((unsigned char const *)(dc->_hoops_GRPH[pattern]))[row];
			_hoops_AIRPI = HOOPS_READ_ONLY.incr_mod_4;
		}
		else if (dc->_hoops_ASPGH == 8) {
			_hoops_RIRPI = ((unsigned char const *)(dc->_hoops_GRPH[pattern]))[row];
			_hoops_AIRPI = HOOPS_READ_ONLY._hoops_PCHGI;
		}
		else if (dc->_hoops_ASPGH == 16) {
			_hoops_RIRPI = ((unsigned short const *)(dc->_hoops_GRPH[pattern]))[row];
			_hoops_AIRPI = HOOPS_READ_ONLY._hoops_HCHGI;
		}
		else {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Bit patterns have not been loaded.");
			return;
		}

		_hoops_SCGCR = _hoops_GAAC;
		_hoops_HSGCR = _hoops_SCGCR + ((int)_hoops_ICGCR->x - (int)_hoops_HCGCR->x + 1);
/*_hoops_RGR _hoops_CSAP _hoops_RHPH _hoops_IH _hoops_RH 0x0f _hoops_AGIR
			_hoops_RPP (_hoops_PIRPI & _hoops_HIRPI._hoops_IIRPI[_hoops_PSCCP])
			*/
		do {
			if (_hoops_RIRPI & (1<<col))
				*_hoops_SCGCR = color;
			col = _hoops_AIRPI[col];
		} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

		_hoops_ARCGH (nr, _hoops_HCGCR, _hoops_ICGCR, 0, _hoops_GAAC);
	}
	else {
		unsigned char const *		_hoops_RIRPI;
		_hoops_SIHHP const *	up = nr->_hoops_IHA->_hoops_PGPH;

		if (up->pattern == null) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "User-defined pattern requested but not defined");
			return;
		}

		row = (int)_hoops_HCGCR->y % up->height;
		if (up->_hoops_RCHHP)
			row = up->height - 1 - row;
		col = (int)_hoops_HCGCR->x % up->width;

		_hoops_RIRPI = &up->pattern[row * up->width];

		_hoops_SCGCR = _hoops_GAAC;
		_hoops_HSGCR = _hoops_SCGCR + ((int)_hoops_ICGCR->x - (int)_hoops_HCGCR->x + 1);


		switch (up->_hoops_ACHHP) {
			case UPAT_NORMAL:
			default: {
				do {
					if (_hoops_RIRPI[col])
						*_hoops_SCGCR = color;
					if (++col == up->width) col = 0;
				} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

				_hoops_ARCGH (nr, _hoops_HCGCR, _hoops_ICGCR, 0, _hoops_GAAC);
			}	break;

			case UPAT_NO_FACE: {
				int							_hoops_CIRPI = 0;
				DC_Point					start, end;
				_hoops_RSGCR	bz;
				int							dx;

				/* _hoops_SISR _hoops_PPR _hoops_SSH _hoops_GIR _hoops_GGR _hoops_HAPR */
				start.y = _hoops_HCGCR->y;
				end.y = _hoops_ICGCR->y;

				dx = int (_hoops_ICGCR->x - _hoops_HCGCR->x);
				if (dx == 0) dx++;
				_hoops_IAGCR(bz, int (_hoops_HCGCR->z), int (_hoops_ICGCR->z), dx); 

				_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR) {
					_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR || _hoops_RIRPI[col]) {
						++_hoops_CIRPI;
						++_hoops_SCGCR;
						if (++col == up->width) col = 0;
						_hoops_APGCR(bz);
					}

					if (_hoops_SCGCR == _hoops_HSGCR) break;
					_hoops_GAAC = _hoops_SCGCR;		/* _hoops_SAHR _hoops_GRP _hoops_SCH _hoops_GAR _hoops_IRS _hoops_SPCS _hoops_SRHR */

					start.x = _hoops_HCGCR->x + _hoops_CIRPI;
					start.z = bz._hoops_HAGR._hoops_SAGCR;

					_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR || !_hoops_RIRPI[col]) {
						*_hoops_SCGCR = color;
						++_hoops_SCGCR;
						if (++col == up->width) col = 0;
						end.z = bz._hoops_HAGR._hoops_SAGCR;
						_hoops_APGCR(bz);
					}

					end.x = start.x + (_hoops_SCGCR - _hoops_GAAC) - 1;

					_hoops_ARCGH (nr, &start, &end, 0, _hoops_GAAC);

					_hoops_CIRPI += _hoops_SCGCR - _hoops_GAAC;
				}
			}	break;

			case UPAT_NO_CONTRAST: {
				int				_hoops_CIRPI = 0;
				DC_Point		start, end;
				_hoops_RSGCR	bz;
				int							dx;

				/* _hoops_SISR _hoops_PPR _hoops_SSH _hoops_GIR _hoops_GGR _hoops_HAPR */
				start.y = _hoops_HCGCR->y;
				end.y = _hoops_ICGCR->y;

				dx = int (_hoops_ICGCR->x - _hoops_HCGCR->x);
				if (dx == 0) dx++;
				_hoops_IAGCR(bz, int (_hoops_HCGCR->z), int (_hoops_ICGCR->z), dx); 

				_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR) {
					_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR || !_hoops_RIRPI[col]) {
						++_hoops_CIRPI;
						++_hoops_SCGCR;
						if (++col == up->width) col = 0;
						_hoops_APGCR(bz);
					}

					if (_hoops_SCGCR == _hoops_HSGCR) break;
					_hoops_GAAC = _hoops_SCGCR;		/* _hoops_SAHR _hoops_GRP _hoops_SCH _hoops_GAR _hoops_IRS _hoops_SPCS _hoops_SRHR */

					start.x = _hoops_HCGCR->x + _hoops_CIRPI;
					start.z = bz._hoops_HAGR._hoops_SAGCR;

					_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR || _hoops_RIRPI[col]) {
						++_hoops_SCGCR;
						if (++col == up->width) col = 0;
						end.z = bz._hoops_HAGR._hoops_SAGCR;
						_hoops_APGCR(bz);
					}

					end.x = start.x + (_hoops_SCGCR - _hoops_GAAC) - 1;

					_hoops_ARCGH (nr, &start, &end, 0, _hoops_GAAC);

					_hoops_CIRPI += _hoops_SCGCR - _hoops_GAAC;
				}
			}	break;
		}
	}
}

#if _MSC_VER >= 1300
#pragma optimize("", off)
#endif

GLOBAL_FUNCTION void HD_Image_To_RGB32_Rasters (
	Net_Rendition const &		inr,
	DC_Point const *			_hoops_HCGCR,
	DC_Point const *			_hoops_ICGCR,
	int							hoffset,
	Image_Format				format,
	int							row_bytes,
	void const * const *		_hoops_HCHIH,
	int							pattern,
	Driver_Color const *		contrast_color,
	Image const *				db_image) {
	Net_Rendition				nr = inr;
	DC_Point					start, end;
	RGBAS32 alter *				_hoops_GAAC = null;
	RGBAS32 alter *				_hoops_SCGCR;
	RGBAS32 alter *				_hoops_HSGCR;
	int							_hoops_PARSP = (int)(_hoops_ICGCR->x - _hoops_HCGCR->x) + 1;
	int							vcount = (int)(_hoops_HCGCR->y - _hoops_ICGCR->y) + 1;
	int							_hoops_SIRPI = 0;

	(void)db_image;

	start.x = _hoops_HCGCR->x;
	start.y = _hoops_HCGCR->y;
	start.z = _hoops_HCGCR->z;
	
	end.x = _hoops_ICGCR->x;
	end.y = _hoops_ICGCR->y;
	end.z = _hoops_ICGCR->z;

	Int_Rectangle const & _hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

	if (_hoops_GPHH.left > start.x) {
		if (_hoops_GPHH.left > end.x)
			return;
		int delta = _hoops_GPHH.left - start.x;
		_hoops_SIRPI += delta;
		_hoops_PARSP -= delta;
		start.x = _hoops_GPHH.left;
	}
	if (_hoops_GPHH.right < end.x) {
		if (_hoops_GPHH.right < start.x)
			return;
		int delta = end.x - _hoops_GPHH.right;
		_hoops_PARSP -= delta;
		end.x = _hoops_GPHH.right;
	}
	if (_hoops_GPHH.bottom > end.y) {
		if (_hoops_GPHH.bottom > start.y)
			return;
		int delta = _hoops_GPHH.bottom - end.y;
		vcount -= delta;
		//_hoops_RSGR._hoops_HAPC = _hoops_HSPH._hoops_PRPC;
	}
	if (_hoops_GPHH.top < start.y) {
		if (_hoops_GPHH.top < end.y)
			return;
		int delta = start.y - _hoops_GPHH.top;
		vcount -= delta;
		_hoops_HCHIH += delta;
		start.y = _hoops_GPHH.top;
	}

	end.y = start.y;

#if 0
	if ((format == _hoops_CSGSP && (db_image && BIT(db_image->flags, _hoops_SHCC))) || 
		(format == Image_RGBA32 || format == _hoops_HRSRH || format == _hoops_CSGSP) &&
		!nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {

		nr.Modify()->_hoops_CPP.Modify()->_hoops_PRH._hoops_HRH = true;
	}
#endif

	switch (format) {
	  case _hoops_CSGSP: {

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
		  RGBAS32 const					*_hoops_GCRPI;

		  if (pattern == FP_SOLID) do {
			  char const				*_hoops_RSGHR;
			  char const				*next;
			  int						_hoops_AAGHR;

			  _hoops_RSGHR = (char const *)((RGBAS32 const *)*_hoops_HCHIH + hoffset);
			  _hoops_AAGHR = _hoops_IICIA;
			  _hoops_GCRPI = (RGBAS32 const *)_hoops_RSGHR;
			  while (--vcount > 0 &&
					 (_hoops_RSGHR + row_bytes ==
					   (next = (char const *)
								((RGBAS32 const *)*++_hoops_HCHIH +
												   hoffset))) &&
					 _hoops_AAGHR >= row_bytes) {
				  _hoops_RSGHR = next;
				  --end.y;
				  _hoops_AAGHR -= row_bytes;
			  }
			  _hoops_ARCGH (nr, &start, &end, row_bytes, _hoops_GCRPI);
			  start.y = --end.y;
		  } _hoops_RGGA (vcount <= 0 || _hoops_GGPGR(nr));

		  else do {
			  _hoops_GCRPI = (RGBAS32 const *)*_hoops_HCHIH++ + hoffset;
			  _hoops_SHRPI (nr, &start, &end, _hoops_GCRPI, pattern, contrast_color);
			  end.y = --start.y;
		  } _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));

		}
		else {

		  do {
				RGBAS32 const *		in;
				RGBAS32 const *		_hoops_RCRPI;
				RGBAS32 const *		_hoops_ACRPI;
				int					_hoops_CIRPI = _hoops_SIRPI;

				in = (RGBAS32 const *)*_hoops_HCHIH++ + hoffset;
				_hoops_RCRPI = in + _hoops_PARSP;

				_hoops_RGGA (in == _hoops_RCRPI) {
					_hoops_RGGA (in == _hoops_RCRPI || in->a != 0) {
						++_hoops_CIRPI;
						++in;
					}

					if (in == _hoops_RCRPI) break;

					_hoops_ACRPI = in;
					_hoops_RGGA (in == _hoops_RCRPI || in->a == 0) ++in;

					start.x = _hoops_HCGCR->x + _hoops_CIRPI;
					end.x = start.x + (in - _hoops_ACRPI) - 1;

					if (pattern == FP_SOLID)
						_hoops_ARCGH (nr, &start, &end, 0, _hoops_ACRPI);
					else
						_hoops_SHRPI (nr, &start, &end, _hoops_ACRPI, pattern, contrast_color);

					_hoops_CIRPI += in - _hoops_ACRPI;
				}
				end.y = --start.y;
		  } _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
		}

	  }	  break;


	  case _hoops_PGPGI: {
		  ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, RGBAS32);

		  do {
			  unsigned short const	*in;

			  in = (unsigned short const *)*_hoops_HCHIH++ + hoffset;
			  _hoops_SCGCR = _hoops_GAAC;
			  _hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

			  do {
				  unsigned char	_hoops_CGRAH = (*in >> 8) & 0x00FF;

				  _hoops_SCGCR->r = _hoops_CGRAH;
				  _hoops_SCGCR->g = _hoops_CGRAH;
				  _hoops_SCGCR->b = _hoops_CGRAH;
				  _hoops_SCGCR->a = _hoops_GPGCR;
				  ++in;
			  } _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

			  _hoops_ARCGH (nr, &start, &end, 0, _hoops_GAAC);

			  end.y = --start.y;
		  } _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
	  }	  break; 

	  case _hoops_AGGSP: {
		  ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, RGBAS32);

		  do {
			  Integer32 const	*in;

			  in = (Integer32 const *)*_hoops_HCHIH++ + hoffset;
			  _hoops_SCGCR = _hoops_GAAC;
			  _hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

			  do {
				  unsigned char	_hoops_CGRAH = (*in >> 24) & 0x00FF;

				  _hoops_SCGCR->r = _hoops_CGRAH;
				  _hoops_SCGCR->g = _hoops_CGRAH;
				  _hoops_SCGCR->b = _hoops_CGRAH;
				  _hoops_SCGCR->a = _hoops_GPGCR;
				  ++in;
			  } _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

			  _hoops_ARCGH (nr, &start, &end, 0, _hoops_GAAC);

			  end.y = --start.y;
		  } _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
	  }	  break; 

	  case _hoops_PCCRH: {
		  ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, RGBAS32);

		  do {
			  float const	*in;

			  in = (float const *)*_hoops_HCHIH++ + hoffset;
			  _hoops_SCGCR = _hoops_GAAC;
			  _hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

			  do {
				  unsigned char	_hoops_CGRAH = ((int)(*in/MAX_FLOAT*256.0)) & 0x00FF;

				  _hoops_SCGCR->r = _hoops_CGRAH;
				  _hoops_SCGCR->g = _hoops_CGRAH;
				  _hoops_SCGCR->b = _hoops_CGRAH;
				  _hoops_SCGCR->a = _hoops_GPGCR;
				  ++in;
			  } _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

			  _hoops_ARCGH (nr, &start, &end, 0, _hoops_GAAC);

			  end.y = --start.y;
		  } _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
	  }	  break; 


#ifndef DISABLE_NON_RGB_IMAGES
#ifndef DISABLE_COLOR_MAPS
	  case Image_MAPPED_16: {
		  Driver_Color const	*_hoops_SPRAR;

		  _hoops_SPRAR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_AHHHP;
		  ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, RGBAS32);

		  do {
			  unsigned short const	*in;

			  in = (unsigned short const *)*_hoops_HCHIH++ + hoffset;
			  _hoops_SCGCR = _hoops_GAAC;
			  _hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

			  do {
				  Driver_Color const	*_hoops_CPHHP;

				  _hoops_CPHHP = _hoops_SPRAR + *in++;
				  *_hoops_SCGCR = *_hoops_CPHHP;
			  } _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

			  _hoops_ARCGH (nr, &start, &end, 0, _hoops_GAAC);

			  end.y = --start.y;
		  } _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
	  }	  break;

	  case Image_MAPPED_8: {
		  Driver_Color const	*_hoops_SPRAR;

		  _hoops_SPRAR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_AHHHP;
		  ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, RGBAS32);

		  do {
			  unsigned char const *in;

			  in = (unsigned char const *)*_hoops_HCHIH++ + hoffset;
			  _hoops_SCGCR = _hoops_GAAC;
			  _hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

			  do {
				  Driver_Color const	*_hoops_CPHHP;

				  _hoops_CPHHP = _hoops_SPRAR + _hoops_IRGCR (*in++);
				  *_hoops_SCGCR = *_hoops_CPHHP;
			  } _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

			  _hoops_ARCGH (nr, &start, &end, 0, _hoops_GAAC);

			  end.y = --start.y;
		  } _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
	  }	  break; 
#endif
#endif

	  case _hoops_HHGH: {
		  ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, RGBAS32);

		  do {
			  _hoops_SHGH const *in;

			  in = (_hoops_SHGH const *)*_hoops_HCHIH++ + hoffset;
			  _hoops_SCGCR = _hoops_GAAC;
			  _hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

			  do {
				  _hoops_SCGCR->r = in->r;
				  _hoops_SCGCR->g = in->g;
				  _hoops_SCGCR->b = in->b;
				  _hoops_SCGCR->a = _hoops_GPGCR;
				  ++in;
			  } _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

			  _hoops_ARCGH (nr, &start, &end, 0, _hoops_GAAC);

			  end.y = --start.y;
		  } _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
	  }	  break; 


	case _hoops_HRSRH:
	case Image_RGBA32:{
		  ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, RGBAS32);

		  do {
			  unsigned char const *	in;
			  unsigned char const *	_hoops_RCRPI;
			  int					_hoops_CIRPI = _hoops_SIRPI;
			  RGBAS32				pixel = _hoops_CAHSR::_hoops_SAHSR;

			  in = (unsigned char const *)*_hoops_HCHIH++ + 4*hoffset;
			  _hoops_RCRPI = in + 4*_hoops_PARSP;

			  if (format == _hoops_HRSRH) pixel.a = *in++;
			  pixel.r = *in++;
			  pixel.g = *in++;
			  pixel.b = *in++;
			  if (format == Image_RGBA32) pixel.a = *in++;

			  _hoops_RGGA (in == _hoops_RCRPI) {
				  _hoops_RGGA (in == _hoops_RCRPI || pixel.a != 0) {
					  ++_hoops_CIRPI;

					  if (format == _hoops_HRSRH) pixel.a = *in++;
					  pixel.r = *in++;
					  pixel.g = *in++;
					  pixel.b = *in++;
					  if (format == Image_RGBA32) pixel.a = *in++;
				  }

				  if (in == _hoops_RCRPI) break;
				  _hoops_SCGCR = _hoops_GAAC;

				  do {
					  *_hoops_SCGCR++ = pixel;

					  if (in == _hoops_RCRPI) break;

					  if (format == _hoops_HRSRH) pixel.a = *in++;
					  pixel.r = *in++;
					  pixel.g = *in++;
					  pixel.b = *in++;
					  if (format == Image_RGBA32) pixel.a = *in++;
				  } while (pixel.a != 0);

				  start.x = _hoops_HCGCR->x + _hoops_CIRPI;
				  end.x = start.x + (_hoops_SCGCR - _hoops_GAAC) - 1;

				  _hoops_ARCGH (nr, &start, &end, 0, _hoops_GAAC);

				  _hoops_CIRPI += _hoops_SCGCR - _hoops_GAAC;
			  }
			  end.y = --start.y;
		  } _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
	  }	  break; 

	  case _hoops_AHGH: {
		  ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, RGBAS32);

		  do {
			  unsigned char const *in;

			  in = (unsigned char const *)*_hoops_HCHIH++ + hoffset;
			  _hoops_SCGCR = _hoops_GAAC;
			  _hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

			  do {
				  _hoops_SCGCR->r = *in;
				  _hoops_SCGCR->g = *in;
				  _hoops_SCGCR->b = *in;
				  _hoops_SCGCR->a = _hoops_GPGCR;
				  ++in;
			  } _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

			  _hoops_ARCGH (nr, &start, &end, 0, _hoops_GAAC);

			  end.y = --start.y;
		  } _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
	}	  break; 

	default:
		ASSERT(0);
	}

	if (_hoops_GAAC != null) FREE_ARRAY (_hoops_GAAC, _hoops_PARSP, RGBAS32);
}
#if _MSC_VER >= 1300
#pragma optimize("", on)
#endif




#ifndef DISABLE_BIT_RASTERS

local void _hoops_PCRPI (
	Net_Rendition const &		nr,
	DC_Point const *			_hoops_HCGCR,
	DC_Point const *			_hoops_ICGCR,
	unsigned char alter *		_hoops_GAAC,
	int							pattern,
	Driver_Color const *		contrast_color) {
	Display_Context const *		dc = nr->_hoops_SRA;
	int							row;
	int							col;
	int							bit;
	unsigned char alter *		_hoops_SCGCR;
	unsigned char alter *		_hoops_HSGCR;
	int							_hoops_APARH;

	UNREFERENCED (contrast_color);

	if (pattern != FP_USER_DEFINED) {
		int						_hoops_RIRPI;
		int const				*_hoops_AIRPI;

		row = (int)_hoops_HCGCR->y & (dc->_hoops_ASPGH-1);
		if (dc->_hoops_CCAGH)
			row = dc->_hoops_ASPGH - 1 - row;
		col = (int)_hoops_HCGCR->x & (dc->_hoops_ASPGH-1);

		if (dc->_hoops_ASPGH == 4) {
			_hoops_RIRPI = ((unsigned char const *)(dc->_hoops_GRPH[pattern]))[row];
			_hoops_AIRPI = HOOPS_READ_ONLY.incr_mod_4;
		}
		else if (dc->_hoops_ASPGH == 8) {
			_hoops_RIRPI = ((unsigned char const *)(dc->_hoops_GRPH[pattern]))[row];
			_hoops_AIRPI = HOOPS_READ_ONLY._hoops_PCHGI;
		}
		else if (dc->_hoops_ASPGH == 16) {
			_hoops_RIRPI = ((unsigned short const *)(dc->_hoops_GRPH[pattern]))[row];
			_hoops_AIRPI = HOOPS_READ_ONLY._hoops_HCHGI;
		}
		else {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Bit patterns have not been loaded.");
			return;
		}

		_hoops_SCGCR = _hoops_GAAC;
		_hoops_HSGCR = _hoops_SCGCR + ((int)_hoops_ICGCR->x - (int)_hoops_HCGCR->x + 1) / 8;
		_hoops_APARH = ((int)_hoops_ICGCR->x - (int)_hoops_HCGCR->x + 1) % 8;

		do {
			for (bit = 0; bit < 8; ++bit) {
				if (BIT (_hoops_RIRPI, HOOPS_READ_ONLY._hoops_ICHGI[col]))
					*_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
				col = _hoops_AIRPI[col];
			}
		} _hoops_RGGA (_hoops_SCGCR++ == _hoops_HSGCR);

		if (_hoops_APARH) do {
			for (bit = 0; bit < 8; ++bit) {
				if (BIT (_hoops_RIRPI, HOOPS_READ_ONLY._hoops_ICHGI[col]))
					*_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
				col = _hoops_AIRPI[col];
			}
		} _hoops_RGGA (--_hoops_APARH == 0);

		_hoops_CGCGH (nr, _hoops_HCGCR, _hoops_ICGCR, 0, _hoops_GAAC);
	}
	else {
		unsigned char const *		_hoops_RIRPI;
		_hoops_SIHHP const *	up = nr->_hoops_IHA->_hoops_PGPH;

		if (up == null) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "User-defined pattern requested but not defined");
			return;
		}

		row = (int)_hoops_HCGCR->y % up->height;
		if (up->_hoops_RCHHP)
			row = up->height - 1 - row;
		col = (int)_hoops_HCGCR->x % up->width;

		_hoops_RIRPI = &up->pattern[row * up->width];

		_hoops_SCGCR = _hoops_GAAC;
		_hoops_HSGCR = _hoops_SCGCR + ((int)_hoops_ICGCR->x - (int)_hoops_HCGCR->x + 1) / 8;
		_hoops_APARH = ((int)_hoops_ICGCR->x - (int)_hoops_HCGCR->x + 1) % 8;

		do {
			for (bit = 0; bit < 8; ++bit) {
				if (_hoops_RIRPI[col])
					*_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
				++col;
				if (col == up->width) col = 0;
			}
		} _hoops_RGGA (_hoops_SCGCR++ == _hoops_HSGCR);

		if (_hoops_APARH) do {
			for (bit = 0; bit < 8; ++bit) {
				if (_hoops_RIRPI[col])
					*_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
				++col;
				if (col == up->width) col = 0;
			}
		} _hoops_RGGA (--_hoops_APARH == 0);

		_hoops_CGCGH (nr, _hoops_HCGCR, _hoops_ICGCR, 0, _hoops_GAAC);
	}
}
#endif


#define _hoops_PCGCR(x)			_hoops_IRGCR(x)

GLOBAL_FUNCTION void HD_Image_To_Bit_Rasters (
	Net_Rendition const &		nr,
	DC_Point const *			_hoops_HCGCR,
	DC_Point const *			_hoops_ICGCR,
	int							hoffset,
	Image_Format				format,
	int							row_bytes,
	void const * const *		_hoops_HCHIH,
	int							pattern,
	Driver_Color const *		contrast_color,
	Image const *				db_image) {
#ifndef DISABLE_BIT_RASTERS
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	_hoops_ISHHP const &	_hoops_CSHHP = nr->_hoops_ASIR;
	DC_Point					start, end;
	unsigned char alter *		_hoops_GAAC;
	int							bit;
	unsigned char alter *		_hoops_SCGCR;
	unsigned char alter *		_hoops_HSGCR;
	int							_hoops_PARSP = (int)(_hoops_ICGCR->x - _hoops_HCGCR->x) + 1;
	int							vcount = (int)(_hoops_HCGCR->y - _hoops_ICGCR->y) + 1;
	int							_hoops_SIRPI = 0;
	int							_hoops_HCRPI = _hoops_PARSP / 8;
	int							_hoops_ICRPI = _hoops_PARSP % 8;
	Quantization_Flags			mode = _hoops_RRGH->_hoops_SIRAP;
	_hoops_CRRRH					color;
	_hoops_SGGCR					_hoops_CCRPI;

	UNREFERENCED(row_bytes);
	UNREFERENCED(db_image);


	start.x = _hoops_HCGCR->x;
	start.y = _hoops_HCGCR->y;
	start.z = _hoops_HCGCR->z;

	end.x = _hoops_ICGCR->x;
	end.y = _hoops_ICGCR->y;
	end.z = _hoops_ICGCR->z;

	Int_Rectangle const & _hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

	if (_hoops_GPHH.left > start.x) {
		if (_hoops_GPHH.left > end.x)
			return;
		int delta = _hoops_GPHH.left - start.x;
		_hoops_SIRPI += delta;
		_hoops_PARSP -= delta;
		start.x = _hoops_GPHH.left;
	}
	if (_hoops_GPHH.right < end.x) {
		if (_hoops_GPHH.right < start.x)
			return;
		int delta = end.x - _hoops_GPHH.right;
		_hoops_PARSP -= delta;
		end.x = _hoops_GPHH.right;
	}
	if (_hoops_GPHH.bottom > end.y) {
		if (_hoops_GPHH.bottom > start.y)
			return;
		int delta = _hoops_GPHH.bottom - end.y;
		vcount -= delta;
		//_hoops_RSGR._hoops_HAPC = _hoops_HSPH._hoops_PRPC;
	}
	if (_hoops_GPHH.top < start.y) {
		if (_hoops_GPHH.top < end.y)
			return;
		int delta = start.y - _hoops_GPHH.top;
		vcount -= delta;
		_hoops_HCHIH += delta;
		start.y = _hoops_GPHH.top;
	}

	end.y = start.y;

	/* _hoops_RPP "/8" == _hoops_GGHSP(_hoops_IGRH) */
	ALLOC_ARRAY (_hoops_GAAC, (_hoops_PARSP + 7) / 8, unsigned char);

	_hoops_CCRPI.r = (int)(0x00010000 * _hoops_RRASP);
	_hoops_CCRPI.g = 0x00008000;		/* (_hoops_SCSH)(0x00010000 * _hoops_SCRPI) */
	_hoops_CCRPI.b = (int)(0x00010000 * _hoops_HRASP);

	switch (format) {
		case _hoops_GGRH:
		case _hoops_RGRH:
		case _hoops_AGRH:
		case _hoops_IRRH:
		case _hoops_CRRH:
		case _hoops_SRRH:
		case _hoops_AHGH:
			ASSERT(0);  //_hoops_GSRPI _hoops_SR _hoops_PAH _hoops_AA _hoops_ARI?
			break;

		case Image_MAPPED_16: {
			unsigned short const *	in;
			Driver_Color const *	_hoops_SPRAR;
			int						_hoops_HGII;

			_hoops_SPRAR = _hoops_CSHHP->_hoops_PSIR->_hoops_AHHHP;
			_hoops_HGII = dc->_hoops_PGCC._hoops_PCHSR - 1;

			switch (mode) {
			  case Quantization_DITHER: {
				  do {
					  int				row;
					  int				col;
					  const		unsigned short	*_hoops_IHGCR;

					  in = (unsigned short const *)*_hoops_HCHIH++ + hoffset;

					  row = (int)start.y & 7;
					  col = (int)start.x & 7;
					  _hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row];

					  _hoops_SCGCR = _hoops_GAAC;
					  _hoops_HSGCR = _hoops_SCGCR + _hoops_HCRPI;

					  _hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR) {
						  *_hoops_SCGCR = 0;
						  for (bit = 0; bit < 8; ++bit) {
							  color.number = (0x00010000 * _hoops_PCGCR(_hoops_SPRAR[*in]._hoops_PIHHP)) / _hoops_HGII +
											 _hoops_IHGCR[col];
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  col = HOOPS_READ_ONLY._hoops_PCHGI[col];
							  ++in;
						  }
						  ++_hoops_SCGCR;
					  }

					  if (_hoops_ICRPI != 0) {
						  *_hoops_SCGCR = 0;
						  for (bit = 0; bit < _hoops_ICRPI; ++bit) {
							  color.number = (0x00010000 * _hoops_PCGCR(_hoops_SPRAR[*in]._hoops_PIHHP)) / _hoops_HGII +
											 _hoops_IHGCR[col];
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  col = HOOPS_READ_ONLY._hoops_PCHGI[col];
							  ++in;
						  }
					  }

					  if (pattern == FP_SOLID)
						  _hoops_CGCGH (nr, &start, &end, 0, _hoops_GAAC);
					  else
						  _hoops_PCRPI (nr, &start, &end, _hoops_GAAC,
										pattern, contrast_color);

					  end.y = --start.y;
				  } _hoops_RGGA (--vcount == 0 ||
						   _hoops_GGPGR(nr));
			  }	  break; /* _hoops_RSRPI */

			  case Quantization_THRESHOLD: {
				  do {
					  in = (unsigned short const *)*_hoops_HCHIH++ + hoffset;
					  _hoops_SCGCR = _hoops_GAAC;
					  _hoops_HSGCR = _hoops_SCGCR + _hoops_HCRPI;

					  do {
						  *_hoops_SCGCR = 0;
						  for (bit = 0; bit < 8; ++bit) {
							  color.number = (0x00010000 * _hoops_PCGCR(_hoops_SPRAR[*in]._hoops_PIHHP)) / _hoops_HGII +
											 0x8000;
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  ++in;
						  }
					  } _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					  if (_hoops_ICRPI != 0) {
						  *_hoops_SCGCR = 0;
						  for (bit = 0; bit < _hoops_ICRPI; ++bit) {
							  color.number = (0x00010000 * _hoops_PCGCR(_hoops_SPRAR[*in]._hoops_PIHHP)) / _hoops_HGII +
											 0x8000;
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  ++in;
						  }
					  }

					  if (pattern == FP_SOLID)
						  _hoops_CGCGH (nr, &start, &end, 0, _hoops_GAAC);
					  else
						  _hoops_PCRPI (nr, &start, &end, _hoops_GAAC,
										pattern, contrast_color);

					  end.y = --start.y;
				  } _hoops_RGGA (--vcount == 0 ||
						   _hoops_GGPGR(nr));
			  }	  break; /* _hoops_ASRPI */

			  case Quantization_ERROR_DIFFUSION: {
				  Integer32 alter *_hoops_PSRPI[2];
				  int				row = 0;

				  ALLOC_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, Integer32);
				  ALLOC_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, Integer32);

				  {
					  int				_hoops_ICRHH;
					  for (_hoops_ICRHH = 0; _hoops_ICRHH < _hoops_PARSP + 2; ++_hoops_ICRHH)
						  _hoops_PSRPI[0][_hoops_ICRHH] = _hoops_PSRPI[1][_hoops_ICRHH] = 0;
				  }

				  do {
					  Integer32 alter *_hoops_HSRPI,
														*_hoops_ISRPI;
					  Integer32 alter *_hoops_CSRPI,
														*_hoops_SSRPI,
														*_hoops_GGAPI;

					  in = (unsigned short const *)*_hoops_HCHIH++ + hoffset;
					  _hoops_SCGCR = _hoops_GAAC;
					  _hoops_HSGCR = _hoops_SCGCR + _hoops_HCRPI;

					  _hoops_HSRPI = &_hoops_PSRPI[row][0];
					  _hoops_ISRPI = &_hoops_PSRPI[row][1];
					  row = 1-row;
					  _hoops_CSRPI = &_hoops_PSRPI[row][0];
					  _hoops_SSRPI = &_hoops_PSRPI[row][1];
					  _hoops_GGAPI = &_hoops_PSRPI[row][2];

					  do {
						  *_hoops_SCGCR = 0;
						  for (bit = 0; bit < 8; ++bit) {
							  color.number = (0x00010000 * _hoops_PCGCR(_hoops_SPRAR[*in]._hoops_PIHHP)) / _hoops_HGII +
											 (*_hoops_HSRPI * 7 + *_hoops_GGAPI * 3 + *_hoops_SSRPI * 5 + *_hoops_CSRPI) / 16;
							  if (color.number < 0)
								  color.number = 0;
							  else if (color.number > 0x00010000)
								  color.number = 0x00010000;
							  *_hoops_ISRPI = color.number;
							  color.number += 0x8000;
							  color._hoops_CAGCR._hoops_RCGCR = 0;
							  *_hoops_ISRPI -= color.number;
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  ++in;
							  _hoops_HSRPI = _hoops_ISRPI++;
							  _hoops_CSRPI = _hoops_SSRPI;
							  _hoops_SSRPI = _hoops_GGAPI++;
						  }
					  } _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					  if (_hoops_ICRPI != 0) {
						  *_hoops_SCGCR = 0;
						  for (bit = 0; bit < _hoops_ICRPI; ++bit) {
							  color.number = (0x00010000 * _hoops_PCGCR(_hoops_SPRAR[*in]._hoops_PIHHP)) / _hoops_HGII +
											 (*_hoops_HSRPI * 7 + *_hoops_GGAPI * 3 + *_hoops_SSRPI * 5 + *_hoops_CSRPI) / 16;
							  if (color.number < 0)
								  color.number = 0;
							  else if (color.number > 0x00010000)
								  color.number = 0x00010000;
							  *_hoops_ISRPI = color.number;
							  color.number += 0x8000;
							  color._hoops_CAGCR._hoops_RCGCR = 0;
							  *_hoops_ISRPI -= color.number;
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  ++in;
							  _hoops_HSRPI = _hoops_ISRPI++;
							  _hoops_CSRPI = _hoops_SSRPI;
							  _hoops_SSRPI = _hoops_GGAPI++;
						  }
					  }

					  if (pattern == FP_SOLID)
						  _hoops_CGCGH (nr, &start, &end, 0, _hoops_GAAC);
					  else
						  _hoops_PCRPI (nr, &start, &end, _hoops_GAAC,
										pattern, contrast_color);

					  end.y = --start.y;
				  } _hoops_RGGA (--vcount == 0 ||
						   _hoops_GGPGR(nr));

				  FREE_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, Integer32);
				  FREE_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, Integer32);
			  }	  break; /* _hoops_RGAPI */
			} /* _hoops_RSGR _hoops_IIGR _hoops_CICA (_hoops_CCH) */
		}	break; /* _hoops_PPCC */

		case Image_MAPPED_8: {
			unsigned char const		*in;
			Driver_Color const	*_hoops_SPRAR;
			int						_hoops_HGII;

			_hoops_SPRAR = _hoops_CSHHP->_hoops_PSIR->_hoops_AHHHP;
			_hoops_HGII = dc->_hoops_PGCC._hoops_PCHSR - 1;

			switch (mode) {
			  case Quantization_DITHER: {
				  do {
					  int				row;
					  int				col;
					  const		unsigned short	*_hoops_IHGCR;

					  in = (unsigned char const *)*_hoops_HCHIH++ + hoffset;

					  row = (int)start.y & 7;
					  col = (int)start.x & 7;
					  _hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row];

					  _hoops_SCGCR = _hoops_GAAC;
					  _hoops_HSGCR = _hoops_SCGCR + _hoops_HCRPI;

					  _hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR) {
						  *_hoops_SCGCR = 0;
						  for (bit = 0; bit < 8; ++bit) {
							  color.number = (0x00010000 * _hoops_PCGCR(_hoops_SPRAR[*in]._hoops_PIHHP)) / _hoops_HGII +
											 _hoops_IHGCR[col];
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  col = HOOPS_READ_ONLY._hoops_PCHGI[col];
							  ++in;
						  }
						  ++_hoops_SCGCR;
					  }

					  if (_hoops_ICRPI != 0) {
						  *_hoops_SCGCR = 0;
						  for (bit = 0; bit < _hoops_ICRPI; ++bit) {
							  color.number = (0x00010000 * _hoops_PCGCR(_hoops_SPRAR[*in]._hoops_PIHHP)) / _hoops_HGII +
											 _hoops_IHGCR[col];
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  col = HOOPS_READ_ONLY._hoops_PCHGI[col];
							  ++in;
						  }
					  }

					  if (pattern == FP_SOLID)
						  _hoops_CGCGH (nr, &start, &end, 0, _hoops_GAAC);
					  else
						  _hoops_PCRPI (nr, &start, &end, _hoops_GAAC,
										pattern, contrast_color);

					  end.y = --start.y;
				  } _hoops_RGGA (--vcount == 0 ||
						   _hoops_GGPGR(nr));
			  }	  break; /* _hoops_RSRPI */

			  case Quantization_THRESHOLD: {
				  do {
					  in = (unsigned char const *)*_hoops_HCHIH++ + hoffset;
					  _hoops_SCGCR = _hoops_GAAC;
					  _hoops_HSGCR = _hoops_SCGCR + _hoops_HCRPI;

					  do {
						  *_hoops_SCGCR = 0;
						  for (bit = 0; bit < 8; ++bit) {
							  color.number = (0x00010000 * _hoops_PCGCR(_hoops_SPRAR[*in]._hoops_PIHHP)) / _hoops_HGII +
											 0x8000;
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  ++in;
						  }
					  } _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					  if (_hoops_ICRPI != 0) {
						  *_hoops_SCGCR = 0;
						  for (bit = 0; bit < _hoops_ICRPI; ++bit) {
							  color.number = (0x00010000 * _hoops_PCGCR(_hoops_SPRAR[*in]._hoops_PIHHP)) / _hoops_HGII +
											 0x8000;
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  ++in;
						  }
					  }

					  if (pattern == FP_SOLID)
						  _hoops_CGCGH (nr, &start, &end, 0, _hoops_GAAC);
					  else
						  _hoops_PCRPI (nr, &start, &end, _hoops_GAAC,
										pattern, contrast_color);

					  end.y = --start.y;
				  } _hoops_RGGA (--vcount == 0 ||
						   _hoops_GGPGR(nr));
			  }	  break; /* _hoops_ASRPI */

			  case Quantization_ERROR_DIFFUSION: {
				  Integer32 alter *_hoops_PSRPI[2];
				  int				row = 0;

				  ALLOC_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, Integer32);
				  ALLOC_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, Integer32);

				  {
					  int				_hoops_ICRHH;
					  for (_hoops_ICRHH = 0; _hoops_ICRHH < _hoops_PARSP + 2; ++_hoops_ICRHH)
						  _hoops_PSRPI[0][_hoops_ICRHH] = _hoops_PSRPI[1][_hoops_ICRHH] = 0;
				  }

				  do {
					  Integer32 alter *_hoops_HSRPI,
														*_hoops_ISRPI;
					  Integer32 alter *_hoops_CSRPI,
														*_hoops_SSRPI,
														*_hoops_GGAPI;

					  in = (unsigned char const *)*_hoops_HCHIH++ + hoffset;
					  _hoops_SCGCR = _hoops_GAAC;
					  _hoops_HSGCR = _hoops_SCGCR + _hoops_HCRPI;

					  _hoops_HSRPI = &_hoops_PSRPI[row][0];
					  _hoops_ISRPI = &_hoops_PSRPI[row][1];
					  row = 1-row;
					  _hoops_CSRPI = &_hoops_PSRPI[row][0];
					  _hoops_SSRPI = &_hoops_PSRPI[row][1];
					  _hoops_GGAPI = &_hoops_PSRPI[row][2];

					  do {
						  *_hoops_SCGCR = 0;
						  for (bit = 0; bit < 8; ++bit) {
							  color.number = (0x00010000 * _hoops_PCGCR(_hoops_SPRAR[*in]._hoops_PIHHP)) / _hoops_HGII +
											 (*_hoops_HSRPI * 7 + *_hoops_GGAPI * 3 + *_hoops_SSRPI * 5 + *_hoops_CSRPI) / 16;
							  if (color.number < 0)
								  color.number = 0;
							  else if (color.number > 0x00010000)
								  color.number = 0x00010000;
							  *_hoops_ISRPI = color.number;
							  color.number += 0x8000;
							  color._hoops_CAGCR._hoops_RCGCR = 0;
							  *_hoops_ISRPI -= color.number;
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  ++in;
							  _hoops_HSRPI = _hoops_ISRPI++;
							  _hoops_CSRPI = _hoops_SSRPI;
							  _hoops_SSRPI = _hoops_GGAPI++;
						  }
					  } _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					  if (_hoops_ICRPI != 0) {
						  *_hoops_SCGCR = 0;
						  for (bit = 0; bit < _hoops_ICRPI; ++bit) {
							  color.number = (0x00010000 * _hoops_PCGCR(_hoops_SPRAR[*in]._hoops_PIHHP)) / _hoops_HGII +
											 (*_hoops_HSRPI * 7 + *_hoops_GGAPI * 3 + *_hoops_SSRPI * 5 + *_hoops_CSRPI) / 16;
							  if (color.number < 0)
								  color.number = 0;
							  else if (color.number > 0x00010000)
								  color.number = 0x00010000;
							  *_hoops_ISRPI = color.number;
							  color.number += 0x8000;
							  color._hoops_CAGCR._hoops_RCGCR = 0;
							  *_hoops_ISRPI -= color.number;
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  ++in;
							  _hoops_HSRPI = _hoops_ISRPI++;
							  _hoops_CSRPI = _hoops_SSRPI;
							  _hoops_SSRPI = _hoops_GGAPI++;
						  }
					  }

					  if (pattern == FP_SOLID)
						  _hoops_CGCGH (nr, &start, &end, 0, _hoops_GAAC);
					  else
						  _hoops_PCRPI (nr, &start, &end, _hoops_GAAC,
										pattern, contrast_color);

					  end.y = --start.y;
				  } _hoops_RGGA (--vcount == 0 ||
						   _hoops_GGPGR(nr));

				  FREE_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, Integer32);
				  FREE_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, Integer32);
			  }	  break; /* _hoops_RGAPI */
			} /* _hoops_RSGR _hoops_IIGR _hoops_CICA (_hoops_CCH) */
		}	break; /* _hoops_APCC */

		case _hoops_HHGH: {
			_hoops_SHGH const *in;

			switch (mode) {
			  case Quantization_DITHER: {
				  do {
					  int				row;
					  int				col;
					  const		unsigned short	*_hoops_IHGCR;

					  in = (_hoops_SHGH const *)*_hoops_HCHIH++ + hoffset;

					  row = (int)start.y & 7;
					  col = (int)start.x & 7;
					  _hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row];

					  _hoops_SCGCR = _hoops_GAAC;
					  _hoops_HSGCR = _hoops_SCGCR + _hoops_HCRPI;

					  _hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR) {
						  *_hoops_SCGCR = 0;
						  for (bit = 0; bit < 8; ++bit) {
							  color.number = (_hoops_CCRPI.r * _hoops_PCGCR(in->r) +
											  _hoops_CCRPI.g * _hoops_PCGCR(in->g) +
											  _hoops_CCRPI.b * _hoops_PCGCR(in->b)) / 255 +
											 _hoops_IHGCR[col];
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  col = HOOPS_READ_ONLY._hoops_PCHGI[col];
							  ++in;
						  }
						  ++_hoops_SCGCR;
					  }

					  if (_hoops_ICRPI != 0) {
						  *_hoops_SCGCR = 0;
						  for (bit = 0; bit < _hoops_ICRPI; ++bit) {
							  color.number = (_hoops_CCRPI.r * _hoops_PCGCR(in->r) +
											  _hoops_CCRPI.g * _hoops_PCGCR(in->g) +
											  _hoops_CCRPI.b * _hoops_PCGCR(in->b)) / 255 +
											 _hoops_IHGCR[col];
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  col = HOOPS_READ_ONLY._hoops_PCHGI[col];
							  ++in;
						  }
					  }

					  if (pattern == FP_SOLID)
						  _hoops_CGCGH (nr, &start, &end, 0, _hoops_GAAC);
					  else
						  _hoops_PCRPI (nr, &start, &end, _hoops_GAAC,
										pattern, contrast_color);

					  end.y = --start.y;
				  } _hoops_RGGA (--vcount == 0 ||
						   _hoops_GGPGR(nr));
			  }	  break; /* _hoops_RSRPI */

			  case Quantization_THRESHOLD: {
				  do {
					  in = (_hoops_SHGH const *)*_hoops_HCHIH++ + hoffset;
					  _hoops_SCGCR = _hoops_GAAC;
					  _hoops_HSGCR = _hoops_SCGCR + _hoops_HCRPI;

					  do {
						  *_hoops_SCGCR = 0;
						  for (bit = 0; bit < 8; ++bit) {
							  color.number = (_hoops_CCRPI.r * _hoops_PCGCR(in->r) +
											  _hoops_CCRPI.g * _hoops_PCGCR(in->g) +
											  _hoops_CCRPI.b * _hoops_PCGCR(in->b)) / 255 +
											 0x8000;
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  ++in;
						  }
					  } _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					  if (_hoops_ICRPI != 0) {
						  *_hoops_SCGCR = 0;
						  for (bit = 0; bit < _hoops_ICRPI; ++bit) {
							  color.number = (_hoops_CCRPI.r * _hoops_PCGCR(in->r) +
											  _hoops_CCRPI.g * _hoops_PCGCR(in->g) +
											  _hoops_CCRPI.b * _hoops_PCGCR(in->b)) / 255 +
											 0x8000;
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  ++in;
						  }
					  }

					  if (pattern == FP_SOLID)
						  _hoops_CGCGH (nr, &start, &end, 0, _hoops_GAAC);
					  else
						  _hoops_PCRPI (nr, &start, &end, _hoops_GAAC,
										pattern, contrast_color);

					  end.y = --start.y;
				  } _hoops_RGGA (--vcount == 0 ||
						   _hoops_GGPGR(nr));
			  }	  break; /* _hoops_ASRPI */

			  case Quantization_ERROR_DIFFUSION: {
				  Integer32 alter *_hoops_PSRPI[2];
				  int				row = 0;

				  ALLOC_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, Integer32);
				  ALLOC_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, Integer32);

				  {
					  int				_hoops_ICRHH;
					  for (_hoops_ICRHH = 0; _hoops_ICRHH < _hoops_PARSP + 2; ++_hoops_ICRHH)
						  _hoops_PSRPI[0][_hoops_ICRHH] = _hoops_PSRPI[1][_hoops_ICRHH] = 0;
				  }

				  do {
					  Integer32 alter *_hoops_HSRPI,
														*_hoops_ISRPI;
					  Integer32 alter *_hoops_CSRPI,
														*_hoops_SSRPI,
														*_hoops_GGAPI;

					  in = (_hoops_SHGH const *)*_hoops_HCHIH++ + hoffset;
					  _hoops_SCGCR = _hoops_GAAC;
					  _hoops_HSGCR = _hoops_SCGCR + _hoops_HCRPI;

					  _hoops_HSRPI = &_hoops_PSRPI[row][0];
					  _hoops_ISRPI = &_hoops_PSRPI[row][1];
					  row = 1-row;
					  _hoops_CSRPI = &_hoops_PSRPI[row][0];
					  _hoops_SSRPI = &_hoops_PSRPI[row][1];
					  _hoops_GGAPI = &_hoops_PSRPI[row][2];

					  do {
						  *_hoops_SCGCR = 0;
						  for (bit = 0; bit < 8; ++bit) {
							  color.number = (_hoops_CCRPI.r * _hoops_PCGCR(in->r) +
											  _hoops_CCRPI.g * _hoops_PCGCR(in->g) +
											  _hoops_CCRPI.b * _hoops_PCGCR(in->b)) / 255 +
											 (*_hoops_HSRPI * 7 + *_hoops_GGAPI * 3 + *_hoops_SSRPI * 5 + *_hoops_CSRPI) / 16;
							  if (color.number < 0)
								  color.number = 0;
							  else if (color.number > 0x00010000)
								  color.number = 0x00010000;
							  *_hoops_ISRPI = color.number;
							  color.number += 0x8000;
							  color._hoops_CAGCR._hoops_RCGCR = 0;
							  *_hoops_ISRPI -= color.number;
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  ++in;
							  _hoops_HSRPI = _hoops_ISRPI++;
							  _hoops_CSRPI = _hoops_SSRPI;
							  _hoops_SSRPI = _hoops_GGAPI++;
						  }
					  } _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					  if (_hoops_ICRPI != 0) {
						  *_hoops_SCGCR = 0;
						  for (bit = 0; bit < _hoops_ICRPI; ++bit) {
							  color.number = (_hoops_CCRPI.r * _hoops_PCGCR(in->r) +
											  _hoops_CCRPI.g * _hoops_PCGCR(in->g) +
											  _hoops_CCRPI.b * _hoops_PCGCR(in->b)) / 255 +
											 (*_hoops_HSRPI * 7 + *_hoops_GGAPI * 3 + *_hoops_SSRPI * 5 + *_hoops_CSRPI) / 16;
							  if (color.number < 0)
								  color.number = 0;
							  else if (color.number > 0x00010000)
								  color.number = 0x00010000;
							  *_hoops_ISRPI = color.number;
							  color.number += 0x8000;
							  color._hoops_CAGCR._hoops_RCGCR = 0;
							  *_hoops_ISRPI -= color.number;
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  ++in;
							  _hoops_HSRPI = _hoops_ISRPI++;
							  _hoops_CSRPI = _hoops_SSRPI;
							  _hoops_SSRPI = _hoops_GGAPI++;
						  }
					  }

					  if (pattern == FP_SOLID)
						  _hoops_CGCGH (nr, &start, &end, 0, _hoops_GAAC);
					  else
						  _hoops_PCRPI (nr, &start, &end, _hoops_GAAC,
										pattern, contrast_color);

					  end.y = --start.y;
				  } _hoops_RGGA (--vcount == 0 ||
						   _hoops_GGPGR(nr));

				  FREE_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, Integer32);
				  FREE_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, Integer32);
			  }	  break; /* _hoops_RGAPI */
			} /* _hoops_RSGR _hoops_IIGR _hoops_CICA (_hoops_CCH) */
		}	break; /* _hoops_AGAPI */

		case _hoops_CSGSP: {
			RGBAS32 const			*in;
			RGBAS32 const			*_hoops_RCRPI;

			switch (mode) {
			  case Quantization_DITHER: {
				  do {
					  int				_hoops_CIRPI = _hoops_SIRPI;
					  int				count;
					  int				row;
					  int				col;
					  const		unsigned short	*_hoops_IHGCR;

					  in = (RGBAS32 const *)*_hoops_HCHIH++ + hoffset;
					  _hoops_RCRPI = in + _hoops_PARSP;

					  row = (int)start.y & 7;
					  col = (int)start.x & 7;
					  _hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row];

					  _hoops_RGGA (in == _hoops_RCRPI) {
						  _hoops_RGGA (in == _hoops_RCRPI || in->a != 0) {
							  col = HOOPS_READ_ONLY._hoops_PCHGI[col];
							  ++_hoops_CIRPI;
							  ++in;
						  }

						  if (in == _hoops_RCRPI) break;

						  _hoops_SCGCR = _hoops_GAAC;
						  *_hoops_SCGCR = 0;
						  count = 0;

						  bit = 0;
						  _hoops_RGGA (in->a == 0) {
							  color.number = (_hoops_CCRPI.r * _hoops_PCGCR(in->r) +
											  _hoops_CCRPI.g * _hoops_PCGCR(in->g) +
											  _hoops_CCRPI.b * _hoops_PCGCR(in->b)) / 255 +
											 _hoops_IHGCR[col];
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  col = HOOPS_READ_ONLY._hoops_PCHGI[col];
							  ++count;
							  if (++in == _hoops_RCRPI) break;

							  if ((bit = HOOPS_READ_ONLY._hoops_PCHGI[bit]) == 0) *++_hoops_SCGCR = 0;
						  }

						  start.x = _hoops_HCGCR->x + _hoops_CIRPI;
						  end.x = start.x + count - 1;

						  if (pattern == FP_SOLID)
							  _hoops_CGCGH (nr, &start, &end, 0, _hoops_GAAC);
						  else
							  _hoops_PCRPI (nr, &start, &end, _hoops_GAAC,
											pattern, contrast_color);

						  _hoops_CIRPI += count;
					  }

					  end.y = --start.y;
				  } _hoops_RGGA (--vcount == 0 ||
						   _hoops_GGPGR(nr));
			  }	  break; /* _hoops_RSRPI */

			  case Quantization_THRESHOLD: {
				  do {
					  int						_hoops_CIRPI = _hoops_SIRPI;
					  int						count;

					  in = (RGBAS32 const *)*_hoops_HCHIH++ + hoffset;
					  _hoops_RCRPI = in + _hoops_PARSP;

					  _hoops_RGGA (in == _hoops_RCRPI) {
						  _hoops_RGGA (in == _hoops_RCRPI || in->a != 0) {
							  ++_hoops_CIRPI;
							  ++in;
						  }

						  if (in == _hoops_RCRPI) break;

						  _hoops_SCGCR = _hoops_GAAC;
						  *_hoops_SCGCR = 0;
						  count = 0;

						  bit = 0;
						  _hoops_RGGA (in->a == 0) {
							  color.number = (_hoops_CCRPI.r * _hoops_PCGCR(in->r) +
											  _hoops_CCRPI.g * _hoops_PCGCR(in->g) +
											  _hoops_CCRPI.b * _hoops_PCGCR(in->b)) / 255 +
											 0x8000;
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  ++count;
							  if (++in == _hoops_RCRPI) break;

							  if ((bit = HOOPS_READ_ONLY._hoops_PCHGI[bit]) == 0) *++_hoops_SCGCR = 0;
						  }

						  start.x = _hoops_HCGCR->x + _hoops_CIRPI;
						  end.x = start.x + count - 1;

						  if (pattern == FP_SOLID)
							  _hoops_CGCGH (nr, &start, &end, 0, _hoops_GAAC);
						  else
							  _hoops_PCRPI (nr, &start, &end, _hoops_GAAC,
											pattern, contrast_color);

						  _hoops_CIRPI += count;
					  }
					  end.y = --start.y;
				  } _hoops_RGGA (--vcount == 0 ||
						   _hoops_GGPGR(nr));
			  }	  break; /* _hoops_ASRPI */

			  case Quantization_ERROR_DIFFUSION: {
				  Integer32 alter *_hoops_PSRPI[2];
				  int				row = 0;

				  ALLOC_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, Integer32);
				  ALLOC_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, Integer32);

				  {
					  int				_hoops_ICRHH;
					  for (_hoops_ICRHH = 0; _hoops_ICRHH < _hoops_PARSP + 2; ++_hoops_ICRHH)
						  _hoops_PSRPI[0][_hoops_ICRHH] = _hoops_PSRPI[1][_hoops_ICRHH] = 0;
				  }

				  do {
					  Integer32 alter *_hoops_HSRPI,
												*_hoops_ISRPI;
					  Integer32 alter *_hoops_CSRPI,
												*_hoops_SSRPI,
												*_hoops_GGAPI;
					  int				_hoops_CIRPI = _hoops_SIRPI;
					  int				count = 0;

					  in = (RGBAS32 const *)*_hoops_HCHIH++ + hoffset;
					  _hoops_RCRPI = in + _hoops_PARSP;

					  _hoops_HSRPI = &_hoops_PSRPI[row][0];
					  _hoops_ISRPI = &_hoops_PSRPI[row][1];
					  row = 1-row;
					  _hoops_CSRPI = &_hoops_PSRPI[row][0];
					  _hoops_SSRPI = &_hoops_PSRPI[row][1];
					  _hoops_GGAPI = &_hoops_PSRPI[row][2];

					  _hoops_RGGA (in == _hoops_RCRPI) {
						  _hoops_RGGA (in == _hoops_RCRPI || in->a != 0) {
							  ++_hoops_CIRPI;
							  ++in;

							  *_hoops_ISRPI = 0;

							  _hoops_HSRPI = _hoops_ISRPI++;
							  _hoops_CSRPI = _hoops_SSRPI;
							  _hoops_SSRPI = _hoops_GGAPI++;
						  }

						  if (in == _hoops_RCRPI) break;

						  _hoops_SCGCR = _hoops_GAAC;
						  *_hoops_SCGCR = 0;

						  bit = 0;
						  _hoops_RGGA (in->a == 0) {
							  color.number = (_hoops_CCRPI.r * _hoops_PCGCR(in->r) +
											  _hoops_CCRPI.g * _hoops_PCGCR(in->g) +
											  _hoops_CCRPI.b * _hoops_PCGCR(in->b)) / 255 +
											 (*_hoops_HSRPI * 7 + *_hoops_GGAPI * 3 + *_hoops_SSRPI * 5 + *_hoops_CSRPI) / 16;
							  if (color.number < 0)
								  color.number = 0;
							  else if (color.number > 0x00010000)
								  color.number = 0x00010000;
							  *_hoops_ISRPI = color.number;
							  color.number += 0x8000;
							  color._hoops_CAGCR._hoops_RCGCR = 0;
							  *_hoops_ISRPI -= color.number;

							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];

							  ++count;
							  if (++in == _hoops_RCRPI) break;

							  if ((bit = HOOPS_READ_ONLY._hoops_PCHGI[bit]) == 0) *++_hoops_SCGCR = 0;

							  _hoops_HSRPI = _hoops_ISRPI++;
							  _hoops_CSRPI = _hoops_SSRPI;
							  _hoops_SSRPI = _hoops_GGAPI++;
						  }

						  start.x = _hoops_HCGCR->x + _hoops_CIRPI;
						  end.x = start.x + count - 1;

						  if (pattern == FP_SOLID)
							  _hoops_CGCGH (nr, &start, &end, 0, _hoops_GAAC);
						  else
							  _hoops_PCRPI (nr, &start, &end, _hoops_GAAC,
											pattern, contrast_color);

						  _hoops_CIRPI += count;
					  }
					  end.y = --start.y;
				  } _hoops_RGGA (--vcount == 0 ||
						   _hoops_GGPGR(nr));

				  FREE_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, Integer32);
				  FREE_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, Integer32);
			  }	  break; /* _hoops_RGAPI */
			} /* _hoops_RSGR _hoops_IIGR _hoops_CICA (_hoops_CCH) */
		}	break; /* _hoops_PGAPI */

		case Image_RGBA32: 
		case _hoops_HRSRH: {
			unsigned char const		*in;
			unsigned char const		*_hoops_RCRPI;

			switch (mode) {
			  case Quantization_DITHER: {
				  do {
					  int				_hoops_CIRPI = _hoops_SIRPI;
					  int				count;
					  int				row;
					  int				col;
					  const		unsigned short	*_hoops_IHGCR;
					  RGBAS32		pixel = _hoops_CAHSR::_hoops_SAHSR;
						
					  in = (unsigned char const *)*_hoops_HCHIH++ + 4*hoffset;
					  _hoops_RCRPI = in + 4*_hoops_PARSP;

					  row = (int)start.y & 7;
					  col = (int)start.x & 7;
					  _hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row];

					  if (format == _hoops_HRSRH) pixel.a = *in++;
					  pixel.r = *in++;
					  pixel.g = *in++;
					  pixel.b = *in++;
					  if (format == Image_RGBA32) pixel.a = *in++;

					  _hoops_RGGA (in == _hoops_RCRPI) {
						  _hoops_RGGA (in == _hoops_RCRPI || pixel.a != 0) {
							  col = HOOPS_READ_ONLY._hoops_PCHGI[col];
							  ++_hoops_CIRPI;

							  if (format == _hoops_HRSRH) pixel.a = *in++;
							  pixel.r = *in++;
							  pixel.g = *in++;
							  pixel.b = *in++;
							  if (format == Image_RGBA32) pixel.a = *in++;
						  }

						  if (in == _hoops_RCRPI) break;

						  _hoops_SCGCR = _hoops_GAAC;
						  *_hoops_SCGCR = 0;
						  count = 0;

						  bit = 0;
						  _hoops_RGGA (pixel.a == 0) {
							  color.number = (_hoops_CCRPI.r * _hoops_PCGCR(pixel.r) +
											  _hoops_CCRPI.g * _hoops_PCGCR(pixel.g) +
											  _hoops_CCRPI.b * _hoops_PCGCR(pixel.b)) / 255 +
											 _hoops_IHGCR[col];
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  col = HOOPS_READ_ONLY._hoops_PCHGI[col];
							  ++count;
							  if (in == _hoops_RCRPI) break;

							  if ((bit = HOOPS_READ_ONLY._hoops_PCHGI[bit]) == 0) *++_hoops_SCGCR = 0;

							  if (format == _hoops_HRSRH) pixel.a = *in++;
							  pixel.r = *in++;
							  pixel.g = *in++;
							  pixel.b = *in++;
							  if (format == Image_RGBA32) pixel.a = *in++;
						  }

						  start.x = _hoops_HCGCR->x + _hoops_CIRPI;
						  end.x = start.x + count - 1;

						  if (pattern == FP_SOLID)
							  _hoops_CGCGH (nr, &start, &end, 0, _hoops_GAAC);
						  else
							  _hoops_PCRPI (nr, &start, &end, _hoops_GAAC,
											pattern, contrast_color);

						  _hoops_CIRPI += count;
					  }

					  end.y = --start.y;
				  } _hoops_RGGA (--vcount == 0 ||
						   _hoops_GGPGR(nr));
			  }	  break; /* _hoops_RSRPI */

			  case Quantization_THRESHOLD: {
				  do {
					  int				_hoops_CIRPI = _hoops_SIRPI;
					  int				count;
					  RGBAS32			pixel = _hoops_CAHSR::_hoops_SAHSR;

					  in = (unsigned char const *)*_hoops_HCHIH++ + 4*hoffset;
					  _hoops_RCRPI = in + 4*_hoops_PARSP;

					  if (format == _hoops_HRSRH) pixel.a = *in++;
					  pixel.r = *in++;
					  pixel.g = *in++;
					  pixel.b = *in++;
					  if (format == Image_RGBA32) pixel.a = *in++;

					  _hoops_RGGA (in == _hoops_RCRPI) {
						  _hoops_RGGA (in == _hoops_RCRPI || pixel.a != 0) {
							  ++_hoops_CIRPI;

							  if (format == _hoops_HRSRH) pixel.a = *in++;
							  pixel.r = *in++;
							  pixel.g = *in++;
							  pixel.b = *in++;
							  if (format == Image_RGBA32) pixel.a = *in++;
						  }

						  if (in == _hoops_RCRPI) break;

						  _hoops_SCGCR = _hoops_GAAC;
						  *_hoops_SCGCR = 0;
						  count = 0;

						  bit = 0;
						  _hoops_RGGA (pixel.a == 0) {
							  color.number = (_hoops_CCRPI.r * _hoops_PCGCR(pixel.r) +
											  _hoops_CCRPI.g * _hoops_PCGCR(pixel.g) +
											  _hoops_CCRPI.b * _hoops_PCGCR(pixel.b)) / 255 +
											 0x8000;
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  ++count;

							  if (in == _hoops_RCRPI) break;
							  if ((bit = HOOPS_READ_ONLY._hoops_PCHGI[bit]) == 0) *++_hoops_SCGCR = 0;

							  if (format == _hoops_HRSRH) pixel.a = *in++;
							  pixel.r = *in++;
							  pixel.g = *in++;
							  pixel.b = *in++;
							  if (format == Image_RGBA32) pixel.a = *in++;
						  }

						  start.x = _hoops_HCGCR->x + _hoops_CIRPI;
						  end.x = start.x + count - 1;

						  if (pattern == FP_SOLID)
							  _hoops_CGCGH (nr, &start, &end, 0, _hoops_GAAC);
						  else
							  _hoops_PCRPI (nr, &start, &end, _hoops_GAAC,
											pattern, contrast_color);

						  _hoops_CIRPI += count;
					  }
					  end.y = --start.y;
				  } _hoops_RGGA (--vcount == 0 ||
						   _hoops_GGPGR(nr));
			  }	  break; /* _hoops_ASRPI */

			  case Quantization_ERROR_DIFFUSION: {
				  Integer32 alter *_hoops_PSRPI[2];
				  int				row = 0;

				  ALLOC_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, Integer32);
				  ALLOC_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, Integer32);

				  {
					  int				_hoops_ICRHH;

					  for (_hoops_ICRHH = 0; _hoops_ICRHH < _hoops_PARSP + 2; ++_hoops_ICRHH)
						  _hoops_PSRPI[0][_hoops_ICRHH] = _hoops_PSRPI[1][_hoops_ICRHH] = 0;
				  }

				  do {
					  Integer32 alter *_hoops_HSRPI,
												*_hoops_ISRPI;
					  Integer32 alter *_hoops_CSRPI,
												*_hoops_SSRPI,
												*_hoops_GGAPI;
					  int				_hoops_CIRPI = _hoops_SIRPI;
					  int				count = 0;
					  RGBAS32			pixel = _hoops_CAHSR::_hoops_SAHSR;

					  in = (unsigned char const *)*_hoops_HCHIH++ + 4*hoffset;
					  _hoops_RCRPI = in + 4*_hoops_PARSP;

					  _hoops_HSRPI = &_hoops_PSRPI[row][0];
					  _hoops_ISRPI = &_hoops_PSRPI[row][1];
					  row = 1-row;
					  _hoops_CSRPI = &_hoops_PSRPI[row][0];
					  _hoops_SSRPI = &_hoops_PSRPI[row][1];
					  _hoops_GGAPI = &_hoops_PSRPI[row][2];

					  if (format == _hoops_HRSRH) pixel.a = *in++;
					  pixel.r = *in++;
					  pixel.g = *in++;
					  pixel.b = *in++;
					  if (format == Image_RGBA32) pixel.a = *in++;

					  _hoops_RGGA (in == _hoops_RCRPI) {
						  _hoops_RGGA (in == _hoops_RCRPI || pixel.a != 0) {
							  ++_hoops_CIRPI;
							  ++in;

							  *_hoops_ISRPI = 0;

							  _hoops_HSRPI = _hoops_ISRPI++;
							  _hoops_CSRPI = _hoops_SSRPI;
							  _hoops_SSRPI = _hoops_GGAPI++;

							  if (format == _hoops_HRSRH) pixel.a = *in++;
							  pixel.r = *in++;
							  pixel.g = *in++;
							  pixel.b = *in++;
							  if (format == Image_RGBA32) pixel.a = *in++;
						  }

						  if (in == _hoops_RCRPI) break;

						  _hoops_SCGCR = _hoops_GAAC;
						  *_hoops_SCGCR = 0;

						  bit = 0;
						  do {
							  color.number = (_hoops_CCRPI.r * _hoops_PCGCR(pixel.r) +
											  _hoops_CCRPI.g * _hoops_PCGCR(pixel.g) +
											  _hoops_CCRPI.b * _hoops_PCGCR(pixel.b)) /
																		255	  +
											 (*_hoops_HSRPI * 7 + *_hoops_GGAPI * 3 +
														*_hoops_SSRPI * 5 + *_hoops_CSRPI) / 16;
							  if (color.number < 0)
								  color.number = 0;
							  else if (color.number > 0x00010000)
								  color.number = 0x00010000;
							  *_hoops_ISRPI = color.number;
							  color.number += 0x8000;
							  color._hoops_CAGCR._hoops_RCGCR = 0;
							  *_hoops_ISRPI -= color.number;
							  if (color._hoops_CAGCR._hoops_SAGCR) *_hoops_SCGCR |= HOOPS_READ_ONLY._hoops_ICHGI[bit];
							  ++count;

							  _hoops_HSRPI = _hoops_ISRPI++;
							  _hoops_CSRPI = _hoops_SSRPI;
							  _hoops_SSRPI = _hoops_GGAPI++;

							  if ((bit = HOOPS_READ_ONLY._hoops_PCHGI[bit]) == 0) *++_hoops_SCGCR = 0;

							  if (in == _hoops_RCRPI) break;

							  if (format == _hoops_HRSRH) pixel.a = *in++;
							  pixel.r = *in++;
							  pixel.g = *in++;
							  pixel.b = *in++;
							  if (format == Image_RGBA32) pixel.a = *in++;
						   } while (pixel.a != 0);

						  start.x = _hoops_HCGCR->x + _hoops_CIRPI;
						  end.x = start.x + count - 1;

						  if (pattern == FP_SOLID)
							  _hoops_CGCGH (nr, &start, &end, 0, _hoops_GAAC);
						  else
							  _hoops_PCRPI (nr, &start, &end, _hoops_GAAC,
											pattern, contrast_color);

						  _hoops_CIRPI += count;
					  }
					  end.y = --start.y;
				  } _hoops_RGGA (--vcount == 0 ||
						   _hoops_GGPGR(nr));

				  FREE_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, Integer32);
				  FREE_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, Integer32);
			  }	  break; /* _hoops_RGAPI */
			} /* _hoops_RSGR _hoops_IIGR _hoops_CICA (_hoops_CCH) */
		}	break; /* _hoops_HGAPI/_hoops_IGAPI */
	  }

	/* _hoops_RPP "/8" == _hoops_GGHSP(_hoops_IGRH) */
	FREE_ARRAY (_hoops_GAAC, (_hoops_PARSP + 7)/8, unsigned char);
#endif
}



#ifndef _hoops_CGAPI

local void _hoops_SGAPI (
	Net_Rendition const &		nr,
	DC_Point const *			_hoops_HCGCR,
	DC_Point const *			_hoops_ICGCR,
	unsigned char alter *		_hoops_GAAC,
	int							pattern,
	Driver_Color const *		contrast_color) {
	Display_Context const *		dc = nr->_hoops_SRA;
	int							row;
	int							col;
	unsigned char alter *		_hoops_SCGCR;
	unsigned char alter *		_hoops_HSGCR;


	if (pattern != FP_USER_DEFINED) {
		int						_hoops_RIRPI;
		int const				*_hoops_AIRPI;

		row = (int)_hoops_HCGCR->y & (dc->_hoops_ASPGH-1);
		if (dc->_hoops_CCAGH)
			row = dc->_hoops_ASPGH - 1 - row;
		col = (int)_hoops_HCGCR->x & (dc->_hoops_ASPGH-1);

		if (dc->_hoops_ASPGH == 4) {
			_hoops_RIRPI = ((unsigned char const *)(dc->_hoops_GRPH[pattern]))[row];
			_hoops_AIRPI = HOOPS_READ_ONLY.incr_mod_4;
		}
		else if (dc->_hoops_ASPGH == 8) {
			_hoops_RIRPI = ((unsigned char const *)(dc->_hoops_GRPH[pattern]))[row];
			_hoops_AIRPI = HOOPS_READ_ONLY._hoops_PCHGI;
		}
		else if (dc->_hoops_ASPGH == 16) {
			_hoops_RIRPI = ((unsigned short const *)(dc->_hoops_GRPH[pattern]))[row];
			_hoops_AIRPI = HOOPS_READ_ONLY._hoops_HCHGI;
		}
		else {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Bit patterns have not been loaded.");
			return;
		}

		_hoops_SCGCR = _hoops_GAAC;
		_hoops_HSGCR = _hoops_SCGCR + ((int)_hoops_ICGCR->x - (int)_hoops_HCGCR->x + 1);

		do {
			if (BIT (_hoops_RIRPI, HOOPS_READ_ONLY._hoops_ICHGI[col]))
				*_hoops_SCGCR = (unsigned char)contrast_color->_hoops_PIHHP;
			col = _hoops_AIRPI[col];
		} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

		_hoops_SGCGH (nr, _hoops_HCGCR, _hoops_ICGCR, 0, _hoops_GAAC);
	}
	else {
		unsigned char const *		_hoops_RIRPI;
		_hoops_SIHHP const *	up = nr->_hoops_IHA->_hoops_PGPH;

		if (up->pattern == null) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "User-defined pattern requested but not defined");
			return;
		}

		row = (int)_hoops_HCGCR->y % up->height;
		if (up->_hoops_RCHHP)
			row = up->height - 1 - row;
		col = (int)_hoops_HCGCR->x % up->width;

		_hoops_RIRPI = &up->pattern[row * up->width];

		_hoops_SCGCR = _hoops_GAAC;
		_hoops_HSGCR = _hoops_SCGCR + ((int)_hoops_ICGCR->x - (int)_hoops_HCGCR->x + 1);

		switch (up->_hoops_ACHHP) {
			case UPAT_NORMAL:
			default: {
				do {
					if (_hoops_RIRPI[col])
						*_hoops_SCGCR = (unsigned char)contrast_color->_hoops_PIHHP;
					if (++col == up->width) col = 0;
				} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

				_hoops_SGCGH (nr, _hoops_HCGCR, _hoops_ICGCR, 0, _hoops_GAAC);
			}	break;

			case UPAT_NO_FACE: {
				int				_hoops_CIRPI = 0;
				DC_Point		start, end;

				/* _hoops_SISR _hoops_GIR _hoops_GGR _hoops_HAPR */
				start.y = _hoops_HCGCR->y;
				start.z = _hoops_HCGCR->z;
				end.y = _hoops_ICGCR->y;
				end.z = _hoops_ICGCR->z;

				_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR) {
					_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR || _hoops_RIRPI[col]) {
						++_hoops_CIRPI;
						++_hoops_SCGCR;
						if (++col == up->width) col = 0;
					}

					if (_hoops_SCGCR == _hoops_HSGCR) break;
					_hoops_GAAC = _hoops_SCGCR;		/* _hoops_SAHR _hoops_GRP _hoops_SCH _hoops_GAR _hoops_IRS _hoops_SPCS _hoops_SRHR */

					_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR || !_hoops_RIRPI[col]) {
						*_hoops_SCGCR = (unsigned char)contrast_color->_hoops_PIHHP;
						++_hoops_SCGCR;
						if (++col == up->width) col = 0;
					}

					start.x = _hoops_HCGCR->x + _hoops_CIRPI;
					end.x = start.x + (_hoops_SCGCR - _hoops_GAAC) - 1;

					_hoops_SGCGH (nr, &start, &end, 0, _hoops_GAAC);

					_hoops_CIRPI += _hoops_SCGCR - _hoops_GAAC;
				}
			}	break;

			case UPAT_NO_CONTRAST: {
				int				_hoops_CIRPI = 0;
				DC_Point		start, end;

				/* _hoops_SISR _hoops_GIR _hoops_GGR _hoops_HAPR */
				start.y = _hoops_HCGCR->y;
				start.z = _hoops_HCGCR->z;
				end.y = _hoops_ICGCR->y;
				end.z = _hoops_ICGCR->z;

				_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR) {
					_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR || !_hoops_RIRPI[col]) {
						++_hoops_CIRPI;
						++_hoops_SCGCR;
						if (++col == up->width) col = 0;
					}

					if (_hoops_SCGCR == _hoops_HSGCR) break;
					_hoops_GAAC = _hoops_SCGCR;		/* _hoops_SAHR _hoops_GRP _hoops_SCH _hoops_GAR _hoops_IRS _hoops_SPCS _hoops_SRHR */

					_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR || _hoops_RIRPI[col]) {
						++_hoops_SCGCR;
						if (++col == up->width) col = 0;
					}

					start.x = _hoops_HCGCR->x + _hoops_CIRPI;
					end.x = start.x + (_hoops_SCGCR - _hoops_GAAC) - 1;

					_hoops_SGCGH (nr, &start, &end, 0, _hoops_GAAC);

					_hoops_CIRPI += _hoops_SCGCR - _hoops_GAAC;
				}
			}	break;
		}
	}
}
#endif


#define _hoops_PCGCR(x)			_hoops_IRGCR(x)

GLOBAL_FUNCTION void HD_Image_To_Gray8_Rasters (
	Net_Rendition const &		nr,
	DC_Point const *			_hoops_HCGCR,
	DC_Point const *			_hoops_ICGCR,
	int							hoffset,
	Image_Format				format,
	int							row_bytes,
	void const * const *		_hoops_HCHIH,
	int							pattern,
	Driver_Color const *		contrast_color,
	Image const *				db_image) {
#ifndef _hoops_CGAPI
	DC_Point					start, end;
	unsigned char alter *		_hoops_GAAC = null;
	unsigned char alter *		_hoops_SCGCR;
	unsigned char alter *		_hoops_HSGCR;
	int							_hoops_PARSP = (int)(_hoops_ICGCR->x - _hoops_HCGCR->x) + 1;
	int							vcount = (int)(_hoops_HCGCR->y - _hoops_ICGCR->y) + 1;
	int							_hoops_SIRPI = 0;

	UNREFERENCED (row_bytes);
	UNREFERENCED(db_image);


	start.x = _hoops_HCGCR->x;
	start.y = _hoops_HCGCR->y;
	start.z = _hoops_HCGCR->z;

	end.x = _hoops_ICGCR->x;
	end.y = _hoops_ICGCR->y;
	end.z = _hoops_ICGCR->z;

	Int_Rectangle const & _hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

	if (_hoops_GPHH.left > start.x) {
		if (_hoops_GPHH.left > end.x)
			return;
		int delta = _hoops_GPHH.left - start.x;
		_hoops_SIRPI += delta;
		_hoops_PARSP -= delta;
		start.x = _hoops_GPHH.left;
	}
	if (_hoops_GPHH.right < end.x) {
		if (_hoops_GPHH.right < start.x)
			return;
		int delta = end.x - _hoops_GPHH.right;
		_hoops_PARSP -= delta;
		end.x = _hoops_GPHH.right;
	}
	if (_hoops_GPHH.bottom > end.y) {
		if (_hoops_GPHH.bottom > start.y)
			return;
		int delta = _hoops_GPHH.bottom - end.y;
		vcount -= delta;
		//_hoops_RSGR._hoops_HAPC = _hoops_HSPH._hoops_PRPC;
	}
	if (_hoops_GPHH.top < start.y) {
		if (_hoops_GPHH.top < end.y)
			return;
		int delta = start.y - _hoops_GPHH.top;
		vcount -= delta;
		_hoops_HCHIH += delta;
		start.y = _hoops_GPHH.top;
	}

	end.y = start.y;

	ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, unsigned char);

	switch (format) {
		case _hoops_GGRH:
		case _hoops_RGRH:
		case _hoops_AGRH:
		case _hoops_IRRH:
		case _hoops_CRRH:
		case _hoops_SRRH:
		case _hoops_AHGH:
			ASSERT(0);  //_hoops_GSRPI _hoops_SR _hoops_PAH _hoops_AA _hoops_ARI?
			break;

		case Image_MAPPED_16: {
			Driver_Color const	*_hoops_SPRAR;

			_hoops_SPRAR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_AHHHP;

			do {
				unsigned short const	*in;

				in = (unsigned short const *)*_hoops_HCHIH++ + hoffset;
				_hoops_SCGCR = _hoops_GAAC;
				_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

				do *_hoops_SCGCR = (unsigned char)_hoops_SPRAR[*in++]._hoops_PIHHP;
				_hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

				_hoops_SGCGH (nr, &start, &end, 0, _hoops_GAAC);

				end.y = --start.y;
			} _hoops_RGGA (--vcount == 0 || 
				_hoops_GGPGR(nr));
		}	break; /* _hoops_PPCC */

		case Image_MAPPED_8: {
			Driver_Color const	*_hoops_SPRAR;

			_hoops_SPRAR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_AHHHP;

			do {
				unsigned char const *in;

				in = (unsigned char const *)*_hoops_HCHIH++ + hoffset;
				_hoops_SCGCR = _hoops_GAAC;
				_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

				do {
					*_hoops_SCGCR = (unsigned char)_hoops_SPRAR[_hoops_PCGCR(*in)]._hoops_PIHHP;
					++in;
				} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

				_hoops_SGCGH (nr, &start, &end, 0, _hoops_GAAC);

				end.y = --start.y;
			} _hoops_RGGA (--vcount == 0 || 
				_hoops_GGPGR(nr));
		}	break; /* _hoops_APCC */

		case _hoops_HHGH: {
			do {
				_hoops_SHGH const *in;

				in = (_hoops_SHGH const *)*_hoops_HCHIH++ + hoffset;
				_hoops_SCGCR = _hoops_GAAC;
				_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

				do {
					*_hoops_SCGCR = (unsigned char)_hoops_IRASP (_hoops_PCGCR(in->r), _hoops_PCGCR(in->g), _hoops_PCGCR(in->b));
					++in;
				} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

				_hoops_SGCGH (nr, &start, &end, 0, _hoops_GAAC);

				end.y = --start.y;
			} _hoops_RGGA (--vcount == 0 ||
						_hoops_GGPGR(nr));
		}	break; /* _hoops_SGRPI */

		case _hoops_CSGSP: {
			do {
				RGBAS32 const		*in;
				RGBAS32 const		*_hoops_RCRPI;
				int					_hoops_CIRPI = _hoops_SIRPI;

				in = (RGBAS32 const *)*_hoops_HCHIH++ + hoffset;
				_hoops_RCRPI = in + _hoops_PARSP;

				_hoops_RGGA (in == _hoops_RCRPI) {
					_hoops_RGGA (in == _hoops_RCRPI || in->a != 0) {
						++_hoops_CIRPI;
						++in;
					}

					if (in == _hoops_RCRPI) break;

					_hoops_SCGCR = _hoops_GAAC;

					_hoops_RGGA (in == _hoops_RCRPI || in->a == 0) {
						*_hoops_SCGCR++ = (unsigned char)_hoops_IRASP (_hoops_PCGCR(in->r),
															_hoops_PCGCR(in->g),
															_hoops_PCGCR(in->b));
						++in;
					}

					start.x = _hoops_HCGCR->x + _hoops_CIRPI;
					end.x = start.x + (_hoops_SCGCR - _hoops_GAAC) - 1;
					if (pattern == FP_SOLID)
						_hoops_SGCGH (nr, &start, &end, 0, _hoops_GAAC);
					else
						_hoops_SGAPI (nr, &start, &end, _hoops_GAAC, pattern, contrast_color);

					_hoops_CIRPI += _hoops_SCGCR - _hoops_GAAC;
				}
				end.y = --start.y;
			} _hoops_RGGA (--vcount == 0 || 
						_hoops_GGPGR(nr));
		}	break; /* _hoops_PGAPI */

		case Image_RGBA32: 
		case _hoops_HRSRH: {
			do {
				unsigned char const		*in;
				unsigned char const		*_hoops_RCRPI;
				int						_hoops_CIRPI = _hoops_SIRPI;
				RGBAS32					pixel = _hoops_CAHSR::_hoops_SAHSR;

				in = (unsigned char const *)*_hoops_HCHIH++ + 4*hoffset;
				_hoops_RCRPI = in + 4*_hoops_PARSP;

				if (format == _hoops_HRSRH) pixel.a = *in++;
				pixel.r = *in++;
				pixel.g = *in++;
				pixel.b = *in++;
				if (format == Image_RGBA32) pixel.a = *in++;

				_hoops_RGGA (in == _hoops_RCRPI) {
					_hoops_RGGA (in == _hoops_RCRPI || pixel.a != 0) {
						++_hoops_CIRPI;

						if (format == _hoops_HRSRH) pixel.a = *in++;
						pixel.r = *in++;
						pixel.g = *in++;
						pixel.b = *in++;
						if (format == Image_RGBA32) pixel.a = *in++;
					}

					if (in == _hoops_RCRPI) break;

					_hoops_SCGCR = _hoops_GAAC;

					do {
						*_hoops_SCGCR++ = (unsigned char)_hoops_IRASP (_hoops_PCGCR(pixel.r),
															_hoops_PCGCR(pixel.g),
															_hoops_PCGCR(pixel.b));

						if (in == _hoops_RCRPI) break;

						if (format == _hoops_HRSRH) pixel.a = *in++;
						pixel.r = *in++;
						pixel.g = *in++;
						pixel.b = *in++;
						if (format == Image_RGBA32) pixel.a = *in++;
					} while (pixel.a != 0);

					start.x = _hoops_HCGCR->x + _hoops_CIRPI;
					end.x = start.x + (_hoops_SCGCR - _hoops_GAAC) - 1;
					if (pattern == FP_SOLID)
						_hoops_SGCGH (nr, &start, &end, 0, _hoops_GAAC);
					else
						_hoops_SGAPI (nr, &start, &end, _hoops_GAAC, pattern, contrast_color);

					_hoops_CIRPI += _hoops_SCGCR - _hoops_GAAC;
				}
				end.y = --start.y;
			} _hoops_RGGA (--vcount == 0 || 
						_hoops_GGPGR(nr));
		}	break; /* _hoops_GRAPI/_hoops_ACSA */
	}

	FREE_ARRAY (_hoops_GAAC, _hoops_PARSP, unsigned char);
#endif
}




#ifndef DISABLE_MAPPED16_RASTERS

local void _hoops_RRAPI (
	Net_Rendition const &		nr,
	DC_Point const *			_hoops_HCGCR,
	DC_Point const *			_hoops_ICGCR,
	unsigned short alter *		_hoops_GAAC,
	int							pattern,
	Driver_Color const *		contrast_color) {
	Display_Context const *		dc = nr->_hoops_SRA;
	int							row;
	int							col;
	unsigned short alter *		_hoops_SCGCR;
	unsigned short alter *		_hoops_HSGCR;

	if (pattern != FP_USER_DEFINED) {
		int						_hoops_RIRPI;
		int const *				_hoops_AIRPI;

		row = (int)_hoops_HCGCR->y & (dc->_hoops_ASPGH-1);
		if (dc->_hoops_CCAGH)
			row = dc->_hoops_ASPGH - 1 - row;
		col = (int)_hoops_HCGCR->x & (dc->_hoops_ASPGH-1);

		if (dc->_hoops_ASPGH == 4) {
			_hoops_RIRPI = ((unsigned char const *)(dc->_hoops_GRPH[pattern]))[row];
			_hoops_AIRPI = HOOPS_READ_ONLY.incr_mod_4;
		}
		else if (dc->_hoops_ASPGH == 8) {
			_hoops_RIRPI = ((unsigned char const *)(dc->_hoops_GRPH[pattern]))[row];
			_hoops_AIRPI = HOOPS_READ_ONLY._hoops_PCHGI;
		}
		else if (dc->_hoops_ASPGH == 16) {
			_hoops_RIRPI = ((unsigned short const *)(dc->_hoops_GRPH[pattern]))[row];
			_hoops_AIRPI = HOOPS_READ_ONLY._hoops_HCHGI;
		}
		else {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Bit patterns have not been loaded.");
			return;
		}

		_hoops_SCGCR = _hoops_GAAC;
		_hoops_HSGCR = _hoops_SCGCR + ((int)_hoops_ICGCR->x - (int)_hoops_HCGCR->x + 1);

		do {
			if (BIT (_hoops_RIRPI, HOOPS_READ_ONLY._hoops_ICHGI[col]))
				*_hoops_SCGCR = contrast_color->_hoops_PGGCR;
			col = _hoops_AIRPI[col];
		} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

		_hoops_RRCGH (nr, _hoops_HCGCR, _hoops_ICGCR, 0, _hoops_GAAC);
	}
	else {
		unsigned char const *		_hoops_RIRPI;
		_hoops_SIHHP const *	up = nr->_hoops_IHA->_hoops_PGPH;

		if (up->pattern == null) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "User-defined pattern requested but not defined");
			return;
		}

		row = (int)_hoops_HCGCR->y % up->height;
		if (up->_hoops_RCHHP)
			row = up->height - 1 - row;
		col = (int)_hoops_HCGCR->x % up->width;

		_hoops_RIRPI = &up->pattern[row * up->width];

		_hoops_SCGCR = _hoops_GAAC;
		_hoops_HSGCR = _hoops_SCGCR + ((int)_hoops_ICGCR->x - (int)_hoops_HCGCR->x + 1);

		switch (up->_hoops_ACHHP) {
			case UPAT_NORMAL:
			default: {
				do {
					if (_hoops_RIRPI[col])
						*_hoops_SCGCR = contrast_color->_hoops_PGGCR;
					if (++col == up->width) col = 0;
				} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

				_hoops_RRCGH (nr, _hoops_HCGCR, _hoops_ICGCR, 0, _hoops_GAAC);
			}	break;

			case UPAT_NO_FACE: {
				int				_hoops_CIRPI = 0;
				DC_Point		start, end;

				/* _hoops_SISR _hoops_GIR _hoops_GGR _hoops_HAPR */
				start.y = _hoops_HCGCR->y;
				start.z = _hoops_HCGCR->z;
				end.y = _hoops_ICGCR->y;
				end.z = _hoops_ICGCR->z;

				_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR) {
					_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR || _hoops_RIRPI[col]) {
						++_hoops_CIRPI;
						++_hoops_SCGCR;
						if (++col == up->width) col = 0;
					}

					if (_hoops_SCGCR == _hoops_HSGCR) break;
					_hoops_GAAC = _hoops_SCGCR;		/* _hoops_SAHR _hoops_GRP _hoops_SCH _hoops_GAR _hoops_IRS _hoops_SPCS _hoops_SRHR */

					_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR || !_hoops_RIRPI[col]) {
						*_hoops_SCGCR = contrast_color->_hoops_PGGCR;
						++_hoops_SCGCR;
						if (++col == up->width) col = 0;
					}

					start.x = _hoops_HCGCR->x + _hoops_CIRPI;
					end.x = start.x + (_hoops_SCGCR - _hoops_GAAC) - 1;

					_hoops_RRCGH (nr, &start, &end, 0, _hoops_GAAC);

					_hoops_CIRPI += _hoops_SCGCR - _hoops_GAAC;
				}
			}	break;

			case UPAT_NO_CONTRAST: {
				int				_hoops_CIRPI = 0;
				DC_Point		start, end;

				/* _hoops_SISR _hoops_GIR _hoops_GGR _hoops_HAPR */
				start.y = _hoops_HCGCR->y;
				start.z = _hoops_HCGCR->z;
				end.y = _hoops_ICGCR->y;
				end.z = _hoops_ICGCR->z;

				_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR) {
					_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR || !_hoops_RIRPI[col]) {
						++_hoops_CIRPI;
						++_hoops_SCGCR;
						if (++col == up->width) col = 0;
					}

					if (_hoops_SCGCR == _hoops_HSGCR) break;
					_hoops_GAAC = _hoops_SCGCR;		/* _hoops_SAHR _hoops_GRP _hoops_SCH _hoops_GAR _hoops_IRS _hoops_SPCS _hoops_SRHR */

					_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR || _hoops_RIRPI[col]) {
						++_hoops_SCGCR;
						if (++col == up->width) col = 0;
					}

					start.x = _hoops_HCGCR->x + _hoops_CIRPI;
					end.x = start.x + (_hoops_SCGCR - _hoops_GAAC) - 1;

					_hoops_RRCGH (nr, &start, &end, 0, _hoops_GAAC);

					_hoops_CIRPI += _hoops_SCGCR - _hoops_GAAC;
				}
			}	break;
		}
	}
}
#endif


#define _hoops_PCGCR(x)			_hoops_IRGCR(x)
#define _hoops_ARAPI(x)			_hoops_SIRGI(x)

#if _MSC_VER >= 1300
#pragma optimize("", off)
#endif

GLOBAL_FUNCTION void HD_Image_To_Mapped16_Rasters (
	Net_Rendition const &		nr,
	DC_Point const *			_hoops_HCGCR,
	DC_Point const *			_hoops_ICGCR,
	int							hoffset,
	Image_Format				format,
	int							row_bytes,
	void const * const *		_hoops_HCHIH,
	int							pattern,
	Driver_Color const *		contrast_color,
	Image const *				db_image) {
#ifndef DISABLE_MAPPED16_RASTERS
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	_hoops_ISHHP const	&	_hoops_CSHHP = nr->_hoops_ASIR;
	DC_Point					start;
	DC_Point					end;
	unsigned short alter *		_hoops_GAAC = null;
	unsigned short alter *		_hoops_SCGCR;
	unsigned short alter *		_hoops_HSGCR;
	int							_hoops_PARSP = (int)(_hoops_ICGCR->x - _hoops_HCGCR->x) + 1;
	int							vcount = (int)(_hoops_HCGCR->y - _hoops_ICGCR->y) + 1;
	int							_hoops_SIRPI = 0;
	Quantization_Flags			mode = _hoops_RRGH->_hoops_SIRAP;

	UNREFERENCED(db_image);


	start.x = _hoops_HCGCR->x;
	start.y = _hoops_HCGCR->y;
	start.z = _hoops_HCGCR->z;

	end.x = _hoops_ICGCR->x;
	end.y = _hoops_ICGCR->y;
	end.z = _hoops_ICGCR->z;

	Int_Rectangle const & _hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

	if (_hoops_GPHH.left > start.x) {
		if (_hoops_GPHH.left > end.x)
			return;
		int delta = _hoops_GPHH.left - start.x;
		_hoops_SIRPI += delta;
		_hoops_PARSP -= delta;
		start.x = _hoops_GPHH.left;
	}
	if (_hoops_GPHH.right < end.x) {
		if (_hoops_GPHH.right < start.x)
			return;
		int delta = end.x - _hoops_GPHH.right;
		_hoops_PARSP -= delta;
		end.x = _hoops_GPHH.right;
	}
	if (_hoops_GPHH.bottom > end.y) {
		if (_hoops_GPHH.bottom > start.y)
			return;
		int delta = _hoops_GPHH.bottom - end.y;
		vcount -= delta;
		//_hoops_RSGR._hoops_HAPC = _hoops_HSPH._hoops_PRPC;
	}
	if (_hoops_GPHH.top < start.y) {
		if (_hoops_GPHH.top < end.y)
			return;
		int delta = start.y - _hoops_GPHH.top;
		vcount -= delta;
		_hoops_HCHIH += delta;
		start.y = _hoops_GPHH.top;
	}

	end.y = start.y;

	switch (format) {
	  case Image_MAPPED_16: {
		  if (_hoops_CSHHP->_hoops_PSIR->_hoops_RHHHP == 0) do {
			  unsigned short const *	_hoops_GCRPI;
			  char const *				_hoops_RSGHR;
			  char const *				next;
			  int						_hoops_AAGHR;

			  _hoops_RSGHR = (char const *)((unsigned short const *)*_hoops_HCHIH +
															hoffset);
			  _hoops_AAGHR = _hoops_IICIA;
			  _hoops_GCRPI = (unsigned short const *)_hoops_RSGHR;
			  while (--vcount > 0 &&
					 (_hoops_RSGHR + row_bytes ==
					  (next = (char const *)
								((unsigned short const *)*++_hoops_HCHIH +
														 hoffset))) &&
					 _hoops_AAGHR >= row_bytes) {
				  _hoops_RSGHR = next;
				  --end.y;
				  _hoops_AAGHR -= row_bytes;
			  }
			  _hoops_RRCGH (nr, &start, &end, row_bytes, _hoops_GCRPI);
			  start.y = --end.y;
		  } _hoops_RGGA (vcount <= 0 || 
			  _hoops_GGPGR(nr));

		  else {
			  short						_hoops_SPRAR;

			  _hoops_SPRAR = (short)_hoops_CSHHP->_hoops_PSIR->_hoops_RHHHP;
			  ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, unsigned short);

			  do {
				  unsigned short const *	in;

				  in = (unsigned short const *)*_hoops_HCHIH++ + hoffset;
				  _hoops_SCGCR = _hoops_GAAC;
				  _hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

				  do *_hoops_SCGCR++ = _hoops_SPRAR + *in++;
				  _hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR);

				  _hoops_RRCGH (nr, &start, &end, 0, _hoops_GAAC);

				  end.y = --start.y;
			  } _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
		  }
	  }	  break; /* _hoops_PPCC */


	  case Image_MAPPED_8: {
		  ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, unsigned short);

		  if (_hoops_CSHHP->_hoops_PSIR->_hoops_RHHHP == 0) do {
			  unsigned short const *		in;

			  in = (unsigned short const *)*_hoops_HCHIH++ + hoffset;
			  _hoops_SCGCR = _hoops_GAAC;
			  _hoops_HSGCR = _hoops_GAAC + _hoops_PARSP;

			  do *_hoops_SCGCR++ = (unsigned short)*in++;
			  _hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR);

			  _hoops_RRCGH (nr, &start, &end, 0, _hoops_GAAC);

			  end.y = --start.y;
		  } _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));

		  else {
			  short							_hoops_SPRAR;

			  _hoops_SPRAR = (short)_hoops_CSHHP->_hoops_PSIR->_hoops_RHHHP;

			  do {
				  unsigned short const *	in;

				  in = (unsigned short const *)*_hoops_HCHIH++ + hoffset;
				  _hoops_SCGCR = _hoops_GAAC;
				  _hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

				  do *_hoops_SCGCR++ = _hoops_SPRAR + (short)*in++;
				  _hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR);

				  _hoops_RRCGH (nr, &start, &end, 0, _hoops_GAAC);

				  end.y = --start.y;
			  } _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
		  }
	  }	  break; /* _hoops_APCC */


	  case _hoops_HHGH: {
		  _hoops_SHGH const *			in;
		  _hoops_CRRRH			color;
		  int					index;
		  _hoops_SGGCR				_hoops_PRAPI;
		  _hoops_SGGCR				_hoops_CCRPI;

		  ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, unsigned short);

		  _hoops_PRAPI.r = dc->_hoops_AGPGH.r;
		  _hoops_PRAPI.g = dc->_hoops_AGPGH.g;
		  _hoops_PRAPI.b = dc->_hoops_AGPGH.b;
		  _hoops_CCRPI.r = 0x00010000 * (_hoops_PRAPI.r - 1) / 255;
		  _hoops_CCRPI.g = 0x00010000 * (_hoops_PRAPI.g - 1) / 255;
		  _hoops_CCRPI.b = 0x00010000 * (_hoops_PRAPI.b - 1) / 255;

		  switch (mode) {
			case Quantization_DITHER: {
				do {
					int						row;
					int						col;
					unsigned short const *	_hoops_IHGCR;

					in = (_hoops_SHGH const *)*_hoops_HCHIH++ + hoffset;
					_hoops_SCGCR = _hoops_GAAC;
					_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

					row = (int)start.y & 7;
					col = (int)start.x & 7;
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row];

					do {
						Integer32 const _hoops_CPGCR = _hoops_IHGCR[col];

						color.number = _hoops_ARAPI (in->r) * _hoops_CCRPI.r + _hoops_CPGCR;
						index = color._hoops_CAGCR._hoops_SAGCR;
						color.number = _hoops_ARAPI (in->g) * _hoops_CCRPI.g + _hoops_CPGCR;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;
						color.number = _hoops_ARAPI (in->b) * _hoops_CCRPI.b + _hoops_CPGCR;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

						*_hoops_SCGCR = index + dc->_hoops_RHGCR;
						++in;
						col = HOOPS_READ_ONLY._hoops_PCHGI[col];
					} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					if (pattern == FP_SOLID)
						_hoops_RRCGH (nr, &start, &end, 0, _hoops_GAAC);
					else
						_hoops_RRAPI (nr, &start, &end, _hoops_GAAC, pattern, contrast_color);
					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
			}	break; /* _hoops_RSRPI */

			case Quantization_THRESHOLD: {
				do {
					in = (_hoops_SHGH const *)*_hoops_HCHIH++ + hoffset;
					_hoops_SCGCR = _hoops_GAAC;
					_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

					do {
						color.number = _hoops_PCGCR (in->r) * _hoops_CCRPI.r + 0x8000;
						index = color._hoops_CAGCR._hoops_SAGCR;
						color.number = _hoops_PCGCR (in->g) * _hoops_CCRPI.g + 0x8000;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;
						color.number = _hoops_PCGCR (in->b) * _hoops_CCRPI.b + 0x8000;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;
						*_hoops_SCGCR = index + dc->_hoops_RHGCR;
						++in;
					} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					if (pattern == FP_SOLID)
						_hoops_RRCGH (nr, &start, &end, 0, _hoops_GAAC);
					else
						_hoops_RRAPI (nr, &start, &end, _hoops_GAAC, pattern, contrast_color);

					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
			}	break; /* _hoops_ASRPI */

			case Quantization_ERROR_DIFFUSION: {
				_hoops_SGGCR alter	*_hoops_PSRPI[2];
				int					row = 0;

				ALLOC_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, _hoops_SGGCR);
				ALLOC_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, _hoops_SGGCR);

				{
					int				_hoops_ICRHH;
					for (_hoops_ICRHH = 0; _hoops_ICRHH < _hoops_PARSP + 2; ++_hoops_ICRHH)
						_hoops_PSRPI[0][_hoops_ICRHH].r = _hoops_PSRPI[0][_hoops_ICRHH].g = _hoops_PSRPI[0][_hoops_ICRHH].b =
							_hoops_PSRPI[1][_hoops_ICRHH].r = _hoops_PSRPI[1][_hoops_ICRHH].g = _hoops_PSRPI[1][_hoops_ICRHH].b = 0;
				}

				do {
					_hoops_SGGCR alter		*_hoops_HSRPI,
														*_hoops_ISRPI;
					_hoops_SGGCR alter		*_hoops_CSRPI,
														*_hoops_SSRPI,
														*_hoops_GGAPI;

					in = (_hoops_SHGH const *)*_hoops_HCHIH++ + hoffset;
					_hoops_SCGCR = _hoops_GAAC;
					_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

					_hoops_HSRPI = &_hoops_PSRPI[row][0];
					_hoops_ISRPI = &_hoops_PSRPI[row][1];
					row = 1-row;
					_hoops_CSRPI = &_hoops_PSRPI[row][0];
					_hoops_SSRPI = &_hoops_PSRPI[row][1];
					_hoops_GGAPI = &_hoops_PSRPI[row][2];

					do {
						color.number = _hoops_CCRPI.r * _hoops_PCGCR (in->r) +
							(_hoops_HSRPI->r * 7 + _hoops_GGAPI->r * 3 + _hoops_SSRPI->r * 5 + _hoops_CSRPI->r) / 16;
						if (color.number < 0) color.number = 0;
						else if (color.number >= 0x01000000) color.number = 0x01000000;
						_hoops_ISRPI->r = color.number;
						color.number += 0x8000;
						color._hoops_CAGCR._hoops_RCGCR = 0;
						_hoops_ISRPI->r -= color.number;
						index = color._hoops_CAGCR._hoops_SAGCR;

						color.number = _hoops_CCRPI.g * _hoops_PCGCR (in->g) +
							(_hoops_HSRPI->g * 7 + _hoops_GGAPI->g * 3 + _hoops_SSRPI->g * 5 + _hoops_CSRPI->g) / 16;
						if (color.number < 0) color.number = 0;
						else if (color.number >= 0x01000000) color.number = 0x01000000;
						_hoops_ISRPI->g = color.number;
						color.number += 0x8000;
						color._hoops_CAGCR._hoops_RCGCR = 0;
						_hoops_ISRPI->g -= color.number;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;

						color.number = _hoops_CCRPI.b * _hoops_PCGCR (in->b) +
							(_hoops_HSRPI->b * 7 + _hoops_GGAPI->b * 3 + _hoops_SSRPI->b * 5 + _hoops_CSRPI->b) / 16;
						if (color.number < 0) color.number = 0;
						else if (color.number >= 0x01000000) color.number = 0x01000000;
						_hoops_ISRPI->b = color.number;
						color.number += 0x8000;
						color._hoops_CAGCR._hoops_RCGCR = 0;
						_hoops_ISRPI->b -= color.number;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

						*_hoops_SCGCR = index + dc->_hoops_RHGCR;
						++in;

						_hoops_HSRPI = _hoops_ISRPI++;
						_hoops_CSRPI = _hoops_SSRPI;
						_hoops_SSRPI = _hoops_GGAPI++;
					} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					if (pattern == FP_SOLID)
						_hoops_RRCGH (nr, &start, &end, 0, _hoops_GAAC);
					else
						_hoops_RRAPI (nr, &start, &end, _hoops_GAAC, pattern, contrast_color);
					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));

				FREE_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, _hoops_SGGCR);
				FREE_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, _hoops_SGGCR);
			}	break; /* _hoops_RGAPI */
		  } /* _hoops_RSGR _hoops_IIGR _hoops_CICA (_hoops_CCH) */
	  }	  break; /* _hoops_SGRPI */

	  case _hoops_CSGSP: {
		  RGBAS32 const		*in;
		  _hoops_CRRRH			color;
		  int						index;
		  _hoops_SGGCR				_hoops_PRAPI;
		  _hoops_SGGCR			_hoops_CCRPI;

		  ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, unsigned short);

		  _hoops_PRAPI.r = dc->_hoops_AGPGH.r;
		  _hoops_PRAPI.g = dc->_hoops_AGPGH.g;
		  _hoops_PRAPI.b = dc->_hoops_AGPGH.b;
		  _hoops_CCRPI.r = 0x00010000 * (_hoops_PRAPI.r - 1) / 255;
		  _hoops_CCRPI.g = 0x00010000 * (_hoops_PRAPI.g - 1) / 255;
		  _hoops_CCRPI.b = 0x00010000 * (_hoops_PRAPI.b - 1) / 255;

		  switch (mode) {
			case Quantization_DITHER: {
				do {
					int						row;
					int						col;
					unsigned short const	*_hoops_IHGCR;

					in = (RGBAS32 const *)*_hoops_HCHIH++ + hoffset;
					_hoops_SCGCR = _hoops_GAAC;
					_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

					row = (int)start.y & 7;
					col = (int)start.x & 7;
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row];

					do {
						Integer32 const _hoops_CPGCR = _hoops_IHGCR[col];

						color.number = _hoops_ARAPI (in->r) * _hoops_CCRPI.r + _hoops_CPGCR;
						index = color._hoops_CAGCR._hoops_SAGCR;
						color.number = _hoops_ARAPI (in->g) * _hoops_CCRPI.g + _hoops_CPGCR;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;
						color.number = _hoops_ARAPI (in->b) * _hoops_CCRPI.b + _hoops_CPGCR;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

						*_hoops_SCGCR = index + dc->_hoops_RHGCR;
						++in;
						col = HOOPS_READ_ONLY._hoops_PCHGI[col];
					} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					if (pattern == FP_SOLID)
						_hoops_RRCGH (nr, &start, &end, 0, _hoops_GAAC);
					else
						_hoops_RRAPI (nr, &start, &end, _hoops_GAAC, pattern, contrast_color);
					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
			}	break; /* _hoops_RSRPI */

			case Quantization_THRESHOLD: {
				do {
					in = (RGBAS32 const *)*_hoops_HCHIH++ + hoffset;
					_hoops_SCGCR = _hoops_GAAC;
					_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

					do {
						color.number = _hoops_PCGCR (in->r) * _hoops_CCRPI.r + 0x8000;
						index = color._hoops_CAGCR._hoops_SAGCR;
						color.number = _hoops_PCGCR (in->g) * _hoops_CCRPI.g + 0x8000;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;
						color.number = _hoops_PCGCR (in->b) * _hoops_CCRPI.b + 0x8000;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;
						*_hoops_SCGCR = index + dc->_hoops_RHGCR;
						++in;
					} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					if (pattern == FP_SOLID)
						_hoops_RRCGH (nr, &start, &end, 0, _hoops_GAAC);
					else
						_hoops_RRAPI (nr, &start, &end, _hoops_GAAC, pattern, contrast_color);

					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
			}	break; /* _hoops_ASRPI */

			case Quantization_ERROR_DIFFUSION: {
				_hoops_SGGCR alter	*_hoops_PSRPI[2];
				int					row = 0;

				ALLOC_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, _hoops_SGGCR);
				ALLOC_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, _hoops_SGGCR);

				{
					int				_hoops_ICRHH;
					for (_hoops_ICRHH = 0; _hoops_ICRHH < _hoops_PARSP + 2; ++_hoops_ICRHH)
						_hoops_PSRPI[0][_hoops_ICRHH].r = _hoops_PSRPI[0][_hoops_ICRHH].g = _hoops_PSRPI[0][_hoops_ICRHH].b =
							_hoops_PSRPI[1][_hoops_ICRHH].r = _hoops_PSRPI[1][_hoops_ICRHH].g = _hoops_PSRPI[1][_hoops_ICRHH].b = 0;
				}

				do {
					_hoops_SGGCR alter		*_hoops_HSRPI,
														*_hoops_ISRPI;
					_hoops_SGGCR alter		*_hoops_CSRPI,
														*_hoops_SSRPI,
														*_hoops_GGAPI;

					in = (RGBAS32 const *)*_hoops_HCHIH++ + hoffset;
					_hoops_SCGCR = _hoops_GAAC;
					_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

					_hoops_HSRPI = &_hoops_PSRPI[row][0];
					_hoops_ISRPI = &_hoops_PSRPI[row][1];
					row = 1-row;
					_hoops_CSRPI = &_hoops_PSRPI[row][0];
					_hoops_SSRPI = &_hoops_PSRPI[row][1];
					_hoops_GGAPI = &_hoops_PSRPI[row][2];

					do {
						color.number = _hoops_CCRPI.r * _hoops_PCGCR (in->r) +
							(_hoops_HSRPI->r * 7 + _hoops_GGAPI->r * 3 + _hoops_SSRPI->r * 5 + _hoops_CSRPI->r) / 16;
						if (color.number < 0) color.number = 0;
						else if (color.number >= 0x01000000) color.number = 0x01000000;
						_hoops_ISRPI->r = color.number;
						color.number += 0x8000;
						color._hoops_CAGCR._hoops_RCGCR = 0;
						_hoops_ISRPI->r -= color.number;
						index = color._hoops_CAGCR._hoops_SAGCR;

						color.number = _hoops_CCRPI.g * _hoops_PCGCR (in->g) +
							(_hoops_HSRPI->g * 7 + _hoops_GGAPI->g * 3 + _hoops_SSRPI->g * 5 + _hoops_CSRPI->g) / 16;
						if (color.number < 0) color.number = 0;
						else if (color.number >= 0x01000000) color.number = 0x01000000;
						_hoops_ISRPI->g = color.number;
						color.number += 0x8000;
						color._hoops_CAGCR._hoops_RCGCR = 0;
						_hoops_ISRPI->g -= color.number;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;

						color.number = _hoops_CCRPI.b * _hoops_PCGCR (in->b) +
							(_hoops_HSRPI->b * 7 + _hoops_GGAPI->b * 3 + _hoops_SSRPI->b * 5 + _hoops_CSRPI->b) / 16;
						if (color.number < 0) color.number = 0;
						else if (color.number >= 0x01000000) color.number = 0x01000000;
						_hoops_ISRPI->b = color.number;
						color.number += 0x8000;
						color._hoops_CAGCR._hoops_RCGCR = 0;
						_hoops_ISRPI->b -= color.number;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

						*_hoops_SCGCR = index + dc->_hoops_RHGCR;
						++in;

						_hoops_HSRPI = _hoops_ISRPI++;
						_hoops_CSRPI = _hoops_SSRPI;
						_hoops_SSRPI = _hoops_GGAPI++;
					} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					if (pattern == FP_SOLID)
						_hoops_RRCGH (nr, &start, &end, 0, _hoops_GAAC);
					else
						_hoops_RRAPI (nr, &start, &end, _hoops_GAAC, pattern, contrast_color);
					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));

				FREE_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, _hoops_SGGCR);
				FREE_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, _hoops_SGGCR);
			}	break; /* _hoops_RGAPI */
		  } /* _hoops_RSGR _hoops_IIGR _hoops_CICA (_hoops_CCH) */
	  }	  break; /* _hoops_PGAPI */

	  case Image_RGBA32:
	  case _hoops_HRSRH: {
		  unsigned char const		*in;
		  _hoops_CRRRH			color;
		  int						index;
		  unsigned char const		*_hoops_RCRPI;
		  _hoops_SGGCR				_hoops_PRAPI;
		  _hoops_SGGCR			_hoops_CCRPI;

		  ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, unsigned short);

		  _hoops_PRAPI.r = dc->_hoops_AGPGH.r;
		  _hoops_PRAPI.g = dc->_hoops_AGPGH.g;
		  _hoops_PRAPI.b = dc->_hoops_AGPGH.b;
		  _hoops_CCRPI.r = 0x00010000 * (_hoops_PRAPI.r - 1) / 255;
		  _hoops_CCRPI.g = 0x00010000 * (_hoops_PRAPI.g - 1) / 255;
		  _hoops_CCRPI.b = 0x00010000 * (_hoops_PRAPI.b - 1) / 255;

		  switch (mode) {
			case Quantization_DITHER: {
				do {
					int						row;
					int						col;
					unsigned short const	*_hoops_IHGCR;
					int						_hoops_CIRPI = _hoops_SIRPI;
					RGBAS32					pixel = _hoops_CAHSR::_hoops_SAHSR;

					in = (unsigned char const *)*_hoops_HCHIH++ + 4*hoffset;
					_hoops_RCRPI = in + 4*_hoops_PARSP;

					row = (int)start.y & 7;
					col = (int)start.x & 7;
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row];

					if (format == _hoops_HRSRH) pixel.a = *in++;
					pixel.r = *in++;
					pixel.g = *in++;
					pixel.b = *in++;
					if (format == Image_RGBA32) pixel.a = *in++;

					_hoops_RGGA (in == _hoops_RCRPI) {
						_hoops_RGGA (in == _hoops_RCRPI || pixel.a != 0) {
							col = HOOPS_READ_ONLY._hoops_PCHGI[col];
							++_hoops_CIRPI;

							if (format == _hoops_HRSRH) pixel.a = *in++;
							pixel.r = *in++;
							pixel.g = *in++;
							pixel.b = *in++;
							if (format == Image_RGBA32) pixel.a = *in++;
						}

						if (in == _hoops_RCRPI) break;

						_hoops_SCGCR = _hoops_GAAC;

						_hoops_RGGA (in == _hoops_RCRPI || pixel.a == 0) {
							Integer32 const _hoops_CPGCR = _hoops_IHGCR[col];

							color.number = _hoops_ARAPI (pixel.r) * _hoops_CCRPI.r + _hoops_CPGCR;
							index = color._hoops_CAGCR._hoops_SAGCR;
							color.number = _hoops_ARAPI (pixel.g) * _hoops_CCRPI.g + _hoops_CPGCR;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;
							color.number = _hoops_ARAPI (pixel.b) * _hoops_CCRPI.b + _hoops_CPGCR;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

							*_hoops_SCGCR++ = index + dc->_hoops_RHGCR;

							col = HOOPS_READ_ONLY._hoops_PCHGI[col];

							if (format == _hoops_HRSRH) pixel.a = *in++;
							pixel.r = *in++;
							pixel.g = *in++;
							pixel.b = *in++;
							if (format == Image_RGBA32) pixel.a = *in++;
						}

						start.x = _hoops_HCGCR->x + _hoops_CIRPI;
						end.x = start.x + (_hoops_SCGCR - _hoops_GAAC) - 1;
						if (pattern == FP_SOLID)
							_hoops_RRCGH (nr, &start, &end, 0, _hoops_GAAC);
						else
							_hoops_RRAPI (nr, &start, &end, _hoops_GAAC, pattern, contrast_color);

						_hoops_CIRPI += _hoops_SCGCR - _hoops_GAAC;
					}
					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
			}	break; /* _hoops_RSRPI */

			case Quantization_THRESHOLD: {
				do {
					int						_hoops_CIRPI = _hoops_SIRPI;
					RGBAS32					pixel = _hoops_CAHSR::_hoops_SAHSR;

					in = (unsigned char const *)*_hoops_HCHIH++ + 4*hoffset;
					_hoops_RCRPI = in + 4*_hoops_PARSP;

					if (format == _hoops_HRSRH) pixel.a = *in++;
					pixel.r = *in++;
					pixel.g = *in++;
					pixel.b = *in++;
					if (format == Image_RGBA32) pixel.a = *in++;

					_hoops_RGGA (in == _hoops_RCRPI) {
						_hoops_RGGA (in == _hoops_RCRPI || pixel.a != 0) {
							++_hoops_CIRPI;

							if (format == _hoops_HRSRH) pixel.a = *in++;
							pixel.r = *in++;
							pixel.g = *in++;
							pixel.b = *in++;
							if (format == Image_RGBA32) pixel.a = *in++;
						}

						if (in == _hoops_RCRPI) break;

						_hoops_SCGCR = _hoops_GAAC;

						_hoops_RGGA (in == _hoops_RCRPI || pixel.a == 0) {
							color.number = _hoops_ARAPI (pixel.r) * _hoops_CCRPI.r + 0x8000;
							index = color._hoops_CAGCR._hoops_SAGCR;
							color.number = _hoops_ARAPI (pixel.g) * _hoops_CCRPI.g + 0x8000;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;
							color.number = _hoops_ARAPI (pixel.b) * _hoops_CCRPI.b + 0x8000;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

							*_hoops_SCGCR++ = index + dc->_hoops_RHGCR;

							if (format == _hoops_HRSRH) pixel.a = *in++;
							pixel.r = *in++;
							pixel.g = *in++;
							pixel.b = *in++;
							if (format == Image_RGBA32) pixel.a = *in++;
						}

						start.x = _hoops_HCGCR->x + _hoops_CIRPI;
						end.x = start.x + (_hoops_SCGCR - _hoops_GAAC) - 1;
						if (pattern == FP_SOLID)
							_hoops_RRCGH (nr, &start, &end, 0, _hoops_GAAC);
						else
							_hoops_RRAPI (nr, &start, &end, _hoops_GAAC, pattern, contrast_color);

						_hoops_CIRPI += _hoops_SCGCR - _hoops_GAAC;
					}
					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
			}	break; /* _hoops_ASRPI */

			case Quantization_ERROR_DIFFUSION: {
				_hoops_SGGCR alter	*_hoops_PSRPI[2];
				int					row = 0;

				ALLOC_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, _hoops_SGGCR);
				ALLOC_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, _hoops_SGGCR);

				{
					int				_hoops_ICRHH;
					for (_hoops_ICRHH = 0; _hoops_ICRHH < _hoops_PARSP + 2; ++_hoops_ICRHH)
						_hoops_PSRPI[0][_hoops_ICRHH].r = _hoops_PSRPI[0][_hoops_ICRHH].g = _hoops_PSRPI[0][_hoops_ICRHH].b =
							_hoops_PSRPI[1][_hoops_ICRHH].r = _hoops_PSRPI[1][_hoops_ICRHH].g = _hoops_PSRPI[1][_hoops_ICRHH].b = 0;
				}

				do {
					_hoops_SGGCR alter		*_hoops_HSRPI, *_hoops_ISRPI;
					_hoops_SGGCR alter		*_hoops_CSRPI, *_hoops_SSRPI, *_hoops_GGAPI;
					int					_hoops_CIRPI = _hoops_SIRPI;
					RGBAS32				pixel = _hoops_CAHSR::_hoops_SAHSR;

					in = (unsigned char const *)*_hoops_HCHIH++ + 4*hoffset;
					_hoops_RCRPI = in + 4*_hoops_PARSP;

					_hoops_HSRPI = &_hoops_PSRPI[row][0];
					_hoops_ISRPI = &_hoops_PSRPI[row][1];
					row = 1-row;
					_hoops_CSRPI = &_hoops_PSRPI[row][0];
					_hoops_SSRPI = &_hoops_PSRPI[row][1];
					_hoops_GGAPI = &_hoops_PSRPI[row][2];

					if (format == _hoops_HRSRH) pixel.a = *in++;
					pixel.r = *in++;
					pixel.g = *in++;
					pixel.b = *in++;
					if (format == Image_RGBA32) pixel.a = *in++;

					_hoops_RGGA (in == _hoops_RCRPI) {
						_hoops_RGGA (in == _hoops_RCRPI || pixel.a != 0) {
							++_hoops_CIRPI;

							_hoops_ISRPI->r = _hoops_ISRPI->g = _hoops_ISRPI->b = 0;

							_hoops_HSRPI = _hoops_ISRPI++;
							_hoops_CSRPI = _hoops_SSRPI;
							_hoops_SSRPI = _hoops_GGAPI++;

							if (format == _hoops_HRSRH) pixel.a = *in++;
							pixel.r = *in++;
							pixel.g = *in++;
							pixel.b = *in++;
							if (format == Image_RGBA32) pixel.a = *in++;
						}

						if (in == _hoops_RCRPI) break;

						_hoops_SCGCR = _hoops_GAAC;

						do {
							color.number = _hoops_CCRPI.r * _hoops_PCGCR (pixel.r) +
								(_hoops_HSRPI->r * 7 + _hoops_GGAPI->r * 3 + _hoops_SSRPI->r * 5 + _hoops_CSRPI->r) / 16;
							if (color.number < 0) color.number = 0;
							else if (color.number >= 0x01000000) color.number = 0x01000000;
							_hoops_ISRPI->r = color.number;
							color.number += 0x8000;
							color._hoops_CAGCR._hoops_RCGCR = 0;
							_hoops_ISRPI->r -= color.number;
							index = color._hoops_CAGCR._hoops_SAGCR;

							color.number = _hoops_CCRPI.g * _hoops_PCGCR (pixel.g) +
								(_hoops_HSRPI->g * 7 + _hoops_GGAPI->g * 3 + _hoops_SSRPI->g * 5 + _hoops_CSRPI->g) / 16;
							if (color.number < 0) color.number = 0;
							else if (color.number >= 0x01000000) color.number = 0x01000000;
							_hoops_ISRPI->g = color.number;
							color.number += 0x8000;
							color._hoops_CAGCR._hoops_RCGCR = 0;
							_hoops_ISRPI->g -= color.number;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;

							color.number = _hoops_CCRPI.b * _hoops_PCGCR (pixel.b) +
								(_hoops_HSRPI->b * 7 + _hoops_GGAPI->b * 3 + _hoops_SSRPI->b * 5 + _hoops_CSRPI->b) / 16;
							if (color.number < 0) color.number = 0;
							else if (color.number >= 0x01000000) color.number = 0x01000000;
							_hoops_ISRPI->b = color.number;
							color.number += 0x8000;
							color._hoops_CAGCR._hoops_RCGCR = 0;
							_hoops_ISRPI->b -= color.number;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

							*_hoops_SCGCR++ = index + dc->_hoops_RHGCR;

							_hoops_HSRPI = _hoops_ISRPI++;
							_hoops_CSRPI = _hoops_SSRPI;
							_hoops_SSRPI = _hoops_GGAPI++;

							if (in == _hoops_RCRPI) break;

							if (format == _hoops_HRSRH) pixel.a = *in++;
							pixel.r = *in++;
							pixel.g = *in++;
							pixel.b = *in++;
							if (format == Image_RGBA32) pixel.a = *in++;
						} while (pixel.a != 0);

						start.x = _hoops_HCGCR->x + _hoops_CIRPI;
						end.x = start.x + (_hoops_SCGCR - _hoops_GAAC) - 1;

						if (pattern == FP_SOLID)
							_hoops_RRCGH (nr, &start, &end, 0, _hoops_GAAC);
						else
							_hoops_RRAPI (nr, &start, &end, _hoops_GAAC, pattern, contrast_color);

						_hoops_CIRPI += _hoops_SCGCR - _hoops_GAAC;
					}
					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));

				FREE_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, _hoops_SGGCR);
				FREE_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, _hoops_SGGCR);
			}	break; /* _hoops_RGAPI */
		  } /* _hoops_RSGR _hoops_IIGR _hoops_CICA (_hoops_CCH) */
	  }	  break; /* _hoops_HGAPI/_hoops_IGAPI */
	}

	if (_hoops_GAAC != null) FREE_ARRAY (_hoops_GAAC, _hoops_PARSP, unsigned short);
#endif
}
#if _MSC_VER >= 1300
#pragma optimize("", on)
#endif




#ifndef DISABLE_MAPPED8_RASTERS

local void _hoops_HRAPI (
	Net_Rendition const &		nr,
	DC_Point const *			_hoops_HCGCR,
	DC_Point const *			_hoops_ICGCR,
	unsigned char alter *		_hoops_GAAC,
	int							pattern,
	Driver_Color const *		contrast_color) {
	Display_Context const *		dc = nr->_hoops_SRA;
	int							row;
	int							col;
	unsigned char alter *		_hoops_SCGCR;
	unsigned char alter *		_hoops_HSGCR;

	if (pattern != FP_USER_DEFINED) {
		int						_hoops_RIRPI;
		int const				*_hoops_AIRPI;

		row = (int)_hoops_HCGCR->y & (dc->_hoops_ASPGH-1);
		if (dc->_hoops_CCAGH)
			row = dc->_hoops_ASPGH - 1 - row;
		col = (int)_hoops_HCGCR->x & (dc->_hoops_ASPGH-1);

		if (dc->_hoops_ASPGH == 4) {
			_hoops_RIRPI = ((unsigned char const *)(dc->_hoops_GRPH[pattern]))[row];
			_hoops_AIRPI = HOOPS_READ_ONLY.incr_mod_4;
		}
		else if (dc->_hoops_ASPGH == 8) {
			_hoops_RIRPI = ((unsigned char const *)(dc->_hoops_GRPH[pattern]))[row];
			_hoops_AIRPI = HOOPS_READ_ONLY._hoops_PCHGI;
		}
		else if (dc->_hoops_ASPGH == 16) {
			_hoops_RIRPI = ((unsigned short const *)(dc->_hoops_GRPH[pattern]))[row];
			_hoops_AIRPI = HOOPS_READ_ONLY._hoops_HCHGI;
		}
		else {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Bit patterns have not been loaded.");
			return;
		}

		_hoops_SCGCR = _hoops_GAAC;
		_hoops_HSGCR = _hoops_SCGCR + ((int)_hoops_ICGCR->x - (int)_hoops_HCGCR->x + 1);

		do {
			if (BIT (_hoops_RIRPI, HOOPS_READ_ONLY._hoops_ICHGI[col]))
				*_hoops_SCGCR = (unsigned char)contrast_color->_hoops_PGGCR;
			col = _hoops_AIRPI[col];
		} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

		_hoops_GRCGH (nr, _hoops_HCGCR, _hoops_ICGCR, 0, _hoops_GAAC);
	}
	else {
		unsigned char const *		_hoops_RIRPI;
		_hoops_SIHHP const *	up = nr->_hoops_IHA->_hoops_PGPH;

		if (up->pattern == null) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "User-defined pattern requested but not defined");
			return;
		}

		row = (int)_hoops_HCGCR->y % up->height;
		if (up->_hoops_RCHHP)
			row = up->height - 1 - row;
		col = (int)_hoops_HCGCR->x % up->width;

		_hoops_RIRPI = &up->pattern[row * up->width];

		_hoops_SCGCR = _hoops_GAAC;
		_hoops_HSGCR = _hoops_SCGCR + ((int)_hoops_ICGCR->x - (int)_hoops_HCGCR->x + 1);

		switch (up->_hoops_ACHHP) {
			case UPAT_NORMAL:
			default: {
				do {
					if (_hoops_RIRPI[col])
						*_hoops_SCGCR = (unsigned char)contrast_color->_hoops_PGGCR;
					if (++col == up->width) col = 0;
				} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

				_hoops_GRCGH (nr, _hoops_HCGCR, _hoops_ICGCR, 0, _hoops_GAAC);
			}	break;

			case UPAT_NO_FACE: {
				int				_hoops_CIRPI = 0;
				DC_Point		start, end;

				/* _hoops_SISR _hoops_GIR _hoops_GGR _hoops_HAPR */
				start.y = _hoops_HCGCR->y;
				start.z = _hoops_HCGCR->z;
				end.y = _hoops_ICGCR->y;
				end.z = _hoops_ICGCR->z;

				_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR) {
					_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR || _hoops_RIRPI[col]) {
						++_hoops_CIRPI;
						++_hoops_SCGCR;
						if (++col == up->width) col = 0;
					}

					if (_hoops_SCGCR == _hoops_HSGCR) break;
					_hoops_GAAC = _hoops_SCGCR;		/* _hoops_SAHR _hoops_GRP _hoops_SCH _hoops_GAR _hoops_IRS _hoops_SPCS _hoops_SRHR */

					_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR || !_hoops_RIRPI[col]) {
						*_hoops_SCGCR = (unsigned char)contrast_color->_hoops_PGGCR;
						++_hoops_SCGCR;
						if (++col == up->width) col = 0;
					}

					start.x = _hoops_HCGCR->x + _hoops_CIRPI;
					end.x = start.x + (_hoops_SCGCR - _hoops_GAAC) - 1;

					_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);

					_hoops_CIRPI += _hoops_SCGCR - _hoops_GAAC;
				}
			}	break;

			case UPAT_NO_CONTRAST: {
				int				_hoops_CIRPI = 0;
				DC_Point		start, end;

				/* _hoops_SISR _hoops_GIR _hoops_GGR _hoops_HAPR */
				start.y = _hoops_HCGCR->y;
				start.z = _hoops_HCGCR->z;
				end.y = _hoops_ICGCR->y;
				end.z = _hoops_ICGCR->z;

				_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR) {
					_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR || !_hoops_RIRPI[col]) {
						++_hoops_CIRPI;
						++_hoops_SCGCR;
						if (++col == up->width) col = 0;
					}

					if (_hoops_SCGCR == _hoops_HSGCR) break;
					_hoops_GAAC = _hoops_SCGCR;		/* _hoops_SAHR _hoops_GRP _hoops_SCH _hoops_GAR _hoops_IRS _hoops_SPCS _hoops_SRHR */

					_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR || _hoops_RIRPI[col]) {
						++_hoops_SCGCR;
						if (++col == up->width) col = 0;
					}

					start.x = _hoops_HCGCR->x + _hoops_CIRPI;
					end.x = start.x + (_hoops_SCGCR - _hoops_GAAC) - 1;

					_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);

					_hoops_CIRPI += _hoops_SCGCR - _hoops_GAAC;
				}
			}	break;
		}
	}
}


#define _hoops_PCGCR(x)			_hoops_IRGCR(x)
#define _hoops_ARAPI(x)			_hoops_SIRGI(x)

#endif

#if _MSC_VER >= 1300
#pragma optimize("", off)
#endif

GLOBAL_FUNCTION void HD_Image_To_Mapped8_Rasters (
	Net_Rendition const	&		nr,
	DC_Point const *			_hoops_HCGCR,
	DC_Point const *			_hoops_ICGCR,
	int							hoffset,
	Image_Format				format,
	int							row_bytes,
	void const * const *		_hoops_HCHIH,
	int							pattern,
	Driver_Color const *		contrast_color,
	Image const *				db_image) {
#ifndef DISABLE_MAPPED8_RASTERS
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	DC_Point					start;
	DC_Point					end;
	unsigned char alter *		_hoops_GAAC = null;
	unsigned char alter *		_hoops_SCGCR;
	unsigned char alter *		_hoops_HSGCR;
	int							_hoops_PARSP = (int)(_hoops_ICGCR->x - _hoops_HCGCR->x) + 1;
	int							vcount = (int)(_hoops_HCGCR->y - _hoops_ICGCR->y) + 1;
	int							_hoops_SIRPI = 0;
	Quantization_Flags			mode = _hoops_RRGH->_hoops_SIRAP;
	Driver_Color const *		_hoops_HGIHP = contrast_color;
	Driver_Color alter			_hoops_IRAPI;

	UNREFERENCED(db_image);


	start.x = _hoops_HCGCR->x;
	start.y = _hoops_HCGCR->y;
	start.z = _hoops_HCGCR->z;

	end.x = _hoops_ICGCR->x;
	end.y = _hoops_ICGCR->y;
	end.z = _hoops_ICGCR->z;

	Int_Rectangle const & _hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

	if (_hoops_GPHH.left > start.x) {
		if (_hoops_GPHH.left > end.x)
			return;
		int delta = _hoops_GPHH.left - start.x;
		_hoops_SIRPI += delta;
		_hoops_PARSP -= delta;
		start.x = _hoops_GPHH.left;
	}
	if (_hoops_GPHH.right < end.x) {
		if (_hoops_GPHH.right < start.x)
			return;
		int delta = end.x - _hoops_GPHH.right;
		_hoops_PARSP -= delta;
		end.x = _hoops_GPHH.right;
	}
	if (_hoops_GPHH.bottom > end.y) {
		if (_hoops_GPHH.bottom > start.y)
			return;
		int delta = _hoops_GPHH.bottom - end.y;
		vcount -= delta;
		//_hoops_RSGR._hoops_HAPC = _hoops_HSPH._hoops_PRPC;
	}
	if (_hoops_GPHH.top < start.y) {
		if (_hoops_GPHH.top < end.y)
			return;
		int delta = start.y - _hoops_GPHH.top;
		vcount -= delta;
		_hoops_HCHIH += delta;
		start.y = _hoops_GPHH.top;
	}

	end.y = start.y;

	/* _hoops_RPP _hoops_CIIA _hoops_HRGR _hoops_HGGPA, _hoops_HRRGR _hoops_RCGRA _hoops_ARCR _hoops_CIHA _hoops_CGARA _hoops_HAIR */
	if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR && pattern != FP_SOLID) {
		_hoops_SGGCR				_hoops_PRAPI;
		_hoops_SGGCR			_hoops_CCRPI;
		_hoops_CRRRH			color;
		int					index;

		_hoops_PRAPI.r = dc->_hoops_AGPGH.r;
		_hoops_PRAPI.g = dc->_hoops_AGPGH.g;
		_hoops_PRAPI.b = dc->_hoops_AGPGH.b;
		_hoops_CCRPI.r = 0x00010000 * (_hoops_PRAPI.r - 1) / 255;
		_hoops_CCRPI.g = 0x00010000 * (_hoops_PRAPI.g - 1) / 255;
		_hoops_CCRPI.b = 0x00010000 * (_hoops_PRAPI.b - 1) / 255;

		color.number = _hoops_PCGCR (contrast_color->_hoops_HRIR.r) * _hoops_CCRPI.r + 0x8000;
		index = color._hoops_CAGCR._hoops_SAGCR;
		color.number = _hoops_PCGCR (contrast_color->_hoops_HRIR.g) * _hoops_CCRPI.g + 0x8000;
		index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;
		color.number = _hoops_PCGCR (contrast_color->_hoops_HRIR.b) * _hoops_CCRPI.b + 0x8000;
		index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

		_hoops_IRAPI._hoops_PGGCR = index + dc->_hoops_RHGCR;
		_hoops_HGIHP = &_hoops_IRAPI;
	}

	switch (format) {
	  case Image_MAPPED_8: {
		  if (BIT(dc->_hoops_PGCC.flags , _hoops_IAPGH)) {
			  /*
			   * _hoops_PS _hoops_GHCA _hoops_SHH _hoops_APRS _hoops_GPP _hoops_IRS _hoops_SCGH _hoops_SISS _hoops_ACCAR
			   * _hoops_IS _hoops_SHH _hoops_IRS _hoops_PPPSR _hoops_SISS, _hoops_GGR _hoops_PGAP _hoops_AGIR _hoops_RIPGH
			   * _hoops_RSAS'_hoops_RA _hoops_PIGS, _hoops_GGR _hoops_PGAP _hoops_AGIR _hoops_RGR _hoops_CSCR _hoops_PIHA _hoops_SHH _hoops_CRAPI...
			   */
			  unsigned char const *	in;
			  _hoops_CRRRH			color;
			  int					index;
			  _hoops_SGGCR				_hoops_PRAPI;
			  _hoops_SGGCR				_hoops_CCRPI;
			  Driver_Color const *	_hoops_SPRAR;

			  _hoops_SPRAR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_AHHHP;

			  ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, unsigned char);

			  _hoops_PRAPI.r = dc->_hoops_AGPGH.r;
			  _hoops_PRAPI.g = dc->_hoops_AGPGH.g;
			  _hoops_PRAPI.b = dc->_hoops_AGPGH.b;
			  _hoops_CCRPI.r = 0x00010000 * (_hoops_PRAPI.r - 1) / 255;
			  _hoops_CCRPI.g = 0x00010000 * (_hoops_PRAPI.g - 1) / 255;
			  _hoops_CCRPI.b = 0x00010000 * (_hoops_PRAPI.b - 1) / 255;

			  switch (mode) {
				case Quantization_DITHER: {
					do {
						int						row;
						int						col;
						unsigned short const	*_hoops_IHGCR;

						in = (unsigned char const *)*_hoops_HCHIH++ + hoffset;
						_hoops_SCGCR = _hoops_GAAC;
						_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

						row = (int)start.y & 7;
						col = (int)start.x & 7;
						_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row];

						do {
							Integer32 const _hoops_CPGCR = _hoops_IHGCR[col];

							color.number = _hoops_ARAPI (_hoops_SPRAR[*in]._hoops_HRIR.r) * _hoops_CCRPI.r + _hoops_CPGCR;
							index = color._hoops_CAGCR._hoops_SAGCR;
							color.number = _hoops_ARAPI (_hoops_SPRAR[*in]._hoops_HRIR.g) * _hoops_CCRPI.g + _hoops_CPGCR;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;
							color.number = _hoops_ARAPI (_hoops_SPRAR[*in]._hoops_HRIR.b) * _hoops_CCRPI.b + _hoops_CPGCR;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

							*_hoops_SCGCR = index + dc->_hoops_RHGCR;
							++in;
							col = HOOPS_READ_ONLY._hoops_PCHGI[col];
						} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

						_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);

						end.y = --start.y;
					} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
				}	break; /* _hoops_RSRPI */

				case Quantization_THRESHOLD: {
					do {
						in = (unsigned char const *)*_hoops_HCHIH++ + hoffset;
						_hoops_SCGCR = _hoops_GAAC;
						_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

						do {
							color.number = _hoops_PCGCR (_hoops_SPRAR[*in]._hoops_HRIR.r) * _hoops_CCRPI.r + 0x8000;
							index = color._hoops_CAGCR._hoops_SAGCR;
							color.number = _hoops_PCGCR (_hoops_SPRAR[*in]._hoops_HRIR.g) * _hoops_CCRPI.g + 0x8000;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;
							color.number = _hoops_PCGCR (_hoops_SPRAR[*in]._hoops_HRIR.b) * _hoops_CCRPI.b + 0x8000;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;
							*_hoops_SCGCR = index + dc->_hoops_RHGCR;
							++in;
						} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

						_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);

						end.y = --start.y;
					} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
				}	break; /* _hoops_ASRPI */

				case Quantization_ERROR_DIFFUSION: {
					_hoops_SGGCR alter	*	_hoops_PSRPI[2];
					int					row = 0;

					ALLOC_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, _hoops_SGGCR);
					ALLOC_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, _hoops_SGGCR);

					{
						int				_hoops_ICRHH;
						for (_hoops_ICRHH = 0; _hoops_ICRHH < _hoops_PARSP + 2; ++_hoops_ICRHH)
							_hoops_PSRPI[0][_hoops_ICRHH].r = _hoops_PSRPI[0][_hoops_ICRHH].g = _hoops_PSRPI[0][_hoops_ICRHH].b =
								_hoops_PSRPI[1][_hoops_ICRHH].r = _hoops_PSRPI[1][_hoops_ICRHH].g = _hoops_PSRPI[1][_hoops_ICRHH].b = 0;
					}

					do {
						_hoops_SGGCR alter	*_hoops_HSRPI, *_hoops_ISRPI;
						_hoops_SGGCR alter	*_hoops_CSRPI, *_hoops_SSRPI, *_hoops_GGAPI;

						in = (unsigned char const *)*_hoops_HCHIH++ + hoffset;
						_hoops_SCGCR = _hoops_GAAC;
						_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

						_hoops_HSRPI = &_hoops_PSRPI[row][0];
						_hoops_ISRPI = &_hoops_PSRPI[row][1];
						row = 1-row;
						_hoops_CSRPI = &_hoops_PSRPI[row][0];
						_hoops_SSRPI = &_hoops_PSRPI[row][1];
						_hoops_GGAPI = &_hoops_PSRPI[row][2];

						do {
							color.number = _hoops_CCRPI.r * _hoops_PCGCR (_hoops_SPRAR[*in]._hoops_HRIR.r) +
								(_hoops_HSRPI->r * 7 + _hoops_GGAPI->r * 3 + _hoops_SSRPI->r * 5 + _hoops_CSRPI->r) / 16;
							if (color.number < 0) color.number = 0;
							else if (color.number >= 0x01000000) color.number = 0x01000000;
							_hoops_ISRPI->r = color.number;
							color.number += 0x8000;
							color._hoops_CAGCR._hoops_RCGCR = 0;
							_hoops_ISRPI->r -= color.number;
							index = color._hoops_CAGCR._hoops_SAGCR;

							color.number = _hoops_CCRPI.g * _hoops_PCGCR (_hoops_SPRAR[*in]._hoops_HRIR.g) +
								(_hoops_HSRPI->g * 7 + _hoops_GGAPI->g * 3 + _hoops_SSRPI->g * 5 + _hoops_CSRPI->g) / 16;
							if (color.number < 0) color.number = 0;
							else if (color.number >= 0x01000000) color.number = 0x01000000;
							_hoops_ISRPI->g = color.number;
							color.number += 0x8000;
							color._hoops_CAGCR._hoops_RCGCR = 0;
							_hoops_ISRPI->g -= color.number;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;

							color.number = _hoops_CCRPI.b * _hoops_PCGCR (_hoops_SPRAR[*in]._hoops_HRIR.b) +
								(_hoops_HSRPI->b * 7 + _hoops_GGAPI->b * 3 + _hoops_SSRPI->b * 5 + _hoops_CSRPI->b) / 16;
							if (color.number < 0) color.number = 0;
							else if (color.number >= 0x01000000) color.number = 0x01000000;
							_hoops_ISRPI->b = color.number;
							color.number += 0x8000;
							color._hoops_CAGCR._hoops_RCGCR = 0;
							_hoops_ISRPI->b -= color.number;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

							*_hoops_SCGCR = index + dc->_hoops_RHGCR;
							++in;

							_hoops_HSRPI = _hoops_ISRPI++;
							_hoops_CSRPI = _hoops_SSRPI;
							_hoops_SSRPI = _hoops_GGAPI++;
						} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

						_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);

						end.y = --start.y;
					} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));

					FREE_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, _hoops_SGGCR);
					FREE_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, _hoops_SGGCR);
				}	break; /* _hoops_RGAPI */
			  } /* _hoops_RSGR _hoops_IIGR _hoops_CICA (_hoops_CCH) */
		  }

		  else if (nr->_hoops_ASIR->_hoops_PSIR->_hoops_RHHHP == 0 &&
				   pattern == FP_SOLID) do {
			  unsigned char const		*_hoops_GCRPI;
			  unsigned char const		*_hoops_RSGHR;
			  unsigned char const		*next;
			  int						_hoops_AAGHR;

			  _hoops_RSGHR = (unsigned char const *)*_hoops_HCHIH + hoffset;
			  _hoops_AAGHR = _hoops_IICIA;
			  _hoops_GCRPI = _hoops_RSGHR;
			  while (--vcount > 0 &&
					 (_hoops_RSGHR + row_bytes ==
					  (next = (unsigned char const *)*++_hoops_HCHIH + hoffset)) &&
					 _hoops_AAGHR >= row_bytes) {
				  _hoops_RSGHR = next;
				  --end.y;
				  _hoops_AAGHR -= row_bytes;
			  }
			  _hoops_GRCGH (nr, &start, &end, row_bytes, _hoops_GCRPI);
			  start.y = --end.y;
		  } _hoops_RGGA (vcount <= 0 || _hoops_GGPGR(nr));

		  else {
			  short			_hoops_SPRAR;

			  _hoops_SPRAR = (short)nr->_hoops_ASIR->_hoops_PSIR->_hoops_RHHHP;
			  ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, unsigned char);

			  do {
				  unsigned char const *in;

				  in = (unsigned char const *)*_hoops_HCHIH++ + hoffset;
				  _hoops_SCGCR = _hoops_GAAC;
				  _hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

				  do *_hoops_SCGCR++ = _hoops_SPRAR + *in++;
				  _hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR);

				  if (pattern == FP_SOLID)
					  _hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);
				  else
					  _hoops_HRAPI (nr, &start, &end, _hoops_GAAC, pattern, _hoops_HGIHP);

				  end.y = --start.y;
			  } _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
		  }
	  }	  break; /* _hoops_APCC */


	  case Image_MAPPED_16: {
		  ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, unsigned char);

		  if (nr->_hoops_ASIR->_hoops_PSIR->_hoops_RHHHP == 0) do {
			  unsigned short const	*in;

			  in = (unsigned short const *)*_hoops_HCHIH++ + hoffset;
			  _hoops_SCGCR = _hoops_GAAC;
			  _hoops_HSGCR = _hoops_GAAC + _hoops_PARSP;

			  do *_hoops_SCGCR++ = (unsigned char)*in++;
			  _hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR);

			  _hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);

			  end.y = --start.y;
		  } _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));

		  else {
			  short			_hoops_SPRAR;

			  _hoops_SPRAR = (short)nr->_hoops_ASIR->_hoops_PSIR->_hoops_RHHHP;

			  do {
				  unsigned short const	*in;

				  in = (unsigned short const *)*_hoops_HCHIH++ + hoffset;
				  _hoops_SCGCR = _hoops_GAAC;
				  _hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

				  do *_hoops_SCGCR++ = _hoops_SPRAR + (short)*in++;
				  _hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR);

				  _hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);

				  end.y = --start.y;
			  } _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
		  }
	  }	  break; /* _hoops_PPCC */


	  case _hoops_HHGH: {
		  _hoops_SHGH const		*in;
		  _hoops_CRRRH			color;
		  int						index;
		  _hoops_SGGCR				_hoops_PRAPI;
		  _hoops_SGGCR			_hoops_CCRPI;

		  ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, unsigned char);

		  _hoops_PRAPI.r = dc->_hoops_AGPGH.r;
		  _hoops_PRAPI.g = dc->_hoops_AGPGH.g;
		  _hoops_PRAPI.b = dc->_hoops_AGPGH.b;
		  _hoops_CCRPI.r = 0x00010000 * (_hoops_PRAPI.r - 1) / 255;
		  _hoops_CCRPI.g = 0x00010000 * (_hoops_PRAPI.g - 1) / 255;
		  _hoops_CCRPI.b = 0x00010000 * (_hoops_PRAPI.b - 1) / 255;

		  switch (mode) {
			case Quantization_DITHER: {
				do {
					int						row;
					int						col;
					unsigned short const	*_hoops_IHGCR;

					in = (_hoops_SHGH const *)*_hoops_HCHIH++ + hoffset;
					_hoops_SCGCR = _hoops_GAAC;
					_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

					row = (int)start.y & 7;
					col = (int)start.x & 7;
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row];

					do {
						Integer32 const _hoops_CPGCR = _hoops_IHGCR[col];

						color.number = _hoops_ARAPI (in->r) * _hoops_CCRPI.r + _hoops_CPGCR;
						index = color._hoops_CAGCR._hoops_SAGCR;
						color.number = _hoops_ARAPI (in->g) * _hoops_CCRPI.g + _hoops_CPGCR;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;
						color.number = _hoops_ARAPI (in->b) * _hoops_CCRPI.b + _hoops_CPGCR;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

						*_hoops_SCGCR = index + dc->_hoops_RHGCR;
						++in;
						col = HOOPS_READ_ONLY._hoops_PCHGI[col];
					} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					if (pattern == FP_SOLID)
						_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);
					else
						_hoops_HRAPI (nr, &start, &end, _hoops_GAAC, pattern, _hoops_HGIHP);
					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
			}	break; /* _hoops_RSRPI */

			case Quantization_THRESHOLD: {
				do {
					in = (_hoops_SHGH const *)*_hoops_HCHIH++ + hoffset;
					_hoops_SCGCR = _hoops_GAAC;
					_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

					do {
						color.number = _hoops_PCGCR (in->r) * _hoops_CCRPI.r + 0x8000;
						index = color._hoops_CAGCR._hoops_SAGCR;
						color.number = _hoops_PCGCR (in->g) * _hoops_CCRPI.g + 0x8000;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;
						color.number = _hoops_PCGCR (in->b) * _hoops_CCRPI.b + 0x8000;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;
						*_hoops_SCGCR = index + dc->_hoops_RHGCR;
						++in;
					} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					if (pattern == FP_SOLID)
						_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);
					else
						_hoops_HRAPI (nr, &start, &end, _hoops_GAAC, pattern, _hoops_HGIHP);

					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
			}	break; /* _hoops_ASRPI */

			case Quantization_ERROR_DIFFUSION: {
				_hoops_SGGCR alter	*_hoops_PSRPI[2];
				int					row = 0;

				ALLOC_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, _hoops_SGGCR);
				ALLOC_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, _hoops_SGGCR);

				{
					int				_hoops_ICRHH;
					for (_hoops_ICRHH = 0; _hoops_ICRHH < _hoops_PARSP + 2; ++_hoops_ICRHH)
						_hoops_PSRPI[0][_hoops_ICRHH].r = _hoops_PSRPI[0][_hoops_ICRHH].g = _hoops_PSRPI[0][_hoops_ICRHH].b =
							_hoops_PSRPI[1][_hoops_ICRHH].r = _hoops_PSRPI[1][_hoops_ICRHH].g = _hoops_PSRPI[1][_hoops_ICRHH].b = 0;
				}

				do {
					_hoops_SGGCR alter	*_hoops_HSRPI, *_hoops_ISRPI;
					_hoops_SGGCR alter	*_hoops_CSRPI, *_hoops_SSRPI, *_hoops_GGAPI;

					in = (_hoops_SHGH const *)*_hoops_HCHIH++ + hoffset;
					_hoops_SCGCR = _hoops_GAAC;
					_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

					_hoops_HSRPI = &_hoops_PSRPI[row][0];
					_hoops_ISRPI = &_hoops_PSRPI[row][1];
					row = 1-row;
					_hoops_CSRPI = &_hoops_PSRPI[row][0];
					_hoops_SSRPI = &_hoops_PSRPI[row][1];
					_hoops_GGAPI = &_hoops_PSRPI[row][2];

					do {
						color.number = _hoops_CCRPI.r * _hoops_PCGCR (in->r) +
							(_hoops_HSRPI->r * 7 + _hoops_GGAPI->r * 3 + _hoops_SSRPI->r * 5 + _hoops_CSRPI->r) / 16;
						if (color.number < 0) color.number = 0;
						else if (color.number >= 0x01000000) color.number = 0x01000000;
						_hoops_ISRPI->r = color.number;
						color.number += 0x8000;
						color._hoops_CAGCR._hoops_RCGCR = 0;
						_hoops_ISRPI->r -= color.number;
						index = color._hoops_CAGCR._hoops_SAGCR;

						color.number = _hoops_CCRPI.g * _hoops_PCGCR (in->g) +
							(_hoops_HSRPI->g * 7 + _hoops_GGAPI->g * 3 + _hoops_SSRPI->g * 5 + _hoops_CSRPI->g) / 16;
						if (color.number < 0) color.number = 0;
						else if (color.number >= 0x01000000) color.number = 0x01000000;
						_hoops_ISRPI->g = color.number;
						color.number += 0x8000;
						color._hoops_CAGCR._hoops_RCGCR = 0;
						_hoops_ISRPI->g -= color.number;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;

						color.number = _hoops_CCRPI.b * _hoops_PCGCR (in->b) +
							(_hoops_HSRPI->b * 7 + _hoops_GGAPI->b * 3 + _hoops_SSRPI->b * 5 + _hoops_CSRPI->b) / 16;
						if (color.number < 0) color.number = 0;
						else if (color.number >= 0x01000000) color.number = 0x01000000;
						_hoops_ISRPI->b = color.number;
						color.number += 0x8000;
						color._hoops_CAGCR._hoops_RCGCR = 0;
						_hoops_ISRPI->b -= color.number;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

						*_hoops_SCGCR = index + dc->_hoops_RHGCR;
						++in;

						_hoops_HSRPI = _hoops_ISRPI++;
						_hoops_CSRPI = _hoops_SSRPI;
						_hoops_SSRPI = _hoops_GGAPI++;
					} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					if (pattern == FP_SOLID)
						_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);
					else
						_hoops_HRAPI (nr, &start, &end, _hoops_GAAC, pattern, _hoops_HGIHP);
					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));

				FREE_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, _hoops_SGGCR);
				FREE_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, _hoops_SGGCR);
			}	break; /* _hoops_RGAPI */
		  } /* _hoops_RSGR _hoops_IIGR _hoops_CICA (_hoops_CCH) */
	  }	  break; 

	  case _hoops_PGPGI: {
		  unsigned short const	*in;
		  _hoops_CRRRH			color;
		  int						index;
		  _hoops_SGGCR				_hoops_PRAPI;
		  _hoops_SGGCR			_hoops_CCRPI;

		  ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, unsigned char);

		  _hoops_PRAPI.r = dc->_hoops_AGPGH.r;
		  _hoops_PRAPI.g = dc->_hoops_AGPGH.g;
		  _hoops_PRAPI.b = dc->_hoops_AGPGH.b;
		  _hoops_CCRPI.r = 0x00010000 * (_hoops_PRAPI.r - 1) / 255;
		  _hoops_CCRPI.g = 0x00010000 * (_hoops_PRAPI.g - 1) / 255;
		  _hoops_CCRPI.b = 0x00010000 * (_hoops_PRAPI.b - 1) / 255;

		  switch (mode) {
			case Quantization_DITHER: {
				do {
					int						row;
					int						col;
					unsigned short const	*_hoops_IHGCR;

					in = (unsigned short const *)*_hoops_HCHIH++ + hoffset;
					_hoops_SCGCR = _hoops_GAAC;
					_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

					row = (int)start.y & 7;
					col = (int)start.x & 7;
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row];

					do {
						Integer32 const _hoops_CPGCR = _hoops_IHGCR[col];
						int				_hoops_CGRAH;

						_hoops_CGRAH = (*in >> 8) & 0x00FF;
						color.number = _hoops_CGRAH * _hoops_CCRPI.r + _hoops_CPGCR;
						index = color._hoops_CAGCR._hoops_SAGCR;
						color.number = _hoops_CGRAH * _hoops_CCRPI.g + _hoops_CPGCR;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;
						color.number = _hoops_CGRAH * _hoops_CCRPI.b + _hoops_CPGCR;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

						*_hoops_SCGCR = index + dc->_hoops_RHGCR;
						++in;
						col = HOOPS_READ_ONLY._hoops_PCHGI[col];
					} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					if (pattern == FP_SOLID)
						_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);
					else
						_hoops_HRAPI (nr, &start, &end, _hoops_GAAC, pattern, _hoops_HGIHP);
					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
			}	break; /* _hoops_RSRPI */

			case Quantization_THRESHOLD: {
				do {
					in = (unsigned short const *)*_hoops_HCHIH++ + hoffset;
					_hoops_SCGCR = _hoops_GAAC;
					_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

					do {
						int				_hoops_CGRAH;

						_hoops_CGRAH = (*in >> 8) & 0x00FF;
						color.number = _hoops_CGRAH * _hoops_CCRPI.r + 0x8000;
						index = color._hoops_CAGCR._hoops_SAGCR;
						color.number = _hoops_CGRAH * _hoops_CCRPI.g + 0x8000;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;
						color.number = _hoops_CGRAH * _hoops_CCRPI.b + 0x8000;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;
						*_hoops_SCGCR = index + dc->_hoops_RHGCR;
						++in;
					} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					if (pattern == FP_SOLID)
						_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);
					else
						_hoops_HRAPI (nr, &start, &end, _hoops_GAAC, pattern, _hoops_HGIHP);

					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
			}	break; /* _hoops_ASRPI */

			case Quantization_ERROR_DIFFUSION: {
				_hoops_SGGCR alter	*_hoops_PSRPI[2];
				int					row = 0;

				ALLOC_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, _hoops_SGGCR);
				ALLOC_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, _hoops_SGGCR);

				{
					int				_hoops_ICRHH;
					for (_hoops_ICRHH = 0; _hoops_ICRHH < _hoops_PARSP + 2; ++_hoops_ICRHH)
						_hoops_PSRPI[0][_hoops_ICRHH].r = _hoops_PSRPI[0][_hoops_ICRHH].g = _hoops_PSRPI[0][_hoops_ICRHH].b =
							_hoops_PSRPI[1][_hoops_ICRHH].r = _hoops_PSRPI[1][_hoops_ICRHH].g = _hoops_PSRPI[1][_hoops_ICRHH].b = 0;
				}

				do {
					_hoops_SGGCR alter	*_hoops_HSRPI, *_hoops_ISRPI;
					_hoops_SGGCR alter	*_hoops_CSRPI, *_hoops_SSRPI, *_hoops_GGAPI;

					in = (unsigned short const *)*_hoops_HCHIH++ + hoffset;
					_hoops_SCGCR = _hoops_GAAC;
					_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

					_hoops_HSRPI = &_hoops_PSRPI[row][0];
					_hoops_ISRPI = &_hoops_PSRPI[row][1];
					row = 1-row;
					_hoops_CSRPI = &_hoops_PSRPI[row][0];
					_hoops_SSRPI = &_hoops_PSRPI[row][1];
					_hoops_GGAPI = &_hoops_PSRPI[row][2];

					do {
						int				_hoops_CGRAH;

						_hoops_CGRAH = (*in >> 8) & 0x00FF;

						color.number = _hoops_CCRPI.r * _hoops_CGRAH +
							(_hoops_HSRPI->r * 7 + _hoops_GGAPI->r * 3 + _hoops_SSRPI->r * 5 + _hoops_CSRPI->r) / 16;
						if (color.number < 0) color.number = 0;
						else if (color.number >= 0x01000000) color.number = 0x01000000;
						_hoops_ISRPI->r = color.number;
						color.number += 0x8000;
						color._hoops_CAGCR._hoops_RCGCR = 0;
						_hoops_ISRPI->r -= color.number;
						index = color._hoops_CAGCR._hoops_SAGCR;

						color.number = _hoops_CCRPI.g * _hoops_CGRAH +
							(_hoops_HSRPI->g * 7 + _hoops_GGAPI->g * 3 + _hoops_SSRPI->g * 5 + _hoops_CSRPI->g) / 16;
						if (color.number < 0) color.number = 0;
						else if (color.number >= 0x01000000) color.number = 0x01000000;
						_hoops_ISRPI->g = color.number;
						color.number += 0x8000;
						color._hoops_CAGCR._hoops_RCGCR = 0;
						_hoops_ISRPI->g -= color.number;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;

						color.number = _hoops_CCRPI.b * _hoops_CGRAH +
							(_hoops_HSRPI->b * 7 + _hoops_GGAPI->b * 3 + _hoops_SSRPI->b * 5 + _hoops_CSRPI->b) / 16;
						if (color.number < 0) color.number = 0;
						else if (color.number >= 0x01000000) color.number = 0x01000000;
						_hoops_ISRPI->b = color.number;
						color.number += 0x8000;
						color._hoops_CAGCR._hoops_RCGCR = 0;
						_hoops_ISRPI->b -= color.number;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

						*_hoops_SCGCR = index + dc->_hoops_RHGCR;
						++in;

						_hoops_HSRPI = _hoops_ISRPI++;
						_hoops_CSRPI = _hoops_SSRPI;
						_hoops_SSRPI = _hoops_GGAPI++;
					} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					if (pattern == FP_SOLID)
						_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);
					else
						_hoops_HRAPI (nr, &start, &end, _hoops_GAAC, pattern, _hoops_HGIHP);
					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));

				FREE_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, _hoops_SGGCR);
				FREE_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, _hoops_SGGCR);
			}	break; /* _hoops_RGAPI */
		  } /* _hoops_RSGR _hoops_IIGR _hoops_CICA (_hoops_CCH) */
	  }	  break; /* _hoops_SRAPI */

	  case _hoops_PCCRH: {
		  float const				*in;
		  _hoops_CRRRH			color;
		  int						index;
		  _hoops_SGGCR				_hoops_PRAPI;
		  _hoops_SGGCR			_hoops_CCRPI;

		  ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, unsigned char);

		  _hoops_PRAPI.r = dc->_hoops_AGPGH.r;
		  _hoops_PRAPI.g = dc->_hoops_AGPGH.g;
		  _hoops_PRAPI.b = dc->_hoops_AGPGH.b;
		  _hoops_CCRPI.r = 0x00010000 * (_hoops_PRAPI.r - 1) / 255;
		  _hoops_CCRPI.g = 0x00010000 * (_hoops_PRAPI.g - 1) / 255;
		  _hoops_CCRPI.b = 0x00010000 * (_hoops_PRAPI.b - 1) / 255;

		  switch (mode) {
			case Quantization_DITHER: {
				do {
					int						row;
					int						col;
					unsigned short const	*_hoops_IHGCR;

					in = (float const *)*_hoops_HCHIH++ + hoffset;
					_hoops_SCGCR = _hoops_GAAC;
					_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

					row = (int)start.y & 7;
					col = (int)start.x & 7;
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row];

					do {
						Integer32 const	_hoops_CPGCR = _hoops_IHGCR[col];
						int					_hoops_CGRAH = (int)(*in++ * 0xff);

						color.number = _hoops_CGRAH * _hoops_CCRPI.r + _hoops_CPGCR;
						index = color._hoops_CAGCR._hoops_SAGCR;
						color.number = _hoops_CGRAH * _hoops_CCRPI.g + _hoops_CPGCR;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;
						color.number = _hoops_CGRAH * _hoops_CCRPI.b + _hoops_CPGCR;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

						*_hoops_SCGCR = index + dc->_hoops_RHGCR;
						col = HOOPS_READ_ONLY._hoops_PCHGI[col];
					} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					if (pattern == FP_SOLID)
						_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);
					else
						_hoops_HRAPI (nr, &start, &end, _hoops_GAAC, pattern, _hoops_HGIHP);
					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
			}	break; /* _hoops_RSRPI */

			case Quantization_THRESHOLD: {
				do {
					in = (float const *)*_hoops_HCHIH++ + hoffset;
					_hoops_SCGCR = _hoops_GAAC;
					_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

					do {
						int				_hoops_CGRAH = (int)(*in++ * 0xff);

						color.number = _hoops_CGRAH * _hoops_CCRPI.r + 0x8000;
						index = color._hoops_CAGCR._hoops_SAGCR;
						color.number = _hoops_CGRAH * _hoops_CCRPI.g + 0x8000;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;
						color.number = _hoops_CGRAH * _hoops_CCRPI.b + 0x8000;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;
						*_hoops_SCGCR = index + dc->_hoops_RHGCR;
					} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					if (pattern == FP_SOLID)
						_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);
					else
						_hoops_HRAPI (nr, &start, &end, _hoops_GAAC, pattern, _hoops_HGIHP);

					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
			}	break; /* _hoops_ASRPI */

			case Quantization_ERROR_DIFFUSION: {
				_hoops_SGGCR alter	*_hoops_PSRPI[2];
				int					row = 0;

				ALLOC_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, _hoops_SGGCR);
				ALLOC_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, _hoops_SGGCR);

				{
					int				_hoops_ICRHH;
					for (_hoops_ICRHH = 0; _hoops_ICRHH < _hoops_PARSP + 2; ++_hoops_ICRHH)
						_hoops_PSRPI[0][_hoops_ICRHH].r = _hoops_PSRPI[0][_hoops_ICRHH].g = _hoops_PSRPI[0][_hoops_ICRHH].b =
							_hoops_PSRPI[1][_hoops_ICRHH].r = _hoops_PSRPI[1][_hoops_ICRHH].g = _hoops_PSRPI[1][_hoops_ICRHH].b = 0;
				}

				do {
					_hoops_SGGCR alter	*_hoops_HSRPI, *_hoops_ISRPI;
					_hoops_SGGCR alter	*_hoops_CSRPI, *_hoops_SSRPI, *_hoops_GGAPI;

					in = (float const *)*_hoops_HCHIH++ + hoffset;
					_hoops_SCGCR = _hoops_GAAC;
					_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

					_hoops_HSRPI = &_hoops_PSRPI[row][0];
					_hoops_ISRPI = &_hoops_PSRPI[row][1];
					row = 1-row;
					_hoops_CSRPI = &_hoops_PSRPI[row][0];
					_hoops_SSRPI = &_hoops_PSRPI[row][1];
					_hoops_GGAPI = &_hoops_PSRPI[row][2];

					do {
						int				_hoops_CGRAH = (int)(*in++ * 0xff);

						color.number = _hoops_CCRPI.r * _hoops_CGRAH +
							(_hoops_HSRPI->r * 7 + _hoops_GGAPI->r * 3 + _hoops_SSRPI->r * 5 + _hoops_CSRPI->r) / 16;
						if (color.number < 0) color.number = 0;
						else if (color.number >= 0x01000000) color.number = 0x01000000;
						_hoops_ISRPI->r = color.number;
						color.number += 0x8000;
						color._hoops_CAGCR._hoops_RCGCR = 0;
						_hoops_ISRPI->r -= color.number;
						index = color._hoops_CAGCR._hoops_SAGCR;

						color.number = _hoops_CCRPI.g * _hoops_CGRAH +
							(_hoops_HSRPI->g * 7 + _hoops_GGAPI->g * 3 + _hoops_SSRPI->g * 5 + _hoops_CSRPI->g) / 16;
						if (color.number < 0) color.number = 0;
						else if (color.number >= 0x01000000) color.number = 0x01000000;
						_hoops_ISRPI->g = color.number;
						color.number += 0x8000;
						color._hoops_CAGCR._hoops_RCGCR = 0;
						_hoops_ISRPI->g -= color.number;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;

						color.number = _hoops_CCRPI.b * _hoops_CGRAH +
							(_hoops_HSRPI->b * 7 + _hoops_GGAPI->b * 3 + _hoops_SSRPI->b * 5 + _hoops_CSRPI->b) / 16;
						if (color.number < 0) color.number = 0;
						else if (color.number >= 0x01000000) color.number = 0x01000000;
						_hoops_ISRPI->b = color.number;
						color.number += 0x8000;
						color._hoops_CAGCR._hoops_RCGCR = 0;
						_hoops_ISRPI->b -= color.number;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

						*_hoops_SCGCR = index + dc->_hoops_RHGCR;

						_hoops_HSRPI = _hoops_ISRPI++;
						_hoops_CSRPI = _hoops_SSRPI;
						_hoops_SSRPI = _hoops_GGAPI++;
					} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					if (pattern == FP_SOLID)
						_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);
					else
						_hoops_HRAPI (nr, &start, &end, _hoops_GAAC, pattern, _hoops_HGIHP);
					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));

				FREE_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, _hoops_SGGCR);
				FREE_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, _hoops_SGGCR);
			}	break; /* _hoops_RGAPI */
		  } /* _hoops_RSGR _hoops_IIGR _hoops_CICA (_hoops_CCH) */
	  }	  break; /* _hoops_GAAPI */

	  case _hoops_AGGSP: {
		  Integer32 const		*in;
		  _hoops_CRRRH			color;
		  int						index;
		  _hoops_SGGCR				_hoops_PRAPI;
		  _hoops_SGGCR			_hoops_CCRPI;

		  ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, unsigned char);

		  _hoops_PRAPI.r = dc->_hoops_AGPGH.r;
		  _hoops_PRAPI.g = dc->_hoops_AGPGH.g;
		  _hoops_PRAPI.b = dc->_hoops_AGPGH.b;
		  _hoops_CCRPI.r = 0x00010000 * (_hoops_PRAPI.r - 1) / 255;
		  _hoops_CCRPI.g = 0x00010000 * (_hoops_PRAPI.g - 1) / 255;
		  _hoops_CCRPI.b = 0x00010000 * (_hoops_PRAPI.b - 1) / 255;

		  switch (mode) {
			case Quantization_DITHER: {
				do {
					int						row;
					int						col;
					unsigned short const	*_hoops_IHGCR;

					in = (Integer32 const *)*_hoops_HCHIH++ + hoffset;
					_hoops_SCGCR = _hoops_GAAC;
					_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

					row = (int)start.y & 7;
					col = (int)start.x & 7;
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row];

					do {
						Integer32 const _hoops_CPGCR = _hoops_IHGCR[col];
						int				_hoops_CGRAH;

						_hoops_CGRAH = *in * 0xff;
						color.number = _hoops_CGRAH * _hoops_CCRPI.r + _hoops_CPGCR;
						index = color._hoops_CAGCR._hoops_SAGCR;
						color.number = _hoops_CGRAH * _hoops_CCRPI.g + _hoops_CPGCR;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;
						color.number = _hoops_CGRAH * _hoops_CCRPI.b + _hoops_CPGCR;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

						*_hoops_SCGCR = index + dc->_hoops_RHGCR;
						++in;
						col = HOOPS_READ_ONLY._hoops_PCHGI[col];
					} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					if (pattern == FP_SOLID)
						_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);
					else
						_hoops_HRAPI (nr, &start, &end, _hoops_GAAC, pattern, _hoops_HGIHP);
					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
			}	break; /* _hoops_RSRPI */

			case Quantization_THRESHOLD: {
				do {
					in = (Integer32 const *)*_hoops_HCHIH++ + hoffset;
					_hoops_SCGCR = _hoops_GAAC;
					_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

					do {
						int				_hoops_CGRAH;

						_hoops_CGRAH = *in * 0xff;
						color.number = _hoops_CGRAH * _hoops_CCRPI.r + 0x8000;
						index = color._hoops_CAGCR._hoops_SAGCR;
						color.number = _hoops_CGRAH * _hoops_CCRPI.g + 0x8000;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;
						color.number = _hoops_CGRAH * _hoops_CCRPI.b + 0x8000;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;
						*_hoops_SCGCR = index + dc->_hoops_RHGCR;
						++in;
					} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					if (pattern == FP_SOLID)
						_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);
					else
						_hoops_HRAPI (nr, &start, &end, _hoops_GAAC, pattern, _hoops_HGIHP);

					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
			}	break; /* _hoops_ASRPI */

			case Quantization_ERROR_DIFFUSION: {
				_hoops_SGGCR alter	*_hoops_PSRPI[2];
				int					row = 0;

				ALLOC_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, _hoops_SGGCR);
				ALLOC_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, _hoops_SGGCR);

				{
					int				_hoops_ICRHH;
					for (_hoops_ICRHH = 0; _hoops_ICRHH < _hoops_PARSP + 2; ++_hoops_ICRHH)
						_hoops_PSRPI[0][_hoops_ICRHH].r = _hoops_PSRPI[0][_hoops_ICRHH].g = _hoops_PSRPI[0][_hoops_ICRHH].b =
							_hoops_PSRPI[1][_hoops_ICRHH].r = _hoops_PSRPI[1][_hoops_ICRHH].g = _hoops_PSRPI[1][_hoops_ICRHH].b = 0;
				}

				do {
					_hoops_SGGCR alter	*_hoops_HSRPI, *_hoops_ISRPI;
					_hoops_SGGCR alter	*_hoops_CSRPI, *_hoops_SSRPI, *_hoops_GGAPI;

					in = (Integer32 const *)*_hoops_HCHIH++ + hoffset;
					_hoops_SCGCR = _hoops_GAAC;
					_hoops_HSGCR = _hoops_SCGCR + _hoops_PARSP;

					_hoops_HSRPI = &_hoops_PSRPI[row][0];
					_hoops_ISRPI = &_hoops_PSRPI[row][1];
					row = 1-row;
					_hoops_CSRPI = &_hoops_PSRPI[row][0];
					_hoops_SSRPI = &_hoops_PSRPI[row][1];
					_hoops_GGAPI = &_hoops_PSRPI[row][2];

					do {
						int				_hoops_CGRAH;

						_hoops_CGRAH = *in * 0xff;

						color.number = _hoops_CCRPI.r * _hoops_CGRAH +
							(_hoops_HSRPI->r * 7 + _hoops_GGAPI->r * 3 + _hoops_SSRPI->r * 5 + _hoops_CSRPI->r) / 16;
						if (color.number < 0) color.number = 0;
						else if (color.number >= 0x01000000) color.number = 0x01000000;
						_hoops_ISRPI->r = color.number;
						color.number += 0x8000;
						color._hoops_CAGCR._hoops_RCGCR = 0;
						_hoops_ISRPI->r -= color.number;
						index = color._hoops_CAGCR._hoops_SAGCR;

						color.number = _hoops_CCRPI.g * _hoops_CGRAH +
							(_hoops_HSRPI->g * 7 + _hoops_GGAPI->g * 3 + _hoops_SSRPI->g * 5 + _hoops_CSRPI->g) / 16;
						if (color.number < 0) color.number = 0;
						else if (color.number >= 0x01000000) color.number = 0x01000000;
						_hoops_ISRPI->g = color.number;
						color.number += 0x8000;
						color._hoops_CAGCR._hoops_RCGCR = 0;
						_hoops_ISRPI->g -= color.number;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;

						color.number = _hoops_CCRPI.b * _hoops_CGRAH +
							(_hoops_HSRPI->b * 7 + _hoops_GGAPI->b * 3 + _hoops_SSRPI->b * 5 + _hoops_CSRPI->b) / 16;
						if (color.number < 0) color.number = 0;
						else if (color.number >= 0x01000000) color.number = 0x01000000;
						_hoops_ISRPI->b = color.number;
						color.number += 0x8000;
						color._hoops_CAGCR._hoops_RCGCR = 0;
						_hoops_ISRPI->b -= color.number;
						index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

						*_hoops_SCGCR = index + dc->_hoops_RHGCR;
						++in;

						_hoops_HSRPI = _hoops_ISRPI++;
						_hoops_CSRPI = _hoops_SSRPI;
						_hoops_SSRPI = _hoops_GGAPI++;
					} _hoops_RGGA (++_hoops_SCGCR == _hoops_HSGCR);

					if (pattern == FP_SOLID)
						_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);
					else
						_hoops_HRAPI (nr, &start, &end, _hoops_GAAC, pattern, _hoops_HGIHP);
					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));

				FREE_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, _hoops_SGGCR);
				FREE_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, _hoops_SGGCR);
			}	break; /* _hoops_RGAPI */
		  } /* _hoops_RSGR _hoops_IIGR _hoops_CICA (_hoops_CCH) */
	  }	  break; /* _hoops_RAAPI */

	  case _hoops_CSGSP: {
		  RGBAS32 const		*in;
		  _hoops_CRRRH			color;
		  int						index;
		  _hoops_SGGCR				_hoops_PRAPI;
		  _hoops_SGGCR			_hoops_CCRPI;
		  RGBAS32 const		*_hoops_RCRPI;

		  ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, unsigned char);

		  _hoops_PRAPI.r = dc->_hoops_AGPGH.r;
		  _hoops_PRAPI.g = dc->_hoops_AGPGH.g;
		  _hoops_PRAPI.b = dc->_hoops_AGPGH.b;
		  _hoops_CCRPI.r = 0x00010000L * (_hoops_PRAPI.r - 1) / 255;
		  _hoops_CCRPI.g = 0x00010000L * (_hoops_PRAPI.g - 1) / 255;
		  _hoops_CCRPI.b = 0x00010000L * (_hoops_PRAPI.b - 1) / 255;

		  switch (mode) {
			case Quantization_DITHER: {
				do {
					int						row;
					int						col;
					unsigned short const	*_hoops_IHGCR;
					int						_hoops_CIRPI = _hoops_SIRPI;

					in = (RGBAS32 const *)*_hoops_HCHIH++ + hoffset;
					_hoops_RCRPI = in + _hoops_PARSP;

					row = (int)start.y & 7;
					col = (int)start.x & 7;
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row];

					_hoops_RGGA (in == _hoops_RCRPI) {
						_hoops_RGGA (in == _hoops_RCRPI || in->a != 0) {
							col = HOOPS_READ_ONLY._hoops_PCHGI[col];
							++_hoops_CIRPI;
							++in;
						}

						if (in == _hoops_RCRPI) break;

						_hoops_SCGCR = _hoops_GAAC;

						_hoops_RGGA (in == _hoops_RCRPI || in->a == 0) {
							Integer32 const _hoops_CPGCR = _hoops_IHGCR[col];

							color.number = _hoops_ARAPI (in->r) * _hoops_CCRPI.r + _hoops_CPGCR;
							index = color._hoops_CAGCR._hoops_SAGCR;
							color.number = _hoops_ARAPI (in->g) * _hoops_CCRPI.g + _hoops_CPGCR;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;
							color.number = _hoops_ARAPI (in->b) * _hoops_CCRPI.b + _hoops_CPGCR;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

							*_hoops_SCGCR++ = index + dc->_hoops_RHGCR;
							++in;
							col = HOOPS_READ_ONLY._hoops_PCHGI[col];
						}

						start.x = _hoops_HCGCR->x + _hoops_CIRPI;
						end.x = start.x + (_hoops_SCGCR - _hoops_GAAC) - 1;
						if (pattern == FP_SOLID)
							_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);
						else
							_hoops_HRAPI (nr, &start, &end, _hoops_GAAC, pattern, _hoops_HGIHP);

						_hoops_CIRPI += _hoops_SCGCR - _hoops_GAAC;
					}
					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
			}	break; /* _hoops_RSRPI */

			case Quantization_THRESHOLD: {
				do {
					int						_hoops_CIRPI = _hoops_SIRPI;

					in = (RGBAS32 const *)*_hoops_HCHIH++ + hoffset;
					_hoops_RCRPI = in + _hoops_PARSP;

					_hoops_RGGA (in == _hoops_RCRPI) {
						_hoops_RGGA (in == _hoops_RCRPI || in->a != 0) {
							++_hoops_CIRPI;
							++in;
						}

						if (in == _hoops_RCRPI) break;

						_hoops_SCGCR = _hoops_GAAC;

						_hoops_RGGA (in == _hoops_RCRPI || in->a == 0) {
							color.number = _hoops_ARAPI (in->r) * _hoops_CCRPI.r + 0x8000;
							index = color._hoops_CAGCR._hoops_SAGCR;
							color.number = _hoops_ARAPI (in->g) * _hoops_CCRPI.g + 0x8000;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;
							color.number = _hoops_ARAPI (in->b) * _hoops_CCRPI.b + 0x8000;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

							*_hoops_SCGCR++ = index + dc->_hoops_RHGCR;
							++in;
						}

						start.x = _hoops_HCGCR->x + _hoops_CIRPI;
						end.x = start.x + (_hoops_SCGCR - _hoops_GAAC) - 1;
						if (pattern == FP_SOLID)
							_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);
						else
							_hoops_HRAPI (nr, &start, &end, _hoops_GAAC, pattern, _hoops_HGIHP);

						_hoops_CIRPI += _hoops_SCGCR - _hoops_GAAC;
					}
					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
			}	break; /* _hoops_ASRPI */

			case Quantization_ERROR_DIFFUSION: {
				_hoops_SGGCR alter	*_hoops_PSRPI[2];
				int					row = 0;

				ALLOC_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, _hoops_SGGCR);
				ALLOC_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, _hoops_SGGCR);

				{
					int				_hoops_ICRHH;
					for (_hoops_ICRHH = 0; _hoops_ICRHH < _hoops_PARSP + 2; ++_hoops_ICRHH)
						_hoops_PSRPI[0][_hoops_ICRHH].r = _hoops_PSRPI[0][_hoops_ICRHH].g = _hoops_PSRPI[0][_hoops_ICRHH].b =
							_hoops_PSRPI[1][_hoops_ICRHH].r = _hoops_PSRPI[1][_hoops_ICRHH].g = _hoops_PSRPI[1][_hoops_ICRHH].b = 0;
				}

				do {
					_hoops_SGGCR alter	*_hoops_HSRPI, *_hoops_ISRPI;
					_hoops_SGGCR alter	*_hoops_CSRPI, *_hoops_SSRPI, *_hoops_GGAPI;
					int					_hoops_CIRPI = _hoops_SIRPI;

					in = (RGBAS32 const *)*_hoops_HCHIH++ + hoffset;
					_hoops_RCRPI = in + _hoops_PARSP;

					_hoops_HSRPI = &_hoops_PSRPI[row][0];
					_hoops_ISRPI = &_hoops_PSRPI[row][1];
					row = 1-row;
					_hoops_CSRPI = &_hoops_PSRPI[row][0];
					_hoops_SSRPI = &_hoops_PSRPI[row][1];
					_hoops_GGAPI = &_hoops_PSRPI[row][2];

					_hoops_RGGA (in == _hoops_RCRPI) {
						_hoops_RGGA (in == _hoops_RCRPI || in->a != 0) {
							++_hoops_CIRPI;
							++in;

							_hoops_ISRPI->r = _hoops_ISRPI->g = _hoops_ISRPI->b = 0;

							_hoops_HSRPI = _hoops_ISRPI++;
							_hoops_CSRPI = _hoops_SSRPI;
							_hoops_SSRPI = _hoops_GGAPI++;
						}

						if (in == _hoops_RCRPI) break;

						_hoops_SCGCR = _hoops_GAAC;

						_hoops_RGGA (in == _hoops_RCRPI || in->a == 0) {
							color.number = _hoops_CCRPI.r * _hoops_PCGCR (in->r) +
								(_hoops_HSRPI->r * 7 + _hoops_GGAPI->r * 3 + _hoops_SSRPI->r * 5 + _hoops_CSRPI->r) / 16;
							if (color.number < 0) color.number = 0;
							else if (color.number >= 0x01000000) color.number = 0x01000000;
							_hoops_ISRPI->r = color.number;
							color.number += 0x8000;
							color._hoops_CAGCR._hoops_RCGCR = 0;
							_hoops_ISRPI->r -= color.number;
							index = color._hoops_CAGCR._hoops_SAGCR;

							color.number = _hoops_CCRPI.g * _hoops_PCGCR (in->g) +
								(_hoops_HSRPI->g * 7 + _hoops_GGAPI->g * 3 + _hoops_SSRPI->g * 5 + _hoops_CSRPI->g) / 16;
							if (color.number < 0) color.number = 0;
							else if (color.number >= 0x01000000) color.number = 0x01000000;
							_hoops_ISRPI->g = color.number;
							color.number += 0x8000;
							color._hoops_CAGCR._hoops_RCGCR = 0;
							_hoops_ISRPI->g -= color.number;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;

							color.number = _hoops_CCRPI.b * _hoops_PCGCR (in->b) +
								(_hoops_HSRPI->b * 7 + _hoops_GGAPI->b * 3 + _hoops_SSRPI->b * 5 + _hoops_CSRPI->b) / 16;
							if (color.number < 0) color.number = 0;
							else if (color.number >= 0x01000000) color.number = 0x01000000;
							_hoops_ISRPI->b = color.number;
							color.number += 0x8000;
							color._hoops_CAGCR._hoops_RCGCR = 0;
							_hoops_ISRPI->b -= color.number;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

							*_hoops_SCGCR++ = index + dc->_hoops_RHGCR;
							++in;

							_hoops_HSRPI = _hoops_ISRPI++;
							_hoops_CSRPI = _hoops_SSRPI;
							_hoops_SSRPI = _hoops_GGAPI++;
						}

						start.x = _hoops_HCGCR->x + _hoops_CIRPI;
						end.x = start.x + (_hoops_SCGCR - _hoops_GAAC) - 1;

						if (pattern == FP_SOLID)
							_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);
						else
							_hoops_HRAPI (nr, &start, &end, _hoops_GAAC, pattern, _hoops_HGIHP);

						_hoops_CIRPI += _hoops_SCGCR - _hoops_GAAC;
					}
					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));

				FREE_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, _hoops_SGGCR);
				FREE_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, _hoops_SGGCR);
			}	break; /* _hoops_RGAPI */
		  } /* _hoops_RSGR _hoops_IIGR _hoops_CICA (_hoops_CCH) */
	  }	  break; /* _hoops_HGAPI */

	  case Image_RGBA32:
	  case _hoops_HRSRH: {
		  unsigned char const		*in;
		  _hoops_CRRRH			color;
		  int						index;
		  _hoops_SGGCR				_hoops_PRAPI;
		  _hoops_SGGCR			_hoops_CCRPI;
		  unsigned char const		*_hoops_RCRPI;

		  ALLOC_ARRAY (_hoops_GAAC, _hoops_PARSP, unsigned char);

		  _hoops_PRAPI.r = dc->_hoops_AGPGH.r;
		  _hoops_PRAPI.g = dc->_hoops_AGPGH.g;
		  _hoops_PRAPI.b = dc->_hoops_AGPGH.b;
		  _hoops_CCRPI.r = 0x00010000L * (_hoops_PRAPI.r - 1) / 255;
		  _hoops_CCRPI.g = 0x00010000L * (_hoops_PRAPI.g - 1) / 255;
		  _hoops_CCRPI.b = 0x00010000L * (_hoops_PRAPI.b - 1) / 255;

		  switch (mode) {
			case Quantization_DITHER: {
				do {
					int						row;
					int						col;
					unsigned short const	*_hoops_IHGCR;
					int						_hoops_CIRPI = hoffset;
					RGBAS32					pixel = _hoops_CAHSR::_hoops_SAHSR;

					in = (unsigned char const *)*_hoops_HCHIH++ + 4*hoffset;
					_hoops_RCRPI = in + 4*_hoops_PARSP;

					row = (int)start.y & 7;
					col = (int)start.x & 7;
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row];

					if (format == _hoops_HRSRH) pixel.a = *in++;
					pixel.r = *in++;
					pixel.g = *in++;
					pixel.b = *in++;
					if (format == Image_RGBA32) pixel.a = *in++;

					_hoops_RGGA (in == _hoops_RCRPI) {
						_hoops_RGGA (in == _hoops_RCRPI || pixel.a != 0) {
							col = HOOPS_READ_ONLY._hoops_PCHGI[col];
							++_hoops_CIRPI;

							if (format == _hoops_HRSRH) pixel.a = *in++;
							pixel.r = *in++;
							pixel.g = *in++;
							pixel.b = *in++;
							if (format == Image_RGBA32) pixel.a = *in++;
						}

						if (in == _hoops_RCRPI) break;

						_hoops_SCGCR = _hoops_GAAC;

						_hoops_RGGA (in == _hoops_RCRPI || pixel.a == 0) {
							Integer32 const _hoops_CPGCR = _hoops_IHGCR[col];

							color.number = _hoops_ARAPI (pixel.r) * _hoops_CCRPI.r + _hoops_CPGCR;
							index = color._hoops_CAGCR._hoops_SAGCR;
							color.number = _hoops_ARAPI (pixel.g) * _hoops_CCRPI.g + _hoops_CPGCR;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;
							color.number = _hoops_ARAPI (pixel.b) * _hoops_CCRPI.b + _hoops_CPGCR;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

							*_hoops_SCGCR++ = index + dc->_hoops_RHGCR;

							col = HOOPS_READ_ONLY._hoops_PCHGI[col];

							if (format == _hoops_HRSRH) pixel.a = *in++;
							pixel.r = *in++;
							pixel.g = *in++;
							pixel.b = *in++;
							if (format == Image_RGBA32) pixel.a = *in++;
						}

						start.x = _hoops_HCGCR->x + _hoops_CIRPI;
						end.x = start.x + (_hoops_SCGCR - _hoops_GAAC) - 1;
						if (pattern == FP_SOLID)
							_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);
						else
							_hoops_HRAPI (nr, &start, &end, _hoops_GAAC, pattern, _hoops_HGIHP);

						_hoops_CIRPI += _hoops_SCGCR - _hoops_GAAC;
					}
					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
			}	break; /* _hoops_RSRPI */

			case Quantization_THRESHOLD: {
				do {
					int						_hoops_CIRPI = _hoops_SIRPI;
					RGBAS32				pixel = _hoops_CAHSR::_hoops_SAHSR;

					in = (unsigned char const *)*_hoops_HCHIH++ + 4*hoffset;
					_hoops_RCRPI = in + 4*_hoops_PARSP;

					if (format == _hoops_HRSRH) pixel.a = *in++;
					pixel.r = *in++;
					pixel.g = *in++;
					pixel.b = *in++;
					if (format == Image_RGBA32) pixel.a = *in++;

					_hoops_RGGA (in == _hoops_RCRPI) {
						_hoops_RGGA (in == _hoops_RCRPI || pixel.a != 0) {
							++_hoops_CIRPI;

							if (format == _hoops_HRSRH) pixel.a = *in++;
							pixel.r = *in++;
							pixel.g = *in++;
							pixel.b = *in++;
							if (format == Image_RGBA32) pixel.a = *in++;
						}

						if (in == _hoops_RCRPI) break;

						_hoops_SCGCR = _hoops_GAAC;

						_hoops_RGGA (in == _hoops_RCRPI || pixel.a == 0) {
							color.number = _hoops_ARAPI (pixel.r) * _hoops_CCRPI.r + 0x8000;
							index = color._hoops_CAGCR._hoops_SAGCR;
							color.number = _hoops_ARAPI (pixel.g) * _hoops_CCRPI.g + 0x8000;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;
							color.number = _hoops_ARAPI (pixel.b) * _hoops_CCRPI.b + 0x8000;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

							*_hoops_SCGCR++ = index + dc->_hoops_RHGCR;

							if (format == _hoops_HRSRH) pixel.a = *in++;
							pixel.r = *in++;
							pixel.g = *in++;
							pixel.b = *in++;
							if (format == Image_RGBA32) pixel.a = *in++;
						}

						start.x = _hoops_HCGCR->x + _hoops_CIRPI;
						end.x = start.x + (_hoops_SCGCR - _hoops_GAAC) - 1;
						if (pattern == FP_SOLID)
							_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);
						else
							_hoops_HRAPI (nr, &start, &end, _hoops_GAAC, pattern, _hoops_HGIHP);

						_hoops_CIRPI += _hoops_SCGCR - _hoops_GAAC;
					}
					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));
			}	break; /* _hoops_ASRPI */

			case Quantization_ERROR_DIFFUSION: {
				_hoops_SGGCR alter	*_hoops_PSRPI[2];
				int					row = 0;

				ALLOC_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, _hoops_SGGCR);
				ALLOC_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, _hoops_SGGCR);

				{
					int				_hoops_ICRHH;
					for (_hoops_ICRHH = 0; _hoops_ICRHH < _hoops_PARSP + 2; ++_hoops_ICRHH)
						_hoops_PSRPI[0][_hoops_ICRHH].r = _hoops_PSRPI[0][_hoops_ICRHH].g = _hoops_PSRPI[0][_hoops_ICRHH].b =
							_hoops_PSRPI[1][_hoops_ICRHH].r = _hoops_PSRPI[1][_hoops_ICRHH].g = _hoops_PSRPI[1][_hoops_ICRHH].b = 0;
				}

				do {
					_hoops_SGGCR alter	*_hoops_HSRPI, *_hoops_ISRPI;
					_hoops_SGGCR alter	*_hoops_CSRPI, *_hoops_SSRPI, *_hoops_GGAPI;
					int					_hoops_CIRPI = _hoops_SIRPI;
					RGBAS32			pixel = _hoops_CAHSR::_hoops_SAHSR;


					in = (unsigned char const *)*_hoops_HCHIH++ + 4*hoffset;
					_hoops_RCRPI = in + 4*_hoops_PARSP;

					_hoops_HSRPI = &_hoops_PSRPI[row][0];
					_hoops_ISRPI = &_hoops_PSRPI[row][1];
					row = 1-row;
					_hoops_CSRPI = &_hoops_PSRPI[row][0];
					_hoops_SSRPI = &_hoops_PSRPI[row][1];
					_hoops_GGAPI = &_hoops_PSRPI[row][2];

					if (format == _hoops_HRSRH) pixel.a = *in++;
					pixel.r = *in++;
					pixel.g = *in++;
					pixel.b = *in++;
					if (format == Image_RGBA32) pixel.a = *in++;

					_hoops_RGGA (in == _hoops_RCRPI) {
						_hoops_RGGA (in == _hoops_RCRPI || pixel.a != 0) {
							++_hoops_CIRPI;

							_hoops_ISRPI->r = _hoops_ISRPI->g = _hoops_ISRPI->b = 0;

							_hoops_HSRPI = _hoops_ISRPI++;
							_hoops_CSRPI = _hoops_SSRPI;
							_hoops_SSRPI = _hoops_GGAPI++;

							if (format == _hoops_HRSRH) pixel.a = *in++;
							pixel.r = *in++;
							pixel.g = *in++;
							pixel.b = *in++;
							if (format == Image_RGBA32) pixel.a = *in++;
						}

						if (in == _hoops_RCRPI) break;

						_hoops_SCGCR = _hoops_GAAC;

						do {
							color.number = _hoops_CCRPI.r * _hoops_PCGCR (pixel.r) +
								(_hoops_HSRPI->r * 7 + _hoops_GGAPI->r * 3 + _hoops_SSRPI->r * 5 + _hoops_CSRPI->r) / 16;
							if (color.number < 0) color.number = 0;
							else if (color.number >= 0x01000000) color.number = 0x01000000;
							_hoops_ISRPI->r = color.number;
							color.number += 0x8000;
							color._hoops_CAGCR._hoops_RCGCR = 0;
							_hoops_ISRPI->r -= color.number;
							index = color._hoops_CAGCR._hoops_SAGCR;

							color.number = _hoops_CCRPI.g * _hoops_PCGCR (pixel.g) +
								(_hoops_HSRPI->g * 7 + _hoops_GGAPI->g * 3 + _hoops_SSRPI->g * 5 + _hoops_CSRPI->g) / 16;
							if (color.number < 0) color.number = 0;
							else if (color.number >= 0x01000000) color.number = 0x01000000;
							_hoops_ISRPI->g = color.number;
							color.number += 0x8000;
							color._hoops_CAGCR._hoops_RCGCR = 0;
							_hoops_ISRPI->g -= color.number;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.g;

							color.number = _hoops_CCRPI.b * _hoops_PCGCR (pixel.b) +
								(_hoops_HSRPI->b * 7 + _hoops_GGAPI->b * 3 + _hoops_SSRPI->b * 5 + _hoops_CSRPI->b) / 16;
							if (color.number < 0) color.number = 0;
							else if (color.number >= 0x01000000) color.number = 0x01000000;
							_hoops_ISRPI->b = color.number;
							color.number += 0x8000;
							color._hoops_CAGCR._hoops_RCGCR = 0;
							_hoops_ISRPI->b -= color.number;
							index = color._hoops_CAGCR._hoops_SAGCR + index * _hoops_PRAPI.b;

							*_hoops_SCGCR++ = index + dc->_hoops_RHGCR;

							_hoops_HSRPI = _hoops_ISRPI++;
							_hoops_CSRPI = _hoops_SSRPI;
							_hoops_SSRPI = _hoops_GGAPI++;

							if (in == _hoops_RCRPI) break;

							if (format == _hoops_HRSRH) pixel.a = *in++;
							pixel.r = *in++;
							pixel.g = *in++;
							pixel.b = *in++;
							if (format == Image_RGBA32) pixel.a = *in++;
						} while (pixel.a != 0);

						start.x = _hoops_HCGCR->x + _hoops_CIRPI;
						end.x = start.x + (_hoops_SCGCR - _hoops_GAAC) - 1;

						if (pattern == FP_SOLID)
							_hoops_GRCGH (nr, &start, &end, 0, _hoops_GAAC);
						else
							_hoops_HRAPI (nr, &start, &end, _hoops_GAAC, pattern, _hoops_HGIHP);

						_hoops_CIRPI += _hoops_SCGCR - _hoops_GAAC;
					}
					end.y = --start.y;
				} _hoops_RGGA (--vcount == 0 || _hoops_GGPGR(nr));

				FREE_ARRAY (_hoops_PSRPI[0], _hoops_PARSP + 2, _hoops_SGGCR);
				FREE_ARRAY (_hoops_PSRPI[1], _hoops_PARSP + 2, _hoops_SGGCR);
			}	break; /* _hoops_RGAPI */
		  } /* _hoops_RSGR _hoops_IIGR _hoops_CICA (_hoops_CCH) */
	  }	  break; /* _hoops_HGAPI/_hoops_IGAPI */
	}

	if (_hoops_GAAC != null) 
		FREE_ARRAY (_hoops_GAAC, _hoops_PARSP, unsigned char);
#endif
}
#if _MSC_VER >= 1300
#pragma optimize("", on)
#endif





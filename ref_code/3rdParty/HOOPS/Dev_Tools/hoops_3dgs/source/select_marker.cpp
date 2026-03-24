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
 * $Id: obf_tmp.txt 1.80 2010-10-06 19:16:29 jason Exp $
 */


#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "tandt.h"
#include "select.h"
#include "patterns.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


GLOBAL_FUNCTION void HD_Select_Marker (
	Net_Rendition const &		nr,
	Marker const *				marker) {
#ifndef DISABLE_SELECTION
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter *	sc = dc->_hoops_APHHP;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_RPRA const *			elements = _hoops_IHCR->matrix->data.elements;
	_hoops_ICP const &	_hoops_CCP = nr->_hoops_GSP;
	bool						_hoops_PISAA = BIT (nr->transform_rendition->heuristics, _hoops_PAIRP);
	DC_Point					center;
	XY							_hoops_CGSIR;
	float						_hoops_CIPAS,
								w,
								size;

	if (BIT (sc->options, _hoops_IICAH)) {
		HD_Select_Dot (nr, (Geometry alter *)marker, marker->key, _hoops_AIRIR(marker), T_MARKERS, &marker->_hoops_CSAI);
		return;
	}

	if (_hoops_PISAA) {
		sc->_hoops_HPPAS._hoops_RAI = (Geometry *)marker;
		sc->_hoops_HPPAS._hoops_HHGGH = sc->_hoops_GICAH;
		sc->_hoops_HPPAS._hoops_CHGGH = -1;
		sc->_hoops_HPPAS._hoops_CIHIA = false;
		sc->_hoops_HPPAS._hoops_PHGGH = 0;

		HD_Std_3D_Marker (nr, marker);

		sc->_hoops_HPPAS._hoops_RAI = null;
		if (sc->_hoops_HPPAS._hoops_CHGGH != -1)
			HD_Elaborate_Selection (nr, dc->_hoops_RAI,
									dc->_hoops_RAI->key, _hoops_AIRIR(dc->_hoops_RAI),
									0, 0, 0,
									sc->_hoops_HPPAS._hoops_IHGGH, sc->_hoops_HPPAS._hoops_HHGGH,
									T_MARKERS, sc->_hoops_HPPAS._hoops_ACSAP);

		return;
	}

	if (_hoops_CCP->ysize < 0) {
		_hoops_ICP alter &	_hoops_HCSHP = (_hoops_ICP alter &)_hoops_CCP;
		float						_hoops_RPCAS;

		_hoops_RPCAS = HD_Compute_Generic_Size (nr, _hoops_HCSHP->_hoops_PHP, _hoops_HCSHP->_hoops_HHP, 1.0f, false, 0, true);
		_hoops_HCSHP->ysize = _hoops_RPCAS*0.5f;
		_hoops_HCSHP->_hoops_RGRS = _hoops_RPCAS*0.5f*nr->_hoops_SRA->current._hoops_AGRS;
	}

	size = (BIT(_hoops_CCP->glyph->flags, _hoops_GSIAP) ? 1.0f : _hoops_CCP->ysize);

	if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) {
		w = 1.0f;
		center.x = _hoops_HPRA (elements, marker->_hoops_CSAI);

		/* _hoops_HHCI _hoops_ISPR _hoops_IIGR _hoops_RH _hoops_IPCAH _hoops_IGIAR _hoops_SPCR */
		if ((_hoops_CGSIR.x = center.x - sc->_hoops_AICAH.x) < 0.0f) _hoops_CGSIR.x = -_hoops_CGSIR.x;

		if (_hoops_CGSIR.x > (size + sc->_hoops_RICAH.x)) return; /* _hoops_GSSR _hoops_AGIR */

		center.y = _hoops_IPRA (elements, marker->_hoops_CSAI);
	}
	else {
		w = _hoops_PHCP (elements, marker->_hoops_CSAI);
		if (w <= _hoops_IHCR->_hoops_CHCR) return;

		if (_hoops_CCP->_hoops_HHP == _hoops_SPSC &&
			_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH) {
			_hoops_HRPA					_hoops_PHSC;
			float						z = 0, _hoops_SRIR = 0;

			HI_Multiply_Matrices (&_hoops_IHCR->_hoops_IPH->data,
								  &_hoops_IHCR->_hoops_SPH->_hoops_PRPA,
								  &_hoops_PHSC);
			_hoops_SRIR = _hoops_IHCR->_hoops_SPH->_hoops_SRIR;
			z = _hoops_CPRA (_hoops_PHSC.elements, marker->_hoops_CSAI);
			z /= _hoops_SRIR;
			size *= 1 / (z + 1);
		}

		center.x = _hoops_HPRA (elements, marker->_hoops_CSAI) / w;
		if ((_hoops_CGSIR.x = center.x - sc->_hoops_AICAH.x) < 0.0f) _hoops_CGSIR.x = -_hoops_CGSIR.x;

		if (_hoops_CGSIR.x > (size + sc->_hoops_RICAH.x)) return; /* _hoops_GSSR _hoops_AGIR */

		center.y = _hoops_IPRA (elements, marker->_hoops_CSAI) / w;
	}

	/* _hoops_HHCI _hoops_ISPR _hoops_HHHGH _hoops_IH _hoops_GHCR */
	if ((_hoops_CGSIR.y = center.y - sc->_hoops_AICAH.y) < 0.0f) _hoops_CGSIR.y = -_hoops_CGSIR.y;
	if (_hoops_CGSIR.y > (size + sc->_hoops_RICAH.y)) return;

	/* _hoops_ISPR _hoops_RH _hoops_GHARP (_hoops_RH _hoops_RRI _hoops_CCCI) _hoops_IPCAH */
	_hoops_CGSIR.x /= sc->_hoops_HICAH.x;
	_hoops_CGSIR.y /= sc->_hoops_HICAH.y;
	_hoops_CIPAS = _hoops_CGSIR.x*_hoops_CGSIR.x + _hoops_CGSIR.y*_hoops_CGSIR.y;
	if (_hoops_CIPAS > (size + sc->_hoops_RICAH.x) * (size + sc->_hoops_RICAH.y) /
					(sc->_hoops_HICAH.x * sc->_hoops_HICAH.y))
		return;

	/*
	 * _hoops_ISPR _hoops_RH _hoops_CIHH
	 */
	if (sc->_hoops_RAPAS == null)
		if (center.x < sc->bounding.left-size	||
			center.x > sc->bounding.right+size	||
			center.y < sc->bounding.bottom-size ||
			center.y > sc->bounding.top+size) return;


	/* _hoops_ISPR _hoops_AHCR */
	center.z = _hoops_CPRA (elements, marker->_hoops_CSAI);
	if (_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) center.z /= w;

	if (center.z < sc->bounding.hither ||
		center.z > sc->bounding.yon) return;

	if (BIT (_hoops_IHCR->flags, _hoops_CSP))
		if (!HD_Point_Within_Cutting_Planes (_hoops_IHCR, center.x, center.y, center.z)) return;

	/* _hoops_AA _hoops_SR _hoops_PICP _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_SIGC? */
	if (BIT (sc->options, _hoops_CRPAS)) {
		bool							_hoops_RCAI = false;

		_hoops_IGRS (dc);

		if (sc->_hoops_GPPAS) {
			void *							_hoops_CCHSP;

			_hoops_CCHSP = _hoops_AACGH (nr, true);
			_hoops_GPICP (nr, marker);
			_hoops_PACGH (nr, _hoops_CCHSP);

			if (_hoops_IACGH (nr, _hoops_CCHSP) == 0)
				_hoops_RCAI = true;
		}
		else {
			_hoops_HCSIR alter *	_hoops_ICSIR = null;

			if (nr->_hoops_SAIR->_hoops_ASSIR != null)
				_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
			if (_hoops_ICSIR == null) {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									"Expected frame buffer not found");
				_hoops_RCAI = true;
				goto _hoops_SIPAS;
			}

			_hoops_ICSIR->input._hoops_PHHSP = 0;

			_hoops_GPICP (nr, marker);

			if (_hoops_ICSIR->input._hoops_PHHSP == 0)
				_hoops_RCAI = true;
		}

	  _hoops_SIPAS:
		_hoops_SGRS (dc);
		if (_hoops_RCAI)
			return;
	}

#ifndef DISABLE_POLY_SELECTION
	if (sc->_hoops_RAPAS != null) {
		if (BIT (sc->options, _hoops_PRPAS)) {
			if (!HD_Select_Point_By_Polygon (nr, &center) &&
				!HD_Select_Circle_By_Polyline (nr, &center, size)) return;
		}
		else { /* _hoops_ISII _hoops_GHSHA */
			if (!HD_Select_Circle_By_Polyline (nr, &center, size)) return;
		}
	}
#endif


	/*
	 * _hoops_GCPAS _hoops_CCSPR - _hoops_PRIA _hoops_RH _hoops_RCAHR
	 */

	size /= sc->_hoops_HICAH.y;

	if (_hoops_CIPAS > size*size)
		/*	  (_hoops_AGGIR(_hoops_APCAS) - _hoops_IGIR) ^ 2	*/
		_hoops_CIPAS = _hoops_CIPAS + size*size - 2.0f * _hoops_SGIHR (_hoops_CIPAS) * size;
	else
		_hoops_CIPAS = 0.0f;

	HD_Elaborate_Selection (nr, dc->_hoops_RAI,
							dc->_hoops_RAI->key, _hoops_AIRIR(dc->_hoops_RAI),
							0, 0, 0, center.z, _hoops_CIPAS,
							T_MARKERS, null);
#endif
}


GLOBAL_FUNCTION void HD_Select_Multimarker (
	Net_Rendition const &		inr,
	_hoops_GRPGR const *			_hoops_CPAI) {
#ifndef DISABLE_SELECTION
	Net_Rendition				nr = inr;
	Display_Context alter *		dc = _hoops_PGRCA(nr->_hoops_SRA);
	_hoops_ACCCP alter *	sc = dc->_hoops_APHHP;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_RPRA const *			elements = _hoops_IHCR->matrix->data.elements;
	_hoops_ICP const &	_hoops_CCP = nr->_hoops_GSP;
	bool						_hoops_PISAA = BIT (nr->transform_rendition->heuristics, _hoops_PAIRP);
	int							count = _hoops_CPAI->count;
	Point const *				points = _hoops_CPAI->points + count;
	int const *					mapping = _hoops_CPAI->mapping + count;
	int							offset1;
	DC_Point					center;
	XY							_hoops_CGSIR;
	float						_hoops_CIPAS;


	if (BIT (sc->options, _hoops_IICAH)) {
		while (count-- > 0) {
			int				index = *--mapping;
			Key				_hoops_PPCAS = HOOPS_WORLD->_hoops_GCHCA.table[index].key;

			HD_Select_Dot (nr, (Geometry alter *)_hoops_CPAI, _hoops_PPCAS, ~(POINTER_SIZED_INT)index, T_MARKERS, --points);
		}
		return;
	}

	if (_hoops_PISAA) {
		while (count-- > 0) {
			int				index = *--mapping & ~_hoops_RIRIR;
			Key				_hoops_PPCAS = HOOPS_WORLD->_hoops_GCHCA.table[index].key;
			Marker			marker;

			ZERO_STRUCT (&marker, Marker);
			marker.type = _hoops_PCIP;
			marker.key = _hoops_PPCAS;
			marker._hoops_CSAI = *--points;

			sc->_hoops_HPPAS._hoops_RAI = (Geometry *)&marker;
			sc->_hoops_HPPAS._hoops_HHGGH = sc->_hoops_GICAH;
			sc->_hoops_HPPAS._hoops_CHGGH = -1;
			sc->_hoops_HPPAS._hoops_CIHIA = false;
			sc->_hoops_HPPAS._hoops_PHGGH = 0;

			HD_Std_3D_Marker (nr, &marker);

			sc->_hoops_HPPAS._hoops_RAI = null;
			if ((offset1 = sc->_hoops_HPPAS._hoops_CHGGH) != -1 || sc->_hoops_HPPAS._hoops_CIHIA) {
				HD_Elaborate_Selection (nr, dc->_hoops_RAI, _hoops_PPCAS, ~(POINTER_SIZED_INT)index,
										0, 0, 0,
										sc->_hoops_HPPAS._hoops_IHGGH, sc->_hoops_HPPAS._hoops_HHGGH,
										T_MARKERS, sc->_hoops_HPPAS._hoops_ACSAP);
			}
		}

		return;
	}

	if (_hoops_CCP->ysize < 0) {
		_hoops_ICP alter &	_hoops_HCSHP = (_hoops_ICP alter &)_hoops_CCP;
		float						_hoops_RPCAS;

		_hoops_RPCAS = HD_Compute_Generic_Size (nr, _hoops_HCSHP->_hoops_PHP, _hoops_HCSHP->_hoops_HHP, 1.0f, false, 0, true);
		_hoops_HCSHP->ysize = _hoops_RPCAS*0.5f;
		_hoops_HCSHP->_hoops_RGRS = _hoops_RPCAS*0.5f*nr->_hoops_SRA->current._hoops_AGRS;
	}

	float		_hoops_HPCAS = (BIT(_hoops_CCP->glyph->flags, _hoops_GSIAP) ? 1.0f : _hoops_CCP->ysize);


	while (count-- > 0) {
		Point			point = *--points;
		int				index = *--mapping;
		Key				_hoops_PPCAS = HOOPS_WORLD->_hoops_GCHCA.table[index].key;
		float			size = _hoops_HPCAS;
		float			w;

		if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) {
			w = 1.0f;
			center.x = _hoops_HPRA (elements, point);

			/* _hoops_HHCI _hoops_ISPR _hoops_IIGR _hoops_RH _hoops_IPCAH _hoops_IGIAR _hoops_SPCR */
			_hoops_CGSIR.x = Abs (center.x - sc->_hoops_AICAH.x);

			if (_hoops_CGSIR.x > (size + sc->_hoops_RICAH.x))
				continue;

			center.y = _hoops_IPRA (elements, point);
		}
		else {
			w = _hoops_PHCP (elements, point);
			if (w <= _hoops_IHCR->_hoops_CHCR)
				continue;

			if (_hoops_CCP->_hoops_HHP == _hoops_SPSC &&
				_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH) {
				_hoops_HRPA					_hoops_PHSC;
				float						z = 0, _hoops_SRIR = 0;

				HI_Multiply_Matrices (&_hoops_IHCR->_hoops_IPH->data,
									  &_hoops_IHCR->_hoops_SPH->_hoops_PRPA,
									  &_hoops_PHSC);
				_hoops_SRIR = _hoops_IHCR->_hoops_SPH->_hoops_SRIR;
				z = _hoops_CPRA (_hoops_PHSC.elements, point);
				z /= _hoops_SRIR;
				size *= 1 / (z + 1);
			}

			center.x = _hoops_HPRA (elements, point) / w;
			_hoops_CGSIR.x = Abs (center.x - sc->_hoops_AICAH.x);

			if (_hoops_CGSIR.x > (size + sc->_hoops_RICAH.x))
				continue;

			center.y = _hoops_IPRA (elements, point) / w;
		}

		/* _hoops_HHCI _hoops_ISPR _hoops_HHHGH _hoops_IH _hoops_GHCR */
		_hoops_CGSIR.y = Abs (center.y - sc->_hoops_AICAH.y);
		if (_hoops_CGSIR.y > (size + sc->_hoops_RICAH.y))
			continue;

		/* _hoops_ISPR _hoops_RH _hoops_GHARP (_hoops_RH _hoops_RRI _hoops_CCCI) _hoops_IPCAH */
		_hoops_CGSIR.x /= sc->_hoops_HICAH.x;
		_hoops_CGSIR.y /= sc->_hoops_HICAH.y;
		_hoops_CIPAS = _hoops_CGSIR.x*_hoops_CGSIR.x + _hoops_CGSIR.y*_hoops_CGSIR.y;
		if (_hoops_CIPAS > (size + sc->_hoops_RICAH.x) * (size + sc->_hoops_RICAH.y) /
						(sc->_hoops_HICAH.x * sc->_hoops_HICAH.y))
			continue;

		// _hoops_ISPR _hoops_RH _hoops_CIHH
		if (sc->_hoops_RAPAS == null)
			if (center.x < sc->bounding.left - size	|| center.x > sc->bounding.right + size ||
				center.y < sc->bounding.bottom - size || center.y > sc->bounding.top + size)
				continue;


		// _hoops_ISPR _hoops_AHCR
		center.z = _hoops_CPRA (elements, point);
		if (_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC))
			center.z /= w;

		if (center.z < sc->bounding.hither || center.z > sc->bounding.yon)
			continue;

		if (BIT (_hoops_IHCR->flags, _hoops_CSP))
			if (!HD_Point_Within_Cutting_Planes (_hoops_IHCR, center.x, center.y, center.z))
				continue;

		// _hoops_AA _hoops_SR _hoops_PICP _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_SIGC?
		if (BIT (sc->options, _hoops_CRPAS)) {
			bool			_hoops_RCAI = false;
			Marker			marker;

			ZERO_STRUCT (&marker, Marker);
			marker.type = _hoops_PCIP;
			marker.key = _hoops_PPCAS;
			marker._hoops_CSAI = point;


			_hoops_IGRS (dc);

			if (sc->_hoops_GPPAS) {
				void *							_hoops_CCHSP;

				_hoops_CCHSP = _hoops_AACGH (nr, true);
				_hoops_GPICP (nr, &marker);
				_hoops_PACGH (nr, _hoops_CCHSP);

				if (_hoops_IACGH (nr, _hoops_CCHSP) == 0)
					_hoops_RCAI = true;
			}
			else {
				_hoops_HCSIR alter *	_hoops_ICSIR = null;

				if (nr->_hoops_SAIR->_hoops_ASSIR != null)
					_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
				if (_hoops_ICSIR == null) {
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
										"Expected frame buffer not found");
					_hoops_RCAI = true;
					goto _hoops_SIPAS;
				}

				_hoops_ICSIR->input._hoops_PHHSP = 0;

				_hoops_GPICP (nr, &marker);

				if (_hoops_ICSIR->input._hoops_PHHSP == 0)
					_hoops_RCAI = true;
			}

		  _hoops_SIPAS:
			_hoops_SGRS (dc);
			if (_hoops_RCAI)
				continue;
		}

#ifndef DISABLE_POLY_SELECTION
		if (sc->_hoops_RAPAS != null) {
			if (BIT (sc->options, _hoops_PRPAS)) {
				if (!HD_Select_Point_By_Polygon (nr, &center) &&
					!HD_Select_Circle_By_Polyline (nr, &center, size))
					continue;
			}
			else { /* _hoops_ISII _hoops_GHSHA */
				if (!HD_Select_Circle_By_Polyline (nr, &center, size))
					continue;
			}
		}
#endif

		// _hoops_GCPAS _hoops_CCSPR - _hoops_PRIA _hoops_RH _hoops_RCAHR
		size /= sc->_hoops_HICAH.y;

		if (_hoops_CIPAS > size*size)
			/*	  (_hoops_AGGIR(_hoops_APCAS) - _hoops_IGIR) ^ 2	*/
			_hoops_CIPAS = _hoops_CIPAS + size*size - 2.0f * _hoops_SGIHR (_hoops_CIPAS) * size;
		else
			_hoops_CIPAS = 0.0f;

		HD_Elaborate_Selection (nr, dc->_hoops_RAI, _hoops_PPCAS, ~(POINTER_SIZED_INT)index,
								0, 0, 0, center.z, _hoops_CIPAS,
								T_MARKERS, null);
	}
#endif
}

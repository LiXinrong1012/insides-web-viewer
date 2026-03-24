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
 * $Id: obf_tmp.txt 1.204 2010-12-01 03:35:03 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "patterns.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

#ifndef _hoops_GCGHR

typedef struct _hoops_SICII {
	struct _hoops_SICII *		_hoops_CGHPR;
	struct _hoops_SICII *		_hoops_SGHPR;
	struct _hoops_SICII *		up;
	struct _hoops_SICII *		_hoops_GRHPR;

	int							length;
	int const *					vertices;
	int const *					faces;
	bool						_hoops_HHAHR;
	bool						_hoops_SICPR;
	int							_hoops_GCCII;

	Activity					_hoops_CPGPR;
	One_Face_Attributes			face_attributes; /* (_hoops_CGHI _hoops_GGR _hoops_AGIR _hoops_PISC _hoops_SPCC) */
} _hoops_RCCII;

#endif


GLOBAL_FUNCTION void HI_Reset_Strip_Flags (
	Polyhedron *					_hoops_IPRI) {
#ifndef _hoops_GCGHR
	if (BIT (_hoops_IPRI->polyhedron_flags, _hoops_CCRHR))
		HI_Resort_Tristrips (_hoops_IPRI, -1);

	Local_Vertex_Attributes *		_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

	if (_hoops_IPRI->tristrips != null) {
		if (_hoops_SPRI->_hoops_RCRHR == _hoops_IPRI->point_count) {
			Tristrip *ts = _hoops_IPRI->tristrips;
			do {
				ts->face_attributes.flags &= ~_hoops_PPRHR;
				ts->face_attributes.flags |= _hoops_PARHR;
			} while ((ts = ts->next) != null);
			_hoops_IPRI->_hoops_ACRHR |= _hoops_PARHR;
		}
		else if (_hoops_SPRI->_hoops_SIRHR == _hoops_IPRI->point_count) {
			Tristrip *ts = _hoops_IPRI->tristrips;
			do {
				ts->face_attributes.flags &= ~_hoops_PPRHR;
				ts->face_attributes.flags |= _hoops_IARHR;
			} while ((ts = ts->next) != null);
			_hoops_IPRI->_hoops_ACRHR |= _hoops_IARHR;
		}
		else if (_hoops_SPRI->_hoops_RCRHR > 0 ||
				 _hoops_SPRI->_hoops_SIRHR > 0) {
			Tristrip *ts = _hoops_IPRI->tristrips;
			/* _hoops_APRS _hoops_IIRGR _hoops_RRP _hoops_IS _hoops_SHH _hoops_ACCII */
			do {
				int				_hoops_PHHA = ts->_hoops_PHHA;
				int const *		lengths = ts->lengths;
				int const *		_hoops_AIHA = ts->_hoops_AIHA;

				ts->face_attributes.flags &= ~_hoops_PPRHR;

				while (_hoops_PHHA-- > 0) {
					int				length = *lengths++;

					if (length < 0)		/* _hoops_HAHCP */
						length = -length;

					while (length-- > 0) {
						int						vertex = *_hoops_AIHA++;
						Local_Vertex_Flags	flags = *_hoops_SPRI->_hoops_CHHPR(vertex);

						if (BIT (flags, _hoops_HARHR))
							ts->face_attributes.flags |= _hoops_IARHR;
						else if (BIT (flags, _hoops_AARHR))
							ts->face_attributes.flags |= _hoops_PARHR;
						else
							ts->face_attributes.flags |= _hoops_CARHR;
					}
					_hoops_IPRI->_hoops_ACRHR |= ts->face_attributes.flags & _hoops_PPRHR;
				}
			} _hoops_RGGA ((ts = ts->next) == null);
		}
		else {
			Tristrip *ts = _hoops_IPRI->tristrips;
			do {
				ts->face_attributes.flags &= ~_hoops_PPRHR;
				ts->face_attributes.flags |= _hoops_CARHR;
			} while ((ts = ts->next) != null);
			_hoops_IPRI->_hoops_ACRHR |= _hoops_CARHR;
		}
	}

	if (_hoops_IPRI->_hoops_SHGPR != null) {
		if (_hoops_SPRI->_hoops_SCHPR == _hoops_IPRI->point_count) {
			Polyedge *pe = _hoops_IPRI->_hoops_SHGPR;
			do {
				pe->_hoops_PPGI.flags &= ~_hoops_SHHPR;
				pe->_hoops_PPGI.flags |= _hoops_HPHPR;
			} while ((pe = pe->next) != null);
			_hoops_IPRI->_hoops_RSHPR |= _hoops_HPHPR;
		}
		else if (_hoops_SPRI->_hoops_CCHPR == _hoops_IPRI->point_count) {
			Polyedge *pe = _hoops_IPRI->_hoops_SHGPR;
			do {
				pe->_hoops_PPGI.flags &= ~_hoops_SHHPR;
				pe->_hoops_PPGI.flags |= _hoops_APHPR;
			} while ((pe = pe->next) != null);
			_hoops_IPRI->_hoops_RSHPR |= _hoops_APHPR;
		}
		else if (_hoops_SPRI->_hoops_SCHPR > 0 ||
				 _hoops_SPRI->_hoops_CCHPR > 0) {
			Polyedge *pe = _hoops_IPRI->_hoops_SHGPR;
			/* _hoops_APRS _hoops_IIRGR _hoops_RRP _hoops_IS _hoops_SHH _hoops_ACCII */
			do {
				int				_hoops_PHHA = pe->_hoops_PHHA;
				int const *		lengths = pe->lengths;
				int const *		_hoops_AIHA = pe->_hoops_AIHA;

				while (_hoops_PHHA-- > 0) {
					int				length = *lengths++;

					pe->_hoops_PPGI.flags &= ~_hoops_SHHPR;

					while (length-- > 0) {
						int						vertex = *_hoops_AIHA++;
						Local_Vertex_Flags	flags = *_hoops_SPRI->_hoops_CHHPR(vertex);

						if (BIT (flags, _hoops_RPHPR))
							pe->_hoops_PPGI.flags |= _hoops_APHPR;
						else if (BIT (flags, _hoops_PPHPR))
							pe->_hoops_PPGI.flags |= _hoops_HPHPR;
						else
							pe->_hoops_PPGI.flags |= _hoops_IPHPR;
					}
					_hoops_IPRI->_hoops_RSHPR |=
						pe->_hoops_PPGI.flags & _hoops_SHHPR;
				}
			} _hoops_RGGA ((pe = pe->next) == null);
		}
		else {
			Polyedge *pe = _hoops_IPRI->_hoops_SHGPR;
			do {
				pe->_hoops_PPGI.flags &= ~_hoops_SHHPR;
				pe->_hoops_PPGI.flags |= _hoops_IPHPR;
			} while ((pe = pe->next) != null);
			_hoops_IPRI->_hoops_RSHPR |= _hoops_IPHPR;
		}
	}

	if (_hoops_IPRI->_hoops_GIGPR != null) {
		if (_hoops_SPRI->_hoops_ICRRA == _hoops_IPRI->point_count) {
			Polymarker *pm = _hoops_IPRI->_hoops_GIGPR;
			do {
				pm->_hoops_SACI.flags &= ~_hoops_APPRA;
				pm->_hoops_SACI.flags |= _hoops_HCRRA;
			} while ((pm = pm->next) != null);
			_hoops_IPRI->_hoops_AGRHR |= _hoops_HCRRA;
		}
		else if (_hoops_SPRI->_hoops_PCRRA == _hoops_IPRI->point_count) {
			Polymarker *pm = _hoops_IPRI->_hoops_GIGPR;
			do {
				pm->_hoops_SACI.flags &= ~_hoops_APPRA;
				pm->_hoops_SACI.flags |= _hoops_SIRRA;
			} while ((pm = pm->next) != null);
			_hoops_IPRI->_hoops_AGRHR |= _hoops_SIRRA;
		}
		else if (_hoops_SPRI->_hoops_SCHPR > 0 ||
				 _hoops_SPRI->_hoops_CCHPR > 0) {
			Polymarker *pm = _hoops_IPRI->_hoops_GIGPR;
			/* _hoops_APRS _hoops_IIRGR _hoops_RRP _hoops_IS _hoops_SHH _hoops_ACCII */
			do {
				int				length = pm->length;
				int const *		_hoops_AIHA = pm->_hoops_AIHA;
				int				_hoops_HCGS = -1;
				Local_Vertex_Flags flags;
				pm->_hoops_SACI.flags &= ~_hoops_APPRA;

				while (length-- > 0) {
					if (_hoops_AIHA)
						_hoops_HCGS = *_hoops_AIHA++;
					else
						_hoops_HCGS++;
					flags = *_hoops_SPRI->_hoops_CHHPR(_hoops_HCGS);

					if (BIT (flags, _hoops_SIRRA))
						pm->_hoops_SACI.flags |= _hoops_SIRRA;
					else if (BIT (flags, _hoops_PPHPR))
						pm->_hoops_SACI.flags |= _hoops_HCRRA;
				}
				_hoops_IPRI->_hoops_RSHPR |=
					pm->_hoops_SACI.flags & _hoops_APPRA;
			} _hoops_RGGA ((pm = pm->next) == null);
		}
	}
#endif
}


GLOBAL_FUNCTION void HI_Resort_Tristrips (
	Polyhedron *		_hoops_IPRI,
	int					region) {
#ifndef _hoops_GCGHR
	Tristrip *			ts = _hoops_IPRI->tristrips;

#if 0
	if (_hoops_PCCII) {
		/* _hoops_PIHGR: _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_IS _hoops_GHIS, _hoops_PPR _hoops_SR _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_RGIC _hoops_AHCA
		 * _hoops_HRHAR _hoops_IIRGR.  _hoops_SAHR _hoops_ARP _hoops_GRR _hoops_CRHH.
		 * _hoops_PAGA: _hoops_SR _hoops_HHS _hoops_HPPR _hoops_IS _hoops_HCCII _hoops_GPGR _hoops_CCGI, _hoops_HIH _hoops_SGS
		 * _hoops_CHH _hoops_HGAP _hoops_IHH _hoops_PIH _hoops_CCCH.  _hoops_PS _hoops_CHR _hoops_HCRAA _hoops_IH _hoops_RH _hoops_AGIR
		 * _hoops_CAS _hoops_PCCP _hoops_RSIR _hoops_RRCPR _hoops_HRGR _hoops_GAGPR _hoops_ARP _hoops_IS _hoops_IRS _hoops_RSRA _hoops_HAIR
		 */
		if (flags == LFA_EXPLICIT_COLOR_BY_FINDEX) {
			float			findex;

			findex = _hoops_IPRI->local_face_attributes.findices[0];

			do {
				ts->face_attributes.findex = findex;
				ts->face_attributes.flags &= ~_hoops_IACHR;
				ts->face_attributes.flags |= flags;
				ts->same_colors = _hoops_ICCII;
			} _hoops_RGGA ((ts = ts->next) == null);
		}
		else if (flags == LFA_EXPLICIT_COLOR_BY_VALUE) {
			RGB const	*color;

			color = &_hoops_IPRI->local_face_attributes.colors[0];

			do {
				ts->face_attributes.color.red	= color->red;
				ts->face_attributes.color.green = color->green;
				ts->face_attributes.color.blue	= color->blue;
				ts->face_attributes.flags &= ~_hoops_IACHR;
				ts->face_attributes.flags |= flags;
				ts->same_colors = _hoops_ICCII;
			} _hoops_RGGA ((ts = ts->next) == null);
		}
		else {
			do {
				ts->face_attributes.flags &= ~_hoops_IACHR;
				ts->same_colors = _hoops_PAIPR;
			} _hoops_RGGA ((ts = ts->next) == null);
		}
	}
	else
#endif
	{
		/* _hoops_ACIPR: _hoops_ARPR _hoops_IRS _hoops_HHIS _hoops_IIGR _hoops_IIRGR _hoops_GSHHR _hoops_HPP _hoops_IGRI, _hoops_GSGS _hoops_GAR _hoops_GGR
		 * _hoops_CCCII, _hoops_PHRI _hoops_SR _hoops_PAH _hoops_HGCR _hoops_SGGR _hoops_CCA _hoops_CICRR
		 * _hoops_CRGR _hoops_RH _hoops_APRS _hoops_IIRGR.
		 * _hoops_PAGA: _hoops_RPP _hoops_IRS _hoops_GHPAH _hoops_SAGGR _hoops_HHGP, _hoops_RSSP _hoops_PIHA _hoops_SHH _hoops_IGCGI,
		 * _hoops_HIS _hoops_IRS _hoops_RSRA _hoops_SCPH _hoops_CCA _hoops_SCCII _hoops_RSSA _hoops_GHCA _hoops_SHH _hoops_PRHI
		 */
		_hoops_RCCII *				root = null;
		_hoops_RCCII *				node;
		_hoops_RCCII *				_hoops_AGPHR;
		_hoops_RCCII *				_hoops_GSCII;
		Local_Face_Attributes *		_hoops_CPRI;
		Tristrip *					_hoops_RSCII;

		_hoops_CPRI = &_hoops_IPRI->local_face_attributes;

		_hoops_RSCII = _hoops_IPRI->tristrips;
		_hoops_IPRI->tristrips = null;

		if (region != -1) {
			Tristrip **				_hoops_ASRGR = &_hoops_RSCII;
			/* _hoops_RHAPA _hoops_GII _hoops_CRPHR _hoops_IH _hoops_RGR _hoops_ISPH _hoops_HII "_hoops_CCPHR" _hoops_CCGI.
			 * _hoops_RPGS _hoops_HSAR _hoops_RH _hoops_RII _hoops_AGIR, _hoops_CR _hoops_CRPHR _hoops_CHR _hoops_HAR _hoops_PRGS _hoops_PAHAR
			 */

			while ((ts = *_hoops_ASRGR) != null) {
				if (ts->face_attributes.region != -1 &&
					(ts->face_attributes.flags & _hoops_PHGPR) != 0 ||
					 BIT (HOOPS_WORLD->system_flags, _hoops_CSRRA) ||
					 ts->_hoops_CPGPR != 0 || ts->_hoops_SPGPR != 0) {
					/* _hoops_GRHP _hoops_RGR _hoops_SPR _hoops_GAR-_hoops_HRGR _hoops_IH _hoops_HA */
					*_hoops_ASRGR = ts->next;
					ts->next = _hoops_IPRI->tristrips;
					_hoops_IPRI->tristrips = ts;
				}
				else {
					/* _hoops_RGR _hoops_SPR _hoops_PAHH _hoops_IRHS _hoops_ASCII */
					int				_hoops_PHHA = ts->_hoops_PHHA;
					int const *		lengths = ts->lengths;
					int const *		_hoops_AIHA = ts->_hoops_AIHA;
					int const *		face_indices = ts->face_indices;
					int const *		regions = _hoops_IPRI->local_face_attributes.regions;

					if (face_indices == null) {
						/* _hoops_PAH _hoops_PSP _hoops_RPIP _hoops_SGH _hoops_CHHA _hoops_PSPI, _hoops_CAHP _hoops_RH _hoops_HSSHH */
						int alter *		fi;
						int				face = 0;

						ALLOC_ARRAY (fi, ts->total, int);
						face_indices = ts->face_indices = fi;
						ts->_hoops_SGAHR = ts->total;

						while (_hoops_PHHA-- > 0) {
							int		length = *lengths++;

							if (length < 0)
								length = -length;
							length -= 2;

							*fi++ = 0;
							*fi++ = 0;
							while (length-- > 0)
								*fi++ = face++;
						}

						_hoops_PHHA = ts->_hoops_PHHA;
						lengths = ts->lengths;
						face_indices = ts->face_indices;
					}

					while (_hoops_PHHA-- > 0) {
						int				length = *lengths++;
						bool		_hoops_SICPR = false;

						if (length < 0) {		/* _hoops_HAHCP */
							length = -length;
							_hoops_SICPR = true;
						}

						ALLOC (_hoops_AGPHR, _hoops_RCCII);
						_hoops_AGPHR->_hoops_CGHPR = _hoops_AGPHR->_hoops_SGHPR = _hoops_AGPHR->up = _hoops_AGPHR->_hoops_GRHPR = null;

						/* _hoops_HCR _hoops_RHGS _hoops_AIRC */
						_hoops_AGPHR->face_attributes = ts->face_attributes;

						if (regions)
							_hoops_AGPHR->face_attributes.region = regions[face_indices[2]];
						else
							_hoops_AGPHR->face_attributes.region = 0;

						_hoops_AGPHR->length = length;
						_hoops_AGPHR->vertices = _hoops_AIHA;
						_hoops_AGPHR->faces = face_indices;
						_hoops_AGPHR->_hoops_HHAHR = false;
						_hoops_AGPHR->_hoops_SICPR = _hoops_SICPR;
						_hoops_AGPHR->_hoops_GCCII = *_hoops_AIHA;
						_hoops_AGPHR->_hoops_CPGPR = 0;

						if ((node = root) == null) {
							root = _hoops_AGPHR;
						}
						else _hoops_PCCAR {
							if (_hoops_SAGI (_hoops_AGPHR->face_attributes,
														   node->face_attributes, ~0) &&
								(node->face_attributes.region == _hoops_AGPHR->face_attributes.region ||
								 node->face_attributes.region != region &&
								 _hoops_AGPHR->face_attributes.region != region)) {
								_hoops_AGPHR->_hoops_GRHPR = node->_hoops_GRHPR;
								node->_hoops_GRHPR = _hoops_AGPHR;
								break;
							}
							else if (_hoops_HGPHR (_hoops_AGPHR->face_attributes,
															   node->face_attributes)) {
								if (node->_hoops_CGHPR != null)
									node = node->_hoops_CGHPR;
								else {
									/* _hoops_PPSI _hoops_GGSR _hoops_IRS _hoops_CCAH '_hoops_CRGP' _hoops_RIIS */

									node->_hoops_CGHPR = _hoops_AGPHR;
									_hoops_AGPHR->up = node;
									break;
								}
							}
							else {
								if (node->_hoops_SGHPR != null)
									node = node->_hoops_SGHPR;
								else {
									/* _hoops_PPSI _hoops_GGSR _hoops_IRS _hoops_CCAH '_hoops_RRPAR' _hoops_RIIS */
									node->_hoops_SGHPR = _hoops_AGPHR;
									_hoops_AGPHR->up = node;
									break;
								}
							}
						}

						_hoops_AIHA += length;
						face_indices += length;
					}

					_hoops_ASRGR = &ts->next;
				}
			}
		}
		else do {
			int				_hoops_PHHA = ts->_hoops_PHHA;
			int const *		lengths = ts->lengths;
			int const *		_hoops_AIHA = ts->_hoops_AIHA;
			int const *		face_indices = ts->face_indices;
			int const *		regions = _hoops_IPRI->local_face_attributes.regions;

			/* _hoops_SRS _hoops_SPIC _hoops_GRR _hoops_GHPAH _hoops_GGR _hoops_GRR _hoops_CRHH,
			 * _hoops_SHCAH/_hoops_HRHAR _hoops_HPP _hoops_AIRC (_hoops_RPP _hoops_GII)
			 */
			if (face_indices == null) {
				/* _hoops_PAH _hoops_PSP _hoops_RPIP _hoops_SGH _hoops_CHHA _hoops_PSPI, _hoops_CAHP _hoops_RH _hoops_HSSHH */
				int alter *		fi;
				int				face = 0;

				ALLOC_ARRAY (fi, ts->total, int);
				face_indices = ts->face_indices = fi;
				ts->_hoops_SGAHR = ts->total;

				while (_hoops_PHHA-- > 0) {
					int		length = *lengths++;

					if (length < 0)
						length = -length;
					length -= 2;

					*fi++ = 0;
					*fi++ = 0;
					while (length-- > 0)
						*fi++ = face++;
				}

				_hoops_PHHA = ts->_hoops_PHHA;
				lengths = ts->lengths;
				face_indices = ts->face_indices;
			}

			while (_hoops_PHHA-- > 0) {
				int			length = *lengths++;
				bool		_hoops_HHAHR = false;
				bool		_hoops_SICPR = false;
				int			first;
				int			_hoops_GCCII = *_hoops_AIHA;

				if (length < 0) {		/* _hoops_HAHCP */
					length = -length;
					_hoops_SICPR = true;
				}
				length -= 2;

				while (length > 0) {
					first = face_indices[2];

					ZALLOC (_hoops_AGPHR, _hoops_RCCII);
					_hoops_AGPHR->_hoops_CGHPR = _hoops_AGPHR->_hoops_SGHPR = _hoops_AGPHR->up = _hoops_AGPHR->_hoops_GRHPR = null;

					_hoops_AAPHR (_hoops_AGPHR->face_attributes);
					_hoops_PIPHR (_hoops_CPRI, first, _hoops_AGPHR->face_attributes);

					_hoops_AGPHR->length = 2;
					_hoops_AGPHR->vertices = _hoops_AIHA;
					_hoops_AGPHR->faces = face_indices;
					_hoops_AGPHR->_hoops_HHAHR = _hoops_HHAHR;
					_hoops_AGPHR->_hoops_SICPR = _hoops_SICPR;
					_hoops_AGPHR->_hoops_GCCII = _hoops_GCCII;
					_hoops_AGPHR->_hoops_CPGPR = 0;

					if ((node = root) == null) {
						root = _hoops_AGPHR;
					}
					else _hoops_PCCAR {
						if (_hoops_SAGI (_hoops_AGPHR->face_attributes, node->face_attributes, ~0)) {
							_hoops_AGPHR->_hoops_GRHPR = node->_hoops_GRHPR;
							node->_hoops_GRHPR = _hoops_AGPHR;
							break;
						}
						else if (_hoops_HGPHR (_hoops_AGPHR->face_attributes, node->face_attributes)) {
							if (node->_hoops_CGHPR != null)
								node = node->_hoops_CGHPR;
							else {
								/* _hoops_PPSI _hoops_GGSR _hoops_IRS _hoops_CCAH '_hoops_CRGP' _hoops_RIIS */

								node->_hoops_CGHPR = _hoops_AGPHR;
								_hoops_AGPHR->up = node;
								break;
							}
						}
						else {
							if (node->_hoops_SGHPR != null)
								node = node->_hoops_SGHPR;
							else {
								/* _hoops_PPSI _hoops_GGSR _hoops_IRS _hoops_CCAH '_hoops_RRPAR' _hoops_RIIS */
								node->_hoops_SGHPR = _hoops_AGPHR;
								_hoops_AGPHR->up = node;
								break;
							}
						}
					}

					_hoops_PCCAR {
						int						current = face_indices[2];
						_hoops_GIIPR		_hoops_PSCII = 0;
						_hoops_SARHR	_hoops_CSSGA = 0;

						//_hoops_RPP (_hoops_RHRHR->_hoops_SGI != _hoops_IRAP)
						_hoops_PSCII = *_hoops_CPRI->_hoops_CHHPR(current);

						_hoops_CSSGA = (_hoops_SARHR)_hoops_PSCII;
						if (_hoops_CPRI->_hoops_GARHR)
							_hoops_CSSGA |= _hoops_CPRI->_hoops_GARHR[current];

						if ((_hoops_CSSGA & _hoops_PHGPR) != (_hoops_AGPHR->face_attributes.flags & _hoops_PHGPR))
							break;

						if (_hoops_PSCII != 0) {
							if (BIT (_hoops_PSCII, LFA_EXPLICIT_COLOR_BY_FINDEX)) {
								if (_hoops_CPRI->findices[current] != _hoops_CPRI->findices[first])
									break;
							}
							else if (BIT (_hoops_PSCII, LFA_EXPLICIT_COLOR_BY_VALUE)) {
								if (_hoops_CPRI->colors[current].red != _hoops_CPRI->colors[first].red ||
									_hoops_CPRI->colors[current].green != _hoops_CPRI->colors[first].green ||
									_hoops_CPRI->colors[current].blue != _hoops_CPRI->colors[first].blue)
									break;
							}
							if (BIT (_hoops_PSCII, _hoops_HAGI)) {
								if (_hoops_CPRI->_hoops_AHHIR[current] != _hoops_CPRI->_hoops_AHHIR[first])
									break;
							}
							if (regions != null) {
								if (regions[current] != regions[first])
									break;
							}

							/* _hoops_RGR _hoops_RSSI _hoops_PAH _hoops_PICII _hoops_IS _hoops_RH _hoops_SCGR _hoops_GHPAH */
							if (BIT (_hoops_PSCII, _hoops_IGAHR))
								_hoops_AGPHR->_hoops_CPGPR |= _hoops_GPSIR;
						}

						++_hoops_AGPHR->length;
						++_hoops_AIHA;
						++face_indices;
						if (!_hoops_SICPR)
							_hoops_HHAHR = !_hoops_HHAHR;

						if (--length <= 0)
							break;

						if (_hoops_AGPHR->_hoops_HHAHR) {
							/* _hoops_SAHR _hoops_SSAS _hoops_IRS _hoops_RSRA _hoops_AAGIR _hoops_SCPH,
							 * _hoops_HHSA _hoops_HPIH _hoops_IHSA */
							break;
						}
					}
				}
				/* _hoops_HSGR _hoops_ISGR _hoops_HPIRA _hoops_IIGR _hoops_RGR _hoops_CGGR */
				_hoops_AIHA += 2;
				face_indices += 2;
			}
		} while ((ts = ts->next) != null);

		/* _hoops_CGH _hoops_HA _hoops_SHH _hoops_SHSS _hoops_IS _hoops_HSGIR _hoops_GII _hoops_CCAH _hoops_CCGI */
		if ((_hoops_AGPHR = root) != null) do {
			_hoops_RCCII			*_hoops_HCPHR;

			/* _hoops_SSS _hoops_IRS _hoops_RIIS */
			_hoops_PCCAR {
				if (_hoops_AGPHR->_hoops_CGHPR != null) _hoops_AGPHR = _hoops_AGPHR->_hoops_CGHPR;
				else if (_hoops_AGPHR->_hoops_SGHPR != null) _hoops_AGPHR = _hoops_AGPHR->_hoops_SGHPR;
				else break;
			}

			if ((_hoops_GSCII = _hoops_AGPHR->up) != null) {
				if (_hoops_GSCII->_hoops_CGHPR == _hoops_AGPHR)
					_hoops_GSCII->_hoops_CGHPR = null;
				else if (_hoops_GSCII->_hoops_SGHPR == _hoops_AGPHR)
					_hoops_GSCII->_hoops_SGHPR = null;
			}

			_hoops_HCPHR = _hoops_AGPHR;

			ZALLOC (ts, Tristrip);
			_hoops_ICAI (ts);
			ts->next = _hoops_IPRI->tristrips;
			_hoops_IPRI->tristrips = ts;
			ts->face_attributes = _hoops_AGPHR->face_attributes;
			ts->same_colors = _hoops_ICCII;

			/* _hoops_RPR _hoops_GH _hoops_RH _hoops_PHI _hoops_IIGR _hoops_IIRGR */
			{
				int		total = 0;
				int		_hoops_PHHA = 0;

				do {
					if (total + _hoops_AGPHR->length > 1<<16)
						break;
					total += _hoops_AGPHR->length;

					++_hoops_PHHA;
				} while ((_hoops_AGPHR = _hoops_AGPHR->_hoops_GRHPR) != null);
				ts->_hoops_PHHA = _hoops_PHHA;
			}
			_hoops_AGPHR = _hoops_HCPHR;

			ALLOC_ARRAY (ts->lengths, ts->_hoops_PHHA, int);
			ts->lengths_allocated = ts->_hoops_PHHA;

			/* _hoops_HGCR _hoops_RH _hoops_IHHA _hoops_PPR _hoops_APSR _hoops_SPCC */
			{
				int		total = 0;
				int *	_hoops_IAIPR = ts->lengths;

				do {
					if (total + _hoops_AGPHR->length > 1<<16)
						break;
					total += _hoops_AGPHR->length;

					if (_hoops_AGPHR->_hoops_SICPR)
						*_hoops_IAIPR++ = -_hoops_AGPHR->length;
					else
						*_hoops_IAIPR++ = _hoops_AGPHR->length;
				} while ((_hoops_AGPHR = _hoops_AGPHR->_hoops_GRHPR) != null);
				ts->total = total;
			}
			_hoops_AGPHR = _hoops_HCPHR;

			_hoops_HCPHR = _hoops_AGPHR->up;	// _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_SPCC _hoops_SAIPR

			ALLOC_ARRAY (ts->_hoops_AIHA, ts->total, int);
			ALLOC_ARRAY (ts->face_indices, ts->total, int);
			ts->_hoops_IPII = ts->_hoops_SGAHR = ts->total;

			ts->_hoops_RAHH |= _hoops_AAHH;

			{
				int		total = 0;
				int				*_hoops_RPIPR = ts->_hoops_AIHA;
				int				*_hoops_PAPHR = ts->face_indices;
				_hoops_RCCII	*_hoops_ICPHR;

				/* _hoops_IH _hoops_GRR _hoops_SARGR _hoops_CCA _hoops_RH _hoops_PSHR _hoops_AIRC... */
				do {
					if (total + _hoops_AGPHR->length > 1<<16)
						break;
					total += _hoops_AGPHR->length;

					if (_hoops_AGPHR->_hoops_HHAHR) {
						/* _hoops_RSRA _hoops_AAGIR _hoops_SCPH */
						*_hoops_RPIPR++ = _hoops_AGPHR->vertices[1];
						*_hoops_RPIPR++ = _hoops_AGPHR->vertices[0];
						*_hoops_RPIPR++ = _hoops_AGPHR->vertices[2];
						*_hoops_PAPHR++ = _hoops_AGPHR->faces[1];
						*_hoops_PAPHR++ = _hoops_AGPHR->faces[0];
						*_hoops_PAPHR++ = _hoops_AGPHR->faces[2];
					}
					else {
						_hoops_AIGA (_hoops_AGPHR->vertices, _hoops_AGPHR->length, int, _hoops_RPIPR);
						if (_hoops_AGPHR->_hoops_SICPR)
							*_hoops_RPIPR = _hoops_AGPHR->_hoops_GCCII;
						_hoops_AIGA (_hoops_AGPHR->faces, _hoops_AGPHR->length, int, _hoops_PAPHR);
						_hoops_RPIPR += _hoops_AGPHR->length;
						_hoops_PAPHR += _hoops_AGPHR->length;
					}

					if (_hoops_AGPHR->face_attributes.region != ts->face_attributes.region)
						ts->face_attributes.region = -1;

					ts->_hoops_CPGPR |= _hoops_AGPHR->_hoops_CPGPR;

					_hoops_ICPHR = _hoops_AGPHR->_hoops_GRHPR;
					FREE (_hoops_AGPHR, _hoops_RCCII);
				} while ((_hoops_AGPHR = _hoops_ICPHR) != null);

				if (_hoops_AGPHR != null)	{	// _hoops_HAR _hoops_CPHR _hoops_CCA _hoops_RGR _hoops_SSAI _hoops_GAPR
					_hoops_GSCII = _hoops_AGPHR;	// _hoops_HIS _hoops_HS _hoops_CRIPR _hoops_HAPR _hoops_APHS _hoops_SCH
					_hoops_AGPHR->up = _hoops_HCPHR;
				}
			}
		} while ((_hoops_AGPHR = _hoops_GSCII) != null);

		/* _hoops_HA _hoops_ICIC _hoops_IS _hoops_APRI _hoops_RHGS _hoops_IIRGR */
		while ((ts = _hoops_RSCII) != null) {
			_hoops_RSCII = ts->next;
			if (_hoops_ISAI (ts) == 0)
				HI_Free_Tristrip (ts);
		}

		/* _hoops_RPP _hoops_SR _hoops_RGAR _hoops_HS _hoops_SPR _hoops_CGGR _hoops_CCA _hoops_IRS _hoops_HSP _hoops_HSGP,
		 * _hoops_IHIS _hoops_IS _hoops_RSGR _hoops_IH _hoops_AIRI _hoops_HIGR _hoops_CHCRA
		 */
		{
			Tristrip **			_hoops_ASRGR;

			/* _hoops_SSS _hoops_IRS _hoops_CGGR _hoops_CCA _hoops_IRS _hoops_HSGP */
			_hoops_ASRGR = &_hoops_IPRI->tristrips;
			while ((ts = *_hoops_ASRGR) != null) {
				if (ts->face_attributes.pattern != FP_SOLID) {
					/* _hoops_GSGI _hoops_IRS _hoops_AHCAH */
					break;
				}
				_hoops_ASRGR = &ts->next;
			}
			if (ts != null) {	/* _hoops_GGHP _hoops_SPR, _hoops_IHSH _hoops_RHIR _hoops_RH _hoops_ACSP */
				/* _hoops_PIP: _hoops_HAPR _hoops_RPGP _hoops_ISHS _hoops_RGAR _hoops_RPP _hoops_AIAH _hoops_HPGR _hoops_RSGR _hoops_IIGR _hoops_HIGR */
				while ((ts = ts->next) != null) {
					if (ts->face_attributes.pattern != FP_SOLID) {
						/* _hoops_HPIH _hoops_HSP _hoops_HSGP, _hoops_PAH'_hoops_RA _hoops_SGGC */
						break;
					}
					else if (ts->next == null) {
						/* _hoops_SAHR _hoops_RH _hoops_SPR, _hoops_IHIS _hoops_RH _hoops_AHCAH _hoops_IS _hoops_RSGR _hoops_IIGR _hoops_HIGR */
						Tristrip *	_hoops_IIRHA = *_hoops_ASRGR;

						*_hoops_ASRGR = _hoops_IIRHA->next;
						_hoops_IIRHA->next = null;
						ts->next = _hoops_IIRHA;
						break;
					}
				}
			}
		}

		if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
			_hoops_GIIPR		*flags = _hoops_CPRI->_hoops_CHHPR();
			int						count = _hoops_IPRI->face_count;

			do *flags++ &= ~_hoops_IGAHR;
			while (--count > 0);
		}
		else {
			_hoops_IPRI->local_face_attributes._hoops_SGRHR &= ~_hoops_IGAHR;
		}

		if (_hoops_CPRI->_hoops_PSRRA != 0)
			_hoops_IPRI->_hoops_ACRHR |= LFA_EXPLICIT_COLOR_BY_FINDEX;
		if (_hoops_CPRI->_hoops_HSRRA != 0)
			_hoops_IPRI->_hoops_ACRHR |= LFA_EXPLICIT_COLOR_BY_VALUE;
		if (_hoops_CPRI->_hoops_SRAPA != 0)
			_hoops_IPRI->_hoops_ACRHR |= _hoops_HAGI;
		if (_hoops_CPRI->_hoops_CPIAA != 0)
			_hoops_IPRI->_hoops_ACRHR |= _hoops_IAGI;
		if (_hoops_CPRI->_hoops_SIIPR != 0)
			_hoops_IPRI->_hoops_ACRHR |= _hoops_HSIPR;
	}

	_hoops_IPRI->polyhedron_flags &= ~_hoops_CCRHR;
#endif
}



HC_INTERFACE void HC_CDECL HC_MSet_Face_Colors_By_FIndex (
	Key						key,
	char const *			geometry,
	int						offset,
	int						count,
	float const *			findices)
{
	_hoops_PAPPR context("MSet_Face_Colors_By_FIndex");

#ifdef _hoops_GCGHR
	_hoops_IRPPR ("Geometry Colors");
#else
#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else

	CODE_GENERATION (
		int		count2 = count;
		if (count == 0) {
			HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Face_Colors_By_FIndex (LOOKUP (%D), ", key));
			HI_Dump_Code (Sprintf_S (null, "%S, ", geometry));
			HI_Dump_Code (Sprintf_D (null, "%d, 0, 0);\n", offset));
		}
		else {
			HI_Dump_Code (Sprintf_D (null, "{float* findices = (float*) malloc(sizeof(float)*%d);\n", count2));
			++HOOPS_WORLD->_hoops_ISPPR;
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (_hoops_CHCHR (null, "findices[%d] = %f;\n", count2, findices[count2]));
			}
			HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Face_Colors_By_FIndex (LOOKUP (%D), ", key));
			HI_Dump_Code (Sprintf_S (null, "%S, ", geometry));
			HI_Dump_Code (Sprintf_DD (null, "%d, %d, findices);\n", offset, count));
			HI_Dump_Code ("free (findices);\n");
			--HOOPS_WORLD->_hoops_ISPPR;
			HI_Dump_Code ("}\n");
		}
	);

	if (count < 0) {
		HE_ERROR (HEC_MSET_FACE, HES_INVALID_COUNT, "Count is negative");
		return;
	}
	if (offset < 0) {
		HE_ERROR (HEC_MSET_FACE, HES_INVALID_OFFSET, "Offset is negative");
		return;
	}

	Polyhedron *			_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_PCGPP)) == null)
		return;

	Color_Object	_hoops_HSCII;
	_hoops_HCRPR			name;
	HI_Canonize_Chars (geometry, &name);
	char const *	_hoops_RPPA = name.text;
	if (!HI_Decipher_Color_Target (context, &_hoops_RPPA, _hoops_RPPA + name.length, true, &_hoops_HSCII, Color_FACE)) {
		HE_ERROR (HEC_MSET_FACE, HES_CANNOT_SET_ATTRIBUTE, "Cannot decipher color type");
	}
	else if (ANYBIT (_hoops_HSCII, ~Color_FACE)) {
		HE_ERROR (HEC_MSET_FACE, HES_CANNOT_SET_ATTRIBUTE, "Only a face color may be set on a face");
	}
	else if (!BIT (_hoops_HSCII, Color_FACE)) {
		; // _hoops_IRAHR
	}
	else if (_hoops_IPRI->face_count < offset + count) {
		char	buf[MAX_ERRMSG];
		HE_ERROR2 (HEC_MSET_FACE, HES_INVALID_OFFSET,
				   Sprintf_D (null, "Shell or mesh only has %d faces -", _hoops_IPRI->face_count),
				   Sprintf_DD (buf, "can't change %d of them at offset %d", count, offset));
	}
	else {
		Local_Face_Attributes *	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;

		if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR) &&
			!BIT(_hoops_IPRI->local_face_attributes._hoops_SGRHR, LFA_EXPLICIT_COLOR_BY_FINDEX) &&
			(offset != 0 || count != _hoops_IPRI->face_count)) {
			/* _hoops_SR _hoops_CHR _hoops_HAR _hoops_RGSR _hoops_IRS _hoops_RIP _hoops_GPP _hoops_RCSAR _hoops_HSP, _hoops_HIS _hoops_RPP _hoops_IRS _hoops_SGI _hoops_CRPR _hoops_SSCP _hoops_HAR _hoops_GAPR
			_hoops_RPII _hoops_PSPP, _hoops_SR _hoops_RRP _hoops_IS _hoops_AA _hoops_SCH _hoops_HA */
			ZALLOC_ARRAY(_hoops_CPRI->flags, _hoops_IPRI->face_count, _hoops_GIIPR);
			for (int i = 0; i < _hoops_IPRI->face_count; i++)
				_hoops_CPRI->flags[i] = _hoops_CPRI->_hoops_SGRHR;
			_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
		}

		if (_hoops_CPRI->findices == null)
			HI_Initialize_Face_Attributes (_hoops_IPRI, LFA_EXPLICIT_COLOR_BY_FINDEX);

		_hoops_ACGHR *	colors = &_hoops_CPRI->findices[offset];
		_hoops_GIIPR *	flags = _hoops_CPRI->_hoops_CHHPR(offset);

		bool	_hoops_ISCII = BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR);

		if (!_hoops_ISCII) {
			*flags &= ~LFA_EXPLICIT_COLOR_BY_VALUE;
			_hoops_CPRI->_hoops_HSRRA = 0;
			*flags |= LFA_EXPLICIT_COLOR_BY_FINDEX;
			_hoops_CPRI->_hoops_PSRRA = _hoops_IPRI->face_count;
		}

		do {
			float			findex = *findices;

			if (findex < -0.5f || findex >= ((float)_hoops_GPARA + 0.5f)) {
				char			buf[MAX_ERRMSG];
				float			max = ((float)_hoops_GPARA + 0.5f), min = -0.5f;

				HE_ERROR2 (HEC_COLOR_MAP, HES_OUT_OF_RANGE_COLOR_INDEX,
						   Sprintf_F (null, "Color index %f is out of range -", findex),
						   Sprintf_FF (buf, "must be between %f and %f", min, max));

				*colors++ = 0.0f;
			}
			else
				*colors++ = findex;

			/* (_hoops_AGCR _hoops_CSCII _hoops_CHR _hoops_SSAAA _hoops_IH _hoops_RH '_hoops_PSP _hoops_PGHC _hoops_RGSR' _hoops_AGIR)	 */
			if (!ANYBIT (*flags, _hoops_IACHR)) {
				if (_hoops_ISCII) {
					*flags |= LFA_EXPLICIT_COLOR_BY_FINDEX;
					++_hoops_CPRI->_hoops_PSRRA;
				}
				_hoops_IPRI->_hoops_ACRHR &= ~LFA_EXPLICIT_COLOR_BY_FINDEX;
			}
			else if (BIT (*flags, LFA_EXPLICIT_COLOR_BY_VALUE)) {
				if (_hoops_ISCII) {
					*flags &= ~LFA_EXPLICIT_COLOR_BY_VALUE;
					--_hoops_CPRI->_hoops_HSRRA;
					*flags |= LFA_EXPLICIT_COLOR_BY_FINDEX;
					++_hoops_CPRI->_hoops_PSRRA;
				}
				_hoops_IPRI->_hoops_ACRHR &= ~_hoops_IACHR;
			}
			*flags |= _hoops_IGAHR;

			if (_hoops_ISCII)
				++flags;
			++findices;
		} _hoops_RGGA (--count == 0);

		_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;

		/* _hoops_RRRPR _hoops_IIGR _hoops_SPIGA _hoops_HHS _hoops_SHH _hoops_IRAP */
		if (_hoops_IPRI->owner) {
			if (!BIT (_hoops_IPRI->owner->_hoops_RCGC, _hoops_ASRRA))
				HI_Propagate_Maybes (context, _hoops_IPRI->owner, _hoops_ASRRA);
		}

		/* _hoops_HPCAR _hoops_IGSIP _hoops_HRGR _hoops_SIGR */
		HI_Invalidate_Display_Lists (context, _hoops_IPRI);
		_hoops_SASIR (context, (Geometry *)_hoops_IPRI, _hoops_GPSIR|_hoops_RPSIR);
	}

	_hoops_RGAIR (name);
	_hoops_IRRPR();
#endif
#endif
}



HC_INTERFACE void HC_CDECL HC_MSet_Vertex_Colors_By_FIndex (
	Key							key,
	char const *				geometry,
	int							offset,
	int							count,
	float const *				findices)
{
	_hoops_PAPPR context("MSet_Vertex_Colors_By_FIndex");

#ifdef _hoops_GCGHR
	_hoops_IRPPR ("Geometry Colors");
#else
#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else
	CODE_GENERATION (
		int		count2 = count;
		HI_Dump_Code (Sprintf_D (null, "{float* findices = (float*) malloc(sizeof(float)*%d);\n", count2));
		++HOOPS_WORLD->_hoops_ISPPR;
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "findices[%d] = %f;\n", count2, findices[count2]));
		}
		HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Vertex_Colors_By_FIndex (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_S (null, "%S, ", geometry));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, findices);\n", offset, count));
		HI_Dump_Code ("free (findices);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);



	if (count < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		return;
	}

	if (offset < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_OFFSET, "Offset is negative");
		return;
	}

	if (count == 0)
		return;  /* _hoops_CPRSH */

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_ACGPP)) == null)
		return;

	_hoops_CGHIR *		_hoops_SSCII = null;
	_hoops_ACGHR *		_hoops_PAHIR = null;
	_hoops_ACGHR *		ecolors = null;
	_hoops_ACGHR *		fcolors = null;
	int						_hoops_PIRRA = 0;
	Local_Vertex_Flags *	flags = null;
	bool					_hoops_ISCII = false;

	Local_Vertex_Attributes *	_hoops_SPRI = null;
	_hoops_AGHIR *	_hoops_PGHIR = null;


	Color_Object	_hoops_HSCII;
	_hoops_HCRPR			name;
	HI_Canonize_Chars (geometry, &name);
	char const * _hoops_RPPA = name.text;
	if (!HI_Decipher_Color_Target (context, &_hoops_RPPA, _hoops_RPPA + name.length, true, &_hoops_HSCII,
		_hoops_IPRI->type == _hoops_CSIP ? (Color_FACE|Color_EDGE) : (Color_FACE|Color_EDGE|Color_VERTEX))) {
		; // _hoops_ASIGA _hoops_PSIIR
	}
	else if (_hoops_IPRI->type == _hoops_CSIP) {
		PolyCylinder *	_hoops_HSPIR = (PolyCylinder *)_hoops_IPRI;

		if (ANYBIT (_hoops_HSCII, ~(Color_EDGE|Color_FACE))) {
			HE_ERROR (HEC_MSET_VERTEX, HES_CANNOT_SET_ATTRIBUTE, "Only edge or face color may be set on a vertex");
		}
		else if (_hoops_HSPIR->point_count < offset + count) {
			char	buf[MAX_ERRMSG];
			HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
					   Sprintf_D (null, "PoltCylinder only has %d vertices -", _hoops_HSPIR->point_count),
					   Sprintf_DD (buf, "can't change %d of them at offset %d", count, offset));
		}
		else {
			_hoops_PGHIR = _hoops_HSPIR->_hoops_RGHIR;

			if (BIT (_hoops_HSCII, Color_EDGE)) {
				if (_hoops_PGHIR == null)
					_hoops_PGHIR = HI_Initialize_PCA_Vertex_Attributes (_hoops_HSPIR, _hoops_IHRRA);
				else if (_hoops_PGHIR->_hoops_HGHIR == null) {
					if (BIT (_hoops_HSCII, Color_FRONT) && _hoops_PGHIR->_hoops_IGHIR != null)
						_hoops_PGHIR->_hoops_HGHIR = _hoops_PGHIR->_hoops_IGHIR;
					else
						_hoops_PGHIR = HI_Initialize_PCA_Vertex_Attributes (_hoops_HSPIR, _hoops_IHRRA);
				}
				else if (_hoops_PGHIR->_hoops_HGHIR == _hoops_PGHIR->_hoops_IGHIR &&
						 !BIT (_hoops_HSCII, Color_FRONT)) {
					/* _hoops_IHSA _hoops_HSSRR */
					_hoops_PGHIR->_hoops_HGHIR = (_hoops_ACGHR *)
						HI_Clone_Anything (_hoops_PGHIR->_hoops_HGHIR, _hoops_HSPIR->point_count * (long)sizeof(_hoops_ACGHR));
				}
				ecolors = &_hoops_PGHIR->_hoops_HGHIR[offset];
			}

			if (BIT (_hoops_HSCII, Color_FRONT)) {
				if (_hoops_PGHIR == null)
					_hoops_PGHIR = HI_Initialize_PCA_Vertex_Attributes (_hoops_HSPIR, _hoops_CHRRA);
				else if (_hoops_PGHIR->_hoops_IGHIR == null) {
					if (BIT (_hoops_HSCII, Color_EDGE) && _hoops_PGHIR->_hoops_HGHIR != null)
						_hoops_PGHIR->_hoops_IGHIR = _hoops_PGHIR->_hoops_HGHIR;
					else
						_hoops_PGHIR = HI_Initialize_PCA_Vertex_Attributes (_hoops_HSPIR, _hoops_CHRRA);
				}
				else if (_hoops_PGHIR->_hoops_IGHIR == _hoops_PGHIR->_hoops_HGHIR &&
						 !BIT (_hoops_HSCII, Color_EDGE)) {
					/* _hoops_IHSA _hoops_HSSRR */
					_hoops_PGHIR->_hoops_IGHIR = (_hoops_ACGHR *)
						HI_Clone_Anything (_hoops_PGHIR->_hoops_IGHIR, _hoops_HSPIR->point_count * (long)sizeof(_hoops_ACGHR));
				}
				fcolors = &_hoops_PGHIR->_hoops_IGHIR[offset];
			}

			_hoops_SSCII	 = &_hoops_PGHIR->flags[offset];
		}
	}
	else {
		if (ANYBIT (_hoops_HSCII, ~(Color_MARKER|Color_VERTEX|Color_EDGE|Color_FACE))) {
			HE_ERROR (HEC_MSET_VERTEX, HES_CANNOT_SET_ATTRIBUTE,
				"Only marker/vertex, edge, or face color may be set on a vertex");
		}
		else if (_hoops_IPRI->point_count < offset + count) {
			char	buf[MAX_ERRMSG];
			HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
					   Sprintf_D (null, "Shell or mesh only has %d vertices -", _hoops_IPRI->point_count),
					   Sprintf_DD (buf, "can't change %d of them at offset %d", count, offset));
		}
		else {
			_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;
			_hoops_PIRRA = _hoops_SPRI->_hoops_HIRRA;

			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR) &&
				!ANYBIT(_hoops_IPRI->local_vertex_attributes._hoops_SGRHR, _hoops_GGSII) &&
				(offset != 0 || count != _hoops_IPRI->point_count)) {
				/* _hoops_SR _hoops_CHR _hoops_HAR _hoops_RGSR _hoops_IRS _hoops_RIP _hoops_GPP _hoops_RCSAR _hoops_HSP, _hoops_HIS _hoops_RPP _hoops_IRS _hoops_SGI _hoops_CRPR _hoops_SSCP _hoops_HAR _hoops_GAPR
				_hoops_RPII _hoops_PSPP, _hoops_SR _hoops_RRP _hoops_IS _hoops_AA _hoops_SCH _hoops_HA */
				ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
				for (int i = 0; i < _hoops_IPRI->point_count; i++)
					_hoops_SPRI->flags[i] = _hoops_SPRI->_hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
			}

			if (BIT (_hoops_HSCII, Color_VERTEX)) {
				if (_hoops_SPRI->_hoops_HAHIR == null) {
					if (BIT (_hoops_HSCII, Color_EDGE) && _hoops_SPRI->_hoops_HGHIR != null)
						_hoops_SPRI->_hoops_HAHIR = _hoops_SPRI->_hoops_HGHIR;
					else if (BIT (_hoops_HSCII, Color_FRONT) && _hoops_SPRI->_hoops_IGHIR != null)
						_hoops_SPRI->_hoops_HAHIR = _hoops_SPRI->_hoops_IGHIR;
					else
						HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_SIRRA, 0);
				}
				else {
					/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GCSP _hoops_HIH _hoops_ASAI _hoops_RGSR _hoops_IRS _hoops_GCSP _hoops_ARIP, _hoops_IPS */
					if (_hoops_SPRI->_hoops_HAHIR == _hoops_SPRI->_hoops_HGHIR &&
						_hoops_SPRI->_hoops_HAHIR == _hoops_SPRI->_hoops_IGHIR &&
						ANYBIT (_hoops_HSCII, Color_EDGE|Color_FRONT) &&
						!ALLBITS (_hoops_HSCII, Color_EDGE|Color_FRONT)) {
						/* 3-_hoops_PPRRR _hoops_HSSRR, _hoops_SPR _hoops_IIGR _hoops_RH _hoops_HIASR _hoops_GHHS _hoops_RAAP _hoops_GGSR */
						if (!BIT (_hoops_HSCII, Color_EDGE)) {
							_hoops_SPRI->_hoops_HGHIR = (_hoops_ACGHR *)
								HI_Clone_Anything (_hoops_SPRI->_hoops_HGHIR,
												   _hoops_IPRI->point_count *
												   (long)sizeof(_hoops_ACGHR));
						}
						else /* _hoops_RPP (!_hoops_IRRC (_hoops_RGSII, _hoops_RCRRA)) */ {
							_hoops_SPRI->_hoops_IGHIR = (_hoops_ACGHR *)
								HI_Clone_Anything (_hoops_SPRI->_hoops_IGHIR,
												   (_hoops_IPRI->point_count +
													_hoops_IPRI->_hoops_GCRHR) *
												   (long)sizeof(_hoops_ACGHR));
						}
					}
					else if (_hoops_SPRI->_hoops_HAHIR == _hoops_SPRI->_hoops_HGHIR &&
								!BIT (_hoops_HSCII, Color_EDGE) ||
							 _hoops_SPRI->_hoops_HAHIR == _hoops_SPRI->_hoops_IGHIR &&
								!BIT (_hoops_HSCII, Color_FRONT)) {
						/* _hoops_IHSA _hoops_HSSRR */
						_hoops_SPRI->_hoops_HAHIR = (_hoops_ACGHR *)
							HI_Clone_Anything (_hoops_SPRI->_hoops_HAHIR,
											   _hoops_IPRI->point_count *
											   (long)sizeof(_hoops_ACGHR));
					}
				}
				_hoops_PAHIR = &_hoops_SPRI->_hoops_HAHIR[offset];
			}
			else _hoops_PAHIR = null;

			if (BIT (_hoops_HSCII, Color_EDGE)) {
				if (_hoops_SPRI->_hoops_HGHIR == null) {
					if (BIT (_hoops_HSCII, Color_VERTEX) && _hoops_SPRI->_hoops_HAHIR != null)
						_hoops_SPRI->_hoops_HGHIR = _hoops_SPRI->_hoops_HAHIR;
					else if (BIT (_hoops_HSCII, Color_FRONT) && _hoops_SPRI->_hoops_IGHIR != null)
						_hoops_SPRI->_hoops_HGHIR = _hoops_SPRI->_hoops_IGHIR;
					else
						HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_RPHPR, 0);
				}
				else {
					/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GCSP _hoops_HIH _hoops_ASAI _hoops_RGSR _hoops_IRS _hoops_GCSP _hoops_ARIP, _hoops_IPS */
					if (_hoops_SPRI->_hoops_HGHIR == _hoops_SPRI->_hoops_HAHIR &&
						_hoops_SPRI->_hoops_HGHIR == _hoops_SPRI->_hoops_IGHIR &&
						ANYBIT (_hoops_HSCII, Color_VERTEX|Color_FRONT) &&
						!ALLBITS (_hoops_HSCII, Color_VERTEX|Color_FRONT)) {
						/* 3-_hoops_PPRRR _hoops_HSSRR, _hoops_SPR _hoops_IIGR _hoops_RH _hoops_HIASR _hoops_GHHS _hoops_RAAP _hoops_GGSR */
						if (!BIT (_hoops_HSCII, Color_VERTEX)) {
							_hoops_SPRI->_hoops_HAHIR = (_hoops_ACGHR *)
								HI_Clone_Anything (_hoops_SPRI->_hoops_HAHIR,
												   _hoops_IPRI->point_count *
												   (long)sizeof(_hoops_ACGHR));
						}
						else /* _hoops_RPP (!_hoops_IRRC (_hoops_RGSII, _hoops_RCRRA)) */ {
							_hoops_SPRI->_hoops_IGHIR = (_hoops_ACGHR *)
								HI_Clone_Anything (_hoops_SPRI->_hoops_IGHIR,
												   (_hoops_IPRI->point_count +
													_hoops_IPRI->_hoops_GCRHR) *
												   (long)sizeof(_hoops_ACGHR));
						}
					}
					else if (_hoops_SPRI->_hoops_HGHIR == _hoops_SPRI->_hoops_HAHIR &&
								!BIT (_hoops_HSCII, Color_VERTEX) ||
							 _hoops_SPRI->_hoops_HGHIR == _hoops_SPRI->_hoops_IGHIR &&
								!BIT (_hoops_HSCII, Color_FRONT)) {
						/* _hoops_IHSA _hoops_HSSRR */
						_hoops_SPRI->_hoops_HGHIR = (_hoops_ACGHR *)
							HI_Clone_Anything (_hoops_SPRI->_hoops_HGHIR,
											   _hoops_IPRI->point_count *
											   (long)sizeof(_hoops_ACGHR));
					}
				}
				ecolors = &_hoops_SPRI->_hoops_HGHIR[offset];
			}
			else ecolors = null;

			if (BIT (_hoops_HSCII, Color_FRONT)) {
				if (_hoops_SPRI->_hoops_IGHIR == null) {
					if (_hoops_IPRI->_hoops_GCRHR != 0)
						HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_HARHR, 0);
					else if (BIT (_hoops_HSCII, Color_EDGE) && _hoops_SPRI->_hoops_HGHIR != null)
						_hoops_SPRI->_hoops_IGHIR = _hoops_SPRI->_hoops_HGHIR;
					else if (BIT (_hoops_HSCII, Color_VERTEX) && _hoops_SPRI->_hoops_HAHIR != null)
						_hoops_SPRI->_hoops_IGHIR = _hoops_SPRI->_hoops_HAHIR;
					else
						HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_HARHR, 0);
				}
				else {
					/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GCSP _hoops_HIH _hoops_ASAI _hoops_RGSR _hoops_IRS _hoops_GCSP _hoops_ARIP, _hoops_IPS */
					if (_hoops_SPRI->_hoops_IGHIR == _hoops_SPRI->_hoops_HAHIR &&
						_hoops_SPRI->_hoops_IGHIR == _hoops_SPRI->_hoops_HGHIR &&
						ANYBIT (_hoops_HSCII, Color_VERTEX|Color_EDGE) &&
						!ALLBITS (_hoops_HSCII, Color_VERTEX|Color_EDGE)) {
						/* 3-_hoops_PPRRR _hoops_HSSRR, _hoops_SPR _hoops_IIGR _hoops_RH _hoops_HIASR _hoops_GHHS _hoops_RAAP _hoops_GGSR */
						if (!BIT (_hoops_HSCII, Color_VERTEX)) {
							_hoops_SPRI->_hoops_HAHIR = (_hoops_ACGHR *)
								HI_Clone_Anything (_hoops_SPRI->_hoops_HAHIR,
												   _hoops_IPRI->point_count *
												   (long)sizeof(_hoops_ACGHR));
						}
						else /* _hoops_RPP (!_hoops_IRRC (_hoops_RGSII, _hoops_ACRRA)) */ {
							_hoops_SPRI->_hoops_HGHIR = (_hoops_ACGHR *)
								HI_Clone_Anything (_hoops_SPRI->_hoops_HGHIR,
												   _hoops_IPRI->point_count *
												   (long)sizeof(_hoops_ACGHR));
						}
					}
					else if (_hoops_SPRI->_hoops_IGHIR == _hoops_SPRI->_hoops_HAHIR && !BIT (_hoops_HSCII, Color_VERTEX) ||
							 _hoops_SPRI->_hoops_IGHIR == _hoops_SPRI->_hoops_HGHIR && !BIT (_hoops_HSCII, Color_EDGE)) {
						/* _hoops_IHSA _hoops_HSSRR */
						_hoops_SPRI->_hoops_IGHIR = (_hoops_ACGHR *)
							HI_Clone_Anything (_hoops_SPRI->_hoops_IGHIR,
											   (_hoops_IPRI->point_count +
												_hoops_IPRI->_hoops_GCRHR) *
											   (long)sizeof(_hoops_ACGHR));
					}
				}
				fcolors = &_hoops_SPRI->_hoops_IGHIR[offset];
			}
			else fcolors = null;

			flags  = _hoops_SPRI->_hoops_CHHPR(offset);
		}

		if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
			if (_hoops_PAHIR != null) {
				if (!ANYBIT (*flags, _hoops_APPRA)) {
					*flags |= _hoops_SIRRA;
					_hoops_SPRI->_hoops_PCRRA += count;
					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_SIRRA;
				}
				else if (BIT (*flags, _hoops_HCRRA)) {
					*flags &= ~_hoops_HCRRA;
					_hoops_SPRI->_hoops_ICRRA -= count;
					*flags |= _hoops_SIRRA;
					_hoops_SPRI->_hoops_PCRRA += count;
					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
				}
				else if (BIT (*flags, _hoops_CCRRA)) {
					*flags &= ~_hoops_CCRRA;
					_hoops_SPRI->_hoops_HIRRA -= count;
					*flags |= _hoops_SIRRA;
					_hoops_SPRI->_hoops_PCRRA += count;
					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
				}
			}

			if (ecolors != null) {
				if (!ANYBIT (*flags, _hoops_PPPRA)) {
					*flags |= _hoops_RPHPR;
					_hoops_SPRI->_hoops_CCHPR += count;
					_hoops_IPRI->_hoops_RSHPR &= ~_hoops_APHPR;
				}
				else if (BIT (*flags, _hoops_PPHPR)) {
					*flags &= ~_hoops_PPHPR;
					_hoops_SPRI->_hoops_SCHPR -= count;
					*flags |= _hoops_RPHPR;
					_hoops_SPRI->_hoops_CCHPR += count;
					_hoops_IPRI->_hoops_RSHPR &= ~_hoops_AGSII;
				}
			}

			if (fcolors != null) {
				if (!ANYBIT (*flags, _hoops_HPPRA)) {
					*flags |= _hoops_HARHR;
					_hoops_SPRI->_hoops_SIRHR += count;
					_hoops_IPRI->_hoops_ACRHR &= ~_hoops_IARHR;
				}
				else if (BIT (*flags, _hoops_AARHR)) {
					*flags &= ~_hoops_AARHR;
					_hoops_SPRI->_hoops_RCRHR -= count;
					*flags |= _hoops_HARHR;
					_hoops_SPRI->_hoops_SIRHR += count;
					_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PGSII;
				}
			}
		}
		else
			_hoops_ISCII = true;
	}


	do {
		float	findex = *findices;

		if (findex < -0.5f || findex >= ((float)_hoops_GPARA + 0.5f)) {
			float	max = ((float)_hoops_GPARA + 0.5f);
			float	min = -0.5f;

			char	buf[MAX_ERRMSG];
			HE_ERROR2 (HEC_COLOR_MAP, HES_OUT_OF_RANGE_COLOR_INDEX,
					   Sprintf_F (null, "Color index %f is out of range -", findex),
					   Sprintf_FF (buf, "must be between %f and %f", min, max));

			if (_hoops_PAHIR != null)
				*_hoops_PAHIR++ = 0.0f;
			if (ecolors != null)
				*ecolors++ = 0.0f;
			if (fcolors != null)
				*fcolors++ = 0.0f;
		}
		else {
			if (_hoops_PAHIR != null)
				*_hoops_PAHIR++ = findex;
			if (ecolors != null)
				*ecolors++ = findex;
			if (fcolors != null)
				*fcolors++ = findex;
		}

		/* (_hoops_AGCR _hoops_CSCII _hoops_CHR _hoops_SSAAA _hoops_IH _hoops_RH '_hoops_PSP _hoops_PGHC _hoops_RGSR' _hoops_AGIR) */

		if (_hoops_IPRI->type == _hoops_CSIP) {
			if (ecolors != null) {
				if (!ANYBIT (*_hoops_SSCII, _hoops_GPPRA)) {
					*_hoops_SSCII |= _hoops_IHRRA;
					++_hoops_PGHIR->_hoops_CCHPR;
				}
				else if (BIT (*_hoops_SSCII, _hoops_SHRRA)) {
					*_hoops_SSCII &= ~_hoops_SHRRA;
					--_hoops_PGHIR->_hoops_SCHPR;
					*_hoops_SSCII |= _hoops_IHRRA;
					++_hoops_PGHIR->_hoops_CCHPR;
				}
			}

			if (fcolors != null) {
				if (!ANYBIT (*_hoops_SSCII, _hoops_RPPRA)) {
					*_hoops_SSCII |= _hoops_CHRRA;
					++_hoops_PGHIR->_hoops_SIRHR;
				}
				else if (BIT (*_hoops_SSCII, _hoops_GIRRA)) {
					*_hoops_SSCII &= ~_hoops_GIRRA;
					--_hoops_PGHIR->_hoops_RCRHR;
					*_hoops_SSCII |= _hoops_CHRRA;
					++_hoops_PGHIR->_hoops_SIRHR;
				}
			}

			++_hoops_SSCII;
		}
		else {
			if (_hoops_PAHIR != null) {
				if (_hoops_ISCII) {
					if (!ANYBIT (*flags, _hoops_APPRA)) {
						*flags |= _hoops_SIRRA;
						++_hoops_SPRI->_hoops_PCRRA;
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_SIRRA;
					}
					else if (BIT (*flags, _hoops_HCRRA)) {
						*flags &= ~_hoops_HCRRA;
						--_hoops_SPRI->_hoops_ICRRA;
						*flags |= _hoops_SIRRA;
						++_hoops_SPRI->_hoops_PCRRA;
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
					}
					else if (BIT (*flags, _hoops_CCRRA)) {
						*flags &= ~_hoops_CCRRA;
						--_hoops_SPRI->_hoops_HIRRA;
						*flags |= _hoops_SIRRA;
						++_hoops_SPRI->_hoops_PCRRA;
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
					}
				}
			}

			if (ecolors != null) {
				if (_hoops_ISCII) {
					if (!ANYBIT (*flags, _hoops_PPPRA)) {
						*flags |= _hoops_RPHPR;
						++_hoops_SPRI->_hoops_CCHPR;
						_hoops_IPRI->_hoops_RSHPR &= ~_hoops_APHPR;
					}
					else if (BIT (*flags, _hoops_PPHPR)) {
						*flags &= ~_hoops_PPHPR;
						--_hoops_SPRI->_hoops_SCHPR;
						*flags |= _hoops_RPHPR;
						++_hoops_SPRI->_hoops_CCHPR;
						_hoops_IPRI->_hoops_RSHPR &= ~_hoops_AGSII;
					}
				}
			}

			if (fcolors != null) {
				if (_hoops_ISCII) {
					if (!ANYBIT (*flags, _hoops_HPPRA)) {
						*flags |= _hoops_HARHR;
						++_hoops_SPRI->_hoops_SIRHR;
						_hoops_IPRI->_hoops_ACRHR &= ~_hoops_IARHR;
					}
					else if (BIT (*flags, _hoops_AARHR)) {
						*flags &= ~_hoops_AARHR;
						--_hoops_SPRI->_hoops_RCRHR;
						*flags |= _hoops_HARHR;
						++_hoops_SPRI->_hoops_SIRHR;
						_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PGSII;
					}
				}
			}

			if (_hoops_ISCII)
				++flags;
		}

		++findices;
	} _hoops_RGGA (--count == 0);

	if (_hoops_IPRI->type != _hoops_CSIP) {
		HI_Reset_Strip_Flags (_hoops_IPRI);

		if (_hoops_PIRRA != 0) {
			if (_hoops_SPRI->_hoops_HIRRA == 0)
				HI_Less_Transparencies (null, _hoops_IPRI->owner, 1);
		}
		else {
			if (_hoops_SPRI->_hoops_HIRRA != 0)
				HI_More_Transparencies (context, _hoops_IPRI->owner, 1);
		}

		_hoops_IPRI->polyhedron_flags &= ~_hoops_SCRRA;
	}

	/* _hoops_RRRPR _hoops_IIGR _hoops_SPIGA _hoops_HHS _hoops_SHH _hoops_IRAP */
	if (_hoops_IPRI->owner != null) {
		if (!BIT (_hoops_IPRI->owner->_hoops_RCGC, _hoops_ASRRA))
			HI_Propagate_Maybes (context, _hoops_IPRI->owner, _hoops_ASRRA);
	}

	/* _hoops_RGR _hoops_HRGR _hoops_ICIC _hoops_PRGI _hoops_RPP _hoops_CPSA _hoops_IRS _hoops_RSRRA */
	HI_Invalidate_Display_Lists (context, _hoops_IPRI);

	/* _hoops_HPCAR _hoops_IGSIP _hoops_HRGR _hoops_SIGR */
	_hoops_SASIR (context, (Geometry *)_hoops_IPRI, _hoops_GPSIR|_hoops_RPSIR);

	_hoops_RGAIR (name);
	_hoops_IRRPR();
#endif
#endif
}

#ifndef _hoops_GCGHR

local RGB _hoops_HGSII(RGB const & rgb)
{
	RGB		_hoops_PAGR = rgb;
	bool	_hoops_IGSII = false;

	if (_hoops_PAGR.red < 0.0f) {
		_hoops_PAGR.red = 0.0f;
		_hoops_IGSII = true;
	}
	else if (_hoops_PAGR.red > 1.0f) {
		_hoops_PAGR.red = 1.0f;
		_hoops_IGSII = true;
	}

	if (_hoops_PAGR.green < 0.0f) {
		_hoops_PAGR.green = 0.0f;
		_hoops_IGSII = true;
	}
	else if (_hoops_PAGR.green > 1.0f) {
		_hoops_PAGR.green = 1.0f;
		_hoops_IGSII = true;
	}

	if (_hoops_PAGR.blue < 0.0f) {
		_hoops_PAGR.blue = 0.0f;
		_hoops_IGSII = true;
	}
	else if (_hoops_PAGR.blue > 1.0f) {
		_hoops_PAGR.blue = 1.0f;
		_hoops_IGSII = true;
	}

	if (_hoops_IGSII)
		HE_WARNING (HEC_MSET_VERTEX, HES_OUT_OF_RANGE_RGB, "RGB value of is out of range");

	return _hoops_PAGR;
}

local RGBA _hoops_CGSII(RGBA const & _hoops_PIHR)
{
	RGBA	_hoops_PAGR = _hoops_PIHR;
	bool	_hoops_IGSII = false;

	if (_hoops_PAGR.red < 0.0f) {
		_hoops_PAGR.red = 0.0f;
		_hoops_IGSII = true;
	}
	else if (_hoops_PAGR.red > 1.0f) {
		_hoops_PAGR.red = 1.0f;
		_hoops_IGSII = true;
	}

	if (_hoops_PAGR.green < 0.0f) {
		_hoops_PAGR.green = 0.0f;
		_hoops_IGSII = true;
	}
	else if (_hoops_PAGR.green > 1.0f) {
		_hoops_PAGR.green = 1.0f;
		_hoops_IGSII = true;
	}

	if (_hoops_PAGR.blue < 0.0f) {
		_hoops_PAGR.blue = 0.0f;
		_hoops_IGSII = true;
	}
	else if (_hoops_PAGR.blue > 1.0f) {
		_hoops_PAGR.blue = 1.0f;
		_hoops_IGSII = true;
	}

	if (_hoops_PAGR.alpha < 0.0f) {
		_hoops_PAGR.alpha = 0.0f;
		_hoops_IGSII = true;
	}
	else if (_hoops_PAGR.alpha > 1.0f) {
		_hoops_PAGR.alpha = 1.0f;
		_hoops_IGSII = true;
	}

	if (_hoops_IGSII)
		HE_WARNING (HEC_MSET_VERTEX, HES_OUT_OF_RANGE_RGB, "RGB value of is out of range");

	return _hoops_PAGR;
}

#endif



/* _hoops_PIP: _hoops_ICRP _hoops_IIGR _hoops_RGR _hoops_API _hoops_CSAP _hoops_IIHA _hoops_GPP _hoops_SGSII */
HC_INTERFACE void HC_CDECL HC_MSet_Face_Colors_By_Value (
	Key					key,
	char const *		geometry,
	int					offset,
	char const *		color_space,
	int					count,
	RGB const *			values)
{
	_hoops_PAPPR context("MSet_Face_Colors_By_Value");

#ifdef _hoops_GCGHR
	_hoops_IRPPR ("Geometry Colors");
#else
	CODE_GENERATION (
		int		count2 = count;
		if (count == 0) {
			HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Face_Colors_By_Value (LOOKUP (%D), ", key));
			HI_Dump_Code (Sprintf_SD (null, "%S, %d, ", geometry, offset));
			HI_Dump_Code (Sprintf_S (null, "%S, 0, 0);\n", color_space));
		}
		else {
			HI_Dump_Code (Sprintf_D (null, "{HC_RGB* values = (HC_RGB*) malloc(sizeof(HC_RGB)*%d);\n", count2));
			++HOOPS_WORLD->_hoops_ISPPR;
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (_hoops_CHCHR (null, "values[%d].x = %f;	 ", count2, values[count2].red));
				HI_Dump_Code (_hoops_CHCHR (null, "values[%d].y = %f;	 ", count2, values[count2].green));
				HI_Dump_Code (_hoops_CHCHR (null, "values[%d].z = %f;\n", count2, values[count2].blue));
			}
			HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Face_Colors_By_Value (LOOKUP (%D), ", key));
			HI_Dump_Code (Sprintf_SD (null, "%S, %d, ", geometry, offset));
			HI_Dump_Code (Sprintf_SD (null, "%S, %d, values);\n", color_space, count));
			HI_Dump_Code ("free (values);\n");
			--HOOPS_WORLD->_hoops_ISPPR;
			HI_Dump_Code ("}\n");
		}
	);

	if (count < 0) {
		HE_ERROR (HEC_MSET_FACE, HES_INVALID_COUNT, "Count is negative");
		return;
	}
	if (offset < 0) {
		HE_ERROR (HEC_MSET_FACE, HES_INVALID_OFFSET, "Offset is negative");
		return;
	}


	Polyhedron *		_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_PCGPP)) == null)
		return;

	Color_Object	_hoops_HSCII;
	_hoops_HCRPR			name;
	HI_Canonize_Chars (geometry, &name);
	char const *	_hoops_RPPA = name.text;
	if (!HI_Decipher_Color_Target (context, &_hoops_RPPA, _hoops_RPPA + name.length, true, &_hoops_HSCII, Color_FACE)) {
		; // _hoops_PSIIR?
	}
	else if (!BIT (_hoops_HSCII, Color_FACE)) {
		; // _hoops_PSIIR?
	}
	else if (ANYBIT (_hoops_HSCII, ~Color_FACE)) {
		HE_ERROR (HEC_MSET_FACE, HES_CANNOT_SET_ATTRIBUTE, "Only a face color may be set on a face");
	}
	else if (_hoops_IPRI->face_count < offset + count) {
		char	buf[MAX_ERRMSG];
		HE_ERROR2 (HEC_MSET_FACE, HES_INVALID_OFFSET,
				   Sprintf_D (null, "Shell or mesh only has %d faces -", _hoops_IPRI->face_count),
				   Sprintf_DD (buf, "can't change %d of them at offset %d", count, offset));
	}
	else {
		if (_hoops_IPRI->local_face_attributes.colors == null)
			HI_Initialize_Face_Attributes (_hoops_IPRI, LFA_EXPLICIT_COLOR_BY_VALUE);

		RGB *	colors = &_hoops_IPRI->local_face_attributes.colors[offset];

		if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR) &&
			!BIT(_hoops_IPRI->local_face_attributes._hoops_SGRHR, LFA_EXPLICIT_COLOR_BY_VALUE) &&
			(offset != 0 || count != _hoops_IPRI->face_count)) {
			ZALLOC_ARRAY(_hoops_IPRI->local_face_attributes.flags, _hoops_IPRI->face_count, _hoops_GIIPR);
			for (int i = 0; i < _hoops_IPRI->face_count; i++)
				_hoops_IPRI->local_face_attributes.flags[i] = _hoops_IPRI->local_face_attributes._hoops_SGRHR;
			_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
		}

		_hoops_GIIPR *	flags  = _hoops_IPRI->local_face_attributes._hoops_CHHPR(offset);

		bool	done = true;

		if ((color_space[0] == 'r' || color_space[0] == 'R') &&
			(color_space[1] == 'g' || color_space[1] == 'G') &&
			(color_space[2] == 'b' || color_space[2] == 'B')) {

			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
				*flags &= ~LFA_EXPLICIT_COLOR_BY_FINDEX;
				_hoops_IPRI->local_face_attributes._hoops_PSRRA = 0;
				*flags |= LFA_EXPLICIT_COLOR_BY_VALUE;
				_hoops_IPRI->local_face_attributes._hoops_HSRRA = _hoops_IPRI->face_count;
			}

			do {
				*colors++ = _hoops_HGSII (*values);

				/* (_hoops_AGCR _hoops_CSCII _hoops_CHR _hoops_SSAAA _hoops_IH _hoops_RH '_hoops_PSP _hoops_PGHC _hoops_RGSR' _hoops_AGIR) */

				if (!ANYBIT (*flags, _hoops_IACHR)) {
					if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
						*flags |= LFA_EXPLICIT_COLOR_BY_VALUE;
						++_hoops_IPRI->local_face_attributes._hoops_HSRRA;
					}
					_hoops_IPRI->_hoops_ACRHR &= ~LFA_EXPLICIT_COLOR_BY_VALUE;
				}
				else if (BIT (*flags, LFA_EXPLICIT_COLOR_BY_FINDEX)) {
					if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
						*flags &= ~LFA_EXPLICIT_COLOR_BY_FINDEX;
						--_hoops_IPRI->local_face_attributes._hoops_PSRRA;
						*flags |= LFA_EXPLICIT_COLOR_BY_VALUE;
						++_hoops_IPRI->local_face_attributes._hoops_HSRRA;
					}
					_hoops_IPRI->_hoops_ACRHR &= ~_hoops_IACHR;
				}

				if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR))
					++flags;
				++values;
			} _hoops_RGGA (--count == 0);
		}
		else {
			_hoops_RHAH	_hoops_APHCR;
			if (HI_Parse_Color_Map_By_Value (context, color_space, count, values, &_hoops_APHCR)) {
				done = false;
			}
			else {
				Named_Material *	_hoops_HAA = _hoops_APHCR._hoops_HAA;

				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
					*flags &= ~LFA_EXPLICIT_COLOR_BY_FINDEX;
					_hoops_IPRI->local_face_attributes._hoops_PSRRA = 0;
					*flags |= LFA_EXPLICIT_COLOR_BY_VALUE;
					_hoops_IPRI->local_face_attributes._hoops_HSRRA = _hoops_IPRI->face_count;
				}

				do {
					colors->red	  = _hoops_HAA->_hoops_CSHR.red;
					colors->green = _hoops_HAA->_hoops_CSHR.green;
					colors->blue  = _hoops_HAA->_hoops_CSHR.blue;
					++colors;

					/* (_hoops_AGCR _hoops_CSCII _hoops_CHR _hoops_SSAAA _hoops_IH _hoops_RH '_hoops_PSP _hoops_PGHC _hoops_RGSR' _hoops_AGIR) */

					if (!ANYBIT (*flags, _hoops_IACHR)) {
						if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
							*flags |= LFA_EXPLICIT_COLOR_BY_VALUE;
							++_hoops_IPRI->local_face_attributes._hoops_HSRRA;
						}
						_hoops_IPRI->_hoops_ACRHR &= ~LFA_EXPLICIT_COLOR_BY_VALUE;
					}
					else if (BIT (*flags, LFA_EXPLICIT_COLOR_BY_FINDEX)) {
						if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
							*flags &= ~LFA_EXPLICIT_COLOR_BY_FINDEX;
							--_hoops_IPRI->local_face_attributes._hoops_PSRRA;
							*flags |= LFA_EXPLICIT_COLOR_BY_VALUE;
							++_hoops_IPRI->local_face_attributes._hoops_HSRRA;
						}
						_hoops_IPRI->_hoops_ACRHR &= ~_hoops_IACHR;
					}
					*flags |= _hoops_IGAHR;

					if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR))
						++flags;
					++_hoops_HAA;
				} _hoops_RGGA (--count == 0);

				_hoops_HAA = _hoops_APHCR._hoops_HAA;
				HI_Free_Material_Names (_hoops_HAA, _hoops_APHCR.length);
				FREE_ARRAY (_hoops_HAA, _hoops_APHCR.length, Named_Material);
			}
		}

		if (done) {
			_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;

			/* _hoops_RRRPR _hoops_IIGR _hoops_SPIGA _hoops_HHS _hoops_SHH _hoops_IRAP */
			if (_hoops_IPRI->owner) {
				if (!BIT (_hoops_IPRI->owner->_hoops_RCGC, _hoops_ASRRA))
					HI_Propagate_Maybes (context, _hoops_IPRI->owner, _hoops_ASRRA);
			}

			HI_Invalidate_Display_Lists (context, _hoops_IPRI);

			/* _hoops_HPCAR _hoops_IGSIP _hoops_HRGR _hoops_SIGR */
			_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR|_hoops_RPSIR);
		}
	}

	_hoops_RGAIR (name);
	_hoops_IRRPR();
#endif
}

HC_INTERFACE void HC_CDECL HC_MSet_Vertex_Colors_By_Value4 (
	Key					key,
	char const *		geometry,
	int					offset,
	char const *		color_space,
	int					count,
	RGBA const *		values)
{
	HC_MSet_Vertex_Colors_By_Value(key,geometry,offset,color_space,count,(RGB const *)values);
}

HC_INTERFACE void HC_CDECL HC_MSet_Vertex_Colors_By_Value (
	Key					key,
	char const *		geometry,
	int					offset,
	char const *		color_space,
	int					count,
	RGB const *			values)
{
	//_hoops_RPP (_hoops_ISCGI(_hoops_GRSII, "_hoops_PIRAI")) {
	//	_hoops_RRSII(_hoops_SIC,_hoops_CPAP,_hoops_SHI,_hoops_GRSII,_hoops_RPR,(_hoops_RGPP _hoops_RCIC *)_hoops_HSH);
	//	_hoops_ASRC;
	//}

	_hoops_PAPPR context("MSet_Vertex_Colors_By_Value");

#ifdef _hoops_GCGHR
	_hoops_IRPPR ("Geometry Colors");
#else
	CODE_GENERATION (
		int		count2 = count;

		HI_Dump_Code (Sprintf_D (null, "{HC_RGB* values = (HC_RGB*) malloc(sizeof(HC_RGB)*%d);\n", count2));
		++HOOPS_WORLD->_hoops_ISPPR;
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "values[%d].red = %f;	 ", count2, values[count2].red));
			HI_Dump_Code (_hoops_CHCHR (null, "values[%d].green = %f;	 ", count2, values[count2].green));
			HI_Dump_Code (_hoops_CHCHR (null, "values[%d].blue = %f;\n", count2, values[count2].blue));
		}
		HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Vertex_Colors_By_Value (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_SD (null, "%S, %d, ", geometry, offset));
		HI_Dump_Code (Sprintf_SD (null, "%S, %d, values);\n", color_space, count));
		HI_Dump_Code ("free (values);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);


	if (count == 0)
		return;  /* _hoops_CPRSH */

	if (count < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		return;
	}

	if (offset < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_OFFSET, "Offset is negative");
		return;
	}


	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_ACGPP)) == null)
		return;

	RGB *						_hoops_PAHIR = null;
	RGB *						ecolors = null;
	RGB *						fcolors = null;

	Local_Vertex_Attributes *	_hoops_SPRI = null;
	_hoops_AGHIR *	_hoops_PGHIR = null;
	Local_Vertex_Flags *		flags = null;
	_hoops_CGHIR *			_hoops_SSCII = null;
	bool						_hoops_ISCII = false;
	int							_hoops_PIRRA = 0;



	Color_Object	_hoops_HSCII;
	_hoops_HCRPR			name;
	HI_Canonize_Chars (geometry, &name);
	char const *	_hoops_RPPA = name.text;
	if (!HI_Decipher_Color_Target (context, &_hoops_RPPA, _hoops_RPPA + name.length, true, &_hoops_HSCII,
			_hoops_IPRI->type == _hoops_CSIP ? (Color_FACE|Color_EDGE) : (Color_FACE|Color_EDGE|Color_VERTEX))) {
		_hoops_RGAIR (name);
		goto Release;
	}
	_hoops_RGAIR (name);

	if (_hoops_IPRI->type == _hoops_CSIP) {
		PolyCylinder *	_hoops_HSPIR = (PolyCylinder *)_hoops_IPRI;

		if (ANYBIT (_hoops_HSCII, ~(Color_EDGE|Color_FACE))) {
			HE_ERROR (HEC_MSET_VERTEX, HES_CANNOT_SET_ATTRIBUTE, "Only edge or face color may be set on a vertex");
			goto Release;
		}
		if ((color_space[0] == 'r' || color_space[0] == 'R') &&
			(color_space[1] == 'g' || color_space[1] == 'G') &&
			(color_space[2] == 'b' || color_space[2] == 'B') &&
			(color_space[3] == 'a' || color_space[3] == 'A')) {
			HE_ERROR (HEC_MSET_VERTEX, HES_CANNOT_SET_ATTRIBUTE, "Polycylinder does not support RGBA colors");
			goto Release;
		}

		if (_hoops_HSPIR->point_count < offset + count) {
			char			buf[MAX_ERRMSG];

			HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
					   Sprintf_D (null, "PolyCylinder only has %d vertices -", _hoops_HSPIR->point_count),
					   Sprintf_DD (buf, "can't change %d of them at offset %d", count, offset));
			goto Release;
		}

		_hoops_PGHIR = _hoops_HSPIR->_hoops_RGHIR;

		_hoops_PAHIR = null;

		if (BIT (_hoops_HSCII, Color_EDGE)) {
			if (_hoops_PGHIR == null)
				_hoops_PGHIR = HI_Initialize_PCA_Vertex_Attributes (_hoops_HSPIR, _hoops_SHRRA);
			else if (_hoops_PGHIR->ecolors == null) {
				if (BIT (_hoops_HSCII, Color_FRONT) && _hoops_PGHIR->fcolors != null)
					_hoops_PGHIR->ecolors = _hoops_PGHIR->fcolors;
				else
					_hoops_PGHIR = HI_Initialize_PCA_Vertex_Attributes (_hoops_HSPIR, _hoops_SHRRA);
			}
			else if (_hoops_PGHIR->ecolors == _hoops_PGHIR->fcolors &&
					 !BIT (_hoops_HSCII, Color_FRONT)) {
				/* _hoops_IHSA _hoops_HSSRR */
				_hoops_PGHIR->ecolors = (RGB *)
					HI_Clone_Anything (_hoops_PGHIR->ecolors,
									   _hoops_HSPIR->point_count * (long)sizeof(RGB));
			}
			ecolors = &_hoops_PGHIR->ecolors[offset];
		}
		else ecolors = null;

		if (BIT (_hoops_HSCII, Color_FRONT)) {
			if (_hoops_PGHIR == null)
				_hoops_PGHIR = HI_Initialize_PCA_Vertex_Attributes (_hoops_HSPIR, _hoops_GIRRA);
			else if (_hoops_PGHIR->fcolors == null) {
				if (BIT (_hoops_HSCII, Color_EDGE) && _hoops_PGHIR->ecolors != null)
					_hoops_PGHIR->fcolors = _hoops_PGHIR->ecolors;
				else
					_hoops_PGHIR = HI_Initialize_PCA_Vertex_Attributes (_hoops_HSPIR, _hoops_GIRRA);
			}
			else if (_hoops_PGHIR->fcolors == _hoops_PGHIR->ecolors &&
					 !BIT (_hoops_HSCII, Color_EDGE)) {
				/* _hoops_IHSA _hoops_HSSRR */
				_hoops_PGHIR->fcolors = (RGB *)
					HI_Clone_Anything (_hoops_PGHIR->fcolors,
									   _hoops_HSPIR->point_count * (long)sizeof(RGB));
			}
			fcolors = &_hoops_PGHIR->fcolors[offset];
		}
		else fcolors = null;

		_hoops_SSCII	 = &_hoops_PGHIR->flags[offset];
	}
	else {
		if ((color_space[0] == 'r' || color_space[0] == 'R') &&
			(color_space[1] == 'g' || color_space[1] == 'G') &&
			(color_space[2] == 'b' || color_space[2] == 'B') &&
			(color_space[3] == 'a' || color_space[3] == 'A')) {
			if (ANYBIT (_hoops_HSCII, ~(Color_MARKER|Color_VERTEX))) {
				HE_ERROR (HEC_MSET_VERTEX, HES_CANNOT_SET_ATTRIBUTE, "Only marker/vertex color may be set on a vertex using RGBA");
				goto Release;
			}
		}
		else {
			if (ANYBIT (_hoops_HSCII, ~(Color_MARKER|Color_VERTEX|Color_EDGE|Color_FACE))) {
				HE_ERROR (HEC_MSET_VERTEX, HES_CANNOT_SET_ATTRIBUTE, "Only marker/vertex, edge, or face color may be set on a vertex");
				goto Release;
			}
		}

		if (_hoops_IPRI->point_count < offset + count) {
			char			buf[MAX_ERRMSG];

			HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
					   Sprintf_D (null, "Shell or mesh only has %d vertices -", _hoops_IPRI->point_count),
					   Sprintf_DD (buf, "can't change %d of them at offset %d", count, offset));
			goto Release;
		}

		_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

		_hoops_PIRRA = _hoops_SPRI->_hoops_HIRRA;

		if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR) &&
			!BIT(_hoops_IPRI->local_vertex_attributes._hoops_SGRHR, _hoops_ARSII) &&
			(offset != 0 || count != _hoops_IPRI->point_count)) {
			ZALLOC_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
			for (int i = 0; i < _hoops_IPRI->point_count; i++)
				_hoops_IPRI->local_vertex_attributes.flags[i] = _hoops_IPRI->local_vertex_attributes._hoops_SGRHR;
			_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
		}


		if ((color_space[0] == 'r' || color_space[0] == 'R') &&
			(color_space[1] == 'g' || color_space[1] == 'G') &&
			(color_space[2] == 'b' || color_space[2] == 'B') &&
			(color_space[3] == 'a' || color_space[3] == 'A')) {
			if (_hoops_SPRI->_hoops_IAHIR == null)
				HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_CCRRA, 0);
		}
		else {
			if (BIT (_hoops_HSCII, Color_VERTEX)) {
				if (_hoops_SPRI->_hoops_PAHIR == null) {
					if (BIT (_hoops_HSCII, Color_EDGE) && _hoops_SPRI->ecolors != null)
						_hoops_SPRI->_hoops_PAHIR = _hoops_SPRI->ecolors;
					else if (BIT (_hoops_HSCII, Color_FRONT) && _hoops_SPRI->fcolors != null)
						_hoops_SPRI->_hoops_PAHIR = _hoops_SPRI->fcolors;
					else
						HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_HCRRA, 0);
				}
				else {
					/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GCSP _hoops_HIH _hoops_ASAI _hoops_RGSR _hoops_IRS _hoops_GCSP _hoops_ARIP, _hoops_IPS */
					if (_hoops_SPRI->_hoops_PAHIR == _hoops_SPRI->ecolors &&
						_hoops_SPRI->_hoops_PAHIR == _hoops_SPRI->fcolors &&
						ANYBIT (_hoops_HSCII, Color_EDGE|Color_FRONT) &&
						!ALLBITS (_hoops_HSCII, Color_EDGE|Color_FRONT)) {
						/* 3-_hoops_PPRRR _hoops_HSSRR, _hoops_SPR _hoops_IIGR _hoops_RH _hoops_HIASR _hoops_GHHS _hoops_RAAP _hoops_GGSR */
						if (!BIT (_hoops_HSCII, Color_EDGE)) {
							_hoops_SPRI->ecolors = (RGB *)
								HI_Clone_Anything (_hoops_SPRI->ecolors,
												   _hoops_IPRI->point_count *
												   (long)sizeof(RGB));
						}
						else /* _hoops_RPP (!_hoops_IRRC (_hoops_RGSII, _hoops_RCRRA)) */ {
							_hoops_SPRI->fcolors = (RGB *)
								HI_Clone_Anything (_hoops_SPRI->fcolors,
												   (_hoops_IPRI->point_count +
													_hoops_IPRI->_hoops_GCRHR) *
												   (long)sizeof(RGB));
						}
					}
					else if (_hoops_SPRI->_hoops_PAHIR == _hoops_SPRI->ecolors &&
								!BIT (_hoops_HSCII, Color_EDGE) ||
							 _hoops_SPRI->_hoops_PAHIR == _hoops_SPRI->fcolors &&
								!BIT (_hoops_HSCII, Color_FRONT)) {
						/* _hoops_IHSA _hoops_HSSRR */
						_hoops_SPRI->_hoops_PAHIR = (RGB *)
							HI_Clone_Anything (_hoops_SPRI->_hoops_PAHIR,
											   _hoops_IPRI->point_count *
											   (long)sizeof(RGB));
					}
				}
				_hoops_PAHIR = &_hoops_SPRI->_hoops_PAHIR[offset];
			}
			else _hoops_PAHIR = null;

			if (BIT (_hoops_HSCII, Color_EDGE)) {
				if (_hoops_SPRI->ecolors == null) {
					if (BIT (_hoops_HSCII, Color_VERTEX) && _hoops_SPRI->_hoops_PAHIR != null)
						_hoops_SPRI->ecolors = _hoops_SPRI->_hoops_PAHIR;
					else if (BIT (_hoops_HSCII, Color_FRONT) && _hoops_SPRI->fcolors != null)
						_hoops_SPRI->ecolors = _hoops_SPRI->fcolors;
					else
						HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_PPHPR, 0);
				}
				else {
					/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GCSP _hoops_HIH _hoops_ASAI _hoops_RGSR _hoops_IRS _hoops_GCSP _hoops_ARIP, _hoops_IPS */
					if (_hoops_SPRI->ecolors == _hoops_SPRI->_hoops_PAHIR &&
						_hoops_SPRI->ecolors == _hoops_SPRI->fcolors &&
						ANYBIT (_hoops_HSCII, Color_VERTEX|Color_FRONT) &&
						!ALLBITS (_hoops_HSCII, Color_VERTEX|Color_FRONT)) {
						/* 3-_hoops_PPRRR _hoops_HSSRR, _hoops_SPR _hoops_IIGR _hoops_RH _hoops_HIASR _hoops_GHHS _hoops_RAAP _hoops_GGSR */
						if (!BIT (_hoops_HSCII, Color_VERTEX)) {
							_hoops_SPRI->_hoops_PAHIR = (RGB *)
								HI_Clone_Anything (_hoops_SPRI->_hoops_PAHIR,
												   _hoops_IPRI->point_count *
												   (long)sizeof(RGB));
						}
						else /* _hoops_RPP (!_hoops_IRRC (_hoops_RGSII, _hoops_RCRRA)) */ {
							_hoops_SPRI->fcolors = (RGB *)
								HI_Clone_Anything (_hoops_SPRI->fcolors,
												   (_hoops_IPRI->point_count +
													_hoops_IPRI->_hoops_GCRHR) *
												   (long)sizeof(RGB));
						}
					}
					else if (_hoops_SPRI->ecolors == _hoops_SPRI->_hoops_PAHIR &&
								!BIT (_hoops_HSCII, Color_VERTEX) ||
							 _hoops_SPRI->ecolors == _hoops_SPRI->fcolors &&
								!BIT (_hoops_HSCII, Color_FRONT)) {
						/* _hoops_IHSA _hoops_HSSRR */
						_hoops_SPRI->ecolors = (RGB *)
							HI_Clone_Anything (_hoops_SPRI->ecolors,
											   _hoops_IPRI->point_count *
											   (long)sizeof(RGB));
					}
				}
				ecolors = &_hoops_SPRI->ecolors[offset];
			}
			else ecolors = null;

			if (BIT (_hoops_HSCII, Color_FRONT)) {
				if (_hoops_SPRI->fcolors == null) {
					if (_hoops_IPRI->_hoops_GCRHR != 0)
						HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_AARHR, 0);
					else if (BIT (_hoops_HSCII, Color_EDGE) && _hoops_SPRI->ecolors != null)
						_hoops_SPRI->fcolors = _hoops_SPRI->ecolors;
					else if (BIT (_hoops_HSCII, Color_VERTEX) && _hoops_SPRI->_hoops_PAHIR != null)
						_hoops_SPRI->fcolors = _hoops_SPRI->_hoops_PAHIR;
					else
						HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_AARHR, 0);
				}
				else {
					/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GCSP _hoops_HIH _hoops_ASAI _hoops_RGSR _hoops_IRS _hoops_GCSP _hoops_ARIP, _hoops_IPS */
					if (_hoops_SPRI->fcolors == _hoops_SPRI->_hoops_PAHIR &&
						_hoops_SPRI->fcolors == _hoops_SPRI->ecolors &&
						ANYBIT (_hoops_HSCII, Color_VERTEX|Color_EDGE) &&
						!ALLBITS (_hoops_HSCII, Color_VERTEX|Color_EDGE)) {
						/* 3-_hoops_PPRRR _hoops_HSSRR, _hoops_SPR _hoops_IIGR _hoops_RH _hoops_HIASR _hoops_GHHS _hoops_RAAP _hoops_GGSR */
						if (!BIT (_hoops_HSCII, Color_VERTEX)) {
							_hoops_SPRI->_hoops_PAHIR = (RGB *)
								HI_Clone_Anything (_hoops_SPRI->_hoops_PAHIR,
												   _hoops_IPRI->point_count *
												   (long)sizeof(RGB));
						}
						else /* _hoops_RPP (!_hoops_IRRC (_hoops_RGSII, _hoops_ACRRA)) */ {
							_hoops_SPRI->ecolors = (RGB *)
								HI_Clone_Anything (_hoops_SPRI->ecolors,
												   _hoops_IPRI->point_count *
												   (long)sizeof(RGB));
						}
					}
					else if (_hoops_SPRI->fcolors == _hoops_SPRI->_hoops_PAHIR && !BIT (_hoops_HSCII, Color_VERTEX) ||
							 _hoops_SPRI->fcolors == _hoops_SPRI->ecolors && !BIT (_hoops_HSCII, Color_EDGE)) {
						/* _hoops_IHSA _hoops_HSSRR */
						_hoops_SPRI->fcolors = (RGB *)
							HI_Clone_Anything (_hoops_SPRI->fcolors,
											   (_hoops_IPRI->point_count +
												_hoops_IPRI->_hoops_GCRHR) *
											   (long)sizeof(RGB));
					}
				}
				fcolors = &_hoops_SPRI->fcolors[offset];
			}
			else fcolors = null;
		}

		flags  = _hoops_SPRI->_hoops_CHHPR(offset);
	}


	if ((color_space[0] == 'r' || color_space[0] == 'R') &&
		(color_space[1] == 'g' || color_space[1] == 'G') &&
		(color_space[2] == 'b' || color_space[2] == 'B') &&
		(color_space[3] == 'a' || color_space[3] == 'A')) {

		if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
			if (!ANYBIT (*flags, _hoops_APPRA)) {
				*flags |= _hoops_CCRRA;
				_hoops_SPRI->_hoops_HIRRA += count;
				_hoops_IPRI->_hoops_AGRHR &= ~_hoops_CCRRA;
			}
			else if (BIT (*flags, _hoops_SIRRA)) {
				*flags &= ~_hoops_SIRRA;
				_hoops_SPRI->_hoops_PCRRA -= count;
				*flags |= _hoops_CCRRA;
				_hoops_SPRI->_hoops_HIRRA += count;
				_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
			}
			else if (BIT (*flags, _hoops_HCRRA)) {
				*flags &= ~_hoops_HCRRA;
				_hoops_SPRI->_hoops_ICRRA -= count;
				*flags |= _hoops_CCRRA;
				_hoops_SPRI->_hoops_HIRRA += count;
				_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
			}
		}
		else
			_hoops_ISCII = true;

		RGBA const *		_hoops_SGHI = (RGBA const *)values;
		RGBAS32 alter *		_hoops_HPHSA = &_hoops_SPRI->_hoops_IAHIR[offset];

		do {
			*_hoops_HPHSA = _hoops_CGSII (*_hoops_SGHI);

			/* (_hoops_AGCR _hoops_CSCII _hoops_CHR _hoops_SSAAA _hoops_IH _hoops_RH '_hoops_PSP _hoops_PGHC _hoops_RGSR' _hoops_AGIR) */

			if (_hoops_ISCII) {
				if (!ANYBIT (*flags, _hoops_APPRA)) {
					*flags |= _hoops_CCRRA;
					++_hoops_SPRI->_hoops_HIRRA;
					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_CCRRA;
				}
				else if (BIT (*flags, _hoops_SIRRA)) {
					*flags &= ~_hoops_SIRRA;
					--_hoops_SPRI->_hoops_PCRRA;
					*flags |= _hoops_CCRRA;
					++_hoops_SPRI->_hoops_HIRRA;
					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
				}
				else if (BIT (*flags, _hoops_HCRRA)) {
					*flags &= ~_hoops_HCRRA;
					--_hoops_SPRI->_hoops_ICRRA;
					*flags |= _hoops_CCRRA;
					++_hoops_SPRI->_hoops_HIRRA;
					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
				}

				++flags;
			}

			++_hoops_HPHSA;
			++_hoops_SGHI;
		} _hoops_RGGA (--count == 0);
	}
	else if ((color_space[0] == 'r' || color_space[0] == 'R') &&
			 (color_space[1] == 'g' || color_space[1] == 'G') &&
			 (color_space[2] == 'b' || color_space[2] == 'B')) {

		if (_hoops_IPRI->type != _hoops_CSIP) {
			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				if (_hoops_PAHIR != null) {
					if (!ANYBIT (*flags, _hoops_APPRA)) {
						*flags |= _hoops_HCRRA;
						_hoops_SPRI->_hoops_ICRRA += count;
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_HCRRA;
					}
					else if (BIT (*flags, _hoops_SIRRA)) {
						*flags &= ~_hoops_SIRRA;
						_hoops_SPRI->_hoops_PCRRA -= count;
						*flags |= _hoops_HCRRA;
						_hoops_SPRI->_hoops_ICRRA += count;
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
					}
					else if (BIT (*flags, _hoops_CCRRA)) {
						*flags &= ~_hoops_CCRRA;
						_hoops_SPRI->_hoops_HIRRA -= count;
						*flags |= _hoops_HCRRA;
						_hoops_SPRI->_hoops_ICRRA += count;
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
					}
				}

				if (ecolors != null) {
					if (!ANYBIT (*flags, _hoops_PPPRA)) {
						*flags |= _hoops_PPHPR;
						_hoops_SPRI->_hoops_SCHPR += count;
						_hoops_IPRI->_hoops_RSHPR &= ~_hoops_HPHPR;
					}
					else if (BIT (*flags, _hoops_RPHPR)) {
						*flags &= ~_hoops_RPHPR;
						_hoops_SPRI->_hoops_CCHPR -= count;
						*flags |= _hoops_PPHPR;
						_hoops_SPRI->_hoops_SCHPR += count;
						_hoops_IPRI->_hoops_RSHPR &= ~_hoops_AGSII;
					}
				}

				if (fcolors != null) {
					if (!ANYBIT (*flags, _hoops_HPPRA)) {
						*flags |= _hoops_AARHR;
						_hoops_SPRI->_hoops_RCRHR += count;
						_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PARHR;
					}
					else if (BIT (*flags, _hoops_HARHR)) {
						*flags &= ~_hoops_HARHR;
						_hoops_SPRI->_hoops_SIRHR -= count;
						*flags |= _hoops_AARHR;
						_hoops_SPRI->_hoops_RCRHR += count;
						_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PGSII;
						_hoops_IPRI->polyhedron_flags &= ~_hoops_SCRRA;
					}
				}
			}
			else
				_hoops_ISCII = true;
		}


		do {
			RGB rgb = _hoops_HGSII (*values++);

			if (_hoops_PAHIR != null)
				*_hoops_PAHIR++ = rgb;
			if (ecolors != null)
				*ecolors++ = rgb;
			if (fcolors != null)
				*fcolors++ = rgb;

			/* (_hoops_AGCR _hoops_CSCII _hoops_CHR _hoops_SSAAA _hoops_IH _hoops_RH '_hoops_PSP _hoops_PGHC _hoops_RGSR' _hoops_AGIR) */

			if (_hoops_IPRI->type == _hoops_CSIP) {
				if (ecolors != null) {
					if (!ANYBIT (*_hoops_SSCII, _hoops_GPPRA)) {
						*_hoops_SSCII |= _hoops_SHRRA;
						++_hoops_PGHIR->_hoops_SCHPR;
					}
					else if (BIT (*_hoops_SSCII, _hoops_IHRRA)) {
						*_hoops_SSCII &= ~_hoops_IHRRA;
						--_hoops_PGHIR->_hoops_CCHPR;
						*_hoops_SSCII |= _hoops_SHRRA;
						++_hoops_PGHIR->_hoops_SCHPR;
					}
				}

				if (fcolors != null) {
					if (!ANYBIT (*_hoops_SSCII, _hoops_RPPRA)) {
						*_hoops_SSCII |= _hoops_GIRRA;
						++_hoops_PGHIR->_hoops_RCRHR;
					}
					else if (BIT (*_hoops_SSCII, _hoops_CHRRA)) {
						*_hoops_SSCII &= ~_hoops_CHRRA;
						--_hoops_PGHIR->_hoops_SIRHR;
						*_hoops_SSCII |= _hoops_GIRRA;
						++_hoops_PGHIR->_hoops_RCRHR;
					}
				}

				++_hoops_SSCII;
			}
			else {
				if (_hoops_ISCII) {
					if (_hoops_PAHIR != null) {
						if (!ANYBIT (*flags, _hoops_APPRA)) {
							*flags |= _hoops_HCRRA;
							++_hoops_SPRI->_hoops_ICRRA;
							_hoops_IPRI->_hoops_AGRHR &= ~_hoops_HCRRA;
						}
						else if (BIT (*flags, _hoops_SIRRA)) {
							*flags &= ~_hoops_SIRRA;
							--_hoops_SPRI->_hoops_PCRRA;
							*flags |= _hoops_HCRRA;
							++_hoops_SPRI->_hoops_ICRRA;
							_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
						}
						else if (BIT (*flags, _hoops_CCRRA)) {
							*flags &= ~_hoops_CCRRA;
							--_hoops_SPRI->_hoops_HIRRA;
							*flags |= _hoops_HCRRA;
							++_hoops_SPRI->_hoops_ICRRA;
							_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
						}
					}

					if (ecolors != null) {
						if (!ANYBIT (*flags, _hoops_PPPRA)) {
							*flags |= _hoops_PPHPR;
							++_hoops_SPRI->_hoops_SCHPR;
							_hoops_IPRI->_hoops_RSHPR &= ~_hoops_HPHPR;
						}
						else if (BIT (*flags, _hoops_RPHPR)) {
							*flags &= ~_hoops_RPHPR;
							--_hoops_SPRI->_hoops_CCHPR;
							*flags |= _hoops_PPHPR;
							++_hoops_SPRI->_hoops_SCHPR;
							_hoops_IPRI->_hoops_RSHPR &= ~_hoops_AGSII;
						}
					}

					if (fcolors != null) {
						if (!ANYBIT (*flags, _hoops_HPPRA)) {
							*flags |= _hoops_AARHR;
							++_hoops_SPRI->_hoops_RCRHR;
							_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PARHR;
						}
						else if (BIT (*flags, _hoops_HARHR)) {
							*flags &= ~_hoops_HARHR;
							--_hoops_SPRI->_hoops_SIRHR;
							*flags |= _hoops_AARHR;
							++_hoops_SPRI->_hoops_RCRHR;
							_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PGSII;
							_hoops_IPRI->polyhedron_flags &= ~_hoops_SCRRA;
						}
					}

					++flags;
				}
			}
		} _hoops_RGGA (--count == 0);
	}
	else {
		_hoops_RHAH				_hoops_APHCR;
		Named_Material *		_hoops_HAA;

		if (!HI_Parse_Color_Map_By_Value (context, color_space, count, values, &_hoops_APHCR)) {
			goto Release;
		}

		_hoops_HAA = _hoops_APHCR._hoops_HAA;

		if (_hoops_IPRI->type != _hoops_CSIP) {
			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				if (_hoops_PAHIR != null) {
					if (!ANYBIT (*flags, _hoops_APPRA)) {
						*flags |= _hoops_HCRRA;
						_hoops_SPRI->_hoops_ICRRA += count;
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_HCRRA;
					}
					else if (BIT (*flags, _hoops_SIRRA)) {
						*flags &= ~_hoops_SIRRA;
						_hoops_SPRI->_hoops_PCRRA -= count;
						*flags |= _hoops_HCRRA;
						_hoops_SPRI->_hoops_ICRRA += count;
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
					}
					else if (BIT (*flags, _hoops_CCRRA)) {
						*flags &= ~_hoops_CCRRA;
						_hoops_SPRI->_hoops_HIRRA -= count;
						*flags |= _hoops_HCRRA;
						_hoops_SPRI->_hoops_ICRRA += count;
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
					}
				}

				if (ecolors != null) {
					if (!ANYBIT (*flags, _hoops_PPPRA)) {
						*flags |= _hoops_PPHPR;
						_hoops_SPRI->_hoops_SCHPR += count;
						_hoops_IPRI->_hoops_RSHPR &= ~_hoops_HPHPR;
					}
					else if (BIT (*flags, _hoops_RPHPR)) {
						*flags &= ~_hoops_RPHPR;
						_hoops_SPRI->_hoops_CCHPR -= count;
						*flags |= _hoops_PPHPR;
						_hoops_SPRI->_hoops_SCHPR += count;
						_hoops_IPRI->_hoops_RSHPR &= ~_hoops_AGSII;
					}
				}

				if (fcolors != null) {
					if (!ANYBIT (*flags, _hoops_HPPRA)) {
						*flags |= _hoops_AARHR;
						_hoops_SPRI->_hoops_RCRHR += count;
						_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PARHR;
					}
					else if (BIT (*flags, _hoops_HARHR)) {
						*flags &= ~_hoops_HARHR;
						_hoops_SPRI->_hoops_SIRHR -= count;
						*flags |= _hoops_AARHR;
						_hoops_SPRI->_hoops_RCRHR += count;
						_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PGSII;
						_hoops_IPRI->polyhedron_flags &= ~_hoops_SCRRA;
					}
				}
			}
			else
				_hoops_ISCII = true;
		}

		do {
			if (_hoops_PAHIR != null) {
				_hoops_PAHIR->red   = _hoops_HAA->_hoops_CSHR.red;
				_hoops_PAHIR->green = _hoops_HAA->_hoops_CSHR.green;
				_hoops_PAHIR->blue  = _hoops_HAA->_hoops_CSHR.blue;
				++_hoops_PAHIR;
			}

			if (ecolors != null) {
				ecolors->red   = _hoops_HAA->_hoops_CSHR.red;
				ecolors->green = _hoops_HAA->_hoops_CSHR.green;
				ecolors->blue  = _hoops_HAA->_hoops_CSHR.blue;
				++ecolors;
			}

			if (fcolors != null) {
				fcolors->red   = _hoops_HAA->_hoops_CSHR.red;
				fcolors->green = _hoops_HAA->_hoops_CSHR.green;
				fcolors->blue  = _hoops_HAA->_hoops_CSHR.blue;
				++fcolors;
			}

			/* (_hoops_AGCR _hoops_CSCII _hoops_CHR _hoops_SSAAA _hoops_IH _hoops_RH '_hoops_PSP _hoops_PGHC _hoops_RGSR' _hoops_AGIR) */

			if (_hoops_IPRI->type == _hoops_CSIP) {
				if (ecolors != null) {
					if (!ANYBIT (*_hoops_SSCII, _hoops_GPPRA)) {
						*_hoops_SSCII |= _hoops_SHRRA;
						++_hoops_PGHIR->_hoops_SCHPR;
					}
					else if (BIT (*_hoops_SSCII, _hoops_IHRRA)) {
						*_hoops_SSCII &= ~_hoops_IHRRA;
						--_hoops_PGHIR->_hoops_CCHPR;
						*_hoops_SSCII |= _hoops_SHRRA;
						++_hoops_PGHIR->_hoops_SCHPR;
					}
				}

				if (fcolors != null) {
					if (!ANYBIT (*_hoops_SSCII, _hoops_RPPRA)) {
						*_hoops_SSCII |= _hoops_GIRRA;
						++_hoops_PGHIR->_hoops_RCRHR;
					}
					else if (BIT (*_hoops_SSCII, _hoops_CHRRA)) {
						*_hoops_SSCII &= ~_hoops_CHRRA;
						--_hoops_PGHIR->_hoops_SIRHR;
						*_hoops_SSCII |= _hoops_GIRRA;
						++_hoops_PGHIR->_hoops_RCRHR;
					}
				}

				++_hoops_SSCII;
			}
			else {
				if (_hoops_ISCII) {
					if (_hoops_PAHIR != null) {
						if (!ANYBIT (*flags, _hoops_APPRA)) {
							*flags |= _hoops_HCRRA;
							++_hoops_SPRI->_hoops_ICRRA;
							_hoops_IPRI->_hoops_AGRHR &= ~_hoops_HCRRA;
						}
						else if (BIT (*flags, _hoops_SIRRA)) {
							*flags &= ~_hoops_SIRRA;
							--_hoops_SPRI->_hoops_PCRRA;
							*flags |= _hoops_HCRRA;
							++_hoops_SPRI->_hoops_ICRRA;
							_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
						}
						else if (BIT (*flags, _hoops_CCRRA)) {
							*flags &= ~_hoops_CCRRA;
							--_hoops_SPRI->_hoops_HIRRA;
							*flags |= _hoops_HCRRA;
							++_hoops_SPRI->_hoops_ICRRA;
							_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
						}
					}

					if (ecolors != null) {
						if (!ANYBIT (*flags, _hoops_PPPRA)) {
							*flags |= _hoops_PPHPR;
							++_hoops_SPRI->_hoops_SCHPR;
							_hoops_IPRI->_hoops_RSHPR &= ~_hoops_HPHPR;
						}
						else if (BIT (*flags, _hoops_RPHPR)) {
							*flags &= ~_hoops_RPHPR;
							--_hoops_SPRI->_hoops_CCHPR;
							*flags |= _hoops_PPHPR;
							++_hoops_SPRI->_hoops_SCHPR;
							_hoops_IPRI->_hoops_RSHPR &= ~_hoops_AGSII;
						}
					}

					if (fcolors != null) {
						if (!ANYBIT (*flags, _hoops_HPPRA)) {
							*flags |= _hoops_AARHR;
							++_hoops_SPRI->_hoops_RCRHR;
							_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PARHR;
						}
						else if (BIT (*flags, _hoops_HARHR)) {
							*flags &= ~_hoops_HARHR;
							--_hoops_SPRI->_hoops_SIRHR;
							*flags |= _hoops_AARHR;
							++_hoops_SPRI->_hoops_RCRHR;
							_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PGSII;
							_hoops_IPRI->polyhedron_flags &= ~_hoops_SCRRA;
						}
					}

					++flags;
				}
			}

			++_hoops_HAA;
		} _hoops_RGGA (--count == 0);

		_hoops_HAA = _hoops_APHCR._hoops_HAA;
		HI_Free_Material_Names (_hoops_HAA, _hoops_APHCR.length);
		FREE_ARRAY (_hoops_HAA, _hoops_APHCR.length, Named_Material);
	}

	if (_hoops_IPRI->type != _hoops_CSIP) {
		HI_Reset_Strip_Flags (_hoops_IPRI);

		if (_hoops_PIRRA != 0) {
			if (_hoops_SPRI->_hoops_HIRRA == 0)
				HI_Less_Transparencies (null, _hoops_IPRI->owner, 1);
		}
		else {
			if (_hoops_SPRI->_hoops_HIRRA != 0)
				HI_More_Transparencies (context, _hoops_IPRI->owner, 1);
		}
	}

	HI_Invalidate_Display_Lists (context, _hoops_IPRI);

	if (_hoops_IPRI->owner) {
		/* _hoops_AGCR _hoops_CHR _hoops_ICIC _hoops_PRGI _hoops_RPP _hoops_CPSA _hoops_IRS _hoops_RSRRA */
		if (!BIT (_hoops_IPRI->owner->_hoops_RCGC, _hoops_ASRRA))
			HI_Propagate_Maybes (context, _hoops_IPRI->owner, _hoops_ASRRA);
	}

	/* _hoops_HPCAR _hoops_IGSIP _hoops_HRGR _hoops_SIGR */
	_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR|_hoops_RPSIR);

Release:
	_hoops_IRRPR();

#endif
}


/**********************************************************************************************************/
local bool _hoops_PRSII (
	Polyhedron const *			_hoops_IPRI,
	int							count,
	int const *					indices)
{

	if (_hoops_IPRI->type == _hoops_CSIP) {
		PolyCylinder alter *		_hoops_HSPIR = (PolyCylinder *)_hoops_IPRI;

		for (int i=0; i<count; i++) {
			if (indices[i] < 0) {
				HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
						   Sprintf_DD (null, "Invalid offset value %d at location %d", indices[i], i));
				return false;
			}
			if (_hoops_HSPIR->point_count < indices[i]) {
				char			buf[MAX_ERRMSG];

				HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
						   Sprintf_DD (null, "Invalid offset value %d at location %d", indices[i], i),
						   Sprintf_D (buf, "Shell or mesh only has %d points", _hoops_HSPIR->point_count));
				return false;
			}
		}
	}
	else {
		for (int i=0; i<count; i++) {
			if (indices[i] < 0) {
				HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
						   Sprintf_DD (null, "Invalid offset value %d at location %d", indices[i], i));
				return false;
			}
			if (_hoops_IPRI->point_count < indices[i]) {
				char			buf[MAX_ERRMSG];

				HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
						   Sprintf_DD (null, "Invalid offset value %d at location %d", indices[i], i),
						   Sprintf_D (buf, "Shell or mesh only has %d points", _hoops_IPRI->point_count));
				return false;
			}
		}
	}

	return true;
}

#define _hoops_HRSII		0
#define _hoops_IRSII		1
#define _hoops_CRSII		2
#define _hoops_SRSII		3

#define _hoops_GASII	1 << 0
#define _hoops_RASII		1 << 1


local int _hoops_AASII (
	_hoops_AIGPR *		_hoops_RIGC,
	Key							key,
	char const *				geometry,
	int							offset,
	int							count,
	int const *					specific_vertices,
	char alter *				result_type,
	float alter *				index_colors,
	RGB alter *					rgb,
	RGBA alter *				_hoops_PIHR,
	int							_hoops_PASII = 0,
	int *						_hoops_HASII = null) {
	Polyhedron *				_hoops_IPRI;
	_hoops_HCRPR						name;
	char const *				_hoops_RPPA;
	Color_Object				_hoops_HSCII;
	int							_hoops_IASII = 0;
	bool						_hoops_CASII = false;

	_hoops_CSPPR();

	if (_hoops_HASII)
		*_hoops_HASII = 0;
	_hoops_IPRI = (Polyhedron *)_hoops_RCSSR (_hoops_RIGC, key);

	//_hoops_IIS'_hoops_GRI _hoops_HGCR _hoops_HHH _hoops_RIHH _hoops_AAIP _hoops_GGSR _hoops_IIGR _hoops_RH _hoops_PPRRR
	if (_hoops_IPRI == null ||
		(_hoops_IPRI->type != _hoops_SCIP && _hoops_IPRI->type != _hoops_GSIP &&
		 _hoops_IPRI->type != _hoops_CSIP) ||
		BIT (_hoops_IPRI->_hoops_RRHH, _hoops_HGAGR)) {
		if (_hoops_HASII)
			*_hoops_HASII = 1;
		HE_ERROR (HEC_COLOR, HES_INVALID_KEY, "Key does not refer to a valid Shell, or Mesh, or PolyCylinder");
		goto Release;
	}

	if (count < 0) {
		if (_hoops_HASII)
			*_hoops_HASII = 1;
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		goto Release;
	}

	if (specific_vertices) {
		if (!_hoops_PRSII (_hoops_IPRI, count, specific_vertices)) {
			if (_hoops_HASII)
				*_hoops_HASII = 1;
			goto Release;
		}
	}
	else if (offset < 0) {
		if (_hoops_HASII)
			*_hoops_HASII = 1;
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_OFFSET, "Offset is negative");
		goto Release;
	}

	HI_Canonize_Chars (geometry, &name);
	_hoops_RPPA = name.text;
	if (!HI_Decipher_Color_Target (_hoops_RIGC, &_hoops_RPPA, _hoops_RPPA + name.length, true, &_hoops_HSCII,
			_hoops_IPRI->type == _hoops_CSIP ? (Color_FACE|Color_EDGE) : (Color_FACE|Color_EDGE|Color_VERTEX))) {
		if (_hoops_HASII)
			*_hoops_HASII = 1;
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_TYPE, "Unrecognized type.");
		_hoops_RGAIR (name);
		goto Release;
	}
	_hoops_RGAIR (name);

	if ((BIT(_hoops_HSCII, Color_EDGE) && BIT(_hoops_HSCII, Color_FACE))
		|| (BIT(_hoops_HSCII, Color_EDGE) && ANYBIT(_hoops_HSCII, Color_VERTEX|Color_MARKER))
		|| (BIT(_hoops_HSCII, Color_FACE) && ANYBIT(_hoops_HSCII, Color_VERTEX|Color_MARKER))) {
		if (BIT(_hoops_PASII, _hoops_GASII))
			_hoops_CASII = true;
		else {
			if (_hoops_HASII)
				*_hoops_HASII = 1;
			HE_ERROR (HEC_COLOR, HES_INVALID_TYPE, "Only one type may be shown at a time");
			goto Release;
		}
	}

	if (count == 0)
		goto Release;

	//_hoops_HSPC _hoops_ASRC _hoops_HSH
	if (result_type)
		memset(result_type, 0, count*sizeof(char));
	if (index_colors) {
		for (int i=0; i<count; ++i)
			index_colors[i] = -1.0f;
	}
	if (rgb) {
		RGB _hoops_SASII(-1.0f, -1.0f, -1.0f);
		for (int i=0; i<count; ++i)
			rgb[i] = _hoops_SASII;
	}
	if (_hoops_PIHR) {
		RGBA _hoops_SASII(-1.0f, -1.0f, -1.0f, -1.0f);
		for (int i=0; i<count; ++i)
			_hoops_PIHR[i] = _hoops_SASII;
	}

	if (_hoops_IPRI->type == _hoops_CSIP) {
		PolyCylinder alter *		_hoops_HSPIR = (PolyCylinder *)_hoops_IPRI;
		_hoops_AGHIR *	_hoops_PGHIR;
		_hoops_CGHIR			_hoops_GPSII = 0, _hoops_RPSII = 0;
		_hoops_ACGHR const *	_hoops_APSII = null;
		RGB const *					_hoops_PPSII = null;

		//_hoops_HHH _hoops_GPRR-_hoops_SASI _hoops_SPHS
		if (ANYBIT (_hoops_HSCII, ~(Color_EDGE|Color_FACE))) {
			if (_hoops_HASII)
				*_hoops_HASII = 1;
			HE_ERROR (HEC_COLOR, HES_INVALID_TYPE, "Only edge or face color may be shown");
			goto Release;
		}

		if (!specific_vertices && _hoops_HSPIR->point_count < offset + count) {
			char			buf[MAX_ERRMSG];

			if (_hoops_HASII)
				*_hoops_HASII = 1;
			HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
					   Sprintf_D (null, "PolyCylinder only has %d vertices -", _hoops_HSPIR->point_count),
					   Sprintf_DD (buf, "can't show %d of them at offset %d", count, offset));
			goto Release;
		}

		_hoops_PGHIR = _hoops_HSPIR->_hoops_RGHIR;

		//_hoops_PIHGR _hoops_GGSR _hoops_RPP _hoops_SR _hoops_HS _hoops_PSP _hoops_PSHA _hoops_IIGR _hoops_RH _hoops_HGRC _hoops_GPRR
		if (_hoops_PGHIR == null || (BIT (_hoops_HSCII, Color_EDGE)
				&& ((_hoops_PGHIR->ecolors == null && _hoops_PGHIR->_hoops_HGHIR == null)
				|| (_hoops_PGHIR->_hoops_CCHPR == 0 && _hoops_PGHIR->_hoops_SCHPR == 0)))
			|| (BIT (_hoops_HSCII, Color_FACE)
				&& ((_hoops_PGHIR->fcolors == null && _hoops_PGHIR->_hoops_IGHIR == null)
				|| (_hoops_PGHIR->_hoops_SIRHR == 0 && _hoops_PGHIR->_hoops_RCRHR == 0))))
			goto Release;

		//_hoops_RPP _hoops_SR _hoops_ASSS _hoops_GPGR _hoops_CSSC, _hoops_SR _hoops_RRP _hoops_IS _hoops_AA _hoops_IRS _hoops_GGRGR-_hoops_SPIC _hoops_IS _hoops_GHSGR _hoops_HCR _hoops_PSHA _hoops_CHR _hoops_RH _hoops_PSHR
		if (_hoops_CASII) {
			bool _hoops_HPSII, _hoops_IPSII, _hoops_CPSII, _hoops_SPSII;

			if (specific_vertices) {
				for (int i=0; i<count; ++i) {
					_hoops_HPSII = BIT(_hoops_PGHIR->flags[specific_vertices[i]], _hoops_CHRRA);
					_hoops_IPSII = BIT(_hoops_PGHIR->flags[specific_vertices[i]], _hoops_GIRRA);
					_hoops_CPSII = BIT(_hoops_PGHIR->flags[specific_vertices[i]], _hoops_IHRRA);
					_hoops_SPSII = BIT(_hoops_PGHIR->flags[specific_vertices[i]], _hoops_SHRRA);

					if (_hoops_IPSII != _hoops_SPSII || _hoops_HPSII != _hoops_CPSII) {
						if (_hoops_HASII)
							*_hoops_HASII = 1;
						HE_ERROR (HEC_COLOR, HES_NO_LOCAL_SETTING,
								  "Not all requested vertex colors are explicitly set in the specified range");
						goto Release;
					}
					if ((_hoops_IPSII && _hoops_PGHIR->fcolors[specific_vertices[i]] != _hoops_PGHIR->ecolors[specific_vertices[i]])
						|| (_hoops_HPSII && _hoops_PGHIR->_hoops_IGHIR[specific_vertices[i]] != _hoops_PGHIR->_hoops_HGHIR[specific_vertices[i]])) {
						if (_hoops_HASII)
							*_hoops_HASII = 1;
						HE_ERROR (HEC_COLOR, HES_COLOR_COMPONENTS_MISMATCH,
								  "Can't show color(s), the values differ across the geometry types");
						goto Release;
					}
				}
			}
			else {
				for (int i=offset; i<offset+count; ++i) {
					_hoops_HPSII = BIT(_hoops_PGHIR->flags[i], _hoops_CHRRA);
					_hoops_IPSII = BIT(_hoops_PGHIR->flags[i], _hoops_GIRRA);
					_hoops_CPSII = BIT(_hoops_PGHIR->flags[i], _hoops_IHRRA);
					_hoops_SPSII = BIT(_hoops_PGHIR->flags[i], _hoops_SHRRA);

					if (_hoops_IPSII != _hoops_SPSII || _hoops_HPSII != _hoops_CPSII) {
						if (_hoops_HASII)
							*_hoops_HASII = 1;
						HE_ERROR (HEC_COLOR, HES_NO_LOCAL_SETTING,
							"Not all requested vertex colors are explicitly set in the specified range");
						goto Release;
					}
					if ((_hoops_IPSII && _hoops_PGHIR->fcolors[i] != _hoops_PGHIR->ecolors[i])
						|| (_hoops_HPSII && _hoops_PGHIR->_hoops_IGHIR[i] != _hoops_PGHIR->_hoops_HGHIR[i])) {
							if (_hoops_HASII)
								*_hoops_HASII = 1;
							HE_ERROR (HEC_COLOR, HES_COLOR_COMPONENTS_MISMATCH,
								"Can't show color(s), the values differ across the geometry types");
							goto Release;
					}
				}
			}
		}

		//_hoops_IAII _hoops_ARP _hoops_GH _hoops_SGI _hoops_PPR _hoops_CICRR
		if (BIT (_hoops_HSCII, Color_EDGE)) {
			_hoops_GPSII = _hoops_IHRRA;
			_hoops_RPSII = _hoops_SHRRA;
			_hoops_APSII = _hoops_PGHIR->_hoops_HGHIR;
			_hoops_PPSII = _hoops_PGHIR->ecolors;
		}
		else if (BIT (_hoops_HSCII, Color_FACE)) {
			_hoops_GPSII = _hoops_CHRRA;
			_hoops_RPSII = _hoops_GIRRA;
			_hoops_APSII = _hoops_PGHIR->_hoops_IGHIR;
			_hoops_PPSII = _hoops_PGHIR->fcolors;
		}

		//_hoops_AA _hoops_SCH
		if (specific_vertices) {
			for (int i=0; i<count; ++i) {
				if (BIT(_hoops_PGHIR->flags[specific_vertices[i]], _hoops_GPSII)) {
					if (result_type)
						result_type[i] = _hoops_IRSII;
					if (index_colors)
						index_colors[i] = _hoops_APSII[specific_vertices[i]];
					++_hoops_IASII;
				}
				else if (BIT(_hoops_PGHIR->flags[specific_vertices[i]], _hoops_RPSII)) {
					if (result_type)
						result_type[i] = _hoops_CRSII;
					if (rgb)
						rgb[i] = _hoops_PPSII[specific_vertices[i]];
					++_hoops_IASII;
				}
			}
		}
		else {
			for (int i=0; i<count; ++i) {
				if (BIT(_hoops_PGHIR->flags[offset+i], _hoops_GPSII)) {
					if (result_type)
						result_type[i] = _hoops_IRSII;
					if (index_colors)
						index_colors[i] = _hoops_APSII[offset+i];
					++_hoops_IASII;
				}
				else if (BIT(_hoops_PGHIR->flags[offset+i], _hoops_RPSII)) {
					if (result_type)
						result_type[i] = _hoops_CRSII;
					if (rgb)
						rgb[i] = _hoops_PPSII[offset+i];
					++_hoops_IASII;
				}
			}
		}
	}
	else {
		Local_Vertex_Attributes const * _hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;
		Local_Vertex_Flags			_hoops_GPSII = 0, _hoops_RPSII = 0, _hoops_GHSII = 0;
		Local_Vertex_Flags const *	flags;
		_hoops_ACGHR const *	_hoops_APSII = null;
		RGB const *					_hoops_PPSII = null;
		RGBAS32 const *				_hoops_RHSII = null;
		bool						_hoops_AHSII = false;

		//_hoops_HHH _hoops_GPRR-_hoops_SASI _hoops_SPHS
		if (ANYBIT (_hoops_HSCII, ~(Color_MARKER|Color_VERTEX|Color_EDGE|Color_FACE))) {
			if (_hoops_HASII)
				*_hoops_HASII = 1;
			HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_TYPE,
					  "Only marker/vertex, edge, or face color may be shown");
			goto Release;
		}

		if (!specific_vertices && _hoops_IPRI->point_count < offset + count) {
			char			buf[MAX_ERRMSG];

			if (_hoops_HASII)
				*_hoops_HASII = 1;
			HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
					   Sprintf_D (null, "Shell or mesh only has %d vertices -", _hoops_IPRI->point_count),
					   Sprintf_DD (buf, "can't show %d of them at offset %d", count, offset));
			goto Release;
		}

		//_hoops_PIHGR _hoops_GGSR _hoops_RPP _hoops_SR _hoops_HS _hoops_PSP _hoops_PSHA _hoops_IIGR _hoops_RH _hoops_HGRC _hoops_GPRR
		if ((BIT (_hoops_HSCII, Color_EDGE)
				&& ((_hoops_SPRI->ecolors == null && _hoops_SPRI->_hoops_HGHIR == null)
				|| (_hoops_SPRI->_hoops_CCHPR == 0 && _hoops_SPRI->_hoops_SCHPR == 0)))
			|| (BIT (_hoops_HSCII, Color_FACE)
				&& ((_hoops_SPRI->fcolors == null && _hoops_SPRI->_hoops_IGHIR == null)
				|| (_hoops_SPRI->_hoops_SIRHR == 0 && _hoops_SPRI->_hoops_RCRHR == 0)))
			|| (ANYBIT (_hoops_HSCII, Color_MARKER|Color_VERTEX)
				&& ((_hoops_SPRI->_hoops_PAHIR == null && _hoops_SPRI->_hoops_HAHIR == null && _hoops_SPRI->_hoops_IAHIR == null)
				|| (_hoops_SPRI->_hoops_PCRRA == 0 && _hoops_SPRI->_hoops_ICRRA == 0
					&& _hoops_SPRI->_hoops_HIRRA == 0))))
			goto Release;

		//_hoops_RPP _hoops_SR _hoops_ASSS _hoops_GPGR _hoops_CSSC, _hoops_SR _hoops_RRP _hoops_IS _hoops_AA _hoops_IRS _hoops_GGRGR-_hoops_SPIC _hoops_IS _hoops_GHSGR _hoops_HCR _hoops_PSHA _hoops_CHR _hoops_RH _hoops_PSHR
		if (_hoops_CASII) {
			bool _hoops_HPSII, _hoops_IPSII, _hoops_CPSII, _hoops_SPSII,
				_hoops_PHSII, _hoops_HHSII, _hoops_IHSII;
			bool _hoops_CHSII = BIT (_hoops_HSCII, Color_FACE);
			bool _hoops_SHSII = BIT (_hoops_HSCII, Color_EDGE);
			bool _hoops_GISII = ANYBIT (_hoops_HSCII, Color_MARKER|Color_VERTEX);

			if (specific_vertices) {
				for (int i=0; i<count; ++i) {
					flags = _hoops_IPRI->local_vertex_attributes._hoops_CHHPR(specific_vertices[i]);
					_hoops_HPSII = BIT(*flags, _hoops_HARHR);
					_hoops_IPSII = BIT(*flags, _hoops_AARHR);
					_hoops_CPSII = BIT(*flags, _hoops_RPHPR);
					_hoops_SPSII = BIT(*flags, _hoops_PPHPR);
					_hoops_PHSII = BIT(*flags, _hoops_SIRRA);
					_hoops_HHSII = BIT(*flags, _hoops_HCRRA);
					_hoops_IHSII = BIT(*flags, _hoops_CCRRA);

					if ((_hoops_CHSII && _hoops_SHSII
							&& (_hoops_IPSII != _hoops_SPSII || _hoops_HPSII != _hoops_CPSII))
						|| (_hoops_CHSII && _hoops_GISII
							&& (_hoops_IPSII != _hoops_HHSII || _hoops_HPSII != _hoops_PHSII))
						|| (_hoops_SHSII && _hoops_GISII
							&& (_hoops_SPSII != _hoops_HHSII || _hoops_CPSII != _hoops_PHSII))) {
						if (_hoops_HASII)
							*_hoops_HASII = 1;
						HE_ERROR (HEC_COLOR, HES_NO_LOCAL_SETTING,
								  "Not all requested vertex colors are explicitly set in the specified range");
						goto Release;
					}

					if ((_hoops_CHSII && _hoops_SHSII
							&& ((_hoops_IPSII && _hoops_SPRI->fcolors[specific_vertices[i]] != _hoops_SPRI->ecolors[specific_vertices[i]])
							|| (_hoops_HPSII && _hoops_SPRI->_hoops_IGHIR[specific_vertices[i]] != _hoops_SPRI->_hoops_HGHIR[specific_vertices[i]])))
						|| (_hoops_CHSII && _hoops_GISII
							&& ((_hoops_IPSII && _hoops_SPRI->fcolors[specific_vertices[i]] != _hoops_SPRI->_hoops_PAHIR[specific_vertices[i]])
							|| (_hoops_HPSII && _hoops_SPRI->_hoops_IGHIR[specific_vertices[i]] != _hoops_SPRI->_hoops_HAHIR[specific_vertices[i]])
							|| _hoops_IHSII))
						|| (_hoops_SHSII && _hoops_GISII
							&& ((_hoops_SPSII && _hoops_SPRI->ecolors[specific_vertices[i]] != _hoops_SPRI->_hoops_PAHIR[specific_vertices[i]])
							|| (_hoops_CPSII && _hoops_SPRI->_hoops_HGHIR[specific_vertices[i]] != _hoops_SPRI->_hoops_HAHIR[specific_vertices[i]])
							|| _hoops_IHSII))) {
						if (_hoops_HASII)
							*_hoops_HASII = 1;
						HE_ERROR (HEC_COLOR, HES_COLOR_COMPONENTS_MISMATCH,
								  "Can't show color(s), the values differ across the geometry types");
						goto Release;
					}
				}
			}
			else {
				flags = _hoops_IPRI->local_vertex_attributes._hoops_CHHPR(offset);
				for (int i=offset; i<offset+count; ++i) {
					_hoops_HPSII = BIT(*flags, _hoops_HARHR);
					_hoops_IPSII = BIT(*flags, _hoops_AARHR);
					_hoops_CPSII = BIT(*flags, _hoops_RPHPR);
					_hoops_SPSII = BIT(*flags, _hoops_PPHPR);
					_hoops_PHSII = BIT(*flags, _hoops_SIRRA);
					_hoops_HHSII = BIT(*flags, _hoops_HCRRA);
					_hoops_IHSII = BIT(*flags, _hoops_CCRRA);

					if ((_hoops_CHSII && _hoops_SHSII
							&& (_hoops_IPSII != _hoops_SPSII || _hoops_HPSII != _hoops_CPSII))
						|| (_hoops_CHSII && _hoops_GISII
							&& (_hoops_IPSII != _hoops_HHSII || _hoops_HPSII != _hoops_PHSII))
						|| (_hoops_SHSII && _hoops_GISII
							&& (_hoops_SPSII != _hoops_HHSII || _hoops_CPSII != _hoops_PHSII))) {
						if (_hoops_HASII)
							*_hoops_HASII = 1;
						HE_ERROR (HEC_COLOR, HES_NO_LOCAL_SETTING,
								  "Not all requested vertex colors are explicitly set in the specified range");
						goto Release;
					}

					if ((_hoops_CHSII && _hoops_SHSII
							&& ((_hoops_IPSII && _hoops_SPRI->fcolors[i] != _hoops_SPRI->ecolors[i])
							|| (_hoops_HPSII && _hoops_SPRI->_hoops_IGHIR[i] != _hoops_SPRI->_hoops_HGHIR[i])))
						|| (_hoops_CHSII && _hoops_GISII
							&& ((_hoops_IPSII && _hoops_SPRI->fcolors[i] != _hoops_SPRI->_hoops_PAHIR[i])
							|| (_hoops_HPSII && _hoops_SPRI->_hoops_IGHIR[i] != _hoops_SPRI->_hoops_HAHIR[i])
							|| _hoops_IHSII))
						|| (_hoops_SHSII && _hoops_GISII
							&& ((_hoops_SPSII && _hoops_SPRI->ecolors[i] != _hoops_SPRI->_hoops_PAHIR[i])
							|| (_hoops_CPSII && _hoops_SPRI->_hoops_HGHIR[i] != _hoops_SPRI->_hoops_HAHIR[i])
							|| _hoops_IHSII))) {
						if (_hoops_HASII)
							*_hoops_HASII = 1;
						HE_ERROR (HEC_COLOR, HES_COLOR_COMPONENTS_MISMATCH,
								  "Can't show color(s), the values differ across the geometry types");
						goto Release;
					}
					if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR))
						++flags;
				}
			}
		}

		//_hoops_IAII _hoops_ARP _hoops_GH _hoops_SGI _hoops_PPR _hoops_CICRR
		if (BIT (_hoops_HSCII, Color_EDGE)) {
			_hoops_GPSII = _hoops_RPHPR;
			_hoops_RPSII = _hoops_PPHPR;
			_hoops_GHSII = 0;
			_hoops_APSII = _hoops_SPRI->_hoops_HGHIR;
			_hoops_PPSII = _hoops_SPRI->ecolors;
			_hoops_RHSII = 0;
		}
		else if (BIT (_hoops_HSCII, Color_FACE)) {
			_hoops_GPSII = _hoops_HARHR;
			_hoops_RPSII = _hoops_AARHR;
			_hoops_GHSII = 0;
			_hoops_APSII = _hoops_SPRI->_hoops_IGHIR;
			_hoops_PPSII = _hoops_SPRI->fcolors;
			_hoops_RHSII = 0;
		}
		else if (ANYBIT (_hoops_HSCII, Color_MARKER|Color_VERTEX)) {
			_hoops_GPSII = _hoops_SIRRA;
			_hoops_RPSII = _hoops_HCRRA;
			_hoops_GHSII = _hoops_CCRRA;
			_hoops_APSII = _hoops_SPRI->_hoops_HAHIR;
			_hoops_PPSII = _hoops_SPRI->_hoops_PAHIR;
			_hoops_RHSII = _hoops_SPRI->_hoops_IAHIR;
			_hoops_AHSII = true;
		}

		//_hoops_AA _hoops_SCH
		if (specific_vertices) {
			for (int i=0; i<count; ++i) {
				flags = _hoops_IPRI->local_vertex_attributes._hoops_CHHPR(specific_vertices[i]);
				if (BIT(*flags, _hoops_GPSII)) {
					if (result_type)
						result_type[i] = _hoops_IRSII;
					if (index_colors)
						index_colors[i] = _hoops_APSII[specific_vertices[i]];
					++_hoops_IASII;
				}
				else if (BIT(*flags, _hoops_RPSII)) {
					if (result_type)
						result_type[i] = _hoops_CRSII;
					if (rgb)
						rgb[i] = _hoops_PPSII[specific_vertices[i]];
					++_hoops_IASII;
				}
				else if (_hoops_AHSII && BIT(*flags, _hoops_GHSII)) {
					if (result_type)
						result_type[i] = _hoops_SRSII;
					if (_hoops_PIHR)
						_hoops_PIHR[i] = _hoops_RHSII[specific_vertices[i]];
					else if (rgb && BIT(_hoops_PASII, _hoops_RASII))
						((RGBA *)rgb)[i] = _hoops_RHSII[specific_vertices[i]];
					++_hoops_IASII;
				}
			}
		}
		else {
			for (int i=0; i<count; ++i) {
				flags = _hoops_IPRI->local_vertex_attributes._hoops_CHHPR(offset+i);
				if (BIT(*flags, _hoops_GPSII)) {
					if (result_type)
						result_type[i] = _hoops_IRSII;
					if (index_colors)
						index_colors[i] = _hoops_APSII[offset+i];
					++_hoops_IASII;
				}
				else if (BIT(*flags, _hoops_RPSII)) {
					if (result_type)
						result_type[i] = _hoops_CRSII;
					if (rgb)
						rgb[i] = _hoops_PPSII[offset+i];
					++_hoops_IASII;
				}
				else if (_hoops_AHSII && BIT(*flags, _hoops_GHSII)) {
					if (result_type)
						result_type[i] = _hoops_SRSII;
					if (_hoops_PIHR)
						_hoops_PIHR[i] = _hoops_RHSII[offset+i];
					else if (rgb && BIT(_hoops_PASII, _hoops_RASII))
						((RGBA *)rgb)[i] = _hoops_RHSII[offset+i];
					++_hoops_IASII;
				}
			}
		}
	}

  Release:
	_hoops_IRRPR();
	return _hoops_IASII;
}

HC_INTERFACE int HC_CDECL HC_MShow_Vertex_Colors_With_Ex (
	Key							key,
	char const *				geometry,
	int							offset,
	int							count,
	char alter *				result_type,
	float alter *				index_colors,
	RGB alter *					rgb,
	RGBA alter *				_hoops_PIHR)
{
	_hoops_PAPPR context("MShow_Vertex_Colors_With_Existence");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return 0;
#else
#	ifdef _hoops_GCGHR
	_hoops_IRPPR ("Geometry COLORS");
	return 0;
#	else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Vertex_Colors_With_Existence () */\n");
	);

	int	_hoops_IASII = _hoops_AASII(context, key, geometry, offset, count, null, result_type, index_colors, rgb, _hoops_PIHR);

	return _hoops_IASII;
#	endif
#endif
}

/*******************************************************/



HC_INTERFACE void HC_CDECL HC_MShow_Vertex_Colors_By_Value (
	Key							key,
	char const *				geometry,
	int							offset,
	int							count,
	RGB alter *					rgb)
{
	_hoops_PAPPR context("MShow_Vertex_Colors_By_Value");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#	ifdef _hoops_GCGHR
	_hoops_IRPPR ("Geometry COLORS");
#	else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Vertex_Colors_By_Value () */\n");
	);

	int							_hoops_IASII = 0;
	char *						result_type;
	int							_hoops_HASII;

	ZALLOC_ARRAY_CACHED(result_type, count, char);
	_hoops_IASII = _hoops_AASII(context, key, geometry, offset, count, null, result_type,
		null, rgb, null, (_hoops_GASII|_hoops_RASII), &_hoops_HASII);

	//_hoops_RPP _hoops_SR'_hoops_RISP _hoops_AIAH _hoops_RHHS _hoops_PCCP _hoops_RIHH, _hoops_SAHR _hoops_CASI _hoops_GH _hoops_PPR _hoops_PHHR _hoops_RISII
	if (_hoops_HASII)
		goto Release;

	//_hoops_RARIR
	if (count != _hoops_IASII) {
		HE_ERROR (HEC_COLOR, HES_NO_LOCAL_SETTING,
				  "Not all requested vertex colors are explicitly set in the specified range");
		goto Release;
	}

	for (int i=0; i<count; ++i) {
		if (result_type[i] != _hoops_CRSII && result_type[i] != _hoops_SRSII) {
			HE_ERROR (HEC_COLOR, HES_NO_LOCAL_SETTING,
				  "Not all requested vertex colors are explicitly set in the specified range");
			goto Release;
		}
	}

Release:
	FREE_ARRAY(result_type, count, char);
#	endif
#endif
}

HC_INTERFACE void HC_CDECL HC_MShow_Vertex_Colors_By_FInd (
	Key								key,
	char const *					geometry,
	int								offset,
	int								count,
	float alter *					findices)
{
	_hoops_PAPPR context("MShow_Vertex_Colors_By_FIndex");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#	ifdef _hoops_GCGHR
	_hoops_IRPPR ("Geometry Colors");
#	else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Vertex_Colors_By_FIndex () */\n");
	);

	int		_hoops_IASII = 0;
	char *	result_type;
	int		_hoops_HASII;

	ZALLOC_ARRAY_CACHED(result_type, count, char);
	_hoops_IASII = _hoops_AASII(context, key, geometry, offset, count, null, result_type,
		findices, null, null, _hoops_GASII, &_hoops_HASII);

	//_hoops_RPP _hoops_SR'_hoops_RISP _hoops_AIAH _hoops_RHHS _hoops_PCCP _hoops_RIHH, _hoops_SAHR _hoops_CASI _hoops_GH _hoops_PPR _hoops_PHHR _hoops_RISII
	if (_hoops_HASII)
		goto Release;

	//_hoops_RARIR
	if (count != _hoops_IASII) {
		HE_ERROR (HEC_COLOR, HES_NO_LOCAL_SETTING,
				  "Not all requested vertex colors are explicitly set in the specified range");
		goto Release;
	}

	for (int i=0; i<count; ++i) {
		if (result_type[i] != _hoops_IRSII) {
			HE_ERROR (HEC_COLOR, HES_NO_LOCAL_SETTING,
				  "Not all requested vertex colors are explicitly set in the specified range");
			goto Release;
		}
	}

Release:
	FREE_ARRAY(result_type, count, char);
#	endif
#endif
}


local bool _hoops_AISII (
	Polyhedron const *		_hoops_IPRI,
	int						count,
	int const *				indices) {
	int						i;

	for (i=0; i<count; i++) {
		if (indices[i] < 0) {
			HE_ERROR (HEC_MSET_FACE, HES_INVALID_OFFSET,
					   Sprintf_DD (null, "Invalid offset value %d at location %d",
									indices[i], i));
			return false;
		}
		if (_hoops_IPRI->face_count < indices[i]) {
			char			buf[MAX_ERRMSG];

			HE_ERROR2 (HEC_MSET_FACE, HES_INVALID_OFFSET,
					   Sprintf_DD (null, "Invalid offset value %d at location %d", indices[i], i),
					   Sprintf_D (buf, "Shell or mesh only has %d faces", _hoops_IPRI->face_count));
			return false;
		}
	}

	return true;
}

#define _hoops_PISII		0
#define _hoops_HISII	1
#define _hoops_IISII		2


local int _hoops_CISII (
	_hoops_AIGPR *		_hoops_RIGC,
	Key							key,
	int							offset,
	int							count,
	int const *					_hoops_SISII,
	char alter *				result_type,
	float alter *				index_colors,
	RGB alter *					rgb,
	int *						_hoops_HASII = null)
{

	int							_hoops_IASII = 0;
	Local_Face_Attributes const * _hoops_CPRI;
	_hoops_GIIPR const *	flags;

	_hoops_CSPPR();

	if (_hoops_HASII)
		*_hoops_HASII = 0;
	Polyhedron *	_hoops_IPRI = (Polyhedron *)_hoops_RCSSR (_hoops_RIGC, key);

	//_hoops_IIS'_hoops_GRI _hoops_HGCR _hoops_HHH _hoops_RIHH _hoops_AAIP _hoops_GGSR _hoops_IIGR _hoops_RH _hoops_PPRRR
	if (_hoops_IPRI == null ||
		(_hoops_IPRI->type != _hoops_SCIP && _hoops_IPRI->type != _hoops_GSIP) ||
		BIT (_hoops_IPRI->_hoops_RRHH, _hoops_HGAGR)) {
		if (_hoops_HASII)
			*_hoops_HASII = 1;
		HE_ERROR (HEC_COLOR, HES_INVALID_KEY, "Key does not refer to a valid Shell or Mesh");
		goto Release;
	}

	if (count < 0) {
		if (_hoops_HASII)
			*_hoops_HASII = 1;
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		goto Release;
	}

	if (_hoops_SISII) {
		if (!_hoops_AISII (_hoops_IPRI, count, _hoops_SISII)) {
			if (_hoops_HASII)
				*_hoops_HASII = 1;
			goto Release;
		}
	}
	else {
		if (offset < 0) {
			if (_hoops_HASII)
				*_hoops_HASII = 1;
			HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_OFFSET, "Offset is negative");
			goto Release;
		}
		if (_hoops_IPRI->face_count < offset + count) {
			char			buf[MAX_ERRMSG];

			HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
					   Sprintf_D (null, "Shell or mesh only has %d faces -", _hoops_IPRI->face_count),
					   Sprintf_DD (buf, "can't show %d of them at offset %d", count, offset));
			goto Release;
		}
	}

	if (count == 0)
		goto Release;

	//_hoops_HSPC _hoops_ASRC _hoops_HSH
	if (result_type)
		memset(result_type, 0, count*sizeof(char));
	if (index_colors) {
		for (int i=0; i<count; ++i)
			index_colors[i] = -1.0f;
	}
	if (rgb) {
		RGB _hoops_SASII(-1.0f, -1.0f, -1.0f);
		for (int i=0; i<count; ++i)
			rgb[i] = _hoops_SASII;
	}

	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;

	//_hoops_PIHGR _hoops_GGSR _hoops_RPP _hoops_SR _hoops_HS _hoops_PSP _hoops_PSHA
	if (_hoops_CPRI->_hoops_PSRRA == 0 && _hoops_CPRI->_hoops_HSRRA == 0)
		goto Release;

	//_hoops_AA _hoops_SCH
	if (_hoops_SISII) {
		for (int i=0; i<count; ++i) {
			flags = _hoops_CPRI->_hoops_CHHPR(_hoops_SISII[i]);
			if (BIT(*flags, LFA_EXPLICIT_COLOR_BY_FINDEX)) {
				if (result_type)
					result_type[i] = _hoops_HISII;
				if (index_colors)
					index_colors[i] = _hoops_CPRI->findices[_hoops_SISII[i]];
				++_hoops_IASII;
			}
			else if (BIT(*flags, LFA_EXPLICIT_COLOR_BY_VALUE)) {
				if (result_type)
					result_type[i] = _hoops_IISII;
				if (rgb)
					rgb[i] = _hoops_CPRI->colors[_hoops_SISII[i]];
				++_hoops_IASII;
			}
		}
	}
	else {
		for (int i=0; i<count; ++i) {
			flags = _hoops_CPRI->_hoops_CHHPR(offset+i);
			if (BIT(*flags, LFA_EXPLICIT_COLOR_BY_FINDEX)) {
				if (result_type)
					result_type[i] = _hoops_HISII;
				if (index_colors)
					index_colors[i] = _hoops_CPRI->findices[offset+i];
				++_hoops_IASII;
			}
			else if (BIT(*flags, LFA_EXPLICIT_COLOR_BY_VALUE)) {
				if (result_type)
					result_type[i] = _hoops_IISII;
				if (rgb)
					rgb[i] = _hoops_CPRI->colors[offset+i];
				++_hoops_IASII;
			}
		}
	}

  Release:
	_hoops_IRRPR();
	return _hoops_IASII;
}


HC_INTERFACE void HC_CDECL HC_MShow_Face_Colors_By_Value (
	Key				key,
	int				offset,
	int				count,
	RGB alter *		rgb)
{
	_hoops_PAPPR context("MShow_Face_Colors_By_Value");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#	ifdef _hoops_GCGHR
	_hoops_IRPPR ("Geometry COLORS");
#	else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Face_Colors_By_Value () */\n");
	);

	int								_hoops_IASII = 0;
	char *							result_type;
	int								_hoops_HASII;

	ZALLOC_ARRAY_CACHED(result_type, count, char);
	_hoops_IASII = _hoops_CISII(context, key, offset, count, null, result_type,
		null, rgb, &_hoops_HASII);

	//_hoops_RPP _hoops_SR'_hoops_RISP _hoops_AIAH _hoops_RHHS _hoops_PCCP _hoops_RIHH, _hoops_SAHR _hoops_CASI _hoops_GH _hoops_PPR _hoops_PHHR _hoops_RISII
	if (_hoops_HASII)
		goto Release;

	//_hoops_RARIR
	if (count != _hoops_IASII) {
		HE_ERROR (HEC_COLOR, HES_NO_LOCAL_SETTING, "Not all requested face colors are explicitly set in the specified range");
		goto Release;
	}

	for (int i=0; i<count; ++i) {
		if (result_type[i] != _hoops_IISII) {
			HE_ERROR (HEC_COLOR, HES_NO_LOCAL_SETTING, "Not all requested face colors are explicitly set in the specified range");
			goto Release;
		}
	}

Release:
	FREE_ARRAY(result_type, count, char);
#	endif
#endif
}

HC_INTERFACE void HC_CDECL HC_MShow_Face_Colors_By_FIndex (
	Key								key,
	int								offset,
	int								count,
	float alter *					findices)
{
	_hoops_PAPPR context("MShow_Face_Colors_By_FIndex");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#	ifdef _hoops_GCGHR
	_hoops_IRPPR ("Geometry Colors");
#	else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Face_Colors_By_FIndex () */\n");
	);

	int			_hoops_IASII = 0;
	char *		result_type;
	int			_hoops_HASII;

	ZALLOC_ARRAY_CACHED(result_type, count, char);
	_hoops_IASII = _hoops_CISII(context, key, offset, count, null, result_type,
		findices, null, &_hoops_HASII);

	//_hoops_RPP _hoops_SR'_hoops_RISP _hoops_AIAH _hoops_RHHS _hoops_PCCP _hoops_RIHH, _hoops_SAHR _hoops_CASI _hoops_GH _hoops_PPR _hoops_PHHR _hoops_RISII
	if (_hoops_HASII)
		goto Release;

	//_hoops_RARIR
	if (count != _hoops_IASII) {
		HE_ERROR (HEC_COLOR, HES_NO_LOCAL_SETTING,
				  "Not all requested face colors are explicitly set in the specified range");
		goto Release;
	}

	for (int i=0; i<count; ++i) {
		if (result_type[i] != _hoops_HISII) {
			HE_ERROR (HEC_COLOR, HES_NO_LOCAL_SETTING,
				  "Not all requested face colors are explicitly set in the specified range");
			goto Release;
		}
	}

Release:
	FREE_ARRAY(result_type, count, char);
#	endif
#endif
}


HC_INTERFACE int HC_CDECL HC_MShow_Face_Colors_With_Ex (
	Key							key,
	char const *				geometry,
	int							offset,
	int							count,
	char alter *				result_type,
	float alter *				index_colors,
	RGB alter *					rgb)
{
	_hoops_PAPPR context("MShow_Face_Colors_With_Existence");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#	ifdef _hoops_GCGHR
	_hoops_IRPPR ("Geometry COLORS");
#	else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Face_Colors_With_Existence () */\n");
	);

	int	_hoops_IASII = 0;

	UNREFERENCED(geometry);
	_hoops_IASII = _hoops_CISII(context, key, offset, count, null, result_type,
		index_colors, rgb);
#	endif
#endif
	return _hoops_IASII;
}


HC_INTERFACE void HC_CDECL HC_MUnSet_Face_Colors (
	Key							key,
	int							offset,
	int							count)
{
	_hoops_PAPPR context("MUnSet_Face_Colors");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Face_Colors (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d);}\n", offset, count));
	);

	_hoops_GIIPR *		flags;
	Local_Face_Attributes *	_hoops_CPRI;
	bool					_hoops_AHPGR = false;
	bool					_hoops_GCSII = true;

	Polyhedron *		_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_PCGPP)) == null)
		return;

	if (count == -1) {
		count = _hoops_IPRI->face_count - offset;
		_hoops_GCSII = false;
	}

	if (count < 0) {
		HE_ERROR (HEC_MSET_FACE, HES_INVALID_COUNT, "Count is negative");
		goto Release;
	}
	if (offset < 0) {
		HE_ERROR (HEC_MSET_FACE, HES_INVALID_OFFSET, "Offset is negative");
		goto Release;
	}
	if (_hoops_IPRI->face_count < offset + count) {
		char			buf[MAX_ERRMSG];

		HE_ERROR2 (HEC_MSET_FACE, HES_INVALID_OFFSET,
				   Sprintf_D (null, "Shell or mesh only has %d faces -", _hoops_IPRI->face_count),
				   Sprintf_DD (buf, "can't change %d of them at offset %d", count, offset));
		goto Release;
	}

	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;

	if (_hoops_CPRI->_hoops_PSRRA == 0 && _hoops_CPRI->_hoops_HSRRA == 0) {
		/* _hoops_ISAP _hoops_ARP _hoops_RPP _hoops_PSP _hoops_SGI, _hoops_HIS _hoops_SAHR _hoops_PSIIR & _hoops_CASI _hoops_GH */
		HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");
		goto Release;
	}

	if (count < _hoops_IPRI->face_count) {
		/* _hoops_RCSII _hoops_IRS _hoops_GIIAR _hoops_IIGR _hoops_HCR _hoops_RSSI. */
		if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
			ZALLOC_ARRAY(_hoops_CPRI->flags, _hoops_IPRI->face_count, _hoops_GIIPR);
			for (int i = 0; i < _hoops_IPRI->face_count; i++)
				_hoops_CPRI->flags[i] = _hoops_CPRI->_hoops_SGRHR;
			_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
		}

		flags = _hoops_CPRI->_hoops_CHHPR(offset);

		do {
			if (BIT (*_hoops_CPRI->_hoops_CHHPR(offset), LFA_EXPLICIT_COLOR_BY_FINDEX)) {
				if (--_hoops_CPRI->_hoops_PSRRA == 0) {
					FREE_ARRAY (_hoops_CPRI->findices, _hoops_IPRI->face_count, _hoops_ACGHR);
					_hoops_CPRI->findices = null;
				}
				else
					_hoops_CPRI->findices[offset] = 0.0f;
			}
			else if (BIT (*_hoops_CPRI->_hoops_CHHPR(offset), LFA_EXPLICIT_COLOR_BY_VALUE)) {
				if (--_hoops_CPRI->_hoops_HSRRA == 0) {
					FREE_ARRAY (_hoops_CPRI->colors, _hoops_IPRI->face_count, RGB);
					_hoops_CPRI->colors = null;
				}
				else
					_hoops_CPRI->colors[offset] = _hoops_GPSR::_hoops_RPSR;
			}
			else
				_hoops_AHPGR = true;

			*_hoops_CPRI->_hoops_CHHPR(offset) &= ~(LFA_EXPLICIT_COLOR_BY_FINDEX|LFA_EXPLICIT_COLOR_BY_VALUE);
			*_hoops_CPRI->_hoops_CHHPR(offset) |= _hoops_IGAHR;

			++offset;
		} while (--count > 0);
	}
	else if (count == _hoops_IPRI->face_count) {
		if (_hoops_CPRI->lff_uniform(_hoops_IPRI->face_count, (_hoops_ACSII & ~_hoops_IACHR)) ||
			(BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR) && _hoops_CPRI->lff_uniform(_hoops_IPRI->face_count))) {
			if (_hoops_CPRI->_hoops_PSRRA != 0) {
				_hoops_CPRI->_hoops_PSRRA = 0;
				FREE_ARRAY (_hoops_CPRI->findices, _hoops_IPRI->face_count, _hoops_ACGHR);
				_hoops_CPRI->findices = null;
			}
			if (_hoops_CPRI->_hoops_HSRRA != 0) {
				_hoops_CPRI->_hoops_HSRRA = 0;
				FREE_ARRAY (_hoops_CPRI->colors, _hoops_IPRI->face_count, RGB);
				_hoops_CPRI->colors = null;
			}
			if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR) &&
				_hoops_CPRI->lff_uniform(_hoops_IPRI->face_count)) {
				_hoops_CPRI->_hoops_SGRHR = _hoops_CPRI->flags[0];
				FREE_ARRAY(_hoops_IPRI->local_face_attributes.flags, _hoops_IPRI->face_count, _hoops_GIIPR);
				_hoops_IPRI->polyhedron_flags &= ~_hoops_APRHR;
				_hoops_CPRI->flags = 0;
			}
			*_hoops_CPRI->_hoops_CHHPR(offset) &= ~(LFA_EXPLICIT_COLOR_BY_FINDEX|LFA_EXPLICIT_COLOR_BY_VALUE);
			*_hoops_CPRI->_hoops_CHHPR(offset) |= _hoops_IGAHR;
		}
		else {
			flags = _hoops_CPRI->_hoops_CHHPR(offset);

			do {
				if (BIT (*_hoops_CPRI->_hoops_CHHPR(offset), LFA_EXPLICIT_COLOR_BY_FINDEX)) {
					if (--_hoops_CPRI->_hoops_PSRRA == 0) {
						FREE_ARRAY (_hoops_CPRI->findices, _hoops_IPRI->face_count, _hoops_ACGHR);
						_hoops_CPRI->findices = null;
					}
					else
						_hoops_CPRI->findices[offset] = 0.0f;
				}
				else if (BIT (*_hoops_CPRI->_hoops_CHHPR(offset), LFA_EXPLICIT_COLOR_BY_VALUE)) {
					if (--_hoops_CPRI->_hoops_HSRRA == 0) {
						FREE_ARRAY (_hoops_CPRI->colors, _hoops_IPRI->face_count, RGB);
						_hoops_CPRI->colors = null;
					}
					else
						_hoops_CPRI->colors[offset] = _hoops_GPSR::_hoops_RPSR;
				}
				else
					_hoops_AHPGR = true;

				*_hoops_CPRI->_hoops_CHHPR(offset) &= ~(LFA_EXPLICIT_COLOR_BY_FINDEX|LFA_EXPLICIT_COLOR_BY_VALUE);
				*_hoops_CPRI->_hoops_CHHPR(offset) |= _hoops_IGAHR;

				++offset;
			} while (--count > 0);
		}

		/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_ISSC _hoops_IS _hoops_IRS _hoops_PIAP _hoops_CAS _hoops_RH _hoops_SGI _hoops_CHR _hoops_GHRHR, _hoops_SR _hoops_GHCA _hoops_RRP _hoops_IS _hoops_CIH _hoops_RH _hoops_SGI _hoops_CRPR */
		if (/*!_hoops_IRRC (_hoops_CPHAR->_hoops_PHRHR, _hoops_PCSII) &&*/
			BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR) &&
			_hoops_CPRI->lff_uniform(_hoops_IPRI->face_count)) {
			_hoops_CPRI->_hoops_SGRHR = _hoops_CPRI->flags[0];
			FREE_ARRAY(_hoops_IPRI->local_face_attributes.flags, _hoops_IPRI->face_count, _hoops_GIIPR);
			_hoops_IPRI->polyhedron_flags &= ~_hoops_APRHR;
			_hoops_CPRI->flags = 0;
		}
	}

	if (_hoops_AHPGR && _hoops_GCSII)
		HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");

	if (_hoops_IPRI->tristrips != null) {
		HI_Invalidate_Display_Lists (context, _hoops_IPRI);
		HI_Reset_Strip_Flags (_hoops_IPRI);
		_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;
		_hoops_SASIR (context, _hoops_IPRI, _hoops_IHSSR | _hoops_SIGPR);
	}

  Release:
	_hoops_IRRPR();
#endif
}

local void _hoops_HCSII (
	_hoops_AIGPR *			_hoops_RIGC,
	Key								key,
	char const *					type,
	int								offset,
	int								count)
{

	_hoops_HCRPR	name;
	HI_Canonize_Chars (type, &name);
	char const *	_hoops_RPPA = name.text;
	Color_Object	_hoops_HSCII;
	if (!HI_Decipher_Color_Target (_hoops_RIGC, &_hoops_RPPA, _hoops_RPPA + name.length, true, &_hoops_HSCII, (Color_FACE|Color_EDGE|Color_VERTEX))) {
		_hoops_RGAIR (name);
		return;
	}
	_hoops_RGAIR (name);

	if (ANYBIT (_hoops_HSCII, ~(Color_MARKER|Color_VERTEX|Color_EDGE|Color_FACE))) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_TYPE, "Only marker/vertex, edge, or face color may be shown");
		return;
	}

	Polyhedron *		_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(_hoops_RIGC, key, _hoops_ACGPP)) == null)
		return;


	bool	_hoops_AHPGR = false;
	bool	_hoops_GCSII = true;


	if (count == -1) {
		count = _hoops_IPRI->point_count - offset;
		_hoops_GCSII = false;
	}

	if (count < 0) {
		HE_ERROR (HEC_MSET_FACE, HES_INVALID_COUNT, "Count is negative");
		goto Release;
	}
	if (offset < 0) {
		HE_ERROR (HEC_MSET_FACE, HES_INVALID_OFFSET, "Offset is negative");
		goto Release;
	}

	if (_hoops_IPRI->type == _hoops_CSIP) {
		PolyCylinder alter *		_hoops_HSPIR = (PolyCylinder *)_hoops_IPRI;
		_hoops_AGHIR *	_hoops_PGHIR;
		_hoops_CGHIR *			flags;

		if (_hoops_HSPIR->point_count < offset + count) {
			char			buf[MAX_ERRMSG];

			HE_ERROR2 (HEC_MUNSET, HES_INVALID_OFFSET,
				Sprintf_D (null, "PolyCylinder only has %d points -", _hoops_HSPIR->point_count),
				Sprintf_DD (buf, "can't change %d of them at offset %d", count, offset));
			goto Release;
		}

		_hoops_PGHIR = _hoops_HSPIR->_hoops_RGHIR;

		if (_hoops_PGHIR->flags == null) {
			/* _hoops_ISAP _hoops_ARP _hoops_RPP _hoops_PSP _hoops_SGI, _hoops_HIS _hoops_SAHR _hoops_PSIIR & _hoops_CASI _hoops_GH */
			HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");
			goto Release;
		}


		float const *		_hoops_ICSII = null;
		float const *		_hoops_CCSII = null;
		_hoops_CGHIR	_hoops_SCSII = 0;

		if (BIT (_hoops_HSCII, Color_EDGE)) {
			_hoops_ICSII = _hoops_PGHIR->_hoops_HGHIR;
			_hoops_SCSII |= _hoops_GPPRA;
		}
		if (BIT (_hoops_HSCII, Color_FACE)) {
			_hoops_CCSII = _hoops_PGHIR->_hoops_IGHIR;
			_hoops_SCSII |= _hoops_RPPRA;
		}

		if (_hoops_ICSII == null && _hoops_CCSII == null)
			goto Release;

		flags = &_hoops_PGHIR->flags[offset];

		do {
			if (ANYBIT (*flags, _hoops_SCSII)) {
				if (BIT (*flags, _hoops_SHRRA & _hoops_SCSII)) {
					if (--_hoops_PGHIR->_hoops_SCHPR == 0) {
						if (_hoops_PGHIR->ecolors != _hoops_PGHIR->fcolors)
							FREE_ARRAY (_hoops_PGHIR->ecolors, _hoops_HSPIR->point_count, RGB);
						_hoops_PGHIR->ecolors = null;
					}
					else
						_hoops_PGHIR->ecolors[offset] = _hoops_GPSR::_hoops_RPSR;
				}
				else if (BIT (*flags, _hoops_IHRRA & _hoops_SCSII)) {
					if (--_hoops_PGHIR->_hoops_CCHPR == 0) {
						if (_hoops_PGHIR->_hoops_HGHIR != _hoops_PGHIR->_hoops_IGHIR)
							FREE_ARRAY (_hoops_PGHIR->_hoops_HGHIR, _hoops_HSPIR->point_count, _hoops_ACGHR);
						_hoops_PGHIR->_hoops_HGHIR = null;
					}
					else
						_hoops_PGHIR->_hoops_HGHIR[offset] = 0.0f;
				}

				if (BIT (*flags, _hoops_GIRRA & _hoops_SCSII)) {
					if (--_hoops_PGHIR->_hoops_RCRHR == 0) {
						if (_hoops_PGHIR->fcolors != _hoops_PGHIR->ecolors)
							FREE_ARRAY (_hoops_PGHIR->fcolors, _hoops_HSPIR->point_count, RGB);
						_hoops_PGHIR->fcolors = null;
					}
					else
						_hoops_PGHIR->fcolors[offset] = _hoops_GPSR::_hoops_RPSR;
				}
				else if (BIT (*flags, _hoops_CHRRA & _hoops_SCSII)) {
					if (--_hoops_PGHIR->_hoops_SIRHR == 0) {
						if (_hoops_PGHIR->_hoops_IGHIR != _hoops_PGHIR->_hoops_HGHIR)
							FREE_ARRAY (_hoops_PGHIR->_hoops_IGHIR, _hoops_HSPIR->point_count, _hoops_ACGHR);
						_hoops_PGHIR->_hoops_IGHIR = null;
					}
					else
						_hoops_PGHIR->_hoops_IGHIR[offset] = 0.0f;
				}

				*flags &= ~_hoops_SCSII;
			}
			else
				_hoops_AHPGR = true;

			++flags;
		} _hoops_RGGA (--count == 0);

		if (_hoops_PGHIR->_hoops_RCRHR == 0 &&
			_hoops_PGHIR->_hoops_SIRHR == 0 &&
			_hoops_PGHIR->_hoops_SCHPR == 0 &&
			_hoops_PGHIR->_hoops_CCHPR == 0) {
				/* _hoops_HCR _hoops_PPRGA! */
				FREE_ARRAY (_hoops_PGHIR->flags, _hoops_HSPIR->point_count, _hoops_CGHIR);
				FREE (_hoops_PGHIR, _hoops_AGHIR);
				_hoops_HSPIR->_hoops_RGHIR = null;
		}
	}
	else {
		if (_hoops_IPRI->point_count < offset + count) {
			char			buf[MAX_ERRMSG];
			HE_ERROR2 (HEC_MSET_FACE, HES_INVALID_OFFSET,
				Sprintf_D (null, "Shell or mesh only has %d points -", _hoops_IPRI->point_count),
				Sprintf_DD (buf, "can't change %d of them at offset %d", count, offset));
			goto Release;
		}

		Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

		if ((_hoops_SPRI->flags == null && BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) ||
			(_hoops_SPRI->_hoops_SGRHR == 0 && !BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR))) {
				/* _hoops_ISAP _hoops_ARP _hoops_RPP _hoops_PSP _hoops_SGI, _hoops_HIS _hoops_SAHR _hoops_PSIIR & _hoops_CASI _hoops_GH */
				HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");
				goto Release;
		}

		float const *		_hoops_HAHIR = null;
		float const *		_hoops_HGHIR = null;
		float const *		_hoops_IGHIR = null;
		Local_Vertex_Flags	needed_flags = 0;

		if (ANYBIT (_hoops_HSCII, Color_MARKER|Color_VERTEX)) {
			_hoops_HAHIR = _hoops_IPRI->local_vertex_attributes._hoops_HAHIR;
			needed_flags |= _hoops_APPRA;
		}
		if (BIT (_hoops_HSCII, Color_EDGE)) {
			_hoops_HGHIR = _hoops_IPRI->local_vertex_attributes._hoops_HGHIR;
			needed_flags |= _hoops_PPPRA;
		}
		if (BIT (_hoops_HSCII, Color_FACE)) {
			_hoops_IGHIR = _hoops_IPRI->local_vertex_attributes._hoops_IGHIR;
			needed_flags |= _hoops_HPPRA;
		}

		if (_hoops_HAHIR == null && _hoops_HGHIR == null && _hoops_IGHIR == null)
			goto Release;

		Local_Vertex_Flags *	flags = _hoops_SPRI->_hoops_CHHPR(offset);

		if (count < _hoops_IPRI->point_count) {
			/* _hoops_RCSII _hoops_IRS _hoops_GIIAR _hoops_IIGR _hoops_HCR _hoops_RSSI. */
			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
				for (int i = 0; i < _hoops_IPRI->point_count; i++)
					_hoops_SPRI->flags[i] = _hoops_SPRI->_hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
			}

			flags = _hoops_SPRI->_hoops_CHHPR(offset);

			do {
				if (ANYBIT (*flags, needed_flags)) {
					if (BIT (*flags, _hoops_HCRRA & needed_flags)) {
						if (--_hoops_SPRI->_hoops_ICRRA == 0) {
							if (_hoops_SPRI->_hoops_PAHIR != _hoops_SPRI->ecolors && _hoops_SPRI->_hoops_PAHIR != _hoops_SPRI->fcolors)
								FREE_ARRAY (_hoops_SPRI->_hoops_PAHIR, _hoops_IPRI->point_count, RGB);
							_hoops_SPRI->_hoops_PAHIR = null;
						}
						else
							_hoops_SPRI->_hoops_PAHIR[offset] = _hoops_GPSR::_hoops_RPSR;

						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_HCRRA;
					}
					else if (BIT (*flags, _hoops_SIRRA & needed_flags)) {
						if (--_hoops_SPRI->_hoops_PCRRA == 0) {
							if (_hoops_SPRI->_hoops_HAHIR != _hoops_SPRI->_hoops_HGHIR && _hoops_SPRI->_hoops_HAHIR != _hoops_SPRI->_hoops_IGHIR)
								FREE_ARRAY (_hoops_SPRI->_hoops_HAHIR, _hoops_IPRI->point_count, _hoops_ACGHR);
							_hoops_SPRI->_hoops_HAHIR = null;
						}
						else
							_hoops_SPRI->_hoops_HAHIR[offset] = 0.0f;

						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_SIRRA;
					}

					if (BIT (*flags, _hoops_PPHPR & needed_flags)) {
						if (--_hoops_SPRI->_hoops_SCHPR == 0) {
							if (_hoops_SPRI->ecolors != _hoops_SPRI->_hoops_PAHIR && _hoops_SPRI->ecolors != _hoops_SPRI->fcolors)
								FREE_ARRAY (_hoops_SPRI->ecolors, _hoops_IPRI->point_count, RGB);
							_hoops_SPRI->ecolors = null;
						}
						else
							_hoops_SPRI->ecolors[offset] = _hoops_GPSR::_hoops_RPSR;

						_hoops_IPRI->_hoops_RSHPR &= ~_hoops_HPHPR;
					}
					else if (BIT (*flags, _hoops_RPHPR & needed_flags)) {
						if (--_hoops_SPRI->_hoops_CCHPR == 0) {
							if (_hoops_SPRI->_hoops_HGHIR != _hoops_SPRI->_hoops_HAHIR && _hoops_SPRI->_hoops_HGHIR != _hoops_SPRI->_hoops_IGHIR)
								FREE_ARRAY (_hoops_SPRI->_hoops_HGHIR, _hoops_IPRI->point_count, _hoops_ACGHR);
							_hoops_SPRI->_hoops_HGHIR = null;
						}
						else
							_hoops_SPRI->_hoops_HGHIR[offset] = 0.0f;

						_hoops_IPRI->_hoops_RSHPR &= ~_hoops_APHPR;
					}

					if (BIT (*flags, _hoops_AARHR & needed_flags)) {
						if (--_hoops_SPRI->_hoops_RCRHR == 0) {
							if (_hoops_SPRI->fcolors != _hoops_SPRI->_hoops_PAHIR && _hoops_SPRI->fcolors != _hoops_SPRI->ecolors)
								FREE_ARRAY (_hoops_SPRI->fcolors, (_hoops_IPRI->point_count +
								_hoops_IPRI->_hoops_GCRHR), RGB);
							_hoops_SPRI->fcolors = null;
						}
						else
							_hoops_SPRI->fcolors[offset] = _hoops_GPSR::_hoops_RPSR;

						_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PARHR;
					}
					else if (BIT (*flags, _hoops_HARHR & needed_flags)) {
						if (--_hoops_SPRI->_hoops_SIRHR == 0) {
							if (_hoops_SPRI->_hoops_IGHIR != _hoops_SPRI->_hoops_HAHIR && _hoops_SPRI->_hoops_IGHIR != _hoops_SPRI->_hoops_HGHIR)
								FREE_ARRAY (_hoops_SPRI->_hoops_IGHIR, (_hoops_IPRI->point_count +
								_hoops_IPRI->_hoops_GCRHR), _hoops_ACGHR);
							_hoops_SPRI->_hoops_IGHIR = null;
						}
						else
							_hoops_SPRI->_hoops_IGHIR[offset] = 0.0f;

						_hoops_IPRI->_hoops_ACRHR &= ~_hoops_IARHR;
						_hoops_IPRI->polyhedron_flags &= ~_hoops_SCRRA;
					}

					*flags &= ~needed_flags;
				}
				else
					_hoops_AHPGR = true;

				++flags;
			} _hoops_RGGA (--count == 0);
		}
		else if (count == _hoops_IPRI->point_count) {
			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				//_hoops_AA {
				if (ANYBIT (*flags, needed_flags)) {
					if (BIT (*flags, _hoops_HCRRA & needed_flags)) {
						if ((_hoops_SPRI->_hoops_ICRRA-= count) == 0) {
							if (_hoops_SPRI->_hoops_PAHIR != _hoops_SPRI->ecolors && _hoops_SPRI->_hoops_PAHIR != _hoops_SPRI->fcolors)
								FREE_ARRAY (_hoops_SPRI->_hoops_PAHIR, _hoops_IPRI->point_count, RGB);
							_hoops_SPRI->_hoops_PAHIR = null;
						}
						else
							_hoops_SPRI->_hoops_PAHIR[offset] = _hoops_GPSR::_hoops_RPSR;

						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_HCRRA;
					}
					else if (BIT (*flags, _hoops_SIRRA & needed_flags)) {
						if ((_hoops_SPRI->_hoops_PCRRA -= count) == 0) {
							if (_hoops_SPRI->_hoops_HAHIR != _hoops_SPRI->_hoops_HGHIR && _hoops_SPRI->_hoops_HAHIR != _hoops_SPRI->_hoops_IGHIR)
								FREE_ARRAY (_hoops_SPRI->_hoops_HAHIR, _hoops_IPRI->point_count, _hoops_ACGHR);
							_hoops_SPRI->_hoops_HAHIR = null;
						}
						else
							_hoops_SPRI->_hoops_HAHIR[offset] = 0.0f;

						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_SIRRA;
					}

					if (BIT (*flags, _hoops_PPHPR & needed_flags)) {
						if ((_hoops_SPRI->_hoops_SCHPR -= count) == 0) {
							if (_hoops_SPRI->ecolors != _hoops_SPRI->_hoops_PAHIR && _hoops_SPRI->ecolors != _hoops_SPRI->fcolors)
								FREE_ARRAY (_hoops_SPRI->ecolors, _hoops_IPRI->point_count, RGB);
							_hoops_SPRI->ecolors = null;
						}
						else
							_hoops_SPRI->ecolors[offset] = _hoops_GPSR::_hoops_RPSR;

						_hoops_IPRI->_hoops_RSHPR &= ~_hoops_HPHPR;
					}
					else if (BIT (*flags, _hoops_RPHPR & needed_flags)) {
						if ((_hoops_SPRI->_hoops_CCHPR -= count) == 0) {
							if (_hoops_SPRI->_hoops_HGHIR != _hoops_SPRI->_hoops_HAHIR && _hoops_SPRI->_hoops_HGHIR != _hoops_SPRI->_hoops_IGHIR)
								FREE_ARRAY (_hoops_SPRI->_hoops_HGHIR, _hoops_IPRI->point_count, _hoops_ACGHR);
							_hoops_SPRI->_hoops_HGHIR = null;
						}
						else
							_hoops_SPRI->_hoops_HGHIR[offset] = 0.0f;

						_hoops_IPRI->_hoops_RSHPR &= ~_hoops_APHPR;
					}

					if (BIT (*flags, _hoops_AARHR & needed_flags)) {
						if ((_hoops_SPRI->_hoops_RCRHR -= count) == 0) {
							if (_hoops_SPRI->fcolors != _hoops_SPRI->_hoops_PAHIR && _hoops_SPRI->fcolors != _hoops_SPRI->ecolors)
								FREE_ARRAY (_hoops_SPRI->fcolors, (_hoops_IPRI->point_count +
								_hoops_IPRI->_hoops_GCRHR), RGB);
							_hoops_SPRI->fcolors = null;
						}
						else
							_hoops_SPRI->fcolors[offset] = _hoops_GPSR::_hoops_RPSR;

						_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PARHR;
					}
					else if (BIT (*flags, _hoops_HARHR & needed_flags)) {
						if ((_hoops_SPRI->_hoops_SIRHR -= count) == 0) {
							if (_hoops_SPRI->_hoops_IGHIR != _hoops_SPRI->_hoops_HAHIR && _hoops_SPRI->_hoops_IGHIR != _hoops_SPRI->_hoops_HGHIR)
								FREE_ARRAY (_hoops_SPRI->_hoops_IGHIR, (_hoops_IPRI->point_count +
								_hoops_IPRI->_hoops_GCRHR), _hoops_ACGHR);
							_hoops_SPRI->_hoops_IGHIR = null;
						}
						else
							_hoops_SPRI->_hoops_IGHIR[offset] = 0.0f;

						_hoops_IPRI->_hoops_ACRHR &= ~_hoops_IARHR;
						_hoops_IPRI->polyhedron_flags &= ~_hoops_SCRRA;
					}

					*flags &= ~needed_flags;
				}
				else
					_hoops_AHPGR = true;

				++flags;
				//} _hoops_CCGR (--_hoops_RPR == 0);
			}
			else {
				flags = _hoops_SPRI->_hoops_CHHPR(offset);

				do {
					if (ANYBIT (*flags, needed_flags)) {
						if (BIT (*flags, _hoops_HCRRA & needed_flags)) {
							if (--_hoops_SPRI->_hoops_ICRRA == 0) {
								if (_hoops_SPRI->_hoops_PAHIR != _hoops_SPRI->ecolors && _hoops_SPRI->_hoops_PAHIR != _hoops_SPRI->fcolors)
									FREE_ARRAY (_hoops_SPRI->_hoops_PAHIR, _hoops_IPRI->point_count, RGB);
								_hoops_SPRI->_hoops_PAHIR = null;
							}
							else
								_hoops_SPRI->_hoops_PAHIR[offset] = _hoops_GPSR::_hoops_RPSR;

							_hoops_IPRI->_hoops_AGRHR &= ~_hoops_HCRRA;
						}
						else if (BIT (*flags, _hoops_SIRRA & needed_flags)) {
							if (--_hoops_SPRI->_hoops_PCRRA == 0) {
								if (_hoops_SPRI->_hoops_HAHIR != _hoops_SPRI->_hoops_HGHIR && _hoops_SPRI->_hoops_HAHIR != _hoops_SPRI->_hoops_IGHIR)
									FREE_ARRAY (_hoops_SPRI->_hoops_HAHIR, _hoops_IPRI->point_count, _hoops_ACGHR);
								_hoops_SPRI->_hoops_HAHIR = null;
							}
							else
								_hoops_SPRI->_hoops_HAHIR[offset] = 0.0f;

							_hoops_IPRI->_hoops_AGRHR &= ~_hoops_SIRRA;
						}

						if (BIT (*flags, _hoops_PPHPR & needed_flags)) {
							if (--_hoops_SPRI->_hoops_SCHPR == 0) {
								if (_hoops_SPRI->ecolors != _hoops_SPRI->_hoops_PAHIR && _hoops_SPRI->ecolors != _hoops_SPRI->fcolors)
									FREE_ARRAY (_hoops_SPRI->ecolors, _hoops_IPRI->point_count, RGB);
								_hoops_SPRI->ecolors = null;
							}
							else
								_hoops_SPRI->ecolors[offset] = _hoops_GPSR::_hoops_RPSR;

							_hoops_IPRI->_hoops_RSHPR &= ~_hoops_HPHPR;
						}
						else if (BIT (*flags, _hoops_RPHPR & needed_flags)) {
							if (--_hoops_SPRI->_hoops_CCHPR == 0) {
								if (_hoops_SPRI->_hoops_HGHIR != _hoops_SPRI->_hoops_HAHIR && _hoops_SPRI->_hoops_HGHIR != _hoops_SPRI->_hoops_IGHIR)
									FREE_ARRAY (_hoops_SPRI->_hoops_HGHIR, _hoops_IPRI->point_count, _hoops_ACGHR);
								_hoops_SPRI->_hoops_HGHIR = null;
							}
							else
								_hoops_SPRI->_hoops_HGHIR[offset] = 0.0f;

							_hoops_IPRI->_hoops_RSHPR &= ~_hoops_APHPR;
						}

						if (BIT (*flags, _hoops_AARHR & needed_flags)) {
							if (--_hoops_SPRI->_hoops_RCRHR == 0) {
								if (_hoops_SPRI->fcolors != _hoops_SPRI->_hoops_PAHIR && _hoops_SPRI->fcolors != _hoops_SPRI->ecolors)
									FREE_ARRAY (_hoops_SPRI->fcolors, (_hoops_IPRI->point_count +
									_hoops_IPRI->_hoops_GCRHR), RGB);
								_hoops_SPRI->fcolors = null;
							}
							else
								_hoops_SPRI->fcolors[offset] = _hoops_GPSR::_hoops_RPSR;

							_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PARHR;
						}
						else if (BIT (*flags, _hoops_HARHR & needed_flags)) {
							if (--_hoops_SPRI->_hoops_SIRHR == 0) {
								if (_hoops_SPRI->_hoops_IGHIR != _hoops_SPRI->_hoops_HAHIR && _hoops_SPRI->_hoops_IGHIR != _hoops_SPRI->_hoops_HGHIR)
									FREE_ARRAY (_hoops_SPRI->_hoops_IGHIR, (_hoops_IPRI->point_count +
									_hoops_IPRI->_hoops_GCRHR), _hoops_ACGHR);
								_hoops_SPRI->_hoops_IGHIR = null;
							}
							else
								_hoops_SPRI->_hoops_IGHIR[offset] = 0.0f;

							_hoops_IPRI->_hoops_ACRHR &= ~_hoops_IARHR;
							_hoops_IPRI->polyhedron_flags &= ~_hoops_SCRRA;
						}

						*flags &= ~needed_flags;
					}
					else
						_hoops_AHPGR = true;

					++flags;
				} _hoops_RGGA (--count == 0);
			}

			/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_ISSC _hoops_IS _hoops_IRS _hoops_PIAP _hoops_CAS _hoops_RH _hoops_SGI _hoops_CHR _hoops_GHRHR, _hoops_SR _hoops_GHCA _hoops_RRP _hoops_IS _hoops_CIH _hoops_RH _hoops_SGI _hoops_CRPR */
			if (/*!_hoops_IRRC (_hoops_CPHAR->_hoops_PHRHR, _hoops_PCSII) &&*/
				BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR) &&
				_hoops_SPRI->lvf_uniform(_hoops_IPRI->point_count)) {
					_hoops_SPRI->_hoops_SGRHR = _hoops_SPRI->flags[0];
					FREE_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
					_hoops_SPRI->flags = null;
					_hoops_IPRI->polyhedron_flags &= ~_hoops_CGRHR;
			}
		}
	}

	if (_hoops_AHPGR && _hoops_GCSII)
		HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");

	_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_GGARA|_hoops_RPSIR);
	HI_Invalidate_Display_Lists (_hoops_RIGC, _hoops_IPRI);

Release:
	_hoops_IRRPR();
}

HC_INTERFACE void HC_CDECL HC_MUnSet_Vertex_Colors2 (
	Key						key,
	char const *			type,
	int						offset,
	int						count)
{
	_hoops_PAPPR context("MUnSet_Vertex_Colors2");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Vertex_Colors2 (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_S (null, "%S, ", type));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d);}\n", offset, count));
	);

	_hoops_HCSII(context, key, type, offset, count);
#endif
}

HC_INTERFACE void HC_CDECL HC_MUnSet_Vertex_Colors (
	Key						key,
	int						offset,
	int						count)
{
	_hoops_PAPPR context("MUnSet_Vertex_Colors");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Vertex_Colors (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d);}\n", offset, count));
	);

	_hoops_HCSII(context, key, "faces, edges, vertex", offset, count);
#endif
}


/**********************************************************************************************************/

HC_INTERFACE void HC_CDECL HC_MSet_Spec_Vert_Col_By_FIndex (
	Key							key,
	char const *				geometry,
	int							count,
	int const *					indices,
	float const *				findices)
{
	_hoops_PAPPR context("MSet_Specific_Vertex_Colors_By_FIndex");

#ifdef _hoops_GCGHR
	_hoops_IRPPR ("Geometry Colors");
#else
#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else
	CODE_GENERATION (
		int		count2 = count;
		HI_Dump_Code (Sprintf_D (null, "{int* indices = (int*) malloc(sizeof(int)*%d);\n", count2));
		HI_Dump_Code (Sprintf_D (null, "float* findices = (float*) malloc(sizeof(float)*%d);\n", count2));
		++HOOPS_WORLD->_hoops_ISPPR;
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "indices[%d] = %f;\n", count2, indices[count2]));
			HI_Dump_Code (_hoops_CHCHR (null, "findices[%d] = %f;\n", count2, findices[count2]));
		}
		HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Specific_Vertex_Colors_By_FIndex (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_SD (null, "%S, %d, indices, findices);\n", geometry, count));
		HI_Dump_Code ("free (indices);\n");
		HI_Dump_Code ("free (findices);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	if (count == 0)
		return;

	if (count < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		return;
	}

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_ACGPP)) == null)
		return;

	ASSERT(_hoops_IPRI->type != _hoops_CSIP);

	_hoops_ACGHR *			_hoops_PAHIR;
	_hoops_ACGHR *			ecolors;
	_hoops_ACGHR *			fcolors;

	Local_Vertex_Flags *		flags = null;
	bool						_hoops_GSSII = true;
	bool						_hoops_ISCII = false;

	Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

	int	_hoops_PIRRA = _hoops_SPRI->_hoops_HIRRA;


	Color_Object	_hoops_HSCII;
	_hoops_HCRPR			name;
	HI_Canonize_Chars (geometry, &name);
	char const *	_hoops_RPPA = name.text;
	if (!HI_Decipher_Color_Target (context, &_hoops_RPPA, _hoops_RPPA + name.length, true, &_hoops_HSCII, (Color_FACE|Color_EDGE|Color_VERTEX))) {
		_hoops_RGAIR (name);
		goto Release;
	}
	_hoops_RGAIR (name);

	if (!_hoops_PRSII (_hoops_IPRI, count, indices))
		goto Release;

	if (ANYBIT (_hoops_HSCII, ~(Color_MARKER|Color_VERTEX|Color_EDGE|Color_FACE))) {
		HE_ERROR (HEC_MSET_VERTEX, HES_CANNOT_SET_ATTRIBUTE, "Only marker/vertex, edge, or face color may be set on a vertex");
		goto Release;
	}

	//_hoops_RSSII = *_hoops_AHRI;
	//_hoops_IH (_hoops_HAS = 0; _hoops_HAS < _hoops_RPR; _hoops_HAS++) {
	//	_hoops_RPP (_hoops_RSSII != _hoops_AHRI[_hoops_HAS]) {
	//		_hoops_ASSII = _hoops_RCPP;
	//		_hoops_IHSA;
	//	}
	//}

	if (count > _hoops_IPRI->point_count) {
		HE_WARNING (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Indices count exceeds vertex count.");
	}

	if (count < _hoops_IPRI->point_count) {
		/* _hoops_PAH'_hoops_RA _hoops_GCAS _hoops_SHH _hoops_RGSR _hoops_HCR _hoops_PSPI */
		_hoops_GSSII = false;
	}
#if 0
	else {
		/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_CPIC _hoops_IS _hoops_AA _hoops_PCCP _hoops_CHCRA _hoops_PII _hoops_RGR, _hoops_SCH _hoops_IRHS _hoops_IS _hoops_SHH _hoops_HAGH */
		for (i = 0; i < count; i++) {
			if (i != indices[i]) {
				_hoops_GSSII = false;
				break;
			}
		}
	}
#endif

	if (BIT (_hoops_HSCII, Color_VERTEX)) {
		if (_hoops_SPRI->_hoops_HAHIR == null) {
			if (BIT (_hoops_HSCII, Color_EDGE) && _hoops_SPRI->_hoops_HGHIR != null)
				_hoops_SPRI->_hoops_HAHIR = _hoops_SPRI->_hoops_HGHIR;
			else if (BIT (_hoops_HSCII, Color_FRONT) && _hoops_SPRI->_hoops_IGHIR != null)
				_hoops_SPRI->_hoops_HAHIR = _hoops_SPRI->_hoops_IGHIR;
			else
				HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_SIRRA, 0);
		}
		else {
			/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GCSP _hoops_HIH _hoops_ASAI _hoops_RGSR _hoops_IRS _hoops_GCSP _hoops_ARIP, _hoops_IPS */
			if (_hoops_SPRI->_hoops_HAHIR == _hoops_SPRI->_hoops_HGHIR &&
				_hoops_SPRI->_hoops_HAHIR == _hoops_SPRI->_hoops_IGHIR &&
				ANYBIT (_hoops_HSCII, Color_EDGE|Color_FRONT) &&
				!ALLBITS (_hoops_HSCII, Color_EDGE|Color_FRONT)) {
				/* 3-_hoops_PPRRR _hoops_HSSRR, _hoops_SPR _hoops_IIGR _hoops_RH _hoops_HIASR _hoops_GHHS _hoops_RAAP _hoops_GGSR */
				if (!BIT (_hoops_HSCII, Color_EDGE)) {
					_hoops_SPRI->_hoops_HGHIR = (_hoops_ACGHR *)
						HI_Clone_Anything (_hoops_SPRI->_hoops_HGHIR,
										   _hoops_IPRI->point_count *
										   (long)sizeof(_hoops_ACGHR));
				}
				else /* _hoops_RPP (!_hoops_IRRC (_hoops_RGSII, _hoops_RCRRA)) */ {
					_hoops_SPRI->_hoops_IGHIR = (_hoops_ACGHR *)
						HI_Clone_Anything (_hoops_SPRI->_hoops_IGHIR,
										   (_hoops_IPRI->point_count +
										    _hoops_IPRI->_hoops_GCRHR) *
										   (long)sizeof(_hoops_ACGHR));
				}
			}
			else if (_hoops_SPRI->_hoops_HAHIR == _hoops_SPRI->_hoops_HGHIR &&
						!BIT (_hoops_HSCII, Color_EDGE) ||
					 _hoops_SPRI->_hoops_HAHIR == _hoops_SPRI->_hoops_IGHIR &&
						!BIT (_hoops_HSCII, Color_FRONT)) {
				/* _hoops_IHSA _hoops_HSSRR */
				_hoops_SPRI->_hoops_HAHIR = (_hoops_ACGHR *)
					HI_Clone_Anything (_hoops_SPRI->_hoops_HAHIR,
									   _hoops_IPRI->point_count *
									   (long)sizeof(_hoops_ACGHR));
			}
		}
		_hoops_PAHIR = _hoops_SPRI->_hoops_HAHIR;
	}
	else _hoops_PAHIR = null;

	if (BIT (_hoops_HSCII, Color_EDGE)) {
		if (_hoops_SPRI->_hoops_HGHIR == null) {
			if (BIT (_hoops_HSCII, Color_VERTEX) && _hoops_SPRI->_hoops_HAHIR != null)
				_hoops_SPRI->_hoops_HGHIR = _hoops_SPRI->_hoops_HAHIR;
			else if (BIT (_hoops_HSCII, Color_FRONT) && _hoops_SPRI->_hoops_IGHIR != null)
				_hoops_SPRI->_hoops_HGHIR = _hoops_SPRI->_hoops_IGHIR;
			else
				HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_RPHPR, 0);
		}
		else {
			/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GCSP _hoops_HIH _hoops_ASAI _hoops_RGSR _hoops_IRS _hoops_GCSP _hoops_ARIP, _hoops_IPS */
			if (_hoops_SPRI->_hoops_HGHIR == _hoops_SPRI->_hoops_HAHIR &&
				_hoops_SPRI->_hoops_HGHIR == _hoops_SPRI->_hoops_IGHIR &&
				ANYBIT (_hoops_HSCII, Color_VERTEX|Color_FRONT) &&
				!ALLBITS (_hoops_HSCII, Color_VERTEX|Color_FRONT)) {
				/* 3-_hoops_PPRRR _hoops_HSSRR, _hoops_SPR _hoops_IIGR _hoops_RH _hoops_HIASR _hoops_GHHS _hoops_RAAP _hoops_GGSR */
				if (!BIT (_hoops_HSCII, Color_VERTEX)) {
					_hoops_SPRI->_hoops_HAHIR = (_hoops_ACGHR *)
						HI_Clone_Anything (_hoops_SPRI->_hoops_HAHIR,
										   _hoops_IPRI->point_count *
										   (long)sizeof(_hoops_ACGHR));
				}
				else /* _hoops_RPP (!_hoops_IRRC (_hoops_RGSII, _hoops_RCRRA)) */ {
					_hoops_SPRI->_hoops_IGHIR = (_hoops_ACGHR *)
						HI_Clone_Anything (_hoops_SPRI->_hoops_IGHIR,
										   (_hoops_IPRI->point_count +
										    _hoops_IPRI->_hoops_GCRHR) *
										   (long)sizeof(_hoops_ACGHR));
				}
			}
			else if (_hoops_SPRI->_hoops_HGHIR == _hoops_SPRI->_hoops_HAHIR &&
						!BIT (_hoops_HSCII, Color_VERTEX) ||
					 _hoops_SPRI->_hoops_HGHIR == _hoops_SPRI->_hoops_IGHIR &&
						!BIT (_hoops_HSCII, Color_FRONT)) {
				/* _hoops_IHSA _hoops_HSSRR */
				_hoops_SPRI->_hoops_HGHIR = (_hoops_ACGHR *)
					HI_Clone_Anything (_hoops_SPRI->_hoops_HGHIR,
									   _hoops_IPRI->point_count *
									   (long)sizeof(_hoops_ACGHR));
			}
		}
		ecolors = _hoops_SPRI->_hoops_HGHIR;
	}
	else ecolors = null;

	if (BIT (_hoops_HSCII, Color_FRONT)) {
		if (_hoops_SPRI->_hoops_IGHIR == null) {
			if (_hoops_IPRI->_hoops_GCRHR != 0)
				HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_HARHR, 0);
			else if (BIT (_hoops_HSCII, Color_EDGE) && _hoops_SPRI->_hoops_HGHIR != null)
				_hoops_SPRI->_hoops_IGHIR = _hoops_SPRI->_hoops_HGHIR;
			else if (BIT (_hoops_HSCII, Color_VERTEX) && _hoops_SPRI->_hoops_HAHIR != null)
				_hoops_SPRI->_hoops_IGHIR = _hoops_SPRI->_hoops_HAHIR;
			else
				HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_HARHR, 0);
		}
		else {
			/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GCSP _hoops_HIH _hoops_ASAI _hoops_RGSR _hoops_IRS _hoops_GCSP _hoops_ARIP, _hoops_IPS */
			if (_hoops_SPRI->_hoops_IGHIR == _hoops_SPRI->_hoops_HAHIR &&
				_hoops_SPRI->_hoops_IGHIR == _hoops_SPRI->_hoops_HGHIR &&
				ANYBIT (_hoops_HSCII, Color_VERTEX|Color_EDGE) &&
				!ALLBITS (_hoops_HSCII, Color_VERTEX|Color_EDGE)) {
				/* 3-_hoops_PPRRR _hoops_HSSRR, _hoops_SPR _hoops_IIGR _hoops_RH _hoops_HIASR _hoops_GHHS _hoops_RAAP _hoops_GGSR */
				if (!BIT (_hoops_HSCII, Color_VERTEX)) {
					_hoops_SPRI->_hoops_HAHIR = (_hoops_ACGHR *)
						HI_Clone_Anything (_hoops_SPRI->_hoops_HAHIR,
										   _hoops_IPRI->point_count *
										   (long)sizeof(_hoops_ACGHR));
				}
				else /* _hoops_RPP (!_hoops_IRRC (_hoops_RGSII, _hoops_ACRRA)) */ {
					_hoops_SPRI->_hoops_HGHIR = (_hoops_ACGHR *)
						HI_Clone_Anything (_hoops_SPRI->_hoops_HGHIR,
										   _hoops_IPRI->point_count *
										   (long)sizeof(_hoops_ACGHR));
				}
			}
			else if (_hoops_SPRI->_hoops_IGHIR == _hoops_SPRI->_hoops_HAHIR && !BIT (_hoops_HSCII, Color_VERTEX) ||
					 _hoops_SPRI->_hoops_IGHIR == _hoops_SPRI->_hoops_HGHIR && !BIT (_hoops_HSCII, Color_EDGE)) {
				/* _hoops_IHSA _hoops_HSSRR */
				_hoops_SPRI->_hoops_IGHIR = (_hoops_ACGHR *)
					HI_Clone_Anything (_hoops_SPRI->_hoops_IGHIR,
									   (_hoops_IPRI->point_count +
									    _hoops_IPRI->_hoops_GCRHR) *
									   (long)sizeof(_hoops_ACGHR));
			}
		}
		fcolors = _hoops_SPRI->_hoops_IGHIR;
	}
	else fcolors = null;

	if (_hoops_GSSII) {
		/* _hoops_RCSII _hoops_HCR */
		if (/* _hoops_ASSII &&*/ !BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
			/* _hoops_PS _hoops_PAH _hoops_SAHR _hoops_SGH _hoops_RH _hoops_GHRHR _hoops_RIP */

			if (_hoops_PAHIR != null) {
				if (!ANYBIT (_hoops_SPRI->_hoops_SGRHR, _hoops_APPRA)) {
					_hoops_SPRI->_hoops_SGRHR |= _hoops_SIRRA;
					_hoops_SPRI->_hoops_PCRRA += count;
					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_SIRRA;
				}
				else if (BIT (_hoops_SPRI->_hoops_SGRHR, _hoops_HCRRA)) {
					_hoops_SPRI->_hoops_SGRHR &= ~_hoops_HCRRA;
					_hoops_SPRI->_hoops_ICRRA -= count;
					_hoops_SPRI->_hoops_SGRHR |= _hoops_SIRRA;
					_hoops_SPRI->_hoops_PCRRA += count;
					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
				}
				else if (BIT (_hoops_SPRI->_hoops_SGRHR, _hoops_CCRRA)) {
					_hoops_SPRI->_hoops_SGRHR &= ~_hoops_CCRRA;
					_hoops_SPRI->_hoops_HIRRA -= count;
					_hoops_SPRI->_hoops_SGRHR |= _hoops_SIRRA;
					_hoops_SPRI->_hoops_PCRRA += count;
					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
				}
			}

			if (ecolors != null) {
				if (!ANYBIT (_hoops_SPRI->_hoops_SGRHR, _hoops_PPPRA)) {
					_hoops_SPRI->_hoops_SGRHR |= _hoops_RPHPR;
					_hoops_SPRI->_hoops_CCHPR += count;
					_hoops_IPRI->_hoops_RSHPR &= ~_hoops_APHPR;
				}
				else if (BIT (_hoops_SPRI->_hoops_SGRHR, _hoops_PPHPR)) {
					_hoops_SPRI->_hoops_SGRHR &= ~_hoops_PPHPR;
					_hoops_SPRI->_hoops_SCHPR -= count;
					_hoops_SPRI->_hoops_SGRHR |= _hoops_RPHPR;
					_hoops_SPRI->_hoops_CCHPR += count;
					_hoops_IPRI->_hoops_RSHPR &= ~_hoops_AGSII;
				}
			}

			if (fcolors != null) {
				if (!ANYBIT (_hoops_SPRI->_hoops_SGRHR, _hoops_HPPRA)) {
					_hoops_SPRI->_hoops_SGRHR |= _hoops_HARHR;
					_hoops_SPRI->_hoops_SIRHR += count;
					_hoops_IPRI->_hoops_ACRHR &= ~_hoops_IARHR;
				}
				else if (BIT (_hoops_SPRI->_hoops_SGRHR, _hoops_AARHR)) {
					_hoops_SPRI->_hoops_SGRHR &= ~_hoops_AARHR;
					_hoops_SPRI->_hoops_RCRHR -= count;
					_hoops_SPRI->_hoops_SGRHR |= _hoops_HARHR;
					_hoops_SPRI->_hoops_SIRHR += count;
					_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PGSII;
				}
				_hoops_IPRI->polyhedron_flags &= ~_hoops_SCRRA;
			}


			/* _hoops_GGAS _hoops_CIPH _hoops_HII _hoops_RAS _hoops_AA-_hoops_HPGP _hoops_HAPR */
			//_hoops_HHIIA _hoops_PPGGR;
		}
		else {
			/* _hoops_RCSII _hoops_IRS _hoops_GIIAR */
			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
				for (int i = 0; i < _hoops_IPRI->point_count; i++)
					_hoops_SPRI->flags[i] = _hoops_SPRI->_hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
			}
		}
	}
	if (count < _hoops_IPRI->point_count) {
		/* _hoops_RCSII _hoops_IRS _hoops_GIIAR _hoops_IIGR _hoops_HCR _hoops_RSSI. */
		if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
			ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
			for (int i = 0; i < _hoops_IPRI->point_count; i++)
				_hoops_SPRI->flags[i] = _hoops_SPRI->_hoops_SGRHR;
			_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
		}
	}

	flags = _hoops_SPRI->_hoops_CHHPR();
	_hoops_ISCII = BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR);

	do {
		int				index = *indices++;
		float			findex = *findices++;

		if (findex < -0.5f || findex >= ((float)_hoops_GPARA + 0.5f)) {
			char			buf[MAX_ERRMSG];
			float			max = ((float)_hoops_GPARA + 0.5f),
										min = -0.5f;

			HE_ERROR2 (HEC_COLOR_MAP, HES_OUT_OF_RANGE_COLOR_INDEX,
					   Sprintf_F (null, "Color index %f is out of range -", findex),
					   Sprintf_FF (buf, "must be between %f and %f", min, max));

			if (_hoops_PAHIR != null) _hoops_PAHIR[index] = 0.0f;
			if (ecolors != null) ecolors[index] = 0.0f;
			if (fcolors != null) fcolors[index] = 0.0f;
		}
		else {
			if (_hoops_PAHIR != null) _hoops_PAHIR[index] = findex;
			if (ecolors != null) ecolors[index] = findex;
			if (fcolors != null) fcolors[index] = findex;
		}

		/* (_hoops_AGCR _hoops_CSCII _hoops_CHR _hoops_SSAAA _hoops_IH _hoops_RH '_hoops_PSP _hoops_PGHC _hoops_RGSR' _hoops_AGIR) */

		if (_hoops_ISCII) {
			if (_hoops_PAHIR != null) {
				if (!ANYBIT (flags[index], _hoops_APPRA)) {
					flags[index] |= _hoops_SIRRA;
					++_hoops_SPRI->_hoops_PCRRA;
					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_SIRRA;
				}
				else if (BIT (flags[index], _hoops_HCRRA)) {
					flags[index] &= ~_hoops_HCRRA;
					--_hoops_SPRI->_hoops_ICRRA;
					flags[index] |= _hoops_SIRRA;
					++_hoops_SPRI->_hoops_PCRRA;
					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
				}
				else if (BIT (flags[index], _hoops_CCRRA)) {
					flags[index] &= ~_hoops_CCRRA;
					--_hoops_SPRI->_hoops_HIRRA;
					flags[index] |= _hoops_SIRRA;
					++_hoops_SPRI->_hoops_PCRRA;
					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
				}
			}

			if (ecolors != null) {
				if (!ANYBIT (flags[index], _hoops_PPPRA)) {
					flags[index] |= _hoops_RPHPR;
					++_hoops_SPRI->_hoops_CCHPR;
					_hoops_IPRI->_hoops_RSHPR &= ~_hoops_APHPR;
				}
				else if (BIT (flags[index], _hoops_PPHPR)) {
					flags[index] &= ~_hoops_PPHPR;
					--_hoops_SPRI->_hoops_SCHPR;
					flags[index] |= _hoops_RPHPR;
					++_hoops_SPRI->_hoops_CCHPR;
					_hoops_IPRI->_hoops_RSHPR &= ~_hoops_AGSII;
				}
			}

			if (fcolors != null) {
				if (!ANYBIT (flags[index], _hoops_HPPRA)) {
					flags[index] |= _hoops_HARHR;
					++_hoops_SPRI->_hoops_SIRHR;
					_hoops_IPRI->_hoops_ACRHR &= ~_hoops_IARHR;
				}
				else if (BIT (flags[index], _hoops_AARHR)) {
					flags[index] &= ~_hoops_AARHR;
					--_hoops_SPRI->_hoops_RCRHR;
					flags[index] |= _hoops_HARHR;
					++_hoops_SPRI->_hoops_SIRHR;
					_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PGSII;
				}
				_hoops_IPRI->polyhedron_flags &= ~_hoops_SCRRA;
			}
		}
	} _hoops_RGGA (--count == 0);

	if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR) &&
		_hoops_SPRI->lvf_uniform(_hoops_IPRI->point_count)) {
		_hoops_SPRI->_hoops_SGRHR = _hoops_SPRI->flags[0];
		FREE_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
		_hoops_SPRI->flags = null;
		_hoops_IPRI->polyhedron_flags &= ~_hoops_CGRHR;
	}


	HI_Reset_Strip_Flags (_hoops_IPRI);
	HI_Invalidate_Display_Lists (context, _hoops_IPRI);

	/* _hoops_RRRPR _hoops_IIGR _hoops_SPIGA _hoops_HHS _hoops_SHH _hoops_IRAP */
	if (_hoops_IPRI->owner != null) {
		if (_hoops_PIRRA != 0) {
			if (_hoops_SPRI->_hoops_HIRRA == 0)
				HI_Less_Transparencies (context, _hoops_IPRI->owner, 1);
		}
		else {
			if (_hoops_SPRI->_hoops_HIRRA != 0)
				HI_More_Transparencies (context, _hoops_IPRI->owner, 1);
		}

		if (!BIT (_hoops_IPRI->owner->_hoops_RCGC, _hoops_ASRRA))
			HI_Propagate_Maybes (context, _hoops_IPRI->owner, _hoops_ASRRA);
	}

	/* _hoops_HPCAR _hoops_IGSIP _hoops_HRGR _hoops_SIGR */
	_hoops_SASIR (context, (Geometry *)_hoops_IPRI, _hoops_GPSIR|_hoops_RPSIR);

  Release:
	_hoops_IRRPR();
#endif
#endif
}

HC_INTERFACE void HC_CDECL HC_MSet_Spec_Vert_Col_By_Value (
	Key					key,
	char const *		geometry,
	int					count,
	int const *			indices,
	char const *		color_space,
	RGB const *			values)
{
	_hoops_PAPPR context("MSet_Specific_Vertex_Colors_By_Value");

#ifdef _hoops_GCGHR
	_hoops_IRPPR ("Geometry Colors");
#else
	CODE_GENERATION (
		int		count2 = count;
		HI_Dump_Code (Sprintf_D (null, "{int* indices = (int*) malloc(sizeof(int)*%d);\n", count2));
		HI_Dump_Code (Sprintf_D (null, "HC_RGB* values = (HC_RGB*) malloc(sizeof(HC_RGB)*%d);\n", count2));
		++HOOPS_WORLD->_hoops_ISPPR;
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (Sprintf_DD (null, "indices[%d].x = %d;\n", count2, indices[count2]));
			HI_Dump_Code (_hoops_CHCHR (null, "values[%d].red = %f;	 ", count2, values[count2].red));
			HI_Dump_Code (_hoops_CHCHR (null, "values[%d].green = %f;	 ", count2, values[count2].green));
			HI_Dump_Code (_hoops_CHCHR (null, "values[%d].blue = %f;\n", count2, values[count2].blue));
		}
		HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Specific_Vertex_Colors_By_Value (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_SD (null, "%S, %d, ", geometry, count));
		HI_Dump_Code (Sprintf_S (null, "indices, %S, values);\n", color_space));
		HI_Dump_Code ("free (indices);\n");
		HI_Dump_Code ("free (values);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	if (count == 0)
		return;  /* _hoops_CPRSH */

	if (count < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		return;
	}

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_ACGPP)) == null)
		return;

	ASSERT(_hoops_IPRI->type != _hoops_CSIP);

	RGB *						_hoops_PAHIR;
	RGB *						ecolors;
	RGB *						fcolors;

	Local_Vertex_Flags *		flags = null;
	bool						_hoops_GSSII = true;
	bool						_hoops_ISCII = false;

	Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;
	int	_hoops_PIRRA = _hoops_SPRI->_hoops_HIRRA;


	Color_Object	_hoops_HSCII;
	_hoops_HCRPR			name;
	HI_Canonize_Chars (geometry, &name);
	char const *	_hoops_RPPA = name.text;
	if (!HI_Decipher_Color_Target (context, &_hoops_RPPA, _hoops_RPPA + name.length, true, &_hoops_HSCII, (Color_FACE|Color_EDGE|Color_VERTEX))) {
		_hoops_RGAIR (name);
		goto Release;
	}
	_hoops_RGAIR (name);

	if (!_hoops_PRSII (_hoops_IPRI, count, indices))
		goto Release;


	if (ANYBIT (_hoops_HSCII, ~(Color_MARKER|Color_VERTEX|Color_EDGE|Color_FACE))) {
		HE_ERROR (HEC_MSET_VERTEX, HES_CANNOT_SET_ATTRIBUTE,
				  "Only marker/vertex, edge, or face color may be set on a vertex");
		goto Release;
	}

	//_hoops_RSSII = *_hoops_HSH;
	//_hoops_IH (_hoops_HAS = 0; _hoops_HAS < _hoops_RPR; _hoops_HAS++) {
	//	_hoops_RPP (_hoops_RSSII != _hoops_HSH[_hoops_HAS]) {
	//		_hoops_ASSII = _hoops_RCPP;
	//		_hoops_IHSA;
	//	}
	//}

	if (count > _hoops_IPRI->point_count) {
		HE_WARNING (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Indices count exceeds vertex count.");
	}

	if (count < _hoops_IPRI->point_count) {
		/* _hoops_PAH'_hoops_RA _hoops_GCAS _hoops_SHH _hoops_RGSR _hoops_HCR _hoops_PSPI */
		_hoops_GSSII = false;
	}
#if 0
	else {
		/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_CPIC _hoops_IS _hoops_AA _hoops_PCCP _hoops_CHCRA _hoops_PII _hoops_RGR, _hoops_SCH _hoops_IRHS _hoops_IS _hoops_SHH _hoops_HAGH */
		for (i = 0; i < count; i++) {
			if (i != indices[i]) {
				_hoops_GSSII = false;
				break;
			}
		}
	}
#endif

	if (BIT (_hoops_HSCII, Color_VERTEX)) {
		if (_hoops_SPRI->_hoops_PAHIR == null) {
			if (BIT (_hoops_HSCII, Color_EDGE) && _hoops_SPRI->ecolors != null)
				_hoops_SPRI->_hoops_PAHIR = _hoops_SPRI->ecolors;
			else if (BIT (_hoops_HSCII, Color_FRONT) && _hoops_SPRI->fcolors != null)
				_hoops_SPRI->_hoops_PAHIR = _hoops_SPRI->fcolors;
			else
				HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_HCRRA, 0);
		}
		else {
			/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GCSP _hoops_HIH _hoops_ASAI _hoops_RGSR _hoops_IRS _hoops_GCSP _hoops_ARIP, _hoops_IPS */
			if (_hoops_SPRI->_hoops_PAHIR == _hoops_SPRI->ecolors &&
				_hoops_SPRI->_hoops_PAHIR == _hoops_SPRI->fcolors &&
				ANYBIT (_hoops_HSCII, Color_EDGE|Color_FRONT) &&
				!ALLBITS (_hoops_HSCII, Color_EDGE|Color_FRONT)) {
				/* 3-_hoops_PPRRR _hoops_HSSRR, _hoops_SPR _hoops_IIGR _hoops_RH _hoops_HIASR _hoops_GHHS _hoops_RAAP _hoops_GGSR */
				if (!BIT (_hoops_HSCII, Color_EDGE)) {
					_hoops_SPRI->ecolors = (RGB *)
						HI_Clone_Anything (_hoops_SPRI->ecolors,_hoops_IPRI->point_count * (long)sizeof(RGB));
				}
				else /* _hoops_RPP (!_hoops_IRRC (_hoops_RGSII, _hoops_RCRRA)) */ {
					_hoops_SPRI->fcolors = (RGB *)
						HI_Clone_Anything (_hoops_SPRI->fcolors, (_hoops_IPRI->point_count +  _hoops_IPRI->_hoops_GCRHR) * (long)sizeof(RGB));
				}
			}
			else if (_hoops_SPRI->_hoops_PAHIR == _hoops_SPRI->ecolors &&
						!BIT (_hoops_HSCII, Color_EDGE) ||
					 _hoops_SPRI->_hoops_PAHIR == _hoops_SPRI->fcolors &&
						!BIT (_hoops_HSCII, Color_FRONT)) {
				/* _hoops_IHSA _hoops_HSSRR */
				_hoops_SPRI->_hoops_PAHIR = (RGB *)
					HI_Clone_Anything (_hoops_SPRI->_hoops_PAHIR, _hoops_IPRI->point_count * (long)sizeof(RGB));
			}
		}
		_hoops_PAHIR = _hoops_SPRI->_hoops_PAHIR;
	}
	else _hoops_PAHIR = null;

	if (BIT (_hoops_HSCII, Color_EDGE)) {
		if (_hoops_SPRI->ecolors == null) {
			if (BIT (_hoops_HSCII, Color_VERTEX) && _hoops_SPRI->_hoops_PAHIR != null)
				_hoops_SPRI->ecolors = _hoops_SPRI->_hoops_PAHIR;
			else if (BIT (_hoops_HSCII, Color_FRONT) && _hoops_SPRI->fcolors != null)
				_hoops_SPRI->ecolors = _hoops_SPRI->fcolors;
			else
				HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_PPHPR, 0);
		}
		else {
			/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GCSP _hoops_HIH _hoops_ASAI _hoops_RGSR _hoops_IRS _hoops_GCSP _hoops_ARIP, _hoops_IPS */
			if (_hoops_SPRI->ecolors == _hoops_SPRI->_hoops_PAHIR &&
				_hoops_SPRI->ecolors == _hoops_SPRI->fcolors &&
				ANYBIT (_hoops_HSCII, Color_VERTEX|Color_FRONT) &&
				!ALLBITS (_hoops_HSCII, Color_VERTEX|Color_FRONT)) {
				/* 3-_hoops_PPRRR _hoops_HSSRR, _hoops_SPR _hoops_IIGR _hoops_RH _hoops_HIASR _hoops_GHHS _hoops_RAAP _hoops_GGSR */
				if (!BIT (_hoops_HSCII, Color_VERTEX)) {
					_hoops_SPRI->_hoops_PAHIR = (RGB *)
						HI_Clone_Anything (_hoops_SPRI->_hoops_PAHIR,
										   _hoops_IPRI->point_count *
										   (long)sizeof(RGB));
				}
				else /* _hoops_RPP (!_hoops_IRRC (_hoops_RGSII, _hoops_RCRRA)) */ {
					_hoops_SPRI->fcolors = (RGB *)
						HI_Clone_Anything (_hoops_SPRI->fcolors,
										   (_hoops_IPRI->point_count +
										    _hoops_IPRI->_hoops_GCRHR) *
										   (long)sizeof(RGB));
				}
			}
			else if (_hoops_SPRI->ecolors == _hoops_SPRI->_hoops_PAHIR &&
						!BIT (_hoops_HSCII, Color_VERTEX) ||
					 _hoops_SPRI->ecolors == _hoops_SPRI->fcolors &&
						!BIT (_hoops_HSCII, Color_FRONT)) {
				/* _hoops_IHSA _hoops_HSSRR */
				_hoops_SPRI->ecolors = (RGB *)
					HI_Clone_Anything (_hoops_SPRI->ecolors,
									   _hoops_IPRI->point_count *
									   (long)sizeof(RGB));
			}
		}
		ecolors = _hoops_SPRI->ecolors;
	}
	else ecolors = null;

	if (BIT (_hoops_HSCII, Color_FRONT)) {
		if (_hoops_SPRI->fcolors == null) {
			if (_hoops_IPRI->_hoops_GCRHR != 0)
				HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_AARHR, 0);
			else if (BIT (_hoops_HSCII, Color_EDGE) && _hoops_SPRI->ecolors != null)
				_hoops_SPRI->fcolors = _hoops_SPRI->ecolors;
			else if (BIT (_hoops_HSCII, Color_VERTEX) && _hoops_SPRI->_hoops_PAHIR != null)
				_hoops_SPRI->fcolors = _hoops_SPRI->_hoops_PAHIR;
			else
				HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_AARHR, 0);
		}
		else {
			/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GCSP _hoops_HIH _hoops_ASAI _hoops_RGSR _hoops_IRS _hoops_GCSP _hoops_ARIP, _hoops_IPS */
			if (_hoops_SPRI->fcolors == _hoops_SPRI->_hoops_PAHIR &&
				_hoops_SPRI->fcolors == _hoops_SPRI->ecolors &&
				ANYBIT (_hoops_HSCII, Color_VERTEX|Color_EDGE) &&
				!ALLBITS (_hoops_HSCII, Color_VERTEX|Color_EDGE)) {
				/* 3-_hoops_PPRRR _hoops_HSSRR, _hoops_SPR _hoops_IIGR _hoops_RH _hoops_HIASR _hoops_GHHS _hoops_RAAP _hoops_GGSR */
				if (!BIT (_hoops_HSCII, Color_VERTEX)) {
					_hoops_SPRI->_hoops_PAHIR = (RGB *)
						HI_Clone_Anything (_hoops_SPRI->_hoops_PAHIR,
										   _hoops_IPRI->point_count *
										   (long)sizeof(RGB));
				}
				else /* _hoops_RPP (!_hoops_IRRC (_hoops_RGSII, _hoops_ACRRA)) */ {
					_hoops_SPRI->ecolors = (RGB *)
						HI_Clone_Anything (_hoops_SPRI->ecolors,
										   _hoops_IPRI->point_count *
										   (long)sizeof(RGB));
				}
			}
			else if (_hoops_SPRI->fcolors == _hoops_SPRI->_hoops_PAHIR && !BIT (_hoops_HSCII, Color_VERTEX) ||
					 _hoops_SPRI->fcolors == _hoops_SPRI->ecolors && !BIT (_hoops_HSCII, Color_EDGE)) {
				/* _hoops_IHSA _hoops_HSSRR */
				_hoops_SPRI->fcolors = (RGB *)
					HI_Clone_Anything (_hoops_SPRI->fcolors,
									   (_hoops_IPRI->point_count +
									    _hoops_IPRI->_hoops_GCRHR) *
									   (long)sizeof(RGB));
			}
		}
		fcolors = _hoops_SPRI->fcolors;
	}
	else fcolors = null;

	flags  = _hoops_SPRI->flags;

	if ((color_space[0] == 'r' || color_space[0] == 'R') &&
		(color_space[1] == 'g' || color_space[1] == 'G') &&
		(color_space[2] == 'b' || color_space[2] == 'B') &&
		(color_space[3] == 'a' || color_space[3] == 'A')) {

		if (_hoops_GSSII) {
			/* _hoops_RCSII _hoops_HCR */
			if (/* _hoops_ASSII &&*/ !BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				/* _hoops_PS _hoops_PAH _hoops_SAHR _hoops_SGH _hoops_RH _hoops_GHRHR _hoops_RIP */

				if (!ANYBIT (_hoops_SPRI->_hoops_SGRHR, _hoops_APPRA)) {
					_hoops_SPRI->_hoops_SGRHR |= _hoops_CCRRA;
					_hoops_SPRI->_hoops_HIRRA += count;
					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_CCRRA;
				}
				else if (BIT (_hoops_SPRI->_hoops_SGRHR, _hoops_SIRRA)) {
					_hoops_SPRI->_hoops_SGRHR &= ~_hoops_SIRRA;
					_hoops_SPRI->_hoops_PCRRA -= count;
					_hoops_SPRI->_hoops_SGRHR |= _hoops_CCRRA;
					_hoops_SPRI->_hoops_HIRRA += count;
					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
				}
				else if (BIT (_hoops_SPRI->_hoops_SGRHR, _hoops_HCRRA)) {
					_hoops_SPRI->_hoops_SGRHR &= ~_hoops_HCRRA;
					_hoops_SPRI->_hoops_ICRRA -= count;
					_hoops_SPRI->_hoops_SGRHR |= _hoops_CCRRA;
					_hoops_SPRI->_hoops_HIRRA += count;
					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
				}
			}
			else {
				/* _hoops_RCSII _hoops_IRS _hoops_GIIAR */
				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
					ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
					for (int i = 0; i < _hoops_IPRI->point_count; i++)
						_hoops_SPRI->flags[i] = _hoops_SPRI->_hoops_SGRHR;
					_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
				}
			}
		}
		if (count < _hoops_IPRI->point_count) {
			/* _hoops_RCSII _hoops_IRS _hoops_GIIAR */
			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
				for (int i = 0; i < _hoops_IPRI->point_count; i++)
					_hoops_SPRI->flags[i] = _hoops_SPRI->_hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
			}
		}

		flags = _hoops_SPRI->_hoops_CHHPR();
		_hoops_ISCII = BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR);

		if (_hoops_SPRI->_hoops_IAHIR == null)
			HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_CCRRA, 0);

		RGBA const *		_hoops_SGHI = (RGBA const *)values;
		RGBAS32 alter *		_hoops_HPHSA = _hoops_SPRI->_hoops_IAHIR;

		do {
			int				index = *indices++;

			_hoops_HPHSA[index] = _hoops_CGSII(*_hoops_SGHI);

			/* (_hoops_AGCR _hoops_CSCII _hoops_CHR _hoops_SSAAA _hoops_IH _hoops_RH '_hoops_PSP _hoops_PGHC _hoops_RGSR' _hoops_AGIR) */

			if (_hoops_ISCII) {
				if (!ANYBIT (flags[index], _hoops_APPRA)) {
					flags[index] |= _hoops_CCRRA;
					++_hoops_SPRI->_hoops_HIRRA;
					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_CCRRA;
				}
				else if (BIT (flags[index], _hoops_SIRRA)) {
					flags[index] &= ~_hoops_SIRRA;
					--_hoops_SPRI->_hoops_PCRRA;
					flags[index] |= _hoops_CCRRA;
					++_hoops_SPRI->_hoops_HIRRA;
					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
				}
				else if (BIT (flags[index], _hoops_HCRRA)) {
					flags[index] &= ~_hoops_HCRRA;
					--_hoops_SPRI->_hoops_ICRRA;
					flags[index] |= _hoops_CCRRA;
					++_hoops_SPRI->_hoops_HIRRA;
					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
				}
			}

			++_hoops_SGHI;
		} _hoops_RGGA (--count == 0);
	}
	else if ((color_space[0] == 'r' || color_space[0] == 'R') &&
			 (color_space[1] == 'g' || color_space[1] == 'G') &&
			 (color_space[2] == 'b' || color_space[2] == 'B')) {

		if (_hoops_GSSII) {
			/* _hoops_RCSII _hoops_HCR */
			if (/* _hoops_ASSII &&*/ !BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				/* _hoops_PS _hoops_PAH _hoops_SAHR _hoops_SGH _hoops_RH _hoops_GHRHR _hoops_RIP */

				if (_hoops_PAHIR != null) {
					if (!ANYBIT (_hoops_SPRI->_hoops_SGRHR, _hoops_APPRA)) {
						_hoops_SPRI->_hoops_SGRHR |= _hoops_HCRRA;
						_hoops_SPRI->_hoops_ICRRA += count;
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_HCRRA;
					}
					else if (BIT (_hoops_SPRI->_hoops_SGRHR, _hoops_SIRRA)) {
						_hoops_SPRI->_hoops_SGRHR &= ~_hoops_SIRRA;
						_hoops_SPRI->_hoops_PCRRA -= count;
						_hoops_SPRI->_hoops_SGRHR |= _hoops_HCRRA;
						_hoops_SPRI->_hoops_ICRRA += count;
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
					}
					else if (BIT (_hoops_SPRI->_hoops_SGRHR, _hoops_CCRRA)) {
						_hoops_SPRI->_hoops_SGRHR &= ~_hoops_CCRRA;
						_hoops_SPRI->_hoops_HIRRA -= count;
						_hoops_SPRI->_hoops_SGRHR |= _hoops_HCRRA;
						_hoops_SPRI->_hoops_ICRRA += count;
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
					}
				}

				if (ecolors != null) {
					if (!ANYBIT (_hoops_SPRI->_hoops_SGRHR, _hoops_PPPRA)) {
						_hoops_SPRI->_hoops_SGRHR |= _hoops_PPHPR;
						_hoops_SPRI->_hoops_SCHPR += count;
						_hoops_IPRI->_hoops_RSHPR &= ~_hoops_HPHPR;
					}
					else if (BIT (_hoops_SPRI->_hoops_SGRHR, _hoops_RPHPR)) {
						_hoops_SPRI->_hoops_SGRHR &= ~_hoops_RPHPR;
						_hoops_SPRI->_hoops_CCHPR -= count;
						_hoops_SPRI->_hoops_SGRHR |= _hoops_PPHPR;
						_hoops_SPRI->_hoops_SCHPR += count;
						_hoops_IPRI->_hoops_RSHPR &= ~_hoops_AGSII;
					}
				}

				if (fcolors != null) {
					if (!ANYBIT (_hoops_SPRI->_hoops_SGRHR, _hoops_HPPRA)) {
						_hoops_SPRI->_hoops_SGRHR |= _hoops_AARHR;
						_hoops_SPRI->_hoops_RCRHR += count;
						_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PARHR;
					}
					else if (BIT (_hoops_SPRI->_hoops_SGRHR, _hoops_HARHR)) {
						_hoops_SPRI->_hoops_SGRHR &= ~_hoops_HARHR;
						_hoops_SPRI->_hoops_SIRHR -= count;
						_hoops_SPRI->_hoops_SGRHR |= _hoops_AARHR;
						_hoops_SPRI->_hoops_RCRHR += count;
						_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PGSII;
						_hoops_IPRI->polyhedron_flags &= ~_hoops_SCRRA;
					}
				}
			}
			else {
				/* _hoops_RCSII _hoops_IRS _hoops_GIIAR */
				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
					ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
					for (int i = 0; i < _hoops_IPRI->point_count; i++)
						_hoops_SPRI->flags[i] = _hoops_SPRI->_hoops_SGRHR;
					_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
				}
			}
		}
		if (count < _hoops_IPRI->point_count) {
			/* _hoops_RCSII _hoops_IRS _hoops_GIIAR _hoops_IIGR _hoops_HCR _hoops_RSSI. */
			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
				for (int i = 0; i < _hoops_IPRI->point_count; i++)
					_hoops_SPRI->flags[i] = _hoops_SPRI->_hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
			}
		}

		flags = _hoops_SPRI->_hoops_CHHPR();
		_hoops_ISCII = BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR);

		do {
			int			index = *indices++;

			RGB rgb = _hoops_HGSII(*values);

			if (_hoops_PAHIR != null)
				_hoops_PAHIR[index] = rgb;
			if (ecolors != null)
				ecolors[index] = rgb;
			if (fcolors != null)
				fcolors[index] = rgb;

			/* (_hoops_AGCR _hoops_CSCII _hoops_CHR _hoops_SSAAA _hoops_IH _hoops_RH '_hoops_PSP _hoops_PGHC _hoops_RGSR' _hoops_AGIR) */

			if (_hoops_ISCII) {
				if (_hoops_PAHIR != null) {
					if (!ANYBIT (flags[index], _hoops_APPRA)) {
						flags[index] |= _hoops_HCRRA;
						++_hoops_SPRI->_hoops_ICRRA;
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_HCRRA;
					}
					else if (BIT (flags[index], _hoops_SIRRA)) {
						flags[index] &= ~_hoops_SIRRA;
						--_hoops_SPRI->_hoops_PCRRA;
						flags[index] |= _hoops_HCRRA;
						++_hoops_SPRI->_hoops_ICRRA;
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
					}
					else if (BIT (flags[index], _hoops_CCRRA)) {
						flags[index] &= ~_hoops_CCRRA;
						--_hoops_SPRI->_hoops_HIRRA;
						flags[index] |= _hoops_HCRRA;
						++_hoops_SPRI->_hoops_ICRRA;
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
					}
				}

				if (ecolors != null) {
					if (!ANYBIT (flags[index], _hoops_PPPRA)) {
						flags[index] |= _hoops_PPHPR;
						++_hoops_SPRI->_hoops_SCHPR;
						_hoops_IPRI->_hoops_RSHPR &= ~_hoops_HPHPR;
					}
					else if (BIT (flags[index], _hoops_RPHPR)) {
						flags[index] &= ~_hoops_RPHPR;
						--_hoops_SPRI->_hoops_CCHPR;
						flags[index] |= _hoops_PPHPR;
						++_hoops_SPRI->_hoops_SCHPR;
						_hoops_IPRI->_hoops_RSHPR &= ~_hoops_AGSII;
					}
				}

				if (fcolors != null) {
					if (!ANYBIT (flags[index], _hoops_HPPRA)) {
						flags[index] |= _hoops_AARHR;
						++_hoops_SPRI->_hoops_RCRHR;
						_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PARHR;
					}
					else if (BIT (flags[index], _hoops_HARHR)) {
						flags[index] &= ~_hoops_HARHR;
						--_hoops_SPRI->_hoops_SIRHR;
						flags[index] |= _hoops_AARHR;
						++_hoops_SPRI->_hoops_RCRHR;
						_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PGSII;
						_hoops_IPRI->polyhedron_flags &= ~_hoops_SCRRA;
					}
				}
			}

			++values;
		} _hoops_RGGA (--count == 0);
	}
	else {
		_hoops_RHAH			_hoops_APHCR;
		Named_Material		*_hoops_HAA;

		if (!HI_Parse_Color_Map_By_Value (context, color_space, count, values, &_hoops_APHCR)) {
			goto Release;
		}

		_hoops_HAA = _hoops_APHCR._hoops_HAA;

		if (_hoops_GSSII) {
			/* _hoops_RCSII _hoops_HCR */
			if (/* _hoops_ASSII &&*/ !BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				/* _hoops_PS _hoops_PAH _hoops_SAHR _hoops_SGH _hoops_RH _hoops_GHRHR _hoops_RIP */

				if (_hoops_PAHIR != null) {
					if (!ANYBIT (_hoops_SPRI->_hoops_SGRHR, _hoops_APPRA)) {
						_hoops_SPRI->_hoops_SGRHR |= _hoops_HCRRA;
						_hoops_SPRI->_hoops_ICRRA += count;
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_HCRRA;
					}
					else if (BIT (_hoops_SPRI->_hoops_SGRHR, _hoops_SIRRA)) {
						_hoops_SPRI->_hoops_SGRHR &= ~_hoops_SIRRA;
						_hoops_SPRI->_hoops_PCRRA -= count;
						_hoops_SPRI->_hoops_SGRHR |= _hoops_HCRRA;
						_hoops_SPRI->_hoops_ICRRA += count;
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
					}
					else if (BIT (_hoops_SPRI->_hoops_SGRHR, _hoops_CCRRA)) {
						_hoops_SPRI->_hoops_SGRHR &= ~_hoops_CCRRA;
						_hoops_SPRI->_hoops_HIRRA -= count;
						_hoops_SPRI->_hoops_SGRHR |= _hoops_HCRRA;
						_hoops_SPRI->_hoops_ICRRA += count;
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
					}
				}

				if (ecolors != null) {
					if (!ANYBIT (_hoops_SPRI->_hoops_SGRHR, _hoops_PPPRA)) {
						_hoops_SPRI->_hoops_SGRHR |= _hoops_PPHPR;
						_hoops_SPRI->_hoops_SCHPR += count;
						_hoops_IPRI->_hoops_RSHPR &= ~_hoops_HPHPR;
					}
					else if (BIT (_hoops_SPRI->_hoops_SGRHR, _hoops_RPHPR)) {
						_hoops_SPRI->_hoops_SGRHR &= ~_hoops_RPHPR;
						_hoops_SPRI->_hoops_CCHPR -= count;
						_hoops_SPRI->_hoops_SGRHR |= _hoops_PPHPR;
						_hoops_SPRI->_hoops_SCHPR += count;
						_hoops_IPRI->_hoops_RSHPR &= ~_hoops_AGSII;
					}
				}

				if (fcolors != null) {
					if (!ANYBIT (_hoops_SPRI->_hoops_SGRHR, _hoops_HPPRA)) {
						_hoops_SPRI->_hoops_SGRHR |= _hoops_AARHR;
						_hoops_SPRI->_hoops_RCRHR += count;
						_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PARHR;
					}
					else if (BIT (_hoops_SPRI->_hoops_SGRHR, _hoops_HARHR)) {
						_hoops_SPRI->_hoops_SGRHR &= ~_hoops_HARHR;
						_hoops_SPRI->_hoops_SIRHR -= count;
						_hoops_SPRI->_hoops_SGRHR |= _hoops_AARHR;
						_hoops_SPRI->_hoops_RCRHR += count;
						_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PGSII;
						_hoops_IPRI->polyhedron_flags &= ~_hoops_SCRRA;
					}
				}

				/* _hoops_GGAS _hoops_CIPH _hoops_HII _hoops_RAS _hoops_AA-_hoops_HPGP _hoops_HAPR */
				//_hoops_HHIIA _hoops_PPGGR;
			}
			else {
				/* _hoops_RCSII _hoops_IRS _hoops_GIIAR */
				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
					ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
					for (int i = 0; i < _hoops_IPRI->point_count; i++)
						_hoops_SPRI->flags[i] = _hoops_SPRI->_hoops_SGRHR;
					_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
				}
			}
		}
		if (count < _hoops_IPRI->point_count) {
			/* _hoops_RCSII _hoops_IRS _hoops_GIIAR */
			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
				for (int i = 0; i < _hoops_IPRI->point_count; i++)
					_hoops_SPRI->flags[i] = _hoops_SPRI->_hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
			}
		}

		flags = _hoops_SPRI->_hoops_CHHPR();
		_hoops_ISCII = BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR);

		do {
			int						index = *indices++;

			if (_hoops_PAHIR != null)
				_hoops_PAHIR[index] = _hoops_HAA->_hoops_CSHR;

			if (ecolors != null)
				ecolors[index] = _hoops_HAA->_hoops_CSHR;

			if (fcolors != null)
				fcolors[index] = _hoops_HAA->_hoops_CSHR;

			/* (_hoops_AGCR _hoops_CSCII _hoops_CHR _hoops_SSAAA _hoops_IH _hoops_RH '_hoops_PSP _hoops_PGHC _hoops_RGSR' _hoops_AGIR) */

			if (_hoops_ISCII) {
				if (_hoops_PAHIR != null) {
					if (!ANYBIT (flags[index], _hoops_APPRA)) {
						flags[index] |= _hoops_HCRRA;
						++_hoops_SPRI->_hoops_ICRRA;
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_HCRRA;
					}
					else if (BIT (flags[index], _hoops_SIRRA)) {
						flags[index] &= ~_hoops_SIRRA;
						--_hoops_SPRI->_hoops_PCRRA;
						flags[index] |= _hoops_HCRRA;
						++_hoops_SPRI->_hoops_ICRRA;
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
					}
					else if (BIT (flags[index], _hoops_CCRRA)) {
						flags[index] &= ~_hoops_CCRRA;
						--_hoops_SPRI->_hoops_HIRRA;
						flags[index] |= _hoops_HCRRA;
						++_hoops_SPRI->_hoops_ICRRA;
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_APPRA;
					}
				}

				if (ecolors != null) {
					if (!ANYBIT (flags[index], _hoops_PPPRA)) {
						flags[index] |= _hoops_PPHPR;
						++_hoops_SPRI->_hoops_SCHPR;
						_hoops_IPRI->_hoops_RSHPR &= ~_hoops_HPHPR;
					}
					else if (BIT (flags[index], _hoops_RPHPR)) {
						flags[index] &= ~_hoops_RPHPR;
						--_hoops_SPRI->_hoops_CCHPR;
						flags[index] |= _hoops_PPHPR;
						++_hoops_SPRI->_hoops_SCHPR;
						_hoops_IPRI->_hoops_RSHPR &= ~_hoops_AGSII;
					}
				}

				if (fcolors != null) {
					if (!ANYBIT (flags[index], _hoops_HPPRA)) {
						flags[index] |= _hoops_AARHR;
						++_hoops_SPRI->_hoops_RCRHR;
						_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PARHR;
					}
					else if (BIT (flags[index], _hoops_HARHR)) {
						flags[index] &= ~_hoops_HARHR;
						--_hoops_SPRI->_hoops_SIRHR;
						flags[index] |= _hoops_AARHR;
						++_hoops_SPRI->_hoops_RCRHR;
						_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PGSII;
						_hoops_IPRI->polyhedron_flags &= ~_hoops_SCRRA;
					}
				}
			}

			++_hoops_HAA;
		} _hoops_RGGA (--count == 0);

		_hoops_HAA = _hoops_APHCR._hoops_HAA;
		HI_Free_Material_Names (_hoops_HAA, _hoops_APHCR.length);
		FREE_ARRAY (_hoops_HAA, _hoops_APHCR.length, Named_Material);
	}

	if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR) &&
		_hoops_SPRI->lvf_uniform(_hoops_IPRI->point_count)) {
		_hoops_SPRI->_hoops_SGRHR = _hoops_SPRI->flags[0];
		FREE_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
		_hoops_SPRI->flags = null;
		_hoops_IPRI->polyhedron_flags &= ~_hoops_CGRHR;
	}

	HI_Reset_Strip_Flags (_hoops_IPRI);
	HI_Invalidate_Display_Lists (context, _hoops_IPRI);

	if (_hoops_IPRI->owner != null) {
		if (_hoops_PIRRA != 0) {
			if (_hoops_SPRI->_hoops_HIRRA == 0)
				HI_Less_Transparencies (context, _hoops_IPRI->owner, 1);
		}
		else {
			if (_hoops_SPRI->_hoops_HIRRA != 0)
				HI_More_Transparencies (context, _hoops_IPRI->owner, 1);
		}

		/* _hoops_AGCR _hoops_CHR _hoops_ICIC _hoops_PRGI _hoops_RPP _hoops_CPSA _hoops_IRS _hoops_RSRRA */
		if (!BIT (_hoops_IPRI->owner->_hoops_RCGC, _hoops_ASRRA))
			HI_Propagate_Maybes (context, _hoops_IPRI->owner, _hoops_ASRRA);
	}

	/* _hoops_HPCAR _hoops_IGSIP _hoops_HRGR _hoops_SIGR */
	_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR|_hoops_RPSIR);

  Release:
	_hoops_IRRPR();
#endif
}

HC_INTERFACE void HC_CDECL HC_MSet_Spec_Face_Col_By_FIndex (
	Key							key,
	int							count,
	int const *					indices,
	float const *				findices)
{
	_hoops_PAPPR context("MSet_Specific_Face_Colors_By_FIndex");

#ifdef _hoops_GCGHR
	_hoops_IRPPR ("Geometry Colors");
#else
#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else

	CODE_GENERATION (
		int		count2 = count;
		if (count == 0) {
			HI_Dump_Code (Sprintf_LD (null, "HC_MSet_SpecificFace_Colors_By_FIndex (LOOKUP (%D), 0, 0, 0);\n", key));
		}
		else {
			HI_Dump_Code (Sprintf_D (null, "{float* findices = (float*) malloc(sizeof(float)*%d);\n", count2));
			HI_Dump_Code (Sprintf_D (null, "int* indices = (int*) malloc(sizeof(int)*%d);\n", count2));
			++HOOPS_WORLD->_hoops_ISPPR;
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (_hoops_CHCHR (null, "indices[%d] = %f;\n", count2, indices[count2]));
				HI_Dump_Code (_hoops_CHCHR (null, "findices[%d] = %f;\n", count2, findices[count2]));
			}
			HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Specific_Face_Colors_By_FIndex (LOOKUP (%D), ", key));
			HI_Dump_Code (Sprintf_D (null, "%d, indices, findices);\n", count));
			HI_Dump_Code ("free (indices);\n");
			HI_Dump_Code ("free (findices);\n");
			--HOOPS_WORLD->_hoops_ISPPR;
			HI_Dump_Code ("}\n");
		}
	);

	if (count == 0)
		return;  /* _hoops_CPRSH */

	if (count < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		return;
	}

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_PCGPP)) == null)
		return;

	if (_hoops_AISII (_hoops_IPRI, count, indices)) {
		Local_Face_Attributes *	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;
		if (_hoops_CPRI->findices == null)
			HI_Initialize_Face_Attributes (_hoops_IPRI, LFA_EXPLICIT_COLOR_BY_FINDEX);
		_hoops_ACGHR *	colors = _hoops_CPRI->findices;
		_hoops_GIIPR *	flags = _hoops_CPRI->_hoops_CHHPR();

		/* _hoops_RGSR _hoops_IRS _hoops_HSP _hoops_RIP _hoops_GPP _hoops_RGAR _hoops_HHH _hoops_IIGR _hoops_RH _hoops_RSSI, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IS _hoops_CCPP _hoops_PCCP _hoops_CRPR _hoops_IH _hoops_RH _hoops_SGI */
		if (count != _hoops_IPRI->face_count &&
			!BIT(_hoops_IPRI->local_face_attributes._hoops_SGRHR, LFA_EXPLICIT_COLOR_BY_FINDEX) &&
			!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
			ZALLOC_ARRAY(_hoops_CPRI->flags, _hoops_IPRI->face_count, _hoops_GIIPR);
			for (int i = 0; i < _hoops_IPRI->face_count; i++)
				_hoops_CPRI->flags[i] = *flags;
			_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
		}
		else {
			/* _hoops_RGSR _hoops_IRS _hoops_HSP _hoops_RIP _hoops_GPP _hoops_RCSAR _hoops_HSP, _hoops_HIS _hoops_RPP _hoops_SSIA _hoops_CHR _hoops_HCR _hoops_RH _hoops_PSHR, _hoops_SSIA _hoops_GRS _hoops_SGAGA _hoops_RH _hoops_PSHR.
				..._hoops_ISAP _hoops_IS _hoops_AA _hoops_ARI? */
		}


		do {
			int						index = *indices++;
			float					findex = *findices++;
			_hoops_GIIPR *		_hoops_PSSII;

			_hoops_PSSII = _hoops_IPRI->local_face_attributes._hoops_CHHPR(index);

			if (findex < -0.5f || findex >= ((float)_hoops_GPARA + 0.5f)) {
				char			buf[MAX_ERRMSG];
				float			max = ((float)_hoops_GPARA + 0.5f),
											min = -0.5f;

				HE_ERROR2 (HEC_COLOR_MAP, HES_OUT_OF_RANGE_COLOR_INDEX,
						   Sprintf_F (null, "Color index %f is out of range -", findex),
						   Sprintf_FF (buf, "must be between %f and %f", min, max));

				colors[index] = 0.0f;
			}
			else
				colors[index] = findex;

			/* (_hoops_AGCR _hoops_CSCII _hoops_CHR _hoops_SSAAA _hoops_IH _hoops_RH '_hoops_PSP _hoops_PGHC _hoops_RGSR' _hoops_AGIR)	 */
			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
				*_hoops_PSSII |= LFA_EXPLICIT_COLOR_BY_FINDEX;
				++_hoops_CPRI->_hoops_PSRRA;
				_hoops_IPRI->_hoops_ACRHR &= ~LFA_EXPLICIT_COLOR_BY_FINDEX;
			}
			else if (!ANYBIT (*_hoops_PSSII, _hoops_IACHR)) {
				*_hoops_PSSII |= LFA_EXPLICIT_COLOR_BY_FINDEX;
				++_hoops_CPRI->_hoops_PSRRA;
				_hoops_IPRI->_hoops_ACRHR &= ~LFA_EXPLICIT_COLOR_BY_FINDEX;
			}
			else if (BIT (*_hoops_PSSII, LFA_EXPLICIT_COLOR_BY_VALUE)) {
				*_hoops_PSSII &= ~LFA_EXPLICIT_COLOR_BY_VALUE;
				--_hoops_CPRI->_hoops_HSRRA;
				*_hoops_PSSII |= LFA_EXPLICIT_COLOR_BY_FINDEX;
				++_hoops_CPRI->_hoops_PSRRA;
				_hoops_IPRI->_hoops_ACRHR &= ~_hoops_IACHR;
			}
			*_hoops_PSSII |= _hoops_IGAHR;
		} _hoops_RGGA (--count == 0);

		_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;
		HI_Invalidate_Display_Lists (context, _hoops_IPRI);

		/* _hoops_RRRPR _hoops_IIGR _hoops_SPIGA _hoops_HHS _hoops_SHH _hoops_IRAP */
		if (_hoops_IPRI->owner) {
			if (!BIT (_hoops_IPRI->owner->_hoops_RCGC, _hoops_ASRRA))
				HI_Propagate_Maybes (context, _hoops_IPRI->owner, _hoops_ASRRA);
		}

		/* _hoops_HPCAR _hoops_IGSIP _hoops_HRGR _hoops_SIGR */
		_hoops_SASIR (context, (Geometry *)_hoops_IPRI, _hoops_GPSIR|_hoops_RPSIR);
	}

	_hoops_IRRPR();
#endif
#endif
}

HC_INTERFACE void HC_CDECL HC_MSet_Spec_Face_Col_By_Value (
	Key					key,
	int					count,
	int const *			indices,
	char const *		color_space,
	RGB const *			values)
{
	_hoops_PAPPR context("MSet_Specific_Face_Colors_By_Value");

#ifdef _hoops_GCGHR
	_hoops_IRPPR ("Geometry Colors");
#else
	CODE_GENERATION (
		int		count2 = count;
		if (count == 0) {
			HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Specific_Face_Colors_By_Value (LOOKUP (%D), ", key));
			HI_Dump_Code (Sprintf_S (null, "0, 0, %S, 0);\n", color_space));
		}
		else {
			HI_Dump_Code (Sprintf_D (null, "{int* indices = (int*) malloc(sizeof(int)*%d);\n", count2));
			HI_Dump_Code (Sprintf_D (null, "HC_RGB* values = (HC_RGB*) malloc(sizeof(HC_RGB)*%d);\n", count2));
			++HOOPS_WORLD->_hoops_ISPPR;
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (Sprintf_DD (null, "indices[%d].x = %d;\n", count2, indices[count2]));
				HI_Dump_Code (_hoops_CHCHR (null, "values[%d].red = %f;	 ", count2, values[count2].red));
				HI_Dump_Code (_hoops_CHCHR (null, "values[%d].green = %f;	 ", count2, values[count2].green));
				HI_Dump_Code (_hoops_CHCHR (null, "values[%d].blue = %f;\n", count2, values[count2].blue));
			}
			HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Specific_Face_Colors_By_Value (LOOKUP (%D), ", key));
			HI_Dump_Code (Sprintf_D (null, "%d, indices, ", count));
			HI_Dump_Code (Sprintf_S (null, "%S, values);\n", color_space));
			HI_Dump_Code ("free (indices);\n");
			HI_Dump_Code ("free (values);\n");
			--HOOPS_WORLD->_hoops_ISPPR;
			HI_Dump_Code ("}\n");
		}
	);


	if (count == 0)
		return;  /* _hoops_CPRSH */

	if (count < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		return;
	}

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_PCGPP)) == null)
		return;

	if (_hoops_AISII (_hoops_IPRI, count, indices)) {
		if (count < _hoops_IPRI->face_count && !BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
			/* _hoops_APSH _hoops_PII _hoops_SR _hoops_CHR _hoops_CPIC _hoops_IS _hoops_ARP _hoops_IRS _hoops_HSP _hoops_HAIR _hoops_GPP _hoops_IRS _hoops_GIIAR _hoops_IIGR _hoops_RH _hoops_RSSI, _hoops_PGAP _hoops_AGSR
			_hoops_SSIA _hoops_GRS _hoops_PSP _hoops_RPIP _hoops_HS _hoops_GHRHR _hoops_HSP _hoops_SGI, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IS _hoops_CCPP _hoops_IRS _hoops_HSSII->_hoops_SGI _hoops_CRPR */
			ZALLOC_ARRAY(_hoops_IPRI->local_face_attributes.flags, _hoops_IPRI->face_count, _hoops_GIIPR);
			for (int i = 0; i < _hoops_IPRI->face_count; i++)
				_hoops_IPRI->local_face_attributes.flags[i] = _hoops_IPRI->local_face_attributes._hoops_SGRHR;
			_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
		}

		if (_hoops_IPRI->local_face_attributes.colors == null)
			HI_Initialize_Face_Attributes (_hoops_IPRI, LFA_EXPLICIT_COLOR_BY_VALUE);

		RGB *				colors = _hoops_IPRI->local_face_attributes.colors;
		_hoops_GIIPR *	flags  = _hoops_IPRI->local_face_attributes._hoops_CHHPR();

		if ((color_space[0] == 'r' || color_space[0] == 'R') &&
			(color_space[1] == 'g' || color_space[1] == 'G') &&
			(color_space[2] == 'b' || color_space[2] == 'B')) {

			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
				if (!ANYBIT (*flags, _hoops_IACHR)) {
					*flags |= LFA_EXPLICIT_COLOR_BY_VALUE;
					_hoops_IPRI->local_face_attributes._hoops_HSRRA += count;
					_hoops_IPRI->_hoops_ACRHR &= ~LFA_EXPLICIT_COLOR_BY_VALUE;
				}
				else if (BIT (*flags, LFA_EXPLICIT_COLOR_BY_FINDEX)) {
					*flags &= ~LFA_EXPLICIT_COLOR_BY_FINDEX;
					_hoops_IPRI->local_face_attributes._hoops_PSRRA -= count;
					*flags |= LFA_EXPLICIT_COLOR_BY_VALUE;
					_hoops_IPRI->local_face_attributes._hoops_HSRRA += count;
					_hoops_IPRI->_hoops_ACRHR &= ~_hoops_IACHR;
				}
			}


			do {
				int				index = *indices++;
				_hoops_GIIPR *	_hoops_PSSII = _hoops_IPRI->local_face_attributes._hoops_CHHPR(index);

				colors[index] = _hoops_HGSII (*values);

				/* (_hoops_AGCR _hoops_CSCII _hoops_CHR _hoops_SSAAA _hoops_IH _hoops_RH '_hoops_PSP _hoops_PGHC _hoops_RGSR' _hoops_AGIR) */

				if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
					if (!ANYBIT (*_hoops_PSSII, _hoops_IACHR)) {
						*_hoops_PSSII |= LFA_EXPLICIT_COLOR_BY_VALUE;
						++_hoops_IPRI->local_face_attributes._hoops_HSRRA;
						_hoops_IPRI->_hoops_ACRHR &= ~LFA_EXPLICIT_COLOR_BY_VALUE;
					}
					else if (BIT (*_hoops_PSSII, LFA_EXPLICIT_COLOR_BY_FINDEX)) {
						*_hoops_PSSII &= ~LFA_EXPLICIT_COLOR_BY_FINDEX;
						--_hoops_IPRI->local_face_attributes._hoops_PSRRA;
						*_hoops_PSSII |= LFA_EXPLICIT_COLOR_BY_VALUE;
						++_hoops_IPRI->local_face_attributes._hoops_HSRRA;
						_hoops_IPRI->_hoops_ACRHR &= ~_hoops_IACHR;
					}
				}

				++values;
			} _hoops_RGGA (--count == 0);
		}
		else {
			_hoops_RHAH				_hoops_APHCR;
			Named_Material *		_hoops_HAA;

			if (!HI_Parse_Color_Map_By_Value (context, color_space, count, values, &_hoops_APHCR)) {
				goto Release;
			}

			_hoops_HAA = _hoops_APHCR._hoops_HAA;

			do {
				int					index = *indices++;
				_hoops_GIIPR	*_hoops_PSSII;

				_hoops_PSSII = _hoops_IPRI->local_face_attributes._hoops_CHHPR(index);

				colors[index].red	= _hoops_HAA->_hoops_CSHR.red;
				colors[index].green = _hoops_HAA->_hoops_CSHR.green;
				colors[index].blue  = _hoops_HAA->_hoops_CSHR.blue;

				/* (_hoops_AGCR _hoops_CSCII _hoops_CHR _hoops_SSAAA _hoops_IH _hoops_RH '_hoops_PSP _hoops_PGHC _hoops_RGSR' _hoops_AGIR) */

				if (!ANYBIT (*_hoops_PSSII, _hoops_IACHR)) {
					*_hoops_PSSII |= LFA_EXPLICIT_COLOR_BY_VALUE;
					++_hoops_IPRI->local_face_attributes._hoops_HSRRA;
					_hoops_IPRI->_hoops_ACRHR &= ~LFA_EXPLICIT_COLOR_BY_VALUE;
				}
				else if (!BIT (*_hoops_PSSII, LFA_EXPLICIT_COLOR_BY_VALUE)) {
					*_hoops_PSSII &= ~LFA_EXPLICIT_COLOR_BY_FINDEX;
					--_hoops_IPRI->local_face_attributes._hoops_PSRRA;
					*_hoops_PSSII |= LFA_EXPLICIT_COLOR_BY_VALUE;
					++_hoops_IPRI->local_face_attributes._hoops_HSRRA;
					_hoops_IPRI->_hoops_ACRHR &= ~_hoops_IACHR;
				}
				*_hoops_PSSII |= _hoops_IGAHR;

				++_hoops_HAA;
			} _hoops_RGGA (--count == 0);

			_hoops_HAA = _hoops_APHCR._hoops_HAA;
			HI_Free_Material_Names (_hoops_HAA, _hoops_APHCR.length);
			FREE_ARRAY (_hoops_HAA, _hoops_APHCR.length, Named_Material);
		}

		_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;
		HI_Invalidate_Display_Lists (context, _hoops_IPRI);

		/* _hoops_RRRPR _hoops_IIGR _hoops_SPIGA _hoops_HHS _hoops_SHH _hoops_IRAP */
		if (_hoops_IPRI->owner) {
			if (!BIT (_hoops_IPRI->owner->_hoops_RCGC, _hoops_ASRRA))
				HI_Propagate_Maybes (context, _hoops_IPRI->owner, _hoops_ASRRA);
		}

		/* _hoops_HPCAR _hoops_IGSIP _hoops_HRGR _hoops_SIGR */
		_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR|_hoops_RPSIR);
	}

  Release:
	_hoops_IRRPR();
#endif
}

HC_INTERFACE int HC_CDECL HC_MShow_Spec_Vert_Colors_W_Ex (
	Key							key,
	char const *				geometry,
	int							count,
	int const *					specific_vertices,
	char alter *				result_type,
	float alter *				index_colors,
	RGB alter *					rgb_colors,
	RGBA alter *				rgba_colors)
{
	_hoops_PAPPR context("MShow_Specific_Vertex_Colors_With_Existence");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return 0;
#else
#	ifdef _hoops_GCGHR
	_hoops_IRPPR ("Geometry COLORS");
	return 0;
#	else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Specific_Vertex_Colors_With_Existence () */\n");
	);

	int _hoops_IASII = _hoops_AASII(context, key, geometry, 0, count, specific_vertices, result_type,
		index_colors, rgb_colors, rgba_colors);

	return _hoops_IASII;
#	endif
#endif
}

HC_INTERFACE void HC_CDECL HC_MShow_Spec_Vert_Col_By_FInd (
	Key								key,
	char const *					geometry,
	int								count,
	int const *						indices,
	float alter *					findices)
{
	_hoops_PAPPR context("MShow_Specific_Vertex_Colors_By_FIndex");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#	ifdef _hoops_GCGHR
	_hoops_IRPPR ("Geometry Colors");
#	else
	CODE_GENERATION (
		HI_Dump_Code ("/* MShow_Specific_Vertex_Colors_By_FIndex () */\n");
	);

	int								_hoops_IASII = 0;
	char *							result_type;
	int								_hoops_HASII;

	ZALLOC_ARRAY_CACHED(result_type, count, char);
	_hoops_IASII = _hoops_AASII(context, key, geometry, 0, count, indices, result_type,
		findices, null, null, _hoops_GASII, &_hoops_HASII);

	//_hoops_RPP _hoops_SR'_hoops_RISP _hoops_AIAH _hoops_RHHS _hoops_PCCP _hoops_RIHH, _hoops_SAHR _hoops_CASI _hoops_GH _hoops_PPR _hoops_PHHR _hoops_RISII
	if (_hoops_HASII)
		goto Release;

	//_hoops_RARIR
	if (count != _hoops_IASII) {
		HE_ERROR (HEC_COLOR, HES_NO_LOCAL_SETTING,
				  "Not all requested vertex colors are explicitly set by index");
		goto Release;
	}

	for (int i=0; i<count; ++i) {
		if (result_type[i] != _hoops_IRSII) {
			HE_ERROR (HEC_COLOR, HES_NO_LOCAL_SETTING,
				  "Not all requested vertex colors are explicitly set by index");
			goto Release;
		}
	}

Release:
	FREE_ARRAY(result_type, count, char);
#	endif
#endif
}

HC_INTERFACE void HC_CDECL HC_MShow_Spec_Vert_Col_By_Value (
	Key					key,
	char const *		geometry,
	int					count,
	int const *			indices,
	RGB alter *			_hoops_ISSII)
{
	_hoops_PAPPR context("MShow_Specific_Vertex_Colors_By_Value");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#	ifdef _hoops_GCGHR
	_hoops_IRPPR ("Geometry COLORS");
#	else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Specific_Vertex_Colors_By_Value () */\n");
	);

	int								_hoops_IASII = 0;
	char *							result_type;
	int								_hoops_HASII;

	ZALLOC_ARRAY_CACHED(result_type, count, char);
	_hoops_IASII = _hoops_AASII(context, key, geometry, 0, count, indices, result_type,
		null, _hoops_ISSII, null, (_hoops_GASII|_hoops_RASII), &_hoops_HASII);

	//_hoops_RPP _hoops_SR'_hoops_RISP _hoops_AIAH _hoops_RHHS _hoops_PCCP _hoops_RIHH, _hoops_SAHR _hoops_CASI _hoops_GH _hoops_PPR _hoops_PHHR _hoops_RISII
	if (_hoops_HASII)
		goto Release;

	//_hoops_RARIR
	if (count != _hoops_IASII) {
		HE_ERROR (HEC_COLOR, HES_NO_LOCAL_SETTING,
				  "Not all requested vertex colors are explicitly set in the specified range");
		goto Release;
	}

	for (int i=0; i<count; ++i) {
		if (result_type[i] != _hoops_CRSII && result_type[i] != _hoops_SRSII) {
			HE_ERROR (HEC_COLOR, HES_NO_LOCAL_SETTING,
				  "Not all requested vertex colors are explicitly set in the specified range");
			goto Release;
		}
	}

Release:
	FREE_ARRAY(result_type, count, char);
#	endif
#endif
}

HC_INTERFACE void HC_CDECL HC_MShow_Spec_Face_Col_By_FInd (
	Key								key,
	int								count,
	int const *						indices,
	float alter *					findices)
{
	_hoops_PAPPR context("MShow_Specific_Face_Colors_By_FIndex");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#	ifdef _hoops_GCGHR
	_hoops_IRPPR ("Geometry Colors");
#	else
	CODE_GENERATION (
		HI_Dump_Code ("/* MShow_Specific_Face_Colors_By_FIndex () */\n");
	);

	int								_hoops_IASII = 0;
	char *							result_type;
	int								_hoops_HASII;

	ZALLOC_ARRAY_CACHED(result_type, count, char);
	_hoops_IASII = _hoops_CISII(context, key, 0, count, indices, result_type,
		findices, null, &_hoops_HASII);

	//_hoops_RPP _hoops_SR'_hoops_RISP _hoops_AIAH _hoops_RHHS _hoops_PCCP _hoops_RIHH, _hoops_SAHR _hoops_CASI _hoops_GH _hoops_PPR _hoops_PHHR _hoops_RISII
	if (_hoops_HASII)
		goto Release;

	//_hoops_RARIR
	if (count != _hoops_IASII) {
		HE_ERROR (HEC_COLOR, HES_NO_LOCAL_SETTING,
				  "Not all requested face colors are explicitly set by index");
		goto Release;
	}

	for (int i=0; i<count; ++i) {
		if (result_type[i] != _hoops_HISII) {
			HE_ERROR (HEC_COLOR, HES_NO_LOCAL_SETTING,
				  "Not all requested face colors are explicitly set by index");
			goto Release;
		}
	}

Release:
	FREE_ARRAY(result_type, count, char);
#	endif
#endif
}

HC_INTERFACE void HC_CDECL HC_MShow_Spec_Face_Col_By_Value (
	Key				key,
	int				count,
	int const *		indices,
	RGB alter *		rgb)
{
	_hoops_PAPPR context("MShow_Specific_Face_Colors_By_Value");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#	ifdef _hoops_GCGHR
	_hoops_IRPPR ("Geometry COLORS");
#	else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Specific_Face_Colors_By_Value () */\n");
	);

	int								_hoops_IASII = 0;
	char *							result_type;
	int								_hoops_HASII;

	ZALLOC_ARRAY_CACHED(result_type, count, char);
	_hoops_IASII = _hoops_CISII(context, key, 0, count, indices, result_type, null, rgb, &_hoops_HASII);

	//_hoops_RPP _hoops_SR'_hoops_RISP _hoops_AIAH _hoops_RHHS _hoops_PCCP _hoops_RIHH, _hoops_SAHR _hoops_CASI _hoops_GH _hoops_PPR _hoops_PHHR _hoops_RISII
	if (_hoops_HASII)
		goto Release;

	//_hoops_RARIR
	if (count != _hoops_IASII) {
		HE_ERROR (HEC_COLOR, HES_NO_LOCAL_SETTING, "Not all requested face colors are explicitly set in the specified range");
		goto Release;
	}

	for (int i=0; i<count; ++i) {
		if (result_type[i] != _hoops_IISII) {
			HE_ERROR (HEC_COLOR, HES_NO_LOCAL_SETTING, "Not all requested face colors are explicitly set in the specified range");
			goto Release;
		}
	}

Release:
	FREE_ARRAY(result_type, count, char);
#	endif
#endif
}

HC_INTERFACE int HC_CDECL HC_MShow_Spec_Face_Colors_W_Ex (
	Key					key,
	char const *		geometry,
	int					count,
	int const *			_hoops_SISII,
	char alter *		result_type,
	float alter *		index_colors,
	RGB alter *			rgb)
{
	_hoops_PAPPR context("MShow_Specific_Face_Colors_With_Existence");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return 0;
#else
#	ifdef _hoops_GCGHR
	_hoops_IRPPR ("Geometry COLORS");
	return 0;
#	else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Specific_Face_Colors_With_Existence () */\n");
	);

	UNREFERENCED(geometry);

	int	_hoops_IASII = _hoops_CISII(context, key, 0, count, _hoops_SISII, result_type, index_colors, rgb);

	return _hoops_IASII;

#	endif
#endif
}


local void _hoops_CSSII (
	_hoops_AIGPR *			_hoops_RIGC,
	Key								key,
	char const *					type,
	int								count,
	int const *						indices)
{

	if (count == 0)
		return;  /* _hoops_CPRSH */

	if (count < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		return;
	}

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(_hoops_RIGC, key, _hoops_ACGPP)) == null)
		return;

	ASSERT(_hoops_IPRI->type != _hoops_CSIP);

	Color_Object	_hoops_HSCII;
	_hoops_HCRPR			name;
	HI_Canonize_Chars (type, &name);
	char const *	_hoops_RPPA = name.text;
	if (!HI_Decipher_Color_Target (_hoops_RIGC, &_hoops_RPPA, _hoops_RPPA + name.length, true, &_hoops_HSCII, (Color_FACE|Color_EDGE|Color_VERTEX))) {
		_hoops_RGAIR (name);
		goto Release;
	}
	_hoops_RGAIR (name);

	if (ANYBIT (_hoops_HSCII, ~(Color_MARKER|Color_VERTEX|Color_EDGE|Color_FACE))) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_TYPE, "Only marker/vertex, edge, or face color may be shown");
		goto Release;
	}


	if (_hoops_PRSII (_hoops_IPRI, count, indices)) {
		float const *					_hoops_HAHIR = null;
		float const *					_hoops_HGHIR = null;
		float const *					_hoops_IGHIR = null;
		bool							_hoops_AHPGR = false;
		Local_Vertex_Flags				needed_flags = 0;

		if (ANYBIT (_hoops_HSCII, Color_MARKER|Color_VERTEX)) {
			_hoops_HAHIR = _hoops_IPRI->local_vertex_attributes._hoops_HAHIR;
			needed_flags |= _hoops_APPRA;
		}
		if (BIT (_hoops_HSCII, Color_EDGE)) {
			_hoops_HGHIR = _hoops_IPRI->local_vertex_attributes._hoops_HGHIR;
			needed_flags |= _hoops_PPPRA;
		}
		if (BIT (_hoops_HSCII, Color_FACE)) {
			_hoops_IGHIR = _hoops_IPRI->local_vertex_attributes._hoops_IGHIR;
			needed_flags |= _hoops_HPPRA;
		}

		if (_hoops_HAHIR == null && _hoops_HGHIR == null && _hoops_IGHIR == null)
			goto Release;

		{
			Local_Vertex_Attributes		*_hoops_SPRI;

			_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

			if ((_hoops_SPRI->flags == null && BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) ||
				(_hoops_SPRI->_hoops_SGRHR == 0 && !BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR))) {
					/* _hoops_ISAP _hoops_ARP _hoops_RPP _hoops_PSP _hoops_SGI, _hoops_HIS _hoops_SAHR _hoops_PSIIR & _hoops_CASI _hoops_GH */
					HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");
					goto Release;
			}


			if (count != _hoops_IPRI->point_count && !BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				/* _hoops_SR _hoops_CHR _hoops_HAR _hoops_RGSR _hoops_IRS _hoops_RIP _hoops_GPP _hoops_RCSAR _hoops_HSP, _hoops_HIS _hoops_RPP _hoops_IRS _hoops_SGI _hoops_CRPR _hoops_SSCP _hoops_HAR _hoops_GAPR
				_hoops_RPII _hoops_PSPP, _hoops_SR _hoops_RRP _hoops_IS _hoops_AA _hoops_SCH _hoops_HA */
				ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
				for (int i = 0; i < _hoops_IPRI->point_count; i++)
					_hoops_SPRI->flags[i] = _hoops_IPRI->local_vertex_attributes._hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
			}
			else if (count != _hoops_IPRI->point_count && BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				/* _hoops_RH '_hoops_SHISR' _hoops_PPRRR */
				do {
					int						index = *indices++;

					if (ANYBIT (*_hoops_SPRI->_hoops_CHHPR(index), needed_flags)) {
						if (BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_HCRRA & needed_flags)) {
							if (--_hoops_SPRI->_hoops_ICRRA == 0) {
								if (_hoops_SPRI->_hoops_PAHIR != _hoops_SPRI->ecolors && _hoops_SPRI->_hoops_PAHIR != _hoops_SPRI->fcolors)
									FREE_ARRAY (_hoops_SPRI->_hoops_PAHIR, _hoops_IPRI->point_count, RGB);
								_hoops_SPRI->_hoops_PAHIR = null;
							}
							else
								_hoops_SPRI->_hoops_PAHIR[index] = _hoops_GPSR::_hoops_RPSR;

							_hoops_IPRI->_hoops_AGRHR &= ~_hoops_HCRRA;
						}
						else if (BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_SIRRA & needed_flags)) {
							if (--_hoops_SPRI->_hoops_PCRRA == 0) {
								if (_hoops_SPRI->_hoops_HAHIR != _hoops_SPRI->_hoops_HGHIR && _hoops_SPRI->_hoops_HAHIR != _hoops_SPRI->_hoops_IGHIR)
									FREE_ARRAY (_hoops_SPRI->_hoops_HAHIR, _hoops_IPRI->point_count, _hoops_ACGHR);
								_hoops_SPRI->_hoops_HAHIR = null;
							}
							else
								_hoops_SPRI->_hoops_HAHIR[index] = 0.0f;

							_hoops_IPRI->_hoops_AGRHR &= ~_hoops_SIRRA;
						}

						if (BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_PPHPR & needed_flags)) {
							if (--_hoops_SPRI->_hoops_SCHPR == 0) {
								if (_hoops_SPRI->ecolors != _hoops_SPRI->_hoops_PAHIR && _hoops_SPRI->ecolors != _hoops_SPRI->fcolors)
									FREE_ARRAY (_hoops_SPRI->ecolors, _hoops_IPRI->point_count, RGB);
								_hoops_SPRI->ecolors = null;
							}
							else
								_hoops_SPRI->ecolors[index] = _hoops_GPSR::_hoops_RPSR;

							_hoops_IPRI->_hoops_RSHPR &= ~_hoops_HPHPR;
						}
						else if (BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_RPHPR & needed_flags)) {
							if (--_hoops_SPRI->_hoops_CCHPR == 0) {
								if (_hoops_SPRI->_hoops_HGHIR != _hoops_SPRI->_hoops_HAHIR && _hoops_SPRI->_hoops_HGHIR != _hoops_SPRI->_hoops_IGHIR)
									FREE_ARRAY (_hoops_SPRI->_hoops_HGHIR, _hoops_IPRI->point_count, _hoops_ACGHR);
								_hoops_SPRI->_hoops_HGHIR = null;
							}
							else
								_hoops_SPRI->_hoops_HGHIR[index] = 0.0f;

							_hoops_IPRI->_hoops_RSHPR &= ~_hoops_APHPR;
						}

						if (BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_AARHR & needed_flags)) {
							if (--_hoops_SPRI->_hoops_RCRHR == 0) {
								if (_hoops_SPRI->fcolors != _hoops_SPRI->_hoops_PAHIR && _hoops_SPRI->fcolors != _hoops_SPRI->ecolors)
									FREE_ARRAY (_hoops_SPRI->fcolors, _hoops_IPRI->point_count +
									_hoops_IPRI->_hoops_GCRHR, RGB);
								_hoops_SPRI->fcolors = null;
							}
							else
								_hoops_SPRI->fcolors[index] = _hoops_GPSR::_hoops_RPSR;

							_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PARHR;
						}
						else if (BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_HARHR & needed_flags)) {
							if (--_hoops_SPRI->_hoops_SIRHR == 0) {
								if (_hoops_SPRI->_hoops_IGHIR != _hoops_SPRI->_hoops_HAHIR && _hoops_SPRI->_hoops_IGHIR != _hoops_SPRI->_hoops_HGHIR)
									FREE_ARRAY (_hoops_SPRI->_hoops_IGHIR, _hoops_IPRI->point_count +
									_hoops_IPRI->_hoops_GCRHR, _hoops_ACGHR);
								_hoops_SPRI->_hoops_IGHIR = null;
							}
							else
								_hoops_SPRI->_hoops_IGHIR[index] = 0.0f;

							_hoops_IPRI->_hoops_ACRHR &= ~_hoops_IARHR;
							_hoops_IPRI->polyhedron_flags &= ~_hoops_SCRRA;
						}

						*_hoops_SPRI->_hoops_CHHPR(index) &= ~(_hoops_CPPRA & needed_flags);
					}
					else
						_hoops_AHPGR = true;
				} _hoops_RGGA (--count == 0);

				goto _hoops_SSSII;
			}
			else if (count == _hoops_IPRI->point_count) {
				/* _hoops_RPP _hoops_IIH _hoops_CHR _hoops_IGAPA _hoops_GGR _hoops_RH _hoops_HIGR, _hoops_SCH _hoops_HRGR _hoops_SSRR _hoops_SGS
				_hoops_RH _hoops_ISIA _hoops_CHR _hoops_SASPR _hoops_HIH _hoops_HAR _hoops_HCR _hoops_IIGR _hoops_RH _hoops_RSSI _hoops_CHR _hoops_IPPRA.
				_hoops_HIS _hoops_SR _hoops_PAH _hoops_HPPR _hoops_IS _hoops_ISPR _hoops_RH _hoops_HIGR _hoops_IIGR _hoops_PSPI, _hoops_PPR _hoops_RPP _hoops_SSIA _hoops_CHR
				_hoops_GGR _hoops_RGPSA _hoops_AGR _hoops_GCPAR _hoops_RCSAR _hoops_HSP _hoops_HRGR _hoops_IRARH _hoops_IPPRA, _hoops_SR _hoops_PAH _hoops_AA
				_hoops_ISCP _hoops_GGGCI _hoops_CHCRA.  _hoops_IAII _hoops_SR _hoops_GRS _hoops_CCPP _hoops_IRS
				_hoops_IHIR _hoops_CRPR _hoops_ARI.  _hoops_RGGCI _hoops_HCR _hoops_IIGR _hoops_RH _hoops_PSPI _hoops_AAPR _hoops_IGRC _hoops_IPPRA, _hoops_HIH _hoops_GGR
				_hoops_IRS _hoops_GRAA-_hoops_RGPSA _hoops_AGR, _hoops_SR _hoops_GRS _hoops_HS _hoops_PSPP _hoops_PCCP _hoops_CRPR, _hoops_PPR _hoops_PSCR
				_hoops_RHGCA _hoops_GH _hoops_CCA _hoops_IRS _hoops_GHRHR _hoops_CRPR, _hoops_HIS _hoops_SR _hoops_PAH _hoops_ISPR _hoops_IH _hoops_SGS _hoops_PPR _hoops_CIH
				_hoops_RH _hoops_CRPR.  _hoops_PHGP _hoops_RH _hoops_CHCRA _hoops_IH _hoops_SSHSR _hoops_IS _hoops_SRCH _hoops_RGR _hoops_CCRSA _hoops_PPR _hoops_CIH
				_hoops_HRGR _hoops_IS _hoops_RSPC _hoops_IRS _hoops_RGPSA _hoops_HIGR _hoops_IIGR _hoops_PSPI */

				bool _hoops_GSSII = true;

				for (int i = 0; i < count; i++) {
					if (i != indices[i]) {
						_hoops_GSSII = false;
						break;
					}
				}

				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR) && _hoops_GSSII) {
					int						index = *indices++;

					if (ANYBIT (*_hoops_SPRI->_hoops_CHHPR(index), needed_flags)) {
						if (BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_HCRRA & needed_flags)) {
							if ((_hoops_SPRI->_hoops_ICRRA -= count) == 0) {
								if (_hoops_SPRI->_hoops_PAHIR != _hoops_SPRI->ecolors && _hoops_SPRI->_hoops_PAHIR != _hoops_SPRI->fcolors)
									FREE_ARRAY (_hoops_SPRI->_hoops_PAHIR, _hoops_IPRI->point_count, RGB);
								_hoops_SPRI->_hoops_PAHIR = null;
							}
							else
								_hoops_SPRI->_hoops_PAHIR[index] = _hoops_GPSR::_hoops_RPSR;

							_hoops_IPRI->_hoops_AGRHR &= ~_hoops_HCRRA;
						}
						else if (BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_SIRRA & needed_flags)) {
							if ((_hoops_SPRI->_hoops_PCRRA -= count) == 0) {
								if (_hoops_SPRI->_hoops_HAHIR != _hoops_SPRI->_hoops_HGHIR && _hoops_SPRI->_hoops_HAHIR != _hoops_SPRI->_hoops_IGHIR)
									FREE_ARRAY (_hoops_SPRI->_hoops_HAHIR, _hoops_IPRI->point_count, _hoops_ACGHR);
								_hoops_SPRI->_hoops_HAHIR = null;
							}
							else
								_hoops_SPRI->_hoops_HAHIR[index] = 0.0f;

							_hoops_IPRI->_hoops_AGRHR &= ~_hoops_SIRRA;
						}

						if (BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_PPHPR & needed_flags)) {
							if ((_hoops_SPRI->_hoops_SCHPR -= count) == 0) {
								if (_hoops_SPRI->ecolors != _hoops_SPRI->_hoops_PAHIR && _hoops_SPRI->ecolors != _hoops_SPRI->fcolors)
									FREE_ARRAY (_hoops_SPRI->ecolors, _hoops_IPRI->point_count, RGB);
								_hoops_SPRI->ecolors = null;
							}
							else
								_hoops_SPRI->ecolors[index] = _hoops_GPSR::_hoops_RPSR;

							_hoops_IPRI->_hoops_RSHPR &= ~_hoops_HPHPR;
						}
						else if (BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_RPHPR & needed_flags)) {
							if ((_hoops_SPRI->_hoops_CCHPR -= count) == 0) {
								if (_hoops_SPRI->_hoops_HGHIR != _hoops_SPRI->_hoops_HAHIR && _hoops_SPRI->_hoops_HGHIR != _hoops_SPRI->_hoops_IGHIR)
									FREE_ARRAY (_hoops_SPRI->_hoops_HGHIR, _hoops_IPRI->point_count, _hoops_ACGHR);
								_hoops_SPRI->_hoops_HGHIR = null;
							}
							else
								_hoops_SPRI->_hoops_HGHIR[index] = 0.0f;

							_hoops_IPRI->_hoops_RSHPR &= ~_hoops_APHPR;
						}

						if (BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_AARHR & needed_flags)) {
							if ((_hoops_SPRI->_hoops_RCRHR -= count) == 0) {
								if (_hoops_SPRI->fcolors != _hoops_SPRI->_hoops_PAHIR && _hoops_SPRI->fcolors != _hoops_SPRI->ecolors)
									FREE_ARRAY (_hoops_SPRI->fcolors, _hoops_IPRI->point_count +
									_hoops_IPRI->_hoops_GCRHR, RGB);
								_hoops_SPRI->fcolors = null;
							}
							else
								_hoops_SPRI->fcolors[index] = _hoops_GPSR::_hoops_RPSR;

							_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PARHR;
						}
						else if (BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_HARHR & needed_flags)) {
							if ((_hoops_SPRI->_hoops_SIRHR -= count) == 0) {
								if (_hoops_SPRI->_hoops_IGHIR != _hoops_SPRI->_hoops_HAHIR && _hoops_SPRI->_hoops_IGHIR != _hoops_SPRI->_hoops_HGHIR)
									FREE_ARRAY (_hoops_SPRI->_hoops_IGHIR, _hoops_IPRI->point_count +
									_hoops_IPRI->_hoops_GCRHR, _hoops_ACGHR);
								_hoops_SPRI->_hoops_IGHIR = null;
							}
							else
								_hoops_SPRI->_hoops_IGHIR[index] = 0.0f;

							_hoops_IPRI->_hoops_ACRHR &= ~_hoops_IARHR;
							_hoops_IPRI->polyhedron_flags &= ~_hoops_SCRRA;
						}

						*_hoops_SPRI->_hoops_CHHPR(index) &= ~needed_flags;
					}
					else
						_hoops_AHPGR = true;

					goto Release;
				}
				else if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
					/* _hoops_RRP _hoops_IS _hoops_CCPP _hoops_SGI _hoops_CRPR, _hoops_PPR _hoops_PSCR _hoops_HII _hoops_ARI _hoops_GPP _hoops_SR'_hoops_GCPP _hoops_IPHR _hoops_CCA _hoops_IHIR _hoops_CRPR */
					ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
					for (int i = 0; i < _hoops_IPRI->point_count; i++)
						_hoops_SPRI->flags[i] = _hoops_IPRI->local_vertex_attributes._hoops_SGRHR;
					_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
				}

				do {
					int						index = *indices++;

					if (ANYBIT (*_hoops_SPRI->_hoops_CHHPR(index), needed_flags)) {
						if (BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_HCRRA & needed_flags)) {
							if (--_hoops_SPRI->_hoops_ICRRA == 0) {
								if (_hoops_SPRI->_hoops_PAHIR != _hoops_SPRI->ecolors && _hoops_SPRI->_hoops_PAHIR != _hoops_SPRI->fcolors)
									FREE_ARRAY (_hoops_SPRI->_hoops_PAHIR, _hoops_IPRI->point_count, RGB);
								_hoops_SPRI->_hoops_PAHIR = null;
							}
							else
								_hoops_SPRI->_hoops_PAHIR[index] = _hoops_GPSR::_hoops_RPSR;

							_hoops_IPRI->_hoops_AGRHR &= ~_hoops_HCRRA;
						}
						else if (BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_SIRRA & needed_flags)) {
							if (--_hoops_SPRI->_hoops_PCRRA == 0) {
								if (_hoops_SPRI->_hoops_HAHIR != _hoops_SPRI->_hoops_HGHIR && _hoops_SPRI->_hoops_HAHIR != _hoops_SPRI->_hoops_IGHIR)
									FREE_ARRAY (_hoops_SPRI->_hoops_HAHIR, _hoops_IPRI->point_count, _hoops_ACGHR);
								_hoops_SPRI->_hoops_HAHIR = null;
							}
							else
								_hoops_SPRI->_hoops_HAHIR[index] = 0.0f;

							_hoops_IPRI->_hoops_AGRHR &= ~_hoops_SIRRA;
						}

						if (BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_PPHPR & needed_flags)) {
							if (--_hoops_SPRI->_hoops_SCHPR == 0) {
								if (_hoops_SPRI->ecolors != _hoops_SPRI->_hoops_PAHIR && _hoops_SPRI->ecolors != _hoops_SPRI->fcolors)
									FREE_ARRAY (_hoops_SPRI->ecolors, _hoops_IPRI->point_count, RGB);
								_hoops_SPRI->ecolors = null;
							}
							else
								_hoops_SPRI->ecolors[index] = _hoops_GPSR::_hoops_RPSR;

							_hoops_IPRI->_hoops_RSHPR &= ~_hoops_HPHPR;
						}
						else if (BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_RPHPR & needed_flags)) {
							if (--_hoops_SPRI->_hoops_CCHPR == 0) {
								if (_hoops_SPRI->_hoops_HGHIR != _hoops_SPRI->_hoops_HAHIR && _hoops_SPRI->_hoops_HGHIR != _hoops_SPRI->_hoops_IGHIR)
									FREE_ARRAY (_hoops_SPRI->_hoops_HGHIR, _hoops_IPRI->point_count, _hoops_ACGHR);
								_hoops_SPRI->_hoops_HGHIR = null;
							}
							else
								_hoops_SPRI->_hoops_HGHIR[index] = 0.0f;

							_hoops_IPRI->_hoops_RSHPR &= ~_hoops_APHPR;
						}

						if (BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_AARHR & needed_flags)) {
							if (--_hoops_SPRI->_hoops_RCRHR == 0) {
								if (_hoops_SPRI->fcolors != _hoops_SPRI->_hoops_PAHIR && _hoops_SPRI->fcolors != _hoops_SPRI->ecolors)
									FREE_ARRAY (_hoops_SPRI->fcolors, _hoops_IPRI->point_count +
									_hoops_IPRI->_hoops_GCRHR, RGB);
								_hoops_SPRI->fcolors = null;
							}
							else
								_hoops_SPRI->fcolors[index] = _hoops_GPSR::_hoops_RPSR;

							_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PARHR;
						}
						else if (BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_HARHR & needed_flags)) {
							if (--_hoops_SPRI->_hoops_SIRHR == 0) {
								if (_hoops_SPRI->_hoops_IGHIR != _hoops_SPRI->_hoops_HAHIR && _hoops_SPRI->_hoops_IGHIR != _hoops_SPRI->_hoops_HGHIR)
									FREE_ARRAY (_hoops_SPRI->_hoops_IGHIR, _hoops_IPRI->point_count +
									_hoops_IPRI->_hoops_GCRHR, _hoops_ACGHR);
								_hoops_SPRI->_hoops_IGHIR = null;
							}
							else
								_hoops_SPRI->_hoops_IGHIR[index] = 0.0f;

							_hoops_IPRI->_hoops_ACRHR &= ~_hoops_IARHR;
							_hoops_IPRI->polyhedron_flags &= ~_hoops_SCRRA;
						}

						*_hoops_SPRI->_hoops_CHHPR(index) &= ~needed_flags;
					}
					else
						_hoops_AHPGR = true;
				} _hoops_RGGA (--count == 0);

			}

_hoops_SSSII:

			/* _hoops_CGSI _hoops_CGH _hoops_HCR _hoops_SHH _hoops_ARP _hoops_HA. */
			/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_ISSC _hoops_IS _hoops_IRS _hoops_PIAP _hoops_CAS _hoops_RH _hoops_SGI _hoops_CHR _hoops_GHRHR, _hoops_SR _hoops_GHCA _hoops_RRP _hoops_IS _hoops_CIH _hoops_RH _hoops_SGI _hoops_CRPR */
			if (/*!_hoops_IRRC (_hoops_CPHAR->_hoops_PHRHR, _hoops_PCSII) &&*/
				BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR) &&
				_hoops_SPRI->lvf_uniform(_hoops_IPRI->point_count)) {
					_hoops_SPRI->_hoops_SGRHR = _hoops_SPRI->flags[0];
					FREE_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
					_hoops_SPRI->flags = null;
					_hoops_IPRI->polyhedron_flags &= ~_hoops_CGRHR;
			}
		}

		if (_hoops_AHPGR)
			HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");

		_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_GGARA|_hoops_RPSIR);
		HI_Invalidate_Display_Lists (_hoops_RIGC, _hoops_IPRI);
	}

Release:
	_hoops_IRRPR();
}

HC_INTERFACE void HC_CDECL HC_MUnSet_Spec_Vertex_Colors2 (
	Key						key,
	char const *			type,
	int						count,
	int const *				indices)
{
	_hoops_PAPPR context("MUnSet_Specific_Vertex_Colors2");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else

	CODE_GENERATION (
		int		count2 = count;
		if (count == 0) {
			HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Specific_Vertex_Colors2 (LOOKUP (%D), 0, 0);\n", key));
		}
		else {
			HI_Dump_Code (Sprintf_D (null, "{int* indices = (int*) malloc(sizeof(int)*%d);\n", count2));
			++HOOPS_WORLD->_hoops_ISPPR;
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (Sprintf_DD (null, "indices[%d].x = %d;\n", count2, indices[count2]));
			}
			HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Specific_Vertex_Colors2 (LOOKUP (%D), ", key));
			HI_Dump_Code (Sprintf_SD (null, "%S, %d, indices);\n", type, count));
			HI_Dump_Code ("free (indices);\n");
			--HOOPS_WORLD->_hoops_ISPPR;
			HI_Dump_Code ("}\n");
		}
	);

	_hoops_CSSII(context, key, type, count, indices);
#endif
}


HC_INTERFACE void HC_CDECL HC_MUnSet_Spec_Vertex_Colors (
	Key						key,
	int						count,
	int const *				indices)
{
	_hoops_PAPPR context("MUnSet_Specific_Vertex_Colors");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else

	CODE_GENERATION (
		int		count2 = count;
		if (count == 0) {
			HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Specific_Vertex_Colors (LOOKUP (%D), 0, 0);\n", key));
		}
		else {
			HI_Dump_Code (Sprintf_D (null, "{int* indices = (int*) malloc(sizeof(int)*%d);\n", count2));
			++HOOPS_WORLD->_hoops_ISPPR;
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (Sprintf_DD (null, "indices[%d].x = %d;\n", count2, indices[count2]));
			}
			HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Specific_Vertex_Colors (LOOKUP (%D), ", key));
			HI_Dump_Code (Sprintf_D (null, "%d, indices);\n", count));
			HI_Dump_Code ("free (indices);\n");
			--HOOPS_WORLD->_hoops_ISPPR;
			HI_Dump_Code ("}\n");
		}
	);

	_hoops_CSSII(context, key, "faces, edges, vertex", count, indices);
#endif
}

HC_INTERFACE void HC_CDECL HC_MUnSet_Spec_Face_Colors (
	Key							key,
	int							count,
	int const *					indices)
{
	_hoops_PAPPR context("MUnSet_Specific_Face_Colors");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else

	CODE_GENERATION (
		int		count2 = count;
		if (count == 0) {
			HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Specific_Face_Colors (LOOKUP (%D), 0, 0);\n", key));
		}
		else {
			HI_Dump_Code (Sprintf_D (null, "{int* indices = (int*) malloc(sizeof(int)*%d);\n", count2));
			++HOOPS_WORLD->_hoops_ISPPR;
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (Sprintf_DD (null, "indices[%d].x = %d;\n", count2, indices[count2]));
			}
			HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Specific_Face_Colors (LOOKUP (%D), ", key));
			HI_Dump_Code (Sprintf_D (null, "%d, indices);\n", count));
			HI_Dump_Code ("free (indices);\n");
			--HOOPS_WORLD->_hoops_ISPPR;
			HI_Dump_Code ("}\n");
		}
	);

	if (count == 0)
		return;  /* _hoops_CPRSH */

	if (count < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		return;
	}

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_PCGPP)) == null)
		return;

	if (_hoops_AISII (_hoops_IPRI, count, indices)) {
		bool						_hoops_AHPGR = false;
		Local_Face_Attributes *		_hoops_CPRI = &_hoops_IPRI->local_face_attributes;

		if ((_hoops_CPRI->flags == null && BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) ||
			(_hoops_CPRI->_hoops_SGRHR == 0 && !BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR))) {
			/* _hoops_ISAP _hoops_ARP _hoops_RPP _hoops_PSP _hoops_SGI, _hoops_HIS _hoops_SAHR _hoops_PSIIR & _hoops_CASI _hoops_GH */
			HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");
			goto Release;
		}

		if (count != _hoops_IPRI->face_count && !BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
			/* _hoops_SR _hoops_CHR _hoops_HAR _hoops_RGSR _hoops_IRS _hoops_RIP _hoops_GPP _hoops_RCSAR _hoops_HSP, _hoops_HIS _hoops_RPP _hoops_IRS _hoops_SGI _hoops_CRPR _hoops_SSCP _hoops_HAR _hoops_GAPR
			_hoops_RPII _hoops_PSPP, _hoops_SR _hoops_RRP _hoops_IS _hoops_AA _hoops_SCH _hoops_HA */
			ZALLOC_ARRAY(_hoops_CPRI->flags, _hoops_IPRI->face_count, _hoops_GIIPR);
			for (int i = 0; i < _hoops_IPRI->face_count; i++)
				_hoops_CPRI->flags[i] = _hoops_IPRI->local_face_attributes._hoops_SGRHR;
			_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
		}
		else if (count != _hoops_IPRI->face_count && BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
			/* _hoops_RH '_hoops_SHISR' _hoops_PPRRR */
			do {
				int						index = *indices++;
				_hoops_GIIPR		*_hoops_PSSII = _hoops_CPRI->_hoops_CHHPR(index);

				if (BIT (*_hoops_PSSII, LFA_EXPLICIT_COLOR_BY_FINDEX)) {
					if (--_hoops_CPRI->_hoops_PSRRA == 0) {
						FREE_ARRAY (_hoops_CPRI->findices, _hoops_IPRI->face_count, _hoops_ACGHR);
						_hoops_CPRI->findices = null;
					}
					else
						_hoops_CPRI->findices[index] = 0.0f;
				}
				else if (BIT (*_hoops_PSSII, LFA_EXPLICIT_COLOR_BY_VALUE)) {
					if (--_hoops_CPRI->_hoops_HSRRA == 0) {
						FREE_ARRAY (_hoops_CPRI->colors, _hoops_IPRI->face_count, RGB);
						_hoops_CPRI->colors = null;
					}
					else
						_hoops_CPRI->colors[index] = _hoops_GPSR::_hoops_RPSR;
				}
				else
					_hoops_AHPGR = true;

				*_hoops_PSSII &= ~(LFA_EXPLICIT_COLOR_BY_FINDEX|LFA_EXPLICIT_COLOR_BY_VALUE);
				*_hoops_PSSII |= _hoops_IGAHR;
			} while (--count > 0);

			goto _hoops_SSSII;
		}
		else if (count == _hoops_IPRI->face_count) {
			/* _hoops_RPP _hoops_IIH _hoops_CHR _hoops_IGAPA _hoops_GGR _hoops_RH _hoops_HIGR, _hoops_SCH _hoops_HRGR _hoops_SSRR _hoops_SGS
			   _hoops_RH _hoops_ISIA _hoops_CHR _hoops_SASPR _hoops_HIH _hoops_HAR _hoops_HCR _hoops_IIGR _hoops_RH _hoops_RSSI _hoops_CHR _hoops_IPPRA.
			   _hoops_HIS _hoops_SR _hoops_PAH _hoops_HPPR _hoops_IS _hoops_ISPR _hoops_RH _hoops_HIGR _hoops_IIGR _hoops_PSPI, _hoops_PPR _hoops_RPP _hoops_SSIA _hoops_CHR
			   _hoops_GGR _hoops_RGPSA _hoops_AGR _hoops_GCPAR _hoops_RCSAR _hoops_HSP _hoops_HRGR _hoops_IRARH _hoops_IPPRA, _hoops_SR _hoops_PAH _hoops_AA
			   _hoops_ISCP _hoops_GGGCI _hoops_CHCRA.  _hoops_IAII _hoops_SR _hoops_GRS _hoops_CCPP _hoops_IRS
			   _hoops_IHIR _hoops_CRPR _hoops_ARI.  _hoops_RGGCI _hoops_HCR _hoops_IIGR _hoops_RH _hoops_PSPI _hoops_AAPR _hoops_IGRC _hoops_IPPRA, _hoops_HIH _hoops_GGR
			   _hoops_IRS _hoops_GRAA-_hoops_RGPSA _hoops_AGR, _hoops_SR _hoops_GRS _hoops_HS _hoops_PSPP _hoops_PCCP _hoops_CRPR, _hoops_PPR _hoops_PSCR
			   _hoops_RHGCA _hoops_GH _hoops_CCA _hoops_IRS _hoops_GHRHR _hoops_CRPR, _hoops_HIS _hoops_SR _hoops_PAH _hoops_ISPR _hoops_IH _hoops_SGS _hoops_PPR _hoops_CIH
			   _hoops_RH _hoops_CRPR.  _hoops_PHGP _hoops_RH _hoops_CHCRA _hoops_IH _hoops_SSHSR _hoops_IS _hoops_SRCH _hoops_RGR _hoops_CCRSA _hoops_PPR _hoops_CIH
			   _hoops_HRGR _hoops_IS _hoops_RSPC _hoops_IRS _hoops_RGPSA _hoops_HIGR _hoops_IIGR _hoops_PSPI */

			bool _hoops_GSSII = true;

			for (int i = 0; i < count; i++) {
				if (i != indices[i]) {
					_hoops_GSSII = false;
					break;
				}
			}

			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR) && _hoops_GSSII) {
				int						index = *indices++;
				_hoops_GIIPR		*_hoops_PSSII = &_hoops_CPRI->_hoops_SGRHR;

				if (BIT (*_hoops_PSSII, LFA_EXPLICIT_COLOR_BY_FINDEX)) {
					if ((_hoops_CPRI->_hoops_PSRRA -= count) == 0) {
						FREE_ARRAY (_hoops_CPRI->findices, _hoops_IPRI->face_count, _hoops_ACGHR);
						_hoops_CPRI->findices = null;
					}
					else
						_hoops_CPRI->findices[index] = 0.0f;
				}
				else if (BIT (*_hoops_PSSII, LFA_EXPLICIT_COLOR_BY_VALUE)) {
					if ((_hoops_CPRI->_hoops_HSRRA -= count) == 0) {
						FREE_ARRAY (_hoops_CPRI->colors, _hoops_IPRI->face_count, RGB);
						_hoops_CPRI->colors = null;
					}
					else
						_hoops_CPRI->colors[index] = _hoops_GPSR::_hoops_RPSR;
				}
				else
					_hoops_AHPGR = true;

				*_hoops_PSSII &= ~(LFA_EXPLICIT_COLOR_BY_FINDEX|LFA_EXPLICIT_COLOR_BY_VALUE);
				*_hoops_PSSII |= _hoops_IGAHR;

				goto Release;
			}
			else if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
				/* _hoops_RRP _hoops_IS _hoops_CCPP _hoops_SGI _hoops_CRPR, _hoops_PPR _hoops_PSCR _hoops_HII _hoops_ARI _hoops_GPP _hoops_SR'_hoops_GCPP _hoops_IPHR _hoops_CCA _hoops_IHIR _hoops_CRPR */
				ZALLOC_ARRAY(_hoops_CPRI->flags, _hoops_IPRI->face_count, _hoops_GIIPR);
				for (int i = 0; i < _hoops_IPRI->face_count; i++)
					_hoops_CPRI->flags[i] = _hoops_IPRI->local_face_attributes._hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
			}

			do {
				int						index = *indices++;
				_hoops_GIIPR		*_hoops_PSSII = _hoops_CPRI->_hoops_CHHPR(index);

				if (BIT (*_hoops_PSSII, LFA_EXPLICIT_COLOR_BY_FINDEX)) {
					if (--_hoops_CPRI->_hoops_PSRRA == 0) {
						FREE_ARRAY (_hoops_CPRI->findices, _hoops_IPRI->face_count, _hoops_ACGHR);
						_hoops_CPRI->findices = null;
					}
					else
						_hoops_CPRI->findices[index] = 0.0f;
				}
				else if (BIT (*_hoops_PSSII, LFA_EXPLICIT_COLOR_BY_VALUE)) {
					if (--_hoops_CPRI->_hoops_HSRRA == 0) {
						FREE_ARRAY (_hoops_CPRI->colors, _hoops_IPRI->face_count, RGB);
						_hoops_CPRI->colors = null;
					}
					else
						_hoops_CPRI->colors[index] = _hoops_GPSR::_hoops_RPSR;
				}
				else
					_hoops_AHPGR = true;

				*_hoops_PSSII &= ~(LFA_EXPLICIT_COLOR_BY_FINDEX|LFA_EXPLICIT_COLOR_BY_VALUE);
				*_hoops_PSSII |= _hoops_IGAHR;
			} while (--count > 0);
		}

	  _hoops_SSSII:

		/* _hoops_CGSI _hoops_CGH _hoops_HCR _hoops_SHH _hoops_ARP _hoops_HA. */
		/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_ISSC _hoops_IS _hoops_IRS _hoops_PIAP _hoops_CAS _hoops_RH _hoops_SGI _hoops_CHR _hoops_GHRHR, _hoops_SR _hoops_GHCA _hoops_RRP _hoops_IS _hoops_CIH _hoops_RH _hoops_SGI _hoops_CRPR */
		if (/*!_hoops_IRRC (_hoops_CPHAR->_hoops_PHRHR, _hoops_PCSII) &&*/
			BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR) &&
			_hoops_CPRI->lff_uniform(_hoops_IPRI->face_count)) {
			_hoops_CPRI->_hoops_SGRHR = _hoops_CPRI->flags[0];
			FREE_ARRAY(_hoops_IPRI->local_face_attributes.flags, _hoops_IPRI->face_count, _hoops_GIIPR);
			_hoops_IPRI->polyhedron_flags &= ~_hoops_APRHR;
			_hoops_CPRI->flags = null;
		}


		if (_hoops_AHPGR)
			HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");

		if (_hoops_IPRI->tristrips != null) {
			HI_Invalidate_Display_Lists (context, _hoops_IPRI);
			_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;
			_hoops_SASIR (context, _hoops_IPRI, _hoops_IHSSR | _hoops_SIGPR);
		}
	}

  Release:
	_hoops_IRRPR();
#endif
}



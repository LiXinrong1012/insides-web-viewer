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
 * $Id: obf_tmp.txt 1.109 2010-10-05 19:46:31 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hd_proto.h"
#include "phdraw.h"
#include "hi_proto.h"
#include "hpserror.h"



local void _hoops_CPHPR (
	Shell *						_hoops_SPHPR) {
	int *						item;
	Local_Vertex_Flags			_hoops_IRRHR;
	int *						_hoops_CRRHR;
	_hoops_SRRHR *	_hoops_GARHR;
	Local_Vertex_Flags *		_hoops_SAHPR;
	Local_Vertex_Attributes *	_hoops_SPRI;

	/*
	 * _hoops_IH _hoops_GRR _hoops_HSP, _hoops_RARHR _hoops_RH _hoops_SGI _hoops_IIGR _hoops_RH _hoops_PSHS _hoops_GIHA,
	 * _hoops_PSCR _hoops_ARP _hoops_RH _hoops_HSP _hoops_RHCP-_hoops_CSSGR _hoops_SGI _hoops_IAR.
	 */

	_hoops_SPRI = &_hoops_SPHPR->local_vertex_attributes;
	_hoops_SAHPR = _hoops_SPHPR->local_vertex_attributes._hoops_CHHPR();
	_hoops_GARHR = _hoops_SPHPR->local_face_attributes._hoops_GARHR;
	item = _hoops_SPHPR->face_list;

	if ((item = _hoops_SPHPR->face_list) == null) {
		Tristrip const *				ts;

		if ((ts = _hoops_SPHPR->tristrips) != null) {
			int							face = -1;

			do {
				int						_hoops_PHHA = ts->_hoops_PHHA;
				int *					lengths = ts->lengths;
				int *					vi = ts->_hoops_AIHA;
				int *					fi = ts->face_indices;

				while (_hoops_PHHA-- > 0) {
					int					length = *lengths++;

					if (length < 0)
						length = -length;
					length -= 2;

					if (fi) {
						fi += 2;
						face = *fi++;
					}
					else
						face++;
					_hoops_GARHR = ((Shell*)_hoops_SPHPR)->local_face_attributes._hoops_GARHR;

					_hoops_IRRHR = *_hoops_SPRI->_hoops_CHHPR(*vi++);
					if (BIT (_hoops_IRRHR, _hoops_AARHR))
						*_hoops_GARHR |= _hoops_PARHR;
					else if (BIT (_hoops_IRRHR, _hoops_HARHR))
						*_hoops_GARHR |= _hoops_IARHR;
					else
						*_hoops_GARHR |= _hoops_CARHR;

					_hoops_IRRHR = *_hoops_SPRI->_hoops_CHHPR(*vi++);
					if (BIT (_hoops_IRRHR, _hoops_AARHR))
						*_hoops_GARHR |= _hoops_PARHR;
					else if (BIT (_hoops_IRRHR, _hoops_HARHR))
						*_hoops_GARHR |= _hoops_IARHR;
					else
						*_hoops_GARHR |= _hoops_CARHR;

					while (length-- > 0) {
						_hoops_IRRHR = *_hoops_SPRI->_hoops_CHHPR(*vi++);
						if (fi)
							face = *fi++;
						else
							face++;
						_hoops_GARHR = ((Shell*)_hoops_SPHPR)->local_face_attributes._hoops_GARHR;
						if (BIT (_hoops_IRRHR, _hoops_AARHR))
							*_hoops_GARHR |= _hoops_PARHR;
						else if (BIT (_hoops_IRRHR, _hoops_HARHR))
							*_hoops_GARHR |= _hoops_IARHR;
						else
							*_hoops_GARHR |= _hoops_CARHR;
					}
				}
			} while ((ts = ts->next) != null);
		}
	}
	else {
		int						*end, face_count = 0;
		_hoops_SARHR	_hoops_GPRHR = 0;

		end = item + _hoops_SPHPR->face_list_length;

		do {
			_hoops_GPRHR = 0;
			if (*item++ >= 0) { /* _hoops_GSSR _hoops_RPRHR _hoops_HSP */
				if (BIT(_hoops_SPHPR->polyhedron_flags, _hoops_APRHR))
					*_hoops_GARHR &= ~_hoops_PPRHR;
				_hoops_CRRHR = item + item[-1];
			}
			else {				/* '_hoops_HHHR' _hoops_HSP == _hoops_IRS _hoops_RCCPR _hoops_GGR _hoops_RH _hoops_CGHI _hoops_HSP */
				_hoops_CRRHR = item - item[-1];
				if (BIT(_hoops_SPHPR->polyhedron_flags, _hoops_APRHR))
					--_hoops_GARHR;
			}

			if (item != _hoops_CRRHR) do {
				_hoops_IRRHR = *_hoops_SPRI->_hoops_CHHPR(*item);

				if (BIT (_hoops_IRRHR, _hoops_AARHR))
					/**_hoops_HPRHR |= _hoops_IPRHR;*/
					_hoops_GPRHR |= _hoops_PARHR;
				else if (BIT (_hoops_IRRHR, _hoops_HARHR))
					/**_hoops_HPRHR |= _hoops_CPRHR;*/
					_hoops_GPRHR |= _hoops_IARHR;
				else
					/**_hoops_HPRHR |= _hoops_SPRHR;*/
					_hoops_GPRHR |= _hoops_CARHR;

#if 0
				if (!BIT(_hoops_SPHPR->polyhedron_flags, _hoops_APRHR)) {
					/* _hoops_PRRAR _hoops_SAHR _hoops_GRP _hoops_SPR _hoops_GHRHR _hoops_RIP _hoops_IH _hoops_HCR _hoops_RSSI... _hoops_RRP _hoops_IS _hoops_IRHH _hoops_RCRR
					_hoops_HCR _hoops_RSSI _hoops_HS _hoops_RH _hoops_PSHR _hoops_SGI.  _hoops_CGP _hoops_HAR, _hoops_SR _hoops_RRP _hoops_IS _hoops_CCPP _hoops_IRS _hoops_RHRHR->_hoops_SGI _hoops_CRPR */

					if (_hoops_AHRHR == 0) {
						/* _hoops_RGR _hoops_HRGR _hoops_RH _hoops_SRS _hoops_GHIR _hoops_RHIR */
						*_hoops_GARHR |= _hoops_GPRHR;
						_hoops_AHRHR = _hoops_GPRHR;
					}
					else {
						if (_hoops_GPRHR != _hoops_AHRHR) {
							/* _hoops_AGGA _hoops_SR _hoops_CHR _hoops_AHCA _hoops_IS _hoops_IRHH _hoops_SPR _hoops_HSP _hoops_HAGH _hoops_HII _hoops_RH _hoops_ACSP,
							_hoops_HIS _hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_IRS _hoops_RHRHR->_hoops_SGI _hoops_CRPR _hoops_GAPR, _hoops_SR _hoops_RRP _hoops_IS _hoops_IRHH _hoops_SPR */
							int i = 0;
							ZALLOC_ARRAY(_hoops_SPHPR->local_face_attributes.flags, _hoops_SPHPR->face_count, _hoops_GIIPR);
							for (i = 0; i < face_count; i++)
								_hoops_SPHPR->local_face_attributes.flags[i] = _hoops_SPHPR->local_face_attributes._hoops_SGRHR;

							_hoops_SPHPR->local_face_attributes.flags[face_count] = _hoops_GPRHR;
							_hoops_SPHPR->polyhedron_flags |= _hoops_APRHR;
							_hoops_GARHR = &(_hoops_SPHPR->local_face_attributes.flags[face_count]);
						}
						else
							/* _hoops_SR'_hoops_ASAR _hoops_HGGC _hoops_HAGC _hoops_HCR _hoops_IIGR _hoops_RH _hoops_RSSI _hoops_HS _hoops_RH _hoops_PSHR _hoops_SGI */
							*_hoops_GARHR |= _hoops_GPRHR;
					}
				}
				else {
#endif
					*_hoops_GARHR |= _hoops_GPRHR;
//				}
			} _hoops_RGGA (++item == _hoops_CRRHR);

// 			_hoops_RPP (_hoops_IRRC(_hoops_RRCPR->_hoops_PHRHR, _hoops_HHRHR))
				++_hoops_GARHR;
			face_count++;
		} while (item != end);
	}
}



local void _hoops_RIHPR (
	_hoops_AIHPR *							_hoops_PIHPR) {
	int								_hoops_IHRHR;
	_hoops_SRRHR *		_hoops_GARHR;
	Local_Vertex_Flags *			_hoops_CHRHR;
	Local_Vertex_Flags *			_hoops_SHRHR;
	Local_Vertex_Flags *			_hoops_GIRHR;
	_hoops_SRRHR		_hoops_RIRHR;
	_hoops_SRRHR		_hoops_AIRHR;
	_hoops_SRRHR		_hoops_PIRHR;
	int								_hoops_SSIPR;

#	define		_hoops_HIRHR(_hoops_PPCP, _hoops_GCCPR) _hoops_GHIA (					\
					if (BIT (*_hoops_PPCP, _hoops_AARHR))		\
						(_hoops_GCCPR) |= _hoops_PARHR;				\
					else if (BIT (*_hoops_PPCP, _hoops_HARHR))	\
						(_hoops_GCCPR) |= _hoops_IARHR;				\
					else												\
						(_hoops_GCCPR) |= _hoops_CARHR;)

	_hoops_RIRHR = _hoops_AIRHR = _hoops_PIRHR = (_hoops_SRRHR)0;
	_hoops_IHRHR = _hoops_PIHPR->rows - 1;
	_hoops_SSIPR = 2*_hoops_PIHPR->columns - 2;

	_hoops_GARHR = _hoops_PIHPR->local_face_attributes._hoops_GARHR;
	_hoops_CHRHR = _hoops_PIHPR->local_vertex_attributes._hoops_CHHPR();
	_hoops_SHRHR = _hoops_PIHPR->local_vertex_attributes._hoops_CHHPR(_hoops_PIHPR->columns);

	do {
		int		_hoops_IIRHR = _hoops_SSIPR;

		_hoops_HIRHR (_hoops_CHRHR, _hoops_RIRHR);
		_hoops_HIRHR (_hoops_SHRHR, _hoops_AIRHR);

		do {
			_hoops_GIRHR = _hoops_CHRHR + 1;
			_hoops_HIRHR (_hoops_GIRHR, _hoops_PIRHR);

			*_hoops_GARHR &= ~_hoops_PPRHR;
			*_hoops_GARHR |= _hoops_RIRHR | _hoops_AIRHR | _hoops_PIRHR;

			_hoops_CHRHR = _hoops_SHRHR; _hoops_RIRHR = _hoops_AIRHR;
			_hoops_SHRHR = _hoops_GIRHR; _hoops_AIRHR = _hoops_PIRHR;

// 			_hoops_RPP (_hoops_IRRC(_hoops_HSHRR->_hoops_PHRHR, _hoops_HHRHR))
				++_hoops_GARHR;
		} _hoops_RGGA (--_hoops_IIRHR == 0);

		if (BIT(_hoops_PIHPR->polyhedron_flags, _hoops_CGRHR))
			++_hoops_CHRHR, ++_hoops_SHRHR;  /* _hoops_ARGAR _hoops_IS _hoops_SPS _hoops_GAGHR */
	} _hoops_RGGA (--_hoops_IHRHR == 0);
}



/*
 * _hoops_IPCP "_hoops_RHCP" _hoops_SGI _hoops_IIGR _hoops_IRS _hoops_HSP _hoops_IRHC _hoops_RSH _hoops_AHPH _hoops_HAGH _hoops_APSA
 * _hoops_PISRR _hoops_CHR _hoops_IGI _hoops_HPP _hoops_SGS _hoops_HSP'_hoops_GRI _hoops_GIHA. _hoops_RCHPR _hoops_CHR _hoops_IGI _hoops_IS _hoops_ACHPR
 * _hoops_GH _hoops_RH _hoops_RHPP _hoops_ASCA _hoops_RRGR.
 */
local void _hoops_CIRHR (
	Polyhedron *		_hoops_IPRI) {

	if (_hoops_IPRI->local_vertex_attributes._hoops_SIRHR ==
		_hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR) {

		for (int i=0; i<_hoops_IPRI->face_count; i++) {
			_hoops_IPRI->local_face_attributes._hoops_GARHR[i] |= _hoops_IARHR;
		}
	}
	else if (_hoops_IPRI->local_vertex_attributes._hoops_RCRHR ==
			 _hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR) {

		for (int i=0; i<_hoops_IPRI->face_count; i++) {
			_hoops_IPRI->local_face_attributes._hoops_GARHR[i] |= _hoops_PARHR;
		}
	}
	else if (_hoops_IPRI->local_vertex_attributes._hoops_SIRHR == 0 &&
			 _hoops_IPRI->local_vertex_attributes._hoops_RCRHR == 0) {

		for (int i=0; i<_hoops_IPRI->face_count; i++) {
			_hoops_IPRI->local_face_attributes._hoops_GARHR[i] |= _hoops_CARHR;
		}
	}
	else { /* _hoops_SR _hoops_HS _hoops_IS _hoops_RHCA */
		if (_hoops_IPRI->type == _hoops_SCIP)
			_hoops_CPHPR ((Shell *)_hoops_IPRI);
		else /* _hoops_GSHPR */
			_hoops_RIHPR ((_hoops_AIHPR *)_hoops_IPRI);
	}

	_hoops_IPRI->_hoops_ACRHR |= _hoops_PPRHR;
}



GLOBAL_FUNCTION void HI_Assemble_Vertex_Normals (
	Polyhedron *				_hoops_IPRI) {

	if (_hoops_IPRI->type == _hoops_SCIP)
		HI_Assemble_Shell_Vertex_Normals ((Shell *)_hoops_IPRI);
	else
		HI_Assemble_Mesh_Vertex_Normals ((_hoops_AIHPR *)_hoops_IPRI);
}


GLOBAL_FUNCTION _hoops_GSPGR HI_Assemble_3D_Tristrips (
	Polyhedron *				_hoops_IPRI,
	_hoops_SARHR		_hoops_HGSPR,
	bool						_hoops_PCRHR) {
	_hoops_GSPGR						_hoops_RSPGR, _hoops_ASPGR;



	if (_hoops_IPRI->local_face_attributes._hoops_GARHR == 0) {
		if (_hoops_IPRI->face_count > 0) {
			ZALLOC_ARRAY(_hoops_IPRI->local_face_attributes._hoops_GARHR, _hoops_IPRI->face_count, _hoops_SRRHR);
			_hoops_IPRI->local_face_attributes._hoops_HCRHR = _hoops_IPRI->face_count;
		}
	}
	else {
		if (_hoops_IPRI->face_count > _hoops_IPRI->local_face_attributes._hoops_HCRHR) {
			FREE_ARRAY(_hoops_IPRI->local_face_attributes._hoops_GARHR, _hoops_IPRI->local_face_attributes._hoops_HCRHR, _hoops_SRRHR);
			_hoops_IPRI->local_face_attributes._hoops_HCRHR = 0;
			ZALLOC_ARRAY(_hoops_IPRI->local_face_attributes._hoops_GARHR, _hoops_IPRI->face_count, _hoops_SRRHR);
			_hoops_IPRI->local_face_attributes._hoops_HCRHR = _hoops_IPRI->face_count;
		}
		else {
			ZERO_ARRAY(_hoops_IPRI->local_face_attributes._hoops_GARHR, _hoops_IPRI->face_count, _hoops_SRRHR);
		}
	}

	_hoops_RSPGR = HI_What_Time();

	if (_hoops_PCRHR) {
		if (BIT (_hoops_IPRI->polyhedron_flags, PHF_VERTEX_NORMALS_VALID)) {
			/* _hoops_SSIA _hoops_ICRHR _hoops_APIP */
			_hoops_PCRHR = false;
		}
		else if (_hoops_IPRI->local_vertex_attributes.explicit_normal_count == _hoops_IPRI->point_count ||
				 _hoops_IPRI->face_count == 0) {
			_hoops_IPRI->polyhedron_flags |= PHF_VERTEX_NORMALS_VALID;
			_hoops_PCRHR = false;
		}
	}

	_hoops_HGSPR &= ~_hoops_IPRI->_hoops_ACRHR;
	if (!_hoops_PCRHR && !_hoops_HGSPR)
		goto _hoops_PRSPR;


	if ((_hoops_HGSPR || BIT(_hoops_IPRI->polyhedron_flags, _hoops_CCRHR)) &&
		_hoops_IPRI->type == _hoops_SCIP &&
		((Shell const *)_hoops_IPRI)->face_list == null) {
		/* _hoops_PS _hoops_PAH'_hoops_RA _hoops_SCRHR _hoops_CCGI, _hoops_CR _hoops_SR _hoops_HS _hoops_PSP _hoops_HSP _hoops_HIGR */
		if (_hoops_IPRI->tristrips != null &&
			(_hoops_IPRI->local_face_attributes.flags != 0 || _hoops_IPRI->local_face_attributes._hoops_SGRHR != 0)) {
			/* _hoops_HIH _hoops_PAH _hoops_GAAP _hoops_CCIH _hoops_GH _hoops_IGRI _hoops_SHPH _hoops_GPP _hoops_CCGI */
			HI_Resort_Tristrips (_hoops_IPRI, -1);
			_hoops_HGSPR &= ~_hoops_IPRI->_hoops_ACRHR;
			if (!_hoops_PCRHR && !_hoops_HGSPR)
				goto _hoops_PRSPR;
		}

		if (_hoops_HGSPR) {
			/* _hoops_CPHP _hoops_IRSGR _hoops_IRS _hoops_GSRHR */

			/* _hoops_SR _hoops_IGI _hoops_IS _hoops_RSRHR _hoops_RH _hoops_HSPR _hoops_ASRHR: */
			/* _hoops_PSRHR (_hoops_HSRHR, _hoops_ISRHR,
					  "_hoops_CSRHR _hoops_HGAP _hoops_SSRHR _hoops_HIH _hoops_HSP _hoops_HIGR _hoops_PIH _hoops_HRGR _hoops_HAR _hoops_HHPA"); */

			/* _hoops_GGAHR _hoops_SCH _hoops_RRGI _hoops_RH _hoops_RGAHR. */
			HI_Reset_Strip_Flags (_hoops_IPRI);

			/* _hoops_SRCH _hoops_IRCC _hoops_IS _hoops_AA _hoops_RGR _hoops_GICS _hoops_HCCPR _hoops_CPHP _hoops_SHPH */
			_hoops_IPRI->_hoops_ACRHR |= _hoops_HGSPR;

			if (_hoops_PCRHR) {
				if (_hoops_IPRI->type == _hoops_SCIP)
					HI_Assemble_Shell_Tristrips ((Shell *)_hoops_IPRI, 0, true);
				else /* _hoops_GSHPR */
					HI_Assemble_Mesh_Tristrips ((_hoops_AIHPR *)_hoops_IPRI, 0, true);
			}
			goto _hoops_PRSPR;
		}
	}

	if (_hoops_HGSPR && _hoops_IPRI->tristrips != null) {
		/* _hoops_CCGC _hoops_APRI _hoops_CGHI _hoops_GHIR'_hoops_GRI _hoops_ACPP */
#ifdef _hoops_IGSPR
# ifdef _hoops_CGSPR
		_hoops_SGSPR (HEC_INFO, HES_REBUILDING_TRISTRIP,
				_hoops_GRSPR (null, "Rebuilding tristrips for polyhedron %k", &_hoops_IPRI));
# endif /* _hoops_SHRS */
#endif /* _hoops_RRSPR */
		HI_Free_Tristrip_List (_hoops_IPRI->tristrips);
		_hoops_IPRI->tristrips = null;
	}

	if (_hoops_IPRI->face_count > 0) {
		if (_hoops_HGSPR) {
			/* _hoops_ARAS _hoops_RHIR _hoops_PPR _hoops_HGCR _hoops_RH _hoops_AGAHR-_hoops_SGI _hoops_HSH _hoops_ARP _hoops_RPHR */
			_hoops_CIRHR (_hoops_IPRI);

			/* _hoops_HPCAR _hoops_RGR _hoops_HPP _hoops_SHIR */
			_hoops_IPRI->polyhedron_flags |= _hoops_PGAHR;

			/* _hoops_HHSA _hoops_IRS _hoops_AIRI _hoops_HIGR _hoops_HRSPR */
			{
				Tristrip *			ts;

				if ((ts = _hoops_IPRI->tristrips) != null) do {
					_hoops_GACR *		dl;

					if ((dl = ts->_hoops_GAHA) != null) do {
						dl->_hoops_GSAI = (_hoops_GHGI)0xffffffff;
					} while ((dl = dl->next) != null);
				} while ((ts = ts->next) != null);
			}

			if (_hoops_IPRI->bounding == null)
				_hoops_IPRI->bounding = Bounding::Create(_hoops_IPRI->point_count, _hoops_IPRI->points);

			/* _hoops_HA _hoops_PHHR _hoops_HGCR _hoops_RH _hoops_CCGI */
			if (_hoops_IPRI->type == _hoops_SCIP) {
				Shell *			_hoops_SPHPR = (Shell *)_hoops_IPRI;

				if (_hoops_SPHPR->face_list) {
					HI_Assemble_Shell_Tristrips (_hoops_SPHPR,
											 _hoops_HGSPR,
											 _hoops_PCRHR);
				}
				else {
					HI_Assemble_Vertex_Normals (_hoops_IPRI);
				}
			}
			else /* _hoops_GSHPR */
				HI_Assemble_Mesh_Tristrips ((_hoops_AIHPR *)_hoops_IPRI,
											_hoops_HGSPR,
											_hoops_PCRHR);
		}
		else {// _hoops_RPP (_hoops_HGAHR)
			HI_Assemble_Vertex_Normals (_hoops_IPRI);

			if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_CCRHR) &&
				_hoops_IPRI->tristrips != null)
				HI_Resort_Tristrips (_hoops_IPRI, -1);
		}
	}

	_hoops_IPRI->_hoops_ACRHR |= _hoops_HGSPR;

	if (_hoops_PCRHR)
		_hoops_IPRI->polyhedron_flags |= PHF_VERTEX_NORMALS_VALID;

	if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
		Local_Face_Attributes   *_hoops_CPRI = &_hoops_IPRI->local_face_attributes;
		_hoops_GIIPR		*flags = _hoops_CPRI->_hoops_CHHPR();
		int						count = _hoops_IPRI->face_count;

		do *flags++ &= ~_hoops_IGAHR;
		while (--count > 0);

		if (_hoops_CPRI->lff_uniform(_hoops_IPRI->face_count)) {
			/* _hoops_SR _hoops_CHR _hoops_ISSC _hoops_IS _hoops_IRS _hoops_PIAP _hoops_CAS _hoops_RH _hoops_SGI _hoops_CHR _hoops_GHRHR, _hoops_IIS'_hoops_GRI _hoops_CIH _hoops_RH _hoops_SGI _hoops_CRPR */
			_hoops_CPRI->_hoops_SGRHR = _hoops_CPRI->flags[0];
			FREE_ARRAY(_hoops_IPRI->local_face_attributes.flags, _hoops_IPRI->face_count, _hoops_GIIPR);
			_hoops_IPRI->polyhedron_flags &= ~_hoops_APRHR;
			_hoops_CPRI->flags = 0;
		}
	}

_hoops_PRSPR:
	_hoops_ASPGR = HI_What_Time();
	return (_hoops_ASPGR - _hoops_RSPGR) / _hoops_HSPGR;
}


GLOBAL_FUNCTION void HI_Free_Texture_Parameters (
	_hoops_RRCC *		_hoops_HAPAR) {
	_hoops_RRCC *		next;

	do {
		next = _hoops_HAPAR->next;

		if (_hoops_HAPAR->_hoops_CCHA != null && BIT (_hoops_HAPAR->_hoops_SCAI, _hoops_ARCC))
			FREE_ARRAY (_hoops_HAPAR->_hoops_CCHA, _hoops_HAPAR->_hoops_CGAHR * _hoops_HAPAR->_hoops_GSHA, _hoops_RSSH);

		FREE (_hoops_HAPAR, _hoops_RRCC);
		_hoops_HAPAR = null;

		if (next != null && _hoops_ISAI (next) == 0)
			_hoops_HAPAR = next;
	} while (_hoops_HAPAR != null);
}

GLOBAL_FUNCTION void HI_Free_Tristrip (
	Tristrip *		ts) {

	if (BIT (ts->_hoops_RAHH, _hoops_AAHH)) {
		if (ts->lengths != null) {
			if (!ts->lengths_allocated)
				ts->lengths_allocated = ts->_hoops_PHHA;
			FREE_ARRAY (ts->lengths, ts->lengths_allocated, int);
		}
		if (ts->_hoops_AIHA != null) {
			if (!ts->_hoops_IPII)
				ts->_hoops_IPII = ts->total;
			FREE_ARRAY (ts->_hoops_AIHA, ts->_hoops_IPII, int);
		}
		if (ts->face_indices != null) {
			if (!ts->_hoops_SGAHR)
				ts->_hoops_SGAHR = ts->total;
			FREE_ARRAY (ts->face_indices, ts->_hoops_SGAHR, int);
		}
	}

	/* _hoops_RPP _hoops_RGR _hoops_CRHH _hoops_HRGR _hoops_HAR _hoops_CIGHR _hoops_HII _hoops_RH _hoops_AARPR, _hoops_HIH _hoops_HRGR _hoops_RIIA _hoops_RH _hoops_GGPI _hoops_HII _hoops_IRS
	   _hoops_PGSA-_hoops_SGSI _hoops_CAIH, _hoops_SR _hoops_RRP _hoops_IS _hoops_CIH _hoops_RRI _hoops_HSAR _hoops_SR _hoops_SIGHR _hoops_CHH */
	if (ts->points != null && BIT (ts->_hoops_RAHH, _hoops_AIPI))
		FREE_ARRAY_ALIGNED (ts->points, ts->point_count, Point, 16);

#ifndef DISABLE_GEOMETRY_ATTRIBUTES
#  ifndef _hoops_GCGHR
	if (ts->_hoops_PCHA != null && BIT (ts->_hoops_RAHH, _hoops_PIPI))
		FREE_ARRAY (ts->_hoops_PCHA, ts->point_count, RGB);
	if (ts->_hoops_HCHA != null && BIT (ts->_hoops_RAHH, _hoops_RCGHR))
		FREE_ARRAY (ts->_hoops_HCHA, ts->point_count, _hoops_ACGHR);
	if (ts->_hoops_PAGI != null && BIT (ts->_hoops_RAHH, _hoops_SHRI))
		FREE_ARRAY (ts->_hoops_PAGI, ts->face_count, RGB);
#  endif

#  ifndef _hoops_HCGHR
	if (ts->_hoops_ICHA != null && BIT (ts->_hoops_RAHH, _hoops_ICGHR))
		FREE_ARRAY (ts->_hoops_ICHA, ts->point_count, Vector);
	if (ts->_hoops_PRHH != null && BIT (ts->_hoops_RAHH, _hoops_RCPI))
		FREE_ARRAY_ALIGNED (ts->_hoops_PRHH, ts->face_count, _hoops_ARPA, 16);
#  endif

#  ifndef DISABLE_TEXTURING
	if (ts->_hoops_GSSH != null && _hoops_ISAI (ts->_hoops_GSSH) == 0)
		HI_Free_Texture_Parameters (ts->_hoops_GSSH);
#  endif
#endif

	if (ts->_hoops_SCGHR && _hoops_ISAI (ts->_hoops_SCGHR) == 0)
		HI_Free_Tristrip ((Tristrip alter *)ts->_hoops_SCGHR);

	if (ts->_hoops_GAHA) {
		_hoops_GACR *		dl;

		while ((dl = ts->_hoops_GAHA) != null) {
			ts->_hoops_GAHA = dl->next;
			_hoops_HPRH(dl);
		}
	}

	ts->bounding.release();

	/* _hoops_RGR _hoops_CGH _hoops_SHH _hoops_RH _hoops_RGAR _hoops_HGHC _hoops_CAS _hoops_RHAC _hoops_CACH _hoops_IRS _hoops_AASGR _hoops_CGI _hoops_RGCPR _hoops_CRGR _hoops_GSGHR */
	FREE (ts, Tristrip);
}


GLOBAL_FUNCTION void HI_Free_Tristrip_List (
	Tristrip *		_hoops_RSGHR) {
	Tristrip *		next;

	if (_hoops_RSGHR) do {
		next = _hoops_RSGHR->next;
		if (_hoops_ISAI (_hoops_RSGHR) <= 0)
			HI_Free_Tristrip (_hoops_RSGHR);
	} while ((_hoops_RSGHR = next) != null);
}

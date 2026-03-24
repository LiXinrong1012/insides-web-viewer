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
 * $Id: obf_tmp.txt 1.279 2010-11-09 04:02:13 covey Exp $
 */

/* _hoops_GIGHR: _hoops_HGI _hoops_PCPH _hoops_HHS _hoops_PAHH _hoops_SHH _hoops_IIAC _hoops_RRI _hoops_AGCRA _hoops_HPP _hoops_SAHR
 *		 _hoops_AHCAS _hoops_SCH _hoops_PHHR _hoops_RHIR _hoops_RH _hoops_HPRGR-_hoops_PGSA _hoops_PHCAS. _hoops_RAHP _hoops_SCH _hoops_HRGR
 *		 _hoops_RSSA _hoops_CHR _hoops_ASAR-_hoops_CHIAR _hoops_IRS _hoops_SHSC _hoops_AHCPR.
 */

/* _hoops_GIGHR: _hoops_GASA: _hoops_GHAP _hoops_CHH _hoops_PII _hoops_IS _hoops_IHIS _hoops_RH _hoops_RGSSA _hoops_PPR _hoops_RSRRA _hoops_RRGR _hoops_PSAP _hoops_CRGR _hoops_IRS _hoops_GIAH
 *		 _hoops_RGHR, _hoops_HIH _hoops_SSIA _hoops_HGGC _hoops_HHCAS _hoops_PPR _hoops_RPGP _hoops_ACSRR _hoops_CCGI, _hoops_HIS _hoops_SSIA _hoops_RSGR _hoops_GH
 *		 _hoops_GRP _hoops_HAH _hoops_AHPH _hoops_IIGR _hoops_RH _hoops_IRGH _hoops_RGCAH _hoops_SGS _hoops_IHCAS _hoops_ARI.  _hoops_PS _hoops_CGH _hoops_SHH _hoops_GHGA
 *		 _hoops_CHCAS _hoops_GHSHA _hoops_IH _hoops_GCPA _hoops_PPR _hoops_HAHAR */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "phedron.h"
#include "tandt.h"
#include "select.h"
#include "topology.h"
#include "phdraw.h"
#include "patterns.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

#ifndef DISABLE_SELECTION

struct _hoops_SHCAS {
	float						tc,
								_hoops_CIPAS;
	int							_hoops_GICAS; /* _hoops_AHHR _hoops_PAR _hoops_SPR _hoops_GPCPR */
	bool					_hoops_RICAS;
	DC_Point					*start;
	_hoops_GRCAR				*_hoops_AICAS;
	DC_Point					*end;
	_hoops_GRCAR				*_hoops_PICAS;
};


/* _hoops_AHGHR _hoops_IRS _hoops_GHSHA _hoops_GGSC _hoops_PPR _hoops_RH _hoops_GHSHA _hoops_SSH _hoops_PIRA,
 * _hoops_CGIC _hoops_RPP _hoops_RH _hoops_GHSHA _hoops_PPSR _hoops_AACC _hoops_SGGR _hoops_HPP _hoops_RH
 * _hoops_HPPA _hoops_GHC _hoops_IHIA _hoops_CCA _hoops_RH _hoops_HIHP _hoops_IPP.
 */

local bool _hoops_HICAS (
	Net_Rendition const &		nr,
	Point const *				_hoops_SIAIA) {
	_hoops_HHCR	const &	_hoops_IHCR = nr->transform_rendition;

	if (BIT (_hoops_IHCR->flags, _hoops_CSP)) {
		_hoops_IAPA const		*_hoops_HRCAR;

		_hoops_HRCAR = _hoops_IHCR->_hoops_RGH->_hoops_PHCA;

		do {
			_hoops_GPPA const		*_hoops_IRCAR;
			bool							_hoops_IICAS = false;

			_hoops_IRCAR = _hoops_HRCAR->_hoops_APPA;
			do {
				/* _hoops_CGP _hoops_GII _hoops_IIGR _hoops_RH _hoops_HPPA _hoops_IPPA _hoops_RGCSA _hoops_SGGR _hoops_RH _hoops_GHSHA
				 * _hoops_PPSR, _hoops_ASRC _hoops_RCPP.
				 */

				if ((_hoops_IRCAR->_hoops_SPPA.a * _hoops_SIAIA->x + _hoops_IRCAR->_hoops_SPPA.b * _hoops_SIAIA->y +
						_hoops_IRCAR->_hoops_SPPA.c * _hoops_SIAIA->z + _hoops_IRCAR->_hoops_SPPA.d) > 0.0f)
					_hoops_IICAS = true;
			} while ((_hoops_IRCAR = _hoops_IRCAR->next) != null);

			if (!_hoops_IICAS)
				return true;
		} while ((_hoops_HRCAR = _hoops_HRCAR->next) != null);

		return false;
	}

	return true;
}




local bool _hoops_CICAS (
	_hoops_PCCCP alter *	status,
	DC_Point const *			_hoops_SICAS,
	DC_Point const *			_hoops_GCCAS) {
	_hoops_RHHPR const *	_hoops_SRCPR,
												*_hoops_ISHHC;
	int							_hoops_RCCAS;
	int							_hoops_PSHHC;
	Shell const *				_hoops_SPHPR = (Shell const *)status->_hoops_IPRI;

	if (_hoops_SPHPR->_hoops_GRCPR == null)
		HI_Create_Shell_Edges ((Shell alter *)_hoops_SPHPR, false);
	else if (_hoops_SPHPR->face_list && !_hoops_SPHPR->_hoops_GSAPA) {
		Shell * _hoops_ACCAS = (Shell*)(status->_hoops_IPRI);

		HI_Repair_Shell_Edges (status->sc->_hoops_SRA->_hoops_RIGC, _hoops_ACCAS);
	}

	if (_hoops_SICAS < _hoops_GCCAS) {
		_hoops_RCCAS = _hoops_SICAS - status->_hoops_CGCAR;
		_hoops_PSHHC = _hoops_GCCAS - status->_hoops_CGCAR;
	}
	else {
		_hoops_RCCAS = _hoops_GCCAS - status->_hoops_CGCAR;
		_hoops_PSHHC = _hoops_SICAS - status->_hoops_CGCAR;
	}

	_hoops_SRCPR = _hoops_SPHPR->_hoops_HHHPR[_hoops_RCCAS];
	_hoops_ISHHC = _hoops_SPHPR->_hoops_HHHPR[_hoops_RCCAS + 1];

	if (_hoops_SRCPR != _hoops_ISHHC) {
		do if (_hoops_SRCPR->_hoops_GIHPR >= _hoops_PSHHC)
			return (_hoops_SRCPR->_hoops_GIHPR > _hoops_PSHHC);
		_hoops_RGGA (++_hoops_SRCPR == _hoops_ISHHC);
	}

	return true;
}


local bool _hoops_PCCAS (
	_hoops_PCCCP alter	*status,
	struct _hoops_SHCAS alter		*_hoops_HCCAS,
	bool						_hoops_HGRHP) {

	if (status->_hoops_IPRI != null &&
		status->_hoops_IPRI->type == _hoops_SCIP && !_hoops_HGRHP)
		if (_hoops_CICAS (status, _hoops_HCCAS->start, _hoops_HCCAS->end))
			return false;

	if (BIT (*_hoops_HCCAS->_hoops_PICAS, _hoops_IPCAR)) {
		status->_hoops_SPPAS.vertex1 = _hoops_HCCAS->start;
		status->_hoops_SPPAS.vertex2 = _hoops_HCCAS->end;
	}
	else if (BIT (*_hoops_HCCAS->_hoops_AICAS, _hoops_IPCAR)) {
		status->_hoops_SPPAS.vertex1 = _hoops_HCCAS->end;
		status->_hoops_SPPAS.vertex2 = _hoops_HCCAS->start;
	}
	else if (_hoops_HCCAS->tc < 0.5f) {
		status->_hoops_SPPAS.vertex1 = _hoops_HCCAS->start;
		status->_hoops_SPPAS.vertex2 = _hoops_HCCAS->end;
	}
	else {
		status->_hoops_SPPAS.vertex1 = _hoops_HCCAS->end;
		status->_hoops_SPPAS.vertex2 = _hoops_HCCAS->start;
	}

	return true;
}


local int _hoops_ICCAS (
	Polyhedron const		*_hoops_IPRI,
	int						_hoops_CCCAS) {
	/* _hoops_HIHP _hoops_RH _hoops_AARPR _hoops_HSP _hoops_PHI _hoops_IS _hoops_IPSP-_hoops_IAHA */

	if (_hoops_CCCAS < 0) return _hoops_CCCAS;							/* _hoops_PSP _hoops_RHHR */
	else if (_hoops_IPRI == NULL) return _hoops_CCCAS;				/* _hoops_PSP _hoops_SIA */
	else if (_hoops_IPRI->type == _hoops_SCIP) return _hoops_CCCAS;/* _hoops_PIHGR */
	else /* _hoops_RPP (_hoops_CPHAR->_hoops_GPRR == _hoops_GSHPR) */ {		/* _hoops_ACIPR _hoops_RPP _hoops_RHGS _hoops_IAHA */
		if (BIT (HOOPS_WORLD->system_flags, _hoops_GGSPP)) {
			_hoops_AIHPR const *		_hoops_PIHPR = (_hoops_AIHPR const *)_hoops_IPRI;
			int					row,
								offset,
								_hoops_SSIPR;

			_hoops_SSIPR = (_hoops_PIHPR->columns - 1)*2;

			row = _hoops_CCCAS / _hoops_SSIPR;
			offset = _hoops_CCCAS % _hoops_SSIPR;

			if (!BIT (offset, 1))
				return row * _hoops_PIHPR->columns + offset/2;
			else
				return -((row + 1) * _hoops_PIHPR->columns + (offset + 1)/2);
		}
		return _hoops_CCCAS;
	}
}


local bool _hoops_SCCAS (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			_hoops_GHPCP,
	float const *				ws,
	_hoops_GRCAR const *			_hoops_ARCAR,
	_hoops_CPPAS alter *			_hoops_GSCAS) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter *	sc = dc->_hoops_APHHP;
	float						_hoops_HSHGA,
								_hoops_ISHGA,
								_hoops_HHGGH = _hoops_GSCAS->_hoops_HISAP,
								_hoops_GPCH = sc->_hoops_AICAH.x,
								_hoops_RPCH = sc->_hoops_AICAH.y;
	DC_Point const *			_hoops_RSCAS = _hoops_GHPCP + count;
	bool						_hoops_SHHAS = false;
	_hoops_CPPAS alter *			_hoops_ASCAS = _hoops_GSCAS;
	_hoops_PCCCP alter	*	status;
	bool						_hoops_PSCAS;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_ICP const &	_hoops_CCP = nr->_hoops_GSP;
	float						_hoops_HSCAS, _hoops_ISCAS;

	status = (_hoops_PCCCP alter *)nr->_hoops_SRA->_hoops_APHHP->_hoops_AICCP;
	_hoops_PSCAS = BIT (nr->transform_rendition->heuristics, _hoops_GAIRP) &&
			  !BIT (sc->options, _hoops_IICAH);

	_hoops_HHGGH *= 0.999f; /* _hoops_SRCH _hoops_IHGRH _hoops_IAHAR _hoops_PCCP _hoops_ISHA
							* _hoops_RHHR _hoops_CRGR _hoops_IRS _hoops_CSCAS _hoops_GPHA _hoops_RHHR.
							*/

	if (_hoops_CCP->ysize < 0) {
		_hoops_ICP alter &	_hoops_HCSHP = (_hoops_ICP alter &)_hoops_CCP;
		float					  _hoops_RPCAS;

		_hoops_RPCAS = HD_Compute_Generic_Size (nr, _hoops_HCSHP->_hoops_PHP, _hoops_HCSHP->_hoops_HHP, 1.0f, false, 0, true);
		_hoops_HCSHP->ysize = _hoops_RPCAS*0.5f;
		_hoops_HCSHP->_hoops_RGRS = _hoops_RPCAS*0.5f*nr->_hoops_SRA->current._hoops_AGRS;
	}

	_hoops_HSCAS = (BIT(_hoops_CCP->glyph->flags, _hoops_GSIAP) ? 1.0f : _hoops_CCP->ysize);
	_hoops_ISCAS = 1.0f/(sc->_hoops_HICAH.x*sc->_hoops_HICAH.y);

	do {
		if ((*_hoops_ARCAR & ~_hoops_RPCAR) == _hoops_HCRCP &&
			(!BIT(*_hoops_ARCAR, _hoops_RPCAR) ||
			 HD_Point_Within_Cutting_Planes (nr->transform_rendition,
											 _hoops_GHPCP->x, _hoops_GHPCP->y, _hoops_GHPCP->z))) {
			_hoops_HSHGA = (_hoops_GHPCP->x - _hoops_GPCH) / sc->_hoops_HICAH.x;
			_hoops_ISHGA = (_hoops_GHPCP->y - _hoops_RPCH) / sc->_hoops_HICAH.y;

			if (_hoops_GHPCP->z >= sc->bounding.hither && _hoops_GHPCP->z <= sc->bounding.yon) {
				float			size = _hoops_HSCAS;
				float			_hoops_SACPA = 1.0f;
				float			_hoops_HISAP;

				if (_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) {
					if (*ws >= _hoops_IHCR->_hoops_CHCR &&
						_hoops_CCP->_hoops_HHP == _hoops_SPSC &&
						nr->transform_rendition->_hoops_SPH->projection == _hoops_GHH) {
						_hoops_SACPA /= *ws;
						size *= _hoops_SACPA;
					}
				}

				if (BIT (sc->options, _hoops_CRPAS)) {
					bool							_hoops_RCAI = false;

					_hoops_IGRS (dc);

					if (sc->_hoops_GPPAS) {
						void *							_hoops_CCHSP;

						_hoops_CCHSP = _hoops_AACGH (nr, true);
						_hoops_AGIGH (nr, 1, _hoops_GHPCP, null, &_hoops_SACPA);
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

						_hoops_AGIGH (nr, 1, _hoops_GHPCP, null, &_hoops_SACPA);

						if (_hoops_ICSIR->input._hoops_PHHSP == 0)
							_hoops_RCAI = true;
					}

				  _hoops_SIPAS:
					_hoops_SGRS (dc);
					if (_hoops_RCAI)
						goto _hoops_SSCAS;
				}

#ifndef DISABLE_POLY_SELECTION
				if (sc->_hoops_RAPAS != null) {
					DC_Point		test;

					test.x = _hoops_GHPCP->x;
					test.y = _hoops_GHPCP->y;
					test.z = _hoops_GHPCP->z;

					if (BIT (sc->options, _hoops_PRPAS)) {
						if (!HD_Select_Point_By_Polygon (nr, &test))
							goto _hoops_SSCAS;
					}
					else /* _hoops_ISII _hoops_GHSHA */
						if (!HD_Select_Circle_By_Polyline (nr, &test, 0.0f))
							goto _hoops_SSCAS;
				}
#endif

				_hoops_HISAP = _hoops_HSHGA*_hoops_HSHGA + _hoops_ISHGA*_hoops_ISHGA;
				if (_hoops_PSCAS && _hoops_HISAP > size*size*_hoops_ISCAS && _hoops_HISAP >= _hoops_HHGGH) {}
				else {
					_hoops_ASCAS->_hoops_HISAP = _hoops_HHGGH = _hoops_HISAP;
					_hoops_ASCAS->vertex1 = _hoops_GHPCP;
					_hoops_ASCAS->_hoops_RCSAP = _hoops_GHPCP->z;
					_hoops_SHHAS = true;
				}

				if (_hoops_SHHAS && status->_hoops_SHPAS)
					return true;
				if (status->_hoops_CHPAS) {
					if (_hoops_HISAP < sc->_hoops_GICAH) {
						/* _hoops_GGCR _hoops_IS _hoops_RGIAS */
						_hoops_AISAP *	_hoops_HHCAP;

						ALLOC (_hoops_HHCAP, _hoops_AISAP);
						_hoops_HHCAP->next = null;
						_hoops_HHCAP->_hoops_PISAP[0] = (int) (_hoops_GHPCP - status->_hoops_CGCAR);
						_hoops_HHCAP->_hoops_PISAP[1] = -1;
						_hoops_HHCAP->_hoops_PISAP[2] = -1;
						_hoops_HHCAP->_hoops_HISAP = _hoops_HISAP;
						_hoops_HHCAP->_hoops_IISAP = _hoops_GHPCP->z;
						_hoops_HHCAP->next = null;
						*status->_hoops_APPAS = _hoops_HHCAP;
						status->_hoops_APPAS = &_hoops_HHCAP->next;
						if (!_hoops_PSCAS && ++status->_hoops_PPPAS >=
								nr->_hoops_IRR->_hoops_CCIRP._hoops_SPHPR)
							status->_hoops_CHPAS = false;
					}
				}
			}
		}

	  _hoops_SSCAS:
		++ws;
		++_hoops_ARCAR;
	} while (++_hoops_GHPCP != _hoops_RSCAS);

	return _hoops_SHHAS;
}


local void _hoops_GGSAS (
	Net_Rendition const &		nr,
	DC_Point const *			_hoops_SICAS,
	float						_hoops_PAISA,
	_hoops_GRCAR const *			_hoops_RGSAS,
	DC_Point const *			_hoops_GCCAS,
	float						_hoops_IICPA,
	_hoops_GRCAR const *			_hoops_CHPSH,
	DC_Point const *			_hoops_AGSAS,
	float						_hoops_CICPA,
	_hoops_GRCAR const *			_hoops_SHPSH,
	Point alter *				_hoops_CIHIA,
	int							_hoops_PGSAS) {
	_hoops_ACCCP alter *	sc = (_hoops_ACCCP alter *)nr->_hoops_SRA->_hoops_APHHP;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	float						_hoops_AGRSH, x1, x2, _hoops_HGSAS, _hoops_IGSAS,
								_hoops_PGRSH, _hoops_AGSIR, _hoops_PGSIR, _hoops_CGSAS, _hoops_SGSAS,
								_hoops_HGRSH, _hoops_HGSIR, _hoops_IGSIR, _hoops_GRSAS, _hoops_RRSAS;
	_hoops_ARPA						plane;


	if (BIT (*_hoops_RGSAS | *_hoops_CHPSH | *_hoops_SHPSH, _hoops_IPCAR)) {
		/* _hoops_HSPH _hoops_RH _hoops_SCPH, _hoops_GHHA, _hoops_PPR _hoops_ASRC */
		DC_Point alter _hoops_ARSAS[4];
		float _hoops_PRSAS, _hoops_HRSAS, _hoops_GPGSI;
		float _hoops_IRSAS, _hoops_CRSAS;
		int a, b, c;
		_hoops_GRCAR _hoops_HGSAI = 0;
		float _hoops_SRSAS = _hoops_IHCR->_hoops_GSCH[0] * nr->_hoops_SRA->_hoops_PGCC._hoops_PASHP;

		_hoops_ARSAS[0] = *_hoops_SICAS;
		_hoops_ARSAS[1] = *_hoops_GCCAS;
		_hoops_ARSAS[2] = *_hoops_AGSAS;

		/* _hoops_RH _hoops_ACSP _hoops_IIGR _hoops_RGR _hoops_RIS (_hoops_AHSAR _hoops_RH _hoops_PAGIR _hoops_ARIP) _hoops_HRGR _hoops_GASAS _hoops_IIHA _hoops_GPP
		 * _hoops_RRGR _hoops_HII _hoops_GAGHC */
		if (_hoops_PAISA >= _hoops_IHCR->_hoops_CHCR) {
			if (_hoops_CICPA < _hoops_IHCR->_hoops_CHCR) {
				a = 0;	_hoops_PRSAS = _hoops_PAISA;
				b = 1;	_hoops_HRSAS = _hoops_IICPA;
				c = 2;	_hoops_GPGSI = _hoops_CICPA;
			}
			else {	/* _hoops_RASAS _hoops_PIHA _hoops_SHH _hoops_GHIPR */
				a = 2;	_hoops_PRSAS = _hoops_CICPA;
				b = 0;	_hoops_HRSAS = _hoops_PAISA;
				c = 1;	_hoops_GPGSI = _hoops_IICPA;
			}
		}
		else {
			if (_hoops_IICPA >= _hoops_IHCR->_hoops_CHCR) {
				a = 1;	_hoops_PRSAS = _hoops_IICPA;
				b = 2;	_hoops_HRSAS = _hoops_CICPA;
				c = 0;	_hoops_GPGSI = _hoops_PAISA;
			}
			else {	/* _hoops_AASAS _hoops_PIHA _hoops_SHH _hoops_RGAR _hoops_SPR _hoops_GGR _hoops_RIPS */
				a = 2;	_hoops_PRSAS = _hoops_CICPA;
				b = 0;	_hoops_HRSAS = _hoops_PAISA;
				c = 1;	_hoops_GPGSI = _hoops_IICPA;
			}
		}
		if (_hoops_HRSAS < _hoops_IHCR->_hoops_CHCR) {
			/* _hoops_IHAC & _hoops_IHRPR _hoops_GIPR _hoops_GHIPR, _hoops_GAGPR _hoops_HSPH _hoops_CAPR _hoops_GGR _hoops_HGHC */
			float			_hoops_PASAS = 1.0f / _hoops_IHCR->_hoops_CHCR;

			_hoops_IRSAS = (_hoops_IHCR->_hoops_CHCR - _hoops_PRSAS) / (_hoops_HRSAS - _hoops_PRSAS);
			_hoops_CRSAS = (_hoops_IHCR->_hoops_CHCR - _hoops_PRSAS) / (_hoops_GPGSI - _hoops_PRSAS);

			_hoops_ARSAS[b].x = (_hoops_PRSAS*_hoops_ARSAS[a].x + (_hoops_ARSAS[b].x - _hoops_PRSAS*_hoops_ARSAS[a].x) * _hoops_IRSAS) * _hoops_PASAS;
			_hoops_ARSAS[b].y = (_hoops_PRSAS*_hoops_ARSAS[a].y + (_hoops_ARSAS[b].y - _hoops_PRSAS*_hoops_ARSAS[a].y) * _hoops_IRSAS) * _hoops_PASAS;
			_hoops_ARSAS[b].z = _hoops_SRSAS;
			_hoops_ARSAS[c].x = (_hoops_PRSAS*_hoops_ARSAS[a].x + (_hoops_ARSAS[c].x - _hoops_PRSAS*_hoops_ARSAS[a].x) * _hoops_CRSAS) * _hoops_PASAS;
			_hoops_ARSAS[c].y = (_hoops_PRSAS*_hoops_ARSAS[a].y + (_hoops_ARSAS[c].y - _hoops_PRSAS*_hoops_ARSAS[a].y) * _hoops_CRSAS) * _hoops_PASAS;
			_hoops_ARSAS[c].z = _hoops_SRSAS;
		}
		else {
			/* _hoops_SAHR _hoops_IHRPR _hoops_SACH, _hoops_IRHH _hoops_PGCR _hoops_HIPH _hoops_RAIGR-_hoops_IHAC-_hoops_IHRPR', _hoops_IHAC-_hoops_IHAC'-_hoops_IHRPR' */
			float					_hoops_PASAS = 1.0f / _hoops_IHCR->_hoops_CHCR;

			/* _hoops_IHAC' (_hoops_GIAP _hoops_PPSR _hoops_IIGR _hoops_GIAP _hoops_HASAS) _hoops_GAPA _hoops_IHAC _hoops_PPR _hoops_IHRPR */
			_hoops_IRSAS = (_hoops_IHCR->_hoops_CHCR - _hoops_HRSAS) / (_hoops_GPGSI - _hoops_HRSAS);
			/* _hoops_IHRPR' (_hoops_HRSSR _hoops_PPSR _hoops_IIGR _hoops_GIAP _hoops_HASAS) _hoops_GAPA _hoops_RAIGR _hoops_PPR _hoops_IHRPR */
			_hoops_CRSAS = (_hoops_IHCR->_hoops_CHCR - _hoops_PRSAS) / (_hoops_GPGSI - _hoops_PRSAS);

			/* _hoops_GASA: _hoops_SIGR?
			   _hoops_IASAS[3]._hoops_SISR = (_hoops_CASAS*_hoops_IASAS[_hoops_RCSR]._hoops_SISR + (_hoops_IASAS[_hoops_GSGGR]._hoops_SISR - _hoops_CASAS*_hoops_IASAS[_hoops_RCSR]._hoops_SISR) * _hoops_SASAS) * _hoops_GPSAS;
			   _hoops_IASAS[3]._hoops_HAPC = (_hoops_CASAS*_hoops_IASAS[_hoops_RCSR]._hoops_HAPC + (_hoops_IASAS[_hoops_GSGGR]._hoops_HAPC - _hoops_CASAS*_hoops_IASAS[_hoops_RCSR]._hoops_HAPC) * _hoops_SASAS) * _hoops_GPSAS;
			   _hoops_IASAS[3]._hoops_SSH = _hoops_RPSAS; */
			_hoops_ARSAS[c].x = (_hoops_PRSAS*_hoops_ARSAS[a].x + (_hoops_ARSAS[c].x - _hoops_PRSAS*_hoops_ARSAS[a].x) * _hoops_CRSAS) * _hoops_PASAS;
			_hoops_ARSAS[c].y = (_hoops_PRSAS*_hoops_ARSAS[a].y + (_hoops_ARSAS[c].y - _hoops_PRSAS*_hoops_ARSAS[a].y) * _hoops_CRSAS) * _hoops_PASAS;
			_hoops_ARSAS[c].z = _hoops_SRSAS;
		}
		_hoops_GGSAS (nr, &_hoops_ARSAS[0], 1, &_hoops_HGSAI, &_hoops_ARSAS[1], 1, &_hoops_HGSAI, &_hoops_ARSAS[2], 1, &_hoops_HGSAI, _hoops_CIHIA, _hoops_PGSAS);
		return;
	}

	_hoops_AGRSH = _hoops_SICAS->x;
	_hoops_PGRSH = _hoops_SICAS->y;
	_hoops_HGRSH = _hoops_SICAS->z;

	x1 = _hoops_GCCAS->x;
	_hoops_AGSIR = _hoops_GCCAS->y;
	_hoops_HGSIR = _hoops_GCCAS->z;

	x2 = _hoops_AGSAS->x;
	_hoops_PGSIR = _hoops_AGSAS->y;
	_hoops_IGSIR = _hoops_AGSAS->z;

	_hoops_HGSAS = x1 - _hoops_AGRSH; _hoops_CGSAS = _hoops_AGSIR - _hoops_PGRSH; _hoops_GRSAS = _hoops_HGSIR - _hoops_HGRSH;
	_hoops_IGSAS = x2 - _hoops_AGRSH; _hoops_SGSAS = _hoops_PGSIR - _hoops_PGRSH; _hoops_RRSAS = _hoops_IGSIR - _hoops_HGRSH;

	plane.a = _hoops_CGSAS * _hoops_RRSAS - _hoops_GRSAS * _hoops_SGSAS;
	plane.b = _hoops_GRSAS * _hoops_IGSAS - _hoops_HGSAS * _hoops_RRSAS;
	plane.c = _hoops_HGSAS * _hoops_SGSAS - _hoops_CGSAS * _hoops_IGSAS;
	plane.d = -(plane.a*_hoops_AGRSH + plane.b*_hoops_PGRSH + plane.c*_hoops_HGRSH);

	if (_hoops_PGSAS < 0) {	/* _hoops_SHPR _hoops_GC */
		_hoops_CIHIA->x = sc->_hoops_AICAH.x;
		_hoops_CIHIA->y = sc->_hoops_AICAH.y;

		if (plane.c == 0.0f)
			_hoops_CIHIA->z = MAX_FLOAT;
		else
			_hoops_CIHIA->z = (plane.a * sc->_hoops_AICAH.x + plane.b * sc->_hoops_AICAH.y + plane.d) /
					 -plane.c;
	}
	else {						/* _hoops_GSSP _hoops_GC */
		float	sz = 0.5f * (sc->bounding.hither + sc->bounding.yon);

		_hoops_CIHIA->x = sc->_hoops_AICAH.x;
		_hoops_CIHIA->y = sc->_hoops_AICAH.y;
		_hoops_CIHIA->z = sz;

		if (_hoops_PGSAS == 0) {		/* _hoops_SPCR */
			if (plane.a == 0.0f)
				_hoops_CIHIA->x = MAX_FLOAT;
			else
				_hoops_CIHIA->x = (plane.b * sc->_hoops_AICAH.y + plane.c * sz + plane.d) /
						 -plane.a;
		}
		else if (_hoops_PGSAS == 1) { /* _hoops_GHCR */
			if (plane.b == 0.0f)
				_hoops_CIHIA->y = MAX_FLOAT;
			else
				_hoops_CIHIA->y = (plane.a * sc->_hoops_AICAH.x + plane.c * sz + plane.d) /
						 -plane.b;
		}
		else {							/* _hoops_AHCR */
			if (plane.c == 0.0f)
				_hoops_CIHIA->z = MAX_FLOAT;
			else
				_hoops_CIHIA->z = (plane.a * sc->_hoops_AICAH.x + plane.b * sc->_hoops_AICAH.y + plane.d) /
						 -plane.c;
		}
	}
}




local bool _hoops_APSAS (
	Net_Rendition const &		nr,
	_hoops_PCCCP alter	*	status,
	DC_Point const *			_hoops_SICAS,
	float						_hoops_PPSAS,
	_hoops_GRCAR const *			_hoops_RGSAS,
	DC_Point const *			_hoops_GCCAS,
	float						_hoops_HPSAS,
	_hoops_GRCAR const *			_hoops_CHPSH,
	DC_Point const *			_hoops_AGSAS,
	float						_hoops_IPSAS,
	_hoops_GRCAR const *			_hoops_SHPSH) {
	_hoops_ACCCP alter *	sc = status->sc;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	float						tc;
	float						_hoops_AGRSH, x1, _hoops_HSHGA,
								_hoops_PGRSH, _hoops_AGSIR, _hoops_ISHGA, yc,
								_hoops_HGRSH, _hoops_HGSIR,
								_hoops_PAISA, _hoops_IICPA;
	int							p1, p2, _hoops_HSPIR, _hoops_CPSAS;
	DC_Point const *			_hoops_GHPCP[3];
	DC_Point alter				_hoops_SPSAS[4];
	float alter					w[3];
	_hoops_GRCAR const *			_hoops_ARCAR[3];

	_hoops_GHPCP[0] = _hoops_SICAS;
	_hoops_GHPCP[1] = _hoops_GCCAS;
	_hoops_GHPCP[2] = _hoops_AGSAS;
	w[0] = _hoops_PPSAS;
	w[1] = _hoops_HPSAS;
	w[2] = _hoops_IPSAS;
	_hoops_ARCAR[0] = _hoops_RGSAS;
	_hoops_ARCAR[1] = _hoops_CHPSH;
	_hoops_ARCAR[2] = _hoops_SHPSH;

	/* _hoops_RH _hoops_HSPR _hoops_HRGR _hoops_GHSAS _hoops_IIHA _hoops_GPP _hoops_RHSAS (_hoops_CACH _hoops_CAPP) */
	_hoops_HSPIR = 0;
	for (p1=0; p1<3; p1++) {
		if (p1 == 2)
			p2 = 0;
		else
			p2 = p1 + 1;

		_hoops_AGRSH = _hoops_GHPCP[p1]->x;
		_hoops_PGRSH = _hoops_GHPCP[p1]->y;
		_hoops_HGRSH = _hoops_GHPCP[p1]->z;
		_hoops_PAISA = w[p1];

		x1 = _hoops_GHPCP[p2]->x;
		_hoops_AGSIR = _hoops_GHPCP[p2]->y;
		_hoops_HGSIR = _hoops_GHPCP[p2]->z;
		_hoops_IICPA = w[p2];

		if (BIT (*_hoops_ARCAR[p1], _hoops_IPCAR)) {
			float			_hoops_PASAS = 1.0f / _hoops_IHCR->_hoops_CHCR;

			if (BIT (*_hoops_ARCAR[p2], _hoops_IPCAR))
				continue;

			/* _hoops_CAHA _hoops_IRS _hoops_RIRA _hoops_RA _hoops_IH _hoops_GGR-_hoops_RIPS-_hoops_IIGR-_hoops_RH-_hoops_RHC, _hoops_PSCR _hoops_GHCH _hoops_HPP _hoops_SGS _hoops_SRSCI */
			tc = (_hoops_IHCR->_hoops_CHCR - _hoops_PAISA) / (_hoops_IICPA - _hoops_PAISA);
			_hoops_SPSAS[_hoops_HSPIR].x = (_hoops_AGRSH + (x1*_hoops_IICPA - _hoops_AGRSH) * tc) * _hoops_PASAS;
			_hoops_SPSAS[_hoops_HSPIR].y = (_hoops_PGRSH + (_hoops_AGSIR*_hoops_IICPA - _hoops_PGRSH) * tc) * _hoops_PASAS;
			_hoops_SPSAS[_hoops_HSPIR].z = (_hoops_HGRSH + (_hoops_HGSIR*_hoops_IICPA - _hoops_HGRSH) * tc) * _hoops_PASAS;
			_hoops_HSPIR++;
		}
		else {
			float			_hoops_PASAS = 1.0f / _hoops_IHCR->_hoops_CHCR;

			_hoops_SPSAS[_hoops_HSPIR].x = _hoops_AGRSH;
			_hoops_SPSAS[_hoops_HSPIR].y = _hoops_PGRSH;
			_hoops_SPSAS[_hoops_HSPIR].z = _hoops_HGRSH;
			_hoops_HSPIR++;

			if (BIT (*_hoops_ARCAR[p2], _hoops_IPCAR)) {
				tc = (_hoops_IHCR->_hoops_CHCR - _hoops_PAISA) / (_hoops_IICPA - _hoops_PAISA);
				_hoops_SPSAS[_hoops_HSPIR].x = (_hoops_AGRSH*_hoops_PAISA + (x1 - _hoops_AGRSH*_hoops_PAISA) * tc) * _hoops_PASAS;
				_hoops_SPSAS[_hoops_HSPIR].y = (_hoops_PGRSH*_hoops_PAISA + (_hoops_AGSIR - _hoops_PGRSH*_hoops_PAISA) * tc) * _hoops_PASAS;
				_hoops_SPSAS[_hoops_HSPIR].z = (_hoops_HGRSH*_hoops_PAISA + (_hoops_HGSIR - _hoops_HGRSH*_hoops_PAISA) * tc) * _hoops_PASAS;
				_hoops_HSPIR++;
			}
		}
	}

	_hoops_CPSAS = 0;

	for (p1=0; p1<_hoops_HSPIR; p1++) {
		if (p1 == _hoops_HSPIR-1)
			p2 = 0;
		else
			p2 = p1+1;

		_hoops_AGRSH = _hoops_SPSAS[p1].x;
		_hoops_PGRSH = _hoops_SPSAS[p1].y;
		_hoops_HGRSH = _hoops_SPSAS[p1].z;

		x1 = _hoops_SPSAS[p2].x;
		_hoops_AGSIR = _hoops_SPSAS[p2].y;
		_hoops_HGSIR = _hoops_SPSAS[p2].z;

		/* _hoops_ACGR _hoops_RH _hoops_HISGR _hoops_PPSR */

		_hoops_HSHGA = x1 - _hoops_AGRSH;
		_hoops_ISHGA = _hoops_AGSIR - _hoops_PGRSH;

		tc = _hoops_HSHGA*_hoops_HSHGA + _hoops_ISHGA*_hoops_ISHGA; /* _hoops_GRAS _hoops_PCHAS */
		if (tc < 0.000001f) {
			/* _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_PPSR, _hoops_HAR _hoops_IRS _hoops_III! */
			yc = _hoops_PGRSH;
		}
		else {
			tc = (_hoops_HSHGA * (sc->_hoops_AICAH.x - _hoops_AGRSH) + _hoops_ISHGA * (sc->_hoops_AICAH.y - _hoops_PGRSH)) / tc;

			/* _hoops_IRHH _hoops_RCRR _hoops_SR'_hoops_ASAR _hoops_HCHAR _hoops_GIAA _hoops_RH _hoops_III **_hoops_CAGH** ... */
			if (tc <= 0.0f)
				yc = _hoops_PGRSH;
			else if (tc >= 1.0f)
				yc = _hoops_AGSIR;
			else
				yc = _hoops_PGRSH + _hoops_ISHGA * tc;
		}

		/* _hoops_PRIA _hoops_ASSA/_hoops_SIPP */

		if (yc >= sc->_hoops_AICAH.y) {
			/* (_hoops_IIH _hoops_CHR _hoops_PAHH _hoops_CGHCP _hoops_HHGS _hoops_ARI) */
			if (_hoops_AGRSH <= sc->_hoops_AICAH.x) {
				if (sc->_hoops_AICAH.x < x1) _hoops_CPSAS++;
			}
			else if (x1 <= sc->_hoops_AICAH.x) {
				if (sc->_hoops_AICAH.x < _hoops_AGRSH) _hoops_CPSAS++;
			}
		}
	}
	if (_hoops_CPSAS == 1)
		return true;
	else
		return false;
}

local void _hoops_AHSAS (
	Net_Rendition const &		nr,
	Tristrip const *			ts) {
	UNREFERENCED (nr);
	UNREFERENCED (ts);
}

local void _hoops_PHSAS (
	Net_Rendition const &		nr,
	_hoops_PCCCP alter	*	status,
	_hoops_SHCAS alter *		_hoops_HCCAS,
	DC_Point const *			_hoops_SICAS,
	float alter					_hoops_PAISA,
	_hoops_GRCAR const *			_hoops_RGSAS,
	DC_Point const *			_hoops_GCCAS,
	float alter					_hoops_IICPA,
	_hoops_GRCAR const *			_hoops_CHPSH,
	bool						_hoops_HHSAS,
	bool						_hoops_ACP,
	int							_hoops_PGSAS) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_ACCCP alter *	sc = status->sc;
	_hoops_CPPAS alter *			_hoops_ASCAS = &status->_hoops_CCCCP;
	float						_hoops_GPCH = sc->_hoops_AICAH.x;
	float						_hoops_RPCH = sc->_hoops_AICAH.y;
	float						sz = 0.5f * (sc->bounding.hither + sc->bounding.yon);
	float						tc;
	float						_hoops_AGRSH, x1, _hoops_HSHGA, xc, _hoops_GPHAS,
								_hoops_PGRSH, _hoops_AGSIR, _hoops_ISHGA, yc, _hoops_RPHAS,
								_hoops_HGRSH, _hoops_HGSIR, _hoops_CSHGA, zc = 0;
	float						_hoops_CIPAS,
								_hoops_CIGGA,
								_hoops_SIGGA,
								_hoops_PHHAS;
	_hoops_IAPA const *	_hoops_HRCAR = null;

	if (BIT (_hoops_IHCR->flags, _hoops_CSP))
		_hoops_HRCAR = _hoops_IHCR->_hoops_RGH->_hoops_PHCA;

	_hoops_HCCAS->_hoops_RICAS = false;
	_hoops_HCCAS->_hoops_GICAS = 0;
	_hoops_HCCAS->_hoops_CIPAS = MAX_FLOAT;
	_hoops_HCCAS->tc = 0.0f;

	if (_hoops_ACP)
		_hoops_ASCAS = &status->_hoops_GHPAS;

	if (sc->_hoops_RAPAS != null) {
		Point						points[2];
		_hoops_GPCIH alter * alter *		_hoops_PRHAS;
		int							_hoops_HRHAS;
		int							_hoops_IRHAS;

		points[0].x = _hoops_SICAS->x;
		points[0].y = _hoops_SICAS->y;
		points[0].z = _hoops_SICAS->z;

		points[1].x = _hoops_GCCAS->x;
		points[1].y = _hoops_GCCAS->y;
		points[1].z = _hoops_GCCAS->z;

		_hoops_HRHAS = HI_Create_Polyglin_Wings (2, points,
													  false, _hoops_GAPAS,
													  &_hoops_PRHAS);
		_hoops_IRHAS = HI_Wings_Intersect (_hoops_HRHAS, _hoops_PRHAS,
										  sc->_hoops_CAPAS, sc->_hoops_SAPAS);

		HI_Free_Wings (_hoops_HRHAS, _hoops_PRHAS);

		if (_hoops_IRHAS) {
			if (status->_hoops_IPRI == NULL ||
				status->_hoops_IPRI->type != _hoops_SCIP ||
				!_hoops_CICAS (status, _hoops_SICAS, _hoops_GCCAS)) {
				if (_hoops_SICAS->z < _hoops_GCCAS->z)
					_hoops_HGRSH = _hoops_SICAS->z;
				else
					_hoops_HGRSH = _hoops_GCCAS->z;

				_hoops_ASCAS->_hoops_HISAP = 0.0f;		/* _hoops_SHR _hoops_PPPSR _hoops_RHHR */
				_hoops_ASCAS->_hoops_RCSAP = _hoops_HGRSH;

				/* _hoops_AAH _hoops_AHGC _hoops_GPP _hoops_PHRHA _hoops_GPHA */
				if (BIT (*_hoops_CHPSH, _hoops_IPCAR)) {
					_hoops_ASCAS->vertex1 = _hoops_SICAS;
					_hoops_ASCAS->vertex2 = _hoops_GCCAS;
				}
				else if (BIT (*_hoops_RGSAS, _hoops_IPCAR)) {
					_hoops_ASCAS->vertex1 = _hoops_GCCAS;
					_hoops_ASCAS->vertex2 = _hoops_SICAS;
				}
				else {
					_hoops_ASCAS->vertex1 = _hoops_SICAS;
					_hoops_ASCAS->vertex2 = _hoops_GCCAS;
				}

				_hoops_HCCAS->_hoops_CIPAS = 0.0f;
				_hoops_HCCAS->_hoops_RICAS = true;

				return;
			}

			if (_hoops_IRHAS) {
				/* _hoops_CGH _hoops_SHH _hoops_SHSS _hoops_IS _hoops_AA _hoops_CPHP _hoops_AHGSP _hoops_ARI? */
			}
		}

		/* _hoops_HPRAR _hoops_RHIR _hoops_IS _hoops_RH "_hoops_ACCGI" _hoops_ISPR */
		/* _hoops_PIP _hoops_SGS _hoops_RH "_hoops_RHCH" _hoops_IIGR _hoops_RH _hoops_SCIRA _hoops_HRGR _hoops_HAR _hoops_GGSP, _hoops_CR _hoops_IRS */
		/* "_hoops_HIASI" _hoops_GHSHA _hoops_ISPH (_hoops_IHSAS, _hoops_PGSH, _hoops_RGGIR, _hoops_AHI) _hoops_GHCA _hoops_HS */
		/* _hoops_IRS _hoops_SCPH _hoops_PGAP _hoops_CHSAS _hoops_RH "_hoops_RHCH" _hoops_SIHH _hoops_GPGS _hoops_RH */
		/* _hoops_HPHR _hoops_ISPH.	 _hoops_RIIA, _hoops_SR _hoops_HS _hoops_IS _hoops_SGH _hoops_IRS _hoops_HPHR _hoops_PPSR */

		_hoops_GPCH = sc->_hoops_RAPAS->x;
		_hoops_RPCH = sc->_hoops_RAPAS->y;
	}

	/* _hoops_RCSPR _hoops_HSPIP _hoops_ISCC _hoops_SHSAS _hoops_GISAS _hoops_RISAS _hoops_RRCII _hoops_AISAS._hoops_IHRPR
	 *
	 * _hoops_IPCP _hoops_CIIA _hoops_SSCP _hoops_RPII _hoops_HGAS _hoops_IS '_hoops_PISAS'. _hoops_HAIA _hoops_HSAGA _hoops_HRGR _hoops_GCPRA.
	 */

	_hoops_AGRSH = _hoops_SICAS->x;
	_hoops_PGRSH = _hoops_SICAS->y;
	_hoops_HGRSH = _hoops_SICAS->z;

	x1 = _hoops_GCCAS->x;
	_hoops_AGSIR = _hoops_GCCAS->y;
	_hoops_HGSIR = _hoops_GCCAS->z;

	if (BIT (*_hoops_RGSAS, _hoops_IPCAR)) {
		float			_hoops_PASAS = 1.0f / _hoops_IHCR->_hoops_CHCR;

		if (BIT (*_hoops_CHPSH, _hoops_IPCAR))
			return;	 /* _hoops_SCACR */
		/* _hoops_CAHA _hoops_IRS _hoops_RIRA _hoops_RA _hoops_IH _hoops_GGR-_hoops_RIPS-_hoops_IIGR-_hoops_RH-_hoops_RHC, _hoops_PSCR _hoops_GHCH _hoops_HPP _hoops_SGS _hoops_SRSCI */
		tc = (_hoops_IHCR->_hoops_CHCR - _hoops_PAISA) / (_hoops_IICPA - _hoops_PAISA);
		_hoops_AGRSH = (_hoops_AGRSH + (x1*_hoops_IICPA - _hoops_AGRSH) * tc) * _hoops_PASAS;
		_hoops_PGRSH = (_hoops_PGRSH + (_hoops_AGSIR*_hoops_IICPA - _hoops_PGRSH) * tc) * _hoops_PASAS;
		_hoops_HGRSH = (_hoops_HGRSH + (_hoops_HGSIR*_hoops_IICPA - _hoops_HGRSH) * tc) * _hoops_PASAS;
	}
	else if (BIT (*_hoops_CHPSH, _hoops_IPCAR)) {
		float			_hoops_PASAS = 1.0f / _hoops_IHCR->_hoops_CHCR;

		tc = (_hoops_IHCR->_hoops_CHCR - _hoops_PAISA) / (_hoops_IICPA - _hoops_PAISA);
		x1 = (_hoops_AGRSH*_hoops_PAISA + (x1 - _hoops_AGRSH*_hoops_PAISA) * tc) * _hoops_PASAS;
		_hoops_AGSIR = (_hoops_PGRSH*_hoops_PAISA + (_hoops_AGSIR - _hoops_PGRSH*_hoops_PAISA) * tc) * _hoops_PASAS;
		_hoops_HGSIR = (_hoops_HGRSH*_hoops_PAISA + (_hoops_HGSIR - _hoops_HGRSH*_hoops_PAISA) * tc) * _hoops_PASAS;
	}

	/* 5) _hoops_ACGR _hoops_RH _hoops_HISGR _hoops_PPSR _hoops_IS _hoops_RH _hoops_HASRH _hoops_GPP _hoops_RH _hoops_PRISA _hoops_III ==

		_hoops_AHGHR _hoops_RH _hoops_PRISA _hoops_III _hoops_CGSSR:

			_hoops_SISR = _hoops_HIHAS + _hoops_IIHAS * _hoops_RA				(_hoops_IIHAS = _hoops_RCRIA - _hoops_HIHAS)
			_hoops_HAPC = _hoops_CIHAS + _hoops_SIHAS * _hoops_RA				(_hoops_SIHAS = _hoops_GSRIA - _hoops_CIHAS)


		_hoops_AHGHR _hoops_RH _hoops_IHGP _hoops_GIRA _hoops_HII _hoops_IRS _hoops_III _hoops_IS _hoops_IRS _hoops_PPSR (_hoops_GCHAS, _hoops_RCHAS):

			 2			 2			 2
			_hoops_PCCIR  = (_hoops_SISR - _hoops_GCHAS)  + (_hoops_HAPC - _hoops_RCHAS)

																   2
		_hoops_SPAA _hoops_RH _hoops_RA-_hoops_PIRA _hoops_HPGR _hoops_RH _hoops_HISGR _hoops_CCHRA - _hoops_RH _hoops_AASC _hoops_IIGR _hoops_PCCIR	 - _hoops_HRGR,
		_hoops_RRPS _hoops_IS _hoops_GAIPA:

				  _hoops_IIHAS * (_hoops_GCHAS - _hoops_HIHAS) + _hoops_SIHAS * (_hoops_RCHAS - _hoops_CIHAS)
			_hoops_ACHAS =  -------------------------------
							   2	 2
							 _hoops_IIHAS	 + _hoops_SIHAS

	*/

	_hoops_HSHGA = x1 - _hoops_AGRSH;
	_hoops_ISHGA = _hoops_AGSIR - _hoops_PGRSH;

	if (_hoops_PGSAS < 0) {	/* _hoops_SHPR _hoops_GC */
		tc = _hoops_HSHGA*_hoops_HSHGA + _hoops_ISHGA*_hoops_ISHGA; /* _hoops_GRAS _hoops_PCHAS */
		if (tc < 0.000001f) {
			/* _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_PPSR, _hoops_HAR _hoops_IRS _hoops_III! */
			xc = _hoops_AGRSH;
			yc = _hoops_PGRSH;
			_hoops_HCCAS->tc = tc = 0.0f;
		}
		else {
			tc = (_hoops_HSHGA * (_hoops_GPCH - _hoops_AGRSH) + _hoops_ISHGA * (_hoops_RPCH - _hoops_PGRSH)) / tc;

			/* _hoops_IRHH _hoops_RCRR _hoops_SR'_hoops_ASAR _hoops_HCHAR _hoops_GIAA _hoops_RH _hoops_III **_hoops_CAGH** ... */
			if (tc <= 0.0f) {
				_hoops_HCCAS->tc = tc = 0.0f;
				xc = _hoops_AGRSH;
				yc = _hoops_PGRSH;
			}
			else if (tc >= 1.0f) {
				_hoops_HCCAS->tc = tc = 1.0f;
				xc = x1;
				yc = _hoops_AGSIR;
			}
			else {
				_hoops_HCCAS->tc = tc;
				xc = _hoops_AGRSH + _hoops_HSHGA * tc;
				yc = _hoops_PGRSH + _hoops_ISHGA * tc;
			}
		}
	}
	else {	/* _hoops_GSSP _hoops_GC */
		_hoops_CSHGA = _hoops_HGSIR - _hoops_HGRSH;

		tc = _hoops_HSHGA*_hoops_HSHGA + _hoops_ISHGA*_hoops_ISHGA + _hoops_CSHGA*_hoops_CSHGA; /* _hoops_GRAS _hoops_PCHAS */
		if (tc < 0.000001f) {
			/* _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_PPSR, _hoops_HAR _hoops_IRS _hoops_III! */
			xc = _hoops_AGRSH;
			yc = _hoops_PGRSH;
			zc = _hoops_HGRSH;
			_hoops_HCCAS->tc = tc = 0.0f;
		}
		else {
			tc = (_hoops_HSHGA * (_hoops_GPCH - _hoops_AGRSH) + _hoops_ISHGA * (_hoops_RPCH - _hoops_PGRSH) + _hoops_CSHGA * (sz - _hoops_HGRSH)) / tc;

			/* _hoops_IRHH _hoops_RCRR _hoops_SR'_hoops_ASAR _hoops_HCHAR _hoops_GIAA _hoops_RH _hoops_III **_hoops_CAGH** ... */
			if (tc <= 0.0f) {
				_hoops_HCCAS->tc = tc = 0.0f;
				xc = _hoops_AGRSH;
				yc = _hoops_PGRSH;
				zc = _hoops_HGRSH;
			}
			else if (tc >= 1.0f) {
				_hoops_HCCAS->tc = tc = 1.0f;
				xc = x1;
				yc = _hoops_AGSIR;
				zc = _hoops_HGSIR;
			}
			else {
				_hoops_HCCAS->tc = tc;
				xc = _hoops_AGRSH + _hoops_HSHGA * tc;
				yc = _hoops_PGRSH + _hoops_ISHGA * tc;
				zc = _hoops_HGRSH + _hoops_CSHGA * tc;
			}
		}
	}

	/* 5.5) _hoops_PRIA _hoops_ASSA/_hoops_SIPP _hoops_RPGP _hoops_IH _hoops_HSSP _hoops_PIHAS */
	/*		(_hoops_AISRA, _hoops_RPR _hoops_RSH _hoops_AHPH _hoops_SPPR _hoops_RIH _hoops_ACCGI) */
	if (_hoops_PGSAS < 0) {	/* _hoops_SHPR _hoops_GC */
		if (yc >= _hoops_RPCH) {
			/* (_hoops_IIH _hoops_CHR _hoops_PAHH _hoops_CGHCP _hoops_HHGS _hoops_ARI) */
			if (_hoops_AGRSH <= _hoops_GPCH) {
				if (_hoops_GPCH < x1) _hoops_HCCAS->_hoops_GICAS = 1;
			}
			else if (x1 <= _hoops_GPCH) {
				if (_hoops_GPCH < _hoops_AGRSH) _hoops_HCCAS->_hoops_GICAS = 1;
			}
		}
	}
	else {						/* _hoops_GSSP _hoops_GC */
		if (_hoops_PGSAS == 0) {			/* _hoops_SPCR */
			if (yc >= _hoops_RPCH) {
				/* (_hoops_IIH _hoops_CHR _hoops_PAHH _hoops_CGHCP _hoops_HHGS _hoops_ARI) */
				if (_hoops_HGRSH <= sz) {
					if (sz < _hoops_HGSIR) _hoops_HCCAS->_hoops_GICAS = 1;
				}
				else if (_hoops_HGSIR <= sz) {
					if (sz < _hoops_HGRSH) _hoops_HCCAS->_hoops_GICAS = 1;
				}
			}
		}
		else if (_hoops_PGSAS == 1) {		/* _hoops_GHCR */
			if (zc >= sz) {
				/* (_hoops_IIH _hoops_CHR _hoops_PAHH _hoops_CGHCP _hoops_HHGS _hoops_ARI) */
				if (_hoops_AGRSH <= _hoops_GPCH) {
					if (_hoops_GPCH < x1) _hoops_HCCAS->_hoops_GICAS = 1;
				}
				else if (x1 <= _hoops_GPCH) {
					if (_hoops_GPCH < _hoops_AGRSH) _hoops_HCCAS->_hoops_GICAS = 1;
				}
			}
		}
		else {								/* _hoops_AHCR */
			if (yc >= _hoops_RPCH) {
				/* (_hoops_IIH _hoops_CHR _hoops_PAHH _hoops_CGHCP _hoops_HHGS _hoops_ARI) */
				if (_hoops_AGRSH <= _hoops_GPCH) {
					if (_hoops_GPCH < x1) _hoops_HCCAS->_hoops_GICAS = 1;
				}
				else if (x1 <= _hoops_GPCH) {
					if (_hoops_GPCH < _hoops_AGRSH) _hoops_HCCAS->_hoops_GICAS = 1;
				}
			}
		}
	}

	/* _hoops_RPP _hoops_SCH _hoops_CSAP _hoops_IRS _hoops_SCIRA _hoops_GHSHA, _hoops_SR _hoops_RGAR _hoops_ASPC _hoops_RHIR _hoops_ARI _hoops_IS _hoops_HGCR */
	/* _hoops_RH _hoops_ACCGI _hoops_ISPR */
	if (sc->_hoops_RAPAS != null)
		return;

	/* 6) _hoops_CCHAS _hoops_RPGP _hoops_GPP _hoops_RH _hoops_HISGR _hoops_PPSR */

	_hoops_GPHAS = (xc - _hoops_GPCH) / sc->_hoops_HICAH.x;
	_hoops_RPHAS = (yc - _hoops_RPCH) / sc->_hoops_HICAH.y;
	_hoops_HCCAS->_hoops_CIPAS = _hoops_CIPAS = _hoops_GPHAS*_hoops_GPHAS + _hoops_RPHAS*_hoops_RPHAS;


	if (!status->_hoops_CHPAS &&
		_hoops_CIPAS >= _hoops_ASCAS->_hoops_HISAP)
		return;


	/* 6.0001) _hoops_CAIP'_hoops_RA _hoops_IIS _hoops_CSCAS _hoops_HISAS _hoops_SPPR _hoops_PHHR _hoops_ASSPR */

	if (status->_hoops_IPRI != null &&
		status->_hoops_IPRI->type == _hoops_SCIP &&
		!_hoops_HHSAS && !_hoops_ACP) {
		if (_hoops_CICAS (status, _hoops_SICAS, _hoops_GCCAS)) {
			_hoops_HCCAS->_hoops_CIPAS = MAX_FLOAT; /* _hoops_IISAS _hoops_CISAS */
			return; /* _hoops_SCACR */
		}
	}

	/* 7) _hoops_IHHSI _hoops_RH _hoops_III _hoops_ACSRR _hoops_RH _hoops_HPPA _hoops_GHC, _hoops_RPP _hoops_GII */

	do {
		_hoops_CIGGA = 0.0f;
		_hoops_SIGGA = 1.0f;

		if (_hoops_HRCAR != null) {
			_hoops_GPPA const		*_hoops_IRCAR;

			_hoops_IRCAR = _hoops_HRCAR->_hoops_APPA;
			do {
				float							_hoops_SCHAS, _hoops_GSHAS;
				float							_hoops_AHHAS;

				_hoops_SCHAS = _hoops_IRCAR->_hoops_SPPA.a * _hoops_AGRSH + _hoops_IRCAR->_hoops_SPPA.b * _hoops_PGRSH +
						_hoops_IRCAR->_hoops_SPPA.c * _hoops_HGRSH + _hoops_IRCAR->_hoops_SPPA.d;
				_hoops_GSHAS = _hoops_IRCAR->_hoops_SPPA.a * x1 + _hoops_IRCAR->_hoops_SPPA.b * _hoops_AGSIR +
						_hoops_IRCAR->_hoops_SPPA.c * _hoops_HGSIR + _hoops_IRCAR->_hoops_SPPA.d;

				if (_hoops_SCHAS <= 0.0f) { /* _hoops_RSHAS _hoops_HRGR _hoops_PGPAA */
					if (_hoops_GSHAS <= 0.0f) {
						/* _hoops_PPAAI _hoops_HRGR _hoops_GACC _hoops_PGPAA. _hoops_GRSH _hoops_AGAPR. */
					}
					else {
						/* _hoops_PPAAI _hoops_HRGR _hoops_HAR _hoops_PGPAA. _hoops_PPRII _hoops_CCPH _hoops_ASHAS. */

						/* _hoops_IPCP _hoops_SGSSR _hoops_PPSR _hoops_IIGR _hoops_RH _hoops_ISHA _hoops_PPR _hoops_PSHAS _hoops_IPPA. */
						/* (_hoops_HSHAS _hoops_PPR _hoops_ISHAS _hoops_PAHHP _hoops_GGR _hoops_HRASR, _hoops_HIS _hoops_PAH'_hoops_RA _hoops_GHCH _hoops_HPP 0) */
						_hoops_AHHAS = _hoops_SCHAS / (_hoops_SCHAS - _hoops_GSHAS);

						if (_hoops_AHHAS < _hoops_SIGGA) {
							_hoops_SIGGA = _hoops_AHHAS;
							if (_hoops_CIGGA >= _hoops_SIGGA) break; /* _hoops_AIIA _hoops_PIRC _hoops_RAAP */
						}
					}
				}
				else {
					/* _hoops_RSHAS _hoops_HRGR _hoops_HAR _hoops_PGPAA */
					if (_hoops_GSHAS > 0.0f) {
						/* _hoops_PPAAI _hoops_HRGR _hoops_GACC _hoops_HAR _hoops_PGPAA. _hoops_GRSH _hoops_AGAPR. */
						_hoops_SIGGA = -999.0f; /* (_hoops_HHSA '_hoops_SAS' _hoops_CAPP) */
						break;
					}
					else {
						/* _hoops_PPAAI *_hoops_HRGR* _hoops_PGPAA. _hoops_PPRII _hoops_CCPH _hoops_CSHAS. */

						/* _hoops_IPCP _hoops_SGSSR _hoops_PPSR _hoops_IIGR _hoops_RH _hoops_ISHA _hoops_PPR _hoops_PSHAS _hoops_IPPA. */
						/* (_hoops_HSHAS _hoops_PPR _hoops_ISHAS _hoops_PAHHP _hoops_GGR _hoops_HRASR, _hoops_HIS _hoops_PSHAS _hoops_PAH'_hoops_RA _hoops_GHCH _hoops_HPP 0)*/
						_hoops_AHHAS = _hoops_SCHAS / (_hoops_SCHAS - _hoops_GSHAS);

						if (_hoops_AHHAS > _hoops_CIGGA) {
							_hoops_CIGGA = _hoops_AHHAS;	  /* _hoops_IHHSI _hoops_GH _hoops_HII _hoops_RH _hoops_HISAR _hoops_RSGR */
							if (_hoops_CIGGA >= _hoops_SIGGA) break; /* _hoops_AIIA _hoops_PIRC _hoops_RAAP */
						}
					}
				}
			} while ((_hoops_IRCAR = _hoops_IRCAR->next) != null);

			_hoops_HRCAR = _hoops_HRCAR->next;
			if (_hoops_CIGGA >= _hoops_SIGGA) continue; /* _hoops_HCR _hoops_PPRGA, _hoops_HPPR _hoops_HPIH _hoops_ARP (_hoops_RPP _hoops_GII) */
		}

		/* 8) _hoops_HSPH _hoops_HISGR _hoops_IS _hoops_RH _hoops_IASC _hoops_AHCRR _hoops_IS _hoops_GHGPR _hoops_ISPR */

		if (_hoops_HSHGA > 0.0f) {
			if (_hoops_AGRSH < sc->bounding.left) {
				_hoops_PHHAS = (sc->bounding.left - _hoops_AGRSH) / _hoops_HSHGA;
				if (_hoops_CIGGA < _hoops_PHHAS) _hoops_CIGGA = _hoops_PHHAS;
			}
			if (x1 > sc->bounding.right) {
				_hoops_PHHAS = (sc->bounding.right - _hoops_AGRSH) / _hoops_HSHGA;
				if (_hoops_SIGGA > _hoops_PHHAS) _hoops_SIGGA = _hoops_PHHAS;
			}
		}
		else {
			if (x1 < sc->bounding.left) {
				if (_hoops_HSHGA == 0.0f) continue;
				_hoops_PHHAS = (sc->bounding.left - _hoops_AGRSH) / _hoops_HSHGA;
				if (_hoops_SIGGA > _hoops_PHHAS) _hoops_SIGGA = _hoops_PHHAS;
			}
			if (_hoops_AGRSH > sc->bounding.right) {
				if (_hoops_HSHGA == 0.0f) continue;
				_hoops_PHHAS = (sc->bounding.right - _hoops_AGRSH) / _hoops_HSHGA;
				if (_hoops_CIGGA < _hoops_PHHAS) _hoops_CIGGA = _hoops_PHHAS;
			}
		}

		if (_hoops_ISHGA > 0.0f) {
			if (_hoops_PGRSH < sc->bounding.bottom) {
				_hoops_PHHAS = (sc->bounding.bottom - _hoops_PGRSH) / _hoops_ISHGA;
				if (_hoops_CIGGA < _hoops_PHHAS) _hoops_CIGGA = _hoops_PHHAS;
			}
			if (_hoops_AGSIR > sc->bounding.top) {
				_hoops_PHHAS = (sc->bounding.top - _hoops_PGRSH) / _hoops_ISHGA;
				if (_hoops_SIGGA > _hoops_PHHAS) _hoops_SIGGA = _hoops_PHHAS;
			}
		}
		else {
			if (_hoops_AGSIR < sc->bounding.bottom) {
				if (_hoops_ISHGA == 0.0f) continue;
				_hoops_PHHAS = (sc->bounding.bottom - _hoops_PGRSH) / _hoops_ISHGA;
				if (_hoops_SIGGA > _hoops_PHHAS) _hoops_SIGGA = _hoops_PHHAS;
			}
			if (_hoops_PGRSH > sc->bounding.top) {
				if (_hoops_ISHGA == 0.0f) continue;
				_hoops_PHHAS = (sc->bounding.top - _hoops_PGRSH) / _hoops_ISHGA;
				if (_hoops_CIGGA < _hoops_PHHAS) _hoops_CIGGA = _hoops_PHHAS;
			}
		}

		_hoops_CSHGA = _hoops_HGSIR - _hoops_HGRSH;

		if (_hoops_CSHGA > 0.0f) {
			if (_hoops_HGRSH < sc->bounding.hither) {
				_hoops_PHHAS = (sc->bounding.hither - _hoops_HGRSH) / _hoops_CSHGA;
				if (_hoops_CIGGA < _hoops_PHHAS) _hoops_CIGGA = _hoops_PHHAS;
			}
			if (_hoops_HGSIR > sc->bounding.yon) {
				_hoops_PHHAS = (sc->bounding.yon - _hoops_HGRSH) / _hoops_CSHGA;
				if (_hoops_SIGGA > _hoops_PHHAS) _hoops_SIGGA = _hoops_PHHAS;
			}
		}
		else {
			if (_hoops_HGSIR < sc->bounding.hither) {
				if (_hoops_CSHGA == 0.0f) continue;
				_hoops_PHHAS = (sc->bounding.hither - _hoops_HGRSH) / _hoops_CSHGA;
				if (_hoops_SIGGA > _hoops_PHHAS) _hoops_SIGGA = _hoops_PHHAS;
			}
			if (_hoops_HGRSH > sc->bounding.yon) {
				if (_hoops_CSHGA == 0.0f) continue;
				_hoops_PHHAS = (sc->bounding.yon - _hoops_HGRSH) / _hoops_CSHGA;
				if (_hoops_CIGGA < _hoops_PHHAS) _hoops_CIGGA = _hoops_PHHAS;
			}
		}

		if (_hoops_CIGGA >= _hoops_SIGGA) continue; /* _hoops_HCR _hoops_PPRGA */


		/* 9) _hoops_CGP _hoops_SCH _hoops_GGHP _hoops_SACH - _hoops_RHSHA _hoops_IPCAH */

		if (tc < _hoops_CIGGA || tc > _hoops_SIGGA) {
			if (tc < _hoops_CIGGA)
				tc = _hoops_CIGGA;
			else
				tc = _hoops_SIGGA;

			_hoops_HCCAS->tc = tc;

			xc = _hoops_AGRSH + _hoops_HSHGA * tc;
			yc = _hoops_PGRSH + _hoops_ISHGA * tc;

			_hoops_GPHAS = (xc - _hoops_GPCH) / sc->_hoops_HICAH.x;
			_hoops_RPHAS = (yc - _hoops_RPCH) / sc->_hoops_HICAH.y;
			_hoops_HCCAS->_hoops_CIPAS = _hoops_CIPAS = _hoops_GPHAS*_hoops_GPHAS + _hoops_RPHAS*_hoops_RPHAS;
		}

		/* 10) _hoops_SSHAS _hoops_HCCHA. _hoops_GSIH _hoops_SCH. */

		if (_hoops_CIPAS < _hoops_ASCAS->_hoops_HISAP) {
			_hoops_ASCAS->_hoops_HISAP = _hoops_CIPAS;

			if (BIT (*_hoops_CHPSH, _hoops_IPCAR)) {
				_hoops_ASCAS->vertex1 = _hoops_SICAS;
				_hoops_ASCAS->vertex2 = _hoops_GCCAS;
			}
			else if (BIT (*_hoops_RGSAS, _hoops_IPCAR)) {
				_hoops_ASCAS->vertex1 = _hoops_GCCAS;
				_hoops_ASCAS->vertex2 = _hoops_SICAS;
			}
			else if (tc < 0.5f) {
				_hoops_ASCAS->vertex1 = _hoops_SICAS;
				_hoops_ASCAS->vertex2 = _hoops_GCCAS;
			}
			else {
				_hoops_ASCAS->vertex1 = _hoops_GCCAS;
				_hoops_ASCAS->vertex2 = _hoops_SICAS;
			}

			_hoops_ASCAS->_hoops_RCSAP = _hoops_HGRSH + _hoops_CSHGA*tc;

			_hoops_HCCAS->_hoops_RICAS = true;
		}
	} while (_hoops_HRCAR != null);
}


local void _hoops_SISAS (
	Net_Rendition const &		nr,
	Polyedge const *			pe,
	int							_hoops_GCSAS = -1) {
	int							_hoops_PHHA = pe->_hoops_PHHA;
	int const *					lengths = pe->lengths;
	int const *					_hoops_AIHA= pe->_hoops_AIHA;
	int							_hoops_HCGS = 0;
	int							length;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter *	sc = dc->_hoops_APHHP;
	_hoops_PCCCP alter	*	status = (_hoops_PCCCP alter *)nr->_hoops_SRA->_hoops_APHHP->_hoops_AICCP;
	struct _hoops_SHCAS		_hoops_HCCAS;
	DC_Point alter				*_hoops_SICAS,
								*_hoops_GCCAS,
								*_hoops_CGCAR;
	float						_hoops_PAISA, _hoops_IICPA, *ws;
	_hoops_GRCAR alter				*_hoops_RGSAS,
								*_hoops_CHPSH,
								*_hoops_RRCAR;
	_hoops_HCSIR alter *	_hoops_ICSIR = null;
	bool						_hoops_PSCAS;
	int							index;
	bool						_hoops_ACP;
	_hoops_CPPAS alter *			_hoops_ASCAS = &status->_hoops_CCCCP;

	_hoops_PSCAS = BIT (nr->transform_rendition->heuristics, _hoops_GAIRP);

	if (BIT (sc->options, _hoops_CRPAS)) {
		if (!sc->_hoops_GPPAS) {
			if (nr->_hoops_SAIR->_hoops_ASSIR != null)
				_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
			if (_hoops_ICSIR == null) {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									"Expected frame buffer not found");
				return;
			}
		}
	}

	_hoops_ACP = BIT (pe->_hoops_PPGI.flags, _hoops_IPACP);
	if (_hoops_ACP)
		_hoops_ASCAS = &status->_hoops_GHPAS;

	/* (_hoops_ACHSP _hoops_GACC _hoops_GCIS _hoops_PPGP-_hoops_SIGC _hoops_GRAA-_hoops_ASSIA _hoops_AHHA) */

	/* _hoops_SRGGR _hoops_ISCP _hoops_SIHC */
	_hoops_CGCAR = status->_hoops_CGCAR;
	ws = status->ws;
	_hoops_RRCAR = status->_hoops_RRCAR;

	if (!lengths)
		lengths = &pe->total;

	while (_hoops_PHHA-- > 0) {
		if (_hoops_AIHA)
			index = *_hoops_AIHA++;
		else
			index = _hoops_HCGS++;

		_hoops_SICAS = &_hoops_CGCAR[index];
		_hoops_PAISA = ws[index];
		_hoops_RGSAS = &_hoops_RRCAR[index];

		length = *lengths++ - 1;
		_hoops_PCCAR {
			bool		_hoops_RCSAS = true;

			if (_hoops_AIHA)
				index = *_hoops_AIHA++;
			else
				index = _hoops_HCGS++;
			_hoops_GCCAS = &_hoops_CGCAR[index];
			_hoops_IICPA = ws[index];
			_hoops_CHPSH = &_hoops_RRCAR[index];

			if (ANYBIT (*_hoops_RGSAS & *_hoops_CHPSH, ~_hoops_RPCAR))
				_hoops_RCSAS = false;
			else if (BIT (sc->options, _hoops_CRPAS)) {
				DC_Point						points[2];

				points[0].x = _hoops_SICAS->x;
				points[0].y = _hoops_SICAS->y;
				points[0].z = _hoops_SICAS->z;
				points[1].x = _hoops_GCCAS->x;
				points[1].y = _hoops_GCCAS->y;
				points[1].z = _hoops_GCCAS->z;

				if (BIT (*_hoops_RGSAS | *_hoops_CHPSH, _hoops_IPCAR)) {
					_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
					int				a, b;
					float			_hoops_PRSAS, _hoops_HRSAS;
					float			trim;
					float			_hoops_PASAS = 1.0f / _hoops_IHCR->_hoops_CHCR;

					/* _hoops_HAIHR _hoops_RSSA _hoops_HIS _hoops_SGS _hoops_PPSR _hoops_RAIGR _hoops_HRGR _hoops_GGR _hoops_RIPS _hoops_IIGR _hoops_RH _hoops_RHC
					 * _hoops_PPR _hoops_PPSR _hoops_IHAC _hoops_HRGR _hoops_GHIPR.
					 */
					if (_hoops_PAISA >= _hoops_IHCR->_hoops_CHCR) {
						a = 0;	_hoops_PRSAS = _hoops_PAISA;
						b = 1;	_hoops_HRSAS = _hoops_IICPA;
					}
					else {
						a = 1;	_hoops_PRSAS = _hoops_IICPA;
						b = 0;	_hoops_HRSAS = _hoops_PAISA;
					}

					trim = (_hoops_IHCR->_hoops_CHCR - _hoops_PRSAS) / (_hoops_HRSAS - _hoops_PRSAS);

					points[b].x = (_hoops_PRSAS*points[a].x + (points[b].x - _hoops_PRSAS*points[a].x) * trim) * _hoops_PASAS;
					points[b].y = (_hoops_PRSAS*points[a].y + (points[b].y - _hoops_PRSAS*points[a].y) * trim) * _hoops_PASAS;
					points[b].z = (_hoops_PRSAS*points[a].z + (points[b].z - _hoops_PRSAS*points[a].z) * trim) * _hoops_PASAS;
				}

				_hoops_IGRS (dc);
				if (sc->_hoops_GPPAS) {
					void *							_hoops_CCHSP;

					_hoops_CCHSP = _hoops_AACGH (nr, true);
					_hoops_SCGGA (nr, 2, points);
					_hoops_PACGH (nr, _hoops_CCHSP);

					_hoops_RCSAS =
						(_hoops_IACGH (nr, _hoops_CCHSP) > 0);
				}
				else {
					_hoops_ICSIR->input._hoops_PHHSP = 0;

					_hoops_SCGGA (nr, 2, points);

					_hoops_RCSAS = (_hoops_ICSIR->input._hoops_PHHSP > 0);
				}
				_hoops_SGRS (dc);
			}

			if (_hoops_RCSAS) {
				DC_Point	const		*_hoops_ACSAS;
				DC_Point	const		*_hoops_PCSAS;
				float					_hoops_IGIAS;

				_hoops_ACSAS = _hoops_ASCAS->vertex1;
				_hoops_PCSAS = _hoops_ASCAS->vertex2;
				_hoops_IGIAS = _hoops_ASCAS->_hoops_HISAP;
				if (status->_hoops_CHPAS)
					_hoops_ASCAS->_hoops_HISAP = sc->_hoops_GICAH;

				_hoops_PHSAS (nr, status, &_hoops_HCCAS, _hoops_SICAS, _hoops_PAISA, _hoops_RGSAS, _hoops_GCCAS, _hoops_IICPA, _hoops_CHPSH, !_hoops_ACP, _hoops_ACP, -1);

				if (_hoops_HCCAS._hoops_RICAS) {
					if (BIT (pe->_hoops_PPGI.flags, _hoops_IPACP)) {
						_hoops_ASCAS->face = pe->_hoops_PPGI._hoops_CPACP;
						status->_hoops_PHPAS = true;
					}
					else {
						_hoops_ASCAS->face = -1;
						status->_hoops_HHPAS = true;
					}

					/* _hoops_GGCR _hoops_IS _hoops_RGIAS _hoops_RPP _hoops_IRPR */
					if (status->_hoops_SHPAS)
						return;

					if (status->_hoops_CHPAS) {
						_hoops_AISAP *	_hoops_HHCAP;

						ALLOC (_hoops_HHCAP, _hoops_AISAP);
						_hoops_HHCAP->next = null;
						if (BIT (pe->_hoops_PPGI.flags, _hoops_IPACP)) {
							_hoops_HHCAP->_hoops_PISAP[0] = -1;
							_hoops_HHCAP->_hoops_PISAP[1] = pe->_hoops_PPGI._hoops_CPACP;
							if (_hoops_GCSAS == -1)	// _hoops_SHIR
								_hoops_HHCAP->_hoops_PISAP[2] = status->_hoops_IPRI->_hoops_AHSCC;
							else
								_hoops_HHCAP->_hoops_PISAP[2] = _hoops_GCSAS;
						}
						else {
							_hoops_HHCAP->_hoops_PISAP[0] = (int) (_hoops_ASCAS->vertex1 - _hoops_CGCAR);
							_hoops_HHCAP->_hoops_PISAP[1] = (int) (_hoops_ASCAS->vertex2 - _hoops_CGCAR);
							_hoops_HHCAP->_hoops_PISAP[2] = -1;
						}
						_hoops_HHCAP->_hoops_HISAP = _hoops_ASCAS->_hoops_HISAP;
						_hoops_HHCAP->_hoops_IISAP = _hoops_ASCAS->_hoops_RCSAP;
						_hoops_HHCAP->next = null;
						*status->_hoops_APPAS = _hoops_HHCAP;
						status->_hoops_APPAS = &_hoops_HHCAP->next;
						if (!_hoops_PSCAS && ++status->_hoops_PPPAS >=
								nr->_hoops_IRR->_hoops_CCIRP._hoops_SPHPR)
							status->_hoops_CHPAS = false;

						if (BIT (pe->_hoops_PPGI.flags, _hoops_IPACP))
							return;	// _hoops_PSP "_hoops_HPHR" _hoops_RCAHR, _hoops_SAHR _hoops_PRIA _hoops_RGR _hoops_SPR _hoops_RARP
					}
				}

				if (_hoops_IGIAS < _hoops_ASCAS->_hoops_HISAP) {
					/* _hoops_PGHC _hoops_RHHR _hoops_CSAP _hoops_GIH... */
					_hoops_ASCAS->vertex1 = _hoops_ACSAS;
					_hoops_ASCAS->vertex2 = _hoops_PCSAS;
					_hoops_ASCAS->_hoops_HISAP = _hoops_IGIAS;
				}
			}

			if (--length <= 0) break;

			_hoops_SICAS = _hoops_GCCAS;
			_hoops_PAISA = _hoops_IICPA;
			_hoops_RGSAS = _hoops_CHPSH;
		}
	}
}

local void _hoops_HCSAS (
	Net_Rendition const &		nr,
	Polyedge const *			pe) {
	_hoops_SISAS (nr, pe);
}


local void _hoops_ICSAS (
	Net_Rendition const &		nr,
	Tristrip const *			ts,
	int *						_hoops_CCSAS,
	int *						_hoops_SCSAS,
	float *						_hoops_GSSAS,
	float *						_hoops_RSSAS,
	int const *					_hoops_AGHAR) {
	int							_hoops_PHHA = ts->_hoops_PHHA;
	int const *					lengths = ts->lengths;
	int const *					_hoops_AIHA = ts->_hoops_AIHA;
	int const *					face_indices = ts->face_indices;
	struct _hoops_SHCAS		_hoops_ASSAS,
								_hoops_PSSAS,
								_hoops_HSSAS;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter *	sc = dc->_hoops_APHHP;
	DC_Point alter				*_hoops_SICAS, *_hoops_GCCAS, *_hoops_AGSAS, *_hoops_CGCAR;
	float						_hoops_PAISA, _hoops_IICPA, _hoops_CICPA, *ws;
	_hoops_GRCAR					*_hoops_RGSAS, *_hoops_CHPSH, *_hoops_SHPSH, *_hoops_RRCAR;
	_hoops_PCCCP alter	*	status;
	int							face = -1;
	bool						_hoops_ISSAS = BIT (sc->options, _hoops_IICAH);
	int							_hoops_PGSAS = -1;
	_hoops_HCSIR alter *	_hoops_ICSIR = null;
	int							index;

	_hoops_ASSAS._hoops_RICAS = false;
	_hoops_PSSAS._hoops_RICAS = false;
	_hoops_HSSAS._hoops_RICAS = false;
	_hoops_ASSAS._hoops_GICAS = 0;
	_hoops_PSSAS._hoops_GICAS = 0;
	_hoops_HSSAS._hoops_GICAS = 0;

	if (BIT (sc->options, _hoops_CRPAS)) {
		if (!sc->_hoops_GPPAS) {
			if (nr->_hoops_SAIR->_hoops_ASSIR != null)
				_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
			if (_hoops_ICSIR == null) {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									"Expected frame buffer not found");
				return;
			}
		}
	}

	/* (_hoops_ACHSP _hoops_GACC _hoops_GCIS _hoops_PPGP-_hoops_SIGC _hoops_GRAA-_hoops_ASSIA _hoops_AHHA) */

	/* _hoops_SRGGR _hoops_ISCP _hoops_SIHC */
	status = (_hoops_PCCCP alter *)nr->_hoops_SRA->_hoops_APHHP->_hoops_AICCP;
	_hoops_CGCAR = status->_hoops_CGCAR;
	ws = status->ws;
	_hoops_RRCAR = status->_hoops_RRCAR;

	if (_hoops_AGHAR == null &&
		BIT (nr->transform_rendition->flags, _hoops_IGSP) &&
		!BIT (nr->_hoops_IRR->_hoops_PHARP, T_FACES))
		_hoops_AGHAR = HD_Get_Screen_Facings (nr, ts, ts->face_count);


	while (_hoops_PHHA-- > 0) {
		bool				_hoops_SICPR = false;
		bool				_hoops_CSSAS = false;
		int						length;
		int						_hoops_SSSAS;
		float					_hoops_GGGPS = MAX_FLOAT;

		/* _hoops_HSPP _hoops_IRS _hoops_CCAH _hoops_ARAH-_hoops_CGGR */
		index = *_hoops_AIHA++;
		index = HI_Split_Point_Original (status->_hoops_IPRI, index);
		_hoops_SICAS = &_hoops_CGCAR[index];
		_hoops_PAISA = ws[index];
		_hoops_RGSAS = &_hoops_RRCAR[index];
		index = *_hoops_AIHA++;
		index = HI_Split_Point_Original (status->_hoops_IPRI, index);
		_hoops_GCCAS = &_hoops_CGCAR[index];
		_hoops_IICPA = ws[index];
		_hoops_CHPSH = &_hoops_RRCAR[index];

		length = *lengths++;
		if (length < 0) {
			_hoops_SICPR = true;
			length = -length;
		}
		length -= 2;

		if (face_indices) face_indices += 2;
		_hoops_PCCAR {
			bool		_hoops_RGGPS;
			bool		_hoops_RCSAS = true;

			index = *_hoops_AIHA++;
			index = HI_Split_Point_Original (status->_hoops_IPRI, index);
			_hoops_AGSAS = &_hoops_CGCAR[index];
			_hoops_CICPA = ws[index];
			_hoops_SHPSH = &_hoops_RRCAR[index];

			if (face_indices)
				face = *face_indices++;
			else
				face++;

			if (_hoops_AGHAR != null && !_hoops_AGHAR[face]) {
				/* _hoops_HRGIR _hoops_RHGCP */
				_hoops_CSSAS = false;
				_hoops_RCSAS = false;
			}
			else if (ANYBIT (*_hoops_RGSAS & *_hoops_CHPSH & *_hoops_SHPSH, ~_hoops_RPCAR)) {
				/* _hoops_RGR _hoops_SCPH _hoops_AGIRH _hoops_GGSR _hoops_GPP _hoops_RH _hoops_PSHR _hoops_PPAP, _hoops_HIS
				 * _hoops_SAHR _hoops_AGGPS _hoops_GPP _hoops_HPP */
				_hoops_CSSAS = false;
				_hoops_RCSAS = false;
			}
			else if (BIT (sc->options, _hoops_CRPAS)) {
				DC_Point						_hoops_HRIGA[6];
				DC_Point *					points = _hoops_HRIGA;

				points->x = _hoops_SICAS->x;
				points->y = _hoops_SICAS->y;
				points->z = _hoops_SICAS->z;
				points++;
				points->x = _hoops_GCCAS->x;
				points->y = _hoops_GCCAS->y;
				points->z = _hoops_GCCAS->z;
				points++;
				points->x = _hoops_AGSAS->x;
				points->y = _hoops_AGSAS->y;
				points->z = _hoops_AGSAS->z;
				points++;

				if (BIT (*_hoops_RGSAS | *_hoops_CHPSH | *_hoops_SHPSH, _hoops_IPCAR)) {
					_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
					int				a, b, c;
					float			_hoops_PRSAS, _hoops_HRSAS, _hoops_GPGSI;
					float			_hoops_IRSAS, _hoops_CRSAS;

					/* "_hoops_IRSHR" _hoops_RSSA _hoops_HIS _hoops_SGS _hoops_PPSR _hoops_RAIGR _hoops_HRGR _hoops_GGR _hoops_RIPS _hoops_IIGR _hoops_RH _hoops_RHC
					 * _hoops_PPR _hoops_PPSR _hoops_IHRPR _hoops_HRGR _hoops_GHIPR.  _hoops_ACAGR _hoops_IIGR _hoops_IHAC _hoops_GRS _hoops_CGIC _hoops_RPP
					 * _hoops_RH _hoops_AACC _hoops_RSSAR _hoops_SPR _hoops_PAR _hoops_PGCR _hoops_HIPH.
					 */
					if (_hoops_PAISA >= _hoops_IHCR->_hoops_CHCR) {
						if (_hoops_CICPA < _hoops_IHCR->_hoops_CHCR) {
							a = 0;	_hoops_PRSAS = _hoops_PAISA;
							b = 1;	_hoops_HRSAS = _hoops_IICPA;
							c = 2;	_hoops_GPGSI = _hoops_CICPA;
						}
						else {	/* _hoops_RASAS _hoops_PIHA _hoops_SHH _hoops_GHIPR */
							a = 2;	_hoops_PRSAS = _hoops_CICPA;
							b = 0;	_hoops_HRSAS = _hoops_PAISA;
							c = 1;	_hoops_GPGSI = _hoops_IICPA;
						}
					}
					else {
						if (_hoops_IICPA >= _hoops_IHCR->_hoops_CHCR) {
							a = 1;	_hoops_PRSAS = _hoops_IICPA;
							b = 2;	_hoops_HRSAS = _hoops_CICPA;
							c = 0;	_hoops_GPGSI = _hoops_PAISA;
						}
						else {	/* _hoops_AASAS _hoops_PIHA _hoops_SHH _hoops_RGAR _hoops_SPR _hoops_GGR _hoops_RIPS */
							a = 2;	_hoops_PRSAS = _hoops_CICPA;
							b = 0;	_hoops_HRSAS = _hoops_PAISA;
							c = 1;	_hoops_GPGSI = _hoops_IICPA;
						}
					}

					a -= 3; b -= 3; c -= 3; /* _hoops_AGCR _hoops_CGRPR _hoops_RH _hoops_PGGPS _hoops_GSSRH _hoops_RH _hoops_CICRR */

					if (_hoops_HRSAS < _hoops_IHCR->_hoops_CHCR) {
						/* _hoops_IHAC & _hoops_IHRPR _hoops_GIPR _hoops_GHIPR, _hoops_GAGPR _hoops_HSPH _hoops_CAPR _hoops_GGR _hoops_HGHC */
						float					_hoops_PASAS = 1.0f / _hoops_IHCR->_hoops_CHCR;

						_hoops_IRSAS = (_hoops_IHCR->_hoops_CHCR - _hoops_PRSAS) / (_hoops_HRSAS - _hoops_PRSAS);
						_hoops_CRSAS = (_hoops_IHCR->_hoops_CHCR - _hoops_PRSAS) / (_hoops_GPGSI - _hoops_PRSAS);

						points[b].x = (_hoops_PRSAS*points[a].x + (points[b].x - _hoops_PRSAS*points[a].x) * _hoops_IRSAS) * _hoops_PASAS;
						points[b].y = (_hoops_PRSAS*points[a].y + (points[b].y - _hoops_PRSAS*points[a].y) * _hoops_IRSAS) * _hoops_PASAS;
						points[b].z = (_hoops_PRSAS*points[a].z + (points[b].z - _hoops_PRSAS*points[a].z) * _hoops_IRSAS) * _hoops_PASAS;
						points[c].x = (_hoops_PRSAS*points[a].x + (points[c].x - _hoops_PRSAS*points[a].x) * _hoops_CRSAS) * _hoops_PASAS;
						points[c].y = (_hoops_PRSAS*points[a].y + (points[c].y - _hoops_PRSAS*points[a].y) * _hoops_CRSAS) * _hoops_PASAS;
						points[c].z = (_hoops_PRSAS*points[a].z + (points[c].z - _hoops_PRSAS*points[a].z) * _hoops_CRSAS) * _hoops_PASAS;
					}
					else {
						/* _hoops_SAHR _hoops_IHRPR _hoops_SACH, _hoops_IRHH _hoops_PGCR _hoops_HIPH _hoops_RAIGR-_hoops_IHAC-_hoops_IHRPR', _hoops_IHAC-_hoops_IHAC'-_hoops_IHRPR' */
						float					_hoops_PASAS = 1.0f / _hoops_IHCR->_hoops_CHCR;

						/* _hoops_IHAC' (_hoops_GIAP _hoops_PPSR _hoops_IIGR _hoops_GIAP _hoops_HASAS) _hoops_GAPA _hoops_IHAC _hoops_PPR _hoops_IHRPR */
						_hoops_IRSAS = (_hoops_IHCR->_hoops_CHCR - _hoops_HRSAS) / (_hoops_GPGSI - _hoops_HRSAS);
						/* _hoops_IHRPR' (_hoops_HRSSR _hoops_PPSR _hoops_IIGR _hoops_GIAP _hoops_HASAS) _hoops_GAPA _hoops_RAIGR _hoops_PPR _hoops_IHRPR */
						_hoops_CRSAS = (_hoops_IHCR->_hoops_CHCR - _hoops_PRSAS) / (_hoops_GPGSI - _hoops_PRSAS);

						points[0].x = points[b].x;
						points[0].y = points[b].y;
						points[0].z = points[b].z;
						points[1].x = (_hoops_HRSAS*points[b].x + (points[c].x - _hoops_HRSAS*points[b].x) * _hoops_IRSAS) * _hoops_PASAS;
						points[1].y = (_hoops_HRSAS*points[b].y + (points[c].y - _hoops_HRSAS*points[b].y) * _hoops_IRSAS) * _hoops_PASAS;
						points[1].z = 0.0f;
						points[2].x = (_hoops_PRSAS*points[a].x + (points[c].x - _hoops_PRSAS*points[a].x) * _hoops_CRSAS) * _hoops_PASAS;
						points[2].y = (_hoops_PRSAS*points[a].y + (points[c].y - _hoops_PRSAS*points[a].y) * _hoops_CRSAS) * _hoops_PASAS;
						points[2].z = 0.0f;
						points[c].x = points[2].x;
						points[c].y = points[2].y;
						points[c].z = points[2].z;
						points += 3;
					}
				}

				_hoops_IGRS (dc);
				if (sc->_hoops_GPPAS) {
					void *							_hoops_CCHSP;

					_hoops_CCHSP = _hoops_AACGH (nr, true);
					_hoops_GSRGA (nr, -(points-_hoops_HRIGA), _hoops_HRIGA);
					_hoops_PACGH (nr, _hoops_CCHSP);

					_hoops_RCSAS =
						(_hoops_IACGH (nr, _hoops_CCHSP) > 0);
				}
				else {
					_hoops_ICSIR->input._hoops_PHHSP = 0;

					_hoops_GSRGA (nr, -(points-_hoops_HRIGA), _hoops_HRIGA);

					_hoops_RCSAS = (_hoops_ICSIR->input._hoops_PHHSP > 0);
				}
				_hoops_SGRS (dc);
			}

			if (_hoops_RCSAS) {
				bool			_hoops_HGGPS = false;
				DC_Point const *	_hoops_ACSAS;
				DC_Point const *	_hoops_PCSAS;
				float				_hoops_IGIAS;

				if (_hoops_ISSAS) {
					int				_hoops_IGGPS = _hoops_PGSAS;
					float			dx01 = _hoops_GCCAS->x - _hoops_SICAS->x;
					float			_hoops_CGGPS = _hoops_GCCAS->y - _hoops_SICAS->y;
					float			_hoops_SGGPS = _hoops_GCCAS->z - _hoops_SICAS->z;
					float			dx12 = _hoops_AGSAS->x - _hoops_GCCAS->x;
					float			_hoops_GRGPS = _hoops_AGSAS->y - _hoops_GCCAS->y;
					float			_hoops_RRGPS = _hoops_AGSAS->z - _hoops_GCCAS->z;
					float			xc = _hoops_CGGPS * _hoops_RRGPS - _hoops_SGGPS * _hoops_GRGPS;
					float			yc = _hoops_SGGPS * dx12 - dx01 * _hoops_RRGPS;
					float			zc = dx01 * _hoops_GRGPS - _hoops_CGGPS * dx12;

					/* _hoops_CGIC _hoops_CCAH _hoops_ARGPS */
					xc = Abs (xc);
					yc = Abs (yc);
					zc = Abs (zc);
					if (xc > yc) {
						if (xc > zc)
							_hoops_PGSAS = 0;
						else
							_hoops_PGSAS = 2;
					}
					else {
						if (yc > zc)
							_hoops_PGSAS = 1;
						else
							_hoops_PGSAS = 2;
					}

					if (_hoops_PGSAS != _hoops_IGGPS)
						_hoops_CSSAS = false;
				}

				_hoops_ACSAS = status->_hoops_SPPAS.vertex1;
				_hoops_PCSAS = status->_hoops_SPPAS.vertex2;
				_hoops_IGIAS = status->_hoops_CCCCP._hoops_HISAP;

				status->_hoops_CCCCP._hoops_HISAP = 0.999f*sc->_hoops_GICAH;

				if (!_hoops_CSSAS)
					_hoops_PHSAS (nr, status, &_hoops_ASSAS, _hoops_SICAS, _hoops_PAISA, _hoops_RGSAS, _hoops_GCCAS, _hoops_IICPA, _hoops_CHPSH, false, false, _hoops_PGSAS);
				_hoops_PHSAS (nr, status, &_hoops_PSSAS, _hoops_GCCAS, _hoops_IICPA, _hoops_CHPSH, _hoops_AGSAS, _hoops_CICPA, _hoops_SHPSH, false, false, _hoops_PGSAS);
				_hoops_PHSAS (nr, status, &_hoops_HSSAS, _hoops_AGSAS, _hoops_CICPA, _hoops_SHPSH, _hoops_SICAS, _hoops_PAISA, _hoops_RGSAS, false, false, _hoops_PGSAS);

				/* _hoops_RPP _hoops_GII _hoops_IIGR _hoops_RH _hoops_SPPR _hoops_HRGR _hoops_GIAA _hoops_RH _hoops_GHSHA
				 * _hoops_IPCAH, _hoops_PRIA _hoops_RH _hoops_HSP _hoops_PHI.
				 */

				if (_hoops_ASSAS._hoops_RICAS ||
					_hoops_PSSAS._hoops_RICAS ||
					_hoops_HSSAS._hoops_RICAS) {
					status->_hoops_CCCCP.face = face;

					status->_hoops_HHPAS = true;
					status->_hoops_SPPAS.vertex1 = status->_hoops_CCCCP.vertex1;
					status->_hoops_SPPAS.vertex2 = status->_hoops_CCCCP.vertex2;
					_hoops_GGGPS = status->_hoops_CCCCP._hoops_RCSAP;
					_hoops_HGGPS = true;
				}

				/* _hoops_IGHS _hoops_PRGI _hoops_PISC _hoops_GRGPH _hoops_IS _hoops_CACH _hoops_RPP _hoops_SR _hoops_CHR _hoops_ASSA _hoops_IIGR
				 * _hoops_RH _hoops_SCPH (_hoops_PIHHR).
				 */

				_hoops_RGGPS = BIT (*_hoops_RGSAS | *_hoops_CHPSH | *_hoops_SHPSH, _hoops_IPCAR);

				_hoops_SSSAS = (_hoops_ASSAS._hoops_GICAS ^
							_hoops_PSSAS._hoops_GICAS ^
							_hoops_HSSAS._hoops_GICAS);

				if ((!_hoops_RGGPS && _hoops_SSSAS) ||
					(_hoops_RGGPS &&
					 _hoops_APSAS (nr, status, _hoops_SICAS, _hoops_PAISA, _hoops_RGSAS, _hoops_GCCAS, _hoops_IICPA, _hoops_CHPSH, _hoops_AGSAS, _hoops_CICPA, _hoops_SHPSH))) {
					/* _hoops_SR _hoops_CHR *_hoops_GIAA* _hoops_RH _hoops_HSP */
					Point				_hoops_PRGPS;

					/* _hoops_RRP _hoops_IS _hoops_CAHA/_hoops_GAGAH _hoops_IRS _hoops_HRGPS. */
					/* _hoops_IRGPS _hoops_HRS _hoops_RH _hoops_SSH _hoops_HCH _hoops_IIGR _hoops_RH
					 * _hoops_GHSHA _hoops_PPSR (_hoops_PAR _hoops_GGR _hoops_GSSP _hoops_GC, _hoops_RH _hoops_SGSSR _hoops_IIGR _hoops_IRS _hoops_GSISC
					 * _hoops_IRSS _hoops_RHIR _hoops_RH _hoops_RHCH _hoops_IIGR _hoops_RH _hoops_GHSHA _hoops_CISAR)
					 */
					_hoops_GGSAS (nr, _hoops_SICAS, _hoops_PAISA, _hoops_RGSAS, _hoops_GCCAS, _hoops_IICPA, _hoops_CHPSH, _hoops_AGSAS, _hoops_CICPA, _hoops_SHPSH, &_hoops_PRGPS, _hoops_PGSAS);
					_hoops_GGGPS = _hoops_PRGPS.z;

					/* _hoops_CACH _hoops_RPP _hoops_RH _hoops_SSH _hoops_HRGR _hoops_PHRHA _hoops_RSAHA _hoops_HCR _hoops_RH _hoops_PACIA. */
					if (_hoops_PRGPS.x >= sc->bounding.left   &&
						_hoops_PRGPS.x <= sc->bounding.right  &&
						_hoops_PRGPS.y >= sc->bounding.bottom &&
						_hoops_PRGPS.y <= sc->bounding.top	   &&
						_hoops_PRGPS.z >= sc->bounding.hither &&
						_hoops_PRGPS.z <= sc->bounding.yon) {
						/* _hoops_GCRR _hoops_RCRR _hoops_RH _hoops_GHSHA _hoops_PPSR _hoops_HRGR _hoops_HAR _hoops_AACC _hoops_SGGR
						 * _hoops_HPP _hoops_HPPA _hoops_GHC.
						 */

						if (_hoops_HICAS (nr, &_hoops_PRGPS)) {
							_hoops_HGGPS = true; /* _hoops_PAHH... */

							status->_hoops_CCCCP.face = face;

							/* _hoops_PRIA _hoops_SCH */
							if (_hoops_ASSAS._hoops_RICAS ||
								_hoops_PSSAS._hoops_RICAS ||
								_hoops_HSSAS._hoops_RICAS) {
								status->_hoops_SPPAS.vertex1 = status->_hoops_CCCCP.vertex1;
								status->_hoops_SPPAS.vertex2 = status->_hoops_CCCCP.vertex2;
							}
							else {
								/* _hoops_RRP _hoops_IS _hoops_CAHP _hoops_RH _hoops_HISGR _hoops_ISHA,
								 * _hoops_PRGI _hoops_PHRI _hoops_SSIA _hoops_AAPR _hoops_HCR _hoops_SACH
								 * _hoops_SGGR. _hoops_CRGPS.
								 */

								struct _hoops_SHCAS alter		*_hoops_SRGPS[3],
																		*tmp;

								_hoops_ASSAS.start = _hoops_SICAS;
								_hoops_ASSAS.end = _hoops_GCCAS;
								_hoops_PSSAS.start = _hoops_GCCAS;
								_hoops_PSSAS.end = _hoops_AGSAS;
								_hoops_HSSAS.start = _hoops_AGSAS;
								_hoops_HSSAS.end = _hoops_SICAS;
								_hoops_ASSAS._hoops_AICAS = _hoops_RGSAS;
								_hoops_ASSAS._hoops_PICAS = _hoops_CHPSH;
								_hoops_PSSAS._hoops_AICAS = _hoops_CHPSH;
								_hoops_PSSAS._hoops_PICAS = _hoops_SHPSH;
								_hoops_HSSAS._hoops_AICAS = _hoops_SHPSH;
								_hoops_HSSAS._hoops_PICAS = _hoops_RGSAS;
								_hoops_SRGPS[0] = &_hoops_HSSAS;
								_hoops_SRGPS[1] = &_hoops_ASSAS;
								_hoops_SRGPS[2] = &_hoops_PSSAS;

								/* _hoops_CHCII-_hoops_GHIS _hoops_ISCP _hoops_GSISC _hoops_SPPR */
								if (_hoops_SRGPS[0]->_hoops_CIPAS > _hoops_SRGPS[1]->_hoops_CIPAS) {
									tmp = _hoops_SRGPS[0];
									_hoops_SRGPS[0] = _hoops_SRGPS[1];
									_hoops_SRGPS[1] = tmp;
								}
								if (_hoops_SRGPS[0]->_hoops_CIPAS > _hoops_SRGPS[2]->_hoops_CIPAS) {
									tmp = _hoops_SRGPS[0];
									_hoops_SRGPS[0] = _hoops_SRGPS[2];
									_hoops_SRGPS[2] = tmp;
								}
								if (_hoops_SRGPS[1]->_hoops_CIPAS > _hoops_SRGPS[2]->_hoops_CIPAS) {
									tmp = _hoops_SRGPS[1];
									_hoops_SRGPS[1] = _hoops_SRGPS[2];
									_hoops_SRGPS[2] = tmp;
								}

								if (!_hoops_PCCAS (status, _hoops_SRGPS[0], false) &&
									!_hoops_PCCAS (status, _hoops_SRGPS[1], false) &&
									!_hoops_PCCAS (status, _hoops_SRGPS[2], false)) {
									/* _hoops_PAGA: _hoops_RGR _hoops_GAGPS _hoops_RH _hoops_HSP, _hoops_HIH _hoops_RH "_hoops_AAH _hoops_ISHA" _hoops_IH _hoops_SCH _hoops_GPGH'_hoops_RA _hoops_HPHR */
									_hoops_PCCAS (status, _hoops_SRGPS[0], true);
								}
							}
						}
						if (_hoops_HGGPS)		/* _hoops_PPPSR _hoops_RHHR */
							status->_hoops_CCCCP._hoops_HISAP = 0.0f;
					}
				}

				if (_hoops_HGGPS) {
					/* _hoops_GGCR _hoops_IS _hoops_RGIAS _hoops_RPP _hoops_IRPR */
					if (status->_hoops_CHPAS) {
						int						_hoops_RAGPS;

						/* _hoops_SGH _hoops_AAGPS._hoops_HSP _hoops_PGGA _hoops_SR _hoops_SIPGR'_hoops_RA _hoops_RIRRR _hoops_IS _hoops_PAGPS _hoops_GAPR */
						/* _hoops_GIGHR: *_hoops_HAR* _hoops_HAGPS(), _hoops_SR _hoops_RRP _hoops_SGCRP _hoops_CIHA */
						_hoops_RAGPS = status->_hoops_CCCCP.face;

						_hoops_CCSAS[_hoops_RAGPS] = (int) (status->_hoops_SPPAS.vertex1 - status->_hoops_CGCAR);
						_hoops_SCSAS[_hoops_RAGPS] = (int) (status->_hoops_SPPAS.vertex2 - status->_hoops_CGCAR);
						_hoops_GSSAS[_hoops_RAGPS] = status->_hoops_CCCCP._hoops_HISAP;
						_hoops_RSSAS[_hoops_RAGPS] = _hoops_GGGPS;
					}

					/* _hoops_PCSA _hoops_GAR _hoops_AAH _hoops_RPP _hoops_IRPR */
					if (BIT (sc->options, _hoops_RHCAH) &&
						  _hoops_GGGPS < status->_hoops_SPPAS._hoops_RCSAP ||
						!BIT (sc->options, _hoops_RHCAH) &&
						  (status->_hoops_CCCCP._hoops_HISAP < status->_hoops_SPPAS._hoops_HISAP ||
						   (status->_hoops_CCCCP._hoops_HISAP == status->_hoops_SPPAS._hoops_HISAP &&
							_hoops_GGGPS < status->_hoops_SPPAS._hoops_RCSAP))) {
						status->_hoops_SPPAS._hoops_RCSAP = _hoops_GGGPS;
						status->_hoops_SPPAS.face = status->_hoops_CCCCP.face;
						if (status->_hoops_CCCCP._hoops_HISAP < status->_hoops_SPPAS._hoops_HISAP)
							status->_hoops_SPPAS._hoops_HISAP = status->_hoops_CCCCP._hoops_HISAP;
								/* _hoops_HII _hoops_HA _hoops_GPP */
						status->_hoops_AHPAS = true;

						if (status->_hoops_SHPAS)
							return;
					}
					else {
						/* _hoops_IAGPS _hoops_ARRS _hoops_CGPR _hoops_SCH _hoops_PPRIP _hoops_RIRA... */
						status->_hoops_SPPAS.vertex1 = _hoops_ACSAS;
						status->_hoops_SPPAS.vertex2 = _hoops_PCSAS;
						status->_hoops_CCCCP._hoops_HISAP = _hoops_IGIAS;
					}
				}
				else {
					/* _hoops_IAGPS _hoops_ARRS _hoops_CGPR _hoops_SCH _hoops_PPRIP _hoops_RIRA... */
					status->_hoops_SPPAS.vertex1 = _hoops_ACSAS;
					status->_hoops_SPPAS.vertex2 = _hoops_PCSAS;
					status->_hoops_CCCCP._hoops_HISAP = _hoops_IGIAS;
				}


				/* _hoops_IPS _hoops_RH 12 _hoops_ISHA _hoops_IS _hoops_RH 01 _hoops_PGGA 12 _hoops_HRGR _hoops_HA _hoops_RH
				 * _hoops_SRS _hoops_ISHA _hoops_IIGR _hoops_RH _hoops_SPS _hoops_SCPH. _hoops_IPS & _hoops_PIIA _hoops_RH
				 * 20 _hoops_ISHA _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_HAHCP
				 */

				if (_hoops_SICPR) {
					_hoops_ASSAS.tc = 1.0f - _hoops_HSSAS.tc;
					_hoops_ASSAS._hoops_CIPAS = _hoops_HSSAS._hoops_CIPAS;
					_hoops_ASSAS._hoops_GICAS = _hoops_HSSAS._hoops_GICAS;
					_hoops_ASSAS._hoops_RICAS = _hoops_HSSAS._hoops_RICAS;
				}
				else {
					_hoops_ASSAS.tc = _hoops_PSSAS.tc;
					_hoops_ASSAS._hoops_CIPAS = _hoops_PSSAS._hoops_CIPAS;
					_hoops_ASSAS._hoops_GICAS = _hoops_PSSAS._hoops_GICAS;
					_hoops_ASSAS._hoops_RICAS = _hoops_PSSAS._hoops_RICAS;
				}
				_hoops_CSSAS = true;
			}

			if (--length <= 0) break;

			if (!_hoops_SICPR) {
				_hoops_SICAS = _hoops_GCCAS;
				_hoops_PAISA = _hoops_IICPA;
				_hoops_RGSAS = _hoops_CHPSH;
			}
			_hoops_GCCAS = _hoops_AGSAS;
			_hoops_IICPA = _hoops_CICPA;
			_hoops_CHPSH = _hoops_SHPSH;
		}
	}
}
#endif

local bool _hoops_CAGPS (
	Net_Rendition const &			nr,
	Polyhedron const *				_hoops_IPRI) {
	_hoops_GRA const &		_hoops_RRA = nr->_hoops_ARA;

	if (_hoops_RRA->_hoops_CICP.scale != _hoops_IPRI->_hoops_GIHIR.scale ||
		_hoops_RRA->_hoops_CICP.translate != _hoops_IPRI->_hoops_GIHIR.translate)
		return true;

	if (_hoops_RRA->_hoops_ACP._hoops_RSCRP != _hoops_IPRI->_hoops_GIHIR._hoops_RSCRP ||
		_hoops_RRA->_hoops_ACP._hoops_CIAIR != _hoops_IPRI->_hoops_GIHIR._hoops_CIAIR)
		return true;

	if (!EQUAL_MEMORY (_hoops_RRA->_hoops_ACP._hoops_SIAIR, _hoops_RRA->_hoops_ACP._hoops_CIAIR * sizeof(float),
						_hoops_IPRI->_hoops_GIHIR._hoops_SIAIR))
		return true;

	return false;
}


GLOBAL_FUNCTION void HD_Select_Polyhedron (
	Net_Rendition const &		inr,
	Polyhedron const *			_hoops_IPRI) {
#ifndef DISABLE_SELECTION
	Net_Rendition				nr = inr;
	bool						_hoops_SAGPS = false,
								_hoops_GPGPS = false,
								_hoops_RPGPS = false,
								_hoops_APGPS = false;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter	*	sc = dc->_hoops_APHHP;
	_hoops_PCCCP			status;
	_hoops_ACHR					_hoops_PPGPS;
	_hoops_ACHR					_hoops_CIPSH;
	bool						_hoops_PSCAS;
	_hoops_ICP const &	_hoops_CCP = nr->_hoops_GSP;
	float						_hoops_HPGPS = (float)_hoops_CCP->ysize;
	int							i;

	ASSERT(_hoops_IPRI->owner == null || _hoops_IPRI->owner->_hoops_RHAGR._hoops_ASAGP(dc->_hoops_RIGC->thread_id));


	if (BIT (_hoops_CCP->glyph->flags, _hoops_GSIAP))
		_hoops_HPGPS = 1.0f;
	else if (_hoops_HPGPS < 0)
		_hoops_HPGPS = 0.5f * HD_Compute_Generic_Size (nr, _hoops_CCP->_hoops_PHP, _hoops_CCP->_hoops_HHP, 1.0f, false, 0, true);

	_hoops_PSCAS = BIT (nr->transform_rendition->heuristics, _hoops_GAIRP);

	ZERO_STRUCT (&status, _hoops_PCCCP);

	sc->_hoops_AICCP = (void alter *)&status; /* _hoops_RIH _hoops_SCH _hoops_RHIR _hoops_IS _hoops_HRCC _hoops_CIPIP _hoops_APSI */

	status.sc = sc;


	/* _hoops_GCGH _hoops_IH _hoops_GGAGA _hoops_SCHS _hoops_GGR _hoops_SPIGA-_hoops_RGAR _hoops_IRGHC. */
	if ((_hoops_IPRI != null) &&
		(_hoops_IPRI->points == null) &&
		(_hoops_IPRI->_hoops_HGAIR != null)) {
		status._hoops_IPRI = null;
		for (i = 0; i < _hoops_IGAIR; i++) {
			if (_hoops_IPRI->_hoops_HGAIR->data[i] != null) {
				status._hoops_IPRI = (Polyhedron *) _hoops_IPRI->_hoops_HGAIR->data[i];
				break;
			}
		}
	}
	else
		status._hoops_IPRI = _hoops_IPRI;

/* _hoops_RH _hoops_HSPR _hoops_RIS _hoops_RHAP _hoops_GHSHA _hoops_CCA _hoops_GPCAR _hoops_IS _hoops_RH _hoops_PHSRP _hoops_HHPA
 * _hoops_PRCCA.	 _hoops_PS _hoops_AAPR _hoops_HSGSC _hoops_IIGR _hoops_GRP (_hoops_PPR _hoops_GHCA _hoops_HPGR _hoops_HHH _hoops_PPSR _hoops_SGH) _hoops_IRS _hoops_GHARR _hoops_HCSP
 * _hoops_IS _hoops_HHPR _hoops_SCH */
#if 0
	if (status._hoops_IPRI->_hoops_HGAIR != null) {
		Geometry *thing;

		for (i = _hoops_IGAIR - 1; i >= 0; i--) {
			thing = status._hoops_IPRI->_hoops_HGAIR->data[i];
			if (thing != null &&
				thing->type == _hoops_SCIP &&
				((Polyhedron *)thing)->point_count != 0) {
				status._hoops_IPRI = (Polyhedron *)thing;
				break;
			}
		}
	}
#endif

	/* _hoops_RPP _hoops_RSIPR _hoops_RH _hoops_AIRA _hoops_PAPA _hoops_GHCRH _hoops_GII _hoops_PRCCA _hoops_HARH _hoops_SCIR _hoops_GII _hoops_AHSIR, _hoops_ASRC */
	if (status._hoops_IPRI == null ||
		status._hoops_IPRI->points == null)
		return;

	if (BIT (nr->transform_rendition->_hoops_APH, Heur_Culling_VIEW_FRUSTUM)) {
		_hoops_PACIR		_hoops_IPGPS;
		Int_Rectangle			_hoops_CPGPS;

		_hoops_IPGPS.left	  = sc->bounding.left	- _hoops_HPGPS;
		_hoops_IPGPS.right  = sc->bounding.right	+ _hoops_HPGPS;
		_hoops_IPGPS.bottom = sc->bounding.bottom - _hoops_HPGPS;
		_hoops_IPGPS.top	  = sc->bounding.top	+ _hoops_HPGPS;

		_hoops_CPGPS.left	  = (int)sc->bounding.left;
		_hoops_CPGPS.right  = (int)sc->bounding.right;
		_hoops_CPGPS.bottom = (int)sc->bounding.bottom;
		_hoops_CPGPS.top	  = (int)sc->bounding.top;

		if (HD_Transform_And_Test_Bounding (nr, &status._hoops_IPRI->bounding,
											&_hoops_IPGPS, &_hoops_CPGPS, 0) == Test_DISJOINT)
			return;
	}

	status._hoops_SPPAS._hoops_HISAP =
		status._hoops_GHPAS._hoops_HISAP =
			status._hoops_CCCCP._hoops_HISAP =
				status._hoops_RHPAS._hoops_HISAP = sc->_hoops_GICAH;

	status._hoops_APPAS = &status._hoops_ACSAP;
	status._hoops_SHPAS = nr->_hoops_IRR->_hoops_CCIRP._hoops_SPHPR < 0;
	status._hoops_CHPAS = nr->_hoops_IRR->_hoops_CCIRP._hoops_SPHPR > 0;

	/* _hoops_SRPR _hoops_RCRR, _hoops_RCSC _hoops_RGR _hoops_HRGR _hoops_IIAC _hoops_IRS _hoops_IGRH _hoops_HRHC _hoops_HSAR _hoops_AGIAS. */

	status._hoops_SPPAS._hoops_RCSAP = MAX_FLOAT * 0.99f; /* _hoops_IGI _hoops_RAS '_hoops_SPGPS' */


	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;

	_hoops_PPGPS = _hoops_RRGH->locks._hoops_RGP;
	_hoops_CIPSH = nr->_hoops_RGP | _hoops_RRGH->_hoops_PHARP;

	/* _hoops_RH _hoops_HSPR _hoops_HGRH _hoops_HRGR _hoops_GHGPS _hoops_HII _hoops_HPRGR 3d _hoops_CPHAR */

	if (BIT (_hoops_RRGH->_hoops_AAICA, T_FACES)) {
		if (BIT (_hoops_RRGH->_hoops_PHARP, T_FACES)) {
			// _hoops_SGHS & _hoops_HRP _hoops_CHR _hoops_PGGAC */
			_hoops_SAGPS = true;
		}
		else if (ANYBIT (_hoops_PPGPS, T_FACES)) {
			if (BIT (_hoops_CIPSH, T_FACES)) {
				if (status._hoops_IPRI->face_count > 0)
					_hoops_SAGPS = true;	// _hoops_CGPR _hoops_HSP _hoops_HPRC _hoops_AAHS, _hoops_HSP _hoops_SIGC _hoops_PPR _hoops_IIH _hoops_CHR _hoops_RSSI.
			}
		}
		else {
			if (BIT (_hoops_CIPSH, T_FACES)) {
				// _hoops_CSH _hoops_HPRC _hoops_AAHS, _hoops_HSP _hoops_SIGC,  _hoops_PPR _hoops_IIH _hoops_CHR _hoops_RRI _hoops_IRGH _hoops_SIGC _hoops_RSSI _hoops_HSAR _hoops_PSIPR.
				if (status._hoops_IPRI->face_count >
					   status._hoops_IPRI->local_face_attributes._hoops_SIIPR)
					_hoops_SAGPS = true;
			}
			else {
				// _hoops_CSH _hoops_IGRI _hoops_AAHS _hoops_PPR _hoops_HSP _hoops_PSIPR, _hoops_SR _hoops_HRAR _hoops_GPP _hoops_RH _hoops_IRGH _hoops_RGSR.
				if (status._hoops_IPRI->local_face_attributes._hoops_CPIAA > 0)
					_hoops_SAGPS = true;
			}
		}
	}

	/* _hoops_PGPR _hoops_RSSI _hoops_PAH _hoops_SHH _hoops_PACIA _hoops_CCA _hoops_IPCAH 0. */

	if (status._hoops_CCCCP._hoops_HISAP != 0.0f &&
		BIT (_hoops_RRGH->_hoops_AAICA, _hoops_GPA)) {
		if (BIT (_hoops_RRGH->_hoops_PHARP, _hoops_GPA)) {
			_hoops_GPGPS = true;		// _hoops_SGHS & _hoops_HRP _hoops_CHR _hoops_PGGAC
		}
		// _hoops_ACGC _hoops_CHR _hoops_PASI _hoops_HHPA _hoops_RGAR _hoops_RPP _hoops_RSSI _hoops_CHH _hoops_SHH _hoops_SIGC
		else if (ANYBIT (_hoops_PPGPS, T_FACES)) {
			if (BIT (_hoops_CIPSH, T_FACES)) {
				if (status._hoops_IPRI->face_count > 0)
					_hoops_GPGPS = true;	// _hoops_CGPR _hoops_HSP _hoops_HPRC _hoops_AAHS, _hoops_HSP _hoops_SIGC _hoops_PPR _hoops_IIH _hoops_CHR _hoops_RSSI.
			}
		}
		else {
			if (BIT (_hoops_CIPSH, T_FACES)) {
				// _hoops_CSH _hoops_HPRC _hoops_AAHS, _hoops_HSP _hoops_SIGC,  _hoops_PPR _hoops_IIH _hoops_CHR _hoops_RRI _hoops_IRGH _hoops_SIGC _hoops_RSSI _hoops_HSAR _hoops_PSIPR.
				if (status._hoops_IPRI->face_count >
					   status._hoops_IPRI->local_face_attributes._hoops_SIIPR)
					_hoops_GPGPS = true;
			}
			else {
				// _hoops_CSH _hoops_IGRI _hoops_AAHS _hoops_PPR _hoops_HSP _hoops_PSIPR, _hoops_SR _hoops_HRAR _hoops_GPP _hoops_RH _hoops_IRGH _hoops_RGSR.
				if (status._hoops_IPRI->local_face_attributes._hoops_CPIAA > 0)
					_hoops_GPGPS = true;
			}
		}
	}

	if (status._hoops_CCCCP._hoops_HISAP != 0.0f &&
		ANYBIT (_hoops_RRGH->_hoops_AAICA, T_ANY_EDGE)) {
		// _hoops_CGP _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_RRCPR, _hoops_RHGPS _hoops_CHR _hoops_PSP _hoops_PGCPR.
		if (status._hoops_IPRI->type != _hoops_GSIP)
			_hoops_CIPSH &= ~T_MESH_QUAD_EDGES;

		if (ANYBIT (_hoops_RRGH->_hoops_PHARP, T_ANY_EDGE)) {
			_hoops_RPGPS = true;		// _hoops_SGHS & _hoops_HRP _hoops_CHR _hoops_PGGAC
		}
		else if (ANYBIT (_hoops_PPGPS, T_ANY_EDGE)) {
			if (ANYBIT (_hoops_CIPSH, T_ANY_EDGE)) {
				// (_hoops_ASHS _hoops_GHCA _hoops_HAR _hoops_SHH _hoops_HSSPR _hoops_GAPR; _hoops_SGH _hoops_ACHAA _hoops_IS _hoops_HCGGS _hoops_SPPR)
				if (status._hoops_IPRI->face_count > 0)
					_hoops_RPGPS = true;
			}
		}
		else {
			if (status._hoops_IPRI->_hoops_SPHA < 0) {	  // _hoops_CCSHR?
				if (status._hoops_IPRI->face_count > 0 &&
					ANYBIT (_hoops_CIPSH, T_ANY_EDGE))
					_hoops_RPGPS = true;
			}
			else if (ANYBIT (_hoops_CIPSH, T_ANY_EDGE)) {
				if (status._hoops_IPRI->_hoops_SPHA >
					   status._hoops_IPRI->_hoops_IHHPR._hoops_SIIPR)
					_hoops_RPGPS = true;
			}
			else {
				if (status._hoops_IPRI->_hoops_IHHPR._hoops_CPIAA > 0)
					_hoops_RPGPS = true;
			}
		}
	}

	if (status._hoops_CCCCP._hoops_HISAP != 0.0f &&
		BIT (_hoops_RRGH->_hoops_AAICA, T_VERTICES)) {
		if (BIT (_hoops_RRGH->_hoops_PHARP, T_VERTICES)) {
			_hoops_APGPS = true;		// _hoops_SGHS & _hoops_HRP _hoops_CHR _hoops_PGGAC
		}
		else if (ANYBIT (_hoops_PPGPS, T_VERTICES)) {
			if (BIT (_hoops_CIPSH, T_VERTICES)) {
				if (status._hoops_IPRI->point_count > 0)
					_hoops_APGPS = true;
			}
		}
		else {
			if (BIT (_hoops_CIPSH, T_VERTICES)) {
				if (status._hoops_IPRI->point_count >
					status._hoops_IPRI->local_vertex_attributes._hoops_SIIPR)
					_hoops_APGPS = true;
			}
			else {
				if (status._hoops_IPRI->local_vertex_attributes._hoops_CPIAA > 0)
					_hoops_APGPS = true;
			}
		}
	}

	if (!_hoops_SAGPS && !_hoops_GPGPS && !_hoops_RPGPS && !_hoops_APGPS)
		return;

	int	_hoops_AHGPS;

	nr.Modify()->_hoops_SAIR.Modify();
	_hoops_CGRA alter &	_hoops_SGRA = nr->_hoops_SAIR;

	_hoops_PACIR			_hoops_PHGPS = _hoops_SGRA->_hoops_HHCAR;


	if (!BIT (sc->options, _hoops_CRPAS)) {
		_hoops_SGRA->_hoops_HHCAR = sc->bounding;

		if (_hoops_APGPS)
			_hoops_SGRA->_hoops_HHCAR._hoops_IACHA(_hoops_HPGPS);
	}
	else if (0) {
		_hoops_SGRA->_hoops_HHCAR = sc->bounding;
		_hoops_SGRA->_hoops_HHCAR._hoops_IACHA(50.0f);
	}

	ALLOC_ARRAY_ALIGNED_CACHED (status._hoops_CGCAR, status._hoops_IPRI->point_count, DC_Point, 16);
	ALLOC_ARRAY_ALIGNED_CACHED (status.ws, status._hoops_IPRI->point_count, float, 16);
	ALLOC_ARRAY_CACHED (status._hoops_RRCAR, status._hoops_IPRI->point_count, _hoops_GRCAR);

	/* _hoops_GCAPH _hoops_RH _hoops_HSPH _hoops_HPHS _hoops_SIH _hoops_IH _hoops_GRR _hoops_GPHA _hoops_CCA _hoops_GPCAR
	 * _hoops_IS _hoops_RH _hoops_IASC _hoops_CISAR, _hoops_IAS._hoops_ISHI. _hoops_HHGPS[0] _hoops_PAH _hoops_SHH _hoops_PPSPR _hoops_IS _hoops_RH _hoops_RAAP,
	 * _hoops_PPR _hoops_IS _hoops_RH _hoops_SCIA _hoops_IIGR _hoops_RH _hoops_IASC _hoops_CISAR.
	 * _hoops_IHGPS _hoops_GAGPR _hoops_ARCSA _hoops_RPP _hoops_RH _hoops_CPHAR _hoops_HRGR _hoops_GPGS _hoops_RH _hoops_IASC
	 * _hoops_CISAR.
	 */
	_hoops_AHGPS = HD_Acquire_Clip_Points (nr,
										   status._hoops_IPRI->bounding,
										   status._hoops_IPRI->point_count,
										   status._hoops_IPRI->points,
										   status._hoops_CGCAR,
										   status.ws,
										   status._hoops_RRCAR);

	_hoops_SGRA->_hoops_HHCAR = _hoops_PHGPS;

	if (_hoops_AHGPS == 0) {
		FREE_ARRAY_ALIGNED (status._hoops_CGCAR, status._hoops_IPRI->point_count, DC_Point, 16);
		FREE_ARRAY_ALIGNED (status.ws, status._hoops_IPRI->point_count, float, 16);
		FREE_ARRAY (status._hoops_RRCAR, status._hoops_IPRI->point_count, _hoops_GRCAR);
		return;
	}


	if (_hoops_SAGPS) {
		Tristrip alter *		tristrip;
		bool					_hoops_CHGPS;
		_hoops_SARHR	_hoops_SHGPS = 0;
#		define									_hoops_GIGPS		1024
		int						_hoops_RIGPS[2*_hoops_GIGPS];
		int						*_hoops_CCSAS = &_hoops_RIGPS[0];
		int						*_hoops_SCSAS = &_hoops_RIGPS[_hoops_GIGPS];
		float					_hoops_AIGPS[2*_hoops_GIGPS];
		float					*_hoops_GSSAS = &_hoops_AIGPS[0];
		float					*_hoops_RSSAS = &_hoops_AIGPS[_hoops_GIGPS];
		int						face_count = status._hoops_IPRI->face_count;

		if (BIT (_hoops_CIPSH, T_FACES)) {
			/* _hoops_IPCP _hoops_RGAR _hoops_AHAP _hoops_GCAS _hoops_IS _hoops_ISPR _hoops_HRGR _hoops_HHHA _hoops_PIGPS. */
			_hoops_SHGPS |= _hoops_HSIPR;
		}

		if (!ALLBITS (status._hoops_IPRI->_hoops_ACRHR, _hoops_SHGPS))
			HI_Assemble_3D_Tristrips ((Polyhedron alter *)status._hoops_IPRI,
									  _hoops_SHGPS,
									  false); /* _hoops_GA'_hoops_RA _hoops_RRP _hoops_GPHA _hoops_ASGA */
		else if (BIT (status._hoops_IPRI->_hoops_CPGPR, _hoops_AHSGA)) {
			/* _hoops_CCGI _hoops_RPGAH _hoops_IHRI, _hoops_HIH _hoops_CPHP _hoops_HGAS.	_hoops_GAAP _hoops_CPHP _hoops_PII
			   _hoops_GPHA _hoops_PSHA, _hoops_PGAP _hoops_PSP _hoops_RPIP _hoops_HRCI _hoops_IIRGR (_hoops_CR _hoops_SR _hoops_PAH
			   _hoops_PSP _hoops_RPIP _hoops_SHH _hoops_RCRR _hoops_IIGR _hoops_SSRHR _hoops_CAPR _hoops_HII _hoops_RH _hoops_SCRPA)
			*/
			Polyhedron alter *	_hoops_HPGPR = (Polyhedron alter *)status._hoops_IPRI;

			if (BIT (_hoops_HPGPR->polyhedron_flags, _hoops_CCRHR))
				HI_Resort_Tristrips (_hoops_HPGPR, -1);

			HI_Reset_Strip_Flags (_hoops_HPGPR);
			_hoops_HPGPR->_hoops_CPGPR &= ~_hoops_AHSGA;
		}
		else if (BIT (status._hoops_IPRI->polyhedron_flags, _hoops_CCRHR))
			HI_Resort_Tristrips ((Polyhedron alter *)status._hoops_IPRI, -1);

		((Polyhedron alter *)status._hoops_IPRI)->polyhedron_flags &= ~_hoops_CCRHR;

		_hoops_CHGPS = BIT (nr->_hoops_RGP |
							 nr->_hoops_IRR->_hoops_PHARP, T_FACES);

		if (status._hoops_SHPAS || !status._hoops_CHPAS)
			_hoops_CCSAS = _hoops_SCSAS = null;
		else {
			if (face_count > _hoops_GIGPS) {
				ALLOC_ARRAY (_hoops_CCSAS, 2 * face_count, int);
				_hoops_SCSAS = _hoops_CCSAS + face_count;
				ALLOC_ARRAY (_hoops_GSSAS, 2 * face_count, float);
				_hoops_RSSAS = _hoops_GSSAS + face_count;
			}
			SET_MEMORY (_hoops_CCSAS, 2 * face_count * sizeof (int), -1);
			ZERO_ARRAY (_hoops_GSSAS, 2 * face_count, float);
		}

		if ((tristrip = status._hoops_IPRI->tristrips) != null) {
			int alter *			_hoops_AGHAR = null;
			bool				_hoops_SCSCC = false;

			if (BIT (nr->transform_rendition->flags, _hoops_IGSP) &&
				!BIT (nr->_hoops_IRR->_hoops_PHARP, T_FACES)) {
				if (_hoops_IPRI->local_face_attributes.normals == null ||
					!BIT (_hoops_IPRI->polyhedron_flags, PHF_FACE_NORMALS_VALID))
					HI_Assemble_Face_Normals ((Polyhedron *)_hoops_IPRI);

				if (face_count > dc->_hoops_ICACP)
					_hoops_SCSCC = true;
				_hoops_AGHAR = HD_Generate_DC_Screen_Facings (nr, face_count,
														 _hoops_IPRI->local_face_attributes.normals,
														 true);
			}

			do if ((_hoops_CHGPS ||
				   BIT(tristrip->face_attributes.flags, _hoops_IAGI)) &&
				   (!BIT(tristrip->face_attributes.flags, _hoops_HSIPR) ||
				   BIT(nr->_hoops_IRR->_hoops_PHARP, T_FACES))) {

				_hoops_ICSAS (nr, tristrip, _hoops_CCSAS, _hoops_SCSAS, _hoops_GSSAS, _hoops_RSSAS, _hoops_AGHAR);

				if (status._hoops_SHPAS && status._hoops_AHPAS)
					break;
			} while ((tristrip = tristrip->next) != null);

			if (_hoops_SCSCC) {
				FREE_ARRAY_ALIGNED(dc->_hoops_CGHAR, dc->_hoops_ICACP, int, 16);
				dc->_hoops_ICACP = 0;
				dc->_hoops_CGHAR = null;
			}
		}

		if (_hoops_CCSAS != null) {
			int				index;

			for (index=0; index < face_count; ++index) {
				if (_hoops_CCSAS[index] != -1) {
					_hoops_AISAP *	_hoops_HHCAP;

					ALLOC (_hoops_HHCAP, _hoops_AISAP);
					_hoops_HHCAP->_hoops_PISAP[0] = _hoops_CCSAS[index];
					_hoops_HHCAP->_hoops_PISAP[1] = _hoops_SCSAS[index];
					_hoops_HHCAP->_hoops_PISAP[2] = _hoops_ICCAS (status._hoops_IPRI, index);
					_hoops_HHCAP->_hoops_HISAP = _hoops_GSSAS[index];
					_hoops_HHCAP->_hoops_IISAP = _hoops_RSSAS[index];
					_hoops_HHCAP->next = null;
					*status._hoops_APPAS = _hoops_HHCAP;
					status._hoops_APPAS = &_hoops_HHCAP->next;
					if (!_hoops_PSCAS && ++status._hoops_PPPAS >=
							nr->_hoops_IRR->_hoops_CCIRP._hoops_SPHPR) {
						status._hoops_CHPAS = false;
						break;
					}
				}
			}

			if (face_count > _hoops_GIGPS) {
				FREE_ARRAY (_hoops_CCSAS, 2 * face_count, int);
				FREE_ARRAY (_hoops_GSSAS, 2 * face_count, float);
			}
		}
	}

	if (_hoops_GPGPS &&
		(_hoops_PSCAS || status._hoops_PPPAS < nr->_hoops_IRR->_hoops_CCIRP._hoops_SPHPR ||
		 !(status._hoops_AHPAS && status._hoops_SPPAS._hoops_HISAP == 0.0f))) {
		if (!BIT (_hoops_IPRI->polyhedron_flags, _hoops_SCRRA) ||
			_hoops_CAGPS (nr, _hoops_IPRI)) {
			_hoops_SARHR	_hoops_SHGPS = _hoops_PPRHR | _hoops_IACHR;

			if (BIT (_hoops_CIPSH, T_FACES)) {
				/* _hoops_IPCP _hoops_RGAR _hoops_AHAP _hoops_GCAS _hoops_IS _hoops_ISPR _hoops_HRGR _hoops_HHHA _hoops_PIGPS. */
				_hoops_SHGPS |= _hoops_HSIPR;
			}

			HD_Assemble_Isolines (nr, status._hoops_IPRI, _hoops_SHGPS);
		}

		if (status._hoops_IPRI->_hoops_CHGPR != null) {
			Polyedge alter *		_hoops_ACP = status._hoops_IPRI->_hoops_CHGPR;
			_hoops_PACIR		_hoops_PHGPS = nr->_hoops_SAIR->_hoops_HHCAR;
			DC_Point *				_hoops_HIGPS = status._hoops_CGCAR;
			float *					_hoops_IIGPS = status.ws;
			_hoops_GRCAR *				_hoops_CIGPS = status._hoops_RRCAR;

			// _hoops_IRS _hoops_IGRH _hoops_SCIPA, _hoops_IPCGP _hoops_RSSA _hoops_CHR _hoops_HAR _hoops_RH _hoops_PSHR _hoops_GAR _hoops_CPHAR _hoops_RSSA, _hoops_HIS _hoops_SR _hoops_RRP
			// _hoops_IS _hoops_SIGPS _hoops_PPR _hoops_HIHP _hoops_CAPR _hoops_GAR _hoops_SR _hoops_PHHR _hoops_IH _hoops_GRR _hoops_IPCGP _hoops_PPR _hoops_PHIH _hoops_CGPR _hoops_CPHR
			nr.Modify()->_hoops_SAIR.Modify();
			_hoops_CGRA alter &	_hoops_SGRA = nr->_hoops_SAIR;

			if (!BIT (sc->options, _hoops_CRPAS)) {
				_hoops_SGRA->_hoops_HHCAR = sc->bounding;

				if (_hoops_APGPS)
					_hoops_SGRA->_hoops_HHCAR._hoops_IACHA(_hoops_HPGPS);
			}

			do {
				int							_hoops_AHGPS;

				ALLOC_ARRAY_ALIGNED_CACHED (status._hoops_CGCAR, _hoops_ACP->point_count, DC_Point, 16);
				ALLOC_ARRAY_ALIGNED_CACHED (status.ws, _hoops_ACP->point_count, float, 16);
				ALLOC_ARRAY_CACHED (status._hoops_RRCAR, _hoops_ACP->point_count, _hoops_GRCAR);

				/* _hoops_GCAPH _hoops_RH _hoops_HSPH _hoops_HPHS _hoops_SIH _hoops_IH _hoops_GRR _hoops_GPHA _hoops_CCA _hoops_GPCAR
				 * _hoops_IS _hoops_RH _hoops_IASC _hoops_CISAR, _hoops_IAS._hoops_ISHI. _hoops_HHGPS[0] _hoops_PAH _hoops_SHH _hoops_PPSPR _hoops_IS _hoops_RH _hoops_RAAP,
				 * _hoops_PPR _hoops_IS _hoops_RH _hoops_SCIA _hoops_IIGR _hoops_RH _hoops_IASC _hoops_CISAR.
				 * _hoops_IHGPS _hoops_GAGPR _hoops_ARCSA _hoops_RPP _hoops_RH _hoops_CPHAR _hoops_HRGR _hoops_GPGS _hoops_RH _hoops_IASC
				 * _hoops_CISAR.
				 */
				_hoops_AHGPS = HD_Acquire_Clip_Points (nr,
													   status._hoops_IPRI->bounding,
													   _hoops_ACP->point_count,
													   _hoops_ACP->points,
													   status._hoops_CGCAR,
													   status.ws,
													   status._hoops_RRCAR);

				if (_hoops_AHGPS != 0)
					_hoops_SISAS (nr, _hoops_ACP);

				FREE_ARRAY_ALIGNED (status._hoops_CGCAR, _hoops_ACP->point_count, DC_Point, 16);
				FREE_ARRAY_ALIGNED (status.ws, _hoops_ACP->point_count, float, 16);
				FREE_ARRAY (status._hoops_RRCAR, _hoops_ACP->point_count, _hoops_GRCAR);

				if (status._hoops_SHPAS && status._hoops_PHPAS)
					break;
			} while ((_hoops_ACP = _hoops_ACP->next) != null);

			_hoops_SGRA->_hoops_HHCAR = _hoops_PHGPS;

			status._hoops_CGCAR = _hoops_HIGPS;
			status.ws = _hoops_IIGPS;
			status._hoops_RRCAR = _hoops_CIGPS;
		}
	}

	if (_hoops_RPGPS &&
		(_hoops_PSCAS || status._hoops_PPPAS < nr->_hoops_IRR->_hoops_CCIRP._hoops_SPHPR ||
		 !(status._hoops_AHPAS && status._hoops_SPPAS._hoops_HISAP == 0.0f) &&
		 !(status._hoops_PHPAS && status._hoops_GHPAS._hoops_HISAP == 0.0f))) {

		/* _hoops_PGSA _hoops_HHH _hoops_SPPR */

		/* _hoops_GHGPS _hoops_HII _hoops_GCGPS _hoops_PPR _hoops_SRSS _hoops_RPPR */

		Polyedge alter *		polyedge;
		_hoops_GHHPR		_hoops_SHGPS = 0;

		if (BIT (_hoops_CIPSH, T_GENERIC_EDGES)) {
			/* _hoops_IPCP _hoops_RGAR _hoops_AHAP _hoops_GCAS _hoops_IS _hoops_ISPR _hoops_HRGR _hoops_HHHA _hoops_PIGPS. */
			_hoops_SHGPS |= _hoops_AHIAA;
		}
		else {
			/* _hoops_ACHSP _hoops_HS _hoops_IS _hoops_ISPR _hoops_SRAPH _hoops_IIGR _hoops_CGSI */
			if (!ANYBIT (_hoops_PPGPS, T_GENERIC_EDGES))
				_hoops_SHGPS |= _hoops_APGI;

			if (BIT (_hoops_CIPSH, T_PERIMETER_EDGES))
				_hoops_SHGPS |= _hoops_AACPR;
			if (BIT (_hoops_CIPSH, _hoops_CRHGP))
				_hoops_SHGPS |= _hoops_CCCPR;
			if (BIT (_hoops_CIPSH, T_MESH_QUAD_EDGES))
				_hoops_SHGPS |= _hoops_AGSPR;
			if (BIT (_hoops_CIPSH, T_HARD_EDGES))
				_hoops_SHGPS |= _hoops_CIIPR;
		}

		if (!ALLBITS (status._hoops_IPRI->_hoops_RSHPR, _hoops_SHGPS) ||
			BIT (_hoops_SHGPS, _hoops_CIIPR) &&
			nr->_hoops_ARA->_hoops_GCIPR != status._hoops_IPRI->_hoops_GCIPR) {
			HI_Assemble_3D_Polyedges ((Polyhedron alter *)status._hoops_IPRI,
									  _hoops_SHGPS,
									  nr->_hoops_ARA->_hoops_GCIPR);
		}

		if ((polyedge = status._hoops_IPRI->_hoops_SHGPR) != null) do {
			_hoops_GHHPR		_hoops_RCGPS;

			_hoops_RCGPS = polyedge->_hoops_PPGI.flags & _hoops_SHGPS;

			if (!BIT (_hoops_RCGPS, _hoops_AHIAA)) {
				if (BIT (_hoops_CIPSH, T_GENERIC_EDGES) ||
					ANYBIT (_hoops_RCGPS, (_hoops_APGI |
										_hoops_AACPR | _hoops_CCCPR | _hoops_CIIPR |
										_hoops_AGSPR))) {
					Polyedge		pe;

					ZERO_STRUCT(&pe, Polyedge);

					pe._hoops_PHHA = polyedge->_hoops_PHHA;
					pe.lengths = polyedge->lengths;
					pe._hoops_AIHA = polyedge->_hoops_AIHA;
					pe._hoops_SPII = polyedge->_hoops_SPII;

					_hoops_SISAS (nr, &pe);
				}
				else if (BIT (_hoops_CIPSH,
							  T_INTERIOR_SILHOUETTE_EDGES)) {
					Polyedge				pe;

					ZERO_STRUCT(&pe, Polyedge);

					pe._hoops_PHHA = polyedge->_hoops_PHHA;
					pe.lengths = polyedge->lengths;
					pe._hoops_AIHA = polyedge->_hoops_AIHA;
					pe._hoops_SPII = polyedge->_hoops_SPII;
					pe._hoops_GSCP = (Polyhedron*)_hoops_IPRI;
					pe.bounding = _hoops_IPRI->bounding;

					_hoops_HGCGA (dc, "silhouette selection", nr);
					dc->_hoops_IPCI->draw_3d_polyedge = _hoops_HCSAS;
					/* _hoops_SIHPC: _hoops_ACGPS _hoops_AASA-_hoops_ISSC */
					/* _hoops_PCGPS _hoops_CHH _hoops_HCGPS _hoops_IPAS
					 * _hoops_PGAP _hoops_CHH _hoops_APRAR _hoops_RH _hoops_GHSHA _hoops_HPPP _hoops_HRII
					 * _hoops_HSAR _hoops_PGSA _hoops_RH _hoops_SPPR.
					 */
					HD_Draw_Silhouette_Edges (nr, &pe);
					_hoops_HGSGA (dc, "silhouette selection");
				}

				if (status._hoops_SHPAS && status._hoops_HHPAS)
					break;
			}
		} while ((polyedge = polyedge->next) != null);

		/* _hoops_CASI _hoops_GH _hoops_ASSIA _hoops_SPPR */
		/*_hoops_RPP (_hoops_IPPSA->_hoops_ASCCP != _hoops_IRAP) {
			_hoops_ICGPS _hoops_RAPC	*_hoops_AIPSH;
			_hoops_AIPSH = (_hoops_ICGPS _hoops_RAPC *)_hoops_IPPSA->_hoops_ASCCP;
			_hoops_AAAGR (_hoops_AIPSH, _hoops_HSAGA._hoops_CPHAR->_hoops_ACHAA, _hoops_ICGPS);
			_hoops_IPPSA->_hoops_ASCCP = _hoops_IRAP;
		}*/
	}

	if (_hoops_APGPS &&
		(_hoops_PSCAS || status._hoops_PPPAS < nr->_hoops_IRR->_hoops_CCIRP._hoops_SPHPR ||
		 !(status._hoops_AHPAS && status._hoops_SPPAS._hoops_HISAP == 0.0f) &&
		 !(status._hoops_PHPAS && status._hoops_GHPAS._hoops_HISAP == 0.0f) &&
		 !(status._hoops_HHPAS && status._hoops_CCCCP._hoops_HISAP == 0.0f))) {
		status._hoops_RHPAS._hoops_HISAP = status._hoops_CCCCP._hoops_HISAP;

		if (_hoops_SCCAS (nr, status._hoops_IPRI->point_count,
								   status._hoops_CGCAR, status.ws, status._hoops_RRCAR, &status._hoops_RHPAS)) {
			status._hoops_IHPAS = true;
		}
	}

	if (status._hoops_AHPAS)
		HD_Elaborate_Selection (nr,
								(Geometry const *)_hoops_IPRI, _hoops_IPRI->key, _hoops_AIRIR(_hoops_IPRI),
								(int) (status._hoops_SPPAS.vertex1 - status._hoops_CGCAR),
								(int) (status._hoops_SPPAS.vertex2 - status._hoops_CGCAR),
								_hoops_ICCAS (status._hoops_IPRI, status._hoops_SPPAS.face),
								status._hoops_SPPAS._hoops_RCSAP,
								status._hoops_SPPAS._hoops_HISAP,
								T_FACES, status._hoops_ACSAP);
	else if (status._hoops_PHPAS)
		HD_Elaborate_Selection (nr,
								(Geometry const *)_hoops_IPRI, _hoops_IPRI->key, _hoops_AIRIR(_hoops_IPRI),
								-1,
								status._hoops_GHPAS.face,	// _hoops_SGH _hoops_HSP _hoops_IS _hoops_ASH _hoops_IPCGP _hoops_RARP
								status._hoops_IPRI->_hoops_AHSCC,
								status._hoops_GHPAS._hoops_RCSAP,
								status._hoops_GHPAS._hoops_HISAP,
								_hoops_GPA, status._hoops_ACSAP);
	else if (status._hoops_HHPAS)
		HD_Elaborate_Selection (nr,
								(Geometry const *)_hoops_IPRI, _hoops_IPRI->key, _hoops_AIRIR(_hoops_IPRI),
								(int) (status._hoops_CCCCP.vertex1 - status._hoops_CGCAR),
								(int) (status._hoops_CCCCP.vertex2 - status._hoops_CGCAR),
								_hoops_ICCAS (status._hoops_IPRI, status._hoops_CCCCP.face),
								status._hoops_CCCCP._hoops_RCSAP,
								status._hoops_CCCCP._hoops_HISAP,
								(status._hoops_CCCCP.face == -1) ?
										T_ANY_EDGE : T_FACES, status._hoops_ACSAP);
	else if (status._hoops_IHPAS)
		/* _hoops_GIHA _hoops_RGAR _hoops_HS _hoops_PCCP _hoops_SHI _hoops_HIS _hoops_RH _hoops_SCCIA _hoops_PPR _hoops_GSCIA _hoops_CHR -1. */
		HD_Elaborate_Selection (nr,
								(Geometry const *)_hoops_IPRI, _hoops_IPRI->key, _hoops_AIRIR(_hoops_IPRI),
								(int) (status._hoops_RHPAS.vertex1 - status._hoops_CGCAR),
								-1,
								-1,
								status._hoops_RHPAS._hoops_RCSAP,
								status._hoops_RHPAS._hoops_HISAP,
								T_VERTICES, status._hoops_ACSAP);
	else if (status._hoops_ACSAP) {
		/* _hoops_SR _hoops_PAHA'_hoops_RA _hoops_HS _hoops_SGCRP _hoops_PPCIA _hoops_HCCPR _hoops_SR _hoops_GACC _hoops_HS _hoops_SHISR _hoops_PPCIA */
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				"unexpected case encountered while selecting a polyhedron");
		while (status._hoops_ACSAP != null) {
			_hoops_AISAP *victim = status._hoops_ACSAP;
			status._hoops_ACSAP = victim->next;
			FREE (victim, _hoops_AISAP);
		}
	}

	FREE_ARRAY_ALIGNED (status._hoops_CGCAR, status._hoops_IPRI->point_count, DC_Point, 16);
	FREE_ARRAY_ALIGNED (status.ws, status._hoops_IPRI->point_count, float, 16);
	FREE_ARRAY (status._hoops_RRCAR, status._hoops_IPRI->point_count, _hoops_GRCAR);
#endif
}



GLOBAL_FUNCTION void HD_Select_Sphere_Polyhedron (
	Net_Rendition const &		inr,
	Sphere const *				sphere)
{
#ifndef DISABLE_SELECTION
#ifndef _hoops_RRHIR
	Net_Rendition				nr = inr;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter	*	sc = dc->_hoops_APHHP;
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	_hoops_ACHR					_hoops_CCGPS;
	_hoops_ACHR					_hoops_SCGPS;

	_hoops_SCGPS = _hoops_CCGPS = nr->_hoops_RGP | _hoops_RRGH->_hoops_PHARP;

	if (BIT (_hoops_CCGPS, T_FACES))
		_hoops_CCGPS |= _hoops_GPA;
	if (BIT (_hoops_CCGPS, T_INTERIOR_SILHOUETTE_EDGES))
		_hoops_SCGPS |= T_EDGES;

	_hoops_CCGPS &= _hoops_RRGH->_hoops_AAICA;
	_hoops_SCGPS &= _hoops_RRGH->_hoops_AAICA;

	if (!ANYBIT (_hoops_SCGPS, T_FACES | T_EDGES))
		return;


	_hoops_PCCCP			status;
	Point						points[1024], *p;
	Vector						_hoops_ICHA[1024], *_hoops_HCPCP;
	DC_Point					_hoops_CGCAR[1024];
	float						ws[1024];
	_hoops_GRCAR					_hoops_RRCAR[1024];
	int							_hoops_AIHA[4096], *vi;
	int							face_indices[4096], *fi;
	int							lengths[1024], *l;
	int							point_count;
	Tristrip					tristrip;
	int							i, j, _hoops_SSPAR;
	float						theta, phi, _hoops_GSGPS;
	float						_hoops_RSGPS, _hoops_ASGPS;
	float						_hoops_GPIAA, _hoops_RPIAA;
	float						_hoops_HAIAA, _hoops_IAIAA;
	int							_hoops_GIIRC, _hoops_RIIRC;

	ZERO_STRUCT (&tristrip, Tristrip);
	_hoops_CAHS (&tristrip);

	sc->_hoops_AICCP = (void alter *)&status; /* _hoops_RIH _hoops_SCH _hoops_RHIR _hoops_IS _hoops_HRCC _hoops_CIPIP _hoops_APSI */
	status.sc = sc;
	status._hoops_IPRI = null;

	status._hoops_AHPAS = false;
	status._hoops_HHPAS = false;
	status._hoops_IHPAS = false;

	status._hoops_CCCCP._hoops_HISAP =
	  status._hoops_SPPAS._hoops_HISAP =
	  status._hoops_RHPAS._hoops_HISAP = sc->_hoops_GICAH;

	status._hoops_ACSAP = null;
	status._hoops_APPAS = &status._hoops_ACSAP;
	status._hoops_PPPAS = 0;
	status._hoops_CHPAS = false;
	status._hoops_SHPAS = nr->_hoops_IRR->_hoops_CCIRP._hoops_SPHPR < 0;

	/* _hoops_SRPR _hoops_RCRR, _hoops_RCSC _hoops_RGR _hoops_HRGR _hoops_IIAC _hoops_IRS _hoops_IGRH _hoops_HRHC _hoops_HSAR _hoops_AGIAS. */
	status._hoops_SPPAS._hoops_RCSAP = MAX_FLOAT * 0.99f; /* _hoops_IGI _hoops_RAS '_hoops_SPGPS' */

	_hoops_GIIRC = 24;
	_hoops_RIIRC = 1 + _hoops_GIIRC/2;


	p = points;
	_hoops_HCPCP = _hoops_ICHA;
	_hoops_RSGPS = 360.0f/_hoops_GIIRC;
	_hoops_ASGPS = 180.0f/(_hoops_RIIRC-1);
	if (sphere->_hoops_CSPIR) {
		for (phi = 0, j = 0; j < _hoops_RIIRC; phi += _hoops_ASGPS, j++) {
			if (phi > 180.0f)
				phi = 180.0f;
			HI_SinCos(phi, &_hoops_HAIAA, &_hoops_IAIAA);
			for (theta = 0, i = 0; i < _hoops_GIIRC; theta += _hoops_RSGPS, i++) {
				HI_SinCos(theta, &_hoops_GPIAA, &_hoops_RPIAA);
				_hoops_GSGPS = _hoops_HAIAA * _hoops_RPIAA;
				_hoops_HCPCP->x = _hoops_GSGPS * sphere->_hoops_CSPIR[0].x;
				_hoops_HCPCP->y = _hoops_GSGPS * sphere->_hoops_CSPIR[0].y;
				_hoops_HCPCP->z = _hoops_GSGPS * sphere->_hoops_CSPIR[0].z;
				_hoops_GSGPS = _hoops_IAIAA;
				_hoops_HCPCP->x += _hoops_GSGPS * sphere->_hoops_CSPIR[1].x;
				_hoops_HCPCP->y += _hoops_GSGPS * sphere->_hoops_CSPIR[1].y;
				_hoops_HCPCP->z += _hoops_GSGPS * sphere->_hoops_CSPIR[1].z;
				_hoops_GSGPS = _hoops_HAIAA * _hoops_GPIAA;
				_hoops_HCPCP->x += _hoops_GSGPS * sphere->_hoops_CSPIR[2].x;
				_hoops_HCPCP->y += _hoops_GSGPS * sphere->_hoops_CSPIR[2].y;
				_hoops_HCPCP->z += _hoops_GSGPS * sphere->_hoops_CSPIR[2].z;
				p->x = sphere->data.center.x + _hoops_HCPCP->x;
				p->y = sphere->data.center.y + _hoops_HCPCP->y;
				p->z = sphere->data.center.z + _hoops_HCPCP->z;
				_hoops_HCPCP++;
				p++;
			}
		}
	}
	else {
		for (phi = 0, j = 0; j < _hoops_RIIRC; phi += _hoops_ASGPS, j++) {
			if (phi > 180.0f)
				phi = 180.0f;
			HI_SinCos(phi, &_hoops_HAIAA, &_hoops_IAIAA);
			for (theta = 0, i = 0; i < _hoops_GIIRC; theta += _hoops_RSGPS, i++) {
				HI_SinCos(theta, &_hoops_GPIAA, &_hoops_RPIAA);
				_hoops_HCPCP->x = _hoops_HAIAA * _hoops_RPIAA;
				_hoops_HCPCP->y = _hoops_IAIAA;
				_hoops_HCPCP->z = _hoops_HAIAA * _hoops_GPIAA;
				p->x = sphere->data.center.x + (_hoops_HCPCP->x * sphere->data.radius);
				p->y = sphere->data.center.y + (_hoops_HCPCP->y * sphere->data.radius);
				p->z = sphere->data.center.z + (_hoops_HCPCP->z * sphere->data.radius);
				_hoops_HCPCP++;
				p++;
			}
		}
	}
	point_count = p - points;

	{	int							_hoops_AHGPS;
		_hoops_PACIR			_hoops_PHGPS;
		_hoops_CGRA alter &	_hoops_SGRA = nr->_hoops_SAIR;

		_hoops_PHGPS = _hoops_SGRA->_hoops_HHCAR;

		if (!BIT (sc->options, _hoops_CRPAS)) {
			_hoops_SGRA->_hoops_HHCAR = sc->bounding;
		}
		else if (0) {
			_hoops_SGRA->_hoops_HHCAR = sc->bounding;
			_hoops_SGRA->_hoops_HHCAR._hoops_IACHA(50.0f);
		}

		/* _hoops_GCAPH _hoops_RH _hoops_HSPH _hoops_HPHS _hoops_SIH _hoops_IH _hoops_GRR _hoops_GPHA _hoops_CCA _hoops_GPCAR
		 * _hoops_IS _hoops_RH _hoops_IASC _hoops_CISAR, _hoops_IAS._hoops_ISHI. _hoops_HHGPS[0] _hoops_PAH _hoops_SHH _hoops_PPSPR _hoops_IS _hoops_RH _hoops_RAAP,
		 * _hoops_PPR _hoops_IS _hoops_RH _hoops_SCIA _hoops_IIGR _hoops_RH _hoops_IASC _hoops_CISAR.
		 * _hoops_IHGPS _hoops_GAGPR _hoops_ARCSA _hoops_RPP _hoops_RH _hoops_CPHAR _hoops_HRGR _hoops_GPGS _hoops_RH _hoops_IASC
		 * _hoops_CISAR.
		 */
		_hoops_AHGPS = HD_Acquire_Clip_Points (nr, null, point_count, points, _hoops_CGCAR, ws, _hoops_RRCAR);

		_hoops_SGRA->_hoops_HHCAR = _hoops_PHGPS;

		if (_hoops_AHGPS == 0)
			return;
	}
	status._hoops_CGCAR = _hoops_CGCAR;
	status.ws = ws;
	status._hoops_RRCAR = _hoops_RRCAR;


	tristrip.points = points;
	tristrip.point_count = point_count;
	tristrip.lengths = lengths;
	tristrip._hoops_AIHA = vi = _hoops_AIHA;
	tristrip.face_indices = fi = face_indices;

	l = lengths;
	vi = _hoops_AIHA;
	_hoops_SSPAR = 0;
	for (j = 0; j < _hoops_RIIRC-1; j++) {
		for (i = 0; i < _hoops_GIIRC-1; i++) {
			*l++ = 4;
			*vi++ = j*_hoops_GIIRC + i;
			*vi++ = (j+1)*_hoops_GIIRC + i;
			*vi++ = j*_hoops_GIIRC + i + 1;
			*vi++ = (j+1)*_hoops_GIIRC + i + 1;
			*fi++ = _hoops_SSPAR;
			*fi++ = _hoops_SSPAR;
			*fi++ = _hoops_SSPAR;
			*fi++ = _hoops_SSPAR++;
		}
		*l++ = 4;
		*vi++ = j*_hoops_GIIRC + _hoops_GIIRC-1;
		*vi++ = (j+1)*_hoops_GIIRC + _hoops_GIIRC-1;
		*vi++ = j*_hoops_GIIRC;
		*vi++ = (j+1)*_hoops_GIIRC;
		*fi++ = _hoops_SSPAR;
		*fi++ = _hoops_SSPAR;
		*fi++ = _hoops_SSPAR;
		*fi++ = _hoops_SSPAR++;
	}
	tristrip.face_count = _hoops_GIIRC*(_hoops_RIIRC-1);
	tristrip.total = vi - _hoops_AIHA;
	tristrip._hoops_PHHA = l - lengths;

	if (ANYBIT (_hoops_CCGPS, T_FACES|T_EDGES)) {
		_hoops_ICSAS (nr, &tristrip, null, null, null, null, null);
	}
	else if (BIT (_hoops_CCGPS, T_INTERIOR_SILHOUETTE_EDGES)) {
		_hoops_HGCGA (dc, "silhouette selection", nr);
		dc->_hoops_IPCI->draw_3d_polyedge = _hoops_HCSAS;
		dc->_hoops_IPCI->draw_3d_tristrip = _hoops_AHSAS;
		/* _hoops_SIHPC: _hoops_ACGPS _hoops_AASA-_hoops_ISSC */
		/* _hoops_PCGPS _hoops_CHH _hoops_HCGPS _hoops_IPAS
		 * _hoops_PGAP _hoops_CHH _hoops_APRAR _hoops_RH _hoops_GHSHA _hoops_HPPP _hoops_HRII
		 * _hoops_HSAR _hoops_PGSA _hoops_RH _hoops_SPPR.
		 */
		HD_Std_3D_Sphere (nr, sphere);
		_hoops_HGSGA (dc, "silhouette selection");
	}

	if (BIT (_hoops_CCGPS, T_FACES) && status._hoops_AHPAS)
		HD_Elaborate_Selection (nr,
								(Geometry const *)sphere, sphere->key, _hoops_AIRIR(sphere),
								0, 0, 0,
								status._hoops_SPPAS._hoops_RCSAP,
								status._hoops_SPPAS._hoops_HISAP,
								T_FACES, null);
	else if (BIT (_hoops_CCGPS, T_ANY_EDGE) && status._hoops_HHPAS)
		HD_Elaborate_Selection (nr,
								(Geometry const *)sphere, sphere->key, _hoops_AIRIR(sphere),
								0, 0, 0,
								status._hoops_CCCCP._hoops_RCSAP,
								status._hoops_CCCCP._hoops_HISAP,
								(status._hoops_CCCCP.face == -1) ?
										T_ANY_EDGE : T_FACES, null);

	if (_hoops_ISAI (&tristrip) != 0)
		/* _hoops_SR _hoops_AAPR _hoops_HPIAA _hoops_SGS '_hoops_GARI' _hoops_HRGR _hoops_HAR _hoops_GCAII _hoops_HPP _hoops_PA _hoops_PIGS _hoops_HPP _hoops_PSGPS */
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				"Invalid tristrip reference count 2");

#endif
#endif
}



GLOBAL_FUNCTION void HD_Select_Cylinder (
	Net_Rendition const &		inr,
	Cylinder const *			cylinder) {
#ifndef DISABLE_SELECTION
#ifndef _hoops_PSPIR
	Net_Rendition				nr = inr;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter *	sc = dc->_hoops_APHHP;
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	_hoops_ACHR					_hoops_CCGPS;
	_hoops_ACHR					_hoops_SCGPS;

	_hoops_SCGPS = _hoops_CCGPS = nr->_hoops_RGP | _hoops_RRGH->_hoops_PHARP;

	if (BIT (_hoops_CCGPS, T_FACES))
		_hoops_CCGPS |= _hoops_GPA;
	if (BIT (_hoops_CCGPS, T_INTERIOR_SILHOUETTE_EDGES))
		_hoops_SCGPS |= T_EDGES;

	_hoops_CCGPS &= _hoops_RRGH->_hoops_AAICA;
	_hoops_SCGPS &= _hoops_RRGH->_hoops_AAICA;

	if (!ANYBIT (_hoops_SCGPS, T_FACES | T_EDGES))
		return;


	_hoops_PCCCP			status;
	Point const *				first  = &cylinder->axis[0];
	Point const *				_hoops_IAGRA = &cylinder->axis[1];
	Vector						_hoops_GGHI;
	Vector						_hoops_RGHI;
	Point						points[256];
	DC_Point					_hoops_CGCAR[256];
	float						ws[256];
	_hoops_GRCAR					_hoops_RRCAR[256];
	int							_hoops_AIHA[512];
	int							face_indices[512];
	int							lengths[3];
	Vector						axis;
	int							_hoops_HGII;
	float						_hoops_GGHCR, _hoops_AGHCR;
	int							ii;
	float						delta;
	Tristrip					tristrip;
	int							*vi, *fi;

	ZERO_STRUCT(&tristrip, Tristrip);

	if (BIT (nr->transform_rendition->_hoops_APH, Heur_Culling_VIEW_FRUSTUM)) {
		_hoops_CAIS	sphere;

		sphere.center = _hoops_AICIR(cylinder->axis[0], cylinder->axis[1]);

		Vector	_hoops_AASIC = sphere.center - cylinder->axis[0];

		float	_hoops_HSGPS = _hoops_AASIC._hoops_SSRP(_hoops_AASIC);

		sphere.radius = _hoops_SGIHR(_hoops_HSGPS + cylinder->radius*cylinder->radius);

		Test _hoops_ASIS = Test_DISJOINT;

		Net_Rendition				_hoops_ISGPS = nr.Copy();
		_hoops_CGRA			_hoops_SGRA = _hoops_ISGPS->_hoops_SAIR.Modify();

		_hoops_SGRA->_hoops_HHCAR.left = sc->bounding.left;
		_hoops_SGRA->_hoops_HHCAR.right = sc->bounding.right;
		_hoops_SGRA->_hoops_HHCAR.bottom = sc->bounding.bottom;
		_hoops_SGRA->_hoops_HHCAR.top = sc->bounding.top;

		HD_Transform_And_Test_Simple_Sphere (_hoops_ISGPS, 1, &sphere, null, 0.0f, 0.0f, &_hoops_ASIS, null, null);

		if (_hoops_ASIS == Test_DISJOINT)
			return;
	}

	sc->_hoops_AICCP = (void alter *)&status; /* _hoops_RIH _hoops_SCH _hoops_RHIR _hoops_IS _hoops_HRCC _hoops_CIPIP _hoops_APSI */
	status.sc = sc;
	status._hoops_IPRI = null;

	status._hoops_AHPAS = false;
	status._hoops_HHPAS = false;
	status._hoops_IHPAS = false;

	status._hoops_CCCCP._hoops_HISAP =
	  status._hoops_SPPAS._hoops_HISAP =
	  status._hoops_RHPAS._hoops_HISAP = sc->_hoops_GICAH;

	status._hoops_ACSAP = null;
	status._hoops_APPAS = &status._hoops_ACSAP;
	status._hoops_PPPAS = 0;
	status._hoops_CHPAS = false;
	status._hoops_SHPAS = nr->_hoops_IRR->_hoops_CCIRP._hoops_SPHPR < 0;

	/* _hoops_SRPR _hoops_RCRR, _hoops_RCSC _hoops_RGR _hoops_HRGR _hoops_IIAC _hoops_IRS _hoops_IGRH _hoops_HRHC _hoops_HSAR _hoops_AGIAS. */
	status._hoops_SPPAS._hoops_RCSAP = MAX_FLOAT * 0.99f; /* _hoops_IGI _hoops_RAS '_hoops_SPGPS' */


	_hoops_HGII = 24;
	delta = 360.0f / _hoops_HGII;

	axis.x = _hoops_IAGRA->x - first->x;
	axis.y = _hoops_IAGRA->y - first->y;
	axis.z = _hoops_IAGRA->z - first->z;

	_hoops_GGHI.x = cylinder->_hoops_CSPIR.axis[0].x * cylinder->radius;
	_hoops_GGHI.y = cylinder->_hoops_CSPIR.axis[0].y * cylinder->radius;
	_hoops_GGHI.z = cylinder->_hoops_CSPIR.axis[0].z * cylinder->radius;
	_hoops_RGHI.x = cylinder->_hoops_CSPIR.axis[1].x * cylinder->radius;
	_hoops_RGHI.y = cylinder->_hoops_CSPIR.axis[1].y * cylinder->radius;
	_hoops_RGHI.z = cylinder->_hoops_CSPIR.axis[1].z * cylinder->radius;

	for (ii=0; ii<_hoops_HGII; ++ii) {
		float			_hoops_RAHCR = ii * delta;

		_hoops_RICH (_hoops_RAHCR, _hoops_GGHCR, _hoops_AGHCR);

		points[ii].x = first->x + _hoops_AGHCR * _hoops_GGHI.x + _hoops_GGHCR * _hoops_RGHI.x;
		points[ii].y = first->y + _hoops_AGHCR * _hoops_GGHI.y + _hoops_GGHCR * _hoops_RGHI.y;
		points[ii].z = first->z + _hoops_AGHCR * _hoops_GGHI.z + _hoops_GGHCR * _hoops_RGHI.z;

		points[ii+_hoops_HGII].x = points[ii].x + axis.x;
		points[ii+_hoops_HGII].y = points[ii].y + axis.y;
		points[ii+_hoops_HGII].z = points[ii].z + axis.z;
	}

	{	int							_hoops_AHGPS;
		_hoops_PACIR			_hoops_PHGPS;
		_hoops_CGRA alter &	_hoops_SGRA = nr->_hoops_SAIR;

		_hoops_PHGPS = _hoops_SGRA->_hoops_HHCAR;

		if (!BIT (sc->options, _hoops_CRPAS)) {
			_hoops_SGRA->_hoops_HHCAR = sc->bounding;
		}
		else if (0) {
			_hoops_SGRA->_hoops_HHCAR = sc->bounding;
			_hoops_SGRA->_hoops_HHCAR._hoops_IACHA(50.0f);
		}

		/* _hoops_GCAPH _hoops_RH _hoops_HSPH _hoops_HPHS _hoops_SIH _hoops_IH _hoops_GRR _hoops_GPHA _hoops_CCA _hoops_GPCAR
		 * _hoops_IS _hoops_RH _hoops_IASC _hoops_CISAR, _hoops_IAS._hoops_ISHI. _hoops_HHGPS[0] _hoops_PAH _hoops_SHH _hoops_PPSPR _hoops_IS _hoops_RH _hoops_RAAP,
		 * _hoops_PPR _hoops_IS _hoops_RH _hoops_SCIA _hoops_IIGR _hoops_RH _hoops_IASC _hoops_CISAR.
		 * _hoops_IHGPS _hoops_GAGPR _hoops_ARCSA _hoops_RPP _hoops_RH _hoops_CPHAR _hoops_HRGR _hoops_GPGS _hoops_RH _hoops_IASC
		 * _hoops_CISAR.
		 */
		_hoops_AHGPS = HD_Acquire_Clip_Points (nr, null, 2 * _hoops_HGII, points, _hoops_CGCAR, ws, _hoops_RRCAR);

		_hoops_SGRA->_hoops_HHCAR = _hoops_PHGPS;

		if (_hoops_AHGPS == 0)
			return;
	}
	status._hoops_CGCAR = _hoops_CGCAR;
	status.ws = ws;
	status._hoops_RRCAR = _hoops_RRCAR;

	tristrip.points = points;
	tristrip.point_count = 2 * _hoops_HGII;
	tristrip.face_count = _hoops_HGII + 2;

	tristrip.lengths = lengths;
	tristrip._hoops_AIHA = vi = _hoops_AIHA;
	tristrip.face_indices = fi = face_indices;


	/* _hoops_SRS _hoops_CGGR _hoops_CSGPS _hoops_AARI */
	lengths[tristrip._hoops_PHHA++] = 2*_hoops_HGII+2;

	/* _hoops_HSPP "_hoops_ARPP" _hoops_RH _hoops_GSSR _hoops_ICPPR */
	*vi++ = _hoops_HGII-1;
	*vi++ = _hoops_HGII-1 + _hoops_HGII;
	*fi++ = 0;
	*fi++ = 0;
	for (ii=0; ii<_hoops_HGII; ii++) {
		*vi++ = ii;
		*fi++ = ii;
		*vi++ = ii+_hoops_HGII;
		*fi++ = ii;
	}

	if (cylinder->flags & _hoops_IHHIA) {
		lengths[tristrip._hoops_PHHA++] = _hoops_HGII;
		for (ii=0; ii<_hoops_HGII; ii++) {
			if (ii & 1)
				*vi++ = _hoops_HGII-1 - ii/2;
			else
				*vi++ = ii/2;
			*fi++ = _hoops_HGII;
		}
	}

	if (cylinder->flags & _hoops_SHHIA) {
		lengths[tristrip._hoops_PHHA++] = _hoops_HGII;
		for (ii=0; ii<_hoops_HGII; ii++) {
			if (ii & 1)
				*vi++ = ii/2 + _hoops_HGII;
			else
				*vi++ = _hoops_HGII-1 - ii/2 + _hoops_HGII;
			*fi++ = _hoops_HGII + 1;
		}
	}

	if (ANYBIT (_hoops_CCGPS, T_FACES|T_EDGES)) {
		_hoops_ICSAS (nr, &tristrip, null, null, null, null, null);
	}
	else if (BIT (_hoops_CCGPS, T_INTERIOR_SILHOUETTE_EDGES)) {
		_hoops_HGCGA (dc, "silhouette selection", nr);
		dc->_hoops_IPCI->draw_3d_polyedge = _hoops_HCSAS;
		dc->_hoops_IPCI->draw_3d_tristrip = _hoops_AHSAS;
		/* _hoops_SIHPC: _hoops_ACGPS _hoops_AASA-_hoops_ISSC */
		/* _hoops_PCGPS _hoops_CHH _hoops_HCGPS _hoops_IPAS
		 * _hoops_PGAP _hoops_CHH _hoops_APRAR _hoops_RH _hoops_GHSHA _hoops_HPPP _hoops_HRII
		 * _hoops_HSAR _hoops_PGSA _hoops_RH _hoops_SPPR.
		 */
		HD_Std_3D_Cylinder (nr, cylinder);
		_hoops_HGSGA (dc, "silhouette selection");
	}

	if (BIT (_hoops_CCGPS, T_FACES) && status._hoops_AHPAS)
		HD_Elaborate_Selection (nr,
								(Geometry const *)cylinder, cylinder->key, _hoops_AIRIR(cylinder),
								0, 0, 0,
								status._hoops_SPPAS._hoops_RCSAP,
								status._hoops_SPPAS._hoops_HISAP,
								T_FACES, null);
	else if (BIT (_hoops_CCGPS, T_ANY_EDGE) && status._hoops_HHPAS)
		HD_Elaborate_Selection (nr,
								(Geometry const *)cylinder, cylinder->key, _hoops_AIRIR(cylinder),
								0, 0, 0,
								status._hoops_CCCCP._hoops_RCSAP,
								status._hoops_CCCCP._hoops_HISAP,
								(status._hoops_CCCCP.face == -1) ? T_ANY_EDGE : T_FACES, null);

#endif
#endif
}



GLOBAL_FUNCTION void HD_Select_PolyCylinder (
	Net_Rendition const &		inr,
	PolyCylinder const *		polycylinder) {
#ifndef DISABLE_SELECTION
#ifndef _hoops_PSPIR
	Net_Rendition				nr = inr;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter *	sc = dc->_hoops_APHHP;
	_hoops_PCCCP			status;
	Point						_hoops_HRIGA[512];
	DC_Point					_hoops_SSGPS[512];
	float						_hoops_HPCPA[512];
	_hoops_GRCAR					_hoops_GGRPS[512];
	int							_hoops_AGCS[1536];
	int							_hoops_PGCS[1536];
	int							_hoops_RGRPS[758];
	float						_hoops_AGRPS[512];
	Point *						points = _hoops_HRIGA;
	DC_Point *					_hoops_CGCAR = _hoops_SSGPS;
	float *						ws = _hoops_HPCPA;
	_hoops_GRCAR *					_hoops_RRCAR = _hoops_GGRPS;
	int *						_hoops_AIHA = _hoops_AGCS;
	int *						face_indices = _hoops_PGCS;
	float *						_hoops_HCHA = _hoops_AGRPS;
	int *						lengths = _hoops_RGRPS;
	int							_hoops_HGII;
	float						_hoops_GGHCR, _hoops_AGHCR;
	int							ii, _hoops_ICRHH;
	float						delta;
	/* _hoops_PSP _hoops_RRP _hoops_IH _hoops_ACRI _hoops_PGGA _hoops_SR _hoops_CHR _hoops_HAR _hoops_ARPRR _hoops_IS _hoops_ASRC _hoops_HSP _hoops_PAR _hoops_ISHA _hoops_PSPI.
	 * _hoops_RPGP _hoops_ACSRR _hoops_CRHH _hoops_RGAR. */
	Tristrip					tristrip;
	int							*vi, *fi;
	int							offset1, offset2;
	int							_hoops_HCRGR;
	int							_hoops_PGRPS;
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	_hoops_ACHR					_hoops_CCGPS;
	bool						_hoops_HHAHR = false;
	int							_hoops_HGRPS;
	_hoops_AGHIR const *_hoops_PGHIR = polycylinder->_hoops_RGHIR;
	int							_hoops_GCSAS = 0;

	if (polycylinder->point_count < 2)
		return;

	_hoops_CCGPS = nr->_hoops_RGP | _hoops_RRGH->_hoops_PHARP;
	if (BIT (_hoops_CCGPS, T_FACES))
		_hoops_CCGPS |= _hoops_GPA;
	_hoops_CCGPS &= _hoops_RRGH->_hoops_AAICA | T_INTERIOR_SILHOUETTE_EDGES;

	if (!ANYBIT (_hoops_CCGPS, T_FACES | _hoops_GPA | T_EDGES | T_INTERIOR_SILHOUETTE_EDGES))
		return;

	if (BIT (nr->transform_rendition->_hoops_APH, Heur_Culling_VIEW_FRUSTUM)) {
		_hoops_PACIR		_hoops_IPGPS;
		Int_Rectangle			_hoops_CPGPS;

		_hoops_IPGPS = sc->bounding;
		_hoops_CPGPS = sc->bounding;

		if (HD_Transform_And_Test_Bounding (nr, &polycylinder->bounding,
											&_hoops_IPGPS, &_hoops_CPGPS,
											0.0f) == Test_DISJOINT)
			return;
	}

	ZERO_STRUCT (&tristrip, Tristrip);

	ZERO_STRUCT (&status, _hoops_PCCCP);
	sc->_hoops_AICCP = (void alter *)&status; /* _hoops_RIH _hoops_SCH _hoops_RHIR _hoops_IS _hoops_HRCC _hoops_CIPIP _hoops_APSI */
	status.sc = sc;

	status._hoops_SPPAS._hoops_HISAP =
		status._hoops_GHPAS._hoops_HISAP =
			status._hoops_CCCCP._hoops_HISAP =
				status._hoops_RHPAS._hoops_HISAP = sc->_hoops_GICAH;

	status._hoops_APPAS = &status._hoops_ACSAP;
	status._hoops_SHPAS = nr->_hoops_IRR->_hoops_CCIRP._hoops_SPHPR < 0;

	/* _hoops_SRPR _hoops_RCRR, _hoops_RCSC _hoops_RGR _hoops_HRGR _hoops_IIAC _hoops_IRS _hoops_IGRH _hoops_HRHC _hoops_HSAR _hoops_AGIAS. */
	status._hoops_SPPAS._hoops_RCSAP = MAX_FLOAT * 0.99f; /* _hoops_IGI _hoops_RAS '_hoops_SPGPS' */



	_hoops_HGII = 24;
	delta = 360.0f / _hoops_HGII;

	_hoops_HCRGR = polycylinder->point_count * _hoops_HGII;
	_hoops_PGRPS = _hoops_HCRGR - _hoops_HGII;	/* _hoops_RHAP _hoops_HAR _hoops_GCIS _hoops_RIRR */

	if (_hoops_HCRGR > _hoops_GGAPR(_hoops_HRIGA)) {
		ALLOC_ARRAY_ALIGNED (points, _hoops_HCRGR, Point, 16);
		ALLOC_ARRAY_ALIGNED (_hoops_CGCAR, _hoops_HCRGR, DC_Point, 16);
		ALLOC_ARRAY_ALIGNED (ws, _hoops_HCRGR, float, 16);
		ALLOC_ARRAY (_hoops_RRCAR, _hoops_HCRGR, _hoops_GRCAR);
		ALLOC_ARRAY (_hoops_AIHA, 3*_hoops_HCRGR, int);
		ALLOC_ARRAY (face_indices, 3*_hoops_HCRGR, int);
		ALLOC_ARRAY (lengths, 2 * (polycylinder->point_count + _hoops_HGII), int);
		ALLOC_ARRAY (_hoops_HCHA, _hoops_HCRGR, float);
	}

	_hoops_HHAHR = BIT (nr->_hoops_ARA->geometry_options, _hoops_RHGAP);

	if (!_hoops_HHAHR)
		_hoops_HGRPS = 0;
	else
		_hoops_HGRPS = polycylinder->_hoops_ISPIR-1;

	int						_hoops_IGRPS = 0, _hoops_CGRPS = 1;

	if (BIT (nr->_hoops_ARA->geometry_options, _hoops_AHGAP)) {
		_hoops_IGRPS = polycylinder->point_count - 1;
		_hoops_CGRPS = -1;
	}


	for (_hoops_ICRHH=0; _hoops_ICRHH<polycylinder->point_count; _hoops_ICRHH++) {
		Point const *		center;
		Vector				_hoops_GGHI;
		Vector				_hoops_RGHI;
		float				radius = polycylinder->radii[_hoops_HGRPS];

		center = &polycylinder->points[_hoops_ICRHH];
		_hoops_GGHI.x = polycylinder->_hoops_CSPIR[_hoops_ICRHH].axis[0].x * radius;
		_hoops_GGHI.y = polycylinder->_hoops_CSPIR[_hoops_ICRHH].axis[0].y * radius;
		_hoops_GGHI.z = polycylinder->_hoops_CSPIR[_hoops_ICRHH].axis[0].z * radius;
		_hoops_RGHI.x = polycylinder->_hoops_CSPIR[_hoops_ICRHH].axis[1].x * radius;
		_hoops_RGHI.y = polycylinder->_hoops_CSPIR[_hoops_ICRHH].axis[1].y * radius;
		_hoops_RGHI.z = polycylinder->_hoops_CSPIR[_hoops_ICRHH].axis[1].z * radius;

		for (ii=0; ii<_hoops_HGII; ++ii) {
			float	_hoops_RAHCR = ii * delta + polycylinder->_hoops_GGHIR[_hoops_ICRHH];
			int		index = _hoops_ICRHH*_hoops_HGII+ii;

			_hoops_RICH (_hoops_RAHCR, _hoops_GGHCR, _hoops_AGHCR);

			points[index].x = center->x + _hoops_AGHCR * _hoops_GGHI.x + _hoops_GGHCR * _hoops_RGHI.x;
			points[index].y = center->y + _hoops_AGHCR * _hoops_GGHI.y + _hoops_GGHCR * _hoops_RGHI.y;
			points[index].z = center->z + _hoops_AGHCR * _hoops_GGHI.z + _hoops_GGHCR * _hoops_RGHI.z;

			if (_hoops_PGHIR) {
				_hoops_CGHIR		flags = _hoops_PGHIR->flags[_hoops_IGRPS];

				if (BIT (flags, _hoops_CHRRA))
					_hoops_HCHA[index] = _hoops_PGHIR->_hoops_IGHIR[_hoops_IGRPS];
			}
		}

		if (!_hoops_HHAHR) {
			if (++_hoops_HGRPS == polycylinder->_hoops_ISPIR)
				_hoops_HGRPS = 0;
		}
		else {
			if (_hoops_HGRPS-- == 0)
				_hoops_HGRPS = polycylinder->_hoops_ISPIR - 1;
		}

		_hoops_IGRPS += _hoops_CGRPS;
	}

	{	int							_hoops_AHGPS;
		_hoops_PACIR			_hoops_PHGPS;
		_hoops_CGRA alter &	_hoops_SGRA = nr->_hoops_SAIR;

		_hoops_PHGPS = _hoops_SGRA->_hoops_HHCAR;


		if (!BIT (sc->options, _hoops_CRPAS)) {
			_hoops_SGRA->_hoops_HHCAR = sc->bounding;
		}
		else if (0) {
			_hoops_SGRA->_hoops_HHCAR = sc->bounding;
			_hoops_SGRA->_hoops_HHCAR._hoops_IACHA(50.0f);
		}

		/* _hoops_GCAPH _hoops_RH _hoops_HSPH _hoops_HPHS _hoops_SIH _hoops_IH _hoops_GRR _hoops_GPHA _hoops_CCA _hoops_GPCAR
		 * _hoops_IS _hoops_RH _hoops_IASC _hoops_CISAR, _hoops_IAS._hoops_ISHI. _hoops_HHGPS[0] _hoops_PAH _hoops_SHH _hoops_PPSPR _hoops_IS _hoops_RH _hoops_RAAP,
		 * _hoops_PPR _hoops_IS _hoops_RH _hoops_SCIA _hoops_IIGR _hoops_RH _hoops_IASC _hoops_CISAR.
		 * _hoops_IHGPS _hoops_GAGPR _hoops_ARCSA _hoops_RPP _hoops_RH _hoops_CPHAR _hoops_HRGR _hoops_GPGS _hoops_RH _hoops_IASC
		 * _hoops_CISAR.
		 */
		_hoops_AHGPS = HD_Acquire_Clip_Points (nr, null, _hoops_HCRGR, points, _hoops_CGCAR, ws, _hoops_RRCAR);

		_hoops_SGRA->_hoops_HHCAR = _hoops_PHGPS;

		if (_hoops_AHGPS == 0)
			goto _hoops_PP;
	}

	status._hoops_CGCAR = _hoops_CGCAR;
	status.ws = ws;
	status._hoops_RRCAR = _hoops_RRCAR;

	if (BIT (nr->transform_rendition->flags, _hoops_IGSP) &&
		BIT (nr->transform_rendition->heuristics, _hoops_GPSA))
		nr.Modify()->transform_rendition.Modify()->heuristics ^=
						_hoops_GPSA|_hoops_SASA;


	tristrip.points = points;
	tristrip.point_count = _hoops_HCRGR;
	tristrip.face_count = _hoops_PGRPS + 2;

	tristrip.lengths = lengths;
	tristrip._hoops_AIHA = vi = _hoops_AIHA;
	tristrip.face_indices = fi = face_indices;

	offset1 = 0;
	offset2 = _hoops_HGII;

	for (_hoops_ICRHH=0; _hoops_ICRHH<polycylinder->point_count-1; _hoops_ICRHH++) {
		int				shift = _hoops_ICRHH * _hoops_HGII;

		/* _hoops_IIRGR _hoops_CSGPS _hoops_AARI */
		lengths[tristrip._hoops_PHHA++] = 2*_hoops_HGII+2;

		/* _hoops_HSPP "_hoops_ARPP" _hoops_RH _hoops_GSSR _hoops_ICPPR */
		*vi++ = shift + _hoops_HGII-1 + offset1;
		*vi++ = shift + _hoops_HGII-1 + offset2;
		*fi++ = shift + 0;
		*fi++ = shift + 0;
		for (ii=0; ii<_hoops_HGII; ii++) {
			*vi++ = shift + ii+offset1;
			*fi++ = shift + ii;
			*vi++ = shift + ii+offset2;
			*fi++ = shift + ii;
		}
	}

	if (!BIT (polycylinder->flags, _hoops_GASSA)) {
		if (polycylinder->flags & _hoops_IHHIA) {
			lengths[tristrip._hoops_PHHA++] = _hoops_HGII;
			for (ii=0; ii<_hoops_HGII; ii++) {
				if ((ii & 1) == 0)
					*vi++ = _hoops_HGII-1 - ii/2;
				else
					*vi++ = ii/2;
				*fi++ = _hoops_PGRPS;
			}
		}

		if (polycylinder->flags & _hoops_SHHIA) {
			int		shift = _hoops_PGRPS;

			lengths[tristrip._hoops_PHHA++] = _hoops_HGII;
			for (ii=0; ii<_hoops_HGII; ii++) {
				if ((ii & 1) == 0)
					*vi++ = ii/2 + shift;
				else
					*vi++ = _hoops_HGII-1 - ii/2 + shift;
				*fi++ = _hoops_PGRPS + 1;
			}
		}
	}

	if (ANYBIT (_hoops_CCGPS, T_FACES|T_EDGES)) {
		_hoops_ICSAS (nr, &tristrip, null, null, null, null, null);
	}
	else if (BIT (_hoops_CCGPS, T_INTERIOR_SILHOUETTE_EDGES)) {
		_hoops_HGCGA (dc, "silhouette selection", nr);
		dc->_hoops_IPCI->draw_3d_polyedge = _hoops_HCSAS;
		dc->_hoops_IPCI->draw_3d_tristrip = _hoops_AHSAS;
		/* _hoops_SIHPC: _hoops_ACGPS _hoops_AASA-_hoops_ISSC */
		/* _hoops_PCGPS _hoops_CHH _hoops_HCGPS _hoops_IPAS
		 * _hoops_PGAP _hoops_CHH _hoops_APRAR _hoops_RH _hoops_GHSHA _hoops_HPPP _hoops_HRII
		 * _hoops_HSAR _hoops_PGSA _hoops_RH _hoops_SPPR.
		 */
		HD_Std_3D_PolyCylinder (nr, polycylinder);
		_hoops_HGSGA (dc, "silhouette selection");
	}

	if (BIT (_hoops_CCGPS, _hoops_GPA) &&
		_hoops_PGHIR != null && _hoops_PGHIR->_hoops_IGHIR != null) {
		Polyedge *			_hoops_CHGPR = null;

		tristrip._hoops_HCHA = _hoops_HCHA;

		HD_Isoline_From_Tristrip (nr, &tristrip);
		HD_Process_Isolines (dc, polycylinder, polycylinder->bounding, &_hoops_CHGPR, 0.001f);

		if (_hoops_CHGPR != null) {
			Polyedge alter *		_hoops_ACP = _hoops_CHGPR;
			DC_Point *				_hoops_HIGPS = status._hoops_CGCAR;
			float *					_hoops_IIGPS = status.ws;
			_hoops_GRCAR *				_hoops_CIGPS = status._hoops_RRCAR;

			// _hoops_HHCI _hoops_HAPR _hoops_IS _hoops_SSS _hoops_AHPA _hoops_RPR
			do {
				if (_hoops_ACP->_hoops_PPGI._hoops_CPACP >= _hoops_GCSAS)
					_hoops_GCSAS = _hoops_ACP->_hoops_PPGI._hoops_CPACP + 1;
			} while ((_hoops_ACP = _hoops_ACP->next) != null);
			_hoops_ACP = _hoops_CHGPR;

			// _hoops_IRS _hoops_IGRH _hoops_SCIPA, _hoops_IPCGP _hoops_RSSA _hoops_CHR _hoops_HAR _hoops_RH _hoops_PSHR _hoops_GAR _hoops_RSRRA _hoops_RSSA, _hoops_HIS _hoops_SR _hoops_RRP
			// _hoops_IS _hoops_SIGPS _hoops_PPR _hoops_HIHP _hoops_CAPR _hoops_GAR _hoops_SR _hoops_PHHR _hoops_IH _hoops_GRR _hoops_IPCGP _hoops_PPR _hoops_PHIH _hoops_CGPR _hoops_CPHR
			nr.Modify()->_hoops_SAIR.Modify();
			_hoops_CGRA alter &	_hoops_SGRA = nr->_hoops_SAIR;

			if (!BIT (sc->options, _hoops_CRPAS)) {
				_hoops_SGRA->_hoops_HHCAR.left	 = sc->bounding.left;
				_hoops_SGRA->_hoops_HHCAR.right	 = sc->bounding.right;
				_hoops_SGRA->_hoops_HHCAR.bottom = sc->bounding.bottom;
				_hoops_SGRA->_hoops_HHCAR.top	 = sc->bounding.top;
			}

			do {
				int							_hoops_AHGPS;

				ALLOC_ARRAY_ALIGNED_CACHED (status._hoops_CGCAR, _hoops_ACP->point_count, DC_Point, 16);
				ALLOC_ARRAY_ALIGNED_CACHED (status.ws, _hoops_ACP->point_count, float, 16);
				ALLOC_ARRAY_CACHED (status._hoops_RRCAR, _hoops_ACP->point_count, _hoops_GRCAR);

				/* _hoops_GCAPH _hoops_RH _hoops_HSPH _hoops_HPHS _hoops_SIH _hoops_IH _hoops_GRR _hoops_GPHA _hoops_CCA _hoops_GPCAR
				 * _hoops_IS _hoops_RH _hoops_IASC _hoops_CISAR, _hoops_IAS._hoops_ISHI. _hoops_HHGPS[0] _hoops_PAH _hoops_SHH _hoops_PPSPR _hoops_IS _hoops_RH _hoops_RAAP,
				 * _hoops_PPR _hoops_IS _hoops_RH _hoops_SCIA _hoops_IIGR _hoops_RH _hoops_IASC _hoops_CISAR.
				 * _hoops_IHGPS _hoops_GAGPR _hoops_ARCSA _hoops_RPP _hoops_RH _hoops_CPHAR _hoops_HRGR _hoops_GPGS _hoops_RH _hoops_IASC
				 * _hoops_CISAR.
				 */
				_hoops_AHGPS = HD_Acquire_Clip_Points (nr,
													   polycylinder->bounding,
													   _hoops_ACP->point_count,
													   _hoops_ACP->points,
													   status._hoops_CGCAR,
													   status.ws,
													   status._hoops_RRCAR);

				if (_hoops_AHGPS != 0)
					_hoops_SISAS (nr, _hoops_ACP, _hoops_GCSAS);

				FREE_ARRAY_ALIGNED (status._hoops_CGCAR, _hoops_ACP->point_count, DC_Point, 16);
				FREE_ARRAY_ALIGNED (status.ws, _hoops_ACP->point_count, float, 16);
				FREE_ARRAY (status._hoops_RRCAR, _hoops_ACP->point_count, _hoops_GRCAR);

				if (status._hoops_SHPAS && status._hoops_PHPAS)
					break;
			} while ((_hoops_ACP = _hoops_ACP->next) != null);

			status._hoops_CGCAR = _hoops_HIGPS;
			status.ws = _hoops_IIGPS;
			status._hoops_RRCAR = _hoops_CIGPS;

			HI_Free_Polyedge_List (_hoops_CHGPR);
		}
	}


	if (status._hoops_AHPAS)
		HD_Elaborate_Selection (nr,
								(Geometry const *)polycylinder, polycylinder->key, _hoops_AIRIR(polycylinder),
								(int) (status._hoops_CCCCP.vertex1 - status._hoops_CGCAR) / _hoops_HGII,
								(int) (status._hoops_CCCCP.vertex2 - status._hoops_CGCAR) / _hoops_HGII,
								-1,
								status._hoops_SPPAS._hoops_RCSAP,
								status._hoops_SPPAS._hoops_HISAP,
								T_FACES, null);
	else if (status._hoops_PHPAS)
		HD_Elaborate_Selection (nr,
								(Geometry const *)polycylinder, polycylinder->key, _hoops_AIRIR(polycylinder),
								-1,
								status._hoops_GHPAS.face,	// _hoops_SGH _hoops_HSP _hoops_IS _hoops_ASH _hoops_IPCGP _hoops_RARP
								_hoops_GCSAS,
								status._hoops_GHPAS._hoops_RCSAP,
								status._hoops_GHPAS._hoops_HISAP,
								T_ANY_EDGE, null);
	else if (status._hoops_HHPAS)
		HD_Elaborate_Selection (nr,
								(Geometry const *)polycylinder, polycylinder->key, _hoops_AIRIR(polycylinder),
								(int) (status._hoops_CCCCP.vertex1 - status._hoops_CGCAR) / _hoops_HGII,
								(int) (status._hoops_CCCCP.vertex2 - status._hoops_CGCAR) / _hoops_HGII,
								-1,
								status._hoops_CCCCP._hoops_RCSAP,
								status._hoops_CCCCP._hoops_HISAP,
								T_ANY_EDGE, null);

	if (status._hoops_ACSAP) {
		/* _hoops_GII _hoops_SGCRP _hoops_PPCIA _hoops_PRHI _hoops_CHR _hoops_HAR _hoops_PGCPR _hoops_IH _hoops_RGR */
		while (status._hoops_ACSAP != null) {
			_hoops_AISAP *victim = status._hoops_ACSAP;
			status._hoops_ACSAP = victim->next;
			FREE (victim, _hoops_AISAP);
		}
	}


  _hoops_PP:


	if (_hoops_HCRGR > _hoops_GGAPR(_hoops_HRIGA)) {
		FREE_ARRAY_ALIGNED (points, _hoops_HCRGR, Point, 16);
		FREE_ARRAY_ALIGNED (_hoops_CGCAR, _hoops_HCRGR, DC_Point, 16);
		FREE_ARRAY_ALIGNED (ws, _hoops_HCRGR, float, 16);
		FREE_ARRAY (_hoops_RRCAR, _hoops_HCRGR, _hoops_GRCAR);
		FREE_ARRAY (_hoops_AIHA, 3*_hoops_HCRGR, int);
		FREE_ARRAY (face_indices, 3*_hoops_HCRGR, int);
		FREE_ARRAY (lengths, 2 * (polycylinder->point_count + _hoops_HGII), int);
		FREE_ARRAY (_hoops_HCHA, _hoops_HCRGR, float);
	}
#endif
#endif
}


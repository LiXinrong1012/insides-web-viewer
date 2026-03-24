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
 * $Id: obf_tmp.txt 1.121 2010-10-06 19:16:28 jason Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "database.h"			/* _hoops_IH _hoops_AIICP */
#include "phedron.h"
#include "phdraw.h"
#include "select.h"				/* _hoops_IH _hoops_PIICP */
#include "hd_proto.h"
#include "hi_proto.h"

#undef _hoops_CACIR
#define _hoops_CACIR 1e-5f


/*
 * _hoops_HSRR _hoops_IRS _hoops_RAGA _hoops_ACRI, _hoops_PGSA _hoops_AGAP _hoops_IGGA _hoops_SPPR _hoops_PGAP _hoops_CHR
 * _hoops_ARIP _hoops_IIGR _hoops_RH _hoops_ASSIA _hoops_HIICP, _hoops_GAR _hoops_AISP _hoops_HPP _hoops_RH _hoops_HSCHR
 * _hoops_IIGR _hoops_RH _hoops_HISS _hoops_RSSI.
 */

local void _hoops_IIICP (
	Net_Rendition const &		nr,
	Polyhedron alter	*		_hoops_IPRI,
	bool						_hoops_CIICP)
{
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ARPA const *				plane;
	_hoops_RPRA const *			_hoops_CRIPA;
	_hoops_CSSHA alter *	_hoops_HSAPA;
	_hoops_CSSHA			_hoops_AGRCA = _hoops_HARCA,
								_hoops_SIICP = _hoops_AARCA;
	/*_hoops_IHRCP _hoops_RCIC *			_hoops_CPHAR = _hoops_HSAGA->_hoops_CPHAR;*/
	int							count = _hoops_IPRI->face_count;
	bool						_hoops_GHHHR = false;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;

	/*
	 * _hoops_GISA-_hoops_ARCPR-_hoops_GCICP _hoops_HRGR _hoops_SHHA _hoops_IS _hoops_SHH _hoops_APRAR,
	 * _hoops_HAGC _hoops_ASHS _hoops_CCCI
	 */
	if (dc->_hoops_RCICP < _hoops_IPRI->face_count){
		if(dc->_hoops_ACICP)
			FREE_ARRAY (dc->_hoops_ACICP, dc->_hoops_RCICP, _hoops_CSSHA);
		POOL_ALLOC_ARRAY_CACHED (_hoops_HSAPA, _hoops_IPRI->face_count, _hoops_CSSHA, dc->memory_pool);
		dc->_hoops_ACICP = _hoops_HSAPA;
		dc->_hoops_RCICP = _hoops_IPRI->face_count;
	}

	_hoops_HSAPA = dc->_hoops_ACICP;

	if (!ALLBITS (_hoops_IPRI->polyhedron_flags,
				  PHF_FACE_NORMALS_VALID|_hoops_ASAHR))
		HI_Assemble_Face_Normals ((Polyhedron alter *)_hoops_IPRI);

	if (_hoops_CIICP && BIT (_hoops_IHCR->flags, _hoops_IGSP)) {
		/* _hoops_PCICP-_hoops_HCICP _hoops_HHAA _hoops_RH _hoops_ICICP _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_HPPHR-_hoops_IAPRR */
		if (BIT (_hoops_IHCR->heuristics, _hoops_GPSA))
			_hoops_AGRCA = _hoops_CCICP;
		else if (BIT (_hoops_IHCR->heuristics, _hoops_SASA))
			_hoops_SIICP = _hoops_CCICP;
	}

	/*
	 * _hoops_HSRR _hoops_GRR _hoops_HSP, _hoops_HIHP _hoops_IPPA _hoops_IS _hoops_RCRP _hoops_IRS _hoops_SHPR-_hoops_GC _hoops_IPPA '_hoops_GSGGR' _hoops_PPR _hoops_RPGP
	 */

	plane = _hoops_IPRI->local_face_attributes.normals;

	if (!BIT (_hoops_IHCR->flags, _hoops_HCPHP))
		HD_Validate_Object_To_Proj (nr);
	_hoops_CRIPA = _hoops_IHCR->object_to_projection_matrix->_hoops_PPRA()->data.elements;

	if (BIT (HOOPS_WORLD->_hoops_CIIPA, _hoops_SIIPA) && /* _hoops_SCICP _hoops_PAR _hoops_PHPA */
		!BIT (HOOPS_WORLD->_hoops_HGGHR, _hoops_IICPP)) {
		Local_Face_Attributes *_hoops_CPRI = &_hoops_IPRI->local_face_attributes;
		float *_hoops_GSICP, *_hoops_PPHPA, *end;

		ASSERT (!BIT(dc->flags, _hoops_GIHCP));
		ASSERT (ALLBITS (_hoops_IPRI->polyhedron_flags, PHF_FACE_NORMALS_VALID|_hoops_ASAHR));

		ALLOC_ARRAY_ALIGNED_CACHED (_hoops_GSICP, _hoops_IPRI->face_count, float, 16);
		HD_Compute_Screen_Plane_Dot_Products (nr, _hoops_IPRI->face_count, _hoops_CPRI->normals, true, _hoops_GSICP);

		_hoops_PPHPA = _hoops_GSICP;
		end = _hoops_PPHPA + _hoops_IPRI->face_count;
		if (_hoops_IPRI->type != _hoops_SCIP ||
			_hoops_CPRI->_hoops_IHAHR != 0 ||
			_hoops_CPRI->explicit_normal_count != 0) {
			while (_hoops_PPHPA < end) {
				if (plane->a == 0.0f && plane->b == 0.0f && plane->c == 0.0f) {
					*_hoops_HSAPA = _hoops_PARCA;
					_hoops_GHHHR = true;
				}
				else {
					if (*_hoops_PPHPA < -1.0e-3f)
						*_hoops_HSAPA = _hoops_SIICP;
					else if (*_hoops_PPHPA > 1.0e-3f)
						*_hoops_HSAPA = _hoops_AGRCA;
					else
						*_hoops_HSAPA = _hoops_PARCA;
				}
				++_hoops_HSAPA;
				++_hoops_PPHPA;
				++plane;
			}
		}
		else {
			//_hoops_GAR _hoops_ARRS, _hoops_HIH _hoops_SIHH _hoops_RH _hoops_ISPR _hoops_IH 0'_hoops_GRI _hoops_GGR _hoops_RH _hoops_HSP _hoops_IPPA
			while (_hoops_PPHPA < end) {
#ifdef _DEBUG
				//_hoops_RPP _hoops_SR _hoops_RHHR _hoops_RGR _hoops_ACSRA, _hoops_SGS _hoops_AGSR _hoops_SGS _hoops_RH _hoops_ARHAR _hoops_GSSR _hoops_RPR _hoops_CGH _hoops_HS _hoops_RPII >0
				ASSERT (plane->a != 0.0f || plane->b != 0.0f || plane->c != 0.0f);
				++plane;
#endif
				if (*_hoops_PPHPA < -1.0e-3f)
					*_hoops_HSAPA = _hoops_SIICP;
				else if (*_hoops_PPHPA > 1.0e-3f)
					*_hoops_HSAPA = _hoops_AGRCA;
				else
					*_hoops_HSAPA = _hoops_PARCA;
				++_hoops_HSAPA;
				++_hoops_PPHPA;
			}
		}

		FREE_ARRAY_ALIGNED (_hoops_GSICP, _hoops_IPRI->face_count, float, 16);
	}
	else {
		while (count-- > 0) {
			if (plane->a == 0.0f && plane->b == 0.0f && plane->c == 0.0f) {
				*_hoops_HSAPA++ = _hoops_PARCA;
				_hoops_GHHHR = true;
			}
			else 
			{
				/* _hoops_HIHP _hoops_PPR _hoops_RPGP _hoops_RH _hoops_IPPA '_hoops_GSGGR' */
				float		xc = _hoops_CRIPA[2][0] * plane->a + _hoops_CRIPA[2][1] * plane->b +
								 _hoops_CRIPA[2][2] * plane->c + _hoops_CRIPA[2][3] * plane->d;

				if (xc < -1.0e-3f)
					*_hoops_HSAPA++ = _hoops_SIICP;
				else if (xc > 1.0e-3f)
					*_hoops_HSAPA++ = _hoops_AGRCA;
				else
					*_hoops_HSAPA++ = _hoops_PARCA;
			}
			++plane;
		}
	}

	if (_hoops_GHHHR) {
		bool			_hoops_CCCIR = false;

		_hoops_HSAPA = dc->_hoops_ACICP;
		do {
			_hoops_CCCIR = _hoops_GHHHR = false;

			if (_hoops_IPRI->type == _hoops_SCIP) {
				_hoops_CGCPR const		*_hoops_SGCPR = ((Shell *)_hoops_IPRI)->_hoops_SGCPR;
				int							_hoops_SPHA = _hoops_IPRI->_hoops_SPHA;

				do {
					if (_hoops_HSAPA[_hoops_SGCPR->_hoops_AIIPR] == _hoops_PARCA) {
						/* _hoops_SGH _hoops_ASRPA _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_APIP */
						if (_hoops_SGCPR->_hoops_HIIPR >= 0 && _hoops_HSAPA[_hoops_SGCPR->_hoops_HIIPR] != _hoops_PARCA) {
							_hoops_HSAPA[_hoops_SGCPR->_hoops_AIIPR] = _hoops_HSAPA[_hoops_SGCPR->_hoops_HIIPR];
							_hoops_CCCIR = true;
						}
						else
							_hoops_GHHHR = true;		/* _hoops_HGGC _hoops_RRP _hoops_IS _hoops_HPPR _hoops_RGR _hoops_SPR _hoops_RPP _hoops_SR _hoops_PAH */
					}
					else if (_hoops_SGCPR->_hoops_HIIPR >= 0 && _hoops_HSAPA[_hoops_SGCPR->_hoops_HIIPR] == _hoops_PARCA) {
						/* _hoops_SR _hoops_ACPA _hoops_PSRPA _hoops_HRGR _hoops_RIRA */
						_hoops_HSAPA[_hoops_SGCPR->_hoops_HIIPR] = _hoops_HSAPA[_hoops_SGCPR->_hoops_AIIPR];
						_hoops_CCCIR = true;
					}

					++_hoops_SGCPR;
				} _hoops_RGGA (--_hoops_SPHA <= 0);
			}
			else {
			}
		} while (_hoops_GHHHR && _hoops_CCCIR);
	}
}


#define _hoops_RSICP(phon)   HI_Assemble_3D_Tristrips (phon, 0, true)

local void HD_Acquire_World_Vertex_Planes (
	Net_Rendition const &		nr,
	Polyhedron alter *			phon,
	_hoops_ARPA alter *				_hoops_PGPCP) {

		if (phon == null)
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
			"HD_Acquire_World_Vertex_Planes called without a valid polyhedron.");

		if (!BIT(phon->polyhedron_flags,PHF_VERTEX_NORMALS_VALID))
			_hoops_RSICP ((Polyhedron alter *)phon);

		HD_Compute_World_Vertex_Planes (nr,
			phon->point_count,
			phon->points,
			phon->local_vertex_attributes.normals,
			_hoops_PGPCP);
}



local void _hoops_ASICP (
	Net_Rendition const &		nr,
	Polyhedron alter	*		_hoops_IPRI,
	float alter *				_hoops_PSICP,
	float						bias) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	int							count = _hoops_IPRI->point_count;
	_hoops_ARPA  *					planes;
	_hoops_ARPA  *					_hoops_PGPCP;
	_hoops_RPRA const *			_hoops_CRIPA;

	POOL_ALLOC_ARRAY_ALIGNED_CACHED(planes, _hoops_IPRI->point_count, _hoops_ARPA, 16, nr->_hoops_SRA->memory_pool);
	_hoops_PGPCP = planes;
	HD_Acquire_World_Vertex_Planes (nr, _hoops_IPRI, _hoops_PGPCP);

	if (_hoops_IHCR->_hoops_SPH->_hoops_PRPA._hoops_APRA == null)
		HI_Validate_Matrix_Adjoint (&_hoops_IHCR->_hoops_SPH->_hoops_PRPA);

	_hoops_CRIPA = _hoops_IHCR->_hoops_SPH->_hoops_PRPA._hoops_APRA->data.elements;

	while (count-- > 0) {
		/* _hoops_RH _hoops_CCPCR _hoops_SIPIR _hoops_HPGR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RGR _hoops_RHPHR _hoops_HRGR _hoops_RSARA _hoops_IS _hoops_CHAA _hoops_RH
			_hoops_HSICP _hoops_RRHC _hoops_RH _hoops_SARA _hoops_RPPR.  _hoops_HHIGR _hoops_HRGR _hoops_APGP _hoops_ISICP _hoops_SGS _hoops_RIIA _hoops_IIGR
			_hoops_CSICP _hoops_RH _hoops_ASSIA _hoops_HPGR _hoops_RH _hoops_PPSR _hoops_GPP _hoops_RH _hoops_ISSGR 90 _hoops_SSICP _hoops_HII _hoops_RH _hoops_SARA _hoops_AAGA,
			_hoops_SR _hoops_HHGC _hoops_SCH _hoops_IS _hoops_SHH _hoops_HPGR 87 _hoops_SSICP. */
		*_hoops_PSICP++ = _hoops_CRIPA[2][0] * _hoops_PGPCP->a +
				 _hoops_CRIPA[2][1] * _hoops_PGPCP->b +
				 _hoops_CRIPA[2][2] * _hoops_PGPCP->c +
				 _hoops_CRIPA[2][3] * _hoops_PGPCP->d +
				 bias;
		++_hoops_PGPCP;
	}
	FREE_ARRAY_ALIGNED(planes, _hoops_IPRI->point_count, _hoops_ARPA, 16);
}

local void _hoops_GGCCP (
	Polyhedron alter	*			phon)
{
	_hoops_ARPA const *_hoops_RIIIA = phon->local_face_attributes.normals;
	_hoops_GHHPR *_hoops_RGCCP = null;
	float _hoops_SSRP;
	int	i;
	int _hoops_AIIPR, _hoops_HIIPR;
	_hoops_CGCPR const *_hoops_SGCPR;

	ASSERT (phon->_hoops_SPHA >= 0); //_hoops_CGH _hoops_HS _hoops_RPII _hoops_IAIAR _hoops_HPP _hoops_HA
	ASSERT (phon->type == _hoops_SCIP);  //_hoops_PAH'_hoops_RA _hoops_AA _hoops_CSHRR _hoops_GAPR _hoops_PGGA _hoops_AGCCP _hoops_HRGR _hoops_PCHCP _hoops_GPP _hoops_SCIA _hoops_IIGR _hoops_PGSPR

	if (phon->_hoops_IHHPR.flags == null)
		HI_Initialize_Edge_Attributes (phon, 0);
	_hoops_RGCCP = phon->_hoops_IHHPR.flags;

	phon->polyhedron_flags |= _hoops_PGCCP;

	if (phon->_hoops_SPHA == 0)
		return;

	_hoops_SGCPR = ((Shell *)phon)->_hoops_SGCPR;
	for (i = 0 ; i < phon->_hoops_SPHA ; i++) {
		_hoops_AIIPR = _hoops_SGCPR[i]._hoops_AIIPR;
		_hoops_HIIPR = _hoops_SGCPR[i]._hoops_HIIPR;
		if (_hoops_HIIPR < 0)
			continue;
		_hoops_SSRP = _hoops_RIIIA[_hoops_AIIPR].a * _hoops_RIIIA[_hoops_HIIPR].a +
			  _hoops_RIIIA[_hoops_AIIPR].b * _hoops_RIIIA[_hoops_HIIPR].b +
			  _hoops_RIIIA[_hoops_AIIPR].c * _hoops_RIIIA[_hoops_HIIPR].c;
		if (_hoops_SSRP > 1.0f - _hoops_CACIR)
			_hoops_RGCCP[i] |= _hoops_HGCCP;
	}
}


/* _hoops_IRS "_hoops_HHHR _hoops_GCSGR _hoops_IGCCP" _hoops_HRGR _hoops_CGCCP _hoops_IRS _hoops_SGCCP _hoops_IIGR _hoops_IRS _hoops_HSIAR _hoops_ISSGR _hoops_GRCCP
 * _hoops_RH _hoops_GPSGR _hoops_PPR _hoops_ISPP _hoops_IGCCP (_hoops_PGAP _hoops_IH _hoops_RRCCP-_hoops_GCRCP _hoops_AARAR _hoops_GRS _hoops_SHR _hoops_SHH _hoops_GGR _hoops_CSIGA
 * _hoops_SSGAR) _hoops_CHR _hoops_IIGR _hoops_HAGH _hoops_RAGIR.  _hoops_GPGP _hoops_RII _hoops_ARCCP, _hoops_SR _hoops_HS _hoops_IRS "_hoops_PRCCP".  _hoops_AGAH _hoops_SCHS _hoops_CHR _hoops_IIGR _hoops_IPGAA
 * _hoops_HAR _hoops_RRCCP-_hoops_GCRCP, _hoops_HIH _hoops_SR _hoops_IHSH _hoops_HPGR _hoops_RH _hoops_HRCCP _hoops_AARI _hoops_IRS _hoops_GPHA _hoops_IS _hoops_CACH _hoops_RPP _hoops_HHH _hoops_APIHR _hoops_CHR _hoops_ARRS
 * _hoops_PPR _hoops_HHH _hoops_APIHR _hoops_CHR _hoops_CAPP.  _hoops_CGP _hoops_SSIA _hoops_CHR, _hoops_SR _hoops_IRCCP _hoops_RH _hoops_GPHA _hoops_CCA _hoops_IRS _hoops_CRCCP _hoops_RIP */
local void _hoops_SRCCP (
	Net_Rendition const &			nr,
	Polyhedron alter	*			phon) {
	/*_hoops_IHRCP _hoops_RAPC *				_hoops_IPGC = (_hoops_IHRCP _hoops_RAPC *)_hoops_HSAGA->_hoops_CPHAR;*/
	Local_Vertex_Attributes alter *	_hoops_SPRI = &phon->local_vertex_attributes;
	_hoops_SGCC const &		_hoops_HSGA = nr->transform_rendition->_hoops_IPH;
	int								count = phon->point_count;
	int								i, j, _hoops_GACCP, _hoops_RACCP, _hoops_CSGHA;
	_hoops_RHHPR				*ptr, *start, *end;
	_hoops_RHHPR *			_hoops_AACCP;	/* '_hoops_SPPR' _hoops_HPIPR */
	_hoops_RHHPR **			_hoops_PACCP; /* '_hoops_RPGPA' _hoops_HPIPR */
	Point *							_hoops_HACCP;
	_hoops_ARPA *							_hoops_PGPCP;
	float							_hoops_SSRP;

	/* _hoops_SR _hoops_HHS _hoops_HS _hoops_IACCP _hoops_GGR _hoops_CARA _hoops_GC, _hoops_HIH _hoops_SR _hoops_GRS _hoops_RRP _hoops_RH _hoops_GSSP _hoops_GPHA _hoops_GHC
	 * _hoops_SPHR _hoops_IH _hoops_RII _hoops_CGSI _hoops_PHGCA. */
	POOL_ALLOC_ARRAY_ALIGNED_CACHED(_hoops_PGPCP, phon->point_count, _hoops_ARPA, 16, nr->_hoops_SRA->memory_pool);
	HD_Acquire_World_Vertex_Planes (nr, phon, _hoops_PGPCP);
	POOL_ALLOC_ARRAY_ALIGNED_CACHED (_hoops_HACCP, count, Point, 16, nr->_hoops_SRA->memory_pool);
	HI_Compute_Transformed_Points (count, phon->points, &_hoops_HSGA->data.elements[0][0], _hoops_HACCP);

	/* _hoops_RH _hoops_ASGH _hoops_RPGPA[_hoops_HAS] _hoops_GASR _hoops_RGAR _hoops_AAAA _hoops_RHAC _hoops_CHSHR _hoops_IS _hoops_GIHA > _hoops_HAS, _hoops_HIH _hoops_SR
	 * _hoops_RRP _hoops_RH _hoops_GIHA < _hoops_HAS _hoops_GAR _hoops_PRAR.  _hoops_PHGP _hoops_SR _hoops_GRAS _hoops_IRS _hoops_PIIA _hoops_HIIA */
	POOL_ALLOC_ARRAY_CACHED (_hoops_AACCP, phon->_hoops_SPHA, _hoops_RHHPR, nr->_hoops_SRA->memory_pool);
	POOL_ALLOC_ARRAY_CACHED (_hoops_PACCP, phon->point_count+1, _hoops_RHHPR *, nr->_hoops_SRA->memory_pool);
	HI_Reverse_Shell_Edges (nr->_hoops_SRA->memory_pool, (Shell const *)phon, _hoops_AACCP, _hoops_PACCP);

	_hoops_SPRI->_hoops_CACCP = 0;
	for (i = 0; i < count; i++) {
		_hoops_GACCP = _hoops_RACCP = 0;
		for (j = 0; j < 2; j++) {
			if (j == 0) {
				start = ((Shell *)phon)->_hoops_HHHPR[i];
				end = ((Shell *)phon)->_hoops_HHHPR[i+1];
			}
			else {
				start = _hoops_PACCP[i];
				end = _hoops_PACCP[i+1];
			}
			for (ptr = start; ptr < end; ptr++) {
				_hoops_CSGHA = ptr->_hoops_GIHPR;
				_hoops_SSRP = _hoops_PGPCP[i].a*_hoops_HACCP[_hoops_CSGHA].x +
					  _hoops_PGPCP[i].b*_hoops_HACCP[_hoops_CSGHA].y +
					  _hoops_PGPCP[i].c*_hoops_HACCP[_hoops_CSGHA].z +
					  _hoops_PGPCP[i].d;
				if (_hoops_SSRP > _hoops_CACIR)
					_hoops_GACCP++;
				else if (_hoops_SSRP < -_hoops_CACIR)
					_hoops_RACCP++;
			}
		}
		if (_hoops_GACCP >= 2 && _hoops_RACCP >= 2) {
			if(!BIT(phon->polyhedron_flags, _hoops_CGRHR)){
				int i = 0;
				ZALLOC_ARRAY(_hoops_SPRI->flags, phon->point_count, Local_Vertex_Flags);
				for(i = 0; i < phon->point_count; i++)
					_hoops_SPRI->flags[i] = _hoops_SPRI->_hoops_SGRHR;
				phon->polyhedron_flags |= _hoops_CGRHR;
			}
			*_hoops_SPRI->_hoops_CHHPR(i) |= _hoops_SACCP;
			_hoops_SPRI->_hoops_CACCP++;
		}
		else
			*_hoops_SPRI->_hoops_CHHPR(i) &= ~_hoops_SACCP;
	}
	/* _hoops_CGH _hoops_SR _hoops_GPCCP _hoops_RH _hoops_CRCCP _hoops_IS _hoops_GIHA' _hoops_HGAI _hoops_APIHR? */
#if 0
	for (i = 0; i < count; i++) {
		if (!BIT (_hoops_SPRI->flags[i], _hoops_SACCP) ||
			BIT (_hoops_SPRI->flags[i], _hoops_RPCCP))
			continue;
		for (j = 0; j < 2; j++) {
			if (j == 0) {
				start = phon->_hoops_SPHPR._hoops_HHHPR[i];
				end = phon->_hoops_SPHPR._hoops_HHHPR[i+1];
			}
			else {
				start = _hoops_PACCP[i];
				end = _hoops_PACCP[i+1];
			}
			for (ptr = start; ptr < end; ptr++) {
				_hoops_CSGHA = ptr->_hoops_GIHPR;
				if (!BIT (_hoops_SPRI->flags[_hoops_CSGHA], _hoops_SACCP)) {
					_hoops_SPRI->flags[_hoops_CSGHA] |= (_hoops_SACCP|_hoops_RPCCP);
					_hoops_SPRI->_hoops_CACCP++;
				}
			}
		}
	}
	for (i = 0; i < count; i++)
		_hoops_SPRI->flags[i] &= ~_hoops_RPCCP;
#endif

	FREE_ARRAY (_hoops_AACCP, phon->_hoops_SPHA, _hoops_RHHPR);
	FREE_ARRAY (_hoops_PACCP, phon->point_count+1, _hoops_RHHPR *);
	FREE_ARRAY_ALIGNED (_hoops_PGPCP, phon->point_count, _hoops_ARPA, 16);
	FREE_ARRAY_ALIGNED (_hoops_HACCP, count, Point, 16);
	phon->polyhedron_flags |= _hoops_APCCP;
}


local void _hoops_PPCCP (
	float			_hoops_RSS,
	float			_hoops_ASS,
	Point const *	_hoops_ISPI,
	Point const *	_hoops_CSPI,
	Point alter *	_hoops_PAGR) {
	float			t, _hoops_SSHGA;

	_hoops_SSHGA = _hoops_RSS - _hoops_ASS;
	if (_hoops_SSHGA > _hoops_CACIR || _hoops_SSHGA < -_hoops_CACIR)
		t = _hoops_RSS / _hoops_SSHGA;
	else
		t = 0; /* _hoops_RSSA _hoops_CHR _hoops_GPP _hoops_APGP _hoops_SCIA _hoops_IIGR _hoops_GRR _hoops_RII, _hoops_HIS _hoops_SCH _hoops_ASSP'_hoops_RA _hoops_RPSHR _hoops_PGAP _hoops_SR _hoops_IRAA */
	_hoops_PAGR->x = (1-t)*_hoops_ISPI->x + t*_hoops_CSPI->x;
	_hoops_PAGR->y = (1-t)*_hoops_ISPI->y + t*_hoops_CSPI->y;
	_hoops_PAGR->z = (1-t)*_hoops_ISPI->z + t*_hoops_CSPI->z;
}


/* _hoops_CAHP _hoops_RH _hoops_IPCGP _hoops_IH _hoops_GPHA _hoops_PSCHR _hoops_HPAHR == 0 _hoops_IH _hoops_IRS _hoops_RSRA _hoops_SCPH */
local bool _hoops_HPCCP (
	float 				_hoops_RSS,
	float 				_hoops_ASS,
	float 				_hoops_IPCCP,
	Point const *		_hoops_ISPI,
	Point const *		_hoops_CSPI,
	Point const *		_hoops_SSPI,
	Polyline alter **	_hoops_PAGR) {
	Polyline alter *	polyline = *_hoops_PAGR;
	Point alter *		pl;

	/* _hoops_IRHH _hoops_RCRR _hoops_SR _hoops_HS _hoops_IRS _hoops_ISII _hoops_PPR _hoops_SGS _hoops_SCH _hoops_HRGR _hoops_ICIC _hoops_IS _hoops_CIPAA */
	if (polyline == null || polyline->_hoops_HIHI != 1) {
		if (polyline != null)
			_hoops_HPRH (polyline);
		ZALLOC (polyline, Polyline);
		polyline->_hoops_HIHI = 1;
		polyline->type = _hoops_IIIP;
		polyline->_hoops_CPGPR = _hoops_PHSSR;
		ALLOC_ARRAY (pl, 2, Point);
		polyline->points = pl;
		polyline->allocated = polyline->count = 2;
		*_hoops_PAGR = polyline;
	}
	else
		pl = polyline->points;

	/* _hoops_SSRR _hoops_ARAR:
		_hoops_IRS) _hoops_IPCGP _hoops_ICHIA _hoops_CPCCP,_hoops_HGGR _hoops_PPR _hoops_HGGR,_hoops_SPCCP
		_hoops_RCSR) _hoops_IPCGP _hoops_ICHIA _hoops_CPCCP,_hoops_HGGR _hoops_PPR _hoops_SPCCP,_hoops_CPCCP
		_hoops_GSGGR) _hoops_IPCGP _hoops_ICHIA _hoops_HGGR,_hoops_SPCCP _hoops_PPR _hoops_SPCCP,_hoops_CPCCP
		_hoops_GHGP) _hoops_IPCGP _hoops_GHCCP _hoops_RGR _hoops_SCPH _hoops_CCGC */
	if (_hoops_RSS * _hoops_ASS < 0) {
		/* _hoops_AGIR _hoops_IRS _hoops_PAR _hoops_RCSR */
		_hoops_PPCCP (_hoops_RSS, _hoops_ASS, _hoops_ISPI, _hoops_CSPI, pl);
		pl++;
		if (_hoops_ASS * _hoops_IPCCP < 0)
			/* _hoops_AGIR _hoops_IRS */
			_hoops_PPCCP (_hoops_ASS, _hoops_IPCCP, _hoops_CSPI, _hoops_SSPI, pl);
		else
			/* _hoops_AGIR _hoops_RCSR */
			_hoops_PPCCP (_hoops_IPCCP, _hoops_RSS, _hoops_SSPI, _hoops_ISPI, pl);
		return true;
	}
	else if (_hoops_ASS * _hoops_IPCCP < 0) {
		/* _hoops_AGIR _hoops_GSGGR */
		_hoops_PPCCP (_hoops_ASS, _hoops_IPCCP, _hoops_CSPI, _hoops_SSPI, pl);
		pl++;
		_hoops_PPCCP (_hoops_IPCCP, _hoops_RSS, _hoops_SSPI, _hoops_ISPI, pl);
		return true;
	}
	else
		/* _hoops_AGIR _hoops_GHGP (_hoops_SSSHR _hoops_IS _hoops_SHH _hoops_RH _hoops_PPCAR _hoops_AGIR */
		return false; /* _hoops_CPS _hoops_HRGR _hoops_GPP _hoops_RH _hoops_PSHR _hoops_PPAP _hoops_IIGR 0 */
}



/* _hoops_RRCPR->_hoops_SPPR[_hoops_HAS] _hoops_ICGI _hoops_PASPR _hoops_IIGR _hoops_SPPR>_hoops_HAS.  _hoops_HGI _hoops_HICRR _hoops_RSSAR
 * _hoops_IRS _hoops_PIIA _hoops_HIIA. _hoops_RHCCP _hoops_HRGR _hoops_HGSAR _hoops_IH _hoops_GHCS */
GLOBAL_FUNCTION void HI_Reverse_Shell_Edges (
	Memory_Pool *				memory_pool,
	Shell const *				_hoops_SPHPR,
	_hoops_RHHPR alter *	_hoops_AACCP,				/* '_hoops_SPPR' _hoops_HPIPR */
	_hoops_RHHPR alter **	_hoops_PACCP) {	/* '_hoops_RPGPA' _hoops_HPIPR */
	int							i;
	int *						_hoops_AHCCP;
	_hoops_RHHPR *		ptr;

	POOL_ZALLOC_ARRAY_CACHED (_hoops_AHCCP, _hoops_SPHPR->point_count, int, memory_pool);
	ptr = _hoops_SPHPR->_hoops_HHHPR[0];
	for (i = 0; i < _hoops_SPHPR->point_count; i++) {
		while (ptr < _hoops_SPHPR->_hoops_HHHPR[i+1]) {
			_hoops_AHCCP[ptr->_hoops_GIHPR]++;
			ptr++;
		}
	}
	_hoops_PACCP[0] = _hoops_AACCP;
	for (i = 0; i < _hoops_SPHPR->point_count; i++)
		_hoops_PACCP[i+1] = _hoops_PACCP[i] + _hoops_AHCCP[i];

	ptr = _hoops_SPHPR->_hoops_HHHPR[0];
	for (i = 0; i < _hoops_SPHPR->point_count; i++) {
		while (ptr < _hoops_SPHPR->_hoops_HHHPR[i+1]) {
			_hoops_PACCP[ptr->_hoops_GIHPR]->_hoops_GIHPR = i;
			_hoops_PACCP[ptr->_hoops_GIHPR]++;
			ptr++;
		}
	}
	_hoops_PACCP[0] = _hoops_AACCP;
	for (i = 0; i < _hoops_SPHPR->point_count; i++)
		_hoops_PACCP[i+1] = _hoops_PACCP[i] + _hoops_AHCCP[i];

	FREE_ARRAY (_hoops_AHCCP, _hoops_SPHPR->point_count, int);
}

#define _hoops_PHCCP 64

#define _hoops_HHCCP(_hoops_IHCCP) \
	POOL_ZALLOC(polyedge, Polyedge, _hoops_IHCCP); \
	_hoops_ICAI(polyedge); \
	\
	polyedge->lengths_allocated=1; \
	polyedge->_hoops_IPII = _hoops_PHCCP; \
	polyedge->_hoops_CPII = _hoops_PHCCP; \
	POOL_ALLOC_ARRAY (polyedge->lengths, polyedge->lengths_allocated, int, _hoops_IHCCP); \
	POOL_ALLOC_ARRAY (polyedge->_hoops_AIHA, polyedge->_hoops_IPII, int, _hoops_IHCCP); \
	POOL_ALLOC_ARRAY (polyedge->_hoops_SPII, polyedge->_hoops_CPII, int, _hoops_IHCCP); \
	polyedge->_hoops_RAHH |= _hoops_AAHH; \
	\
	vlist = polyedge->_hoops_AIHA; \
	_hoops_CHCCP = polyedge->_hoops_SPII; \
	_hoops_SHCCP = vlist+polyedge->_hoops_IPII; \
	pp = points; \
	\
	polyedge->point_count = 2; \
	polyedge->_hoops_PHHA = 1; \
	\
	polyedge->points = points; \
	polyedge->point_count = _hoops_PHCCP; \
	\
	polyedge->_hoops_SPHA = _hoops_RASGR->_hoops_SPHA; \
	polyedge->_hoops_ASHA = _hoops_RASGR->_hoops_ASHA; \
	polyedge->_hoops_RSHA = _hoops_RASGR->_hoops_RSHA; \
	polyedge->_hoops_PCHA = _hoops_RASGR->_hoops_PCHA; \
	polyedge->_hoops_HCHA = _hoops_RASGR->_hoops_HCHA; \
	polyedge->_hoops_ICHA = _hoops_RASGR->_hoops_ICHA; \
	polyedge->_hoops_CCHA = _hoops_RASGR->_hoops_CCHA; \
	polyedge->_hoops_GSHA = _hoops_RASGR->_hoops_GSHA; \
	polyedge->_hoops_SRHA = _hoops_SRHH|DL_TEMPORARY_DATA|DL_DO_NOT_DEFER;



#define _hoops_GICCP(_hoops_RICCP) do {							\
			*pp = _hoops_IPRI->points[_hoops_RICCP];								\
			if (sc != null && sc->_hoops_AICCP != null) {							\
				int			_hoops_PICCP = pp - points;							\
				_hoops_HICCP->_hoops_CGCAR[_hoops_PICCP] = _hoops_IICCP[_hoops_RICCP];	\
				_hoops_HICCP->ws[_hoops_PICCP] = _hoops_CICCP[_hoops_RICCP];					\
				_hoops_HICCP->_hoops_RRCAR[_hoops_PICCP] = _hoops_SICCP[_hoops_RICCP];	\
				mapping[_hoops_PICCP] = _hoops_RICCP;								\
			}																	\
		} while (0)


GLOBAL_FUNCTION void HD_Draw_Silhouette_Edges (
	Net_Rendition const &		nr,
	Polyedge const *			_hoops_RASGR) {
	Display_Context const *		dc = (Display_Context const *)nr->_hoops_SRA;
	int							vertex1;
	int							vertex2;
	int							_hoops_AIIPR;
	int							_hoops_HIIPR;
	int							_hoops_SHPC;
	int							_hoops_PHHA = _hoops_RASGR->_hoops_PHHA;
	int const *					lengths = _hoops_RASGR->lengths;
	int const *					vi = _hoops_RASGR->_hoops_AIHA;
	int const *					ei = _hoops_RASGR->_hoops_SPII;
	Polyhedron const *			_hoops_IPRI = (Polyhedron*)_hoops_RASGR->_hoops_GSCP;
	int *						vlist = null;
	int *						_hoops_CHCCP = null;
	int alter *					_hoops_SHCCP = null;
	int alter *					_hoops_ACI;
	int alter *					_hoops_AARCP;
	_hoops_GIIPR const *	_hoops_GCCCP;
	Polyedge *					polyedge = null;
	int							length;
	int							_hoops_RCCCP = 0;
	Point						points[_hoops_PHCCP];
	Point alter *				pp = points;
	_hoops_ACCCP *			sc = nr->_hoops_SRA->_hoops_APHHP;
	_hoops_PCCCP *			_hoops_HICCP = null;
	DC_Point const *			_hoops_IICCP = null;
	float const *				_hoops_CICCP = null;
	_hoops_GRCAR const *			_hoops_SICCP = null;
	DC_Point const *			_hoops_HCCCP = null;
	DC_Point const *			_hoops_ICCCP = null;
	int alter *					mapping = null;

	/*
	 * _hoops_HSRR _hoops_GRR _hoops_ISHA _hoops_GIAA _hoops_RGR _hoops_CIIA _hoops_ACRI, _hoops_IPS _hoops_SCH _hoops_IS _hoops_PCCP _hoops_IIPR _hoops_HIGR
	 * _hoops_RPP _hoops_PPR _hoops_RGAR _hoops_RPP _hoops_SCH _hoops_SSCP _hoops_PGCR _hoops_HISS _hoops_RSSI, _hoops_GIPR _hoops_CHR "_hoops_HAR _hoops_PSIPR",
	 * _hoops_PPR _hoops_PGI _hoops_SPR _hoops_HSP _hoops_RSSI _hoops_CPCHR _hoops_PPR _hoops_SPR _hoops_HPIPR _hoops_PAR _hoops_SPR _hoops_HSP _hoops_HRGR
	 * _hoops_ARHAR.
	 */

	if (_hoops_IPRI->local_face_attributes._hoops_SIIPR > 0)
		_hoops_GCCCP = ((Polyhedron*)_hoops_IPRI)->local_face_attributes._hoops_CHHPR();
	else
		_hoops_GCCCP = null;

	if (sc != null && sc->_hoops_AICCP != null) {
		_hoops_HICCP = (_hoops_PCCCP *)sc->_hoops_AICCP;
		_hoops_IICCP = _hoops_HICCP->_hoops_CGCAR;
		_hoops_CICCP = _hoops_HICCP->ws;
		_hoops_SICCP = _hoops_HICCP->_hoops_RRCAR;
		POOL_ALLOC_ARRAY (_hoops_HICCP->_hoops_CGCAR, _hoops_PHCCP, DC_Point, dc->memory_pool);
		POOL_ALLOC_ARRAY (_hoops_HICCP->ws, _hoops_PHCCP, float, dc->memory_pool);
		POOL_ALLOC_ARRAY (_hoops_HICCP->_hoops_RRCAR, _hoops_PHCCP, _hoops_GRCAR, dc->memory_pool);
		POOL_ALLOC_ARRAY (mapping, _hoops_PHCCP, int, dc->memory_pool);

		_hoops_HCCCP = _hoops_HICCP->_hoops_CCCCP.vertex1;
		_hoops_ICCCP = _hoops_HICCP->_hoops_CCCCP.vertex2;
	}

#	define		_hoops_SCCCP(_hoops_AIIPR, _hoops_HIIPR, _hoops_GSCCP, _hoops_IPPGR) \
		 /* _hoops_PGSA _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_HAR _hoops_PCCP _hoops_CRIPR _hoops_PAR _hoops_GSIPR-_hoops_SGH _hoops_ISHA */				\
		(_hoops_HIIPR >= 0 &&													\
																		\
		 /* _hoops_PPR _hoops_RH _hoops_ICICP _hoops_PAHHP (_hoops_HGI _hoops_CRRPR _hoops_RSCCP!) */		\
		 _hoops_GSCCP[_hoops_AIIPR] != _hoops_GSCCP[_hoops_HIIPR] &&			\
																		\
		 /* _hoops_PPR _hoops_RSIPR _hoops_HSP _hoops_HRGR _hoops_GRGA _hoops_PSIPR */					\
		 !(_hoops_IPPGR != null &&										\
		   BIT (_hoops_IPPGR[_hoops_AIIPR]|_hoops_IPPGR[_hoops_HIIPR],					\
				_hoops_HSIPR)))

	_hoops_HHCCP(dc->memory_pool);

	if (_hoops_IPRI->type == _hoops_GSIP) {
		int							columns;
		int							_hoops_ISIPR;
		_hoops_CSSHA const *	_hoops_GSCCP;
		int							_hoops_SSIPR;
		int							face_count;

		//_hoops_RPP (_hoops_CSPH->_hoops_ASCCP == _hoops_IRAP)
			_hoops_IIICP (nr, (Polyhedron*)_hoops_IPRI, true);

		/* _hoops_PPSI _hoops_AGCR _hoops_CGSI _hoops_CRGR _hoops_CPCPR (_hoops_HPGR _hoops_CHGC _hoops_HPPR _hoops_IS) */
		_hoops_GSCCP = dc->_hoops_ACICP;
		columns = ((_hoops_AIHPR *)_hoops_IPRI)->columns;
		_hoops_ISIPR = columns - 1;
		face_count = _hoops_IPRI->face_count;
		_hoops_SSIPR = 2*_hoops_ISIPR;

		while (_hoops_PHHA-- <= 0) {
			/* _hoops_SRS _hoops_GPHA */
			_hoops_ACI = vlist;
			_hoops_AARCP = _hoops_CHCCP;
			pp = points;
			vertex1 = *vi++;
			ei++;

			/* _hoops_GIRPA _hoops_GIHA */
			length = *lengths++ - 1;
			while (length-- > 0) {
				vertex2	   = *vi++;
				_hoops_SHPC = *ei++;

				{
					int		_hoops_ISPI;
					int		_hoops_CSPI;
					int		row;
					int		col;

					if (vertex1 < vertex2) {
						_hoops_ISPI = vertex1;
						_hoops_CSPI = vertex2;
					}
					else {
						_hoops_ISPI = vertex2;
						_hoops_CSPI = vertex1;
					}

					row = _hoops_ISPI / columns;
					col = _hoops_ISPI - row * columns;

					if (_hoops_ISPI + 1 == _hoops_CSPI && col < _hoops_ISIPR) { /* _hoops_GGCPR */
						/* (_hoops_HPSIR '_hoops_PSCCP' _hoops_RPGP _hoops_RGAR _hoops_SIGR _hoops_IH _hoops_HSCCP _hoops_CSHRR) */
						_hoops_AIIPR = 2*col + row*_hoops_SSIPR;		/* _hoops_AAPA _hoops_HSP */
						_hoops_HIIPR = _hoops_AIIPR - _hoops_SSIPR + 1;		/* _hoops_GSSC _hoops_HSP */
						if (_hoops_AIIPR >= face_count) {				/* _hoops_PSAP _hoops_RH _hoops_SCIA */
							_hoops_AIIPR = _hoops_HIIPR;						/* (_hoops_SRCH _hoops_ISCCP _hoops_PSRPA) */
							_hoops_HIIPR = _hoops_PIIPR;
						}
						else if (_hoops_HIIPR < 0) _hoops_HIIPR = _hoops_PIIPR; /* _hoops_PSAP _hoops_RH _hoops_PRPC */
					}
					else if (_hoops_ISPI + columns == _hoops_CSPI) {				/* _hoops_RGCPR _hoops_AGCPR */
						_hoops_AIIPR = 2*col + row*_hoops_SSIPR;		/* _hoops_RPHR _hoops_HSP */
						_hoops_HIIPR = _hoops_AIIPR - 1;						/* _hoops_RAAP _hoops_HSP */
						if (col == _hoops_ISIPR) {					/* _hoops_PSAP _hoops_RH _hoops_RPHR */
							_hoops_AIIPR = _hoops_HIIPR;						/* (_hoops_SRCH _hoops_ISCCP _hoops_PSRPA) */
							_hoops_HIIPR = _hoops_PIIPR;
						}
						else if (col == 0) _hoops_HIIPR = _hoops_PIIPR;		/* _hoops_PSAP _hoops_RH _hoops_RAAP */
					}
					else {										/* _hoops_GH _hoops_PPR _hoops_IS _hoops_RH _hoops_RAAP */
						_hoops_AIIPR = 2*col + row*_hoops_SSIPR - 1;	/* _hoops_AAPA-_hoops_RPHR */
						_hoops_HIIPR = _hoops_AIIPR - 1;						/* _hoops_GSSC-_hoops_RAAP */
					}
				}

				/* _hoops_HCIC _hoops_SCH _hoops_PGCPR? */
				if (_hoops_SCCCP (_hoops_AIIPR, _hoops_HIIPR, _hoops_GSCCP, _hoops_GCCCP)) {
					/* _hoops_PGSA _hoops_SCH */
					if (_hoops_ACI == vlist) { /* _hoops_SRS _hoops_GHIR */
						_hoops_GICCP (vertex1);
						*_hoops_ACI++ = pp++ - points;
						*_hoops_AARCP++ = 0;

						_hoops_GICCP (vertex2);
						*_hoops_ACI++ = pp++ - points;
						*_hoops_AARCP++ = _hoops_SHPC;
					}
					else {
						if (_hoops_ACI[-2] == vertex1) { /* _hoops_PAH _hoops_SAS: _hoops_IRS _hoops_CSCCP */
							_hoops_GICCP (vertex2);
							*_hoops_ACI++ = pp++ - points;
							*_hoops_AARCP++ = _hoops_SHPC;
						}
						else {					/* _hoops_GHHR & _hoops_SIAPR */
							polyedge->total = polyedge->lengths[0] = _hoops_ACI - vlist;
							polyedge->point_count = polyedge->total;
							_hoops_IACIP (nr, polyedge);

							if (_hoops_HICCP != null) {
								if (_hoops_HICCP->_hoops_CCCCP.vertex1 != _hoops_HCCCP)
									_hoops_HICCP->_hoops_CCCCP.vertex1 =
										_hoops_HCCCP = _hoops_IICCP +
													mapping[_hoops_HICCP->_hoops_CCCCP.vertex1 - _hoops_HICCP->_hoops_CGCAR];
								if (_hoops_HICCP->_hoops_CCCCP.vertex2 != _hoops_ICCCP)
									_hoops_HICCP->_hoops_CCCCP.vertex2 =
										_hoops_ICCCP = _hoops_IICCP +
													mapping[_hoops_HICCP->_hoops_CCCCP.vertex2 - _hoops_HICCP->_hoops_CGCAR];
							}

							if (polyedge->_hoops_HSAI > 1) {
								/* _hoops_IIS _hoops_PHHR _hoops_IIGR _hoops_RH _hoops_RHGS _hoops_SPR */
								_hoops_ISAI (polyedge);
								_hoops_HHCCP(dc->memory_pool);
							}

							_hoops_ACI = vlist;
							_hoops_AARCP = _hoops_CHCCP;
							pp = points;

							_hoops_GICCP (vertex1);
							*_hoops_ACI++ = pp++ - points;
							*_hoops_AARCP++ = 0;

							_hoops_GICCP (vertex2);
							*_hoops_ACI++ = pp++ - points;
							*_hoops_AARCP++ = _hoops_SHPC;
						}

						if (_hoops_ACI >= _hoops_SHCCP) {
							/* _hoops_HSRPR _hoops_SCH */
							polyedge->total = polyedge->lengths[0] = _hoops_ACI - vlist;
							polyedge->point_count = polyedge->total;
							_hoops_IACIP (nr, polyedge);

							if (_hoops_HICCP != null) {
								if (_hoops_HICCP->_hoops_CCCCP.vertex1 != _hoops_HCCCP)
									_hoops_HICCP->_hoops_CCCCP.vertex1 =
										_hoops_HCCCP = _hoops_IICCP +
													mapping[_hoops_HICCP->_hoops_CCCCP.vertex1 - _hoops_HICCP->_hoops_CGCAR];
								if (_hoops_HICCP->_hoops_CCCCP.vertex2 != _hoops_ICCCP)
									_hoops_HICCP->_hoops_CCCCP.vertex2 =
										_hoops_ICCCP = _hoops_IICCP +
													mapping[_hoops_HICCP->_hoops_CCCCP.vertex2 - _hoops_HICCP->_hoops_CGCAR];
							}

							if (polyedge->_hoops_HSAI > 1) {
								/* _hoops_IIS _hoops_PHHR _hoops_IIGR _hoops_RH _hoops_RHGS _hoops_SPR */
								_hoops_ISAI (polyedge);
								_hoops_HHCCP(dc->memory_pool);
							}

							_hoops_ACI = vlist;
							_hoops_AARCP = _hoops_CHCCP;
							pp = points;
						}
					}
				}

				vertex1 = vertex2;
			}

			if (_hoops_ACI != vlist) {
				/* _hoops_HSRPR _hoops_SCH */
				polyedge->total = polyedge->lengths[0] = _hoops_ACI - vlist;
				polyedge->point_count = polyedge->total;
				_hoops_IACIP (nr, polyedge);

				if (_hoops_HICCP != null) {
					if (_hoops_HICCP->_hoops_CCCCP.vertex1 != _hoops_HCCCP)
						_hoops_HICCP->_hoops_CCCCP.vertex1 =
							_hoops_HCCCP = _hoops_IICCP +
										mapping[_hoops_HICCP->_hoops_CCCCP.vertex1 - _hoops_HICCP->_hoops_CGCAR];
					if (_hoops_HICCP->_hoops_CCCCP.vertex2 != _hoops_ICCCP)
						_hoops_HICCP->_hoops_CCCCP.vertex2 =
							_hoops_ICCCP = _hoops_IICCP +
										mapping[_hoops_HICCP->_hoops_CCCCP.vertex2 - _hoops_HICCP->_hoops_CGCAR];
				}

				if (polyedge->_hoops_HSAI > 1) {
					/* _hoops_IIS _hoops_PHHR _hoops_IIGR _hoops_RH _hoops_RHGS _hoops_SPR */
					_hoops_ISAI (polyedge);
					_hoops_HHCCP(dc->memory_pool);
				}
			}
		}
	}
	else { /* _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_SSCCP */
		_hoops_CSSHA const *		_hoops_GSCCP;
		_hoops_CGCPR const *			_hoops_SGCPR;
		bool							_hoops_GGSCP = false;
		bool							_hoops_RRSI = false;
		Local_Vertex_Attributes		 *	_hoops_SPRI;
		Shell alter *					_hoops_SPHPR = (Shell alter *)_hoops_IPRI;

		if (_hoops_SPHPR->_hoops_SGCPR == null ||
			_hoops_SPHPR->_hoops_GRCPR == null) {
			/* (_hoops_ASAR)_hoops_ARPR _hoops_RRCPR _hoops_SPPR _hoops_IS _hoops_GCIS _hoops_ISCP _hoops_IHH _hoops_IAS-_hoops_IS-_hoops_RCHP _hoops_SIHC */
			if (_hoops_SPHPR->_hoops_GRCPR != null) {
				FREE_ARRAY (_hoops_SPHPR->_hoops_GRCPR,
							_hoops_IPRI->_hoops_SPHA,
							_hoops_RHHPR);
				_hoops_SPHPR->_hoops_GRCPR = null;
			}

			if (_hoops_SPHPR->_hoops_HHHPR != null) {
				FREE_ARRAY (_hoops_SPHPR->_hoops_HHHPR,
							_hoops_IPRI->point_count + 1,
							_hoops_RHHPR const *);
				_hoops_SPHPR->_hoops_HHHPR = null;
			}

			if (_hoops_SPHPR->_hoops_SGCPR != null) {
				FREE_ARRAY (_hoops_SPHPR->_hoops_SGCPR,
							_hoops_IPRI->_hoops_SPHA,
							_hoops_CGCPR);
				_hoops_SPHPR->_hoops_SGCPR = null;
			}

			HI_Create_Shell_Edges ((Shell alter *)_hoops_IPRI, true);
		}
		_hoops_SPRI = (Local_Vertex_Attributes*) &_hoops_IPRI->local_vertex_attributes;
		if (!_hoops_SPRI->flags)
			HI_Initialize_Vertex_Attributes((Polyhedron alter *)_hoops_IPRI, 0, 0);

		if (ANYBIT (nr->_hoops_IRR->_hoops_SRI, _hoops_SICI|_hoops_PRAAP) &&
			BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_CPCRP) &&
			nr->_hoops_SRA->_hoops_APHHP == null) {
			if (!BIT (_hoops_IPRI->polyhedron_flags, _hoops_APCCP))
				_hoops_SRCCP (nr, (Polyhedron*)_hoops_IPRI);
			if (_hoops_IPRI->local_vertex_attributes._hoops_CACCP != 0)
				_hoops_GGSCP = true;
		}

		if (_hoops_GGSCP) {
			int						i, j, _hoops_SAHAR;
			float alter *			_hoops_PSICP;
			Tristrip *				ts = _hoops_IPRI->tristrips;
			Polyline *				polyline = null;
			Point const *			_hoops_RGSCP = _hoops_IPRI->points;
			Net_Rendition			_hoops_CRAI = nr;
			int						_hoops_HSPI, _hoops_ISPI, _hoops_CSPI;

			POOL_ALLOC_ARRAY_CACHED (_hoops_PSICP, _hoops_IPRI->point_count, float, dc->memory_pool);
			_hoops_ASICP (nr, (Polyhedron*)_hoops_IPRI, _hoops_PSICP, 0.01f);

			_hoops_CRAI.Modify()->_hoops_AHP = _hoops_CRAI->_hoops_RHP;

			while (ts != null) {
				j = 0;
				i = 0;
				while (i<ts->_hoops_PHHA) {
					if (ts->lengths[i] > 0) {
						_hoops_SAHAR = j + ts->lengths[i];
						j += 2;
						while (j < _hoops_SAHAR) {
							_hoops_HSPI = ts->_hoops_AIHA [j-2];
							_hoops_ISPI = ts->_hoops_AIHA [j-1];
							_hoops_CSPI = ts->_hoops_AIHA [j];
							_hoops_RRSI = !BIT(*_hoops_SPRI->_hoops_CHHPR(_hoops_HSPI), _hoops_SACCP) &&
									   !BIT(*_hoops_SPRI->_hoops_CHHPR(_hoops_ISPI), _hoops_SACCP) &&
									   !BIT(*_hoops_SPRI->_hoops_CHHPR(_hoops_CSPI), _hoops_SACCP);
							if (!_hoops_RRSI &&
								_hoops_HPCCP (
									_hoops_PSICP [_hoops_HSPI], _hoops_PSICP [_hoops_ISPI], _hoops_PSICP [_hoops_CSPI],
									&_hoops_RGSCP [_hoops_HSPI], &_hoops_RGSCP [_hoops_ISPI], &_hoops_RGSCP [_hoops_CSPI],
									&polyline)) {
								_hoops_CPAGR (_hoops_CRAI, polyline);
							}
							j++;
						}
					}
					else {
						int _hoops_PGHAR = j;
						_hoops_SAHAR = j + -lengths[i];
						j += 2;
						while (j < _hoops_SAHAR) {
							_hoops_HSPI = ts->_hoops_AIHA [_hoops_PGHAR];
							_hoops_ISPI = ts->_hoops_AIHA [j-1];
							_hoops_CSPI = ts->_hoops_AIHA [j];
							_hoops_RRSI = !BIT(*_hoops_SPRI->_hoops_CHHPR(_hoops_HSPI), _hoops_SACCP) &&
									   !BIT(*_hoops_SPRI->_hoops_CHHPR(_hoops_ISPI), _hoops_SACCP) &&
									   !BIT(*_hoops_SPRI->_hoops_CHHPR(_hoops_CSPI), _hoops_SACCP);
							if (!_hoops_RRSI &&
								_hoops_HPCCP (
									_hoops_PSICP [_hoops_HSPI], _hoops_PSICP [_hoops_ISPI], _hoops_PSICP [_hoops_CSPI],
									&_hoops_RGSCP [_hoops_HSPI], &_hoops_RGSCP [_hoops_ISPI], &_hoops_RGSCP [_hoops_CSPI],
									&polyline)) {
								_hoops_CPAGR (_hoops_CRAI, polyline);
							}
							j++;
						}
					}
					i++;
				}
				ts = ts->next;
			}
			if (polyline != null)
				_hoops_HPRH (polyline);
			FREE_ARRAY (_hoops_PSICP, _hoops_IPRI->point_count, float);
		}

		/* _hoops_IPCP _hoops_HSPR _hoops_IGIPR _hoops_SGS _hoops_GISA-_hoops_ARCPR-_hoops_PRCPR _hoops_SSCP _hoops_RPII _hoops_ASAS */
		//_hoops_RPP (_hoops_CSPH->_hoops_ASCCP == _hoops_IRAP)
			_hoops_IIICP (nr, (Polyhedron*)_hoops_IPRI, true);

		/* _hoops_PPSI _hoops_AGCR _hoops_CGSI _hoops_CRGR _hoops_CPCPR (_hoops_HPGR _hoops_CHGC _hoops_HPPR _hoops_IS) */
		_hoops_GSCCP = dc->_hoops_ACICP;
		_hoops_SGCPR	 = _hoops_SPHPR->_hoops_SGCPR;

		if (!BIT (_hoops_IPRI->polyhedron_flags, _hoops_PGCCP))
			_hoops_GGCCP ((Polyhedron*)_hoops_IPRI);
		//_hoops_AGSCP _hoops_RCIC *_hoops_PGSCP = _hoops_CPHAR->_hoops_HGSCP._hoops_SGI;

		while (_hoops_PHHA-- > 0) {
			/* _hoops_SRS _hoops_GPHA */
			_hoops_ACI = vlist;
			_hoops_AARCP = _hoops_CHCCP;
			pp = points;
			vertex1 = *vi++;
			ei++;

			/* _hoops_GIRPA _hoops_GIHA */
			length = *lengths++ - 1;
			while (length-- > 0) {
				vertex2	   = *vi++;
				_hoops_SHPC = *ei++;

				/*_hoops_RPP (!_hoops_AGGC (_hoops_PGSCP[_hoops_IGSCP], _hoops_AGCCP|_hoops_CGSCP))*/ {
					_hoops_AIIPR = _hoops_SGCPR[_hoops_SHPC]._hoops_AIIPR;
					_hoops_HIIPR = _hoops_SGCPR[_hoops_SHPC]._hoops_HIIPR;

					/* _hoops_PCHIA _hoops_GII _hoops_SAHP _hoops_SGS _hoops_CHH _hoops_SHH _hoops_GIR _hoops_HPP _hoops_RH _hoops_IPCGP _hoops_RIIRA (_hoops_CACH _hoops_ARRS) */
					if (_hoops_GGSCP)
						_hoops_RRSI = BIT(*_hoops_SPRI->_hoops_CHHPR(vertex1), _hoops_SACCP) &&
									BIT(*_hoops_SPRI->_hoops_CHHPR(vertex2), _hoops_SACCP);

					/* _hoops_HCIC _hoops_SCH _hoops_PGCPR? */
					if (!_hoops_RRSI &&
						_hoops_SCCCP (_hoops_AIIPR, _hoops_HIIPR, _hoops_GSCCP, _hoops_GCCCP)) {

						/* _hoops_PGSA _hoops_SCH */
						if (_hoops_ACI == vlist) { /* _hoops_SRS _hoops_GHIR */
							_hoops_GICCP (vertex1);
							*_hoops_ACI++ = pp++ - points;
							*_hoops_AARCP++ = 0;

							_hoops_GICCP (vertex2);
							*_hoops_ACI++ = pp++ - points;
							*_hoops_AARCP++ = _hoops_SHPC;
							_hoops_RCCCP = vertex2;
						}
						else {
							if (vertex1 == _hoops_RCCCP) { /* _hoops_PAH _hoops_SAS: _hoops_IRS _hoops_CSCCP */
								_hoops_GICCP (vertex2);
								*_hoops_ACI++ = pp++ - points;
								*_hoops_AARCP++ = _hoops_SHPC;
							}
							else {
								/* _hoops_GHHR _hoops_PGHC; _hoops_GGCR _hoops_RGR _hoops_SPR */
								polyedge->total = polyedge->lengths[0] = _hoops_ACI - vlist;
								polyedge->point_count = polyedge->total;
								_hoops_IACIP (nr, polyedge);

								if (_hoops_HICCP != null) {
									if (_hoops_HICCP->_hoops_CCCCP.vertex1 != _hoops_HCCCP)
										_hoops_HICCP->_hoops_CCCCP.vertex1 =
											_hoops_HCCCP = _hoops_IICCP +
														mapping[_hoops_HICCP->_hoops_CCCCP.vertex1 - _hoops_HICCP->_hoops_CGCAR];
									if (_hoops_HICCP->_hoops_CCCCP.vertex2 != _hoops_ICCCP)
										_hoops_HICCP->_hoops_CCCCP.vertex2 =
											_hoops_ICCCP = _hoops_IICCP +
														mapping[_hoops_HICCP->_hoops_CCCCP.vertex2 - _hoops_HICCP->_hoops_CGCAR];
								}

								if (polyedge->_hoops_HSAI > 1) {
									/* _hoops_IIS _hoops_PHHR _hoops_IIGR _hoops_RH _hoops_RHGS _hoops_SPR */
									_hoops_ISAI (polyedge);
									_hoops_HHCCP(dc->memory_pool);
								}

								_hoops_ACI = vlist;
								_hoops_AARCP = _hoops_CHCCP;
								pp = points;

								_hoops_GICCP (vertex1);
								*_hoops_ACI++ = pp++ - points;
								*_hoops_AARCP++ = 0;

								_hoops_GICCP (vertex2);
								*_hoops_ACI++ = pp++ - points;
								*_hoops_AARCP++ = _hoops_SHPC;
							}
							_hoops_RCCCP = vertex2;

							if (_hoops_ACI >= _hoops_SHCCP) {
								/* _hoops_HSRPR _hoops_SCH */
								polyedge->total = polyedge->lengths[0] = _hoops_ACI - vlist;
								polyedge->point_count = polyedge->total;
								_hoops_IACIP (nr, polyedge);

								if (_hoops_HICCP != null) {
									if (_hoops_HICCP->_hoops_CCCCP.vertex1 != _hoops_HCCCP)
										_hoops_HICCP->_hoops_CCCCP.vertex1 =
											_hoops_HCCCP = _hoops_IICCP +
														mapping[_hoops_HICCP->_hoops_CCCCP.vertex1 - _hoops_HICCP->_hoops_CGCAR];
									if (_hoops_HICCP->_hoops_CCCCP.vertex2 != _hoops_ICCCP)
										_hoops_HICCP->_hoops_CCCCP.vertex2 =
											_hoops_ICCCP = _hoops_IICCP +
														mapping[_hoops_HICCP->_hoops_CCCCP.vertex2 - _hoops_HICCP->_hoops_CGCAR];
								}

								if (polyedge->_hoops_HSAI > 1) {
									/* _hoops_IIS _hoops_PHHR _hoops_IIGR _hoops_RH _hoops_RHGS _hoops_SPR */
									_hoops_ISAI (polyedge);
									_hoops_HHCCP(dc->memory_pool);
								}

								_hoops_ACI = vlist;
								_hoops_AARCP = _hoops_CHCCP;
								pp = points;
							}
						}
					}
				}
				vertex1 = vertex2;
			}

			if (_hoops_ACI != vlist) {
				polyedge->total = polyedge->lengths[0] = _hoops_ACI - vlist;
				polyedge->point_count = polyedge->total;
				_hoops_IACIP (nr, polyedge);

				if (_hoops_HICCP != null) {
					if (_hoops_HICCP->_hoops_CCCCP.vertex1 != _hoops_HCCCP)
						_hoops_HICCP->_hoops_CCCCP.vertex1 =
							_hoops_HCCCP = _hoops_IICCP +
										mapping[_hoops_HICCP->_hoops_CCCCP.vertex1 - _hoops_HICCP->_hoops_CGCAR];
					if (_hoops_HICCP->_hoops_CCCCP.vertex2 != _hoops_ICCCP)
						_hoops_HICCP->_hoops_CCCCP.vertex2 =
							_hoops_ICCCP = _hoops_IICCP +
										mapping[_hoops_HICCP->_hoops_CCCCP.vertex2 - _hoops_HICCP->_hoops_CGCAR];
				}

				if (polyedge->_hoops_HSAI > 1) {
					/* _hoops_IIS _hoops_PHHR _hoops_IIGR _hoops_RH _hoops_RHGS _hoops_SPR */
					_hoops_ISAI (polyedge);
					_hoops_HHCCP(dc->memory_pool);
				}
			}
		}
	}

	if (sc != null && sc->_hoops_AICCP) {
		FREE_ARRAY (_hoops_HICCP->_hoops_CGCAR, _hoops_PHCCP, DC_Point);
		FREE_ARRAY (_hoops_HICCP->ws, _hoops_PHCCP, float);
		FREE_ARRAY (_hoops_HICCP->_hoops_RRCAR, _hoops_PHCCP, _hoops_GRCAR);
		FREE_ARRAY (mapping, _hoops_PHCCP, int);
		_hoops_HICCP->_hoops_CGCAR = (DC_Point alter *)_hoops_IICCP;
		_hoops_HICCP->ws = (float alter *)_hoops_CICCP;
		_hoops_HICCP->_hoops_RRCAR = (_hoops_GRCAR alter *)_hoops_SICCP;
	}

	if (polyedge && _hoops_ISAI (polyedge) == 0)
		HI_Free_Polyedge (polyedge);
}


GLOBAL_FUNCTION void HD_Draw_NonCulled_Edges (
	Net_Rendition const &		nr,
	Polyedge const *			_hoops_RASGR) {
	Display_Context const *		dc = (Display_Context const *)nr->_hoops_SRA;
	int							vertex1;
	int							vertex2;
	int							_hoops_AIIPR;
	int							_hoops_HIIPR;
	int							_hoops_SHPC;
	int							_hoops_PHHA = _hoops_RASGR->_hoops_PHHA;
	int const *					lengths = _hoops_RASGR->lengths;
	int const *					vi = _hoops_RASGR->_hoops_AIHA;
	int const *					ei = _hoops_RASGR->_hoops_SPII;
	Polyhedron const *			_hoops_IPRI = (Polyhedron*)_hoops_RASGR->_hoops_GSCP;
	int *						vlist = 0;
	int *						_hoops_CHCCP = 0;
	int alter *					_hoops_SHCCP = 0;
	int alter *					_hoops_ACI;
	int alter *					_hoops_AARCP;
	_hoops_GIIPR const *	_hoops_GCCCP;
	Polyedge *					polyedge;
	int							length;
	Point						points[_hoops_PHCCP];
	Point alter *				pp = points;
	_hoops_ACCCP *			sc = nr->_hoops_SRA->_hoops_APHHP;
	_hoops_PCCCP *			_hoops_HICCP = null;
	DC_Point const *			_hoops_IICCP = null;
	float const *				_hoops_CICCP = null;
	_hoops_GRCAR const *			_hoops_SICCP = null;
	DC_Point const *			_hoops_HCCCP = null;
	DC_Point const *			_hoops_ICCCP = null;
	int alter *					mapping = null;

	/*
	 * _hoops_HSRR _hoops_GRR _hoops_ISHA _hoops_GIAA _hoops_RGR _hoops_CIIA _hoops_ACRI, _hoops_IPS _hoops_SCH _hoops_IS _hoops_PCCP _hoops_IIPR _hoops_HIGR
	 * _hoops_RPP _hoops_PPR _hoops_RGAR _hoops_RPP _hoops_SCH _hoops_SSCP _hoops_PGCR _hoops_HISS _hoops_RSSI, _hoops_GIPR _hoops_CHR "_hoops_HAR _hoops_PSIPR",
	 * _hoops_PPR _hoops_PGI _hoops_SPR _hoops_HSP _hoops_RSSI _hoops_CPCHR _hoops_PPR _hoops_SPR _hoops_HPIPR _hoops_PAR _hoops_SPR _hoops_HSP _hoops_HRGR
	 * _hoops_ARHAR.
	 */

	if (_hoops_IPRI->local_face_attributes._hoops_SIIPR > 0)
		_hoops_GCCCP = ((Polyhedron*)_hoops_IPRI)->local_face_attributes._hoops_CHHPR();
	else
		_hoops_GCCCP = null;

	if (sc != null && sc->_hoops_AICCP != null) {
		_hoops_HICCP = (_hoops_PCCCP *)sc->_hoops_AICCP;
		_hoops_IICCP = _hoops_HICCP->_hoops_CGCAR;
		_hoops_CICCP = _hoops_HICCP->ws;
		_hoops_SICCP = _hoops_HICCP->_hoops_RRCAR;
		POOL_ALLOC_ARRAY (_hoops_HICCP->_hoops_CGCAR, _hoops_PHCCP, DC_Point, dc->memory_pool);
		POOL_ALLOC_ARRAY (_hoops_HICCP->ws, _hoops_PHCCP, float, dc->memory_pool);
		POOL_ALLOC_ARRAY (_hoops_HICCP->_hoops_RRCAR, _hoops_PHCCP, _hoops_GRCAR, dc->memory_pool);
		POOL_ALLOC_ARRAY (mapping, _hoops_PHCCP, int, dc->memory_pool);

		_hoops_HCCCP = _hoops_HICCP->_hoops_CCCCP.vertex1;
		_hoops_ICCCP = _hoops_HICCP->_hoops_CCCCP.vertex2;
	}


#	define		_hoops_SGSCP(_hoops_AIIPR, _hoops_HIIPR, _hoops_GSCCP, _hoops_IPPGR)					\
		 /* _hoops_PGSA _hoops_RPP _hoops_SCH _hoops_SSCP _hoops_IRS _hoops_SIGC _hoops_RIHA _hoops_HSP */									\
		(_hoops_GSCCP[_hoops_AIIPR] != _hoops_HARCA &&										\
		 (_hoops_IPPGR == null || !BIT (_hoops_IPPGR[_hoops_AIIPR], _hoops_HSIPR)) ||	\
		 _hoops_HIIPR >= 0 && _hoops_GSCCP[_hoops_HIIPR] != _hoops_HARCA &&						\
		 (_hoops_IPPGR == null || !BIT (_hoops_IPPGR[_hoops_HIIPR], _hoops_HSIPR)))

	_hoops_HHCCP(dc->memory_pool);

	if (_hoops_IPRI->type == _hoops_GSIP) {
		/* _hoops_IPCP _hoops_HSPR _hoops_IGCPR _hoops_CHR "_hoops_GGR _hoops_AGR" */
		int							columns;
		int							_hoops_ISIPR;
		_hoops_CSSHA const	*	_hoops_GSCCP;
		int							_hoops_SSIPR;
		int							face_count;

		//_hoops_RPP (_hoops_CSPH->_hoops_ASCCP == _hoops_IRAP)
			_hoops_IIICP (nr, (Polyhedron*)_hoops_IPRI, false);

		/* _hoops_PPSI _hoops_AGCR _hoops_CGSI _hoops_CRGR _hoops_CPCPR (_hoops_HPGR _hoops_CHGC _hoops_HPPR _hoops_IS) */
		_hoops_GSCCP = dc->_hoops_ACICP;
		columns = ((_hoops_AIHPR const *)_hoops_IPRI)->columns;
		_hoops_ISIPR = columns - 1;
		face_count = _hoops_IPRI->face_count;
		_hoops_SSIPR = 2*_hoops_ISIPR;

		while (_hoops_PHHA-- <= 0) {
			/* _hoops_SRS _hoops_GPHA */
			_hoops_ACI = vlist;
			_hoops_AARCP = _hoops_CHCCP;
			pp = points;
			vertex1 = *vi++;
			ei++;

			/* _hoops_GIRPA _hoops_GIHA */
			length = *lengths++ - 1;
			while (length-- > 0) {
				vertex2	   = *vi++;
				_hoops_SHPC = *ei++;

				{
					int		_hoops_ISPI;
					int		_hoops_CSPI;
					int		row;
					int		col;

					if (vertex1 < vertex2) {
						_hoops_ISPI = vertex1;
						_hoops_CSPI = vertex2;
					}
					else {
						_hoops_ISPI = vertex2;
						_hoops_CSPI = vertex1;
					}

					row = _hoops_ISPI / columns;
					col = _hoops_ISPI - row * columns;

					if (_hoops_ISPI + 1 == _hoops_CSPI && col < _hoops_ISIPR) { /* _hoops_GGCPR */
						/* (_hoops_HPSIR '_hoops_PSCCP' _hoops_RPGP _hoops_RGAR _hoops_SIGR _hoops_IH _hoops_HSCCP _hoops_CSHRR) */
						_hoops_AIIPR = 2*col + row*_hoops_SSIPR;		/* _hoops_AAPA _hoops_HSP */
						_hoops_HIIPR = _hoops_AIIPR - _hoops_SSIPR + 1;		/* _hoops_GSSC _hoops_HSP */
						if (_hoops_AIIPR >= face_count) {				/* _hoops_PSAP _hoops_RH _hoops_SCIA */
							_hoops_AIIPR = _hoops_HIIPR;						/* (_hoops_SRCH _hoops_ISCCP _hoops_PSRPA) */
							_hoops_HIIPR = _hoops_PIIPR;
						}
						else if (_hoops_HIIPR < 0) _hoops_HIIPR = _hoops_PIIPR; /* _hoops_PSAP _hoops_RH _hoops_PRPC */
					}
					else if (_hoops_ISPI + columns == _hoops_CSPI) {				/* _hoops_RGCPR _hoops_AGCPR */
						_hoops_AIIPR = 2*col + row*_hoops_SSIPR;		/* _hoops_RPHR _hoops_HSP */
						_hoops_HIIPR = _hoops_AIIPR - 1;						/* _hoops_RAAP _hoops_HSP */
						if (col == _hoops_ISIPR) {					/* _hoops_PSAP _hoops_RH _hoops_RPHR */
							_hoops_AIIPR = _hoops_HIIPR;						/* (_hoops_SRCH _hoops_ISCCP _hoops_PSRPA) */
							_hoops_HIIPR = _hoops_PIIPR;
						}
						else if (col == 0) _hoops_HIIPR = _hoops_PIIPR;		/* _hoops_PSAP _hoops_RH _hoops_RAAP */
					}
					else {										/* _hoops_GH _hoops_PPR _hoops_IS _hoops_RH _hoops_RAAP */
						_hoops_AIIPR = 2*col + row*_hoops_SSIPR - 1;	/* _hoops_AAPA-_hoops_RPHR */
						_hoops_HIIPR = _hoops_AIIPR - 1;						/* _hoops_GSSC-_hoops_RAAP */
					}
				}

				/* _hoops_HCIC _hoops_SCH _hoops_PGCPR? */
				if (_hoops_SGSCP (_hoops_AIIPR, _hoops_HIIPR, _hoops_GSCCP, _hoops_GCCCP)) {
					/* _hoops_PGSA _hoops_SCH */
					if (_hoops_ACI == vlist) { /* _hoops_SRS _hoops_GHIR */
						_hoops_GICCP (vertex1);
						*_hoops_ACI++ = pp++ - points;
						*_hoops_AARCP++ = 0;

						_hoops_GICCP (vertex2);
						*_hoops_ACI++ = pp++ - points;
						*_hoops_AARCP++ = _hoops_SHPC;
					}
					else {
						if (_hoops_ACI[-2] == vertex1) { /* _hoops_PAH _hoops_SAS: _hoops_IRS _hoops_CSCCP */
							_hoops_GICCP (vertex2);
							*_hoops_ACI++ = pp++ - points;
							*_hoops_AARCP++ = _hoops_SHPC;
						}
						else {
							/* _hoops_GHHR & _hoops_SIAPR */
							polyedge->total = polyedge->lengths[0] = _hoops_ACI - vlist;
							polyedge->point_count = polyedge->total;
							_hoops_IACIP (nr, polyedge);

							if (_hoops_HICCP != null) {
								if (_hoops_HICCP->_hoops_CCCCP.vertex1 != _hoops_HCCCP)
									_hoops_HICCP->_hoops_CCCCP.vertex1 =
										_hoops_HCCCP = _hoops_IICCP +
													mapping[_hoops_HICCP->_hoops_CCCCP.vertex1 - _hoops_HICCP->_hoops_CGCAR];
								if (_hoops_HICCP->_hoops_CCCCP.vertex2 != _hoops_ICCCP)
									_hoops_HICCP->_hoops_CCCCP.vertex2 =
										_hoops_ICCCP = _hoops_IICCP +
													mapping[_hoops_HICCP->_hoops_CCCCP.vertex2 - _hoops_HICCP->_hoops_CGCAR];
							}

							if (polyedge->_hoops_HSAI > 1) {
								/* _hoops_IIS _hoops_PHHR _hoops_IIGR _hoops_RH _hoops_RHGS _hoops_SPR */
								_hoops_ISAI (polyedge);
								_hoops_HHCCP(dc->memory_pool);
							}

							_hoops_ACI = vlist;
							_hoops_AARCP = _hoops_CHCCP;
							pp = points;

							_hoops_GICCP (vertex1);
							*_hoops_ACI++ = pp++ - points;
							*_hoops_AARCP++ = 0;

							_hoops_GICCP (vertex2);
							*_hoops_ACI++ = pp++ - points;
							*_hoops_AARCP++ = _hoops_SHPC;
						}

						if (_hoops_ACI >= _hoops_SHCCP) {
							/* _hoops_HSRPR _hoops_SCH */
							polyedge->total = polyedge->lengths[0] = _hoops_ACI - vlist;
							polyedge->point_count = polyedge->total;
							_hoops_IACIP (nr, polyedge);

							if (_hoops_HICCP != null) {
								if (_hoops_HICCP->_hoops_CCCCP.vertex1 != _hoops_HCCCP)
									_hoops_HICCP->_hoops_CCCCP.vertex1 =
										_hoops_HCCCP = _hoops_IICCP +
													mapping[_hoops_HICCP->_hoops_CCCCP.vertex1 - _hoops_HICCP->_hoops_CGCAR];
								if (_hoops_HICCP->_hoops_CCCCP.vertex2 != _hoops_ICCCP)
									_hoops_HICCP->_hoops_CCCCP.vertex2 =
										_hoops_ICCCP = _hoops_IICCP +
													mapping[_hoops_HICCP->_hoops_CCCCP.vertex2 - _hoops_HICCP->_hoops_CGCAR];
							}

							if (polyedge->_hoops_HSAI > 1) {
								/* _hoops_IIS _hoops_PHHR _hoops_IIGR _hoops_RH _hoops_RHGS _hoops_SPR */
								_hoops_ISAI (polyedge);
								_hoops_HHCCP(dc->memory_pool);
							}

							_hoops_ACI = vlist;
							_hoops_AARCP = _hoops_CHCCP;
							pp = points;
						}
					}
				}

				vertex1 = vertex2;
			}

			if (_hoops_ACI != vlist) {
				polyedge->total = polyedge->lengths[0] = _hoops_ACI - vlist;
				polyedge->point_count = polyedge->total;
				_hoops_IACIP (nr, polyedge);

				if (_hoops_HICCP != null) {
					if (_hoops_HICCP->_hoops_CCCCP.vertex1 != _hoops_HCCCP)
						_hoops_HICCP->_hoops_CCCCP.vertex1 =
							_hoops_HCCCP = _hoops_IICCP +
										mapping[_hoops_HICCP->_hoops_CCCCP.vertex1 - _hoops_HICCP->_hoops_CGCAR];
					if (_hoops_HICCP->_hoops_CCCCP.vertex2 != _hoops_ICCCP)
						_hoops_HICCP->_hoops_CCCCP.vertex2 =
							_hoops_ICCCP = _hoops_IICCP +
										mapping[_hoops_HICCP->_hoops_CCCCP.vertex2 - _hoops_HICCP->_hoops_CGCAR];
				}

				if (polyedge->_hoops_HSAI > 1) {
					/* _hoops_IIS _hoops_PHHR _hoops_IIGR _hoops_RH _hoops_RHGS _hoops_SPR */
					_hoops_ISAI (polyedge);
					_hoops_HHCCP(dc->memory_pool);
				}
			}
		}
	}
	else { /* _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_SSCCP */
		_hoops_CSSHA const *		_hoops_GSCCP;
		_hoops_CGCPR const *			_hoops_SGCPR;
		Local_Vertex_Attributes const *	_hoops_SPRI;
		Shell alter *					_hoops_SPHPR = (Shell alter *)_hoops_IPRI;

		if (_hoops_SPHPR->_hoops_SGCPR == null ||
			_hoops_SPHPR->_hoops_GRCPR == null) {
			/* (_hoops_ASAR)_hoops_ARPR _hoops_RRCPR _hoops_SPPR _hoops_IS _hoops_GCIS _hoops_ISCP _hoops_IHH _hoops_IAS-_hoops_IS-_hoops_RCHP _hoops_SIHC */
			if (_hoops_SPHPR->_hoops_GRCPR != null) {
				FREE_ARRAY (_hoops_SPHPR->_hoops_GRCPR,
							_hoops_IPRI->_hoops_SPHA,
							_hoops_RHHPR);
				_hoops_SPHPR->_hoops_GRCPR = null;
			}

			if (_hoops_SPHPR->_hoops_HHHPR != null) {
				FREE_ARRAY (_hoops_SPHPR->_hoops_HHHPR,
							_hoops_IPRI->point_count + 1,
							_hoops_RHHPR const *);
				_hoops_SPHPR->_hoops_HHHPR = null;
			}

			if (_hoops_SPHPR->_hoops_SGCPR != null) {
				FREE_ARRAY (_hoops_SPHPR->_hoops_SGCPR,
							_hoops_IPRI->_hoops_SPHA,
							_hoops_CGCPR);
				_hoops_SPHPR->_hoops_SGCPR = null;
			}

			HI_Create_Shell_Edges ((Shell alter *)_hoops_IPRI, true);
		}
		_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

		/* _hoops_IPCP _hoops_HSPR _hoops_IGIPR _hoops_SGS _hoops_GISA-_hoops_ARCPR-_hoops_PRCPR _hoops_SSCP _hoops_RPII _hoops_ASAS */
		//_hoops_RPP (_hoops_CSPH->_hoops_ASCCP == _hoops_IRAP)
			_hoops_IIICP (nr, (Polyhedron*)_hoops_IPRI, false);

		/* _hoops_PPSI _hoops_AGCR _hoops_CGSI _hoops_CRGR _hoops_CPCPR (_hoops_HPGR _hoops_CHGC _hoops_HPPR _hoops_IS) */
		_hoops_GSCCP = dc->_hoops_ACICP;
		_hoops_SGCPR	 = _hoops_SPHPR->_hoops_SGCPR;

		while (_hoops_PHHA-- > 0) {
			/* _hoops_SRS _hoops_GPHA */
			_hoops_ACI = vlist;
			_hoops_AARCP = _hoops_CHCCP;
			pp = points;
			vertex1 = *vi++;
			ei++;

			/* _hoops_GIRPA _hoops_GIHA */
			length = *lengths++ - 1;
			while (length-- > 0) {
				vertex2	   = *vi++;
				_hoops_SHPC = *ei++;

				_hoops_AIIPR = _hoops_SGCPR[_hoops_SHPC]._hoops_AIIPR;
				_hoops_HIIPR = _hoops_SGCPR[_hoops_SHPC]._hoops_HIIPR;

				/* _hoops_HCIC _hoops_SCH _hoops_PGCPR? */
				if (_hoops_SGSCP (_hoops_AIIPR, _hoops_HIIPR, _hoops_GSCCP, _hoops_GCCCP)) {
					/* _hoops_PGSA _hoops_SCH */
					if (_hoops_ACI == vlist) { /* _hoops_SRS _hoops_GHIR */
						_hoops_GICCP (vertex1);
						*_hoops_ACI++ = pp++ - points;
						*_hoops_AARCP++ = 0;

						_hoops_GICCP (vertex2);
						*_hoops_ACI++ = pp++ - points;
						*_hoops_AARCP++ = _hoops_SHPC;
					}
					else {
						if (_hoops_ACI[-1] == vertex1) { /* _hoops_PAH _hoops_SAS: _hoops_IRS _hoops_CSCCP */
							_hoops_GICCP (vertex2);
							*_hoops_ACI++ = pp++ - points;
							*_hoops_AARCP++ = _hoops_SHPC;
						}
						else {
							/* _hoops_GHHR _hoops_PGHC; _hoops_GGCR _hoops_RGR _hoops_SPR */
							polyedge->total = polyedge->lengths[0] = _hoops_ACI - vlist;
							polyedge->point_count = polyedge->total;
							_hoops_IACIP (nr, polyedge);

							if (_hoops_HICCP != null) {
								if (_hoops_HICCP->_hoops_CCCCP.vertex1 != _hoops_HCCCP)
									_hoops_HICCP->_hoops_CCCCP.vertex1 =
										_hoops_HCCCP = _hoops_IICCP +
													mapping[_hoops_HICCP->_hoops_CCCCP.vertex1 - _hoops_HICCP->_hoops_CGCAR];
								if (_hoops_HICCP->_hoops_CCCCP.vertex2 != _hoops_ICCCP)
									_hoops_HICCP->_hoops_CCCCP.vertex2 =
										_hoops_ICCCP = _hoops_IICCP +
													mapping[_hoops_HICCP->_hoops_CCCCP.vertex2 - _hoops_HICCP->_hoops_CGCAR];
							}

							if (polyedge->_hoops_HSAI > 1) {
								/* _hoops_IIS _hoops_PHHR _hoops_IIGR _hoops_RH _hoops_RHGS _hoops_SPR */
								_hoops_ISAI (polyedge);
								_hoops_HHCCP(dc->memory_pool);
							}

							_hoops_ACI = vlist;
							_hoops_AARCP = _hoops_CHCCP;
							pp = points;

							_hoops_GICCP (vertex1);
							*_hoops_ACI++ = pp++ - points;
							*_hoops_AARCP++ = 0;

							_hoops_GICCP (vertex2);
							*_hoops_ACI++ = pp++ - points;
							*_hoops_AARCP++ = _hoops_SHPC;
						}

						if (_hoops_ACI >= _hoops_SHCCP) {
							/* _hoops_HSRPR _hoops_SCH */
							polyedge->total = polyedge->lengths[0] = _hoops_ACI - vlist;
							polyedge->point_count = polyedge->total;
							_hoops_IACIP (nr, polyedge);

							if (_hoops_HICCP != null) {
								if (_hoops_HICCP->_hoops_CCCCP.vertex1 != _hoops_HCCCP)
									_hoops_HICCP->_hoops_CCCCP.vertex1 =
										_hoops_HCCCP = _hoops_IICCP +
													mapping[_hoops_HICCP->_hoops_CCCCP.vertex1 - _hoops_HICCP->_hoops_CGCAR];
								if (_hoops_HICCP->_hoops_CCCCP.vertex2 != _hoops_ICCCP)
									_hoops_HICCP->_hoops_CCCCP.vertex2 =
										_hoops_ICCCP = _hoops_IICCP +
													mapping[_hoops_HICCP->_hoops_CCCCP.vertex2 - _hoops_HICCP->_hoops_CGCAR];
							}

							if (polyedge->_hoops_HSAI > 1) {
								/* _hoops_IIS _hoops_PHHR _hoops_IIGR _hoops_RH _hoops_RHGS _hoops_SPR */
								_hoops_ISAI (polyedge);
								_hoops_HHCCP(dc->memory_pool);
							}

							_hoops_ACI = vlist;
							_hoops_AARCP = _hoops_CHCCP;
							pp =points;
						}
					}
				}
				vertex1 = vertex2;
			}

			if (_hoops_ACI != vlist) {
				/* _hoops_HSRPR _hoops_SCH */
				polyedge->total = polyedge->lengths[0] = _hoops_ACI - vlist;
				polyedge->point_count = polyedge->total;
				_hoops_IACIP (nr, polyedge);

				if (_hoops_HICCP != null) {
					if (_hoops_HICCP->_hoops_CCCCP.vertex1 != _hoops_HCCCP)
						_hoops_HICCP->_hoops_CCCCP.vertex1 =
							_hoops_HCCCP = _hoops_IICCP +
										mapping[_hoops_HICCP->_hoops_CCCCP.vertex1 - _hoops_HICCP->_hoops_CGCAR];
					if (_hoops_HICCP->_hoops_CCCCP.vertex2 != _hoops_ICCCP)
						_hoops_HICCP->_hoops_CCCCP.vertex2 =
							_hoops_ICCCP = _hoops_IICCP +
										mapping[_hoops_HICCP->_hoops_CCCCP.vertex2 - _hoops_HICCP->_hoops_CGCAR];
				}

				if (polyedge->_hoops_HSAI > 1) {
					/* _hoops_IIS _hoops_PHHR _hoops_IIGR _hoops_RH _hoops_RHGS _hoops_SPR */
					_hoops_ISAI (polyedge);
					_hoops_HHCCP(dc->memory_pool);
				}
			}
		}
	}

	if (sc != null && sc->_hoops_AICCP) {
		FREE_ARRAY (_hoops_HICCP->_hoops_CGCAR, _hoops_PHCCP, DC_Point);
		FREE_ARRAY (_hoops_HICCP->ws, _hoops_PHCCP, float);
		FREE_ARRAY (_hoops_HICCP->_hoops_RRCAR, _hoops_PHCCP, _hoops_GRCAR);
		FREE_ARRAY (mapping, _hoops_PHCCP, int);
		_hoops_HICCP->_hoops_CGCAR = (DC_Point alter *)_hoops_IICCP;
		_hoops_HICCP->ws = (float alter *)_hoops_CICCP;
		_hoops_HICCP->_hoops_RRCAR = (_hoops_GRCAR alter *)_hoops_SICCP;
	}

	if (polyedge && _hoops_ISAI (polyedge) == 0)
		HI_Free_Polyedge (polyedge);
}

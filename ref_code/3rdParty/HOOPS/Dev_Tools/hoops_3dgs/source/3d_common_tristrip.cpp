/*
 * Copyright (c) 2009 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.  Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.143 2011-01-19 21:12:03 warren Exp $
 */


#if defined(DX9_DRIVER) || \
	defined(WIN32_OPENGL2_DRIVER) || \
	defined(GLX_OPENGL2_DRIVER) || \
	defined(AGL_OPENGL2_DRIVER) || \
	defined(_hoops_CGPAR) || \
	defined(OPENGL2_DRIVER)

void _hoops_SGPAR(H3DData* data);

//_hoops_SRPA _hoops_HRSP _hoops_GRPAR _hoops_HGPP _hoops_SGS _hoops_PIRC _hoops_HRGR _hoops_IRS _hoops_GIRA _hoops_RRPAR _hoops_HSAR _hoops_ARPAR _hoops_HII _hoops_GII _hoops_RII
#define _hoops_PRPAR 0.7f
local void _hoops_HRPAR (_hoops_RSSH *f1, _hoops_RSSH *f2, _hoops_RSSH *_hoops_CGHGR)
{
	if (*f1 == 0.0f)
		*f1 = 0.5f * (*f2+*_hoops_CGHGR);
	if (*f2 == 0.0f)
		*f2 = 0.5f * (*f1+*_hoops_CGHGR);
	if (*_hoops_CGHGR == 0.0f)
		*_hoops_CGHGR = 0.5f * (*f1+*f2);

	while (*f1-*f2 > _hoops_PRPAR)
		*f2 += 1.0f;
	while (*f1-*_hoops_CGHGR > _hoops_PRPAR)
		*_hoops_CGHGR += 1.0f;
	while (*f2-*f1 > _hoops_PRPAR) {
		*f1 += 1.0f;
		while (*f1-*_hoops_CGHGR > _hoops_PRPAR)
			*_hoops_CGHGR += 1.0f;
	}
	while (*f2-*_hoops_CGHGR > _hoops_PRPAR)
		*_hoops_CGHGR += 1.0f;
	while (*_hoops_CGHGR-*f1 > _hoops_PRPAR) {
		*f1 += 1.0f;
		while (*f1-*f2 > _hoops_PRPAR)
			*f2 += 1.0f;
	}
	while (*_hoops_CGHGR-*f2 > _hoops_PRPAR) {
		*f2 += 1.0f;
		while (*f2-*f1 > _hoops_PRPAR)
			*f1 += 1.0f;
	}
	ASSERT (*f1-*f2 < _hoops_PRPAR);
	ASSERT (*f2-*f1 < _hoops_PRPAR);
	ASSERT (*f1-*_hoops_CGHGR < _hoops_PRPAR);
	ASSERT (*_hoops_CGHGR-*f1 < _hoops_PRPAR);
	ASSERT (*_hoops_CGHGR-*f2 < _hoops_PRPAR);
	ASSERT (*f2-*_hoops_CGHGR < _hoops_PRPAR);
}



local void _hoops_IRPAR (
	Net_Rendition const &		nr,
	Tristrip const *			ts,
	_hoops_ARPA const *				_hoops_GGARR,
	H3DVertexBuffer *			_hoops_HACP,
	int							_hoops_CACP,
	_hoops_HRPA const *			_hoops_SHAS,
	RGB const *					_hoops_GPCP,
	_hoops_HCI *			_hoops_RPCP,
	int							_hoops_CRPAR)
{
	_hoops_SSAGR(_hoops_SHAS);
	_hoops_SSAGR(&ts->points[_hoops_CACP]);

	_hoops_HHA const &	matr = nr->_hoops_IHA->_hoops_CHA;
	_hoops_HHA const &	_hoops_SHA = nr->_hoops_IHA->_hoops_GIA;
	H3DData *					h3ddata = H3DD(nr->_hoops_SRA);
	float						_hoops_APCP;
	int							_hoops_PSR = 0, offset = 0, param_width = ts->_hoops_GSSH ? ts->_hoops_GSSH->_hoops_GSHA : 0;
	int							_hoops_RICP;
	float						u, v, s;
	H3DVertexFormat				_hoops_PPCP = _hoops_HACP->_hoops_HPCP();
	float						_hoops_IRIR = nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR;
	/*_hoops_IPCP _hoops_CPCP _hoops_GHCP _hoops_PIHA _hoops_SHH _hoops_GAR _hoops_SPCP:
	* _hoops_AHC
	* _hoops_GSSR
	* _hoops_IACA
	* _hoops_HAIR
	* _hoops_HH
	*/

	// _hoops_RHCP _hoops_AHC
	if (_hoops_SHAS == null) {
		_hoops_HACP->_hoops_AHCP(ts->points[_hoops_CACP]);
		if (_hoops_PPCP._hoops_HHCP()) {
			if (ts->_hoops_ICHA)
				_hoops_HACP->_hoops_IHCP(ts->_hoops_ICHA[_hoops_CACP]);
			else if (ts->_hoops_PRHH)
				_hoops_HACP->_hoops_IHCP(ts->_hoops_PRHH[_hoops_CRPAR]);
		}
		if (_hoops_GGARR) {
			int _hoops_SRPAR;
			_hoops_SII(_hoops_RHRR, 0, _hoops_RPCP, &_hoops_SRPAR, null, null);
			ASSERT(_hoops_SRPAR != -1);
			_hoops_ARPA const *t = _hoops_GGARR + _hoops_CACP;
			_hoops_HACP->_hoops_IICGR(t, _hoops_SRPAR);
		}
	}
	else {
		_hoops_APCP = 1.0f / _hoops_PHCP (_hoops_SHAS->elements, ts->points[_hoops_CACP]);
		_hoops_HACP->_hoops_AHCP(_hoops_HPRA(_hoops_SHAS->elements, ts->points[_hoops_CACP]) * _hoops_APCP,
				_hoops_IPRA(_hoops_SHAS->elements, ts->points[_hoops_CACP]) * _hoops_APCP,
				_hoops_CPRA(_hoops_SHAS->elements, ts->points[_hoops_CACP]) * _hoops_APCP);
		if (_hoops_PPCP._hoops_HHCP()) {
			_hoops_ARPA plane;
			Vector vector;

			ASSERT (_hoops_SHAS->_hoops_APRA != null);

			if (ts->_hoops_ICHA)
				plane = _hoops_ARPA (ts->_hoops_ICHA[_hoops_CACP], ts->points[_hoops_CACP]);
			else
				plane = ts->_hoops_PRHH[_hoops_CRPAR];

			_hoops_RPRA const *	_hoops_APRA = _hoops_SHAS->_hoops_APRA->data.elements;

			vector.x = plane.a*_hoops_APRA[0][0] + plane.b*_hoops_APRA[0][1] + plane.c*_hoops_APRA[0][2] + plane.d*_hoops_APRA[0][3];
			vector.y = plane.a*_hoops_APRA[1][0] + plane.b*_hoops_APRA[1][1] + plane.c*_hoops_APRA[1][2] + plane.d*_hoops_APRA[1][3];
			vector.z = plane.a*_hoops_APRA[2][0] + plane.b*_hoops_APRA[2][1] + plane.c*_hoops_APRA[2][2] + plane.d*_hoops_APRA[2][3];
			if (BIT(_hoops_SHAS->_hoops_RAGR, _hoops_CHCP))
				HI_Normalize(&vector);

			_hoops_HACP->_hoops_IHCP(vector);
		}
	}

	if (_hoops_PPCP._hoops_PSCP()) {
		// _hoops_RHCP _hoops_PSHA
		if (_hoops_PPCP._hoops_SHCP()) {
			const RGB *_hoops_IASGR = null;
			if (ts->_hoops_PCHA)
				_hoops_IASGR = &ts->_hoops_PCHA[_hoops_CACP];
			else if (ts->_hoops_PAGI)
				_hoops_IASGR = &ts->_hoops_PAGI[_hoops_CRPAR];
			else
				_hoops_IASGR = _hoops_GPCP;

			ASSERT(_hoops_IASGR);  //_hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_SPR _hoops_IIGR _hoops_AGCR, _hoops_ICRS _hoops_PAHA'_hoops_RA _hoops_HS _hoops_SPI _hoops_ARP
			_hoops_HACP->color(_hoops_GICP(h3ddata->_hoops_SHAP, _hoops_IASGR->red, _hoops_IASGR->green, _hoops_IASGR->blue, _hoops_IRIR));
		}

		// _hoops_AICP _hoops_PICP _hoops_IIGR _hoops_RH _hoops_GGAR _hoops_HH _hoops_RPP _hoops_SCH _hoops_HICP
		if (ts->_hoops_SRHA & _hoops_GGIA) {
			_hoops_GRA const &		_hoops_RRA = nr->_hoops_ARA;
			
			_hoops_SII(_hoops_IAAR, 0, _hoops_RPCP, &_hoops_RICP, null, null);
			_hoops_HACP->_hoops_IICP(ts->_hoops_HCHA[_hoops_CACP] * _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate,
					0,
					0,
					_hoops_RICP);
		}

		//_hoops_RH _hoops_PIRA _hoops_GGR _hoops_RRAP _hoops_HRGR _hoops_RCCP _hoops_IS _hoops_ACCP _hoops_SHH _hoops_PCCP _hoops_HCCP _hoops_HIIA
		ASSERT (h3ddata->_hoops_AIC == 
				  (nr->_hoops_IRR->_hoops_SRI == _hoops_GAI && 
				   BIT (nr->transform_rendition->heuristics, _hoops_IRI) &&
				   !BIT (ts->_hoops_SRHA, DL_SHADOW_TRISTRIP)));
		if (h3ddata->_hoops_AIC) {
			float _hoops_ICCP;

			if (ts->_hoops_CCCP != null)
				_hoops_ICCP = ts->_hoops_CCCP[_hoops_CACP];
			else if (ts->_hoops_GSCP)
				_hoops_ICCP = _hoops_SCCP(ts->_hoops_GSCP->priority,1);
			else
				_hoops_ICCP = _hoops_SCCP(nr->_hoops_SRA->_hoops_RAI->priority,1);
			_hoops_SII(_hoops_ACPR, 0, _hoops_RPCP, &_hoops_RICP, null, null);
			_hoops_HACP->u (_hoops_ICCP, _hoops_RICP);
		}

		// _hoops_IISH _hoops_GGSR _hoops_HCPI _hoops_GRPC _hoops_IH _hoops_RSPH _hoops_HCPI _hoops_AGIR. _hoops_GAPAR _hoops_SAIA.
		if (ts->_hoops_CARI & _hoops_APIA) {
			// _hoops_RAPAR _hoops_AIAA _hoops_RSSA _hoops_IRHH _hoops_IRS _hoops_PCPI. _hoops_AAPAR _hoops_GGR _hoops_RH _hoops_PCPI _hoops_CHR _hoops_SR?
			int const i = _hoops_HACP->_hoops_IACGR();
			_hoops_SII(_hoops_HCRR, 0, _hoops_RPCP, &_hoops_RICP, null, null);
			_hoops_HACP->_hoops_IICP((i & 2) ? -1 : +1,
					(i & 1) ? -1 : +1,
					0,
					_hoops_RICP);
		}

		// _hoops_GRAR _hoops_PCRR
		if (matr->_hoops_ARIR && param_width > 0) {
			int _hoops_PAPAR = 0;
			_hoops_HIR *	_hoops_PGC = matr->_hoops_SCA;
			_hoops_RRCC *	_hoops_HAPAR = ts->_hoops_GSSH;

			while (_hoops_PGC) {
				_hoops_PSR = _hoops_PGC->texture->_hoops_PSR;
				offset = _hoops_PGC->texture->_hoops_RSCP;
				if (_hoops_HAPAR)
					param_width = _hoops_HAPAR->_hoops_GSHA;

				if (offset > param_width)
					offset = 0;

				u = v = s = 0;
				if (_hoops_PSR != HK_PS_WORLD) {
					if (_hoops_HAPAR) {
						if (offset+0 < param_width) u = _hoops_HAPAR->_hoops_CCHA[_hoops_CACP * param_width + offset + 0];
						if (offset+1 < param_width) v = _hoops_HAPAR->_hoops_CCHA[_hoops_CACP * param_width + offset + 1];
						if (offset+2 < param_width) s = _hoops_HAPAR->_hoops_CCHA[_hoops_CACP * param_width + offset + 2];
					}
				}

				_hoops_SII(_hoops_PSRR, _hoops_PAPAR++, _hoops_RPCP, &_hoops_RICP, null, null);
				_hoops_HACP->_hoops_IICP(u, v, s, _hoops_RICP);
				_hoops_PGC = _hoops_PGC->next;
				if (_hoops_HAPAR && _hoops_HAPAR->next)
					_hoops_HAPAR = _hoops_HAPAR->next;

				if (_hoops_RPCP->_hoops_RGC)
					break;
			}

			/* _hoops_RGAR _hoops_SPI _hoops_AI _hoops_PICP _hoops_AHCA _hoops_IAPAR _hoops_PPR _hoops_SHI */
			_hoops_PSR = 0;
			offset = 0;

			if (matr->texture[_hoops_HIA]) {
				_hoops_SII(_hoops_PPAR, 0, _hoops_RPCP, &_hoops_RICP, null, null);
				u = v = s = 0;
				if (param_width > 0) u = ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * param_width + 0];
				if (param_width > 1) v = ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * param_width + 1];
				if (param_width > 2) s = ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * param_width + 2];
				_hoops_HACP->_hoops_IICP(u, v, s, _hoops_RICP);
			}

			if (matr->texture[_hoops_IIA]) {
				_hoops_SII(_hoops_APAR, 0, _hoops_RPCP, &_hoops_RICP, null, null);
				u = v = s = 0;
				if (param_width > 0) u = ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * param_width + 0];
				if (param_width > 1) v = ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * param_width + 1];
				if (param_width > 2) s = ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * param_width + 2];
				_hoops_HACP->_hoops_IICP(u, v, s, _hoops_RICP);
			}

			if (matr->texture[_hoops_ACA]) {
				_hoops_SII(_hoops_RPAR, 0, _hoops_RPCP, &_hoops_RICP, null, null);
				u = v = s = 0;
				if (param_width > 0) u = ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * param_width + 0];
				if (param_width > 1) v = ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * param_width + 1];
				if (param_width > 2) s = ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * param_width + 2];
				_hoops_HACP->_hoops_IICP(u, v, s, _hoops_RICP);
			}

			if (matr->texture[_hoops_PCA]) {
				_hoops_SII(_hoops_HPAR, 0, _hoops_RPCP, &_hoops_RICP, null, null);
				u = v = s = 0;
				if (param_width > 0) u = ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * param_width + 0];
				if (param_width > 1) v = ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * param_width + 1];
				if (param_width > 2) s = ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * param_width + 2];
				_hoops_HACP->_hoops_IICP(u, v, s, _hoops_RICP);
			}

			if (matr->texture[_hoops_HCA]) {
				_hoops_SII(_hoops_CPAR, 0, _hoops_RPCP, &_hoops_RICP, null, null);
				u = v = s = 0;
				if (param_width > 0) u = ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * param_width + 0];
				if (param_width > 1) v = ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * param_width + 1];
				if (param_width > 2) s = ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * param_width + 2];
				_hoops_HACP->_hoops_IICP(u, v, s, _hoops_RICP);
			}
		}

		if (_hoops_SHA != matr && _hoops_SHA->_hoops_ARIR && param_width > 0) {
			int _hoops_PAPAR = 0;
			_hoops_HIR *_hoops_PGC = _hoops_SHA->_hoops_SCA;
			while (_hoops_PGC) {
				_hoops_PSR = _hoops_PGC->texture->_hoops_PSR;
				offset = _hoops_PGC->texture->_hoops_RSCP;
				if (offset > param_width)
					offset = 0;

				u = v = s = 0;
				if (_hoops_PSR != HK_PS_WORLD) {
					if (offset+0 < param_width) u = ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * param_width + offset + 0];
					if (offset+1 < param_width) v = ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * param_width + offset + 1];
					if (offset+2 < param_width) s = ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * param_width + offset + 2];
				}

				_hoops_SII(_hoops_IRAR, _hoops_PAPAR++, _hoops_RPCP, &_hoops_RICP, null, null);
				_hoops_HACP->_hoops_IICP(u, v, s, _hoops_RICP);
				_hoops_PGC = _hoops_PGC->next;
			}
		}
	}
}


#define _hoops_CAPAR() (_hoops_PPCP._hoops_PSCP() || _hoops_SHAS || _hoops_GPCP || _hoops_GGARR || h3ddata->_hoops_AIC)

INLINE void _hoops_SAPAR(H3DVertexFormat _hoops_PPCP,
	Net_Rendition const &nr, H3DData alter *h3ddata, Tristrip const *ts, _hoops_ARPA const *_hoops_GGARR,
	H3DVertexBuffer &_hoops_PAIH, int _hoops_CACP, 
	_hoops_HRPA const *_hoops_SHAS, RGB const *_hoops_GPCP, 
	_hoops_HCI * _hoops_RPCP, int _hoops_CRPAR)
{
	ASSERT (_hoops_CACP < ts->point_count);
	ASSERT (_hoops_CRPAR < ts->face_count || (ts->_hoops_PRHH == null && ts->_hoops_PAGI == null));
	if (h3ddata->_hoops_PGARR) {
		_hoops_IRPAR(nr, ts, _hoops_GGARR, &_hoops_PAIH, _hoops_CACP, _hoops_SHAS, _hoops_GPCP, _hoops_RPCP, _hoops_CRPAR);
	}
	else {
		ASSERT (!(_hoops_PPCP._hoops_PSCP() || _hoops_SHAS || _hoops_GPCP || ts->_hoops_CCCP));
		_hoops_PAIH._hoops_AHCP(ts->points[_hoops_CACP]);
		if (_hoops_PPCP._hoops_HHCP()) {
			if (ts->_hoops_ICHA)
				_hoops_PAIH._hoops_IHCP(ts->_hoops_ICHA[_hoops_CACP]);
			else
				_hoops_PAIH._hoops_IHCP(ts->_hoops_PRHH[_hoops_CRPAR]);
		}
	}
	_hoops_PAIH._hoops_CPPH();
}



int _hoops_SRGAR(H3DData *h3ddata, H3D_Display_List_Bin *_hoops_RRHA)
{
	int i, j;
	int point_count = 0;
	int _hoops_SRIRR;
	short *_hoops_PHAS;
	int _hoops_GHAS = 0;
	_hoops_IRHA *pair;
	Tristrip const *ts;

	ASSERT(_hoops_RRHA);

	_hoops_RRHA->_hoops_CRHA->ResetCursor();
	pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();

	if (!pair)
		return 0;

	ts = (Tristrip const *) pair->geo;


	for (;;) {
		point_count = _hoops_IRGAR(ts);
		_hoops_PHAS = _hoops_AIAS(h3ddata, point_count);
		if (_hoops_PHAS)
			SET_MEMORY(_hoops_PHAS, point_count*sizeof(short), -1);

		/* _hoops_PHIR _hoops_RH _hoops_CIHA _hoops_SRHR */
		i = j = 0;
		for (i = 0; i < ts->total; i++)
			_hoops_CRIRR(_hoops_SRIRR, ts->_hoops_AIHA[i], false);

		if (_hoops_RRHA) {
			_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
			pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
			if (!pair)
				break;
			ts = (Tristrip const *) pair->geo;
		}
		else
			break;
	}

	// _hoops_HA _hoops_SR _hoops_HS _hoops_RH _hoops_APSR _hoops_GPHA _hoops_SRHR _hoops_IGIR _hoops_SIGR, _hoops_SR _hoops_PAH _hoops_HIAP _hoops_RH _hoops_HIGR _hoops_PPR _hoops_CIPH _hoops_PIH
	_hoops_RRHA->_hoops_CRHA->ResetCursor();

	return _hoops_GHAS;
}


void _hoops_GPPAR(
		H3D_Display_List_Bin *_hoops_RRHA,
		H3D_Vertex_Buffer_Style _hoops_APHA,
		unsigned int alter *_hoops_SCPI,
		unsigned int alter *_hoops_RPPAR)
{
	int point_count = 0;
	int _hoops_APPAR = 0;
	_hoops_IRHA *pair;
	Tristrip const *ts;

	ASSERT(_hoops_RRHA);

	_hoops_RRHA->_hoops_CRHA->ResetCursor();
	pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();

	if (!pair)
		return;
	ts = (Tristrip const *) pair->geo;
	for (;;) {
		point_count += ts->point_count;
		_hoops_APPAR += ts->total;
		if (_hoops_RRHA) {
			_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
			pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
			if (!pair)
				break;
			ts = (Tristrip const *) pair->geo;
		}
		else
			break;
	}

	// _hoops_HA _hoops_SR _hoops_HS _hoops_RH _hoops_APSR _hoops_GPHA _hoops_SRHR _hoops_IGIR _hoops_SIGR, _hoops_SR _hoops_PAH _hoops_HIAP _hoops_RH _hoops_HIGR _hoops_PPR _hoops_CIPH _hoops_PIH
	_hoops_RRHA->_hoops_CRHA->ResetCursor();

	*_hoops_SCPI = point_count;
	*_hoops_RPPAR = _hoops_APPAR;
	UNREFERENCED (_hoops_APHA);
}



int _hoops_RHA(Tristrip const *ts, bool _hoops_PAA)
{
	int _hoops_RCHA = 0;
	if (ts == null)
		return 0;

	if (ts->_hoops_AIHA)
		_hoops_RCHA |= _hoops_ACHA;
	if (ts->face_indices)
		_hoops_RCHA |= _hoops_RISRR;
	if (ts->_hoops_PCHA)
		_hoops_RCHA |= _hoops_CAA;
	if (ts->_hoops_HCHA)
		_hoops_RCHA |= _hoops_HGP;
	if (ts->_hoops_ICHA)
		_hoops_RCHA |= _hoops_HSA;
	if (ts->_hoops_GSSH && ts->_hoops_GSSH->_hoops_CCHA)
		_hoops_RCHA |= _hoops_SCHA;
	if (ts->_hoops_GSSH && ts->_hoops_GSSH->_hoops_GSHA)
		_hoops_RCHA |= _hoops_PIA;
	if (ts->_hoops_PAGI)
		_hoops_RCHA |= _hoops_PGP;
	if (ts->_hoops_PRHH)
		_hoops_RCHA |= _hoops_ISA;
	if (BIT(ts->_hoops_SRHA, _hoops_GGIA))
		_hoops_RCHA |= _hoops_IGP;
	if (!ANYBIT (_hoops_RCHA, _hoops_PGP|_hoops_CAA)) {
		if (_hoops_PAA) {
			//_hoops_AAHA _hoops_PSHA _hoops_PAH _hoops_SHH _hoops_HSHA _hoops_GAR _hoops_GPHA _hoops_PAR _hoops_HSP _hoops_PSHA, _hoops_CSHA _hoops_HRGR _hoops_SSHA
			if (BIT (_hoops_RCHA, _hoops_ISA))
				_hoops_RCHA |= _hoops_PGP;
			else
				_hoops_RCHA |= _hoops_CAA;
		}
	}

	return _hoops_RCHA;
}

H3D_Vertex_Buffer_Style _hoops_HRGAR (
	H3DData const *h3ddata,
	Tristrip const *ts,
	_hoops_CIGA const &_hoops_SIGA,
	H3D_Display_List_Bin alter *_hoops_RRHA,
	unsigned int *_hoops_ARHA)
{
	bool _hoops_PRHA;
	unsigned int flags;
	int _hoops_PPPAR;

	if (_hoops_RRHA) {
		_hoops_IRHA *pair = _hoops_RRHA->_hoops_CRHA->PeekFirst();
		ts = (Tristrip const *) pair->geo;
		flags = *_hoops_ARHA = _hoops_RRHA->flags;
	}
	else
		flags = *_hoops_ARHA = ts->_hoops_SRHA;

	if (BIT(flags, DL_DO_NOT_RECOMPILE)) {
		H3D_Display_List *odl = (H3D_Display_List *) ts->_hoops_GAHA->list;
		_hoops_PPPAR = odl->_hoops_RAHA;
	}
	else {
		//_hoops_SR _hoops_GA'_hoops_RA _hoops_RRP _hoops_RH _hoops_AAHA _hoops_ARI, _hoops_CR _hoops_SCH _hoops_PAHA'_hoops_RA _hoops_HAHA _hoops_SRHR _hoops_IAHA
		_hoops_PPPAR = _hoops_RHA(ts, false);
	}

	_hoops_PRHA = (
			BIT(_hoops_PPPAR, _hoops_HSA) ||
			BIT(_hoops_PPPAR, _hoops_CAA) ||
			BIT(_hoops_PPPAR, _hoops_IGP) ||
			_hoops_SIGA->_hoops_CHA->_hoops_ARIR ||
			_hoops_SIGA->_hoops_GIA->_hoops_ARIR ||
			h3ddata->_hoops_RPARR);

	// _hoops_ISRS _hoops_AIAH _hoops_HICP, _hoops_HIS _hoops_RGAR _hoops_RRP _hoops_IS _hoops_CAHA _hoops_GGSR _hoops_RPP _hoops_SR _hoops_RRP _hoops_GPHA _hoops_GGAR
	if (BIT(flags, DL_DO_NOT_RECOMPILE)) {
		if (_hoops_PRHA)
			return H3D_Unshared_Vertices;
		else
			return H3D_Partially_Shared_Vertices;
	}

	if (ts->_hoops_GSSH && BIT (ts->_hoops_GSSH->_hoops_SCAI, _hoops_HPPAR))
		return H3D_Unshared_Vertices;

	// _hoops_SSCR _hoops_GGSR _hoops_PGAP _hoops_CRHH _hoops_CRAA _hoops_IS _hoops_IRAA, _hoops_PPR _hoops_HGCR _hoops_IPPAR _hoops_CIRGR/_hoops_CPPAR
	if (BIT(_hoops_PPPAR, _hoops_ISA) || BIT(_hoops_PPPAR, _hoops_PGP)) {
		if (_hoops_PRHA)
			return H3D_Unshared_Vertices;
		else
			return H3D_Partially_Shared_Vertices;
	}
	else
		return H3D_Shared_Vertices;
}

bool _hoops_SPPAR(H3DIndexedBufferObject **_hoops_HRRS, H3D_Display_List_Bin *_hoops_RRHA, H3D_Display_List *odl)
{
	H3DIndexedBufferObject *_hoops_CGPS;
	bool _hoops_GIGI = false;

	delete *_hoops_HRRS;

	if (odl->item.geometry.id) {
		odl->item.geometry.id->ResetCursor();

		while((_hoops_CGPS = (H3DIndexedBufferObject*) odl->item.geometry.id->PeekCursor()) != null)
			delete _hoops_CGPS;
	}
	if (_hoops_RRHA) {
		FREE(odl, H3D_Display_List);
		_hoops_RRHA->odl = null;
		_hoops_RRHA->flags |= DL_INSUFFICIENT_VRAM;
		_hoops_GIGI = false;
	}
	else {
		HD_Queue_Destroy_List(odl, true);
		_hoops_GIGI = true;
	}

	return _hoops_GIGI;
}

_hoops_ARPA *_hoops_GHPAR(H3DData *h3ddata, Tristrip const *ts);

bool _hoops_RHPAR (
		Net_Rendition const &nr,
		H3DVertexFormat _hoops_PPCP,
		Tristrip const *ts,
		_hoops_ARPA const *_hoops_GGARR,
		H3D_Display_List_Bin *_hoops_RRHA,
		H3D_Bounding_Tree *_hoops_RSPS,
		int *_hoops_AHPAR,
		int _hoops_SCPI,
		int face_count,
		_hoops_HCI _hoops_RPCP,
		H3D_Display_List *odl)
{
	Display_Context alter *dc = (Display_Context alter *) nr->_hoops_SRA;
	H3DData alter *h3ddata = H3DD (dc);
	bool status = true;

	float *_hoops_ICPS = null;
	short *_hoops_CCPS = null;

	H3DIndexedBufferObject *_hoops_PHPAR = null;
	int stride = 2;			// _hoops_IGI _hoops_IH 32-_hoops_IGRH _hoops_PSPI
	int _hoops_PCPS = _hoops_SCPI;
	int _hoops_HCPS = face_count * 3;
	bool _hoops_AAAS = false;
	H3DVertexBuffer &_hoops_PAIH = h3ddata->_hoops_CP;		// _hoops_IGI _hoops_IH _hoops_AH "_hoops_SI" _hoops_PSCA
	H3DVertexBuffer _hoops_HHPAR;	// _hoops_IGI _hoops_IH _hoops_HACH "_hoops_AIRI _hoops_HIGR" _hoops_PSCA
	H3DIndexBuffer _hoops_SGIRR;
	H3DIndexBuffer _hoops_IHPAR;
	int _hoops_SCHC = 0;	//_hoops_IGI _hoops_IH _hoops_GSRI _hoops_GPGR _hoops_CHPAR
	int _hoops_GHAS = 0;
	int _hoops_SHPAR = 0;
	// _hoops_IGI _hoops_IH _hoops_GIPAR
	int *_hoops_PHAS = h3ddata->_hoops_ISRRR;
	int _hoops_CRPAR = 0;
	int _hoops_RIPAR = 0;
	bool _hoops_PCGS = false;
	H3DFORMAT format = H3DFMT_INDEX32;
	int _hoops_AIPAR;
	int _hoops_PIPAR = 0;
	int _hoops_HIPAR;
	int point_count;
	H3DIndexedBufferObject *_hoops_IIPAR = null;
	int i, j, len;
	bool _hoops_CIPAR = false;
	_hoops_IRHA *pair = null;
	_hoops_HRPA const *_hoops_SHAS = null;
	RGB const *_hoops_GPCP = _hoops_CCAI (dc->_hoops_SPA->color, Color_FRONT);
	int _hoops_SIPAR = (int) _hoops_AHIA (h3ddata->_hoops_ACGH._hoops_CGGI, h3ddata->_hoops_ACGH._hoops_GRGI);
	if (_hoops_SIPAR > H3D_Display_List_MAX_SIZE)
		_hoops_SIPAR = H3D_Display_List_MAX_SIZE;

	if (_hoops_SCPI > _hoops_SIPAR) {
		_hoops_PCPS = _hoops_SIPAR;
		_hoops_AAAS = true;		//_hoops_RRP _hoops_IS _hoops_HHGP _hoops_CRGR _hoops_GPGR _hoops_AIRI _hoops_CPCI
	}
	if (face_count > _hoops_SIPAR) {
		_hoops_HCPS = _hoops_SIPAR * 3;
		_hoops_AAAS = true;
	}

	if (_hoops_PCPS <= 0xffff) {
		format = H3DFMT_INDEX16;

		if (face_count > 0xffff) {
			_hoops_HCPS = 0xffff;
			_hoops_AAAS = true;
		}
	}
	else {
		format = H3DFMT_INDEX32;
	}

	/* 16 _hoops_IGRH _hoops_CSHRR _hoops_HGAP _hoops_HSP _hoops_GCPAR _hoops_GPHA _hoops_RPR _hoops_IIGR <= 0xffff, _hoops_PGAP _hoops_HRGR
	 * _hoops_HAH _hoops_RCPAR, _hoops_HIS _hoops_SR _hoops_ACPAR _hoops_CSHRR _hoops_IS 32 _hoops_IGRH
	 */
	if (format == H3DFMT_INDEX32) {
		_hoops_PHPAR = h3ddata->_hoops_GSCR->_hoops_CAIRR();
		if (!_hoops_PHPAR->_hoops_CAIRR(h3ddata, _hoops_PCPS, face_count, _hoops_PPCP)) {
			status = false;
			goto _hoops_HPAGR;
		}
	}
	else {

		if (format == H3DFMT_INDEX16)
			stride = 1;
		else
			stride = 2;

		_hoops_ACRRR(h3ddata, _hoops_ICPS, _hoops_PCPS * _hoops_PPCP._hoops_HGHS(false));
		_hoops_HCRRR(h3ddata, _hoops_CCPS, face_count * 3 * stride);
	}

	if (_hoops_RRHA) {
		_hoops_RRHA->_hoops_CRHA->ResetCursor();
		pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
		ts = (Tristrip const *) pair->geo;
		if (pair->_hoops_CPAI)
			_hoops_SHAS = &pair->_hoops_CPAI->matrix;
		else
			_hoops_SHAS = null;
		if (_hoops_SHAS && _hoops_PPCP._hoops_HHCP() && _hoops_SHAS->_hoops_APRA == null)
			HI_Validate_Matrix_Adjoint((_hoops_HRPA alter *)_hoops_SHAS);
		_hoops_GPCP = _hoops_CCAI (pair->color, Color_FRONT);
		_hoops_HIPAR = _hoops_RRHA->_hoops_CRHA->Count();
	}
	else
		_hoops_HIPAR = 1;

	_hoops_IHPAR = _hoops_SGIRR;
	for (_hoops_AIPAR = 0; ; _hoops_AIPAR++) {	// _hoops_HAPR _hoops_RHIR _hoops_HCR _hoops_RH _hoops_CHPAR
		if (_hoops_AHPAR) {
			if (_hoops_PCGS)	// _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_PCPAR _hoops_GAPR, _hoops_SCH _hoops_PIHA _hoops_SHH _hoops_RH _hoops_SRS _hoops_PAIRR
				_hoops_AHPAR[_hoops_AIPAR - _hoops_PIPAR] = _hoops_IHPAR - _hoops_SGIRR;
			else
				_hoops_AHPAR[_hoops_AIPAR - _hoops_PIPAR] = 0;
		}

		point_count = _hoops_IRGAR(ts);
		_hoops_PHAS = _hoops_IPGAR(h3ddata, point_count);
		if (_hoops_PHAS)
			SET_MEMORY(_hoops_PHAS, point_count*sizeof(int), -1);
		h3ddata->_hoops_PGARR = _hoops_CAPAR ();

		/* _hoops_PHIR _hoops_RH _hoops_CIHA _hoops_SRHR */
		i = j = 0;
		_hoops_IHPAR = _hoops_SGIRR + _hoops_SCHC;
		j = 0;
		for (i = 0; i < ts->_hoops_PHHA; i++) {
			len = ts->lengths[i];
			if (len < 0)
				len = -len;

			int _hoops_HCPAR = j;
			int _hoops_ICPAR = j+len-2;

			if (_hoops_CIPAR)
				_hoops_HCPAR--;

			for (; j < _hoops_ICPAR; j++) {

				if (_hoops_PCGS && _hoops_AAAS &&
					(_hoops_GHAS > _hoops_PCPS - 3 ||
					_hoops_SHPAR * 3 > _hoops_HCPS - 3)) {
					//_hoops_PAH'_hoops_RA _hoops_CIPH _hoops_GII _hoops_RRI _hoops_RSSA, _hoops_HIS _hoops_GGCR _hoops_RH _hoops_SRHR _hoops_IS _hoops_RH _hoops_AIRI _hoops_HIGR

					_hoops_IIPAR = h3ddata->_hoops_GSCR->_hoops_PRAS();
					if (!_hoops_IIPAR)
						status = false;
					if (status)
						status = _hoops_IIPAR->CreateVertexBuffer (h3ddata,
							_hoops_GHAS,
							_hoops_PPCP);
					if (status)
						status = _hoops_IIPAR->CreateIndexBuffer(
							h3ddata,
							H3DPT_TRIANGLELIST,
							_hoops_SHPAR * 3 * stride,
							_hoops_SHPAR);
					if (!status) {
						_hoops_SPPAR(&_hoops_IIPAR, _hoops_RRHA, odl);
						goto _hoops_HPAGR;
					}

					_hoops_IIPAR->LockVertexBuffer(0, 0, &_hoops_HHPAR, 0);
					COPY_MEMORY(_hoops_PAIH._hoops_ARHS(), _hoops_GHAS * _hoops_PPCP._hoops_HGHS(), _hoops_HHPAR._hoops_HACGR());
					_hoops_IIPAR->UnlockVertexBuffer();

					_hoops_IIPAR->LockIndexBuffer(0,0, &_hoops_IHPAR, 0);
					_hoops_IHPAR._hoops_RSHRR(_hoops_SGIRR, _hoops_SHPAR * 3);
					_hoops_IIPAR->UnlockIndexBuffer();

					//_hoops_GGCR _hoops_IS _hoops_AIRI _hoops_HIGR
					if (odl->item.geometry.id == 0)
						odl->item.geometry.id = POOL_NEW(dc->memory_pool, H3DIndexedBufferObject_List)(dc->memory_pool);
					odl->item.geometry.id->AddFirst(_hoops_IIPAR);

					if (_hoops_PHPAR) {
						_hoops_PHPAR->UnlockVertexBuffer();
						_hoops_PHPAR->UnlockIndexBuffer();
					}

					// _hoops_ARP _hoops_GH _hoops_PPHS'_hoops_GRI _hoops_IASC _hoops_HPHS
					_hoops_RIPAR++;
					if (_hoops_RSPS) {
						_hoops_IIPAR->_hoops_IAHS = _hoops_RSPS;
						_hoops_CAHS (_hoops_RSPS);
					}
					_hoops_IIPAR->_hoops_SAHS			= _hoops_AIPAR - _hoops_PIPAR + 1;
					_hoops_IIPAR->_hoops_GPHS			= _hoops_PIPAR;
					if (_hoops_HIPAR > 1) {
						ALLOC_ARRAY(_hoops_IIPAR->_hoops_RPHS, _hoops_IIPAR->_hoops_SAHS, int);
						_hoops_AIGA(_hoops_AHPAR, _hoops_IIPAR->_hoops_SAHS, int, _hoops_IIPAR->_hoops_RPHS);
					}
					else
						_hoops_IIPAR->_hoops_RPHS = null;

					_hoops_PCGS = false;
				}
				if (!_hoops_PCGS) {
					if (_hoops_PHPAR) {
						_hoops_PHPAR->LockVertexBuffer(0, 0, &_hoops_PAIH, 0);
						_hoops_PHPAR->LockIndexBuffer(0, 0, &_hoops_SGIRR, 0);
					}
					else {
						//_hoops_ASAR-_hoops_HSPC _hoops_HHH _hoops_CCPAR
						_hoops_SGIRR._hoops_IRA(format, _hoops_CCPS);
						_hoops_PAIH._hoops_IRA(_hoops_ICPS, &_hoops_PPCP);
					}
					_hoops_SCHC = 0;
					_hoops_GHAS = 0;
					_hoops_SHPAR = 0;
					_hoops_IHPAR = _hoops_SGIRR;
					_hoops_PIPAR = _hoops_AIPAR;

					_hoops_PHAS = _hoops_IPGAR(h3ddata, point_count);
					if (_hoops_PHAS)
						SET_MEMORY(h3ddata->_hoops_ISRRR, point_count*sizeof(int), -1);
					_hoops_PCGS = true;
				}

				int _hoops_SCPAR = ts->_hoops_AIHA[j];
				int _hoops_GSPAR = ts->_hoops_AIHA[j+1];
				int _hoops_RSPAR = ts->_hoops_AIHA[j+2];
				int _hoops_RHAS, _hoops_AHAS, _hoops_ASPAR;

				if (_hoops_PHAS) {
					_hoops_RHAS = _hoops_PHAS[_hoops_SCPAR];
					if (_hoops_RHAS < 0) {
						_hoops_RHAS = _hoops_PHAS[_hoops_SCPAR] = _hoops_GHAS++;
						_hoops_SAPAR (_hoops_PPCP, nr, h3ddata, ts, _hoops_GGARR, _hoops_PAIH, _hoops_SCPAR, _hoops_SHAS, _hoops_GPCP, &_hoops_RPCP, _hoops_CRPAR);
					}
					_hoops_AHAS = _hoops_PHAS[_hoops_GSPAR];
					if (_hoops_AHAS < 0) {
						_hoops_AHAS = _hoops_PHAS[_hoops_GSPAR] = _hoops_GHAS++;
						_hoops_SAPAR (_hoops_PPCP, nr, h3ddata, ts, _hoops_GGARR, _hoops_PAIH, _hoops_GSPAR, _hoops_SHAS, _hoops_GPCP, &_hoops_RPCP, _hoops_CRPAR);
					}
					_hoops_ASPAR = _hoops_PHAS[_hoops_RSPAR];
					if (_hoops_ASPAR < 0) {
						_hoops_ASPAR = _hoops_PHAS[_hoops_RSPAR] = _hoops_GHAS++;
						_hoops_SAPAR (_hoops_PPCP, nr, h3ddata, ts, _hoops_GGARR, _hoops_PAIH, _hoops_RSPAR, _hoops_SHAS, _hoops_GPCP, &_hoops_RPCP, _hoops_CRPAR);
					}
				}
				else {
					_hoops_RHAS = _hoops_GHAS++;
					_hoops_SAPAR (_hoops_PPCP, nr, h3ddata, ts, _hoops_GGARR, _hoops_PAIH, _hoops_SCPAR, _hoops_SHAS, _hoops_GPCP, &_hoops_RPCP, _hoops_CRPAR);
					_hoops_AHAS = _hoops_GHAS++;
					_hoops_SAPAR (_hoops_PPCP, nr, h3ddata, ts, _hoops_GGARR, _hoops_PAIH, _hoops_GSPAR, _hoops_SHAS, _hoops_GPCP, &_hoops_RPCP, _hoops_CRPAR);
					_hoops_ASPAR = _hoops_GHAS++;
					_hoops_SAPAR (_hoops_PPCP, nr, h3ddata, ts, _hoops_GGARR, _hoops_PAIH, _hoops_RSPAR, _hoops_SHAS, _hoops_GPCP, &_hoops_RPCP, _hoops_CRPAR);
				}

				if ((j-_hoops_HCPAR)%2 == 0) {
					_hoops_IHPAR[0] = _hoops_RHAS;
					_hoops_IHPAR[1] = _hoops_AHAS;
					_hoops_IHPAR[2] = _hoops_ASPAR;
				}
				else {
					_hoops_IHPAR[0] = _hoops_ASPAR;
					_hoops_IHPAR[1] = _hoops_AHAS;
					_hoops_IHPAR[2] = _hoops_RHAS;
				}

				_hoops_IHPAR+=3;
				_hoops_SHPAR++;
			}
			j+=2;
		}

		_hoops_SCHC = _hoops_IHPAR - _hoops_SGIRR;


		if (_hoops_RRHA) {
			_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
			pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
			if (!pair)
				break;
			ts = (Tristrip const *) pair->geo;
			/* _hoops_AGHP _hoops_IACA _hoops_PSPAR _hoops_RPP _hoops_SIGR */
			if ( _hoops_GGARR && ts->_hoops_GSSH->_hoops_CCHA != null)
				_hoops_GGARR = _hoops_GHPAR(h3ddata,ts);
			if (pair->_hoops_CPAI)
				_hoops_SHAS = &pair->_hoops_CPAI->matrix;
			else
				_hoops_SHAS = null;
			if (_hoops_SHAS && _hoops_PPCP._hoops_HHCP() && _hoops_SHAS->_hoops_APRA == null)
				HI_Validate_Matrix_Adjoint((_hoops_HRPA alter *)_hoops_SHAS);
			_hoops_GPCP = _hoops_CCAI (pair->color, Color_FRONT);
			_hoops_CIPAR = (_hoops_SHAS && BIT(_hoops_SHAS->_hoops_RAGR, _hoops_CASA));

			// _hoops_IGHS _hoops_CAGH _hoops_PAPA _hoops_CGHS, _hoops_HIS _hoops_HRCI _hoops_GII _hoops_CPAP _hoops_CGHS
			if (ts->_hoops_GAHA && ts->_hoops_GAHA->list)
				HD_Queue_Destroy_List (ts->_hoops_GAHA->list, true);

			odl->item.geometry._hoops_IGGI.point_count += ts->total;
			odl->item.geometry._hoops_IGGI._hoops_PHHA += ts->_hoops_PHHA;
			odl->item.geometry._hoops_IGGI.total += ts->total;
		}
		else
			break;
	}

	if (_hoops_PCGS) {
		//_hoops_HGGC _hoops_HS _hoops_IRS _hoops_IGRH _hoops_IIGR _hoops_PIH _hoops_GGR _hoops_RH _hoops_HSHRR, _hoops_HIS _hoops_GGCR _hoops_SCH _hoops_IS _hoops_AIRI _hoops_HIGR
		_hoops_IIPAR = h3ddata->_hoops_GSCR->_hoops_PRAS();
		if (!_hoops_IIPAR)
			status = false;
		if (status)
			status = _hoops_IIPAR->CreateVertexBuffer (h3ddata,
				_hoops_GHAS,
				_hoops_PPCP);
		if (status)
			status = _hoops_IIPAR->CreateIndexBuffer(
				h3ddata,
				H3DPT_TRIANGLELIST,
				_hoops_SHPAR * 3 * stride,
				_hoops_SHPAR);
		if (!status) {
			_hoops_SPPAR(&_hoops_IIPAR, _hoops_RRHA, odl);
			goto _hoops_HPAGR;
		}

		_hoops_IIPAR->LockVertexBuffer(0, 0, &_hoops_HHPAR, 0);
		ASSERT (_hoops_GHAS <= _hoops_PCPS);
		COPY_MEMORY(_hoops_PAIH._hoops_ARHS(), _hoops_GHAS * _hoops_PPCP._hoops_HGHS(), _hoops_HHPAR._hoops_HACGR());
		_hoops_IIPAR->UnlockVertexBuffer();

		_hoops_IIPAR->LockIndexBuffer(0,0,&_hoops_IHPAR,0);
		_hoops_IHPAR._hoops_RSHRR(_hoops_SGIRR, _hoops_SHPAR * 3);
		_hoops_IIPAR->UnlockIndexBuffer();

		if (_hoops_PHPAR) {
			_hoops_PHPAR->UnlockVertexBuffer();
			_hoops_PHPAR->UnlockIndexBuffer();
		}

		// _hoops_ARP _hoops_GH _hoops_PPHS'_hoops_GRI _hoops_IASC _hoops_HPHS
		_hoops_RIPAR++;
		if (_hoops_RSPS) {
			_hoops_IIPAR->_hoops_IAHS = _hoops_RSPS;
			_hoops_CAHS (_hoops_RSPS);
		}
		_hoops_IIPAR->_hoops_SAHS = _hoops_AIPAR - _hoops_PIPAR + 1;
		_hoops_IIPAR->_hoops_GPHS = _hoops_PIPAR;
		if (_hoops_HIPAR > 1) {
			ALLOC_ARRAY(_hoops_IIPAR->_hoops_RPHS, _hoops_IIPAR->_hoops_SAHS, int);
			_hoops_AIGA(_hoops_AHPAR, _hoops_IIPAR->_hoops_SAHS, int, _hoops_IIPAR->_hoops_RPHS);
		}
		else
			_hoops_IIPAR->_hoops_RPHS = null;
		odl->item.geometry.id->AddFirst(_hoops_IIPAR);
	}

  _hoops_HPAGR:
	_hoops_HP(_hoops_PHPAR);

	return status;
}


int _hoops_IRGAR(Tristrip const *ts)
{
	int i = 0;
	int point_count = 0;

	/* _hoops_CGP _hoops_PPSR _hoops_RPR _hoops_HRGR 0, _hoops_HSPAR _hoops_GPHA _hoops_PSPI _hoops_HIGR _hoops_IS _hoops_CACH _hoops_RSH _hoops_AHPH _hoops_RSSA _hoops_IIH *_hoops_CGH* _hoops_SHH */
	if (ts->point_count == 0) {
		if (ts->_hoops_AIHA) {
			for (i = 0; i < ts->total; i++)
				if (point_count < ts->_hoops_AIHA[i])
					point_count = ts->_hoops_AIHA[i];
			point_count++;	//_hoops_PIHA _hoops_HIHA _hoops_IH 0 _hoops_IIHA _hoops_CIHA
		}
		else
			point_count = ts->total;
	}
	else
		point_count = ts->point_count;
	return point_count;
}


void _hoops_CRGAR(
		Net_Rendition const & nr,
		Tristrip const *ts,
		H3D_Display_List_Bin alter *_hoops_RRHA,
		H3D_Vertex_Buffer_Style _hoops_APHA,
		unsigned int alter *_hoops_SCPI,
		int alter *face_count)
{
	H3DData *h3ddata = H3DD(nr->_hoops_SRA);
	int i = 0;
	_hoops_IRHA *pair = null;
	_hoops_HRPA const *matrix = null;
	int _hoops_ISPAR = 0;

	*_hoops_SCPI = 0;
	*face_count = 0;

	switch (_hoops_APHA) {
		case H3D_Shared_Vertices:
			{
				if (!_hoops_RRHA) {
					*face_count = ts->total - (ts->_hoops_PHHA * 2);
					*_hoops_SCPI = _hoops_IRGAR(ts);
				}
				else {
					*face_count = _hoops_RRHA->_hoops_IGGI.total - (_hoops_RRHA->_hoops_IGGI._hoops_PHHA * 2);
					*_hoops_SCPI = _hoops_SRGAR(h3ddata, _hoops_RRHA);
				}
			}
			break;
		case H3D_Partially_Shared_Vertices:
			{
				int total = 0;

				if (_hoops_RRHA) {
					_hoops_RRHA->_hoops_CRHA->ResetCursor();
					pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
					ts = (Tristrip const *) pair->geo;
					if (pair->_hoops_CPAI)
						matrix = &pair->_hoops_CPAI->matrix;
					else
						matrix = null;
				}
				for (;;) {
					*_hoops_SCPI += ts->total;

					if (matrix && BIT(matrix->_hoops_RAGR, _hoops_CASA))
						_hoops_ISPAR = 0x1;
					else
						_hoops_ISPAR = 0;
					for (i = 0; i < ts->_hoops_PHHA ; i++) {
						if (total != 0) {
							total++;
							if ((total & 0x1) != _hoops_ISPAR)
								total++;
						}
						total += ts->lengths[i] + 1;
					}
					if ((total & 0x1) != 0)
						total++;

					if (_hoops_RRHA) {
						_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
						pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
						if (!pair)
							break;
						ts = (Tristrip const *) pair->geo;
						if (pair->_hoops_CPAI)
							matrix = &pair->_hoops_CPAI->matrix;
						else
							matrix = null;
					}
					else
						break;
				}

				*face_count = total - 2;
			}
			break;
		case H3D_Unshared_Vertices:
			{
				if (!_hoops_RRHA)
					*face_count = ts->total - (ts->_hoops_PHHA * 2);
				else
					*face_count = _hoops_RRHA->_hoops_IGGI.total - (_hoops_RRHA->_hoops_IGGI._hoops_PHHA * 2);

				*_hoops_SCPI = 3 * (*face_count);
			}
			break;
		default:
			{
				ASSERT(0);
			}
	}
}


local void _hoops_CSPAR (
		Tristrip const *ts,
		int _hoops_SSPAR,
		int start,
		int end,
		int alter *_hoops_GGHAR,
		int alter *_hoops_RGHAR,
		int const *_hoops_AGHAR)
{
	int _hoops_PGHAR, j, k;
	int _hoops_HGHAR;
	int const *face_indices = ts->face_indices;

	ASSERT (_hoops_AGHAR);

	_hoops_PGHAR = j = start;
	j += 2;
	_hoops_HGHAR = _hoops_SSPAR + (end - j - 1);

	if (face_indices)
		while (j<end && !_hoops_AGHAR[face_indices[j]])
			j++;
	else {
		while (j<end && !_hoops_AGHAR[_hoops_SSPAR]) {
			j++;
			_hoops_SSPAR++;
		}
	}

	if (j < end) {
		/* _hoops_AHIC _hoops_HGPP _hoops_SGS _hoops_SR _hoops_IGHAR _hoops_RH _hoops_APRAR _hoops_SCGR _hoops_SCPH _hoops_PPR _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_PCCP _hoops_PRGI _hoops_PHI _hoops_IIGR _hoops_HIPH */
		if ((j-_hoops_PGHAR) & 0x1) {
			_hoops_SSPAR--;
			j -= 3;
		}
		else
			j -= 2;
		if (face_indices) {
			while (!_hoops_AGHAR[face_indices[end-1]])
				end--;
		}
		else {
			k = 0;
			while (!_hoops_AGHAR[_hoops_HGHAR-k])
				k++;
			end -= k;
		}
	}

	*_hoops_GGHAR = j;
	*_hoops_RGHAR = end;
}


//_hoops_SCPH _hoops_CGGR _hoops_CCA _hoops_CIHA _hoops_SRHR _hoops_PPR _hoops_GCSP _hoops_GIHA
void _hoops_CSSRR(
		Net_Rendition const & nr,
		Tristrip const *ts,
		_hoops_ARPA const *_hoops_GGARR,
		H3D_Display_List_Bin *_hoops_RRHA,
		_hoops_IAPA const *_hoops_CAPA,
		H3DVertexFormat _hoops_PPCP,
		H3D_Vertex_Buffer_Style _hoops_APHA,
		_hoops_HCI *_hoops_RPCP,
		bool _hoops_CISP,
		int _hoops_RASP)
{
	Display_Context alter *dc = (Display_Context alter *) nr->_hoops_SRA;
	H3DData alter *h3ddata = H3DD (dc);
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	H3DVertexBufferCache *_hoops_HACP = null;
	H3DIndexBufferCache *_hoops_RAHC = null;
	H3DVertexBuffer &_hoops_PAIH = h3ddata->_hoops_CP;
	short * _hoops_CHPC = null;
	H3DShader *_hoops_RSR = null;
	_hoops_HRPA const *_hoops_SHAS = null;
	RGB const *_hoops_GPCP = _hoops_CCAI (dc->_hoops_SPA->color, Color_FRONT);
	bool _hoops_PIAS = false;
	bool _hoops_ARSA = false;
	int const *_hoops_CGHAR = dc->_hoops_CGHAR;
	_hoops_IRHA *pair = null;
	bool _hoops_CIPAR = false;
	unsigned int _hoops_SCPI;
	unsigned int _hoops_CPHA;
	short *_hoops_PHAS = null;

	if (!BIT(_hoops_IHCR->flags, _hoops_IGSP))
		_hoops_CGHAR = null;

	if (!h3ddata->_hoops_GSA &&
		nr->_hoops_IHA->_hoops_CHA != nr->_hoops_IHA->_hoops_GIA &&
		ANYBIT(nr->transform_rendition->heuristics, _hoops_RSA))
		_hoops_ARSA = true;

	if (_hoops_RRHA) {
		_hoops_GPPAR (_hoops_RRHA, _hoops_APHA, &_hoops_SCPI, &_hoops_CPHA);
		_hoops_RRHA->_hoops_CRHA->ResetCursor();
		pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
		if (pair) {
			ts = (Tristrip *) pair->geo;
			_hoops_GPCP = _hoops_CCAI (pair->color, Color_FRONT);
			if (pair->_hoops_CPAI)
				_hoops_SHAS = &pair->_hoops_CPAI->matrix;
			else
				_hoops_SHAS = null;
			_hoops_CIPAR = (_hoops_SHAS && BIT(_hoops_SHAS->_hoops_RAGR, _hoops_CASA));
		}
	}
	else {
		if (ts->_hoops_PHHA == 0)
			return;
		else {
			_hoops_CPHA = ts->total;
			_hoops_SCPI = _hoops_IRGAR(ts);
		}
	}
	int *_hoops_SGHAR = ts->face_indices;

	H3D_TRACE(h3ddata, "immediate mode draw_3d_tristrip_im");

	_hoops_GPRH(_hoops_GRHAR)++;

	_hoops_RPIH(h3ddata, _hoops_PPCP, _hoops_HACP);
	_hoops_RCHC(h3ddata, _hoops_HACP);
	_hoops_RAHC = h3ddata->_hoops_ACHC;
	_hoops_PAIH.reset();


	bool _hoops_GIAS = (_hoops_APHA == H3D_Partially_Shared_Vertices);
	bool _hoops_PCGS = false;
	short *_hoops_AAHC = null;
	int _hoops_IGIC = (int)_hoops_HACP->_hoops_GRIC;

	//_hoops_SSCR _hoops_GGSR _hoops_RH _hoops_RRHAR # _hoops_IIGR _hoops_PSPI _hoops_IS _hoops_AAHS (_hoops_GA'_hoops_RA _hoops_HHGC _hoops_IS _hoops_AAHS _hoops_RRI _hoops_HSAR _hoops_HAHH)
	//_hoops_PAGA: _hoops_IPIH _hoops_HAR _hoops_CCCI _hoops_IH "_hoops_SCGI" _hoops_AGIR, _hoops_HIH _hoops_CGH _hoops_HGGC _hoops_IPHR _hoops_RCRAR
	// - _hoops_PS _hoops_RRP _hoops_HPGR _hoops_CHGC _hoops_RH _hoops_RPR
	// - _hoops_PS _hoops_HHS _hoops_HS 3 _hoops_RIR _hoops_CGGR _hoops_IH _hoops_ARHAR _hoops_HIPH
	// - _hoops_PS _hoops_HHS _hoops_HS 3 _hoops_IHH _hoops_IH _hoops_PRHAR _hoops_CGPR _hoops_HRHAR _hoops_GH _hoops_IRS _hoops_CGGR
	int _hoops_IRHAR = _hoops_CPHA + 3*ts->_hoops_PHHA + 3;
	if (_hoops_IRHAR < _hoops_IGIC)
		_hoops_IGIC = _hoops_IRHAR;

	/* _hoops_RASR _hoops_IH _hoops_ASCA */
	// _hoops_HCGA _hoops_CSCS _hoops_RRSP _hoops_PPR _hoops_HGCR _hoops_HRP _hoops_IH _hoops_RH _hoops_CI
	_hoops_CISP &= nr->_hoops_CPP->_hoops_PRH._hoops_HRH;
	int flags = _hoops_IISP(h3ddata, nr, _hoops_APHA, T_FACES, _hoops_CISP, _hoops_RASP, H3DID_USE_FACE_DISPLACEMENT);
	flags |= _hoops_CCSP(nr);

	// _hoops_CAIA _hoops_CRHAR-_hoops_SRHAR _hoops_HHH _hoops_GPIA _hoops_AAP _hoops_IS _hoops_HHPR _hoops_GAHAR.
	if ( ts->_hoops_CARI & _hoops_APIA )
		flags |= H3DID_CIRCLE_MARKER | H3DID_QUAD_MARKER;

	if ( ts->_hoops_CARI & _hoops_RAHAR )
		flags |= H3DID_POLY_CYLINDER;

	_hoops_ISGI const *_hoops_CSGI = dc->_hoops_SPA->modelling_matrix;
	_hoops_SSGI const *_hoops_GGRI = dc->_hoops_SPA->color;

	if (pair && _hoops_GPCP)
		dc->_hoops_SPA->color = pair->color;

	// _hoops_SPAA _hoops_AGSGR _hoops_SCH _hoops_GPP
	_hoops_SSHH(h3ddata, nr, T_FACES, ts, flags, &_hoops_RSR);

	// _hoops_SPAA _hoops_GHAA _hoops_CPS _hoops_AAHAR _hoops_PAHAR _hoops_HII _hoops_HPPA _hoops_GHC
	_hoops_SSSP(h3ddata, nr, _hoops_RSR);

	// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_ASCA _hoops_RSPH _hoops_CHPI, _hoops_AHHR _hoops_GGSR _hoops_GPIA _hoops_HRP _hoops_CR _hoops_SR _hoops_CRHAR-_hoops_SRHAR _hoops_CAPR
	if ( ts->_hoops_CARI & _hoops_APIA )
		_hoops_RSR->_hoops_CCAA( nr, 0, false, false, null);

	// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_ASCA _hoops_HAHAR, _hoops_HGSR _hoops_SAAA _hoops_IH _hoops_AII
	if ( ts->_hoops_CARI & _hoops_RAHAR )
		_hoops_RSR->_hoops_CIPA( nr );

	if (_hoops_SHAS) {
		_hoops_CIPAR = (BIT(_hoops_SHAS->_hoops_RAGR, _hoops_CASA));
		if (_hoops_CIPAR && ANYBIT (_hoops_IHCR->heuristics, _hoops_RSA))
			_hoops_AGSP (h3ddata, _hoops_IHCR, true);  //_hoops_RPP _hoops_IRS _hoops_RSGA _hoops_HRGR _hoops_IAHAR _hoops_IHHH _hoops_ASSA _hoops_GGSR, _hoops_CAHAR _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_ISSC _hoops_RIH
		if (ts->point_count > H3D_Hardware_Transform_Cutoff) {
			_hoops_AGGH(h3ddata, _hoops_SHAS, _hoops_RSR);
			_hoops_PIAS = true;
			_hoops_SHAS = null;
		}
		else {
			if (_hoops_PPCP._hoops_HHCP() && _hoops_SHAS->_hoops_APRA == null)
				HI_Validate_Matrix_Adjoint((_hoops_HRPA alter *)_hoops_SHAS);
		}
	}

	bool _hoops_HSAS = false;
	int i = 0;
	int _hoops_SAHAR = 0;
	int j = 0;
	int _hoops_GPHAR = 0;
	int _hoops_RPHAR = 0;
	int _hoops_CACP = 0;
	int _hoops_CRPAR = -1;				// _hoops_IGI _hoops_IH _hoops_GPIC _hoops_RPIC
	int _hoops_SSPAR = 0;				// _hoops_IGI _hoops_IH _hoops_APHAR
	int _hoops_RHAS = 0;
	int _hoops_GHAS = 0;
	int _hoops_AICA = 0;

	int _hoops_PPHAR = 0;												// _hoops_PGAP _hoops_CRHH _hoops_GGR _hoops_RH _hoops_SCGI _hoops_SR'_hoops_ASAR _hoops_GRP
	int const _hoops_HPHAR = (_hoops_RRHA) ? _hoops_RRHA->_hoops_CRHA->Count() : 1;		// _hoops_APSR _hoops_CCGI _hoops_GGR _hoops_RH _hoops_SCGI


	bool _hoops_IHHS =
		!BIT (nr->transform_rendition->flags, _hoops_CHHS) &&
			BIT (nr->_hoops_IRR->_hoops_SHHS, _hoops_GIHS) &&
			(ANYBIT (nr->transform_rendition->_hoops_APH, Heur_Culling_EXTENT|_hoops_RIHS) ||
				(BIT (nr->transform_rendition->_hoops_APH, Heur_Culling_VIEW_FRUSTUM) &&
					!BIT (nr->transform_rendition->flags, _hoops_AIHS)));

	while (_hoops_PPHAR < _hoops_HPHAR) {
		_hoops_CRPAR = -1;
		_hoops_CACP = -1;
		_hoops_SSPAR = 0;
		_hoops_SGHAR = ts->face_indices;
		j = 0;

		//_hoops_RGAR _hoops_ISPR _hoops_IASC _hoops_IH _hoops_SCGI _hoops_AGIR, _hoops_CR _hoops_GRAA-_hoops_SCGI _hoops_HRGR _hoops_GGRGR-_hoops_IPHAR _hoops_HPGR _hoops_CPHAR _hoops_PAPA
		if (!_hoops_RRHA || !_hoops_IHHS || _hoops_SHAS || _hoops_RSIS(pair->nr, (_hoops_GAHS *)ts)) {
			h3ddata->_hoops_PGARR = _hoops_CAPAR ();
			for (i = 0; i < ts->_hoops_PHHA; i++) {
				_hoops_GPHAR = j;
				if (ts->lengths) 
					_hoops_SAHAR = j + ts->lengths[i];
				else
					_hoops_SAHAR = j + 3;
				if (_hoops_CGHAR)
					_hoops_CSPAR (ts, _hoops_SSPAR, j, _hoops_SAHAR, &j, &_hoops_RPHAR, _hoops_CGHAR);
				else
					_hoops_RPHAR = _hoops_SAHAR;

				_hoops_CRPAR = _hoops_SSPAR + (j - _hoops_GPHAR);		// _hoops_RPP _hoops_SR _hoops_HSGR _hoops_RH _hoops_SRS _hoops_CIAGR, _hoops_RRP _hoops_IS _hoops_HIHA _hoops_IH _hoops_RGR
				_hoops_GPHAR = j;
				if (_hoops_RPHAR > j + 2) {
					while (j < _hoops_RPHAR) {
						bool _hoops_SPHAR = false;
						if (_hoops_PCGS)
						{
							if (_hoops_HSAS)
								_hoops_PCGS = false;
							else if (_hoops_CHPC - _hoops_AAHC >= _hoops_IGIC)
								_hoops_PCGS = false;

							_hoops_HSAS = false;
							if (!_hoops_PCGS) {
								_hoops_HACP->Unlock(_hoops_SHAS);
								_hoops_RAHC->Unlock();
								_hoops_SGSA(h3ddata, nr, h3ddata->_hoops_ACHC, _hoops_CAPA, _hoops_CHPC - _hoops_AAHC, _hoops_CHPC - _hoops_AAHC - 2,
									_hoops_SCAS, H3DPT_TRIANGLESTRIP, _hoops_AICA, _hoops_ARSA);
								_hoops_AICA = 0;
							}
						}
						if (!_hoops_PCGS) {
							_hoops_SPHAR = _hoops_PCGS = true;

							_hoops_HACP->Lock(_hoops_IGIC, &_hoops_PAIH);
							_hoops_RAHC->Lock(_hoops_IGIC, &_hoops_CHPC);

							_hoops_PHAS = _hoops_AIAS(h3ddata, (int) ts->point_count);
							if (_hoops_PHAS)
								SET_MEMORY(_hoops_PHAS, ts->point_count*sizeof(short), -1);
							_hoops_GHAS = 0;

							_hoops_AAHC = _hoops_CHPC;
						}

						int _hoops_GHHAR = 2 - h3ddata->_hoops_RRARR;
						ASSERT(_hoops_GHHAR >= 0);

						if (_hoops_SGHAR) {
							if (j < ts->total - _hoops_GHHAR)
								_hoops_CRPAR = _hoops_SGHAR[j + _hoops_GHHAR];
						}
						else {
							if (j > _hoops_GPHAR + (2 - _hoops_GHHAR) && j < _hoops_RPHAR - _hoops_GHHAR)
								_hoops_CRPAR++;
						}

						// _hoops_CGP _hoops_SR _hoops_HHGP _hoops_IRS _hoops_CGGR, _hoops_PSCR _hoops_SR _hoops_RRP _hoops_IS _hoops_AHIC
						if (_hoops_SPHAR && j != _hoops_GPHAR) {
							if ((j - _hoops_GPHAR) % 2 == 1) {
								j -= 3;
								if (!_hoops_SGHAR)
									_hoops_CRPAR -= 3;
							}
							else {
								j -= 2;
								if (!_hoops_SGHAR)
									_hoops_CRPAR -= 2;
							}
						}

						// _hoops_IGAS _hoops_RH _hoops_GPHA
						if (ts->_hoops_AIHA)
							_hoops_CACP = ts->_hoops_AIHA[j];
						else
							_hoops_CACP++;

						if (_hoops_GIAS)
							_hoops_RHAS = -1;
						else
							_hoops_RHAS = _hoops_PHAS[_hoops_CACP];
						if (_hoops_RHAS < 0) {
							_hoops_RHAS = _hoops_PHAS[_hoops_CACP] = _hoops_GHAS++;
							//_hoops_RHHAR (_hoops_ICRS, _hoops_SCII, _hoops_RRAP, _hoops_GARI, _hoops_ARIA, _hoops_AHHAR, _hoops_PHHAR, _hoops_HHHAR, _hoops_IHHAR, _hoops_CHHAR, _hoops_SHHAR);
							_hoops_SAPAR (_hoops_PPCP, nr, h3ddata, ts, _hoops_GGARR, _hoops_PAIH, _hoops_CACP, null, _hoops_GPCP, _hoops_RPCP, _hoops_CRPAR);
						}
					
						ASSERT (_hoops_RHAS <= _hoops_IGIC);
						*_hoops_CHPC++ = _hoops_RHAS;

						// _hoops_GSCA _hoops_GIHAR _hoops_RIHAR
						// ===========================

						// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_HPGR _hoops_RH _hoops_RSGI _hoops_IIGR _hoops_IRS _hoops_CGGR, _hoops_ISPR _hoops_IS _hoops_CACH _hoops_RPP _hoops_AIHAR _hoops_CHR _hoops_SIGR
						if (j == _hoops_GPHAR && !_hoops_SPHAR) {
							*_hoops_CHPC++ = _hoops_RHAS;
							_hoops_AICA++;
						}

						// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_HPGR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_IRS _hoops_CGGR, _hoops_ISPR _hoops_IS _hoops_CACH _hoops_RPP _hoops_AIHAR _hoops_CHR _hoops_SIGR
						if (j == (_hoops_RPHAR - 1) &&
							((i < ts->_hoops_PHHA - 1) || _hoops_PPHAR < _hoops_HPHAR - 1)) {
							_hoops_AICA+=2;

							// _hoops_PIHAR _hoops_RSIH _hoops_RPP _hoops_PSP _hoops_GC _hoops_IH _hoops_ARHAR _hoops_HIPH (3 _hoops_GIHA) + _hoops_HPGR _hoops_CHGC 3 _hoops_GIHA
							if (_hoops_CHPC + 6 > _hoops_AAHC + _hoops_IGIC) {
								_hoops_HSAS = true;
								break;
							}
							else {
								*_hoops_CHPC++ = _hoops_RHAS;
								_hoops_AICA++;

								// _hoops_RPP _hoops_RGR _hoops_CGGR _hoops_HRGR _hoops_PISC, _hoops_RRP _hoops_IHH _hoops_CIHA _hoops_IS _hoops_IRHH _hoops_SCH _hoops_PRGI
								if ( (_hoops_RPHAR - _hoops_GPHAR) % 2 == 1) {
									*_hoops_CHPC++ = _hoops_RHAS;
									_hoops_AICA++;
								}
							}
						}

						_hoops_SPHAR = false;
						j++;
					}
				}
				if (ts->lengths)
					_hoops_SSPAR += ts->lengths[i] - 2;
				else
					_hoops_SSPAR++;
				j = _hoops_SAHAR;
			}
		}

		if (_hoops_RRHA) {
			bool _hoops_HIHAR = _hoops_CIPAR;

			_hoops_HACP->_hoops_PPIRR(_hoops_SHAS, _hoops_PAIH.length());

			_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
			pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
			if (pair) {
				ts = (Tristrip *) pair->geo;
				/* _hoops_AGHP _hoops_IACA _hoops_PSPAR _hoops_RPP _hoops_SIGR */
				if ( _hoops_GGARR && ts->_hoops_GSSH->_hoops_CCHA != null)
					_hoops_GGARR = _hoops_GHPAR(h3ddata,ts);

				if (pair->_hoops_CPAI)
					_hoops_SHAS = &pair->_hoops_CPAI->matrix;
				else
					_hoops_SHAS = null;
				_hoops_GPCP = _hoops_CCAI (pair->color, Color_FRONT);
				if (_hoops_PCGS && (_hoops_PIAS || (_hoops_SHAS != null && ts->point_count > H3D_Hardware_Transform_Cutoff))) {
					_hoops_HACP->Unlock();
					_hoops_RAHC->Unlock();
					_hoops_PAIH.reset();
					_hoops_SGSA(h3ddata, nr, h3ddata->_hoops_ACHC, _hoops_CAPA, _hoops_CHPC - _hoops_AAHC, _hoops_CHPC - _hoops_AAHC - 2,
						_hoops_SCAS, H3DPT_TRIANGLESTRIP, _hoops_AICA, _hoops_ARSA);
					_hoops_AICA = 0;
					_hoops_PCGS = false;
					_hoops_HSAS = false;
				}
				if (_hoops_PIAS) {
					_hoops_IGGH(h3ddata, _hoops_RSR);
					_hoops_PIAS = false;
				}
				if (_hoops_SHAS) {
					_hoops_CIPAR = BIT(_hoops_SHAS->_hoops_RAGR, _hoops_CASA);
					if (ts->point_count > H3D_Hardware_Transform_Cutoff) {
						_hoops_AGGH(h3ddata, _hoops_SHAS, _hoops_RSR);
						_hoops_PIAS = true;
						_hoops_SHAS = null;
					}
					else {
						if (_hoops_PPCP._hoops_HHCP() && _hoops_SHAS->_hoops_APRA == null)
							HI_Validate_Matrix_Adjoint((_hoops_HRPA alter *)_hoops_SHAS);
					}
				}
				else
					_hoops_CIPAR = false;
				if (_hoops_CIPAR != _hoops_HIHAR && ANYBIT (_hoops_IHCR->heuristics, _hoops_RSA))
					_hoops_AGSP (h3ddata, _hoops_IHCR, _hoops_CIPAR);

				_hoops_PHAS = _hoops_AIAS(h3ddata, (int) ts->point_count);
				if (_hoops_PHAS)
					SET_MEMORY(_hoops_PHAS, ts->point_count*sizeof(short), -1);
			}
		}
		_hoops_PPHAR++;
	}
	if (_hoops_PCGS) {
		_hoops_HACP->Unlock(_hoops_SHAS);
		_hoops_RAHC->Unlock();
		_hoops_SGSA(h3ddata, nr, h3ddata->_hoops_ACHC, _hoops_CAPA, _hoops_CHPC - _hoops_AAHC, _hoops_CHPC - _hoops_AAHC - 2,
			_hoops_SCAS, H3DPT_TRIANGLESTRIP, _hoops_AICA, _hoops_ARSA);
	}
	if (_hoops_PIAS)
		_hoops_IGGH(h3ddata, _hoops_RSR);

	dc->_hoops_SPA->modelling_matrix = _hoops_CSGI;
	dc->_hoops_SPA->color = _hoops_GGRI;

} //_hoops_RSGR _hoops_API '_hoops_PGSA 3d _hoops_CRHH _hoops_RGPS _hoops_IIRGR'

/*
 * _hoops_PGAA
 */
//_hoops_IIHAR _hoops_CCA _hoops_CIHA _hoops_SRHR _hoops_PPR _hoops_GCSP _hoops_GIHA
void _hoops_SSSRR(
		Net_Rendition const & nr,
		Tristrip const *ts,
		_hoops_ARPA const *_hoops_GGARR,
		H3D_Display_List_Bin *_hoops_RRHA,
		_hoops_IAPA const *_hoops_CAPA,
		H3DVertexFormat _hoops_PPCP,
		H3D_Vertex_Buffer_Style _hoops_APHA,
		_hoops_HCI *_hoops_RPCP,
		bool _hoops_CISP,
		int _hoops_RASP)
{
	Display_Context const *dc = nr->_hoops_SRA;
	H3DData alter *h3ddata = H3DD (dc);
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	H3DVertexBufferCache *_hoops_HACP = null;
	H3DVertexBuffer &_hoops_PAIH = h3ddata->_hoops_CP;
	H3DShader *_hoops_RSR = null;
	_hoops_HRPA const *_hoops_SHAS = null;
	RGB const *_hoops_GPCP = _hoops_CCAI (dc->_hoops_SPA->color, Color_FRONT);
	bool _hoops_PIAS = false;
	bool _hoops_ARSA = false;
	bool _hoops_CIPAR = false;
	_hoops_IRHA *pair = null;
	unsigned int _hoops_ASIC = 0;
	int _hoops_APPH = 0;
	int const *_hoops_CGHAR = dc->_hoops_CGHAR;
	short *_hoops_PHAS;

	if (!BIT(_hoops_IHCR->flags, _hoops_IGSP))
		_hoops_CGHAR = null;

	if (!h3ddata->_hoops_GSA &&
		nr->_hoops_IHA->_hoops_CHA != nr->_hoops_IHA->_hoops_GIA &&
		ANYBIT(nr->transform_rendition->heuristics, _hoops_RSA))
		_hoops_ARSA = true;

	if (_hoops_APHA == H3D_Partially_Shared_Vertices)	//_hoops_GHSI _hoops_GCSP _hoops_RGAR _hoops_IIAH _hoops_CCA _hoops_CCGI
		_hoops_APHA = H3D_Unshared_Vertices;

	_hoops_CRGAR(nr, ts, _hoops_RRHA, H3D_Unshared_Vertices, &_hoops_ASIC, &_hoops_APPH);

	if (_hoops_RRHA) {
		_hoops_RRHA->_hoops_CRHA->ResetCursor();
		pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
		ts = (Tristrip *) pair->geo;
		_hoops_GPCP = _hoops_CCAI (pair->color, Color_FRONT);
		if (pair->_hoops_CPAI)
			_hoops_SHAS = &pair->_hoops_CPAI->matrix;
		else
			_hoops_SHAS = null;
		_hoops_CIPAR = (_hoops_SHAS && BIT(_hoops_SHAS->_hoops_RAGR, _hoops_CASA));
		if (_hoops_CIPAR && ANYBIT (_hoops_IHCR->heuristics, _hoops_RSA))
			_hoops_AGSP (h3ddata, _hoops_IHCR, _hoops_CIPAR);
	}

	if (ts->_hoops_PHHA == 0)
		return;

	int *_hoops_SGHAR = ts->face_indices;

	H3D_TRACE(h3ddata, "immediate mode draw_3d_tristrip_im");

	_hoops_RPIH(h3ddata, _hoops_PPCP, _hoops_HACP);

	_hoops_GPRH(_hoops_GRHAR)++;

	// _hoops_GHSGR _hoops_CIHAR
	if (_hoops_RRHA)
		_hoops_ASIC = _hoops_RRHA->_hoops_IGGI.point_count;
	else
		_hoops_ASIC = _hoops_IRGAR(ts);
	_hoops_PHAS = _hoops_AIAS(h3ddata, (int) _hoops_ASIC);

	// _hoops_GHSGR _hoops_SIHAR
	_hoops_RCHC(h3ddata, _hoops_HACP);

	short * _hoops_CHPC = null;

	int _hoops_CRPAR = -1;
	int _hoops_SCPAR, _hoops_GSPAR, _hoops_RSPAR;
	int _hoops_RHAS, _hoops_AHAS, _hoops_ASPAR;

	//_hoops_CGIC _hoops_PHI _hoops_IIGR _hoops_HIPH _hoops_IS _hoops_SGIC _hoops_GGR _hoops_SPR _hoops_PHHR
	int _hoops_IGIC = (int)_hoops_HACP->_hoops_GRIC/3;
	_hoops_IGIC = _hoops_AHIA(_hoops_IGIC, _hoops_APPH);

	Tristrip *_hoops_GCHAR = (Tristrip *) ts;
	bool _hoops_PCGS = false;
	int _hoops_GHAS = 0;		//_hoops_IGI _hoops_IH _hoops_CIHAR
	int _hoops_RGSA = 0;
	if (_hoops_RRHA) {
		_hoops_RRHA->_hoops_CRHA->ResetCursor();
		pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
		if (pair) {
			ts = _hoops_GCHAR = (Tristrip *) pair->geo;
		}
	}


	/* _hoops_RASR _hoops_IH _hoops_RCHAR _hoops_PGSA _hoops_HCPH */
	// _hoops_HCGA _hoops_CSCS _hoops_RRSP _hoops_PPR _hoops_HGCR _hoops_HRP _hoops_IH _hoops_RH _hoops_CI
	_hoops_CISP &= nr->_hoops_CPP->_hoops_PRH._hoops_HRH;
	int flags = _hoops_IISP(h3ddata, nr, _hoops_APHA, T_FACES, _hoops_CISP, _hoops_RASP, H3DID_USE_FACE_DISPLACEMENT);
	flags |= _hoops_CCSP(nr);

	// _hoops_CAIA _hoops_CRHAR-_hoops_SRHAR _hoops_HHH _hoops_GPIA _hoops_HRP _hoops_IS _hoops_HHPR _hoops_GAHAR.
	if ( ts->_hoops_CARI & _hoops_APIA )
		flags |= H3DID_CIRCLE_MARKER | H3DID_QUAD_MARKER;

	if ( ts->_hoops_CARI & _hoops_RAHAR )
		flags |= H3DID_POLY_CYLINDER;

	// _hoops_SPAA _hoops_AGSGR _hoops_SCH _hoops_GPP
	_hoops_SSHH(h3ddata, nr, T_FACES, ts, flags, &_hoops_RSR);

	// _hoops_SPAA _hoops_GHAA _hoops_CPS _hoops_AAHAR _hoops_PAHAR _hoops_HII _hoops_HPPA _hoops_GHC
	_hoops_SSSP(h3ddata, nr, _hoops_RSR);

	// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_ASCA _hoops_RSPH _hoops_CHPI, _hoops_AHHR _hoops_GGSR _hoops_GPIA _hoops_HRP _hoops_CR _hoops_SR _hoops_CRHAR-_hoops_SRHAR _hoops_CAPR
	if ( ts->_hoops_CARI & _hoops_APIA )
		_hoops_RSR->_hoops_CCAA( nr, 0, false, false, null);

	// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_ASCA _hoops_HAHAR, _hoops_HGSR _hoops_SAAA _hoops_IH _hoops_AII
	if ( ts->_hoops_CARI & _hoops_RAHAR )
		_hoops_RSR->_hoops_CIPA( nr );

	if (_hoops_SHAS && _hoops_SHAS->_hoops_APRA == null)
		HI_Validate_Matrix_Adjoint((_hoops_HRPA alter *)_hoops_SHAS);

	if (_hoops_SHAS) {
		_hoops_CIPAR = (BIT(_hoops_SHAS->_hoops_RAGR, _hoops_CASA));
		if (ts->point_count > H3D_Hardware_Transform_Cutoff) {
			_hoops_AGGH(h3ddata, _hoops_SHAS, _hoops_RSR);
			_hoops_PIAS = true;
			_hoops_SHAS = null;
		}
		else {
			if (_hoops_PPCP._hoops_HHCP() && _hoops_SHAS->_hoops_APRA == null)
				HI_Validate_Matrix_Adjoint((_hoops_HRPA alter *)_hoops_SHAS);
		}
	}

	bool _hoops_IHHS =
		!BIT (nr->transform_rendition->flags, _hoops_CHHS) &&
			BIT (nr->_hoops_IRR->_hoops_SHHS, _hoops_GIHS) &&
			(ANYBIT (nr->transform_rendition->_hoops_APH, Heur_Culling_EXTENT|_hoops_RIHS) ||
				(BIT (nr->transform_rendition->_hoops_APH, Heur_Culling_VIEW_FRUSTUM) &&
					!BIT (nr->transform_rendition->flags, _hoops_AIHS)));

	while (_hoops_GCHAR) {
		int index = 0;			//_hoops_CIHA _hoops_CRGR _hoops_GARI->_hoops_ACHAR
		int _hoops_PCHAR = 0;			//_hoops_PGAP _hoops_CGGR _hoops_SR'_hoops_ASAR _hoops_HCHAR _hoops_HPGR
		_hoops_CRPAR = -1;
		_hoops_SGHAR = _hoops_GCHAR->face_indices;

		//_hoops_RGAR _hoops_ISPR _hoops_IASC _hoops_IH _hoops_SCGI _hoops_AGIR, _hoops_CR _hoops_GRAA-_hoops_SCGI _hoops_HRGR _hoops_GGRGR-_hoops_IPHAR _hoops_HPGR _hoops_CPHAR _hoops_PAPA
		if (!_hoops_RRHA || !_hoops_IHHS || _hoops_RSIS(pair->nr, (_hoops_GAHS *)ts)) {
			h3ddata->_hoops_PGARR = _hoops_CAPAR ();
			for (_hoops_PCHAR = 0; _hoops_PCHAR < _hoops_GCHAR->_hoops_PHHA; _hoops_PCHAR++) {
				if (_hoops_PCHAR > 0)
					index += 2;

				int _hoops_ICHAR = 0;				// _hoops_SCGR _hoops_CIHA _hoops_GIAA _hoops_RH _hoops_CGGR
				for (_hoops_ICHAR = 0; _hoops_ICHAR < _hoops_GCHAR->lengths[_hoops_PCHAR] - 2; _hoops_ICHAR ++) {
					if (_hoops_PCGS && _hoops_RGSA == _hoops_IGIC) {
						_hoops_PCGS = false;
						_hoops_HACP->Unlock();
						h3ddata->_hoops_ACHC->Unlock();

						// _hoops_PCSS _hoops_ARR _hoops_IH _hoops_GRR _hoops_ARP _hoops_IIGR _hoops_HPPA _hoops_GHC.
						_hoops_SGSA(h3ddata, nr, h3ddata->_hoops_ACHC, _hoops_CAPA, _hoops_PAIH._hoops_IACGR(), _hoops_RGSA,
							_hoops_SCAS, H3DPT_TRIANGLELIST, 0, _hoops_ARSA);
					}
					if (!_hoops_PCGS) {
						_hoops_PCGS = true;
						_hoops_HACP->Lock(_hoops_IGIC*3, &_hoops_PAIH);
						h3ddata->_hoops_ACHC->Lock(_hoops_IGIC*3, &_hoops_CHPC);

						_hoops_RGSA = 0;
						_hoops_GHAS = 0;
						SET_MEMORY(_hoops_PHAS, _hoops_GCHAR->point_count*sizeof(short), -1);
					}

					if (_hoops_ICHAR == 0 && _hoops_SGHAR)
						_hoops_SGHAR += 2;

					if (_hoops_SGHAR)
						_hoops_CRPAR = *_hoops_SGHAR++;
					else
						_hoops_CRPAR++;

					if ((!_hoops_CGHAR || _hoops_CGHAR[_hoops_CRPAR]))
					{
						//_hoops_PGSA _hoops_GAR _hoops_SCPH _hoops_CPCI
						if (_hoops_ICHAR % 2 == 0) {
							_hoops_SCPAR = _hoops_GCHAR->_hoops_AIHA[index];
							_hoops_GSPAR = _hoops_GCHAR->_hoops_AIHA[index+1];
							_hoops_RSPAR = _hoops_GCHAR->_hoops_AIHA[index+2];
						}
						else {
							_hoops_SCPAR = _hoops_GCHAR->_hoops_AIHA[index+2];
							_hoops_GSPAR = _hoops_GCHAR->_hoops_AIHA[index+1];
							_hoops_RSPAR = _hoops_GCHAR->_hoops_AIHA[index];
						}

						if (_hoops_APHA == H3D_Unshared_Vertices)
							_hoops_RHAS = _hoops_AHAS = _hoops_ASPAR = -1;
						else {
							_hoops_RHAS = _hoops_PHAS[_hoops_SCPAR];
							_hoops_AHAS = _hoops_PHAS[_hoops_GSPAR];
							_hoops_ASPAR = _hoops_PHAS[_hoops_RSPAR];
						}

						_hoops_RSSH alter *params = (_hoops_RSSH alter *)_hoops_GCHAR->_hoops_GSSH ? _hoops_GCHAR->_hoops_GSSH->_hoops_CCHA : 0;
						int width = _hoops_GCHAR->_hoops_GSSH ? _hoops_GCHAR->_hoops_GSSH->_hoops_GSHA : 0;
						if (_hoops_GCHAR->_hoops_GSSH && BIT (_hoops_GCHAR->_hoops_GSSH->_hoops_SCAI, _hoops_HPPAR) && 
								(params[_hoops_SCPAR*width]-params[_hoops_GSPAR*width] > _hoops_PRPAR ||
								 params[_hoops_SCPAR*width]-params[_hoops_RSPAR*width] > _hoops_PRPAR ||
								 params[_hoops_GSPAR*width]-params[_hoops_SCPAR*width] > _hoops_PRPAR ||
								 params[_hoops_GSPAR*width]-params[_hoops_RSPAR*width] > _hoops_PRPAR ||
								 params[_hoops_RSPAR*width]-params[_hoops_SCPAR*width] > _hoops_PRPAR ||
								 params[_hoops_RSPAR*width]-params[_hoops_GSPAR*width] > _hoops_PRPAR)) {
							_hoops_RSSH _hoops_CCHAR[3], _hoops_SCHAR[3], _hoops_GSHAR[3];

							//_hoops_ASAC
							COPY_PARAMETER(&_hoops_GCHAR->_hoops_GSSH->_hoops_CCHA[_hoops_SCPAR*width],_hoops_CCHAR,1); 
							COPY_PARAMETER(&_hoops_GCHAR->_hoops_GSSH->_hoops_CCHA[_hoops_GSPAR*width],_hoops_SCHAR,1); 
							COPY_PARAMETER(&_hoops_GCHAR->_hoops_GSSH->_hoops_CCHA[_hoops_RSPAR*width],_hoops_GSHAR,1); 

							_hoops_HRPAR (&params[_hoops_SCPAR*width], &params[_hoops_GSPAR*width], &params[_hoops_RSPAR*width]);

							_hoops_SAPAR (_hoops_PPCP, nr, h3ddata, _hoops_GCHAR, _hoops_GGARR, _hoops_PAIH, _hoops_SCPAR, _hoops_SHAS, _hoops_GPCP, _hoops_RPCP, _hoops_CRPAR);
							_hoops_SAPAR (_hoops_PPCP, nr, h3ddata, _hoops_GCHAR, _hoops_GGARR, _hoops_PAIH, _hoops_GSPAR, _hoops_SHAS, _hoops_GPCP, _hoops_RPCP, _hoops_CRPAR);
							_hoops_SAPAR (_hoops_PPCP, nr, h3ddata, _hoops_GCHAR, _hoops_GGARR, _hoops_PAIH, _hoops_RSPAR, _hoops_SHAS, _hoops_GPCP, _hoops_RPCP, _hoops_CRPAR);

							_hoops_RHAS = _hoops_GHAS++;
							_hoops_AHAS = _hoops_GHAS++;
							_hoops_ASPAR = _hoops_GHAS++;
							//_hoops_PHIH
							COPY_PARAMETER(_hoops_CCHAR,&_hoops_GCHAR->_hoops_GSSH->_hoops_CCHA[_hoops_SCPAR*width],1); 
							COPY_PARAMETER(_hoops_SCHAR,&_hoops_GCHAR->_hoops_GSSH->_hoops_CCHA[_hoops_GSPAR*width],1); 
							COPY_PARAMETER(_hoops_GSHAR,&_hoops_GCHAR->_hoops_GSSH->_hoops_CCHA[_hoops_RSPAR*width],1); 
						}
						else {
							if (_hoops_RHAS < 0) {
								//_hoops_PSP _hoops_SCGH _hoops_PPSR _hoops_GSGI
								_hoops_RHAS = _hoops_PHAS[_hoops_SCPAR] = _hoops_GHAS++;
								_hoops_SAPAR (_hoops_PPCP, nr, h3ddata, _hoops_GCHAR, _hoops_GGARR, _hoops_PAIH, _hoops_SCPAR, _hoops_SHAS, _hoops_GPCP, _hoops_RPCP, _hoops_CRPAR);
							}
							if (_hoops_AHAS < 0) {
								//_hoops_PSP _hoops_SCGH _hoops_PPSR _hoops_GSGI
								_hoops_AHAS = _hoops_PHAS[_hoops_GSPAR] = _hoops_GHAS++;
								_hoops_SAPAR (_hoops_PPCP, nr, h3ddata, _hoops_GCHAR, _hoops_GGARR, _hoops_PAIH, _hoops_GSPAR, _hoops_SHAS, _hoops_GPCP, _hoops_RPCP, _hoops_CRPAR);
							}
							if (_hoops_ASPAR < 0) {
								//_hoops_PSP _hoops_SCGH _hoops_PPSR _hoops_GSGI
								_hoops_ASPAR = _hoops_PHAS[_hoops_RSPAR] = _hoops_GHAS++;
								_hoops_SAPAR (_hoops_PPCP, nr, h3ddata, _hoops_GCHAR, _hoops_GGARR, _hoops_PAIH, _hoops_RSPAR, _hoops_SHAS, _hoops_GPCP, _hoops_RPCP, _hoops_CRPAR);
							}
						}



						if (!_hoops_CIPAR) {
							*_hoops_CHPC++ = _hoops_RHAS;
							*_hoops_CHPC++ = _hoops_AHAS;
							*_hoops_CHPC++ = _hoops_ASPAR;
						}
						else {
							*_hoops_CHPC++ = _hoops_RHAS;
							*_hoops_CHPC++ = _hoops_ASPAR;
							*_hoops_CHPC++ = _hoops_AHAS;
						}
						_hoops_RGSA++;
					}
					index++;

				}
			}
		}

		_hoops_GCHAR = null;
		if (_hoops_RRHA) {
			bool _hoops_HIHAR = _hoops_CIPAR;

			_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
			pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
			if (pair) {
				if (pair->_hoops_CPAI)
					_hoops_SHAS = &pair->_hoops_CPAI->matrix;
				else
					_hoops_SHAS = null;
				_hoops_GPCP = _hoops_CCAI (pair->color, Color_FRONT);
				_hoops_GCHAR = (Tristrip *) pair->geo;
				/* _hoops_AGHP _hoops_IACA _hoops_PSPAR _hoops_RPP _hoops_SIGR */
				if ( _hoops_GGARR && _hoops_GCHAR->_hoops_GSSH->_hoops_CCHA != null)
					_hoops_GGARR = _hoops_GHPAR(h3ddata, _hoops_GCHAR);

				if (_hoops_PCGS && (_hoops_PIAS || (_hoops_SHAS != null && ts->point_count > H3D_Hardware_Transform_Cutoff))) {
					_hoops_HACP->Unlock();
					h3ddata->_hoops_ACHC->Unlock();
					_hoops_SGSA(h3ddata, nr, h3ddata->_hoops_ACHC, _hoops_CAPA, _hoops_PAIH._hoops_IACGR(), _hoops_RGSA,
						_hoops_SCAS, H3DPT_TRIANGLELIST, 0, _hoops_ARSA);
					_hoops_PCGS = false;
				}
				if (_hoops_PIAS) {
					_hoops_IGGH(h3ddata, _hoops_RSR);
					_hoops_PIAS = false;
				}
				if (_hoops_SHAS) {
					_hoops_CIPAR = BIT(_hoops_SHAS->_hoops_RAGR, _hoops_CASA);
					if (ts->point_count > H3D_Hardware_Transform_Cutoff) {
						_hoops_AGGH(h3ddata, _hoops_SHAS, _hoops_RSR);
						_hoops_PIAS = true;
						_hoops_SHAS = null;
					}
					else {
						if (_hoops_PPCP._hoops_HHCP() && _hoops_SHAS->_hoops_APRA == null)
							HI_Validate_Matrix_Adjoint((_hoops_HRPA alter *)_hoops_SHAS);
					}
				}
				else
					_hoops_CIPAR = false;
				if (_hoops_CIPAR != _hoops_HIHAR && ANYBIT (_hoops_IHCR->heuristics, _hoops_RSA))
					_hoops_AGSP (h3ddata, _hoops_IHCR, _hoops_CIPAR);
				SET_MEMORY(_hoops_PHAS, _hoops_GCHAR->point_count*sizeof(short), -1);
			}
		}
	}

	if (_hoops_PCGS) {
		_hoops_PCGS = false;
		_hoops_HACP->Unlock();
		h3ddata->_hoops_ACHC->Unlock();

		// _hoops_PCSS _hoops_ARR _hoops_IH _hoops_GRR _hoops_ARP _hoops_IIGR _hoops_HPPA _hoops_GHC.
		_hoops_SGSA(h3ddata, nr, h3ddata->_hoops_ACHC, _hoops_CAPA, _hoops_PAIH._hoops_IACGR(), _hoops_RGSA,
			_hoops_SCAS, H3DPT_TRIANGLELIST, 0, _hoops_ARSA);
	}
	if (_hoops_PIAS) {
		_hoops_IGGH(h3ddata, _hoops_RSR);
		_hoops_PIAS = false;
	}

} //_hoops_RSGR _hoops_API '_hoops_PGSA 3d _hoops_CRHH _hoops_RGPS _hoops_CPCI'


bool _hoops_HGRI(
		Net_Rendition const & nr,
		unsigned Integer32 _hoops_SRHA,
		bool _hoops_CISP)
{
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;

	if (_hoops_CISP &&
		!BIT (_hoops_SRHA, DL_DO_NOT_DEFER) &&
		!BIT (_hoops_SRHA, DL_3D_TRANSPARENCY) &&
		nr->_hoops_CPP->_hoops_PRH._hoops_SRI != _hoops_PIII &&
		nr->_hoops_CPP->_hoops_PRH.style == Transparency_STYLE_BLENDING) {
		_hoops_HHA const &matr = _hoops_SIGA->_hoops_CHA;
		if (matr->_hoops_IRIR < 1.0f ||
			(matr->_hoops_SCA && matr->_hoops_SCA->_hoops_HGA == 0 && !BIT(matr->_hoops_SCA->texture->_hoops_SCR, _hoops_PGA)))
			return true;
		return true;
	}
	//_hoops_RPP (_hoops_RSHAR->_hoops_ASHAR != _hoops_RSHAR->_hoops_PSHAR &&
	//	(_hoops_RSHAR->_hoops_ASHAR->_hoops_HSHAR || _hoops_RSHAR->_hoops_PSHAR->_hoops_HSHAR))
	//	_hoops_ASRC _hoops_IHPR;
	return false;
}

_hoops_ARPA *_hoops_GHPAR( H3DData *h3ddata, Tristrip const *ts )
{
	_hoops_ARPA *_hoops_GGARR;
	Vector *_hoops_AGARR;

	_hoops_SSRRR(h3ddata, ts->point_count);
	ZERO_ARRAY (h3ddata->_hoops_GGARR, ts->point_count, _hoops_ARPA);
	ZERO_ARRAY (h3ddata->_hoops_AGARR, ts->point_count, Vector);
	_hoops_GGARR = h3ddata->_hoops_GGARR;
	_hoops_AGARR = h3ddata->_hoops_AGARR;

	_hoops_RRCC const *params = ts->_hoops_GSSH;
	int const param_width = params->_hoops_GSHA;
	float const *_hoops_IICP = params->_hoops_CCHA;

	// _hoops_HSRR _hoops_GRR _hoops_CGGR
	int const *vi = ts->_hoops_AIHA;
	for ( int s = 0; s != ts->_hoops_PHHA; ++s )
	{
		// _hoops_GCIH _hoops_SRS _hoops_SCPH
		int _hoops_HSPI;
		int _hoops_ISPI = *vi++;
		int _hoops_CSPI = *vi++;

		// _hoops_HSRR _hoops_GRR _hoops_SCPH
		const int _hoops_ISHAR = ts->lengths[s] - 2;
		for ( int t = 0; t != _hoops_ISHAR; ++t )
		{
			// _hoops_CSHAR _hoops_SCPH
			_hoops_HSPI = _hoops_ISPI;
			_hoops_ISPI = _hoops_CSPI;
			_hoops_CSPI = *vi++;

			// _hoops_SSHAR _hoops_RSSA
			const Point _hoops_GGIAR = ts->points[_hoops_HSPI];
			const Point p1 = ts->points[_hoops_ISPI];
			const Point p2 = ts->points[_hoops_CSPI];

			// _hoops_CHSR _hoops_GRPAR
			const float* _hoops_RGIAR = _hoops_IICP + _hoops_HSPI * param_width;
			const float* _hoops_AGIAR = _hoops_IICP + _hoops_ISPI * param_width;
			const float* _hoops_PGIAR = _hoops_IICP + _hoops_CSPI * param_width;

			// _hoops_SSSA _hoops_AHC _hoops_HGIAR _hoops_IGIAR _hoops_SPPR 
			Vector _hoops_CGIAR = p1 - _hoops_GGIAR;
			Vector _hoops_SGIAR = p2 - _hoops_GGIAR;

			// _hoops_CHSR _hoops_CARP _hoops_HGIAR
			float _hoops_GRIAR = _hoops_AGIAR[0] - _hoops_RGIAR[0];
			float _hoops_RRIAR = _hoops_AGIAR[1] - _hoops_RGIAR[1];
			float _hoops_ARIAR = _hoops_PGIAR[0] - _hoops_RGIAR[0];
			float _hoops_PRIAR = _hoops_PGIAR[1] - _hoops_RGIAR[1];

			// _hoops_CHSR _hoops_PIRAR
			float d = (_hoops_GRIAR * _hoops_PRIAR - _hoops_ARIAR * _hoops_RRIAR);
			if (d != 0.0) {
				float _hoops_HRIAR = 1.0f / d;
				Vector _hoops_IRIAR = Vector(_hoops_PRIAR * _hoops_CGIAR.x - _hoops_RRIAR * _hoops_SGIAR.x, 
								   _hoops_PRIAR * _hoops_CGIAR.y - _hoops_RRIAR * _hoops_SGIAR.y,
								   _hoops_PRIAR * _hoops_CGIAR.z - _hoops_RRIAR * _hoops_SGIAR.z) * _hoops_HRIAR;
				Vector _hoops_CRIAR = Vector(_hoops_GRIAR * _hoops_SGIAR.x - _hoops_ARIAR * _hoops_CGIAR.x, 
								   _hoops_GRIAR * _hoops_SGIAR.y - _hoops_ARIAR * _hoops_CGIAR.y,
								   _hoops_GRIAR * _hoops_SGIAR.z - _hoops_ARIAR * _hoops_CGIAR.z) * _hoops_HRIAR;

				// _hoops_GAGP _hoops_ARIA
				_hoops_GGARR[_hoops_HSPI].a += _hoops_IRIAR.x;
				_hoops_GGARR[_hoops_HSPI].b += _hoops_IRIAR.y;
				_hoops_GGARR[_hoops_HSPI].c += _hoops_IRIAR.z;
						   
				_hoops_GGARR[_hoops_ISPI].a += _hoops_IRIAR.x;
				_hoops_GGARR[_hoops_ISPI].b += _hoops_IRIAR.y;
				_hoops_GGARR[_hoops_ISPI].c += _hoops_IRIAR.z;
						   
				_hoops_GGARR[_hoops_CSPI].a += _hoops_IRIAR.x;
				_hoops_GGARR[_hoops_CSPI].b += _hoops_IRIAR.y;
				_hoops_GGARR[_hoops_CSPI].c += _hoops_IRIAR.z;

				// _hoops_CHSR _hoops_SRIAR
				_hoops_AGARR[_hoops_HSPI] += _hoops_CRIAR;
				_hoops_AGARR[_hoops_ISPI] += _hoops_CRIAR;
				_hoops_AGARR[_hoops_CSPI] += _hoops_CRIAR;
			}
		}
	}

	// _hoops_AHGA _hoops_GPHA _hoops_ARIA
	for ( int i = 0; i != ts->point_count; ++i )
	{
		// _hoops_GAIAR _hoops_IACA
		Vector t(_hoops_GGARR[i]);
		
		// _hoops_CHSR _hoops_GSSR
		Vector n;
		if ( ts->_hoops_ICHA )
			n = ts->_hoops_ICHA[i];
		else
			n = Vector(0, 0, 1);

		// _hoops_RAIAR
		t = (t - n * n._hoops_SSRP(t));
		t._hoops_AAIAR();

		// _hoops_SAH _hoops_IACA
		_hoops_GGARR[i].a = t.x;
		_hoops_GGARR[i].b = t.y;
		_hoops_GGARR[i].c = t.z;

		// _hoops_CHSR _hoops_RSSP - _hoops_HAS._hoops_IAS. _hoops_RHAP _hoops_PAIAR _hoops_HAIAR _hoops_PSSP _hoops_IAIAR _hoops_SPR.
		Vector _hoops_CAIAR = n._hoops_SAIAR(t);
		_hoops_GGARR[i].d = _hoops_CAIAR._hoops_SSRP(_hoops_AGARR[i]) < 0.0f ? -1.0f : 1.0f;
	}

	// _hoops_AP
	return _hoops_GGARR;
}

/*
 * _hoops_PGAA
 */
void _hoops_RRRI (
		Net_Rendition const &		nr,
		Tristrip const *			ts,
		H3D_Display_List_Bin *		_hoops_RRHA)
{
	Display_Context const *		dc = nr->_hoops_SRA;
	H3DData alter *				h3ddata = H3DD (dc);
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	_hoops_HHA const &	matr = _hoops_SIGA->_hoops_CHA;
	_hoops_HHA const &	_hoops_SHA = _hoops_SIGA->_hoops_GIA;
	H3DShader *					_hoops_RSR;
	int							i = 0, j, len;
	_hoops_IAPA const *	_hoops_CAPA = null;
	int 						_hoops_SRRS = H3DID_USE_FACE_DISPLACEMENT;
	int 						face_count = 0;
	unsigned int				_hoops_SCPI = 0;
	int							point_count = 0;
	unsigned int				_hoops_SRHA = 0;
	_hoops_IRHA *				pair = null;
	_hoops_HRPA const *			_hoops_SHAS = null;
	RGB const *					_hoops_GPCP = _hoops_CCAI (dc->_hoops_SPA->color, Color_FRONT);
	int 						_hoops_RASP = 0;
	int 						_hoops_GPIAR = 0;
	_hoops_GACR alter *		dl = null;
	H3D_Display_List alter *	odl = null;
	bool						_hoops_IRRS = false;
	Tristrip alter *			_hoops_RPIAR = (Tristrip alter *)ts;
	H3DIndexedBufferObject *	_hoops_IIPAR = null;
	H3DVertexBufferCache *		_hoops_IRPRR = null;
	bool 						_hoops_IAHC = false;
	bool 						_hoops_CIPAR = false;
	H3DCULL						_hoops_IRSA, _hoops_CRSA, _hoops_PRSA;
	bool						_hoops_ARSA;
	H3D_Vertex_Buffer_Style		_hoops_APHA = H3D_Invalid;
	bool						_hoops_CRRS;
	bool						_hoops_AAPS = false;
	int							_hoops_PIHS = 0;
	int	*						_hoops_AHPAR = null;
	int							_hoops_HIPAR = 1;
	int							_hoops_AIPAR = 0;	//_hoops_GRHP _hoops_IHGC _hoops_IIGR _hoops_PGAP _hoops_CRHH _hoops_SR'_hoops_ASAR _hoops_IPIH _hoops_ASCA
	int							_hoops_PIPAR = 0;	//_hoops_GRHP _hoops_IHGC _hoops_IIGR _hoops_PGAP _hoops_CRHH _hoops_HRGR _hoops_HPGR _hoops_RSGI _hoops_IIGR _hoops_CIHA _hoops_SRHR
	bool 						_hoops_CISP;
	bool						_hoops_IHHS;
	bool						_hoops_APIAR = (matr->texture[_hoops_IIA] || (matr->_hoops_SCA && BIT(matr->_hoops_SCA->texture->_hoops_SCR, _hoops_GSR))) != 0;
	_hoops_ARPA *						_hoops_GGARR = null;


	_hoops_CISP = BIT (nr->_hoops_PSGI, T_FACES);

	if (!ts) {
		pair = _hoops_RRHA->_hoops_CRHA->PeekFirst();
		ts = (Tristrip *)pair->geo;
		if (!ts)
			return;
	}

	if (!h3ddata->_hoops_GSA) {
		_hoops_IAHC = _hoops_HGRI (nr, ts->_hoops_SRHA, _hoops_CISP);
	}

	if (_hoops_SIGA->pattern == FP_USER_DEFINED) {
		if (_hoops_SIGA->_hoops_PGPH != null && _hoops_SIGA->_hoops_PGPH->stipple)
			_hoops_RASP = _hoops_SIGA->_hoops_PGPH->stipple;
		else if (_hoops_SIGA->_hoops_PGPH != null &&
			_hoops_SIGA->_hoops_PGPH->height <= 32 && _hoops_SIGA->_hoops_PGPH->width <= 32 &&
			_hoops_RIII(_hoops_SIGA->_hoops_PGPH->width) == _hoops_SIGA->_hoops_PGPH->width &&
			_hoops_RIII(_hoops_SIGA->_hoops_PGPH->height) == _hoops_SIGA->_hoops_PGPH->height)
			_hoops_GPIAR = 1;
		else
			_hoops_IAHC = true;
	}

	if (!_hoops_HPCA(nr, _hoops_CAPA)) {
		// _hoops_PPIAR _hoops_AHPH _hoops_HPPA _hoops_GHC _hoops_IS _hoops_RGHH
		_hoops_IAHC = true;
	}


	if (_hoops_IAHC && !h3ddata->_hoops_GSA) {
		if (h3ddata->_hoops_ISCI)
			h3ddata->_hoops_CIGI->mask &= ~_hoops_GCGI;

		if (BIT(ts->_hoops_SRHA, DL_DO_NOT_RECOMPILE)) {
			/* _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_AIRI _hoops_HIGR _hoops_RGAR, _hoops_SIHH _hoops_RH _hoops_PPPS _hoops_SIHC _hoops_GGR _hoops_AGR _hoops_IS _hoops_CAH */
			Tristrip alter *_hoops_RPIAR = (Tristrip alter *) ts;
			_hoops_GACR alter *dl;
			H3D_Display_List alter *odl=0;
			bool _hoops_RACR = false;

			_hoops_RACR = _hoops_AACR(nr, &_hoops_RPIAR->_hoops_GAHA, &dl, &odl, H3D_DL_GEOMETRY);
			HD_Queue_Destroy_List (odl, true);
		}
		else {
			HD_Std_3D_Tristrip(nr,ts);
		}
		return;
	}

	if (_hoops_RRHA) {
		_hoops_RRHA->_hoops_CRHA->ResetCursor();
		pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
		ts = (Tristrip const *) pair->geo;
		if (_hoops_RRHA->odl) {
			if (pair->_hoops_CPAI)
				_hoops_SHAS = &pair->_hoops_CPAI->matrix;
			else
				_hoops_SHAS = null;
			if (_hoops_SHAS && (ts->_hoops_ICHA||ts->_hoops_PRHH) && _hoops_SHAS->_hoops_APRA == null)
				HI_Validate_Matrix_Adjoint((_hoops_HRPA alter *)_hoops_SHAS);
		}
		_hoops_GPCP = _hoops_CCAI (pair->color, Color_FRONT);
	}

	_hoops_APHA = _hoops_HRGAR (h3ddata, ts, _hoops_SIGA, _hoops_RRHA, &_hoops_SRHA);
	if (_hoops_APHA == H3D_Partially_Shared_Vertices)
		_hoops_SRRS |= H3DID_FLAT_SHADING;

	// _hoops_HPIAR _hoops_CPAP _hoops_IH _hoops_CAGH _hoops_PAPA _hoops_AIRI _hoops_CPCI
	if (h3ddata->_hoops_ISCI > 0)
	{
		bool _hoops_HIRS = false;

		if (BIT(_hoops_SRHA, DL_DO_NOT_RECOMPILE)) {
			bool _hoops_RACR = false;
			_hoops_RACR = _hoops_AACR(nr, &_hoops_RPIAR->_hoops_GAHA, &dl, &odl, H3D_DL_GEOMETRY);
			HD_Queue_Destroy_List (odl, true);
			return;
		}
		if (ANYBIT (h3ddata->_hoops_CIGI->_hoops_RRSI, _hoops_PGRI))
			return;  //_hoops_CIRS _hoops_SIRS _hoops_IS _hoops_CRHR _hoops_GCRS _hoops_RCRS _hoops_CPAP

		if (ANYBIT (_hoops_SRHA, DL_SUPPRESS_SEGMENT_DISPLAY_LISTS))
			_hoops_HIRS = true;  //_hoops_HHHA _hoops_IPPS
		else if (!h3ddata->_hoops_CSC->_hoops_RAIH && _hoops_CISP)
			_hoops_HIRS = true;  //_hoops_AGSI _hoops_IHSP
		else if (h3ddata->_hoops_CHSP.mode || h3ddata->_hoops_PI.mode)
			_hoops_HIRS = true;  //_hoops_RGCH _hoops_PAH _hoops_SGH _hoops_HIH _hoops_HAR _hoops_CAHP _hoops_HCGI'_hoops_GRI
		//_hoops_SHS _hoops_RPP (_hoops_GARI->_hoops_CPPS && _hoops_IRRC (_hoops_GARI->_hoops_HGCI, _hoops_SPPS))
		//	_hoops_GHPS = _hoops_IHPR;  //_hoops_AGCR _hoops_GPHA _hoops_RHPS _hoops_CHR _hoops_AHPS _hoops_IS _hoops_AGRP _hoops_SIHH _hoops_PHPS
		else if (nr->_hoops_IRR->_hoops_GAHA == Display_List_GEOMETRY &&
			!BIT (_hoops_SRHA, DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS))
			_hoops_HIRS = true;  //_hoops_HHPS _hoops_CPAP _hoops_AIRI _hoops_CPCI

		if (!_hoops_HIRS) {
			ASSERT (ts);

			Tristrip alter *_hoops_IPIAR = (Tristrip alter *)ts;
			_hoops_IRHA *pair;
			bool _hoops_IIRS = (dc->_hoops_SPA->color &&
				ANYBIT (dc->_hoops_SPA->color->_hoops_GHA, Color_FACE));

			if (!ts->_hoops_PAGI &&
				!ts->_hoops_PCHA &&
				!_hoops_IIRS &&
				nr->_hoops_IHA->_hoops_CPA != h3ddata->_hoops_CIGI->nr->_hoops_IHA->_hoops_CPA)
				h3ddata->_hoops_CIGI->mask &= ~_hoops_PGRI;

			if (BIT(ts->_hoops_SRHA, DL_TEMPORARY_DATA))
				HD_Isolate_Tristrip_Data (dc, ts);

			if (ts->_hoops_GAHA) {
				_hoops_GACR alter *dl;
				H3D_Display_List alter *odl=0;
				bool _hoops_RACR;
				_hoops_RACR = _hoops_AACR(nr, &_hoops_IPIAR->_hoops_GAHA, &dl, &odl, H3D_DL_GEOMETRY);
				HD_Queue_Destroy_List (odl, true);
				_hoops_HPRH(_hoops_IPIAR->_hoops_GAHA);
				_hoops_IPIAR->_hoops_GAHA = null;
			}

			// _hoops_RGPA _hoops_CPAP _hoops_IS _hoops_HIGR
			_hoops_IPIAR->_hoops_CARI |= _hoops_SARI;

			pair = POOL_NEW(dc->memory_pool, _hoops_IRHA)(nr, ts, dc->_hoops_SPA->modelling_matrix, dc->_hoops_SPA->color);

			if (!h3ddata->_hoops_CIGI->_hoops_RCGI)
				h3ddata->_hoops_CIGI->_hoops_RCGI = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);

			h3ddata->_hoops_CIGI->_hoops_RCGI->AddFirst(pair);
			return;
	    }
		_hoops_SHAS = null;
		h3ddata->_hoops_CIGI->mask &= ~_hoops_PGRI;
		if (h3ddata->_hoops_CIGI->_hoops_IHGI)
			return;

		bool _hoops_IHHS =
			!BIT (nr->transform_rendition->flags, _hoops_CHHS) &&
				BIT (nr->_hoops_IRR->_hoops_SHHS, _hoops_GIHS) &&
				(ANYBIT (nr->transform_rendition->_hoops_APH, Heur_Culling_EXTENT|_hoops_RIHS) ||
					(BIT (nr->transform_rendition->_hoops_APH, Heur_Culling_VIEW_FRUSTUM) &&
						!BIT (nr->transform_rendition->flags, _hoops_AIHS)));

		if (_hoops_IHHS && !_hoops_RSIS (nr, (_hoops_GAHS *)ts))
			return;
	}

	h3ddata->_hoops_AIC = (
		nr->_hoops_IRR->_hoops_SRI == _hoops_GAI && 
		BIT (nr->transform_rendition->heuristics, _hoops_IRI) &&
		!BIT (ts->_hoops_SRHA, DL_SHADOW_TRISTRIP));

	if (nr->_hoops_IRR->_hoops_GAHA) {
		if (BIT (ts->_hoops_SRHA, DL_DO_NOT_RECOMPILE))
			_hoops_CRRS = true;
		else if (nr->_hoops_IRR->_hoops_GAHA == Display_List_GEOMETRY)
			_hoops_CRRS = !BIT(_hoops_SRHA, DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS);
		else if (nr->_hoops_IRR->_hoops_GAHA == Display_List_SEGMENT) {
			if (_hoops_RRHA)
				_hoops_CRRS = !BIT(_hoops_RRHA->flags, DL_SUPPRESS_SEGMENT_DISPLAY_LISTS);
			else
				_hoops_CRRS = !BIT(ts->_hoops_SRHA, DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS);
		}
		else
			_hoops_CRRS = false;
	}
	else
		_hoops_CRRS = false;

	if (BIT(_hoops_SRHA, DL_DO_NOT_RECOMPILE))
		_hoops_CRRS = true;
	if (_hoops_CRRS && !_hoops_HHCA(ts, _hoops_RRHA)) {
		/* _hoops_CPPP _hoops_RGR _hoops_RRGR _hoops_CGPR _hoops_SR _hoops_AIAH _hoops_HS _hoops_IRS _hoops_CPIAR _hoops_AIRI _hoops_HIGR.
		 * _hoops_SPIAR _hoops_IIGR _hoops_RH _hoops_HSPR _hoops_SSSC _hoops_CGH _hoops_CRHR _hoops_AIRI _hoops_HIGR
		 * _hoops_HSSI, _hoops_HIH _hoops_HAR _hoops_SSCC _hoops_AIRI _hoops_HIGR _hoops_SGH. */
		if (!_hoops_HCRI(h3ddata, 0) ||
			h3ddata->_hoops_PI.mode ||
			h3ddata->_hoops_CHSP.mode)
			_hoops_CRRS = false;

		if (!BIT(_hoops_SRHA, DL_DO_NOT_RECOMPILE))
			_hoops_CRGAR(nr, ts, _hoops_RRHA, _hoops_APHA, &_hoops_SCPI, &face_count);

		// _hoops_GHIAR _hoops_RH _hoops_AIRI _hoops_HIGR _hoops_AASC _hoops_CGPR _hoops_GRP _hoops_IRCI
		if (nr->_hoops_IRR->_hoops_GAHA != Display_List_SEGMENT &&
			(_hoops_SCPI < H3D_Display_List_MINIMUM ||
			 face_count < H3D_Display_List_MINIMUM))
			_hoops_CRRS = false;
	}


	// _hoops_ARGH _hoops_IH _hoops_PGCR-_hoops_RPSA _hoops_APSA
	_hoops_ARSA = false;
	_hoops_IRSA = H3DCULL_NONE;
	_hoops_CRSA = H3DCULL_NONE;
	_hoops_PRSA = h3ddata->_hoops_CSC->_hoops_HRSA;
	if (!h3ddata->_hoops_GSA &&
		matr != _hoops_SHA &&
		ANYBIT(nr->transform_rendition->heuristics, _hoops_RSA))
	{
		_hoops_ARSA = true;

		if (!BIT (nr->transform_rendition->matrix->data.flags, _hoops_HASA))
			HI_Validate_Matrix_NEG3X3((_hoops_HRPA alter *)&nr->transform_rendition->matrix->data);

		bool _hoops_IASA = BIT (nr->transform_rendition->matrix->data._hoops_RAGR, _hoops_CASA);

		if ((_hoops_IASA && BIT(nr->transform_rendition->heuristics,_hoops_SASA)) ||
			(!_hoops_IASA && BIT(nr->transform_rendition->heuristics,_hoops_GPSA)))
		{
			_hoops_IRSA = H3DCULL_CCW;
			_hoops_CRSA = H3DCULL_CW;
		}
		else {
			_hoops_IRSA = H3DCULL_CW;
			_hoops_CRSA = H3DCULL_CCW;
		}
	}


	//_hoops_PRPP _hoops_SIAC _hoops_ACPP _hoops_HIS _hoops_SGS _hoops_GCAC _hoops_HCPH _hoops_CHR _hoops_RCAC _hoops_IS _hoops_SSS
	H3D_TRACE(h3ddata, "draw_3d_tristrip");

	/* _hoops_RAP _hoops_GH _hoops_RH _hoops_AI */
	_hoops_HCI _hoops_RPCP;
	ZERO_STRUCT (&_hoops_RPCP, _hoops_HCI);
	_hoops_HRIA(h3ddata, nr, T_FACES,  _hoops_SRHA, ts->_hoops_CARI, &_hoops_RPCP);
	int _hoops_RARR = 0;
	int _hoops_SIR = 0;
	int _hoops_RHIAR = 0;

	/* _hoops_CGP _hoops_SR _hoops_CHR _hoops_ASCA _hoops_PCCP _hoops_AHIAR _hoops_CRHH, _hoops_RH _hoops_SRS _hoops_HH _hoops_SSCP _hoops_AIAH _hoops_RPII _hoops_ARP _hoops_GH... */
	if (BIT(_hoops_SRHA, _hoops_GGIA)) {
		_hoops_SII(_hoops_IAAR, 0, &_hoops_RPCP, null, null, &_hoops_RARR);
		H3DTexture *_hoops_ACRS = _hoops_GHAH(h3ddata, nr);
		h3ddata->_hoops_GSCR->_hoops_GSAC(nr, null, _hoops_GCHGR, _hoops_ACRS, _hoops_RARR);
	}

	/* _hoops_PHIAR _hoops_HSP _hoops_HSGP _hoops_IS _hoops_PCCP _hoops_HHPA _hoops_GRH _hoops_HH _hoops_CSRR */
	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		_hoops_SII(_hoops_CCRR, 0, &_hoops_RPCP, null, null, &_hoops_RARR);
		_hoops_AGPH((Display_Context alter *) nr->_hoops_SRA, nr->_hoops_IHA->pattern, 0, _hoops_RASP);
		h3ddata->_hoops_GSCR->_hoops_GSAC(nr, 0, _hoops_RSAC, h3ddata->_hoops_SRPH[nr->_hoops_IHA->pattern], _hoops_RARR);
	}

	/* _hoops_ISIRR _hoops_PPR _hoops_HSCR _hoops_CGCR _hoops_HHIAR _hoops_RPP _hoops_HAHH */
	if (_hoops_RPCP._hoops_GIC ) {
		_hoops_SII(_hoops_RCPR, 0, &_hoops_RPCP, null, null, &_hoops_RARR);
		H3DTexture *_hoops_IHIAR = _hoops_GHAH(h3ddata, nr);
		h3ddata->_hoops_GSCR->_hoops_GSAC(nr, 0, _hoops_GCHGR, _hoops_IHIAR, _hoops_RARR);
	}



	/* _hoops_HCRS _hoops_RHIR _hoops_RH _hoops_ACSP _hoops_IIGR _hoops_RH _hoops_AI */
	if (matr->_hoops_ARIR)
	{
		H3DTexture *id = null;
		_hoops_RCR *txr = null;

		if (matr->_hoops_SCA) {
			_hoops_HIR *_hoops_GRIA = matr->_hoops_SCA;
			do {
				txr = _hoops_GRIA->texture;
				_hoops_SII(_hoops_PSRR, _hoops_SIR++, &_hoops_RPCP, null, null, &_hoops_RARR);
				if (!BIT (txr->_hoops_SCR, _hoops_GSR))
					id = _hoops_PIGH(h3ddata, nr, txr, 0);
				h3ddata->_hoops_GSCR->_hoops_GSAC(nr, txr, 0, id, _hoops_RARR);
			} while ((_hoops_GRIA = _hoops_GRIA->next) != null);
		}
		if ((txr = matr->texture[_hoops_RIA]) != null) {
			_hoops_SII(_hoops_CAAR, 0, &_hoops_RPCP, null, null, &_hoops_RARR);
			id = _hoops_PIGH(h3ddata, nr, txr, _hoops_HSGH);
			h3ddata->_hoops_GSCR->_hoops_GSAC(nr, txr, _hoops_HSGH, id, _hoops_RARR);
		}
		if ((txr = matr->texture[_hoops_ACA]) != null) {
			_hoops_SII(_hoops_RPAR, 0, &_hoops_RPCP, null, null, &_hoops_RARR);
			id = _hoops_PIGH(h3ddata, nr, txr, 0);
			h3ddata->_hoops_GSCR->_hoops_GSAC(nr, txr, 0, id, _hoops_RARR);
		}
		if ((txr = matr->texture[_hoops_IIA]) != null) {
			_hoops_SII(_hoops_APAR, 0, &_hoops_RPCP, null, null, &_hoops_RARR);
			id = _hoops_PIGH(h3ddata, nr, txr, 0);
			h3ddata->_hoops_GSCR->_hoops_GSAC(nr, txr, 0, id, _hoops_RARR);
		}
		if ((txr = matr->texture[_hoops_HIA]) != null) {
			_hoops_SII(_hoops_PPAR, 0, &_hoops_RPCP, null, null, &_hoops_RARR);
			id = _hoops_PIGH(h3ddata, nr, txr, 0);
			h3ddata->_hoops_GSCR->_hoops_GSAC(nr, txr, 0, id, _hoops_RARR);
		}
		if ((txr = matr->texture[_hoops_PCA]) != null) {
			_hoops_SII(_hoops_HPAR, 0, &_hoops_RPCP, null, null, &_hoops_RARR);
			id = _hoops_PIGH(h3ddata, nr, txr, 0);
			h3ddata->_hoops_GSCR->_hoops_GSAC(nr, txr, 0, id, _hoops_RARR);
		}
		if ((txr = matr->texture[_hoops_HCA]) != null) {
			_hoops_SII(_hoops_CPAR, 0, &_hoops_RPCP, null, null, &_hoops_RARR);
			id = _hoops_PIGH(h3ddata, nr, txr, 0);
			h3ddata->_hoops_GSCR->_hoops_GSAC(nr, txr, 0, id, _hoops_RARR);
		}
	}

	if (_hoops_ARSA && _hoops_SHA->_hoops_ARIR) {
		H3DTexture *id = null;
		_hoops_RCR *txr = null;
		if (_hoops_SHA->_hoops_SCA) {
			_hoops_HIR *_hoops_GRIA = _hoops_SHA->_hoops_SCA;
			do {
				txr = _hoops_GRIA->texture;
				 _hoops_SII(_hoops_IRAR, _hoops_RHIAR++, &_hoops_RPCP, null, null, &_hoops_RARR);
				id = _hoops_PIGH(h3ddata, nr, txr, 0);
				h3ddata->_hoops_GSCR->_hoops_GSAC(nr, txr, 0, id, _hoops_RARR);
			} while ((_hoops_GRIA = _hoops_GRIA->next) != null);
		}
	}


	Test *	cull_results = null;

	/* _hoops_AGGA, _hoops_CGIC _hoops_PGAP _hoops_AIPS _hoops_SR _hoops_HHGC _hoops_IS _hoops_SGH, _hoops_PPR _hoops_ARP _hoops_GH */
	H3DVertexFormat _hoops_PPCP;
	int _hoops_GRRA = 0;

	if (_hoops_RRHA) {
		_hoops_RRHA->_hoops_CRHA->ResetCursor();
		pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
		ts = (Tristrip const *) pair->geo;
		if (_hoops_RRHA->odl) {
			if (pair->_hoops_CPAI)
				_hoops_SHAS = &pair->_hoops_CPAI->matrix;
			else
				_hoops_SHAS = null;
			if (_hoops_SHAS && _hoops_PPCP._hoops_HHCP() && _hoops_SHAS->_hoops_APRA == null)
				HI_Validate_Matrix_Adjoint((_hoops_HRPA alter *)_hoops_SHAS);
		}
		_hoops_GPCP = _hoops_CCAI (pair->color, Color_FRONT);;
	}

	/* _hoops_ARP _hoops_GH _hoops_RH _hoops_AIPS _hoops_SGI, _hoops_PPR _hoops_CSGA _hoops_PGAS _hoops_PPARR _hoops_IGIR */
	if (BIT(_hoops_SRHA, DL_DO_NOT_RECOMPILE)) {
		odl = (H3D_Display_List *) ts->_hoops_GAHA->list;
		_hoops_PPCP = odl->_hoops_PPCP;
	}
	else {
		_hoops_PPCP._hoops_AIHC();

		if (ts->_hoops_ICHA != null || ts->_hoops_PRHH != null)
			_hoops_PPCP._hoops_CCRS();

		if (ts->_hoops_PCHA != null || ts->_hoops_PAGI != null || _hoops_GPCP)
			_hoops_PPCP._hoops_RPHC();

		int _hoops_ASRR = 0;
		if (BIT(_hoops_SRHA, _hoops_GGIA)) {
			_hoops_SII(_hoops_IAAR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
			_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
			_hoops_PPCP._hoops_HIHC( _hoops_GRRA, 3);
		}

		if (ts->_hoops_CARI & _hoops_APIA) {
			_hoops_SII(_hoops_HCRR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
			_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
			_hoops_PPCP._hoops_HIHC( _hoops_GRRA, 2 );
		}

		if (nr->_hoops_IRR->_hoops_SRI == _hoops_GAI) {
			_hoops_SII(_hoops_ACPR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
			_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
			_hoops_PPCP._hoops_HIHC( _hoops_GRRA, 1 );
		}

		if (matr->_hoops_ARIR && ts->_hoops_GSSH && ts->_hoops_GSSH->_hoops_GSHA > 0) {
			_hoops_HIR *_hoops_PGC = matr->_hoops_SCA;
			for (_hoops_ASRR = 0; _hoops_ASRR < _hoops_SIR; _hoops_ASRR++) {
				_hoops_SII(_hoops_PSRR, _hoops_ASRR, &_hoops_RPCP, &_hoops_GRRA, null, null);
				_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
				switch(_hoops_PGC->texture->_hoops_PSR) {
					case HK_PS_U:
						_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
						break;

					case HK_PS_UNSPECIFIED:
					case HK_PS_UV:
					case HK_PS_OBJECT:
					case HK_PS_WORLD:
					case HK_PS_SURFACE_NORMAL:
					case HK_PS_REFLECTION_VECTOR:
					case HK_PS_NATURAL_UV:
					case HK_PS_LOCAL_PIXELS:
					case HK_PS_OUTER_PIXELS:
					case HK_PS_LOCAL_WINDOW:
					case HK_PS_OUTER_WINDOW:
					case HK_PS_TRANSMISSION_VECTOR:
					case HK_PS_SPHERE:
					case HK_PS_CYLINDER:
					case _hoops_HSR:
						_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
						break;

					case HK_PS_UVW:
						_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
						break;
					default: HE_ERROR (HEC_DX9_DRIVER, HES_PROCEDURAL_ERROR,
						"Invalid vertex param width");
				}
				_hoops_PGC = _hoops_PGC->next;
			}

			if (matr->texture[_hoops_IIA]) {
				_hoops_SII(_hoops_APAR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
				_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
				_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
			}

			if (_hoops_APIAR) {
				_hoops_SII(_hoops_RHRR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
				_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
				_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
			}

			if (matr->texture[_hoops_HIA]) {
				_hoops_SII(_hoops_PPAR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
				_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
				_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
			}
			if (matr->texture[_hoops_ACA]) {
				_hoops_SII(_hoops_RPAR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
				_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
				_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
			}
			if (matr->texture[_hoops_PCA]) {
				_hoops_SII(_hoops_HPAR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
				_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
				_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
			}
			if (matr->texture[_hoops_HCA]) {
				_hoops_SII(_hoops_CPAR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
				_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
				_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
			}
		}

		if (_hoops_ARSA && _hoops_SHA->_hoops_ARIR && ts->_hoops_GSSH && ts->_hoops_GSSH->_hoops_GSHA > 0) {
			for (int j = 0; j < _hoops_RHIAR; j++) {
				_hoops_SII(_hoops_IRAR, j, &_hoops_RPCP, &_hoops_GRRA, null, null);
				_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
				_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
			}
		}
	}

	if (!_hoops_CRRS) {
  _hoops_CIPS:
		if (h3ddata->_hoops_CIGI &&
			!BIT (_hoops_SRHA, DL_SUPPRESS_SEGMENT_DISPLAY_LISTS))
			h3ddata->_hoops_CIGI->mask &= ~_hoops_GCGI;

		/* _hoops_AGHP _hoops_IACA _hoops_PSPAR _hoops_RPP _hoops_SIGR */
		if ( _hoops_APIAR && ts->_hoops_GSSH->_hoops_CCHA != null)
			_hoops_GGARR = _hoops_GHPAR(h3ddata, ts);

		if (_hoops_APHA == H3D_Unshared_Vertices)
			_hoops_SSSRR(nr, ts, _hoops_GGARR, _hoops_RRHA, _hoops_CAPA, _hoops_PPCP, _hoops_APHA, &_hoops_RPCP, _hoops_CISP, _hoops_RASP);
		else
			_hoops_CSSRR(nr, ts, _hoops_GGARR, _hoops_RRHA, _hoops_CAPA, _hoops_PPCP, _hoops_APHA, &_hoops_RPCP, _hoops_CISP, _hoops_RASP);
		goto done;
	}
	else {
		H3D_Bounding_Tree *_hoops_RSPS = null;

		if (_hoops_RRHA) {
			ZALLOC(_hoops_RRHA->odl, H3D_Display_List);
			odl = _hoops_RRHA->odl;
			odl->type = H3D_DL_GEOMETRY;
			odl->time_stamp = HOOPS_WORLD->_hoops_GPPI;
			_hoops_IRRS = true;

			_hoops_HIPAR = _hoops_RRHA->_hoops_CRHA->Count();
			// _hoops_SSCR _hoops_GGSR _hoops_RPP _hoops_SR _hoops_HS _hoops_CHIAR _hoops_SHIAR
			for (;;) {
				if (pair->_hoops_CPAI && ts->bounding != null) {
					_hoops_AAPS = true;
					break;
				}
				_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
				pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
				if (!pair)
					break;
				ts = (Tristrip const *) pair->geo;
			}
			_hoops_RSPS = _hoops_SRHS (dc->memory_pool, null, _hoops_RRHA, _hoops_AAPS);
			if (_hoops_HIPAR > 1) {
				ALLOC_ARRAY(_hoops_AHPAR, _hoops_HIPAR, int);
			}
		}
		else {
			_hoops_IRRS = _hoops_AACR(nr, &_hoops_RPIAR->_hoops_GAHA, &dl, &odl, H3D_DL_GEOMETRY);

			/* _hoops_AGAS _hoops_RH _hoops_AIRI _hoops_HIGR _hoops_RPP _hoops_GII _hoops_GCAC _hoops_SGI _hoops_PAR _hoops_RH _hoops_PGAS _hoops_HS _hoops_HGAS */
			if (!_hoops_IRRS &&
				!h3ddata->_hoops_PI.mode &&
				!h3ddata->_hoops_CHSP.mode &&
				((_hoops_PPCP._hoops_HPCP() & odl->_hoops_PPCP._hoops_HPCP()) != _hoops_PPCP._hoops_HPCP() ||	//_hoops_RPP _hoops_CCAH _hoops_PGAS _hoops_HRGR _hoops_GIIAR _hoops_IIGR _hoops_RHGS _hoops_PGAS, _hoops_PSP _hoops_RRP _hoops_IS _hoops_HRCI
				!_hoops_RPRC(nr, ts, dl, odl)))
			{
				Tristrip alter * _hoops_RPIAR = (Tristrip alter *)ts;
				HD_Queue_Destroy_List (odl, true);
				if (BIT(_hoops_SRHA, DL_DO_NOT_RECOMPILE))
					goto done;

				_hoops_IRRS = _hoops_AACR(nr, &_hoops_RPIAR->_hoops_GAHA, &dl, &odl, H3D_DL_GEOMETRY);
			}
			if (_hoops_IRRS) {
				_hoops_RSPS = _hoops_SRHS (dc->memory_pool, (_hoops_GAHS const *)ts, null, false);
				dl->_hoops_GSAI = ts->_hoops_GSAI;  //_hoops_PSP _hoops_GRRI->_hoops_RSRC _hoops_GGR _hoops_SCGI _hoops_AGIR
			}
		}

		if (_hoops_IRRS) {
			/* _hoops_AGGA, _hoops_SR _hoops_RRP _hoops_IS _hoops_HSRS _hoops_RSH _hoops_SR _hoops_HHGC _hoops_IS _hoops_CISA _hoops_GPHA/_hoops_CIHA _hoops_SRHR. _hoops_RIIAR _hoops_CHR:
			 * - _hoops_AIIAR _hoops_RPIC (_hoops_RIH _hoops_GGR _hoops_HCR _hoops_RSSA, _hoops_PPR _hoops_PIIAR _hoops_CIHA _hoops_PSCA)
			 * - _hoops_HIIAR _hoops_RPIC (_hoops_RIH _hoops_GGR _hoops_HCR _hoops_RSSA, _hoops_HHGP _hoops_GH _hoops_HCR _hoops_HIPH)
			 * - _hoops_HIIAR _hoops_RPIC "_hoops_IIIAR" (_hoops_IPS _hoops_GRR _hoops_CCGI _hoops_RSSA _hoops_GGR, _hoops_IPS _hoops_GRR _hoops_CIHA _hoops_SRHR'_hoops_GRI _hoops_PSPI _hoops_GGR)
			 */

			H3DVertexBuffer &_hoops_PAIH = h3ddata->_hoops_CP;
			H3DIndexBuffer _hoops_CHPC;
			H3DIndexBuffer _hoops_IHPAR;

			float *_hoops_ICPS = null;
			short *_hoops_CCPS = null;
			bool _hoops_AAAS = false;
			unsigned int _hoops_PCPS;
			unsigned int _hoops_HCPS;

			bool _hoops_PCGS = false;
			int _hoops_GHAS = 0;		//_hoops_SCGR _hoops_PPSR _hoops_CIIAR _hoops_GGR _hoops_GPHA _hoops_SRHR
			int _hoops_RIPAR = 0;

			if (_hoops_SCPI == 0) {
				// _hoops_RPP _hoops_SR _hoops_HGCR _hoops_ARI, _hoops_SR _hoops_PAHH _hoops_RIAGR _hoops_IRS _hoops_AIRI _hoops_HIGR _hoops_ARPP (_hoops_HIS _hoops_SR _hoops_HPSH _hoops_SIIAR)
				//   _hoops_SGS _hoops_SIGR _hoops_IS _hoops_SHH _hoops_RHHS _hoops_SGGR (_hoops_HGPP _hoops_SGS _hoops_SR _hoops_RRP _hoops_RH _hoops_GCHA _hoops_HA)
				_hoops_CRGAR(nr, ts, _hoops_RRHA, _hoops_APHA, &_hoops_SCPI, &face_count);
			}
			if (_hoops_RRHA) {
				_hoops_RRHA->_hoops_CRHA->ResetCursor();
				pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
				ts = (Tristrip const *) pair->geo;
				if (_hoops_RRHA->odl) {
					if (pair->_hoops_CPAI)
						_hoops_SHAS = &pair->_hoops_CPAI->matrix;
					else
						_hoops_SHAS = null;
					if (_hoops_SHAS && _hoops_PPCP._hoops_HHCP() && _hoops_SHAS->_hoops_APRA == null)
						HI_Validate_Matrix_Adjoint((_hoops_HRPA alter *)_hoops_SHAS);
					_hoops_CIPAR = (_hoops_SHAS && BIT(_hoops_SHAS->_hoops_RAGR, _hoops_CASA));
				}
				_hoops_GPCP = _hoops_CCAI (pair->color, Color_FRONT);

				// _hoops_IGHS _hoops_CAGH _hoops_PAPA _hoops_CGHS, _hoops_HIS _hoops_HRCI _hoops_GII _hoops_CPAP _hoops_CGHS
				if (ts->_hoops_GAHA && ts->_hoops_GAHA->list)
					HD_Queue_Destroy_List (ts->_hoops_GAHA->list, true);
			}

			/* _hoops_AGHP _hoops_IACA _hoops_PSPAR _hoops_RPP _hoops_SIGR */
			if ( _hoops_APIAR && ts->_hoops_GSSH->_hoops_CCHA != null)
				_hoops_GGARR = _hoops_GHPAR(h3ddata, ts);

			bool _hoops_PAA = (_hoops_GPCP!=null);
			odl->_hoops_RAHA = _hoops_RHA(ts, _hoops_PAA);
			if (odl->item.geometry.id == 0)
				odl->item.geometry.id = POOL_NEW(dc->memory_pool, H3DIndexedBufferObject_List)(dc->memory_pool);
			odl->item.geometry._hoops_SGAS = H3D_OBJ_IndexBuffer;
			odl->item.geometry._hoops_GSAI = ts->_hoops_GSAI;
			odl->item.geometry._hoops_SRHA = ts->_hoops_SRHA;
			odl->item.geometry._hoops_CARI = ts->_hoops_CARI;
			if (nr->_hoops_IRR->_hoops_SRI == _hoops_GAI && 
				BIT (nr->transform_rendition->heuristics, _hoops_IRI))
				odl->item.geometry._hoops_CARI |= _hoops_HRRI;
			odl->item.geometry._hoops_IRRI = ts->face_attributes.flags;
			odl->item.geometry._hoops_IGGI.point_count = 0;
			odl->item.geometry._hoops_IGGI.total = 0;
			odl->item.geometry._hoops_IGGI._hoops_PHHA = 0;
			odl->_hoops_PPCP = _hoops_PPCP;

			int _hoops_CHRC;
			_hoops_SII(_hoops_PHIA, 0, &_hoops_RPCP, null, null, &_hoops_CHRC);
			odl->item.geometry._hoops_HSRC = _hoops_IGIA(matr, _hoops_CHRC, 0);

			if (_hoops_APHA == H3D_Partially_Shared_Vertices) {
				/* _hoops_GHSI _hoops_GCSP _hoops_GIHA
				* _hoops_GCIAR'_hoops_GRI _hoops_GPIC _hoops_RCIAR, _hoops_HIS _hoops_PSP _hoops_RRP _hoops_IS _hoops_ACIAR;
				* _hoops_SR _hoops_GSRGR _hoops_PCIAR _hoops_IIGR _hoops_RSSA _hoops_IH _hoops_GRR _hoops_CIHA _hoops_HIGR. */
				int i;
				int _hoops_GHHAR = 2 - h3ddata->_hoops_RRARR;	//_hoops_HAGH _hoops_HSP _hoops_SHI _hoops_GAPA _hoops_AHHS/_hoops_HCIAR
				ASSERT(_hoops_GHHAR >= 0);

				_hoops_PCPS = _hoops_SCPI;
				_hoops_HCPS = face_count + 2;

				if (_hoops_PCPS > h3ddata->_hoops_ACGH._hoops_CGGI ||
					_hoops_HCPS > h3ddata->_hoops_ACGH._hoops_GRGI * 2)
				{
					_hoops_PCPS = h3ddata->_hoops_ACGH._hoops_CGGI;
					_hoops_HCPS = h3ddata->_hoops_ACGH._hoops_GRGI;
					_hoops_AAAS = true;

					//_hoops_AGHR(_hoops_SCGI->_hoops_AIHRR->_hoops_SGR() == 1);
				}

				_hoops_ACRRR(h3ddata, _hoops_ICPS, (int) _hoops_PCPS * _hoops_PPCP._hoops_HGHS(false));
				_hoops_HCRRR(h3ddata, _hoops_CCPS, (int) _hoops_HCPS);

				int _hoops_ICIAR = 0;
				int _hoops_ISPAR;

				for (_hoops_AIPAR = 0; ;_hoops_AIPAR++) {
					int j;
					int _hoops_CACP;
					int _hoops_CRPAR = -1;
					int len = 0;
					int _hoops_SCHC = 0;
					int _hoops_CCIAR = 0;
					int *_hoops_SGHAR = ts->face_indices;

					if (_hoops_SHAS && BIT(_hoops_SHAS->_hoops_RAGR, _hoops_CASA))
						_hoops_ISPAR = 0x1;
					else
						_hoops_ISPAR = 0;

					h3ddata->_hoops_PGARR = _hoops_CAPAR ();
					for (i = 0; i < ts->_hoops_PHHA; i++) {
						if (_hoops_SGHAR)
							_hoops_SGHAR += _hoops_GHHAR;
						_hoops_CRPAR++;

						len = ts->lengths[i];

						// _hoops_SCIAR _hoops_IRS _hoops_CGGR, _hoops_IPS _hoops_GRR _hoops_GPHA _hoops_PPR _hoops_CIHA _hoops_IAPR
						for (j = 0 ; j < len ; j++) {
							// _hoops_HHGP, _hoops_HIH _hoops_SHSP _hoops_IRS _hoops_RSCA _hoops_IGRH _hoops_IIGR _hoops_GSIAR _hoops_IS _hoops_RGHH _hoops_ARHAR _hoops_HIPH,
							// _hoops_IHH _hoops_GIHA, _hoops_PPR _hoops_IS _hoops_ASSS _hoops_RSIAR _hoops_IH _hoops_HPGR _hoops_CHGC _hoops_SPR _hoops_SCPH _hoops_GGR _hoops_IRS _hoops_CGGR
							// _hoops_GSIAR _hoops_HRGR _hoops_ASIAR _hoops_PSIAR, _hoops_IS _hoops_SHH _hoops_GPP _hoops_RH _hoops_ICIC _hoops_PPAP
							if (_hoops_PCGS && _hoops_AAAS &&
								(_hoops_PAIH.length() > (int) _hoops_PCPS - 16 ||
								_hoops_CHPC.length() > (int) _hoops_HCPS - 20))
							{
								bool _hoops_IA = true;

								_hoops_IIPAR = h3ddata->_hoops_GSCR->_hoops_PRAS();
								_hoops_IA = _hoops_IA && _hoops_IIPAR->CreateVertexBuffer(h3ddata, _hoops_PAIH.length(), _hoops_PPCP);
								_hoops_IA = _hoops_IA && _hoops_IIPAR->CreateIndexBuffer(h3ddata, H3DPT_TRIANGLESTRIP, _hoops_CHPC.length(), _hoops_CHPC.length() - 2);

								if (!_hoops_IA) {
									bool _hoops_GIGI = _hoops_SPPAR(&_hoops_IIPAR, _hoops_RRHA, odl);
									if (_hoops_GIGI)
										goto _hoops_CIPS;
									else
										goto done;
								}

								_hoops_IIPAR->_hoops_PAHS(_hoops_ICPS, _hoops_PAIH.length() * _hoops_PPCP._hoops_HGHS());
								_hoops_IIPAR->_hoops_HAHS(_hoops_CCPS, _hoops_CHPC.length() * sizeof(short));

								if (odl->item.geometry.id == 0)
									odl->item.geometry.id = POOL_NEW(dc->memory_pool, H3DIndexedBufferObject_List)(dc->memory_pool);
								odl->item.geometry.id->AddFirst(_hoops_IIPAR);

								_hoops_RIPAR++;
								if (_hoops_RSPS) {
									_hoops_IIPAR->_hoops_IAHS = _hoops_RSPS;
									_hoops_CAHS (_hoops_RSPS);
								}
								_hoops_IIPAR->_hoops_SAHS			= _hoops_AIPAR - _hoops_PIPAR + 1;
								_hoops_IIPAR->_hoops_GPHS			= _hoops_PIPAR;
								if (_hoops_HIPAR > 1) {
									ALLOC_ARRAY(_hoops_IIPAR->_hoops_RPHS, _hoops_IIPAR->_hoops_SAHS, int);
									_hoops_AIGA(_hoops_AHPAR, _hoops_IIPAR->_hoops_SAHS, int, _hoops_IIPAR->_hoops_RPHS);
								}
								else
									_hoops_IIPAR->_hoops_RPHS = null;

								_hoops_PCGS = false;
							}
							if (!_hoops_PCGS) {
								_hoops_PAIH._hoops_IRA(_hoops_ICPS, &_hoops_PPCP);
								_hoops_CHPC._hoops_IRA(H3DFMT_INDEX16, _hoops_CCPS);

								// _hoops_RPP _hoops_SR _hoops_AAPR _hoops_GGR _hoops_RH _hoops_IRGP _hoops_IIGR _hoops_IRS _hoops_CGGR _hoops_CGPR _hoops_SR _hoops_HHGP, _hoops_PSCR
								// _hoops_SR _hoops_RRP _hoops_IS _hoops_APHS _hoops_RH _hoops_PGHC _hoops_GPHA, _hoops_PPR _hoops_GACC
								// _hoops_HIHA _hoops_IH _hoops_RSSP
								for (int _hoops_GCCGR = 0; _hoops_GCCGR < 2; _hoops_GCCGR++) {
									if (j > 0) {
										j--;
										if (_hoops_SGHAR) {
											if (j < len - _hoops_GHHAR)
												_hoops_SGHAR--;
										}
										else {
											if (j > (2 - _hoops_GHHAR) && j < len - _hoops_GHHAR)
												_hoops_CRPAR--;
										}
									}
								}

								if ((j & 0x1) != _hoops_ISPAR) {
									_hoops_CHPC = 0;
									++_hoops_CHPC;
								}

								_hoops_GHAS = 0;
								_hoops_ICIAR = 0;
								_hoops_PIPAR = _hoops_AIPAR;

								_hoops_PCGS = true;
							}

							if (j == 0) {
								if (_hoops_AHPAR)
									_hoops_AHPAR[_hoops_AIPAR - _hoops_PIPAR] = _hoops_CHPC.length();

								// _hoops_GIHAR _hoops_HIPH
								if (_hoops_CHPC.length()) {
									_hoops_CHPC = _hoops_GHAS;
									++_hoops_CHPC;
									_hoops_CCIAR = _hoops_CHPC.length();
									if ((_hoops_CCIAR & 0x1) != _hoops_ISPAR) {
										_hoops_CHPC = _hoops_GHAS;
										++_hoops_CHPC;
									}
								}
							}

							if (_hoops_SGHAR) {
								if (j < len - _hoops_GHHAR)
									_hoops_CRPAR = *_hoops_SGHAR++;
							}
							else {
								if (j > (2 - _hoops_GHHAR) && j < len - _hoops_GHHAR)
									_hoops_CRPAR++;
							}

							_hoops_CACP = ts->_hoops_AIHA[j + _hoops_SCHC];
							_hoops_SAPAR(_hoops_PPCP, nr, h3ddata, ts, _hoops_GGARR, _hoops_PAIH, _hoops_CACP, _hoops_SHAS, _hoops_GPCP, &_hoops_RPCP, _hoops_CRPAR);

							_hoops_CHPC = _hoops_GHAS;
							++_hoops_CHPC;

							_hoops_GHAS++;
						}

						// _hoops_GIHAR _hoops_HIPH _hoops_GGR _hoops_ISSC
						_hoops_CHPC = _hoops_GHAS+_hoops_ICIAR-1;
						++_hoops_CHPC;

						_hoops_SCHC += len;

						if (j == len - 1) {
							_hoops_CCIAR = _hoops_CHPC.length();
							if ((_hoops_CCIAR & 0x1) != 0) {
								_hoops_CHPC = *(_hoops_CHPC-1);
								++_hoops_CHPC;
								_hoops_CCIAR++;
							}
						}
					}

					if (_hoops_RRHA) {
						_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
						pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
						if (!pair)
							break;
						ts = (Tristrip const *) pair->geo;
						/* _hoops_AGHP _hoops_IACA _hoops_PSPAR _hoops_RPP _hoops_SIGR */
						if ( _hoops_APIAR && ts->_hoops_GSSH->_hoops_CCHA != null)
							_hoops_GGARR = _hoops_GHPAR(h3ddata,ts);
						if (pair->_hoops_CPAI)
							_hoops_SHAS = &pair->_hoops_CPAI->matrix;
						else
							_hoops_SHAS = null;
						if (_hoops_SHAS && _hoops_PPCP._hoops_HHCP() && _hoops_SHAS->_hoops_APRA == null)
							HI_Validate_Matrix_Adjoint((_hoops_HRPA alter *)_hoops_SHAS);
						_hoops_GPCP = _hoops_CCAI (pair->color, Color_FRONT);

						// _hoops_IGHS _hoops_CAGH _hoops_PAPA _hoops_CGHS, _hoops_HIS _hoops_HRCI _hoops_GII _hoops_CPAP _hoops_CGHS
						if (ts->_hoops_GAHA && ts->_hoops_GAHA->list)
							HD_Queue_Destroy_List (ts->_hoops_GAHA->list, true);

						odl->item.geometry._hoops_IGGI.point_count += ts->total;
						odl->item.geometry._hoops_IGGI._hoops_PHHA += ts->_hoops_PHHA;
						odl->item.geometry._hoops_IGGI.total += ts->total;
					}
					else
						break;
				}

				if (_hoops_PCGS) {
					bool _hoops_IA = true;

					_hoops_IIPAR = h3ddata->_hoops_GSCR->_hoops_PRAS();
					_hoops_IA = _hoops_IA && _hoops_IIPAR->CreateVertexBuffer(h3ddata, _hoops_PAIH.length(), _hoops_PPCP);
					_hoops_IA = _hoops_IA && _hoops_IIPAR->CreateIndexBuffer(h3ddata, H3DPT_TRIANGLESTRIP, _hoops_CHPC.length(), _hoops_CHPC.length() - 2);

					if (!_hoops_IA) {
						bool _hoops_GIGI = _hoops_SPPAR(&_hoops_IIPAR, _hoops_RRHA, odl);
						if (_hoops_GIGI)
							goto _hoops_CIPS;
						else
							goto done;
					}

					_hoops_IIPAR->_hoops_PAHS(_hoops_ICPS, _hoops_PAIH.length() * _hoops_PPCP._hoops_HGHS());
					_hoops_IIPAR->_hoops_HAHS(_hoops_CCPS, _hoops_CHPC.length() * sizeof(short));

					if (odl->item.geometry.id == 0)
						odl->item.geometry.id = POOL_NEW(dc->memory_pool, H3DIndexedBufferObject_List)(dc->memory_pool);
					odl->item.geometry.id->AddFirst(_hoops_IIPAR);

					_hoops_RIPAR++;
					if (_hoops_RSPS) {
						_hoops_IIPAR->_hoops_IAHS = _hoops_RSPS;
						_hoops_CAHS (_hoops_RSPS);
					}
					_hoops_IIPAR->_hoops_SAHS			= _hoops_AIPAR - _hoops_PIPAR + 1;
					_hoops_IIPAR->_hoops_GPHS			= _hoops_PIPAR;
					if (_hoops_HIPAR > 1) {
						ALLOC_ARRAY(_hoops_IIPAR->_hoops_RPHS, _hoops_IIPAR->_hoops_SAHS, int);
						_hoops_AIGA(_hoops_AHPAR, _hoops_IIPAR->_hoops_SAHS, int, _hoops_IIPAR->_hoops_RPHS);
					}
					else
						_hoops_IIPAR->_hoops_RPHS = null;

					_hoops_PCGS = false;
				}
			}
			else if (_hoops_APHA == H3D_Unshared_Vertices) {
				/* _hoops_HRPS _hoops_GIHA
				 * _hoops_CGP _hoops_SR _hoops_HS _hoops_IRS _hoops_ASRS _hoops_IIGR _hoops_GPIC _hoops_PPR _hoops_HSIAR _hoops_GGAR, _hoops_SR _hoops_RRP _hoops_IS _hoops_HHGP _hoops_CRGR _hoops_HIPH */

				_hoops_PCPS = face_count*3;
				_hoops_HCPS = face_count*3;

				if (_hoops_PCPS > h3ddata->_hoops_ACGH._hoops_CGGI ||
					_hoops_HCPS > h3ddata->_hoops_ACGH._hoops_GRGI * 2)
				{
					_hoops_PCPS = h3ddata->_hoops_ACGH._hoops_CGGI;
					_hoops_HCPS = h3ddata->_hoops_ACGH._hoops_GRGI;
					_hoops_AAAS = true;

					//_hoops_AGHR(_hoops_SCGI->_hoops_AIHRR->_hoops_SGR() == 1);
				}

				_hoops_ACRRR(h3ddata, _hoops_ICPS, (int) _hoops_PCPS * _hoops_PPCP._hoops_HGHS(false));
				_hoops_HCRRR(h3ddata, _hoops_CCPS, (int) _hoops_HCPS);

				/* _hoops_PHIR _hoops_RH _hoops_GPHA _hoops_SRHR */
				{
					// _hoops_ASC _hoops_AII _hoops_CHR _hoops_IGI _hoops_CGPR _hoops_GSRI _hoops_GPGR _hoops_CHPAR. _hoops_GSAH _hoops_IS _hoops_PRRP _hoops_ARPR
					// _hoops_IRS _hoops_ISIAR _hoops_GPHA/_hoops_CIHA _hoops_SRHR.

					short *_hoops_PHAS = h3ddata->_hoops_PSRRR;
					int _hoops_GHAS = 0;
					int _hoops_CRPAR = -1;
					int *_hoops_SGHAR = null;

					for (_hoops_AIPAR = 0; ; _hoops_AIPAR++) {
						if (_hoops_AHPAR)
							_hoops_AHPAR[_hoops_AIPAR - _hoops_PIPAR] = _hoops_CHPC.length();

						point_count = _hoops_IRGAR(ts);
						_hoops_PHAS = _hoops_AIAS(h3ddata, point_count);
						h3ddata->_hoops_PGARR = _hoops_CAPAR ();

						_hoops_SGHAR = ts->face_indices;
						_hoops_CRPAR = -1;

						/* _hoops_PHIR _hoops_RH _hoops_CIHA _hoops_SRHR */
						i = j = 0;
						j = 0;
						for (i = 0; i < ts->_hoops_PHHA; i++) {
							len = ts->lengths[i];
							if (len < 0)
								len = -len;

							if (_hoops_SGHAR)
								_hoops_SGHAR += 2;

							int _hoops_HCPAR = j;
							int _hoops_ICPAR = j+len-2;

							if (_hoops_CIPAR)
								_hoops_HCPAR--;

							for (; j < _hoops_ICPAR; j++) {
								if (_hoops_PCGS && _hoops_AAAS &&
									(_hoops_PAIH.length() > (int) _hoops_PCPS - 3 ||
									_hoops_CHPC.length() > (int) _hoops_HCPS - 3))
								{
									bool _hoops_IA = true;
									_hoops_IIPAR = h3ddata->_hoops_GSCR->_hoops_PRAS();
									_hoops_IA = _hoops_IA && _hoops_IIPAR->CreateVertexBuffer(h3ddata, _hoops_PAIH.length(), _hoops_PPCP);
									_hoops_IA = _hoops_IA && _hoops_IIPAR->CreateIndexBuffer(h3ddata, H3DPT_TRIANGLELIST, _hoops_CHPC.length(), _hoops_CHPC.length() / 3);

									if (!_hoops_IA) {
										bool _hoops_GIGI = _hoops_SPPAR(&_hoops_IIPAR, _hoops_RRHA, odl);
										if (_hoops_GIGI)
											goto _hoops_CIPS;
										else
											goto done;
									}

									_hoops_IIPAR->_hoops_PAHS(_hoops_ICPS, _hoops_PAIH.length() * _hoops_PPCP._hoops_HGHS());
									_hoops_IIPAR->_hoops_HAHS(_hoops_CCPS, _hoops_CHPC.length() * sizeof(short));

									if (odl->item.geometry.id == 0)
										odl->item.geometry.id = POOL_NEW(dc->memory_pool, H3DIndexedBufferObject_List)(dc->memory_pool);
									odl->item.geometry.id->AddFirst(_hoops_IIPAR);

									_hoops_RIPAR++;
									if (_hoops_RSPS) {
										_hoops_IIPAR->_hoops_IAHS = _hoops_RSPS;
										_hoops_CAHS (_hoops_RSPS);
									}
									_hoops_IIPAR->_hoops_SAHS = _hoops_AIPAR - _hoops_PIPAR + 1;
									_hoops_IIPAR->_hoops_GPHS = _hoops_PIPAR;
									if (_hoops_HIPAR > 1) {
										ALLOC_ARRAY(_hoops_IIPAR->_hoops_RPHS, _hoops_IIPAR->_hoops_SAHS, int);
										_hoops_AIGA(_hoops_AHPAR, _hoops_IIPAR->_hoops_SAHS, int, _hoops_IIPAR->_hoops_RPHS);
									}
									else
										_hoops_IIPAR->_hoops_RPHS = null;

									_hoops_PCGS = false;
								}
								if (!_hoops_PCGS) {
									_hoops_PAIH._hoops_IRA(_hoops_ICPS, &_hoops_PPCP);
									_hoops_CHPC._hoops_IRA(H3DFMT_INDEX16, _hoops_CCPS);

									_hoops_GHAS = 0;
									_hoops_PIPAR = _hoops_AIPAR;

									_hoops_PCGS = true;
								}

								if (_hoops_SGHAR)
									_hoops_CRPAR = *_hoops_SGHAR++;
								else
									_hoops_CRPAR++;

								_hoops_RSSH alter *params = (_hoops_RSSH alter *)ts->_hoops_GSSH ? ts->_hoops_GSSH->_hoops_CCHA : 0;
								int width = ts->_hoops_GSSH ? ts->_hoops_GSSH->_hoops_GSHA : 0;
								int _hoops_RHAS, _hoops_AHAS, _hoops_ASPAR;

								if (ts->_hoops_GSSH && BIT (ts->_hoops_GSSH->_hoops_SCAI, _hoops_HPPAR) &&
										(params[ts->_hoops_AIHA[j]*width]-params[ts->_hoops_AIHA[j+1]*width] > _hoops_PRPAR ||
										 params[ts->_hoops_AIHA[j]*width]-params[ts->_hoops_AIHA[j+2]*width] > _hoops_PRPAR ||
										 params[ts->_hoops_AIHA[j+1]*width]-params[ts->_hoops_AIHA[j]*width] > _hoops_PRPAR ||
										 params[ts->_hoops_AIHA[j+1]*width]-params[ts->_hoops_AIHA[j+2]*width] > _hoops_PRPAR ||
										 params[ts->_hoops_AIHA[j+2]*width]-params[ts->_hoops_AIHA[j]*width] > _hoops_PRPAR ||
										 params[ts->_hoops_AIHA[j+2]*width]-params[ts->_hoops_AIHA[j+1]*width] > _hoops_PRPAR)) {
									_hoops_RSSH _hoops_CCHAR[3], _hoops_SCHAR[3], _hoops_GSHAR[3];
									int _hoops_SCPAR = ts->_hoops_AIHA[j];
									int _hoops_GSPAR = ts->_hoops_AIHA[j+1];
									int _hoops_RSPAR = ts->_hoops_AIHA[j+2];

									//_hoops_ASAC
									COPY_PARAMETER(&ts->_hoops_GSSH->_hoops_CCHA[_hoops_SCPAR*width],_hoops_CCHAR,1);
									COPY_PARAMETER(&ts->_hoops_GSSH->_hoops_CCHA[_hoops_GSPAR*width],_hoops_SCHAR,1);
									COPY_PARAMETER(&ts->_hoops_GSSH->_hoops_CCHA[_hoops_RSPAR*width],_hoops_GSHAR,1);

									_hoops_HRPAR (&params[_hoops_SCPAR*width], &params[_hoops_GSPAR*width], &params[_hoops_RSPAR*width]);
									ASSERT (params[_hoops_SCPAR*width]-params[_hoops_GSPAR*width] < _hoops_PRPAR);
									ASSERT (params[_hoops_GSPAR*width]-params[_hoops_SCPAR*width] < _hoops_PRPAR);
									ASSERT (params[_hoops_SCPAR*width]-params[_hoops_RSPAR*width] < _hoops_PRPAR);
									ASSERT (params[_hoops_RSPAR*width]-params[_hoops_SCPAR*width] < _hoops_PRPAR);
									ASSERT (params[_hoops_RSPAR*width]-params[_hoops_GSPAR*width] < _hoops_PRPAR);
									ASSERT (params[_hoops_GSPAR*width]-params[_hoops_RSPAR*width] < _hoops_PRPAR);

									_hoops_SAPAR (_hoops_PPCP, nr, h3ddata, ts, _hoops_GGARR, _hoops_PAIH, _hoops_SCPAR, _hoops_SHAS, _hoops_GPCP, &_hoops_RPCP, _hoops_CRPAR);
									_hoops_SAPAR (_hoops_PPCP, nr, h3ddata, ts, _hoops_GGARR, _hoops_PAIH, _hoops_GSPAR, _hoops_SHAS, _hoops_GPCP, &_hoops_RPCP, _hoops_CRPAR);
									_hoops_SAPAR (_hoops_PPCP, nr, h3ddata, ts, _hoops_GGARR, _hoops_PAIH, _hoops_RSPAR, _hoops_SHAS, _hoops_GPCP, &_hoops_RPCP, _hoops_CRPAR);

									_hoops_RHAS = _hoops_GHAS++;
									_hoops_AHAS = _hoops_GHAS++;
									_hoops_ASPAR = _hoops_GHAS++;

									//_hoops_PHIH
									COPY_PARAMETER(_hoops_CCHAR,&ts->_hoops_GSSH->_hoops_CCHA[_hoops_SCPAR*width],1);
									COPY_PARAMETER(_hoops_SCHAR,&ts->_hoops_GSSH->_hoops_CCHA[_hoops_GSPAR*width],1);
									COPY_PARAMETER(_hoops_GSHAR,&ts->_hoops_GSSH->_hoops_CCHA[_hoops_RSPAR*width],1);
								}
								else {
							
									int _hoops_SCPAR = ts->_hoops_AIHA[j];
									int _hoops_GSPAR = ts->_hoops_AIHA[j+1];
									int _hoops_RSPAR = ts->_hoops_AIHA[j+2];

									_hoops_RHAS = _hoops_PHAS[_hoops_SCPAR] = _hoops_GHAS++;
									_hoops_AHAS = _hoops_PHAS[_hoops_GSPAR] = _hoops_GHAS++;
									_hoops_ASPAR = _hoops_PHAS[_hoops_RSPAR] = _hoops_GHAS++;

									_hoops_SAPAR (_hoops_PPCP, nr, h3ddata, ts, _hoops_GGARR, _hoops_PAIH, _hoops_SCPAR, _hoops_SHAS, _hoops_GPCP, &_hoops_RPCP, _hoops_CRPAR);
									_hoops_SAPAR (_hoops_PPCP, nr, h3ddata, ts, _hoops_GGARR, _hoops_PAIH, _hoops_GSPAR, _hoops_SHAS, _hoops_GPCP, &_hoops_RPCP, _hoops_CRPAR);
									_hoops_SAPAR (_hoops_PPCP, nr, h3ddata, ts, _hoops_GGARR, _hoops_PAIH, _hoops_RSPAR, _hoops_SHAS, _hoops_GPCP, &_hoops_RPCP, _hoops_CRPAR);
								}

								if ((j-_hoops_HCPAR)%2 == 0) {
									_hoops_CHPC[0] = _hoops_RHAS;
									_hoops_CHPC[1] = _hoops_AHAS;
									_hoops_CHPC[2] = _hoops_ASPAR;
								}
								else {
									_hoops_CHPC[0] = _hoops_ASPAR;
									_hoops_CHPC[1] = _hoops_AHAS;
									_hoops_CHPC[2] = _hoops_RHAS;
								}

								_hoops_CHPC+=3;
							}
							j+=2;
						}

						if (_hoops_RRHA) {
							_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
							pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
							if (!pair)
								break;
							ts = (Tristrip const *) pair->geo;
							/* _hoops_AGHP _hoops_IACA _hoops_PSPAR _hoops_RPP _hoops_SIGR */
							if ( _hoops_APIAR && ts->_hoops_GSSH->_hoops_CCHA != null)
								_hoops_GGARR = _hoops_GHPAR(h3ddata,ts);
							if (_hoops_RRHA->odl) {
								if (pair->_hoops_CPAI)
									_hoops_SHAS = &pair->_hoops_CPAI->matrix;
								else
									_hoops_SHAS = null;
								if (_hoops_SHAS && _hoops_PPCP._hoops_HHCP() && _hoops_SHAS->_hoops_APRA == null)
									HI_Validate_Matrix_Adjoint((_hoops_HRPA alter *)_hoops_SHAS);
								_hoops_CIPAR = (_hoops_SHAS && BIT(_hoops_SHAS->_hoops_RAGR, _hoops_CASA));
							}
							_hoops_GPCP = _hoops_CCAI (pair->color, Color_FRONT);

							// _hoops_IGHS _hoops_CAGH _hoops_PAPA _hoops_CGHS, _hoops_HIS _hoops_HRCI _hoops_GII _hoops_CPAP _hoops_CGHS
							if (ts->_hoops_GAHA && ts->_hoops_GAHA->list)
								HD_Queue_Destroy_List (ts->_hoops_GAHA->list, true);

							odl->item.geometry._hoops_IGGI.point_count += ts->total;
							odl->item.geometry._hoops_IGGI._hoops_PHHA += ts->_hoops_PHHA;
							odl->item.geometry._hoops_IGGI.total += ts->total;
						}
						else
							break;
					}

					if (_hoops_PCGS) {
						bool _hoops_IA = true;
						_hoops_IIPAR = h3ddata->_hoops_GSCR->_hoops_PRAS();
						_hoops_IA = _hoops_IA && _hoops_IIPAR->CreateVertexBuffer(h3ddata, _hoops_PAIH.length(), _hoops_PPCP);
						_hoops_IA = _hoops_IA && _hoops_IIPAR->CreateIndexBuffer(h3ddata, H3DPT_TRIANGLELIST, _hoops_CHPC.length(), _hoops_CHPC.length() / 3);

						if (!_hoops_IA) {
							bool _hoops_GIGI = _hoops_SPPAR(&_hoops_IIPAR, _hoops_RRHA, odl);
							if (_hoops_GIGI)
								goto _hoops_CIPS;
							else
								goto done;
						}

						_hoops_IIPAR->_hoops_PAHS(_hoops_ICPS, _hoops_PAIH.length() * _hoops_PPCP._hoops_HGHS());
						_hoops_IIPAR->_hoops_HAHS(_hoops_CCPS, _hoops_CHPC.length() * sizeof(short));

						if (odl->item.geometry.id == 0)
							odl->item.geometry.id = POOL_NEW(dc->memory_pool, H3DIndexedBufferObject_List)(dc->memory_pool);
						odl->item.geometry.id->AddFirst(_hoops_IIPAR);

						_hoops_RIPAR++;
						if (_hoops_RSPS) {
							_hoops_IIPAR->_hoops_IAHS = _hoops_RSPS;
							_hoops_CAHS (_hoops_RSPS);
						}
						_hoops_IIPAR->_hoops_SAHS			= _hoops_AIPAR - _hoops_PIPAR + 1;
						_hoops_IIPAR->_hoops_GPHS			= _hoops_PIPAR;
						if (_hoops_HIPAR > 1) {
							ALLOC_ARRAY(_hoops_IIPAR->_hoops_RPHS, _hoops_IIPAR->_hoops_SAHS, int);
							_hoops_AIGA(_hoops_AHPAR, _hoops_IIPAR->_hoops_SAHS, int, _hoops_IIPAR->_hoops_RPHS);
						}
						else
							_hoops_IIPAR->_hoops_RPHS = null;

						_hoops_PCGS = false;
					}
				}
			}
			else  {
				if (!_hoops_RHPAR (
						nr,
						_hoops_PPCP,
						ts,
						_hoops_GGARR,
						_hoops_RRHA,
						_hoops_RSPS,
						_hoops_AHPAR,
						_hoops_SCPI,
						face_count,
						_hoops_RPCP,
						odl)) {
					if (_hoops_RRHA) {
						ASSERT(_hoops_RRHA->odl == null);
						goto done;
					}
					else
						goto _hoops_CIPS;
				}
			}
			if (_hoops_AHPAR)
				FREE_ARRAY(_hoops_AHPAR, _hoops_HIPAR, int);
		}
		odl->item.geometry.id->ResetCursor();
		if (odl->item.geometry._hoops_SGAS == H3D_OBJ_IndexBuffer)
			_hoops_IIPAR = odl->item.geometry.id->PeekCursor();
		else if (odl->item.geometry._hoops_SGAS == H3D_OBJ_VertexBuffer)
			_hoops_IRPRR = (H3DVertexBufferCache *)odl->item.geometry.id->PeekCursor();
	}

	if (h3ddata->_hoops_CIGI &&
		h3ddata->_hoops_CIGI->_hoops_IHGI)
		goto done;

	_hoops_IHHS =
		!BIT (nr->transform_rendition->flags, _hoops_CHHS) &&
			BIT (nr->_hoops_IRR->_hoops_SHHS, _hoops_GIHS) &&
			(ANYBIT (nr->transform_rendition->_hoops_APH, Heur_Culling_EXTENT|_hoops_RIHS) ||
				(BIT (nr->transform_rendition->_hoops_APH, Heur_Culling_VIEW_FRUSTUM) &&
					!BIT (nr->transform_rendition->flags, _hoops_AIHS)));


	if (_hoops_IIPAR->_hoops_IAHS && _hoops_IHHS) {
		H3D_Bounding_Tree *tree = _hoops_IIPAR->_hoops_IAHS;

		if (tree->count > h3ddata->_hoops_HIHS) {
			if (h3ddata->_hoops_IIHS)
				FREE_ARRAY (h3ddata->_hoops_IIHS, h3ddata->_hoops_HIHS, Test);
			ALLOC_ARRAY (h3ddata->_hoops_IIHS, tree->count, Test);
			h3ddata->_hoops_HIHS = tree->count;
		}

		cull_results = h3ddata->_hoops_IIHS;

		float _hoops_CIHS;

		int	_hoops_SIHS = 0;

		if (BIT (nr->transform_rendition->_hoops_APH, _hoops_RIHS))
			_hoops_SIHS = nr->_hoops_IRR->_hoops_GCHS;
		if (BIT (nr->transform_rendition->_hoops_APH, Heur_Culling_EXTENT))
			_hoops_SIHS = _hoops_IAAA(nr->_hoops_IRR->_hoops_GRGC, _hoops_SIHS);

		_hoops_PIHS = HD_Transform_And_Test_Simple_Sphere (nr, 
						tree->count, tree->_hoops_RCHS, tree->_hoops_ACHS,
						0, _hoops_SIHS, cull_results, null, &_hoops_CIHS);

		if (_hoops_CIHS > 0.0f &&
			nr->_hoops_IRR->_hoops_PCHS == Heur_MAX_EXTENT_MODE_DEFER) { 

			int _hoops_HCHS = (int) (_hoops_CIHS * (float)_hoops_ICHS / (float)_hoops_SIHS);

			if (_hoops_HCHS > dc->_hoops_SSGC)
				((Display_Context alter *)dc)->_hoops_SSGC = _hoops_HCHS;
		}

		if (_hoops_PIHS == 0) {
			if (cull_results && BIT(cull_results[0],Test_EXTENT))
				_hoops_GPRH (_hoops_CSIAR) += _hoops_IIPAR->_hoops_SAHS;
			else
				_hoops_GPRH (_hoops_SSIAR) += _hoops_IIPAR->_hoops_SAHS;
			goto done;
		}
		else if (_hoops_PIHS < tree->count && cull_results) {
			for (i = 0 ; i < tree->count ; i++) {
				if (!tree->_hoops_ACHS ||
					tree->_hoops_ACHS[i] == 0) {
					if (BIT (cull_results[i],Test_EXTENT))
						_hoops_GPRH (_hoops_CSIAR)++;
					else if (cull_results[i] == Test_DISJOINT)
						_hoops_GPRH (_hoops_SSIAR)++;
				}
			}
		}
	}
	else
		_hoops_PIHS = _hoops_IIPAR->_hoops_SAHS;

	_hoops_GPRH(_hoops_GGCAR)++;

	_hoops_HISP(h3ddata, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));

	if ( ts->_hoops_CARI & _hoops_APIA )
		_hoops_SRRS |= H3DID_CIRCLE_MARKER | H3DID_QUAD_MARKER;

	if ( ts->_hoops_CARI & _hoops_RAHAR )
		_hoops_SRRS |= H3DID_POLY_CYLINDER;

	// _hoops_HCGA _hoops_CSCS _hoops_SRGS _hoops_AAIP _hoops_PPR _hoops_HGCR _hoops_HRP _hoops_IH _hoops_RH _hoops_CI
	_hoops_CISP &= nr->_hoops_CPP->_hoops_PRH._hoops_HRH;
	_hoops_SRRS = _hoops_IISP(h3ddata, nr, _hoops_APHA, T_FACES, _hoops_CISP, _hoops_RASP, _hoops_SRRS);
	_hoops_SRRS |= _hoops_CCSP(nr);

	// _hoops_RRAH _hoops_CI
	if (BIT(_hoops_SRRS, H3DID_CREATE_SHADOW_MAP))
		_hoops_SSHH (h3ddata, nr, T_FACES, null, _hoops_SRRS, &_hoops_RSR);
	else if (_hoops_RRHA || BIT(_hoops_SRHA, DL_DO_NOT_RECOMPILE))
		_hoops_CSIC (h3ddata, nr, T_FACES, null, _hoops_SRRS, odl->_hoops_RAHA, &_hoops_RSR);
	else
		_hoops_SSHH (h3ddata, nr, T_FACES, ts, _hoops_SRRS, &_hoops_RSR);

	// _hoops_SPAA _hoops_GHAA _hoops_CPS _hoops_AAHAR _hoops_PAHAR _hoops_HII _hoops_HPPA _hoops_GHC
	_hoops_SSSP(h3ddata, nr, _hoops_RSR);

	// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_ASCA _hoops_RSPH _hoops_CHPI, _hoops_AHHR _hoops_GGSR _hoops_GPIA _hoops_HRP _hoops_CR _hoops_SR _hoops_CRHAR-_hoops_SRHAR _hoops_CAPR
	if ( ts->_hoops_CARI & _hoops_APIA )
		_hoops_RSR->_hoops_CCAA( nr, 0, false, false, null);

	// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_ASCA _hoops_HAHAR, _hoops_HGSR _hoops_SAAA _hoops_IH _hoops_AII
	if ( ts->_hoops_CARI & _hoops_RAHAR )
		_hoops_RSR->_hoops_CIPA( nr );

	for (i = 0; i < 2; i++) {	//_hoops_PGCR-_hoops_RPSA _hoops_APSA _hoops_HAPR
		bool _hoops_PPSA = false;
		if (_hoops_ARSA)
		{
			/* _hoops_RH "_hoops_HPSA != _hoops_IPSA" _hoops_ISPR _hoops_HRGR _hoops_CPSA _hoops_RH _hoops_PSHR _hoops_GAR:
			 * (_hoops_IPSA == _hoops_SPSA || _hoops_GHSA == _hoops_IPSA)
			 */
			if (i == 0 && _hoops_CRSA != _hoops_PRSA) {
				_hoops_RHSA(h3ddata,_hoops_IRSA);
			}
			else if (i == 1 && _hoops_IRSA != _hoops_PRSA) {
				_hoops_RHSA(h3ddata,_hoops_CRSA);
				_hoops_PHSA(h3ddata, nr, T_FACES, _hoops_RSR);

				/* _hoops_SIIR _hoops_AI _hoops_IH _hoops_ISSC _hoops_APIR */
				_hoops_HHA const &_hoops_SHA = nr->_hoops_IHA->_hoops_GIA;
				_hoops_SIR = 0;

				if (_hoops_SHA->_hoops_ARIR)
				{
					H3DTexture *id = null;
					_hoops_RCR *txr = null;

					if (_hoops_SHA->_hoops_SCA) {
						_hoops_HIR *_hoops_GRIA = _hoops_SHA->_hoops_SCA;
						do {
							txr = _hoops_GRIA->texture;
							_hoops_SII(_hoops_IRAR, _hoops_SIR++, &_hoops_RPCP, null, null, &_hoops_RARR);
							id = _hoops_PIGH(h3ddata, nr, txr, 0);
							h3ddata->_hoops_GSCR->_hoops_GSAC(nr, txr, 0, id, _hoops_RARR);
						} while ((_hoops_GRIA = _hoops_GRIA->next) != null);
					}
				}
			}
			else
				_hoops_PPSA = true;
		}
		else
			i = 2;	//_hoops_HAR _hoops_PGCR-_hoops_RPSA, _hoops_HIS _hoops_HHSA _hoops_IRS _hoops_IHSA _hoops_RAS _hoops_SPR _hoops_IPGR

		if (!_hoops_PPSA) {
			do {		//_hoops_HPPA _hoops_IPPA _hoops_HAPR
				h3ddata->_hoops_RPCI = nr->_hoops_CPA;
				_hoops_RSR->_hoops_CHPA (nr, _hoops_CAPA);

				// _hoops_GISP _hoops_RH _hoops_CPAP _hoops_CCA _hoops_RH _hoops_SCGR _hoops_HPPA _hoops_IPPA _hoops_ARP
				if (_hoops_IIPAR) {
					H3DIndexedBufferObject *_hoops_RGCAR;

					odl->item.geometry.id->ResetCursor();
					_hoops_RGCAR = odl->item.geometry.id->PeekCursor();
					do {
						if (_hoops_PIHS == _hoops_RGCAR->_hoops_SAHS)
							_hoops_RGCAR->_hoops_CHSA(h3ddata);
						else
							_hoops_RGCAR->_hoops_CHSA(h3ddata, cull_results);

						odl->item.geometry.id->AdvanceCursor();
					} while ((_hoops_RGCAR = odl->item.geometry.id->PeekCursor()) != null);

				}
				else if (_hoops_IRPRR) {
					if (ts) {
						_hoops_GPRH(_hoops_AGCAR) += ts->total - (ts->_hoops_PHHA*2);
						_hoops_IRPRR->_hoops_CHSA(h3ddata, H3DPT_TRIANGLELIST, ts->total - (ts->_hoops_PHHA*2));
					}
					else {
						_hoops_GPRH(_hoops_AGCAR) += _hoops_RRHA->_hoops_IGGI.total - (_hoops_RRHA->_hoops_IGGI._hoops_PHHA*2);
						_hoops_IRPRR->_hoops_CHSA(h3ddata, H3DPT_TRIANGLELIST,  _hoops_RRHA->_hoops_IGGI.total - (_hoops_RRHA->_hoops_IGGI._hoops_PHHA*2));
					}
					if (dc->_hoops_PGCAR > 0 &&
						_hoops_GPRH(_hoops_AGCAR) > _hoops_GPRH(_hoops_HGCAR)+dc->_hoops_PGCAR) {
						_hoops_GPRH(_hoops_HGCAR) = _hoops_GPRH(_hoops_AGCAR);
						_hoops_GPRH(_hoops_IGCAR)++;
						_hoops_SGPAR(h3ddata);
					}
				}

				if (_hoops_CAPA != null)
					_hoops_CAPA = _hoops_CAPA->next;
			} while (_hoops_CAPA != null);
		}
	}
	if (_hoops_ARSA)
		_hoops_RHSA(h3ddata, _hoops_PRSA);

  done:
	h3ddata->_hoops_AIC = false;

} //_hoops_RSGR _hoops_API '_hoops_CPSA _hoops_PGSA 3d _hoops_CRHH'


void draw_3d_tristrip (
		Net_Rendition const &  nr,
		Tristrip const * ts)
{
	_hoops_RRRI(nr, ts, null);
}

void _hoops_CRRI (
		Net_Rendition const &  nr,
		Tristrip const * ts,
		H3D_Display_List_Bin * _hoops_RRHA)
{
	H3DData alter *h3ddata = H3DD (nr->_hoops_SRA);
	Tristrip alter *_hoops_RPIAR = (Tristrip alter *) ts;

	//_hoops_PRPP _hoops_SIAC _hoops_ACPP _hoops_HIS _hoops_SGS _hoops_GCAC _hoops_HCPH _hoops_CHR _hoops_RCAC _hoops_IS _hoops_SSS
	H3D_TRACE(h3ddata, "draw_indexed_tristrip");

	if (_hoops_RRHA)
		_hoops_RRHA->flags |= (_hoops_GGIA | DL_INDEX_INTERPOLATION);
	else
		_hoops_RPIAR->_hoops_SRHA |= (_hoops_GGIA | DL_INDEX_INTERPOLATION);
	_hoops_RRRI(nr, _hoops_RPIAR, _hoops_RRHA);


}


void _hoops_ARCI (
		Net_Rendition const &  nr,
		Tristrip const * ts)
{
	_hoops_CRRI(nr, ts, null);
}


#endif

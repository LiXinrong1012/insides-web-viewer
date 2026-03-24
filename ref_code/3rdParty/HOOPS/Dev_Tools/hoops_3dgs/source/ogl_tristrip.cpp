/*
 * Copyright (c) 2008 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.87 2010-12-01 21:35:22 heppe Exp $
 *
 */

#if defined(GLX_DRIVER) || defined(WGL_DRIVER) || defined(AGL_DRIVER) || defined(COCOA_OGL_DRIVER)


/*
 * _hoops_SRAC
 */
local void
old_draw_3d_tristrip (
	Net_Rendition const &		nr,
	Tristrip const *			ts) {
	Display_Context const *		dc = nr->_hoops_SRA;
	OGLData alter *				_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	Point const *				points = ts->points;
	RGB const *					_hoops_PAGI = ts->_hoops_PAGI;
	_hoops_ARPA const *				_hoops_PRHH = ts->_hoops_PRHH;
	RGB const *					_hoops_PCHA = ts->_hoops_PCHA;
	Vector const *				_hoops_ICHA = ts->_hoops_ICHA;
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	_hoops_HHA const &	matr = _hoops_SIGA->_hoops_CHA;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_GRGH const &		_hoops_ACHI = nr->_hoops_IRR;
	int							_hoops_RRIRC = 0;
	int *						lengths = ts->lengths;
	int *						_hoops_AIHA = ts->_hoops_AIHA;
	int *						face_indices = ts->face_indices;
	_hoops_RSSH const *			_hoops_CCHA = null;
	Integer32					_hoops_GSHA = 0;
	int 						_hoops_PHHA = ts->_hoops_PHHA;
	int 						_hoops_HCGS, _hoops_HCIRC, _hoops_AGGHC;
	int 						_hoops_SAHAR, _hoops_SSPAR, _hoops_PGGHC;
	int 						_hoops_RASP = 0;
	int 						_hoops_GPIAR = 0;
	int 						_hoops_HGGHC = _hoops_RCHAC;
	OGL_Render_Control *		rc = &_hoops_CSRGR->_hoops_CSC._hoops_PAPAC;
	OGL_Display_List alter *	odl = null;
	int 						_hoops_PGHAR, end;
	int 						i,j,k;
	int 						_hoops_IGGHC;
	int 						_hoops_CIIPP;
	_hoops_IAPA const		*_hoops_CAPA = null, *_hoops_PIPRC = null;
	bool 						_hoops_CCIRC = _hoops_CSRGR->_hoops_PRHGC;
	bool 						_hoops_IAHC = false;
	unsigned int				stipple[32];
	int							_hoops_PRHA = false;
	_hoops_HRPA const *			matrix = null;
	bool						_hoops_CISP;
	_hoops_RRCC*			_hoops_CGGHC = ts->_hoops_GSSH;

	_hoops_RAPRC("old_draw_3d_tristrip", true);

	_hoops_CISP = BIT (nr->_hoops_PSGI, T_FACES);

	if ((_hoops_CSRGR->dc->options._hoops_IRARR & _hoops_IPGAC) && _hoops_CSRGR->_hoops_CHAAC > _hoops_IPRAC) {
		if (BIT (nr->transform_rendition->heuristics, Heur_Culling_VIEW_FRUSTUM)) {
			if (nr->_hoops_IRR->_hoops_PCHS == Heur_MAX_EXTENT_MODE_DEFER) {
				_hoops_CSRGR->_hoops_CHAAC = 0;
 				glFlush();
			}
		}
	}
	_hoops_CSRGR->_hoops_CHAAC++;
	if (_hoops_CSRGR->_hoops_CSC._hoops_IPAGC) {
		_hoops_CCIRC = false;

		/* _hoops_ARAR _hoops_SGS _hoops_HS _hoops_HSP _hoops_AIRC _hoops_CHASA _hoops_RH _hoops_HSPR _hoops_CCA _hoops_SGGHC */
		_hoops_CIIPP = 0x7fffffff; //_hoops_HGPGA->_hoops_ASHGC->_hoops_GRGHC;

		/* _hoops_CGPR _hoops_HHPS _hoops_AIRI _hoops_CPCI, _hoops_SR _hoops_HS _hoops_IS _hoops_SRSHR _hoops_SPR _hoops_PPR _hoops_RRGHC _hoops_CCA _hoops_SCH */
		_hoops_PRHA = ( (ts->_hoops_GSSH && ts->_hoops_GSSH->_hoops_GSHA) || _hoops_PCHA || _hoops_ICHA);
	}
	else {
		bool synthetic_params = (
			ts->_hoops_ICHA && 
			matr &&
			matr->texture[_hoops_RIA] &&
			(matr->texture[_hoops_RIA]->_hoops_PSR == _hoops_HSR ||
			_hoops_IHCR->_hoops_SPH->projection != _hoops_GHH)
		);

		_hoops_IAHC = _hoops_HGRI (nr, ts->_hoops_SRHA, _hoops_CISP);

		if (BIT (nr->transform_rendition->flags, _hoops_GRHH) &&
			BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES)) {
			if (BIT (HOOPS_WORLD->system_flags, _hoops_RGRI) ||
			   !ANYBIT (_hoops_IHCR->heuristics, _hoops_RSA)) {
				_hoops_RRIRC = _hoops_PRIRC;
				_hoops_CCIRC = false;
			}
		}

		if (_hoops_IAHC || synthetic_params || _hoops_RRIRC == _hoops_PRIRC) {
			if (_hoops_CSRGR->_hoops_CIGI)
				_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_GCGI;
			if (BIT(ts->_hoops_SRHA, DL_DO_NOT_RECOMPILE)) {
				/* _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_AIRI _hoops_HIGR _hoops_RGAR, _hoops_SIHH _hoops_RH _hoops_PPPS _hoops_SIHC _hoops_GGR _hoops_AGR _hoops_IS _hoops_CAH */
				Tristrip alter *_hoops_RPIAR = (Tristrip alter *) ts;
				_hoops_GACR alter *dl;

				ENSURE_LIST_BASE(_hoops_CSRGR, 0);
				_hoops_AACR(nr, &_hoops_RPIAR->_hoops_GAHA, &dl, &odl, OGL_DL_GEOMETRY);
				HD_Queue_Destroy_List (odl, true);
				return;
			}
			if (_hoops_IAHC) {
				HD_Std_3D_Tristrip (nr, ts);
				return;
			}
		}

		/* _hoops_HHIGR _hoops_HRGR _hoops_HAR _hoops_ICIC _hoops_IS _hoops_CAH _hoops_GRHCP _hoops_RGR _hoops_PPSR */

		if (_hoops_CSRGR->_hoops_ISCI > 0)
		{
			if (BIT(ts->_hoops_SRHA, DL_DO_NOT_RECOMPILE)) {
				_hoops_SCARC (nr, ts);
				return;
			}

			if (_hoops_RRIRC != _hoops_PRIRC &&
				!BIT (ts->_hoops_SRHA, DL_SUPPRESS_SEGMENT_DISPLAY_LISTS)) {

				if (ts->_hoops_AIHA == null)
					return;

				if (!ts->_hoops_PCHA &&
					!ts->_hoops_HCHA && 
					!ts->_hoops_PAGI &&
					nr->_hoops_IHA->_hoops_CPA != _hoops_CSRGR->_hoops_CIGI->nr->_hoops_IHA->_hoops_CPA)
					_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_PGRI;

#ifdef _hoops_GCGGC
				if (ts->_hoops_GSHA > 5 &&
					_hoops_ACGGC(dc->_hoops_RIGC->thread_id) != null)
					_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_PGRI;
#endif

				if (!_hoops_CSRGR->_hoops_CIGI->_hoops_RCGI)
					_hoops_CSRGR->_hoops_CIGI->_hoops_RCGI = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);

				if (BIT(ts->_hoops_SRHA, DL_TEMPORARY_DATA)) {
					HD_Isolate_Tristrip_Data (dc, ts);
				}
				else if (ts->_hoops_GSSH && BIT (ts->_hoops_SRHA, _hoops_GGIA) &&
					!BIT (ts->_hoops_GSSH->_hoops_SCAI, _hoops_ARCC)) {
					Tristrip alter *		_hoops_RPIAR = (Tristrip alter *) ts;

					_hoops_APRGA(ts->_hoops_GSSH->_hoops_CCHA, ts->point_count * ts->_hoops_GSSH->_hoops_GSHA, _hoops_RSSH, _hoops_RPIAR->_hoops_GSSH->_hoops_CCHA);
					_hoops_RPIAR->_hoops_GSSH->_hoops_CGAHR = ts->point_count;
					_hoops_RPIAR->_hoops_GSSH->_hoops_SCAI |= _hoops_ARCC;
				}

				Tristrip alter *_hoops_IPIAR = (Tristrip alter *)ts;
				_hoops_IPIAR->_hoops_CARI |= _hoops_SARI;

				_hoops_IPSGC *pair = POOL_NEW(dc->memory_pool, _hoops_IPSGC)(nr, ts, dc->_hoops_SPA->modelling_matrix, null);

				_hoops_CSRGR->_hoops_CIGI->_hoops_RCGI->AddFirst(pair);
				return;
			}
			_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_PGRI;
			if (_hoops_CSRGR->_hoops_CIGI->_hoops_IHGI)
				return;
		}
		if (_hoops_SIGA->pattern == FP_USER_DEFINED) {
			if (_hoops_SIGA->_hoops_PGPH != null && _hoops_SIGA->_hoops_PGPH->stipple)
				_hoops_RASP = _hoops_SIGA->_hoops_PGPH->stipple;
			else
				_hoops_GPIAR = 1;
		}
		if (BIT (_hoops_IHCR->flags, _hoops_CSP)) {
			if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH)
				_hoops_CAPA = _hoops_IHCR->_hoops_RGH->_hoops_IRH;
			else
				_hoops_CAPA = _hoops_IHCR->_hoops_RGH->_hoops_PHCA;
		}
		_hoops_PIPRC = _hoops_CAPA;
		/* _hoops_AIR _hoops_AISR _hoops_ISPR */
		if (_hoops_SIGA->_hoops_AGP &&
			matr->_hoops_SCA &&
			!_hoops_CSRGR->_hoops_RIRGC) {
			_hoops_AS const *light = _hoops_SIGA->_hoops_AGP->_hoops_CGR;
			while (light != null) {
				if (light->_hoops_PRR == _hoops_I) {
					_hoops_CSRGR->_hoops_AIRGC = true;
					break;
				}
				light = light->next;
			}
		}

		ZERO_STRUCT(rc, OGL_Render_Control);
		/* _hoops_ARAR _hoops_SGS _hoops_HS _hoops_HSP _hoops_AIRC _hoops_CHASA _hoops_RH _hoops_HSPR _hoops_CCA _hoops_ARGHC */
		_hoops_CIIPP = 0x7fffffff; //_hoops_HGPGA->_hoops_ASHGC->_hoops_PRGHC;
		if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_NONDL_VERTEX_ARRAYS))
			_hoops_CCIRC = false;

		_hoops_SAARC (nr, rc, ts);

		_hoops_GGGH(_hoops_CSRGR, nr);
		/* _hoops_IRAA _hoops_PICP _hoops_IIGR _hoops_IRS _hoops_HRGHC _hoops_IIGR _hoops_IRGHC _hoops_GGR _hoops_PGAP _hoops_RH _hoops_HSAGA _hoops_IIGR _hoops_CRGHC
		 * _hoops_PAH _hoops_SHH _hoops_GCGP */
		if (_hoops_CSRGR->_hoops_GGCGC) {
			if (!matrix)
				_hoops_SAHRC (_hoops_CSRGR, nr->transform_rendition, false);
		}
		else {
			if (BIT (ts->_hoops_SRHA, DL_NEGATIVE_3X3))
				_hoops_SAHRC (_hoops_CSRGR, nr->transform_rendition, true);
		}
		_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
		_hoops_PIIGC(_hoops_CSRGR, nr);
		ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
		ENSURE_TRANSPARENCY (_hoops_CSRGR, nr->_hoops_CPP->_hoops_PRH._hoops_HRH && !_hoops_RASP);
		_hoops_IPGP(_hoops_CSRGR, BIT(nr->transform_rendition->flags, _hoops_CASP));


#if 0
		if (ts->_hoops_GPPPI) {
			/* _hoops_SR _hoops_PAH _hoops_ARP _hoops_RH _hoops_HAIR _hoops_ARR _hoops_PPR _hoops_PSCR _hoops_HPRAR _hoops_CRGR _hoops_RH _hoops_ARACP _hoops_ARAR */
			if (_hoops_PCHA != null) {
				/* _hoops_SGH _hoops_CIHA _hoops_IIGR _hoops_SRS _hoops_PPSR */
				glColor3fv ((float const *) &_hoops_PCHA[_hoops_AIHA[0]]);
				_hoops_CSRGR->_hoops_CSC.color = _hoops_CAHSR::_hoops_SAHSR;
				_hoops_PCHA = null;
			}
			else if (_hoops_PAGI != null) {
				/* _hoops_SGH _hoops_CIHA _hoops_IIGR _hoops_SRS _hoops_HSP (_hoops_IHIA _hoops_CCA _hoops_HRSSR _hoops_PPSR) */
				glColor3fv ((float const *)
							&_hoops_PAGI[face_indices?face_indices[2]:0]);
				_hoops_CSRGR->_hoops_CSC.color = _hoops_CAHSR::_hoops_SAHSR;
				_hoops_PAGI = null;
			}
		}
#endif
	}

	if (_hoops_RRIRC == _hoops_PRIRC) {
		_hoops_HRIRC (_hoops_CSRGR, nr);
	}

	if (_hoops_ACHI->_hoops_GAHA &&
		!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC &&
		!BIT(ts->_hoops_SRHA, DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS) &&
		_hoops_CSRGR->_hoops_RRSGC &&
		_hoops_RRIRC != _hoops_PRIRC) {
		Tristrip alter *_hoops_RPIAR = (Tristrip alter *) ts;
		_hoops_GACR alter *dl;
		bool _hoops_RACR = false;
		bool _hoops_GCPS = false;
		bool _hoops_SRGHC = false;
		unsigned int error;

		ENSURE_LIST_BASE(_hoops_CSRGR, 0);

		_hoops_RACR = _hoops_AACR(nr, &_hoops_RPIAR->_hoops_GAHA, &dl, &odl, OGL_DL_GEOMETRY);

		if (!_hoops_RACR) {
			if  (odl->type != OGL_DL_GEOMETRY) {
			    HD_Queue_Destroy_List (odl, true);
				_hoops_RACR = _hoops_AACR(nr, &_hoops_RPIAR->_hoops_GAHA, &dl, &odl, OGL_DL_GEOMETRY);
			}
			else 
				_hoops_GCPS = _hoops_RPRC (nr, ts, dl, odl);
			_hoops_SRGHC = (odl->item.geometry.id == _hoops_RSARR);
		}


		if (_hoops_RACR) {
			error = glGetError ();
			/* _hoops_CAHP _hoops_SPR _hoops_PPRAR _hoops_AIRI _hoops_HIGR _hoops_CRSRR */
			odl->item.geometry.id = glGenLists(1);
			if (!glIsList(odl->item.geometry.id)) {
				/* _hoops_PISPR _hoops_IRS _hoops_ISPC _hoops_HIGR _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_GRHP _hoops_IRCC */
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					"OpenGL reported an error during display list creation in draw_3d_tristrip");
				odl->item.geometry.id = _hoops_RSARR;
			}
			odl->_hoops_CARH = 16 * ts->total;
			if (ts->_hoops_ICHA || ts->_hoops_PRHH)
				odl->_hoops_CARH += 12 * ts->total;
			if (_hoops_CGGHC && _hoops_CGGHC->_hoops_CCHA)
				odl->_hoops_CARH += ts->total * ts->_hoops_GSSH->_hoops_GSHA * sizeof(_hoops_RSSH);
			if (HOOPS_WORLD->display_list_vram_usage + odl->_hoops_CARH > HOOPS_WORLD->_hoops_PHARR) {
				dl->_hoops_AGRI |= DL_INSUFFICIENT_VRAM;
				odl->item.geometry.id = _hoops_RSARR; /* _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_GRHP _hoops_IRCC */
				odl->_hoops_CARH = 0;
				_hoops_SRGHC = true;
			}
			else
				HOOPS_WORLD->display_list_vram_usage += odl->_hoops_CARH;
		}
		if (rc->txr[rc->pass] && _hoops_CGGHC && _hoops_CGGHC->_hoops_SCAI != odl->item.geometry.param_flags[0])
			_hoops_GCPS = false;

		if (rc->_hoops_GCI[rc->pass] == _hoops_HCSGC &&
			_hoops_IHCR->_hoops_SPH->projection != _hoops_GHH)
			_hoops_SRGHC = true;

		/* _hoops_CASRR, _hoops_RPP _hoops_HAHH */
		if (!_hoops_GCPS && !_hoops_SRGHC) {
		    if (BIT(ts->_hoops_SRHA, DL_DO_NOT_RECOMPILE)) {
			    /* _hoops_RH _hoops_CRHH _hoops_ASSP'_hoops_RA _hoops_SCIR _hoops_RH _hoops_HAHH _hoops_SIHC _hoops_GGR _hoops_AGR _hoops_IS _hoops_HRSPR. */
			    HD_Queue_Destroy_List (odl, true);
			    return;
		    }
			/* _hoops_ISIA _hoops_GAR _hoops_IRS _hoops_HSCI _hoops_IS _hoops_IRHH _hoops_HSIRC _hoops_SIGC */
			if (!_hoops_RACR)
				_hoops_RCCA(_hoops_SGAGR)++;
			/* _hoops_CASRR _hoops_RH _hoops_HIGR */
			glNewList (odl->item.geometry.id, GL_COMPILE);
			_hoops_CSRGR->_hoops_CSC._hoops_IPAGC = true;
			_hoops_CSRGR->_hoops_CSC._hoops_SCIRC = true;
			old_draw_3d_tristrip(nr, ts); /* _hoops_GHHA */
			_hoops_CSRGR->_hoops_CSC._hoops_SCIRC = false;
			_hoops_CSRGR->_hoops_CSC._hoops_IPAGC = false;
			glEndList ();

			if ((error = glGetError ()) != 0) {
				/* _hoops_CIH _hoops_SCH _hoops_PPR _hoops_GRHHR _hoops_IH _hoops_RH _hoops_AAH */
				glDeleteLists (odl->item.geometry.id, 1);
				/* _hoops_PISPR _hoops_IRS _hoops_ISPC _hoops_HIGR _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_GRHP _hoops_IRCC */
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					"OpenGL reported an error during display list compilation in old_draw_3d_tristrip");
				odl->item.geometry.id = _hoops_RSARR;
			}

			dl->_hoops_GSAI = ts->_hoops_GSAI;
			odl->item.geometry._hoops_GSAI = ts->_hoops_GSAI;
			odl->item.geometry._hoops_SRHA = dl->_hoops_AGRI = ts->_hoops_SRHA;
			odl->item.geometry._hoops_CARI = ts->_hoops_CARI;
			odl->item.geometry._hoops_IRRI = ts->face_attributes.flags;
			odl->item.geometry.param_width = _hoops_CGGHC ? _hoops_CGGHC->_hoops_GSHA : 0;
			odl->item.geometry.param_flags[0] = _hoops_CGGHC ? _hoops_CGGHC->_hoops_SCAI : 0;
		}


		/* _hoops_HSSC _hoops_RHIR _hoops_PPR _hoops_PGSA _hoops_CIPH _hoops_RH _hoops_GSSR _hoops_PPRRR */
		if (odl->item.geometry.id == _hoops_RSARR)
			odl = null;
	}

	/* _hoops_HAR _hoops_ICIC _hoops_IS _hoops_CAH _hoops_IS _hoops_GAGHC _hoops_RAS _hoops_RGR _hoops_PPSR */

_hoops_RAGHC:

	if (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC) {
		pre_pass(nr, rc, ts);
		if (_hoops_CSRGR->_hoops_GSGRR) {
			//_hoops_HAHH _hoops_RGAR _hoops_PGGA _hoops_HGPGA->_hoops_IHAH._hoops_AAGHC _hoops_SIAS _hoops_AGRP _hoops_GAPA _hoops_HHHH _hoops_GPP _hoops_SHPP _hoops_ICCI
			_hoops_PIIGC(_hoops_CSRGR, nr);
		}
		_hoops_CCHA = rc->params[rc->pass];
		_hoops_CCHA += rc->_hoops_RSCP[rc->pass];
		_hoops_GSHA = rc->param_width[rc->pass];
		_hoops_IGGHC = rc->flags[rc->pass];
		if (BIT(rc->flags[rc->pass], _hoops_RGCGC)) {
			OGL_SET_HANDEDNESS (_hoops_CSRGR, _hoops_IHCR, rc->flags[rc->pass]);
			if (BIT(rc->flags[rc->pass],_hoops_AGCGC))
				_hoops_RRIRC = _hoops_IIHAC;
		}
	}
	else {
		/* _hoops_SHIR _hoops_IH _hoops_AIRI _hoops_HIGR*/
		if (_hoops_CGGHC && !_hoops_CGGHC->_hoops_CCHA &&
			ALLBITS(ts->_hoops_SRHA, _hoops_GGIA | DL_INDEX_INTERPOLATION)) {
			pre_pass(nr, rc, ts);
			_hoops_CCHA = rc->params[rc->pass];
			_hoops_CCHA += rc->_hoops_RSCP[rc->pass];
			_hoops_GSHA = rc->param_width[rc->pass];
		}
		else {
			_hoops_CCHA = _hoops_CGGHC ? _hoops_CGGHC->_hoops_CCHA : 0;
			_hoops_GSHA = _hoops_CGGHC ? _hoops_CGGHC->_hoops_GSHA : 0;
		}
		if (_hoops_CGGHC && BIT (_hoops_CGGHC->_hoops_SCAI, _hoops_HPPAR))
			_hoops_IGGHC = _hoops_RHARC;
		else
			_hoops_IGGHC = 0;
		if (!_hoops_CSRGR->_hoops_CSC._hoops_SCIRC) {
			if (dc->_hoops_SPA->modelling_matrix) {
				matrix = &dc->_hoops_SPA->modelling_matrix->matrix;
				_hoops_CCIRC = false;
			}
		}
	}
	if (_hoops_CSRGR->_hoops_SPGRC)
		_hoops_CCIRC = false;

	if (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC) {
		_hoops_PRHA =   (rc->txr[rc->pass] ||
								rc->param_width[rc->pass] ||
								_hoops_PCHA ||
								_hoops_ICHA ||
								BIT (ts->_hoops_SRHA, DL_FORCE_SMOOTH_SHADE_MODEL));
		if (_hoops_PRHA)
			ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_SMOOTH);
		else
			ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_FLAT);

		if (_hoops_RASP) {
			int _hoops_PHPSR;
			const unsigned char *pattern;

			_hoops_PHPSR = (int)(64 - _hoops_RASP);
			pattern = _hoops_HRPH[_hoops_PHPSR];
			/* _hoops_IRCH _hoops_HSGP _hoops_HII 8x8 _hoops_IS 8x32 */
			for (i = 0; i < 8; i++) {
				stipple[i] = pattern[i];
				stipple[i] |= stipple[i] << 8;
				stipple[i] |= stipple[i] << 16;
			}
			/* _hoops_IRCH _hoops_HSGP _hoops_HII 8x32 _hoops_IS 32x32 */
			_hoops_AIGA (stipple,  8, unsigned int, stipple+8);
			_hoops_AIGA (stipple, 16, unsigned int, stipple+16);
			glEnable (GL_POLYGON_STIPPLE);
			glPolygonStipple ((GLubyte const *)stipple);
		}
		else if (_hoops_GPIAR) {
			for (i = 0; i < _hoops_SIGA->_hoops_PGPH->height; i++) {
				int		index = _hoops_SIGA->_hoops_PGPH->height-1 - i;

				stipple[index] = 0;
				for (j = 0; j < _hoops_SIGA->_hoops_PGPH->width; j++) {
					if (_hoops_SIGA->_hoops_PGPH->pattern[i*_hoops_SIGA->_hoops_PGPH->width + j] == 0)
						stipple[index] |= 1 << (_hoops_SIGA->_hoops_PGPH->width-1 - j);
				}
				while (j<32) {
					stipple[index] |= stipple[index]<<j;
					j <<= 1;
				}
			}
			while (i<32) {
				_hoops_AIGA (stipple, i, unsigned int, stipple+i);
				i <<= 1;
			}
			glEnable (GL_POLYGON_STIPPLE);
			glPolygonStipple ((GLubyte const *)stipple);
		}

		if (_hoops_GSHA && !_hoops_RASP &&
			nr->_hoops_CPP->_hoops_PRH.style == _hoops_GCPI &&
			rc->pass == 0) {
			if (rc->txr[rc->pass] && BIT(rc->txr[rc->pass]->flags, _hoops_IAPS)) {
				_hoops_RASP = 32;	/* 50% */
				ENSURE_TRANSPARENCY (_hoops_CSRGR, false);
			}
		}

		if (_hoops_PCHA || _hoops_PAGI) {
			_hoops_GASGC (_hoops_CSRGR, GL_FRONT_AND_BACK);
		}
	}

	if (!_hoops_GPIAR || _hoops_SIGA->_hoops_PGPH->_hoops_ACHHP != UPAT_NO_FACE)
	do {
		if (_hoops_CAPA != null) {
			_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
		}
	/*_hoops_GRAA-_hoops_HPRGR _hoops_PAGHC*/

	if (!ANYBIT(rc->flags[rc->pass], _hoops_CIGRC) &&
		!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC &&
		odl &&
		!BIT(_hoops_IGGHC, _hoops_AGRRC) &&
		rc->_hoops_RSCP[rc->pass] == 0 &&
		!_hoops_CSRGR->_hoops_SPGRC && 
		(!rc->txr[rc->pass] || (_hoops_CGGHC && (_hoops_CGGHC->_hoops_SCAI == odl->item.geometry.param_flags[0])) )) {

		/*------------------------------*\
		 *  _hoops_HAGHC _hoops_RCSPR _hoops_HPARR _hoops_IPARR    *
		\*------------------------------*/
		ASSERT (odl->type == OGL_DL_GEOMETRY);
 		glCallList (odl->item.geometry.id);
		odl->_hoops_GPPI = HOOPS_WORLD->_hoops_GPPI;
		_hoops_GPRH(_hoops_GGCAR)++;
		_hoops_GPRH(_hoops_AGCAR) += ts->total - 2*ts->_hoops_PHHA;

		if (dc->_hoops_PGCAR > 0 &&
			_hoops_GPRH(_hoops_AGCAR) > _hoops_GPRH(_hoops_HGCAR)+dc->_hoops_PGCAR) {
			_hoops_GPRH(_hoops_HGCAR) = _hoops_GPRH(_hoops_AGCAR);
			_hoops_GPRH(_hoops_IGCAR)++;
			//_hoops_IAGHC();
			glFinish();
		}
	}
	else {
		int data_type;

		/* _hoops_IH _hoops_SCIRA _hoops_RGSSA _hoops_RSPH _hoops_GRRI */
		if (BIT(ts->_hoops_SRHA, DL_DO_NOT_RECOMPILE)) {
			/* _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_AIRI _hoops_HIGR _hoops_RGAR, _hoops_SIHH _hoops_RH _hoops_PPPS _hoops_SIHC _hoops_GGR _hoops_AGR _hoops_IS _hoops_CAH */
			Tristrip alter *_hoops_RPIAR = (Tristrip alter *) ts;
			_hoops_GACR alter *dl;

			ENSURE_LIST_BASE(_hoops_CSRGR, 0);
			_hoops_AACR(nr, &_hoops_RPIAR->_hoops_GAHA, &dl, &odl, OGL_DL_GEOMETRY);
			HD_Queue_Destroy_List (odl, true);
			return;
		}
	/*_hoops_GRAA-_hoops_HPRGR _hoops_PAGHC*/
	_hoops_GPRH(_hoops_GRHAR)++;
	_hoops_GPRH(_hoops_PCCA) += ts->total - 2*ts->_hoops_PHHA;

	if (_hoops_CCHA || ts->_hoops_HCHA) {
		if (BIT (_hoops_IGGHC, _hoops_RHARC) && !BIT(rc->flags[rc->pass], _hoops_CIGRC)) {
			/*_hoops_ASSIP _hoops_CAGHC*/
			data_type = _hoops_SAGHC;
		}
		else {
			if (_hoops_ICHA) {
				/*_hoops_ASSIP*/
				if (BIT(rc->flags[rc->pass], _hoops_CIGRC))
					data_type = _hoops_GPGHC;
				else
					data_type = _hoops_PSSIP;
			}
			else if (_hoops_PRHH) {
				/*_hoops_HSSIP*/
				data_type = _hoops_ISSIP;
			}
			else {
				/*_hoops_CSSIP*/
				data_type = _hoops_SSSIP;
			}
		}

#if 0
		switch (rc->param_width[rc->pass]) {
			case 1:
				gltextcoord = glTexCoord1fv;
				break;
			case 2:
				gltextcoord = glTexCoord2fv;
				break;
			case 3:
				gltextcoord = glTexCoord3fv;
				break;
			case 4:
			default:
				gltextcoord = glTexCoord4fv;
				break;
		}
#endif

	}
	else {
		if (_hoops_PCHA) {
			if (_hoops_ICHA) {
				/*_hoops_GGGCP*/
				data_type = _hoops_RGGCP;
			}
			else if (_hoops_PRHH) {
				/*_hoops_AGGCP*/
				data_type = _hoops_PGGCP;
			}
			else {
				/*_hoops_HGGCP*/
				data_type = _hoops_IGGCP;
			}
		}
		else {
			if (_hoops_PAGI) {
				if (_hoops_ICHA) {
					/*_hoops_CGGCP*/
					data_type = _hoops_SGGCP;
				}
				else if (_hoops_PRHH) {
					/*_hoops_GRGCP*/
					data_type = _hoops_RRGCP;
				}
				else {
					/*_hoops_ARGCP*/
					data_type = _hoops_PRGCP;
				}
			}
			else {
				if (_hoops_ICHA) {
					/*_hoops_HRGCP*/
					data_type = _hoops_IRGCP;
				}
				else if (_hoops_PRHH) {
					/*_hoops_CRGCP*/
					data_type = _hoops_SRGCP;
				}
				else {
					/*_hoops_GAGCP*/
					data_type = _hoops_RAGCP;
				}
			}
		}
	}

	_hoops_SSPAR = -1;

	switch (data_type) {
#ifndef DISABLE_TEXTURING
#ifndef DISABLE_EXTENDED_TEXTURE
	case _hoops_SAGHC: {
		/*_hoops_ASSIP _hoops_CAGHC*/
		_hoops_RSSH _hoops_CCHAR[3], _hoops_SCHAR[3], _hoops_GSHAR[3];

		if (matrix &&
			(_hoops_ICHA || _hoops_PRHH) &&
			matrix->_hoops_APRA == null)
			HI_Validate_Matrix_Adjoint((_hoops_HRPA alter *)matrix);

		j=0;
		glBegin (GL_TRIANGLES);
		for (i=0; i<_hoops_PHHA; i++) {
			_hoops_SAHAR = j + lengths[i];
			_hoops_HCIRC = _hoops_AIHA[j];
			j++;
			_hoops_AGGHC = _hoops_AIHA[j];
			j++;
			while (1) {
				_hoops_HCGS = _hoops_AIHA[j];
				if (face_indices)
					_hoops_SSPAR = face_indices[j];
				else
					_hoops_SSPAR++;

				COPY_PARAMETER(&_hoops_CCHA[_hoops_HCIRC*_hoops_GSHA],_hoops_CCHAR,3);
				COPY_PARAMETER(&_hoops_CCHA[_hoops_AGGHC*_hoops_GSHA],_hoops_SCHAR,3);
				COPY_PARAMETER(&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA],_hoops_GSHAR,3);

				if (_hoops_CCHAR[0] == 0.0f) _hoops_CCHAR[0] = 0.5f * (_hoops_SCHAR[0]+_hoops_GSHAR[0]);
				if (_hoops_SCHAR[0] == 0.0f) _hoops_SCHAR[0] = 0.5f * (_hoops_CCHAR[0]+_hoops_GSHAR[0]);
				if (_hoops_GSHAR[0] == 0.0f) _hoops_GSHAR[0] = 0.5f * (_hoops_CCHAR[0]+_hoops_SCHAR[0]);
#define _hoops_PRPAR 0.7f
				while (_hoops_CCHAR[0]-_hoops_SCHAR[0] > _hoops_PRPAR) _hoops_SCHAR[0] += 1.0f;
				while (_hoops_CCHAR[0]-_hoops_GSHAR[0] > _hoops_PRPAR) _hoops_GSHAR[0] += 1.0f;
				while (_hoops_SCHAR[0]-_hoops_CCHAR[0] > _hoops_PRPAR) _hoops_CCHAR[0] += 1.0f;
				while (_hoops_SCHAR[0]-_hoops_GSHAR[0] > _hoops_PRPAR) _hoops_GSHAR[0] += 1.0f;
				while (_hoops_GSHAR[0]-_hoops_CCHAR[0] > _hoops_PRPAR) _hoops_CCHAR[0] += 1.0f;
				while (_hoops_GSHAR[0]-_hoops_SCHAR[0] > _hoops_PRPAR) _hoops_SCHAR[0] += 1.0f;

				if (_hoops_PRHH) {
					if (matrix) {
						_hoops_ARPA _hoops_RPGHC;
						_hoops_GIRAC (matrix, _hoops_PRHH[_hoops_SSPAR], _hoops_RPGHC);
						_hoops_CIHAC (_hoops_RRIRC, _hoops_RPGHC, _hoops_CSRGR->_hoops_SRIRC);
					}
					else
						_hoops_CIHAC (_hoops_RRIRC, _hoops_PRHH[_hoops_SSPAR], _hoops_CSRGR->_hoops_SRIRC);
				}

				if (!BIT(rc->flags[rc->pass], _hoops_CIGRC)) {
					glTexCoord2fv (_hoops_CCHAR);
				}
				else {
					(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, _hoops_CCHAR);
				    (*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, _hoops_CCHAR);
					glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCIRC]);
				}
				if (matrix) {
					if (_hoops_ICHA)
						_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCIRC], points[_hoops_HCIRC]);
					else
						_hoops_CAIRC (matrix,  points[_hoops_HCIRC]);
				}
				else {
					if (_hoops_ICHA)
						_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCIRC], points[_hoops_HCIRC], _hoops_CSRGR->_hoops_SRIRC);
					glVertex3fv (&points[_hoops_HCIRC].x);
				}


				if (!BIT(rc->flags[rc->pass], _hoops_CIGRC)) {
					glTexCoord2fv (_hoops_SCHAR);
				}
				else {
					(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, _hoops_SCHAR);
				    (*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, _hoops_SCHAR);
					glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_AGGHC]);
				}
				if (matrix) {
					if (_hoops_ICHA)
						_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_AGGHC], points[_hoops_AGGHC]);
					else
						_hoops_CAIRC (matrix,  points[_hoops_AGGHC]);
				}
				else {
					if (_hoops_ICHA)
						_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_AGGHC], points[_hoops_AGGHC], _hoops_CSRGR->_hoops_SRIRC);
					glVertex3fv (&points[_hoops_AGGHC].x);
				}

				if (!BIT(rc->flags[rc->pass], _hoops_CIGRC)) {
					glTexCoord2fv (_hoops_GSHAR);
				}
				else {
					(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, _hoops_GSHAR);
				    (*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, _hoops_GSHAR);
					glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCGS]);
				}
				if (matrix) {
					if (_hoops_ICHA)
						_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS]);
					else
						_hoops_CAIRC (matrix,  points[_hoops_HCGS]);
				}
				else {
					if (_hoops_ICHA)
						_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
					glVertex3fv (&points[_hoops_HCGS].x);
				}
				_hoops_HCIRC = _hoops_AGGHC;
				_hoops_AGGHC = _hoops_HCGS;

				j++;
				if (j==_hoops_SAHAR) break;

				_hoops_HCGS = _hoops_AIHA[j];
				if (face_indices)
					_hoops_SSPAR = face_indices[j];
				else
					_hoops_SSPAR++;

				COPY_PARAMETER(&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA],_hoops_CCHAR,3);
				COPY_PARAMETER(&_hoops_CCHA[_hoops_AGGHC*_hoops_GSHA],_hoops_SCHAR,3);
				COPY_PARAMETER(&_hoops_CCHA[_hoops_HCIRC*_hoops_GSHA],_hoops_GSHAR,3);

				if (_hoops_CCHAR[0] == 0.0f) _hoops_CCHAR[0] = 0.5f * (_hoops_SCHAR[0]+_hoops_GSHAR[0]);
				if (_hoops_SCHAR[0] == 0.0f) _hoops_SCHAR[0] = 0.5f * (_hoops_CCHAR[0]+_hoops_GSHAR[0]);
				if (_hoops_GSHAR[0] == 0.0f) _hoops_GSHAR[0] = 0.5f * (_hoops_CCHAR[0]+_hoops_SCHAR[0]);

				while (_hoops_CCHAR[0]-_hoops_SCHAR[0] > _hoops_PRPAR) _hoops_SCHAR[0] += 1.0f;
				while (_hoops_CCHAR[0]-_hoops_GSHAR[0] > _hoops_PRPAR) _hoops_GSHAR[0] += 1.0f;
				while (_hoops_SCHAR[0]-_hoops_CCHAR[0] > _hoops_PRPAR) _hoops_CCHAR[0] += 1.0f;
				while (_hoops_SCHAR[0]-_hoops_GSHAR[0] > _hoops_PRPAR) _hoops_GSHAR[0] += 1.0f;
				while (_hoops_GSHAR[0]-_hoops_CCHAR[0] > _hoops_PRPAR) _hoops_CCHAR[0] += 1.0f;
				while (_hoops_GSHAR[0]-_hoops_SCHAR[0] > _hoops_PRPAR) _hoops_SCHAR[0] += 1.0f;

				if (_hoops_PRHH) {
					if (matrix) {
						_hoops_ARPA _hoops_RPGHC;
						_hoops_GIRAC (matrix, _hoops_PRHH[_hoops_SSPAR], _hoops_RPGHC);
						_hoops_CIHAC (_hoops_RRIRC, _hoops_RPGHC, _hoops_CSRGR->_hoops_SRIRC);
					}
					else
						_hoops_CIHAC (_hoops_RRIRC, _hoops_PRHH[_hoops_SSPAR], _hoops_CSRGR->_hoops_SRIRC);
				}

				if (!BIT(rc->flags[rc->pass], _hoops_CIGRC)) {
					glTexCoord2fv (_hoops_CCHAR);
				}
				else {
					(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, _hoops_CCHAR);
				    (*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, _hoops_CCHAR);
					glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCGS]);
				}
				if (matrix) {
					if (_hoops_ICHA)
						_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS]);
					else
						_hoops_CAIRC (matrix,  points[_hoops_HCGS]);
				}
				else {
					if (_hoops_ICHA)
						_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
					glVertex3fv (&points[_hoops_HCGS].x);
				}

				if (!BIT(rc->flags[rc->pass], _hoops_CIGRC)) {
					glTexCoord2fv (_hoops_SCHAR);
				}
				else {
					(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, _hoops_SCHAR);
				    (*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, _hoops_SCHAR);
					glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_AGGHC]);
				}
				if (matrix) {
					if (_hoops_ICHA)
						_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_AGGHC], points[_hoops_AGGHC]);
					else
						_hoops_CAIRC (matrix,  points[_hoops_AGGHC]);
				}
				else {
					if (_hoops_ICHA)
						_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_AGGHC], points[_hoops_AGGHC], _hoops_CSRGR->_hoops_SRIRC);
					glVertex3fv (&points[_hoops_AGGHC].x);
				}


				if (!BIT(rc->flags[rc->pass], _hoops_CIGRC)) {
					glTexCoord2fv (_hoops_GSHAR);
				}
				else {
					(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, _hoops_GSHAR);
				    (*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, _hoops_GSHAR);
					glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCIRC]);
				}
				if (matrix) {
					if (_hoops_ICHA)
						_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCIRC], points[_hoops_HCIRC]);
					else
						_hoops_CAIRC (matrix,  points[_hoops_HCIRC]);
				}
				else {
					if (_hoops_ICHA)
						_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCIRC], points[_hoops_HCIRC], _hoops_CSRGR->_hoops_SRIRC);
					glVertex3fv (&points[_hoops_HCIRC].x);
				}

				_hoops_HCIRC = _hoops_AGGHC;
				_hoops_AGGHC = _hoops_HCGS;
				j++;
				if (j==_hoops_SAHAR) break;
			}
		}
		glEnd ();

	}break;
#endif /* _hoops_APGHC */
#endif /* _hoops_AHCAC */

#ifndef _hoops_SIGGC
	case _hoops_GPGHC: {
		int _hoops_PGCRC = 0;
		j=0;
		if (dc->_hoops_CGHAR == null)  {
			if (_hoops_CCIRC && ts->total >= _hoops_HGGHC) {
				_hoops_HGCRC(_hoops_CSRGR);
				_hoops_CPPRC(_hoops_CSRGR);
				ENSURE_COLOR_ARRAY_ON(_hoops_CSRGR);
				glNormalPointer(GL_FLOAT, 0, _hoops_ICHA);

				ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,0,true);
				glTexCoordPointer(_hoops_GSHA, GL_FLOAT, 0, _hoops_CCHA);

				ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,1,true);
				glTexCoordPointer(_hoops_GSHA, GL_FLOAT, 0, _hoops_CCHA);
				_hoops_IHRRC(_hoops_CSRGR,0);

				glColorPointer(3, GL_FLOAT, 0, rc->_hoops_IARRC._hoops_PHRRC);
 				glVertexPointer(3, GL_FLOAT, 0, points);

				for (i = 0; i < _hoops_PHHA; i++) {
					if (lengths[i] > 0) {
						if (lengths[i] < _hoops_CIIPP)
							_hoops_PGCRC += lengths[i] - 2;
						else
							glDrawElements(GL_TRIANGLE_STRIP, lengths[i], GL_UNSIGNED_INT, &_hoops_AIHA[j]);
						j += lengths[i];
					}
					else {
						if (-lengths[i] < _hoops_CIIPP)
							_hoops_PGCRC += -lengths[i] - 2;
						else
							glDrawElements(GL_TRIANGLE_FAN, -lengths[i], GL_UNSIGNED_INT, &_hoops_AIHA[j]);
						j += -lengths[i];
					}
				}
				if (_hoops_PGCRC) {
					int *_hoops_RGCRC, *_hoops_AGCRC;

					j = 0;
					if (!_hoops_CSRGR->_hoops_IHSGC)
						ALLOC_ARRAY(_hoops_CSRGR->_hoops_IHSGC, _hoops_CHSGC, int);
					_hoops_RGCRC = _hoops_CSRGR->_hoops_IHSGC;
					_hoops_AGCRC = _hoops_RGCRC;
					for (i = 0; i < _hoops_PHHA; i++) {
						if (lengths[i] > 0) {
							if (lengths[i] < _hoops_CIIPP) {
								if (_hoops_AGCRC - _hoops_RGCRC + (lengths[i]-2)*3 >= _hoops_CHSGC) {
									glDrawElements(GL_TRIANGLES, _hoops_AGCRC - _hoops_RGCRC, GL_UNSIGNED_INT, _hoops_RGCRC);
									_hoops_AGCRC = _hoops_RGCRC;
								}
								_hoops_SAHAR = j+lengths[i];
								j += 2;
								while (j<_hoops_SAHAR) {
									*_hoops_AGCRC++ = _hoops_AIHA[ j-2 ];
									*_hoops_AGCRC++ = _hoops_AIHA[ j-1 ];
									*_hoops_AGCRC++ = _hoops_AIHA[ j ];
									j++;
									if (j == _hoops_SAHAR)
										break;
									*_hoops_AGCRC++ = _hoops_AIHA[ j ];
									*_hoops_AGCRC++ = _hoops_AIHA[ j-1 ];
									*_hoops_AGCRC++ = _hoops_AIHA[ j-2 ];
									j++;
								}
							}
							else
								j += lengths[i];
						}
						else {
							if (-lengths[i] < _hoops_CIIPP) {
								if (_hoops_AGCRC - _hoops_RGCRC + (-(lengths[i]-2)*3) >= _hoops_CHSGC) {
									glDrawElements(GL_TRIANGLES, _hoops_AGCRC - _hoops_RGCRC, GL_UNSIGNED_INT, _hoops_RGCRC);
									_hoops_AGCRC = _hoops_RGCRC;
								}
								_hoops_SAHAR = j + (-lengths[i]);
								_hoops_HCIRC = _hoops_AIHA[j]; /* _hoops_RH _hoops_PRII _hoops_PCIHP */
								j += 2;
								while (j<_hoops_SAHAR) {
									*_hoops_AGCRC++ = _hoops_HCIRC;
									*_hoops_AGCRC++ = _hoops_AIHA[ j-1 ];
									*_hoops_AGCRC++ = _hoops_AIHA[ j ];
									j++;
								}
							}
							else
								j += -lengths[i];

						}
					}
					if (_hoops_AGCRC - _hoops_RGCRC > 0)
						glDrawElements(GL_TRIANGLES, _hoops_AGCRC - _hoops_RGCRC, GL_UNSIGNED_INT, _hoops_RGCRC);
				}
				ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,0,false);
				ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,1,false);
				_hoops_IGCRC(_hoops_CSRGR);
				_hoops_AHPRC(_hoops_CSRGR);
				_hoops_RHPRC(_hoops_CSRGR);
			}
			else {
 				for (i = 0; i < _hoops_PHHA; i++) {
					if (lengths[i] < _hoops_CIIPP) {
						_hoops_PGCRC += lengths[i] - 2;
						j += lengths[i];
					}
					else {
						glBegin (GL_TRIANGLE_STRIP);
						_hoops_SAHAR = j + lengths[i];

						while (j<_hoops_SAHAR) {
							_hoops_HCGS = _hoops_AIHA[j];
							(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
							(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
							glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCGS]);
							if (matrix) {
								if (_hoops_ICHA)
									_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS]);
								else
									_hoops_CAIRC (matrix,  points[_hoops_HCGS]);
							}
							else {
								if (_hoops_ICHA)
									_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
								glVertex3fv (&points[_hoops_HCGS].x);
							}
							j++;
						}
						glEnd ();
					}
				}
				if (_hoops_PGCRC) {
					j = 0;
					glBegin (GL_TRIANGLES);
					for (i = 0; i < _hoops_PHHA; i++) {
						if (lengths[i] < _hoops_CIIPP) {
							_hoops_SAHAR = j+lengths[i];
							j += 2;
							while (j<_hoops_SAHAR) {
								_hoops_HCGS = _hoops_AIHA[j-2];
								(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCGS]);
								if (matrix) {
									if (_hoops_ICHA)
										_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS]);
									else
										_hoops_CAIRC (matrix,  points[_hoops_HCGS]);
								}
								else {
									if (_hoops_ICHA)
										_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
									glVertex3fv (&points[_hoops_HCGS].x);
								}


								_hoops_HCGS = _hoops_AIHA[j-1];
								(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCGS]);
								if (matrix) {
									if (_hoops_ICHA)
										_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS]);
									else
										_hoops_CAIRC (matrix,  points[_hoops_HCGS]);
								}
								else {
									if (_hoops_ICHA)
										_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
									glVertex3fv (&points[_hoops_HCGS].x);
								}


								_hoops_HCGS = _hoops_AIHA[j];
								(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCGS]);
								if (matrix) {
									if (_hoops_ICHA)
										_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS]);
									else
										_hoops_CAIRC (matrix,  points[_hoops_HCGS]);
								}
								else {
									if (_hoops_ICHA)
										_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
									glVertex3fv (&points[_hoops_HCGS].x);
								}


								j++;
								if (j == _hoops_SAHAR)
									break;

								_hoops_HCGS = _hoops_AIHA[j];
								(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCGS]);
								if (matrix) {
									if (_hoops_ICHA)
										_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS]);
									else
										_hoops_CAIRC (matrix,  points[_hoops_HCGS]);
								}
								else {
									if (_hoops_ICHA)
										_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
									glVertex3fv (&points[_hoops_HCGS].x);
								}


								_hoops_HCGS = _hoops_AIHA[j-1];
								(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCGS]);
								if (matrix) {
									if (_hoops_ICHA)
										_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS]);
									else
										_hoops_CAIRC (matrix,  points[_hoops_HCGS]);
								}
								else {
									if (_hoops_ICHA)
										_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
									glVertex3fv (&points[_hoops_HCGS].x);
								}


								_hoops_HCGS = _hoops_AIHA[j-2];
								(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCGS]);
								if (matrix) {
									if (_hoops_ICHA)
										_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS]);
									else
										_hoops_CAIRC (matrix,  points[_hoops_HCGS]);
								}
								else {
									if (_hoops_ICHA)
										_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
									glVertex3fv (&points[_hoops_HCGS].x);
								}
								j++;
							}
						}
						else
							j += lengths[i];
					}
					glEnd ();
				}
			}
		}
		else {
			/* _hoops_SHPR _hoops_IPPA _hoops_GSSIA _hoops_CHR _hoops_HHPA */
			if (_hoops_CCIRC && ts->total >= _hoops_HGGHC) {
				/* _hoops_GRP _hoops_GPHA _hoops_SIRGR _hoops_PPR _hoops_GSSIA */
				ENSURE_COLOR_ARRAY_ON(_hoops_CSRGR);
				_hoops_HGCRC(_hoops_CSRGR);
				_hoops_CPPRC(_hoops_CSRGR);

				glNormalPointer(GL_FLOAT, 0, _hoops_ICHA);
				ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,0,true);
				glTexCoordPointer(_hoops_GSHA, GL_FLOAT, 0, _hoops_CCHA);
				ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,1,true);
				glTexCoordPointer(_hoops_GSHA, GL_FLOAT, 0, _hoops_CCHA);
				_hoops_IHRRC(_hoops_CSRGR,0);
				glColorPointer(3, GL_FLOAT, 0, rc->_hoops_IARRC._hoops_PHRRC);
				glVertexPointer(3, GL_FLOAT, 0, points);

				_hoops_SSPAR = 0;
				for (i = 0; i < _hoops_PHHA; i++) {
					_hoops_SAHAR = j + lengths[i];
					_hoops_PGGHC = _hoops_SSPAR + lengths[i] - 2;
					if (lengths[i] < _hoops_CIIPP) {
						_hoops_PGCRC += lengths[i] - 2;
					}
					else {
						_hoops_PGHAR = j;
						j += 2;
						if (face_indices)
							while (j<_hoops_SAHAR && !dc->_hoops_CGHAR[face_indices[j]])
								j++;
						else {
							while (j<_hoops_SAHAR && !dc->_hoops_CGHAR[_hoops_SSPAR]) {
								j++;
								_hoops_SSPAR++;
							}
						}
						if (j<_hoops_SAHAR) {
							/* _hoops_AHIC _hoops_HGPP _hoops_SGS _hoops_SR _hoops_IGHAR _hoops_RH _hoops_APRAR _hoops_SCGR _hoops_SCPH _hoops_PPR _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_PCCP _hoops_PRGI _hoops_PHI _hoops_IIGR _hoops_HIPH */
							if ((j-_hoops_PGHAR) & 0x1) {
								_hoops_SSPAR--;
								j -= 3;
							}
							else
								j -= 2;
							end = _hoops_SAHAR;
							if (face_indices) {
								while (!dc->_hoops_CGHAR[face_indices[end-1]])
									end--;
							}
							else {
								k = 1;
								while (!dc->_hoops_CGHAR[_hoops_PGGHC-k])
									k++;
								end -= k-1;
							}
							if (end - j > 0)
								glDrawElements(GL_TRIANGLE_STRIP, end-j, GL_UNSIGNED_INT, &_hoops_AIHA[j]);
						}
					}
					j = _hoops_SAHAR;
					_hoops_SSPAR = _hoops_PGGHC;
				}
				if (_hoops_PGCRC) {
					int *_hoops_RGCRC, *_hoops_AGCRC;

					j = 0;
					if (!_hoops_CSRGR->_hoops_IHSGC)
						ALLOC_ARRAY(_hoops_CSRGR->_hoops_IHSGC, _hoops_CHSGC, int);
					_hoops_RGCRC = _hoops_CSRGR->_hoops_IHSGC;
					_hoops_AGCRC = _hoops_RGCRC;
					_hoops_SSPAR = 0;
					for (i = 0; i < _hoops_PHHA; i++) {
						if (lengths[i] < _hoops_CIIPP) {
							if (_hoops_AGCRC - _hoops_RGCRC + (lengths[i]-2)*3 >= _hoops_CHSGC) {
								glDrawElements(GL_TRIANGLES, _hoops_AGCRC - _hoops_RGCRC, GL_UNSIGNED_INT, _hoops_RGCRC);
								_hoops_AGCRC = _hoops_RGCRC;
							}
							_hoops_SAHAR = j+lengths[i];
							j += 2;
							if (face_indices) {
								while (j<_hoops_SAHAR) {
									if (dc->_hoops_CGHAR[face_indices[j]]) {
										*_hoops_AGCRC++ = _hoops_AIHA[ j-2 ];
										*_hoops_AGCRC++ = _hoops_AIHA[ j-1 ];
										*_hoops_AGCRC++ = _hoops_AIHA[ j ];
									}
									j++;
									if (j == _hoops_SAHAR)
										break;
									if (dc->_hoops_CGHAR[face_indices[j]]) {
										*_hoops_AGCRC++ = _hoops_AIHA[ j ];
										*_hoops_AGCRC++ = _hoops_AIHA[ j-1 ];
										*_hoops_AGCRC++ = _hoops_AIHA[ j-2 ];
									}
									j++;
								}
							}
							else {
								while (j<_hoops_SAHAR) {
									if (dc->_hoops_CGHAR[_hoops_SSPAR++]) {
										*_hoops_AGCRC++ = _hoops_AIHA[ j-2 ];
										*_hoops_AGCRC++ = _hoops_AIHA[ j-1 ];
										*_hoops_AGCRC++ = _hoops_AIHA[ j ];
									}
									j++;
									if (j == _hoops_SAHAR)
										break;
									if (dc->_hoops_CGHAR[_hoops_SSPAR++]) {
										*_hoops_AGCRC++ = _hoops_AIHA[ j ];
										*_hoops_AGCRC++ = _hoops_AIHA[ j-1 ];
										*_hoops_AGCRC++ = _hoops_AIHA[ j-2 ];
									}
									j++;
								}
							}
						}
						else {
							j += lengths[i];
							_hoops_SSPAR += lengths[i] - 2;
						}
					}
					if (_hoops_AGCRC - _hoops_RGCRC)
						glDrawElements(GL_TRIANGLES, _hoops_AGCRC - _hoops_RGCRC, GL_UNSIGNED_INT, _hoops_RGCRC);
				}
				ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,0,false);
				ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,1,false);
				_hoops_RHPRC(_hoops_CSRGR);
				_hoops_IGCRC(_hoops_CSRGR);
				_hoops_AHPRC(_hoops_CSRGR);
			}
			else {
				/* _hoops_GRAA-_hoops_GPHA _hoops_CRPR, _hoops_CCA _hoops_GSSIA */
				_hoops_SSPAR = 0;
				for (i = 0; i < _hoops_PHHA; i++) {
					if (lengths[i] < _hoops_CIIPP) {
						_hoops_PGCRC += lengths[i] - 2;
						j += lengths[i];
						_hoops_SSPAR += lengths[i]-2;
						continue;
					}
					_hoops_SAHAR = j + lengths[i];
					_hoops_PGGHC = _hoops_SSPAR + lengths[i]-2;
					_hoops_PGHAR = j;
					j += 2;
					if (face_indices) {
						while (j<_hoops_SAHAR && !dc->_hoops_CGHAR[face_indices[j]])
							j++;
					}
					else {
						while (j<_hoops_SAHAR && !dc->_hoops_CGHAR[_hoops_SSPAR]) {
							j++;
							_hoops_SSPAR++;
						}
					}
					if (j<_hoops_SAHAR) {
						end = _hoops_SAHAR;
						if (face_indices) {
							while (!dc->_hoops_CGHAR[face_indices[end-1]])
								end--;
						}
						else {
							k = 1;
							while (!dc->_hoops_CGHAR[_hoops_PGGHC-k])
								k++;
							end -= k-1;
						}
						if ((j-_hoops_PGHAR) & 0x1) {
							_hoops_SSPAR--;
							j -= 3;
						}
						else
							j -= 2;
						glBegin (GL_TRIANGLE_STRIP);
						while (j < end) {
							_hoops_HCGS = _hoops_AIHA[j];
							(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
							(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
							glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCGS]);
							if (matrix) {
								if (_hoops_ICHA)
									_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS]);
								else
									_hoops_CAIRC (matrix,  points[_hoops_HCGS]);
							}
							else {
								if (_hoops_ICHA)
									_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
								glVertex3fv (&points[_hoops_HCGS].x);
							}
							j++;
						}
						glEnd ();
					}
					j = _hoops_SAHAR;
					_hoops_SSPAR = _hoops_PGGHC;
				}
				if (_hoops_PGCRC) {
					j = 0;
					glBegin (GL_TRIANGLES);
					_hoops_SSPAR=0;
					for (i = 0; i < _hoops_PHHA; i++) {
						if (lengths[i] < _hoops_CIIPP) {
							_hoops_SAHAR = j+lengths[i];
							j += 2;
							if (face_indices) {
								while (j<_hoops_SAHAR) {
									if (dc->_hoops_CGHAR[face_indices[j]]) {
										_hoops_HCGS = _hoops_AIHA[j-2];
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCGS]);
										if (matrix) {
											if (_hoops_ICHA)
												_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS]);
											else
												_hoops_CAIRC (matrix,  points[_hoops_HCGS]);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}


										_hoops_HCGS = _hoops_AIHA[j-1];
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCGS]);
										if (matrix) {
											if (_hoops_ICHA)
												_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS]);
											else
												_hoops_CAIRC (matrix,  points[_hoops_HCGS]);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}


										_hoops_HCGS = _hoops_AIHA[j];
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCGS]);
										if (matrix) {
											if (_hoops_ICHA)
												_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS]);
											else
												_hoops_CAIRC (matrix,  points[_hoops_HCGS]);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}

									}

									j++;
									if (j == _hoops_SAHAR)
										break;

									if (dc->_hoops_CGHAR[face_indices[j]]) {
										_hoops_HCGS = _hoops_AIHA[j];
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCGS]);
										if (matrix) {
											if (_hoops_ICHA)
												_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS]);
											else
												_hoops_CAIRC (matrix,  points[_hoops_HCGS]);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}


										_hoops_HCGS = _hoops_AIHA[j-1];
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCGS]);
										if (matrix) {
											if (_hoops_ICHA)
												_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS]);
											else
												_hoops_CAIRC (matrix,  points[_hoops_HCGS]);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}


										_hoops_HCGS = _hoops_AIHA[j-2];
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCGS]);
										if (matrix) {
											if (_hoops_ICHA)
												_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS]);
											else
												_hoops_CAIRC (matrix,  points[_hoops_HCGS]);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}

									}
									j++;
								}
							}
							else {
								while (j<_hoops_SAHAR) {
									if (dc->_hoops_CGHAR[_hoops_SSPAR++]) {
										_hoops_HCGS = _hoops_AIHA[j-2];
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCGS]);
										if (matrix) {
											if (_hoops_ICHA)
												_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS]);
											else
												_hoops_CAIRC (matrix,  points[_hoops_HCGS]);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}


										_hoops_HCGS = _hoops_AIHA[j-1];
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCGS]);
										if (matrix) {
											if (_hoops_ICHA)
												_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS]);
											else
												_hoops_CAIRC (matrix,  points[_hoops_HCGS]);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}


										_hoops_HCGS = _hoops_AIHA[j];
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCGS]);
										if (matrix) {
											if (_hoops_ICHA)
												_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS]);
											else
												_hoops_CAIRC (matrix,  points[_hoops_HCGS]);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}

									}
									j++;
									if (j == _hoops_SAHAR)
										break;
									if (dc->_hoops_CGHAR[_hoops_SSPAR++]) {
										_hoops_HCGS = _hoops_AIHA[j];
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCGS]);
										if (matrix) {
											if (_hoops_ICHA)
												_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS]);
											else
												_hoops_CAIRC (matrix,  points[_hoops_HCGS]);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}


										_hoops_HCGS = _hoops_AIHA[j-1];
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCGS]);
										if (matrix) {
											if (_hoops_ICHA)
												_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS]);
											else
												_hoops_CAIRC (matrix,  points[_hoops_HCGS]);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}


										_hoops_HCGS = _hoops_AIHA[j-2];
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										glColor3fv ((float const *) &rc->_hoops_IARRC._hoops_PHRRC[_hoops_HCGS]);
										if (matrix) {
											if (_hoops_ICHA)
												_hoops_PIRAC (matrix, _hoops_RRIRC, _hoops_CSRGR->_hoops_SRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS]);
											else
												_hoops_CAIRC (matrix,  points[_hoops_HCGS]);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}

									}
									j++;
								}
							}
						}
						else {
							j += lengths[i];
							_hoops_SSPAR += lengths[i] - 2;
						}
					}
					glEnd ();
				}
			}
		}
	} break;
#endif

/* _hoops_ARAR
    _hoops_PPGHC
	_hoops_HPGHC,
	_hoops_IPGHC,
	_hoops_CPGHC,
	_hoops_SPGHC,
	_hoops_GHGHC */
#include "oglvstrip.cpp"

/* _hoops_ARAR
    _hoops_RHGHC:
	_hoops_AHGHC:
	_hoops_PHGHC:
	_hoops_HHGHC:
	_hoops_IHGHC:
	_hoops_CHGHC: */
#include "oglfstrip.cpp"

	default:break;

	} /*_hoops_CICA*/
	} /*_hoops_SHS*/


		if (_hoops_CAPA != null)
			_hoops_CAPA = _hoops_CAPA->next;
	} while (_hoops_CAPA != null);

	/* _hoops_PCCP _hoops_IHH _hoops_RIH _hoops_IS _hoops_HGCR _hoops_RH _hoops_HSP _hoops_CGARA _hoops_HAIR _hoops_GGR _hoops_IRS _hoops_HSP _hoops_HSGP */
	if (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC) {
		if (BIT(rc->flags[rc->pass], _hoops_RGCGC)) {
			if (BIT(rc->flags[rc->pass], _hoops_CARRC)) {
				/* _hoops_GIARC _hoops_RIPS _hoops_IS _hoops_ISSC _hoops_PPR _hoops_HSPP _hoops_IAPR */
 				rc->flags[rc->pass] ^= (_hoops_CARRC|_hoops_AGCGC);
				goto _hoops_RAGHC;
			}
			else
				OGL_SET_HANDEDNESS (_hoops_CSRGR, _hoops_IHCR, 0);
		}

		if (_hoops_GPRRC(nr, ts->_hoops_GSSH ? ts->_hoops_GSSH->_hoops_GSHA : 0, ts->_hoops_GSSH ? ts->_hoops_GSSH->_hoops_SCAI : 0, rc)){
			if(rc->pass != 0){
				if(_hoops_CGGHC->next)
					_hoops_CGGHC = _hoops_CGGHC->next;
			}
			goto _hoops_RAGHC;
		}

		if (_hoops_CSRGR->_hoops_CSC._hoops_PRPAC[0]) {
			_hoops_SRGRC(_hoops_CSRGR,0);
			_hoops_AARRC (_hoops_CSRGR,0);
			_hoops_ICGRC(_hoops_CSRGR);
			_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
		}
		else if (_hoops_PCHA || _hoops_PAGI) {
			_hoops_ICGRC(_hoops_CSRGR);
			_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
		}
		if (_hoops_RASP || _hoops_GPIAR && _hoops_SIGA->_hoops_PGPH->_hoops_ACHHP == UPAT_NO_CONTRAST)
			glDisable (GL_POLYGON_STIPPLE);
		else if (_hoops_SIGA->pattern != FP_SOLID) {
			/* _hoops_PCCP _hoops_IHH _hoops_RIH _hoops_IS _hoops_HGCR _hoops_RH _hoops_HSP _hoops_CGARA _hoops_HAIR _hoops_GGR _hoops_IRS _hoops_HSP _hoops_HSGP */
			_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
			_hoops_SCIGC (_hoops_CSRGR);
			FORCE_COLOR (_hoops_CSRGR, &_hoops_SIGA->contrast_color, false);
			if (_hoops_GPIAR) {
				for (i = 0; i < 32; i++) {
					stipple[i] ^= ~0UL;
				}
				/* _hoops_AIAH _hoops_PPP */
				glPolygonStipple ((GLubyte const *)stipple);
			}
			else {
				glEnable (GL_POLYGON_STIPPLE);
				ENSURE_FACE_PATTERN (_hoops_CSRGR, _hoops_SIGA->pattern);
			}

			_hoops_CAPA = _hoops_PIPRC;
			do {
				if (_hoops_CAPA != null) {
					_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
				}

				if (!odl ||
					_hoops_PRHH ||
					!odl->item.geometry.id ||
					(odl->item.geometry.id == _hoops_RSARR)) {
					/* _hoops_HSP _hoops_ASGA _hoops_RGRRH _hoops_GPIC _hoops_RPIC _hoops_RGRRH _hoops_PSP _hoops_CCGI _hoops_GGR _hoops_RH _hoops_AIRI _hoops_HIGR.
					 * _hoops_SR _hoops_PAH _hoops_SHGHC _hoops_SGS _hoops_HSRAP _hoops_CCA _hoops_IRS _hoops_IHGP _hoops_GRAA-_hoops_GRRI _hoops_HAPR. */
					j=0;
					i=0;
					while (i<_hoops_PHHA) {
						glBegin (GL_TRIANGLE_STRIP);
						_hoops_SAHAR = j + lengths[i];
						while (j<_hoops_SAHAR) {
							_hoops_HCGS = _hoops_AIHA[j];
							glVertex3fv (&points[_hoops_HCGS].x);
							j++;
						}
						glEnd ();
						i++;
					}
				}
				else {
					odl->_hoops_GPPI = HOOPS_WORLD->_hoops_GPPI;
					glCallList (odl->item.geometry.id);
				}

				if (_hoops_CAPA != null)
					_hoops_CAPA = _hoops_CAPA->next;
			} while (_hoops_CAPA != null);

			glDisable (GL_POLYGON_STIPPLE);
		}
	}
	else {
		if (ALLBITS(ts->_hoops_SRHA, _hoops_GGIA | DL_INDEX_INTERPOLATION))
			_hoops_GPRRC(nr, ts->_hoops_GSSH ? ts->_hoops_GSSH->_hoops_GSHA : 0, ts->_hoops_GSSH ? ts->_hoops_GSSH->_hoops_SCAI : 0, rc);
	}
	_hoops_CSRGR->_hoops_AIRGC = false;

}/* _hoops_RSGR _hoops_API '_hoops_RHGS _hoops_PGSA 3d _hoops_CRHH'*/


local void
_hoops_GIGHC (
		Net_Rendition const &  nr,
		Tristrip const *ts,
		OGL_Display_List_Bin *_hoops_RRHA)
{
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	OGLData *_hoops_CSRGR = OGLD(dc);
	OGL_Display_List alter *odl;
	bool _hoops_HAHRC, _hoops_IAHRC, _hoops_CAHRC;
	int pass, _hoops_PRHA = 0;
	GLuint id;
	_hoops_IPSGC *pair;

	if (!_hoops_RRHA) {
		old_draw_3d_tristrip (nr, ts);
		_hoops_ICGRC(_hoops_CSRGR);
		return;
	}

	_hoops_CAHRC = false;
	for (pass = 0 ; pass < 2 ; pass++) {
		_hoops_RRHA->_hoops_CRHA->ResetCursor();
		pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
		if (!pair)
			return;
		ts = (Tristrip *)pair->geo;
		_hoops_HAHRC = (pair->_hoops_CPAI && BIT (pair->_hoops_CPAI->matrix._hoops_RAGR, _hoops_CASA));
		_hoops_IAHRC = ((pass == 0) ? _hoops_HAHRC : !_hoops_HAHRC);

		_hoops_SAHRC (_hoops_CSRGR, nr->transform_rendition, _hoops_IAHRC);
		ZALLOC(odl, OGL_Display_List);
		AGLM(odl->_hoops_CSRGR = OGLD(dc));
		odl->_hoops_GHRI = dc->_hoops_GHRI;
		odl->time_stamp = HOOPS_WORLD->_hoops_GPPI;
		odl->type = OGL_DL_GEOMETRY;
		ENSURE_LIST_BASE(_hoops_CSRGR, 0);
		id = glGenLists(1);
		glNewList (id, GL_COMPILE);
		_hoops_CSRGR->_hoops_CSC._hoops_IPAGC = true;

		_hoops_ISGI const *_hoops_CSGI = dc->_hoops_SPA->modelling_matrix;
		_hoops_SSGI const *_hoops_GGRI = dc->_hoops_SPA->color;

		for (;;) {
			pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
			if (!pair)
				break;
			ts = (Tristrip *)pair->geo;
			/* _hoops_IGHS _hoops_CAGH _hoops_PAPA _hoops_CGHS, _hoops_HIS _hoops_HRCI _hoops_GII _hoops_CPAP _hoops_CGHS */
			if (ts->_hoops_GAHA && ts->_hoops_GAHA->list)
				HD_Queue_Destroy_List (ts->_hoops_GAHA->list, true);

			odl->item.geometry._hoops_IGGI.point_count += ts->point_count;
			odl->item.geometry._hoops_IGGI._hoops_PHHA += ts->_hoops_PHHA;
			odl->item.geometry._hoops_IGGI.total += ts->total;
			odl->_hoops_CARH += _hoops_RRHRC (ts);
			/* _hoops_SR'_hoops_GHGP _hoops_SHH _hoops_GGR _hoops_SPGC _hoops_RPP _hoops_CCGI _hoops_HS _hoops_PGSGR _hoops_HGSGR
			   _hoops_IH _hoops_APHRC, _hoops_HIH _hoops_SGS _hoops_AGIR _hoops_HRGR _hoops_AGIA
			   _hoops_IS _hoops_SHH _hoops_GIR _hoops_GGR _hoops_RH _hoops_PIS _hoops_SCGI _hoops_SPAAR _hoops_RRGR _hoops_ARRS */
			_hoops_PRHA |= (
					(ts->_hoops_GSSH && ts->_hoops_GSSH->_hoops_GSHA >= 2) || 
					ts->_hoops_PCHA || 
					ts->_hoops_ICHA);
			dc->_hoops_SPA->modelling_matrix = pair->_hoops_CPAI;
			_hoops_HAHRC = (pair->_hoops_CPAI && BIT (pair->_hoops_CPAI->matrix._hoops_RAGR, _hoops_CASA));
			if (_hoops_HAHRC == _hoops_IAHRC) {
				if (BIT (ts->_hoops_SRHA, _hoops_GGIA))
					_hoops_ARCI (nr, ts);
				else
					old_draw_3d_tristrip (nr, ts);
			}
			else
				_hoops_CAHRC = true;
			_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
		}
		dc->_hoops_SPA->modelling_matrix = _hoops_CSGI;
		dc->_hoops_SPA->color = _hoops_GGRI;

		_hoops_CSRGR->_hoops_CSC._hoops_IPAGC = false;
		glEndList ();
		HOOPS_WORLD->display_list_vram_usage += odl->_hoops_CARH;
		odl->item.geometry.id = id;
		/* _hoops_SAHR _hoops_SGH _hoops_RH _hoops_CCRC _hoops_PPR _hoops_RSRC _hoops_HII _hoops_RH _hoops_HACH _hoops_CRHH */
		odl->item.geometry._hoops_SRHA = ts->_hoops_SRHA;
		odl->item.geometry._hoops_CARI = ts->_hoops_CARI;
		odl->item.geometry._hoops_IRRI = ts->face_attributes.flags;
		odl->item.geometry._hoops_GSAI = ts->_hoops_GSAI;

		if (_hoops_PRHA)
			odl->item.geometry._hoops_SRHA |= DL_FORCE_SMOOTH_SHADE_MODEL;
		if (_hoops_IAHRC)
			odl->item.geometry._hoops_SRHA |= DL_NEGATIVE_3X3;
		if (BIT (nr->transform_rendition->flags, _hoops_GRHH) &&
			BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES))
			odl->item.geometry._hoops_SRHA |= DL_LIGHTING;
		if (!ANYBIT (nr->_hoops_IRR->_hoops_CSA, _hoops_IIRAP|_hoops_SSA))
			odl->item.geometry._hoops_SRHA |= DL_FLAT_LIGHTING;
		odl->item.geometry._hoops_SRHA &= ~_hoops_SRHH;

		/* _hoops_CSRI _hoops_HRGR _hoops_IRS _hoops_PPHRC _hoops_GPRR*/
		if (_hoops_RRHA->_hoops_CHGI->item._hoops_ACGI._hoops_ARRI == null)
			_hoops_RRHA->_hoops_CHGI->item._hoops_ACGI._hoops_ARRI = POOL_NEW(dc->memory_pool, OGL_Display_List_List)(dc->memory_pool);
		_hoops_RRHA->_hoops_CHGI->item._hoops_ACGI._hoops_ARRI->AddFirst(odl);
		if (!_hoops_CAHRC)
			break;
	}
}


#endif



/*
 * Copyright (c) 1998-2001 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.213 2010-11-30 23:40:34 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "phedron.h"
#include "patterns.h"
#include "adt.h"


GLOBAL_FUNCTION void HD_Markers_To_Polymarker (
	Net_Rendition const & 		inr,
	int							count,
	Point *						points) {
	Net_Rendition				nr = inr;
	Polymarker					*pm;

	if (count == 0)
		return;

	/* _hoops_IRHH _hoops_RH _hoops_SCII _hoops_IRAA _hoops_RGCI _hoops_GPHA _hoops_AIRC _hoops_HII _hoops_GPIA _hoops_AIRC */
	nr.Modify()->_hoops_SCP = nr->_hoops_GSP;

	POOL_ZALLOC (pm, Polymarker, inr->_hoops_SRA->memory_pool);
	_hoops_ICAI (pm);
	pm->point_count = pm->length = count;
	pm->points = points;
	pm->_hoops_SRHA = (DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS|DL_TEMPORARY_DATA);
	pm->bounding = Bounding::Create (count, points);
	_hoops_SACIP(nr, pm);
	if (_hoops_ISAI (pm) ==  0)
		HI_Free_Polymarker_List (pm);
}


GLOBAL_FUNCTION void HD_Prepare_Geometry_Transparency (
	Net_Rendition alter & 		nr,
	char const *				_hoops_PAIIH) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_APARR				_hoops_RRCI;

	nr.Modify();
	nr->_hoops_CPP.Modify();

	_hoops_RRCI = _hoops_HGCGA (dc, _hoops_PAIIH, nr);

	if (BIT(dc->flags, _hoops_GPHHP)) {
		nr->current |= _hoops_AHIHP;
		nr->_hoops_CPP->_hoops_PRH._hoops_HRH = true;
		return;
	}


	if (BIT (nr->current, _hoops_CRSI) &&
		!BIT (nr->current, _hoops_SRSI) &&
		(dc->_hoops_SHPGR == QMoves_XOR ||
		 !BIT(dc->flags, _hoops_IIPIP))) {
		nr->_hoops_RCSHR &= ~_hoops_AHIHP;
		nr->_hoops_CPP->_hoops_PRH.style = _hoops_GCPI;
	}
	else if (nr->_hoops_IRR->_hoops_SRI == _hoops_PRAAP ||
			 nr->_hoops_CPP->_hoops_PRH.style == _hoops_AIII ||
			 BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSRAP)) {
		nr->_hoops_RCSHR &= ~_hoops_AHIHP;
	}
	else {
		nr->current |= _hoops_AHIHP;
		_hoops_RRCI->mode |= _hoops_AHIHP;
		nr->_hoops_CPP->_hoops_PRH._hoops_HRH = true;

		if (!BIT(dc->flags, _hoops_AASHP) &&
			nr->_hoops_CPP->_hoops_PRH._hoops_SRI == _hoops_PIII) {
			/* _hoops_HSPP _hoops_CCA _hoops_APRAR _hoops_HPRGR _hoops_CRAA [_hoops_IH _hoops_CPAP _hoops_CCA _hoops_RSSI] */
			HD_Vanillify_Actions (_hoops_RRCHP, _hoops_RRCI);

			/* _hoops_AGRP _hoops_ARIPR _hoops_SR _hoops_PAH _hoops_PSCPR _hoops_GAR _hoops_PSPA (_hoops_CGSI _hoops_PII _hoops_SCHS _hoops_HGCR _hoops_PRGS _hoops_ISHP _hoops_IS _hoops_CCGI _hoops_AHI) */
			_hoops_RRCI->draw_3d_ellipse			= HD_Defer_Peeled_Trans_3D_Ellipse;
			_hoops_RRCI->draw_3d_polygon			= HD_Defer_Peeled_Trans_3D_Polygon;
			_hoops_RRCI->draw_3d_tristrip		= HD_Defer_Peeled_Trans_3D_Tristrip;
			_hoops_RRCI->_hoops_ARCI	= HD_Defer_Peeled_Trans_3D_Tristrip;
			_hoops_RRCI->draw_3d_polyedge		= HD_Defer_Peeled_Trans_3D_Polyedge;
			_hoops_RRCI->draw_3d_polyline		= HD_Defer_Peeled_Trans_3D_Polyline;
			_hoops_RRCI->draw_3d_polymarker		= HD_Defer_Peeled_Trans_3D_Polymarker;
			_hoops_RRCI->draw_3d_marker			= HD_Defer_Peeled_Trans_3D_Marker;

			dc->_hoops_AHAGH = nr->_hoops_CPP->_hoops_PRH._hoops_RPAAP;
			dc->_hoops_PHAGH = nr->_hoops_CPP->_hoops_PRH._hoops_APAAP;

		}
		else if (ANYBIT (nr->current, _hoops_CSGGR|_hoops_CRSI)) {
			/*
			 * _hoops_RAH _hoops_ICCGR _hoops_CCSHP _hoops_ISSGR!
			 * _hoops_PS _hoops_GA'_hoops_RA _hoops_HSRPR _hoops_RH _hoops_HHIS _hoops_CGPR _hoops_CPHR (_hoops_GCASS _hoops_RH _hoops_RCPP _hoops_RHPC) _hoops_PGGA
			 * _hoops_SR _hoops_HHGC _hoops_IS _hoops_PSCPR _hoops_HCR _hoops_RGR _hoops_CPAP _hoops_CCGR _hoops_HCR _hoops_RH _hoops_CIGC _hoops_AGSAR
			 * _hoops_IRHH _hoops_PAII _hoops_PPRRR _hoops_CRGR _hoops_RH _hoops_HCHSR _hoops_SRHR.
			 * _hoops_RCASS _hoops_GRS _hoops_ACASS _hoops_RH _hoops_ACPH _hoops_GASR _hoops_IH _hoops_IHHH, _hoops_IS _hoops_PCASS
			 * _hoops_RH _hoops_HCASS _hoops_SICAR.
			 */
			HD_Vanillify_Actions ((_hoops_RRCHP|_hoops_CGCHP|_hoops_HHCHP), _hoops_RRCI);

			_hoops_RRCI->draw_3d_image					= HD_Std_3D_Image;
			_hoops_RRCI->draw_3d_text					= HD_Std_3D_Text;

			_hoops_RRCI->_hoops_CRCGA			= HD_Std_3D_Stenciled_Quad;

			_hoops_RRCI->_hoops_CSCGA					= HD_Standard_Draw_Inter_Text;

			_hoops_RRCI->draw_dc_polytriangle			= HD_Hide_DC_Polytriangle;
			_hoops_RRCI->draw_dc_colorized_polytriangle	= HD_Hide_DC_Colorized_Polytris;
			_hoops_RRCI->draw_dc_gouraud_polytriangle	= HD_Hide_DC_Gouraud_Polytris;
			_hoops_RRCI->draw_dc_phong_polytriangle		= HD_Hide_DC_Phong_Polytris;
			_hoops_RRCI->draw_dc_textured_polytriangle	= HD_Hide_DC_Textured_Polytris;
			_hoops_RRCI->draw_dc_polydot					= HD_Hide_DC_Polydot;
			_hoops_RRCI->draw_dc_colorized_polydot		= HD_Hide_DC_Colorized_Polydot;
			_hoops_RRCI->draw_dc_polyline				= HD_Hide_DC_Polyline;
			_hoops_RRCI->draw_dc_colorized_polyline		= HD_Hide_DC_Colorized_Polyline;
			_hoops_RRCI->draw_dc_gouraud_polyline		= HD_Hide_DC_Gouraud_Polyline;
			_hoops_RRCI->draw_dc_phong_polyline			= HD_Hide_DC_Phong_Polyline;
			_hoops_RRCI->draw_dc_textured_polyline		= HD_Hide_DC_Textured_Polyline;
			_hoops_RRCI->draw_dc_polymarker				= HD_Std_DC_Polymarker;
			_hoops_RRCI->draw_dc_colorized_polymarker	= HD_Std_DC_Colorized_Polymarker;
			_hoops_RRCI->_hoops_RPCGA					= HD_Hide_DC_Polygon;
			_hoops_RRCI->draw_dc_face					= HD_Hide_DC_Face;
			_hoops_RRCI->draw_dc_colorized_face			= HD_Hide_DC_Colorized_Face;
			_hoops_RRCI->draw_dc_ellipse					= HD_Std_DC_Ellipse;
			_hoops_RRCI->_hoops_SCISR 		= HD_Std_DC_Outline_Ellipse;
			_hoops_RRCI->_hoops_HPCGA					= HD_Hide_DC_Image;
			_hoops_RRCI->_hoops_AGCSR					= HD_Hide_Plain_Text;
			_hoops_RRCI->_hoops_SPCGA			= HD_Hide_DC_Stenciled_Quad;
		}
		else {
			/*
			 * _hoops_PS _hoops_PCASS _hoops_RH _hoops_HCASS _hoops_SICAR _hoops_SAHR _hoops_GGR _hoops_AGIR _hoops_SR _hoops_SPGA'_hoops_RA
			 * _hoops_SGGHA _hoops_GPP _hoops_GSIA _hoops_SGS _hoops_SSCP 3D _hoops_IHAHP.	_hoops_GPGP _hoops_SGS _hoops_PGRRR,
			 * _hoops_RH _hoops_CPAP _hoops_GRS _hoops_SHH _hoops_ICASS _hoops_HPP _hoops_ICCGR.
			 */
			_hoops_RRCI->_hoops_GCCGA		 = HD_Rasterize_DC_Spans_C24_U;
			_hoops_RRCI->_hoops_ACCGA		 = HD_Rasterize_DC_Spans_C24_G;
			_hoops_RRCI->_hoops_HCCGA		 = HD_Rasterize_DC_Spans_C24_R;
		}
	}
}

_hoops_AAGSP::~_hoops_AAGSP() {

	if (modelling_matrix != null)
		_hoops_HPRH (modelling_matrix);

	if (color != null)
		_hoops_HPRH (color);
};

GLOBAL_FUNCTION Geometry const * HD_Process_Geometry_Reference (
	Net_Rendition const &		inr,
	_hoops_PHIP const *	_hoops_RRA) {
	_hoops_SSAGR(_hoops_RRA);
	Display_Context alter *		dc = (Display_Context alter *)inr->_hoops_SRA;
	_hoops_AAGSP *			_hoops_GACSS = dc->_hoops_SPA;
	_hoops_CRCP const *				_hoops_SRCP = null;
	_hoops_HICS				path;

	if (dc->_hoops_AHSI != null) {
		_hoops_SRCP = dc->_hoops_AHSI->segment;
		path = dc->_hoops_AHSI->path;
	}


	// _hoops_ARPR _hoops_RPP _hoops_SIGR
	if (_hoops_GACSS == null || _hoops_GACSS->_hoops_CSAGR != _hoops_RRA) {
		if (_hoops_RRA->condition.count > 0 &&
			 !HI_Condition_Passed (inr->_hoops_ASIR->conditions.count,
								  inr->_hoops_ASIR->conditions._hoops_RCHA,
								  &_hoops_RRA->condition))
			return null;

		_hoops_GACSS = POOL_NEW(dc->memory_pool, _hoops_AAGSP)();
		_hoops_GACSS->next = dc->_hoops_SPA;
		_hoops_GACSS->_hoops_CSAGR = _hoops_RRA;
		_hoops_GACSS->nr = inr;

		dc->_hoops_SPA = _hoops_GACSS;

		_hoops_SSAGR(_hoops_RRA->_hoops_IHIP[0]);

		Net_Rendition alter &		nr = _hoops_GACSS->nr;

		Attribute const *			_hoops_ASGPR = _hoops_RRA->_hoops_IPPGR;
		_hoops_SSAGR(_hoops_ASGPR);

		_hoops_RCCA(_hoops_CPGIP)++;

		//_hoops_AGIRC(_hoops_CSPH, "_hoops_CCAH _hoops_PAGGR","", 0);

		if (_hoops_ASGPR != null) {

			do {
				_hoops_SSAGR(_hoops_ASGPR->next);
				if(_hoops_ASGPR->type > _hoops_IAAA(HK_MODELLING_MATRIX,HK_COLOR))
					break;

				switch (_hoops_ASGPR->type) {
					case HK_MODELLING_MATRIX: {

						_hoops_ISGI const *	_hoops_RACSS = (_hoops_ISGI const *)_hoops_ASGPR;
						ASSERT(_hoops_GACSS->modelling_matrix == null);

						if (BIT(_hoops_RACSS->matrix._hoops_RAGR, _hoops_CICH)) {

							if (_hoops_GACSS->next != dc->_hoops_ISAGR &&
								_hoops_GACSS->next->modelling_matrix) {

								// _hoops_HASC _hoops_CCA _hoops_CGHI _hoops_SPR
								_hoops_ISGI const *	_hoops_AACSS = _hoops_GACSS->next->modelling_matrix;
								_hoops_ISGI alter *	_hoops_CPAI;

								POOL_ZALLOC (_hoops_CPAI, _hoops_ISGI, dc->memory_pool);
								_hoops_CPAI->type = HK_MODELLING_MATRIX;
								_hoops_CPAI->_hoops_HIHI = 1;

								_hoops_GACSS->modelling_matrix = _hoops_CPAI;

								HI_Multiply_Matrices (&_hoops_RACSS->matrix, &_hoops_AACSS->matrix, &_hoops_CPAI->matrix);
							}
							else {

								// _hoops_PPSR _hoops_HPGR _hoops_SCH
								_hoops_GACSS->modelling_matrix = _hoops_RACSS;
								_hoops_PRRH (_hoops_GACSS->modelling_matrix);
							}

							if (!BIT (_hoops_GACSS->modelling_matrix->matrix.flags, _hoops_HASA))
								HI_Validate_Matrix_NEG3X3 ((_hoops_HRPA alter *)&_hoops_GACSS->modelling_matrix->matrix);

						}

					} break;
					case HK_COLOR: {
						_hoops_SSGI const *color = (_hoops_SSGI const *)_hoops_ASGPR;
						ASSERT(_hoops_GACSS->color == null);

						if (HI_Color_Is_Simple (color, null)) {
							_hoops_GACSS->color = color;
							_hoops_PRRH (color);
						}
					} break;
				}

			} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

			HD_Downwind_Rendition (nr, _hoops_RRA->_hoops_IPPGR, _hoops_CAHGP, true);

			if (BIT (nr->_hoops_RCSHR, _hoops_AHIHP) &&
				!BIT (nr->current, _hoops_AHIHP)) {
				HD_Prepare_Geometry_Transparency (nr, "reference transparency");

				_hoops_GACSS->_hoops_ARRGH = true;
			}
		}

		// _hoops_ARP _hoops_GCHRR _hoops_CCGCS _hoops_RPP _hoops_SIGR
		if (_hoops_GACSS->next != dc->_hoops_ISAGR) {

			if (!_hoops_GACSS->modelling_matrix &&
				_hoops_GACSS->next->modelling_matrix) {

				// _hoops_PPSR _hoops_HPGR _hoops_CGHI _hoops_SPR
				_hoops_GACSS->modelling_matrix = _hoops_GACSS->next->modelling_matrix;
				_hoops_PRRH(_hoops_GACSS->modelling_matrix);
			}

			if (!_hoops_GACSS->color &&
				_hoops_GACSS->next->color) {

				// _hoops_PPSR _hoops_HPGR _hoops_CGHI _hoops_SPR
				_hoops_GACSS->color = _hoops_GACSS->next->color;
				_hoops_PRRH(_hoops_GACSS->color);
			}
		}

#ifdef HOOPS_DEBUG_BUILD
		_hoops_GACSS->_hoops_GRRGH = _hoops_GACSS->modelling_matrix;
		_hoops_GACSS->_hoops_RRRGH = _hoops_GACSS->color;
#endif

		if (_hoops_RRA->_hoops_IHIP[0]->type != _hoops_IRCP) {
			_hoops_GACSS->geometry = (Geometry const *)_hoops_RRA->_hoops_IHIP[0];
			_hoops_GACSS->single = true;
		}
		else {
			_hoops_CRCP const *				_hoops_SRCP = (_hoops_CRCP const *)_hoops_RRA->_hoops_IHIP[0];
			Bounding const &			_hoops_RCHS = _hoops_RRA->bounding;
			_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;

			if (!_hoops_RCHS._hoops_HICAR() && 
				!BIT(dc->flags, _hoops_HSAGR) &&
				!BIT (nr->current, _hoops_PGCGA) &&
				!BIT(_hoops_IHCR->flags, _hoops_APGSP) &&
				 ANYBIT (_hoops_IHCR->_hoops_APH, Heur_Culling_EXTENT|_hoops_RIHS|Heur_Culling_VIEW_FRUSTUM)) {

				// _hoops_ASIGA _hoops_ISPR _hoops_SRGR _hoops_PAR _hoops_HPRC?
				bool _hoops_SSRPS =
					ANYBIT (_hoops_RCHS->flags, _hoops_IGCIR|Bounding_TRANSFORM_DEPENDENT) ||
					BIT (_hoops_RCHS->flags, _hoops_HGCIR) &&
					(nr->_hoops_SISI->transform != FT_FULL ||
					BIT (dc->_hoops_CPGPR, _hoops_RSCCA)) ||
					ANYBIT (nr->_hoops_AHP->line_style->flags,
						_hoops_PRCAP|LSF_OFFSET|LSF_WEIGHT|_hoops_RHISA|LSF_GLYPHS);

				if (!_hoops_SSRPS) {

					_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
					_hoops_ICP const &	_hoops_CCP = nr->_hoops_GSP;
					float						_hoops_SRIHS = 0.0f;

					if (BIT (nr->_hoops_RGP, T_VERTICES)) {
						if (BIT (_hoops_CCP->glyph->flags, _hoops_GSIAP))
							_hoops_SRIHS = 1.0f;
						else if (_hoops_CCP->ysize < 0)
							_hoops_SRIHS = 0.5f * HD_Compute_Generic_Size (nr, _hoops_CCP->_hoops_PHP, _hoops_CCP->_hoops_HHP, 1.0f, false, 0, true);
						else 
							_hoops_SRIHS = _hoops_CCP->ysize;
					}

					int	_hoops_SIHS = 0;

					if (!BIT (nr->current, _hoops_CRSI) && 
						ANYBIT (_hoops_IHCR->_hoops_APH, Heur_Culling_EXTENT|_hoops_RIHS) &&
						BIT (_hoops_RRGH->_hoops_SHHS, _hoops_AIIRP)) {

						if (BIT (_hoops_IHCR->_hoops_APH, _hoops_RIHS))
							_hoops_SIHS = _hoops_RRGH->_hoops_GCHS;
						if (BIT (_hoops_IHCR->_hoops_APH, Heur_Culling_EXTENT))
							_hoops_SIHS = _hoops_IAAA(_hoops_RRGH->_hoops_GRGC, _hoops_SIHS);
					}

					Test _hoops_ASIS = Test_DISJOINT;
					float _hoops_CIHS = 0.0f;

					HD_Transform_And_Test_Simple_Sphere (nr, 1, &_hoops_RCHS->sphere, null, _hoops_SRIHS,
														 _hoops_SIHS, &_hoops_ASIS, null, &_hoops_CIHS);

					switch (_hoops_ASIS) {
						case Test_DISJOINT: {
							_hoops_GPRH(_hoops_GCRGH)++;
							goto _hoops_PP;
						} _hoops_HHHI;

						case _hoops_GAAGI: {
							if (BIT (_hoops_IHCR->_hoops_APH, Heur_Culling_VIEW_FRUSTUM) &&
								!ANYBIT (_hoops_IHCR->flags, _hoops_AIHS|_hoops_PSASP))
								nr.Modify()->transform_rendition.Modify()->flags |= _hoops_AIHS;	
						} break;

						case _hoops_AAAGI:
						case _hoops_PAAGI: {
							if (_hoops_RRGH->_hoops_PCHS == Heur_MAX_EXTENT_MODE_DEFER &&
								(!BIT (_hoops_IHCR->_hoops_APH, _hoops_RIHS) ||
								  _hoops_CIHS > _hoops_RRGH->_hoops_GCHS)) {

								 // _hoops_PAH'_hoops_RA _hoops_PSCPR _hoops_CCSHP _hoops_APGR _hoops_CAPRR, _hoops_HAR _hoops_GHGC _hoops_SIRCS _hoops_HIASR
								if (!BIT(dc->flags, _hoops_RASS) || 
									(BIT (nr->current, _hoops_CSGGR) &&
									 ANYBIT (_hoops_RRGH->_hoops_SRI, _hoops_GRAAP|_hoops_HSSS|_hoops_PRAAP|_hoops_SICI)))
										break;		

								// _hoops_PAGA: _hoops_PSCPR _hoops_GRP _hoops_GIGR _hoops_IPP, _hoops_GAR _hoops_SR _hoops_GRS _hoops_RRSS
								//		 _hoops_IRGH _hoops_AIRC _hoops_GICS _hoops_CGPR _hoops_SR _hoops_ASRC _hoops_IS _hoops_CPSA _hoops_PGSA
								Net_Rendition					_hoops_CRAI = inr.Copy();
								int								_hoops_HCHS;

								_hoops_HHCR alter &		_hoops_GGCC = _hoops_CRAI->transform_rendition.Modify();
								_hoops_CGRA alter &		_hoops_GCRCS = _hoops_CRAI->_hoops_SAIR.Modify();

								if (_hoops_ASIS == _hoops_AAAGI &&
									BIT (_hoops_IHCR->_hoops_APH, Heur_Culling_VIEW_FRUSTUM) &&
									!BIT (_hoops_IHCR->flags, _hoops_PSASP))
									_hoops_GGCC->flags |= _hoops_AIHS;

								_hoops_GGCC->flags |= _hoops_APGSP|_hoops_CAHPP;
								_hoops_GCRCS->_hoops_ASIHP |= _hoops_ACARP;

								_hoops_HCHS = int ((float)_hoops_CIHS * _hoops_RCHS._hoops_SGCIR() /
									(float)nr->_hoops_IRR->_hoops_GRGC * (float)_hoops_ICHS);

								HD_Defer_Tree_Batch (_hoops_CRAI, _hoops_SRCP, path, _hoops_HCHS, _hoops_RRA);
							}
							else
								_hoops_GPRH(_hoops_SIRGH)++;

							goto _hoops_PP;

						}	_hoops_HHHI;

					}
				}

				nr.Modify()->transform_rendition.Modify()->flags |= _hoops_APGSP;
			}

			_hoops_GACSS->geometry = _hoops_SRCP->geometry;
			_hoops_GACSS->single = false;
		}

		int _hoops_PACSS = _hoops_RRA->_hoops_RGPGR|_hoops_AGPGR(_hoops_AHIP);
		if (_hoops_GACSS->nr->_hoops_RGPGR != _hoops_PACSS)
			_hoops_GACSS->nr.Modify()->_hoops_RGPGR &= _hoops_PACSS;

		_hoops_GACSS->start = _hoops_GACSS->geometry;		// _hoops_IH _hoops_HRCC _hoops_SGS _hoops_SIAS _hoops_RRP _hoops_IS _hoops_HACSS _hoops_RH _hoops_SHSC _hoops_HIGR
	}

	if (_hoops_GACSS->geometry == null) {
		// _hoops_CACH _hoops_RPP _hoops_SR _hoops_HS _hoops_RRI _hoops_CPAP
		if (++_hoops_GACSS->index < _hoops_RRA->_hoops_HHIP)
			_hoops_GACSS->start = _hoops_GACSS->geometry = (Geometry const *)_hoops_RRA->_hoops_IHIP[_hoops_GACSS->index];
	}

	//_hoops_AGIRC(_hoops_CSPH, "_hoops_SCGR _hoops_PAGGR","", 0);

	// _hoops_CRGS _hoops_RH _hoops_CIS _hoops_RPP _hoops_SR _hoops_HS _hoops_CIPH _hoops_IS _hoops_HPPP
	if (_hoops_GACSS->geometry != null)
		return _hoops_GACSS->geometry;


	// _hoops_GGAS _hoops_CGPR _hoops_CPHR
  _hoops_PP:;

	//_hoops_AGIRC(_hoops_CSPH, "_hoops_GGAS _hoops_PAGGR","", 0);

#ifdef HOOPS_DEBUG_BUILD
	// _hoops_RPP _hoops_AGCR _hoops_CHR _hoops_RHHR _hoops_AICRR _hoops_SARS'_hoops_RA _hoops_ASAC _hoops_PPR _hoops_PHIH _hoops_CIAH
	ASSERT(_hoops_GACSS->_hoops_GRRGH == _hoops_GACSS->modelling_matrix);
	ASSERT(_hoops_GACSS->_hoops_RRRGH == _hoops_GACSS->color);
	ASSERT(dc->_hoops_ISAGR->modelling_matrix == null);
	ASSERT(dc->_hoops_ISAGR->color == null);
#endif

	if (_hoops_GACSS->_hoops_ARRGH)
		_hoops_HGSGA (dc, "reference transparency");

	dc->_hoops_SPA = _hoops_GACSS->next;
	delete _hoops_GACSS;

	return null;
}

GLOBAL_FUNCTION Geometry const * HD_Standard_Render (
	Net_Rendition const &		_hoops_GSAGR,
	Geometry const *			geometry,
	Action_Mask					mask,
	bool						_hoops_RSAGR) {
	Display_Context alter *		dc = (Display_Context alter *)_hoops_GSAGR->_hoops_SRA;
	_hoops_ACHR					_hoops_RGP = _hoops_GSAGR->_hoops_RGP;

	UNREFERENCED (mask);

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_IPIGA)) return;
#endif

	if (BIT(dc->flags, _hoops_CHSI) && !BIT(dc->flags, _hoops_HSAGR))
		return null;

	do {
		Net_Rendition				nr = _hoops_GSAGR;
		bool						single = _hoops_RSAGR;

		if (dc->_hoops_SPA != dc->_hoops_ISAGR) {
			if ((geometry = dc->_hoops_SPA->geometry) == null)
				geometry = dc->_hoops_SPA->_hoops_CSAGR;	// _hoops_IHIS _hoops_GPP _hoops_IS _hoops_GGAS
			nr = dc->_hoops_SPA->nr;
			single = dc->_hoops_SPA->single;
		}

		dc->_hoops_RAI = geometry;
		dc->_hoops_CPIGA = false;

		for (;;) if (_hoops_GGPGR(nr)) {
			geometry = dc->_hoops_RAI;
			if (dc->_hoops_SPA != dc->_hoops_ISAGR &&
				geometry != dc->_hoops_SPA->_hoops_CSAGR)
				dc->_hoops_SPA->geometry = geometry;
			dc->_hoops_RAI = null;
			return geometry;
		}
		else {
			Type		type = dc->_hoops_RAI->type;

			if (!BIT (nr->_hoops_RGPGR, _hoops_AGPGR(type))) {
				if (single)
					goto Done;
				_hoops_PGPGR (dc->_hoops_RAI, type);
			}
			else switch (type) {
				/*
				 * _hoops_PHIGA _hoops_GGR _hoops_ARI _hoops_HA _hoops_IHSA _hoops_RGAR _hoops_RH _hoops_CICA,
				 * _hoops_HAR _hoops_RH _hoops_HAPR.  _hoops_PHGP _hoops_RH _hoops_RGAR _hoops_PPRRR _hoops_GGSR _hoops_HRGR _hoops_AIH
				 * _hoops_IRS _hoops_ASRC.  _hoops_HHIGA _hoops_ASRC _hoops_SIHH _hoops_RGSR
				 * _hoops_CSPH->_hoops_IHIGA = _hoops_IRAP.
				 */



				/*
				 * _hoops_PS _hoops_PAH _hoops_SSPC _hoops_AGCR - _hoops_SSIA _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_SHH _hoops_CHCC
				 */

				case _hoops_HGPGR: {
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, _hoops_HGPGR);
				}	break;



				/*
				 * _hoops_PS _hoops_PGSA _hoops_AGCR _hoops_GRP _hoops_RH _hoops_HSPR _hoops_IHGP _hoops_CIGCR
				 *
				 *		_hoops_AGIR _hoops_IACSS: {
				 *			_hoops_RPP (_hoops_AGGC (_hoops_HPRC, ..._hoops_CACSS'_hoops_GRI _hoops_SHAAA...)) {
				 *				_hoops_AA {
				 *					..._hoops_PGSA _hoops_SCH...
				 *					_hoops_RPP ((_hoops_CSPH->_hoops_IHIGA =
				 *						 _hoops_CSPH->_hoops_IHIGA->_hoops_SPS) == _hoops_IRAP) _hoops_HHIIA _hoops_AP;
				 *				} _hoops_HPGP (_hoops_CSPH->_hoops_IHIGA->_hoops_GPRR == _hoops_IACSS);
				 *			_hoops_SHS
				 *				_hoops_SACSS (_hoops_CSPH->_hoops_IHIGA, _hoops_IACSS);
				 *
				 * _hoops_HGI _hoops_IHIGR _hoops_IHHH _hoops_IS _hoops_PCACR _hoops_HSGR _hoops_HPPP _hoops_HCR _hoops_CPAP _hoops_IIGR _hoops_GPRR _hoops_IACSS
				 * _hoops_HPGR _hoops_ARR, _hoops_SIHH _hoops_PSHSC _hoops_GPCSS.	_hoops_HHIGR _hoops_RPCSS _hoops_SRS _hoops_IGH _hoops_GII
				 * _hoops_IIGR _hoops_RH _hoops_CPAP _hoops_HRGR _hoops_SIGC, _hoops_PPR _hoops_RRRS _hoops_SCH _hoops_HCR, _hoops_PAR _hoops_IRIIP _hoops_SCH _hoops_HCR.
				 *
				 * _hoops_APCSS _hoops_SHH _hoops_RCRR _hoops_HCR _hoops_RH _hoops_PPCSS _hoops_CHR _hoops_RCGRA _hoops_GIAA _hoops_IRS _hoops_AGIR.
				 * _hoops_HHIGA _hoops_ASRC _hoops_SIHH _hoops_RGSR _hoops_CSPH->_hoops_IHIGA = _hoops_IRAP.
				 */

				case _hoops_PIIP: {
					if (_hoops_ICCSP (nr, _hoops_CIIP) && ANYBIT (_hoops_RGP, T_LINES)) {
						dc->_hoops_SCGC |= _hoops_CIIP;
#ifndef DISABLE_CALLBACKS
						if (nr->_hoops_RSGC->action.draw_3d_polyline != null ||
							nr->_hoops_RSGC->action.draw_3d_geometry != null) {
							_hoops_CHCHP		draw;

							if (nr->_hoops_RSGC->action.draw_3d_polyline != null) {
								draw = nr->_hoops_RSGC->action.draw_3d_polyline;
								_hoops_HCHGH(nr, _hoops_AIRCR);
							}
							else {
								draw = (_hoops_CHCHP)nr->_hoops_RSGC->action.draw_3d_geometry;
								_hoops_HCHGH(nr, _hoops_PSRCR);
							}

							do {
								(*draw) (&nr, (Polyline const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_PIIP);
							_hoops_SCHGH(nr);
						}
						else
#endif
						{
							_hoops_GRCGA		draw = dc->_hoops_IPCI->draw_3d_polyline;

							do {
								(*draw) (nr, (Polyline const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
									goto Done;
							} while (dc->_hoops_RAI->type == _hoops_PIIP);
						}
					}
					//_hoops_CGPGR
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, _hoops_PIIP);
				}	break;

				case _hoops_HIIP:
				case _hoops_IIIP: {
					if (_hoops_ICCSP (nr, _hoops_CIIP) && BIT (_hoops_RGP, T_LINES)) {
						dc->_hoops_SCGC |= _hoops_CIIP;

#ifndef DISABLE_CALLBACKS
						if (nr->_hoops_RSGC->action.draw_3d_polyline != null ||
							nr->_hoops_RSGC->action.draw_3d_geometry != null) {
							_hoops_CHCHP		draw;

							if (nr->_hoops_RSGC->action.draw_3d_polyline != null) {
								draw = nr->_hoops_RSGC->action.draw_3d_polyline;
								_hoops_HCHGH(nr, _hoops_AIRCR);
							}
							else {
								draw = (_hoops_CHCHP)nr->_hoops_RSGC->action.draw_3d_geometry;
								_hoops_HCHGH(nr, _hoops_PSRCR);
							}

							do {
								(*draw) (&nr, (Polyline const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_IIIP);
							_hoops_SCHGH(nr);
						}
						else
	#endif
						{
							_hoops_GRCGA		draw = dc->_hoops_IPCI->draw_3d_polyline;

							do {
								(*draw) (nr, (Polyline const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
									goto Done;
							} while (dc->_hoops_RAI->type == _hoops_IIIP);
						}
					}
					//_hoops_CGPGR
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, type);
				}	break;

				case _hoops_SIIP: {
					if (_hoops_ICCSP (nr, _hoops_GCIP) && ANYBIT (_hoops_RGP, T_LINES)) {
						dc->_hoops_SCGC |= _hoops_GCIP;

#ifndef DISABLE_CALLBACKS
						if (nr->_hoops_RSGC->action.draw_3d_polyline != null ||
							nr->_hoops_RSGC->action.draw_3d_geometry != null ||
							nr->_hoops_RSGC->action.draw_3d_infinite_line != null) {
							_hoops_CHCHP		draw;

							if (nr->_hoops_RSGC->action.draw_3d_infinite_line != null) {
								draw = nr->_hoops_RSGC->action.draw_3d_infinite_line;
								_hoops_HCHGH(nr, _hoops_PIRCR);
							}
							else {
								draw = (_hoops_CHCHP)nr->_hoops_RSGC->action.draw_3d_geometry;
								_hoops_HCHGH(nr, _hoops_PSRCR);
							}

							do {
								(*draw) (&nr, (Polyline const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_SIIP);
							_hoops_SCHGH(nr);
						}
						else
#endif
						{
							_hoops_GRCGA		draw = dc->_hoops_IPCI->draw_3d_polyline;

							draw = dc->_hoops_IPCI->draw_3d_infinite_line;

							do {
								(*draw) (nr, (Polyline const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
									goto Done;
							} while (dc->_hoops_RAI->type == _hoops_SIIP);
						}
					}
					//_hoops_CGPGR
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, _hoops_SIIP);
				}	break;


				case _hoops_CHIP: {
#ifndef _hoops_CCPIR
					if (_hoops_ICCSP (nr, _hoops_SHIP) && BIT (_hoops_RGP, T_LINES)) {
						dc->_hoops_SCGC |= _hoops_SHIP;

#	ifndef DISABLE_CALLBACKS
						if (nr->_hoops_RSGC->action.draw_3d_nurbs_curve != null ||
							nr->_hoops_RSGC->action.draw_3d_geometry != null) {
							_hoops_CGSHP draw;

							if (nr->_hoops_RSGC->action.draw_3d_nurbs_curve != null) {
								draw = nr->_hoops_RSGC->action.draw_3d_nurbs_curve;
								_hoops_HCHGH(nr, _hoops_RSRCR);
							}
							else {
								draw = (_hoops_CGSHP)nr->_hoops_RSGC->action.draw_3d_geometry;
								_hoops_HCHGH(nr, _hoops_PSRCR);
							}

							do {
								(*draw) (&nr, (_hoops_PIRGR *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_CHIP);
							_hoops_SCHGH(nr);
						}
						else
#	endif
						{
							_hoops_RRCGA draw = dc->_hoops_IPCI->draw_3d_nurbs_curve;

							do {
								(*draw) (nr, (_hoops_PIRGR *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
									goto Done;
							} while (dc->_hoops_RAI->type == _hoops_CHIP);
						}
					}
#endif
					//_hoops_CGPGR
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, _hoops_CHIP);
				}	break;

				case _hoops_PRCP: {
#ifndef _hoops_GSPIR
					if (_hoops_ICCSP (nr, _hoops_HRCP|_hoops_PCSI) &&
						ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE)) {
						dc->_hoops_SCGC |= _hoops_HRCP;

						_hoops_CRCP *	_hoops_ARPGR;
						if ((_hoops_ARPGR = dc->_hoops_RAI->owner) != null)
							_hoops_ARPGR->_hoops_RHAGR._hoops_PRPGR(dc->_hoops_RIGC->thread_id);

#	ifndef DISABLE_CALLBACKS
						if (nr->_hoops_RSGC->action.draw_3d_nurbs_surface != null ||
							nr->_hoops_RSGC->action.draw_3d_geometry != null) {
							_hoops_GIIGA draw;

							if (nr->_hoops_RSGC->action.draw_3d_nurbs_surface != null) {
								_hoops_HCHGH(nr, _hoops_ASRCR);
								draw = nr->_hoops_RSGC->action.draw_3d_nurbs_surface;
							}
							else {
								_hoops_HCHGH(nr, _hoops_PSRCR);
								draw = (_hoops_GIIGA)nr->_hoops_RSGC->action.draw_3d_geometry;
							}

							do {
								(*draw) (&nr, (_hoops_APPGR *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									if (_hoops_ARPGR != null)
										_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_PRCP);
							_hoops_SCHGH(nr);
						}
						else
#	endif
						{
							_hoops_RIIGA draw;

							draw = dc->_hoops_IPCI->draw_3d_nurbs_surface;

							do {
								(*draw) (nr, (_hoops_APPGR *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									if (_hoops_ARPGR != null)
										_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_PRCP);
						}

						if (_hoops_ARPGR != null)
							_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
					}
#endif
					//_hoops_CGPGR
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, _hoops_PRCP);
				}	break;

				case _hoops_ASIP: {
					if (_hoops_ICCSP (nr, _hoops_PSIP|_hoops_PCSI) &&
						ANYBIT (_hoops_RGP, T_FACES|T_ANY_SHELL_EDGE)) {
						dc->_hoops_SCGC |= _hoops_PSIP;

#ifndef DISABLE_CALLBACKS
						if (nr->_hoops_RSGC->action.draw_3d_cylinder != null ||
							nr->_hoops_RSGC->action.draw_3d_geometry != null) {
							_hoops_AIIGA		draw;

							if (nr->_hoops_RSGC->action.draw_3d_cylinder != null) {
								draw = nr->_hoops_RSGC->action.draw_3d_cylinder;
								_hoops_HCHGH(nr, _hoops_SCRCR);
							}
							else {
								draw = (_hoops_AIIGA)nr->_hoops_RSGC->action.draw_3d_geometry;
								_hoops_HCHGH(nr, _hoops_PSRCR);
							}

							do {
								(*draw) (&nr, (Cylinder const *)dc->_hoops_RAI);
								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_ASIP);
							_hoops_SCHGH(nr);
						}
						else
#endif
						{
							_hoops_PIIGA		draw = dc->_hoops_IPCI->draw_3d_cylinder;

							do {
								(*draw) (nr, (Cylinder const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
									goto Done;
							} while (dc->_hoops_RAI->type == _hoops_ASIP);
						}
					}
					//_hoops_CGPGR
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, _hoops_ASIP);
				}	break;

				case _hoops_CSIP: {
					if (_hoops_ICCSP (nr, _hoops_SSIP|_hoops_PCSI) &&
						ANYBIT (_hoops_RGP, T_FACES|T_ANY_SHELL_EDGE)) {
						dc->_hoops_SCGC |= _hoops_PSIP;

#ifndef DISABLE_CALLBACKS
						if (nr->_hoops_RSGC->action.draw_3d_polycylinder != null ||
							nr->_hoops_RSGC->action.draw_3d_geometry != null) {
							_hoops_HIIGA	draw;

							if (nr->_hoops_RSGC->action.draw_3d_polycylinder != null) {
								draw = nr->_hoops_RSGC->action.draw_3d_polycylinder;
								_hoops_HCHGH(nr, _hoops_GSRCR);
							}
							else {
								draw = (_hoops_HIIGA)nr->_hoops_RSGC->action.draw_3d_geometry;
								_hoops_HCHGH(nr, _hoops_PSRCR);
							}

							do {
								(*draw) (&nr, (PolyCylinder const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_CSIP);
							_hoops_SCHGH(nr);
						}
						else
#endif
						{
							_hoops_IIIGA	draw = dc->_hoops_IPCI->draw_3d_polycylinder;

							do {
								(*draw) (nr, (PolyCylinder const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
									goto Done;
							} while (dc->_hoops_RAI->type == _hoops_CSIP);
						}
					}
					//_hoops_CGPGR
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, _hoops_CSIP);
				}	break;

				case _hoops_HSIP: {
					if (_hoops_ICCSP (nr, _hoops_ISIP|_hoops_PCSI) &&
						ANYBIT (_hoops_RGP, T_FACES|T_ANY_SHELL_EDGE)) {
						dc->_hoops_SCGC |= _hoops_PSIP;

#ifndef DISABLE_CALLBACKS
						if (nr->_hoops_RSGC->action.draw_3d_sphere != null ||
							nr->_hoops_RSGC->action.draw_3d_geometry != null) {
							_hoops_CIIGA		draw;

							if (nr->_hoops_RSGC->action.draw_3d_sphere != null) {
								draw = nr->_hoops_RSGC->action.draw_3d_sphere;
								_hoops_HCHGH(nr, _hoops_CCRCR);
							}
							else {
								draw = (_hoops_CIIGA)nr->_hoops_RSGC->action.draw_3d_geometry;
								_hoops_HCHGH(nr, _hoops_PSRCR);
							}

							do {
								(*draw) (&nr, (Sphere const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_HSIP);
							_hoops_SCHGH(nr);
						}
						else
#endif
						{
							_hoops_SIIGA		draw = dc->_hoops_IPCI->draw_3d_sphere;

							do {
								(*draw) (nr, (Sphere const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
									goto Done;
							} while (dc->_hoops_RAI->type == _hoops_HSIP);
						}
					}
					//_hoops_CGPGR
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, _hoops_HSIP);
				}	break;

				case _hoops_SGCP: {
					if (_hoops_ICCSP (nr, _hoops_ARCP) && ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE)) {
						dc->_hoops_SCGC |= _hoops_ARCP|_hoops_ACIP;

#ifndef DISABLE_CALLBACKS
						if (nr->_hoops_RSGC->action.draw_3d_geometry != null) {
							_hoops_GCIGA		draw;

							draw = (_hoops_GCIGA)nr->_hoops_RSGC->action.draw_3d_geometry;
							_hoops_HCHGH(nr, _hoops_PSRCR);

							do {
								(*draw) (&nr, (Ellipse const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_SGCP);
							_hoops_SCHGH(nr);
						}
						else
#endif
						{
							_hoops_RCIGA		draw = dc->_hoops_IPCI->draw_3d_ellipse;

							do {
								(*draw) (nr, (Ellipse const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
									goto Done;
							} while (dc->_hoops_RAI->type == _hoops_SGCP);
						}
					}
					//_hoops_CGPGR
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, _hoops_SGCP);
				}	break;

				case _hoops_CGCP: {
					if (_hoops_ICCSP (nr, _hoops_ARCP) && ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE)) {
						dc->_hoops_SCGC |= _hoops_ARCP|_hoops_ACIP;

#ifndef DISABLE_CALLBACKS
						if (nr->_hoops_RSGC->action.draw_3d_ellipse != null ||
							nr->_hoops_RSGC->action.draw_3d_geometry != null) {
							_hoops_GCIGA		draw;

							if (nr->_hoops_RSGC->action.draw_3d_ellipse != null) {
								draw = nr->_hoops_RSGC->action.draw_3d_ellipse;
								_hoops_HCHGH(nr, _hoops_RCRCR);
							}
							else {
								draw = (_hoops_GCIGA)nr->_hoops_RSGC->action.draw_3d_geometry;
								_hoops_HCHGH(nr, _hoops_PSRCR);
							}
							do {
								(*draw) (&nr, (Ellipse const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_CGCP);
							_hoops_SCHGH(nr);
						}
						else
#endif
						{
							_hoops_RCIGA		draw = dc->_hoops_IPCI->draw_3d_ellipse;

							do {
								(*draw) (nr, (Ellipse const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
									goto Done;
							} while (dc->_hoops_RAI->type == _hoops_CGCP);
						}
					}
					//_hoops_CGPGR
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, _hoops_CGCP);
				}	break;

				case _hoops_RIIP: {
					if (_hoops_ICCSP (nr, _hoops_AIIP) && ANYBIT (_hoops_RGP, T_LINES)) {
						dc->_hoops_SCGC |= _hoops_AIIP;

#ifndef DISABLE_CALLBACKS
						if (nr->_hoops_RSGC->action.draw_3d_elliptical_arc != null ||
							nr->_hoops_RSGC->action.draw_3d_geometry != null) {
							_hoops_ACIGA		draw;

							if (nr->_hoops_RSGC->action.draw_3d_elliptical_arc != null) {
								draw = nr->_hoops_RSGC->action.draw_3d_elliptical_arc;
								_hoops_HCHGH(nr, _hoops_ACRCR);
							}
							else {
								draw = (_hoops_ACIGA)nr->_hoops_RSGC->action.draw_3d_geometry;
								_hoops_HCHGH(nr, _hoops_PSRCR);
							}

							do {
								(*draw) (&nr, (Elliptical_Arc const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_RIIP);
							_hoops_SCHGH(nr);
						}
						else
#endif
						{
							_hoops_PCIGA		draw = dc->_hoops_IPCI->draw_3d_elliptical_arc;

							do {
								(*draw) (nr, (Elliptical_Arc const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
									goto Done;
							} while (dc->_hoops_RAI->type == _hoops_RIIP);
						}
					}
					//_hoops_CGPGR
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, _hoops_RIIP);
				}	break;

				case _hoops_GIIP: {
					if (_hoops_ICCSP (nr, _hoops_AIIP) && ANYBIT (_hoops_RGP, T_LINES)) {
						dc->_hoops_SCGC |= _hoops_AIIP;

#ifndef DISABLE_CALLBACKS
						if (nr->_hoops_RSGC->action.draw_3d_elliptical_arc != null ||
							nr->_hoops_RSGC->action.draw_3d_geometry != null) {
							_hoops_ACIGA		draw;

							if (nr->_hoops_RSGC->action.draw_3d_elliptical_arc != null) {
								draw = nr->_hoops_RSGC->action.draw_3d_elliptical_arc;
								_hoops_HCHGH(nr, _hoops_ACRCR);
							}
							else {
								draw = (_hoops_ACIGA)nr->_hoops_RSGC->action.draw_3d_geometry;
								_hoops_HCHGH(nr, _hoops_PSRCR);
							}

							do {
								(*draw) (&nr, (Elliptical_Arc const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_GIIP);
							_hoops_SCHGH(nr);
						}
						else
#endif
						{
							_hoops_PCIGA		draw = dc->_hoops_IPCI->draw_3d_elliptical_arc;

							do {
								(*draw) (nr, (Elliptical_Arc const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
									goto Done;
							} while (dc->_hoops_RAI->type == _hoops_GIIP);
						}
					}
					//_hoops_CGPGR
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, _hoops_GIIP);
				}	break;

				case _hoops_GRCP: {
					if (_hoops_ICCSP (nr, _hoops_ARCP) && ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE)) {
						dc->_hoops_SCGC |= _hoops_ARCP|_hoops_ACIP;

#ifndef DISABLE_CALLBACKS
						if (nr->_hoops_RSGC->action.draw_3d_geometry != null) {
							_hoops_ACIGA		draw;

							draw = (_hoops_ACIGA)nr->_hoops_RSGC->action.draw_3d_geometry;
							_hoops_HCHGH(nr, _hoops_PSRCR);

							do {
								(*draw) (&nr, (Elliptical_Arc const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_GRCP);
							_hoops_SCHGH(nr);
						}
						else
#endif
						{
							_hoops_PCIGA		draw = dc->_hoops_IPCI->draw_3d_elliptical_arc;

							do {
								(*draw) (nr, (Elliptical_Arc const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
									goto Done;
							} while (dc->_hoops_RAI->type == _hoops_GRCP);
						}
					}
					//_hoops_CGPGR
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, _hoops_GRCP);
				}	break;

				case _hoops_RRCP: {
					if (_hoops_ICCSP (nr, _hoops_ARCP) && ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE)) {
						dc->_hoops_SCGC |= _hoops_ARCP|_hoops_ACIP;
#ifndef DISABLE_CALLBACKS
						if (nr->_hoops_RSGC->action.draw_3d_geometry != null) {
							_hoops_ACIGA		draw;

							draw = (_hoops_ACIGA)nr->_hoops_RSGC->action.draw_3d_geometry;
							_hoops_HCHGH(nr, _hoops_PSRCR);

							do {
								(*draw) (&nr, (Elliptical_Arc const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_RRCP);
							_hoops_SCHGH(nr);
						}
						else
#endif
						{
							_hoops_PCIGA		draw = dc->_hoops_IPCI->draw_3d_elliptical_arc;

							do {
								(*draw) (nr, (Elliptical_Arc const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
									goto Done;
							} while (dc->_hoops_RAI->type == _hoops_RRCP);
						}
					}
					//_hoops_CGPGR
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, _hoops_RRCP);
				}	break;

				case _hoops_RCIP: {
					if (_hoops_ICCSP (nr, _hoops_ACIP) && ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE)) {
						dc->_hoops_SCGC |= _hoops_ACIP;

#ifndef DISABLE_CALLBACKS
						if (nr->_hoops_RSGC->action.draw_3d_polygon != null ||
							nr->_hoops_RSGC->action.draw_3d_geometry != null) {
							_hoops_HCIGA		draw;

							if (nr->_hoops_RSGC->action.draw_3d_polygon != null) {
								draw = nr->_hoops_RSGC->action.draw_3d_polygon;
								_hoops_HCHGH(nr, _hoops_HIRCR);
							}
							else {
								draw = (_hoops_HCIGA)nr->_hoops_RSGC->action.draw_3d_geometry;
								_hoops_HCHGH(nr, _hoops_PSRCR);
							}

							do {
								(*draw) (&nr, (Polygon const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_RCIP);
							_hoops_SCHGH(nr);
						}
						else
#endif
						{
							_hoops_ICIGA		draw = dc->_hoops_IPCI->draw_3d_polygon;

							do {
								(*draw) (nr, (Polygon const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
									goto Done;
							} while (dc->_hoops_RAI->type == _hoops_RCIP);
						}
					}
					//_hoops_CGPGR
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, _hoops_RCIP);
				}	break;

				case _hoops_GGCP: {
					if (_hoops_ICCSP (nr, _hoops_RGCP|_hoops_PCSI) &&
						ANYBIT (_hoops_RGP, T_FACES|T_ANY_GRID_EDGE|T_VERTICES)) {
						dc->_hoops_SCGC |= _hoops_RGCP|_hoops_ACIP;

#ifndef DISABLE_CALLBACKS
						if (nr->_hoops_RSGC->action.draw_3d_grid != null ||
							nr->_hoops_RSGC->action.draw_3d_geometry != null) {
							_hoops_CCIGA	draw;

							if (nr->_hoops_RSGC->action.draw_3d_grid != null) {
								draw = nr->_hoops_RSGC->action.draw_3d_grid;
								_hoops_HCHGH(nr, _hoops_SIRCR);
							}
							else {
								draw = (_hoops_CCIGA)nr->_hoops_RSGC->action.draw_3d_geometry;
								_hoops_HCHGH(nr, _hoops_PSRCR);
							}

							do {
								(*draw) (&nr, (Grid const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_GGCP);
							_hoops_SCHGH(nr);
						}
						else
#endif
						{
							_hoops_SCIGA	draw = dc->_hoops_IPCI->draw_3d_grid;

							do {
								(*draw) (nr, (Grid const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
									goto Done;
							} while (dc->_hoops_RAI->type == _hoops_GGCP);
						}
					}
					//_hoops_CGPGR
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, _hoops_GGCP);
				}	break;

				case _hoops_ICIP: {
					if (_hoops_ICCSP (nr, _hoops_CCIP) && ANYBIT (_hoops_RGP, T_ANY_LIGHTS|T_FACES)) {
						dc->_hoops_SCGC |= _hoops_CCIP;
#ifndef DISABLE_CALLBACKS
						if (nr->_hoops_RSGC->action.draw_3d_geometry != null) {
							_hoops_CICHP			draw;

							draw = nr->_hoops_RSGC->action.draw_3d_geometry;

							do {
								(*draw) (&nr, dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_ICIP);
							_hoops_SCHGH(nr);
						}
						else
#endif
						{
							_hoops_IRCGA	draw = dc->_hoops_IPCI->_hoops_HRCGA;

							do {
								(*draw) (nr, (Light const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
									goto Done;
							} while (dc->_hoops_RAI->type == _hoops_ICIP);
						}
					}
					//_hoops_CGPGR
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, _hoops_ICIP);
				}	break;

				case _hoops_GSIP:
				case _hoops_SCIP: {
					Type type = dc->_hoops_RAI->type;
					if (_hoops_ICCSP (nr, _hoops_RSIP|_hoops_PCSI)) {
						dc->_hoops_SCGC |= _hoops_RSIP;

						_hoops_CRCP *	_hoops_ARPGR;
						if ((_hoops_ARPGR = dc->_hoops_RAI->owner) != null)
							_hoops_ARPGR->_hoops_RHAGR._hoops_PRPGR(dc->_hoops_RIGC->thread_id);

#ifndef DISABLE_CALLBACKS
						if (nr->_hoops_RSGC->action.draw_3d_polyhedron != null ||
							nr->_hoops_RSGC->action.draw_3d_geometry != null) {
							_hoops_CHIGA			draw;

							if (nr->_hoops_RSGC->action.draw_3d_polyhedron) {
								draw = nr->_hoops_RSGC->action.draw_3d_polyhedron;
								_hoops_HCHGH(nr, _hoops_GCRCR);
							}
							else {
								draw = (_hoops_CHIGA)nr->_hoops_RSGC->action.draw_3d_geometry;
								_hoops_HCHGH(nr, _hoops_PSRCR);
							}

							do {
								(*draw) (&nr, (Polyhedron const *)dc->_hoops_RAI);

								if (dc->_hoops_AHSI != null && dc->_hoops_AHSI->_hoops_AARGH != null) {
									_hoops_SCHGH(nr);
									if (_hoops_ARPGR != null)
										_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
									return dc->_hoops_RAI;
								}
								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									if (_hoops_ARPGR != null)
										_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
									goto Done;
								}
							} while (dc->_hoops_RAI->type == type);
							_hoops_SCHGH(nr);
						}
						else
#endif
						{
							_hoops_SHIGA	draw = dc->_hoops_IPCI->draw_3d_polyhedron;

							do {
								(*draw) (nr, (Polyhedron const *)dc->_hoops_RAI);

								if (dc->_hoops_AHSI != null && dc->_hoops_AHSI->_hoops_AARGH != null) {
									if (_hoops_ARPGR != null)
										_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
									return dc->_hoops_RAI;
								}
								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									if (_hoops_ARPGR != null)
										_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
									goto Done;
								}
							} while (dc->_hoops_RAI->type == type);
						}

						if (_hoops_ARPGR != null)
							_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
					}
					//_hoops_CGPGR
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, type);
				}	break;

				case _hoops_PCIP: {
					if (_hoops_ICCSP (nr, _hoops_HCIP) && ANYBIT (_hoops_RGP, T_MARKERS)) {
						dc->_hoops_SCGC |= _hoops_HCIP;

#ifndef DISABLE_CALLBACKS
						/* _hoops_AA _hoops_SPR _hoops_HPGR _hoops_IRS _hoops_GHIR _hoops_IH _hoops_ASGC */
						if (nr->_hoops_RSGC->action.draw_3d_marker != null ||
							nr->_hoops_RSGC->action.draw_3d_geometry != null) {
							_hoops_IHCHP		draw;

							if (nr->_hoops_RSGC->action.draw_3d_marker != null) {
								draw = nr->_hoops_RSGC->action.draw_3d_marker;
								_hoops_HCHGH(nr, _hoops_RIRCR);
							}
							else {
								draw = (_hoops_IHCHP)nr->_hoops_RSGC->action.draw_3d_geometry;
								_hoops_HCHGH(nr, _hoops_PSRCR);
							}

							do {
								(*draw) (&nr, (Marker const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_PCIP);
							_hoops_SCHGH(nr);
						}
						else if (single || nr->_hoops_IRR->_hoops_SRI == _hoops_GAI ||
								 nr->_hoops_RSGC->action.draw_dc_marker != null ||
								 nr->_hoops_RSGC->action.draw_dc_polymarker != null) {
							_hoops_SGCGA		draw = HD_Std_3D_Marker;

							do {
								(*draw) (nr, (Marker const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
									goto Done;
							} while (dc->_hoops_RAI->type == _hoops_PCIP);
						}
						else
#endif
						{
							Point			points[1024];
							Marker const *	first = (Marker const*)dc->_hoops_RAI;
							int				count = 0;

							do {
								if (((Marker const *)dc->_hoops_RAI)->orientation)
									_hoops_AGCGH (nr, (Marker const *)dc->_hoops_RAI);
								else {
									points[count++] = ((Marker const *)dc->_hoops_RAI)->_hoops_CSAI;

									if (count == _hoops_GGAPR(points)) {
										HD_Markers_To_Polymarker (nr, count, points);
										count = 0;
										first = (Marker const *) dc->_hoops_RAI;
									}
								}
								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
									break;
							} while (dc->_hoops_RAI->type == _hoops_PCIP);

							if (count == 1)
								_hoops_AGCGH (nr, first);
							else if (count > 0)
								HD_Markers_To_Polymarker (nr, count, points);

							if (single || dc->_hoops_RAI == null)
								goto Done;
						}
					}
					//_hoops_CGPGR
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, _hoops_PCIP);
				}	break;

				case _hoops_PIRS: {
					if (_hoops_ICCSP (nr, _hoops_HCIP) && ANYBIT (_hoops_RGP, T_MARKERS)) {
						dc->_hoops_SCGC |= _hoops_HCIP;

#ifndef DISABLE_CALLBACKS
						if (nr->_hoops_RSGC->action.draw_3d_marker != null) {
							_hoops_IHCHP		draw;

							draw = nr->_hoops_RSGC->action.draw_3d_marker;
							_hoops_HCHGH(nr, _hoops_RIRCR);

							do {
								_hoops_GRPGR const *		_hoops_CPAI = (_hoops_GRPGR const *)dc->_hoops_RAI;

								for (int i=0; i<_hoops_CPAI->count; ++i) {
									Marker *			marker;
									int					index = _hoops_CPAI->mapping[i] & ~_hoops_RIRIR;

									ZALLOC (marker, Marker);
									marker->type = _hoops_PCIP;
									marker->_hoops_HIHI = 1;
									marker->owner = _hoops_CPAI->owner;
									marker->key =  HOOPS_WORLD->_hoops_GCHCA.table[index].key;
									marker->_hoops_CSAI = _hoops_CPAI->points[i];
									if (BIT (_hoops_CPAI->mapping[i], _hoops_RIRIR))
										marker->_hoops_RRHH |= _hoops_GGCCA;

									dc->_hoops_RAI = marker;
									(*draw) (&nr, (Marker const *)dc->_hoops_RAI);

									if (BIT (marker->_hoops_RRHH, _hoops_GGCCA))
										_hoops_CPAI->mapping[i] |= _hoops_RIRIR;
									else
										_hoops_CPAI->mapping[i] &= ~_hoops_RIRIR;

									_hoops_HPRH (marker);
								}
								dc->_hoops_RAI = _hoops_CPAI;

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_PIRS);
							_hoops_SCHGH(nr);
						}
						else if (nr->_hoops_RSGC->action.draw_3d_geometry != null) {
							_hoops_CIPSP		draw;

							draw = (_hoops_CIPSP)nr->_hoops_RSGC->action.draw_3d_geometry;
							_hoops_HCHGH(nr, _hoops_PSRCR);

							do {
								(*draw) (&nr, (_hoops_GRPGR const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_PIRS);
							_hoops_SCHGH(nr);
						}
						else if (single || nr->_hoops_IRR->_hoops_SRI == _hoops_GAI ||
								 nr->_hoops_RSGC->action.draw_dc_marker != null ||
								 nr->_hoops_RSGC->action.draw_dc_polymarker != null) {
							do {
								_hoops_GRPGR const *		_hoops_CPAI = (_hoops_GRPGR const *)dc->_hoops_RAI;

								for (int i=0; i<_hoops_CPAI->count; ++i) {
									Marker *			marker;
									int					index = _hoops_CPAI->mapping[i] & ~_hoops_RIRIR;

									ZALLOC (marker, Marker);
									marker->type = _hoops_PCIP;
									marker->_hoops_HIHI = 1;
									marker->key =  HOOPS_WORLD->_hoops_GCHCA.table[index].key;
									marker->_hoops_CSAI = _hoops_CPAI->points[i];
									if (BIT (_hoops_CPAI->mapping[i], _hoops_RIRIR))
										marker->_hoops_RRHH |= _hoops_GGCCA;

									dc->_hoops_RAI = marker;
									HD_Std_3D_Marker (nr, (Marker const *)dc->_hoops_RAI);

									if (BIT (marker->_hoops_RRHH, _hoops_GGCCA))
										_hoops_CPAI->mapping[i] |= _hoops_RIRIR;
									else
										_hoops_CPAI->mapping[i] &= ~_hoops_RIRIR;

									_hoops_HPRH (marker);
								}
								dc->_hoops_RAI = _hoops_CPAI;

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
									goto Done;
							} while (dc->_hoops_RAI->type == _hoops_PIRS);
						}
						else
#endif
						{
							do {
								_hoops_PGCGH (nr, (_hoops_GRPGR const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
									goto Done;
							} while (dc->_hoops_RAI->type == _hoops_PIRS);
						}
					}
					//_hoops_CGPGR
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, _hoops_PIRS);
				}	break;

				case _hoops_AGCP: {
					if (_hoops_ICCSP (nr, _hoops_PGCP) && ANYBIT (_hoops_RGP, T_TEXT)) {
						dc->_hoops_SCGC |= _hoops_PGCP;

#ifndef DISABLE_CALLBACKS
						if (nr->_hoops_RSGC->action.draw_3d_text != null ||
							nr->_hoops_RSGC->action.draw_3d_geometry != null) {
							_hoops_HICHP	draw;

							if (nr->_hoops_RSGC->action.draw_3d_text != null) {
								draw = nr->_hoops_RSGC->action.draw_3d_text;
								_hoops_HCHGH(nr, _hoops_IIRCR);
							}
							else {
								draw = (_hoops_HICHP)nr->_hoops_RSGC->action.draw_3d_geometry;
								_hoops_HCHGH(nr, _hoops_PSRCR);
							}

							do {
								_hoops_HACC const *	text = (_hoops_HACC const *)dc->_hoops_RAI;

								if (text->count != 0 || text->_hoops_AAPGR != null)
									(*draw) (&nr, text);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_AGCP);
							_hoops_SCHGH(nr);
						}
						else
#endif
						{
							_hoops_PRCGA	draw = dc->_hoops_IPCI->draw_3d_text;

							do {
								_hoops_HACC const *	text = (_hoops_HACC const *)dc->_hoops_RAI;

								if (text->count != 0 || text->_hoops_AAPGR != null)
									(*draw) (nr, text);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
									goto Done;
							} while (dc->_hoops_RAI->type == _hoops_AGCP);
						}
					}
					//_hoops_CGPGR
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, _hoops_AGCP);
				}	break;

				case _hoops_HGCP: {
					if (_hoops_ICCSP (nr, _hoops_IGCP) && ANYBIT (_hoops_RGP, T_IMAGES)) {
						dc->_hoops_SCGC |= _hoops_IGCP;

#ifndef DISABLE_CALLBACKS
						if (nr->_hoops_RSGC->action.draw_3d_image != null ||
							nr->_hoops_RSGC->action.draw_3d_geometry != null) {
							_hoops_IICHP			draw;

							if (nr->_hoops_RSGC->action.draw_3d_image != null) {
								draw = nr->_hoops_RSGC->action.draw_3d_image;
								_hoops_HCHGH(nr, _hoops_CIRCR);
							}
							else {
								draw = (_hoops_IICHP)nr->_hoops_RSGC->action.draw_3d_geometry;
								_hoops_HCHGH(nr, _hoops_PSRCR);
							}

							do {
								(*draw) (&nr, (Image const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
									_hoops_SCHGH(nr);
									goto Done;
								}
							} while (dc->_hoops_RAI->type == _hoops_HGCP);
							_hoops_SCHGH(nr);
						}
						else
#endif
						{
							_hoops_ARCGA	draw = dc->_hoops_IPCI->draw_3d_image;

							do {
								(*draw) (nr, (Image const *)dc->_hoops_RAI);

								if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
									goto Done;
							} while (dc->_hoops_RAI->type == _hoops_HGCP);
						}
					}
					//_hoops_CGPGR
					if (single)
						goto Done;
					_hoops_CSHI (dc->_hoops_RAI, _hoops_HGCP);
				}	break;

				case _hoops_AHIP: {
					_hoops_PHIP const *	_hoops_RRA = (_hoops_PHIP const *)dc->_hoops_RAI;
					Geometry const *			_hoops_PPPGR = _hoops_RRA->next;

					if (nr->_hoops_IRR->_hoops_GAHA == Display_List_SEGMENT)
						dc->_hoops_SCGC |= HD_Geometry_To_Action_Mask ((Geometry const *)_hoops_RRA);

					if ((dc->_hoops_RAI = HD_Process_Geometry_Reference (nr, _hoops_RRA)) != null)
						goto _hoops_SPPGR;
					nr = _hoops_GSAGR;
					single = _hoops_RSAGR;

					if (single || (dc->_hoops_RAI = _hoops_PPPGR) == null)
						goto Done;
				}	break;


				/*
				 * _hoops_ASC _hoops_HPCSS _hoops_IPCSS
				 */

				case _hoops_GHPGR: {
					do {
						_hoops_RHPGR *	_hoops_AHPGR = (_hoops_RHPGR *)dc->_hoops_RAI;

						if (ANYBIT (_hoops_RGP, _hoops_AHPGR->which))
							_hoops_PHPGR (HEC_GEOMETRY, HES_MEMORY_PURGED,
								Sprintf_P (null, "Need to redraw all or some of '%p' -",_hoops_AHPGR->owner), "but memory has been purged from it");
						if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
							goto Done;
					} while (dc->_hoops_RAI->type == _hoops_GHPGR);
				}	break;

				case _hoops_HCIIR: {
					do {
						(*dc->_hoops_IPCI->_hoops_PPCI) (nr, (_hoops_GACR alter *)dc->_hoops_RAI);
						dc->_hoops_RAI = dc->_hoops_RAI->next;
						if (single || dc->_hoops_RAI == null)
							goto Done;
					} while (dc->_hoops_RAI->type == _hoops_HCIIR);
				}   break;

				NODEFAULT;
#if 0
				default: {
					_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, Sprintf_D (null,
													 "Unknown type '%d' in render", geometry->type));
					dc->_hoops_RAI = null;
					return null;
				}	_hoops_HHHI;
#endif
			}

			if (dc->_hoops_RAI == null)
				break;
		}

  Done:;
//		_hoops_CSPH->_hoops_IHIGA = _hoops_IRAP;
		if (dc->_hoops_SPA != dc->_hoops_ISAGR)
			dc->_hoops_SPA->geometry = null;

  _hoops_SPPGR:;
	} while (dc->_hoops_SPA != dc->_hoops_ISAGR);

	return null;
}

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
 * $Id: obf_tmp.txt 1.221 2010-12-16 19:42:16 reuben Exp $
 */


#include "hoops.h"
#include "database.h"
#include "please.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "hidden.h"
#include "adt.h"
#include "task_queue.h"


#define	_hoops_GIISS(dc)																	\
			do if (dc->_hoops_PGCC.driver_type == null) {												\
				HD_Get_Physical_Info (dc);															\
				dc->current._hoops_HAP.x = dc->_hoops_PGCC._hoops_PRPSR.x / dc->_hoops_PGCC.size.x;	\
				dc->current._hoops_HAP.y = dc->_hoops_PGCC._hoops_PRPSR.y / dc->_hoops_PGCC.size.y;	\
				dc->current._hoops_AGRS = dc->current._hoops_HAP.x / dc->current._hoops_HAP.y;		\
			} while (0)



static void _hoops_RIISS (
	_hoops_AIGPR *		_hoops_AIISS,
	bool *						_hoops_PIISS,
	_hoops_GGAGR alter *				_hoops_GHRI,
	int							request,
	void *						request_info) {
	Display_Context alter *		dc;
	bool						_hoops_IA = true;
	HThreadID					thread_id = THREAD_ID();
	bool						_hoops_HIISS=false;

	dc = (Display_Context alter *)_hoops_GHRI->_hoops_PPRPR;

	ASSERT(dc != null);

	if (dc != null &&
		dc->_hoops_GRAGH != thread_id) {
		_hoops_CAAI (dc->_hoops_RASCA);
		ASSERT(dc->_hoops_RIGC == null);
		dc->_hoops_GRAGH = thread_id;
		dc->_hoops_RIGC = _hoops_AIISS;
		_hoops_HIISS=true;
	}

	switch (request) {
		case _hoops_RAGRH: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Standard Driver called without Setup!");
		}	break;

		case _hoops_AAGSC: {
			char alter *		_hoops_PCRSR;

			if (dc->_hoops_AAHSR != null)
				break;				// _hoops_AIAH _hoops_HHPHA

			dc->_hoops_GHRI = _hoops_GHRI;
			dc->_hoops_AAHSR = _hoops_GHRI->owner;

			if (dc->_hoops_AAHSR->type == _hoops_IRCP &&
				_hoops_GHRI->owner->name.length > 0) {
				dc->_hoops_HCRSR = _hoops_GHRI->owner->name.length + 1;
				POOL_ALLOC_ARRAY (_hoops_PCRSR, dc->_hoops_HCRSR, char, dc->memory_pool);
				_hoops_AAHR (_hoops_GHRI->owner->name.text, _hoops_PCRSR);
				dc->_hoops_PCRSR = _hoops_PCRSR;
			}
			//_hoops_SHS {
			//	_hoops_CSPH->_hoops_IIISS = 0;
			//	_hoops_CSPH->_hoops_CIISS = _hoops_IRAP;
			//}

			//_hoops_SIISS (_hoops_CSPH->_hoops_GCISS, _hoops_RCISS, _hoops_APPC _hoops_ICHRR _hoops_RCIC *);
			//_hoops_CSPH->_hoops_AAP._hoops_CRSAI._hoops_SPCC = 0; /* _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_HPCS _hoops_ARI */

			/* _hoops_IRHH _hoops_AAP _hoops_CCCI */
			HD_Upwind_Driver_Options (dc);

			_hoops_CAAI (HOOPS_WORLD->_hoops_APHGI);

			if (!(*dc->_hoops_ACPGR->start_device)(dc)) {
				/* _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_CSPH (_hoops_HRGHR - _hoops_AAHAR _hoops_RHPP _hoops_GHCA _hoops_GHHA _hoops_GPP _hoops_IHHH) */

				_hoops_APAI (dc->_hoops_RASCA);
				_hoops_APAI (HOOPS_WORLD->_hoops_APHGI);

				if (_hoops_GHRI->_hoops_PPRPR != null)
					if (!HD_Standard_Driver (dc->_hoops_RIGC, _hoops_GHRI, _hoops_IAGSC, null)) {
						/* ? _hoops_PAHA'_hoops_RA _hoops_IHPS */
						ASSERT(0); // _hoops_RHAP _hoops_SCH?
					}

				_hoops_IA = false;
				dc = null;
				break;
			}

			_hoops_APAI (HOOPS_WORLD->_hoops_APHGI);

			//_hoops_CSPH->_hoops_ACISS = _hoops_RCPP;
			//_hoops_CSPH->_hoops_PCISS = _hoops_RCPP;
		}	break;

		case _hoops_HAGSC: {
			_hoops_GIISS (dc);

			// _hoops_HCISS _hoops_ICISS _hoops_SPR _hoops_HCHSR
			_hoops_GSPGR _hoops_CCISS = _hoops_RCCA(_hoops_CPRGH);

			long _hoops_SCISS = _hoops_RCCA(_hoops_CSRGH);
			long _hoops_GSISS = _hoops_RCCA(_hoops_SSRGH);

			long _hoops_RSISS = _hoops_RCCA(_hoops_SHPSA);
			long _hoops_ASISS = _hoops_RCCA(_hoops_CIPSA);
			long _hoops_PSISS = _hoops_RCCA(_hoops_ISRGH);

			float _hoops_GGAGH = _hoops_RCCA(_hoops_GGAGH);
			float _hoops_RGAGH = _hoops_RCCA(_hoops_RGAGH);

			SET_MEMORY(dc->_hoops_IGGI, sizeof(_hoops_HPRGH), 0);

			_hoops_RCCA(_hoops_CPRGH) = _hoops_CCISS;

			_hoops_RCCA(_hoops_CSRGH) = _hoops_SCISS;
			_hoops_RCCA(_hoops_SSRGH) = _hoops_GSISS;

			_hoops_RCCA(_hoops_SHPSA) = _hoops_RSISS;
			_hoops_RCCA(_hoops_CIPSA) = _hoops_ASISS;
			_hoops_RCCA(_hoops_ISRGH) = _hoops_PSISS;

			_hoops_RCCA(_hoops_GGAGH) = _hoops_GGAGH;
			_hoops_RCCA(_hoops_RGAGH) = _hoops_RGAGH;

			_hoops_IA = (*dc->_hoops_ACPGR->update) (dc, *(Activity *)request_info);

			_hoops_RCCA(_hoops_CSRGH) += _hoops_RCCA(_hoops_PCCA);
			_hoops_RCCA(_hoops_SSRGH) += _hoops_RCCA(_hoops_AGCAR);
		}	break;

		case _hoops_SSRPH: {
			_hoops_GIISS (dc);

			if (!BIT(dc->_hoops_PGCC.flags, _hoops_HSHSR)) {
				_hoops_IA = false;
				break;
			}

			if (BIT(dc->flags, _hoops_SAISR) &&
				!BIT(dc->flags, _hoops_GIRIP) &&
				!dc->options._hoops_CRSSP) {
				/* _hoops_HGAPR _hoops_ISCC _hoops_RAIGR _hoops_RCASA _hoops_IS _hoops_HAISR _hoops_RH _hoops_RHPP _hoops_CRGR _hoops_IPAC _hoops_SSHGR.
				 * _hoops_HSISS-_hoops_IPAC _hoops_CGH _hoops_SHH _hoops_IRS _hoops_AGSRH _hoops_ACPH _hoops_GASR _hoops_PCPH!
				 *
				 * (_hoops_IRCHS _hoops_SCH _hoops_RGR _hoops_PPRRR _hoops_GHCA _hoops_CRHR _hoops_CGRSC _hoops_HII _hoops_IHGS _hoops_SHSS
				 *	_hoops_IS _hoops_RCCS _hoops_PCCP _hoops_PAAP.)
				 */
				_hoops_CAAI (HOOPS_WORLD->_hoops_APHGI);
				(*dc->_hoops_ACPGR->init_update) (dc);
				(*dc->_hoops_ACPGR->finish_update) (dc);
				_hoops_APAI (HOOPS_WORLD->_hoops_APHGI);
			}
		}	break;

		case _hoops_PAGSC: {
			Net_Rendition			nr;

			if (dc->_hoops_GHSS._hoops_GHRI != null) {
				_hoops_HPRH (dc->_hoops_GHSS._hoops_GHRI);
				dc->_hoops_GHSS._hoops_GHRI = null;
			}
			if (dc->_hoops_GHSS.image != null) {
				_hoops_HPRH (dc->_hoops_GHSS.image);
				dc->_hoops_GHSS.image = null;
			}

			if (dc->_hoops_IAHGH != null) {
				_hoops_HPRH (dc->_hoops_IAHGH);
				dc->_hoops_IAHGH = null;
			}

			if ((nr = dc->_hoops_SHCIP) != null)
				_hoops_ASHGH(nr);

			HD_Clean_DC_Breadcrumbs (dc);
			// _hoops_RGR _hoops_SPR _hoops_HRGR *_hoops_HAR* _hoops_GIR _hoops_GGR _hoops_ISISS
			HD_Free_Sprite_List (dc, &dc->_hoops_CRHGH);

			if (BIT(dc->flags, _hoops_SAISR)) {
#if 0
				/* _hoops_RGR _hoops_GHCA _hoops_HAR _hoops_IPHR _hoops_RPP _hoops_IASRH _hoops_ISHP _hoops_PPR _hoops_RH _hoops_CAGH _hoops_HRGR _hoops_PPRGA */
				HD_Upwind_Driver_Options (dc);
#endif
				HD_Get_Current_Info (dc);

				dc->flags &= ~_hoops_SAISR;		/* _hoops_PRAR, _hoops_HAAI... */
				_hoops_CAAI (HOOPS_WORLD->_hoops_APHGI);
				(*dc->_hoops_ACPGR->init_update) (dc);
				if (nr) {
					(*dc->_hoops_ACPGR->init_picture) (nr);
					HD_Unload_All_Fonts(dc);
					(*dc->_hoops_ACPGR->finish_picture) (nr, false);
				}
				(*dc->_hoops_ACPGR->free_outer_window) (dc);
				(*dc->_hoops_ACPGR->finish_update) (dc);
				_hoops_APAI (HOOPS_WORLD->_hoops_APHGI);
				HD_Free_Colors (dc);
			}

			HD_Free_Fonts (dc);
			HD_Free_Hidden_Item_Cache (dc);
			_hoops_CAAI (HOOPS_WORLD->_hoops_APHGI);
			(*dc->_hoops_ACPGR->stop_device) (dc);
			_hoops_APAI (HOOPS_WORLD->_hoops_APHGI);
		}	break;

		case _hoops_IAGSC: {
			if (dc != null) {	/* _hoops_GHCA _hoops_SHH _hoops_IRAP _hoops_RPP _hoops_CCAGR _hoops_SRSH */
				/* _hoops_IGHHH: _hoops_HCR _hoops_AGCR _hoops_AAAPR _hoops_PIHA _hoops_SHH _hoops_RAGA _hoops_AGSRH
				 * _hoops_CIGS _hoops_HSH _hoops_ARPP _hoops_APISR _hoops_HRGR _hoops_PIGS, _hoops_GGR
				 * _hoops_AGIR _hoops_RH _hoops_GASCA _hoops_ISHS!
				 */

				if (dc->_hoops_AGHPP) {
					ASSERT(dc->_hoops_AGHPP->Count() == 0);
					delete dc->_hoops_AGHPP;
					delete dc->_hoops_HGHPP;
				}

				if (dc->_hoops_ISPGH)
					delete dc->_hoops_ISPGH;

				if (dc->_hoops_CSPGH)
					delete dc->_hoops_CSPGH;

				_hoops_RGAIR (dc->options._hoops_IAPIR);

				_hoops_RGAIR (dc->_hoops_PGCC._hoops_GSPGH);
				_hoops_RGAIR (dc->_hoops_PGCC._hoops_RSPGH);

				if (dc->_hoops_HCRSR > 0)
					FREE_ARRAY (dc->_hoops_PCRSR, dc->_hoops_HCRSR, char);

				if (dc->_hoops_GPHGH > 0)
					FREE_ARRAY (dc->_hoops_RPHGH, dc->_hoops_GPHGH, char);

				dc->_hoops_SHCIP.release();

				if (dc->global_bounds!=null)
					dc->global_bounds.release();

				HI_Free_Name_List(dc->options._hoops_HAPIR);

				if (dc->options._hoops_APPIR > 0)
					FREE_ARRAY (dc->options._hoops_RPPIR, dc->options._hoops_APPIR, int);

				if (dc->_hoops_AHGCP) {
					FREE_ARRAY (dc->_hoops_AHGCP->data,
							dc->_hoops_AHGCP->allocated, Hidden_Tristrip *);
					FREE (dc->_hoops_AHGCP, _hoops_SISIP);
				}

				if (dc->_hoops_PGPCP != null)
					FREE_ARRAY (dc->_hoops_PGPCP, dc->_hoops_PAHCP, _hoops_ARPA);
				if (dc->_hoops_AIACP != null)
					FREE_ARRAY_ALIGNED (dc->_hoops_AIACP, dc->_hoops_PIACP, _hoops_ARPA, 16);

				if (dc->options._hoops_SAPIR)
					HI_Free_Font_Names (dc->options._hoops_SAPIR);

				if (dc->options._hoops_GPPIR)
					HI_Free_Font_Names (dc->options._hoops_GPPIR);

				if (dc->_hoops_IRHGH) {
					_hoops_AAPIR	*next, *_hoops_IRHGH = dc->_hoops_IRHGH;

					while (_hoops_IRHGH != null) {
						next = _hoops_IRHGH->next;
						_hoops_RGAIR(_hoops_IRHGH->name);
						FREE (_hoops_IRHGH, _hoops_AAPIR);
						_hoops_IRHGH = next;
					}
				}

#ifndef DISABLE_CUT_GEOMETRY
				if (dc->_hoops_CRIGA != null)
					HD_Delete_Cut_Geometry_Pieces (dc);
#endif

#				if defined(WIN32_SYSTEM) && !defined(NUTCRACKER)
#				  ifdef DYNAMIC_LOADER
					/* _hoops_CSISS _hoops_RHPP _hoops_ASCSR (_hoops_RPP _hoops_PSP _hoops_SPR _hoops_SHS _hoops_HRGR _hoops_GRP _hoops_SCH) */
					_hoops_CAAI (HOOPS_WORLD->_hoops_APHGI);
					HD_W32_UnLoad_Dynamic_Driver (dc->_hoops_GHRI->action);
					_hoops_APAI (HOOPS_WORLD->_hoops_APHGI);
#				  endif
#				endif /* _hoops_HIHPH */


				dc->_hoops_IPCI = null;
				dc->_hoops_ACPGR.release();

				delete dc->_hoops_ISAGR;

				ASSERT(!dc->_hoops_CISCP);

#ifdef VALIDATE_MEMORY
				size_t allocated = 0;
				HI_Relinquish_Memory_On_Pool (dc->memory_pool);
				HI_Memory_On_Pool(dc->memory_pool, &allocated);
				if (allocated > 0) {
					//_hoops_GHCC (_hoops_SSISS, _hoops_GGCSS, "_hoops_HIARC _hoops_AGCGR _hoops_AASAR _hoops_GGR _hoops_RHPP _hoops_PPGS _hoops_ICGAR.");
					HI_Dump_Allocation_Metadata (dc->memory_pool, "driver memory pool");
				}
#endif

				HI_Destroy_Memory_Pool(dc->memory_pool);

				_hoops_APAI (dc->_hoops_RASCA);
				DESTROY_MUTEX (dc->_hoops_RASCA);

				FREE (dc->_hoops_IGGI, _hoops_HPRGH);
				FREE (dc->_hoops_CAHGH, _hoops_HPRGH);
				FREE (dc, Display_Context);
				dc = null;
				_hoops_GHRI->_hoops_PPRPR = null;
			}
			_hoops_GHRI->_hoops_CGPIR |= _hoops_SGPIR;
		}	break;

		case _hoops_HSRPH: {
			Button				button;
			int						_hoops_RGCSS;

			/* _hoops_IRAA _hoops_HCR _hoops_RH _hoops_CRGIA _hoops_IIH _hoops_CHR */
			if (BIT(dc->flags, _hoops_SAISR) && !dc->options._hoops_IRSSP) {
				_hoops_CAAI (HOOPS_WORLD->_hoops_APHGI);
				while ((*dc->_hoops_ACPGR->_hoops_ISCSP) (dc, &button, &_hoops_RGCSS))
					HI_Queue_Keyboard_Event (_hoops_GHRI, button, _hoops_RGCSS);
				_hoops_APAI (HOOPS_WORLD->_hoops_APHGI);
			}
		}	break;

		case _hoops_PSRPH: {
			int						status;
			int						_hoops_CHCGR, _hoops_SHCGR;

			/* _hoops_IRAA _hoops_HPGR _hoops_ICRP _hoops_SPR _hoops_ISAR */
			if (BIT(dc->flags, _hoops_SAISR) && !dc->options._hoops_IRSSP) {
				bool	_hoops_AGCSS=false;
				_hoops_CAAI (HOOPS_WORLD->_hoops_APHGI);
				_hoops_AGCSS = (*dc->_hoops_ACPGR->_hoops_HSCSP) (dc, &status, &_hoops_CHCGR, &_hoops_SHCGR);
				_hoops_APAI (HOOPS_WORLD->_hoops_APHGI);
				if (_hoops_AGCSS)
					HD_Queue_Pixel_Location_Event (dc, status, _hoops_CHCGR, _hoops_SHCGR);
			}
		}	break;

		case _hoops_HGAPH: {
			Button					button;
			int						status;
			int						_hoops_CHCGR, _hoops_SHCGR;

			if (BIT(dc->flags, _hoops_SAISR) && !dc->options._hoops_IRSSP) {
				_hoops_CAAI (HOOPS_WORLD->_hoops_APHGI);
				/* _hoops_IRAA _hoops_HCR _hoops_RH _hoops_CRGIA _hoops_IIH _hoops_CHR */
				if (dc->_hoops_ACPGR->_hoops_ISCSP != HD_No_Such_Keyboard)
					while ((*dc->_hoops_ACPGR->_hoops_ISCSP)(dc, &button,
															   &status)) {}

				/* _hoops_IRAA _hoops_HPGR _hoops_ICRP _hoops_SPR _hoops_ISAR */
				if (dc->_hoops_ACPGR->_hoops_HSCSP != HD_No_Such_Locater)
					(void)(*dc->_hoops_ACPGR->_hoops_HSCSP)(dc,&status,&_hoops_CHCGR,&_hoops_SHCGR);
				_hoops_APAI (HOOPS_WORLD->_hoops_APHGI);
			}
		}	break;


		/* _hoops_AGSIP! _hoops_HPCAR _hoops_AGCR _hoops_CHR _hoops_GPRS _hoops_SIHH _hoops_IGRC _hoops_GHGA _hoops_PA
				  _hoops_AHCA _hoops_CAPR. */

		case _hoops_SPRPH: {
			if (!BIT(dc->_hoops_PGCC.flags, _hoops_RSHSR) ||
				dc->_hoops_ACPGR->_hoops_HSCSP == HD_No_Such_Locater)
				_hoops_IA = false;
		}	break;

		case _hoops_GHRPH: {
		}	break;

		case _hoops_RHRPH: {
			if (!BIT(dc->_hoops_PGCC.flags, _hoops_RSHSR) ||
				dc->_hoops_ACPGR->_hoops_HSCSP == HD_No_Such_Locater)
				_hoops_IA = false;
		}	break;

		case _hoops_AHRPH: {
		}	break;

		case _hoops_PHRPH: {
			if (!BIT(dc->_hoops_PGCC.flags, _hoops_RSHSR) ||
				dc->_hoops_ACPGR->_hoops_HSCSP == HD_No_Such_Locater)
				_hoops_IA = false;
		}	break;

		case _hoops_HHRPH: {
		}	break;

		case _hoops_IHRPH: {
			if (!BIT(dc->_hoops_PGCC.flags, _hoops_RSHSR) ||
				dc->_hoops_ACPGR->_hoops_HSCSP == HD_No_Such_Locater)
				_hoops_IA = false;
		}	break;

		case _hoops_CHRPH: {
		}	break;

		case _hoops_APRPH: {
			_hoops_GIISS (dc);
		}	break;

		case _hoops_IPRPH:  {
		}	break;

		case _hoops_RIRPH:
		case _hoops_GIRPH: {
			_hoops_GIISS (dc);
			if (!BIT(dc->_hoops_PGCC.flags, _hoops_PSHSR) ||
				dc->_hoops_ACPGR->_hoops_ISCSP == HD_No_Such_Keyboard)
				_hoops_IA = false;
		}	break;

		case _hoops_AIRPH: {
		}	break;

		/* _hoops_AGCR _hoops_CHR _hoops_HAR _hoops_GPRS! */

		case _hoops_RISHA: {
			_hoops_IA = (*dc->_hoops_ACPGR->_hoops_GSCSP) (dc, (Selection_Event alter *)request_info);
		}	break;

		case _hoops_CAGSC: {
			if (dc != null)  {
				_hoops_GIISS (dc);
				if (!BIT(dc->flags, _hoops_SAISR))
					HD_Minimum_Update(dc);
				_hoops_IA = HD_Gather_Device_Info (dc, (_hoops_APRHH alter *)request_info);
			}
		}	break;

		case _hoops_GPGSC: {
			if (dc != null) {	/* _hoops_RPP _hoops_CCAGR _hoops_PGCSS */

				_hoops_GIISS (dc);

				_hoops_PGHGH alter *	_hoops_GCHIH = (_hoops_PGHGH alter *)request_info;

				if (!BIT(dc->flags, _hoops_SAISR) &&			/* _hoops_IIP _hoops_GPGGR? */
					(_hoops_GCHIH->item == _hoops_IARSC ||
					 _hoops_GCHIH->item == _hoops_PPRSC ||
					 _hoops_GCHIH->item == _hoops_HPRSC ||
					 BIT(dc->_hoops_PGCC.flags, _hoops_PPPGH)))
					if (!HD_Minimum_Update (dc)) {
						_hoops_IA = false;
						break;
					}

				dc->flags |= _hoops_GIRIP;
				_hoops_CAAI (HOOPS_WORLD->_hoops_APHGI);
				(*dc->_hoops_ACPGR->init_update) (dc);
				_hoops_IA = HD_Gather_Font_Info (dc, _hoops_GCHIH);
				(*dc->_hoops_ACPGR->finish_update) (dc);
				_hoops_APAI (HOOPS_WORLD->_hoops_APHGI);
				dc->flags &= ~_hoops_GIRIP;
			}
		}	break;

		case _hoops_SAGSC: {
			if (dc != null) {
				bool		_hoops_HGCSS = false;

				_hoops_GIISS (dc);

				dc->flags |= _hoops_GIRIP;
				_hoops_CAAI (HOOPS_WORLD->_hoops_APHGI);
				(*dc->_hoops_ACPGR->init_update) (dc);

				if (!dc->current._hoops_RAPGH) {
					dc->options._hoops_IASSP = true;
					dc->current._hoops_RAPGH = (*dc->_hoops_ACPGR->get_outer_window)(dc);
					_hoops_HGCSS=true;
				}
				_hoops_IA = HD_Gather_Font_Names (dc, (_hoops_RCHIH alter *)request_info);

				if (_hoops_HGCSS) {
					(*dc->_hoops_ACPGR->free_outer_window)(dc);
					dc->current._hoops_RAPGH = 0;
					dc->options._hoops_IASSP = false;
				}
				(*dc->_hoops_ACPGR->finish_update) (dc);
				_hoops_APAI (HOOPS_WORLD->_hoops_APHGI);

				dc->flags &= ~_hoops_GIRIP;
			}
		}	break;

		case _hoops_PIACA: {
			if (dc != null) { /* _hoops_RPP _hoops_CCAGR _hoops_PGCSS */
				_hoops_GIISS (dc);
				/* _hoops_IRHH _hoops_AAP _hoops_CCCI */
				HD_Upwind_Driver_Options (dc);
				_hoops_IA = HD_Gather_Window_Extent (dc, (_hoops_RIACA alter *)request_info);
			}
		}	break;

		case _hoops_IISAA: {
			if (dc != null) {/* _hoops_RPP _hoops_CCAGR _hoops_PGCSS */
				_hoops_GIISS (dc);
				/* _hoops_IRHH _hoops_AAP _hoops_CCCI */
				HD_Upwind_Driver_Options (dc);
				if (!BIT(dc->flags, _hoops_SAISR))
					HD_Minimum_Update(dc);
				_hoops_IA = HD_Gather_Screen_Extent (dc, (_hoops_RISAA alter *)request_info);
			}
		}	break;

		case _hoops_ASGPI: {
			if (dc != null) {
				if (!BIT(dc->flags, _hoops_GIRIP))
					(*dc->_hoops_ACPGR->init_update) (dc);
				(*dc->_hoops_ACPGR->_hoops_CGAGR) (dc, request_info);
				if (!BIT(dc->flags, _hoops_GIRIP))
					(*dc->_hoops_ACPGR->init_update) (dc);
			}
		}	break;

		case _hoops_GHGGC: {
			if (dc != null) {
				if (!BIT(dc->flags, _hoops_GIRIP))
					(*dc->_hoops_ACPGR->init_picture) (dc->_hoops_SHCIP);
				(*dc->_hoops_ACPGR->_hoops_ARSSP) (dc->_hoops_SHCIP, request_info);
				if (!BIT(dc->flags, _hoops_GIRIP))
					(*dc->_hoops_ACPGR->finish_picture) (dc->_hoops_SHCIP, false);
			}
		}	break;

		case _hoops_SGRHP: {
			_hoops_AHAGR alter *	sc = (_hoops_AHAGR alter *)request_info;

			(*dc->_hoops_ACPGR->init_update) (dc);

#ifndef _hoops_IGGGC
			if (sc->_hoops_IGSGP() != null) {
				HD_Delete_Octree (dc->_hoops_RIGC, sc->_hoops_APHGA, sc->_hoops_IGSGP());
				sc->_hoops_AGSGP (null);
			}
#endif

			if (sc->_hoops_PSSIR() != null) {
				HD_Free_Frame_Buffer_Info (sc->_hoops_APHGA, sc->_hoops_PSSIR());
				sc->_hoops_HSCGP (null);
			}

			_hoops_HRPA *	_hoops_HSGA = sc->_hoops_ARSGP();
			if (_hoops_HSGA != null) {
				_hoops_HSGA->_hoops_APRA.release();
				FREE (_hoops_HSGA, _hoops_HRPA);
			}
			sc->_hoops_RRSGP(null);

			(*dc->_hoops_ACPGR->finish_update) (dc);
		}	break;

		default: {
			_hoops_IA = false;	/* _hoops_HAR _hoops_SPR _hoops_SR _hoops_ACPA/_hoops_PAH _hoops_AA! */
		}	break;
	}

	*_hoops_PIISS = _hoops_IA;

	if (_hoops_HIISS && dc != null) {
		dc->_hoops_GRAGH = 0;
		dc->_hoops_RIGC = null;
		_hoops_APAI (dc->_hoops_RASCA);
	}
}



class _hoops_IGCSS : public _hoops_GCARR {
	public:
		_hoops_IGCSS (
			_hoops_AIGPR *		_hoops_AIISS,
			bool *						_hoops_IA,
			_hoops_GGAGR alter *				_hoops_GHRI,
			int							request,
			void *						request_info) :
				_hoops_AIISS(_hoops_AIISS),
				_hoops_IA(_hoops_IA),
				_hoops_GHRI(_hoops_GHRI),
				request(request),
				request_info(request_info) {

			_hoops_GHRI->_hoops_ACARR->_hoops_PCARR(this);
		};

		virtual ~_hoops_IGCSS() {}

		virtual _hoops_ICARR Type() {return _hoops_CGCSS;}

		virtual void _hoops_HCARR(bool _hoops_SCARR) {
			UNREFERENCED(_hoops_SCARR);

			HThreadID thread_id = THREAD_ID();
			LOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);
			HOOPS_WORLD->_hoops_RCPGI->ReplaceItem(thread_id, _hoops_AIISS);
			UNLOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);

			_hoops_GGAGI(_hoops_AIISS->thread_id);

			_hoops_RIISS (_hoops_AIISS, _hoops_IA, _hoops_GHRI, request, request_info);

			_hoops_IRRPR();

			LOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);
			HOOPS_WORLD->_hoops_RCPGI->ReplaceItem(thread_id, (_hoops_AIGPR *)1);
			UNLOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);

			HM_RELEASE_SEMAPHORE(_hoops_AIISS->semaphore, 1);

			delete this;
		}

	private:
		_hoops_AIGPR *		_hoops_AIISS;
		bool *						_hoops_IA;
		_hoops_GGAGR alter *				_hoops_GHRI;
		int							request;
		void *						request_info;
};


class _hoops_SGCSS : public _hoops_GCARR {
	public:
		_hoops_SGCSS (_hoops_GGAGR const * _hoops_GHRI)
			: _hoops_GHRI(_hoops_GHRI) {
			_hoops_GHRI->_hoops_GRPIR->_hoops_PCARR(this);
		};

		virtual ~_hoops_SGCSS() {;}

		virtual _hoops_ICARR Type() {return _hoops_GRCSS;}

		_hoops_GGAGR const * _hoops_RRCSS() {return _hoops_GHRI;}

		virtual bool _hoops_GCIRI(_hoops_GCARR const * _hoops_ARCSS) {
			_hoops_SGCSS const * _hoops_AGPHR = (_hoops_SGCSS const *)_hoops_ARCSS;
			return (_hoops_GHRI == _hoops_AGPHR->_hoops_GHRI);
		}

		virtual void _hoops_HCARR(bool _hoops_SCARR) {

			if (!_hoops_SCARR && !ANYBIT(_hoops_GHRI->_hoops_CGPIR, _hoops_SGPIR|_hoops_CRGSC)) {
				_hoops_AIGPR * _hoops_RIGC;
				_hoops_HCRGI(_hoops_RIGC);

				/* _hoops_HGCR _hoops_IRS _hoops_CCAH _hoops_PAAP _hoops_AIS */
				if (BIT(_hoops_GHRI->owner->_hoops_PHSI, _hoops_ARRPR)) {
					char pathname[4096];
					Sprintf_P (pathname, "%p", (void *)_hoops_GHRI->owner);
					HI_Do_One_Update (_hoops_RIGC, pathname, -1.0);
				}
				else {
					HI_Do_Update (_hoops_RIGC, -1.0, false);
				}
			}

			delete this;
		}

	private:
		_hoops_GGAGR const *	_hoops_GHRI;
};

GLOBAL_FUNCTION void HI_Queue_Actor_Update(
	_hoops_GGAGR const *	_hoops_GHRI,
	bool			_hoops_GSSIH) {

	if (!_hoops_GHRI->_hoops_GRPIR)
		((_hoops_GGAGR alter *)_hoops_GHRI)->_hoops_GRPIR = NEW(_hoops_SRIAP)(0);

	_hoops_SGCSS const * _hoops_PRCSS = NEW(_hoops_SGCSS)(_hoops_GHRI);

	if (_hoops_GSSIH) {
		_hoops_GCARR * _hoops_HPIRI = null;

		while ((_hoops_HPIRI = _hoops_GHRI->_hoops_GRPIR->_hoops_IAIRI()) != null) {
			_hoops_HPIRI->_hoops_HCARR(false);
			if (_hoops_PRCSS == _hoops_HPIRI)
				break;
		}
	}
}



class _hoops_HRCSS : public _hoops_GCARR {
	public:
		_hoops_HRCSS (_hoops_GGAGR * _hoops_GHRI)
			: _hoops_GHRI(_hoops_GHRI) {
			_hoops_GHRI->_hoops_GRPIR->_hoops_PCARR(this);
		};

		virtual ~_hoops_HRCSS() {;}

		virtual _hoops_ICARR Type() {return _hoops_IRCSS;}

		virtual void _hoops_HCARR(bool _hoops_SCARR) {
			if (!_hoops_SCARR) {
				if (!BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_SGPIR)) {
					_hoops_AIGPR * _hoops_RIGC;
					_hoops_IIRIR(_hoops_RIGC);

					if (_hoops_GHRI->owner != null) {
						HI_Clean_Segment_Display_Lists (_hoops_GHRI->owner, true);
						HI_Delete_Renditions (_hoops_RIGC, _hoops_GHRI->owner, null, (Display_Context alter *)_hoops_GHRI->_hoops_PPRPR);
					}

                    _hoops_GHRI->_hoops_CGPIR |= _hoops_CRGSC;

					if (BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA))
						_hoops_HISAA (_hoops_RIGC, _hoops_GHRI, _hoops_PAGSC, null);

					_hoops_HISAA (_hoops_RIGC, _hoops_GHRI, _hoops_IAGSC, null);
				}
			}

			delete this;
		}

	private:
		_hoops_GGAGR *				_hoops_GHRI;
};

GLOBAL_FUNCTION void HI_Queue_Actor_Shutdown(
	_hoops_GGAGR const *	_hoops_GHRI,
	bool			_hoops_GSSIH) {

	if (!_hoops_GHRI->_hoops_GRPIR)
		((_hoops_GGAGR alter *)_hoops_GHRI)->_hoops_GRPIR = NEW(_hoops_SRIAP)(0);

	_hoops_HRCSS const * _hoops_PRCSS = NEW(_hoops_HRCSS)((_hoops_GGAGR alter *)_hoops_GHRI);

	if (_hoops_GSSIH) {
		_hoops_GCARR *		_hoops_HPIRI = null;

		while ((_hoops_HPIRI = _hoops_GHRI->_hoops_GRPIR->_hoops_IAIRI()) != null) {
			_hoops_HPIRI->_hoops_HCARR(false);
			if (_hoops_PRCSS == _hoops_HPIRI)
				break;
		}
	}
}



class _hoops_CRCSS : public _hoops_GCARR {
	public:
		_hoops_CRCSS (_hoops_GGAGR *_hoops_GHRI, Polyhedron alter *_hoops_IPRI)
			: _hoops_GHRI(_hoops_GHRI),  _hoops_IPRI(_hoops_IPRI)  {
			_hoops_GHRI->_hoops_GRPIR->_hoops_PCARR(this, -1);
		};

		virtual ~_hoops_CRCSS() {;}

		virtual _hoops_ICARR Type() {return _hoops_SRCSS;}

		virtual void _hoops_HCARR (bool _hoops_SCARR) {
			_hoops_AIGPR * _hoops_RIGC;
			_hoops_HCRGI(_hoops_RIGC);

			UNREFERENCED (_hoops_SCARR);

			HI_Flush_Derived_Normals (_hoops_RIGC, _hoops_IPRI);

			delete this;
		}

	private:
		_hoops_GGAGR *				_hoops_GHRI;
		Polyhedron alter *	_hoops_IPRI;
};


GLOBAL_FUNCTION void HI_Queue_Flush_Derived_Normals (
	_hoops_GGAGR const *		_hoops_GHRI,
	Polyhedron alter *	_hoops_IPRI)
{
	if (!_hoops_GHRI->_hoops_GRPIR)
		((_hoops_GGAGR alter *)_hoops_GHRI)->_hoops_GRPIR = NEW(_hoops_SRIAP)(0);

	NEW(_hoops_CRCSS)((_hoops_GGAGR alter *)_hoops_GHRI, _hoops_IPRI);
}


GLOBAL_FUNCTION void HI_Check_Actor_Queue(
	_hoops_GGAGR const *	_hoops_GHRI) {

	if (_hoops_GHRI->_hoops_GRPIR) {
		_hoops_GCARR *		_hoops_HPIRI = null;

		while ((_hoops_HPIRI = _hoops_GHRI->_hoops_GRPIR->_hoops_IAIRI()) != null) {
			_hoops_HPIRI->_hoops_HCARR(false);
		}
	}
}


GLOBAL_FUNCTION bool HD_Standard_Driver (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_GGAGR alter *				_hoops_GHRI,
	int							request,
	void *						request_info)
{
	bool						_hoops_IA = true;

	_hoops_RSIIR(_hoops_RIGC);

	if (_hoops_CIAGP (&_hoops_GHRI->_hoops_GAIAP) == 1) {
		HI_Check_Actor_Queue(_hoops_GHRI);
	}

	if (BIT(_hoops_GHRI->_hoops_CGPIR, _hoops_SGPIR)) {
		_hoops_IA = false;
	}
	else if (!BIT(_hoops_GHRI->_hoops_CGPIR, _hoops_SISHA) &&
		BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP)) {

		Display_Context alter * dc = (Display_Context alter *)_hoops_GHRI->_hoops_PPRPR;

		if (dc != null &&
			dc->_hoops_GRAGH == THREAD_ID()) {

			ASSERT(dc->_hoops_RIGC != null);
			_hoops_RSIIR(dc->_hoops_RIGC);

			_hoops_RIISS (dc->_hoops_RIGC, &_hoops_IA, _hoops_GHRI, request, request_info);
		}
		else {
			if (!_hoops_GHRI->_hoops_ACARR) {
				_hoops_CAAI (HOOPS_WORLD->_hoops_APHGI);
				if (!_hoops_GHRI->_hoops_ACARR)
					_hoops_GHRI->_hoops_ACARR = NEW(_hoops_SRIAP)(1, true);
				_hoops_APAI (HOOPS_WORLD->_hoops_APHGI);
			}

			NEW(_hoops_IGCSS)(_hoops_RIGC, &_hoops_IA, _hoops_GHRI, request, request_info);

			HM_WAIT_SEMAPHORE (_hoops_RIGC->semaphore);
		}
	}
	else {
		_hoops_RIISS (_hoops_RIGC, &_hoops_IA, _hoops_GHRI, request, request_info);
	}

	if (_hoops_SPRIR (&_hoops_GHRI->_hoops_GAIAP) == 0) {
#ifdef HOOPS_DEBUG_BUILD
		Display_Context alter * dc = (Display_Context alter *)_hoops_GHRI->_hoops_PPRPR;
		ASSERT((!dc || dc->_hoops_RIGC == null));
#endif
		HI_Check_Actor_Queue(_hoops_GHRI);
	}

	return _hoops_IA;
}




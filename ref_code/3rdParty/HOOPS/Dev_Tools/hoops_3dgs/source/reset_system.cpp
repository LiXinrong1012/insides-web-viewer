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
 * $Id: obf_tmp.txt 1.196 2010-12-06 22:05:39 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "please.h"
#include "searchh.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hd_proto.h"
#include "hpserror.h"
#include "task_queue.h"
#include "adt.h"

#ifndef _hoops_HPAIH
HC_INTERFACE void HC_CDECL HI_DCleanup();
#endif


HC_INTERFACE void HC_CDECL HC_Reset_System (void)
{
	_hoops_IGHGP alter *		_hoops_SSGGA = HOOPS_WORLD;
	int					_hoops_RASRS = 0;

	if (_hoops_SSGGA == null)
		return;

	HI_Set_Name("Reset_System");

	CODE_GENERATION (
		HI_Dump_Code ("HC_Reset_System ();\n");
	);

	if (HOOPS_WORLD->_hoops_GCHGI != null)
		HI_Free_User_Options_Compressor();

	_hoops_RASRS = _hoops_SSGGA->system_flags & (_hoops_IGHGA | _hoops_CSCPP | Sysop_RAW_MEMORY);

#ifndef DISABLE_CODE_GENERATION
	if (BIT (_hoops_RASRS, _hoops_IGHGA)) {
		if (HOOPS_WORLD->_hoops_AGHGA) {
			HI_Chain_Code_Files ();
			HI_Finish_Code_Generation ();
		}
	}
#endif

	_hoops_RPPPR();

	_hoops_SSGGA->_hoops_PPRIR = true;

	if (HOOPS_WORLD->_hoops_HIPSA != null) {
		delete HOOPS_WORLD->_hoops_HIPSA;
		HOOPS_WORLD->_hoops_HIPSA = null;
	}

	typedef char	_hoops_CSSHA;

	if (HOOPS_WORLD->_hoops_CIHGI)
		_hoops_HPRH(HOOPS_WORLD->_hoops_CIHGI);

#ifndef _hoops_HPAIH
	HI_DCleanup();
#endif
	
	if (_hoops_SSGGA->_hoops_CISHA != null) {
		_hoops_GGAGR *					_hoops_GHRI = _hoops_SSGGA->_hoops_CISHA;

		do	{
			HI_Delete_Renditions (HOOPS_WORLD->_hoops_PGSCA, _hoops_GHRI->owner);

			if (!BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_SGPIR) &&
				_hoops_GHRI->_hoops_PPRPR != null)
				HI_Queue_Actor_Shutdown(_hoops_GHRI, true);
			else
				ASSERT(_hoops_GHRI->_hoops_PPRPR == null);

			if (_hoops_GHRI->_hoops_GRPIR) {
				delete _hoops_GHRI->_hoops_GRPIR;
				_hoops_GHRI->_hoops_GRPIR = null;
			}

			if (_hoops_GHRI->_hoops_ACARR) {
				delete _hoops_GHRI->_hoops_ACARR;
				_hoops_GHRI->_hoops_ACARR = null;
			}
		} while ((_hoops_GHRI = _hoops_GHRI->_hoops_CISHA) != null);
	}


	HI_Flush_Driver_Config ("*", "*", "*");

	if (HOOPS_WORLD->_hoops_RAPHP != null)
		delete HOOPS_WORLD->_hoops_RAPHP;

	if (_hoops_SSGGA->_hoops_SIHGH > 0)
		HI_Disable_Timer_Interrupts ();


	/* _hoops_RH _hoops_SGRRI _hoops_GIRPR _hoops_SSCP _hoops_RGCI _hoops_HAII _hoops_PPGS _hoops_GHCS (_hoops_HAR _hoops_RHIR _hoops_AGAH _hoops_GSSR
	 * _hoops_GHCS _hoops_CRAA, _hoops_HIS _hoops_SCH _hoops_IRHS _hoops_IS _hoops_SHH _hoops_HGGPR _hoops_HPP _hoops_AACAR _hoops_GHPSA _hoops_IIGR _hoops_AASRS _hoops_PAR _hoops_HAR. */
#ifdef FREETYPE
	HD_Free_Freetype_Globals (_hoops_SSGGA);
#endif

	HI_Free_Stencil_Cache();

	// _hoops_AIHPC _hoops_IPGRR, _hoops_GHIR, _hoops_GHARR _hoops_SASI _hoops_PPR _hoops_PPGS _hoops_GGR _hoops_SGS _hoops_AGR
	delete HOOPS_WORLD->_hoops_ACARR;
	HOOPS_WORLD->_hoops_ACARR = null;
	HI_Free_Time ();
	HI_Stop_System_Specific ();

	{
		_hoops_AIGPR *	_hoops_RIGC = _hoops_SSGGA->_hoops_PGSCA;
		_hoops_AIGPR *	_hoops_PASRS = null;

		LOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);
		do {

			if (BIT (HOOPS_WORLD->system_flags, Sysop_RAW_MEMORY)) {


				{
					_hoops_SIRIR *	victim;

					while ((victim = _hoops_RIGC->open_list) != null) {
						_hoops_CIGPR (_hoops_RIGC,victim);
						_hoops_HPRH (victim);
					}
				}


				if (_hoops_RIGC->_hoops_PISHA != null)
					_hoops_HPRH (_hoops_RIGC->_hoops_PISHA);
				if (_hoops_RIGC->_hoops_PCRPH != null)
					_hoops_HPRH (_hoops_RIGC->_hoops_PCRPH);

				{
					_hoops_HISHA *	victim;

					while ((victim = _hoops_RIGC->_hoops_PAARH) != null) {
						_hoops_CIGPR (_hoops_RIGC,victim);
						_hoops_HPRH (victim);
					}
				}

				if (_hoops_RIGC->_hoops_SIPPH)
					FREE(_hoops_RIGC->_hoops_SIPPH, _hoops_AISIA);

				if (_hoops_RIGC->_hoops_PRCIA != null) {
					HI_Delete_Shell_Selection_Cache(_hoops_RIGC->_hoops_PRCIA);
					_hoops_RIGC->_hoops_PRCIA = null;
				}
				if (_hoops_RIGC->_hoops_RAHPA != null) {
					HI_Delete_Intersect_Polyline_Cache(_hoops_RIGC->_hoops_RAHPA);
					_hoops_RIGC->_hoops_RAHPA = null;
				}
				if (_hoops_RIGC->_hoops_HSIHA != null) {
					HI_Delete_Point_Inside_Shell_Cache(_hoops_RIGC->_hoops_HSIHA);
					_hoops_RIGC->_hoops_HSIHA = null;
				}

#ifndef DISABLE_SEARCH
				{
					_hoops_SSPPR *		victim;
					_hoops_AGHPR *		list;

					while ((victim = _hoops_RIGC->_hoops_AHPGI) != null) {
						_hoops_RIGC->_hoops_AHPGI = victim->prev;

						HI_Free_Search_List (_hoops_RIGC, victim->list);
						FREE (victim, _hoops_SSPPR);
					}

					while ((victim = _hoops_RIGC->_hoops_GHHCA) != null) {
						_hoops_RIGC->_hoops_GHHCA = victim->prev;

						HI_Free_Search_List (_hoops_RIGC, victim->list);
						FREE (victim, _hoops_SSPPR);
					}

					while ((victim = _hoops_RIGC->_hoops_RGHPR) != null) {
						_hoops_RIGC->_hoops_RGHPR = victim->prev;

						HI_Free_Search_List (_hoops_RIGC, victim->list);
						FREE (victim, _hoops_SSPPR);
					}

#ifndef DISABLE_CALLBACKS
					while ((victim = _hoops_RIGC->_hoops_AAPCR) != null) {
						_hoops_RIGC->_hoops_AAPCR = victim->prev;

						HI_Free_Search_List (_hoops_RIGC, victim->list);
						FREE (victim, _hoops_SSPPR);
					}
#endif

					while ((victim = _hoops_RIGC->_hoops_PSHPP) != null) {
						_hoops_RIGC->_hoops_PSHPP = victim->prev;

						HI_Free_Search_List (_hoops_RIGC, victim->list);
						FREE (victim, _hoops_SSPPR);
					}

					while ((victim = _hoops_RIGC->_hoops_PHPGI) != null) {
						_hoops_RIGC->_hoops_PHPGI = victim->prev;

						HI_Free_Search_List (_hoops_RIGC, victim->list);
						FREE (victim, _hoops_SSPPR);
					}

#ifndef DISABLE_TEXTURING
					while ((victim = _hoops_RIGC->_hoops_IHPGI) != null) {
						_hoops_RIGC->_hoops_IHPGI = victim->prev;

						HI_Free_Search_List (_hoops_RIGC, victim->list);
						FREE (victim, _hoops_SSPPR);
					}
					while ((victim = _hoops_RIGC->_hoops_CHPGI) != null) {
						_hoops_RIGC->_hoops_CHPGI = victim->prev;

						HI_Free_Search_List (_hoops_RIGC, victim->list);
						FREE (victim, _hoops_SSPPR);
					}
#endif

					while ((victim = _hoops_RIGC->_hoops_HHPGI) != null) {
						_hoops_RIGC->_hoops_HHPGI = victim->prev;

						HI_Free_Search_List (_hoops_RIGC, victim->list);

						if (victim->_hoops_HASRS != null)
							_hoops_HPRH (victim->_hoops_HASRS);
						if (victim->_hoops_IASRS > 0)
							FREE_ARRAY (victim->_hoops_HGPIR, victim->_hoops_IASRS, _hoops_HCRPR);
						FREE (victim, _hoops_SSPPR);
					}

					while ((victim = _hoops_RIGC->_hoops_RHSAH) != null) {
						_hoops_RIGC->_hoops_RHSAH = victim->prev;

						HI_Free_Search_List (_hoops_RIGC, victim->list);
						FREE (victim, _hoops_SSPPR);
					}

					while ((victim = _hoops_RIGC->_hoops_HCHPH) != null) {
						_hoops_RIGC->_hoops_HCHPH = victim->prev;

						HI_Free_Search_List (_hoops_RIGC, victim->list);
						FREE (victim, _hoops_SSPPR);
					}


#ifndef _hoops_HRGIH
					// _hoops_RHRIR: _hoops_ASAI _hoops_APSAR _hoops_CCA _hoops_IRAGP
					while ((victim = _hoops_RIGC->glyph_search_stack) != null) {
						_hoops_RIGC->glyph_search_stack = victim->prev;

						while ((list = victim->list) != null) {
							victim->list = list->next;

							_hoops_GASC * item = (_hoops_GASC *) list->item;
							*item = null;
							FREE (item, _hoops_GASC);

							FREE (list, _hoops_AGHPR);
						}

						FREE (victim, _hoops_SSPPR);
					}
#endif

#ifndef _hoops_GASSI
					// _hoops_RHRIR: _hoops_ASAI _hoops_APSAR _hoops_CCA _hoops_IRAGP
					while ((victim = _hoops_RIGC->_hoops_SHPGI) != null) {
						_hoops_RIGC->_hoops_SHPGI = victim->prev;

						while ((list = victim->list) != null) {
							victim->list = list->next;

							_hoops_GPAIR * item = (_hoops_GPAIR *) list->item;
							*item = null; // _hoops_RGR _hoops_HRGR _hoops_RH _hoops_SSPII
							FREE (item, _hoops_GPAIR);

							FREE (list, _hoops_AGHPR);
						}

						FREE (victim, _hoops_SSPPR);
					}
#endif

#ifndef _hoops_IRCPI
					// _hoops_RHRIR: _hoops_ASAI _hoops_APSAR _hoops_CCA _hoops_IRAGP
					while ((victim = _hoops_RIGC->_hoops_GIPGI) != null) {
						_hoops_RIGC->_hoops_GIPGI = victim->prev;

						while ((list = victim->list) != null) {
							victim->list = list->next;

							Line_Style * item = (Line_Style *) list->item;
							*item = null;
							FREE (item, Line_Style);

							FREE (list, _hoops_AGHPR);
						}

						FREE (victim, _hoops_SSPPR);
					}
#endif
				}
			}
#endif

			HM_DESTRUCT_SEMAPHORE (_hoops_RIGC->semaphore);

			_hoops_PASRS = _hoops_RIGC->next;

			/* _hoops_PAGA: _hoops_SRCH _hoops_GSGHR -- _hoops_SSRR _hoops_PPGS/_hoops_ISSSH _hoops_ASSSH _hoops_SRPHP */
			if (_hoops_RIGC != _hoops_SSGGA->_hoops_PGSCA) {
				HI_Destroy_Memory_Pool (_hoops_RIGC->memory_pool);
				_hoops_RIGC->memory_pool = null;
				FREE_MEMORY (_hoops_RIGC, _hoops_AIGPR);
			}

		} while ((_hoops_RIGC = _hoops_PASRS) != null);
		UNLOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);
	}

	if (BIT (HOOPS_WORLD->_hoops_IRARR, _hoops_GRHGI) ||
		BIT (HOOPS_WORLD->system_flags, Sysop_RAW_MEMORY)) {
		/* _hoops_HS _hoops_IS _hoops_CPPPR _hoops_HRGHR _hoops_CASI _hoops_GH _hoops_HCR _hoops_HCCGR... */

		HI_Flush_Seg_Path_Lookup(_hoops_SSGGA->_hoops_PGSCA);

		{	Pending_Special		*victim;

			while ((victim = _hoops_SSGGA->_hoops_SRHGI) != null) {
				_hoops_SSGGA->_hoops_SRHGI = victim->next;
				_hoops_RGAIR (victim->type);
				_hoops_RGAIR (victim->value);
				FREE (victim, Pending_Special);
			}
		}

		{	_hoops_ISSAP		*victim;

			while ((victim = _hoops_SSGGA->_hoops_GAHGI) != null) {
				_hoops_SSGGA->_hoops_GAHGI = victim->next;
				if (victim->segment != null)
					_hoops_HPRH (victim->segment);
				if (victim->geometry != null)
					_hoops_HPRH (victim->geometry);
				FREE (victim, _hoops_ISSAP);
			}
		}


		{
			int i;
			for (i=0; i<_hoops_SSGGA->_hoops_CARHP; i++) {
				_hoops_CPPGI	*_hoops_ISGHP = &_hoops_SSGGA->_hoops_SARHP[i];

				HI_Flush_Color_Material_Lookup (&_hoops_ISGHP->_hoops_HIHPP);


				{
					_hoops_GPPGI *		keys = &_hoops_ISGHP->global_keys;
					_hoops_PSSAP *		victim;
					_hoops_PSSAP **		list;
					_hoops_PSSAP **		_hoops_CASRS;

					if ((list = keys->table) != null) {
						_hoops_CASRS = list + keys->size;
						do {
							while ((victim = *list) != null) {
								*list = victim->next;
								FREE (victim, _hoops_PSSAP);
							}
						} while (++list != _hoops_CASRS);
						FREE_ARRAY (keys->table, keys->size, _hoops_PSSAP *);
					}
				}

				{
					_hoops_SCHIR *		victim;

					while ((victim = _hoops_ISGHP->_hoops_AIHPP) != null) {
						_hoops_CIGPR (HOOPS_WORLD->_hoops_PGSCA,victim);
						_hoops_HPRH (victim);
					}
				}


				/* _hoops_RGR _hoops_GASR _hoops_CGH _hoops_SHH _hoops_CASI _hoops_RAS _hoops_SASRS _hoops_HAPR _hoops_ARRS */
				if (_hoops_ISGHP->_hoops_SCHPP != null)
					FREE_ARRAY (_hoops_ISGHP->_hoops_SCHPP,
						_hoops_GSHPP, _hoops_RSHIR *);

				{
					_hoops_SRPPR *			victim;
					_hoops_SRPPR **		list;
					_hoops_SRPPR **		_hoops_CASRS;

					if ((list = _hoops_ISGHP->_hoops_ASPPR) != null) {
						_hoops_CASRS = list + _hoops_PSPPR;
						do {
							while ((victim = *list) != null) {
								_hoops_CIGPR (HOOPS_WORLD->_hoops_PGSCA,victim);
								_hoops_HPRH (victim);
							}
						} while (++list != _hoops_CASRS);
						FREE_ARRAY (_hoops_ISGHP->_hoops_ASPPR,
							_hoops_PSPPR, _hoops_SRPPR *);
					}
				}

#ifndef DISABLE_CALLBACKS
				{
					_hoops_HCHIR *			victim;
					_hoops_HCHIR **		list;
					_hoops_HCHIR **		_hoops_CASRS;

					if ((list = _hoops_ISGHP->_hoops_RAPCR) != null) {
						_hoops_CASRS = list + _hoops_PAPCR;
						do {
							while ((victim = *list) != null) {
								_hoops_CIGPR (HOOPS_WORLD->_hoops_PGSCA,victim);
								_hoops_HPRH (victim);
							}
						} while (++list != _hoops_CASRS);
						FREE_ARRAY (_hoops_ISGHP->_hoops_RAPCR,
							_hoops_PAPCR, _hoops_HCHIR *);
					}
				}
#endif


				{
					_hoops_PGIIR *			victim;
					_hoops_PGIIR **			list;
					_hoops_PGIIR **			_hoops_CASRS;

					if ((list = _hoops_ISGHP->_hoops_SPPGI) != null) {
						_hoops_CASRS = list + _hoops_GPRGI;
						do {
							while ((victim = *list) != null) {
								_hoops_CIGPR (HOOPS_WORLD->_hoops_PGSCA,victim);
								_hoops_HPRH (victim);
							}
						} while (++list != _hoops_CASRS);
						FREE_ARRAY (_hoops_ISGHP->_hoops_SPPGI,
							_hoops_GPRGI, _hoops_PGIIR *);
					}
				}

				_hoops_RGAIR(_hoops_ISGHP->_hoops_ISHAP);
			}
		}

		FREE_ARRAY(HOOPS_WORLD->_hoops_SARHP, HOOPS_WORLD->_hoops_CARHP, _hoops_CPPGI);


		{
			_hoops_GPPGI *			keys = &_hoops_SSGGA->_hoops_CCPGI;
			_hoops_PSSAP *			victim;
			_hoops_PSSAP **			list;
			_hoops_PSSAP **			_hoops_CASRS;

			if ((list = keys->table) != null) {
				_hoops_CASRS = list + keys->size;
				do {
					while ((victim = *list) != null) {
						*list = victim->next;
						FREE (victim, _hoops_PSSAP);
					}
				} while (++list != _hoops_CASRS);
				FREE_ARRAY (keys->table, keys->size, _hoops_PSSAP *);
			}
		}


		if (_hoops_SSGGA->_hoops_HGGHP != null)
			_hoops_HPRH (_hoops_SSGGA->_hoops_HGGHP);


		{	_hoops_HRIIR *			victim;

			while ((victim = _hoops_SSGGA->_hoops_CGAPH) != null) {
				_hoops_CIGPR (HOOPS_WORLD->_hoops_PGSCA,victim);
				_hoops_HPRH (victim);
			}
		}

		{	int						_hoops_GPSRS = 0;

			do {
				_hoops_PIIIR *		victim;
				_hoops_PIIIR **		list;
				_hoops_PIIIR **		_hoops_CASRS;
				int					_hoops_RPSRS;

				_hoops_RPSRS = _hoops_SSGGA->_hoops_GSPGI[_hoops_GPSRS].size;
				if ((list = _hoops_SSGGA->_hoops_GSPGI[_hoops_GPSRS].table) != null) {
					_hoops_CASRS = list + _hoops_RPSRS;
					do {
						while ((victim = *list) != null) {
							_hoops_CIGPR (HOOPS_WORLD->_hoops_PGSCA,victim);
							_hoops_HPRH (victim);
						}
					} while (++list != _hoops_CASRS);
					FREE_ARRAY (_hoops_SSGGA->_hoops_GSPGI[_hoops_GPSRS].table,
								_hoops_RPSRS,
								_hoops_PIIIR *);
				}
			} while (++_hoops_GPSRS != _hoops_CIRGI);
		}



		if (_hoops_SSGGA->root != null) {
			HI_Disentangle (HOOPS_WORLD->_hoops_PGSCA, (_hoops_HPAH alter *)_hoops_SSGGA->root);
			_hoops_HPRH (_hoops_SSGGA->root);
		}

		if (HOOPS_WORLD->_hoops_GCHCA.table != null)
			FREE_ARRAY (HOOPS_WORLD->_hoops_GCHCA.table, HOOPS_WORLD->_hoops_GCHCA.allocated, _hoops_PPPGI);



		if (HOOPS_WORLD->_hoops_PCIIR > 0) {
			_hoops_HPRH (HOOPS_WORLD->_hoops_PCIIR[0]);	/* _hoops_GRH _hoops_GGAGA _hoops_GGR _hoops_RARP 0 */
			FREE_ARRAY (HOOPS_WORLD->_hoops_PCIIR, HOOPS_WORLD->_hoops_AGCAA, _hoops_PIIIR *);
			HOOPS_WORLD->_hoops_PCIIR = 0;
		}


		_hoops_RGAIR (_hoops_SSGGA->_hoops_GRGHP);

#define _hoops_SPRSP		65		/* _hoops_PSSP _hoops_RHPP._hoops_GGHR */

		if (_hoops_SSGGA->_hoops_IPSHH != null)
			FREE_ARRAY (_hoops_SSGGA->_hoops_IPSHH, 16L * _hoops_SPRSP, unsigned short);
		if (_hoops_SSGGA->_hoops_SCSHH != null)
			FREE_ARRAY (_hoops_SSGGA->_hoops_SCSHH, 8L * _hoops_SPRSP, unsigned char);
		if (_hoops_SSGGA->_hoops_SCPGI != null)
			FREE_ARRAY (_hoops_SSGGA->_hoops_SCPGI, 4L * _hoops_SPRSP, unsigned char);


		if (_hoops_SSGGA->_hoops_RAHGI != null) {
			HI_Free_Kanji_Data ();
		}

		{
			_hoops_AAPIR	*victim;

			while ((victim = _hoops_SSGGA->_hoops_AAGHP) != null) {
				_hoops_SSGGA->_hoops_AAGHP = victim->next;
				_hoops_RGAIR (victim->name);
				FREE (victim, _hoops_AAPIR);
			}

			while ((victim = _hoops_SSGGA->_hoops_PAGHP) != null) {
				_hoops_SSGGA->_hoops_PAGHP = victim->next;
				_hoops_RGAIR (victim->name);
				FREE (victim, _hoops_AAPIR);
			}

			while ((victim = _hoops_SSGGA->_hoops_HAGHP) != null) {
				_hoops_SSGGA->_hoops_HAGHP = victim->next;
				_hoops_RGAIR (victim->name);
				FREE (victim, _hoops_AAPIR);
			}

			if (_hoops_SSGGA->_hoops_GRHGA.length != 0)
				_hoops_RGAIR (_hoops_SSGGA->_hoops_GRHGA);

			if (_hoops_SSGGA->_hoops_PARPR.length != 0)
				_hoops_RGAIR (_hoops_SSGGA->_hoops_PARPR);

			if (_hoops_SSGGA->_hoops_HAHGI.length != 0)
				_hoops_RGAIR (_hoops_SSGGA->_hoops_HAHGI);
		}


		/*
		 * _hoops_AGGGR _hoops_IASAH _hoops_CHR _hoops_GACC _hoops_HGGPR _hoops_GGR _hoops_APSRS
		 */
		{
			_hoops_SSHIR			*victim;

			while ((victim = _hoops_SSGGA->_hoops_AIHPH) != null) {
				_hoops_CIGPR (HOOPS_WORLD->_hoops_PGSCA,victim);
				_hoops_HPRH (victim);
			}
		}

		{
			_hoops_RGIIR		*victim;

			while ((victim = _hoops_SSGGA->_hoops_RASAH) != null) {
				_hoops_CIGPR (HOOPS_WORLD->_hoops_PGSCA,victim);
				_hoops_HPRH (victim);
			}
		}

		{
			_hoops_CPSPP		*victim;
			int						i;

			for (i=0; i<4; i++) {
				while ((victim = _hoops_SSGGA->_hoops_PSSPP[i]) != null) {
					_hoops_SSGGA->_hoops_PSSPP[i] = victim->next;
					FREE (victim, _hoops_CPSPP);
				}
			}
		}

		if (_hoops_SSGGA->_hoops_GAIAA != null) {
			FREE_ARRAY(_hoops_SSGGA->_hoops_GAIAA, 3*72, float);
			_hoops_SSGGA->_hoops_GAIAA = null;
		}

		while (_hoops_SSGGA->_hoops_IIHGI != null) {
			_hoops_IAPGI *	table = _hoops_SSGGA->_hoops_IIHGI;
			int								i;

			_hoops_SSGGA->_hoops_IIHGI = table->next;
			for (i=0; i<_hoops_RAPGI; i++) {
				while (table->forward[i] != null) {
					_hoops_AAPGI *		_hoops_SPRAR = table->forward[i];

					table->forward[i] = _hoops_SPRAR->forward;
					FREE (_hoops_SPRAR, _hoops_AAPGI);
				}
			}

			FREE (table, _hoops_IAPGI);
		}

		ASSERT(HOOPS_WORLD->_hoops_PPAPA->Count() == 0);
	} /* _hoops_PPSRS */

	_hoops_IRRPR();

	if (HOOPS_WORLD->_hoops_RCPGI) {
		delete HOOPS_WORLD->_hoops_RCPGI;
		HOOPS_WORLD->_hoops_RCPGI = null;
	}

	HOOPS_WORLD->_hoops_PPAPA->DeleteItems();
	delete HOOPS_WORLD->_hoops_PPAPA;

	HI_Destroy_Memory_Pool (HOOPS_WORLD->_hoops_PGSCA->memory_pool);
	HOOPS_WORLD->_hoops_PGSCA->memory_pool = null;

	HI_Destroy_Memory_Pool (HOOPS_WORLD->memory_pool);
	HOOPS_WORLD->memory_pool = null;

	HI_System_Memory_Purge();

	DESTROY_MUTEX (HOOPS_WORLD->_hoops_RPHGI);
	DESTROY_MUTEX (HOOPS_WORLD->_hoops_PIPSA);
	DESTROY_MUTEX (HOOPS_WORLD->_hoops_GAPHP);
	DESTROY_MUTEX (HOOPS_WORLD->_hoops_IIAGP);
	DESTROY_MUTEX (HOOPS_WORLD->_hoops_RIPSA);
	DESTROY_MUTEX (HOOPS_WORLD->_hoops_RAPSA);
	DESTROY_MUTEX (HOOPS_WORLD->_hoops_HPSAP);
	DESTROY_MUTEX (HOOPS_WORLD->_hoops_APHGI);
	DESTROY_MUTEX (HOOPS_WORLD->_hoops_PPHGI);
	DESTROY_MUTEX (HOOPS_WORLD->_hoops_HPHGI);
	DESTROY_MUTEX (HOOPS_WORLD->_hoops_SAAI);
	DESTROY_MUTEX (HOOPS_WORLD->_hoops_RSASA);
	DESTROY_MUTEX (HOOPS_WORLD->_hoops_IGAPH);
	DESTROY_MUTEX (HOOPS_WORLD->_hoops_ICRGI);
	DESTROY_LOCK (HOOPS_WORLD->_hoops_SSRGI);

	FREE_MEMORY ((void*)HOOPS_WORLD->time_stamp, _hoops_GSPGR);

	FREE_MEMORY (HOOPS_WORLD->_hoops_PGSCA, _hoops_AIGPR);

	if (_hoops_RASRS != 0 || HOOPS_WORLD->_hoops_SCSPP) {
		ZERO_STRUCT(HOOPS_ETERNAL_WORLD, _hoops_GSSSH);

		HOOPS_ETERNAL_WORLD->system_flags = _hoops_RASRS;
		HOOPS_ETERNAL_WORLD->_hoops_RRHGA = HOOPS_WORLD->_hoops_RRHGA;

		if (HOOPS_WORLD->_hoops_SCSPP) {
			HOOPS_ETERNAL_WORLD->_hoops_SCSPP = true;
			HOOPS_ETERNAL_WORLD->malloc = HOOPS_WORLD->malloc;
			HOOPS_ETERNAL_WORLD->free = HOOPS_WORLD->free;
		}
	}

	FREE_MEMORY (HOOPS_WORLD, _hoops_IGHGP);
	HOOPS_WORLD = null;
}

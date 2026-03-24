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
 * $Id: obf_tmp.txt 1.131 2011-01-13 02:14:49 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hi_proto.h"
#include "hc_proto.h"
#include "hd_proto.h"
#include "hpserror.h"
#include "please.h"
#include "driver.h"
#include "phedron.h"
#include "adt.h"

enum {
	_hoops_SRCCA,
	_hoops_GACCA,
	_hoops_RACCA,
	_hoops_AACCA,
	_hoops_PACCA,
	_hoops_HACCA,
	_hoops_IACCA,

	_hoops_CACCA,
	_hoops_SACCA,
	_hoops_GPCCA,
	_hoops_RPCCA,
	_hoops_APCCA,

	_hoops_PPCCA,
	_hoops_HPCCA,
	_hoops_IPCCA,
	_hoops_CPCCA,
	_hoops_SPCCA,
	_hoops_GHCCA,
	_hoops_RHCCA,
	_hoops_AHCCA,
	_hoops_PHCCA,
	_hoops_HHCCA,

	_hoops_IHCCA,
	_hoops_CHCCA,
	_hoops_SHCCA,

	_hoops_GICCA,
	_hoops_RICCA,
	_hoops_AICCA,

	_hoops_PICCA,
	_hoops_HICCA,

	_hoops_IICCA,

	_hoops_CICCA
};

local const _hoops_IGRCR _hoops_SICCA[] = {
	{_hoops_IACCA,			_hoops_GRRCR ("refresh"),								_hoops_RRRCR, 0, false},
	{_hoops_GACCA, 		_hoops_GRRCR ("redraw everything"),						_hoops_RRRCR, 0, false},
	{_hoops_APCCA, 	_hoops_GRRCR ("redraw fix text bounding"),				_hoops_RRRCR, 0, false},
	{_hoops_RACCA,			_hoops_GRRCR ("redraw geometry"),						_hoops_RRRCR, 0, false},
	{_hoops_AACCA,			_hoops_GRRCR ("redraw partial erase"),					_hoops_RRRCR, 0, false},
	{_hoops_PACCA,			_hoops_GRRCR ("redo radiosity"),						_hoops_RRRCR, 0, false},
	{_hoops_HACCA,			_hoops_GRRCR ("set created"),							_hoops_RRRCR, 0, false},
	{_hoops_SRCCA,			_hoops_GRRCR ("unset redraw"),							_hoops_RRRCR, 0, false},

	{_hoops_CACCA,			_hoops_GRRCR ("mark interesting"),						_hoops_RRRCR, 0, false},
	{_hoops_SACCA,				_hoops_GRRCR ("clear interesting"),						_hoops_RRRCR, 0, false},

	{_hoops_GPCCA, _hoops_GRRCR ("bounding retention"),					_hoops_RRRCR, 0, true},
	{_hoops_GPCCA, _hoops_GRRCR ("bounding volume retention"), 			_hoops_RRRCR, 0, true},
	{_hoops_RPCCA,	_hoops_GRRCR ("compute bounding volume"),				_hoops_RRRCR, 0, false},
	{_hoops_RPCCA,	_hoops_GRRCR ("compute bounding volumes"),				_hoops_RRRCR, 0, false},

	{_hoops_SPCCA,			_hoops_GRRCR ("set derived geometry regeneration"),		_hoops_RRRCR, 0, false},
	{_hoops_GHCCA,			_hoops_GRRCR ("unset derived geometry regeneration"),	_hoops_RRRCR, 0, false},
	{_hoops_IPCCA,		_hoops_GRRCR ("set cut geometry regeneration"),			_hoops_RRRCR, 0, false},
	{_hoops_CPCCA,	_hoops_GRRCR ("unset cut geometry regeneration"),		_hoops_RRRCR, 0, false},
	{_hoops_PPCCA,				_hoops_GRRCR ("set shadow regeneration"),				_hoops_RRRCR, 0, false},
	{_hoops_HPCCA,			_hoops_GRRCR ("unset shadow regeneration"),				_hoops_RRRCR, 0, false},
	{_hoops_RHCCA,		_hoops_GRRCR ("set hidden line regeneration"),			_hoops_RRRCR, 0, false},
	{_hoops_AHCCA,	_hoops_GRRCR ("unset hidden line regeneration"),		_hoops_RRRCR, 0, false},
	{_hoops_PHCCA,				_hoops_GRRCR ("set static model regeneration"),			_hoops_RRRCR, 0, false},
	{_hoops_HHCCA,			_hoops_GRRCR ("unset sraric model regeneration"),		_hoops_RRRCR, 0, false},

	{_hoops_IHCCA,		_hoops_GRRCR ("reset device"),							_hoops_RRRCR, 0, false},

	{_hoops_CHCCA,		_hoops_GRRCR ("clear stats"),							_hoops_RRRCR, 0, false},
	{_hoops_CHCCA,		_hoops_GRRCR ("clear statistics"),						_hoops_RRRCR, 0, false},

	{_hoops_SHCCA,		_hoops_GRRCR ("reset root attributes"),					_hoops_RRRCR, 0, false},

	{_hoops_CICCA,	_hoops_GRRCR ("compress user options"),				_hoops_RRRCR, 0, false},

	{_hoops_PICCA,	_hoops_GRRCR ("free boolean cache"),					_hoops_RRRCR, 0, false},

	{_hoops_HICCA,		_hoops_GRRCR ("compile only"),							_hoops_RRRCR, 0, false},

	{_hoops_IICCA,	_hoops_GRRCR ("inspect"),								_hoops_RRRCR, 0, false},

	{_hoops_GICCA,		_hoops_GRRCR ("read lock database"),					_hoops_RRRCR, 0, false},
	{_hoops_RICCA,		_hoops_GRRCR ("write lock database"),					_hoops_RRRCR, 0, false},
	{_hoops_RICCA,		_hoops_GRRCR ("lock database"),							_hoops_RRRCR, 0, false},
	{_hoops_AICCA,			_hoops_GRRCR ("unlock database"),						_hoops_RRRCR, 0, false},
};



local void _hoops_GCCCA (
	_hoops_HPAH *			thing,
	_hoops_RCCCA		set) {

	do {
		thing->_hoops_RRHH |= set;

		if (thing->type == _hoops_IRCP) {
			_hoops_CRCP		*_hoops_SRCP = (_hoops_CRCP *)thing;
			Xref			*_hoops_AHICA;

			if ((_hoops_AHICA = _hoops_SRCP->_hoops_SGRPR()) != null) do {
				if (_hoops_AHICA->type == _hoops_AGRPR) {
					if (!ALLBITS (_hoops_AHICA->owner->_hoops_RRHH, set)) {
						_hoops_GCCCA ((_hoops_HPAH *)_hoops_AHICA->owner, set);
					}
				}
			} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);
		}

		thing = thing->owner;
	} while (thing->type != _hoops_PRAIR && !ALLBITS (thing->_hoops_RRHH, set));
}


local bool _hoops_ACCCA (
	_hoops_PAPPR &						context,
	char const *					list,
	_hoops_PCCCA *	data)
{

	_hoops_HIACR (_hoops_HCCCA, _hoops_SICCA);

	Option_Value *					option_list;
	Option_Value *					option;
	bool							_hoops_ICCCA = false;

	if (!HI_Parse_Options (context, list, _hoops_CIACR (_hoops_HCCCA), &option_list, _hoops_SIACR))
		return _hoops_ICCCA;

	ZERO_STRUCT(data, _hoops_PCCCA);
	data->area.left	  = -1.0f;	data->area.right = 1.0f;
	data->area.bottom = -1.0f;	data->area.top	 = 1.0f;

	if ((option = option_list) != null) do switch (option->type->id) {
		case _hoops_IACCA:	data->_hoops_CCCCA.set |= _hoops_SCCCA;
								_hoops_ICCCA = true;
								break;

		case _hoops_GACCA: data->_hoops_CCCCA.set |= _hoops_GSCCA;
								_hoops_ICCCA = true;
								break;

		case _hoops_APCCA: data->_hoops_CCCCA.set |= _hoops_RSCCA;
								_hoops_ICCCA = true;
								break;

		case _hoops_RACCA:	data->_hoops_CCCCA.set |= _hoops_GGARA;
								_hoops_ICCCA = true;
								break;

		case _hoops_AACCA:	data->_hoops_CCCCA.set |= _hoops_HRCCA;
								_hoops_ICCCA = true;
								break;

		case _hoops_PACCA:	data->_hoops_CCCCA.set |= _hoops_GPSIR;
								_hoops_ICCCA = true;
								break;

		case _hoops_HACCA:	data->_hoops_CCCCA.set |= _hoops_CASIR|
														_hoops_GGARA|
														_hoops_SIGPR;
								_hoops_ICCCA = true;
								break;

		case _hoops_IHCCA:	data->_hoops_ASCCA = true;
									_hoops_ICCCA = true;
									break;

		case _hoops_PPCCA:				data->_hoops_CCCCA.set |= _hoops_HISSR|_hoops_IISSR|
																_hoops_PSCCA|
																_hoops_HSCCA;
										_hoops_ICCCA = true;
										break;

		case _hoops_HPCCA:			data->_hoops_CCCCA.clear |= _hoops_HISSR|_hoops_IISSR|
																  _hoops_PSCCA|
																  _hoops_HSCCA;
										_hoops_ICCCA = true;
										break;

		case _hoops_IPCCA:		data->_hoops_CCCCA.set |= _hoops_ISCCA;
										_hoops_ICCCA = true;
										break;

		case _hoops_CPCCA:	data->_hoops_CCCCA.clear |= _hoops_ISCCA;
										_hoops_ICCCA = true;
										break;

		case _hoops_SPCCA:			data->_hoops_CCCCA.set |= _hoops_CSCCA;
										_hoops_ICCCA = true;
										break;

		case _hoops_GHCCA:			data->_hoops_CCCCA.clear |= _hoops_CSCCA;
										_hoops_ICCCA = true;
										break;

		case _hoops_RHCCA:		data->_hoops_CCCCA.set |= _hoops_RPSIR;
										_hoops_ICCCA = true;
										break;

		case _hoops_AHCCA:	data->_hoops_CCCCA.clear |= _hoops_RPSIR;
										_hoops_ICCCA = true;
										break;

		case _hoops_PHCCA:				data->_hoops_CCCCA.set |= _hoops_SSCCA;
										_hoops_ICCCA = true;
										break;

		case _hoops_HHCCA:			data->_hoops_CCCCA.clear |= _hoops_SSCCA;
										_hoops_ICCCA = true;
										break;


		case _hoops_SRCCA:	data->_hoops_CCCCA.clear = ~_hoops_AHGPR;
								data->_hoops_CCCCA.set = 0;
								_hoops_ICCCA = true;
								break;


		case _hoops_CACCA: {
			data->database.set	 |=	 _hoops_GGCCA;
			data->database.clear &= ~_hoops_GGCCA;
			_hoops_ICCCA = true;
		}	break;

		case _hoops_SACCA: {
			data->database.clear |=	 _hoops_GGCCA;
			data->database.set	 &= ~_hoops_GGCCA;
			_hoops_ICCCA = true;
		}	break;

		case _hoops_GPCCA: {
			if (option->_hoops_GCACR) {
				data->database.clear |=	 _hoops_GGSCA;
				data->database.set	 &= ~_hoops_GGSCA;
			}
			else {
				data->database.set	 |=	 _hoops_GGSCA;
				data->database.clear &= ~_hoops_GGSCA;
			}
			_hoops_ICCCA = true;
		}	break;

		case _hoops_RPCCA:
			data->_hoops_RGSCA = true;
			_hoops_ICCCA = true;
			break;

		case _hoops_CHCCA:
			data->_hoops_AGSCA = true;
			_hoops_ICCCA = true;
			break;

		case _hoops_HICCA:
			data->_hoops_IHGI = true;
			_hoops_ICCCA = true;
			break;

		case _hoops_SHCCA:
			// _hoops_ASIGA _hoops_SIGP
			HI_Set_Default_Attributes(HOOPS_WORLD->_hoops_PGSCA);	// _hoops_PAGA: _hoops_HGAI, _hoops_HRSAR _hoops_ACPH; _hoops_HAR _hoops_RCPGR _hoops_PPR _hoops_CPHR _hoops_RIR-_hoops_CAGH
			break;


		case _hoops_CICCA:
			// _hoops_ASIGA _hoops_SIGP
			HI_Compress_User_Options(HOOPS_WORLD->_hoops_PGSCA);	// _hoops_PAGA: _hoops_HGAI, _hoops_HRSAR _hoops_ACPH; _hoops_HAR _hoops_RCPGR _hoops_PPR _hoops_CPHR _hoops_RIR-_hoops_CAGH
			break;

		case _hoops_PICCA: {
				// _hoops_PAGA: _hoops_HGAI, _hoops_HRSAR _hoops_ACPH; _hoops_HAR _hoops_RCPGR _hoops_PPR _hoops_CPHR _hoops_RIR-_hoops_CAGH
				; // _hoops_ISAP
		}	break;

		case _hoops_IICCA:
			data->_hoops_CCCCA.set |= _hoops_HGSCA;
			_hoops_ICCCA = true;
		break;

		case _hoops_GICCA:
			HI_Read_Lock_Database(); // _hoops_PAGA: _hoops_HGAI, _hoops_HRSAR _hoops_ACPH; _hoops_HAR _hoops_RCPGR _hoops_PPR _hoops_CPHR _hoops_RIR-_hoops_CAGH
			context._hoops_IGSCA();
			break;

		case _hoops_RICCA:
			HI_Write_Lock_Database(); // _hoops_PAGA: _hoops_HGAI, _hoops_HRSAR _hoops_ACPH; _hoops_HAR _hoops_RCPGR _hoops_PPR _hoops_CPHR _hoops_RIR-_hoops_CAGH
			context._hoops_IGSCA();
			break;

		case _hoops_AICCA:
			HI_Unlock_Database(); // _hoops_PAGA: _hoops_HGAI, _hoops_HRSAR _hoops_ACPH; _hoops_HAR _hoops_RCPGR _hoops_PPR _hoops_CPHR _hoops_RIR-_hoops_CAGH
			context._hoops_IGSCA();
			break;

		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, Sprintf_D (null,
										  "Unknown Update Control value %d", option->type->id));
		}	break;

	} while ((option = option->next) != null);

	HI_Free_Option_List (context, option_list);
	return _hoops_ICCCA;
}


GLOBAL_FUNCTION void HI_Set_And_Clear_Flags (
	_hoops_AIGPR *			_hoops_RIGC,
	_hoops_CRCP *						segment,
	void *							info) {

	_hoops_PCCCA *	data = (_hoops_PCCCA *)info;
	_hoops_PCCCA		save;
	int								_hoops_CGSCA = _hoops_RSPPR(_hoops_RIGC, flags);
	int								_hoops_SGSCA = _hoops_RIGC->flags;
	Geometry *						g = null;

	_hoops_RSPPR(_hoops_RIGC, flags) &= ~_hoops_GRSCA;
	_hoops_RIGC->flags &= ~_hoops_RRSCA;

	save._hoops_CCCCA.clear = data->_hoops_CCCCA.clear;
	save.database.clear = data->database.clear;

	while (segment->type != _hoops_IRCP) {
		/* "_hoops_CAGH" _hoops_HRGR _hoops_CPSA _hoops_IRS _hoops_CPAP. _hoops_RAP _hoops_HHH _hoops_ARSCA _hoops_PPR _hoops_SSS _hoops_RGCI _hoops_RRRPR */
		segment->_hoops_CPGPR &= ~data->_hoops_CCCCA.clear;
		segment->_hoops_SPGPR &= ~data->_hoops_CCCCA.clear;
		segment->_hoops_CPGPR |= data->_hoops_CCCCA.set;
		segment->_hoops_RRHH &= ~data->database.clear;
		segment->_hoops_RRHH |= data->database.set;

		data->_hoops_CCCCA.set &= ~(_hoops_CASIR|_hoops_AHSGA);

		data->_hoops_CCCCA.clear = 0;		/* _hoops_AA _hoops_HAR _hoops_PRSCA "_hoops_HRSCA" _hoops_GH */
		data->database.clear = 0;

		g = (Geometry *)segment;
		segment = segment->owner;
	}

	if (data->_hoops_ASCCA) {
		Attribute *		_hoops_ASGPR;

		if ((_hoops_ASGPR = segment->_hoops_IPPGR) != null) do {
			if (_hoops_ASGPR->type >= HK_DRIVER) {
				if (_hoops_ASGPR->type == HK_DRIVER) {
					_hoops_GGAGR alter *		_hoops_GHRI = (_hoops_GGAGR alter *)_hoops_ASGPR;

					_hoops_GHRI->_hoops_CGPIR |= _hoops_IRSCA;
				}
				break;
			}
		} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
	}

	save._hoops_CCCCA.set = data->_hoops_CCCCA.set;
	save.database.set = data->database.set;

	if (data->_hoops_CCCCA.clear || data->database.clear) {
		data->_hoops_CCCCA.set = 0;		/* _hoops_AA _hoops_HAR _hoops_PRSCA "_hoops_ARH" _hoops_ISHP */
		data->database.set = 0;

		segment->_hoops_CPGPR &= ~data->_hoops_CCCCA.clear;
		segment->_hoops_SPGPR &= ~data->_hoops_CCCCA.clear;
		segment->_hoops_RRHH	&= ~data->database.clear;

		if (!BIT (segment->_hoops_RRHH, _hoops_GGSCA))
			segment->bounding = null;

		{	Attribute *		_hoops_ASGPR;

			if ((_hoops_ASGPR = segment->_hoops_IPPGR) != null) do {
				_hoops_ASGPR->_hoops_CPGPR &= ~data->_hoops_CCCCA.clear;
				_hoops_ASGPR->_hoops_SPGPR &= ~data->_hoops_CCCCA.clear;
				_hoops_ASGPR->_hoops_RRHH &= ~data->database.clear;
			} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
		}
		{	Geometry *		geometry;

			if ((geometry = segment->geometry) != null) do {
				geometry->_hoops_CPGPR &= ~data->_hoops_CCCCA.clear;
				geometry->_hoops_SPGPR &= ~data->_hoops_CCCCA.clear;
				geometry->_hoops_RRHH &= ~data->database.clear;
			} while ((geometry = geometry->next) != null);
		}
		{	Subsegment *	_hoops_GIPIA;

			if ((_hoops_GIPIA = segment->_hoops_RGRPR) != null) do {
				if (_hoops_GIPIA->type == _hoops_AGRPR) {
					_hoops_PGRPR *		include = (_hoops_PGRPR *)_hoops_GIPIA;

					_hoops_GIPIA->_hoops_CPGPR &= ~data->_hoops_CCCCA.clear;
					_hoops_GIPIA->_hoops_SPGPR &= ~data->_hoops_CCCCA.clear;
					_hoops_GIPIA->_hoops_RRHH &= ~data->database.clear;

					{
						_hoops_CRCP *		_hoops_HGRPR = (_hoops_CRCP alter *)include->_hoops_IGRPR;

						/* _hoops_PSP _hoops_RII _hoops_GCIS _hoops_IS _hoops_IHHH (_hoops_SR _hoops_CHR _hoops_RH _hoops_RGAR _hoops_CGRPR _hoops_GGR _hoops_RH _hoops_HIGR)? */
						if (_hoops_HGRPR->_hoops_SGRPR()->_hoops_GRRPR == null) {
							_hoops_CRCP *	owner = _hoops_HGRPR->owner;

							while (owner != HOOPS_WORLD->root) {
								/* _hoops_HRCC _hoops_ICAS _hoops_PCCP _hoops_RRRPR? */
								if (owner->_hoops_SGRPR() != null)
									break;
								owner = owner->owner;
							}

							/* _hoops_RPP _hoops_PIRC, _hoops_ICIC _hoops_IS _hoops_SCAC _hoops_SGI _hoops_APHR _hoops_ARI */
							if (owner == HOOPS_WORLD->root)
								HI_Set_And_Clear_Flags (_hoops_RIGC, _hoops_HGRPR, info);
						}
					}
				}
				else if (_hoops_GIPIA->type == _hoops_IRCP && _hoops_GIPIA->_hoops_CPGPR)
					HI_Set_And_Clear_Flags (_hoops_RIGC, (_hoops_CRCP *)_hoops_GIPIA, info);
			} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);
		}
	}

	/* _hoops_PHIH */
	data->_hoops_CCCCA.set = save._hoops_CCCCA.set;
	data->_hoops_CCCCA.clear = save._hoops_CCCCA.clear;
	data->database.set = save.database.set;
	data->database.clear = save.database.clear;

	if (data->_hoops_CCCCA.set) {
		if (data->area.left != -1.0f || data->area.right != 1.0f ||
			data->area.bottom != -1.0f || data->area.top != 1.0f) {

			char				segname[32];
			int					left, right, bottom, top;
			int					width, height;
			float				_hoops_CRSCA;
			Key					segkey;

			_hoops_PACIR	area = data->area;

			segkey = _hoops_AIRIR (segment);
			_hoops_GRSPR (segname, "%k", &segkey);
			if (HI_Compute_Window_Extent (_hoops_RIGC, segname, &_hoops_CRSCA, &_hoops_CRSCA,
										  &width, &height,
										  &left, &right, &bottom, &top)) {
				_hoops_CRSCA = 2.0f / (0.5f * (right - left + 1));
				if (area.left > 0.0f) area.left -= _hoops_CRSCA;
				if (area.right < 0.0f) area.right += _hoops_CRSCA;

				_hoops_CRSCA = 2.0f / (0.5f * (top - bottom + 1));
				if (area.bottom > 0.0f) area.bottom -= _hoops_CRSCA;
				if (area.top < 0.0f) area.top += _hoops_CRSCA;
			}

			HI_Propagate_Scoped_Activity (_hoops_RIGC, (_hoops_SIHIR *)segment,
										  data->_hoops_CCCCA.set, &area);
		}
		else
			HI_Propagate_Scoped_Activity (_hoops_RIGC, (_hoops_SIHIR *)segment,
										  data->_hoops_CCCCA.set, &data->area);
	}

	if (!ALLBITS (segment->_hoops_RRHH, data->database.set)) {
		_hoops_GCCCA ((_hoops_HPAH *)segment, data->database.set);
	}

	if (data->_hoops_RGSCA && BIT (segment->_hoops_RRHH, _hoops_GGSCA)) {
		_hoops_RPPPR();
		if (g) {
			g->_hoops_CPGPR |= _hoops_AHSGA;
			switch (g->type) {
				case _hoops_SCIP:
				case _hoops_GSIP: {
					Polyhedron alter *phon = (Polyhedron alter *)g;
					phon->bounding = null;
				} break;
				case _hoops_CSIP: {
					PolyCylinder *_hoops_HSPIR = (PolyCylinder *)g;
					_hoops_HSPIR->bounding = null;
				} break;
			}
		}

		Bounding	bounding;
		Bounding	_hoops_HSRIR;

		HI_Figure_Segment_Bounding (segment, bounding, _hoops_HSRIR);

		if (segment->bounding != null &&
				!BIT (segment->bounding->flags, _hoops_CCIIR))
			segment->bounding = null;

		if (segment->bounding == null)
			segment->bounding = bounding;

		segment->_hoops_HSRIR = _hoops_HSRIR;

		/* _hoops_RHRRA _hoops_PRSCA _hoops_IASC _hoops_ARI? */
		_hoops_IRRPR();
	}

	if (data->_hoops_AGSCA || data->_hoops_IHGI) {
		Attribute *		_hoops_HPHCR;

		if ((_hoops_HPHCR = segment->_hoops_IPPGR) != null) {
			do if (_hoops_HPHCR->type == HK_DRIVER)
				  break;
			while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);
		}

		if (_hoops_HPHCR && _hoops_HPHCR->type == HK_DRIVER) {
			_hoops_GGAGR *		driver = (_hoops_GGAGR *)_hoops_HPHCR;

			if (!ANYBIT (driver->_hoops_CGPIR, _hoops_GCSHA|_hoops_SGPIR))
				HI_Initialize_Actor (_hoops_RIGC, driver);	/* _hoops_SRSCA _hoops_PCSHA _hoops_GASCA */

			if (!BIT (driver->_hoops_CGPIR, _hoops_GCSHA)) {
				HE_ERROR (HEC_DRIVER, HES_DEAD_DRIVER,
						  Sprintf_P (null, "The device for '%p' doesn't seem to be alive", segment));
			}
			else {
				Display_Context alter *		dc = (Display_Context alter *)driver->_hoops_PPRPR;

				if (dc != null) {
					_hoops_CAAI (dc->_hoops_RASCA);
					if (data->_hoops_AGSCA)
						SET_MEMORY(dc->_hoops_IGGI, sizeof(dc->_hoops_IGGI), 0);
					if (data->_hoops_IHGI)
						dc->flags |= _hoops_CHSI;
					_hoops_APAI (dc->_hoops_RASCA);
				}
			}
		}
		else {
			HE_WARNING (HEC_DRIVER, HES_DEAD_DRIVER,
						Sprintf_P (null, "The segment '%p' doesn't seem to be a driver", segment));
		}
	}

	_hoops_RSPPR(_hoops_RIGC, flags) = _hoops_CGSCA;
	_hoops_RIGC->flags = _hoops_SGSCA;
}



HC_INTERFACE void HC_CDECL HC_Control_Update (
	char const *					segname,
	char const *					list)
{
	_hoops_PAPPR context("Control_Update");

	CODE_GENERATION (
		if (segname != null)
			HI_Dump_Code (Sprintf_SS (null, "HC_Control_Update (%S, %S);\n", segname, list));
		else
			HI_Dump_Code (Sprintf_S (null, "HC_Control_Update (0, %S);\n", list));
	);

	_hoops_PCCCA		data;

	if (!_hoops_ACCCA (context, list, &data))
		return;

	if (segname != null) {
		_hoops_CSPPR();
		HI_For_Each (context, segname, true, HI_Set_And_Clear_Flags, (void *)&data);
		_hoops_IRRPR();
	}
}

HC_INTERFACE void HC_CDECL HC_Control_Update_Area (
	char const *					segname,
	double							left,
	double							right,
	double							bottom,
	double							top,
	char const *					list)
{
	_hoops_PAPPR context("Control_Update_Area");

	CODE_GENERATION (
		if (segname != null)
			HI_Dump_Code (Sprintf_SS (null, "HC_Control_Update_Area (%S, %S ", segname, list));
		else
			HI_Dump_Code (Sprintf_S (null, "HC_Control_Update_Area (0, %S, ", list));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", left, right));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", bottom, top));
		HI_Dump_Code (Sprintf_S (null, "%S);\n", list));
	);

	_hoops_PCCCA	data;

	if (!_hoops_ACCCA (context, list, &data))
		return;

	if (segname != null) {
		data._hoops_CCCCA.set &= ~_hoops_AASCA;

		data.area.left	 = (float)left;		data.area.right = (float)right;
		data.area.bottom = (float)bottom;	data.area.top	= (float)top;

		_hoops_CSPPR();
		HI_For_Each (context, segname, true, HI_Set_And_Clear_Flags, (void *)&data);
		_hoops_IRRPR();
	}
}

HC_INTERFACE void HC_CDECL HC_Control_Update_By_Key (
	Key								key,
	char const *					list)
{
	_hoops_PAPPR context("Control_Update_By_Key");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Control_Update_By_Key (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_S (null, "%S);\n", list));
	);

	_hoops_PCCCA		data;

	if (!_hoops_ACCCA (context, list, &data))
		return;

	if (key != _hoops_SHSSR) {
		_hoops_CSPPR();

		_hoops_HPAH *	item = _hoops_RCSSR (context, key);
		if (item != null)
			HI_Set_And_Clear_Flags (context, (_hoops_CRCP *)item, (void*)&data);
		else
			HE_ERROR (HEC_GEOMETRY_OR_SEGMENT, HES_INVALID_KEY, "Provided key does not point to a valid geometry or segment");

		_hoops_IRRPR();
	}
}

HC_INTERFACE void HC_CDECL HC_Control_Update_Area_By_Key (
	Key								key,
	double							left,
	double							right,
	double							bottom,
	double							top,
	char const *					list)
{

	_hoops_PAPPR context("Control_Update_Area_By_Key");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Control_Update_Area_By_Key (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", left, right));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", bottom, top));
		HI_Dump_Code (Sprintf_S (null, "%S);\n", list));
	);

	_hoops_PCCCA		data;

	if (!_hoops_ACCCA (context, list, &data))
		return;

	if (key != _hoops_SHSSR) {
		_hoops_CSPPR();
		_hoops_HPAH *	item = _hoops_RCSSR (context, key);

		if (item != null) {
			data._hoops_CCCCA.set &= ~_hoops_AASCA;
			data.area.left	 = (float)left;		data.area.right = (float)right;
			data.area.bottom = (float)bottom;	data.area.top	= (float)top;
			HI_Set_And_Clear_Flags (null, (_hoops_CRCP *)item, (void*)&data);
		}
		else
			HE_ERROR (HEC_GEOMETRY_OR_SEGMENT, HES_INVALID_KEY, "Provided key does not point to a valid geometry or segment");

		_hoops_IRRPR();
	}
}



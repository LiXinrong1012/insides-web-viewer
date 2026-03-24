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
 * $Id: obf_tmp.txt 1.81 2010-10-06 19:16:43 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


struct _hoops_GGIPI {
	Vector				direction;
	Light *				light;
	int					_hoops_IGSSR;
};

local void _hoops_RGIPI (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_GGIPI *		data) 
{
	_hoops_HIPIR *			light;
	ZALLOC (light, _hoops_HIPIR);
	light->type = _hoops_ICIP;
	light->_hoops_CPGPR = _hoops_PHSSR;
	light->_hoops_PRR = _hoops_H;
	light->direction = light->original = data->direction;
	light->direction._hoops_AAIAR();
	light->time_stamp = HOOPS_WORLD->_hoops_GPPI + 1;
	
	HI_Insert_Geometry (_hoops_RIGC, item, (Geometry *) light,
							light->direction.z == 0.0f,
							_hoops_CCHPA);

	if (item->type == _hoops_IRCP)
		HI_More_Light (_hoops_RIGC, (_hoops_CRCP*)item, 1);

	data->light = light;
	++data->_hoops_IGSSR;
}

GLOBAL_FUNCTION Key HI_Insert_Distant_Light (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Vector const &			direction) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_GGIPI	data;

	ZERO_STRUCT (&data, _hoops_GGIPI);
	data.direction = direction;

	_hoops_RGIPI (_hoops_RIGC, item, &data);
	
	Key	_hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data.light);

	return _hoops_CHSSR;
}


HC_INTERFACE Key HC_CDECL HC_Insert_Distant_Light (
	double				x,
	double				y,
	double				z) 
{
	_hoops_PAPPR context("Insert_Distant_Light");

	if (x == 0 && y == 0 && z == 0) {
		HE_ERROR (HEC_DISTANT_LIGHT, HES_INVALID_DIRECTION, "Light direction cannot be all zeroes");
		return _hoops_SHSSR;
	}

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Distant_Light (context, target, Vector(x,y,z));
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "DEFINE (HC_Insert_Distant_Light (%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%F), ", z));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
	);

	return _hoops_CHSSR;
}



local const _hoops_IGRCR _hoops_AGIPI[] = {
	{_hoops_CISGP, _hoops_GRRCR ("front"), _hoops_RRRCR, 0, false},
	{_hoops_SISGP,	_hoops_GRRCR ("back"), _hoops_RRRCR, 0, false},
	{_hoops_GCSGP,	_hoops_GRRCR ("both"), _hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_PGIPI = {
	_hoops_GGAPR (_hoops_AGIPI),				_hoops_AGIPI,
};

local const _hoops_IGRCR _hoops_HGIPI[] = {
	{_hoops_IISGP,			 _hoops_GRRCR ("bright side"),
		_hoops_GHAGA, -999, false, &_hoops_PGIPI},
};


struct _hoops_IGIPI {
	int					count;
	Point const *		points;
	_hoops_GISGP			flags;
	_hoops_GISGP			_hoops_HSSGP;
	Light *				light;
	int					_hoops_IGSSR;
};


local bool _hoops_CGIPI (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_IGIPI *			data,
	char const *			list) 
{
	ZERO_STRUCT(data, _hoops_IGIPI);

	Option_Value *		option_list;
	Option_Value *		option;
	bool				_hoops_IA = true;

	data->_hoops_HSSGP = _hoops_CISGP;

	_hoops_HIACR (_hoops_GHRGI, _hoops_HGIPI);

	if (!HI_Parse_Options (_hoops_RIGC, list, _hoops_CIACR (_hoops_GHRGI), &option_list, _hoops_SIACR)) 
		return false;

	if ((option = option_list) != null) do switch (option->type->id) {
		case _hoops_IISGP: {
			data->flags |= _hoops_IISGP;
			data->_hoops_HSSGP = (int)option->value.option_list->type->id;
		}	break;

		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Area light option lookup");
			_hoops_IA = false;
		}
	} while ((option = option->next) != null);

	HI_Free_Option_List (_hoops_RIGC, option_list);

	return _hoops_IA;
}


local void _hoops_SGIPI (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_IGIPI *			data) 
{


	_hoops_SHPIR *	light;
	ZALLOC (light, _hoops_SHPIR);
	light->type = _hoops_ICIP;
	light->_hoops_CPGPR = _hoops_PHSSR;

	light->_hoops_PRR = _hoops_S;
	light->flags = data->flags;
	light->_hoops_HSSGP = data->_hoops_HSSGP;
	light->count = data->count;

	bool	_hoops_GRIPI = true;

	if (light->count > 0) {
		Point *	_hoops_PAGR;
		ALLOC_ARRAY (_hoops_PAGR, light->count, Point);
		light->points = _hoops_PAGR;
		Point const *	in = data->points;
		int				count = light->count;
		do {
			_hoops_PAGR->x = in->x;
			_hoops_PAGR->y = in->y;
			_hoops_PAGR->z = in->z;
			++_hoops_PAGR;
			++in;
			if (in->z != 0.0f) 
				_hoops_GRIPI = false;
		} while (--count > 0);
	}

	light->time_stamp = HOOPS_WORLD->_hoops_GPPI + 1;

	HI_Insert_Geometry (_hoops_RIGC, item, (Geometry *) light,
						_hoops_GRIPI,
						_hoops_CCHPA);

	if (item->type == _hoops_IRCP)
		HI_More_Light (_hoops_RIGC, (_hoops_CRCP*)item, 1);

	data->light = light;
	++data->_hoops_IGSSR;
}

GLOBAL_FUNCTION Key HI_Insert_Area_Light (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	int						count,
	Point const	*			points,
	char const *			list) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_IGIPI	data;
	if (!_hoops_CGIPI (_hoops_RIGC, &data, list)) {
		return _hoops_SHSSR;
	}

	data.count = count;
	data.points = points;

	Key	_hoops_CHSSR = _hoops_SHSSR;

	_hoops_SGIPI (_hoops_RIGC, item, &data);

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data.light);

	return _hoops_CHSSR;
}

HC_INTERFACE Key HC_CDECL HC_Insert_Area_Light (
	int				count,
	Point const	*	points,
	char const *	list) 
{	
	_hoops_PAPPR context("Insert_Area_Light");

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Area_Light (context, target, count, points, list);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_D (null, "{HC_POINT points[%d];\n", count));
		++HOOPS_WORLD->_hoops_ISPPR;
		for(int i=0; i<count; i++) {
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].x = %f;	 ", i, points[i].x));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].y = %f;	 ", i, points[i].y));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].z = %f;\n", i, points[i].z));
		}
		HI_Dump_Code (Sprintf_D (null, "DEFINE (HC_Insert_Area_Light (%d, points, ", count));
		HI_Dump_Code (Sprintf_S (null, "%S), ", list));
		HI_Dump_Code (Sprintf_D (null, "%D);}\n", _hoops_CHSSR));
		--HOOPS_WORLD->_hoops_ISPPR;
	);

	return _hoops_CHSSR;
}


local const _hoops_IGRCR _hoops_AHSIA[] = {
	{_hoops_ICSGP,		_hoops_GRRCR ("%"),						_hoops_RRRCR, 0, false},
	{_hoops_HCSGP,		_hoops_GRRCR ("deg"),					_hoops_RRRCR, 0, false},
	{_hoops_HCSGP,		_hoops_GRRCR ("degree"),				_hoops_RRRCR, 0, false},
	{_hoops_HCSGP,		_hoops_GRRCR ("degrees"),				_hoops_RRRCR, 0, false},
	{_hoops_PCSGP,			_hoops_GRRCR ("fru"),					_hoops_RRRCR, 0, false},
	{_hoops_PCSGP,			_hoops_GRRCR ("field relative units"),	_hoops_RRRCR, 0, false},
};

/* _hoops_GIGHR: _hoops_CRIPR _hoops_GHCA _hoops_HAR _hoops_SHH "%", _hoops_HIS _hoops_HSGR _hoops_SRS _hoops_RARP _hoops_GGR _hoops_GASR */
local const _hoops_HPAGA _hoops_RRIPI = {
	_hoops_GGAPR (_hoops_AHSIA) - 1,
	&_hoops_AHSIA[1],
};

/* _hoops_HIH _hoops_PSSPR _hoops_PAH _hoops_SGH "%" */
local const _hoops_HPAGA _hoops_ARIPI = {
	_hoops_GGAPR (_hoops_AHSIA),
	_hoops_AHSIA,
};

local const _hoops_IGRCR _hoops_PRIPI[] = {
	{_hoops_AISGP,			 _hoops_GRRCR ("edge sharpness"),		_hoops_CIGHA, 1, false, &_hoops_ARIPI},
	{_hoops_AISGP,			 _hoops_GRRCR ("inner cone"),			_hoops_CIGHA, 1, false, &_hoops_ARIPI},
	{_hoops_PISGP,			 _hoops_GRRCR ("illumination cone"),	_hoops_CIGHA, 1, false, &_hoops_RRIPI},
	{_hoops_PISGP,			 _hoops_GRRCR ("outer cone"),			_hoops_CIGHA, 1, false, &_hoops_RRIPI},
	{_hoops_HISGP,	 _hoops_GRRCR ("concentration"),		_hoops_SPPCR, 1, false},
	{_hoops_RISGP, _hoops_GRRCR ("camera relative"),		_hoops_RRRCR, 0, true},
	{_hoops_RISGP, _hoops_GRRCR ("camera-relative"),		_hoops_RRRCR, 0, true},
};



struct _hoops_HRIPI {
	Point				position;
	Point				target;
	float				_hoops_ACSR;
	float				_hoops_HCSR;
	float				_hoops_CCSGP;
	_hoops_GISGP			flags;
	_hoops_RCSGP	_hoops_GSSGP;
	_hoops_RCSGP	_hoops_SCSGP;

	float				_hoops_ASSGP;
	float				_hoops_RSSGP;

	Light *				light;
	int					_hoops_IGSSR;
};


local bool _hoops_IRIPI (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HRIPI *			data,
	char const *			list,
	Point const &			position,
	Point const &			target) 
{
	ZERO_STRUCT(data, _hoops_HRIPI);

	Option_Value *		option_list;
	Option_Value *		option;
	bool				_hoops_IA = true;

	data->_hoops_ACSR = 80.0f;
	data->_hoops_HCSR = 30.0f;
	data->_hoops_GSSGP = _hoops_ICSGP;
	data->_hoops_SCSGP = _hoops_HCSGP;
	data->_hoops_CCSGP = 1.0f;

	_hoops_HIACR (_hoops_PHRGI, _hoops_PRIPI);

	if (!HI_Parse_Options (_hoops_RIGC, list, _hoops_CIACR (_hoops_PHRGI), &option_list, _hoops_SIACR)) 
		return false;

	if ((option = option_list) != null) do {
		if (option->_hoops_GCACR)
			data->flags &= (int)~option->type->id;
		else {
			data->flags |= (int)option->type->id;

			switch (option->type->id) {
				case _hoops_AISGP: {
					data->_hoops_ACSR = option->value._hoops_RRRHA[0].value;
					data->_hoops_GSSGP = (_hoops_RCSGP)
								option->value._hoops_RRRHA[0]._hoops_HHP;
				}	break;

				case _hoops_PISGP: {
					data->_hoops_HCSR = option->value._hoops_RRRHA[0].value;
					data->_hoops_SCSGP = (_hoops_RCSGP)
								option->value._hoops_RRRHA[0]._hoops_HHP;
				}	break;

				case _hoops_HISGP: {
					data->_hoops_CCSGP = option->value._hoops_PIPCR[0];
				}	break;

				case _hoops_RISGP: {
				}	break;

				default: {
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Spot Light option lookup");
					_hoops_IA = false;
				}
			}
		}
	} while ((option = option->next) != null);

	HI_Free_Option_List (_hoops_RIGC, option_list);

	/* _hoops_RPP _hoops_HAR _hoops_SARA-_hoops_CSCHR, _hoops_SR _hoops_PAH _hoops_ISPR _hoops_AHC _hoops_HCPC. _hoops_SAAP _hoops_ARI.
	** _hoops_IAII, _hoops_SR _hoops_PIHA _hoops_IPPRH _hoops_CCGR _hoops_ASCA _hoops_GHIR */

	if (!BIT (data->flags, _hoops_RISGP) &&
		position.x == target.x && position.y == target.y && position.z == target.z) {
		HE_ERROR (HEC_SPOT_LIGHT, HES_BAD_POSITION, "Spot Light position and target can not be the same");
		return false;
	}

	switch (data->_hoops_SCSGP) {
		case _hoops_HCSGP: {
			if (data->_hoops_HCSR < 0.0f || data->_hoops_HCSR > 360.0f) {
				HE_ERROR (HEC_SPOT_LIGHT, HES_BAD_ILLUMINATION_ANGLE, "'Illumination Cone' must be from 0 to 360 degrees");
				return false;
			}
			data->_hoops_ASSGP = 0.5f * data->_hoops_HCSR;
		}	break;

		case _hoops_PCSGP: {
			float			tmp;
			float			_hoops_CRIPI;

			if (data->_hoops_ACSR < 0.0f) {
				HE_ERROR (HEC_SPOT_LIGHT, HES_BAD_ILLUMINATION_FRU, "'Illumination Cone' may not be negative");
				return false;
			}

			/* _hoops_SARA-_hoops_CSCHR _hoops_PIHA _hoops_SHH _hoops_GGSRA _hoops_HPGR _hoops_PAAP _hoops_GHIR */
			if (!BIT (data->flags, _hoops_RISGP)) {
				tmp = position.x - target.x;
				_hoops_CRIPI = tmp * tmp;
				tmp = position.y - target.y;
				_hoops_CRIPI += tmp * tmp;
				tmp = position.z - target.z;
				_hoops_CRIPI += tmp * tmp;

				tmp = data->_hoops_HCSR * 0.5f;
				tmp *= tmp;
				tmp += _hoops_CRIPI;	/* _hoops_SRIPI^2 */
				tmp = _hoops_SGIHR (_hoops_CRIPI) / _hoops_SGIHR (tmp);
				data->_hoops_ASSGP = _hoops_ISSSR (tmp);
			}
			else
				data->_hoops_ASSGP = data->_hoops_HCSR;
		}	break;
	}

	switch (data->_hoops_GSSGP) {
		case _hoops_HCSGP: {
			if (data->_hoops_ACSR < 0.0f || data->_hoops_ACSR > 360.0f) {
				HE_ERROR (HEC_SPOT_LIGHT, HES_BAD_EDGE_SHARPNESS_ANGLE, "'Edge Sharpness' must be from 0 to 360 degrees");
				return false;
			}
			data->_hoops_RSSGP = 0.5f * data->_hoops_ACSR;
		}	break;

		case _hoops_PCSGP: {
			float			tmp;
			float			_hoops_CRIPI;

			if (data->_hoops_ACSR < 0.0f) {
				HE_ERROR (HEC_SPOT_LIGHT, HES_BAD_EDGE_SHARPNESS_FRU, "'Edge Sharpness' may not be negative");
				return false;
			}

			/* _hoops_SARA-_hoops_CSCHR _hoops_PIHA _hoops_SHH _hoops_GGSRA _hoops_HPGR _hoops_PAAP _hoops_GHIR */
			if (!BIT (data->flags, _hoops_RISGP)) {
				tmp = position.x - target.x;
				_hoops_CRIPI = tmp * tmp;
				tmp = position.y - target.y;
				_hoops_CRIPI += tmp * tmp;
				tmp = position.z - target.z;
				_hoops_CRIPI += tmp * tmp;

				tmp = data->_hoops_ACSR * 0.5f;
				tmp *= tmp;
				tmp += _hoops_CRIPI;	/* _hoops_SRIPI^2 */
				tmp = _hoops_SGIHR (_hoops_CRIPI) / _hoops_SGIHR (tmp);
				data->_hoops_RSSGP = _hoops_ISSSR (tmp);
			}
			else
				data->_hoops_RSSGP = data->_hoops_ACSR;
		}	break;

		case _hoops_ICSGP: {
			if (data->_hoops_ACSR < 0.0f || data->_hoops_ACSR > 100.0f) {
				HE_ERROR (HEC_SPOT_LIGHT, HES_BAD_EDGE_SHARPNESS_PERCENT, "'Edge Sharpness' must be from 0% to 100%");
				return false;
			}
			data->_hoops_RSSGP = 0.01f * data->_hoops_ACSR * data->_hoops_ASSGP;
		}	break;
	}

	if (data->_hoops_CCSGP < 0.0f) {
		HE_ERROR (HEC_SPOT_LIGHT, HES_BAD_CONCENTRATION, "'Concentration' may not be negative");
		return false;
	}

	return _hoops_IA;
}


local void _hoops_GAIPI (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_HRIPI *			data) 
{
	_hoops_PIPIR *			light;
	ZALLOC (light, _hoops_PIPIR);
	light->type = _hoops_ICIP;
	light->_hoops_CPGPR = _hoops_PHSSR;

	light->_hoops_PRR = _hoops_I;
	light->flags = data->flags;

	light->position = data->position;
	light->target = data->target;

	light->_hoops_HCSR = data->_hoops_HCSR;
	light->_hoops_ACSR = data->_hoops_ACSR;
	light->_hoops_SCSGP = data->_hoops_SCSGP;
	light->_hoops_GSSGP = data->_hoops_GSSGP;
	light->_hoops_CCSGP = data->_hoops_CCSGP;
	light->_hoops_ASSGP = data->_hoops_ASSGP;
	light->_hoops_RSSGP = data->_hoops_RSSGP;

	light->time_stamp = HOOPS_WORLD->_hoops_GPPI + 1;

	HI_Insert_Geometry (_hoops_RIGC, item, (Geometry *) light,
						light->position.z == 0.0f &&
						light->target.z == 0.0f,
						_hoops_CCHPA);

	if (item->type == _hoops_IRCP)
		HI_More_Light (_hoops_RIGC, (_hoops_CRCP*)item, 1);

	data->light = light;
	++data->_hoops_IGSSR;
}


GLOBAL_FUNCTION Key HI_Insert_Spot_Light (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Point const	&			position,
	Point const	&			target,
	char const *			list) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_HRIPI	data;

	if (!_hoops_IRIPI (_hoops_RIGC, &data, list, position, target)) {
		return _hoops_SHSSR;
	}

	data.position = position;
	data.target = target;

	Key	_hoops_CHSSR = _hoops_SHSSR;

	_hoops_GAIPI (_hoops_RIGC, item, &data);

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data.light);

	return _hoops_CHSSR;
}


HC_INTERFACE Key HC_CDECL HC_Insert_Spot_Light (
	Point const	*	position,
	Point const	*	_hoops_RAIPI,
	char const *	list) 
{
	_hoops_PAPPR context("Insert_Spot_Light");

	if (!position || !_hoops_RAIPI) {
		HE_ERROR (HEC_SPOT_LIGHT, HES_INVALID_INPUT, "All points must be provided.");
		return _hoops_SHSSR;
	}

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Spot_Light (context, target, *position, *_hoops_RAIPI, list);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code ("{HC_POINT position, target;\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_FF (null, "position.x = %f;  position.y = %f;	 ", position->x, position->y));
		HI_Dump_Code (Sprintf_F (null, "position.z = %f;\n", position->z));
		HI_Dump_Code (Sprintf_FF (null, "target.x = %f;	 target.y = %f;	 ", _hoops_RAIPI->x, _hoops_RAIPI->y));
		HI_Dump_Code (Sprintf_F (null, "target.z = %f;\n", _hoops_RAIPI->z));
		HI_Dump_Code (Sprintf_S (null, "DEFINE (HC_Insert_Spot_Light (&position, &target, %S), ", list));
		HI_Dump_Code (Sprintf_LD (null, "%D);}\n", _hoops_CHSSR));
		--HOOPS_WORLD->_hoops_ISPPR;
	);

	return _hoops_CHSSR;
}


struct _hoops_AAIPI {
	Point				position;
	Light *				light;
	int					_hoops_IGSSR;
};


local void _hoops_PAIPI (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_AAIPI *		data) 
{
	_hoops_AIPIR *			light;
	ZALLOC (light, _hoops_AIPIR);
	light->type = _hoops_ICIP;
	light->_hoops_CPGPR = _hoops_PHSSR;
	light->_hoops_PRR = _hoops_C;
	light->position = data->position;
	light->time_stamp = HOOPS_WORLD->_hoops_GPPI + 1;

	HI_Insert_Geometry (_hoops_RIGC, item, (Geometry *) light,
						light->position.z == 0.0f,
						_hoops_CCHPA);

	if (item->type == _hoops_IRCP)
		HI_More_Light (_hoops_RIGC, (_hoops_CRCP*)item, 1);

	data->light = light;
	++data->_hoops_IGSSR;
}

GLOBAL_FUNCTION Key HI_Insert_Local_Light (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Point const &			position) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_AAIPI data;
	ZERO_STRUCT (&data, _hoops_AAIPI);
	data.position = position;

	Key	_hoops_CHSSR = _hoops_SHSSR;

	_hoops_PAIPI (_hoops_RIGC, item, &data);

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data.light);

	return _hoops_CHSSR;
}


HC_INTERFACE Key HC_CDECL HC_Insert_Local_Light (
	double			x,
	double			y,
	double			z) 
{
	_hoops_PAPPR context("Insert_Local_Light");

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Local_Light (context, target, Point(x,y,z));
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "DEFINE (HC_Insert_Local_Light (%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%F), ", z));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
	);

	return _hoops_CHSSR;
}



HC_INTERFACE void HC_CDECL HC_Show_Distant_Light (
	Key							key,
	float *						x,
	float *						y,
	float *						z) 
{
	_hoops_PAPPR context("Show_Distant_Light");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Distant_Light () */\n");
	);

	_hoops_CSPPR();

	_hoops_HIPIR const *	light = (_hoops_HIPIR const *)_hoops_RCSSR (context, key);

	if (light == null ||
		light->type != _hoops_ICIP || light->_hoops_PRR != _hoops_H ||
		BIT (light->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_DISTANT_LIGHT, HES_INVALID_KEY, "Provided key does not refer to a valid 'distant light'");
	}
	else {
		*x = light->original.x;
		*y = light->original.y;
		*z = light->original.z;
	}

	_hoops_IRRPR();
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Spot_Light (
	Key					key,
	Point *				position,
	Point *				target,
	char *				list) 
{
	_hoops_PAPPR context("Show_Spot_Light");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Spot_Light () */\n");
	);

	_hoops_CSPPR();

	_hoops_PIPIR const *	light = (_hoops_PIPIR const *)_hoops_RCSSR (context, key);

	if (light == null ||
		light->type != _hoops_ICIP || light->_hoops_PRR != _hoops_I ||
		BIT (light->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SPOT_LIGHT, HES_INVALID_KEY, "Provided key does not refer to a valid 'spot light'");
	}
	else {

		char	buf[1024];
		char *	p = buf;

		if (position != null)
			*position = light->position;

		if (target != null)
			*target = light->target;

		if (BIT (light->flags, _hoops_RISGP))
			p = HI_Copy_Chars ("camera relative,", p);

		if (BIT (light->flags, _hoops_PISGP)) {
			p = HI_Sprintf1 (p, buf+_hoops_GGAPR(buf)-1, "illumination cone=%f", (void *)&light->_hoops_HCSR);
			switch (light->_hoops_SCSGP) {
				case _hoops_HCSGP:	p = HI_Copy_Chars (" degrees,", p);		break;
				case _hoops_PCSGP:		p = HI_Copy_Chars (" fru,", p);			break;
			}
		}
		if (BIT (light->flags, _hoops_AISGP)) {
			p = HI_Sprintf1 (p, buf+_hoops_GGAPR(buf)-1, "edge sharpness=%f", (void *)&light->_hoops_ACSR);
			switch (light->_hoops_GSSGP) {
				case _hoops_HCSGP:	p = HI_Copy_Chars (" degrees,", p);		break;
				case _hoops_PCSGP:		p = HI_Copy_Chars (" fru,", p);			break;
				case _hoops_ICSGP:	p = HI_Copy_Chars ("%,", p);			break;
			}
		}
		if (BIT (light->flags, _hoops_HISGP)) {
			p = HI_Sprintf1 (p, buf+_hoops_GGAPR(buf)-1, "concentration=%f,", (void *)&light->_hoops_CCSGP);
		}
		if (p != buf) --p;

		if (list != null)
			HI_Return_Chars (list, -1, buf, (int)(p - buf));
	}

	_hoops_IRRPR();
#endif
}



#ifndef DISABLE_GEOMETRY_SHOW

local void _hoops_HAIPI (
	_hoops_SHPIR const *	light,
	char *				list,
	int					_hoops_GGCIR) {

	if (BIT (light->flags, _hoops_IISGP))
		switch (light->_hoops_HSSGP) {
			case _hoops_CISGP: {
				HI_Return_Chars (list, _hoops_GGCIR, "bright side=front", 17);
			}	break;

			case _hoops_SISGP:	{
				HI_Return_Chars (list, _hoops_GGCIR, "bright side=back", 16);
			}	break;

			case _hoops_GCSGP:	{
				HI_Return_Chars (list, _hoops_GGCIR, "bright side=both", 16);
			}	break;
		}
	else
		HI_Return_Chars (list, _hoops_GGCIR, "", 0);
}

#endif

HC_INTERFACE void HC_CDECL HC_Show_Area_Light (
	Key						key,
	int *					ucount,
	Point *					upoints,
	char *					list) 
{
	_hoops_PAPPR context("Show_Area_Light");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Area_Light () */\n");
	);

	_hoops_CSPPR();

	_hoops_SHPIR const *	light = (_hoops_SHPIR const *)_hoops_RCSSR (context, key);

	if (light == null ||
		light->type != _hoops_ICIP || light->_hoops_PRR != _hoops_S ||
		BIT (light->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_AREA_LIGHT, HES_INVALID_KEY, "Provided key does not refer to a valid 'area light'");
	}
	else {
		int count = light->count;
		Point *	points = light->points;

		if (ucount != null)
			*ucount = count;

		if (upoints != null) {
			_hoops_RGGA (count-- <= 0) {
				upoints->x = points->x;
				upoints->y = points->y;
				upoints->z = points->z;
				upoints++;
				points++;
			}
		}

		if (list != null)
			_hoops_HAIPI (light, list, -1);
	}

	_hoops_IRRPR();
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Area_Light_Count (
	Key						key,
	int *					count,
	char *					list) 
{
	_hoops_PAPPR context("Show_Area_Light_Count");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Area_Light_Count () */\n");
	);

	_hoops_CSPPR();

	_hoops_SHPIR const *	light = (_hoops_SHPIR const *)_hoops_RCSSR (context, key);

	if (light == null ||
		light->type != _hoops_ICIP || light->_hoops_PRR != _hoops_S ||
		BIT (light->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_AREA_LIGHT, HES_INVALID_KEY, "Provided key does not refer to a valid 'area light'");
	}
	else {
		*count = light->count;

		if (list != null)
			_hoops_HAIPI (light, list, -1);
	}

	_hoops_IRRPR();
#endif
}






HC_INTERFACE void HC_CDECL HC_Show_Local_Light (
	Key						key,
	float *					x,
	float *					y,
	float *					z) 
{
	_hoops_PAPPR context("Show_Local_Light");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Local_Light () */\n");
	);

	_hoops_CSPPR();

	_hoops_AIPIR const *	light = (_hoops_AIPIR const *)_hoops_RCSSR (context, key);

	if (light == null ||
		light->type != _hoops_ICIP || light->_hoops_PRR != _hoops_C ||
		BIT (light->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_LOCAL_LIGHT, HES_INVALID_KEY, "Provided key does not refer to a valid 'local light'");
	}
	else {
		*x = light->position.x;
		*y = light->position.y;
		*z = light->position.z;
	}

	_hoops_IRRPR();
#endif
}




// _hoops_PAGA: _hoops_IAIPI _hoops_CGH _hoops_SHH _hoops_RHSI _hoops_HII _hoops_AGCR _hoops_PSCH _hoops_RPP _hoops_RH _hoops_ACAR _hoops_PCAAA _hoops_RARIR _hoops_PAII _hoops_RRR

HC_INTERFACE void HC_CDECL HC_Move_Light_Position (
	Key						key,
	double					x,
	double					y,
	double					z) 
{
	_hoops_PAPPR context("Move_Light_Position");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Move_Light_Position (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%F);\n", z));
	);

	_hoops_CRCP *				_hoops_SRCP;

	_hoops_RPPPR();

	Light alter *	light = (Light *)_hoops_RCSSR (context, key);

	if (light == null ||
		light->type != _hoops_ICIP ||
		(light->_hoops_PRR != _hoops_C	 &&	 light->_hoops_PRR != _hoops_I) ||
		BIT (light->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SPOT_LIGHT, HES_INVALID_KEY, "Provided key does not refer to a valid \"Local Light\" or \"Spot Light\"");
		goto Release;
	}

	if (light->_hoops_PRR == _hoops_C) {
		_hoops_AIPIR alter *		pl = (_hoops_AIPIR alter *)light;

		pl->position.x = (float)x;
		pl->position.y = (float)y;
		pl->position.z = (float)z;
	}
	else {
		_hoops_PIPIR alter *		sl = (_hoops_PIPIR alter *)light;

		if (!BIT (light->flags, _hoops_RISGP) &&
			x == sl->target.x &&
			y == sl->target.y &&
			z == sl->target.z) {
			HE_ERROR (HEC_SPOT_LIGHT, HES_BAD_POSITION, "Spot Light position and target may not be the same");
			goto Release;
		}

		sl->position.x = (float)x;
		sl->position.y = (float)y;
		sl->position.z = (float)z;
	}

	light->_hoops_CPGPR |= _hoops_HHSSR;

	_hoops_SRCP = light->owner;

	if (!BIT (light->_hoops_RRHH, _hoops_RSPCR)) {
		if (z != 0.0f) {
			light->_hoops_RRHH |= _hoops_RSPCR;
			if (!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_ASPCR))
				HI_Propagate_Maybes (context, _hoops_SRCP, _hoops_ASPCR);
		}
	}

	_hoops_SASIR (context, _hoops_SRCP, _hoops_AISSR|_hoops_RPSIR|_hoops_IISSR);

  Release:
	_hoops_IRRPR();
}


HC_INTERFACE void HC_CDECL HC_Move_Light_Target (
	Key					key,
	double				x,
	double				y,
	double				z) 
{
	_hoops_PAPPR context("Move_Light_Target");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Move_Light_Target (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%F);\n", z));
	);

	_hoops_CRCP *	_hoops_SRCP;

	_hoops_RPPPR();
	_hoops_PIPIR alter *	light = (_hoops_PIPIR alter *)_hoops_RCSSR (context, key);

	if (light == null ||
		light->type != _hoops_ICIP || light->_hoops_PRR != _hoops_I ||
		BIT (light->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SPOT_LIGHT, HES_INVALID_KEY, "Provided key does not refer to a valid \"Spot Light\"");
		goto Release;
	}

	if (!BIT (light->flags, _hoops_RISGP) &&
		x == light->position.x &&
		y == light->position.y &&
		z == light->position.z) {
		HE_ERROR (HEC_SPOT_LIGHT, HES_BAD_POSITION, "Spot Light position and target may not be the same");
		goto Release;
	}

	light->target.x = (float)x;
	light->target.y = (float)y;
	light->target.z = (float)z;

	light->_hoops_CPGPR |= _hoops_HHSSR;

	_hoops_SRCP = light->owner;

	if (!BIT (light->_hoops_RRHH, _hoops_RSPCR)) {
		if (z != 0.0f) {
			light->_hoops_RRHH |= _hoops_RSPCR;
			if (!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_ASPCR))
				HI_Propagate_Maybes (context, _hoops_SRCP, _hoops_ASPCR);
		}
	}

	_hoops_SASIR (context, _hoops_SRCP, _hoops_AISSR|_hoops_RPSIR|_hoops_IISSR);

  Release:
	_hoops_IRRPR();
}



HC_INTERFACE void HC_CDECL HC_Move_Distant_Light (
	Key						key,
	double					x,
	double					y,
	double					z) 
{
	_hoops_PAPPR context("Move_Distant_Light");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Move_Distant_Light (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%F);\n", z));
	);

	if (x == 0 && y == 0 && z == 0) {
		HE_ERROR (HEC_DISTANT_LIGHT, HES_INVALID_DIRECTION, "Light direction cannot be all zeroes");
		return;
	}

	_hoops_CRCP *	_hoops_SRCP;

	_hoops_RPPPR();

	_hoops_HIPIR alter *	light = (_hoops_HIPIR alter *)_hoops_RCSSR (context, key);

	if (light == null ||
		light->type != _hoops_ICIP || light->_hoops_PRR != _hoops_H ||
		BIT (light->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_DISTANT_LIGHT, HES_INVALID_KEY, "Provided key does not refer to a valid \"Distant Light\"");
		goto Release;
	}

	light->direction.x = light->original.x = (float)x;
	light->direction.y = light->original.y = (float)y;
	light->direction.z = light->original.z = (float)z;

	HI_Normalize (&light->direction);

	light->_hoops_CPGPR |= _hoops_HHSSR;

	_hoops_SRCP = light->owner;

	if (!BIT (light->_hoops_RRHH, _hoops_RSPCR)) {
		if (light->direction.z != 0.0f) {
			light->_hoops_RRHH |= _hoops_RSPCR;
			if (!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_ASPCR))
				HI_Propagate_Maybes (context, _hoops_SRCP, _hoops_ASPCR);
		}
	}

	_hoops_SASIR (context, _hoops_SRCP, _hoops_AISSR|_hoops_RPSIR|_hoops_IISSR);

  Release:
	_hoops_IRRPR();
}

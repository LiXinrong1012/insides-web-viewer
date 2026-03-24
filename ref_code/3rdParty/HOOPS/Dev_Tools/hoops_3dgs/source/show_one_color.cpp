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
 * $Id: obf_tmp.txt 1.101 2010-11-18 00:59:02 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"



local const _hoops_IGRCR _hoops_IAHRS[] = {
	{M_DIFFUSE|_hoops_RHGRA,			_hoops_GRRCR ("diffuse"),			_hoops_CASAP, -1, true},
	{M_DIFFUSE,								_hoops_GRRCR ("diffuse color"),		_hoops_RRRCR, 0, true},
	{_hoops_RHGRA,						_hoops_GRRCR ("diffuse texture"),	_hoops_CASAP, -1, true},
	{M_SPECULAR|_hoops_PIARA,			_hoops_GRRCR ("specular"),			_hoops_RRRCR, 0, true},
	{M_MIRROR|_hoops_HIARA,				_hoops_GRRCR ("mirror"),			_hoops_RRRCR, 0, true},
	{M_TRANSMISSION|_hoops_IIARA,	_hoops_GRRCR ("transmission"),		_hoops_RRRCR, 0, true},
	{M_EMISSION|_hoops_CIARA,			_hoops_GRRCR ("emission"),			_hoops_RRRCR, 0, true},
	{_hoops_RAGRA,								_hoops_GRRCR ("gloss"),				_hoops_RRRCR, 0, true},
	{_hoops_AAGRA,								_hoops_GRRCR ("index"),				_hoops_RRRCR, 0, true},
	{_hoops_SIARA,						_hoops_GRRCR ("bump"),				_hoops_RRRCR, 0, true},
	{_hoops_GCARA,					_hoops_GRRCR ("environment"),		_hoops_RRRCR, 0, true},
};
local const _hoops_HPAGA _hoops_CAHRS = {
	_hoops_GGAPR (_hoops_IAHRS),	_hoops_IAHRS,
};

local const _hoops_IGRCR _hoops_SAHRS[] = {
	{Color_WINDOW,			_hoops_GRRCR ("window"),			_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_WINDOW_CONTRAST, _hoops_GRRCR ("window contrast"),	_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_FACE_CONTRAST,	_hoops_GRRCR ("face contrast"),		_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_FACE_CONTRAST,	_hoops_GRRCR ("polygon contrast"),	_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_LINE,			_hoops_GRRCR ("line"),				_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_LINE,			_hoops_GRRCR ("polyline"),			_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_MARKER,			_hoops_GRRCR ("marker only"),		_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_VERTEX,			_hoops_GRRCR ("vertex"),			_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_MARKER|Color_VERTEX,_hoops_GRRCR ("marker"),			_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_TEXT,			_hoops_GRRCR ("text"),				_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_EDGE,			_hoops_GRRCR ("edge"),				_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_FRONT,			_hoops_GRRCR ("front"),				_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_BACK,			_hoops_GRRCR ("back"),				_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_FACE,			_hoops_GRRCR ("face"),				_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_POLYGON,			_hoops_GRRCR ("polygon"),			_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_GEOMETRY,		_hoops_GRRCR ("geometry"),			_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_EVERYTHING,		_hoops_GRRCR ("everything"),		_hoops_GHAGA, -999, false,&_hoops_CAHRS},
	{_hoops_PRARA,		_hoops_GRRCR ("ambient up"),		_hoops_RRRCR, 0, true},
	{_hoops_HRARA,	_hoops_GRRCR ("ambient down"),		_hoops_RRRCR, 0, true},
	{_hoops_IRARA,		_hoops_GRRCR ("ambient"),			_hoops_RRRCR, 0, true},
	{Color_LIGHTING,		_hoops_GRRCR ("lighting"),			_hoops_RRRCR, 0, true},

	{Color_WINDOW,			_hoops_GRRCR ("windows"),			_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_LINE,			_hoops_GRRCR ("lines"),				_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_LINE,			_hoops_GRRCR ("polylines"),			_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_MARKER,			_hoops_GRRCR ("markers only"),		_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_VERTEX,			_hoops_GRRCR ("vertices"),			_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_MARKER|Color_VERTEX,_hoops_GRRCR ("markers"),		_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_EDGE,			_hoops_GRRCR ("edges"),				_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_FRONT,			_hoops_GRRCR ("fronts"),			_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_BACK,			_hoops_GRRCR ("backs"),				_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_FACE,			_hoops_GRRCR ("faces"),				_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_POLYGON,			_hoops_GRRCR ("polygons"),			_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_LIGHTING,		_hoops_GRRCR ("light"),				_hoops_RRRCR, 0, true},
	{Color_LIGHTING,		_hoops_GRRCR ("lights"),			_hoops_RRRCR, 0, true},

	{Color_EDGE_CONTRAST,	_hoops_GRRCR ("edge contrast"),		_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_LINE_CONTRAST,	_hoops_GRRCR ("line contrast"),		_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_MARKER_CONTRAST, _hoops_GRRCR ("marker contrast"),	_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_VERTEX_CONTRAST, _hoops_GRRCR ("vertex contrast"),	_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_TEXT_CONTRAST,	_hoops_GRRCR ("text contrast"),		_hoops_GHAGA, -999, true,&_hoops_CAHRS},

	{Color_CUT_GEOMETRY,	_hoops_GRRCR ("cut geometry"),		_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_CUT_FACE,		_hoops_GRRCR ("cut faces"),			_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_CUT_EDGE,		_hoops_GRRCR ("cut edges"),			_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_CUT_FACE,		_hoops_GRRCR ("cut face"),			_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{Color_CUT_EDGE,		_hoops_GRRCR ("cut edge"),			_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{_hoops_GRARA,	_hoops_GRRCR ("back contrast"),		_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{_hoops_GRARA,	_hoops_GRRCR ("back face contrast"),_hoops_GHAGA, -999, true,&_hoops_CAHRS},
	{_hoops_HGARA, _hoops_GRRCR ("cut face contrast"),_hoops_GHAGA, -999, true,&_hoops_CAHRS},
};

GLOBAL_FUNCTION Option_Value * HI_Decipher_Color_Type (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			type,
	int						_hoops_IRIAA) 
{
	
	_hoops_HIACR (_hoops_RAPPP, _hoops_SAHRS);

	Option_Value *	option;

	HI_Parse_Options (_hoops_RIGC, type, _hoops_CIACR (_hoops_RAPPP), &option, _hoops_CGPCR|_hoops_IRIAA);

	return option;
}


GLOBAL_FUNCTION Option_Value * HI_Decipher_Color_Channel (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			type,
	int						_hoops_IRIAA) 
{
	_hoops_HIACR (_hoops_HPRGI, _hoops_IAHRS);

	Option_Value	*option;

	HI_Parse_Options (_hoops_RIGC, type, _hoops_CIACR (_hoops_HPRGI),&option, _hoops_IRIAA);

	return option;
}



#ifndef DISABLE_SHOW

local void _hoops_CHGHS (
	_hoops_AIGPR *	_hoops_RIGC,
	Attribute *				_hoops_ASGPR,
	Option_Value *			option,
	char *					cname,
	int						_hoops_PCPRA) {
	Color_Object			_hoops_AGARA;
	_hoops_SSGI *					color;
	_hoops_ACSGA *			list;
	char					buf[4096];
	char					*_hoops_ASAPR = buf,
							*_hoops_PSAPR = buf+_hoops_GGAPR(buf)-1;

	if ((color = (_hoops_SSGI *)_hoops_ASGPR) == null || option == null) {
		if (option != null)
			HI_Free_Option_List (_hoops_RIGC, option);
		if (color != null)
			_hoops_HPRH (color);
		HI_Return_Chars(cname, _hoops_PCPRA, "", 0);
		return;
	}

	_hoops_AGARA = option->type->id;

	list = color->colors;
	do if (BIT (list->_hoops_GHA, _hoops_AGARA)) {
		switch (list->type) {
			case _hoops_SHGRA: {
				_hoops_PCSGA const *		findex = (_hoops_PCSGA const *)list;

				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "#%f", (void *)&findex->value);
			}	break;

			case _hoops_PPCA: {
				_hoops_APCA const *		normal = (_hoops_APCA const *)list;

				if (normal->name.length > 0)
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%n", (void *)&normal->name);
				else {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "R=%f ", (void *)&normal->rgb.red);
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "G=%f ", (void *)&normal->rgb.green);
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "B=%f",  (void *)&normal->rgb.blue);
				}
			}	break;

			case _hoops_GIGRA: {
				_hoops_HCSGA alter *		_hoops_ICSGA = (_hoops_HCSGA alter *)list;

				if (option->value.option_list != null)
					_hoops_ASAPR = HI_Show_Material (_hoops_ASAPR, _hoops_PSAPR, &_hoops_ICSGA->_hoops_ISHIR, option->value.option_list, false);
				else if (_hoops_ICSGA->name.length > 0) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%n", (void *)&_hoops_ICSGA->name);
				}
				else if (ANYBIT (_hoops_AGARA, Color_FACE|Color_EDGE|Color_VERTEX))
					_hoops_ASAPR = HI_Show_Material (_hoops_ASAPR, _hoops_PSAPR, &_hoops_ICSGA->_hoops_ISHIR, null, false);
				else {
					/* _hoops_SPI _hoops_HRGR _hoops_RH _hoops_RGAR _hoops_ICPRA _hoops_PIRA _hoops_RPP _hoops_HAR
					 * _hoops_HSP/_hoops_ISHA/_hoops_GPIA
					 */
					_hoops_ARGRA	save;

					save = _hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA;
					if (!BIT (save, M_DIFFUSE)) continue;
					_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA = M_DIFFUSE;	// _hoops_HAR _hoops_CPSA _hoops_ICIC
					_hoops_ASAPR = HI_Show_Material (_hoops_ASAPR, _hoops_PSAPR, &_hoops_ICSGA->_hoops_ISHIR, null, false);
					_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA = save;
				}
			}	break;
		}

		HI_Return_Chars (cname, _hoops_PCPRA, buf, (int)(_hoops_ASAPR - buf));

		break;
	} while ((list = list->next) != null);

	HI_Free_Option_List (_hoops_RIGC, option);
	_hoops_HPRH (color);
}

local void _hoops_SHGHS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_SSGI const *			color,
	_hoops_CPAIR *			_hoops_CICSR, /* (_hoops_CIGII _hoops_RCIC) */
	Option_Value alter *	_hoops_GIGHS,
	Option_Value alter *	_hoops_RIGHS,
	float alter *			_hoops_HPCSA,
	char alter *			_hoops_AIGHS,
	int						_hoops_PIGHS,
	char alter *			_hoops_HIGHS,
	int						_hoops_IIGHS) 
{
	Color_Object			_hoops_AGARA;
	_hoops_ACSGA *			list;
	char					buf[4096];
	char *					_hoops_ASAPR = buf;
	char *					_hoops_PSAPR = buf+_hoops_GGAPR(buf);

	if (_hoops_AIGHS)
		_hoops_AIGHS[0] = '\0';
	if (_hoops_HIGHS)
		_hoops_HIGHS[0] = '\0';
	if (_hoops_HPCSA)
		_hoops_HPCSA[0] = _hoops_HPCSA[1] = _hoops_HPCSA[2] = -1;

	if (!color || !_hoops_GIGHS) {
		if (_hoops_GIGHS)
			HI_Free_Option_List (_hoops_RIGC, _hoops_GIGHS);
		if (_hoops_RIGHS)
			HI_Free_Option_List (_hoops_RIGC, _hoops_RIGHS);
		return;
	}	

	_hoops_AGARA = _hoops_GIGHS->type->id;

	list = color->colors;
	do if (BIT (list->_hoops_GHA, _hoops_AGARA)) {
		switch (list->type) {
			case _hoops_SHGRA: {
				_hoops_PCSGA const *		findex = (_hoops_PCSGA const *)list;

				if (_hoops_HPCSA)
					*_hoops_HPCSA = findex->value;
				if (_hoops_HIGHS)
					HI_Return_Chars (_hoops_HIGHS, _hoops_IIGHS, "findex", 6);
			}	break;

			case _hoops_PPCA: {
				_hoops_APCA const *		normal = (_hoops_APCA const *)list;

				if (_hoops_HPCSA) {
					_hoops_HPCSA[0] = normal->rgb.red;
					_hoops_HPCSA[1] = normal->rgb.green;
					_hoops_HPCSA[2] = normal->rgb.blue;
				}
			}	break;

			case _hoops_GIGRA: {
				_hoops_HCSGA const *		_hoops_ICSGA = (_hoops_HCSGA const *)list;
				Named_Material const *		_hoops_ISHIR;
				int							_hoops_PHGIP = -1;
				_hoops_ARGRA			mask;

				_hoops_ISHIR = &_hoops_ICSGA->_hoops_ISHIR;
				mask = _hoops_ISHIR->_hoops_PRGRA & _hoops_RIGHS->type->id;
				if (mask == 0) {
					/*_hoops_GA'_hoops_RA _hoops_PSRHR _hoops_ARI. */
					HI_Return_Chars (_hoops_HIGHS, _hoops_IIGHS, "ignore color", 12);
					break;
				}
				if (ANYBIT (mask, M_DIFFUSE|_hoops_RHGRA)) {
					int _hoops_HGA = 0;
					_hoops_HIR *_hoops_PGC;
					_hoops_RCR *_hoops_CIGHS = null, *texture = null;
					Material_Channel_Flags flags = 0;
					_hoops_HCRPR *name = null;

					if (_hoops_RIGHS->_hoops_AIPCR > 1) {
						/* _hoops_GASA: _hoops_GPGR _hoops_SPI _hoops_GRIP _hoops_CHR _hoops_HAR _hoops_RPRI _hoops_ARI (_hoops_IH _hoops_PCAI, "_hoops_SPI = (0,1,2)") */
						HE_ERROR (HEC_COLOR, HES_BAD_VALUE, "Invalid diffuse channel");
						break;
					}
					else if (_hoops_RIGHS->_hoops_AIPCR == 1) {
						_hoops_HGA = _hoops_RIGHS->value._hoops_RIARA[0];
						/* _hoops_RPP _hoops_AIARA _hoops_IRS _hoops_SASI _hoops_RCAP, _hoops_RGAR _hoops_ARP _hoops_RH _hoops_HH, _hoops_HAR _hoops_RH _hoops_HAIR */
						mask &= ~M_DIFFUSE;
					}
					if (ALLBITS (mask, M_DIFFUSE|_hoops_RHGRA) &&
						!BIT (_hoops_ISHIR->_hoops_HRGRA, M_DIFFUSE)) {
						HE_ERROR (HEC_COLOR, HES_BAD_VALUE, 
							"request for 'diffuse' channel ambiguous, since material has "
							"both diffuse texture and diffuse color");
						break;
					}

					if (_hoops_ISHIR->_hoops_SCA) {
						if (BIT (mask, M_DIFFUSE)) {
							if (_hoops_HPCSA)
								*(RGB alter *)_hoops_HPCSA = _hoops_ISHIR->_hoops_CSHR;
							break;
						}
						/* _hoops_SHS 
						   _hoops_AGHR(_hoops_PISH == _hoops_SIGHS) */
						_hoops_PGC = _hoops_ISHIR->_hoops_SCA;
						while (_hoops_PGC) {
							if (_hoops_PGC->_hoops_HGA == _hoops_HGA) {
								if (BIT (_hoops_PGC->flags, _hoops_CCARA)) {
									texture = _hoops_PGC->texture;
									flags = _hoops_PGC->flags;
								}
								else if ((_hoops_CIGHS=HI_Activate_Texture (_hoops_PGC->texture, _hoops_CICSR, false)) != null) {
									texture = _hoops_CIGHS;
									flags = _hoops_PGC->flags;
								}
								else {
									Named_Material _hoops_GGPRA;
									ZERO_STRUCT(&_hoops_GGPRA, Named_Material);
									HI_Evaluate_Color (_hoops_RIGC, &_hoops_PGC->texture->name, &_hoops_GGPRA, _hoops_CICSR, false);
									if (_hoops_GGPRA._hoops_SCA) {
										_hoops_CIGHS = texture = _hoops_GGPRA._hoops_SCA->texture;
										/* _hoops_RPP _hoops_RH _hoops_HH _hoops_CSPGI _hoops_PAH'_hoops_RA _hoops_SHH _hoops_GSGI, _hoops_RGCI _hoops_RSIRR _hoops_GRS _hoops_SHH _hoops_GCGHS. 
										 * _hoops_SGH _hoops_RH _hoops_RSIRR _hoops_SGS _hoops_CSAP _hoops_ARP _hoops_GAR-_hoops_HRGR */
										if (_hoops_GGPRA._hoops_SCA->texture->name.length == 0)
											name = &_hoops_PGC->name;
										_hoops_PRRH (_hoops_CIGHS); /* _hoops_HIS _hoops_SCH _hoops_ASSP'_hoops_RA _hoops_RCGHS _hoops_CCA _hoops_IRPRA */
										flags = _hoops_GGPRA._hoops_SCA->flags;
										if (BIT (_hoops_GGPRA._hoops_PRGRA, M_DIFFUSE)) {
											HI_HLS_To_RGB ((_hoops_PACHR const *)&_hoops_GGPRA._hoops_CSHR, &_hoops_CIGHS->_hoops_HPIR._hoops_IPIR);
											flags |= _hoops_PRA;
											if (_hoops_HPCSA)
												*(RGB alter *)_hoops_HPCSA = texture->_hoops_HPIR._hoops_IPIR;
										}
										else
											HI_Return_Chars (_hoops_HIGHS, _hoops_IIGHS, "ignore color", 12);
									}
									else {
										texture = null;
										if (BIT (_hoops_GGPRA._hoops_PRGRA, M_DIFFUSE)) {
											if (_hoops_HPCSA)
												HI_HLS_To_RGB ((_hoops_PACHR const *)&_hoops_GGPRA._hoops_CSHR, (RGB alter *)_hoops_HPCSA);
										}
										else
											HI_Return_Chars (_hoops_HIGHS, _hoops_IIGHS, "ignore color", 12);
									}
									HI_Free_Material_Names (&_hoops_GGPRA, 1);
								}
								if (texture) {
									if (_hoops_HPCSA)
										*(RGB alter *)_hoops_HPCSA = texture->_hoops_HPIR._hoops_IPIR;
									if (_hoops_AIGHS) {
										if (!BIT(flags, _hoops_PRA) && _hoops_HIGHS)
											HI_Return_Chars (_hoops_HIGHS, _hoops_IIGHS, "ignore color", 12);
										if (name)
											_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%qn", (void *)name);
										else
											_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%qn", (void *)&texture->name);
										HI_Return_Chars (_hoops_AIGHS, _hoops_PIGHS, buf, _hoops_ASAPR-buf);
									}
								}
								if (_hoops_CIGHS)
									_hoops_HPRH (_hoops_CIGHS); /* _hoops_CGH _hoops_SHR _hoops_RIGHH _hoops_PISS */
								break;
							}
							_hoops_PGC = _hoops_PGC->next;
						}
						if (!_hoops_PGC) {
							/* _hoops_SR _hoops_RHHR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_HIGR */
							HE_ERROR (HEC_COLOR, HES_BAD_VALUE, "requested diffuse channel is not present");
							break;
						}
					}
					else {
						if (_hoops_HPCSA) {
							_hoops_HPCSA[0] = _hoops_ISHIR->_hoops_CSHR.red;
							_hoops_HPCSA[1] = _hoops_ISHIR->_hoops_CSHR.green;
							_hoops_HPCSA[2] = _hoops_ISHIR->_hoops_CSHR.blue;
						}
					}
				}
				else {
					if (ANYBIT (_hoops_RIGHS->type->id, M_SPECULAR|_hoops_PIARA))
						_hoops_PHGIP = _hoops_HIA;
					else if (ANYBIT (_hoops_RIGHS->type->id, M_MIRROR|_hoops_HIARA))
						_hoops_PHGIP = _hoops_ACA;
					else if (ANYBIT (_hoops_RIGHS->type->id, M_TRANSMISSION|_hoops_IIARA))
						_hoops_PHGIP = _hoops_PCA;
					else if (ANYBIT (_hoops_RIGHS->type->id, M_EMISSION|_hoops_CIARA))
						_hoops_PHGIP = _hoops_HCA;
					else if (BIT (_hoops_RIGHS->type->id, _hoops_SIARA))
						_hoops_PHGIP = _hoops_IIA;
					else if (BIT (_hoops_RIGHS->type->id, _hoops_GCARA))
						_hoops_PHGIP = _hoops_RIA;

					if (_hoops_HPCSA) {
						if(_hoops_PHGIP >= 0)
							*(RGB alter *)_hoops_HPCSA = _hoops_ISHIR->color[_hoops_PHGIP];
						else if(BIT (_hoops_RIGHS->type->id, _hoops_RAGRA)) {
							*_hoops_HPCSA = _hoops_ISHIR->gloss;
							break;
						}
					}
					if (_hoops_AIGHS) {
						if (_hoops_ISHIR->texture[_hoops_PHGIP]) {
							if (!BIT(_hoops_ISHIR->flags[_hoops_PHGIP], _hoops_PRA) && _hoops_HIGHS)
								HI_Return_Chars (_hoops_HIGHS, _hoops_IIGHS, "ignore color", 12);
							else if(_hoops_HPCSA) {
								*(RGB alter *)_hoops_HPCSA = _hoops_ISHIR->texture[_hoops_PHGIP]->_hoops_HPIR._hoops_IPIR;
							}

							if (_hoops_AIGHS) {
								_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%qn", (void *)&_hoops_ISHIR->texture[_hoops_PHGIP]->name);
								HI_Return_Chars (_hoops_AIGHS, _hoops_PIGHS, buf, _hoops_ASAPR-buf);
							}
						}
						else
							_hoops_AIGHS[0] = '\0'; 
					}
				}
			}	break;
		}
		break;
	} while ((list = list->next) != null);

	if (!_hoops_ASAPR)
		_hoops_SPCI(HEC_INTERNAL_ERROR, HES_DATA_ERROR, "internal buffer overrun in show_explicit_color");

	if (_hoops_RIGHS)
		HI_Free_Option_List (_hoops_RIGC, _hoops_RIGHS);
	HI_Free_Option_List (_hoops_RIGC, _hoops_GIGHS);
}



local void _hoops_ACGHS (
	_hoops_AIGPR *	_hoops_RIGC,
	Attribute *				_hoops_ASGPR,
	Option_Value *			option,
	char *					style,
	int						_hoops_GSPRA,
	float *					a,
	float *					b,
	float *					c) {
	Color_Object			_hoops_AGARA;
	_hoops_SSGI *					color;
	_hoops_ACSGA *			list;

	if ((color = (_hoops_SSGI *)_hoops_ASGPR) == null || option == null) {
		if (option != null)
			HI_Free_Option_List (_hoops_RIGC, option);
		if (color != null)
			_hoops_HPRH (color);
		*a = *b = *c =-1;
		return;
	}

	_hoops_AGARA = option->type->id;

	list = color->colors;
	do if (BIT (list->_hoops_GHA, _hoops_AGARA)) {
		switch (list->type) {
			case _hoops_SHGRA: {
				HE_ERROR (HEC_COLOR, HES_COLOR_WAS_SET_BY_INDEX, 
					Sprintf_P (null, "Color in '%p' was set \"by index\"", color->owner));
				goto done;
			}	_hoops_HHHI;

			case _hoops_PPCA: {
				_hoops_APCA const *		normal = (_hoops_APCA const *)list;

				if (option &&
					option->value.option_list &&
					!BIT (option->value.option_list->type->id, M_DIFFUSE))
					HE_WARNING (HEC_COLOR, HES_NO_DIFFUSE_COLOR_COMPONENT, "Color only has a simple diffuse value");

				if (a)
					*a = normal->rgb.red;
				if (b)
					*b = normal->rgb.green;
				if (c)
					*c = normal->rgb.blue;
			}	break;

			case _hoops_GIGRA: {
				_hoops_HCSGA const *		_hoops_ICSGA = (_hoops_HCSGA const *)list;
				int							_hoops_PHGIP = -1;
				_hoops_ARGRA			mask, _hoops_PCGHS, _hoops_HCGHS;
				int							i;
				Named_Material const *		_hoops_GASPA;

				_hoops_GASPA = &_hoops_ICSGA->_hoops_ISHIR;
				mask = _hoops_GASPA->_hoops_PRGRA;
				if (option &&
					option->value.option_list)
					mask &= option->value.option_list->type->id;

				if (mask == _hoops_RAGRA) {
					if (a)
						*a = _hoops_GASPA->gloss;
					if (b && c)
						*b = *c = -1.0f;
					break;
				}
				else if (mask == _hoops_AAGRA) {
					if (a)
						*a = _hoops_GASPA->_hoops_PAGRA;
					if (b && c)
						*b = *c = -1.0f;
					break;
				}
				else if (BIT (mask, M_DIFFUSE)) {
					if (BIT (mask, _hoops_RHGRA) && 
						_hoops_GASPA->_hoops_SCA &&
						BIT (_hoops_GASPA->_hoops_HRGRA, M_DIFFUSE)) {
						HE_ERROR2 (HEC_COLOR, HES_NO_DIFFUSE_COLOR_COMPONENT,
									"Can only show simple diffuse color 'by_value'","current setting includes a texture");
						goto done;
					}

					if (a)
						*a = _hoops_GASPA->_hoops_CSHR.red;
					if (b)
						*b = _hoops_GASPA->_hoops_CSHR.green;
					if (c)
						*c = _hoops_GASPA->_hoops_CSHR.blue;
				}
				else {
					for (i=0; i<_hoops_CRGRA; i++) {
						_hoops_PCGHS = HOOPS_READ_ONLY._hoops_SRGRA[i];
						_hoops_HCGHS = HOOPS_READ_ONLY._hoops_APGRA[i];
						if (BIT (mask, _hoops_PCGHS)) {
							if (BIT (mask, _hoops_HCGHS) &&
								_hoops_GASPA->texture[i] != null &&
								BIT (_hoops_GASPA->_hoops_HRGRA, _hoops_PCGHS)) {				
								HE_ERROR2 (HEC_COLOR, HES_NO_DIFFUSE_COLOR_COMPONENT,
											"Can only show simple color 'by_value'", "current setting includes a texture");
								goto done;
							}

							_hoops_PHGIP = i;
							break;
						}
					}
					if (_hoops_PHGIP == -1) {
						HE_ERROR2 (HEC_COLOR, HES_NO_DIFFUSE_COLOR_COMPONENT,"Can not show color 'by_value'","requested item has no setting");
						goto done;
					}
					if (a)
						*a = _hoops_GASPA->color[_hoops_PHGIP].red;
					if (b)
						*b = _hoops_GASPA->color[_hoops_PHGIP].green;
					if (c)
						*c = _hoops_GASPA->color[_hoops_PHGIP].blue;
				}
			}	break;
		}

		HI_Return_Chars (style, _hoops_GSPRA, "rgb", 3);

		break;
	} while ((list = list->next) != null);

  done:
	HI_Free_Option_List (_hoops_RIGC, option);
	_hoops_HPRH (color);
}


local void _hoops_ICGHS (
	_hoops_AIGPR *	_hoops_RIGC,
	Attribute *				_hoops_ASGPR,
	Option_Value *			option,
	int *					index) 
{
	Color_Object			_hoops_AGARA;
	_hoops_SSGI *					color;
	_hoops_ACSGA *			list;

	if ((color = (_hoops_SSGI *)_hoops_ASGPR) == null || option == null) {
		if (option != null)
			HI_Free_Option_List (_hoops_RIGC, option);
		if (color != null)
			_hoops_HPRH (color);
		*index = -1;
		return;
	}

	_hoops_AGARA = option->type->id;
	HI_Free_Option_List (_hoops_RIGC, option);

	list = color->colors;
	do if (BIT (list->_hoops_GHA, _hoops_AGARA)) {
		if (list->type != _hoops_SHGRA)
			HE_ERROR (HEC_COLOR, HES_COLOR_WAS_NOT_SET_BY_INDEX, 
				Sprintf_P (null, "Color in '%p' was not set \"by index\"", color->owner));
		else {
			_hoops_PCSGA const *	findex = (_hoops_PCSGA const *)list;

			*index = (int)findex->value;
		}

		break;
	} while ((list = list->next) != null);

	_hoops_HPRH (color);
}
#endif



HC_INTERFACE void HC_CDECL HC_Show_One_Color (
	char const *	type,
	char *			cname) 
{
	_hoops_PAPPR context("Show_One_Color");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_One_Color () */\n");
	);

	Option_Value *	opt = HI_Decipher_Color_Type (context, type, _hoops_PAPCA);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_ISPRA)) != null) {

		_hoops_CHGHS (context, HI_Find_Attribute (context, target, HK_COLOR), opt, cname, -1);
		_hoops_IRRPR();
	}
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_One_Color_By_Index (
	char const *	type,
	int *			index) 
{
	_hoops_PAPPR context("Show_One_Color_By_Index");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_One_Color_By_Index () */\n");
	);

	Option_Value *	opt = HI_Decipher_Color_Type (context, type, _hoops_PAPCA);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_ISPRA)) != null) {

		_hoops_ICGHS (context, HI_Find_Attribute (context, target, HK_COLOR), opt, index);
		_hoops_IRRPR();
	}
#endif
}

HC_INTERFACE void HC_CDECL HC_Show_One_Color_By_Value (
	char const *	type,
	char *			style,
	float *			a,
	float *			b,
	float *			c) 
{
	_hoops_PAPPR context("Show_One_Color_By_Value");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_One_Color_By_Value () */\n");
	);

	Option_Value *	opt = HI_Decipher_Color_Type (context, type, _hoops_PAPCA);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_ISPRA)) != null) {

		_hoops_ACGHS (context, HI_Find_Attribute (context, target, HK_COLOR), opt, style, -1, a, b, c);
		_hoops_IRRPR();
	}
#endif
}


#ifndef _hoops_ARPCR

HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Color (
	int				count,
	Key const *		keys,
	char const *	type,
	char *			cname) 
{
	_hoops_PAPPR context("PShow_One_Net_Color");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_One_Net_Color () */\n");
	);

	_hoops_SSGI *	color;
	if ((color = (_hoops_SSGI *) HI_Find_Attribute_And_Lock(context, _hoops_ISPRA, _hoops_HRPCR, count, keys)) != null) {
		Option_Value *	opt = HI_Decipher_Color_Type (context, type, _hoops_PAPCA);
		_hoops_CHGHS (context, color, opt, cname, -1);
		_hoops_IRRPR();
	}
#endif
}
#endif

#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Color_By_Index (
	int				count,
	Key const *		keys,
	char const *	type,
	int *			index) 
{
	_hoops_PAPPR context("PShow_One_Net_Color_By_Index");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_One_Net_Color_By_Index () */\n");
	);

	_hoops_SSGI *	color;
	if ((color = (_hoops_SSGI *) HI_Find_Attribute_And_Lock(context, _hoops_ISPRA, _hoops_HRPCR, count, keys)) != null) {
		Option_Value *	opt = HI_Decipher_Color_Type (context, type, _hoops_PAPCA);
		_hoops_ICGHS (context, color, opt, index);
		_hoops_IRRPR();
	}
#endif
}
#endif


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Color_By_Value (
	int				count,
	Key const *		keys,
	char const *	type,
	char *			style,
	float *			a,
	float *			b,
	float *			c) 
{
	_hoops_PAPPR context("PShow_One_Net_Color_By_Value");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_One_Net_Color_By_Value () */\n");
	);

	_hoops_SSGI *	color;
	if ((color = (_hoops_SSGI *) HI_Find_Attribute_And_Lock(context, _hoops_ISPRA, _hoops_HRPCR, count, keys)) != null) {
		Option_Value *	opt = HI_Decipher_Color_Type (context, type, _hoops_PAPCA);
		_hoops_ACGHS (context, color, opt, style, -1, a, b, c);
		_hoops_IRRPR();
	}
#endif
}
#endif



HC_INTERFACE void HC_CDECL HC_Show_Explicit_Color (
	char const *	type,
	char const *	channel,
	float alter *	rgb,
	char alter *	texture,
	char alter *	options) 
{
	_hoops_PAPPR context("Show_Explicit_Color");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Explicit_Color */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_ISPRA)) != null) {

		_hoops_CRCP const *	_hoops_CCGHS[2];
		int				count = 1;

		_hoops_CCGHS[0] = _hoops_RSPPR(context, _hoops_RPGHP);

		if (target->type == _hoops_CIRIR) {

			_hoops_SIRIR const * _hoops_ASIIR = (_hoops_SIRIR *)target;

			switch (_hoops_ASIIR->_hoops_GCRIR) {

				case _hoops_RCRIR: {
					_hoops_CCGHS[1] = (_hoops_CRCP const *)_hoops_ASIIR->info.segment._hoops_IGRPR;
					count++;
				}	break;

				case _hoops_HCRIR: {
					_hoops_CCGHS[1] = (_hoops_CRCP const *)_hoops_ASIIR->info.geometry._hoops_IGRPR->owner;
					count++;
				}	break;

				default: {
					count = 0; // _hoops_HSGR _hoops_SCGHS
				}	break;
			}
		}
		else if (target->type == _hoops_IRCP) {
			_hoops_CCGHS[1] = (_hoops_CRCP const *)target;
			count++;
		}
		else {
			_hoops_CCGHS[1] = (_hoops_CRCP const *)target->owner;
			count++;
		}

		_hoops_CPAIR *	_hoops_CICSR = null;

		if (count > 0)
			_hoops_CICSR = (_hoops_CPAIR *)HI_Find_Net_Attribute_By_Path (context, count, _hoops_CCGHS, _hoops_IPAIR);
	
		_hoops_SSGI *		color = (_hoops_SSGI * )HI_Find_Attribute (context, target, HK_COLOR);

		Option_Value *	_hoops_GIGHS = HI_Decipher_Color_Type (context, type, _hoops_PAPCA);

		Option_Value *	_hoops_RIGHS = HI_Decipher_Color_Channel (context, channel, _hoops_PAPCA);

		_hoops_SHGHS(context, color, _hoops_CICSR, _hoops_GIGHS, _hoops_RIGHS, rgb, texture, -1, options, -1);

		if (_hoops_CICSR)
			_hoops_HPRH (_hoops_CICSR);

		_hoops_HPRH (color);

		_hoops_IRRPR();
	}
}


HC_INTERFACE void HC_CDECL HC_PShow_Net_Explicit_Color (
	int				count,
	Key const *		keys,
	char const *	type,
	char const *	channel,
	float alter *	rgb,
	char alter *	texture,
	char alter *	options) 
{
	_hoops_PAPPR context("PShow_Net_Explicit_Color");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Explicit_Color */\n");
	);

	_hoops_CRACA	control;
	ZERO_STRUCT (&control, _hoops_CRACA);

	_hoops_SSGI *	color;
	if ((color = (_hoops_SSGI *)HI_Find_Attribute_And_Lock(context, _hoops_ISPRA, _hoops_ISCAP|_hoops_HRPCR, count, keys, null, &control)) != null) {

		_hoops_CPAIR *	_hoops_CICSR = (_hoops_CPAIR *)HI_Find_Attribute_And_Lock(context, _hoops_SSRPP|_hoops_SRGPP, _hoops_HRPCR|_hoops_CSCAP, count, keys);

		Option_Value *	_hoops_GIGHS = HI_Decipher_Color_Type (context, type, _hoops_PAPCA);
		Option_Value *	_hoops_RIGHS = HI_Decipher_Color_Channel (context, channel, _hoops_PAPCA);

		_hoops_SHGHS(context, color, _hoops_CICSR, _hoops_GIGHS, _hoops_RIGHS, rgb, texture, -1, options, -1);

		if (_hoops_CICSR)
			_hoops_HPRH (_hoops_CICSR);

		_hoops_HPRH (color);

		_hoops_IRRPR();
	}
	else {
		rgb[0]=rgb[1]=rgb[2]=-1;
		HI_Return_Chars(texture, -1, "", 0);
		HI_Return_Chars(options, -1, "", 0);
	}

}



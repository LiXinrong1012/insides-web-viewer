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
 * $Id: obf_tmp.txt 1.183 2010-11-30 22:36:13 heppe Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "please.h"

struct _hoops_SPCIH {
	Point				where;
	int					width, height;
	void const *		_hoops_SHGGR;
	int					type;
	Image *				image;
	int					_hoops_IGSSR;

	Option_Value *		option_list;
	Option_Value *		_hoops_CAGPI;

	_hoops_HCRPR				name; /*_hoops_PCSA _hoops_IS _hoops_CIH _hoops_RGR*/
	Image_Format		format;
	bool 				_hoops_RIRRP;
	bool 				_hoops_AIRRP;
	bool 				texture;
	_hoops_HCAIR 		_hoops_PIRRP;
	_hoops_HCAIR 		_hoops_HIRRP;
	bool				_hoops_IIRRP;

	bool				_hoops_SAGPI;
	bool				_hoops_GPGPI;
	bool				_hoops_RPGPI;
	bool				_hoops_APGPI;
	bool				_hoops_PPGPI;
	bool 				_hoops_HPGPI;
	bool				_hoops_IPGPI;
	float				_hoops_SSRRP;

	bool				_hoops_CPGPI;
	bool				_hoops_SPGPI;
	int					_hoops_IARH;
};

local void _hoops_GHGPI(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				owner,
	_hoops_SPCIH *		data, 
	Image *					image) {

	if (data->_hoops_GPGPI) {
		if (!data->_hoops_IIRRP) 
			image->flags |= _hoops_GICC;
		else
			image->flags &= ~_hoops_GICC;
	}
	if (data->_hoops_RPGPI)
		image->flags |= _hoops_GPAH;
	else
		image->flags &= ~_hoops_GPAH;

	if (data->_hoops_SSRRP < 1.0f)
		image->flags |= _hoops_HAAH;
	image->_hoops_SSRRP = data->_hoops_SSRRP;

	if (data->_hoops_APGPI) {
		image->_hoops_PIRRP.value = data->_hoops_PIRRP.value;
		image->_hoops_PIRRP._hoops_HHP = data->_hoops_PIRRP._hoops_HHP;

		image->_hoops_HIRRP.value = data->_hoops_HIRRP.value;
		image->_hoops_HIRRP._hoops_HHP = data->_hoops_HIRRP._hoops_HHP;
	}

#ifndef DISABLE_TEXTURING

	if (data->_hoops_PPGPI || 
		data->_hoops_HPGPI || 
		data->_hoops_IPGPI|| 
		data->_hoops_SAGPI) {

		/* _hoops_RPP _hoops_RGR _hoops_CSCR _hoops_SSCP _hoops_IRS _hoops_CHHA _hoops_HH _hoops_HSCI _hoops_SCH */
		if (image->texture) {

			if(!data->_hoops_SAGPI) {
				// _hoops_GRHP _hoops_RH _hoops_RHGS _hoops_RSIRR
				HI_Copy_Name (&image->texture->name, &data->name);
			}

			char definition[4096];

			HI_Show_Texture (_hoops_RIGC, image->texture, definition, -1, null, 0, false, 0);

			if (definition[0] != '\0') {
				Option_Value *		option;

				if (HI_Parse_Options (_hoops_RIGC, definition, _hoops_CIACR (_hoops_CPRGI),
					&option, _hoops_CGPCR|_hoops_PAPCA)) {
					
					Option_Value *end = option;

					while(end->next != null)
						end = end->next;

					end->next = data->_hoops_CAGPI; 
					data->_hoops_CAGPI = option;
				}
			}

			_hoops_RPPPR();
			HI_UnDefine_Texture(_hoops_RIGC, image->texture);
			_hoops_IRRPR();

			/* _hoops_AHHHH, _hoops_SR _hoops_CPSA _hoops_AA _hoops_RRP _hoops_RGR _hoops_ISPR */
			if (image->texture) {
				_hoops_HPRH (image->texture);
				image->texture = null;
			}
		}
	}

	if (data->name.length > 0) {

		_hoops_RGAIR(image->name);
		HI_Copy_Name (&data->name, &image->name);

		if(data->texture) {

			if (data->_hoops_AIRRP) {
				_hoops_CRCP		*_hoops_SRCP = null;

				if (owner->type == _hoops_IRCP) {
					_hoops_SRCP = (_hoops_CRCP *) owner;
				}
				else if (owner->type == _hoops_CIRIR) {
					_hoops_SIRIR *	open_list = (_hoops_SIRIR *)owner;

					if (open_list->_hoops_GCRIR == _hoops_RCRIR) {
						_hoops_SRCP = open_list->info.segment._hoops_IGRPR;
					}
					else {
						HE_ERROR (HEC_IMAGE, HES_NO_OPEN_SEGMENT, 
								"Local Textures require open segment");
						return;
					}
				}
				else {
					HE_ERROR (HEC_SYSTEM, HES_INVALID_TYPE,
						"Unknown open type.	 System may have corrupted memory.");
					return;
				}

HOOPS_WORLD->_hoops_RCHGI=1;
				_hoops_RPPPR();
HOOPS_WORLD->_hoops_RCHGI=0;
				HI_Define_Implicit_Texture(_hoops_RIGC, _hoops_SRCP, image, data->_hoops_CAGPI);
				_hoops_IRRPR();
			}
			else {

HOOPS_WORLD->_hoops_RCHGI=1;
				_hoops_RPPPR();
HOOPS_WORLD->_hoops_RCHGI=0;
				HI_Define_Implicit_Texture(_hoops_RIGC, _hoops_RSPPR(_hoops_RIGC, _hoops_RPGHP), image, data->_hoops_CAGPI);
				_hoops_IRRPR();
			}
		}
	}
#endif

}

local void _hoops_RHGPI (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				owner,
	_hoops_SPCIH *		data) 
{
	if (data->_hoops_SHGGR == null) 
		data->type = _hoops_HGPGI;

	if ((data->format == _hoops_GGRH || data->format == _hoops_RGRH || data->format == _hoops_AGRH) && 
		(data->width < 1 || data->height < 1)) {
		if (data->format == _hoops_GGRH) {
			if (!HI_Query_PNG_Dimensions (data->_hoops_IARH, data->_hoops_SHGGR, &data->width, &data->height)) {
				HE_ERROR (HEC_IMAGE, HES_INVALID_ENCODING, "Invalid PNG data");
				return;
			}
		}
		else if (data->format == _hoops_RGRH) {
			if (!HI_Query_JPEG_Dimensions (data->_hoops_IARH, data->_hoops_SHGGR, &data->width, &data->height)) {
				HE_ERROR (HEC_IMAGE, HES_INVALID_ENCODING, "Invalid JPEG data");
				return;
			}
			if (data->_hoops_RPGPI) {
				HE_WARNING (HEC_IMAGE, HES_INVALID_OPTION, "'discard' image option ignored for jpeg");
			}
		}
		else if (data->format == _hoops_AGRH) {
			if (!HI_Query_TARGA_Dimensions (data->_hoops_IARH, data->_hoops_SHGGR, &data->width, &data->height)) {
				HE_ERROR (HEC_IMAGE, HES_INVALID_ENCODING, "Invalid TARGA data");
				return;
			}
		}
	}

	Image *	image;

	HI_Create_Image (&image,
					 &data->where,
					 data->width, data->height,
					 data->format, 0,
					 data->type, 
					 (unsigned char *)data->_hoops_SHGGR);

	if (data->_hoops_SPGPI) {
		void *_hoops_PHGH;
		image->_hoops_IARH = data->_hoops_IARH;
		ALLOC_ARRAY (_hoops_PHGH, (long)image->_hoops_IARH, char);
		COPY_MEMORY (data->_hoops_SHGGR, image->_hoops_IARH, _hoops_PHGH);
		image->_hoops_PHGH = _hoops_PHGH;
		image->flags |= (_hoops_HHRH | _hoops_SSGH);

		if (data->format == _hoops_GGRH) {
			if (HI_PNG_Check_Transparency (image)) {
				image->flags |= _hoops_SHCC;			
				HOOPS_WORLD->_hoops_ACPIR++;
			}
		}
		if (data->format == _hoops_AGRH) {
			if (HI_TARGA_Check_Transparency (image)) {
				image->flags |= _hoops_SHCC;			
				HOOPS_WORLD->_hoops_ACPIR++;
			}
		}
		if (data->format == _hoops_CRRH ||
			data->format == _hoops_SRRH) {
			if (HI_DXT_Check_Transparency (image)) {
				image->flags |= _hoops_SHCC;			
				HOOPS_WORLD->_hoops_ACPIR++;
			}
		}

	}

	if (image == null)
		return;

	HI_Insert_Geometry (_hoops_RIGC, owner, (Geometry *)image,
						image->_hoops_CSAI.z == 0.0f,
						_hoops_IHSSR);

	data->image = image;
	++data->_hoops_IGSSR;

	_hoops_GHGPI(_hoops_RIGC, owner, data, image);
}

local void _hoops_AHGPI (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_SPCIH *		data) {

	_hoops_RGAIR (data->name);

	if (data->option_list) 
		HI_Free_Option_List (_hoops_RIGC, data->option_list);

	if (data->_hoops_CAGPI && !data->_hoops_IPGPI) 
		HI_Free_Option_List (_hoops_RIGC, data->_hoops_CAGPI);
}


GLOBAL_FUNCTION Key HI_Insert_Image (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPAH *					item,
	Point const *				where,
	char const *				format,
	int							width,
	int							height,
	int							size,
	void const *				_hoops_SHGGR,
	bool						_hoops_PSSIH) 
{	
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_SPCIH	data;

	if (HI_Determine_Image_Format (_hoops_RIGC, format, &data)) {

		bool _hoops_PHGPI = true;

		if (size > 0) {

			data._hoops_SPGPI = true;
			data._hoops_IARH = size;

			if (data.format != _hoops_GGRH &&
				data.format != _hoops_RGRH &&
				data.format != _hoops_AGRH &&
				(width < 1 || height < 1)) {
				HE_ERROR (HEC_IMAGE, HES_INVALID_WIDTH_OR_HEIGHT, "Width or height is less than 1");
				_hoops_PHGPI = false;
			}
		}
		else {

			if (data.format == _hoops_GGRH ||
				data.format == _hoops_RGRH ||
				data.format == _hoops_AGRH ||
				data.format == _hoops_IRRH ||
				data.format == _hoops_CRRH ||
				data.format == _hoops_SRRH) {
				HE_ERROR (HEC_IMAGE, HES_INVALID_ENCODING, "Compressed image insert mismatched");
				_hoops_PHGPI = false;
			}
		}
#ifdef _hoops_AASSH
		if (data.format == _hoops_GGRH) {
			_hoops_IRPPR ("png");
			_hoops_PHGPI = false;
		}
#endif
#ifdef _hoops_RASSH
		if (data.format == _hoops_RGRH) {
			_hoops_IRPPR ("jpeg");
			_hoops_PHGPI = false;
		}
#endif

		if (_hoops_PHGPI) {
			data.where = *where;	  
			data.width = width;		 
			data.height = height;
			data._hoops_SHGGR = data._hoops_RIRRP ? _hoops_SHGGR : null;
			if (_hoops_PSSIH)
				data.type = _hoops_IGPGI;
			else
				data.type = _hoops_HGPGI;
			data._hoops_IGSSR = 0;
			_hoops_RHGPI (_hoops_RIGC, item, &data);
		}
	}

	Key	_hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data.image);

	_hoops_AHGPI (_hoops_RIGC, &data);

	return	_hoops_CHSSR;
}


HC_INTERFACE Key HC_CDECL HC_Insert_Image (
	double						x,
	double						y,
	double						z,
	char const *				format,
	int							width,
	int							height,
	void const *				_hoops_SHGGR) 
{	
	_hoops_PAPPR context("Insert_Image");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Insert_Image */\n");
	);

	if (width < 1 || height < 1) {
		HE_ERROR (HEC_IMAGE, HES_INVALID_WIDTH_OR_HEIGHT, "Width or height is less than 1");
		return _hoops_SHSSR;
	}

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;
	Point where(x, y, z);

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Image (context, target, &where, format, width, height, 0, _hoops_SHGGR, false);
		_hoops_IRRPR();
	}

	return	_hoops_CHSSR;
}


HC_INTERFACE Key HC_CDECL HC_Insert_Compressed_Image (
	double						x,
	double						y,
	double						z,
	char const *				format,
	int							width,
	int							height,
	int							size,
	void const *				_hoops_SHGGR) 
{
	_hoops_PAPPR context("Insert_Compressed_Image");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Insert_Compressed_Image */\n");
	);

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;
	Point where(x, y, z);

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Image (context, target, &where, format, width, height, size, _hoops_SHGGR, false);
		_hoops_IRRPR();
	}

	return	_hoops_CHSSR;
}


HC_INTERFACE Key HC_CDECL HC_Insert_Image_By_Ref (
	double						x,
	double						y,
	double						z,
	char const *				format,
	int							width,
	int							height,
	void const *				_hoops_SHGGR) 
{
	_hoops_PAPPR context("Insert_Image_By_Ref");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Insert_Image_By_Ref */\n");
	);

	if (width < 1 || height < 1) {
		HE_ERROR (HEC_IMAGE, HES_INVALID_WIDTH_OR_HEIGHT, "Width or height is less than 1");
		return _hoops_SHSSR;
	}

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;
	Point where(x, y, z);

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Image (context, target, &where, format, width, height, 0, _hoops_SHGGR, true);
		_hoops_IRRPR();
	}

	return	_hoops_CHSSR;
}




GLOBAL_FUNCTION Key HI_Insert_Image_By_Row (
	_hoops_AIGPR *		_hoops_RIGC,
	float						x,
	float						y,
	float						z,
	char const *				format,
	int							width,
	int							height,
	void **						_hoops_PICIH) 
{
	_hoops_SPCIH				data;
	Key							_hoops_CHSSR = _hoops_SHSSR;

	if (width < 1 || height < 1) {
		HE_ERROR (HEC_IMAGE, HES_INVALID_WIDTH_OR_HEIGHT, "Width or height is less than 1");
		return _hoops_SHSSR;
	}


	if (HI_Determine_Image_Format (_hoops_RIGC, format, &data)) {
		data.where = Point(x,y,z);
		data.width = width;		
		data.height = height;
		data._hoops_SHGGR = (void *)_hoops_PICIH;
		data.type = _hoops_CGPGI;
		data._hoops_IGSSR = 0;

		if (HI_Find_Target_And_Lock(_hoops_RIGC, _hoops_GISSR)) {
			_hoops_RHGPI  (_hoops_RIGC, (_hoops_HPAH *)_hoops_RIGC->open_list, &data);
			_hoops_IRRPR();
		}

		if (data._hoops_IGSSR != 1) {
			if (data._hoops_IGSSR > 1)
				HE_WARNING (HEC_IMAGE, HES_BAD_RETURN_KEY, 
				"Image inserted in multiple segments, no key returned");
			/* _hoops_RPP _hoops_SCH _hoops_HRGR 0 _hoops_RH _hoops_RH _hoops_RIHH _hoops_HRGR _hoops_AIAH _hoops_RPII _hoops_RAGA */
		}
		else
			_hoops_CHSSR = _hoops_AIRIR (data.image);
	}

	_hoops_AHGPI (_hoops_RIGC, &data);

	return _hoops_CHSSR;
}

local const _hoops_IGRCR _hoops_AHSIA[] = {
	{GSU_ORU,			_hoops_GRRCR ("oru"),			_hoops_RRRCR, 0, false},
	{GSU_SRU,			_hoops_GRRCR ("sru"),			_hoops_RRRCR, 0, false},
	{GSU_WRU,			_hoops_GRRCR ("wru"),			_hoops_RRRCR, 0, false},
	{_hoops_SPSC,			_hoops_GRRCR ("wsu"),			_hoops_RRRCR, 0, false},
	{_hoops_SPSC,			_hoops_GRRCR ("world"),			_hoops_RRRCR, 0, false},
	{GSU_PIXELS,		_hoops_GRRCR ("pixels"),		_hoops_RRRCR, 0, false},
	{GSU_PIXELS,		_hoops_GRRCR ("pixel"),			_hoops_RRRCR, 0, false},
	{GSU_PIXELS,		_hoops_GRRCR ("pxl"),			_hoops_RRRCR, 0, false},
	{GSU_PIXELS,		_hoops_GRRCR ("px"),			_hoops_RRRCR, 0, false},
	{GSU_POINTS,		_hoops_GRRCR ("points"),		_hoops_RRRCR, 0, false},
	{GSU_POINTS,		_hoops_GRRCR ("point"),			_hoops_RRRCR, 0, false},
	{GSU_POINTS,		_hoops_GRRCR ("pts"),			_hoops_RRRCR, 0, false},
	{GSU_POINTS,		_hoops_GRRCR ("pt"),			_hoops_RRRCR, 0, false},
	{GSU_PERCENT,		_hoops_GRRCR ("%"),				_hoops_RRRCR, 0, false},
	{GSU_SCALE,			_hoops_GRRCR (""),				_hoops_RRRCR, 0, false},
};

/* _hoops_GIGHR: _hoops_IGIR _hoops_GHCA _hoops_HAR _hoops_SHH "%", _hoops_HIS _hoops_HSGR _hoops_SRS _hoops_RARP _hoops_GGR _hoops_GASR */
local const _hoops_HPAGA _hoops_PHSIA = {
		_hoops_GGAPR (_hoops_AHSIA),		&_hoops_AHSIA[0],
};

/* _hoops_HSGS _hoops_HSH _hoops_IH _hoops_GASR */
#define _hoops_HHGPI				-1
#define _hoops_IHGPI				-2
#define _hoops_CHGPI				-3
#define _hoops_SHGPI			-4
#define _hoops_GIGPI				-5
#define _hoops_RIGPI				-6
#define _hoops_AIGPI			-7
#define _hoops_PIGPI			-8
#define _hoops_HIGPI		-9
#define _hoops_IIGPI	-10
#define _hoops_CIGPI			-11
#define _hoops_SIGPI -12

local const _hoops_IGRCR _hoops_GCGPI[] = {
	{Image_MAPPED_8,		_hoops_GRRCR ("mapped"),		_hoops_RRRCR, 0, false},
	{Image_MAPPED_8,		_hoops_GRRCR ("mapped 8"),		_hoops_RRRCR, 0, false},
	{Image_MAPPED_16,		_hoops_GRRCR ("mapped 16"),		_hoops_RRRCR, 0, false},
	{_hoops_HHGH,			_hoops_GRRCR ("rgb"),			_hoops_RRRCR, 0, false},
	{Image_RGBA32,			_hoops_GRRCR ("rgba"),			_hoops_RRRCR, 0, false},
	{_hoops_HRSRH,			_hoops_GRRCR ("argb"),			_hoops_RRRCR, 0, false},
	{_hoops_PCCRH,	_hoops_GRRCR ("depth"),			_hoops_RRRCR, 0, false},
	{_hoops_HHGPI,			_hoops_GRRCR ("name"),			_hoops_PRRCR, 1, true},
	{_hoops_IHGPI,			_hoops_GRRCR ("data"),			_hoops_RRRCR, 0, true},
	{_hoops_CHGPI,			_hoops_GRRCR ("local"),			_hoops_RRRCR, 0, true},
	{_hoops_SHGPI,			_hoops_GRRCR ("texture"),		_hoops_RRRCR, 0, true},
	{_hoops_GIGPI,			_hoops_GRRCR ("size"),			_hoops_CIGHA, -2, false, &_hoops_PHSIA},
	{_hoops_HIGPI,		_hoops_GRRCR ("down sample"),	_hoops_RRRCR,  0, true},
	{_hoops_HIGPI,		_hoops_GRRCR ("down sampling"),	_hoops_RRRCR,  0, true},
	{_hoops_HIGPI,		_hoops_GRRCR ("downsample"),	_hoops_RRRCR,  0, true},
	{_hoops_HIGPI,		_hoops_GRRCR ("downsampling"),	_hoops_RRRCR,  0, true},
	{_hoops_HIGPI,		_hoops_GRRCR ("down-sample"),	_hoops_RRRCR,  0, true},
	{_hoops_HIGPI,		_hoops_GRRCR ("down-sampling"),	_hoops_RRRCR,  0, true},
	{_hoops_CIGPI,			_hoops_GRRCR ("discard"),		_hoops_RRRCR, 0, true},
	{_hoops_SIGPI, _hoops_GRRCR ("compression quality"), _hoops_SPPCR, 1, false},
	{_hoops_IRRH,			_hoops_GRRCR ("dxt1"),			_hoops_RRRCR, 0, false},
	{_hoops_CRRH,			_hoops_GRRCR ("dxt3"),			_hoops_RRRCR, 0, false},
	{_hoops_SRRH,			_hoops_GRRCR ("dxt5"),			_hoops_RRRCR, 0, false},
	{_hoops_GGRH,				_hoops_GRRCR ("png"),			_hoops_RRRCR, 0, false},
	{_hoops_RGRH,			_hoops_GRRCR ("jpeg"),			_hoops_RRRCR, 0, false},
	{_hoops_RGRH,			_hoops_GRRCR ("jpg"),			_hoops_RRRCR, 0, false},
	{_hoops_AGRH,			_hoops_GRRCR ("tga"),			_hoops_RRRCR, 0, false},
	{_hoops_AGRH,			_hoops_GRRCR ("targa"),			_hoops_RRRCR, 0, false},
	{_hoops_AHGH,		_hoops_GRRCR ("grayscale"),		_hoops_RRRCR, 0, false},
	{_hoops_AHGH,		_hoops_GRRCR ("greyscale"),		_hoops_RRRCR, 0, false},
	{_hoops_AHGH,		_hoops_GRRCR ("gray scale"),	_hoops_RRRCR, 0, false},
	{_hoops_AHGH,		_hoops_GRRCR ("grey scale"),	_hoops_RRRCR, 0, false},
	{_hoops_AHGH,		_hoops_GRRCR ("luminanace"),	_hoops_RRRCR, 0, false},
};

GLOBAL_FUNCTION Image_Format HI_Determine_Image_Format (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			format,
	void *					_hoops_RCGPI) 
{ 
	_hoops_SPCIH *		_hoops_ACGPI = (_hoops_SPCIH *)_hoops_RCGPI;
	_hoops_SPCIH			_hoops_PCGPI;
	Option_Value *			option;

	if (!_hoops_RCGPI) 
		_hoops_ACGPI = &_hoops_PCGPI;

	ZERO_STRUCT(_hoops_ACGPI, _hoops_SPCIH);

	_hoops_ACGPI->_hoops_RIRRP = true;
	_hoops_ACGPI->texture = true;
	_hoops_ACGPI->_hoops_IIRRP = true;
	_hoops_ACGPI->_hoops_SSRRP = 1.0f;

	_hoops_CAAI (HOOPS_WORLD->_hoops_HPSAP);
	if (_hoops_CIACR (_hoops_AHRGI)->table == null) {
		_hoops_HIACR (_hoops_AHRGI, _hoops_GCGPI);
		// _hoops_GGGRA _hoops_GGR _hoops_HH _hoops_AAP _hoops_GAR _hoops_IRS _hoops_RGSAP _hoops_ARI
		_hoops_PIIIR *		_hoops_SPSAA;
		_hoops_SRHSR			texture_name = _hoops_GRRCR ("texture options");

		HI_Init_Texture_Options();

		_hoops_SPSAA = HI_Define_Nice_Option (_hoops_CIACR (_hoops_AHRGI),
									(long)_hoops_IIGPI, (_hoops_HCRPR const *)&texture_name,
								   _hoops_GHAGA, -999, true, _hoops_CIACR (_hoops_CPRGI));

		_hoops_SPSAA->_hoops_RRHH |= _hoops_SIIIR;
	}
	_hoops_APAI (HOOPS_WORLD->_hoops_HPSAP);

	if (!HI_Parse_Options (_hoops_RIGC, format, _hoops_CIACR (_hoops_AHRGI),
						   &_hoops_ACGPI->option_list, _hoops_SIACR))
		return _hoops_CAHPA;


	if ((option = _hoops_ACGPI->option_list) != null) do {
		switch (option->type->id) {
			case _hoops_HHGPI: {
				if (!option->_hoops_GCACR)
					HI_Copy_Name (&option->value._name[0], &_hoops_ACGPI->name);
				_hoops_ACGPI->_hoops_SAGPI=true;
			}	break;

			case _hoops_IHGPI: {
				_hoops_ACGPI->_hoops_RIRRP = !option->_hoops_GCACR;
				_hoops_ACGPI->_hoops_CPGPI = true;
			}	break;

			case _hoops_CHGPI: {
				_hoops_ACGPI->_hoops_AIRRP = !option->_hoops_GCACR;
				_hoops_ACGPI->_hoops_PPGPI=true;
			}	break;

			case _hoops_SHGPI: {
				_hoops_ACGPI->texture = !option->_hoops_GCACR;
				_hoops_ACGPI->_hoops_HPGPI=true;
			}	break;

			case _hoops_GIGPI: {
				switch (option->_hoops_AIPCR) {
					case 0: {
						HE_ERROR (HEC_IMAGE, HES_INVALID_SIZE, "Image size requires 1 or 2 values");
					}	break;

					case 1: {
						_hoops_ACGPI->_hoops_PIRRP.value = option->value._hoops_RRRHA[0].value;
						_hoops_ACGPI->_hoops_PIRRP._hoops_HHP = (_hoops_SPGRP) option->value._hoops_RRRHA[0]._hoops_HHP;
						_hoops_ACGPI->_hoops_HIRRP.value = option->value._hoops_RRRHA[0].value;
						_hoops_ACGPI->_hoops_HIRRP._hoops_HHP = (_hoops_SPGRP) option->value._hoops_RRRHA[0]._hoops_HHP;
						if (_hoops_ACGPI->_hoops_HIRRP.value <= 0.0f) {
							HE_ERROR (HEC_IMAGE, HES_INVALID_SIZE, "Image size must be positive");
						}
						else
							_hoops_ACGPI->_hoops_APGPI=true;
					}	break;

					case 2: {
						_hoops_ACGPI->_hoops_PIRRP.value = option->value._hoops_RRRHA[0].value;
						_hoops_ACGPI->_hoops_PIRRP._hoops_HHP = (_hoops_SPGRP) option->value._hoops_RRRHA[0]._hoops_HHP;
						_hoops_ACGPI->_hoops_HIRRP.value = option->value._hoops_RRRHA[1].value;
						_hoops_ACGPI->_hoops_HIRRP._hoops_HHP = (_hoops_SPGRP) option->value._hoops_RRRHA[1]._hoops_HHP;
						if (_hoops_ACGPI->_hoops_PIRRP.value <= 0.0f ||
							_hoops_ACGPI->_hoops_HIRRP.value <= 0.0f) {
							HE_ERROR (HEC_IMAGE, HES_INVALID_SIZE, "Image size must be positive");
						}
						else
							_hoops_ACGPI->_hoops_APGPI=true;
					}	break;
					
				}
			}	break;

			case _hoops_PCCRH:
			case _hoops_AHGH:
			case Image_MAPPED_8:
			case Image_MAPPED_16:
			case _hoops_HHGH:
			case Image_RGBA32:
			case _hoops_HRSRH:
			case _hoops_IRRH:
			case _hoops_CRRH:
			case _hoops_SRRH: 
			case _hoops_GGRH: 
			case _hoops_RGRH:  
			case _hoops_AGRH:{
				_hoops_ACGPI->format = (Image_Format)option->type->id;
				_hoops_ACGPI->_hoops_CPGPI = true;
			}	break;

			case _hoops_HIGPI:{
				_hoops_ACGPI->_hoops_IIRRP = !option->_hoops_GCACR;
				_hoops_ACGPI->_hoops_GPGPI=true;
			}	break;

			case _hoops_CIGPI:{
				_hoops_ACGPI->_hoops_IIRRP = !option->_hoops_GCACR;
				_hoops_ACGPI->_hoops_RPGPI = true;
			}	break;

			case _hoops_IIGPI:{
				_hoops_ACGPI->_hoops_CAGPI = option->value.option_list;
				_hoops_ACGPI->_hoops_IPGPI=true;
			}	break;


			case _hoops_SIGPI: {
				if (option->_hoops_AIPCR != 1) {
					HE_ERROR (HEC_IMAGE, HES_INVALID_SIZE, "Image compression quality requires exactly 1 value.");
					break;
				}
				_hoops_ACGPI->_hoops_SSRRP = option->value._hoops_PIPCR[0];
			}	break;

			default: {
				HE_ERROR (HEC_IMAGE, HES_INVALID_OPTION, "Unknown image option");
			} break;
		}
	} while ((option = option->next) != null);

	if (_hoops_ACGPI == &_hoops_PCGPI) 
		_hoops_AHGPI (_hoops_RIGC, &_hoops_PCGPI);

	return _hoops_ACGPI->format;
}




HC_INTERFACE void HC_CDECL HC_Show_Partial_Image (
	Key							key,
	int							xoffset,
	int							yoffset,
	int							xcount,
	int							ycount,
	void *						_hoops_SHGGR) 
{
	_hoops_PAPPR context("Show_Partial_Image");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Partial_Image () */\n");
	);

	Image *						image;
	Image *						_hoops_HCGPI = null;
	void const * const *		_hoops_GAAC;
	unsigned char *				source;
	unsigned char *				_hoops_PCAP = (unsigned char *)_hoops_SHGGR;

	if (xoffset < 0 || yoffset < 0) {
		HE_ERROR (HEC_IMAGE, HES_INVALID_OFFSET,
				"Offset from the array origin must be non-negative");
		return;
	}
	if (xcount < 0 || ycount < 0) {
		HE_ERROR (HEC_IMAGE, HES_INVALID_INPUT,
				"X count or Y count is less than zero");
		return;
	}
	if (xcount == 0 || ycount == 0) 
		return;

	_hoops_CSPPR();

	image = (Image *)_hoops_RCSSR (context, key);

	if (image == null ||
		image->type != _hoops_HGCP ||
		BIT (image->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_IMAGE, HES_INVALID_KEY, "Key does not refer to a valid image");
		goto Release;
	}
	else if (BIT (image->flags, _hoops_SSGH)) {
		if (image->format == _hoops_GGRH) {
			_hoops_HCGPI = HI_JPEG_Decompress (image);
			image = _hoops_HCGPI;
		}
		if (image->format == _hoops_RGRH) {
			_hoops_HCGPI = HI_JPEG_Decompress (image);
			image = _hoops_HCGPI;
		}
		else if (image->format == _hoops_AGRH) {
			_hoops_HCGPI = HI_TARGA_Decompress (image);
			image = _hoops_HCGPI;
		}
		else {
			HE_ERROR (HEC_IMAGE, HES_INVALID_TYPE,"Provided key refers to an image that cannot be decompressed");
			goto Release;
		}
		if (!image) {
			HE_ERROR (HEC_IMAGE, HES_INVALID_TYPE, "Error encountered during image decompression");
			goto Release;
		}
	}
	else if (xoffset + xcount > image->width || yoffset + ycount > image->height) {
		HE_ERROR (HEC_IMAGE, HES_REPLACEMENT_OVERFLOW,"Replacement is not entirely within the original array");
		goto Release;
	}

	_hoops_GAAC = image->rasters + yoffset;
	if (image->format == Image_MAPPED_8 ||
		image->format == Image_MAPPED_16 ||
		image->format == image->_hoops_ISRRP) {

		xcount *= image->_hoops_CSRRP;
		if (ycount > 0) do {
			source = (unsigned char *)*_hoops_GAAC++;
			source += xoffset * image->_hoops_CSRRP;
			COPY_MEMORY ((void *)source, xcount, (void *)_hoops_PCAP);
			_hoops_PCAP += xcount;
		}
		_hoops_RGGA (--ycount == 0);
	}
	else {
		if (image->format == _hoops_CSGSP) {
			if (ycount > 0 && xcount > 0) do {
				int				count = xcount;
				RGBAS32 *		array = (RGBAS32 *)*_hoops_GAAC++;

				array += xoffset;

				do {
					if (image->_hoops_ISRRP == _hoops_HRSRH)
						*_hoops_PCAP++ = array->a;

					*_hoops_PCAP++ = array->r;
					*_hoops_PCAP++ = array->g;
					*_hoops_PCAP++ = array->b;

					if (image->_hoops_ISRRP == Image_RGBA32)
						*_hoops_PCAP++ = array->a;

					++array;
				} while (--count > 0);
			} while (--ycount > 0);
		}
		else if (image->format == Image_RGBA32) {
			if (ycount > 0 && xcount > 0) do {
				int				count = xcount;
				_hoops_AIGH *		array = (_hoops_AIGH *)*_hoops_GAAC++;

				array += xoffset;

				do {
					if (image->_hoops_ISRRP == _hoops_HRSRH)
						*_hoops_PCAP++ = array->a;

					*_hoops_PCAP++ = array->r;
					*_hoops_PCAP++ = array->g;
					*_hoops_PCAP++ = array->b;

					if (image->_hoops_ISRRP == Image_RGBA32)
						*_hoops_PCAP++ = array->a;

					++array;
				} while (--count > 0);
			} while (--ycount > 0);
		}
		else if (image->format == _hoops_HRSRH) {
			if (ycount > 0 && xcount > 0) do {
				int				count = xcount;
				_hoops_IRSRH *		array = (_hoops_IRSRH *)*_hoops_GAAC++;

				array += xoffset;

				do {
					if (image->_hoops_ISRRP == _hoops_HRSRH)
						*_hoops_PCAP++ = array->a;

					*_hoops_PCAP++ = array->r;
					*_hoops_PCAP++ = array->g;
					*_hoops_PCAP++ = array->b;

					if (image->_hoops_ISRRP == Image_RGBA32)
						*_hoops_PCAP++ = array->a;

					++array;
				} while (--count > 0);
			} while (--ycount > 0);
		}
		else if (image->format == _hoops_HHGH) {
			if (ycount > 0 && xcount > 0) do {
				int				count = xcount;
				_hoops_SHGH *			array = (_hoops_SHGH *)*_hoops_GAAC++;

				array += xoffset;

				do {
					if (image->_hoops_ISRRP == _hoops_HRSRH)
						*_hoops_PCAP++ = _hoops_GPGCR;

					*_hoops_PCAP++ = array->r;
					*_hoops_PCAP++ = array->g;
					*_hoops_PCAP++ = array->b;

					if (image->_hoops_ISRRP == Image_RGBA32)
						*_hoops_PCAP++ = _hoops_GPGCR;

					++array;
				} while (--count > 0);
			} while (--ycount > 0);
		}
	}
  Release:
	if (_hoops_HCGPI != null)
		HI_Au_Revoir ((_hoops_HPAH *)_hoops_HCGPI);
	_hoops_IRRPR();
#endif
}


#ifndef DISABLE_GEOMETRY_SHOW

local void _hoops_ICGPI (
	Image *						image,
	char *						format,
	int							_hoops_CCGPI) {
	char						buf[1000];
	char *						_hoops_ASAPR = buf;
	char *						_hoops_PSAPR;

	if (_hoops_CCGPI == -1)
		_hoops_PSAPR = _hoops_ASAPR + HOOPS_WORLD->_hoops_RAPPR;		/* _hoops_IHRPR _hoops_IAHA */
	else
		_hoops_PSAPR = _hoops_ASAPR + _hoops_CCGPI;				/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA */

	switch (image->_hoops_ISRRP) {
#ifndef DISABLE_NON_RGB_IMAGES
		case Image_MAPPED_8: {
			_hoops_ASAPR = HI_Copy_Chars ("mapped 8", _hoops_ASAPR);
		}	break;

		case Image_MAPPED_16: {
			_hoops_ASAPR = HI_Copy_Chars ("mapped 16", _hoops_ASAPR);
		}	break;

		case _hoops_HRSRH: {
			_hoops_ASAPR = HI_Copy_Chars ("argb", _hoops_ASAPR);
		}	break;
#endif
		case _hoops_HHGH: {
			_hoops_ASAPR = HI_Copy_Chars ("rgb", _hoops_ASAPR);
		}	break;

		case Image_RGBA32: {
			_hoops_ASAPR = HI_Copy_Chars ("rgba", _hoops_ASAPR);
		}	break;

		case _hoops_PCCRH: {
			_hoops_ASAPR = HI_Copy_Chars ("depth", _hoops_ASAPR);
		}	break;

		case _hoops_AHGH: {
			_hoops_ASAPR = HI_Copy_Chars ("grayscale", _hoops_ASAPR);
		}	break;

		case _hoops_GGRH: {
			_hoops_ASAPR = HI_Copy_Chars ("png", _hoops_ASAPR);
		}	break;

		case _hoops_RGRH: {
			_hoops_ASAPR = HI_Copy_Chars ("jpeg", _hoops_ASAPR);
		}	break;

		case _hoops_AGRH: {
			_hoops_ASAPR = HI_Copy_Chars ("tga", _hoops_ASAPR);
		}	break;

		case _hoops_IRRH: {
			_hoops_ASAPR = HI_Copy_Chars ("dxt1", _hoops_ASAPR);
		}	break;

		case _hoops_CRRH: {
			_hoops_ASAPR = HI_Copy_Chars ("dxt3", _hoops_ASAPR);
		}	break;

		case _hoops_SRRH: {
			_hoops_ASAPR = HI_Copy_Chars ("dxt5", _hoops_ASAPR);
		}	break;
	}

	if (image->name.length != 0)
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, ",name=%qn", (void *)&image->name);

	if (image->_hoops_PIRRP._hoops_HHP != _hoops_SHGRP || 
		image->_hoops_HIRRP._hoops_HHP != _hoops_SHGRP) {
		char _hoops_SCGPI[1000];

		if (image->_hoops_PIRRP._hoops_HHP == image->_hoops_HIRRP._hoops_HHP &&
			image->_hoops_PIRRP.value == image->_hoops_HIRRP.value) {

			HI_Format_Generic_Size_String(&image->_hoops_PIRRP, _hoops_SCGPI, -1);
			_hoops_ASAPR = HI_Copy_Chars (",size=", _hoops_ASAPR);
			_hoops_ASAPR = HI_Copy_Chars (_hoops_SCGPI, _hoops_ASAPR);
		}
		else {
			if (image->_hoops_PIRRP._hoops_HHP != _hoops_SHGRP) {
				HI_Format_Generic_Size_String(&image->_hoops_PIRRP, _hoops_SCGPI, -1);
				_hoops_ASAPR = HI_Copy_Chars (",size=(", _hoops_ASAPR);
				_hoops_ASAPR = HI_Copy_Chars (_hoops_SCGPI, _hoops_ASAPR);
			}
			if (image->_hoops_HIRRP._hoops_HHP != _hoops_SHGRP) {
				HI_Format_Generic_Size_String(&image->_hoops_PIRRP, _hoops_SCGPI, -1);
				_hoops_ASAPR = HI_Copy_Chars (",", _hoops_ASAPR);
				_hoops_ASAPR = HI_Copy_Chars (_hoops_SCGPI, _hoops_ASAPR);
				_hoops_ASAPR = HI_Copy_Chars (")", _hoops_ASAPR);
			}
		}
	}

	if (image->_hoops_SSRRP < 1.0) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, ",compression quality=%f", (void *)&image->_hoops_SSRRP);
	}
	if (BIT (image->flags, _hoops_GPAH))
		_hoops_ASAPR = HI_Copy_Chars (",discard", _hoops_ASAPR);

	HI_Return_Chars (format, _hoops_CCGPI, buf, (int)(_hoops_ASAPR - buf));
}

local bool _hoops_GSGPI (Image *image)
{
	Image *_hoops_IHARI = null;

	if (image->format == _hoops_GGRH)
		_hoops_IHARI = HI_PNG_Decompress (image);
	else if (image->format == _hoops_RGRH)
		_hoops_IHARI = HI_JPEG_Decompress (image);
	else if (image->format == _hoops_AGRH)
		_hoops_IHARI = HI_TARGA_Decompress (image);
	if (_hoops_IHARI == null)
		return false;

	ASSERT (!image->rasters); //_hoops_IAII _hoops_RH _hoops_HSPR _hoops_CHH _hoops_SHH _hoops_IRS _hoops_AGCGR
	image->rasters = _hoops_IHARI->rasters;
	_hoops_IHARI->rasters = null;
	_hoops_IHARI->flags |= _hoops_APAH;

	FREE_ARRAY (image->_hoops_PHGH, image->_hoops_IARH, char);
	image->_hoops_PHGH = _hoops_IHARI->_hoops_PHGH;
	_hoops_IHARI->_hoops_PHGH = null;

	image->row_bytes = _hoops_IHARI->row_bytes;
	
	image->format = _hoops_HHGH;
	image->flags &= ~_hoops_SSGH;

	//_hoops_SR _hoops_AIAH _hoops_RSGPI _hoops_RH _hoops_CICRR _hoops_SGS _hoops_SR _hoops_AAPR _hoops_GPIHR _hoops_GGR
	HI_Au_Revoir ((_hoops_HPAH *)_hoops_IHARI);
	return true;
}

#endif

HC_INTERFACE void HC_CDECL HC_Show_Image (
	Key				key,
	float *			x,
	float *			y,
	float *			z,
	char *			format,
	int *			width,
	int *			height,
	void *			_hoops_SHGGR) 
{
	_hoops_PAPPR context("Show_Image");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Image () */\n");
	);

	unsigned char *	_hoops_PCAP = (unsigned char *)_hoops_SHGGR;

	void const * const * _hoops_GAAC;
	int w;
	int h;

	_hoops_CSPPR();

	Image *	image = (Image *)_hoops_RCSSR (context, key);
	Image *	_hoops_HCGPI = null;

	if (image == null ||
		image->type != _hoops_HGCP ||
		BIT (image->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_IMAGE, HES_INVALID_KEY, "Provided key does not refer to a valid image");
		goto Release;
	}
	if (BIT (image->flags, _hoops_SSGH)) {
		if (image->format == _hoops_GGRH) {
			_hoops_HCGPI = HI_PNG_Decompress (image);
			image = _hoops_HCGPI;
		}
		else if (image->format == _hoops_RGRH) {
			_hoops_HCGPI = HI_JPEG_Decompress (image);
			image = _hoops_HCGPI;
		}
		else if (image->format == _hoops_AGRH) {
			_hoops_HCGPI = HI_TARGA_Decompress (image);
			image = _hoops_HCGPI;
		}
		else {
			HE_ERROR (HEC_IMAGE, HES_INVALID_TYPE,"Provided key refers to an image that cannot be decompressed");
			goto Release;
		}
		if (!image) {
			HE_ERROR (HEC_IMAGE, HES_INVALID_TYPE, "Error encountered during image decompression");
			goto Release;
		}
	}
	if (ALLBITS (image->flags, _hoops_GRRH)) {
		_hoops_GACR *	dl = image->_hoops_GAHA;
		_hoops_GGAGR *		_hoops_CSHHP = (_hoops_GGAGR *)dl->_hoops_GHRI; 
		_hoops_HISAA (context, _hoops_CSHHP, _hoops_ASGPI, dl->list);
	}

	_hoops_GAAC = image->rasters;
	w = image->width;
	h = image->height;

	if (width != null)
		*width = w;
	if (height != null)
		*height = h;

	if (_hoops_PCAP != null) {

		if (image->format == Image_MAPPED_8 ||
			image->format == Image_MAPPED_16 ||
			image->format == image->_hoops_ISRRP) {
			w *= image->_hoops_CSRRP;

			if (h > 0 && w > 0) do {

				COPY_MEMORY (*_hoops_GAAC, w, (void *)_hoops_PCAP);
				_hoops_GAAC++;
				_hoops_PCAP += w;
			} while (--h > 0);
		}
		else {
			if (image->format == _hoops_CSGSP) {
				if (h > 0 && w > 0) do {
					int				count = w;
					RGBAS32 *		array = (RGBAS32 *)*_hoops_GAAC++;

					do {
						if (image->_hoops_ISRRP == _hoops_HRSRH)
							*_hoops_PCAP++ = array->a;

						*_hoops_PCAP++ = array->r;
						*_hoops_PCAP++ = array->g;
						*_hoops_PCAP++ = array->b;

						if (image->_hoops_ISRRP == Image_RGBA32)
							*_hoops_PCAP++ = array->a;

						++array;
					} while (--count > 0);
				} while (--h > 0);
			}
			else if (image->format == Image_RGBA32) {
				if (h > 0 && w > 0) do {
					int				count = w;
					_hoops_AIGH *		array = (_hoops_AIGH *)*_hoops_GAAC++;

					do {
						if (image->_hoops_ISRRP == _hoops_HRSRH)
							*_hoops_PCAP++ = array->a;

						*_hoops_PCAP++ = array->r;
						*_hoops_PCAP++ = array->g;
						*_hoops_PCAP++ = array->b;

						if (image->_hoops_ISRRP == Image_RGBA32)
							*_hoops_PCAP++ = array->a;

						++array;
					} while (--count > 0);
				} while (--h > 0);
			}
			else if (image->format == _hoops_HRSRH) {
				if (h > 0 && w > 0) do {
					int				count = w;
					_hoops_IRSRH *		array = (_hoops_IRSRH *)*_hoops_GAAC++;

					do {
						if (image->_hoops_ISRRP == _hoops_HRSRH)
							*_hoops_PCAP++ = array->a;

						*_hoops_PCAP++ = array->r;
						*_hoops_PCAP++ = array->g;
						*_hoops_PCAP++ = array->b;

						if (image->_hoops_ISRRP == Image_RGBA32)
							*_hoops_PCAP++ = array->a;

						++array;
					} while (--count > 0);
				} while (--h > 0);
			}
			else if (image->format == _hoops_HHGH) {
				if (h > 0 && w > 0) do {
					int				count = w;
					_hoops_SHGH *			array = (_hoops_SHGH *)*_hoops_GAAC++;

					do {
						if (image->_hoops_ISRRP == _hoops_HRSRH)
							*_hoops_PCAP++ = _hoops_GPGCR;

						*_hoops_PCAP++ = array->r;
						*_hoops_PCAP++ = array->g;
						*_hoops_PCAP++ = array->b;

						if (image->_hoops_ISRRP == Image_RGBA32)
							*_hoops_PCAP++ = _hoops_GPGCR;

						++array;
					} while (--count > 0);
				} while (--h > 0);
			}
		}
	}

	if (x != null)
		*x = image->_hoops_CSAI.x;
	if (y != null)
		*y = image->_hoops_CSAI.y;
	if (z != null)
		*z = image->_hoops_CSAI.z;

	if (format != null)
		_hoops_ICGPI (image, format, -1);

  Release:
	if (_hoops_HCGPI != null)
		HI_Au_Revoir ((_hoops_HPAH *)_hoops_HCGPI);
	_hoops_IRRPR();
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Compressed_Image (
	Key				key,
	float *			x,
	float *			y,
	float *			z,
	char *			format,
	int *			width,
	int *			height,
	int *			data_size,
	void *			_hoops_SHGGR) 
{
	_hoops_PAPPR context("Show_Compressed_Image");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Compressed_Image () */\n");
	);

	unsigned char *	_hoops_PCAP = (unsigned char *)_hoops_SHGGR;

	_hoops_CSPPR();

	Image *	image = (Image *)_hoops_RCSSR (context, key);

	if (image == null ||
		image->type != _hoops_HGCP ||
		BIT (image->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_IMAGE, HES_INVALID_KEY, "Provided key does not refer to a valid image");
		goto Release;
	}
	if (!BIT (image->flags, _hoops_SSGH)) {
		HE_ERROR (HEC_IMAGE, HES_INVALID_TYPE, "Provided key does not refer to a compressed image");
		goto Release;
	}


	if (ALLBITS (image->flags, _hoops_GRRH|_hoops_APAH)) {
		_hoops_GACR *	dl = image->_hoops_GAHA;
		_hoops_GGAGR *		_hoops_GHRI = (_hoops_GGAGR *)dl->_hoops_GHRI; 
		
		_hoops_HISAA (context, _hoops_GHRI, _hoops_ASGPI, dl->list);
	}

	if (width != null)
		*width = image->width;
	if (height != null)
		*height = image->height;

	//_hoops_AGCR _hoops_CGH _hoops_SHR _hoops_SHH _hoops_IRS _hoops_APIP _hoops_ARAPH _hoops_IH _hoops_SGRH _hoops_RRRH
	ASSERT (image->_hoops_PHGH != NULL); 
	ASSERT (image->_hoops_IARH != 0);

	if (_hoops_PCAP != null)
		COPY_MEMORY (image->_hoops_PHGH, image->_hoops_IARH, (void *)_hoops_PCAP);

	if (data_size != null)
		*data_size = image->_hoops_IARH;

	if (x != null)
		*x = image->_hoops_CSAI.x;
	if (y != null)
		*y = image->_hoops_CSAI.y;
	if (z != null)
		*z = image->_hoops_CSAI.z;

	if (format != null)
		_hoops_ICGPI (image, format, -1);

  Release:
	_hoops_IRRPR();
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Image_Format (
	Key				key,
	char *			format) 
{
	_hoops_PAPPR context("Show_Image_Format");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Image_Format () */\n");
	);

	_hoops_CSPPR();

	Image *	image = (Image *)_hoops_RCSSR (context, key);

	if (image == null ||
		image->type != _hoops_HGCP ||
		BIT (image->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_IMAGE, HES_INVALID_KEY, "Provided key does not refer to a valid image");
		goto Release;
	}

	if (format != null)
		_hoops_ICGPI (image, format, -1);

  Release:
	_hoops_IRRPR();
#endif
}




HC_INTERFACE void HC_CDECL HC_Show_Compressed_Image_Size (
	Key				key,
	char *			format,
	int *			width,
	int *			height,
	int *			data_size) 
{
	_hoops_PAPPR context("Show_Compressed_Image_Size");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Compressed_Image_Size () */\n");
	);

	_hoops_CSPPR();

	Image *	image = (Image *)_hoops_RCSSR (context, key);

	if (image == null ||
		image->type != _hoops_HGCP ||
		BIT (image->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_IMAGE, HES_INVALID_KEY, "Provided key does not refer to a valid image");
	}
	else {
		if (height != null)
			*height = image->height;
		if (width != null)
			*width = image->width;
		if (data_size != null)
			*data_size = image->_hoops_IARH;

		if (format != null)
			_hoops_ICGPI (image, format, -1);
	}

	_hoops_IRRPR();
#endif
}

HC_INTERFACE void HC_CDECL HC_Show_Image_Size (
	Key				key,
	float *			x,
	float *			y,
	float *			z,
	char *			format,
	int *			width,
	int *			height) 
{
	_hoops_PAPPR context("Show_Image_Size");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Image_Size () */\n");
	);

	_hoops_CSPPR();

	Image *	image = (Image *)_hoops_RCSSR (context, key);

	if (image == null ||
		image->type != _hoops_HGCP ||
		BIT (image->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_IMAGE, HES_INVALID_KEY, "Provided key does not refer to a valid image");
	}
	else {
		if (height != null)
			*height = image->height;
		if (width != null)
			*width = image->width;

		if (x != null)
			*x = image->_hoops_CSAI.x;
		if (y != null)
			*y = image->_hoops_CSAI.y;
		if (z != null)
			*z = image->_hoops_CSAI.z;

		if (format != null)
			_hoops_ICGPI (image, format, -1);
	}

	_hoops_IRRPR();
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Image_Name (
	Key				key,
	char *			name) 
{
	_hoops_PAPPR context("Show_Image_Name");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Image_Name () */\n");
	);

	_hoops_CSPPR();

	Image *		image = (Image *)_hoops_RCSSR (context, key);

	if (image == null ||
		image->type != _hoops_HGCP ||
		BIT (image->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_IMAGE, HES_INVALID_KEY, "Provided key does not refer to a valid image");
	}
	else {

		if (name != null &&
			image->name.length != 0) {

			char	*_hoops_ASAPR = name;
			char	*_hoops_PSAPR;

			_hoops_PSAPR = _hoops_ASAPR + HOOPS_WORLD->_hoops_RAPPR;		/* _hoops_IHRPR _hoops_IAHA */

			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%qn", (void *)&image->name);

			*_hoops_ASAPR = '\0'; 
		}
	}

	_hoops_IRRPR();

#endif
}






HC_INTERFACE void HC_CDECL HC_Move_Image (
	Key				key,
	double			x,
	double			y,
	double			z) 
{
	_hoops_PAPPR context("Move_Image");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Move_Image (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%F);\n", z));
	);

	_hoops_CRCP *		_hoops_SRCP;

	_hoops_RPPPR();

	Image * image = (Image *)_hoops_RCSSR (context, key);

	if (image == null || image->type != _hoops_HGCP ||
		BIT (image->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_IMAGE, HES_INVALID_KEY, "Provided key does not refer to a valid Image");
		goto Release;
	}

	if (image->_hoops_CSAI.x == x &&
		image->_hoops_CSAI.y == y &&
		image->_hoops_CSAI.z == z) goto Release;

	image->_hoops_CSAI.x = (float)x;
	image->_hoops_CSAI.y = (float)y;
	image->_hoops_CSAI.z = (float)z;
	image->_hoops_CPGPR |= _hoops_HHSSR;

	_hoops_SRCP = image->owner;

	if (!BIT (image->_hoops_RRHH, _hoops_RSPCR)) {
		if (image->_hoops_CSAI.z != 0.0f) {
			image->_hoops_RRHH |= _hoops_RSPCR;
			if (!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_ASPCR))
				HI_Propagate_Maybes (context, _hoops_SRCP, _hoops_ASPCR);
		}
	}

	_hoops_SASIR (context, _hoops_SRCP, _hoops_RAGGA|_hoops_PISSR|_hoops_RPSIR);

  Release:
	_hoops_IRRPR();
}

HC_INTERFACE void HC_CDECL HC_Edit_Image_Options (
	Key				key,
	char const *	format) 
{
	_hoops_PAPPR context("Edit_Image_Options");

#ifdef DISABLE_GEOMETRY_EDIT
	_hoops_IRPPR ("Geometry Edit");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* Edit_Image_Options () */\n");
	);

	struct _hoops_SPCIH			data;

	_hoops_RPPPR();

	Image *	image = (Image *)_hoops_RCSSR (context, key);

	if (image == null || image->type != _hoops_HGCP ||
		BIT (image->_hoops_RRHH, _hoops_HGAGR)) {
			HE_ERROR (HEC_IMAGE, HES_INVALID_KEY, "Key does not refer to a valid image");
			goto Release;
	}

	HI_Determine_Image_Format (context, format, &data);

	if (data._hoops_CPGPI) {
		HE_ERROR (HEC_IMAGE, HES_INVALID_OPTION, "A non-editable image option was specified.");
		goto Release;
	}
	
	_hoops_GHGPI(context, (_hoops_HPAH *)image->owner, &data, image);

	_hoops_AHGPI (context, &data);

	if (!ANYBIT (image->_hoops_CPGPR, _hoops_CASIR|_hoops_AHSGA)) {
		image->_hoops_CPGPR |= _hoops_HHSSR;
		_hoops_SASIR (context, image->owner, _hoops_IHSSR);
	}

	HI_Clear_Image_Cache(image);

Release:
	_hoops_IRRPR();
#endif
}


#define _hoops_PSGPI(x)				((_hoops_GARSR)_hoops_IRGCR(x))

GLOBAL_FUNCTION _hoops_GARSR HI_Find_Raster_Max (
	_hoops_GARSR			max,
	int					width,
	Image_Format		format,
	void *				_hoops_CACIH) {

	switch (format) {
		case _hoops_HHGH: 
		case Image_RGBA32: 
		case _hoops_HRSRH: {
		}	break;
#ifndef DISABLE_NON_RGB_IMAGES
		case Image_MAPPED_8: {
			unsigned char	*_hoops_GAAC = (unsigned char *)_hoops_CACIH;

			_hoops_RGGA (--width < 0) {
				if (max < _hoops_PSGPI (*_hoops_GAAC)) max = _hoops_PSGPI (*_hoops_GAAC);
				++_hoops_GAAC;
			}

		}	break;

		case Image_MAPPED_16: {
			_hoops_GARSR	*_hoops_GAAC = (_hoops_GARSR *)_hoops_CACIH;

			_hoops_RGGA (--width < 0) {
				if (max < *_hoops_GAAC) max = *_hoops_GAAC;
				++_hoops_GAAC;
			}
		}	break;
#endif
	}

	return max;
}


GLOBAL_FUNCTION long HI_Count_Transparent_Pixels (
	int						width,
	Image_Format			format,
	void *					_hoops_CACIH) {
	long					count = 0;

	switch (format) {
		case _hoops_CSGSP: {
			RGBAS32		*_hoops_GAAC = (RGBAS32 *)_hoops_CACIH;

			_hoops_RGGA (--width < 0) {
				if (_hoops_GAAC->a != 0xFF) ++count;
				++_hoops_GAAC;
			}
		}	break;

		case Image_RGBA32: {
			_hoops_AIGH		*_hoops_GAAC = (_hoops_AIGH *)_hoops_CACIH;

			_hoops_RGGA (--width < 0) {
				if (_hoops_GAAC->a != 0xFF) ++count;
				++_hoops_GAAC;
			}
		}	break;

		case _hoops_HRSRH: {
			_hoops_IRSRH		*_hoops_GAAC = (_hoops_IRSRH *)_hoops_CACIH;

			_hoops_RGGA (--width < 0) {
				if (_hoops_GAAC->a != 0xFF) ++count;
				++_hoops_GAAC;
			}
		}	break;

		case _hoops_HHGH:
		case Image_MAPPED_8:
		case Image_MAPPED_16: {
		}	break;
	}

	return count;
}



HC_INTERFACE void HC_CDECL HC_Edit_Image (
	Key						key,
	int						xoffset,
	int						yoffset,
	int						xcount,
	int						ycount,
	void const *			pixels) 
{
	_hoops_PAPPR context("Edit_Image");

#ifdef DISABLE_GEOMETRY_EDIT
	_hoops_IRPPR ("Geometry Edit");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Edit_Image () */\n");
	);

	void const * const *	rasters;
	unsigned char *			source;
	int						_hoops_HSGPI;

	_hoops_RPPPR();

	Image *	image = (Image *)_hoops_RCSSR (context, key);

	if (image == null || image->type != _hoops_HGCP ||
		BIT (image->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_IMAGE, HES_INVALID_KEY, "Key does not refer to a valid image");
		goto Release;
	}

	if (xcount < 0 || ycount < 0) {
		HE_ERROR (HEC_IMAGE, HES_INVALID_COUNT, "xcount or ycount is less than zero");
		goto Release;
	}

	if (xoffset + xcount > image->width || yoffset + ycount > image->height) {
		HE_ERROR (HEC_IMAGE, HES_INVALID_OFFSET, "Replacement is not entirely within the original array");
		goto Release;
	}

	if (xoffset < 0 || yoffset < 0) {
		HE_ERROR (HEC_IMAGE, HES_INVALID_OFFSET, "Offset from the array origin must be non-negative");
		goto Release;
	}

	if (xcount == 0 || ycount == 0) {
		if (BIT(image->_hoops_RRHH, _hoops_IIPIR)) {
			if (image->format != _hoops_HHGH) {

				rasters = (void const **)image->rasters;

				image->_hoops_RGARP = 0;
				image->_hoops_AGARP = 0;

				if (image->format == Image_MAPPED_16 || image->format == Image_MAPPED_8)
					for (int i=0; i<image->height; i++)
						image->_hoops_RGARP = HI_Find_Raster_Max (image->_hoops_RGARP,
							image->width, image->format, (void alter *)image->rasters[i]);
				else
					for (int i=0; i<image->height; i++)
						image->_hoops_AGARP += HI_Count_Transparent_Pixels (
							image->width, image->format, (void alter *)image->rasters[i]);
			}

			goto _hoops_ISGPI;
		}

		goto Release;
	}

	if (image->format == _hoops_IRRH ||
		image->format == _hoops_CRRH ||
		image->format == _hoops_SRRH) {
		HE_ERROR (HEC_IMAGE, HES_INVALID_KEY, "Key refers to a DXT image, which cannot be edited");
		goto Release;
	}

	if (image->format == _hoops_GGRH ||
		image->format == _hoops_RGRH ||
		image->format == _hoops_AGRH) {
		if (!_hoops_GSGPI (image))
			goto Release;
	}

	if (BIT(image->flags, _hoops_SHCC))
		HOOPS_WORLD->_hoops_ACPIR--;

	rasters = image->rasters + yoffset;
	source = (unsigned char *)pixels;
	_hoops_HSGPI = ycount;

	if (image->format == Image_MAPPED_8 ||
		image->format == Image_MAPPED_16 ||
		image->format == image->_hoops_ISRRP) {
		do {
			unsigned char *		_hoops_PCAP;

			_hoops_PCAP = (unsigned char *)*rasters++;
			_hoops_PCAP += xoffset * image->_hoops_CSRRP;

			if (image->format != Image_MAPPED_8 && image->format != Image_MAPPED_16)
				image->_hoops_AGARP -= HI_Count_Transparent_Pixels (xcount, image->format, _hoops_PCAP);

			COPY_MEMORY ((void *)source, (long)xcount * (long)image->_hoops_CSRRP, (void *)_hoops_PCAP);

			if (image->format != Image_MAPPED_8 && image->format != Image_MAPPED_16)
				image->_hoops_AGARP += HI_Count_Transparent_Pixels (xcount, image->format, _hoops_PCAP);
			else
				image->_hoops_RGARP = HI_Find_Raster_Max (image->_hoops_RGARP, xcount, image->format, _hoops_PCAP);

			source += xcount * image->_hoops_CSRRP;
		} while (--ycount > 0);
	}
	else if (image->format == _hoops_CSGSP) {
		do {
			int				count = xcount;
			RGBAS32			*_hoops_PCAP, *_hoops_CSGPI;

			_hoops_PCAP = _hoops_CSGPI = (RGBAS32 *)*rasters++;
			_hoops_PCAP += xoffset;
			image->_hoops_AGARP -= HI_Count_Transparent_Pixels (xcount, image->format, _hoops_PCAP);
			do {
				_hoops_PCAP->a = _hoops_GPGCR;	/* _hoops_HPCAR _hoops_HGGPA */
				if (image->_hoops_ISRRP == _hoops_HRSRH) _hoops_PCAP->a = *source++;
				_hoops_PCAP->r = *source++;
				_hoops_PCAP->g = *source++;
				_hoops_PCAP->b = *source++;
				if (image->_hoops_ISRRP == Image_RGBA32) _hoops_PCAP->a = *source++;
				++_hoops_PCAP;
			} while (--count > 0);
			image->_hoops_AGARP += HI_Count_Transparent_Pixels (xcount, image->format, _hoops_CSGPI);
		} while (--ycount > 0);
	}
	else if (image->format == Image_RGBA32) {
		do {
			int				count = xcount;
			_hoops_AIGH			*_hoops_PCAP, *_hoops_CSGPI;

			_hoops_PCAP = _hoops_CSGPI = (_hoops_AIGH *)*rasters++;
			_hoops_PCAP += xoffset;
			image->_hoops_AGARP -= HI_Count_Transparent_Pixels (xcount, image->format, _hoops_PCAP);
			do {
				_hoops_PCAP->a = _hoops_GPGCR;	/* _hoops_HPCAR _hoops_HGGPA */
				if (image->_hoops_ISRRP == _hoops_HRSRH) _hoops_PCAP->a = *source++;
				_hoops_PCAP->r = *source++;
				_hoops_PCAP->g = *source++;
				_hoops_PCAP->b = *source++;
				if (image->_hoops_ISRRP == Image_RGBA32) _hoops_PCAP->a = *source++;
				++_hoops_PCAP;
			} while (--count > 0);
			image->_hoops_AGARP += HI_Count_Transparent_Pixels (xcount, image->format, _hoops_CSGPI);
		} while (--ycount > 0);
	}
	else if (image->format == _hoops_HRSRH) {
		do {
			int				count = xcount;
			_hoops_IRSRH			*_hoops_PCAP, *_hoops_CSGPI;

			_hoops_PCAP = _hoops_CSGPI = (_hoops_IRSRH *)*rasters++;
			_hoops_PCAP += xoffset;
			image->_hoops_AGARP -= HI_Count_Transparent_Pixels (xcount, image->format, _hoops_PCAP);
			do {
				_hoops_PCAP->a = _hoops_GPGCR;	/* _hoops_HPCAR _hoops_HGGPA */
				if (image->_hoops_ISRRP == _hoops_HRSRH) _hoops_PCAP->a = *source++;
				_hoops_PCAP->r = *source++;
				_hoops_PCAP->g = *source++;
				_hoops_PCAP->b = *source++;
				if (image->_hoops_ISRRP == Image_RGBA32) _hoops_PCAP->a = *source++;
				++_hoops_PCAP;
			} while (--count > 0);
			image->_hoops_AGARP += HI_Count_Transparent_Pixels (xcount, image->format, _hoops_CSGPI);
		} while (--ycount > 0);
	}
	else if (image->format == _hoops_HHGH) {
		do {
			int				count = xcount;
			_hoops_SHGH			*_hoops_PCAP, *_hoops_CSGPI;

			_hoops_PCAP = _hoops_CSGPI = (_hoops_SHGH *)*rasters++;
			_hoops_PCAP += xoffset;
			do {
				_hoops_PCAP->r = *source++;
				_hoops_PCAP->g = *source++;
				_hoops_PCAP->b = *source++;
				++_hoops_PCAP;
			} while (--count > 0);
		} while (--ycount > 0);
	}

	ycount = _hoops_HSGPI;

_hoops_ISGPI:
	
	if (image->_hoops_AGARP > 0) {
		HOOPS_WORLD->_hoops_ACPIR++;
		if (!BIT(image->flags, _hoops_SHCC)) {
			image->flags |= _hoops_SHCC;
			_hoops_SASIR (context, image->owner, _hoops_RAGGA);
		}
	}
	else {
		if (BIT(image->flags, _hoops_SHCC)) {
			image->flags &= ~_hoops_SHCC;
		}
	}

	if (!ANYBIT (image->_hoops_CPGPR, _hoops_CASIR|_hoops_AHSGA)) {
		image->_hoops_CPGPR |= _hoops_HHSSR;
		_hoops_SASIR (context, image->owner, _hoops_IHSSR);
	}

	HI_Clear_Image_Cache(image);

Release:
	_hoops_IRRPR();
#endif
}


GLOBAL_FUNCTION void HI_Clear_Image_Cache (
	Image alter *	image) 
{
	/* _hoops_SCAC _hoops_GGSR _hoops_PIAH _hoops_CIPH */
	if (image->next) {
		_hoops_HPRH(image->next);
		image->next=0;
	}

	_hoops_GACR *	dl;

	while ((dl = image->_hoops_GAHA) != null) {
		 image->_hoops_GAHA = dl->next;
		 _hoops_HPRH(dl);
	}
}



GLOBAL_FUNCTION void HI_Validate_Inverted_Rasters (
	Image *			image) 
{
	if (image->_hoops_RCPIR == null) {
		void const		**_hoops_RCPIR;
		ALLOC_ARRAY (_hoops_RCPIR, image->height, void const *);
		image->_hoops_RCPIR = _hoops_RCPIR;

		void const * const * rasters = image->rasters + image->height;

		do *_hoops_RCPIR++ = *--rasters;
		_hoops_RGGA (rasters == image->rasters);
	}
}



#define _hoops_SSGPI 7 /* _hoops_SGS _hoops_HRGR, _hoops_GPP _hoops_PCCP 8 _hoops_RAPSR _hoops_HIICP */

GLOBAL_FUNCTION void HI_Create_Image (
	Image **				_hoops_SACIH,
	Point const *			where,
	int						width,
	int						height,
	Image_Format			format,
	int						row_bytes,
	int						in_type,
	unsigned char const *	source) 
{
	Image *				image;
	void const **		rasters=0;
	void const **		_hoops_GGRPI=0;
	bool				_hoops_RGRPI=false;
	int					type = in_type;
	int					i, j;

	*_hoops_SACIH = 0;

	ZALLOC (image, Image);
	image->_hoops_HIHI = 1;
	image->type = _hoops_HGCP;
	image->_hoops_CPGPR = _hoops_PHSSR;
	image->key = _hoops_AIRIR (image);

	if (where != null)
		image->_hoops_CSAI = *where;
	else
		image->_hoops_CSAI = Point(0,0,0);

	image->width = width;
	image->height = height;
	image->_hoops_HPIR._hoops_CIRH = 1.0f;
	image->_hoops_HPIR._hoops_SIRH = 1.0f;
	image->_hoops_PGARP = -1;

	if (image->width == (int)_hoops_HSHGI(image->width) &&
		image->height == (int)_hoops_HSHGI(image->height))
		image->flags |= _hoops_GHRH;

	if (type != _hoops_HISCP && source == null) 
		type = _hoops_HGPGI;

	/* _hoops_PCSA _hoops_HAR _hoops_IS _hoops_CIH _hoops_RH _hoops_PPGS */
	if (type == _hoops_IGPGI || type == _hoops_SGPGI)
		image->_hoops_RRHH |= _hoops_IIPIR;

	image->format = image->_hoops_ISRRP = format;

	switch (format) {
		case _hoops_GGRH:
		case _hoops_RGRH:
		case _hoops_AGRH:
		case _hoops_IRRH:
		case _hoops_CRRH:
		case _hoops_SRRH:
			*_hoops_SACIH = image;
			//_hoops_IH _hoops_SGRH _hoops_AGHS, _hoops_CPS _hoops_CAPP _hoops_RGR _hoops_PPSR _hoops_HRGR 
			//_hoops_RH _hoops_CSSAR _hoops_IIGR _hoops_RH _hoops_CIS
			return;	

		case _hoops_AHGH:
		case Image_MAPPED_8:
		case _hoops_PGGSP:
			image->_hoops_GCPIR = image->_hoops_CSRRP = 1;
			break;
		case _hoops_PGPGI:
		case Image_MAPPED_16:
			image->_hoops_GCPIR = image->_hoops_CSRRP = 2;
			break;
		case _hoops_HHGH:
			image->_hoops_GCPIR = image->_hoops_CSRRP = 3;
			if (type != _hoops_IGPGI && 
				type != _hoops_SGPGI &&
				type != _hoops_HISCP) {

					image->format = _hoops_HHGH;
					image->_hoops_GCPIR = 3;
			} 
			break;
		case Image_RGBA32:
		case _hoops_HRSRH:
		case _hoops_CSGSP:
			image->_hoops_GCPIR = image->_hoops_CSRRP = 4;
			if (type != _hoops_IGPGI && 
				type != _hoops_SGPGI &&
				type != _hoops_HISCP) {

					image->format = Image_RGBA32;
			}
			break;
		case _hoops_PCCRH:
		case _hoops_AGGSP:
			image->_hoops_GCPIR = image->_hoops_CSRRP = 4;
			break;
	}

	if (row_bytes == 0) {
		if (type != _hoops_IGPGI) {
			/* _hoops_HAR _hoops_RCRR _hoops_CGPR _hoops_RH _hoops_SPS _hoops_AGIR _hoops_HRGR _hoops_SIGR _hoops_RPP _hoops_HPGR _hoops_HCR */
			if (1 || type != _hoops_HISCP) 
				image->row_bytes = image->_hoops_GCPIR * image->width;
			else
				image->row_bytes = (image->_hoops_GCPIR * image->width + _hoops_SSGPI) & ~_hoops_SSGPI;
		}
		else
			image->row_bytes = image->_hoops_CSRRP * image->width;
	}
	else
		image->row_bytes = row_bytes;

	ALLOC_ARRAY (image->rasters, image->height, void const *);

	rasters = (void const **)image->rasters;

	if (type == _hoops_IGPGI || type == _hoops_SGPGI) {
		image->flags |= _hoops_HHRH;
		image->_hoops_PHGH = source;

		for (i=0; i<image->height; i++) {
			rasters[i] = (void *)source;
			source += image->row_bytes;
		}

		if (type != _hoops_SGPGI) 
			_hoops_RGRPI = true;
	}
	else {
		unsigned char	*_hoops_PHGH;

		if (type == _hoops_CGPGI) {
			_hoops_GGRPI = (void const **)source;
		}
		else if (source) {
			ALLOC_ARRAY (_hoops_GGRPI, image->height, void const *);
			for (i=0; i<image->height; i++) {
				_hoops_GGRPI[i] = (void *)source;
				source += image->_hoops_CSRRP * image->width;
			}
		}

		TRY_ALLOC_ARRAY (image->_hoops_PHGH, (long)image->row_bytes * (long)image->height, char);

		if (!image->_hoops_PHGH) {
			/* _hoops_ASIGA  _hoops_AHRH _hoops_GACC _hoops_GGR _hoops_ICPAA _hoops_HPP _hoops_GAGHR */

			FREE_ARRAY (image->rasters, image->height, void const *);
			FREE (image, Image);
			HE_ERROR (HEC_MEMORY, HES_OUT_OF_MEMORY, "No more memory available");
			return;
		}

		image->flags |= _hoops_HHRH;

		_hoops_PHGH = (unsigned char *)image->_hoops_PHGH;
		for (i=0; i<image->height; i++) {
			rasters[i] = (void *)_hoops_PHGH;
			_hoops_PHGH += image->row_bytes;
		}

		rasters = (void const **)image->rasters;

		if (!_hoops_GGRPI) { 
			if (in_type != _hoops_RRPGI) {
				if (image->format == Image_MAPPED_8 || 
					image->format == Image_MAPPED_16 ||
					image->format == _hoops_HHGH ||
					image->format == _hoops_PGPGI ||
					image->format == _hoops_PGGSP ||
					image->format == _hoops_PCCRH ||
					image->format == _hoops_AGGSP ||
					image->format == _hoops_AHGH ||
					in_type == _hoops_HISCP) {

						SET_MEMORY ((void*)image->_hoops_PHGH, image->row_bytes*image->height, 0);
				}
				else {
					Integer32	_hoops_PCRSP = 0;

					if (image->format == _hoops_CSGSP) {
						RGBAS32		_hoops_AGRPI;
						_hoops_AGRPI.r = 0;
						_hoops_AGRPI.g = 0;
						_hoops_AGRPI.b = 0;
						_hoops_AGRPI.a = _hoops_GPGCR;
						_hoops_PCRSP = *(Integer32*)&_hoops_AGRPI;
					}
					else if (image->format == Image_RGBA32) {
						_hoops_AIGH		_hoops_PGRPI;
						_hoops_PGRPI.r = 0;
						_hoops_PGRPI.g = 0;
						_hoops_PGRPI.b = 0;
						_hoops_PGRPI.a = _hoops_GPGCR;
						_hoops_PCRSP = *(Integer32*)&_hoops_PGRPI;
					}
					else if (image->format == _hoops_HRSRH) {
						_hoops_IRSRH		_hoops_HGRPI;
						_hoops_HGRPI.r = 0;
						_hoops_HGRPI.g = 0;
						_hoops_HGRPI.b = 0;
						_hoops_HGRPI.a = _hoops_GPGCR;
						_hoops_PCRSP = *(Integer32*)&_hoops_HGRPI;
					}

					for (i=0; i<image->height; i++) {
						Integer32	*array = (Integer32 *)rasters[i];

						for (j=0; j<image->width; j++) {
							array[j] = _hoops_PCRSP;
						}
					}
				}
			}
		}
		else if (image->format == Image_MAPPED_8 || 
			image->format == Image_MAPPED_16 ||
			image->format == image->_hoops_ISRRP) {

				for (i=0; i<image->height; i++) {
					COPY_MEMORY ((void*)_hoops_GGRPI[i], 
						image->_hoops_CSRRP * image->width, (void alter *)rasters[i]);
				}

				_hoops_RGRPI=true;
		}
		else {
			for (i=0; i<image->height; i++) {
				_hoops_AIGH		*array = (_hoops_AIGH *)rasters[i];
				unsigned char	*_hoops_IGRPI = (unsigned char*)_hoops_GGRPI[i];

				for (j=0; j<image->width; j++) {
					if (image->_hoops_ISRRP == _hoops_HRSRH) {
						array[j].a = *_hoops_IGRPI++;
						array[j].r = *_hoops_IGRPI++;
						array[j].g = *_hoops_IGRPI++;
						array[j].b = *_hoops_IGRPI++;
					}
					else if (image->_hoops_ISRRP == _hoops_CSGSP) {
						RGBAS32 *pixel = (RGBAS32*)&_hoops_IGRPI[j]; 

						array[j].a = pixel->a;
						array[j].r = pixel->r;
						array[j].g = pixel->g;
						array[j].b = pixel->b;

						_hoops_IGRPI+=4;
					}
					else {
						/*_hoops_CSCR->_hoops_CGRPI == _hoops_SGRPI*/
						array[j].a = _hoops_GPGCR;
						array[j].r = *_hoops_IGRPI++;
						array[j].g = *_hoops_IGRPI++;
						array[j].b = *_hoops_IGRPI++;
					}

					if (array[j].a != _hoops_GPGCR)
						image->_hoops_AGARP++;
				} 
			} 
		}
	}

	if (_hoops_RGRPI) {
		rasters = (void const **)image->rasters;

		if (image->format == Image_MAPPED_16 || image->format == Image_MAPPED_8)
			for (i=0; i<image->height; i++)
				image->_hoops_RGARP = HI_Find_Raster_Max (image->_hoops_RGARP, 
				image->width, image->format, (void alter *)image->rasters[i]);
		else
			for (i=0; i<image->height; i++)
				image->_hoops_AGARP += HI_Count_Transparent_Pixels (
				image->width, image->format, (void alter *)image->rasters[i]);
	}

	if (image->_hoops_AGARP) {
		image->flags |= _hoops_SHCC;
		HOOPS_WORLD->_hoops_ACPIR++;
	}

	*_hoops_SACIH = image;

	if (_hoops_GGRPI) {
		if (type == _hoops_CGPGI) {
			for (i=0; i<image->height; i++) {
				FREE_ARRAY (_hoops_GGRPI[i], image->_hoops_CSRRP * image->width, char);
			}

		}

		FREE_ARRAY (_hoops_GGRPI, image->height, void const *);
	}
}





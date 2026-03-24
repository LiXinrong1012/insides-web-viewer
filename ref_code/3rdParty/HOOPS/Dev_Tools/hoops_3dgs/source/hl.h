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
 * $Id: obf_tmp.txt 1.64 2010-09-17 02:22:55 covey Exp $
 */

#define _hoops_SIRSH (1.0e-5)							/* _hoops_IH _hoops_HA: _hoops_CGH _hoops_SHH _hoops_HCSP */
#define _hoops_GCRSH(x) ((x < _hoops_SIRSH) && (x > -_hoops_SIRSH))

Begin_HOOPS_Namespace

struct _hoops_RCRSH {
	_hoops_RCRSH	*			next;
	Net_Rendition			_hoops_APHGA;

	Geometry const *		_hoops_RAI;	/* _hoops_IH _hoops_ASGC */
	_hoops_CRCP const *			_hoops_RRCIP;
	_hoops_HICS			path;

	DC_Point *				_hoops_CAP;
	DC_Point *				points;

	_hoops_ARPA *					planes;

	int						count;
};



struct _hoops_ACRSH {
	_hoops_ACRSH *		next;
	_hoops_ACRSH *		prev;

	float			start;
	float			end;
};

struct _hoops_PCRSH {
	_hoops_PCRSH *			next;

	DC_Point const *	points;
	RGBAS32 const *		colors;

	float				start;
	float				end;

	_hoops_ACRSH *			_hoops_HCRSH;
	_hoops_ACRSH *			_hoops_ICRSH;
};


struct _hoops_CCRSH {
	_hoops_CCRSH *			next;
	Net_Rendition			_hoops_APHGA;
	Geometry const *		_hoops_RAI;	/* _hoops_IH _hoops_ASGC */
	_hoops_CRCP const *			_hoops_RRCIP;
	_hoops_HICS			path;

	_hoops_PCRSH *				_hoops_PICHR;

	DC_Point *				points;
	RGBAS32 *				colors;
	int						count;

	bool					_hoops_HSIPH;
};


struct _hoops_SCRSH {
	float				xmin, xmax, ymin, ymax;

	float				_hoops_GSAHR;
};


typedef int				_hoops_GSRSH;
#define _hoops_RSRSH				(_hoops_GSRSH)0x00
#define _hoops_ASRSH					(_hoops_GSRSH)0x01
#define _hoops_PSRSH			(_hoops_GSRSH)0x02

struct _hoops_HSRSH {
	_hoops_HSRSH *				next;
	Net_Rendition			_hoops_APHGA;
	Geometry const *		_hoops_RAI;	/* _hoops_IH _hoops_ASGC */
	_hoops_CRCP const *			_hoops_RRCIP;
	_hoops_HICS			path;

	DC_Point				_hoops_GGIAR;
	float					rotation;
	float					_hoops_ACIGH;

	bool					_hoops_HSIPH;
	_hoops_GSRSH			type;
	RGBAS32					color;
};


struct _hoops_ISRSH {
	_hoops_ISRSH *				next;
	Net_Rendition			_hoops_APHGA;
	Geometry const *		_hoops_RAI;	/* _hoops_IH _hoops_ASGC */
	_hoops_CRCP const *			_hoops_RRCIP;
	_hoops_HICS			path;

	DC_Point				_hoops_GGIAR;
	_hoops_HIHSA *		_hoops_CSRSH;
	_hoops_PGCSR *	_hoops_HGCSR;

	bool					_hoops_HSIPH;
};


struct _hoops_SSRSH {
	_hoops_SSRSH *				next;
	Net_Rendition			_hoops_APHGA;
	Geometry const *		_hoops_RAI;	/* _hoops_IH _hoops_ASGC */
	_hoops_CRCP const *			_hoops_RRCIP;
	_hoops_HICS			path;

	DC_Point				_hoops_GGIAR;
	DC_Point				p1;
	_hoops_HHHSA *			_hoops_GGASH;

	bool					_hoops_HSIPH;	/* ? */
};


struct _hoops_RGASH {
	_hoops_RCRSH	*	_hoops_RCHHR;
	int				offset;
	float			xmin, xmax, ymin, ymax;
};

struct _hoops_AGASH {
	_hoops_AGASH *		_hoops_ICHSP;
	_hoops_AGASH *		_hoops_GHIIP;

	_hoops_RGASH *	_hoops_PGASH;
	_hoops_RCRSH *			_hoops_CPGCP;
	_hoops_RGASH *	current;

	_hoops_AGASH *		next;

	unsigned long			count;
	unsigned long			level;
	unsigned long			index;

	float					xmin, xmax, ymin, ymax;
};




struct _hoops_SGSGP {
	_hoops_AGASH *			root;
	_hoops_AGASH *			_hoops_HGASH;

	_hoops_RCRSH *				_hoops_CPGCP;

	_hoops_CCRSH *				_hoops_GPHGA;
	_hoops_SSRSH *					_hoops_GGPC;
	_hoops_HSRSH *					_hoops_IGASH;
	_hoops_ISRSH *					strings;

	_hoops_CCRSH	*				_hoops_CGASH;

	int							_hoops_APPH;
	int							_hoops_SGASH;
	int							polyline_count;
	int							_hoops_GRASH;

	float						_hoops_HARHA;
	float						_hoops_RRASH;
	int							_hoops_ARASH;
	int							_hoops_PRASH;

	Display_Context *			dc;

	Int_Rectangle				extent;
	bool						_hoops_HHPGR;
	bool						_hoops_HRASH;
	bool						_hoops_IRASH;
	bool						_hoops_GISHP;
};


End_HOOPS_Namespace;


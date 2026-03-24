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
 * $Id: obf_tmp.txt 1.102 2010-06-16 22:04:10 covey Exp $
 */

#ifndef _hoops_CHGSH

#ifndef _hoops_GRAGP	
#include "database.h"
#endif

Begin_HOOPS_Namespace

#define _hoops_HSISA				0.2f	/* _hoops_IPCP _hoops_CSCS _hoops_CCPCR _hoops_SIPIR */


typedef short _hoops_SHGSH;
#define HF_NONE							(_hoops_SHGSH)0x0000
#define HF_SLABBED						(_hoops_SHGSH)0x0001
#define HF_CHOPPED_START				(_hoops_SHGSH)0x0002
#define HF_CHOPPED_END					(_hoops_SHGSH)0x0004
#define HF_CHOPPED_MIDDLE				(_hoops_SHGSH)0x0008
#define HF_CHOPPED_ANY					(HF_CHOPPED_START|HF_CHOPPED_MIDDLE|HF_CHOPPED_END)
#define HF_CHOPPED_NEAR_START			(_hoops_SHGSH)0x0020
#define HF_CHOPPED_NEAR_END				(_hoops_SHGSH)0x0040
#define HF_ZSORT_BACKFACE				(_hoops_SHGSH)0x0080
#define HF_ZSORT_FRONTFACE				(_hoops_SHGSH)0x0100

#define _hoops_GIGSH(_hoops_RIGSH, _hoops_AIGSH) \
	((((_hoops_RIGSH) + (1<<ALIGNMENT) - 1) & ~((1<<ALIGNMENT) - 1))*_hoops_AIGSH)

#define _hoops_PIGSH(_hoops_HIGSH, _hoops_RIGSH) \
	((_hoops_HIGSH)+=_hoops_GIGSH((_hoops_RIGSH), 1))

struct _hoops_HARHH {
	unsigned char *			data;
	int						size;	
	_hoops_PHASP			_hoops_HSAI;
};

union _hoops_APHSA;

struct _hoops_SRHSA {
	_hoops_SRHSA *		next;
	Net_Rendition			_hoops_APHGA;		/* _hoops_IH _hoops_RGR _hoops_CPAP */
	_hoops_APHSA alter *		_hoops_GPHSA;		/* _hoops_RPP _hoops_ARGPR */
	DC_Point alter *		points;			/* _hoops_IRAP _hoops_IH _hoops_IIGSH _hoops_APSAR */	
	_hoops_HARHH *			_hoops_CHCSA;

	_hoops_ARPA					plane;			/* _hoops_IPPA _hoops_CGSSR (_hoops_SHPR _hoops_GC) */

	float					_hoops_RICR, _hoops_AICR;		
	float					xmin, xmax;			
	float					ymin, ymax;		

	int						count;			/* _hoops_PHI _hoops_IIGR _hoops_RSSA */
	short					type;			/* _hoops_IIGR _hoops_RH _hoops_CPAP */
	_hoops_PHASP			_hoops_HSAI;

};


struct _hoops_CASS {
	_hoops_CASS alter			*next, *prev, *_hoops_HPISA;
	_hoops_SRHSA alter *	_hoops_ASHSA;
	Integer32				values; /* _hoops_IGI _hoops_IH _hoops_GHCP _hoops_RGSP _hoops_ASPA _hoops_PPR _hoops_CIGSH _hoops_HPGR _hoops_HAGH _hoops_IACH */
	_hoops_SHGSH			flags;			
};


struct _hoops_CHAGH {
	_hoops_CASS *		_hoops_SIGSH;
	_hoops_SHCRP	_hoops_SRI;
	bool			_hoops_GCGSH;
};


/* _hoops_RAGA _hoops_PCCP _hoops_AASGR, _hoops_RGR _hoops_HRPR _hoops_ICGI _hoops_RH _hoops_HAHH _hoops_HPHS
   _hoops_IS _hoops_GRGPR _hoops_PCCP _hoops_IGGA _hoops_SCPH _hoops_GIAA _hoops_SCH */
struct _hoops_GPGCP {
	/* _hoops_CIHA _hoops_IIGR _hoops_RH _hoops_GHPAH _hoops_SGS _hoops_RGR _hoops_SCPH _hoops_IISA _hoops_HII.  0 <= _hoops_RCGSH < _hoops_GARI->_hoops_IIRGR */
	unsigned short	_hoops_HPGCP;		
	/* _hoops_SHI _hoops_HII _hoops_GHPAH'_hoops_GRI _hoops_SRS _hoops_GPHA _hoops_CIHA _hoops_IS _hoops_SCPH'_hoops_GRI _hoops_SRS _hoops_CIHA.  0 <= _hoops_ACGSH < _hoops_GARI->_hoops_IHHA[_hoops_RCGSH] */
	unsigned short	_hoops_IPGCP;		
	/* _hoops_SHI _hoops_HII _hoops_ACHAR _hoops_IS _hoops_GHPAH'_hoops_GRI _hoops_SRS _hoops_GPHA _hoops_CIHA.  0 <= _hoops_PCGSH < _hoops_GARI->_hoops_APSR */
	int		_hoops_PPGCP;		
};



typedef short _hoops_HCGSH;
#define _hoops_ICGSH					(_hoops_HCGSH)0x0000
#define _hoops_CCGSH		(_hoops_HCGSH)0x0001  
#define _hoops_SCGSH			(_hoops_HCGSH)0x0002  
#define _hoops_GSGSH			(_hoops_HCGSH)0x0004  

struct Hidden_Tristrip {
	Net_Rendition				_hoops_APHGA;		/* _hoops_IH _hoops_RGR _hoops_CPAP */
	Net_Rendition				_hoops_PARHH;	
	Tristrip const *			tristrips;
	float *						_hoops_SPGCP;
	_hoops_GPGCP *	_hoops_CPGCP;
	RGBAS32 *					_hoops_GHGCP;	/* _hoops_PSPP _hoops_IS _hoops_IGIR 2*_hoops_RSGSH */
	_hoops_RSSH *					params;
	int *						_hoops_AGHAR;	
	_hoops_ARPA*						_hoops_AARHH;
	_hoops_ARPA*						_hoops_RIACP;
	
	float						_hoops_GCSIP;			/* _hoops_PGPR _hoops_IH _hoops_CCSHP _hoops_CRHH */	
	Integer32					_hoops_IISIP;
	int							_hoops_AGH;		/* _hoops_ACHAA _hoops_PAR _hoops_PPSR _hoops_RPR, _hoops_CSHA _hoops_HRGR _hoops_RRPAR */
	int							_hoops_APPH;
	int							_hoops_GSSIP;
	_hoops_HCGSH		flags;	
	DC_Point					*_hoops_GHPCP;
};

struct _hoops_PGRCP {
	Net_Rendition				_hoops_APHGA;		/* _hoops_IH _hoops_RGR _hoops_CPAP */
	Net_Rendition				_hoops_PARHH;	
	Polymarker const *			_hoops_GIGPR;
	float *						_hoops_SPGCP;

	RGBAS32 *					_hoops_GHGCP;	/* _hoops_PSPP _hoops_IS _hoops_IGIR 2*_hoops_RSGSH */
	_hoops_RSSH *					params;
	int *						_hoops_AGHAR;	
	_hoops_ARPA*						_hoops_AARHH;
	_hoops_ARPA*						_hoops_RIACP;

	float						_hoops_GCSIP;			/* _hoops_PGPR _hoops_IH _hoops_CCSHP _hoops_CRHH */	
	Integer32					_hoops_IISIP;
	int							_hoops_AGH;		/* _hoops_ACHAA _hoops_PAR _hoops_PPSR _hoops_RPR, _hoops_CSHA _hoops_HRGR _hoops_RRPAR */
	int							point_count;
	int							_hoops_GSSIP;
	
	DC_Point					*_hoops_GHPCP;
};


struct _hoops_SISIP {
	Hidden_Tristrip **			data;	
	int							allocated;
	int							used;
};


#define _hoops_GHSIP 1024

typedef short _hoops_ASGSH;
#define _hoops_HHSIP	 (_hoops_ASGSH)0x0001

struct _hoops_CPSIP {
	Net_Rendition			nr;

	DC_Point alter *		points;
	RGBAS32 alter *			_hoops_HPHSA;
	RGBA alter *			rgba_colors;
	_hoops_ARPA alter *			planes;
	_hoops_RSSH alter *		params;

	Integer32				param_flags;
	Integer32				param_width;
	_hoops_SCHSA			_hoops_PHSIP; 
	Integer32				_hoops_IISIP;

	int						used;
	int						_hoops_RHSIP;

	_hoops_ASGSH		flags;

};




struct _hoops_ICHSA {
	bool *					_hoops_CCHSA;
};

struct _hoops_CAHSA {
	RGBAS32 alter *			_hoops_HPHSA;
	RGBA alter *			rgba_colors;
	_hoops_ARPA alter *			planes;
	_hoops_RSSH alter *		params;
	Integer32				param_width;
	Integer32				param_flags;
	_hoops_SCHSA			_hoops_RAGR; /* _hoops_CGHI _hoops_PGGA _hoops_IGIR _hoops_GHCA _hoops_IHSA _hoops_AHSGP */
};

struct _hoops_HIHSA {
	_hoops_HACC const *			text;	
	KName					_hoops_SIHSA;
	float					_hoops_RACSR;
	float					_hoops_GCHSA;
};

struct _hoops_HHHSA {
	void const * const *	rasters;	
	Driver_Color const *	contrast_color;	
	Image const *			db_image;	
	int						hoffset;
	Image_Format			format;
	int						row_bytes;
	int						pattern;
	int						_hoops_HIHI;
};

struct _hoops_GIHSA {
	_hoops_RAARP *		stencil;
	int						_hoops_HIHI;
};


struct _hoops_PSGSH {
	_hoops_CASS alter *			root;
	_hoops_CASS alter *			_hoops_HRSSA;
	int						count;
};



union _hoops_APHSA {
	_hoops_CAHSA		_hoops_HSGSH;
	_hoops_ICHSA	_hoops_HSGCP;
	_hoops_HHHSA				_hoops_CHHSA;
	_hoops_GIHSA			_hoops_AIHSA;
	_hoops_HIHSA		text_info;
	_hoops_PSGSH			_hoops_ISGSH;
};



/*
 * _hoops_RGR _hoops_CPCP _hoops_HRGR _hoops_SAPIA! - _hoops_ACGR _hoops_CPR _hoops_RCPA _hoops_GISP & _hoops_PGII _hoops_GPGP _hoops_SPCSA _hoops_SGH _hoops_SCH
 * _hoops_IS _hoops_PRPS _hoops_CIPIP _hoops_CGH _hoops_SHH _hoops_GGR _hoops_RIPS _hoops_CGPR _hoops_CPS _hoops_SHS _hoops_HRGR _hoops_SASPR.
 */
#define _hoops_IPHSA					(char)1
#define _hoops_IAHSA						(char)2
#define _hoops_ACHSA					(char)3
#define _hoops_HCHSA				(char)4
#define _hoops_HRCSA(type)		((char)(type) <= (char)_hoops_HCHSA)
#define _hoops_AHHSA						(char)5
#define _hoops_IARHH(type)	((char)(type) <= (char)_hoops_AHHSA)
#define _hoops_PHHSA					(char)6
#define _hoops_PCHSA					(char)7
#define _hoops_SHHSA					(char)8
#define _hoops_PIHSA						(char)9
#define _hoops_RCHSA						(char)10
#define _hoops_RIGCP					(char)11
#define _hoops_HIGCP				(char)12

/* _hoops_RGAR _hoops_IH _hoops_CSGSH */
#define _hoops_SSGSH				(char)13

#define _hoops_GGRSH(hidden)	(!_hoops_IARHH((hidden)->_hoops_ASHSA->type))

struct _hoops_RGRSH {
	float				_hoops_AGRSH, _hoops_PGRSH, _hoops_HGRSH, _hoops_HSHGA, _hoops_ISHGA, _hoops_CSHGA;
};

struct _hoops_IGRSH {
	DC_Point alter *	start;				/* _hoops_HSPP _hoops_PPSR _hoops_IIGR _hoops_ISHA */
	DC_Point alter *	end;
	float				x, y, z;	/* _hoops_SGSSR _hoops_PPSR _hoops_GPP _hoops_IPPA */
	float				t;			/* _hoops_IIGR _hoops_SGSSR _hoops_PPSR _hoops_CCA _hoops_GPCAR _hoops_IS
										   _hoops_GHC' _hoops_SGSSR _hoops_III _hoops_CGSSR */
	_hoops_RGRSH		equation;	/* _hoops_ISHA _hoops_CGSSR */
};

struct _hoops_CGRSH {
	_hoops_IGRSH			_hoops_SGRSH,   /* _hoops_HHAA _hoops_IPPA _hoops_CCA _hoops_SCIRA _hoops_RRHC +"_hoops_RA" */
						_hoops_GRRSH;  /* _hoops_HHAA _hoops_IPPA _hoops_CCA _hoops_SCIRA _hoops_RRHC -"_hoops_RA" */
	bool				_hoops_RRRSH;	   /* _hoops_IHPR _hoops_RPP _hoops_RRI _hoops_HSAR 2 _hoops_ARRSH _hoops_GSGI */
};

struct _hoops_PRRSH {
	_hoops_CGRSH		poly0,
						poly1;
	_hoops_RGRSH		_hoops_HRRSH;			/* _hoops_GHC' _hoops_SGSSR */
};

End_HOOPS_Namespace;

#define _hoops_CHGSH
#endif

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
 * $Id: obf_tmp.txt 1.122 2010-08-06 19:05:09 jason Exp $
 */

#ifndef _hoops_CIGCI
#include "driver.h"


class OGL_Master_Context;


struct OGLData;
typedef VList<OGLData *> OGLData_List;

struct HOGLData;
typedef VList<HOGLData *> _hoops_SIGCI;

Begin_HOOPS_Namespace

struct _hoops_GCGCI {
	float _hoops_HIIH;
	int _hoops_ISISR;
	int _hoops_RCGCI;
	int descent;
	int _hoops_ACGCI;

	LOGFONT _hoops_PCGCI;
	HFONT _hoops_HCGCI;

	long _hoops_ICGCI;

	float _hoops_PRPHA;
	long _hoops_CCGCI;

	int	_hoops_SCGCI;
	float _hoops_GSGCI;
	float _hoops_RSGCI;
	float _hoops_ASGCI;
	LOGFONT _hoops_PSGCI; 
	HFONT _hoops_HSGCI;
	int _hoops_ISGCI;
	int _hoops_CSGCI;
};


struct _hoops_SSGCI {
	HINSTANCE	_hoops_ACSRH;
	HINSTANCE	_hoops_HGRAH;
};

GLOBAL_DATA _hoops_SSGCI _hoops_GGRCI;
#	define _hoops_RCSRH(a) (_hoops_GGRCI.a)


struct _hoops_RGRCI {
	_hoops_RGRCI	   alter		*_hoops_AGRCI;
	Display_Context alter	*dc;
};


struct _hoops_PGRCI {
	_hoops_PGRCI			*_hoops_HGRCI;
	DWORD				_hoops_IGRCI;
	DWORD				_hoops_CGRCI;
	DWORD				_hoops_SGRCI;
	HPEN				_hoops_GRRCI;
	Line_Style			line_style;
	_hoops_RGRCI			*_hoops_AGRCI;
};


struct _hoops_RRRCI {
	_hoops_RRRCI					*_hoops_AGRCI;
	Display_Context const	*dc;
};


struct _hoops_ARRCI {
	_hoops_ARRCI					*_hoops_PRRCI;
	short						_hoops_HRRCI;
	int							_hoops_IRRCI;
	struct {
		COLORREF				_hoops_CRRCI;
		Integer32			_hoops_SRRCI;
		Driver_Color		_hoops_GARCI;
	}							_hoops_RARCI;
	Driver_Color			_hoops_AARCI;
	int							_hoops_PARCI;
	HBRUSH						_hoops_HARCI;
	_hoops_RRRCI					*_hoops_AGRCI;
};


struct _hoops_SGRRR {
	_hoops_SGRRR	*next;
	LOGFONT				_hoops_PCGCI;
	char				*name;
	char				*specific;
	float				_hoops_IARCI;
	float				_hoops_IGGGH;
	float				_hoops_PRPHA;
	Integer32		_hoops_CARCI;
	_hoops_IHGRP	encoding;
};

struct _hoops_SARCI {
	LOGFONT const		*_hoops_GPRCI;
	long				_hoops_ACGCI;
	float				_hoops_PRPHA;
	void *				_hoops_RPRCI; /*_hoops_APRCI*/
};

struct _hoops_PPRCI {
	_hoops_PPRCI					*_hoops_AGRCI;
	Display_Context const	*dc;
};


struct _hoops_HPRCI {
	_hoops_HPRCI			*_hoops_IPRCI;
	HFONT				_hoops_CPRCI;
	LOGFONT const		*_hoops_GPRCI;
	long				_hoops_CIRHH;
	long				_hoops_SPRCI;
	float				width_scale;
	_hoops_PPRCI			*_hoops_AGRCI;
};

//#_hoops_PPIP _hoops_GHRCI
#ifdef _hoops_RHRCI
struct _hoops_AHRCI {
	HINSTANCE					_hoops_HPGGH;
	FARPROC						_hoops_APRPR;
	int							count;
	_hoops_AHRCI			**backlink,
								*next;
};
#endif


typedef enum {
	_hoops_PHRCI		= 0,
	_hoops_GGARI		= 1,
	_hoops_RGARI		= 2,
	_hoops_HHRCI		= 3,
	_hoops_IHRCI		= 4,
	_hoops_CHRCI		= 5,
	_hoops_SHRCI		= 6,
	_hoops_GIRCI	= 7
} _hoops_RIRCI;





struct _hoops_RRPRH {
	_hoops_RIRCI							_hoops_SSRRI;

	char								_hoops_AIRCI[4096];
	char								_hoops_PIRCI[4096];
	HKEY								_hoops_HIRCI;

	/*
	 * _hoops_IIRCI _hoops_SGS _hoops_PAH _hoops_SHH _hoops_GCSP _hoops_HPP _hoops_HCR _hoops_SPGIA
	 * _hoops_IIGR _hoops_RH _hoops_HRCRH _hoops_RHPP.  _hoops_IPCP _hoops_IGRH _hoops_PAIA _hoops_CHR
	 * _hoops_CIRCI _hoops_HRRPI _hoops_CIPP.	_hoops_IPCP _hoops_III _hoops_PAIA _hoops_CHR
	 * _hoops_HAR, _hoops_HIH _hoops_CHR _hoops_PGPAA _hoops_IH _hoops_GSGAR.
	 */
	HBITMAP								*bit_patterns;
	
	/*
	 * _hoops_APGIP _hoops_CHR _hoops_GAGCI _hoops_PPR _hoops_RIRCP
	 */
	FARPROC								_hoops_SIRCI;
	FARPROC								_hoops_GCRCI;
	int									_hoops_RCRCI;

	HANDLE								_hoops_ACRCI;
	DWORD								_hoops_PCRCI;
	volatile bool						_hoops_HCRCI;

	FARPROC								_hoops_ICRCI;
	BOOL								_hoops_CCRCI;
	HWND								_hoops_SCRCI;

	char								_hoops_GSRCI[80];

	unsigned char						_hoops_RSRCI[8];

	/*
	 * _hoops_PS _hoops_RRP _hoops_IS _hoops_HSSRR _hoops_ASRCI _hoops_PPR _hoops_CSGSR _hoops_RSAHA _hoops_PSRCI
	 * _hoops_SPGIA - _hoops_IIH _hoops_CHR _hoops_HRSP _hoops_HSRCI _hoops_SGS _hoops_GGCA
	 */
	int									_hoops_ISRCI;
	int									_hoops_CSRCI;
	_hoops_PGRCI							_hoops_SSRCI;
	int									_hoops_GGACI;
	int									_hoops_RGACI;
	_hoops_ARRCI							_hoops_AGACI;
	int									_hoops_PGACI;
	int									_hoops_HGACI;
	_hoops_HPRCI							_hoops_IGACI;


	BOOL								_hoops_CGACI;

	bool								_hoops_SGACI;
	bool								_hoops_GRACI;
	bool								_hoops_RRACI;
	bool								d3d_hoops_class;

	/* _hoops_HHSSA _hoops_HRSAR _hoops_PIH */
	void								*d3d_shared_data;
	/* _hoops_HIHH _hoops_HRSAR _hoops_PIH */
	OGLData_List						*_hoops_ARACI;
	_hoops_SIGCI						*_hoops_PRACI;

	OGL_Master_Context *				_hoops_HRACI;
	_hoops_RPPGI			_hoops_IRACI;

#ifdef _hoops_RHRCI
	_hoops_AHRCI					*_hoops_CRACI;
#endif

	_hoops_SGRRR						*font_list;
};

End_HOOPS_Namespace;

#define _hoops_CIGCI	1
#endif /* _hoops_SRACI */

/*
 * Copyright (c) 1998 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.  Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.72 2010-12-06 22:05:41 jason Exp $
 */


/* 
 * _hoops_HGI _hoops_RPHRA _hoops_HRGR _hoops_IGI _hoops_IS _hoops_GSRS _hoops_APHRA _hoops_PGPP _hoops_GAPA _hoops_PGCR _hoops_ARH _hoops_IIGR _hoops_RRCPR 
 * _hoops_HSCAR.  _hoops_HHIGR _hoops_PPHRA _hoops_AGCR _hoops_PGPP _hoops_HPP _hoops_HPHRA _hoops_IPHRA _hoops_CPHRA _hoops_SGS _hoops_CHR _hoops_SPIP
 * _hoops_HII _hoops_RH _hoops_SPHRA.  _hoops_HSRR _hoops_RH _hoops_CSCS _hoops_GHHRA _hoops_RCAHR, _hoops_RHAC _hoops_PAH _hoops_RHHRA _hoops_RH 
 * _hoops_IPHRA _hoops_AHHRA _hoops_PHHRA _hoops_SGS _hoops_HRGR _hoops_HHPA _hoops_GPP _hoops_RH _hoops_HHHRA.  _hoops_ICAGR _hoops_AGGAR _hoops_SGS _hoops_CSAP _hoops_SCGR 
 * _hoops_CGPR _hoops_RGR _hoops_AHAC _hoops_CSAP _hoops_PHPH _hoops_HRGR _hoops_HPGR _hoops_IHHRA://_hoops_CHHRA._hoops_SHHRA._hoops_GIHRA/_hoops_SHHRA/_hoops_HCISR/_hoops_RIHRA-_hoops_AIHRA.
 * _hoops_GPGP _hoops_PIHRA, _hoops_RH _hoops_HIHRA "_hoops_IIHRA _hoops_CIHRA _hoops_IH _hoops_SIHRA _hoops_GCHRA" _hoops_GACC _hoops_SSCP _hoops_PCCP _hoops_RCHRA
 * _hoops_ARIP _hoops_GPP _hoops_RGR _hoops_ACHRA.  _hoops_PAGA _hoops_SGS _hoops_AGCR _hoops_PRCHR _hoops_PCHRA _hoops_HCHRA _hoops_SPR _hoops_IIGR _hoops_RH _hoops_SCHS
 * _hoops_PPR _hoops_GHGA _hoops_PCCP _hoops_SGSSR _hoops_IS _hoops_SCRI _hoops_ICHRA.  _hoops_PS _hoops_SGH _hoops_IRS _hoops_RPPR _hoops_HAGH
 * _hoops_CCHRA _hoops_ARI, _hoops_GGR _hoops_SGS _hoops_HRII _hoops_HSAR _hoops_SCHRA _hoops_HCHRA, _hoops_RGR _hoops_PCPH _hoops_GSHRA _hoops_IRS _hoops_HPRGR
 * _hoops_IPHRA _hoops_HHIS _hoops_HIH _hoops_RAIA _hoops_HAGH "_hoops_GGICR" _hoops_HRHAR _hoops_PPR _hoops_HPPA _hoops_API _hoops_RHSP
 * _hoops_RSHRA.
 */

#include "hoops.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "database.h"
#include "hpserror.h"
#include "adt.h"

/* _hoops_ASHRA _hoops_PSHRA._hoops_GGHR _hoops_ASSP'_hoops_RA _hoops_IPHR _hoops_HIS _hoops_SR'_hoops_GCPP _hoops_HGPR _hoops_IRS _hoops_CIAGR _hoops_CGSI _hoops_SR _hoops_RRP _hoops_ARI. */
#ifndef HCD_POINT
#  define HCD_POINT void
#endif

HC_INTERFACE Key HC_DQKInsert_Shell (
	const char		*segment,
	int				point_count,
	const HCD_POINT  *points,
	int				face_list_length,
	const int		*face_list) ;

HC_INTERFACE void HC_CDECL HC_DCompute_Optimized_Shell (
	int				in_point_count,
	const HCD_POINT *_hoops_HSHRA,
	const float		*_hoops_ISHRA,
	int				in_face_list_length,
	const int		*in_face_list,
	const char		*option_string,
	int				*out_point_count,
	HCD_POINT		*_hoops_CSHRA,
	int				*out_face_list_length,
	int				*out_face_list,
	int				*vertex_mapping,
	int				*face_mapping) ;

 


GLOBAL_FUNCTION void HC_CDECL _hoops_SSHRA(char *_hoops_GGIRA);


#if 0
#define _hoops_RGIRA	    /* _hoops_AGIRA _hoops_HSP _hoops_GSPHR _hoops_RRGR */
#endif
/* _hoops_HGI _hoops_RIHH _hoops_PIRA _hoops_HRGR _hoops_IGI _hoops_CGPR _hoops_PSCS _hoops_IPPA _hoops_GHSSR _hoops_IH _hoops_AAPI */
/* _hoops_IS _hoops_PRPS _hoops_RPP _hoops_IRS _hoops_HSSP'_hoops_GRI _hoops_IPPA _hoops_HRGR _hoops_APIP.  _hoops_CGP _hoops_RH _hoops_IPPA _hoops_PGIRA _hoops_CHR */
/* _hoops_CRGP _hoops_HSAR _hoops_RGR _hoops_PIRA, _hoops_RH _hoops_IPPA _hoops_HRGR _hoops_GHSAR _hoops_AIPH. */
#define _hoops_HGIRA 0.0000001
#define _hoops_IGIRA 0.0000001

/* _hoops_HGI _hoops_RIHH _hoops_PIRA _hoops_HRGR _hoops_IGI _hoops_CGPR _hoops_CGIRA _hoops_IGH _hoops_IRS _hoops_PPSR _hoops_HRGR _hoops_GPP _hoops_IRS _hoops_IPPA */
/* _hoops_PAR _hoops_PGAP _hoops_PPAP _hoops_SCH _hoops_HRGR _hoops_GPP.  _hoops_CGP _hoops_SGIRA _hoops_RH _hoops_IPPA _hoops_CGSSR _hoops_CCA _hoops_IRS _hoops_PPSR  */
/* _hoops_GRIRA _hoops_IRS _hoops_GHPP _hoops_GIAA _hoops_AGCR _hoops_HSH, _hoops_PSCR _hoops_RH _hoops_PPSR _hoops_HRGR _hoops_GHSAR _hoops_IS _hoops_SHH  */
/* _hoops_GPP _hoops_RH _hoops_IPPA. */
#define _hoops_RRIRA 0.0003
#define _hoops_ARIRA 0.0003

#define _hoops_PRIRA 0.000001
#define _hoops_HRIRA 0.000001

/* _hoops_CGP _hoops_RH _hoops_RCSA _hoops_GAPA _hoops_RH _hoops_ASGA _hoops_IIGR _hoops_PGCR _hoops_RSSI _hoops_IRIRA _hoops_RGR _hoops_PIRA
	_hoops_SCH _hoops_HRGR _hoops_GHSAR _hoops_IRS _hoops_ACIPR _hoops_ISHA */
#define _hoops_CRIRA 22.5



#if !(defined  (DISABLE_COMPUTE) || defined  (_hoops_SRIRA))


#if 0
/* _hoops_PPSR */
struct _hoops_APCIR {
	double		x, y, z;
};

struct _hoops_PPCIR {
	double		x, y, z;
};

/* _hoops_IPPA _hoops_CGSSR _hoops_GGR _hoops_RH _hoops_SRSGR _hoops_GAIRA + _hoops_HPGHR + _hoops_RAIRA + _hoops_APCAR = 0 */
struct _hoops_AAIRA {
	double	a, b, c, d;
};
#endif




/* _hoops_IASC _hoops_AHCRR */
struct _hoops_PAIRA {
     _hoops_APCIR	min, max; /* "_hoops_AHPA" _hoops_IRHS _hoops_IS _hoops_CRGC _hoops_SRHIR "_hoops_CGGPR" */
};






/* _hoops_SSSA _hoops_RH _hoops_IPPA _hoops_IIGR _hoops_IRS _hoops_HSSP. */
local  bool _hoops_HAIRA (
	int					count,
	_hoops_APCIR *			_hoops_IAIRA, 
	_hoops_AAIRA *			plane,
	double				_hoops_CAIRA) 
{
	/*
	* _hoops_IPCP 3 _hoops_AIAHR _hoops_RAIGR, _hoops_IHAC, _hoops_PPR _hoops_IHRPR _hoops_CHR _hoops_PIAHR _hoops_IS _hoops_RH
	* _hoops_HIAHR _hoops_IIGR _hoops_RH _hoops_IIAHR _hoops_IIGR _hoops_RH _hoops_HSSP _hoops_CIAA _hoops_RH _hoops_CIAHR, _hoops_SIAHR, _hoops_PPR
	* _hoops_HSHC _hoops_GHC, _hoops_GCAHR.
	* _hoops_HSRR _hoops_APRAR _hoops_RCAHR, _hoops_ACAHR _hoops_IS _hoops_PCAHR & _hoops_HCAHR (1_hoops_ICPC _hoops_ICAHR) _hoops_CCAHR. 513
	*/

	if (count < 3) 
		return false;

	/* _hoops_ARAS _hoops_AARI _hoops_RH _hoops_HSSP, _hoops_IGGC _hoops_SCAHR _hoops_HIAHR */

	/*
	* _hoops_IRS "_hoops_RHCH" _hoops_PPSR _hoops_HRGR _hoops_GACC _hoops_HPISR, _hoops_IS _hoops_IRHH _hoops_RH _hoops_IPPA '_hoops_GHGP' _hoops_RPPR
	* _hoops_RRI "_hoops_APIP" _hoops_CGPR _hoops_RH _hoops_HSSP _hoops_HRGR _hoops_GRAA-_hoops_HPSS.
	*/

	double	a = 0;
	double	b = 0;
	double	c = 0;

	_hoops_PPCIR _hoops_SAIRA;
	_hoops_SAIRA = _hoops_GPIRA::_hoops_CRGA;

	_hoops_APCIR const *	pl = _hoops_IAIRA;
	_hoops_APCIR const *	_hoops_RPIRA = pl + count - 1;
	do {
		a += (pl[0].y + pl[1].y) * (pl[1].z - pl[0].z);
		b += (pl[0].z + pl[1].z) * (pl[1].x - pl[0].x);
		c += (pl[0].x + pl[1].x) * (pl[1].y - pl[0].y);

		_hoops_SAIRA.x += pl[0].x;
		_hoops_SAIRA.y += pl[0].y;
		_hoops_SAIRA.z += pl[0].z;

	} _hoops_RGGA (++pl == _hoops_RPIRA);


	/* _hoops_IRAA _hoops_PICP _hoops_IIGR _hoops_RH _hoops_APIRA _hoops_PPSR, _hoops_PPR _hoops_IPS _hoops_IRS/_hoops_RCSR/_hoops_GSGGR _hoops_CRGR '_hoops_GSSR' */
	_hoops_APCIR const *	close = _hoops_IAIRA;

	_hoops_PPCIR	normal(
		a + (pl->y + close->y) * (close->z - pl->z),
		b + (pl->z + close->z) * (close->x - pl->x),
		c + (pl->x + close->x) * (close->y - pl->y));


	if (fabs(normal.x) < _hoops_CAIRA && fabs(normal.y) < _hoops_CAIRA && fabs(normal.z) < _hoops_CAIRA) {
		*plane = _hoops_PPIRA::_hoops_CRGA;
		return false;
	}

	/* _hoops_HPIRA _hoops_SPAAR _hoops_RH _hoops_AASHR */

	double len = normal.length();

	 /* "_hoops_CGH" _hoops_SHR _hoops_SHH */
	if (len > 1.0E-24) { 
		normal /= len;
		_hoops_APCIR _hoops_IPIRA = *pl + _hoops_SAIRA;
		_hoops_IPIRA /= (double)count;
		*plane = _hoops_AAIRA(normal, -(_hoops_IPIRA.x*normal.x + _hoops_IPIRA.y*normal.y + _hoops_IPIRA.z*normal.z));
		return true;
	}

	*plane = _hoops_PPIRA::_hoops_CRGA;
	return false;
}



/* _hoops_PAIGR _hoops_CPIRA _hoops_RH _hoops_SPIRA _hoops_GAPA _hoops_IRS _hoops_HSSP _hoops_PPR _hoops_IRS _hoops_IPPA */
#define _hoops_GHIRA		0
#define _hoops_RHIRA		1
#define _hoops_AHIRA	2
#define _hoops_PHIRA	3
 
/* _hoops_HPHS _hoops_AHCA _hoops_IRS _hoops_RRCPR _hoops_PIH _hoops_IHHA */
struct _hoops_HHIRA {
    int _hoops_IHIRA;		
    int _hoops_CHIRA;
    int _hoops_SHIRA;
    int _hoops_GIIRA;
};



/* _hoops_PPIP _hoops_IRS _hoops_HSSP _hoops_IH _hoops_SGH _hoops_HPP _hoops_RH _hoops_IPHRA _hoops_RIIRA. */
struct _hoops_AIIRA {             
    _hoops_APCIR *				_hoops_PIIRA;				/* _hoops_RSSA _hoops_GGR _hoops_RH _hoops_HSSP */                     
    _hoops_PPCIR *				_hoops_HIIRA;			/* _hoops_ASGA _hoops_IH _hoops_RH _hoops_RSSA */                    
    int *					_hoops_IIIRA;		/* _hoops_PPSR _hoops_PSPI _hoops_CRGR _hoops_RH _hoops_GIGR _hoops_PPSR _hoops_HIGR */
													/* _hoops_IH _hoops_RH _hoops_RSIR _hoops_CIIRA _hoops_RRCPR */          
	_hoops_HHIRA *			_hoops_SIIRA;			/* _hoops_GIGR _hoops_RRCPR _hoops_SIHC */
	_hoops_AIIRA *			_hoops_GCIRA;				/* _hoops_RSSA _hoops_IS _hoops_IRS _hoops_HSSP _hoops_HHGP _hoops_HII _hoops_RGR _hoops_SPR */
	_hoops_AIIRA *			_hoops_RCIRA;				/* _hoops_RSSA _hoops_IS _hoops_RH _hoops_RII _hoops_HSSP _hoops_HHGP */
	_hoops_AIIRA *			_hoops_ACIRA;				/* _hoops_RSSA _hoops_IS _hoops_PCIRA (_hoops_RPP _hoops_SPR _hoops_HICP) */
	POINTER_SIZED_INT *		_hoops_HCIRA;	/* _hoops_CCAH _hoops_GPHA _hoops_PSPI _hoops_PGAP _hoops_PPIP _hoops_RH _hoops_HSSP (_hoops_RPP _hoops_GII)*/
    int 					_hoops_ICIRA;			/* _hoops_PHI _hoops_IIGR _hoops_RSSA. */                         
                                                                   
    int 					_hoops_CCIRA;			/* _hoops_GIGR _hoops_RRCPR _hoops_HSP _hoops_PHI _hoops_IH _hoops_RGR _hoops_SCIRA */  
	int						_hoops_GSIRA;				/* _hoops_CCAH _hoops_HSP _hoops_PHI */
	int						_hoops_RSIRA;				/* _hoops_PHI _hoops_IIGR _hoops_ASIRA _hoops_IIAC _hoops_IS _hoops_RH _hoops_GIGR _hoops_HSP */

	int						_hoops_PSIRA;				/* _hoops_SPCC _hoops_IIGR _hoops_ARRS _hoops_CRPR */
    _hoops_AAIRA 					_hoops_HSIRA;				/* _hoops_RH _hoops_IPPA _hoops_SGS _hoops_ICGI _hoops_RGR _hoops_HSSP */
    bool 					_hoops_ISIRA;				/* _hoops_RPP _hoops_IHPR, _hoops_PSCR _hoops_RGR _hoops_HSSP _hoops_HRGR _hoops_SIGC */
													/* _hoops_GGR _hoops_RH _hoops_RSGR _hoops_GHPP _hoops_IIGR _hoops_AIHGR _hoops_PGPP. */
    RGB 					_hoops_CSIRA;				/* _hoops_HSSP _hoops_HAIR. */
    bool 					_hoops_SSIRA;			/* _hoops_ARP _hoops_IIHA _hoops_GPP _hoops_RH _hoops_SCHS _hoops_HSP _hoops_HPRC _hoops_SGI */
    bool 					_hoops_GGCRA;				/* _hoops_RGR _hoops_RIP _hoops_HRGR _hoops_ARP _hoops_IHPR _hoops_RPP _hoops_RH _hoops_HSSP _hoops_CGH */
													/* _hoops_SHH _hoops_IAIH _hoops_RHSP _hoops_APHRA _hoops_PGPP. _hoops_HGI _hoops_HRGR _hoops_ARP */
													/* _hoops_HPP _hoops_GGSGR _hoops_IIGR _hoops_RH _hoops_IASC _hoops_RGCRA _hoops_IH _hoops_CII _hoops_PPR _hoops_HCSS, */
													/* _hoops_PPR _hoops_HRGR _hoops_IGI _hoops_IS _hoops_IRHH _hoops_RH _hoops_PGPP _hoops_RRI _hoops_AGCRA  */
													/* _hoops_HPP _hoops_HAPP _hoops_AAPI _hoops_SGS _hoops_CHR _hoops_HAR _hoops_SSPP _hoops_PGCRA */
													/* _hoops_GGR _hoops_RH _hoops_CAIH.	 */

};


/* _hoops_HGI _hoops_PPARR _hoops_PRCHR _hoops_ISCP _hoops_GHCS _hoops_HGCRA, _hoops_GAR _hoops_PRAR _hoops_GAR _hoops_IRS _hoops_CIAGR _hoops_RII _hoops_SCSHR _hoops_IIGR _hoops_PSIGA _hoops_HPHS. */
struct  _hoops_IGCRA {
	_hoops_AIGPR *	_hoops_RIGC;
	_hoops_PAIRA		_hoops_CGCRA;			/* _hoops_IASC _hoops_HPHS _hoops_IH _hoops_RH _hoops_SGCRA */
	_hoops_PAIRA		_hoops_GRCRA;		/* _hoops_IASC _hoops_HPHS _hoops_IH _hoops_RH _hoops_SAAP */
	int 					_hoops_RRCRA;		/* _hoops_HRGR _hoops_RGR _hoops_IRS _hoops_ICHRA, _hoops_HIPRA, _hoops_PAR _hoops_ARCRA? */
	bool 					_hoops_PRCRA;		/* _hoops_IHPR _hoops_IS _hoops_SGGC _hoops_GHPP _hoops_AAPI, _hoops_RCPP */
	/* _hoops_IS _hoops_SHSP _hoops_GAR _hoops_HRCRA _hoops_HPP _hoops_RH _hoops_HSSAR _hoops_CPHRA. */

	_hoops_AIIRA  *		_hoops_IRCRA;			/* _hoops_CASPR _hoops_ICGAR _hoops_IH _hoops_AAPI */
	int 				_hoops_CRCRA;   	 

	_hoops_APCIR *			_hoops_SRCRA;			/* _hoops_CASPR _hoops_ICGAR _hoops_IH _hoops_RSSA _hoops_GGR _hoops_ARH _hoops_IIGR 3 */
	int 				_hoops_GACRA;

	_hoops_APCIR *			_hoops_RACRA;			/* _hoops_CASPR _hoops_ICGAR _hoops_IH _hoops_RSSA _hoops_GGR _hoops_ARH _hoops_IIGR 4 */
	int 				_hoops_AACRA;

	_hoops_PPCIR *			_hoops_PACRA;			/* _hoops_CASPR _hoops_ICGAR _hoops_IH _hoops_AAGA _hoops_GGR _hoops_ARH _hoops_IIGR 3 */
	int 				_hoops_HACRA;

	_hoops_PPCIR *			_hoops_IACRA;			/* _hoops_CASPR _hoops_ICGAR _hoops_IH _hoops_AAGA _hoops_GGR _hoops_ARH _hoops_IIGR 4 */
	int 				_hoops_CACRA;

	int *				_hoops_SACRA;			/* _hoops_CASPR _hoops_ICGAR _hoops_IH _hoops_PPSR _hoops_PPISR, _hoops_ARH _hoops_IIGR 3 */
	int 				_hoops_GPCRA;

	int *				_hoops_RPCRA;			/* _hoops_CASPR _hoops_ICGAR _hoops_IH _hoops_PPSR _hoops_PPISR, _hoops_ARH _hoops_IIGR 4 */
	int 				_hoops_APCRA;
};


typedef VList<_hoops_AIIRA *> _hoops_PPCRA;

typedef VHash<_hoops_AIIRA *, _hoops_AIIRA *> _hoops_HPCRA;


struct _hoops_IPCRA;

/* _hoops_SCIA _hoops_PAPA _hoops_IIGR _hoops_IRS _hoops_IPHRA _hoops_AHHRA */
struct _hoops_CPCRA {
	_hoops_PPCRA *	_hoops_SPCRA;		/* _hoops_AAPI _hoops_GGR _hoops_RH _hoops_IPHRA _hoops_HHIS */
	_hoops_IPCRA *			_hoops_GHCRA;		/* _hoops_SRRPR _hoops_RHCRA */
	_hoops_HHIRA *		_hoops_SIIRA;	    /* _hoops_HPHS _hoops_IH _hoops_CIIRA _hoops_RRCPR */
};

/* _hoops_GIIS _hoops_IIGR _hoops_IRS _hoops_IPHRA _hoops_HHIS */
struct _hoops_IPCRA {
	_hoops_IPCRA *			_hoops_GCIRA;		    /* _hoops_AIIS _hoops_GGR "_hoops_RIPS" _hoops_IIGR _hoops_RGR _hoops_GIIS */
	_hoops_IPCRA *			_hoops_RCIRA;		    /* _hoops_AIIS _hoops_GGR "_hoops_ISSC" _hoops_IIGR _hoops_RGR _hoops_GIIS */
	_hoops_AAIRA				_hoops_AHCRA;	    /* _hoops_PHCRA _hoops_IPPA _hoops_IH _hoops_RGR _hoops_GIIS */
	_hoops_PPCRA *	_hoops_SPCRA;		/* _hoops_HIGR _hoops_IIGR _hoops_AAPI _hoops_ASPSR _hoops_IS _hoops_RGR _hoops_GIIS */
	_hoops_CPCRA *			_hoops_HHCRA;			/* _hoops_CRS _hoops_IS _hoops_PCIRA _hoops_IPHRA _hoops_AHHRA */
};



/* _hoops_IHCRA _hoops_HCGC _hoops_RPP _hoops_RH _hoops_SCGR _hoops_HSP/_hoops_HSSP _hoops_GGR _hoops_RH _hoops_HHIS _hoops_IGICR _hoops_RAS _hoops_CHCRA.
     _hoops_CGP _hoops_SCH _hoops_RHAP, _hoops_SR _hoops_SSPC _hoops_RGCI _hoops_RASI.
	 _hoops_CGP _hoops_SCH _hoops_ASSP'_hoops_RA, _hoops_SR _hoops_IHSH _hoops_HPGR _hoops_RGCI _hoops_RASI (_hoops_RPP _hoops_GII) */
local void _hoops_SHCRA (_hoops_AIIRA *_hoops_GICRA, int *_hoops_RICRA, _hoops_PPCRA *face_list) {
	if (_hoops_RICRA[_hoops_GICRA->_hoops_GSIRA] == _hoops_GICRA->_hoops_GSIRA)
		face_list->AddLast(_hoops_GICRA);
	else if (_hoops_GICRA->_hoops_GCIRA)
		_hoops_SHCRA(_hoops_GICRA->_hoops_GCIRA, _hoops_RICRA, face_list);
	else if (_hoops_GICRA->_hoops_RCIRA)
		_hoops_SHCRA(_hoops_GICRA->_hoops_RCIRA, _hoops_RICRA, face_list);
}

/* _hoops_AHGHR _hoops_IRS _hoops_HSP/_hoops_HSSP, _hoops_SR _hoops_SPIC _hoops_ISHP _hoops_ISCP _hoops_HHIS _hoops_PPR _hoops_SRPS _hoops_RH _hoops_CCAH _hoops_GIHA */
local void _hoops_AICRA (_hoops_AIIRA *_hoops_SCAAR, _hoops_AIIRA *_hoops_GICRA, int *_hoops_PICRA, _hoops_HICRA *vertices, _hoops_IICRA *_hoops_CICRA) {
	int i;
	if (_hoops_SCAAR != _hoops_GICRA) {
		if (_hoops_SCAAR->_hoops_GCIRA)
			_hoops_AICRA(_hoops_SCAAR->_hoops_GCIRA, _hoops_GICRA, _hoops_PICRA, vertices, _hoops_CICRA);
		if (_hoops_SCAAR->_hoops_RCIRA)
			_hoops_AICRA(_hoops_SCAAR->_hoops_RCIRA, _hoops_GICRA, _hoops_PICRA, vertices, _hoops_CICRA);
	}
	
	for (i = 0 ; i < _hoops_SCAAR->_hoops_PSIRA ; i++) {
		POINTER_SIZED_INT _hoops_SICRA = _hoops_PICRA[_hoops_SCAAR->_hoops_HCIRA[i]];
		if (_hoops_SICRA != -1) {

			_hoops_HICRA::status result = vertices->LookupItem(_hoops_SICRA);

			if (result == _hoops_HICRA::Failed) {
				vertices->InsertItem(_hoops_SICRA);
				/* _hoops_SR'_hoops_GCPP _hoops_GGCR _hoops_SPR _hoops_IS _hoops_RH _hoops_RHGS _hoops_GPHA _hoops_CIHA _hoops_HIS _hoops_SGS _hoops_SR _hoops_PAH _hoops_GRPR _hoops_GAPA
					_hoops_IRS _hoops_AHHR _hoops_CIHA _hoops_PPR _hoops_IRS _hoops_IRAP _hoops_PIRA _hoops_GIIA _hoops_CGPR _hoops_RHAC _hoops_RHHR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_HIGR */
				_hoops_CICRA->AddLast(_hoops_SCAAR->_hoops_HCIRA[i]+1);
			}
		}
	}
}

/* _hoops_SSSA _hoops_RCSA _hoops_GAPA _hoops_PSPAR */
local double _hoops_GCCRA (_hoops_PPCIR *_hoops_ISPI, _hoops_PPCIR *_hoops_CSPI) {
	double _hoops_RCCRA = _hoops_ISPI->length();
	double _hoops_ACCRA = _hoops_CSPI->length();
	double _hoops_PCCRA = _hoops_ISPI->_hoops_SSRP(*_hoops_CSPI);
	return _hoops_ISSSR(_hoops_PCCRA / (_hoops_RCCRA * _hoops_ACCRA));
}


typedef VHash<POINTER_SIZED_INT, _hoops_APCIR *> _hoops_HCCRA;
typedef VHash<POINTER_SIZED_INT, _hoops_PPCIR *> _hoops_ICCRA;

/* _hoops_AHGHR _hoops_IRS _hoops_HSP/_hoops_HSSP _hoops_PPR _hoops_SCH'_hoops_GRI _hoops_CCAH _hoops_GIHA, _hoops_GRAS _hoops_GPHA _hoops_ASGA _hoops_IH _hoops_RH _hoops_CCAH _hoops_GIHA */
local void _hoops_CCCRA (
	_hoops_AIIRA *						_hoops_GICRA, 
	_hoops_HICRA::PairList *	vertices, 
	Point **							_hoops_SCCRA, 
	int *								_hoops_GSCRA, 
	int **								face_list, 
	_hoops_ICCRA *						_hoops_RSCRA, 
	_hoops_HICRA *			_hoops_HCIRA) 
{
	int face_count = 0;
	int	_hoops_HHHHR;
	int i = 0;

	while (face_count < _hoops_GICRA->_hoops_GSIRA) {
		_hoops_HHHHR = (*face_list)[i];
		i += _hoops_HHHHR + 1;
		face_count++;
	}
	int	_hoops_ASCRA = i + 1;
	_hoops_HHHHR = (*face_list)[i]; 

	_hoops_HICRA::Pair *	_hoops_PSCRA;
	vertices->ResetCursor();	
	for (_hoops_PSCRA = vertices->PeekFirst() ; _hoops_PSCRA != null ; _hoops_PSCRA = vertices->PeekCursor()) {
		POINTER_SIZED_INT	_hoops_HCGS = _hoops_PSCRA->Key();

		Point	vertex = (*_hoops_SCCRA)[_hoops_HCGS];

		_hoops_PPCIR *	_hoops_GGPHR;
		ALLOC(_hoops_GGPHR, _hoops_PPCIR);

		/* _hoops_SR _hoops_SPIC _hoops_GH _hoops_RH _hoops_IPHRA _hoops_IS _hoops_SSS _hoops_RH _hoops_GIGR _hoops_HSP _hoops_HII _hoops_PGAP _hoops_RGR _hoops_HSP _hoops_CSAP _hoops_HHGP _hoops_PSAP */
		_hoops_AIIRA *	_hoops_HSCRA = _hoops_GICRA;
		while (_hoops_HSCRA->_hoops_ACIRA)
			_hoops_HSCRA = _hoops_HSCRA->_hoops_ACIRA;

		/* _hoops_SR _hoops_GRAS _hoops_IRS _hoops_ISCRA _hoops_AASHR _hoops_IIGR _hoops_RH _hoops_RII _hoops_GPHA _hoops_ASGA _hoops_IS _hoops_GRAS _hoops_ISCP _hoops_CCAH _hoops_GSSR */
		*_hoops_GGPHR = _hoops_GPIRA::_hoops_CRGA;

		for (int i = 0 ; i < _hoops_HSCRA->_hoops_ICIRA ; i++) {
			_hoops_PPCIR _hoops_CSCRA = _hoops_HSCRA->_hoops_PIIRA[i] - vertex;
			*_hoops_GGPHR += _hoops_HSCRA->_hoops_HIIRA[i] / _hoops_CSCRA.length();
		}

		_hoops_GGPHR->_hoops_AAIAR();

		/* _hoops_AGGA _hoops_SR _hoops_ISPR _hoops_IS _hoops_CACH _hoops_RSH _hoops_IS _hoops_RGHH _hoops_RGR _hoops_CCAH _hoops_GPHA _hoops_GSSR, _hoops_RAGA _hoops_SGS _hoops_SR _hoops_GHCA _hoops_HS _hoops_RII _hoops_HAGH
			_hoops_RSSI _hoops_ICAS _hoops_RGR _hoops_PSHR _hoops_GPHA */
		do { 
			_hoops_PPCIR *_hoops_SSCRA;
			vhash_status_t result; 

			/* _hoops_PHAA _hoops_SR _hoops_ISPR _hoops_RPP _hoops_SR _hoops_PRGI _hoops_HS _hoops_GII _hoops_RII _hoops_ASGA _hoops_IH _hoops_RGR _hoops_GPHA, _hoops_RPP _hoops_HAR _hoops_SR _hoops_GGCR
				_hoops_RH _hoops_SPR _hoops_SR _hoops_SAHR _hoops_GGSRA */ 
			result = _hoops_RSCRA->LookupItem(_hoops_HCGS, &_hoops_SSCRA);
			if (result == VHASH_STATUS_FAILED) { 
				ALLOC(_hoops_SSCRA, _hoops_PPCIR);
				*_hoops_SSCRA = _hoops_PPCIR(_hoops_GICRA->_hoops_HSIRA);
				_hoops_RSCRA->InsertItem(_hoops_HCGS, _hoops_SSCRA);
				_hoops_RSCRA->InsertItem(_hoops_HCGS, _hoops_GGPHR);
				_hoops_HCIRA->InsertItem(_hoops_HCGS, -1);
				break;
			}
			else {
				/* _hoops_PS _hoops_AA _hoops_HS _hoops_RII _hoops_ASGA _hoops_IH _hoops_RGR _hoops_GPHA, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IS _hoops_CACH _hoops_RPP _hoops_AGAP _hoops_RCPS _hoops_HII _hoops_RSSI/_hoops_GHC
					_hoops_SR _hoops_CGH _hoops_IAIC, _hoops_HAS._hoops_IAS., _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_IRS _hoops_ACIPR _hoops_ISHA _hoops_HIS _hoops_SR _hoops_PAH "_hoops_RGSRA" _hoops_RH _hoops_ASGA,
					_hoops_PAR _hoops_RPP _hoops_SR _hoops_CGH _hoops_IRHH _hoops_IRS _hoops_CCAH _hoops_GPHA, _hoops_HAS._hoops_IAS., _hoops_SR'_hoops_RISP _hoops_GGHP _hoops_IRS _hoops_ACIPR _hoops_ISHA */
				_hoops_PPCIR _hoops_AGSRA = _hoops_PPCIR(_hoops_GICRA->_hoops_HSIRA);

				if (_hoops_GCCRA(_hoops_SSCRA, &_hoops_AGSRA) > _hoops_CRIRA) {
					POINTER_SIZED_INT _hoops_PGSRA;
					_hoops_HCIRA->LookupItem(_hoops_HCGS, &_hoops_PGSRA);
					if (_hoops_PGSRA == -1) {
						_hoops_HCIRA->RemoveItem(_hoops_HCGS, &_hoops_PGSRA);
						_hoops_HCIRA->InsertItem(_hoops_HCGS, *_hoops_GSCRA);

						(*_hoops_SCCRA)[*_hoops_GSCRA] = (*_hoops_SCCRA)[_hoops_HCGS];
						
						for (int i = _hoops_ASCRA ; i < (_hoops_ASCRA + _hoops_HHHHR) ; i++) {
							if ((*face_list)[i] == _hoops_HCGS)
								(*face_list)[i] = *_hoops_GSCRA;
						}

						_hoops_HCGS = *_hoops_GSCRA;
						(*_hoops_GSCRA)++;
					}
					else
						_hoops_HCGS = _hoops_PGSRA;
				}
				else {
					_hoops_RSCRA->InsertItem(_hoops_HCGS, _hoops_GGPHR);
					break;
				}
			}
		} while (1);

		vertices->AdvanceCursor();
	}
}

/* _hoops_HGSRA _hoops_CSPP _hoops_IIGR _hoops_RH _hoops_ARRS _hoops_API */
/* _hoops_AHGHR _hoops_IRS _hoops_HSP/_hoops_HSSP _hoops_PPR _hoops_SCH'_hoops_GRI _hoops_CCAH _hoops_GIHA, _hoops_GRAS _hoops_GPHA _hoops_ASGA _hoops_IH _hoops_RH _hoops_CCAH _hoops_GIHA */
local void _hoops_IGSRA (
	_hoops_AIIRA *						_hoops_GICRA, 
	_hoops_HICRA::PairList *	vertices, 
	_hoops_APCIR **							_hoops_SCCRA, 
	int *								_hoops_GSCRA, 
	int **								face_list, 
	_hoops_ICCRA *						_hoops_RSCRA, 
	_hoops_HICRA *			_hoops_HCIRA) 
{
	_hoops_HICRA::Pair * _hoops_PSCRA;
	int face_count = 0;
	int _hoops_HHHHR;
	int i = 0;
	while (face_count < _hoops_GICRA->_hoops_GSIRA) {
		_hoops_HHHHR = (*face_list)[i];
		i += _hoops_HHHHR + 1;
		face_count++;
	}
	int _hoops_ASCRA = i + 1;
	_hoops_HHHHR = (*face_list)[i];

	vertices->ResetCursor();	
	for (_hoops_PSCRA = vertices->PeekFirst() ; _hoops_PSCRA != null ; _hoops_PSCRA = vertices->PeekCursor()) {
		POINTER_SIZED_INT _hoops_HCGS = _hoops_PSCRA->Key();
		
		_hoops_APCIR	vertex = (*_hoops_SCCRA)[_hoops_HCGS];

		_hoops_PPCIR *	_hoops_GGPHR;
		ZALLOC(_hoops_GGPHR, _hoops_PPCIR);

		/* _hoops_SR _hoops_SPIC _hoops_GH _hoops_RH _hoops_IPHRA _hoops_IS _hoops_SSS _hoops_RH _hoops_GIGR _hoops_HSP _hoops_HII _hoops_PGAP _hoops_RGR _hoops_HSP _hoops_CSAP _hoops_HHGP _hoops_PSAP */
		_hoops_AIIRA *	_hoops_HSCRA = _hoops_GICRA;
		while (_hoops_HSCRA->_hoops_ACIRA)
			_hoops_HSCRA = _hoops_HSCRA->_hoops_ACIRA;

		/* _hoops_SR _hoops_GRAS _hoops_IRS _hoops_ISCRA _hoops_AASHR _hoops_IIGR _hoops_RH _hoops_RII _hoops_GPHA _hoops_ASGA _hoops_IS _hoops_GRAS _hoops_ISCP _hoops_CCAH _hoops_GSSR */
		for (int i = 0 ; i < _hoops_HSCRA->_hoops_ICIRA ; i++) {
			_hoops_PPCIR _hoops_CSCRA = _hoops_HSCRA->_hoops_PIIRA[i] - vertex;
			*_hoops_GGPHR += _hoops_HSCRA->_hoops_HIIRA[i] / _hoops_CSCRA.length();
		}

		_hoops_GGPHR->_hoops_AAIAR();

		/* _hoops_AGGA _hoops_SR _hoops_ISPR _hoops_IS _hoops_CACH _hoops_RSH _hoops_IS _hoops_RGHH _hoops_RGR _hoops_CCAH _hoops_GPHA _hoops_GSSR, _hoops_RAGA _hoops_SGS _hoops_SR _hoops_GHCA _hoops_HS _hoops_RII _hoops_HAGH
			_hoops_RSSI _hoops_ICAS _hoops_RGR _hoops_PSHR _hoops_GPHA */
		do { 
			_hoops_PPCIR *	_hoops_SSCRA;

			/* _hoops_PHAA _hoops_SR _hoops_ISPR _hoops_RPP _hoops_SR _hoops_PRGI _hoops_HS _hoops_GII _hoops_RII _hoops_ASGA _hoops_IH _hoops_RGR _hoops_GPHA, _hoops_RPP _hoops_HAR _hoops_SR _hoops_GGCR
				_hoops_RH _hoops_SPR _hoops_SR _hoops_SAHR _hoops_GGSRA */ 
			_hoops_HCCRA::status result = _hoops_RSCRA->LookupItem(_hoops_HCGS, &_hoops_SSCRA);

			if (result == _hoops_HCCRA::Failed) { 
				ALLOC(_hoops_SSCRA, _hoops_PPCIR);
				*_hoops_SSCRA = _hoops_PPCIR(_hoops_GICRA->_hoops_HSIRA);
				_hoops_RSCRA->InsertItem(_hoops_HCGS, _hoops_SSCRA);
				_hoops_RSCRA->InsertItem(_hoops_HCGS, _hoops_GGPHR);
				_hoops_HCIRA->InsertItem(_hoops_HCGS, -1);
				break;
			}
			else {
				/* _hoops_PS _hoops_AA _hoops_HS _hoops_RII _hoops_ASGA _hoops_IH _hoops_RGR _hoops_GPHA, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IS _hoops_CACH _hoops_RPP _hoops_AGAP _hoops_RCPS _hoops_HII _hoops_RSSI/_hoops_GHC
					_hoops_SR _hoops_CGH _hoops_IAIC, _hoops_HAS._hoops_IAS., _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_IRS _hoops_ACIPR _hoops_ISHA _hoops_HIS _hoops_SR _hoops_PAH "_hoops_RGSRA" _hoops_RH _hoops_ASGA,
					_hoops_PAR _hoops_RPP _hoops_SR _hoops_CGH _hoops_IRHH _hoops_IRS _hoops_CCAH _hoops_GPHA, _hoops_HAS._hoops_IAS., _hoops_SR'_hoops_RISP _hoops_GGHP _hoops_IRS _hoops_ACIPR _hoops_ISHA */
				_hoops_PPCIR _hoops_AGSRA = _hoops_PPCIR(_hoops_GICRA->_hoops_HSIRA);
				if (_hoops_GCCRA(_hoops_SSCRA, &_hoops_AGSRA) > _hoops_CRIRA) {
					POINTER_SIZED_INT _hoops_PGSRA;
					_hoops_HCIRA->LookupItem(_hoops_HCGS, &_hoops_PGSRA);
					if (_hoops_PGSRA == -1) {
						_hoops_HCIRA->RemoveItem(_hoops_HCGS, &_hoops_PGSRA);
						_hoops_HCIRA->InsertItem(_hoops_HCGS, *_hoops_GSCRA);

						(*_hoops_SCCRA)[*_hoops_GSCRA] = (*_hoops_SCCRA)[_hoops_HCGS];
						
						for (int i = _hoops_ASCRA ; i < (_hoops_ASCRA + _hoops_HHHHR) ; i++) {
							if ((*face_list)[i] == _hoops_HCGS)
								(*face_list)[i] = *_hoops_GSCRA;
						}

						_hoops_HCGS = *_hoops_GSCRA;
						(*_hoops_GSCRA)++;
					}
					else
						_hoops_HCGS = (POINTER_SIZED_INT)_hoops_PGSRA;
				}
				else {
					_hoops_RSCRA->InsertItem(_hoops_HCGS, _hoops_GGPHR);
					break;
				}
			}
		} while (1);

		vertices->AdvanceCursor();
	}
}

/* _hoops_GPGP _hoops_AGR _hoops_IS _hoops_SRCH _hoops_PPGS _hoops_SHCS, _hoops_SR _hoops_HGSR _hoops_RSPHR _hoops_HGCRA _hoops_IIGR _hoops_AGRR _hoops_AGSAR */
/* _hoops_SGS _hoops_SR _hoops_PAH _hoops_SGH, _hoops_PPR _hoops_SGH _hoops_GRH _hoops_CGSRA _hoops_CIGR _hoops_IS _hoops_HGCR _hoops_CAPR _hoops_PPR _hoops_CIH _hoops_CAPR. */
#define	    _hoops_SGSRA 	8000
#define	    _hoops_GRSRA 	12000
#define	    _hoops_RRSRA 	9000
#define	    _hoops_ARSRA 	80000
#define	    _hoops_PRSRA 	60000
		 
					    			    	
local INLINE void _hoops_HRSRA(_hoops_AIIRA ** p, _hoops_IGCRA * _hoops_IRSRA)
{
	if (_hoops_IRSRA->_hoops_CRCRA >= _hoops_SGSRA)
		ALLOC(*p, _hoops_AIIRA);
	else
		*p = &_hoops_IRSRA->_hoops_IRCRA[_hoops_IRSRA->_hoops_CRCRA++];	
}

			
local INLINE void _hoops_CRSRA(_hoops_AIIRA * p, _hoops_IGCRA * _hoops_IRSRA)
{
	if (_hoops_IRSRA->_hoops_CRCRA >= _hoops_SGSRA) {
		if (p < _hoops_IRSRA->_hoops_IRCRA || p >= &_hoops_IRSRA->_hoops_IRCRA[_hoops_SGSRA])
			FREE(p, _hoops_AIIRA);
	}
}
			 
			
local INLINE void _hoops_SRSRA(_hoops_APCIR ** p, int _hoops_GPIGR, _hoops_IGCRA * _hoops_IRSRA) 
{
	if (_hoops_GPIGR == 3)  {
		if (_hoops_IRSRA->_hoops_GACRA >= _hoops_GRSRA)
			ALLOC_ARRAY(*p,_hoops_GPIGR,_hoops_APCIR);
		else {
			*p = &_hoops_IRSRA->_hoops_SRCRA[_hoops_IRSRA->_hoops_GACRA*3];
			_hoops_IRSRA->_hoops_GACRA++; 
		} 
	}
	else if (_hoops_GPIGR == 4)  {
		if (_hoops_IRSRA->_hoops_AACRA >= _hoops_RRSRA)
			ALLOC_ARRAY(*p,_hoops_GPIGR,_hoops_APCIR);
		else {
			*p = &_hoops_IRSRA->_hoops_RACRA[_hoops_IRSRA->_hoops_AACRA*4];
			_hoops_IRSRA->_hoops_AACRA++;
		} 
	} 
	else 
		ALLOC_ARRAY(*p,_hoops_GPIGR, _hoops_APCIR);
}

local INLINE void _hoops_GASRA(_hoops_PPCIR ** p, int _hoops_GPIGR, _hoops_IGCRA * _hoops_IRSRA) 
{
	if (_hoops_GPIGR == 3)  {
		if (_hoops_IRSRA->_hoops_HACRA >= _hoops_GRSRA)
			ALLOC_ARRAY(*p,_hoops_GPIGR,_hoops_PPCIR);
		else {
			*p = &_hoops_IRSRA->_hoops_PACRA[_hoops_IRSRA->_hoops_HACRA*3];
			_hoops_IRSRA->_hoops_HACRA++; 
		} 
	}
	else if (_hoops_GPIGR == 4)  {
		if (_hoops_IRSRA->_hoops_CACRA >= _hoops_RRSRA)
			ALLOC_ARRAY(*p,_hoops_GPIGR,_hoops_PPCIR);
		else {
			*p = &_hoops_IRSRA->_hoops_IACRA[_hoops_IRSRA->_hoops_CACRA*4];
			_hoops_IRSRA->_hoops_CACRA++;
		} 
	} 
	else 
		ALLOC_ARRAY(*p,_hoops_GPIGR, _hoops_PPCIR);
}



local INLINE void _hoops_RASRA(_hoops_APCIR *p, int _hoops_GPIGR, _hoops_IGCRA * _hoops_IRSRA)
{
	if (_hoops_GPIGR != 3 && _hoops_GPIGR != 4)
		FREE_ARRAY(p,_hoops_GPIGR, _hoops_APCIR);
	else if (_hoops_GPIGR == 3 && _hoops_IRSRA->_hoops_GACRA >= _hoops_GRSRA)    {
		if (p < _hoops_IRSRA->_hoops_SRCRA || p >= &_hoops_IRSRA->_hoops_SRCRA[_hoops_GRSRA * 3])
			FREE_ARRAY(p,_hoops_GPIGR,_hoops_APCIR); 
	}
	else if (_hoops_GPIGR == 4 && _hoops_IRSRA->_hoops_AACRA >= _hoops_RRSRA)    {
		if (p < _hoops_IRSRA->_hoops_RACRA || p >= &_hoops_IRSRA->_hoops_RACRA[_hoops_RRSRA * 4])
			FREE_ARRAY(p,_hoops_GPIGR,_hoops_APCIR); 
	}
}


local INLINE void _hoops_AASRA(_hoops_PPCIR *p, int _hoops_GPIGR, _hoops_IGCRA * _hoops_IRSRA)
{
	if (_hoops_GPIGR != 3 && _hoops_GPIGR != 4)
		FREE_ARRAY(p,_hoops_GPIGR, _hoops_PPCIR);
	else if (_hoops_GPIGR == 3 && _hoops_IRSRA->_hoops_HACRA >= _hoops_GRSRA)    {
		if (p < _hoops_IRSRA->_hoops_PACRA || p >= &_hoops_IRSRA->_hoops_PACRA[_hoops_GRSRA * 3])
			FREE_ARRAY(p,_hoops_GPIGR,_hoops_PPCIR); 
	}
	else if (_hoops_GPIGR == 4 && _hoops_IRSRA->_hoops_CACRA >= _hoops_RRSRA)    {
		if (p < _hoops_IRSRA->_hoops_IACRA || p >= &_hoops_IRSRA->_hoops_IACRA[_hoops_RRSRA * 4])
			FREE_ARRAY(p,_hoops_GPIGR,_hoops_PPCIR); 
	}
}


local INLINE void _hoops_PASRA(int ** p, int _hoops_GPIGR, _hoops_IGCRA * _hoops_IRSRA)
{
	if (_hoops_GPIGR == 3)  {
    	if (_hoops_IRSRA->_hoops_GPCRA >= _hoops_ARSRA)
			ALLOC_ARRAY(*p,_hoops_GPIGR,int);
		else {
			*p = &_hoops_IRSRA->_hoops_SACRA[_hoops_IRSRA->_hoops_GPCRA*3];
			_hoops_IRSRA->_hoops_GPCRA++; 
		} 
	} 
    else if (_hoops_GPIGR == 4)  {
	    if (_hoops_IRSRA->_hoops_APCRA >= _hoops_PRSRA)
			ALLOC_ARRAY(*p,_hoops_GPIGR,int);
    	else {
			*p = &_hoops_IRSRA->_hoops_RPCRA[_hoops_IRSRA->_hoops_APCRA*4];
			_hoops_IRSRA->_hoops_APCRA++; 
		} 
	}
    else
		ALLOC_ARRAY(*p,_hoops_GPIGR, int);
}


local INLINE void _hoops_HASRA(int * p, int _hoops_GPIGR, _hoops_IGCRA * _hoops_IRSRA)
{
	if (_hoops_GPIGR != 3 && _hoops_GPIGR != 4)
		FREE_ARRAY(p,_hoops_GPIGR, int);
	else if (_hoops_GPIGR == 3 && _hoops_IRSRA->_hoops_GPCRA >= _hoops_ARSRA) {
	    if (p < _hoops_IRSRA->_hoops_SACRA || p >= &_hoops_IRSRA->_hoops_SACRA[_hoops_ARSRA * 3])
    		FREE_ARRAY(p,_hoops_GPIGR,int); 
	}
	else if (_hoops_GPIGR == 4 && _hoops_IRSRA->_hoops_APCRA >= _hoops_PRSRA) {
	    if (p < _hoops_IRSRA->_hoops_RPCRA || p >= &_hoops_IRSRA->_hoops_RPCRA[_hoops_PRSRA * 4])
    		FREE_ARRAY(p,_hoops_GPIGR,int); 
	}
}




/* _hoops_ASHGR _hoops_PAIGR _hoops_IIGR _hoops_IRGH _hoops_IASRA. */

local void _hoops_CASRA (_hoops_IGCRA *_hoops_IRSRA, _hoops_IPCRA *node, _hoops_CPCRA *tree);
local void _hoops_SASRA (_hoops_IGCRA *_hoops_IRSRA, _hoops_IPCRA *node, _hoops_PPCRA *_hoops_GPSRA, double _hoops_IASGA);
local void _hoops_RPSRA (_hoops_IGCRA *_hoops_IRSRA, _hoops_IPCRA *node, _hoops_AIIRA *polygon, _hoops_PPCRA *_hoops_APSRA, bool _hoops_PPSRA, double _hoops_IASGA);
local void _hoops_HPSRA (_hoops_IGCRA *_hoops_IRSRA, _hoops_IPCRA *node, _hoops_AIIRA *polygon, _hoops_PPCRA *_hoops_APSRA, bool _hoops_PPSRA, double _hoops_IASGA);
local bool _hoops_IPSRA (_hoops_IGCRA *_hoops_IRSRA, _hoops_AIIRA *polygon, _hoops_APCIR const *points, int const *_hoops_ASPH, Point const *normals, int position, bool invert, bool _hoops_CPSRA, double _hoops_CAIRA);


#ifdef _hoops_RGIRA
#include <stdio.h>
#ifdef WINDOWS_SYSTEM
#include <crtdbg.h>
#else
#include <stdarg.h>
#include <assert.h>
#endif

/* _hoops_IH _hoops_GSPHR _hoops_GCGC _hoops_SR _hoops_PAH _hoops_HGSR _hoops_IRS _hoops_HSRPR _hoops_RGHR _hoops_SGS _hoops_GRS _hoops_IIPR _hoops_ARPP _hoops_PPR */
/* _hoops_RAS _hoops_HSP _hoops_SPSRA _hoops_HII _hoops_RH _hoops_AIHGR _hoops_PGPP. */
char *_hoops_GHSRA = 0;

/* _hoops_APGRR _hoops_RGR _hoops_API _hoops_IS _hoops_HHPR _hoops_IRS _hoops_RGHR _hoops_HSRPR _hoops_IIGR _hoops_HSP _hoops_SPSRA. */
GLOBAL_FUNCTION void HC_CDECL _hoops_SSHRA (char *_hoops_GGIRA) {
    _hoops_GHSRA = _hoops_GGIRA;
}

/* _hoops_API _hoops_PGAP _hoops_RHSRA _hoops_RH _hoops_HSP _hoops_SPSRA */
local void _hoops_AHSRA (HVList *_hoops_PHSRA, HVList *_hoops_HHSRA, int	_hoops_IHSRA);

/* _hoops_API _hoops_PGAP _hoops_RHSRA _hoops_HSSP _hoops_HPHS */
local void _hoops_CHSRA (char *_hoops_GGIRA, HVList *_hoops_SHSRA);

/* _hoops_HSRPR _hoops_HPHS _hoops_AHCA _hoops_RSSI. */
local void _hoops_GISRA (char *_hoops_GGIRA, int _hoops_RISRA, _hoops_APCIR const *points, int _hoops_RHGIR, int *faces);

/* _hoops_CGP _hoops_RHAC _hoops_HHGC _hoops_CICAR _hoops_HHGP _hoops_GSPHR _hoops_HPHS, _hoops_ARP _hoops_AGCR _hoops_HSH */
/* _hoops_AISRA, _hoops_ARP _hoops_RH _hoops_RGHR _hoops_RSIRR _hoops_RHAC _hoops_HHGC _hoops_IH _hoops_RH _hoops_HSRPR, _hoops_IGH _hoops_RH _hoops_HSP */
/* _hoops_RHAC _hoops_CHR _hoops_GPIHR _hoops_GGR _hoops_PISRA _hoops_HII _hoops_RH _hoops_SGCRA _hoops_PAR _hoops_RH _hoops_SAAP, _hoops_PPR _hoops_RH _hoops_PHI */
/* _hoops_IIGR _hoops_RH _hoops_HSP _hoops_RHAC _hoops_HHGC _hoops_HISRA _hoops_SIHC _hoops_IH. _hoops_GPGP _hoops_AGR _hoops_IS _hoops_HGCR _hoops_RH _hoops_HSP _hoops_PHI, _hoops_RHAC */
/* _hoops_PAH _hoops_SGH _hoops_RH _hoops_HSP _hoops_CGRSR _hoops_ARSAR _hoops_HPP _hoops_RH _hoops_IISRA _hoops_CIPH. */

char 	*_hoops_CISRA = null;			/* _hoops_RSIRR _hoops_IIGR _hoops_RGHR _hoops_IS _hoops_SGH _hoops_IH _hoops_RH _hoops_HISRA _hoops_IIPR */
int 	_hoops_SISRA = true;				/* _hoops_IHPR _hoops_IS _hoops_HISRA _hoops_IRS _hoops_SGCRA _hoops_HSP, _hoops_RCPP _hoops_IS _hoops_HISRA _hoops_IRS _hoops_SAAP _hoops_HSP */
int 	_hoops_GCSRA = 48;		    /* _hoops_PGAP _hoops_HSP _hoops_PHI _hoops_AA _hoops_RHAC _hoops_HHGC _hoops_HISRA _hoops_IIPR _hoops_IH */
int 	_hoops_RCSRA = false;		    /* _hoops_ARP _hoops_IHPR _hoops_RPP _hoops_RHAC _hoops_HHGC _hoops_RH _hoops_RRGR _hoops_IS _hoops_ACSRA _hoops_CGPR _hoops_RH _hoops_HSP _hoops_HRGR _hoops_RHHR. */

/* _hoops_RGR _hoops_CHR _hoops_IGI _hoops_HPP _hoops_RH _hoops_HHGP _hoops_HISRA _hoops_RRGR */
FILE 	*_hoops_PCSRA = null;		    /* _hoops_HHGP _hoops_HISRA _hoops_RGHR _hoops_RGHH */
int 	_hoops_HCSRA = 0;		    /* _hoops_PAHGA _hoops_RH _hoops_SCGR _hoops_ICSRA _hoops_PAPA */
int 	_hoops_CCSRA = 0;		/* _hoops_CHR _hoops_SR _hoops_CRSH _hoops_CCA _hoops_RH _hoops_SGCRA _hoops_PAR _hoops_RH _hoops_SAAP _hoops_SCSRA? */
int 	_hoops_GSSRA = 0;		    /* _hoops_IHPR _hoops_RPP _hoops_SR _hoops_CHR _hoops_RSSRA _hoops_PIH, _hoops_RCPP _hoops_IAII */

local void _hoops_ASSRA (const char *str, ...) {
    int i;
    va_list _hoops_PSSRA;
    if (!_hoops_GSSRA)
		return;

    fprintf(_hoops_PCSRA, "%2.2d:", _hoops_HCSRA);
    for (i = 0 ; i < _hoops_HCSRA ; i++)
		fprintf(_hoops_PCSRA, "  ");

    va_start(_hoops_PSSRA, str);
    vfprintf(_hoops_PCSRA, str, _hoops_PSSRA);
    va_end(_hoops_PSSRA);
}

local void _hoops_HSSRA (const char *str, _hoops_AIIRA *_hoops_HARIR) {
    int i;
    if (!_hoops_GSSRA)
		return;

    _hoops_ASSRA("%s Poly, Old Face:%d, points:%d\n", str, _hoops_HARIR->_hoops_CCIRA, _hoops_HARIR->_hoops_ICIRA);
    for (i = 0 ; i < _hoops_HARIR->_hoops_ICIRA ; i++)
		_hoops_ASSRA("@%d: %f %f %f\n", _hoops_HARIR->_hoops_IIIRA[i], _hoops_HARIR->_hoops_PIIRA[i].x, _hoops_HARIR->_hoops_PIIRA[i].y, _hoops_HARIR->_hoops_PIIRA[i].z);
}

local void _hoops_ISSRA (int _hoops_CSSRA) { /* _hoops_HSP -1 _hoops_IS _hoops_AGSGR _hoops_PSAP _hoops_RSSRA */
    if (_hoops_CSSRA != -1 && _hoops_PCSRA != 0 && _hoops_GCSRA == _hoops_CSSRA && _hoops_CCSRA == _hoops_SISRA)
		_hoops_GSSRA = true;
    else
		_hoops_GSSRA = false;

    if (_hoops_RCSRA)
#ifdef WINDOWS_SYSTEM
		_hoops_SSSRA(!(_hoops_GCSRA == _hoops_CSSRA && _hoops_CCSRA == _hoops_SISRA));
#else
		assert(!(_hoops_GCSRA == _hoops_CSSRA && _hoops_CCSRA == _hoops_SISRA));
#endif
}

local void _hoops_GGGAA (int status, _hoops_IPCRA *node) {
    static const char *_hoops_RGGAA[] = { "In Front", "In Back", "Coincident", "Spanning" };
    int _hoops_AGGAA = -1;
    _hoops_AIIRA *_hoops_HARIR;

    if (!_hoops_GSSRA)
		return;

    _hoops_HARIR = (_hoops_AIIRA *)HI_VList_Peek_First(node->_hoops_SPCRA);
    if (_hoops_HARIR)
		_hoops_AGGAA = _hoops_HARIR->_hoops_CCIRA;

    _hoops_ASSRA("Status:%s, Plane a:%f b:%f c:%f d:%f Plane Face:%d\n", _hoops_RGGAA[status], 
			    	 node->_hoops_AHCRA.a, node->_hoops_AHCRA.b, node->_hoops_AHCRA.c, 
			    	 node->_hoops_AHCRA.d, _hoops_AGGAA);
}

#define _hoops_PGGAA \
				_hoops_PCSRA = null; \
				_hoops_HCSRA = 0;	\
				_hoops_CCSRA = false;	\
				_hoops_GSSRA = false; \
				if (_hoops_CISRA)    \
				    _hoops_PCSRA = fopen(_hoops_CISRA, "w+")


#define _hoops_HGGAA(str) \
				_hoops_ASSRA(str)

#define _hoops_IGGAA(str, _hoops_HARIR) \
				_hoops_HSSRA(str, _hoops_HARIR)

#define _hoops_CGGAA(status, node) \
				_hoops_GGGAA(status, node)

#define _hoops_SGGAA	\
				if (_hoops_PCSRA) \
					fclose(_hoops_PCSRA)

#define _hoops_GRGAA	\
				++_hoops_HCSRA

#define _hoops_RRGAA	\
				--_hoops_HCSRA

#define _hoops_ARGAA(_hoops_PRGAA) \
				_hoops_CCSRA = _hoops_PRGAA

#define _hoops_HRGAA(face) \
				_hoops_ISSRA(face)

#else
GLOBAL_FUNCTION void HC_CDECL _hoops_SSHRA (char *_hoops_GGIRA) {
	UNREFERENCED(_hoops_GGIRA);
}

#define _hoops_PGGAA 
#define _hoops_HGGAA(str) \
				((void)str)
#define _hoops_IGGAA(str, _hoops_HARIR) \
 				((void)str, (void)_hoops_HARIR)
#define _hoops_SGGAA
#define _hoops_GRGAA 
#define _hoops_RRGAA 
#define _hoops_ARGAA(_hoops_PRGAA) \
				((void) _hoops_PRGAA)
#define _hoops_HRGAA(face) \
				((void) face)
#define _hoops_CGGAA(status, node) \
				((void)status, (void)node)
#endif



/* _hoops_ISIRR _hoops_AIHGR _hoops_CSSC _hoops_SGS _hoops_CHR _hoops_CGI _hoops_GGR _hoops_AIH _hoops_RH _hoops_HCSP _hoops_GSGR _hoops_GGR _hoops_RH  */
/* _hoops_AGAH _hoops_IRGAA. */
#define _hoops_CRGAA					0x1
#define _hoops_SRGAA				0x2
#define _hoops_GAGAA					0x3
#define _hoops_RAGAA				0x4
#define _hoops_AAGAA 	0x5
#define _hoops_PAGAA 0x6
#define _hoops_HAGAA			0x7
#define _hoops_IAGAA	0x8
#define _hoops_CAGAA				0x9

local const _hoops_IGRCR _hoops_SAGAA[] = {
    {_hoops_SRGAA,	_hoops_GRRCR ("subtract"),	_hoops_RRRCR, 0, false},
    {_hoops_GAGAA, 	_hoops_GRRCR ("union"),		_hoops_RRRCR, 0, false},
    {_hoops_RAGAA, _hoops_GRRCR ("intersect"),	_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_GPGAA = {
    _hoops_GGAPR (_hoops_SAGAA),
    _hoops_SAGAA,
};

local const _hoops_IGRCR _hoops_RPGAA[] = {
	{_hoops_GPSA,	_hoops_GRRCR ("left"),	_hoops_RRRCR, 0, false},
	{_hoops_SASA,	_hoops_GRRCR ("right"),	_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_APGAA = {
	_hoops_GGAPR (_hoops_RPGAA),
	_hoops_RPGAA,
};

 
/* _hoops_ICGI _hoops_IRS _hoops_IPS _hoops_IIGR _hoops_RH _hoops_SRGR _hoops_IIGR _hoops_PPGAA _hoops_HIS _hoops_SGS, _hoops_IH _hoops_PCAI, "_hoops_AIHGR _hoops_GPRR = _hoops_HIPRA" 
	_hoops_PPR _hoops_SAHR _hoops_GAGPR "_hoops_HIPRA" _hoops_PAH _hoops_PHGA _hoops_RH _hoops_PSHR _hoops_AHAP (_hoops_CCA _hoops_IRS _hoops_RSCA _hoops_HPIHR _hoops_HII _hoops_HPGAA, _hoops_IIGR _hoops_IPGAA) */
local const _hoops_IGRCR _hoops_CPGAA[] = {
	{_hoops_CRGAA, 						_hoops_GRRCR("boolean type"), 		_hoops_GHAGA, -999,	false,	&_hoops_GPGAA },
	{_hoops_SRGAA, 					_hoops_GRRCR("subtract"), 			_hoops_RRRCR, 		0,		false},
	{_hoops_GAGAA, 					_hoops_GRRCR("union"), 				_hoops_RRRCR, 		0,		false},
	{_hoops_RAGAA, 				_hoops_GRRCR("intersect"), 			_hoops_RRRCR, 		0, 		false},
	{_hoops_AAGAA,	_hoops_GRRCR("target handedness"),	_hoops_GHAGA, 	1, 		true,	&_hoops_APGAA},
	{_hoops_PAGAA,	_hoops_GRRCR("tool handedness"),	_hoops_GHAGA, 	1,		true,	&_hoops_APGAA},
	{_hoops_HAGAA,			_hoops_GRRCR("plane tolerance"),	_hoops_SPPCR,		1,		false},
	{_hoops_IAGAA,			_hoops_GRRCR("plane merge tolerance"),_hoops_SPPCR,		1,		false},
	{_hoops_CAGAA,			_hoops_GRRCR("plane coefficient"),_hoops_SPPCR,		1,		false}

	
};


/* _hoops_PPARR _hoops_IH _hoops_ASRC _hoops_IIGR _hoops_AAP _hoops_RAS _hoops_SPGAA _hoops_HCSP _hoops_GSGR */
struct configs {
	int	operation;
	double _hoops_GHGAA;
	double _hoops_RHGAA;	
	double _hoops_AHGAA;
	bool	_hoops_PHGAA;
	bool	_hoops_HHGAA;
};

/* _hoops_IHGAA _hoops_RH _hoops_AAP _hoops_HII _hoops_RH _hoops_AGAH _hoops_HCSP _hoops_GSGR.*/
local bool _hoops_CHGAA (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			option_string,
	struct configs *		_hoops_SHGAA) 
{
	/* _hoops_ARP _hoops_SHIR _hoops_HSH _hoops_IH _hoops_HCR _hoops_IIGR _hoops_RH _hoops_GIGAA */
	_hoops_SHGAA->operation = _hoops_SRGAA;
 
	if (option_string == null) 
		return false;

	_hoops_HIACR (_hoops_RIGAA, _hoops_CPGAA);

	Option_Value *	option_list = null;
	Option_Value *	option;

	if (!HI_Parse_Options (_hoops_RIGC, option_string, _hoops_CIACR (_hoops_RIGAA), &option_list, _hoops_SIACR))
		return false;

	_hoops_SHGAA->_hoops_PHGAA = false;
	_hoops_SHGAA->_hoops_HHGAA = false;

	if ((option = option_list) != null) 
		do {
			switch (option->type->id) {
			case _hoops_CRGAA:
				_hoops_SHGAA->operation = option->value.option_list->type->id;
				break;
			case _hoops_HAGAA:
				_hoops_SHGAA->_hoops_GHGAA = option->value._hoops_PIPCR[0];
		    break;		 
			case _hoops_IAGAA:
				_hoops_SHGAA->_hoops_RHGAA = option->value._hoops_PIPCR[0];
		    break;		 
			case _hoops_CAGAA:
				_hoops_SHGAA->_hoops_AHGAA = option->value._hoops_PIPCR[0];
		    break;		 
 			case _hoops_AAGAA:
				if (option->value.option_list->type->id == _hoops_SASA)
	 				_hoops_SHGAA->_hoops_PHGAA = true;
				break;
			case _hoops_PAGAA:
				if (option->value.option_list->type->id == _hoops_SASA)
	 				_hoops_SHGAA->_hoops_HHGAA = true;
				break;
	 		case _hoops_SRGAA: 
			case _hoops_GAGAA: 
			case _hoops_RAGAA: 
				_hoops_SHGAA->operation = option->type->id;
				break;
			}
		} _hoops_RGGA ((option = option->next) == null);

	HI_Free_Option_List (_hoops_RIGC, option_list);
	return true;
}

/* _hoops_AIGAA _hoops_RPP _hoops_IRS _hoops_PPSR _hoops_HRGR _hoops_GPP _hoops_IRS _hoops_IPPA _hoops_PAR _hoops_HAR.  _hoops_PS _hoops_ARAS _hoops_RH _hoops_PPSR */
/* _hoops_RHIR _hoops_RH _hoops_IPPA _hoops_CGSSR.  _hoops_RAIGR _hoops_GHPP _hoops_IIGR 0.0 _hoops_CHH _hoops_SHH _hoops_GPP _hoops_RH _hoops_IPPA, */
/* _hoops_HPGP >0 _hoops_PAR <0 _hoops_HRGR _hoops_GPP _hoops_SPR _hoops_PPAP _hoops_PAR _hoops_RH _hoops_RII _hoops_IIGR _hoops_RH _hoops_IPPA. */
local double _hoops_PIGAA (_hoops_AAIRA *pl, _hoops_APCIR *p) { 
    return (pl->a * p->x + pl->b*p->y + pl->c*p->z + pl->d); 
}


 


/*
 * _hoops_HIGAA _hoops_RH _hoops_PPSR _hoops_PPR _hoops_HSP _hoops_CPCI _hoops_IIGR _hoops_PGCR _hoops_SCHS _hoops_GIRP.
 * _hoops_IIGAA, _hoops_SR _hoops_SAHR _hoops_CIGAA _hoops_RH _hoops_GIAP _hoops_RRCPR _hoops_CIAA _hoops_RH _hoops_SRS _hoops_SPR.
 * _hoops_CGP _hoops_RGAR _hoops_SPR _hoops_ARP _hoops_IIGR _hoops_PIH _hoops_HRGR _hoops_CIIA, _hoops_PSCR _hoops_SR _hoops_SAHR _hoops_ARPR _hoops_IRS _hoops_GHPP _hoops_CCA
 * _hoops_RH _hoops_SPR _hoops_ARP _hoops_IIGR _hoops_PIH.
 *
 * _hoops_IPCP _hoops_GHPP _hoops_HRGR _hoops_RH _hoops_SIC _hoops_IH _hoops_RH _hoops_ARGR _hoops_AGAH _hoops_RRCPR.  _hoops_HGI _hoops_RRCPR _hoops_GRS
 * _hoops_SHH _hoops_SPIP _hoops_GGR _hoops_RH _hoops_SCGR _hoops_IGS _hoops_CAGH.
 */
local Key _hoops_SIGAA (
	int 			_hoops_GCGAA, 		/* _hoops_RSSA _hoops_PPR _hoops_ASGA _hoops_SRS _hoops_RRCPR */
	Point const *	points1, 
	Vector const *	_hoops_RCGAA,	
	int 			_hoops_ACGAA, 
	int *			_hoops_PCGAA,	/* _hoops_RSSI _hoops_SRS _hoops_RRCPR */
	int 			_hoops_HCGAA, 
	Point const *	points2, 	/* _hoops_RSSA _hoops_PPR _hoops_ASGA _hoops_GIAP _hoops_RRCPR */
	Vector const *	_hoops_ICGAA,	
	int 			_hoops_CCGAA, 		/* _hoops_RSSI _hoops_GIAP _hoops_RRCPR */
	int *			_hoops_SCGAA,					
	RGB const *		_hoops_GSGAA, /* _hoops_CGP _hoops_ARSAR, _hoops_RH _hoops_SRS "_hoops_RSGAA" _hoops_RSSI _hoops_GRS _hoops_SHH */
	int 			_hoops_ASGAA,  /* _hoops_SHIC _hoops_CCA _hoops_AGCR _hoops_PSHA.  _hoops_PSGAA _hoops_HRGR _hoops_PCCP _hoops_CRPR */
								/* _hoops_IIGR _hoops_IGIR _hoops_RSGAA */
	RGB const *		_hoops_HSGAA, /* _hoops_CGP _hoops_ARSAR, _hoops_RH _hoops_ISGAA _hoops_RSSI _hoops_RAS _hoops_RH _hoops_SRS */
	int 			_hoops_CSGAA,  /* _hoops_RSGAA _hoops_RSSI _hoops_GRS _hoops_SHH _hoops_SHIC _hoops_CCA _hoops_AGCR _hoops_PSHA */								
	bool *			_hoops_SSGAA, 	/* _hoops_CGP _hoops_ARSAR, _hoops_HSP _hoops_HPRC _hoops_SGI _hoops_GRS _hoops_SHH _hoops_ARP _hoops_CCA _hoops_AGCR*/
	bool *			_hoops_GGRAA)  /* _hoops_PGRR _hoops_PIHA _hoops_PSSP _hoops_PSHA */							   
{
    int 			_hoops_RGRAA; 
	int				_hoops_AGRAA; 
    Key 			_hoops_PGRAA = -1;
    Point *			_hoops_HGRAA;
    int *			_hoops_IGRAA;
    Vector *		_hoops_CGRAA = 0;
    int 			_hoops_SGRAA = 0;
 
    if (_hoops_GCGAA && _hoops_HCGAA && _hoops_ACGAA && _hoops_CCGAA) {
		_hoops_RGRAA = _hoops_GCGAA + _hoops_HCGAA;
		_hoops_AGRAA = _hoops_ACGAA + _hoops_CCGAA;
    
		ALLOC_ARRAY_CACHED(_hoops_HGRAA, _hoops_RGRAA, Point);
		if (_hoops_RCGAA && _hoops_ICGAA)
		    ALLOC_ARRAY_CACHED(_hoops_CGRAA, _hoops_RGRAA, Vector);
		ALLOC_ARRAY_CACHED(_hoops_IGRAA, _hoops_AGRAA, int);
    
		for (int i = 0 ; i < _hoops_GCGAA ; i++)
		    _hoops_HGRAA[i] = points1[i];
		for (int i = 0 ; i < _hoops_HCGAA ; i++)
		    _hoops_HGRAA[i + _hoops_GCGAA] = points2[i];
		if (_hoops_RCGAA && _hoops_ICGAA) {
		    for (int i = 0 ; i < _hoops_GCGAA ; i++)
				_hoops_CGRAA[i] = _hoops_RCGAA[i];
		    for (int i = 0 ; i < _hoops_HCGAA ; i++)
				_hoops_CGRAA[i + _hoops_GCGAA] = _hoops_ICGAA[i];
		}
    
		for (int i = 0 ; i < _hoops_ACGAA ; i++)
		    _hoops_IGRAA[i] = _hoops_PCGAA[i];

		int ii = 0;
    
		while (1) {
		    _hoops_IGRAA[ii+_hoops_ACGAA] = _hoops_SCGAA[ii];
		    int _hoops_GRRAA = _hoops_SCGAA[ii];
		    ii++;
		    for (int j = 0 ; j < _hoops_GRRAA ; j++)
				_hoops_IGRAA[ii+_hoops_ACGAA + j] = _hoops_SCGAA[ii + j] + _hoops_GCGAA;
		    ii += _hoops_GRRAA;
		    _hoops_SGRAA++;
		    if (ii >= _hoops_CCGAA)
				break;
		}
 
		_hoops_PGRAA = HC_Insert_Shell(_hoops_RGRAA, _hoops_HGRAA, _hoops_AGRAA, _hoops_IGRAA);

		if (_hoops_RCGAA && _hoops_ICGAA)
		    HC_MSet_Vertex_Normals(_hoops_PGRAA, 0, _hoops_RGRAA, _hoops_CGRAA);
		if (_hoops_CGRAA)
		    FREE_ARRAY(_hoops_CGRAA, _hoops_RGRAA, Vector);
		FREE_ARRAY(_hoops_HGRAA, _hoops_RGRAA, Point);
		FREE_ARRAY(_hoops_IGRAA, _hoops_AGRAA, int);

		if (_hoops_GSGAA)
		    HC_MSet_Face_Colors_By_Value(_hoops_PGRAA, "faces", 0, "rgb", _hoops_ASGAA, _hoops_GSGAA);

		if (_hoops_HSGAA)
		    HC_MSet_Face_Colors_By_Value(_hoops_PGRAA, "faces", _hoops_ASGAA, "rgb", _hoops_CSGAA, _hoops_HSGAA);
    
		if (_hoops_SSGAA) {
		    HC_Open_Geometry(_hoops_PGRAA);
		    for (int i = 0 ; i < _hoops_ASGAA ; i++) {
				if (_hoops_SSGAA[i]) {	    
					HC_Open_Face(i);
						HC_Set_Visibility("off");
					HC_Close_Face();
				}
		    }
		    HC_Close_Geometry();
		}
    
		if (_hoops_GGRAA) {	
		    HC_Open_Geometry(_hoops_PGRAA);
		    for (int i = 0 ; i < _hoops_CSGAA ; i++) {
				if (_hoops_GGRAA[i]) {	    
					HC_Open_Face(i+_hoops_ASGAA);
						HC_Set_Visibility("off");
					HC_Close_Face();
				}
		    }
		    HC_Close_Geometry();
		}
    }
    else {
		if (_hoops_GCGAA && _hoops_ACGAA) {
			_hoops_PGRAA = HC_Insert_Shell(_hoops_GCGAA, points1, _hoops_ACGAA, _hoops_PCGAA);
		    if (_hoops_RCGAA)
				HC_MSet_Vertex_Normals(_hoops_PGRAA, 0, _hoops_GCGAA, _hoops_RCGAA);

		    if (_hoops_GSGAA)
				HC_MSet_Face_Colors_By_Value(_hoops_PGRAA, "faces", 0, "rgb", _hoops_ASGAA, _hoops_GSGAA);

		    if (_hoops_SSGAA) {	
				HC_Open_Geometry(_hoops_PGRAA);
				for (int i = 0 ; i < _hoops_ASGAA ; i++) {
				    if (_hoops_SSGAA[i]) {	    
					    HC_Open_Face(i);
							HC_Set_Visibility("off");
					    HC_Close_Face();
				    }
				}
				HC_Close_Geometry();
		    }
		}
		else if (_hoops_HCGAA && _hoops_CCGAA) {
		    _hoops_PGRAA = HC_Insert_Shell(_hoops_HCGAA, points2, _hoops_CCGAA, _hoops_SCGAA);
		    if (_hoops_ICGAA)
				HC_MSet_Vertex_Normals(_hoops_PGRAA, 0, _hoops_HCGAA, _hoops_ICGAA);

		    if (_hoops_HSGAA)
				HC_MSet_Face_Colors_By_Value(_hoops_PGRAA, "faces", 0, "rgb", _hoops_CSGAA, _hoops_HSGAA);

		    if (_hoops_GGRAA) {
				HC_Open_Geometry(_hoops_PGRAA);
				for (int i = 0 ; i < _hoops_CSGAA ; i++) {
				    if (_hoops_GGRAA[i]) {	    
					    HC_Open_Face(i);
							HC_Set_Visibility("off");
					    HC_Close_Face();
				    }
				}
				HC_Close_Geometry();
		    }
		}
    }
  
    return _hoops_PGRAA;  
}

/*
 * _hoops_HIGAA _hoops_RH _hoops_PPSR _hoops_PPR _hoops_HSP _hoops_CPCI _hoops_IIGR _hoops_PGCR _hoops_SCHS _hoops_GIRP.
 * _hoops_IIGAA, _hoops_SR _hoops_SAHR _hoops_CIGAA _hoops_RH _hoops_GIAP _hoops_RRCPR _hoops_CIAA _hoops_RH _hoops_SRS _hoops_SPR.
 * _hoops_CGP _hoops_RGAR _hoops_SPR _hoops_ARP _hoops_IIGR _hoops_PIH _hoops_HRGR _hoops_CIIA, _hoops_PSCR _hoops_SR _hoops_SAHR _hoops_ARPR _hoops_IRS _hoops_GHPP _hoops_CCA
 * _hoops_RH _hoops_SPR _hoops_ARP _hoops_IIGR _hoops_PIH.
 *
 * _hoops_IPCP _hoops_GHPP _hoops_HRGR _hoops_RH _hoops_SIC _hoops_IH _hoops_RH _hoops_ARGR _hoops_AGAH _hoops_RRCPR.  _hoops_HGI _hoops_RRCPR _hoops_GRS
 * _hoops_SHH _hoops_SPIP _hoops_GGR _hoops_RH _hoops_SCGR _hoops_IGS _hoops_CAGH.
 */ 
local Key _hoops_RRRAA (
	int 				_hoops_GCGAA, 		/* _hoops_RSSA _hoops_PPR _hoops_ASGA _hoops_SRS _hoops_RRCPR */
	_hoops_APCIR const	*	points1, 
	Vector const *		_hoops_RCGAA,	
	int 				_hoops_ACGAA, 
	int *				_hoops_PCGAA,	/* _hoops_RSSI _hoops_SRS _hoops_RRCPR */
	int 				_hoops_HCGAA, 
	_hoops_APCIR const	*	points2, 	/* _hoops_RSSA _hoops_PPR _hoops_ARRAA _hoops_GIAP _hoops_RRCPR */
	Vector const *		_hoops_ICGAA,	
	int 				_hoops_CCGAA, 		/* _hoops_RSSI _hoops_GIAP _hoops_RRCPR */
	int *				_hoops_SCGAA,					
	RGB const *			_hoops_GSGAA, /* _hoops_CGP _hoops_ARSAR, _hoops_RH _hoops_SRS "_hoops_RSGAA" _hoops_RSSI _hoops_GRS _hoops_SHH */
	int 				_hoops_ASGAA,  /* _hoops_SHIC _hoops_CCA _hoops_AGCR _hoops_PSHA.  _hoops_PSGAA _hoops_HRGR _hoops_PCCP _hoops_CRPR */
								/* _hoops_IIGR _hoops_IGIR _hoops_RSGAA */
	RGB const *			_hoops_HSGAA, /* _hoops_CGP _hoops_ARSAR, _hoops_RH _hoops_ISGAA _hoops_RSSI _hoops_RAS _hoops_RH _hoops_SRS */
	int 				_hoops_CSGAA,  /* _hoops_RSGAA _hoops_RSSI _hoops_GRS _hoops_SHH _hoops_SHIC _hoops_CCA _hoops_AGCR _hoops_PSHA */								
	bool *				_hoops_SSGAA, 	/* _hoops_CGP _hoops_ARSAR, _hoops_HSP _hoops_HPRC _hoops_SGI _hoops_GRS _hoops_SHH _hoops_ARP _hoops_CCA _hoops_AGCR*/
	bool *				_hoops_GGRAA)  /* _hoops_PGRR _hoops_PIHA _hoops_PSSP _hoops_PSHA */
{
    int 			_hoops_RGRAA; 
	int				_hoops_AGRAA; 
    Key 			_hoops_PGRAA = -1;
    _hoops_APCIR *		_hoops_HGRAA;
    int *			_hoops_IGRAA;
    Vector *		_hoops_CGRAA = 0;
    int 			_hoops_SGRAA = 0;

    if (_hoops_GCGAA && _hoops_HCGAA && _hoops_ACGAA && _hoops_CCGAA) {
		_hoops_RGRAA = _hoops_GCGAA + _hoops_HCGAA;
		_hoops_AGRAA = _hoops_ACGAA + _hoops_CCGAA;

		ALLOC_ARRAY(_hoops_HGRAA, _hoops_RGRAA, _hoops_APCIR);
		if (_hoops_RCGAA && _hoops_ICGAA)
		    ALLOC_ARRAY(_hoops_CGRAA, _hoops_RGRAA, Vector);
		ALLOC_ARRAY(_hoops_IGRAA, _hoops_AGRAA, int);

		for (int i = 0 ; i < _hoops_GCGAA ; i++)
		    _hoops_HGRAA[i] = points1[i];
		for (int i = 0 ; i < _hoops_HCGAA ; i++)
		    _hoops_HGRAA[i + _hoops_GCGAA] = points2[i];
		if (_hoops_RCGAA && _hoops_ICGAA) {
		    for (int i = 0 ; i < _hoops_GCGAA ; i++)
				_hoops_CGRAA[i] = _hoops_RCGAA[i];
		    for (int i = 0 ; i < _hoops_HCGAA ; i++)
				_hoops_CGRAA[i + _hoops_GCGAA] = _hoops_ICGAA[i];
		}

		for (int i = 0 ; i < _hoops_ACGAA ; i++)
		    _hoops_IGRAA[i] = _hoops_PCGAA[i];

		int ii = 0;

		while (1) {
		    _hoops_IGRAA[ii+_hoops_ACGAA] = _hoops_SCGAA[ii];
		    int _hoops_GRRAA = _hoops_SCGAA[ii];
		    ii++;
		    for (int j = 0 ; j < _hoops_GRRAA ; j++)
				_hoops_IGRAA[ii+_hoops_ACGAA + j] = _hoops_SCGAA[ii + j] + _hoops_GCGAA;
		    ii += _hoops_GRRAA;
		    _hoops_SGRAA++;
		    if (ii >= _hoops_CCGAA)
				break;
		}

		_hoops_PGRAA = HC_DQKInsert_Shell(".", _hoops_RGRAA, _hoops_HGRAA, _hoops_AGRAA, _hoops_IGRAA);

		if (_hoops_RCGAA && _hoops_ICGAA)
		    HC_MSet_Vertex_Normals(_hoops_PGRAA, 0, _hoops_RGRAA, _hoops_CGRAA);
		if (_hoops_CGRAA)
		    FREE_ARRAY(_hoops_CGRAA, _hoops_RGRAA, Point);
		FREE_ARRAY(_hoops_HGRAA, _hoops_RGRAA, _hoops_APCIR);
		FREE_ARRAY(_hoops_IGRAA, _hoops_AGRAA, int);

		if (_hoops_GSGAA)
		    HC_MSet_Face_Colors_By_Value(_hoops_PGRAA, "faces", 0, "rgb", _hoops_ASGAA, _hoops_GSGAA);

		if (_hoops_HSGAA)
		    HC_MSet_Face_Colors_By_Value(_hoops_PGRAA, "faces", _hoops_ASGAA, "rgb", _hoops_CSGAA, _hoops_HSGAA);

		if (_hoops_SSGAA) {
		    HC_Open_Geometry(_hoops_PGRAA);
		    for (int i = 0 ; i < _hoops_ASGAA ; i++) {
				if (_hoops_SSGAA[i]) {	    
					HC_Open_Face(i);
						HC_Set_Visibility("off");
					HC_Close_Face();
				}
		    }
		    HC_Close_Geometry();
		}

		if (_hoops_GGRAA) {	
		    HC_Open_Geometry(_hoops_PGRAA);
		    for (int i = 0 ; i < _hoops_CSGAA ; i++) {
				if (_hoops_GGRAA[i]) {	    
					HC_Open_Face(i+_hoops_ASGAA);
						HC_Set_Visibility("off");
					HC_Close_Face();
				}
		    }
		    HC_Close_Geometry();
		}
    }
    else {
		if (_hoops_GCGAA && _hoops_ACGAA) {
			_hoops_PGRAA = HC_DQKInsert_Shell(".", _hoops_GCGAA, points1, _hoops_ACGAA, _hoops_PCGAA);
		    if (_hoops_RCGAA)
				HC_MSet_Vertex_Normals(_hoops_PGRAA, 0, _hoops_GCGAA, _hoops_RCGAA);

		    if (_hoops_GSGAA)
				HC_MSet_Face_Colors_By_Value(_hoops_PGRAA, "faces", 0, "rgb", _hoops_ASGAA, _hoops_GSGAA);

		    if (_hoops_SSGAA) {	
				HC_Open_Geometry(_hoops_PGRAA);
				for (int i = 0 ; i < _hoops_ASGAA ; i++) {
				    if (_hoops_SSGAA[i]) {	    
					    HC_Open_Face(i);
							HC_Set_Visibility("off");
					    HC_Close_Face();
				    }
				}
				HC_Close_Geometry();
		    }
		}
		else if (_hoops_HCGAA && _hoops_CCGAA) {
		    _hoops_PGRAA = HC_DQKInsert_Shell(".", _hoops_HCGAA, points2, _hoops_CCGAA, _hoops_SCGAA);
		    if (_hoops_ICGAA)
				HC_MSet_Vertex_Normals(_hoops_PGRAA, 0, _hoops_HCGAA, _hoops_ICGAA);

		    if (_hoops_HSGAA)
				HC_MSet_Face_Colors_By_Value(_hoops_PGRAA, "faces", 0, "rgb", _hoops_CSGAA, _hoops_HSGAA);

		    if (_hoops_GGRAA) {
				HC_Open_Geometry(_hoops_PGRAA);
				for (int i = 0 ; i < _hoops_CSGAA ; i++) {
				    if (_hoops_GGRAA[i]) {	    
					    HC_Open_Face(i);
							HC_Set_Visibility("off");
					    HC_Close_Face();
				    }
				}
				HC_Close_Geometry();
		    }
		}
    }

    return _hoops_PGRAA;  
}

/* _hoops_PSIH _hoops_RH _hoops_IPPA _hoops_IH _hoops_IRS _hoops_RAGA _hoops_HSSP.  _hoops_PRRAA _hoops_HRGR _hoops_GIIA */
/* _hoops_GGR _hoops_RH _hoops_HSSP _hoops_HRPR. */
local bool _hoops_HRRAA (
	_hoops_AIIRA *	p, 
	double			_hoops_CAIRA)
{
    _hoops_APCIR _hoops_IRRAA[256];
    for (int i = 0 ; i < p->_hoops_ICIRA ; i++) {    
		_hoops_IRRAA[i].x = p->_hoops_PIIRA[i].x;
		_hoops_IRRAA[i].y = p->_hoops_PIIRA[i].y;
		_hoops_IRRAA[i].z = p->_hoops_PIIRA[i].z;
    }

	p->_hoops_HSIRA = _hoops_PPIRA::_hoops_CRGA;

    _hoops_HAIRA(p->_hoops_ICIRA, _hoops_IRRAA, &p->_hoops_HSIRA, _hoops_CAIRA);
    if (fabs(p->_hoops_HSIRA.a) < _hoops_CAIRA && fabs(p->_hoops_HSIRA.b) < _hoops_CAIRA && fabs(p->_hoops_HSIRA.c) < _hoops_CAIRA)
		return false;

    return true;
}

/* _hoops_CRRAA _hoops_RH _hoops_GSSR _hoops_IH _hoops_IRS _hoops_PPSR _hoops_IGIAR _hoops_PCCP _hoops_ISHA _hoops_PPIP _hoops_SRRAA _hoops_PGCR _hoops_RII */
/* _hoops_RSSA.  _hoops_PGII _hoops_HRSP _hoops_RSSA _hoops_PIHA _hoops_SHH _hoops_GARAA. */
local void _hoops_RARAA (
	_hoops_APCIR &	p1, 
	_hoops_PPCIR &	_hoops_ICIPR,	/* _hoops_SRS _hoops_CIIA _hoops_PPSR _hoops_PPR _hoops_GSSR _hoops_ARSSR _hoops_RH _hoops_ISHA */
	_hoops_APCIR &	p2, 
	_hoops_PPCIR &	_hoops_CCIPR,	/* _hoops_GIAP _hoops_CIIA _hoops_PPSR _hoops_PPR _hoops_GSSR _hoops_ARSSR _hoops_RH _hoops_ISHA */
	_hoops_APCIR &	_hoops_IAPH,	/* _hoops_HRSSR _hoops_CIIA _hoops_PPSR _hoops_SGS _hoops_SR _hoops_HHGC _hoops_RH _hoops_GSSR _hoops_IH */
	_hoops_PPCIR &	_hoops_GCGCR) /* _hoops_IIPR _hoops_GSSR _hoops_IH _hoops_RH _hoops_HRSSR _hoops_PPSR */
{   

	/* _hoops_SRS _hoops_SR _hoops_HGCR _hoops_RH _hoops_IHHA _hoops_IIGR _hoops_RH _hoops_PSPAR _hoops_AARAA-_hoops_PARAA, _hoops_PPR _hoops_HARAA-_hoops_PARAA. */
    _hoops_PPCIR _hoops_IARAA = p2 - p1;
	_hoops_PPCIR _hoops_CARAA = _hoops_IAPH - p1;
   
    double	_hoops_SARAA = _hoops_IARAA.length();
    double	_hoops_GPRAA = _hoops_CARAA.length();

    /* _hoops_HA _hoops_SR _hoops_ARP _hoops_RPRAA _hoops_IS _hoops_RH _hoops_AAGA _hoops_APRAA _hoops_RH _hoops_AGRP _hoops_HII _hoops_PPRAA _hoops_IS _hoops_HPRAA. */
	_hoops_IARAA = _hoops_CCIPR - _hoops_ICIPR;

    /* _hoops_AGGA _hoops_ARPR _hoops_IPRAA _hoops_HPP _hoops_CPRAA _hoops_RH _hoops_AGRP _hoops_AAGA _hoops_CPPSR _hoops_HPP _hoops_RH _hoops_GIRA _hoops_IGIAR _hoops_RH _hoops_ISHA _hoops_IIGR _hoops_HARAA, _hoops_IS _hoops_PPRAA */
    double	_hoops_SPRAA = _hoops_GPRAA / _hoops_SARAA;

	_hoops_GCGCR = _hoops_ICIPR + _hoops_IARAA * _hoops_SPRAA; 
 
	_hoops_GCGCR._hoops_AAIAR();
}

/* _hoops_GHRAA _hoops_RRCPR _hoops_HPHS _hoops_HRPR */
local void _hoops_RHRAA (
    _hoops_HHIRA *	info, 
    int				pcount,
    int				fcount)
{
    info->_hoops_IHIRA = pcount;
    info->_hoops_CHIRA = fcount;
    info->_hoops_GIIRA = info->_hoops_CHIRA;
    info->_hoops_SHIRA = info->_hoops_IHIRA;
}

/* "_hoops_AHRAA" _hoops_IH _hoops_IRS _hoops_HSSP */
local void _hoops_PHRAA (
    _hoops_AIIRA *	p, 
    _hoops_HHIRA *	info)
{
	ZERO_STRUCT(p, _hoops_AIIRA);

    p->_hoops_SIIRA = info;

    p->_hoops_ISIRA = true;

    p->_hoops_CCIRA = -1;
    p->_hoops_GSIRA = -1;
	p->_hoops_RSIRA = -1;
}

/* "_hoops_AHRAA" _hoops_IH _hoops_IRS _hoops_HSSP */
local bool  _hoops_HHRAA (
    _hoops_IGCRA	*	_hoops_IRSRA,
    _hoops_AIIRA *		p,
    _hoops_APCIR *			points,
    int		    		_hoops_GPIGR,
    _hoops_HHIRA *		info,
    _hoops_AIIRA *		_hoops_SCAAR)
{
    ZERO_STRUCT(p, _hoops_AIIRA);

    p->_hoops_SIIRA = info;
    p->_hoops_ICIRA = _hoops_GPIGR;

	p->_hoops_ISIRA = true;
	p->_hoops_HSIRA = _hoops_SCAAR->_hoops_HSIRA;

	p->_hoops_CCIRA = -1;
	p->_hoops_GSIRA = -1;
	p->_hoops_RSIRA = -1;

    _hoops_SRSRA(&p->_hoops_PIIRA, p->_hoops_ICIRA, _hoops_IRSRA);
    for (int i = 0 ; i < p->_hoops_ICIRA ; i++)
		p->_hoops_PIIRA[i] = points[i];
		
	return true;
}
 
/* "_hoops_AHRAA" _hoops_IH _hoops_IRS _hoops_HSSP */
local bool _hoops_IHRAA (
    _hoops_IGCRA	*	_hoops_IRSRA,
    _hoops_AIIRA *		p,
    _hoops_APCIR *			points,
    int		    		_hoops_GPIGR,
    int *				indices,
    _hoops_PPCIR *			normals,
    _hoops_HHIRA *		info,
    _hoops_AIIRA *		_hoops_SCAAR)
{
	ZERO_STRUCT(p, _hoops_AIIRA);
	
    p->_hoops_SIIRA = info;
    p->_hoops_ICIRA = _hoops_GPIGR;

    p->_hoops_CCIRA = -1;
    p->_hoops_GSIRA = -1;
	p->_hoops_RSIRA = -1;

	p->_hoops_ISIRA = true;
	p->_hoops_HSIRA = _hoops_SCAAR->_hoops_HSIRA;

    if (_hoops_GPIGR) {    	
		_hoops_SRSRA(&p->_hoops_PIIRA, _hoops_GPIGR, _hoops_IRSRA);
	    if (normals)
			_hoops_GASRA(&p->_hoops_HIIRA, _hoops_GPIGR, _hoops_IRSRA);
	    _hoops_PASRA(&p->_hoops_IIIRA, _hoops_GPIGR, _hoops_IRSRA);
	    for (int i = 0 ; i < _hoops_GPIGR ; i++) {
			p->_hoops_PIIRA[i] = points[i];
			p->_hoops_IIIRA[i] = indices[i];
			if (normals)
			    p->_hoops_HIIRA[i] = normals[i];
	    }
    }

	return true;
}


/* _hoops_SSAP _hoops_HSSP _hoops_HPHS _hoops_HII _hoops_IRS _hoops_RRCPR */
local bool _hoops_CHRAA (
	_hoops_IGCRA	*	_hoops_IRSRA,					/* _hoops_RSPHR _hoops_PIH _hoops_HRPR */
	_hoops_AIIRA *		p,					/* _hoops_HSSP _hoops_SR _hoops_CHR _hoops_SHRAA _hoops_GGR */
	Point const	*		points,				/* _hoops_RRCPR _hoops_PPSR _hoops_HIGR */
	int const *			_hoops_ASPH,				/* _hoops_RRCPR _hoops_HSP _hoops_HIGR */
	Vector const *		normals,			/* _hoops_RRCPR _hoops_GSSR _hoops_HIGR */
	int		    		position,			/* _hoops_APHR _hoops_AHC _hoops_GGR _hoops_RH _hoops_HSP _hoops_HIGR _hoops_IIGR _hoops_RH _hoops_HSSP */
	bool				invert,
	bool				_hoops_GIRAA,
	double				_hoops_CAIRA)		/* _hoops_RGAR _hoops_PSIGA _hoops_RPP _hoops_SCGR _hoops_CAIH _hoops_HRGR _hoops_RIRAA. */
											/* _hoops_RAP _hoops_IHPR _hoops_RPP _hoops_SR _hoops_CHR _hoops_AIRAA _hoops_RH "_hoops_SGCRA", _hoops_RCPP */
											/* _hoops_RPP _hoops_AIRAA _hoops_RH _hoops_SAAP. _hoops_HGI _hoops_PIRAA _hoops_RGSR _hoops_RH */
											/* _hoops_AAPI _hoops_SSPC _hoops_RIP _hoops_IH _hoops_SCSRA _hoops_SGS _hoops_CHR _hoops_SIPP */
											/* _hoops_RH _hoops_IRPR _hoops_IASC _hoops_HIAHR.  _hoops_HGI _hoops_PPRRR _hoops_SR _hoops_PAH */
											/* _hoops_SRCH _hoops_HIRAA _hoops_SCSRA _hoops_RHIR _hoops_RH _hoops_IPHRA _hoops_CPHRA _hoops_SGS _hoops_GA'_hoops_RA _hoops_RRP _hoops_SCH. */
{						  
 
    /* _hoops_SIPR _hoops_RH _hoops_IASC _hoops_HIAHR _hoops_IIGR _hoops_RH _hoops_CII _hoops_PPR _hoops_ASH _hoops_IIRAA */
	_hoops_APCIR	_hoops_CIRAA = _hoops_IRSRA->_hoops_CGCRA.min;
	_hoops_APCIR	_hoops_SIRAA = _hoops_IRSRA->_hoops_CGCRA.max;
	_hoops_APCIR	_hoops_GCRAA = _hoops_IRSRA->_hoops_GRCRA.min;
	_hoops_APCIR	_hoops_RCRAA = _hoops_IRSRA->_hoops_GRCRA.max;

    /* _hoops_CCPP _hoops_RH _hoops_RSSA, _hoops_ASGA, _hoops_PPR _hoops_PPSR _hoops_PSPI _hoops_SIRGR _hoops_GGR _hoops_RH _hoops_SCIRA */
    if (p->_hoops_PIIRA)
		_hoops_RASRA(p->_hoops_PIIRA, p->_hoops_ICIRA, _hoops_IRSRA);
		
    p->_hoops_ICIRA = _hoops_ASPH[position];
    _hoops_SRSRA(&p->_hoops_PIIRA, p->_hoops_ICIRA, _hoops_IRSRA);

    if (normals)
		_hoops_GASRA(&p->_hoops_HIIRA, p->_hoops_ICIRA, _hoops_IRSRA);
		
    _hoops_PASRA(&p->_hoops_IIIRA, p->_hoops_ICIRA, _hoops_IRSRA); 	

   
    /* _hoops_ACRAA _hoops_RH _hoops_RSSA _hoops_PIH. _hoops_PCRAA _hoops_SR _hoops_CHR _hoops_HPGR _hoops_SCH, _hoops_RIPHR _hoops_IRS _hoops_IASC _hoops_AHCRR _hoops_IH _hoops_RH _hoops_HSSP */

	Point min, max;
	min.x = max.x = points[_hoops_ASPH[position+1]].x;
	min.y = max.y = points[_hoops_ASPH[position+1]].y;
	min.z = max.z = points[_hoops_ASPH[position+1]].z;
    
 	for (int i = 0 ; i < p->_hoops_ICIRA ; i++) {

		int ii;

		if (!_hoops_GIRAA)
			ii = i;
		else
			ii = p->_hoops_ICIRA - i - 1;

		_hoops_APCIR *	points2 = &p->_hoops_PIIRA[ii];
	    points2->x = points[_hoops_ASPH[position+1+i]].x;
	    points2->y = points[_hoops_ASPH[position+1+i]].y;
	    points2->z = points[_hoops_ASPH[position+1+i]].z; 
	    
	    if (min.x > points2->x)
			min.x = points2->x;
	    if (min.y > points2->y)
			min.y = points2->y;
	    if (min.z > points2->z)
			min.z = points2->z;
	    if (max.x < points2->x)
			max.x = points2->x;
	    if (max.y < points2->y)
			max.y = points2->y;
	    if (max.z < points2->z)
			max.z = points2->z;

 	    if (normals) {	    
			p->_hoops_HIIRA[ii].x = normals[_hoops_ASPH[position+1+i]].x;
			p->_hoops_HIIRA[ii].y = normals[_hoops_ASPH[position+1+i]].y;
			p->_hoops_HIIRA[ii].z = normals[_hoops_ASPH[position+1+i]].z;
	    }
	    p->_hoops_IIIRA[ii] = _hoops_ASPH[position+1+i];	    
	}
	
	/* _hoops_CGP _hoops_SR _hoops_CHR _hoops_GGR _hoops_ICHRA _hoops_CCH _hoops_PPR _hoops_CHR _hoops_GPIHR _hoops_GGR _hoops_HCRAA _hoops_AAPI, */
	/* _hoops_PSCR _hoops_SR _hoops_HHGC _hoops_IS _hoops_AA _hoops_IRS _hoops_IGRH _hoops_IIGR _hoops_CHCRA.  _hoops_PS _hoops_CHR _hoops_CPIC _hoops_IS _hoops_ARP _hoops_RH */
	/* _hoops_SSPC _hoops_SGI _hoops_IH _hoops_AAPI _hoops_SGS _hoops_CHR _hoops_SIPP _hoops_RH _hoops_SGCRA/_hoops_ICRAA _hoops_SGSSR. */
	if (_hoops_IRSRA->_hoops_RRCRA == _hoops_SRGAA && _hoops_IRSRA->_hoops_PRCRA) {	
	    if (!invert) {
			/* _hoops_SR _hoops_CHR _hoops_HCHAR _hoops_HPGR _hoops_RH _hoops_SAAP _hoops_AAPI.  _hoops_GHIAR _hoops_CAPR _hoops_RPP _hoops_SSIA */
			/* _hoops_CHR _hoops_SIPP _hoops_RH _hoops_CII _hoops_IASC _hoops_AHCRR. */
			if (max.x < _hoops_CIRAA.x || min.x > _hoops_SIRAA.x || max.y < _hoops_CIRAA.y || min.y > _hoops_SIRAA.y ||
			     max.z < _hoops_CIRAA.z || min.z > _hoops_SIRAA.z)
			    p->_hoops_GGCRA = true;
		}
		else {
			/* _hoops_SR _hoops_CHR _hoops_HCHAR _hoops_HPGR _hoops_RH _hoops_CII _hoops_AAPI.  _hoops_GHIAR _hoops_CAPR _hoops_RPP _hoops_SSIA */
			/* _hoops_CHR _hoops_SIPP _hoops_RH _hoops_HCSS _hoops_IASC _hoops_AHCRR. */
			if (max.x < _hoops_GCRAA.x || min.x > _hoops_RCRAA.x || max.y < _hoops_GCRAA.y || min.y > _hoops_RCRAA.y ||
			     max.z < _hoops_GCRAA.z || min.z > _hoops_RCRAA.z)
				p->_hoops_GGCRA = true;
	    }
	}
	        
    return (_hoops_HRRAA(p, _hoops_CAIRA));
}

/* _hoops_SSAP _hoops_HSSP _hoops_HPHS _hoops_HII _hoops_IRS _hoops_RRCPR, _hoops_CCRAA _hoops_SCRAA _hoops_CSPP */
local bool _hoops_IPSRA (
	_hoops_IGCRA *	_hoops_IRSRA,					/* _hoops_RSPHR _hoops_PIH _hoops_HRPR */
	_hoops_AIIRA *		p,					/* _hoops_HSSP _hoops_SR _hoops_CHR _hoops_SHRAA _hoops_GGR */
	_hoops_APCIR const *		points,				/* _hoops_RRCPR _hoops_PPSR _hoops_HIGR */
	int const *			_hoops_ASPH,				/* _hoops_RRCPR _hoops_HSP _hoops_HIGR */
	Vector const *		normals,			/* _hoops_RRCPR _hoops_GSSR _hoops_HIGR */
	int		    		position,			/* _hoops_APHR _hoops_AHC _hoops_GGR _hoops_RH _hoops_HSP _hoops_HIGR _hoops_IIGR _hoops_RH _hoops_HSSP */
	bool				invert,
	bool				_hoops_GIRAA,
	double				_hoops_CAIRA)		/* _hoops_RGAR _hoops_PSIGA _hoops_RPP _hoops_SCGR _hoops_CAIH _hoops_HRGR _hoops_RIRAA. */
											/* _hoops_RAP _hoops_IHPR _hoops_RPP _hoops_SR _hoops_CHR _hoops_AIRAA _hoops_RH "_hoops_SGCRA", _hoops_RCPP */
											/* _hoops_RPP _hoops_AIRAA _hoops_RH _hoops_SAAP. _hoops_HGI _hoops_PIRAA _hoops_RGSR _hoops_RH */
											/* _hoops_AAPI _hoops_SSPC _hoops_RIP _hoops_IH _hoops_SCSRA _hoops_SGS _hoops_CHR _hoops_SIPP */
											/* _hoops_RH _hoops_IRPR _hoops_IASC _hoops_HIAHR.  _hoops_HGI _hoops_PPRRR _hoops_SR _hoops_PAH */
											/* _hoops_SRCH _hoops_HIRAA _hoops_SCSRA _hoops_RHIR _hoops_RH _hoops_IPHRA _hoops_CPHRA _hoops_SGS _hoops_GA'_hoops_RA */
											/* _hoops_RRP _hoops_SCH. */
{						  
	/* _hoops_SIPR _hoops_RH _hoops_IASC _hoops_HIAHR _hoops_IIGR _hoops_RH _hoops_CII _hoops_PPR _hoops_ASH _hoops_IIRAA */
	_hoops_APCIR	_hoops_CIRAA = _hoops_IRSRA->_hoops_CGCRA.min;
	_hoops_APCIR	_hoops_SIRAA = _hoops_IRSRA->_hoops_CGCRA.max;
	_hoops_APCIR	_hoops_GCRAA = _hoops_IRSRA->_hoops_GRCRA.min;
	_hoops_APCIR	_hoops_RCRAA = _hoops_IRSRA->_hoops_GRCRA.max;

    /* _hoops_CCPP _hoops_RH _hoops_RSSA, _hoops_ASGA, _hoops_PPR _hoops_PPSR _hoops_GSRAA _hoops_SIRGR _hoops_GGR _hoops_RH _hoops_SCIRA */
    if (p->_hoops_PIIRA)
		_hoops_RASRA(p->_hoops_PIIRA, p->_hoops_ICIRA, _hoops_IRSRA);
		
    p->_hoops_ICIRA = _hoops_ASPH[position];
    _hoops_SRSRA(&p->_hoops_PIIRA, p->_hoops_ICIRA, _hoops_IRSRA);

    if (normals)
		_hoops_GASRA(&p->_hoops_HIIRA, p->_hoops_ICIRA, _hoops_IRSRA);
		
    _hoops_PASRA(&p->_hoops_IIIRA, p->_hoops_ICIRA, _hoops_IRSRA); 	

    /* _hoops_ACRAA _hoops_RH _hoops_RSSA _hoops_PIH. _hoops_PCRAA _hoops_SR _hoops_CHR _hoops_HPGR _hoops_SCH, _hoops_RIPHR _hoops_IRS _hoops_IASC _hoops_AHCRR _hoops_IH _hoops_RH _hoops_HSSP */
	_hoops_APCIR	min = points[_hoops_ASPH[position+1]];
	_hoops_APCIR	max = points[_hoops_ASPH[position+1]];
    
 	for (int i = 0 ; i < p->_hoops_ICIRA ; i++) {

		int ii;
		if (!_hoops_GIRAA)
			ii = i;
		else
			ii = p->_hoops_ICIRA - i - 1;

		_hoops_APCIR *	points2;
	    points2 = &p->_hoops_PIIRA[ii];
	    points2->x = points[_hoops_ASPH[position+1+i]].x;
	    points2->y = points[_hoops_ASPH[position+1+i]].y;
	    points2->z = points[_hoops_ASPH[position+1+i]].z; 
	    
	    if (min.x > points2->x)
			min.x = points2->x;
	    if (min.y > points2->y)
			min.y = points2->y;
	    if (min.z > points2->z)
			min.z = points2->z;
	    if (max.x < points2->x)
			max.x = points2->x;
	    if (max.y < points2->y)
			max.y = points2->y;
	    if (max.z < points2->z)
			max.z = points2->z;

 	    if (normals) {	    
			p->_hoops_HIIRA[ii].x = normals[_hoops_ASPH[position+1+i]].x;
			p->_hoops_HIIRA[ii].y = normals[_hoops_ASPH[position+1+i]].y;
			p->_hoops_HIIRA[ii].z = normals[_hoops_ASPH[position+1+i]].z;
	    }
	    p->_hoops_IIIRA[ii] = _hoops_ASPH[position+1+i];	    
	}
	
	/* _hoops_CGP _hoops_SR _hoops_CHR _hoops_GGR _hoops_ICHRA _hoops_CCH _hoops_PPR _hoops_CHR _hoops_GPIHR _hoops_GGR _hoops_HCRAA _hoops_AAPI, */
	/* _hoops_PSCR _hoops_SR _hoops_HHGC _hoops_IS _hoops_AA _hoops_IRS _hoops_IGRH _hoops_IIGR _hoops_CHCRA.  _hoops_PS _hoops_CHR _hoops_CPIC _hoops_IS _hoops_ARP _hoops_RH */
	/* _hoops_SSPC _hoops_SGI _hoops_IH _hoops_AAPI _hoops_SGS _hoops_CHR _hoops_SIPP _hoops_RH _hoops_SGCRA/_hoops_ICRAA _hoops_SGSSR. */
	if (_hoops_IRSRA->_hoops_RRCRA == _hoops_SRGAA && _hoops_IRSRA->_hoops_PRCRA) {	
	    if (!invert) {
			/* _hoops_SR _hoops_CHR _hoops_HCHAR _hoops_HPGR _hoops_RH _hoops_SAAP _hoops_AAPI.  _hoops_GHIAR _hoops_CAPR _hoops_RPP _hoops_SSIA */
			/* _hoops_CHR _hoops_SIPP _hoops_RH _hoops_CII _hoops_IASC _hoops_AHCRR. */
			if (max.x < _hoops_CIRAA.x || min.x > _hoops_SIRAA.x || max.y < _hoops_CIRAA.y || min.y > _hoops_SIRAA.y ||
			     max.z < _hoops_CIRAA.z || min.z > _hoops_SIRAA.z)
			    p->_hoops_GGCRA = true;
		}
		else {
			/* _hoops_SR _hoops_CHR _hoops_HCHAR _hoops_HPGR _hoops_RH _hoops_CII _hoops_AAPI.  _hoops_GHIAR _hoops_CAPR _hoops_RPP _hoops_SSIA */
			/* _hoops_CHR _hoops_SIPP _hoops_RH _hoops_HCSS _hoops_IASC _hoops_AHCRR. */
			if (max.x < _hoops_GCRAA.x || min.x > _hoops_RCRAA.x || max.y < _hoops_GCRAA.y || min.y > _hoops_RCRAA.y ||
			     max.z < _hoops_GCRAA.z || min.z > _hoops_RCRAA.z)
				p->_hoops_GGCRA = true;
	    }
	}
	        
    return (_hoops_HRRAA(p, _hoops_CAIRA));
}
  
/* _hoops_RSRAA _hoops_IRS _hoops_HSSP _hoops_SGS _hoops_HRGR _hoops_ASRAA _hoops_HPP _hoops_IRS _hoops_RAGA _hoops_IPPA */
local void _hoops_PSRAA (
	_hoops_IGCRA	*	_hoops_IRSRA,		/* "_hoops_ISHGR" _hoops_PIH _hoops_SR _hoops_SGH _hoops_GGR _hoops_RH _hoops_AIHGR _hoops_SICAR */
	_hoops_AIIRA *		p,			/* _hoops_RH _hoops_HSSP _hoops_IS _hoops_HHGP */
	_hoops_AAIRA *			part,		/* _hoops_RH _hoops_IPPA _hoops_SGS _hoops_HSRAA _hoops_RH _hoops_HSSP */
	_hoops_AIIRA **		_hoops_ISRAA,	/* "_hoops_RIPS" _hoops_ARGR _hoops_HSSP */
	_hoops_AIIRA **		_hoops_SIPI, 	/* "_hoops_ISSC" _hoops_ARGR _hoops_HSSP */
	double				_hoops_IASGA)		/* _hoops_AAHP _hoops_PIRA _hoops_IS _hoops_SGH */
{
    int count = p->_hoops_ICIRA;
    int _hoops_CSRAA = 0, _hoops_SSRAA = 0;
    _hoops_APCIR _hoops_GGAAA, _hoops_RGAAA;
    _hoops_PPCIR _hoops_AGAAA, _hoops_PGAAA;
    _hoops_APCIR _hoops_HGAAA[128];
    _hoops_APCIR _hoops_IGAAA[128];
    _hoops_PPCIR _hoops_CGAAA[128];
    _hoops_PPCIR _hoops_SGAAA[128];
    int _hoops_GRAAA[128];
    int _hoops_RRAAA[128];
    int _hoops_ARAAA;
    int _hoops_PRAAA;
    double _hoops_HRAAA, _hoops_IRAAA;
    bool _hoops_CRAAA = false;
    int _hoops_SRAAA = 0, _hoops_GAAAA = 0;
    bool _hoops_RAAAA, _hoops_AAAAA;
	POINTER_SIZED_INT _hoops_HCIRA[128];
	int _hoops_PSIRA = 0;

    ZERO_STRUCT(&_hoops_PGAAA, _hoops_APCIR);
 
    _hoops_GGAAA = p->_hoops_PIIRA[count - 1];
    
    if (p->_hoops_HIIRA) {
		_hoops_CRAAA = true;
		_hoops_AGAAA = p->_hoops_HIIRA[count - 1];
    }
    _hoops_ARAAA = p->_hoops_IIIRA[count - 1];

    _hoops_HRAAA = _hoops_PIGAA(part, &_hoops_GGAAA);
   

    /* _hoops_IPCP _hoops_CSCS _hoops_IHGRA _hoops_ARI _hoops_HRGR _hoops_SGS _hoops_SR _hoops_IHSH _hoops_HPGR _hoops_GRR _hoops_ISHA _hoops_IIGR _hoops_RH _hoops_HSSP. */
    /* _hoops_CGP _hoops_SCH _hoops_HRGR _hoops_ASRAA _hoops_HPP _hoops_RH _hoops_IPPA, _hoops_PSCR _hoops_SR _hoops_CSGA _hoops_RH _hoops_SGSSR */
    /* _hoops_PPSR _hoops_PPR _hoops_GGCR _hoops_IRS _hoops_CCAH _hoops_GPHA _hoops_IH _hoops_SGS _hoops_PPSR _hoops_GGR _hoops_GIPR _hoops_RH _hoops_RIPS _hoops_PPR _hoops_ISSC */
    /* _hoops_AAPI. _hoops_PS _hoops_HS _hoops_IS _hoops_RIPHR _hoops_RH _hoops_ASSA _hoops_PPR _hoops_SIPP _hoops_AAPI _hoops_GGR _hoops_RH _hoops_RPHR */
    /* _hoops_AGR _hoops_IS _hoops_RHHSR _hoops_RSSP. */
    for (int i = 0 ; i < count ; i++) {
		_hoops_RGAAA = p->_hoops_PIIRA[i];
		if (_hoops_CRAAA)
		    _hoops_PGAAA = p->_hoops_HIIRA[i];
		_hoops_PRAAA = p->_hoops_IIIRA[i];

		/* _hoops_CRSR _hoops_PPAP _hoops_IIGR _hoops_RH _hoops_IPPA _hoops_HRGR _hoops_RH _hoops_IHAC _hoops_PPSR _hoops_GPP? */
		_hoops_IRAAA = _hoops_PIGAA(part, &_hoops_RGAAA);
	 	if (_hoops_IRAAA > _hoops_IASGA) {
		    /* _hoops_IHAC _hoops_PPSR _hoops_GGR _hoops_RIPS _hoops_IIGR _hoops_RH _hoops_IPPA. */
		    _hoops_SRAAA++;
		    if (_hoops_HRAAA < -_hoops_IASGA) {
				/* _hoops_RAIGR _hoops_PPAP _hoops_HRGR _hoops_GGR _hoops_ISSC _hoops_IIGR _hoops_RH _hoops_IPPA, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IS _hoops_HHGP _hoops_RH _hoops_ISHA */
				/* _hoops_PPR _hoops_ASH _hoops_RH _hoops_CCAH _hoops_GPHA _hoops_CRGR _hoops_GIPR _hoops_RH _hoops_SIPP _hoops_PPR _hoops_ASSA _hoops_CPCI. */
				_hoops_PPCIR v = _hoops_RGAAA - _hoops_GGAAA;	
		 		_hoops_PPCIR normal = _hoops_PPCIR(*part)._hoops_AAIAR();
		  		double _hoops_PAAAA = -_hoops_HRAAA / normal._hoops_SSRP(_hoops_PPCIR(v));

				_hoops_HGAAA[_hoops_CSRAA] = _hoops_GGAAA + v * _hoops_PAAAA;

				if (_hoops_CRAAA) {
				    _hoops_RARAA(_hoops_GGAAA, _hoops_AGAAA, _hoops_RGAAA, _hoops_PGAAA, _hoops_HGAAA[_hoops_CSRAA], _hoops_CGAAA[_hoops_CSRAA]);
					_hoops_SGAAA[_hoops_SSRAA] = _hoops_CGAAA[_hoops_CSRAA];
				}

				_hoops_HCIRA[_hoops_PSIRA++] = _hoops_RRAAA[_hoops_SSRAA] = _hoops_GRAAA[_hoops_CSRAA] = p->_hoops_SIIRA->_hoops_SHIRA;
				p->_hoops_SIIRA->_hoops_SHIRA++;
				_hoops_IGAAA[_hoops_SSRAA++] = _hoops_HGAAA[_hoops_CSRAA++];
		    }

		    /* _hoops_CPGP _hoops_IHAC _hoops_HRGR _hoops_HAAAA _hoops_IIGR _hoops_RH _hoops_IPPA, _hoops_ASH _hoops_SCH _hoops_ASSA _hoops_RH _hoops_SIPP _hoops_HIGR */
		    if (_hoops_CRAAA)
				_hoops_CGAAA[_hoops_CSRAA] = _hoops_PGAAA;
		    _hoops_GRAAA[_hoops_CSRAA] = _hoops_PRAAA;
		    _hoops_HGAAA[_hoops_CSRAA++] = _hoops_RGAAA;
		}
		else if (_hoops_IRAAA < -_hoops_IASGA) {
		    /* _hoops_IHAC _hoops_PPSR _hoops_GGR _hoops_ISSC _hoops_IIGR _hoops_RH _hoops_IPPA */
		    _hoops_GAAAA++;
		    if (_hoops_HRAAA > _hoops_IASGA) {
				/* _hoops_ASCGR _hoops_HRGR _hoops_HHGP _hoops_HPP _hoops_RH _hoops_IPPA.  _hoops_GCRR _hoops_IRS _hoops_CCAH _hoops_GPHA _hoops_HPGR _hoops_RH _hoops_HHGP _hoops_PPSR */
				/* _hoops_PPR _hoops_GGCR _hoops_SCH _hoops_IS _hoops_GIPR _hoops_IIGR _hoops_RH _hoops_ASSA _hoops_PPR _hoops_SIPP _hoops_AAPI. */
				_hoops_PPCIR v = _hoops_RGAAA - _hoops_GGAAA;	
				_hoops_PPCIR normal = _hoops_PPCIR(*part)._hoops_AAIAR();
				double _hoops_PAAAA = -_hoops_HRAAA / normal._hoops_SSRP(v);

				_hoops_HGAAA[_hoops_CSRAA] = _hoops_GGAAA + v * _hoops_PAAAA;
	
				if (_hoops_CRAAA) {
				    _hoops_RARAA(_hoops_GGAAA,_hoops_AGAAA,_hoops_RGAAA,_hoops_PGAAA,_hoops_HGAAA[_hoops_CSRAA],_hoops_CGAAA[_hoops_CSRAA]);
					_hoops_SGAAA[_hoops_SSRAA] = _hoops_CGAAA[_hoops_CSRAA];
				}
				
				_hoops_HCIRA[_hoops_PSIRA++] = _hoops_RRAAA[_hoops_SSRAA] = _hoops_GRAAA[_hoops_CSRAA] = p->_hoops_SIIRA->_hoops_SHIRA;
				p->_hoops_SIIRA->_hoops_SHIRA++;
				_hoops_IGAAA[_hoops_SSRAA++] = _hoops_HGAAA[_hoops_CSRAA++];	    
		    }

		    /* _hoops_CR _hoops_IHAC _hoops_HRGR _hoops_GGR _hoops_ISSC _hoops_IIGR _hoops_RH _hoops_IPPA, _hoops_ASH _hoops_SCH _hoops_GGR _hoops_RH _hoops_ASSA _hoops_HIGR. */
		    _hoops_RRAAA[_hoops_SSRAA] = _hoops_PRAAA;
		    if (_hoops_CRAAA)
				_hoops_SGAAA[_hoops_SSRAA] = _hoops_PGAAA;
		    _hoops_IGAAA[_hoops_SSRAA++] = _hoops_RGAAA;
		}	
		else {
			 /* _hoops_PPSR _hoops_IHAC _hoops_HRGR _hoops_GPP _hoops_RH _hoops_HPPA _hoops_IPPA. _hoops_HHIGR'_hoops_GRI _hoops_ARIP _hoops_IIGR _hoops_GIPR _hoops_AAPI. */
			_hoops_RRAAA[_hoops_SSRAA] = _hoops_GRAAA[_hoops_CSRAA] = p->_hoops_SIIRA->_hoops_SHIRA;
			p->_hoops_SIIRA->_hoops_SHIRA++;
			if (_hoops_CRAAA)
			 	_hoops_CGAAA[_hoops_CSRAA] = _hoops_SGAAA[_hoops_SSRAA] = _hoops_PGAAA;
			_hoops_HGAAA[_hoops_CSRAA++] = _hoops_IGAAA[_hoops_SSRAA++] = _hoops_RGAAA;
		 }
		 _hoops_ARAAA = _hoops_PRAAA;
		 _hoops_AGAAA = _hoops_PGAAA;

		 _hoops_GGAAA = _hoops_RGAAA;
		 _hoops_HRAAA = _hoops_IRAAA;
    }
    _hoops_HRSRA(_hoops_ISRAA, _hoops_IRSRA);
    _hoops_HRSRA(_hoops_SIPI, _hoops_IRSRA);
 
    /* _hoops_HCRS _hoops_IAISR _hoops_PPR _hoops_RIPHR _hoops_AAPI _hoops_HII _hoops_ISCP _hoops_CPCI */
    if (_hoops_CRAAA) {    
		_hoops_IHRAA(_hoops_IRSRA, *_hoops_ISRAA, _hoops_HGAAA, _hoops_CSRAA, _hoops_GRAAA, _hoops_CGAAA, p->_hoops_SIIRA, p);
		_hoops_IHRAA(_hoops_IRSRA, *_hoops_SIPI, _hoops_IGAAA, _hoops_SSRAA, _hoops_RRAAA, _hoops_SGAAA, p->_hoops_SIIRA, p);
    }
    else {     
		_hoops_RAAAA = _hoops_IHRAA(_hoops_IRSRA, *_hoops_ISRAA, _hoops_HGAAA, _hoops_CSRAA, _hoops_GRAAA, 0, p->_hoops_SIIRA, p);
		_hoops_AAAAA = _hoops_IHRAA(_hoops_IRSRA, *_hoops_SIPI, _hoops_IGAAA, _hoops_SSRAA, _hoops_RRAAA, 0, p->_hoops_SIIRA, p);		    	

		(*_hoops_ISRAA)->_hoops_CSIRA = p->_hoops_CSIRA;
		(*_hoops_SIPI)->_hoops_CSIRA = p->_hoops_CSIRA;
		(*_hoops_ISRAA)->_hoops_SSIRA = p->_hoops_SSIRA;
		(*_hoops_SIPI)->_hoops_SSIRA = p->_hoops_SSIRA;
    }

    /* _hoops_IH _hoops_HSP _hoops_CGRSR. */
    (*_hoops_ISRAA)->_hoops_CCIRA = p->_hoops_CCIRA;
	(*_hoops_ISRAA)->_hoops_RSIRA = p->_hoops_RSIRA + 1;
	(*_hoops_ISRAA)->_hoops_ACIRA = p;
    (*_hoops_SIPI)->_hoops_CCIRA = p->_hoops_CCIRA;
	(*_hoops_SIPI)->_hoops_RSIRA = p->_hoops_RSIRA + 1;
	(*_hoops_SIPI)->_hoops_ACIRA = p;

	/* _hoops_SR _hoops_IPS _hoops_RH _hoops_CCAH _hoops_GPHA _hoops_PSPI _hoops_CRGR _hoops_RH _hoops_IRPR _hoops_AAAPR _hoops_IH _hoops_RH _hoops_RIPS
		_hoops_PPR _hoops_ISSC _hoops_RSSI */
	if (_hoops_PSIRA) {
		(*_hoops_ISRAA)->_hoops_PSIRA = _hoops_PSIRA;
		ALLOC_ARRAY((*_hoops_ISRAA)->_hoops_HCIRA, (*_hoops_ISRAA)->_hoops_PSIRA, POINTER_SIZED_INT);
		(*_hoops_SIPI)->_hoops_PSIRA = _hoops_PSIRA;
		ALLOC_ARRAY((*_hoops_SIPI)->_hoops_HCIRA, (*_hoops_SIPI)->_hoops_PSIRA, POINTER_SIZED_INT);

		for (int i = 0 ; i < _hoops_PSIRA ; i++) {
			(*_hoops_ISRAA)->_hoops_HCIRA[i] = _hoops_HCIRA[i];
			(*_hoops_SIPI)->_hoops_HCIRA[i] = _hoops_HCIRA[i];
		}
	}

    _hoops_IGGAA("Front", *_hoops_ISRAA);
    _hoops_IGGAA("Back", *_hoops_SIPI);
} 



/* _hoops_RSRAA _hoops_IRS _hoops_HSSP _hoops_SGS _hoops_HRGR _hoops_ASRAA _hoops_HPP _hoops_IRS _hoops_RAGA _hoops_IPPA */
/* _hoops_HGI _hoops_HRGR _hoops_IRS _hoops_SPAC _hoops_CSPP _hoops_HSAR _hoops_IAAAA _hoops_PGGA _hoops_SCH */
/* _hoops_ASSP'_hoops_RA _hoops_HPPR _hoops_IS _hoops_RHHSR _hoops_RH _hoops_GIGR _hoops_RRCPR _hoops_PIH, _hoops_SCH _hoops_SAHR */
/* _hoops_CAAAA _hoops_AHCA _hoops_IGGA _hoops_SAAAA.  _hoops_HGI _hoops_HRGR _hoops_IGI _hoops_CGPR _hoops_RICPR */
/* _hoops_IPCP _hoops_IPHRA _hoops_CPHRA. */
local int _hoops_GPAAA (
	_hoops_IGCRA	*	_hoops_IRSRA,
	_hoops_AIIRA *		p,  
	_hoops_AAIRA *			part,
	_hoops_AIIRA **		_hoops_ISRAA, 
	_hoops_AIIRA **		_hoops_SIPI,
	double				_hoops_IASGA) 
{
    int 			count = p->_hoops_ICIRA;
	int 			_hoops_CSRAA = 0;
	int				_hoops_SSRAA = 0;
	_hoops_APCIR 			_hoops_GGAAA;
	_hoops_APCIR 			_hoops_RGAAA;
    _hoops_APCIR 			_hoops_HGAAA[128];
    _hoops_APCIR 			_hoops_IGAAA[128];
	int 			_hoops_SRAAA = 0; 
	int				_hoops_GAAAA = 0;
	double 		    _hoops_HRAAA;
	double		    _hoops_IRAAA;
	int             _hoops_HGII = 0;
 
    /* _hoops_IPCP _hoops_CSCS _hoops_IHGRA _hoops_ARI _hoops_HRGR _hoops_SGS _hoops_SR _hoops_IHSH _hoops_HPGR _hoops_GRR _hoops_ISHA _hoops_IIGR _hoops_RH _hoops_HSSP. */
    /* _hoops_CGP _hoops_SCH _hoops_HRGR _hoops_ASRAA _hoops_HPP _hoops_RH _hoops_IPPA, _hoops_PSCR _hoops_SR _hoops_CSGA _hoops_RH _hoops_SGSSR */
    /* _hoops_PPSR _hoops_PPR _hoops_GGCR _hoops_IRS _hoops_CCAH _hoops_GPHA _hoops_IH _hoops_SGS _hoops_PPSR _hoops_GGR _hoops_GIPR _hoops_RH _hoops_RIPS _hoops_PPR _hoops_ISSC */
    /* _hoops_AAPI. _hoops_PS _hoops_HS _hoops_IS _hoops_RIPHR _hoops_RH _hoops_ASSA _hoops_PPR _hoops_SIPP _hoops_AAPI _hoops_GGR _hoops_RH _hoops_RPHR */
    /* _hoops_AGR _hoops_IS _hoops_RHHSR _hoops_RSSP. */

    _hoops_GGAAA = p->_hoops_PIIRA[count - 1];
    
    _hoops_HRAAA = _hoops_PIGAA(part, &_hoops_GGAAA);
    for (int i = 0 ; i < count ; i++) {
		_hoops_RGAAA = p->_hoops_PIIRA[i];
	    _hoops_IRAAA = _hoops_PIGAA(part, &_hoops_RGAAA);
	
	 	if (_hoops_IRAAA > _hoops_IASGA) {
		    /* _hoops_IHAC _hoops_HRGR _hoops_SIPP _hoops_RH _hoops_IPPA. */
		    _hoops_SRAAA++;
		    if (_hoops_HRAAA < -_hoops_IASGA) {
				/* _hoops_ASCGR _hoops_HRGR _hoops_HHGP _hoops_HPP _hoops_RH _hoops_IPPA.  _hoops_GCRR _hoops_IRS _hoops_CCAH _hoops_GPHA _hoops_HPGR _hoops_RH _hoops_HHGP _hoops_PPSR */
				/* _hoops_PPR _hoops_GGCR _hoops_SCH _hoops_IS _hoops_GIPR _hoops_IIGR _hoops_RH _hoops_ASSA _hoops_PPR _hoops_SIPP _hoops_AAPI. */
				_hoops_PPCIR v = _hoops_RGAAA - _hoops_GGAAA; 
				_hoops_PPCIR	normal = _hoops_PPCIR(*part)._hoops_AAIAR();
		  		double _hoops_PAAAA = -_hoops_HRAAA / normal._hoops_SSRP(v);

				_hoops_HGAAA[_hoops_CSRAA] = _hoops_GGAAA + v * _hoops_PAAAA;
		 		_hoops_IGAAA[_hoops_SSRAA++] = _hoops_HGAAA[_hoops_CSRAA++];
		    }

		    /* _hoops_RGPA _hoops_IHAC _hoops_IS _hoops_RH _hoops_SIPP _hoops_HIGR */
		    _hoops_HGAAA[_hoops_CSRAA++] = _hoops_RGAAA;
		}
		else if (_hoops_IRAAA < -_hoops_IASGA) {
		    /* _hoops_IHAC _hoops_HRGR _hoops_ASSA _hoops_RH _hoops_IPPA */
		    _hoops_GAAAA++;
		    if (_hoops_HRAAA > _hoops_IASGA) {
				/* _hoops_ASCGR _hoops_HRGR _hoops_HHGP _hoops_HPP _hoops_RH _hoops_IPPA. _hoops_GCRR _hoops_IRS _hoops_CCAH _hoops_GPHA _hoops_HPGR _hoops_RH _hoops_HHGP _hoops_PPSR */
				/* _hoops_PPR _hoops_GGCR _hoops_SCH _hoops_IS _hoops_GIPR _hoops_AAPI. */
				_hoops_PPCIR v = _hoops_RGAAA - _hoops_GGAAA; 
				_hoops_PPCIR	normal = _hoops_PPCIR(*part)._hoops_AAIAR();
		   		double _hoops_PAAAA = -_hoops_HRAAA / normal._hoops_SSRP(v);
		
				_hoops_HGAAA[_hoops_CSRAA] = _hoops_GGAAA + v * _hoops_PAAAA;
		 		_hoops_IGAAA[_hoops_SSRAA++] = _hoops_HGAAA[_hoops_CSRAA++];	    
		    }

		    /* _hoops_RGPA _hoops_IHAC _hoops_IS _hoops_RH _hoops_ASSA _hoops_HIGR. */
		    _hoops_IGAAA[_hoops_SSRAA++] = _hoops_RGAAA;
		}	
		else {
			/* _hoops_IHAC _hoops_HRGR _hoops_GPP _hoops_RH _hoops_IPPA, _hoops_HIS _hoops_SCH'_hoops_GRI _hoops_ARIP _hoops_IIGR _hoops_GIPR _hoops_AAPI. */
		    _hoops_HGAAA[_hoops_CSRAA++] = _hoops_IGAAA[_hoops_SSRAA++] = _hoops_RGAAA;
		}
		_hoops_GGAAA = _hoops_RGAAA;
		_hoops_HRAAA = _hoops_IRAAA;
    }

	if (_hoops_SRAAA && !_hoops_GAAAA)
		_hoops_HGII = _hoops_GHIRA;
    else if (_hoops_GAAAA && !_hoops_SRAAA)
		_hoops_HGII = _hoops_RHIRA;
    else if (!_hoops_SRAAA && !_hoops_GAAAA)
		_hoops_HGII = _hoops_AHIRA;
    else
		_hoops_HGII = _hoops_PHIRA;

	if (_hoops_HGII == _hoops_PHIRA) {
		_hoops_HRSRA(_hoops_ISRAA, _hoops_IRSRA);
		_hoops_HRSRA(_hoops_SIPI, _hoops_IRSRA);

		/* _hoops_GPIPR _hoops_RH _hoops_AAPI */
		_hoops_HHRAA(_hoops_IRSRA, *_hoops_ISRAA,_hoops_HGAAA, _hoops_CSRAA, p->_hoops_SIIRA, p);
		_hoops_HHRAA(_hoops_IRSRA, *_hoops_SIPI, _hoops_IGAAA, _hoops_SSRAA, p->_hoops_SIIRA, p);
		(*_hoops_ISRAA)->_hoops_RSIRA = p->_hoops_RSIRA + 1;
		(*_hoops_SIPI)->_hoops_RSIRA = p->_hoops_RSIRA + 1;

#ifdef _hoops_RGIRA
		/* _hoops_IH _hoops_HSP _hoops_CGRSR. */
		(*_hoops_ISRAA)->_hoops_CCIRA = p->_hoops_CCIRA;
		(*_hoops_SIPI)->_hoops_CCIRA = p->_hoops_CCIRA;
#endif
	}

	return _hoops_HGII;
} 



/* _hoops_RPAAA _hoops_HCR _hoops_RH _hoops_RSSA _hoops_IIGR _hoops_IRS _hoops_HSSP _hoops_ACSRR _hoops_IRS _hoops_IPPA _hoops_IS _hoops_SSS _hoops_GGSR */
/* _hoops_RPP _hoops_RH _hoops_IPPA _hoops_HSRAA _hoops_RH _hoops_HSSP _hoops_PAR _hoops_HAR. */
local int _hoops_APAAA (
	_hoops_AIIRA	*p, 
	_hoops_AAIRA 	*part,
	double	_hoops_IASGA) {	    /* _hoops_AAHP _hoops_PIRA _hoops_IS _hoops_SGH */
    int 		i;
    int 		count = p->_hoops_ICIRA;
	int 		_hoops_SRAAA = 0;
	int 		_hoops_GAAAA = 0;
    double 	_hoops_IRAAA;
     
    for (i = 0 ; i < count ; i++) {
    	_hoops_IRAAA = _hoops_PIGAA(part, &p->_hoops_PIIRA[i]);

	 	if (_hoops_IRAAA > _hoops_IASGA)
		    _hoops_SRAAA++;
		else if (_hoops_IRAAA < -_hoops_IASGA)
		    _hoops_GAAAA++;
	
		if (_hoops_SRAAA && _hoops_GAAAA)
		    return _hoops_PHIRA;	/* _hoops_SIAS _hoops_GAR _hoops_PRAR _hoops_SRCH _hoops_HHH _hoops_PPSR _hoops_PPAAA */
										/* _hoops_GAR _hoops_HAAI _hoops_GAR _hoops_SR _hoops_CACH _hoops_RGR. */
    }
 
    if (_hoops_SRAAA && !_hoops_GAAAA)
		return _hoops_GHIRA;
    else if (_hoops_GAAAA && !_hoops_SRAAA)
		return _hoops_RHIRA;
    else if (!_hoops_SRAAA && !_hoops_GAAAA)
		return _hoops_AHIRA;
    else
		return _hoops_PHIRA;   
} 

local void _hoops_HPAAA (
	_hoops_IGCRA	*_hoops_IRSRA,
	_hoops_AIIRA	    *p)
{
    if (p->_hoops_ICIRA) {
		if (p->_hoops_GCIRA)
			_hoops_HPAAA(_hoops_IRSRA, p->_hoops_GCIRA);
		if (p->_hoops_RCIRA)
			_hoops_HPAAA(_hoops_IRSRA, p->_hoops_RCIRA);
		
	    _hoops_RASRA(p->_hoops_PIIRA,p->_hoops_ICIRA, _hoops_IRSRA);

		if (p->_hoops_HIIRA)
			_hoops_AASRA(p->_hoops_HIIRA,p->_hoops_ICIRA, _hoops_IRSRA);
	    if (p->_hoops_IIIRA)
	        _hoops_HASRA(p->_hoops_IIIRA,p->_hoops_ICIRA, _hoops_IRSRA);
		if (p->_hoops_HCIRA) {
			FREE_ARRAY(p->_hoops_HCIRA, p->_hoops_PSIRA, POINTER_SIZED_INT);
			p->_hoops_PSIRA = 0;
		}
    }
    _hoops_CRSRA(p, _hoops_IRSRA);
}

local void _hoops_IPAAA (_hoops_AIIRA * item, _hoops_AIIRA * key, void const * const user_data ) {
	UNREFERENCED(item);
	_hoops_HPAAA((_hoops_IGCRA *)user_data, key);
}

/* _hoops_AHGHR _hoops_IRS _hoops_RRCPR'_hoops_GRI _hoops_PPSR _hoops_PPR _hoops_HSP _hoops_HIGR, _hoops_RIPHR _hoops_GH _hoops_IRS _hoops_CPAAA _hoops_HIGR */ 
local void _hoops_SPAAA (
	_hoops_IGCRA	*		_hoops_IRSRA,	    	/* _hoops_GHAAA */
	_hoops_CPCRA *				t,		    /* _hoops_RH _hoops_HHIS */
	int		    			_hoops_RISRA,	    /* _hoops_SPCC _hoops_PPR _hoops_HSSP _hoops_HIGR */
	Point const *			_hoops_RHAAA,
	Vector const *			_hoops_AHAAA,	/* _hoops_ASGA */
	int		    			_hoops_RHGIR,	    /* _hoops_HSP _hoops_SPCC _hoops_PPR _hoops_HSP _hoops_HIGR */
	int const *				_hoops_ASPH,
	bool	   				invert,		/* _hoops_RGAR _hoops_PSIGA _hoops_RPP _hoops_SCGR _hoops_CAIH _hoops_HRGR _hoops_RIRAA. */
										/* _hoops_RAP _hoops_IHPR _hoops_RPP _hoops_SR _hoops_CHR _hoops_AIRAA _hoops_RH "_hoops_SGCRA", _hoops_RCPP */
										/* _hoops_RPP _hoops_AIRAA _hoops_RH _hoops_SAAP. _hoops_HGI _hoops_PIRAA _hoops_RGSR _hoops_RH */
										/* _hoops_AAPI _hoops_SSPC _hoops_RIP _hoops_IH _hoops_SCSRA _hoops_SGS _hoops_CHR _hoops_SIPP */
										/* _hoops_RH _hoops_IRPR _hoops_IASC _hoops_HIAHR.  _hoops_HGI _hoops_PPRRR _hoops_SR _hoops_PAH */
										/* _hoops_SRCH _hoops_HIRAA _hoops_SCSRA _hoops_RHIR _hoops_RH _hoops_IPHRA _hoops_CPHRA _hoops_SGS _hoops_GA'_hoops_RA */
										/* _hoops_RRP _hoops_SCH. */
	RGB const *				colors,		/* _hoops_PSHA.  _hoops_ICAH _hoops_PSHR _hoops_HCHC _hoops_GAR _hoops_PHAAA */
	unsigned short const *	vis,		/* _hoops_HPRC _hoops_RIP. _hoops_ICAH _hoops_PHAAA _hoops_IIGR _hoops_CAPR */
	bool 					_hoops_HHAAA,
	double					_hoops_CAIRA) 
{
    int 					i = 0;
    int 					_hoops_AIPHR = 0;

    UNREFERENCED(_hoops_RISRA);

    while (1) {
		/* _hoops_IIPP _hoops_PPR _hoops_HSPC _hoops_HSSP */
		_hoops_AIIRA *polygon;
		_hoops_HRSRA(&polygon, _hoops_IRSRA);
	 	_hoops_PHRAA(polygon, t->_hoops_SIIRA);
		if (colors) {	
		    polygon->_hoops_CSIRA = colors[_hoops_AIPHR];
		}
		if (vis) {
		    if (BIT(vis[_hoops_AIPHR], 0x0002))
				polygon->_hoops_SSIRA = true;
		    else
				polygon->_hoops_SSIRA = false;
		}
 
		/* _hoops_SIPR _hoops_AAPI _hoops_PPSR _hoops_HPHS _hoops_HII _hoops_RH _hoops_RRCPR _hoops_CPCI _hoops_PPR _hoops_GGCR _hoops_SCH _hoops_IS _hoops_RH _hoops_HSSP _hoops_HIGR */
	  	if (_hoops_CHRAA(_hoops_IRSRA, polygon, _hoops_RHAAA, _hoops_ASPH, _hoops_AHAAA, i, invert, _hoops_HHAAA, _hoops_CAIRA)) {
			t->_hoops_SPCRA->AddLast(polygon);
		    polygon->_hoops_CCIRA = _hoops_AIPHR;
			polygon->_hoops_RSIRA = 0;
			polygon->_hoops_HCIRA = null;
			polygon->_hoops_PSIRA = 0;
			polygon->_hoops_ACIRA = null;
		}
		else
			_hoops_HPAAA(_hoops_IRSRA, polygon);

		i += _hoops_ASPH[i] + 1;
		_hoops_AIPHR++;
		if (i >= _hoops_RHGIR)
		    break;
    }
}

/* _hoops_AHGHR _hoops_IRS _hoops_RRCPR'_hoops_GRI _hoops_PPSR _hoops_PPR _hoops_HSP _hoops_HIGR, _hoops_RIPHR _hoops_GH _hoops_IRS _hoops_CPAAA _hoops_HIGR */ 
/* _hoops_CCRAA _hoops_GPPS _hoops_CSPP */
local void _hoops_IHAAA (
	_hoops_IGCRA *		_hoops_IRSRA,	    		/* _hoops_GHAAA */
	_hoops_CPCRA *				t,		    	/* _hoops_RH _hoops_HHIS */
	int		    			_hoops_RISRA,	    	/* _hoops_SPCC _hoops_PPR _hoops_HSSP _hoops_HIGR */
	_hoops_APCIR const *			_hoops_RHAAA,
	Vector const *			_hoops_AHAAA,		/* _hoops_ASGA */
	int		    			_hoops_RHGIR,	    	/* _hoops_HSP _hoops_SPCC _hoops_PPR _hoops_HSP _hoops_HIGR */
	int const *				_hoops_ASPH,
	bool	   				invert,			/* _hoops_RGAR _hoops_PSIGA _hoops_RPP _hoops_SCGR _hoops_CAIH _hoops_HRGR _hoops_RIRAA. */
											/* _hoops_RAP _hoops_IHPR _hoops_RPP _hoops_SR _hoops_CHR _hoops_AIRAA _hoops_RH "_hoops_SGCRA", _hoops_RCPP */
											/* _hoops_RPP _hoops_AIRAA _hoops_RH _hoops_SAAP. _hoops_HGI _hoops_PIRAA _hoops_RGSR _hoops_RH */
											/* _hoops_AAPI _hoops_SSPC _hoops_RIP _hoops_IH _hoops_SCSRA _hoops_SGS _hoops_CHR _hoops_SIPP */
											/* _hoops_RH _hoops_IRPR _hoops_IASC _hoops_HIAHR.  _hoops_HGI _hoops_PPRRR _hoops_SR _hoops_PAH */
											/* _hoops_SRCH _hoops_HIRAA _hoops_SCSRA _hoops_RHIR _hoops_RH _hoops_IPHRA _hoops_CPHRA _hoops_SGS _hoops_GA'_hoops_RA */
											/* _hoops_RRP _hoops_SCH. */
	RGB const *				colors,			/* _hoops_PSHA.  _hoops_ICAH _hoops_PSHR _hoops_HCHC _hoops_GAR _hoops_PHAAA */
	unsigned short const *	vis,			/* _hoops_HPRC _hoops_RIP. _hoops_ICAH _hoops_PHAAA _hoops_IIGR _hoops_CAPR */
	bool					_hoops_HHAAA,
	double					_hoops_CAIRA) 
{
    int 					i = 0;
    int 					_hoops_AIPHR = 0;

    UNREFERENCED(_hoops_RISRA);

    while (1) {
		/* _hoops_IIPP _hoops_PPR _hoops_HSPC _hoops_HSSP */
		_hoops_AIIRA *polygon;
		_hoops_HRSRA(&polygon, _hoops_IRSRA);
	 	_hoops_PHRAA(polygon, t->_hoops_SIIRA);
		if (colors) {	
		    polygon->_hoops_CSIRA = colors[_hoops_AIPHR];
		}
		if (vis) {
		    if (BIT(vis[_hoops_AIPHR], 0x0002))
				polygon->_hoops_SSIRA = true;
		    else
				polygon->_hoops_SSIRA = false;
		}
 
		/* _hoops_SIPR _hoops_AAPI _hoops_PPSR _hoops_HPHS _hoops_HII _hoops_RH _hoops_RRCPR _hoops_CPCI _hoops_PPR _hoops_GGCR _hoops_SCH _hoops_IS _hoops_RH _hoops_HSSP _hoops_HIGR */
	  	if (_hoops_IPSRA(_hoops_IRSRA, polygon, _hoops_RHAAA, _hoops_ASPH, _hoops_AHAAA, i, invert, _hoops_HHAAA, _hoops_CAIRA)) {
			t->_hoops_SPCRA->AddLast(polygon);
			polygon->_hoops_CCIRA = _hoops_AIPHR;
			polygon->_hoops_RSIRA = 0;
			polygon->_hoops_HCIRA = null;
			polygon->_hoops_PSIRA = 0;
			polygon->_hoops_ACIRA = null;
		}
		else
			_hoops_HPAAA(_hoops_IRSRA, polygon);

		i += _hoops_ASPH[i] + 1;
		_hoops_AIPHR++;
		if (i >= _hoops_RHGIR)
		    break;
    }
}

/* _hoops_GHRAA _hoops_IRS _hoops_IPHRA _hoops_HHIS */
local void _hoops_CHAAA (
	_hoops_IGCRA *	_hoops_IRSRA,				/* _hoops_RSPHR _hoops_PIH */
	_hoops_CPCRA *			t,				/* _hoops_HHIS _hoops_IS _hoops_IHPI.  _hoops_PS _hoops_GRS _hoops_RIPHR _hoops_RH _hoops_HSSP _hoops_HIGR _hoops_IH _hoops_RGR */
	int		    		pcount,			/* _hoops_PPSR _hoops_RPR _hoops_PPR _hoops_PPSR _hoops_HIGR _hoops_PPR _hoops_ASGA */
	Point const *		points,
	Vector const *		normals,
	int		    		fcount,			/* _hoops_HSP _hoops_RPR _hoops_PPR _hoops_HSP _hoops_HIGR */
	int const *			faces,
 	bool	    		invert,			/* _hoops_RGAR _hoops_PSIGA _hoops_RPP _hoops_SCGR _hoops_CAIH _hoops_HRGR _hoops_RIRAA. */
										/* _hoops_RAP _hoops_IHPR _hoops_RPP _hoops_SR _hoops_CHR _hoops_AIRAA _hoops_RH "_hoops_SGCRA", _hoops_RCPP */
										/* _hoops_RPP _hoops_AIRAA _hoops_RH _hoops_SAAP. _hoops_HGI _hoops_PIRAA _hoops_RGSR _hoops_RH */
										/* _hoops_AAPI _hoops_SSPC _hoops_RIP _hoops_IH _hoops_SCSRA _hoops_SGS _hoops_CHR _hoops_SIPP */
										/* _hoops_RH _hoops_IRPR _hoops_IASC _hoops_HIAHR.  _hoops_HGI _hoops_PPRRR _hoops_SR _hoops_PAH */
										/* _hoops_SRCH _hoops_HIRAA _hoops_SCSRA _hoops_RHIR _hoops_RH _hoops_IPHRA _hoops_CPHRA _hoops_SGS _hoops_GA'_hoops_RA */
										/* _hoops_RRP _hoops_SCH. */
	RGB const *				fcolors,	/* _hoops_PSHA _hoops_PPR _hoops_SHAAA. _hoops_RAPAR _hoops_RRP _hoops_IS _hoops_SHH _hoops_GIAAA _hoops_GGR _hoops_SPCC */
	unsigned short const *	_hoops_RIAAA,
	bool					_hoops_HHAAA, 
	double					_hoops_CAIRA) 
{	
	t->_hoops_GHCRA = 0;
	POOL_ALLOC(t->_hoops_SIIRA, _hoops_HHIRA, _hoops_IRSRA->_hoops_RIGC->memory_pool);
	_hoops_RHRAA(t->_hoops_SIIRA, pcount, fcount);
	t->_hoops_SPCRA = POOL_NEW(_hoops_IRSRA->_hoops_RIGC->memory_pool, _hoops_PPCRA)(_hoops_IRSRA->_hoops_RIGC->memory_pool);
	_hoops_SPAAA(_hoops_IRSRA, t, pcount, points, normals, fcount, faces, invert, fcolors, _hoops_RIAAA, _hoops_HHAAA,_hoops_CAIRA);
}

/* _hoops_GHRAA _hoops_IRS _hoops_IPHRA _hoops_HHIS, _hoops_GHGPR _hoops_CSPP */
local void _hoops_AIAAA (
	_hoops_IGCRA *		_hoops_IRSRA,			/* _hoops_RSPHR _hoops_PIH */
	_hoops_CPCRA *				t,			/* _hoops_HHIS _hoops_IS _hoops_IHPI.  _hoops_PS _hoops_GRS _hoops_RIPHR _hoops_RH _hoops_HSSP _hoops_HIGR _hoops_IH _hoops_RGR */
	int		    			pcount,		/* _hoops_PPSR _hoops_RPR _hoops_PPR _hoops_PPSR _hoops_HIGR _hoops_PPR _hoops_ASGA */
	_hoops_APCIR const *			points,
	Vector const *			normals,
	int		    			fcount,		/* _hoops_HSP _hoops_RPR _hoops_PPR _hoops_HSP _hoops_HIGR */
	int const *				faces,
 	bool	    			invert,		/* _hoops_RGAR _hoops_PSIGA _hoops_RPP _hoops_SCGR _hoops_CAIH _hoops_HRGR _hoops_RIRAA. */
										/* _hoops_RAP _hoops_IHPR _hoops_RPP _hoops_SR _hoops_CHR _hoops_AIRAA _hoops_RH "_hoops_SGCRA", _hoops_RCPP */
										/* _hoops_RPP _hoops_AIRAA _hoops_RH _hoops_SAAP. _hoops_HGI _hoops_PIRAA _hoops_RGSR _hoops_RH */
										/* _hoops_AAPI _hoops_SSPC _hoops_RIP _hoops_IH _hoops_SCSRA _hoops_SGS _hoops_CHR _hoops_SIPP */
										/* _hoops_RH _hoops_IRPR _hoops_IASC _hoops_HIAHR.  _hoops_HGI _hoops_PPRRR _hoops_SR _hoops_PAH */
										/* _hoops_SRCH _hoops_HIRAA _hoops_SCSRA _hoops_RHIR _hoops_RH _hoops_IPHRA _hoops_CPHRA _hoops_SGS _hoops_GA'_hoops_RA _hoops_RRP _hoops_SCH. */
	RGB const *				fcolors,	/* _hoops_PSHA _hoops_PPR _hoops_SHAAA. _hoops_RAPAR _hoops_RRP _hoops_IS _hoops_SHH _hoops_GIAAA _hoops_GGR _hoops_SPCC */
	unsigned short const *	_hoops_RIAAA,
	bool					_hoops_HHAAA,
	double					_hoops_CAIRA) 
{
	t->_hoops_GHCRA = 0;
	POOL_ALLOC(t->_hoops_SIIRA, _hoops_HHIRA, _hoops_IRSRA->_hoops_RIGC->memory_pool);
	_hoops_RHRAA(t->_hoops_SIIRA, pcount, fcount);
	t->_hoops_SPCRA = POOL_NEW(_hoops_IRSRA->_hoops_RIGC->memory_pool, _hoops_PPCRA)(_hoops_IRSRA->_hoops_RIGC->memory_pool);
	_hoops_IHAAA(_hoops_IRSRA, t, pcount, points, normals, fcount, faces, invert, fcolors, _hoops_RIAAA, _hoops_HHAAA, _hoops_CAIRA);
}

/* _hoops_GISA _hoops_IRS _hoops_IPHRA _hoops_HHIS. _hoops_AHHRA _hoops_PIHA _hoops_HS _hoops_RPII _hoops_PIAAA'_hoops_ICAHR _hoops_AIAH _hoops_HIS _hoops_SGS _hoops_RH _hoops_HSSP _hoops_HIGR _hoops_HRGR _hoops_SSHS. */
local void _hoops_HIAAA (
	_hoops_IGCRA *	_hoops_IRSRA,
	_hoops_CPCRA *			t,
	double				_hoops_IASGA) 
{
    POOL_ALLOC(t->_hoops_GHCRA, _hoops_IPCRA, _hoops_IRSRA->_hoops_RIGC->memory_pool);
    _hoops_CASRA(_hoops_IRSRA, t->_hoops_GHCRA, t);	
    _hoops_SASRA(_hoops_IRSRA, t->_hoops_GHCRA, t->_hoops_SPCRA, _hoops_IASGA);
}

local void _hoops_IIAAA (
	_hoops_HPCRA *	_hoops_CIAAA,
	_hoops_IPCRA *			n) 
{
	_hoops_AIIRA *		_hoops_HARIR;
	_hoops_AIIRA *		temp;
		
    if (n->_hoops_GCIRA) {    
		_hoops_IIAAA(_hoops_CIAAA, n->_hoops_GCIRA);
		n->_hoops_GCIRA = null;
    }
    if (n->_hoops_RCIRA) {    
		_hoops_IIAAA(_hoops_CIAAA, n->_hoops_RCIRA);
		n->_hoops_RCIRA = null;
    }

	n->_hoops_SPCRA->ResetCursor();
	while ((temp = n->_hoops_SPCRA->PeekCursor()) != null) {

		if (_hoops_CIAAA->LookupItem(temp, &_hoops_HARIR) == _hoops_HPCRA::Failed)
			_hoops_CIAAA->InsertItem(temp, null);

		n->_hoops_SPCRA->AdvanceCursor();
	}
    
	delete n->_hoops_SPCRA; 
    n->_hoops_SPCRA = null;
 
    FREE(n, _hoops_IPCRA);
}
  

local void _hoops_SIAAA (
	_hoops_IGCRA *	_hoops_IRSRA,	      
	_hoops_CPCRA *			t) 
{
	_hoops_HPCRA *	_hoops_CIAAA = POOL_NEW(_hoops_IRSRA->_hoops_RIGC->memory_pool, _hoops_HPCRA)(_hoops_IRSRA->_hoops_RIGC->memory_pool, t->_hoops_SPCRA->Count()*2);
	_hoops_AIIRA *		_hoops_HARIR;
	_hoops_AIIRA *		temp;
		
	t->_hoops_SPCRA->ResetCursor();
	while ((temp = t->_hoops_SPCRA->PeekCursor()) != null) {

		if (_hoops_CIAAA->LookupItem(temp, &_hoops_HARIR) == _hoops_HPCRA::Failed)
			_hoops_CIAAA->InsertItem(temp, null);

		t->_hoops_SPCRA->AdvanceCursor();
	}

    FREE(t->_hoops_SIIRA, _hoops_HHIRA);
    
    delete t->_hoops_SPCRA; 
 
    if (t->_hoops_GHCRA)
		_hoops_IIAAA(_hoops_CIAAA, t->_hoops_GHCRA);

	_hoops_CIAAA->MapFunction(_hoops_IPAAA, (void *)_hoops_IRSRA);
	delete _hoops_CIAAA;
	
    FREE(t, _hoops_CPCRA);
}

local void _hoops_CASRA (
	_hoops_IGCRA *		_hoops_IRSRA,
	_hoops_IPCRA *				n,
	_hoops_CPCRA *				tree) 
{	
    n->_hoops_HHCRA = tree;
    n->_hoops_GCIRA = null;
    n->_hoops_RCIRA = null;
    n->_hoops_SPCRA = POOL_NEW(_hoops_IRSRA->_hoops_RIGC->memory_pool, _hoops_PPCRA)(_hoops_IRSRA->_hoops_RIGC->memory_pool);    
}


/* _hoops_GCAAA _hoops_RCAAA _hoops_RPP _hoops_RGR _hoops_HSSP _hoops_SSCP _hoops_ASIRA _hoops_SGS _hoops_CHR _hoops_ACAAA _hoops_IS _hoops_RH */
/* _hoops_IIPR _hoops_HSHRR.  _hoops_CGP _hoops_GIPR _hoops_RASI _hoops_IIGR _hoops_IRS _hoops_PCIRA _hoops_CHR _hoops_PCAAA _hoops_SIGC, */
/* _hoops_PSCR _hoops_IIH _hoops_HRGR _hoops_PSP _hoops_ICPRA _hoops_HHGP _hoops_PPR _hoops_RH _hoops_PCIRA _hoops_ACAS _hoops_HRGR _hoops_CHIS */
/* _hoops_IS _hoops_HCAAA _hoops_RH _hoops_ICAAA. */
local bool _hoops_CCAAA (
	_hoops_AIIRA *	p)
{   
	bool _hoops_SCAAA = false, _hoops_GSAAA = false;

	if (!p->_hoops_GCIRA && !p->_hoops_RCIRA)
		return false;	/* _hoops_PSP _hoops_RASI, _hoops_PSP _hoops_ASIRA */

	if (!p->_hoops_GCIRA || !p->_hoops_GCIRA->_hoops_ISIRA)
		_hoops_SCAAA = true;	/* _hoops_CR _hoops_SR _hoops_HS _hoops_SPR _hoops_RPSI _hoops_PPR _hoops_HAR _hoops_RH _hoops_RII, _hoops_PSCR _hoops_SR _hoops_HS _hoops_IRS _hoops_HHGP */
	else
		_hoops_SCAAA = _hoops_CCAAA(p->_hoops_GCIRA);    /* _hoops_ISPR _hoops_IS _hoops_CACH _hoops_RPP _hoops_RH _hoops_RPSI _hoops_ASIRA */

	if (!p->_hoops_RCIRA || !p->_hoops_RCIRA->_hoops_ISIRA)
		_hoops_GSAAA = true;	/* _hoops_CR _hoops_SR _hoops_HS _hoops_SPR _hoops_RPSI _hoops_PPR _hoops_HAR _hoops_RH _hoops_RII, _hoops_PSCR _hoops_SR _hoops_HS _hoops_IRS _hoops_HHGP */
	else
		_hoops_GSAAA = _hoops_CCAAA(p->_hoops_RCIRA);    /* _hoops_ISPR _hoops_IS _hoops_CACH _hoops_RPP _hoops_RH _hoops_RPSI _hoops_ASIRA */


	if (!_hoops_SCAAA && !_hoops_GSAAA)
		return false;	/* _hoops_PSP _hoops_ICPRA _hoops_ASIRA _hoops_GPP _hoops_PGI _hoops_PPAP */
	else
		return true;	/* _hoops_RSAAA, _hoops_ASIRA. */
}


local void _hoops_ASAAA (
	_hoops_IGCRA *	_hoops_IRSRA,
	_hoops_AIIRA *		p,
	_hoops_PPCRA *	_hoops_APSRA)
{
	/* _hoops_RAHP _hoops_IPHRA _hoops_HIGAA'_hoops_GRI _hoops_HS _hoops_RPII _hoops_IHGS _hoops_CPHR, _hoops_SR _hoops_HS _hoops_RPII _hoops_ISCPR _hoops_AAPI _hoops_GGR _hoops_RH _hoops_HIGR */
	/* _hoops_GAR _hoops_SIGC _hoops_PAR _hoops_HAR.  _hoops_GPGP _hoops_PIHRA, _hoops_GAR _hoops_AAPI _hoops_HS _hoops_RPII _hoops_HHGP _hoops_SR _hoops_HS _hoops_GCSS _hoops_CICRR */
	/* _hoops_IS _hoops_PAII _hoops_HHGP _hoops_PSAP _hoops_RASI. _hoops_HIGAR _hoops_SR _hoops_CHR _hoops_CPIC _hoops_IS _hoops_AA _hoops_HA _hoops_HRGR _hoops_ARAS _hoops_RH _hoops_HIGR _hoops_IIGR _hoops_AAPI. */
	/* _hoops_GAR _hoops_SR _hoops_ISPR _hoops_SIGC _hoops_AAPI, _hoops_SR _hoops_GACC _hoops_IHSH _hoops_HPGR _hoops_RH _hoops_HHGP _hoops_RASI.  _hoops_CGP _hoops_HCR _hoops_RH _hoops_HHGP */
	/* _hoops_RASI _hoops_IIGR _hoops_IRS _hoops_PCIRA _hoops_CHR _hoops_GACC _hoops_SIGC, _hoops_PSCR _hoops_SR _hoops_SAHR _hoops_GRHP _hoops_RH _hoops_PCIRA _hoops_HSSP _hoops_RIIA */
	/* _hoops_IIGR _hoops_RH _hoops_HHGP _hoops_RASI.  _hoops_HGI _hoops_PSAAA _hoops_IS _hoops_SRCH _hoops_HSAAA _hoops_RH _hoops_HACH _hoops_HSHRR _hoops_CCA _hoops_AHIHR _hoops_ASIRA */
	/* _hoops_HHPPR _hoops_HPP _hoops_RH _hoops_ISAAA _hoops_IIGR _hoops_RSH _hoops_IPHRA _hoops_CPHRA _hoops_IPHR. */

	if (!_hoops_CCAAA(p) && p->_hoops_ISIRA) {
		/* _hoops_CSH _hoops_ICPRA _hoops_ASIRA _hoops_GPP _hoops_RGR _hoops_PAR _hoops_SCH'_hoops_GRI _hoops_RASI, _hoops_HIS _hoops_GGCR _hoops_RH _hoops_PCIRA */
		/* _hoops_IS _hoops_RH _hoops_HIGR. */
		_hoops_APSRA->AddLast(p);
		return;
	}
	else {
		/* _hoops_CSAAA.  _hoops_ARGH _hoops_RH _hoops_RPSI _hoops_AIIS _hoops_PPR _hoops_GA'_hoops_RA _hoops_SGH _hoops_RH _hoops_PCIRA. */
		if (p->_hoops_GCIRA && p->_hoops_GCIRA->_hoops_ISIRA)
			_hoops_ASAAA(_hoops_IRSRA, p->_hoops_GCIRA, _hoops_APSRA);

		if (p->_hoops_RCIRA && p->_hoops_RCIRA->_hoops_ISIRA)
			_hoops_ASAAA(_hoops_IRSRA, p->_hoops_RCIRA, _hoops_APSRA);
	}
}

/* _hoops_HGI _hoops_GSHRA _hoops_PCCP _hoops_SSAAA _hoops_HSSP _hoops_HIGR _hoops_HPP _hoops_HCHAR _hoops_HPGR _hoops_RH _hoops_SCGR _hoops_HSSP _hoops_HIGR. */
local void _hoops_GGPAA (
	_hoops_IGCRA	*	_hoops_IRSRA,
	_hoops_CPCRA *			t,
	_hoops_PPCRA *	_hoops_RGPAA,
	_hoops_PPCRA *	_hoops_APSRA)  
{
    /* _hoops_RAHP _hoops_IPHRA _hoops_HIGAA'_hoops_GRI _hoops_HS _hoops_RPII _hoops_IHGS _hoops_CPHR, _hoops_SR _hoops_HS _hoops_RPII _hoops_ISCPR _hoops_AAPI _hoops_GGR _hoops_RH _hoops_HIGR */
    /* _hoops_GAR _hoops_SIGC _hoops_PAR _hoops_HAR.  _hoops_GPGP _hoops_PIHRA, _hoops_GAR _hoops_AAPI _hoops_HS _hoops_RPII _hoops_HHGP _hoops_SR _hoops_HS _hoops_GCSS _hoops_CICRR */
    /* _hoops_IS _hoops_PAII _hoops_HHGP _hoops_PSAP _hoops_RASI. _hoops_HIGAR _hoops_SR _hoops_CHR _hoops_CPIC _hoops_IS _hoops_AA _hoops_HA _hoops_HRGR _hoops_ARAS _hoops_RH _hoops_HIGR _hoops_IIGR _hoops_AAPI. */
    /* _hoops_GAR _hoops_SR _hoops_ISPR _hoops_SIGC _hoops_AAPI, _hoops_SR _hoops_GACC _hoops_IHSH _hoops_HPGR _hoops_RH _hoops_HHGP _hoops_RASI.  _hoops_CGP _hoops_HCR _hoops_RH _hoops_HHGP */
    /* _hoops_RASI _hoops_IIGR _hoops_IRS _hoops_PCIRA _hoops_CHR _hoops_GACC _hoops_SIGC, _hoops_PSCR _hoops_SR _hoops_SAHR _hoops_GRHP _hoops_RH _hoops_PCIRA _hoops_HSSP _hoops_RIIA */
    /* _hoops_IIGR _hoops_RH _hoops_HHGP _hoops_RASI.  _hoops_HGI _hoops_PSAAA _hoops_IS _hoops_SRCH _hoops_HSAAA _hoops_RH _hoops_HACH _hoops_HSHRR _hoops_CCA _hoops_AHIHR _hoops_ASIRA */
    /* _hoops_HHPPR _hoops_HPP _hoops_RH _hoops_ISAAA _hoops_IIGR _hoops_RSH _hoops_IPHRA _hoops_CPHRA _hoops_IPHR. */
    UNREFERENCED(t);

	_hoops_AIIRA * temp;

	_hoops_RGPAA->ResetCursor();

	while ((temp = _hoops_RGPAA->PeekCursor()) != null) {
		if (temp->_hoops_ISIRA) {
			if (temp->_hoops_GGCRA) {
				/* _hoops_SSPC _hoops_HRGR _hoops_ARP _hoops_CGPR _hoops_RH _hoops_HSSP _hoops_CPCI _hoops_CHR _hoops_AGPAA.  _hoops_ASC _hoops_AAPI _hoops_IHCS */
				/* _hoops_SIPP _hoops_RH _hoops_IASC _hoops_HIAHR _hoops_IIGR _hoops_RH _hoops_SGCRA _hoops_PPR _hoops_SAAP, _hoops_HIS _hoops_SSIA _hoops_AAPR "_hoops_IAIH" */
				/* _hoops_RHSP _hoops_RH _hoops_AIHGR _hoops_PGPP.  _hoops_SAGAR, _hoops_SSIA _hoops_HGGC _hoops_RRP _hoops_IS _hoops_SHH _hoops_PGPAA _hoops_GGR */
				/* _hoops_RH _hoops_RSGR _hoops_GHPP. */
				_hoops_APSRA->AddLast(temp);
			}
			else {
				/* _hoops_ISPR _hoops_RGR _hoops_HSSP _hoops_PPR _hoops_SCH'_hoops_GRI _hoops_RASI _hoops_IH _hoops_HGPAA _hoops_GGR _hoops_RH _hoops_IGPAA. */
				_hoops_ASAAA(_hoops_IRSRA, temp, _hoops_APSRA);
			}
		}
		_hoops_RGPAA->AdvanceCursor();
	}
}


/* _hoops_IPHRA _hoops_HIGAA _hoops_CGPAA _hoops_RH _hoops_AAPI _hoops_IIGR _hoops_SPR _hoops_IPHRA _hoops_ISHP _hoops_HPIH _hoops_IPHRA _hoops_HHIS _hoops_IS _hoops_CACH _hoops_RPP */
/* _hoops_SPR _hoops_CARA _hoops_HRGR _hoops_ASSA _hoops_RH _hoops_RII _hoops_SPR. */
local void _hoops_SGPAA(
	_hoops_IGCRA *	_hoops_IRSRA,			/* _hoops_PGGC _hoops_IIGR _hoops_PIH _hoops_APSAR _hoops_SGS _hoops_SR _hoops_RRP _hoops_IS _hoops_SGH */
	_hoops_CPCRA *			t,			/* _hoops_AHHRA _hoops_SGS _hoops_SR _hoops_GRS _hoops_AISI _hoops_AAPI _hoops_ISHP _hoops_IS _hoops_CACH _hoops_RPP _hoops_SSIA _hoops_CHR _hoops_ASSA _hoops_RH _hoops_CARA _hoops_PAR _hoops_HAR. */
	_hoops_CPCRA *			tree,		/* _hoops_AHHRA _hoops_GRPAA _hoops_AAPI _hoops_SR _hoops_CHR _hoops_RRPAA _hoops_ISHP _hoops_RH _hoops_RII _hoops_HHIS */
	_hoops_PPCRA *	_hoops_APSRA,	/* _hoops_RH _hoops_IGPAA _hoops_CAS _hoops_RH _hoops_ACPP _hoops_RSGR _hoops_GH */
	bool				_hoops_ARPAA,	/* _hoops_PAGAR _hoops_SR _hoops_GRHP _hoops_RGAR _hoops_AAPI _hoops_SGS _hoops_CHR _hoops_SIPP. _hoops_PRPAA _hoops_RCAAA _hoops_AGSR _hoops_SR */
										/* _hoops_GRHP _hoops_AAPI _hoops_SGS _hoops_CHR _hoops_ASSA. _hoops_HRPAA _hoops_SGH _hoops_AGICR _hoops_CGPR _hoops_GHGA _hoops_RSHRA, */
										/* _hoops_CR _hoops_RHAC _hoops_HHGC _hoops_IS _hoops_GRHP _hoops_RH _hoops_SCSRA _hoops_IIGR _hoops_RH _hoops_SGCRA _hoops_SGS _hoops_CHR _hoops_ASSA _hoops_RH _hoops_SAAP. */
	bool				_hoops_PPSRA,/* _hoops_IHPR _hoops_RPP _hoops_IRPAA _hoops_HRGR _hoops_GHSAR _hoops_ASSA _hoops_RH _hoops_ICRAA, _hoops_RCPP _hoops_RPP _hoops_GGSR. */
	double				_hoops_IASGA) {		/* _hoops_AAHP _hoops_IS _hoops_SGH _hoops_HPGP _hoops_HPPA */
    _hoops_PPCRA *	_hoops_RGPAA = tree->_hoops_SPCRA;
    _hoops_PPCRA *	_hoops_CRPAA = 0;
    _hoops_PPCRA *	_hoops_SRPAA = 0;
	_hoops_AIIRA *		temp;

    if (_hoops_IRSRA->_hoops_PRCRA) {
    	_hoops_CRPAA = POOL_NEW(_hoops_IRSRA->_hoops_RIGC->memory_pool, _hoops_PPCRA)(_hoops_IRSRA->_hoops_RIGC->memory_pool);
		_hoops_SRPAA = _hoops_CRPAA;
    }
    else
		_hoops_SRPAA = _hoops_APSRA;

    /* _hoops_ARAS _hoops_RHIR _hoops_RH _hoops_AAPI _hoops_PPR _hoops_GAPAA _hoops_CAPR _hoops_ACSRR _hoops_RH _hoops_HSSAR _hoops_HHIS */
	_hoops_RGPAA->ResetCursor();

	while((temp =  _hoops_RGPAA->PeekCursor()) != null) {

#ifdef _hoops_RGIRA
		 _hoops_HRGAA(temp->_hoops_CCIRA);
#endif

		if (!temp->_hoops_GGCRA) {     
    		if (!_hoops_ARPAA)
				_hoops_RPSRA(_hoops_IRSRA, t->_hoops_GHCRA, temp, _hoops_SRPAA, _hoops_PPSRA, _hoops_IASGA);
     		else
	 			_hoops_HPSRA(_hoops_IRSRA, t->_hoops_GHCRA, temp , _hoops_SRPAA, _hoops_PPSRA, _hoops_IASGA);     
		}

#ifdef _hoops_RGIRA
		_hoops_HRGAA(-1);
#endif

		_hoops_RGPAA->AdvanceCursor();
	}

    if (_hoops_IRSRA->_hoops_PRCRA) {
		_hoops_GGPAA(_hoops_IRSRA, t, _hoops_RGPAA, _hoops_APSRA);
        delete _hoops_CRPAA; 
    }
}




/* _hoops_AHGHR _hoops_IRS _hoops_HSP _hoops_HIGR, _hoops_SSS _hoops_GGSR _hoops_RSH _hoops_AHPH _hoops_RSSI _hoops_CHR _hoops_IGRC _hoops_GGR _hoops_SCH. */
local int _hoops_RAPAA (
	int	*_hoops_ASPH, 
	int _hoops_RHGIR)
{
    int _hoops_AAPAA = 0;
    int i = 0;
    if (!_hoops_RHGIR)
		return 0;

    while (1) {
		i += _hoops_ASPH[i] + 1;
		_hoops_AAPAA++;
		if (i >= _hoops_RHGIR)
		    break;
    }
    return _hoops_AAPAA;
}

/* _hoops_AHGHR _hoops_IRS _hoops_AGAPR _hoops_HIGR _hoops_IIGR _hoops_AAPI, _hoops_ARPR _hoops_PPSR _hoops_PPR _hoops_HSP _hoops_CPCI _hoops_IRPR _hoops_IH _hoops_IRS _hoops_AGAH _hoops_RRCPR.*/
local bool _hoops_PAPAA (
	_hoops_IGCRA *		_hoops_IRSRA,				/* _hoops_GHAAA */
	_hoops_PPCRA *		_hoops_RGPAA,		/* _hoops_CIIA _hoops_HSSP _hoops_HIGR */
	int *					_hoops_HAPAA,			/* _hoops_IIPR _hoops_PPSR _hoops_PPR _hoops_HSP _hoops_CIPH */
	Point **				_hoops_SPRGA,
	Vector **				_hoops_IAPAA,
	int *					_hoops_CAPAA,
	int **					_hoops_SAPAA,
	int *					_hoops_GPPAA,		
	int *					_hoops_RPPAA,
	bool					invert,				/* _hoops_RPP _hoops_ISSP _hoops_HRGR _hoops_IHPR _hoops_PSCR _hoops_SR _hoops_HS */
												/* _hoops_IRS _hoops_HIGR _hoops_IIGR _hoops_AAPI _hoops_SGS _hoops_AAPR _hoops_GCPRA _hoops_HII _hoops_RH */
												/* _hoops_SGCRA _hoops_GGR _hoops_IRS _hoops_ICHRA _hoops_CAIH.  _hoops_GPGP _hoops_RGR _hoops_AGIR */
												/* _hoops_SR _hoops_RRP _hoops_IS _hoops_PIIA _hoops_RH _hoops_PPSR _hoops_AGR _hoops_HIS _hoops_SGS */
												/* _hoops_RSSP _hoops_HRGR _hoops_GGSP _hoops_GGR _hoops_RH _hoops_HACH _hoops_RRCPR. */
	bool					_hoops_APPAA,
	bool 					_hoops_PPPAA,
	RGB **					_hoops_AGRGA,
	int *					_hoops_HPPAA,
	bool **					_hoops_IPPAA,	
	bool 					_hoops_CPPAA) 
{  
    int 				_hoops_AAPAA = 0;
    int 				i = 0;
    _hoops_AIIRA *		first;
	int 				_hoops_RISRA = 0;
	int					_hoops_RHGIR = 0;
    Point *				points;
    Vector *			normals = 0;
    RGB *				_hoops_SPPAA = 0;
    bool *				_hoops_RGP = 0;
    int 				_hoops_GHPAA;
    int *				faces; 
    bool 				_hoops_RCAI;
    int 				_hoops_RHPAA;
    long 				_hoops_AHPAA = 0;
    int *				_hoops_PICRA;
	int *				_hoops_RICRA = null;


    /* _hoops_ARP _hoops_RH _hoops_ASRC _hoops_HSH _hoops_GGR _hoops_AGIR _hoops_SR _hoops_HS _hoops_PCCP _hoops_RHPA _hoops_HSHRR. */
    *_hoops_HAPAA = 0;
    *_hoops_SPRGA = 0;
    *_hoops_IAPAA = 0;
    *_hoops_CAPAA = 0;
    *_hoops_GPPAA = 0;
    *_hoops_RPPAA = 0;
	if (_hoops_AGRGA)	
		*_hoops_AGRGA = 0;
	if (_hoops_HPPAA)
		*_hoops_HPPAA = 0;
	if (_hoops_IPPAA)
		*_hoops_IPPAA = 0;

	_hoops_APCIR	_hoops_PHPAA = _hoops_IRSRA->_hoops_CGCRA.min;
	_hoops_APCIR	_hoops_HHPAA = _hoops_IRSRA->_hoops_CGCRA.max;
	_hoops_APCIR	_hoops_IHPAA = _hoops_IRSRA->_hoops_GRCRA.min;
	_hoops_APCIR	_hoops_CHPAA = _hoops_IRSRA->_hoops_GRCRA.max;


    first = _hoops_RGPAA->PeekFirst();
    if (!first)
		return true;	    /* _hoops_PCCP _hoops_RHPA _hoops_CIIA _hoops_HSHRR _hoops_HRGR _hoops_RCRAR, _hoops_SR'_hoops_GCPP _hoops_SAHR _hoops_ASRC _hoops_RHPA _hoops_HSH. */

    _hoops_RISRA = first->_hoops_SIIRA->_hoops_SHIRA;

    _hoops_AHPAA = 0;

	_hoops_AIIRA * temp;
	_hoops_RGPAA->ResetCursor();
	while ((temp = _hoops_RGPAA->PeekCursor()) != null) {

		_hoops_RHGIR += (temp->_hoops_ICIRA + 1);
		_hoops_AHPAA++;

		_hoops_RGPAA->AdvanceCursor();
	}

    *_hoops_GPPAA = _hoops_RISRA;
    *_hoops_RPPAA = _hoops_RHGIR;
    ZALLOC_ARRAY(points, _hoops_RISRA, Point);
    if (_hoops_APPAA) {     
		ZALLOC_ARRAY(normals, _hoops_RISRA, Vector);
    }

    ALLOC_ARRAY(faces, _hoops_RHGIR, int);

  
	if (_hoops_PPPAA)
		ALLOC_ARRAY(_hoops_SPPAA, _hoops_AHPAA, RGB);

    if (_hoops_CPPAA)
		ALLOC_ARRAY(_hoops_RGP, _hoops_AHPAA, bool);

    _hoops_GHPAA = 0; 

	_hoops_RGPAA->ResetCursor();
	while ((temp = _hoops_RGPAA->PeekCursor()) != null) {

	    _hoops_RHPAA = _hoops_AAPAA;
	    _hoops_RCAI = false;
    
	    if (_hoops_PPPAA || _hoops_CPPAA) {    
			if (_hoops_PPPAA) {
			    _hoops_SPPAA[_hoops_GHPAA] =  temp->_hoops_CSIRA;
			}
			if (_hoops_CPPAA)
			    _hoops_RGP[_hoops_GHPAA] = temp->_hoops_SSIRA;   
	    }

	    faces[_hoops_AAPAA++] = temp->_hoops_ICIRA;
	    for (i = 0 ; i < temp->_hoops_ICIRA ; i++) {
			int index;
			if (!invert)	
			    faces[_hoops_AAPAA++] = temp->_hoops_IIIRA[i];
			else 
			    faces[_hoops_AAPAA++] = temp->_hoops_IIIRA[temp->_hoops_ICIRA - 1 - i];
			index = temp->_hoops_IIIRA[i];
			points[index].x = (float)temp->_hoops_PIIRA[i].x;
			points[index].y = (float)temp->_hoops_PIIRA[i].y;
			points[index].z = (float)temp->_hoops_PIIRA[i].z;
			if (invert && _hoops_IRSRA->_hoops_PRCRA && (points[index].x < _hoops_IHPAA.x || points[index].y < _hoops_IHPAA.y || points[index].z < _hoops_IHPAA.z ||
			     points[index].x > _hoops_CHPAA.x || points[index].y > _hoops_CHPAA.y || points[index].z > _hoops_CHPAA.z))
			    _hoops_RCAI = true;    /* _hoops_RGR _hoops_HSSP _hoops_CGH _hoops_IGRC _hoops_SHH _hoops_IAIH _hoops_PGGA _hoops_SCH'_hoops_GRI _hoops_SIPP _hoops_RH _hoops_IASC */
					    		/* _hoops_RGCRA _hoops_SGS _hoops_HS _hoops_RPII _hoops_IGI _hoops_IH _hoops_CHCRA. */
			if (_hoops_APPAA) {	
			    normals[temp->_hoops_IIIRA[i]].x = (float)temp->_hoops_HIIRA[i].x;
			    normals[temp->_hoops_IIIRA[i]].y = (float)temp->_hoops_HIIRA[i].y;
			    normals[temp->_hoops_IIIRA[i]].z = (float)temp->_hoops_HIIRA[i].z;
			}
	    }
	    if (_hoops_RCAI)     
			_hoops_AAPAA = _hoops_RHPAA;     
	    else {
			temp->_hoops_GSIRA = _hoops_GHPAA;
			_hoops_GHPAA++;
	    }

		_hoops_RGPAA->AdvanceCursor();
	}

    ALLOC_ARRAY(*_hoops_SPRGA, _hoops_RISRA, Point);
    if (_hoops_APPAA)
		ALLOC_ARRAY(*_hoops_IAPAA, _hoops_RISRA, Vector);
    ALLOC_ARRAY(*_hoops_SAPAA, _hoops_RHGIR, int);
    ALLOC_ARRAY(_hoops_PICRA, _hoops_RISRA, int);
	
    if (_hoops_AAPAA)	{   /* _hoops_SCH'_hoops_GRI _hoops_SSRR _hoops_SR "_hoops_HPSH" _hoops_HCR _hoops_RSSI _hoops_ARRS, _hoops_RPP _hoops_GGR _hoops_RGSC _hoops_IIH _hoops_CSAP _hoops_PSP */
    		    	/* _hoops_SHPAA _hoops_GAPA _hoops_RH _hoops_SGCRA _hoops_PPR _hoops_SAAP */

		if (_hoops_GHPAA)
			ALLOC_ARRAY(_hoops_RICRA, _hoops_GHPAA, int);

		HI_Compute_Optimized_Shell(_hoops_IRSRA->_hoops_RIGC, _hoops_RISRA, points, normals, _hoops_AAPAA, faces, "tolerance = 0.000001 oru, normal tolerance = 30 deg",
								   _hoops_HAPAA, *_hoops_SPRGA, _hoops_CAPAA, *_hoops_SAPAA, _hoops_PICRA, _hoops_RICRA); 

		if (_hoops_PPPAA || _hoops_CPPAA) {
		    int _hoops_GIPAA;  
	    
		    _hoops_GIPAA = _hoops_RAPAA(*_hoops_SAPAA, *_hoops_CAPAA);
		    if (_hoops_GIPAA) {	
		    	if (_hoops_PPPAA)
					ALLOC_ARRAY(*_hoops_AGRGA, _hoops_GIPAA, RGB);
		    	if (_hoops_CPPAA)
					ALLOC_ARRAY(*_hoops_IPPAA, _hoops_GIPAA, bool);
	    
		    	for (i = 0 ; i < _hoops_GHPAA ; i++) {
					if (_hoops_RICRA[i] != -1) {	    
					    if (_hoops_PPPAA) {
							(*_hoops_AGRGA)[_hoops_RICRA[i]] = _hoops_SPPAA[i];
					    }
					    if (_hoops_CPPAA)
				    	    (*_hoops_IPPAA)[_hoops_RICRA[i]] = _hoops_RGP[i];
					}
		    	}
		    }
	    
		    *_hoops_HPPAA = _hoops_GIPAA;
		}

		if (_hoops_APPAA) {

			_hoops_ICCRA *				_hoops_RSCRA = POOL_NEW(_hoops_IRSRA->_hoops_RIGC->memory_pool, _hoops_ICCRA)(_hoops_IRSRA->_hoops_RIGC->memory_pool, *_hoops_HAPAA);
			_hoops_HICRA *	_hoops_RIPAA = POOL_NEW(_hoops_IRSRA->_hoops_RIGC->memory_pool, _hoops_HICRA)(_hoops_IRSRA->_hoops_RIGC->memory_pool, *_hoops_HAPAA);
			_hoops_IICRA *	_hoops_CICRA = POOL_NEW(_hoops_IRSRA->_hoops_RIGC->memory_pool, _hoops_IICRA)(_hoops_IRSRA->_hoops_RIGC->memory_pool);

			/* _hoops_PS'_hoops_GCPP _hoops_SSS _hoops_PGAP _hoops_HHGP _hoops_RSSI _hoops_AIPAA, _hoops_PGAP _hoops_GIHA _hoops_SR _hoops_RRP _hoops_ASGA _hoops_IH,
				_hoops_PGAP _hoops_RSSI _hoops_PAH _hoops_HSSRR _hoops_IRS _hoops_GPHA _hoops_GSSR, _hoops_PPR _hoops_PGAP _hoops_GRS _hoops_HGAP _hoops_IRS _hoops_CCAH _hoops_GPHA _hoops_GSSR
				(_hoops_HAS._hoops_IAS., _hoops_SR _hoops_GGCR _hoops_GIHA _hoops_RPP _hoops_SR'_hoops_RISP _hoops_GGHP _hoops_ACIPR _hoops_SPPR) */

			_hoops_RGPAA->ResetCursor();
			while ((temp = _hoops_RGPAA->PeekCursor()) != null) {

				if (temp->_hoops_GCIRA || temp->_hoops_RCIRA) {
					_hoops_PPCRA *_hoops_PIPAA = POOL_NEW(_hoops_IRSRA->_hoops_RIGC->memory_pool, _hoops_PPCRA)(_hoops_IRSRA->_hoops_RIGC->memory_pool);
					_hoops_AIIRA *_hoops_GICRA;
					
					_hoops_SHCRA(temp, _hoops_RICRA, _hoops_PIPAA);

					_hoops_PIPAA->ResetCursor();
					for (_hoops_GICRA = _hoops_PIPAA->PeekFirst() ; _hoops_GICRA != null ; _hoops_GICRA = _hoops_PIPAA->PeekCursor()) {
						/* _hoops_IRHH _hoops_RCRR _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_PCCP _hoops_GIGR _hoops_HSP _hoops_PIIHR _hoops_IS _hoops_HCHAR _hoops_IH _hoops_CCAH _hoops_GIHA */
						if (_hoops_GICRA->_hoops_RSIRA != 0) {
							_hoops_HICRA *_hoops_HIPAA = 
								POOL_NEW(_hoops_IRSRA->_hoops_RIGC->memory_pool, _hoops_HICRA)(_hoops_IRSRA->_hoops_RIGC->memory_pool, _hoops_GICRA->_hoops_ICIRA);

							_hoops_AICRA(temp, _hoops_GICRA, _hoops_PICRA, _hoops_HIPAA, _hoops_CICRA);

							_hoops_HICRA::PairList * _hoops_IIPAA = _hoops_HIPAA->GetPairList();

							_hoops_CCCRA(_hoops_GICRA, _hoops_IIPAA, _hoops_SPRGA, _hoops_HAPAA, _hoops_SAPAA, _hoops_RSCRA, _hoops_RIPAA);

							delete _hoops_IIPAA;
							delete _hoops_HIPAA;
						}

						_hoops_PIPAA->AdvanceCursor();
					}

					delete _hoops_PIPAA;
				}
				
				_hoops_RGPAA->AdvanceCursor();
			}

			/* _hoops_SR _hoops_CIPAA _hoops_SIPAA _hoops_HIS _hoops_SGS _hoops_SR _hoops_GA'_hoops_RA _hoops_IPS "_hoops_AHCI" _hoops_GPHA _hoops_ASGA
				_hoops_IAPR _hoops_ISCP _hoops_GGSRA _hoops_GPHA _hoops_ASGA */
			_hoops_CICRA->ResetCursor();
			for (POINTER_SIZED_INT	_hoops_GCPAA = _hoops_CICRA->PeekFirst() ; _hoops_GCPAA != 0 ; _hoops_GCPAA = _hoops_CICRA->PeekCursor()) {
				/* _hoops_SR _hoops_AGPI _hoops_RCPAA _hoops_PGGA _hoops_SR _hoops_SHI _hoops_SCH _hoops_HPP _hoops_SPR */
				_hoops_PICRA[_hoops_GCPAA-1] = -1;
				_hoops_CICRA->AdvanceCursor();
			}
			delete _hoops_CICRA;

			/* _hoops_AGGA _hoops_AASHR _hoops_RH _hoops_GGSRA _hoops_GPHA _hoops_ASGA _hoops_HII _hoops_GRR _hoops_HSP _hoops_SGS _hoops_ACPAA _hoops_SGS _hoops_GPHA */
			_hoops_HICRA::PairList * _hoops_PCPAA = _hoops_RIPAA->GetPairList();
			_hoops_HICRA::Pair * _hoops_SICRA;

			_hoops_PCPAA->ResetCursor();
			while ((_hoops_SICRA = _hoops_PCPAA->PeekCursor()) != 0) {

				POINTER_SIZED_INT	_hoops_PGSRA = _hoops_SICRA->Key();
			
				/* _hoops_SIPR _hoops_IASH _hoops_IIGR _hoops_RH _hoops_IPPA _hoops_GSSR _hoops_CR _hoops_SR _hoops_GA'_hoops_RA _hoops_RRP _hoops_SCH _hoops_CPRIR */
				_hoops_PPCIR *	_hoops_HCPAA;
				_hoops_RSCRA->LookupItem(_hoops_PGSRA, &_hoops_HCPAA);
				FREE(_hoops_HCPAA, _hoops_APCIR);

				_hoops_PPCIR	_hoops_GGPHR = _hoops_GPIRA::_hoops_CRGA;

				i = 0;
				do {
					vhash_status_t	result = _hoops_RSCRA->LookupNthItem(_hoops_PGSRA, i+1, &_hoops_HCPAA);
					if (result == VHASH_STATUS_FAILED)
						break;
					else {
						_hoops_GGPHR.x += _hoops_HCPAA->x;
						_hoops_GGPHR.y += _hoops_HCPAA->y;
						_hoops_GGPHR.z += _hoops_HCPAA->z;
						FREE(_hoops_HCPAA, _hoops_APCIR);
						i++;
					}
				} while (1);

				_hoops_GGPHR /= (double) i;
				_hoops_GGPHR._hoops_AAIAR();

				(*_hoops_IAPAA)[_hoops_PGSRA] = Vector(_hoops_GGPHR.x, _hoops_GGPHR.y, _hoops_GGPHR.z);

				_hoops_PCPAA->AdvanceCursor();
			}

			delete _hoops_PCPAA;
			delete _hoops_RIPAA;
			delete _hoops_RSCRA;

		    for (i = 0 ; i < _hoops_RISRA ; i++) {
				if (_hoops_PICRA[i] != -1) {
					if (!invert)
						(*_hoops_IAPAA)[_hoops_PICRA[i]] = normals[i];
				    else {
						((*_hoops_IAPAA)[_hoops_PICRA[i]]).x = -normals[i].x;
						((*_hoops_IAPAA)[_hoops_PICRA[i]]).y = -normals[i].y;
						((*_hoops_IAPAA)[_hoops_PICRA[i]]).z = -normals[i].z;
				    }
				}
		    }
		}   
	}
   
    if (_hoops_SPPAA)
		FREE_ARRAY(_hoops_SPPAA, _hoops_AHPAA, Point);
    if (_hoops_RGP)
		FREE_ARRAY(_hoops_RGP, _hoops_AHPAA, bool);

    FREE_ARRAY(points, _hoops_RISRA, Point);
    if (normals)
		FREE_ARRAY(normals, _hoops_RISRA, Vector);
    FREE_ARRAY(faces, _hoops_RHGIR, int);
    FREE_ARRAY(_hoops_PICRA, _hoops_RISRA, int);
	if (_hoops_GHPAA)
		FREE_ARRAY(_hoops_RICRA, _hoops_GHPAA, int);

    if (*_hoops_CAPAA == 0)
		return false;	    /* _hoops_SR _hoops_RIAGR _hoops_IRS _hoops_HSHRR _hoops_ICPAA _hoops_GGR, _hoops_HIS _hoops_PSP _hoops_SPCC _hoops_HPGR _hoops_RGR _hoops_PPSR _hoops_PIHA _hoops_SHH _hoops_PCCP _hoops_RIHH. */
    else
		return true;
}


/* _hoops_AHGHR _hoops_IRS _hoops_AGAPR _hoops_HIGR _hoops_IIGR _hoops_AAPI, _hoops_ARPR _hoops_PPSR _hoops_PPR _hoops_HSP _hoops_CPCI _hoops_IRPR _hoops_IH _hoops_IRS _hoops_AGAH _hoops_RRCPR.*/
/* _hoops_CCRAA _hoops_GPPS _hoops_CSPP */
local bool _hoops_CCPAA (
	_hoops_IGCRA *		_hoops_IRSRA,					/* _hoops_GHAAA */
	_hoops_PPCRA *		_hoops_RGPAA,		/* _hoops_CIIA _hoops_HSSP _hoops_HIGR */
	int *					_hoops_HAPAA,			/* _hoops_IIPR _hoops_PPSR _hoops_PPR _hoops_HSP _hoops_CIPH */
	_hoops_APCIR **				_hoops_SPRGA,
	Vector **				_hoops_IAPAA,
	int *					_hoops_CAPAA,
	int **					_hoops_SAPAA,
	int *					_hoops_GPPAA,		
	int *					_hoops_RPPAA,
	bool					invert,				/* _hoops_RPP _hoops_ISSP _hoops_HRGR _hoops_IHPR _hoops_PSCR _hoops_SR _hoops_HS */
												/* _hoops_IRS _hoops_HIGR _hoops_IIGR _hoops_AAPI _hoops_SGS _hoops_AAPR _hoops_GCPRA _hoops_HII _hoops_RH */
												/* _hoops_SGCRA _hoops_GGR _hoops_IRS _hoops_ICHRA _hoops_CAIH.  _hoops_GPGP _hoops_RGR _hoops_AGIR */
												/* _hoops_SR _hoops_RRP _hoops_IS _hoops_PIIA _hoops_RH _hoops_PPSR _hoops_AGR _hoops_HIS _hoops_SGS */
												/* _hoops_RSSP _hoops_HRGR _hoops_GGSP _hoops_GGR _hoops_RH _hoops_HACH _hoops_RRCPR. */
	bool					_hoops_APPAA,
	bool 					_hoops_PPPAA,
	RGB **					_hoops_AGRGA,
	int *					_hoops_HPPAA,
	bool **					_hoops_IPPAA,	
	bool 					_hoops_CPPAA) 
{  
    int 				_hoops_AAPAA = 0;
    int 				i = 0;
    _hoops_AIIRA *		first;
	int 				_hoops_RISRA = 0;
	int				 	_hoops_RHGIR = 0;
    _hoops_APCIR *			points;
    Vector *			normals = 0;
    RGB *				_hoops_SPPAA = 0;
    bool *				_hoops_RGP = 0;
    int 				_hoops_GHPAA;
    int *				faces; 
    bool 				_hoops_RCAI;
    int 				_hoops_RHPAA;
    long 				_hoops_AHPAA = 0;
    int *				_hoops_PICRA;
	int *				_hoops_RICRA = null;

    /* _hoops_ARP _hoops_RH _hoops_ASRC _hoops_HSH _hoops_GGR _hoops_AGIR _hoops_SR _hoops_HS _hoops_PCCP _hoops_RHPA _hoops_HSHRR. */
    *_hoops_HAPAA = 0;
    *_hoops_SPRGA = 0;
    *_hoops_IAPAA = 0;
    *_hoops_CAPAA = 0;
    *_hoops_GPPAA = 0;
    *_hoops_RPPAA = 0;
	if (_hoops_AGRGA)	
		*_hoops_AGRGA = 0;
	if (_hoops_HPPAA)
		*_hoops_HPPAA = 0;
	if (_hoops_IPPAA)
		*_hoops_IPPAA = 0;

	_hoops_APCIR	_hoops_PHPAA = _hoops_IRSRA->_hoops_CGCRA.min;
	_hoops_APCIR	_hoops_HHPAA = _hoops_IRSRA->_hoops_CGCRA.max;
	_hoops_APCIR	_hoops_IHPAA = _hoops_IRSRA->_hoops_GRCRA.min;
	_hoops_APCIR	_hoops_CHPAA = _hoops_IRSRA->_hoops_GRCRA.max;

    first = _hoops_RGPAA->PeekFirst();
    if (!first)
		return true;	    /* _hoops_PCCP _hoops_RHPA _hoops_CIIA _hoops_HSHRR _hoops_HRGR _hoops_RCRAR, _hoops_SR'_hoops_GCPP _hoops_SAHR _hoops_ASRC _hoops_RHPA _hoops_HSH. */

    _hoops_RISRA = first->_hoops_SIIRA->_hoops_SHIRA;

	_hoops_AIIRA * temp;

    _hoops_AHPAA = 0;
	_hoops_RGPAA->ResetCursor();
	while ((temp = _hoops_RGPAA->PeekCursor()) != null) {
		_hoops_RHGIR += (temp->_hoops_ICIRA + 1);
		_hoops_AHPAA++;
		_hoops_RGPAA->AdvanceCursor();
	}

    *_hoops_GPPAA = _hoops_RISRA;
    *_hoops_RPPAA = _hoops_RHGIR;
    ZALLOC_ARRAY(points, _hoops_RISRA, _hoops_APCIR);
    if (_hoops_APPAA) {     
		ZALLOC_ARRAY(normals, _hoops_RISRA, Vector);
     }

     ALLOC_ARRAY(faces, _hoops_RHGIR, int);

  
	if (_hoops_PPPAA)
		ALLOC_ARRAY(_hoops_SPPAA, _hoops_AHPAA, RGB);

    if (_hoops_CPPAA)
		ALLOC_ARRAY(_hoops_RGP, _hoops_AHPAA, bool);

    _hoops_GHPAA = 0; 
   
	_hoops_RGPAA->ResetCursor();
	while ((temp = _hoops_RGPAA->PeekCursor()) != null) {
	    _hoops_RHPAA = _hoops_AAPAA;
	    _hoops_RCAI = false;
    
	    if (_hoops_PPPAA || _hoops_CPPAA) {    
			if (_hoops_PPPAA) {
			    _hoops_SPPAA[_hoops_GHPAA] =  temp->_hoops_CSIRA;
			}
			if (_hoops_CPPAA)
			    _hoops_RGP[_hoops_GHPAA] = temp->_hoops_SSIRA;   
	    }

	    faces[_hoops_AAPAA++] = temp->_hoops_ICIRA;
	    for (i = 0 ; i < temp->_hoops_ICIRA ; i++) {
			int index;
			if (!invert)	
			    faces[_hoops_AAPAA++] = temp->_hoops_IIIRA[i];
			else 
			    faces[_hoops_AAPAA++] = temp->_hoops_IIIRA[temp->_hoops_ICIRA - 1 - i];
			index = temp->_hoops_IIIRA[i];
			points[index].x = temp->_hoops_PIIRA[i].x;
			points[index].y = temp->_hoops_PIIRA[i].y;
			points[index].z = temp->_hoops_PIIRA[i].z;
			if (invert && _hoops_IRSRA->_hoops_PRCRA && (points[index].x < _hoops_IHPAA.x || points[index].y < _hoops_IHPAA.y || points[index].z < _hoops_IHPAA.z ||
			     points[index].x > _hoops_CHPAA.x || points[index].y > _hoops_CHPAA.y || points[index].z > _hoops_CHPAA.z))
			    _hoops_RCAI = true;    /* _hoops_RGR _hoops_HSSP _hoops_CGH _hoops_IGRC _hoops_SHH _hoops_IAIH _hoops_PGGA _hoops_SCH'_hoops_GRI _hoops_SIPP _hoops_RH _hoops_IASC */
					    		/* _hoops_RGCRA _hoops_SGS _hoops_HS _hoops_RPII _hoops_IGI _hoops_IH _hoops_CHCRA. */
			if (_hoops_APPAA) {	
			    normals[temp->_hoops_IIIRA[i]] = Vector(temp->_hoops_HIIRA[i].x, temp->_hoops_HIIRA[i].y, temp->_hoops_HIIRA[i].z);
			}
	    }
	    if (_hoops_RCAI)     
			_hoops_AAPAA = _hoops_RHPAA;     
	    else {
			temp->_hoops_GSIRA = _hoops_GHPAA;
			_hoops_GHPAA++;
	    }

		_hoops_RGPAA->AdvanceCursor();
	}


    ALLOC_ARRAY(*_hoops_SPRGA, _hoops_RISRA, _hoops_APCIR);
    if (_hoops_APPAA)
		ALLOC_ARRAY(*_hoops_IAPAA, _hoops_RISRA, Vector);
    ALLOC_ARRAY(*_hoops_SAPAA, _hoops_RHGIR, int);
    ALLOC_ARRAY(_hoops_PICRA, _hoops_RISRA, int);

    PUSHNAME(_hoops_IRSRA->_hoops_RIGC);	
    if (_hoops_AAPAA)	{   /* _hoops_SCH'_hoops_GRI _hoops_SSRR _hoops_SR "_hoops_HPSH" _hoops_HCR _hoops_RSSI _hoops_ARRS, _hoops_RPP _hoops_GGR _hoops_RGSC _hoops_IIH _hoops_CSAP _hoops_PSP */
    		    	/* _hoops_SHPAA _hoops_GAPA _hoops_RH _hoops_SGCRA _hoops_PPR _hoops_SAAP */
		/* _hoops_SR _hoops_RRP _hoops_IS _hoops_AGRP _hoops_ISCP _hoops_RACIR _hoops_GSSR _hoops_CRPR _hoops_CRGR _hoops_PCCP _hoops_CRPR _hoops_IIGR _hoops_PHRP
		 *  _hoops_IS _hoops_RIH _hoops_GGR _hoops_IS _hoops_SCPAA */
		float *_hoops_GSPAA = 0;
	
		if (normals) {
			memcpy((void *)_hoops_GSPAA, normals, sizeof(float)*3*_hoops_RISRA);
			ALLOC_ARRAY(_hoops_GSPAA, 3*_hoops_RISRA, float);
		}

		if (_hoops_GHPAA)
			ALLOC_ARRAY(_hoops_RICRA, _hoops_GHPAA, int);

		HC_DCompute_Optimized_Shell(_hoops_RISRA, points, _hoops_GSPAA, _hoops_AAPAA, faces, "tolerance = 0.000001 oru, normal tolerance = 30 deg",
								   _hoops_HAPAA, *_hoops_SPRGA, _hoops_CAPAA, *_hoops_SAPAA, _hoops_PICRA, _hoops_RICRA);

		if (_hoops_GSPAA)
			FREE_ARRAY(_hoops_GSPAA, 3*_hoops_RISRA, float);

		if (_hoops_PPPAA || _hoops_CPPAA) {
		    int _hoops_GIPAA;   
	    
		    _hoops_GIPAA = _hoops_RAPAA(*_hoops_SAPAA, *_hoops_CAPAA);
		    if (_hoops_GIPAA) {	
		    	if (_hoops_PPPAA)
					ALLOC_ARRAY(*_hoops_AGRGA, _hoops_GIPAA, RGB);
		    	if (_hoops_CPPAA)
					ALLOC_ARRAY(*_hoops_IPPAA, _hoops_GIPAA, bool);
	    
		    	for (int j = 0 ; j < _hoops_GHPAA ; j++) {
					if (_hoops_RICRA[j] != -1) {	    
					    if (_hoops_PPPAA) {
							(*_hoops_AGRGA)[_hoops_RICRA[j]] = _hoops_SPPAA[j];
					    }
					    if (_hoops_CPPAA)
				    	    ((*_hoops_IPPAA)[_hoops_RICRA[j]]) = _hoops_RGP[j];
					}
		    	}
		    }

		    *_hoops_HPPAA = _hoops_GIPAA;
		}

		if (_hoops_APPAA) {
			_hoops_ICCRA *				_hoops_RSCRA = POOL_NEW(_hoops_IRSRA->_hoops_RIGC->memory_pool, _hoops_ICCRA)(_hoops_IRSRA->_hoops_RIGC->memory_pool, *_hoops_HAPAA*2);
			_hoops_HICRA *	_hoops_RIPAA = POOL_NEW(_hoops_IRSRA->_hoops_RIGC->memory_pool, _hoops_HICRA)(_hoops_IRSRA->_hoops_RIGC->memory_pool, *_hoops_HAPAA*2);
			_hoops_IICRA *	_hoops_CICRA = POOL_NEW(_hoops_IRSRA->_hoops_RIGC->memory_pool, _hoops_IICRA)(_hoops_IRSRA->_hoops_RIGC->memory_pool);

			/* _hoops_PS'_hoops_GCPP _hoops_SSS _hoops_PGAP _hoops_HHGP _hoops_RSSI _hoops_AIPAA, _hoops_PGAP _hoops_GIHA _hoops_SR _hoops_RRP _hoops_ASGA _hoops_IH,
				_hoops_PGAP _hoops_RSSI _hoops_PAH _hoops_HSSRR _hoops_IRS _hoops_GPHA _hoops_GSSR, _hoops_PPR _hoops_PGAP _hoops_GRS _hoops_HGAP _hoops_IRS _hoops_CCAH _hoops_GPHA _hoops_GSSR
				(_hoops_HAS._hoops_IAS., _hoops_SR _hoops_GGCR _hoops_GIHA _hoops_RPP _hoops_SR'_hoops_RISP _hoops_GGHP _hoops_ACIPR _hoops_SPPR) */
				_hoops_RGPAA->ResetCursor();
				while ((temp = _hoops_RGPAA->PeekCursor()) != null) {

					if (temp->_hoops_GCIRA || temp->_hoops_RCIRA) {
						_hoops_PPCRA *_hoops_PIPAA = POOL_NEW(_hoops_IRSRA->_hoops_RIGC->memory_pool, _hoops_PPCRA)(_hoops_IRSRA->_hoops_RIGC->memory_pool);
						_hoops_AIIRA *_hoops_GICRA;
						
						_hoops_SHCRA(temp, _hoops_RICRA, _hoops_PIPAA);

						_hoops_PIPAA->ResetCursor();
						while ((_hoops_GICRA = _hoops_PIPAA->PeekCursor()) != null) {

							/* _hoops_IRHH _hoops_RCRR _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_PCCP _hoops_GIGR _hoops_HSP _hoops_PIIHR _hoops_IS _hoops_HCHAR _hoops_IH _hoops_CCAH _hoops_GIHA */
							if (_hoops_GICRA->_hoops_RSIRA != 0) {
								_hoops_HICRA *_hoops_HIPAA = 
									POOL_NEW(_hoops_IRSRA->_hoops_RIGC->memory_pool, _hoops_HICRA)(_hoops_IRSRA->_hoops_RIGC->memory_pool, _hoops_GICRA->_hoops_ICIRA*2);

								_hoops_AICRA(temp, _hoops_GICRA, _hoops_PICRA, _hoops_HIPAA, _hoops_CICRA);
								
								_hoops_HICRA::PairList * _hoops_IIPAA = _hoops_HIPAA->GetPairList();
	
								_hoops_IGSRA(_hoops_GICRA, _hoops_IIPAA, _hoops_SPRGA, _hoops_HAPAA, _hoops_SAPAA,
															 _hoops_RSCRA, _hoops_RIPAA);

								delete _hoops_IIPAA;
								delete _hoops_HIPAA;
							}

							_hoops_PIPAA->AdvanceCursor();
						}

						delete _hoops_PIPAA;
					}
				
					_hoops_RGPAA->AdvanceCursor();
				}

			/* _hoops_SR _hoops_CIPAA _hoops_SIPAA _hoops_HIS _hoops_SGS _hoops_SR _hoops_GA'_hoops_RA _hoops_IPS "_hoops_AHCI" _hoops_GPHA _hoops_ASGA
				_hoops_IAPR _hoops_ISCP _hoops_GGSRA _hoops_GPHA _hoops_ASGA */
			_hoops_CICRA->ResetCursor();
			POINTER_SIZED_INT _hoops_GCPAA;
			while ((_hoops_GCPAA = _hoops_CICRA->PeekCursor()) != 0) {
				/* _hoops_SR _hoops_AGPI _hoops_RCPAA _hoops_PGGA _hoops_SR _hoops_SHI _hoops_SCH _hoops_HPP _hoops_SPR */
				_hoops_PICRA[_hoops_GCPAA-1] = -1;
				_hoops_CICRA->AdvanceCursor();
			}
			delete _hoops_CICRA;

			/* _hoops_AGGA _hoops_AASHR _hoops_RH _hoops_GGSRA _hoops_GPHA _hoops_ASGA _hoops_HII _hoops_GRR _hoops_HSP _hoops_SGS _hoops_ACPAA _hoops_SGS _hoops_GPHA */
			
			_hoops_HICRA::PairList * _hoops_PCPAA = _hoops_RIPAA->GetPairList();
			_hoops_HICRA::Pair * _hoops_SICRA;

			_hoops_PCPAA->ResetCursor();
			while ((_hoops_SICRA = _hoops_PCPAA->PeekCursor()) != 0) {
				POINTER_SIZED_INT _hoops_PGSRA = _hoops_SICRA->Key();
				_hoops_PPCIR *	_hoops_HCPAA;

				/* _hoops_SIPR _hoops_IASH _hoops_IIGR _hoops_RH _hoops_IPPA _hoops_GSSR _hoops_CR _hoops_SR _hoops_GA'_hoops_RA _hoops_RRP _hoops_SCH _hoops_CPRIR */
				_hoops_RSCRA->LookupItem(_hoops_PGSRA, &_hoops_HCPAA);
				FREE(_hoops_HCPAA, _hoops_PPCIR);
				
				_hoops_PPCIR	_hoops_GGPHR = _hoops_GPIRA::_hoops_CRGA;

				i = 0;
				do {

					if (_hoops_RSCRA->LookupNthItem(_hoops_PGSRA, i+1, &_hoops_HCPAA) == _hoops_HCCRA::Success)
						break;
					else {
						_hoops_GGPHR.x += _hoops_HCPAA->x;
						_hoops_GGPHR.y += _hoops_HCPAA->y;
						_hoops_GGPHR.z += _hoops_HCPAA->z;
						FREE(_hoops_HCPAA, _hoops_APCIR);
						i++;
					}
				} while (1);

				_hoops_GGPHR /= (double)i;

				_hoops_GGPHR._hoops_AAIAR();

				(*_hoops_IAPAA)[_hoops_PGSRA] = Vector(_hoops_GGPHR.x, _hoops_GGPHR.y, _hoops_GGPHR.z);

				_hoops_PCPAA->AdvanceCursor();
			}

			delete _hoops_PCPAA;
			delete _hoops_RIPAA;
			delete _hoops_RSCRA;

		    for (int j = 0 ; j < _hoops_RISRA ; j++) {
				if (_hoops_PICRA[j] != -1) {
					if (!invert)
						(*_hoops_IAPAA)[_hoops_PICRA[j]] = normals[j];
				    else {
						((*_hoops_IAPAA)[_hoops_PICRA[j]]).x = -normals[j].x;
						((*_hoops_IAPAA)[_hoops_PICRA[j]]).y = -normals[j].y;
						((*_hoops_IAPAA)[_hoops_PICRA[j]]).z = -normals[j].z;
				    }
				}
		    }
		}   
	}
    POPNAME(_hoops_IRSRA->_hoops_RIGC);
   
    if (_hoops_SPPAA)
		FREE_ARRAY(_hoops_SPPAA, _hoops_AHPAA, Point);
    if (_hoops_RGP)
		FREE_ARRAY(_hoops_RGP, _hoops_AHPAA, bool);

    FREE_ARRAY(points, _hoops_RISRA, _hoops_APCIR);
    if (normals)
		FREE_ARRAY(normals, _hoops_RISRA, Point);
    FREE_ARRAY(faces, _hoops_RHGIR, int);
    FREE_ARRAY(_hoops_PICRA, _hoops_RISRA, int);
	if (_hoops_GHPAA)
		FREE_ARRAY(_hoops_RICRA, _hoops_GHPAA, int);

    if (*_hoops_CAPAA == 0)
		return false;	    /* _hoops_SR _hoops_RIAGR _hoops_IRS _hoops_HSHRR _hoops_ICPAA _hoops_GGR, _hoops_HIS _hoops_PSP _hoops_SPCC _hoops_HPGR _hoops_RGR _hoops_PPSR _hoops_PIHA _hoops_SHH _hoops_PCCP _hoops_RIHH. */
    else
		return true;
}

/* _hoops_GPIPR _hoops_RH _hoops_IPHRA _hoops_HHIS _hoops_HII _hoops_IRS _hoops_GIIS _hoops_PPR _hoops_RAGA _hoops_IRS _hoops_HSSP _hoops_HIGR. */
local void _hoops_SASRA (
	_hoops_IGCRA *	_hoops_IRSRA,
	_hoops_IPCRA *			n, 
	_hoops_PPCRA *	_hoops_SHSRA ,
	double 				_hoops_IASGA) {
    _hoops_PPCRA *	_hoops_RSPAA;
    _hoops_PPCRA *	_hoops_ASPAA;
    _hoops_AIIRA *		_hoops_HARIR;
    _hoops_AIIRA *		root;
	
    _hoops_RSPAA = POOL_NEW(_hoops_IRSRA->_hoops_RIGC->memory_pool, _hoops_PPCRA)(_hoops_IRSRA->_hoops_RIGC->memory_pool);
    _hoops_ASPAA = POOL_NEW(_hoops_IRSRA->_hoops_RIGC->memory_pool, _hoops_PPCRA)(_hoops_IRSRA->_hoops_RIGC->memory_pool);

	_hoops_SHSRA->ResetCursor();
    
	root = _hoops_SHSRA->PeekCursor(); 
	_hoops_SHSRA->AdvanceCursor();

	/* _hoops_SIPR _hoops_RH _hoops_IPPA _hoops_HII _hoops_IRS _hoops_HSSP */
	n->_hoops_AHCRA = root->_hoops_HSIRA;

	n->_hoops_SPCRA->AddLast(root);

    /* _hoops_SGCH _hoops_RHIR _hoops_RH _hoops_ACSP _hoops_IIGR _hoops_RH _hoops_AAPI */
    while ((_hoops_HARIR = _hoops_SHSRA->PeekCursor()) != null) {
		_hoops_AIIRA *_hoops_ISRAA;
		_hoops_AIIRA *_hoops_SIPI;
		int result;
		/* _hoops_AIHH _hoops_RPP _hoops_RH _hoops_SCGR _hoops_HSSP _hoops_HRGR _hoops_GGR _hoops_RIPS, _hoops_GHIPR, _hoops_PAR _hoops_HHGP _hoops_HPP _hoops_RH */
	    /* _hoops_SCGR _hoops_AIIS _hoops_PSPAA _hoops_IPPA. */
 	    result = _hoops_APAAA(_hoops_HARIR, &n->_hoops_AHCRA, _hoops_IASGA);
	    switch (result) {
	    case _hoops_AHIRA:
		/* _hoops_PS _hoops_GA'_hoops_RA _hoops_CPSA _hoops_RRP _hoops_IS _hoops_GRHP _hoops_RH _hoops_SCIRA _hoops_AARI _hoops_CR _hoops_HCR _hoops_SR _hoops_PICP */
		/* _hoops_AHCA _hoops_CHR _hoops_RH _hoops_PSPAA _hoops_GHC. */
			if (_hoops_HARIR->_hoops_RSIRA)
				_hoops_HPAAA(_hoops_IRSRA, _hoops_HARIR);
			break;
	    case _hoops_RHIRA:
			_hoops_ASPAA->AddLast(_hoops_HARIR);
			break;
	    case _hoops_GHIRA:
			_hoops_RSPAA->AddLast(_hoops_HARIR);
			break;
	    case _hoops_PHIRA: {	    
			/* _hoops_RSRAA _hoops_RH _hoops_HSSP _hoops_PPR _hoops_HSPAA _hoops_RH _hoops_ISPAA _hoops_PAII _hoops_GIAH _hoops_ASRAR. */
			int _hoops_HGII = _hoops_GPAAA(_hoops_IRSRA, _hoops_HARIR, &n->_hoops_AHCRA, &_hoops_ISRAA, &_hoops_SIPI, _hoops_IASGA);

			switch (_hoops_HGII) {	    
		    case _hoops_AHIRA:
				if (_hoops_HARIR->_hoops_RSIRA)
					_hoops_HPAAA(_hoops_IRSRA, _hoops_HARIR);
		    	break;
		    case _hoops_RHIRA:
				_hoops_ASPAA->AddLast(_hoops_HARIR);
		    	break;
		    case _hoops_GHIRA:
				_hoops_RSPAA->AddLast(_hoops_HARIR);
		    	break;
		    case _hoops_PHIRA:
				if (_hoops_HARIR->_hoops_RSIRA)
					_hoops_HPAAA(_hoops_IRSRA, _hoops_HARIR);
   			    _hoops_ASPAA->AddLast(_hoops_SIPI);
			    _hoops_RSPAA->AddLast(_hoops_ISRAA);
		    	break; }
			} 
			break; 
	    }
	
		_hoops_SHSRA->AdvanceCursor();
    }

    /* _hoops_AGGA _hoops_RIPHR _hoops_RH _hoops_CPHRA _hoops_IH _hoops_RH _hoops_RIPS _hoops_PPR _hoops_ISSC _hoops_AAPI */
    if (_hoops_RSPAA->Count()) {
	 	ALLOC(n->_hoops_GCIRA, _hoops_IPCRA);
		_hoops_CASRA(_hoops_IRSRA, n->_hoops_GCIRA, n->_hoops_HHCRA);
		_hoops_SASRA(_hoops_IRSRA, n->_hoops_GCIRA, _hoops_RSPAA, _hoops_IASGA);
    }

    if (_hoops_ASPAA->Count()) {
	 	ALLOC(n->_hoops_RCIRA, _hoops_IPCRA);
		_hoops_CASRA(_hoops_IRSRA, n->_hoops_RCIRA, n->_hoops_HHCRA);
		_hoops_SASRA(_hoops_IRSRA, n->_hoops_RCIRA, _hoops_ASPAA, _hoops_IASGA);
    }

	delete _hoops_RSPAA; 
    delete _hoops_ASPAA; 
}


/* _hoops_HGI _hoops_PCPH _hoops_CSPAA _hoops_IRS _hoops_HSSP _hoops_ISHP _hoops_IRS _hoops_IPHRA _hoops_HHIS. */
/* _hoops_IPCP _hoops_HSSP _hoops_PAR _hoops_PRGGR _hoops_IIGR _hoops_RH _hoops_HSSP _hoops_SGS _hoops_SSPAA _hoops_SIPP */
/* _hoops_RH _hoops_CARA _hoops_GGHAA _hoops_HPP _hoops_RH _hoops_RGHAA _hoops_HRGR _hoops_RRAI _hoops_IS _hoops_RH _hoops_IGPAA. */
/* _hoops_IS _hoops_SHH _hoops_SIPP, _hoops_PCCP _hoops_CARA _hoops_IRHS _hoops_IS _hoops_SHH "_hoops_GGR _hoops_RIPS" _hoops_IIGR _hoops_RH _hoops_HPPA */
/* _hoops_GHC.  _hoops_CACPR _hoops_CARA _hoops_SGS _hoops_HRGR "_hoops_GGR _hoops_ISSC" _hoops_IIGR _hoops_PAR _hoops_ASPSR _hoops_CCA  */
/* _hoops_RH _hoops_HPPA _hoops_GHC _hoops_HRGR _hoops_GHSAR _hoops_IS _hoops_SHH _hoops_GIHRR _hoops_PPR _hoops_ASSA _hoops_RH _hoops_CARA. */
/* */
local void _hoops_RPSRA (
	_hoops_IGCRA *	_hoops_IRSRA,			/* _hoops_AGRR "_hoops_CSHGR" _hoops_PIH _hoops_SR _hoops_RRP     */
	_hoops_IPCRA *			n,				/* _hoops_AGHAA _hoops_IH _hoops_RH _hoops_IPHRA _hoops_PGHAA _hoops_SR _hoops_CHR _hoops_HHCPR _hoops_ACSRR */
	_hoops_AIIRA *		polygon,		/* _hoops_HGHAA _hoops_SR _hoops_CHR _hoops_HHCPR */
	_hoops_PPCRA *	_hoops_APSRA,		/* _hoops_ARGR _hoops_IGPAA. */
	bool				_hoops_PPSRA,	/* _hoops_IHPR _hoops_RPP _hoops_IRPAA _hoops_HRGR _hoops_ASSA, _hoops_RCPP _hoops_IAII. */
	double				_hoops_IASGA)			/* _hoops_AAHP _hoops_IS _hoops_SGH */
{
    _hoops_AIIRA *	_hoops_ISRAA;
    _hoops_AIIRA *	_hoops_SIPI;
    int result;

    _hoops_GRGAA;
    _hoops_IGGAA("CutPolygon:", polygon);

    result = _hoops_APAAA(polygon, &n->_hoops_AHCRA, _hoops_IASGA);

    _hoops_CGGAA(result, n);

    if (result == _hoops_AHIRA) {

		_hoops_PPCIR	_hoops_ICIPR = _hoops_PPCIR(polygon->_hoops_HSIRA)._hoops_AAIAR();

		_hoops_PPCIR	_hoops_CCIPR = _hoops_PPCIR(n->_hoops_AHCRA)._hoops_AAIAR();

		double	_hoops_IGHAA = _hoops_ICIPR._hoops_SSRP(_hoops_CCIPR);

		/* _hoops_IPSP _hoops_CHIA _hoops_IGH _hoops_IRPAA _hoops_HRGR "_hoops_GGR" _hoops_PAR "_hoops_GGSR".  _hoops_GPGP _hoops_PIHRA, */
		/* _hoops_SR _hoops_PICP _hoops_AHCA _hoops_IGH _hoops_RH _hoops_ASPSR _hoops_GHC _hoops_HS _hoops_PAII "_hoops_SHHRR" */
		/* _hoops_CPIC _hoops_RH _hoops_PSHR _hoops_HAGA. */
		if (_hoops_PPSRA)
		    result = (_hoops_IGHAA > 0) ? _hoops_RHIRA : _hoops_GHIRA;
		else
		    result = _hoops_GHIRA;
/*		    _hoops_GHPP = (_hoops_CGHAA > 0) ? _hoops_SGHAA : _hoops_GRHAA; */

		_hoops_CGGAA(result, n);
    }

    switch (result) {
    case _hoops_GHIRA:
		if (!n->_hoops_GCIRA) {
			_hoops_HGGAA("++++ Polygon outside. Add to Cutlist\n");
			_hoops_APSRA->AddLast(polygon);	/* _hoops_HGHAA _hoops_HRGR _hoops_SIPP _hoops_RH _hoops_CARA, _hoops_GGCR _hoops_IS _hoops_RH _hoops_IGPAA. */
		}
		else {
			_hoops_RPSRA(_hoops_IRSRA, n->_hoops_GCIRA, polygon, _hoops_APSRA, _hoops_PPSRA, _hoops_IASGA);	/* _hoops_ICIA _hoops_HHCPR _hoops_ACSRR _hoops_RH _hoops_HAAAA _hoops_RRHAA */
		}
 		break;
    case _hoops_RHIRA:
		if (n->_hoops_RCIRA) {
 			_hoops_RPSRA(_hoops_IRSRA, n->_hoops_RCIRA, polygon, _hoops_APSRA, _hoops_PPSRA, _hoops_IASGA);	/* _hoops_ICIA _hoops_HHCPR _hoops_ACSRR _hoops_RH _hoops_ARHAA _hoops_HIGR. */
		}
 		else {
			_hoops_HGGAA("---- Polygon inside, clear visibility.\n");
			polygon->_hoops_ISIRA = false; /* _hoops_HGHAA _hoops_ASSA _hoops_RH _hoops_CARA, _hoops_HIS _hoops_SSPC _hoops_SCH. */
		}
 		break;
    case _hoops_PHIRA: 
        _hoops_PSRAA(_hoops_IRSRA, polygon, &n->_hoops_AHCRA, &_hoops_ISRAA, &_hoops_SIPI, _hoops_IASGA);/* _hoops_RSRAA _hoops_RH _hoops_HSSP */

		polygon->_hoops_GCIRA = _hoops_ISRAA;
		
		if (!n->_hoops_GCIRA) {
			_hoops_HGGAA("++++ Front polygon outside. Add to Cutlist\n");
			_hoops_APSRA->AddLast(_hoops_ISRAA);	/* _hoops_RIPS _hoops_HSSP _hoops_HRGR _hoops_SIPP _hoops_RH _hoops_CARA, _hoops_GGCR _hoops_IS _hoops_IGPAA. */
		}
		else	   
			_hoops_RPSRA(_hoops_IRSRA, n->_hoops_GCIRA, _hoops_ISRAA, _hoops_APSRA, _hoops_PPSRA, _hoops_IASGA); /* _hoops_GRHP _hoops_HHCPR _hoops_ACSRR _hoops_RH _hoops_RIPS _hoops_HIGR */
	  
		if (n->_hoops_RCIRA) {
			polygon->_hoops_RCIRA = _hoops_SIPI;
 			_hoops_RPSRA(_hoops_IRSRA, n->_hoops_RCIRA, _hoops_SIPI, _hoops_APSRA, _hoops_PPSRA, _hoops_IASGA);  /* _hoops_GRHP _hoops_HHCPR _hoops_ISSC _hoops_SCIRA _hoops_ACSRR _hoops_RH _hoops_ISSC _hoops_HIGR */
		}
		else {
			_hoops_HPAAA(_hoops_IRSRA, _hoops_SIPI);
			_hoops_HGGAA("---- Back Polygon inside object. Throw away.\n");
			/* _hoops_ISAP _hoops_IS _hoops_AA _hoops_ARI, _hoops_HSSP _hoops_HRGR _hoops_ASSA _hoops_RH _hoops_CARA _hoops_HIS _hoops_SAHR */
			/* _hoops_RSRHR _hoops_SCH _hoops_GGSR. */
		}
		break;
    }

    _hoops_RRGAA;
}


/* _hoops_HGI _hoops_PCPH _hoops_CSPAA _hoops_IRS _hoops_HSSP _hoops_ISHP _hoops_IRS _hoops_IPHRA _hoops_HHIS. */
/* _hoops_IPCP _hoops_HSSP _hoops_PAR _hoops_PRGGR _hoops_IIGR _hoops_RH _hoops_HSSP _hoops_SGS _hoops_SSPAA _hoops_ASSA */
/* _hoops_RH _hoops_CARA _hoops_GGHAA _hoops_HPP _hoops_RH _hoops_RGHAA _hoops_HRGR _hoops_RRAI _hoops_IS _hoops_RH _hoops_IGPAA. */
/* _hoops_IS _hoops_SHH _hoops_SIPP, _hoops_PCCP _hoops_CARA _hoops_IRHS _hoops_IS _hoops_SHH "_hoops_GGR _hoops_RIPS" _hoops_IIGR _hoops_RH _hoops_HPPA */
/* _hoops_GHC.  _hoops_CACPR _hoops_CARA _hoops_SGS _hoops_HRGR "_hoops_GGR _hoops_ISSC" _hoops_IIGR _hoops_PAR _hoops_ASPSR _hoops_CCA  */
/* _hoops_RH _hoops_HPPA _hoops_GHC _hoops_HRGR _hoops_GHSAR _hoops_IS _hoops_SHH _hoops_GIHRR _hoops_PPR _hoops_ASSA _hoops_RH _hoops_CARA. */
/* */
local void _hoops_HPSRA (
	_hoops_IGCRA *	_hoops_IRSRA,
	_hoops_IPCRA *			n, 
	_hoops_AIIRA *		polygon,
	_hoops_PPCRA *	_hoops_APSRA,
	bool				_hoops_PPSRA,		/* _hoops_IHPR _hoops_RPP _hoops_IRPAA _hoops_HRGR _hoops_ASSA, _hoops_RCPP _hoops_IAII. */
	double				_hoops_IASGA)
{
    _hoops_AIIRA *	_hoops_ISRAA;
    _hoops_AIIRA *	_hoops_SIPI;

    _hoops_GRGAA;
    _hoops_IGGAA("CutPolygonInverse:", polygon);

    int result = _hoops_APAAA(polygon, &n->_hoops_AHCRA, _hoops_IASGA);
    _hoops_CGGAA(result, n);

    if (result == _hoops_AHIRA) {

		_hoops_PPCIR _hoops_ICIPR = _hoops_PPCIR(polygon->_hoops_HSIRA)._hoops_AAIAR();
		_hoops_PPCIR _hoops_CCIPR = _hoops_PPCIR(n->_hoops_AHCRA)._hoops_AAIAR();

		double	_hoops_IGHAA = _hoops_ICIPR._hoops_SSRP(_hoops_CCIPR);

		/* _hoops_IPSP _hoops_CHIA _hoops_IGH _hoops_IRPAA _hoops_HRGR "_hoops_GGR" _hoops_PAR "_hoops_GGSR".  _hoops_GPGP _hoops_PIHRA, */
		/* _hoops_SR _hoops_PICP _hoops_AHCA _hoops_IGH _hoops_RH _hoops_ASPSR _hoops_GHC _hoops_HS _hoops_PAII "_hoops_SHHRR" */
		/* _hoops_CPIC _hoops_RH _hoops_PSHR _hoops_HAGA. */
		if (_hoops_PPSRA)
		    result = (_hoops_IGHAA > 0) ? _hoops_RHIRA : _hoops_GHIRA;
		else
		    result = _hoops_GHIRA;
/*		    _hoops_GHPP = (_hoops_CGHAA > 0) ? _hoops_SGHAA : _hoops_GRHAA; */
    
		_hoops_CGGAA(result, n);
    }
 
    switch (result) {
    case _hoops_GHIRA:
		if (n->_hoops_GCIRA) {
			_hoops_HPSRA(_hoops_IRSRA, n->_hoops_GCIRA, polygon, _hoops_APSRA, _hoops_PPSRA,_hoops_IASGA);	/* _hoops_GRHP _hoops_HHCPR _hoops_ACSRR _hoops_RH _hoops_PRHAA _hoops_HIGR */
		}
		else {
			_hoops_HGGAA("---- Polygon Outside.  Clear Visibility\n");
			polygon->_hoops_ISIRA = false; /* _hoops_HGHAA _hoops_ASSA _hoops_RH _hoops_CARA, _hoops_HIS _hoops_SSPC _hoops_SCH. */
		}
		break;     
	case _hoops_RHIRA:
		if (!n->_hoops_RCIRA) {
		   _hoops_HGGAA("++++ Polygon inside.  Add to cutlist\n");
		  _hoops_APSRA->AddLast(polygon);				/* _hoops_HSSP _hoops_HRGR _hoops_ASSA _hoops_RH _hoops_CARA.  _hoops_RGPA _hoops_IS _hoops_IGPAA. */
		}
		else {
			_hoops_HPSRA(_hoops_IRSRA, n->_hoops_RCIRA, polygon, _hoops_APSRA, _hoops_PPSRA,_hoops_IASGA);	/* _hoops_SAS _hoops_HCHAR _hoops_HPGR _hoops_RH _hoops_ISSC _hoops_HIGR. */
		}
		break;
    case _hoops_PHIRA:
		_hoops_PSRAA(_hoops_IRSRA, polygon, &n->_hoops_AHCRA, &_hoops_ISRAA, &_hoops_SIPI, _hoops_IASGA); /* _hoops_HHGP _hoops_RH _hoops_SCIRA */

        polygon->_hoops_GCIRA = _hoops_SIPI;
		
		if (n->_hoops_GCIRA) {
			polygon->_hoops_RCIRA = _hoops_ISRAA;						
			_hoops_HPSRA(_hoops_IRSRA, n->_hoops_GCIRA, _hoops_ISRAA, _hoops_APSRA, _hoops_PPSRA, _hoops_IASGA);		/* _hoops_HSPAA _hoops_RIPS _hoops_ARIP _hoops_ISHP _hoops_RH _hoops_RIPS _hoops_HIGR. */
		}
		else {
			_hoops_HPAAA(_hoops_IRSRA, _hoops_ISRAA);
			_hoops_HGGAA("---- Front Polygon outside.  Throw Away.\n");
			/* _hoops_SCIRA _hoops_HRGR _hoops_SIPP _hoops_RH _hoops_CARA, _hoops_SSPC _hoops_SCH. */
		}
		if (!n->_hoops_RCIRA) {
			_hoops_HGGAA("++++ Back Polygon inside.  Add to Cutlist.\n");
			_hoops_APSRA->AddLast(_hoops_SIPI);				/* _hoops_SCIRA _hoops_HRGR _hoops_ASSA _hoops_RH _hoops_CARA, _hoops_GGCR _hoops_IS _hoops_RH _hoops_IGPAA. */
		}
		else
			_hoops_HPSRA(_hoops_IRSRA, n->_hoops_RCIRA, _hoops_SIPI, _hoops_APSRA, _hoops_PPSRA,_hoops_IASGA);		/* _hoops_SAS _hoops_IPAC _hoops_RH _hoops_ISSC _hoops_HIGR. */	
	
		break;
    }

    _hoops_RRGAA;
}

/* _hoops_SIPR _hoops_IASC _hoops_HPHS _hoops_IH _hoops_GIPR _hoops_RH _hoops_SGCRA _hoops_PPR _hoops_SAAP _hoops_PPSR _hoops_CPCI */
local void _hoops_HRHAA(
    _hoops_IGCRA *_hoops_IRSRA,
    int				_hoops_IRHAA,
    Point const	*_hoops_CRHAA,
    int				_hoops_SRHAA,
    Point const	*_hoops_GAHAA)   
{
	_hoops_APCIR _hoops_PHPAA, _hoops_HHPAA, _hoops_IHPAA, _hoops_CHPAA;
	int i;
	_hoops_PHPAA.x = _hoops_CRHAA[0].x;
	_hoops_PHPAA.y = _hoops_CRHAA[0].y;
	_hoops_PHPAA.z = _hoops_CRHAA[0].z;
	_hoops_HHPAA.x = _hoops_CRHAA[0].x;
	_hoops_HHPAA.y = _hoops_CRHAA[0].y;
	_hoops_HHPAA.z = _hoops_CRHAA[0].z;
	for (i = 0 ; i < _hoops_IRHAA ; i++) {
	    if (_hoops_PHPAA.x > _hoops_CRHAA[i].x)
			_hoops_PHPAA.x = _hoops_CRHAA[i].x;
	    if (_hoops_PHPAA.y > _hoops_CRHAA[i].y)
			_hoops_PHPAA.y = _hoops_CRHAA[i].y;
	    if (_hoops_PHPAA.z > _hoops_CRHAA[i].z)
			_hoops_PHPAA.z = _hoops_CRHAA[i].z;
	    if (_hoops_HHPAA.x < _hoops_CRHAA[i].x)
			_hoops_HHPAA.x = _hoops_CRHAA[i].x;
	    if (_hoops_HHPAA.y < _hoops_CRHAA[i].y)
			_hoops_HHPAA.y = _hoops_CRHAA[i].y;
	    if (_hoops_HHPAA.z < _hoops_CRHAA[i].z)
			_hoops_HHPAA.z = _hoops_CRHAA[i].z;
	}
 
	_hoops_HHPAA.x += 0.01f;
	_hoops_HHPAA.y += 0.01f;
	_hoops_HHPAA.z += 0.01f;
	_hoops_PHPAA.x -= 0.01f;
	_hoops_PHPAA.y -= 0.01f;
	_hoops_PHPAA.z -= 0.01f;	
	
	_hoops_IHPAA.x = _hoops_GAHAA[0].x;
	_hoops_IHPAA.y = _hoops_GAHAA[0].y;
	_hoops_IHPAA.z = _hoops_GAHAA[0].z;
	_hoops_CHPAA.x = _hoops_GAHAA[0].x;
	_hoops_CHPAA.y = _hoops_GAHAA[0].y;
	_hoops_CHPAA.z = _hoops_GAHAA[0].z;
	for (i = 0 ; i < _hoops_SRHAA ; i++) {
	    if (_hoops_IHPAA.x > _hoops_GAHAA[i].x)
			_hoops_IHPAA.x = _hoops_GAHAA[i].x;
	    if (_hoops_IHPAA.y > _hoops_GAHAA[i].y)
			_hoops_IHPAA.y = _hoops_GAHAA[i].y;
	    if (_hoops_IHPAA.z > _hoops_GAHAA[i].z)
			_hoops_IHPAA.z = _hoops_GAHAA[i].z;
	    if (_hoops_CHPAA.x < _hoops_GAHAA[i].x)
			_hoops_CHPAA.x = _hoops_GAHAA[i].x;
	    if (_hoops_CHPAA.y < _hoops_GAHAA[i].y)
			_hoops_CHPAA.y = _hoops_GAHAA[i].y;
	    if (_hoops_CHPAA.z < _hoops_GAHAA[i].z)
			_hoops_CHPAA.z = _hoops_GAHAA[i].z;
	}
 
	_hoops_CHPAA.x += 0.01f;
	_hoops_CHPAA.y += 0.01f;
	_hoops_CHPAA.z += 0.01f;
	_hoops_IHPAA.x -= 0.01f;
	_hoops_IHPAA.y -= 0.01f;
	_hoops_IHPAA.z -= 0.01f;

	_hoops_IRSRA->_hoops_CGCRA.min = _hoops_PHPAA;
	_hoops_IRSRA->_hoops_CGCRA.max = _hoops_HHPAA; 
	_hoops_IRSRA->_hoops_GRCRA.min = _hoops_IHPAA;
	_hoops_IRSRA->_hoops_GRCRA.max = _hoops_CHPAA;
}




/* _hoops_GHRAA _hoops_PPGS _hoops_HGCRA */
local _hoops_IGCRA * _hoops_RAHAA (
	_hoops_AIGPR *	_hoops_RIGC) 
{ 

    _hoops_IGCRA *_hoops_IRSRA;
	ZALLOC_CACHED (_hoops_IRSRA, _hoops_IGCRA);
	_hoops_IRSRA->_hoops_RIGC = _hoops_RIGC;
	ALLOC_ARRAY_CACHED(_hoops_IRSRA->_hoops_SRCRA, 3*_hoops_GRSRA, _hoops_APCIR);
	ALLOC_ARRAY_CACHED(_hoops_IRSRA->_hoops_RACRA, 4*_hoops_RRSRA, _hoops_APCIR);
	ALLOC_ARRAY_CACHED(_hoops_IRSRA->_hoops_PACRA, 3*_hoops_GRSRA, _hoops_PPCIR);
	ALLOC_ARRAY_CACHED(_hoops_IRSRA->_hoops_IACRA, 4*_hoops_RRSRA, _hoops_PPCIR);
	ALLOC_ARRAY_CACHED(_hoops_IRSRA->_hoops_SACRA, 3*_hoops_ARSRA, int);
	ALLOC_ARRAY_CACHED(_hoops_IRSRA->_hoops_RPCRA, 4*_hoops_PRSRA, int);
	ALLOC_ARRAY_CACHED(_hoops_IRSRA->_hoops_IRCRA, _hoops_SGSRA, _hoops_AIIRA);

    return _hoops_IRSRA;
}
#endif 

local void _hoops_AAHAA (
    void	*_hoops_PAHAA) {
#if !(defined  (DISABLE_COMPUTE) || defined  (_hoops_SRIRA))
    _hoops_IGCRA *_hoops_IRSRA = (_hoops_IGCRA *)_hoops_PAHAA;

    if (_hoops_IRSRA) {    
	    FREE_ARRAY(_hoops_IRSRA->_hoops_SRCRA,3*_hoops_GRSRA,_hoops_APCIR);
	    FREE_ARRAY(_hoops_IRSRA->_hoops_RACRA,4*_hoops_RRSRA,_hoops_APCIR);
		FREE_ARRAY(_hoops_IRSRA->_hoops_PACRA, 3*_hoops_GRSRA, _hoops_PPCIR);
		FREE_ARRAY(_hoops_IRSRA->_hoops_IACRA, 4*_hoops_RRSRA, _hoops_PPCIR);
	    FREE_ARRAY(_hoops_IRSRA->_hoops_SACRA,3*_hoops_ARSRA,int);
	    FREE_ARRAY(_hoops_IRSRA->_hoops_RPCRA,4*_hoops_PRSRA,int);
	    FREE_ARRAY(_hoops_IRSRA->_hoops_IRCRA,_hoops_SGSRA,_hoops_AIIRA);
	    FREE(_hoops_IRSRA, _hoops_IGCRA);
    }
#endif
}



HC_INTERFACE Key HC_CDECL HC_Compute_Boolean_Shell (
    int				_hoops_SRHAA,	    /* _hoops_SRS _hoops_ARP _hoops_CHR _hoops_RH _hoops_SAAP */
    Point const *	_hoops_GAHAA,
    Vector const *	_hoops_HAHAA,
    int				_hoops_IAHAA,
    int const *		_hoops_CAHAA,

	int				_hoops_IRHAA,	    /* _hoops_GIAP _hoops_ARP _hoops_IIGR _hoops_RSSA _hoops_CHR _hoops_RH "_hoops_SGCRA" */
    Point const *	_hoops_CRHAA,
    Vector const *	_hoops_SAHAA,
    int				_hoops_GPHAA,
    int const *		_hoops_RPHAA,

    char const *	option_string) 
{
	_hoops_PAPPR context("Compute_Boolean_Shell");

#if !(defined  (DISABLE_COMPUTE) || defined  (_hoops_SRIRA))
 
	int			_hoops_APHAA = 0, _hoops_PPHAA = 0, _hoops_HPHAA = 0, _hoops_IPHAA = 0;
	int			_hoops_CPHAA = 0, _hoops_SPHAA = 0;
	int			_hoops_GHHAA = 0, _hoops_RHHAA = 0;
	Point *		_hoops_AHHAA = null;
	Point *		_hoops_PHHAA = null;
	Vector *	_hoops_HHHAA = null;
	Vector *	_hoops_IHHAA = null;
	int *		_hoops_CHHAA = null;
	int *		_hoops_SHHAA = null;

 	Key _hoops_PGRAA = -1;
	_hoops_PPCRA *_hoops_PHSRA = POOL_NEW(context->memory_pool, _hoops_PPCRA)(context->memory_pool);
	_hoops_PPCRA *_hoops_HHSRA = POOL_NEW(context->memory_pool, _hoops_PPCRA)(context->memory_pool);
	_hoops_CPCRA *_hoops_GIHAA;
	_hoops_CPCRA *_hoops_RIHAA;
 	bool _hoops_APPAA = true;
	
    struct configs	config;

	_hoops_PGGAA;

 	_hoops_IGCRA *	_hoops_AIHAA = _hoops_RAHAA(context);

  	_hoops_HRHAA(_hoops_AIHAA, _hoops_IRHAA, _hoops_CRHAA, _hoops_SRHAA, _hoops_GAHAA);
 
	config._hoops_GHGAA = _hoops_RRIRA;
	config._hoops_RHGAA = _hoops_ARIRA;
	config._hoops_AHGAA = _hoops_HGIRA;
	if (!_hoops_CHGAA (context, option_string, &config))
	    return _hoops_SHSSR;

	_hoops_AIHAA->_hoops_RRCRA = config.operation;
	_hoops_AIHAA->_hoops_PRCRA = true;

	if (!_hoops_SAHAA || !_hoops_HAHAA)
	    _hoops_APPAA = false;
	ALLOC(_hoops_GIHAA, _hoops_CPCRA);
 	_hoops_CHAAA(_hoops_AIHAA, _hoops_GIHAA, _hoops_IRHAA, _hoops_CRHAA, _hoops_SAHAA, 
			 _hoops_GPHAA, _hoops_RPHAA, false, 0, 0, config._hoops_PHGAA,config._hoops_AHGAA);
	_hoops_HIAAA(_hoops_AIHAA, _hoops_GIHAA, (float)config._hoops_GHGAA);	    

	ALLOC(_hoops_RIHAA, _hoops_CPCRA);
 	_hoops_CHAAA(_hoops_AIHAA, _hoops_RIHAA, _hoops_SRHAA, _hoops_GAHAA, _hoops_HAHAA, 
	 	     _hoops_IAHAA, _hoops_CAHAA, true, 0, 0, config._hoops_HHGAA,config._hoops_AHGAA);
	_hoops_HIAAA(_hoops_AIHAA, _hoops_RIHAA, (float)config._hoops_GHGAA);	    
	
	 
	switch (config.operation) {
	case _hoops_RAGAA:	
		/* _hoops_HSRR _hoops_SGSSR, _hoops_SR _hoops_HHGC _hoops_IS _hoops_GRHP _hoops_RGAR _hoops_AGAP _hoops_AAPI _hoops_SGS _hoops_CHR _hoops_ASSA _hoops_GRR _hoops_RII. */
		/* _hoops_IH _hoops_RGR _hoops_SR _hoops_RRP _hoops_IS _hoops_ISSP _hoops_GIPR _hoops_PIHAA. */
		_hoops_ARGAA(false);

		_hoops_SGPAA(_hoops_AIHAA, _hoops_GIHAA, _hoops_RIHAA, _hoops_PHSRA, true, false, (float)config._hoops_RHGAA);
		if (!_hoops_PAPAA(_hoops_AIHAA, _hoops_PHSRA, &_hoops_APHAA, &_hoops_AHHAA, &_hoops_HHHAA, 
		     &_hoops_HPHAA, &_hoops_CHHAA, &_hoops_CPHAA, &_hoops_SPHAA, false, _hoops_APPAA, 0,0,0,0,0))
		    goto _hoops_HIHAA;

		_hoops_ARGAA(true);

		_hoops_SGPAA(_hoops_AIHAA, _hoops_RIHAA, _hoops_GIHAA, _hoops_HHSRA, true, false, (float)config._hoops_RHGAA);
		if (!_hoops_PAPAA(_hoops_AIHAA, _hoops_HHSRA, &_hoops_PPHAA, &_hoops_PHHAA, &_hoops_IHHAA, 
		     &_hoops_IPHAA, &_hoops_SHHAA, &_hoops_GHHAA, &_hoops_RHHAA, false, _hoops_APPAA,0,0,0,0,0))
		    goto _hoops_HIHAA;

		break;
	case _hoops_SRGAA:	  
		/* _hoops_HSRR _hoops_IIHAA, _hoops_SR _hoops_GRHP _hoops_RH _hoops_AAPI _hoops_GGR _hoops_RH _hoops_SAAP _hoops_SGS _hoops_CHR _hoops_SIPP _hoops_RH _hoops_SGSSR */
		/* _hoops_HIS _hoops_ISSP _hoops_RCPP.*/
		_hoops_ARGAA(false);

		_hoops_SGPAA(_hoops_AIHAA, _hoops_GIHAA, _hoops_RIHAA, _hoops_PHSRA, false, false, (float)config._hoops_RHGAA);
		if (!_hoops_PAPAA(_hoops_AIHAA, _hoops_PHSRA, &_hoops_APHAA, &_hoops_AHHAA, &_hoops_HHHAA, 
		     &_hoops_HPHAA, &_hoops_CHHAA, &_hoops_CPHAA, &_hoops_SPHAA,false, _hoops_APPAA,0,0,0,0,0))
		    goto _hoops_HIHAA;

		_hoops_ARGAA(true);

		/* _hoops_SR _hoops_RRP _hoops_IS _hoops_GRHP _hoops_RH _hoops_AAPI _hoops_HII _hoops_RH _hoops_SGCRA _hoops_SGS _hoops_CHR _hoops_ASSA _hoops_RH _hoops_SGSSR, _hoops_HIS */
		/* _hoops_ISSP _hoops_IHPR _hoops_ARI. */
		_hoops_SGPAA(_hoops_AIHAA, _hoops_RIHAA, _hoops_GIHAA, _hoops_HHSRA, true, false, (float)config._hoops_RHGAA);
		if (!_hoops_PAPAA(_hoops_AIHAA, _hoops_HHSRA, &_hoops_PPHAA, &_hoops_PHHAA, &_hoops_IHHAA, 
		     &_hoops_IPHAA, &_hoops_SHHAA, &_hoops_GHHAA, &_hoops_RHHAA, true,_hoops_APPAA,0,0,0,0,0))
		    goto _hoops_HIHAA;

		break;
	case _hoops_GAGAA:
		/* _hoops_CIHAA, _hoops_GRHP _hoops_RH _hoops_AAPI _hoops_SGS _hoops_CHR _hoops_SIPP _hoops_GIPR _hoops_IAHI, _hoops_HIS _hoops_ISSP _hoops_RCPP _hoops_GGR _hoops_GIPR _hoops_ARAR. */
		_hoops_ARGAA(false);

		_hoops_SGPAA(_hoops_AIHAA, _hoops_GIHAA, _hoops_RIHAA, _hoops_PHSRA, false, false, (float)config._hoops_RHGAA);

		/* _hoops_SIHAA(_hoops_GCHAA->_hoops_RCHAA, _hoops_ACHAA); */

		if (!_hoops_PAPAA(_hoops_AIHAA, _hoops_PHSRA, &_hoops_APHAA, &_hoops_AHHAA, &_hoops_HHHAA, 
		     &_hoops_HPHAA, &_hoops_CHHAA, &_hoops_CPHAA, &_hoops_SPHAA,false, _hoops_APPAA,0,0,0,0,0))
		    goto _hoops_HIHAA;

		_hoops_ARGAA(true);

		_hoops_SGPAA(_hoops_AIHAA, _hoops_RIHAA, _hoops_GIHAA, _hoops_HHSRA, false, false, (float)config._hoops_RHGAA);
		if (!_hoops_PAPAA(_hoops_AIHAA, _hoops_HHSRA, &_hoops_PPHAA, &_hoops_PHHAA, &_hoops_IHHAA, 
		     &_hoops_IPHAA, &_hoops_SHHAA, &_hoops_GHHAA, &_hoops_RHHAA, false, _hoops_APPAA,0,0,0,0,0))
		    goto _hoops_HIHAA;

		break;	    
	}
    /* _hoops_PISPR _hoops_RH _hoops_PGCR _hoops_SCHS _hoops_GIRP */
    _hoops_PGRAA = _hoops_SIGAA(_hoops_APHAA, _hoops_AHHAA, _hoops_HHHAA, _hoops_HPHAA, _hoops_CHHAA,
						  _hoops_PPHAA, _hoops_PHHAA, _hoops_IHHAA, _hoops_IPHAA, _hoops_SHHAA,0,0,0,0,0,0);

#ifdef _hoops_RGIRA
	_hoops_AHSRA( _hoops_PHSRA, _hoops_HHSRA, _hoops_RAPAA(_hoops_CHHAA, _hoops_HPHAA));

	_hoops_SGGAA;
#endif

_hoops_HIHAA:	
	_hoops_SIAAA(_hoops_AIHAA, _hoops_GIHAA);
	_hoops_SIAAA(_hoops_AIHAA, _hoops_RIHAA);

	if (_hoops_AHHAA)
	    FREE_ARRAY(_hoops_AHHAA, _hoops_CPHAA, Point);
 	if (_hoops_PHHAA)
 		FREE_ARRAY(_hoops_PHHAA, _hoops_GHHAA, Point);
	if (_hoops_HHHAA)
 	    FREE_ARRAY(_hoops_HHHAA, _hoops_CPHAA, Vector);
	if (_hoops_IHHAA)
 	    FREE_ARRAY(_hoops_IHHAA, _hoops_GHHAA, Vector);
	if (_hoops_CHHAA)
 		FREE_ARRAY(_hoops_CHHAA, _hoops_SPHAA, int);
	if (_hoops_SHHAA)
 	    FREE_ARRAY(_hoops_SHHAA, _hoops_RHHAA, int);	

    delete _hoops_PHSRA; 
	delete _hoops_HHSRA; 

	_hoops_AAHAA (_hoops_AIHAA);

 	return _hoops_PGRAA;
#else
    return _hoops_SHSSR;
#endif
}

#define _hoops_PCHAA
#ifdef _hoops_PCHAA

#if !(defined  (DISABLE_COMPUTE) || defined  (_hoops_SRIRA))

local void _hoops_HCHAA (
    _hoops_IGCRA *	_hoops_IRSRA,
    int					_hoops_IRHAA,
    _hoops_APCIR const *		_hoops_CRHAA,
    int					_hoops_SRHAA,
    _hoops_APCIR const *		_hoops_GAHAA)
{
	_hoops_APCIR	_hoops_PHPAA = _hoops_CRHAA[0];
	_hoops_APCIR	_hoops_HHPAA = _hoops_CRHAA[0];
	
	for (int i = 0 ; i < _hoops_IRHAA ; i++) {
	    if (_hoops_PHPAA.x > _hoops_CRHAA[i].x)
			_hoops_PHPAA.x = _hoops_CRHAA[i].x;
	    if (_hoops_PHPAA.y > _hoops_CRHAA[i].y)
			_hoops_PHPAA.y = _hoops_CRHAA[i].y;
	    if (_hoops_PHPAA.z > _hoops_CRHAA[i].z)
			_hoops_PHPAA.z = _hoops_CRHAA[i].z;
	    if (_hoops_HHPAA.x < _hoops_CRHAA[i].x)
			_hoops_HHPAA.x = _hoops_CRHAA[i].x;
	    if (_hoops_HHPAA.y < _hoops_CRHAA[i].y)
			_hoops_HHPAA.y = _hoops_CRHAA[i].y;
	    if (_hoops_HHPAA.z < _hoops_CRHAA[i].z)
			_hoops_HHPAA.z = _hoops_CRHAA[i].z;
	}
 
	_hoops_HHPAA.x += 0.01f;
	_hoops_HHPAA.y += 0.01f;
	_hoops_HHPAA.z += 0.01f;
	_hoops_PHPAA.x -= 0.01f;
	_hoops_PHPAA.y -= 0.01f;
	_hoops_PHPAA.z -= 0.01f;	
	

	_hoops_APCIR _hoops_IHPAA = _hoops_GAHAA[0];
	_hoops_APCIR _hoops_CHPAA = _hoops_GAHAA[0];

	for (int i = 0 ; i < _hoops_SRHAA ; i++) {
	    if (_hoops_IHPAA.x > _hoops_GAHAA[i].x)
			_hoops_IHPAA.x = _hoops_GAHAA[i].x;
	    if (_hoops_IHPAA.y > _hoops_GAHAA[i].y)
			_hoops_IHPAA.y = _hoops_GAHAA[i].y;
	    if (_hoops_IHPAA.z > _hoops_GAHAA[i].z)
			_hoops_IHPAA.z = _hoops_GAHAA[i].z;
	    if (_hoops_CHPAA.x < _hoops_GAHAA[i].x)
			_hoops_CHPAA.x = _hoops_GAHAA[i].x;
	    if (_hoops_CHPAA.y < _hoops_GAHAA[i].y)
			_hoops_CHPAA.y = _hoops_GAHAA[i].y;
	    if (_hoops_CHPAA.z < _hoops_GAHAA[i].z)
			_hoops_CHPAA.z = _hoops_GAHAA[i].z;
	}
 
	_hoops_CHPAA.x += 0.01f;
	_hoops_CHPAA.y += 0.01f;
	_hoops_CHPAA.z += 0.01f;
	_hoops_IHPAA.x -= 0.01f;
	_hoops_IHPAA.y -= 0.01f;
	_hoops_IHPAA.z -= 0.01f;

	_hoops_IRSRA->_hoops_CGCRA.min = _hoops_PHPAA;
	_hoops_IRSRA->_hoops_CGCRA.max = _hoops_HHPAA; 
	_hoops_IRSRA->_hoops_GRCRA.min = _hoops_IHPAA;
	_hoops_IRSRA->_hoops_GRCRA.max = _hoops_CHPAA;
}
#endif

 
HC_INTERFACE Key HC_CDECL HC_DKCompute_Boolean_Shell (
	int						_hoops_SRHAA,	    /* _hoops_SRS _hoops_HRGR _hoops_RH "_hoops_SAAP" */
    _hoops_APCIR const *			_hoops_GAHAA,
    Vector const *			_hoops_HAHAA,
    int						_hoops_IAHAA,
    int const *				_hoops_CAHAA,

	int						_hoops_IRHAA,	    /* _hoops_GIAP _hoops_HRGR _hoops_RH "_hoops_SGCRA" */
    _hoops_APCIR const *			_hoops_CRHAA,
    Vector const *			_hoops_SAHAA,
    int						_hoops_GPHAA,
    int const *				_hoops_RPHAA,

    char const *			option_string,
    RGB const *				_hoops_ICHAA,
    RGB const *				_hoops_CCHAA,
    unsigned short const *	_hoops_SCHAA,
    unsigned short const *	_hoops_GSHAA) 
{
	_hoops_PAPPR context("DKCompute_Boolean_Shell");

#if !(defined  (DISABLE_COMPUTE) || defined  (_hoops_SRIRA))

	int _hoops_APHAA = 0, _hoops_PPHAA = 0, _hoops_HPHAA = 0, _hoops_IPHAA = 0;
	int _hoops_CPHAA=0, _hoops_SPHAA = 0;
	int _hoops_GHHAA = 0, _hoops_RHHAA = 0;
	int _hoops_RSHAA=0;
	int _hoops_ASHAA=0;
	_hoops_APCIR *_hoops_AHHAA = 0;
	_hoops_APCIR *_hoops_PHHAA = 0;
 	Vector *_hoops_HHHAA = 0;
	Vector *_hoops_IHHAA = 0;
	int *_hoops_CHHAA = 0;
	int *_hoops_SHHAA = 0;
	RGB *_hoops_PSHAA = 0;
	RGB *_hoops_HSHAA = 0;
	bool *_hoops_ISHAA =0;
	bool *_hoops_CSHAA =0;
	Key _hoops_PGRAA = -1;
	_hoops_PPCRA *_hoops_PHSRA = POOL_NEW(context->memory_pool, _hoops_PPCRA)(context->memory_pool);
	_hoops_PPCRA *_hoops_HHSRA = POOL_NEW(context->memory_pool, _hoops_PPCRA)(context->memory_pool);


	_hoops_CPCRA *_hoops_GIHAA;
	_hoops_CPCRA *_hoops_RIHAA;
	
 	bool _hoops_APPAA = true;
	bool _hoops_PPPAA = false;
	bool _hoops_CPPAA = false;
    struct configs	config;


	_hoops_PGGAA;

 	_hoops_IGCRA * _hoops_AIHAA = _hoops_RAHAA(context);

  	_hoops_HCHAA(_hoops_AIHAA, _hoops_IRHAA, _hoops_CRHAA, _hoops_SRHAA, _hoops_GAHAA);

  	if (_hoops_ICHAA || _hoops_CCHAA)
	    _hoops_PPPAA = true;
  	if (_hoops_GSHAA || _hoops_SCHAA)
	    _hoops_CPPAA = true;

	config._hoops_GHGAA = _hoops_PRIRA;
	config._hoops_RHGAA = _hoops_HRIRA;
	config._hoops_AHGAA = _hoops_IGIRA;

 	if (!_hoops_CHGAA (context, option_string, &config))
	    return _hoops_SHSSR;

	_hoops_AIHAA->_hoops_RRCRA = config.operation;
	_hoops_AIHAA->_hoops_PRCRA = true;

	if (!_hoops_SAHAA || !_hoops_HAHAA)
	    _hoops_APPAA = false;
	ALLOC(_hoops_GIHAA, _hoops_CPCRA);
	_hoops_AIAAA(_hoops_AIHAA, _hoops_GIHAA, _hoops_IRHAA, _hoops_CRHAA, _hoops_SAHAA, 
	    _hoops_GPHAA, _hoops_RPHAA, true, _hoops_ICHAA, _hoops_SCHAA, config._hoops_PHGAA, config._hoops_AHGAA);
 	_hoops_HIAAA(_hoops_AIHAA, _hoops_GIHAA, config._hoops_GHGAA);	    

	ALLOC(_hoops_RIHAA, _hoops_CPCRA);
 	_hoops_AIAAA(_hoops_AIHAA, _hoops_RIHAA, _hoops_SRHAA, _hoops_GAHAA, _hoops_HAHAA, 
	    _hoops_IAHAA, _hoops_CAHAA, false, _hoops_CCHAA, _hoops_GSHAA, config._hoops_HHGAA, config._hoops_AHGAA);
	_hoops_HIAAA(_hoops_AIHAA, _hoops_RIHAA, config._hoops_GHGAA);	    
	

	switch (config.operation) {
	case _hoops_RAGAA:	
		/* _hoops_HSRR _hoops_SGSSR, _hoops_SR _hoops_HHGC _hoops_IS _hoops_GRHP _hoops_RGAR _hoops_AGAP _hoops_AAPI _hoops_SGS _hoops_CHR _hoops_ASSA _hoops_GRR _hoops_RII. */
		/* _hoops_IH _hoops_RGR _hoops_SR _hoops_RRP _hoops_IS _hoops_ISSP _hoops_GIPR _hoops_PIHAA. */
		/* _hoops_ICRAA _hoops_ACSRR _hoops_SGCRA, _hoops_SSHAA _hoops_GGR */
		_hoops_ARGAA(false);

		_hoops_SGPAA(_hoops_AIHAA, _hoops_GIHAA, _hoops_RIHAA, _hoops_PHSRA, true, true, config._hoops_RHGAA);
		if (!_hoops_CCPAA(_hoops_AIHAA, _hoops_PHSRA, &_hoops_APHAA, &_hoops_AHHAA, &_hoops_HHHAA, 
		     &_hoops_HPHAA, &_hoops_CHHAA, &_hoops_CPHAA, &_hoops_SPHAA,false, _hoops_APPAA,
			 _hoops_PPPAA, &_hoops_PSHAA, &_hoops_RSHAA, &_hoops_ISHAA, _hoops_CPPAA))
		    goto _hoops_HIHAA;
 		
		/* _hoops_SGCRA _hoops_ACSRR _hoops_ICRAA, _hoops_SSHAA _hoops_GGSR */
		_hoops_ARGAA(true);

		_hoops_SGPAA(_hoops_AIHAA, _hoops_RIHAA, _hoops_GIHAA, _hoops_HHSRA, true, false, config._hoops_RHGAA);
		if (!_hoops_CCPAA(_hoops_AIHAA, _hoops_HHSRA, &_hoops_PPHAA, &_hoops_PHHAA, &_hoops_IHHAA, 
		     &_hoops_IPHAA, &_hoops_SHHAA, &_hoops_GHHAA, &_hoops_RHHAA, false, _hoops_APPAA,
			 _hoops_PPPAA, &_hoops_HSHAA, &_hoops_ASHAA, &_hoops_CSHAA, _hoops_CPPAA))
		    goto _hoops_HIHAA;

		break;
	case _hoops_SRGAA:	  
		/* _hoops_HSRR _hoops_IIHAA, _hoops_SR _hoops_GRHP _hoops_RH _hoops_AAPI _hoops_GGR _hoops_RH _hoops_SAAP _hoops_SGS _hoops_CHR _hoops_SIPP _hoops_RH _hoops_SGSSR */
		/* _hoops_HIS _hoops_ISSP _hoops_RCPP.*/
		_hoops_ARGAA(false);

		_hoops_SGPAA(_hoops_AIHAA, _hoops_GIHAA, _hoops_RIHAA, _hoops_PHSRA, false, true, config._hoops_RHGAA);
		if (!_hoops_CCPAA(_hoops_AIHAA, _hoops_PHSRA, &_hoops_APHAA, &_hoops_AHHAA, &_hoops_HHHAA, 
		     &_hoops_HPHAA, &_hoops_CHHAA, &_hoops_CPHAA, &_hoops_SPHAA,false, _hoops_APPAA,
			 _hoops_PPPAA, &_hoops_PSHAA, &_hoops_RSHAA, &_hoops_ISHAA, _hoops_CPPAA))
		    goto _hoops_HIHAA;		
		
		/* _hoops_SR _hoops_RRP _hoops_IS _hoops_GRHP _hoops_RH _hoops_AAPI _hoops_HII _hoops_RH _hoops_SGCRA _hoops_SGS _hoops_CHR _hoops_ASSA _hoops_RH _hoops_SGSSR, _hoops_HIS */
		/* _hoops_ISSP _hoops_IHPR _hoops_ARI. */
		_hoops_ARGAA(true);

		_hoops_SGPAA(_hoops_AIHAA, _hoops_RIHAA, _hoops_GIHAA, _hoops_HHSRA, true, false, config._hoops_RHGAA);
		if (!_hoops_CCPAA(_hoops_AIHAA, _hoops_HHSRA, &_hoops_PPHAA, &_hoops_PHHAA, &_hoops_IHHAA, 
		     &_hoops_IPHAA, &_hoops_SHHAA, &_hoops_GHHAA, &_hoops_RHHAA, true ,_hoops_APPAA,
			 _hoops_PPPAA, &_hoops_HSHAA, &_hoops_ASHAA, &_hoops_CSHAA, _hoops_CPPAA))
		    goto _hoops_HIHAA;

		break;
	case _hoops_GAGAA:
		/* _hoops_CIHAA, _hoops_GRHP _hoops_RH _hoops_AAPI _hoops_SGS _hoops_CHR _hoops_SIPP _hoops_GIPR _hoops_IAHI, _hoops_HIS _hoops_ISSP _hoops_RCPP _hoops_GGR _hoops_GIPR _hoops_ARAR. */
		_hoops_ARGAA(false);

		_hoops_SGPAA(_hoops_AIHAA, _hoops_GIHAA, _hoops_RIHAA, _hoops_PHSRA, false, false, config._hoops_RHGAA);
		if (!_hoops_CCPAA(_hoops_AIHAA, _hoops_PHSRA, &_hoops_APHAA, &_hoops_AHHAA, &_hoops_HHHAA, 
		     &_hoops_HPHAA, &_hoops_CHHAA, &_hoops_CPHAA, &_hoops_SPHAA,false, _hoops_APPAA,
			 _hoops_PPPAA, &_hoops_PSHAA, &_hoops_RSHAA, &_hoops_ISHAA, _hoops_CPPAA))
		    goto _hoops_HIHAA;
				
		_hoops_ARGAA(true);

		_hoops_SGPAA(_hoops_AIHAA,_hoops_RIHAA, _hoops_GIHAA, _hoops_HHSRA, false, true, config._hoops_RHGAA);
		if (!_hoops_CCPAA(_hoops_AIHAA, _hoops_HHSRA, &_hoops_PPHAA, &_hoops_PHHAA, &_hoops_IHHAA, 
		     &_hoops_IPHAA, &_hoops_SHHAA, &_hoops_GHHAA, &_hoops_RHHAA, false, _hoops_APPAA,
			 _hoops_PPPAA, &_hoops_HSHAA, &_hoops_ASHAA, &_hoops_CSHAA, _hoops_CPPAA))
		    goto _hoops_HIHAA;

		break;    
	}
    /* _hoops_PISPR _hoops_RH _hoops_SCHS _hoops_GIRP */
    _hoops_PGRAA = _hoops_RRRAA(_hoops_APHAA, _hoops_AHHAA, _hoops_HHHAA, _hoops_HPHAA, _hoops_CHHAA,
			  _hoops_PPHAA, _hoops_PHHAA, _hoops_IHHAA, _hoops_IPHAA, _hoops_SHHAA, _hoops_PSHAA, 
			  _hoops_RSHAA, _hoops_HSHAA, _hoops_ASHAA, _hoops_ISHAA, _hoops_CSHAA);


#ifdef _hoops_RGIRA
    _hoops_AHSRA( _hoops_PHSRA, _hoops_HHSRA, _hoops_RAPAA(_hoops_CHHAA, _hoops_HPHAA));

    _hoops_SGGAA;
#endif



_hoops_HIHAA:	
	_hoops_SIAAA(_hoops_AIHAA, _hoops_GIHAA);
	_hoops_SIAAA(_hoops_AIHAA, _hoops_RIHAA);


	if (_hoops_AHHAA)
	    FREE_ARRAY(_hoops_AHHAA, _hoops_CPHAA, _hoops_APCIR);
 	if (_hoops_PHHAA)
 		FREE_ARRAY(_hoops_PHHAA, _hoops_GHHAA, _hoops_APCIR);
	if (_hoops_HHHAA)
 	    FREE_ARRAY(_hoops_HHHAA, _hoops_CPHAA, Point);
	if (_hoops_IHHAA)
 	    FREE_ARRAY(_hoops_IHHAA, _hoops_GHHAA, Point);
	if (_hoops_CHHAA)
 		FREE_ARRAY(_hoops_CHHAA, _hoops_SPHAA, int);
	if (_hoops_SHHAA)
 	    FREE_ARRAY(_hoops_SHHAA, _hoops_RHHAA, int);	
	if (_hoops_PSHAA)
 	    FREE_ARRAY(_hoops_PSHAA, _hoops_RSHAA, Point);	
	if (_hoops_HSHAA)
 	    FREE_ARRAY(_hoops_HSHAA, _hoops_ASHAA, Point);	
	if (_hoops_ISHAA)
 	    FREE_ARRAY(_hoops_ISHAA, _hoops_RSHAA, bool);	
	if (_hoops_CSHAA)
 	    FREE_ARRAY(_hoops_CSHAA, _hoops_ASHAA, bool);	

    delete _hoops_PHSRA; 
	delete _hoops_HHSRA; 

	_hoops_AAHAA (_hoops_AIHAA);

 	return _hoops_PGRAA;
#else
    return _hoops_SHSSR;
#endif
}

#endif /* _hoops_CCRAA _hoops_GGIAA */



#ifdef _hoops_RGIRA
local void _hoops_CHSRA (char *_hoops_GGIRA, HVList *_hoops_SHSRA) {
    FILE *_hoops_RGIAA;
    int i = 0;

    _hoops_RGIAA = fopen(_hoops_GGIRA, "wt");

    START_LIST_ITERATION(_hoops_AIIRA, _hoops_SHSRA);
	    fprintf(_hoops_RGIAA, "---- Old Face: %d, New Face = %d, points = %d\n", temp->_hoops_CCIRA, temp->_hoops_GSIRA,
				temp->_hoops_ICIRA);
	    for (i = 0 ; i < temp->_hoops_ICIRA ; i++)
			fprintf(_hoops_RGIAA, "%f %f %f\n", temp->_hoops_PIIRA[i].x, temp->_hoops_PIIRA[i].y, temp->_hoops_PIIRA[i].z);
    END_LIST_ITERATION(_hoops_SHSRA);

    fclose (_hoops_RGIAA);
}

local void _hoops_GISRA (char *_hoops_GGIRA, int _hoops_RISRA, _hoops_APCIR const *points, int _hoops_RHGIR, int *faces) { 
	int i, j, _hoops_HHHHR;
	FILE *_hoops_RGIAA;

	_hoops_RGIAA = fopen(_hoops_GGIRA, "wt");	
	for (i = 0 ; i < _hoops_RISRA ; i++)
		fprintf(_hoops_RGIAA, "point %d: %f %f %f\n", i, points[i].x, points[i].y, points[i].z);

	i = 0;
	while (i < _hoops_RHGIR) {
		_hoops_HHHHR = faces[i++];
		fprintf(_hoops_RGIAA, "\nface #pts = %d ", _hoops_HHHHR);
		for (j = 0 ; j < _hoops_HHHHR ; j++)
			fprintf(_hoops_RGIAA, " %d ", faces[i++]);
	}

	fclose(_hoops_RGIAA);
}

#endif

#ifdef _hoops_RGIRA
local void _hoops_AHSRA(
    HVList	*_hoops_PHSRA,
    HVList	*_hoops_HHSRA,
    int			    _hoops_IHSRA)
{
    FILE *_hoops_PSRGA  = 0;
   
    if (!_hoops_GHSRA)
		return;

    _hoops_PSRGA = fopen(_hoops_GHSRA, "wt");

    if (_hoops_PHSRA) {
		fprintf(_hoops_PSRGA, "Faces from the tool\n");
		START_LIST_ITERATION(_hoops_AIIRA, _hoops_PHSRA);
		    fprintf(_hoops_PSRGA, "%d -> %d\n", temp->_hoops_CCIRA, temp->_hoops_GSIRA);
		END_LIST_ITERATION(_hoops_PHSRA);
    }

    if (_hoops_HHSRA) {
		fprintf(_hoops_PSRGA, "\n\nFaces from target\n");
		START_LIST_ITERATION(_hoops_AIIRA, _hoops_HHSRA);
			if (temp->_hoops_GSIRA == -1)
			    fprintf(_hoops_PSRGA, "%d -> %d\n", temp->_hoops_CCIRA, temp->_hoops_GSIRA);
			else
			    fprintf(_hoops_PSRGA, "%d -> %d\n", temp->_hoops_CCIRA, temp->_hoops_GSIRA + _hoops_IHSRA);
		END_LIST_ITERATION(_hoops_HHSRA);
    }

    fclose(_hoops_PSRGA);
}

#endif


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
 * $Id: obf_tmp.txt 1.59 2010-12-16 19:42:16 reuben Exp $
 */

#ifndef _hoops_SGGSC

Begin_HOOPS_Namespace

/* _hoops_SCHGR _hoops_GRGSC */
#define	_hoops_GCSHA						(_hoops_SGIAP)0x00000001
#define	_hoops_SGPIR						(_hoops_SGIAP)0x00000002
#define	_hoops_PIRPH		(_hoops_SGIAP)0x00000004
#define	_hoops_PARPH		(_hoops_SGIAP)0x00000008
#define	_hoops_RRGSC			(_hoops_SGIAP)0x00000010
#define	_hoops_ARGSC		(_hoops_SGIAP)0x00000020
#define	_hoops_PPRPH				(_hoops_SGIAP)0x00000040
#define	_hoops_RPRPH			(_hoops_SGIAP)0x00000080
#define	_hoops_CARPH				(_hoops_SGIAP)0x00000100
#define	_hoops_SHRPH				(_hoops_SGIAP)0x00000200
#define	_hoops_PRGSC				(_hoops_SGIAP)0x00000400
#define	_hoops_RCSHA				(_hoops_SGIAP)0x00000800
#define	_hoops_HRGSC				(_hoops_SGIAP)0x00000F00
#define	_hoops_IRGSC				(_hoops_SGIAP)0x00000FF0
#define	_hoops_IARPH		(_hoops_SGIAP)0x00001000
#define	_hoops_SISHA					(_hoops_SGIAP)0x00002000
#define	_hoops_ISRPH		(_hoops_SGIAP)0x00004000
#define	_hoops_CSRPH					(_hoops_SGIAP)0x00008000
#define	_hoops_CRGSC					(_hoops_SGIAP)0x00010000

#define	_hoops_IRSCA				(_hoops_SGIAP)0x80000000

/* _hoops_SRGSC _hoops_IRAC */
#define	_hoops_HIAPH			(_hoops_APSHA)0x00000000
#define	_hoops_CPSHA			(_hoops_APSHA)0x00000001
#define	_hoops_HPSHA			(_hoops_APSHA)0x00000002
#define	_hoops_SPSHA		(_hoops_APSHA)0x00000004
#define	_hoops_IPSHA	(_hoops_APSHA)0x00000008
#define	_hoops_SARPH	(_hoops_APSHA)0x0000000F


/* _hoops_GAGSC (_hoops_PSGC _hoops_IIGR _hoops_RH _hoops_RHPP) */
enum _hoops_RAGSC {
	_hoops_AAGSC=0,
	_hoops_PAGSC,				  
	_hoops_HAGSC,		  
	_hoops_RAGRH,				  
	_hoops_IAGSC,				   
	_hoops_HSRPH,	
	_hoops_PSRPH,	   	   
	_hoops_RISHA,			

	_hoops_SPRPH,		
	_hoops_GHRPH,		
	_hoops_RHRPH,		
	_hoops_AHRPH,	   
	_hoops_PHRPH,	
	_hoops_HHRPH,	   
	_hoops_IHRPH,
	_hoops_CHRPH,
	_hoops_GIRPH,	
	_hoops_AIRPH,	

	_hoops_HPRPH,		   
	_hoops_CPRPH,		   
	_hoops_CIAPH,			   
	_hoops_APRPH,	   
	_hoops_IPRPH,	   
	   
	_hoops_RIRPH,	   
	_hoops_CAGSC,	   
	_hoops_HGAPH,		  

	_hoops_SSRPH,	
	_hoops_SAGSC,	
	_hoops_GPGSC,		
	_hoops_PIACA,	

	_hoops_IISAA,
	_hoops_GHGGC,

	_hoops_SGRHP,

	_hoops_ASGPI,
	_hoops_GAGRH
};

/*
	_hoops_RPGSC
	_hoops_HARSP _hoops_HPGR _hoops_APGSC _hoops_GHIR; _hoops_RH _hoops_RHPP _hoops_CGH _hoops_AA _hoops_CGSI _hoops_SGS
	_hoops_RRP _hoops_IS _hoops_SHH _hoops_CPHR _hoops_SHRII _hoops_RSIH, _hoops_PII _hoops_ARSSR _hoops_CCAH _hoops_SCHGR _hoops_PSSGR.
	_hoops_IPCP _hoops_RHPP _hoops_CGH _hoops_ASAI _hoops_AA _hoops_PA _hoops_IS _hoops_IRS _hoops_SISS _hoops_GAPR.

	_hoops_IPCP _hoops_ASRC _hoops_HSAGA _hoops_HRGR _hoops_IAIH.

	_hoops_PPGSC
	_hoops_HARSP _hoops_HPGR _hoops_RH _hoops_SRS _hoops_HRHI _hoops_IH _hoops_RH _hoops_RHPP. _hoops_IPCP _hoops_RHPP _hoops_CGH
	_hoops_CCPP _hoops_PPGS _hoops_PPR _hoops_HSPC _hoops_RH _hoops_SISS.

	_hoops_CGP _hoops_RH _hoops_ASRC _hoops_HSAGA _hoops_HRGR _hoops_HPGSC _hoops_PSCR _hoops_RH _hoops_RHPP _hoops_GRS _hoops_SHH _hoops_PPSPR
	_hoops_CRHPH _hoops_PPR _hoops_GRS _hoops_HAR _hoops_SHH _hoops_PIGS _hoops_GICS (_hoops_AHSAR _hoops_IH _hoops_IPGSC).

	_hoops_CPGSC
	_hoops_CGP _hoops_RH _hoops_RHPP _hoops_IRHS _hoops_IS _hoops_AA _hoops_PA _hoops_GGR _hoops_SPGSC _hoops_IS _hoops_IRS _hoops_GHGSC
	_hoops_AGRP _hoops_GGR _hoops_RH _hoops_AARPR, _hoops_SCH _hoops_CGH _hoops_AA _hoops_SCH _hoops_ARI. _hoops_HGI _hoops_HRGR _hoops_HIAGR
	_hoops_IIGR _hoops_IGH _hoops_RH _hoops_AARPR _hoops_AGRP _hoops_RGRRH _hoops_IRS _hoops_AIRI _hoops_AGRP.

	_hoops_CGP _hoops_RH _hoops_ASRC _hoops_HRGR _hoops_HPGSC, _hoops_RGR _hoops_IAGC _hoops_GRS _hoops_HAR _hoops_SHH _hoops_IIAC _hoops_IIGR _hoops_RH
	_hoops_RHPP _hoops_GICS.

	_hoops_RHGSC
	_hoops_IPCP _hoops_RHPP _hoops_GRS _hoops_AA _hoops_HISI _hoops_SCH _hoops_APPP _hoops_IS _hoops_RISIR _hoops_RH _hoops_SHPR _hoops_AIRI
	_hoops_GH _hoops_IS _hoops_ICGIP.

	_hoops_CGP _hoops_RH _hoops_ASRC _hoops_HRGR _hoops_HPGSC, _hoops_RGR _hoops_IAGC _hoops_GRS _hoops_HAR _hoops_SHH _hoops_IIAC _hoops_GICS _hoops_GHCRH
	_hoops_GRS _hoops_GII _hoops_HASRH _hoops_IAGC _hoops_SHH _hoops_IIAC.

	_hoops_AHGSC
	_hoops_IPCP _hoops_RHPP _hoops_CGH _hoops_GSAGP _hoops_ISHP _hoops_RH _hoops_AIRI. _hoops_ACHSP _hoops_SHH _hoops_PIGS _hoops_HII
	_hoops_RCHPH, _hoops_PPR _hoops_HIS _hoops_HCPCA _hoops_PPGS _hoops_GHCA _hoops_HAR _hoops_SHH _hoops_IRS _hoops_RIRA _hoops_GRIGI.

	_hoops_IPCP _hoops_ASRC _hoops_HSAGA _hoops_HRGR _hoops_IAIH.

	_hoops_IPGSC
	_hoops_PHGSC _hoops_CGPR _hoops_RH _hoops_CGHI _hoops_HHGSC _hoops_IIGR _hoops_RH _hoops_SAGHR _hoops_RHPP _hoops_CHR _hoops_RHSI
	_hoops_HII _hoops_RH _hoops_AARPR, _hoops_RPP _hoops_IHGSC _hoops_HRGR _hoops_HAR _hoops_IRAP. _hoops_IPCP _hoops_RHPP _hoops_CGH
	_hoops_CIH _hoops_HCR _hoops_RGCI _hoops_PPGS _hoops_PPR _hoops_ASRC.

	_hoops_IPCP _hoops_ASRC _hoops_HSAGA _hoops_HRGR _hoops_IAIH.


	_hoops_IPCP _hoops_RHPP _hoops_CGH _hoops_ASRC _hoops_HPGSC _hoops_IS _hoops_IRHC _hoops_SGS _hoops_SCH _hoops_PAH'_hoops_RA _hoops_IPPRH _hoops_GPP
	_hoops_RH _hoops_SAGHR _hoops_ARP _hoops_IIGR _hoops_SSHGR _hoops_IPIH _hoops_PPP.

	_hoops_CHGSC
	_hoops_IPCP _hoops_RHPP _hoops_CGH _hoops_ISPR _hoops_RH _hoops_PPP _hoops_CIIA _hoops_IH _hoops_AGSHA, _hoops_PPR _hoops_HAGIP _hoops_IH
	_hoops_SSHGR _hoops_IS _hoops_SHH _hoops_CGRHP _hoops_IAR.

		_hoops_HSRR _hoops_SHGSC _hoops_PPR _hoops_CHGSC, _hoops_RH _hoops_RHPP _hoops_PAH _hoops_HGCR _hoops_SGGR
		_hoops_CCA _hoops_GIGSC "_hoops_RIGSC" _hoops_SSHGR _hoops_PRGI _hoops_RPP _hoops_SSIA _hoops_CPSA _hoops_CGH _hoops_SHH
		"_hoops_AIGSC" _hoops_SSHGR: _hoops_RH _hoops_PIGSC _hoops_PCPH _hoops_GRS _hoops_HIGSC
		_hoops_PCPA'_hoops_GRI _hoops_CPIC _hoops_GPP. _hoops_IIGSC _hoops_IH _hoops_CIGSC _hoops_PPR _hoops_SSPPC.

	_hoops_HGI _hoops_API _hoops_GRS _hoops_RGAR _hoops_SHH _hoops_PIGS _hoops_RPP _hoops_CIIA _hoops_AGSHA _hoops_HS _hoops_RRHSA
	_hoops_RPII _hoops_PPHRH _hoops_PPP. _hoops_HHIGR _hoops_PIHA _hoops_ASRC _hoops_GSCPC.

	_hoops_SIGSC
	_hoops_IPCP _hoops_RHPP _hoops_CGH _hoops_SSS _hoops_IRS _hoops_GHSI _hoops_PIISR-_hoops_GGR "_hoops_GCGSC"
	_hoops_HRPR _hoops_CGI _hoops_GGR, _hoops_PPR _hoops_CGH _hoops_AA _hoops_IRS _hoops_RCGSC-_hoops_RHCS.

	_hoops_CGP _hoops_CPHP _hoops_HRGR _hoops_PPHRH _hoops_PACIA, _hoops_RH _hoops_GCGSC
	_hoops_HRPR _hoops_CGH _hoops_SHH _hoops_ASAS _hoops_PPR _hoops_RH _hoops_ASRC _hoops_HSAGA _hoops_CGH
	_hoops_SHH _hoops_GSCPC. (_hoops_IPCP _hoops_CIS _hoops_GRS _hoops_IGRC _hoops_GSSHR _hoops_RH _hoops_PGRRR.)

	_hoops_ACGSC - _hoops_PCGSC
	_hoops_HCGSC - _hoops_ICGSC
	_hoops_CCGSC - _hoops_SCGSC
	_hoops_GSGSC - _hoops_RSGSC
	_hoops_ASGSC - _hoops_PSGSC
		 _hoops_IPCP _hoops_RHPP _hoops_CGH _hoops_HSPP/_hoops_RRS _hoops_HSGSC _hoops_AHCA _hoops_PSCS _hoops_SSHGR _hoops_IIGR
		 _hoops_RH _hoops_CHIA _hoops_CSSC. (_hoops_ISGSC _hoops_IS _hoops_GSSHR _hoops_GRAA-_hoops_PPP _hoops_SSHGR _hoops_RHAP
		 _hoops_HAR _hoops_IGRC _hoops_GIPPR _hoops_PA _hoops_PHRI.) _hoops_IPCP _hoops_RIHRR _hoops_PGRRR _hoops_IPAC _hoops_PPR
		 _hoops_GIGSC _hoops_GRS _hoops_GPHCR _hoops_GPP _hoops_RCHAR _hoops_SHGSC _hoops_PAR
		 _hoops_CHGSC _hoops_PSGC.

	_hoops_CGP _hoops_RH _hoops_ASRC _hoops_HSAGA _hoops_CGH _hoops_SHH _hoops_HPGSC _hoops_RPP _hoops_RH _hoops_RHPP _hoops_RHAP _hoops_HAR _hoops_HS
	_hoops_GII _hoops_SISS _hoops_IIGR _hoops_RH _hoops_IRPR _hoops_GPRR.


	_hoops_CSGSC - _hoops_SSGSC
	_hoops_IPCP _hoops_RHPP _hoops_CGH _hoops_HSPP/_hoops_RRS _hoops_CGRSR _hoops_IRS _hoops_HASRH _hoops_APCS _hoops_GPP _hoops_RGCI
	_hoops_SHPR _hoops_GGR _hoops_CAPRH _hoops_CCA _hoops_RGCI _hoops_HAII _hoops_HCCIA _hoops_SISS.

	_hoops_CGP _hoops_RH _hoops_ASRC _hoops_HRGR _hoops_HPGSC, _hoops_RH _hoops_RHPP _hoops_SSSCP _hoops_IHGC _hoops_RGCI _hoops_HASRH _hoops_ACAS.

	_hoops_GGRSC - _hoops_RGRSC
	_hoops_IPCP _hoops_RHPP _hoops_CGH _hoops_HGCR _hoops_HRPP _hoops_IS _hoops_HGRAI _hoops_HASRH _hoops_PCRR _hoops_ICPAA
	_hoops_HII _hoops_GSPCA _hoops_SHS.

	_hoops_CGP _hoops_RH _hoops_RHPP _hoops_ASRC _hoops_HPGSC, _hoops_PSCR _hoops_PSP _hoops_HASRH _hoops_HRGR _hoops_SSRR (_hoops_RH _hoops_IPSP
	_hoops_HRGR _hoops_SPAII) _hoops_PPR _hoops_PSP _hoops_GHSHA _hoops_PSGC _hoops_GRS _hoops_GPHCR.

	_hoops_AGRSC
	_hoops_IPCP _hoops_RHPP _hoops_CGH _hoops_IGRC _hoops_PAAP _hoops_RH _hoops_RRHSA-_hoops_PPP _hoops_SHPP
	_hoops_HASRH. _hoops_IPCP _hoops_ARGPR _hoops_RGGHR _hoops_CHR _hoops_GGR _hoops_IRS _hoops_PGRSC _hoops_HRPR
	_hoops_CGI _hoops_GGR.

	_hoops_IPCP _hoops_ASRC _hoops_PIHA _hoops_SHH _hoops_GSCPC.

	_hoops_HGRSC
	_hoops_IPCP _hoops_RPPS-_hoops_GHARR _hoops_RHPP _hoops_CGH _hoops_ISPR _hoops_IH _hoops_RPPS-_hoops_GHARR _hoops_IGRSC,
	_hoops_IHIS, _hoops_PCCS, _hoops_AHI _hoops_SSHGR, _hoops_PPR _hoops_AASA _hoops_RH _hoops_IRPR _hoops_SAPRC _hoops_SICAR.

	_hoops_IPCP _hoops_HPGSC _hoops_HRGR _hoops_GIIA, _hoops_RH _hoops_GHARR _hoops_HRGR _hoops_HAR _hoops_IRS _hoops_RPPS _hoops_GHARR _hoops_PAR _hoops_IIH
	_hoops_HRGR _hoops_PSP _hoops_RRP _hoops_IS _hoops_ISPR _hoops_IH _hoops_CGRSC.



	_hoops_SGRSC
	_hoops_PSSHH _hoops_SGS _hoops_RH _hoops_RHPP _hoops_GGI _hoops_RGCI _hoops_CGRH _hoops_IPS _hoops_IIGR _hoops_CSCR _hoops_PIH _hoops_CRGR
	_hoops_RH _hoops_PIH _hoops_CRS _hoops_IIGR _hoops_PCCP _hoops_AARSP (_hoops_IH _hoops_PCAI, _hoops_HIS _hoops_SGS _hoops_SCH _hoops_PAH _hoops_SHH 
	_hoops_GRRSC _hoops_PPR/_hoops_PAR _hoops_PHPH _hoops_IS _hoops_IRS _hoops_RGHR.

	_hoops_IPCP _hoops_ASRC _hoops_CGH _hoops_SHR _hoops_SHH _hoops_GSCPC.
*/

/* _hoops_ASRC _hoops_PIRA _hoops_HII _hoops_RHPP _hoops_SIGH _hoops_IGH _hoops_SCH _hoops_CSAP _hoops_SHSS _hoops_IS _hoops_IPHAI
   _hoops_RH _hoops_IAGC. */

/* _hoops_PIP: _hoops_AGRR _hoops_HSAPH-_hoops_IGIGC _hoops_SPSIR _hoops_HPCAR _hoops_SGS _hoops_RH _hoops_PAIGR
	 _hoops_GH _hoops_IS _hoops_PPR _hoops_RHGGP '_hoops_RAPGA' _hoops_CHR _hoops_GGR _hoops_RH _hoops_ASGH _hoops_HSAPH _hoops_AGR.
 */


/* _hoops_GIGHR: _hoops_IHARH _hoops_IH _hoops_API-_hoops_GPRR _hoops_CRGIA _hoops_CHR _hoops_PSHS _hoops_GAR
		 256+(_hoops_RAIGC&0xFF).  _hoops_SPCA _hoops_HRGR _hoops_IPIH _hoops_PSP _hoops_HHPR _hoops_AGPGC
		 _hoops_IH _hoops_CRGIA _hoops_RII _hoops_HSAR _hoops_API & _hoops_HCCGI
*/

#define _hoops_HCRPH(code)	(((code)&0xFF00)==0x8000?0x0100|((code)&0x00FF)\
								 :(code)&0xFF00?0:(code))

#	define	  _hoops_RRPPH			  0
#	define	  _hoops_HGPPH	  (Button)0
#	define	  _hoops_IGPPH	  (Button)31
#	define	  _hoops_ISAPH  (Button)32 /* _hoops_GCIS _hoops_GC */
#	define	  _hoops_CSAPH	  (Button)126
#	define	  RUBOUT_KEY		  (Button)127
#	define	  _hoops_SSAPH (Button)161
#	define	  _hoops_GGPPH  (Button)255

#	define	  _hoops_RGPPH	  LEFT_ARROW_KEY
#	define	  LEFT_ARROW_KEY	  (Button)0x8001
#	define	  UP_ARROW_KEY		  (Button)0x8002
#	define	  RIGHT_ARROW_KEY	  (Button)0x8003
#	define	  DOWN_ARROW_KEY	  (Button)0x8004
#	define	  _hoops_AGPPH	  DOWN_ARROW_KEY

#	define    _hoops_SGPPH	  INSERT_KEY
#	define 	  INSERT_KEY		  (Button)0x8005
#	define 	  HOME_KEY		  (Button)0x8006
#	define 	  PAGE_UP_KEY		  (Button)0x8007
#	define 	  PAGE_DOWN_KEY		  (Button)0x8008
#	define 	  END_KEY		  (Button)0x8009
#	define 	  _hoops_GAPPH		  (Button)0x8010
#	define	  _hoops_GRPPH		  _hoops_GAPPH

#	define	  FIRST_KEYPAD_KEY	  (Button)0x8020
#	define	  _hoops_CGPPH	  (Button)0x805F

#	define	  FIRST_FUNCTION_KEY  (Button)0x8060
#	define	  _hoops_PGPPH	  (Button)0x809F

#	define	  _hoops_CRPIR			  511

#	define	  _hoops_AAHPH(x)		  (Button)(x - '@' + _hoops_HGPPH)


struct _hoops_APRHH {
	_hoops_HCRPR				item;			/* _hoops_PCPA'_hoops_GRI _hoops_PGIIP */
	_hoops_HCRPR				data;			/* _hoops_GHPP */
};

struct _hoops_RCHIH {
	bool				_hoops_RRRSC,
						_hoops_ARRSC,
						_hoops_PRRSC,
						_hoops_HRRSC;

	int					count;			/* _hoops_RSH _hoops_AHPH _hoops_GSGI */
	_hoops_HCRPR				*_hoops_HGPIR;			/* _hoops_CRPR _hoops_IIGR _hoops_RPPCR */
};

#define _hoops_IRRSC				0
#define _hoops_CRRSC				1
#define _hoops_SRRSC		2
#define _hoops_GARSC		3
#define _hoops_RARSC			4
#define _hoops_AARSC		5
#define _hoops_PARSC		6
#define _hoops_HARSC	7
#define _hoops_IARSC			8
#define _hoops_CARSC			9
#define _hoops_SARSC		10
#define _hoops_GPRSC			11
#define _hoops_RPRSC				12
#define _hoops_APRSC			13
#define _hoops_PPRSC		14
#define _hoops_HPRSC			15

struct _hoops_PGHGH {
	int					item;			/* _hoops_PCPA'_hoops_GRI _hoops_PGIIP */

	/* _hoops_IH _hoops_ICRP _hoops_CGSI... */
	_hoops_CSSGP	_hoops_SSSGP;		/* _hoops_SRCH _hoops_AARPR._hoops_GGHR - _hoops_GA'_hoops_RA */
	_hoops_HCRPR				specified;		/* _hoops_SGH "_hoops_IPRSC" _hoops_PPARR */

	float				height;			/* _hoops_IH _hoops_CPRSC */
	char *				_hoops_SPRSC;
	int					_hoops_GHRSC;
	_hoops_IHGRP		encoding;

	/* _hoops_IH _hoops_RHRSC */
	int					count;
	Point *				points;
	int					face_list_length;
	int *				face_list;

	/* _hoops_IH _hoops_AHRSC */
	KName				text;
	_hoops_HACC const *		_hoops_PCHIH;
	float				xfrac,
						yfrac;
	float				_hoops_PHRSC,
						_hoops_HHRSC;
	float				left, right,
						bottom, top;

	_hoops_CRCP *			context;
	int					_hoops_CISAA;
	_hoops_CRCP const **	path;
};


struct _hoops_RIACA {
	struct {int			left,
						right,
						bottom,
						top;}	_hoops_IIACA;
	struct {int			x, y;}	_hoops_HIACA;
	struct {float		x, y;}	_hoops_HAP;

	_hoops_CRCP*			context;
	int					_hoops_CISAA;
	_hoops_CRCP const **	path;
};

struct _hoops_RISAA {
	float				left, right, bottom, top;
	_hoops_ACHR			_hoops_RGP;
	bool				_hoops_PPSAA;
	_hoops_HGIAA			_hoops_PISAA;

	_hoops_CRCP *			context;
	int					_hoops_CISAA;
	_hoops_CRCP const **	path;
};

End_HOOPS_Namespace;

#define _hoops_SGGSC
#endif


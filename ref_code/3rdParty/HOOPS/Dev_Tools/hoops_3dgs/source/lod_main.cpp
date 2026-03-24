/************************************************************************

  MxMain.c

  This file provides the external interface for the LOD module.
  All communication to and from the outside world should pass through
  this file, through the function LOD_main.

  This file should be the only C file that knows about anything from HOOPS

  Copyright (C) 1998 Michael Garland.  See "COPYING.txt" for details.
  
  $Id: obf_tmp.txt 1.46 2010-01-20 01:34:55 covey Exp $

 ************************************************************************/

#include "hoops.h"

#ifndef DISABLE_LOD_GENERATION

#include "hi_proto.h"
#include "phedron.h"
#include "hpserror.h"
#include "lod.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>


/* _hoops_IH _hoops_GCCPI _hoops_RCCPI */
#define _hoops_ACCPI		0
#define _hoops_PCCPI		1 
#define _hoops_HCCPI			2
#define _hoops_ICCPI		3
#define _hoops_CCCPI		4

/* _hoops_IH _hoops_SCCPI _hoops_RCCPI */
#define _hoops_GSCPI		0
#define _hoops_RSCPI			1
#define _hoops_ASCPI			2
#define _hoops_PSCPI		3
#define _hoops_HSCPI 4
#define _hoops_ISCPI	5


/************************************************************************

  _hoops_HHRCP _hoops_CSGGI _hoops_GCIS _hoops_RGHR _hoops_IH _hoops_RH _hoops_CSCPI _hoops_GIRPR.
  _hoops_HIPR, _hoops_GPRR _hoops_PAIGR _hoops_IH _hoops_AGRR _hoops_PSPAR _hoops_PPR _hoops_HCIA

  _hoops_GICPI (_hoops_IHRPR) 1998 _hoops_RICPI _hoops_AICPI.  _hoops_AIHH "_hoops_PICPI._hoops_HICPI" _hoops_IH _hoops_RCAHR.
  
 ************************************************************************/




struct _hoops_SSCPI {
	double _hoops_GGSPI[4];
};

struct _hoops_RGSPI {
		double _hoops_GGSPI[3];
};

struct _hoops_AGSPI {
		double _hoops_GGSPI[2];
};

struct _hoops_PGSPI {
	_hoops_SSCPI row[4];
};

struct _hoops_HGSPI {
		_hoops_RGSPI row[3];
};

struct _hoops_IGSPI {
		_hoops_AGSPI row[2];
};

typedef int _hoops_CGSPI;


/* _hoops_HHH _hoops_PGPP _hoops_SASI _hoops_IS 3x3 _hoops_HCIA */
extern double _hoops_SGSPI (_hoops_HGSPI *, const _hoops_HGSPI *);
extern void _hoops_GRSPI (_hoops_RGSPI *_hoops_RRSPI, const _hoops_HGSPI *_hoops_RAGH, int i);
extern void _hoops_ARSPI (_hoops_RGSPI *_hoops_RRSPI, const _hoops_HGSPI *_hoops_RAGH, const _hoops_RGSPI *_hoops_ISPI);

/* _hoops_HHH _hoops_PGPP _hoops_SASI _hoops_IS 4x4 _hoops_HCIA */
extern void _hoops_PRSPI (_hoops_PGSPI *_hoops_PAGR, const _hoops_PGSPI *in);
extern void _hoops_HRSPI (_hoops_PGSPI *_hoops_PAGR, const _hoops_PGSPI *_hoops_RAGH, const _hoops_PGSPI *_hoops_AAGH);
extern void _hoops_IRSPI (_hoops_SSCPI *, const _hoops_PGSPI * _hoops_RAGH, const _hoops_SSCPI * v);


/* _hoops_PSGR _hoops_SPCC _hoops_AAGA _hoops_PGPP */

extern void	  _hoops_CRSPI (double *r, const double *u, const double *v, int _hoops_GHGIR);
extern void	  _hoops_SRSPI (double *r, const double *u, const double *v, int _hoops_GHGIR);
extern void	  _hoops_GASPI (double *r, const double *u, const double d, int _hoops_GHGIR);
extern void	  _hoops_RASPI (double *r, const double *u, const double d, int _hoops_GHGIR);
extern void	  _hoops_AASPI  (double *r, const double *u, int _hoops_GHGIR);
extern void	  _hoops_PASPI  (double *r, const double d, int _hoops_GHGIR);
extern void	  _hoops_HASPI	(double *r, const double *u, int _hoops_GHGIR);
extern double  _hoops_IASPI(const double *u, const double *v, int _hoops_GHGIR);
extern void	  _hoops_CASPI(double *r, const double *u, const double *v, int _hoops_GHGIR);
extern double  _hoops_SASPI(const double *v, int _hoops_GHGIR);
extern double  _hoops_GPSPI(const double *v, int _hoops_GHGIR); 
extern int	_hoops_RPSPI(double *v, int _hoops_GHGIR);
extern _hoops_CGSPI _hoops_APSPI(const double *u, const double *v, int _hoops_GHGIR);
extern _hoops_CGSPI _hoops_PPSPI(const double *u, const double *v, int _hoops_GHGIR);
extern void	  _hoops_HPSPI(double *r, int b, int _hoops_GHGIR);


/*
 * _hoops_A _hoops_PPR _hoops_PAIGR _hoops_IH _hoops_SHHP-_hoops_PHIAH
 */

/* _hoops_HAIA _hoops_AAPGH _hoops_SGH _hoops_IPSPI _hoops_RIIA _hoops_IIGR _hoops_CPSPI*/
#if !defined(_hoops_SPSPI) && defined(_hoops_GHSPI)
#define _hoops_SPSPI _hoops_GHSPI
#endif

/* _hoops_GSCA _hoops_SASPP, _hoops_HGPP _hoops_GAR _hoops_RHSPI, _hoops_PGAP _hoops_GA'_hoops_RA _hoops_PPIP _hoops_AHSPI _hoops_GGR <_hoops_CSGGI._hoops_GGHR>*/
#ifndef _hoops_IAGHA
#define _hoops_IAGHA 3.141592653589793238462643383279502884197169399375105820974944592308
#endif

/* _hoops_SSHGI _hoops_CICC _hoops_PHSPI(_hoops_GHGPR _hoops_IRS,_hoops_GHGPR _hoops_RCSR,_hoops_GHGPR _hoops_HHSPI) { _hoops_ASRC _hoops_IHSPI(_hoops_IRS-_hoops_RCSR)<_hoops_HHSPI; } */
#define _hoops_HSCIA(a,b,_hoops_ISCIA) ((fabs((a)-(b))<(_hoops_ISCIA)))

#ifndef _hoops_CHSPI
enum _hoops_SHSPI {X=0, Y=1, _hoops_GACPA=2, _hoops_CPCPA=3};
#endif


/* _hoops_HII _hoops_RH _hoops_RHGS _hoops_GISPI._hoops_GGHR */
extern double _hoops_RISPI(const _hoops_RGSPI *, const _hoops_RGSPI *, const _hoops_RGSPI *);
extern void	 _hoops_AISPI (_hoops_RGSPI *, const _hoops_RGSPI *, const _hoops_RGSPI *, const _hoops_RGSPI *);
extern int	_hoops_PISPI (_hoops_RGSPI *, const _hoops_RGSPI *, const _hoops_RGSPI *, const _hoops_RGSPI *);
extern int	_hoops_HISPI (_hoops_SSCPI *, const _hoops_RGSPI *, const _hoops_RGSPI *, const _hoops_RGSPI *);
extern void	 _hoops_IISPI (_hoops_SSCPI *, const _hoops_RGSPI *, const _hoops_RGSPI *, const _hoops_RGSPI *);
extern double _hoops_CISPI (const _hoops_RGSPI *, const _hoops_RGSPI *, const _hoops_RGSPI *);
extern void	 _hoops_SISPI (_hoops_RGSPI [], const _hoops_RGSPI *, const _hoops_RGSPI *);




/************************************************************************

  _hoops_GCSPI._hoops_GGHR

  _hoops_HGI _hoops_RGHR _hoops_ICGI _hoops_ICRP _hoops_IIGR _hoops_RH _hoops_PIH _hoops_CSSC _hoops_SIGR _hoops_HPP _hoops_RH _hoops_SPIGA _hoops_RPHRA:
  _hoops_RCSPI, _hoops_ACSPI
  _hoops_RHCP, _hoops_IHRRR, _hoops_ASCGR
  _hoops_PCSPI, _hoops_HCSPI, _hoops_ICSPI

  _hoops_GICPI (_hoops_IHRPR) 1998 _hoops_RICPI _hoops_AICPI.  _hoops_AIHH "_hoops_PICPI._hoops_HICPI" _hoops_IH _hoops_RCAHR.
  
 ************************************************************************/


/* 
 * _hoops_GSRSA _hoops_CHR _hoops_SIRGR _hoops_SGS _hoops_APCS _hoops_PCCS
 */
typedef struct  {
		int allocated;
		int used;
		int _hoops_CCSPI;
		void *data;
} _hoops_SCSPI;


/*
 * _hoops_API _hoops_IGCPR _hoops_IH _hoops_GSSPI _hoops_GSRSA
 */
extern void _hoops_RSSPI	   (_hoops_SCSPI *, int _hoops_ASSPI);
extern void _hoops_PSSPI  (_hoops_SCSPI *);
extern void _hoops_HSSPI	 (_hoops_SCSPI *);
extern int	_hoops_ISSPI	 (_hoops_SCSPI *, const void *_hoops_CSSPI);
extern int	_hoops_SSSPI	 (_hoops_SCSPI *, const void *_hoops_CSSPI);
extern void _hoops_GGGHI (_hoops_SCSPI *, const void *_hoops_CSSPI, int i);
extern void _hoops_RGGHI	 (_hoops_SCSPI *, int i, int j);
extern void _hoops_AGGHI	 (_hoops_SCSPI *, int which);
extern void _hoops_PGGHI	 (_hoops_SCSPI *, int size_in);
extern void _hoops_HGGHI	 (_hoops_SCSPI *);
extern int	_hoops_IGGHI (const _hoops_SCSPI *, int which);

#define _hoops_CGGHI(b) ((b)->used)
#define _hoops_SGGHI(b,i)	((char *)(b)->data + ((i) * (b)->_hoops_CCSPI))
#define _hoops_GRGHI(b,i)	(* ((void **) _hoops_SGGHI	((b), (i))))


/* _hoops_SIHPA _hoops_AIIS */
typedef struct  {
	double _hoops_RRGHI;		     /* _hoops_GHCP */
	void *_hoops_ASHSA;		     /* _hoops_PIH */
	POINTER_SIZED_INT token; /* _hoops_HGHC _hoops_GGR _hoops_SIHPA (_hoops_CRS-_hoops_PCPP _hoops_IS _hoops_RHHSR _hoops_AHSGP) */
} _hoops_ARGHI;

/*
 * _hoops_PSCH _hoops_IH _hoops_GSSPI _hoops_PRGHI
 */
/* _hoops_SSHGI _hoops_CICC _hoops_HRGHI (_hoops_IRGHI *_hoops_GGHR) { _hoops_ASRC _hoops_GGHR->_hoops_AAS != -47; } */
/* _hoops_SSHGI _hoops_SRPC _hoops_CRGHI (_hoops_IRGHI *_hoops_GGHR) { _hoops_GGHR->_hoops_AAS = -47; } */
/* _hoops_SSHGI _hoops_SCSH _hoops_SRGHI (_hoops_IRGHI *_hoops_GGHR) { _hoops_ASRC _hoops_GGHR->_hoops_AAS; } */
/* _hoops_SSHGI _hoops_SRPC _hoops_GAGHI (_hoops_IRGHI *_hoops_GGHR, _hoops_SCSH _hoops_RA) { _hoops_GGHR->_hoops_AAS=_hoops_RA; } */
/* _hoops_SSHGI _hoops_SRPC	_hoops_RAGHI (_hoops_IRGHI *_hoops_GGHR, _hoops_GHGPR _hoops_ARGI) { _hoops_GGHR->_hoops_AAGHI=_hoops_ARGI; } */
/* _hoops_SSHGI _hoops_GHGPR _hoops_PAGHI (_hoops_RCIC _hoops_IRGHI *_hoops_GGHR) { _hoops_ASRC _hoops_GGHR->_hoops_AAGHI; } */
/* _hoops_SSHGI _hoops_SRPC _hoops_HAGHI (_hoops_IRGHI *_hoops_GGHR) { _hoops_GGHR->_hoops_AAGHI = 0.0f; _hoops_GGHR->_hoops_AAS = -47; _hoops_GGHR->_hoops_PPISA = _hoops_IHHAH; } */

#define _hoops_IAGHI(h)  ((h)->token != -47)
#define _hoops_CAGHI(h)	((h)->token = -47)
#define _hoops_SAGHI(h)	 ((h)->token)
#define _hoops_GPGHI(h,t)  ((h)->token = t)
#define _hoops_RPGHI(h,k)  ((h)->_hoops_RRGHI = k)
#define _hoops_APGHI(h)	 ((h)->_hoops_RRGHI)
#define _hoops_PPGHI(h) { (h)->_hoops_RRGHI = 0.0f; (h)->token = -47; (h)->_hoops_ASHSA = NULL; }



/* _hoops_RH _hoops_SIHPA */
typedef struct  {
		_hoops_SCSPI data; /* _hoops_IRS _hoops_HPGHI _hoops_CSSSA _hoops_CRPR _hoops_IIGR _hoops_RGHHH. */
} _hoops_IPGHI;


extern void _hoops_CPGHI	   (_hoops_IPGHI *);
extern void _hoops_SPGHI (_hoops_IPGHI *); 
extern void _hoops_CHPHH		   (_hoops_IPGHI *, _hoops_ARGHI *);
extern void _hoops_GHGHI		   (_hoops_IPGHI *, _hoops_ARGHI *);
extern void *_hoops_PIPHH	   (_hoops_IPGHI *);
extern void _hoops_RHGHI		   (_hoops_IPGHI *, _hoops_ARGHI *);
extern void *_hoops_AHGHI		   (_hoops_IPGHI *, int);

/* _hoops_SSHGI _hoops_SCSH _hoops_PHGHI (_hoops_HHGHI *_hoops_SPHAI) { _hoops_ASRC _hoops_IHGHI (&(_hoops_SPHAI->_hoops_PIH)); } */
#define _hoops_CHGHI(m)  (_hoops_CGGHI (&((m)->data)))




typedef int _hoops_SHGHI;
typedef int _hoops_GIGHI;


/* 
 *	_hoops_GIIC _hoops_IGCPR _hoops_IH _hoops_RIGHI, _hoops_AIGHI, _hoops_PIGHI, _hoops_HIGHI
 *	_hoops_PPR _hoops_IHIA _hoops_HICRR _hoops_PSCH
 */

typedef _hoops_RGSPI _hoops_IIGHI;

/* _hoops_SIGR _hoops_IH _hoops_SRGIA _hoops_GPGR _hoops_GIHA _hoops_CCA _hoops_HAGH _hoops_AIRC */
typedef struct  {
		_hoops_SHGHI prev, next; 
} _hoops_CIGHI;

typedef struct  {
	_hoops_SHGHI _hoops_ISPI, _hoops_CSPI;
} _hoops_SIGHI ;

typedef struct  {
	_hoops_SHGHI v[3];
} _hoops_GCGHI;


/* _hoops_SSHGI _hoops_RCGHI _hoops_ACGHI (_hoops_HIGHI *_hoops_IAS, _hoops_RCGHI _hoops_HPPC) {
		_hoops_RPP (_hoops_HPPC == _hoops_IAS->_hoops_IIHHR) _hoops_ASRC _hoops_IAS->_hoops_CIHHR;
		_hoops_SHS { _hoops_ASRC _hoops_IAS->_hoops_IIHHR; }
}*/
#define _hoops_PCGHI(e,v) (((v)==(e)->_hoops_ISPI)?(e)->_hoops_CSPI:(e)->_hoops_ISPI)


extern void		  _hoops_HCGHI (_hoops_GCGHI *, _hoops_SHGHI, _hoops_SHGHI, _hoops_SHGHI);
extern int		  _hoops_ICGHI (const _hoops_GCGHI *, _hoops_SHGHI);
extern _hoops_SHGHI _hoops_CCGHI (const _hoops_GCGHI *, _hoops_SHGHI, _hoops_SHGHI);
extern _hoops_CGSPI	  _hoops_SCGHI (const _hoops_GCGHI *, _hoops_SHGHI, _hoops_SHGHI);
extern int		  _hoops_GSGHI (_hoops_GCGHI *, _hoops_SHGHI, _hoops_SHGHI);



/* 
 *	_hoops_GIIC _hoops_IGCPR _hoops_IH _hoops_RSGHI, _hoops_ASGHI, _hoops_PPR _hoops_PSGHI 
 *	(_hoops_HCR _hoops_CHR _hoops_CCCIP _hoops_PGPAA _hoops_GGR _hoops_HSGHI)
 *	_hoops_PPR _hoops_IHIA _hoops_HICRR _hoops_PSCH
 */

typedef struct  {
		unsigned char r, g, b, a;
		unsigned int _hoops_ISGHI;
} _hoops_CSGHI;

typedef struct  {
	double _hoops_CCSAR[3];
} _hoops_SSGHI;

typedef struct  {
	double u[2];
} _hoops_GGRHI;


#define _hoops_RGRHI(x)	 ((unsigned char)(((x)>1.0f?1.0f:(x))*255.0f))
#define _hoops_AGRHI(x)	 ((x) / 255.0f)

extern void _hoops_PGRHI (_hoops_CSGHI *, double, double, double);
extern void _hoops_HGRHI (_hoops_GGRHI *, double, double);
extern void _hoops_IGRHI (_hoops_SSGHI *, double, double, double);

/*
 * _hoops_RHCP, _hoops_IHRRR, _hoops_PPR _hoops_ASCGR _hoops_CPCI, _hoops_IPSH _hoops_IHIA _hoops_SGSS _hoops_PSCH 
 */

typedef _hoops_SCSPI _hoops_CGRHI;	   /* _hoops_SPPPI _hoops_GPRR _hoops_SGRHI */
typedef _hoops_SCSPI _hoops_GRRHI;	   /* _hoops_SPPPI _hoops_GPRR _hoops_RCGHI */

/* _hoops_SSHGI _hoops_SGRHI _hoops_RRRHI (_hoops_ARRHI *_hoops_PRRHI, _hoops_SCSH _hoops_HAS) {_hoops_ASRC *((_hoops_SGRHI *) _hoops_HRRHI (_hoops_PRRHI, _hoops_HAS));} */
/* _hoops_SSHGI _hoops_RCGHI _hoops_IRRHI (_hoops_CRRHI *_hoops_SRRHI, _hoops_SCSH _hoops_HAS) {	_hoops_ASRC *((_hoops_RCGHI *) _hoops_HRRHI (_hoops_SRRHI, _hoops_HAS));} */
#define _hoops_GARHI(_hoops_PSRGA,i)  (* ((_hoops_GIGHI *) _hoops_SGGHI (_hoops_PSRGA, i)))
#define _hoops_RARHI(vl,i)	 (* ((_hoops_SHGHI *) _hoops_SGGHI (vl, i)))

extern _hoops_CGSPI _hoops_AARHI (_hoops_CGRHI *_hoops_PSRGA, _hoops_GIGHI fid, int *index);
extern _hoops_CGSPI _hoops_PARHI (_hoops_GRRHI *vl, _hoops_GIGHI _hoops_HACGH, int *index);
												





/************************************************************************

  _hoops_HSGHI

  _hoops_GICPI (_hoops_IHRPR) 1998 _hoops_RICPI _hoops_AICPI.  _hoops_AIHH "_hoops_PICPI._hoops_HICPI" _hoops_IH _hoops_RCAHR.
  
 ************************************************************************/


/* 
 * _hoops_HHH _hoops_PSIGA _hoops_PAIGR _hoops_IH _hoops_RH _hoops_SARR _hoops_GPRR 
 */
#define _hoops_HARHI 0x0
#define _hoops_IARHI 0x1
#define _hoops_CARHI 0x2
#define _hoops_SARHI 0x2

#define _hoops_GPRHI	 0x3
#define _hoops_RPRHI	 (0x3<<2)
#define _hoops_APRHI	 (0x3<<4)
#define _hoops_PPRHI		 (_hoops_GPRHI|_hoops_RPRHI|_hoops_APRHI)


typedef struct 	{
	unsigned char _hoops_HPRHI, tag;			 /* _hoops_IAIGH _hoops_IRCCP _hoops_SIH*/
	unsigned char _hoops_IPRHI, _hoops_CPRHI;	 /* _hoops_SPRHI _hoops_IRCCP _hoops_SIH*/
} _hoops_GHRHI;


typedef struct   {
	unsigned char _hoops_HPRHI, tag;			 /* _hoops_IAIGH _hoops_IRCCP _hoops_SIH*/
	unsigned char _hoops_IPRHI, _hoops_CPRHI;	 /* _hoops_SPRHI _hoops_IRCCP _hoops_SIH*/
} _hoops_RHRHI;


typedef struct  {
	_hoops_SHGHI _hoops_ISPI, _hoops_CSPI;
	double _hoops_AHRHI[3], _hoops_PHRHI[3];	/* _hoops_HHRHI _hoops_HRGR _hoops_HAR _hoops_CPSA _hoops_HAHH*/
	_hoops_SCSPI _hoops_IHRHI; /* _hoops_SPPPI _hoops_GPRR _hoops_SCSH */
	_hoops_SCSPI _hoops_CHRHI; /* _hoops_SPPPI _hoops_GPRR _hoops_SCSH */

} _hoops_SHRHI;

extern void _hoops_GIRHI (_hoops_SHRHI *_hoops_RIRHI);
extern void _hoops_AIRHI (_hoops_SHRHI *_hoops_RIRHI);

/* _hoops_SSHGI _hoops_SCSH _hoops_PIRHI (_hoops_HIRHI *_hoops_IIRHI, _hoops_SCSH _hoops_HAS) { _hoops_ASRC *((_hoops_SCSH *) _hoops_HRRHI (&(_hoops_IIRHI->_hoops_CIRHI), _hoops_HAS)); } */
/* _hoops_SSHGI _hoops_SCSH _hoops_SIRHI (_hoops_HIRHI *_hoops_IIRHI, _hoops_SCSH _hoops_HAS) {	_hoops_ASRC *((_hoops_SCSH *) _hoops_HRRHI (&(_hoops_IIRHI->_hoops_GCRHI), _hoops_HAS)); } */
#define _hoops_RCRHI(_hoops_RIRHI,i)	(*((int *) _hoops_SGGHI (&((_hoops_RIRHI)->_hoops_IHRHI), (i))))
#define _hoops_ACRHI(_hoops_RIRHI,i)  (*((int *) _hoops_SGGHI (&((_hoops_RIRHI)->_hoops_CHRHI), (i))))


typedef _hoops_SHRHI _hoops_PCRHI;

/* _hoops_HCRHI _hoops_IH _hoops_SGCRP _hoops_IRCCP _hoops_SIH*/
#define _hoops_ICRHI 0x01
#define _hoops_CCRHI 0x02
#define _hoops_SCRHI 0x04

typedef struct  {
	/* _hoops_HCR _hoops_SIA _hoops_CPCI _hoops_CRCC _hoops_GPRR _hoops_SCSH */
	_hoops_SCSPI _hoops_GSRHI;	/* _hoops_ACAR _hoops_GIGR _hoops_AAPI _hoops_IS _hoops_RGR _hoops_SARR'_hoops_GRI _hoops_GIGR _hoops_HIPH */
	_hoops_SCSPI _hoops_RSRHI;	/* _hoops_ACAR _hoops_RGR _hoops_SARR'_hoops_GRI _hoops_GIGR _hoops_HIPH _hoops_IS _hoops_IIPR _hoops_HIPH */
	_hoops_SCSPI _hoops_ASRHI;	/* _hoops_ACAR _hoops_GIGR _hoops_GIHA _hoops_IS _hoops_IIPR _hoops_GIHA */

	/* _hoops_PSRHI _hoops_GSRSA*/
	_hoops_SCSPI vertices;				/* _hoops_PAHGA _hoops_GPRR _hoops_RIGHI */
	_hoops_SCSPI faces;				/* _hoops_PAHGA _hoops_GPRR _hoops_PIGHI */
	/* _hoops_HSRHI _hoops_GSRSA*/
	_hoops_SCSPI *normals;				/* _hoops_PAHGA _hoops_GPRR _hoops_ASGHI */
	_hoops_SCSPI *colors;				/* _hoops_PAHGA _hoops_GPRR _hoops_RSGHI */
	_hoops_SCSPI *_hoops_ISRHI;				/* _hoops_PAHGA _hoops_GPRR _hoops_CSRHI */

	_hoops_SCSPI _hoops_SSRHI; /* _hoops_SPPPI _hoops_GPRR _hoops_GGAHI */
	_hoops_SCSPI _hoops_RGAHI; /* _hoops_SPPPI _hoops_GPRR _hoops_AGAHI */
	_hoops_SCSPI _hoops_PGAHI;

	unsigned int flags;
	int _hoops_HGAHI;
	unsigned char _hoops_IGAHI, _hoops_CGAHI, _hoops_SGAHI;
} _hoops_GRAHI;

extern void _hoops_RRAHI (_hoops_GRAHI *m, int _hoops_ARAHI, int _hoops_PRAHI);
extern void _hoops_HRAHI (_hoops_GRAHI *m);


/*
 * _hoops_PPSS _hoops_ACAPA _hoops_SICAR
 */
/* _hoops_SSHGI _hoops_RIGHI *_hoops_IRAHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_SCSH _hoops_HAS) { _hoops_ASRC (_hoops_RIGHI *) _hoops_HRRHI	 (&(_hoops_SPHAI->_hoops_GIHA), _hoops_HAS); } */
/* _hoops_SSHGI _hoops_PIGHI *_hoops_CRAHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_SCSH _hoops_HAS) { _hoops_ASRC (_hoops_PIGHI *) _hoops_HRRHI  (&(_hoops_SPHAI->_hoops_RSSI), _hoops_HAS); } */
/* _hoops_SSHGI _hoops_RIGHI *_hoops_SRAHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_SGRHI _hoops_RCHP, _hoops_ICHRR _hoops_HAS) { _hoops_ASRC _hoops_IRAHI (_hoops_SPHAI, _hoops_CRAHI(_hoops_SPHAI, _hoops_RCHP)->_hoops_HPPC[_hoops_HAS]); } */
/* _hoops_SSHGI _hoops_ASGHI *_hoops_GAAHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_SCSH _hoops_HAS) { _hoops_ASRC (_hoops_ASGHI *) _hoops_HRRHI	 (_hoops_SPHAI->_hoops_ASGA, _hoops_HAS); } */
/* _hoops_SSHGI _hoops_RSGHI *_hoops_RAAHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_SCSH _hoops_HAS) { _hoops_ASRC (_hoops_RSGHI *) _hoops_HRRHI  (_hoops_SPHAI->_hoops_PSHA, _hoops_HAS); } */
/* _hoops_SSHGI _hoops_CSRHI *_hoops_AAAHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_SCSH _hoops_HAS) { _hoops_ASRC (_hoops_CSRHI *) _hoops_HRRHI  (_hoops_SPHAI->_hoops_PAAHI, _hoops_HAS); } */
/* _hoops_SSHGI _hoops_SCSH _hoops_HAAHI(_hoops_HSGHI *_hoops_SPHAI) { _hoops_ASRC _hoops_IHGHI (&(_hoops_SPHAI->_hoops_GIHA)); } */
/* _hoops_SSHGI _hoops_SCSH _hoops_IAAHI(_hoops_HSGHI *_hoops_SPHAI) { _hoops_ASRC _hoops_IHGHI (&(_hoops_SPHAI->_hoops_RSSI)); } */
#define _hoops_CAAHI(m,i)	 ((_hoops_IIGHI *) _hoops_SGGHI	 (&((m)->vertices), (i)))
#define _hoops_SAAHI(m,i)		 ((_hoops_GCGHI *) _hoops_SGGHI  (&((m)->faces), (i))) 
#define _hoops_GPAHI(m,f,i)	 (_hoops_CAAHI ((m), _hoops_SAAHI((m), (f))->v[(i)]))
#define _hoops_RPAHI(m,i)	 ((_hoops_SSGHI *) _hoops_SGGHI	 ((m)->normals, (i)))
#define _hoops_APAHI(m,i)	 ((_hoops_CSGHI *) _hoops_SGGHI	(m->colors, i))
#define _hoops_PPAHI(m,i)	 ((_hoops_GGRHI *) _hoops_SGGHI  (m->_hoops_ISRHI, i))
#define _hoops_HPAHI(m)  (_hoops_CGGHI (&((m)->vertices)))
#define _hoops_IPAHI(m)	 (_hoops_CGGHI (&((m)->faces)))
#define _hoops_CPAHI(m,i)	  ((POINTER_SIZED_INT) _hoops_GRGHI  (&((m)->_hoops_ASRHI), (i)))
extern int _hoops_SPAHI (_hoops_GRAHI *m);
extern int _hoops_GHAHI (_hoops_GRAHI *m);


/* 
 * _hoops_RHAHI _hoops_IH _hoops_SGCRP _hoops_IRCCP _hoops_PPR _hoops_HPGGR _hoops_SIH 
 */
/* _hoops_SSHGI _hoops_GGAHI *_hoops_AHAHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_SCSH _hoops_HAS) { _hoops_ASRC (_hoops_GGAHI *) _hoops_HRRHI	 (&(_hoops_SPHAI->_hoops_PHAHI), _hoops_HAS); }; */
/* _hoops_SSHGI _hoops_SCSH _hoops_HHAHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_RCGHI _hoops_HAS, _hoops_SCSH _hoops_IRCCP) { _hoops_ASRC _hoops_AHAHI (_hoops_SPHAI,_hoops_HAS)->_hoops_IRCCP & _hoops_IRCCP; } */
/* _hoops_SSHGI _hoops_SRPC _hoops_IHAHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_RCGHI _hoops_HAS, _hoops_SCSH _hoops_IRCCP) { _hoops_AHAHI (_hoops_SPHAI, _hoops_HAS)->_hoops_IRCCP |= _hoops_IRCCP; } */
/* _hoops_SSHGI _hoops_SRPC _hoops_CHAHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_RCGHI _hoops_HAS, _hoops_SCSH _hoops_IRCCP) { _hoops_AHAHI (_hoops_SPHAI, _hoops_HAS)->_hoops_IRCCP &= ~_hoops_IRCCP; } */
/* _hoops_SSHGI _hoops_APPC _hoops_GSPR _hoops_SHAHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_RCGHI _hoops_HAS) { _hoops_ASRC _hoops_AHAHI (_hoops_SPHAI, _hoops_HAS)->_hoops_HPGGR; } */
/* _hoops_SSHGI _hoops_SRPC _hoops_GIAHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_RCGHI _hoops_HAS, _hoops_APPC _hoops_GSPR _hoops_GSGGR) { _hoops_AHAHI (_hoops_SPHAI, _hoops_HAS)->_hoops_HPGGR = _hoops_GSGGR; } */
#define _hoops_RIAHI(m,i)		((_hoops_GHRHI *) _hoops_SGGHI  (&((m)->_hoops_SSRHI), (i)))
#define _hoops_AIAHI(m,i,t)	(_hoops_RIAHI ((m), (i))->tag & (t))
#define _hoops_PIAHI(m,i,t)	(_hoops_RIAHI ((m), (i))->tag |= (t))
#define _hoops_HIAHI(m,i,t)	(_hoops_RIAHI ((m), (i))->tag &= ~(t))
#define _hoops_IIAHI(m,i)		(_hoops_RIAHI ((m), (i))->_hoops_HPRHI)
#define _hoops_CIAHI(m,i,c)		(_hoops_RIAHI ((m), (i))->_hoops_HPRHI = (c))

/* _hoops_SSHGI _hoops_AGAHI *_hoops_SIAHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_SCSH _hoops_HAS) { _hoops_ASRC (_hoops_AGAHI *) _hoops_HRRHI	 (&(_hoops_SPHAI->_hoops_GCAHI), _hoops_HAS); }; */
/* _hoops_SSHGI _hoops_SCSH _hoops_RCAHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_SGRHI _hoops_HAS, _hoops_SCSH _hoops_IRCCP) { _hoops_ASRC _hoops_SIAHI (_hoops_SPHAI, _hoops_HAS)->_hoops_IRCCP & _hoops_IRCCP; } */
/* _hoops_SSHGI _hoops_SRPC _hoops_ACAHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_SGRHI _hoops_HAS, _hoops_SCSH _hoops_IRCCP) { _hoops_SIAHI (_hoops_SPHAI, _hoops_HAS)->_hoops_IRCCP |= _hoops_IRCCP; } */
/* _hoops_SSHGI _hoops_SRPC _hoops_PCAHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_SGRHI _hoops_HAS, _hoops_SCSH _hoops_IRCCP) { _hoops_SIAHI (_hoops_SPHAI, _hoops_HAS)->_hoops_IRCCP &= ~_hoops_IRCCP; } */
/* _hoops_SSHGI _hoops_APPC _hoops_GSPR _hoops_HCAHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_SGRHI _hoops_HAS) { _hoops_ASRC _hoops_SIAHI (_hoops_SPHAI, _hoops_HAS)->_hoops_HPGGR; } */
/* _hoops_SSHGI _hoops_SRPC _hoops_ICAHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_SGRHI _hoops_HAS, _hoops_APPC _hoops_GSPR _hoops_GSGGR) { _hoops_SIAHI (_hoops_SPHAI, _hoops_HAS)->_hoops_HPGGR = _hoops_GSGGR; } */
#define _hoops_CCAHI(m,i)		((_hoops_RHRHI *) _hoops_SGGHI	 (&((m)->_hoops_RGAHI), (i)))
#define _hoops_SCAHI(m,i,t)	(_hoops_CCAHI ((m), (i))->tag & (t))
#define _hoops_GSAHI(m,i,t)	(_hoops_CCAHI ((m), (i))->tag |= (t))
#define _hoops_RSAHI(m,i,t)	(_hoops_CCAHI ((m), (i))->tag &= ~(t))
#define _hoops_ASAHI(m,i)		(_hoops_CCAHI ((m), (i))->_hoops_HPRHI)
#define _hoops_PSAHI(m,i,c)		(_hoops_CCAHI ((m), (i))->_hoops_HPRHI = (c))


/* 
 * _hoops_HSAHI _hoops_ACAPA _hoops_IH _hoops_ISAHI _hoops_PPR _hoops_ISCPR 
 */
/* _hoops_SSHGI _hoops_SCSH _hoops_CSAHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_RCGHI _hoops_HAS) { _hoops_ASRC _hoops_HHAHI(_hoops_SPHAI,_hoops_HAS,_hoops_SSAHI); } */
/* _hoops_SSHGI _hoops_SRPC _hoops_GGPHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_RCGHI _hoops_HAS) { _hoops_IHAHI(_hoops_SPHAI,_hoops_HAS,_hoops_SSAHI); } */
/* _hoops_SSHGI _hoops_SRPC _hoops_RGPHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_RCGHI _hoops_HAS) { _hoops_CHAHI(_hoops_SPHAI,_hoops_HAS,_hoops_SSAHI); } */
/* _hoops_SSHGI _hoops_SCSH _hoops_AGPHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_SGRHI _hoops_HAS) { _hoops_ASRC _hoops_RCAHI(_hoops_SPHAI,_hoops_HAS,_hoops_SSAHI);} */
/* _hoops_SSHGI _hoops_SRPC _hoops_PGPHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_SGRHI _hoops_HAS) { _hoops_ACAHI(_hoops_SPHAI,_hoops_HAS,_hoops_SSAHI); } */
/* _hoops_SSHGI _hoops_SRPC _hoops_HGPHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_SGRHI _hoops_HAS) { _hoops_PCAHI(_hoops_SPHAI,_hoops_HAS,_hoops_SSAHI); } */
#define _hoops_IGPHI(m,i)	  (_hoops_AIAHI((m),(i),_hoops_ICRHI))
#define _hoops_CGPHI(m,i)	  (_hoops_PIAHI((m),(i),_hoops_ICRHI))
#define _hoops_SGPHI(m,i)  (_hoops_HIAHI((m),(i),_hoops_ICRHI))
#define _hoops_GRPHI(m,i)		  (_hoops_SCAHI((m),(i),_hoops_ICRHI))
#define _hoops_RRPHI(m,i)	  (_hoops_GSAHI((m),(i),_hoops_ICRHI))
#define _hoops_ARPHI(m,i)	  (_hoops_RSAHI((m),(i),_hoops_ICRHI))

/* 
 * _hoops_RHAHI _hoops_IH _hoops_RHSGH _hoops_IRCCP _hoops_PPR _hoops_HPGGR _hoops_SIH 
 */
/* _hoops_SSHGI _hoops_SCSH _hoops_PRPHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_RCGHI _hoops_HAS, _hoops_SCSH _hoops_IRCCP) { _hoops_ASRC _hoops_AHAHI (_hoops_SPHAI, _hoops_HAS)->_hoops_HRPHI & _hoops_IRCCP; } */
/* _hoops_SSHGI _hoops_SRPC _hoops_IRPHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_RCGHI _hoops_HAS, _hoops_SCSH _hoops_IRCCP) { _hoops_AHAHI (_hoops_SPHAI, _hoops_HAS)->_hoops_HRPHI |= _hoops_IRCCP; } */
/* _hoops_SSHGI _hoops_SRPC _hoops_CRPHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_RCGHI _hoops_HAS, _hoops_SCSH _hoops_IRCCP) { _hoops_AHAHI (_hoops_SPHAI, _hoops_HAS)->_hoops_HRPHI &= ~_hoops_IRCCP;} */
/* _hoops_SSHGI _hoops_APPC _hoops_GSPR _hoops_SRPHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_RCGHI _hoops_HAS) { _hoops_ASRC _hoops_AHAHI (_hoops_SPHAI, _hoops_HAS)->_hoops_GAPHI; } */
/* _hoops_SSHGI _hoops_SRPC _hoops_RAPHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_RCGHI _hoops_HAS, _hoops_APPC _hoops_GSPR _hoops_GSGGR) { _hoops_AHAHI (_hoops_SPHAI, _hoops_HAS)->_hoops_GAPHI=_hoops_GSGGR; } */
#define _hoops_AAPHI(m,i,t)	 (_hoops_RIAHI ((m), (i))->_hoops_CPRHI & (t))
#define _hoops_PAPHI(m,i,t)	 (_hoops_RIAHI ((m), (i))->_hoops_CPRHI |= (t))
#define _hoops_HAPHI(m,i,t)	 (_hoops_RIAHI ((m), (i))->_hoops_CPRHI &= ~(t))
#define _hoops_IAPHI(m,i)	 (_hoops_RIAHI ((m), (i))->_hoops_IPRHI)
#define _hoops_CAPHI(m,i,c)		(_hoops_RIAHI ((m), (i))->_hoops_IPRHI=(c))

/* _hoops_SSHGI _hoops_SCSH _hoops_SAPHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_SGRHI _hoops_HAS, _hoops_SCSH _hoops_IRCCP) { _hoops_ASRC _hoops_SIAHI (_hoops_SPHAI, _hoops_HAS)->_hoops_HRPHI & _hoops_IRCCP; } */
/* _hoops_SSHGI _hoops_SRPC _hoops_GPPHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_SGRHI _hoops_HAS, _hoops_SCSH _hoops_IRCCP) { _hoops_SIAHI (_hoops_SPHAI, _hoops_HAS)->_hoops_HRPHI |= _hoops_IRCCP; } */
/* _hoops_SSHGI _hoops_SRPC _hoops_RPPHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_SGRHI _hoops_HAS, _hoops_SCSH _hoops_IRCCP) { _hoops_SIAHI (_hoops_SPHAI, _hoops_HAS)->_hoops_HRPHI &= ~_hoops_IRCCP;} */
/* _hoops_SSHGI _hoops_APPC _hoops_GSPR _hoops_APPHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_SGRHI _hoops_HAS) { _hoops_ASRC _hoops_SIAHI (_hoops_SPHAI, _hoops_HAS)->_hoops_GAPHI; } */
/* _hoops_SSHGI _hoops_SRPC _hoops_APPHI (_hoops_HSGHI *_hoops_SPHAI, _hoops_SGRHI _hoops_HAS, _hoops_APPC _hoops_GSPR _hoops_GSGGR) { _hoops_SIAHI (_hoops_SPHAI, _hoops_HAS)->_hoops_GAPHI = _hoops_GSGGR; } */
#define _hoops_PPPHI(m,i,t)  (_hoops_CCAHI ((m), (i))->_hoops_CPRHI & (t))
#define _hoops_HPPHI(m,i,t)	   (_hoops_CCAHI ((m), (i))->_hoops_CPRHI |= (t))
#define _hoops_IPPHI(m,i,t)  (_hoops_CCAHI ((m), i)->_hoops_CPRHI &= ~(t))
#define _hoops_CPPHI(m,i)	   (_hoops_CCAHI ((m), (i))->_hoops_IPRHI)
#define _hoops_SPPHI(m,i,c)	   (_hoops_CCAHI ((m), (i))->_hoops_IPRHI = (c))


/*
 *	_hoops_RHCP _hoops_GHPHI
 */

extern _hoops_SHGHI _hoops_RHPHI	(_hoops_GRAHI *m, double, double, double);
extern _hoops_GIGHI	  _hoops_AHPHI		(_hoops_GRAHI *m, int, int, int);



/* _hoops_SSHGI _hoops_SCSH _hoops_PHPHI(_hoops_HSGHI *_hoops_SPHAI) { _hoops_ASRC  (_hoops_SPHAI->_hoops_HHPHI & _hoops_SPHAI->_hoops_IHPHI); } */
/* _hoops_SSHGI _hoops_SCSH _hoops_CHPHI(_hoops_HSGHI *_hoops_SPHAI) { _hoops_ASRC  (_hoops_SPHAI->_hoops_SHPHI & (_hoops_SPHAI->_hoops_IHPHI >> 2)); } */
/* _hoops_SSHGI _hoops_SCSH _hoops_GIPHI(_hoops_HSGHI *_hoops_SPHAI) { _hoops_ASRC	 (_hoops_SPHAI->_hoops_RIPHI & (_hoops_SPHAI->_hoops_IHPHI >> 4)); } */
#define _hoops_AIPHI(m)  (((m)->_hoops_CGAHI & (m)->_hoops_HGAHI))
#define _hoops_PIPHI(m)  (((m)->_hoops_IGAHI & ((m)->_hoops_HGAHI >> 2)))
#define _hoops_HIPHI(m)	 (((m)->_hoops_SGAHI & ((m)->_hoops_HGAHI >> 4)))

extern const char *_hoops_IIPHI (_hoops_GRAHI *m, int);

extern int	 _hoops_CIPHI	(_hoops_GRAHI *m, _hoops_GIGHI, double *, _hoops_CGSPI _hoops_SIPHI);
extern double _hoops_GCPHI		 (_hoops_GRAHI *m, _hoops_GIGHI);

extern double _hoops_RCPHI (_hoops_GRAHI *m, _hoops_GIGHI, int);


/*
 *	_hoops_ACPHI _hoops_HGAGA _hoops_PPR _hoops_GHPHI, _hoops_GPHA _hoops_GSSR _hoops_IISRR
 */
extern void _hoops_PCPHI (_hoops_GRAHI *m, _hoops_SHGHI, _hoops_SHGHI, _hoops_CGRHI *);
extern void _hoops_HCPHI (_hoops_GRAHI *m, _hoops_SHGHI v, _hoops_GRRHI *_hoops_ICPHI);

/* _hoops_CCPHI _hoops_ARRHI *_hoops_APIHR (_hoops_HSGHI *_hoops_SPHAI, _hoops_RCGHI _hoops_HPPC); */
#define neighbors(m,v) ((_hoops_CGRHI *) _hoops_GRGHI (&((m)->_hoops_PGAHI), (v)))



/*
 * _hoops_SCPHI _hoops_PPR _hoops_IPPAR _hoops_PGPP
 */
extern void _hoops_GSPHI (_hoops_GRAHI *, _hoops_CGRHI *);

/* _hoops_RSPHI _hoops_ASPHI _hoops_CCHGR*/
extern void _hoops_PSPHI (_hoops_GRAHI *, _hoops_SHGHI, _hoops_SHGHI, _hoops_SHRHI *);
extern void _hoops_HSPHI (_hoops_GRAHI *, _hoops_SHRHI *);




/************************************************************************

  _hoops_CHARH _hoops_ISPHI _hoops_GRP _hoops_CSPHI _hoops_RIHH _hoops_RRPIP

  _hoops_GICPI (_hoops_IHRPR) 1998 _hoops_RICPI _hoops_AICPI.  _hoops_AIHH "_hoops_PICPI._hoops_HICPI" _hoops_IH _hoops_RCAHR.
  
 ************************************************************************/

typedef struct  {
	_hoops_ARGHI h;
	_hoops_SIGHI e;
	double _hoops_SSPHI[3];
} _hoops_GGHHI;

extern void _hoops_RGHHI (_hoops_GGHHI *_hoops_AGHHI);


typedef _hoops_SCSPI _hoops_PGHHI;	/* _hoops_SPPPI _hoops_GPRR _hoops_HGHHI* */

/* _hoops_SSHGI _hoops_HGHHI *_hoops_IGHHI (_hoops_CGHHI *_hoops_SGHHI, _hoops_SCSH _hoops_HAS) { _hoops_ASRC (_hoops_HGHHI *) _hoops_GRHHI (_hoops_SGHHI, _hoops_HAS); } */
/* _hoops_SSHGI _hoops_SCSH _hoops_RRHHI (_hoops_CGHHI *_hoops_SGHHI, _hoops_HGHHI *_hoops_ARHHI) { _hoops_ASRC _hoops_PRHHI (_hoops_SGHHI, _hoops_ARHHI); } */
#define _hoops_HRHHI(_hoops_IHHIR,i)  ((_hoops_GGHHI *) _hoops_GRGHI (_hoops_IHHIR, i))
#define _hoops_IRHHI(_hoops_IHHIR,q)  (_hoops_SSSPI (_hoops_IHHIR, q))

extern _hoops_CGSPI _hoops_CRHHI (_hoops_PGHHI *_hoops_IHHIR, const _hoops_GGHHI *t, int *index);


typedef struct  {
	/* _hoops_IS _hoops_SHH _hoops_RIRRR _hoops_HII _hoops_SRHHI _hoops_HPGR _hoops_CISPP */
	double _hoops_IPPHA;
	double _hoops_CPPHA;
	double _hoops_SPPHA;
	double _hoops_GAHHI;
	int _hoops_PPPHA;
	int _hoops_HPPHA;
	int _hoops_GHPHA;
	int _hoops_RHPHA;

	_hoops_PGHHI _hoops_RAHHI;
	_hoops_SCSPI _hoops_AAHHI; /* _hoops_PAHGA _hoops_GPRR _hoops_CGHHI, _hoops_GPHHR _hoops_IS _hoops_IAGH _hoops_IIGR _hoops_PAHHI */
	_hoops_SCSPI _hoops_HAHHI; /* _hoops_PAHGA _hoops_GPRR _hoops_IAHHI */
	_hoops_IPGHI heap;
	_hoops_GRAHI *m;
	_hoops_PGSPI *_hoops_CAHHI;
	void (*_hoops_SAHHI)(const _hoops_SHRHI *, double);
	int _hoops_GPHHI;
	int _hoops_RPHHI;
} _hoops_APHHI;

extern void	  _hoops_PPHHI (_hoops_APHHI *, _hoops_GRAHI *, _hoops_SAPHA *);
extern void	  _hoops_HPHHI (_hoops_APHHI *);

extern _hoops_CGSPI _hoops_IPHHI (_hoops_APHHI *, int);
extern void	  _hoops_CPHHI (_hoops_APHHI *, _hoops_SHRHI *);

extern void _hoops_SPHHI (_hoops_APHHI *, const _hoops_SHRHI *);
extern void _hoops_GHHHI (_hoops_APHHI *, const _hoops_SHRHI *);

/* _hoops_SSHGI _hoops_IAHHI *_hoops_RHHHI (_hoops_AHHHI *_hoops_ARHHI, _hoops_SCSH _hoops_HAS) { _hoops_ASRC (_hoops_IAHHI *) _hoops_GRHHI	 (&(_hoops_ARHHI->_hoops_PHHHI), _hoops_HAS); } */
/* _hoops_SSHGI _hoops_CGHHI *_hoops_HHHHI (_hoops_AHHHI *_hoops_ARHHI, _hoops_SCSH _hoops_HAS) {	_hoops_ASRC (_hoops_CGHHI *) _hoops_GRHHI	 (&(_hoops_ARHHI->_hoops_IHHHI), _hoops_HAS); } */
/* _hoops_SSHGI _hoops_SCSH _hoops_ASHS (_hoops_AHHHI *_hoops_ARHHI) { _hoops_ASRC _hoops_PHGHI (&(_hoops_ARHHI->_hoops_SIHPA)); } */
#define _hoops_CHHHI(q,i)  ((_hoops_SHHHI *) _hoops_GRGHI	 (&((q)->_hoops_HAHHI), (i)))
#define _hoops_GIHHI(q,i)	((_hoops_PGHHI *) _hoops_GRGHI  (&((q)->_hoops_AAHHI), (i)))
/* #_hoops_PPIP _hoops_ASHS(_hoops_ARHHI)  (_hoops_PHGHI (&((_hoops_ARHHI)->_hoops_SIHPA))) */



/************************************************************************

  3D _hoops_RIHHI _hoops_SASRR _hoops_AIHHI

  _hoops_GICPI (_hoops_IHRPR) 1998 _hoops_RICPI _hoops_AICPI.  _hoops_AIHH "_hoops_PICPI._hoops_HICPI" _hoops_IH _hoops_RCAHR.
  
 ************************************************************************/

typedef struct _hoops_PIHHI {
	double a2, _hoops_HASSR, _hoops_IASSR, _hoops_GPSSR;
	double	   _hoops_CHHI, _hoops_CASSR, _hoops_HIHHI;
	double		   _hoops_PIGCR, _hoops_GSHIR;
	double			   _hoops_RIGCR;

	double r;
} _hoops_SHHHI;

/* _hoops_CISPP */
void _hoops_IIHHI (_hoops_SHHHI *, double a, double b, double c, double d, double area);
void _hoops_CIHHI (_hoops_SHHHI *, const _hoops_PGSPI *Q, double area); 

/* _hoops_SIHHI _hoops_IGPI */
extern void _hoops_GCHHI (_hoops_SHHHI *, const _hoops_SHHHI *Q);
extern void _hoops_RCHHI (_hoops_SHHHI *, const _hoops_SHHHI *, const _hoops_SHHHI *);
extern void _hoops_ACHHI (_hoops_SHHHI *, const _hoops_SHHHI *, const _hoops_SHHHI *);
extern void _hoops_PCHHI (_hoops_SHHHI *, const _hoops_SHHHI *, const double);
extern void _hoops_HCHHI (_hoops_SHHHI *, double s); /* _hoops_PHHSR _hoops_GGR _hoops_HGHC */
extern void _hoops_ICHHI (_hoops_SHHHI *q);
extern void _hoops_CCHHI (_hoops_SHHHI *, const _hoops_SHHHI *, const _hoops_PGSPI *);
/*_hoops_SSHGI _hoops_SRPC _hoops_SCHHI (_hoops_IAHHI *_hoops_ARHHI, _hoops_GHGPR _hoops_IRS) { _hoops_ARHHI->_hoops_PCCIR=_hoops_IRS; }*/
#define _hoops_GSHHI(q,a) { (q)->r=(a); }

/* _hoops_ACAPA _hoops_IGPI */
extern double _hoops_RSHHI (const _hoops_SHHHI *); 
extern double _hoops_ASHHI (const _hoops_SHHHI *);

/* _hoops_SCAHH _hoops_PPR _hoops_CHCRA */
extern _hoops_CGSPI _hoops_PSHHI	 (const _hoops_SHHHI *, _hoops_RGSPI *v); 
extern _hoops_CGSPI _hoops_HSHHI (const _hoops_SHHHI *, double *x, double *y, double *z); 
extern _hoops_CGSPI _hoops_ISHHI (const _hoops_SHHHI *, _hoops_RGSPI *v, const _hoops_RGSPI *_hoops_ISPI, const _hoops_RGSPI *_hoops_CSPI); 
extern _hoops_CGSPI _hoops_CSHHI (const _hoops_SHHHI *, _hoops_RGSPI *v, const _hoops_RGSPI *_hoops_ISPI, const _hoops_RGSPI *_hoops_CSPI, const _hoops_RGSPI *_hoops_SSPI);
extern double _hoops_SSHHI (const _hoops_SHHHI *, double x, double y, double z);
extern double _hoops_GGIHI (const _hoops_SHHHI *q, const double *v);





void _hoops_IIHHI (_hoops_SHHHI *q, double a, double b, double c, double d, double area) {
	q->a2 = a*a;  q->_hoops_HASSR = a*b;	q->_hoops_IASSR = a*c;  q->_hoops_GPSSR = a*d;
				  q->_hoops_CHHI = b*b;	q->_hoops_CASSR = b*c;  q->_hoops_HIHHI = b*d;
								q->_hoops_PIGCR = c*c;  q->_hoops_GSHIR = c*d;
											  q->_hoops_RIGCR = d*d;

	q->r = area;

	ASSERT(! (_hoops_SSHHI (q, 0, 0, 0) < 0));
	ASSERT(! (_hoops_SSHHI (q, 0, 0, 0) < 0));
} /* _hoops_RSGR _hoops_API _hoops_RGIHI */


void _hoops_CIHHI (_hoops_SHHHI *q, const _hoops_PGSPI *_hoops_AGIHI, double area) {
	q->a2 = _hoops_AGIHI->row[0]._hoops_GGSPI[0];  
	q->_hoops_HASSR = _hoops_AGIHI->row[0]._hoops_GGSPI[1];  
	q->_hoops_IASSR = _hoops_AGIHI->row[0]._hoops_GGSPI[2];  
	q->_hoops_GPSSR = _hoops_AGIHI->row[0]._hoops_GGSPI[3];

	q->_hoops_CHHI = _hoops_AGIHI->row[1]._hoops_GGSPI[1];  
	q->_hoops_CASSR = _hoops_AGIHI->row[1]._hoops_GGSPI[2];  
	q->_hoops_HIHHI = _hoops_AGIHI->row[1]._hoops_GGSPI[3];
	q->_hoops_PIGCR = _hoops_AGIHI->row[2]._hoops_GGSPI[2];  
	q->_hoops_GSHIR = _hoops_AGIHI->row[2]._hoops_GGSPI[3];
	q->_hoops_RIGCR = _hoops_AGIHI->row[3]._hoops_GGSPI[3];

	q->r = area;

	/* _hoops_AGHR (_hoops_PGIHI (_hoops_ARHHI, 0, 0, 0) >= 0); */
}



static void _hoops_HGIHI (_hoops_RGSPI *_hoops_RRSPI, const _hoops_SHHHI *q) { 
		_hoops_RRSPI->_hoops_GGSPI[0] = q->_hoops_GPSSR;
		_hoops_RRSPI->_hoops_GGSPI[1] = q->_hoops_HIHHI;
		_hoops_RRSPI->_hoops_GGSPI[2] = q->_hoops_GSHIR;
}

double _hoops_RSHHI (const _hoops_SHHHI *q) { 
		return q->_hoops_RIGCR; 
}
double _hoops_ASHHI (const _hoops_SHHHI *q) { 
		return q->r; 
}
void _hoops_ICHHI (_hoops_SHHHI *q) { 
		q->a2=q->_hoops_HASSR=q->_hoops_IASSR=q->_hoops_GPSSR=q->_hoops_CHHI=q->_hoops_CASSR=q->_hoops_HIHHI=q->_hoops_PIGCR=q->_hoops_GSHIR=q->_hoops_RIGCR=q->r=0.0; 
}



static void _hoops_IGIHI (const _hoops_SHHHI *q, _hoops_HGSPI *m) {
		m->row[0]._hoops_GGSPI[0] = q->a2;
		m->row[0]._hoops_GGSPI[1] = q->_hoops_HASSR;
		m->row[0]._hoops_GGSPI[2] = q->_hoops_IASSR;
		m->row[1]._hoops_GGSPI[0] = q->_hoops_HASSR;
		m->row[1]._hoops_GGSPI[1] = q->_hoops_CHHI;
		m->row[1]._hoops_GGSPI[2] = q->_hoops_CASSR;
		m->row[2]._hoops_GGSPI[0] = q->_hoops_IASSR;
		m->row[2]._hoops_GGSPI[1] = q->_hoops_CASSR;
		m->row[2]._hoops_GGSPI[2] = q->_hoops_PIGCR;
		/* _hoops_CGIHI: _hoops_HGASR: _hoops_HRGR _hoops_SCH _hoops_IHRI _hoops_IS _hoops_SHSP _hoops_RH _hoops_PRPC _hoops_ARIP _hoops_IIGR _hoops_RH _hoops_RSGA _hoops_CISPH? */
}

static void _hoops_SGIHI (_hoops_PGSPI *m, const _hoops_SHHHI *q) {
		m->row[0]._hoops_GGSPI[0] = q->a2;
		m->row[0]._hoops_GGSPI[1] = q->_hoops_HASSR;
		m->row[0]._hoops_GGSPI[2] = q->_hoops_IASSR;
		m->row[0]._hoops_GGSPI[3] = q->_hoops_HASSR;
		m->row[1]._hoops_GGSPI[0] = q->_hoops_HASSR;
		m->row[1]._hoops_GGSPI[1] = q->_hoops_CHHI;
		m->row[1]._hoops_GGSPI[2] = q->_hoops_CASSR;
		m->row[1]._hoops_GGSPI[3] = q->_hoops_HIHHI;
		m->row[2]._hoops_GGSPI[0] = q->_hoops_IASSR;
		m->row[2]._hoops_GGSPI[1] = q->_hoops_CASSR;
		m->row[2]._hoops_GGSPI[2] = q->_hoops_PIGCR;
		m->row[2]._hoops_GGSPI[3] = q->_hoops_GSHIR;
		m->row[3]._hoops_GGSPI[0] = q->_hoops_GPSSR;
		m->row[3]._hoops_GGSPI[1] = q->_hoops_HIHHI;
		m->row[3]._hoops_GGSPI[2] = q->_hoops_GSHIR;
		m->row[3]._hoops_GGSPI[3] = q->_hoops_RIGCR;
}

#if 0
static void _hoops_GRIHI (_hoops_SHHHI *q, const double *v) {
	q->a2 = v[0];  q->_hoops_HASSR = v[1];  q->_hoops_IASSR = v[2];	 q->_hoops_GPSSR = v[3];
				   q->_hoops_CHHI = v[4];  q->_hoops_CASSR = v[5];	 q->_hoops_HIHHI = v[6];
										  q->_hoops_PIGCR = v[7];	 q->_hoops_GSHIR = v[8];
												 q->_hoops_RIGCR = v[9];

	/* _hoops_AGHR (_hoops_PGIHI (_hoops_ARHHI, 0, 0, 0) >= 0); */
}
#endif

void _hoops_GCHHI (_hoops_SHHHI *_hoops_PCAP, const _hoops_SHHHI *src) {
	_hoops_PCAP->r = src->r;

	_hoops_PCAP->a2 = src->a2;	 _hoops_PCAP->_hoops_HASSR = src->_hoops_HASSR;  _hoops_PCAP->_hoops_IASSR = src->_hoops_IASSR;  _hoops_PCAP->_hoops_GPSSR = src->_hoops_GPSSR;
						 _hoops_PCAP->_hoops_CHHI = src->_hoops_CHHI;  _hoops_PCAP->_hoops_CASSR = src->_hoops_CASSR;  _hoops_PCAP->_hoops_HIHHI = src->_hoops_HIHHI;
															  _hoops_PCAP->_hoops_PIGCR = src->_hoops_PIGCR;  _hoops_PCAP->_hoops_GSHIR = src->_hoops_GSHIR;
																   _hoops_PCAP->_hoops_RIGCR = src->_hoops_RIGCR;
}

void _hoops_RCHHI (_hoops_SHHHI *_hoops_RRIHI, const _hoops_SHHHI *_hoops_AICIH, const _hoops_SHHHI *_hoops_ARIHI) {
	/* _hoops_GAGP _hoops_CCAC*/
	_hoops_RRIHI->r  = _hoops_AICIH->r + _hoops_ARIHI->r;

	/* _hoops_GAGP _hoops_AIAHR*/
	_hoops_RRIHI->a2 = _hoops_AICIH->a2 + _hoops_ARIHI->a2;
	_hoops_RRIHI->_hoops_HASSR = _hoops_AICIH->_hoops_HASSR + _hoops_ARIHI->_hoops_HASSR;
	_hoops_RRIHI->_hoops_IASSR = _hoops_AICIH->_hoops_IASSR + _hoops_ARIHI->_hoops_IASSR;  
	_hoops_RRIHI->_hoops_GPSSR = _hoops_AICIH->_hoops_GPSSR + _hoops_ARIHI->_hoops_GPSSR;

	_hoops_RRIHI->_hoops_CHHI = _hoops_AICIH->_hoops_CHHI + _hoops_ARIHI->_hoops_CHHI;  
	_hoops_RRIHI->_hoops_CASSR = _hoops_AICIH->_hoops_CASSR + _hoops_ARIHI->_hoops_CASSR;  
	_hoops_RRIHI->_hoops_HIHHI = _hoops_AICIH->_hoops_HIHHI + _hoops_ARIHI->_hoops_HIHHI;

	_hoops_RRIHI->_hoops_PIGCR = _hoops_AICIH->_hoops_PIGCR + _hoops_ARIHI->_hoops_PIGCR;  
	_hoops_RRIHI->_hoops_GSHIR = _hoops_AICIH->_hoops_GSHIR + _hoops_ARIHI->_hoops_GSHIR;

	_hoops_RRIHI->_hoops_RIGCR = _hoops_AICIH->_hoops_RIGCR + _hoops_ARIHI->_hoops_RIGCR;

	/* _hoops_AGHR (_hoops_PGIHI (_hoops_PRIHI, 0, 0, 0) >= 0); */
}

void _hoops_ACHHI (_hoops_SHHHI *_hoops_RRIHI, const _hoops_SHHHI *_hoops_AICIH, const _hoops_SHHHI *_hoops_ARIHI) {
	/* _hoops_GAGP _hoops_CCAC*/
	_hoops_RRIHI->r  = _hoops_AICIH->r - _hoops_ARIHI->r;

	/* _hoops_GAGP _hoops_AIAHR*/
	_hoops_RRIHI->a2 = _hoops_AICIH->a2 - _hoops_ARIHI->a2;
	_hoops_RRIHI->_hoops_HASSR = _hoops_AICIH->_hoops_HASSR - _hoops_ARIHI->_hoops_HASSR;
	_hoops_RRIHI->_hoops_IASSR = _hoops_AICIH->_hoops_IASSR - _hoops_ARIHI->_hoops_IASSR;  
	_hoops_RRIHI->_hoops_GPSSR = _hoops_AICIH->_hoops_GPSSR - _hoops_ARIHI->_hoops_GPSSR;

	_hoops_RRIHI->_hoops_CHHI = _hoops_AICIH->_hoops_CHHI - _hoops_ARIHI->_hoops_CHHI;  
	_hoops_RRIHI->_hoops_CASSR = _hoops_AICIH->_hoops_CASSR - _hoops_ARIHI->_hoops_CASSR;  
	_hoops_RRIHI->_hoops_HIHHI = _hoops_AICIH->_hoops_HIHHI - _hoops_ARIHI->_hoops_HIHHI;

	_hoops_RRIHI->_hoops_PIGCR = _hoops_AICIH->_hoops_PIGCR - _hoops_ARIHI->_hoops_PIGCR;  
	_hoops_RRIHI->_hoops_GSHIR = _hoops_AICIH->_hoops_GSHIR - _hoops_ARIHI->_hoops_GSHIR;

	_hoops_RRIHI->_hoops_RIGCR = _hoops_AICIH->_hoops_RIGCR - _hoops_ARIHI->_hoops_RIGCR;

	/* _hoops_AGHR (_hoops_PGIHI (_hoops_PRIHI, 0, 0, 0) >= 0); */
}


void _hoops_HCHHI (_hoops_SHHHI *q, double s) {
	q->a2 *= s;	 q->_hoops_HASSR *= s;  q->_hoops_IASSR *= s;  q->_hoops_GPSSR *= s;
				 q->_hoops_CHHI *= s;  q->_hoops_CASSR *= s;  q->_hoops_HIHHI *= s;
							  q->_hoops_PIGCR *= s;  q->_hoops_GSHIR *= s;
															   q->_hoops_RIGCR *= s;
	/* _hoops_AGHR (_hoops_PGIHI (_hoops_ARHHI, 0, 0, 0) >= 0); */
}

void _hoops_CCHHI (_hoops_SHHHI *_hoops_RRIHI, const _hoops_SHHHI *_hoops_HRIHI, const _hoops_PGSPI *mat) {
		_hoops_PGSPI _hoops_AGIHI, _hoops_IRIHI, temp;

	_hoops_SGIHI (&_hoops_AGIHI, _hoops_HRIHI);
	_hoops_PRSPI (&_hoops_IRIHI, mat);

	/* _hoops_SSSA:	 _hoops_CRIHI(_hoops_SRIHI) * _hoops_GAIHI * _hoops_SRIHI*/
	/* _hoops_GIGHR: _hoops_SRIHI _hoops_HRGR _hoops_CCGRH _hoops_CR _hoops_GAIHI _hoops_HRGR _hoops_CCGRH*/
		_hoops_HRSPI (&temp, &_hoops_IRIHI, &_hoops_AGIHI);
		_hoops_HRSPI (&_hoops_AGIHI, &temp, &_hoops_IRIHI);

	/* _hoops_CGIHI: ??_hoops_HGASR: _hoops_SHHH _hoops_SR _hoops_SHH _hoops_SCACP _hoops_RH _hoops_CCAC??*/
	_hoops_CIHHI (_hoops_RRIHI, &_hoops_AGIHI, _hoops_HRIHI->r);

	/* _hoops_AGHR (_hoops_PGIHI (_hoops_PRIHI, 0, 0, 0) >= 0); */
}


double _hoops_SSHHI (const _hoops_SHHHI *q, double x, double y, double z) {
	/* _hoops_GCRIA _hoops_RAIHI + 2b_hoops_HPPC + _hoops_GSGGR*/

	double _hoops_HPIS = 
		   x*x*(q->a2) + 2*x*y*(q->_hoops_HASSR) + 2*x*z*(q->_hoops_IASSR) + 2*x*(q->_hoops_GPSSR)
						   + y*y*(q->_hoops_CHHI)   + 2*y*z*(q->_hoops_CASSR) + 2*y*(q->_hoops_HIHHI)
										   + z*z*(q->_hoops_PIGCR)   + 2*z*(q->_hoops_GSHIR)
														   + (q->_hoops_RIGCR);
	/* _hoops_AGHR (_hoops_AAIHI >= 0); */
	return _hoops_HPIS;
}

double _hoops_GGIHI (const _hoops_SHHHI *q, const double *v) {
		return _hoops_SSHHI (q, v[X], v[Y], v[_hoops_GACPA]);
}

_hoops_CGSPI _hoops_PSHHI (const _hoops_SHHHI *q, _hoops_RGSPI *v) {
	_hoops_HGSPI _hoops_PAIHI, _hoops_HAIHI;
		double _hoops_HHIPA;
		_hoops_RGSPI _hoops_IAIHI;

		_hoops_IGIHI (q, &_hoops_HAIHI);
	_hoops_HHIPA = _hoops_SGSPI (&_hoops_PAIHI, &_hoops_HAIHI);
	if (_hoops_HSCIA(_hoops_HHIPA, 0.0, 1e-12f))
				return 0;

		_hoops_HGIHI (&_hoops_IAIHI, q);
		_hoops_ARSPI (v, &_hoops_PAIHI, &_hoops_IAIHI);
		_hoops_AASPI (v->_hoops_GGSPI, v->_hoops_GGSPI, 3);


	/* _hoops_AGHR (_hoops_CAIHI (_hoops_ARHHI, _hoops_HPPC->_hoops_SAIHI) >= 0); */
	return 1;
}

_hoops_CGSPI _hoops_HSHHI (const _hoops_SHHHI *q, double *x, double *y, double *z) {
	_hoops_RGSPI v;
	_hoops_CGSPI _hoops_IA = _hoops_PSHHI (q, &v);

	if (_hoops_IA)
	{
				*x = (double)v._hoops_GGSPI[X];
				*y = (double)v._hoops_GGSPI[Y];
				*z = (double)v._hoops_GGSPI[_hoops_GACPA];
	}

	/* _hoops_AGHR (_hoops_CAIHI (_hoops_ARHHI, _hoops_HPPC._hoops_SAIHI) >= 0); */
	return _hoops_IA;
}

_hoops_CGSPI _hoops_ISHHI (const _hoops_SHHHI *q, _hoops_RGSPI *v, const _hoops_RGSPI *_hoops_ISPI, const _hoops_RGSPI *_hoops_CSPI) {
	_hoops_RGSPI _hoops_GPIHI, _hoops_RPIHI, d;
	_hoops_HGSPI _hoops_APIHI;
		double _hoops_SSHGA;
		double a, f1, f2, _hoops_CGHGR, _hoops_SGHGR;
		_hoops_RGSPI _hoops_IAIHI;
		_hoops_RGSPI temp;

	_hoops_SRSPI (d._hoops_GGSPI, _hoops_ISPI->_hoops_GGSPI, _hoops_CSPI->_hoops_GGSPI, 3);
		_hoops_IGIHI (q, &_hoops_APIHI);
		_hoops_ARSPI (&_hoops_GPIHI, &_hoops_APIHI, _hoops_CSPI);
	_hoops_ARSPI (&_hoops_RPIHI, &_hoops_APIHI, &d);

	_hoops_SSHGA = 2* (_hoops_IASPI (d._hoops_GGSPI, _hoops_RPIHI._hoops_GGSPI, 3));
	if (_hoops_HSCIA(_hoops_SSHGA, 0.0, 1e-12f))
				return 0;

		_hoops_HGIHI (&_hoops_IAIHI, q);
		f1 = _hoops_IASPI (_hoops_IAIHI._hoops_GGSPI, d._hoops_GGSPI, 3);
		f2 = _hoops_IASPI (_hoops_GPIHI._hoops_GGSPI, d._hoops_GGSPI, 3);
		_hoops_CGHGR = _hoops_IASPI (_hoops_CSPI->_hoops_GGSPI, _hoops_RPIHI._hoops_GGSPI, 3);
		_hoops_SGHGR = _hoops_IASPI (_hoops_RPIHI._hoops_GGSPI, d._hoops_GGSPI, 3);
	a =	  (-2*f1 - f2 - _hoops_CGHGR) /  (2*_hoops_SGHGR);

	if (a<0.0) a=0.0; else if (a>1.0) a=1.0;

		_hoops_GASPI (temp._hoops_GGSPI, d._hoops_GGSPI, a, 3);
	_hoops_CRSPI (v->_hoops_GGSPI, temp._hoops_GGSPI, _hoops_CSPI->_hoops_GGSPI, 3);


	/* _hoops_AGHR (_hoops_CAIHI (_hoops_ARHHI, _hoops_HPPC->_hoops_SAIHI) >= 0); */
	return 1;
}


_hoops_CGSPI _hoops_CSHHI (const _hoops_SHHHI *q, _hoops_RGSPI *v, const _hoops_RGSPI *_hoops_ISPI,
						  const _hoops_RGSPI *_hoops_CSPI, const _hoops_RGSPI *_hoops_SSPI) {
		_hoops_HGSPI _hoops_APIHI;
		_hoops_RGSPI _hoops_PPIHI, _hoops_APRSH, _hoops_HPIHI;
		_hoops_RGSPI _hoops_GCHAI, _hoops_CGPCP, _hoops_RCHAI;
		double _hoops_IPIHI, _hoops_CPIHI, _hoops_SPIHI, _hoops_GHIHI, _hoops_RHIHI, _hoops_SSHGA;
		double a, b, f1, f2, _hoops_CGHGR, _hoops_SGHGR;
		_hoops_RGSPI _hoops_AHIHI, _hoops_PHIHI, _hoops_HHIHI;

	_hoops_SRSPI (_hoops_PPIHI._hoops_GGSPI, _hoops_ISPI->_hoops_GGSPI, _hoops_SSPI->_hoops_GGSPI, 3);
	_hoops_SRSPI (_hoops_APRSH._hoops_GGSPI, _hoops_CSPI->_hoops_GGSPI, _hoops_SSPI->_hoops_GGSPI, 3);
	_hoops_IGIHI (q, &_hoops_APIHI);
	_hoops_HGIHI (&_hoops_HPIHI, q);

	_hoops_ARSPI (&_hoops_AHIHI, &_hoops_APIHI, &_hoops_PPIHI);
	_hoops_ARSPI (&_hoops_PHIHI, &_hoops_APIHI, &_hoops_APRSH);
	_hoops_ARSPI (&_hoops_HHIHI, &_hoops_APIHI, _hoops_SSPI);

	_hoops_IPIHI = 
				(_hoops_IASPI (_hoops_PPIHI._hoops_GGSPI, _hoops_PHIHI._hoops_GGSPI, 3)) + 
				(_hoops_IASPI (_hoops_APRSH._hoops_GGSPI, _hoops_AHIHI._hoops_GGSPI, 3));
	_hoops_CPIHI =  (_hoops_IASPI (_hoops_PPIHI._hoops_GGSPI, _hoops_HHIHI._hoops_GGSPI, 3)) +	 (_hoops_IASPI (_hoops_SSPI->_hoops_GGSPI, _hoops_AHIHI._hoops_GGSPI, 3));
	_hoops_SPIHI =  (_hoops_IASPI (_hoops_APRSH._hoops_GGSPI, _hoops_HHIHI._hoops_GGSPI, 3)) +	 (_hoops_IASPI (_hoops_SSPI->_hoops_GGSPI, _hoops_PHIHI._hoops_GGSPI, 3));

	_hoops_GHIHI = _hoops_IASPI (_hoops_APRSH._hoops_GGSPI, _hoops_PHIHI._hoops_GGSPI, 3);
	_hoops_RHIHI = _hoops_IASPI (_hoops_PPIHI._hoops_GGSPI, _hoops_AHIHI._hoops_GGSPI, 3);

	_hoops_SSHGA = _hoops_RHIHI * _hoops_GHIHI - 2 * _hoops_IPIHI;
	if (_hoops_HSCIA(_hoops_SSHGA, 0.0, 1e-12f))
				return 0;

		f1 = _hoops_IASPI (_hoops_HPIHI._hoops_GGSPI, _hoops_PPIHI._hoops_GGSPI, 3);
		f2 = _hoops_IASPI (_hoops_HPIHI._hoops_GGSPI, _hoops_APRSH._hoops_GGSPI, 3);
		_hoops_CGHGR = _hoops_IASPI (_hoops_HPIHI._hoops_GGSPI, _hoops_APRSH._hoops_GGSPI, 3);
		_hoops_SGHGR = _hoops_IASPI (_hoops_HPIHI._hoops_GGSPI, _hoops_PPIHI._hoops_GGSPI, 3);
	a =	 (_hoops_GHIHI*(2*f1 + _hoops_CPIHI) -
				  _hoops_IPIHI*(2*f2 + _hoops_SPIHI)) / -_hoops_SSHGA;

	b =	 (_hoops_RHIHI*(2*_hoops_CGHGR + _hoops_SPIHI) -
				  _hoops_IPIHI*(2*_hoops_SGHGR + _hoops_CPIHI)) / -_hoops_SSHGA;

	if (a<0.0) a=0.0; else if (a>1.0) a=1.0;
	if (b<0.0) b=0.0; else if (b>1.0) b=1.0;

		/*_hoops_HPASR _hoops_GIGR _hoops_RRGR _hoops_IH _hoops_RH _hoops_SPS 4 _hoops_APGR...*/
	/*_hoops_HPPC = _hoops_IRS*_hoops_IHIHI + _hoops_RCSR*_hoops_SACAI + _hoops_SSIHR;*/
		_hoops_GASPI (_hoops_GCHAI._hoops_GGSPI, _hoops_PPIHI._hoops_GGSPI, a, 3);
		_hoops_GASPI (_hoops_CGPCP._hoops_GGSPI, _hoops_APRSH._hoops_GGSPI, b, 3);
		_hoops_CRSPI (_hoops_RCHAI._hoops_GGSPI, _hoops_GCHAI._hoops_GGSPI, _hoops_CGPCP._hoops_GGSPI, 3);
	_hoops_CRSPI (v->_hoops_GGSPI, _hoops_RCHAI._hoops_GGSPI, _hoops_SSPI->_hoops_GGSPI, 3);


	/* _hoops_AGHR (_hoops_CAIHI (_hoops_ARHHI, _hoops_HPPC->_hoops_SAIHI) >= 0); */
	return 1;
}



static int _hoops_SCAAR(int i) { return (i-1)/2; }
static int left(int i) { return 2*i+1; }
static int right(int i) { return 2*i+2; }


/*
 * _hoops_IAIGH _hoops_HICRR _hoops_PSCH _hoops_IH _hoops_GSSPI _hoops_RH _hoops_SIHPA
 */
static void swaph (_hoops_IPGHI *h, int i, int j) {
	_hoops_ARGHI *_hoops_GAIS, *_hoops_CHIHI;

	_hoops_RGGHI (&(h->data), i, j);
	_hoops_GAIS = (_hoops_ARGHI *) _hoops_GRGHI  (&(h->data), i);
	_hoops_CHIHI = (_hoops_ARGHI *) _hoops_GRGHI  (&(h->data), j);
	_hoops_GPGHI (_hoops_GAIS, i);
	_hoops_GPGHI (_hoops_CHIHI, j);
}


static void _hoops_HHPHH (_hoops_IPGHI *h, int i) {
	_hoops_ARGHI *_hoops_HSAHP = (_hoops_ARGHI *) _hoops_GRGHI (&(h->data), i);
	_hoops_ARGHI *tmp;
	int p = _hoops_SCAAR(i);
	ASSERT (i >= 0 && i < _hoops_CGGHI (&(h->data)));

	while (i > 0)
	{
		tmp = (_hoops_ARGHI *) _hoops_GRGHI	(&(h->data), p);
		if (_hoops_APGHI (_hoops_HSAHP) > _hoops_APGHI  (tmp))
		{
			swaph (h, i, p);
			i = p;
			p = _hoops_SCAAR (p);
		}
		else
			break;
	}
}

static void _hoops_IHPHH (_hoops_IPGHI *h, int i) {
	int l = left(i);
	int r = right(i);
	_hoops_ARGHI *_hoops_HSAHP, *hl, *_hoops_IIRHP, *_hoops_PSAHP;
	int _hoops_SHIHI, _hoops_IHPPI;
	ASSERT (i >= 0 && i < _hoops_CGGHI (&(h->data)));

	/* _hoops_SR _hoops_CHR _hoops_RHRIR _hoops_ARI _hoops_IS _hoops_RGHH _hoops_RH _hoops_AGIR _hoops_CAS _hoops_GSSAA _hoops_HRGR _hoops_GGR _hoops_CCIR, _hoops_HIH _hoops_PCCIR _hoops_HRGR _hoops_HAR */
	while (l < _hoops_CGGHI (&(h->data)))
	{
		_hoops_HSAHP = (_hoops_ARGHI *) _hoops_GRGHI  (&(h->data), i);
		hl	   = (_hoops_ARGHI *) _hoops_GRGHI  (&(h->data), l);
		_hoops_IIRHP	   = (_hoops_ARGHI *) _hoops_GRGHI  (&(h->data), r);
		if (
			 (r < _hoops_CGGHI (&(h->data))) && 
			 (_hoops_APGHI (hl) < _hoops_APGHI (_hoops_IIRHP))
	  )
			_hoops_PSAHP = _hoops_IIRHP;
		else 
			_hoops_PSAHP = hl;

		if (_hoops_APGHI (_hoops_HSAHP) < _hoops_APGHI (_hoops_PSAHP))
		{
			_hoops_SHIHI = _hoops_SAGHI (_hoops_HSAHP);
			_hoops_IHPPI = _hoops_SAGHI (_hoops_PSAHP);
			swaph (h, _hoops_SHIHI, _hoops_IHPPI);
			i = _hoops_IHPPI;
			l = left (i);
			r = right (i);
		}
		else
			break;
	}
}

/*
 * _hoops_GIIHI _hoops_CCHGR _hoops_IS _hoops_RH _hoops_SIHPA
 */

void _hoops_CPGHI (_hoops_IPGHI *h) { 
	/* _hoops_HSPC _hoops_RH _hoops_RIS _hoops_IS _hoops_ASH _hoops_IRGHI *'_hoops_GRI */
	_hoops_RSSPI (&(h->data), sizeof (_hoops_ARGHI *)); 
}

void _hoops_SPGHI (_hoops_IPGHI *h) { 
	_hoops_PSSPI (&(h->data)); 
}


void _hoops_CHPHH (_hoops_IPGHI *h, _hoops_ARGHI *t) {
	int i;
#if 0
	double v = _hoops_APGHI (t);
#endif

	i = _hoops_SSSPI (&(h->data), t);
	_hoops_GPGHI (t, i);
	_hoops_HHPHH (h, i);
}

void _hoops_GHGHI (_hoops_IPGHI *h, _hoops_ARGHI *t) {
	int i;
	double v = _hoops_APGHI (t);
	_hoops_ARGHI *tmp;

	i = _hoops_SAGHI (t);
	ASSERT (i >= 0 && i < _hoops_CGGHI (&(h->data)));
	tmp = (_hoops_ARGHI *) _hoops_GRGHI	(&(h->data), _hoops_SCAAR (i));
	if (i > 0 && v > _hoops_APGHI (tmp))
		_hoops_HHPHH (h, i);
	else
		_hoops_IHPHH (h, i);
}

/* _hoops_ASRC _hoops_PPR _hoops_HASIR _hoops_RH _hoops_SCIA _hoops_CARRA _hoops_IIGR _hoops_RH _hoops_SIHPA */
void *_hoops_PIPHH (_hoops_IPGHI *h) {
	_hoops_ARGHI *_hoops_PRGGH;
	int len = _hoops_CGGHI (&(h->data));
	if (len < 1) return NULL;

	swaph (h, 0, len - 1);
	_hoops_PRGGH = (_hoops_ARGHI *) _hoops_GRGHI	 (&(h->data), len-1);
	_hoops_HGGHI (&(h->data));
	_hoops_CAGHI (_hoops_PRGGH);

	_hoops_IHPHH (h, 0);
	return _hoops_PRGGH->_hoops_ASHSA;
}

/* _hoops_HASIR _hoops_IRS _hoops_SAGHR _hoops_CARRA _hoops_IIGR _hoops_RH _hoops_SIHPA */
void _hoops_RHGHI (_hoops_IPGHI *h, _hoops_ARGHI *t) {
	_hoops_ARGHI *temp;
	int i, end;

	if (!_hoops_IAGHI (t)) 
		return;

	i = _hoops_SAGHI (t);
	end = _hoops_CGGHI (&(h->data)) - 1;
	ASSERT (i >= 0 && i <= end);
	_hoops_CAGHI (t);
	if (i!= end)
	{
	swaph (h, i, end);
	_hoops_HGGHI (&(h->data));

	temp = (_hoops_ARGHI *) _hoops_GRGHI	 (&(h->data), i);
	if (_hoops_APGHI (temp) < _hoops_APGHI (t))
		_hoops_IHPHH (h, i);
	else
		_hoops_HHPHH (h, i);
	}
	else
	_hoops_HGGHI (&(h->data)); /* _hoops_HASIR _hoops_CGHI _hoops_CARRA */
}

/* _hoops_ACAPA _hoops_GGR _hoops_HGHC _hoops_SIHH _hoops_RIIHI _hoops_SIHPA.	
 * _hoops_PPRAR _hoops_GGR _hoops_RH _hoops_SPIGA _hoops_RPHRA */
void *_hoops_AHGHI (_hoops_IPGHI *h, int i) {
	_hoops_ARGHI *temp;

	ASSERT (i >= 0 && i < _hoops_CGGHI (&(h->data)));
	temp = (_hoops_ARGHI *) _hoops_GRGHI (&(h->data), i); 
	return temp->_hoops_ASHSA; 
}


/*
 *	_hoops_PSCH _hoops_IH _hoops_PRCA _hoops_GSRSA
 */

void _hoops_RSSPI (_hoops_SCSPI *b, int _hoops_ASSPI) {
	b->allocated = 3; 
	b->used = 0;
	b->_hoops_CCSPI = _hoops_ASSPI;
	ALLOC_ARRAY_ALIGNED (b->data, b->allocated * _hoops_ASSPI, unsigned char, 8);
}

void _hoops_PSSPI (_hoops_SCSPI *b) {
	if (b->data) { 
		FREE_ARRAY_ALIGNED (b->data, b->allocated * b->_hoops_CCSPI, unsigned char, 8);
		b->data = NULL; 
	}
}

void _hoops_HSSPI (_hoops_SCSPI *b) {
	b->used = 0;
}


void _hoops_PGGHI (_hoops_SCSPI *b, int size_in) {
	void *tmp;
	int _hoops_PAGHH = b->allocated * b->_hoops_CCSPI;
	int _hoops_HAGHH = size_in * b->_hoops_CCSPI;

	tmp = b->data;
	ALLOC_ARRAY_ALIGNED (b->data, _hoops_HAGHH, unsigned char, 8);
	COPY_MEMORY (tmp, b->used * b->_hoops_CCSPI, b->data);
	FREE_ARRAY_ALIGNED (tmp, _hoops_PAGHH, unsigned char, 8);
	ASSERT (size_in > b->used);
	b->allocated = size_in;
} /* _hoops_RSGR _hoops_API _hoops_AIIHI */


/* _hoops_PCIAR _hoops_RH _hoops_AHAP _hoops_SSIHH _hoops_IS _hoops_HPP _hoops_PIIHI _hoops_CRGR _hoops_RH _hoops_RPHR _hoops_HGHC */
int _hoops_ISSPI (_hoops_SCSPI *b, const void *_hoops_CSSPI) {
	void *_hoops_HIIHI;
	if (b->used >= b->allocated)
		_hoops_PGGHI (b, b->allocated * 2);
	_hoops_HIIHI = (char *) b->data + (b->used * b->_hoops_CCSPI);
	COPY_MEMORY (_hoops_CSSPI, b->_hoops_CCSPI , _hoops_HIIHI);

	return b->used++;
}

/* _hoops_GAR _hoops_GGR _hoops_IIIHI, _hoops_HIH _hoops_CIIHI _hoops_IH _hoops_GSRSA _hoops_SGS _hoops_ASH _hoops_CICRR, _hoops_HAR _hoops_PCIAR */
int _hoops_SSSPI (_hoops_SCSPI *b, const void *_hoops_CSSPI) {
	ASSERT (b->_hoops_CCSPI == sizeof (void *));
	return _hoops_ISSPI (b, &_hoops_CSSPI);
}


/* _hoops_PCIAR _hoops_RH _hoops_AHAP _hoops_SSIHH _hoops_IS _hoops_HPP _hoops_PIIHI _hoops_CRGR _hoops_RH _hoops_RPHR _hoops_HGHC */
void _hoops_GGGHI (_hoops_SCSPI *b, const void *_hoops_CSSPI, int i) {
	void *_hoops_HIIHI;
	_hoops_HIIHI = (char *) b->data + (i * b->_hoops_CCSPI);
	COPY_MEMORY (_hoops_CSSPI, b->_hoops_CCSPI , _hoops_HIIHI);
}

static void _hoops_SIIHI (_hoops_SCSPI *b, int i, int j, void *_hoops_GCIHI, void *_hoops_RCIHI) {
	void *temp;
	ALLOC_ARRAY (temp, b->_hoops_CCSPI, unsigned char);

	UNREFERENCED(i);
	UNREFERENCED(j);
	ASSERT (i >= 0 && i < b->used);
	ASSERT (j >= 0 && j < b->used);

	COPY_MEMORY (_hoops_GCIHI, b->_hoops_CCSPI, temp);
	COPY_MEMORY (_hoops_RCIHI, b->_hoops_CCSPI, _hoops_GCIHI);
	COPY_MEMORY (temp,	 b->_hoops_CCSPI, _hoops_RCIHI);

	FREE_ARRAY (temp, b->_hoops_CCSPI, unsigned char);
}

void _hoops_RGGHI (_hoops_SCSPI *b, int i, int j) {
	char _hoops_ACIHI[12];
	void *temp = _hoops_ACIHI;
	void *_hoops_GCIHI = (char *) b->data + (i * b->_hoops_CCSPI);
	void *_hoops_RCIHI = (char *) b->data + (j * b->_hoops_CCSPI);

	if (b->_hoops_CCSPI > 12) 
		_hoops_SIIHI (b, i, j, _hoops_GCIHI, _hoops_RCIHI);

	ASSERT (i >= 0 && i < b->used);
	ASSERT (j >= 0 && j < b->used);

	COPY_MEMORY (_hoops_GCIHI, b->_hoops_CCSPI, temp);
	COPY_MEMORY (_hoops_RCIHI, b->_hoops_CCSPI, _hoops_GCIHI);
	COPY_MEMORY (temp,	 b->_hoops_CCSPI, _hoops_RCIHI);
}


void _hoops_HGGHI (_hoops_SCSPI *b) {
		b->used--;
}

void _hoops_AGGHI (_hoops_SCSPI *b, int which) {
		if (which != b->used - 1)
				_hoops_RGGHI (b, which, b->used - 1);
		_hoops_HGGHI (b);
}


/*
 * _hoops_IPCP _hoops_ACSP _hoops_IIGR _hoops_RH _hoops_RGHR _hoops_HRGR _hoops_PSCH _hoops_SGS _hoops_AAPR _hoops_RAARH _hoops_PAPR
 * _hoops_GAR _hoops_SSHGI'_hoops_GRI _hoops_GGR _hoops_GCSPI._hoops_GGHR
 */

void _hoops_HCGHI (_hoops_GCGHI *f, _hoops_SHGHI _hoops_HSPI, _hoops_SHGHI _hoops_ISPI, _hoops_SHGHI _hoops_CSPI) {
		ASSERT (_hoops_HSPI != _hoops_ISPI);
		ASSERT (_hoops_ISPI != _hoops_CSPI);
		ASSERT (_hoops_CSPI != _hoops_HSPI);
		f->v[0] = _hoops_HSPI;
		f->v[1] = _hoops_ISPI;
		f->v[2] = _hoops_CSPI;
}

int _hoops_ICGHI (const _hoops_GCGHI *f, _hoops_SHGHI i) {
		if (f->v[0]==i) return 0;
		else if (f->v[1]==i) return 1;
		else { 
				ASSERT(f->v[2]==i); 
				return 2; 
		}
}

_hoops_SHGHI _hoops_CCGHI (const _hoops_GCGHI *f, _hoops_SHGHI _hoops_HSPI, _hoops_SHGHI _hoops_ISPI) {
		if (f->v[0]!=_hoops_HSPI && f->v[0]!=_hoops_ISPI) return f->v[0];
		else if (f->v[1]!=_hoops_HSPI && f->v[1]!=_hoops_ISPI) return f->v[1];
		else { 
				ASSERT (f->v[2]!=_hoops_HSPI && f->v[2]!=_hoops_ISPI); 
				return f->v[2]; 
		}
}

_hoops_CGSPI _hoops_SCGHI (const _hoops_GCGHI *f, _hoops_SHGHI _hoops_HSPI, _hoops_SHGHI _hoops_ISPI) {
		if (f->v[0]==_hoops_HSPI) return f->v[1]==_hoops_ISPI;
		else if (f->v[1]==_hoops_HSPI) return f->v[2]==_hoops_ISPI;
		else { 
				ASSERT(f->v[2]==_hoops_HSPI); 
				return f->v[0]==_hoops_ISPI; 
		}
}

int _hoops_GSGHI (_hoops_GCGHI *f, _hoops_SHGHI from, _hoops_SHGHI to) {
		int i;
		int _hoops_PCIHI = 0;

		for (i = 0; i < 3; i++)
				if (f->v[i] == from)
				{
						f->v[i] = to;
						_hoops_PCIHI++;
				}
		return _hoops_PCIHI;
}


void _hoops_PGRHI (_hoops_CSGHI *c, double r, double g, double b) {
		c->r = _hoops_RGRHI(r);
		c->g = _hoops_RGRHI(g);
		c->b = _hoops_RGRHI(b);
}

void _hoops_HGRHI (_hoops_GGRHI *t, double u, double v) {
		t->u[0] = u;
		t->u[1] = v;
}

void _hoops_IGRHI (_hoops_SSGHI *n, double x, double y, double z) {
		n->_hoops_CCSAR[0] = x;
		n->_hoops_CCSAR[1] = y;
		n->_hoops_CCSAR[2] = z;
}


_hoops_CGSPI _hoops_AARHI (_hoops_CGRHI *_hoops_PSRGA, _hoops_GIGHI fid, int *index) {
		int i;
		for (i = 0; i < _hoops_CGGHI (_hoops_PSRGA); i++)
				if (_hoops_GARHI (_hoops_PSRGA, i) == fid)
				{
						if (index)
								*index = i;
					return 1;
				}
	return 0;
}

_hoops_CGSPI _hoops_PARHI (_hoops_GRRHI *vl, _hoops_GIGHI _hoops_HACGH, int *index) {
		int i;
		for (i = 0; i < _hoops_CGGHI (vl); i++)
				if (_hoops_RARHI (vl, i) == _hoops_HACGH)
				{
						if (index)
								*index = i;
					return 1;
				}
	return 0;
}


static const _hoops_GHRHI _hoops_HCIHI = { 0, 0, 0, 0 };
static const _hoops_RHRHI	 _hoops_ICIHI = { 0, 0, 0, 0 };



void _hoops_RRAHI (_hoops_GRAHI *m, int _hoops_ARAHI, int _hoops_PRAHI) {
	UNREFERENCED (_hoops_ARAHI);
	UNREFERENCED (_hoops_PRAHI);
	_hoops_RSSPI (&(m->vertices),	  sizeof (_hoops_IIGHI));
	_hoops_RSSPI (&(m->faces),	  sizeof (_hoops_GCGHI));
	_hoops_RSSPI (&(m->_hoops_PGAHI), sizeof (_hoops_CGRHI *));
	_hoops_RSSPI (&(m->_hoops_SSRHI),	  sizeof (_hoops_GHRHI));
	_hoops_RSSPI (&(m->_hoops_RGAHI),	  sizeof (_hoops_RHRHI));
	_hoops_RSSPI (&(m->_hoops_GSRHI),  sizeof (int));
	_hoops_RSSPI (&(m->_hoops_RSRHI),  sizeof (int));
	_hoops_RSSPI (&(m->_hoops_ASRHI), sizeof (int));
	m->colors = NULL;  m->normals = NULL;  m->_hoops_ISRHI = NULL;
	m->_hoops_IGAHI = m->_hoops_CGAHI = m->_hoops_SGAHI = _hoops_HARHI;
	m->_hoops_HGAHI = _hoops_PPRHI;
}

void _hoops_HRAHI (_hoops_GRAHI *m) {
	int i;

	/* _hoops_CASI _hoops_GH _hoops_RH _hoops_HSP _hoops_GPHHR _hoops_RIS */
	for (i = 0; i < _hoops_CGGHI (&(m->_hoops_PGAHI)); i++)  
	{
		_hoops_PSSPI ((_hoops_SCSPI*)_hoops_GRGHI (&(m->_hoops_PGAHI), i));
		FREE (_hoops_GRGHI (&(m->_hoops_PGAHI), i), _hoops_SCSPI);
	}
	_hoops_PSSPI (&(m->_hoops_PGAHI));

	/* _hoops_CASI _hoops_GH _hoops_CPS _hoops_SHS */
	_hoops_PSSPI (&(m->vertices));
	_hoops_PSSPI (&(m->faces));
	_hoops_PSSPI (&(m->_hoops_PGAHI));
	_hoops_PSSPI (&(m->_hoops_SSRHI));
	_hoops_PSSPI (&(m->_hoops_RGAHI));
	_hoops_PSSPI (&(m->_hoops_GSRHI));
	_hoops_PSSPI (&(m->_hoops_RSRHI));
	_hoops_PSSPI (&(m->_hoops_ASRHI));

	if (m->normals) FREE (m->normals, _hoops_SCSPI);
	if (m->colors)	FREE (m->colors,  _hoops_SCSPI);
	if (m->_hoops_ISRHI) FREE (m->_hoops_ISRHI, _hoops_SCSPI);
}


static _hoops_GIGHI _hoops_CCIHI(_hoops_GRAHI *m, _hoops_SHGHI _hoops_ISPI, _hoops_SHGHI _hoops_CSPI, _hoops_SHGHI _hoops_SSPI) {
	_hoops_GCGHI temp;
	_hoops_GIGHI id;

	_hoops_HCGHI (&temp, _hoops_ISPI, _hoops_CSPI, _hoops_SSPI);
	id = _hoops_ISSPI (&(m->faces), &temp);
	_hoops_ISSPI (&(m->_hoops_RGAHI), &_hoops_ICIHI);
	_hoops_RRPHI (m, id);

	return id;
}

static void _hoops_SCIHI(_hoops_GRAHI *m, _hoops_GIGHI id) {
	_hoops_CGRHI *_hoops_GSIHI, *_hoops_RSIHI, *_hoops_ASIHI;

	_hoops_GSIHI = neighbors (m, _hoops_SAAHI (m, id)->v[0]);
	_hoops_RSIHI = neighbors (m, _hoops_SAAHI (m, id)->v[1]);
	_hoops_ASIHI = neighbors (m, _hoops_SAAHI (m, id)->v[2]);
	_hoops_ISSPI (_hoops_GSIHI, &id);
	_hoops_ISSPI (_hoops_RSIHI, &id);
	_hoops_ISSPI (_hoops_ASIHI, &id);
}

static void _hoops_PSIHI (_hoops_GRAHI *m, _hoops_SHGHI _hoops_HACGH, unsigned short _hoops_HPRHI) {
	int i, _hoops_HSIHI;
	_hoops_GIGHI fid;
	ASSERT (_hoops_HACGH < _hoops_HPAHI (m)); 
	_hoops_HSIHI = _hoops_CGGHI (neighbors(m, _hoops_HACGH));

	for (i = 0; i < _hoops_HSIHI; i++)
	{
		fid = _hoops_GARHI (neighbors(m, _hoops_HACGH), i);
		_hoops_PSAHI (m, fid, (unsigned char) _hoops_HPRHI);
	}
}

static void _hoops_ISIHI(_hoops_GRAHI *m, _hoops_SHGHI _hoops_HACGH,_hoops_CGRHI *faces) {
	int i, fid, _hoops_HSIHI;
	ASSERT (_hoops_HACGH < _hoops_HPAHI(m)); 

	_hoops_HSIHI = _hoops_CGGHI (neighbors(m, _hoops_HACGH));
	for (i = 0; i < _hoops_HSIHI; i++)
	{
		fid = _hoops_GARHI (neighbors(m, _hoops_HACGH), i);
		if (!_hoops_ASAHI(m, fid))
		{
			_hoops_ISSPI (faces, &fid);
			_hoops_PSAHI (m, fid, 1);
		}
	}
}


static void _hoops_CSIHI(_hoops_GRAHI *m, _hoops_CGRHI *faces, unsigned short _hoops_HPRHI) {
	int i, j;
	_hoops_GIGHI fid;
	_hoops_SHGHI _hoops_HACGH;

	for (i = 0; i < _hoops_CGGHI (faces); i++)
		for (j = 0; j < 3; j++) 
		{
			fid = _hoops_GARHI (faces, i);
			_hoops_HACGH = _hoops_SAAHI (m, fid)->v[j];
			_hoops_CIAHI(m, _hoops_HACGH, (unsigned char) _hoops_HPRHI);
		}
}

static void _hoops_SSIHI(_hoops_GRAHI *m, _hoops_CGRHI *faces,
					  _hoops_GRRHI *_hoops_ICPHI) {
	int i, j; 
	for (i = 0; i < _hoops_CGGHI (faces); i++)
		for (j = 0; j < 3; j++)
		{
			_hoops_SHGHI v = _hoops_SAAHI (m, _hoops_GARHI (faces, i))->v[j];
			if (!_hoops_IIAHI(m, v))
			{
				_hoops_ISSPI (_hoops_ICPHI, &v);
				_hoops_CIAHI (m, v, 1);
			}
		}
}


void _hoops_PCPHI (_hoops_GRAHI *m, _hoops_SHGHI _hoops_ISPI, _hoops_SHGHI _hoops_CSPI,
					_hoops_CGRHI *faces) {
	_hoops_PSIHI (m, _hoops_ISPI, 1);
	_hoops_PSIHI (m, _hoops_CSPI, 0);
	_hoops_ISIHI (m, _hoops_ISPI, faces);
}


void _hoops_HCPHI (_hoops_GRAHI *m, _hoops_SHGHI v, _hoops_GRRHI *_hoops_ICPHI) {
	_hoops_CGRHI *_hoops_HCRHH = neighbors(m, v);

	_hoops_CSIHI(m, _hoops_HCRHH, 0);
	_hoops_CIAHI(m, v, 1); /* _hoops_CAIP'_hoops_RA _hoops_HHGC _hoops_IS _hoops_GCIS _hoops_HPPC _hoops_GGR _hoops_RH _hoops_PGSH*/
	_hoops_SSIHI(m, _hoops_HCRHH, _hoops_ICPHI);
}



static void _hoops_GGCHI (_hoops_GRAHI *m, _hoops_SHGHI from, _hoops_SHGHI to) {
	int i;
	int *_hoops_RGCHI;
	_hoops_GCGHI *f;
#if 0
	int _hoops_GCHAI = _hoops_IGPHI (m, from);
	int _hoops_CGPCP = _hoops_IGPHI (m, to);
#endif
	ASSERT (from < _hoops_HPAHI (m)); 
	ASSERT (to < _hoops_HPAHI (m)); 
	ASSERT (_hoops_IGPHI (m, from));
	ASSERT (_hoops_IGPHI (m, to));

	for (i = 0; i < _hoops_CGGHI (neighbors (m, from)); i++)
	{
		f = _hoops_SAAHI (m, _hoops_GARHI (neighbors (m, from), i));
		_hoops_GSGHI (f, from, to);
	}

	_hoops_PSIHI (m, from, 0);
	_hoops_PSIHI (m, to, 1);
	_hoops_ISIHI (m, from, neighbors (m, to));

	_hoops_SGPHI (m, from);
	_hoops_HSSPI (neighbors (m, from));	/* _hoops_HASIR _hoops_GPHHR _hoops_GGR _hoops_RHGS _hoops_GPHA*/

	/* _hoops_GRHP _hoops_IHGC _hoops_IIGR _hoops_CAS _hoops_GIHA _hoops_CHR _hoops_CPIC _hoops_IS */
	_hoops_RGCHI = (int *) _hoops_SGGHI	 (&(m->_hoops_ASRHI), from);
	*_hoops_RGCHI = to;
}


static void _hoops_AGCHI (_hoops_GRAHI *m, _hoops_GIGHI fid) {
	_hoops_GCGHI *f = _hoops_SAAHI (m, fid);
	int j, _hoops_PPIHA=0;

	_hoops_ARPHI (m, fid);

	if (_hoops_AARHI (neighbors (m, f->v[0]), fid, &j)) { 
		_hoops_PPIHA++; 
		_hoops_AGGHI (neighbors (m, f->v[0]), j);
	}
	if (_hoops_AARHI (neighbors (m, f->v[1]), fid, &j)) { 
		_hoops_PPIHA++; 
		_hoops_AGGHI (neighbors (m, f->v[1]), j);
	}
	if (_hoops_AARHI (neighbors (m, f->v[2]), fid, &j)) { 
		_hoops_PPIHA++; 
		_hoops_AGGHI (neighbors (m, f->v[2]), j); 
	}
	ASSERT (_hoops_PPIHA > 0);
	ASSERT (!_hoops_AARHI (neighbors (m, f->v[0]), fid, &j));
	ASSERT (!_hoops_AARHI (neighbors (m, f->v[1]), fid, &j));
	ASSERT (!_hoops_AARHI (neighbors (m, f->v[2]), fid, &j));
}

#if 0
static void _hoops_GSPHI (_hoops_GRAHI *m, _hoops_CGRHI *_hoops_PGCHI) {
	int i;
	_hoops_GCGHI *f;

	for (i = 0; i < _hoops_CGGHI (_hoops_PGCHI); i++)
	{
		ASSERT (_hoops_GRPHI (m, _hoops_GARHI (_hoops_PGCHI, i)));
		f = _hoops_SAAHI (m, _hoops_GARHI (_hoops_PGCHI, i));

		if (f->v[0]==f->v[1] || f->v[1]==f->v[2] || f->v[0]==f->v[2])
			_hoops_AGCHI (m, _hoops_GARHI (_hoops_PGCHI, i));
	}
}
#endif

void _hoops_PSPHI (_hoops_GRAHI *m, _hoops_SHGHI _hoops_ISPI, _hoops_SHGHI _hoops_CSPI,
					 _hoops_SHRHI *_hoops_HGCHI) {
	int i, _hoops_HSIHI;
	_hoops_GCGHI *f;
	int _hoops_IGCHI;
	_hoops_CGRHI *_hoops_GSIHI;
	_hoops_GIGHI fid;

	_hoops_HGCHI->_hoops_ISPI = _hoops_ISPI;
	_hoops_HGCHI->_hoops_CSPI = _hoops_CSPI;
	_hoops_HGCHI->_hoops_AHRHI[X] = _hoops_HGCHI->_hoops_AHRHI[Y] = _hoops_HGCHI->_hoops_AHRHI[_hoops_GACPA] = 0.0;
	_hoops_HGCHI->_hoops_PHRHI[X] = _hoops_HGCHI->_hoops_PHRHI[Y] = _hoops_HGCHI->_hoops_PHRHI[_hoops_GACPA] = 0.0;

	_hoops_HSSPI (&(_hoops_HGCHI->_hoops_IHRHI));
	_hoops_HSSPI (&(_hoops_HGCHI->_hoops_CHRHI));

	/* _hoops_PHIAR _hoops_APIHR _hoops_IIGR _hoops_CIHHR _hoops_IS _hoops_GCRHI _hoops_PPR _hoops_CIRHI*/
	_hoops_HSIHI = _hoops_CGGHI (neighbors (m, _hoops_CSPI));
	for (i = 0; i < _hoops_HSIHI; i++)
	{
		f = _hoops_SAAHI (m, _hoops_GARHI (neighbors (m, _hoops_CSPI), i));
		_hoops_IGCHI =  (f->v[0]==_hoops_ISPI || f->v[1]==_hoops_ISPI || f->v[2]==_hoops_ISPI);
		_hoops_GSIHI = neighbors (m, _hoops_CSPI);
		fid = _hoops_GARHI (_hoops_GSIHI, i);
		if (_hoops_IGCHI) 
			_hoops_ISSPI (&(_hoops_HGCHI->_hoops_CHRHI), &fid);
		else			 
			_hoops_ISSPI (&(_hoops_HGCHI->_hoops_IHRHI), &fid);
	}
}

void _hoops_HSPHI (_hoops_GRAHI *m, _hoops_SHRHI *_hoops_HGCHI) {
	int i;
	_hoops_SHGHI _hoops_ISPI=_hoops_HGCHI->_hoops_ISPI, _hoops_CSPI=_hoops_HGCHI->_hoops_CSPI;
	_hoops_GIGHI fid;
	_hoops_GCGHI *f;
	_hoops_IIGHI *v;

	/* _hoops_PARAR _hoops_IIHHR _hoops_IS _hoops_CCAH _hoops_AHC*/
	v = _hoops_CAAHI (m, _hoops_ISPI);
	_hoops_CRSPI (v->_hoops_GGSPI, v->_hoops_GGSPI, _hoops_HGCHI->_hoops_AHRHI, 3);

	/* _hoops_ACRAR _hoops_CRHPH _hoops_RSSI*/
	for (i = 0; i < _hoops_CGGHI (&(_hoops_HGCHI->_hoops_CHRHI)); i++)
	{
		fid = _hoops_ACRHI (_hoops_HGCHI, i);
		_hoops_AGCHI (m, fid);
	}

	/* _hoops_HRHI _hoops_HGAS _hoops_RSSI*/
	for (i = 0; i < _hoops_CGGHI (&(_hoops_HGCHI->_hoops_IHRHI)); i++)
	{
		fid = _hoops_RCRHI (_hoops_HGCHI, i);
		f = _hoops_SAAHI (m, fid);
		_hoops_GSGHI (f, _hoops_CSPI, _hoops_ISPI);
		_hoops_ISSPI (neighbors (m, _hoops_ISPI), &fid);
	}

	/* !!_hoops_CCPC: _hoops_HGI _hoops_HRGR _hoops_CPSA _hoops_RGAR _hoops_IRS _hoops_AH _hoops_CGCHI _hoops_IS _hoops_RH _hoops_ARPC*/
	/*
	_hoops_RPP (_hoops_PHPHI (_hoops_SPHAI) == _hoops_SGCHI)
	{
		_hoops_IH (_hoops_HAS = 0; _hoops_HAS < _hoops_IHGHI (&(_hoops_GRCHI->_hoops_CIRHI)); _hoops_HAS++)
		{
			_hoops_RRCHI (&_hoops_IRHP, _hoops_ACHP[0], _hoops_ACHP[1], _hoops_ACHP[2]);
			_hoops_ARCHI (_hoops_SPHAI, _hoops_PIRHI (_hoops_GRCHI, _hoops_HAS), _hoops_ACHP, 1);
			_hoops_GGSR = _hoops_GAAHI (_hoops_SPHAI, _hoops_PIRHI (_hoops_GRCHI, _hoops_HAS));
			_hoops_PRCHI (_hoops_GGSR, &_hoops_IRHP, _hoops_GGHSP (_hoops_ASGHI));
		}
	}
	*/

	/* _hoops_HRCHI _hoops_CIHHR*/
	/* _hoops_RGPHI (_hoops_SPHAI, _hoops_CIHHR); */
	_hoops_GGCHI (m, _hoops_CSPI, _hoops_ISPI);
	_hoops_HSSPI (neighbors (m, _hoops_CSPI));
} /* _hoops_RSGR _hoops_API _hoops_IRCHI */



/*
 *
 * _hoops_GCIAR _hoops_SHS _hoops_IISA _hoops_HII _hoops_RH _hoops_GIGR _hoops_CRCHI
 *
 */


_hoops_SHGHI _hoops_RHPHI(_hoops_GRAHI *m, double x, double y, double z) {
	_hoops_SHGHI _hoops_HACGH, _hoops_SRCHI, _hoops_GACHI;
	_hoops_CGRHI *_hoops_PSRGA;


	_hoops_IIGHI temp;
	temp._hoops_GGSPI[0] = x;
	temp._hoops_GGSPI[1] = y;
	temp._hoops_GGSPI[2] = z;
	_hoops_HACGH = _hoops_ISSPI (&(m->vertices), &temp);
	_hoops_ISSPI (&(m->_hoops_SSRHI), &_hoops_HCIHI);
	_hoops_CGPHI (m, _hoops_HACGH);

	_hoops_GACHI = _hoops_ISSPI (&(m->_hoops_ASRHI), &_hoops_HACGH);		/* (_hoops_GRS _hoops_HAR _hoops_CIPAA _hoops_RACHI) */
	/* _hoops_AGCR _hoops_PGCR _hoops_HCPH _hoops_HS _hoops_IS _hoops_SHH (_hoops_PPR _hoops_CHR) _hoops_SRSGA _hoops_GH _hoops_GGR _hoops_AACHI */
	ALLOC (_hoops_PSRGA, _hoops_CGRHI);
	_hoops_RSSPI (_hoops_PSRGA, sizeof (_hoops_GIGHI)); 
	_hoops_SRCHI = _hoops_SSSPI (&(m->_hoops_PGAHI), _hoops_PSRGA);
	ASSERT (_hoops_SRCHI == _hoops_HACGH);
	ASSERT (_hoops_GACHI == _hoops_HACGH);
	ASSERT (_hoops_CGGHI (neighbors (m, _hoops_HACGH)) == 0);

	return _hoops_HACGH;
}


_hoops_GIGHI _hoops_AHPHI (_hoops_GRAHI *m, int _hoops_ISPI, int _hoops_CSPI, int _hoops_SSPI) {
	_hoops_GIGHI id = _hoops_CCIHI (m, _hoops_ISPI, _hoops_CSPI, _hoops_SSPI);
	_hoops_SCIHI (m, id);
	return id;
}


/*	
 * _hoops_PACHI _hoops_PCIA
 */

#ifndef _hoops_IAAA
#  define _hoops_IAAA(a,b) (((a)>(b))?(a):(b))
#endif

#if 0
static
int _hoops_HACHI (_hoops_GRAHI *m, unsigned char i) {
	switch (i)
	{
		case _hoops_HARHI: return 0;
		case _hoops_CARHI: return _hoops_IAAA (1, _hoops_HPAHI(m));
		case _hoops_IARHI: return _hoops_IAAA (1, _hoops_IPAHI(m));
		default: return 0;
	}
}
#endif


/*	
 * _hoops_HGHGR _hoops_PISRR _hoops_IH _hoops_CGGGA _hoops_CSIIR _hoops_IIGR _hoops_RSSI.
 */

int _hoops_CIPHI (_hoops_GRAHI *m, _hoops_GIGHI f, double *n, _hoops_CGSPI _hoops_SIPHI) {
	double *_hoops_ISPI = _hoops_CAAHI (m, _hoops_SAAHI (m, f)->v[0])->_hoops_GGSPI;
	double *_hoops_CSPI = _hoops_CAAHI (m, _hoops_SAAHI (m, f)->v[1])->_hoops_GGSPI;
	double *_hoops_SSPI = _hoops_CAAHI (m, _hoops_SAAHI (m, f)->v[2])->_hoops_GGSPI;

	double a[3], b[3];

	_hoops_SRSPI(a, _hoops_CSPI, _hoops_ISPI, 3);
	_hoops_SRSPI(b, _hoops_SSPI, _hoops_ISPI, 3);
	_hoops_CASPI (n, a, b, 3);
	if (_hoops_SIPHI)
		return _hoops_RPSPI(n, 3);

	return 1;
} /* _hoops_RSGR _hoops_API _hoops_ARCHI */


double _hoops_GCPHI (_hoops_GRAHI *m, _hoops_GIGHI f) {
	double n[3];

	_hoops_CIPHI (m, f, n, 0);
	return 0.5f * _hoops_SASPI(n, 3);
}


double _hoops_RCPHI (_hoops_GRAHI *m, _hoops_GIGHI f, int i) {
	int _hoops_IACHI = (i==0)?2:i-1;
	int _hoops_CACHI = (i==2)?0:i+1;
	double _hoops_SACHI[3], _hoops_GPCHI[3];
	_hoops_IIGHI *_hoops_RPCHI, *_hoops_APCHI, *vi;

	_hoops_RPCHI = _hoops_GPAHI (m, f, _hoops_IACHI);
	_hoops_APCHI = _hoops_GPAHI (m, f, _hoops_CACHI);
	vi	  = _hoops_GPAHI (m, f, i);
	_hoops_SRSPI(_hoops_SACHI, _hoops_RPCHI->_hoops_GGSPI, vi->_hoops_GGSPI, 3);
	_hoops_SRSPI(_hoops_GPCHI, _hoops_APCHI->_hoops_GGSPI, vi->_hoops_GGSPI, 3);
	_hoops_RPSPI(_hoops_SACHI, 3);
	_hoops_RPSPI(_hoops_GPCHI, 3);

	return (double) acos (_hoops_IASPI(_hoops_SACHI, _hoops_GPCHI, 3));
}


/*
 * _hoops_IPCP _hoops_ACSP _hoops_IIGR _hoops_RH _hoops_RGHR _hoops_HRGR _hoops_PSCH _hoops_SGS _hoops_AAPR _hoops_RAARH _hoops_PAPR _hoops_GGR _hoops_RH _hoops_RGSPR
 * _hoops_RGHR _hoops_GAR _hoops_SSHGI _hoops_PSCH
 */

void _hoops_GIRHI (_hoops_SHRHI *_hoops_RIRHI) { 
	_hoops_RSSPI (&(_hoops_RIRHI->_hoops_IHRHI), sizeof (int));
	_hoops_RSSPI (&(_hoops_RIRHI->_hoops_CHRHI), sizeof (int));
}

void _hoops_AIRHI (_hoops_SHRHI *_hoops_RIRHI) { 
	_hoops_PSSPI (&(_hoops_RIRHI->_hoops_IHRHI));
	_hoops_PSSPI (&(_hoops_RIRHI->_hoops_CHRHI));
}


/* _hoops_PPCHI
 * _hoops_HGI _hoops_API _hoops_HRGR _hoops_RRRIR _hoops_HPCHI, _hoops_HIS _hoops_SGH _hoops_IPCHI */
int _hoops_SPAHI (_hoops_GRAHI *m) {
	int i, _hoops_HSIHI, count = 0;

	_hoops_HSIHI = _hoops_IPAHI (m);
	for (i = 0; i < _hoops_HSIHI; i++)
	{
		if (_hoops_GRPHI (m, i))
			count++;
	}
	return count;
} /* _hoops_RSGR _hoops_API _hoops_PPCHI */



/* _hoops_PPCHI
 * _hoops_HGI _hoops_API _hoops_HRGR _hoops_RRRIR _hoops_HPCHI, _hoops_HIS _hoops_SGH _hoops_IPCHI */
int _hoops_GHAHI (_hoops_GRAHI *m) {
	int i, _hoops_HSIHI, count = 0;

	_hoops_HSIHI = _hoops_HPAHI (m);
	for (i = 0; i < _hoops_HSIHI; i++)
	{
		if (_hoops_IGPHI (m, i))
			count++;
	}
	return count;
} /* _hoops_RSGR _hoops_API _hoops_CPCHI */

const double _hoops_SPCHI = 6.928203230275509f;


/*
 *	_hoops_HAIA _hoops_PGPP _hoops_SASI _hoops_IS 3x3 _hoops_HCIA
 */

#if 0
static double _hoops_HHIPA (const _hoops_HGSPI *_hoops_RAGH) {
		_hoops_RGSPI temp;
		_hoops_CASPI (temp._hoops_GGSPI, _hoops_RAGH->row[1]._hoops_GGSPI, _hoops_RAGH->row[2]._hoops_GGSPI, 3);
	return _hoops_IASPI (_hoops_RAGH->row[0]._hoops_GGSPI, temp._hoops_GGSPI, 3);
}

static void _hoops_GHCHI (_hoops_HGSPI *_hoops_RHCHI, const _hoops_HGSPI *_hoops_RAGH) {
		_hoops_GRSPI (&(_hoops_RHCHI->row[0]), _hoops_RAGH, 0);
		_hoops_GRSPI (&(_hoops_RHCHI->row[1]), _hoops_RAGH, 1);
		_hoops_GRSPI (&(_hoops_RHCHI->row[2]), _hoops_RAGH, 2);
}
#endif

void _hoops_ARSPI (_hoops_RGSPI *_hoops_RRSPI, const _hoops_HGSPI *_hoops_RAGH, const _hoops_RGSPI *_hoops_ISPI) {
		_hoops_RRSPI->_hoops_GGSPI[0] = _hoops_IASPI (_hoops_RAGH->row[0]._hoops_GGSPI, _hoops_ISPI->_hoops_GGSPI, 3); 
		_hoops_RRSPI->_hoops_GGSPI[1] = _hoops_IASPI (_hoops_RAGH->row[1]._hoops_GGSPI, _hoops_ISPI->_hoops_GGSPI, 3); 
		_hoops_RRSPI->_hoops_GGSPI[2] = _hoops_IASPI (_hoops_RAGH->row[2]._hoops_GGSPI, _hoops_ISPI->_hoops_GGSPI, 3);
}

void _hoops_GRSPI (_hoops_RGSPI *_hoops_RRSPI, const _hoops_HGSPI *_hoops_RAGH, int i) { 
		_hoops_RRSPI->_hoops_GGSPI[0] = _hoops_RAGH->row[0]._hoops_GGSPI[i];
		_hoops_RRSPI->_hoops_GGSPI[1] = _hoops_RAGH->row[1]._hoops_GGSPI[i];
		_hoops_RRSPI->_hoops_GGSPI[2] = _hoops_RAGH->row[2]._hoops_GGSPI[i]; 
}

/*
 * _hoops_ISSP _hoops_IRS 3x3 _hoops_RSGA. _hoops_HRS _hoops_RH _hoops_AHCHI.
 */
double _hoops_SGSPI (_hoops_HGSPI *_hoops_RHCHI, const _hoops_HGSPI *_hoops_RAGH) {
		_hoops_HGSPI temp, _hoops_APIHI;
		double d;
				
		/* _hoops_GRAS _hoops_RH _hoops_GGRA: _hoops_GGRA (&_hoops_RAIGR, _hoops_PHCHI); */
		_hoops_CASPI (_hoops_APIHI.row[0]._hoops_GGSPI, _hoops_RAGH->row[1]._hoops_GGSPI, _hoops_RAGH->row[2]._hoops_GGSPI, 3);
		_hoops_CASPI (_hoops_APIHI.row[1]._hoops_GGSPI, _hoops_RAGH->row[2]._hoops_GGSPI, _hoops_RAGH->row[0]._hoops_GGSPI, 3);
		_hoops_CASPI (_hoops_APIHI.row[2]._hoops_GGSPI, _hoops_RAGH->row[0]._hoops_GGSPI, _hoops_RAGH->row[1]._hoops_GGSPI, 3);

	d = _hoops_IASPI (_hoops_APIHI.row[0]._hoops_GGSPI, _hoops_RAGH->row[0]._hoops_GGSPI, 3);

	if (d==0.0)
				return 0.0;
		/* _hoops_GRAS _hoops_RH _hoops_HGICR: _hoops_HGICR (&_hoops_IRHP, &_hoops_RAIGR); */
		_hoops_GRSPI (&(temp.row[0]), &_hoops_APIHI, 0);
		_hoops_GRSPI (&(temp.row[1]), &_hoops_APIHI, 1);
		_hoops_GRSPI (&(temp.row[2]), &_hoops_APIHI, 2);

		_hoops_RASPI (_hoops_RHCHI->row[0]._hoops_GGSPI, temp.row[0]._hoops_GGSPI, d, 3);
		_hoops_RASPI (_hoops_RHCHI->row[1]._hoops_GGSPI, temp.row[1]._hoops_GGSPI, d, 3);
		_hoops_RASPI (_hoops_RHCHI->row[2]._hoops_GGSPI, temp.row[2]._hoops_GGSPI, d, 3);
	return d;
}


/*
 *	_hoops_HAIA _hoops_PGPP _hoops_SASI _hoops_IS 4x4 _hoops_HCIA
 */


static void _hoops_HHCHI (_hoops_SSCPI *result, const _hoops_PGSPI *m, int i) { 
		result->_hoops_GGSPI[0] = m->row[0]._hoops_GGSPI[i];
		result->_hoops_GGSPI[1] = m->row[1]._hoops_GGSPI[i];
		result->_hoops_GGSPI[2] = m->row[2]._hoops_GGSPI[i];
		result->_hoops_GGSPI[3] = m->row[3]._hoops_GGSPI[i];
}


static void _hoops_IHCHI(_hoops_PGSPI *_hoops_RAGH, const _hoops_PGSPI *_hoops_AAGH) {
	_hoops_HASPI (_hoops_RAGH->row[0]._hoops_GGSPI, _hoops_AAGH->row[0]._hoops_GGSPI, 4); 
		_hoops_HASPI (_hoops_RAGH->row[1]._hoops_GGSPI, _hoops_AAGH->row[1]._hoops_GGSPI, 4);
	_hoops_HASPI (_hoops_RAGH->row[2]._hoops_GGSPI, _hoops_AAGH->row[2]._hoops_GGSPI, 4); 
		_hoops_HASPI (_hoops_RAGH->row[3]._hoops_GGSPI, _hoops_AAGH->row[3]._hoops_GGSPI, 4);
}


void _hoops_IRSPI (_hoops_SSCPI *_hoops_PAGR, const _hoops_PGSPI *_hoops_RAGH, const _hoops_SSCPI *v) {
		_hoops_PAGR->_hoops_GGSPI[0] = _hoops_IASPI (_hoops_RAGH->row[0]._hoops_GGSPI, v->_hoops_GGSPI, 4); 
		_hoops_PAGR->_hoops_GGSPI[1] = _hoops_IASPI (_hoops_RAGH->row[1]._hoops_GGSPI, v->_hoops_GGSPI, 4); 
		_hoops_PAGR->_hoops_GGSPI[2] = _hoops_IASPI (_hoops_RAGH->row[2]._hoops_GGSPI, v->_hoops_GGSPI, 4); 
		_hoops_PAGR->_hoops_GGSPI[3] = _hoops_IASPI (_hoops_RAGH->row[3]._hoops_GGSPI, v->_hoops_GGSPI, 4);
}




static void _hoops_CHCHI(_hoops_PGSPI *_hoops_PAGR, const _hoops_PGSPI *in) {
		_hoops_PGSPI temp;
		_hoops_HHCHI (&(temp.row[0]), in, 0); 
		_hoops_HHCHI (&(temp.row[1]), in, 1); 
		_hoops_HHCHI (&(temp.row[2]), in, 2); 
		_hoops_HHCHI (&(temp.row[3]), in, 3); 

		/* _hoops_HAHH _hoops_IS _hoops_GIAH _hoops_HII _hoops_ARRS, _hoops_GGR _hoops_AGIR _hoops_GGSR==_hoops_GGR */
		_hoops_HASPI (_hoops_PAGR->row[0]._hoops_GGSPI, temp.row[0]._hoops_GGSPI, 4);
		_hoops_HASPI (_hoops_PAGR->row[1]._hoops_GGSPI, temp.row[1]._hoops_GGSPI, 4);
		_hoops_HASPI (_hoops_PAGR->row[2]._hoops_GGSPI, temp.row[2]._hoops_GGSPI, 4);
		_hoops_HASPI (_hoops_PAGR->row[3]._hoops_GGSPI, temp.row[3]._hoops_GGSPI, 4);
}

void _hoops_HRSPI(_hoops_PGSPI *_hoops_PAGR, const _hoops_PGSPI *_hoops_RAGH, const _hoops_PGSPI *_hoops_AAGH) {
	_hoops_PGSPI temp, _hoops_CGPCP;
	int i,j;

		_hoops_CHCHI (&temp, _hoops_RAGH);
		_hoops_IHCHI (&_hoops_CGPCP, _hoops_AAGH);

	for (i = 0; i < 4; i++)
				for (j=0;j<4;j++)
					_hoops_PAGR->row[i]._hoops_GGSPI[j] = _hoops_IASPI(_hoops_CGPCP.row[i]._hoops_GGSPI, temp.row[j]._hoops_GGSPI, 4);
}

/* _hoops_SGGS _hoops_SHII _hoops_HII _hoops_SHCHI._hoops_GSGGR _hoops_GGR _hoops_GCHRA _hoops_GICHI _hoops_RRGGR*/
static void _hoops_RICHI(_hoops_SSCPI *result, const _hoops_SSCPI *a, const _hoops_SSCPI *b, const _hoops_SSCPI *c) {
		double _hoops_GIGCR, _hoops_RIGCR, d3, _hoops_CACPH, _hoops_AICHI, _hoops_PICHI;
	_hoops_GIGCR = (b->_hoops_GGSPI[_hoops_GACPA] * c->_hoops_GGSPI[_hoops_CPCPA]) - (b->_hoops_GGSPI[_hoops_CPCPA] * c->_hoops_GGSPI[_hoops_GACPA]);
	_hoops_RIGCR = (b->_hoops_GGSPI[Y] * c->_hoops_GGSPI[_hoops_CPCPA]) - (b->_hoops_GGSPI[_hoops_CPCPA] * c->_hoops_GGSPI[Y]);
	d3 = (b->_hoops_GGSPI[Y] * c->_hoops_GGSPI[_hoops_GACPA]) - (b->_hoops_GGSPI[_hoops_GACPA] * c->_hoops_GGSPI[Y]);
	_hoops_CACPH = (b->_hoops_GGSPI[X] * c->_hoops_GGSPI[_hoops_CPCPA]) - (b->_hoops_GGSPI[_hoops_CPCPA] * c->_hoops_GGSPI[X]);
	_hoops_AICHI = (b->_hoops_GGSPI[X] * c->_hoops_GGSPI[_hoops_GACPA]) - (b->_hoops_GGSPI[_hoops_GACPA] * c->_hoops_GGSPI[X]);
	_hoops_PICHI = (b->_hoops_GGSPI[X] * c->_hoops_GGSPI[Y]) - (b->_hoops_GGSPI[Y] * c->_hoops_GGSPI[X]);

	result->_hoops_GGSPI[X] = - a->_hoops_GGSPI[Y] * _hoops_GIGCR + a->_hoops_GGSPI[_hoops_GACPA] * _hoops_RIGCR - a->_hoops_GGSPI[_hoops_CPCPA] * d3;
	result->_hoops_GGSPI[Y] =   a->_hoops_GGSPI[X] * _hoops_GIGCR - a->_hoops_GGSPI[_hoops_GACPA] * _hoops_CACPH + a->_hoops_GGSPI[_hoops_CPCPA] * _hoops_AICHI;
	result->_hoops_GGSPI[_hoops_GACPA] = - a->_hoops_GGSPI[X] * _hoops_RIGCR + a->_hoops_GGSPI[Y] * _hoops_CACPH - a->_hoops_GGSPI[_hoops_CPCPA] * _hoops_PICHI;
	result->_hoops_GGSPI[_hoops_CPCPA] =   a->_hoops_GGSPI[X] * d3 - a->_hoops_GGSPI[Y] * _hoops_AICHI + a->_hoops_GGSPI[_hoops_GACPA] * _hoops_PICHI;
}

void _hoops_PRSPI(_hoops_PGSPI *_hoops_PAGR, const _hoops_PGSPI *in) {
	_hoops_PGSPI _hoops_APIHI;
		_hoops_SSCPI _hoops_HICHI;

		_hoops_IHCHI (&_hoops_APIHI, in);
		_hoops_AASPI (_hoops_HICHI._hoops_GGSPI, _hoops_APIHI.row[0]._hoops_GGSPI, 4);

	_hoops_RICHI (&(_hoops_PAGR->row[0]), &(_hoops_APIHI.row[1]), &(_hoops_APIHI.row[2]), &(_hoops_APIHI.row[3]));
	_hoops_RICHI (&(_hoops_PAGR->row[1]), &(_hoops_HICHI),	 &(_hoops_APIHI.row[2]), &(_hoops_APIHI.row[3]));
	_hoops_RICHI (&(_hoops_PAGR->row[2]), &(_hoops_APIHI.row[0]), &(_hoops_APIHI.row[1]), &(_hoops_APIHI.row[3]));
	_hoops_RICHI (&(_hoops_PAGR->row[3]), &(_hoops_HICHI),	 &(_hoops_APIHI.row[1]), &(_hoops_APIHI.row[2]));
}


#if 0
/*
 * _hoops_ASHPA _hoops_IICHI _hoops_RRGR _hoops_IH 4x4 _hoops_HCIA.
 * _hoops_CICHI _hoops_CHII _hoops_PSAP _hoops_PPR _hoops_SICHI _hoops_HII _hoops_GCCHI'_hoops_GRI _hoops_RSGA _hoops_GIRPR
 * _hoops_IH _hoops_RH _hoops_RAR _hoops_RCCHI (_hoops_ACCHI) _hoops_ICCGR.
 *
 * _hoops_GCAAA _hoops_AHCHI _hoops_IIGR _hoops_IRS, _hoops_PPR _hoops_RCSR=_hoops_IRS _hoops_AGICR.
 * _hoops_CGP _hoops_RSGA _hoops_HRGR _hoops_PCCHI, _hoops_HRS 0 _hoops_PPR _hoops_GRIRA _hoops_HCCHI _hoops_GGR _hoops_RCSR.
 *
 * _hoops_ICCHI _hoops_SPRP _hoops_CCCHI _hoops_CCA _hoops_IASI _hoops_SCCHI.
 */


static double invert(_hoops_PGSPI *result, const _hoops_PGSPI *input) {
		_hoops_PGSPI temp;
	int i, j, k;
	double max, t, _hoops_HHIPA, pivot;

		_hoops_IHCHI (&temp, input);

	/*---------- _hoops_CPCHR _hoops_CCCHI ----------*/

	for (i=0; i<4; i++)					/* _hoops_PPSI _hoops_SRGH _hoops_RSGA _hoops_CRGR _hoops_IIPR */
		for (j=0; j<4; j++)
						result->row[i]._hoops_GGSPI[j] = (double)(i==j);

	_hoops_HHIPA = 1.0;
	for (i=0; i<4; i++) {				/* _hoops_GSCHI _hoops_GGR _hoops_PIHP _hoops_HAS, _hoops_CAPP _hoops_RSCHI */
		max = -1.;
		for (k=i; k<4; k++)				/* _hoops_SSS _hoops_PCIHP _hoops_IH _hoops_PIHP _hoops_HAS */
			if (fabs (temp.row[k]._hoops_GGSPI[i]) > max) {
				max = (double) fabs (temp.row[k]._hoops_GGSPI[i]);
				j = k;
			}
		if (max<=0.) return 0.;			/* _hoops_RPP _hoops_PSP _hoops_RRAIA _hoops_PCIHP, _hoops_ASCHI */
		if (j!=i) {						/* _hoops_GGSHR _hoops_HAPHR _hoops_HAS _hoops_PPR _hoops_PPHR */
			for (k=i; k<4; k++)
				Swap (temp.row[i]._hoops_GGSPI[k], temp.row[j]._hoops_GGSPI[k]);
			for (k=0; k<4; k++)
				Swap (result->row[i]._hoops_GGSPI[k], result->row[j]._hoops_GGSPI[k]);
			_hoops_HHIPA = -_hoops_HHIPA;
		}
		pivot = temp.row[i]._hoops_GGSPI[i];
		_hoops_HHIPA *= pivot;
		for (k=i+1; k<4; k++)			/* _hoops_RGAR _hoops_AA _hoops_PSCHI _hoops_IS _hoops_RPHR _hoops_IIGR _hoops_PCIHP */
			temp.row[i]._hoops_GGSPI[k] /= pivot;
		for (k=0; k<4; k++)
			result->row[i]._hoops_GGSPI[k] /= pivot;
		/* _hoops_SR _hoops_ACPA _hoops_SGS _hoops_RAIGR(_hoops_HAS, _hoops_HAS) _hoops_GRS _hoops_SHH _hoops_ARP _hoops_IS 1, _hoops_HIS _hoops_GA'_hoops_RA _hoops_SHAC _hoops_IS _hoops_AA _hoops_SCH */

		for (j=i+1; j<4; j++) {			/* _hoops_GSCHI _hoops_GGR _hoops_HAPHR _hoops_CAPP _hoops_HAS */
			t = temp.row[j]._hoops_GGSPI[i];		  /* _hoops_SR'_hoops_ASAR _hoops_GISI _hoops_AHHR _hoops_RGR _hoops_HSCHI */
			for (k=i+1; k<4; k++)		/* _hoops_ICHRA _hoops_CPPSR _hoops_GAGHR _hoops_HAS _hoops_HII _hoops_GAGHR _hoops_PPHR */
				temp.row[j]._hoops_GGSPI[k] -= temp.row[i]._hoops_GGSPI[k] * t;	/* (_hoops_SSPC _hoops_ARGI<=_hoops_HAS, _hoops_SR _hoops_ACPA _hoops_SSIA'_hoops_ASAR 0) */
			for (k=0; k<4; k++)
				result->row[j]._hoops_GGSPI[k] -= result->row[i]._hoops_GGSPI[k] * t;
		}
	}

	/*---------- _hoops_SPCHR _hoops_CCCHI ----------*/

	for (i=4-1; i>0; i--) {				/* _hoops_GSCHI _hoops_GGR _hoops_PIHP _hoops_HAS, _hoops_ARRS _hoops_RSCHI */
		for (j=0; j<i; j++) {			/* _hoops_GSCHI _hoops_GGR _hoops_HAPHR _hoops_ARRS _hoops_HAS */
			t = temp.row[j]._hoops_GGSPI[i];		  /* _hoops_SR'_hoops_ASAR _hoops_GISI _hoops_AHHR _hoops_RGR _hoops_HSCHI */
			for (k=0; k<4; k++)			/* _hoops_ICHRA _hoops_CPPSR _hoops_GAGHR _hoops_HAS _hoops_HII _hoops_GAGHR _hoops_PPHR */
				result->row[j]._hoops_GGSPI[k] -= result->row[i]._hoops_GGSPI[k] * t;
		}
	}

	return _hoops_HHIPA;
} /* _hoops_RSGR _hoops_API _hoops_ISSP */
#endif


/*
 * _hoops_HHH _hoops_CSCS _hoops_SCPH _hoops_PGPP
 */

void _hoops_AISPI (_hoops_RGSPI *_hoops_PAGR, const _hoops_RGSPI *_hoops_ISPI, const _hoops_RGSPI *_hoops_CSPI, const _hoops_RGSPI *_hoops_SSPI) {
		_hoops_RGSPI a, b;
	_hoops_SRSPI (a._hoops_GGSPI, _hoops_CSPI->_hoops_GGSPI, _hoops_ISPI->_hoops_GGSPI, 3);
	_hoops_SRSPI (b._hoops_GGSPI, _hoops_SSPI->_hoops_GGSPI, _hoops_ISPI->_hoops_GGSPI, 3);
	_hoops_CASPI (_hoops_PAGR->_hoops_GGSPI, a._hoops_GGSPI, b._hoops_GGSPI, 3);
}

/* _hoops_RAIA _hoops_SGCCP _hoops_SGS _hoops_SCPH _hoops_CCAC _hoops_HRGR _hoops_SHHP _hoops_HPAHR _hoops_HIHHR / 2 */
double _hoops_RISPI (const _hoops_RGSPI *_hoops_ISPI, const _hoops_RGSPI *_hoops_CSPI, const _hoops_RGSPI *_hoops_SSPI) {
		_hoops_RGSPI temp;
		_hoops_AISPI (&temp, _hoops_ISPI, _hoops_CSPI, _hoops_SSPI);
	return 0.5f * _hoops_SASPI (temp._hoops_GGSPI, 3);
}


int _hoops_PISPI (_hoops_RGSPI *_hoops_PAGR, const _hoops_RGSPI *_hoops_ISPI, const _hoops_RGSPI *_hoops_CSPI, const _hoops_RGSPI *_hoops_SSPI) {
		double f;
		
		_hoops_AISPI (_hoops_PAGR, _hoops_ISPI, _hoops_CSPI, _hoops_SSPI);
		/* _hoops_HA _hoops_ISCHI */
		f = _hoops_SASPI (_hoops_PAGR->_hoops_GGSPI, 3);

		if (_hoops_HSCIA (f, 0.0, 1e-12f))
				return 0;

		_hoops_RASPI (_hoops_PAGR->_hoops_GGSPI, _hoops_PAGR->_hoops_GGSPI, f, 3);
		return 1;
} /* _hoops_RSGR _hoops_API _hoops_CSCHI */


int _hoops_HISPI (_hoops_SSCPI *_hoops_PAGR, const _hoops_RGSPI *_hoops_ISPI, const _hoops_RGSPI *_hoops_CSPI, const _hoops_RGSPI *_hoops_SSPI) {
	_hoops_RGSPI n;
		
		if (!_hoops_PISPI (&n, _hoops_ISPI, _hoops_CSPI, _hoops_SSPI))
				return 0;

		_hoops_PAGR->_hoops_GGSPI[0] = n._hoops_GGSPI[0];
		_hoops_PAGR->_hoops_GGSPI[1] = n._hoops_GGSPI[1];
		_hoops_PAGR->_hoops_GGSPI[2] = n._hoops_GGSPI[2];
		_hoops_PAGR->_hoops_GGSPI[3] = - (_hoops_IASPI(n._hoops_GGSPI, _hoops_ISPI->_hoops_GGSPI, 3));
		return 1;
} /* _hoops_RSGR _hoops_API _hoops_SSCHI */


void _hoops_IISPI (_hoops_SSCPI *_hoops_PAGR, const _hoops_RGSPI *_hoops_ISPI, const _hoops_RGSPI *_hoops_CSPI, const _hoops_RGSPI *_hoops_SSPI) {
		_hoops_RGSPI n;

	_hoops_AISPI (&n, _hoops_ISPI, _hoops_CSPI, _hoops_SSPI);
		_hoops_PAGR->_hoops_GGSPI[0] = n._hoops_GGSPI[0];
		_hoops_PAGR->_hoops_GGSPI[1] = n._hoops_GGSPI[1];
		_hoops_PAGR->_hoops_GGSPI[2] = n._hoops_GGSPI[2];
		_hoops_PAGR->_hoops_GGSPI[3] = - (_hoops_IASPI (n._hoops_GGSPI, _hoops_ISPI->_hoops_GGSPI, 3));
} /* _hoops_RSGR _hoops_API _hoops_GGSHI */

#if 0
/* _hoops_PGAA
 * _hoops_RGSHI _hoops_RH _hoops_CIAS _hoops_HII 3 _hoops_HIAIH
 */
static double _hoops_AGSHI (double f1, double f2, double _hoops_CGHGR) {
	if (f1 >= f2)
		if (f1 >= _hoops_CGHGR)
			return f1;
		else {
			ASSERT (_hoops_CGHGR >= f2);
			return _hoops_CGHGR;
		}
	else
		if (f2 >= _hoops_CGHGR)
			return f2;
		else {
			ASSERT (_hoops_CGHGR >= f1);
			return _hoops_CGHGR;
		}  
} /* _hoops_RSGR _hoops_API _hoops_PGSHI */
#endif

double _hoops_CISPI(const _hoops_RGSPI *_hoops_ISPI, const _hoops_RGSPI *_hoops_CSPI, const _hoops_RGSPI *_hoops_SSPI) {

	_hoops_RGSPI _hoops_GCHAI, _hoops_CGPCP, _hoops_RCHAI;
	double _hoops_SARAA, _hoops_GPRAA, _hoops_HGSHI;

	_hoops_SRSPI (_hoops_GCHAI._hoops_GGSPI, _hoops_CSPI->_hoops_GGSPI, _hoops_ISPI->_hoops_GGSPI, 3);
	_hoops_SRSPI (_hoops_CGPCP._hoops_GGSPI, _hoops_SSPI->_hoops_GGSPI, _hoops_CSPI->_hoops_GGSPI, 3);
	_hoops_SRSPI (_hoops_RCHAI._hoops_GGSPI, _hoops_ISPI->_hoops_GGSPI, _hoops_SSPI->_hoops_GGSPI, 3);
	_hoops_SARAA = _hoops_GPSPI (_hoops_GCHAI._hoops_GGSPI, 3);
	_hoops_GPRAA = _hoops_GPSPI (_hoops_CGPCP._hoops_GGSPI, 3);
	_hoops_HGSHI = _hoops_GPSPI (_hoops_RCHAI._hoops_GGSPI, 3);

	return _hoops_SPCHI * _hoops_RISPI(_hoops_ISPI, _hoops_CSPI, _hoops_SSPI) / (_hoops_SARAA+_hoops_GPRAA+_hoops_HGSHI);
} /* _hoops_RSGR _hoops_API _hoops_IGSHI */


/* _hoops_CGSHI _hoops_HCR _hoops_IIGR _hoops_RH _hoops_GRPC _hoops_IIGR _hoops_RH _hoops_AHCRR _hoops_AARI _hoops_PGCR _hoops_RSSA */
void _hoops_SISPI (_hoops_RGSPI v[], const _hoops_RGSPI *min, const _hoops_RGSPI *max) {
	v[0]._hoops_GGSPI[0] = min->_hoops_GGSPI[0]; v[0]._hoops_GGSPI[1] = min->_hoops_GGSPI[1]; v[0]._hoops_GGSPI[2] = min->_hoops_GGSPI[2];
	v[1]._hoops_GGSPI[0] = min->_hoops_GGSPI[0]; v[1]._hoops_GGSPI[1] = max->_hoops_GGSPI[1]; v[1]._hoops_GGSPI[2] = min->_hoops_GGSPI[2];
	v[2]._hoops_GGSPI[0] = max->_hoops_GGSPI[0]; v[2]._hoops_GGSPI[1] = min->_hoops_GGSPI[1]; v[2]._hoops_GGSPI[2] = min->_hoops_GGSPI[2];
	v[3]._hoops_GGSPI[0] = max->_hoops_GGSPI[0]; v[3]._hoops_GGSPI[1] = max->_hoops_GGSPI[1]; v[3]._hoops_GGSPI[2] = min->_hoops_GGSPI[2];
	v[4]._hoops_GGSPI[0] = min->_hoops_GGSPI[0]; v[4]._hoops_GGSPI[1] = min->_hoops_GGSPI[1]; v[4]._hoops_GGSPI[2] = max->_hoops_GGSPI[2];
	v[5]._hoops_GGSPI[0] = min->_hoops_GGSPI[0]; v[5]._hoops_GGSPI[1] = max->_hoops_GGSPI[1]; v[5]._hoops_GGSPI[2] = max->_hoops_GGSPI[2];
	v[6]._hoops_GGSPI[0] = max->_hoops_GGSPI[0]; v[6]._hoops_GGSPI[1] = min->_hoops_GGSPI[1]; v[6]._hoops_GGSPI[2] = max->_hoops_GGSPI[2];
	v[7]._hoops_GGSPI[0] = max->_hoops_GGSPI[0]; v[7]._hoops_GGSPI[1] = max->_hoops_GGSPI[1]; v[7]._hoops_GGSPI[2] = max->_hoops_GGSPI[2];
} /* _hoops_RSGR _hoops_API _hoops_SGSHI */




/*
 *	_hoops_PCSH _hoops_CASGI _hoops_GRSHI _hoops_GHSSR
 */


void _hoops_CRSPI (double *r, const double *u, const double *v, int _hoops_GHGIR) {
	int i;
	for (i = 0; i < _hoops_GHGIR; i++) 
		r[i] = u[i] + v[i];
} 


void _hoops_SRSPI (double *r, const double *u, const double *v, int _hoops_GHGIR) {
	int i;
	for (i = 0; i < _hoops_GHGIR; i++) 
		r[i] = u[i] - v[i];
} 


void _hoops_GASPI (double *r, const double *u, const double d, int _hoops_GHGIR) {
	int i;
	for (i = 0; i < _hoops_GHGIR; i++) 
		r[i] = u[i] * d;
} 

void _hoops_RASPI (double *r, const double *u, const double d, int _hoops_GHGIR) {
	int i;
	for (i = 0; i < _hoops_GHGIR; i++) 
		r[i] = u[i] / d;
} 

void _hoops_AASPI  (double *r, const double *u, int _hoops_GHGIR) { 
	int i;
	for (i = 0; i < _hoops_GHGIR; i++) 
		r[i] = -u[i];
}

void _hoops_PASPI  (double *r, const double d, int _hoops_GHGIR) { 
	int i;
	for (i = 0; i < _hoops_GHGIR; i++) 
		r[i] = d;
}

void _hoops_HASPI  (double *r, const double *u, int _hoops_GHGIR)
	{
	int i;
	for (i = 0; i < _hoops_GHGIR; i++) 
		r[i] = u[i];
}

double _hoops_IASPI(const double *u, const double *v, int _hoops_GHGIR) {
	int i;
	double _hoops_SSRP=0.0;	 
	for (i = 0; i < _hoops_GHGIR; i++) 
		_hoops_SSRP += u[i]*v[i];  
	return _hoops_SSRP;
}

void _hoops_CASPI(double *r, const double *u, const double *v, int _hoops_GHGIR) {
	UNREFERENCED(_hoops_GHGIR);
	ASSERT (_hoops_GHGIR == 3);
	r[0] =	(u[1] * v[2]) - (v[1] * u[2]); 
	r[1] = -(u[0] * v[2]) + (v[0] * u[2]);
	r[2] =	(u[0] * v[1]) - (v[0] * u[1]);	
}


double _hoops_SASPI(const double *v, int _hoops_GHGIR) { 
	return (double) sqrt(_hoops_IASPI(v,v,_hoops_GHGIR)); 
}


double _hoops_GPSPI(const double *v, int _hoops_GHGIR) { 
	return _hoops_IASPI(v,v,_hoops_GHGIR); 
}


/* _hoops_CGP _hoops_GSSAA _hoops_HRGR _hoops_GRAA-_hoops_AHHR, _hoops_GHAHH _hoops_PCGGR _hoops_PPR _hoops_ASRC 1, _hoops_SHS _hoops_ASRC 0 
 * _hoops_GPGP _hoops_RII _hoops_ARCCP, _hoops_ASRC 0 _hoops_GPP _hoops_HPCS */
int _hoops_RPSPI(double *v, int _hoops_GHGIR) {
	double len = _hoops_GPSPI(v, _hoops_GHGIR);
	if (_hoops_HSCIA (len, 0.0, 1e-12f))
		return 0;

	len = (double) sqrt (len);	
	_hoops_RASPI(v, v, len, _hoops_GHGIR); 

	return 1;
} /* _hoops_RSGR _hoops_API _hoops_RRSHI */




typedef struct {
	int *data;
	int used;
	int allocated;
} _hoops_ARSHI;

#define _hoops_HSCIA(a,b,_hoops_ISCIA) ((fabs((a)-(b))<(_hoops_ISCIA)))


local void _hoops_PRSHI (int pcount, const float *points, float *min, float *max) {
	int i;

	/* _hoops_HSPP _hoops_HPP _hoops_IHRHA _hoops_IRS _hoops_CGGPR/_hoops_AHPA _hoops_IAPR _hoops_RH _hoops_RSSA */
	max[0] = -10000;
	max[1] = -10000;
	max[2] = -10000;
	min[0] = 10000;
	min[1] = 10000;
	min[2] = 10000;
	for (i=0; i<pcount; i++) {
		if (points[3*i] > max[0]) 
			max[0] = points[3*i];
		if (points[3*i+1] > max[1]) 
			max[1] = points[3*i+1];
		if (points[3*i+2] > max[2]) 
			max[2] = points[3*i+2];
		if (points[3*i] < min[0]) 
			min[0] = points[3*i];
		if (points[3*i+1] < min[1]) 
			min[1] = points[3*i+1];
		if (points[3*i+2] < min[2]) 
			min[2] = points[3*i+2];
	}
}


local float _hoops_HRSHI(float f) {
	return log(f)/log((float)2);
}

/* _hoops_RIIRA: _hoops_SR _hoops_HHGC _hoops_IS _hoops_CSGA _hoops_IRS _hoops_APPHH _hoops_IIGR _hoops_RH _hoops_IASC _hoops_CISAR _hoops_HGPP _hoops_SGS _hoops_IRS _hoops_RAGA
 * _hoops_PHI _hoops_IIGR _hoops_HSGS _hoops_SAIIA _hoops_GRS _hoops_SHH _hoops_RHIAA.	_hoops_RCPA _hoops_AA _hoops_SGS, _hoops_SR _hoops_ARPR _hoops_PGCR "_hoops_SCAH _hoops_PIRRR" (_hoops_IGRC
 * _hoops_SAHR _hoops_SIRGR _hoops_IIGR _hoops_SGI), _hoops_PPR _hoops_CSGA _hoops_RSH _hoops_AHPH _hoops_HSGS _hoops_SCAH _hoops_CRGIA _hoops_SR _hoops_HGCR */
local int _hoops_IRSHI(
		int pcount, 
		const float *points, 
		const float *min, 
		const float *max, 
		float _hoops_CRSHI) 
{
	unsigned int *flags, *_hoops_SRSHI;
	int d, i, j, k, _hoops_GASHI, _hoops_RASHI, _hoops_AASHI, _hoops_PASHI, _hoops_ARAHR, _hoops_HASHI, n, m, _hoops_IASHI, _hoops_CASHI;
	int _hoops_SASHI, _hoops_GPSHI;
	int _hoops_RPSHI, _hoops_APSHI;
	int _hoops_PPSHI;
	float _hoops_IGHCP[3], _hoops_SRCIH, _hoops_HPSHI;
	unsigned int key, _hoops_IPSHI, index;

	_hoops_PASHI = (int)(pcount * _hoops_CRSHI);
	_hoops_PPSHI = 4;
	_hoops_GASHI = (int)(HI_Sqrt(_hoops_PASHI / 2));
	do {
		/* _hoops_ARPR 2^_hoops_SPHAI _hoops_CPSHI "_hoops_SPSHI" _hoops_IGIAR _hoops_GRR _hoops_SPIS*/
		m = (int)_hoops_HRSHI(_hoops_GASHI) + 1;
		_hoops_CASHI = m-1;
		n = m+8;
		_hoops_SASHI = (int)pow((float)2, n);
		_hoops_RPSHI = _hoops_SASHI / 2;
		_hoops_GPSHI = _hoops_SASHI - 1;
		_hoops_APSHI = _hoops_RPSHI - 1;
		ALLOC_ARRAY (flags, _hoops_SASHI, unsigned int);
		ALLOC_ARRAY (_hoops_SRSHI, _hoops_RPSHI, unsigned int);
		ZERO_ARRAY (flags, _hoops_SASHI, unsigned int);
		ZERO_ARRAY (_hoops_SRSHI, _hoops_RPSHI, unsigned int);
		/* _hoops_SR _hoops_CHR _hoops_GRP 32-_hoops_IGRH _hoops_APPC _hoops_AGRIR _hoops_GAR _hoops_IGRH _hoops_AAAPR, _hoops_HIS _hoops_SR _hoops_PAH _hoops_ASH 2^5 _hoops_RRI _hoops_SGI */
		n += 5;	 
		_hoops_IASHI = n-1;
		/* _hoops_IH _hoops_GRR _hoops_PHI _hoops_CSGA _hoops_IRS _hoops_SIPIR _hoops_SGS _hoops_GRS _hoops_CSRA _hoops_CPHH _hoops_IS _hoops_CCIR _hoops_HII 0.._hoops_GHSHI-1 */
		if (max[0] - min[0] != 0)
			_hoops_IGHCP[0] = (float)(_hoops_GASHI-1) / (max[0] - min[0]);
		else
			_hoops_IGHCP[0] = 0;
		if (max[1] - min[1] != 0)
			_hoops_IGHCP[1] = (float)(_hoops_GASHI-1) / (max[1] - min[1]);
		else
			_hoops_IGHCP[1] = 0;
		if (max[2] - min[2] != 0)
			_hoops_IGHCP[2] = (float)(_hoops_GASHI-1) / (max[2] - min[2]);
		else
			_hoops_IGHCP[2] = 0;
		_hoops_ARAHR = 0;
		_hoops_HASHI = 0;
		for (d=0; d<pcount; d++) {
			i = (int)((points[d*3 + 0] - min[0]) * _hoops_IGHCP[0]);
			j = (int)((points[d*3 + 1] - min[1]) * _hoops_IGHCP[1]);
			k = (int)((points[d*3 + 2] - min[2]) * _hoops_IGHCP[2]);
			key = ((i<<(n-m))^(j<<((n-m)/2))^k);
			_hoops_IPSHI = 0x1 << (key & 0x1f);
			index = (key>>5) & _hoops_GPSHI;
			if (!(flags[index] & _hoops_IPSHI)) {
				flags[index] |= _hoops_IPSHI;
				_hoops_ARAHR++;
			}
			i /= 2;
			j /= 2;
			k /= 2;
			key = ((i<<(_hoops_IASHI-_hoops_CASHI))^(j<<((_hoops_IASHI-_hoops_CASHI)/2))^k);
			_hoops_IPSHI = 0x1 << (key & 0x1f);
			index = (key>>5) & _hoops_APSHI;
			if (!(_hoops_SRSHI[index] & _hoops_IPSHI)) {
				_hoops_SRSHI[index] |= _hoops_IPSHI;
				_hoops_HASHI++;
			}
		}
	
		FREE_ARRAY (flags, _hoops_SASHI, unsigned int);
		flags = null;
		FREE_ARRAY (_hoops_SRSHI, _hoops_RPSHI, unsigned int);
		_hoops_SRSHI = null;

		_hoops_SRCIH = (float)_hoops_PASHI / _hoops_HASHI;
		_hoops_HPSHI = (float)_hoops_ARAHR / _hoops_HASHI;
		if (2*_hoops_ARAHR < _hoops_PASHI) {
			_hoops_GASHI *= 4;
			_hoops_PPSHI--;
		}
		else if (_hoops_HASHI/2 > _hoops_PASHI) {
			_hoops_GASHI /= 4;
			_hoops_PPSHI--;
		}
		else 
			_hoops_PPSHI = 0;
	} while (_hoops_PPSHI);
	_hoops_AASHI = (int)((_hoops_GASHI / 2) * pow(2.0f, _hoops_SRCIH / _hoops_HPSHI)) - 1;
	_hoops_RASHI = (int)pow((float)_hoops_PASHI, 1.0f / 3.0f);
	if (_hoops_AASHI < _hoops_RASHI) 
		_hoops_AASHI = _hoops_RASHI;
	if (_hoops_AASHI > 2048)
		_hoops_AASHI = 2048;
	return _hoops_AASHI;
} /* _hoops_RSGR _hoops_API _hoops_RHSHI */


local void _hoops_AHSHI (const _hoops_SHHHI *q, _hoops_HGSPI *m) {
	m->row[0]._hoops_GGSPI[0] = q->a2;
	m->row[0]._hoops_GGSPI[1] = q->_hoops_HASSR;
	m->row[0]._hoops_GGSPI[2] = q->_hoops_IASSR;
	m->row[1]._hoops_GGSPI[0] = q->_hoops_HASSR;
	m->row[1]._hoops_GGSPI[1] = q->_hoops_CHHI;
	m->row[1]._hoops_GGSPI[2] = q->_hoops_CASSR;
	m->row[2]._hoops_GGSPI[0] = q->_hoops_IASSR;
	m->row[2]._hoops_GGSPI[1] = q->_hoops_CASSR;
	m->row[2]._hoops_GGSPI[2] = q->_hoops_PIGCR;
}


local void _hoops_SAIAR(double *r, const double *u, const double *v, int _hoops_GHGIR) {
	if (_hoops_GHGIR == 3) {
		r[0] =	(u[1] * v[2]) - (v[1] * u[2]); 
		r[1] = -(u[0] * v[2]) + (v[0] * u[2]);
		r[2] =	(u[0] * v[1]) - (v[0] * u[1]);	
	}
}

local double _hoops_SSRP(const double *u, const double *v, int _hoops_GHGIR) {
	int i;
	double _hoops_HAGR=0.0;	 

	for (i = 0; i < _hoops_GHGIR; i++) 
		_hoops_HAGR += u[i]*v[i];  
	return _hoops_HAGR;
}

local void _hoops_AHAHH (double *r, const double *u, const double d, int _hoops_GHGIR) {
	int i;
	for (i = 0; i < _hoops_GHGIR; i++) 
		r[i] = u[i] / d;
}

local void _hoops_PHSHI (_hoops_RGSPI *_hoops_RRSPI, const _hoops_HGSPI *_hoops_RAGH, int i) { 
	_hoops_RRSPI->_hoops_GGSPI[0] = _hoops_RAGH->row[0]._hoops_GGSPI[i];
	_hoops_RRSPI->_hoops_GGSPI[1] = _hoops_RAGH->row[1]._hoops_GGSPI[i];
	_hoops_RRSPI->_hoops_GGSPI[2] = _hoops_RAGH->row[2]._hoops_GGSPI[i]; 
}

local double _hoops_HHSHI (_hoops_HGSPI *_hoops_RHCHI, const _hoops_HGSPI *_hoops_RAGH) {
	_hoops_HGSPI temp, _hoops_APIHI;
	double d;

	/* _hoops_GRAS _hoops_RH _hoops_GGRA: _hoops_GGRA (&_hoops_RAIGR, _hoops_PHCHI); */
	_hoops_SAIAR (_hoops_APIHI.row[0]._hoops_GGSPI, _hoops_RAGH->row[1]._hoops_GGSPI, _hoops_RAGH->row[2]._hoops_GGSPI, 3);
	_hoops_SAIAR (_hoops_APIHI.row[1]._hoops_GGSPI, _hoops_RAGH->row[2]._hoops_GGSPI, _hoops_RAGH->row[0]._hoops_GGSPI, 3);
	_hoops_SAIAR (_hoops_APIHI.row[2]._hoops_GGSPI, _hoops_RAGH->row[0]._hoops_GGSPI, _hoops_RAGH->row[1]._hoops_GGSPI, 3);

	d = _hoops_SSRP (_hoops_APIHI.row[0]._hoops_GGSPI, _hoops_RAGH->row[0]._hoops_GGSPI, 3);

	if (d==0.0)
		return 0.0;
	/* _hoops_GRAS _hoops_RH _hoops_HGICR: _hoops_HGICR (&_hoops_IRHP, &_hoops_RAIGR); */
	_hoops_PHSHI (&(temp.row[0]), &_hoops_APIHI, 0);
	_hoops_PHSHI (&(temp.row[1]), &_hoops_APIHI, 1);
	_hoops_PHSHI (&(temp.row[2]), &_hoops_APIHI, 2);

	_hoops_AHAHH (_hoops_RHCHI->row[0]._hoops_GGSPI, temp.row[0]._hoops_GGSPI, d, 3);
	_hoops_AHAHH (_hoops_RHCHI->row[1]._hoops_GGSPI, temp.row[1]._hoops_GGSPI, d, 3);
	_hoops_AHAHH (_hoops_RHCHI->row[2]._hoops_GGSPI, temp.row[2]._hoops_GGSPI, d, 3);
	return d;
}

local void _hoops_IHSHI (_hoops_RGSPI *_hoops_RRSPI, const _hoops_SHHHI *q) { 
	_hoops_RRSPI->_hoops_GGSPI[0] = q->_hoops_GPSSR;
	_hoops_RRSPI->_hoops_GGSPI[1] = q->_hoops_HIHHI;
	_hoops_RRSPI->_hoops_GGSPI[2] = q->_hoops_GSHIR;
}

local void _hoops_CHSHI (_hoops_RGSPI *_hoops_RRSPI, const _hoops_HGSPI *_hoops_RAGH, const _hoops_RGSPI *_hoops_ISPI) {
	_hoops_RRSPI->_hoops_GGSPI[0] = _hoops_SSRP (_hoops_RAGH->row[0]._hoops_GGSPI, _hoops_ISPI->_hoops_GGSPI, 3); 
	_hoops_RRSPI->_hoops_GGSPI[1] = _hoops_SSRP (_hoops_RAGH->row[1]._hoops_GGSPI, _hoops_ISPI->_hoops_GGSPI, 3); 
	_hoops_RRSPI->_hoops_GGSPI[2] = _hoops_SSRP (_hoops_RAGH->row[2]._hoops_GGSPI, _hoops_ISPI->_hoops_GGSPI, 3);
}

local void _hoops_SHSHI	(double *r, const double *u, int _hoops_GHGIR) {
	int i;
	for (i = 0; i < _hoops_GHGIR; i++) 
		r[i] = -u[i];
}

local int optimize (const _hoops_SHHHI *q, _hoops_RGSPI *v) {
	_hoops_HGSPI _hoops_PAIHI, _hoops_HAIHI;
	double _hoops_HHIPA;
	_hoops_RGSPI _hoops_IAIHI;

	_hoops_AHSHI (q, &_hoops_HAIHI);
	_hoops_HHIPA = _hoops_HHSHI (&_hoops_PAIHI, &_hoops_HAIHI);
	if (_hoops_HSCIA(_hoops_HHIPA, 0.0, 1e-12f))
		return 0;

	_hoops_IHSHI (&_hoops_IAIHI, q);
	_hoops_CHSHI (v, &_hoops_PAIHI, &_hoops_IAIHI);
	_hoops_SHSHI (v->_hoops_GGSPI, v->_hoops_GGSPI, 3);

	return 1;
}

local void _hoops_GISHI (_hoops_SHHHI *q, double a, double b, double c, double d) {
	q->a2 = a*a;  q->_hoops_HASSR = a*b;	q->_hoops_IASSR = a*c;  q->_hoops_GPSSR = a*d;
	q->_hoops_CHHI = b*b;  q->_hoops_CASSR = b*c;	q->_hoops_HIHHI = b*d;
	q->_hoops_PIGCR = c*c;  q->_hoops_GSHIR = c*d;
	q->_hoops_RIGCR = d*d;
	q->r = 1;
}

local void _hoops_RISHI (_hoops_SHHHI *_hoops_RRIHI, const _hoops_SHHHI *_hoops_AICIH, const _hoops_SHHHI *_hoops_ARIHI) {
	/* _hoops_GAGP _hoops_CCAC*/
	_hoops_RRIHI->r  = _hoops_AICIH->r + _hoops_ARIHI->r;

	/* _hoops_GAGP _hoops_AIAHR*/
	_hoops_RRIHI->a2 = _hoops_AICIH->a2 + _hoops_ARIHI->a2;
	_hoops_RRIHI->_hoops_HASSR = _hoops_AICIH->_hoops_HASSR + _hoops_ARIHI->_hoops_HASSR;
	_hoops_RRIHI->_hoops_IASSR = _hoops_AICIH->_hoops_IASSR + _hoops_ARIHI->_hoops_IASSR;  
	_hoops_RRIHI->_hoops_GPSSR = _hoops_AICIH->_hoops_GPSSR + _hoops_ARIHI->_hoops_GPSSR;

	_hoops_RRIHI->_hoops_CHHI = _hoops_AICIH->_hoops_CHHI + _hoops_ARIHI->_hoops_CHHI;  
	_hoops_RRIHI->_hoops_CASSR = _hoops_AICIH->_hoops_CASSR + _hoops_ARIHI->_hoops_CASSR;  
	_hoops_RRIHI->_hoops_HIHHI = _hoops_AICIH->_hoops_HIHHI + _hoops_ARIHI->_hoops_HIHHI;

	_hoops_RRIHI->_hoops_PIGCR = _hoops_AICIH->_hoops_PIGCR + _hoops_ARIHI->_hoops_PIGCR;  
	_hoops_RRIHI->_hoops_GSHIR = _hoops_AICIH->_hoops_GSHIR + _hoops_ARIHI->_hoops_GSHIR;

	_hoops_RRIHI->_hoops_RIGCR = _hoops_AICIH->_hoops_RIGCR + _hoops_ARIHI->_hoops_RIGCR;
}

local int _hoops_AISHI (const _hoops_SHHHI *q, float *_hoops_PAGR) {
	_hoops_RGSPI v;
	if (optimize (q, &v)) {
		_hoops_PAGR[0] = (float) v._hoops_GGSPI[0];
		_hoops_PAGR[1] = (float) v._hoops_GGSPI[1];
		_hoops_PAGR[2] = (float) v._hoops_GGSPI[2];
		return 1;
	}
	return 0;
}


/* _hoops_RH _hoops_PISHI _hoops_PAHGA _hoops_HCR _hoops_IIGR _hoops_RH _hoops_HPHS _hoops_IHIA _hoops_CCA _hoops_IRS _hoops_CGGHA _hoops_GPHA
 * _hoops_IH _hoops_CPS _hoops_SGS _hoops_RHCI _hoops_IS _hoops_SIHGA _hoops_HAS,_hoops_PPHR,_hoops_ARGI */
typedef struct {
	/* _hoops_RRAS _hoops_IIGR _hoops_ISCRH _hoops_HII _hoops_PGAP _hoops_SR _hoops_GRS _hoops_SGHHR _hoops_IS _hoops_GRAS _hoops_PCCP _hoops_RRHAR _hoops_GPHA _hoops_ACAGR */
	_hoops_SHHHI _hoops_HISHI; 
	int i, j, k, id;
	/* _hoops_IIPGA _hoops_SGGPR _hoops_GGR _hoops_AGIR _hoops_RH _hoops_CSPHI _hoops_PAH'_hoops_RA _hoops_SHH _hoops_SSAAA */
	float x, y, z;		
	float _hoops_HAHAP; /* _hoops_IS _hoops_HHSA 8-_hoops_RAPSR _hoops_AHSGP */
} _hoops_IISHI;

typedef struct {
	_hoops_IISHI *data;
	int allocated;
	int used;
} _hoops_CISHI;

typedef struct {
	_hoops_CISHI *_hoops_SISHI;
	int _hoops_GCSHI;
	int _hoops_RCSHI;

	const float *min, *max;
	int _hoops_ACSHI;
	float _hoops_IGHCP[3];

	int *faces;
	int _hoops_PCSHI;
	int _hoops_HCSHI;

	int pcount;
	float *points;
} _hoops_CRRR;


local void _hoops_ICSHI (_hoops_CRRR *m, const float *min, const float *max, 
		int _hoops_GASHI, int _hoops_IPSAA) {
	int ii;
	_hoops_CISHI *node;

	m->_hoops_HCSHI = 0;
	m->_hoops_PCSHI = 100;
	ALLOC_ARRAY (m->faces, m->_hoops_PCSHI, int);
	m->pcount = 0;
	m->points = null;
	m->min = min;
	m->max = max;
	m->_hoops_ACSHI = _hoops_GASHI;

	/* _hoops_SPHAI->_hoops_CCSHI _hoops_PIHA _hoops_SHH _hoops_IRS _hoops_RIIR _hoops_IIGR 2 _hoops_HIS _hoops_SGS _hoops_SR _hoops_PAH _hoops_SGH _hoops_IRS _hoops_PISH */
	m->_hoops_GCSHI = 1;
	while (m->_hoops_GCSHI < _hoops_IPSAA)
		m->_hoops_GCSHI = m->_hoops_GCSHI << 1;
	ALLOC_ARRAY (m->_hoops_SISHI, m->_hoops_GCSHI, _hoops_CISHI);
	for	(ii = 0; ii < m->_hoops_GCSHI; ii++) {
		node = &m->_hoops_SISHI[ii];
		node->allocated = 2;
		ALLOC_ARRAY_ALIGNED (node->data, node->allocated, _hoops_IISHI, 8);
		node->used = 0;
	}
	m->_hoops_RCSHI = m->_hoops_GCSHI - 1;

	if (max[0] - min[0] != 0)
		m->_hoops_IGHCP[0] = (float)(_hoops_GASHI-1) / (max[0] - min[0]);
	else
		m->_hoops_IGHCP[0] = 0;
	if (max[1] - min[1] != 0)
		m->_hoops_IGHCP[1] = (float)(_hoops_GASHI-1) / (max[1] - min[1]);
	else
		m->_hoops_IGHCP[1] = 0;
	if (max[2] - min[2] != 0)
		m->_hoops_IGHCP[2] = (float)(_hoops_GASHI-1) / (max[2] - min[2]);
	else
		m->_hoops_IGHCP[2] = 0;
}

local void _hoops_SCSHI (_hoops_CRRR *m) {
	int i;

	FREE_ARRAY (m->points, 3 * m->pcount, float);
	m->points = null;
	FREE_ARRAY (m->faces, m->_hoops_PCSHI, int);
	m->faces = null;
	for (i = 0; i < m->_hoops_GCSHI; i++) {
		FREE_ARRAY_ALIGNED (m->_hoops_SISHI[i].data, m->_hoops_SISHI[i].allocated, _hoops_IISHI, 8);
		m->_hoops_SISHI[i].data = null;
	}
	FREE_ARRAY (m->_hoops_SISHI, m->_hoops_GCSHI, _hoops_CISHI);
	m->_hoops_SISHI = null;
} /* _hoops_RSGR _hoops_API _hoops_GSSHI */


#define _hoops_RSSHI(i,j,k,mask) (((i << 6) ^ (j << 3) ^ k) & mask)


local int _hoops_ASSHI (_hoops_CRRR *m, float x, float y, float z, _hoops_IISHI **_hoops_PAGR) {
	int i, j, k, ii, _hoops_HGGI;
	_hoops_CISHI *node;
	_hoops_IISHI *v;

	i = (int)((x - m->min[0]) * m->_hoops_IGHCP[0]);
	j = (int)((y - m->min[1]) * m->_hoops_IGHCP[1]);
	k = (int)((z - m->min[2]) * m->_hoops_IGHCP[2]);
	_hoops_HGGI = _hoops_RSSHI(i,j,k,m->_hoops_RCSHI);
	node = &m->_hoops_SISHI[_hoops_HGGI];
	v = node->data;
	for (ii = 0; ii < node->used; ii++) {
		if ((i == v->i) &&
			(j == v->j) &&
			(k == v->k)) {
			*_hoops_PAGR = v;
			return 1;
		}
		v++;
	}
	*_hoops_PAGR = null;
	return 0;
}

local void _hoops_PSSHI (_hoops_CRRR *m, float x, float y, float z, int id) {
	int i, j, k, _hoops_HGGI;
	_hoops_CISHI *node;
	_hoops_IISHI *v, *temp;

	i = (int)((x - m->min[0]) * m->_hoops_IGHCP[0]);
	j = (int)((y - m->min[1]) * m->_hoops_IGHCP[1]);
	k = (int)((z - m->min[2]) * m->_hoops_IGHCP[2]);
	_hoops_HGGI = _hoops_RSSHI(i,j,k,m->_hoops_RCSHI);
	node = &m->_hoops_SISHI[_hoops_HGGI];
	if (node->used == node->allocated) {
		node->allocated *= 2;
		ALLOC_ARRAY_ALIGNED (temp, node->allocated, _hoops_IISHI, 8);
		COPY_MEMORY (node->data, node->used * sizeof (_hoops_IISHI), temp);
		FREE_ARRAY_ALIGNED (node->data, node->used, _hoops_IISHI, 8);
		node->data = temp;
	}
	v = &node->data[node->used++];
	v->i = i;
	v->j = j;
	v->k = k;
	v->id = id;
	v->x = x;
	v->y = y;
	v->z = z;
	v->_hoops_HAHAP = 0;
	_hoops_GISHI (&v->_hoops_HISHI, 0.0, 0.0, 0.0, 0.0);
	m->pcount++;
} /* _hoops_RSGR _hoops_API _hoops_HSSHI */


local void _hoops_ISSHI (_hoops_CRRR *m, int _hoops_HAGR) {
	if (m->_hoops_HCSHI == m->_hoops_PCSHI) {
		int *temp;

		m->_hoops_PCSHI *= 2;
		ALLOC_ARRAY (temp, m->_hoops_PCSHI, int);
		COPY_MEMORY (m->faces, m->_hoops_HCSHI * sizeof (int), temp);
		FREE_ARRAY (m->faces, m->_hoops_HCSHI, int);
		m->faces = temp;
	}
	m->faces[m->_hoops_HCSHI++] = _hoops_HAGR;
} /* _hoops_RSGR _hoops_API _hoops_CSSHI */


/* _hoops_AHGHR _hoops_HRSP _hoops_SAPS _hoops_PPSR _hoops_CPHH, _hoops_HGCR _hoops_PCCP _hoops_SSSHI _hoops_IPPA _hoops_CGSSR.
 * _hoops_GCIH _hoops_HPP _hoops_ARRAR _hoops_IS _hoops_GHGPR _hoops_HIS _hoops_SGS _hoops_RH _hoops_GIRPA _hoops_IISRR _hoops_HS _hoops_CASH _hoops_GPPS */
local void _hoops_GGGII (const float *_hoops_RGGII, const float *_hoops_AGGII, const float *_hoops_PGGII,		
				double *a, double *b, double *c, double *d) {
	double _hoops_ISPI[3], _hoops_CSPI[3], _hoops_SSPI[3];
	_hoops_ISPI[0] = _hoops_RGGII[0];	  _hoops_ISPI[1] = _hoops_RGGII[1];	_hoops_ISPI[2] = _hoops_RGGII[2];
	_hoops_CSPI[0] = _hoops_AGGII[0];	  _hoops_CSPI[1] = _hoops_AGGII[1];	_hoops_CSPI[2] = _hoops_AGGII[2];
	_hoops_SSPI[0] = _hoops_PGGII[0];	  _hoops_SSPI[1] = _hoops_PGGII[1];	_hoops_SSPI[2] = _hoops_PGGII[2];
	*a = _hoops_ISPI[1] * (_hoops_CSPI[2] - _hoops_SSPI[2]) + _hoops_CSPI[1] * (_hoops_SSPI[2] - _hoops_ISPI[2]) + _hoops_SSPI[1] * (_hoops_ISPI[2] - _hoops_CSPI[2]);
	*b = _hoops_ISPI[2] * (_hoops_CSPI[0] - _hoops_SSPI[0]) + _hoops_CSPI[2] * (_hoops_SSPI[0] - _hoops_ISPI[0]) + _hoops_SSPI[2] * (_hoops_ISPI[0] - _hoops_CSPI[0]);
	*c = _hoops_ISPI[0] * (_hoops_CSPI[1] - _hoops_SSPI[1]) + _hoops_CSPI[0] * (_hoops_SSPI[1] - _hoops_ISPI[1]) + _hoops_SSPI[0] * (_hoops_ISPI[1] - _hoops_CSPI[1]);
	*d = - (*a * _hoops_ISPI[0] + *b * _hoops_ISPI[1] + *c * _hoops_ISPI[2]);
} /* _hoops_RSGR _hoops_API _hoops_HGGII */


local void _hoops_IGGII (_hoops_CRRR *m, const int *face, const float *points) {
	int ii, count;
	double a, b, c, d;
	const float *v, *_hoops_ISPI, *_hoops_CSPI, *_hoops_SSPI;
	_hoops_SHHHI _hoops_CGGII;
	_hoops_IISHI **_hoops_ICPHI, *_hoops_SGGII[7];
	int _hoops_GRGII = 0;

	if (face[0] < 3)
		return;
	/* _hoops_GCSRP _hoops_HPGR _hoops_SPR _hoops_CRGP _hoops_HSAR _hoops_RH _hoops_GC _hoops_GGR _hoops_RRGII _hoops_IS _hoops_ASSS _hoops_IH _hoops_IRS _hoops_IRAP _hoops_HPGR _hoops_RH _hoops_HSPP */
	if (face[0] > 6) {
		_hoops_GRGII = 2+face[0];
		ALLOC_ARRAY (_hoops_ICPHI, _hoops_GRGII, _hoops_IISHI *);
	}
	else
		_hoops_ICPHI = _hoops_SGGII;

	/* _hoops_ARGII _hoops_RH _hoops_CSPHI _hoops_SGS _hoops_PRGII _hoops_RH _hoops_HRGII _hoops_RRAI _hoops_HPP _hoops_RGR _hoops_SAGHR _hoops_HSP */
	_hoops_ISPI = &points[3*face[1]];
	_hoops_CSPI = &points[3*face[2]];
	_hoops_SSPI = &points[3*face[3]];
	_hoops_GGGII (_hoops_ISPI, _hoops_CSPI, _hoops_SSPI, &a, &b, &c, &d);	   
	_hoops_GISHI (&_hoops_CGGII, a, b, c, d);

	_hoops_ICPHI[0] = null;
	count = 0;
	for (ii = 1; ii <= face[0]; ii++) {
		v = &points[3*face[ii]];
		/* _hoops_HGCR _hoops_IRGII _hoops_PPARR */
		_hoops_ASSHI (m, v[0], v[1], v[2], &_hoops_ICPHI[ii]);
		if (_hoops_ICPHI[ii] != _hoops_ICPHI[ii-1])
			count++;
		/* _hoops_GGCR _hoops_CSPHI (_hoops_SISH,_hoops_CRGII,_hoops_SRGII) */
		_hoops_RISHI (&_hoops_ICPHI[ii]->_hoops_HISHI, &_hoops_ICPHI[ii]->_hoops_HISHI, &_hoops_CGGII);
	}
	/* _hoops_CGP _hoops_RH _hoops_CGHI _hoops_GPHA == _hoops_RH _hoops_SRS _hoops_SPR, _hoops_SR _hoops_HS _hoops_SPR _hoops_CRGP _hoops_HSGS _hoops_PIRA. */
	if (_hoops_ICPHI[face[0]] == _hoops_ICPHI[1])
		count--;
	_hoops_ICPHI[0] = _hoops_ICPHI[face[0]]; /* _hoops_IPS _hoops_RH _hoops_CGHI _hoops_IS _hoops_RH _hoops_HSPP */
	/* _hoops_GAGII _hoops_IRS _hoops_HSP _hoops_IS _hoops_RH _hoops_IIPR _hoops_HSP _hoops_HIGR _hoops_RPP _hoops_RH _hoops_PHI _hoops_IIGR _hoops_HSGS _hoops_GIHA _hoops_RHIAA _hoops_CSAP _hoops_HPGR _hoops_CHGC 3.
	 * _hoops_PAGA: _hoops_RH _hoops_SHRRR _hoops_IISA _hoops_GH _hoops_CCA 0 _hoops_IH _hoops_RH _hoops_AGIR _hoops_CAS _hoops_RPR _hoops_CGH _hoops_SHH _hoops_GPCPR 1, 
	 * _hoops_HIH _hoops_SGS _hoops_PAHA'_hoops_RA _hoops_RPSHR. */
	if (count >= 3) {
		_hoops_ISSHI (m, count);
		for (ii = 1; ii <= face[0]; ii++) {
			if (_hoops_ICPHI[ii] != _hoops_ICPHI[ii-1])
				_hoops_ISSHI (m, _hoops_ICPHI[ii]->id);
		}
	}
	/* _hoops_RPP _hoops_SR _hoops_PSPP _hoops_CPHP (_hoops_PGAP _hoops_CGH _hoops_PAHH _hoops_SHH _hoops_RRRIR _hoops_RAGII), _hoops_SR _hoops_HS _hoops_IS _hoops_CIH _hoops_SCH */
	if (_hoops_ICPHI != _hoops_SGGII)
		FREE_ARRAY (_hoops_ICPHI, _hoops_GRGII, _hoops_IISHI *);
} /* _hoops_RSGR _hoops_API _hoops_AAGII */


local void _hoops_PAGII (_hoops_CRRR *m) {
	int ii, _hoops_ICRHH, i, j, k;
	_hoops_CISHI *node;
	float *_hoops_HAGII;
	_hoops_IISHI *_hoops_HAHCR;
	int _hoops_IA;
	float *_hoops_IAGII[3], _hoops_CAGII;
	
	/* _hoops_SISR */
	ALLOC_ARRAY (_hoops_IAGII[0], m->_hoops_ACSHI + 1, float);
	if (m->_hoops_IGHCP[0] != 0)
		_hoops_CAGII = 1.0f / m->_hoops_IGHCP[0];
	else
		_hoops_CAGII = 0;
	for (ii = 0; ii < m->_hoops_ACSHI+1; ii++)
		_hoops_IAGII[0][ii] = m->min[0] + _hoops_CAGII * ii;
	/* _hoops_HAPC */
	ALLOC_ARRAY (_hoops_IAGII[1], m->_hoops_ACSHI + 1, float);
	if (m->_hoops_IGHCP[1] != 0)
		_hoops_CAGII = 1.0f / m->_hoops_IGHCP[1];
	else
		_hoops_CAGII = 0;
	for (ii = 0; ii < m->_hoops_ACSHI+1; ii++)
		_hoops_IAGII[1][ii] = m->min[1] + _hoops_CAGII * ii;
	/* _hoops_SSH */
	ALLOC_ARRAY (_hoops_IAGII[2], m->_hoops_ACSHI + 1, float);
	if (m->_hoops_IGHCP[2] != 0)
		_hoops_CAGII = 1.0f / m->_hoops_IGHCP[2];
	else
		_hoops_CAGII = 0;
	for (ii = 0; ii < m->_hoops_ACSHI+1; ii++)
		_hoops_IAGII[2][ii] = m->min[2] + _hoops_CAGII * ii;

	ALLOC_ARRAY (m->points, 3 * m->pcount, float);
	for (ii = 0; ii < m->_hoops_GCSHI; ii++) {
		node = &m->_hoops_SISHI[ii];
		for (_hoops_ICRHH = 0; _hoops_ICRHH < node->used; _hoops_ICRHH++) {
			_hoops_HAHCR = &node->data[_hoops_ICRHH];
			i = (int)((_hoops_HAHCR->x - m->min[0]) * m->_hoops_IGHCP[0]);
			j = (int)((_hoops_HAHCR->y - m->min[1]) * m->_hoops_IGHCP[1]);
			k = (int)((_hoops_HAHCR->z - m->min[2]) * m->_hoops_IGHCP[2]);
			_hoops_HAGII = m->points + (3 * (_hoops_HAHCR->id));
			_hoops_IA = _hoops_AISHI (&_hoops_HAHCR->_hoops_HISHI, _hoops_HAGII);
			if (!_hoops_IA ||
				_hoops_HAGII[0] < _hoops_IAGII[0][i] ||
				_hoops_HAGII[1] < _hoops_IAGII[1][j] ||
				_hoops_HAGII[2] < _hoops_IAGII[2][k] ||
				_hoops_HAGII[0] > _hoops_IAGII[0][i+1] ||
				_hoops_HAGII[1] > _hoops_IAGII[1][j+1] ||
				_hoops_HAGII[2] > _hoops_IAGII[2][k+1]) {
				_hoops_HAGII[0] = _hoops_HAHCR->x;
				_hoops_HAGII[1] = _hoops_HAHCR->y;
				_hoops_HAGII[2] = _hoops_HAHCR->z;
			}
		}
	}
	FREE_ARRAY (_hoops_IAGII[0], m->_hoops_ACSHI + 1, float);
	FREE_ARRAY (_hoops_IAGII[1], m->_hoops_ACSHI + 1, float);
	FREE_ARRAY (_hoops_IAGII[2], m->_hoops_ACSHI + 1, float);
} /* _hoops_RSGR _hoops_API _hoops_SAGII */


local _hoops_HAPHA *_hoops_GPGII (int pcount, const float *points, int _hoops_RPGII, const int *faces, 
				const float *min, const float *max, int _hoops_AASHI) {
	int ii, id, _hoops_IPSAA;
	float x, y, z;
	int const *_hoops_PPHPA, *end;
	_hoops_CRRR *m;
	_hoops_IISHI *_hoops_HAHCR;
	_hoops_HAPHA *_hoops_PAGR;
	int *_hoops_PHAS;

	ALLOC (m, _hoops_CRRR);	
	_hoops_IPSAA = pcount / 2;
	_hoops_ICSHI (m, min, max, _hoops_AASHI, _hoops_IPSAA);

	/* _hoops_CAHA _hoops_GGSR _hoops_GPCPR _hoops_RSH _hoops_AHPH _hoops_HSGS _hoops_SPSHI _hoops_SR _hoops_HS, _hoops_RH _hoops_SIA
	 * _hoops_GAPA _hoops_RHGS _hoops_PPR _hoops_CCAH _hoops_RSSA, _hoops_PPR _hoops_HSPC _hoops_RH _hoops_IIPGA _hoops_SGGPR _hoops_HSH */
	ALLOC_ARRAY (_hoops_PHAS, pcount, int);
	id = 0;
	for	 (ii = 0; ii < pcount; ii++) {
		x = points[ii*3 + 0];
		y = points[ii*3 + 1];
		z = points[ii*3 + 2];
		if (!_hoops_ASSHI (m, x, y, z, &_hoops_HAHCR)) {
			_hoops_PSSHI (m, x, y, z, id);
			_hoops_PHAS[ii] = id;
			id++;
		}
		else {
			_hoops_PHAS[ii] = _hoops_HAHCR->id;
		}
	}

	_hoops_PPHPA = faces;
	end = _hoops_PPHPA + _hoops_RPGII;
	while (_hoops_PPHPA < end) {
		if (_hoops_PPHPA[0] > 0) {
			/* _hoops_IRS _hoops_SHISR _hoops_HSP -- _hoops_GGCR _hoops_SCH _hoops_IS _hoops_RH _hoops_SARR */
			_hoops_IGGII (m, _hoops_PPHPA, points);
			_hoops_PPHPA += _hoops_PPHPA[0] + 1;
		}
		else {
			/* _hoops_IRS _hoops_RCCPR _hoops_GGR _hoops_RH _hoops_PGHC _hoops_HSP -- _hoops_SSPC _hoops_SCH */
			_hoops_PPHPA += -_hoops_PPHPA[0] + 1;
		}
	}

	_hoops_PAGII (m);

	ALLOC (_hoops_PAGR, _hoops_HAPHA);
	_hoops_PAGR->_hoops_IAPHA.pcount = m->pcount;
	if (m->pcount > 0) {
		ALLOC_ARRAY_ALIGNED (_hoops_PAGR->_hoops_IAPHA.points, 3 * m->pcount, float, 16);
		COPY_MEMORY (m->points, 3 * m->pcount * sizeof (float), _hoops_PAGR->_hoops_IAPHA.points);
	}
	else
		_hoops_PAGR->_hoops_IAPHA.points = null;

	_hoops_PAGR->_hoops_IAPHA._hoops_RHGIR = m->_hoops_HCSHI;
	if (m->_hoops_HCSHI > 0) {
		ALLOC_ARRAY (_hoops_PAGR->_hoops_IAPHA.faces, m->_hoops_HCSHI, int);
		COPY_MEMORY (m->faces, m->_hoops_HCSHI * sizeof (int), _hoops_PAGR->_hoops_IAPHA.faces);
	}
	else
		_hoops_PAGR->_hoops_IAPHA.faces = null;

	_hoops_SCSHI (m);
	_hoops_PAGR->_hoops_CAPHA = pcount;
	_hoops_PAGR->_hoops_PHAS = _hoops_PHAS;
	FREE (m, _hoops_CRRR);
	return _hoops_PAGR;
} /* _hoops_RSGR _hoops_API _hoops_APGII */


local _hoops_HAPHA *_hoops_PPGII (int pcount, const float *points, 
				const Tristrip *t, 
				const float *min, const float *max, int _hoops_AASHI) {
	int ii, _hoops_ICRHH, id, _hoops_IPSAA, length;
	float x, y, z;
	int const *_hoops_PPHPA;
	_hoops_CRRR *m;
	_hoops_IISHI *_hoops_HAHCR;
	_hoops_HAPHA *_hoops_PAGR;
	int _hoops_RCHHR[4];
	bool _hoops_CIPAR;
	int *_hoops_PHAS;

	ALLOC (m, _hoops_CRRR);	
	_hoops_IPSAA = pcount / 2;
	_hoops_ICSHI (m, min, max, _hoops_AASHI, _hoops_IPSAA);

	/* _hoops_CAHA _hoops_GGSR _hoops_GPCPR _hoops_RSH _hoops_AHPH _hoops_HSGS _hoops_SPSHI _hoops_SR _hoops_HS, _hoops_RH _hoops_SIA
	 * _hoops_GAPA _hoops_RHGS _hoops_PPR _hoops_CCAH _hoops_RSSA, _hoops_PPR _hoops_HSPC _hoops_RH _hoops_IIPGA _hoops_SGGPR _hoops_HSH */
	ALLOC_ARRAY (_hoops_PHAS, pcount, int);
	id = 0;
	for	 (ii = 0; ii < pcount; ii++) {
		x = points[ii*3 + 0];
		y = points[ii*3 + 1];
		z = points[ii*3 + 2];
		if (!_hoops_ASSHI (m, x, y, z, &_hoops_HAHCR)) {
			_hoops_PSSHI (m, x, y, z, id);
			_hoops_PHAS[ii] = id;
			id++;
		}
		else
			_hoops_PHAS[ii] = _hoops_HAHCR->id;
	}

	_hoops_RCHHR[0] = 3;
	while (t) {
		_hoops_PPHPA = t->_hoops_AIHA;
		for (ii = 0; ii < t->_hoops_PHHA; ii++) {
			if (t->lengths[ii] > 0) {
				/* _hoops_IRS _hoops_CRHH */
				_hoops_CIPAR = 0;
				for (_hoops_ICRHH = 2; _hoops_ICRHH < t->lengths[ii]; _hoops_ICRHH++) {
					if (!_hoops_CIPAR) {
						_hoops_RCHHR[1] = _hoops_PPHPA[_hoops_ICRHH-2];
						_hoops_RCHHR[2] = _hoops_PPHPA[_hoops_ICRHH-1];
						_hoops_RCHHR[3] = _hoops_PPHPA[_hoops_ICRHH-0];
					}
					else {
						_hoops_RCHHR[1] = _hoops_PPHPA[_hoops_ICRHH-2];
						_hoops_RCHHR[2] = _hoops_PPHPA[_hoops_ICRHH-0];
						_hoops_RCHHR[3] = _hoops_PPHPA[_hoops_ICRHH-1];
					}
					_hoops_CIPAR = !_hoops_CIPAR;
					_hoops_IGGII (m, _hoops_RCHHR, points);
				}
				_hoops_PPHPA += t->lengths[ii];
			}
			else {
				/* _hoops_IRS _hoops_HAHCP */
				_hoops_RCHHR[1] = _hoops_PPHPA[1];
				length = -(t->lengths[ii]);
				for (_hoops_ICRHH = 2; _hoops_ICRHH < length; _hoops_ICRHH++) {
					_hoops_RCHHR[2] = _hoops_PPHPA[_hoops_ICRHH-1];
					_hoops_RCHHR[3] = _hoops_PPHPA[_hoops_ICRHH];
					_hoops_IGGII (m, _hoops_RCHHR, points);
				}
				_hoops_PPHPA += -_hoops_PPHPA[0] + 1;
			}
		}
		t = t->next;
	}
	_hoops_PAGII (m);

	ALLOC (_hoops_PAGR, _hoops_HAPHA);
	_hoops_PAGR->_hoops_IAPHA.pcount = m->pcount;
	if (m->pcount != 0) {
		ALLOC_ARRAY_ALIGNED (_hoops_PAGR->_hoops_IAPHA.points, 3 * m->pcount, float, 16);
		COPY_MEMORY (m->points, 3 * m->pcount * sizeof (float), _hoops_PAGR->_hoops_IAPHA.points);
	}
	else
		_hoops_PAGR->_hoops_IAPHA.points = null;

	_hoops_PAGR->_hoops_IAPHA._hoops_RHGIR = m->_hoops_HCSHI;
	if (m->_hoops_HCSHI != 0) {
		ALLOC_ARRAY (_hoops_PAGR->_hoops_IAPHA.faces, m->_hoops_HCSHI, int);
		COPY_MEMORY (m->faces, m->_hoops_HCSHI * sizeof (int), _hoops_PAGR->_hoops_IAPHA.faces);
	}
	else
		_hoops_PAGR->_hoops_IAPHA.faces = null;

	_hoops_SCSHI (m);
	_hoops_PAGR->_hoops_CAPHA = pcount;
	_hoops_PAGR->_hoops_PHAS = _hoops_PHAS;
	FREE (m, _hoops_CRRR);
	return _hoops_PAGR;
} /* _hoops_RSGR _hoops_API _hoops_HPGII */


/*
#_hoops_GCIS <_hoops_IPGII._hoops_GGHR>
_hoops_GCGIH *_hoops_CPGII;
_hoops_RSPHR _hoops_SCSH _hoops_SPGII = 1;
_hoops_RSPHR _hoops_SCSH _hoops_GHGII = 0;
*/

static void _hoops_RHGII (_hoops_APHHI *_hoops_RCCIA); /* _hoops_CPCHR */
static void _hoops_AHGII (_hoops_APHHI *_hoops_RCCIA, const _hoops_PGSPI *mat); /* _hoops_CPCHR */
static void _hoops_PHGII (_hoops_APHHI *q); /* _hoops_CPCHR */
static void _hoops_HHGII (_hoops_APHHI *q); /* _hoops_CPCHR */

void _hoops_PPHHI (_hoops_APHHI *q, _hoops_GRAHI *_hoops_IHGII, _hoops_SAPHA *_hoops_GPPHA) {
	int i;
	_hoops_PGHHI *_hoops_IHHIR;
	_hoops_SHHHI *_hoops_CHGII;

	/* _hoops_GHRAA _hoops_SGCRP _hoops_CCPAR*/
	_hoops_CPGHI (&(q->heap));
	_hoops_RSSPI (&(q->_hoops_HAHHI), sizeof (_hoops_SHHHI *));
	_hoops_RSSPI (&(q->_hoops_AAHHI), sizeof (_hoops_PGHHI *));
	_hoops_RSSPI (&(q->_hoops_RAHHI), sizeof (_hoops_GGHHI *));

	/* _hoops_AGCR _hoops_PCCS _hoops_HCPH _hoops_CHR _hoops_HAR _hoops_RGHP, _hoops_HIH _hoops_CGH _hoops_HPIHR _hoops_HSRAP */
	_hoops_PGGHI (&(q->_hoops_AAHHI), _hoops_HPAHI (_hoops_IHGII));
	_hoops_PGGHI (&(q->_hoops_HAHHI), _hoops_HPAHI (_hoops_IHGII));
	for (i = 0; i < _hoops_HPAHI (_hoops_IHGII); i++)
	{
		ALLOC (_hoops_IHHIR, _hoops_PGHHI);
		ALLOC_ALIGNED (_hoops_CHGII, _hoops_SHHHI, 8);
		_hoops_SSSPI (&(q->_hoops_HAHHI), _hoops_CHGII);
		_hoops_RSSPI (_hoops_IHHIR, sizeof (_hoops_GGHHI *));
		_hoops_SSSPI (&(q->_hoops_AAHHI), _hoops_IHHIR);
	}
	q->m = _hoops_IHGII;

	/* _hoops_SHGII _hoops_SIGC _hoops_CCPAR*/
	q->_hoops_PPPHA	 = _hoops_GPPHA->_hoops_PPPHA;
	q->_hoops_HPPHA	 = _hoops_GPPHA->_hoops_HPPHA;
	q->_hoops_IPPHA	 = _hoops_GPPHA->_hoops_IPPHA;
	q->_hoops_CPPHA = _hoops_GPPHA->_hoops_CPPHA;
	q->_hoops_SPPHA	 = _hoops_GPPHA->_hoops_SPPHA;
	q->_hoops_GHPHA	 = _hoops_GPPHA->_hoops_GHPHA;
	q->_hoops_RHPHA		 = _hoops_GPPHA->_hoops_RHPHA;

	q->_hoops_CAHHI = NULL;
	q->_hoops_GAHHI = 0.0;

	q->_hoops_RPHHI = 0;
	q->_hoops_GPHHI = 0;

	for (i = 0; i < _hoops_IPAHI(q->m); i++) 
		if (_hoops_GRPHI (q->m, i))  
			q->_hoops_RPHHI++;
	for (i = 0; i < _hoops_HPAHI(q->m); i++) 
		if (_hoops_IGPHI (q->m, i))	
			q->_hoops_GPHHI++;

	q->_hoops_SAHHI = NULL;

	_hoops_RHGII (q);
	if (q->_hoops_IPPHA > 0.0)
		_hoops_PHGII (q);
	if (q->_hoops_CAHHI)
		_hoops_AHGII (q, q->_hoops_CAHHI);

	_hoops_HHGII (q);
} /* _hoops_RSGR _hoops_API _hoops_GIGII */


void _hoops_HPHHI (_hoops_APHHI *q) {
	int i;

	for (i = 0; i < _hoops_CGGHI (&(q->_hoops_HAHHI)); i++)
		FREE_ALIGNED (_hoops_GRGHI (&(q->_hoops_HAHHI), i), _hoops_SHHHI, 8);
	for (i = 0; i < _hoops_CGGHI (&(q->_hoops_AAHHI)); i++)
	{
		_hoops_PGHHI *_hoops_IHHIR = _hoops_GIHHI (q, i) ;
		_hoops_PSSPI (_hoops_IHHIR);
		FREE (_hoops_IHHIR, _hoops_PGHHI);
	}
	for (i = 0; i < _hoops_CGGHI (&(q->_hoops_RAHHI)); i++)
	{
		_hoops_GGHHI *e = (_hoops_GGHHI *)_hoops_GRGHI (&(q->_hoops_RAHHI), i) ;
		FREE_ALIGNED (e, _hoops_GGHHI, 8);
	}

	_hoops_SPGHI (&(q->heap));
	_hoops_PSSPI  (&(q->_hoops_HAHHI));
	_hoops_PSSPI  (&(q->_hoops_AAHHI));
	_hoops_PSSPI  (&(q->_hoops_RAHHI));
}


static void _hoops_RHGII (_hoops_APHHI *_hoops_RCCIA) {
	int i, j;
	_hoops_GCGHI *f;
	_hoops_RGSPI _hoops_ISPI, _hoops_CSPI, _hoops_SSPI;
	_hoops_SSCPI p;
	_hoops_SHHHI _hoops_CHGII;

	for (j = 0; j < _hoops_CGGHI (&(_hoops_RCCIA->_hoops_HAHHI)); j++)
		_hoops_ICHHI (_hoops_CHHHI (_hoops_RCCIA, j));
	for (i = 0; i < _hoops_IPAHI(_hoops_RCCIA->m); i++)
	{
		f = _hoops_SAAHI (_hoops_RCCIA->m, i);

		_hoops_HASPI (_hoops_ISPI._hoops_GGSPI, _hoops_CAAHI (_hoops_RCCIA->m, f->v[0])->_hoops_GGSPI, 3);
		_hoops_HASPI (_hoops_CSPI._hoops_GGSPI, _hoops_CAAHI (_hoops_RCCIA->m, f->v[1])->_hoops_GGSPI, 3);
		_hoops_HASPI (_hoops_SSPI._hoops_GGSPI, _hoops_CAAHI (_hoops_RCCIA->m, f->v[2])->_hoops_GGSPI, 3);

		if (_hoops_RCCIA->_hoops_HPPHA==_hoops_ISCPI)
			_hoops_IISPI (&p, &_hoops_ISPI, &_hoops_CSPI, &_hoops_SSPI);
		else
			if (!_hoops_HISPI (&p, &_hoops_ISPI, &_hoops_CSPI, &_hoops_SSPI))
			{
				/* _hoops_RH _hoops_SCPH _hoops_CSAP _hoops_ARHAR.	 _hoops_CSH _hoops_RIGII */
				/* _hoops_AGHR(0); */
					continue;
			}

		_hoops_IIHHI (&_hoops_CHGII, 
				p._hoops_GGSPI[X], p._hoops_GGSPI[Y], p._hoops_GGSPI[_hoops_GACPA], p._hoops_GGSPI[_hoops_CPCPA], 
				_hoops_GCPHI(_hoops_RCCIA->m, i));

		switch (_hoops_RCCIA->_hoops_HPPHA)
		{
		case _hoops_ASCPI:
			for (j=0; j<3; j++)
			{
				_hoops_SHHHI *_hoops_AIGII;
				_hoops_SHHHI Q_j;
				_hoops_GCHHI (&Q_j, &_hoops_CHGII);
				_hoops_HCHHI (&Q_j, _hoops_RCPHI (_hoops_RCCIA->m, i, j));
				_hoops_AIGII = _hoops_CHHHI(_hoops_RCCIA, f->v[j]);
				_hoops_RCHHI (_hoops_AIGII, _hoops_AIGII, &Q_j);
			}
			break;
		case _hoops_RSCPI:
			_hoops_HCHHI (&_hoops_CHGII, _hoops_ASHHI (&_hoops_CHGII));
			/* _hoops_PSP _hoops_IHSA: _hoops_HRRHH*/
		default:
			{
				_hoops_SHHHI *_hoops_PIGII, *_hoops_HIGII, *_hoops_IIGII;
				_hoops_PIGII = _hoops_CHHHI(_hoops_RCCIA, f->v[0]);
				_hoops_HIGII = _hoops_CHHHI(_hoops_RCCIA, f->v[1]);
				_hoops_IIGII = _hoops_CHHHI(_hoops_RCCIA, f->v[2]); 
				_hoops_RCHHI (_hoops_PIGII, _hoops_PIGII, &_hoops_CHGII);
				_hoops_RCHHI (_hoops_HIGII, _hoops_HIGII, &_hoops_CHGII);
				_hoops_RCHHI (_hoops_IIGII, _hoops_IIGII, &_hoops_CHGII);
			}
			break;
		}
	}
}

static void _hoops_AHGII (_hoops_APHHI *_hoops_RCCIA, const _hoops_PGSPI *mat) {
	int j;
	_hoops_SHHHI *_hoops_CHGII;
	for (j = 0; j < _hoops_CGGHI (&(_hoops_RCCIA->_hoops_HAHHI)); j++)
	{
		_hoops_CHGII = _hoops_CHHHI(_hoops_RCCIA, j);
		_hoops_CCHHI (_hoops_CHGII, _hoops_CHGII, mat);
	}
}


/* _hoops_GASA: _hoops_IGS _hoops_SPPR _hoops_CGH _hoops_SHH _hoops_CIGII _hoops_GCPRA _hoops_SRSR, _hoops_HAR _hoops_GPICR.
 * _hoops_HGI _hoops_API _hoops_RPSAR _hoops_IRS _hoops_GHPPR _hoops_IS _hoops_SIGII _hoops_SGGR _hoops_HII _hoops_HGPP 
 * _hoops_PCCP _hoops_ISHA.
 */
static void _hoops_GCGII (_hoops_APHHI *q, _hoops_SHGHI i, _hoops_SHGHI j, _hoops_CGRHI *faces) {
	_hoops_GIGHI fid;
	double _hoops_GCCPR;
	_hoops_RGSPI _hoops_RCGII, _hoops_PCAP;
	_hoops_RGSPI e;			/* _hoops_ISHA _hoops_GAPA _hoops_GPHA _hoops_HAS _hoops_PPR _hoops_PPHR */
	_hoops_RGSPI n;			/* _hoops_HSP _hoops_GSSR _hoops_IIGR _hoops_ACGII[_hoops_RSSI[_hoops_PCGII]] */
	_hoops_RGSPI _hoops_CCIPR;		/* _hoops_HPI _hoops_AAGA _hoops_AARGR _hoops_IS _hoops_IAS _hoops_PPR _hoops_ACHP */
	_hoops_SHHHI _hoops_CHGII;
	_hoops_SHHHI *_hoops_PIGII, *_hoops_HIGII;

	for (fid = 0; fid < _hoops_CGGHI (faces); fid++)
	{
		_hoops_HASPI (_hoops_RCGII._hoops_GGSPI, _hoops_CAAHI (q->m, i)->_hoops_GGSPI, 3); 
		_hoops_HASPI (_hoops_PCAP._hoops_GGSPI, _hoops_CAAHI (q->m, j)->_hoops_GGSPI, 3);
		_hoops_SRSPI (e._hoops_GGSPI, _hoops_PCAP._hoops_GGSPI, _hoops_RCGII._hoops_GGSPI, 3);

		if (!_hoops_CIPHI (q->m, _hoops_GARHI (faces, fid), n._hoops_GGSPI, 1))
			continue;

		_hoops_CASPI (_hoops_CCIPR._hoops_GGSPI, e._hoops_GGSPI, n._hoops_GGSPI, 3);
		_hoops_GCCPR = _hoops_SASPI (_hoops_CCIPR._hoops_GGSPI, 3);
		if (_hoops_HSCIA (_hoops_GCCPR, 0.0, 1e-12f))
			continue;

		_hoops_RASPI (_hoops_CCIPR._hoops_GGSPI, _hoops_CCIPR._hoops_GGSPI, _hoops_GCCPR, 3);

		_hoops_IIHHI (
			&_hoops_CHGII, 
			_hoops_CCIPR._hoops_GGSPI[0], _hoops_CCIPR._hoops_GGSPI[1], _hoops_CCIPR._hoops_GGSPI[2], 
			-_hoops_IASPI (_hoops_CCIPR._hoops_GGSPI, _hoops_RCGII._hoops_GGSPI, 3),
			1.0f);
		_hoops_HCHHI (&_hoops_CHGII, q->_hoops_IPPHA);

		if (q->_hoops_HPPHA == _hoops_RSCPI)
		{
			_hoops_GSHHI (&_hoops_CHGII, _hoops_GCPHI(q->m, _hoops_GARHI (faces, fid)));
			_hoops_HCHHI (&_hoops_CHGII, _hoops_ASHHI (&_hoops_CHGII));
		}

		_hoops_PIGII = _hoops_CHHHI (q, i);
		_hoops_HIGII = _hoops_CHHHI (q, j);
		_hoops_RCHHI (_hoops_PIGII, _hoops_PIGII, &_hoops_CHGII);
		_hoops_RCHHI (_hoops_HIGII, _hoops_HIGII, &_hoops_CHGII);
	}
} /* _hoops_RSGR _hoops_API _hoops_HCGII */


static void _hoops_PHGII (_hoops_APHHI *q) {
	_hoops_GRRHI _hoops_HGSH;
	_hoops_CGRHI faces;
	_hoops_SHGHI _hoops_HACGH;
	int i, j;

	_hoops_RSSPI (&faces, sizeof (_hoops_GIGHI));
	_hoops_RSSPI (&_hoops_HGSH, sizeof (_hoops_SHGHI));

	for (i = 0; i < _hoops_HPAHI(q->m); i++)
	{
		_hoops_HSSPI (&_hoops_HGSH);
		_hoops_HCPHI(q->m, i, &_hoops_HGSH);

		for (j = 0; j < _hoops_CGGHI (&_hoops_HGSH); j++)
		{
			_hoops_HACGH = _hoops_RARHI (&_hoops_HGSH, j);
			if (i < _hoops_HACGH)
			{
				_hoops_HSSPI (&faces);
				_hoops_PCPHI(q->m, i, _hoops_HACGH, &faces);
				if (_hoops_CGGHI (&faces) == 1)
					_hoops_GCGII (q, i, _hoops_HACGH, &faces);
			}
		}
	}

	_hoops_PSSPI (&faces);
	_hoops_PSSPI (&_hoops_HGSH);
}

#if 0
/* _hoops_PGAA 
 * _hoops_HGH _hoops_RPP _hoops_RH _hoops_ISHA (_hoops_IIHHR,_hoops_CIHHR) _hoops_HRGR _hoops_GRAA-_hoops_AHGPA.
 * [_hoops_HGI _hoops_CRRPR _hoops_HIICP _hoops_SPPR.]
 */
static
_hoops_CGSPI _hoops_ICGII(_hoops_GRAHI *m, _hoops_SHGHI _hoops_ISPI, _hoops_SHGHI _hoops_CSPI) {
	int _hoops_HPIS;
	_hoops_CGRHI faces;
	_hoops_RSSPI (&faces, sizeof (_hoops_GIGHI));

	_hoops_PCPHI(m, _hoops_ISPI, _hoops_CSPI, &faces);
	_hoops_HPIS = _hoops_CGGHI (&faces) != 2;

	_hoops_PSSPI (&faces);
	return _hoops_HPIS;
}

/* _hoops_PGAA
 * _hoops_HGH _hoops_RPP _hoops_RH _hoops_GPHA _hoops_HPPC _hoops_HRGR _hoops_GRAA-_hoops_AHGPA.
 * [_hoops_HGI _hoops_CRRPR _hoops_HIICP _hoops_GIHA.]
 */
static
_hoops_CGSPI _hoops_CCGII(_hoops_GRAHI *m, _hoops_SHGHI v) {
	_hoops_GRRHI _hoops_HGSH;
	int i, _hoops_SCGII;

	_hoops_RSSPI (&_hoops_HGSH, sizeof (_hoops_SHGHI));
	_hoops_HCPHI(m, v, &_hoops_HGSH);

	for (i = 0; i < _hoops_CGGHI (&_hoops_HGSH); i++)
		if (_hoops_ICGII(m, v, _hoops_RARHI (&_hoops_HGSH, i)))
		{
			_hoops_PSSPI (&_hoops_HGSH);
			return 1;
		}

	_hoops_SCGII = _hoops_CGGHI (&_hoops_HGSH) - _hoops_CGGHI (neighbors(m, v));
	ASSERT(_hoops_SCGII >= 0);

	/* _hoops_GSGII _hoops_GRAA-_hoops_AHGPA _hoops_GPHA: _hoops_RGCI _hoops_HRCCP _hoops_HRGR _hoops_HAR _hoops_RSGII*/
	/* _hoops_IS _hoops_IRS _hoops_IHIAH. */
	_hoops_PSSPI (&_hoops_HGSH);
	return (_hoops_SCGII > 0);
}
#endif


/* _hoops_GASA: _hoops_CRHR _hoops_APRP _hoops_RCCPR _hoops_GIHA -- _hoops_RPP _hoops_IIH _hoops_CHR _hoops_HAH _hoops_AHPH _hoops_SPPR _hoops_ICPAA 
 * _hoops_GGSR _hoops_IIGR _hoops_IRS _hoops_SAGHR _hoops_GPHA, _hoops_ARP _hoops_IRS _hoops_GHPPR _hoops_HIS _hoops_CASH _hoops_SGS _hoops_SCH _hoops_GRS 
 * _hoops_APGP _hoops_CRHR _hoops_SCH _hoops_HII _hoops_SGIPR _hoops_IHGS _hoops_PGCRA _hoops_GGR _hoops_HPIH _hoops_ISHA _hoops_RISRP 
 */
static void _hoops_ASGII (_hoops_APHHI *q, _hoops_GGHHI *info, int limit) {
	if (
	 (_hoops_CGGHI (neighbors (q->m, info->e._hoops_ISPI)) > limit) ||
	 (_hoops_CGGHI (neighbors (q->m, info->e._hoops_CSPI)) > limit) 
	 )
	{
		_hoops_RPGHI (
		&(info->h), 
		_hoops_APGHI (&(info->h)) - 1e12 
	);
	}
} /* _hoops_RSGR _hoops_API _hoops_PSGII */



/* _hoops_HSGII 
 * _hoops_HRS _hoops_IHPR _hoops_RPP _hoops_ISGII _hoops_HRGR _hoops_GIAA _hoops_RH _hoops_IASC _hoops_AHCRR _hoops_AARI _hoops_SIHC'_hoops_GRI _hoops_GIHA
 * _hoops_PPR _hoops_PAII _hoops_APIHR.
 */
#define _hoops_IACIR (1e6)
static _hoops_CGSPI _hoops_CSGII (_hoops_APHHI *q, _hoops_GGHHI *info) {
	int i;
	_hoops_SHGHI _hoops_HACGH;
	_hoops_SHGHI _hoops_ISPI = info->e._hoops_ISPI;
	_hoops_SHGHI _hoops_CSPI = info->e._hoops_CSPI;
	_hoops_PGHHI *_hoops_IHHIR;
	_hoops_GGHHI *_hoops_AGHHI;
	_hoops_IIGHI *v;
	double min[3];
	double max[3];

	min[0] = min[1] = min[2] =	_hoops_IACIR;
	max[0] = max[1] = max[2] = -_hoops_IACIR;

	_hoops_IHHIR = _hoops_GIHHI (q, _hoops_ISPI);
	for (i = 0; i < _hoops_CGGHI (_hoops_IHHIR); i++)
	{
		_hoops_AGHHI = _hoops_HRHHI (_hoops_IHHIR, i);
		_hoops_HACGH = _hoops_PCGHI (&(_hoops_AGHHI->e), _hoops_ISPI);
		v = _hoops_CAAHI (q->m, _hoops_HACGH);
		if (v->_hoops_GGSPI[0] < min[0]) min[0] = v->_hoops_GGSPI[0];
		if (v->_hoops_GGSPI[1] < min[1]) min[1] = v->_hoops_GGSPI[1];
		if (v->_hoops_GGSPI[2] < min[2]) min[2] = v->_hoops_GGSPI[2];
		if (v->_hoops_GGSPI[0] > max[0]) max[0] = v->_hoops_GGSPI[0];
		if (v->_hoops_GGSPI[1] > max[1]) max[1] = v->_hoops_GGSPI[1];
		if (v->_hoops_GGSPI[2] > max[2]) max[2] = v->_hoops_GGSPI[2];
	}
	
	_hoops_IHHIR = _hoops_GIHHI (q, _hoops_CSPI);
	for (i = 0; i < _hoops_CGGHI (_hoops_IHHIR); i++)
	{
		_hoops_AGHHI = _hoops_HRHHI (_hoops_IHHIR, i);
		_hoops_HACGH = _hoops_PCGHI (&(_hoops_AGHHI->e), _hoops_CSPI);
		v = _hoops_CAAHI (q->m, _hoops_HACGH);
		if (v->_hoops_GGSPI[0] < min[0]) min[0] = v->_hoops_GGSPI[0];
		if (v->_hoops_GGSPI[1] < min[1]) min[1] = v->_hoops_GGSPI[1];
		if (v->_hoops_GGSPI[2] < min[2]) min[2] = v->_hoops_GGSPI[2];
		if (v->_hoops_GGSPI[0] > max[0]) max[0] = v->_hoops_GGSPI[0];
		if (v->_hoops_GGSPI[1] > max[1]) max[1] = v->_hoops_GGSPI[1];
		if (v->_hoops_GGSPI[2] > max[2]) max[2] = v->_hoops_GGSPI[2];
	}
/*
	_hoops_AGHR (!_hoops_SSGII (_hoops_SIHC->_hoops_ISGII[0]));
	_hoops_AGHR (!_hoops_SSGII (_hoops_SIHC->_hoops_ISGII[1]));
	_hoops_AGHR (!_hoops_SSGII (_hoops_SIHC->_hoops_ISGII[2]));
*/

	if (info->_hoops_SSPHI[0] < min[0]) return 0;
	if (info->_hoops_SSPHI[1] < min[1]) return 0;
	if (info->_hoops_SSPHI[2] < min[2]) return 0;
	if (info->_hoops_SSPHI[0] > max[0]) return 0;
	if (info->_hoops_SSPHI[1] > max[1]) return 0;
	if (info->_hoops_SSPHI[2] > max[2]) return 0;

	return 1;
} /* _hoops_RSGR _hoops_API _hoops_HSGII */


static void _hoops_GGRII (_hoops_APHHI *q, _hoops_GGHHI *info) {
	_hoops_SHGHI i=info->e._hoops_ISPI, j=info->e._hoops_CSPI;
	const _hoops_SHHHI *Qi=_hoops_CHHHI(q, i), *Qj=_hoops_CHHHI(q, j);
	double _hoops_RGRII = 0;
	_hoops_SHHHI _hoops_CHGII;
	_hoops_RGSPI *vi, *_hoops_AGRII;
	_hoops_RGSPI _hoops_ACCAA;
	_hoops_RGSPI temp, _hoops_SPGIR;
	double _hoops_PGRII;
	_hoops_CGSPI _hoops_HGRII = 0;
	_hoops_CGSPI _hoops_IGRII = 0;

	_hoops_RCHHI (&_hoops_CHGII, Qi, Qj);

	if ((q->_hoops_PPPHA == _hoops_ICCPI) ||
		(q->_hoops_PPPHA == _hoops_CCCPI))
	{
		if (_hoops_HSHHI (&_hoops_CHGII, &info->_hoops_SSPHI[X], &info->_hoops_SSPHI[Y], &info->_hoops_SSPHI[_hoops_GACPA]))
		{
			_hoops_RGRII = _hoops_GGIHI (&_hoops_CHGII, info->_hoops_SSPHI);
/* _hoops_AGHR (_hoops_CGRII > -1000); */
			if (q->_hoops_PPPHA == _hoops_CCCPI)
				_hoops_HGRII = !_hoops_CSGII (q, info);
		}
		else
			_hoops_IGRII = 1;
	}

	if (q->_hoops_PPPHA == _hoops_HCCPI || _hoops_IGRII)
	{
		vi = _hoops_CAAHI (q->m, i); 
		_hoops_AGRII = _hoops_CAAHI (q->m, j);	
		_hoops_IGRII = 0;

		if (_hoops_ISHHI (&_hoops_CHGII, &_hoops_ACCAA, vi, _hoops_AGRII)) {
			_hoops_RGRII = _hoops_GGIHI (&_hoops_CHGII, _hoops_ACCAA._hoops_GGSPI);
/* _hoops_AGHR (_hoops_CGRII > -1000); */
			_hoops_HASPI (info->_hoops_SSPHI, _hoops_ACCAA._hoops_GGSPI, 3);
		}
		else
			_hoops_IGRII = 1;
	}

	/* _hoops_IH _hoops_SGRII, _hoops_RPP _hoops_RH _hoops_IASC _hoops_AHCRR _hoops_RPGP _hoops_ISHS, 
	 * _hoops_SHIR _hoops_IS _hoops_PSHR _hoops_GRRII _hoops_GAR _hoops_RRRII */
	if (q->_hoops_PPPHA == _hoops_ACCPI || 
		 q->_hoops_PPPHA == _hoops_PCCPI  || 
		 _hoops_IGRII ||
		 _hoops_HGRII)
	{
		double ei, _hoops_ARRII;

		vi = _hoops_CAAHI (q->m, i); 
		_hoops_AGRII = _hoops_CAAHI (q->m, j);	
		ei = _hoops_GGIHI (&_hoops_CHGII, vi->_hoops_GGSPI);
		_hoops_ARRII = _hoops_GGIHI (&_hoops_CHGII, _hoops_AGRII->_hoops_GGSPI);
	
		if (ei < _hoops_ARRII) { _hoops_RGRII = ei; _hoops_HASPI (_hoops_ACCAA._hoops_GGSPI, vi->_hoops_GGSPI, 3); }
		else		  { _hoops_RGRII = _hoops_ARRII; _hoops_HASPI (_hoops_ACCAA._hoops_GGSPI, _hoops_AGRII->_hoops_GGSPI, 3); }
/* _hoops_AGHR (_hoops_CGRII > -1000); */
	
		if (q->_hoops_PPPHA >= _hoops_PCCPI || _hoops_HGRII)
		{
			/* _hoops_HPASR _hoops_GIGR _hoops_RRGR...*/
			/* _hoops_PRRII _hoops_GHHPA = (_hoops_HRRII+_hoops_IRRII)/2;*/
			_hoops_CRSPI (temp._hoops_GGSPI, vi->_hoops_GGSPI, _hoops_AGRII->_hoops_GGSPI, 3);
			_hoops_RASPI (_hoops_SPGIR._hoops_GGSPI, temp._hoops_GGSPI, 2.0f, 3);
			_hoops_PGRII = _hoops_GGIHI (&_hoops_CHGII, _hoops_SPGIR._hoops_GGSPI);
			if (_hoops_PGRII < _hoops_RGRII) { _hoops_RGRII = _hoops_PGRII; _hoops_ACCAA = _hoops_SPGIR; }
		}
		_hoops_HASPI (info->_hoops_SSPHI, _hoops_ACCAA._hoops_GGSPI, 3);
	}

/*
	_hoops_RPP (_hoops_ARHHI->_hoops_CRRII == _hoops_SRRII)
		_hoops_CGRII /= _hoops_GARII (&_hoops_PCPI);
*/

	_hoops_RPGHI (&(info->h), -_hoops_RGRII);
} /* _hoops_RSGR _hoops_API _hoops_RARII */



static void _hoops_AARII (_hoops_APHHI *q, _hoops_GGHHI *info) {
	_hoops_GGRII (q, info);

	/* _hoops_PARII (_hoops_ARHHI, _hoops_SIHC); */

	_hoops_ASGII (q, info, q->_hoops_RHPHA);

	if (_hoops_IAGHI (&(info->h)))
		_hoops_GHGHI (&(q->heap), &(info->h));
	else
		_hoops_CHPHH (&(q->heap), &(info->h));
} /* _hoops_RSGR _hoops_API _hoops_HARII */



static void _hoops_IARII (_hoops_APHHI *q, _hoops_SHGHI i, _hoops_SHGHI j) {
	_hoops_GGHHI *info;

	ALLOC_ALIGNED (info, _hoops_GGHHI, 8);
	_hoops_RGHHI (info);
	_hoops_IRHHI (_hoops_GIHHI(q, i), info);
	_hoops_IRHHI (_hoops_GIHHI(q, j), info);

	info->e._hoops_ISPI = i;
	info->e._hoops_CSPI = j;

	_hoops_AARII (q, info);
	_hoops_SSSPI (&(q->_hoops_RAHHI), info);
} /* _hoops_RSGR _hoops_API _hoops_CARII */

static void _hoops_HHGII (_hoops_APHHI *q) {
	int i, j;
	_hoops_GRRHI _hoops_HGSH;
	_hoops_SHGHI _hoops_HACGH;

	_hoops_RSSPI (&_hoops_HGSH, sizeof (_hoops_SHGHI));

	for (i = 0; i < _hoops_HPAHI (q->m); i++)
	{
		_hoops_HSSPI (&_hoops_HGSH);
		_hoops_HCPHI (q->m, i, &_hoops_HGSH);

		for (j = 0; j < _hoops_CGGHI (&_hoops_HGSH); j++)
		{
			_hoops_HACGH = _hoops_RARHI (&_hoops_HGSH, j);
			if (i < _hoops_HACGH) {
				/* _hoops_PGPR _hoops_GGCR _hoops_SAGHR _hoops_ISHA _hoops_ARR */
				_hoops_IARII (q, i, _hoops_HACGH);
			}
		}
	}

	_hoops_PSSPI (&_hoops_HGSH);
}


void _hoops_SPHHI (_hoops_APHHI *q, const _hoops_SHRHI *_hoops_HGCHI) {
	_hoops_SHGHI _hoops_ISPI=_hoops_HGCHI->_hoops_ISPI, _hoops_CSPI=_hoops_HGCHI->_hoops_CSPI;
	int i, j;
	_hoops_GRRHI _hoops_HGSH;
	_hoops_PGHHI *_hoops_IHHIR;
	_hoops_SIGHI *temp;
	_hoops_GGHHI *info;
	_hoops_SHGHI id, u;

	_hoops_RSSPI (&_hoops_HGSH, sizeof (_hoops_SHGHI));

	/*
	 * _hoops_HPACP, _hoops_GHAP _hoops_CSAP _hoops_SIIAR _hoops_RH _hoops_GPHA "_hoops_PGSH" _hoops_GRP:
	 *		_hoops_SARII(_hoops_SPHAI, _hoops_IIHHR, _hoops_PGSH);
	 * _hoops_HGI _hoops_ASSP'_hoops_RA _hoops_IPHR _hoops_CGPR _hoops_SR _hoops_PAHHH _hoops_RPGH _hoops_CCA _hoops_IRS _hoops_GIIAR _hoops_IIGR
	 * _hoops_RH _hoops_APSR _hoops_SPPR.	 _hoops_RPGAI, _hoops_SR _hoops_RRP _hoops_IS _hoops_PGGC _hoops_RH "_hoops_PGSH"
	 * _hoops_HII _hoops_RH _hoops_ISHA _hoops_GPHHR _hoops_IGCGI _hoops_HPGR _hoops_IIHHR.
	 */

	for (i = 0; i < _hoops_CGGHI (_hoops_GIHHI(q, _hoops_ISPI)); i++)
	{
		_hoops_IHHIR = _hoops_GIHHI(q, _hoops_ISPI);
		temp = & (_hoops_HRHHI (_hoops_IHHIR, i)->e);
		id = _hoops_PCGHI (temp, _hoops_ISPI);
		_hoops_ISSPI (&_hoops_HGSH, &id);
	}

	for (i = 0; i < _hoops_CGGHI (_hoops_GIHHI(q, _hoops_CSPI)); i++)
	{
		_hoops_IHHIR = _hoops_GIHHI(q, _hoops_CSPI);
		info = _hoops_HRHHI (_hoops_IHHIR, i);

		if (info->e._hoops_ISPI == _hoops_CSPI) u = info->e._hoops_CSPI;
		else				   u = info->e._hoops_ISPI;
		ASSERT (info->e._hoops_ISPI==_hoops_CSPI || info->e._hoops_CSPI==_hoops_CSPI);
		ASSERT (u != _hoops_CSPI);

		if (u==_hoops_ISPI || _hoops_PARHI (&_hoops_HGSH, u, NULL))
		{
			/* _hoops_HGI _hoops_HRGR _hoops_IRS _hoops_GPRII _hoops_AGGAR --- _hoops_PCHIA _hoops_SCH */
			_hoops_CGSPI _hoops_PPIHA = _hoops_CRHHI (_hoops_GIHHI(q, u), info, &j);
			UNREFERENCED(_hoops_PPIHA);
			ASSERT (_hoops_PPIHA);
			_hoops_AGGHI (_hoops_GIHHI(q, u), j);
			_hoops_RHGHI (&(q->heap), &(info->h));
		}
		else
		{
			/* _hoops_RPRII _hoops_RGR _hoops_IS _hoops_IIHHR */
			info->e._hoops_ISPI = _hoops_ISPI;
			info->e._hoops_CSPI = u;
			_hoops_IRHHI (_hoops_GIHHI(q, _hoops_ISPI), info);
		}
	}

	_hoops_HSSPI (_hoops_GIHHI(q, _hoops_CSPI));
	_hoops_PSSPI (&_hoops_HGSH);
}

void _hoops_CPHHI (_hoops_APHHI *q, _hoops_SHRHI *_hoops_HGCHI) {
	int i;
	_hoops_PGHHI *_hoops_IHHIR;

	/* _hoops_APRII-_hoops_ASPHI _hoops_PAAP*/
	q->_hoops_GPHHI--;
	q->_hoops_RPHHI -= _hoops_CGGHI (&(_hoops_HGCHI->_hoops_CHRHI));
	_hoops_RCHHI (_hoops_CHHHI (q, _hoops_HGCHI->_hoops_ISPI), 
			  _hoops_CHHHI (q, _hoops_HGCHI->_hoops_ISPI), 
			  _hoops_CHHHI (q, _hoops_HGCHI->_hoops_CSPI));

	_hoops_SPHHI (q, _hoops_HGCHI);

	_hoops_HSPHI (q->m, _hoops_HGCHI);

	/* _hoops_CGIHI: _hoops_PPRII _hoops_PAAP _hoops_ISHA _hoops_SIHC _hoops_ARI _hoops_HIS _hoops_SGS _hoops_RH _hoops_HPRII _hoops_IPRII*/
	/* _hoops_GRS _hoops_SHH _hoops_GGSRA _hoops_CCA _hoops_GPCAR _hoops_IS _hoops_RH _hoops_CCAH _hoops_HSHRR _hoops_HRII _hoops_HSAR _hoops_RH _hoops_RHGS*/
	_hoops_IHHIR = _hoops_GIHHI (q, _hoops_HGCHI->_hoops_ISPI);
	for (i = 0; i < _hoops_CGGHI (_hoops_IHHIR); i++)
		_hoops_AARII (q, _hoops_HRHHI (_hoops_IHHIR, i));
}

void _hoops_GHHHI (_hoops_APHHI *q, const _hoops_SHRHI *_hoops_HGCHI) {
	_hoops_SHGHI _hoops_ISPI=_hoops_HGCHI->_hoops_ISPI, _hoops_CSPI=_hoops_HGCHI->_hoops_CSPI;
	_hoops_GRRHI _hoops_HGSH, _hoops_CPRII;
	int i, _hoops_SPRII, _hoops_GHRII;

	_hoops_RSSPI (&_hoops_HGSH, sizeof (_hoops_SHGHI));
	_hoops_RSSPI (&_hoops_CPRII, sizeof (_hoops_SHGHI));

	_hoops_HCPHI(q->m, _hoops_HGCHI->_hoops_ISPI, &_hoops_HGSH);
	_hoops_HCPHI(q->m, _hoops_HGCHI->_hoops_CSPI, &_hoops_CPRII);

	i = 0;
	while (i < _hoops_CGGHI (_hoops_GIHHI (q, _hoops_ISPI)))
	{
		_hoops_PGHHI *_hoops_IHHIR = _hoops_GIHHI (q, _hoops_ISPI);
		_hoops_GGHHI *info = _hoops_HRHHI (_hoops_IHHIR, i);
		_hoops_SHGHI u;
		if (info->e._hoops_ISPI == _hoops_ISPI)  u = info->e._hoops_CSPI;
		else					u = info->e._hoops_ISPI;
		ASSERT (info->e._hoops_ISPI==_hoops_ISPI || info->e._hoops_CSPI==_hoops_ISPI);
		ASSERT (u!=_hoops_ISPI && u!=_hoops_CSPI);

		_hoops_SPRII = _hoops_PARHI (&_hoops_HGSH, u, NULL);
		_hoops_GHRII = _hoops_PARHI (&_hoops_CPRII, u, NULL);

		if (_hoops_SPRII)
		{
			if (_hoops_GHRII)	_hoops_IARII (q, _hoops_CSPI, u);
			i++;
		}
		else
		{
			/* _hoops_CGIHI: !!_hoops_HGASR: _hoops_GHAP _hoops_SSSHR _hoops_RGR _hoops_IS _hoops_SHH _hoops_IHPR, _hoops_HIH _hoops_SCH'_hoops_GRI _hoops_HAR.
			 *		   _hoops_ICAH _hoops_IS _hoops_SSS _hoops_GGSR _hoops_RCSC, _hoops_PPR _hoops_IGH _hoops_SCH'_hoops_GRI _hoops_RRHCP
			 *		   _hoops_RHRII _hoops_PAR _hoops_RH _hoops_RRGR _hoops_SGS'_hoops_GRI _hoops_RHPH.
			 * _hoops_AHRII(_hoops_PHRII);
			 */
			info->e._hoops_ISPI = _hoops_CSPI;
			info->e._hoops_CSPI = u;
			_hoops_IRHHI (_hoops_GIHHI(q, _hoops_CSPI), info);
			_hoops_AGGHI (_hoops_GIHHI(q, _hoops_ISPI), i);
		}

		_hoops_AARII (q, info);
	}

	/* _hoops_CGIHI: ??_hoops_HGASR: _hoops_HCIC _hoops_SCH _hoops_SPCHH _hoops_IH _hoops_IIH _hoops_HAR _hoops_IS _hoops_SHH _hoops_PCCP _hoops_ISHA _hoops_ARI ?? */
	if (_hoops_PARHI (&_hoops_HGSH, _hoops_CSPI, NULL))
		_hoops_IARII (q, _hoops_ISPI, _hoops_CSPI);

	_hoops_PSSPI (&_hoops_HGSH);
	_hoops_PSSPI (&_hoops_CPRII);
}


_hoops_CGSPI _hoops_IPHHI (_hoops_APHHI *q, int target) {
	_hoops_GGHHI *info;
	_hoops_SHGHI _hoops_ISPI, _hoops_CSPI;
	_hoops_SHRHI _hoops_HHRII;

	_hoops_GIRHI (&_hoops_HHRII);

	while (q->_hoops_RPHHI > target)
	{
		info = (_hoops_GGHHI *) _hoops_PIPHH	 (&(q->heap));
		if (!info) { 
			_hoops_AIRHI (&_hoops_HHRII);
			return 0; 
		}

/* _hoops_HPGR _hoops_AGRR _hoops_IACH, _hoops_RGR _hoops_IHRII _hoops_SSCP _hoops_CHRII _hoops_IS _hoops_SHH _hoops_SHRII _hoops_SHGC */
/*
		_hoops_RPP (_hoops_SPGII)
		{
			_hoops_SPGII = 0;
			_hoops_CPGII = _hoops_GIRII ("_hoops_RIRII._hoops_HICPI", "_hoops_SSCHA");
			_hoops_AGHR (_hoops_CPGII);
		}
		_hoops_AIRII (_hoops_CPGII, "%_hoops_RCHP \_hoops_ACHP", (_hoops_GHGPR)(_hoops_SIHC->_hoops_GGHR._hoops_AAGHI));
		_hoops_GHGII++;
		_hoops_RPP (_hoops_GHGII > 1000)
		{
			_hoops_PIRII (_hoops_CPGII);
			_hoops_RIARR(0);
		}
*/

		_hoops_ISPI=info->e._hoops_ISPI;
		_hoops_CSPI=info->e._hoops_CSPI;

		if (_hoops_IGPHI (q->m, _hoops_ISPI) && _hoops_IGPHI (q->m, _hoops_CSPI))
		{
			_hoops_SHRHI *_hoops_HIRII=NULL;
			/* _hoops_RPP (_hoops_IIRII) _hoops_CIRII=_hoops_IIRII->_hoops_SIRII(); */
			_hoops_SHRHI *_hoops_HGCHI = _hoops_HIRII?_hoops_HIRII:&_hoops_HHRII;
	
			_hoops_PSPHI (q->m, _hoops_ISPI, _hoops_CSPI, _hoops_HGCHI);
			/*
			 * _hoops_CGIHI: !!_hoops_HGASR: _hoops_ICAH _hoops_IS _hoops_RCRP _hoops_ISSC _hoops_RH _hoops_PRIA _hoops_PSPP _hoops_HPP
			 *		  _hoops_SIRII() (_hoops_RPP _hoops_GII).
			 * _hoops_GASA: ?
			 */
			if (q->_hoops_GHPHA && _hoops_CGGHI (&(_hoops_HGCHI->_hoops_CHRHI))>0) continue;
			_hoops_HGCHI->_hoops_AHRHI[X] = info->_hoops_SSPHI[X] - _hoops_CAAHI (q->m, _hoops_ISPI)->_hoops_GGSPI[X];
			_hoops_HGCHI->_hoops_AHRHI[Y] = info->_hoops_SSPHI[Y] - _hoops_CAAHI (q->m, _hoops_ISPI)->_hoops_GGSPI[Y];
			_hoops_HGCHI->_hoops_AHRHI[_hoops_GACPA] = info->_hoops_SSPHI[_hoops_GACPA] - _hoops_CAAHI (q->m, _hoops_ISPI)->_hoops_GGSPI[_hoops_GACPA];
			_hoops_HGCHI->_hoops_PHRHI[X] = info->_hoops_SSPHI[X] - _hoops_CAAHI (q->m, _hoops_CSPI)->_hoops_GGSPI[X];
			_hoops_HGCHI->_hoops_PHRHI[Y] = info->_hoops_SSPHI[Y] - _hoops_CAAHI (q->m, _hoops_CSPI)->_hoops_GGSPI[Y];
			_hoops_HGCHI->_hoops_PHRHI[_hoops_GACPA] = info->_hoops_SSPHI[_hoops_GACPA] - _hoops_CAAHI (q->m, _hoops_CSPI)->_hoops_GGSPI[_hoops_GACPA];

			/* _hoops_RPP (_hoops_IIRII) _hoops_IIRII->_hoops_GCRII(_hoops_GRCHI); */
			if (q->_hoops_SAHHI)
				(*(q->_hoops_SAHHI))(_hoops_HGCHI, -_hoops_APGHI (&(info->h)));
		
			_hoops_CPHHI (q, _hoops_HGCHI);
		}
	}

	_hoops_AIRHI (&_hoops_HHRII);
	return 1;
}


void _hoops_RGHHI (_hoops_GGHHI *_hoops_AGHHI) {
	_hoops_PPGHI (&(_hoops_AGHHI->h));
	_hoops_AGHHI->h._hoops_ASHSA = _hoops_AGHHI;
}


_hoops_CGSPI _hoops_CRHHI (_hoops_PGHHI *_hoops_IHHIR, const _hoops_GGHHI *t, int *index) {
	int i;
	for (i = 0; i < _hoops_CGGHI (_hoops_IHHIR); i++)
		if (_hoops_HRHHI (_hoops_IHHIR,  i) == t)
		{
			if (index) *index = i;
			return 1;
		}
	return 0;
}




/* _hoops_CACH _hoops_RCRII._hoops_GGHR _hoops_IH _hoops_IRS _hoops_GAIGR _hoops_IIGR _hoops_RH _hoops_ACRII _hoops_RPCC */
static void _hoops_PCRII (_hoops_GRAHI *m,
		int point_count, const float *points,
		const Tristrip *t) {
	int i, j;
	const float *_hoops_HCRII = (float *) points;
	const int *_hoops_RGCHI;
	int _hoops_CIPAR;

	for (i = 0; i < point_count; i++, _hoops_HCRII += 3)
		_hoops_RHPHI (m, _hoops_HCRII[0], _hoops_HCRII[1], _hoops_HCRII[2]);

	while (t) {
		_hoops_RGCHI = t->_hoops_AIHA;
		for (i = 0; i < t->_hoops_PHHA; i++) {
			_hoops_CIPAR = 1;
			for (j = 2; j < t->lengths[i]; j++) {
				if (_hoops_CIPAR)
					_hoops_AHPHI (m, _hoops_RGCHI[j-2], _hoops_RGCHI[j-1], _hoops_RGCHI[j]);
				else
					_hoops_AHPHI (m, _hoops_RGCHI[j-1], _hoops_RGCHI[j-2], _hoops_RGCHI[j]);
				_hoops_CIPAR = !_hoops_CIPAR;
			}
			_hoops_RGCHI += t->lengths[i];
		}
		t = t->next;
	}
} /* _hoops_RSGR _hoops_API _hoops_ICRII */


/*
 *	_hoops_HGI _hoops_API _hoops_SIHR _hoops_RH _hoops_CCHGR _hoops_IS _hoops_RH _hoops_API _hoops_SGS _hoops_CCRII _hoops_RH 
 *	_hoops_RRCPR _hoops_HII _hoops_RH _hoops_CHARP _hoops_SCRII.
 */
static int _hoops_GSRII (_hoops_GRAHI *m, 
				int pcount, const float *points, 
				int _hoops_SHSIH, const int *_hoops_ASPH) {
	const float *_hoops_HCRII;
	const int *_hoops_RGCHI;
	int i, j, count;
	int _hoops_RSRII = 0;

	for (i = 0, _hoops_HCRII = points; i < pcount; i++, _hoops_HCRII += 3)
		_hoops_RHPHI (m, _hoops_HCRII[0], _hoops_HCRII[1], _hoops_HCRII[2]);

	for (_hoops_RGCHI = _hoops_ASPH; _hoops_RGCHI < _hoops_ASPH + _hoops_SHSIH; _hoops_RGCHI += count + 1) {
		count = *_hoops_RGCHI;
		ASSERT (count >= 0);
		for (j = 3; j <= count; j++) {
			_hoops_AHPHI (m, _hoops_RGCHI[1], _hoops_RGCHI[j-1], _hoops_RGCHI[j]);
			_hoops_RSRII++;
		}
	}

	return _hoops_RSRII;
} /* _hoops_RSGR _hoops_API _hoops_ASRII */


#define _hoops_PSRII(m,from,to) do { \
	int *_hoops_RGCHI = (int *) _hoops_SGGHI  (&(m->_hoops_ASRHI), from); \
	*_hoops_RGCHI = to; \
} while (0)

#define _hoops_HSRII(m,i) (*(int *) _hoops_SGGHI (&((m)->_hoops_ASRHI), (i)))

static void _hoops_ISRII (_hoops_GRAHI *m, int *_hoops_PHAS) {
	int i, _hoops_HSIHI, k, _hoops_CSRII;

	if (_hoops_PHAS != NULL) {
		_hoops_HSIHI = _hoops_CGGHI (&(m->_hoops_ASRHI));
		for (i = 0; i < _hoops_HSIHI; i++) {
			k = i;
			while (!_hoops_IGPHI(m, k)) {
				_hoops_CSRII = _hoops_HSRII(m, k);
				ASSERT(k != _hoops_CSRII);
				k = _hoops_CSRII;
			} 
			k = _hoops_HSRII(m, k);
			_hoops_PHAS[i] = k;
		}
	}
}



/* _hoops_SSRII
 */
static void _hoops_GGAII (
				_hoops_GRAHI *m,
				int *pcount, float *points, 
				int *_hoops_SHSIH, int	  *_hoops_ASPH,
				int _hoops_RGAII, int *_hoops_PHAS) {
	double *_hoops_AGAII;
	float *_hoops_PGAII;
	int *_hoops_HGAII, *_hoops_IGAII;
	int i, _hoops_HSIHI;
	int _hoops_CGAII;

	UNREFERENCED(_hoops_RGAII);

	_hoops_PGAII = points;
	_hoops_HSIHI = _hoops_HPAHI (m);
	_hoops_CGAII = 0;
	for (i = 0; i < _hoops_HSIHI; i++) {
		if (_hoops_IGPHI(m, i)) {
			_hoops_AGAII = _hoops_CAAHI (m, i)->_hoops_GGSPI;
			_hoops_PGAII[0] = (float) (_hoops_AGAII[0]);
			_hoops_PGAII[1] = (float) (_hoops_AGAII[1]);
			_hoops_PGAII[2] = (float) (_hoops_AGAII[2]);
			_hoops_PGAII += 3;
			_hoops_PSRII(m,i,_hoops_CGAII);
			_hoops_CGAII++;
		}
	}
	*pcount = _hoops_CGAII;
	
	_hoops_ISRII (m, _hoops_PHAS);

	/* _hoops_GGR _hoops_RGR _hoops_RIS _hoops_SR _hoops_IIPR _hoops_RSSI
	 * _hoops_IGIPR _hoops_SGS _hoops_SARR _hoops_SSCP _hoops_HIPH _hoops_RGAR -- _hoops_GRS _hoops_IHSA _hoops_IAII 
	 */
	_hoops_IGAII = _hoops_ASPH;
	_hoops_HSIHI = _hoops_IPAHI (m);
	for (i = 0; i < _hoops_HSIHI; i++) {
		if (_hoops_GRPHI (m, i)) {
			_hoops_HGAII = _hoops_SAAHI (m, i)->v;
			ASSERT(_hoops_IGPHI(m, _hoops_HGAII[0]));
			ASSERT(_hoops_IGPHI(m, _hoops_HGAII[1]));
			ASSERT(_hoops_IGPHI(m, _hoops_HGAII[2]));
			_hoops_IGAII[0] = 3;
			_hoops_IGAII[1] = _hoops_HSRII(m, _hoops_HGAII[0]);
			_hoops_IGAII[2] = _hoops_HSRII(m, _hoops_HGAII[1]);
			_hoops_IGAII[3] = _hoops_HSRII(m, _hoops_HGAII[2]);
			ASSERT ((_hoops_IGAII[1] >= 0) &&  (_hoops_IGAII[1] < *pcount));
			ASSERT ((_hoops_IGAII[2] >= 0) &&  (_hoops_IGAII[2] < *pcount));
			ASSERT ((_hoops_IGAII[3] >= 0) &&  (_hoops_IGAII[3] < *pcount));
			_hoops_IGAII += 4;
		}
	}
	*_hoops_SHSIH = _hoops_IGAII - _hoops_ASPH;

} /* _hoops_RSGR _hoops_API _hoops_SSRII */


/*	_hoops_SGAII
 *	_hoops_PAAS _hoops_GRAII _hoops_HRGR _hoops_IGI, _hoops_HCR _hoops_SHCPI _hoops_CIHA _hoops_ISSC
 *	_hoops_CRGR _hoops_RH _hoops_PSHR _hoops_RSSA _hoops_CRPR.	 _hoops_HGI _hoops_HCPRI _hoops_IS _hoops_RH _hoops_AGAH "_hoops_RRAII _hoops_PPGS"
 *	_hoops_RGSR.
 */
static void _hoops_ARAII(
				_hoops_GRAHI *m,
				int *pcount, 
				int *_hoops_SHSIH, int *_hoops_ASPH) {
	int *_hoops_HGAII, *_hoops_IGAII;
	int i, _hoops_HSIHI;
	int _hoops_APGIR, _hoops_CGAII = 0;

	_hoops_HSIHI = _hoops_APGIR = _hoops_HPAHI (m);
	for (i = 0; i < _hoops_HSIHI; i++)
		if (_hoops_IGPHI(m, i))
			_hoops_CGAII++;
	*pcount = _hoops_CGAII; /* _hoops_PRAII _hoops_GHCA _hoops_PAR _hoops_GHCA _hoops_HAR _hoops_SHH _hoops_SIGR _hoops_SPHR */

	_hoops_IGAII = _hoops_ASPH;
	_hoops_HSIHI = _hoops_IPAHI (m);
	for (i = 0; i < _hoops_HSIHI; i++) {
		if (_hoops_GRPHI (m, i)) {
			_hoops_HGAII = _hoops_SAAHI (m, i)->v;
			/* _hoops_IGIPR _hoops_HIPH _hoops_RGAR */
			_hoops_IGAII[0] = 3;
			/* _hoops_PIP: _hoops_ISGHR _hoops_SSRII, _hoops_PSP _hoops_GPHA _hoops_SIA */
			_hoops_IGAII[1] = _hoops_HGAII[0];
			_hoops_IGAII[2] = _hoops_HGAII[1];
			_hoops_IGAII[3] = _hoops_HGAII[2];
			ASSERT ((_hoops_IGAII[1] >= 0) &&  (_hoops_IGAII[1] < _hoops_APGIR));
			ASSERT ((_hoops_IGAII[2] >= 0) &&  (_hoops_IGAII[2] < _hoops_APGIR));
			ASSERT ((_hoops_IGAII[3] >= 0) &&  (_hoops_IGAII[3] < _hoops_APGIR));
			_hoops_IGAII += 4;
		}
	}
	*_hoops_SHSIH = _hoops_IGAII - _hoops_ASPH;
} /* _hoops_RSGR _hoops_API _hoops_SGAII */


static void _hoops_HRAII (const _hoops_SAPHA *_hoops_IRAII, _hoops_SAPHA *_hoops_GPPHA) {
	/* _hoops_PPSI _hoops_GGR _hoops_SHIR _hoops_HSH */
	_hoops_GPPHA->_hoops_PPPHA  = _hoops_CCCPI;
	_hoops_GPPHA->_hoops_HPPHA  = _hoops_RSCPI; 
	_hoops_GPPHA->_hoops_IPPHA   = 1000.0;
	_hoops_GPPHA->_hoops_CPPHA = 0;
	_hoops_GPPHA->_hoops_SPPHA   = 0;
	_hoops_GPPHA->_hoops_GHPHA	   = 0;
	_hoops_GPPHA->_hoops_PRPHA			   = 0.5;
	_hoops_GPPHA->_hoops_RHPHA		   = 15;
	if (_hoops_IRAII != NULL) {
		if (_hoops_IRAII->_hoops_PPPHA != _hoops_SGRHA)
			_hoops_GPPHA->_hoops_PPPHA = _hoops_IRAII->_hoops_PPPHA;
		if (_hoops_IRAII->_hoops_HPPHA != _hoops_SGRHA)
			_hoops_GPPHA->_hoops_HPPHA = _hoops_IRAII->_hoops_HPPHA;
		if (_hoops_IRAII->_hoops_IPPHA != _hoops_SGRHA)
			_hoops_GPPHA->_hoops_IPPHA = _hoops_IRAII->_hoops_IPPHA;
		if (_hoops_IRAII->_hoops_CPPHA != _hoops_SGRHA)
			_hoops_GPPHA->_hoops_CPPHA = _hoops_IRAII->_hoops_CPPHA;
		if (_hoops_IRAII->_hoops_SPPHA != _hoops_SGRHA)
			_hoops_GPPHA->_hoops_SPPHA = _hoops_IRAII->_hoops_SPPHA;
		if (_hoops_IRAII->_hoops_GHPHA != _hoops_SGRHA)
			_hoops_GPPHA->_hoops_SPPHA = _hoops_IRAII->_hoops_SPPHA;
		if (_hoops_IRAII->_hoops_PRPHA != _hoops_SGRHA)
			_hoops_GPPHA->_hoops_PRPHA = _hoops_IRAII->_hoops_PRPHA;
		if (_hoops_IRAII->_hoops_RHPHA != _hoops_SGRHA)
			_hoops_GPPHA->_hoops_RHPHA = _hoops_IRAII->_hoops_RHPHA;
	}
} /* _hoops_RSGR _hoops_API _hoops_CRAII */




/* 
 * _hoops_HICRR
 */
static void _hoops_SRAII	 (
			_hoops_HAPHA *root, 
			_hoops_SAPHA *_hoops_GPPHA,
			_hoops_APHHI *_hoops_GAAII,
			int _hoops_RAAII,
			int depth) {
	int _hoops_AAAII;
	int _hoops_CGAII;

	_hoops_IPHHI (_hoops_GAAII, _hoops_RAAII);
	_hoops_AAAII = _hoops_SPAHI (_hoops_GAAII->m);
	if (_hoops_AAAII == 0) {
		root->_hoops_IAPHA.pcount = 0;
		root->_hoops_IAPHA.points = NULL;
		root->_hoops_IAPHA._hoops_RHGIR = 0;
		root->_hoops_IAPHA.faces = NULL;
		root->next = NULL;
		return;
	}
	ALLOC_ARRAY (root->_hoops_IAPHA.faces, 4 * _hoops_AAAII, int);

	if (_hoops_GPPHA->_hoops_PPPHA == _hoops_ACCPI) {
		root->_hoops_IAPHA.points = NULL;
		_hoops_ARAII (
			_hoops_GAAII->m,
			&(root->_hoops_IAPHA.pcount),
			&(root->_hoops_IAPHA._hoops_RHGIR),
			root->_hoops_IAPHA.faces
		);
		root->_hoops_PHAS = NULL; /* _hoops_PPSR _hoops_ARCR _hoops_HRGR _hoops_SRGH */
	}
	else {
		_hoops_CGAII = _hoops_GHAHI (_hoops_GAAII->m);
		ALLOC_ARRAY_ALIGNED (root->_hoops_IAPHA.points, 3 * _hoops_CGAII, float, 16);
		_hoops_GGAII(
			_hoops_GAAII->m, 
			&(root->_hoops_IAPHA.pcount),
			root->_hoops_IAPHA.points,
			&(root->_hoops_IAPHA._hoops_RHGIR),
			root->_hoops_IAPHA.faces,
			root->_hoops_CAPHA, 
			root->_hoops_PHAS
	  );
	}
	if (depth > 1) {
		ALLOC (root->next, _hoops_HAPHA);
		root->next->_hoops_CAPHA = root->_hoops_CAPHA;
		ALLOC_ARRAY (root->next->_hoops_PHAS, root->next->_hoops_CAPHA, int);

		root->next->next = NULL;
		_hoops_SRAII (
			root->next, 
			_hoops_GPPHA, 
			_hoops_GAAII, 
			(int) (_hoops_GPPHA->_hoops_PRPHA * _hoops_RAAII), 
			depth - 1 
	  );
	}
} /* _hoops_RSGR _hoops_API _hoops_PAAII */
	
GLOBAL_FUNCTION void HI_LOD_Execute(	
			int pcount, const float *_hoops_RHAAA, 
			int flist_length, const int *_hoops_ASPH, 
			_hoops_SAPHA *_hoops_IRAII, 
			int *new_pcount, float *new_points, 
			int *new_flist_length, int *_hoops_ASPHA, 
			int *_hoops_PHAS) {
	_hoops_GRAHI m;
	_hoops_APHHI _hoops_GAAII;
	_hoops_SAPHA _hoops_GPPHA;
	int num_faces;
	int _hoops_RAAII;

	_hoops_RRAHI (&m, pcount, 100);
	num_faces = _hoops_GSRII (&m, pcount, _hoops_RHAAA, 
						flist_length, _hoops_ASPH);
	_hoops_HRAII (_hoops_IRAII, &_hoops_GPPHA);
	_hoops_PPHHI (&_hoops_GAAII, &m, &_hoops_GPPHA);

	num_faces = _hoops_IPAHI (&m); /* _hoops_IGIPR _hoops_SGS _hoops_HCR _hoops_RSSI _hoops_CHR _hoops_APIP */
	_hoops_RAAII = (int) (_hoops_GPPHA._hoops_PRPHA * num_faces);
	_hoops_IPHHI (&_hoops_GAAII, _hoops_RAAII);
	_hoops_GGAII (&m, new_pcount, new_points, new_flist_length, 
						_hoops_ASPHA, pcount, _hoops_PHAS);

	/* _hoops_CASI _hoops_GH _hoops_ISCP _hoops_PPGS */
	_hoops_HPHHI (&_hoops_GAAII);
	_hoops_HRAHI (&m);

} 


GLOBAL_FUNCTION _hoops_HAPHA *HI_LOD_Chain_Execute_Tristrips(
				int point_count, const float *points,
				const Tristrip *tristrip, 
				_hoops_SAPHA *_hoops_IRAII, 
				int depth) {
	_hoops_GRAHI m;
	_hoops_APHHI _hoops_GAAII;
	_hoops_SAPHA _hoops_GPPHA;
	int num_faces;
	int _hoops_RAAII;
	_hoops_HAPHA *root;

	_hoops_RRAHI (&m, point_count, 100);
	_hoops_PCRII (&m, point_count, points, tristrip);
	_hoops_HRAII (_hoops_IRAII, &_hoops_GPPHA);
	_hoops_PPHHI (&_hoops_GAAII, &m, &_hoops_GPPHA);

	ALLOC (root, _hoops_HAPHA);
	root->_hoops_CAPHA = point_count;
	ALLOC_ARRAY (root->_hoops_PHAS, root->_hoops_CAPHA, int);
	root->next = NULL;

	num_faces = _hoops_IPAHI (_hoops_GAAII.m); /* _hoops_IGIPR _hoops_HCR _hoops_RSSI _hoops_CHR _hoops_APIP */
	_hoops_RAAII = (int) (_hoops_GPPHA._hoops_PRPHA * num_faces);
	_hoops_SRAII (root, &_hoops_GPPHA, &_hoops_GAAII, _hoops_RAAII, depth);		

	/* _hoops_CASI _hoops_GH _hoops_ISCP _hoops_PPGS */
	_hoops_HPHHI (&_hoops_GAAII);
	_hoops_HRAHI (&m);

	return root;

} 


GLOBAL_FUNCTION _hoops_HAPHA *HI_Compute_LOD_Fast(
				int pcount,
				const float *points,
				int _hoops_RHGIR, 
				const int *faces,
				float _hoops_PRPHA,
				int depth) {
	_hoops_HAPHA *root, *node;
	int i, _hoops_ACSHI;
	float min[3], max[3];

	_hoops_PRSHI (pcount, points, min, max);
	_hoops_ACSHI = _hoops_IRSHI (pcount, points, min, max, _hoops_PRPHA);
	root = _hoops_GPGII (pcount, points, _hoops_RHGIR, faces, min, max, _hoops_ACSHI);

	node = root;
	for (i = 0; i < depth - 1; i++) {
		_hoops_ACSHI = _hoops_IRSHI (
			node->_hoops_IAPHA.pcount, node->_hoops_IAPHA.points, 
			min, max, _hoops_PRPHA);
		node->next = _hoops_GPGII (
			node->_hoops_IAPHA.pcount, node->_hoops_IAPHA.points, 
			node->_hoops_IAPHA._hoops_RHGIR, node->_hoops_IAPHA.faces, 
			min, max, _hoops_ACSHI);
		if (node->next == null)
			break;
		node = node->next;
	}
	node->next = null;
	return root;
} 

GLOBAL_FUNCTION _hoops_HAPHA *HI_Compute_LOD_Tristrips_Fast(
				int pcount,
				const float *points,
				const Tristrip *t,
				float _hoops_PRPHA,
				int depth) {
	_hoops_HAPHA *root, *node;
	int i, _hoops_ACSHI;
	float min[3], max[3], _hoops_HAAII;

	_hoops_PRSHI (pcount, points, min, max);
	_hoops_ACSHI = _hoops_IRSHI (pcount, points, min, max, _hoops_PRPHA);
	root = _hoops_PPGII (pcount, points, t, min, max, _hoops_ACSHI);

	node = root;
	_hoops_HAAII = _hoops_PRPHA;
	for (i = 0; i < depth - 1; i++) {
		_hoops_HAAII *= _hoops_PRPHA;
		_hoops_ACSHI = _hoops_IRSHI (
			pcount, points, 
			min, max, _hoops_HAAII);
		node->next = _hoops_PPGII (
			pcount, points, t,
			min, max, _hoops_ACSHI);
		if (node->next == null)
			break;
		node = node->next;
	}
	node->next = null;
	return root;
} 



#endif

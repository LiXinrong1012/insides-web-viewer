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
 * $Id: obf_tmp.txt 1.59 2010-12-06 22:05:41 jason Exp $
 */

#ifndef _hoops_RSCAR
#define _hoops_RSCAR

#ifndef HOOPS_DEFINED
#include "hoops.h"
#endif


#if defined(HOOPS_DEFINED) && !defined(SOLARIS_SYSTEM) && !defined(AIX_SYSTEM)
//#_hoops_PPIP _hoops_ASCAR
#endif

#define V_PREFIX HOOPS_3DGS_

#include "utility/vlist.h"
#include "utility/vhash.h"
#include "utility/varray.h"
#include "utility/vheap.h"
#include "utility/vconf.h"

#define UTF_UTILS_API HOOPS_API 

#include "utility/utf_utils.h"


/* _hoops_PSCAR _hoops_HSCAR _hoops_ISCAR -- _hoops_GPRR _hoops_HIAGR _hoops_PIH _hoops_HCCGR _hoops_IIHA _hoops_GPP _hoops_SRPC _hoops_CICRR */


typedef char _hoops_CSCAR;

#define VBSP_STATUS_STOP		0
#define VBSP_STATUS_CONTINUE	1
#define VBSP_STATUS_SOMETHING	2

/* 
 * _hoops_SSCAR
 */ 
/* _hoops_GGSAR
	_hoops_RGSAR _hoops_PGCR _hoops_AGSAR _hoops_IIGR _hoops_HHH _hoops_CIS-_hoops_PAPR _hoops_CSSC (_hoops_IAS._hoops_ISHI. _hoops_PGSAR).  _hoops_CPGP _hoops_RH _hoops_RGAR _hoops_HPHS _hoops_SGS 
		_hoops_RH _hoops_SSCAR _hoops_SSCP _hoops_AHCA _hoops_RH _hoops_AGSAR _hoops_HRGR _hoops_PAII _hoops_PRCH, _hoops_SCH _hoops_HRGR _hoops_SHHA _hoops_SGS _hoops_RGR _hoops_API _hoops_GRS _hoops_ACPA _hoops_PCPA _hoops_IS _hoops_AA
		_hoops_CCA _hoops_CAPR.	_hoops_IPCP _hoops_PPS _hoops_API _hoops_HRGR _hoops_GACC _hoops_HGSAR _hoops_IH _hoops_GHGA _hoops_HISI _hoops_PGSI _hoops_CHR _hoops_RGHP _hoops_CGPR
		_hoops_RH _hoops_SSSC _hoops_CHR _hoops_IGSAR (_hoops_IAS._hoops_ISHI. _hoops_CGSAR'_hoops_GRI _hoops_SGSAR _hoops_RHAP _hoops_IRS _hoops_GRSAR)
   \_hoops_PRGH _hoops_RRSAR _hoops_RH _hoops_PIRA _hoops_ARSAR _hoops_GAR _hoops_SPR _hoops_IIGR _hoops_RH _hoops_PRSAR _hoops_IS _hoops_RH _hoops_AGRR _hoops_RPGP _hoops_PSCH.  
		_hoops_HHIGR _hoops_GRS _hoops_PASI _hoops_SHH _hoops_IRS _hoops_CRS _hoops_IS _hoops_IRS _hoops_HRPR _hoops_IIAAR _hoops_HCR _hoops_IIGR _hoops_RH _hoops_PIH _hoops_SGS _hoops_HRGR _hoops_HRSAR _hoops_IS _hoops_PCCP
		_hoops_RSIR _hoops_RPGP (_hoops_IAS._hoops_ISHI. _hoops_IRSAR) _hoops_CAIH.
   \_hoops_PRGH _hoops_CRSAR _hoops_RH _hoops_SRS _hoops_CARA _hoops_IIGR _hoops_RH _hoops_CIS-_hoops_PAPR _hoops_GPRR 
   \_hoops_PRGH _hoops_SRSAR (_hoops_GAR _hoops_CCA _hoops_CRSAR _hoops_ARRS) _hoops_RH _hoops_GIAP _hoops_CARA _hoops_IIGR _hoops_HHH _hoops_CIS-_hoops_PAPR _hoops_GPRR 
   \_hoops_HRS _hoops_RCPP _hoops_RPP _hoops_IIH _hoops_HRGR _hoops_PSP _hoops_RRP _hoops_IS _hoops_AA _hoops_GII _hoops_GASAR _hoops_PCGC (_hoops_IAS._hoops_ISHI. _hoops_RASAR _hoops_AASAR)
 */ 
typedef _hoops_CSCAR (*_hoops_PASAR)(void *_hoops_HASAR, void *_hoops_IASAR, void *_hoops_CASAR);
typedef _hoops_CSCAR (*_hoops_SASAR)(void *_hoops_HASAR, void *_hoops_IASAR, int _hoops_HGII);
/* _hoops_GPSAR
	_hoops_RPSAR _hoops_RH _hoops_RAGA _hoops_API _hoops_CRS _hoops_IS _hoops_GRR _hoops_IIGR _hoops_RH _hoops_APSAR _hoops_SGS _hoops_RIAGR _hoops_RPII _hoops_PPSAR _hoops_AIH _hoops_HPSAR
   \_hoops_PRGH _hoops_RRSAR _hoops_RH _hoops_PIRA _hoops_ARSAR _hoops_GAR _hoops_SPR _hoops_IIGR _hoops_RH _hoops_PRSAR _hoops_IS _hoops_RH _hoops_AGRR _hoops_RPGP _hoops_PSCH. 
   \_hoops_PRGH _hoops_IGCI _hoops_RH _hoops_CARA _hoops_IIGR _hoops_HHH _hoops_CIS-_hoops_PAPR _hoops_GPRR (_hoops_IAS._hoops_ISHI. _hoops_PGSAR)
   \_hoops_HRS _hoops_RCPP _hoops_RPP _hoops_IIH _hoops_HRGR _hoops_PSP _hoops_RRP _hoops_IS _hoops_SAS (_hoops_IAS._hoops_ISHI. _hoops_SR _hoops_AAPR _hoops_IPSAR _hoops_IH _hoops_CPHP _hoops_PPR _hoops_GSGI _hoops_SCH)
 */ 
typedef _hoops_CSCAR (*_hoops_CPSAR)(void *item, void *_hoops_HASAR);

// _hoops_IH _hoops_SPSAR
#include "database.h"

/* _hoops_SRGR _hoops_IIGR _hoops_RH _hoops_HSPR _hoops_HRPR _hoops_CGH _hoops_SHH _hoops_GHSAR _hoops_RHSAR.  _hoops_SPCA _hoops_CGH _hoops_SHH
 * _hoops_PSP _hoops_RRP _hoops_IS _hoops_IRIGR _hoops_PAR _hoops_GGI _hoops_CAPR _hoops_AHSAR _hoops_RHIR _hoops_RH _hoops_ARSAR _hoops_PHSAR */

struct VBSP;

struct _hoops_HHSAR{
	int used;
	void **items;
	_hoops_SASC const **item_bounds;
};

struct _hoops_IHSAR {
	VBSP *tree;
	int _hoops_CHSAR; /* _hoops_SHSAR, _hoops_GISAR, _hoops_PAR _hoops_RISAR */
	int _hoops_AISAR;
	int _hoops_PISAR;
	void **_hoops_RAGR;
	_hoops_HHSAR *_hoops_PAIS;
	_hoops_IHSAR *kids[3];  /* _hoops_HISAR, _hoops_CASH, _hoops_HHGP */ 
	bool _hoops_IISAR;
};

struct VBSP {
	Memory_Pool *			memory_pool;
	_hoops_SASC			bbox;				/* _hoops_IASC _hoops_CISAR _hoops_SGS _hoops_ICGI _hoops_HCR _hoops_APSAR _hoops_PPSAR */
	int						_hoops_SISAR;			/* _hoops_IGI _hoops_RGAR _hoops_CGPR _hoops_APSAR _hoops_CHR _hoops_PPSAR */
	_hoops_IHSAR *				root;				/* _hoops_GPRR _hoops_HRGR _hoops_PAPR _hoops_GGR _hoops_GCSAR._hoops_GSGGR */
	_hoops_PASAR		compare;			/* _hoops_ARP _hoops_RCSAR _hoops_GHIR _hoops_HII _hoops_RSCRR _hoops_ACSAR* _hoops_RSCRR _hoops_HIGR */
	_hoops_SASAR		_hoops_PCSAR;			/* _hoops_ARP _hoops_RCSAR _hoops_GHIR _hoops_HII _hoops_RSCRR _hoops_ACSAR* _hoops_RSCRR _hoops_HIGR */
	void *					_hoops_HCSAR;	/* _hoops_PCAGR */
	bool					_hoops_ICSAR;
	Vector					_hoops_CCSAR;
	float					_hoops_SCSAR;
	bool					_hoops_GSSAR;
};

/* _hoops_RSSAR _hoops_IRS _hoops_CCAH _hoops_SSCAR _hoops_CARA */
GLOBAL_FUNCTION VBSP *HI_New_BSP(Memory_Pool * memory_pool, _hoops_SASC const & bbox_in, int max_depth_in);

/* _hoops_ASSAR _hoops_HRGR _hoops_HGSAR _hoops_RGAR _hoops_IH _hoops_PSSAR _hoops_IIGR _hoops_RH _hoops_HSSAR _hoops_ACAS.  _hoops_ISSAR _hoops_IIGR _hoops_GII _hoops_APSAR _hoops_SGS _hoops_AAPR
   _hoops_PPSAR _hoops_CRGR _hoops_RH _hoops_HSSAR _hoops_HRGR _hoops_RH _hoops_IPSP'_hoops_GRI _hoops_CSSAR (_hoops_AAPP: _hoops_SGH _hoops_SSSAR) */
GLOBAL_FUNCTION void HI_Delete_BSP(VBSP *tree);

/* _hoops_CGP _hoops_SSRR, _hoops_HSPP _hoops_GGGPR _hoops_PIH _hoops_GPRR _hoops_CCA _hoops_RH 6 _hoops_PHRP _hoops_IH _hoops_PRCH _hoops_PPR _hoops_SGH 
	  _hoops_RH _hoops_PSHR _hoops_CRS _hoops_IH _hoops_GIPR _hoops_IGCI _hoops_PPR _hoops_IGCI _hoops_PRCH (_hoops_IRAP _hoops_IH _hoops_RGGPR _hoops_GRS
	  _hoops_HS _hoops_RH _hoops_PSHR _hoops_GIRRR).  _hoops_HGI _hoops_GRS _hoops_SRCH _hoops_RH _hoops_RRP _hoops_IS _hoops_IPS _hoops_RH _hoops_IASC _hoops_AHCRR
	  _hoops_HPGR _hoops_RH _hoops_GHIR _hoops_IIGR _hoops_AGGPR (_hoops_CR _hoops_SR _hoops_PAH _hoops_ACPA _hoops_SGS _hoops_RH _hoops_AHCRR _hoops_CRS _hoops_HRGR _hoops_HAR _hoops_CPIC _hoops_IS
	  _hoops_SHH _hoops_PGGPR _hoops_HGGPR) 
   \_hoops_PRGH _hoops_HHIS _hoops_RH _hoops_SSCAR _hoops_CARA, _hoops_GAR _hoops_SPIP _hoops_HPP _hoops_IGGPR
   \_hoops_PRGH _hoops_IGCI _hoops_RH _hoops_IGCI _hoops_IS _hoops_SHH _hoops_PPSAR
   \_hoops_PRGH _hoops_IGCI _hoops_PRCH _hoops_PCCP _hoops_CRPR _hoops_IIGR 6 _hoops_PHRP (_hoops_CGGPR[_hoops_SGGPR],_hoops_AHPA[_hoops_SGGPR]) _hoops_SGS _hoops_SCIR _hoops_RH _hoops_IASC _hoops_IPIS _hoops_IIGR _hoops_RH
	  _hoops_PPSAR _hoops_IGCI.  _hoops_CGP _hoops_PGI _hoops_IRAP _hoops_PAR _hoops_RH _hoops_PSHR _hoops_GRGPR _hoops_GAR "_hoops_IGCI", _hoops_SR _hoops_HPCAR _hoops_SGS "_hoops_IGCI" _hoops_RRGPR _hoops_CCA _hoops_RH
	  _hoops_ARGPR _hoops_HPHS _hoops_PPR _hoops_IRAA _hoops_SCH _hoops_HII _hoops_IIH (_hoops_PRGPR _hoops_HRGPR _hoops_IRS _hoops_IPS)
*/
GLOBAL_FUNCTION void HI_BSP_Insert( VBSP *tree, void *item, _hoops_SASC const * item_bounds=null);


/* _hoops_SAHR _hoops_PII _hoops_IRGPR'_hoops_GRI _hoops_ARCR _hoops_API, _hoops_AHSAR _hoops_GGGPR _hoops_API _hoops_HRS	 
	  1 _hoops_IS _hoops_GRHP _hoops_CPIC
	  0 _hoops_IS _hoops_RRS */
GLOBAL_FUNCTION int HI_BSP_Map_Function(
	VBSP *			tree,
	_hoops_CPSAR	function,
	void *			user_data);

/* _hoops_AGCR _hoops_PSCH _hoops_CHR _hoops_APGP _hoops_IRS _hoops_CRGPR _hoops_IIGR _hoops_SRGPR _hoops_SGS _hoops_HRGR _hoops_GAGPR
	  _hoops_RAGPR _hoops_GPP _hoops_PIS _hoops_IRS _hoops_PCHC _hoops_AAGPR (_hoops_PGI _hoops_PIS _hoops_PAGPR'_hoops_HAGPR _hoops_PAR 
	  _hoops_IAGPR _hoops_IRS _hoops_HGGS) */
/* _hoops_RPGP _hoops_IRS _hoops_HSSAR _hoops_ACSRR _hoops_ARSAR _hoops_IASC _hoops_IPIS */
GLOBAL_FUNCTION int HI_Test_BSP( 
	VBSP *					tree, 
	_hoops_PASAR		_hoops_CAGPR,
	void *					_hoops_HASAR, 
	void *					_hoops_CASAR, 
	_hoops_SASC const &	_hoops_RCHS, 
	bool					_hoops_SAGPR);

GLOBAL_FUNCTION int HI_Test_BSP_Bounding_Reject( 
	VBSP *					tree, 
	_hoops_PASAR		_hoops_CAGPR,
	_hoops_SASAR		_hoops_GPGPR,
	void *					_hoops_HASAR, 
	void *					_hoops_CASAR, 
	_hoops_SASC const &	_hoops_RCHS);

/* _hoops_RPGP _hoops_RH _hoops_APSAR _hoops_GGR _hoops_SPR _hoops_HSSAR _hoops_RH _hoops_APSAR _hoops_GGR _hoops_RH _hoops_RII _hoops_SPR */
GLOBAL_FUNCTION int HI_Test_BSP_BSP( 
	VBSP *				tree, 
	_hoops_PASAR	_hoops_CAGPR,
	void *				_hoops_HASAR, 
	VBSP *				_hoops_RPGPR,
	bool				_hoops_ICSAR);

/* _hoops_RPGP _hoops_IRS _hoops_HSSAR _hoops_ACSRR _hoops_IRS _hoops_HGGS */
GLOBAL_FUNCTION bool HI_Test_BSP_Ray(
	VBSP *				tree, 
	_hoops_PASAR	_hoops_CAGPR,
	void *				_hoops_HCSAR,
	void *				part,
	Point const *		start,
	Vector const *		direction);

#endif /*_hoops_APGPR*/



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
 * $Id: obf_tmp.txt 1.48 2008-03-19 21:18:59 covey Exp $
 */

#ifndef _hoops_IPPAS

/* _hoops_GAGA-_hoops_PPR-_hoops_HSPH _hoops_PIH _hoops_HCCGR _hoops_PPR _hoops_HPHS */

#	define		_hoops_SIPHP		1		/* _hoops_CSH _hoops_HIHP */
#	define		_hoops_CIPHP			2		/* _hoops_ARGIH _hoops_GGR --> _hoops_ARGIH _hoops_GGSR */
#	define		_hoops_PCPHP			3		/* _hoops_SPRGGR _hoops_GGR --> _hoops_ARGIH _hoops_GGSR */
#	define		_hoops_ACPHP		0		/* _hoops_SPRGGR _hoops_GGR --> _hoops_SPRGGR _hoops_GGSR */
#	define		_hoops_RCPHP		5		/* _hoops_SPRGGR _hoops_GGR --> _hoops_ARGIH/_hoops_SRSCI _hoops_GGSR */
#	define		_hoops_GCPHP		4		/* _hoops_SPRGGR _hoops_GGR --> _hoops_SPRGGR/_hoops_SRSCI _hoops_GGSR */
#	define		_hoops_GHRGGR				5
#	define		_hoops_PGSC(x)	(!ANYBIT(x, 3))
#	define		_hoops_IHGSP(x)	((x) >= 4)


#define	_hoops_CCIIS	256

typedef unsigned char	_hoops_GRCAR;
#define _hoops_HCRCP				(_hoops_GRCAR)0x00
#define _hoops_SCIIS			(_hoops_GRCAR)0x01		/* _hoops_PIHA _hoops_SHH _hoops_GGR _hoops_AGR! */
#define _hoops_GSIIS			(_hoops_GRCAR)0x02		/* (_hoops_RPIA-_hoops_SIACP	 */
#define CC_OFF_TO_RIGHT			(_hoops_GRCAR)0x04		/*	_hoops_IRHAP _hoops_GPP _hoops_SCH.)	 */
#define CC_OFF_TO_BOTTOM		(_hoops_GRCAR)0x08
#define _hoops_IPCAR		(_hoops_GRCAR)0x10
#define	_hoops_RPCAR		(_hoops_GRCAR)0x20


/* "_hoops_PRSHA" _hoops_CPPC _hoops_RSH _hoops_GGGR _hoops_IS _hoops_RH _hoops_RHC _hoops_IPPA _hoops_CPHP _hoops_PAH _hoops_RCPS _hoops_SIHH
 * _hoops_IHGS _hoops_SACH. (_hoops_GPIP _hoops_SAAP _hoops_HRGR _hoops_HPGR _hoops_SRSCI=1.0, _hoops_SARA _hoops_AHC _hoops_HRGR _hoops_HPGR _hoops_SRSCI=0.0,
 * _hoops_PRSHA _hoops_HRGR _hoops_GGR _hoops_GAPA.) _hoops_IPCP _hoops_SCHIA _hoops_IS _hoops_AHHR _hoops_SCH _hoops_HRGR, _hoops_RH _hoops_RRI _hoops_CCCI _hoops_RH
 * _hoops_SPCR _hoops_PPR _hoops_GHCR _hoops_HIH _hoops_RH _hoops_RRI _hoops_RHRGGR _hoops_RH _hoops_AHCR/_hoops_SRSCI.
 */
#define _hoops_GIPHP			-0.001f



#define _hoops_HRRRC(m, p) ((m)[0][0]*(p).a+(m)[0][1]*(p).b+(m)[0][2]*(p).c+(m)[0][3]*(p).d)
#define _hoops_IRRRC(m, p) ((m)[1][0]*(p).a+(m)[1][1]*(p).b+(m)[1][2]*(p).c+(m)[1][3]*(p).d)
#define _hoops_CRRRC(m, p) ((m)[2][0]*(p).a+(m)[2][1]*(p).b+(m)[2][2]*(p).c+(m)[2][3]*(p).d)
#define _hoops_AHRGGR(m, p) ((m)[3][0]*(p).a+(m)[3][1]*(p).b+(m)[3][2]*(p).c+(m)[3][3]*(p).d)

#define _hoops_HPRA(m, p) ((m)[0][0]*(p).x+(m)[1][0]*(p).y+(m)[2][0]*(p).z+(m)[3][0])
#define _hoops_IPRA(m, p) ((m)[0][1]*(p).x+(m)[1][1]*(p).y+(m)[2][1]*(p).z+(m)[3][1])
#define _hoops_CPRA(m, p) ((m)[0][2]*(p).x+(m)[1][2]*(p).y+(m)[2][2]*(p).z+(m)[3][2])
#define _hoops_PHCP(m, p) ((m)[0][3]*(p).x+(m)[1][3]*(p).y+(m)[2][3]*(p).z+(m)[3][3])
#define _hoops_PRPPI(m,p) ((m)[0][0]*(p).x+(m)[1][0]*(p).y+(m)[3][0])
#define _hoops_HRPPI(m,p) ((m)[0][1]*(p).x+(m)[1][1]*(p).y+(m)[3][1])

/* _hoops_RPICR _hoops_GAR _hoops_PHRGGR,_hoops_GHCR,_hoops_AHCR _hoops_HIH _hoops_IH _hoops_SGH _hoops_CCA _hoops_GPHA _hoops_GRPAR... */
#define _hoops_CCRIS(m,p)	((m)[0][0]*(p)[0]+(m)[1][0]*(p)[1]+(m)[2][0]*(p)[2]+(m)[3][0])
#define _hoops_SCRIS(m,p)	((m)[0][1]*(p)[0]+(m)[1][1]*(p)[1]+(m)[2][1]*(p)[2]+(m)[3][1])
#define _hoops_GSRIS(m,p)	((m)[0][2]*(p)[0]+(m)[1][2]*(p)[1]+(m)[2][2]*(p)[2]+(m)[3][2])
#define _hoops_ICRIS(m,p) ((m)[0][3]*(p)[0]+(m)[1][3]*(p)[1]+(m)[2][3]*(p)[2]+(m)[3][3])

/* _hoops_HHRGGR[_hoops_SPRGGR] _hoops_HRGR _hoops_IRS _hoops_IHRGGR[_hoops_SPRGGR] _hoops_SGS _hoops_IGIPR _hoops_RH _hoops_SRSCI _hoops_PIHP _hoops_HRGR 0 */
#define _hoops_HPSPH(m, p) ((m)[0][0]*(p).x+(m)[1][0]*(p).y+(m)[2][0]*(p).z)
#define _hoops_IPSPH(m, p) ((m)[0][1]*(p).x+(m)[1][1]*(p).y+(m)[2][1]*(p).z)
#define _hoops_CPSPH(m, p) ((m)[0][2]*(p).x+(m)[1][2]*(p).y+(m)[2][2]*(p).z)

#define _hoops_IPPAS
#endif

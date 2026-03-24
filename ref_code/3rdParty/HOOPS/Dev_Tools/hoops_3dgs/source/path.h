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
 * $Id: obf_tmp.txt 1.25 2010-06-16 22:04:10 covey Exp $
 */

#ifndef _hoops_HRACC

Begin_HOOPS_Namespace

#define _hoops_RPPSA			1		/* _hoops_IRCH _hoops_PSHS _hoops_IRACC */
#define _hoops_AIPPR		2		/* *,%... _hoops_CHR _hoops_GPRS _hoops_GGR _hoops_RHAR */
#define QUALIFIERS		4		/* {}<>! _hoops_CHR _hoops_GPRS */

struct _hoops_RSAPR {
	_hoops_RSAPR			*next;
	int						type;
	_hoops_HCRPR					_hoops_AGPPR;		/* _hoops_RPP _hoops_GPRR = _hoops_CRACC */
	_hoops_RSAPR			*expansion;		/* _hoops_RPP _hoops_GPRR = _hoops_SRACC */
												/* (_hoops_RGAR _hoops_APIP _hoops_RHSP _hoops_PPPCR!) */
	Key					key;			/* _hoops_RPP _hoops_GPRR = _hoops_GAACC */
	int						level;			/* _hoops_RPP _hoops_GPRR == _hoops_RAACC* _hoops_PAR
															  _hoops_AAACC* */
	bool					_hoops_GARHH;
};

#define _hoops_ISAPR				1
#define _hoops_CSAPR				2
#define _hoops_SSAPR			3
#define _hoops_GGPPR			4
#define _hoops_RGPPR			5
#define _hoops_SGPPR				6
#define _hoops_GRPPR				7
#define _hoops_RRPPR				8
#define _hoops_ARPPR			9
#define _hoops_PRPPR				10
#define _hoops_PGPPR				11
#define _hoops_HGPPR			12
#define _hoops_IGPPR			13
#define _hoops_CGPPR		14
#define _hoops_CSRCC				15
#define _hoops_HRPPR				16
#define _hoops_HSAPR			17
#define _hoops_PGRHH	18

End_HOOPS_Namespace;

#define _hoops_HRACC
#endif

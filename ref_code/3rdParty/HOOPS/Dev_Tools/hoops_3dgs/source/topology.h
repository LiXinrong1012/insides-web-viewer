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
 * $Id: obf_tmp.txt 1.21 2010-06-16 22:04:10 covey Exp $
 */


Begin_HOOPS_Namespace

struct _hoops_APRGGR {
	_hoops_APRGGR		*next, *prev;

	bool				_hoops_HASHH;
	int					owner;
	int					region;

#	define _hoops_PGHAS					0
#	define _hoops_HGHAS					1
	Point			*pt[2];
};



/*
 * _hoops_IRS "_hoops_CRHAS" _hoops_HRGR _hoops_AIIA _hoops_IRS _hoops_AAIA _hoops_GPHA, _hoops_GCIAH _hoops_HRSP _hoops_ARAR:
 * 1. _hoops_SSRS _hoops_RSSA _hoops_GIRP _hoops_SRSGR _hoops_IRS _hoops_RSRA _hoops_CRHAS
 *	  _hoops_GGR _hoops_RGR _hoops_AGIR, _hoops_RAAP _hoops_PPR _hoops_RPHR _hoops_GHCA _hoops_HS _hoops_HAGH _hoops_HSH, _hoops_HIH
 *	  _hoops_RH _hoops_RSSA _hoops_IS _hoops_PGAP _hoops_SSIA _hoops_ACAHR _hoops_PIHA _hoops_SHH _hoops_RCGRA
 * 2. _hoops_HCR _hoops_RSSA _hoops_RIHA _hoops_GPP _hoops_IRS _hoops_IRGGA _hoops_SRSGR _hoops_IRS _hoops_RSRA _hoops_CRHAS
 *	  _hoops_ARI, _hoops_RAAP _hoops_RSSA _hoops_IS _hoops_RH _hoops_PHSHH _hoops_PPSR _hoops_GPP _hoops_RH _hoops_IRGGA,
 *	  _hoops_RPHR _hoops_RSSA _hoops_IS _hoops_RH _hoops_SHGRGR.
 * 3. _hoops_IIGR _hoops_IPGAA, _hoops_IRS _hoops_GIGRGR _hoops_GPHA _hoops_RAACR _hoops_IRS _hoops_CRHAS
 *	  _hoops_GGR _hoops_RGR _hoops_AGIR, _hoops_RAAP _hoops_PPR _hoops_RPHR _hoops_ACAHR _hoops_IS _hoops_RH _hoops_PSHR _hoops_PPSR
 */
struct _hoops_GPCIH {
	_hoops_GPCIH				*next;			/* _hoops_SPRS _hoops_AGGAR */

#	define _hoops_HRASA			0
#	define _hoops_IGHAS			1
	_hoops_APRGGR		_hoops_GRCPR[2];

#	define _hoops_RIGRGR		0x02
#	define _hoops_AIGRGR		0x01
#	define _hoops_CGHAS				0x03	/* _hoops_GIPR _hoops_CHR _hoops_PIGRGR */
#	define _hoops_HIGRGR					0x00	/* _hoops_RSIPR _hoops_HRGR _hoops_PIGRGR */
	int					type;			/* _hoops_IIGRGR _hoops_IIGR _hoops_RGR _hoops_CRHAS */

	int					owner;
	int					region;

	bool				_hoops_HASHH;
	float				_hoops_SSAGS[2];
};




struct _hoops_RGASA {
	_hoops_RGASA		*left, *right;
	Vector			_hoops_GRASA;
	int					_hoops_HGASA;
};

End_HOOPS_Namespace;


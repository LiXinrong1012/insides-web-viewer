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
 * $Id: obf_tmp.txt 1.50 2010-06-16 22:04:10 covey Exp $
 */

/* _hoops_PAGA: _hoops_SHR _hoops_GGCR _hoops_GPCPR 0.01 _hoops_IS _hoops_RH _hoops_CSPP _hoops_PHI _hoops_IH _hoops_IRS _hoops_GSSR
 *		 _hoops_CSPP-_hoops_PHI '_hoops_PH'. _hoops_PS *_hoops_AAPR* _hoops_CPRAA 0.1 _hoops_GGR _hoops_RH _hoops_GSSR
 *		 _hoops_AGIR, _hoops_HIH _hoops_SGS _hoops_CSAP _hoops_CPIC _hoops_IS _hoops_GGHC _hoops_RH _hoops_RGGHR _hoops_IS _hoops_ARAS _hoops_GGSR _hoops_HAH
 *		 _hoops_HAAI.
 */

#ifndef _hoops_ASHII
#define _hoops_ASHII

Begin_HOOPS_Namespace

#define _hoops_PRCCR  1.25f  /* (_hoops_RH _hoops_RRGR _hoops_IGIPR 2 _hoops_PSHII _hoops_IHRSP) */

#define _hoops_HSHII		100
#define _hoops_ISHII			100
#define _hoops_CSHII			1000
#define _hoops_SSHII		100

struct _hoops_GGIII {
	_hoops_GGIII		*next;

#	define		_hoops_RGIII	0
#	define		_hoops_AGIII		1
#	define		_hoops_PGIII		2
#	define		_hoops_HGIII	3
#	define		_hoops_IGIII	4
#	define		_hoops_CGIII		5
#	define		_hoops_SGIII		6
#	define		_hoops_GRIII		7
#	define		_hoops_RRIII			8
#	define		_hoops_ARIII		9
#	define		_hoops_PRIII	10
	int			type;
};

#define _hoops_HRIII		1024		// _hoops_CIGS _hoops_IRIII
#define _hoops_CRIII		32768		// _hoops_SAIPR _hoops_IS _hoops_SRIII _hoops_PPR _hoops_HCHC _hoops_RRAI _hoops_RAS _hoops_SGS

struct _hoops_GAIII {
	_hoops_AIGPR *	_hoops_RIGC;
	_hoops_GGIII *		_hoops_RAIII,
							_hoops_AAIII;

	int					version;

	int					_hoops_PAIII;

	Key					new_key;
	Key					_hoops_HAIII;

	_hoops_HCRPR				_hoops_IAIII;
	_hoops_HCRPR				_hoops_ISHAP;

	_hoops_IRIPH *			_hoops_GRHRI;

	Point				_hoops_CAIII[_hoops_HSHII];
	int					_hoops_SAIII;
	int					_hoops_GPIII;
	Point *				_hoops_RPIII;

	int					_hoops_APIII[_hoops_ISHII];
	int					_hoops_PPIII;
	int					_hoops_HPIII;
	int *				_hoops_IPIII;

	int					_hoops_CPIII[_hoops_ISHII];
	int					_hoops_SPIII;
	int					_hoops_GHIII;
	int *				_hoops_RHIII;

	char				_hoops_AHIII[_hoops_CSHII];
	int					_hoops_PHIII;
	int					_hoops_HHIII;
	char *				_hoops_IHIII;

	float				_hoops_CHIII[_hoops_SSHII];
	int					_hoops_SHIII;
	int					_hoops_GIIII;
	float *				_hoops_RIIII;

	_hoops_ARPA				_hoops_AIIII[_hoops_HSHII];
	int					_hoops_PIIII;
	int					_hoops_HIIII;
	_hoops_ARPA *				_hoops_IIIII;

	/* _hoops_IRS _hoops_HSHRR _hoops_RAIA _hoops_IRS _hoops_PPSR-_hoops_CRPR _hoops_CSRR; _hoops_CIIII == _hoops_HAPHR * _hoops_IAPHR */
	int					_hoops_SIIII;
	int					_hoops_GCIII;

	/* _hoops_PPSI _hoops_AGCR _hoops_GGR _hoops_ARI _hoops_HIS _hoops_SSIA'_hoops_ASAR _hoops_GPP _hoops_RH _hoops_SIHPA */
	char				*_hoops_RCIII,
						*_hoops_ACIII,
						*_hoops_PCIII,
						*_hoops_HCIII,
						*_hoops_ICIII;
	int					_hoops_CCIII, _hoops_SCIII, _hoops_GSIII,
						_hoops_RSIII, _hoops_ASIII;

	/* _hoops_PPR _hoops_PPSI _hoops_AGCR _hoops_GGR _hoops_ARI _hoops_IS _hoops_PSIII _hoops_HICA _hoops_HSIII _hoops_AHCA
	 * _hoops_PPRAR _hoops_CCPAR. _hoops_AISRR _hoops_HRGR _hoops_ISIII _hoops_IRGH _hoops_IS _hoops_CSIII.
	 */
	float				a0[4][4];
	Point				*_hoops_GGIAR, *p1, *p2;
	int					_hoops_SSIII, i1, i2, _hoops_SAPH;
	long				_hoops_GGCII, _hoops_SARAA;
	float				_hoops_AIPCP, f1, f2, _hoops_CGHGR, _hoops_SGHGR, _hoops_RGCII;
	Point				_hoops_AGCII, _hoops_AIGCR, _hoops_PIGCR;
	void				**_hoops_PGCII;
	int					width, height;
};

End_HOOPS_Namespace;

#endif


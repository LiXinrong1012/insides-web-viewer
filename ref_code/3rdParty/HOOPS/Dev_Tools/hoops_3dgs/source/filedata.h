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
 * $Id: obf_tmp.txt 1.29 2010-06-16 22:04:10 covey Exp $
 */

#ifndef _hoops_ARIPH
#define _hoops_ARIPH

Begin_HOOPS_Namespace

#define			_hoops_PRIPH			1024

#define			FILE_For_Reading		(int)0
#define			FILE_For_Writing		(int)1

#define			DIR_Select_Readable		(int)0x01
#define			DIR_Select_Writeable	(int)0x02
#define			DIR_Select_Executable	(int)0x04
#define			DIR_Select_File			(int)0x08
#define			DIR_Select_Directory	(int)0x10

#define			_hoops_HRIPH 0x1

struct _hoops_IRIPH {
	void				*_hoops_CRIPH;
	char				buffer[2][_hoops_PRIPH + 2];
										   /* _hoops_SRIPH _hoops_SPR _hoops_RAPSR _hoops_HIS _hoops_SGS
											&_hoops_SRHR[0][_hoops_GAIPH] _hoops_HRGR
											_hoops_RPRI. _hoops_ICAGR _hoops_RRI _hoops_IS _hoops_IRHH _hoops_PRGI. */
	int					_hoops_RAIPH;
	char				*_hoops_ASAPR,
						*_hoops_PSAPR;
	char				*_hoops_AAIPH,
						*_hoops_PAIPH;
	bool				_hoops_HAIPH,
						_hoops_IAIPH;
	char const			*message,
						*_hoops_RGHGA;
	int					_hoops_CAIPH;
	int					user_data;
	int					_hoops_SAIPH,
						_hoops_GPIPH,
						_hoops_RPIPH,
						_hoops_APIPH;
	_hoops_HCRPR				filename;
	bool				_hoops_PPIPH,
						_hoops_HHGHP,
						_hoops_HPIPH,
						_hoops_IPIPH,
						_hoops_CPIPH;
	float				version;
	int					_hoops_SAPPR;
};

#define _hoops_SPIPH(_hoops_GHIPH) ((_hoops_GHIPH)->_hoops_PSAPR == (_hoops_GHIPH)->_hoops_ASAPR && (_hoops_GHIPH)->_hoops_HAIPH)

End_HOOPS_Namespace;

#endif

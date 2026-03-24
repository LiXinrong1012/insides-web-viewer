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
 * $Id: obf_tmp.txt 1.112 2009-10-12 23:03:55 covey Exp $
 */

#ifndef _hoops_RHCCC

#ifndef HI_PROTO_DEFINED
#	include "hi_proto.h"
#endif


/* _hoops_PGGGI _hoops_RIRA _hoops_CGSI _hoops_PSIGA _hoops_RHSP _hoops_CPHAR _hoops_ASCA. */

#define _hoops_AHCCC(x)		((Named_Material const *)(x))
#define _hoops_PHCCC(x)		((_hoops_RHAH const *)(x))

#define _hoops_ICRCP(_hoops_SPRAR, _hoops_HHCCC, _hoops_PSACR, _hoops_PPCCP, _hoops_IARCP) do {		\
		float			_hoops_IHCCC;											\
		int				_hoops_CHCCC;											\
		void			*_hoops_SHCCC, *_hoops_GICCC;									\
		_hoops_GICCC = (void *)(_hoops_SPRAR);											\
		if ((_hoops_HHCCC) == (int)(_hoops_HHCCC) || !_hoops_PPCCP) {		\
			_hoops_SHCCC = (void *)(_hoops_PHCCC(_hoops_GICCC)->_hoops_HAA +					\
							 (int)((_hoops_HHCCC) + 0.5f) %				\
						   _hoops_PHCCC(_hoops_GICCC)->length);						\
			_hoops_PSACR = _hoops_AHCCC(_hoops_SHCCC)->_hoops_CSHR;						\
		}																\
		else {															\
			_hoops_IHCCC = (float)(_hoops_HHCCC) +								\
					(float)_hoops_PHCCC(_hoops_GICCC)->length; /* _hoops_IRHH _hoops_RPRHR */	\
			_hoops_CHCCC = (int)_hoops_IHCCC;										\
			_hoops_IHCCC -= (float)_hoops_CHCCC;										\
			_hoops_SHCCC = (void *)(_hoops_PHCCC(_hoops_GICCC)->_hoops_HAA +					\
						   _hoops_CHCCC % _hoops_PHCCC(_hoops_GICCC)->length);				\
			_hoops_GICCC = (void *)(_hoops_PHCCC(_hoops_GICCC)->_hoops_HAA + (_hoops_CHCCC + 1) %	\
										  _hoops_PHCCC(_hoops_GICCC)->length);		\
			_hoops_PIPCP (_hoops_AHCCC(_hoops_SHCCC)->_hoops_CSHR,				\
							 _hoops_AHCCC(_hoops_GICCC)->_hoops_CSHR, _hoops_IHCCC, _hoops_PSACR);\
		}																\
		if (BIT (_hoops_IARCP.options, _hoops_CHRH))								\
			_hoops_PSACR = HD_Apply_Color_Effects (_hoops_PSACR, _hoops_IARCP);					\
	} while (0)

#define _hoops_CARCP(_hoops_SPRAR, index, _hoops_RICCC) do {			\
		void *_hoops_SHCCC = (void *)(_hoops_SPRAR);	\
		_hoops_SHCCC = (void *)(_hoops_PHCCC(_hoops_SHCCC)->_hoops_HAA +		\
				 (index) % _hoops_PHCCC(_hoops_SHCCC)->length);		\
		_hoops_RICCC = _hoops_AHCCC(_hoops_SHCCC)->_hoops_CSHR;		\
	} while (0)


#define _hoops_SIPCP(dc, _hoops_AICCC) \
	do if ((dc)->options._hoops_SRSSP) {							\
		RGBAS32		*_hoops_IASGR = &(_hoops_AICCC);				\
		_hoops_IASGR->r = (dc)->_hoops_PGCC._hoops_HHHHP[_hoops_IRGCR(_hoops_IASGR->r)]; \
		_hoops_IASGR->g = (dc)->_hoops_PGCC._hoops_HHHHP[_hoops_IRGCR(_hoops_IASGR->g)]; \
		_hoops_IASGR->b = (dc)->_hoops_PGCC._hoops_HHHHP[_hoops_IRGCR(_hoops_IASGR->b)]; \
	} while (0)



#define _hoops_RSRCP(a, b, _hoops_PICCC, _hoops_PAGR)		do {					\
		Point const	*_hoops_HICCC = (Point const *)&(a); \
		Point const	*_hoops_IICCC = (Point const *)&(b); \
		(_hoops_PAGR).x = _hoops_HICCC->x + (_hoops_IICCC->x - _hoops_HICCC->x) * (_hoops_PICCC);				\
		(_hoops_PAGR).y = _hoops_HICCC->y + (_hoops_IICCC->y - _hoops_HICCC->y) * (_hoops_PICCC);				\
		(_hoops_PAGR).z = _hoops_HICCC->z + (_hoops_IICCC->z - _hoops_HICCC->z) * (_hoops_PICCC);				\
	}	while (0)


#define _hoops_CICCC(tmp) ((Vector const *)(tmp))
#define _hoops_ASRCP(_hoops_SICCC, in1, _hoops_PICCC, _hoops_PAGR) do {		\
		Vector		result;									\
		Vector const *_hoops_HICCC = (Vector *)&(_hoops_SICCC);				\
		Vector const *_hoops_IICCC = (Vector *)&(in1);				\
		result.x = _hoops_HICCC->x + (_hoops_IICCC->x - _hoops_HICCC->x) * (_hoops_PICCC);	\
		result.y = _hoops_HICCC->y + (_hoops_IICCC->y - _hoops_HICCC->y) * (_hoops_PICCC);	\
		result.z = _hoops_HICCC->z + (_hoops_IICCC->z - _hoops_HICCC->z) * (_hoops_PICCC);	\
		(void)HI_Normalize (&result);						\
		_hoops_PAGR = result;										\
	}	while (0)


#define _hoops_PSSIP			0x10010010
#define _hoops_SAGHC		0x10F10010
#define _hoops_GPGHC	0x10B10010
#define _hoops_ISSIP			0x10010001 /*_hoops_HSP*/
#define _hoops_SSSIP			0x10010000
#define _hoops_RGGCP			0x10001010
#define _hoops_PGGCP			0x10001001 /*_hoops_HSP*/
#define _hoops_IGGCP			0x10001000
#define _hoops_SGGCP			0x10000110 /*_hoops_HSP*/
#define _hoops_RRGCP			0x10000101 /*_hoops_HSP*/
#define _hoops_PRGCP			0x10000100 /*_hoops_HSP*/
#define _hoops_IRGCP			0x10000010
#define _hoops_SRGCP			0x10000001 /*_hoops_HSP*/
#define _hoops_RAGCP			0x10000000


#define _hoops_RHCCC	TRUE
#endif /* _hoops_GCCCC */


/*
 * Copyright (c) 2005 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.8 2009-02-03 01:56:12 jason Exp $
 */

#ifndef HOOPS_PROCESSOR_SPECIFIC_FUNCTIONALITY_DEFINED

#ifdef _hoops_IIIPA
	/*
		_hoops_SSHAI _hoops_IH _hoops_CIGR, _hoops_GGIAI _hoops_IH _hoops_RGCPR _hoops_RGIAI
		_hoops_PCASA _hoops_AGIAI _hoops_GPP _hoops_RHAR _hoops_CPCPR (_hoops_SHCAR, _hoops_PGIAI _hoops_AGSR [_hoops_ICIPA]) _hoops_IGI _hoops_CCA _hoops_AGCR _hoops_CIGR
	 */

#	ifdef _hoops_HGIAI
#		define	EAX				[eax]
#		define	EBX				[ebx]
#		define	_hoops_IGIAI				[ecx]
#		define	EDX				[edx]
#		define	_hoops_RCCPA				[edi]
		/* _hoops_CGIAI* _hoops_CGH _hoops_SHH _hoops_IHRI _hoops_GAR-_hoops_HRGR */


#		define	FXSAVE(d)				__asm	fxsave		d
#		define	_hoops_SGIAI(d)				__asm	fxrstor		d
#		define  LDMXCSR(d)				__asm	ldmxcsr		d
#		define  STMXCSR(d)				__asm	stmxcsr		d

#		define  _hoops_GRIAI(d)			__asm	prefetchnta	d
#		define  _hoops_RRIAI(d)			__asm	prefetcht0	d
#		define  _hoops_ARIAI(d)			__asm	prefetcht1	d
#		define  _hoops_PRIAI(d)			__asm	prefetcht2	d

#		define  ADDPS(d,s)				__asm	addps		d, s
#		define  _hoops_HRIAI(d,s)				__asm	subps		d, s
#		define  MULPS(d,s)				__asm	mulps		d, s
#		define  _hoops_RICPA(d,s)				__asm	divps		d, s
#		define  _hoops_IRIAI(d,s)				__asm	minps		d, s
#		define  _hoops_CRIAI(d,s)				__asm	maxps		d, s
#		define  _hoops_SRIAI(d,s)				__asm	sqrtps		d, s
#		define  _hoops_GAIAI(d,s)				__asm	rcpps		d, s
#		define  _hoops_RAIAI(d,s)			__asm	rsqrtps		d, s

#		define  _hoops_PHCPA(d,s)				__asm	andps		d, s
#		define  _hoops_IHCPA(d,s)				__asm	andnps		d, s
#		define  _hoops_CHCPA(d,s)				__asm	orps		d, s
#		define  XORPS(d,s)				__asm	xorps		d, s

#		define  UNPCKHPS(d,s)			__asm	unpckhps	d, s
#		define  UNPCKLPS(d,s)			__asm	unpcklps	d, s

#		define  _hoops_AAIAI(d,s,c)			__asm	cmpps		d, s, c
#		define  SHUFPS(d,s,c)			__asm	shufps		d, s, c

#		define  MOVHLPS(d,s)			__asm	movhlps		d, s
#		define  MOVLHPS(d,s)			__asm	movlhps		d, s
#		define  _hoops_PAIAI(d,s)				__asm	movlps		d, s
#		define  _hoops_HAIAI(d,s)				__asm	movhps		d, s
#		define  MOVAPS(d,s)				__asm	movaps		d, s
#		define  MOVUPS(d,s)				__asm	movups		d, s

#	  if 0
#		define	_hoops_IAIAI(d,s)			__asm	cvtdq2ps	d, s

#		define	_hoops_CAIAI(d,s)			__asm	cvtpi2ps	d, s
#		define	_hoops_SAIAI(d,s)			__asm	cvtps2pi	d, s

#		define  _hoops_GPIAI(d,s)				__asm	addss		d, s
#		define  _hoops_RPIAI(d,s)				__asm	subss		d, s
#		define  _hoops_APIAI(d,s)				__asm	mulss		d, s
#		define  _hoops_PPIAI(d,s)				__asm	divss		d, s
#		define  _hoops_HPIAI(d,s)				__asm	minss		d, s
#		define  _hoops_IPIAI(d,s)				__asm	maxss		d, s
#		define  _hoops_CPIAI(d,s)				__asm	sqrtss		d, s
#		define  _hoops_SPIAI(d,s)				__asm	rcpss		d, s
#		define  _hoops_GHIAI(d,s)			__asm	rsqrtss		d, s

#		define  _hoops_RHIAI(d,s,c)			__asm	cmpss		d, s, c

#		define  _hoops_AHIAI(d,s)				__asm	movss		d, s

#		define	_hoops_PHIAI(d,s)			__asm	cvtsi2ss	d, s
#		define	_hoops_HHIAI(d,s)			__asm	cvtss2si	d, s

#		define	_hoops_IAIAI(d,s)			__asm	cvtdq2ps	d, s
#		define	_hoops_IHIAI(d,s)			__asm	cvtps2dq	d, s
#		define  _hoops_CHIAI(d,s)				__asm	pand		d, s
#		define  _hoops_SHIAI(d,s)				__asm	pandn		d, s
#		define  _hoops_GIIAI(d,s)				__asm	por			d, s
#		define  _hoops_RIIAI(d,s)				__asm	pxor		d, s

#		define  _hoops_AIIAI(d,s)			__asm	movsldup	d, s
#		define  _hoops_PIIAI(d,s)			__asm	movshdup	d, s
#		define  _hoops_HIIAI(d,s)			__asm	addsubps	d, s
#		define  _hoops_IIIAI(d,s)				__asm	haddps		d, s
#		define  _hoops_CIIAI(d,s)				__asm	hsubps		d, s
#	  endif
#	else
		/* _hoops_CASH _hoops_SIIAI _hoops_GCIAI (_hoops_PPR _hoops_PISH _hoops_IH _hoops_PCHC _hoops_PGPP), _hoops_HISAR _hoops_SIIAI _hoops_RCIAI _hoops_PAR _hoops_AHGPH/_hoops_RPRAR */
#		define	EAX				0x00
#		define	EBX				0x03	/* _hoops_CHCAR, _hoops_RGR _hoops_HRGR _hoops_GGSR _hoops_IIGR _hoops_AGR... */
#		define	_hoops_IGIAI				0x01
#		define	EDX				0x02
#		define	_hoops_RCCPA				0x07
#		define	XMM0			0xF0
#		define	XMM1			0xF1
#		define	XMM2			0xF2
#		define	XMM3			0xF3
#		define	XMM4			0xF4
#		define	XMM5			0xF5
#		define	XMM6			0xF6
#		define	XMM7			0xF7

#		define  _hoops_ACIAI(x)					__asm _emit x

		/*******************************************************************************/
		/* _hoops_PRGIH _hoops_PCIAI _hoops_HSH, _hoops_HCR _hoops_HCIAI _hoops_RAIA 0F, _hoops_HHH _hoops_HS _hoops_PCCP _hoops_GSHRH _hoops_PCIAI _hoops_SRS */
#		define	_hoops_ICIAI			_hoops_ACIAI(0x0F)		/* _hoops_HCR  _hoops_HCIAI  */
#		define	_hoops_CCIAI			_hoops_ACIAI(0x66)		/* _hoops_HHH _hoops_SCIAI */
#		define	_hoops_GSIAI			_hoops_ACIAI(0xF2)		/* _hoops_HHH _hoops_PHHGI */
#		define	_hoops_RSIAI			_hoops_ACIAI(0xF3)		/* _hoops_HCR _hoops_ASIAI _hoops_IRSP _hoops_IIGR _hoops_CAGA */

		/* _hoops_SGSS _hoops_CIGR _hoops_IH _hoops_ARHRH:
			_hoops_GCIAI _hoops_HRGR 3 _hoops_IH _hoops_CGIAI <- _hoops_CGIAI, 0 _hoops_RPP _hoops_IRS _hoops_RGCPR _hoops_PPGS _hoops_CGRPR (1 & 2 _hoops_IH _hoops_PSIAI, _hoops_IPIH _hoops_PPRAR)
			_hoops_GII _hoops_PPGS _hoops_CGRPR _hoops_HRGR _hoops_SHR _hoops_GGR _hoops_AHGPH/_hoops_RPRAR
			_hoops_IAII _hoops_PASPR _hoops_IAGA _hoops_GGR _hoops_RCIAI
		 */
#		define	_hoops_HSIAI(_hoops_ISSAH,_hoops_ISIAI,_hoops_RSHPA)	_hoops_ACIAI (((_hoops_ISSAH & 3) << 6) | ((_hoops_ISIAI & 7) << 3) | (_hoops_RSHPA & 7))
#		define	_hoops_CSIAI(d,s)		(((d & s) >> 4) & 3)
#		define	_hoops_SSIAI(d,s)		((d & (d >> 4)) | (s & ~(d >> 4)))
#		define	DS_RM(d,s)		((s & (d >> 4)) | (d & ~(d >> 4)))
#		define	_hoops_GGCAI(d,s)	_hoops_HSIAI (_hoops_CSIAI(d,s), _hoops_SSIAI(d,s), DS_RM(d,s))

		/* _hoops_HHH _hoops_RGCAI _hoops_PII _hoops_AGCAI _hoops_PH _hoops_GH 1 _hoops_RPP _hoops_HCGP _hoops_HRGR _hoops_CGIAI _hoops_PPR _hoops_PASPR _hoops_HRGR _hoops_PPGS
			(_hoops_HHS _hoops_GACC _hoops_PH _hoops_RPP _hoops_PASPR _hoops_HRGR _hoops_CGIAI, _hoops_HIH _hoops_RRP _hoops_IS _hoops_PIIA _hoops_PGCAI _hoops_GGR _hoops_PIHRA)
		 */
#		define	_hoops_HGCAI(_hoops_AHSCA,_hoops_IGCAI,d,s)		(_hoops_AHSCA  |  ((s >> 4) & (~d >> 4) & _hoops_IGCAI))

#		define	_hoops_CGCAI(_hoops_AHSCA,d,s)			_hoops_ICIAI	_hoops_ACIAI (_hoops_AHSCA)		_hoops_GGCAI (d, s)
#		define	_hoops_SGCAI(_hoops_AHSCA,_hoops_IGCAI,d,s)		_hoops_CGCAI (_hoops_HGCAI (_hoops_AHSCA,_hoops_IGCAI,d,s), d, s)
#		define	_hoops_GRCAI(_hoops_AHSCA,_hoops_IGCAI,d,s)	    _hoops_RSIAI	_hoops_SGCAI (_hoops_AHSCA,_hoops_IGCAI,d,s)

		/*******************************************************************************/
		/* _hoops_HCIAI */

		/* _hoops_RGSHA */
#		define	FXSAVE(d)				_hoops_CGCAI (0xAE,d,0)				/* _hoops_RRCAI _hoops_PIAP -> [_hoops_GHGP] */
#		define	_hoops_SGIAI(d)				_hoops_CGCAI (0xAE,d,1)				/* _hoops_RRCAI _hoops_PIAP <- [_hoops_GHGP] */
#		define  LDMXCSR(d)				_hoops_CGCAI (0xAE,d,2)				/* _hoops_ARCAI <- _hoops_GHGP */
#		define  STMXCSR(d)				_hoops_CGCAI (0xAE,d,3)				/* _hoops_ARCAI -> _hoops_GHGP */

#		define  _hoops_GRIAI(d)			_hoops_CGCAI (0x18,d,0)				/* _hoops_GRAA-_hoops_PRCAI */
#		define  _hoops_RRIAI(d)			_hoops_CGCAI (0x18,d,1)				/* _hoops_HCR _hoops_IHAH _hoops_HARH */
#		define  _hoops_ARIAI(d)			_hoops_CGCAI (0x18,d,2)				/* _hoops_SRS-_hoops_PAPA _hoops_IHAH */
#		define  _hoops_PRIAI(d)			_hoops_CGCAI (0x18,d,3)				/* _hoops_GIAP-_hoops_PAPA _hoops_IHAH */

		/* _hoops_GSSR _hoops_CAGA _hoops_PSCH _hoops_IGGRA _hoops_GPP 4 _hoops_RSRA _hoops_PHRP _hoops_GGR _hoops_GGAIA */
#		define  ADDPS(d,s)				_hoops_SGCAI (0x58,0,d,s)				/* 4 _hoops_SISR  _hoops_GHGP <- _hoops_GHGP +_hoops_GRI */
#		define  _hoops_HRIAI(d,s)				_hoops_SGCAI (0x5C,0,d,s)				/* 4 _hoops_SISR  _hoops_GHGP <- _hoops_GHGP -_hoops_GRI */
#		define  MULPS(d,s)				_hoops_SGCAI (0x59,0,d,s)				/* 4 _hoops_SISR  _hoops_GHGP <- _hoops_GHGP *_hoops_GRI */
#		define  _hoops_RICPA(d,s)				_hoops_SGCAI (0x5E,0,d,s)				/* 4 _hoops_SISR  _hoops_GHGP <- _hoops_GHGP /_hoops_GRI */
#		define  _hoops_IRIAI(d,s)				_hoops_SGCAI (0x5D,0,d,s)				/* 4 _hoops_SISR  _hoops_GHGP <- _hoops_CGGPR (_hoops_GHGP,_hoops_GRI)  */
#		define  _hoops_CRIAI(d,s)				_hoops_SGCAI (0x5F,0,d,s)				/* 4 _hoops_SISR  _hoops_GHGP <- _hoops_AHPA (_hoops_GHGP,_hoops_GRI)  */
#		define  _hoops_SRIAI(d,s)				_hoops_SGCAI (0x51,0,d,s)				/* 4 _hoops_SISR  _hoops_GHGP <- _hoops_AGGIR(_hoops_GRI) */
#		define  _hoops_GAIAI(d,s)				_hoops_SGCAI (0x53,0,d,s)				/* 4 _hoops_SISR  _hoops_GHGP <~ 1/_hoops_GRI */
#		define  _hoops_RAIAI(d,s)			_hoops_SGCAI (0x52,0,d,s)				/* 4 _hoops_SISR  _hoops_GHGP <~ 1/_hoops_AGGIR(_hoops_GRI) */

#		define  _hoops_PHCPA(d,s)				_hoops_SGCAI (0x54,0,d,s)				/* 4 _hoops_SISR  _hoops_GHGP <- _hoops_GHGP & _hoops_GRI */
#		define  _hoops_IHCPA(d,s)				_hoops_SGCAI (0x55,0,d,s)				/* 4 _hoops_SISR  _hoops_GHGP <- ~_hoops_GHGP & _hoops_GRI */
#		define  _hoops_CHCPA(d,s)				_hoops_SGCAI (0x56,0,d,s)				/* 4 _hoops_SISR  _hoops_GHGP <- _hoops_GHGP | _hoops_GRI */
#		define  XORPS(d,s)				_hoops_SGCAI (0x57,0,d,s)				/* 4 _hoops_SISR  _hoops_GHGP <- _hoops_GHGP ^ _hoops_GRI */

#		define  UNPCKHPS(d,s)			_hoops_SGCAI (0x15,0,d,s)				/* _hoops_GHGP <- (_hoops_CCPIA,_hoops_HRCAI,_hoops_IRCAI,_hoops_CRCAI) */
#		define  UNPCKLPS(d,s)			_hoops_SGCAI (0x14,0,d,s)				/* _hoops_GHGP <- (_hoops_SRCAI,_hoops_PCGP,_hoops_GACAI,_hoops_PARP) */

#		define  _hoops_AAIAI(d,s,c)			_hoops_SGCAI (0xC2,0,d,s)	_hoops_ACIAI (c)	/* 4 _hoops_SISR  _hoops_GHGP <- _hoops_GHGP _hoops_GSGGR _hoops_GRI */
#		define  SHUFPS(d,s,c)			_hoops_SGCAI (0xC6,0,d,s)	_hoops_ACIAI (c)	/* _hoops_GHGP <- (_hoops_GHGP[_hoops_RACAI], _hoops_GHGP[_hoops_AACAI], _hoops_GRI[_hoops_PACAI], _hoops_GRI[_hoops_HACAI]) */

#		define  MOVHLPS(d,s)			_hoops_SGCAI (0x12,0,d,s)				/* _hoops_IACAI <- _hoops_CACAI */
#		define  MOVLHPS(d,s)			_hoops_SGCAI (0x16,0,d,s)				/* _hoops_SACAI <- _hoops_GPCAI */
#		define  _hoops_PAIAI(d,s)				_hoops_SGCAI (0x12,1,d,s)				/* _hoops_IACAI <- _hoops_RPCAI _hoops_HAPCA _hoops_APCAI <- _hoops_GPCAI */
#		define  _hoops_HAIAI(d,s)				_hoops_SGCAI (0x16,1,d,s)				/* _hoops_SACAI <- _hoops_RPCAI _hoops_HAPCA _hoops_APCAI <- _hoops_CACAI */
#		define  MOVAPS(d,s)				_hoops_SGCAI (0x28,1,d,s)				/* 4 _hoops_SISR  _hoops_GHGP <- _hoops_GRI  (_hoops_RGCGA) */
#		define  MOVUPS(d,s)				_hoops_SGCAI (0x10,1,d,s)				/* 4 _hoops_SISR  _hoops_GHGP <- _hoops_GRI */

#	  if 0	/* _hoops_IPIH _hoops_RGAR _hoops_GRP _hoops_HCIAI 4-_hoops_AIIC _hoops_CAGA _hoops_PGPP */
#		define	_hoops_IAIAI(d,s)			_hoops_SGCAI (0x5B,0,d,s)				/* 4 _hoops_SISR  _hoops_RRCAI <- _hoops_PPCAI */

		/* _hoops_PPAC _hoops_CAGA _hoops_PSCH _hoops_HPCAI _hoops_GPP 2 _hoops_RSRA _hoops_PHRP */
#		define	_hoops_CAIAI(d,s)			_hoops_SGCAI (0x2A,0,d,s)				/* 2 _hoops_SISR  _hoops_RRCAI <- _hoops_PPCAI */
#		define	_hoops_SAIAI(d,s)			_hoops_SGCAI (0x2D,0,d,s)				/* 2 _hoops_SISR  _hoops_PPCAI <- _hoops_RRCAI */

		/* _hoops_GSSR _hoops_ASIAI _hoops_PSCH _hoops_IGGRA _hoops_GPP 1 _hoops_RSRA _hoops_AIIC */
#		define  _hoops_GPIAI(d,s)				_hoops_GRCAI (0x58,0,d,s)				/* 1 _hoops_SISR  _hoops_GHGP <- _hoops_GHGP +_hoops_GRI */
#		define  _hoops_RPIAI(d,s)				_hoops_GRCAI (0x5C,0,d,s)				/* 1 _hoops_SISR  _hoops_GHGP <- _hoops_GHGP -_hoops_GRI */
#		define  _hoops_APIAI(d,s)				_hoops_GRCAI (0x59,0,d,s)				/* 1 _hoops_SISR  _hoops_GHGP <- _hoops_GHGP *_hoops_GRI */
#		define  _hoops_PPIAI(d,s)				_hoops_GRCAI (0x5E,0,d,s)				/* 1 _hoops_SISR  _hoops_GHGP <- _hoops_GHGP /_hoops_GRI */
#		define  _hoops_HPIAI(d,s)				_hoops_GRCAI (0x5D,0,d,s)				/* 1 _hoops_SISR  _hoops_GHGP <- _hoops_CGGPR (_hoops_GHGP,_hoops_GRI)  */
#		define  _hoops_IPIAI(d,s)				_hoops_GRCAI (0x5F,0,d,s)				/* 1 _hoops_SISR  _hoops_GHGP <- _hoops_AHPA (_hoops_GHGP,_hoops_GRI)  */
#		define  _hoops_CPIAI(d,s)				_hoops_GRCAI (0x51,0,d,s)				/* 1 _hoops_SISR  _hoops_GHGP <- _hoops_AGGIR(_hoops_GRI) */
#		define  _hoops_SPIAI(d,s)				_hoops_GRCAI (0x53,0,d,s)				/* 1 _hoops_SISR  _hoops_GHGP <~ 1/_hoops_GRI */
#		define  _hoops_GHIAI(d,s)			_hoops_GRCAI (0x52,0,d,s)				/* 1 _hoops_SISR  _hoops_GHGP <~ 1/_hoops_AGGIR(_hoops_GRI) */

#		define  _hoops_RHIAI(d,s,c)			_hoops_GRCAI (0xC2,0,d,s)	_hoops_ACIAI (c)	/* 1 _hoops_SISR  _hoops_GHGP <- _hoops_GHGP _hoops_GSGGR _hoops_GRI */

#		define  _hoops_AHIAI(d,s)				_hoops_GRCAI (0x10,1,d,s)				/* _hoops_SRCAI <- _hoops_PCGP _hoops_HAPCA _hoops_GHGP <- (_hoops_IPCAI,0,0,0) */

#		define	_hoops_PHIAI(d,s)			_hoops_GRCAI (0x5B,0,d,s)				/* 1 _hoops_SISR  _hoops_RRCAI <- _hoops_PPCAI */
#		define	_hoops_HHIAI(d,s)			_hoops_GRCAI (0x2D,0,d,s)				/* 1 _hoops_SISR  _hoops_PPCAI <- _hoops_RRCAI */

		/* _hoops_SCIAI */
#		define	_hoops_IAIAI(d,s)			_hoops_SGCAI (0x5B,0,d,s)				/* 4 _hoops_SISR  _hoops_RRCAI <- _hoops_PPCAI */
#		define	_hoops_IHIAI(d,s)	_hoops_CCIAI	_hoops_SGCAI (0x5B,0,d,s)				/* 4 _hoops_SISR  _hoops_PPCAI <- _hoops_RRCAI */
#		define  _hoops_CHIAI(d,s)		_hoops_CCIAI	_hoops_SGCAI (0xDB,0,d,s)				/* 4 _hoops_SISR  _hoops_GHGP <- _hoops_GHGP & _hoops_GRI */
#		define  _hoops_SHIAI(d,s)		_hoops_CCIAI	_hoops_SGCAI (0xDF,0,d,s)				/* 4 _hoops_SISR  _hoops_GHGP <- ~_hoops_GHGP & _hoops_GRI */
#		define  _hoops_GIIAI(d,s)		_hoops_CCIAI	_hoops_SGCAI (0xEB,0,d,s)				/* 4 _hoops_SISR  _hoops_GHGP <-  _hoops_GHGP |_hoops_GRI */
#		define  _hoops_RIIAI(d,s)		_hoops_CCIAI	_hoops_SGCAI (0xEF,0,d,s)				/* 4 _hoops_SISR  _hoops_GHGP <-  _hoops_GHGP ^_hoops_GRI */
#		define	_hoops_CPCAI(d,s,c)	_hoops_CCIAI	_hoops_SGCAI (0x70,0,d,s,c) _hoops_ACIAI (c)	/* _hoops_GHGP <- (_hoops_GRI[_hoops_RACAI], _hoops_GRI[_hoops_AACAI], _hoops_GRI[_hoops_PACAI], _hoops_GRI[_hoops_HACAI]) */

		/* _hoops_PHHGI */
#		define  _hoops_AIIAI(d,s)			_hoops_GRCAI (0x12,0,d,s)				/* _hoops_GHGP <- (_hoops_PCGP,_hoops_PCGP,_hoops_HRCAI,_hoops_HRCAI) */
#		define  _hoops_PIIAI(d,s)			_hoops_GRCAI (0x16,0,d,s)				/* _hoops_GHGP <- (_hoops_PARP,_hoops_PARP,_hoops_CRCAI,_hoops_CRCAI) */
#		define  _hoops_HIIAI(d,s)	_hoops_GSIAI	_hoops_SGCAI (0x58,0,d,s)				/* _hoops_GHGP <- (_hoops_SRCAI-_hoops_PCGP, _hoops_GACAI+_hoops_PARP, _hoops_CCPIA-_hoops_HRCAI, _hoops_IRCAI+_hoops_CRCAI) */
#		define  _hoops_IIIAI(d,s)		_hoops_GSIAI	_hoops_SGCAI (0x7C,0,d,s)				/* _hoops_GHGP <- (_hoops_SRCAI+_hoops_GACAI, _hoops_CCPIA+_hoops_IRCAI, _hoops_PCGP+_hoops_PARP, _hoops_HRCAI+_hoops_CRCAI) */
#		define  _hoops_CIIAI(d,s)		_hoops_GSIAI	_hoops_SGCAI (0x7D,0,d,s)				/* _hoops_GHGP <- (_hoops_SRCAI-_hoops_GACAI, _hoops_CCPIA-_hoops_IRCAI, _hoops_PCGP-_hoops_PARP, _hoops_HRCAI-_hoops_CRCAI) */
#	  endif
#	endif

	/* _hoops_SPCAI-_hoops_GHCAI _hoops_IRSP _hoops_IIGR _hoops_RHCAI */
#	define	_hoops_AHCAI(d,s)	_hoops_AAIAI (d, s, 0)	/* _hoops_GHGP == _hoops_GRI */
#	define	CMPLTPS(d,s)	_hoops_AAIAI (d, s, 1)	/* _hoops_GHGP < _hoops_GRI */
#	define	_hoops_RHCPA(d,s)	_hoops_AAIAI (d, s, 2)	/* _hoops_GHGP <= _hoops_GRI */
#	define	_hoops_PHCAI(d,s)	_hoops_AAIAI (d, s, 3)	/* _hoops_PGI _hoops_GHGP _hoops_PAR _hoops_GRI _hoops_HRGR _hoops_HHCAI */
#	define	_hoops_IHCAI(d,s)	_hoops_AAIAI (d, s, 4)	/* _hoops_GHGP != _hoops_GRI */
#	define	_hoops_CHCAI(d,s)	_hoops_AAIAI (d, s, 5)	/* _hoops_GHGP >= _hoops_GRI */
#	define	_hoops_SHCAI(d,s)	_hoops_AAIAI (d, s, 6)	/* _hoops_GHGP > _hoops_GRI */
#	define	_hoops_GICAI(d,s)	_hoops_AAIAI (d, s, 7)	/* _hoops_RSIPR _hoops_GHGP _hoops_GHCRH _hoops_GRI _hoops_HRGR _hoops_HHCAI */

#	define	_hoops_RICAI(d,s)	_hoops_RHIAI (d, s, 0)	/* _hoops_GHGP == _hoops_GRI */
#	define	_hoops_AICAI(d,s)	_hoops_RHIAI (d, s, 1)	/* _hoops_GHGP < _hoops_GRI */
#	define	_hoops_PICAI(d,s)	_hoops_RHIAI (d, s, 2)	/* _hoops_GHGP <= _hoops_GRI */
#	define	_hoops_HICAI(d,s)	_hoops_RHIAI (d, s, 3)	/* _hoops_PGI _hoops_GHGP _hoops_PAR _hoops_GRI _hoops_HRGR _hoops_HHCAI */
#	define	_hoops_IICAI(d,s)	_hoops_RHIAI (d, s, 4)	/* _hoops_GHGP != _hoops_GRI */
#	define	_hoops_CICAI(d,s)	_hoops_RHIAI (d, s, 5)	/* _hoops_GHGP >= _hoops_GRI */
#	define	_hoops_SICAI(d,s)	_hoops_RHIAI (d, s, 6)	/* _hoops_GHGP > _hoops_GRI */
#	define	_hoops_GCCAI(d,s)	_hoops_RHIAI (d, s, 7)	/* _hoops_RSIPR _hoops_GHGP _hoops_GHCRH _hoops_GRI _hoops_HRGR _hoops_HHCAI */

	/* _hoops_CPPC _hoops_RH _hoops_IGCHH _hoops_RAPSR '_hoops_GSGGR' _hoops_IH _hoops_RCCAI(_hoops_GHGP,_hoops_GRI,_hoops_GSGGR) _hoops_RPP _hoops_RHAC _hoops_GA'_hoops_RA _hoops_HHGC _hoops_IS _hoops_SAHR _hoops_AAIR _hoops_IRS _hoops_ACCAI _hoops_PIRA */
	/* _hoops_SRCAI _hoops_IAGA _hoops_GGR _hoops_HISAR _hoops_ARIP _hoops_IIGR _hoops_PASPR, _hoops_PARP _hoops_GGR _hoops_CASH _hoops_ARIP */
#	define	SHUFSEL(_hoops_HHAIH,_hoops_GIGCR,s0,s1)		((s1<<6) | (s0<<4) | (_hoops_GIGCR<<2) | _hoops_HHAIH)

#endif



#if 0
/* _hoops_RGR _hoops_CSAP _hoops_HAR _hoops_RICPR _hoops_CIAH
#_hoops_IHS _hoops_PICPH
*/
	local INLINE vector float _hoops_RGSPH(vector float a, vector float b, vector float c, vector float d) {
		vector float _hoops_PCCAI, _hoops_HCCAI, _hoops_ICCAI, _hoops_CCCAI;
		
		/* _hoops_PHAA _hoops_HHAA _hoops_IIGR 4x4 _hoops_IRS _hoops_RSGA _hoops_HGICR */
		_hoops_PCCAI = _hoops_SCCAI( a, c );		/* 1 {_hoops_GSCAI, _hoops_RSCAI, _hoops_GRRRH, _hoops_HRRRH} */
		_hoops_ICCAI = _hoops_ASCAI( a, c );		/* 2 {_hoops_RRRRH, _hoops_RRCCP, _hoops_PSCAI, _hoops_HSCAI} */
		_hoops_HCCAI = _hoops_SCCAI( b, d );		/* 3 {_hoops_ISCAI, _hoops_SRCAI, _hoops_ARRRH, _hoops_GACAI} */
		_hoops_CCCAI = _hoops_ASCAI( b, d );		/* 4 {_hoops_PRRRH, _hoops_CCPIA, _hoops_CSCAI, _hoops_IRCAI} */
		
		/* _hoops_RGPA _hoops_GIRPA _hoops_HSH */
		b = _hoops_SSCAI( _hoops_PCCAI, _hoops_ICCAI );	/* 4 {_hoops_GSCAI + _hoops_RRRRH, _hoops_RSCAI + _hoops_RRCCP, _hoops_GRRRH + _hoops_PSCAI, _hoops_HRRRH + _hoops_HSCAI} */
		d = _hoops_SSCAI( _hoops_HCCAI, _hoops_CCCAI );	/* 6 {_hoops_ISCAI + _hoops_PRRRH, _hoops_SRCAI + _hoops_CCPIA, _hoops_ARRRH + _hoops_CSCAI, _hoops_GACAI + _hoops_IRCAI} */

		/* _hoops_RAH _hoops_HHAA _hoops_IIGR _hoops_RH _hoops_GIAP _hoops_HHAA _hoops_IIGR _hoops_RH _hoops_HGICR */
		a = _hoops_SCCAI( b, d );			/* 7 { _hoops_GSCAI + _hoops_RRRRH, _hoops_ISCAI + _hoops_PRRRH, _hoops_RSCAI + _hoops_RRCCP, _hoops_SRCAI + _hoops_CCPIA } */
		c = _hoops_ASCAI( b, d );			/* 8 { _hoops_GRRRH + _hoops_PSCAI, _hoops_ARRRH + _hoops_CSCAI, _hoops_HRRRH + _hoops_HSCAI, _hoops_GACAI + _hoops_IRCAI } */

		/* _hoops_ACGR _hoops_RH _hoops_GHPP */
		return _hoops_SSCAI( a, c );			/* 10 */
	}

	local INLINE vector unsigned char _hoops_IICPH(int index, unsigned char *target) {
		vector unsigned char _hoops_GGSAI, _hoops_RGSAI;
		vector unsigned char mask;

		/* _hoops_ICRP _hoops_ACAAA _hoops_AGSAI */
		_hoops_GGSAI = _hoops_CCCPH(index, target);

		/* _hoops_CHGC _hoops_ACAAA _hoops_AGSAI */
		_hoops_RGSAI = _hoops_CCCPH(index + 16, target);

		/* _hoops_ARPR _hoops_RH _hoops_SCCPH _hoops_PISH */
		mask = _hoops_GSCPH(0, target + index);

		/* _hoops_ASRC _hoops_RH _hoops_RSCPH _hoops_PIH */
		return _hoops_PSCPH(_hoops_GGSAI, _hoops_RGSAI, mask);
	}

	local INLINE void _hoops_HGSPH(vector unsigned char src, int index, unsigned char *target) {
		vector unsigned char _hoops_GGSAI, _hoops_RGSAI;
		vector unsigned char mask, _hoops_PGSAI, _hoops_HGSAI, _hoops_IGSAI;

		_hoops_GGSAI = _hoops_CCCPH(index, target);			/* _hoops_ICRP _hoops_ACAAA _hoops_AGSAI */
		_hoops_RGSAI = _hoops_CCCPH(index + 16, target);		/* _hoops_CHGC _hoops_ACAAA _hoops_AGSAI */

		_hoops_PGSAI = _hoops_CGSAI(0, target + index);	/* _hoops_ARPR _hoops_AHSGP _hoops_AAGA */
		_hoops_HGSAI = _hoops_SGSAI( 0 );				/* _hoops_GISA _hoops_AAGA _hoops_IHIR _hoops_IIGR _hoops_HPAGI */
		_hoops_IGSAI = _hoops_SGSAI( -1 );				/* _hoops_GISA _hoops_AAGA _hoops_IHIR _hoops_IIGR -1 */

		mask = _hoops_PSCPH(_hoops_HGSAI, _hoops_IGSAI, _hoops_PGSAI);		/* _hoops_GISA _hoops_HAIHR _hoops_PISH */

		src = _hoops_PSCPH(src, src, _hoops_PGSAI);		/* _hoops_RCIAH _hoops_IRSHR _hoops_GCSS _hoops_PIH */

		_hoops_GGSAI = _hoops_GRSAI(_hoops_GGSAI, src, mask);			/* _hoops_CARR _hoops_PIH _hoops_CRGR _hoops_RRSAI _hoops_ARIP */
		_hoops_RGSAI = _hoops_GRSAI(src, _hoops_RGSAI, mask);			/* _hoops_CARR _hoops_PIH _hoops_CRGR _hoops_ARSAI _hoops_ARIP */

		_hoops_PRSAI(_hoops_GGSAI, index, target);				/* _hoops_SAH _hoops_RH _hoops_RRSAI _hoops_ARIP */
		_hoops_PRSAI(_hoops_RGSAI, index + 16, target);		/* _hoops_SAH _hoops_RH _hoops_ARSAI _hoops_ARIP */
	}
#endif


#define HOOPS_PROCESSOR_SPECIFIC_FUNCTIONALITY_DEFINED
#endif

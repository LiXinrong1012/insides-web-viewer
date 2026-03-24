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
 * $Id: obf_tmp.txt 1.14 2010-05-07 21:51:41 reuben Exp $
 */

#include "hoops.h"
#include "hpspsf.h"
#include "hi_proto.h"


struct _hoops_GHPHS {
	char* array;
	float* priorities;
	int _hoops_RPSIH;
	void* _hoops_RHPHS;
};

#define _hoops_AHPHS(thing,a,b) { \
	Swap(QS_VAL(thing,a), QS_VAL(thing,b)); \
	switch (thing->_hoops_RPSIH) { \
		case 1: {	\
			if (thing->array != null) \
				Swap(*(thing->array + a), *(thing->array+b)); \
			} break; \
		case 2: { \
			if (thing->array != null) \
				Swap(*((short*)(thing->array+2*a)), *((short*)(thing->array+2*b))); \
			} break;	\
		case 4:	{ \
			if (thing->array != null) \
				Swap(*((Integer32*)(thing->array+4*a)), *((Integer32*)(thing->array+4*b))); \
			} break; \
		default: \
			memcpy((thing->_hoops_RHPHS), (thing->array + (thing->_hoops_RPSIH)*a), thing->_hoops_RPSIH); \
			memcpy((thing->array + (thing->_hoops_RPSIH)*a), (thing->array + (thing->_hoops_RPSIH)*b), thing->_hoops_RPSIH); \
			memcpy((thing->array + (thing->_hoops_RPSIH)*b), (thing->_hoops_RHPHS), thing->_hoops_RPSIH); \
			break; \
	} \
}	
#define QS_RESET
#include "utility/hqsort.h"
#define QS_BUBBLE_SORT				_hoops_PHPHS 
#define QS_QUICK_SORT_RECURSIVE		_hoops_HHPHS
#define QS_ISSORTED					_hoops_IHPHS
#define QS_TYPE				struct _hoops_GHPHS	*		/* _hoops_RH _hoops_GPRR _hoops_IIGR _hoops_CARA _hoops_PAR _hoops_CRPR _hoops_SGS _hoops_ICGI _hoops_HCR _hoops_HSH */
#define QS_VAL(thing,a)		(thing->priorities[a])			/* _hoops_HRS _hoops_RH _hoops_PIRA _hoops_IIGR _hoops_PCCP _hoops_IGCI _hoops_CCA _hoops_CIHA _hoops_IRS */
#define QS_COMPARE(f1,f2)	(f1>f2)							/* _hoops_SGH ">" _hoops_IS _hoops_GHIS _hoops_GACPR, "<" _hoops_IS _hoops_GHIS _hoops_CPIHR */
#define QS_SWAP(thing,a,b) _hoops_AHPHS(thing,a,b)

#include "utility/hqsort.h"

#define QS_RESET
#include "utility/hqsort.h"
#define QS_BUBBLE_SORT				_hoops_CHPHS 
#define QS_QUICK_SORT_RECURSIVE		_hoops_SHPHS
#define QS_ISSORTED					_hoops_GIPHS
#define QS_TYPE				struct _hoops_GHPHS	*		/* _hoops_RH _hoops_GPRR _hoops_IIGR _hoops_CARA _hoops_PAR _hoops_CRPR _hoops_SGS _hoops_ICGI _hoops_HCR _hoops_HSH */
#define QS_VAL(thing,a)		(thing->priorities[a])			/* _hoops_HRS _hoops_RH _hoops_PIRA _hoops_IIGR _hoops_PCCP _hoops_IGCI _hoops_CCA _hoops_CIHA _hoops_IRS */
#define QS_COMPARE(f1,f2)	(f1<f2)			/* _hoops_SGH ">" _hoops_IS _hoops_GHIS _hoops_GACPR, "<" _hoops_IS _hoops_GHIS _hoops_CPIHR */
#define QS_SWAP(thing,a,b) _hoops_AHPHS(thing,a,b)
#include "utility/hqsort.h"




#ifdef _hoops_IIIPA
#define _hoops_RIPHS 1
#else
#define _hoops_RIPHS 0
#endif


#if _hoops_RIPHS
#define _hoops_AIPHS	64
#define _hoops_PIPHS	128

#define _hoops_APRRC(x)	{const char * t = (((const char *)(x)) +  _hoops_AIPHS);  __asm   mov  eax, t _hoops_RRIAI(0x00)}
#define _hoops_HIPHS(x)	{const char * t = (((const char *)(x)) +  _hoops_PIPHS); __asm   mov  eax, t _hoops_RRIAI(0x00)}
#else
#define _hoops_APRRC(x)
#define _hoops_HIPHS(x)
#endif


/*
// ================================================================================================
// _hoops_IHAA _hoops_IRS _hoops_AIIC _hoops_IH _hoops_SHCAH
//  _hoops_GPHR _hoops_IIPHS _hoops_IIGR _hoops_CPGII _hoops_PHI.
//  _hoops_RPP _hoops_SCH'_hoops_GRI 1 (_hoops_HHHR _hoops_AIIC), _hoops_SCH _hoops_RRSRH _hoops_HCR _hoops_SIH
//  _hoops_RPP _hoops_SCH'_hoops_GRI 0 (_hoops_RPRHR _hoops_AIIC), _hoops_SCH _hoops_RRSRH _hoops_RH _hoops_HRASR _hoops_RGAR
// ================================================================================================
*/

static unsigned Integer32 _hoops_CIPHS(unsigned Integer32 f)
{
	Integer32 t = f>>31;
	unsigned Integer32 mask = -t | 0x80000000;
	return f ^ mask;
}

static void _hoops_SIPHS(unsigned Integer32* f)
{
	Integer32 t = *f >> 31;
	unsigned Integer32 mask = -t | 0x80000000;
	*f ^= mask;
}

/*
// ================================================================================================
// _hoops_IHAA _hoops_IRS _hoops_AIIC _hoops_ISSC (_hoops_ISSP _hoops_GCPHS)
//  _hoops_CPCSH _hoops_CSAP _hoops_AHAPI _hoops_HII _hoops_ARRS, _hoops_HIS:
//  _hoops_RPP _hoops_HRASR _hoops_HRGR 1 (_hoops_HHHR), _hoops_SCH _hoops_RRSRH _hoops_RH _hoops_HRASR _hoops_IGRH _hoops_ISSC
//  _hoops_RPP _hoops_HRASR _hoops_HRGR 0 (_hoops_RPRHR), _hoops_SCH _hoops_RRSRH _hoops_HCR _hoops_SIH _hoops_ISSC
// ================================================================================================
*/
static unsigned Integer32 _hoops_RCPHS(unsigned Integer32 f)
{
	unsigned Integer32 mask = ((f >> 31) - 1) | 0x80000000;
	return f ^ mask;
}

/* ---- _hoops_ACPHS _hoops_IH _hoops_PCPHS 11-_hoops_IGRH _hoops_HCPHS */
#define _0(x)	(x & 0x7FF)
#define _1(x)	(x >> 11 & 0x7FF)
#define _2(x)	(x >> 22)


/* ---- _hoops_ACPHS _hoops_IH _hoops_PCPHS 8-_hoops_IGRH _hoops_HCPHS */
#define _80(x)	(x & 0xFF)
#define _81(x)	(x >> 8 & 0xFF)
#define _82(x)	(x >> 16 & 0xFF)
#define _83(x)	(x >> 24)

#define _hoops_ICPHS() do{\
}while(0)

#if defined(__sun) && defined(__amd64)
#undef _hoops_ICPHS
#define _hoops_ICPHS() do{\
	asm volatile ("" ::: "memory");\
}while(0)
#endif

void HI_Radix_Sort_8(float* _hoops_IASIH, float *_hoops_CASIH, void** _hoops_SASIH, void** _hoops_GPSIH, Integer32 _hoops_RPSIH, unsigned long elements, bool _hoops_APSIH)
{
	unsigned Integer32 i;
	unsigned Integer32 *_hoops_CCPHS = (unsigned Integer32*)_hoops_CASIH;
	unsigned Integer32 *array = (unsigned Integer32*)_hoops_IASIH;

	/* 4 _hoops_SCPHS _hoops_GPP _hoops_RH _hoops_RRGC: */
	const unsigned Integer32 _hoops_GSPHS = 256;
	unsigned Integer32 _hoops_SACIC[1024]; /* _hoops_RSPHS * 4 */

	unsigned Integer32 *_hoops_IHHI = _hoops_SACIC + _hoops_GSPHS;
	unsigned Integer32 *_hoops_CHHI = _hoops_IHHI + _hoops_GSPHS;
	unsigned Integer32 *_hoops_GPCIC = _hoops_CHHI + _hoops_GSPHS;

	for (i = 0; i < _hoops_GSPHS * 4; i++) {
		_hoops_SACIC[i] = 0;
	}

	/* 1.  _hoops_GGAIA _hoops_ASPHS _hoops_RIH */
	for (i = 0; i < elements; i++) {
		unsigned Integer32 fi = 0;
		_hoops_APRRC(&array[i]);

		fi = _hoops_CIPHS((unsigned Integer32)array[i]);

		_hoops_SACIC[_80(fi)] ++;
		_hoops_IHHI[_81(fi)] ++;
		_hoops_CHHI[_82(fi)] ++;
		_hoops_GPCIC[_83(fi)] ++;
	}
	
	/* 2.  _hoops_PSPHS _hoops_RH _hoops_SCPHS -- _hoops_GRR _hoops_HSPHS _hoops_RARP _hoops_ISPHS _hoops_RH _hoops_PHI _hoops_IIGR _hoops_HSH _hoops_HPSIR _hoops_ACAS. */
	{
		unsigned Integer32 _hoops_CSPHS = 0, _hoops_SSPHS = 0, _hoops_GGHHS = 0, _hoops_RGHHS = 0;
		unsigned Integer32 _hoops_AGHHS;
		for (i = 0; i < _hoops_GSPHS; i++) {

			_hoops_AGHHS = _hoops_SACIC[i] + _hoops_CSPHS;
			_hoops_SACIC[i] = _hoops_CSPHS - 1;
			_hoops_CSPHS = _hoops_AGHHS;

			_hoops_AGHHS = _hoops_IHHI[i] + _hoops_SSPHS;
			_hoops_IHHI[i] = _hoops_SSPHS - 1;
			_hoops_SSPHS = _hoops_AGHHS;

			_hoops_AGHHS = _hoops_CHHI[i] + _hoops_GGHHS;
			_hoops_CHHI[i] = _hoops_GGHHS - 1;
			_hoops_GGHHS = _hoops_AGHHS;

			_hoops_AGHHS = _hoops_GPCIC[i] + _hoops_RGHHS;
			_hoops_GPCIC[i] = _hoops_RGHHS - 1;
			_hoops_RGHHS = _hoops_AGHHS;
		}
	}

	/* _hoops_RAPSR 0: _hoops_PGHHS _hoops_RSIR _hoops_PIRA, _hoops_IRIGR/_hoops_GGI _hoops_HSPHS, _hoops_GGI _hoops_GGSR _hoops_AHAPI */
	for (i = 0; i < elements; i++) {
		unsigned Integer32 _hoops_SHHCR = 0;
		unsigned Integer32 fi = array[i];
		unsigned Integer32 offset = 0;
		_hoops_SIPHS(&fi);
		_hoops_SHHCR = _80(fi);
		
		_hoops_HIPHS(&array[i]);
		offset = ++_hoops_SACIC[_hoops_SHHCR];
		_hoops_CCPHS[offset] = fi;
		/* _hoops_RPP (_hoops_HGHHS) _hoops_IGHHS[_hoops_SHI] = _hoops_HGHHS[_hoops_HAS]; */
		if (_hoops_SASIH) {
			void *_hoops_HHRAR = _hoops_SASIH;
			void *_hoops_ACCHH = _hoops_GPSIH; 
			switch (_hoops_RPSIH) { 
			case 1: {	
				char *_hoops_CGHHS = ((char*)_hoops_HHRAR)+i*_hoops_RPSIH;
				char *_hoops_PCAP = ((char*)_hoops_ACCHH)+offset*_hoops_RPSIH; 
				*_hoops_PCAP = *_hoops_CGHHS;
				} break; 
			case 2: { 
				short *_hoops_CGHHS = (short*)(((char*)_hoops_HHRAR)+i*_hoops_RPSIH);
				short *_hoops_PCAP = (short*)(((char*)_hoops_ACCHH)+offset*_hoops_RPSIH); 
				*_hoops_PCAP = *_hoops_CGHHS;
				} break;	
			case 4:	{ 
				Integer32 *_hoops_CGHHS = (Integer32*)(((char*)_hoops_HHRAR)+i*_hoops_RPSIH);
				Integer32 *_hoops_PCAP = (Integer32*)(((char*)_hoops_ACCHH)+offset*_hoops_RPSIH); 
				*_hoops_PCAP = *_hoops_CGHHS;
				} break; 
			default: {
				char *_hoops_CGHHS = ((char*)_hoops_HHRAR)+i*_hoops_RPSIH;
				char *_hoops_PCAP = ((char*)_hoops_ACCHH)+offset*_hoops_RPSIH; 
				memcpy(_hoops_PCAP, _hoops_CGHHS, _hoops_RPSIH);
				} break; 
			} 
		}
	}

	/*	_hoops_RAPSR 1: _hoops_IRIGR/_hoops_GGI _hoops_HSPHS, _hoops_IPS
		_hoops_GSHHR -> _hoops_CRPR */
	for (i = 0; i < elements; i++) {
		unsigned Integer32 si = _hoops_CCPHS[i];
		unsigned Integer32 _hoops_SHHCR = _81(si);
		unsigned Integer32 offset = 0;
		
		_hoops_HIPHS(&_hoops_CCPHS[i]);
		offset = ++_hoops_IHHI[_hoops_SHHCR];
		array[offset] = si;
		if (_hoops_SASIH) {
			void *_hoops_HHRAR = _hoops_GPSIH;
			void *_hoops_ACCHH = _hoops_SASIH; 
			switch (_hoops_RPSIH) { 
			case 1: {	
				char *_hoops_CGHHS = ((char*)_hoops_HHRAR)+i*_hoops_RPSIH;
				char *_hoops_PCAP = ((char*)_hoops_ACCHH)+offset*_hoops_RPSIH; 
				*_hoops_PCAP = *_hoops_CGHHS;
				} break; 
			case 2: { 
				short *_hoops_CGHHS = (short*)(((char*)_hoops_HHRAR)+i*_hoops_RPSIH);
				short *_hoops_PCAP = (short*)(((char*)_hoops_ACCHH)+offset*_hoops_RPSIH); 
				*_hoops_PCAP = *_hoops_CGHHS;
				} break;	
			case 4:	{ 
				Integer32 *_hoops_CGHHS = (Integer32*)(((char*)_hoops_HHRAR)+i*_hoops_RPSIH);
				Integer32 *_hoops_PCAP = (Integer32*)(((char*)_hoops_ACCHH)+offset*_hoops_RPSIH); 
				*_hoops_PCAP = *_hoops_CGHHS;
				} break; 
			default: {
				char *_hoops_CGHHS = ((char*)_hoops_HHRAR)+i*_hoops_RPSIH;
				char *_hoops_PCAP = ((char*)_hoops_ACCHH)+offset*_hoops_RPSIH; 
				memcpy(_hoops_PCAP, _hoops_CGHHS, _hoops_RPSIH);
				} break; 
			} 
		}
	}

	for (i = 0; i < elements; i++) {
		unsigned Integer32 _hoops_CGGRC = array[i];
		unsigned Integer32 _hoops_SHHCR = _82(_hoops_CGGRC);
		unsigned Integer32 offset = 0;
		
		_hoops_HIPHS(&array[i]);
		offset = ++_hoops_CHHI[_hoops_SHHCR];
		_hoops_CCPHS[offset] = _hoops_CGGRC;
		if (_hoops_SASIH) {
			void *_hoops_HHRAR = _hoops_SASIH;
			void *_hoops_ACCHH = _hoops_GPSIH; 
			switch (_hoops_RPSIH) { 
			case 1: {	
				char *_hoops_CGHHS = ((char*)_hoops_HHRAR)+i*_hoops_RPSIH;
				char *_hoops_PCAP = ((char*)_hoops_ACCHH)+offset*_hoops_RPSIH; 
				*_hoops_PCAP = *_hoops_CGHHS;
				} break; 
			case 2: { 
				short *_hoops_CGHHS = (short*)(((char*)_hoops_HHRAR)+i*_hoops_RPSIH);
				short *_hoops_PCAP = (short*)(((char*)_hoops_ACCHH)+offset*_hoops_RPSIH); 
				*_hoops_PCAP = *_hoops_CGHHS;
				} break;	
			case 4:	{ 
				Integer32 *_hoops_CGHHS = (Integer32*)(((char*)_hoops_HHRAR)+i*_hoops_RPSIH);
				Integer32 *_hoops_PCAP = (Integer32*)(((char*)_hoops_ACCHH)+offset*_hoops_RPSIH); 
				*_hoops_PCAP = *_hoops_CGHHS;
				} break; 
			default: {
				char *_hoops_CGHHS = ((char*)_hoops_HHRAR)+i*_hoops_RPSIH;
				char *_hoops_PCAP = ((char*)_hoops_ACCHH)+offset*_hoops_RPSIH; 
				memcpy(_hoops_PCAP, _hoops_CGHHS, _hoops_RPSIH);
				} break; 
			} 
		}
	}

	/*	 _hoops_RAPSR 2: _hoops_IRIGR/_hoops_GGI _hoops_HSPHS, _hoops_IPS & _hoops_IHAA _hoops_GGSR
		 _hoops_CRPR -> _hoops_GSHHR */
	for (i = 0; i < elements; i++) {
		unsigned Integer32 _hoops_CGGRC = _hoops_CCPHS[i];
		unsigned Integer32 _hoops_SHHCR = _83(_hoops_CGGRC);
		unsigned Integer32 offset = 0;

		_hoops_HIPHS(&_hoops_CCPHS[i]);
	
		

		if (_hoops_APSIH) {
			offset = ++_hoops_GPCIC[_hoops_SHHCR];
			array[offset] = _hoops_RCPHS(_hoops_CGGRC);
			if (_hoops_SASIH) {
				void *_hoops_HHRAR = _hoops_GPSIH;
				void *_hoops_ACCHH = _hoops_SASIH; 
				switch (_hoops_RPSIH) { 
				case 1: {	
					char *_hoops_CGHHS = ((char*)_hoops_HHRAR)+i*_hoops_RPSIH;
					char *_hoops_PCAP = ((char*)_hoops_ACCHH)+offset*_hoops_RPSIH; 
					*_hoops_PCAP = *_hoops_CGHHS;
					} break; 
				case 2: { 
					short *_hoops_CGHHS = (short*)(((char*)_hoops_HHRAR)+i*_hoops_RPSIH);
					short *_hoops_PCAP = (short*)(((char*)_hoops_ACCHH)+offset*_hoops_RPSIH); 
					*_hoops_PCAP = *_hoops_CGHHS;
					} break;	
				case 4:	{ 
					Integer32 *_hoops_CGHHS = (Integer32*)(((char*)_hoops_HHRAR)+i*_hoops_RPSIH);
					Integer32 *_hoops_PCAP = (Integer32*)(((char*)_hoops_ACCHH)+offset*_hoops_RPSIH); 
					*_hoops_PCAP = *_hoops_CGHHS;
					} break; 
				default: {
					char *_hoops_CGHHS = ((char*)_hoops_HHRAR)+i*_hoops_RPSIH;
					char *_hoops_PCAP = ((char*)_hoops_ACCHH)+offset*_hoops_RPSIH; 
					memcpy(_hoops_PCAP, _hoops_CGHHS, _hoops_RPSIH);
					} break; 
				} 
			}
		}
		else{ 
			offset = ++_hoops_GPCIC[_hoops_SHHCR];
#if SOLARIS_SYSTEM
			_hoops_ICPHS();
#endif
			array[elements-1-offset] = _hoops_RCPHS(_hoops_CGGRC);
			/* _hoops_RPP (_hoops_HGHHS) ((_hoops_GSPR*)_hoops_HGHHS)[(_hoops_IAGH-1-_hoops_SHI)*_hoops_SGHHS] = ((_hoops_GSPR*)_hoops_IGHHS)[_hoops_HAS*_hoops_SGHHS]; */
			if (_hoops_SASIH) {
				void *_hoops_HHRAR = _hoops_GPSIH;
				void *_hoops_ACCHH = _hoops_SASIH; 
				switch (_hoops_RPSIH) { 
				case 1: {	
					char *_hoops_CGHHS = ((char*)_hoops_HHRAR)+i*_hoops_RPSIH;
					char *_hoops_PCAP = ((char*)_hoops_ACCHH)+(elements-1-offset)*_hoops_RPSIH; 
					*_hoops_PCAP = *_hoops_CGHHS;
					} break; 
				case 2: { 
					short *_hoops_CGHHS = (short*)(((char*)_hoops_HHRAR)+i*_hoops_RPSIH);
					short *_hoops_PCAP = (short*)(((char*)_hoops_ACCHH)+(elements-1-offset)*_hoops_RPSIH); 
					*_hoops_PCAP = *_hoops_CGHHS;
					} break;	
				case 4:	{ 
					Integer32 *_hoops_CGHHS = (Integer32*)(((char*)_hoops_HHRAR)+i*_hoops_RPSIH);
					Integer32 *_hoops_PCAP = (Integer32*)(((char*)_hoops_ACCHH)+(elements-1-offset)*_hoops_RPSIH); 
					*_hoops_PCAP = *_hoops_CGHHS;
					} break; 
				default: {
					char *_hoops_CGHHS = ((char*)_hoops_HHRAR)+i*_hoops_RPSIH;
					char *_hoops_PCAP = ((char*)_hoops_ACCHH)+(elements-1-offset)*_hoops_RPSIH; 
					memcpy(_hoops_PCAP, _hoops_CGHHS, _hoops_RPSIH);
					} break; 
				} 
			}
		}
	}
	

	/* _hoops_IS _hoops_GGI _hoops_GIGR: */
	memcpy(_hoops_CCPHS, array, elements * sizeof(float));
}

void HI_Radix_Sort_11(float* _hoops_IASIH, float *_hoops_CASIH, void** _hoops_SASIH, void** _hoops_GPSIH, Integer32 _hoops_RPSIH, unsigned long elements, bool _hoops_APSIH)
{
	unsigned Integer32 i;
	unsigned Integer32 *_hoops_CCPHS = (unsigned Integer32*)_hoops_CASIH;
	unsigned Integer32 *array = (unsigned Integer32*)_hoops_IASIH;

	/* 3 _hoops_SCPHS _hoops_GPP _hoops_RH _hoops_RRGC: */
	const unsigned Integer32 _hoops_GSPHS = 2048;
	unsigned Integer32 _hoops_SACIC[6144]; /* _hoops_RSPHS * 3  */

	unsigned Integer32 *_hoops_IHHI = _hoops_SACIC + _hoops_GSPHS;
	unsigned Integer32 *_hoops_CHHI = _hoops_IHHI + _hoops_GSPHS;

	for (i = 0; i < _hoops_GSPHS * 3; i++) {
		_hoops_SACIC[i] = 0;
	}

	/* 1.  _hoops_GGAIA _hoops_ASPHS _hoops_RIH */
	for (i = 0; i < elements; i++) {
		unsigned Integer32 fi = 0;
		_hoops_APRRC(array);

		fi = _hoops_CIPHS((unsigned Integer32)array[i]);

		_hoops_SACIC[_0(fi)] ++;
		_hoops_IHHI[_1(fi)] ++;
		_hoops_CHHI[_2(fi)] ++;
	}
	
	/* 2.  _hoops_PSPHS _hoops_RH _hoops_SCPHS -- _hoops_GRR _hoops_HSPHS _hoops_RARP _hoops_ISPHS _hoops_RH _hoops_PHI _hoops_IIGR _hoops_HSH _hoops_HPSIR _hoops_ACAS. */
	{
		unsigned Integer32 _hoops_CSPHS = 0, _hoops_SSPHS = 0, _hoops_GGHHS = 0;
		unsigned Integer32 _hoops_AGHHS;
		for (i = 0; i < _hoops_GSPHS; i++) {

			_hoops_AGHHS = _hoops_SACIC[i] + _hoops_CSPHS;
			_hoops_SACIC[i] = _hoops_CSPHS - 1;
			_hoops_CSPHS = _hoops_AGHHS;

			_hoops_AGHHS = _hoops_IHHI[i] + _hoops_SSPHS;
			_hoops_IHHI[i] = _hoops_SSPHS - 1;
			_hoops_SSPHS = _hoops_AGHHS;

			_hoops_AGHHS = _hoops_CHHI[i] + _hoops_GGHHS;
			_hoops_CHHI[i] = _hoops_GGHHS - 1;
			_hoops_GGHHS = _hoops_AGHHS;
		}
	}

	/* _hoops_RAPSR 0: _hoops_PGHHS _hoops_RSIR _hoops_PIRA, _hoops_IRIGR/_hoops_GGI _hoops_HSPHS, _hoops_GGI _hoops_GGSR _hoops_AHAPI */
	for (i = 0; i < elements; i++) {
		unsigned Integer32 _hoops_SHHCR = 0;
		unsigned Integer32 fi = array[i];
		unsigned Integer32 offset = 0;
		_hoops_SIPHS(&fi);
		_hoops_SHHCR = _0(fi);
		
		_hoops_HIPHS(&array[i]);
		offset = ++_hoops_SACIC[_hoops_SHHCR];
		_hoops_CCPHS[offset] = fi;
		/* _hoops_RPP (_hoops_HGHHS) _hoops_IGHHS[_hoops_SHI] = _hoops_HGHHS[_hoops_HAS]; */
		if (_hoops_SASIH) {
			void *_hoops_HHRAR = _hoops_SASIH;
			void *_hoops_ACCHH = _hoops_GPSIH; 
			switch (_hoops_RPSIH) { 
			case 1: {	
				char *_hoops_CGHHS = ((char*)_hoops_HHRAR)+i*_hoops_RPSIH;
				char *_hoops_PCAP = ((char*)_hoops_ACCHH)+offset*_hoops_RPSIH; 
				*_hoops_PCAP = *_hoops_CGHHS;
				} break; 
			case 2: { 
				short *_hoops_CGHHS = (short*)(((char*)_hoops_HHRAR)+i*_hoops_RPSIH);
				short *_hoops_PCAP = (short*)(((char*)_hoops_ACCHH)+offset*_hoops_RPSIH); 
				*_hoops_PCAP = *_hoops_CGHHS;
				} break;	
			case 4:	{ 
				Integer32 *_hoops_CGHHS = (Integer32*)(((char*)_hoops_HHRAR)+i*_hoops_RPSIH);
				Integer32 *_hoops_PCAP = (Integer32*)(((char*)_hoops_ACCHH)+offset*_hoops_RPSIH); 
				*_hoops_PCAP = *_hoops_CGHHS;
				} break; 
			default: {
				char *_hoops_CGHHS = ((char*)_hoops_HHRAR)+i*_hoops_RPSIH;
				char *_hoops_PCAP = ((char*)_hoops_ACCHH)+offset*_hoops_RPSIH; 
				memcpy(_hoops_PCAP, _hoops_CGHHS, _hoops_RPSIH);
				} break; 
			} 
		}
	}

	/*	_hoops_RAPSR 1: _hoops_IRIGR/_hoops_GGI _hoops_HSPHS, _hoops_IPS
		_hoops_GSHHR -> _hoops_CRPR */
	for (i = 0; i < elements; i++) {
		unsigned Integer32 si = _hoops_CCPHS[i];
		unsigned Integer32 _hoops_SHHCR = _1(si);
		unsigned Integer32 offset = 0;
		
		_hoops_HIPHS(&_hoops_CCPHS[i]);
		offset = ++_hoops_IHHI[_hoops_SHHCR];
		array[offset] = si;
		/* _hoops_RPP (_hoops_HGHHS) _hoops_HGHHS[_hoops_SHI] = _hoops_IGHHS[_hoops_HAS]; */
		if (_hoops_SASIH) {
			void *_hoops_HHRAR = _hoops_GPSIH;
			void *_hoops_ACCHH = _hoops_SASIH; 
			switch (_hoops_RPSIH) { 
			case 1: {	
				char *_hoops_CGHHS = ((char*)_hoops_HHRAR)+i*_hoops_RPSIH;
				char *_hoops_PCAP = ((char*)_hoops_ACCHH)+offset*_hoops_RPSIH; 
				*_hoops_PCAP = *_hoops_CGHHS;
				} break; 
			case 2: { 
				short *_hoops_CGHHS = (short*)(((char*)_hoops_HHRAR)+i*_hoops_RPSIH);
				short *_hoops_PCAP = (short*)(((char*)_hoops_ACCHH)+offset*_hoops_RPSIH); 
				*_hoops_PCAP = *_hoops_CGHHS;
				} break;	
			case 4:	{ 
				Integer32 *_hoops_CGHHS = (Integer32*)(((char*)_hoops_HHRAR)+i*_hoops_RPSIH);
				Integer32 *_hoops_PCAP = (Integer32*)(((char*)_hoops_ACCHH)+offset*_hoops_RPSIH); 
				*_hoops_PCAP = *_hoops_CGHHS;
				} break; 
			default: {
				char *_hoops_CGHHS = ((char*)_hoops_HHRAR)+i*_hoops_RPSIH;
				char *_hoops_PCAP = ((char*)_hoops_ACCHH)+offset*_hoops_RPSIH; 
				memcpy(_hoops_PCAP, _hoops_CGHHS, _hoops_RPSIH);
				} break; 
			} 
		}
	}

	/*	_hoops_RAPSR 2: _hoops_IRIGR/_hoops_GGI _hoops_HSPHS, _hoops_IPS & _hoops_IHAA _hoops_GGSR
		_hoops_CRPR -> _hoops_GSHHR */
	for (i = 0; i < elements; i++) {
		unsigned Integer32 _hoops_CGGRC = array[i];
		unsigned Integer32 _hoops_SHHCR = _2(_hoops_CGGRC);
		unsigned Integer32 offset = 0;

		_hoops_HIPHS(&array[i]);
		if (_hoops_APSIH) {
			offset = ++_hoops_CHHI[_hoops_SHHCR];
			_hoops_CCPHS[offset] = _hoops_RCPHS(_hoops_CGGRC);
			/* _hoops_RPP (_hoops_HGHHS) _hoops_IGHHS[_hoops_SHI] = _hoops_HGHHS[_hoops_HAS]; */
			if (_hoops_SASIH) {
				void *_hoops_HHRAR = _hoops_SASIH;
				void *_hoops_ACCHH = _hoops_GPSIH; 
				switch (_hoops_RPSIH) { 
				case 1: {	
					char *_hoops_CGHHS = ((char*)_hoops_HHRAR)+i*_hoops_RPSIH;
					char *_hoops_PCAP = ((char*)_hoops_ACCHH)+offset*_hoops_RPSIH; 
					*_hoops_PCAP = *_hoops_CGHHS;
					} break; 
				case 2: { 
					short *_hoops_CGHHS = (short*)(((char*)_hoops_HHRAR)+i*_hoops_RPSIH);
					short *_hoops_PCAP = (short*)(((char*)_hoops_ACCHH)+offset*_hoops_RPSIH); 
					*_hoops_PCAP = *_hoops_CGHHS;
					} break;	
				case 4:	{ 
					Integer32 *_hoops_CGHHS = (Integer32*)(((char*)_hoops_HHRAR)+i*_hoops_RPSIH);
					Integer32 *_hoops_PCAP = (Integer32*)(((char*)_hoops_ACCHH)+offset*_hoops_RPSIH); 
					*_hoops_PCAP = *_hoops_CGHHS;
					} break; 
				default: {
					char *_hoops_CGHHS = ((char*)_hoops_HHRAR)+i*_hoops_RPSIH;
					char *_hoops_PCAP = ((char*)_hoops_ACCHH)+offset*_hoops_RPSIH; 
					memcpy(_hoops_PCAP, _hoops_CGHHS, _hoops_RPSIH);
					} break; 
				}
			}
		}
		else {
			offset = ++_hoops_CHHI[_hoops_SHHCR];
#if SOLARIS_SYSTEM
			_hoops_ICPHS();
#endif
			_hoops_CCPHS[elements-1-offset] = _hoops_RCPHS(_hoops_CGGRC);
			/* _hoops_RPP (_hoops_HGHHS) _hoops_IGHHS[_hoops_IAGH-1-_hoops_SHI] = _hoops_HGHHS[_hoops_HAS]; */
			if (_hoops_SASIH) {
				void *_hoops_HHRAR = _hoops_SASIH;
				void *_hoops_ACCHH = _hoops_GPSIH; 
				switch (_hoops_RPSIH) { 
				case 1: {	
					char *_hoops_CGHHS = ((char*)_hoops_HHRAR)+i*_hoops_RPSIH;
					char *_hoops_PCAP = ((char*)_hoops_ACCHH)+(elements-1-offset)*_hoops_RPSIH; 
					*_hoops_PCAP = *_hoops_CGHHS;
					} break; 
				case 2: { 
					short *_hoops_CGHHS = (short*)(((char*)_hoops_HHRAR)+i*_hoops_RPSIH);
					short *_hoops_PCAP = (short*)(((char*)_hoops_ACCHH)+(elements-1-offset)*_hoops_RPSIH); 
					*_hoops_PCAP = *_hoops_CGHHS;
					} break;	
				case 4:	{ 
					Integer32 *_hoops_CGHHS = (Integer32*)(((char*)_hoops_HHRAR)+i*_hoops_RPSIH);
					Integer32 *_hoops_PCAP = (Integer32*)(((char*)_hoops_ACCHH)+(elements-1-offset)*_hoops_RPSIH); 
					*_hoops_PCAP = *_hoops_CGHHS;
					} break; 
				default: {
					char *_hoops_CGHHS = ((char*)_hoops_HHRAR)+i*_hoops_RPSIH;
					char *_hoops_PCAP = ((char*)_hoops_ACCHH)+(elements-1-offset)*_hoops_RPSIH; 
					memcpy(_hoops_PCAP, _hoops_CGHHS, _hoops_RPSIH);
					} break; 
				} 
			}
		}
	}

	/* _hoops_IS _hoops_GGI _hoops_GIGR: */
	memcpy(array, _hoops_CCPHS, elements * sizeof(float));
	if (_hoops_SASIH) memcpy(_hoops_SASIH, _hoops_GPSIH, elements * _hoops_RPSIH);
}

/*
_hoops_RPR - _hoops_IPCP _hoops_PHI _hoops_IIGR _hoops_IAGH _hoops_IS _hoops_SHH _hoops_GSHHR
_hoops_AGHC - _hoops_IPCP _hoops_RGGHR _hoops_SGS _hoops_CHR _hoops_IGRC _hoops_GHHS _hoops_GSHHR
_hoops_CRPR - _hoops_PCCP _hoops_CRPR _hoops_SGS _hoops_SAGGR _hoops_GSHHR _hoops_GGAIA _hoops_IS _hoops_AGHC
_hoops_HAGPR - _hoops_RH _hoops_IGIR _hoops_IIGR _hoops_RH _hoops_IAGH _hoops_GGR _hoops_CRPR
_hoops_GACPR - _hoops_HRGR _hoops_RH _hoops_CRPR _hoops_IHGS _hoops_GSHHR _hoops_GACPR _hoops_PAR _hoops_CPIHR?
*/
void HI_Sort_Array(unsigned long count, float* priorities, void** array, int _hoops_IRAHH, bool _hoops_APSIH) {


	if (count < 16) {
		struct _hoops_GHPHS sc;
		sc.priorities = priorities;
		sc.array = (char*) array;
		sc._hoops_RPSIH = _hoops_IRAHH;
		ALLOC_ARRAY_CACHED(sc._hoops_RHPHS, sc._hoops_RPSIH, char);

		if (_hoops_APSIH)
			_hoops_HHPHS (&sc, 0, count-1, 1024);
		else
			_hoops_SHPHS (&sc, 0, count-1, 1024);

		FREE_ARRAY(sc._hoops_RHPHS, sc._hoops_RPSIH, char);
	}
	else if (count < 900) {
		float* _hoops_GRHHS;
		void** _hoops_RRHHS;
		/* _hoops_SGH _hoops_ARHHS 8 */
		ALLOC_ARRAY_CACHED (_hoops_GRHHS, count, float); 
		ALLOC_ARRAY_CACHED (_hoops_RRHHS, count, void*);
		HI_Radix_Sort_8(priorities, _hoops_GRHHS, array, _hoops_RRHHS, _hoops_IRAHH, count, _hoops_APSIH);
		FREE_ARRAY(_hoops_RRHHS, count, void*);
		FREE_ARRAY(_hoops_GRHHS, count, float);
	}
	else {
		float* _hoops_GRHHS;
		void** _hoops_RRHHS;
		/* _hoops_SGH _hoops_ARHHS 11 */
		ALLOC_ARRAY_CACHED (_hoops_GRHHS, count, float); 
		ALLOC_ARRAY_CACHED (_hoops_RRHHS, count, void*);
		HI_Radix_Sort_11(priorities, _hoops_GRHHS, array, _hoops_RRHHS, _hoops_IRAHH, count, _hoops_APSIH);
		FREE_ARRAY(_hoops_RRHHS, count, void*);
		FREE_ARRAY(_hoops_GRHHS, count, float);
	}

	
}

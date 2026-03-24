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
 * $Id: obf_tmp.txt 1.275 2011-01-13 19:37:29 reuben Exp $
 */

#ifndef _MSC_VER
// _hoops_CSCRS._hoops_CRSC _hoops_CPPC _hoops_AGCR _hoops_IH _hoops_SPHGR
#define HMUTEX_IMPLEMENT_FUNCTIONS
#else
#pragma warning (disable: 4073)
#pragma init_seg(lib)
#endif

#include "hoops.h"
#include "database.h"
#include "hversion.h"
#include "tandt.h"		/* _hoops_IH _hoops_SSCRS'_hoops_GRI _hoops_CAPP */
#include "hd_proto.h"
#include "hi_proto.h"
#include "adt.h"

HOOPS_API _hoops_IGHGP * HOOPS_WORLD = null;

HOOPS_API _hoops_GSSSH HOOPS_ETERNAL_WORLD_DATA;
HOOPS_API _hoops_GSSSH * HOOPS_ETERNAL_WORLD = null;


Point const _hoops_HPCH::_hoops_IPCH = Point (0.0f, 0.0f, 0.0f);

Vector const _hoops_IRGA::X_Axis = Vector (1.0f, 0.0f, 0.0f);
Vector const _hoops_IRGA::_hoops_RCPCR = Vector (0.0f, 1.0f, 0.0f);
Vector const _hoops_IRGA::_hoops_IGHH = Vector (0.0f, 0.0f, 1.0f);
Vector const _hoops_IRGA::_hoops_CRGA = Vector (0.0f, 0.0f, 0.0f);

_hoops_ARPA const _hoops_CGISA::_hoops_CRGA = _hoops_ARPA (0.0f, 0.0f, 0.0f, 0.0f);


_hoops_APCIR const _hoops_HGAGI::_hoops_IPCH = _hoops_APCIR (0.0, 0.0, 0.0);

_hoops_PPCIR const _hoops_GPIRA::X_Axis = _hoops_PPCIR (1.0, 0.0, 0.0);
_hoops_PPCIR const _hoops_GPIRA::_hoops_RCPCR = _hoops_PPCIR (0.0, 1.0, 0.0);
_hoops_PPCIR const _hoops_GPIRA::_hoops_IGHH = _hoops_PPCIR (0.0, 0.0, 1.0);
_hoops_PPCIR const _hoops_GPIRA::_hoops_CRGA = _hoops_PPCIR (0.0, 0.0, 0.0);

_hoops_AAIRA const _hoops_PPIRA::_hoops_CRGA = _hoops_AAIRA (0.0, 0.0, 0.0, 0.0);


RGB const _hoops_GPSR::_hoops_RPSR = RGB (0, 0, 0);
RGB const _hoops_GPSR::_hoops_IAHHP = RGB (1, 1, 1);

RGBA const _hoops_IGISA::_hoops_RPSR   = RGBA (0, 0, 0, 1);
RGBA const _hoops_IGISA::_hoops_IAHHP   = RGBA (1, 1, 1, 1);
RGBA const _hoops_IGISA::_hoops_SAHSR = RGBA (0, 0, 0, 0);

RGBAS32 const _hoops_CAHSR::_hoops_RPSR   = RGBAS32 (0,   0,   0, 255);
RGBAS32 const _hoops_CAHSR::_hoops_IAHHP   = RGBAS32 (255, 255, 255, 255);
RGBAS32 const _hoops_CAHSR::_hoops_SAHSR = RGBAS32 (0,   0,   0,   0);

_hoops_PACIR const _hoops_SGPGP::_hoops_GRPGP = _hoops_PACIR (-1.0f, 1.0f, -1.0f, 1.0f);


GLOBAL_FUNCTION void HI_Write_Lock_Database()
{
	_hoops_RPPPR();
}

GLOBAL_FUNCTION void HI_Read_Lock_Database()
{
	_hoops_CSPPR();
}

GLOBAL_FUNCTION void HI_Unlock_Database()
{
	_hoops_IRRPR();
}

GLOBAL_FUNCTION int HI_Check_Lock (
	Lock 			hl,
	char const *	file,
	int				line)
{
#ifndef _hoops_AGIGI
	UNREFERENCED(hl);
	UNREFERENCED(file);
	UNREFERENCED(line);
	return HM_LOCK_STATE_READ|HM_LOCK_STATE_WRITE;
#else
	return HM_Check_Lock ((HM_Lock *)hl, file, line);
#endif
}

local _hoops_AIGPR * _hoops_GGSRS(HThreadID thread_id)
{
	/* _hoops_PAGA: _hoops_SRCH _hoops_HRSAI -- _hoops_SSRR _hoops_PPGS/_hoops_ISSSH _hoops_ASSSH _hoops_SRPHP */
	_hoops_AIGPR * _hoops_RIGC;
	ALLOCATE_MEMORY (_hoops_RIGC, _hoops_AIGPR);
	ZERO_STRUCT (_hoops_RIGC, _hoops_AIGPR);

	_hoops_RIGC->_hoops_CACAA = &_hoops_RIGC->_hoops_SACAA[0];
	_hoops_RIGC->_hoops_SGSAH = -1;
	_hoops_RIGC->_hoops_GRSAH = -1;
	_hoops_RIGC->_hoops_RRSAH = -1;

	_hoops_RIGC->thread_id = thread_id;
	HM_CONSTRUCT_SEMAPHORE (_hoops_RIGC->semaphore, 1, 0);

	return _hoops_RIGC;
}


#ifdef HOOPS_DEBUG_BUILD
// _hoops_IH _hoops_AHRPR
#include <stdlib.h>
#endif


GLOBAL_FUNCTION void HI_Init_Internal_Data (void)
{
	_hoops_IGHGP *				_hoops_SSGGA = HOOPS_WORLD;

	ASSERT(_hoops_SSGGA == null);

	if (!HOOPS_ETERNAL_WORLD) {
		HOOPS_ETERNAL_WORLD = &HOOPS_ETERNAL_WORLD_DATA;
		ZERO_STRUCT (HOOPS_ETERNAL_WORLD, _hoops_GSSSH);
	}

	ALLOCATE_MEMORY (_hoops_SSGGA, _hoops_IGHGP);
	ZERO_STRUCT (_hoops_SSGGA, _hoops_IGHGP);
	HOOPS_WORLD = _hoops_SSGGA;

	HI_Set_System_Memory_Functions();
	if (HOOPS_ETERNAL_WORLD->_hoops_SCSPP) {
		_hoops_SSGGA->_hoops_SCSPP = HOOPS_ETERNAL_WORLD->_hoops_SCSPP;
		_hoops_SSGGA->malloc = HOOPS_ETERNAL_WORLD->malloc;
		_hoops_SSGGA->free = HOOPS_ETERNAL_WORLD->free;
	}
	else {
		_hoops_SSGGA->free = _hoops_SSGGA->_hoops_RSSPP;
		_hoops_SSGGA->malloc = _hoops_SSGGA->_hoops_GSSPP;
	}

	_hoops_SSGGA->_hoops_PCPGI = 1024*1024*512;
	_hoops_SSGGA->_hoops_HCPGI = 1.0f;
	_hoops_SSGGA->_hoops_ICPGI = 32;

	_hoops_SSGGA->_hoops_CRGHP = 
		_hoops_SSGGA->_hoops_IRGHP = 1.0f;

	CREATE_MUTEX (_hoops_SSGGA->_hoops_RPHGI);
	CREATE_MUTEX (_hoops_SSGGA->_hoops_PIPSA);
	CREATE_MUTEX (_hoops_SSGGA->_hoops_GAPHP);
	CREATE_MUTEX (_hoops_SSGGA->_hoops_IIAGP);
	CREATE_MUTEX (_hoops_SSGGA->_hoops_RIPSA);
	CREATE_MUTEX (_hoops_SSGGA->_hoops_RAPSA);
	CREATE_MUTEX (_hoops_SSGGA->_hoops_HPSAP);
	CREATE_MUTEX (_hoops_SSGGA->_hoops_APHGI);
	CREATE_MUTEX (_hoops_SSGGA->_hoops_PPHGI);
	CREATE_MUTEX (_hoops_SSGGA->_hoops_HPHGI);
	CREATE_MUTEX (_hoops_SSGGA->_hoops_SAAI);
	CREATE_MUTEX (_hoops_SSGGA->_hoops_RSASA);
	CREATE_MUTEX (_hoops_SSGGA->_hoops_IGAPH);
	CREATE_MUTEX (_hoops_SSGGA->_hoops_ICRGI);
	CREATE_LOCK (_hoops_SSGGA->_hoops_SSRGI);

	_hoops_SSGGA->_hoops_HIHI = 1;
	_hoops_SSGGA->type = _hoops_PRAIR;

	ALLOCATE_MEMORY (_hoops_SSGGA->time_stamp, _hoops_GSPGR);

	_hoops_SSGGA->_hoops_PGSCA = _hoops_GGSRS(THREAD_ID());
	_hoops_SSGGA->_hoops_SIPGI = _hoops_SSGGA->_hoops_PGSCA;

	_hoops_SSGGA->_hoops_GCPGI = HOOPS_VERSION;
	_hoops_SSGGA->_hoops_RCRGI = 666;

	_hoops_SSGGA->_hoops_ASPGI = true;

	HOOPS_WORLD->_hoops_PHCAR[_hoops_SIPHP] = HD_Transform_Not_At_All;
	HOOPS_WORLD->_hoops_PHCAR[_hoops_CIPHP] = HD_Transform_And_Test_XY_XY;
	HOOPS_WORLD->_hoops_PHCAR[_hoops_PCPHP] = HD_Transform_And_Test_XYZ_XY;
	HOOPS_WORLD->_hoops_PHCAR[_hoops_ACPHP] = HD_Transform_And_Test_XYZ_XYZ;
	HOOPS_WORLD->_hoops_PHCAR[_hoops_RCPHP] = HD_Transform_And_Test_XYZ_XY_W;
	HOOPS_WORLD->_hoops_PHCAR[_hoops_GCPHP] = HD_Transform_And_Test_XYZ_XYZ_W;


	_hoops_SSGGA->_hoops_RAPPR = _hoops_AGGHP;
	_hoops_SSGGA->encoding = _hoops_CCIGI;
	_hoops_SSGGA->_hoops_RRGHP = 0;

	_hoops_SSGGA->system_flags = _hoops_AGSPP |
						  _hoops_HGSPP |
						  HOOPS_ETERNAL_WORLD->system_flags;

	_hoops_SSGGA->_hoops_CRHGI = 1941;

	_hoops_SSGGA->_hoops_PAHGI = true;

	_hoops_SSGGA->_hoops_PRGHP = 50;

	_hoops_SSGGA->_hoops_CCRGI = 20000;

	_hoops_SSGGA->_hoops_RRHGA = HOOPS_ETERNAL_WORLD->_hoops_RRHGA;

	_hoops_SSGGA->_hoops_GPHGI = 1;

	_hoops_SSGGA->_hoops_PHARR = _hoops_CSSPP;

	_hoops_SSGGA->_hoops_GCPCR = _hoops_GIPHP;


#ifdef HOOPS_DEBUG_BUILD
	char *	e;

	e = getenv("HOOPS_DEBUG_RAW_MEMORY");
	if (e != null)
		_hoops_SSGGA->system_flags |= Sysop_RAW_MEMORY;
	
	e = getenv("HOOPS_DEBUG_MEMORY_LOGGING");
	if (e != null)
		_hoops_SSGGA->_hoops_IRARR |= _hoops_GRHGI;
#endif

	ASSERT(HOOPS_WORLD->memory_pool == 0);
	ASSERT(HOOPS_WORLD->_hoops_PGSCA->memory_pool == 0);
	
	HOOPS_WORLD->memory_pool = HI_Create_Memory_Pool(MPF_DEFAULT);
	HOOPS_WORLD->_hoops_PGSCA->memory_pool = HI_Create_Memory_Pool(MPF_NONE);
}


GLOBAL_FUNCTION _hoops_AIGPR * HI_Set_Name (const char * _hoops_SCPGA)
{
	_hoops_AIGPR *_hoops_RIGC;

	if (!HOOPS_WORLD || !HOOPS_WORLD->_hoops_GCSPP) {
		HI_Start_Hoops (_hoops_SCPGA);
		_hoops_RIGC = HOOPS_WORLD->_hoops_PGSCA;
	}
	else {
		// _hoops_SRPR _hoops_SGCRP _hoops_CGH _hoops_SHH _hoops_IPSP _hoops_ISSSH
		_hoops_HCRGI (_hoops_RIGC);
		_hoops_AASAH(_hoops_RIGC, _hoops_SCPGA);
	}

	return _hoops_RIGC;
}

GLOBAL_FUNCTION _hoops_AIGPR * HI_Find_Thread_Specific_Data (
	HThreadID _hoops_GGGGI,
	bool _hoops_RGGGI) {

#ifndef DISABLE_MUTEX
	_hoops_AIGPR *_hoops_RIGC = HOOPS_WORLD->_hoops_SIPGI;

	if (!BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP) ||
		_hoops_RIGC->thread_id == _hoops_GGGGI)
		return _hoops_RIGC;		/* _hoops_RGSRS & _hoops_PIHGR */

	/* _hoops_RRP _hoops_IS _hoops_RIPIR _hoops_IH _hoops_SCH... */
	_hoops_RIGC = HOOPS_WORLD->_hoops_PGSCA;
	do {
		if (_hoops_RIGC->thread_id == _hoops_GGGGI)
			break;
	} while ((_hoops_RIGC = _hoops_RIGC->next) != null);

	if (_hoops_RIGC == null) {
		/* _hoops_SHR _hoops_AAHS _hoops_ARI _hoops_GGR _hoops_AGSRS _hoops_IIGR _hoops_GHARR _hoops_HCSP, _hoops_RGR _hoops_RGCA _hoops_SHH _hoops_GGSP,
		 * _hoops_PPR _hoops_CGH _hoops_SHH _hoops_SHRII _hoops_RAGII _hoops_APIC */
		LOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);

		if (HOOPS_WORLD->_hoops_RCPGI &&
			_hoops_PRGGI::Success == HOOPS_WORLD->_hoops_RCPGI->LookupItem(_hoops_GGGGI, &_hoops_RIGC)) {

			if ((POINTER_SIZED_INT)_hoops_RIGC > 1 &&
				(_hoops_RGGGI ||
				 _hoops_RIGC->_hoops_GSHGH)) {

				UNLOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);
				goto _hoops_RRARI;
			}
			else {
				ASSERT(0); // _hoops_SGCRP _hoops_AHSHA _hoops_PIHA _hoops_IIP _hoops_SGH _hoops_IPSP _hoops_ISSSH _hoops_PIH _hoops_PII _hoops_RGR
				_hoops_HRAIR (HEC_FATAL_ERROR, HES_UNDEFINE_NOT_ALLOWED, "Unsafe threading.");
			}
		}

		_hoops_RIGC = _hoops_GGSRS(_hoops_GGGGI);
		_hoops_RIGC->memory_pool = HI_Create_Memory_Pool(MPF_NONE);

		_hoops_RIGC->next = HOOPS_WORLD->_hoops_PGSCA->next;
		HOOPS_WORLD->_hoops_PGSCA->next = _hoops_RIGC;

		UNLOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);
	}

_hoops_RRARI:

	/* _hoops_PCSA _hoops_ICRP _hoops_PGSRS _hoops_IGI */
	HOOPS_WORLD->_hoops_SIPGI = _hoops_RIGC;


	return _hoops_RIGC;
#else
	UNREFERENCED (_hoops_GGGGI);
	/* _hoops_PAHA'_hoops_RA _hoops_HGCR _hoops_PIGS _hoops_RPP _hoops_SR _hoops_SARS'_hoops_RA _hoops_RIPHR _hoops_CCA _hoops_ASSSH _hoops_IHAHP */
	return HOOPS_WORLD->_hoops_PGSCA;
#endif
}

#define _hoops_PRSHH(x)			((unsigned short)(x))

HOOPS_API _hoops_ACHGI HOOPS_READ_ONLY = {
	/* _hoops_HGSRS[8][8] */
	{{_hoops_PRSHH(0xFE00), _hoops_PRSHH(0x3E00), _hoops_PRSHH(0xCE00), _hoops_PRSHH(0x0E00),  _hoops_PRSHH(0xF200), _hoops_PRSHH(0x3200), _hoops_PRSHH(0xC200), _hoops_PRSHH(0x0200)},
	 {_hoops_PRSHH(0x7E00), _hoops_PRSHH(0xBE00), _hoops_PRSHH(0x4E00), _hoops_PRSHH(0x8E00),  _hoops_PRSHH(0x7200), _hoops_PRSHH(0xB200), _hoops_PRSHH(0x4200), _hoops_PRSHH(0x8200)},
	 {_hoops_PRSHH(0xDE00), _hoops_PRSHH(0x1E00), _hoops_PRSHH(0xEE00), _hoops_PRSHH(0x2E00),  _hoops_PRSHH(0xD200), _hoops_PRSHH(0x1200), _hoops_PRSHH(0xE200), _hoops_PRSHH(0x2200)},
	 {_hoops_PRSHH(0x5E00), _hoops_PRSHH(0x9E00), _hoops_PRSHH(0x6E00), _hoops_PRSHH(0xAE00),  _hoops_PRSHH(0x5200), _hoops_PRSHH(0x9200), _hoops_PRSHH(0x6200), _hoops_PRSHH(0xA200)},

	 {_hoops_PRSHH(0xF600), _hoops_PRSHH(0x3600), _hoops_PRSHH(0xC600), _hoops_PRSHH(0x0600),  _hoops_PRSHH(0xFA00), _hoops_PRSHH(0x3A00), _hoops_PRSHH(0xCA00), _hoops_PRSHH(0x0A00)},
	 {_hoops_PRSHH(0x7600), _hoops_PRSHH(0xB600), _hoops_PRSHH(0x4600), _hoops_PRSHH(0x8600),  _hoops_PRSHH(0x7A00), _hoops_PRSHH(0xBA00), _hoops_PRSHH(0x4A00), _hoops_PRSHH(0x8A00)},
	 {_hoops_PRSHH(0xD600), _hoops_PRSHH(0x1600), _hoops_PRSHH(0xE600), _hoops_PRSHH(0x2600),  _hoops_PRSHH(0xDA00), _hoops_PRSHH(0x1A00), _hoops_PRSHH(0xEA00), _hoops_PRSHH(0x2A00)},
	 {_hoops_PRSHH(0x5600), _hoops_PRSHH(0x9600), _hoops_PRSHH(0x6600), _hoops_PRSHH(0xA600),  _hoops_PRSHH(0x5A00), _hoops_PRSHH(0x9A00), _hoops_PRSHH(0x6A00), _hoops_PRSHH(0xAA00)}},

	/* _hoops_IGSRS[4], _hoops_CGSRS[8], _hoops_SGSRS[16] */
	{1, 2, 3, 0},
	{1, 2, 3, 4, 5, 6, 7, 0},
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0},

	/* _hoops_IIRPI[16] */
	{1, 2, 4, 8, 16, 32, 64, 128, 256, 512,
	 1024, 2048, 4096, 8192, 16384, 0 /* _hoops_PGSAH:32768 */},

	/* _hoops_GRSRS[64] */
	{	0,
		1,
		1, 2,
		1, 2, 2, 3,
		1, 2, 2, 3, 2, 3, 3, 4,
		1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
		1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
				2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6},

	/* _hoops_RRSRS */
	{0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0,
	 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0,
	 0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8,
	 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8,
	 0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4,
	 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4,
	 0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC,
	 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC,
	 0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2,
	 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2,
	 0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA,
	 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
	 0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6,
	 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6,
	 0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE,
	 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE,
	 0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1,
	 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
	 0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9,
	 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9,
	 0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5,
	 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5,
	 0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED,
	 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
	 0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3,
	 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3,
	 0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB,
	 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB,
	 0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7,
	 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7,
	 0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF,
	 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF},

#	ifdef _MSC_VER
#		pragma warning(disable: 4310)	// _hoops_HIIC _hoops_AHHPP _hoops_SRSR _hoops_PIRA
#	endif

	/* _hoops_ARSRS _hoops_GASR */
	{(char)0000, (char)0001, (char)0002, (char)0003,
	 (char)0004, (char)0005, (char)0006, (char)0007,
	 (char)0010, (char)0011, (char)0012, (char)0013,
	 (char)0014, (char)0015, (char)0016, (char)0017,
	 (char)0020, (char)0021, (char)0022, (char)0023,
	 (char)0024, (char)0025, (char)0026, (char)0027,
	 (char)0030, (char)0031, (char)0032, (char)0033,
	 (char)0034, (char)0035, (char)0036, (char)0037,
	 (char)0040, (char)0041, (char)0042, (char)0043,
	 (char)0044, (char)0045, (char)0046, (char)0047,
	 (char)0050, (char)0051, (char)0052, (char)0053,
	 (char)0054, (char)0055, (char)0056, (char)0057,
	 (char)0060, (char)0061, (char)0062, (char)0063,
	 (char)0064, (char)0065, (char)0066, (char)0067,
	 (char)0070, (char)0071, (char)0072, (char)0073,
	 (char)0074, (char)0075, (char)0076, (char)0077,
	 (char)0100, (char)0141, (char)0142, (char)0143,
	 (char)0144, (char)0145, (char)0146, (char)0147,
	 (char)0150, (char)0151, (char)0152, (char)0153,
	 (char)0154, (char)0155, (char)0156, (char)0157,
	 (char)0160, (char)0161, (char)0162, (char)0163,
	 (char)0164, (char)0165, (char)0166, (char)0167,
	 (char)0170, (char)0171, (char)0172, (char)0133,
	 (char)0134, (char)0135, (char)0136, (char)0137,
	 (char)0140, (char)0141, (char)0142, (char)0143,
	 (char)0144, (char)0145, (char)0146, (char)0147,
	 (char)0150, (char)0151, (char)0152, (char)0153,
	 (char)0154, (char)0155, (char)0156, (char)0157,
	 (char)0160, (char)0161, (char)0162, (char)0163,
	 (char)0164, (char)0165, (char)0166, (char)0167,
	 (char)0170, (char)0171, (char)0172, (char)0173,
	 (char)0174, (char)0175, (char)0176, (char)0177,
	 (char)0200, (char)0201, (char)0202, (char)0203,
	 (char)0204, (char)0205, (char)0206, (char)0207,
	 (char)0210, (char)0211, (char)0212, (char)0213,
	 (char)0214, (char)0215, (char)0216, (char)0217,
	 (char)0220, (char)0221, (char)0222, (char)0223,
	 (char)0224, (char)0225, (char)0226, (char)0227,
	 (char)0230, (char)0231, (char)0232, (char)0233,
	 (char)0234, (char)0235, (char)0236, (char)0237,
	 (char)0240, (char)0241, (char)0242, (char)0243,
	 (char)0244, (char)0245, (char)0246, (char)0247,
	 (char)0250, (char)0251, (char)0252, (char)0253,
	 (char)0254, (char)0255, (char)0256, (char)0257,
	 (char)0260, (char)0261, (char)0262, (char)0263,
	 (char)0264, (char)0265, (char)0266, (char)0267,
	 (char)0270, (char)0271, (char)0272, (char)0273,
	 (char)0274, (char)0275, (char)0276, (char)0277,
	 (char)0340, (char)0341, (char)0342, (char)0343,
	 (char)0344, (char)0345, (char)0346, (char)0347,
	 (char)0350, (char)0351, (char)0352, (char)0353,
	 (char)0354, (char)0355, (char)0356, (char)0357,
	 (char)0360, (char)0361, (char)0362, (char)0363,
	 (char)0364, (char)0365, (char)0366, (char)0327,
	 (char)0370, (char)0371, (char)0372, (char)0373,
	 (char)0374, (char)0375, (char)0376, (char)0337,
	 (char)0340, (char)0341, (char)0342, (char)0343,
	 (char)0344, (char)0345, (char)0346, (char)0347,
	 (char)0350, (char)0351, (char)0352, (char)0353,
	 (char)0354, (char)0355, (char)0356, (char)0357,
	 (char)0360, (char)0361, (char)0362, (char)0363,
	 (char)0364, (char)0365, (char)0366, (char)0367,
	 (char)0370, (char)0371, (char)0372, (char)0373,
	 (char)0374, (char)0375, (char)0376, (char)0377},

	/* _hoops_PRSRS[1024] */
	{
		 0.513870f, 0.175741f, 0.308652f, 0.534534f,
		 0.947628f, 0.171736f, 0.702231f, 0.226431f,
		 0.494773f, 0.124720f, 0.083899f, 0.389647f,
		 0.277226f, 0.368071f, 0.983437f, 0.535398f,
		 0.765682f, 0.646473f, 0.767139f, 0.780237f,
		 0.822951f, 0.151932f, 0.625477f, 0.314685f,
		 0.346901f, 0.917204f, 0.519760f, 0.401154f,
		 0.606758f, 0.785402f, 0.931523f, 0.869921f,
		 0.866525f, 0.674520f, 0.758400f, 0.581893f,
		 0.389248f, 0.355635f, 0.200232f, 0.826927f,
		 0.415903f, 0.463522f, 0.979163f, 0.126436f,
		 0.212637f, 0.958451f, 0.737463f, 0.409056f,
		 0.780113f, 0.757899f, 0.956842f, 0.028096f,
		 0.318728f, 0.756934f, 0.242995f, 0.589542f,
		 0.043424f, 0.956025f, 0.319133f, 0.059360f,
		 0.441876f, 0.915020f, 0.572247f, 0.118838f,
		 0.569771f, 0.252048f, 0.495858f, 0.236734f,
		 0.476961f, 0.406093f, 0.872998f, 0.426963f,
		 0.358218f, 0.381988f, 0.043180f, 0.160587f,
		 0.522351f, 0.696581f, 0.097100f, 0.400847f,
		 0.773432f, 0.244827f, 0.342824f, 0.229994f,
		 0.297877f, 0.304546f, 0.887207f, 0.036669f,
		 0.651147f, 0.398606f, 0.676297f, 0.732578f,
		 0.937797f, 0.233280f, 0.838481f, 0.967210f,
		 0.778638f, 0.431518f, 0.674102f, 0.809358f,
		 0.158765f, 0.279899f, 0.135323f, 0.864187f,
		 0.750185f, 0.207999f, 0.139963f, 0.294589f,
		 0.802805f, 0.218934f, 0.563082f, 0.715602f,
		 0.197542f, 0.989825f, 0.250038f, 0.430608f,
		 0.755274f, 0.860929f, 0.894781f, 0.978088f,
		 0.395412f, 0.432205f, 0.127140f, 0.457675f,
		 0.237831f, 0.986032f, 0.652831f, 0.604246f,
		 0.241906f, 0.454873f, 0.789960f, 0.078819f,
		 0.476410f, 0.152588f, 0.245752f, 0.944993f,
		 0.614020f, 0.988186f, 0.477276f, 0.799684f,
		 0.744184f, 0.380735f, 0.479891f, 0.526908f,
		 0.098099f, 0.594211f, 0.347183f, 0.143366f,
		 0.779540f, 0.710997f, 0.446139f, 0.704569f,
		 0.095309f, 0.962825f, 0.551302f, 0.740264f,
		 0.579039f, 0.637876f, 0.781656f, 0.187904f,
		 0.302103f, 0.282807f, 0.684006f, 0.292919f,
		 0.565391f, 0.418449f, 0.306581f, 0.444530f,
		 0.565690f, 0.487929f, 0.606633f, 0.415860f,
		 0.130424f, 0.255960f, 0.035758f, 0.977097f,
		 0.114506f, 0.378054f, 0.646711f, 0.350446f,
		 0.553049f, 0.358411f, 0.565451f, 0.475635f,
		 0.163682f, 0.615225f, 0.172170f, 0.554712f,
		 0.292231f, 0.872162f, 0.835062f, 0.844895f,
		 0.895509f, 0.594763f, 0.540566f, 0.168211f,
		 0.654958f, 0.690519f, 0.263855f, 0.106692f,
		 0.814912f, 0.191361f, 0.423297f, 0.351858f,
		 0.839209f, 0.137331f, 0.262667f, 0.177253f,
		 0.479918f, 0.380171f, 0.504823f, 0.502776f,
		 0.351924f, 0.525583f, 0.120635f, 0.519556f,
		 0.607121f, 0.732908f, 0.556884f, 0.344134f,
		 0.801968f, 0.590988f, 0.266907f, 0.670676f,
		 0.552153f, 0.788935f, 0.887718f, 0.889998f,
		 0.068109f, 0.800584f, 0.907367f, 0.644128f,
		 0.165154f, 0.301360f, 0.166283f, 0.285169f,
		 0.841976f, 0.536325f, 0.036350f, 0.207211f,
		 0.021239f, 0.358133f, 0.621471f, 0.520032f,
		 0.546037f, 0.153675f, 0.823362f, 0.033355f,
		 0.025968f, 0.378132f, 0.616332f, 0.020394f,
		 0.626561f, 0.915205f, 0.374798f, 0.729457f,
		 0.395814f, 0.982265f, 0.597287f, 0.112332f,
		 0.221591f, 0.799181f, 0.870664f, 0.738232f,
		 0.013631f, 0.739560f, 0.418353f, 0.362033f,
		 0.203911f, 0.183165f, 0.076289f, 0.115555f,
		 0.159123f, 0.788256f, 0.040355f, 0.790644f,
		 0.599013f, 0.402600f, 0.229052f, 0.182802f,
		 0.614316f, 0.331902f, 0.605152f, 0.964109f,
		 0.378071f, 0.184412f, 0.300094f, 0.054197f,
		 0.144022f, 0.010448f, 0.884850f, 0.958016f,
		 0.625903f, 0.955599f, 0.631040f, 0.039153f,
		 0.351310f, 0.146339f, 0.106021f, 0.197440f,
		 0.083947f, 0.026826f, 0.945717f, 0.919618f,
		 0.907975f, 0.865609f, 0.148927f, 0.171789f,
		 0.068223f, 0.651019f, 0.736875f, 0.102420f,
		 0.160007f, 0.093974f, 0.121734f, 0.024643f,
		 0.762306f, 0.956959f, 0.027900f, 0.646604f,
		 0.108057f, 0.427927f, 0.309732f, 0.018603f,
		 0.885293f, 0.757873f, 0.509539f, 0.165785f,
		 0.762909f, 0.880830f, 0.499552f, 0.875130f,
		 0.734772f, 0.235033f, 0.051616f, 0.605485f,
		 0.875949f, 0.504011f, 0.678388f, 0.989394f,
		 0.604792f, 0.496345f, 0.589750f, 0.895479f,
		 0.044631f, 0.882853f, 0.108217f, 0.520112f,
		 0.578829f, 0.009945f, 0.387075f, 0.477138f,
		 0.192946f, 0.507894f, 0.775009f, 0.354395f,
		 0.697759f, 0.912791f, 0.670958f, 0.705776f,
		 0.426894f, 0.020912f, 0.212958f, 0.947594f,
		 0.502821f, 0.194261f, 0.644719f, 0.127989f,
		 0.264949f, 0.336029f, 0.703689f, 0.038137f,
		 0.953592f, 0.754740f, 0.874348f, 0.634001f,
		 0.243531f, 0.635797f, 0.850488f, 0.237380f,
		 0.720950f, 0.339220f, 0.050226f, 0.485009f,
		 0.897470f, 0.242293f, 0.527509f, 0.494446f,
		 0.855048f, 0.345890f, 0.123841f, 0.215523f,
		 0.115482f, 0.363218f, 0.204003f, 0.436071f,
		 0.828279f, 0.509733f, 0.819508f, 0.410715f,
		 0.870630f, 0.712983f, 0.643532f, 0.581447f,
		 0.953245f, 0.461115f, 0.521089f, 0.358758f,
		 0.325798f, 0.008809f, 0.978186f, 0.432064f,
		 0.175729f, 0.159383f, 0.533711f, 0.578173f,
		 0.314158f, 0.341818f, 0.157807f, 0.436559f,
		 0.242659f, 0.201458f, 0.720482f, 0.220171f,
		 0.194639f, 0.423127f, 0.774202f, 0.830553f,
		 0.245082f, 0.005425f, 0.514215f, 0.345996f,
		 0.082395f, 0.704941f, 0.260366f, 0.351500f,
		 0.536126f, 0.869134f, 0.304142f, 0.079271f,
		 0.454275f, 0.376648f, 0.464701f, 0.828528f,
		 0.023977f, 0.903785f, 0.197636f, 0.633342f,
		 0.129290f, 0.235913f, 0.600229f, 0.647284f,
		 0.839841f, 0.842531f, 0.156927f, 0.213617f,
		 0.624083f, 0.434771f, 0.568817f, 0.089778f,
		 0.380915f, 0.724062f, 0.510823f, 0.794917f,
		 0.883400f, 0.100720f, 0.660395f, 0.549224f,
		 0.728357f, 0.451207f, 0.841428f, 0.773812f,
		 0.385553f, 0.832817f, 0.627170f, 0.619888f,
		 0.440254f, 0.224525f, 0.245860f, 0.495973f,
		 0.622894f, 0.072769f, 0.132851f, 0.061927f,
		 0.719590f, 0.850896f, 0.972971f, 0.658508f,
		 0.957281f, 0.351030f, 0.576863f, 0.641238f,
		 0.957214f, 0.927117f, 0.435064f, 0.587311f,
		 0.850548f, 0.407890f, 0.293568f, 0.844298f,
		 0.649812f, 0.898498f, 0.594616f, 0.389402f,
		 0.469974f, 0.189573f, 0.126483f, 0.468008f,
		 0.692872f, 0.992452f, 0.725989f, 0.980276f,
		 0.668749f, 0.719332f, 0.377500f, 0.084539f,
		 0.048655f, 0.027090f, 0.552158f, 0.986240f,
		 0.341448f, 0.843535f, 0.131103f, 0.381173f,
		 0.789165f, 0.094816f, 0.756421f, 0.521762f,
		 0.154494f, 0.852768f, 0.953587f, 0.375148f,
		 0.514112f, 0.120919f, 0.869126f, 0.841813f,
		 0.651629f, 0.977923f, 0.967278f, 0.503504f,
		 0.143889f, 0.297166f, 0.529382f, 0.869209f,
		 0.734386f, 0.761293f, 0.299752f, 0.587922f,
		 0.087534f, 0.390402f, 0.121784f, 0.596959f,
		 0.517552f, 0.302667f, 0.908050f, 0.674572f,
		 0.785702f, 0.926133f, 0.788127f, 0.365605f,
		 0.559641f, 0.380423f, 0.777903f, 0.748953f,
		 0.628632f, 0.247130f, 0.814128f, 0.015565f,
		 0.468361f, 0.447621f, 0.497944f, 0.325742f,
		 0.249118f, 0.447017f, 0.391145f, 0.914483f,
		 0.881083f, 0.503097f, 0.208932f, 0.913631f,
		 0.190476f, 0.178867f, 0.752893f, 0.859563f,
		 0.820310f, 0.837558f, 0.927969f, 0.355177f,
		 0.949512f, 0.338793f, 0.687162f, 0.854923f,
		 0.424145f, 0.654674f, 0.247717f, 0.041641f,
		 0.394495f, 0.624545f, 0.422543f, 0.763932f,
		 0.051762f, 0.567174f, 0.410619f, 0.002836f,
		 0.558119f, 0.969104f, 0.890137f, 0.836554f,
		 0.763870f, 0.967937f, 0.758118f, 0.871967f,
		 0.805478f, 0.849272f, 0.360280f, 0.111697f,
		 0.178189f, 0.276087f, 0.554873f, 0.725476f,
		 0.377031f, 0.469270f, 0.454261f, 0.694551f,
		 0.699910f, 0.058088f, 0.187981f, 0.797889f,
		 0.306573f, 0.819326f, 0.531039f, 0.908933f,
		 0.127172f, 0.023837f, 0.741193f, 0.071652f,
		 0.714201f, 0.609277f, 0.448963f, 0.324634f,
		 0.631526f, 0.897755f, 0.944135f, 0.741983f,
		 0.474287f, 0.077156f, 0.702491f, 0.659759f,
		 0.113404f, 0.164886f, 0.496526f, 0.556712f,
		 0.258443f, 0.672788f, 0.933905f, 0.558072f,
		 0.932590f, 0.691985f, 0.767395f, 0.031124f,
		 0.953489f, 0.616385f, 0.820038f, 0.241341f,
		 0.013685f, 0.223617f, 0.869303f, 0.537804f,
		 0.454426f, 0.332136f, 0.333983f, 0.036680f,
		 0.326580f, 0.753247f, 0.107560f, 0.271482f,
		 0.832403f, 0.756805f, 0.381819f, 0.778893f,
		 0.741924f, 0.769335f, 0.804441f, 0.088873f,
		 0.877684f, 0.523324f, 0.814327f, 0.087820f,
		 0.261588f, 0.376432f, 0.498412f, 0.223525f,
		 0.017617f, 0.019383f, 0.813708f, 0.520677f,
		 0.624141f, 0.291269f, 0.518339f, 0.875659f,
		 0.609605f, 0.321029f, 0.655303f, 0.599401f,
		 0.285312f, 0.713854f, 0.932718f, 0.677017f,
		 0.609074f, 0.001256f, 0.844311f, 0.712998f,
		 0.773465f, 0.073566f, 0.873883f, 0.030701f,
		 0.612440f, 0.813600f, 0.627509f, 0.894880f,
		 0.420061f, 0.650248f, 0.237231f, 0.326019f,
		 0.275079f, 0.250734f, 0.879970f, 0.475212f,
		 0.465133f, 0.070299f, 0.755440f, 0.028332f,
		 0.104297f, 0.978057f, 0.366780f, 0.608258f,
		 0.537751f, 0.677771f, 0.447686f, 0.643890f,
		 0.627297f, 0.142297f, 0.379761f, 0.674719f,
		 0.511493f, 0.780460f, 0.443864f, 0.559684f,
		 0.934146f, 0.555093f, 0.749184f, 0.559085f,
		 0.734911f, 0.771001f, 0.183804f, 0.758285f,
		 0.595749f, 0.751598f, 0.230494f, 0.801968f,
		 0.637002f, 0.122963f, 0.991493f, 0.407687f,
		 0.956814f, 0.924070f, 0.266023f, 0.627457f,
		 0.707676f, 0.261940f, 0.024290f, 0.326155f,
		 0.803820f, 0.730463f, 0.121714f, 0.845454f,
		 0.853225f, 0.311646f, 0.597148f, 0.322065f,
		 0.407988f, 0.978025f, 0.398834f, 0.629019f,
		 0.126793f, 0.715010f, 0.881833f, 0.408749f,
		 0.943250f, 0.181889f, 0.920699f, 0.166717f,
		 0.833840f, 0.730267f, 0.981137f, 0.894340f,
		 0.279215f, 0.998666f, 0.994388f, 0.189960f,
		 0.012616f, 0.802055f, 0.378106f, 0.346613f,
		 0.149141f, 0.535043f, 0.047464f, 0.375347f,
		 0.289629f, 0.807506f, 0.760250f, 0.432832f,
		 0.692901f, 0.531373f, 0.639691f, 0.622016f,
		 0.110111f, 0.177342f, 0.218768f, 0.634590f,
		 0.374954f, 0.420268f, 0.849756f, 0.203980f,
		 0.343489f, 0.891966f, 0.822762f, 0.837656f,
		 0.277312f, 0.260196f, 0.036983f, 0.797473f,
		 0.263851f, 0.352559f, 0.568460f, 0.796818f,
		 0.767509f, 0.544074f, 0.978057f, 0.383297f,
		 0.905421f, 0.127171f, 0.703433f, 0.475726f,
		 0.541572f, 0.882860f, 0.378739f, 0.024161f,
		 0.793020f, 0.571817f, 0.425810f, 0.261735f,
		 0.041986f, 0.564147f, 0.760584f, 0.517028f,
		 0.047540f, 0.326567f, 0.958506f, 0.055750f,
		 0.250665f, 0.985759f, 0.722666f, 0.920458f,
		 0.866411f, 0.686646f, 0.998429f, 0.237072f,
		 0.856922f, 0.964343f, 0.578288f, 0.956949f,
		 0.379068f, 0.848522f, 0.540710f, 0.503237f,
		 0.800435f, 0.918961f, 0.366708f, 0.290287f,
		 0.877425f, 0.031002f, 0.077912f, 0.584861f,
		 0.189217f, 0.929689f, 0.239854f, 0.677883f,
		 0.421336f, 0.471326f, 0.174257f, 0.835488f,
		 0.592584f, 0.671205f, 0.224043f, 0.998121f,
		 0.819073f, 0.296260f, 0.414839f, 0.696429f,
		 0.709127f, 0.221386f, 0.356702f, 0.152700f,
		 0.982787f, 0.268190f, 0.729845f, 0.036606f,
		 0.409676f, 0.744901f, 0.198083f, 0.843978f,
		 0.658978f, 0.406216f, 0.093774f, 0.367398f,
		 0.155271f, 0.051806f, 0.717985f, 0.227317f,
		 0.533969f, 0.482248f, 0.599654f, 0.932485f,
		 0.790131f, 0.031133f, 0.557473f, 0.438424f,
		 0.714369f, 0.392092f, 0.908265f, 0.672690f,
		 0.709623f, 0.959491f, 0.665593f, 0.995697f,
		 0.582543f, 0.401555f, 0.072352f, 0.065822f,
		 0.403230f, 0.684655f, 0.311095f, 0.077569f,
		 0.027085f, 0.267528f, 0.735846f, 0.841522f,
		 0.372520f, 0.684159f, 0.469148f, 0.674850f,
		 0.048279f, 0.234088f, 0.708087f, 0.571106f,
		 0.424115f, 0.998893f, 0.583062f, 0.618073f,
		 0.738576f, 0.903587f, 0.913034f, 0.132409f,
		 0.337658f, 0.041696f, 0.701007f, 0.479835f,
		 0.638056f, 0.982748f, 0.713494f, 0.049626f,
		 0.908784f, 0.280946f, 0.987726f, 0.352143f,
		 0.464900f, 0.903755f, 0.610331f, 0.708161f,
		 0.367089f, 0.799161f, 0.611261f, 0.498755f,
		 0.220860f, 0.320354f, 0.316693f, 0.444467f,
		 0.169097f, 0.726585f, 0.004669f, 0.882529f,
		 0.671724f, 0.478939f, 0.207223f, 0.510888f,
		 0.166229f, 0.549786f, 0.502737f, 0.567762f,
		 0.202790f, 0.464650f, 0.142286f, 0.915509f,
		 0.147772f, 0.295251f, 0.353709f, 0.997533f,
		 0.049327f, 0.322467f, 0.667180f, 0.136993f,
		 0.758850f, 0.587974f, 0.105996f, 0.146053f,
		 0.902052f, 0.053301f, 0.586361f, 0.714431f,
		 0.793388f, 0.585058f, 0.369900f, 0.546001f
	},

	{ /*_hoops_HRSRS*/
		(0.0f/255.0f),	(1.0f/255.0f),	(2.0f/255.0f),	(3.0f/255.0f),	(4.0f/255.0f),	(5.0f/255.0f),
		(6.0f/255.0f),	(7.0f/255.0f),	(8.0f/255.0f),	(9.0f/255.0f),	(10.0f/255.0f),	(11.0f/255.0f),
		(12.0f/255.0f),	(13.0f/255.0f),	(14.0f/255.0f),	(15.0f/255.0f),	(16.0f/255.0f),	(17.0f/255.0f),
		(18.0f/255.0f),	(19.0f/255.0f),	(20.0f/255.0f),	(21.0f/255.0f),	(22.0f/255.0f),	(23.0f/255.0f),
		(24.0f/255.0f),	(25.0f/255.0f),	(26.0f/255.0f),	(27.0f/255.0f),	(28.0f/255.0f),	(29.0f/255.0f),
		(30.0f/255.0f),	(31.0f/255.0f),	(32.0f/255.0f),	(33.0f/255.0f),	(34.0f/255.0f),	(35.0f/255.0f),
		(36.0f/255.0f),	(37.0f/255.0f),	(38.0f/255.0f),	(39.0f/255.0f),	(40.0f/255.0f),	(41.0f/255.0f),
		(42.0f/255.0f),	(43.0f/255.0f),	(44.0f/255.0f),	(45.0f/255.0f),	(46.0f/255.0f),	(47.0f/255.0f),
		(48.0f/255.0f),	(49.0f/255.0f),	(50.0f/255.0f),	(51.0f/255.0f),	(52.0f/255.0f),	(53.0f/255.0f),
		(54.0f/255.0f),	(55.0f/255.0f),	(56.0f/255.0f),	(57.0f/255.0f),	(58.0f/255.0f),	(59.0f/255.0f),
		(60.0f/255.0f),	(61.0f/255.0f),	(62.0f/255.0f),	(63.0f/255.0f),	(64.0f/255.0f),	(65.0f/255.0f),
		(66.0f/255.0f),	(67.0f/255.0f),	(68.0f/255.0f),	(69.0f/255.0f),	(70.0f/255.0f),	(71.0f/255.0f),
		(72.0f/255.0f),	(73.0f/255.0f),	(74.0f/255.0f),	(75.0f/255.0f),	(76.0f/255.0f),	(77.0f/255.0f),
		(78.0f/255.0f),	(79.0f/255.0f),	(80.0f/255.0f),	(81.0f/255.0f),	(82.0f/255.0f),	(83.0f/255.0f),
		(84.0f/255.0f),	(85.0f/255.0f),	(86.0f/255.0f),	(87.0f/255.0f),	(88.0f/255.0f),	(89.0f/255.0f),
		(90.0f/255.0f),	(91.0f/255.0f),	(92.0f/255.0f),	(93.0f/255.0f),	(94.0f/255.0f),	(95.0f/255.0f),
		(96.0f/255.0f),	(97.0f/255.0f),	(98.0f/255.0f),	(99.0f/255.0f),	(100.0f/255.0f), (101.0f/255.0f),
		(102.0f/255.0f), (103.0f/255.0f), (104.0f/255.0f), (105.0f/255.0f), (106.0f/255.0f), (107.0f/255.0f),
		(108.0f/255.0f), (109.0f/255.0f), (110.0f/255.0f), (111.0f/255.0f), (112.0f/255.0f), (113.0f/255.0f),
		(114.0f/255.0f), (115.0f/255.0f), (116.0f/255.0f), (117.0f/255.0f), (118.0f/255.0f), (119.0f/255.0f),
		(120.0f/255.0f), (121.0f/255.0f), (122.0f/255.0f), (123.0f/255.0f), (124.0f/255.0f), (125.0f/255.0f),
		(126.0f/255.0f), (127.0f/255.0f), (128.0f/255.0f), (129.0f/255.0f), (130.0f/255.0f), (131.0f/255.0f),
		(132.0f/255.0f), (133.0f/255.0f), (134.0f/255.0f), (135.0f/255.0f), (136.0f/255.0f), (137.0f/255.0f),
		(138.0f/255.0f), (139.0f/255.0f), (140.0f/255.0f), (141.0f/255.0f), (142.0f/255.0f), (143.0f/255.0f),
		(144.0f/255.0f), (145.0f/255.0f), (146.0f/255.0f), (147.0f/255.0f), (148.0f/255.0f), (149.0f/255.0f),
		(150.0f/255.0f), (151.0f/255.0f), (152.0f/255.0f), (153.0f/255.0f), (154.0f/255.0f), (155.0f/255.0f),
		(156.0f/255.0f), (157.0f/255.0f), (158.0f/255.0f), (159.0f/255.0f), (160.0f/255.0f), (161.0f/255.0f),
		(162.0f/255.0f), (163.0f/255.0f), (164.0f/255.0f), (165.0f/255.0f), (166.0f/255.0f), (167.0f/255.0f),
		(168.0f/255.0f), (169.0f/255.0f), (170.0f/255.0f), (171.0f/255.0f), (172.0f/255.0f), (173.0f/255.0f),
		(174.0f/255.0f), (175.0f/255.0f), (176.0f/255.0f), (177.0f/255.0f), (178.0f/255.0f), (179.0f/255.0f),
		(180.0f/255.0f), (181.0f/255.0f), (182.0f/255.0f), (183.0f/255.0f), (184.0f/255.0f), (185.0f/255.0f),
		(186.0f/255.0f), (187.0f/255.0f), (188.0f/255.0f), (189.0f/255.0f), (190.0f/255.0f), (191.0f/255.0f),
		(192.0f/255.0f), (193.0f/255.0f), (194.0f/255.0f), (195.0f/255.0f), (196.0f/255.0f), (197.0f/255.0f),
		(198.0f/255.0f), (199.0f/255.0f), (200.0f/255.0f), (201.0f/255.0f), (202.0f/255.0f), (203.0f/255.0f),
		(204.0f/255.0f), (205.0f/255.0f), (206.0f/255.0f), (207.0f/255.0f), (208.0f/255.0f), (209.0f/255.0f),
		(210.0f/255.0f), (211.0f/255.0f), (212.0f/255.0f), (213.0f/255.0f), (214.0f/255.0f), (215.0f/255.0f),
		(216.0f/255.0f), (217.0f/255.0f), (218.0f/255.0f), (219.0f/255.0f), (220.0f/255.0f), (221.0f/255.0f),
		(222.0f/255.0f), (223.0f/255.0f), (224.0f/255.0f), (225.0f/255.0f), (226.0f/255.0f), (227.0f/255.0f),
		(228.0f/255.0f), (229.0f/255.0f), (230.0f/255.0f), (231.0f/255.0f), (232.0f/255.0f), (233.0f/255.0f),
		(234.0f/255.0f), (235.0f/255.0f), (236.0f/255.0f), (237.0f/255.0f), (238.0f/255.0f), (239.0f/255.0f),
		(240.0f/255.0f), (241.0f/255.0f), (242.0f/255.0f), (243.0f/255.0f), (244.0f/255.0f), (245.0f/255.0f),
		(246.0f/255.0f), (247.0f/255.0f), (248.0f/255.0f), (249.0f/255.0f), (250.0f/255.0f), (251.0f/255.0f),
		(252.0f/255.0f), (253.0f/255.0f), (254.0f/255.0f), (255.0f/255.0f)
	},
	/* _hoops_IRSRS */
	"Attempted use of a feature disabled in this custom HOOPS build:",

	/*	_hoops_CRSRS */
	{M_SPECULAR,
	M_MIRROR,
	M_TRANSMISSION,
	M_EMISSION},
	/*	_hoops_SRSRS */
	{M_SPECULAR,
	 M_MIRROR,
	 M_TRANSMISSION,
	 M_EMISSION,
	 _hoops_SIARA,
	 _hoops_GCARA},
	/*	_hoops_GASRS */
	{_hoops_PIARA,
	 _hoops_HIARA,
	 _hoops_IIARA,
	 _hoops_CIARA,
	 _hoops_SIARA,
	 _hoops_GCARA}
};

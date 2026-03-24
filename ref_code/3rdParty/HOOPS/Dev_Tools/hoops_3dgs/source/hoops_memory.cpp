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
 * $Id: obf_tmp.txt 1.256 2010-12-06 22:16:11 jason Exp $
 */

#ifdef H_MUTEX_DEBUG_TRACE
#undef H_MUTEX_DEBUG_TRACE
#endif

#include "hoops.h"
#include "database.h"
#include "hi_proto.h"
#include "hc_proto.h"
#include "hpserror.h"
#include "task_queue.h"
#include "adt.h"

#include <stdio.h>
#include <stdlib.h>


Begin_HOOPS_Namespace

//#_hoops_PPIP _hoops_SHARI

#define _hoops_GIARI(_size) (((_size) + (1<<ALIGNMENT) - 1) & ~((1<<ALIGNMENT) - 1))

#define _hoops_RIARI _hoops_GIARI(sizeof(_hoops_AIARI))


#define QUICK_MEM_BLOCK_SIZE			(4096 - 2*sizeof(void *))
#define QUICK_MEM_MAX_BLOCK_SIZE		(QUICK_MEM_BLOCK_SIZE-_hoops_RIARI)


#define QUICK_MEM_MAX_BYTES				512
#define QUICK_MEM_SLOT(glob_size)		(int)((glob_size-1)>>ALIGNMENT)
#define QUICK_MEM_SLOT_SIZE(_hoops_GIARA)		(int)((_hoops_GIARA+1)<<ALIGNMENT)
#define QUICK_MEM_SLOTS					(QUICK_MEM_SLOT(QUICK_MEM_MAX_BYTES)+1)

#define _hoops_PIARI		(QUICK_MEM_BLOCK_SIZE*1024*4)


#define _hoops_HIARI				10 // 1024
#define _hoops_IIARI					(1<<_hoops_HIARI)
#define _hoops_CIARI					64
#define _hoops_SIARI				(_hoops_IIARI*_hoops_CIARI)


#define _hoops_GCARI(_hoops_PASIH)	(int)((_hoops_PASIH-1)>>_hoops_HIARI)
#define _hoops_RCARI (_hoops_GCARI(_hoops_SIARI)+1)


#define _hoops_ACARI			18 // 1024*256
#define _hoops_PCARI				(1<<_hoops_ACARI)
#define _hoops_HCARI				32
#define _hoops_ICARI			(_hoops_PCARI*_hoops_HCARI)


#define _hoops_CCARI(_hoops_PASIH)	(int)((_hoops_PASIH-1)>>_hoops_ACARI)
#define _hoops_SCARI (_hoops_CCARI(_hoops_ICARI)+1)

#define _hoops_GSARI		1024*1024*64
#define _hoops_RSARI			1
#define _hoops_ASARI	2

#define _hoops_PSARI(pool) (void)pool

#ifdef VALIDATE_MEMORY
//#_hoops_PPIP _hoops_HSARI
#define _hoops_ISARI
#	include <stdio.h>

class _hoops_CSARI {
public:
	Memory_Pool const *	pool;
	char const *		type;
	char const *		file;
	int					line;
	size_t				count;
	int					_hoops_SSARI;

	_hoops_CSARI (Memory_Pool * _hoops_GGPRI, const char * _hoops_RGPRI, const char * _hoops_AGPRI, int _hoops_PGPRI, size_t _hoops_CRHC, int _hoops_HGPRI) :
		pool(_hoops_GGPRI), type(_hoops_RGPRI), file(_hoops_AGPRI), line(_hoops_PGPRI), count(_hoops_CRHC), _hoops_SSARI(_hoops_HGPRI) {;}
};

typedef VHash<const void *, _hoops_CSARI *> _hoops_IGPRI;

#endif


struct _hoops_CGPRI {
	_hoops_CGPRI *			next;
};



struct _hoops_SGPRI {
	_hoops_AIARI *			_hoops_GRPRI;
#ifdef VALIDATE_MEMORY
	const char *			type_name;
	unsigned Integer32		_hoops_RRPRI;
#endif
	Integer32				size;
};

struct _hoops_AIARI {
	_hoops_CGPRI *			globs;
	_hoops_AIARI *		next;
	_hoops_AIARI **		backlink;
	_hoops_AIARI *		_hoops_ARPRI;
	_hoops_AIARI **		_hoops_PRPRI;
	Memory_Pool *		pool;

	size_t				size;
	unsigned Integer32	glob_count;
	Integer32			_hoops_HRPRI;
	Integer32			_hoops_GIARA;
};

static const int _hoops_IRPRI[_hoops_RCARI] = {

#if 1

	1024*16,1024*8,1024*4,1024*2, 128,128,128,128,

	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,

	32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,

	16,16,16,16,16,16,16,16,
#else
	1024*16,1024*8,1024*4,1024*2, 1024,1024,1024,1024,
	512,512,512,512,512,512,512,512,
	512,512,512,512,512,512,512,512,
	512,512,512,512,512,512,512,512,

	256,256,256,256,256,256,256,256,
	256,256,256,256,256,256,256,256,
	256,256,256,256,256,256,256,256,
	256,256,256,256,256,256,256,256,
#endif
	//512,512,512,512,512,512,512,512,
	//256,256,256,256,256,256,256,256,
	//128,128,128,128,128,128,128,128,
	//64,64,64,64,64,64,64,64,
	//32,32,32,32,32,32,32,32,
	//16,16,16,16,16,16,16,16,
	//8,8,8,8,8,8,8,8,
};

static const int _hoops_CRPRI[_hoops_SCARI] = {
	8,8,8,8,8,8,8,8,
	4,4,4,4,4,4,4,4,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
};

#define _hoops_SRPRI	8
#define _hoops_GAPRI		_hoops_PIARI

static const size_t _hoops_RAPRI[_hoops_SRPRI] = {
	1024*2, // 2_hoops_CRRGR
	QUICK_MEM_BLOCK_SIZE-1, // <~4_hoops_CRRGR
	QUICK_MEM_BLOCK_SIZE, // ~4_hoops_CRRGR
	1024*16, // 16_hoops_CRRGR
	1024*64, // 64_hoops_CRRGR
	1024*1024, // 1_hoops_RPRAR
	1024*1024*4, // 4_hoops_RPRAR
	_hoops_GAPRI // 16_hoops_RPRAR
};

static const size_t _hoops_AAPRI[_hoops_SRPRI] = {
	1024*1024*2, // 2_hoops_CRRGR
	1024*1024*2, // <~4_hoops_CRRGR
#if 1
	1024*1024*32, // ~4_hoops_CRRGR
	1024*1024*16, // 16_hoops_CRRGR
	1024*1024*16, // 64_hoops_CRRGR
	1024*1024*32, // 1_hoops_RPRAR
	1024*1024*32, // 4_hoops_RPRAR
#else
	1024*1024*64, // ~4_hoops_CRRGR
	1024*1024*64, // 16_hoops_CRRGR
	1024*1024*64, // 64_hoops_CRRGR
	1024*1024*64, // 1_hoops_RPRAR
	1024*1024*64, // 4_hoops_RPRAR
#endif
	1024*1024*64 // 16_hoops_RPRAR
};

struct _hoops_PAPRI {
	_hoops_AIARI *		_hoops_HAPRI[_hoops_SRPRI];
	_hoops_AIARI *		_hoops_IAPRI[_hoops_SRPRI];
	size_t				_hoops_CAPRI[_hoops_SRPRI];
};

struct Quick_Slot {
	_hoops_AIARI *		_hoops_SAPRI;
	_hoops_AIARI *		_hoops_GPPRI;
	_hoops_AIARI *		_hoops_RPPRI;
	_hoops_AIARI *		_hoops_APPRI;
};

struct _hoops_PPPRI {
	_hoops_AIARI *		_hoops_HAPRI;
	int					_hoops_HPPRI;
	int					_hoops_IPPRI;
};

struct _hoops_CPPRI {
	_hoops_GSPGR 				_hoops_SPPRI;
	_hoops_AIARI *		_hoops_HAPRI;
	int					_hoops_HPPRI;
	int					_hoops_IPPRI;
};


typedef VHash<void *, const char *> _hoops_GHPRI;


#define _hoops_RHPRI	0x10000000
#define _hoops_AHPRI	0x01000000

struct Memory_Pool {
	POINTER_SIZED_INT	flags;
#ifdef _hoops_PHPRI
	_hoops_CCAGP			_hoops_RHAGR;
#else
	_hoops_CPGRR				_hoops_RASCA;
#endif

	_hoops_CHSPP		malloc;
	_hoops_GISPP			free;

	size_t				_hoops_HHPRI;
	_hoops_GCARR *				_hoops_IHPRI;
	_hoops_AIARI *		_hoops_CHPRI;
	_hoops_AIARI *		_hoops_SHPRI;

	Quick_Slot *		_hoops_GIPRI;
	_hoops_PPPRI *			_hoops_RIPRI;
	_hoops_CPPRI *	_hoops_AIPRI;
	_hoops_CPPRI *	_hoops_PIPRI;
	_hoops_PAPRI *			_hoops_HIPRI;

	size_t				_hoops_IIPRI;
	size_t				_hoops_CIPRI;
	size_t				_hoops_SIPRI;

	size_t				_hoops_GCPRI;
	volatile size_t		_hoops_RCPRI;

	Memory_Pool *		next;

#ifdef VALIDATE_MEMORY
	_hoops_RRGGI *	_hoops_ACPRI;
	_hoops_IGPRI *		_hoops_PCPRI;
#endif
};
End_HOOPS_Namespace;

/* _hoops_HSPR _hoops_III _hoops_HCPRI _hoops_IS _hoops_GGHSP(_hoops_ICPRI) + 1 _hoops_RAPSR, */
/* _hoops_ISGRH _hoops_GH _hoops_IS _hoops_SPS _hoops_PRGI _hoops_GPGR _hoops_IIGR _hoops_GHARR'_hoops_GRI _hoops_AHSGP _hoops_AASC */
#define GLOB_HEADER_SIZE _hoops_GIARI(sizeof(_hoops_SGPRI))

#ifdef VALIDATE_MEMORY
#	define _hoops_CCPRI		0xDEADBEEF
#	define _hoops_SCPRI		0xCAFEF00D
#	define _hoops_GSPRI			0x55
#	define GLOB_FOOTER_SIZE (int)(1<<ALIGNMENT)
#else
#	define GLOB_FOOTER_SIZE 0
#endif


local INLINE void _hoops_RSPRI(_hoops_SGPRI * _hoops_ASPRI, int size, _hoops_AIARI * _hoops_PSPRI)
{
	_hoops_ASPRI->_hoops_GRPRI = _hoops_PSPRI;
	_hoops_ASPRI->size = size;

#ifdef VALIDATE_MEMORY
	char *	remainder = (char *)_hoops_ASPRI + sizeof(_hoops_SGPRI);
	long	_hoops_HSPRI = size + GLOB_HEADER_SIZE - sizeof(_hoops_SGPRI) + GLOB_FOOTER_SIZE;
	_hoops_ASPRI->type_name = 0;
	_hoops_ASPRI->_hoops_RRPRI = _hoops_CCPRI;
	SET_MEMORY (remainder, _hoops_HSPRI, _hoops_GSPRI);
#endif
}

#ifdef _hoops_PHPRI

INLINE bool _hoops_ISPRI(Memory_Pool const * pool)
{
	if (BIT (pool->flags, MPF_LOCKING) &&
		BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP)) {
		pool->_hoops_RHAGR._hoops_PRPGR(THREAD_ID());
		ASSERT(!BIT(pool->flags, _hoops_RHPRI));
		_hoops_PGRCA(pool)->flags |= _hoops_RHPRI;
		return true;
	}
	return false;
}

INLINE void _hoops_CSPRI(Memory_Pool const * pool)
{
	ASSERT(BIT(pool->flags, _hoops_RHPRI));
	_hoops_PGRCA(pool)->flags &= ~_hoops_RHPRI;
	pool->_hoops_RHAGR._hoops_IRPGR();
}

#else

INLINE bool _hoops_ISPRI(Memory_Pool const * pool)
{
	if (BIT (pool->flags, MPF_LOCKING) &&
		BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP)) {
		LOCK_MUTEX (pool->_hoops_RASCA);
		ASSERT(!BIT(pool->flags, _hoops_RHPRI));
		_hoops_PGRCA(pool)->flags |= _hoops_RHPRI;
		return true;
	}
	return false;
}

INLINE void _hoops_CSPRI(Memory_Pool const * pool)
{
	ASSERT(BIT(pool->flags, _hoops_RHPRI));
	_hoops_PGRCA(pool)->flags &= ~_hoops_RHPRI;
	UNLOCK_MUTEX (pool->_hoops_RASCA);
}

#endif


#define GLOB_HEADER_TO_FREE_LIST(g) ((_hoops_CGPRI*)(((char*)g)+GLOB_HEADER_SIZE))
#define _hoops_SSPRI(p) ((_hoops_SGPRI *)(((char*)p)-GLOB_HEADER_SIZE))


#ifdef VALIDATE_MEMORY

#ifdef _hoops_GGHRI
#undef _hoops_PSARI
local void _hoops_PSARI(Memory_Pool * pool)
{
	bool _hoops_PCGS = _hoops_ISPRI(pool);

	_hoops_AIARI *	_hoops_PSPRI = null;

	for (long _hoops_GIARA = 0; _hoops_GIARA < QUICK_MEM_SLOTS; _hoops_GIARA++) {
		for (int j = 0; j < 4; j++) {
			switch (j) {
				case 0:		_hoops_PSPRI = pool->_hoops_GIPRI[_hoops_GIARA]._hoops_SAPRI;				break;
				case 1:		_hoops_PSPRI = pool->_hoops_GIPRI[_hoops_GIARA]._hoops_GPPRI;			break;
				case 2:		_hoops_PSPRI = pool->_hoops_GIPRI[_hoops_GIARA]._hoops_RPPRI;			break;
				case 3:		_hoops_PSPRI = pool->_hoops_GIPRI[_hoops_GIARA]._hoops_APPRI;			break;
			}

			while (_hoops_PSPRI != null) {
				switch (j) {
					case 0: {
						if (_hoops_PSPRI->glob_count == 0 || _hoops_PSPRI->glob_count > (unsigned int)_hoops_PSPRI->_hoops_HRPRI)
							_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Memory block count bad.");
					}	break;
					case 1: {
						if (_hoops_PSPRI->glob_count == 0 || _hoops_PSPRI->glob_count >= (unsigned int)_hoops_PSPRI->_hoops_HRPRI)
							_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Memory block count bad.");
					}	 break;
					case 2: {
						if (_hoops_PSPRI->glob_count >= (unsigned int)(_hoops_PSPRI->_hoops_HRPRI>>2)+1)
							_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Memory block count bad.");
					}	break;
					case 3: {
						if (_hoops_PSPRI->glob_count != (unsigned int)_hoops_PSPRI->_hoops_HRPRI)
							_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Memory block count bad.");
					}	break;
				}

				_hoops_CGPRI *		_hoops_PSRGA = _hoops_PSPRI->globs;

				while (_hoops_PSRGA) {
					_hoops_SGPRI *	_hoops_ASPRI = _hoops_SSPRI(_hoops_PSRGA);
					long			size = QUICK_MEM_SLOT_SIZE(_hoops_GIARA);

					if (_hoops_ASPRI->_hoops_RRPRI != _hoops_CCPRI)
						_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Quick memory glob bad.");
					if (_hoops_ASPRI->size != size)
						_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Size of quick memory glob bad.");

					_hoops_PSRGA = _hoops_PSRGA->next;
				}

				_hoops_PSPRI = _hoops_PSPRI->_hoops_ARPRI;
			}
		}
	}

	if (_hoops_PCGS)
		_hoops_CSPRI(pool);
}
#endif


local FILE *	_hoops_RGHRI = NULL;
local long		_hoops_AGHRI = 0;
local long		_hoops_PGHRI = 0;
local char		_hoops_HGHRI[4096];

#ifdef WINDOWS_SYSTEM
#	include <direct.h>
#	define getcwd _getcwd
#else
#	include <unistd.h>
#endif

local _hoops_GHRIR				global_alloc_id = 0;
local char const * const	_hoops_IGHRI = "Unknown (no VALIDATE_MEMORY?)";

local void _hoops_CGHRI (
	void *			p,
	size_t			size,
	bool			alloc,
	const char *	type_name,
	const char *	_hoops_SGHRI,
	int				line)
{

	ASSERT(p != null);
	ASSERT(size > 0);
	ASSERT(!BIT(HOOPS_WORLD->system_flags, Sysop_RAW_MEMORY));

	_hoops_CGPRI *		_hoops_PSRGA = (_hoops_CGPRI *)p;
	_hoops_SGPRI *	_hoops_ASPRI = _hoops_SSPRI(_hoops_PSRGA);
	_hoops_AIARI *	_hoops_PSPRI = _hoops_ASPRI->_hoops_GRPRI;
	Memory_Pool *	pool = _hoops_PSPRI->pool;

	ASSERT(pool != null);

	// _hoops_CCPH _hoops_IHH _hoops_CRAA _hoops_PIH
	char _hoops_GRHRI[4096];
	const char * file = _hoops_SGHRI;

	if (file != null) {
		size_t x = _hoops_SSGR(_hoops_SGHRI);
		size_t l = x;

		while (_hoops_SGHRI[x] != '/' && _hoops_SGHRI[x] != '\\') {
			if (x == 0)
				break;
			x--;
		}

		if (x > 0) {
			x++;
			_hoops_AIGA(&_hoops_SGHRI[x], l-x+1, char, _hoops_GRHRI);
			file = _hoops_GRHRI;
		}
	}
	else
		file = _hoops_IGHRI;

	if (alloc) {
		if (type_name != null)
			_hoops_ASPRI->type_name = type_name;
		else
			_hoops_ASPRI->type_name = _hoops_IGHRI;

		_hoops_CIAGP (&global_alloc_id);
	}
	else
		type_name = _hoops_ASPRI->type_name;

	bool _hoops_PCGS = _hoops_ISPRI(pool);

	if (BIT (HOOPS_WORLD->_hoops_IRARR, _hoops_GRHGI)) {
		if (_hoops_RGHRI == NULL) {
			if (_hoops_AGHRI == 0)
				getcwd(_hoops_HGHRI,4096);

			char _hoops_RRHRI[4096];
			sprintf(_hoops_RRHRI, "%s%cmemory_log_%ld.txt", _hoops_HGHRI, PATH_DELIMITER, _hoops_AGHRI);
			_hoops_RGHRI= fopen(_hoops_RRHRI,"wb");
			ASSERT(_hoops_RGHRI != NULL);
		}

		_hoops_PGHRI++;

		// _hoops_HAIHR _hoops_RPP _hoops_RHAC _hoops_HHGC _hoops_ARHRI _hoops_PAR _hoops_CRS _hoops_PRHRI...
		void * _hoops_HRHRI = p;
		//_hoops_SRPC * _hoops_IRHRI = (_hoops_SRPC*)_hoops_ARHRI;

		fprintf(_hoops_RGHRI, "%c %8d %p %s %s:%d\n", alloc?'+':'-', (int)size, _hoops_HRHRI, type_name, file, line);

		if (_hoops_PGHRI > 0x000FFFFF) {
			_hoops_PGHRI = 0;
			_hoops_AGHRI++;
			fclose(_hoops_RGHRI);
			_hoops_RGHRI = NULL;
		}
	}

	if (BIT (HOOPS_WORLD->_hoops_IRARR, _hoops_RRHGI)) {
		if (pool->_hoops_ACPRI) {
			size_t		_hoops_CRHRI = pool->_hoops_ACPRI->Lookup(type_name);

			if (alloc)
				_hoops_CRHRI += size;
			else
				_hoops_CRHRI -= size;

			pool->_hoops_ACPRI->ReplaceItem(type_name, _hoops_CRHRI);

#ifdef _hoops_ISARI
			char _hoops_ICAGA[1024];
			size_t		x = strlen(file);

			while (x > 0 && file[x] != PATH_DELIMITER)
				--x;
			sprintf(_hoops_ICAGA, "#%s %s:%d", type_name, &file[x+1], line);

			_hoops_CRHRI = pool->_hoops_ACPRI->Lookup(_hoops_ICAGA);

			if (alloc)
				_hoops_CRHRI += size;
			else
				_hoops_CRHRI -= size;

			pool->_hoops_ACPRI->ReplaceItem(_hoops_ICAGA, _hoops_CRHRI);
#endif
		}

		if (pool->_hoops_PCPRI) {
			if (alloc) {
				_hoops_CSARI *	_hoops_SRHRI = SYSTEM_NEW(_hoops_CSARI)(pool, type_name, file, line, size, global_alloc_id);
				pool->_hoops_PCPRI->InsertItem (p, _hoops_SRHRI);
			}
			else {
				_hoops_CSARI *	_hoops_SRHRI;
				vhash_status_t status = pool->_hoops_PCPRI->RemoveItem(p, &_hoops_SRHRI);
				if (status == VHASH_STATUS_SUCCESS)
					delete _hoops_SRHRI;
			}
		}
	}

	char *		remainder = (char *)_hoops_ASPRI + sizeof(_hoops_SGPRI);
	long		_hoops_GAHRI = _hoops_GIARI(size);
	size_t		_hoops_HSPRI = size + GLOB_HEADER_SIZE - sizeof(_hoops_SGPRI) + GLOB_FOOTER_SIZE;

	if (alloc) {
		if (_hoops_ASPRI->_hoops_RRPRI != _hoops_CCPRI)
			_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
									Sprintf_SD (null, "Alloc: Memory glob bad in %s at line %d", file, line));
		else if (_hoops_ASPRI->size != _hoops_GAHRI)
			_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
									Sprintf_SD (null, "Alloc: Size of memory glob bad in %s at line %d", file, line));

		while (_hoops_HSPRI-- > 0) {
			if (*remainder++ != _hoops_GSPRI) {
				_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
										Sprintf_SD (null, "Alloc: Memory glob damaged in %s at line %d", file, line));
				break;
			}
		}
		_hoops_ASPRI->_hoops_RRPRI = _hoops_SCPRI;
	}
	else {
		if (_hoops_ASPRI->_hoops_RRPRI == _hoops_CCPRI)
			_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
									Sprintf_SD (null, "Free: Memory double free in %s at line %d", file, line));
		else if (_hoops_ASPRI->_hoops_RRPRI != _hoops_SCPRI)
			_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
									Sprintf_SD (null, "Free: Memory glob bad in %s at line %d", file, line));
		else if (_hoops_ASPRI->size != _hoops_GAHRI)
			_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
									Sprintf_SD (null, "Free: Size of memory glob bad in %s at line %d", file, line));
		else if (remainder[_hoops_HSPRI - GLOB_FOOTER_SIZE] != _hoops_GSPRI)
			_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
									Sprintf_SD (null, "Free: damage detected after memory block in %s at line %d", file, line));

		char * ptr = (char *)_hoops_ASPRI + sizeof(_hoops_SGPRI);
		char * end = (char *)_hoops_ASPRI + GLOB_HEADER_SIZE;
		while (ptr < end) {
			if (*ptr++ != _hoops_GSPRI) {
				_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
										Sprintf_SD (null, "Free: damage detected before memory block in %s at line %d", file, line));
				break;
			}
		}
		_hoops_RSPRI (_hoops_ASPRI, _hoops_GAHRI, _hoops_PSPRI);
	}


	if (_hoops_PCGS)
		_hoops_CSPRI(pool);
}

local void _hoops_RAHRI (_hoops_CSARI *_hoops_SRHRI, const void *p, const void *const user_data) {
	FILE *		fp = (FILE *)user_data;
	fprintf (fp, "alloc id:%d\n\taddr:%p\n\tpool:%p\n\ttype:%s\n\tfile:%s\n\tline:%d\n\tcount:%d\n",
			 _hoops_SRHRI->_hoops_SSARI, p, _hoops_SRHRI->pool, _hoops_SRHRI->type, _hoops_SRHRI->file, _hoops_SRHRI->line, (int)_hoops_SRHRI->count);
}

GLOBAL_FUNCTION void HI_Dump_Allocation_Metadata (Memory_Pool *pool, const char * message)
{
	if (pool->_hoops_PCPRI == null ||
		pool->_hoops_PCPRI->Count() == 0)
		return;

	char	filename[4096];
	int		time = (int)(*HOOPS_WORLD->time_stamp);
	sprintf (filename, "allocation_metadata_%d.txt", time);

	FILE *	fp = fopen(filename,"wb");
	if (!fp) {
		HE_WARNING (HEC_HOOPS_SYSTEM, HES_MEMORY_USAGE, "Failed during creation of allocation metadata dump file.");
		return;
	}
	fprintf (fp, "%s\n", message);
	pool->_hoops_PCPRI->MapFunction (_hoops_RAHRI, fp);
	fclose (fp);
}


#else

GLOBAL_FUNCTION void HI_Dump_Allocation_Metadata (Memory_Pool *pool, const char * message)
{
	UNREFERENCED(pool);
	UNREFERENCED(message);
}

#endif


INLINE void _hoops_AAHRI (Memory_Pool * pool, _hoops_AIARI * _hoops_PSPRI)
{
	HOOPS_WORLD->_hoops_CCRGH++;
	(*pool->free) ((void*)_hoops_PSPRI);
}

local void _hoops_PAHRI (
	_hoops_AIARI *	_hoops_PSPRI,
	Memory_Pool *	pool,
	bool			_hoops_HAHRI,
	size_t			glob_size)
{
	_hoops_SSAGR(_hoops_PSPRI);

	bool	_hoops_PCGS = false;
	if (_hoops_HAHRI)
		_hoops_PCGS = _hoops_ISPRI(pool);

	if ((*_hoops_PSPRI->backlink = _hoops_PSPRI->next) != null)
		_hoops_PSPRI->next->backlink = _hoops_PSPRI->backlink;

	pool->_hoops_HHPRI -= glob_size;

	if (_hoops_PSPRI->size > _hoops_GAPRI ||
		HOOPS_WORLD->memory_pool->_hoops_HIPRI == null) {

		pool->_hoops_GCPRI -= _hoops_PSPRI->size;

		if (_hoops_PCGS)
			_hoops_CSPRI(pool);

		_hoops_AAHRI (pool, _hoops_PSPRI);
		return;
	}

	if (pool != HOOPS_WORLD->memory_pool) {
		pool->_hoops_GCPRI -= _hoops_PSPRI->size;
		pool = HOOPS_WORLD->memory_pool;
		_hoops_PCGS = _hoops_ISPRI(pool);
		pool->_hoops_GCPRI += _hoops_PSPRI->size;
	}

	for (int i=0; i<_hoops_SRPRI; ++i) {
		if (_hoops_PSPRI->size <= _hoops_RAPRI[i]) {
			// _hoops_HSRPA _hoops_CIAA _hoops_RHGPA _hoops_HIGR
			if (pool->_hoops_HIPRI->_hoops_IAPRI[i] == null)
				pool->_hoops_HIPRI->_hoops_IAPRI[i] = _hoops_PSPRI;

			if ((_hoops_PSPRI->next = pool->_hoops_HIPRI->_hoops_HAPRI[i]) != null) {
				pool->_hoops_HIPRI->_hoops_HAPRI[i]->backlink = &_hoops_PSPRI->next;

				// _hoops_GHGPR _hoops_CCHHR _hoops_HIGR
				_hoops_PSPRI->next->_hoops_ARPRI = _hoops_PSPRI;
			}

			_hoops_PSPRI->backlink = &pool->_hoops_HIPRI->_hoops_HAPRI[i];
			_hoops_PSPRI->_hoops_ARPRI = null;

			pool->_hoops_HIPRI->_hoops_HAPRI[i] = _hoops_PSPRI;
			pool->_hoops_HIPRI->_hoops_CAPRI[i] += _hoops_PSPRI->size;

			if (pool->_hoops_HIPRI->_hoops_CAPRI[i] > _hoops_AAPRI[i]) {
				// _hoops_PPRI _hoops_GGSR _hoops_IAHRI _hoops_CIPH _hoops_SIACP _hoops_ISSC _hoops_HII _hoops_RH _hoops_CAHRI
				while (pool->_hoops_HIPRI->_hoops_CAPRI[i] > _hoops_AAPRI[i]>>1) {
					_hoops_PSPRI = pool->_hoops_HIPRI->_hoops_IAPRI[i];

					ASSERT(_hoops_PSPRI->next == null);

					pool->_hoops_HIPRI->_hoops_CAPRI[i] -= _hoops_PSPRI->size;

					if ((pool->_hoops_HIPRI->_hoops_IAPRI[i] = _hoops_PSPRI->_hoops_ARPRI) != null) {
						_hoops_PSPRI->_hoops_ARPRI->next = null;
						_hoops_PSPRI->_hoops_ARPRI = null;
					}

					if ((*_hoops_PSPRI->backlink = _hoops_PSPRI->next) != null)
						_hoops_PSPRI->next->backlink = _hoops_PSPRI->backlink;

					if (pool->_hoops_IHPRI != null) {
						// _hoops_HSRPA _hoops_CIAA _hoops_CIH _hoops_HIGR _hoops_RPP _hoops_GRP _hoops_AISSA
						if ((_hoops_PSPRI->next = pool->_hoops_SHPRI) != null)
							pool->_hoops_SHPRI->backlink = &_hoops_PSPRI->next;
						_hoops_PSPRI->backlink = &pool->_hoops_SHPRI;
						pool->_hoops_SHPRI = _hoops_PSPRI;
						pool->_hoops_RCPRI += _hoops_PSPRI->size;
					}
					else {
						pool->_hoops_GCPRI -= _hoops_PSPRI->size;
						_hoops_AAHRI (pool, _hoops_PSPRI);
					}
				}
			}

			break;
		}
	}

	if (_hoops_PCGS)
		_hoops_CSPRI(pool);
}

local void * _hoops_SAHRI (
	size_t			size,
	bool			_hoops_GPHRI,
	Memory_Pool *	pool)
{
	bool			_hoops_RPHRI = true;

_hoops_APHRI:

	void *	mem = (*pool->malloc)((size_t)size);

	if (mem == null) {
		if (_hoops_RPHRI) {
			bool _hoops_HAHRI = BIT(pool->flags, _hoops_RHPRI);

			// _hoops_CGP _hoops_SR _hoops_CRCC _hoops_IRS _hoops_AAHS _hoops_SR _hoops_PIHA _hoops_SSIAA _hoops_ARPP _hoops_RCPH _hoops_PPHRI
			if (_hoops_HAHRI)
				_hoops_CSPRI(pool);

			/* _hoops_CACH _hoops_RPP "_hoops_PHARA" _hoops_GRS _hoops_IRHH _hoops_IRS _hoops_RIS _hoops_SR _hoops_PAH _hoops_HGCR */
			HI_Relinquish_Memory ();

			if (_hoops_HAHRI)
				_hoops_ISPRI(pool);

			if (!_hoops_GPHRI)
				HE_WARNING (HEC_MEMORY, HES_OUT_OF_MEMORY, "Memory running out");

			_hoops_RPHRI = false;
			goto _hoops_APHRI;
		}

		if (_hoops_GPHRI)
			return null;
		else
			_hoops_HRAIR (HEC_MEMORY, HES_OUT_OF_MEMORY, "No more memory available");
	}

#ifdef _hoops_HPHRI
	{
		char	*_hoops_IPHRI = (char *)mem;
		do
			*_hoops_IPHRI++ = size;		/* _hoops_CISA _hoops_CCA "_hoops_PISA" _hoops_RGGHR */
		_hoops_RGGA (--size == 0);
	}
#endif

	return mem;
}


#define _hoops_CPHRI(_hoops_SPHRI) ((void *)(((char *)(_hoops_SPHRI)) + _hoops_RIARI + GLOB_HEADER_SIZE))
#define _hoops_GHHRI(_hoops_SPHRI) ((_hoops_SGPRI *)(((char *)(_hoops_SPHRI)) + _hoops_RIARI))


INLINE void _hoops_RHHRI(
	_hoops_AIARI *	_hoops_PSPRI,
	Memory_Pool *	pool,
	size_t			_hoops_GAHRI,
	size_t			_hoops_AHHRI,
	size_t			glob_size,
	bool			_hoops_PHHRI)
{

	ZERO_STRUCT(_hoops_PSPRI, _hoops_AIARI);

	_hoops_PSPRI->pool = pool;
	_hoops_PSPRI->size = _hoops_GAHRI;
	_hoops_PSPRI->_hoops_GIARA = -1;
	_hoops_PSPRI->_hoops_HRPRI = -1;

	if (!_hoops_PHHRI)
		_hoops_RSPRI (_hoops_GHHRI(_hoops_PSPRI), _hoops_GIARI(_hoops_AHHRI), _hoops_PSPRI);

	if ((_hoops_PSPRI->next = pool->_hoops_CHPRI) != null)
		_hoops_PSPRI->next->backlink = &_hoops_PSPRI->next;
	_hoops_PSPRI->backlink = &pool->_hoops_CHPRI;
	pool->_hoops_CHPRI = _hoops_PSPRI;

	pool->_hoops_HHPRI += glob_size;
}

local _hoops_AIARI * _hoops_HHHRI (
	size_t			_hoops_CPAH,
	bool			_hoops_GPHRI,
	Memory_Pool *	_hoops_IHHRI,
	bool			_hoops_HAHRI,
	size_t			glob_size,
	bool			_hoops_PHHRI)
{
	size_t			size = _hoops_GIARI(_hoops_CPAH) + _hoops_RIARI;	/* _hoops_GIRR _hoops_GH; _hoops_GGCR _hoops_RGSPR */

	if (!_hoops_PHHRI)
		size += GLOB_HEADER_SIZE + GLOB_FOOTER_SIZE;

	_hoops_AIARI *	_hoops_PSPRI = null;

	bool _hoops_PCGS = false;

	if (size <= _hoops_GAPRI &&
		HOOPS_WORLD->memory_pool->_hoops_HIPRI) {

		Memory_Pool *	pool = HOOPS_WORLD->memory_pool;

		// _hoops_GHGC _hoops_IRS _hoops_IHSH
		if (_hoops_IHHRI != HOOPS_WORLD->memory_pool || _hoops_HAHRI)
			_hoops_PCGS = _hoops_ISPRI(pool);

		for (int i=0; i<_hoops_SRPRI; ++i) {
			if (size <= _hoops_RAPRI[i]) {
				if ((_hoops_PSPRI = pool->_hoops_HIPRI->_hoops_HAPRI[i]) == null)
					break;

				while (_hoops_PSPRI != null && size != _hoops_PSPRI->size)
					_hoops_PSPRI = _hoops_PSPRI->next;

				if (_hoops_PSPRI != null) {
					if (_hoops_PSPRI == pool->_hoops_HIPRI->_hoops_IAPRI[i])
						pool->_hoops_HIPRI->_hoops_IAPRI[i] = _hoops_PSPRI->_hoops_ARPRI;

					if ((*_hoops_PSPRI->backlink = _hoops_PSPRI->next) != null) {
						_hoops_PSPRI->next->backlink = _hoops_PSPRI->backlink;
						_hoops_PSPRI->next->_hoops_ARPRI = _hoops_PSPRI->_hoops_ARPRI;
					}

					pool->_hoops_HIPRI->_hoops_CAPRI[i] -= _hoops_PSPRI->size;



					bool _hoops_CHHRI = false;
					if (pool != _hoops_IHHRI) {
						pool->_hoops_GCPRI -= _hoops_PSPRI->size;

						if (_hoops_PCGS) {
							_hoops_CSPRI(pool);
							_hoops_PCGS = false;
						}

						if (_hoops_HAHRI)
							_hoops_CHHRI = _hoops_ISPRI(_hoops_IHHRI);

						_hoops_IHHRI->_hoops_GCPRI += _hoops_PSPRI->size;
					}

					_hoops_RHHRI(_hoops_PSPRI, _hoops_IHHRI, size, _hoops_CPAH, glob_size, _hoops_PHHRI);

					if (_hoops_CHHRI)
						_hoops_CSPRI(_hoops_IHHRI);

					HOOPS_WORLD->_hoops_SCRGH++;
				}

				break;
			}
		}

		if (_hoops_PSPRI) {
			if (_hoops_PCGS)
				_hoops_CSPRI(pool);

			return _hoops_PSPRI;
		}

		if (pool != _hoops_IHHRI) {
			if (_hoops_PCGS) {
				_hoops_CSPRI(pool);
				_hoops_PCGS = false;
			}
		}
	}

	if ((_hoops_PSPRI = (_hoops_AIARI *)_hoops_SAHRI (size, _hoops_GPHRI, _hoops_IHHRI)) == null)
		return null;

	HOOPS_WORLD->_hoops_GSRGH++;

	if (_hoops_HAHRI && !_hoops_PCGS)
		_hoops_PCGS = _hoops_ISPRI(_hoops_IHHRI);

	_hoops_RHHRI(_hoops_PSPRI, _hoops_IHHRI, size, _hoops_CPAH, glob_size, _hoops_PHHRI);

	_hoops_IHHRI->_hoops_GCPRI += _hoops_PSPRI->size;

	if (_hoops_PCGS)
		_hoops_CSPRI(_hoops_IHHRI);

#ifdef _hoops_HPHRI
	printf ("Allocated %ld at %ld\n", (long)size, (long)_hoops_PSPRI + _hoops_RIARI);
#endif

	return _hoops_PSPRI;
}


local _hoops_AIARI * _hoops_SHHRI (
	short			_hoops_GIARA,
	Memory_Pool *	pool)
{
	_hoops_AIARI *	_hoops_PSPRI = null;
	int 			_hoops_GAHRI = ((_hoops_GIARA+1)<<ALIGNMENT);
	int 			glob_size = _hoops_GAHRI + GLOB_HEADER_SIZE + GLOB_FOOTER_SIZE;
	int 			glob_count = QUICK_MEM_MAX_BLOCK_SIZE/glob_size;

	if (pool->_hoops_GIPRI[_hoops_GIARA]._hoops_GPPRI) {
		_hoops_PSPRI = pool->_hoops_GIPRI[_hoops_GIARA]._hoops_GPPRI;
		if (_hoops_PSPRI->_hoops_ARPRI)
			_hoops_PSPRI->_hoops_ARPRI->_hoops_PRPRI = &pool->_hoops_GIPRI[_hoops_GIARA]._hoops_GPPRI;
		pool->_hoops_GIPRI[_hoops_GIARA]._hoops_GPPRI = _hoops_PSPRI->_hoops_ARPRI;
	}
	else if (pool->_hoops_GIPRI[_hoops_GIARA]._hoops_APPRI) {
		_hoops_PSPRI = pool->_hoops_GIPRI[_hoops_GIARA]._hoops_APPRI;
		if (_hoops_PSPRI->_hoops_ARPRI)
			_hoops_PSPRI->_hoops_ARPRI->_hoops_PRPRI = &pool->_hoops_GIPRI[_hoops_GIARA]._hoops_APPRI;
		pool->_hoops_GIPRI[_hoops_GIARA]._hoops_APPRI = _hoops_PSPRI->_hoops_ARPRI;
		pool->_hoops_IIPRI -= QUICK_MEM_MAX_BLOCK_SIZE;
	}
	else {
		if (pool->_hoops_IIPRI > 0) {
			long		_hoops_GIHRI = QUICK_MEM_SLOTS-1;

			do {
				if (pool->_hoops_GIPRI[_hoops_GIHRI]._hoops_APPRI) {
					HOOPS_WORLD->_hoops_SCRGH++;

					_hoops_PSPRI = pool->_hoops_GIPRI[_hoops_GIHRI]._hoops_APPRI;
					if (_hoops_PSPRI->_hoops_ARPRI)
						_hoops_PSPRI->_hoops_ARPRI->_hoops_PRPRI = &pool->_hoops_GIPRI[_hoops_GIHRI]._hoops_APPRI;
					pool->_hoops_GIPRI[_hoops_GIHRI]._hoops_APPRI = _hoops_PSPRI->_hoops_ARPRI;
					pool->_hoops_IIPRI -= QUICK_MEM_MAX_BLOCK_SIZE;
					break;
				}
			} while (--_hoops_GIHRI >= 0);

			ASSERT(_hoops_PSPRI != null);
		}
		else {
			long		alloc = QUICK_MEM_BLOCK_SIZE-_hoops_RIARI;
			_hoops_PSPRI = _hoops_HHHRI (alloc, false, pool, false, 0, true);
		}

		_hoops_PSPRI->glob_count = glob_count;
		_hoops_PSPRI->_hoops_HRPRI = glob_count;

		_hoops_SGPRI *	_hoops_ASPRI = _hoops_GHHRI(_hoops_PSPRI);

		_hoops_PSPRI->globs = GLOB_HEADER_TO_FREE_LIST(_hoops_ASPRI);

		while (1) {
			_hoops_RSPRI (_hoops_ASPRI, _hoops_GAHRI, _hoops_PSPRI);
			if (--glob_count == 0)
				break;
			_hoops_SGPRI *	next = (_hoops_SGPRI *)((char*)_hoops_ASPRI + glob_size);
			GLOB_HEADER_TO_FREE_LIST(_hoops_ASPRI)->next = GLOB_HEADER_TO_FREE_LIST(next);
			_hoops_ASPRI = next;
		}
		GLOB_HEADER_TO_FREE_LIST(_hoops_ASPRI)->next = null;
	}

	_hoops_PSPRI->_hoops_PRPRI = null;
	_hoops_PSPRI->_hoops_ARPRI = null;
	_hoops_PSPRI->_hoops_GIARA = _hoops_GIARA;

#ifdef VALIDATE_MEMORY
	if (pool->_hoops_GIPRI[_hoops_GIARA]._hoops_SAPRI) {
		_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Don't need a free block???");
	}
#endif

	pool->_hoops_GIPRI[_hoops_PSPRI->_hoops_GIARA]._hoops_SAPRI = _hoops_PSPRI;

	return _hoops_PSPRI;
}

GLOBAL_FUNCTION void * HI_Alloc_Array(
	size_t				size,
	bool				try_alloc,
	bool				cache_big_blocks,
	Memory_Pool alter *	pool,
	const char *		type_name,
	const char *		file,
	int					line)
{
	if (size == 0) {
#ifdef VALIDATE_MEMORY
		_hoops_IPR (_hoops_RISSH, _hoops_AISSH,
			Sprintf_SD (null, "Attempted alloc of size 0 in %s line %d", file, line));
#else
		UNREFERENCED(type_name);
		UNREFERENCED(file);
		UNREFERENCED(line);
#endif
		return 0;
	}

	_hoops_SSAGR(pool);
	void *				p = null;
	_hoops_AIARI *		_hoops_PSPRI;

	if (size <= QUICK_MEM_MAX_BYTES) {
		_hoops_CGPRI *		_hoops_PSRGA;
		long			_hoops_GIARA = QUICK_MEM_SLOT(size);
		_hoops_SSAGR(&pool->_hoops_GIPRI[_hoops_GIARA]);

		_hoops_AIARI **	_hoops_RIHRI = &pool->_hoops_GIPRI[_hoops_GIARA]._hoops_SAPRI;
		_hoops_SSAGR(_hoops_RIHRI);

		bool			_hoops_PCGS = _hoops_ISPRI(pool);

		pool->_hoops_HHPRI += QUICK_MEM_SLOT_SIZE(_hoops_GIARA);

		if ((_hoops_PSPRI = *_hoops_RIHRI) == null) {
			_hoops_PSPRI = _hoops_SHHRI (_hoops_GIARA, pool);
		}
		if (_hoops_PSPRI) {
			--_hoops_PSPRI->glob_count;
			_hoops_PSRGA = _hoops_PSPRI->globs;
			if ((_hoops_PSPRI->globs = _hoops_PSRGA->next) == null) {
				// _hoops_IHIS _hoops_IS _hoops_RHPA _hoops_HIGR
				ASSERT (_hoops_PSPRI->glob_count == 0);
				*_hoops_RIHRI = null;
				if ((_hoops_PSPRI->_hoops_ARPRI = pool->_hoops_GIPRI[_hoops_GIARA]._hoops_RPPRI) != null)
					_hoops_PSPRI->_hoops_ARPRI->_hoops_PRPRI = &_hoops_PSPRI->_hoops_ARPRI;
				_hoops_PSPRI->_hoops_PRPRI = &pool->_hoops_GIPRI[_hoops_GIARA]._hoops_RPPRI;
				pool->_hoops_GIPRI[_hoops_GIARA]._hoops_RPPRI = _hoops_PSPRI;
			}

			p = _hoops_PSRGA;

#ifdef VALIDATE_MEMORY
			SET_MEMORY(p, sizeof(_hoops_CGPRI*), _hoops_GSPRI);
#endif
		}

		if (_hoops_PCGS)
			_hoops_CSPRI(pool);

		_hoops_PSARI(pool);
	}
	else if (cache_big_blocks) {
		_hoops_PSPRI = null;

		if (size <= _hoops_SIARI) {
			if (pool->_hoops_RIPRI == null) {
				pool = HOOPS_WORLD->memory_pool;
				_hoops_SSAGR(pool);
			}

			bool	_hoops_PCGS = _hoops_ISPRI(pool);

			long	_hoops_GIARA = _hoops_GCARI(size);
			long	_hoops_AIHRI = _hoops_GIARA;

			while (_hoops_GIARA < _hoops_RCARI) {
				_hoops_PPPRI *	_hoops_PIHRI = &pool->_hoops_RIPRI[_hoops_GIARA];

				if ((_hoops_PSPRI = _hoops_PIHRI->_hoops_HAPRI) != null) {
					_hoops_PIHRI->_hoops_HAPRI = _hoops_PSPRI->_hoops_ARPRI;
					_hoops_PIHRI->_hoops_HPPRI--;
					_hoops_PSPRI->_hoops_ARPRI = null;//_hoops_HISRA
					pool->_hoops_CIPRI -= _hoops_PSPRI->size;
				}
				else if (_hoops_PIHRI->_hoops_IPPRI < _hoops_IRPRI[_hoops_GIARA]) {
					size_t	_hoops_HIHRI = (_hoops_GIARA+1)*_hoops_IIARI;
					_hoops_PSPRI = _hoops_HHHRI(_hoops_HIHRI, try_alloc, pool, false, 0, false);
					_hoops_PSPRI->_hoops_GIARA = _hoops_GIARA;
				}

				if (_hoops_PSPRI) {
					_hoops_PIHRI->_hoops_IPPRI++;
					break;
				}

				_hoops_GIARA++;

				if (_hoops_GIARA > _hoops_AIHRI + 16)
					break;
			}

			if (_hoops_PSPRI) {
				pool->_hoops_HHPRI += size;
				_hoops_PSPRI->glob_count = (unsigned int)_hoops_GIARI(size); // _hoops_HPGGR _hoops_RGR _hoops_GAR _hoops_IRS _hoops_IHAH _hoops_AHSC _hoops_RIS
				p = _hoops_CPHRI(_hoops_PSPRI);
				_hoops_RSPRI (_hoops_SSPRI(p), _hoops_GIARI(size), _hoops_PSPRI);
			}
			else {
				HOOPS_WORLD->_hoops_ICRGH++;
				//_hoops_ICGAR->_hoops_IIHRI+=_hoops_IGIR; _hoops_CPHR _hoops_GGR _hoops_CIHRI
				_hoops_PSPRI = _hoops_HHHRI(size, try_alloc, pool, false, size, false);
				if (_hoops_PSPRI)
					p = _hoops_CPHRI(_hoops_PSPRI);
			}

			if (_hoops_PCGS)
				_hoops_CSPRI(pool);
		}
		else {
			if (pool->_hoops_AIPRI == null) {
				pool = HOOPS_WORLD->memory_pool;
				_hoops_SSAGR(pool);
			}

			bool	_hoops_PCGS = _hoops_ISPRI(pool);

			if (size <= _hoops_ICARI) {
				long	_hoops_GIARA = _hoops_CCARI(size);
				long	_hoops_AIHRI = _hoops_GIARA;

				while (_hoops_GIARA < _hoops_SCARI) {
					_hoops_CPPRI *	_hoops_SIHRI = &pool->_hoops_AIPRI[_hoops_GIARA];

					_hoops_SIHRI->_hoops_SPPRI = *HOOPS_WORLD->time_stamp;

					if ((_hoops_PSPRI = _hoops_SIHRI->_hoops_HAPRI) != null) {
						_hoops_SIHRI->_hoops_HAPRI = _hoops_PSPRI->_hoops_ARPRI;
						_hoops_SIHRI->_hoops_HPPRI--;
						_hoops_PSPRI->_hoops_ARPRI = null;//_hoops_HISRA
						pool->_hoops_SIPRI -= _hoops_PSPRI->size;
					}
					else if (_hoops_SIHRI->_hoops_IPPRI < _hoops_CRPRI[_hoops_GIARA]) {
						size_t	_hoops_HIHRI = (_hoops_GIARA+1)*_hoops_PCARI;
						_hoops_PSPRI = _hoops_HHHRI(_hoops_HIHRI, try_alloc, pool, false, 0, false);
						_hoops_PSPRI->_hoops_GIARA = _hoops_GIARA;
					}

					if (_hoops_PSPRI) {
						_hoops_SIHRI->_hoops_IPPRI++;
						break;
					}

					_hoops_GIARA++;

					if (_hoops_GIARA > _hoops_AIHRI + 8)
						break;
				}

				if (_hoops_PSPRI) {
					pool->_hoops_HHPRI += size;
					_hoops_PSPRI->glob_count = (unsigned int)_hoops_GIARI(size); // _hoops_HPGGR _hoops_RGR _hoops_GAR _hoops_IRS _hoops_IHAH _hoops_AHSC _hoops_RIS
					p = _hoops_CPHRI(_hoops_PSPRI);
					_hoops_RSPRI (_hoops_SSPRI(p), _hoops_GIARI(size), _hoops_PSPRI);
				}
			}
			else if (size <= _hoops_GSARI) {
				 // _hoops_RGAR _hoops_SPR
				_hoops_CPPRI *	_hoops_SIHRI = &pool->_hoops_PIPRI[0];

				_hoops_SIHRI->_hoops_SPPRI = *HOOPS_WORLD->time_stamp;

				if ((_hoops_PSPRI = _hoops_SIHRI->_hoops_HAPRI) != null) {
					_hoops_SIHRI->_hoops_HAPRI = _hoops_PSPRI->_hoops_ARPRI;
					_hoops_SIHRI->_hoops_HPPRI--;
					_hoops_PSPRI->_hoops_ARPRI = null;//_hoops_HISRA
					pool->_hoops_SIPRI -= _hoops_PSPRI->size;
				}
				else if (_hoops_SIHRI->_hoops_IPPRI < _hoops_ASARI) {
					_hoops_PSPRI = _hoops_HHHRI(_hoops_GSARI, try_alloc, pool, false, 0, false);
				}

				if (_hoops_PSPRI) {
					pool->_hoops_HHPRI += size;
					_hoops_PSPRI->glob_count = (unsigned int)_hoops_GIARI(size); // _hoops_HPGGR _hoops_RGR _hoops_GAR _hoops_IRS _hoops_IHAH _hoops_AHSC _hoops_RIS
					p = _hoops_CPHRI(_hoops_PSPRI);
					_hoops_RSPRI (_hoops_SSPRI(p), _hoops_GIARI(size), _hoops_PSPRI);
					_hoops_SIHRI->_hoops_IPPRI++;
				}
			}

			if (_hoops_PSPRI == null) {
				HOOPS_WORLD->_hoops_ICRGH++;
				//_hoops_ICGAR->_hoops_IIHRI+=_hoops_IGIR; _hoops_CPHR _hoops_GGR _hoops_CIHRI
				_hoops_PSPRI = _hoops_HHHRI(size, try_alloc, pool, false, size, false);
				if (_hoops_PSPRI)
					p = _hoops_CPHRI(_hoops_PSPRI);
			}

			if (_hoops_PCGS)
				_hoops_CSPRI(pool);
		}
	}
	else {
		if (pool != HOOPS_WORLD->memory_pool) {
			pool = HOOPS_WORLD->memory_pool;
			_hoops_SSAGR(pool);
		}

		HOOPS_WORLD->_hoops_ICRGH++;
		//_hoops_ICGAR->_hoops_IIHRI+=_hoops_IGIR; _hoops_CPHR _hoops_GGR _hoops_CIHRI
		_hoops_PSPRI = _hoops_HHHRI(size, try_alloc, pool, true, size, false);
		if (_hoops_PSPRI)
			p = _hoops_CPHRI(_hoops_PSPRI);
	}

#ifdef VALIDATE_MEMORY
	if (p)
		_hoops_CGHRI(p, size, true, type_name, file, line);
#endif

	return p;
}

GLOBAL_FUNCTION void HI_Free_Array(
	void *			p,
	size_t			_hoops_GCHRI,
	const char *	file,
	int				line)
{
	_hoops_SSAGR(_hoops_SSPRI(p));

	if (p == null) {
#ifdef VALIDATE_MEMORY
		_hoops_IPR (_hoops_RISSH, _hoops_AISSH,
			Sprintf_SD (null, "Attempted free a null pointer 0 in %s line %d", file, line));
#else
		UNREFERENCED(_hoops_GCHRI);
		UNREFERENCED(file);
		UNREFERENCED(line);
#endif
		return;
	}

	_hoops_CGPRI *		_hoops_PSRGA = (_hoops_CGPRI *)p;
	_hoops_SGPRI *	_hoops_ASPRI = _hoops_SSPRI(_hoops_PSRGA);
	_hoops_AIARI *	_hoops_PSPRI = _hoops_ASPRI->_hoops_GRPRI;
	Memory_Pool *	pool = _hoops_PSPRI->pool;;

	_hoops_SSAGR(pool);

	ASSERT(pool != 0);
	ASSERT(_hoops_PSPRI != 0);

	size_t size = _hoops_ASPRI->size;
	ASSERT(size == _hoops_GIARI(_hoops_GCHRI));

#ifdef VALIDATE_MEMORY
	_hoops_CGHRI(p, _hoops_GCHRI, false, 0, file, line);
#endif

	if (size <= QUICK_MEM_MAX_BYTES) {
		bool 		_hoops_PCGS = _hoops_ISPRI(pool);

		_hoops_PSRGA->next = _hoops_PSPRI->globs;
		_hoops_PSPRI->globs = _hoops_PSRGA;
		++_hoops_PSPRI->glob_count;

		pool->_hoops_HHPRI -= QUICK_MEM_SLOT_SIZE(_hoops_PSPRI->_hoops_GIARA);

		if (_hoops_PSPRI != pool->_hoops_GIPRI[_hoops_PSPRI->_hoops_GIARA]._hoops_SAPRI) {
			if (_hoops_PSPRI->glob_count == (unsigned int)_hoops_PSPRI->_hoops_HRPRI) {
				// _hoops_HSRPA _hoops_GGSR _hoops_IIGR _hoops_CSRR _hoops_HIGR
				if ((*_hoops_PSPRI->_hoops_PRPRI = _hoops_PSPRI->_hoops_ARPRI) != null)
					_hoops_PSPRI->_hoops_ARPRI->_hoops_PRPRI = _hoops_PSPRI->_hoops_PRPRI;

				if (pool->_hoops_IIPRI < _hoops_PIARI) {
					// _hoops_HSRPA _hoops_CIAA _hoops_PPRAR _hoops_HIGR _hoops_RPP _hoops_SIGR _hoops_PAR _hoops_GRP _hoops_AISSA
					if ((_hoops_PSPRI->_hoops_ARPRI = pool->_hoops_GIPRI[_hoops_PSPRI->_hoops_GIARA]._hoops_APPRI) != null)
						pool->_hoops_GIPRI[_hoops_PSPRI->_hoops_GIARA]._hoops_APPRI->_hoops_PRPRI = &_hoops_PSPRI->_hoops_ARPRI;
					_hoops_PSPRI->_hoops_PRPRI = &pool->_hoops_GIPRI[_hoops_PSPRI->_hoops_GIARA]._hoops_APPRI;
					pool->_hoops_GIPRI[_hoops_PSPRI->_hoops_GIARA]._hoops_APPRI = _hoops_PSPRI;
					pool->_hoops_IIPRI += QUICK_MEM_MAX_BLOCK_SIZE;
				}
				else
					_hoops_PAHRI (_hoops_PSPRI, pool, false, 0);
			}
			else if (_hoops_PSPRI->glob_count == _hoops_AHIA((unsigned int)(_hoops_PSPRI->_hoops_HRPRI>>2)+1, 8U)) {
				// _hoops_IHIS _hoops_HII _hoops_RHPA _hoops_HIGR _hoops_IS _hoops_GCPSH _hoops_HIGR
				if ((*_hoops_PSPRI->_hoops_PRPRI = _hoops_PSPRI->_hoops_ARPRI) != null)
					_hoops_PSPRI->_hoops_ARPRI->_hoops_PRPRI = _hoops_PSPRI->_hoops_PRPRI;
				if ((_hoops_PSPRI->_hoops_ARPRI = pool->_hoops_GIPRI[_hoops_PSPRI->_hoops_GIARA]._hoops_GPPRI) != null)
					pool->_hoops_GIPRI[_hoops_PSPRI->_hoops_GIARA]._hoops_GPPRI->_hoops_PRPRI = &_hoops_PSPRI->_hoops_ARPRI;
				_hoops_PSPRI->_hoops_PRPRI = &pool->_hoops_GIPRI[_hoops_PSPRI->_hoops_GIARA]._hoops_GPPRI;
				pool->_hoops_GIPRI[_hoops_PSPRI->_hoops_GIARA]._hoops_GPPRI = _hoops_PSPRI;
			}
		}

		if (_hoops_PCGS)
			_hoops_CSPRI(pool);

		_hoops_PSARI(pool);
	}
	else {
		if (_hoops_PSPRI->glob_count == 0) {
#ifdef VALIDATE_MEMORY
			size_t		_hoops_RCHRI = _hoops_GIARI(size) + _hoops_RIARI + GLOB_HEADER_SIZE + GLOB_FOOTER_SIZE;
			if (_hoops_RCHRI != _hoops_PSPRI->size) {
				ASSERT(0);
				_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Size of memory freed not equal to size allocated.");
				return;
			}
#endif
			_hoops_PAHRI (_hoops_PSPRI, pool, true, size);
		}
		else {
#ifdef VALIDATE_MEMORY
			if (_hoops_PSPRI->glob_count != size) {
				ASSERT(0);
				_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Size of memory freed not equal to size allocated.");
				return;
			}
#endif
			bool	_hoops_PCGS = _hoops_ISPRI(pool);

			pool->_hoops_HHPRI -= size;

			if (size <= _hoops_SIARI) {
				//_hoops_RGRRR		_hoops_CSRR = _hoops_ACHRI(_hoops_IGIR);
				long		_hoops_GIARA = _hoops_PSPRI->_hoops_GIARA;
				_hoops_PPPRI *	_hoops_PIHRI = &pool->_hoops_RIPRI[_hoops_GIARA];

				_hoops_PIHRI->_hoops_IPPRI--;

				if (_hoops_PIHRI->_hoops_HPPRI < _hoops_IRPRI[_hoops_GIARA]) {
					_hoops_PSPRI->_hoops_ARPRI = _hoops_PIHRI->_hoops_HAPRI;
					_hoops_PIHRI->_hoops_HAPRI = _hoops_PSPRI;
					_hoops_PIHRI->_hoops_HPPRI++;
					pool->_hoops_CIPRI += _hoops_PSPRI->size;
				}
				else {
					// _hoops_PRIA _hoops_CGPR _hoops_IHAH _hoops_IAPR _hoops_PCHRI
					HOOPS_WORLD->_hoops_ICRGH++;
					_hoops_PAHRI (_hoops_PSPRI, pool, false, 0);
				}
			}
			else if (size <= _hoops_ICARI) {
				ASSERT(pool == HOOPS_WORLD->memory_pool);

				//_hoops_RGRRR				_hoops_CSRR = _hoops_HCHRI(_hoops_IGIR);
				long				_hoops_GIARA = _hoops_PSPRI->_hoops_GIARA;
				_hoops_CPPRI *	_hoops_SIHRI = &pool->_hoops_AIPRI[_hoops_GIARA];

				_hoops_SIHRI->_hoops_IPPRI--;
				_hoops_SIHRI->_hoops_SPPRI = *HOOPS_WORLD->time_stamp;

				if (_hoops_SIHRI->_hoops_HPPRI < _hoops_CRPRI[_hoops_GIARA]) {
					_hoops_PSPRI->_hoops_ARPRI = _hoops_SIHRI->_hoops_HAPRI;
					_hoops_SIHRI->_hoops_HAPRI = _hoops_PSPRI;
					_hoops_SIHRI->_hoops_HPPRI++;
					pool->_hoops_SIPRI += _hoops_PSPRI->size;
				}
				else {
					// _hoops_PRIA _hoops_CGPR _hoops_IHAH _hoops_IAPR _hoops_PCHRI
					HOOPS_WORLD->_hoops_ICRGH++;
					_hoops_PAHRI (_hoops_PSPRI, pool, false, 0);
				}
			}
			else {
				ASSERT(pool == HOOPS_WORLD->memory_pool);

				_hoops_CPPRI *	_hoops_SIHRI = &pool->_hoops_PIPRI[0];

				_hoops_SIHRI->_hoops_IPPRI--;
				_hoops_SIHRI->_hoops_SPPRI = *HOOPS_WORLD->time_stamp;

				// _hoops_IHAH _hoops_PAH _hoops_HAR _hoops_PGSAH
				ASSERT(_hoops_SIHRI->_hoops_HPPRI < _hoops_ASARI);

				_hoops_PSPRI->_hoops_ARPRI = _hoops_SIHRI->_hoops_HAPRI;
				_hoops_SIHRI->_hoops_HAPRI = _hoops_PSPRI;
				_hoops_SIHRI->_hoops_HPPRI++;
				pool->_hoops_SIPRI += _hoops_PSPRI->size;
			}

			if (_hoops_PCGS)
				_hoops_CSPRI(pool);
		}
	}
}

GLOBAL_FUNCTION size_t HI_Memory_On_Pool (Memory_Pool *pool, size_t * allocated, size_t *used)
{
	if (BIT (HOOPS_WORLD->system_flags, Sysop_RAW_MEMORY) && pool == HOOPS_WORLD->memory_pool) {
		if (allocated)
			*allocated = HOOPS_WORLD->raw_memory_usage;
		if (used)
			*used = HOOPS_WORLD->raw_memory_usage;

		return HOOPS_WORLD->raw_memory_usage;
	}

	if (allocated)
		*allocated = pool->_hoops_GCPRI;
	if (used)
		*used = pool->_hoops_HHPRI;

	return pool->_hoops_HHPRI;
}


GLOBAL_FUNCTION void HI_Show_Memory_Usage(
	long *		allocated,
	long *		used)
{

	if (BIT (HOOPS_WORLD->system_flags, Sysop_RAW_MEMORY)) {
		*allocated = (long) HOOPS_WORLD->raw_memory_usage;
		*used = (long) HOOPS_WORLD->raw_memory_usage;
		return;
	}

	*allocated = 0;
	*used = 0;

	_hoops_CAAI (HOOPS_WORLD->_hoops_RPHGI);

	Memory_Pool *	pool = HOOPS_WORLD->_hoops_ACPGI;

	while (pool) {
		bool		_hoops_PCGS = _hoops_ISPRI(pool);

		*used += (long)pool->_hoops_HHPRI;
		*allocated += (long)pool->_hoops_GCPRI;

		if (_hoops_PCGS)
			_hoops_CSPRI(pool);

		pool = pool->next;
	}

	_hoops_APAI (HOOPS_WORLD->_hoops_RPHGI);
}

HC_INTERFACE void HC_CDECL HC_Show_Memory_Usage (
	long *		allocated,
	long *		used)
{
	_hoops_PAPPR context("Show_Memory_Usage");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("HC_Show_Memory_Usage (&ll, &ll);\n");
	);

	HI_Show_Memory_Usage (allocated, used);

#endif
}


GLOBAL_FUNCTION void HI_Relinquish_Memory_On_Pool (Memory_Pool * pool)
{
	bool		_hoops_ICHRI = false;

	if (pool->_hoops_IHPRI != null) {
		_hoops_ICHRI = true;
		HI_Use_Memory_Task(pool, false);
	}

	bool _hoops_PCGS = _hoops_ISPRI(pool);

	_hoops_AIARI *		_hoops_PSPRI;

//#_hoops_PPIP _hoops_CCHRI
#ifdef _hoops_SCHRI
	_hoops_AIARI *current, *next;
	next = pool->_hoops_CHPRI;
	while ((current = next) != null) {
		next = current->next;
	}
#endif

	for (long _hoops_GIARA=0; _hoops_GIARA<QUICK_MEM_SLOTS; _hoops_GIARA++) {
		if ((_hoops_PSPRI = pool->_hoops_GIPRI[_hoops_GIARA]._hoops_SAPRI) != null) {
			if (_hoops_PSPRI->glob_count == (unsigned Integer32)_hoops_PSPRI->_hoops_HRPRI) {
				if ((*_hoops_PSPRI->backlink = _hoops_PSPRI->next) != null)
					_hoops_PSPRI->next->backlink = _hoops_PSPRI->backlink;
				ASSERT(_hoops_PSPRI->_hoops_PRPRI == null);
				ASSERT(_hoops_PSPRI->_hoops_ARPRI == null);
				pool->_hoops_GCPRI -= _hoops_PSPRI->size;
				_hoops_AAHRI (pool, _hoops_PSPRI);
				pool->_hoops_GIPRI[_hoops_GIARA]._hoops_SAPRI = null;
			}
		}

		while ((_hoops_PSPRI = pool->_hoops_GIPRI[_hoops_GIARA]._hoops_APPRI) != null) {
			if ((*_hoops_PSPRI->backlink = _hoops_PSPRI->next) != null)
				_hoops_PSPRI->next->backlink = _hoops_PSPRI->backlink;
			if ((*_hoops_PSPRI->_hoops_PRPRI = _hoops_PSPRI->_hoops_ARPRI) != null)
				_hoops_PSPRI->_hoops_ARPRI->_hoops_PRPRI = _hoops_PSPRI->_hoops_PRPRI;
			pool->_hoops_GCPRI -= _hoops_PSPRI->size;
			pool->_hoops_IIPRI -= QUICK_MEM_MAX_BLOCK_SIZE;
			_hoops_AAHRI (pool, _hoops_PSPRI);
		}
	}

#ifdef _hoops_SCHRI
	next = pool->_hoops_CHPRI;
	while ((current = next) != null) {
		next = current->next;
	}
#endif

	if (pool->_hoops_RIPRI) {
		for (long _hoops_GIARA  =0; _hoops_GIARA < _hoops_RCARI; _hoops_GIARA++) {
			while ((_hoops_PSPRI = pool->_hoops_RIPRI[_hoops_GIARA]._hoops_HAPRI) != null) {
				if ((*_hoops_PSPRI->backlink = _hoops_PSPRI->next) != null)
					_hoops_PSPRI->next->backlink = _hoops_PSPRI->backlink;
				pool->_hoops_RIPRI[_hoops_GIARA]._hoops_HAPRI = _hoops_PSPRI->_hoops_ARPRI;
				pool->_hoops_GCPRI -= _hoops_PSPRI->size;
				pool->_hoops_CIPRI -= _hoops_PSPRI->size;
				_hoops_AAHRI (pool, _hoops_PSPRI);
			}

			pool->_hoops_RIPRI[_hoops_GIARA]._hoops_HPPRI=0;
		}
	}

#ifdef _hoops_SCHRI
	next = pool->_hoops_CHPRI;
	while ((current = next) != null) {
		next = current->next;
	}
#endif

	if (pool->_hoops_AIPRI) {
		for (long _hoops_GIARA = 0; _hoops_GIARA < _hoops_SCARI; _hoops_GIARA++) {
			while ((_hoops_PSPRI = pool->_hoops_AIPRI[_hoops_GIARA]._hoops_HAPRI) != null) {
				if ((*_hoops_PSPRI->backlink = _hoops_PSPRI->next) != null)
					_hoops_PSPRI->next->backlink = _hoops_PSPRI->backlink;
				pool->_hoops_AIPRI[_hoops_GIARA]._hoops_HAPRI = _hoops_PSPRI->_hoops_ARPRI;
				pool->_hoops_GCPRI -= _hoops_PSPRI->size;
				pool->_hoops_SIPRI -= _hoops_PSPRI->size;
				_hoops_AAHRI (pool, _hoops_PSPRI);
			}

			pool->_hoops_AIPRI[_hoops_GIARA]._hoops_HPPRI=0;
		}
	}

#ifdef _hoops_SCHRI
	next = pool->_hoops_CHPRI;
	while ((current = next) != null) {
		next = current->next;
	}
#endif

	if (pool->_hoops_PIPRI) {
		for (long _hoops_GIARA = 0; _hoops_GIARA < _hoops_RSARI; _hoops_GIARA++) {
			while ((_hoops_PSPRI = pool->_hoops_PIPRI[_hoops_GIARA]._hoops_HAPRI) != null) {
				if ((*_hoops_PSPRI->backlink = _hoops_PSPRI->next) != null)
					_hoops_PSPRI->next->backlink = _hoops_PSPRI->backlink;
				pool->_hoops_PIPRI[_hoops_GIARA]._hoops_HAPRI = _hoops_PSPRI->_hoops_ARPRI;
				pool->_hoops_GCPRI -= _hoops_PSPRI->size;
				pool->_hoops_SIPRI -= _hoops_PSPRI->size;
				_hoops_AAHRI (pool, _hoops_PSPRI);
			}

			pool->_hoops_PIPRI[_hoops_GIARA]._hoops_HPPRI=0;
		}
	}

	if (pool->_hoops_HIPRI) {
		for (int i=0; i<_hoops_SRPRI; ++i) {
			while ((_hoops_PSPRI = pool->_hoops_HIPRI->_hoops_HAPRI[i]) != null) {
				if ((*_hoops_PSPRI->backlink = _hoops_PSPRI->next) != null)
					_hoops_PSPRI->next->backlink = _hoops_PSPRI->backlink;
				pool->_hoops_HIPRI->_hoops_CAPRI[i] -= _hoops_PSPRI->size;
				pool->_hoops_GCPRI -= _hoops_PSPRI->size;
				_hoops_AAHRI (pool, _hoops_PSPRI);
			}

			pool->_hoops_HIPRI->_hoops_IAPRI[i] = null;
			ASSERT(pool->_hoops_HIPRI->_hoops_CAPRI[i] == 0);
			pool->_hoops_HIPRI->_hoops_CAPRI[i] = 0;
		}
	}

	if (pool->_hoops_SHPRI) {
		while ((_hoops_PSPRI = pool->_hoops_SHPRI) != null) {
			if ((*_hoops_PSPRI->backlink = _hoops_PSPRI->next) != null)
				_hoops_PSPRI->next->backlink = _hoops_PSPRI->backlink;
			pool->_hoops_RCPRI -= _hoops_PSPRI->size;
			pool->_hoops_GCPRI -= _hoops_PSPRI->size;
			_hoops_AAHRI (pool, _hoops_PSPRI);
		}

		ASSERT(pool->_hoops_RCPRI == 0);
		pool->_hoops_RCPRI = 0;
	}

#ifdef _hoops_SCHRI
	next = pool->_hoops_CHPRI;
	while ((current = next) != null) {
		next = current->next;
	}
#endif

#ifdef VALIDATE_MEMORY
	if (pool->_hoops_IIPRI != 0)
		HE_WARNING (HEC_MEMORY, HES_DATA_ERROR, "Unused quick memory count wrong.");
	if (pool->_hoops_CIPRI != 0)
		HE_WARNING (HEC_MEMORY, HES_DATA_ERROR, "Unused big memory count wrong.");
#endif

	if (_hoops_PCGS)
		_hoops_CSPRI(pool);

	if (_hoops_ICHRI)
		HI_Use_Memory_Task(pool, true);
}

GLOBAL_FUNCTION void HI_Relinquish_Memory (void) {
	_hoops_CAAI (HOOPS_WORLD->_hoops_RPHGI);

	Memory_Pool *	pool = HOOPS_WORLD->_hoops_ACPGI;

	while (pool) {
		if (pool->_hoops_CHPRI)
			HI_Relinquish_Memory_On_Pool(pool);

		pool = pool->next;
	}

	_hoops_APAI (HOOPS_WORLD->_hoops_RPHGI);
}


HC_INTERFACE void HC_CDECL HC_Relinquish_Memory (void)
{
	_hoops_PAPPR context("Relinquish Memory");

	CODE_GENERATION (
		HI_Dump_Code ("HC_Relinquish_Memory ();\n");
	);

	HI_Relinquish_Memory ();

	HI_System_Memory_Purge();
}


#  include "database.h"
#  include "driver.h"
#  include "hoops.h"
#  include "hidden.h"


#define	_hoops_GSHRI				0x0001
#define	_hoops_RSHRI				0x0002
#define	_hoops_ASHRI		0x0004
#define _hoops_PSHRI			0x0008
#define _hoops_HSHRI		0x0010
#define _hoops_ISHRI	0x0020
#define _hoops_CSHRI	0x0040
#define _hoops_SSHRI		0x0080

local const _hoops_IGRCR _hoops_GGIRI[] = {
	{_hoops_GSHRI,			_hoops_GRRCR ("block stuff"),			_hoops_RRRCR, 0, false},
	{_hoops_RSHRI,			_hoops_GRRCR ("type allocs"),			_hoops_RRRCR, 0, false},
	{_hoops_RSHRI,			_hoops_GRRCR ("type alloc"),			_hoops_RRRCR, 0, false},
	{_hoops_ASHRI,		_hoops_GRRCR ("type alloc lines"),		_hoops_RRRCR, 0, false},
	{_hoops_PSHRI,		_hoops_GRRCR ("type"),					_hoops_ARSAP, 1, true},
	{_hoops_HSHRI,		_hoops_GRRCR ("callback"),				_hoops_PRRCR,	1, false},
	{_hoops_ISHRI,	_hoops_GRRCR ("callback data"),			_hoops_PRRCR,	1, false},
	{_hoops_CSHRI, _hoops_GRRCR ("supported"),				_hoops_PRRCR,	0, false},
	{_hoops_SSHRI,		_hoops_GRRCR ("oversized allocs"),		_hoops_PRRCR,	0, false},
};

HC_INTERFACE POINTER_SIZED_INT HC_CDECL HC_Dump_Memory_Profile (
	char const *	which)
{
	_hoops_PAPPR context("Dump_Memory_Profile");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Dump_Memory_Profile (); */");
	);


	Option_Value *			option_list;
	Option_Value *			option;
	int						_hoops_ICSGA = 0;
	size_t					_hoops_CRHRI = 0;

#ifdef VALIDATE_MEMORY
	_hoops_HCRPR					type;
	_hoops_IRPCR			callback = null;
	void *					_hoops_RGIRI = null;
#endif

	_hoops_HIACR (_hoops_IIRGI, _hoops_GGIRI);

	if (!HI_Parse_Options (context, which, _hoops_CIACR (_hoops_IIRGI), &option_list, _hoops_SIACR)) {
		HI_Free_Option_List (context, option_list);
		return -1;
	}

	if ((option = option_list) != null) do {
		int	_hoops_ARPPH = option->type->id;

		if (option->_hoops_GCACR)
			_hoops_ICSGA &= ~_hoops_ARPPH;
		else {
			_hoops_ICSGA |= _hoops_ARPPH;
		}

		if (_hoops_ARPPH == _hoops_SSHRI) {
			HI_Free_Option_List (context, option_list);

			if (BIT (HOOPS_WORLD->system_flags, Sysop_RAW_MEMORY))
				return 0;

			return HOOPS_WORLD->_hoops_ICRGH;
		}


		if (_hoops_ARPPH == _hoops_CSHRI) {
			HI_Free_Option_List (context, option_list);
			if (!BIT (HOOPS_WORLD->_hoops_IRARR, _hoops_RRHGI))
				return 0;
			if (BIT (HOOPS_WORLD->system_flags, Sysop_RAW_MEMORY))
				return 0;

#if !defined (VALIDATE_MEMORY)
			return 0;
#else
			return 1;
#endif
		}

		if (_hoops_ARPPH == _hoops_PSHRI) {
#ifndef VALIDATE_MEMORY
			HE_ERROR (HEC_MEMORY, HES_MEMORY_PROFILE_NOT_COMPILED, "Memory profiling 'type' is not compiled into this copy of HOOPS");
			return 0;
#else
			/* _hoops_ASRC _hoops_RH _hoops_PHI _hoops_IIGR _hoops_GCSRR _hoops_PSPP _hoops_IH _hoops_RAGA _hoops_GPRR */
			Memory_Pool *	 _hoops_AGIRI = HOOPS_WORLD->memory_pool;
			HI_Copy_Name(option->value._name, &type);

			if (_hoops_AGIRI) {
				bool _hoops_PCGS = _hoops_ISPRI(_hoops_AGIRI);

				_hoops_RRGGI *	_hoops_GCAH = _hoops_AGIRI->_hoops_ACPRI;
				_hoops_CRHRI = _hoops_GCAH->Lookup(type.text);

				if (_hoops_PCGS)
					_hoops_CSPRI(_hoops_AGIRI);
			}
			_hoops_RGAIR(type);
#endif
		}

		if (_hoops_ARPPH == _hoops_HSHRI) {
#ifndef VALIDATE_MEMORY
			HE_ERROR (HEC_MEMORY, HES_MEMORY_PROFILE_NOT_COMPILED, "Memory profiling 'callback' is not compiled into this copy of HOOPS");
			return 0;
#else
	  		_hoops_HCRPR *		name = option->value._name;
			POINTER_SIZED_INT	value;

			if (!option->_hoops_GCACR) {
				char *		_hoops_RPPA = name->text;
				if (HI_Scan_Ptr (context, (char const **)&_hoops_RPPA, _hoops_RPPA+name->length, &value) == null) {
					callback = (_hoops_IRPCR)value;
				}
				else
					HE_ERROR (HEC_HOOPS_SYSTEM, HES_BAD_VALUE,
						Sprintf_N (null, "callback '%n' is not a valid pointer", name));
			}
#endif
		}

		if (_hoops_ARPPH == _hoops_ISHRI) {
#ifndef VALIDATE_MEMORY
			HE_ERROR (HEC_MEMORY, HES_MEMORY_PROFILE_NOT_COMPILED,"Memory profiling 'callback data' is not compiled into this copy of HOOPS");
			return 0;
#else
	  		_hoops_HCRPR *		name = option->value._name;
			POINTER_SIZED_INT	value;

			if (!option->_hoops_GCACR) {
				char *		_hoops_RPPA = name->text;
				if (HI_Scan_Ptr (context, (char const **)&_hoops_RPPA, _hoops_RPPA+name->length, &value) == null) {
					_hoops_RGIRI = (void *)value;
				}
				else
					HE_ERROR (HEC_HOOPS_SYSTEM, HES_BAD_VALUE, Sprintf_N (null, "callback data '%n' is not a valid pointer", name));
			}
#endif
		}
	} while ((option = option->next) != null);

	HI_Free_Option_List (context, option_list);

	if (_hoops_ICSGA == 0)
		return -1;		/* _hoops_ISAP _hoops_HGRC? */

#ifndef VALIDATE_MEMORY
	if (!ANYBIT(_hoops_ICSGA, _hoops_GSHRI|_hoops_RSHRI|_hoops_ASHRI))
		return (long)_hoops_CRHRI;

	HE_ERROR (HEC_MEMORY, HES_MEMORY_PROFILE_NOT_COMPILED, "Memory profiling 'dump_memory.txt' is not compiled into this copy of HOOPS");
	return 0;
#else

	FILE *	fp;
	if (NULL == (fp = fopen("dump_memory.txt","a+"))) {
		HE_ERROR (HEC_MEMORY, HES_MEMORY_PROFILE_NOT_COMPILED,"can't open dump_memory.txt");
	}
	if (BIT (HOOPS_WORLD->system_flags, Sysop_RAW_MEMORY)) {
		fprintf(fp, "raw_memory_usage : %p\n", I2V(HOOPS_WORLD->raw_memory_usage));
		return 0;
	}
	else {
		Memory_Pool	*		pool = HOOPS_WORLD->memory_pool;
		bool				_hoops_PCGS = _hoops_ISPRI(pool);

		if (BIT(_hoops_ICSGA, _hoops_GSHRI)) {
			size_t 			allocated = 0;
			size_t 			_hoops_PGIRI = 0;

			fprintf(fp,"pool : %p\n", pool);
			fprintf(fp,"flags: %p\n", pool->flags);
			fprintf(fp,"slots: %d\n", QUICK_MEM_SLOTS);
			fprintf(fp,"align: %d\n", ALIGNMENT);

			fprintf(fp,"unused_quick_block_bytes: %p\n", I2V(pool->_hoops_IIPRI));
			fprintf(fp,"unused_big_block_bytes: %p\n", I2V(pool->_hoops_CIPRI));
			fprintf(fp,"allocated_glob_bytes: %p\n", I2V(pool->_hoops_HHPRI));
			fprintf(fp,"allocated_memory_block_bytes: %p\n", I2V(pool->_hoops_GCPRI));

			{	_hoops_AIARI *	_hoops_PSPRI;
				size_t			_hoops_ARAHR = 0;
				int				_hoops_HGIRI = 0;

				fprintf(fp,"block sizes:\n");

				if ((_hoops_PSPRI = pool->_hoops_CHPRI) != null) {
					do {
						if (_hoops_PSPRI->_hoops_HRPRI == -1) {
							fprintf(fp,"%p ", I2V(_hoops_PSPRI->size));
							_hoops_ARAHR += _hoops_PSPRI->size;
							++_hoops_HGIRI;
							if (_hoops_HGIRI % 10 == 0)
								fprintf(fp,"\n");
						}
					} while ((_hoops_PSPRI = _hoops_PSPRI->next) != null);
				}

				allocated += _hoops_ARAHR;
				_hoops_PGIRI += _hoops_HGIRI * (long)sizeof(_hoops_AIARI);
			}

			{	_hoops_AIARI *	_hoops_PSPRI;
				size_t			_hoops_ARAHR = 0;
				int				_hoops_HGIRI = 0;

				fprintf(fp,"\nqmem blocks\n");

				fprintf(fp,"size\tglob_count\ttotal_glob_count\n");

				if ((_hoops_PSPRI = pool->_hoops_CHPRI) != null) {
					do {
						if (_hoops_PSPRI->_hoops_HRPRI != -1) {
							fprintf(fp,"%p\t%d\t\t%hd\n", I2V(_hoops_PSPRI->size), _hoops_PSPRI->glob_count, _hoops_PSPRI->_hoops_HRPRI);

							_hoops_ARAHR += _hoops_PSPRI->size;
							++_hoops_HGIRI;
						}
					} while ((_hoops_PSPRI = _hoops_PSPRI->next) != null);
				}

				allocated += _hoops_ARAHR;
				_hoops_PGIRI += _hoops_HGIRI * (long)sizeof(_hoops_AIARI);
			}

			{	int				_hoops_GIARA = QUICK_MEM_SLOTS - 1;
				_hoops_AIARI *	_hoops_PSPRI;

				fprintf(fp,"slot\tbytes\tfree\tfragment\tempty\n");

				do {
					int			_hoops_IGIRI = 0;
					int			_hoops_CGIRI = 0;
					int			_hoops_SGIRI = 0;

					int _hoops_GRIRI = ((_hoops_GIARA + 1) << ALIGNMENT);

					if ((_hoops_PSPRI = pool->_hoops_GIPRI[_hoops_GIARA]._hoops_SAPRI) != null) {
						_hoops_PGIRI += QUICK_MEM_BLOCK_SIZE-(_hoops_PSPRI->_hoops_HRPRI*_hoops_GRIRI);
						do ++_hoops_IGIRI;
						_hoops_RGGA ((_hoops_PSPRI = _hoops_PSPRI->_hoops_ARPRI) == null);
					}

					if ((_hoops_PSPRI = pool->_hoops_GIPRI[_hoops_GIARA]._hoops_GPPRI) != null) {
						_hoops_PGIRI += QUICK_MEM_BLOCK_SIZE-(_hoops_PSPRI->_hoops_HRPRI*_hoops_GRIRI);
						do ++_hoops_CGIRI;
						_hoops_RGGA ((_hoops_PSPRI = _hoops_PSPRI->_hoops_ARPRI) == null);
					}
					if ((_hoops_PSPRI = pool->_hoops_GIPRI[_hoops_GIARA]._hoops_RPPRI) != null) {
						_hoops_PGIRI += QUICK_MEM_BLOCK_SIZE-(_hoops_PSPRI->_hoops_HRPRI*_hoops_GRIRI);
						do ++_hoops_SGIRI;
						_hoops_RGGA ((_hoops_PSPRI = _hoops_PSPRI->_hoops_ARPRI) == null);
					}

					fprintf(fp,"%d\t%d\t%d\t%d\t%d\n", _hoops_GIARA,_hoops_GRIRI,
						_hoops_IGIRI, _hoops_CGIRI, _hoops_SGIRI);
				} _hoops_RGGA (--_hoops_GIARA < 0);
			}

			fprintf(fp,"waste: %ld\n\n", _hoops_PGIRI);
		}

		if (ANYBIT(_hoops_ICSGA, _hoops_RSHRI|_hoops_ASHRI)) {
			/* _hoops_RRIRI _hoops_CCRSA _hoops_HIGR _hoops_IS _hoops_CRHR _hoops_PGGS _hoops_PAGIR */
			_hoops_RRGGI * _hoops_GCAH = pool->_hoops_ACPRI;
			pool->_hoops_ACPRI = null;

			if (_hoops_PCGS) // _hoops_RSAIP _hoops_IS _hoops_SRCH _hoops_HISRA _hoops_ACSRA
				_hoops_CSPRI(pool);
			_hoops_RRGGI::PairList * _hoops_ARIRI = _hoops_GCAH->GetPairList();
			_hoops_ISPRI(pool);

			_hoops_ARIRI->ResetCursor();
			_hoops_RRGGI::Pair * p;

			while ((p = _hoops_ARIRI->PeekCursor()) != 0) {
				char _hoops_PRIRI[1024];
				strcpy(_hoops_PRIRI, p->Key());

				if (BIT(_hoops_ICSGA, _hoops_ASHRI)) {
					if (_hoops_PRIRI[0] == '#')
						fprintf(fp, "\t%s : %p\n", &_hoops_PRIRI[1], I2V(p->Item()));
				}

				if (ANYBIT(_hoops_ICSGA, _hoops_RSHRI|_hoops_RSHRI)) {
					if (_hoops_PRIRI[0] != '#') {
						fprintf(fp, "%s : %p\n", p->Key(), I2V(p->Item()));
						if (callback)
							callback(p->Key(), p->Item(), _hoops_RGIRI);
					}
				}
				_hoops_ARIRI->AdvanceCursor();
			}
			if (_hoops_PCGS) // _hoops_RSAIP _hoops_IS _hoops_SRCH _hoops_HISRA _hoops_ACSRA
				_hoops_CSPRI(pool);
			delete _hoops_ARIRI;
			_hoops_ISPRI(pool);

			pool->_hoops_ACPRI = _hoops_GCAH;
		}

		if (_hoops_PCGS)
			_hoops_CSPRI(pool);

//#_hoops_PPIP _hoops_HRIRI
#ifdef _hoops_IRIRI
#define _hoops_CRIRI(x)   #x
#define XSTR(x)  _hoops_CRIRI(x)

#if 0
#define QUICK_MEM_SIZE_CHECK(_x_) do { \
    if (sizeof(_x_) > QUICK_MEM_MAX_BYTES)  { \
        fprintf (fp, "QUICK_MEM_MAX_BYTES EXCEDED: %s \t%ld\n", XSTR(_x_), sizeof(_x_)); \
    } \
} while (0)
#else
#define QUICK_MEM_SIZE_CHECK(_x_) do { \
	fprintf (fp, "%s \t%ld\n", XSTR(_x_), sizeof(_x_)); \
} while (0)
#endif

    QUICK_MEM_SIZE_CHECK(Display_Context);
#endif
	}

	fclose(fp);
	return (long)_hoops_CRHRI;
#endif
}





GLOBAL_FUNCTION bool HI_Destroy_Memory_Pool(Memory_Pool alter * pool)
{
	bool	result = true;

#ifdef VALIDATE_MEMORY
	/* _hoops_RRIRI _hoops_CCRSA _hoops_HIGR _hoops_IS _hoops_CRHR _hoops_PGGS _hoops_PAGIR */
	if (pool->_hoops_ACPRI) {
		_hoops_RRGGI * _hoops_GCAH = pool->_hoops_ACPRI;
		pool->_hoops_ACPRI = null;
		delete _hoops_GCAH;
	}
	if (pool->_hoops_PCPRI) {
		_hoops_IGPRI *_hoops_GCAH = pool->_hoops_PCPRI;
		pool->_hoops_PCPRI = null;
		_hoops_GCAH->DeleteItems();
		delete _hoops_GCAH;
	}
#endif

	HI_Use_Memory_Task(pool, false);

	HI_Relinquish_Memory_On_Pool(pool);

	_hoops_AIARI *current, *next;

	next = pool->_hoops_SHPRI;
	while ((current = next) != null) {
		next = current->next;
		_hoops_AAHRI (pool, current);
	}

	bool	_hoops_SRIRI = HOOPS_WORLD->_hoops_PPRIR || pool == HOOPS_WORLD->memory_pool;

	if (_hoops_SRIRI) {
		next = pool->_hoops_CHPRI;
		while ((current = next) != null) {
			next = pool->_hoops_CHPRI;
			while ((current = next) != null) {
				next = current->next;
				_hoops_AAHRI (pool, current);
			}
		}
	}

	if (!_hoops_SRIRI && pool->_hoops_CHPRI != null) {
		// _hoops_GAIRI _hoops_RAIRI
		result = false;

		pool->flags |= MPF_LOCKING|_hoops_AHPRI;

#ifndef _hoops_PHPRI
		if (!pool->_hoops_RASCA)
			CREATE_MUTEX (pool->_hoops_RASCA);
#endif
	}
	else {
		if (pool == HOOPS_WORLD->memory_pool) {
			ASSERT(HOOPS_WORLD->_hoops_PPRIR || HOOPS_WORLD->memory_pool->next == null);

			_hoops_CAAI (HOOPS_WORLD->_hoops_RPHGI);
			Memory_Pool alter *target = HOOPS_WORLD->_hoops_ACPGI;
			Memory_Pool alter *next;
			while (target != pool) {
				next = target->next;
				HI_Destroy_Memory_Pool(target);
				target = next;
			}
			_hoops_APAI (HOOPS_WORLD->_hoops_RPHGI);
		}

		FREE_MEMORY_ARRAY(pool->_hoops_GIPRI, QUICK_MEM_SLOTS, Quick_Slot);

		if (pool->_hoops_RIPRI)
			FREE_MEMORY_ARRAY(pool->_hoops_RIPRI, _hoops_RCARI, _hoops_PPPRI);

		if (pool->_hoops_AIPRI) {
			FREE_MEMORY_ARRAY(pool->_hoops_AIPRI, _hoops_SCARI, _hoops_CPPRI);
			FREE_MEMORY_ARRAY(pool->_hoops_PIPRI, _hoops_RSARI, _hoops_CPPRI);
		}

		if (pool->_hoops_HIPRI)
			FREE_MEMORY_ARRAY(pool->_hoops_HIPRI, 1, _hoops_PAPRI);

#ifndef _hoops_PHPRI
		if (pool->_hoops_RASCA)
			DESTROY_MUTEX (pool->_hoops_RASCA);
#endif

		_hoops_CAAI (HOOPS_WORLD->_hoops_RPHGI);
		ASSERT(HOOPS_WORLD->memory_pool != pool || HOOPS_WORLD->memory_pool == HOOPS_WORLD->_hoops_ACPGI);
		Memory_Pool alter ** _hoops_ASRGR = &HOOPS_WORLD->_hoops_ACPGI;
		while (*_hoops_ASRGR != pool)
			_hoops_ASRGR = &((*_hoops_ASRGR)->next);
		*_hoops_ASRGR = pool->next;
		_hoops_APAI (HOOPS_WORLD->_hoops_RPHGI);

		FREE_MEMORY(pool, Memory_Pool);
	}

	return result;
}


GLOBAL_FUNCTION Memory_Pool alter * HI_Create_Memory_Pool(Integer32 flags)
{
	Memory_Pool alter *		pool = null;
	ALLOCATE_MEMORY(pool, Memory_Pool);
	ZERO_STRUCT (pool, Memory_Pool);

	pool->flags = flags;

	pool->malloc = HOOPS_WORLD->malloc;
	pool->free = HOOPS_WORLD->free;

	ALLOCATE_MEMORY_ARRAY(pool->_hoops_GIPRI, QUICK_MEM_SLOTS, Quick_Slot);
	ZERO_ARRAY(pool->_hoops_GIPRI, QUICK_MEM_SLOTS, Quick_Slot);

	if (BIT(flags, MPF_BIG_BLOCKS)) {
		ALLOCATE_MEMORY_ARRAY(pool->_hoops_RIPRI, _hoops_RCARI, _hoops_PPPRI);
		ZERO_ARRAY(pool->_hoops_RIPRI, _hoops_RCARI, _hoops_PPPRI);
	}

	if (BIT(flags, MPF_SUPER_BIG_BLOCK)) {
		ALLOCATE_MEMORY_ARRAY(pool->_hoops_AIPRI, _hoops_SCARI, _hoops_CPPRI);
		ZERO_ARRAY(pool->_hoops_AIPRI, _hoops_SCARI, _hoops_CPPRI);

		ALLOCATE_MEMORY_ARRAY(pool->_hoops_PIPRI, _hoops_RSARI, _hoops_CPPRI);
		ZERO_ARRAY(pool->_hoops_PIPRI, _hoops_RSARI, _hoops_CPPRI);
	}

	if (BIT(flags, MPF_RECYCLER)) {
		ALLOCATE_MEMORY_ARRAY(pool->_hoops_HIPRI, 1, _hoops_PAPRI);
		ZERO_ARRAY(pool->_hoops_HIPRI, 1, _hoops_PAPRI);
	}

#ifndef _hoops_PHPRI
	if (BIT(flags, MPF_LOCKING))
		CREATE_MUTEX (pool->_hoops_RASCA);
#endif

	_hoops_CAAI (HOOPS_WORLD->_hoops_RPHGI);
	pool->next = HOOPS_WORLD->_hoops_ACPGI;
	HOOPS_WORLD->_hoops_ACPGI = pool;
	_hoops_APAI (HOOPS_WORLD->_hoops_RPHGI);

#ifdef VALIDATE_MEMORY
	if (!HOOPS_WORLD->memory_pool) {
		HOOPS_WORLD->memory_pool = pool;
	}

	pool->_hoops_ACPRI = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_RRGGI)((Memory_Pool *)null);
	pool->_hoops_PCPRI = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_IGPRI)((Memory_Pool *)null);
#endif

	return pool;
}




class _hoops_AAIRI : public _hoops_GCARR {
	public:
		_hoops_AAIRI(Memory_Pool * _hoops_IHHRI)	{
			pool = _hoops_IHHRI;
			pool->_hoops_IHPRI = this;
			HOOPS_WORLD->_hoops_ACARR->_hoops_PCARR(this);
		}

		virtual ~_hoops_AAIRI() {
			bool _hoops_PCGS = _hoops_ISPRI(pool);
			pool->_hoops_IHPRI = null;
			if (_hoops_PCGS)
				_hoops_CSPRI(pool);
		}

		virtual _hoops_ICARR Type() {return _hoops_PAIRI;}

		virtual void _hoops_HCARR(bool _hoops_SCARR);

	private:
		Memory_Pool *	pool;
};

GLOBAL_FUNCTION void HI_Use_Memory_Task(Memory_Pool alter * pool, bool _hoops_HAIRI)
{
#ifdef DISABLE_MUTEX
	if (_hoops_HAIRI)
		HE_ERROR2 (0, 0, _hoops_CAGHP (_hoops_SAGHP), "Multi-threading");
	return;
#else
	if (_hoops_HAIRI) {
		if (pool->_hoops_IHPRI == null)
			NEW(_hoops_AAIRI)(pool);
	}
	else {
		if (pool->_hoops_IHPRI) {
			HOOPS_WORLD->_hoops_ACARR->_hoops_IAIRI(pool->_hoops_IHPRI);
			delete pool->_hoops_IHPRI;
		}
	}
#endif
}





void _hoops_AAIRI::_hoops_HCARR(bool _hoops_SCARR) {
	int			_hoops_CAIRI = 10;
	size_t		_hoops_SAIRI;

	if (_hoops_SCARR)
		goto _hoops_PRSPR;


	// _hoops_HSPAR _hoops_RCAGA _hoops_AHSC _hoops_RIS _hoops_IACH
	for (long _hoops_GIARA = 0; _hoops_GIARA < _hoops_SCARI; _hoops_GIARA++) {
		_hoops_SAIRI = 0;

#define _hoops_GPIRI _hoops_SSAGI(60) // 60 _hoops_RPIRI

		if (pool->_hoops_AIPRI[_hoops_GIARA]._hoops_HPPRI > 0 &&
			*HOOPS_WORLD->time_stamp - pool->_hoops_AIPRI[_hoops_GIARA]._hoops_SPPRI > _hoops_GPIRI) {

			bool			_hoops_PCGS = _hoops_ISPRI(pool);
			_hoops_AIARI *	_hoops_HAPRI = pool->_hoops_AIPRI[_hoops_GIARA]._hoops_HAPRI;
			pool->_hoops_AIPRI[_hoops_GIARA]._hoops_HAPRI = null;
			pool->_hoops_AIPRI[_hoops_GIARA]._hoops_HPPRI=0;
			if (_hoops_PCGS)
				_hoops_CSPRI(pool);

			while (_hoops_HAPRI != null) {
				_hoops_AIARI *	_hoops_PSPRI = _hoops_HAPRI;
				_hoops_HAPRI = _hoops_PSPRI->_hoops_ARPRI;
				_hoops_SAIRI += _hoops_PSPRI->size;
				_hoops_PAHRI (_hoops_PSPRI, pool, true, 0);
			}
		}

		if (_hoops_SAIRI > 0) {
			bool	_hoops_PCGS = _hoops_ISPRI(pool);
			pool->_hoops_SIPRI -= _hoops_SAIRI;
			if (_hoops_PCGS)
				_hoops_CSPRI(pool);
		}

		if (HOOPS_WORLD->_hoops_ACARR->_hoops_APIRI())
			break;
	}

	_hoops_SAIRI=0;

	while (!HOOPS_WORLD->_hoops_ACARR->_hoops_APIRI() &&
			pool->_hoops_RCPRI > _hoops_PIARI) {

		bool			_hoops_PCGS = _hoops_ISPRI(pool);
		_hoops_AIARI *	_hoops_HAPRI = pool->_hoops_SHPRI;
		pool->_hoops_SHPRI = null;
		pool->_hoops_RCPRI = 0;
		if (_hoops_PCGS)
			_hoops_CSPRI(pool);

		while (_hoops_HAPRI != null) {
			_hoops_AIARI *		_hoops_PSPRI = _hoops_HAPRI;

			_hoops_HAPRI = _hoops_PSPRI->next;
			_hoops_SAIRI += _hoops_PSPRI->size;
			_hoops_AAHRI (pool, _hoops_PSPRI);
		}

		_hoops_CAIRI=0;
	}

	if (_hoops_SAIRI > 0) {
		bool	_hoops_PCGS = _hoops_ISPRI(pool);
		pool->_hoops_GCPRI -= _hoops_SAIRI;
		if (_hoops_PCGS)
			_hoops_CSPRI(pool);
	}

_hoops_PRSPR:
	if (_hoops_SCARR)
		delete this;
	else
		HOOPS_WORLD->_hoops_ACARR->_hoops_PCARR(this,_hoops_CAIRI);
};



THREAD_FUNCTION(task_queue_function) {
	_hoops_SRIAP *		_hoops_ACARR = THREAD_FUNCTION_DATA(_hoops_SRIAP *);

	HI_Set_Thread_Name (-1,
		_hoops_ACARR->_hoops_PPIRI()?"Hoops Updater":"Hoops Task Worker",
		_hoops_ACARR->_hoops_PPIRI());

	HThreadID thread_id = THREAD_ID();
	_hoops_AIGPR * _hoops_SPAIR = (_hoops_AIGPR *)1;
	LOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);
	HOOPS_WORLD->_hoops_RCPGI->InsertItem(thread_id,_hoops_SPAIR);
	UNLOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);

    while (1) {
		_hoops_GCARR * _hoops_HPIRI = _hoops_ACARR->_hoops_IAIRI();
		if (_hoops_HPIRI) {
			_hoops_GSPGR _hoops_CAIRI = _hoops_HPIRI->_hoops_IPIRI() - HI_What_Time();

			if (_hoops_CAIRI > 0)
				MILLI_SECOND_SLEEP(_hoops_CAIRI);

			_hoops_HPIRI->_hoops_HCARR(_hoops_ACARR->_hoops_APIRI());
		}
		else
			break;
    }

	//_hoops_CPIRI("_hoops_SRGIR %_hoops_CCAHR %_hoops_GHGP\_hoops_ACHP", (_hoops_SRPC *)_hoops_SPIRI, _hoops_SPIRI->_hoops_GHIRI);
	LOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);
	HOOPS_WORLD->_hoops_RCPGI->RemoveItem(thread_id);
	UNLOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);

	_hoops_ACARR->_hoops_RHIRI();
	//_hoops_CPIRI("_hoops_SRGIR %_hoops_CCAHR %_hoops_GHGP\_hoops_ACHP", (_hoops_SRPC *)_hoops_SPIRI, _hoops_SPIRI->_hoops_GHIRI);
	return 0;
}


HOOPS_API _hoops_SRIAP::_hoops_SRIAP(int in_thread_count, bool _hoops_AHIRI)
{
	_hoops_PHCHA = in_thread_count;
	_hoops_GCSIH = _hoops_AHIRI;

	_hoops_PHIRI = null;

	_hoops_HHIRI = 0;

	CREATE_MUTEX (_hoops_IHIRI);

	if (_hoops_PHCHA > 0) {
		HM_CONSTRUCT_SEMAPHORE (_hoops_CHIRI, _hoops_PHCHA+111, 0); //111 _hoops_HRGR _hoops_ARGS _hoops_PISA

		ZALLOC_ARRAY(_hoops_SHIRI, _hoops_PHCHA, HThreadHandle);

		LOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);
		if (!HOOPS_WORLD->_hoops_RCPGI)
			HOOPS_WORLD->_hoops_RCPGI = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_PRGGI)(HOOPS_WORLD->memory_pool);
		UNLOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);

		for (int i=0; i<_hoops_PHCHA; i++) {
			CREATE_THREAD(_hoops_SHIRI[i], task_queue_function, this);
		}
	}
}

HOOPS_API _hoops_SRIAP::~_hoops_SRIAP()
{
	_hoops_HHIRI = _hoops_PHCHA;

	//_hoops_CPIRI("_hoops_HCPCA %_hoops_CCAHR %_hoops_GHGP %_hoops_GHGP\_hoops_ACHP", (_hoops_SRPC *)_hoops_RGR, _hoops_GIIRI, _hoops_GHIRI);

	if (_hoops_PHCHA > 0) {
		/* _hoops_PGGC _hoops_AHSHA */
		HM_RELEASE_SEMAPHORE (_hoops_CHIRI, _hoops_PHCHA);
		while (_hoops_APIRI()) {
			MILLI_SECOND_SLEEP(10);
		}

// _hoops_RIIRI [#10032] _hoops_PPR [#11684]
#ifndef _MSC_VER
		// _hoops_HGI _hoops_RRGR _hoops_AIIRI _hoops_GGHC _hoops_IRS _hoops_SRPHP _hoops_GPP _hoops_PSCSR.
		for (int i = 0; i < _hoops_PHCHA; ++i) {
			JOIN_THREAD(_hoops_SHIRI[i]);
		}
#endif
		HM_DESTRUCT_SEMAPHORE(_hoops_CHIRI);
		FREE_ARRAY(_hoops_SHIRI, _hoops_PHCHA, HThreadID);
	}

	/* _hoops_SCAC _hoops_AISSA _hoops_HIGR */
	_hoops_GCARR *	_hoops_HPIRI;
	while ((_hoops_HPIRI = _hoops_PHIRI) != null) {
		_hoops_PHIRI = _hoops_HPIRI->_hoops_PIIRI;
		_hoops_HPIRI->_hoops_HCARR(true);
	}

	DESTROY_MUTEX(_hoops_IHIRI);
}

HOOPS_API void _hoops_SRIAP::_hoops_PCARR(_hoops_GCARR * _hoops_HPIRI, int _hoops_HIIRI)
{
	if (_hoops_PHCHA > 0 &&
		!BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP)) {

		// _hoops_IIIRI _hoops_CGPR _hoops_RGR _hoops_SRIPR
		// _hoops_AGHR(0);
		// _hoops_SCH _hoops_SRIPR _hoops_IH _hoops_AIRI _hoops_HIGR _hoops_GGAS

		_hoops_HPIRI->_hoops_HCARR(true);
		return;
	}

	if (_hoops_HIIRI == -1)
		_hoops_HPIRI->_hoops_CIIRI(0);
	else
		_hoops_HPIRI->_hoops_CIIRI(HI_What_Time()+_hoops_HIIRI);

	LOCK_MUTEX (_hoops_IHIRI);

	_hoops_GCARR *		_hoops_HCPSR = _hoops_PHIRI;
	_hoops_GCARR **		_hoops_ASRGR = &_hoops_PHIRI;

	while (_hoops_HCPSR && _hoops_HPIRI->_hoops_IPIRI() > _hoops_HCPSR->_hoops_IPIRI()) {
		_hoops_ASRGR = &_hoops_HCPSR->_hoops_PIIRI;
		_hoops_HCPSR = _hoops_HCPSR->_hoops_PIIRI;
	}

	*_hoops_ASRGR = _hoops_HPIRI;
	_hoops_HPIRI->_hoops_PIIRI = _hoops_HCPSR;

	UNLOCK_MUTEX (_hoops_IHIRI);

	if (_hoops_PHCHA > 0)
		HM_RELEASE_SEMAPHORE(_hoops_CHIRI, 1);
}

HOOPS_API _hoops_GCARR * _hoops_SRIAP::_hoops_IAIRI(_hoops_GCARR * _hoops_SIIRI)
{
	_hoops_GCARR *	_hoops_HPIRI = null;

	if (_hoops_SIIRI != null) {
		while (1) {
			if (_hoops_PHCHA > 0)
				HM_WAIT_SEMAPHORE (_hoops_CHIRI);
			LOCK_MUTEX (_hoops_IHIRI);

			_hoops_HPIRI = _hoops_PHIRI;
			_hoops_GCARR  **_hoops_ASRGR = &_hoops_PHIRI;
			while (_hoops_HPIRI && _hoops_HPIRI != _hoops_SIIRI) {
				_hoops_ASRGR = &_hoops_HPIRI->_hoops_PIIRI;
				_hoops_HPIRI = _hoops_HPIRI->_hoops_PIIRI;
			}
			if (_hoops_HPIRI != _hoops_SIIRI)
				_hoops_HPIRI=null;
			else {
				*_hoops_ASRGR = _hoops_HPIRI->_hoops_PIIRI;
				_hoops_HPIRI->_hoops_PIIRI = null;
			}

			UNLOCK_MUTEX (_hoops_IHIRI);
			if (_hoops_HPIRI)
				break;

			if (_hoops_PHCHA > 0)
				HM_RELEASE_SEMAPHORE(_hoops_CHIRI, 1);
		}
	}
	else {
		if (_hoops_PHCHA > 0)
			HM_WAIT_SEMAPHORE (_hoops_CHIRI);

		if (!_hoops_APIRI()) {
			LOCK_MUTEX (_hoops_IHIRI);
			_hoops_HPIRI = _hoops_PHIRI;
			if (_hoops_HPIRI) {
				_hoops_PHIRI = _hoops_HPIRI->_hoops_PIIRI;
				while (_hoops_PHIRI &&
						_hoops_HPIRI->Type() == _hoops_PHIRI->Type() &&
						_hoops_HPIRI->_hoops_GCIRI(_hoops_PHIRI)) {

					_hoops_GCARR * _hoops_RCIRI = _hoops_PHIRI;
					_hoops_PHIRI = _hoops_PHIRI->_hoops_PIIRI;
					delete _hoops_RCIRI;
				}
			}
			UNLOCK_MUTEX (_hoops_IHIRI);
		}
	}
	return _hoops_HPIRI;
}


GLOBAL_FUNCTION _hoops_CPGRR HI_Create_Mutex ()
{
	_hoops_CPGRR m;
	CREATE_MUTEX (m);
	return m;
}

GLOBAL_FUNCTION void HI_Destroy_Mutex (_hoops_CPGRR _hoops_RASCA)
{
	DESTROY_MUTEX (_hoops_RASCA);
}

//#_hoops_PPIP _hoops_ACIRI
#ifdef _hoops_PCIRI

struct _hoops_HCIRI {
	_hoops_HCIRI *	next;
};

struct _hoops_ICIRI {
	_hoops_HCIRI volatile *	top;
#if	defined(_hoops_CHAGP) || defined(_hoops_IIIPA) || (defined(_hoops_HIAGP) && defined(__i386__))
	POINTER_SIZED_INT		version;
#endif
};

#if defined(_M_X64)
#	define	_hoops_CCIRI	_InterlockedCompareExchange64
#else
#	define	_hoops_CCIRI	_InterlockedCompareExchange
#endif

local INLINE void _hoops_SCIRI (_hoops_ICIRI * _hoops_GSIRI, _hoops_HCIRI * item)
{
	item->next = (_hoops_HCIRI *)_hoops_GSIRI->top;
	_hoops_GSIRI->top = item;
}

local INLINE void _hoops_RSIRI (_hoops_ICIRI * _hoops_GSIRI, _hoops_HCIRI * item)
{
#if defined(_hoops_CHAGP)
	while (1) {
		item->next = (_hoops_HCIRI *)_hoops_GSIRI->top;
		if ((POINTER_SIZED_INT)item->next ==
			_hoops_CCIRI ((POINTER_SIZED_INT volatile *)&_hoops_GSIRI->top,
			(POINTER_SIZED_INT)item,
			(POINTER_SIZED_INT)item->next))
			break;
	}
#elif	defined(_hoops_IIIPA)
	__asm {
		mov				edi, _hoops_GSIRI		; edi = _hoops_GSIRI
			mov				eax, [edi]		; eax = _hoops_GSIRI->top
			mov				ebx, item		; ebx = item
_hoops_RPHRI:
		mov				[ebx], eax		; _hoops_ASIRI: item->next = top
			lock _hoops_PSIRI	[edi], ebx		; _hoops_HSIRI _hoops_GSIRI->top = item, if _hoops_GSIRI->top _hoops_ISIRI == eax
			_hoops_CSIRI				_hoops_RPHRI			; _hoops_GAPCA, eax: _hoops_SACRH _hoops_GSIRI->top
	}
#elif defined(_hoops_HIAGP) && defined(__i386__)
	while (1) {
		item->next = _hoops_GSIRI->top;
		if (_hoops_SSIRI (&_hoops_GSIRI->top, item, item->next))
			break;
	}
#else
	_hoops_CAAI (HOOPS_WORLD->_hoops_PIPSA);
	item->next = _hoops_GSIRI->top;
	_hoops_GSIRI->top = item;
	_hoops_APAI (HOOPS_WORLD->_hoops_PIPSA);
#endif
}

local INLINE _hoops_HCIRI * _hoops_GGCRI (_hoops_ICIRI * _hoops_GSIRI)
{
	_hoops_HCIRI *	result = 0;
	result = (_hoops_HCIRI *)_hoops_GSIRI->top;
	if (result != null)
		_hoops_GSIRI->top = result->next;
	return result;
}

local INLINE void _hoops_RGCRI(_hoops_ICIRI * _hoops_GSIRI, unsigned Integer32 * count)
{
	_hoops_HCIRI *	head;
	_hoops_HCIRI *	_hoops_AGCRI;
	unsigned Integer32		n;

	do {
		n = 0;
		_hoops_AGCRI = head = (_hoops_HCIRI *)_hoops_GSIRI->top;
		while (_hoops_AGCRI != 0) {
			++n;
			_hoops_AGCRI = _hoops_AGCRI->next;
		}
		*count = n;
	} while (head != _hoops_GSIRI->top);
}

local INLINE _hoops_HCIRI * _hoops_PGCRI (_hoops_ICIRI * _hoops_GSIRI)
{
	_hoops_HCIRI *	result = 0;

#if defined(_hoops_CHAGP)
	_hoops_ICIRI _hoops_HGCRI;
	_hoops_ICIRI _hoops_IGCRI;
	while (1) {
		_hoops_IGCRI = *_hoops_GSIRI;
		if (_hoops_IGCRI.top == null)
			break;
		_hoops_HGCRI.top = _hoops_IGCRI.top->next;
		_hoops_HGCRI.version = _hoops_IGCRI.version;
		_hoops_HGCRI.version++;
#if defined(_M_X64)
		if (_InterlockedCompareExchange128 ((__int64 volatile *)&_hoops_GSIRI,
			(__int64)_hoops_HGCRI.version,
			(__int64)_hoops_HGCRI.top,
			(__int64*)&_hoops_IGCRI))
			break;
#else
		__int64 _hoops_RCAGP = (__int64)*(__int64*)&_hoops_HGCRI;
		__int64 compare = (__int64)*(__int64*)&_hoops_IGCRI;

		__int64 _hoops_HRSSA = _InterlockedCompareExchange64 ((__int64 volatile *)_hoops_GSIRI, _hoops_RCAGP, compare);

		if (compare == _hoops_HRSSA)
			break;
#endif
	}
	result = (_hoops_HCIRI *)_hoops_IGCRI.top;
#elif	defined(_hoops_IIIPA)
	__asm {
		mov				edi, _hoops_GSIRI		; edi = _hoops_GSIRI
			mov				eax, [edi]		; eax = _hoops_GSIRI->top
			mov				edx, [edi+4]	; edx = _hoops_GSIRI->version
_hoops_RPHRI:
		test			eax, eax
			jz				done
			mov				ebx, [eax];		; ebx = _hoops_GSIRI->top->next
			mov				ecx, edx		; ecx = _hoops_GSIRI->version
			inc				ecx				;					 + 1
			lock _hoops_CGCRI	[edi]			; _hoops_HSIRI _hoops_GSIRI->top = _hoops_GSIRI->top->next;
		_hoops_CSIRI				_hoops_RPHRI			; _hoops_GAPCA, eax = _hoops_SACRH _hoops_GSIRI->top, edx = _hoops_SACRH _hoops_GSIRI->version
done:
		mov				result, eax
	}
#elif defined(_hoops_HIAGP) && defined(__i386__)
	_hoops_ICIRI _hoops_HGCRI;
	_hoops_ICIRI _hoops_IGCRI;
	while (1) {
		_hoops_IGCRI = *_hoops_GSIRI;
		if (_hoops_IGCRI.top == null)
			break;
		_hoops_HGCRI.top = _hoops_GSIRI->top->next;
		_hoops_HGCRI.version = _hoops_GSIRI->version;
		_hoops_HGCRI.version++;

		if (_hoops_SSIRI(
			(long long *)&_hoops_GSIRI,
			(long long)*(long long *)&_hoops_HGCRI,
			(long long)*(long long *)&_hoops_IGCRI))
			break;
	}
#else
	_hoops_CAAI (HOOPS_WORLD->_hoops_PIPSA);
	result = _hoops_GSIRI->top;
	if (result != null)
		_hoops_GSIRI->top = result->next;
	_hoops_APAI (HOOPS_WORLD->_hoops_PIPSA);
#endif
	return result;
}


local INLINE _hoops_HCIRI * _hoops_SGCRI (_hoops_ICIRI * _hoops_GSIRI)
{
	_hoops_HCIRI *	result = 0;
	result = (_hoops_HCIRI *)_hoops_GSIRI->top;
	_hoops_GSIRI->top = 0;
	return result;
}

local INLINE _hoops_HCIRI * _hoops_GRCRI (_hoops_ICIRI * _hoops_GSIRI)
{
	_hoops_HCIRI *		result = 0;
#if defined(_hoops_CHAGP)
	while (1) {
		result = (_hoops_HCIRI *)_hoops_GSIRI->top;
		if ((POINTER_SIZED_INT)result ==
			_hoops_CCIRI ((POINTER_SIZED_INT volatile *)&_hoops_GSIRI->top,
			(POINTER_SIZED_INT)0,
			(POINTER_SIZED_INT)result))
			break;
	}
#elif	defined(_hoops_IIIPA)
	__asm {
		mov				edi, _hoops_GSIRI		; edi = _hoops_GSIRI
			mov				eax, [edi]		; eax = _hoops_GSIRI->top
			xor				ebx, ebx		; ebx = 0
_hoops_RPHRI:
		lock _hoops_PSIRI	[edi], ebx		; _hoops_HSIRI _hoops_GSIRI->top = 0, if _hoops_GSIRI->top _hoops_ISIRI == eax
			_hoops_CSIRI				_hoops_RPHRI			; _hoops_GAPCA, eax: _hoops_SACRH _hoops_GSIRI->top

			mov				result, eax
	}
#elif defined(_hoops_HIAGP) && defined(__i386__)
	while (1) {
		result = _hoops_GSIRI->top;
		if (_hoops_SSIRI (&_hoops_GSIRI->top, 0, result))
			break;
	}
#else
	_hoops_CAAI (HOOPS_WORLD->_hoops_PIPSA);
	result = _hoops_GSIRI->top;
	_hoops_GSIRI->top = null;
	_hoops_APAI (HOOPS_WORLD->_hoops_PIPSA);
#endif
	return result;
}

#endif

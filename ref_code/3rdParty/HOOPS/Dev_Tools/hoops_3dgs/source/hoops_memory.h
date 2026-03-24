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
 * $Id: hoops_memory.h,v 1.58 2010-12-06 22:05:41 jason Exp $
 */

#ifndef HOOPS_MEMORY_DEFINED

GLOBAL_FUNCTION void HI_Free_Array(
	void *			p, 
	size_t			size,
	const char *	file, 
	int				line);

GLOBAL_FUNCTION void* HI_Alloc_Array(
	size_t			size, 
	bool			try_alloc, 
	bool			cache_big_blocks, 
	Memory_Pool *	mempool, 
	const char *	type_name, 
	const char *	file, 
	int				line);

GLOBAL_FUNCTION void * HI_System_Alloc (size_t size);
GLOBAL_FUNCTION void HI_System_Free (void *pntr);

#define MPF_NONE			0x00000000
#define MPF_LOCKING			0x00000001
#define MPF_BIG_BLOCKS		0x00000002
#define MPF_SUPER_BIG_BLOCK	0x00000004
#define MPF_RECYCLER		0x00000008

#define MPF_DEFAULT	(MPF_LOCKING|MPF_BIG_BLOCKS|MPF_SUPER_BIG_BLOCK|MPF_RECYCLER)

GLOBAL_FUNCTION Memory_Pool alter * HI_Create_Memory_Pool(Integer32 flags);
GLOBAL_FUNCTION bool HI_Destroy_Memory_Pool(Memory_Pool alter * pool);
GLOBAL_FUNCTION Memory_Pool * HI_Fetch_Pool(void* p, size_t size);

GLOBAL_FUNCTION void HI_Use_Memory_Task(Memory_Pool alter * pool, bool use_one);

GLOBAL_FUNCTION void HI_Set_System_Memory_Functions();
GLOBAL_FUNCTION void HI_Show_Memory_Usage(long *allocated, long *used);

GLOBAL_FUNCTION size_t HI_Memory_On_Pool (Memory_Pool *memory_pool, size_t * allocated=0, size_t *used=0);
GLOBAL_FUNCTION void HI_Relinquish_Memory_On_Pool (Memory_Pool * pool);

GLOBAL_FUNCTION void HI_Dump_Allocation_Metadata(Memory_Pool alter *pool, const char * message);

#define	H_ALLOC_ARRAY(_p, _size, _type, _trying, _cache_big_blocks, _mempool, _type_name, _file, _line) do { \
		size_t _size_ = _size; \
		if (BIT (HOOPS_WORLD->system_flags, Sysop_RAW_MEMORY)) { \
			_p = (_type *)(*HOOPS_WORLD->malloc)(_size_); \
			HOOPS_WORLD->raw_memory_usage += _size_; \
		} else { \
			_p = (_type *)HI_Alloc_Array(_size_, _trying, _cache_big_blocks, _mempool, _type_name, _file, _line); \
		} \
	} while (0)

#define H_FREE_ARRAY(_p, _size, _file, _line) do { \
	size_t _size_ = (_size); \
	ASSERT(_p != 0); \
	ASSERT(_size_ > 0); \
	if (BIT (HOOPS_WORLD->system_flags, Sysop_RAW_MEMORY)) { \
		HOOPS_WORLD->raw_memory_usage -= _size_; \
		(*HOOPS_WORLD->free)((void*)_p); \
	} else { \
		HI_Free_Array((void*)_p, _size_, _file, _line); \
	} \
} while (0)


#define FREE(p, type) \
	H_FREE_ARRAY (p, sizeof(type), __FILE__,__LINE__)
#define FREE_ARRAY(p, count, type) \
	H_FREE_ARRAY (p, (count)*sizeof(type), __FILE__,__LINE__)

#define ALLOC(p, type) \
	H_ALLOC_ARRAY (p, sizeof(type), type, false, false, HOOPS_WORLD->memory_pool, #type, __FILE__, __LINE__)
#define ALLOC_ARRAY(p, count, type) \
	H_ALLOC_ARRAY (p, (count)*sizeof(type), type, false, false,HOOPS_WORLD->memory_pool, #type, __FILE__, __LINE__)
#define TRY_ALLOC_ARRAY(p, count, type) \
	H_ALLOC_ARRAY (p, (count)*sizeof(type), type, true, false, HOOPS_WORLD->memory_pool, #type, __FILE__, __LINE__)

// Use only for draw time temps not database
#define ALLOC_CACHED(p, type) \
	H_ALLOC_ARRAY (p, sizeof(type), type, false, true, HOOPS_WORLD->memory_pool, #type, __FILE__, __LINE__)
#define ALLOC_ARRAY_CACHED(p, count, type) \
	H_ALLOC_ARRAY (p, (count)*sizeof(type), type, false, true,HOOPS_WORLD->memory_pool, #type, __FILE__, __LINE__)
#define TRY_ALLOC_ARRAY_CACHED(p, count, type) \
	H_ALLOC_ARRAY (p, (count)*sizeof(type), type, true, true, HOOPS_WORLD->memory_pool, #type, __FILE__, __LINE__)

#define POOL_ALLOC(p, type, mempool) \
	H_ALLOC_ARRAY (p, sizeof(type), type, false, false, mempool, #type, __FILE__, __LINE__)
#define POOL_ALLOC_ARRAY(p, count, type, mempool) \
	H_ALLOC_ARRAY (p, (count)*sizeof(type), type, false, false, mempool, #type, __FILE__, __LINE__)
#define POOL_TRY_ALLOC_ARRAY(p, count, type, mempool) \
	H_ALLOC_ARRAY (p, (count)*sizeof(type), #type, type, true, false, mempool, #type, __FILE__, __LINE__)

#define POOL_ALLOC_CACHED(p, type, mempool) \
	H_ALLOC_ARRAY (p, sizeof(type), type, false, true, mempool, #type, __FILE__, __LINE__)
#define POOL_ALLOC_ARRAY_CACHED(p, count, type, mempool) \
	H_ALLOC_ARRAY (p, (count)*sizeof(type), type, false, true, mempool, #type, __FILE__, __LINE__)
#define POOL_TRY_ALLOC_ARRAY_CACHED(p, count, type, mempool) \
	H_ALLOC_ARRAY (p, (count)*sizeof(type), type, true, true, mempool, #type, __FILE__, __LINE__)



#define	ZALLOC(_dst_, _type_)	do {					\
			ALLOC (_dst_, _type_);						\
			ZERO_STRUCT ((void *)_dst_, _type_);		\
		} while (0)
#define	ZALLOC_ARRAY(_dst_, _cnt_, _type_)	do {		\
			ALLOC_ARRAY (_dst_, _cnt_, _type_);			\
			ZERO_ARRAY ((void *)_dst_, _cnt_, _type_);	\
		} while (0)

#define	ZALLOC_CACHED(_dst_, _type_)	do {					\
			ALLOC_CACHED (_dst_, _type_);						\
			ZERO_STRUCT ((void *)_dst_, _type_);		\
		} while (0)
#define	ZALLOC_ARRAY_CACHED(_dst_, _cnt_, _type_)	do {		\
			ALLOC_ARRAY_CACHED (_dst_, _cnt_, _type_);			\
			ZERO_ARRAY ((void *)_dst_, _cnt_, _type_);	\
		} while (0)


#define	POOL_ZALLOC(_dst_, _type_, _pool_)	do {					\
			POOL_ALLOC (_dst_, _type_, _pool_);						\
			ZERO_STRUCT ((void *)_dst_, _type_);		\
		} while (0)
#define	POOL_ZALLOC_ARRAY(_dst_, _cnt_, _type_, _pool_)	do {		\
			POOL_ALLOC_ARRAY (_dst_, _cnt_, _type_, _pool_);			\
			ZERO_ARRAY ((void *)_dst_, _cnt_, _type_);	\
		} while (0)

#define	POOL_ZALLOC_CACHED(_dst_, _type_, _pool_)	do {					\
			POOL_ALLOC_CACHED (_dst_, _type_, _pool_);						\
			ZERO_STRUCT ((void *)_dst_, _type_);		\
		} while (0)

#define	POOL_ZALLOC_ARRAY_CACHED(_dst_, _cnt_, _type_, _pool_)	do {		\
			POOL_ALLOC_ARRAY_CACHED (_dst_, _cnt_, _type_, _pool_);			\
			ZERO_ARRAY ((void *)_dst_, _cnt_, _type_);	\
		} while (0)

/* calculates the number that we would need to add to i to get the next multiple of n */
#define TO_NEXT_MULTIPLE(i,n) (((n)-1) - ((((unsigned POINTER_SIZED_INT)(i))-1)%(n))) 


#define POOL_ALLOC_ARRAY_ALIGNED(var, count, type, align_in, _pool_) do { \
		if (align_in <= (1<<ALIGNMENT)) \
			POOL_ALLOC_ARRAY(var, count, type, _pool_); \
		else { \
			unsigned char *_uc_, _offset_; \
			H_ALLOC_ARRAY(_uc_, (count)*sizeof(type) + align_in, unsigned char, false, false, _pool_,  #type, __FILE__, __LINE__); \
			_uc_ += 1; \
			_offset_ = 1 + TO_NEXT_MULTIPLE(_uc_, align_in); \
			_uc_ += _offset_ - 1; \
			_uc_[-1] = _offset_; \
			var = (type *)_uc_; \
		} \
	} while (0)


#define POOL_ALLOC_ARRAY_ALIGNED_CACHED(var, count, type, align_in, _pool_) do { \
		if (align_in <= (1<<ALIGNMENT)) \
			POOL_ALLOC_ARRAY_CACHED(var, count, type, _pool_); \
		else { \
			unsigned char *_uc_, _offset_; \
			H_ALLOC_ARRAY(_uc_, (count)*sizeof(type) + align_in, unsigned char, false, true, _pool_, #type, __FILE__,__LINE__); \
			_uc_ += 1; \
			_offset_ = 1 + TO_NEXT_MULTIPLE(_uc_, align_in); \
			_uc_ += _offset_ - 1; \
			_uc_[-1] = _offset_; \
			var = (type *)_uc_; \
		} \
	} while (0)


#define FREE_ARRAY_ALIGNED(var, count, type, align_in) do { \
		if (align_in <= (1<<ALIGNMENT)) \
			FREE_ARRAY(var, count, type); \
		else { \
			unsigned char *_uc_, _offset_; \
			_uc_ = (unsigned char *)var; \
			_offset_ = _uc_[-1]; \
			_uc_ -= _offset_; \
			H_FREE_ARRAY(_uc_, (count)*sizeof(type)+align_in, __FILE__,__LINE__); \
		} \
	} while (0)

#define POOL_ALLOC_ALIGNED(p, type, align_in, _pool_)	POOL_ALLOC_ARRAY_ALIGNED(p, 1, type, align_in, _pool_)

#define ALLOC_ARRAY_ALIGNED(var, count, type, align_in) POOL_ALLOC_ARRAY_ALIGNED(var, count, type, align_in, HOOPS_WORLD->memory_pool)
#define ALLOC_ARRAY_ALIGNED_CACHED(var, count, type, align_in) POOL_ALLOC_ARRAY_ALIGNED_CACHED(var, count, type, align_in, HOOPS_WORLD->memory_pool)

#define ALLOC_ALIGNED(p, type, align_in)	POOL_ALLOC_ALIGNED(p, type, align_in, HOOPS_WORLD->memory_pool)
#define FREE_ALIGNED(p, type, align_in)		FREE_ARRAY_ALIGNED(p, 1, type, align_in)


/* used to derive a 16-byte aligned address (usually to select a safe address from within a larger buffer) */
#define	ALIGNED_16(x)	(((unsigned POINTER_SIZED_INT)(x) + 15) & ~(unsigned POINTER_SIZED_INT)0x00F)


Begin_HOOPS_Namespace

class HOOPS_API CMO {
public:
	virtual ~CMO() {}

	INLINE void alter * operator new (size_t size, const char* type_name, const char* file, int line) {
		void * p;
		H_ALLOC_ARRAY (p, size,  unsigned char, false, false, HOOPS_WORLD->memory_pool, type_name, file, line);
		SET_MEMORY (p, size, 0);
		return p;
	}

	INLINE void operator delete (void alter * p, size_t size) throw () {
		H_FREE_ARRAY(p, size, __FILE__, __LINE__);
	}

private:
	static void alter *	operator new [] (size_t size);
	static void alter *	operator new (size_t size);
};

// use only for draw time temps like renditions, not for database
class HOOPS_API CMO_Pooled {
public:
	virtual ~CMO_Pooled() {}

	INLINE void alter * operator new (size_t size, Memory_Pool * pool, const char* type, const char* file, int line) {
		void * p;
		H_ALLOC_ARRAY (p, size, unsigned char, false, true, pool, type, file, line);
		SET_MEMORY (p, size, 0);
		return p;
	}

	INLINE void operator delete (void alter * p, size_t size) throw () {
		H_FREE_ARRAY(p, size, __FILE__, __LINE__);
	}

private:
	static void alter *	operator new [] (size_t size);
	static void alter *	operator new (size_t size);
};

// use only for draw time temps like renditions, not for database
class HOOPS_API CMO_Pooled_Copyable : public CMO_Pooled {
public:
	Memory_Pool *	memory_pool;

	CMO_Pooled_Copyable (Memory_Pool * pool) : memory_pool (pool) {}
	CMO_Pooled_Copyable (CMO_Pooled_Copyable const & x) : memory_pool (x.memory_pool) {}
	virtual ~CMO_Pooled_Copyable() {}

private:
	CMO_Pooled_Copyable();
};

#ifdef VALIDATE_MEMORY
#	define NEW(_type_) new (#_type_, __FILE__, __LINE__) (_type_)
#	define POOL_NEW(_pool_, _type_) new ((_pool_), #_type_, __FILE__, __LINE__) (_type_)
#else 
#	define NEW(_type_) new (0, 0, 0) (_type_)
#	define POOL_NEW(_pool_, _type_) new ((_pool_), 0, 0, 0) (_type_)
#endif

#define SYSTEM_NEW new

End_HOOPS_Namespace;
Use_HOOPS_Namespace;


#define HOOPS_MEMORY_DEFINED
#endif









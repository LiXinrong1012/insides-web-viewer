#ifndef _VDS_VMEMMGR_H_
#define  _VDS_VMEMMGR_H_

#include "Vds_Core_Def.h"
#include "vds_datatypes.h"
#include "vds_structures.h"

struct V_LINK;


class VMemMgr
{
	public:

	VUDWORD udwTotalAllocMem;

	V_LINK  *pFreeListTable;
	VUDWORD udwFreeListSize;
	
	V_LINK  *pAllocBlocksList;
	
	void * pCurFreeBlock;
	VUDWORD udwCurBlockSize; 

	VUDWORD udwMissedAllocCount; 
	
	public:
	VMemMgr(VUDWORD udwFLSize);
	~VMemMgr();
	void*	alloc(VUDWORD size);	
	void	free(void *pData);	

	private:
	void addToAllocList(VUBYTE *pMem);
	void addToFreeList(VUBYTE *pData, VUDWORD udwFLIndex);
	void* getFromFreeList(VUDWORD udwFLIndex);
};


#endif 
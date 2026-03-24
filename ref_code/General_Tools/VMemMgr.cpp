#include "vmemmgr.h"
#include "vds_mem.h"



VMemMgr::VMemMgr(VUDWORD udwFLSize)
{
	pFreeListTable = NULL;
	udwFreeListSize = 0;
	udwMissedAllocCount = 0;



	//init
	udwFreeListSize = udwFLSize;
	pFreeListTable = (V_LINK*)vmalloc(udwFreeListSize*sizeof(V_LINK));
	memset(pFreeListTable,0,sizeof(V_LINK)*udwFreeListSize);
	pAllocBlocksList = (V_LINK*)vmalloc(sizeof(V_LINK));
	memset(pAllocBlocksList,0,sizeof(V_LINK));

	pCurFreeBlock = vmalloc(udwFreeListSize*8+4);
	udwCurBlockSize =udwFreeListSize*8+4; 

	addToAllocList((VUBYTE*)pCurFreeBlock);

	udwTotalAllocMem = udwFreeListSize*8+4;
}

VMemMgr::~VMemMgr()
{
	V_LINK *pCurLink,*pTmpLink;

	if(pFreeListTable)
	{
		for(VUDWORD i=0;i<udwFreeListSize;i++)
		{
			pCurLink = pFreeListTable[i].pNext;

			while(pCurLink)
			{
				pTmpLink = pCurLink;
				pCurLink = pCurLink->pNext;
				vfree(pTmpLink);
			}
		}		
		vfree(pFreeListTable);
		
	}


	pCurLink = pAllocBlocksList;
	while(pCurLink)
	{
		pTmpLink = pCurLink;
		pCurLink = pCurLink->pNext;

		if(pTmpLink->pData)
			vfree(pTmpLink->pData);
		vfree(pTmpLink);
	}
	
}


void*	VMemMgr::alloc(VUDWORD size)
{
	VUBYTE *pMemPtr=NULL;
	VUDWORD udwFreeListIndex;
	VUDWORD udwSize;
	VUDWORD *pudwSizePtr;
	
	udwSize = size + (8-size%8);
	udwFreeListIndex  = (udwSize+7)/8 - 1;

	if(udwFreeListIndex>=udwFreeListSize)
	{
		pMemPtr = (VUBYTE *)vmalloc(udwSize+4);
		udwTotalAllocMem += udwSize+4;

		pudwSizePtr = (VUDWORD *)pMemPtr;
		*pudwSizePtr = udwSize;
		addToAllocList(pMemPtr);

		pMemPtr = (VUBYTE *)((VUDWORD)pMemPtr+4);
	}
	else if(pMemPtr = (VUBYTE *)getFromFreeList(udwFreeListIndex))
	{
	}
	else if(udwSize+4<=udwCurBlockSize)
	{
		pMemPtr = (VUBYTE*)pCurFreeBlock;
		pudwSizePtr = (VUDWORD *)pMemPtr;
		*pudwSizePtr = udwSize;

		pMemPtr = (VUBYTE *)((VUDWORD)pMemPtr+4);
		udwCurBlockSize = udwCurBlockSize-(udwSize+4);
		pCurFreeBlock = (void*)((VUDWORD)pCurFreeBlock+udwSize+4);
	}
	else
	{
		pMemPtr = (VUBYTE *)vmalloc(udwSize+4);
		udwTotalAllocMem += udwSize+4;

		pudwSizePtr = (VUDWORD *)pMemPtr;
		*pudwSizePtr = udwSize;
		addToAllocList(pMemPtr);

		pMemPtr = (VUBYTE *)((VUDWORD)pMemPtr+4);

		udwMissedAllocCount++;
		if(udwMissedAllocCount>=3)
		{
			if(udwCurBlockSize>=12)
			{
				udwCurBlockSize =  udwCurBlockSize- 4;
				udwSize = udwCurBlockSize - (udwCurBlockSize%8);
				udwFreeListIndex  = (udwSize+7)/8 - 1;

				pudwSizePtr = (VUDWORD *)pCurFreeBlock;
				*pudwSizePtr = udwSize;
				addToFreeList((VUBYTE*)((VUDWORD)pCurFreeBlock+4),udwFreeListIndex);
			}

			pCurFreeBlock = vmalloc(udwFreeListSize*8+4);
			udwTotalAllocMem += udwFreeListSize*8+4;

			udwCurBlockSize =udwFreeListSize*8+4; 
			addToAllocList((VUBYTE*)pCurFreeBlock);
			udwMissedAllocCount = 0;
		}
	}

	return (void*)pMemPtr;
}	

void	VMemMgr::free(void *pData)
{
	V_LINK *pCurLink,*pTmpLink;
	VUBYTE* pMemPtr;
	VUDWORD udwFreeListIndex;
	VUDWORD udwSize;	
	pMemPtr = (VUBYTE*)((VUBYTE*)pData-4);
	udwSize = (VUDWORD)(*((VUDWORD*)(pMemPtr)));

	udwFreeListIndex  = (udwSize+7)/8 - 1;

	if(udwFreeListIndex>=udwFreeListSize)
	{
		pCurLink = pAllocBlocksList;
		if(pCurLink->pData == pMemPtr)
		{
			vfree(pMemPtr);
			if(pCurLink->pNext)
			{
				pCurLink->pData = pCurLink->pNext->pData;
				pCurLink->pNext = pCurLink->pNext->pNext;
			}
			else
			{
				pCurLink->pData = NULL;
				pCurLink->pNext = NULL;
			}
		}
		else
		{
			while(pCurLink->pNext)
			{
				pTmpLink = pCurLink->pNext;
				if(pTmpLink->pData == pMemPtr)
				{
					vfree(pMemPtr);
					pCurLink->pNext = pTmpLink->pNext;
					vfree(pTmpLink);
					break;
				}
				pCurLink = pCurLink->pNext;
			}
		}
	}
	else
	{
		addToFreeList((VUBYTE*)pData,udwFreeListIndex);
	}
}


void VMemMgr::addToAllocList(VUBYTE *pData)
{

	V_LINK *pCurLink = pAllocBlocksList;
	if(pCurLink->pData==NULL)
	{
		pCurLink->pData = pData;
		pCurLink->pNext = NULL;
	}
	else
	{
		V_LINK *pTmpLink = (V_LINK*)vmalloc(sizeof(V_LINK));
		if(pTmpLink)
		{
			pTmpLink->pData = pData;
			pTmpLink->pNext = pCurLink->pNext;
			pCurLink->pNext  =pTmpLink;
		}
	}
}


void VMemMgr::addToFreeList(VUBYTE *pData, VUDWORD udwFLIndex)
{

	V_LINK *pCurLink = &(pFreeListTable[udwFLIndex]);
	if(pCurLink->pData==NULL)
	{
		pCurLink->pData = pData;
		pCurLink->pNext = NULL;
	}
	else
	{
		V_LINK *pTmpLink = (V_LINK*)vmalloc(sizeof(V_LINK));
		if(pTmpLink)
		{
			pTmpLink->pData = pData;
			pTmpLink->pNext = pCurLink->pNext;
			pCurLink->pNext  =pTmpLink;
		}
	}
}

void* VMemMgr::getFromFreeList(VUDWORD udwFLIndex)
{
	void *pMemPtr = NULL;
	if(udwFLIndex>=udwFreeListSize)
		return pMemPtr;

	V_LINK *pCurLink = &(pFreeListTable[udwFLIndex]);
	if(pCurLink->pData!=NULL)
	{
		V_LINK *pTmpLink;
		pMemPtr = pCurLink->pData;
		if(pCurLink->pNext ==NULL)
			pCurLink->pData = NULL;
		else
		{
			pTmpLink = pCurLink->pNext;
			pCurLink->pData = pCurLink->pNext->pData;
			pCurLink->pNext = pCurLink->pNext->pNext;
			vfree(pTmpLink);
		}
	}
	return pMemPtr;
}


// Dummy MemMgr for checking
/*
void*	VMemMgr::alloc(VUDWORD size)
{
	return vmalloc(size);
}	

void	VMemMgr::free(void *pData)
{
	vfree(pData);
}
*/
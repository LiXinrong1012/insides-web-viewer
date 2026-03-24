#include "hash.h"




VHash::VHash(VUDWORD udwSize,VUDWORD (*funcPtrId )(void *data),VUDWORD (*funcPtrComp )(void *data1,void* data2),VMemMgr *pMemMgr)
{
	init(udwSize,funcPtrId,funcPtrComp,pMemMgr);
}

VHash::~VHash()
{

	V_LINK *pCurLink,*pTmpLink;
	for(VUDWORD i=0;i<udwHashSize;i++)
	{
		pCurLink = pHashLinkTable[i].pNext;
		while(pCurLink)
		{
			pTmpLink = pCurLink;
			pCurLink = pCurLink->pNext;
			pMemAllocMgr->free(pTmpLink);
			//delete pTmpLink;
		}
	}

	if(pHashLinkTable)
	{
		pMemAllocMgr->free(pHashLinkTable);
		//delete[] pHashLinkTable;
	}

}

void VHash::init(VUDWORD udwSize,VUDWORD (*funcPtrId )(void *data),VUDWORD (*funcPtrComp )(void *data1,void* data2),VMemMgr *pMemMgr)
{
	pHashLinkTable = NULL;
	udwHashSize = 0;
	fpId = NULL;

	udwCurTravIndex = 0;
	pCurTravLink = NULL;

	udwCount =0;

	//init
	udwHashSize = udwSize;
	fpId = funcPtrId;
	fpComp = funcPtrComp;

	pMemAllocMgr = pMemMgr;
	
	pHashLinkTable = (V_LINK*)pMemAllocMgr->alloc(udwHashSize *sizeof(V_LINK));
	//pHashLinkTable = new V_LINK[udwHashSize];

	memset(pHashLinkTable,0,sizeof(V_LINK)*udwHashSize);
}

bool VHash::insert(void *pData)
{
	if(pData == NULL)
		return false;

	V_LINK *pIdLink;
	VUDWORD udwId,udwIndex;
	udwId = (*fpId)(pData);
	udwIndex = udwId%udwHashSize;

	pIdLink = &(pHashLinkTable[udwIndex]);

	if(pIdLink->pData==NULL)
	{
		pIdLink->pData = pData;
		pIdLink->pNext = NULL;
	}
	else
	{
		V_LINK *pCurLink;
		pCurLink = pIdLink;
		while(pCurLink->pNext!=NULL)
		{
			if(udwId == (*fpId)(pCurLink->pData))
			{
				if(!fpComp)
					return false;
				else
				{
					if((*fpComp)(pCurLink->pData,pData)==0)
						return false;
				}
			}
			pCurLink = pCurLink->pNext;
		}

		if(udwId == (*fpId)(pCurLink->pData))
		{
			if(!fpComp)
				return false;
			else
			{
				if((*fpComp)(pCurLink->pData,pData)==0)
					return false;
			}
		}

		V_LINK *pTmpLink = (V_LINK*)pMemAllocMgr->alloc(sizeof(V_LINK));
		//V_LINK *pTmpLink = new V_LINK();
		pTmpLink->pData = pData;
		pTmpLink->pNext = NULL;
		pCurLink->pNext = pTmpLink;
	}
	udwCount++;
	return true;
}

void* VHash::get(void *pData)
{
	V_LINK *pIdLink;
	VUDWORD udwId,udwIndex;
	udwId = (*fpId)(pData);
	udwIndex = udwId%udwHashSize;

	pIdLink = &(pHashLinkTable[udwIndex]);

	if(pIdLink->pData!=NULL)
	{
		if(pIdLink->pNext==NULL)
		{
			if(udwId == (*fpId)(pIdLink->pData))
			{
				if(!fpComp)
					return 	pIdLink->pData;
				else
				{
					if((*fpComp)(pIdLink->pData,pData)==0)
						return 	pIdLink->pData;
				}
			}
		}
		else
		{
			V_LINK *pCurLink;
			pCurLink = pIdLink;
			while(pCurLink)
			{
				if(udwId == (*fpId)(pCurLink->pData))
				{
					if(!fpComp)
						return 	pCurLink->pData;
					else
					{
						if((*fpComp)(pCurLink->pData,pData)==0)
							return 	pCurLink->pData;
					}
				}
				pCurLink = pCurLink->pNext;
			}
		}
	}

	return NULL;

}

void  VHash::reset()
{
	udwCurTravIndex = 0;
	pCurTravLink = &(pHashLinkTable[0]);

	if(pCurTravLink->pData==NULL)
	{
		udwCurTravIndex++;
		while(udwCurTravIndex<udwHashSize)
		{
			pCurTravLink = &(pHashLinkTable[udwCurTravIndex]);
			if(pCurTravLink->pData)
				break;
			udwCurTravIndex++;
		}
		if(udwCurTravIndex>=udwHashSize)
			pCurTravLink = NULL;
	}
}

void* VHash::next()
{
	void *pRetVal = NULL;

	if(!pCurTravLink)
		return NULL;
	if(pCurTravLink->pData!=NULL)
	{
		pRetVal = pCurTravLink->pData;
		pCurTravLink = pCurTravLink->pNext;

		if(!pCurTravLink)
		{
			udwCurTravIndex++;
			while(udwCurTravIndex<udwHashSize)
			{
				pCurTravLink = &(pHashLinkTable[udwCurTravIndex]);
				if(pCurTravLink->pData)
					break;
				udwCurTravIndex++;
			}
			if(udwCurTravIndex>=udwHashSize)
				pCurTravLink = NULL;

		}
	}
	return pRetVal;
}


void  VHash::remove(void *pData)
{
	V_LINK *pIdLink, *pRemoveLink=NULL;
	VUDWORD udwId,udwIndex;
	udwId = (*fpId)(pData);
	udwIndex = udwId%udwHashSize;

	pIdLink = &(pHashLinkTable[udwIndex]);

	if(pIdLink->pData!=NULL)
	{
		if(pIdLink->pNext==NULL)
		{
			if(udwId == (*fpId)(pIdLink->pData))
			{
				if(!fpComp)
				{
					pIdLink->pData = NULL;
					udwCount--;
					if(pCurTravLink == pIdLink)
						pCurTravLink = pIdLink->pNext;
				}
				else
				{
					if((*fpComp)(pIdLink->pData,pData)==0)
					{
						pIdLink->pData = NULL;
						udwCount--;
						if(pCurTravLink == pIdLink)
							pCurTravLink = pIdLink->pNext;
					}
				}
			}
		}
		else
		{
			bool bDone = false;
			V_LINK *pCurLink,*pTmpLink;
			
			pCurLink = pIdLink;
			pTmpLink = pIdLink->pNext;
			if(udwId == (*fpId)(pIdLink->pData))
			{
				if(!fpComp)
				{
					pIdLink->pData = pCurLink->pNext->pData;
					pIdLink->pNext = pCurLink->pNext->pNext;
					
					udwCount--;
					if(pCurTravLink == pTmpLink)
						pCurTravLink = pIdLink;

					pMemAllocMgr->free(pTmpLink);
					//delete pTmpLink;
					bDone = true;
				}
				else
				{
					if((*fpComp)(pIdLink->pData,pData)==0)
					{
						pIdLink->pData = pCurLink->pNext->pData;
						pIdLink->pNext = pCurLink->pNext->pNext;
						
						udwCount--;
						if(pCurTravLink == pTmpLink)
							pCurTravLink = pIdLink;

						pMemAllocMgr->free(pTmpLink);
						//delete pTmpLink;
						bDone = true;
					}
				}
			}
			
			if(!bDone)
			{
				while(pCurLink->pNext)
				{
					if(udwId == (*fpId)(pCurLink->pNext->pData))
					{
						if(!fpComp)
						{
							pTmpLink = pCurLink->pNext;
							pCurLink->pNext = pCurLink->pNext->pNext;
							udwCount--;

							if(pCurTravLink == pTmpLink)
								pCurTravLink = pCurLink->pNext;

							pMemAllocMgr->free(pTmpLink);
							//delete pTmpLink;

							break;
						}
						else
						{
							if((*fpComp)(pCurLink->pNext->pData,pData)==0)
							{
								pTmpLink = pCurLink->pNext;
								pCurLink->pNext = pCurLink->pNext->pNext;
								
								udwCount--;

								if(pCurTravLink == pTmpLink)
									pCurTravLink = pCurLink->pNext;

								pMemAllocMgr->free(pTmpLink);
								//delete pTmpLink;
								break;
							}
						}
					}
					pCurLink = pCurLink->pNext;
				}
			}
		}
	}

	if(udwIndex == udwCurTravIndex)
	{
		if(!pCurTravLink)
		{
			udwCurTravIndex++;
			while(udwCurTravIndex<udwHashSize)
			{
				pCurTravLink = &(pHashLinkTable[udwCurTravIndex]);
				if(pCurTravLink->pData)
					break;
				udwCurTravIndex++;
			}
			if(udwCurTravIndex>=udwHashSize)
				pCurTravLink = NULL;

		}
	}
}

void  VHash::removeAll()
{
	V_LINK *pCurLink,*pTmpLink;
	for(VUDWORD i=0;i<udwHashSize;i++)
	{
		pCurLink = pHashLinkTable[i].pNext;
		while(pCurLink)
		{
			pTmpLink = pCurLink;
			pCurLink = pCurLink->pNext;
			pMemAllocMgr->free(pTmpLink);
			//delete pTmpLink;
		}
	}
	memset(pHashLinkTable,0,sizeof(V_LINK)*udwHashSize);

	udwCurTravIndex = 0;
	pCurTravLink = NULL;
	udwCount =0;
}

void  VHash::rehash(VUDWORD udwSize)
{
	V_LINK *pRootLink=NULL,*pCurLink,*pTmpLink;

	if(udwSize==0)
		return;

	double sizeRatio = udwHashSize/udwSize;

	if(sizeRatio >.75 && sizeRatio <1.25)
		return;

	if(udwCount)
	{
		for(VUDWORD i=0;i<udwHashSize;i++)
		{
			pCurLink = (&pHashLinkTable[i]);
			if(!pCurLink->pData)
				continue;
			
			pTmpLink = (V_LINK*)pMemAllocMgr->alloc(sizeof(V_LINK));
			pTmpLink->pData = pCurLink->pData;
			
			pTmpLink->pNext = pRootLink;
			pRootLink = pTmpLink;

			pCurLink = pCurLink->pNext;
			while(pCurLink)
			{
				pTmpLink = pCurLink;
				pCurLink = pCurLink->pNext;
				
				pTmpLink->pNext = pRootLink;
				pRootLink = pTmpLink;
			}
		}
	}

	udwHashSize = udwSize;
	udwCurTravIndex = 0;
	pCurTravLink = NULL;
	udwCount =0;

	if(pHashLinkTable)
		pMemAllocMgr->free(pHashLinkTable);
		

	pHashLinkTable = (V_LINK*)pMemAllocMgr->alloc(udwHashSize *sizeof(V_LINK));
	memset(pHashLinkTable,0,sizeof(V_LINK)*udwHashSize);

	pCurLink = pRootLink;
	while(pCurLink)
	{
		pTmpLink = pCurLink;
		pCurLink = pCurLink->pNext;
		
		insert(pTmpLink->pData);
		pMemAllocMgr->free(pTmpLink);
	}
	
}

void* VHash::getById(VUDWORD id)
{
	V_LINK *pIdLink;
	VUDWORD udwId,udwIndex;
	udwId = id;
	udwIndex = udwId%udwHashSize;

	pIdLink = &(pHashLinkTable[udwIndex]);

	if(pIdLink->pData!=NULL)
	{
		if(pIdLink->pNext==NULL)
		{
			if(udwId == (*fpId)(pIdLink->pData))
			{
				if(!fpComp)
					return 	pIdLink->pData;
				else
					return 	NULL;
			}
		}
		else
		{
			V_LINK *pCurLink;
			pCurLink = pIdLink;
			while(pCurLink)
			{
				if(udwId == (*fpId)(pCurLink->pData))
				{
					if(!fpComp)
						return 	pCurLink->pData;
					else
						return 	NULL;
				}
				pCurLink = pCurLink->pNext;
			}
		}
	}

	return NULL;
}


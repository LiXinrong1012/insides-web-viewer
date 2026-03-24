#include "vlistctnr.h"


VListCtnr::VListCtnr(VMemMgr *pMemMgr)
{
	init(pMemMgr);
}
VListCtnr::~VListCtnr()
{
	V_LINK *pCurLink,*pTmpLink;
	pCurLink = rootLink.pNext;
	while(pCurLink->pData)
	{
		pTmpLink = pCurLink;
		pCurLink = pCurLink->pNext;
		pMemAllocMgr->free(pTmpLink);
	}
}

void VListCtnr::insertNext(void *pData)	
{
	if(pData==NULL)
		return;

	V_LINK *pTmpLink = (V_LINK*)pMemAllocMgr->alloc(sizeof(V_LINK));
	pTmpLink->pData = pData;
	pTmpLink->pNext = pCurTravLink->pNext;
	pCurTravLink->pNext = pTmpLink;

	pOldTravLink = pCurTravLink;
	pCurTravLink = pCurTravLink->pNext;
	udwCount++;
}

void VListCtnr::insertPrev(void *pData)
{
	if(pData==NULL)
		return;

	V_LINK *pTmpLink = (V_LINK*)pMemAllocMgr->alloc(sizeof(V_LINK));
	pTmpLink->pData = pData;
	pTmpLink->pNext = pOldTravLink->pNext;

	pOldTravLink->pNext = pTmpLink;
	pCurTravLink = pOldTravLink->pNext;
	udwCount++;
}

void  VListCtnr::reset()
{
	pCurTravLink = pOldTravLink = &rootLink;
	bRemoved = false;
}

void* VListCtnr::next()
{
	if(bRemoved)
		bRemoved = false;
	else
	{
		pOldTravLink = pCurTravLink;
		pCurTravLink = pCurTravLink->pNext;
	}
	return pCurTravLink->pData;
}

void* VListCtnr::lookForward()
{
	if(bRemoved)
		return pCurTravLink->pData;
	else
		return pCurTravLink->pNext->pData;
}

void  VListCtnr::remove()
{
	V_LINK *pCurLink;

	if(!pCurTravLink->pData)
		return;

	pCurLink = pCurTravLink;
	pCurTravLink = pCurTravLink->pNext;
	pOldTravLink->pNext = pOldTravLink->pNext->pNext;
    pMemAllocMgr->free(pCurLink);
    bRemoved = true;

	udwCount--;
}


void  VListCtnr::removeAll()
{
	V_LINK *pCurLink,*pTmpLink;
	pCurLink = rootLink.pNext;
	while(pCurLink->pData)
	{
		pTmpLink = pCurLink;
		pCurLink = pCurLink->pNext;
		pMemAllocMgr->free(pTmpLink);
	}

	rootLink.pData = NULL;
	rootLink.pNext = &rootLink;
	pCurTravLink = pOldTravLink = &rootLink;
	bRemoved = false;
	udwCount  = 0;
}

void VListCtnr::init(VMemMgr *pMemMgr)
{
	rootLink.pData = NULL;
	rootLink.pNext = &rootLink;
	pCurTravLink = pOldTravLink = &rootLink;
	bRemoved = false;
	pMemAllocMgr = pMemMgr;
	udwCount  = 0;
}
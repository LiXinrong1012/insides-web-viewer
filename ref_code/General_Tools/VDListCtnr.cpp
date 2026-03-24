#include "VDListCtnr.h"


VDListCtnr::VDListCtnr(VMemMgr *pMemMgr) 
{
	init(pMemMgr) ;
}

VDListCtnr::~VDListCtnr() 
{
	V_DLINK *pTmpCurrent = 0 ;

	pCurrent = root.pNext ;
	while( pCurrent->pData )
	{
		pTmpCurrent = pCurrent ;
		pCurrent = pCurrent->pNext ;
		pMemMgr->free(pTmpCurrent) ;
	}

	root.pData = 0 ;
	root.pNext = 0 ;
	root.pPrevious = 0 ;
}

void VDListCtnr::init(VMemMgr *pMemMgr) 
{
	this->pMemMgr = pMemMgr ;
	root.pData = 0 ;
	root.pNext		= &root ;
	root.pPrevious	= &root ;

	pCurrent = &root ;

	udwCount = 0 ;
	bRemoved = false ;
	bTravForward = true ;
}

int VDListCtnr::insertLast(void *pData) 
{
	if( pData == 0 )
		return -1 ;

	if( pCurrent->pNext->pData != 0 )
	{
		while( pCurrent->pData )
			pCurrent = pCurrent->pNext ;
	}	

	V_DLINK *pLink = (V_DLINK*)pMemMgr->alloc(sizeof(V_DLINK)) ;
	pLink->pData		= pData ;

	pLink->pNext		= pCurrent->pNext ;
	pLink->pPrevious	= pCurrent ;
	pCurrent->pNext->pPrevious = pLink ; 

	pCurrent->pNext = pLink ;
	pCurrent = pLink ;

	udwCount ++ ;
	return udwCount ;
}

int VDListCtnr::insertFirst(void *pData) 
{
	if( pData == 0 )
		return -1 ;

	V_DLINK *pLink = (V_DLINK*)pMemMgr->alloc(sizeof(V_DLINK)) ;
	pLink->pData = pData ;
	pLink->pNext		= root.pNext ;
	pLink->pPrevious	= &root ;

	V_DLINK *pTmp = root.pNext ;

	root.pNext		= pLink ;
	pTmp->pPrevious = pLink ;

	pCurrent = pLink ;

	udwCount ++ ;
	return udwCount ;
}

int VDListCtnr::remove(void *pData) 
{
	V_DLINK *pPrevious = 0 ;
	V_DLINK *pNext = 0 ;

	if( pData )
	{
		pCurrent = root.pNext ;
		while( pCurrent->pData && pCurrent->pData != pData )
		{
			pCurrent = pCurrent->pNext ;
		}
	}

	if( pCurrent->pData == 0 )
		return -1 ;

	pPrevious = pCurrent->pPrevious ;
	pNext	  = pCurrent->pNext ;
	
	pPrevious->pNext = pNext ;
	pNext->pPrevious = pPrevious ;

	pMemMgr->free(pCurrent) ;
	pCurrent = pNext ;
	bRemoved = true ;
	-- udwCount ;

	return udwCount ;
}

void VDListCtnr::removeAll(void) 
{
	V_DLINK *pTmpCurrent = 0 ;

	pCurrent = root.pNext ;
	while( pCurrent->pData )
	{
		pTmpCurrent = pCurrent ;
		pCurrent = pCurrent->pNext ;
		pMemMgr->free(pTmpCurrent) ;
	}

	root.pData = 0 ;
	root.pNext		= &root ;
	root.pPrevious	= &root ;

	pCurrent = &root ;

	udwCount = 0 ;
	bRemoved = false ;
}

void VDListCtnr::reset(void) 
{
	pCurrent = &root ;
	bRemoved = false ;
	bTravForward = false ;
}

VUDWORD VDListCtnr::count(void)
{
	return udwCount ;
}

void* VDListCtnr::current(void) 
{
	return pCurrent->pData ;
}

void* VDListCtnr::next(void) 
{
	if( bRemoved )
		bRemoved = false ;
	else
	{
		if( pCurrent == &root && bTravForward )
			return 0 ;
		pCurrent = pCurrent->pNext ;
	}

	bTravForward = true ;
	return pCurrent->pData ;
}

void* VDListCtnr::previous(void)  
{
	if( pCurrent == &root && !bTravForward )
		return 0 ;

	bTravForward = false ;
	pCurrent = pCurrent->pPrevious ;
	return pCurrent->pData ;
}

void* VDListCtnr::whatIsNext(void* pData)  
{
	V_DLINK *pCurrentState = pCurrent ;
	pCurrent = &root ;
	bRemoved = false ;

	while( pCurrent->pData && pCurrent->pData != pData )
		pCurrent = pCurrent->pNext ;

	V_DLINK *pTmp = pCurrent->pNext ;
	pCurrent = pCurrentState ;

	return pTmp->pData ;
}

void* VDListCtnr::whatIsPrevious(void* pData)  
{
	V_DLINK *pCurrentState = pCurrent ;
	pCurrent = &root ;
	bRemoved = false ;

	while( pCurrent->pData && pCurrent->pData != pData )
		pCurrent = pCurrent->pNext ;

	V_DLINK *pTmp = pCurrent->pPrevious ;
	pCurrent = pCurrentState ;

	return pTmp->pData ;
}

bool VDListCtnr::isFirst(void) 
{
	if( pCurrent == root.pNext )
		return true ;
	return false ;
}

bool VDListCtnr::isLast(void)
{
	if( pCurrent->pNext == &root )
		return true ;
	return false ;
}

bool VDListCtnr::isEmpty(void) 
{
	if( udwCount == 0 )
		return true ;
	return false ;
}

bool VDListCtnr::removeAllDataFrom(void *pData)
{
	V_DLINK *pPrevious = 0 ;
	V_DLINK *pNext = 0 ;

	if( pData )
	{
		pCurrent = root.pNext ;
		while( pCurrent->pData && pCurrent->pData != pData )
		{
			pCurrent = pCurrent->pNext ;
		}
	}

	if( pCurrent->pData == 0 )
		return false ;

	while( pCurrent->pData )
	{
		V_DLINK *pTmpData = pCurrent ;
		pPrevious = pCurrent->pPrevious ;
		pNext	  = pCurrent->pNext ;
		
		pPrevious->pNext = pNext ;
		pNext->pPrevious = pPrevious ;

		pMemMgr->free(pTmpData) ;
		pTmpData = 0 ;

		//bRemoved = true ;
		-- udwCount ;

		if( pNext->pData != 0 )
			pCurrent = pNext ;
		else if( pNext == &root )
		{
			pCurrent = pPrevious ;
			break ;
		}
	}

	bTravForward = true ;

	return true ;
}
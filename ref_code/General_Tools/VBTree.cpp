#include <stdio.h>
#include "VBTree.h"

VBTree::VBTree(int (*funcPtrComp)(void *,void *),VMemMgr *pMemMgr)
{
	root.pParent= NULL;
	root.pLLink = NULL;
	root.pRLink = NULL;
	root.bFactor= NULL;
	root.pData	= NULL;

	fpComp = funcPtrComp;
	this->pCurPos = NULL ;
    
	inTraversal = 0 ;
    locJumped = 0 ;
    pCurData = 0 ;
	
	pMemAllocMgr = pMemMgr;
}

#define TRAV_UP(a,b)	((&(a)->pLLink)[(b)>0])
#define TRAV_DOWN(a)	((&(a)->pParent->pLLink)[(a)->pParent->pLLink != (a)])


void VBTree::insert ( void *pData)
{
	VBTreeNode *pObj = new(((VBTreeNode*)pMemAllocMgr->alloc(sizeof(VBTreeNode)))) VBTreeNode;
	
	pObj->pData = pData ;                 ;
	pObj->pParent = pObj->pLLink = pObj->pRLink = NULL ; 
	
	if (!root.pLLink ) 
	{
		root.pLLink  = pObj;
		pObj->pParent = &root;
		return ;
	}
	
	VBTreeNode *thisLoc = root.pLLink ;
    while(1) 
	{
		if ((*fpComp)(pObj->pData,thisLoc->pData) < 0) 
		{ 
			if (thisLoc->pLLink)
				thisLoc = thisLoc->pLLink;
			else 
			{
				thisLoc->pLLink = pObj;
				pObj->pParent = thisLoc;
				thisLoc = pObj;
				break;
			}
		}
		else 
		{	
			if(thisLoc->pRLink)
				thisLoc = thisLoc->pRLink;
			else 
			{
				thisLoc->pRLink = pObj;
				pObj->pParent = thisLoc;
				thisLoc = pObj;
				break;
			}
		}
	}
	
	while (1) 
	{
		VBTreeNode *pTop = thisLoc->pParent ;
		if (!pTop->pParent) 
			break; 
		
		int a = (thisLoc == pTop->pRLink ) ? 1 : -1 ;
		
		if (pTop->bFactor == a) 
		{ 
			VBTreeNode *down = TRAV_UP(thisLoc,-a) ;
			if (thisLoc->bFactor == a) 
			{
				TRAV_DOWN(pTop) = thisLoc;
				thisLoc->pParent = pTop->pParent;
				TRAV_UP(pTop,a) = down;
				
				if (down != NULL ) 
					down->pParent = pTop ;
				
				TRAV_UP(thisLoc,-a) = pTop;
				pTop->pParent = thisLoc ;
				pTop->bFactor  = 0; 
				thisLoc->bFactor = 0;
			}
			else 
			{ 
				TRAV_DOWN(pTop) = down;
				down->pParent = pTop->pParent ;
				TRAV_UP(pTop ,a) = TRAV_UP(down,-a);
				
				if (TRAV_UP(down,-a)) 
					TRAV_UP(down,-a)->pParent = pTop ;
				
				pTop->pParent = down;
				TRAV_UP(down,-a) = pTop ;
				TRAV_UP(thisLoc,-a) = TRAV_UP(down,a);
				
				if (TRAV_UP(down,a)) 
					TRAV_UP(down,a)->pParent = thisLoc ;
				
				TRAV_UP(down,a) = thisLoc;
				thisLoc->pParent = down;
				
				if (down->bFactor == a) 
				{ 
					pTop->bFactor = -a;	
					thisLoc->bFactor = 0; 
				}
				else if (down->bFactor == 0) 
				{ 
					pTop->bFactor = 0;	
					thisLoc->bFactor = 0; 
				}
				else 
				{
					pTop->bFactor = 0;	
					thisLoc->bFactor = a;
				}
				down->bFactor = 0;
			}
			break ;
		}
		else if(pTop->bFactor == 0) 
		{
			pTop->bFactor = a  ;
		}
		else 
		{
			pTop->bFactor = 0;
			break;
		}
		thisLoc = pTop;
	}
}

void VBTree::remove(void *pData) 
{
	int	a;
	int	cval;


   VBTreeNode *toRemove = root.pLLink ;
   while (toRemove) 
   {
		cval = (*fpComp)(pData,toRemove->pData);
		if (cval < 0)
			toRemove = toRemove->pLLink;
		else if (cval > 0)
			toRemove = toRemove->pRLink;
		else 
		{
			
			while (toRemove->pLLink) 
			{
				if ((*fpComp)(pData,toRemove->pLLink->pData)) 
					break;
				toRemove = toRemove->pLLink;
			}
		break;
		}
   }

   if ( toRemove == NULL )
	   return ;
   
   
   if ( toRemove == this->pCurPos ) 
   {
        if ( this->inTraversal == 1 ) 
		{
            this->pCurData = next() ;
            this->locJumped = 1 ;
        }
        else if ( this->inTraversal == 2 ) 
		{
            this->pCurData = prev() ;
            this->locJumped = 1 ;
        }
   }

   a = toRemove->bFactor ? toRemove->bFactor : 1 ;
   VBTreeNode *node,*down,*pTop ;
   if (node = TRAV_UP(toRemove,a)) 
   {
		if (TRAV_UP(node,-a) != NULL ) 
		{
			a = -a;
			while (down = TRAV_UP(node,a)) 
				node = down;
		}
		pTop = node->pParent;

		down = TRAV_UP(node,node->bFactor) ;
		TRAV_DOWN(node) = down;
		if (down) down->pParent = pTop;

		TRAV_DOWN(toRemove) = node ;
		node->bFactor = toRemove->bFactor;
		node->pParent = toRemove->pParent ;
		node->pLLink  = toRemove->pLLink  ;
		node->pRLink  = toRemove->pRLink  ;
		
		if (node->pLLink) node->pLLink->pParent = node;
		if (node->pRLink) node->pRLink->pParent = node;
		if (pTop == toRemove) pTop = node ;
	}
	else 
	{
		pTop = toRemove->pParent ;
		if (pTop->pLLink == toRemove) 
			a = -1; 
		else 
			a = 1;
		TRAV_UP(pTop,a) = NULL ;
	}

	VBTreeNode *thisLoc ;
	while (pTop->pParent) 
	{
		if (pTop->bFactor == -a) 
		{
			a = -a;
			thisLoc = TRAV_UP(pTop,a);
			down = TRAV_UP(thisLoc,-a);
			if (thisLoc->bFactor == 0) 
			{ 
				TRAV_DOWN(pTop) = thisLoc;
				thisLoc->pParent = pTop->pParent ;
				TRAV_UP(pTop,a) = down;
				
				if (down) 
					down->pParent = pTop;
				
				TRAV_UP(thisLoc,-a) = pTop;
				pTop->pParent = thisLoc;
				pTop->bFactor = a;
				thisLoc->bFactor = -a;
				
				break;
			}
			if (thisLoc->bFactor == a) 
			{
				TRAV_DOWN(pTop) = thisLoc ;
				thisLoc->pParent = pTop->pParent ;
				TRAV_UP(pTop,a) = down;
				
				if (down) 
					down->pParent = pTop;
				
				TRAV_UP(thisLoc,-a) = pTop;
				pTop->pParent = thisLoc ;
				pTop->bFactor = 0; 
				thisLoc->bFactor = 0;
				pTop = thisLoc ;
			}
			else 
			{	
				TRAV_DOWN(pTop) = down;
				down->pParent = pTop->pParent ;
				TRAV_UP(pTop,a) = TRAV_UP(down,-a);
				
				if (TRAV_UP(down,-a)) 
					TRAV_UP(down,-a)->pParent = pTop;
				
				pTop->pParent = down;
				TRAV_UP(down,-a) = pTop;
				TRAV_UP(thisLoc,-a) = TRAV_UP(down,a);
				
				if (TRAV_UP(down,a)) 
					TRAV_UP(down,a)->pParent = thisLoc;
				
				TRAV_UP(down,a) = thisLoc;
				thisLoc->pParent = down;
				
				if (down->bFactor == a)
				{ 
					pTop->bFactor = -a;
					thisLoc->bFactor = 0;
				}
				else if (down->bFactor == 0)
				{ 
					pTop->bFactor = 0;
					thisLoc->bFactor = 0;
				}
				else
				{ 
					pTop->bFactor = 0;
					thisLoc->bFactor = a;
				}
				down->bFactor = 0;
				pTop = down;
			}
		}
		else if (pTop->bFactor == 0) 
		{
			pTop->bFactor = -a;
			break;
		}
		else if (pTop->bFactor == a) 
		{
			pTop->bFactor = 0;
		}
		if (pTop->pParent->pLLink == pTop) 
			a = -1;
		else 
			a = 1;
		pTop = pTop->pParent;
	}
    pMemAllocMgr->free(toRemove) ;
}

void *VBTree::get(void *pData)
{
	int	cval;

	VBTreeNode *thisLoc = root.pLLink;
	while (thisLoc) 
	{
		cval = (*fpComp)(pData,thisLoc->pData);
		if (cval < 0)
			thisLoc = thisLoc->pLLink;
		else if (cval > 0)
			thisLoc = thisLoc->pRLink;
		else 
		{
			while (thisLoc->pLLink) 
			{
				if ((*fpComp)(pData,thisLoc->pLLink->pData)) break;
				thisLoc = thisLoc->pLLink;
			}
			break;
		}
	}

	if ( thisLoc )
		return thisLoc->pData ;
	else
		return NULL ;
}

void *VBTree::next() 
{
	VBTreeNode *pTop ;
	
	this->inTraversal = 1 ;
    if ( this->locJumped ) 
	{
        this->locJumped = 0 ;
        return this->pCurData ;
    }
    
	this->locJumped = 0 ;
    if ( !pCurPos ) 
	{
        this->inTraversal = 0 ;
        return NULL ;
    }
    if (!pCurPos->pParent) 
	{ 
		pCurPos = pCurPos->pLLink ; 
        if (!pCurPos) 
		{
            this->inTraversal = 0 ;
            return NULL ;
        }
		
		while (pCurPos->pLLink) 
			pCurPos = pCurPos->pLLink ;
		
		return pCurPos->pData ;
	}

	if (pCurPos->pRLink) 
	{
		pCurPos = pCurPos->pRLink;
		
		while (pCurPos->pLLink) 
			pCurPos = pCurPos->pLLink;
		return pCurPos->pData;
	}

	while (1) 
	{
		pTop = pCurPos->pParent;
        if (!pTop->pParent) 
		{
            this->inTraversal = 0 ;
            return NULL ;
        }
		if (pTop->pLLink == pCurPos) 
		{
			pCurPos = pTop ;
			return pCurPos->pData; 
		}
		 
		pCurPos = pTop;
	}
    this->inTraversal = 0 ;
	return NULL ;
}

void * VBTree::prev()
{
	VBTreeNode	*pTop ;
    
	this->inTraversal = 2 ;
    if ( this->locJumped ) 
	{
        this->locJumped = 0 ;
        return this->pCurData ;
    }
    this->locJumped = 0 ;
    
	if ( !pCurPos ) 
	{
        this->inTraversal = 0 ;
        return NULL ;
    }
	
	if (!pCurPos->pParent) 
	{  
		pCurPos = pCurPos->pLLink; 
        if (!pCurPos) 
		{
            this->inTraversal = 0 ;
            return NULL ;
        }
		
		while (pCurPos->pRLink) pCurPos = pCurPos->pRLink;
		return pCurPos->pData ;
	}

	if (pCurPos->pLLink) 
	{
		pCurPos = pCurPos->pLLink ; 
		while (pCurPos->pRLink) 
			pCurPos = pCurPos->pRLink;
		return pCurPos->pData ;
	}
	while (1) 
	{
		pTop = pCurPos->pParent ;
        if (!pTop->pParent) {
            this->inTraversal = 0 ;
            return NULL ;
        }
		if (pTop->pRLink == pCurPos ) 
		{
			pCurPos = pTop ;
			return pCurPos->pData;
		}
		pCurPos = pTop ;
	}
    this->inTraversal = 0 ;
    return NULL ;
}
void VBTree::removeAll()
{
	reset()   ;
	VBTreeNode *next ;
	prev() ;
	while ( pCurPos && pCurPos->pData ) 
	{
		next = pCurPos ;
		void *val =  prev() ;
		pMemAllocMgr->free(next) ;
		if ( val == NULL )
			break ;
	}
	root.pParent = root.pLLink = NULL ;
	root.pRLink = NULL ;
	root.bFactor = 0 ;
	root.pData = NULL ;
	//fpComp = NULL ;
	this->pCurPos = NULL ;
    inTraversal = 0 ;
    locJumped = 0 ;
    pCurData = 0 ;
}
int VBTree::count() 
{
	reset()   ;
	VBTreeNode *next ;
	prev() ;
	int count = 0 ;
	while ( pCurPos && pCurPos->pData ) 
	{
		count++ ;
		next = pCurPos ;
		void *val =  prev() ;
		if ( val == NULL )
			break ;
	}
    reset() ;
	return count ;
}


void VBTree::reset()
{ 
	pCurPos = &root ; 
	locJumped =	inTraversal= 0;
}
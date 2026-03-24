#include "vboctree.h"


VBOctree::VBOctree(double bBox[6],VUDWORD mLevels, void (*funcPtrBound)(void *,void *),VMemMgr *pMemMgr)
{
	memcpy(boundBox,bBox,sizeof(boundBox));
	maxLevels = mLevels;
	fpBound = funcPtrBound;
	pMemAllocMgr = pMemMgr;

	rootNode.pEntLink = NULL;
	rootNode.pParent = NULL;
	int i;
	for( i=0;i<8;i++)
		rootNode.pChilds[i] = NULL;

	double maxLen = 0,thisLen;

	for( i=0;i<3;i++)
	{
		thisLen = bBox[i+3]-bBox[i];
		thisLen = thisLen>0?thisLen:-thisLen;
		if(thisLen>maxLen)
			maxLen = thisLen;
	}

	double diff;

	maxLen = maxLen*1.1;
	for(i=0;i<3;i++)
	{
		diff = (maxLen-(boundBox[i+3]-boundBox[i]));
		boundBox[i] =  boundBox[i]-diff/2;
		boundBox[i+3] =  boundBox[i+3]+diff/2;

		rootNode.centPt[i] = boundBox[i] + maxLen/2;
	}


	
	rootNode.len = maxLen;

	udwCount =0;
}


VBOctree::~VBOctree()
{
}
	
	
bool VBOctree::insert(void *pData)
{
	double entBox[6];
	(*fpBound)(pData,(void*)entBox);
	
	if(insertNode(&rootNode,0, pData,entBox))
		return true;	
	else
		return false;
}

bool VBOctree::remove(void *pData)
{
	double entBox[6];
	(*fpBound)(pData,(void*)entBox);
	
	if(removeNode(&rootNode,0, pData,entBox))
		return true;	
	else
		return false;
}

bool VBOctree::getEntities(double centPt[3],double radius,VListCtnr *pEntLists)
{
	pEntLists->removeAll();

	double entBox[6];

	int i;

	for(i=0;i<3;i++)
	{
		entBox[i] = centPt[i]-radius;
		entBox[i+3] = centPt[i]+radius;
	}

	GetEntitiesInBoundBox(&rootNode,entBox,pEntLists);
	
	return true;	
}

void  VBOctree::removeAll()
{
	int i;
	for ( i = 0; i < 8; i++) 
	{
		clearThisNode(rootNode.pChilds[i]);
	}

	V_LINK *pTmpLink;
	V_LINK *pEntityLink = rootNode.pEntLink;
	while(pEntityLink)
	{
		pTmpLink = pEntityLink;
		pEntityLink = pEntityLink->pNext;
		pMemAllocMgr->free(pTmpLink);		
	}

	rootNode.pEntLink = NULL;
	rootNode.pParent = NULL;
	for(i=0;i<8;i++)
		rootNode.pChilds[i] = NULL;
	udwCount =0;
}

void  VBOctree::clearThisNode(OCT_NODE *pThisNode)
{
	if(!pThisNode)
		return;

	for (int i = 0; i < 8; i++) 
	{
		clearThisNode(pThisNode->pChilds[i]);
	}

	V_LINK *pTmpLink;
	V_LINK *pEntityLink = pThisNode->pEntLink;
	while(pEntityLink)
	{
		pTmpLink = pEntityLink;
		pEntityLink = pEntityLink->pNext;
		pMemAllocMgr->free(pTmpLink);		
	}

	pMemAllocMgr->free(pThisNode);

}

/*
bool VBOctree::insertNode(OCT_NODE *pThisNode, VUDWORD thisLevel,void *pData,double *entBox)
{
	int i;
	if(thisLevel>=maxLevels)
	{
		V_LINK *pTmpLink = (V_LINK*)pMemAllocMgr->alloc(sizeof(V_LINK));
		pTmpLink->pData = pData;
		pTmpLink->pNext = pThisNode->pEntLink;
		pThisNode->pEntLink = pTmpLink;
		return true;		
	}

	double centPt[3], thisBBox[6];

	for(i=0;i<3;i++)
	{
		thisBBox[i] = pThisNode->centPt[i]-(pThisNode->len/2);
		thisBBox[i+3] = pThisNode->centPt[i]+(pThisNode->len/2);
	}


	centPt[0] = (entBox[0]+entBox[3])/2;
	centPt[1] = (entBox[1]+entBox[4])/2;
	centPt[2] = (entBox[2]+entBox[5])/2;


	double thisCentPt[3], thisDimsXYZ[3], distEntVect[3];

	for(i=0;i<3;i++)
		thisDimsXYZ[i] = (thisBBox[i+3] - thisBBox[i])/2;
	
	for(i=0;i<3;i++)
		thisDimsXYZ[i] = thisDimsXYZ[i]>0?thisDimsXYZ[i]:-thisDimsXYZ[i];

	for(i=0;i<3;i++)
		distEntVect[i] = centPt[i] - thisBBox[i];

	double octCell[3];
	double newCellBBox[6], newCellCent[3];

	
	for(i=0;i<3;i++)
	{
		octCell[i] = distEntVect[i]/thisDimsXYZ[i];

		if(octCell[i]<0 || octCell[i]>2)
			return false;

		newCellBBox[i] = thisBBox[i] + thisDimsXYZ[i]*((int)octCell[i]);
		newCellBBox[i+3] = thisBBox[i] + thisDimsXYZ[i]*(((int)octCell[i])+1);
	
		newCellCent[i] = (newCellBBox[i] + newCellBBox[i+3])/2;

		if(entBox[i] < newCellBBox[i] || 
			entBox[i+3] > newCellBBox[i+3])
		{
			V_LINK *pTmpLink = (V_LINK*)pMemAllocMgr->alloc(sizeof(V_LINK));
			pTmpLink->pData = pData;
			pTmpLink->pNext = pThisNode->pEntLink;
			pThisNode->pEntLink = pTmpLink;
			return true;
		}
			
	}
		

	int cellIdx = ((int)octCell[0])*4 + ((int)octCell[1])*2 + ((int)octCell[2]);

	if(!(pThisNode->pChilds[cellIdx]))
	{
		OCT_NODE *pTmpNode = (OCT_NODE *)pMemAllocMgr->alloc(sizeof(OCT_NODE));
		pTmpNode->pEntLink = NULL;
		pTmpNode->pParent = pThisNode;
		
		for(i=0;i<8;i++)
			pTmpNode->pChilds[i]=NULL;

		pTmpNode->len = pThisNode->len/2;

		pThisNode->pChilds[cellIdx] = pTmpNode;

		for(i=0;i<3;i++)
			pThisNode->centPt[i] = newCellCent[i];
	}

	return insertNode(pThisNode->pChilds[cellIdx], thisLevel+1,pData,entBox);
}
*/

bool VBOctree::insertNode(OCT_NODE *pThisNode, VUDWORD thisLevel,void *pData,double *entBox)
{
	int i;
	if(thisLevel>=maxLevels)
	{
		V_LINK *pTmpLink = (V_LINK*)pMemAllocMgr->alloc(sizeof(V_LINK));
		pTmpLink->pData = pData;
		pTmpLink->pNext = pThisNode->pEntLink;
		pThisNode->pEntLink = pTmpLink;
		return true;		
	}
	
	int tlfFlags =0, brbFlags = 0;
    for ( i = 0; i < 3 ; i++) 
	{
      if (entBox[i] > pThisNode->centPt[i]) 
		  tlfFlags |= 1 << i;
      if (entBox[i+3] >= pThisNode->centPt[i]) 
		  brbFlags |= 1 << i;
	}

	double maxLen = 0,thisLen;

	for( i=0;i<3;i++)
	{
		thisLen = entBox[i+3]-entBox[i];
		thisLen = thisLen>0?thisLen:-thisLen;
		if(thisLen>maxLen)
			maxLen = thisLen;
	}
	double dSizeRatio;
	dSizeRatio = maxLen/pThisNode->len;
	
	//changed by jerry. brbFlags & 7 to (brbFlags & 7). June 15, 2010
	if(( (brbFlags & 7) == 7) && tlfFlags ==0 && dSizeRatio>.5)
	{
		V_LINK *pTmpLink = (V_LINK*)pMemAllocMgr->alloc(sizeof(V_LINK));
		pTmpLink->pData = pData;
		pTmpLink->pNext = pThisNode->pEntLink;
		pThisNode->pEntLink = pTmpLink;
		return true;		
	}

	for (i = 0; i < 8; i++) 
	{
		if ( ((i & brbFlags) == i) && ((i | tlfFlags) == i) ) 
		{
			if(!pThisNode->pChilds[i])
			{
				OCT_NODE *pTmpNode = (OCT_NODE *)pMemAllocMgr->alloc(sizeof(OCT_NODE));
				pTmpNode->pEntLink = NULL;
				pTmpNode->pParent = pThisNode;
				
				int jj;
				for( jj=0;jj<8;jj++)
					pTmpNode->pChilds[jj]=NULL;

				pTmpNode->len = pThisNode->len/2;

				pThisNode->pChilds[i] = pTmpNode;

				for(jj=0;jj<3;jj++)
				{
					pTmpNode->centPt[jj] = pThisNode->centPt[jj] + 
						(((1<<jj) & i)?(pThisNode->len/4):-pThisNode->len/4);
				}
			}
			insertNode(pThisNode->pChilds[i],thisLevel+1,pData,entBox);
		}
	}

	return true;
}

bool VBOctree::removeNode(OCT_NODE *pThisNode, VUDWORD thisLevel,void *pData,double *entBox)
{
	int i;
	if(thisLevel>=maxLevels)
	{
		removeEntityFromThisNode(pThisNode, pData);
		return true;		
	}
	
	int tlfFlags =0, brbFlags = 0;
    for ( i = 0; i < 3 ; i++) 
	{
      if (entBox[i] > pThisNode->centPt[i]) 
		  tlfFlags |= 1 << i;
      if (entBox[i+3] >= pThisNode->centPt[i]) 
		  brbFlags |= 1 << i;
	}
	for (i = 0; i < 8; i++) 
	{
		if ( ((i & brbFlags) == i) && ((i | tlfFlags) == i) ) 
		{
			if(pThisNode->pChilds[i])
			{
				removeEntityFromThisNode(pThisNode->pChilds[i], pData);
				removeNode(pThisNode->pChilds[i],thisLevel+1,pData,entBox);
			}
			
		}
	}

	return true;
}


void VBOctree::GetEntitiesInBoundBox(OCT_NODE *pThisNode, double *entBox, 
                                    VListCtnr *pEntList)
{
	if(pThisNode->pEntLink)
		pEntList->insertNext(pThisNode->pEntLink);
	
	int tlfFlags =0, brbFlags = 0;
	int i;
    for ( i = 0; i < 3 ; i++) 
	{
      if (entBox[i] > pThisNode->centPt[i]) 
		  tlfFlags |= 1 << i;
      if (entBox[i+3] >= pThisNode->centPt[i]) 
		  brbFlags |= 1 << i;
	}
	for (i = 0; i < 8; i++) 
	{
		if ( ((i & brbFlags) == i) && ((i | tlfFlags) == i) ) 
		{
			if(pThisNode->pChilds[i])
				GetEntitiesInBoundBox(pThisNode->pChilds[i],entBox,pEntList);
		}
	}
}


void VBOctree::removeEntityFromThisNode(OCT_NODE *pThisNode, void *pDataPtr)
{
	V_LINK **pPrevLinkNextPtr;
	V_LINK *pTmpLink;
	V_LINK *pEntityLink = pThisNode->pEntLink;
	pPrevLinkNextPtr = (&pThisNode->pEntLink);
	while(pEntityLink)
	{
		pTmpLink = pEntityLink;
		pEntityLink = pEntityLink->pNext;
		if(pTmpLink->pData==pDataPtr)
		{
			pMemAllocMgr->free(pTmpLink);
			*pPrevLinkNextPtr = pEntityLink;
		}
		else
			pPrevLinkNextPtr = &(pTmpLink->pNext);
	}
}

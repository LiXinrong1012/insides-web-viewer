#ifndef _VDS_VBOCTREE_H_
#define  _VDS_VBOCTREE_H_

#include "vds_datatypes.h"
#include "vmemmgr.h"
#include "vlistctnr.h"
#include "vds_structures.h"


class VBOctree
{
	public:

	struct OCT_NODE
	{
		V_LINK *pEntLink;
		OCT_NODE *pParent;
		OCT_NODE *pChilds[8];

		double centPt[3];
		double len;
	};

	VUDWORD udwCount;
	VUDWORD maxLevels;
	void (*fpBound)(void *data1,void *data2);

	double boundBox[6];

	OCT_NODE rootNode;
	VMemMgr *pMemAllocMgr;
		
	public:
	VBOctree(double bBox[6],VUDWORD maxLevels, void (*)(void *,void *),VMemMgr *pMemMgr);
	~VBOctree();
	
	
	bool insert(void *pData);
	bool remove(void *pData);
	bool getEntities(double centPt[3],double radius,VListCtnr *pEntLists);

	void  clearThisNode(OCT_NODE *pThisNode);	
	void  removeAll();	

	private:

	bool insertNode(OCT_NODE *pThisNode,VUDWORD thisLevel,void *pData,double *entBox);	

	void GetEntitiesInBoundBox(OCT_NODE *pThisNode, double *entBox, 
                                    VListCtnr *pEntList);

	bool removeNode(OCT_NODE *pThisNode,VUDWORD thisLevel,void *pData,double *entBox);	
	void removeEntityFromThisNode(OCT_NODE *pThisNode, void *pDataPtr);
};


#endif 
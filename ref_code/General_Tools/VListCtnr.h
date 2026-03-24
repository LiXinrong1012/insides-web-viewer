#ifndef _VDS_LISTCTNR_H_
#define  _VDS_LISTCTNR_H_

#include "vmemmgr.h"
#include "vds_structures.h"




class VListCtnr
{
	private:

	V_LINK  rootLink;
	VUDWORD udwCount;

	VUDWORD udwCurTravIndex;
	V_LINK *pCurTravLink;
	V_LINK *pOldTravLink;

	VMemMgr *pMemAllocMgr;

	bool bRemoved;
		
	public:
	VListCtnr(VMemMgr *pMemMgr);
	~VListCtnr();

	void init(VMemMgr *pMemMgr);

	void insertNext(void *pData);	
	void insertPrev(void *pData);	
	VUDWORD count(){ return udwCount;}
	void  reset();	
	void* next();	
	void  remove();	
	void  removeAll();	

	void* lookForward();
};


#endif 
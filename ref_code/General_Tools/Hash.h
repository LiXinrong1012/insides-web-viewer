#ifndef _VDS_HASH_H_
#define  _VDS_HASH_H_

#include "vds_datatypes.h"
#include "vmemmgr.h"
#include "vds_structures.h"

#include "Version.h"


class VHash
{
	public:

	V_LINK  *pHashLinkTable;
	VUDWORD udwHashSize; 
	VUDWORD udwCount;
	VUDWORD (*fpId)(void *data);
	VUDWORD (*fpComp)(void *data1,void *data2);

	VUDWORD udwCurTravIndex;
	V_LINK *pCurTravLink;

	VMemMgr *pMemAllocMgr;
		
	public:
	VHash(VUDWORD udwHashSize,VUDWORD (*)(void *),VUDWORD (*)(void *,void *),VMemMgr *pMemMgr);
	~VHash();
	void init(VUDWORD udwHashSize,VUDWORD (*)(void *),VUDWORD (*)(void *,void *),VMemMgr *pMemMgr);
	bool insert(void *pData);	
	void* get(void *pData);	
	void* getById(VUDWORD id);	
	void  reset();	
	void* next();	
	void  remove(void *pData);	
	void  removeAll();	
	void  rehash(VUDWORD udwHashSize);
};


#endif 
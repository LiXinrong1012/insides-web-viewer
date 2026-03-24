#ifndef VDLISTCTNR_H
#define VDLISTCTNR_H

#include "vmemmgr.h"
#include "vds_structures.h"

class VDListCtnr
{
	VMemMgr *pMemMgr ;
	V_DLINK  root ;
	V_DLINK  *pCurrent ;

	VUDWORD  udwCount ;
	bool  bRemoved ;
	bool  bTravForward ;
public:

	VDListCtnr(VMemMgr *pMemMgr) ;
	virtual ~VDListCtnr() ;
	void init(VMemMgr *pMemMgr) ;

	int insertLast(void *pData) ;
	int insertFirst(void *pData) ;
	
	int remove(void *pData=0) ;
	void removeAll(void) ;

	void reset(void) ;
	VUDWORD count(void) ;

	void* current(void) ;
	void* next(void) ;
	void* previous(void) ;
	void* whatIsNext(void* pData=0) ;
	void* whatIsPrevious(void* pData=0) ;

	bool isFirst(void) ;
	bool isLast(void) ;
	bool isEmpty(void) ;

	bool removeAllDataFrom(void *pData) ;
};


#endif
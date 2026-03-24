#ifndef _VBTREE_H__
#define _VBTREE_H__

#include "vds_datatypes.h"
#include "vmemmgr.h"
#include "vds_structures.h"

struct VBTreeNode 
{
public :
	VBTreeNode() 
	{ 
		pParent = NULL;
		pLLink	= NULL;
		pRLink	= NULL;
		pData	= NULL; 
		bFactor = NULL; 
	}
    ~VBTreeNode() {;}

	VBTreeNode *pParent; 
	VBTreeNode *pLLink; 
	VBTreeNode *pRLink; 

	void *pData      ; 
	short bFactor   ; 

	void *operator new( size_t size, void *ptr )
	{return ptr;}
    void operator delete( void *p, void *ptr)
	{;}
};

class VBTree {

public:
	VBTree(int (*)(void *,void *),VMemMgr *pMemMgr);
    ~VBTree() 
	{
		removeAll() ;
	}

	void insert( void *data  ) ;
	void *get( void *data ) ;
	
	
	void reset(); 
	void *next() ;
	void *prev() ;
	
	void remove( void *data);
	void  removeAll();
	
	int   count()   ;

private :

	VMemMgr *pMemAllocMgr;

	VBTreeNode  root  ;
	void     *pCurData ;
	
	int (*fpComp)(void *data1,void *data2);
	
	
	int      locJumped;
	VBTreeNode *pCurPos ;
    int      inTraversal ;

};

#endif
#include "TDYRigidResultItem.h"
#include "basetdyresult.h"

TDYRigidResultItem::TDYRigidResultItem(IResults* parent)
	:RigidResultItem(parent)
{
}


TDYRigidResultItem::~TDYRigidResultItem(void)
{
}

void TDYRigidResultItem::setPos( int pos )
{
	BaseTDYResult* tdyResults=(BaseTDYResult*)_parentResults;
	int startPos=tdyResults->getStartPos(pos);
	
	QDataStream* dataStream=tdyResults->getDataStream();

	int len=getDataLength();
	double* d=getData(0,0);

	dataStream->device()->seek(startPos+getOffset());
	dataStream->readRawData( (char*)(d),sizeof(double)*len);
	

}
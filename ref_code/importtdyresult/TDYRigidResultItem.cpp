#include "TDYRigidResultItem.h"
#include "TDYResults.h"

TDYRigidResultItem::TDYRigidResultItem(IResults* parent)
	:RigidResultItem(parent)
{
}


TDYRigidResultItem::~TDYRigidResultItem(void)
{
}

void TDYRigidResultItem::setPos( int pos )
{
	TDYResults* tdyResults=(TDYResults*)_parentResults;
	int startPos=tdyResults->getStartPos(pos);
	QDataStream* _dataStream=tdyResults->getDataStream();

	int len=getDataLength();
	double* d=getData(0,0);
	_dataStream->device()->seek(startPos+getOffset());
	_dataStream->readRawData( (char*)(d),sizeof(double)*len);
}

#include "TDYFlexResultItem.h"
#include "TDYResults.h"

TDYFlexResultItem::TDYFlexResultItem(IResults*parent)
	:FlexResultItem(parent)
{
}


TDYFlexResultItem::~TDYFlexResultItem(void)
{
}

void TDYFlexResultItem::setPos( int pos )
{
	TDYResults* tdyResults=(TDYResults*)_parentResults;
	int startPos=tdyResults->getStartPos(pos);
	QDataStream* _dataStream=tdyResults->getDataStream();

	int len=getDataLength();
	double* d=getData(0,0);
	_dataStream->device()->seek(startPos+getOffset());
	_dataStream->readRawData( (char*)(d),sizeof(double)*len);
}

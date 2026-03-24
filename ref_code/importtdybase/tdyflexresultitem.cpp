#include "TDYFlexResultItem.h"
#include "basetdyresult.h"

TDYFlexResultItem::TDYFlexResultItem(IResults*parent)
	:FlexResultItem(parent)
{
}

TDYFlexResultItem::~TDYFlexResultItem(void)
{
}

void TDYFlexResultItem::setPos( int pos )
{
	BaseTDYResult* tdyResults=(BaseTDYResult*)_parentResults;
	int startPos=tdyResults->getStartPos(pos);
	QDataStream* dataStream=tdyResults->getDataStream();

	int len=getDataLength();
	double* d=getData(0,0);
	dataStream->device()->seek(startPos+getOffset());
	dataStream->readRawData( (char*)(d),sizeof(double)*len);
}

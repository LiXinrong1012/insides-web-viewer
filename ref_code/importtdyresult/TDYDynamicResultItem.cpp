#include "TDYDynamicResultItem.h"
#include "TDYResults.h"
#include <QDataStream>

using namespace INSIDES;

TDYDynamicResultItem::TDYDynamicResultItem(IResults* result)
	:DynamicResultItem(result)
{
}

TDYDynamicResultItem::~TDYDynamicResultItem(void)
{
}

void TDYDynamicResultItem::setPos( int pos )
{
	TDYResults* res=(TDYResults*)getParent();
	QDataStream* dataStream=res->getDynamicDataStream();
	int startPos=res->getDynamicStartPos(pos);
	dataStream->device()->seek(startPos);

	QVector<int> dataHeaders;
	dataHeaders.resize(_index+1);
	dataStream->readRawData( (char*)(dataHeaders.data()),sizeof(int)*(_index+1));

	if(dataHeaders[_index]==0){ //无数据集
		_pieceCount=0;
		return;
	}

	int s=0;
	for(int i=0;i<_index;++i)
		s+=dataHeaders[i];

	dataStream->device()->seek(startPos+res->getDynamicResultItemCount()*sizeof(int)+s*_dataLength*sizeof(double));

	_pieceCount=dataHeaders[_index];
	_data.resize(_pieceCount*_dataLength);
	dataStream->readRawData( (char*)(_data.data()),dataHeaders[_index]*_dataLength*sizeof(double));
}

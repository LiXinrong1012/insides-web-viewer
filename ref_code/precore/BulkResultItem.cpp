#include "BulkResultItem.h"
#include <QDataStream>


namespace INSIDES
{

BulkResultItem::BulkResultItem( IResults* results,int frameCount,int dataSize )
	:IResultItem(results)
	,_frameCount(frameCount)
	,_size(dataSize)
	,_currentIndex(0)
{
	_datas.resize(_size*_frameCount);
}


BulkResultItem::~BulkResultItem(void)
{
}

void BulkResultItem::setPos( int pos )
{
	_currentIndex=pos;
}

IResultItem::Precision* BulkResultItem::getData( int section,int subSection/*=-1*/,int sbusubSection/*=-1*/ )
{
	return _datas.data()+_size*_currentIndex+section;
}


QDataStream& operator << (QDataStream& fout,const BulkResultItem& item)
{
	fout<<item._datas
		<<item._size
		<<item._frameCount
		<<item._currentIndex;
	return fout;
}

QDataStream& operator >> (QDataStream& fin, BulkResultItem& item)
{
	fin>>item._datas
		>>item._size
		>>item._frameCount
		>>item._currentIndex;
	return fin;
}

}
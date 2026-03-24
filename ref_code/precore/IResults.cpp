#include "IResults.h"

#include "IResultItem.h"


namespace INSIDES
{

IResults::IResults(void)
	:_isRandomRead(false)
	,_frameCount(0)
	,_currentFrame(0)
{
}

IResults::~IResults(void)
{
	clear();
}

void IResults::clear()
{
	_resultsMap.clear();
	_resultItemList.clear();
}

void IResults::addResult( IResultItem* resultItem )
{
	_resultItemList.push_back(QSharedPointer<IResultItem>(resultItem));
}

void IResults::addResult( BaseItem* item,IResultItem* resultItem )
{
	QSharedPointer<IResultItem> sResultItem=QSharedPointer<IResultItem>(resultItem);
	_resultItemList.push_back(sResultItem);
	resultItem->setConnectedItem(item);
	_resultsMap[item]=sResultItem;
}

bool IResults::next()
{
	if(_currentFrame>=_frameCount)
		return false;

	bool result= setPos(_currentFrame);
	if(result){
		_currentFrame++;
		return true;
	}
	return false;
}

bool IResults::setPos( int pos )
{
	if(pos!=_currentFrame || pos==0){
		_currentFrame=pos;

		for(ResultMap::Iterator b=_resultsMap.begin();b!=_resultsMap.end();++b)
		{
			b->data()->setPos(pos);
		}

		return true;
	}
	return false;
}

QWeakPointer<IResultItem> IResults::findResultItem( BaseItem* item )
{
	ResultMap::Iterator b=_resultsMap.find(item);
	if(b==_resultsMap.end())
		return QWeakPointer<IResultItem>();
	return b.value();
}

QList<double> IResults::getTimeList() const
{
	QList<double> timelist;
	int n=getFrameCount();
	for(int i=0;i<n;++i)
		timelist.push_back(getTime(i));
	return timelist;
}

}
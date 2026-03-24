#include "LegendManager.h"

#include "precore/IResultItem.h"
#include "precore/FlexResultItem.h"


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
LegendItem::LegendItem()
	:_isDirty(false)
{

}

LegendItem::~LegendItem()
{

}

void LegendItem::addItem( const DisplayLegendItem& item )
{
	int n=_displayLegend.size();
	int i;
	for(i=0;i<n;++i)
		if(_displayLegend[i].relatedResultItem==item.relatedResultItem)
			break;
	if(i<n){
		_displayLegend[i]=item;
		_displayLegend[i].parentLegendItem=this;
	}
	else{
		_displayLegend.push_back(item);
		_displayLegend[_displayLegend.size()-1].parentLegendItem=this;
	}
}

void LegendItem::updateBounding()
{
	float tmpMin=1e20,tmpMax=-1e20;
	for(int i=0;i<_displayLegend.size();++i){
		double cMin=_displayLegend[i].relatedResultItem->minBounding(
			_displayLegend[i].sectionIndex,
			_displayLegend[i].subSectionIndex,
			_displayLegend[i].subsubSectionIndex);
		double cMax=_displayLegend[i].relatedResultItem->maxBounding(
			_displayLegend[i].sectionIndex,
			_displayLegend[i].subSectionIndex,
			_displayLegend[i].subsubSectionIndex);

		if(cMin<tmpMin)
			tmpMin=cMin;
		if(cMax>tmpMax)
			tmpMax=cMax;
	}
	_legend.setMinMax(tmpMin,tmpMax,10);

}

void LegendItem::updateOnlyCurrentBounding()
{
	float tmpMin=1e20,tmpMax=-1e20;
	for(int i=0;i<_displayLegend.size();++i){
		FlexResultItem* flexResultItem=(FlexResultItem*)_displayLegend[i].relatedResultItem;

		int displaySectionIndex=_displayLegend[i].sectionIndex;
		if(displaySectionIndex>0)
		{
			int nodeCount=flexResultItem->getSection(displaySectionIndex)->numOfNodeOrElement;
			if(nodeCount<=0)
				continue;

			for(int tmpIndex=0;tmpIndex<nodeCount;++tmpIndex)
			{
				IResultItem::Precision d=flexResultItem->getNodeElemData(displaySectionIndex,
					_displayLegend[i].subSectionIndex,
					tmpIndex)[_displayLegend[i].subsubSectionIndex];
				if(d>tmpMax)
					tmpMax=d;
				if(d<tmpMin)
					tmpMin=d;
			}
		}
	}
	_legend.setMinMax(tmpMin,tmpMax,10);
}


void LegendItem::clearAll()
{
	for(int i=0;i<_displayLegend.size();++i)
		_displayLegend[i].isRemoved=true;
	setDirty(true);
}

void LegendItem::setDirty( bool b )
{
	_isDirty=b;
	if(!b){
		QList<DisplayLegendItem> newOne;
		for(int i=0;i<_displayLegend.size();++i)
			if(!_displayLegend[i].isRemoved)
				newOne.push_back(_displayLegend[i]);
		_displayLegend=newOne;
	}
}




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
LegendManager::LegendManager(void)
{
}


LegendManager::~LegendManager(void)
{
	clear();
}

LegendItem* LegendManager::getLegend( int index )
{
	return _legendItems[index];
}

int LegendManager::getLegendCount()
{
	return _legendItems.size();
}

void LegendManager::clear()
{
	qDeleteAll(_legendItems);
	_legendItems.clear();
}


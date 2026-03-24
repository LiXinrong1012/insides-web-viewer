#include "RigidResultItem.h"
#include <limits>
#include "IResults.h"
#include "precore/precore_data.h"

namespace INSIDES
{

RigidResultItem::RigidResultItem(IResults* parent)
	:IResultItem(parent)
	,_dataLength(0)
{
	_classType=TDY_POST_ITEMCLASS_RIGID;
	_data.push_back(0);
	_data.push_back(0);
	_data.push_back(0);
	_data.push_back(0);
	_data.push_back(0);
	_data.push_back(0);
	_data.push_back(0);
}


RigidResultItem::~RigidResultItem(void)
{
}

int RigidResultItem::sectionCount() const
{
	return _sectionNames.size();
}

int RigidResultItem::subSectionCount( int section ) const
{
	if(section<0)
		return 0;

	return _sectionNames[section].count;
}



QString RigidResultItem::sectionName( int section ) const
{
	return _sectionNames[section].name;
}

QString RigidResultItem::subSectionName( int section,int subSection ) const
{
	//return QString("%1-%2").arg(_sectionNames[section].name).arg(subSection+1);
	return QString("comp-%1").arg(subSection+1);
}




RigidResultItem::Precision* RigidResultItem::getData( int section,int subSection/*=-1*/,int sbusubSection/*=-1*/ )
{
	if(subSection==-1)
		subSection=0;
	int realIndex=getRealIndex(section,subSection);
	return _data.data()+realIndex;
}

int RigidResultItem::getRealIndex( int section,int subSection )
{
	return _sectionNames[section].realIndex[subSection];
}

void RigidResultItem::setSections( const QList<RigidSection>& sections )
{
	_sectionNames=sections;
	updateRealIndex();
}

void RigidResultItem::updateRealIndex()
{
	int c=0;
	for(int i=0;i<_sectionNames.size();++i)
	{
		for(int j=0;j<_sectionNames[i].count;++j)
			_sectionNames[i].realIndex[j]=c++;
	}
	_data.resize(c);
	_dataLength=c;
}

void RigidResultItem::addSection( const RigidSection& sec )
{
	_sectionNames.push_back(sec);
	updateRealIndex();
}

void RigidResultItem::clearSections()
{
	_sectionNames.clear();
	updateRealIndex();
}

RigidResultItem::Precision RigidResultItem::minBounding( int section,int subSection/*=0*/,int subsubSection/*=0*/ )
{
	if(!_hasBounding)
		updateMinMaxBounding();

	return _sectionNames[section].minBounding[subSection];
}

RigidResultItem::Precision RigidResultItem::maxBounding( int section,int subSection/*=0*/,int subsubSection/*=0*/ )
{
	if(!_hasBounding)
		updateMinMaxBounding();

	return _sectionNames[section].maxBounding[subSection];
}

void RigidResultItem::updateMinMaxBounding()
{
	resetBounding();

	int frameCount=_parentResults->getFrameCount();
	int oldFrameIndex=_parentResults->getCurrentFrame();
	for(int i=0;i<frameCount;++i){
		setPos(i);
		updateCurrentBounding();
	}

	setPos(oldFrameIndex);

	_hasBounding=true;
}

void RigidResultItem::updateCurrentBounding()
{
	int secCount=sectionCount();

	for(int sec=0;sec<secCount;++sec)
	{
		int subSecCount=subSectionCount(sec);
		for(int subSec=0;subSec<subSecCount;++subSec){
			Precision va=getData(sec,subSec)[0];
			if(va< _sectionNames[sec].minBounding[subSec])
				_sectionNames[sec].minBounding[subSec]=va;
			if(va> _sectionNames[sec].maxBounding[subSec])
				_sectionNames[sec].maxBounding[subSec]=va;
		}
	}
}

void RigidResultItem::resetBounding()
{
	int secCount=sectionCount();
	for(int sec=0;sec<secCount;++sec)
	{
		int subSecCount=subSectionCount(sec);
		for(int subSec=0;subSec<subSecCount;++subSec){
			_sectionNames[sec].minBounding[subSec]=std::numeric_limits<double>::max();
			_sectionNames[sec].maxBounding[subSec]=-std::numeric_limits<double>::max();
		}
	}
}

}
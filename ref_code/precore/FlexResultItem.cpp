#include "FlexResultItem.h"
#include <limits>
#include "IResults.h"

#include "precore/precore_data.h"

namespace INSIDES
{

FlexResultItem::FlexResultItem(IResults* parent)
	:IResultItem(parent)
	,_next(0)
{
	_classType=TDY_POST_ITEMCLASS_FLEX;
}


FlexResultItem::~FlexResultItem(void)
{
}

int FlexResultItem::sectionCount() const
{
	return _flexSections.size();
}

int FlexResultItem::subSectionCount( int section ) const
{
	if(section<0 || section>=_flexSections.size())
		return 0;

	return _flexSections[section].subSections.size();
}

int FlexResultItem::subsubSectionCount( int section,int subsection ) const
{
	if(section<0 || subsection<0)
		return 0;

	return _flexSections[section].subSections[subsection].count;
}

QString FlexResultItem::sectionName( int section ) const
{
	return _flexSections[section].name;
}

QString FlexResultItem::subSectionName( int section,int subSection ) const
{
	return _flexSections[section].subSections[subSection].name;
}

QString FlexResultItem::subsubSectionName( int section,int subSection,int subsubSection ) const
{
	//return QString("%1-%2").arg(subSectionName(section,subSection)).arg(subsubSection);
	return QString("comp-%1").arg(subsubSection+1);
}

FlexResultItem::Precision* FlexResultItem::getData( int section,int subSection/*=-1*/,int subsubSection/*=-1*/ )
{
	int diff=0;
	if(subSection==-1)
		subSection=0;
	if(subsubSection==-1)
		subsubSection=0;
	diff=_flexSections[section].subSections[subSection].offset;
	return _values.data()+diff/8+subsubSection;
}


void FlexResultItem::setSection( int i012,const FlexSection& section )
{
	while(i012>=_flexSections.size())
		_flexSections.push_back(section);

	_flexSections[i012]=section;
}

void FlexResultItem::addSection( const FlexSection& section )
{
	_flexSections<<section;
}

void FlexResultItem::updateSection()
{
	_values.clear();
	int nodeCount=getNodeCount();
	int elemCount=getElementCount();
	int allSize=0;
	foreach(const FlexSection& sec,_flexSections)
	{
		int tmpSize=getFlexSectionSize(sec);
		if(sec.numOfNodeOrElement<=0)
			allSize+=tmpSize;
		else
			allSize+=sec.numOfNodeOrElement*tmpSize;
	}

	_values.resize(allSize);
}

int FlexResultItem::getFlexSectionSize( const FlexSection& flexSection )
{
	int all=0;
	for(int i=0;i<flexSection.subSections.size();++i)
		all+=flexSection.subSections[i].count;
	return all;
}

FlexResultItem::Precision* FlexResultItem::getNodeData( int subSection,int nodeIndex )
{
	Precision* d=getData(1,subSection);
	int rCount=subsubSectionCount(1,subSection);
	return & d[rCount*nodeIndex];
}

FlexResultItem::Precision* FlexResultItem::getElemData(int section,int subSection,int elemIndex )
{
	Precision* d=getData(section,subSection);
	int rCount=subsubSectionCount(section,subSection);
	return & d[rCount*elemIndex];
}

FlexResultItem::Precision* FlexResultItem::getNodeElemData( int nodeElemSection,int subSection,int nodeElemIndex )
{
	Precision* d=getData(nodeElemSection,subSection);
	int rCount=subsubSectionCount(nodeElemSection,subSection);
	return & d[rCount*nodeElemIndex];
}

FlexResultItem::Precision FlexResultItem::minBounding( int section,int subSection/*=0*/,int subsubSection/*=0*/ )
{
	if(!_hasBounding)
		updateBounding();

	return _flexSections[section].subSections[subSection].minBounding[subsubSection];
}

FlexResultItem::Precision FlexResultItem::maxBounding( int section,int subSection/*=0*/,int subsubSection/*=0*/ )
{
	if(!_hasBounding)
		updateBounding();

	return _flexSections[section].subSections[subSection].maxBounding[subsubSection];

}

void FlexResultItem::updateBounding()
{
	resetBounding();

	int frameSize=_parentResults->getFrameCount();
	int oldFrameIndex=_parentResults->getCurrentFrame();
	for(int frameindex=0;frameindex<frameSize;++frameindex)
	{
		setPos(frameindex);
		updateCurrentBounding();
	}

	setPos(oldFrameIndex);
	_hasBounding=true;
}

void FlexResultItem::updateCurrentBounding()
{
	// for part variables
	{
		int subSecCount=_flexSections[0].subSections.size();
		for(int i=0;i<subSecCount;++i){
			int subsubSecCount=_flexSections[0].subSections[i].count;
			for(int j=0;j<subsubSecCount;++j){
				double va=getData(0,i)[j];
				if(va<_flexSections[0].subSections[i].minBounding[j])
					_flexSections[0].subSections[i].minBounding[j]=va;
				if(va>_flexSections[0].subSections[i].maxBounding[j])
					_flexSections[0].subSections[i].maxBounding[j]=va;
			}
		}
	}

	// for node and element variables
	int n=_flexSections.size();
	for(int tmpSection=1;tmpSection<n;++tmpSection)
	{
		FlexSection& sec=_flexSections[tmpSection];
		int subSecCount=sec.subSections.size();
		int nodeCount=sec.numOfNodeOrElement;
		for(int i=0;i<subSecCount;++i){
			int subsubSecCount=sec.subSections[i].count;
			for(int nodeIndex=0;nodeIndex<nodeCount;++nodeIndex)
			{
				double* vaList=getNodeElemData(tmpSection,i,nodeIndex);
				for(int j=0;j<subsubSecCount;++j){
					double va=vaList[j];
					if(va<sec.subSections[i].minBounding[j])
						sec.subSections[i].minBounding[j]=va;
					if(va>sec.subSections[i].maxBounding[j])
						sec.subSections[i].maxBounding[j]=va;
				}
			}
		}
	}
}

void FlexResultItem::resetBounding()
{
	int n=_flexSections.size();
	for(int i=0;i<n;++i)
	{
		FlexSection& sec=_flexSections[i];
		int n=sec.subSections.size();
		for(int j=0;j<n;++j){
			for(int k=0;k<FlexSubSection::MAX_SUBSUBITEM_COUNT;++k){
				sec.subSections[j].minBounding[k]=1e200;
				sec.subSections[j].maxBounding[k]=-1e200;
				//_flexSections[i]->subSections[j].minBounding[k]=std::numeric_limits<double>::max();
			}
		}
	}
}

void FlexResultItem::setNext( FlexResultItem* nextResult )
{
	if(_next)
		delete _next;

	_next=nextResult;
}

const FlexSection* FlexResultItem::getSection( int i012 )const
{
	return &_flexSections[i012];
}




}
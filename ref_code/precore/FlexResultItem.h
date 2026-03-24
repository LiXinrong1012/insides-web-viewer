#pragma once
#include "precore/iresultitem.h"
#include "precore/FEMPartBaseItem.h"


namespace INSIDES
{

class IResults;

struct FlexSubSection
{
	enum {MAX_SUBSUBITEM_COUNT=10};
	QString name;
	int		count;
	int		offset;
	double	minBounding[MAX_SUBSUBITEM_COUNT];
	double	maxBounding[MAX_SUBSUBITEM_COUNT];
};

struct FlexSection{
	QString name;
	int		offset;
	int		numOfNodeOrElement;
	QList<FlexSubSection> subSections;

	FlexSection():offset(0),numOfNodeOrElement(-1){}

	FlexSection& operator= (const FlexSection& section){
		this->name=section.name;
		this->offset=section.offset;
		this->subSections=section.subSections;
		this->numOfNodeOrElement=section.numOfNodeOrElement;
		return *this;
	}

	FlexSection(const FlexSection& section){
		this->name=section.name;
		this->offset=section.offset;
		this->subSections=section.subSections;
		this->numOfNodeOrElement=section.numOfNodeOrElement;
	}
};

class PRECORE_EXPORT FlexResultItem :
	public IResultItem
{
public:
	FlexResultItem(IResults* parent);
	~FlexResultItem(void);

	virtual void setPos(int index){};

	virtual int sectionCount()const;
	virtual int subSectionCount(int section)const;
	virtual int subsubSectionCount(int section,int subsection)const;

	virtual QString sectionName(int section)const;
	virtual QString subSectionName(int section,int subSection)const;
	virtual QString subsubSectionName(int section,int subSection,int subsubSection)const;
	virtual Precision* getData(int section,int subSection=-1,int sbusubSection=-1);
	virtual int getDataLength()const{return _values.size();}

	virtual Precision minBounding(int section,int subSection=0,int subsubSection=0);
	virtual Precision maxBounding(int section,int subSection=0,int subsubSection=0);
	virtual void updateCurrentBounding();
	virtual void resetBounding();

	void addSection(const FlexSection& section);
	/// deprecated, by Jerry He, 2014.11.15
	void FlexResultItem::setSection( int i012,const FlexSection& section );
	const FlexSection* getSection(int i012)const;
	void updateSection();

	Precision* getNodeElemData(int nodeElemSection,int subSection,int nodeElemIndex);
	Precision* getNodeData(int subSection,int nodeIndex);
	Precision* getElemData(int section,int subSection,int elemIndex);


	FEMPartBaseItem* getFEMBaseItem(){return &_femBaseItem;}
	const FEMPartBaseItem* getFEMBaseItem()const{return &_femBaseItem;}

	int getNodeCount(){return _femBaseItem.getFEMPart()->m_Mesh.GetNodeCnt();}
	int getElementCount(){return _femBaseItem.getFEMPart()->m_Mesh.GetElementCnt();}

	FlexResultItem* getNext(){return _next;}
	void setNext(FlexResultItem* nextResult);
	
private:
	QVector<FlexSection> _flexSections;
	/*
	FlexSection _partSection;
	FlexSection _nodeSection;
	FlexSection _elementSection;
	FlexSection* _flexSections[3];
	*/

	QVector<Precision>	_values;
	

	//JFEMPart	_femPart;
	FEMPartBaseItem		_femBaseItem;

	FlexResultItem*	_next;		//This can be used to store mapped FlexResultItem by user-defined interface

	int getFlexSectionSize(const FlexSection& flexSection);
	void updateBounding();
};

}
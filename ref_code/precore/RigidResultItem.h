#pragma once
#include "precore/iresultitem.h"

#include <QVector>
#include <QList>


namespace INSIDES
{

class IResults;

struct RigidSection
{
	enum {MAX_RIGID_SUBITEMS=10};
	QString name;
	int		count;
	double	minBounding[MAX_RIGID_SUBITEMS];
	double	maxBounding[MAX_RIGID_SUBITEMS];
	int		realIndex[MAX_RIGID_SUBITEMS];
};


class PRECORE_EXPORT RigidResultItem :
	public IResultItem
{
public:
	RigidResultItem(IResults* parent);
	virtual ~RigidResultItem(void);

	void clearSections();
	void setSections(const QList<RigidSection>& sections);
	void addSection(const RigidSection& sec);
	QList<RigidSection> getSections(){return _sectionNames;}

	virtual int sectionCount()const;
	virtual int subSectionCount(int section)const;

	virtual QString sectionName(int section)const;
	virtual QString subSectionName(int section,int subSection)const;

	virtual Precision minBounding(int section,int subSection=0,int subsubSection=0);
	virtual Precision maxBounding(int section,int subSection=0,int subsubSection=0);

	///	使用现有的数据更新Bounding
	virtual void updateCurrentBounding();
	virtual void resetBounding();

	virtual Precision* getData(int section,int subSection=-1,int sbusubSection=-1);

	virtual int getDataLength()const{return _dataLength;}

protected:
	int getRealIndex(int section,int subSection);
	void updateRealIndex();
	void updateMinMaxBounding();

		
	typedef QList<RigidSection>  SectionNameType;
	SectionNameType			_sectionNames;
	QVector<Precision>		_data;
	int						_dataLength;
};


}
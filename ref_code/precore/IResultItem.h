#pragma once

#include "precore/precore_global.h"
#include <QList>
#include <QString>


namespace INSIDES
{

class BaseItem;
class IResults;

/*!
	@breif 所有结果条目的基类。
	定义的结果条目的基本格式。
	@author Jerry He
	@date	2014.3
*/
class PRECORE_EXPORT IResultItem
{
public:
	/// 结果数据的类型：采用双精度浮点型
	typedef double Precision;

	IResultItem(IResults* parentResults);
	virtual ~IResultItem(void);

	/// 返回结果集指针
	IResults* getParent(){return _parentResults;}

	/// 设置结果集指针
	void setParent(IResults* i){_parentResults=i;}

	int getCategory();
	void setCategory(int i){_category=i;}

	/// 获得类类型，由此可以区别不同的IResultItem类别
	int getClassType()const{return _classType;}

	virtual int sectionCount()const{return 0;}
	virtual int subSectionCount(int section)const{return 0;}
	virtual int subsubSectionCount(int section,int subsection)const{return 0;}

	virtual Precision minBounding(int section,int subSection=0,int subsubSection=0){return 0.0;}
	virtual Precision maxBounding(int section,int subSection=0,int subsubSection=0){return 0.0;}
	virtual void updateCurrentBounding(){}
	virtual void resetBounding(){}
	virtual bool hasBounding(){return _hasBounding;}
	virtual void setHasBounding(bool b){_hasBounding=b;}


	virtual QString sectionName(int section)const{return QString();}
	virtual QString subSectionName(int section,int subSection)const{return QString();}
	virtual QString subsubSectionName(int section,int subSection,int subsubSection)const{return QString();}

	/// 
	virtual Precision* getData(int section,int subSection=-1,int sbusubSection=-1){return NULL;}
	virtual int getDataLength()const{return 0;}

	/// 设置结果条目位置到零
	void reset(){setPos(0);}

	/// 设置结果条目的位置
	virtual void setPos(int pos)=0;

	/// 获得此结果条目关联的模型条目
	BaseItem* connectedItem()const{return _connectedItem;}

	/// 设置此结果条目关联的模型条目
	void setConnectedItem(BaseItem* item){_connectedItem=item;}

	bool hasData()const{return _hasData;}
	void setHasData(bool b){_hasData=b;}


protected:

	IResults*		_parentResults;
	BaseItem*		_connectedItem;
	int				_category;
	int				_classType;
	bool			_hasData;
	bool			_hasBounding;

};

}
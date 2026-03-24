#ifndef TDY_PRE_POST_CORE_IRESULTS_H_
#define TDY_PRE_POST_CORE_IRESULTS_H_

#pragma once

#include "precore/precore_global.h"
#include <QHash>
#include <QList>
#include <QSharedPointer>
#include <QWeakPointer>

#include <complex>

namespace INSIDES
{

class BaseItem;
class IResultItem;

struct ResultQueryPara
{
	BaseItem*	item;
	int			section;
	int			subsection;
	int			subsubsection;

	ResultQueryPara()
		:item(NULL)
		,section(-1)
		,subsection(-1)
		,subsubsection(-1)
	{
	}
};

/*!
*	This class is the base class of all results.
*	@author Jerry He
*	@date	2014.3.25
*/
class PRECORE_EXPORT IResults
{
public:
	enum {RESULT_DYNAMIC=0,RESULT_EIGEN};

	typedef QHash<BaseItem*,QSharedPointer<IResultItem>>	ResultMap;
	typedef QList<QSharedPointer<IResultItem>>				ResultItemListType;

	virtual int getResultType()const{return RESULT_DYNAMIC;}

	/// 进行初始化，创建之后调用
	virtual bool init()=0;

	/// 将整个结果设置到pos
	virtual bool setPos(int pos);

	/// 得到此帧的时候
	virtual double getTime(int index)const{return 0;}

	//virtual std::complex<double> getEigenFreq(int index)const{return std::complex<double>(0,0);}
	virtual QString getEigenFreq(int index)const{return QString();}

	IResults(void);
	virtual ~IResults(void);
	void clear();

	int getFrameCount()const{return _frameCount;}
	void setFrameCount(int frameCount){_frameCount=frameCount;}

	int getResultCount()const{return _resultItemList.size();}
	ResultItemListType& getResultItemList(){return _resultItemList;}
	ResultMap& getResults(){return _resultsMap;}

	QWeakPointer<IResultItem> findResultItem(BaseItem* item);

	void addResult(BaseItem* item,IResultItem* resultItem);
	void addResult(IResultItem* resultItem);

		
	virtual QDataStream* getDataStream(){return NULL;}

	/// 得到当前的时间
	double getTime()const{return getTime(getCurrentFrame());}
	QList<double> getTimeList()const;


	/// 得到当前帧
	int	getCurrentFrame()const{return _currentFrame;}

	bool reset(){return setPos(0);}
	bool next();

protected:
	int			_frameCount;
	int			_currentFrame;
	ResultMap	_resultsMap;
	ResultItemListType		_resultItemList;
	bool		_isRandomRead;
};

}

#endif
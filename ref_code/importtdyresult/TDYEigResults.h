#pragma once

#include "precore/IResults.h"
#include "importtdybase/basetdyresult.h"
#include <QVector>
#include <QDataStream>

using namespace INSIDES;

class QDomDocument;
class QDomElement;

/*!
	@brief  模态结果实现类
	@date   2015.7.7
	@author Jerry
*/
class TDYEigResults :
	public BaseTDYResult
{
public:
	TDYEigResults(void);
	virtual ~TDYEigResults(void);
	 
	///获得结果类型
	virtual int getResultType()const{return RESULT_EIGEN;}

	/// 进行初始化，创建之后调用
	virtual bool init();

	///根据索引值获得对应的freq
	virtual QString getEigenFreq(int index)const;

	///初始化第一帧
	virtual void initFirstFrame(QDomDocument& handler,QDomElement item);

	///获得起始位置
	virtual int	getStartPos(int frameIndex){return _startPosList[frameIndex];}

private:
	QVector<int>	_startPosList;
	QVector<QString>	_eigFreqList;
};
#pragma once

#include "precore/IResults.h"
#include "importtdybase/basetdyresult.h"
#include <QVector>
#include <QDataStream>
#include <QFile>

using namespace INSIDES;

class QDomDocument;
class QDomElement;

class TDYResults :
	public BaseTDYResult
{
public:
	TDYResults(void);
	virtual ~TDYResults(void);

	/// 进行初始化，创建之后调用
	virtual bool init();

	/// 得到此帧的时候
	virtual double getTime(int index)const;

	///获得开始位置 
	virtual int	getStartPos(int frameIndex){return _startPosList[frameIndex];}

	///初始化第一帧
	virtual void initFirstFrame(QDomDocument& handler,QDomElement item);

	///初始化Load
	virtual void handleLoad(QXmlStreamReader& reader);

	///获得动态开始位置
	int getDynamicStartPos(int frameIndex){return _dynamicStartPosList[frameIndex];}

	///获得动态数据流
	QDataStream* getDynamicDataStream(){return _dynamicDataStream?_dynamicDataStream->dataStream:NULL;}

	///获得动态结果条目数
	int getDynamicResultItemCount()const{return _currentDynamicItemIndex;}

private:
	///打开文件
	QDataStream* openFile(const QString& fileName);

private:
	///开始位置列表
	QVector<int>	_startPosList;

	///时间列表
	QVector<double>	_timeList;

	///　可变二进制文件指针
	DataStream*	_dynamicDataStream;

	/// 可变文件每帧起始点
	QList<int>	_dynamicStartPosList;

	///当前动态条目索引
	int		_currentDynamicItemIndex;
};


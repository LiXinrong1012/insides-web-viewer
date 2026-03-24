#ifndef BASETDYRESULT_H
#define BASETDYRESULT_H

#include "precore/IResults.h"
#include <QVector>
#include <QDataStream>
#include <QtXml/QDomDocument>
#include <QFile>
#include <QMap>


namespace INSIDES{
	class FlexSection;
	class BaseItem;
}
class QXmlStreamReader;

/*!
	@brief  封装QDataStream
*/
class DataStream
{
public:
	DataStream(const QString& fileName);
	~DataStream();

	QDataStream*  dataStream;
	QFile*	file;
};

/*!
	@brief  tdy结果基类
	@date   2015.7.3
	@author Jerry
*/
class BaseTDYResult : public INSIDES::IResults
{

public:
    BaseTDYResult();
	virtual ~BaseTDYResult(void);

	/// 进行初始化，创建之后调用
	virtual bool init()=0;

	/// 得到此帧的时间
	virtual double getTime( int index ) const{return 0;}

	///根据当前所在帧数的不同，获得正确的QDataStream指针
	virtual QDataStream* getDataStream();

	///获得开始的位置
	virtual int	getStartPos(int frameIndex){return 0;}

	///初始化第一帧数据
	virtual void initFirstFrame(QDomDocument& handler,QDomElement item)=0;

	///用来处理load的函数
	virtual void handleLoad(QXmlStreamReader& reader){};

	///用来处理topo文件
	void initTopoFlex(QXmlStreamReader& reader,INSIDES::BaseItem* item);

protected:
	/// 获得所有想处理的XML条目
	void getAllCheckResultItems(QXmlStreamReader& reader);

	/// 获得所有特定名字的XML条目列表
	QList<QDomElement> getChildrenWithName(QDomElement item,const QString& name);

	///处理XML节点
	bool processXMLNode(QXmlStreamReader& reader,const QString& iName="");

	///通过name获得全部子项
	QList<QDomElement> _getChildrenItemsByName( QDomDocument& topoHandler,QDomElement curr,const QString& name );
	
	///读取柔性体选择内容
	INSIDES::FlexSection readFlexSection(QXmlStreamReader& reader);

	///获得第一个offset
	int _getFirstOffset( INSIDES::FlexSection& partSec,INSIDES::FlexSection& nodeSec,INSIDES::FlexSection& elemSec );

	///重建offset索引
	void reindexOffset(INSIDES::FlexSection& sec,int offset );

	// 以下函数由processXMLNode调用

	///用来解析rigidPart
	void readRigidPart(QXmlStreamReader& reader,INSIDES::BaseItem* item);

	///用来解析request
	void readRequest(QXmlStreamReader& reader,INSIDES::BaseItem* item);

	///用来解析assembly
	void readAssembly(QXmlStreamReader& reader,INSIDES::BaseItem* item);
	
protected:
	///<frame,dataStream ptr>
	///保存的当结果文件需要变动时，存储对应帧数以及datastream
	QMap<int,DataStream*>		_dataStreamMap;

	///存储子tdy结果？感觉未使用
	BaseTDYResult*  _sanTDYResults;
};

#endif // BASETDYRESULT_H

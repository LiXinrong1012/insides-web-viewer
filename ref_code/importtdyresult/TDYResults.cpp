#include "TDYResults.h"

#include "Base/console.h"
#include "Base/AppConfiguration.h"
#include "base/MultiProgressOperator.h"

#include "precore/modeldocument.h"

#include "importtdybase/tdyrigidresultitem.h"
#include "TDYDynamicResultItem.h"

#include <QtCore>
#include <QtXml/QDomDocument>
#include <QtXml/QXmlStreamReader>

using namespace Base;
using namespace pp;

//DataStream::DataStream( const QString& fileName )
//	:file(NULL)
//	,dataStream(NULL)
//{
//	file=new QFile(fileName);  
//	if (!file->open(QIODevice::ReadOnly)) {  
//		Console().Error("Cannot open file for writing: %s", 
//			qPrintable(file->errorString()) );
//		delete file;
//		file=NULL;
//		return;
//	}  
//
//	dataStream=new QDataStream(file);  
//	dataStream->setVersion(QDataStream::Qt_4_8);	
//}
//
//DataStream::~DataStream()
//{
//	if(dataStream) delete dataStream;
//	if(file) delete file;
//}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

///移动
//static QList<QDomElement> _getChildrenItemsByName(QDomDocument& topoHandler,
//	QDomElement curr,const QString& name)
//{
//	QList<QDomElement> vec;
//	QDomElement varElem=curr.firstChildElement(name);
//	while(!varElem.isNull()){
//		if(varElem.hasChildNodes())
//			vec.push_back(varElem);
//		varElem=varElem.nextSiblingElement(name);
//	}
//	return vec;
//}

TDYResults::TDYResults(void)
	:_dynamicDataStream(NULL)
{
	_sanTDYResults = this;
}

TDYResults::~TDYResults(void)
{
	if(_dynamicDataStream)
		delete _dynamicDataStream;
}

bool TDYResults::init()
{
	_currentDynamicItemIndex=0;

	QString fileName=AppConfiguration::instance()->workingDirectory()+"result/overview.xml";
	QDomDocument handler;
	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
		Base::Console().Warning("No result file.");
		return false;
	}
	handler.setContent(&file);
	QDomElement rootItem=handler.firstChildElement();
	QDomElement curr=rootItem.firstChildElement();

	int childCount=rootItem.childNodes().count();
	Base::Console().Log("Total item count = %d",childCount);
	if(childCount==0)
		childCount=1;
	float progressDelta=100.0/childCount;
	float totalProgress=0;

	static QString resultName;
	resultName.clear();
	bool isFirst=true;

	int currentFrame=0;
	while(!curr.isNull()){
		if(isFirst){
			Base::Console().Log("Initializing first frame...");
			initFirstFrame(handler,curr);
			isFirst=false;
			Base::Console().Log("Initializing first frame complete.");
		}
		
		int startpos=curr.attribute("startpos").toInt();
		QString str = curr.attribute("resfile");
		
		if(resultName.isEmpty() || resultName.compare(str,Qt::CaseInsensitive))
		{
			resultName = str;
			str=AppConfiguration::instance()->workingDirectory()+"result/"+str;
			DataStream* dataStream=new DataStream(str);
			_dataStreamMap[currentFrame] = dataStream;
		}
		  
		double frameTime=curr.attribute("time").toDouble();
		_startPosList.push_back(startpos);
		_timeList.push_back(frameTime);

		if(_dynamicDataStream){ //新版本
			int dynamicStartPos=curr.attribute("vstartpos").toInt();
			this->_dynamicStartPosList.push_back(dynamicStartPos);
		}

		curr=curr.nextSiblingElement();
		currentFrame++;
		totalProgress+=progressDelta;
		Base::MultiProgressOperator::setProgress((int)totalProgress);
	}

	_frameCount=_startPosList.size();

	Console().Message("Result imported, total frame count = %d",_frameCount);
	return true;
}

void TDYResults::initFirstFrame( QDomDocument& handler,QDomElement item )
{
	QString topoName=item.attribute("topofile");
	topoName=AppConfiguration::instance()->workingDirectory()+"result/"+topoName;

	QString dynamicsResultName=item.attribute("vresfile");
	if(!dynamicsResultName.isEmpty())
		dynamicsResultName=AppConfiguration::instance()->workingDirectory()+"result/"+dynamicsResultName;

	if(!dynamicsResultName.isEmpty())
		_dynamicDataStream=new DataStream(dynamicsResultName);

	QXmlStreamReader topoReader;
	QFile file(topoName);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	topoReader.setDevice(&file);
	topoReader.readNext();
	topoReader.readNext();//tdytopo
	topoReader.readNext();
	topoReader.readNext();//model
	
	topoReader.readNext();
	Base::Console().Log("Read topo xml file");

	getAllCheckResultItems(topoReader);

	Base::Console().Log("Got all checking result items.");
	file.close();
}

double TDYResults::getTime( int index ) const 
{
	return _timeList[index];
}

void TDYResults::handleLoad( QXmlStreamReader& reader )
{
	QString itemName=reader.attributes().value("GlobalName").toString();
	if(itemName.isEmpty())
		return;
	ModelDocument* doc=myDocument();
	BaseItem* item=doc->findItemWithoutFolder(itemName);
	if(!item)
		return;

	QString loadType=reader.attributes().value("NumberOfForces").toString();
	RigidResultItem* rigidItem=NULL;
	bool isDynamic=(loadType=="Dynamic");
	if(isDynamic)
	{
		TDYDynamicResultItem* item=new TDYDynamicResultItem(this);
		item->setOrderIndex(_currentDynamicItemIndex++);
		rigidItem=item;
	}
	else
		rigidItem=new TDYRigidResultItem(this);
	
	int id = reader.readNext();
	id = reader.readNext();
	id = reader.readNext();
	
	int off= -1;
	while(!reader.atEnd())
	{
		id = reader.readNext();
		if(off == -1)
			off = reader.attributes().value("offset").toString().toInt();

		if(reader.name().compare("ForceVariable",Qt::CaseInsensitive))
			break;

		RigidSection sec;
		sec.name=reader.attributes().value("name").toString();
		sec.count=reader.attributes().value("NumberOfComponents").toString().toInt();
		rigidItem->addSection(sec);
		rigidItem->setHasData(true);
		id=reader.readNext();
		id=reader.readNext();
	}
	id = reader.readNext();
	id = reader.readNext();
	id = reader.readNext();//</load>读完

	if(!isDynamic)
		((TDYRigidResultItem*)rigidItem)->setOffset(off);
	
	addResult(item,rigidItem);
}

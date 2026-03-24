#include "TDYEigResults.h"

#include "Base/console.h"
#include "Base/AppConfiguration.h"

#include "precore/modeldocument.h"

#include "importtdybase/TDYRigidResultItem.h"

#include <QtCore>
#include <QtXml/QDomDocument>

using namespace Base;
using namespace pp;


TDYEigResults::TDYEigResults(void)
{
}

TDYEigResults::~TDYEigResults(void)
{
}

bool TDYEigResults::init()
{
	QString fileName=AppConfiguration::instance()->workingDirectory()+"result/eigen_overview.xml";
	QDomDocument handler;
	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
		Base::Console().Warning("No result file.");
		return false;
	}

	handler.setContent(&file);

	QDomElement rootItem=handler.firstChildElement();
	QDomElement curr=rootItem.firstChildElement();

	static QString resultName;
	resultName.clear();

	bool isFirst=true;
	while(!curr.isNull()){
		if(isFirst){
			initFirstFrame(handler,curr);
			isFirst=false;
		}

		int frameId=curr.attribute("id").toInt();
		int startpos=curr.attribute("startpos").toInt();
		QString str = curr.attribute("eigfile");

		if(resultName.isEmpty() || resultName.compare(str,Qt::CaseInsensitive))
		{
			resultName = str;
			str=AppConfiguration::instance()->workingDirectory()+"result/"+str;
			DataStream* dataStream=new DataStream(str);
			_dataStreamMap[frameId] = dataStream;
		}

		QString frameTime=curr.attribute("eigen_value");
		_startPosList.push_back(startpos);
		_eigFreqList.push_back(frameTime);

		curr=curr.nextSiblingElement();
	}

	_frameCount=_startPosList.size();

	Console().Message("Result imported, total frame count = %d",_frameCount);
	return true;
}

void TDYEigResults::initFirstFrame( QDomDocument& handler,QDomElement item )
{
	QString topoName=item.attribute("topofile");
	topoName=AppConfiguration::instance()->workingDirectory()+"result/"+topoName;

	QXmlStreamReader reader;
	QFile tfile(topoName);
	if(!tfile.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	reader.setDevice(&tfile);
	reader.readNext();
	reader.readNext();

	reader.readNext();
	reader.readNext();

	ModelDocument* doc=myDocument();
	QList<QDomElement> checkItems;
	getAllCheckResultItems(reader);
	return;
	///////////////////////////////////
	for(int i=0;i<checkItems.size();++i)
	{
		QDomElement curr=checkItems[i];
		if(processXMLNode(reader))
			continue;

		QString itemName=curr.attribute("GlobalName");
		if(itemName.isEmpty())
			continue;

		BaseItem* item=doc->findItemWithoutFolder(itemName);
		if(!item)
			continue;

		if( curr.tagName()=="LOAD"){	//处理力的结果数据
			QString numOfForces=curr.attribute("NumberOfForces");
			if(numOfForces!="Dynamic"){
				TDYRigidResultItem* rigidItem=new TDYRigidResultItem(this);
				QDomElement varNode=curr.firstChildElement();

				QDomElement compNode=varNode.firstChildElement();
				while(!compNode.isNull())
				{
					RigidSection sec;
					sec.name=compNode.attribute("name");
					sec.count=compNode.attribute("NumberOfComponents").toInt();
					rigidItem->addSection(sec);
					rigidItem->setHasData(true);
					compNode=compNode.nextSiblingElement();
				}
				compNode=varNode.firstChildElement();
				int off=compNode.attribute("offset").toInt();
				rigidItem->setOffset(off);
				addResult(item,rigidItem);
			}
		}
	}
}

QString TDYEigResults::getEigenFreq( int index ) const
{
	return _eigFreqList[index];
}

#include "basetdyresult.h"
#include "base/Console.h"
#include "precore/FlexResultItem.h"
#include "precore/ResultDocument.h"
#include "tdyrigidresultitem.h"
#include "tdyflexresultitem.h"

#include "precore/modeldocument.h"
#include <QtXml/QXmlStreamReader>

using namespace INSIDES;


DataStream::DataStream( const QString& fileName )
	:file(NULL)
	,dataStream(NULL)
{
	file=new QFile(fileName);  
	if (!file->open(QIODevice::ReadOnly)) {  
		Base::Console().Error("Cannot open file for writing: %s", 
			qPrintable(file->errorString()) );
		delete file;
		file=NULL;
		return;
	}  

	dataStream=new QDataStream(file);  
	dataStream->setVersion(QDataStream::Qt_4_8);	
}

DataStream::~DataStream()
{
	if(dataStream) 
		delete dataStream;
	if(file) 
		delete file;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
BaseTDYResult::BaseTDYResult()
	:IResults()
	,_sanTDYResults(NULL)
{
}

BaseTDYResult::~BaseTDYResult(void)
{
	QList<DataStream*> list = _dataStreamMap.values();
	for (int i=0;i<list.count();i++)
		delete list[i];
	_dataStreamMap.clear();
}

FlexSection BaseTDYResult::readFlexSection(QXmlStreamReader& reader)
{
	int numberOfVariables = reader.attributes().value("NumberOfVariables").toString().toInt();
	int offset = reader.attributes().value("offset").toString().toInt();
	
	FlexSection section;
	for(int i=0;i<numberOfVariables;i++)
	{
		reader.readNextStartElement();
		FlexSubSection subSection;
		
		subSection.count=reader.attributes().value("NumberOfComponents").toString().toInt();
		subSection.name=reader.attributes().value("name").toString();
		subSection.offset=reader.attributes().value("offset").toString().toInt();
		section.subSections.push_back(subSection);
		reader.readNext();
	}
	return section;
}

int BaseTDYResult::_getFirstOffset( FlexSection& partSec,FlexSection& nodeSec,FlexSection& elemSec )
{partSec.subSections.size();
	if(partSec.subSections.size()>0)
		return partSec.subSections[0].offset;
	if(nodeSec.subSections.size()>0)
		return nodeSec.subSections[0].offset;
	if(elemSec.subSections.size()>0)
		return elemSec.subSections[0].offset;
	return -1;
}

void BaseTDYResult::reindexOffset( FlexSection& sec,int offset )
{
	if(sec.subSections.size()==0)
		return;
	sec.offset-=offset;
	for(int i=0;i<sec.subSections.size();++i)
		sec.subSections[i].offset-=offset;
}

void BaseTDYResult::getAllCheckResultItems(QXmlStreamReader& reader)
{
	while(!reader.atEnd())
	{
		int id = reader.readNext();
		
		if(!reader.isStartElement())
			continue;
		
		QString currName=reader.name().toString();
		bool flag;
		if(currName=="ASSEMBLY")
		{
			currName="ASSEBMLY";
			QString itemName=reader.attributes().value("GlobalName").toString();
			id = reader.readNext();
			
			getAllCheckResultItems(reader);
			processXMLNode(reader,itemName);
		}
		else if(currName=="FEMPART" || currName =="VFEMPART" ||
			currName == "MNFPART")
			processXMLNode(reader);
		else if(currName=="RIGIDPART")
			processXMLNode(reader);
		else if(currName=="LOAD")
			processXMLNode(reader);
		else if(currName=="REQUEST")
			processXMLNode(reader);
		else if(currName == "AssemblyVariables")
			break;
		else
			id = reader.readNext();
	}
}

bool BaseTDYResult::processXMLNode( QXmlStreamReader& reader ,const QString& iName/*=""*/)
{
	QString itemName=reader.attributes().value("GlobalName").toString();
	if(itemName.isEmpty())
		itemName = iName;

	if(itemName.isEmpty())
		return false;

	BaseItem* item=INSIDES::myDocument()->findItemWithoutFolder(itemName);
	if(!item)
		item = INSIDES::myDocument()->findItem(itemName);
	if(!item)
		return false;

	QString curXMLName=reader.name().toString();
	if(curXMLName=="RIGIDPART")
		readRigidPart(reader,item);
	else if(curXMLName=="REQUEST")//没有例子未测试
		readRequest(reader,item);
	else if( curXMLName=="FEMPART" || curXMLName =="VFEMPART" || curXMLName == "MNFPART")
	{
		Base::Console().Log("Pass MNFPart");
		initTopoFlex(reader,item);
	}
	else if(curXMLName=="AssemblyVariables" )
		readAssembly(reader,item);
	else if( curXMLName=="LOAD")//处理力的结果数据
		handleLoad(reader);
	else
		return false;

	return true;
}

void BaseTDYResult::readAssembly( QXmlStreamReader& reader,INSIDES::BaseItem* item )
{
	QString s = reader.name().toString();
	TDYRigidResultItem* rigidItem=new TDYRigidResultItem(this);
	while(!reader.atEnd())//定位到AssemblyVariables
	{
		if(!reader.name().toString().compare("AssemblyVariables",Qt::CaseInsensitive))
			break;

		reader.readNext();
	}
	int numberOfVariables = reader.attributes().value("NumberOfVariables").toString().toInt();
	int off = reader.attributes().value("offset").toString().toInt();
	for(int i=0;i<numberOfVariables;i++)
	{
		reader.readNextStartElement();
		RigidSection sec;
		sec.name=reader.attributes().value("name").toString();
		sec.count=reader.attributes().value("NumberOfComponents").toString().toInt();
		rigidItem->addSection(sec);
		rigidItem->setHasData(true);
		reader.readNext();
	}

	rigidItem->setOffset(off);
	addResult(item,rigidItem);
	int a =0;
}

void BaseTDYResult::initTopoFlex(QXmlStreamReader& reader,INSIDES::BaseItem* item )
{
	TDYFlexResultItem* flexResultItem=new TDYFlexResultItem(this);
	FEMPartBaseItem* femBaseItem=flexResultItem->getFEMBaseItem();
	JFEMPart* femPart=femBaseItem->getFEMPart();
	QVector<SNode>& nodelist=femBaseItem->getSNodeList();
	QVector<SElement>& elemslist=femBaseItem->getSElementList();
	int numberOfNodes = reader.attributes().value("NumberOfNodes").toString().toInt();
	int numberOfElements = reader.attributes().value("NumberOfElements").toString().toInt();

	//nodes
	while(!reader.atEnd())
	{
		if(!reader.name().compare("NODES",Qt::CaseInsensitive))
			break;
		reader.readNextStartElement();
	}
	reader.readNext();
	for(int i=0;i<numberOfNodes;i++)
	{
		int id = reader.readNext();//NODE
		SNode node;
		node.id=reader.attributes().value("id").toString().toInt();

		node.QG=reader.readElementText();
		nodelist.push_back(node);

		id = reader.readNext();
	}
	reader.readNext();reader.readNext();//</nodes>读完

	QList<int>	elemGroupSize;
	int sum =0;
	while(!reader.atEnd())
	{
		//elements
		while(!reader.atEnd())
		{
			if(!reader.name().compare("ELEMENTS",Qt::CaseInsensitive) && reader.isStartElement())
				break;
			reader.readNext();
		}

		int n =0;
		QString str = reader.attributes().value("NumOfElems").toString();
		if(!str.isEmpty())
			n = str.toInt();
		else
			n= numberOfElements;

		QString tmpName=reader.name().toString();

		if(n>0)
			elemGroupSize.push_back(n);

		reader.readNext();//<elements>结束
		for(int j=0;j<n;++j)
		{
			reader.readNext();
			tmpName=reader.name().toString();
			if(tmpName.compare("ELEMENT"))
				break;

			SElement elem;
			elem.id=reader.attributes().value("id").toString().toInt();
			elem.groupId=elemGroupSize.size()-1;
			elem.typeName=reader.attributes().value("type").toString();
			elem.nodeList= reader.readElementText();
			elemslist.push_back(elem);

			reader.readNext();// </ELEMENT>
			sum++;
		}

		if(sum == numberOfElements)
			break;	
	}

	femBaseItem->updateInteralMesh();

	//PartVariables
	while(!reader.atEnd())
	{
		if(!reader.name().compare("PartVariables",Qt::CaseInsensitive))
			break;
		reader.readNext();
	}

	FlexSection partSection=readFlexSection(reader);
	partSection.name="PartVariables";
	int minOffset=partSection.subSections[0].offset;
	reindexOffset(partSection,minOffset);
	flexResultItem->addSection(partSection);

	//NodeVariables
	while(!reader.atEnd())
	{
		if(!reader.name().compare("NodeVariables",Qt::CaseInsensitive))
			break;
		reader.readNext();
	}

	FlexSection nodeSection=readFlexSection(reader);
	nodeSection.name="NodeVariables";
	reindexOffset(nodeSection,minOffset);
	nodeSection.numOfNodeOrElement=nodelist.size();
	flexResultItem->addSection(nodeSection);

	//ElementVariables
	int num =0;
	reader.skipCurrentElement();
	reader.readNext();
	reader.readNext();
	while(!reader.name().compare("ElementVariables",Qt::CaseInsensitive))
	{
		QString typeName=reader.attributes().value("type").toString();
		FlexSection elemSection=readFlexSection(reader);
		elemSection.numOfNodeOrElement=elemGroupSize[num];
		reindexOffset(elemSection,minOffset);
		if(typeName.isEmpty())
			elemSection.name="ElementVariables";
		else
			elemSection.name="ElementVariables_"+typeName;
		flexResultItem->addSection(elemSection);

		reader.skipCurrentElement();
		reader.readNextStartElement();
		num ++;
	}

	flexResultItem->setOffset(minOffset);
	flexResultItem->updateSection();
	flexResultItem->setHasData(true);
	addResult(item,flexResultItem);
}

void BaseTDYResult::readRequest( QXmlStreamReader& reader,INSIDES::BaseItem* item )
{
	TDYRigidResultItem* rigidItem=new TDYRigidResultItem(this); 

	int offset=-1;
	int numberOfVariables = reader.attributes().value("NumberOfVariables").toString().toInt();
	int id = reader.readNext();//<request>读完
	for(int i=0;i<numberOfVariables;i++)
	{
		id = reader.readNext();
		QString tmp;
		if(offset==-1)
		{
			tmp=reader.attributes().value("offset").toString();
			if(!tmp.isEmpty())
				offset = tmp.toInt();
		}

		RigidSection sec;
		sec.name=reader.attributes().value("name").toString();
		sec.count=1;
		rigidItem->addSection(sec);
		rigidItem->setHasData(true);
		id = reader.readNext();
		id = reader.readNext();
	}
	if(offset==-1)
		delete rigidItem;
	else
	{
		rigidItem->setOffset(offset);
		addResult(item,rigidItem);
	}
	reader.readNext();
	reader.readNext();
}

void BaseTDYResult::readRigidPart( QXmlStreamReader& reader ,BaseItem* item)
{
	TDYRigidResultItem* rigidItem=new TDYRigidResultItem(this);

	while(!reader.atEnd())//定位到PartVariables
	{
		if(!reader.name().toString().compare("PartVariables",Qt::CaseInsensitive))
			break;
		reader.readNext();
	}
	int numberOfVariables = reader.attributes().value("NumberOfVariables").toString().toInt();
	int off = reader.attributes().value("offset").toString().toInt();
	reader.readNext();
	for(int i=0;i<numberOfVariables;i++)
	{
		reader.readNext();
		QString secName=reader.attributes().value("name").toString();
		int secCount=reader.attributes().value("NumberOfComponents").toString().toInt();
		RigidSection sec;
		sec.name=secName;
		sec.count=secCount;
		rigidItem->addSection(sec);
		rigidItem->setHasData(true);
		reader.readNext();
		reader.readNext();
	}
	reader.readNext();reader.readNext();//</PartVariables>读完
	reader.readNext();reader.readNext();//</RIGIDPART>读完

	rigidItem->setOffset(off);
	addResult(item,rigidItem);
}

QList<QDomElement> BaseTDYResult::getChildrenWithName( QDomElement item,const QString& name )
{
	QList<QDomElement> vec;
	QDomElement curr=item.firstChildElement();
	while(!curr.isNull())
	{
		if(curr.tagName()==name)
			vec<<curr;
		curr=curr.nextSiblingElement();
	}
	return vec;
}

QDataStream* BaseTDYResult::getDataStream()
{
	//1700 f curr
	// 0   1000  2000 file
	int frame = myResultDocument()->getResults()->getCurrentFrame();

	QList<int> iList = _dataStreamMap.keys();

	if(iList.isEmpty())
		return NULL;

	if(iList.count() == 1)
		return _dataStreamMap[iList[0]]->dataStream;

	for (int i=1;i<iList.count();i++)
	{
		if( frame < iList[i])
			return _dataStreamMap[iList[i-1]]->dataStream;
	}
	return  _dataStreamMap[iList[iList.count()-1]]->dataStream;;
}

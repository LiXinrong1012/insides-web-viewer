#include "tdytypeinfomanager.h"
#include <QSet>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QApplication>

#include "mainitem.h"
#include "modelparser.h"

namespace INSEditor
{
namespace Parse
{
static void _udpateKeyvalue(QList<TDYTypeKeyValuePtr>& vec,TDYTypeKeyValuePtr v)
{
	if(v->subKeyValueGroup.size()==0)
		vec<<v;
	else
	{
		vec.push_back(v);
		foreach(TDYTypeKeyValuePtr a,v->subKeyValueGroup)
			_udpateKeyvalue(vec,a);
	}
}
void TDYTypeInfo::update()
{
	// properties
	QSet<QString> tmpProperties;
	foreach(const TDYTypePropertyGroup& g,propertyGroups)
	{
		foreach(const TDYTypeProperty& p, g.properties)
			tmpProperties.insert(p.keyName);
	}
	propertyList=QList<QString>::fromSet(tmpProperties);

	// keyvalues
	keyvalueList.clear();
	if(keyvalueGroups){
		keyvalueList.push_back(keyvalueGroups);
		foreach(TDYTypeKeyValuePtr a,keyvalueGroups->subKeyValueGroup)
			_udpateKeyvalue(keyvalueList,a);
	}
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
TDYTypeInfoManager::TDYTypeInfoManager()
	:_isLoaded(false)
{
}

TDYTypeInfoManager::~TDYTypeInfoManager()
{
}

void TDYTypeInfoManager::addTDYInfos( QString keyName,TDYTypeInfoPtr ptr)
{
	ptr->update();
	_tdyTypeInfos[keyName] = ptr;
}

void TDYTypeInfoManager::save( const QString& fileName )
{
	QDomDocument doc;

	QDomProcessingInstruction instruction;
	instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ");
	doc.appendChild(instruction);

	QDomElement typeInfoElement = doc.createElement("TYPE_INFO");
	doc.appendChild(typeInfoElement);

	QMapIterator<QString,TDYTypeInfoPtr> it(_tdyTypeInfos);
	while(it.hasNext())
	{
		it.next();
		QString keyName = it.key();
		TDYTypeInfoPtr ptr = it.value();
		
		QDomElement typeElement = doc.createElement("TYPE");
		typeElement.setAttribute("VIEWER_CATEGORY",ptr->viewerCategory);
		typeElement.setAttribute("KEYNAME",ptr->keyName);
		typeInfoElement.appendChild(typeElement);

		QDomElement propertyGroupsElement = doc.createElement("PROPERTY_GROUPS");
		typeElement.appendChild(propertyGroupsElement);

		foreach(TDYTypePropertyGroup group,ptr->propertyGroups)
		{
			QDomElement propertyGroupElement = doc.createElement("PROPERTY_GROUP");
			propertyGroupElement.setAttribute("KEYNAME",group.keyName);
			propertyGroupsElement.appendChild(propertyGroupElement);

			foreach(TDYTypeProperty property,group.properties)
			{
				QDomElement propertyElement = doc.createElement("PROPERTY");
				propertyElement.setAttribute("KEYNAME",property.keyName);
				propertyGroupElement.appendChild(propertyElement);
			}
		} 
		TDYTypeKeyValuePtr keyValuePtr = ptr->keyvalueGroups;

		/*QDomElement keyValueElement = doc.createElement("KEY_VALUE");
		typeElement.appendChild(keyValueElement);*/
		addKeyValueElement(keyValuePtr,doc,typeElement);
	}

	QFile file(fileName);
	file.open(QIODevice::WriteOnly|QIODevice::Text);
	QTextStream stream(&file);
	stream.setCodec("UTF-8");
	stream << doc.toString();
	file.close();
}

void TDYTypeInfoManager::addKeyValueElement( TDYTypeKeyValuePtr kvPtr ,QDomDocument& doc ,QDomElement& element)
{
	if(!kvPtr)
		return;
	QDomElement tmpKeyValueElement = doc.createElement("KEY_VALUE");
	tmpKeyValueElement.setAttribute("KEYNAME",kvPtr->keyName);
	tmpKeyValueElement.setAttribute("CONPONENT_COUNT",kvPtr->componentCount);
	tmpKeyValueElement.setAttribute("COMPONENT_TYPE",kvPtr->componentType);
	tmpKeyValueElement.setAttribute("IS_OPTIMAL",kvPtr->isOptimal);
	tmpKeyValueElement.setAttribute("IS_REFERENCE",kvPtr->isReference);
	tmpKeyValueElement.setAttribute("IS_MULTIPLE_KEYVALUE",kvPtr->isMultipleKeyvalue);
	QStringList tmpList = kvPtr->validReferenceTypes;
	tmpKeyValueElement.setAttribute("VALID_REFERENCE_TYPES",tmpList.join(","));
	tmpList = kvPtr->validUnderProperties;
	tmpKeyValueElement.setAttribute("VALID_UNDER_PROPERTIES",tmpList.join(","));

	element.appendChild(tmpKeyValueElement);

	if (kvPtr->subKeyValueGroup.count()>0)
	{
		foreach(TDYTypeKeyValuePtr ptr,kvPtr->subKeyValueGroup)
			addKeyValueElement(ptr,doc,tmpKeyValueElement);
	}
}

void TDYTypeInfoManager::loadFromTDYTemplate( const QString& fileName )
{
	TDYTypeInfoPtr infoPtr;
	TDYTypeKeyValuePtr keyValuePtr;

	QDomDocument doc;
	QFile file(fileName);
	file.open(QIODevice::ReadOnly | QIODevice::Text);

	doc.setContent(file.readAll());
	file.close();

	QDomElement templeteElement = doc.firstChildElement();
	QDomElement element = templeteElement.firstChildElement();
	while(!element.isNull())
	{
		infoPtr=TDYTypeInfoPtr(new TDYTypeInfo());
		keyValuePtr = TDYTypeKeyValuePtr(new TDYTypeKeyValue());
		infoPtr->keyName = element.attribute("KEYWORD");

		QStringList list = element.attribute("PROPERTIES").split(",",QString::SkipEmptyParts);

		foreach(const QString& str,list)
		{
			TDYTypePropertyGroup pGroup;
			TDYTypeProperty property;
			property.keyName = str;
			pGroup.keyName = str;
			pGroup.properties.push_back(property);
			infoPtr->propertyGroups.push_back(pGroup);
		}

		QStringList subItemNamesList = element.attribute("SUBITEMNAMES").split(",",QString::SkipEmptyParts);
		foreach(const QString& str,subItemNamesList)
		{
			TDYTypeKeyValuePtr tmpKeyValuePtr=TDYTypeKeyValuePtr(new TDYTypeKeyValue());
			tmpKeyValuePtr->keyName = str.trimmed();
			keyValuePtr->subKeyValueGroup.push_back(tmpKeyValuePtr);
		}
		infoPtr->keyvalueGroups = keyValuePtr;

		this->addTDYInfos(infoPtr->keyName,infoPtr);

		element=element.nextSiblingElement();
	}
	_isLoaded=true;
}

void TDYTypeInfoManager::load( const QString& fileName )
{
	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
		return;

	QDomDocument doc;
	doc.setContent(file.readAll());
	file.close();

	QDomElement typeInfoElement = doc.firstChildElement("TYPE_INFO");
	QString s = doc.toString();
	QDomElement typeElement = typeInfoElement.firstChildElement("TYPE");
	while(!typeElement.isNull())
	{
		TDYTypeInfoPtr infoPtr=TDYTypeInfoPtr(new TDYTypeInfo());
		
		infoPtr->viewerCategory = typeElement.attribute("VIEWER_CATEGORY").toInt();
		infoPtr->keyName = typeElement.attribute("KEYNAME");
		infoPtr->helpString = typeElement.attribute("HELP");
		QDomElement propertyGroupsElement = typeElement.firstChildElement("PROPERTY_GROUPS");
		QDomElement propertyGroupElement = propertyGroupsElement.firstChildElement("PROPERTY_GROUP");

		while(!propertyGroupElement.isNull())
		{
			TDYTypePropertyGroup pGroup;
			pGroup.keyName = propertyGroupElement.attribute("KEYNAME");
			
			QDomElement propertyElement = propertyGroupElement.firstChildElement("PROPERTY");
			while(!propertyElement.isNull())
			{
				TDYTypeProperty pro;
				pro.keyName = propertyElement.attribute("KEYNAME");
				pGroup.properties.push_back(pro);
				propertyElement = propertyElement.nextSiblingElement("PROPERTY");
			}
			
			infoPtr->propertyGroups.push_back(pGroup);

			propertyGroupElement = propertyGroupElement.nextSiblingElement("PROPERTY_GROUP");
		}

		QDomElement keyValueElement = typeElement.firstChildElement("KEY_VALUE");
		if(!keyValueElement.isNull())
			infoPtr->keyvalueGroups = readKeyValueElement(keyValueElement);
		
		this->addTDYInfos(infoPtr->keyName,infoPtr);
		typeElement = typeElement.nextSiblingElement("TYPE");
	}
	_isLoaded=true;
}

INSEditor::Parse::TDYTypeKeyValuePtr TDYTypeInfoManager::readKeyValueElement( QDomElement& element )
{
	TDYTypeKeyValuePtr kvPtr = TDYTypeKeyValuePtr(new TDYTypeKeyValue());
	kvPtr->keyName = element.attribute("KEYNAME");
	QString testKeyName(kvPtr->keyName);
	kvPtr->componentCount = element.attribute("CONPONENT_COUNT").toInt();
	kvPtr->componentType = element.attribute("COMPONENT_TYPE");
	kvPtr->isOptimal = element.attribute("IS_OPTIMAL").toInt();
	kvPtr->isReference = element.attribute("IS_REFERENCE").toInt();
	kvPtr->valueCount = element.attribute("VALUE_COUNT","0").toInt();
	kvPtr->selectCount = element.attribute("SELECT_COUNT","1").toInt();
	kvPtr->isMultipleKeyvalue = element.attribute("IS_MULTIPLE_KEYVALUE").toInt();
	kvPtr->validReferenceTypes = element.attribute("VALID_REFERENCE_TYPES").split(",",QString::SkipEmptyParts);
	kvPtr->validUnderProperties = element.attribute("VALID_UNDER_PROPERTIES").split(",",QString::SkipEmptyParts);
	kvPtr->helpString = element.attribute("HELP");

	QDomElement child=element.firstChildElement();
	while(!child.isNull())
	{
		TDYTypeKeyValuePtr tmpPtr = readKeyValueElement(child);
		kvPtr->subKeyValueGroup.push_back(tmpPtr);

		child=child.nextSiblingElement();
	}

	return kvPtr;
}

const char* TDYTypeInfoManager::getAllKeynames()
{
	const QMap<QString,INSEditor::Parse::TDYTypeInfoPtr>& allInfos=_tdyTypeInfos;

	QList<QString> strList = allInfos.keys();
	QStringList list(strList);
	_allKeynames=list.join(" ").toLower().toStdString();
	return _allKeynames.c_str();
}

const char* TDYTypeInfoManager::getAllProperties()
{
	const QMap<QString,INSEditor::Parse::TDYTypeInfoPtr>& allInfos=_tdyTypeInfos;
	QStringList strList;
	for(QMap<QString,INSEditor::Parse::TDYTypeInfoPtr>::Iterator b=allInfos.begin();
		b!=allInfos.end();++b)
	{
		TDYTypeInfoPtr tmp=b.value();
		strList<<tmp->propertyList;
		foreach(const TDYTypeKeyValuePtr& v,tmp->keyvalueList)
			strList<<v->keyName;
	}
	_allProperties=strList.join(" ").toLower().toStdString();
	return _allProperties.c_str();
}


} // end namespace Parse
} // end namespace INSEditor



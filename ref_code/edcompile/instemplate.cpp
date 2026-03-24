#include "instemplate.h"

#include <QFile>
#include <QApplication>
#include <QStringBuilder>
#include <QSet>

#include <QtXml/QDomDocument>


namespace INSEditor{
namespace Parse{


static QStringList QStringToStringList(const QString& str)
{
	return str.split(",",QString::SkipEmptyParts);
}

bool ItemTemplate::hasProperty( const QString& p ) const
{
	return this->_subProperties.contains(p);
}

bool ItemTemplate::hasSubItem( const QString& p ) const
{
	return this->_subItems.contains(p);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
ItemTemplateManagerSinleton::ItemTemplateManagerSinleton()
{
	loadDefault();
}

ItemTemplateManagerSinleton::~ItemTemplateManagerSinleton()
{
}

ItemTemplateManagerSinleton* ItemTemplateManagerSinleton::instance()
{
	static ItemTemplateManagerSinleton _instance;
	return &_instance;
}

bool ItemTemplateManagerSinleton::loadDefault()
{
	return loadTemplateFile(qApp->applicationDirPath()+"/ins_template.xml");
}

bool ItemTemplateManagerSinleton::loadTemplateFile( const QString& fileName )
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		//QMessageBox::critical(this, "QXSRExample::parseXML", "Couldn't open example.xml", QMessageBox::Ok);
		return false;
	}

	QDomDocument doc; 
	if (!doc.setContent(&file)) 
		return false;      

	//Get the root element
	QDomElement docElem = doc.documentElement(); 
	QDomElement curr=docElem.firstChildElement();
	while(!curr.isNull()){
		QString keyname=curr.attribute("KEYWORD").toUpper();
		QString props=curr.attribute("PROPERTIES");
		QString subitemName=curr.attribute("SUBITEMNAMES");
		QString shortHelp=curr.attribute("SHORTHELP");
		QString longhelp=curr.attribute("LONGHELP");

		ItemTemplate item;
		item.setKeyName(keyname);
		item.setSubItems(QStringToStringList(subitemName));
		item.setSubProperties(QStringToStringList(props));

		_items[keyname]=item;

		curr=curr.nextSiblingElement();
	}

	reset();
	return true;
}

void ItemTemplateManagerSinleton::reset()
{
	//int n=_items.size();
	//QSet<QString> set1,set2;
	//for(int i=0;i<n;++i)
	//{
	//	ItemTemplate& item=_items[i];
	//	QString str=item.getKeyName();
	//	if(str.size()>0){
	//		set1<<str;
	//		QString lowStr=str.toLower();
	//		set1<<lowStr;
	//		lowStr[0]=lowStr[0].toUpper();
	//		set1<<lowStr;
	//	}

	//	int k=item.getSubItems().size();
	//	for(int j=0;j<k;++j)
	//		set2<<item.getSubItems()[j].trimmed();
	//	k=item.getSubProperties().size();
	//	for(int j=0;j<k;++j)
	//		set2<<item.getSubProperties()[j].trimmed();
	//}

	//QStringList set1List=set1.toList(),set2List=set2.toList();

	//_keywordSet1=set1List.join(" ");
	//_keywordSet2=set2List.join(" ");
}

const char* ItemTemplateManagerSinleton::getKeywordSet1()
{
	_keywordSet1Array=_keywordSet1.toStdString();
	return _keywordSet1Array.c_str();
}

const char* ItemTemplateManagerSinleton::getKeywordSet2()
{
	_keywordSet2Array=_keywordSet2.toStdString();
	return _keywordSet2Array.c_str();
}

const ItemTemplate* ItemTemplateManagerSinleton::getItem( const QString& key )
{
	QString a=key.toUpper();
	if(_items.find(a)==_items.end())
		return NULL;

	return &_items[a];
}


}	// end namespace Parse
}	// end namespace INSEditor
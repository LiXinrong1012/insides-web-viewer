#include "mainitem.h"
#include <algorithm>
#include <fstream>
#include <sstream>

namespace Parse {

	void Item::appendItem( Item* item )
	{
		this->itemList.push_back(item);
		item->parent=this;
	}

	int Item::row()
	{
		if(!getParent())
			return 0;
		return getParent()->itemList.indexOf(this);
	}

	QString Item::toString() const
	{
		QStringList myKeyValueString;
		for(int i=0;i<keyValues.size();++i){
			QString i1=keyValues[i].keyname;
			QString i2=keyValues[i].valueList.join(",");
			myKeyValueString.push_back(QString("%1:%2=%3").arg(keyValues[i].valueList.size())
				.arg(i1).arg(i2));
		}

		QString propsStr=properties.join(",");
		QString keyValueStr=myKeyValueString.join(";");
		return QString("[%1] (%2:%3) {%4}").arg(keyname).arg(properties.size()).arg(propsStr).arg(keyValueStr);
	}

	Item::Item()
		:parent(NULL)
		,rowIndex(0)
		,columnIndex(0)
	{
	}

	Item::Item( const QString& name ) 
		:keyname(name)
		,parent(NULL)
		,rowIndex(0)
		,columnIndex(0)
	{
	}

	Item::~Item()
	{
		qDeleteAll(itemList);
		itemList.clear();
	}

	QString Item::getFullName() const
	{
		if(parent)
			return parent->getFullName()+"."+mainLabel;

		return QString();
	}


}// end namespace Parse
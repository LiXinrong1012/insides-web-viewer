#include "mainitem.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <QDebug>

namespace INSEditor{

namespace Parse {

	LineItem::LineItem()
		:BaseItem(LINEITEM)
	{
	}

	LineItem::LineItem( const QString& name ) 
		:BaseItem(LINEITEM)
		,keyname(name)
		,parent(NULL)
	{
	}

	LineItem::LineItem( const LineItem& item )
		:BaseItem(item)
	{
		deepCopy(this,&item);
	}

	LineItem& LineItem::operator=( const LineItem& item )
	{
		if(this==&item)
			return *this;

		BaseItem::operator=(item);
		deepCopy(this,&item);

		return *this;
	}

	void LineItem::deepCopy(LineItem* dst,const LineItem* src)
	{
		clear();
		int n=src->allItems.size();
		BaseItem* tmp;
		for(int i=0;i<n;++i){
			BaseItem* c=src->allItems[i];
			if(c->type==KEYVALUEITEM){
				tmp=new KeyValueItem(*(KeyValueItem*)c);
				dst->allItems.push_back(tmp);
				dst->keyValues.push_back((KeyValueItem*)tmp);
			}
			else if(c->type==PROPERTYITEM){
				tmp=new PropertyItem(*(PropertyItem*)c);
				dst->allItems.push_back(tmp);
				dst->properties.push_back((PropertyItem*)tmp);
			}
			else{
				tmp=new CommentItem(*(CommentItem*)c);
				dst->allItems.push_back(tmp);
				dst->comments.push_back((CommentItem*)tmp);
			}
		}

		dst->parent=src->parent;
		dst->keyname=src->keyname;
		dst->mainID=src->mainID;
		dst->mainLabel=src->mainLabel;
	}

	void LineItem::clear()
	{
		qDeleteAll(allItems);
		allItems.clear();
		keyValues.clear();
		properties.clear();
		comments.clear();
	}

	LineItem::~LineItem()
	{
		clear();
	}

	void LineItem::removeProperty( PropertyItem* item )
	{
		if(!item)
			return;

		delete item;
		allItems.removeOne(item);
		properties.removeOne(item);
	}

	QString LineItem::toString() const
	{
		QStringList myKeyValueString;
		for(int i=0;i<keyValues.size();++i){
			QString i1=keyValues[i]->keyname;
			QString i2=keyValues[i]->valueList.join(",");
			myKeyValueString.push_back(QString("%1=%2").arg(i1).arg(i2));
		}

		QStringList myPropertyList;
		for(int i=0;i<properties.size();++i)
			myPropertyList.push_back(properties[i]->name);

		QStringList commentsList;
		for(int i=0;i<comments.size();++i)
			commentsList.push_back(comments[i]->comment);

		QString propsStr=myPropertyList.join(", ");
		QString keyValueStr=myKeyValueString.join("; ");
		QString comentsStr=commentsList.join("");
		return QString("[%1][%2][%3] (%4) {%5} {{%6}}")
			.arg(keyname).arg(mainID).arg(mainLabel)
			.arg(propsStr).arg(keyValueStr).arg(comentsStr);
	}

	QString LineItem::getFullName() const
	{
		if(parent)
			return parent->getFullName()+"."+mainID;
		return QString();
	}

	BaseItem* LineItem::addItem( const BaseItem& item )
	{
		const BaseItem* c=&item;
		BaseItem* tmp;
		if(c->type==KEYVALUEITEM){
			tmp=new KeyValueItem(*(KeyValueItem*)c);
			this->allItems.push_back(tmp);
			this->keyValues.push_back((KeyValueItem*)tmp);
		}
		else if(c->type==PROPERTYITEM){
			tmp=new PropertyItem(*(PropertyItem*)c);
			this->allItems.push_back(tmp);
			this->properties.push_back((PropertyItem*)tmp);
		}
		else{
			tmp=new CommentItem(*(CommentItem*)c);
			this->allItems.push_back(tmp);
			this->comments.push_back((CommentItem*)tmp);
		}
		return tmp;
	}

#ifdef _DEBUG
	void LineItem::print(const QString& pre)
	{
		qDebug()<<qPrintable(pre)<<qPrintable(toString());
	}
#endif

	bool LineItem::hasProperty( const QString& property ) const
	{
		foreach(PropertyItem* c,properties)
		{
			if(c->name.compare(property,Qt::CaseInsensitive)==0)
				return true;
		}
		return false;
	}

	KeyValueItem* LineItem::getKeyvalue( const QString& name )
	{
		foreach(KeyValueItem* c, keyValues)
		{
			if(!c->keyname.compare(name,Qt::CaseInsensitive))
				return c;
		}
		return NULL;
	}


	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
	AssemblyItem::AssemblyItem()
	{
		type=ASSEMBLYITEM;
	}

	AssemblyItem::AssemblyItem( const LineItem& lineItem )
	{
		LineItem* tmp=this;
		*tmp=lineItem;
		type=ASSEMBLYITEM;
	}

	AssemblyItem::~AssemblyItem()
	{
		qDeleteAll(allItemList);
		itemList.clear();
		allItemList.clear();
	}

	void AssemblyItem::addChild( LineItem* item )
	{
		this->itemList.push_back(item);
		this->allItemList.push_back(item);
		item->parent=this;
	}

	CommentItem* AssemblyItem::addComment( const CommentItem& item )
	{
		CommentItem* tmp=new CommentItem(item);
		this->allItemList.push_back(tmp);
		return tmp;
	}

	int AssemblyItem::row()
	{
		if(!getParent())
			return 0;

		AssemblyItem* parentAssembly=getParent();
		return parentAssembly->itemList.indexOf(this);
	}

	void AssemblyItem::removeChild( LineItem* item )
	{
		if(item){
			delete item;
			itemList.removeOne(item);
			allItemList.removeOne(item);
		}
	}

#ifdef _DEBUG
	void AssemblyItem::print( const QString& pre )
	{
		LineItem::print(pre);
		QString newPre=pre+"\t";

		int n=allItemList.size();
		for(int i=0;i<n;++i){
			BaseItem* item=allItemList[i];
			if(item->type==COMMENT)
				qDebug()<<qPrintable(newPre)<<qPrintable(((CommentItem*)item)->comment);
			else
				((LineItem*)item)->print(newPre);
		}
	}

#endif



}	// end namespace Parse

}	// end namespace INSEditor
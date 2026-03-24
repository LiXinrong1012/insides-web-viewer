#include "PropertyManagerSingleton.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

using namespace Base;

string uiTypeName[]={
	"unknown",
	"String",
	"Bool",
	"Int",
	"Float",
	"Color",
	"Combo",
	"File",
	"Maps",
	"Panel"
};

UiType g_getUiTypeFromName(string name)
{
	for(int i=0;i<UT_SIZE;++i){
		if(name==uiTypeName[i])
			return (UiType)i;
	}
	return UT_UNKNOWN;
}
string g_getUiTypeName(UiType type)
{
	return uiTypeName[type];
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
PropertyTypeItem::PropertyTypeItem()
:_keyName("Unknown"),
_discription("UnKnown"),
_uiType(UT_UNKNOWN),
_id(0),
_parent(NULL)
{
}
PropertyTypeItem::PropertyTypeItem(string keyName,string discription,UiType uiType)
:_keyName(keyName),
_discription(discription),
_uiType(uiType),
_id(0),
_parent(NULL)
{
}
PropertyTypeItem::PropertyTypeItem(string keyName,UiType uiType)
:_keyName(keyName),
_discription(keyName),
_uiType(uiType),
_id(0),
_parent(NULL)
{
}
PropertyTypeItem::PropertyTypeItem(string keyName,UiType uiType,unsigned int i)
:_keyName(keyName),
_discription(keyName),
_uiType(uiType),
_id(i),
_parent(NULL)
{
}

PropertyTypeItem::PropertyTypeItem(string keyName,string discription,UiType uiType,unsigned int i)
:_keyName(keyName),
_discription(discription),
_uiType(uiType),
_id(i),
_parent(NULL)
{
}

void PropertyTypeItem::output(ofstream& out)
{
	out<<"(";
	out<<"keyName = "<<getKeyName()<<",";
	out<<"discription = "<<getDiscription()<<",";
	out<<"UiType = "<<g_getUiTypeName(getUiType())<<",";
	out<<"Id = "<<getId()<<",";
	out<<"parent = "<<(_parent==NULL?"Null":_parent->getKeyName())<<")"<<endl;
}

PropertyTypeItem* PropertyTypeItem::createPanel(const string & panelName)
{
	PropertyTypeItem* item=new PropertyTypeItem(panelName,panelName,UT_PANEL,0);
	return item;
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
PropertyManagerSingleton& Base::operator >> (PropertyManagerSingleton & s,const string& bar)
{
	s.add(bar);
	return s;
}

PropertyManagerSingleton* PropertyManagerSingleton::_instance=NULL;

PropertyManagerSingleton::PropertyManagerSingleton(void)
{
}

PropertyManagerSingleton::~PropertyManagerSingleton(void)
{
}

PropertyManagerSingleton* PropertyManagerSingleton::instance()
{
	if(!_instance)
		if(!_instance){
			_instance=new PropertyManagerSingleton();
			_instance->initPropertyTypeItems();
		}
	return _instance;
}
void PropertyManagerSingleton::destruct(PropertyManagerSingleton* p)
{
	p->clear();
	delete p;
}
void PropertyManagerSingleton::clear()
{
	for(unsigned int i=0;i<_propertyTypeItems.size();++i){
		delete _propertyTypeItems[i];
	}
	_propertyTypeItems.clear();
	_propertyTypeItemMap.clear();
}

void PropertyManagerSingleton::writeToFile(string fileName)
{
	ofstream out(fileName.c_str());
	for(unsigned int i=0;i<_propertyTypeItems.size();++i){
		_propertyTypeItems[i]->output(out);
	}
	out.close();
}
void PropertyManagerSingleton::initPropertyTypeItems()
{
	(*this)>>"Base::Name String"
		>>"Base::Type Int"
		>>"Visibility Bool"
		>>"Transparency Int"
		>>"Mass Float"
		>>"InertiaXX Float"
		>>"InertiaYY Float"
		>>"InertiaZZ Float"
		>>"InertiaXY Float"
		>>"InertiaYZ Float"
		>>"InertiaXZ Float"
		>>"x Float"
		>>"y Float"
		>>"z Float"
		>>"Theata0 Float"
		>>"Theata1 Float"
		>>"Theata2 Float"
		>>"Theata3 Float"
		>>"MatId Int"
		>>"UndeformedMatId Int"
		>>"SelectedMatId Int"
		>>"BoundingBox String"
		>>"LineWidth Int"
		>>"LineColor Color"
		>>"LineStyle Combo"
		>>"LineSymbol Combo"
		>>"PenStyle Combo"
		>>"ConstraintType String"
		>>"ConnectionMarker String"
		>>"ActionMarker String"
		>>"ReactionMarker String"
		>>"DisplayStressType Combo";

	//writeToFile("E:/type.txt");
}
PropertyTypeItem* PropertyManagerSingleton::getPropertyTypeItem(string name)
{
	map<string,PropertyTypeItem*>::iterator f=_propertyTypeItemMap.find(name);
	if(f==_propertyTypeItemMap.end())
		return NULL;
	return f->second;
}
PropertyTypeItem* PropertyManagerSingleton::getPropertyTypeItem(unsigned int id)
{
	assert(id>0&& id<=_propertyTypeItems.size());
	return _propertyTypeItems[id-1];
}
PropertyTypeItem* PropertyManagerSingleton::add(const PropertyTypeItem& item)
{
	map<string,PropertyTypeItem*>::iterator f=_propertyTypeItemMap.find(item.getKeyName());
	if(f!=_propertyTypeItemMap.end())
		return f->second;
	PropertyTypeItem* newItem=new PropertyTypeItem(item);
	return add(newItem);
}
PropertyTypeItem* PropertyManagerSingleton::add(PropertyTypeItem* item)
{
	item->setId(_propertyTypeItems.size()+1);
	_propertyTypeItems.push_back(item);
	_propertyTypeItemMap[item->getKeyName()]=item;
	return item;
}

PropertyTypeItem* PropertyManagerSingleton::add(const string& strLine)
{
	istringstream instream; 
    instream.str(strLine);  
	string name,typeName;
	instream>>name>>typeName;
	UiType type=g_getUiTypeFromName(typeName);
	return add(name,type);
}
PropertyTypeItem* PropertyManagerSingleton::add(const string & itemFullName,UiType uiType)
{
	vector<string> vecs;
	int curr=0;
	while(true){
		int p=itemFullName.find("::",curr);
		if(p==std::string::npos)
		{
			string tmpStr(itemFullName,curr,itemFullName.size()-curr);
			vecs.push_back(tmpStr);
			break;
		}
		vecs.push_back(string(itemFullName,curr,p-curr));
		curr=p+2;
	}

	assert(vecs.size()!=0);

	PropertyTypeItem* parent=NULL;
	unsigned int i;
	for(i=0;i<vecs.size()-1;++i){
		PropertyTypeItem* tmpProp=getPropertyTypeItem(vecs[i]);
		if(tmpProp==NULL){
			tmpProp=PropertyTypeItem::createPanel(vecs[i]);
			add(tmpProp);
		}
		tmpProp->setParent(parent);
		parent=tmpProp;
	}
	PropertyTypeItem* addItem=new PropertyTypeItem(vecs[i],uiType);
	addItem->setParent(parent);
	return add(addItem);
}
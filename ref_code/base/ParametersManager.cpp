#include "ParametersManager.h"
#include "base/Console.h"
#include <map>
#include "QObject"
#include <QFileInfo>
#include <QtGui>
#include <QSharedPointer>
#include <QWeakPointer>

#include "pp_xml/XMLHandler.h"

using namespace pp;

using namespace std;

namespace Base{

ParameterItem::ParameterItem(const KeyType& key,const QVariant& value,bool changeable,bool debugOnly,int type)
:_keyword(key)
,_discription(key)
,_variant(value)
,_bChangeable(changeable)
,_bDebugOnly(debugOnly)
,_type(type)
{
}

ParameterItem::ParameterItem()
	:_bChangeable(true)
	,_bDebugOnly(false)
	,_type(ValidType)
{
}

int ParameterItem::getType()const
{
	if(_type==ValidType)
		return _variant.type();
	return _type;
}

void ParameterItem::setVariant(const QVariant& v)
{
#ifdef _DEBUG
	if(v.type()!=_variant.type()&& _variant.type()!=0)
		Base::Console().Error("Try to set variant to un-matched parameter item:%s = %s",
		_keyword.toStdString().c_str(),
		v.toString().toStdString().c_str());
#endif
	_variant=v;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class ParametersGroupPrivate
{
public:
	typedef QMap<ParameterItem::KeyType,ParameterItem > MapType;

	ParametersGroupPrivate(){}
	~ParametersGroupPrivate();

	void reset();
	const ParameterItem* next();
	const ParameterItem* get(const ParameterItem::KeyType&key);

	ParametersManager* _parent;
	MapType _data;
	QString _name;
	MapType::const_iterator _currentIter;
};

ParametersGroupPrivate::~ParametersGroupPrivate()
{
	_data.clear();
}

const ParameterItem* ParametersGroupPrivate::get(const ParameterItem::KeyType&key)
{
	MapType::iterator f=_data.find(key);
	if(f==_data.end())
		return NULL;
	return &f.value();
}

inline void ParametersGroupPrivate::reset()
{
	_currentIter=_data.begin();
}

inline const ParameterItem* ParametersGroupPrivate::next()
{
	if(_currentIter==_data.end())
		return NULL;
	const ParameterItem* tmp=&_currentIter.data();
	_currentIter++;
	return tmp;
}



ParametersGroup::ParametersGroup(ParametersManager* parent)
:_ptr(new ParametersGroupPrivate())
{
	_ptr->_parent=parent;
}

ParametersGroup::~ParametersGroup(void)
{
}

void ParametersGroup::reset()
{
	_ptr->reset();
}

const ParameterItem* ParametersGroup::next()
{
	return _ptr->next();
}

void ParametersGroup::clear()
{
	_ptr->_data.clear();
}

void ParametersGroup::set(const ParameterItem& item,bool overrid/* =true */)
{
	const ParameterItem* oldItem=_ptr->get(item.getKeyword());
	if(oldItem && !overrid)
			return;
		
	if(oldItem){
		ParameterItem tmpOldItem=*oldItem;
		_ptr->_data[item.getKeyword()]=item;

		if(_ptr->_parent)
			_ptr->_parent->notifyListeners(this,&item,&tmpOldItem);
	}
	else{
		_ptr->_data[item.getKeyword()]=item;

		if(_ptr->_parent)
			_ptr->_parent->notifyListeners(this,&item,NULL);
	}
}

//void ParametersCollection::setValue(const KeyType& key,const QVariant& value)
//{
	//ParameterItem* item=get(key);
	//if(item)
		//item->setVariant(value);
//}

const ParameterItem* ParametersGroup::get(const KeyType& key)const
{
	return _ptr->get(key);
}


QString ParametersGroup::getName()
{
	return _ptr->_name;
}

void ParametersGroup::setName( const QString& name )
{
	_ptr->_name=name;
}

ParametersManager* ParametersGroup::getParent()
{
	return _ptr->_parent;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

class ParametersManagerPrivate
{
public:
	typedef QList<QSharedPointer<ParametersGroup> > CollectionsType;
	CollectionsType _collections;
	bool _bDebug;
	QWeakPointer<ParametersGroup> _defaultCollection;
	QList<IParametersModificationListener*>	_listeners;

	ParametersManagerPrivate()
#ifdef _DEBUG
		:_bDebug(true)
#else
		:_bDebug(false)
#endif
	{}
};


ParametersManager::ParametersManager()
:_ptr(new ParametersManagerPrivate())
{
}
ParametersManager::~ParametersManager()
{

}



const ParameterItem* ParametersManager::get(const KeyType& key,const QString& collectionName)const
{
	if(collectionName.isEmpty()){
		QStringList vec=key.split("::");
		if(vec.size()==2){
			const ParametersGroup* a=getCollection(vec[0]);
			if(a)
				return a->get(vec[1]);
		}
		if(getDefaultCollection())
			return getDefaultCollection()->get(key);
		return NULL;
	}
	const ParametersGroup* a=getCollection(collectionName);
	if(a)
		return a->get(key);

	return NULL;
}



bool ParametersManager::get(const KeyType& key, void** result,const QString& collectionName)
{
	const ParameterItem* item=get(key,collectionName);
	if(item){
		*result=(void*)item->getVariant().toLongLong();
		return true;
	}
	return false;
}


bool ParametersManager::set(const KeyType& key, void* value,const QString& collectionName)
{
	ParametersGroup* collection=getCollection(collectionName);
	if(collection){
		qlonglong a=(qlonglong)value;
		ParameterItem item;
		item.setType(ParameterItem::VoidStarPointer);
		item.setVariant(a);
		collection->set(item);
		return true;
	}
	return false;
}

void ParametersManager::set( const ParameterItem& item,const QString& groupName/*=QString()*/ )
{
	getOrCreateGroup(groupName)->set(item);
}

bool ParametersManager::setValue(const KeyType& key,const QVariant& v,const QString& collectionName)
{
	ParametersGroup* collection=getCollection(collectionName);
	if(collection){
		const ParameterItem* oldItem=collection->get(key);
		if(oldItem){
			ParameterItem newItem=*oldItem;
			newItem.setVariant(v);
			collection->set(newItem);
			return true;
		}
	}
	return false;
}


void ParametersManager::clear()
{
	for(int i=0;i<getCollectionCount();++i)
		getCollection(i)->clear();
}

void ParametersManager::clear(const QString& collectionName)
{
	ParametersGroup* collection=getCollection(collectionName);
	if(collection)
		collection->clear();
}


bool ParametersManager::isDebug()
{
	return _ptr->_bDebug;
}
void ParametersManager::setDebug(bool b)
{
	_ptr->_bDebug=b;
}

void ParametersManager::remove( const QString& collectionName )
{
	Console().Warning("Not implemented yet.");
	/*
	ParameterCollectionSingletonPrivate::CollectionsType::iterator f=_ptr->_collections.find(collectionName);
	if(f!=_ptr->_collections.end())
		_ptr->_collections.erase(f);
		*/
}

void ParametersManager::remove( int index )
{
	Console().Warning("Not implemented yet.");
	//_ptr->_collections.remove(index);
}

void ParametersManager::removeAll()
{
	Console().Warning("Not implemented yet.");
}

ParametersGroup* ParametersManager::addCollection( const QString& collectionName )
{
	ParametersGroup* c=getCollection(collectionName);
	if(c)
		return c;
	c=new ParametersGroup(this);
	c->setName(collectionName);
	_ptr->_collections.push_back(QSharedPointer<ParametersGroup>(c));
	//_ptr->_defaultCollection=_ptr->_collections[_ptr->_collections.size()-1];
	return c;
}

ParametersGroup* ParametersManager::getCollection( const QString& collection )
{
	if(collection.isEmpty())
		return _ptr->_defaultCollection.data();

	int size=_ptr->_collections.size();
	int i=0;
	for(i=0;i<size;++i){
		QSharedPointer<ParametersGroup> a=_ptr->_collections[i];
		if(a->getName()==collection)
			break;
	}
	if(i==size)
		return NULL;
	return _ptr->_collections[i].data();
}

ParametersGroup* ParametersManager::getCollection( int index )
{
	return _ptr->_collections[index].data();
}

const ParametersGroup* ParametersManager::getCollection( const QString& collection ) const
{
	if(collection.isEmpty())
		return _ptr->_defaultCollection.data();

	int size=_ptr->_collections.size();
	int i=0;
	for(i=0;i<size;++i){
		QSharedPointer<ParametersGroup> a=_ptr->_collections[i];
		if(a->getName()==collection)
			break;
	}
	if(i==size)
		return NULL;
	return _ptr->_collections[i].data();
}

int ParametersManager::getCollectionCount() const
{
	return _ptr->_collections.size();
}

ParametersGroup* ParametersManager::getDefaultCollection()
{
	return _ptr->_defaultCollection.data();
}

const ParametersGroup* ParametersManager::getDefaultCollection() const
{
	return _ptr->_defaultCollection.data();
}

void ParametersManager::setDefaultCollection( ParametersGroup* p )
{
	int a=indexOf(p);
	if(a!=-1)
		_ptr->_defaultCollection=_ptr->_collections[a];
}

int ParametersManager::indexOf( ParametersGroup* collection ) const
{
	int size=_ptr->_collections.size();
	int i=0;
	for(i=0;i<size;++i){
		QSharedPointer<ParametersGroup> a=_ptr->_collections[i];
		if(a.data()==collection)
			break;
	}
	if(i==size)
		return -1;
	return i;
}

void ParametersManager::saveToFile( const QString& fileName )
{
	XMLHandler handler;
	handler.Create();
	JXMLItem xmlRoot=handler.GetRoot();
	JXMLItem xmlEasyPlot=handler.GetFirstChild(xmlRoot);
	JXMLItem nodeParameters=handler.AddChild(xmlEasyPlot,"PARAMETERS");

	ParametersManager* parametersManager=this;
	int count=parametersManager->getCollectionCount();
	for(int i=0;i<count;++i)
	{
		JXMLItem nodeParaCollection=handler.AddChild(nodeParameters,"COLLECTION");
		ParametersGroup* collection=parametersManager->getCollection(i);
		handler.SetAttribString(nodeParaCollection,"NAME",collection->getName());

		collection->reset();
		while (const ParameterItem* item = collection->next()) {
			if ((!item->getDebugOnly() || parametersManager->isDebug()) && item->getChangeable()) {
				JXMLItem nodePara=handler.AddChild(nodeParaCollection,"ITEM");
				handler.SetAttribString(nodePara,"KEY",item->getKeyword());
				handler.SetAttribString(nodePara,"VALUE",item->getVariant().toString());
				handler.SetAttribLong(nodePara,"TYPE",item->getType());
				handler.SetAttribLong(nodePara,"CHANGEABLE",item->getChangeable()?1:0);
				handler.SetAttribLong(nodePara,"DEBUG",item->getDebugOnly()?1:0);
			}
		}
	}

	handler.Save(fileName);

}



static bool _setItem(ParameterItem& item,QString strValue)
{
	QVariant value = strValue;
	int type=item.getType();
	bool valid = false;
	switch (type) {
	case QVariant::Bool:
		if ((valid = value.canConvert<bool>()) == true) {
			value = value.toBool();
		}
		break;
	case QVariant::Int:
		if ((valid = value.canConvert<int>()) == true) {
			value = value.toInt();
		}
		break;
	case QVariant::UInt:
		if ((valid = value.canConvert<uint>()) == true) {
			value = value.toUInt();
		}
		break;
	case QMetaType::Float:
	case QVariant::Double:
		if ((valid = value.canConvert<double>()) == true) {
			value = value.toDouble();
		}
		break;
	case QVariant::String:
	case ParameterItem::PathString:
	case ParameterItem::DirString:
		if ((valid = value.canConvert<QString>()) == true) {
			value = value.toString();
		}
		break;
	case QVariant::Color:
		if ((valid = value.canConvert<QColor>()) == true) {
			value = value.value<QColor>();
		}
		break;
	case ParameterItem::VoidStarPointer:
		if ((valid = value.canConvert<qlonglong>()) == true) {
			value = value.toLongLong();
		}
		break;
	default:
		break;
	}
	if (valid) {
		item.setVariant(value);
		return true;
	}
	return false;
}


void ParametersManager::loadFromFile( const QString& fileName )
{
	XMLHandler handler;
	if(!handler.Open(fileName))
		return;
	JXMLItem xmlRoot=handler.GetRoot();
	if(!xmlRoot)
		return;
	JXMLItem xmlEasyPlot=handler.GetFirstChild(xmlRoot);
	if(!xmlEasyPlot)
		return;
	JXMLItem nodeParameters=handler.GetFirstChild(xmlEasyPlot,"PARAMETERS");
	if(!nodeParameters)
		return;

	ParametersManager* parametersManager=this;
	JXMLItem curr=handler.GetFirstChild(nodeParameters);
	while(curr)
	{
		QString name=handler.GetAttribString(curr,"NAME");
		ParametersGroup* collection=parametersManager->addCollection(name);

		JXMLItem nodePara=handler.GetFirstChild(curr);
		while (nodePara) {
			ParameterItem item;
			item.setKeyword(handler.GetAttribString(nodePara,"KEY"));
			item.setType(handler.GetAttribLong(nodePara,"TYPE"));
			QString strValue=handler.GetAttribString(nodePara,"VALUE");
			_setItem(item,strValue);

			item.setChangeable(handler.GetAttribLong(nodePara,"CHANGEABLE",0)==1);
			item.setDebugOnly(handler.GetAttribLong(nodePara,"DEBUG",0)==1);

			collection->set(item);
			
			nodePara=handler.GetNextSibling(nodePara);
		}

		curr=handler.GetNextSibling(curr);
	}
}

void ParametersManager::notifyListeners( ParametersGroup* parameterGroup,const ParameterItem* newitem,const ParameterItem* oldItem )
{
	int n=_ptr->_listeners.count();
	for(int i=0;i<n;++i){
		IParametersModificationListener* listener=_ptr->_listeners[i];
		if(listener->parameterChanged(parameterGroup,newitem,oldItem))
			;//return;
	}
}

void ParametersManager::attach( IParametersModificationListener* listener )
{
	_ptr->_listeners.push_back(listener);
}

void ParametersManager::disattach( IParametersModificationListener* listener )
{
	_ptr->_listeners.removeAll(listener);
}

ParametersGroup* ParametersManager::getOrCreateGroup( const QString& groupName )
{
	ParametersGroup* group=getCollection(groupName);
	if(!group){
		return addCollection(groupName);
	}
	return group;
}





}
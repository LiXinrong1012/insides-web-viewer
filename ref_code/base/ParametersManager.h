#pragma once

#include "Base/base_global.h"
#include <QString>
#include <QVariant>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QList>


namespace Base{

class ParametersGroupPrivate;
class ParametersGroup;
class ParameterItem;
class ParametersManager;


class IParametersModificationListener
{
protected:
	virtual bool parameterChanged(ParametersGroup* parameterManager,
		const ParameterItem* newParameter,const ParameterItem* oldParameter)=0;

	friend class ParametersManager;
};


/*!
*	This class defines a simple parameter item.
*	@author	Jerry parameter
*	@date	2011.11.19
*/
class BASE_EXPORT ParameterItem
{
public:
	typedef QString KeyType;
	enum {ValidType=0,VoidStarPointer=257,PathString=258,DirString=259};

	ParameterItem();
	ParameterItem(const KeyType& key,const QVariant& value,bool changeable=true,
		bool debugOnly=false,int type=ValidType);

	const KeyType& getKeyword()const{return _keyword;}
	void setKeyword(const QString& name){_keyword=name;}

	/*!
	*	Get the stored variant.
	*	@note The variant is only for reading.
	*/
	const QVariant& getVariant()const{return _variant;}
	/*!
	*	Set the stored variant.
	*	@note The variant should hold the same type of the original one.
	*/
	void setVariant(const QVariant& v);

	/*!	Get whether this item is changeable.*/
	bool getChangeable()const{return _bChangeable;}
	void setChangeable(bool b){_bChangeable=b;}

	/*!	
	*	Get whether this item is only used for debug.
	*	When an item is used for debug, it should not show to users.
	*/
	bool getDebugOnly()const{return _bDebugOnly;}
	void setDebugOnly(bool t){_bDebugOnly=t;}

	/*!
	*	Get variant's type.
	*	@li QMetaType::Bool 1 bool.
	*	@li QMetaType::Int 2 int
	*	@li QMetaType::UInt 3 unsigned int
	*	@li QMetaType::Double 6 double
	*	@li QMetaType::QString 10 QString
	*	@li QMetaType::QColor 67 QColor
	*	@li ParameterItem::VoidStarPointer 257	qlongqlong 
	*	@li ParameterItem::PathString 258 QString
	*	@li ParameterItem::DirString 259 QString
	*/
	int getType()const;
	void setType(int t){_type=t;}

	KeyType getDiscription(){return _discription;}
	void setDiscription(const KeyType& v ){_discription=v;}

	friend class ParametersGroup;

private:
	KeyType		_keyword;
	KeyType		_discription;
	QVariant	_variant;
	bool		_bChangeable;
	bool		_bDebugOnly;
	int			_type;
};

/*!
*	This class is used for storing a list of parameter items.
*
*	The parameter items is identified by their keywords.
*/
class BASE_EXPORT ParametersGroup
{
public:
	typedef QString KeyType;

	ParametersGroup::ParametersGroup(ParametersManager* parent);
	~ParametersGroup(void);

	/// Get the name of this collection
	QString getName();
	
	/// Set the name of this collection
	void setName(const QString& name);

	/// Get a parameter, return null if this parameter doesn't exist.
	const ParameterItem* get(const KeyType& key)const;

	/// Set a parameter
	void set(const ParameterItem& item,bool overrid=true);
	//void setValue(const KeyType& name,const QVariant& value);

	void clear();

	/*!
	*	Reset.
	*/
	void reset();
	/*!
	*	Return next parameter item.
	*/
	const ParameterItem* next();

	ParametersManager* getParent();

private:
	QScopedPointer<ParametersGroupPrivate> _ptr;

};


class ParametersManagerPrivate;


class BASE_EXPORT ParametersManager
{
public:
	ParametersManager();
	~ParametersManager();


	// to support listeners, Jerry, 2014.6.16
	void attach(IParametersModificationListener* listener);
	void disattach(IParametersModificationListener* listener);

	typedef QString KeyType;

	ParametersGroup* getDefaultCollection();
	const ParametersGroup* getDefaultCollection()const;
	void setDefaultCollection(ParametersGroup* p);
	ParametersGroup* getCollection(const QString& collection);
	const ParametersGroup* getCollection(const QString& collection)const;
	int	getCollectionCount()const;
	int indexOf(ParametersGroup* collection)const;
	ParametersGroup* getCollection(int index);
	ParametersGroup* addCollection(const QString& collectionName);
	ParametersGroup* getOrCreateGroup(const QString& groupName);

	/*!
	*	Try to find a parameter item in specified place.
	*	@param key Parameter item's keyword.
	*	@param type The specified store palce.
	*	@return Return true if the parameter exists in specified store place.
	*/
	const ParameterItem* get(const KeyType& key,const QString& collectionName=QString())const;

	bool get(const KeyType& key, void** result,const QString& collectionName=QString());
	template<class T>  T* get(const KeyType& key);


	/*!
	*	Store an parameter item in specified store place.
	*	@note If an parameter item with keyword value exists, the original one would be deleted,
	*	and this function will return false. Otherwise, this function will return true.
	*/
	bool setValue(const KeyType& key,const QVariant& v,const QString& collection=QString());
	/*!
	*	Store a pointer in specified store place.
	*/
	bool set(const KeyType& key, void* value,const QString& collection=QString());
	void set(const ParameterItem& item,const QString& groupName=QString());

	void clear();
	void clear(const QString& collectionName);
	void remove(const QString& collectionName);
	void remove(int index);
	void removeAll();


	bool isDebug();
	void setDebug(bool b=true);

	void saveToFile(const QString& fileName);
	void loadFromFile(const QString& fileName);

private:
	void notifyListeners(ParametersGroup* parameterGroup,const ParameterItem* newitem,const ParameterItem* newItem);

	Q_DISABLE_COPY(ParametersManager);

	QScopedPointer<ParametersManagerPrivate> _ptr;

	friend class ParametersGroup;

};

template<class T>
T* ParametersManager::get(const KeyType& key)
{
	void* tmp;
	if(get(key,&tmp)){
		return (T*)tmp;
	}
	return NULL;
}







}		//end namespace Base

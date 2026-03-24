#pragma once

#include "base/base_global.h"
#include <QList>
#include <QString>
#include <QVariant>
#include <QSharedPointer>
#include <QStringList>
#include <QAbstractItemDelegate>

namespace INSIDES
{
	class BaseItem;
}

/*!
*	This class stands for a property definition that can be show in tree view.
*	@author Jerry He
*	@date	2014.6
*/
struct BASE_EXPORT TreeItemProperty
{
	/// The order in the related group
	int			index;
	/// name of this property
	QString		name;
	/// type of this property, can be QVariant::Type or user-defined type
	int			type;
	/// whether this properties is editable
	bool		editable;
	/// width display in tree view
	int			width;

	TreeItemProperty():index(0),type(0),editable(false),width(30){}
	TreeItemProperty(const QString&n,int t,bool e,int w):name(n),type(t),editable(e),width(w){}

	QString getDisplayName()const;
};

class BASE_EXPORT ITreeItemPropertyFunc
{
public:
	virtual QString getKeyname()const=0;
	virtual QVariant getData(INSIDES::BaseItem* baseItem,int index)=0;
	virtual bool setData(INSIDES::BaseItem* baseItem,int index,const QVariant& data)=0;
};


class BASE_EXPORT TreeItemPropertyGroup
{
public:
	TreeItemPropertyGroup(void){}
	virtual ~TreeItemPropertyGroup(void){}

	QString getKeyname()const{return _keyname;}
	void setKeyname(const QString& name){_keyname=name;}

	TreeItemPropertyGroup& addProperty(const TreeItemProperty& p);
	TreeItemProperty* getProperty(int index){return &_propertylist[index];}
	const TreeItemProperty* getProperty(int index)const{return &_propertylist[index];}
	TreeItemProperty* getProperty(const QString& name);

	int getCount()const{return _propertylist.size();}
	int indexOf(const QString& name)const;

protected:
	QList<TreeItemProperty>	_propertylist;
	QString		_keyname;
};


class BASE_EXPORT TreeItemPropertyManager
{
public:
	static TreeItemPropertyManager* instance();
	void saveState();
	void loadState();

	void addGroup(TreeItemPropertyGroup* pros);

	TreeItemPropertyGroup* getGroup(const QString& name);
	const TreeItemPropertyGroup* getGroup(int index)const{return _itemValueList[index].data();}
	TreeItemPropertyGroup* getGroup(int index){return _itemValueList[index].data();}

	int getCount()const{return _itemValueList.size();}
	QString getKeyname(int index)const{return _itemValueList[index]->getKeyname();}

	int getFirstColumnWidth()const{return _firstColumnWidth;}
	void setFirstColumnWidth(int w){_firstColumnWidth=w;}

	/// get the selected items that would be shown in the tree view.
	QStringList& getSelectedItems(){return _selectedItemList;}
	void setSelectedItems(const QStringList& l){_selectedItemList=l;}

	void addItemDelegate(int type,QAbstractItemDelegate* itemDele);
	QAbstractItemDelegate* getItemDelegate(int type);


protected:
	typedef QSharedPointer<TreeItemPropertyGroup> ItemPointer;
	typedef QSharedPointer<QAbstractItemDelegate> DelegatePointer;
	typedef QMap<int,DelegatePointer> DelegateMap;

	QList<ItemPointer>	_itemValueList;
	int					_firstColumnWidth;	//第一列的宽度。
	QStringList			_selectedItemList;
	DelegateMap			_delegateMap;

	Q_DISABLE_COPY(TreeItemPropertyManager);
	TreeItemPropertyManager();
	~TreeItemPropertyManager();
};
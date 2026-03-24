#include "TreeItemPropertyManager.h"
#include <QSettings>
#include <QtCore>

#include "Console.h"

using namespace INSIDES;

QString TreeItemProperty::getDisplayName() const
{
	QStringList vec=name.split("::");
#ifdef _DEBUG
	if (vec.size()==1){
		Base::Console().Warning("Property without parent view");
	}
#endif
	return vec[vec.size()-1];
}


////////////////////////////////////////////////////////////////////////////////
int TreeItemPropertyGroup::indexOf( const QString& name ) const
{
	int n=_propertylist.size();
	for(int i=0;i<n;++i)
		if(_propertylist[i].name.compare(name,Qt::CaseInsensitive)==0)
			return i;
	return -1;
}

TreeItemProperty* TreeItemPropertyGroup::getProperty( const QString& name )
{
	int tmp=indexOf(name);
	if(tmp==-1)
		return NULL;
	return &_propertylist[tmp];
}


TreeItemPropertyGroup& TreeItemPropertyGroup::addProperty( const TreeItemProperty& p )
{
	_propertylist.push_back(p);
	_propertylist[_propertylist.size()-1].index=_propertylist.size()-1;
	return *this;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
TreeItemPropertyManager* TreeItemPropertyManager::instance()
{
	static TreeItemPropertyManager tmp;
	return &tmp;
}

TreeItemPropertyManager::TreeItemPropertyManager()
	:_firstColumnWidth(150)
{
}
TreeItemPropertyManager::~TreeItemPropertyManager()
{
}
void TreeItemPropertyManager::saveState()
{
	QSettings settings("JERRYHE","INSIDESVIEWER");
	settings.beginGroup("TREEITEMS");
	settings.setValue("SELECTED",_selectedItemList);

	settings.beginWriteArray("VIEW");
	int n=getCount();
	for(int i=0;i<n;++i){
		settings.setArrayIndex(i);
		const TreeItemPropertyGroup* props=getGroup(i);
		settings.beginWriteArray("ITEMS");

		int n2=props->getCount();
		for(int j=0;j<n2;++j){
			settings.setArrayIndex(j);
			settings.setValue("WIDTH",props->getProperty(j)->width);
		}

		settings.endArray();
	}

	settings.endArray();
	settings.endGroup();

}

void TreeItemPropertyManager::loadState()
{
	QSettings settings("JERRYHE","INSIDESVIEWER");
	settings.beginGroup("TREEITEMS");
	QStringList tmp=settings.value("SELECTED").toStringList();
	_selectedItemList=tmp;

	int n=settings.beginReadArray("VIEW");
	for(int i=0;i<n;++i){
		settings.setArrayIndex(i);
		TreeItemPropertyGroup* props=getGroup(i);
		if(!props)
			continue;

		int n2=settings.beginReadArray("ITEMS");

		for(int j=0;j<n2;++j){
			settings.setArrayIndex(j);
			props->getProperty(j)->width=settings.value("WIDTH",20).toInt();
		}


		settings.endArray();
	}

	settings.endArray();

	settings.endGroup();
}


void TreeItemPropertyManager::addGroup( TreeItemPropertyGroup* pros )
{
#ifdef _DEBUG
	if(pros->getKeyname().isEmpty() ||
		getGroup(pros->getKeyname())){
			Base::Console().Error("Has added duplicate TreeItemPropertyGroup.(%s)",
				pros->getKeyname().toStdString().c_str());
	}
#endif
	_itemValueList.push_back(QSharedPointer<TreeItemPropertyGroup>(pros));
}

TreeItemPropertyGroup* TreeItemPropertyManager::getGroup( const QString& name )
{
	int n=_itemValueList.size();
	for(int i=0;i<n;++i)
		if(_itemValueList[i]->getKeyname().compare(name,Qt::CaseInsensitive)==0)
			return _itemValueList[i].data();

	return NULL;
}

void TreeItemPropertyManager::addItemDelegate( int type,QAbstractItemDelegate* itemDele )
{
#ifdef _DEBUG
	// check whether there already exists this type delegate
	if(getItemDelegate(type)){
		Base::Console().Warning("Has added duplicate tree item delegates.");
	}
#endif
	_delegateMap[type]=QSharedPointer<QAbstractItemDelegate>(itemDele);
}

QAbstractItemDelegate* TreeItemPropertyManager::getItemDelegate( int type )
{
	DelegateMap::Iterator f=_delegateMap.find(type);
	if(f==_delegateMap.end())
		return NULL;
	return f.value().data();
}

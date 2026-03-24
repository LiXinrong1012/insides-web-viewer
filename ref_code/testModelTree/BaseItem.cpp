#include "BaseItem.h"
#include <QtCore>

BaseItem::BaseItem(void)
	:_parent(NULL)
	,_visibilityType(BaseItem::Visual)
{
	static int id=1;
	QString name=QString("Item_%1").arg(id++);

}


BaseItem::~BaseItem(void)
{
	qDeleteAll(_itemlist);
}

bool BaseItem::insertChild( int pos,BaseItem* item )
{
	_itemlist.insert(pos,item);
	return true;
}

bool BaseItem::appendChild( BaseItem* item )
{
	_itemlist.push_back(item);
	item->_parent=this;
	return true;
}

int BaseItem::row() const
{
	if(_parent)
		return _parent->indexOf(const_cast<BaseItem*>(this));
	else
		return 0;
}

int BaseItem::indexOf( BaseItem* const item ) const
{
	return _itemlist.indexOf(item);
}

bool BaseItem::remove( BaseItem* item )
{
	_itemlist.remove(item);
	return true;
}

bool BaseItem::clearChildren()
{
	qDeleteAll(_itemlist);
	return true;
}

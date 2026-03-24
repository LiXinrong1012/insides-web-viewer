#include "modeldocument.h"

#include "BaseItem.h"

ModelDocument::ModelDocument(QObject *parent)
	: QObject(parent)
	,_enableSignal(true)
{
	_rootItem=new BaseItem();
}

ModelDocument::~ModelDocument()
{
	delete _rootItem;
}

ModelDocument* ModelDocument::instance()
{
	static PreDocument* _instance=NULL;
	if(!_instance)
		_instance=new PreDocument(NULL);
	return _instance;
}

void ModelDocument::setCurrentRoot(BaseItem* root)
{
	if(_currentRoot==root)
		return;

	if(_enableSignal)
		emit beginRootItemChanging(_currentRoot);
	_currentRoot=root;
	if(_enableSignal)
		emit rootItemChanged(root);
}

void ModelDocument::appendChild( BaseItem* parent,BaseItem* item )
{
	parent->appendChild(item);
	if(_enableSignal)
		emit itemAdded(item,true);
}

void ModelDocument::removeItem( BaseItem* item )
{
	BaseItem* parent=item->_parent;
	if(!parent)
		return;
	parent->remove(item);
	if(_enableSignal)
		emit itemRemoved(parent,item);
	delete item;
}

void ModelDocument::modifyItem( BaseItem* src,BaseItem* dst )
{
	dst->_visibilityType=src->_visibilityType;
}

void ModelDocument::createDefault()
{
	_enableSignal=true;
	_rootItem->clearChildren();

	BaseItem* i1=new BaseItem();
	BaseItem* i2=new BaseItem();
	BaseItem* i3=new BaseItem();
	BaseItem* i4=new BaseItem();
	i1->appendChild(i2);
	i1->appendChild(i3);
	_rootItem->appendChild(i1);
	_rootItem->appendChild(i4);

	_enableSignal=false;
	notifyModelReseted(_rootItem);
	if(_enableSignal)
		emit modelReseted(_rootItem);
}

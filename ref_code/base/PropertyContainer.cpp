#include "PropertyContainer.h"
#include "pre_compile.h"
#include "base/base_global.h"
#include "Console.h"
#include <assert.h>
#include <algorithm>

using namespace Base;


PropertyNode::PropertyNode()
:_item(NULL),
_property(NULL),
_parent(NULL)
{
}
PropertyNode::PropertyNode(PropertyTypeItem* item)
:_item(item),
_property(NULL),
_parent(NULL)
{
}
PropertyNode::~PropertyNode()
{
	clear();
}
void PropertyNode::clear()
{
	clearChildren();
	delete _property;
}
bool PropertyNode::insertChild(PropertyNode* node)
{
	_childs.push_back(node);
	node->setParent(this);
	return true;
}

void PropertyNode::clearChildren()
{
	for(unsigned int i=0;i<_childs.size();++i)
		delete _childs[i];
	_childs.clear();
}
static int _PropertyNodeComp(PropertyNode* node1,PropertyNode *node2)
{
	if(node1->getPropertyItem()->getId()<node2->getPropertyItem()->getId())
		return 1;
	return -1;
}
void PropertyNode::sortChildren()
{
	sort(_childs.begin(),_childs.end(),_PropertyNodeComp);
}

void PropertyNode::clearPropertyData()
{
	delete _property;
	_property=NULL;
	for(unsigned int i=0;i<_childs.size();++i)
		_childs[i]->clearPropertyData();
}
void PropertyNode::createPropertyData()
{
	_property=Property::create(_item);
	for(unsigned int i=0;i<_childs.size();++i)
		_childs[i]->createPropertyData();
}
PropertyNode* PropertyNode::findPropertyNode(PropertyTypeItem* item)
{
	for(unsigned int i=0;i<_childs.size();++i)
		if(_childs[i]->getPropertyItem()==item)
			return _childs[i];
	return NULL;
}
void PropertyNode::getAllPropertyTypeItemList(vector<PropertyTypeItem*>& l)
{
	if(_item)
		l.push_back(_item);
	int size=_childs.size();
	for(int i=0;i<size;++i)
		_childs[i]->getAllPropertyTypeItemList(l);
}
void PropertyNode::getAllPropertyList(vector<Property*>& l)
{
	if(_property)
		l.push_back(_property);
	int size=_childs.size();
	for(int i=0;i<size;++i)
		_childs[i]->getAllPropertyList(l);
}
void PropertyNode::getAllPropertyNodeList(vector<PropertyNode*>& l)
{
	if(_property)
		l.push_back(this);
	int size=_childs.size();
	for(int i=0;i<size;++i)
		_childs[i]->getAllPropertyNodeList(l);
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

PropertyContainer& Base::operator >> (PropertyContainer & s,const string& bar)
{
	s.insert(bar);
	return s;
}

PropertyContainer& PropertyContainer::addOrCreatePropertyItem(const string& strLine)
{
	PropertyTypeItem* item=PropertyManager()->add(strLine);
	assert(item);
	insert(item);
	return *this;
}

PropertyContainer::PropertyContainer(void)
:_propertyNodesHead(new PropertyNode())
{
}

PropertyContainer::~PropertyContainer(void)
{
	delete _propertyNodesHead;
}



void PropertyContainer::insert(string typeName)
{
	PropertyTypeItem* p=Base::PropertyManager()->getPropertyTypeItem(typeName);
#ifdef _DEBUG
	if(!p){
		Base::Console().Error("Try to insert unexisted property type: %s .",typeName);
		return;}
#endif
	insert(p);
}
void PropertyContainer::insert(Base::PropertyTypeItem *p)
{
	PropertyTypeItem* curr=p;
	vector<PropertyTypeItem*> vecs;
	while(p){
		vecs.push_back(p);
		p=p->getParent();
	}

	PropertyNode* currentParent=_propertyNodesHead;
	for(int i=vecs.size()-1;i>=0;--i){
		PropertyTypeItem* item=vecs[i];
		currentParent=findOrCreatePropertyNode(item,currentParent);
	}
}
void PropertyContainer::insert(unsigned int typeId)
{
	PropertyTypeItem* p=PropertyManager()->getPropertyTypeItem(typeId);
#ifdef _DEBUG
	if(!p){
		Base::Console().Error("Try to insert nonexistent property type: %s .",typeId);
		return;}
#endif
	insert(p);
}
PropertyNode* PropertyContainer::findOrCreatePropertyNode(PropertyTypeItem* item,PropertyNode* parent)
{
	PropertyNode* node=findPropertyNode(item);
	if(node)
		return node;
	PropertyNode* newNode=new PropertyNode(item);
	parent->insertChild(newNode);
	_propertyTypeItemMap[item]=newNode;
	return newNode;
}
PropertyNode* PropertyContainer::findPropertyNode(PropertyTypeItem* item)
{
	map<PropertyTypeItem*,PropertyNode*>::iterator f=_propertyTypeItemMap.find(item);
	if(f==_propertyTypeItemMap.end())
		return NULL;
	return f->second;
}

bool PropertyContainer::createData()
{
	clearData();

	for(unsigned int i=0;i<_propertyNodesHead->childSize();++i)
		_propertyNodesHead->getChild(i)->createPropertyData();
	return true;

}
bool PropertyContainer::clearData()
{
	for(unsigned int i=0;i<_propertyNodesHead->childSize();++i)
		_propertyNodesHead->getChild(i)->clearPropertyData();
	return true;
}
bool PropertyContainer::clear()
{
	_propertyNodesHead->clear();
	_propertyTypeItemMap.clear();
	return true;
}

void PropertyContainer::setPropertiesModified(bool s)
{
	vector<Property*> vec;
	_propertyNodesHead->getAllPropertyList(vec);
	for(unsigned int i=0;i<vec.size();++i)
		vec[i]->setModified(s);
}
std::vector<Property*> PropertyContainer::getPropertyList()const
{
	vector<Property*> vec;
	_propertyNodesHead->getAllPropertyList(vec);
	return vec;
}
std::vector<PropertyTypeItem*> PropertyContainer::getPropertyTypeItemList()const
{
	vector<PropertyTypeItem*> vec;
	_propertyNodesHead->getAllPropertyTypeItemList(vec);
	return vec;
}
std::vector<PropertyNode*> PropertyContainer::getPropertyNodeList()const
{
	vector<PropertyNode*> vec;
	_propertyNodesHead->getAllPropertyNodeList(vec);
	return vec;
}
bool PropertyContainer::intersect(const std::vector<const PropertyContainer*> &propertyContainer,
					  PropertyContainer *result)
{
	result->clear();
	int size=propertyContainer.size(),typeSize=PropertyManager()->propertyTypeItemNum()+1;
	if(size==0||
		typeSize==1)
		return true;
	vector<int> vec(typeSize,0);
	for(int i=0;i<size;++i){
		const PropertyContainer* p=propertyContainer[i];
		const vector<PropertyTypeItem*> plist=p->getPropertyTypeItemList();
		for(unsigned int j=0;j<plist.size();++j)
			vec[plist[j]->getId()]++;
	}
	for(int i=1;i<typeSize;i++){
		if(vec[i]==size)
			result->insert(i);
	}
	return true;
}


bool PropertyContainer::intersect(const std::vector<PropertyContainer*> &propertyContainer,
					  PropertyContainer *result)
{
	/*return PropertyContainer::intersect(propertyContainer,result);
	return true;
	*/
	return true;
}

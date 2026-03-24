#pragma once

#include "Property.h"
#include <vector>

namespace Base{

class BASE_EXPORT PropertyNode{
public:
	PropertyNode();
	PropertyNode(PropertyTypeItem* item);
	~PropertyNode();

	PropertyTypeItem* getPropertyItem(){return _item;}
	unsigned int childSize(){return _childs.size();}
	PropertyNode* getChild(unsigned int index){return _childs[index];}

	PropertyNode* findPropertyNode(PropertyTypeItem* item);

	void setPropertyItem(PropertyTypeItem* item){_item=item;}
	bool insertChild(PropertyNode* node);


	void clearChildren();
	void sortChildren();

	void clearPropertyData();
	void createPropertyData();

	void clear();

	Property* getProperty(){return _property;}

	PropertyNode* getParent(){return _parent;}
	void setParent(PropertyNode* node){_parent=node;}

	void getAllPropertyTypeItemList(vector<PropertyTypeItem*>& l);
	void getAllPropertyList(vector<Property*>& l);

	/*! only get PropertyNodes with a non-NULL _property. */
	void getAllPropertyNodeList(vector<PropertyNode*>& l);
	
protected:
	PropertyTypeItem*	_item;
	Property*		_property;
	PropertyNode*	_parent;
	std::vector<PropertyNode*> _childs;
};

class BASE_EXPORT PropertyContainer
{
public:
	PropertyContainer(void);
	~PropertyContainer(void);

	void insert(string typeName);
	void insert(PropertyTypeItem* item);
	void insert(unsigned int typeId);

	PropertyNode* findOrCreatePropertyNode(PropertyTypeItem* item,PropertyNode* parent);
	PropertyNode* findPropertyNode(PropertyTypeItem* item);

	bool createData();
	bool clearData();
	bool clear();

	PropertyContainer& addOrCreatePropertyItem(const string& strLine);

	void setPropertiesModified(bool s);

	std::vector<Property*> getPropertyList()const;
	std::vector<PropertyTypeItem*> getPropertyTypeItemList()const;
	std::vector<PropertyNode*> getPropertyNodeList()const;

	PropertyNode* getRootNode(){return _propertyNodesHead;}

	enum SortType{ST_KEY,ST_NAME};
	void sort(SortType t=ST_KEY);

	static bool intersect(const std::vector<const PropertyContainer*> &propertyContainer,
		PropertyContainer *result);
	static bool intersect(const std::vector< PropertyContainer*> &propertyContainer,
		PropertyContainer *result);

protected:
	PropertyNode* _propertyNodesHead;
	std::map<PropertyTypeItem*,PropertyNode*> _propertyTypeItemMap;
};

BASE_EXPORT PropertyContainer& operator >> (PropertyContainer & s,const string& bar);

}
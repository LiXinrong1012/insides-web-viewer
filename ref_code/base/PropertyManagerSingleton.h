#pragma once
#include "base/base_global.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

namespace Base{

enum UiType{
	UT_UNKNOWN,
	UT_STRING,
	UT_BOOL,
	UT_INT,
	UT_FLOAT,
	UT_COLOR,
	UT_COMBO,
	UT_FILE,
	UT_MAPS,
	UT_PANEL,
	UT_SIZE
};


class BASE_EXPORT PropertyTypeItem{
public:
	PropertyTypeItem();
	PropertyTypeItem(string keyName,string discription,UiType uiType);
	PropertyTypeItem(string keyName,UiType uiType);
	PropertyTypeItem(string keyName,UiType uiType,unsigned int i);
	PropertyTypeItem(string keyName,string discription,UiType uiType,unsigned int i);

	const string& getKeyName()const{return _keyName;}
	void setKeyName(const string& keyName){_keyName=keyName;}

	const string& getDiscription()const{return _discription;}
	void setDiscription(const string& discription){_discription=discription;}

	UiType getUiType()const{return _uiType;}
	void setUiType(UiType type){_uiType=type;}

	unsigned int getId()const{return _id;}
	void setId(unsigned int id){_id=id;}

	PropertyTypeItem* getParent()const{return _parent;}
	void setParent(PropertyTypeItem* item){_parent=item;}

	static PropertyTypeItem* createPanel(const string & panelName);

	void output(ofstream& out);

protected:
	string	_keyName;
	string	_discription;
	UiType	_uiType;
	unsigned int _id;
	PropertyTypeItem* _parent;
};
class BASE_EXPORT PropertyManagerSingleton
{
public:
	static PropertyManagerSingleton* instance();
	static void destruct(PropertyManagerSingleton* p);

	unsigned int propertyTypeItemNum(){return _propertyTypeItems.size();}

	PropertyTypeItem* add(const PropertyTypeItem& item);
	PropertyTypeItem* add(PropertyTypeItem* item);
	/*! example: Base::Name Int */
	PropertyTypeItem* add(const string& strline);
	PropertyTypeItem* add(const string & itemFullName,UiType uiType);

	PropertyTypeItem* getPropertyTypeItem(string name);
	PropertyTypeItem* getPropertyTypeItem(unsigned int id);
	void clear();

	void writeToFile(string fileName);
private:
	PropertyManagerSingleton(void);
	~PropertyManagerSingleton(void);

	static PropertyManagerSingleton* _instance;
	std::vector<PropertyTypeItem*>	_propertyTypeItems;
	map<string,PropertyTypeItem*>	_propertyTypeItemMap;

	void initPropertyTypeItems();
};

BASE_EXPORT PropertyManagerSingleton& operator >> (PropertyManagerSingleton & s,const string& bar);

inline PropertyManagerSingleton* PropertyManager(){
	return PropertyManagerSingleton::instance();
}

}//end namespace Base.
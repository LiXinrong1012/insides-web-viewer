#pragma once
#include <string>
#include <vector>
using namespace std;
#include "PropertyManagerSingleton.h"
namespace Base{

class BASE_EXPORT Property
{
public:
	Property(const PropertyTypeItem* type);
	virtual ~Property(void);

	const PropertyTypeItem* getType()const{return _type;}
	const std::string& getTypeName()const;
	const std::string& getDiscription()const;
	UiType getUiType()const;
	
	static Property* create(PropertyTypeItem* type);

	bool modified()const{return _modified;}
	void setModified(bool b){_modified=b;}
	

protected:
	const PropertyTypeItem* _type;
	bool _modified;
};

//to-do: use template classs. Jerry 2011.3.27.
template<class T>
class TemplateProperty:public Property
{
public:
	TemplateProperty(PropertyTypeItem* type):Property(type){}
	virtual ~TemplateProperty(){}
	void setValue(const T& v){if(_value!=v){setModified(true);_value=v;}}
	const T& value(){return _value;}
protected:
	T _value;
};

typedef TemplateProperty<int> IntProperty;
typedef TemplateProperty<string> StringProperty;
typedef TemplateProperty<bool> BoolProperty;
typedef TemplateProperty<float> FloatProperty;
typedef std::map<string,string> InformationPropertyItem;
typedef TemplateProperty<InformationPropertyItem> InformationProperty;


class BASE_EXPORT ColorProperty: public Property
{
public:
	ColorProperty(PropertyTypeItem* type);
	virtual ~ColorProperty(){}
	void setValue(const int*);
	const int* value();
protected:
	int _rgba[4];
};

class BASE_EXPORT ComboProperty: public Property
{
public:
	typedef std::vector<string> LabelStringList;
	ComboProperty(PropertyTypeItem* type);
	void setValue(int v);
	int value()const{return _value;}
	void clearComboList();
	void pushBack(const string& str){_strLabelList.push_back(str);}
	const LabelStringList& getLabelStringList(){return _strLabelList;}
private:
	std::vector<string> _strLabelList;
	int _value;
};



} //end namesapce Base
#include "Property.h"
#include "Console.h"
using namespace std;
using namespace Base;


Property* Property::create(PropertyTypeItem* type)
{
	switch(type->getUiType())
	{
	case UT_INT:
		return new IntProperty(type);
	case UT_STRING:
		return new StringProperty(type);
	case UT_BOOL:
		return new BoolProperty(type);
	case UT_FLOAT:
		return new FloatProperty(type);
	case UT_COMBO:
		return new ComboProperty(type);
	case UT_COLOR:
		return new ColorProperty(type);
	case UT_MAPS:
		return new InformationProperty(type);
	case UT_PANEL:
		return new Property(type);
	default:
		return NULL;
	}
	return NULL;
}

Base::UiType Property::getUiType()const
{
	return _type->getUiType();
}
const string& Property::getTypeName()const
{
	return _type->getKeyName();
}
const string& Property::getDiscription()const
{
	return _type->getDiscription();
}
Property::Property(const PropertyTypeItem* type):_modified(false)
{
	_type=type;
}

Property::~Property(void)
{
}




ColorProperty::ColorProperty(PropertyTypeItem* type):Property(type)
{
	for(int i=0;i<4;++i)
		_rgba[i]=255;
}
void ColorProperty::setValue(const int*a)
{
	for(int i=0;i<4;++i)
	{
		if(_rgba[i]!=a[i]){
			for(int j=0;j<4;j++)
				_rgba[j]=a[j];
			setModified(true);
			return;
		}
	}
}
const int* ColorProperty::value()
{
	return _rgba;
}


ComboProperty::ComboProperty(PropertyTypeItem* type):Property(type)
,_value(0)
{
}
void ComboProperty::setValue(int v)
{
#ifdef _DEBUG
	if(v>=_strLabelList.size()||v<0){
		Console().Error("Try to set value outflow.");
		return;
	}
#endif
	if(_value==v)
		return;
	_value=v;
	setModified(true);
}
void ComboProperty::clearComboList()
{
	_strLabelList.clear();
	_value=0;
}
#include "BaseClass.h"

namespace Base
{
	TYPESYSTEM_SOURCE_P(BaseClass);

	J_PROPERTY_SOURCE_P(BaseClass);

	bool BaseClass::getProperty(Property* p)
	{
		const string& key=p->getType()->getKeyName();
		if(key=="Type"){
			((IntProperty*)p)->setValue(getTypeId().getKey());
			return true;
		}
		return false;
	}
	bool BaseClass::setProperty(const Property*p)
	{
		return false;
	}

	void BaseClass::initProperty(PropertyContainer* p)
	{
		(*p)>>"Type";
	}


	void BaseClass::setPropertyContainerValue(const PropertyContainer* p){
		vector<Property*> propertyList=p->getPropertyList();
		int size=propertyList.size();
		for(int i=0;i<size;++i){
			if(propertyList[i]->modified())
				setProperty(propertyList[i]);
		}
	}
	void BaseClass::getPropertyContainerValue(PropertyContainer* p)
	{
		vector<Property*> propertyList=p->getPropertyList();
		int size=p->getPropertyList().size();
		for(int i=0;i<size;++i)
			getProperty(propertyList[i]);
	}




	BaseClass::BaseClass(void)
	{
	}

	BaseClass::~BaseClass(void)
	{
	}


	void BaseClass::init(void)
	{
		//when this class has already initialized, just pass.
		if(BaseClass::classTypeId!=Type::badType())
			return;

		initProperty(); //Jerry 2011.3.26

		//assert(BaseClass::classTypeId == Type::badType() && "don't init() twice!");
		/* Make sure superclass gets initialized before subclass. */ 
		/*assert(strcmp(#_parentclass_), "inherited"));*/
		/*Type parentType(Type::fromName(#_parentclass_));*/ 
		/*assert(parentType != Type::badType() && "you forgot init() on parentclass!");*/

		/* Set up entry in the type system. */ 
		BaseClass::classTypeId = 
			Type::createType(Type::badType(), 
			"Base::BaseClass", 
			BaseClass::create); 
	}


	void BaseClass::initSubclass(Base::Type &toInit,const char* ClassName, const char *ParentName, Type::instantiationMethod method)
	{
		// dont't init twice!
		if(toInit != Base::Type::badType())
			return;
		// get the parent class
		Base::Type parentType(Base::Type::fromName(ParentName)); 
		// forgot init parent!
		assert(parentType != Base::Type::badType() );

		// create the new type
		toInit = Base::Type::createType(parentType, ClassName, method);

	}

}//end namespace Base.
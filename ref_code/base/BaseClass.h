#pragma once
#include "Type.h"

#include "PropertyContainer.h"


#define REGISTER_TREEICON(name) \
	public: \
	virtual const char* getTreeIcon(){return name;}

#define REGISTER_TREEITEM_EXPANDED(trueOrNot) \
	public: \
	virtual bool isInitExpanded()const{return trueOrNot;};

namespace Base
{
	class BASE_EXPORT BaseClass
	{
		J_TYPE_PROPERTY_HEADER();

	public:
		BaseClass(void);
		~BaseClass(void);

		void getPropertyContainerValue(PropertyContainer* p);
		void setPropertyContainerValue(const PropertyContainer* p);

		bool isDerivedFrom(const Type type) const {return getTypeId().isDerivedFrom(type);}

	protected:

		static void initSubclass(Base::Type &toInit,const char* ClassName, const char *ParentName, Type::instantiationMethod method=0);

	};


}//end namespace Base.

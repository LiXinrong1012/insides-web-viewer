#pragma once
#include "BaseClass.h"

namespace Base{


class BASE_EXPORT TestClass :
	public Base::BaseClass
{
	TYPESYSTEM_HEADER();

public:
	TestClass(void);
	~TestClass(void);
};

}
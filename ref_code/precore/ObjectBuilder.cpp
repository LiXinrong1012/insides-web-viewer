#include "ObjectBuilder.h"
#include "precore/BaseItemFactory.h"

namespace INSIDES
{

ObjectBuilder::ObjectBuilder(void)
{
	_creator=BaseItemFactory();
}


ObjectBuilder::~ObjectBuilder(void)
{
}

BaseItem* ObjectBuilder::createObject( int category )
{
	return ((BaseItem*)_creator->Produce(category));
}

ObjectBuilder* ObjectBuilder::instance()
{
	static ObjectBuilder _instance;
	return &_instance;
}

}
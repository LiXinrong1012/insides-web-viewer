#include "BaseItemManager.h"
#include "BaseItemFactory.h"
#include "base/Console.h"

namespace INSIDES
{

BaseItemManager::BaseItemManager(void)
{
}


BaseItemManager::~BaseItemManager(void)
{
}

BaseItemManager* BaseItemManager::instance()
{
	static BaseItemManager _instance;
	return &_instance;
}

BaseItem* BaseItemManager::create( int typeID )
{
	BaseItem* item=(BaseItem*)BaseItemFactory()->Produce(typeID);
#ifdef _DEBUG
	if(!item){
		Base::Console().Error("Trying to create unregistered base item. (type = %d)",typeID);
		return item;
	}
#endif

	item->setCategory(typeID);
	return item;
}


}
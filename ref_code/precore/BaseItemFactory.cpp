#include "BaseItemFactory.h"


namespace INSIDES
{

BaseItemFactorySingleton::BaseItemFactorySingleton(void)
{
}


BaseItemFactorySingleton::~BaseItemFactorySingleton(void)
{
}

BaseItemFactorySingleton* BaseItemFactorySingleton::instance()
{
	static BaseItemFactorySingleton* _instance=NULL;
	if(!_instance)
		_instance=new BaseItemFactorySingleton();
	return _instance;
}

}
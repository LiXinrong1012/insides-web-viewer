#include "functionsmanager.h"

#include "base/Console.h"

using namespace std;

FunctionsManager::FunctionsManager()
{

}

FunctionsManager::~FunctionsManager()
{
	clear();
}

bool FunctionsManager::insert( const string& keyname, BaseFunction* function )
{
#if _DEBUG
	if(find(keyname)){
		Base::Console().Error("Inserting duplicate function: %s",keyname.c_str());
		return false;
	}
#endif
	_map[keyname]=function;
	return true;
}

void FunctionsManager::clear()
{
	for(StringToFunctionMap::iterator b=_map.begin();
		b!=_map.end();++b)
	{
		BaseFunction* function=b->second;
		delete function;
	}
	_map.clear();
}

#ifndef FUNCTIONSMANAGER_H
#define FUNCTIONSMANAGER_H

#include <string>
#include <map>
class BaseFunction;

class FunctionsManager
{
public:
	typedef std::map<std::string, BaseFunction*> StringToFunctionMap;

	FunctionsManager();
	~FunctionsManager();

	BaseFunction* getFunction(const std::string& s )
	{
		StringToFunctionMap::iterator it = getMap()->find(s) ;
		if ( it == getMap()->end() ) 
			return NULL ;
		return it->second ;
	}

	bool find ( std::string const& s )
	{
		StringToFunctionMap::iterator it = getMap()->find(s) ;
		if ( it == getMap()->end() )
			return false ;
		else
			return true ;
	}

	bool insert(const std::string& keyname, BaseFunction* function);
	void clear();

protected:
	StringToFunctionMap* getMap() { return &_map; }

private:
	StringToFunctionMap _map;
};

#endif // FUNCTIONSMANAGER_H

#include "HoopsStyleManager.h"
#include "HTools.h"
#include <map>
#include <string>

using namespace std;


class HoopsStyleManagerPrivate
{
public:
	HoopsStyleManagerPrivate(){
		_rootKey=HC_Open_Segment("?Style Library");
		HC_Close_Segment();

		registerDefault();
	}

	void registerDefault();

	void clear();
	bool removeStyle(const char* keyName);
	HC_KEY getStyle(const char* keyName);
	void startDefineStyle(const char* keyName);
	void endDefineStyle();

	HC_KEY _rootKey;
	typedef map<string,HC_KEY> KeyMap;
	KeyMap _keyMap;

};

HC_KEY HoopsStyleManagerPrivate::getStyle(const char* keyName)
{
	KeyMap::iterator f=_keyMap.find(keyName);
	if(f!=_keyMap.end()){
		return f->second;
	}
	return INVALID_KEY;
}

void HoopsStyleManagerPrivate::startDefineStyle(const char *keyName)
{
	HC_KEY key=getStyle(keyName);
	if(key==INVALID_KEY){
		HC_Open_Segment_By_Key(_rootKey);
		key=HC_Open_Segment("");
		HC_Close_Segment();
		HC_Close_Segment();
	}

	HC_Open_Segment_By_Key(key);
	_keyMap[keyName]=key;
}
void HoopsStyleManagerPrivate::endDefineStyle()
{
	HC_Close_Segment();
}

void HoopsStyleManagerPrivate::clear()
{
	for(KeyMap::iterator b=_keyMap.begin();
		b!=_keyMap.end();++b)
		HC_Delete_By_Key(b->second);
	_keyMap.clear();
}

bool HoopsStyleManagerPrivate::removeStyle(const char* keyName)
{
	KeyMap::iterator f=_keyMap.find(keyName);
	if(f!=_keyMap.end()){
		HC_Delete_By_Key(f->second);
		_keyMap.erase(f);
		return true;
	}
	return false;
}

void HoopsStyleManagerPrivate::registerDefault()
{
	startDefineStyle("stl");
	HC_Set_Visibility("faces=on");
	HC_Set_Visibility("lines=off");
	HC_Set_Visibility("edges=off");
	endDefineStyle();
}



HoopsStyleManager* HoopsStyleManager::_instance=NULL;

HoopsStyleManager* HoopsStyleManager::instance()
{
	if(!_instance)
		_instance=new HoopsStyleManager();
	return _instance;
}

void HoopsStyleManager::destruct()
{
	delete _instance;
	_instance=NULL;
}

HoopsStyleManager::HoopsStyleManager(void)
:_ptr(new HoopsStyleManagerPrivate())
{
}

HoopsStyleManager::~HoopsStyleManager(void)
{
}


HC_KEY HoopsStyleManager::getStyle(const char* keyName)
{
	return _ptr->getStyle(keyName);
}

bool HoopsStyleManager::removeStyle(const char* keyName)
{
	return _ptr->removeStyle(keyName);
}

void HoopsStyleManager::clear()
{
	_ptr->clear();
}

void HoopsStyleManager::startDefineStyle(const char* keyName)
{
	_ptr->startDefineStyle(keyName);
}

void HoopsStyleManager::endDefineStyle()
{
	_ptr->endDefineStyle();
}

bool HoopsStyleManager::includeStyleSegment(const char* keyName)
{
	HC_KEY key=getStyle(keyName);
	if(key==INVALID_KEY)
		return false;

	HC_Style_Segment_By_Key(key);
	return true;
}
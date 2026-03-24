#include "PixmapManager.h"
#include "Base/pre_compile.h"
#include "Base/Console.h"

using namespace Base;

PixmapManagerSingleton* PixmapManagerSingleton::_instance=NULL;

PixmapManagerSingleton* PixmapManagerSingleton::instance(){
	if(_instance==NULL)
		_instance=new PixmapManagerSingleton();
	return _instance;
}


PixmapManagerSingleton::PixmapManagerSingleton(void)
{
}

PixmapManagerSingleton::~PixmapManagerSingleton(void)
{
}


QPixmap* PixmapManagerSingleton::add(const QString& keyName)
{
	QPixmap* pix=new QPixmap(keyName);
	if(pix->isNull()){
		delete pix;
		return NULL;
	}
	_dataMap[keyName]=pix;
	return pix;
}
bool PixmapManagerSingleton::exist(const QString& keyName)
{
	KeyMap::iterator f=_dataMap.find(keyName);
	if(f==_dataMap.end()){
		// try load this.
		QPixmap* item=add(keyName);
		if(item)
			return true;
		return false;
	}
	return true;
}
QPixmap* PixmapManagerSingleton::get(const QString& keyName)
{
	KeyMap::iterator f=_dataMap.find(keyName);
	if(f==_dataMap.end()){
		return add(keyName);
	}
	return f->second;
}


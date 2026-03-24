#include "HoopsUpdator.h"
#include "precore/appearance.h"
#include "precore/BaseItem.h"

#include "precore/IResultItem.h"


HoopsUpdatorSingleton::HoopsUpdatorSingleton(void)
{
}


HoopsUpdatorSingleton::~HoopsUpdatorSingleton(void)
{
}

HoopsUpdatorSingleton* HoopsUpdatorSingleton::instance()
{
	static HoopsUpdatorSingleton* _instance=NULL;
	if(!_instance){
		_instance=new HoopsUpdatorSingleton();
	}
	return _instance;
}

void HoopsUpdatorSingleton::onItemUpdating( AppearanceItem* item )
{
	int typeID=item->getBaseItem()->getCategory();
	HoopsModelUpdatingFunc func=this->_modelUpdatingFuncMap[typeID];
	if(!func)
		return;
	func(item);
}

void HoopsUpdatorSingleton::registerItemUpdating( int typeID,HoopsModelUpdatingFunc func )
{
	_modelUpdatingFuncMap[typeID]=func;
}

HoopsResultUpdatingFunc HoopsUpdatorSingleton::getResultUpdatingFunc( int typeId )
{
	return _resultUpdatingFuncMap[typeId];
}

void HoopsUpdatorSingleton::registerResultUpdating( int typeId,HoopsResultUpdatingFunc func )
{
	_resultUpdatingFuncMap[typeId]=func;
}

void HoopsUpdatorSingleton::onResultItemUpdating(ResultUpdatePara* para, IResultItem* resultItem,AppearanceItem* appItem )
{
	BaseItem* item=resultItem->connectedItem();
	HoopsResultUpdatingFunc func=NULL;
	if(item)
		func=getResultUpdatingFunc(item->getCategory());
	else
		func=getResultUpdatingFunc(resultItem->getCategory());

	if(func)
		func(para,resultItem,appItem);
}

HoopsEigenUpdatingFunc HoopsUpdatorSingleton::getEigenUpdatingFunc( int typeId )
{
	return _eigenUpdatingFuncMap[typeId];
}

void HoopsUpdatorSingleton::registerEigenUpdating( int typeId,HoopsEigenUpdatingFunc func )
{
	_eigenUpdatingFuncMap[typeId]=func;
}

void HoopsUpdatorSingleton::onEigenItemUpdating( IResultItem* resultItem,AppearanceItem* appItem,float scale )
{
	BaseItem* item=resultItem->connectedItem();
	HoopsEigenUpdatingFunc func=NULL;
	if(item)
		func=getEigenUpdatingFunc(item->getCategory());
	else
		func=getEigenUpdatingFunc(resultItem->getCategory());

	if(func)
		func(resultItem,appItem,scale);
}


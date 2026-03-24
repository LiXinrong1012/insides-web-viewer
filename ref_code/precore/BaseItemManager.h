#pragma once

#include "precore/precore_global.h"
#include "precore/BaseItem.h"

namespace INSIDES
{

/*!
*	负责统一管理BaseItem条目的创建和删除。
*	@author Jerry He
*	@date 2014.2.21
*/
class PRECORE_EXPORT BaseItemManager
{
public:
	static BaseItemManager* instance();
	BaseItem* create(int typeID);
	void remove(BaseItem* item){delete item;}


private:
	BaseItemManager(void);
	~BaseItemManager(void);
};

inline BaseItemManager* myBaseItemManager(){
	return BaseItemManager::instance();
}


}
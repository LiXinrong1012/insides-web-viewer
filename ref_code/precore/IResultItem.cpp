#include "IResultItem.h"
#include "precore/BaseItem.h"
#include "precore/precore_data.h"


namespace INSIDES
{

IResultItem::IResultItem(IResults* parent)
	:_connectedItem(NULL)
	,_category(0)
	,_hasData(false)
	,_parentResults(parent)
	,_classType(TDY_POST_ITEMCLASS_BASE)
	,_hasBounding(false)
{
}


IResultItem::~IResultItem(void)
{
}

int IResultItem::getCategory()
{
	if(_connectedItem)
		return _connectedItem->getCategory();
	else
		return _category;
}

}
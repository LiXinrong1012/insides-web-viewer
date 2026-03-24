#include "BaseItemHelper.h"
#include "precore_data.h"
#include "BaseItem.h"
#include "Assembly.h"
#include "modeldocument.h"

#include "TypeDataManager.h"


namespace INSIDES
{

BaseItemHelper::BaseItemHelper(void)
{
}


BaseItemHelper::~BaseItemHelper(void)
{
}

Assembly* BaseItemHelper::getParentAssembly( BaseItem* item )
{
	if(!item)
		return NULL;
	else if(item->getCategory()==TDY_PRE_CATE_ASSEMBLY)
		return (Assembly*)item;
	return getParentAssembly(item->getParent());
}

ParametersBaseItem* BaseItemHelper::getRelatedParameters( BaseItem* item )
{
	if(!item)
		return NULL;
	BaseItem* p=item->getParent();
	if(!p)
		return NULL;
	QString parentName=p->getKeyName();
	BaseItem* aaa=NULL;
	if(p->count()>0)
		aaa=p->child(0);

	if(p->count()>0&& p->child(0)->getCategory()==TDY_PRE_CATE_PARAMETERS)
		return ((ParametersBaseItem*)p->child(0));

	return getRelatedParameters(p);
}

int BaseItemHelper::getInstanceCategory( BaseItem* instanceItem )
{
	QString relatedItemName=instanceItem->get(BaseItem::instanceKeyName);
	BaseItem* item=myDocument()->findItem(relatedItemName,getParentAssembly(instanceItem));
	if(!item)
		return TDY_PRE_CATE_UNKNOWN;
	return item->getCategory();
}

QIcon BaseItemHelper::getBaseItemIcon( BaseItem* item )
{
	TypeData* t=TypeDataManager::instance()->getTypeData(item->getCategory());
	if(!t)
		return QIcon();

	return QIcon(t->icon);
}


}
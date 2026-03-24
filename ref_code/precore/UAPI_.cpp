#include "UAPI_.h"
#include "precore/BaseItem.h"
#include "precore/ParametersBaseItem.h"
#include "precore/precore_data.h"

using namespace INSIDES;

void PREI_Delete_Item( BaseItem* item )
{
	delete item;
}

bool PREI_Add_Item( BaseItem* parent,BaseItem* item,int pos)
{
	if(!parent)
		return false;
	if(item->getID()==0)
		item->setID(BaseItem::nextCurrentMaxID());


	if(pos==-1)
		return parent->appendChild(item);
	else
		return parent->insertChild(pos,item);
}

bool PREI_Remove_Item( BaseItem* item, bool deleteIt)
{
	BaseItem* parent=item->getParent();
	if(!parent)
		return false;
	return parent->remove(item,deleteIt);
}

bool PREI_Modify_Item( BaseItem* src,BaseItem* dst )
{
	if(src==dst)
		return false;
	if(src->getClassType()!=dst->getClassType())
		return false;
	src->copyTo(dst);
	if(dst->getCategory()==TDY_PRE_CATE_PARAMETERS)
		((ParametersBaseItem*)dst)->refreshChildren();

	return true;
}



#include "BaseResultViewManager.h"

#include "precore/BaseItem.h"
#include "precore/appearance.h"
#include "precore/precore_data.h"
#include "precore/modeldocument.h"

#include "osg/Matrixf"

#include "HoopsUpdator.h"



BaseResultViewManager::BaseResultViewManager( PreHQWidget* w )
	:ViewManager(w)
{

}


BaseResultViewManager::~BaseResultViewManager(void)
{
	clear();
}

void BaseResultViewManager::clear()
{
	_modelMap.clear();
	_viewMap.clear();

	qDeleteAll(_appearanceList);
	_appearanceList.clear();
}

void BaseResultViewManager::clearView()
{
	clear();
	ViewManager::clearView();
}

AppearanceItem* BaseResultViewManager::getAppearance( BaseItem* item )
{
	return _modelMap[item];
}

AppearanceItem* BaseResultViewManager::getAppearance( HC_KEY key )
{
	return _viewMap[key];
}


void BaseResultViewManager::removeAssemblyMatrix(BaseItem* item)
{
	if(item->getCategory()==TDY_PRE_CATE_ASSEMBLY)
	{
		AppearanceItem* appItem=getAppearance(item);
		if(appItem && appItem->getHCKey()!=-1){
			HC_Open_Segment_By_Key(appItem->getHCKey());
			static osg::Matrixf matrix;
			HC_Set_Modelling_Matrix(matrix.ptr());

			HC_Close_Segment();
		}
	}
	int n=item->count();
	for(int i=0;i<n;++i)
		removeAssemblyMatrix(item->child(i));
}



void BaseResultViewManager::removePartMatrix()
{
	removeAssemblyMatrix(myDocument()->getAssembly());
}



void BaseResultViewManager::createModelItem( BaseItem* item )
{
	if( (item->isPartOrAssembly()&& (item!=myDocument()->getActiveItem()))
		|| item->isExternal() )
		return;
	HC_KEY key=HC_Open_Segment("");
	//AppearanceItem* appearance=new AppearanceItem(*item->getAppearance());
	AppearanceItem* appearance=item->getAppearance()->clone();
	appearance->setHCKey(key);
	appearance->setBaseItem(item);
	_modelMap[item]=appearance;
	_viewMap[key]=appearance;
	_appearanceList.push_back(appearance);
	// 对于柔性体，不进行初始的绘制。Jerry, 2014.7.22
	if(item->getCategory()!=TDY_PRE_CATE_FEMPART)
		HoopsUpdator()->onItemUpdating(appearance);
	onVisibilityChanged(appearance);
	onApplyMaterial(appearance);

	int n=item->count();
	for(int i=0;i<n;++i)
		createModelItem(item->child(i));

	HC_Close_Segment();
}

#include "femappearanceitem.h"


namespace INSIDES
{


FEMAppearanceItem::FEMAppearanceItem()
	:AppearanceItem()
{
	for(int i=0;i<MAX_GROUP_COUNT;++i){
		_femHCKeys[i][0]=-1;
		_femHCKeys[i][1]=-1;
		_femHCKeys[i][2]=-1;
	}
}

FEMAppearanceItem::~FEMAppearanceItem()
{

}

AppearanceItem* FEMAppearanceItem::clone() const
{
	FEMAppearanceItem* appItem=new FEMAppearanceItem();
	DeepCopy(*appItem,*this);
	memcpy(appItem->_femHCKeys,_femHCKeys,sizeof(JHC_KEY)*MAX_GROUP_COUNT*3);
	return appItem;
}


} // end namespace INSIDES
#ifndef FEMAPPEARANCEITEM_H
#define FEMAPPEARANCEITEM_H

#include "precore/appearance.h"

namespace INSIDES
{

class PRECORE_EXPORT FEMAppearanceItem : public AppearanceItem
{
public:
	enum {MAX_GROUP_COUNT=10};
	FEMAppearanceItem();
	~FEMAppearanceItem();

	AppearanceItem* clone()const;

	JHC_KEY getGroupHKey(int groupIndex,int index){return _femHCKeys[groupIndex][index];}
	void setGroupHKey(int groupIndex,int index,JHC_KEY k){_femHCKeys[groupIndex][index]=k;}


	JHC_KEY  _femHCKeys[MAX_GROUP_COUNT][3];
	
};

} // end namespace INSIDES

#endif // FEMAPPEARANCEITEM_H

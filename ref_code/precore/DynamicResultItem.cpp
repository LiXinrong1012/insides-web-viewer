#include "DynamicResultItem.h"
#include <limits>
#include "IResults.h"
#include "precore/precore_data.h"

namespace INSIDES
{
	DynamicResultItem::DynamicResultItem(IResults* parent)
		:RigidResultItem(parent)
		,_pieceCount(0)
	{
		_classType=TDY_POST_ITEMCLASS_DYNAMICRIGID;
	}


	DynamicResultItem::~DynamicResultItem(void)
	{
	}



}
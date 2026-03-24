#pragma once

#include "precore/precore_global.h"

#include <QIcon>

namespace INSIDES
{

class BaseItem;
class Assembly;
class ParametersBaseItem;

class PRECORE_EXPORT BaseItemHelper
{
public:
	BaseItemHelper(void);
	~BaseItemHelper(void);

	/// Get the nearest Assembly item for this item.
	static Assembly* getParentAssembly(BaseItem* item);

	static ParametersBaseItem* getRelatedParameters( BaseItem* item );
	static int getInstanceCategory(BaseItem* instanceItem);

	static QIcon getBaseItemIcon(BaseItem* item);
};


}
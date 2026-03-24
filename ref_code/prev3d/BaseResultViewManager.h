#pragma once

#include "prev3d/viewmanager.h"

#include <QHash>
#include <QList>

namespace INSIDES{
	class BaseItem;
	class AppearanceItem;
}

using namespace INSIDES;

class PREV3D_EXPORT BaseResultViewManager :
	public ViewManager
{
public:
	BaseResultViewManager(PreHQWidget* w);
	virtual ~BaseResultViewManager(void);

	virtual AppearanceItem* getAppearance(BaseItem* item);
	virtual AppearanceItem* getAppearance(HC_KEY key);
	virtual void clearView();

protected:

	/// 删掉原来的位置信息
	void removePartMatrix();

	/// 使用模型信息创建HOOPS显示
	void createModelItem(BaseItem* item);

protected:
	typedef QHash<BaseItem*,AppearanceItem*> ModelMap;
	typedef QHash<HC_KEY,AppearanceItem*>	ViewMap;
	typedef QList<AppearanceItem*>			AppearanceList;

	ModelMap	_modelMap;
	ViewMap		_viewMap;
	AppearanceList	_appearanceList;

private:
	void removeAssemblyMatrix(BaseItem* item);
	void clear();
};


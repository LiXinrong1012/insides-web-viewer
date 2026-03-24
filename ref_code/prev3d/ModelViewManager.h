#pragma once

#include "prev3d/prev3d_global.h"
#include <QList>
#include <QHash>
#include "prev3d/ViewManager.h"

#include "precore/modeldocumentlistener.h"

namespace INSIDES{
	class AppearanceItem;
	class BaseItem;
}

using namespace INSIDES;

class PreHQWidget;

class PREV3D_EXPORT ModelViewManager : public ViewManager
{
	Q_OBJECT;

public:
	ModelViewManager(PreHQWidget* w);
	~ModelViewManager(void);

	virtual AppearanceItem* getAppearance(BaseItem* item);
	virtual AppearanceItem* getAppearance(HC_KEY key);
	virtual void reset();
	virtual void redraw();
	virtual void clearView();

	HC_KEY getHCKey(BaseItem* item);
	BaseItem* getBaseItem(HC_KEY key);


private:
	typedef QHash<HC_KEY,BaseItem*> HCMap;

	void createAll(BaseItem* item);
	void redrawAll(BaseItem* item);

	void testStyle();
	HCMap	_hcMap;

	void clearHCKey(BaseItem* item);
};


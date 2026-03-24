#pragma once
#include <qobject>

#include "prev3d/prev3d_global.h"

class PreHQWidget;

namespace INSIDES{
	class BaseItem;
	class AppearanceItem;
}

using namespace INSIDES;

/*!
*	This class is used as the base class of manager HOOPS view.
*	@author	Jerry He
*	@date	2014.3.25
*/
class PREV3D_EXPORT ViewManager :
	public QObject
{
public:
	enum {ModelViewType,ResultViewType,BaseViewType};

	ViewManager(PreHQWidget* w);
	~ViewManager(void);

	virtual AppearanceItem* getAppearance(BaseItem* item){return NULL;}
	virtual AppearanceItem* getAppearance(HC_KEY key){return NULL;}
	virtual void reset(){}	//重置并刷新显示。
	virtual void redraw(){}	//重新刷新显示
	virtual void clearView();

	int getViewType()const{return _viewType;}

	bool openRootSegment();
	void closeSegment();
	HC_KEY getRootKey(){return _rootKey;}


	void onVisibilityChanged(BaseItem* item);
	void onVisibilityChanged(AppearanceItem* item);

	void onApplyMaterial(BaseItem* item);
	void onApplyMaterial(AppearanceItem* item);

	HC_KEY getHCKey(BaseItem* item);
	BaseItem* getBaseItem(HC_KEY key);


protected:
	void updateVisibility(const AppearanceItem* item);

	///更新材质显示
	void updateMaterial(BaseItem* item);
	void setViewType(int viewType){_viewType=viewType;}
	void insertTitleText(const QString& text,float size=0.07);

	PreHQWidget* _preHQWidget;

private:
	HC_KEY		_rootKey;
	int		_viewType;
};


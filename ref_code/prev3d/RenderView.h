#pragma once

#include "prev3d/prev3d_global.h"
#include "base/view.h"
#include "base/TreeItemPropertyManager.h"
#include <QSharedPointer>
#include <QList>
#include "prev3d/Pre3dRibbonPage.h"

class PreHQWidget;

using namespace INSIDES;

class Render3DTreeItemProperties: public ITreeItemPropertyFunc
{
public:
	Render3DTreeItemProperties(PreHQWidget* w=NULL):_HQWidget(w){}

	PreHQWidget* _HQWidget;
	virtual QString getKeyname()const;
	virtual QVariant getData(BaseItem* baseItem,int index);
	virtual bool setData(BaseItem* baseItem,int index,const QVariant& data);
};

class PREV3D_EXPORT RenderView :
	public Base::View
{
public:
	RenderView(void);
	~RenderView(void);

	static QString getClassTypeName();
	static Pre3dRibbonPage* getPre3DRibbonPage(){return &_ribbonPage;}

	/// Get related ribbon page for this type of view.
	virtual Qtitan::RibbonPage* getRibbonPage(){return _ribbonPage.ribbonPage;}
	/// Update the ribbon page control after this view activated.
	virtual void updateRibbonPage();

	virtual QString getViewType()const;
	virtual QWidget* getWidget();
	virtual QWidget* getActualWidget();

	virtual QList<QAction*>	getActionList();

	virtual ITreeItemPropertyFunc* getTreeItemProperties();

	virtual bool saveState(QDataStream& out);
	virtual bool loadState(QDataStream& in,qint64 dataSize);


private:
	QWidget* _widget;
	QWidget* _actualWidget;
	QList<QAction* > _actionList;

	Render3DTreeItemProperties _treeProperties;
	static Pre3dRibbonPage		_ribbonPage;

	void initActionList();
};


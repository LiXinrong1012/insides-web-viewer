#pragma once

#include "preui/preui_global.h"
#include <QWidget>
#include <QScopedPointer>

#include "precore/ISelectionSupplier.h"

class PropertyBrowserWidgetPrivate;

namespace INSIDES{
	class BaseItem;
}

using INSIDES::BaseItem;

typedef INSIDES::BaseItem PropertyItemClass;

class PREUI_EXPORT PropertyBrowserWidget:public QWidget,public INSIDES::ISelectionSupplier
{
	Q_OBJECT;

public:
	PropertyBrowserWidget(QWidget* parent=0);
	~PropertyBrowserWidget(void);


	PropertyItemClass* getItem();

public slots:
	void setItem(BaseItem* item);
	void updateTree();
	void applyClicked();
	void cancelClicked();
	void updateTree(BaseItem* p);
	void update(const std::vector<BaseItem*>& items);

signals:
	void itemChanged(BaseItem* p);

protected:
	void setupUi();

protected:
	virtual void ss_onSetSelection_protected(const INSIDES::BaseItemSelection& );
	virtual void ss_onSetClicked_projected(BaseItem* item);

private:
	QScopedPointer<class PropertyBrowserWidgetPrivate> d_ptr;
};

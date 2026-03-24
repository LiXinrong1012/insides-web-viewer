#include "imodelsearchtoolbar.h"

#include "precore/BaseItem.h"

IModelSearchToolbar::IModelSearchToolbar(QWidget *parent)
	: QWidget(parent)
{

}

IModelSearchToolbar::~IModelSearchToolbar()
{

}

void IModelSearchToolbar::emitReqUpdate( const QList<BaseItem*>& resutls )
{
	emit reqUpdate(resutls);
}

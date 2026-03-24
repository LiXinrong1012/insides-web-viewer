#ifndef IMODELSEARCHTOOLBAR_H
#define IMODELSEARCHTOOLBAR_H

#include <QWidget>

namespace INSIDES
{
	class BaseItem;
}

using INSIDES::BaseItem;

class IModelSearchToolbar : public QWidget
{
	Q_OBJECT

public:
	IModelSearchToolbar(QWidget *parent);
	~IModelSearchToolbar();

	void emitReqUpdate(const QList<BaseItem*>& resutls);
signals:
	void reqUpdate(const QList<BaseItem*>& resutls);

	
};

#endif // IMODELSEARCHTOOLBAR_H

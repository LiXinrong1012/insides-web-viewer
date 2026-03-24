#ifndef MTSEARCHENGINEIMP_H
#define MTSEARCHENGINEIMP_H

#include <QObject>
#include <QWidget>
#include <QtPlugin>
#include "mtsearchengine.h"

class IModelSearchToolbar;
namespace INSIDES
{
	class BaseItem;
}
using INSIDES::BaseItem;

class MTSearchEngineImp :public QObject, public MTSearchEngine
{
	Q_OBJECT
		Q_INTERFACES(MTSearchEngine)
public:
	MTSearchEngineImp();
	~MTSearchEngineImp();

	virtual IModelSearchToolbar* newSearchToolbar(QWidget* parent);
};

#endif // MTSEARCHENGINEIMP_H

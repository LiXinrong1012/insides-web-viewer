#include "mtsearchengineimp.h"
#include "modelsearchtoolbar.h"

#include "edcore/document.h"
#include "precore/BaseItem.h"
#include "precore/precore_data.h"


Q_EXPORT_PLUGIN2(mtsearchengine, MTSearchEngineImp);


MTSearchEngineImp::MTSearchEngineImp()
{

}

MTSearchEngineImp::~MTSearchEngineImp()
{
}

IModelSearchToolbar* MTSearchEngineImp::newSearchToolbar( QWidget* parent )
{
	return new ModelSearchToolbar(parent);
}

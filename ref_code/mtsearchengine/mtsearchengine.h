#ifndef MTSEARCHENGINE_H
#define MTSEARCHENGINE_H

#include "mtsearchengine_global.h"

class IModelSearchToolbar;

class MTSearchEngine
{
public:
	virtual ~MTSearchEngine(){}

	virtual IModelSearchToolbar* newSearchToolbar(QWidget* parent)=0;
};


Q_DECLARE_INTERFACE(MTSearchEngine,
	"com.jerryhe.tdypre.MTSearchEngine/2.0");

#endif // MTSEARCHENGINE_H

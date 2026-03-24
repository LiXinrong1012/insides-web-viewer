#include "EigenViewManager.h"

#include "precore/modeldocument.h"
#include "precore/precore_data.h"
#include "precore/IResultItem.h"
#include "precore/ResultDocument.h"
#include "precore/FlexResultItem.h"

#include "base/ParametersManager.h"
#include "base/Console.h"

#include "coresps/ShapeManager.h"
#include "coresps/HoopsUltility.h"

#include <osg/Matrixf>

#include "HoopsUpdator.h"
#include "PreHQWidget.h"
#include "Hoops3DConfiguration.h"


EigenViewManager::EigenViewManager( PreHQWidget* w )
	:BaseResultViewManager(w)
{
	myResultDocument()->attachListener(this);
}


EigenViewManager::~EigenViewManager(void)
{
	myResultDocument()->disattachListener(this);
}

void EigenViewManager::reset()
{
	clearView();

	this->openRootSegment();
	createModelItem(myDocument()->getActiveItem());
	this->closeSegment();

	removePartMatrix();
	drawEigen();
}

void EigenViewManager::onResultCurrentFrameChanged()
{
	drawEigen();

	//updateView();
	if(_preHQWidget && _preHQWidget->GetHoopsView())
		_preHQWidget->GetHoopsView()->Update();
}

void EigenViewManager::redraw()
{
	drawEigen();
}

void EigenViewManager::drawEigen()
{
	ResultDocument* resultDoc=myResultDocument();
	HoopsUpdatorSingleton* updator=HoopsUpdator();
	IResults* results=resultDoc->getResults();
	double displayScale=Hoops3DConfiguration::instance()->getEigenDisplayScale();
	QList<QSharedPointer<IResultItem> > datas=results->getResults().values();
	IResultItem* ritem;
	for(QList<QSharedPointer<IResultItem> >::Iterator b=datas.begin();b!=datas.end();++b){
		ritem=b->data();
		if(ritem->connectedItem() && ritem->hasData()){
			AppearanceItem* appItem=getAppearance(ritem->connectedItem());
			if(appItem && appItem->getHCKey()!=-1){
				HC_Open_Segment_By_Key(appItem->getHCKey());
				updator->onEigenItemUpdating(ritem,appItem,displayScale);
				HC_Close_Segment();
			}
		}
	}


	openRootSegment();
	HC_KEY key=HC_Open_Segment("TIME");
	HC_Flush_Contents(".","everything");
	QString str=results->getEigenFreq(results->getCurrentFrame());
	if(!str.isEmpty())
	{
		QString freqText=QString("Freq=%1, Scale=%2").arg(str).arg(Hoops3DConfiguration::instance()->getEigenDisplayScale());
		insertTitleText(freqText,0.05);
	}
	HC_Close_Segment();
	closeSegment();
}


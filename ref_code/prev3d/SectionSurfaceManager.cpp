#include "SectionSurfaceManager.h"
#include <QPluginLoader>
#include <QDir>
#include <QApplication>

#include "include/IExchangeSectionSurface.h"

#include "precore/FlexResultItem.h"


SectionSurfaceManager::SectionSurfaceManager(void)
{
	this->setPriority(30);
	myResultDocument()->attachListener(this);
}


SectionSurfaceManager::~SectionSurfaceManager(void)
{
	myResultDocument()->disattachListener(this);
}

void SectionSurfaceManager::onResultCurrentFrameChanged()
{
	updateData();
}

void SectionSurfaceManager::addSectionSurface( FlexResultItem* flexResultItem,
	QList<double>& points,QList<double>& parameters)
{
	QDir pluginsDir(qApp->applicationDirPath());

	pluginsDir.cd("plugins");
	QPluginLoader pluginLoader(pluginsDir.absoluteFilePath("exsecsurf.dll"));
	QObject *plugin = pluginLoader.instance();
	if (plugin && qobject_cast<IExchangeSectionSurface*>(plugin)) {
		IExchangeSectionSurface* ex=qobject_cast<IExchangeSectionSurface*>(plugin);
		QList<QList<double> > secPoints;
		ISectionSurface* sectionSurface=ex->createSectionSurface(flexResultItem);
		if(sectionSurface){
			sectionSurface->setD1Points(points);
			sectionSurface->setD1Paras(parameters);
			SecSurfPtr tmp=SecSurfPtr(sectionSurface);
			sectionSurface->init();
			_itemMap[flexResultItem->connectedItem()]=tmp;
		}

	}
}

void SectionSurfaceManager::updateData()
{
	for(ItemMap::Iterator b=_itemMap.begin();b!=_itemMap.end();++b)
	{
		b.value()->update();
	}
}

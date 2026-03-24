#include "findresultsmanager.h"
#include "edcore/console.h"

FindResultsManager::FindResultsManager()
	:_findResultDock1(NULL),
	_findResultDock2(NULL),
	_findResultWidget1(NULL),
	_findResultWidget2(NULL)
{
}

FindResultsManager::~FindResultsManager()
{
}

FindResultsManager* FindResultsManager::instance()
{
	static FindResultsManager tmp;
	return &tmp;
}

QDockWidget* FindResultsManager::getResultDock( int index )
{
	if(index==0)
		return _findResultDock1;
	else if(index==1)
		return _findResultDock2;

	Base::Console().Error("Error in getResultDock");
	return NULL;
}

void FindResultsManager::setResultDock( int index,QDockWidget* w )
{
	if(index==0)
		_findResultDock1=w;
	else if(index==1)
		_findResultDock2=w;
	else
		Base::Console().Error("Error in setResultDock");
}

FindResultWidget* FindResultsManager::getResultWidget( int index )
{
	if(index==0)
		return _findResultWidget1;
	else if(index==1)
		return _findResultWidget2;

	Base::Console().Error("Error in getResultDock");
	return NULL;
}

void FindResultsManager::setResultWidget( int index,FindResultWidget* w )
{
	if(index==0)
		_findResultWidget1=w;
	else if(index==1)
		_findResultWidget2=w;
	else
		Base::Console().Error("Error in setResultDock");
}

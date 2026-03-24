#include "helpenginesingleton.h"


QHelpEngine* HelpEngineSingleton::_engine=0;

HelpEngineSingleton::HelpEngineSingleton()
{

}

HelpEngineSingleton::~HelpEngineSingleton()
{

}

QHelpEngine* HelpEngineSingleton::instance()
{
	return _engine;
}

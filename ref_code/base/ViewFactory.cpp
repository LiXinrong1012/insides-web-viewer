#include "ViewFactory.h"

namespace Base
{

ViewFactory::ViewFactory(void)
{
}


ViewFactory::~ViewFactory(void)
{
}

ViewFactory* ViewFactory::instance( void )
{
	static ViewFactory* _instance=NULL;
	if(!_instance)
		_instance=new ViewFactory();
	return _instance;
}

}
#include "InputWidgetFactory.h"

using namespace std;

namespace Base{


InputWidgetFactory::InputWidgetFactory(void)
{
}


InputWidgetFactory::~InputWidgetFactory(void)
{
}

InputWidgetFactory* InputWidgetFactory::instance( void )
{
	if(_factorySingleton==NULL)
		_factorySingleton=new InputWidgetFactory;
	return _factorySingleton;
}

void InputWidgetFactory::destruct( void )
{
	delete _factorySingleton;
	_factorySingleton=NULL;
}

InputWidgetFactory* InputWidgetFactory::_factorySingleton=NULL;

}
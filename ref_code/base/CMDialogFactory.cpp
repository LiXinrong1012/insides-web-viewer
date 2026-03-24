#include "CMDialogFactory.h"


namespace Base{

CreatingModifyingDialogFactory::CreatingModifyingDialogFactory(void)
{
}


CreatingModifyingDialogFactory::~CreatingModifyingDialogFactory(void)
{
}

CreatingModifyingDialogFactory* CreatingModifyingDialogFactory::instance( void )
{
	if(_factorySingleton==NULL)
		_factorySingleton=new CreatingModifyingDialogFactory;
	return _factorySingleton;
}

void CreatingModifyingDialogFactory::destruct( void )
{
	delete _factorySingleton;
	_factorySingleton=NULL;
}

CreatingModifyingDialogFactory* Base::CreatingModifyingDialogFactory::_factorySingleton=NULL;

}
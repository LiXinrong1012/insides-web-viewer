#include "Factory.h"
namespace Base
{


	// ----------------------------------------------------
	FactorySingleton* FactorySingleton::_factorySingleton=NULL;

	FactorySingleton& FactorySingleton::Instance(){
		if(_factorySingleton==NULL)
			_factorySingleton=new FactorySingleton;
		return *_factorySingleton;
	}

	void FactorySingleton::Destruct(){
		delete _factorySingleton;
		_factorySingleton=NULL;
	}

}//namespace Base.
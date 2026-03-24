#pragma once
#include "base/factory.h"

#include <QString>

namespace Base
{

/*!
*	Factory to support produce various views.
*	@author Jerry He
*	@date	2014.3.25
*/
class BASE_EXPORT ViewFactory :
	public Base::Factory<QString>
{
public:
	static ViewFactory* instance(void);
	static void destruct(void);

private:
	ViewFactory();
	~ViewFactory();

};

}
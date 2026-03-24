#pragma once

#include "base/base_global.h"

/*!
*	This header is used to support FlexNET license support.
*	@author Jerry He
*	@date	2014.6.18
*/

namespace Base{

	namespace L
	{
		BASE_EXPORT bool init();
		BASE_EXPORT void setlicensefile(const char* licensefile);
		BASE_EXPORT bool co(const char* feature,const char* ver);
		BASE_EXPORT bool ci(const char*feature);
		BASE_EXPORT void tc();
	}

}


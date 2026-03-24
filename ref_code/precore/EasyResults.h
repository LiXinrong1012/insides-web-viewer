#pragma once

#include "precore/Results.h"

namespace INSIDES
{

/*!
*	This class is used as an old-format results database.
*	All results would be loaded into memory.
*	@author Jerry He
*	@date	2014.3.25
*/
class PRECORE_EXPORT EasyResults :
	public Results
{
public:
	EasyResults(void);
	virtual ~EasyResults(void);

	virtual bool init();
	virtual bool setPos(int pos);

protected:


};

}
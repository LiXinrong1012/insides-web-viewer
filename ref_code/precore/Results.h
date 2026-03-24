#pragma once

#include "precore/precore_global.h"
#include "precore/IResults.h"
#include <QHash>

namespace INSIDES
{

class BaseItem;
class IResultItem;


/*!
*	This class is the base class of all results.
*	@author Jerry He
*	@date	2014.3.25
*/
class PRECORE_EXPORT Results : public IResults
{
public:
	Results(void);
	virtual ~Results(void);

	virtual bool init();

	virtual double getTime(int index)const;

protected:
};

}

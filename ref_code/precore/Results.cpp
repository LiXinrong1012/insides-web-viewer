#include "Results.h"
#include <QtCore>

#include "IResultItem.h"

namespace INSIDES
{


Results::Results(void)
	:IResults()
{
}


Results::~Results(void)
{
}



bool Results::init()
{
	return false;
}


double Results::getTime( int index ) const
{
	return 0.0;
}

}
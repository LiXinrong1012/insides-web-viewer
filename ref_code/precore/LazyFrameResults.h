#pragma once
#include "precore/results.h"

namespace INSIDES
{


/*!
*	惰性的帧动画数据，只在当前帧读入。
*	@author Jerry He
*	@date	2014.3.26
*/
class LazyFrameResults :
	public Results
{
public:
	LazyFrameResults(void);
	virtual ~LazyFrameResults(void);


	virtual bool init();
	virtual bool reset();
	virtual bool next();
	virtual bool setPos(int pos);

};


}
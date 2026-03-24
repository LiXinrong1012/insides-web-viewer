#pragma once

#include "base/base_global.h"

namespace Base{

/*!
*	Virtual base class for animation control, it will work with 
*	animation bar.
*	@author Jerry He
*	@date	2014.4.1 (Fool's day!)
*/
class BASE_EXPORT AnimationControler
{
public:
	AnimationControler(void);
	virtual ~AnimationControler(void);

	virtual bool hasAnimation()=0;

	virtual int	getCurrentFrame()=0;
	virtual int getFrameCount()=0;

	virtual void setCurrentFrame(int frame)=0;

		//void setFrameSize(int size){ m_frameSize=size; }
};


}
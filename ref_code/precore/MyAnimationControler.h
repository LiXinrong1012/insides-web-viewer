#pragma once

#include "base/AnimationControler.h"

namespace INSIDES
{

class ResultDocument;

class MyAnimationControler : public Base::AnimationControler
{
public:
	MyAnimationControler(ResultDocument* doc);
	~MyAnimationControler(void);

	virtual bool hasAnimation();

	virtual int	getCurrentFrame();
	virtual int getFrameCount();

	virtual void setCurrentFrame(int frame);

private:
	ResultDocument* _doc;
	int			_tmp;
};

}
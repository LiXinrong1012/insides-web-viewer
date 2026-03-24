#include "MyAnimationControler.h"

#include "ResultDocument.h"
#include "Base/Console.h"

using namespace Base;


namespace INSIDES
{

MyAnimationControler::MyAnimationControler(ResultDocument* doc)
	:_doc(doc)
	,_tmp(0)
{
}


MyAnimationControler::~MyAnimationControler(void)
{
}

bool MyAnimationControler::hasAnimation()
{
	IResults* r=_doc->getResults();
	if(!r)
		return false;

	return r->getFrameCount()!=0;
}

int MyAnimationControler::getCurrentFrame()
{
	IResults* r=_doc->getResults();
	if(!r)
		return 0;

	return r->getCurrentFrame();
}

void MyAnimationControler::setCurrentFrame( int frame )
{
	IResults* r=_doc->getResults();
	if(!r)
		return;

	r->setPos(frame);
	_doc->notifyListeners();
}

int MyAnimationControler::getFrameCount()
{
	IResults* r=_doc->getResults();
	if(!r)
		return 0;

	return r->getFrameCount();
}

}
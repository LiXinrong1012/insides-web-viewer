#include "optestthread.h"

#include "base/Console.h"
#include "base/MultiProgressOperator.h"



OPTestThread::OPTestThread(QObject *parent)
	: QThread(parent)
{

}

OPTestThread::~OPTestThread()
{

}

void OPTestThread::run()
{
	Base::MultiProgressOperator::startProgress("Load...");
	for(int i=0;i<100;++i){
		Base::Console().Log("%d",i);
		Base::MultiProgressOperator::setProgress(i);
		this->msleep(50);
	}
	Base::MultiProgressOperator::stopProgress();
	exec();

}

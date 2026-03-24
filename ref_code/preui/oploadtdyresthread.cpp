#include "oploadtdyresthread.h"

#include "precore/ResultDocument.h"

#include "base/MultiProgressOperator.h"

using namespace INSIDES;

OPLoadTDYResThread::OPLoadTDYResThread(QObject *parent)
	: QThread(parent)
{

}

OPLoadTDYResThread::~OPLoadTDYResThread()
{

}

void OPLoadTDYResThread::run()
{
	Base::MultiProgressOperator::startProgress("Loading TDY result...");
	ResultDocument* doc=myResultDocument();
	doc->loadTDYResults();

	Base::MultiProgressOperator::stopProgress();
	emit jobFinished();
	exec();
}

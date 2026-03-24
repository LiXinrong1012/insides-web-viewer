#include "opsavemodelthread.h"
#include "precore/document.h"

#include "base/MultiProgressOperator.h"



using namespace Base;
using namespace INSIDES;

OPSaveModelThread::OPSaveModelThread(QObject *parent)
	: QThread(parent)
	,_saveResult(true)
{

}

OPSaveModelThread::~OPSaveModelThread()
{

}

void OPSaveModelThread::run()
{
	MultiProgressOperator::startProgress("Save model...");
	MultiDocuments::instance()->getActiveDocument()->save(_filename,_saveResult);
	MultiProgressOperator::stopProgress();
}

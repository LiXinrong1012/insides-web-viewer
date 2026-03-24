#include "solvermanagerfilter.h"

#include <time.h>

SolverManagerFilter::SolverManagerFilter(QObject *parent)
	: QObject(parent)
	,_startTime(0)
	,_updateFreq(0)
	,_CPUTime(0)
	,_isRunning(false)
	,_lastUpdateInformationTime(0)
{
	connect(this,SIGNAL(emitStarted()),this,SLOT(onStarted()));
	connect(this,SIGNAL(emitPaused()),this,SLOT(onPaused()));
	connect(this,SIGNAL(emitRestarted()),this,SLOT(onRestarted()));
	connect(this,SIGNAL(emitFinished()),this,SLOT(onFinished()));
	connect(this,SIGNAL(emitLog(int,QString)),this,SLOT(onLog(int,QString)));
	connect(this,SIGNAL(emitInformation(SolverUpdateInfo2*)),this,SLOT(onInformation(SolverUpdateInfo2*)));
}

SolverManagerFilter::~SolverManagerFilter()
{

}

void SolverManagerFilter::started()
{
	_CPUTime=0;
	_startTime=clock();
	_isRunning=true;
	emit emitStarted();
}

void SolverManagerFilter::onStarted()
{
	if(getConnector())
		getConnector()->started();
}

void SolverManagerFilter::paused()
{
	_CPUTime+=(clock()-_startTime)/1000;
	_isRunning=false;
	emit emitPaused();
}

void SolverManagerFilter::onPaused()
{
	if(getConnector())
		getConnector()->paused();
}

void SolverManagerFilter::restarted()
{
	_startTime=clock();
	_isRunning=true;
	emit emitRestarted();
}
void SolverManagerFilter::onRestarted()
{
	if(getConnector())
		getConnector()->restarted();
}


void SolverManagerFilter::finished()
{
	_CPUTime=(clock()-_startTime)/1000;
	_startTime=0;
	_isRunning=false;
	staticInfo.process=1;
	staticInfo.cpuTime=_CPUTime;
	emit emitFinished();
}

void SolverManagerFilter::onFinished()
{
	if(getConnector())
		getConnector()->finished();
}

void SolverManagerFilter::log( int logType,const std::string& message )
{
	QString tmp=QString::fromStdString(message);
	emit emitLog(logType,tmp);
}

void SolverManagerFilter::onLog( int logType,QString message )
{
	if(getConnector())
		getConnector()->log2(logType,message);
}

void SolverManagerFilter::information( const SolverUpdateInfo* info )
{
	/// 根据频率决定是否触发信号
	if(_updateFreq>0){
		if(clock()-_lastUpdateInformationTime<_updateFreq)
			return;
		_lastUpdateInformationTime=clock();
	}
	SolverUpdateInfo& tmp=staticInfo;
	tmp=*info;

	staticInfo.cpuTime = (clock()-_startTime)/1000+_CPUTime;
	if(staticInfo.endTime-staticInfo.startTime==0)
		staticInfo.process=0;
	else
		staticInfo.process = (staticInfo.calTime-staticInfo.startTime)/(staticInfo.endTime-staticInfo.startTime);

	if(staticInfo.process==0)
		staticInfo.remainTime=0;
	else
		staticInfo.remainTime = staticInfo.cpuTime / staticInfo.process*(1-staticInfo.process);
	emitInformation(&staticInfo);
}

void SolverManagerFilter::onInformation(SolverUpdateInfo2* info )
{
	if(getConnector()){
		getConnector()->information2(*info);
	}
}

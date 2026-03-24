#include "myinssolver.h"
#include "inssolvermanager.h"

#include <Windows.h>

extern "C" void* createINSSolver()
{
	MyINSSolver* solver=new MyINSSolver();
	return solver;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
MyINSSolver::MyINSSolver()
	:_isPaused(false)
	,_needPause(false)
	,_needStop(false)
{
}

void MyINSSolver::start()
{
	/// 进行必要的初始化
	//char buffer[1024];
	//sprintf(buffer,"Input File = %s",_solverPara.fileName.c_str());
	//_solverPara.manager->log(INSSolverManager::LT_MESSAGE,buffer);
	_solverPara.manager->started();

	double maxCalcTime=10;

	SolverUpdateInfo info;
	info.startTime=0;
	info.endTime=maxCalcTime;
	info.error=1e-4;

	double currentTime=0;

	double timedelta=0.1;

	while(true){
		if(_needPause){
			_isPaused=true;
			_needPause=false;
			_solverPara.manager->paused();
		}
		if(_isPaused){
			Sleep(100); 
			continue;
		}

		if(_needStop){
			_solverPara.manager->finished();
			break;
		}
		Sleep(timedelta*1000);
		currentTime=currentTime+timedelta;
		info.calTime=currentTime;
		info.stepTime++;
		_solverPara.manager->information(&info);
		if(currentTime>=maxCalcTime){
			_solverPara.manager->finished();
			return;
		}
		_solverPara.manager->log(INSSolverManager::LT_ERROR,"this is message test.");
	}
}

void MyINSSolver::pause()
{
	_needPause=true;
}

void MyINSSolver::restart()
{
	_isPaused=false;
	_solverPara.manager->restarted();
}

void MyINSSolver::stop()
{
	_needStop=true;
}

void MyINSSolver::compile( const char* fileName )
{
}

void MyINSSolver::setPara(const INSSolverPara& para )
{
	_solverPara=para;
}




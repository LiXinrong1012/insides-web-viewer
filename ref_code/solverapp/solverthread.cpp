#include "solverthread.h"

#include "inssolver/inssolver.h"

SolverThread::SolverThread(QObject *parent,INSSolver* solver)
	: QThread(parent)
	,_solver(solver)
{
	 
}

SolverThread::~SolverThread()
{

}

void SolverThread::run()
{
	_solver->start();
}

#ifndef SOLVERTHREAD_H
#define SOLVERTHREAD_H

#include <QThread>

class INSSolver;

class SolverThread : public QThread
{
	Q_OBJECT

public:
	SolverThread(QObject *parent,INSSolver* solver);
	~SolverThread();

	void run();

private:
	INSSolver*	_solver;
	
};

#endif // SOLVERTHREAD_H

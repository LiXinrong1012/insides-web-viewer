#ifndef OPLOADMODELTHREAD_H
#define OPLOADMODELTHREAD_H

#include <QThread>

class OPLoadModelThread : public QThread
{
	Q_OBJECT

public:
	OPLoadModelThread(QObject *parent);
	~OPLoadModelThread();

private:
	
};

#endif // OPLOADMODELTHREAD_H

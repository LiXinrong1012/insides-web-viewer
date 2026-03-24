#ifndef OPLOADTDYRESTHREAD_H
#define OPLOADTDYRESTHREAD_H

#include <QThread>

class OPLoadTDYResThread : public QThread
{
	Q_OBJECT

public:
	OPLoadTDYResThread(QObject *parent);
	~OPLoadTDYResThread();

signals:
	void jobFinished();

protected:
	void run();

private:
	
};

#endif // OPLOADTDYRESTHREAD_H

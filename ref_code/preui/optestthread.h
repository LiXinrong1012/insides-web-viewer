#ifndef OPTESTTHREAD_H
#define OPTESTTHREAD_H

#include <QThread>

class OPTestThread : public QThread
{
	Q_OBJECT

public:
	OPTestThread(QObject *parent);
	~OPTestThread();

protected:
	void run();

private:
	
};

#endif // OPTESTTHREAD_H

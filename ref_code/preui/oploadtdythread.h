#ifndef OPLOADTDYTHREAD_H
#define OPLOADTDYTHREAD_H

#include <QThread>

class IExchangeFile2;

class OPLoadTDYThread : public QThread
{
	Q_OBJECT

public:
	OPLoadTDYThread(QObject *parent);
	~OPLoadTDYThread();

	void setFileName(const QString& fileName){_fileName=fileName;}

signals:
	void jobFinished();

protected:
	virtual void run();

private:
	QString			_fileName;

	
};

#endif // OPLOADTDYTHREAD_H

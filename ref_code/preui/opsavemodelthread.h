#ifndef OPSAVEMODELTHREAD_H
#define OPSAVEMODELTHREAD_H

#include <QThread>

class OPSaveModelThread : public QThread
{
	Q_OBJECT

public:
	OPSaveModelThread(QObject *parent);
	~OPSaveModelThread();

	void setFileName(const QString& fileName){_filename=fileName;}
	void setSaveResult(bool b){_saveResult=b;}

protected:
	void run();

private:
	QString _filename;
	bool	_saveResult;
	
};

#endif // OPSAVEMODELTHREAD_H

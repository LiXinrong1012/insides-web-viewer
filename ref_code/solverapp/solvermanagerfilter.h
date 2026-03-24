#ifndef SOLVERMANAGERFILTER_H
#define SOLVERMANAGERFILTER_H

#include <QObject>
#include "inssolvermanager2.h"

class SolverManagerFilter : public QObject, public INSSolverManager2
{
	Q_OBJECT

public:
	SolverManagerFilter(QObject *parent=0);
	~SolverManagerFilter();

	virtual void started();
	virtual void paused();
	virtual void restarted();
	virtual void finished();
	virtual void log(int logType,const std::string& message);
	virtual void information(const SolverUpdateInfo* info);


	virtual void log2(int logType,const QString& mes){}
	virtual void information2(SolverUpdateInfo2& info){}

signals:
	void emitStarted();
	void emitPaused();
	void emitRestarted();
	void emitFinished();
	void emitLog(int logType,QString message);
	void emitInformation(SolverUpdateInfo2* info);

	private slots:
		void onStarted();
		void onPaused();
		void onRestarted();
		void onFinished();
		void onLog(int logType,QString message);
		void onInformation(SolverUpdateInfo2* info);

private:
	int		_CPUTime;
	long	_startTime;
	long	_lastUpdateInformationTime;
	/// 更新频率，当<=0时表示所有information都触发更新，其它时表示多少毫秒更新一次
	int		_updateFreq;
	bool	_isRunning;
	SolverUpdateInfo2 staticInfo;
};

#endif // SOLVERMANAGERFILTER_H

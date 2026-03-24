#ifndef SOLVERDIALOG_H
#define SOLVERDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QTimer>
namespace Ui {class SolverDialog;};

#include "inssolver/inssolver.h"
#include "inssolvermanager2.h"

class SolverDialog : public QDialog, public INSSolverManager2
{
	Q_OBJECT

public:
	SolverDialog(const QString& fileName, QWidget *parent = 0);
	~SolverDialog();

	void setSolver(INSSolver* solver){_solver=solver;}

	/// 传给INSSolver的回调，设置文件名的时候可以用
	void setMainSolverManager(INSSolverManager* m){_mainManager=m;}

	static QString seconds2FriendlyString(int seconds);
	static QString seconds2String(int seconds);
public:
	/// INSSolverManager
	virtual void started();
	virtual void paused();
	virtual void restarted();
	virtual void finished();
	virtual void log2(int logType,const QString& message);
	virtual void information2(SolverUpdateInfo2& info);

	private slots:
		void onOpen();
		void onStart();
		void onPauseOrRestart();
		void onStop();

		void appendLog(int logType,QString log);

		///tabwidget当前页改变
		void onCurrentChanged ( int index );

private:
	Ui::SolverDialog*	ui;
	QString				_fileName;
	INSSolverManager*	_mainManager;

	bool	_isStarted;
	INSSolver*	_solver;
	QString			_logText;
	long			_cpuTime;
	///是否显示的为暂停
	bool			_isShowPaused;
private:
	void updateEditText(QTextEdit* editer,const QString& fileName);
	///更新上面几行显示的LABEL
	void updateLabel(int cpuTime,double process,int remainTime);
};

#endif // SOLVERDIALOG_H

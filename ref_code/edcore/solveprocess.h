#ifndef SOLVERPROCESSWRAPPER_H
#define SOLVERPROCESSWRAPPER_H

#include "edcore/edcore_global.h"
#include <QObject>
#include <QtNetwork/QLocalSocket>
#include <QProcess>
#include <QTimer>
#include <QQueue>
#include <QMutex>

#include "inssolver/socketmessage.h"


namespace INSEditor{

class Project;
/*!
	@brief 代表求解器求解的一个工程。
	@author	Jerry He
	@date	2015.1.8
*/
class EDCORE_EXPORT SolveProcess: public QObject
{
	Q_OBJECT

public:
	SolveProcess(Project *parent);
	~SolveProcess();

	/// local socket related functions

	/// 尝试连接给定的服务器strServerName
	void connectSolver(const QString &strServerName);

	///发送字符串消息到服务器
	void sendMessage(const QString& message);

	///发送SendToServerMessage对象到服务器
	void sendMessage(const SendToServerMessage& mes);

	/// 获得求解时间
	double getCalcTime()const{return _calcTime;}

	/// 获得最大求解时间
	double getMaxCalcTime()const{return _maxCalcTime;}

	/// 获得开始求解时间
	double getStartCalcTime()const {return _startCalcTime;}

	/// 获得积分误差
	double getIntError()const{return _intError;}

	/// 获得物理积分步长
	double getStepTime()const{return _stepTime;}

	/// 获得其它信息
	QString getOtherMessage()const{return _otherMessage;}

	/// 获得当前状态
	int getCurrentState()const {return _currentState;}

	/// 获得日志文本
	QString& getLogText(){return _logText;}

	/// 获得CPU计算时间
	long getCpuTime()const{return _cpuTime;}

	/// 获得预计剩余时间
	double getReaminTime()const{return _remainTime;}

	/// 获得当前进度 
	double getProcess()const{return _process;}

private slots:
	/// 连接成功信号关联槽
	void socketConnectedHandler();

	/// 连接断开信息关联槽
	void socketDisConnectedHandler();

	/// 连接错误信号关联槽
	void socketErrorHandler(QLocalSocket::LocalSocketError error);

	/// 有消息可读信号关联槽
	void socketReadyRead();

	/// 求解完成信号关联槽
	void onSolverFinished(int,QProcess::ExitStatus);

private:
	QLocalSocket _socket;
	QProcess*	 _solver;
	QString		 _serverName;

	// display related variables

	/// 求解时间
	double _calcTime;
	/// 最大求解时间
	double _maxCalcTime;
	/// 开始求解时间
	double _startCalcTime;
	/// 预计剩余时间
	double _remainTime;
	/// 积分误差
	double _intError;
	/// CPU求解时间,单位为秒
	long  _cpuTime;
	/// 进度
	double _process;
	/// 当前物理积分步长
	double _stepTime ;
	/// 其他信息
	QString _otherMessage;
	/// 当前状态
	int _currentState;
	/// 日志信息
	QString _logText;

private:
	/// 用于解析信息
	void processMessage(const SendToClientMessage& message);
	
	/// 更新日志
	void updateLog(int logType,const QString& log );
};

}


#endif // SOLVERPROCESSWRAPPER_H

#include "solveprocess.h"
#include "project.h"
#include "document.h"

#include "inssolver/inssolvermanager.h"

#include <QMessageBox>
#include <QTextStream>
#include <QDebug>


namespace INSEditor
{

SolveProcess::SolveProcess(Project *parent)
	: QObject(parent)
	,_socket(this)
	,_solver(NULL)

	/////////////
	,_calcTime(0)
	,_maxCalcTime(0)
	,_startCalcTime(0)
	,_intError(0)
	,_cpuTime(0)
	,_stepTime(0)
	,_otherMessage("")
	,_currentState(0)
	/////////////

{
	connect(&_socket, SIGNAL(connected()), this, SLOT(socketConnectedHandler()));
	connect(&_socket, SIGNAL(disconnected()), this, SLOT(socketDisConnectedHandler()));
	connect(&_socket, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(socketErrorHandler(QLocalSocket::LocalSocketError)));
	connect(&_socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));

	QString appName=INSEditor::Document::instance()->getProperties()->solverExecutablePath;
	QStringList arguments;
	QUuid uuid=QUuid::createUuid();
	_serverName=uuid.toString();
	if(!Document::instance()->getProperties()->isShowSolverUI)
		arguments<<"-nogui";
	arguments<<"-n"<<_serverName;
	QString modelName=parent->getStartupEntity()->getFullFileName();
	arguments<<modelName;

	_solver = new QProcess(this);
	_solver->start(appName,arguments);
	connect(_solver,SIGNAL(finished(int,QProcess::ExitStatus)),
		this,SLOT(onSolverFinished(int,QProcess::ExitStatus)));

	int sum = 0;
	while(!_socket.waitForConnected(5000))
	{
		sum += 30;
		Sleep(30);
		connectSolver(_serverName);
		if(sum > 5000)
		{
			QMessageBox msg;
			msg.setWindowTitle(tr("Can't Find The Solver"));
			msg.setText(tr("Please check the path of the solver configuration!"));
			msg.exec();
			return;
		}
	}
}

SolveProcess::~SolveProcess()
{
}

void SolveProcess::connectSolver( const QString &strServerName )
{
	// 服务端的serverNewConnectionHandler成员方法将被调用
	_socket.connectToServer(strServerName);
	if (!_socket.waitForConnected(10000))
	{
//		QMessageBox::warning(NULL,"Warning","Cannot connect solver.");
		return;
	}
}

void SolveProcess::socketConnectedHandler()
{
	//QMessageBox::about(NULL,"connected","connected");
	//qDebug() << "connected.";
}

void SolveProcess::socketDisConnectedHandler()
{
	qDebug() << "disconnected.";
}

void SolveProcess::socketErrorHandler(QLocalSocket::LocalSocketError error )
{
	qWarning() << error;
}

void SolveProcess::socketReadyRead()
{
	QLocalSocket* socket=&_socket;
	QDataStream in(socket);
	SendToClientMessage mes;
	while(!in.atEnd())
	{
		in>>mes;
		processMessage(mes);
	}
}

void SolveProcess::onSolverFinished( int,QProcess::ExitStatus )
{
}

void SolveProcess::sendMessage( const SendToServerMessage& mes )
{
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out<<mes;
	_socket.write(block);
	_socket.flush();
}

void SolveProcess::processMessage(const SendToClientMessage& message)
{
	SendToClientMessage msg = message;
	
	switch(msg.messageType)
	{
	/*case SendToClientMessage::UNDEFINED:
		currentState = SendToClientMessage::UNDEFINED;
		break;*/
	case SendToClientMessage::STARTED:
		_currentState = SendToClientMessage::STARTED;
		break;
	case SendToClientMessage::PAUSED:
		_currentState = SendToClientMessage::PAUSED;
		break;
	case SendToClientMessage::RESTARTED:
		_currentState = SendToClientMessage::RESTARTED;
		break;
	case SendToClientMessage::FINISHED:
		_currentState = SendToClientMessage::FINISHED;
		break;
	case SendToClientMessage::LOG:
		{
			_currentState = SendToClientMessage::LOG;
			updateLog(msg.logType,msg.log);
		}
		
		break;
	case  SendToClientMessage::INFORMATION:
		{
			qDebug()<<msg.informations.count()<<" "<<msg.messageType<<" "<<msg.logType<<" "<<msg.log;

			_startCalcTime = msg.informations["START_TIME"].toDouble();
			_maxCalcTime = msg.informations["END_TIME"].toDouble();
			_intError = msg.informations["ERROR"].toDouble();
			
			_calcTime = msg.informations["CAL_TIME"].toDouble();
			_remainTime = msg.informations["REMAIN_TIME"].toDouble();
			_cpuTime = msg.informations["CPU_TIME"].toLong();
			_process = msg.informations["PROCESS"].toDouble();
			_stepTime = msg.informations["STEP_TIME"].toDouble();
			_otherMessage = msg.informations["MESSAGE"];
		}
		break;
	}
	Document::instance()->requestSolveProcessUpdate(this);
}

void SolveProcess::updateLog( int logType,const QString& log )
{
	QString str;
	switch (logType)
	{
	case INSSolverManager::LT_ERROR:
		str = QString("<font color=red>%1</font><br>").arg(log);
		break;
	case INSSolverManager::LT_LOG:
		str = QString("<font color=black>%1</font><br>").arg(log);
		break;
	case INSSolverManager::LT_MESSAGE:
		str = QString("<font color=green>%1</font><br>").arg(log);
		break;
	case INSSolverManager::LT_WARNING:
		str = QString("<font color=blue>%1</font><br>").arg(log);
		break;
	}
	_logText += str;
}


}
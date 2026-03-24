#include <QtGui/QApplication>
#include <QLibrary>
#include <QtGui>
#include <ostream>
#include <string>
#include <iostream>

#include "solverdialog.h"
#include "localserver.h"
#include "solvermanagerfilter.h"

using namespace std;


INSSolver* createSolver()
{
	typedef void* (*F1) ();

	QLibrary lib("inssolver.dll");
	lib.load();

	bool bloaded=lib.isLoaded();
	if(bloaded){
		F1 f1=(F1)lib.resolve("createINSSolver");
		if(f1){
			return (INSSolver*)f1();
		}
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	QString fileName;     //求解文件路径
	bool startUI=true;    //是否建立用户界面
	QString serverName;   //是否建立服务连接

	// 1. 获取求解的文件名
	// 2. 获取是否启动用户界面
	// 3. 是否建立Socket服务
	int current=1;
	while(current<argc)
	{
		if(QString::compare(argv[current],"-n")==0)
		{
			if(current+1<argc)
				serverName=argv[++current];
			else{
				cout<<"valid server name."<<endl;
				return 0;
			}
		}
		else if(QString::compare(argv[current],"-nogui")==0)
		{
			startUI=false;
			current++;
		}
		else
			fileName=argv[current++];
	}

	/// 同时启动UI和Server
	if(!serverName.isEmpty() && startUI)
	{
		QApplication a(argc, argv);

		LocalServer localServer;
		if(!localServer.listen(serverName)){
			QString errorMessage=QString(QObject::tr("Listen to name(%1) failed.")).arg(serverName);
			QMessageBox::critical(0,QObject::tr("Error"),errorMessage);
			return 0;
		}

		SolverManagerFilter solverManagerFilter;

		QString message=QString("Started server(%1) succeeded.").arg(serverName);
		cout<<qPrintable(message)<<endl;

		INSSolver* solver=createSolver();
		if(!solver){
			QMessageBox::critical(0,"Error","Create Solver instance failed.");
			return 0;
		}
		SolverDialog dlg(fileName);
		dlg.setMainSolverManager(&solverManagerFilter);

		INSSolverPara para;
		para.manager=&solverManagerFilter;
		para.fileName=fileName.toStdString();
		solver->setPara(para);

		dlg.setSolver(solver);
		localServer.setSolver(solver);
		dlg.setConnector(&localServer);
		solverManagerFilter.setConnector(&dlg);

		dlg.show();
		return a.exec();
	}
	if(!serverName.isEmpty())
	{
		QCoreApplication a(argc, argv);

		LocalServer localServer;
		if(!localServer.listen(serverName)){
			QString errorMessage=QString(QObject::tr("Listen to name(%1) failed.")).arg(serverName);
			QMessageBox::critical(0,QObject::tr("Error"),errorMessage);
			return 0;
		}

		SolverManagerFilter solverManagerFilter;
		
		QString message=QString("Started server(%1) succeeded.").arg(serverName);
		cout<<qPrintable(message)<<endl;

		INSSolver* solver=createSolver();
		if(!solver){
			QMessageBox::critical(0,"Error","Create Solver instance failed.");
			return 0;
		}
		
		INSSolverPara para;
		para.manager=&solverManagerFilter;
		para.fileName=fileName.toStdString();
		solver->setPara(para);

		localServer.setSolver(solver);
		solverManagerFilter.setConnector(&localServer);
		return a.exec();
	}
	else if(startUI){
		QApplication a(argc, argv);

		INSSolver* solver=createSolver();
		if(!solver){
			QMessageBox::critical(0,"Error","Create Solver instance failed.");
			return a.exec();
		}
				
		SolverManagerFilter solverManagerFilter;
		SolverDialog dlg(fileName);
		dlg.setMainSolverManager(&solverManagerFilter);

		INSSolverPara para;
		para.manager=&solverManagerFilter;
		para.fileName=fileName.toStdString();
		solver->setPara(para);

		dlg.setSolver(solver);
		solverManagerFilter.setConnector(&dlg);

		dlg.show();
		return a.exec();
	}
	else
		return 0;
}

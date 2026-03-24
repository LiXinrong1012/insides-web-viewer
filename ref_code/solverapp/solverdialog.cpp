#include "solverdialog.h"
#include "ui_solverdialog.h"

#include "solverthread.h"

#include <QLibrary>
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include <QTime>
#include <QVector>



SolverDialog::SolverDialog(const QString& fileName,QWidget *parent)
	: QDialog(parent)
	,_fileName(fileName)
	,_mainManager(NULL)
	,_isStarted(false)
	,_solver(NULL)
	,_cpuTime(0)
	,_isShowPaused(true)
{
	ui = new Ui::SolverDialog();
	ui->setupUi(this);

	ui->btnPause->setEnabled(false);
	ui->btnStop->setEnabled(false);

	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  
	ui->tableWidget->verticalHeader()->hide();
	ui->logsTextEdit->setReadOnly(true);
	QPixmap pix;
	pix.load(":/resources/b007.png");
	ui->statusLabel->setPixmap(pix);

	connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(onCurrentChanged(int)));
}

SolverDialog::~SolverDialog()
{
	delete ui;
}

void SolverDialog::onStart()
{
	if(!_solver || _isStarted)
		return;

	ui->fileValue->setText(_fileName);

	QThread* thread=new SolverThread(this,_solver);
	thread->start();
	_isStarted = true;
}

void SolverDialog::onPauseOrRestart()
{
	if(!_solver)
		return;
	
	if(_isShowPaused)
		//点了暂停按钮
		_solver->pause();
	else
		//点了继续按钮
		_solver->restart();
}

void SolverDialog::onStop()
{
	if(!_solver)
		return;
	_solver->stop();
}

void SolverDialog::information2(SolverUpdateInfo2& ainfo )
{
	SolverUpdateInfo2* info=&ainfo;
	if(!ui->tableWidget->item(0,0))
	{
		ui->tableWidget->setItem(0,0,new QTableWidgetItem(info->calTime));
		ui->tableWidget->setItem(0,1,new QTableWidgetItem(info->stepTime));
		ui->tableWidget->setItem(0,2,new QTableWidgetItem(info->startTime));
		ui->tableWidget->setItem(0,3,new QTableWidgetItem(info->endTime));
		ui->tableWidget->setItem(0,4,new QTableWidgetItem(info->error));
	}
	else
	{
		ui->tableWidget->item(0,0)->setData(Qt::DisplayRole,info->calTime);
		ui->tableWidget->item(0,1)->setData(Qt::DisplayRole,info->stepTime);
		ui->tableWidget->item(0,2)->setData(Qt::DisplayRole,info->startTime);
		ui->tableWidget->item(0,3)->setData(Qt::DisplayRole,info->endTime);
		ui->tableWidget->item(0,4)->setData(Qt::DisplayRole,info->error);
	}

	
	updateLabel(info->cpuTime,info->process,info->remainTime);

	if(getConnector())
		getConnector()->information2(ainfo);
}

void SolverDialog::log2(int logType, const QString& message )
{
	if(getConnector())
		getConnector()->log2(logType,message);

	appendLog(logType,message);
}

void SolverDialog::appendLog(int logType, QString log )
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
	ui->logsTextEdit->append(str);
	//_logText += str;
	//ui->logsTextEdit->setText(_logText);
}

void SolverDialog::onOpen()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open the solver input file"),".",
		tr("Solver input file (*.ins *.tdy)"));
	if(fileName.isEmpty())
		return;
	INSSolverPara para;
	para.fileName = fileName.toStdString();
	para.manager = _mainManager;
	_solver->setPara(para);
	_fileName = fileName;
	ui->fileValue->setText(_fileName);
}

void SolverDialog::updateEditText( QTextEdit* editer,const QString& fileName )
{
	QFile file(fileName);
	if(!file.open(QIODevice::Text|QIODevice::ReadOnly))
		return;

	QString s = file.readAll();
	editer->setText(s);
	file.close();
}

void SolverDialog::started()
{
	ui->btnOpen->setEnabled(false);
	ui->btnStart->setEnabled(false);
	ui->btnPause->setEnabled(true);
	ui->btnStop->setEnabled(true);
	QPixmap pix;
	pix.load(":/resources/b010.png");
	ui->statusLabel->setPixmap(pix);


	if(getConnector())
		getConnector()->started();
}


void SolverDialog::paused()
{
	ui->btnPause->setIcon(QIcon(":/resources/b005.png"));
	_isShowPaused = false;
	QPixmap pix;
	pix.load(":/resources/b008.png");
	ui->statusLabel->setPixmap(pix);

	if(getConnector())
		getConnector()->paused();
}

void SolverDialog::restarted()
{
	ui->btnPause->setIcon(QIcon(":/resources/b004.png"));
	_isShowPaused = true;
	QPixmap pix;
	pix.load(":/resources/b010.png");
	ui->statusLabel->setPixmap(pix);

	if(getConnector())
		getConnector()->restarted();
}

void SolverDialog::finished()
{
	ui->btnPause->setEnabled(false);
	ui->btnStop->setEnabled(false);
	QPixmap pix;
	pix.load(":/resources/b009.png");
	ui->statusLabel->setPixmap(pix);

	QTableWidgetItem* tmp = ui->tableWidget->item(0,3);
	QString t = tmp->text();
	ui->tableWidget->item(0,0)->setText(t);

	if(getConnector())
	{
		getConnector()->finished();
//		QTimer::singleShot(1000,this,SLOT(close()));
	}
}

void SolverDialog::onCurrentChanged( int index )
{
	if(index<1 || index>4)
		return;

	QFileInfo info(_fileName);
	QString path = info.absolutePath()+"/result/";

	QStringList filenames;
	filenames<<"overview.xml"<<"solver.log"<<"solver.msg"
		<<"topo_0.xml";
	switch (index)
	{
	case 1:
		updateEditText(ui->overTextEdit,path + filenames[0]);
		break;
	case 2:
		updateEditText(ui->logTextEdit,path + filenames[1]);
		break;
	case 3:
		updateEditText(ui->msgTextEdit,path + filenames[2]);
		break;
	case 4:
		updateEditText(ui->topoTextEdit,path + filenames[3]);
		break;

	}
		
	updateEditText(ui->topoTextEdit,path + filenames[index-1]);
}

QString SolverDialog::seconds2FriendlyString(int allSeconds)
{
	static QStringList singleLabel,doubleLabel;
	if(singleLabel.size()==0){
		singleLabel<<"day"<<"hour"<<"minute"<<"second";
		doubleLabel<<"days"<<"hours"<<"minutes"<<"seconds";
	}
	int days=0;
	int daysSeconds=3600*24;
	days=allSeconds/daysSeconds;
	int remainedSeconds=allSeconds%daysSeconds;
	QTime time(0,0,0);
	time=time.addSecs(remainedSeconds);
	QVector<int> t(4);
	t[0]=days;
	t[1]=time.hour();
	t[2]=time.minute();
	t[3]=time.second();

	QStringList timeStrs;
	for(int i=0;i<4;++i){
		if(timeStrs.size()>2)
			break;
		if(t[i]==1)
			timeStrs<<"1 "+singleLabel[i];
		else if(t[i]>0)
			timeStrs<<QString("%1 %2").arg(t[i]).arg(doubleLabel[i]);
		else if(timeStrs.size()>0)
			break;
	}
	return timeStrs.join(", ");
}
QString SolverDialog::seconds2String( int allSeconds )
{
	int days=0;
	int daysSeconds=3600*24;
	days=allSeconds/daysSeconds;
	int remainedSeconds=allSeconds%daysSeconds;
	QTime time(0,0,0);
	time=time.addSecs(remainedSeconds);
	QString timeStr=time.toString("hh:mm:ss");
	if(days==0)
		return timeStr;
	else if(days==1)
		return "1 day and "+timeStr;
	else
		return QString("%1 days and %2").arg(days).arg(timeStr);
}

void SolverDialog::updateLabel( int cpuTime,double process,int remainTime )
{
	QString CPTTimeStr=seconds2String(cpuTime);
	QString remainTimeStr=seconds2FriendlyString(remainTime);
	QString processStr;
	if(remainTimeStr.isEmpty())
		processStr=QString("%1%").arg((int)(process*100));
	else
		processStr=QString("%1% (remained time: %2)").arg(int(process*100)).arg(remainTimeStr);

	ui->processValue->setText(processStr);
	ui->cpuTimeValue->setText(CPTTimeStr);
}







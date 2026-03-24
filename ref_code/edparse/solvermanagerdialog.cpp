#include "solvermanagerdialog.h"
#include "ui_solvermanagerdialog.h"

#include "edcore/document.h"
#include "edcore/solution.h"
#include "edcore/project.h"
#include "edcore/entity.h"
#include "edcore/solveprocess.h"
#include "edcore/viewerprocess.h"
#include "edcore/filemanager.h"

#include "inssolver/inssolvermanager.h"
#include "inssolver/inssolver.h"
#include "inssolver/socketmessage.h"

#include "insviewer/socketservermessage.h"

#include <QProgressBar>
#include <QLabel>
#include <QMenu>
#include <QCloseEvent>
#include <QMessageBox>
#include <QLibrary>
#include <QFileInfo>
#include <QPoint>
#include <QDir>
#include <QScrollBar>
#include <QToolButton>

using namespace INSEditor;

QMap<QString,HWND> proViewHwndMap; 
QString currentProFile;

SolverManagerDialog::SolverManagerDialog(QWidget *parent)
	: QDialog(parent)
	,_runningCount(0)
	,_time(0)
{
	ui = new Ui::SolverManagerDialog();
	ui->setupUi(this);

	initBtn(false,false,false);

	_maxSolverCount = Document::instance()->getProperties()->maxSolveNumber;

	connect(Document::instance(),SIGNAL(solveProcessChanged(SolveProcess*)),
		this,SLOT(onSolveProcessChanged(SolveProcess*)));

	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); 
	ui->tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); 
	ui->tableWidget->verticalHeader()->hide();
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  
	ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);

	ui->finishTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->finishTableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); 
	ui->finishTableWidget->verticalHeader()->hide();
	ui->finishTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);

	ui->currTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->currTableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); 

	//工程列表控件的相关连接
	connect(ui->tableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showTableWidgetMenu(QPoint)));
	connect(ui->tableWidget,SIGNAL(itemClicked(QTableWidgetItem*)),SLOT(onTableWidgetItemClicked(QTableWidgetItem*)));

	//下方详细信息分页控件相关连接
	connect(ui->infoTabWidget,SIGNAL(currentChanged ( int )),this,SLOT(onInfoTabWidgetChanged(int)));

	//上方已完成相关连接
	connect(ui->finishTableWidget,SIGNAL(itemClicked(QTableWidgetItem*)),SLOT(onFinishTableWidgetItemClicked(QTableWidgetItem*)));
	connect(ui->finishTableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showFinishTableWidgetMenu(QPoint)));

	_checkStateTimer = new QTimer(this);
	connect(_checkStateTimer,SIGNAL(timeout()),this,SLOT(startCheckState()));

	createAction();
	ui->tableWidget->installEventFilter(this);
	ui->finishTableWidget->installEventFilter(this);

	connect(FileManager::instance(),SIGNAL(requestAddSolveProject()),this,SLOT(onUpdateSolveMaxNum()));
}

SolverManagerDialog::~SolverManagerDialog()
{
	delete ui;
}

void SolverManagerDialog::init()
{
	if(_solverProjectList.isEmpty())
		return;

	//存储之前对应的状态
	QStringList cpuTimeList,stateList,remainList;
	QList<int>	progressList;
	foreach(Project* pro,_solverProjectList)
	{
		for (int i=0;i<ui->tableWidget->rowCount();i++)
		{
			QTableWidgetItem* item = ui->tableWidget->item(i,0);
			if(item)
			{
				Project* tmp = (Project*)item->data(Qt::UserRole).toULongLong();
				if(tmp == pro)
				{
					cpuTimeList<<ui->tableWidget->item(i,1)->text();
					QProgressBar* bar = (QProgressBar*)ui->tableWidget->cellWidget(i,2);
					progressList<<bar->value();
					remainList<<ui->tableWidget->item(i,3)->text();
					stateList<< ui->tableWidget->item(i,4)->text();
				}
			}
		}
	}

	for (int i=ui->tableWidget->rowCount()-1;i>=0;i--)
		ui->tableWidget->removeRow(i);

	for(int i=0;i<_solverProjectList.count();i++)
	{
		Project* tmp = _solverProjectList[i];

		ui->tableWidget->insertRow(ui->tableWidget->rowCount());
		
		QTableWidgetItem* item = new QTableWidgetItem(tmp->getProjectName());
		item->setData(Qt::UserRole,quintptr(tmp));
		ui->tableWidget->setItem(i,0,item);

		if(i>=cpuTimeList.count())
			ui->tableWidget->setItem(i,1,new QTableWidgetItem(tr("00:00:00")));
		else
			ui->tableWidget->setItem(i,1,new QTableWidgetItem(cpuTimeList[i]));

		QProgressBar* bar = new QProgressBar;
		bar->setRange(0,100);
		if(i>=progressList.count())
			bar->setValue(0);
		else
			bar->setValue(progressList[i]);
		bar->setMaximumHeight(20);
		ui->tableWidget->setCellWidget(i,2,bar);

		if(i>=remainList.count())
			ui->tableWidget->setItem(i,3,new QTableWidgetItem(tr("0")));
		else
			ui->tableWidget->setItem(i,3,new QTableWidgetItem(remainList[i]));
		SolveProcess* process = tmp->getSolveProcess();
		if(i>=stateList.count())
			ui->tableWidget->setItem(i,4,new QTableWidgetItem(tr("Stop")));
		else
			ui->tableWidget->setItem(i,4,new QTableWidgetItem(stateList[i]));
	}

	if(_solverProjectList.isEmpty())
		initBtn(false,false,false);
}

void SolverManagerDialog::onStart()
{
	/*QList<Project*> list = getSelectProjects();
	foreach(Project* p,list)
	{
		if(_runningCount<_maxSolverCount)
			startByProject(p);
		else
			updateState(p,"Waiting");
		ui->startBtn->setEnabled(false);
		ui->pauseBtn->setEnabled(true);
		ui->pauseBtn->setText("Pause");
		ui->stopBtn->setEnabled(true);
	}*/
}

void SolverManagerDialog::onPauseOrRestart()
{
	QString text = ui->pauseBtn->text();
	if(!text.compare("Pause",Qt::CaseInsensitive))
	{
		onPause();
		initBtn(false,true,true,"Restart");
	}
	else
	{
		onRestart();
		initBtn(false,true,true);
	}
}

void SolverManagerDialog::onPause()
{
	QList<Project*> list = getSelectProjects();
	foreach(Project* pro,list)
	{
		if(!pro->getSolveProcess())
			continue;

		SendToServerMessage msg;
		msg.command = SendToServerMessage::PAUSE;
		pro->getSolveProcess()->sendMessage(msg);
	}
}

void SolverManagerDialog::onRestart()
{
	QList<Project*> list = getSelectProjects();
	foreach(Project* p,list)
	{
		if(!p->getSolveProcess())
			continue;

		SendToServerMessage msg;
		msg.command = SendToServerMessage::RESTART;
		p->getSolveProcess()->sendMessage(msg);
	}
}

void SolverManagerDialog::onStop()
{
	QList<Project*> list = getSelectProjects();
	foreach(Project* p,list)
	{
		if(!p->getSolveProcess())
			continue;

		SendToServerMessage msg;
		if(p->getSolveProcess()->getCurrentState() == SendToClientMessage::PAUSED)
		{
			msg.command = SendToServerMessage::RESTART;
			p->getSolveProcess()->sendMessage(msg);
		}
		Sleep(300);
		msg.command = SendToServerMessage::STOP;
		p->getSolveProcess()->sendMessage(msg);
	}
	if(!list.isEmpty())
		initBtn(false,false,false);
}

void SolverManagerDialog::updateState(Project* pro,const QString& message )
{
	int row = getProjectRow(pro);
	if(row == -1)
		return;
	QTableWidgetItem* item = ui->tableWidget->item(row,4);
	static QString msg; 
	if(item)
		item->setText(message);

	if(msg.compare(message) || msg.isEmpty())
	{
		msg = message;
		ui->tabWidget->setCurrentIndex(0);
	}

	if(!message.compare("Finished",Qt::CaseInsensitive))
	{
		//求解完成后把项目移到已完成表格中
		int currRow = ui->finishTableWidget->rowCount();
		ui->finishTableWidget->insertRow(ui->finishTableWidget->rowCount());
		ui->finishTableWidget->setItem(currRow,0,new QTableWidgetItem(ui->tableWidget->item(row,0)->text()));
		ui->finishTableWidget->item(currRow,0)->setData(Qt::UserRole,ui->tableWidget->item(row,0)->data(Qt::UserRole));

		ui->finishTableWidget->setItem(currRow,1,new QTableWidgetItem(ui->tableWidget->item(row,1)->text()));

		QProgressBar* bar = new QProgressBar;
		bar->setRange(0,100);
		QProgressBar* oldBar = (QProgressBar*)ui->tableWidget->cellWidget(row,2);
		if(oldBar->value()>0)
			bar->setValue(100);
		else
			bar->setValue(oldBar->value());

		bar->setMaximumHeight(20);
		ui->finishTableWidget->setCellWidget(currRow,2,bar);

		ui->finishTableWidget->setItem(currRow,3,new QTableWidgetItem(ui->tableWidget->item(row,4)->text()));

		ui->tableWidget->removeRow(row);
		_solverProjectList.removeOne(pro);

		SendToServerMessage msg;
		msg.command = SendToServerMessage::TERMINATE;
		pro->getSolveProcess()->sendMessage(msg);

		_runningCount--;
		while(true)
		{
			for (int i=0;i<ui->tableWidget->rowCount();i++)
			{
				if(_runningCount<_maxSolverCount)
				{
					QTableWidgetItem* tmp = ui->tableWidget->item(i,4);
					if(!tmp)
						continue;
					if(!tmp->text().compare("Waiting",Qt::CaseInsensitive))
					{
						Project* pro = (Project*)ui->tableWidget->item(i,0)->data(Qt::UserRole).toULongLong();
						startByProject(pro);
					}
				}
			}
			break;
		}
		if(ui->tableWidget->rowCount() == 0)
		{
			initBtn(false,false,false);
			ui->tabWidget->setCurrentIndex(1);
		}
	}
}

int SolverManagerDialog::getProjectRow(Project* pro)
{
	int row =-1;
	for (int i=0;i<ui->tableWidget->rowCount();i++)
	{
		QTableWidgetItem* tmp = ui->tableWidget->item(i,0);
		if(tmp)
		{
			Project* p = (Project*)tmp->data(Qt::UserRole).toULongLong();
			if(p == pro)
				row = i;
		}
	}
	return row;
}

QList<Project*> SolverManagerDialog::getSelectProjects()
{
	QList<Project*> list;
	for(int i=0;i<ui->tableWidget->rowCount();i++)
	{
		if(ui->tableWidget->isItemSelected(ui->tableWidget->item(i,0)))
		{
			Project* tmpPro = (Project*)ui->tableWidget->item(i,0)->data(Qt::UserRole).toULongLong();
			list.push_back(tmpPro);
		}
	}
	if(list.isEmpty())
	{
		for (int i=0;i<ui->tableWidget->rowCount();i++)
		{
			Project* tmpPro = (Project*)ui->tableWidget->item(i,0)->data(Qt::UserRole).toULongLong();
			list.push_back(tmpPro);
		}
	}
	return list;
}

void SolverManagerDialog::showTableWidgetMenu( QPoint p)
{
	if(ui->tableWidget->rowCount() == 0)
		return;
	QMenu menu;
	QAction* ac = menu.addAction(tr("Start"),this,SLOT(onStart()));
	if(ui->startBtn->isEnabled())
		ac->setEnabled(true);
	else
		ac->setEnabled(false);

	if(!ui->pauseBtn->text().compare("Pause",Qt::CaseInsensitive))
		ac = menu.addAction(tr("Pause"),this,SLOT(onPauseOrRestart()));
	else
		ac = menu.addAction(tr("Restart"),this,SLOT(onPauseOrRestart()));
	if(ui->pauseBtn->isEnabled())
		ac->setEnabled(true);
	else
		ac->setEnabled(false);

	ac = menu.addAction(tr("Stop"),this,SLOT(onStop()));
	if(ui->stopBtn->isEnabled())
		ac->setEnabled(true);
	else
		ac->setEnabled(false);

	menu.addAction(_openWithViewer);
	menu.addAction(_checkResultWithViewer);
	int row = ui->tableWidget->currentRow();
	if(row < 0)
		return;
	Project* pro = (Project*)ui->tableWidget->item(row,0)->data(Qt::UserRole).toULongLong();
	if(pro->hasResult())
		_checkResultWithViewer->setEnabled(true);
	else
		_checkResultWithViewer->setEnabled(false);

	ac = menu.addAction(tr("Cancel waiting for solving"),this,SLOT(onCancelSolve()));
	QList<int> rows = getSelectRows();
	for (int i=0;i<rows.count();i++)
	{
		if((!ui->tableWidget->item(rows[i],4)->text().compare("Waiting",Qt::CaseInsensitive)))
			continue;
		ac->setEnabled(false);
	}

	int curr = ui->tableWidget->currentRow();
	QString text = ui->tableWidget->item(curr,4)->text();
	if(curr != 0 && curr != -1 && !text.compare("Waiting",Qt::CaseInsensitive))
	{
		Project* pro = (Project*)ui->tableWidget->item(curr-1,0)->data(Qt::UserRole).toULongLong();
		if(!pro->getSolveProcess())
			ac = menu.addAction(tr("Move up"),this,SLOT(onMoveUp()));
	}

	if((curr != ui->tableWidget->rowCount()-1) && (curr != -1) && !text.compare("Waiting",Qt::CaseInsensitive))
	{
		QTableWidgetItem* tmp = ui->tableWidget->item(curr+1,0);
		if(tmp)
		{
			Project* pro = (Project*)tmp->data(Qt::UserRole).toULongLong();
			if(!pro->getSolveProcess())
				ac = menu.addAction(tr("Move down"),this,SLOT(onMoveDown()));
		}
	}

	QPoint tmp;
	tmp.setX(p.x() + ui->tabWidget->x()+25);
	tmp.setY(p.y() + ui->tabWidget->y()+80 + ui->tableWidget->horizontalHeader()->height());
	menu.exec(mapToGlobal(tmp));
}

void SolverManagerDialog::showFinishTableWidgetMenu( QPoint p )
{
	QMenu menu;

	menu.addAction(_openWithViewer);
	menu.addAction(_checkResultWithViewer);
	if(ui->finishTableWidget->rowCount() != 0)
	{
		int row = ui->finishTableWidget->currentRow();
		Project* pro = (Project*)ui->finishTableWidget->item(row,0)->data(Qt::UserRole).toULongLong();
		if(pro->hasResult())
			_checkResultWithViewer->setEnabled(true);
		else
			_checkResultWithViewer->setEnabled(false);

		QAction* ac = menu.addAction(tr("Remove selected"),this,SLOT(removeSelected()));

		ac = menu.addAction(tr("Remove all"),this,SLOT(removeAll()));

		QPoint tmp;
		tmp.setX(p.x() + ui->tabWidget->x()+25);
		tmp.setY(p.y() + ui->tabWidget->y()+80 + ui->finishTableWidget->horizontalHeader()->height());
		menu.exec(mapToGlobal(tmp));
	}
}

void SolverManagerDialog::onSolveProcessChanged( SolveProcess* process )
{
	Project* pro = (Project*)process->parent();
	if(!pro)
		return ;

	///求解时间
	double calcTime = process->getCalcTime();
	///最大求解时间
	double maxCalcTime = process->getMaxCalcTime();
	///开始求解时间
	double startCalcTime = process->getStartCalcTime();
	///积分误差
	double intError = process->getIntError();
	long  cpuTime = process->getCpuTime();	
	///预计剩余求解时间
	double remainTime = process->getReaminTime();
	///当前进度
	double p = process->getProcess();
	/// 当前物理积分步长
	double stepTime = process->getStepTime();
	/// 其他信息
//	QString otherMessage = process->getOtherMessage();
	///当前状态
	int currentState = process->getCurrentState();

	//更新最上方的表
	int row = getProjectRow(pro);
	if(row<0)
		return;

	ui->tableWidget->item(row,1)->setData(Qt::DisplayRole,seconds2String(cpuTime));

	QProgressBar* bar = (QProgressBar*)ui->tableWidget->cellWidget(row,2);
	bar->setValue(p*100);

	if(remainTime<0)
		remainTime=0;
	ui->tableWidget->item(row,3)->setData(Qt::DisplayRole,seconds2FriendlyString(int(remainTime)));

	//确认当前选中的项是否为当前更新的project
	bool flag = ui->tableWidget->isItemSelected(ui->tableWidget->item(row,0));

	if(currentState== SendToClientMessage::FINISHED)
		updateState(pro,"Finished");
	else if(currentState == SendToClientMessage::PAUSED)
		updateState(pro,"Paused");
	else if(currentState == SendToClientMessage::LOG)
	{
		if(flag)
			updateLog(pro->getSolveProcess()->getLogText());
		else if(!ui->tableWidget->currentItem())
		{//默认选中第一个
			QTableWidgetItem* tmp = ui->tableWidget->item(0,0);
			if(tmp)
			{
				Project* firstProject = (Project*)tmp->data(Qt::UserRole).toULongLong();
				updateLog(firstProject->getSolveProcess()->getLogText());
			}
		}
	}
	else
		updateState(pro,"Running");

	//是否更新中间的curr表
	if(flag)
		updateCurrTableWidget(calcTime,stepTime,startCalcTime,maxCalcTime,intError);
}

QString SolverManagerDialog::seconds2FriendlyString(int allSeconds)
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

void SolverManagerDialog::updateCurrTableWidget( const double& calTime,const double& stepTime,const double& startTime,const double& endTime,const double& error )
{
	ui->currTableWidget->item(0,0)->setText(QString::number(calTime));
	ui->currTableWidget->item(0,1)->setText(QString::number(stepTime));
	ui->currTableWidget->item(0,2)->setText(QString::number(startTime));
	ui->currTableWidget->item(0,3)->setText(QString::number(endTime));
	ui->currTableWidget->item(0,4)->setText(QString::number(error));
}

void SolverManagerDialog::addProjects( const QList<INSEditor::Project*>& projects )
{
	foreach(Project* p ,projects)
	{
		if(!_solverProjectList.contains(p))
			_solverProjectList.push_back(p);
	}
	init();
}

void SolverManagerDialog::addProject( INSEditor::Project* project )
{
	_solverProjectList.push_back(project);
	init();
}

void SolverManagerDialog::onMoveUp()
{
	QList<Project*> list = getSelectProjects();
	foreach(Project* pro ,list)
	{
		if(pro->getSolveProcess())
			list.removeOne(pro);
	}
	if(list.isEmpty())
		return;
	for (int i=0;i<list.count();i++)
		moveUp(list[i]);

	init();

	for (int i=0;i<ui->tableWidget->rowCount();i++)
	{
		Project* tmp = (Project*)ui->tableWidget->item(i,0)->data(Qt::UserRole).toULongLong();
		if(list.contains(tmp))
		{
			ui->tableWidget->selectRow(i);
			break;
		}
	}
}

void SolverManagerDialog::moveUp( INSEditor::Project* project )
{
	for (int i=0;i<_solverProjectList.count();i++)
	{
		if(_solverProjectList[i] == project)
		{
			if(i == 0 || _solverProjectList[i-1]->getSolveProcess())
				return ;

			Project* tmp = _solverProjectList[i-1];
			_solverProjectList[i-1] = _solverProjectList[i];
			_solverProjectList[i] = tmp;
			break;
		}
	}
}

void SolverManagerDialog::moveDown(Project* project)
{
	for (int i=0;i<_solverProjectList.count();i++)
	{
		if(_solverProjectList[i] == project)
		{
			if((i >= _solverProjectList.count()-1) || _solverProjectList[i+1]->getSolveProcess())
				return ;

			Project* tmp = _solverProjectList[i+1];
			_solverProjectList[i+1] = _solverProjectList[i];
			_solverProjectList[i] = tmp;
			break;
		}
	}
}

void SolverManagerDialog::onMoveDown()
{
	QList<Project*> list = getSelectProjects();
	foreach(Project* pro,list)
	{
		if(pro->getSolveProcess())
			list.removeOne(pro);
	}
	if(list.isEmpty())
		return;
	for (int i=list.count()-1;i>=0;i--)
		moveDown(list[i]);

	init();

	//选中这行
	for (int i=0;i<ui->tableWidget->rowCount();i++)
	{
		Project* tmp = (Project*)ui->tableWidget->item(i,0)->data(Qt::UserRole).toULongLong();
		if(list.contains(tmp))
		{
			ui->tableWidget->selectRow(i);
			break;
		}
	}
}

void SolverManagerDialog::onTableWidgetItemClicked( QTableWidgetItem* item )
{
	if(!item)
		return;
	int row = item->row();
	Project* pro = (Project*)ui->tableWidget->item(row,0)->data(Qt::UserRole).toULongLong();
	if(!pro)
		return;

	//如果选多条且状态不一禁止操作
	QList<int > rows = getSelectRows();
	QString tmpStr;
	foreach(int r,rows)
	{
		if(tmpStr.isEmpty())
			tmpStr = ui->tableWidget->item(r,4)->text();
		if(tmpStr != ui->tableWidget->item(r,4)->text())
		{
			initBtn(false,false,false);
			return;
		}
	}

	//等待状态。。
	SolveProcess* process =  pro->getSolveProcess();
	if(!process)
	{
		updateCurrTableWidget(0,0,0,0,0);
		updateInfoTabWidget(NULL);
		initBtn(false,false,false);
		return;
	}
	///求解时间
	double calcTime = process->getCalcTime();
	///最大求解时间
	double maxCalcTime = process->getMaxCalcTime();
	///开始求解时间
	double startCalcTime = process->getStartCalcTime();
	///积分误差
	double intError = process->getIntError();
	double stepTime = process->getStepTime();
	
	updateCurrTableWidget(calcTime,stepTime,startCalcTime,maxCalcTime,intError);
	updateInfoTabWidget(process);	

	//更新按钮
	switch (process->getCurrentState())
	{
	case SendToClientMessage::FINISHED:
		initBtn(false,false,false);
		break;
	case SendToClientMessage::PAUSED:
		initBtn(false,true,true,"Restart");
		break;
	case SendToClientMessage::RESTARTED:
		initBtn(false,true,true);
		break;
	case SendToClientMessage::STARTED:
		initBtn(false,true,true);
		break;
	default:
		initBtn(false,true,true);
	}
}

void SolverManagerDialog::onFinishTableWidgetItemClicked( QTableWidgetItem* item )
{
	if(!item)
		return;
	int row = item->row();
	QString proName = ui->finishTableWidget->item(item->row(),0)->text();
	QDir dir(INSEditor::Document::instance()->getSolution()->getSolutionDirectory()+proName);
	if(!dir.exists())
	{
		QMessageBox::warning(this,tr("Sorry"),tr("The current project is not found, may have been deleted!"));
		ui->finishTableWidget->removeRow(row);
		return;
	}
	Project* pro = (Project*)ui->finishTableWidget->item(row,0)->data(Qt::UserRole).toULongLong();
	if(!pro)
		return;
	SolveProcess* process =  pro->getSolveProcess();
	double calcTime = process->getCalcTime();
	double maxCalcTime = process->getMaxCalcTime();
	double startCalcTime = process->getStartCalcTime();
	double intError = process->getIntError();
	double stepTime = process->getStepTime();

	updateCurrTableWidget(calcTime,stepTime,startCalcTime,maxCalcTime,intError);
	updateInfoTabWidget(process);	
}

void SolverManagerDialog::updateInfoTabWidget( SolveProcess* process )
{
	int curr = ui->infoTabWidget->currentIndex();
	switch (curr)
	{
	case 0:
		{
			if(process)
				ui->logsTextEdit->setHtml(process->getLogText());
			else
				ui->logsTextEdit->setHtml("<font color=red>The solve is not started</font>");
			QScrollBar *scrollbar = ui->logsTextEdit->verticalScrollBar();
			scrollbar->setSliderPosition(scrollbar->maximum());
		}
		break;
	default:
		onInfoTabWidgetChanged(curr,process);
	}
}

void SolverManagerDialog::onInfoTabWidgetChanged( int index,SolveProcess* process)
{
	if(!process)
	{
		switch (index)
		{
		case 0:
			ui->logsTextEdit->setHtml("<font color=red>The solve is not started</font>");
			break;
		case 1:
			ui->overTextEdit->setHtml("<font color=red>The solve is not started</font>");
			break;
		case 2:
			ui->logTextEdit->setHtml("<font color=red>The solve is not started</font>");
			break;
		case 3:
			ui->msgTextEdit->setHtml("<font color=red>The solve is not started</font>");
			break;
		case 4:
			ui->topoTextEdit->setHtml("<font color=red>The solve is not started</font>");
			break;
		}
		return;
	}

	Project* pro = (Project*)process->parent();
	QString path = pro->getDirectory()+"result/";
	QString openFileName;
	switch (index)
	{
	case 0:
		return;
		break;
	case 1:
		//overView
		{
			openFileName = "overview.xml";
			updateEditText(ui->overTextEdit,path + openFileName);
		}
		break;
	case 2:
		//slover log
		{
			openFileName = "solver.log";
			updateEditText(ui->logTextEdit,path + openFileName);
		}
		break;

	case 3:
		//solver msg
		{
			openFileName = "solver.msg";
			updateEditText(ui->msgTextEdit,path + openFileName);
		}
		break;

	case 4:
		//topo 0
		{
			openFileName = "topo_0.xml";
			updateEditText(ui->topoTextEdit,path + openFileName);
		}
		break;
	}
}

void SolverManagerDialog::onInfoTabWidgetChanged( int curr )
{
	QTableWidgetItem* item = ui->tableWidget->item(ui->tableWidget->currentRow(),0);
	if(!item)
	{
		if(ui->tabWidget->currentIndex()==0)
			item = ui->tableWidget->item(0,0);
		else
			item = ui->finishTableWidget->item(0,0);
	}
	if(!item)
		return;

	Project* pro = (Project*)item->data(Qt::UserRole).toULongLong();
	onInfoTabWidgetChanged(curr,pro->getSolveProcess());
}

void SolverManagerDialog::updateEditText( QTextEdit* editer,const QString& fileName )
{
	QFile file(fileName);
	if(!file.open(QIODevice::Text|QIODevice::ReadOnly))
		return;

	editer->setText(file.readAll());
	file.close();
}

void SolverManagerDialog::solverProject( QList<Project*> projectList )
{
	QStringList solveringList ;
	bool running = false;
	foreach(Project* p,projectList)
	{
		if(p->getSolveProcess())
		{
			solveringList.push_back(p->getProjectName());
			if(p->getSolveProcess()->getCurrentState() != SendToClientMessage::FINISHED)
				running = true;
		}
	}

	if(!solveringList.isEmpty())
	{
		QMessageBox msgBox;
		msgBox.setText(tr("The projects %1 is running or finished.\n\nTo solve them again?").arg(solveringList.join(" , ")));
		msgBox.setIcon(QMessageBox::Warning);

		QPushButton *yesButton = msgBox.addButton(tr("Solve them"), QMessageBox::ActionRole);
		QPushButton *skipButton = msgBox.addButton(tr("Skip them"), QMessageBox::ActionRole);
		QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);

		msgBox.exec();
		if(msgBox.clickedButton() == yesButton)
		{
			foreach(Project* tmp,projectList)
			{
				if(solveringList.contains(tmp->getProjectName(),Qt::CaseInsensitive))
				{
					tmp->getSolveProcess()->deleteLater();
					tmp->clearSolveProcess();
					for (int i=ui->finishTableWidget->rowCount()-1;i>=0;i--)
					{
						if(solveringList.contains(ui->finishTableWidget->item(i,0)->text(),Qt::CaseInsensitive))
							ui->finishTableWidget->removeRow(i);
					}
				}
			}
		}
		else if (msgBox.clickedButton() == skipButton)
		{
			foreach(Project* tmp,projectList)
			{
				if(solveringList.contains(tmp->getProjectName(),Qt::CaseInsensitive))
					projectList.removeOne(tmp);
			}
		}
		else
			return;

		if(running)
			ui->tabWidget->setCurrentIndex(0);
		else
			ui->tabWidget->setCurrentIndex(1);
	}

	if(!projectList.isEmpty())
	{
		foreach(Project* tmp,projectList)
		{
			if(!_solverProjectList.contains(tmp))
				_solverProjectList<<tmp;
		}
		init();
		foreach(Project* p,projectList)
		{
			if(_runningCount<_maxSolverCount)
			{
				if(!p->getStartupEntity())
					QMessageBox::warning(this,tr("Warning"),tr("Project %1 no main file,please set start up file!").arg(p->getProjectName()));
				else
					startByProject(p);
			}
			else
				updateState(p,"Waiting");
			initBtn(false,true,true);
		}
		ui->tabWidget->setCurrentIndex(0);
	}
}

void SolverManagerDialog::startByProject( Project* project )
{
	int row = getProjectRow(project);
	if(row==-1 || project->getSolveProcess())
		return;

	project->openWithSolver2();
	SendToServerMessage msg;
	msg.command = SendToServerMessage::START;
	project->getSolveProcess()->sendMessage(msg);
	_runningCount++;
}

void SolverManagerDialog::removeSelected()
{
	QList<int> rows;
	for (int i=0;i<ui->finishTableWidget->rowCount();i++)
	{
		if(ui->finishTableWidget->isItemSelected(ui->finishTableWidget->item(i,0)))
			rows.push_front(i);
	}
	if(rows.isEmpty())
		QMessageBox::warning(this,tr("Warning"),tr("There is no selected item."));
	else
	{
		for (int i = 0;i<rows.count();i++)
		{
			int tmp = rows[i];
			Project* pro = (Project*)ui->finishTableWidget->item(tmp,0)->data(Qt::UserRole).toULongLong();
			delete pro->getSolveProcess();
			pro->clearSolveProcess();
			_solverProjectList.removeOne(pro);
			ui->finishTableWidget->removeRow(tmp);
		}
	}
}

void SolverManagerDialog::removeAll()
{
	QList<int> rows;
	for (int i=0;i<ui->finishTableWidget->rowCount();i++)
		rows.push_front(i);
	for (int i = 0;i<rows.count();i++)
	{
		int tmp = rows[i];
		Project* pro = (Project*)ui->finishTableWidget->item(tmp,0)->data(Qt::UserRole).toULongLong();
		delete pro->getSolveProcess();
		pro->clearSolveProcess();
		_solverProjectList.removeOne(pro);
		ui->finishTableWidget->removeRow(tmp);
	}
}

void SolverManagerDialog::updateLog(const QString& log )
{
	ui->logsTextEdit->setHtml(log);
	QScrollBar *scrollbar = ui->logsTextEdit->verticalScrollBar();
	scrollbar->setSliderPosition(scrollbar->maximum());
}

void SolverManagerDialog::onCancelSolve()
{
	QList<int> rows = getSelectRows();
	for (int i=0;i<rows.count();i++)
	{
		QTableWidgetItem* item = ui->tableWidget->item(rows[i],0);
		if(!item)
			return;
		Project* pro = (Project*)item->data(Qt::UserRole).toULongLong();
		_solverProjectList.removeOne(pro);
		emit updateSolveProjectOnTree(pro);
	}

	Sleep(200);
	init();
}

QString SolverManagerDialog::seconds2String( int allSeconds )
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

QList<int> SolverManagerDialog::getSelectRows()
{
	QList<int> selectRows;
	QList<QTableWidgetSelectionRange> list = ui->tableWidget->selectedRanges();
	foreach(QTableWidgetSelectionRange range,list)
	{
		for (int i=range.topRow();i<=range.bottomRow();i++)
		{
			if(!selectRows.contains(i))
				selectRows.push_front(i);
		}
	}
	return selectRows;
}

void SolverManagerDialog::initBtn( bool startBtnEnable,bool pauseBtnEnable,bool stopBtnEnable,const QString& pauseBtnText/*="Pause"*/ )
{
	ui->startBtn->setEnabled(startBtnEnable);
	ui->pauseBtn->setEnabled(pauseBtnEnable);
	ui->stopBtn->setEnabled(stopBtnEnable);
	ui->pauseBtn->setText(pauseBtnText);
}

void SolverManagerDialog::createAction()
{
	_openWithViewer = new QAction("&View(v)",this);
	connect(_openWithViewer,SIGNAL(triggered()),this,SLOT(openWithViewer()));
	_openWithViewer->setShortcut(QKeySequence("F4"));

	_checkResultWithViewer = new QAction("&Result(r)",this);
	connect(_checkResultWithViewer,SIGNAL(triggered()),this,SLOT(onCheckResult()));
}

void SolverManagerDialog::openWithViewer()
{
	QTableWidget* table;
	int id = ui->tabWidget->currentIndex();
	if (id == 0)
		table = ui->tableWidget;
	else
		table = ui->finishTableWidget;

	int row = table->currentRow();
	if(row<0)
	{
		QMessageBox::warning(this,"Warning","Please select one project.");
		return;
	}

	Project* pro = (Project*)table->item(row,0)->data(Qt::UserRole).toULongLong();
	
	pro->openWithViewer2();
}

bool SolverManagerDialog::eventFilter( QObject *watched, QEvent *event )
{
	if(event->type() == QEvent::KeyPress)
	{
		QKeyEvent* e = static_cast<QKeyEvent*>(event);
		if(e->key() == Qt::Key_F4)
			openWithViewer();
	}

	return QDialog::eventFilter(watched,event);
}

void SolverManagerDialog::onCheckResult()
{
	QTableWidget* table;
	int id = ui->tabWidget->currentIndex();
	if (id == 0)
		table = ui->tableWidget;
	else
		table = ui->finishTableWidget;

	int row = table->currentRow();
	if(row<0)
	{
		QMessageBox::warning(this,"Warning","Please select one project.");
		return;
	}

	Project* pro = (Project*)table->item(row,0)->data(Qt::UserRole).toULongLong();
	checkResult(pro);
}

BOOL CALLBACK SolverManagerDialog::EnumWindowsProc_viewer( HWND hwnd,LPARAM lparam )
{
	char lpWinTitle[256];  
	::GetWindowTextA(hwnd,lpWinTitle,256-1);
	QString m_strTitle(lpWinTitle); 
	if(m_strTitle.contains("INSIDES Viewer",Qt::CaseInsensitive) && m_strTitle.contains(currentProFile,Qt::CaseInsensitive)) 
	{
		proViewHwndMap[currentProFile] = hwnd;
		return FALSE;
	}

	return TRUE ;
}

void SolverManagerDialog::checkResult(Project* pro,bool fromTree)
{
	currentProFile = pro->getStartupEntity()->getFullFileName();
	if(pro->getViewProcess())
	{
		//后处理是开着的
		if(pro->getViewProcess()->getViewer())
		{
			if(fromTree)
			{
				_currentProject = pro;
				_checkType = 3;
				_time =0;
				_checkStateTimer->start(1000);
			}
			else
			{
				updateViewer(pro);
				
				//这里激活

				DWORD ProcessID;
				GetWindowThreadProcessId(proViewHwndMap[currentProFile],&ProcessID);
				if(ProcessID == pro->getViewProcess()->getViewer()->pid()->dwProcessId)
				{
					if(IsIconic(proViewHwndMap[currentProFile]))
						::ShowWindow(proViewHwndMap[currentProFile],SW_SHOWMAXIMIZED );
					::ShowWindow(proViewHwndMap[currentProFile],SW_SHOW);
					::SetForegroundWindow(proViewHwndMap[currentProFile]);
				}
				
			}
		}
		else
		{//后处理被关掉了
			delete pro->getViewProcess();
			pro->clearViewProcess();
			if(fromTree)
			{
				_currentProject = pro;
				_checkType = 3;
				_time =0;
				_checkStateTimer->start(1000);
			}
			else
			{
				openWithViewer();
				updateViewer(pro);
			}
		}
	}
	else
	{//从未打开过后处理
		if(fromTree)
		{
			_currentProject = pro;
			_checkType = 3;
			_time =0;
			_checkStateTimer->start(1000);
		}
		else
		{
			openWithViewer();
			updateViewer(pro);
		}
	}
	
}

void SolverManagerDialog::checkResultFromTree( INSEditor::Project* pro )
{
	checkResult(pro,true);
}

void SolverManagerDialog::notifyViewerImportResult(Project* pro)
{
	//通知后处理更新结果
	ViewerSocketToServerMessage vMsg;
	vMsg.command = ViewerSocketToServerMessage::IMPORT_RESULT;
	vMsg.informations["FILE_NAME"] = pro->getStartupEntity()->getFullFileName();
	pro->getViewProcess()->sendMessage(vMsg);
}

void SolverManagerDialog::updateViewer( INSEditor::Project* pro )
{
	if(pro->getSolveProcess())
	{
		//正在计算中
		if(pro->getSolveProcess()->getCurrentState() != SendToClientMessage::FINISHED)
		{
			//通知求解器暂停
			SendToServerMessage msg;
			msg.command = SendToServerMessage::PAUSE;
			pro->getSolveProcess()->sendMessage(msg);

			_currentProject = pro;
			_checkType = 1;
			_time =0;
			_checkStateTimer->start(1000);
			
		}
		else//计算完成的
			notifyViewerImportResult(pro);
	}
}

void SolverManagerDialog::startCheckState()
{
	//等待求解器回应
	_time ++;
	
	switch (_checkType)
	{
	case 1:
		{
			if(_currentProject->getSolveProcess()->getCurrentState() == SendToClientMessage::PAUSED)
			{
				notifyViewerImportResult(_currentProject);
				_checkType = 2;
			}
		}
		break;
	case 2:
		{
			if(_currentProject->getViewProcess()->getCuState() == ViewerServerToClientMessage::IMPORTED_RESULT)
			{
				//继续计算
				SendToServerMessage msg;
				msg.command = SendToServerMessage::RESTART;
				_currentProject->getSolveProcess()->sendMessage(msg);
				_checkStateTimer->stop();

				//查找保存后处理句柄
				::EnumWindows(EnumWindowsProc_viewer,0) ;
			}
		}
		break;
	case 3:
		{
			notifyViewerImportResult(_currentProject);
			_checkStateTimer->stop();
		}
		break;
	}
	if(_time>10)
	{
		if(_checkType ==1)
		{
			QMessageBox::warning(this,"Warning","The Solver no reply.");
			_checkStateTimer->stop();
		}
		else
		{
			QMessageBox::warning(this,"Warning","The viewer no reply.");
			_checkStateTimer->stop();
		}
	} 
}

void SolverManagerDialog::onUpdateSolveMaxNum()
{
	_maxSolverCount = Document::instance()->getProperties()->maxSolveNumber;
	for (int i=0;i<ui->tableWidget->rowCount();i++)
	{
		if(_runningCount<_maxSolverCount)
		{
			QTableWidgetItem* tmp = ui->tableWidget->item(i,4);
			if(!tmp)
				continue;
			if(!tmp->text().compare("Waiting",Qt::CaseInsensitive))
			{
				Project* pro = (Project*)ui->tableWidget->item(i,0)->data(Qt::UserRole).toULongLong();
				startByProject(pro);
			}
		}
	}
}




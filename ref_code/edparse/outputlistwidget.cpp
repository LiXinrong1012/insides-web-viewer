#include "outputlistwidget.h"
#include "ui_outputlistwidget.h"

#include "edcore/filemanager.h"
#include "edcompile/mainitem.h"

#include <QFileInfo>
#include <QMessageBox>
#include <QMenu>
#include <QClipboard>

OutputListWidget::OutputListWidget(QWidget *parent)
	: QListWidget(parent)
	,_time(0)
	,_buildCount(0)
{
	ui = new Ui::OutputListWidget();
	ui->setupUi(this);

	//¼ÇÂ¼±àÒëÊ±¼ä
	//_timer = new QTimer;
	//connect(_timer,SIGNAL(timeout()),this,SLOT(onTimeout()));

	this->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));

	connect(FileManager::instance(),SIGNAL(requestUpdateOutputInfo(const INSEditor::Parse::CompileInfoItem&)),this,SLOT(updateOutputInfo(const INSEditor::Parse::CompileInfoItem&)));
	connect(FileManager::instance(),SIGNAL(requestBeginBuild()),this,SLOT(onBeginBuild()));
	connect(FileManager::instance(),SIGNAL(requestEndBuild()),this,SLOT(onEndBuild()));

	connect(FileManager::instance(),SIGNAL(requestTestOutput(QString)),this,SLOT(onTestOutput(QString)));
}

OutputListWidget::~OutputListWidget()
{
	delete ui;
}

void OutputListWidget::updateOutputInfo( const INSEditor::Parse::CompileInfoItem& item )
{
	QString str;
	if(_fileName.isEmpty() || _fileName != item.fileName)
	{
		_buildCount++;
		_fileName = item.fileName;
		str =QString::number(_buildCount) + ">------ Build started: File: "+ item.fileName +" ------";
		this->addItem(str);
	}
	QFileInfo info(_fileName);
	str = QString::number(_buildCount)+">"+info.fileName() + QString("(%1)").arg(item.rowIndex + 1)+": error:" + item.errorInfo ;
	QListWidgetItem* tmp = new QListWidgetItem(str);
	tmp->setData(Build_File,item.fileName);
	tmp->setData(Build_Row,item.rowIndex);
	tmp->setData(Build_Column,item.columnIndex);
	tmp->setData(Build_Info,item.errorInfo);
	this->addItem(tmp);
}

void OutputListWidget::onBeginBuild()
{
	this->clear();
	_dockWidget->show();
	_dockWidget->raise();
}

void OutputListWidget::onEndBuild()
{
	QString str;
	this->addItem(QString::number(_buildCount)+">");
	this->addItem(QString::number(_buildCount)+">Build succeeded.");
	this->addItem(QString::number(_buildCount)+">");

	/*str = QString::number(_buildCount)+">Time Elapsed 00:00:"+QString::number(_time);
	this->addItem(str);*/

	str = "========== Build: "+ QString::number(_buildCount) + " succeeded ==========";
	this->addItem(str);

	_time = 0;
	_buildCount = 0;
	_fileName = "";
}

void OutputListWidget::onTimeout()
{
	_time+=1;
}

void OutputListWidget::contextMenuRequest(QPoint p)
{
	if(this->count() == 0)
		return;

	QMenu menu;
	QAction* ac = menu.addAction("Copy to clipboard");
	connect(ac,SIGNAL(triggered()),this,SLOT(copyToClipboard()));
	
	ac = menu.addAction("Clear all");
	connect(ac,SIGNAL(triggered()),this,SLOT(clearAll()));

	menu.exec(mapToGlobal(p));
}

void OutputListWidget::copyToClipboard()
{
	QString currText = this->currentItem()->text();
	if(currText.isEmpty())
	{
		QMessageBox::warning(this,"Warning","Selected nothing!");
		return;
	}

	QClipboard * clipboard = QApplication::clipboard();
	clipboard->setText(currText);
}

void OutputListWidget::mouseDoubleClickEvent( QMouseEvent * event )
{
	QListWidgetItem* item = this->currentItem();
	if(!item)
	{
		QListWidget::mouseDoubleClickEvent(event);
		return;
	}
	if(item->data(Build_File).toString().isEmpty())
	{
		QListWidget::mouseDoubleClickEvent(event);
		return;
	}

	FileManager::instance()->notifyGotoPosition(item->data(Build_File).toString(),item->data(Build_Row).toInt(),item->data(Build_Column).toInt());
}

void OutputListWidget::clearAll()
{
	this->clear();
}

void OutputListWidget::onTestOutput( QString s )
{
	this->addItem(s);
	this->scrollToBottom();
}


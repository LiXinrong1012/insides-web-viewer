#include "vinteractivetablewidget.h"
#include "ui_vinteractivetablewidget.h"

#include "interactivetablemodel.h"

#include "precore/projectselector.h"

#include "base/activeviewobject.h"
#include "base/AnimationControler.h"

#include "pubbase/mimedata.h"

#include "prevttbase/sorttransposeproxymodel.h"
#include "prevttbase/settingdialog.h"

#include <QtGui>

VInteractiveTableWidget::VInteractiveTableWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::VInteractiveTableWidget();
	ui->setupUi(this);

	_viewModel=new InteractiveTableModel(this);
	_proxyModel = new SortTransposeProxyModel();
	_proxyModel->setSourceModel(_viewModel);
	ui->tableView->setProxyModel(_proxyModel);
	ui->tableView->setModel(_proxyModel);

	connect(ui->selector,SIGNAL(itemAdding(TableItemTitle)),
		_viewModel,SLOT(onItemAdding(TableItemTitle)));
	connect(ui->selector,SIGNAL(notifyUpdate(TableItemTitle)),
		_viewModel,SLOT(onNotifyUpdate(TableItemTitle)));

	connect(_viewModel,SIGNAL(newDataAdded()),
		ui->tableView,SLOT(onNewDataAdded()));

	//ui->tableView->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
	//connect(ui->tableView, SIGNAL(beginSort(int)), _proxyModel, SLOT(updateComponent(int)));
	connect(ui->tableView,SIGNAL(resetLayout()),_viewModel,SLOT(onResetLayout()));

	ui->selector->emit_itemAdding();
}

VInteractiveTableWidget::~VInteractiveTableWidget()
{
	delete ui;
}

void VInteractiveTableWidget::onResultsDeleted()
{
	_viewModel->clearData();
	ui->tableView->reset();
}

ResultSelectorWidget* VInteractiveTableWidget::getSelector()
{
	return ui->selector;
}

bool VInteractiveTableWidget::saveMyState( QDataStream& out )
{
	INSIDES::MimeData mimeData;
	QDataStream& stream=*mimeData.startWriteCustomData("insviewer/pretm/1.0");
	TableItemTitle title=_viewModel->getItemTitle();
	stream<<title.itemName;
	stream<<title.secIndex;

	mimeData.stopWriteAllCustomData();
	out<<mimeData;
	return true;
}

bool VInteractiveTableWidget::loadMyState( QDataStream& in )
{
	MimeData mimeData;
	in>>mimeData;
	if(mimeData.hasFormat("insviewer/pretm/1.0"))
	{
		QSharedPointer<QDataStream> stream=mimeData.startReadCustomData("insviewer/pretm/1.0");
		TableItemTitle title;
		(*stream)>>title.itemName;
		(*stream)>>title.secIndex;
		_viewModel->setItemTitle(title);
	}

	return true;
}

void VInteractiveTableWidget::exportAsTxt()
{
	QString fileName= QFileDialog::getSaveFileName(this, tr("Save File"),
		".",
		tr("dat (*.dat)"));

	if(fileName.isEmpty())
		return;

	int rowCount=_viewModel->rowCount();
	int columnCount=_viewModel->columnCount();
	QFile dataFile(fileName);
	if (dataFile.open(QFile::WriteOnly | QFile::Truncate)) {
		QTextStream out(&dataFile);
		QList<QString> headers;
		int realColumnCount=0;
		int realRowCount=0;

		writeHeader(out,rowCount,columnCount,headers,realColumnCount,realRowCount);

		if(rowCount*columnCount==0)
			out<<"Table size: Row = "<<rowCount<<" ,Column = "<<columnCount<<endl;
		else
		{
			out<<"Table size: Row = "<<realRowCount<<" ,Column = "<<realColumnCount<<endl;

			out<<"Headers\t";
			for(int i=0;i<headers.size();++i)
				out<<headers[i]<<"\t";
			out<<endl;

			writeOneFrame(out,rowCount,columnCount);
		}
	}
}

void VInteractiveTableWidget::addItems()
{
	const BaseItemSelection& selection=myProjectSelector()->getSelection();
	if(selection.size()==0)
		return;

	ui->selector->setCurrentBaseItem(selection[0]);
	_viewModel->setBaseItemList(selection);
}

void VInteractiveTableWidget::writeOneFrame(QTextStream& out,int rowCount,int columnCount)
{
	if(ui->tableView->selectionModel()->selectedRows().size()==0)
	{
		for(int row=0;row<rowCount;++row)
		{
			out<<_viewModel->headerData(row,Qt::Vertical).toString()<<"\t";
			for(int column=0;column<columnCount;++column)
			{
				QVariant var=_viewModel->data(_viewModel->index(row,column));
				QString strValue=var.toString();
				QStringList vec=strValue.split(',');
				for(int i=0;i<vec.size();++i)
					out<<vec[i]<<"\t";
			}
			out<<endl;
		}
	}
	else
	{
		QModelIndexList selectedList=ui->tableView->selectionModel()->selectedRows();
		for(int i=0;i<selectedList.size();++i)
		{
			int row=selectedList[i].row();
			out<<_viewModel->headerData(row,Qt::Vertical).toString()<<"\t";
			for(int column=0;column<columnCount;++column)
			{
				QVariant var=_viewModel->data(_viewModel->index(row,column));
				QString strValue=var.toString();
				QStringList vec=strValue.split(',');
				for(int i=0;i<vec.size();++i)
					out<<vec[i]<<"\t";
			}
			out<<endl;
		}
	}
}

bool VInteractiveTableWidget::writeHeader(QTextStream& out,int rowCount,int columnCount,
	QList<QString>& headers,int& realColumnCount,int& realRowCount)
{
	out<<"This file is exported from INSIDES Viewer."<<endl;
	out<<"Creating time: "<<QDateTime::currentDateTime().toString("yyyy.dd.MM hh:mm:ss")<<endl;

	if(rowCount*columnCount==0)
		return false;

	// headers
	for(int column=0;column<columnCount;++column)
	{
		QVariant var=_viewModel->data(_viewModel->index(0,column));
		QString strValue=var.toString();
		QStringList vec=strValue.split(',');
		if(vec.size()==1){
			realColumnCount=realColumnCount+1;
			headers.push_back(_viewModel->headerData(column,Qt::Horizontal).toString());
		}
		else{
			realColumnCount=realColumnCount+vec.size();
			QString tmpStr=_viewModel->headerData(column,Qt::Horizontal).toString();
			for(int i=0;i<vec.size();++i)
				headers.push_back(QString("%1-%2").arg(tmpStr).arg(i+1));
		}
	}
	QModelIndexList selectedRows=ui->tableView->selectionModel()->selectedRows();
	if(selectedRows.size()!=0)
		realRowCount=selectedRows.size();
	else
		realRowCount=rowCount;
	return true;
}

void VInteractiveTableWidget::exportAllAsTxt()
{
	QString fileName= QFileDialog::getSaveFileName(this, tr("Save File"),
		".",
		tr("dat (*.dat)"));

	if(fileName.isEmpty())
		return;

	int timeDelta=QInputDialog::getInt(this,"Get time interval","Enter the time interval:",1);
	if(timeDelta<=0)
	{
		QMessageBox::about(this,"Error","Time interval should be larger than zero.");
		return;
	}

	Base::AnimationControler* controler=Base::ActiveViewObject::instance()->animationControler();
	int originalFrame=controler->getCurrentFrame();
	int frameCount=controler->getFrameCount();


	int rowCount=_viewModel->rowCount();
	int columnCount=_viewModel->columnCount();
	QFile dataFile(fileName);
	if (dataFile.open(QFile::WriteOnly | QFile::Truncate)) {
		QTextStream out(&dataFile);

		QList<QString> headers;
		int realColumnCount=0;
		int realRowCount=0;
		writeHeader(out,rowCount,columnCount,headers,realColumnCount,realRowCount);
		if(rowCount*columnCount==0)
			out<<"Table size: Row = "<<rowCount<<" ,Column = "<<columnCount<<endl;
		else
		{
			// headers
			out<<"Table size: Row = "<<realRowCount<<" ,Column = "<<realColumnCount+1<<
				",Time delta =  "<<timeDelta<<endl;

			out<<"Headers\t";
			for(int i=0;i<headers.size();++i)
				out<<headers[i]<<"\t";
			out<<endl;

			for(int i=0;i<frameCount;++i)
			{
				if(i%timeDelta==0)
				{
					_viewModel->setDataToFrame(i);
					writeOneFrame(out,rowCount,columnCount);
				}
			}
			_viewModel->setDataToFrame(originalFrame);
		}
	}
}

void VInteractiveTableWidget::showSetting()
{
	TableSetting setting;
	setting.doubleCount = _viewModel->getDoubleCount();
	SettingDialog dlg(setting,this);
	dlg.exec();

	_viewModel->setDoubleCount(setting.doubleCount);

	ui->tableView->resizeColumnsToContents();
}

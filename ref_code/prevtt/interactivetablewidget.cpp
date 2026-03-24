#include "interactivetablewidget.h"
#include "ui_interactivetablewidget.h"

#include "sourcedatamodel.h"

#include "prevttbase/sorttransposeproxymodel.h"
#include "prevttbase/settingdialog.h"

#include "precore/projectselector.h"

#include "pubbase/mimedata.h"

#include <QtGui>


InteractiveTableWidget::InteractiveTableWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::InteractiveTableWidget();
	ui->setupUi(this);
	
	_viewModel=new SourceDataModel(this);
//	ui->tableView->setModel(_viewModel);
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

	connect(ui->tableView->selectionModel(),SIGNAL(selectionChanged(const QItemSelection&,const QItemSelection&)),
		this,SLOT(onSelectionChanged ()));

	connect(ui->tableView,SIGNAL(setSourceModel()),this,SLOT(onSetSourceModel()));
	connect(ui->tableView,SIGNAL(resetLayout()),_viewModel,SLOT(onResetLayout()));
	connect(ui->tableView,SIGNAL(selectRows(const QString&,int)),this,SLOT(onSelectRow(const QString&,int)));

	_transposeAction = new QAction("exchange header position",this);
	_transposeAction->setIcon(QIcon(":/resources/menu/a012x16x16.png"));
    connect(_transposeAction,SIGNAL(triggered()),ui->tableView,SLOT(onExchangeActionClicked()));

	ui->selector->emit_itemAdding();
}

InteractiveTableWidget::~InteractiveTableWidget()
{
	delete ui;
}

void InteractiveTableWidget::onResultsDeleted()
{
	SourceDataModel* m = (SourceDataModel*)ui->tableView->model();
	m->clearData();
	ui->tableView->reset();
}

ResultSelectorWidget* InteractiveTableWidget::getSelector()
{
	return ui->selector;
}

bool InteractiveTableWidget::saveMyState( QDataStream& out )
{
	MimeData mimeData;
	QDataStream& stream=*mimeData.startWriteCustomData("insviewer/prett/1.0");
//	SourceDataModel* m = (SourceDataModel*)ui->tableView->model();
	TableItemTitle title=_viewModel->getItemTitle();
	stream<<title.itemName;
	stream<<title.secIndex;

	mimeData.stopWriteAllCustomData();
	out<<mimeData;
	return true;
}

bool InteractiveTableWidget::loadMyState( QDataStream& in, qint64 dataSize)
{
	MimeData mimeData;
	in>>mimeData;
	if(mimeData.hasFormat("insviewer/prett/1.0"))
	{
		QSharedPointer<QDataStream> stream=mimeData.startReadCustomData("insviewer/prett/1.0");
		TableItemTitle title;
		(*stream)>>title.itemName;
		(*stream)>>title.secIndex;
//		SourceDataModel* m = (SourceDataModel*)ui->tableView->model();
		_viewModel->setItemTitle(title);
	}

	return true;
}

void InteractiveTableWidget::exportAsTxt()
{
	QString fileName= QFileDialog::getSaveFileName(this, tr("Save File"),
		".",
		tr("dat (*.dat *.dat *.dat)"));

	if(fileName.isEmpty())
		return;

	int rowCount=ui->tableView->model()->rowCount();
	int columnCount=ui->tableView->model()->columnCount();
	QFile dataFile(fileName);
	if (dataFile.open(QFile::WriteOnly | QFile::Truncate)) {
		QTextStream out(&dataFile);
		out<<"This file is exported from INSIDES Viewer."<<endl;
		out<<"Creating time: "<<QDateTime::currentDateTime().toString("yyyy.dd.MM hh:mm:ss")<<endl;

		if(rowCount*columnCount==0)
			out<<"Table size: Row = "<<rowCount<<" ,Column = "<<columnCount<<endl;
		else
		{
			// headers
			QVector<QString> headers;
			int realColumnCount=0;
			for(int column=0;column<columnCount;++column)
			{
				QVariant var=ui->tableView->model()->data(ui->tableView->model()->index(0,column));
				QString strValue=var.toString();
				QStringList vec=strValue.split(',');
				if(vec.size()==1){
					realColumnCount=realColumnCount+1;
					headers.push_back(ui->tableView->model()->headerData(column,Qt::Horizontal).toString());
				}
				else{
					realColumnCount=realColumnCount+vec.size();
					QString tmpStr=ui->tableView->model()->headerData(column,Qt::Horizontal).toString();
					for(int i=0;i<vec.size();++i)
						headers.push_back(QString("%1-%2").arg(tmpStr).arg(i+1));
				}
			}
			out<<"Table size: Row = "<<rowCount<<" ,Column = "<<realColumnCount<<endl;

			for(int i=0;i<headers.size();++i)
				out<<headers[i]<<"\t";
			out<<endl;


			for(int row=0;row<rowCount;++row)
			{
				for(int column=0;column<columnCount;++column)
				{
					QVariant var=ui->tableView->model()->data(ui->tableView->model()->index(row,column));
					QString strValue=var.toString();
					QStringList vec=strValue.split(',');
					for(int i=0;i<vec.size();++i)
						out<<vec[i]<<"\t";
				}
				out<<endl;
			}
		}
	}
}

void InteractiveTableWidget::onSelectionChanged()
{
	SourceDataModel* myModel=(SourceDataModel*)ui->tableView->model();

	if(!myModel)
		return;

	return;

	//int testInt = myModel->getReulstType();
	//if((myModel->getReulstType()!=TDY_PRE_CATE_FEMPART) || (myModel->getSectionIndex()==0) )
	//	return;

	SelectionNodeElem selectionNodeElem;
	IResultItem* resultItem=myModel->getResultItem();
	QModelIndexList selection=ui->tableView->selectionModel()->selectedRows();
	foreach(QModelIndex index,selection)
		selectionNodeElem.indices.push_back(index.row());

	QModelIndex ind = ui->tableView->selectionModel()->currentIndex();
	int row = ind.row();
	if (selectionNodeElem.indices.count()==0)
		selectionNodeElem.indices.push_back(row); 

	selectionNodeElem.item=resultItem->connectedItem();
	selectionNodeElem.resultItem=resultItem;

	//第二个下拉框选的是哪个
	if(myModel->getSectionIndex()==1)
		myProjectSelector()->notifySetSelectionNodes(selectionNodeElem);
	else
		myProjectSelector()->notifySetSelectionElements(selectionNodeElem);
}

void InteractiveTableWidget::onSetSourceModel()
{
	ui->tableView->setModel(_viewModel);
}

void InteractiveTableWidget::onSelectRow(const QString& selectionName,int indices)
{
	SortTransposeProxyModel* interModel=static_cast<SortTransposeProxyModel*>(ui->tableView->model());
	SourceDataModel* model = static_cast<SourceDataModel*>(interModel->sourceModel());
	TableItemTitle title = model->getItemTitle();
	QString pointName = model->getItemTitle().itemName;

	if (selectionName == pointName)
		ui->tableView->selectRow(indices);
}

void InteractiveTableWidget::showSetting()
{
	TableSetting setting;
	setting.doubleCount = _viewModel->getDoubleCount();
	SettingDialog dlg(setting,this);
	dlg.exec();

	_viewModel->setDoubleCount(setting.doubleCount);

	ui->tableView->resizeColumnsToContents();
}


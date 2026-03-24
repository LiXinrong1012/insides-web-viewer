#include "sorttableview.h"
#include "precore/precore_data.h"
#include "precore/projectselector.h"
#include "precore/IResultItem.h"
#include "sorttransposeproxymodel.h"

#include <QtGui>

SortTableView::SortTableView(QWidget *parent)
	: QTableView(parent)
	,_currentCol(0)
	,_sortFalg(false)
{
	myResultDocument()->attachListener(this);
	horizontalHeader()->setMovable(true);
	myProjectSelector()->attachSupplier(this);

	this->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(this->horizontalHeader(),SIGNAL(customContextMenuRequested ( const QPoint & )),this,SLOT(onCustomContextMenuRequested ( const QPoint & )));
	connect(this->horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(onSectionClicked(int)));

	connect(this->verticalHeader(),SIGNAL(customContextMenuRequested ( const QPoint & )),this,SLOT(onCustomContextMenuRequested ( const QPoint & )));
	connect(this->verticalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(onSectionClicked(int)));

	this->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
}

SortTableView::~SortTableView()
{
	myResultDocument()->disattachListener(this);
	myProjectSelector()->disattachSupplier(this);
}

void SortTableView::onResultCurrentFrameChanged()
{
	QAbstractItemModel* m=model();
	if(m)
		emit resetLayout();
}

void SortTableView::onNewDataAdded()
{
	resizeColumnsToContents();
}

void SortTableView::ss_onSetSelectionNodes_protected( const SelectionNodeElem& selection )
{
	QString selectionName =selection.item->getFullName();
	QAbstractItemModel* m=model();
	if(!m)
		return;
	
	emit selectRows(selectionName,selection.indices[0]);
}

void SortTableView::ss_onSetSelectionElements_protected( const SelectionNodeElem& selection )
{
}

void SortTableView::onCustomContextMenuRequested( const QPoint &pos )
{
	QString temString;
	QHeaderView* header = (QHeaderView*)sender();
	if(!_proxyModel->isTranspose())
	{
		if(header != this->horizontalHeader())
			return;

		_currentCol=this->horizontalHeader()->logicalIndexAt(pos);
		temString = this->model()->data(this->model()->index(0,_currentCol),Qt::DisplayRole).toString();
	}
	else
	{
		if(header != this->verticalHeader())
			return;

		_currentCol = this->verticalHeader()->logicalIndexAt(pos);
		temString = this->model()->data(this->model()->index(_currentCol,0),Qt::DisplayRole).toString();
	}

	QMenu hearderMenu;
	QMenu* sortMenu = hearderMenu.addMenu("Sort");
	QAction* noSortAction = hearderMenu.addAction("Disable sort");

	if (temString.split(",").count()==0)
		return;
	else
	{
		for (int i=0;i<temString.split(",").count();i++)
		{
			if(!_proxyModel->isTranspose())
			{
				QAction* action = sortMenu->addAction(QString(tr("column %1")).arg(i+1));
				action->setData(i);
				connect(action,SIGNAL(triggered()),this,SLOT(sortBy()));
			}
			else
			{
				QAction* action = sortMenu->addAction(QString(tr("row %1")).arg(i+1));
				action->setData(i);
				connect(action,SIGNAL(triggered()),this,SLOT(sortBy()));
			}
		}

		if (temString.split(",").count()!=1)
		{
			QAction* ac = sortMenu->addAction(tr("length"));
			connect(ac,SIGNAL(triggered(bool)),this,SLOT(sortByLength()));
		}
		connect(noSortAction,SIGNAL(triggered()),this,SLOT(closeSort()));

		hearderMenu.exec(QCursor::pos());
	}
}

void SortTableView::onSectionClicked( int section )
{
	QHeaderView* header = (QHeaderView*)sender();
	if(_proxyModel->isTranspose())
	{
		if(header != this->verticalHeader())
			return;
	}
	else
	{
		if(header != this->horizontalHeader())
			return;
	}

	if (_sortFalg)
	{
		if (_currentCol == section)
		{
			_proxyModel->setEnableMySort(true);
			this->setSortingEnabled(true);
		}
		else
		{
			_proxyModel->setEnableMySort(false);
			this->setSortingEnabled(false);
		}
	}
	else
		_proxyModel->setEnableMySort(false);
}

void SortTableView::closeSort()
{
	_sortFalg = false;
	_proxyModel->sort(0);
	_proxyModel->setEnableMySort(false);
	this->setSortingEnabled(false);
}

void SortTableView::sortBy()
{
	_sortFalg = true;
	QAction* senderAction=(QAction*)sender();
	int index=senderAction->data().toInt();

	this->setSortingEnabled(true);

//	this->sortByColumn(_currentCol);

	QHeaderView *headerGoods = this->horizontalHeader();
	headerGoods->setSortIndicator(_currentCol, Qt::AscendingOrder);
	//	headerGoods->setSortIndicatorShown(true); ///¼ýÍ··½Ïò
	emit beginSort(index);
	
}

void SortTableView::sortByLength()
{
	_sortFalg = true;
	this->setSortingEnabled(true);

	emit beginSort(1000);
}

void SortTableView::onExchangeActionClicked()
{
	if(_proxyModel->isTranspose())
	{
		_proxyModel->setIsTranspose(false);
		_proxyModel->sort(0);
		this->setSortingEnabled(false);
	}
	else
	{
		emit setSourceModel();
		this->setModel(_proxyModel);
		_proxyModel->setIsTranspose(true);
		this->setSortingEnabled(false);
	}
	_proxyModel->setEnableMySort(false);
	_sortFalg = false;
	resizeColumnsToContents ();
	resizeRowsToContents();
	
}

void SortTableView::setProxyModel( SortTransposeProxyModel* proxyModel )
{
	_proxyModel = proxyModel;
	connect(this, SIGNAL(beginSort(int)), _proxyModel, SLOT(updateComponent(int)));
}

void SortTableView::contextMenuRequest(QPoint p)
{
	QPoint newPoint ;
	newPoint.setX(p.x()+this->verticalHeader()->width());
	newPoint.setY(p.y()+this->horizontalHeader()->height());
	QMenu menu;
	QAction* ac = menu.addAction("Copy to clipboard");
	connect(ac,SIGNAL(triggered()),this,SLOT(copyStringToClipboard()));
	menu.exec(mapToGlobal(newPoint));
}

void SortTableView::copyStringToClipboard()
{
	QList<QModelIndex> list = this->selectionModel()->selectedIndexes();
	if(list.isEmpty())
	{
		QMessageBox::warning(this,"Warning","Selected nothing!");
		return;
	}
	QString str;
	QTextStream stream(&str);
	int lastRow = -1;
	bool first=true;
	QSet<int> rowSet ;
	foreach(QModelIndex index,list)
		rowSet.insert(index.row());

	foreach(int r,rowSet)
	{
		foreach(QModelIndex index,list)
		{
			if(r != index.row())
				continue;
			
			stream<<index.data(Qt::DisplayRole).toString();
			stream<<"\t";
		}

		stream<<"\n";
	}
	
	QClipboard * clipboard = QApplication::clipboard();
	clipboard->setText(str);
}



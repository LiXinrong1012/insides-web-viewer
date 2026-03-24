#include "testsorttable.h"

#include "originaldatamodel.h"
#include "proxydatamodel.h"

#include <QtGui>

ProxyDataModel* gProxyDataModel=NULL;

testSortTable::testSortTable(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);

	OriginalDataModel* orignalDataModel=new OriginalDataModel(this);

	ProxyDataModel* proxyDataModel=new ProxyDataModel(this,orignalDataModel);
	gProxyDataModel=proxyDataModel;


	ui.tableView->setModel(proxyDataModel);

		
	ui.tableView->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.tableView->horizontalHeader(),SIGNAL(customContextMenuRequested(const QPoint&)),
		this,SLOT(onContextMenu(const QPoint&)));

	ui.tableView->setSortingEnabled(true);
}

testSortTable::~testSortTable()
{

}

void testSortTable::onContextMenu(const QPoint & pos)
{
	int sectionIndex=ui.tableView->horizontalHeader()->logicalIndexAt(pos);
	
	QMenu menu;
	QAction* a1=menu.addAction(QString("Sort by %1").arg(sectionIndex));
	connect(a1,SIGNAL(triggered()),gProxyDataModel,SLOT(sortBy()));
	QCursor cursor;
	menu.exec(cursor.pos());

}

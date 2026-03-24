#include "testtreeviewfilter.h"

#include "proxyfiltermodel.h"

testTreeViewFilter::testTreeViewFilter(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	QStandardItemModel *model = new QStandardItemModel(5, 1, parent);
	_model=model;
	for( int r=0; r<5; r++ ) 
	{
		QStandardItem *item = new QStandardItem( QString("Row:%0").arg(r));

		for( int i=0; i<3; i++ )
		{
			QStandardItem *child = new QStandardItem( QString("Item %0").arg(i) );
			child->setEditable( false );
			item->appendRow( child );
		}

		model->setItem(r, 0, item);
	}

	model->setHorizontalHeaderItem( 0, new QStandardItem( "Column 1" ) );

	_proxy = new ProxyFilterModel(this);
	_proxy->setDynamicSortFilter(true);
	_proxy->setSourceModel(_model);

	connect(ui.txtFilter, SIGNAL(textChanged(QString)),
		this, SLOT(filterChanged()));

	ui.treeView->setModel(_proxy);
	ui.tableView->setModel(_model);
}

testTreeViewFilter::~testTreeViewFilter()
{

}

void testTreeViewFilter::filterChanged()
{
	QRegExp::PatternSyntax syntax = QRegExp::RegExp;

	Qt::CaseSensitivity caseSensitivity = Qt::CaseInsensitive;
	//QString strPattern = "^" + ui.txtFilter->text();
	QString strPattern =ui.txtFilter->text();
	QRegExp regExp(strPattern, caseSensitivity);

	_proxy->setFilterRegExp(regExp);
}

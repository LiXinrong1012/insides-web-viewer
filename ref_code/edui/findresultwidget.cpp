#include "findresultwidget.h"

FindResultWidget::FindResultWidget(QWidget *parent)
	: QListWidget(parent)
{
	connect(this,SIGNAL(itemDoubleClicked(QListWidgetItem*)),
		this,SLOT(onItemClicked()));
}

FindResultWidget::~FindResultWidget()
{
}

void FindResultWidget::onItemClicked()
{
	int row=currentRow();

	int n=this->count();
	if(row==0 || row==n-1)
		return;

	emit resultItemClicked(_results[row-1]);
}

void FindResultWidget::addResultItem( const FindResultItem& resultItem )
{
	_results.push_back(resultItem);

	QString lineText=QString("%1(%2): %3").arg(resultItem.fileName).arg(resultItem.lineFrom).arg(resultItem.text);
	addItem(lineText);
}

void FindResultWidget::addEnd( int fileCount,int allFileCount )
{
	// Format: Matching lines: 130    Matching files: 29    Total files searched: 164
	addItem(QString("%1 %2   %3 %4   %5 %6").
		arg(tr("Matching lines: ")).
		arg(_results.size()).
		arg(tr("Matching files: ")).
		arg(fileCount).
		arg(tr("Total files searched:")).
		arg(allFileCount));
}

void FindResultWidget::addFirst( const QString& searchText )
{
	clear();
	_results.clear();
	addItem(QString("%1 \"%2\" %3").arg(tr("Find")).arg(searchText).arg(tr("in files:")));
}

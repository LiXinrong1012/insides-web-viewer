#include "interactivetableview.h"
#include "interactivetablemodel.h"
#include "precore/precore_data.h"
#include "precore/projectselector.h"
#include "precore/IResultItem.h"

#include <QtGui>

InteractiveTableView::InteractiveTableView(QWidget *parent)
	: QTableView(parent)
{
	myResultDocument()->attachListener(this);

	horizontalHeader()->setMovable(true);


}

InteractiveTableView::~InteractiveTableView()
{
	myResultDocument()->disattachListener(this);
}

void InteractiveTableView::onResultCurrentFrameChanged()
{
	QAbstractItemModel* m=model();
	if(m){
		InteractiveTableModel* interModel=static_cast<InteractiveTableModel*>(m);
		interModel->resetLayout();
	}
}

void InteractiveTableView::onNewDataAdded()
{
	resizeColumnsToContents();
}

void InteractiveTableView::onSelectionChanged()
{
	//InteractiveTableModel* myModel=(InteractiveTableModel*)model();
	//if(!myModel)
	//	return;

	//if((myModel->getReulstType()!=TDY_PRE_CATE_FEMPART) || (myModel->getSectionIndex()==0) )
	//	return;

	//SelectionNodeElem selectionNodeElem;
	//IResultItem* resultItem=myModel->getResultItem();
	//QModelIndexList selection=selectionModel()->selectedRows();
	//foreach(QModelIndex index,selection){
	//	selectionNodeElem.indices.push_back(index.row());
	//}
	//selectionNodeElem.item=resultItem->connectedItem();
	//selectionNodeElem.resultItem=resultItem;
	//if(myModel->getSectionIndex()==1)
	//	myProjectSelector()->notifySetSelectionNodes(selectionNodeElem);
	//else
	//	myProjectSelector()->notifySetSelectionElements(selectionNodeElem);

}

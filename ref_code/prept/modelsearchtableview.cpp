#include "modelsearchtableview.h"
#include "modelsearchtablemodel.h"

#include <QHeaderView>

#include "precore/modeldocument.h"
#include "precore/projectselector.h"



ModelSearchTableView::ModelSearchTableView(QWidget *parent)
	: QTableView(parent)
{
	setModel(new ModelSearchTableModel(this));

	this->verticalHeader()->setVisible(false);
	this->setSortingEnabled(true);
	verticalHeader()->setDefaultSectionSize(16);

	ModelSearchTableModel* comModel=(ModelSearchTableModel*)this->model();
	connect(comModel,SIGNAL(structChanged()),this,SLOT(onStructChanged()));

	setSelectionBehavior(SelectRows);
	setSelectionMode(ExtendedSelection);

	connect(this,SIGNAL(clicked(const QModelIndex&)),
		this, SLOT(onClicked(const QModelIndex&)));

	horizontalHeader()->setMovable(true);
	connect(this->horizontalHeader(),SIGNAL(sectionResized(int,int, int)),
		this,SLOT(onColumnSizeChanged(int,int,int)));

	QItemSelectionModel* interModel=this->selectionModel();
	connect(interModel, SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), 
		this, SLOT(slot_SelectionChanged(const QItemSelection &, const QItemSelection &)));

	connect(interModel, SIGNAL(currentChanged ( const QModelIndex&, const QModelIndex&)), 
		this, SLOT(slot_CurrentChanged(const QModelIndex &, const QModelIndex &)));


	myProjectSelector()->attachSupplier(this);
}

ModelSearchTableView::~ModelSearchTableView()
{
	myProjectSelector()->disattachSupplier(this);
}

void ModelSearchTableView::onStructChanged()
{
	ModelSearchTableModel* model=(ModelSearchTableModel*)this->model();
	if(!model)
		return;

	updateHeaderWidth(this,model,model);
	updateHeaderDelegate(this,model,model);
}

void ModelSearchTableView::ss_onSetSelection_protected( const QList<BaseItem*>& selection )
{

}

void ModelSearchTableView::ss_onSetClicked_projected( BaseItem* item )
{
	/*to do, Jerry,2014,3,8*/
}

void ModelSearchTableView::onClicked( const QModelIndex & index )
{
	if(index.isValid()){
		int row=index.row();
		ModelSearchTableModel* aModel=(ModelSearchTableModel*)this->model();
		ss_notifySetClicked(aModel->getItem(row));
	}
}

void ModelSearchTableView::onColumnSizeChanged( int index,int oldSize,int newSize )
{

}

void ModelSearchTableView::slot_SelectionChanged( const QItemSelection &, const QItemSelection & )
{
	QModelIndexList selectionIndexlist=this->selectedIndexes();
	ModelSearchTableModel* aModel=(ModelSearchTableModel*)this->model();
	QList<BaseItem*> emitItems;
	foreach(QModelIndex index,selectionIndexlist){
		BaseItem* item=aModel->getItem(index.row());
		if(item)
			emitItems.push_back(item);
	}

	ss_notifySetSelection(emitItems);
}

void ModelSearchTableView::slot_CurrentChanged( const QModelIndex & current, const QModelIndex & previous )
{

}

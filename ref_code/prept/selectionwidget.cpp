#include "selectionwidget.h"
#include "ui_selectionwidget.h"

#include "precore/BaseItem.h"
#include "precore/projectselector.h"
#include "precore/FEMPartBaseItem.h"

SelectionWidget::SelectionWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::SelectionWidget();
	ui->setupUi(this);

	myProjectSelector()->attachSupplier(this);
}

SelectionWidget::~SelectionWidget()
{
	delete ui;

	myProjectSelector()->disattachSupplier(this);
}

void SelectionWidget::ss_onSetSelection_protected( const BaseItemSelection& )
{

}

void SelectionWidget::ss_onSetClicked_projected( BaseItem* item )
{
	clear();
	if(item){
		ui->selectionInfo->addItem(item->getKeyName());
	}
}

void SelectionWidget::ss_onSetSelectionNodes_protected( const SelectionNodeElem& selection )
{
	clear();
	if(selection.item && selection.indices.size()>0){
		FEMPartBaseItem* femPartBaseItem=(FEMPartBaseItem*)selection.item;

		ui->selectionInfo->addItem(femPartBaseItem->getKeyName());
		PP_NODE* nodes=femPartBaseItem->getFEMPart()->m_Mesh.GetNode();

		foreach(int nodeIndex,selection.indices){
			if(nodeIndex<femPartBaseItem->getFEMPart()->m_Mesh.GetNodeCnt())
				ui->selectionInfo->addItem(QString("Node: %1").arg(nodes[nodeIndex].NID));
		}
	}
}

void SelectionWidget::ss_onSetSelectionElements_protected( const SelectionNodeElem& selection )
{
	clear();
	if(selection.item && selection.indices.size()>0){
		FEMPartBaseItem* femPartBaseItem=(FEMPartBaseItem*)selection.item;
		int elementCnt=femPartBaseItem->getFEMPart()->m_Mesh.GetElementCnt();
		PP_ELEMENT* elements=femPartBaseItem->getFEMPart()->m_Mesh.GetElement();

		ui->selectionInfo->addItem(femPartBaseItem->getKeyName());
		foreach(int nodeIndex,selection.indices){
			if(nodeIndex<elementCnt)
				ui->selectionInfo->addItem(QString("Element: %1").arg(elements[nodeIndex].EID));
		}
	}
}

void SelectionWidget::clear()
{
	ui->selectionInfo->clear();
}


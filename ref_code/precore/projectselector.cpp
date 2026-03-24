#include "projectselector.h"
#include "ISelectionSupplier.h"

#define PROJECT_SELECTION_BEGIN_NOTIFY 	if(_isOperating) return;else _isOperating=true;
#define PROJECT_SELECTION_END_NOTIFY 	_isOperating=false;


namespace INSIDES
{

ProjectSelector::ProjectSelector()
	:_clickedItem(NULL)
	,_isOperating(false)
	,_type(ST_Entity)
{
}

ProjectSelector::~ProjectSelector()
{

}

ProjectSelector* ProjectSelector::instance()
{
	static ProjectSelector* _instance=NULL;
	if(!_instance)
		_instance=new ProjectSelector();
	return _instance;
}



BaseItem* ProjectSelector::getClicked() const
{
	return _clickedItem;
}

void ProjectSelector::notifySetSelection( const BaseItemSelection& selection, ISelectionSupplier* sendor )
{
	PROJECT_SELECTION_BEGIN_NOTIFY

	_selection=selection;
	foreach(ISelectionSupplier* supplier,_selectionSupplierList)
	{
		if(supplier!=sendor)
			supplier->ss_onSetSelection(_selection);
	}

	PROJECT_SELECTION_END_NOTIFY
}

void ProjectSelector::notifySetClickedItem( BaseItem* item,ISelectionSupplier* sendor/*=NULL*/ )
{
	PROJECT_SELECTION_BEGIN_NOTIFY
	_clickedItem=item;
	foreach(ISelectionSupplier* supplier,_selectionSupplierList)
	{
		if(supplier!=sendor)
			supplier->ss_onSetClicked(_clickedItem);
	}
	PROJECT_SELECTION_END_NOTIFY
}

bool ProjectSelector::attachSupplier( ISelectionSupplier* supplier )
{
	_selectionSupplierList.removeOne(supplier);
	_selectionSupplierList.push_back(supplier);
	supplier->_subject=this;
	return true;
}

bool ProjectSelector::disattachSupplier( ISelectionSupplier* supplier )
{
	_selectionSupplierList.removeOne(supplier);
	return true;
}

void ProjectSelector::clear()
{
	_selection.clear();
	_clickedItem=NULL;
}

const QList<BaseItem*>& ProjectSelector::getSelection() const
{
	return _selection;
}

void ProjectSelector::notifySetSelectionNodes(const SelectionNodeElem& selection ,ISelectionSupplier* sender)
{
	PROJECT_SELECTION_BEGIN_NOTIFY
	_selectionNodes=selection;
	foreach(ISelectionSupplier* supplier,_selectionSupplierList)
	{
		if(supplier!=sender)
			supplier->ss_onSetSelectionNodes(_selectionNodes);
	}
	PROJECT_SELECTION_END_NOTIFY
}

void ProjectSelector::notifySetSelectionElements(const SelectionNodeElem& selection,ISelectionSupplier* sendor )
{
	PROJECT_SELECTION_BEGIN_NOTIFY
	_selectionElements=selection;
	foreach(ISelectionSupplier* supplier,_selectionSupplierList)
	{
		if(supplier!=sendor)
			supplier->ss_onSetSelectionElements(_selectionElements);
	}
	PROJECT_SELECTION_END_NOTIFY
}

}

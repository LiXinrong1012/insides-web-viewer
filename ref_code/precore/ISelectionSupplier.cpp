#include "ISelectionSupplier.h"
#include "projectselector.h"


namespace INSIDES
{

ISelectionSupplier::ISelectionSupplier(void)
	:_subject(NULL)
	,_isOperating(false)
{
	static int id=1;
	setSupplierName(QString("Supplier_%1").arg(id++));
}


ISelectionSupplier::~ISelectionSupplier(void)
{
	if(_subject)
		_subject->disattachSupplier(this);
}



void ISelectionSupplier::ss_notifySetSelection( const BaseItemSelection& selection )
{
	if(_isOperating)
		return;

	// notify all other suppliers
	_subject->notifySetSelection(selection,this);

}
void ISelectionSupplier::ss_notifySetClicked( BaseItem* item )
{
	if(_isOperating)
		return;

	// notify all other suppliers
	_subject->notifySetClickedItem(item,this);
}
void ISelectionSupplier::ss_onSetSelection( const BaseItemSelection& selection )
{
	if(_isOperating)
		return;
	_isOperating=true;

	ss_onSetSelection_protected(selection);

	_isOperating=false;
}
void ISelectionSupplier::ss_onSetClicked( BaseItem* item )
{
	if(_isOperating)
		return;
	_isOperating=true;

	ss_onSetClicked_projected(item);

	_isOperating=false;
}

void ISelectionSupplier::ss_onSetSelectionNodes( const SelectionNodeElem& selection )
{
	if(_isOperating)
		return;
	_isOperating=true;

	ss_onSetSelectionNodes_protected(selection);

	_isOperating=false;
}

void ISelectionSupplier::ss_onSetSelectionElements( const SelectionNodeElem& selection )
{
	if(_isOperating)
		return;
	_isOperating=true;

	ss_onSetSelectionElements_protected(selection);

	_isOperating=false;
}

void ISelectionSupplier::ss_notifySetSelectionNodes( const SelectionNodeElem& selection )
{
	if(_isOperating) return;

	// notify all other suppliers
	_subject->notifySetSelectionNodes(selection,this);

}

void ISelectionSupplier::ss_notifySetSelectionElements( const SelectionNodeElem& selection )
{
	if(_isOperating) return;

	// notify all other suppliers
	_subject->notifySetSelectionElements(selection,this);

}


}
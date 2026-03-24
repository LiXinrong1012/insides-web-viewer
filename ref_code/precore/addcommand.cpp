#include "addcommand.h"

#include "modeldocument.h"
#include "UAPI_.h"

namespace INSIDES
{


AddCommand::AddCommand( ModelDocument* doc,BaseItem* parentItem,BaseItem* item,QUndoCommand* parent/*=0*/ )
	: QUndoCommand(parent)
	,_doc(doc)
	,_parentItem(parentItem)
	,_item(item)
	,_needDelete(true)
{
	setText(QObject::tr("Insert item %1")
		.arg(item->getKeyName()));
}

AddCommand::~AddCommand()
{
	if(_needDelete)
		delete _item;
}

void AddCommand::redo()
{
	_doc->insertChild(_parentItem,_item);
	_needDelete=false;
	_doc->update();
}

void AddCommand::undo()
{
	_doc->remove(_item,false);
	_needDelete=true;
	_doc->update();
}


}
#include "removecommand.h"
#include "precore/modeldocument.h"
#include "precore/BaseItem.h"
#include "precore/UAPI_.h"


namespace INSIDES
{

RemoveCommand::RemoveCommand(ModelDocument* doc,BaseItem* item)
	: QUndoCommand()
	,_doc(doc)
	,_item(item)
	,_parent(item->getParent())
	,_needDelete(false)
{
	setText(QObject::tr("Remove item: %1").arg(item->getKeyName()));
}

RemoveCommand::~RemoveCommand()
{
	if(_needDelete)
		PREI_Delete_Item(_item);
}

void RemoveCommand::redo()
{
	_doc->remove(_item,false);
	_needDelete=true;
	_doc->update();
}

void RemoveCommand::undo()
{
	_doc->insertChild(_parent,_item);
	_needDelete=false;
	_doc->update();
}

}
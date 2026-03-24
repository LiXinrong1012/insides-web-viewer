#include "modifycommand.h"
#include "precore/modeldocument.h"
#include "precore/BaseItem.h"
#include "precore/UAPI_.h"

namespace INSIDES
{

ModifyCommand::ModifyCommand( ModelDocument* doc,BaseItem* src,BaseItem* dst )
	:QUndoCommand()
	,_doc(doc)
	,_src(src)
	,_dst(dst)
{
	_oldDst=dst->clone();
	setText(QObject::tr("Modify item: %1").arg(dst->getKeyName()));
}

ModifyCommand::~ModifyCommand()
{
	PREI_Delete_Item(_oldDst);
	PREI_Delete_Item(_src);
}

void ModifyCommand::redo()
{
	_doc->modify(_src,_dst);
}

void ModifyCommand::undo()
{
	_doc->modify(_oldDst,_dst);
}

}
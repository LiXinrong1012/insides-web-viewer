#include "UAPI.h"
#include "precore/modeldocument.h"
#include "precore/BaseItem.h"
#include "precore/Command.h"
#include "UAPI_.h"

namespace INSIDES
{

void PRE_Add_Item( ModelDocument* doc,BaseItem* parent,BaseItem* item )
{
	if(doc->getUndoable())
	{
		AddCommand* cmd=new AddCommand(doc,parent,item);
		doc->pushCommand(cmd);
	}
	else{
		doc->insertChild(parent,item);
	}
}

void PRECORE_EXPORT PRE_Remove_Item( ModelDocument* doc, BaseItem* item )
{
	if(doc->getUndoable())
	{
		RemoveCommand* cmd=new RemoveCommand(doc,item);
		doc->pushCommand(cmd);
	}
	else{
		doc->remove(item,true);
	}
}

void PRECORE_EXPORT PRE_Modify_Item( ModelDocument* doc,BaseItem* src,BaseItem* dst )
{
	if(doc->getUndoable())
	{
		ModifyCommand* cmd=new ModifyCommand(doc,src,dst);
		doc->pushCommand(cmd);
	}
	else{
		doc->modify(src,dst);
	}

}

}

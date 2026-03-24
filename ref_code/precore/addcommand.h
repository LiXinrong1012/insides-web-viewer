#ifndef ADDCOMMAND_H
#define ADDCOMMAND_H

#include "precore/precore_global.h"
#include <QtGui/QUndoCommand> 

namespace INSIDES
{

class ModelDocument;
class BaseItem;

class PRECORE_EXPORT AddCommand : public QUndoCommand
{
public:
	AddCommand(ModelDocument* doc,BaseItem* parentItem,BaseItem* item,QUndoCommand* parent=0);
	~AddCommand();

	void redo();
	void undo();

private:
	ModelDocument*	_doc;
	BaseItem*		_parentItem;
	BaseItem*		_item;
	bool			_needDelete;
	
};

}

#endif // ADDCOMMAND_H

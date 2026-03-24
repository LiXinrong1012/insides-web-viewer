#ifndef REMOVECOMMAND_H
#define REMOVECOMMAND_H

#include <QUndoCommand>

namespace INSIDES
{

class ModelDocument;
class BaseItem;

class RemoveCommand : public QUndoCommand
{
public:
	RemoveCommand(ModelDocument* doc,BaseItem* item);
	~RemoveCommand();

	void redo();
	void undo();

private:
	ModelDocument* _doc;
	BaseItem*	_item;
	BaseItem*	_parent;
	bool		_needDelete;
};

}


#endif // REMOVECOMMAND_H

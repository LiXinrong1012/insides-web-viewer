#ifndef MODIFYCOMMAND_H
#define MODIFYCOMMAND_H

#include <QUndoCommand>

namespace INSIDES
{

class ModelDocument;
class BaseItem;

class ModifyCommand : public QUndoCommand
{
public:
	ModifyCommand(ModelDocument* doc,BaseItem* src,BaseItem* dst);
	~ModifyCommand();

	void redo();
	void undo();

private:
	ModelDocument* _doc;
	BaseItem*	_src;
	BaseItem*	_oldDst;
	BaseItem*	_dst;
	bool		_needDelete;
};

}

#endif // MODIFYCOMMAND_H

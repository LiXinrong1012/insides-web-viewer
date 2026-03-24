#ifndef PROJECTSELECTOR_H
#define PROJECTSELECTOR_H

#include "precore/precore_global.h"
#include <QObject>
#include <vector>
#include <QList>
#include <QScopedPointer>
#include "precore/ISelectionSupplier.h"


namespace INSIDES
{

class BaseItem;

class ProjectSelectorPrivate;
class ISelectionSupplier;

typedef BaseItem ProjectItemClass;

typedef QList<BaseItem*> BaseItemSelection;
/*!
*	统一的选择条目接口。
*	@author Jerry He
*	@date 2014.2.19
*/
class PRECORE_EXPORT ProjectSelector
{
public:
	enum SelectionType{ST_Entity,ST_Node,ST_Element};

	static ProjectSelector* instance();
	void clear();

	SelectionType getSelectionType()const{return _type;}
	void setSelectionType(SelectionType t){_type=t;}

	const BaseItemSelection& getSelection()const;
	BaseItem* getClicked()const;
	const SelectionNodeElem& getSelectionNodes()const{return _selectionNodes;}
	const SelectionNodeElem& getSelectionElements()const{return _selectionElements;}

	bool attachSupplier(ISelectionSupplier* supplier);
	bool disattachSupplier(ISelectionSupplier* supplier);

	void notifySetSelection(const BaseItemSelection& selection,ISelectionSupplier* sendor=NULL);
	void notifySetClickedItem(BaseItem* item,ISelectionSupplier* sendor=NULL);
	void notifySetSelectionNodes(const SelectionNodeElem& selection,ISelectionSupplier* sendor=NULL);
	void notifySetSelectionElements(const SelectionNodeElem& selection,ISelectionSupplier* sendor=NULL);

	bool isOperating()const{return _isOperating;}

private:
	typedef QList<ISelectionSupplier*> SelectionSupplierList;

	ProjectSelector();
	~ProjectSelector();

	BaseItemSelection	_selection;
	BaseItem*			_clickedItem;
	SelectionNodeElem	_selectionNodes;
	SelectionNodeElem	_selectionElements;


	bool				_isOperating;
	SelectionType		_type;
	SelectionSupplierList	_selectionSupplierList;
};

inline ProjectSelector* myProjectSelector(){return ProjectSelector::instance();}

}


#endif // PROJECTSELECTOR_H
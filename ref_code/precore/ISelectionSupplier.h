#pragma once

#include "precore/precore_global.h"
#include <QList>
#include <QVector>
#include <QString>

namespace INSIDES
{
class ProjectSelector;
class BaseItem;
class IResultItem;

typedef QList<BaseItem*> BaseItemSelection;

struct SelectionNodeElem
{
	BaseItem*	item;
	IResultItem* resultItem;
	QVector<int>	indices;

	SelectionNodeElem():item(NULL),resultItem(NULL){}
};

class PRECORE_EXPORT ISelectionSupplier
{
public:
	ISelectionSupplier(void);
	~ISelectionSupplier(void);

	/*! After the selection have changed, this function can be used to notify all the other ISelectionSupppliers. */
	void ss_notifySetSelection(const BaseItemSelection& selection);
	void ss_notifySetClicked(BaseItem* item);
	void ss_notifySetSelectionNodes(const SelectionNodeElem& selection);
	void ss_notifySetSelectionElements(const SelectionNodeElem& selection);

	ProjectSelector* getSubject(){return _subject;}

protected:
	virtual void ss_onSetSelection_protected(const BaseItemSelection& ){}
	virtual void ss_onSetClicked_projected(BaseItem* item){}
	virtual void ss_onSetSelectionNodes_protected(const SelectionNodeElem& selection){}
	virtual void ss_onSetSelectionElements_protected(const SelectionNodeElem& selection){}

	QString getSupplierName()const{return _name;}
	void setSupplierName(const QString& name){_name=name;}
private:
	/*! update selection .*/
	void ss_onSetSelection(const BaseItemSelection& selection);
	void ss_onSetClicked(BaseItem* item);
	void ss_onSetSelectionNodes(const SelectionNodeElem& selection);
	void ss_onSetSelectionElements(const SelectionNodeElem& selection);

	ProjectSelector* _subject;
	QString			_name;
	bool			_isOperating;

	friend class ProjectSelector;
};

}
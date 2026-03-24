#ifndef SELECTIONWIDGET_H
#define SELECTIONWIDGET_H

#include <QWidget>
namespace Ui {class SelectionWidget;};


#include "precore/ISelectionSupplier.h"

using namespace INSIDES;

class SelectionWidget : public QWidget, public ISelectionSupplier
{
	Q_OBJECT

public:
	SelectionWidget(QWidget *parent = 0);
	~SelectionWidget();

protected:
	virtual void ss_onSetSelection_protected(const BaseItemSelection& );
	virtual void ss_onSetClicked_projected(BaseItem* item);
	virtual void ss_onSetSelectionNodes_protected(const SelectionNodeElem& selection);
	virtual void ss_onSetSelectionElements_protected(const SelectionNodeElem& selection);

private:
	Ui::SelectionWidget *ui;

	void clear();
};

#endif // SELECTIONWIDGET_H

#ifndef RESULTSELECTORWIDGET_H
#define RESULTSELECTORWIDGET_H

#include "prev3d/prev3d_global.h"
#include "precore/ISelectionSupplier.h"

#include <QWidget>

namespace Ui {class ResultSelectorWidget;};

namespace INSIDES{
	class IResultItem;
}

using namespace INSIDES;

class PREV3D_EXPORT ResultSelectorWidget : public QWidget, public ISelectionSupplier
{
	Q_OBJECT

public:
	ResultSelectorWidget(QWidget *parent = 0);
	~ResultSelectorWidget();

signals:
	void selectionIndexChanged();

	public slots:
		void onOK();
		void onResultsImported();


protected slots:
	void onCurrentItemChanged();
	void oncbSelectionChanged();


protected:
	virtual void ss_onSetClicked_projected(BaseItem* item);
	virtual void ss_onSetSelection_protected(const BaseItemSelection& );

	virtual void protected_onOK();

	IResultItem* getCurrentBaseItem();

	Ui::ResultSelectorWidget *ui;
	int			_lastSubIndex;
	bool		_disableSubSection;

};

#endif // RESULTSELECTORWIDGET_H

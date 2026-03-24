#ifndef RESULTSELECTORWIDGET1243d_H
#define RESULTSELECTORWIDGET1243d_H

#include "precore/ISelectionSupplier.h"
#include "precore/ResultDocument.h"

#include <QWidget>

using namespace INSIDES;
namespace Ui {class ResultSelectorWidget;};

namespace INSIDES{
	class IResultItem;
	class IResultListener;
}
namespace Base{class View;}
struct TableItemTitle
{
	QString itemName;
	int secIndex;

	TableItemTitle():secIndex(-1){}
};

class ResultSelectorWidget : public QWidget,public IResultListener
{
	Q_OBJECT

public:
	ResultSelectorWidget(QWidget *parent = 0);
	~ResultSelectorWidget();

	void setParentView(Base::View* view){_parentView=view;}
	void emit_itemAdding();
	void setCurrentBaseItem( BaseItem* item );

signals:
	void itemAdding(TableItemTitle tableItem);
	void notifyUpdate(TableItemTitle tableItem);
	void resultDeleted();


protected slots:
	void onCurrentItemChanged();
	void oncbSelectionChanged();


private:
	void updateItems();
	void updateSections();

	void clearAll();


protected:

	void res_ResultsLoaded(IResults* results);
	void res_ResultsDeleted();


	IResultItem* getCurrentBaseItem();
	/// 得到当前选择条目的名字
	QString getCurrentItemName()const;
	TableItemTitle getTableItemTitle();

	Ui::ResultSelectorWidget *ui;
	Base::View*			_parentView;
	ResultItemSelect	_resultItemSelect;

	bool		_IsOperatingUI;


};

#endif // RESULTSELECTORWIDGET1243d_H

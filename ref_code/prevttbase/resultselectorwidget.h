#ifndef RESULTSELECTORWIDGET_H
#define RESULTSELECTORWIDGET_H

#include "precore/ISelectionSupplier.h"
#include "precore/ResultDocument.h"

#include <QWidget>

using namespace INSIDES;

namespace Ui {class ResultSelectorWidget;};
namespace Base{class View;}

namespace INSIDES{
class IResultItem;
}

/*!
	@brief   用于存储表格属性
	@date    2015.6.30
	@author  Jerry
*/
struct TableItemTitle
{
	///条目名
	QString itemName;

	///索引
	int secIndex;

	TableItemTitle():secIndex(-1){}
};


/*!
	@brief   结果选择界面
	@date    2015.6.30
	@author  Jerry
*/
class ResultSelectorWidget : public QWidget, public ISelectionSupplier, public IResultListener
{
	Q_OBJECT

public:
	ResultSelectorWidget(QWidget *parent = 0);
	~ResultSelectorWidget();

	///设置父类view
	void setParentView(Base::View* view){_parentView=view;}

	///用于发送条目添加信号
	void emit_itemAdding();

	///设置当前的基类条目
	void setCurrentBaseItem( BaseItem* item );

signals:
	///需要添加条目时发出
	void itemAdding(TableItemTitle tableItem);

	///需要通知更新时发出
	void notifyUpdate(TableItemTitle tableItem);

	///结果删除后发出
	void resultDeleted();

protected slots:
	///当当前条目改变时调用
	void onCurrentItemChanged();

	///当两个下拉框有变动时触发
	void oncbSelectionChanged();

protected:
	///请求结果重新加载
	void res_ResultsLoaded(IResults* results);

	///请求结果删除
	void res_ResultsDeleted();

	///设置item被点击
	virtual void ss_onSetClicked_projected(BaseItem* item);

	///选择选中的第一个
	virtual void ss_onSetSelection_protected(const BaseItemSelection& );

	///获得当前基类结果条目
	IResultItem* getCurrentBaseItem();

	/// 得到当前选择条目的名字
	QString getCurrentItemName()const;
	
	///获得表格条目数据结构对象
	TableItemTitle getTableItemTitle();

private:
	///更新全部条目
	void updateItems();

	///更新选择
	void updateSections();

	///清除所有
	void clearAll();

private:
	Ui::ResultSelectorWidget *ui;

	///父视图指针
	Base::View*			_parentView;

	///指示选择的一个结果条目
	ResultItemSelect	_resultItemSelect;

	///是否在更新UI
	bool		_IsOperatingUI;
};

#endif // RESULTSELECTORWIDGET_H

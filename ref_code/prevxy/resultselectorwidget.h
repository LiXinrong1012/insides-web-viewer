#ifndef RESULTSELECTORWIDGET_H
#define RESULTSELECTORWIDGET_H

#include "precore/ISelectionSupplier.h"
#include "precore/ResultDocument.h"

#include "xyitemtitle.h"

#include <QWidget>

namespace Ui {class ResultSelectorWidget;};

namespace INSIDES{
	class IResultItem;
}

namespace Base{class View;}

class QComboBox;
class QCPCurve;
class AddCustomCurveDialog;

/*!
	@brief   结果选择界面
	@date    2015.7.3
	@author  Jerry
*/
class ResultSelectorWidget : public QWidget, public INSIDES::ISelectionSupplier, public INSIDES::IResultListener
{
	Q_OBJECT

public:
	ResultSelectorWidget(QWidget *parent = 0);
	~ResultSelectorWidget();

	///设置所属上级view
	void setParentView(Base::View* view){_parentView=view;}
	
	///获得x坐标的内容
	void xContent(XYItemTitle& title);

	///获得y坐标的内容
	void yContent(XYItemTitle& title);

signals:
	///选择索引项改变时发出
	void selectionIndexChanged();

	///有条目增加时发出
	void itemAdding(XYItemTitle curveTitle);

	///新的结果加载后调用
	void newResultLoaded();

public slots:
	///当确认按钮点击时调用
	void onOK();

	///当复选框点击时调用
	void setCheckBoxChecked();

protected slots:
	///当当前条目改变时调用
	void onCurrentItemChanged();

	///当当前第一选择栏的选择项改变时调用
	void oncbSelectionChanged();

	///当当前第二选择栏的选择项改变时调用
	void onSubsectionChanged();

	///当当前y条目改变时调用
	void onCurrentYItemChanged();

	///当自定义按钮点击时调用
	void onCustomBtnClicked();

private:
	///更新所有条目
	void updateItems();

	///更新选择项
	void updateSections();

	///更新子选择项
	void updateSubsections();

	///更新子子选择项
	void updateSubsubsections();

	///更新y选择项
	void updateYSections();
	
	///y行子选择项
	void updateYSubsections();
	
	///更新y行子子选择项
	void updateYSubsubsections();

	///更新索引状态
	void updateIndexStatus();

	///更新y行索引状态
	void updateYIndexStatus();

	///清除所有
	void clearAll();

	///设置默认名
	void setDefaultName(XYItemTitle& title);

protected:
	///请求加载结果
	void res_ResultsLoaded(INSIDES::IResults* results);

	///请求结果删除
	void res_ResultsDeleted();

	///设置点击
	virtual void ss_onSetClicked_projected(INSIDES::BaseItem* item);

	///设置选择
	virtual void ss_onSetSelection_protected(const INSIDES::BaseItemSelection& );

	///确认键点击 
	virtual void protected_onOK();

	///获得当前结果条目
	INSIDES::IResultItem* getCurrentBaseItem(QComboBox* box);

	/// 得到当前选择条目的名字
	QString getCurrentItemName(QComboBox* box)const;

private:
	Ui::ResultSelectorWidget *ui;

	///保存所属上级view
	Base::View*			_parentView;

	///选择的结果条目
	INSIDES::ResultItemSelect	_resultItemSelect;

	///是否正在操作界面
	bool		_IsOperatingUI;

	///x軕的自定义增加曲线框
	AddCustomCurveDialog*	_xCustomDialog;

	///y轴的自定义增加曲线框
	AddCustomCurveDialog*	_yCustomDialog;

};

#endif // RESULTSELECTORWIDGET_H

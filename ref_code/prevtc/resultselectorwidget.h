#ifndef RESULTSELECTORWIDGET_H
#define RESULTSELECTORWIDGET_H

#include "precore/ISelectionSupplier.h"
#include "precore/ResultDocument.h"

#include <QWidget>

namespace Ui {class ResultSelectorWidget;};

namespace INSIDES{
	class IResultItem;
}
namespace Base{class View;}

class QCPCurve;

/*!
	@brief   用于存储曲线属性的数据结构类
	@date    2015.6.29
	@author  Jerry
*/
class CurveItemTitle
{
public:
	CurveItemTitle():type(Normal),relatedPlotable(NULL){};

	enum Type{Normal=0,Custom,IsImported};

	/// 曲线类型
	Type type;	

	/// 曲线的名字
	QString name;	

	///曲线定义条目或者内容
	QString itemContent;	

	///记录具体选择的哪个条目
	int secIndex;
	int subsecIndex;
	int subsubsecIndex;
	int nodeElemIndex;

	///存储所有点的x值
	QVector<double>	xs;

	///存储所有点的y值 
	QVector<double> ys;

	///　此曲线的指针
	QCPCurve* relatedPlotable; 

	friend QDataStream& operator << (QDataStream& fout,const CurveItemTitle& item);
	friend QDataStream& operator >> (QDataStream& fin, CurveItemTitle& item);
};

QDataStream& operator << (QDataStream& fout,const CurveItemTitle& path);
QDataStream& operator >> (QDataStream& fin, CurveItemTitle& path);

/*!
	@brief   选择条目的界面
	@date    2015.6.30
	@author  Jerry
*/
class ResultSelectorWidget : public QWidget, public INSIDES::ISelectionSupplier, public INSIDES::IResultListener
{
	Q_OBJECT

public:
	ResultSelectorWidget(QWidget *parent = 0);
	~ResultSelectorWidget();

	///设置其所属view
	void setParentView(Base::View* view){_parentView=view;}

signals:
	///选择项改变时发出
	void selectionIndexChanged();

	///条目增加时发出
	void itemAdding(QVector<double>& xlist,QVector<double>& ylist, const QString& title);

	///条目增加时发出，该函数为重载
	void itemAdding(CurveItemTitle curveTitle);

	///新的结果导入时发出
	void newResultLoaded();

public slots:
	///当OK按钮被点击时调用 
	void onOK();

protected slots:
	///当前条目改变时调用
	void onCurrentItemChanged();

	///当选择项改变时调用 
	void oncbSelectionChanged();

	///当子选择项改变时调用
	void onSubsectionChanged();

private:
	///更新所有条目
	void updateItems();

	///更新第一栏条目
	void updateSections();

	///更新第二栏条目
	void updateSubsections();

	///更新第三栏条目
	void updateSubsubsections();

	///更新索引状态
	void updateIndexStatus();

	///清除所有
	void clearAll();

	///设置默认名
	void setDefaultName(CurveItemTitle& title);

protected:
	///请求结果重新载入
	void res_ResultsLoaded(INSIDES::IResults* results);

	///请求结果删除
	void res_ResultsDeleted();

	///当点击时调用
	virtual void ss_onSetClicked_projected(INSIDES::BaseItem* item);

	///当选择时调用
	virtual void ss_onSetSelection_protected(const INSIDES::BaseItemSelection& );

	///OK点击时调用 
	virtual void protected_onOK();

	///获得当前结果基条目
	INSIDES::IResultItem* getCurrentBaseItem();

	/// 得到当前选择条目的名字
	QString getCurrentItemName()const;
	
private:
	Ui::ResultSelectorWidget *ui;

	///存储其所属view
	Base::View*			_parentView;

	///结果选择的结果条目
	INSIDES::ResultItemSelect	_resultItemSelect;

	///是否正在操作UI
	bool		_IsOperatingUI;

};

#endif // RESULTSELECTORWIDGET_H

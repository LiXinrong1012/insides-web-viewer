#ifndef INTERACTIVETABLEVIEW_H
#define INTERACTIVETABLEVIEW_H

#include <QTableView>
#include "precore/ResultDocument.h"
#include "precore/ISelectionSupplier.h"
#include "precore/ModelDocument.h"
#include "precore/FlexResultItem.h"


/*!
*	代表即帧刷新数据的表格视图。
*	@author Jerry He
*	@date	2014.4.23
*/
class SortTransposeProxyModel;
using namespace INSIDES;

class SortTableView : public QTableView, public IResultListener, public ISelectionSupplier
{
	Q_OBJECT

public:
	SortTableView(QWidget *parent);
	~SortTableView();
	
	///设置代理模型
	void setProxyModel(SortTransposeProxyModel* proxyModel);

signals:
	///开始排序
	void beginSort(int com);

	///更换原来MODEL
	void setSourceModel();

	///重新设置布局
	void resetLayout();

	///选中行
	void selectRows(const QString& selectionName,int indices);

protected slots:
	///当新数据增加时调用
	void onNewDataAdded();

	///通过长度来排序
	void sortByLength();

	///排序
	void sortBy();

	///关闭排序
	void closeSort();

	///选择被点击时调用
	void onSectionClicked(int section);

	///当转换action点击时触发
	void onExchangeActionClicked();

	///响应菜单事件 
	void contextMenuRequest(QPoint p);

	///拷贝字符串到剪切板
	void copyStringToClipboard();

protected:
	/// invoked after result data has changed.
	virtual void onResultCurrentFrameChanged();

	///重写选择节点使用
	virtual void ss_onSetSelectionNodes_protected(const SelectionNodeElem& selection);

	///重写选择项使用
	virtual void ss_onSetSelectionElements_protected(const SelectionNodeElem& selection);

private slots:
	///菜单事件槽
	void onCustomContextMenuRequested ( const QPoint &pos );

private:
	///当前列
	int _currentCol;

	///排序标志
	bool _sortFalg;

	///代理model
	SortTransposeProxyModel* _proxyModel;

};
#endif // INTERACTIVETABLEVIEW_H

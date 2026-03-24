#ifndef MODELTREEWIDGET_H
#define MODELTREEWIDGET_H

#include <QWidget>
#include <QTreeView>
namespace Ui {class ModelTreeWidget;};

class ModelTreeView;
class ModelTreeSearchWidget;

namespace INSIDES{
	class BaseItem;
}

using INSIDES::BaseItem;

/*!
*	@breif 代表整个模型树窗口。
*	支持搜索、条目树结构显示、按钮。
*	@author	Jerry He
*	@date	2014.9.30
*/
class ModelTreeWidget : public QWidget
{
	Q_OBJECT

public:
	ModelTreeWidget(QWidget *parent = 0);
	~ModelTreeWidget();

	QTreeView* getTreeView();

signals:
	void showSearchOptionClicked();
	void searchOptionChanged(const QString& keyword);

protected slots:
	void updateSearchResult(const QList<BaseItem*>& vec);

	/// 排序方式改变
	void onSort();

	/// 显示表头显示元素对话框
	void onShowHeaderSettings();

	/// 树表头宽度改变时，搜索表的宽度跟着改变
	void onTreeSectionResized(int logicalIndex,int oldSize,int newSize);

private:
	Ui::ModelTreeWidget *ui;
};

#endif // MODELTREEWIDGET_H

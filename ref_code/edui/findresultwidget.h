#ifndef FINDRESULTWIDGET_H
#define FINDRESULTWIDGET_H

#include <QListWidget>

/*!
	@brief  查找结果单个条目对应结构体
	@date   2015.6.19
	@author Jerry
*/
class FindResultItem
{
public:
	QString fileName;
	int	lineFrom;
	int indexFrom;
	int lineTo;
	int indexTo;
	QString text;
};

/*!
	@brief   用于显示查找结果的listWidget
	@date    2015.6.19
	@author  Jerry
*/
class FindResultWidget : public QListWidget
{
	Q_OBJECT

public:
	FindResultWidget(QWidget *parent);
	~FindResultWidget();

	///相当于查找结果列表的表头
	void addFirst(const QString& searchText);

	///相当于查找结果列表的结尾
	void addEnd(int fileCount,int allFileCount);

public slots:
	///添加查找结果条目
	void addResultItem(const FindResultItem& resultItem);

signals:
	///当结果条目被点击时触发
	void resultItemClicked(const FindResultItem& resultItem);

private slots:
	///查找结果条目被点击时触发信号对应槽
	void onItemClicked();

private:
	///存放所有找到的结果
	QList<FindResultItem> _results;
};

#endif // FINDRESULTWIDGET_H

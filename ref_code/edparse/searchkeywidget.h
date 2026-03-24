#ifndef SEARCHKEYWIDGET_H
#define SEARCHKEYWIDGET_H

#include "edparse/edparse_global.h"
#include "edparse/isearchreplacedialog.h"

#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QPushButton>

namespace Ui{
	class SearchKeyWidget;
}

/*!
	@brief   搜索关键字界面类
	@date    2015.6.17
	@author  Jianjun
*/
class EDPARSE_EXPORT SearchKeyWidget : public ISearchReplaceDialog
{
	Q_OBJECT

public:
	SearchKeyWidget(QWidget *parent = 0);
	~SearchKeyWidget();
	//search

	///获取搜索内容 
	QString getSearchContent() const;

	///获取替换内容
	QString getReplaceContent() const;

	///设置类型为查找or替换，默认为查找
	virtual void setTypeFindOrReplace(bool showFind=true);

private slots:
	//search页对应槽函数

	///下一个按钮单击对应槽
	void onNextPushButtonClicked();

	///上一个按钮单击对应槽
	void onPreviousPushButtonClicked();

	///搜索所有按钮单击对应槽
	void onSearchAllPushButtonClicked();

	///用正则表达式复选框对应槽
	void onSearchUseCheckBoxClicked();

	///search options展开按钮单击事件对应槽
	void onSearchOpenGroupBtnClicked();

	///results options展开按钮单击事件对应槽
	void onSearchOpenGroupToolBtn2Clicked();

	//find or replace 开关

	///查找按钮单击事件对应槽
	void onFindBtnClicked();

	///替换按钮单击事件对应槽
	void onReplaceBtnClicked();

	//replace页对应槽

	///替换按钮单击对应槽
	void onReplacePushButtonClicked();

	///替换所有按钮单击对应槽
	void onReplaceAllPushButtonClicked();

	///读取界面最新值
	void controls2Values();

	///插入搜索历史
	void insertSearchHistory(QString str);

	///更新窗口
	void updateWindow();

private:
	Ui::SearchKeyWidget *ui;
};

#endif // SEARCHKEYWIDGET_H

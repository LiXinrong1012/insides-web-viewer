#ifndef TAGMANAGEDIALOG_H
#define TAGMANAGEDIALOG_H

#include <QDialog>
namespace Ui {class TagManageDialog;};

/*!
	@brief   tags管理对话框，可进行添加或删除
	@date    2015.6.18
	@author  Jianjun
*/
class TagManageDialog : public QDialog
{
	Q_OBJECT

public:
	TagManageDialog(QWidget *parent = 0);
	~TagManageDialog();

private slots:
	///新标签按钮点击时调用
	void onNewTagsBtnClicked();

	///删除按钮点击时调用
	void onDelBtnClicked();

private:
	Ui::TagManageDialog *ui;
};

#endif // TAGMANAGEDIALOG_H

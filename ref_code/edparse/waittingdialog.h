#ifndef WAITTINGDIALOG_H
#define WAITTINGDIALOG_H

#include <QDialog>
namespace Ui {class WaittingDialog;};

/*!
	@brief   该类还未使用，功能不明
	@date    2015.6.18
	@author
*/
class WaittingDialog : public QDialog
{
	Q_OBJECT

public:
	WaittingDialog(QWidget *parent = 0);
	~WaittingDialog();

	void setBtnEnable(bool b);
private slots:
	void onOkBtnClicked();
private:
	Ui::WaittingDialog *ui;
};

#endif // WAITTINGDIALOG_H

#ifndef HOOPSVISIBILITYSETTINGDIALOG_H
#define HOOPSVISIBILITYSETTINGDIALOG_H

#include <QDialog>
namespace Ui {class HoopsVisibilitySettingDialog;};

class HoopsVisibilitySettingDialog : public QDialog
{
	Q_OBJECT

public:
	HoopsVisibilitySettingDialog(QWidget *parent = 0);
	~HoopsVisibilitySettingDialog();

private:
	Ui::HoopsVisibilitySettingDialog *ui;
};

#endif // HOOPSVISIBILITYSETTINGDIALOG_H

#ifndef HOOPSVISIBILITYSETTINGDIALOG_H
#define HOOPSVISIBILITYSETTINGDIALOG_H

#include <QDialog>
#include <QModelIndex>

class AppearanceItem;
class QRadioButton;

namespace Ui {class HoopsVisibilitySettingDialog;};

class HoopsVisibilitySettingDialog : public QDialog
{
	Q_OBJECT

public:
	HoopsVisibilitySettingDialog(QWidget *parent = 0);
	~HoopsVisibilitySettingDialog();

	void setAppearance(AppearanceItem* item);
	void setModel(const QModelIndex& modelIndex){_modelIndex=modelIndex;}

protected slots:
	void value2Control();
	void control2Value();

	void checkAllClicked();

private:
	Ui::HoopsVisibilitySettingDialog *ui;
	AppearanceItem*			_appItem;
	QList<QList<QRadioButton*> >	_btnList;
	QModelIndex		_modelIndex;
	bool			_enabled;
};

#endif // HOOPSVISIBILITYSETTINGDIALOG_H

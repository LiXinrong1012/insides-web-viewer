#ifndef CONTOURDISPLAYSELECTORDIALOG_H
#define CONTOURDISPLAYSELECTORDIALOG_H

#include <QDialog>
namespace Ui {class ContourDisplaySelectorDialog;};

class ContourDisplaySelectorWidget;

class ContourDisplaySelectorDialog : public QDialog
{
	Q_OBJECT

public:
	ContourDisplaySelectorDialog(QWidget *parent = 0);
	~ContourDisplaySelectorDialog();

	ContourDisplaySelectorWidget* getWidget();

private:
	Ui::ContourDisplaySelectorDialog *ui;
};

#endif // CONTOURDISPLAYSELECTORDIALOG_H

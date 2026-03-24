#ifndef SETWINDOWCOLORDIALOG_H
#define SETWINDOWCOLORDIALOG_H

#include <QDialog>
#include <QFrame>
namespace Ui {class SetWindowColorDialog;};

class HBaseView;

class SetWindowColorDialog : public QDialog
{
	Q_OBJECT

public:
	SetWindowColorDialog(QWidget * parent, HBaseView * pBaseView);
	~SetWindowColorDialog();

private:
	Ui::SetWindowColorDialog *ui;
	public slots:
		void chooseWindowTopColor();
		void chooseWindowBottomColor();

		void onOkBtnClicked();
		void onCancelBtnClicked();

protected:
	void showEvent(QShowEvent * e);

private:
	HBaseView * _baseView;

	QColor _topColor;
	QColor _bottomColor;

	QFrame * _color1Frame;
	QFrame * _color2Frame;
};

#endif // SETWINDOWCOLORDIALOG_H

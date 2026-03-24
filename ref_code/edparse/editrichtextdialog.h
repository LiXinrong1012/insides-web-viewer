#ifndef EDITRICHTEXTDIALOG_H
#define EDITRICHTEXTDIALOG_H

#include <QDialog>
namespace Ui {class EditRichTextDialog;};

/*!
	@brief    暂时还不清楚是做什么用的
	@date     2015.6.16
	@author   Jerry
*/
class EditRichTextDialog : public QDialog
{
	Q_OBJECT

public:
	EditRichTextDialog(QWidget *parent,const QString& title,const QString& label,const QString& text);
	~EditRichTextDialog();

	static QString getText(QWidget *parent,const QString& title,const QString& label,const QString& text);

private:
	Ui::EditRichTextDialog *ui;
};

#endif // EDITRICHTEXTDIALOG_H

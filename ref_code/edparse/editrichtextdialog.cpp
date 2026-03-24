#include "editrichtextdialog.h"
#include "ui_editrichtextdialog.h"

EditRichTextDialog::EditRichTextDialog( QWidget *parent,const QString& title,
	const QString& label,const QString& text )
	: QDialog(parent)
{
	ui = new Ui::EditRichTextDialog();
	ui->setupUi(this);

	setWindowTitle(title);
	ui->label->setText(label);
	ui->txt->setPlainText(text);
}

EditRichTextDialog::~EditRichTextDialog()
{
	delete ui;
}

QString EditRichTextDialog::getText( QWidget *parent,const QString& title,const QString& label,const QString& text )
{
	EditRichTextDialog dlg(parent,title,label,text);
	dlg.exec();

	return dlg.ui->txt->toPlainText();

}


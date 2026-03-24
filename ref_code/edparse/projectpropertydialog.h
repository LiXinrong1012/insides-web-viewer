#ifndef PROJECTPROPERTYDIALOG_H
#define PROJECTPROPERTYDIALOG_H

#include <QDialog>
#include "ui_projectpropertydialog.h"

class ProjectPropertyDialog : public QDialog
{
	Q_OBJECT

public:
	ProjectPropertyDialog(QWidget *parent = 0);
	~ProjectPropertyDialog();

private:
	Ui::ProjectPropertyDialog ui;
};

#endif // PROJECTPROPERTYDIALOG_H

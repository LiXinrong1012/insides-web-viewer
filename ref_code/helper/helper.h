#ifndef HELPER_H
#define HELPER_H

#include <QtGui/QMainWindow>
#include "ui_helper.h"

class helper : public QMainWindow
{
	Q_OBJECT

public:
	helper(QWidget *parent = 0, Qt::WFlags flags = 0);
	~helper();

private:
	Ui::helperClass ui;
};

#endif // HELPER_H

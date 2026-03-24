#ifndef TMPWIDGET2_H
#define TMPWIDGET2_H

#include <QWidget>
namespace Ui {class TmpWidget2;};

class TmpWidget2 : public QWidget
{
	Q_OBJECT

public:
	TmpWidget2(QWidget *parent = 0);
	~TmpWidget2();

private:
	Ui::TmpWidget2 *ui;
};

#endif // TMPWIDGET2_H

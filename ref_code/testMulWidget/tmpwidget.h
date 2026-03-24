#ifndef TMPWIDGET_H
#define TMPWIDGET_H

#include <QWidget>
namespace Ui {class TmpWidget;};

class TmpWidget : public QWidget
{
	Q_OBJECT

public:
	TmpWidget(QWidget *parent = 0);
	~TmpWidget();

private:
	Ui::TmpWidget *ui;
};

#endif // TMPWIDGET_H

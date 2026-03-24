#ifndef TESTPARADLG_H
#define TESTPARADLG_H

#include <QDialog>
namespace Ui {class TestParaDlg;};


class TestParaDlg : public QDialog
{
	Q_OBJECT

public:
	TestParaDlg(QWidget *parent = 0);
	~TestParaDlg();

private:
	Ui::TestParaDlg *ui;
};

#endif // TESTPARADLG_H

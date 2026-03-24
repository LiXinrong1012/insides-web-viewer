#ifndef SECTIONINPUTDIALOG_H
#define SECTIONINPUTDIALOG_H

#include <QDialog>
namespace Ui {class SectionInputDialog;};

class SectionInputDialog : public QDialog
{
	Q_OBJECT

public:
	SectionInputDialog(QWidget *parent = 0);
	~SectionInputDialog();

	QList<double> getSection1DPoints();
	QList<double> getSection1DParameters();

protected slots:
	void onOK();

private:
	Ui::SectionInputDialog *ui;
};

#endif // SECTIONINPUTDIALOG_H

#ifndef EXPRESSINPUTDIALOG_H
#define EXPRESSINPUTDIALOG_H

#include <QDialog>
#include <qlist.h>
#include "pretdy/TDYParameters.h"
#include <QListWidgetItem>
namespace Ui {class ExpressInputDialog;};


class ExpressInputDialog : public QDialog
{
	Q_OBJECT

public:
	ExpressInputDialog(QWidget *parent = 0);
	ExpressInputDialog(TDYParameterItem item );
	~ExpressInputDialog();
public:
	TDYParameterItem* getInputItem();
	void InitData();
	int m_nCombolistIndex;

	private slots:
		void onShowList(int);
		void onHelpShow(QListWidgetItem*);
		void onAddTxtToEnd(QListWidgetItem*);
		void onShowMenu();
		void smarkerAct();
		void srigidAct();
		void sjointAct();
		void onOK();




private:
	Ui::ExpressInputDialog *ui;
	QList<QList<TDYParameterItem>> comboList;

};

#endif // EXPRESSINPUTDIALOG_H
